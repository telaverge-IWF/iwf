/*********************************-*-C++-*-************************************
 * *                                                                          *
 * *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 * *            Manufactured in the United States of America.                 *
 * *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 * *                                                                          *
 * *   This product and related documentation is protected by copyright and   *
 * *   distributed under licenses restricting its use, copying, distribution  *
 * *   and decompilation.  No part of this product or related documentation   *
 * *   may be reproduced in any form by any means without prior written       *
 * *   authorization of Diametriq and its licensors, if any.                  *
 * *                                                                          *
 * *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 * *   government is subject to restrictions as set forth in subparagraph     *
 * *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 * *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 * *                                                                          *
 * ****************************************************************************/

#include <stdint.h>
#include <stdlib.h>
#include <string>
#include "AlarmId.h"
#include "HAComponent.h"
#include "AvaMgr.h"
#include "AvaMgr.pb.h"
#include "ErrorResp.h"
#include "AvaMgrPeerStatusInterface_caller.h"
#include "AvaMgrProcessStatusInterface_caller.h"
#include "AvaMgrComponentStatusInterface_caller.h"
#include "AvailabilityManager.h"
#include "ManagementInterface.h"

bool AvailabilityManager::IsEthernetInterfaceOperational(const char *interfaceName) {
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::IsExternalInterfaceOperational() >>>>>>>>>>");

    int sockfd;
    struct ifreq ifr;

    sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0);

    if (sockfd < 0) {
        CLOG_ERROR("Could not create socket");

        CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::IsExternalInterfaceOperational() @ exit point 1 <<<<<<<<<<");

        return false;
    }

    strncpy(ifr.ifr_name, interfaceName, IFNAMSIZ);

    if (ioctl(sockfd, SIOCGIFFLAGS, &ifr) < 0) {
        CLOG_ERROR("Could not read interface flags %d for interface %s",errno,interfaceName);

        CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::IsExternalInterfaceOperational() @ exit point 2 <<<<<<<<<<");

        close(sockfd);

        return false;
    }

    if (ifr.ifr_flags & (IFF_RUNNING)) {
        CLOG_INFO("Interface %s is operational", interfaceName);

        CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::IsExternalInterfaceOperational() @ exit point 3 <<<<<<<<<<");

        close(sockfd);

        return true;
    } else {
        CLOG_ERROR("Interface %s is NOT operational", interfaceName);

        CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::IsExternalInterfaceOperational() @ exit point 4 <<<<<<<<<<");

        close(sockfd);

        return false;
    }

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::IsExternalInterfaceOperational() <<<<<<<<<<");
}

