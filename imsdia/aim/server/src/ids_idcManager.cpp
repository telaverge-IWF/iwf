/****************************************************************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *
 * ID: $Id: ids_idcManager.cpp,v 1.22.6.4.6.2 2013/04/01 05:38:44 vsarath Exp $
 * ID: $Id: ids_idcManager.cpp,v 1.22.6.4.6.2 2013/04/01 05:38:44 vsarath Exp $
 * LOG:
 *  LOG: $Log: ids_idcManager.cpp,v $
 *  LOG: Revision 1.22.6.4.6.2  2013/04/01 05:38:44  vsarath
 *  LOG: Fix for Coverity warnings
 *  LOG:
 *  LOG: Revision 1.22.6.4.6.1  2013/02/27 08:49:06  jvikram
 *  LOG: Warnings raised by Coverity have been fixed
 *  LOG:
 *  LOG: Revision 1.22.6.4  2012/11/20 17:39:44  pramana
 *  LOG: Merged from CMAPI branch for 212-07 release
 *  LOG:
 *  LOG: Revision 1.22.30.2  2012/11/20 10:16:59  rgovardhan
 *  LOG: merge from 00 Nov20Rel
 *  LOG:
 *  LOG: Revision 1.22.30.1  2012/11/06 09:45:58  millayaraja
 *  LOG: merge from B-DRE-0212-00 branch
 *  LOG:
 *  LOG: Revision 1.22.6.1  2012/11/05 12:10:11  pramana
 *  LOG: Fix for coverity issue 10567
 *  LOG:
 *  LOG: Revision 1.22.24.1  2012/11/05 10:17:41  ncshivakumar
 *  LOG: iCoverity Fixes
 *  LOG:
 *  LOG: Revision 1.22  2010/09/22 05:27:27  nvijikumar
 *  LOG: GlobalUniqueAddr based routing/distribution support
 *  LOG:
 *  LOG: Revision 1.21  2010/08/19 11:23:06  nvijikumar
 *  LOG: Porting changes from B-MOTO-IDIA-0421-00
 *  LOG: 1. New Overload implimentation changes are not being ported.
 *  LOG: 2. Force disconnect changes are not being ported.
 *  LOG:
 *  LOG: Revision 1.20  2009/08/24 11:51:54  rajeshak
 *  LOG: changes for non-blocking accept.
 *  LOG:
 *  LOG: Revision 1.19  2009/07/13 05:59:42  rajeshak
 *  LOG: Bug fix in IdcSockReader.
 *  LOG:
 *  LOG: Revision 1.18  2009/06/29 14:38:19  rajeshak
 *  LOG: HMI Changes to improve the performance.
 *  LOG:
 *  LOG: Revision 1.17  2009/06/10 03:27:28  rajeshak
 *  LOG: Check whether socketId is valid or not(SIGPIPE issue fix when IDC is killed)
 *  LOG:
 *  LOG: Revision 1.16  2009/04/10 06:42:57  sureshj
 *  LOG: Removed comppilation flag HMI_ENABLE & added dynamic configuration.
 *  LOG:
 *  LOG: Revision 1.15  2009/04/07 14:06:04  sureshj
 *  LOG: HMI monitoring is enabled for IdcSockReader thread.
 *  LOG:
 *  LOG: Revision 1.14  2009/03/19 12:32:23  rajeshak
 *  LOG: Klockwork Issue Fix.
 *  LOG:
 *  LOG: Revision 1.13  2009/03/19 08:34:24  nvijikumar
 *  LOG: Reverted back HMI changes
 *  LOG:
 *  LOG: Revision 1.12  2009/03/16 11:49:05  sureshj
 *  LOG: FeatureId: HMI enhancement for monitoring raw threads.
 *  LOG: Description:Diameter  Threads added to HMI monitor list.
 *  LOG:
 *  LOG: Revision 1.11  2009/03/07 08:48:31  nvijikumar
 *  LOG: Trace enhanced
 *  LOG:
 *  LOG: Revision 1.10  2009/03/03 11:10:47  rajeshak
 *  LOG: Klockwork reported issue fix
 *  LOG:
 *  LOG: Revision 1.9  2009/02/19 08:35:22  nvijikumar
 *  LOG: Dispatch dedicated Sender thread and queue only if _IDS_SENDER_THR defined
 *  LOG:
 *  LOG: Revision 1.8  2009/02/19 05:51:27  nvijikumar
 *  LOG: New API exposed to ClientHandler for writing an event
 *  LOG:
 *  LOG: Revision 1.7  2009/02/12 04:10:49  nvijikumar
 *  LOG: IDS Layer bypass changes:
 *  LOG: Same functionality exists only task Queue and Thread removed
 *  LOG:
 *  LOG: Revision 1.6  2009/01/09 09:08:40  nvijikumar
 *  LOG: Raising alarm when received failed
 *  LOG:
 *  LOG: Revision 1.5  2009/01/07 07:22:08  nvijikumar
 *  LOG: Fix for IDS exiting issue when IDC is killed during load
 *  LOG:
 *  LOG: Revision 1.4  2009/01/06 13:42:09  nvijikumar
 *  LOG: Fixes for valgrind reported issues
 *  LOG:
 *  LOG: Revision 1.3  2009/01/04 09:48:48  nvijikumar
 *  LOG: Support for 64 Peers with select
 *  LOG:
 *  LOG: Revision 1.2  2009/01/04 06:54:29  nvijikumar
 *  LOG: Some more updates
 *  LOG:
 *  LOG: Revision 1.1  2009/01/04 06:37:14  nvijikumar
 *  LOG: Platform transport replaced with new TCP transport to handle IDC traffic
 *  LOG: To limit number of threads with multiple connections
 *  LOG:
 ****************************************************************************/
