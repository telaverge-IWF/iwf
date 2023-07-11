
#ifndef __EACC_Socket_h__
#define __EACC_Socket_h__

#include<unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <string.h>
#include <sys/un.h>
#include <linux/tipc.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fcntl.h>

#include "Exception.h"

namespace eAccelero
{
EACC_DEFINE_EXCEPTION_CLASS(SocketException, Exception, "Socket Exception")
#define SocketExceptionLog(...) GEN_EXCEPTION_LOG(eAccelero::SocketException, ##__VA_ARGS__)

// Allows families for AF_INET, AF_INET6 and AF_TIPC
class SockAddr
{
 public:
    enum
    {
        MAX_SIZE = sizeof(struct sockaddr_in6),
    };
    SockAddr()
        : m_len(sizeof(struct sockaddr))
    {
        memset(m_buf, 0, MAX_SIZE);
    }
    SockAddr(const SockAddr& rhs)
        : m_len(rhs.m_len) 
    {
        memcpy(m_buf, rhs.m_buf, MAX_SIZE);
    }
    SockAddr& operator =(const SockAddr &rhs)
    {
        if (this != &rhs)
        {
            m_len = rhs.m_len;
            memcpy(m_buf, rhs.m_buf, MAX_SIZE);
        }
        return *this;
    }

    operator struct sockaddr*()
    {
        return SA();
    }
    operator const struct sockaddr*() const
    {
        return (const struct sockaddr*)(&m_addr);
    }

    int Family()
    {
        return SA()->sa_family;
    }

    const int& len() const
    {
        return m_len;
    }

    int& len()
    {
        return m_len;
    }

 protected:
    SockAddr(sa_family_t family)
        : m_len(sizeof(struct sockaddr))
    {
        SA()->sa_family = family;
    }
    struct sockaddr* SA()
    {
        return &m_addr;
    }
    int m_len;

    // Too instuct the compiler to relax strict aliasing rules
    union
    {
        unsigned char m_buf[MAX_SIZE];
        struct sockaddr m_addr;
        struct sockaddr_tipc m_tipcAddr;
    };
};

class IPAddress
{
 public:
    enum
    {
        MAX_SIZE = sizeof(struct in6_addr),
    };
    IPAddress(const char *str = NULL);

    IPAddress(const struct in_addr& ipv4)
    {
        memset(m_buf, 0, MAX_SIZE);
        m_family = AF_INET;
        memcpy(m_buf, &ipv4, sizeof(struct in_addr));
    }
    IPAddress(const struct in6_addr& ipv6)
    {
        memset(m_buf, 0, MAX_SIZE);
        m_family = AF_INET6;
        memcpy(m_buf, &ipv6, sizeof(struct in6_addr));
    }
    IPAddress(const IPAddress& rhs)
        : m_family(rhs.m_family)
    {
        memcpy(m_buf, rhs.m_buf, MAX_SIZE);
    }

    IPAddress& operator=(const IPAddress& rhs)
    {
        if (this != &rhs)
        {
            m_family = rhs.m_family;
            memcpy(m_buf, rhs.m_buf, MAX_SIZE);
        }
        return *this;
    }

    const sa_family_t Family() const
    {
        return m_family;
    }

    const char *ToString(char *buf, int len = INET6_ADDRSTRLEN)
    {
        const char* retVal = inet_ntop(m_family, m_buf,
                buf, len);
        if (NULL == retVal)
        {
            throw SystemException("Failed convert IP to string");
        }

        return retVal;        
    }

    unsigned char *buf()
    {
        return m_buf;
    }
    const unsigned char *buf() const
    {
        return m_buf;
    }

 private:
    sa_family_t   m_family;
    unsigned char m_buf[MAX_SIZE];
};

class SocketAddrIn;
std::ostream& operator<<(std::ostream &os, SocketAddrIn& sockIn);

class SocketAddrIn: public SockAddr
{
 public:
    SocketAddrIn()
    {
    }
    explicit SocketAddrIn(const struct sockaddr* addr)
    {
        memcpy(SA(), addr, this->len());
    }

    SocketAddrIn(const IPAddress& ipAddr, unsigned short port, unsigned scopeId = 0);

