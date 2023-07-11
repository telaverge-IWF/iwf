#include "TopSrv.h"
#include "Component.h"

namespace eAccelero
{

TopologyService::TopologyService()
    : m_sock(SOCK_SEQPACKET),
      m_sockEvhId(-1),
      m_subscriptions(128,8)
{
}

void TopologyService::Initialize()
{
    TIPCAddr addr(TIPC_CLUSTER_SCOPE);
    addr.SetName(TIPC_TOP_SRV, TIPC_TOP_SRV);
    
    m_sockEvhId = ComponentBase::Instance().GetDispatcher()->AddEventHandler(
        EventSlot<SockEvent, TopologyService>(this, &TopologyService::OnSockEvent),
        SockEvent(m_sock.FD(), SockEvent::READ_EVENT));    
    
    m_sock.Connect(addr);
}

void TopologyService::Terminate()
{
    ComponentBase::Instance().GetDispatcher()->RemoveEventHandler(
        SOCK_EVENT_TYPE, m_sockEvhId);
    m_sock.Close();
}

EventHandlerId TopologyService::Subscribe(const EventSlotBase &slot, const TopologyEvent &event)
{
    EventHandlerId id;
    SubscrEntry *entry = m_subscriptions.alloc(&id);
    const_cast<EventSlotBase &>(slot).Duplicate((void*)entry->slot);

    event.SetEventHandlerId(id);
    entry->subscr = event.Subscription();

    // Send the subscription information to the Topology server
    m_sock.Send((void*)(const struct tipc_subscr*)event.Subscription(),
                sizeof(struct tipc_subscr));

    return id;
}

void TopologyService::Unsubscribe(EventHandlerId evh)
{
    SubscrEntry *entry = m_subscriptions[evh];
    entry->subscr.Filter(entry->subscr.Filter() | TIPC_SUB_CANCEL);
    
    // std::cout << "Unsubscribing... " << entry->subscr << std::endl;

    m_sock.Send((struct tipc_subscr*)entry->subscr,
                sizeof(struct tipc_subscr));

    m_subscriptions.free(entry);
}

int TopologyService::OnSockEvent(SockEvent &event)
{
    // Only read events are expected
    if (event.Events() & SockEvent::READ_EVENT)
    {
        TIPCEvent te;
        EventHandlerId evhId;
        // int ret = 0;
        
        CLOG_DEBUG("Topology service event received");
        
        m_sock.Recv((struct tipc_event*)te, sizeof(tipc_event));
        
        TIPCSubscr subscr = te.Subscr();
        evhId = (unsigned)(unsigned long)subscr.GetUserHandle();
        SubscrEntry *entry = m_subscriptions[evhId];
        
        TopologyEvent tpe(subscr, te.Port(), evhId, (TopologyEvent::NotifyType)te.Event(),
                          te.Lower(), te.Upper(), entry->cookie);
                          
        reinterpret_cast<EventSlotBase*>(&entry->slot)->Notify(tpe);
    }
    
    return 0;
}

}