#ident "$Id: ids_idcManager.cpp,v 1.22.6.4.6.2 2013/04/01 05:38:44 vsarath Exp $"

/*
 * System header files
 */
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <arpa/nameser.h>
#include <math.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/ioctl.h>

#if defined(linux) && !defined(USE_SELECT)
#include<sys/epoll.h>
#endif

#include <ids_idcManager.h>
#include <ids_clientinterface.h>
#include <ids_msghandler.h>
#include <ids_routedb.h>
#include <ids_conndb.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif

/* 
 * Static Global declarations accessed by Acceptor and Reader Threads
 */
static int lastFd;
static fd_set readfds;

#if !defined(linux) || defined(USE_SELECT)
static unsigned int maxConnsIndex;
static TCP_SOCK_INFO *desc[IDS_MAX_CONNS];
#else
#define EPOLL_RUN_TIMEOUT 1000
static int epfd;
#endif

/* Global variables */
extern ConnectionTable conTable;
extern RouteTable routeTable;
extern MsgHandler *msgHandler;
/* Singleton class */
static IdcTransManager *idcTransManager = NULL;

int ParseIdcTransInfo()
{
    char *ipAddr = NULL;
    int port = 0;

    bool ipFlag = false, portFlag =false;
    char key[ITS_PATH_MAX];
    char value[ITS_PATH_MAX];
    ITS_ResourceManager *rf = new
                 ITS_ResourceManager(APPL_GetConfigFileName());

    rf->Lock();
    rf->Rewind(NULL);

    while (rf->GetKeyName(NULL, key, ITS_PATH_MAX) == ITS_SUCCESS &&
           rf->GetKeyValue(NULL, value, ITS_PATH_MAX) == ITS_SUCCESS)
    {
        if (strcmp(key, "IdcTcpTransIp") == 0)
        {
            //fix for the coverity issue CID 10566
            //Fix for memory leak.Free ipAddr if not free
            if(ipAddr != NULL)
            {
                free(ipAddr);
                ipAddr = NULL;
            }
            ipAddr = strdup(value);
            ipFlag = true;
        }

        if (strcmp(key, "IdcTcpTransPort") == 0)
        {
            port = atoi(value);
            portFlag = true;
        }
    }
    rf->Unlock();

    delete rf;

    DT_DBG(("IP Added = %s Port = %d\n",ipAddr,port));
    if (ipFlag && portFlag)
    {
        (ClientHandler::GetClientHandler())->SetServerIPAddr(ipAddr);
        (ClientHandler::GetClientHandler())->SetServerPort(port);
      
        if(ipAddr)
        {
            free(ipAddr);
        }  
        return ITS_SUCCESS;
    }

    if(ipAddr)
    {
        free(ipAddr);
    }

    return !ITS_SUCCESS;
}

