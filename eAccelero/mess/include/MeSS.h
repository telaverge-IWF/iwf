#ifndef __EACC_MeSS_h__
#define __EACC_MeSS_h__

#include "Component.h"
#include <unordered_map>
#include <sstream>
#include "TopSrv.h"
#include "MeSSage.h"
#include "MemPool.h"
#include "Transceiver.h"
#include "Interface.h"
#include "Thread.h"

#include "google/protobuf/message.h"

namespace eAccelero
{

class MeSSComponent;
    
enum MessageStatus
{
    MESS_STATUS_SUCCESS,
    MESS_STATUS_ERROR,      // Generic error
    MESS_STATUS_TIMEOUT,    // Message Timedout
    MESS_STATUS_UNHANDLED,  // Message not handled at the peer
    MESS_STATUS_BOUNCE,     // The peer is not up
    MESS_STATUS_NOT_READY,  // MeSS not ready, rebind in progress
};

struct MeSSHandle
{
    MeSSEndpoint   m_src;
    MessageStatus  m_state;
    void    *m_cookie;
};

// Should be only one per component
class MeSS: public Subcomponent
{
 public:
    enum Flags
    {
        RDM_DELIVERY = 1,       // 1
        SEQ_DELIVERY = (1<<1),  // 2
        DGM_DELIVERY = (1<<2),  // 4
        BLOCK_FOR_RESP  = (1<<3),  // 8
    };
    enum
    {
        REQ_EXPIRY_TIME = 30000, // 30 secs
        INVALID_IDX = 0xFFFFFFFF
    };
    
    MeSS(MeSSComponent& comp);
    ~MeSS();

    void Initialize();

    void Terminate();

    unsigned Send(const MeSSEndpoint &dest, const MessageId &msgId, void *payload,
                unsigned len, void *cookie = NULL, unsigned flags = RDM_DELIVERY);

    unsigned Send(const MeSSEndpoint &dest, const MessageId &msgId, 
                const google::protobuf::Message& msg,
                void *cookie = NULL, unsigned flags = RDM_DELIVERY);

    int Dispatch(Transceiver *sock, MeSSage *in, MeSSage *req,
                    MessageStatus code = MESS_STATUS_SUCCESS);
    
    void RegisterInterface(Interface *iface);
    
    void RegisterRespHandler(const MessageId &msgId, const MethodBase &cbk);
    
    int OnSeqSockEvent(SockEvent &ev);
    
    void Rebind(MeSSEndpoint &meSSEndpoint, bool immediate = false);
    
    TopologyService& TopSvc()
    {
        return m_topSvc;
    }
    
    MemPool& Pool()
    {
        return m_pool;
    }

    static MeSS& MeSSObj()
    {
        return *m_messObj;
    }
    
    MeSSEndpoint& Self()
    {
        return m_self;
    }
    
    static MeSSHandle& Handle()
    {
        return tss_state;
    }

	// Not used yet
    const pthread_t& MeSSThread() const
    {
        return m_messThreadId;
    }
    pthread_t& MeSSThread()
    {
        return m_messThreadId;
    }

    MeSSConnection* Lookup(const MeSSEndpoint &dest);

    void OnMeSSConnNew(MeSSConnection *conn);

    void OnMeSSConnClose(MeSSConnection *conn);

    bool IsRebindPending()
    {
        return m_rebindPending;
    }

    void DeferredRebind();

    unsigned SelfNodeId()
    {
        return m_selfNodeId;
    }

 protected:

    // Bind to lthe current instance and compId
    // Old binding will be removed
    void Bind();

    void CleanupSocks();

    MeSSComponent &m_comp;
    // TODO Should instance be part of Component/Subcomponent

    MeSSEndpoint m_self;
    unsigned m_selfNodeId;

    // Topology service event
    TopologyService m_topSvc;

    // Socket for connection oriented sequential packet delivery TODO
    TIPCSock  *m_seqSock;
    EventHandlerId m_seqSockEvH;

    Transceiver *m_rdmSock;
    Transceiver *m_dgmSock;
    
    typedef std::unordered_map<unsigned, MeSSConnection*> ConnMap;
    ConnMap m_connMap;
    Mutex   m_connMapLock;
    
    typedef std::unordered_map<unsigned, Interface*> IfMap;
    IfMap m_ifaceMap;
    
    typedef std::unordered_map<unsigned, MethodBase*> RespMap;
    RespMap m_respMap;
    
    // Allocate memory using mempool
    MemPool m_pool;

    pthread_t m_messThreadId;

    // Rebind related
    bool m_rebindPending;
    MeSSEndpoint m_newEndpoint;
    RWLock m_rebindLock;

    struct CmdArgs
    {
        CmdArgs()
            : instance("i", "--inst", "Instance of the MeSS Component", true)
        {
        }
        CmdOption<int> instance;
    }m_cmdArgs;
    
    static MeSS *m_messObj;
    
    static __thread MeSSHandle tss_state;
};

} // namespace eAccelero

#endif // __EACC_MeSS_h__
