/***************************************************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *  ID: $Id: sip_transport.c,v 9.1 2005/03/23 12:54:27 cvsadmin Exp $
 *
 *  $Log: sip_transport.c,v $
 *  Revision 9.1  2005/03/23 12:54:27  cvsadmin
 *  Begin PR6.5
 *
 *  Revision 1.22  2005/03/21 13:53:26  cvsadmin
 *  PR6.4.2 Source Propagated to Current
 *
 *  Revision 1.21.2.2  2005/03/09 07:12:20  mkrishna
 *  modification done for TCP transport
 *
 *  Revision 1.21.2.1  2004/12/28 14:00:34  mkrishna
 *  SIP code propagated from Current Branch
 *
 *  Revision 1.21  2004/07/19 14:34:38  sjaddu
 *  sip_event_term(&sipEvent) to sipEvent.
 *
 *  Revision 1.20  2004/06/10 14:24:50  sjaddu
 *  One NToHL is removed from Trans create func.
 *
 *  Revision 1.19  2004/05/16 08:47:46  sjaddu
 *  Added TCP support.
 *
 *  Revision 1.18  2004/04/27 13:07:04  sjaddu
 *  NToHL is requied on linux, don't know why.
 *
 *  Revision 1.17  2004/04/27 11:15:39  sjaddu
 *  Transport layer revamping, no more dumps.
 *
 *  Revision 1.16  2004/04/23 13:19:44  sjaddu
 *  Testing going on.
 *
 *  Revision 1.15  2004/04/21 06:45:04  sjaddu
 *  Fixed some bugs.
 *
 *  Revision 1.14  2004/04/16 04:54:55  akumar
 *  SIP attributes are configurable thru XML.
 *
 *  Revision 1.13  2004/04/15 12:16:16  sjaddu
 *  Added indications & state machine revamping.
 *
 *  Revision 1.12  2004/04/05 12:48:31  akumar
 *  Bug fix cycle.
 *
 *  Revision 1.11  2004/04/05 09:14:14  akumar
 *  Bug fix while testing basic session setup.
 *
 *  Revision 1.10  2004/04/05 07:47:25  sjaddu
 *  More testing, one complete call works fine.
 *
 *  Revision 1.9  2004/04/01 06:44:03  sjaddu
 *  Testing is in progress.
 *
 *  Revision 1.8  2004/03/25 10:08:53  dsatish
 *  Commit Done after ipaddress data type changes
 *
 *  Revision 1.7  2004/03/25 06:07:49  dsatish
 *  Commit After Sip_TransportInit function signature changes
 *
 *  Revision 1.6  2004/03/25 04:55:40  dsatish
 *  Commit after signature changes
 *
 *  Revision 1.5  2004/03/23 07:34:32  dsatish
 *  commit after doing proper indentation
 *
 *  Revision 1.4  2004/03/22 12:34:22  dsatish
 *  commit after the code review.
 *
 *  Revision 1.3  2004/03/19 13:54:22  dsatish
 *  Initial Check in of the Transport Layer source Code.
 *
 *
 ****************************************************************************/

#ifdef __sun
#define BSD_COMP
#endif

#include <sip_intern.h>
#include <sys/ioctl.h>

/*globals*/
ITS_THREAD  TRANS_thrId;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Return the actual index, which is ready to read in the trans table 
 *  
 *  Input Parameters:
 *  
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      None.
 *  
 *  Notes:
 *  
 *  See Also:
 ****************************************************************************/
