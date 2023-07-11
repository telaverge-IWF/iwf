#ifndef __EACC_SctpSocket_h__
#define __EACC_SctpSocket_h__

#include <vector>
#include <string.h>
#include "SctpDefs.h"
#include "Socket.h"

namespace eAccelero
{

static const int SCTP_MAX_ADDR = 8;

class SctpSock;

class SockAddrArray
{
 public:
    SockAddrArray()
        : m_size(),
          m_count()
    {
        memset(m_buff, 0, sizeof(m_buff));
    }

    SockAddrArray& Add(const SocketAddrIn& addr)
    {
        memcpy(m_buff + m_size, (const struct sockaddr*)addr, addr.len());
        m_size += addr.len();
        m_count++;
        return *this;
    }

    void Remove(const SocketAddrIn& addr)
    {
        // TODO
    }

    unsigned GetNext(SocketAddrIn& addr, unsigned size = 0) const;

    unsigned Size() const
    {
        return m_size;
    }
    unsigned Count() const
    {
        return m_count;
    }

    const void* Buffer() const
    {
        return m_buff;
    }

 protected:
    uint8_t m_buff[SCTP_MAX_ADDR * sizeof(sockaddr_in6)];
    uint16_t m_size;
    uint16_t m_count;

    friend class SctpSock;
};

class SctpNotificationHandler
{
 public:
    virtual ~SctpNotificationHandler()
    {
    }
    virtual void OnAssociationChange(sctp_assoc_change& event)
    {
    }
    virtual void OnPeerAddrChange(sctp_paddr_change& event)
    {
    }
    virtual void OnSendFailed(sctp_remote_error& event)
    {
    }
    virtual void OnRemoteError(sctp_send_failed& event)
    {
    }
    virtual void OnSctpShutdown(sctp_shutdown_event& event)
    {
    }
    virtual void OnPartialDelivery(sctp_pdapi_event& event)
    {
    }
    virtual void OnAdaptationIndication(sctp_adaptation_event& event)
    {
    }
    virtual void OnSctpAuthIndication(sctp_authkey_event& event)
    {
    }
    virtual void OnSenderDry(sctp_sender_dry_event& event)
    {
    }
};


class SctpSock: public Socket
{
 public:

    // type mostly will be SOCK_SEQPACKET
    SctpSock(int domain, int type)
        : Socket(domain, type, IPPROTO_SCTP),
          m_notifyHandler(NULL)
    {
    }

    explicit SctpSock(int sockFD =  INVALID_FD)
        : Socket(sockFD),
          m_notifyHandler(NULL)
    {
    }

    ~SctpSock()
    {
        // Doesn't own the notify handler
    }

    int SetSctpOption(int optName, const void* val, const int szVal)
    {
        return SetOption(SOL_SCTP, optName, val, szVal);
    }
    void GetSctpOption(int optName, void* val, int& len)
    {
        GetOption(SOL_SCTP, optName, val, len);
    }

    void Bindx(const SockAddrArray& addrs)
    {
        SetSctpOption(SCTP_SOCKOPT_BINDX_ADD, addrs.Buffer(), addrs.Size());
    }

    void Unbindx(const SockAddrArray& addrs)
    {
        SetSctpOption(SCTP_SOCKOPT_BINDX_REM, addrs.Buffer(), addrs.Size());
    }

    int Connectx(const SockAddrArray& addrs, int *id = NULL);

    int PeelOff(int assocId)
    {
        sctp_peeloff_arg_t arg;
        int sz = sizeof(arg);

        arg.associd = assocId;
        arg.sd = 0;
        GetSctpOption(SCTP_SOCKOPT_PEELOFF, (void*)&arg, sz);

        return arg.sd;
    }

    unsigned GetLocalAddrs(SockAddrArray& addrs, int assocId = 0)
    {
        return GetAddrs(SCTP_GET_LOCAL_ADDRS, addrs, assocId);
    }

    unsigned GetPeerAddrs(SockAddrArray& addrs, int assocId = 0)
    {
        return GetAddrs(SCTP_GET_PEER_ADDRS, addrs, assocId);
    }

    static const uint16_t DEFAULT_OUT_STREAMS = 1;
    static const uint16_t DEFAULT_IN_STREAMS = 1;
    static const uint16_t DEFAULT_INIT_ATTEMPTS = 6;
    static const uint16_t DEFAULT_INIT_TIMEOUT = 30000;

