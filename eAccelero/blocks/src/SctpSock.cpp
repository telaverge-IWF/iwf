
#include "SctpSock.h"

using namespace eAccelero;

unsigned SockAddrArray::GetNext(SocketAddrIn& addr, unsigned size) const
{
    if (size >= m_size)
    {
        return 0xFFFFFFFF;
    }
    const struct sockaddr* saAddr = (const struct sockaddr*)(m_buff + size);
    int len = 0;
    switch(saAddr->sa_family)
    {
        case AF_INET:
            len = sizeof(struct sockaddr_in);
            break;
        case AF_INET6:
            len = sizeof(struct sockaddr_in6);
            break;
        default:
            errno = EINVAL;
            return 0xFFFFFFFF;
    }
    memcpy((struct sockaddr*)addr, saAddr, len);
    addr.len() = len;

    return size + len;
}

std::ostream& operator << (std::ostream& os, const SockAddrArray& addrArray)
{
    bool first = true;
    unsigned size = 0;
    SocketAddrIn addr;
    while( (size = addrArray.GetNext(addr, size)) <= addrArray.Size())
    {
        if (!first) os << ", ";
        os << addr;
        first = false;
    }
    return os;
}

int SctpSock::Connectx(const SockAddrArray& addrs, int *id)
{
#if 0
    sctp_getaddrs_old param;
    int optLen = sizeof(param);

    param.assoc_id = 0;
    param.addr_num = addrs.Size();
    param.addrs = (sockaddr*)addrs.Buffer();

    int ret = SetSctpOption(SCTP_SOCKOPT_CONNECTX3, &param, optLen);
    
    *id = param.assoc_id;

    return ret;
#endif
    if (id) *id = 0;
    int ret = SetSctpOption(SCTP_SOCKOPT_CONNECTX, addrs.Buffer(), addrs.Size());

    if (ret > 0)
    {
        *id = ret;
        ret = 0;
    }
    return ret;
}

unsigned SctpSock::GetAddrs(int opt, SockAddrArray& addrs, int assocId)
{
    char buffer[1024];
    int len = 1024;
    struct sctp_getaddrs* getAddr = (struct sctp_getaddrs*)(buffer);
    getAddr->assoc_id = assocId;

    GetSctpOption(opt, getAddr, len);

    memcpy(addrs.m_buff, getAddr->addrs, len);
    addrs.m_size = len;
    addrs.m_count = getAddr->addr_num;

    return addrs.m_count;
}

void SctpSock::RegisterNotifications(uint32_t events, SctpNotificationHandler *handler)
{
    sctp_event_subscribe subEvents;
    memset(&subEvents, 0, sizeof(subEvents));
    
    if (events & EVENT_DATA_IO)
    {
        subEvents.sctp_data_io_event = 1;
    }
    if (events & EVENT_ASSOCIATION_CHANGE)
    {
        subEvents.sctp_association_event = 1;
    }
    if (events & EVENT_PEER_ADDR_CHANGE)
    {
        subEvents.sctp_address_event = 1;
    }
    if (events &EVENT_SEND_FAILED)
    {
        subEvents.sctp_send_failure_event = 1;
    }
    if (events & EVENT_REMOTE_ERROR)
    {
        subEvents.sctp_peer_error_event = 1;
    }
    if (events & EVENT_SHUTDOWN)
    {
        subEvents.sctp_shutdown_event = 1;
    }
    if (events & EVENT_PARTIAL_DELIVERY)
    {
        subEvents.sctp_partial_delivery_event = 1;
    }
    if (events & EVENT_ADAPTATION_INDICATION)
    {
        subEvents.sctp_adaptation_layer_event = 1;
    }
    if (events & EVENT_AUTH_INDICATION)
    {
        subEvents.sctp_authentication_event = 1;
    }
#if 0
    if (events & EVENT_SENDER_DRY)
    {
        subEvents.sctp_sender_dry_event = 1;
    }
#endif

    // TODO if there is an exception, we need to set the 
    // handler back to NULL
    m_notifyHandler = handler;
    SetSctpOption(SCTP_EVENTS, &subEvents, sizeof(subEvents));
}

int SctpSock::Recvx(void *msg, const int &msgLen, int& flags, 
                    struct sctp_sndrcvinfo& sinfo)
{
    if ((unsigned)msgLen < sizeof(sctp_notification))
    {
        throw SocketException("Larger buffer size expected to handle notifications");
    }

    char cbuf[sizeof(struct cmsghdr) + sizeof(struct sctp_sndrcvinfo)];
    struct cmsghdr* cmsg = (struct cmsghdr*)(cbuf);
    struct sctp_sndrcvinfo* sri = (struct sctp_sndrcvinfo*)(cmsg + 1);

