#include "Timer.h"
#include "Component.h"

namespace eAccelero
{

void TimerSpoke::AddNode(TimerSpokeNode *node)
{
    if (m_head == NULL)
    {
        // prev and next will be NULL
        m_head = node;
        m_tail = node; 
    }
    else
    {
        TimerSpokeNode* current = NULL;
        current = m_tail;
        while(current != NULL)
        {
            if (node->absExpiryTime >= current->absExpiryTime)
            {
                // Node has greater expiry time than current node.
                // Add it after the current node.
                break;
            }
            current = current->prev;
        }

        if (NULL == current)
        {
            // Inital node. Add it at the start
            node->next = m_head;
            m_head->prev = node;
            m_head = node;
        }
        else
        {
            node->prev = current;
            node->next = current->next;
            if (current->next != NULL)
            {
                current->next->prev = node;
            }
            else
            {
                // current is the last node
                m_tail = node;
            }
            current->next = node;
        }
    }

    m_numNodes++;
}

void TimerSpoke::RemoveNode(TimerSpokeNode *node)
{
    if (node == m_head) m_head = node->next;
    if (node == m_tail) m_tail = node->prev;
    node->Unlink();
    m_numNodes--;
}

TimerWheel::TimerWheel(unsigned numSpokes, unsigned resolution)
    : m_numTimers(0),
      m_numSpokes(numSpokes),
      m_spokeMask(numSpokes - 1),
      m_timerResolution(resolution),
      m_resBits(__builtin_ctz(resolution)),
      m_curSpoke(0),
      m_allocator(NODES_PER_POOL, NUM_POOLS)
{
    if ((m_numSpokes & m_spokeMask) != 0 ||
        (m_timerResolution & (m_timerResolution -1)) != 0)
    {
        throw DispatcherExceptionLog(Logger::EACC_LOG_FATAL, 
                "Resolution or Num spokes must be a power of 2");
    }
    m_spokes = new TimerSpoke[m_numSpokes];

    m_curSpokeTime.nowMonotonic();
    m_curSpoke = this->ComputeSpoke(m_curSpokeTime);
}

EventHandlerId TimerWheel::AddEventHandler(const EventSlotBase &slot, const Event& event)
{
    TimeVal tv;
    EventHandlerId timerId = 0;
    unsigned spoke = 0;
    const TimerEvent &ev = static_cast<const TimerEvent&>(event);

    tv.nowMonotonic() += ev.Timeout();
    spoke = this->ComputeSpoke(tv);

    // TODO use ScopedPtr to free the alloc, when an exception is thrown

    TimerSpokeNode *node = new((void*)m_allocator.alloc(&timerId))
                            TimerSpokeNode(spoke, ev.Timeout(), tv, ev.Cookie());

    const_cast<EventSlotBase&>(slot).Duplicate((void*)node->slot);
    m_spokes[spoke].AddNode(node);

    m_numTimers++;

    return timerId;
}

void TimerWheel::RemoveEventHandler(EventHandlerId id)
{
    TimerSpokeNode* node = m_allocator[id];
    EACC_ASSERT(node->spokeId < m_numSpokes);

    m_spokes[node->spokeId].RemoveNode(node);

    // Call the desctrutor
    reinterpret_cast<EventSlotBase*>(node->slot)->~EventSlotBase();
    m_allocator.free(node);
    m_numTimers--;
}

int TimerWheel::Poll(int &waitDuration)
{
    (void)waitDuration;
    TimeVal earliest, now;
    TimerSpokeNode *node;
    bool more = false;
    bool exitFlag = true;
    int ret = 0;

    do
    {
        exitFlag = true;
        now.nowMonotonic();
        TimerSpoke& spoke = m_spokes[m_curSpoke];

        // TODO optimize to expire timers near the expiry time
        more = spoke.PeekExpiryTime(earliest);
        while (more && earliest <= now)
        {
            node = spoke.RemoveHead();

            TimerEvent te(node);
            ret = reinterpret_cast<EventSlotBase*>(node->slot)->Notify(te);
            if (ret == TimerEvent::RecurTimer)
            {
                // Make it recurring, the timerId will not change
                // Recompute the spoke and add the node to the spoke
                node->absExpiryTime.nowMonotonic();
                node->absExpiryTime += node->msExpiry;
                node->spokeId = this->ComputeSpoke(node->absExpiryTime);
                m_spokes[node->spokeId].AddNode(node);
            }
            else if (ret == TimerEvent::StopTimer)
            {
                // Delete the timer, timer fired only once
                // Node already deleted from spoke, free the used memory
                // Call the desctrutor
                reinterpret_cast<EventSlotBase*>(node->slot)->~EventSlotBase();
                m_allocator.free(node);
                m_numTimers--;
            }
            else
            {
                // Timer already stopped. Do nothing.
            }

            more = spoke.PeekExpiryTime(earliest);
        }

        now -= m_curSpokeTime;
        if (now.Truncate() >= m_timerResolution)
        {
            // Adjust for lost time in function calls, done at the dispatcher

            // TODO don't go on a frenzy, exit after looping 10-20 times, then
            //      loop later
            m_curSpoke++;
            m_curSpoke &= m_spokeMask;
            m_curSpokeTime += m_timerResolution;
            exitFlag = false;
        }
    }
    while(!exitFlag);

#if 0
    {
        static int _counter = 0;

        TimeVal drift; 
        drift.nowMonotonic() -= m_curSpokeTime;
        if(drift.Truncate() > 10)
        {
            EACC_ASSERT(0);
        }
        _counter++;
    }
#endif

    return 0;
}

} // namespace eAccelero
