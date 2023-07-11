/*********************************-*-C-*-************************************
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
 *
 * LOG: $Log: its_sockets.c,v $
 * LOG: Revision 9.1.114.1.12.1.6.1.2.1  2020/02/14 11:36:10  jkchaitanya
 * LOG: TCP Timeout fix ported from DRE
 * LOG:
 * LOG: Revision 9.1.114.1.12.1.6.1  2014/09/16 09:34:54  jsarvesh
 * LOG: Changes done for removing warnings
 * LOG:
 * LOG: Revision 9.1.114.1.12.1.4.1  2014/09/15 07:20:42  jsarvesh
 * LOG: Changes done for removing Warnings
 * LOG:
 * LOG: Revision 9.1.114.1.12.1  2014/02/20 14:19:03  jkchaitanya
 * LOG: fix for mh
 * LOG:
 * LOG: Revision 9.1.114.1  2011/04/13 07:36:19  nvijikumar
 * LOG: Merging diamter branch changes
 * LOG:
 * LOG: Revision 1.11  2010/10/11 11:33:41  vkumara
 * LOG: SOCK_GetIpAddress support on linux
 * LOG:
 * LOG: Revision 1.10  2010/08/31 04:35:49  nvijikumar
 * LOG: Typo
 * LOG:
 * LOG: Revision 1.9  2010/08/27 12:15:36  nvijikumar
 * LOG: DSCP Value support (Vasanth)
 * LOG:
 * LOG: Revision 1.8  2009/09/18 06:29:19  rajeshak
 * LOG: Fix for HelpDeskIssue-2213 (Hung Thread)
 * LOG: Using Socket Connect with timeout.
 * LOG:
 * LOG: Revision 1.7  2009/06/10 03:30:15  rajeshak
 * LOG: Check whether we are writing to valid socket or not.
 * LOG: (SIGPIPE issue fix when Peer is killed).
 * LOG:
 * LOG: Revision 1.6  2009/03/19 11:16:36  chandrashekharbs
 * LOG: interface index updated from if_nametoindex
 * LOG:
 * LOG: Revision 1.5  2009/03/18 05:56:38  rajeshak
 * LOG: Klockwork reported Issue fix.
 * LOG:
 * LOG: Revision 1.4  2009/03/03 12:37:44  chandrashekharbs
 * LOG: USE_IPV6 flag check changed to avoid compilation errors when compiled without this flag
 * LOG:
 * LOG: Revision 1.3  2009/03/03 12:19:44  chandrashekharbs
 * LOG: Changes for IPV6 TCP support
 * LOG:
 * LOG: Revision 1.2  2008/12/09 10:45:24  nvijikumar
 * LOG: Commented SOCK_GetPeerName as it was causing more cs (context switches)
 * LOG:
 * LOG: Revision 1.1.1.1  2008/08/07 13:50:16  vnarang
 * LOG: Light wieght IntelliSS7 ( AcceleroCore)
 * LOG:
 * LOG: Revision 9.1.28.6  2007/01/22 15:00:27  nanaparthi
 * LOG: Fix for Bug Id 5151
 * LOG:
 * LOG: Revision 9.1.28.5  2006/12/20 11:20:11  tpanda
 * LOG: Check if the peer down before write to socket
 * LOG:
 * LOG: Revision 9.1.28.4  2006/10/26 05:24:54  nvijikumar
 * LOG: Correction for ERROR Traces.
 * LOG:
 * LOG: Revision 9.1.28.3  2006/10/25 15:58:30  yranade
 * LOG: Added error trace for peername error case.
 * LOG:
 * LOG: Revision 9.1.28.2  2006/09/13 10:16:34  yranade
 * LOG: Updates and corrections.
 * LOG:
 * LOG: Revision 9.1.28.1  2006/04/18 11:57:56  yranade
 * LOG: Patch in Linux specific issues.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:43  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:52:13  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.10.1  2004/09/29 09:56:14  asingh
 * LOG: Changes for linux ES 30 operating system; compilation issue.
 * LOG:
 * LOG: Revision 7.2  2003/01/28 23:17:10  mmiers
 * LOG: Make sure the class records are correctly exported.
 * LOG: Flesh out ring buffer class (not done yet).
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:05  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/06/19 19:31:16  lbana
 * LOG: Missing SOCK_CreateAddr in SOCK_RawOpen call.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:27  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:14  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.15  2001/04/27 21:26:32  labuser
 * LOG: In SOCK_AddrsAreEqual default return value should be FALSE.
 * LOG:
 * LOG: Revision 3.14  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.13  2001/02/20 19:00:57  mmiers
 * LOG: Assert removal
 * LOG:
 * LOG: Revision 3.12  2001/02/07 22:12:56  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.11  2001/01/31 20:55:59  mmiers
 * LOG: More cleanup.  Socket fix.
 * LOG:
 * LOG: Revision 3.10  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.9  2001/01/31 00:32:58  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.8  2000/12/21 18:24:07  mmiers
 * LOG: Finish fixing address conversion
 * LOG:
 * LOG: Revision 3.7  2000/12/21 01:47:39  mmiers
 * LOG: Temp version.
 * LOG:
 * LOG: Revision 3.6  2000/11/30 19:37:45  mmiers
 * LOG: Ready to debug.
 * LOG:
 * LOG: Revision 3.5  2000/11/13 19:28:30  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.8  2000/10/11 18:57:17  mmiers
 * LOG: Skip the loopback interface by default.
 * LOG:
 * LOG: Revision 3.7  2000/10/11 18:53:36  mmiers
 * LOG: Initiation in both directions.
 * LOG:
 * LOG: Revision 3.6  2000/10/10 17:10:06  mmiers
 * LOG: Associations work!
 * LOG:
 * LOG: Revision 3.5  2000/10/09 21:58:57  mmiers
 * LOG: Debug of SCTP.
 * LOG:
 * LOG: Revision 3.4  2000/10/05 00:11:05  mmiers
 * LOG: Merge in the rev13 changes.
 * LOG:
 * LOG: Revision 3.3  2000/09/28 22:10:25  mmiers
 * LOG: Build on UNIX.
 * LOG:
 * LOG: Revision 3.2  2000/09/28 21:49:52  mmiers
 * LOG:
 * LOG: Checkpoint for solaris build.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:06:02  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.19  2000/07/12 20:02:10  mmiers
 * LOG: getpeername() size is [in/out].  Docs on UNIX confirm this.
 * LOG:
 * LOG: Revision 1.18  2000/06/02 15:51:35  mmiers
 * LOG:
 * LOG:
 * LOG: More sockets testing.
 * LOG:
 * LOG: Revision 1.17  2000/05/25 14:09:04  mmiers
 * LOG:
 * LOG:
 * LOG: Typo
 * LOG:
 * LOG: Revision 1.16  2000/05/24 22:13:10  mmiers
 * LOG:
 * LOG:
 * LOG: const modifier
 * LOG:
 * LOG: Revision 1.15  2000/05/24 22:01:12  mmiers
 * LOG:
 * LOG:
 * LOG: More fixes for raw sockets.  Now 3 platforms down.
 * LOG:
 * LOG: Revision 1.14  2000/05/24 19:59:40  mmiers
 * LOG:
 * LOG:
 * LOG: Back this change out.  Special case only the windows code, its
 * LOG: the oddball here.
 * LOG:
 * LOG: Revision 1.13  2000/05/24 19:46:44  mmiers
 * LOG:
 * LOG:
 * LOG: Work around an NT limitation.
 * LOG:
 * LOG: Revision 1.12  2000/05/24 14:43:15  mmiers
 * LOG:
 * LOG:
 * LOG: Figuring out path MTU.
 * LOG:
 * LOG: Revision 1.11  2000/05/23 18:53:12  mmiers
 * LOG:
 * LOG:
 * LOG: bind() on RawOpen
 * LOG:
 * LOG: Revision 1.10  2000/05/23 18:47:33  mmiers
 * LOG:
 * LOG:
 * LOG: Socket API update.
 * LOG:
 * LOG: Revision 1.9  2000/05/23 14:40:49  mmiers
 * LOG:
 * LOG:
 * LOG: Fix a few typo bugs.
 * LOG:
 * LOG: Revision 1.8  2000/05/22 23:48:21  mmiers
 * LOG:
 * LOG:
 * LOG: Unix domain datagram sockets.
 * LOG:
 * LOG: Revision 1.7  2000/05/22 16:01:55  mmiers
 * LOG:
 * LOG:
 * LOG: Add RAW socket type.
 * LOG:
 * LOG: Revision 1.6  2000/05/22 15:50:41  mmiers
 * LOG:
 * LOG:
 * LOG: Add RAW socket support.
 * LOG:
 * LOG: Revision 1.5  2000/05/03 21:07:17  mmiers
 * LOG:
 * LOG:
 * LOG: Start adding support for reader/writer locks.
 * LOG: Add SOCK_GetPeerName().
 * LOG:
 * LOG: Revision 1.4  2000/02/10 14:48:12  mmiers
 * LOG:
 * LOG: Add functions for network/host conversion so they're always in our
 * LOG: namespace.
 * LOG:
 * LOG: Revision 1.3  2000/01/06 02:34:41  mmiers
 * LOG:
 * LOG:
 * LOG: Correct the build on UNIX platforms.
 * LOG:
 * LOG: Revision 1.2  2000/01/05 00:25:02  mmiers
 * LOG:
 * LOG:
 * LOG: Tweaks for RUDP.
 * LOG:
 * LOG: Revision 1.1  1999/12/16 16:16:28  mmiers
 * LOG: Sanitize the build environment a bit.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:28:08  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.19  1999/11/22 19:23:33  mmiers
 * LOG:
 * LOG:
 * LOG: Cleanup from Linux build.  Removed nested comment in iniparse,
 * LOG: cleaned up decls in gdi_trans.
 * LOG:
 * LOG: Revision 1.18  1999/10/15 23:04:35  labuser
 * LOG:
 * LOG:
 * LOG: close() on UNIX, not closesocket().
 * LOG:
 * LOG: Revision 1.17  1999/10/14 15:38:38  mmiers
 * LOG:
 * LOG:
 * LOG: Remove memory leaks from socket creation.  Publish
 * LOG: ReConnect/ReAccept APIs.
 * LOG:
 * LOG: Revision 1.16  1999/10/05 15:53:33  mmiers
 * LOG:
 * LOG:
 * LOG: Add permission setting to UNIX domain sockets.
 * LOG:
 * LOG: Revision 1.15  1999/08/31 21:11:37  labuser
 * LOG:
 * LOG:
 * LOG: Fixes for UNIX domain sockets.
 * LOG:
 * LOG: Revision 1.14  1999/08/09 20:08:11  labuser
 * LOG:
 * LOG:
 * LOG: Be a little paranoid about cleaning up UNIX domain socket files.
 * LOG:
 * LOG: Revision 1.13  1999/06/24 00:59:13  mmiers
 * LOG:
 * LOG:
 * LOG: Add an IPC type semaphore
 * LOG:
 * LOG: Revision 1.12  1999/03/01 21:31:34  mmiers
 * LOG:
 * LOG:
 * LOG: Move the address variable for DNS config.
 * LOG:
 * LOG: Revision 1.11  1999/03/01 21:26:19  mmiers
 * LOG:
 * LOG:
 * LOG: Make DNS usage a configurable option for sockets.
 * LOG:
 * LOG: Revision 1.10  1999/02/25 23:03:45  mmiers
 * LOG:
 * LOG:
 * LOG: Fixes for CC.
 * LOG:
 * LOG: Revision 1.9  1998/12/11 21:58:27  rsonak
 * LOG: Fix some socket related bugs.
 * LOG:
 * LOG: Revision 1.8  1998/11/19 02:18:10  mmiers
 * LOG: Straighten out a few potential bugs.
 * LOG:
 * LOG: Revision 1.7  1998/11/17 14:58:17  mmiers
 * LOG: #include <ctype.h>
 * LOG:
 * LOG: Revision 1.6  1998/11/17 03:30:57  mmiers
 * LOG: Deal with gethostbyaddr() when appropriate.
 * LOG:
 * LOG: Revision 1.5  1998/11/16 23:35:10  mmiers
 * LOG: Get the OS right.
 * LOG:
 * LOG: Revision 1.4  1998/11/16 23:24:54  mmiers
 * LOG: Remove some WIN curiosities.
 * LOG:
 * LOG: Revision 1.3  1998/11/13 17:50:53  mmiers
 * LOG: Add UDP sockets to the collection.
 * LOG:
 * LOG: Revision 1.2  1998/09/28 16:07:25  mmiers
 * LOG: Fix long standing bug in hostname/addr resolution.  Affects all
 * LOG: platforms.
 * LOG:
 * LOG: Revision 1.1  1998/06/20 03:50:36  mmiers
 * LOG: Add Linux as a target.
 * LOG:
 * LOG: Revision 1.5  1998/05/14 20:46:00  mmiers
 * LOG: Remove references to non-associated projects.
 * LOG:
 * LOG: Revision 1.4  1998/04/13 21:16:30  mmiers
 * LOG: Resolving some cross-platform issues.
 * LOG:
 * LOG: Revision 1.3  1998/04/08 18:43:26  mmiers
 * LOG: Get sockets to build on Solaris.
 * LOG:
 * LOG: Revision 1.2  1998/04/08 17:25:28  mmiers
 * LOG: Work on sockets abstraction.
 * LOG:
 * LOG: Revision 1.1  1998/04/08 03:23:46  mmiers
 * LOG: Trace and sockets APIs.
 * LOG:
 * LOG: Revision 1.1  1998/02/25 20:38:39  ssharma
 * LOG: First cut version of the sockets library.
 * LOG:
 *
 ****************************************************************************/
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <arpa/nameser.h>

