#ifndef __EACC_TOP_SRV_H__
#define __EACC_TOP_SRV_H__

#include "Dispatcher.h"
#include "Tipc.h"
#include "SockEvent.h"
#include "Allocator.h"
#include "MeSSDef.h"

namespace eAccelero
{

#define TOPOLOGY_EVENT_TYPE   4

class TopologyEvent: public Event
{
 public:
    enum SubscrType
    {
        SUBSCR_TYPE_COMPONENT = TIPC_SUB_SERVICE,
        SUBSCR_TYPE_INSTANCE = TIPC_SUB_PORTS,
    };
    
    enum NotifyType
    {
        NOTIFY_TYPE_PUBLISHED = TIPC_PUBLISHED,
        NOTIFY_TYPE_WITHDRAWN  = TIPC_WITHDRAWN,
        NOTIFY_TYPE_TIMEOUT = TIPC_SUBSCR_TIMEOUT
    };

    TopologyEvent(unsigned compId, unsigned instLow, unsigned instHigh,
        void *cookie = NULL,
        unsigned msTimeout = TIPC_WAIT_FOREVER)
        : Event(TOPOLOGY_EVENT_TYPE),
          m_subscr(compId, instLow, instHigh, SUBSCR_TYPE_INSTANCE, msTimeout),
          m_evhId(-1),
          m_notifyType(NOTIFY_TYPE_PUBLISHED),
          m_lower(0),
          m_upper(0),
          m_cookie(cookie)
    {
    }
    TopologyEvent(unsigned compId,
        void *cookie = NULL,
        unsigned msTimeout = TIPC_WAIT_FOREVER)
        : Event(TOPOLOGY_EVENT_TYPE),
          m_subscr(compId, 0, MESS_MAX_INSTANCES, SUBSCR_TYPE_COMPONENT, msTimeout),
          m_evhId(-1),
          m_notifyType(NOTIFY_TYPE_PUBLISHED),
          m_lower(0),
          m_upper(0),
          m_cookie(cookie)
    {
    }
    TopologyEvent(TIPCSubscr &subscr, const TIPCAddr &port,
        EventHandlerId id, NotifyType notifyType,
        unsigned lower, unsigned upper, void *cookie)
        : Event(TOPOLOGY_EVENT_TYPE),
          m_subscr(subscr),
          m_port(port),
          m_evhId(id),
          m_notifyType(notifyType),
          m_lower(lower),
          m_upper(upper),
          m_cookie(cookie)
    {
    }

    const EventHandlerId& EvhId() const
    {
        return m_evhId;
    }
    const TIPCSubscr& Subscription() const
    {
        return m_subscr;
    }    
    TIPCSubscr& Subscription()
    {
        return m_subscr;
    }
    TIPCAddr& Port()
    {
        return m_port;
    }
    const NotifyType& NotificationType() const
    {
        return m_notifyType;
    }
    const unsigned& Lower() const
    {
        return m_lower;
    }
    const unsigned& Upper() const
    {
        return m_upper;
    }
    void* Cookie() const
    {
        return m_cookie;
    }

    void SetEventHandlerId(EventHandlerId &id) const
    {
        m_subscr.SetUserHandle((void*)(unsigned long)id);
    }

 protected:
    mutable TIPCSubscr m_subscr;
    
    TIPCAddr   m_port;

    EventHandlerId m_evhId;
    NotifyType m_notifyType;
    unsigned m_lower;
    unsigned m_upper;

    mutable void *m_cookie;
};

struct SubscrEntry
{
    char slot[4*sizeof(void*)];
    TIPCSubscr subscr;
    void *cookie;
};

class TopologyService
{
 public:
    TopologyService();

    void Initialize();

    void Terminate();

    EventHandlerId Subscribe(const EventSlotBase &slot, const TopologyEvent &event);

    void Unsubscribe(EventHandlerId evh);

    int OnSockEvent(SockEvent &event);

 protected:
    TIPCSock m_sock;
    EventHandlerId m_sockEvhId;

    typedef IndexAllocator<SubscrEntry> Subscriptions;
    Subscriptions m_subscriptions;
};

};

#endif // __EACC_TOP_SRV_H__
