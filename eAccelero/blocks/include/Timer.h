#ifndef __EACC_Timer_h__
#define __EACC_Timer_h__

#include "Dispatcher.h"
#include "TimeVal.h"
#include "Allocator.h"

namespace eAccelero
{

// TODO add stats

#define TIMER_EVENT_TYPE 3

// Should be allocated using placement new
struct TimerSpokeNode
{
    TimerSpokeNode(unsigned spoke, int msTimeout, 
        const TimeVal &expiryTime, const void *cookie = NULL)
        : spokeId(spoke),
          msExpiry(msTimeout),
          cookie((void*)cookie),
          absExpiryTime(expiryTime),
          prev(NULL),
          next(NULL)
    {
    }

    void Unlink()
    {
        if (this->prev)
        {
            EACC_ASSERT(this->prev->next);
            this->prev->next = this->next;
        }
        if (this->next)
        {
            EACC_ASSERT(this->next->prev);
            this->next->prev = this->prev;
        }

        this->next = NULL;
        this->prev = NULL;
    }

    char            slot[4*sizeof(void*)];
    unsigned        spokeId;
    unsigned        msExpiry;
    void            *cookie;
    TimeVal         absExpiryTime;
    TimerSpokeNode *prev;
    TimerSpokeNode *next;
};

class TimerSpoke
{
 public:
    TimerSpoke()
        : m_numNodes(0),
          m_head(NULL),
          m_tail(NULL)
    {
    }

    void AddNode(TimerSpokeNode *node);

    void RemoveNode(TimerSpokeNode *node);

    bool PeekExpiryTime(TimeVal &tv)
    {
        bool ret = false;
        if (m_head)
        {
            tv = m_head->absExpiryTime;
            ret = true;
        }
        return ret;
    }

    TimerSpokeNode *RemoveHead()
    {
        TimerSpokeNode *ret = NULL;
        if (m_head != NULL)
        {
            ret = m_head;
            this->RemoveNode(ret);
        }

        return ret;
    }

 protected:
    unsigned m_numNodes;
    TimerSpokeNode *m_head;
    TimerSpokeNode *m_tail;
};

class TimerWheel: public NotifierBase
{
 public:
    enum
    {
        DEFAULT_TIMER_SPOKES = 8192,
        DEFAULT_TIMER_RESOLUTION = 8,
    };

    TimerWheel(unsigned numSpokes = DEFAULT_TIMER_SPOKES,
               unsigned resolution = DEFAULT_TIMER_RESOLUTION);

    ~TimerWheel()
    {
        delete []m_spokes;
    }

    unsigned Size()
    {
        return m_numTimers;
    }

    EventHandlerId AddEventHandler(const EventSlotBase &slot, const Event& event);

    void RemoveEventHandler(EventHandlerId id);

    int Poll(int &waitDuration);

 private:
    unsigned ComputeSpoke(TimeVal &tv)
    {
        return ((tv.Truncate() >> m_resBits) & m_spokeMask);
    }

    // For the allocator
    enum
    {
        NODES_PER_POOL = DEFAULT_TIMER_SPOKES * 4,
        NUM_POOLS      = 64
    };

    unsigned m_numTimers;
    unsigned m_numSpokes;
    unsigned m_spokeMask;
    unsigned m_timerResolution;
    unsigned m_resBits;

    unsigned m_curSpoke;
    TimeVal  m_curSpokeTime;

    TimerSpoke *m_spokes;

    typedef IndexAllocator<TimerSpokeNode> Allocator;
    Allocator m_allocator;
};

class TimerEvent: public Event
{
 public:
    static const int StopTimer = 0;
    static const int RecurTimer = 1;
    static const int TimerStopped = 2;

    TimerEvent(unsigned m_msTimeout, void *cookie = NULL)
        : Event(TIMER_EVENT_TYPE),
          m_msTimeout(m_msTimeout),
          m_cookie(cookie)
    {
    }
    TimerEvent(TimerSpokeNode *node)
        : Event(TIMER_EVENT_TYPE),
          m_msTimeout(node->msExpiry),
          m_cookie(node->cookie),
          m_timerId(ALLOC_DATA_GET_IDX(node))
    {
    }
    const unsigned& Timeout() const
    {
        return m_msTimeout;
    }
    const void* Cookie() const
    {
        return m_cookie;
    }
    const EventHandlerId TimerId() const
    {
        return m_timerId;
    }
 protected:
    unsigned m_msTimeout;
    void *m_cookie;
    EventHandlerId m_timerId;
};


} // namespace eAccelero

#endif // __EACC_Timer_h__