int AvailabilityManager::AssignIpAddressToInterface(const char *interfaceName, const char *ipAddress, unsigned char routingPrefix, bool assign) {

    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::AssignIpAddressToInterface() >>>>>>>>>>");

    int addrFamily = GetAddrFamily(ipAddress);

    if (addrFamily == -1)
        return addrFamily;

    struct RtNetlinkIpAddressReq rtNetlinkIpAddressReq;

    int fd;
    struct sockaddr_nl la;
    struct sockaddr_nl pa;
    struct msghdr msgHdr;
    struct iovec ioVec;

    int rc;

    int ifAddrMsgLen;
    struct rtattr *pRtAttr;

    fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);

    bzero(&la, sizeof (la));
    la.nl_family = AF_NETLINK;
    la.nl_pid = getpid();
    bind(fd, (struct sockaddr*) &la, sizeof (la));

    bzero(&rtNetlinkIpAddressReq, sizeof (rtNetlinkIpAddressReq));

    ifAddrMsgLen = sizeof (struct ifaddrmsg);

    pRtAttr = (struct rtattr *) rtNetlinkIpAddressReq.buf;
    pRtAttr->rta_type = IFA_ADDRESS;

    if (addrFamily == AF_INET) {
        pRtAttr->rta_len = sizeof (struct rtattr) + 4;
        inet_pton(AF_INET, ipAddress,
                ((char *) pRtAttr) + sizeof (struct rtattr));
    } else if (addrFamily == AF_INET6) {
        pRtAttr->rta_len = sizeof (struct rtattr) + 16;
        inet_pton(AF_INET6, ipAddress,
                ((char *) pRtAttr) + sizeof (struct rtattr));
    }

    ifAddrMsgLen += pRtAttr->rta_len;

    pRtAttr = (struct rtattr *) (((char *) pRtAttr)
            + pRtAttr->rta_len);
    pRtAttr->rta_type = IFA_LOCAL;

    if (addrFamily == AF_INET) {
        pRtAttr->rta_len = sizeof (struct rtattr) + 4;
        inet_pton(AF_INET, ipAddress,
                ((char *) pRtAttr) + sizeof (struct rtattr));
    } else if (addrFamily == AF_INET6) {
        pRtAttr->rta_len = sizeof (struct rtattr) + 16;
        inet_pton(AF_INET6, ipAddress,
                ((char *) pRtAttr) + sizeof (struct rtattr));
    }

    ifAddrMsgLen += pRtAttr->rta_len;

    rtNetlinkIpAddressReq.nl.nlmsg_len = NLMSG_LENGTH(ifAddrMsgLen);
    rtNetlinkIpAddressReq.nl.nlmsg_flags = NLM_F_REQUEST | NLM_F_CREATE | NLM_F_APPEND;

    if (assign)
        rtNetlinkIpAddressReq.nl.nlmsg_type = RTM_NEWADDR;
    else
        rtNetlinkIpAddressReq.nl.nlmsg_type = RTM_DELADDR;

    if (addrFamily == AF_INET)
        rtNetlinkIpAddressReq.rt.ifa_family = AF_INET;
    else if (addrFamily == AF_INET6)
        rtNetlinkIpAddressReq.rt.ifa_family = AF_INET6;

    rtNetlinkIpAddressReq.rt.ifa_prefixlen = routingPrefix;
    rtNetlinkIpAddressReq.rt.ifa_flags = IFA_F_PERMANENT;
    rtNetlinkIpAddressReq.rt.ifa_scope = RT_SCOPE_UNIVERSE;

    unsigned index = if_nametoindex(interfaceName);
    rtNetlinkIpAddressReq.rt.ifa_index = index;

    bzero(&pa, sizeof (pa));
    pa.nl_family = AF_NETLINK;

    bzero(&msgHdr, sizeof (msgHdr));
    msgHdr.msg_name = (void *) &pa;
    msgHdr.msg_namelen = sizeof (pa);
    ioVec.iov_base = (void *) &rtNetlinkIpAddressReq.nl;
    ioVec.iov_len = rtNetlinkIpAddressReq.nl.nlmsg_len;
    msgHdr.msg_iov = &ioVec;
    msgHdr.msg_iovlen = 1;

    rc = sendmsg(fd, &msgHdr, 0);

    close(fd);

    if (rc == -1) {
        if (assign)
            CLOG_ERROR("IP address %s ASSIGNMENT with routing prefix %d on interface %s failed", ipAddress, routingPrefix, interfaceName);
        else
            CLOG_ERROR("IP address %s UNASSIGNMENT with routing prefix %d on interface %s failed", ipAddress, routingPrefix, interfaceName);
    } else {
        if (assign)
            CLOG_NOTICE("Successfully ASSIGNED IP address %s with routing prefix %d on interface %s", ipAddress, routingPrefix, interfaceName);
        else
            CLOG_NOTICE("Successfully UNASSIGNED IP address %s with routing prefix %d on interface %s", ipAddress, routingPrefix, interfaceName);
    }

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::AssignIpAddressToInterface() <<<<<<<<<<");

    return rc;
}