int
IdcReadWriteUtils::ReadEvent(ITS_INT sd, ITS_EVENT *ev)
{
    ITS_INT nread = 0, ret =0;
    char buf;
    ITS_USHORT tmp =0;
    ITS_OCTET evtInfo[2*sizeof(ITS_USHORT)]  = { 0 };

    DT_DBG(("IdcReadWriteUtils::ReadEvent"));

    /* read the source */
    ret = Read(sd, (char *)evtInfo, sizeof(ITS_UINT));

    if (ret != sizeof(ITS_UINT))
    {
        return (ITS_ERCVFAIL);
    }
    /* First 2 bytes contains evt->src) */
    memcpy(&tmp, &evtInfo[0], sizeof(ITS_USHORT));
    ev->src  = SOCK_NToHS(tmp);

    /* Next 2 bytes contains evt->len) */
    memcpy(&tmp, &evtInfo[2], sizeof(ITS_USHORT));
    ev->len  = SOCK_NToHS(tmp);

    ev->data = (ITS_OCTET *)malloc(ev->len);
    if (ev->data == NULL)
    {
        return (ITS_ENOMEM);
    }

    /* read the data */
    if (ev->len)
    {
      nread = Read(sd, (char *)ev->data, ev->len);

        if (nread != ev->len)
        {
            free(ev->data);
            ev->data = NULL;

            return (ITS_ERCVFAIL);
        }
    }
    return (ITS_SUCCESS);
}

int 
IdcReadWriteUtils::WriteEvent(IDS_TRANS_INFO* trInfo, ITS_EVENT *ev)
{
    int ret = ITS_SUCCESS;
    MUTEX_AcquireMutex(&trInfo->wMutex);
    if((ret = WriteEvent(trInfo->u.tcpInfo, ev)) != ITS_SUCCESS)
    {
        DT_ERR(("IdcReadWriteUtils::WriteEvent failed"));
    }
    MUTEX_ReleaseMutex(&trInfo->wMutex);
    ITS_EVENT_TERM(ev);
    return ret;
}
int
IdcReadWriteUtils::WriteEvent(ITS_INT sd, ITS_EVENT *ev)
{
    int ret, nrite;
    ITS_USHORT tmp =0;
    ITS_OCTET evtInfo[2*sizeof(ITS_USHORT)] = {0};
    if (ev->len)
    {
        /* First 2 bytes contains evt->src) */
        tmp = SOCK_HToNS(ev->src);
        memcpy(&evtInfo[0], &tmp, sizeof(ITS_USHORT));

        /* Next 2 bytes contains evt->len) */
        tmp = SOCK_HToNS(ev->len);
        memcpy(&evtInfo[2], &tmp, sizeof(ITS_USHORT));

        struct sockaddr addr;
        socklen_t addrSz = sizeof(struct sockaddr);
        if (getpeername(sd, &addr, &addrSz) != 0)
        {
            DT_ERR(("getpeername failed...errno = %d\n\n", errno));
            return (ITS_EBADSOCKET);
        }

        ret = Write(sd,(char *)evtInfo, sizeof(ITS_UINT));
        if (ret != sizeof(ITS_UINT))
        {
            return (ITS_ESENDFAIL);
        }

        /* Write Payload */
        nrite = Write(sd, (char *)ev->data, ev->len);

        if (nrite != (ITS_INT)ev->len)
        {
            /* Free the event*/
            if (ev->data)
            {
                free(ev->data);
                ev->data = NULL;
            }

            return (ITS_ESENDFAIL);
        }
    }
    return (ITS_SUCCESS);
}