#include <its.h>
#include <its_sockets.h>
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

#ident "$Id: its_sockets.c,v 9.1.114.1.12.1.6.1.2.1 2020/02/14 11:36:10 jkchaitanya Exp $"

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
extern int ITS_tcpSndTimeOut;

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_CreateAddr
 *
 *  Purpose:
 *      Create the address structure appropriate for an INET addr
 *
 *  Input Parameters:
 *      host - the hostname or IP address (second form is dotted quad).
 *      port - the port number
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      sin - the INET address
 *      NULL - an error occurred
 *
 ****************************************************************************/
ITSDLLAPI int
SOCK_CreateAddr(ITS_SOCK_DOMAIN domain,
                const char* host_or_path, int port,
                void **data, int *size)
{

    if (domain == INET6_DOMAIN)
    {
        struct sockaddr_in6 *sin6;

        if ((sin6 = calloc(1, sizeof(struct sockaddr_in6))) == NULL)
        {
            return (ITS_ENOMEM);
        }

        if (inet_pton(AF_INET6, host_or_path, &sin6->sin6_addr) <= 0 )
        {
            ITS_TRACE_ERROR(("inet_pton failed"));
        }

        /* Set up pertinant info in sockaddr_in */
        sin6->sin6_family= AF_INET6;
        sin6->sin6_port = htons((u_short)port);

        *data = (void *)sin6;
        *size = sizeof(struct sockaddr_in6);

        return ITS_SUCCESS;
    }
    else if (domain == INET_DOMAIN)
    {

        struct sockaddr_in *sin;             /* ptr to INET domain addr data */ 
        u_long addr;

#if defined(USE_DNS)
        int    i;                            /* loop iterator */
        struct hostent     *hostinfo = NULL; /* host resolution structure */
        int    attempt = 0;                  /* count of resolve attempts */
        int    done = ITS_FALSE;             /* while termination */

        /*
         * Try for up to one minute to resolve hostname 
         * Close socket on failure because if we can't   
         * resolve then we don't have a use for it        
         */
        while (!done) 
        {
            ITS_BOOLEAN byName = isalpha(host_or_path[0]);
            done = ITS_TRUE; 

            if (byName)
            {
                hostinfo = gethostbyname(host_or_path);
            }
            else
            {
                addr = inet_addr(host_or_path);

                if ((int)addr == -1)
                {
                    hostinfo = gethostbyname(host_or_path);
                }
                else
                {
                    hostinfo = gethostbyaddr((char *)&addr,
                                             sizeof(addr),
                                             AF_INET);

                    if (hostinfo == NULL)
                    {
                        hostinfo = gethostbyname(host_or_path);
                    }
                }
            }

            if (hostinfo == NULL) 
            {
                /*
                 * If the error is TRY_AGAIN do so unless we have tried to 
                 * often already, in which case just timeout 
                 */
                switch (h_errno) 
                {    
                case TRY_AGAIN:
                    if (++attempt > MAX_RESOLVE_ATTEMPTS) 
                    {
                        return (ITS_EBADHOST);
                    } 
                    else
                    {
                        done = ITS_FALSE;

                        TIMERS_Sleep(5);
                    } 
                    break; 

                /* Any other error we just give up */ 
                default:
                    return (ITS_EINVALIDARGS);
                }
            }
        }
#else /* !USE_DNS */

        addr = inet_addr(host_or_path);

        if ((int)addr == -1)
        {
            return (ITS_EBADHOST);
        }

#endif /* USE_DNS */


        /* Allocate storage for sockaddr_in structure */ 
        if ((sin = calloc(1, sizeof(struct sockaddr_in))) == NULL)
        {
            return (ITS_ENOMEM);
        }

        /* Set up pertinant info in sockaddr_in */ 
        sin->sin_family = AF_INET;
        sin->sin_port = htons((u_short)port);

#if defined(USE_DNS)

        /* Find index into host list */ 
        for (i = 0; hostinfo->h_addr_list[i] != NULL; i++) 
        {    
            if (hostinfo->h_addrtype == AF_INET)
            {    
                if (hostinfo->h_length == sizeof(sin->sin_addr.s_addr))
                {  
                    break; 
                } 
            } 
        }

        /*
         * Err if nothing in list, otherwise get info into the sockaddr_in  
         * (I am not real sure that he error CAN happen, but I'll leave     
         *  this check in because it doesn't hurt...) 
         */
        if (hostinfo->h_addr_list[i] == NULL)
        {
            free(sin);

            return (ITS_EBADHOST);
        }             

        memcpy((void *)&sin->sin_addr.s_addr, (void *)hostinfo->h_addr,
               hostinfo->h_length);
#else

        sin->sin_addr.s_addr = addr;

#endif

        *data = (void *)sin;
        *size = sizeof(struct sockaddr_in);
        return (ITS_SUCCESS);
    }
    else if (domain == UNIX_DOMAIN)
    {
        struct sockaddr_un   *aun;           /* ptr to UNIX domain addr data */

        /* Allocate space for sockaddr_un structure */ 
        if ((aun = (struct sockaddr_un *)calloc(1, sizeof(struct sockaddr_un)))
            == NULL)
        {
            return (ITS_ENOMEM);
        }

        /* Set up pertinent sockaddr_un info */
        aun->sun_family = AF_UNIX;
        strcpy(aun->sun_path, host_or_path);

        /* Save this in our own dataspace */ 
        *data = (void *)aun;
        *size = sizeof(aun->sun_family) + strlen(aun->sun_path);
    }
    else
    {
        *data = NULL;
        *size = 0;

        return (ITS_EINVALIDARGS);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_ClientOpen.
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
SOCK_ClientOpenWithTMO(ITS_SocketInfo **sockInfo, ITS_SOCK_DOMAIN domain,
                       const char *host_or_path, int port)
{
    int                 dummy = 1;                    /* for setsockoption() */
    char                buf[BUF_SZ]={0};
    ITS_SocketInfo      *ret = NULL;

    /* Make sure we've got a valid pointer */
    ITS_C_ASSERT(sockInfo != NULL);

    *sockInfo = NULL;

    /* Initialize addr storage if we need to */
    if ( (ret = (ITS_SocketInfo *)calloc(1, sizeof(ITS_SocketInfo))) == NULL)
    {
        ITS_TRACE_ERROR(("Calloc failed. Error: %s errno: %d\n", strerror_r(errno, buf, BUF_SZ), errno));
        return (ITS_ENOMEM);
    }

#ifdef USE_IPV6
    if (domain == INET6_DOMAIN)
    {
        struct linger      linger;           /* for set linger */

        if (SOCK_CreateIpv6Addr(domain, host_or_path, port,
                    &ret->addr, &ret->asize) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("Failed to crate IPV6 socket:\n"));
            free(ret);

            return (ITS_EBADHOST);
        }

        /* Create a socket */
        if ((ret->socket = socket(AF_INET6, SOCK_STREAM, 0)) < 0)
        {
            free(ret->addr);
            free(ret);
            ITS_TRACE_ERROR(("socket failed:%s:errno: %d\n", strerror_r(errno, buf, BUF_SZ), errno));

            return (ITS_ENOSOCKET);
        }

        /* Set linger on, to 0 time */
        linger.l_onoff = 1;
        linger.l_linger = 0;
        if((setsockopt(ret->socket, SOL_SOCKET, SO_LINGER,
                        (char *)&linger, sizeof(struct linger))) < 0)
        {
            ITS_TRACE_ERROR(("setsockopt failed:socket:%d:%s:errno: %d\n",
                        ret->socket, strerror_r(errno, buf, BUF_SZ), errno));
        }

        /* Set SO_SNDTIMEO to set the send timeout. */
        struct timeval sndTv = {0, 0};

        sndTv.tv_sec = 0;
        sndTv.tv_usec = ITS_tcpSndTimeOut;

        if (setsockopt(ret->socket, SOL_SOCKET, SO_SNDTIMEO, &sndTv, sizeof(sndTv)) < 0 )
        {
            ITS_TRACE_ERROR(("setsockopt failed:%s: with error no %d",  strerror_r(errno, buf, BUF_SZ),  errno));

            return !ITS_SUCCESS;
        }

        /* Save off addr info in our own dataspace */
        ret->type = SPROT_TYPE_TCP_CLIENT;
        ret->af = AF_INET6;

        /* Set reuseaddr socket option */
        if ( (setsockopt(ret->socket, SOL_SOCKET, SO_REUSEADDR, (void *)&dummy, sizeof(int))) < 0)
        {
            ITS_TRACE_ERROR(("setsockopt failed:socket:%d:%s:errno: %d\n",
                        ret->socket, strerror_r(errno, buf, BUF_SZ), errno));
        }

        *sockInfo = ret;

        /* fini */
        return (ITS_SUCCESS);
    }
#endif

    /* get the address */
    if (SOCK_CreateAddr(domain, host_or_path, port,
                &ret->addr, &ret->asize) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("SOCK_CreateAddr failed:\n"));
        free(ret);

        return (ITS_EBADHOST);
    }

    /* setup if INET domain */
    if (domain == INET_DOMAIN)
    {
        struct linger      linger;           /* set linger structure */

        /* Create a socket */
        if ( (ret->socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            if (inet_ntop(AF_INET, &((struct sockaddr_in *)(ret->addr))->sin_addr.s_addr, buf, sizeof(buf)))
            {
                ITS_TRACE_ERROR(("socket cration Failed :%s:%d ", buf, ntohs(((struct sockaddr_in *)(ret->addr))->sin_port)));
            }

            ITS_TRACE_ERROR(("Error: %s errno: %d\n", strerror_r(errno, buf, BUF_SZ), errno));

            free(ret->addr);
            free(ret);

            return (ITS_ENOSOCKET);
        }

        /* Set linger on, to 0 time */
        linger.l_onoff = 1;
        linger.l_linger = 0;

        if ( (setsockopt(ret->socket, SOL_SOCKET, SO_LINGER,
                       (char *)&linger, sizeof(struct linger))) < 0)
        {
            if (inet_ntop(AF_INET, &((struct sockaddr_in *)(ret->addr))->sin_addr.s_addr, buf, sizeof(buf)))
            {
                ITS_TRACE_ERROR(("setSockopt Failed on:%s:%d socket %d", buf, ntohs(((struct sockaddr_in *)(ret->addr))->sin_port), ret->socket));
            }

            ITS_TRACE_ERROR(("Error: %s errno: %d\n", strerror_r(errno, buf, BUF_SZ), errno));
        }

        int enable_keep_alive = 1;

        if ( (setsockopt(ret->socket, SOL_SOCKET, SO_KEEPALIVE, &enable_keep_alive, sizeof(int))) < 0)
        {
            ITS_TRACE_ERROR(("setsockopt failed:%s: with error no %d", strerror_r(errno, buf, BUF_SZ), errno));
        }

        /* Set SO_SNDTIMEO to set the send timeout. */
        struct timeval sndTv = {0, 0};

        sndTv.tv_sec = 0;
        sndTv.tv_usec = ITS_tcpSndTimeOut;

        if (setsockopt(ret->socket, SOL_SOCKET, SO_SNDTIMEO, &sndTv, sizeof(sndTv)) < 0 )
        {
            ITS_TRACE_ERROR(("setsockopt failed:%s: with error no %d", strerror_r(errno, buf, BUF_SZ), errno));

            return !ITS_SUCCESS;
        }

        /* Save off addr info in our own dataspace */
        ret->type = SPROT_TYPE_TCP_CLIENT;
        ret->af = AF_INET;

        *sockInfo = ret;
    }
    /* Setup for UNIX domain */
    else if (domain == UNIX_DOMAIN)
    {
        /* Create a socket */
        if ((ret->socket = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
        {
            ITS_TRACE_ERROR(("socket failed:%s:errno: %d\n", strerror_r(errno, buf, BUF_SZ), errno));
            free(ret->addr);
            free(ret);

            return (ITS_EBADSOCKET);
        }

        /* Save this in our own dataspace */
        ret->type = SPROT_TYPE_LOCAL_CLIENT;
        ret->af = AF_UNIX;

        *sockInfo = ret;
    }
    /* Any other domain in invalid */
    else
    {
        free(ret->addr);
        free(ret);
        ITS_TRACE_ERROR(("INVALID socket:\n"));

        return (ITS_EINVALIDARGS);
    }

    /* Set re-use addr socket option */
    if ( (setsockopt(ret->socket, SOL_SOCKET, SO_REUSEADDR,
                    (void *)&dummy, sizeof(int))) < 0)
    {
        if (inet_ntop(AF_INET, &((struct sockaddr_in *)(ret->addr))->sin_addr.s_addr, buf, sizeof(buf)))
        {
            ITS_TRACE_ERROR(("setSockopt Failed on:%s:%d socket %d", buf, ntohs(((struct sockaddr_in *)(ret->addr))->sin_port), ret->socket));
        }

        ITS_TRACE_ERROR(("Error: %s errno: %d\n", strerror_r(errno, buf, BUF_SZ), errno));
    }

    /* fini */
    return (ITS_SUCCESS);
}

ITSDLLAPI int
SOCK_CreateIpv6Addr(ITS_SOCK_DOMAIN domain,
                const char* host_or_path, int port,
                void **data, int *size)
{
#ifdef USE_IPV6
    int ifid = 0;
    if (domain == INET6_DOMAIN)
    {
        struct sockaddr_in6 *sin6;
        u_long addr;

        if ((sin6 = calloc(1, sizeof(struct sockaddr_in6))) == NULL)
        {
            return (ITS_ENOMEM);
        }

        if (inet_pton(AF_INET6, host_or_path, &sin6->sin6_addr) <= 0 )
        {
            ITS_TRACE_ERROR(("inet_pton"));
        }

        /* Set up pertinant info in sockaddr_in */
        sin6->sin6_family= AF_INET6;
        sin6->sin6_port = htons((u_short)port);

        ifid = if_nametoindex("eth0");
        sin6->sin6_scope_id = ifid;

        *data = (void *)sin6;
        *size = sizeof(struct sockaddr_in6);
   
    }
#endif
    return ITS_SUCCESS;
}


/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_ClientOpen.
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
SOCK_ClientOpen(ITS_SocketInfo **sockInfo, ITS_SOCK_DOMAIN domain,
                const char *host_or_path, int port) 
{
    int                 dummy = 1;                    /* for setsockoption() */
    ITS_SocketInfo      *ret = NULL;

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
        struct linger      linger;           /* for set linger */

        if (SOCK_CreateIpv6Addr(domain, host_or_path, port,
                    &ret->addr, &ret->asize) != ITS_SUCCESS)
        {
            free(ret);

            return (ITS_EBADHOST);
        }


        /* Create a socket */ 
        if ((ret->socket = socket(AF_INET6, SOCK_STREAM, 0)) < 0) 
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
        ret->type = SPROT_TYPE_TCP_CLIENT;
        ret->af = AF_INET6;

        /* Set reuseaddr socket option */ 
        setsockopt(ret->socket, SOL_SOCKET, SO_REUSEADDR,
               (void *)&dummy, sizeof(int));

        *sockInfo = ret;
        /* fini */ 
        return (ITS_SUCCESS);

    }
#endif


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
        struct linger      linger;           /* set linger structure */

        /* Create a socket */ 
        if ((ret->socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
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
        ret->type = SPROT_TYPE_TCP_CLIENT;
        ret->af = AF_INET;

        *sockInfo = ret;
    }
    /* Setup for UNIX domain */ 
    else if (domain == UNIX_DOMAIN) 
    {
        /* Create a socket */ 
        if ((ret->socket = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) 
        {
            free(ret->addr);
            free(ret);

            return (ITS_EBADSOCKET);
        }

        /* Save this in our own dataspace */ 
        ret->type = SPROT_TYPE_LOCAL_CLIENT;
        ret->af = AF_UNIX;

        *sockInfo = ret;
    }
    /* Any other domain in invalid */ 
    else
    {
        free(ret->addr);
        free(ret);

        return (ITS_EINVALIDARGS);
    }

    /* Set re-use addr socket option */ 
    setsockopt(ret->socket, SOL_SOCKET, SO_REUSEADDR,
               (void *)&dummy, sizeof(int));

    /* fini */ 
    return (ITS_SUCCESS);
        
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_ClientOpen.
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
SOCK_ServerOpen(ITS_SocketInfo **sockInfo, ITS_SOCK_DOMAIN domain,
                const char *host_or_path, int port) 
{
    int    dummy = 1;       /* for socket option */
    ITS_SocketInfo *ret;

#if 0
    /* Make sure the address is good */
    ITS_C_ASSERT(sockInfo != NULL);
#endif
    *sockInfo = NULL;

    /* Set up our addr info accounting */ 
    if ((ret = (ITS_SocketInfo *)calloc(1, sizeof(ITS_SocketInfo))) == NULL)
    {    
        return (ITS_ENOMEM);
    }


    /* setup if INET domain */
#ifdef USE_IPV6
    if (domain == INET6_DOMAIN)
    {
        /* get the address */
        struct linger      linger;           /* for set linger */

        if (SOCK_CreateIpv6Addr(domain, host_or_path, port,
                            &ret->addr, &ret->asize) != ITS_SUCCESS)
        {
            free(ret);

            return (ITS_EBADHOST);
        }
        
        /* Create a socket */
        if ((ret->socket = socket(AF_INET6, SOCK_STREAM, 0)) < 0)
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
        ret->type = SPROT_TYPE_TCP_SERVER;
        ret->af = AF_INET6;


        /* bind to the port specified */ 
        struct sockaddr_in6 addr6;
        bzero(&addr6, sizeof(addr6));  
        addr6.sin6_family = AF_INET6;
        addr6.sin6_port = htons(port);

        if (inet_pton(AF_INET6, "0::0", &addr6.sin6_addr) <= 0 )
        {
            ITS_TRACE_ERROR(("inet_pton failed"));
        }



        if (bind(ret->socket, (struct sockaddr*)&addr6, sizeof(addr6)) < 0) 
        {
            free(ret->addr);
            close(ret->socket);
            free(ret);

            return (ITS_EBINDFAIL);
        }
        if (listen(ret->socket, SOMAXCONN) < 0)
        {
            unlink(host_or_path);

            free(ret->addr);
            close(ret->socket);
            free(ret);

            return (ITS_ELISTENFAIL);
        }

        *sockInfo = ret;
        return (ITS_SUCCESS);
    }
#endif


    /* get the address */
    if (SOCK_CreateAddr(domain, host_or_path, port,
                        &ret->addr, &ret->asize) != ITS_SUCCESS)
    {
        free(ret);

        return (ITS_EBADHOST);
    }
    if (domain == INET_DOMAIN) 
    {
        struct linger      linger;           /* for set linger */ 

        /* Create a socket */ 
        if ((ret->socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
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
        ret->type = SPROT_TYPE_TCP_SERVER;
        ret->af = AF_INET;

    }
    /* Setup for UNIX domain */
    else if (domain == UNIX_DOMAIN)
    {
        /* clean up the remnants */
        unlink(host_or_path);

        /* Create a socket */ 
        if ((ret->socket = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) 
        {    
            free(ret->addr);
            free(ret);

            return (ITS_ENOSOCKET);
        } 

        /* Save this in our own datapsace */ 
        ret->type = SPROT_TYPE_LOCAL_SERVER;
        ret->af = AF_UNIX;

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

        return (ITS_EBINDFAIL);
    }

    /* change the permission bits on the socket */
    if (domain == UNIX_DOMAIN)
    {
        if (chmod(host_or_path, DEFAULT_MODE_MASK) < 0)
        {
            unlink(host_or_path);
 
            free(ret->addr);
            close(ret->socket);
            free(ret);
 
            return (ITS_EINVALIDARGS);
        }
    }
 
    /* Set up a listen queue */ 
    if (listen(ret->socket, SOMAXCONN) < 0)
    {
        unlink(host_or_path);

        free(ret->addr);
        close(ret->socket);
        free(ret);

        return (ITS_ELISTENFAIL);
    }
    *sockInfo = ret;

    /* fini */
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_EndPointOpen.
 *
 *  Purpose:
 *     Create an end socket and resolve hostname
 *
 *  Input Parameters:
 *      host_or_path        local hostname
 *      port                local port number
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
SOCK_EndPointOpen(ITS_SocketInfo **sockInfo, ITS_SOCK_DOMAIN domain,
                  const char *host_or_path, int port)
{
    int    dummy = 1;                    /* for socket option */
    char buf[BUF_SZ]={0};
    ITS_SocketInfo *ret;
    struct linger      linger;           /* for set linger */

    /* Make sure the address is good */
    ITS_C_ASSERT(sockInfo != NULL);

    /* Set up our addr info accounting */
    if ((ret = (ITS_SocketInfo *)calloc(1, sizeof(ITS_SocketInfo))) == NULL)
    {
        ITS_TRACE_ERROR(("calloc failed:\n"));
        return (ITS_ENOMEM);
    }

    /* get the address */
    if (SOCK_CreateAddr(domain, host_or_path, port,
                        &ret->addr, &ret->asize) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("SOCK_CreateAddr failed:\n"));
        free(ret);

        return (ITS_EBADHOST);
    }

    /* Create a socket */
    if (domain == INET_DOMAIN)
    {
        if ((ret->socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        {
            ITS_TRACE_ERROR(("socket failed:%s:errno: %d\n", strerror_r(errno, buf, BUF_SZ), errno));

            free(ret->addr);
            free(ret);

            return (ITS_ENOSOCKET);
        }

        /* Set linger on, to 0 time */
        linger.l_onoff = 1;
        linger.l_linger = 0;
        if((setsockopt(ret->socket, SOL_SOCKET, SO_LINGER,
                   (char *)&linger, sizeof(struct linger))) < 0)
        {
            ITS_TRACE_ERROR(("setsockopt failed:socket:%d:%s:errno: %d\n",
                                                ret->socket, strerror_r(errno, buf, BUF_SZ), errno));
        }

        /* Save off addr info in our own dataspace */
        ret->type = SPROT_TYPE_UDP;
        ret->af = AF_INET;

        *sockInfo = ret;

        /* Set reuseaddr socket option */
        if ( (setsockopt(ret->socket, SOL_SOCKET, SO_REUSEADDR,
                   (void *)&dummy, sizeof(int))) < 0)
        {
            ITS_TRACE_ERROR(("setsockopt failed:socket:%d:%s:errno: %d\n",
                                                ret->socket, strerror_r(errno, buf, BUF_SZ), errno));
        }

	/* Set SO_SNDTIMEO to set the send timeout. */
        struct timeval sndTv = {0, 0};

        sndTv.tv_sec = 0;
        sndTv.tv_usec = ITS_tcpSndTimeOut;

        if (setsockopt(ret->socket, SOL_SOCKET, SO_SNDTIMEO, &sndTv, sizeof(sndTv)) < 0 )
        {
            ITS_TRACE_ERROR(("setsockopt failed:%s: with error no %d", strerror_r(errno, buf, BUF_SZ), errno));

            return !ITS_SUCCESS;
	}
    }
    else if (domain == UNIX_DOMAIN)
    {
        /* clean up the remnants */
        unlink(host_or_path);

        /* Create a socket */ 
        if ((ret->socket = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0) 
        {    
            free(ret->addr);
            free(ret);

            return (ITS_ENOSOCKET);
        } 

        /* Save this in our own datapsace */ 
        ret->type = SPROT_TYPE_LOCAL_DATAGRAM;
        ret->af = AF_UNIX;

        *sockInfo = ret;
    }
    /* Any other domain is invalid */ 
    else
    {
        free(ret->addr);
        free(ret);

        return (ITS_EINVALIDARGS);
    }

    /* bind to the port specified */ 
    if (bind(ret->socket, (struct sockaddr *)ret->addr, ret->asize) < 0) 
    {
        free(ret->addr);
        close(ret->socket);
        free(ret);

        return (ITS_EBINDFAIL);
    }

    /* change the permission bits on the socket */
    if (domain == UNIX_DOMAIN)
    {
        if (chmod(host_or_path, DEFAULT_MODE_MASK) < 0)
        {
            unlink(host_or_path);

            free(ret->addr);
            close(ret->socket);
            free(ret);

            return (ITS_EINVALIDARGS);
        }
    }

    /* fini */
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_ServerAcceptWithTMO.
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
SOCK_ServerAcceptWithTMO(ITS_SocketInfo* info, ITS_SocketInfo **newInfo)
{
    char                buf[BUF_SZ];
    int                flag = 1;          /* for setsockopt() call */
    struct protoent    *ent;  /* protocol entry */
    ITS_SocketInfo     *tmp;
    ITS_SocketInfo     tmp1;

    if (!info)
    {
        return (ITS_ECONNECTFAIL);
    }

    ITS_C_ASSERT(newInfo != NULL);

    *newInfo = NULL;

    /* allocate info struct */
    if ( (tmp = (ITS_SocketInfo *)calloc(1, sizeof(ITS_SocketInfo))) == NULL)
    {
        ITS_TRACE_ERROR(("Calloc failed. Error: %s errno: %d\n", strerror_r(errno, buf, BUF_SZ), errno));

        return (ITS_ENOMEM);
    }

    /* Allocate storage for addr structure */
    if ( (tmp->addr = (struct sockaddr_un *)calloc(1,
                                                  sizeof(struct sockaddr_un)))
        == NULL)
    {
        ITS_TRACE_ERROR(("Calloc failed. Error: %s errno: %d\n", strerror_r(errno, buf, BUF_SZ), errno));
        free(tmp);

        return (ITS_ENOMEM);
    }

    /* Accept a connection */
    tmp->asize = sizeof(struct sockaddr_un);
    tmp->socket = accept(info->socket, tmp->addr, (socklen_t*)&tmp->asize);

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
        ITS_TRACE_ERROR(("SOCK_GetPeerName failed:\n"));
        free(tmp->addr);
        free(tmp);

        return (ITS_EBADSOCKET);
    }

    /* We don't need tmp1 anymore */
    free(tmp1.addr);

    /* Update our socket data info */
    tmp->af = ((struct sockaddr_un *)tmp->addr)->sun_family;

    /* Set SO_SNDTIMEO to set the send timeout. */
    struct timeval sndTv = {0, 0};

    sndTv.tv_sec = 0;
    sndTv.tv_usec = ITS_tcpSndTimeOut;

    if (setsockopt(tmp->socket, SOL_SOCKET, SO_SNDTIMEO, &sndTv, sizeof(sndTv)) < 0 )
    {
        ITS_TRACE_ERROR(("setsockopt failed:%s: with error no %d",  strerror_r(errno, buf, BUF_SZ),  errno));

        return !ITS_SUCCESS;
    }

    /* Get rid of nagle support */
    if (tmp->af == AF_INET && (ent = getprotobyname("tcp")) != NULL)
    {
        if ( (setsockopt(tmp->socket, ent->p_proto,
                        TCP_NODELAY, (char *)&flag, sizeof(flag))) < 0)
        {
            ITS_TRACE_ERROR(("connect failed:socket:%d:%s:errno: %d\n",
                        tmp->socket, strerror_r(errno, buf, BUF_SZ), errno));
        }
    }

    *newInfo = tmp;

    /* fini */
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_Ipv6ServerAcceptWithTMO.
 *
 *  Purpose:
 *      Accept a connection
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
SOCK_Ipv6ServerAcceptWithTMO(ITS_SocketInfo* info, ITS_SocketInfo **newInfo)
{
#ifdef USE_IPV6
    char                buf[BUF_SZ];
    ITS_SocketInfo      *tmp;

    if (!info)
    {
        return (ITS_ECONNECTFAIL);
    }

    ITS_C_ASSERT(newInfo != NULL);

    *newInfo = NULL;

    /* allocate info struct */
    if ( (tmp = (ITS_SocketInfo *)calloc(1, sizeof(ITS_SocketInfo))) == NULL)
    {
        ITS_TRACE_ERROR(("Calloc failed. Error: %s errno: %d\n", strerror_r(errno, buf, BUF_SZ), errno));
        return (ITS_ENOMEM);
    }

    /* Allocate storage for addr structure */
    if ( (tmp->addr = (struct sockaddr_un *)calloc(1,
                                                  sizeof(struct sockaddr_un)))
        == NULL)
    {
        ITS_TRACE_ERROR(("Calloc failed. Error: %s errno: %d\n", strerror_r(errno, buf, BUF_SZ), errno));
        return (ITS_ENOMEM);
    }

    /* Accept a connection */
    struct sockaddr_in6 addr;
    int size = sizeof(addr);
    int client;
    addr.sin6_family = AF_INET6;

    if (inet_pton(AF_INET6, "0::0", &addr.sin6_addr) <= 0 )
    {
        ITS_TRACE_ERROR(("inet_pton failed"));
    }

    client = accept(info->socket, (struct sockaddr*)&addr, (socklen_t*)&size);

    tmp->asize = sizeof(struct sockaddr_in6);
    tmp->socket = client;

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

    tmp->af = AF_INET6;

    /* Set SO_SNDTIMEO to set the send timeout. */
    struct timeval sndTv = {0, 0};

    sndTv.tv_sec = 0;
    sndTv.tv_usec = ITS_tcpSndTimeOut;

    if (setsockopt(tmp->socket, SOL_SOCKET, SO_SNDTIMEO, &sndTv, sizeof(sndTv)) < 0 )
    {
        ITS_TRACE_ERROR(("setsockopt failed:%s: with error no %d",  strerror_r(errno, buf, BUF_SZ),  errno));

        return !ITS_SUCCESS;
    }

    *newInfo = tmp;
#endif
    /* fini */
    return (ITS_SUCCESS);
}


/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_RawOpen.
 *
 *  Purpose:
 *      This will create a raw socket and resolve the target server's
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
SOCK_RawOpen(ITS_SocketInfo **sockInfo, ITS_SOCK_DOMAIN domain,
             const char *host_or_path, int port, int pf,
             ITS_BOOLEAN autoHeaders) 
{
    int                 dummy = 1;                    /* for setsockoption() */
    ITS_SocketInfo      *ret = NULL;

    /* Make sure we've got a valid pointer */
    ITS_C_ASSERT(sockInfo != NULL);

    *sockInfo = NULL;

    /* Initialize addr storage if we need to */ 
    if ((ret = (ITS_SocketInfo *)calloc(1, sizeof(ITS_SocketInfo))) == NULL)
    {
        return (ITS_ENOMEM);
    }

    if(SOCK_CreateAddr(domain, host_or_path, port, &ret->addr,
                       &ret->asize) != ITS_SUCCESS)
    {
        free(ret);

        return ITS_EBADHOST;
    }

    /* setup if INET domain */ 
    if (domain != INET_DOMAIN)
    {
        free(ret->addr);
        free(ret);

        return (ITS_EINVALIDARGS);
    }
    else
    {
        struct linger      linger;           /* set linger structure */

        /* Create a socket */ 
        if ((ret->socket = socket(AF_INET, SOCK_RAW, pf)) < 0) 
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
        ret->type = SPROT_TYPE_RAW;
        ret->af = AF_INET;

        *sockInfo = ret;
    }

    /*
     * if user wants automatic IP header generated, clear this
     * On linux this is off by default.
     */
    if (autoHeaders)
    {
        dummy = 0;
        setsockopt(ret->socket, IPPROTO_IP, IP_HDRINCL,
                   (void *)&dummy, sizeof(int));
    }

    /* fini */ 
    return (ITS_SUCCESS);
        
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_Pending.
 *
 *  Purpose:
 *      Use this to see how many bytes can be gotten from a subsequent read() 
 *      call.  Note that this will return a number meaning that _at least_ so 
 *      many bytes can be read, because more data may be received in between 
 *      the time this call is made and the actual read() system call is made
 *
 *  Input Parameters:
 *      int     sock                File descriptor to check
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      <0              An error occured
 *      (Other)         Number of bytes available (may be 0)
 *
 ****************************************************************************/
ITSDLLAPI int
SOCK_Pending(ITS_SocketInfo *info)
{    
    int bytes_pending = 0;       /* ioctl() will fill in with #bytes ready */  
    int rc;                      /* return code */  

    if (!info)
    {
        return (ITS_ECONNECTFAIL);
    }

    /* If error display and return -1 else return bytes pending */ 
    if (ioctl(info->socket, FIONREAD, &bytes_pending) < 0) 
    {
        rc= ITS_EINVALIDARGS; 
    } 
    else
    {    
        rc = bytes_pending; 
    }

    return rc;  
} 
    
/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_ReadyToRead.  
 *
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      int    sock              File descriptor to check 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - data pending
 *      ITS_FALSE - no data or error.
 *
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
SOCK_ReadyToRead(ITS_SocketInfo* info) 
{    
    fd_set fds;

    if (!info)
    {
        return (ITS_FALSE);
    }

    FD_ZERO(&fds);
    FD_SET(info->socket, &fds);

    if (select(info->socket + 1, &fds, NULL, NULL, NULL) > 0)
    {
        return (ITS_TRUE);
    }
    else
    {
        return (ITS_FALSE);
    }
} 

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_ClientConnect.
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
SOCK_ClientConnect(ITS_SocketInfo* info)
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
    if (connect(info->socket, info->addr, info->asize) < 0)
    {
        return (ITS_ECONNECTFAIL);
    } 

    /*
     * Disable TCP NAGLE algorighm. (don't delay short messages waiting for 
     * window ack)
     */
    if (info->af == AF_INET && (ent = getprotobyname("tcp")) != NULL)
    {    
        setsockopt(info->socket, ent->p_proto,
                   TCP_NODELAY, (char *)&flag, sizeof(flag));
    }

    /*
     * fini 
     */
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_ClientIpv6Connect.
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
SOCK_ClientIpv6Connect(ITS_SocketInfo* info)
{
#ifdef USE_IPV6
    struct protoent     *ent;                /* For use in disabling nagle */ 
    int flag = 1;                            /* For use in disabling nagle */

    if (!info)
    {
        return (ITS_ECONNECTFAIL);
    }
    setsockopt(info->socket, SOL_SOCKET, SO_BINDTODEVICE, "eth0\0", 5);
    /*
     * Attempt connection 
     */
    if (connect(info->socket, info->addr, info->asize) < 0)
    {
        return (ITS_ECONNECTFAIL);
    } 

   

    /*
     * Disable TCP NAGLE algorighm. (don't delay short messages waiting for 
     * window ack)
     */
    if (info->af == AF_INET6 && (ent = getprotobyname("tcp")) != NULL)
    {    
        setsockopt(info->socket, ent->p_proto,
                   TCP_NODELAY, (char *)&flag, sizeof(flag));
    }
#endif
	return (ITS_SUCCESS);
}


/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_ServerAccept.
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
SOCK_ServerAccept(ITS_SocketInfo* info, ITS_SocketInfo **newInfo)
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
                                                  sizeof(struct sockaddr_un)))
        == NULL)
    {    
        free(tmp);
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

    /* Get rid of nagle support */ 
    if (tmp->af == AF_INET && (ent = getprotobyname("tcp")) != NULL) 
    {    
        setsockopt(tmp->socket, ent->p_proto,
                   TCP_NODELAY, (char *)&flag, sizeof(flag));
    }

    *newInfo = tmp;

    /* fini */ 
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_Ipv6ServerAccept.
 *
 *  Purpose:
 *      Accept a connection 
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
SOCK_Ipv6ServerAccept(ITS_SocketInfo* info, ITS_SocketInfo **newInfo)
{
#ifdef USE_IPV6
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
                                                  sizeof(struct sockaddr_un)))
        == NULL)
    {
        free(tmp);
        return (ITS_ENOMEM);
    }

    /* Accept a connection */ 
    struct sockaddr_in6 addr;
    int size=sizeof(addr), client;
    addr.sin6_family = AF_INET6;
    if ( inet_pton(AF_INET6, "0::0", &addr.sin6_addr) <= 0 )
    {
        ITS_TRACE_ERROR(("inet_pton failed"));
    }
    client = accept(info->socket, (struct sockaddr*)&addr, &size);

    tmp->asize = sizeof(struct sockaddr_in6);
    tmp->socket = client;

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

    *newInfo = tmp;
#endif
    /* fini */ 
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
ITSDLLAPI int
SOCK_Read(ITS_SocketInfo* info, char *buf, int nbytes) 
{
    int     nleft;                    /* Amount of data left to read */      
    int     nread;                    /* Amount of data we have read */ 
    int     done = ITS_FALSE;             /* Loop terminator for EOF      */  

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
        nread = read(info->socket, buf, nleft); 

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
 *      void *from                     who the message came from
 *      int *len                       length of the orig addr
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
SOCK_Recv(ITS_SocketInfo* info, char *buf, int nbytes, void* from, int* len) 
{
    if (!info)
    {
        return (0);
    }

    /* Read something */ 
    return recvfrom(info->socket, buf, nbytes, 0, from, (socklen_t *)len); 
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_NonBlockingRead.
 *
 *  Purpose:
 *      This is a nonblocking read that will timeout if it does not receive the
 *      specified amount of data in the time indicated.   
 *
 *  Input Parameters:
 *      int fd                   file descriptor of socket to read from 
 *      char *dataptr            pointer to buffer to write to 
 *      int datasize             amount of bytes to attempt reading 
 *      int maxtime              time in seconds to wait for data 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      0                          EOF or TIMEOUT or ERROR has occured  
 *      default                    The amount of bytes read
 ****************************************************************************/
ITSDLLAPI int
SOCK_NonBlockingRead(ITS_SocketInfo* info, char *buf, int size, int maxtime) 
{ 
    time_t     start_time, now_time;    /* Used to check for timeout */  
    int        ioctl_val = 1;           /* value for ioctl() call */
    int        br = 0;                  /* bytes read in single read() */ 
    int        rc = 0;                  /* function return code */ 
    int        done = ITS_FALSE;            /* while() terminator */ 
    int        totalread = 0;           /* bytes read in total */ 

 
    /* Note the time we started */ 
    time(&start_time); 

    if (!info)
    {
        return (0);
    }

    /* Set this socket to nonblocking */ 
    ioctl_val = 1;
    if (ioctl(info->socket, FIONBIO, &ioctl_val) < 0) 
    {
        return (0);
    }  

    /* While we are not done, try to read */ 
    while(!done) 
    {
        /* Read some data */ 
        switch ((br = read(info->socket, buf + totalread, size - totalread)))
        {
            /* An error has occured */ 
            case -1: 
            switch(errno) 
            {
            /* Resource temporarily unavailable (no data yet) */ 
            case EAGAIN: 
            case EINPROGRESS:  
                break; 

            /* Recover from interrupt errors */ 
            case EINTR: 
            case EDEADLK: 
            case EBUSY:
                break; 
 
            /* Any other error */ 
            default: 
                done = ITS_TRUE;
                rc = 0;  
                break; 
            } 
            break; 

            /* EOF (peer has closed connection) */ 
            case 0:
            done = ITS_TRUE;
            rc=0;  
            break;

            /* We have read some amount of data */ 
            default:
            totalread += br;   
            if (totalread >= size) 
            {    
                done = ITS_TRUE;
            } 
            break; 
        }
        
        /* Set the return code (may be reset in timeout below) */ 
        rc = totalread;
 
        /*
         * Check to see if we have timed out if we are not already done 
         */
        if (!done) 
        {    
            time(&now_time); 
            if (now_time > start_time + maxtime) 
            {    
                done = ITS_TRUE;
            }
        }
    } 

   /* Set this socket back to blocking */
   ioctl_val = 0; 
   if (ioctl(info->socket, FIONBIO, &ioctl_val) < 0)
   {
       /* what to do? */
   }

    /* fini */
    return rc; 
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
ITSDLLAPI int
SOCK_Write(ITS_SocketInfo* info, char *buf, int nbytes) 
{
    int    nleft;
    int    nwritten;

    /* Set up how much we need to write */ 
    nleft = nbytes;

    if (!info)
    {
        return (0);
    }

    struct sockaddr addr;
    socklen_t addrSz = sizeof(struct sockaddr);
    if (getpeername(info->socket, &addr, &addrSz) != 0)
    {
        ITS_TRACE_ERROR(("getpeername failed...errno = %d\n\n", errno));
        return (ITS_EBADSOCKET);
    }

    /* While still bytes to write do so */ 
    while (nleft > 0)
    {
        /* Write some data */ 
        nwritten = write(info->socket, buf, nleft); 

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
SOCK_WriteOnce(ITS_SocketInfo* info, char *buf, int nbytes, int *error)
{
     int    nwritten = 0;
     if (!info)
     {
	return (0);
     }
     *error = 0;

     /* Write some data */
     nwritten = write(info->socket, buf, nbytes);

     /* If any of these errors return # actually written */
     if (nwritten <= 0)
     {
	*error = errno;
	if ( (*error == EWOULDBLOCK) || (*error == EAGAIN))
	{
	     nwritten = 0;
	}

	ITS_TRACE_CRITICAL(("Write Failed Errno = %d\n\n", errno));
     }

     return nwritten;
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
 *      void *to             address to send to
 *      int len              length of addr to send to
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
SOCK_Send(ITS_SocketInfo* info, char *buf, int nbytes, void* to, int len) 
{
    /* Write some data */ 
    return sendto(info->socket, buf, nbytes, 0, to, len); 
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_NonBlockingWrite.
 *
 *  Purpose:
 *      This is a nonblocking write that will timeout if it does not receive the
 *      specified amount of data in the time indicated. 
 *
 *  Input Parameters:
 *      int fd                  file descriptor of socket to write from 
 *      char *dataptr           pointer to buffer to write to 
 *      int datasize            amount of bytes to attempt writeing 
 *      int maxtime             time in seconds to wait for data 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      0                          EOF or TIMEOUT or ERROR has occured  
 *      default                    The amount of bytes actually written
 ****************************************************************************/
ITSDLLAPI int
SOCK_NonBlockingWrite(ITS_SocketInfo* info, char *buf, int size, int maxtime) 
{ 
    time_t    start_time, now_time;        /* Used to check for timeout */  
    int       ioctl_val = 1;              /* value for ioctl() call */
    int       br = 0;                    /* bytes write in single write() */ 
    int       rc = 0;                    /* function return code */ 
    int       done = ITS_FALSE;              /* while() terminator */ 
    int       totalwrite = 0;           /* bytes write in total */ 
    int       write_attempt_size = 0;     /* Amount of bytes to attempt */ 
                                           /* to write on a single write()*/ 
 
    /* Note the time we started */ 
    time(&start_time); 

    if (!info)
    {
        return (0);
    }

    /* Set this socket to nonblocking */ 
    ioctl_val = 1;
    if (ioctl(info->socket, FIONBIO, &ioctl_val) < 0) 
    {
        return (0);
    } 

    /* While we are not done, try to write */ 
    while(!done) 
    {
        /* Optimize write for ethernet */ 
        write_attempt_size = size - totalwrite; 
        if (write_attempt_size > 1400) 
        {
            write_attempt_size = 1400; 
        } 
    
        /* Read some data */ 
        switch((br = write(info->socket, buf + totalwrite, write_attempt_size)))
        {
        /* An error has occured */ 
        case -1: 
            switch(errno) 
            {
            /* Resource temporarily unavailable (no data yet) */ 
            case EAGAIN: 
            case EINPROGRESS:  
                break; 

            /*
             * Recover from intterupted system calls and that lot 
             * In these cases return with whatever data we wrote   
             */
            case EINTR: 
            case EBUSY: 
            case EDEADLK: 
                break; 

            /* Any other error */ 
            default: 
                done = ITS_TRUE;
                rc = 0;  
                break; 
            } 
            break; 

            /* EOF (peer has closed connection) */ 
            case 0:
            done = ITS_TRUE;
            rc=0;  
            break;

            /* We have write some amount of data */ 
            default:
            totalwrite+=br;   
            if (totalwrite >= size) 
            {    
                done = ITS_TRUE;
            } 
            break; 
        }
        
        /* Set the return code (may be reset in timeout below) */ 
        rc = totalwrite;
 
        /* Check to see if we have timed out if we are not already done */ 
        if (!done) 
        {    
            time(&now_time); 
            if (now_time > start_time + maxtime) 
            {    
                done = ITS_TRUE;
                rc = 0; 
            }
        }
    } 

    /* Set this socket back to blocking */
    ioctl_val = 0; 
    if (ioctl(info->socket, FIONBIO, &ioctl_val) < 0)
    {
        /* what to do here */
    }

    /* fini */
    return rc; 
} 

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_ClientTimeoutConnect.
 *
 *  Purpose:
 *      This is a Connect  write with timeout. If it does not connect in
 *      specified amount of time it will return.
 *
 *  Input Parameters:
 *      int fd                  file descriptor of socket to write from
 *      int maxtime             time in milli seconds
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS            Successful connection.
 *      ITS_ECONNECTFAIL       On Connection Failure.
 ****************************************************************************/
ITSDLLAPI int
SOCK_ClientTimeoutConnect(ITS_SocketInfo* info, int maxtime)
{
    fd_set fdset;
    struct timeval tv; 
    int ret  = !ITS_SUCCESS;
    int flag = 1;                  /* For use in disabling nagle */
    int ioctl_val = 1;             /* value for ioctl() call */
    struct protoent *ent;          /* For use in disabling nagle */
    socklen_t len;

    /* Set this socket to nonblocking */
    ioctl_val = 1;
    if (ioctl(info->socket, FIONBIO, &ioctl_val) < 0)
    {
        return ITS_ECONNECTFAIL;
    }

    /*
     * Attempt connection
     */
    ret = connect(info->socket, info->addr, info->asize); 
    if (ret < 0) 
    {
        if (errno == EINPROGRESS)
        {
            do
            {
                tv.tv_sec = maxtime / 1000; 
                tv.tv_usec = (maxtime % 1000) * 1000; 
                if (tv.tv_usec > 1000000)
                {
                    tv.tv_usec -= 1000000;
                    tv.tv_sec++;
                }

                FD_ZERO(&fdset); 
                FD_SET(info->socket, &fdset); 

                ret = select(info->socket+1, NULL, &fdset, NULL, &tv); 
                if (ret < 0 && errno != EINTR) 
                {
                    /* Error connecting */
                    ret = ITS_ECONNECTFAIL;
                    break;
                }
                else if (ret > 0) 
                {
                    /* Socket selected for write */
                    len = sizeof(int); 
                    if (getsockopt(info->socket, SOL_SOCKET, SO_ERROR, 
                                  (void*)(&flag), &len) < 0)
                    { 
                        ret = ITS_ECONNECTFAIL;
                        break; 
                    } 

                    /* Check the value returned. */
                    if (flag) 
                    { 
                        ret = ITS_ECONNECTFAIL; 
                        break;
                    } 
                    /*
                     * Disable TCP NAGLE algorighm. 
                     * (don't delay short messages waiting for window ack)
                     */
                    if (info->af == AF_INET && 
                       (ent = getprotobyname("tcp")) != NULL)
                    {
                        setsockopt(info->socket, ent->p_proto,
                           TCP_NODELAY, (char *)&flag, sizeof(flag));
                    }
                    ret = ITS_SUCCESS;
                    break;
                }
                else
                {
                    /* "Timeout in select() - Cancelling */
                    ret = ITS_ECONNECTFAIL;
                    break;
                }

            } while(1);
        }
        else
        {
            ret = ITS_ECONNECTFAIL;
        }
    }

    /* Set this socket back to blocking */
    ioctl_val = 0;
    if (ioctl(info->socket, FIONBIO, &ioctl_val) < 0)
    {
        /* what to do here */
    }

    /* fini */
    return ret;
}


/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_Close.
 *
 *  Purpose:
 *      Close the socket, delete any stream files that may be littering 
 *      the file system and remove the socket data from the tracking structure
 *
 *  Input Parameters:
 *      int sock                                socket handle
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      void
 ****************************************************************************/
ITSDLLAPI void
SOCK_Close(ITS_SocketInfo* info)
{
    struct sockaddr_un *aun;

    if (!info)
    {
        return;
    }

    if (info->socket >= 0)
    {
        /* Close the socket handle */ 
        close(info->socket);

        /* Remove the stream file */
        if (info->af == AF_UNIX &&
            info->type != SPROT_TYPE_LOCAL_CLIENT) 
        {
            aun = (struct sockaddr_un *)info->addr;
            unlink(aun->sun_path);
        }

        /* Remove from our dataspace */ 
        free(info->addr);
    }

    free(info);
 
    return; 
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_DebugDump.  
 *
 *  Purpose:
 *      Dump out all the accounting info we have been maintaining on a 
 *      given socket
 *
 *  Input Parameters:
 *      int sock                        file descriptor of socket
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
ITSDLLAPI void
SOCK_DebugDump(ITS_SocketInfo* info) 
{
#if 0
    struct hostent *hostinfo;
    struct in_addr in;

    TRACE_DEBUG(("sock_debug_dump: SOCKET DEBUG INFO:\n"));
    TRACE_DEBUG(("sock_debug_dump: fd: %d  address family: %s\n",
                 info->socket,
                 info->af == AF_INET ? "AF_INET" : "AF_UNIX"));

    /* If this is a socket... */ 
    if (info->af == AF_INET) 
    {
        /*
         * Print address and hostname if available 
         * Print out the port in any case          
         */
        in = ((struct sockaddr_in *)info->addr)->sin_addr;
        if ((hostinfo = gethostbyaddr((char *)&in, sizeof(struct in_addr),
                                      AF_INET)) != NULL)
        {    
            TRACE_DEBUG(( "address: %-16.16s  hostname: %s\n",
                    inet_ntoa(in), hostinfo->h_name));
        } 
        else
        {    
            TRACE_DEBUG (("address: %-16.16s  hostname: unresolved\n",
                    inet_ntoa(in)));
        }

        TRACE_DEBUG (("port: %d\n",
             ntohs(((struct sockaddr_in *)info->addr)->sin_port)));
    }

    /* This is not a socket, it must be a stream */ 
    else 
    {    
        TRACE_DEBUG(("path: %s\n",
                    ((struct sockaddr_un *)info->addr)->sun_path));
    }

    /* fini */ 
    return; 
#endif
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_GetPeerName
 *
 *  Purpose:
 *      Determine the address information for a connected peer.
 *
 *  Input Parameters:
 *      in - pointer to ITS_SocketInfo
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      out - pointer to ITS_SocketInfo
 *
 *  Return Value:
 *      ITS_SUCCESS - address of connected peer is in "out".
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SOCK_GetPeerName(ITS_SocketInfo* in, ITS_SocketInfo* out)
{
    memset(out, 0, sizeof(ITS_SocketInfo));
    out->socket = in->socket;
    out->type = in->type;

    if ((out->addr = calloc(1, sizeof(struct sockaddr))) == NULL)
    {
        return (ITS_ENOMEM);
    }

    out->asize = sizeof(struct sockaddr);

    if (getpeername(in->socket, out->addr, (socklen_t *)&out->asize) != 0)
    {
        ITS_TRACE_ERROR(("getpeername failed...errno = %d\n\n", errno));
        free(out->addr);

        return (ITS_EBADSOCKET);
    }

    out->af = in->af;

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_AddrsAreEqual
 *
 *  Purpose:
 *      Determine if the address information for two connections
 *
 *  Input Parameters:
 *      a1, a2 - pointers to ITS_SocketInfo
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_FALSE - addrs are not equal
 *      ITS_TRUE - addrs are equal
 *
 *  Notes:
 *      The actual file descriptors for the sockets are not included
 *      in the equality check.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
SOCK_AddrsAreEqual(ITS_SocketInfo* a1, ITS_SocketInfo* a2)
{
    struct sockaddr_in *tmp = (struct sockaddr_in *)a1->addr;

    if (a1->type != a2->type ||
        a1->af != a2->af)
    {
        return (ITS_FALSE);
    }

    switch (tmp->sin_family)
    {
    default:
    case AF_INET:
        {
            struct sockaddr_in *a, *b;

            a = (struct sockaddr_in *)a1->addr;
            b = (struct sockaddr_in *)a2->addr;

            if (a->sin_port == b->sin_port &&
                a->sin_addr.s_addr == b->sin_addr.s_addr)
            {
                return (ITS_TRUE);
            }
        }
        break;

    case AF_UNIX:
        {
            struct sockaddr_un *a, *b;

            a = (struct sockaddr_un *)a1->addr;
            b = (struct sockaddr_un *)a2->addr;

            if (a1->asize != a2->asize)
            {
                return (ITS_FALSE);
            }

            if (strcmp(a->sun_path, b->sun_path) == 0)
            {
                return (ITS_TRUE);
            }
        }
        break;
    }

    return (ITS_FALSE);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_NToHL
 *
 *  Purpose:
 *      Convert an unsigned long from network order to host order
 *
 *  Input Parameters:
 *      ulong - the value to convert
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The converted value
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_ULONG
SOCK_NToHL(ITS_ULONG ulong)
{
    return ntohl(ulong);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_NToHL
 *
 *  Purpose:
 *      Convert an unsigned short from network order to host order
 *
 *  Input Parameters:
 *      ushort - the value to convert
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The converted value
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_USHORT
SOCK_NToHS(ITS_USHORT ushort)
{
    return ntohs(ushort);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_NToHL
 *
 *  Purpose:
 *      Convert an unsigned long from host order to network order
 *
 *  Input Parameters:
 *      ulong - the value to convert
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The converted value
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_ULONG
SOCK_HToNL(ITS_ULONG ulong)
{
    return htonl(ulong);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_NToHL
 *
 *  Purpose:
 *      Convert an unsigned short from host order to network order
 *
 *  Input Parameters:
 *      ushort - the value to convert
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The converted value
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_USHORT
SOCK_HToNS(ITS_USHORT ushort)
{
    return htons(ushort);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_GetLocalAddrs()
 *
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      number of local addresses.  -1 on failure.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SOCK_Poll(ITS_SockPollInfo *socks, int nsocks, int usecs)
{
    int i;
    fd_set reads, writes;
    int ret, max;

    if (nsocks < 0 ||
        (usecs == SOCK_POLL_WAIT_FOREVER && nsocks == 0))
    {
        return (ITS_EINVALIDARGS);
    }

    FD_ZERO(&reads);
    FD_ZERO(&writes);

    max = 0;
    for (i = 0; i < nsocks; i++)
    {
        socks[i].wasSet = 0;

        if ((int)socks[i].sinfo->socket > max)
        {
            max = socks[i].sinfo->socket;
        }

        if (socks[i].lookFor & (SOCK_POLL_READ|SOCK_POLL_READ_OOB))
        {
            FD_SET(socks[i].sinfo->socket, &reads);
        }

        if (socks[i].lookFor & (SOCK_POLL_WRITE|SOCK_POLL_WRITE_OOB))
        {
            FD_SET(socks[i].sinfo->socket, &writes);
        }
    }

    if (max > 0)
    {
        max++;
    }

    if (usecs == SOCK_POLL_WAIT_FOREVER)
    {
        ret = select(max, &reads, &writes, NULL, NULL);
    }
    else
    {
        struct timeval tv;

        tv.tv_sec = usecs / USEC_PER_SEC;
        tv.tv_usec = usecs % USEC_PER_SEC;

        ret = select(max, &reads, &writes, NULL, &tv);
    }

    if (ret < 0)
    {
        return (ITS_EBADSOCKET);
    }

    if (ret == 0)
    {
        return (ITS_SUCCESS);
    }

    for (i = 0; i < nsocks; i++)
    {
        if (FD_ISSET(socks[i].sinfo->socket, &reads))
        {
            socks[i].wasSet |= SOCK_POLL_READ;
        }
        if (FD_ISSET(socks[i].sinfo->socket, &writes))
        {
            socks[i].wasSet |= SOCK_POLL_WRITE;
        }
    }

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_GetLocalAddrs()
 *
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      number of local addresses.  -1 on failure.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SOCK_GetLocalAddrs(SOCK_AddrStore **addrs, SOCK_AddrStore **masks,
                   SOCK_AddrStore **bcasts)
{
    struct ifconf cf;
    struct ifreq *ifrequest;
    u_int intf_flags;
    int numints, i, numAddrs, tsock, numnets;
    struct sockaddr_in *tmp;

    *addrs = *masks = NULL;

    cf.ifc_buf = malloc(8192);
    cf.ifc_len = 8192;
    if (cf.ifc_buf == NULL)
    {
        return (-1);
    }

    if ((tsock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        free(cf.ifc_buf);

        return (-1);
    }

    if (ioctl(tsock, SIOCGIFCONF, (char *)&cf) == -1)
    {
        close(tsock);
        free(cf.ifc_buf);

        return (-1);
    }

    numints = cf.ifc_len / sizeof(struct ifreq);

    numAddrs = numints + 1;
    ifrequest = cf.ifc_req;

    if ((*addrs = (SOCK_AddrStore *)calloc(numAddrs,
                                           sizeof(SOCK_AddrStore))) == NULL)
    {
        close(tsock);
        free(cf.ifc_buf);

        return (-1);
    }
    
    if ((*masks = (SOCK_AddrStore *)calloc(numAddrs,
                                           sizeof(SOCK_AddrStore))) == NULL)
    {
        free(*addrs);
        close(tsock);
        free(cf.ifc_buf);

        return (-1);
    }
    
    if ((*bcasts = (SOCK_AddrStore *)calloc(numAddrs,
                                            sizeof(SOCK_AddrStore))) == NULL)
    {
        free(*addrs);
        close(tsock);
        free(cf.ifc_buf);

        return (-1);
    }

    numnets = 0;

    for (i = 0; i < numints; i++, ifrequest++)
    {
        /* look at each network */
        if (ioctl(tsock, SIOCGIFFLAGS, (char *)ifrequest) == -1)
        {
            /* cant get the flags? */
            continue;
        }

        intf_flags = ifrequest->ifr_flags;

#ifdef SKIP_LOOPBACK
        if (ifrequest->ifr_flags & IFF_LOOPBACK)
        {
            continue;
        }
#endif

        if (ioctl(tsock, SIOCGIFADDR, (char *)ifrequest) == -1)
        {
            /* now get the address */
            continue;
        }

        if (ifrequest->ifr_addr.sa_family != AF_INET)
        {
            /* It is not a IP address skip it */
            continue;
        }

        if (((struct sockaddr_in *)(&ifrequest->ifr_addr))->sin_addr.s_addr == 0)
        {
            /* no address is set */
            continue;
        }

        /* Test to see if duplicate */
        /* some O/S's will give it to you twice */
        if (numnets)
        {
            int dup, j;
            dup = 0;

            for (j = 0; j < numnets; j++)
            {
                if (((struct sockaddr_in *)(&ifrequest->ifr_addr))->sin_addr.s_addr == 
                    ((struct sockaddr_in *)&addrs[j])->sin_addr.s_addr)
                {
                    dup = 1;

                    break;
                }
            }

            if (dup)
            {
                continue;
            }
        }

        tmp = (struct sockaddr_in *)&((*addrs)[numnets]);

        memcpy(tmp, &ifrequest->ifr_addr, sizeof(struct sockaddr_in));
        tmp->sin_port = 0;
        memset(tmp->sin_zero, 0, sizeof(tmp->sin_zero));
        tmp->sin_family = AF_INET;

        /* now get the netmask */
        if (ioctl(tsock, SIOCGIFNETMASK, (char *)ifrequest) == -1)
        {
            numnets++;

            continue;
        }

        tmp = (struct sockaddr_in *)&((*masks)[numnets]);

        memcpy(tmp, &ifrequest->ifr_addr, sizeof(struct sockaddr_in));

        tmp->sin_port = 0;
        memset(tmp->sin_zero, 0, sizeof(tmp->sin_zero));
        tmp->sin_family = AF_INET;

        if (ioctl(tsock, SIOCGIFBRDADDR, (char *)ifrequest) == -1)
        {
            numnets++;

            continue;
        }

        tmp = (struct sockaddr_in *)&((*bcasts)[numnets]);

        memcpy(tmp, &ifrequest->ifr_addr, sizeof(struct sockaddr_in));

        tmp->sin_port = 0;
        memset(tmp->sin_zero, 0, sizeof(tmp->sin_zero));
        tmp->sin_family = AF_INET;

        numnets++;
    }

    free(cf.ifc_buf);

    if (!numnets)
    {
        if (*addrs)
        {
            free(*addrs);
            *addrs = NULL;
        }

        if (*masks)
        {
            free(*masks);
            *masks = NULL;
        }

        if (*bcasts)
        {
            free(*bcasts);
            *bcasts = NULL;
        }
    }

    close(tsock);

    return (numnets);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_GetIPv4AddrAndPort() extracts the IP addr and port from
 *      an opaque type.
 *
 *  Purpose:
 *
 *  Input Parameters:
 *      addrStruct - the address to convert
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      addr - the IP address
 *      port - the port
 *
 *  Return Value:
 *      number of local addresses.  -1 on failure.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SOCK_GetIPv4AddrAndPort(SOCK_AddrStore *addrStruct,
                        SOCK_IPv4Addr *addr,
                        ITS_USHORT *port)
{
    struct sockaddr_in *who = (struct sockaddr_in *)addrStruct;

    if (who->sin_family != AF_INET)
    {
        return (ITS_EINVALIDARGS);
    }

    *addr = SOCK_NToHL(who->sin_addr.s_addr);
    *port = SOCK_NToHS(who->sin_port);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *
 *  Purpose:
 *      Convert from a name in dotted quad to an address.
 *
 *  Input Parameters:
 *      name - the name to convert.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      addr - the IP address
 *
 *  Return Value:
 *      number of local addresses.  -1 on failure.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SOCK_IPv4NameToAddr(const char *name, SOCK_IPv4Addr *addr)
{
    char *tmp, *tmp2;
    ITS_ULONG conv;

    /* first */
    if ((tmp = strchr(name, '.')) == NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    *tmp = 0;
    tmp++;
    conv = atoi(name) << 24;

    /* second */
    tmp2 = tmp;
    if ((tmp = strchr(tmp, '.')) == NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    *tmp = 0;
    tmp++;
    conv |= atoi(tmp2) << 16;

    /* third */
    tmp2 = tmp;
    if ((tmp = strchr(tmp, '.')) == NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    *tmp = 0;
    tmp++;
    conv |= atoi(tmp2) << 8;

    /* last */
    conv |= atoi(tmp);

    *addr = SOCK_HToNL(conv);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *
 *  Purpose:
 *      Convert from an address to the dotted quad notation
 *
 *  Input Parameters:
 *      addr - the IP address
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      name - the string value of the name
 *
 *  Return Value:
 *      number of local addresses.  -1 on failure.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SOCK_IPv4AddrToName(char *name, SOCK_IPv4Addr addr)
{
    char buf[20];

    memset(buf, 0, 20 * sizeof(char));

    sprintf(buf, "%u.%u.%u.%u", (addr >> 24),
                                (addr >> 16) & 0xFFU,
                                (addr >> 8)  & 0xFFU,
                                 addr & 0xFFU);

    strcat(name, buf);

    return (ITS_SUCCESS);
}


/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_DscpMarking.
 *
 *  Purpose:
 *      This will be used to set DSCP value to setsockopt 
 *
 *  Input Parameters:
 *      ITS_SocketInfo*                   Socket Info
 *      int                               dscp parameter to be set in setsockopt
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success
 *      !ITS_SUCCESS - Error
 *
 ****************************************************************************/
ITSDLLAPI void
SOCK_SetDscpMarking(ITS_SocketInfo *sockInfo, int dscp)
{
    int                 sockopt;

    ITS_TRACE_DEBUG(("SOCK_SetDscpMarking"));
    if (sockInfo == NULL)
    {
        //return (ITS_ECONNECTFAIL);
        return;
    }
    ITS_TRACE_DEBUG(("SOCK_SetDscpMarking fd %d val %d",sockInfo->socket, dscp));

    /* in.h (7posix) - Internet address family for setting level IPPROTO_IP.
     * ip(7) - Linux man page for setting option_name IP_TOS.
     */
    sockopt = setsockopt(sockInfo->socket,IPPROTO_IP,IP_TOS,&dscp,
                                         sizeof(dscp));
    if( sockopt == -1 )
    {
        ITS_TRACE_CRITICAL((" Failed to set DSCP option for IDS-IDC Intf "));
        //return (!ITS_SUCCESS);
        return;
    }
    //return (ITS_SUCCESS);
    return;
}

int SOCK_GetIpAddress(ITS_SocketInfo *info, char** strBuff,
                                         int len, ITS_BOOLEAN isIpV4)
{
    if (isIpV4 == ITS_TRUE)
    {
        struct in_addr in = ((struct sockaddr_in*)info->addr)->sin_addr;
        strcpy(*strBuff, inet_ntoa(in));
        //inet_ntop(AF_INET, &in, *strBuff, len);
        return ITS_SUCCESS;
    }
#ifdef USE_IPV6
    else
    {
        struct in6_addr in6 = ((struct sockaddr_in6*)info->addr)->sin6_addr;
        char straddr[64];
        inet_ntop(AF_INET6, &in6, (char*)*strBuff, len);
        return ITS_SUCCESS;
    }
#endif
    return ITS_EINVALIDARGS;
}

/*
 * the class record
 */
ITSDLLAPI ITS_ClassRec itsSOCKET_ClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,              /* CORE is superclass */
        0,                              /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        SOCKET_CLASS_NAME,              /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ITS_INST_NO_CONST,              /* instance create */
        ITS_INST_NO_DEST,               /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    }
};

ITSDLLAPI ITS_Class itsSOCKET_Class = (ITS_Class)&itsSOCKET_ClassRec;