static int 
SIP_GetActiveIndex(ITS_SockPollInfo *spInfo, ITS_INT noConn, 
                   SIP_TRANSPORT_INFO *trans)
{
    int i= 0 , j = 0;
    for (i = 0; i <= noConn; ++i)
    {
        if (spInfo[i].wasSet)
        {
            if (spInfo[i].sinfo->socket == trans->cntlFd[0])
            {
                char buf[1];
                read(spInfo[i].sinfo->socket, buf, 242);
                SIP_DEBUG(("SIP_GetActiveIndex:: Write on cntl fd \n"));
                break;
            }
            else
            {
                for (j = 0; j < trans->maxConn; ++j)
                {
                    if (trans->transTbl[j].portNo != 0)
                    {
                        if (spInfo[i].sinfo->socket 
                                == trans->spInfo[j].sinfo->socket)
                        {
                            break;
                        }
                    }
                }
            }            
            spInfo[i].wasSet = 0;
            return j;
        }
    }
    return ITS_ENOTFOUND;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      returns the available slot to sotre socket fd
 *
 *  Input Parameters:
 *      port number nd transport type
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      index or ITS_ENOTFOUND
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int  
SIP_TransportFindSlot(SIP_TRANSPORT_INFO *trans)
{
    int index  =0;
    
    for (index = 0; index < trans->maxConn; ++index)
    {
        if (trans->transTbl[index].portNo == 0)
        {
            return index;
        }
    }
    return ITS_ENOTFOUND;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Searches for the existing entry for given portno,ipaddress and type of
          the socket.
 *
 *  Input Parameters:
 *      port number nd transport type
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      index of type ITS_INTeger.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int  
SIP_TransportSearch(ITS_USHORT portNo, SOCK_IPv4Addr ip,
                    SIP_TRANSPORT_TYPE type, SIP_TRANSPORT_INFO *trans)
{
    int index  =0;
    
    for ( index = 0; index < trans->maxConn; ++index)
    {
        if (trans->transTbl[index].portNo == portNo &&
            trans->transTbl[index].type   == type   &&
            trans->transTbl[index].ipAddr == ip)
        {
            return index;
        }
    } 
    return ITS_ENOTFOUND;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      returns the available slot to sotre socket fd
 *
 *  Input Parameters:
 *      port number nd transport type
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      index or ITS_ENOTFOUND
 *
 *  Notes:
 *      This is local function , no mutex protection
 *  See Also:
 ****************************************************************************/
static int
SIP_AcceptConnection(ITS_INT index, SIP_TRANSPORT_INFO *trans)
{
    ITS_SocketInfo *newInfo = NULL;
    int ret = 0;

    /* if it is server so what , we should call accept */
    ret = SOCK_ServerAccept(trans->spInfo[index].sinfo,
                            &newInfo); 
    if (ret  != ITS_SUCCESS)
    {
        SIP_ERROR(("SIP_TransportCreate:: Failed create accept\n"));
        return ret;
    }
    
    index = SIP_TransportFindSlot(trans);
    if (index  == ITS_ENOTFOUND)
    {
        return  index;
    }

    trans->transTbl[index].portNo = SIP_TCP_REM_CLIENT; 
    trans->transTbl[index].ipAddr = SIP_TCP_REM_CLIENT; 
    trans->transTbl[index].type   = SIP_TCP_REM_CLIENT;
    trans->transTbl[index].refCnt++;

    /*Init sock poll info*/
    trans->spInfo[index].sinfo   = newInfo;
    trans->spInfo[index].lookFor = SOCK_POLL_READ;
    
    SIP_DEBUG(("SIP_AcceptConnection::accepted connection index = %d\n",index));
    trans->currConn++;

    trans->isUpdated = ITS_TRUE;
    return index;
} 

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Deletes the TCP tranaport entry for the given index .
 *
 *  Input Parameters:
 *       index.
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      ITS_SUCCESS or Error  code 
 *
 *  Notes:
 *       this local function only, not mutex protected 
 *  See Also:
 ****************************************************************************/
static int 
SIP_DeleteTCPTransport(ITS_INT index, SIP_TRANSPORT_INFO *trans)
{
    if (trans->transTbl[index].portNo == trans->tcpPortNo )
    {
        return ITS_SUCCESS;
    }
    
    SIP_DEBUG(("Deleting TCP transport as remote side closed its connection"
               " Index = %d \n", index));

    if (trans->transTbl[index].refCnt == 0)
    {   
        SIP_WARNING(("Aleardy deleted index = %d \n", index));
        return ITS_SUCCESS;
    }
    trans->transTbl[index].refCnt--;

    if (trans->transTbl[index].refCnt == 0)
    {
        SIP_DEBUG(("SIP_TransportDelete :: deleting transport port %d\n",
                    trans->transTbl[index].portNo));

        /* This is imp */
        trans->transTbl[index].portNo = 0;

        /*set the update flag */
        trans->isUpdated = ITS_TRUE;

        SOCK_Close(trans->spInfo[index].sinfo);
        trans->spInfo[index].sinfo = NULL;

        trans->currConn--;
    }
    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function poll on the socket for events from network
        On getting any notification. 
 *  
 *  Input Parameters:
 *  
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      None.
 *  
 *  Notes:
 *    
 *  See Also:
 ****************************************************************************/
static void *
SIP_TransportWait(void *tr)
{
    int ret = 0;
    SIP_TRANSPORT_INFO *trans = (SIP_TRANSPORT_INFO *)tr;
    ITS_SockPollInfo *lPoll = 
       (ITS_SockPollInfo *)ITS_Calloc(trans->maxConn, sizeof(ITS_SockPollInfo));
    ITS_USHORT noConn =0, i = 0;
    ITS_INT noDesc = 0;

    SIP_DEBUG(("SIP_TransportWait:: Entry ---\n"));
    
    while (trans->isUp)
    {
        /* make local copy only if there is any change */
        if (trans->isUpdated)
        {
            if (MUTEX_AcquireMutex(&trans->transMutex) != ITS_SUCCESS)
            {
                break;    
            }

            /*Critical section, copy all values in to local */
            for (i = 0, noConn = 0; i < trans->maxConn; ++i)
            {
                if (trans->transTbl[i].portNo != 0)
                {
                    memcpy(&lPoll[noConn], &trans->spInfo[i], 
                           sizeof(ITS_SockPollInfo));
                    noConn++;
                }
            }
            trans->isUpdated = ITS_FALSE;
            MUTEX_ReleaseMutex(&trans->transMutex);
        }

        noDesc = SOCK_Poll(lPoll, noConn, 10000);
        if (noDesc > 0)
        {
        }
        else if (noDesc == 0)
        {
            /* select time out */
            continue;
        }
        else if (noDesc < 0)
        {
            if (MUTEX_AcquireMutex(&trans->transMutex) != ITS_SUCCESS)
            {
                SIP_ERROR(("Mutex acquire failed :: Trans exiting \n"));
                break;    
            }
            ret = SIP_GetActiveIndex(lPoll, noConn, trans);
            if (ret != ITS_ENOTFOUND)
            {
                SIP_ERROR(("SOCK_Poll Error on Port %d\n", 
                            trans->transTbl[ret].portNo)); 
            }
            else
            {
                SIP_ERROR(("SIP_TransportWait:: SOCK_Poll Error Unkown\n")); 
            }
            MUTEX_ReleaseMutex(&trans->transMutex);
            continue;
        }
        
        /* 
         * This complte block is a critical section,
         * some thing went wrong in transport design
         * Do not call any function which has this mutex
         * lock in it, its not a recurssive lock
         */
        if (MUTEX_AcquireMutex(&trans->transMutex) != ITS_SUCCESS)
        {
            SIP_ERROR(("Mutex acquire failed :: Trans exiting \n"));
            break;    
        }

        while(noDesc > 0)
        {
            int index = 0;
            SIP_EVENT *sipEvent = NULL;
            ITS_EVENT event ;

            index = SIP_GetActiveIndex(lPoll, noConn, trans);
            if (index == ITS_ENOTFOUND)
            {
                noDesc--;
                continue;
            }
            
            if (trans->transTbl[index].type == SIP_TCP_SERVER)
            {
                SIP_AcceptConnection(index, trans);
            }
            else
            {
                struct sockaddr_in from;
                int from_len = sizeof(from);
                int noBytes = 0;
                ITS_CHAR *buf = 0;
                SOCK_IPv4Addr ipAddr = 0;
                ITS_USHORT portNo = 0;

                ret = ioctl(trans->spInfo[index].sinfo->socket, 
                            FIONREAD, &noBytes); 
                if (ret < 0 || noBytes == 0)
                {
                    SIP_DEBUG(("ioctl ret = %d,  port  %d, Nobytes  %d \n",
                                ret, trans->transTbl[index].portNo, noBytes ));

                    /* This could be because some TCP client disconnected */
                    SIP_DeleteTCPTransport(index, trans);
                    noDesc--;
                    continue;      
                }

                /* allocate exact buf required */
                buf = ITS_Malloc(noBytes + 1); 
                sipEvent = (SIP_EVENT *) ITS_Malloc( sizeof(SIP_EVENT));
                sipEvent->msg = NULL;

                if (trans->transTbl[index].type == SIP_UDP)
                {
                    ret = SOCK_Recv(trans->spInfo[index].sinfo, buf, noBytes,
                                                           &from, &from_len);
                    ipAddr = from.sin_addr.s_addr;
                    portNo = from.sin_port;

                    sipEvent->dest.ipAddr = ipAddr;
                    sipEvent->dest.portNo = portNo;
                }
                else
                {       
                    ret = SOCK_Read(trans->spInfo[index].sinfo, buf, noBytes);

                    sipEvent->dest.ipAddr = trans->transTbl[index].ipAddr;
                    sipEvent->dest.portNo = trans->transTbl[index].portNo;
                }

                if (ret < 0)
                {
                    if (ret == EBADF)
                        SIP_ERROR(("invalid file descriptor.\n"));

                    if (ret == EIO)
                        SIP_ERROR(("An I/O error\n"));

                    if (ret == ENOMEM)
                        SIP_ERROR(("insufficient user memory\n"));

                    if (ret == ENOTSOCK)
                        SIP_ERROR(("Not a socket\n"));

                    noDesc--;
                    continue;
                }

                /* set '\0' at the end */
                buf[noBytes] = 0;

                buf[ret] = 0;
                sipEvent->buf = buf;

                sipEvent->dest.transType = trans->transTbl[index].type;
                sipEvent->dest.transIndex = index;

                event.src = ITS_SIP_TRANSPORT_SRC;
                event.len = 0;
                event.data = (ITS_OCTET *) sipEvent;

                ret = TRANSPORT_PutEvent(ITS_SIP_SRC, &event);
                if (ret != ITS_SUCCESS)
                {
                    ITS_Free(sipEvent->buf);
                    SIP_EVENT_TERM(sipEvent);
                }
                SIP_DEBUG(("Send event to SIP TRNASACTION layer\n"));
            }
            noDesc--;
        }
        MUTEX_ReleaseMutex(&trans->transMutex);
    }
    SIP_CRITICAL(("------ Exiting Transport thread -----\n"));
    return NULL;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Initialises transport
 *      Initialises the mutex lock
 *  Input Parameters:
 *      trans - of type ptr SIP_TRANSPORT_INFO 
 *      
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int 
SIP_TransportInit(SIP_TRANSPORT_INFO *trans)
{
    int ret =0  , i = 0;

    SIP_DEBUG(("Enter ::Transport_Init()    \n"));

    if ((ret = MUTEX_CreateMutex(&trans->transMutex, 0))  != ITS_SUCCESS)
    {
        SIP_ERROR(("Mutex create failed \n"));
        return  ret;
    }

    trans->currConn = 0;

    /* Allocate memory for tables */
    trans->transTbl = ITS_Calloc(trans->maxConn, sizeof(SIP_TRANS_TBL));
    trans->spInfo   = ITS_Calloc(trans->maxConn, sizeof(ITS_SockPollInfo));

    for (i = 0; i < trans->maxConn; ++i)
    {
        trans->transTbl[i].portNo = 0;
        trans->transTbl[i].refCnt = 0;
        trans->transTbl[i].type   = 0;
        trans->spInfo[i].sinfo    = NULL;
    } 

    /* Create default UDP transport */
    ret = SIP_TransportCreate(trans->ipAddr, trans->udpPortNo, SIP_UDP, trans);
    if (ret < ITS_SUCCESS)
    {
        ITS_Free(trans->spInfo);
        ITS_Free(trans->transTbl);
        return ITS_ENOSOCKET;
    }

    /* Create default TCP server transport */
    ret = SIP_TransportCreate(trans->ipAddr, trans->tcpPortNo,
                              SIP_TCP_SERVER, trans);
    if (ret < ITS_SUCCESS)
    {
        ITS_Free(trans->spInfo);
        ITS_Free(trans->transTbl);
        return ITS_ENOSOCKET;
    }
    
    /* Create contrl fd */
    ret = pipe(trans->cntlFd);
    if (ret != 0)
    {
        SIP_ERROR(("Error in creating control fd \n"));
    }
    else
    {
        ITS_SocketInfo *fdInfo = NULL;
        fdInfo = ITS_Malloc(sizeof(ITS_SocketInfo));

        fdInfo->socket = trans->cntlFd[0];
        fdInfo->type = 0;
        fdInfo->addr = 0;

        /* Init table, put some invalid port */
        trans->transTbl[trans->currConn].portNo = SIP_INVALID_PORT;
        trans->transTbl[trans->currConn].type   = 0;
        trans->transTbl[trans->currConn].refCnt++;


        /*Init sock poll info*/
        trans->spInfo[trans->currConn].sinfo   = fdInfo;
        trans->spInfo[trans->currConn].lookFor = SOCK_POLL_READ;

        trans->currConn++;
    }

    trans->isUp      = ITS_TRUE;
    trans->isUpdated = ITS_TRUE;

    /* Create Wait thr for transport */
    if ((ret  = THREAD_CreateThread(&TRANS_thrId, 0, SIP_TransportWait,
                (void *)trans, ITS_TRUE)) != ITS_SUCCESS)
    {
        SIP_DEBUG(("Thread create failed \n"));
        ITS_Free(trans->spInfo);
        ITS_Free(trans->transTbl);
        return ret;
    }
    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Deletes the entry for the given index .
 *
 *  Input Parameters:
 *       index.
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      ITS_SUCCESS or Error  code 
 *
 *  Notes:
 *      
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int 
SIP_TransportDelete(ITS_INT index, SIP_TRANSPORT_INFO *trans)
{
    if (MUTEX_AcquireMutex(&trans->transMutex) != ITS_SUCCESS)
    {
        return ITS_EBADMUTEX;
    }

    if (trans->transTbl[index].portNo == trans->udpPortNo ||
        trans->transTbl[index].portNo == trans->tcpPortNo )
    {
        MUTEX_ReleaseMutex(&trans->transMutex);
        return ITS_SUCCESS;
    }

    if (trans->transTbl[index].type == SIP_TCP_REM_CLIENT)
    {
        /* 
         * If this connection is made by remote end, you don't
         * close it, let other end take care of it
         */
        MUTEX_ReleaseMutex(&trans->transMutex);
        return ITS_SUCCESS;
    }

    SIP_DEBUG(("Deleting <<< port#  %d >>>, <<< Index %d >>> <<refCnt  %d>>\n", 
                trans->transTbl[index].portNo,
                index, trans->transTbl[index].refCnt));

    if (trans->transTbl[index].refCnt == 0)
    {   
        SIP_DEBUG(("Aleardy deleted index = %d \n", index));
        MUTEX_ReleaseMutex(&trans->transMutex);
        return ITS_SUCCESS;
    }
    trans->transTbl[index].refCnt--;

    if (trans->transTbl[index].refCnt == 0)
    {
        SIP_DEBUG(("SIP_TransportDelete :: deleting transport port %d\n",
                    trans->transTbl[index].portNo));

        /* This is imp */
        trans->transTbl[index].portNo = 0;

        /*set the update flag */
        trans->isUpdated = ITS_TRUE;

        /* Wake up the select */
        write(trans->cntlFd[1], (void *)trans, 1);
        TIMERS_USleep(10000);
        
        SOCK_Close(trans->spInfo[index].sinfo);
        trans->spInfo[index].sinfo = NULL;

        trans->currConn--;
    }
    MUTEX_ReleaseMutex(&trans->transMutex);
    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Creates the socket for requested port no. Also binds the socket with
 *         given ip address.
 *
 *  Input Parameters:
 *      SOCK_IPv4Addr  ip -  ip address
 *      ITS_INT    portno
 *       SIP_TRANSPORT_TYPE    type - UDP or TCP or SCTP.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returns the index value of type ITS_INTeger.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SIP_TransportCreate(SOCK_IPv4Addr ip, int portno,
                    SIP_TRANSPORT_TYPE type, SIP_TRANSPORT_INFO *trans)
{
    int index = 0 ,ret =0;
    ITS_SocketInfo *sockInfo = NULL;
    char ipAddr[16];

    ipAddr[0] = 0;
    SOCK_IPv4AddrToName(ipAddr, SOCK_NToHL(ip));

    if (MUTEX_AcquireMutex(&trans->transMutex) != ITS_SUCCESS)
    {
        return ITS_EBADMUTEX;
    }

    if (trans->currConn >= trans->maxConn)
    {
        SIP_ERROR(("SIP_TransportCreate:: Failed  max connections exeeded\n"));
        MUTEX_ReleaseMutex(&trans->transMutex);
        return ITS_ENOMEM;
    }

    index = SIP_TransportSearch(portno, ip, type, trans);
    if (index != ITS_ENOTFOUND)
    {
        SIP_DEBUG(("Entry found for <<< port#  %d >>>  <<< Index  %d >>> \n",
                     portno, index));
        trans->transTbl[index].refCnt++;
        MUTEX_ReleaseMutex(&trans->transMutex);
        return index;
    }

    switch (type)
    {
    case SIP_UDP:
        ret = SOCK_EndPointOpen(&sockInfo, INET_DOMAIN, ipAddr, portno);
        if (ret  != ITS_SUCCESS)
        {
            SIP_ERROR(("SIP_TransportCreate:: Failed create port %d ,IP %s\n",
                        portno, ipAddr));
            MUTEX_ReleaseMutex(&trans->transMutex);
            return ret;
        }
        break;
    case SIP_TCP_CLIENT:
        /* If it is tcp client, these must be server addr & port*/
        ret = SOCK_ClientOpen(&sockInfo, INET_DOMAIN, ipAddr, portno);
        if (ret  != ITS_SUCCESS)
        {
            SIP_ERROR(("SIP_TransportCreate:: Failed create port %d\n",
                        portno));
            MUTEX_ReleaseMutex(&trans->transMutex);
            return ret;
        }

        ret = SOCK_ClientConnect(sockInfo);
        if (ret  != ITS_SUCCESS)
        {
            SIP_ERROR(("SIP_TransportCreate:: Failed create port %d\n",
                        portno));
            MUTEX_ReleaseMutex(&trans->transMutex);
            return ret;
        }
        break;

    case SIP_TCP_SERVER:
        ret = SOCK_ServerOpen(&sockInfo, INET_DOMAIN, ipAddr, portno);
        if (ret  != ITS_SUCCESS)
        {
            SIP_ERROR(("SIP_TransportCreate:: Failed create port %d\n",
                        portno));
            MUTEX_ReleaseMutex(&trans->transMutex);
            return ret;
        }
        break;
        
    case SIP_SCTP_CLIENT:
        break;
    case SIP_SCTP_SERVER:
        break;
    default:
        break;
    }

    index = SIP_TransportFindSlot(trans);
    if (index  == ITS_ENOTFOUND)
    {
        MUTEX_ReleaseMutex(&trans->transMutex);
        return  index;
    }

    /* Init table */
    trans->transTbl[index].portNo = portno;
    trans->transTbl[index].ipAddr = ip;
    trans->transTbl[index].type   = type;
    
    trans->transTbl[index].refCnt++;

    /*Init sock poll info*/
    trans->spInfo[index].sinfo   = sockInfo;
    trans->spInfo[index].lookFor = SOCK_POLL_READ;
    
    trans->currConn++;

    SIP_DEBUG(("Creating <<< port#  %d >>>, <<< index  %d>>> \n",
                trans->transTbl[index].portNo,
                index));

    /*set the update flag */
    trans->isUpdated = ITS_TRUE;

    /*Interrupt select */
    write(trans->cntlFd[1], (void *)trans, 1);

    MUTEX_ReleaseMutex(&trans->transMutex);
    return index;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Sends the given data to the destination address
 *
 *  Input Parameters:
 *      SIP_DEST_INFO destinfo
 *      ITS_INT       index
 *      ITS_CHAR *buf  encoded message buffer
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS or error code
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int 
SIP_TransportSend(SIP_DEST_INFO *destInfo,
                          ITS_INT index,
                          ITS_CHAR *buf,
                          SIP_TRANSPORT_INFO *trans)
{
    ITS_INT ret = 0;
    ITS_CHAR addr[16];

    addr[0]= 0;
    SOCK_IPv4AddrToName(addr, SOCK_NToHL(destInfo->ipAddr));
    SIP_DEBUG(("Sending <<< IP Addr  = %s >>>, <<< Rport = %d >>>\n",
               addr, SOCK_NToHS(destInfo->portNo)));

    if (MUTEX_AcquireMutex(&trans->transMutex) != ITS_SUCCESS)
    {
        return ITS_EBADMUTEX;
    }

    SIP_DEBUG(("SIP_TransportSend:: Index %d,  Lport#  %d \n",
               index, trans->transTbl[index].portNo));

    if (index >= trans->maxConn)
    {
        return ITS_EINVALIDARGS;
    }
    if (trans->transTbl[index].type == SIP_UDP)
    {
        struct sockaddr_in to;
        to.sin_addr.s_addr = destInfo->ipAddr;
        to.sin_port = destInfo->portNo;
        to.sin_family = AF_INET;

        ret =SOCK_Send(trans->spInfo[index].sinfo, 
                       buf, strlen(buf), &to, sizeof(to));
    }
    else
    {   
        ret = SOCK_Write(trans->spInfo[index].sinfo, buf, strlen(buf));
    }
    
    if(ret !=  strlen(buf))
    {
        SIP_ERROR(("SIP_TransportSend: could not send message "));
        ret = SIP_TRANSPORT_SEND_FAILED;
    }
    else
    {
        ret = ITS_SUCCESS;
    }

    MUTEX_ReleaseMutex(&trans->transMutex);

    SIP_DEBUG(("Exited Send ret = %d\n", ret));
    return ret;
}

