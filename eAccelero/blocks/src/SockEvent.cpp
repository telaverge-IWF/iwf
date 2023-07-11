#include "SockEvent.h"
#include "Component.h"

namespace eAccelero
{

EventHandlerId SockEventNotifier::AddEventHandler(
                    const EventSlotBase &slot, const Event &eventDetails)
{
    EventHandlerId evhId = 0;
    EPollEntry *entry = m_allocator.alloc(&evhId);
    const SockEvent &ev = static_cast<const SockEvent&>(eventDetails);
    entry->m_fd = ev.FD();
    const_cast<EventSlotBase &>(slot).Duplicate((void*)entry);

    m_epoll.add(entry->m_fd, ev.Events(), evhId);

    return evhId;
}

void SockEventNotifier::RemoveEventHandler(EventHandlerId id)
{
    EPollEntry *entry = m_allocator[id];
    m_epoll.remove(entry->m_fd);
    entry->m_fd = Socket::INVALID_FD;

    // Call the destructors
    reinterpret_cast<EventSlotBase*>(&entry->m_slot)->~EventSlotBase();

    m_allocator.free(entry);
}
 
int SockEventNotifier::Poll(int &waitDuration)
{
    int ret = 0;
    struct epoll_event *event = NULL;
    struct EPollEntry *entry = NULL;

    ret = m_epoll.wait(m_events, waitDuration);
    if (ret > 0)
    {
        int rc = 0;
        for(int i = 0; i < ret; i++)
        {
            event = &m_events[i];
            //CLOG_DEBUG("SockEvent 0x%x on evh %d", event->events, event->data.u32);
            
            entry = m_allocator.find(event->data.u32);
            if (entry == NULL)
            {
                // Probably the entry was removed in a previous notify call
                continue;
            }
            
            SockEvent ev(entry->m_fd, event->data.u32, event->events);
            //CLOG_DEBUG("Notifying sockevent on fd %d", entry->m_fd);

            rc = reinterpret_cast<EventSlotBase*>(&entry->m_slot)-> Notify(ev);
            if (rc == Dispatcher::REMOVE_EVENT_HANDLER)
            {
                ComponentBase::Instance().GetDispatcher()->RemoveEventHandler(SOCK_EVENT_TYPE, event->data.u32);
            }
            else if (ev.Events() != event->events)
            {
                // Check if the file descriptor was removed. might have got removed
                entry = m_allocator.find(event->data.u32);
                if (entry)
                {
                    // The events were modified in the notiy. Register for the new events
                    m_epoll.modify(entry->m_fd, ev.Events(), event->data.u32);
                }
            }
        }
    }
    else if (ret < 0)
    {
        // EINTR, handle signals here
    }
    // if ret == 0 then it is the epoll timeout

    return ret;
}

} //namespace eAccelero