    struct iovec vec;
    vec.iov_base = msg;
    vec.iov_len  = (socklen_t)msgLen;

    struct msghdr msgHdr;
    msgHdr.msg_name = NULL;
    msgHdr.msg_namelen = 0;
    msgHdr.msg_iov = &vec;
    msgHdr.msg_iovlen = 1;
    msgHdr.msg_control = cbuf;
    msgHdr.msg_controllen = sizeof(cbuf);
    msgHdr.msg_flags = flags;

    int nread = recvmsg(this->FD(), &msgHdr, flags);
    if (nread < 0)
    {
        flags = msgHdr.msg_flags;
        if (errno == EINTR || errno == EAGAIN)
        {
            return -1;
        }
        throw SocketException("Sctp Receive failed");
    }
    memcpy(&sinfo, sri, sizeof(struct sctp_sndrcvinfo));
    flags = msgHdr.msg_flags;
    if (flags & MSG_NOTIFICATION)
    {
        // it is a notification
        sctp_notification* event = (sctp_notification*)msg;
        this->HandleNotification(*event);
        return 0;
    }
    return nread;
}

int SctpSock::Sendx(void *msg, const int &msgLen, int flags, 
                    const struct sctp_sndrcvinfo& sinfo)
{
    char cbuf[CMSG_SPACE(sizeof(struct sctp_sndrcvinfo))];

    struct iovec vec;
    vec.iov_base = msg;
    vec.iov_len  = (socklen_t)msgLen;

    struct msghdr msgHdr;
    msgHdr.msg_name = NULL;
    msgHdr.msg_namelen = 0;
    msgHdr.msg_iov = &vec;
    msgHdr.msg_iovlen = 1;
    msgHdr.msg_control = cbuf;
    msgHdr.msg_controllen = CMSG_LEN(sizeof(struct sctp_sndrcvinfo));
    msgHdr.msg_flags = 0;

    struct cmsghdr* cmsg = CMSG_FIRSTHDR(&msgHdr);
    cmsg->cmsg_len = CMSG_LEN(sizeof(struct sctp_sndrcvinfo));
    cmsg->cmsg_level = IPPROTO_SCTP;
    cmsg->cmsg_type  = SCTP_SNDRCV;

    struct sctp_sndrcvinfo* sri = (struct sctp_sndrcvinfo*)CMSG_DATA(cmsg);
    memcpy(sri, &sinfo, sizeof(struct sctp_sndrcvinfo));

    int nwritten = sendmsg(this->FD(), &msgHdr, flags);
    if (nwritten < 0)
    {
        if (errno == EINTR || errno == EAGAIN)
        {
            return -1;
        }
        throw SocketException("Sctp Send failed");
    }

    return nwritten;
}

void SctpSock::HandleNotification(sctp_notification& event)
{
    if (m_notifyHandler == NULL)
    {
        // no handler... cannot notify!
        return;
    }
    switch(event.sn_header.sn_type)
    {
	    case SCTP_ASSOC_CHANGE:
        {
            m_notifyHandler->OnAssociationChange(event.sn_assoc_change);
            break;
        }
	    case SCTP_PEER_ADDR_CHANGE:
        {
            m_notifyHandler->OnPeerAddrChange(event.sn_paddr_change);
            break;
        }
	    case SCTP_SEND_FAILED:
        {
            m_notifyHandler->OnSendFailed(event.sn_remote_error);
            break;
        }
	    case SCTP_REMOTE_ERROR:
        {
            m_notifyHandler->OnRemoteError(event.sn_send_failed);
            break;
        }
	    case SCTP_SHUTDOWN_EVENT:
        {
            m_notifyHandler->OnSctpShutdown(event.sn_shutdown_event);
            break;
        }
	    case SCTP_PARTIAL_DELIVERY_EVENT:
        {
            m_notifyHandler->OnPartialDelivery(event.sn_pdapi_event);
            break;
        }
	    case SCTP_ADAPTATION_INDICATION:
        {
            m_notifyHandler->OnAdaptationIndication(event.sn_adaptation_event);
            break;
        }
	    case SCTP_AUTHENTICATION_INDICATION:
        {
            m_notifyHandler->OnSctpAuthIndication(event.sn_authkey_event);
            break;
        }
	    case SCTP_SENDER_DRY_EVENT:
        {
            // not supported now
            m_notifyHandler->OnSenderDry(event.sn_sender_dry_event);
        }
    }
}

