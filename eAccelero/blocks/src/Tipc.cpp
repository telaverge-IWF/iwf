#include "Tipc.h"

namespace eAccelero
{

std::ostream& operator << (std::ostream &os, TIPCAddr& addr)
{
    switch(addr.AddrType())
    {
        case TIPC_ADDR_NAMESEQ:
            os << "{" << addr.TA()->addr.nameseq.type << ", "
                      << addr.TA()->addr.nameseq.lower << "-"
                      << addr.TA()->addr.nameseq.upper << "}";
            break;
        case TIPC_ADDR_NAME:
            os << "{" << addr.TA()->addr.name.name.type << ", "
                      << addr.TA()->addr.name.name.instance << "}";
            break;
        case TIPC_ADDR_ID:
            os << "<" << tipc_zone(addr.TA()->addr.id.node) << "."
                      << tipc_cluster(addr.TA()->addr.id.node) << "."
                      << tipc_node(addr.TA()->addr.id.node) << ":"
                      << addr.TA()->addr.id.ref << ">";
            break;
    }

    return os;
}

std::ostream& operator << (std::ostream &os, TIPCSubscr& addr)
{
    os << "[Seq = {" << addr.Type() << ", "
       << addr.Lower() << "-"  << addr.Upper() << "} "
       << "Timeout = " << ntohl(addr.m_subscr.timeout) << "ms"
       << " filter = " << addr.Filter() << "]";
    return os;
}

std::ostream& operator << (std::ostream &os, TIPCEvent& event)
{
    TIPCAddr addr = event.Port();
    TIPCSubscr sub = event.Subscr();
    os << "<< event = " << event.Event() << ", {" << event.Lower() << "," 
       << event.Upper() << "}, " << addr << " " << sub << " >>";
    return os;
}

int TIPCSock::RecvAnc(void *buf, int buf_len, 
                uint32_t flags, TIPCAddr *fromaddr)
{
	struct msghdr msg;
	struct iovec iov;
	char anc_buf[CMSG_SPACE(8) + CMSG_SPACE(1024) + CMSG_SPACE(12)];
	struct cmsghdr *anc;
	unsigned char *cptr;
	__u32 *iptr;
	ssize_t sz;
    int i;

	iov.iov_base = buf;
	iov.iov_len = buf_len;

	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_name = (struct sockaddr_tipc*)(*fromaddr);
	msg.msg_namelen = (fromaddr) ? sizeof(struct sockaddr_tipc) : 0;
	msg.msg_control = anc_buf;
	msg.msg_controllen = sizeof(anc_buf);

	sz = recvmsg(m_fd, &msg, flags);
	if (sz >= 0) {
		anc = CMSG_FIRSTHDR(&msg);
		while (anc != NULL) {
			cptr = CMSG_DATA(anc);

			if (anc->cmsg_type == TIPC_ERRINFO) {
                socklen_t optlen;
				iptr = (__u32 *)cptr;
				printf("error code = %u, data size = %u bytes\n",
				       iptr[0], iptr[1]);
                // Error codes can be
                // TIPC_OK			    0
                // TIPC_ERR_NO_NAME	    1
                // TIPC_ERR_NO_PORT	    2
                // TIPC_ERR_NO_NODE	    3
                // TIPC_ERR_OVERLOAD	4
                // TIPC_CONN_SHUTDOWN	5
				/*
				 * provide the same return code value 
				 * that TIPC's recv() and recvfrom() generate
				 */
                i = -1;
				optlen = sizeof(i);
				getsockopt(m_fd, SOL_SOCKET, SO_TYPE, &i, &optlen);
				if (((i == SOCK_SEQPACKET) || (i == SOCK_STREAM))
				    && (iptr[0] != TIPC_CONN_SHUTDOWN))
                {
					sz = -1;
                }
			} else if (anc->cmsg_type == TIPC_RETDATA) {
				for (i = anc->cmsg_len - sizeof(*anc); i > 0; i--) {
					printf("returned byte 0x%02x\n", *cptr);
					cptr++;
				}
			} else if (anc->cmsg_type == TIPC_DESTNAME) {
				iptr = (__u32 *)cptr;
				//printf("destination name = {%u,%u,%u}\n",
				//       iptr[0], iptr[1], iptr[2]);
			} else {
				printf("unrecognized ancillary data type %u\n",
				       anc->cmsg_type);
			}

			anc = CMSG_NXTHDR(&msg, anc);
		}
	}
    else
    {
        if (errno != EAGAIN && errno != EINTR)
        {
            throw SocketException("TIPC recvmsg failed");
        }
    }

	return sz;
}

#if 0
int TIPCSock::Send(void *buffer, int buf_len, uint32_t flags, 
                TIPCAddr *toAddr)
{
    int ret = 0;
	struct msghdr msg;
    struct iovec iov = { buffer, buf_len };

	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_name = (struct sockaddr_tipc*)(*toAddr);
	msg.msg_namelen = (toAddr) ? sizeof(struct sockaddr_tipc) : 0;
	msg.msg_control = NULL;
	msg.msg_controllen = 0;

    ret = sendmsg(m_fd, &msg, flags);
    if (ret < 0)
    {
        if (errno != EAGAIN && errno != EINTR)
        {
            throw TIPC_ERROR("Sendmsg error");
        }
    }

    return ret;
}
#endif

} //namespace eAccelero