    unsigned short Port()
    {
        // assuming that for both Ipv6 and ipv4 port is at same location
        return ntohs(SI()->sin_port);
    }

    IPAddress& GetIPAddr(IPAddress &ip)
    {
        if (this->Family() == AF_INET)
        {
            ip = IPAddress(SI()->sin_addr);
        }
        else if (this->Family() == AF_INET6)
        {
            ip = IPAddress(SI6()->sin6_addr);
        }
        else
        {
            throw SocketException("Invalid IP family");
        }

        return ip;
    }

    friend std::ostream& operator<<(std::ostream &os, SocketAddrIn& sockIn);
 private:
    struct sockaddr_in* SI()
    {
        return (struct sockaddr_in*)(m_buf);
    }
    struct sockaddr_in6* SI6()
    {
        return (struct sockaddr_in6*)(m_buf);
    }
};

// Wrapper around the socket FD
class Socket
{
 public:
    enum
    {
        INVALID_FD = -1,
        DEFAULT_LISTEN_BACKLOG = 10,
    };
 	explicit Socket(int sockFD = INVALID_FD)
        : m_fd(sockFD)
    {
    }
    // Flags can be SOCK_CLOEXEC, SOCK_NONBLOCK
	Socket(int domain, int type, int protocol=0, int flags = SOCK_CLOEXEC)
    {
        type |= flags;
        m_fd = socket(domain, type, protocol);
        if (m_fd < 0)
        {
            throw SocketException("SockOpen failed");
        }
    }
	Socket(const Socket& rhs)
        : m_fd(rhs.m_fd)
    {
    }

	~Socket()
    {
        if (m_fd != INVALID_FD)
        {
            close(m_fd);
        }
    }
	Socket& operator = (const Socket& rhs)
    {
        m_fd = rhs.m_fd;
        return *this;
    }

    // Don't close when getting destroyed
    int Release()
    {
        int ret = m_fd;
        m_fd = INVALID_FD;
        return ret;
    }
    int& FD()
    {
        return m_fd;
    }
    const int FD() const
    {
        return m_fd;
    }
    void Shutdown(int how = SHUT_RDWR)
    {
        int ret = shutdown(m_fd, how);
        if (ret < 0)
        {
            throw SocketException("Shutdown failed");
        }
    }
    void Close()
    {
        close(m_fd);
        m_fd = INVALID_FD;
    }
    void Bind(const SockAddr &addr)
    {
        int ret = bind(m_fd, addr, addr.len());
        if (ret < 0)
        {
            std::stringstream ss;
            ss << "Bind failure" << addr;
            throw SocketException(ss.str().c_str());
        }
    }
    void Bind(struct sockaddr* addr, socklen_t len)
    {
        int ret = bind(m_fd, addr, len);
        if (ret < 0)
        {
            std::stringstream ss;
            ss << "Bind failure" << addr;
            throw SocketException(ss.str().c_str());
        }
    }
    int Connect(const SockAddr &addr)
    {
        int ret = connect(m_fd, addr, addr.len());
        if (ret < 0 && 
            !(errno == EINPROGRESS || errno == EINTR || errno == EAGAIN))
        {
            throw SocketException("Connect failure");
        }
        return ret;
    }

