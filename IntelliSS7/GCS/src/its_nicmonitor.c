
/******************************************************************************
 *                                                                            *
 *  Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.         *
 *             Manufactured in the United States of America.                  *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.         *
 *                                                                            *
 *   This product and related documentation is protected by copyright and     *
 *   distributed under licenses restricting its use, copying, distribution    *
 *   and decompilation.  No part of this product or related documentation     *
 *   may be reproduced in any form by any means without prior written         *
 *   authorization of IntelliNet Technologies and its licensors, if any.      *
 *                                                                            *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the        *
 *   government is subject to restrictions as set forth in subparagraph       *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software         *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                          *
 *                                                                            *
 ******************************************************************************
 *                                                                            *
 * CONTRACT: INTERNAL                                                         *
 *                                                                            *
 ******************************************************************************
 *
 *  ID: $Id: its_nicmonitor.c,v 9.2.52.1 2014/09/16 09:34:53 jsarvesh Exp $
 *  
 * LOG: $Log: its_nicmonitor.c,v $
 * LOG: Revision 9.2.52.1  2014/09/16 09:34:53  jsarvesh
 * LOG: Changes done for removing warnings
 * LOG:
 * LOG: Revision 9.2.48.1  2014/09/15 07:20:40  jsarvesh
 * LOG: Changes done for removing Warnings
 * LOG:
 * LOG: Revision 9.2  2008/06/20 11:23:02  mpatri
 * LOG: Accelero CGI Phase I: Included linux/types.h system header file
 * LOG:
 * LOG: Revision 9.1  2007/01/10 11:14:58  yranade
 * LOG: Merge changes from 6.5.3 and Lucent branches
 * LOG:
 * LOG: Revision 1.1.2.6  2006/10/11 17:28:37  mshanmugam
 * LOG: GetLinkStatus now checks for IFF_UP status also
 * LOG:
 * LOG: Revision 1.1.2.5  2006/09/29 14:51:31  mshanmugam
 * LOG: Propagation of redundancy modifications from Kineto Branch (kramesh).
 * LOG:
 * LOG: Revision 1.1.2.4  2006/08/08 11:44:43  brajappa
 * LOG: Prototype for function CleanupEthMonSocket defined. Bug Id: 4139, compilation error in solaris
 * LOG:
 * LOG: Revision 1.1.2.3  2006/08/05 07:35:14  brajappa
 * LOG: Modification after Unit testing for ACC-RED-0653
 * LOG:
 * LOG: Revision 1.1.2.2  2006/08/05 05:28:59  brajappa
 * LOG: Incorporated code review comments for ACC-RED-0653 redundancy enchancements
 * LOG:
 *
 ****************************************************************************/


#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>

#if defined(linux)

#include <linux/types.h>
#include <linux/sockios.h>
#include <linux/ethtool.h>

#elif defined(solaris)
#include <sys/sockio.h>
#include <sys/stropts.h>
#include <inet/nd.h>
#include <inet/common.h>
#endif

#include <stdio.h>

#include <pthread.h>
#include <semaphore.h>

#include <its_nicmonitor.h>

#define INVALID_ID      -1
#define IP_LINK_DOWN     0
#define IP_LINK_UP       1
#define MAX_SOCKS        64

/* Static function predeclaration */
static void IPManagerDestroy();
static ITS_INT EnableARP(const ITS_CHAR* ifName, ITS_INT enable);
static void CleanupEthMonSocket();
static ITS_INT GetLinkFlags(const ITS_CHAR* ifName, ITS_UINT* linkFlags);
static ITS_INT SetLinkFlags(const ITS_CHAR* ifName, ITS_UINT linkFlags);


/* Static Variables */

/* Socket ID used for makeing ioctl calls */
static ITS_INT sSock = INVALID_ID;

/* Contains the list of interfaces managed */
static IfInfo sIfInfoSet[MAX_MANAGED_IFS];

/* Number of managed interfaces */
static ITS_INT sNumManagedIfs = 0;

/* Floating IP */
static struct sockaddr_in sFloatingIP;

/* Index of the active interface in the sIfInfoSet */
static ITS_INT sActiveIfId = INVALID_ID;
static ITS_INT sRunning = ITS_TRUE;
static Config config;
static ITS_INT isConfigInited = ITS_FALSE;

static ITS_INT sEthMonSock = INVALID_ID;
static ITS_INT sClientSocks[MAX_CLIENT_SOCKS];

/* Thread Id for EthMon Thread */
static pthread_t sEthMonitorThreadId;

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *     This method assign the given ip to the mentioned interface.   
 *
 *  Input Parameters:
 *     ITS_CHAR*   ifName   - Name of the interface (eth0, hme0)
 *     sockaddr_in sockAddr - IP address in sockaddr format 
 *        
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *     ITS_SUCCESS if the assignment is successful. Error code otherwise.
 *         
 *  Notes:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Balaji   02-AUG-2006  ACC-RED-SDS ID::D0120  Redundancy changes
 *
 *****************************************************************************/
static ITS_INT
AssignIP(
        const ITS_CHAR* ifName,
        struct sockaddr_in* sockAddr)
{
    ITS_INT ret;
    struct ifreq ifReq;

#if defined(solaris)
    ITS_CHAR cmd[MAX_IF_BUFFER];
    ITS_UINT linkFlags;

    sprintf(cmd, "ifconfig %s plumb", ifName);

    ret = system(cmd);
    if (0 != ret)
    {
        return ret;
    }
#endif    