int AvailabilityManager::SetArpAttribOnInterface(const char *interfaceName, bool isEnableArp) {

    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::SetArpAttribOnInterface() >>>>>>>>>>");

    int rc = 0;
    if(m_uiArpMechanism == ARP_MECHANISM_NOAP_FLAG_ON_INTERFACE )
    {
        int sockfd;
        struct ifreq ifr;

        sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0);

        if (sockfd < 0) {
            CLOG_ERROR("Could not create socket");

            CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::SetArpAttribOnInterface() @ exit point 1 <<<<<<<<<<");

            return sockfd;
        }

        strncpy(ifr.ifr_name, interfaceName, IFNAMSIZ);

        rc = ioctl(sockfd, SIOCGIFFLAGS, &ifr);

        if (rc < 0) {
            CLOG_ERROR("Could not read interface flags");

            CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::SetArpAttribOnInterface() @ exit point 2 <<<<<<<<<<");

            close(sockfd);

            return rc;
        }

        if (isEnableArp)
            ifr.ifr_flags &= ~IFF_NOARP;
        else
            ifr.ifr_flags |= IFF_NOARP;

        rc = ioctl(sockfd, SIOCSIFFLAGS, &ifr);

        if (rc < 0) {
            CLOG_WARNING("Could not set the NOARP flag");

            CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::SetArpAttribOnInterface() @ exit point 3 <<<<<<<<<<");

            close(sockfd);

            return rc;
        }

        close(sockfd);

    }
    else if(m_uiArpMechanism == ARP_MECHANISM_ARP_ANNOUNCE)
    {
        unsigned char arpIgnoreValue = ARP_IGNORE_DEFAULT;
        if (isEnableArp)
            arpIgnoreValue = m_objInterfaceMap[interfaceName].arpIgnoreOption;
        else
            arpIgnoreValue = ARP_IGNORE_DONOT_REPLY_FOR_LOCAL_ADDRESSES;

        bool ret = SetArpIgnoreFlagOnInterface(arpIgnoreValue,interfaceName);

        if(ret)
        {
            CLOG_DEBUG("Successfully set arp_ignore Value of %c on interface %s",arpIgnoreValue,interfaceName);
            rc = 0;
        }
        else
        {
            CLOG_ERROR("Failed to set arp_ignore value of %c on interface %s",arpIgnoreValue,interfaceName);
            rc = -1;
        }
    }
    else
    {
        CLOG_DEBUG("ARP will be controlled via arp_tables");
    }

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::SetArpAttribOnInterface() <<<<<<<<<<");

    return rc;
}
bool AvailabilityManager::SetGratArpCountAttribOnInterface(unsigned char count, const char* interfaceName)
{
    char fileName[255] = {0};
    sprintf(fileName,"/sys/class/net/%s/bonding/num_grat_arp",interfaceName);
    CLOG_DEBUG("File name is %s,interface name is %s",fileName,interfaceName);
    int fd;
    fd = open(fileName, O_WRONLY);
    if(fd < 0 && errno != ENOENT)
    {
        CLOG_ERROR("File %s open failed with error number %d",fileName,errno);
        return false;
    }
    else
    {
        CLOG_DEBUG("File %s opened Successfully for Writing",fileName);
    }
    if(errno == ENOENT)
    {
        //Since interface is not bonded hence this file doesn't exist
        //and returning true
        return true;
    }
    int ret = write(fd,&count,1);
    if(ret < 0 )
    {
        CLOG_DEBUG("Write to file %s failed with error number %d",fileName,errno);
        ret = close(fd);
        if(ret < 0 )
        {
            CLOG_DEBUG("Close of file %s with fd %d Failed.",fileName,fd);
        }
        return false;
    }
    else
    {
        CLOG_DEBUG("Write to file %s successful.",fileName);
        ret = close(fd);
        if(ret < 0 )
        {
            CLOG_ERROR("Close of file %s with fd %d Failed after write Failure.",fileName,fd);
        }
        return true;
    }
}

char AvailabilityManager::GetGratArpCountAttribOfInterface(const char* interfaceName)
{
    char fileName[255] = {0};
    char count;
    int fd;
    sprintf(fileName,"/sys/class/net/%s/bonding/num_grat_arp",interfaceName);
    fd = open(fileName, O_RDONLY);
    if(fd < 0 && errno != ENOENT)
    {
        CLOG_ERROR("File %s open failed with error number %d.",fileName,errno);
        return -1;
    }
    else
    {
        CLOG_DEBUG("File %s opened Successfully for Reading.",fileName);
    }
    if(errno == ENOENT)
    {
        //Since interface is not bonded hence this file doesn't exist
        //and returning true
        return true;
    }
    int ret = read(fd,&count,1);
    if(ret < 0 )
    {
        CLOG_DEBUG("Read from file %s failed with error number %d.",fileName,errno);
        ret = close(fd);
        if(ret < 0 )
        {
            CLOG_DEBUG("Close of file %s with fd %d Failed.",fileName,fd);
        }
        return -1;
    }
    else
    {
        CLOG_DEBUG("Read from file %s successful.Data is %c",fileName,count);
        ret = close(fd);
        if(ret < 0 )
        {
            CLOG_ERROR("Close of file %s with fd %d Failed after read Failure.",fileName,fd);
        }
        return count;
    }
}