/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_Read.
 *
 *  Purpose:
 *      Read whatever data is on the socket, keep doing it until we get all
 *      data or a closed peer
 *
 *  Input Parameters:
 *      int sock                       file descriptor of this socket
 *      char *buf                      pointer to where you want to stick data
 *      int nbytes                     the number of bytes you expect to read
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *  0                    peer has closed connection or there was an error
 *                       and thus far no data has been read
 *
 *  >0                   This much data has been read.  There may or
 *                       may not have been an error.
 ****************************************************************************/
int
IdcReadWriteUtils::Read(int sd, char *buf, int nbytes)
{
    int     nleft;                    /* Amount of data left to read */
    int     nread;                    /* Amount of data we have read */
    int     done = ITS_FALSE;             /* Loop terminator for EOF      */

    /* Set up how much we want to read */
    nleft = nbytes;

    if (sd <= 0)
    {
        return (0);
    }

    /* While not error or EOF and there is more data expected... */
    while ((nleft > 0) && (!done))
    {
        /* Read something */
        nread = read(sd, buf, nleft);

        /*
         * If there was an error return # of bytes read thus far
         * (how odd..)
         */
        if (nread < 0)
        {
            return nread;
        }

        /* If there is an EOF set while to exit */
        else if (nread == 0)
        {
            done = ITS_TRUE;
        }

        /* We read some data */
        else
        {
            nleft -= nread;
            buf += nread;
        }
    }

    /* Return the amount of data we read */
    return (nbytes - nleft);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_Write.
 *
 *  Purpose:
 *      Write a fixed amount of data (or as much as you can) out over a socket
 *
 *  Input Parameters:
 *      int sock             file descriptor of socket
 *      char *buf            pointer to data to write out
 *      int nbytes           size of data to write
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      0                   Some sort of error occured and no data send
 *      other               Amount of data that was sent (which could be less
 *                          than requested)
 ****************************************************************************/
int
IdcReadWriteUtils::Write(int sd, char *buf, int nbytes)
{
    int    nleft;
    int    nwritten;

    /* Set up how much we need to write */
    nleft = nbytes;

    if (sd <= 0)
    {
        return (0);
    }

    /* While still bytes to write do so */
    while (nleft > 0)
    {
        /* Write some data */
        nwritten = write(sd, buf, nleft);

        /* If any of these errors return # actually written */
        if (nwritten <= 0 &&
            (errno != EINTR &&   errno != EBUSY &&
             errno != EDEADLK && errno != EWOULDBLOCK &&
             errno != EINPROGRESS))    /* error, or zero length write */
        {
            return nwritten;
        }

        /* else adjust counters and keep going */
        else
        {
            /*
             * If the return code was -1 (error) set to zero so we
             * do not end up losing data!!!
             */
            if (nwritten == -1)
            {
                nwritten = 0;
            }
            /*
             * Note that the buf pointer is incremented as opposed to
             * doing a write to buf+nwritten (which might have been a
             * bit more clear).
             */
            nleft -= nwritten;
            buf += nwritten;
        }
    }

    /* Return how much we actually wrote */
    return (nbytes - nleft);
}

int
IdcTxQueueHandler::HandleMessage(DIAThread *thr, its::Event &ev)
{
    int ret = ITS_SUCCESS;
    int sockFd;
    DT_DBG(("IdcTxQueueHandler::HandleMessage"));
   
    sockFd = ev.GetSource();
    ev.SetSource(ITS_APP_SRC);

    ret = WriteEvent(sockFd, &ev.GetEvent());
    if (ret != ITS_SUCCESS)
    {
        DT_CRT(("IdcTxQueueHandler::write Event failed"));
    }
    return ITS_SUCCESS;
}

int
IdcSockReader::HandleReadEvent(int sockId)
{
    ITS_EVENT ev;
    int ret = ReadEvent(sockId,&ev);
    if (ret != ITS_SUCCESS)
    {
        DT_CRT(("HandleReadEvent::Read Failure"));
        if (ret == ITS_ERCVFAIL)
        {
            DIA_Alarm(15102, __FILE__, __LINE__,"ret =%d Inst = %d",
                                  ret, sockId);

            ClientHandler::GetClientHandler()->CleanUP(sockId);
            close(sockId);
        }
        return ret;
    }
    ITS_EVENT *evt = &ev;
    if (evt->src != IDS_APPDATA_SRC)
    {
        if ((evt->len > IDS_MIN_MSG_SIZE) &&
            (evt->data[IDS_MSG_TYPE_POS] == REGISTER_MSG))
        {
            DT_DBG(("TcpReceiver: Register from client"));

            ClientHandler::GetClientHandler()->Register(sockId, evt);
        }
        else if ((evt->len > IDS_MIN_MSG_SIZE) &&
                (evt->data[IDS_MSG_TYPE_POS] == DEREGISTER_MSG))
        {
            DT_DBG(("TcpReceiver:DeRegister frm client"));
            ClientHandler::GetClientHandler()->DeRegister(sockId, evt);

        }
        else if ((evt->len > IDS_MIN_MSG_SIZE) &&
                (evt->data[IDS_MSG_TYPE_POS] == GLOBAL_UNIQ_ADDR_MSG))
        {
            DT_DBG(("TcpReceiver:Global Uniq Addr frm client"));
            ClientHandler::GetClientHandler()->ProcessGlobalUniqAddrMsg(evt);

        }
        ITS_EVENT_TERM(evt);
    }
    else
    {
        if (msgHandler->ProcessAppMsg(evt) != ITS_SUCCESS)
        {
            DT_ERR((" Failed to process Message from IDC"));
        }
        ITS_EVENT_TERM(evt);
    }
    return ITS_SUCCESS;
}

void
IdcSockReader::Execute(void *arg)
{
    int ret, i;
    ITSDiaConfig *cfg = &itsDiaConfig;
    HMIThread_Info* hmiInfo = NULL;

#if !defined(linux) || defined(USE_SELECT)
    fd_set reads;
    struct timeval tv;
#else
    struct epoll_event events[IDS_MAX_CONNS];
#endif

    DT_DBG(("IdcSockReader::Execute"));
    ITS_INT thrID = THREAD_GetCurrentThreadID();
    hmiInfo = HMI_AddToMonList(&monList, "IdcSockReader", (ITS_THREAD*)thrID);

    while (!_doExit)
    {
        if(cfg->IsHMIEnabled())
        {
            HMI_ResetCounter(hmiInfo);
        }
#if !defined(linux) || defined(USE_SELECT)
        tv.tv_sec = 1;
        tv.tv_usec = 1;
        memcpy(&reads, &readfds, sizeof(readfds));
        ret =  select(lastFd+1, &reads, NULL, NULL, &tv);
        if (ret == 0)
        {
              continue ;
        }
        for(i=0;i<maxConnsIndex;i++)
        {
            if (desc[i] && FD_ISSET(desc[i]->socket, &reads))
            {
                ret = HandleReadEvent(desc[i]->socket);
                if (ret != ITS_SUCCESS)
                {
                    FD_CLR(desc[i]->socket, &reads);
                    free(desc[i]);
                    desc[i] = NULL;
                    continue;//
                }
                /* Check if mutex required */
                TCP_SOCK_RST_LASTUPDT(desc[i]);

            }
        }
#else
        // epoll procedure goes here
        ret = epoll_wait(epfd, events, IDS_MAX_CONNS, EPOLL_RUN_TIMEOUT);
        if (ret < 0)
        {
            DT_ERR (("epoll_wait failed "));
            continue ;
        }

        for(i=0;i<ret;i++)
        {
            if (events[i].data.ptr != NULL)
            {
                TCP_SOCK_INFO *info = (TCP_SOCK_INFO*)events[i].data.ptr;
                if (info != NULL)
                {
                    int rCode = HandleReadEvent(info->socket);
                    if (rCode != ITS_SUCCESS)
                    {
                        DT_ERR (("Failed to Read message from IDC"));
                        DIA_Alarm(15102, __FILE__, __LINE__,"ret =%d Inst = %d",
                                  rCode, info->socket);
                        free(info);
                        continue;
                    }
                    TCP_SOCK_RST_LASTUPDT(info);
                }
            }
        }
#endif
    }
    HMI_RemoveFromMonList(&monList, (ITS_THREAD*)thrID);
    delete this;
}

void
IdcSockAcceptor::Execute(void *arg)
{
    int    flag = 1;          /* for setsockopt() call */
    struct protoent    *ent;  /* protocol entry */
    int ret;
    int tIndex = 0;
    fd_set acptfd;
    fd_set tempfd;
    struct timeval tv;

    DT_DBG(("IdcSockAcceptor::Execute"));

    FD_ZERO(&readfds);
    FD_ZERO(&acptfd);
    FD_SET(_serSocket, &acptfd);

    ITSDiaConfig *cfg = &itsDiaConfig;
    HMIThread_Info* hmiInfo = NULL;
    ITS_INT thrID = THREAD_GetCurrentThreadID();
    hmiInfo = HMI_AddToMonList(&monList, "IdcConnAcceptor", (ITS_THREAD*)thrID);

    while (!_doExit)
    {
        if (_serSocket >= 0)
        {
            tv.tv_sec = 1;
            tv.tv_usec = 0;
            memcpy(&tempfd, &acptfd, sizeof(acptfd));
            ret =  select(_serSocket+1, &tempfd, NULL, NULL, &tv);

            if (_doExit)
            {
                break;
            }

            if(cfg->IsHMIEnabled())
            {
                HMI_ResetCounter(hmiInfo);
            }

            if (ret == 0)
            {
                continue ;
            }

            if (FD_ISSET(_serSocket, &tempfd))
            {
                int fd;
                struct sockaddr_un addr;
                socklen_t aSize = sizeof(struct sockaddr_un);

                fd = accept(_serSocket, (struct sockaddr *) &addr,
                           &aSize);
                if (fd <= 0)
                {
                    DT_CRT(("IdcSockAcceptor::Accept Failure"));
                    continue;
                }

                if (addr.sun_family == AF_INET &&
                          (ent = getprotobyname("tcp")) != NULL)
                {
                    setsockopt(fd, ent->p_proto,
                               TCP_NODELAY, (char *)&flag, sizeof(flag));
                }

                /* Store socket info */
                TCP_SOCK_INFO *info = (TCP_SOCK_INFO*)malloc(sizeof(TCP_SOCK_INFO));
                if (info == NULL)
                {
                    throw "Error: memory allocation failed";
                }

                info->socket = fd;
                TCP_SOCK_RST_LASTUPDT(info);
                lastFd = fd;
            
#if !defined(linux) || defined(USE_SELECT)
                tIndex = 0;
                while ((desc[tIndex] != NULL) && (tIndex < (maxConnsIndex-1)))
                {
                    tIndex++;
                }
            
                if ((desc[tIndex] == NULL) && tIndex < maxConnsIndex)
                {
                    desc[tIndex] = info;
                }
                else
                {
                    if (maxConnsIndex < IDS_MAX_CONNS)
                    {
                        desc[maxConnsIndex++] = info;
                    }
                    else
                    {
                        DT_ERR(("Max connections reached"));
                        free(info);
                        close(fd); 
                        continue;
                    }
                }
                FD_SET(fd, &readfds);
#else
                static struct epoll_event ev;
                ev.events = EPOLLIN | EPOLLPRI | EPOLLERR | EPOLLHUP;
                //ev.data.fd = fd;
                ev.data.ptr = info;
                if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd,&ev) < 0)
                {
                    DT_ERR(("Failed to add fd to epoll Check if Max Conns reached"));
                }
#endif
                if (_doExit)
                {
                    break;
                }

                /* Insert entry to HeartBeatHandler */
                HeartBeatHandler::GetHeartBeatHandler()->InsertHandle(fd, info);
            }
        }
    }
    HMI_RemoveFromMonList(&monList, (ITS_THREAD*)thrID);
    delete this;
}

