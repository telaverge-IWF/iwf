/*********************************-*-C-*-************************************
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
 * LOG: $Log: its_sctp_sockets.c,v $
 * LOG: Revision 1.1.4.1.2.2.4.1.2.1.8.1  2014/09/16 09:34:54  jsarvesh
 * LOG: Changes done for removing warnings
 * LOG:
 * LOG: Revision 1.1.4.1.2.2.4.1.2.1.6.1  2014/09/15 07:20:42  jsarvesh
 * LOG: Changes done for removing Warnings
 * LOG:
 * LOG: Revision 1.1.4.1.2.2.4.1.2.1  2013/11/05 09:49:58  jvikram
 * LOG: Merge From TNSI
 * LOG:
 * LOG: Revision 1.9.8.2.4.2  2013/07/11 06:32:55  jvikram
 * LOG: Fixed sctp version issue.
 * LOG:
 * LOG: Revision 1.9.8.2.4.1  2013/06/25 10:00:04  jvikram
 * LOG: Merged changes from DRE Branch.
 * LOG:
 * LOG: Revision 1.9.2.2.2.2.4.3  2013/03/28 07:24:57  ncshivakumar
 * LOG: Fix for Bug 1312
 * LOG:
 * LOG: Revision 1.9.2.2.2.2.4.2  2013/03/05 06:55:50  ncshivakumar
 * LOG: Multihome changes
 * LOG:
 * LOG: Revision 1.9.2.2.2.2.4.1  2013/02/21 11:26:03  ncshivakumar
 * LOG: Modifed for supporting multitransport
 * LOG:
 * LOG: Revision 1.9.2.2.2.2  2012/11/24 07:57:58  jsarvesh
 * LOG: changes done if sctp is configured from cli and tcp from xml
 * LOG:
 * LOG: Revision 1.9.2.2.2.1  2012/08/21 08:44:36  ksalil
 * LOG: Merge from B-DRE-0100-00
 * LOG:
 * LOG: Revision 1.9.2.3  2012/08/14 09:06:13  ksalil
 * LOG: Changes for Compiler warnings
 * LOG:
 * LOG: Revision 1.9.2.2  2012/03/08 09:54:17  brajappa
 * LOG: Fixed the recvmsg error, sctp_recvmsg now sees msgFlags,initialize to zero
 * LOG:
 * LOG: Revision 1.9.2.1  2012/02/06 05:56:27  brajappa
 * LOG: sctp_connectx api has one more arg in LKSCTP 1.0.10
 * LOG:
 * LOG: Revision 1.9  2011/03/16 08:32:37  vkumara
 * LOG: Removed additional socket creation call
 * LOG:
 * LOG: Revision 1.8  2009/12/19 08:51:53  sureshj
 * LOG: Fix for helpdesk ticket 2287. SCTP_NODELAY not getting set.
 * LOG:
 * LOG: Revision 1.7  2009/05/12 08:50:23  rajeshak
 * LOG: Klockwork reported Issue fix.
 * LOG:
 * LOG: Revision 1.6  2009/03/19 11:16:22  chandrashekharbs
 * LOG: interface index updated from if_nametoindex
 * LOG:
 * LOG: Revision 1.5  2009/03/19 11:10:20  chandrashekharbs
 * LOG: Support for IPV6 SCTP added
 * LOG:
 * LOG: Revision 1.4  2009/03/18 05:56:38  rajeshak
 * LOG: Klockwork reported Issue fix.
 * LOG:
 * LOG: Revision 1.3  2009/02/27 06:02:38  rajeshak
 * LOG: IssueID:1667
 * LOG: FeatureID:None
 * LOG: Description: (SCTP: Only StreamID- 1 is used for sending SCTP packets)
 * LOG: Incrementing Stream Id after every successful send.
 * LOG:
 * LOG: Revision 1.2  2009/02/02 07:00:05  rajeshak
 * LOG: Changes for socket configuration
 * LOG:
 * LOG: Revision 1.1.1.1  2008/08/07 13:50:16  vnarang
 * LOG: Light wieght IntelliSS7 ( AcceleroCore)
 * LOG:
 * LOG: Revision 1.1.2.5  2007/02/17 07:06:32  nanaparthi
 * LOG: Fix for following issue :
 * LOG: Application is dumping core when we configure Host side as TCP, Peer side as SCTP
 * LOG:
 * LOG: Revision 1.1.2.4  2007/01/08 11:16:59  nanaparthi
 * LOG: Support for SCTP MultiHoming
 * LOG:
 * LOG: Revision 1.1.2.3  2007/01/01 13:49:07  nanaparthi
 * LOG: Support for SCTP MultiHoming
 * LOG:
 * LOG: Revision 1.1.2.2  2006/10/06 05:42:50  nanaparthi
 * LOG: Support for SCTP MultiHoming Server.
 * LOG:
 * LOG: Revision 1.1.2.1  2006/09/26 07:04:02  nanaparthi
 * LOG: Baseline LKSCTP support for Linux.
 * LOG:
 *
 * ID: $Id: its_sctp_sockets.c,v 1.1.4.1.2.2.4.1.2.1.8.1 2014/09/16 09:34:54 jsarvesh Exp $
 ****************************************************************************/
#ident "$Id: its_sctp_sockets.c,v 1.1.4.1.2.2.4.1.2.1.8.1 2014/09/16 09:34:54 jsarvesh Exp $"

#include <net/if.h>
#include <netinet/in.h>

#include <netinet/sctp.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <arpa/nameser.h>

#include <its.h>
#include <its_sockets.h>
#include <its_lksctp_sockets.h>
#include <its_trace.h>
#include <its_object.h>
#include <its_assertion.h>

#include <errno.h>
#include <netdb.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>


/*
 * System header files
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/ioctl.h>
#include <sys/time.h>

#include <its_timers.h>


/*
 * for those OS's who don't define this
 */
#ifndef SOMAXCONN
#define SOMAXCONN 25
#endif

/* local definition, maximum amount of times to retry hostname resolution */
#define MAX_RESOLVE_ATTEMPTS 12

/* What mask to set UNIX domain sockets to */
#define DEFAULT_MODE_MASK    \
    S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH

/* intermachine addressing */
#define SKIP_LOOPBACK

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      LKSCTP_SOCK_ClientOpen 
 *
 *  Purpose:
 *      This will create a client socket and resolve the target server's
 *      hostname.
 *
 *  Input Parameters:
 *      SOCK_DOMAIN                        INET_DOMAIN or UNIX_DOMAIN
 *      char *                             hostname of steam pathname of server
 *      int                                port number of server socket
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success
 *      Anything else - Something bad happened
 *
 ****************************************************************************/
