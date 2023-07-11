#include "Socket.h"

namespace eAccelero
{
IPAddress::IPAddress(const char *str)
{
    memset(m_buf, 0, MAX_SIZE);
    if (NULL == str)
        return;

    int retVal;
    if (NULL == strchr(str,':'))
    {
        m_family = AF_INET;
    }
    else
    {
        m_family = AF_INET6;
    }

    retVal = inet_pton(m_family, str, m_buf);
    if(retVal < 0)
    {
        throw SystemException("Conversion to network failed");
    }        
}

SocketAddrIn::SocketAddrIn(const IPAddress& ipAddr, unsigned short port, unsigned scopeId)
    : SockAddr(ipAddr.Family())
{
    if (this->Family() == AF_INET)
    {
        m_len = sizeof(struct sockaddr_in);
        SI()->sin_port = htons(port);
        memcpy(&(SI()->sin_addr), ipAddr.buf(), sizeof(in_addr));
    }
    else if (this->Family() == AF_INET6)
    {
        m_len = sizeof(struct sockaddr_in6);
        SI6()->sin6_port = htons(port);
        SI6()->sin6_scope_id = scopeId;
        memcpy(&(SI6()->sin6_addr), ipAddr.buf(), sizeof(in6_addr));
    }
    else
    {
        throw SocketException("Invalid IP family");
    }
}

std::ostream& operator<<(std::ostream &os, SocketAddrIn& sockIn)
{
    char buf[INET6_ADDRSTRLEN];
    IPAddress ipAddr;
    os << "<" << sockIn.GetIPAddr(ipAddr).ToString(buf)
       << "." << sockIn.Port() << ">";
    return os;
}

} // namespace eAccelero