IdcTransManager::IdcTransManager(int numThreads)
    :DIAModule(numThreads, IDS_TCP_SEND_MSG_QUEUE_NAME, IDS_TCP_SEND_MSG_QUEUE)
{
    /* create and register MsgHandler for Sock Write*/
    sockWrite    = new IdcTxQueueHandler();
    RegisterMessageHandler(sockWrite, ITS_NO_SRC);
  
    /* create Thread for Connection Acceptor */
    idcSockAcceptor = new IdcSockAcceptor;
   
    /* create Thread for to read from socke */
    idcSockReader = new IdcSockReader;
} 

IdcTransManager* 
IdcTransManager::GetIdcTransManager()
{
    if(idcTransManager == NULL)
    {
        idcTransManager = new IdcTransManager(1);
    }
    return idcTransManager;
}

int
IdcTransManager::StartMgr()
{
    int ret = ITS_SUCCESS;
    if (!CreateTcpTrans())
    {
        DT_CRT (("IdcTransManager:: CreateTcpTrans Failed")); 
        return !ITS_SUCCESS;
    }
    /* Start Sock Write Thread */ 
    /* Dispatch dedicated sender thread and queue only if _IDS_SENDER_THR
     * is defined
     */
#if _IDS_SENDER_THR
    this->Start();
#endif
    /* Start Sock Acceptor Thread */ 
    idcSockAcceptor->Start();
    /* Start Sock Reader Thread */ 
    idcSockReader->Start();

    signal(SIGPIPE,SIG_IGN);
    return ret;
}