ITSDLLAPI int
LKSCTP_SOCK_ClientOpen(ITS_SocketInfo **sockInfo, ITS_SOCK_DOMAIN domain,
                const char *host_or_path, int port, ITS_SockConfigOpt* sockOpt)
{
    int                 dummy = 1;                    /* for setsockoption() */
    ITS_SocketInfo      *ret = NULL;
    socklen_t len;

    /* Make sure we've got a valid pointer */
    ITS_C_ASSERT(sockInfo != NULL);

    *sockInfo = NULL;

    /* Initialize addr storage if we need to */
    if ((ret = (ITS_SocketInfo *)calloc(1, sizeof(ITS_SocketInfo))) == NULL)
    {
        return (ITS_ENOMEM);
    }

    /* get the address */
    if (SOCK_CreateAddr(domain, host_or_path, port,
                        &ret->addr, &ret->asize) != ITS_SUCCESS)
    {
        free(ret);
        return (ITS_EBADHOST);
    }

    /* setup if INET domain */
    if (domain == INET_DOMAIN)
    {
        /* Create a socket */
        if ((ret->socket = socket(AF_INET, SOCK_STREAM,IPPROTO_SCTP)) < 0)  
        {
            free(ret->addr);
            free(ret);
            return (ITS_ENOSOCKET);
        }

        /* Save off addr info in our own dataspace */
        ret->type = SPROT_TYPE_SCTP_CLIENT;
        ret->af = AF_INET;
        ret->no_ips = 1; 
        *sockInfo = ret;
        
    }
    /* Any other domain in invalid */
    else
    {
        free(ret->addr);
        free(ret);
        return (ITS_EINVALIDARGS);
    }

    //if (sockOpt)
    if (0)
    {
        int rCode = 0;

        /* RecvTimeout */
        struct timeval rcvTv, sndTv;
        rcvTv.tv_sec = sockOpt->recvTimeout.tv_sec;
        rcvTv.tv_usec = sockOpt->recvTimeout.tv_usec;
        setsockopt(ret->socket, SOL_SOCKET, SO_RCVTIMEO, 
                                 &rcvTv, sizeof(rcvTv));

        len = sizeof(rcvTv);
        memset(&rcvTv, 0, len);
        rCode = getsockopt(ret->socket, SOL_SOCKET, SO_RCVTIMEO,
                                 &rcvTv, &len);
        if(rCode ==0) 
        {
            ITS_TRACE_DEBUG(("SCTP_SockOpt: Receive Timeout sec=%d, uSec=%d ", rcvTv.tv_sec, rcvTv.tv_usec));
        }

        /* SendTimeout */
        sndTv.tv_sec = sockOpt->sendTimeout.tv_sec;
        sndTv.tv_usec = sockOpt->sendTimeout.tv_usec;
        setsockopt(ret->socket, SOL_SOCKET, SO_SNDTIMEO, 
                                 &sndTv, sizeof(sndTv));

        len = sizeof(sndTv);
        memset(&sndTv, 0,  len);
        rCode = getsockopt(ret->socket, SOL_SOCKET, SO_SNDTIMEO,
                                 &sndTv, &len);
        if(rCode ==0) 
        {
            ITS_TRACE_DEBUG(("SCTP_SockOpt: Send Timeout sec=%d, uSec=%d ", sndTv.tv_sec, sndTv.tv_usec));
        }
        
        /* HbTimeout, sackdelay & no of retransmissions triggering path failure */
        struct sctp_paddrparams sp;
        memset(&sp, 0, sizeof(sp));

        if (sockOpt->hbOn)
        {
            sp.spp_hbinterval = sockOpt->hbTimeout;
        }
        else
        {
            sp.spp_hbinterval = 0;
        }

        sp.spp_pathmaxrxt = sockOpt->pathmaxrxt;

#ifdef  _LKSCTP_VER_1_0_6  
        if (sockOpt->hbOn)
        {
            sp.spp_flags &= ~(SPP_HB_ENABLE | SPP_HB_DISABLE);
            sp.spp_flags |= SPP_HB_ENABLE;
        }
        else
        {
            sp.spp_flags &= ~(SPP_HB_ENABLE | SPP_HB_DISABLE);
            sp.spp_flags |= SPP_HB_DISABLE;
        }

        if (sp.spp_pathmaxrxt == 0)
        {
            sp.spp_flags |= SPP_PMTUD_DISABLE;
        }
        else
        {
            sp.spp_flags |= SPP_PMTUD_ENABLE;
        }

        sp.spp_sackdelay = sockOpt->ackDelay;
        if (sp.spp_sackdelay == 0)
        {
            sp.spp_flags &= ~(SPP_SACKDELAY_ENABLE|SPP_SACKDELAY_DISABLE);
            sp.spp_flags |= SPP_SACKDELAY_DISABLE;
        }
        else
        {
            sp.spp_flags &= ~(SPP_SACKDELAY_ENABLE|SPP_SACKDELAY_DISABLE);
            sp.spp_flags |= SPP_SACKDELAY_ENABLE;
        }
#endif
        setsockopt(ret->socket, IPPROTO_SCTP,
                    SCTP_PEER_ADDR_PARAMS, &sp, sizeof(sp));
        
        len = sizeof(sp);
        memset(&sp, 0, len); 
        rCode = sctp_opt_info(ret->socket, IPPROTO_SCTP,
                    SCTP_PEER_ADDR_PARAMS, &sp, &len);
        if(rCode ==0) 
        {
#ifdef  _LKSCTP_VER_1_0_6
            ITS_TRACE_DEBUG(("SCTP_SockOpt: HB Interval=%d, Sackdelay=%d, pathmaxrxt=%d ",
                              sp.spp_hbinterval, sp.spp_sackdelay, sp.spp_pathmaxrxt));
#else
            ITS_TRACE_DEBUG(("SCTP_SockOpt: HB Interval=%d,  pathmaxrxt=%d ",
                              sp.spp_hbinterval, sp.spp_pathmaxrxt));
#endif
        }

        /* MaxAttempts, MaxInStreams, noOfOutStreams, initTimeout */
        struct sctp_initmsg initMsg;
        initMsg.sinit_num_ostreams = sockOpt->noOfOutStreams;
        initMsg.sinit_max_instreams = sockOpt->maxNoOfInStreams;
        initMsg.sinit_max_attempts = sockOpt->maxAttempts;
        initMsg.sinit_max_init_timeo = sockOpt->initTimeout;
        setsockopt(ret->socket, IPPROTO_SCTP, SCTP_INITMSG,
                                 &initMsg, sizeof(initMsg)); 

        len = sizeof(initMsg);
        memset(&initMsg, 0, len); 
        rCode = getsockopt(ret->socket, IPPROTO_SCTP,
                    SCTP_INITMSG, &initMsg, &len);
        if(rCode ==0) 
        {
            ITS_TRACE_DEBUG(("SCTP_SockOpt:\nNoOfOutStreams=%d, MaxInStreams=%d \
                                           \nMaxAttempts=%d, MaxInitTimeout=%d \n",
                                             initMsg.sinit_num_ostreams,
                                             initMsg.sinit_max_instreams,
                                             initMsg.sinit_max_attempts,
                                             initMsg.sinit_max_init_timeo));
        }

        /* shutdown timeout */
        struct linger lngr;
        lngr.l_onoff = 1;
        lngr.l_linger = sockOpt->shutdownTimeout;
        setsockopt(ret->socket, SOL_SOCKET, SO_LINGER,
                                 &lngr, sizeof(lngr));

        len = sizeof(lngr);
        memset(&lngr, 0, len);
        rCode = getsockopt(ret->socket, SOL_SOCKET,
                    SO_LINGER, &lngr, &len);
        if(rCode ==0)
        {
            ITS_TRACE_DEBUG(("SCTP_SockOpt: shutdownTimeout=%d", lngr.l_linger));
        }

        /* cookie life & max retry for association failure */
        struct sctp_assocparams asocinfo;
        len = (socklen_t)sizeof(asocinfo);
        memset((void *)&asocinfo, 0, sizeof(asocinfo));
        asocinfo.sasoc_asocmaxrxt = sockOpt->asocmaxrxt;
        asocinfo.sasoc_cookie_life = sockOpt->cookieLife; //in millisec
        setsockopt(ret->socket, IPPROTO_SCTP, SCTP_ASSOCINFO, 
                                 (void *)&asocinfo, len); 

        len = sizeof(asocinfo);
        memset(&asocinfo, 0, len);
        rCode = getsockopt(ret->socket, IPPROTO_SCTP,
                    SCTP_ASSOCINFO, &asocinfo, &len);
        if(rCode ==0)
        {
            ITS_TRACE_DEBUG(("SCTP_SockOpt: cookielife=%d, asocmaxrxt=%d\n", 
                             asocinfo.sasoc_cookie_life, asocinfo.sasoc_asocmaxrxt));
        }

        /* RTO */
        struct sctp_rtoinfo rtoInfo;
        rtoInfo.srto_initial = sockOpt->rtoInitial;
        rtoInfo.srto_max = sockOpt->rtoMax;
        rtoInfo.srto_min = sockOpt->rtoMin;
        setsockopt(ret->socket, IPPROTO_SCTP, SCTP_RTOINFO,
                                 (void *)&rtoInfo, sizeof(rtoInfo));

        len = sizeof(rtoInfo);
        memset(&rtoInfo, 0, len);
        rCode = getsockopt(ret->socket, IPPROTO_SCTP,
                    SCTP_RTOINFO, &rtoInfo, &len);
        if(rCode ==0)
        {
            ITS_TRACE_DEBUG(("SCTP_SockOpt: RTO_min=%d, RTO_max=%d, RTO_Init=%d\n",
                              rtoInfo.srto_min, rtoInfo.srto_max, rtoInfo.srto_initial));
        }
        /* send buffer size */
        int bufferSz = sockOpt->sndBuffSize;
        setsockopt(ret->socket, SOL_SOCKET, SO_SNDBUF, 
                                 &bufferSz, sizeof(bufferSz));

        len = sizeof(bufferSz);
        memset(&bufferSz, 0, len);
        rCode = getsockopt(ret->socket, SOL_SOCKET,
                    SO_SNDBUF, &bufferSz, &len);
        if(rCode ==0)
        {
            ITS_TRACE_DEBUG(("SCTP_SockOpt: SendBuff Size=%d",bufferSz));
        }

        /* recv buffer size */
        bufferSz = sockOpt->rcvBuffSize;
        setsockopt(ret->socket, SOL_SOCKET, SO_RCVBUF, 
                                 &bufferSz, sizeof(bufferSz));

        len = sizeof(bufferSz);
        memset(&bufferSz, 0, len);
        rCode = getsockopt(ret->socket, SOL_SOCKET,
                    SO_RCVBUF, &bufferSz, &len);
        if(rCode ==0)
        {
            ITS_TRACE_DEBUG(("SCTP_SockOpt: RecvBuff Size=%d",bufferSz));
        }

        ret->max_out_stream = sockOpt->noOfOutStreams;
    }
    else
    {
        struct linger      linger;           /* set linger structure */

        /* Set linger on, to 0 time */
        linger.l_onoff = 1;
        linger.l_linger = 0;
        setsockopt(ret->socket, SOL_SOCKET, SO_LINGER,
                       (char *)&linger, sizeof(struct linger));  

        ret->max_out_stream = 1;
    }

    ret->stream_no = 1;

    /* Set re-use addr socket option */
    setsockopt(ret->socket, SOL_SOCKET, SO_REUSEADDR,
               (void *)&dummy, sizeof(int));

    /* fini */
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      LKSCTP_SOCK_FillSCTPConfig
 *
 *  Purpose:
 *         Copies the sctp heart beat parameters to sctp_paddrparams
 *         Structure from sockOpt read from config file
 *  Input Parameters:
 *      sockOpt        Socket Configuration  
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *              void
 ****************************************************************************/

ITSDLLAPI void
LKSCTP_SOCK_FillSCTPConfig(struct sctp_paddrparams *sp,ITS_SockConfigOpt* sockOpt)
{
    /* HbTimeout, sackdelay & no of retransmissions triggering path failure */

    if (sockOpt->hbOn)
    {
        sp->spp_hbinterval = sockOpt->hbTimeout;
    }
    else
    {
        sp->spp_hbinterval = 0;
    }

    sp->spp_pathmaxrxt = sockOpt->pathmaxrxt;

    if (sockOpt->hbOn)
    {
        sp->spp_flags &= ~(SPP_HB_ENABLE | SPP_HB_DISABLE);
        sp->spp_flags |= SPP_HB_ENABLE;
    }
    else
    {
        sp->spp_flags &= ~(SPP_HB_ENABLE | SPP_HB_DISABLE);
        sp->spp_flags |= SPP_HB_DISABLE;
    }

    if (sp->spp_pathmaxrxt == 0)
    {
        sp->spp_flags |= SPP_PMTUD_DISABLE;
    }
    else
    {
        sp->spp_flags |= SPP_PMTUD_ENABLE;
    }

    sp->spp_sackdelay = sockOpt->ackDelay;
    if (sp->spp_sackdelay == 0)
    {
        sp->spp_flags &= ~(SPP_SACKDELAY_ENABLE|SPP_SACKDELAY_DISABLE);
        sp->spp_flags |= SPP_SACKDELAY_DISABLE;
    }
    else
    {
        sp->spp_flags &= ~(SPP_SACKDELAY_ENABLE|SPP_SACKDELAY_DISABLE);
        sp->spp_flags |= SPP_SACKDELAY_ENABLE;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      LKSCTP_SOCK_MultiHomeClientOpen
 *
 *  Purpose:
 *      This will create a MultiHomed client socket and resolve the target 
 *      server's hostname.
 *
 *  Input Parameters:
 *      SOCK_DOMAIN                        INET_DOMAIN or UNIX_DOMAIN
 *      char **                            array of addresses of client
 *      int                                port number of server socket
 *      int                                number of addresses
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success
 *      Anything else - Something bad happened
 *
 ****************************************************************************/


ITSDLLAPI int
LKSCTP_SOCK_MultiHomeClientOpen(ITS_SocketInfo **sockInfo, ITS_SOCK_DOMAIN domain,
                                const char *host_or_path[], int port, int no_ips,
                                ITS_SockConfigOpt* sockOpt)                  
{
    int                 dummy = 1;                    /* for setsockoption() */
    ITS_SocketInfo      *ret = NULL;
    socklen_t len;

    char *bindbuf,*p;
    int i=0;

    /* Make sure we've got a valid pointer */
    ITS_C_ASSERT(sockInfo != NULL);

    *sockInfo = NULL;

    /* Initialize addr storage if we need to */
    if ((ret = (ITS_SocketInfo *)calloc(1, sizeof(ITS_SocketInfo))) == NULL)
    {
        return (ITS_ENOMEM);
    }

#ifdef USE_IPV6
    if (domain == INET6_DOMAIN)
    {
        if ((bindbuf = (char *) calloc (no_ips, sizeof(struct sockaddr_in6))) == NULL)
        {
            free(ret);
            return (ITS_ENOMEM);
        }
        p = bindbuf;

        for(i=0;i<no_ips;i++)
        {
            if (SOCK_CreateIpv6Addr(domain, host_or_path[i], port,
                         &ret->addr, &ret->asize) != ITS_SUCCESS)
            {
                free(ret);
                free(bindbuf);
                return (ITS_EBADHOST);
            }
            memcpy (p,ret->addr, ret->asize);
            p += ret->asize;
        }
        ret->multi_addrs = bindbuf;
        ret->no_ips = no_ips;
        /* Create a socket */
        if ((ret->socket = socket(AF_INET6, SOCK_STREAM,IPPROTO_SCTP)) < 0)
        {
            free(ret->addr);
            free(ret);
            free(bindbuf);
            return (ITS_ENOSOCKET);
        }

        /* Save off addr info in our own dataspace */
        ret->type = SPROT_TYPE_SCTP_CLIENT;
        ret->af = AF_INET6;
        *sockInfo = ret;

        //if (sockOpt)
        if (0)
        {
            //RecvTimeout
            struct timeval rcvTv, sndTv;
            rcvTv.tv_sec = sockOpt->recvTimeout.tv_sec;
            rcvTv.tv_usec = sockOpt->recvTimeout.tv_usec;
            setsockopt(ret->socket, SOL_SOCKET, SO_RCVTIMEO,
                                     &rcvTv, sizeof(rcvTv));

            //SendTimeout
            sndTv.tv_sec = sockOpt->sendTimeout.tv_sec;
            sndTv.tv_usec = sockOpt->sendTimeout.tv_usec;
            setsockopt(ret->socket, SOL_SOCKET, SO_SNDTIMEO,
                                     &sndTv, sizeof(sndTv));
  
            /* HbTimeout, sackdelay & no of retransmissions triggering path failure */
            struct sctp_paddrparams sp;
              
            memset(&sp, 0, sizeof(sp)); 
            LKSCTP_SOCK_FillSCTPConfig(&sp,sockOpt);
        
            setsockopt(ret->socket, IPPROTO_SCTP,
                       SCTP_PEER_ADDR_PARAMS, &sp, sizeof(sp));
        
            len = sizeof(sp);
            memset(&sp, 0, len); 
            int rCode = sctp_opt_info(ret->socket, IPPROTO_SCTP,
                    SCTP_PEER_ADDR_PARAMS, &sp, &len);
            if(rCode ==0) 
            {
                ITS_TRACE_DEBUG(("SCTP_SockOpt: HB Interval=%d, Sackdelay=%d, pathmaxrxt=%d ",
                                  sp.spp_hbinterval, sp.spp_sackdelay, sp.spp_pathmaxrxt));
            }
     
            //MaxAttempts, MaxInStreams, noOfOutStreams, initTimeout
            struct sctp_initmsg initMsg;
            initMsg.sinit_num_ostreams = sockOpt->noOfOutStreams;
            initMsg.sinit_max_instreams = sockOpt->maxNoOfInStreams;
            initMsg.sinit_max_attempts = sockOpt->maxAttempts;
            initMsg.sinit_max_init_timeo = sockOpt->initTimeout;
            setsockopt(ret->socket, IPPROTO_SCTP, SCTP_INITMSG,
                                     &initMsg, sizeof(initMsg)); 
        
            //shutdown timeout
            struct linger lngr;
            lngr.l_onoff = 1;
            lngr.l_linger = sockOpt->shutdownTimeout;
            setsockopt(ret->socket, SOL_SOCKET, SO_LINGER,
                                     &lngr, sizeof(lngr)); 
       
            //cookie life
            struct sctp_assocparams asocinfo;
            len = (socklen_t)sizeof(asocinfo);
            memset((void *)&asocinfo, 0, sizeof(asocinfo));
            asocinfo.sasoc_assoc_id = 0;
            asocinfo.sasoc_asocmaxrxt = sockOpt->asocmaxrxt;
            asocinfo.sasoc_cookie_life = sockOpt->cookieLife; //in millisec
            setsockopt(ret->socket, IPPROTO_SCTP, SCTP_ASSOCINFO,
                                     (void *)&asocinfo, len); 

            //RTO
            struct sctp_rtoinfo rtoInfo;
            rtoInfo.srto_initial = sockOpt->rtoInitial;
            rtoInfo.srto_max = sockOpt->rtoMax;
            rtoInfo.srto_min = sockOpt->rtoMin;
            setsockopt(ret->socket, IPPROTO_SCTP, SCTP_RTOINFO,
                                     (void *)&rtoInfo, sizeof(rtoInfo));

            //send buffer size
            int bufferSz = sockOpt->sndBuffSize;
            setsockopt(ret->socket, SOL_SOCKET, SO_SNDBUF,
                                     &bufferSz, sizeof(bufferSz));

            //recv buffer size
            bufferSz = sockOpt->rcvBuffSize;
            setsockopt(ret->socket, SOL_SOCKET, SO_RCVBUF,
                                     &bufferSz, sizeof(bufferSz));

            ret->max_out_stream = sockOpt->noOfOutStreams;
        }
        else 
        {
            struct linger      linger;           /* set linger structure */

            /* Set linger on, to 0 time */
            linger.l_onoff = 1;
            linger.l_linger = 0;
            setsockopt(ret->socket, SOL_SOCKET, SO_LINGER,
                           (char *)&linger, sizeof(struct linger));

            ret->max_out_stream = 1;
        }

        ret->stream_no = 1;

        /* Set re-use addr socket option */
        setsockopt(ret->socket, SOL_SOCKET, SO_REUSEADDR,
                   (void *)&dummy, sizeof(int));

         /* fini */
        return (ITS_SUCCESS);

    }//End IPV6
#endif

    if ((bindbuf = (char *) calloc (no_ips, sizeof(struct sockaddr_in))) == NULL)
    {
        free(ret);
        return (ITS_ENOMEM);
    }
    p = bindbuf;

    for(i=0;i<no_ips;i++)
    {
        if (SOCK_CreateAddr(domain, host_or_path[i], port,
                        &ret->addr, &ret->asize) != ITS_SUCCESS)
        {
                free(ret);
                free(bindbuf);
                return (ITS_EBADHOST);
        }
        memcpy (p,ret->addr, ret->asize);
        p += ret->asize;
    }
    ret->multi_addrs = bindbuf;
    ret->no_ips = no_ips;

    /* setup if INET domain */
    if (domain == INET_DOMAIN)
    {
        /* Create a socket */
        if ((ret->socket = socket(AF_INET, SOCK_STREAM,IPPROTO_SCTP)) < 0)
        {
            free(ret->addr);
            free(ret);
            free(bindbuf);
            return (ITS_ENOSOCKET);
        }

        /* Save off addr info in our own dataspace */
        ret->type = SPROT_TYPE_SCTP_CLIENT;
        ret->af = AF_INET;
        *sockInfo = ret;
    }

#if 0
#ifdef USE_IPV6  
    if (domain == INET_DOMAIN6)
    {
        /* Create a socket */
        if ((ret->socket = socket(AF_INET6, SOCK_STREAM,IPPROTO_SCTP)) < 0)
        {
            free(ret->addr);
            free(ret);
            free(bindbuf);
            return (ITS_ENOSOCKET);
        }

        /* Save off addr info in our own dataspace */
        ret->type = SPROT_TYPE_SCTP_CLIENT;
        ret->af = AF_INET6;
        *sockInfo = ret;
    }
#endif
#endif
    else
    {
        free(ret->addr);
        free(ret);
        free(bindbuf);
        return (ITS_EINVALIDARGS);
    }

    //if (sockOpt)
    if (0)
    {
        int rCode = 0;

        /* RecvTimeout */
        struct timeval rcvTv, sndTv;
        rcvTv.tv_sec = sockOpt->recvTimeout.tv_sec;
        rcvTv.tv_usec = sockOpt->recvTimeout.tv_usec;
        setsockopt(ret->socket, SOL_SOCKET, SO_RCVTIMEO,
                                 &rcvTv, sizeof(rcvTv));

        len = sizeof(rcvTv);
        memset(&rcvTv, 0, len);
        rCode = getsockopt(ret->socket, SOL_SOCKET, SO_RCVTIMEO,
                                 &rcvTv, &len);
        if(rCode ==0) 
        {
            ITS_TRACE_DEBUG(("SCTP_SockOpt: Receive Timeout sec=%d, uSec=%d ", rcvTv.tv_sec, rcvTv.tv_usec));
        }

        /* SendTimeout */
        sndTv.tv_sec = sockOpt->sendTimeout.tv_sec;
        sndTv.tv_usec = sockOpt->sendTimeout.tv_usec;
        setsockopt(ret->socket, SOL_SOCKET, SO_SNDTIMEO,
                                 &sndTv, sizeof(sndTv));

        len = sizeof(sndTv);
        memset(&sndTv, 0,  len);
        rCode = getsockopt(ret->socket, SOL_SOCKET, SO_SNDTIMEO,
                                 &sndTv, &len);
        if(rCode ==0) 
        {
            ITS_TRACE_DEBUG(("SCTP_SockOpt: Send Timeout sec=%d, uSec=%d ", sndTv.tv_sec, sndTv.tv_usec));
        }

        /* HbTimeout, sackdelay & no of retransmissions triggering path failure */
        struct sctp_paddrparams sp;
        memset(&sp, 0, sizeof(sp)); 
        LKSCTP_SOCK_FillSCTPConfig(&sp,sockOpt);
        
        setsockopt(ret->socket, IPPROTO_SCTP,
                    SCTP_PEER_ADDR_PARAMS, &sp, sizeof(sp));
        
        len = sizeof(sp);
        memset(&sp, 0, len); 
        rCode = sctp_opt_info(ret->socket, IPPROTO_SCTP,
                    SCTP_PEER_ADDR_PARAMS, &sp, &len);
        if(rCode ==0) 
        {
            ITS_TRACE_DEBUG(("SCTP_SockOpt: HB Interval=%d, Sackdelay=%d, pathmaxrxt=%d ",
                              sp.spp_hbinterval, sp.spp_sackdelay, sp.spp_pathmaxrxt));
        }

        /* MaxAttempts, MaxInStreams, noOfOutStreams, initTimeout */
        struct sctp_initmsg initMsg;
        initMsg.sinit_num_ostreams = sockOpt->noOfOutStreams;
        initMsg.sinit_max_instreams = sockOpt->maxNoOfInStreams;
        initMsg.sinit_max_attempts = sockOpt->maxAttempts;
        initMsg.sinit_max_init_timeo = sockOpt->initTimeout;
        setsockopt(ret->socket, IPPROTO_SCTP, SCTP_INITMSG,
                                 &initMsg, sizeof(initMsg)); 

        len = sizeof(initMsg);
        memset(&initMsg, 0, len); 
        rCode = getsockopt(ret->socket, IPPROTO_SCTP,
                    SCTP_INITMSG, &initMsg, &len);
        if(rCode ==0) 
        {
            ITS_TRACE_DEBUG(("SCTP_SockOpt:\nNoOfOutStreams=%d, MaxInStreams=%d\
                                           \nMaxAttempts=%d, MaxInitTimeout=%d \n",
                                             initMsg.sinit_num_ostreams,
                                             initMsg.sinit_max_instreams,
                                             initMsg.sinit_max_attempts,
                                             initMsg.sinit_max_init_timeo));
        }

        /* shutdown timeout */
        struct linger lngr;
        lngr.l_onoff = 1;
        lngr.l_linger = sockOpt->shutdownTimeout;
        setsockopt(ret->socket, SOL_SOCKET, SO_LINGER,
                                 &lngr, sizeof(lngr)); 
   
        len = sizeof(lngr);
        memset(&lngr, 0, len);
        rCode = getsockopt(ret->socket, SOL_SOCKET,
                    SO_LINGER, &lngr, &len);
        if(rCode ==0)
        {
            ITS_TRACE_DEBUG(("SCTP_SockOpt: shutdownTimeout=%d", lngr.l_linger));
        }

        /* cookie life & max retry for association failure */
        struct sctp_assocparams asocinfo;
        len = (socklen_t)sizeof(asocinfo);
        memset((void *)&asocinfo, 0, sizeof(asocinfo));
        asocinfo.sasoc_assoc_id = 0;
        asocinfo.sasoc_asocmaxrxt = sockOpt->asocmaxrxt;
        asocinfo.sasoc_cookie_life = sockOpt->cookieLife; //in millisec
        setsockopt(ret->socket, IPPROTO_SCTP, SCTP_ASSOCINFO,
                                 (void *)&asocinfo, len); 

        len = sizeof(asocinfo);
        memset(&asocinfo, 0, len);
        rCode = getsockopt(ret->socket, IPPROTO_SCTP,
                    SCTP_ASSOCINFO, &asocinfo, &len);
        if(rCode ==0)
        {
            ITS_TRACE_DEBUG(("SCTP_SockOpt: cookielife=%d, asocmaxrxt=%d \n", 
                             asocinfo.sasoc_cookie_life, asocinfo.sasoc_asocmaxrxt));
        }

        /* RTO */
        struct sctp_rtoinfo rtoInfo;
        rtoInfo.srto_initial = sockOpt->rtoInitial;
        rtoInfo.srto_max = sockOpt->rtoMax;
        rtoInfo.srto_min = sockOpt->rtoMin;
        setsockopt(ret->socket, IPPROTO_SCTP, SCTP_RTOINFO,
                                 (void *)&rtoInfo, sizeof(rtoInfo));

        len = sizeof(rtoInfo);
        memset(&rtoInfo, 0, len);
        rCode = getsockopt(ret->socket, IPPROTO_SCTP,
                    SCTP_RTOINFO, &rtoInfo, &len);
        if(rCode ==0)
        {
            ITS_TRACE_DEBUG(("SCTP_SockOpt: RTO_min=%d, RTO_max=%d, RTO_Init=%d\n",
                              rtoInfo.srto_min, rtoInfo.srto_max, rtoInfo.srto_initial));
        }
        /* send buffer size */
        int bufferSz = sockOpt->sndBuffSize;
        setsockopt(ret->socket, SOL_SOCKET, SO_SNDBUF,
                                 &bufferSz, sizeof(bufferSz));

        len = sizeof(bufferSz);
        memset(&bufferSz, 0, len);
        rCode = getsockopt(ret->socket, SOL_SOCKET,
                    SO_SNDBUF, &bufferSz, &len);
        if(rCode ==0)
        {
            ITS_TRACE_DEBUG(("SCTP_SockOpt: SendBuff Size=%d",bufferSz));
        }

        /* recv buffer size */
        bufferSz = sockOpt->rcvBuffSize;
        setsockopt(ret->socket, SOL_SOCKET, SO_RCVBUF,
                                 &bufferSz, sizeof(bufferSz));

        len = sizeof(bufferSz);
        memset(&bufferSz, 0, len);
        rCode = getsockopt(ret->socket, SOL_SOCKET,
                    SO_RCVBUF, &bufferSz, &len);
        if(rCode ==0)
        {
            ITS_TRACE_DEBUG(("SCTP_SockOpt: RecvBuff Size=%d",bufferSz));
        }

        ret->max_out_stream = sockOpt->noOfOutStreams;
    }
    else 
    {
        struct linger      linger;           /* set linger structure */

        /* Set linger on, to 0 time */
        linger.l_onoff = 1;
        linger.l_linger = 0;
        setsockopt(ret->socket, SOL_SOCKET, SO_LINGER,
                       (char *)&linger, sizeof(struct linger));

        ret->max_out_stream = 1;
    }
    ret->stream_no = 0;

    /* Set re-use addr socket option */
    setsockopt(ret->socket, SOL_SOCKET, SO_REUSEADDR,
               (void *)&dummy, sizeof(int));

     /* fini */
    return (ITS_SUCCESS);
}



/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      LKSCTP_SOCK_ServerOpen.
 *
 *  Purpose:
 *     Create a server socket and resolve hostname (why a hostname?  don't
 *     ask me I didn't write this I am just cleaning it up.  I suspect the
 *     client was written first and modified into this... )
 *
 *  Input Parameters:
 *      SOCK_DOMAIN         INET_DOMAIN or UNIX_DOMAIN
 *      host_or_path        hostname (of what, self??)
 *      port                port number (of what, self??)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success
 *      Anything else - an error occured
 *
 ****************************************************************************/
ITSDLLAPI int
LKSCTP_SOCK_ServerOpen(ITS_SocketInfo **sockInfo, ITS_SOCK_DOMAIN domain,
                       const char *host_or_path, int port)
{
    int    dummy = 1;       /* for socket option */
    ITS_SocketInfo *ret;

    /* Make sure the address is good */
    ITS_C_ASSERT(sockInfo != NULL);

    /* Set up our addr info accounting */
    if ((ret = (ITS_SocketInfo *)calloc(1, sizeof(ITS_SocketInfo))) == NULL)
    {
        return (ITS_ENOMEM);
    }

    /* get the address */
    if (SOCK_CreateAddr(domain, host_or_path, port,
                        &ret->addr, &ret->asize) != ITS_SUCCESS)
    {
        free(ret);
        return (ITS_EBADHOST);
    }

    /* setup if INET domain */
    if (domain == INET_DOMAIN)
    {
        struct linger      linger;           /* for set linger */

        /* Create a socket */
        if ((ret->socket = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP)) < 0)
        {
            free(ret->addr);
            free(ret);
            return (ITS_ENOSOCKET);
        }

        /* Set linger on, to 0 time */
        linger.l_onoff = 1;
        linger.l_linger = 0;
        setsockopt(ret->socket, SOL_SOCKET, SO_LINGER,
                   (char *)&linger, sizeof(struct linger));

        /* Save off addr info in our own dataspace */
        ret->type = SPROT_TYPE_SCTP_SERVER;
        ret->af = AF_INET;
        *sockInfo = ret;
    }
    /* Any other domain is invalid */
    else
    {
        free(ret->addr);
        free(ret);
        return (ITS_EINVALIDARGS);
    }

    /* Set reuseaddr socket option */
    setsockopt(ret->socket, SOL_SOCKET, SO_REUSEADDR,
               (void *)&dummy, sizeof(int));

    /* bind to the port specified */
    if (bind(ret->socket, (struct sockaddr *)ret->addr, ret->asize) < 0)
    {
        free(ret->addr);
        close(ret->socket);
        free(ret);
	*sockInfo = NULL;
        return (ITS_EBINDFAIL);
    }

    /* Set up a listen queue */
    if (listen(ret->socket, SOMAXCONN) < 0)
    {
        unlink(host_or_path);
        free(ret->addr);
        close(ret->socket);
        free(ret);
	*sockInfo = NULL;
        return (ITS_ELISTENFAIL);
    }

    ret->stream_no = 0;
    ret->max_out_stream = 1;

    /* fini */
    return (ITS_SUCCESS);
}


/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      LKSCTP_SOCK_MultiHomeServerOpen.
 *
 *  Purpose:
 *     Create a server socket and resolve hostname (why a hostname?  don't
 *     ask me I didn't write this I am just cleaning it up.  I suspect the
 *     client was written first and modified into this... )
 *
 *  Input Parameters:
 *      SOCK_DOMAIN         INET_DOMAIN or UNIX_DOMAIN
 *      host_or_path        hostname (of what, self??)
 *      port                port number (of what, self??)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success
 *      Anything else - an error occured
 *
 ****************************************************************************/
ITSDLLAPI int
LKSCTP_SOCK_MultiHomeServerOpen(ITS_SocketInfo **sockInfo, ITS_SOCK_DOMAIN domain,
                                const char *host_or_path[], int port, int no_ips,ITS_SockConfigOpt* sockOpt)
{
    int    dummy = 1;       /* for socket option */
    socklen_t len;
    ITS_SocketInfo *ret;

    char *bindbuf,*p; 
    int i=0;

    /* Make sure the address is good */
    ITS_C_ASSERT(sockInfo != NULL);

    /* Set up our addr info accounting */
    if ((ret = (ITS_SocketInfo *)calloc(1, sizeof(ITS_SocketInfo))) == NULL)
    {
        return (ITS_ENOMEM);
    }

#ifdef USE_IPV6
    /* setup if INET domain */
    if (domain == INET6_DOMAIN)
    {
        /* get the address */
        struct linger      linger;           /* for set linger */

        if ((bindbuf = (char *) calloc (no_ips, sizeof(struct sockaddr_in6))) == NULL)
        {
            free (ret);
            return (ITS_ENOMEM);
        }
        p = bindbuf;

        for(i=0;i<no_ips;i++)
        {
            if (SOCK_CreateIpv6Addr(domain, host_or_path[i], port,
                             &ret->addr, &ret->asize) != ITS_SUCCESS)
            {
                free(ret);
                free(bindbuf);
                return (ITS_EBADHOST);
           }
           memcpy (p,ret->addr, ret->asize);
           p += ret->asize;
        }

        /* Create a socket */
        if ((ret->socket = socket(AF_INET6, SOCK_STREAM, IPPROTO_SCTP)) < 0)
        {
            free(ret->addr);
            free(ret);
            free(bindbuf);
            return (ITS_ENOSOCKET);
        }

        /* Set linger on, to 0 time */
        linger.l_onoff = 1;
        linger.l_linger = 0;
        setsockopt(ret->socket, SOL_SOCKET, SO_LINGER,
                   (char *)&linger, sizeof(struct linger));

        /* Save off addr info in our own dataspace */
        ret->type = SPROT_TYPE_SCTP_SERVER;
        ret->af = AF_INET6;
        *sockInfo = ret;

        /* Set reuseaddr socket option */
        setsockopt(ret->socket, SOL_SOCKET, SO_REUSEADDR,
               (void *)&dummy, sizeof(int));
        
        /* HbTimeout, sackdelay & no of retransmissions triggering path failure */
        struct sctp_paddrparams sp;
        memset(&sp, 0, sizeof(sp)); 
        LKSCTP_SOCK_FillSCTPConfig(&sp,sockOpt);
        
        setsockopt(ret->socket, IPPROTO_SCTP,
                    SCTP_PEER_ADDR_PARAMS, &sp, sizeof(sp));
        
        len = sizeof(sp);
        memset(&sp, 0, len); 
        int rCode = sctp_opt_info(ret->socket, IPPROTO_SCTP,
                    SCTP_PEER_ADDR_PARAMS, &sp, &len);
        if(rCode ==0) 
        {
            ITS_TRACE_DEBUG(("SCTP_SockOpt: HB Interval=%d, Sackdelay=%d, pathmaxrxt=%d ",
                              sp.spp_hbinterval, sp.spp_sackdelay, sp.spp_pathmaxrxt));
        }
        
        if (sctp_bindx(ret->socket, (struct sockaddr*)bindbuf,
                    no_ips, SCTP_BINDX_ADD_ADDR) < 0)
         {
             printf("bind failed \n");
             close(ret->socket);
             free(ret);
             *sockInfo = NULL;
             free(bindbuf);
             return (ITS_EBINDFAIL);
         }
        
        /* Set up a listen queue */
        if (listen(ret->socket, SOMAXCONN) < 0)
        {
            unlink(host_or_path[0]);
            free(ret->addr);
            close(ret->socket);
            free(ret);
	    *sockInfo = NULL;
            return (ITS_ELISTENFAIL);
        }

        ret->stream_no = 1;
        ret->max_out_stream = 1;

        /* fini */
        return (ITS_SUCCESS);
    }
#endif

    if ((bindbuf = (char *) calloc (no_ips, sizeof(struct sockaddr_in))) == NULL)
    {
        free (ret);
        return (ITS_ENOMEM);
    }
    p = bindbuf;

    for(i=0;i<no_ips;i++)
    {
        if (SOCK_CreateAddr(domain, host_or_path[i], port,
                            &ret->addr, &ret->asize) != ITS_SUCCESS)
        {
            free(ret);
            free(bindbuf);
            return (ITS_EBADHOST);
        }
        memcpy (p,ret->addr, ret->asize);
        p += ret->asize;
    }
   
    /* setup if INET domain */
    if (domain == INET_DOMAIN)
    {
        struct linger      linger;           /* for set linger */

        /* Create a socket */
        if ((ret->socket = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP)) < 0)
        {
            free(ret->addr);
            free(ret);
            free(bindbuf);
            return (ITS_ENOSOCKET);
        }

        /* Set linger on, to 0 time */
        linger.l_onoff = 1;
        linger.l_linger = 0;
        setsockopt(ret->socket, SOL_SOCKET, SO_LINGER,
                   (char *)&linger, sizeof(struct linger));

        /* Save off addr info in our own dataspace */
        ret->type = SPROT_TYPE_SCTP_SERVER;
        ret->af = AF_INET;
        *sockInfo = ret;
    }
    /* Any other domain is invalid */
    else
    {
        free(ret->addr);
        free(ret);
        free(bindbuf);
        return (ITS_EINVALIDARGS);
    }

    /* HbTimeout, sackdelay & no of retransmissions triggering path failure */
     struct sctp_paddrparams sp;
     memset(&sp, 0, sizeof(sp)); 
     LKSCTP_SOCK_FillSCTPConfig(&sp,sockOpt);
        
     setsockopt(ret->socket, IPPROTO_SCTP,
                SCTP_PEER_ADDR_PARAMS, &sp, sizeof(sp));
        
     len = sizeof(sp);
     memset(&sp, 0, len); 
     int rCode = sctp_opt_info(ret->socket, IPPROTO_SCTP,
                           SCTP_PEER_ADDR_PARAMS, &sp, &len);
     if(rCode ==0) 
     {
         ITS_TRACE_DEBUG(("SCTP_SockOpt: HB Interval=%d, Sackdelay=%d, pathmaxrxt=%d ",
                           sp.spp_hbinterval, sp.spp_sackdelay, sp.spp_pathmaxrxt));
     }
    /* Set reuseaddr socket option */
    setsockopt(ret->socket, SOL_SOCKET, SO_REUSEADDR,
               (void *)&dummy, sizeof(int));

    /* bind to the port specified */
    if (sctp_bindx(ret->socket, (struct sockaddr *)bindbuf, 
                   no_ips, SCTP_BINDX_ADD_ADDR) < 0)
    {
        close(ret->socket);
        free(ret);
	*sockInfo = NULL;
        free(bindbuf);
        return (ITS_EBINDFAIL);
    }

    /* Set up a listen queue */
    if (listen(ret->socket, SOMAXCONN) < 0)
    {
        unlink(host_or_path[0]);
        free(ret->addr);
        close(ret->socket);
        free(ret);
	*sockInfo = NULL;
        free(bindbuf);
        return (ITS_ELISTENFAIL);
    }

    ret->stream_no = 0;
    ret->max_out_stream = 1;

    /* fini */
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      LKSCTP_SOCK_ClientConnect.
 *
 *  Purpose:
 *      Connect a socket, if it is a tcp socket disable that pesky nagle
 *      algorithm
 *
 *  Input Parameters:
 *      int sock        file descriptor to connect() with
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS      if everything is OK
 *      Anything else    if it's all gone horribly wrong
 *
 ****************************************************************************/
ITSDLLAPI int
LKSCTP_SOCK_ClientConnect(ITS_SocketInfo* info)
{
    struct protoent     *ent;                /* For use in disabling nagle */
    int flag = 1;                            /* For use in disabling nagle */

    if (!info)
    {
        return (ITS_ECONNECTFAIL);
    }

    /*
     * Attempt connection
     */

    if(info->no_ips == 1)                     /* Basic SCTP */
    {
        if(connect(info->socket, info->addr, info->asize) < 0)
        {
           return (ITS_ECONNECTFAIL);
        }
    }
    /*
     * SCTP MultiHoming 
     */ 
#ifdef USE_SCTP_BEFORE_1_0_10
    else if (sctp_connectx(info->socket,
                           (struct sockaddr *)info->multi_addrs, 
                           info->no_ips) < 0)                           
#else
    else if (sctp_connectx(info->socket,
                          (struct sockaddr *)info->multi_addrs, 
                          info->no_ips,
                          NULL) < 0)                           
#endif
    {
        return (ITS_ECONNECTFAIL);
    }
    /*
     * Disable TCP NAGLE algorighm. (don't delay short messages waiting for
     * window ack)
     */
    if (info->af == AF_INET && (ent = getprotobyname("sctp")) != NULL)
    {
        setsockopt(info->socket, ent->p_proto,
                   SCTP_NODELAY, (char *)&flag, sizeof(flag)); 
    }

    struct sctp_status status;
    memset(&status, 0, sizeof(status));
    socklen_t len = sizeof(status);
    if (getsockopt(info->socket, IPPROTO_SCTP, SCTP_STATUS, &status, &len) == 0) 
    {
        info->max_out_stream = status.sstat_outstrms; 
    }

    /*
     * fini
     */
    return (ITS_SUCCESS);
}
/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      LKSCTP_SOCK_Ipv6ClientConnect.
 *
 *  Purpose:
 *      Connect a ipv6 socket, if it is a tcp socket disable that pesky nagle
 *      algorithm
 *
 *  Input Parameters:
 *      int sock        file descriptor to connect() with
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS      if everything is OK
 *      Anything else    if it's all gone horribly wrong
 *
 ****************************************************************************/
ITSDLLAPI int
LKSCTP_SOCK_Ipv6ClientConnect(ITS_SocketInfo* info)
{
#ifdef USE_IPV6
    struct protoent     *ent;                /* For use in disabling nagle */
    int flag = 1;                            /* For use in disabling nagle */

    if (!info)
    {
        return (ITS_ECONNECTFAIL);
    }

    /*
     * Attempt connection
     */

    //setsockopt(info->socket, SOL_SOCKET, SO_BINDTODEVICE, "eth0\0", 5);

    if(info->no_ips == 1)
    {
        if(connect(info->socket, info->addr, info->asize) < 0)
        {
            return (ITS_ECONNECTFAIL);
        }
    }
    /*
     * SCTP MultiHoming 
     */ 
#ifdef USE_SCTP_BEFORE_1_0_10
    else if (sctp_connectx(info->socket,
                          (struct sockaddr_in6 *)info->multi_addrs, 
                          info->no_ips) < 0)                           
#else
    else if (sctp_connectx(info->socket,
                          (struct sockaddr_in6 *)info->multi_addrs, 
                          info->no_ips,NULL) < 0)                           
#endif
    {
        return (ITS_ECONNECTFAIL);
    }
    /*
     * Disable TCP NAGLE algorighm. (don't delay short messages waiting for
     * window ack)
     */
    if (info->af == AF_INET6 && (ent = getprotobyname("sctp")) != NULL)
    {
        setsockopt(info->socket, ent->p_proto,
                   SCTP_NODELAY, (char *)&flag, sizeof(flag)); 
 
        struct sctp_initmsg initMsg;
        socklen_t len = sizeof(initMsg);
        if (getsockopt(info->socket, IPPROTO_SCTP, SCTP_INITMSG,
                                &initMsg, &len) == 0)
        {
            info->max_out_stream = initMsg.sinit_num_ostreams; 
        }
    }
#endif
    /*
     * fini
     */
    return (ITS_SUCCESS);
}
/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      LKSCTP_SOCK_ServerAccept.
 *
 *  Purpose:
 *      Accept a connection and disable the NAGLE algorithm (queue short
 *      messages waiting for window ack) support on connection
 *
 *  Input Parameters:
 *      int sock                file descriptor to accept on
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS           file descriptor of connection
 *      Anything else         something is wrong
 *
 ****************************************************************************/
ITSDLLAPI int
LKSCTP_SOCK_ServerAccept(ITS_SocketInfo* info, ITS_SocketInfo **newInfo)
{
    int    flag = 1;          /* for setsockopt() call */
    struct protoent    *ent;  /* protocol entry */
    ITS_SocketInfo* tmp;
    ITS_SocketInfo tmp1;

    if (!info)
    {
        return (ITS_ECONNECTFAIL);
    }

    ITS_C_ASSERT(newInfo != NULL);

    *newInfo = NULL;

    /* allocate info struct */
    if ((tmp = (ITS_SocketInfo *)calloc(1, sizeof(ITS_SocketInfo))) == NULL)
    {
        return (ITS_ENOMEM);
    }

    /* Allocate storage for addr structure */
    if ((tmp->addr = (struct sockaddr_un *)calloc(1,
                      sizeof(struct sockaddr_un))) == NULL)   
    {
        free(tmp);
        tmp = NULL;
        return (ITS_ENOMEM);
    }

    /* Accept a connection */
    tmp->asize = sizeof(struct sockaddr_un);
    tmp->socket = accept(info->socket, tmp->addr, (socklen_t *)&tmp->asize);

    /*
     * If the return code is 0 or greater it is a file descriptor
     * (technically this is an err, but you will never see a file
     * descriptor of zero so I'm leaving the code as is
     */
    if (tmp->socket <= 0)
    {
        /* We could not accept so we do not need this memory anymore */
        free(tmp->addr);
        free(tmp);
        return (ITS_EBADSOCKET);
    }

    if (SOCK_GetPeerName(tmp, &tmp1) != ITS_SUCCESS)
    {
        /* We could accept, but the peer crapped out */
        free(tmp->addr);
        free(tmp);
        return (ITS_EBADSOCKET);
    }

    /* We don't need tmp1 anymore */
    free(tmp1.addr);

    /* Update our socket data info */
    tmp->af = ((struct sockaddr_un *)tmp->addr)->sun_family;

    tmp->stream_no = 0;
    tmp->max_out_stream = 1;

    /* Get rid of nagle support */
    if (tmp->af == AF_INET && (ent = getprotobyname("sctp")) != NULL)
    {
        setsockopt(tmp->socket, ent->p_proto,
                   SCTP_NODELAY, (char *)&flag, sizeof(flag));  
    }

    struct sctp_status status;
    memset(&status, 0, sizeof(status));
    socklen_t len = sizeof(status);
    if (getsockopt(tmp->socket, IPPROTO_SCTP, SCTP_STATUS, &status, &len) == 0) 
    {
        tmp->max_out_stream = status.sstat_outstrms; 
    }

    *newInfo = tmp;

    /* fini */
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      LKSCTP_SOCK_Read.
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
ITSDLLAPI int
LKSCTP_SOCK_Read(ITS_SocketInfo* info, char *buf, int nbytes)
{
    int     nleft;                    /* Amount of data left to read */
    int     nread;                    /* Amount of data we have read */
    int     done = ITS_FALSE;             /* Loop terminator for EOF      */

    struct sctp_sndrcvinfo sndrcvinfo = {0};  
    int flags = 0;

    /* Set up how much we want to read */
    nleft = nbytes;

    if (!info)
    {
        return (0);
    }

    /* While not error or EOF and there is more data expected... */
    while ((nleft > 0) && (!done))
    {
        /* Read something */

        nread = sctp_recvmsg( info->socket, buf, nleft,
	                    (struct sockaddr *)NULL, 0, &sndrcvinfo, &flags );

        /*  nread = read(info->socket, buf, nleft); */

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
 *      LKSCTP_SOCK_Write.
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
ITSDLLAPI int
LKSCTP_SOCK_Write(ITS_SocketInfo* info, char *buf, int nbytes)
{
    int    nleft;
    int    nwritten;

    /* Set up how much we need to write */
    nleft = nbytes;

    if (!info)
    {
        return (0);
    }

    /* While still bytes to write do so */
    while (nleft > 0)
    {
        /* Write some data */

        nwritten = sctp_sendmsg(info->socket, buf, nleft, NULL,0, 0, 
                                0, 1, 0, 0);  

        /*  nwritten = write(info->socket, buf, nleft);  */

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

ITSDLLAPI int
LKSCTP_SOCK_Stream_Write(ITS_SocketInfo* info, char *buf, int nbytes, int *streamNo, int maxOutStream)
{
    int    nleft;
    int    nwritten;
    int    outputStreamNo = *streamNo;
    struct sctp_sndrcvinfo sinfo;

    memset(&sinfo, 0, sizeof(sinfo));
    sinfo.sinfo_stream = outputStreamNo;

    /* Set up how much we need to write */
    nleft = nbytes;

    if (!info)
    {
        return (0);
    }

    /* While still bytes to write do so */
    while (nleft > 0)
    {
        /* Write some data */

        nwritten = sctp_send(info->socket, buf, nleft, &sinfo, 0);

        /*  nwritten = write(info->socket, buf, nleft);  */

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

    if (outputStreamNo < (maxOutStream-1))
    {
        outputStreamNo++;
    }
    else
    {
        outputStreamNo = 0;
    }
    *streamNo = outputStreamNo;

    /* Return how much we actually wrote */
    return (nbytes - nleft);
}
