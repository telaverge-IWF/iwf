#include "MeSS.h"
#include "MeSSComponent.h"
#include "ComponentDefines.h"

namespace eAccelero
{

__thread MeSSHandle MeSS::tss_state;
    
MeSS* MeSS::m_messObj = NULL;
    
MeSS::MeSS(MeSSComponent& comp)
    : Subcomponent("MeSS", SUBCOMP_MESS),
      m_comp(comp),
      m_selfNodeId(),
      m_seqSock(NULL),
      m_seqSockEvH(-1),
      m_rdmSock(NULL),
      m_dgmSock(NULL),
      m_messThreadId(0),
      m_rebindPending(false)
{
    m_messObj = this;
    
    m_comp.RegisterSubcomponent(this);
}

MeSS::~MeSS()
{
    this->CleanupSocks();
}

void MeSS::Initialize()
{
    // Get self node id
    TIPCAddr addr;
    TIPCSock sock(SOCK_RDM);

    sock.GetSockAddr(addr);
    m_selfNodeId = tipc_node((((struct sockaddr_tipc *) addr)->addr.id.node));

    m_self.instance = m_cmdArgs.instance;
    m_self.compId   = m_comp.Id();

    // Connect to the topology server to get subscription events
    m_topSvc.Initialize();

    this->Bind();
}

void MeSS::Rebind(MeSSEndpoint &meSSEndpoint, bool immediate)
{
    if (!immediate)
    {
        m_rebindPending = true;
        m_newEndpoint   = meSSEndpoint;

        CLOG_DEBUG("Deferring Rebind on {%d, %d} ", 
                m_newEndpoint.compId, m_newEndpoint.instance);
    }
    else
    {
        ScopedWriteLock guard(m_rebindLock);
        m_self = meSSEndpoint;
        this->Bind();
    }
}

void MeSS::DeferredRebind()
{
    ScopedWriteLock guard(m_rebindLock);

    m_rebindPending = false;
    m_self.instance = m_newEndpoint.instance;
    m_self.compId   = m_newEndpoint.compId;
    
    this->Bind();

    CLOG_INFO("MeSS Rebind to {%d, %d} completed", m_self.compId, m_self.instance);
}

void MeSS::Bind()
{
    TIPCAddr addr(TIPC_CLUSTER_SCOPE);
    addr.SetNameSeq(m_self.compId, m_self.instance, m_self.instance);

    this->CleanupSocks();

    m_seqSock = new TIPCSock(SOCK_SEQPACKET);
    m_seqSock->Bind(addr);
    m_seqSock->Listen();
    m_seqSockEvH = ComponentBase::Instance().GetDispatcher()->AddEventHandler(
                    EventSlot<SockEvent, MeSS>(this, &MeSS::OnSeqSockEvent),
                    SockEvent(m_seqSock->FD(), SockEvent::READ_EVENT));
    m_seqSock->SetNonBlocking(1);

    m_rdmSock = new Transceiver(m_self, SOCK_RDM);
    m_dgmSock = new Transceiver(m_self, SOCK_DGRAM);
}

void MeSS::CleanupSocks()
{
    if (m_seqSock)
    {
        //Cleanup connections first
        for (ConnMap::iterator it = m_connMap.begin(); it != m_connMap.end();)
        {
            CLOG_DEBUG("Cleaning up connection for dest {%d:%d}",
                        it->second->Dest().compId, it->second->Dest().instance);
            delete it->second;
            m_connMap.erase(it++);
        }

        CLOG_DEBUG("Cleaning up seq server sock");
        ComponentBase::Instance().GetDispatcher()->RemoveEventHandler(SOCK_EVENT_TYPE, m_seqSockEvH);
        delete m_seqSock;
        m_seqSock = NULL;
    }
    if (m_rdmSock)
    {
        CLOG_DEBUG("Cleaning up RDM sock");
        delete m_rdmSock;
        m_rdmSock = NULL;
    }
    if (m_dgmSock)
    {
        CLOG_DEBUG("Cleaning up Datagram sock");
        delete m_dgmSock;
        m_dgmSock = NULL;
    }
}

void MeSS::Terminate()
{
    m_topSvc.Terminate();
    
    this->CleanupSocks();
    
    // Remove the interfaces and response handlers
    for(IfMap::iterator it = m_ifaceMap.begin();
        it != m_ifaceMap.end(); )
    {
        m_ifaceMap.erase(it++);
    }
    for(RespMap::iterator it = m_respMap.begin();
        it != m_respMap.end(); )
    {
        delete it->second;
        m_respMap.erase(it++);
    }    
}

int MeSS::OnSeqSockEvent(SockEvent &event)
{
    if (event.Events() & SockEvent::READ_EVENT)
    {
        TIPCAddr from;
        int connFd;
        connFd = m_seqSock->Accept(from);

        CLOG_INFO("Accepted connection %d", connFd);

        new MeSSConnection(connFd);
    }
    if (event.Events() & SockEvent::ERROR_EVENT)
    {
        CLOG_FATAL("Error event received on MeSS server sock");
        throw MeSSException("MeSS error event");
    }
    return 0;
}

unsigned MeSS::Send(const MeSSEndpoint &dest, const MessageId &msgId, void *payload,
               unsigned len, void *cookie, unsigned flags)
{
    Transceiver *sock;
    MeSSEndpoint des = dest;
    unsigned offset = 0;

    if (EACC_UNLIKELY(m_rebindPending == true))
    {
        // Create Dummy and dispatch error
        // Optimize: don't have to create a request and destroy it
        MeSSage *req = MeSSage::CreateReqMessage(des, msgId, len, cookie);
        memcpy(req->Payload(), payload, len);
        CLOG_WARNING("Mess not ready, rebind in progress, failing to send to %d:%d", 
                     dest.compId, dest.instance);
        this->Dispatch(NULL, NULL, req, MESS_STATUS_NOT_READY);

        MeSSage::DestroyMessage(req);

        return INVALID_IDX;
    }

    ScopedReadLock guard(m_rebindLock);

    if (flags & RDM_DELIVERY)
    {
        sock = m_rdmSock;
        offset = MESS_MIN_RDM_INSTANCE;
    }
    else if (flags & SEQ_DELIVERY)
    {
        sock = this->Lookup(dest);
    }
    else
    {
        sock = m_dgmSock;
        offset = MESS_MIN_DGM_INSTANCE;
    }

    des.instance = MESS_ToDMInst(offset, des.instance);    
    
    MeSSage *req = MeSSage::CreateReqMessage(des, msgId, len, cookie);
    memcpy(req->Payload(), payload, len);
    
    sock->Send(req);
    
    return req->Id();
}

unsigned MeSS::Send(const MeSSEndpoint &dest, const MessageId &msgId, 
            const google::protobuf::Message& msg, void *cookie, unsigned flags)
{
    Transceiver *sock;
    MeSSEndpoint des = dest;
    unsigned offset = 0;
    unsigned len = 0;

    if (EACC_UNLIKELY(m_rebindPending == true))
    {
        // Create Dummy and dispatch error
        // Optimize: don't have to create a request and destroy it
        MeSSage *req = MeSSage::CreateReqMessage(des, msgId, len, cookie);
        msg.SerializeToArray(req->Payload(), len);        
        CLOG_WARNING("Mess not ready, rebind in progress, failing to send to %d:%d", 
                     dest.compId, dest.instance);
        this->Dispatch(NULL, NULL, req, MESS_STATUS_NOT_READY);

        MeSSage::DestroyMessage(req);

        return INVALID_IDX;
    }

    ScopedReadLock guard(m_rebindLock);

    if (flags & RDM_DELIVERY)
    {
        sock = m_rdmSock;
        offset = MESS_MIN_RDM_INSTANCE;
    }
    else if (flags & SEQ_DELIVERY)
    {
        sock = this->Lookup(dest);
    }
    else
    {
        sock = m_dgmSock;
        offset = MESS_MIN_DGM_INSTANCE;
    }

    des.instance = MESS_ToDMInst(offset, des.instance);

    // From the probuf message get the size
    len = msg.ByteSize();
    MeSSage *req = MeSSage::CreateReqMessage(des, msgId, len, cookie, PROTOBUF_ENCODING);

    msg.SerializeToArray(req->Payload(), len);
    
    sock->Send(req);
    
    return req->Id();
}

int MeSS::Dispatch(Transceiver *sock, MeSSage *in, MeSSage *req, MessageStatus code)
{
    int ret = Interface::Success;

    if (in && in->IsRequest())
    {
        // Request message received
        IfMap::iterator it = m_ifaceMap.find(in->MsgId().interfaceId);
        if(it == m_ifaceMap.end())
        {
            return Interface::InterfaceNotImpl;
        }
        Interface *iface = it->second;

        tss_state.m_src = in->Hdr().src;
        tss_state.m_src.instance = MESS_ToInst(tss_state.m_src.instance);
        ret = iface->Invoke(in->MsgId().methodId, sock, in);
    }
    else
    {
        // Response or timeout received
        int msgId = 0;
        
        if (in)
        {
            msgId = in->MsgId().msgId;
            if (in->Hdr().code == CODE_SUCCESS)
            {
                tss_state.m_state = MESS_STATUS_SUCCESS;
            }
            else if (in->Hdr().code == CODE_INVALID_MESSAGE)
            {
                tss_state.m_state = MESS_STATUS_UNHANDLED;
            }
            else
            {
                tss_state.m_state = MESS_STATUS_ERROR;
            }
            tss_state.m_src = in->Hdr().src; 
        }
        else
        {
            // timeout message or a bounce occurred
            EACC_ASSERT(req);
            msgId = req->MsgId().msgId;
            tss_state.m_state = code;

            // Put the destionation as the the source endpoint for the timeout
            tss_state.m_src = req->Dest();
        }
        tss_state.m_src.instance = MESS_ToInst(tss_state.m_src.instance);
        
        // Multicast messages may not have the corresponding req, 
        // so they cannot have cookies as of now
        if (req)
        {
            tss_state.m_cookie = req->Cookie();
        }
                
        MethodBase *method = m_respMap[msgId];
        if (method)
        {
            ret = method->Invoke(sock, in);
        }
        else
        {
            CLOG_ERROR("Method %x not implemented. Response cbk failed", msgId);
        }
    }
    
    return ret;
}

void MeSS::RegisterInterface(Interface *iface)
{
    std::pair<IfMap::iterator, bool> ret;
    ret = m_ifaceMap.insert(std::pair<unsigned, Interface*>(iface->InterfaceId(), iface));
    if (ret.second == false)
    {
        std::stringstream out;
        out << "Interface " << iface->InterfaceId() << " already registered";        
        throw MeSSExceptionLog(Logger::EACC_LOG_CRITICAL, out.str().c_str());
    }
    iface->RegisterMethods();
}

void MeSS::RegisterRespHandler(const MessageId &msgId, const MethodBase &cbk)
{
    std::pair<RespMap::iterator, bool> ret;
    ret = m_respMap.insert(std::pair<unsigned, MethodBase*>(msgId.msgId, cbk.Duplicate()));
    if (ret.second == false)
    {
        std::stringstream out;
        out << "Response Handler " << msgId.interfaceId << ":" << msgId.methodId << " already registered";        
        throw MeSSExceptionLog(Logger::EACC_LOG_CRITICAL, out.str().c_str());
    }
}

MeSSConnection* MeSS::Lookup(const MeSSEndpoint &dest)
{
    MeSSConnection *conn;
    Mutex::ScopedMutex guard(m_connMapLock);

    ConnMap::iterator it = m_connMap.find(METoInt(dest));
    if (it == m_connMap.end())
    {
        // Connection not present
        conn = new MeSSConnection(m_self);
        m_connMap.insert(std::pair<unsigned, MeSSConnection*>(METoInt(dest), conn));

        // conn->Connect(dest);
        CLOG_INFO("Inserted new connection to cache for dest 0x%x", METoInt(dest));
    }
    else
    {
        conn = it->second;
    }
    CLOG_DEBUG("Fetched connection %p", conn);
    
    return conn;
}

void MeSS::OnMeSSConnNew(MeSSConnection *conn)
{
    Mutex::ScopedMutex guard(m_connMapLock);

    // Passive connection added. Add this also to the connection map
    ConnMap::iterator it = m_connMap.find(METoInt(conn->Dest()));
    if (it == m_connMap.end())
    {
        // None existing add the new connection
        m_connMap.insert(std::pair<unsigned, MeSSConnection*>
                            (METoInt(conn->Dest()), conn));
        CLOG_INFO("New server passive connection for dest 0x%x", 
                  METoInt(conn->Dest()));
    }
    else
    {
        // Already a connection is existing. 
        // TODO handle this scenario
        CLOG_WARNING("Connection already existing for dest 0x%x! Mem leak!",
                METoInt(conn->Dest()));
    }
}

void MeSS::OnMeSSConnClose(MeSSConnection *conn)
{
    Mutex::ScopedMutex guard(m_connMapLock);
    unsigned dest = METoInt(conn->Dest());

    ConnMap::iterator it = m_connMap.find(dest);
    if (it != m_connMap.end())
    {
        m_connMap.erase(it);
        CLOG_INFO("Connection %p closed for dest 0x%x", conn, dest); 
    }
    else
    {
        CLOG_ERROR("MeSS Connection doesn't exist for Destination 0x%x", METoInt(conn->Dest()));
    }
}



} // namespace eAccelero

