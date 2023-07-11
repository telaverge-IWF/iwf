#ifndef __EACC_Tipc_h__
#define __EACC_Tipc_h__

#include "Socket.h"
#include <linux/tipc.h>

namespace eAccelero
{

class TIPCAddr;
std::ostream& operator << (std::ostream &os, TIPCAddr& addr);

// To use with socket APIs derive from SockAddr
class TIPCAddr: public SockAddr
{
 public:
    TIPCAddr(signed char scope = TIPC_NODE_SCOPE)
        : SockAddr(AF_TIPC)
    {
        // scope can be TIPC_ZONE_SCOPE, TIPC_CLUSTER_SCOPE or TIPC_NODE_SCOPE
        TA()->scope = scope;
    }

    TIPCAddr(struct sockaddr_tipc &rhs)
    {
        memcpy(m_buf, &rhs, sizeof(sockaddr_tipc));
    }

    // Address Type can be the following
    // TIPC_ADDR_NAMESEQ, TIPC_ADDR_MCAST, TIPC_ADDR_NAME, TIPC_ADDR_ID
    unsigned char& AddrType()
    {
        return TA()->addrtype;
    }
    signed char& Scope()
    {
        return TA()->scope;
    }
    operator struct sockaddr_tipc*()
    {
        return (struct sockaddr_tipc*)m_buf;
    }
    struct sockaddr_tipc* operator ->()
    {
        return (struct sockaddr_tipc*)m_buf;
    }

    // User defined types start with TIPC_RESERVED_TYPES+1
    void SetNameSeq(uint32_t type, uint32_t lower, uint32_t upper)
    {
        TA()->addrtype = TIPC_ADDR_NAMESEQ;
        TA()->addr.nameseq.type = type;
        TA()->addr.nameseq.lower = lower;
        TA()->addr.nameseq.upper = upper;
    }

    void SetName(uint32_t type, uint32_t instance = 1, uint32_t domain = 0)
    {
        TA()->addrtype = TIPC_ADDR_NAME;
        TA()->addr.name.name.type = type;
        TA()->addr.name.name.instance = instance;
        TA()->addr.name.domain = 0;
    }

    void SetID(uint32_t node, uint32_t ref)
    {
        TA()->addrtype = TIPC_ADDR_ID;
        TA()->addr.id.node = node;
        TA()->addr.id.ref = ref;
    }

    friend std::ostream& operator << (std::ostream &os, TIPCAddr& addr);

 protected:
    struct sockaddr_tipc* TA()
    {
        return &m_tipcAddr;
    }
};
class TIPCSubscr;
std::ostream& operator << (std::ostream &os, TIPCSubscr& addr);

class TIPCSubscr
{
 public:
    TIPCSubscr()
    {
        memset(&m_subscr, 0, sizeof(m_subscr));
    }

    // Filter can be
    //   TIPC_SUB_PORTS - filter for port availability
    //   TIPC_SUB_SERVICE - filter for service availability
    //   TIPC_SUB_CANCEL - cancel a subscription
    TIPCSubscr(uint32_t type, uint32_t lower, uint32_t upper,
               uint32_t filter = TIPC_SUB_PORTS,
               uint32_t msTimeout =  TIPC_WAIT_FOREVER)
    {
        memset(&m_subscr, 0, sizeof(m_subscr));
        m_subscr.seq.type = htonl(type);
        m_subscr.seq.lower = htonl(lower);
        m_subscr.seq.upper = htonl(upper);
        m_subscr.timeout = htonl(msTimeout);
        m_subscr.filter = htonl(filter);
    }

    TIPCSubscr(struct sockaddr_tipc *addr,
               uint32_t filter = TIPC_SUB_PORTS,
               uint32_t msTimeout =  TIPC_WAIT_FOREVER)
    {
        memset(&m_subscr, 0, sizeof(m_subscr));
        m_subscr.seq.type = htonl(addr->addr.nameseq.type);
        m_subscr.seq.lower = htonl(addr->addr.nameseq.lower);
        m_subscr.seq.upper = htonl(addr->addr.nameseq.upper);
        m_subscr.timeout = htonl(msTimeout);
        m_subscr.filter = htonl(filter);
    }

    TIPCSubscr(const struct tipc_subscr* subscr)
    {
        memcpy(&m_subscr, subscr, sizeof(m_subscr));
    }

    void SetUserHandle(void *cookie)
    {
        // To avoid strict aliasing rules
        memcpy(m_subscr.usr_handle, &cookie, sizeof(void*));
    }
    void* GetUserHandle()
    {
        return (void*)(*((unsigned long*)m_subscr.usr_handle));
        //return (void*)((m_subscr.usr_handle));
    }

    const uint32_t Type() const
    {
        return ntohl(m_subscr.seq.type);
    }
    const uint32_t Lower() const
    {
        return ntohl(m_subscr.seq.lower);
    }
    const uint32_t Upper() const
    {
        return ntohl(m_subscr.seq.upper);
    }
    const uint32_t Filter() const
    {
        return ntohl(m_subscr.filter);
    }
    void Filter(unsigned filt)
    {
        m_subscr.filter = htonl(filt);
    }

    operator struct tipc_subscr*()
    {
        return &m_subscr;
    }
    operator const struct tipc_subscr*() const
    {
        return &m_subscr;
    }

    friend std::ostream& operator << (std::ostream &os, TIPCSubscr& addr);
 protected:
    struct tipc_subscr m_subscr;
};

class TIPCEvent;
std::ostream& operator << (std::ostream &os, TIPCEvent& event);

class TIPCEvent
{
 public:
    TIPCEvent()
    {
    }

    operator struct tipc_event*()
    {
        return &m_event;
    }

    TIPCSubscr Subscr()
    {
        return TIPCSubscr(&m_event.s);
    }

    const uint32_t Event() const
    {
        return ntohl(m_event.event);
    }
    const uint32_t Lower() const
    {
        return ntohl(m_event.found_lower);
    }
    const uint32_t Upper() const
    {
        return ntohl(m_event.found_upper);
    }

    TIPCAddr Port()
    {
        TIPCAddr addr;
        addr.SetID(ntohl(m_event.port.node), ntohl(m_event.port.ref));
        return addr;
    }

 protected:
    struct tipc_event m_event;
};

// TIPC socket wrappers
class TIPCSock:public Socket
{
 public:
    // sockType can be SOCK_DGRAM, SOCK_STREAM, SOCK_SEQPACKET
    // or SOCK_RDM
    TIPCSock(int sockType)
        : Socket(AF_TIPC, sockType, 0)
    {
    }
    TIPCSock()
        : Socket(Socket::INVALID_FD)
    {
    }
    ~TIPCSock()
    {
    }

    // Receive with ancillary data
    int RecvAnc(void *buffer, int buf_len, uint32_t flags = 0,
                    TIPCAddr *fromAddr = NULL);

    // options can be TIPC_CONN_TIMEOUT, TIPC_DEST_DROPPABLE, TIPC_IMPORTANCE,
    //  TIPC_SRC_DROPPABLE
    void SetTIPCOption(int opt, unsigned val)
    {
        this->SetOption(SOL_TIPC, opt, (void*)&val, sizeof(unsigned));
    }

    unsigned GetTIPCOption(int opt)
    {
        unsigned val = 0;
        int valLen = sizeof(val);
        this->GetOption(SOL_TIPC, opt, (void*)&val, valLen);
        return val;
    }

};

} // namespace eAccelero

#endif // __EACC_Tipc_h__