    void Listen(int backlog = DEFAULT_LISTEN_BACKLOG)
    {
        int ret = listen(m_fd, backlog);
        if (ret < 0)
        {
            throw SocketException("Listen failure");
        }
    }
    // Flags can be SOCK_CLOEXEC, SOCK_NONBLOCK
    int Accept(SockAddr &addr, int flags = SOCK_CLOEXEC)
    {
        socklen_t len = SockAddr::MAX_SIZE;
        int ret = accept4(m_fd, addr, &len, flags);
        if (ret < 0)
        {
            throw SocketException("Accept failure");
        }
        return ret;
    }
    // Flags can be SOCK_CLOEXEC, SOCK_NONBLOCK
    int Accept(int flags = SOCK_CLOEXEC)
    {
        int ret = accept4(m_fd, NULL, NULL, flags);
        if (ret < 0)
        {
            throw SocketException("Accept failure");
        }
        return ret;
    }
    int Recv(void* msg, const int &msgLen,
		     int flags = 0)
    {
        int ret = recv(m_fd, msg, msgLen, flags);
        if (ret < 0 && (errno != EAGAIN && errno != EINTR))
        {
            throw SocketException("Recv failed");
        }
        return ret;
    }
    int Recv(SockAddr &addr, void* msg, const int &msgLen, int flags = 0)
    {
        socklen_t len = SockAddr::MAX_SIZE;
        int ret = recvfrom(m_fd, msg, msgLen, flags, addr, &len);
        if (ret < 0 && (errno != EAGAIN && errno != EINTR))
        {
            throw SocketException("Recv failed");
        }
        return ret;
    }
    int Send(void *msg, const int msgLen, int flags = 0)
    {
        int ret = send(m_fd, msg, msgLen, flags);
        if (ret < 0 && (errno != EAGAIN && errno != EINTR))
        {
            throw SocketException("Send failed");
        }
        return ret;
    }
    int Send(SockAddr &addr, void *msg, const int msgLen, int flags = 0)
    {
        int ret = sendto(m_fd, msg, msgLen, flags, addr, addr.len());
        if (ret < 0 && (errno != EAGAIN && errno != EINTR))
        {
            throw SocketException("Send failed");
        }
        return ret;
    }
    void GetPeerAddr(SockAddr &addr)
    {
        socklen_t len = SockAddr::MAX_SIZE;
        int ret = getpeername(m_fd, addr, &len);
        if (ret < 0)
        {
            throw SocketException("Get peername failed");
        }
    }
    void GetSockAddr(SockAddr &addr)
    {
        socklen_t len = SockAddr::MAX_SIZE;
        int ret = getsockname(m_fd, addr, &len);
        if (ret < 0)
        {
            throw SocketException("Get peername failed");
        }
    }
    void GetOption(int level, int optName, void *optVal, int &optLen)
    {
        int ret = getsockopt(m_fd, level, optName, optVal, (socklen_t*)&optLen);
        if (ret < 0)
        {
            throw SocketException("Get Sock Options failed");
        }
    }
    int SetOption(int level, int optName, const void *optVal, const int &optLen)
    {
        int ret = setsockopt(m_fd, level, optName, optVal, optLen);
        if (ret < 0 && 
            (errno != EINPROGRESS && errno != EAGAIN && errno != EINTR))
        {
            throw SocketException("Set Sock options failed");
        }
        return ret;
    }
    void SetNonBlocking(int enable)
    {
        // TODO Replace this with posix behavior "fcntl"
        int ret = ioctl(m_fd, FIONBIO, &enable);
        if (ret < 0)
        {
            throw SocketException("Set nonblocking IO failed");
        }
    }
    void SetCloseOnExec(bool enable)
    {
        int flags = enable ? FD_CLOEXEC : 0;

        int ret = fcntl(m_fd, F_SETFD, flags);
        if (ret < 0)
        {
            throw SocketException("Set Close on Exec failed");
        }
    }

    // Utility functions
    void SetSOLOption(int optName, int val)
    {
        SetOption(SOL_SOCKET, optName, (void*)&val, sizeof(val));
    }
    void GetSOLOption(int optName, int &val)
    {
        int len = sizeof(val);
        GetOption(SOL_SOCKET, optName, (void*)&val, len);
    }

    void SetReuseAddress(int enable)
    {
        SetSOLOption(SO_REUSEADDR, enable);
    }

    void SetSendBufSize(int bufSize)
    {
        SetSOLOption(SO_SNDBUF, bufSize);
    }
    int GetSendBufSize()
    {
        int size = 0;
        GetSOLOption(SO_SNDBUF, size);
        return size;
    }
    void SetRecvBufSize(int bufSize)
    {
        SetSOLOption(SO_RCVBUF, bufSize);
    }
    int GetRecvBufSize()
    {
        int size = 0;
        GetSOLOption(SO_RCVBUF, size);
        return size;
    }
    int GetError()
    {
        int err = 0;
        GetSOLOption(SO_ERROR, err);
        return err;
    }

 protected:
    int m_fd;
}; // class Socket

} // namespace eAccelero

#endif // __EACC_Socket_h__