char AvailabilityManager::GetArpIgnoreValueOfInterface(const char* interfaceName)
{
    char fileName[255] = {0};
    char count;
    int fd;
    sprintf(fileName,"/proc/sys/net/ipv4/conf/%s/arp_ignore",interfaceName);
    fd = open(fileName, O_RDONLY);
    if(fd < 0 && errno != ENOENT)
    {
        CLOG_ERROR("File %s open failed with error number %d.",fileName,errno);
        return -1;
    }
    else
    {
        CLOG_DEBUG("File %s opened Successfully for Reading.",fileName);
    }
    int ret = read(fd,&count,1);
    if(ret < 0 )
    {
        CLOG_DEBUG("Read from file %s failed with error number %d.",fileName,errno);
        ret = close(fd);
        if(ret < 0 )
        {
            CLOG_DEBUG("Close of file %s with fd %d Failed.",fileName,fd);
        }
        return -1;
    }
    else
    {
        CLOG_DEBUG("Read from file %s successful.Data is %c",fileName,count);
        ret = close(fd);
        if(ret < 0 )
        {
            CLOG_ERROR("Close of file %s with fd %d Failed after read Failure.",fileName,fd);
        }
        return count;
    }
}


bool AvailabilityManager::SetArpIgnoreFlagOnInterface(unsigned char flag, const char* interfaceName)
{
    char fileName[255] = {0};
    sprintf(fileName,"/proc/sys/net/ipv4/conf/%s/arp_ignore",interfaceName);
    CLOG_DEBUG("File name is %s,interface name is %s",fileName,interfaceName);
    int fd;
    fd = open(fileName, O_WRONLY);
    if(fd < 0)
    {
        CLOG_ERROR("File %s open failed with error number %d",fileName,errno);
        return false;
    }
    else
    {
        CLOG_DEBUG("File %s opened Successfully for Writing",fileName);
    }

    int ret = write(fd,&flag,1);
    if(ret < 0 )
    {
        CLOG_DEBUG("Write to file %s failed with error number %d",fileName,errno);
        ret = close(fd);
        if(ret < 0 )
        {
            CLOG_DEBUG("Close of file %s with fd %d Failed.",fileName,fd);
        }
        return false;
    }
    else
    {
        CLOG_DEBUG("Write to file %s successful.",fileName);
        ret = close(fd);
        if(ret < 0 )
        {
            CLOG_ERROR("Close of file %s with fd %d Failed after write Failure.",fileName,fd);
        }
        return true;
    }
}


int AvailabilityManager::PerformRouteOpOnInterface(std::string interfaceName, std::string srcAddress, ROUTE_OPERATION op)
{
    std::map<std::string,InterfaceAttributes>::iterator interfaceMapIter;
    interfaceMapIter = m_objInterfaceMap.find(interfaceName);
    CLOG_DEBUG("Entering PerformRouteOpOnInterface %s, %s,%x",interfaceName.c_str(),srcAddress.c_str(),interfaceMapIter->second.addRoute);
    if((interfaceMapIter != m_objInterfaceMap.end()) && (interfaceMapIter->second.addRoute))
    {
        //Add the routes.
        std::vector<struct Route>::iterator it = interfaceMapIter->second.routes.begin();
        char processArgs[ARGUMENT_LEN];
        pid_t pid;
        CLOG_DEBUG("Before For number of routes is %d",interfaceMapIter->second.routes.size());
        for(;(it != interfaceMapIter->second.routes.end());it++)
        {
            CLOG_DEBUG("Adding route to dest %s",it->destination.c_str());
            memset(processArgs,0,ARGUMENT_LEN);
            std::string operation;
            if(op == ADD)
            {
                operation = "add";
            }
            else if(op == DELETE)
            {
                operation = "del";
            }
            else
            {
                //Operation not supported
                return -1;
            }
            snprintf(processArgs,ARGUMENT_LEN," route %s %s dev %s via %s src %s",operation.c_str(),
                    it->destination.c_str(),interfaceName.c_str(),it->gateway.c_str(),srcAddress.c_str());
            CLOG_DEBUG("Adding route with processArgs %s",processArgs);

            //Optional fields
            if(it->metric != 0)
            {
                int len = strlen(processArgs);
                snprintf(&processArgs[len],ARGUMENT_LEN-len," metric %d",it->metric);
            }
            if(!it->tableId.empty())
            {
                int len = strlen(processArgs);
                snprintf(&processArgs[len],ARGUMENT_LEN-len," table %s",it->tableId.c_str());
            }

            LaunchProcess("/sbin/ip",processArgs,pid);
            if (pid < 0)
            {
                CLOG_ERROR("Adding Route failed\n");
            }
            else
            {
                CLOG_DEBUG("Added Route Successfully.");
            }
        }
    }
    CLOG_DEBUG("Exiting PerformRouteOpOnInterface");
    return 0;
}