bool
IdcTransManager::CreateTcpTrans(void)
{
    int aSize;
    int dummy = 1;
    int _socket;
    struct sockaddr_in sin;
    struct linger      linger;
    char * ipAddr = NULL;
    unsigned int port = 0;

    ipAddr = (ClientHandler::GetClientHandler())->GetServerIPAddr(); 
    port   = (ClientHandler::GetClientHandler())->GetServerPort();
 
    if (ipAddr == NULL || port == 0)
    {
        DT_CRT (("CreateTcpTrans:: IP / PORT  not configured"));
        return false;
    }
    //fix for the coverity issue CID no 10567
    memset(&sin,0,sizeof(struct sockaddr_in));

    /* Buil sock addr */
    sin.sin_family = AF_INET;
    sin.sin_port = htons((u_short)port);
    sin.sin_addr.s_addr = inet_addr(ipAddr);
    aSize = sizeof(struct sockaddr_in);

    /* Socket Creation */
    if ((_socket =  socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        DT_CRT(("CreateTcpTrans::Error socket create failure"));
        return false;
    }
    /* Set linger on, to 0 time */
    linger.l_onoff = 1;
    linger.l_linger = 0;
    if(setsockopt(_socket, SOL_SOCKET, SO_LINGER,
               (char *)&linger, sizeof(struct linger)) < 0)
    {
        DT_CRT(("CreateTcpTrans::SetSocketOpt failure "));
        shutdown(_socket, SHUT_RDWR);
        close(_socket);
        return false;
    }

    /* Set reuseaddr socket option */
    // Now Unchecked return value
    if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR,
               (void *)&dummy, sizeof(int)) < 0)
    {
        DT_CRT(("CreateTcpTrans::SetSocketOpt failure "));
        shutdown(_socket, SHUT_RDWR);
        close(_socket);
        return false;
    }
    

    /* bind to the port specified */
    if (bind(_socket, (struct sockaddr *)&sin, aSize) < 0)
    {
        DT_CRT(("CreateTcpTrans::Socket bind failure "));
        shutdown(_socket, SHUT_RDWR);
        close(_socket);
        return false;
    }

    /* Socket Creation */
    if (listen(_socket, SOMAXCONN) < 0)
    {
        DT_CRT(("iCreateTcpTrans:: socket bind failure "));
        //Fixing Resource Leak
        shutdown(_socket, SHUT_RDWR);
        close(_socket);
        return false;
    }
    idcSockAcceptor->SetServerSocket(_socket);

#if !defined(linux) || defined(USE_SELECT)
    /* Initialize desc array with "0" */
    for (int i=0;i<IDS_MAX_CONNS;i++)
    {
        desc[i] = NULL;
    }
#else
    epfd = epoll_create(IDS_MAX_CONNS);
    if (epfd < 0)
    {
        return (false);
    }
#endif

    return (true);

}
