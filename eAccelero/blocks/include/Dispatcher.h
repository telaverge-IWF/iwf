#ifndef __EACC_Dispatcher_h__
#define __EACC_Dispatcher_h__

#include <map>
#include "Exception.h"

namespace eAccelero
{
EACC_DEFINE_EXCEPTION_CLASS(DispatcherException, Exception, "Dispatcher Exception")
#define DispatcherExceptionLog(_level, _descr, ...) \
            GEN_EXCEPTION_LOG(eAccelero::DispatcherException,\
                              _descr,\
                              &eAccelero::ComponentBase::Instance().GetLogger(),\
                              _level,\
                              ##__VA_ARGS__)

// TODO Refcounting and smart pointers
class Event
{
 public:
    Event(unsigned eventType)
        : m_eventType(eventType)
    {
    }

    const unsigned EventType() const
    {
        return m_eventType;
    }

    virtual ~Event()
    {
    }

 private:
    unsigned m_eventType;
};

typedef unsigned EventHandlerId;

class EventSlotBase
{
 public:
    virtual ~EventSlotBase()
    {
    }
    virtual int Notify(Event& event) = 0;
    virtual EventSlotBase* Duplicate(void *ptr = NULL) = 0;
 protected:
    EventSlotBase()
    {
    }
};

class NotifierBase
{
 public:
    virtual ~NotifierBase()
    {
    }
    // check for events, waitDuration - wait for the specified duration.This
    // will be updated in case, the Poll takes more time.
    virtual int Poll(int &waitDuration) = 0;
    virtual EventHandlerId AddEventHandler(const EventSlotBase &slot,
                                const Event &eventDetails) = 0;
    virtual void RemoveEventHandler(EventHandlerId) = 0;
};

// Socket notifications
//  Read, write, Error, Shutdown, Polltimeout
// Timer notificaitons
//  Timeout
// Signal notifications
//  Signal


// Notifier -> eventslot -> callback
class Dispatcher
{
 public:

    enum
    {
        DEFAULT_WAIT_DURATION = 16, // in ms

	REMOVE_EVENT_HANDLER  = -1,
    };

    enum
    {
        NORMAL_EXIT =0,
        SIGTERM_SIGINT_EXIT
    };
    Dispatcher(int waitDuration = DEFAULT_WAIT_DURATION);

    ~Dispatcher();

    EventHandlerId AddEventHandler(const EventSlotBase &slot, const Event &eventDetails);

    void RemoveEventHandler(unsigned eventType, EventHandlerId id);

    void RegisterNotifier(unsigned eventType, NotifierBase *notifier);

    void DeregisterNotifier(unsigned eventType);

    void Run();

    void Stop()
    {
        m_stop = 1;
    }

    volatile unsigned m_exitCause;
 protected:
    typedef std::map<unsigned, NotifierBase*> NotifierMap;
    unsigned m_stop;

    NotifierMap m_notifiers;
    int m_waitDuration;
};

template <typename E, typename C>
class EventSlot: public EventSlotBase
{
 public:
    typedef int (C::*Callback)(E&);

    EventSlot(const C *obj, Callback cbk)
        : EventSlotBase(),
          m_obj(const_cast<C*>(obj)),
          m_cbk(cbk)
    {
    }

    int Notify(Event& event)
    {
        if (m_obj && m_cbk)
        {
            return (m_obj->*m_cbk)(static_cast<E&>(event));
        }
        return 0;
    }

    EventSlotBase* Duplicate(void *ptr = NULL)
    {
        EventSlotBase *slot = NULL;
        if (ptr)
        {
            slot = new(ptr) EventSlot((C*)this->m_obj, (Callback)this->m_cbk);
        }
        else
        {
            slot = new EventSlot((C*)this->m_obj, (Callback)this->m_cbk);
        }
        return slot;
    }

 private:
    C *m_obj;
    Callback m_cbk;
    // TODO if mutex lock required?
};

} // namespace eAccelero

#endif // __EACC_Dispatcher_h__
