
#include "Dispatcher.h"
#include "Component.h"
#include "TimeVal.h"

namespace eAccelero
{

Dispatcher::Dispatcher(int waitDuration)
    : m_exitCause(NORMAL_EXIT),
     m_stop(0),
      m_waitDuration(waitDuration)
{
}

Dispatcher::~Dispatcher()
{
    for(NotifierMap::iterator it = m_notifiers.begin();
        it != m_notifiers.end(); )
    {
        delete it->second;
        m_notifiers.erase(it++);
    }
}

EventHandlerId Dispatcher::AddEventHandler(const EventSlotBase &slot, const Event &eventDetails)
{
    NotifierMap::iterator it = m_notifiers.find(eventDetails.EventType());
    if (it == m_notifiers.end())
    {
        throw ComponentExceptionLog(Logger::EACC_LOG_CRITICAL,
                "Notifier not found for event type");
    }
    return it->second->AddEventHandler(slot, eventDetails);
}

void Dispatcher::RemoveEventHandler(unsigned eventType, EventHandlerId id)
{
    NotifierMap::iterator it = m_notifiers.find(eventType);
    if (it == m_notifiers.end())
    {
        throw ComponentExceptionLog(Logger::EACC_LOG_CRITICAL,
                "Notifier not found for event type");
    }
    it->second->RemoveEventHandler(id);
}

void Dispatcher::RegisterNotifier(unsigned eventType, NotifierBase *notifier)
{
    NotifierMap::iterator it = m_notifiers.find(eventType);
    if (it != m_notifiers.end())
    {
        throw ComponentExceptionLog(Logger::EACC_LOG_FATAL,
                "Notifier already present for event type");
    }
    m_notifiers[eventType] = notifier;
}

void Dispatcher::DeregisterNotifier(unsigned eventType)
{
    NotifierMap::iterator it = m_notifiers.find(eventType);
    if (it == m_notifiers.end())
    {
        throw ComponentExceptionLog(Logger::EACC_LOG_WARNING,
                "Notifier not found for event type");
    }
    delete it->second;
    m_notifiers.erase(it);
}

void Dispatcher::Run()
{
    NotifierMap::iterator it;
    int waitDuration = m_waitDuration;
    TimeVal start, end;

    while(!m_stop)
    {
        start.now();
        for(it = m_notifiers.begin(); it != m_notifiers.end(); it++)
        {
            // Check for events
            it->second->Poll(waitDuration);
        }
        end.now() -= start;

        // Adjust the wait duration based on the time spent on notifications
        waitDuration = m_waitDuration - end.Truncate();
        if (waitDuration < 0)
        {
            // the notifiers have overshot the waitDuration, don't wait
            // go on a busy loop
            waitDuration = 0;
        }
    }
    std::cout << "Dispatcher exiting because of exit cause:" << m_exitCause << std::endl;
}

} // namespace eAccelero
