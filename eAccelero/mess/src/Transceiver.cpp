
#include "MeSS.h"

namespace eAccelero
{

    
void MeSSageQ::PushBack(MeSSage* msg)
{
    Mutex::ScopedMutex  guard(m_lock);

    if (m_head == NULL)
    {
        // prev and next will be NULL
        m_head = msg;
        m_tail = msg; 
    }
    else
    {
        m_tail->m_next = msg;
        msg->m_prev = m_tail;
        m_tail = msg;
    }

    m_count++;    
}
void MeSSageQ::PushFront(MeSSage* msg)
{
    Mutex::ScopedMutex  guard(m_lock);

    if (m_head == NULL)
    {
        // prev and next will be NULL
        m_head = msg;
        m_tail = msg; 
    }
    else
    {
        msg->m_next = m_head;
        m_head->m_prev = msg;
        m_head = msg;
    }

    m_count++;    
}

MeSSage* MeSSageQ::PopFrontNoLock()
{
    MeSSage *ret = m_head;
    if (ret)
    {
        EACC_ASSERT(m_count != 0);

        if (ret == m_tail) m_tail = NULL;
        m_head = ret->m_next;
        ret->Unlink();
        m_count--;              
    }

    return ret;        
}

void MeSSageQ::Erase(MeSSage* msg)
{
    Mutex::ScopedMutex  guard(m_lock);
    EACC_ASSERT(m_count != 0);

#ifdef DEBUG
    // Check if the msg is part of the pending queue
    bool found = false;
    for (MeSSage *ptr = m_head; ptr; ptr = ptr->m_next)
    {
        if (ptr == msg)
        {
            found = true;
            break;
        }
    }
    EACC_ASSERT(found);

#endif

    if (msg == m_head) m_head = msg->m_next;
    if (msg == m_tail) m_tail = msg->m_prev;

    msg->Unlink();
    m_count--;
}

Transceiver::Transceiver(MeSSEndpoint &self, unsigned sockType)
    : m_sock(sockType),
      m_sockType(0),
      m_evhId(-1),
      m_timerId(-1),
      m_writable(false)
{
    if (sockType == SOCK_SEQPACKET)
    {
        m_evhId = ComponentBase::Instance().GetDispatcher()->AddEventHandler(
                    EventSlot<SockEvent, Transceiver>(this, &Transceiver::OnSockEvent),
                    SockEvent(m_sock.FD()));
    }
    else if (sockType == SOCK_RDM)
    {
        m_sockType = MESS_MIN_RDM_INSTANCE;
        this->Bind(self);
    }
    else if (sockType == SOCK_DGRAM)
    {
        m_sockType = MESS_MIN_DGM_INSTANCE;
        this->Bind(self);
    }
   
    this->ResetHooks();
    
    m_timerId = ComponentBase::Instance().GetDispatcher()->AddEventHandler(
                    EventSlot<TimerEvent, Transceiver>(this, &Transceiver::OnTimerEvent),
                    TimerEvent(PERIODIC_TIMER));                
}

Transceiver::Transceiver(int sockFD)
    : m_sockType(0),
      m_evhId(-1),
      m_timerId(-1),
      m_writable(false)
{
    m_sock.FD() = sockFD;
    
    this->ResetHooks();

    m_evhId = ComponentBase::Instance().GetDispatcher()->AddEventHandler(
                    EventSlot<SockEvent, Transceiver>(this, &Transceiver::OnSockEvent),
                    SockEvent(m_sock.FD()));
                    
    m_timerId = ComponentBase::Instance().GetDispatcher()->AddEventHandler(
                    EventSlot<TimerEvent, Transceiver>(this, &Transceiver::OnTimerEvent),
                    TimerEvent(PERIODIC_TIMER));    
}

Transceiver::~Transceiver()
{
    ComponentBase::Instance().GetDispatcher()->RemoveEventHandler(TIMER_EVENT_TYPE,
                                                 m_timerId);
            
    this->Cleanup();
}

int Transceiver::OnSockEvent(SockEvent &event)
{
    if (event.Events() & SockEvent::READ_EVENT)
    {
        int ret;
        m_timeStamp.nowMonotonic();
        // TODO make the size related to the payload size received
        MeSSage *in = MeSSage::CreateMessage(MAX_RECV_BUFF_SZ - sizeof(MeSSage));
        try
        {
            ret = m_sock.Recv(in->Buffer(), in->Size());
            if (ret == 0)
            {
                this->Cleanup();
            }
            else if (ret > 0)
            {
                MeSSage *req = NULL;
                bool drop = false;

                if (m_hooks.onReadHook)
                {
                    this->OnRead(in);
                }

                if (!in->IsRequest() && (in->Hdr().mcast == 0))
                {
                    // Check if the request was orginated by this node
                    unsigned nodeId = MeSSage::ExtractSrcNodeId(in->Id());
                    if (nodeId == MeSS::MeSSObj().SelfNodeId())
                    {
                        unsigned tid = MeSSage::ExtractAllocId(in->Id());

                        // Response message. Get the corresponding request
                        req = (MeSSage*)MeSS::MeSSObj().Pool().Find(tid);
                        if (req && req->IsPendingResp())
                        {
                            m_pendingQ.Erase(req);
                        }
                        else if (req && req->IsPendingSend())
                        {
                            // There might be a stray response when the component
                            // has restarted and sent a request. But the request is
                            // not yet sent. The response received would have been 
                            // before the component had restarted. 
                            CLOG_ERROR("Response received for unsent request."
                                    " Probably a stray response %x from {%d, %d}."
                                    " Dropping message 0x%x",
                                    req->Id(), req->Hdr().src.compId,
                                    req->Hdr().src.instance, req->Hdr().msgId.msgId);
                            drop = true;
                        }
                        else
                        {
                            // Answer uncorrelated
                            CLOG_WARNING("Unable to find Request for a response "
                                    "message %x. Dropping!", in->Id());
                            drop = true;
                        }
                    }
                    else
                    {
                        // Response not for self
                        CLOG_WARNING("Response message not destined for self. "
                                "MsgId: 0x%x, Origin-Node: %d", in->Id(), nodeId);
                        drop = true;
                    }
                }
                if (!drop)
                {
                    ret = MeSS::MeSSObj().Dispatch(this, in, req);
                    if (ret != Interface::Success && in->IsRequest())
                    {
                        MeSSage *resp = MeSSage::CreateRespMessage(*in, 0);
                        if (ret == Interface::DecodeFailure)
                        {
                            resp->Hdr().code = CODE_DECODE_ERROR;
                        }
                        else
                        {
                            resp->Hdr().code = CODE_INVALID_MESSAGE;
                        }

                        CLOG_WARNING("Unable to dispatch, error - %d, method - 0x%x",
                                ret, in->Hdr().msgId.msgId);

                        this->Send(resp);
                    }
                    if (req)
                    {
                        MeSSage::DestroyMessage(req);
                    }
                }
            }
        }
        catch(SocketException &e)
        {
            CLOG_WARNING("MeSS Socket exception thrown on Recv <%s>", e.what());
            this->Cleanup();
        }
        MeSSage::DestroyMessage(in);
    }
    if (event.Events() & SockEvent::WRITE_EVENT)
    {
        int ret = 0;
        if (m_hooks.onWritableHook)
        {
            ret = this->OnWritable();
            if (ret != 0)
            {
                // Do a cleanup
                this->Cleanup();
            }
        }

        if (ret == 0)
        {
            m_writable = true;
            this->Send();
        }
    }
    if (event.Events() & SockEvent::ERROR_EVENT)
    {
        // Close the socket
        CLOG_WARNING("Error event received on MeSS Rdm sock");
        if (m_hooks.onErrorHook)
        {
            this->OnError();
        }
        this->Cleanup();
    }
    
    if (m_evhId != (unsigned)(-1))
    {
        if (!m_writable)
        {
            event.Events() = SockEvent::READ_EVENT | SockEvent::WRITE_EVENT;
        }
        else
        {
            event.Events() = SockEvent::READ_EVENT;
        }
    }
    else
    {
        // Destroyable, delete me
        delete this;
    }

    if (MeSS::MeSSObj().IsRebindPending())
    {
        MeSS::MeSSObj().DeferredRebind();
    }

    return 0;
}

int Transceiver::OnTimerEvent(TimerEvent &event)
{
    // Go through the pending queue and find expired requests
    MeSSage *msg;
    TimeVal tv;
    tv.nowMonotonic() -= MeSS::REQ_EXPIRY_TIME;
    while (1)
    {
        m_pendingQ.Lock();
        if (m_pendingQ.Empty())
        {
            m_pendingQ.Unlock();
            break;
        }
        if (tv < m_pendingQ.Peek()->Tstamp())
        {
            m_pendingQ.Unlock();
            // Current time is less
            break;
        }

        msg = m_pendingQ.PopFrontNoLock();
        m_pendingQ.Unlock();

        MeSS::MeSSObj().Dispatch(NULL, NULL, msg, MESS_STATUS_TIMEOUT);
        
        MeSSage::DestroyMessage(msg);
        // TODO, do it in a staggerred manner, not everything one shot
    }

    return 1;
}

void Transceiver::BouncePending()
{
    MeSSage *msg = NULL;

    m_pendingQ.Lock();
    while(!m_pendingQ.Empty())
    {
        msg = m_pendingQ.PopFrontNoLock();
        if (msg->IsRequest())
        {
            m_pendingQ.Unlock();
            MeSS::MeSSObj().Dispatch(NULL, NULL, msg, MESS_STATUS_BOUNCE);
            m_pendingQ.Lock();
        }
        MeSSage::DestroyMessage(msg);
    }
    m_pendingQ.Unlock();

    m_sendQ.Lock();
    while(!m_sendQ.Empty())
    {
        msg = m_sendQ.PopFrontNoLock();
        if (msg->IsRequest())
        {
            m_sendQ.Unlock();
            MeSS::MeSSObj().Dispatch(NULL, NULL, msg, MESS_STATUS_BOUNCE);
            m_sendQ.Lock();
        }
        MeSSage::DestroyMessage(msg);
    }
    m_sendQ.Unlock();
}

void Transceiver::Send(MeSSage *msg)
{
    msg->SetPendingSend();
    m_sendQ.PushBack(msg);
    this->Send();
}

void Transceiver::Send()
{
    MeSSage *msg = NULL;
    const int MAX_MSGS_PER_SEND = 40;
    TIPCAddr addr(TIPC_CLUSTER_SCOPE);
    int ret = 0;
    unsigned lower = 0, upper = 0;
    bool queued = false;

    for(int i = 0; i < MAX_MSGS_PER_SEND; i++)
    {
        if (!m_writable)
        {
            break;
        }

        msg = m_sendQ.PopFront();
        if (msg == NULL)
        {
            // Queue empty.. nothing to send
            break;
        }

        if (msg->Hdr().mcast)
        {
            unsigned short inst = MESS_ToInst(msg->Dest().instance);
            lower = MESS_GetDMOffset(msg->Dest().instance);
            upper = msg->Dest().instance;
            if (inst == MESS_MULTICAST_STANDBY)
            {
                lower = MESS_ToDMInst(lower, MESS_MIN_STANDBY_INSTANCE);
            }
        }
        else
        {
            // unicast message
            lower = msg->Dest().instance;
            upper = msg->Dest().instance;
        }

        queued = false;
        if (msg->m_hdr.reqFlag && msg->m_hdr.mcast == 0)
        {
            msg->Tstamp().nowMonotonic();
            // put request/non-multicast messages into the pending queue
            msg->SetPendingResp();
            m_pendingQ.PushBack(msg);
            queued = true;
        }
        
        addr.SetNameSeq(msg->Dest().compId, lower, upper);
        ret = this->SockSend(addr, msg->Buffer(), msg->Len());
        if (ret < 0)
        {
            // EAGAIN, try again later, set the WRITE FD
            m_writable = false;
            if (queued)
            {
                // Remove from pending and put it in sendQ
                m_pendingQ.Erase(msg);
            }
            msg->SetPendingSend();
            m_sendQ.PushFront(msg);

            break;
        }

        if (!queued)
        {
            // delete the sent response messsage or multicast message
            MeSSage::DestroyMessage(msg);
        }
    }
    
    if (!m_sendQ.Empty())
    {
        // try again later
        m_writable = false;
    }
}

void Transceiver::Bind(MeSSEndpoint &self)
{
    TIPCAddr addr(TIPC_CLUSTER_SCOPE);
    // For RDM and DGM seperate instances are used
    addr.SetNameSeq(self.compId, MESS_ToDMInst(m_sockType, self.instance),
                                 MESS_ToDMInst(m_sockType, self.instance));    
    m_sock.Bind(addr);
    m_sock.SetNonBlocking(1);
    m_evhId = ComponentBase::Instance().GetDispatcher()->AddEventHandler(
                    EventSlot<SockEvent, Transceiver>(this, &Transceiver::OnSockEvent),
                    SockEvent(m_sock.FD()));    
}

int Transceiver::SockSend(TIPCAddr &addr, void *msg, unsigned len)
{
    return m_sock.Send(addr, msg, len);
}

void Transceiver::Cleanup()
{
    m_writable = false;
    if (m_evhId == (unsigned)(-1))
    {
        // Nothing to cleanup, already cleaned up
        return;
    }

    // Bounce the pending messages
    this->BouncePending();
    if (m_hooks.onCleanupHook)
    {
        this->OnCleanup();
    }

    CLOG_DEBUG("Remove event handler for event %d fd %d", m_evhId, m_sock.FD());
    ComponentBase::Instance().GetDispatcher()->RemoveEventHandler(SOCK_EVENT_TYPE, m_evhId);
    m_sock.Close();
    m_evhId = -1;
}

int MeSSConnection::SockSend(TIPCAddr &addr, void *msg, unsigned len)
{
    int ret = 0;
    if (m_state != Idle)
    {
        ret = m_sock.Send(msg, len);
    }
    else
    {
        addr->addrtype = TIPC_ADDR_NAME;
        addr->addr.name.domain = 0;
        m_dest.compId = addr->addr.name.name.type;
        m_dest.instance = addr->addr.name.name.instance;

        m_state = Connecting;
        m_writable = false; // no further writes allowed
        ret = m_sock.Send(addr, msg, len);
    }
    return ret;
}

// Called for the passive connection  
int MeSSConnection::OnRead(MeSSage *in)
{
    m_hooks.onReadHook = 0;

    if (m_state == Connected)
    {
        m_dest = in->Hdr().src;

        MeSS::MeSSObj().OnMeSSConnNew(this);
        m_state = Passive;
    }
    else
    {
        EACC_ASSERT(m_state == Connecting);
        m_state = Active;
        m_writable = true;
    }

    return 0;
}

// This will be called for the client socket, after connecting
int MeSSConnection::OnWritable()
{
    int ret = 0;
    // When the socket is connecting, check the error state.
    // If success, connection succeeded, otherwise connection has failed
    // TODO start a timer for retrying the connection
    if (m_state == Connecting)
    {
        // no more hooks required
        m_hooks.onWritableHook = 0;

        ret = m_sock.GetError();
        if (ret == 0)
        {
            // Established
            m_state = Active;
            m_writable = true;
        }
        else
        {
            m_state = Idle;
        }
    }
    // Don't care about other states, infact they should not be called
    return ret;
}

// virtual int OnError();

int MeSSConnection::OnCleanup()
{
    MeSS::MeSSObj().OnMeSSConnClose(this);
    return 0;
}


 
} // namespace eAccelero