    void SetInitMsgParams(uint16_t maxOutStreams = DEFAULT_OUT_STREAMS,
                          uint16_t maxInStreams = DEFAULT_IN_STREAMS,
                          uint16_t maxInitAttempts = DEFAULT_INIT_ATTEMPTS,
                          uint16_t maxInitTimeout = DEFAULT_INIT_TIMEOUT)
    {
        sctp_initmsg initMsg = { maxOutStreams, maxInStreams, 
                                 maxInitAttempts, maxInitTimeout };
        SetSctpOption(SCTP_INITMSG, &initMsg, sizeof(initMsg));
    }
    void GetInitMsgParams(sctp_initmsg& initMsg)
    {
        int len = sizeof(initMsg);
        GetSctpOption(SCTP_INITMSG, (void*)&initMsg, len);
    }
    void GetInitMsgParams(uint16_t& maxOutStreams, uint16_t& maxInStreams,
                          uint16_t& maxInitAttempts, uint16_t& maxInitTimeout)
    {
        sctp_initmsg initMsg = {0};
        GetInitMsgParams(initMsg);
        maxOutStreams = initMsg.sinit_num_ostreams;
        maxInStreams = initMsg.sinit_max_instreams;
        maxInitAttempts = initMsg.sinit_max_attempts;
        maxInitTimeout = initMsg.sinit_max_init_timeo;
    }

    enum SctpEvents
    {
        EVENT_DATA_IO = 1,
        EVENT_ASSOCIATION_CHANGE = (1 << 1),
        EVENT_PEER_ADDR_CHANGE = (1 << 2),
        EVENT_SEND_FAILED = (1 << 3),
        EVENT_REMOTE_ERROR = (1 << 4),
        EVENT_SHUTDOWN = (1 << 5),
        EVENT_PARTIAL_DELIVERY = (1 << 6),
        EVENT_ADAPTATION_INDICATION = (1 << 7),
        EVENT_AUTH_INDICATION = (1 << 8),
        EVENT_SENDER_DRY = (1 << 9),

        EVENT_ALL = ((EVENT_SENDER_DRY << 1) - 1)
    };

    void RegisterNotifications(uint32_t events, SctpNotificationHandler *handler);

    int Recvx(void *msg, const int &msgLen, int& flags, struct sctp_sndrcvinfo& sinfo);

    int Sendx(void *msg, const int &msgLen, int flags, 
              const struct sctp_sndrcvinfo& sinfo);

 protected:

    void HandleNotification(sctp_notification& event);

    // both SOL_SCTP and IPPROTO_SCTP are the same in Linux
#if 0
    int SetSctpProtoOption(int optName, const void* val, const int szVal)
    {
        return SetOption(IPPROTO_SCTP, optName, val, szVal);
    }
    void GetSctpProtoOption(int optName, const void* val, int& len)
    {
        GetOption(IPPROTO_SCTP, optName, val, len);
    }
#endif

    unsigned GetAddrs(int opt, SockAddrArray& addrs, int assocId);

    SctpNotificationHandler* m_notifyHandler;
};

#if 0
class SctpAssoc
{
 public:
    SctpAssoc(const SctpSock& sock, int assocId)
        : m_sock(sock),
          m_assocId(assocId),
          m_closed(false)
    {
    }
    ~SctpAssoc()
    {
        if (!m_closed)
        {
            // Socket not owned by me
            this->Close();
        }
        m_sock.Release();
    }

    int Send(void *msg, int msgLen, uint16_t flags = 0, 
             uint16_t streamNo = 0, uint32_t ppid = 0)
    {
        struct sctp_sndrcvinfo sinfo;
        memset(&sinfo, 0, sizeof(struct sctp_sndrcvinfo));
        sinfo.sinfo_flags = flags;
        sinfo.sinfo_stream = streamNo;
        sinfo.sinfo_assoc_id = m_assocId;
        sinfo.sinfo_ppid = htonl(ppid);

        return m_sock.Sendx(msg, msgLen, 0, sinfo);
    }

    void OnRead(void *msg, int msgLen)
    {
    }

    void Close()
    {
        this->Send(NULL, 0, SCTP_EOF);
        // Send with SCTP_EOF flag
    }

    void Abort()
    {
        this->Send(NULL, 0, SCTP_ABORT);
    }

    void SetClosed(bool closed = true)
    {
        m_closed = closed;
    }
    

 protected:
    SctpSock m_sock;
    int m_assocId;
    bool m_closed; // TODO change this as state
};
#endif

}

std::ostream& operator << (std::ostream& os, const eAccelero::SockAddrArray& addrArray);

#endif // __EACC_Socket_h__