    strncpy(ifReq.ifr_name, ifName, IFNAMSIZ);
    memcpy(&ifReq.ifr_addr, sockAddr, sizeof(struct sockaddr));

    ret = ioctl(sSock, SIOCSIFADDR, &ifReq);
    if(ret < 0)
    {
        perror("Assign IP failed");
        return ret;
    }

#if defined(solaris)

    ret = GetLinkFlags(ifName, &linkFlags);
    if (ret < 0)
    {
        return ret;
    }

    linkFlags |= IFF_UP;
    ret = SetLinkFlags(ifName, linkFlags);
    if (ret < 0)
    {
        return ret;
    }
#endif

    printf("Assigned IP address %s\n", ifReq.ifr_name);


    return ITS_SUCCESS;
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *    Removes the Interface mentioned.    
 *
 *  Input Parameters:
 *    ITS_CHAR* ifName - Interface name to be removed (eth0:1)
 *    
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *    ITS_SUCCESS if sucessfull, else and error code is returned
 *
 *  Notes:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Balaji   02-AUG-2006  ACC-RED-SDS ID::D0120  Redundancy changes
 *
 *****************************************************************************/
static ITS_INT 
DeassignIP(const ITS_CHAR* ifName)
{
    ITS_INT ret;

#if defined(solaris)
    ITS_CHAR cmd[MAX_IF_BUFFER];

    sprintf(cmd, "ifconfig %d unplumb", ifName);
    ret = system(cmd);
    if (ret != 0)
    {
        return ret;
    }
#else    
    struct ifreq ifReq;

    /* in linux to delete ipv4 address set the if with null address */	
    strncpy(ifReq.ifr_name, ifName, IFNAMSIZ);
    memset(&ifReq.ifr_addr, 0, sizeof(struct sockaddr));
    ifReq.ifr_addr.sa_family = AF_INET;
    ((struct sockaddr_in*)ifReq.ifr_addr.sa_data)->sin_addr.s_addr = 
        INADDR_ANY;

    ret = ioctl(sSock, SIOCSIFADDR, &ifReq);
    if(ret < 0)
    {
        perror("Deassign IP failed");
        return ret;
    }
#endif

    printf("Deassigned IP address %s\n", ifName);

    return ITS_SUCCESS;
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *    This function sets the interface as mentioned in the ifNum index as
 *    active. It assigns the virtual IP to the interface.    
 *
 *  Input Parameters:
 *    ifNum - Index to the interface table, whose entry will be made active
 *            by assigning the virtual IP
 *    
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS if successful else an error code. 
 *         
 *  Notes:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Balaji   02-AUG-2006  ACC-RED-SDS ID::D0120  Redundancy changes
 *
 *****************************************************************************/
static ITS_INT 
SetIfAsActive(ITS_INT ifNum)
{
    ITS_CHAR cmd[MAX_IF_BUFFER];
    ITS_CHAR tempIfName[IFNAMSIZ];
    ITS_INT prevActiveIfId = sActiveIfId;

    if (sIfInfoSet[ifNum].isActive)
    {
        /* Interface already active. Do nothing */
        return ITS_SUCCESS;
    }
    if (INVALID_ID != prevActiveIfId)
    {
        /*disable arp on the interface that went down */
        EnableARP(sIfInfoSet[prevActiveIfId].name, ITS_FALSE);

        /* Some one is active already. Change its state */
        /* Remove its virtual IP */
        sIfInfoSet[prevActiveIfId].isActive = ITS_FALSE;
        sprintf(tempIfName, "%s:1", sIfInfoSet[prevActiveIfId].name);
        DeassignIP(tempIfName);        
    }

    sIfInfoSet[ifNum].isActive = ITS_TRUE;
    sActiveIfId = ifNum;

    /* Assign the virtual IP to the interface. ':1' is appended to the
       interface name */
    sprintf(tempIfName, "%s:1", sIfInfoSet[ifNum].name);
    AssignIP(tempIfName, &sFloatingIP);

    /* Send a gratuitous/unsolicited arp, to update the hosts having the ip 
     * addr entry */
#if defined(solaris)
    EnableARP(tempIfName, ITS_TRUE);
#else    
    {
        ITS_CHAR srcAddr[20];
        ITS_INT numCounts = 2;
        ITS_UINT linkFlags = 0;
        ITS_INT  ret = 0;

        ret = GetLinkFlags(sIfInfoSet[ifNum].name, &linkFlags);
        if (ret >= 0)
        {
            linkFlags |= IFF_UP;
            ret = SetLinkFlags(sIfInfoSet[ifNum].name, linkFlags);
            printf("Bringing up %s\n", sIfInfoSet[ifNum].name);
        }        

        inet_ntop (sFloatingIP.sin_family, &sFloatingIP.sin_addr, 
                srcAddr, sizeof(struct sockaddr_in));
        sprintf (cmd, "/sbin/arping -c %d -U -s %s -I %s 255.255.255.255 "
                 "> /dev/null", numCounts, srcAddr, sIfInfoSet[ifNum].name);
        system(cmd);
    }
#endif

    if(INVALID_ID != prevActiveIfId)
    {
        /* Enable arp on the interface that went down */
        EnableARP(sIfInfoSet[prevActiveIfId].name, ITS_TRUE);
    }

    return ITS_SUCCESS;
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *     Adds the interface to the interface monitor table and assigns the
 *     virtual IP to the first interface. 
 *
 *  Input Parameters:
 *     ifNum - Index to the interface table.
 *     ifReq - ifreq structure from which the interface name is extracted
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *     ITS_SUCCESS always.
 *         
 *  Notes:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Balaji   02-AUG-2006  ACC-RED-SDS ID::D0120  Redundancy changes
 *
 *****************************************************************************/
static ITS_INT 
InitInterface(ITS_INT ifNum,
        ITS_CHAR* ifName)
{
    static ITS_INT isInitial = ITS_TRUE;
    ITS_CHAR tempIfName[MAX_IFNAME_SIZE];

    /* Cleanup previously assigned floating IP if any */
    sprintf(tempIfName, "%s:1", ifName);
    DeassignIP(tempIfName);
    
    strcpy (sIfInfoSet[ifNum].name, ifName);
    sIfInfoSet[ifNum].status = IP_LINK_UP;
    
    if (isInitial)
    {
        isInitial = ITS_FALSE;

        /* Make the first added Interface as active */
        SetIfAsActive(ifNum);
    }
    else
    {
        sIfInfoSet[ifNum].isActive = ITS_FALSE;
    }

    return ITS_SUCCESS;	
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *     Opens the ioctl socket, verifies the presence of a NIC and then 
 *     assigns the virtual ip to the active interface 
 *
 *  Input Parameters:
 *     ifNames - list of interfaces to be monitoresd
 *     floatingIP - the virtual IP that is to be assigned to the interface.
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *     Returns ITS_SUCCESS if successful else an error code
 *         
 *  Notes:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Balaji   02-AUG-2006  ACC-RED-SDS ID::D0120  Redundancy changes
 *
 *****************************************************************************/
static ITS_INT 
IPManagerInit(InterfaceNames *ifNames,
        const ITS_CHAR* floatingIP)
{
    ITS_INT ret = INVALID_ID;
    ITS_INT i;
    ITS_UINT linkFlags = 0;

    sSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (sSock == INVALID_ID)
    {
        perror("Socket Creation Failed");
        return ret;
    }

    memset(&sFloatingIP, 0, sizeof(sFloatingIP));
    sFloatingIP.sin_family = AF_INET;
    inet_pton(AF_INET, floatingIP, &sFloatingIP.sin_addr);


    /* Check if the interface is present */
    for (i = 0; i < ifNames->numInterfaces; i++)
    {
        if(GetLinkFlags(ifNames->ifName[i], &linkFlags) == 0)
        {
            /* Interface found. Add it to the interface table
             * and assign virutal ip for the first one */ 
            InitInterface(sNumManagedIfs, ifNames->ifName[i]);
            sNumManagedIfs++;
        }
        else
        {
            printf("Error: Interface %s not found\n",
                  ifNames->ifName[i]);
        }
    }
    if (sNumManagedIfs == 0)
    {
        printf("Not enough interfaces to manage. Init EthMon Failed\n");
        IPManagerDestroy();
        return INVALID_ID;
    }

    return 0;
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *     Cleans up the IP manager. Deassigns any active interface and closes
 *     the ioctl socket.   
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *         
 *  Notes:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Balaji   02-AUG-2006  ACC-RED-SDS ID::D0120  Redundancy changes
 *
 *****************************************************************************/
static void 
IPManagerDestroy()
{
    if (INVALID_ID != sActiveIfId)
    {
        ITS_CHAR tempIfName[IFNAMSIZ];

        sprintf(tempIfName, "%s:1", sIfInfoSet[sActiveIfId].name);
        DeassignIP(tempIfName);
    }

    if (INVALID_ID != sSock)
    {
        close(sSock);
    }
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *     Get the links status, if it is UP or down   
 *
 *  Input Parameters:
 *     ifName - Interface name for which the link is UP or down
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *      linkStatus - Status of the link, if it is UP or down
 *
 *  Return Value:
 *         
 *  Notes:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Balaji   02-AUG-2006  ACC-RED-SDS ID::D0120  Redundancy changes
 *
 *****************************************************************************/
static ITS_INT 
GetLinkStatus(const ITS_CHAR* ifName,
        ITS_UINT *linkStatus)
{
    ITS_INT ret = 0;

#if defined(solaris)    
    static ITS_INT isFirst = ITS_TRUE;
    static ITS_INT devFd = INVALID_ID;

    if (isFirst)
    {
        ITS_CHAR device[MAX_IF_BUFFER];
        ITS_CHAR tempIf;
        ITS_INT len;

        /* Open the device to get its status */
        isFirst = 0;
        sprintf(device, "/dev/%s", ifName);
        devFd = open(device, 0);
        if (devFd < 0)
        {
            /* Opening the device with instance failed
             * Strip of the instance id and open it now */

            printf("%s open failed\n", device);
            len = strlen(device);
            device[len - 2] = '\0';

            devFd = open(device, 0);
            if (devFd < 0)
            {
                printf("%s open failed\n", device);
            }
        }
    }
    if (devFd != INVALID_ID)
    {
        struct strioctl strIo;
        ITS_CHAR buf[MAX_IF_BUFFER];
        ITS_CHAR *cp;

        strIo.ic_cmd = ND_GET;
        strIo.ic_timout = 0;
        strIo.ic_len = sizeof(buf);
        strIo.ic_dp = buf;

        ret = ioctl(devFd,I_STR,(ITS_CHAR *)&strIo);
        if (ret < 0)
        {
            if (errno == ENOENT) 
            {
                printf("NDD: name is non-existent for this module\n");
            }
            else
            {
                printf("NDD: operation failed, \n");
            }
            return ret;
        }
        if ('1' == buf[0])
        {
            *linkStatus = IP_LINK_UP;
        }
        else
        {
            *linkStatus = IP_LINK_DOWN;
        }

    }
#else    
    struct ifreq ifReq;
    struct ethtool_value linkStats; 
    ITS_UINT linkFlag = 0;

    *linkStatus = 0;
    
    ret = GetLinkFlags(ifName, &linkFlag);
    if (ret < 0)
    {
        return ret;
    }

    if ( !(linkFlag & IFF_UP) )
    {
        *linkStatus = 0;
        return 0;
    }

    strncpy(ifReq.ifr_name, ifName, IFNAMSIZ);

    /* This Works only for Linux */
    ifReq.ifr_data = (caddr_t)&linkStats;
    linkStats.cmd = ETHTOOL_GLINK;
    ret = ioctl(sSock, SIOCETHTOOL, &ifReq);
    if (ret < 0)
    {
        perror("NicMon: Getting Eth stats failed\n");
        switch(errno)
        {
            case EPERM:
            case EOPNOTSUPP:
                printf("NicMon: Interface %s does not support"
                       " NIC Monitoring\n", ifName);
                break;
            case EACCES:
                printf("NicMon: Run as root to enable NIC monitoring\n");    
                break;
        }
        return ret;
    }
    *linkStatus = linkStats.data;
#endif    

    return ret; 
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *    Get NIC parameters for the NIC    
 *
 *  Input Parameters:
 *    ifName    - Interface name for which link flags are to be set
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *    linkFlags - value for the link flag
 *
 *  Return Value:
 *         
 *  Notes:
 *   Possible return values IFF_UP, IFF_BROADCAST, IFF_LOOPBACK, IFF_RUNNING,
 *   IFF_NOARP... 
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Balaji   02-AUG-2006  ACC-RED-SDS ID::D0120  Redundancy changes
 *
 *****************************************************************************/
static ITS_INT 
GetLinkFlags(const ITS_CHAR* ifName,
        ITS_UINT* linkFlags)
{
    ITS_INT ret = 0;
    struct ifreq ifReq;

    strncpy(ifReq.ifr_name, ifName, IFNAMSIZ);

    ret = ioctl(sSock, SIOCGIFFLAGS, &ifReq);
    if (ret < 0)
    {
        perror("Getting Interface Flags failed\n");
        return ret;
    }
    *linkFlags = ifReq.ifr_flags;

    return ret;
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *    Set the NIC flags for the specified interface.    
 *
 *  Input Parameters:
 *    ifName    - Interface name for which link flags are to be set
 *    linkFlags - value for the link flag
 *
 *  Input/Output Parameters:
 *    None  
 *
 *  Output Parameters:
 *    None  
 *
 *  Return Value:
 *         
 *  Notes:
 *   Possible values IFF_UP, IFF_BROADCAST, IFF_LOOPBACK, IFF_RUNNING,
 *   IFF_NOARP... 
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Balaji   02-AUG-2006  ACC-RED-SDS ID::D0120  Redundancy changes
 *
 *****************************************************************************/
static ITS_INT 
SetLinkFlags(const ITS_CHAR* ifName,
        ITS_UINT linkFlags)
{
    ITS_INT ret = 0;
    struct ifreq ifReq;

    strncpy(ifReq.ifr_name, ifName, IFNAMSIZ);
    ifReq.ifr_flags = linkFlags;

    ret = ioctl(sSock, SIOCSIFFLAGS, &ifReq);
    if (ret < 0)
    {
        perror("Getting Interface Flags failed\n");
        return ret;
    }

    return ret;
}


/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *    Enables or disables the ARP on the given interface  
 *
 *  Input Parameters:
 *    ifName - Interface name on which ARP is to be enabled/disabled
 *    enable - if 1 ARP is enabled, if 0 ARP is disabled 
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *         
 *  Notes:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Balaji   02-AUG-2006  ACC-RED-SDS ID::D0120  Redundancy changes
 *
 *****************************************************************************/
static ITS_INT 
EnableARP(const ITS_CHAR* ifName,
        ITS_INT enable)
{
    ITS_INT ret = 0;
    ITS_UINT linkFlags = 0;

    ret = GetLinkFlags(ifName, &linkFlags);
    if (ret < 0)
    {
        return ret;
    }

    if (enable)
    {
        linkFlags &= (0xFFFFFFFF & ~IFF_NOARP);
    }
    else
    {
        linkFlags |= IFF_NOARP;
    }

    ret = SetLinkFlags(ifName, linkFlags);

    return ret;
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *    Suspends the execution for the given duration in milliseconds   
 *
 *  Input Parameters:
 *    msWait - duration of wait in milliseconds
 *
 *  Input/Output Parameters:
 *    None  
 *
 *  Output Parameters:
 *    None  
 *
 *  Return Value:
 *         
 *  Notes:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Balaji   02-AUG-2006  ACC-RED-SDS ID::D0120  Redundancy changes
 *
 *****************************************************************************/
static void 
Wait(ITS_UINT msWait)
{
    struct timespec waitTime, remTime;

    waitTime.tv_sec = msWait / 1000;
    waitTime.tv_nsec = (msWait % 1000) * 1000 * 1000;
    remTime.tv_sec = 0;
    remTime.tv_nsec = 0;

    while(nanosleep(&waitTime, &remTime) < 0 && EINTR == errno)
    {
        waitTime = remTime;
    }
}


/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *    Initialized the client socket table   
 *
 *  Input Parameters:
 *    None
 *
 *  Input/Output Parameters:
 *    None  
 *
 *  Output Parameters:
 *    None  
 *
 *  Return Value:
 *         
 *  Notes:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Balaji   02-AUG-2006  ACC-RED-SDS ID::D0120  Redundancy changes
 *
 *****************************************************************************/
static void 
InitClientSocks()
{
    ITS_INT i;

    for (i = 0; i < MAX_CLIENT_SOCKS; i++)
    {
        sClientSocks[i] = INVALID_ID;
    }
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *    Adds a client socket to the table.   
 *
 *  Input Parameters:
 *    sock - Client socket to be added to the table
 *
 *  Input/Output Parameters:
 *    None  
 *
 *  Output Parameters:
 *    None  
 *
 *  Return Value:
 *         
 *  Notes:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Balaji   02-AUG-2006  ACC-RED-SDS ID::D0120  Redundancy changes
 *
 *****************************************************************************/
static ITS_INT 
InsertClientSock(ITS_INT sock)
{
    ITS_INT i;

    for (i = 0; i < MAX_CLIENT_SOCKS; i++)
    {
        if (INVALID_ID == sClientSocks[i])
        {
            sClientSocks[i] = sock;
            return ITS_SUCCESS;
        }
    }

    return INVALID_ID;
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *    Sets the FDSET with client socket IDs.    
 *
 *  Input Parameters:
 *    fdSet - read FD set to be provides to 'select' system call.
 *
 *  Input/Output Parameters:
 *    None  
 *
 *  Output Parameters:
 *    None  
 *
 *  Return Value:
 *         
 *  Notes:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Balaji   02-AUG-2006  ACC-RED-SDS ID::D0120  Redundancy changes
 *
 *****************************************************************************/
static void 
SetClientSockFDSet(fd_set* fdSet)
{
    ITS_INT i;

    for (i = 0; i < MAX_CLIENT_SOCKS; i++)
    {
        if (INVALID_ID != sClientSocks[i])
        {
            FD_SET(sClientSocks[i], fdSet);
        }
    }
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *     Check if the client socket is set of reading. If so they are closed.  
 *
 *  Input Parameters:
 *     fdSet - read FD set as returned by the 'select' method
 *
 *  Input/Output Parameters:
 *     None 
 *
 *  Output Parameters:
 *     None 
 *
 *  Return Value:
 *         
 *  Notes:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Balaji   02-AUG-2006  ACC-RED-SDS ID::D0120  Redundancy changes
 *
 *****************************************************************************/
static void
CheckIfClientSockSet(fd_set* fdSet)
{
    ITS_INT i;
    ITS_INT shutdown = 0;
    ITS_INT ret;

    for (i = 0; i < MAX_CLIENT_SOCKS; i++)
    {
        if (INVALID_ID != sClientSocks[i] && FD_ISSET(sClientSocks[i], fdSet))
        {
            /* Client Sock FD is set */
            ret = recv(sClientSocks[i], &shutdown, sizeof(ITS_INT), 0);
            if (ret > 0)
            {
                if (shutdown)
                {
                    printf("Shutdown message received. Shutting down GCS\n");
                    CleanupEthMonSocket();
                    exit(0);
                }
            }
            else if(0 == ret)
            {
                close(sClientSocks[i]);
                sClientSocks[i] = INVALID_ID;
            }
        }
    }
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *     Sends the Link status to DSM-GCS client.   
 *
 *  Input Parameters:
 *     status - Can be LINK_UP of LINK_DOWN
 *
 *  Input/Output Parameters:
 *     None 
 *
 *  Output Parameters:
 *     None 
 *
 *  Return Value:
 *         
 *  Notes:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Balaji   02-AUG-2006  ACC-RED-SDS ID::D0120  Redundancy changes
 *
 *****************************************************************************/
static void 
SendToClientSock(ITS_UINT status)
{
    ITS_INT i;

    for (i = 0; i < MAX_CLIENT_SOCKS; i++)
    {
        if (INVALID_ID != sClientSocks[i])
        {
            if (send(sClientSocks[i], &status, sizeof(ITS_UINT), 0) < 0)
            {
                /* Send failed. Probably the peer socket is closed */
                close(sClientSocks[i]);
                sClientSocks[i] = INVALID_ID;
            }
        }
    }   
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *     Closes all the DSM-GCS client communication sockets.   
 *
 *  Input Parameters:
 *     None
 *
 *  Input/Output Parameters:
 *     None 
 *
 *  Output Parameters:
 *     None 
 *
 *  Return Value:
 *     None
 *         
 *  Notes:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Balaji   02-AUG-2006  ACC-RED-SDS ID::D0120  Redundancy changes
 *
 *****************************************************************************/
static void 
CloseAllClientSock()
{
    ITS_INT i;

    for (i = 0; i < MAX_CLIENT_SOCKS; i++)
    {
        if (INVALID_ID != sClientSocks[i])
        {
            close(sClientSocks[i]);
            sClientSocks[i] = INVALID_ID;
        }
    }   
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *     Initialized and bind to the ethernet monitoring port. This socket is
 *     used for notifying the DSM-GCS with IP link status   
 *
 *  Input Parameters:
 *     None
 *
 *  Input/Output Parameters:
 *     None 
 *
 *  Output Parameters:
 *     None 
 *
 *  Return Value:
 *     ITS_SUCCESS if successful, else and error code is returned
 *         
 *  Notes:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Balaji   02-AUG-2006  ACC-RED-SDS ID::D0120  Redundancy changes
 *
 *****************************************************************************/
static ITS_INT 
InitEthMonSocket()
{
    ITS_INT ret = 0;
    struct sockaddr_in sinAddr;
    ITS_UINT enable = 1;

    memset(&sinAddr, 0, sizeof(sinAddr));

    sEthMonSock = socket(AF_INET, SOCK_STREAM, 0);
    if (INVALID_ID == sEthMonSock)
    {
        perror("Eth Mon Socket failed\n");
        return INVALID_ID;
    }

    /* Reuse the socket address. The accepted sockets of previous run
     * would have been in TIME_WAIT state */
    ret = setsockopt(sEthMonSock, SOL_SOCKET, SO_REUSEADDR,
            &enable, sizeof(ITS_UINT));
    if (ret < 0)
    {
        /* Need not return from here. If the socket address is already in use
         * bind will fail */
        perror("InitEthMonSocket(setsockopt");
    }
    
    sinAddr.sin_family = AF_INET;
    sinAddr.sin_port   = htons(config.serverPort);
    sinAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    ret = bind(sEthMonSock, (struct sockaddr*)&sinAddr, sizeof(sinAddr));
    if (ret < 0)
    {
        perror("InitEthMonSocket(bind)");
        return ret;
    }

    ret = listen(sEthMonSock, 5);
    if (ret < 0)
    {
        perror("Listen\n");
    }
    /* Initialize the client socket table */
    InitClientSocks();

    return ret;
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *     Closes all the client and server socket communication with the 
 *     GCS client
 *
 *  Input Parameters:
 *     None
 *
 *  Input/Output Parameters:
 *     None
 *
 *  Output Parameters:
 *     None  
 *
 *  Return Value:
 *         
 *  Notes:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Balaji   02-AUG-2006  ACC-RED-SDS ID::D0120  Redundancy changes
 *
 *****************************************************************************/
static void 
CleanupEthMonSocket()
{
    CloseAllClientSock();
    close(sEthMonSock);
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *     Checks for client registrations or closure   
 *
 *  Input Parameters:
 *     msWait - Duration in milliseconds to wait
 *
 *  Input/Output Parameters:
 *     None 
 *
 *  Output Parameters:
 *     None 
 *
 *  Return Value:
 *     ITS_SUCCESS if successful, an error code otherwise
 *         
 *  Notes:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Balaji   02-AUG-2006  ACC-RED-SDS ID::D0120  Redundancy changes
 *
 *****************************************************************************/
static ITS_INT 
CheckForMessages(ITS_INT msWait)
{
    struct timeval waitTime;
    ITS_INT ret = 0;
    ITS_CHAR buff[20];
    fd_set readFdSet;
    ITS_INT size;
    struct sockaddr_in tempSock;

    waitTime.tv_sec = msWait / 1000;
    waitTime.tv_usec = (msWait % 1000) * 1000;

    FD_ZERO(&readFdSet);
    FD_SET(sEthMonSock, &readFdSet);
    SetClientSockFDSet(&readFdSet);
    while ( (ret = select(MAX_SOCKS, &readFdSet,0 , 0, &waitTime)) < 0
            && EINTR == errno);
    if (ret <= 0)
    {
        /* timeout or error */
        return ITS_SUCCESS;
    }

    /* This is done to see of the clients are alive */
    CheckIfClientSockSet(&readFdSet);

    if(!FD_ISSET(sEthMonSock, &readFdSet))
    {
        return ITS_SUCCESS;
    }

    tempSock.sin_family = AF_INET;
    size = sizeof(struct sockaddr_in);
    ret = accept(sEthMonSock, (struct sockaddr*)&tempSock, (socklen_t*) &size);
    if (ret < 0)
    {
        perror("Accept");
        return ret;
    }
    printf("##### Client's address %s:%d\n",
            inet_ntop(AF_INET, &tempSock.sin_addr, buff, 20),
            ntohs(tempSock.sin_port));

    /* Insert the client socket to the Client socket table */
    InsertClientSock(ret);

    /* Wait for the remaining time */
    Wait ( (waitTime.tv_sec*1000) + (waitTime.tv_usec/1000) );

    return ITS_SUCCESS;
}


/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *    Determines if there is a change in links status. If there is a change in
 *    link status, a message is send to the registered clients.   
 *
 *  Input Parameters:
 *    cumLinkStatus    - link status as polled from interface
 * 
 *  Input/Output Parameters:
 *    curCumLinkStatus - current link status
 *
 *  Output Parameters:
 *    None  
 *
 *  Return Value:
 *         
 *  Notes:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Balaji   02-AUG-2006  ACC-RED-SDS ID::D0120  Redundancy changes
 *
 *****************************************************************************/
static void 
ComputeLinkStateChange(ITS_UINT* curCumLinkState,
        ITS_UINT cumLinkStatus)
{
    if (*curCumLinkState != cumLinkStatus)
    {
        /* Link state has changed */
        if (cumLinkStatus)
        {
            printf("Cumulative Link status is UP\n");
        }
        else
        {
            printf("Cumulative Links status is DOWN\n");
        }
        SendToClientSock(cumLinkStatus);

        *curCumLinkState = cumLinkStatus;
    }
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *    Monitors the interface for link status. If one of the interface fails,
 *    switchover to the other is done.  
 *
 *  Input Parameters:
 *    msWait - Time period of polling NIC status.
 *
 *  Input/Output Parameters:
 *    None  
 *
 *  Output Parameters:
 *    None  
 *
 *  Return Value:
 *         
 *  Notes:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Balaji   02-AUG-2006  ACC-RED-SDS ID::D0120  Redundancy changes
 *
 *****************************************************************************/
static ITS_INT 
IPManagerStartMonitor(ITS_UINT msWait)
{
    ITS_INT ret = 0;
    ITS_UINT curCumLinkState = IP_LINK_UP;
    ITS_INT i;

    if(sNumManagedIfs < 2)
    {
        printf("Not enough interfaces to monitor\n");
        return INVALID_ID;
    }

    ret = InitEthMonSocket();
    if (ret < 0)
    {
        printf("Initialization of Ethmon failed\n");
        return INVALID_ID;
    }

    while(sRunning)
    {
        ITS_UINT linkStatus = 0;

        CheckForMessages(msWait);

        if (INVALID_ID != sActiveIfId)
        {
            ret = GetLinkStatus(sIfInfoSet[sActiveIfId].name, &linkStatus);
            if (ret < 0)
            {
                /* Getting link status Failed */
                return INVALID_ID;
            }
            if (linkStatus)
            {
                /* Link up.. */
                ComputeLinkStateChange(&curCumLinkState, IP_LINK_UP);
                continue;
            }
        }
        /* Either there is no active interface 
           or the active Link is Down.
           Find a suitable link to takover as active */
        for (i = 0; i < sNumManagedIfs; i++)
        {
            if (i == sActiveIfId) continue;

            linkStatus = 0;
            ret = GetLinkStatus(sIfInfoSet[i].name, &linkStatus); 
            if (ret < 0)
            {
                return INVALID_ID;
            }
            if(linkStatus)
            {
                /* Set this interface as active */
                SetIfAsActive(i);
                ComputeLinkStateChange(&curCumLinkState, IP_LINK_UP);
                break;
            }
        }
        if (i == sNumManagedIfs)
        {
            /* No active interface found. Poll again */
            printf("No active interface found to switchover\n");
            ComputeLinkStateChange(&curCumLinkState, IP_LINK_DOWN);
            if (INVALID_ID != sActiveIfId)
            {
                ITS_CHAR tempIfName[IFNAMSIZ];
                sIfInfoSet[sActiveIfId].isActive = ITS_FALSE;
                sprintf(tempIfName, "%s:1", sIfInfoSet[sActiveIfId].name);
                DeassignIP(tempIfName);
                sActiveIfId = INVALID_ID;
            }
        }
    }
    CleanupEthMonSocket();

    return ret;
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *     Monitors only single interface as mentioned in the ifName. 
 *     Monitoring is done only to get the links status. 
 *
 *  Input Parameters:
 *     ifName - Interface name to be monitored
 *     msWait - Time period for NIC status poll
 *
 *  Input/Output Parameters:
 *     None 
 *
 *  Output Parameters:
 *     None 
 *
 *  Return Value:
 *         
 *  Notes:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Balaji   02-AUG-2006  ACC-RED-SDS ID::D0120  Redundancy changes
 *
 *****************************************************************************/
static ITS_INT 
SingleLinkMonitor(
        const ITS_CHAR* ifName,
        ITS_INT msWait)
{
    ITS_INT ret = 0;
    ITS_UINT linkStatus = IP_LINK_DOWN;
    ITS_UINT curLinkStatus = IP_LINK_UP;

    sSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (sSock == INVALID_ID)
    {
        perror("Socket Creation Failed");
        return ret;
    }
    
    ret = InitEthMonSocket();
    if (ret < 0)
    {
        printf("Initialization of Ethmon failed\n");
        return INVALID_ID;
    }

    while(sRunning)
    {
        CheckForMessages(msWait);

        linkStatus = 0;
        ret = GetLinkStatus(ifName, &linkStatus);
        if (ret < 0)
        {
            printf("Get link status failed\n");
            return INVALID_ID;
        }

        ComputeLinkStateChange(&curLinkStatus, linkStatus);
    }
    CleanupEthMonSocket();

    return ITS_SUCCESS;
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *     Initalize the configuration parameters   
 *
 *  Input Parameters:
 *     None
 *
 *  Input/Output Parameters:
 *     None 
 *
 *  Output Parameters:
 *     None 
 *
 *  Return Value:
 *     None
 *         
 *  Notes:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Balaji   02-AUG-2006  ACC-RED-SDS ID::D0120  Redundancy changes
 *
 *****************************************************************************/
static void 
InitConfig()
{
    config.ifNames.numInterfaces = 0;
    config.floatIP = NULL;
    config.monDuration = 100;
    config.serverPort = 5000;
    isConfigInited = ITS_TRUE;
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *    This is the thread that monitors the interfaces and make NIC level
 *    redundancy possible    
 *
 *  Input Parameters:
 *    void* arg - Semaphore that has to be signaled from here.
 *     
 *  Input/Output Parameters:
 *     None. 
 *
 *  Output Parameters:
 *     None. 
 *
 *  Return Value:
 *         
 *  Notes:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Balaji   02-AUG-2006  ACC-RED-SDS ID::D0120  Redundancy changes
 *
 *****************************************************************************/
static void* 
EthMonitorThread(
        void* arg)
{
    sem_t* semInit = (sem_t*)arg;
    ITS_INT ret;

    if (config.ifNames.numInterfaces >= 2 && NULL != config.floatIP)
    {
        /* Multiple Interfaces and a floating IP found 
         * Manage the redundant NIC's with the floating IP */
        ret = IPManagerInit(&config.ifNames, config.floatIP);
        if (ret < 0)
        {
            IPManagerDestroy();
            printf("Exiting NIC monitor...\n");
            return 0;
        }

        /* signal the main thread to proceed */
        sem_post(semInit);

        ret = IPManagerStartMonitor(config.monDuration);
        if (ret < 0)
        {
            IPManagerDestroy();
            printf("Exiting NIC monitor...\n");
            return 0;
        }

        IPManagerDestroy();
    }
    else
    {
        /* No multiple interface of no floaing IP 
         * NIC level redundancy is not possible and just do link status
         * monitoring */
        
        /* signal the main thread to proceed */
        sem_post(semInit);

        if (config.ifNames.numInterfaces >= 1)
        {
            ret = SingleLinkMonitor(config.ifNames.ifName[0],
                    config.monDuration);
            if (ret < 0)
            {
                printf("Exiting NIC monitor...\n");
                return 0;
            }
        }
        else
        {
            /* No interfaces present to monitor */
            printf("No Interface present to monitor\n");
        }
    }
    printf("NICmonitor thread exited...\n");

    return NULL;    
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *     Extracts the configuration values from the command line argument   
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      argc - Count of command line arguments 
 *      argv - Command line arguments
 * 
 *  Output Parameters:
 *     None.
 *
 *  Return Value:
 *      ITS_SUCCESS on succesfullt parsing the argument. 
 *      INVALID_ID if failed
 *         
 *  Notes:
 *     This function is to be called from spread.c
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Balaji   02-AUG-2006  ACC-RED-SDS ID::D0120  Redundancy changes
 *
 *****************************************************************************/
ITS_INT 
ITS_ParseEthMonArg(
        ITS_INT* argc,
        ITS_CHAR** argv[])
{
    if(!isConfigInited)
    {
        InitConfig();
    }
    if( (*argc) > 0 )
    {
        if( 0 == strncmp( **argv, "-i", 2 ) )
        {
            if (*argc < 2)
            {
                return INVALID_ID;
            }
            (*argc)--; (*argv)++;
            strcpy(config.ifNames.ifName[config.ifNames.numInterfaces],
                    **argv);
            config.ifNames.numInterfaces++;
        }
        else if ( 0 == strncmp(**argv, "-f", 2) )
        {
            if (*argc < 2)
            {
                return INVALID_ID;
            }
            (*argc)--; (*argv)++;
            config.floatIP = **argv;
        }
        else if ( 0 == strncmp(**argv, "-m", 2) )
        {
            if (*argc < 2)
            {
                return INVALID_ID;
            }
            (*argc)--; (*argv)++;
            config.monDuration = atoi(**argv);
            if (config.monDuration <= 0)
            {
                return INVALID_ID;
            }
        }
        else if ( 0 == strncmp(**argv, "-p", 2) )
        {
            if (*argc < 2)
            {
                return INVALID_ID;
            }
            (*argc)--; (*argv)++;
            config.serverPort = atoi(**argv);
        }
        else
        {
            return INVALID_ID;
        }
    }
    return ITS_SUCCESS;
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *     Starts the NIC monitor thread and waits for it to initialize. Only 
 *     after NIC monitor is initialized the GCS can bind to the Virtual IP
 *     in case virtual IP is used. 
 *
 *  Input Parameters:
 *     None.
 *
 *  Input/Output Parameters:
 *     None.
 *
 *  Output Parameters:
 *     None. 
 *
 *  Return Value:
 *     ITS_SUCCESS if successful, error code otherwise
 *         
 *  Notes:
 *      This function is to be called from spread.c
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Balaji   02-AUG-2006  ACC-RED-SDS ID::D0120  Redundancy changes
 *
 *****************************************************************************/
ITS_INT 
ITS_InitEthMonThread()
{
    sem_t semIsEthThreadInited;
    int ret = ITS_SUCCESS;

    ret = sem_init(&semIsEthThreadInited, 0, 0);
    if (ret < 0)
    {
        printf("Semaphore init failed: %d\n", errno);
        return ret;
    }

    /* Launch the NIC monitor thread */
    ret = pthread_create(&sEthMonitorThreadId, NULL, EthMonitorThread, 
            (void*)&semIsEthThreadInited);
    if (ret < 0)
    {
        sem_destroy(&semIsEthThreadInited);
        printf("Thread create failed: %d\n", ret);
        return ret;
    }

    printf("\nWaiting for Ethernet monitor tool....\n");
    ret = sem_wait(&semIsEthThreadInited);
    if (ret < 0)
    {
        printf("Semaphore wait failed: %d\n", ret);
    }

    printf("EthMonitor Tool is up and running.\n\n");    
    sem_destroy(&semIsEthThreadInited);

    return ITS_SUCCESS;
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *    Terminates the Eth monitor thread
 *
 *  Input Parameters:
 *     None.
 *
 *  Input/Output Parameters:
 *     None.
 *
 *  Output Parameters:
 *     None. 
 *
 *  Return Value:
 *         
 *  Notes:
 *      This function is to be called from spread.c
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Balaji   02-AUG-2006  ACC-RED-SDS ID::D0120  Redundancy changes
 *
 *****************************************************************************/
void ITS_TerminateEthMonThread()
{
    sRunning = ITS_FALSE;

    /* Wait for the thread to join */
    pthread_join(sEthMonitorThreadId, NULL);
}


