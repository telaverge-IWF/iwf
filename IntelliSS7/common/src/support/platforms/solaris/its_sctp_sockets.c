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
 * LOG: Revision 1.1.4.1.20.1  2014/09/16 09:34:54  jsarvesh
 * LOG: Changes done for removing warnings
 * LOG:
 * LOG: Revision 1.1.4.1.16.1  2014/09/15 07:20:42  jsarvesh
 * LOG: Changes done for removing Warnings
 * LOG:
 * LOG: Revision 1.1.4.1  2011/04/13 07:39:59  nvijikumar
 * LOG: Diameter specific changes
 * LOG:
 * LOG: Revision 1.6  2010/11/09 06:46:47  vkumara
 * LOG: Broken Pipe issue over IPV6.
 * LOG:
 * LOG: Revision 1.5  2010/11/04 07:23:15  vkumara
 * LOG: Bind is not required if dscp value is 0.
 * LOG: Port number is not required while binding.
 * LOG:
 * LOG: Revision 1.4  2010/11/03 12:48:03  vkumara
 * LOG: DSCP with IPV6 Support
 * LOG:
 * LOG: Revision 1.3  2010/10/11 08:01:55  mdinesh
 * LOG: Solaris IPV6 Support
 * LOG:
 * LOG: Revision 1.2  2010/09/20 05:17:41  mdinesh
 * LOG: Verify Socket Before write (fix for core dump - Vasant)
 * LOG:
 * LOG: Revision 1.1.1.1  2008/08/07 13:50:17  vnarang
 * LOG: Light wieght IntelliSS7 ( AcceleroCore)
 * LOG:
 * LOG: Revision 1.1.2.2  2006/10/06 06:03:25  nanaparthi
 * LOG: Support for SCTP MultiHoming Server.
 * LOG:
 * LOG: Revision 1.1.2.1  2006/09/26 06:48:22  nanaparthi
 * LOG: Baseline SKSCTP support for Solaris.
 * LOG:
 *
 * ID: $Id: its_sctp_sockets.c,v 1.1.4.1.20.1 2014/09/16 09:34:54 jsarvesh Exp $
 ****************************************************************************/
#ident "$Id: its_sctp_sockets.c,v 1.1.4.1.20.1 2014/09/16 09:34:54 jsarvesh Exp $"

#include <netinet/in.h>

#include <its.h>
#include <its_sockets.h>
#include <its_sksctp_sockets.h>
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
#include <sys/sockio.h>
#include <stropts.h>
#include <poll.h>
#include <sys/ioctl.h>
#include <sys/filio.h>
#include <sys/time.h>

#include <net/if.h>
#include <netinet/sctp.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <arpa/nameser.h>

#include <its_timers.h>

#ident "$Id: its_sctp_sockets.c,v 1.1.4.1.20.1 2014/09/16 09:34:54 jsarvesh Exp $"

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
SKSCTP_SOCK_ClientOpen(ITS_SocketInfo **sockInfo, ITS_SOCK_DOMAIN domain,
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

    /* setup if INET domain */
    if (domain == INET_DOMAIN)
    {
        /* get the address */
        if (SOCK_CreateAddr(domain, host_or_path, port,
                        &ret->addr, &ret->asize) != ITS_SUCCESS)
        {
            free(ret);
            return (ITS_EBADHOST);
        }
        struct linger      linger;           /* set linger structure */

        /* Create a socket */
        if ((ret->socket = socket(AF_INET, SOCK_STREAM,IPPROTO_SCTP)) < 0)  /* naresh */
        {
            free(ret->addr);
            free(ret);

            return (ITS_ENOSOCKET);
        }

        /* Set linger on, to 0 time */
        linger.l_onoff = 1;
        linger.l_linger = 0;
        setsockopt(ret->socket, SOL_SOCKET, SO_LINGER,
                       (char *)&linger, sizeof(struct linger));  /* naresh */

        /* Save off addr info in our own dataspace */
        ret->type = SPROT_TYPE_SCTP_CLIENT;
        ret->af = AF_INET;

        *sockInfo = ret;
    }
#ifdef USE_IPV6
    else if (domain == INET6_DOMAIN)
    {
        /* code needs to be changed in case of multihoming */
        if (SOCK_CreateIpv6Addr(domain, host_or_path, port,
                    &ret->addr, &ret->asize) != ITS_SUCCESS)
        {
            free(ret);

            return (ITS_EBADHOST);
        }

        /* Create a socket */
        if ((ret->socket = socket(AF_INET6, SOCK_STREAM,IPPROTO_SCTP)) < 0)
        {
            free(ret->addr);
            free(ret);
            return (ITS_ENOSOCKET);
        }

        /* Save off addr info in our own dataspace */
        ret->type = SPROT_TYPE_SCTP_CLIENT;
        ret->af = AF_INET6;
        *sockInfo = ret;

        struct linger      linger;           /* set linger structure */

        /* Set linger on, to 0 time */
        linger.l_onoff = 1;
        linger.l_linger = 0;
        setsockopt(ret->socket, SOL_SOCKET, SO_LINGER,
                           (char *)&linger, sizeof(struct linger));

        ret->max_out_stream = 1;

        ret->stream_no = 1;

        /* Set re-use addr socket option */
        setsockopt(ret->socket, SOL_SOCKET, SO_REUSEADDR,
                   (void *)&dummy, sizeof(int));

         /* fini */
        return (ITS_SUCCESS);

    }//End IPV6
#endif

    /* Setup for UNIX domain */
/*    else if (domain == UNIX_DOMAIN)
    {
        /* Create a socket */
/*        if ((ret->socket = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
        {
            free(ret->addr);
            free(ret);

            return (ITS_EBADSOCKET);
        }

        /* Save this in our own dataspace */
/*        ret->type = SPROT_TYPE_LOCAL_CLIENT;
        ret->af = AF_UNIX;

        *sockInfo = ret;
    }*/
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
 *      SOCK_ServerOpen.
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
SKSCTP_SOCK_ServerOpen(ITS_SocketInfo **sockInfo, ITS_SOCK_DOMAIN domain,
                const char *host_or_path, int port, int dscp)
{
    int    dummy = 1;       /* for socket option */
    ITS_SocketInfo *ret;

    /* Make sure the address is good */
    ITS_C_ASSERT(sockInfo != NULL);

    /* Set up our addr info accounting */
    if ((ret = (ITS_SocketInfo *)calloc(1, sizeof(ITS_SocketInfo))) == NULL)  /* naresh */
    {
        return (ITS_ENOMEM);
    }

    /* setup if INET domain */
    if (domain == INET_DOMAIN)
    {
        if (SOCK_CreateAddr(domain, host_or_path, port,
                        &ret->addr, &ret->asize) != ITS_SUCCESS)
        {
            free(ret);
            return (ITS_EBADHOST);
        }

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
#ifdef USE_IPV6
    else if (domain == INET6_DOMAIN)
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
        if ((ret->socket = socket(AF_INET6, SOCK_STREAM, IPPROTO_SCTP)) < 0)
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
        ret->af = AF_INET6;
        *sockInfo = ret;

        /* Set reuseaddr socket option */
        setsockopt(ret->socket, SOL_SOCKET, SO_REUSEADDR,
               (void *)&dummy, sizeof(int));

        /* bind to the port specified */
        struct sockaddr_in6 addr6;
        memset(&addr6, 0, sizeof(addr6));
        addr6.sin6_family = AF_INET6;
        addr6.sin6_port = htons(port);
        addr6.sin6_flowinfo = htonl(dscp << 20);

        int ifid = 0;
        //ifid = if_nametoindex("bge0");
        addr6.sin6_scope_id = ifid;
        
        if ( inet_pton(AF_INET6, "0::0", &addr6.sin6_addr) == 0 )
        {
            ret->addr;
            free(ret);
            return (ITS_EBADHOST);
        }
 
        /* bind to the port specified */
        if (bind(ret->socket, (struct sockaddr *)&addr6, ret->asize) < 0)
        {
            free(ret->addr);
            close(ret->socket);
            free(ret);
            return (ITS_EBINDFAIL);
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

        ret->stream_no = 1;
        ret->max_out_stream = 1;

        /* fini */
        return (ITS_SUCCESS);
    }
#endif

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
/*    if (domain == UNIX_DOMAIN)
    {
        if (chmod(host_or_path, DEFAULT_MODE_MASK) < 0)
        {
            unlink(host_or_path);

            free(ret->addr);
            close(ret->socket);
            free(ret);

            return (ITS_EINVALIDARGS);
        }
    } */

    /* Set up a listen queue */
    if (listen(ret->socket, SOMAXCONN) < 0)
    {
        unlink(host_or_path);

        free(ret->addr);
        close(ret->socket);
        free(ret);

        return (ITS_ELISTENFAIL);
    }

    /* fini */
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SKSCTP_SOCK_MultiHomeServerOpen.
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
SKSCTP_SOCK_MultiHomeServerOpen(ITS_SocketInfo **sockInfo, ITS_SOCK_DOMAIN domain,
                const char *host_or_path[], int port,int no_ips)
{
    int    dummy = 1;       /* for socket option */
    ITS_SocketInfo *ret;
   
    struct sockaddr_in *bindbuf;
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

        if (SOCK_CreateIpv6Addr(domain, *host_or_path, port,
                            &ret->addr, &ret->asize) != ITS_SUCCESS)
        {
            free(ret);

            return (ITS_EBADHOST);
        }

        /* Create a socket */
        if ((ret->socket = socket(AF_INET6, SOCK_STREAM, IPPROTO_SCTP)) < 0)
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
        ret->af = AF_INET6;
        *sockInfo = ret;

        /* Set reuseaddr socket option */
        setsockopt(ret->socket, SOL_SOCKET, SO_REUSEADDR,
               (void *)&dummy, sizeof(int));
                
        /* bind to the port specified */ 

        struct sockaddr_in6 addr6;
        memset(&addr6, 0, sizeof(addr6));  
        addr6.sin6_family = AF_INET6;
        addr6.sin6_port = htons(port);

        int ifid = 0;
        //ifid = if_nametoindex("bnx0");

        addr6.sin6_scope_id = ifid;
        addr6.sin6_flowinfo = 0;

        if ( inet_pton(AF_INET6, "0::0", &addr6.sin6_addr) == 0 )
        {
            free(ret->addr);
            free(ret);
            return (ITS_EBADHOST);
        }

        /* bind to the port specified */
        //if (sctp_bindx(ret->socket, (struct sockaddr*)&addr6, 1, SCTP_BINDX_ADD_ADDR) != 0 )
        if (bind(ret->socket, (struct sockaddr *)&addr6, ret->asize) < 0)
        {
            free(ret->addr);
            close(ret->socket);
            free(ret);
            return (ITS_EBINDFAIL);
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

        ret->stream_no = 1;
        ret->max_out_stream = 1;

        /* fini */
        return (ITS_SUCCESS);
    }
#endif

    if ((bindbuf = (struct sockaddr_in *)calloc(no_ips, 
                                 sizeof(struct sockaddr_in))) == NULL)
    {
        free(ret->addr);
        free(ret);
       return (ITS_ENOMEM);
    }

    for(i=0;i<no_ips;i++)
    {
        if (SOCK_CreateAddr(domain, host_or_path[i], port,
                                &ret->addr, &ret->asize) != ITS_SUCCESS)
        {
                free(ret);
                free(bindbuf);
                return (ITS_EBADHOST);
        }
              bindbuf[i]= *(struct sockaddr_in *)ret->addr;
               
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

        return (ITS_EBINDFAIL);
    }

    if (sctp_bindx(ret->socket, bindbuf, (no_ips - 1) , SCTP_BINDX_ADD_ADDR) < 0)/*naresh*/
    {   
         free(bindbuf);
       /* free(ret->addr);*/
        close(ret->socket);
        free(ret);
        return (ITS_EBINDFAIL);
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

    /* fini */
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SKSCTP_SOCK_ClientConnect.
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
SKSCTP_SOCK_ClientConnect(ITS_SocketInfo* info)
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
    if (info->af == AF_INET && (ent = getprotobyname("sctp")) != NULL)
    {
        setsockopt(info->socket, ent->p_proto,
                   SCTP_NODELAY, (char *)&flag, sizeof(flag));  /* naresh */
    }

    /*
     * fini
     */
    return (ITS_SUCCESS);
}
/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SKSCTP_SOCK_Ipv6ClientConnect.
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
SKSCTP_SOCK_Ipv6ClientConnect(ITS_SocketInfo* info, int dscp)
{
#ifdef USE_IPV6
    struct protoent     *ent;                /* For use in disabling nagle */
    int flag = 1;                            /* For use in disabling nagle */

    if (!info)
    {
        return (ITS_ECONNECTFAIL);
    }

    /* 
     * This bind() before connect() is to support 
     * DSCP IPV6 by setting flow label flag to parsed 
     * dscp value
     */
    if (dscp != 0)  
    {
        struct sockaddr_in6 addr6;
     	memset(&addr6, 0, sizeof(addr6));
     	addr6.sin6_family = AF_INET6;
     	addr6.sin6_flowinfo = htonl(dscp << 20);

     	int ifid = 0;
     	//ifid = if_nametoindex("bge0");
     	addr6.sin6_scope_id = ifid;

     	if ( inet_pton(AF_INET6, "0::0", &addr6.sin6_addr) == 0 )
     	{
            return (ITS_EBADHOST);
     	}

     	/* bind to the port specified */
     	if (bind(info->socket, (struct sockaddr *)&addr6, info->asize) < 0)
     	{
            free(info->addr);
            close(info->socket);
            free(info);
            return (ITS_EBINDFAIL);
        }
    }

    /*
     * Attempt connection
     */

    //setsockopt(info->socket, SOL_SOCKET, SO_BINDTODEVICE, "eth0\0", 5);

    /* code needs change for SCTP multi homing */
    if(connect(info->socket, info->addr, info->asize) < 0)
    {
       return (ITS_ECONNECTFAIL);
    }

    /*
     * SCTP MultiHoming 
     */ 
#if 0
    /* this code needs to be handled in case of multihoming */
    else if (sctp_connectx(info->socket,
                          (struct sockaddr_in6 *)info->multi_addrs, 
                          info->no_ips) < 0)                           
    {
        return (ITS_ECONNECTFAIL);
    }
#endif
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
 *      SKSCTP_SOCK_ServerAccept.
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
SKSCTP_SOCK_ServerAccept(ITS_SocketInfo* info, ITS_SocketInfo **newInfo)
{
    int    flag = 1;          /* for setsockopt() call */
    struct protoent    *ent;  /* protocol entry */
    struct sctp_event_subscribe event;   /* naresh */
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
    tmp->socket = accept(info->socket, tmp->addr, &tmp->asize);

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

	 event.sctp_data_io_event = 1;
	 event.sctp_association_event = 1;
	 event.sctp_address_event = 1;
	 event.sctp_send_failure_event = 1;
	 event.sctp_peer_error_event = 1;
	 event.sctp_shutdown_event = 1;
	 event.sctp_partial_delivery_event = 1;

	     if(setsockopt(tmp->socket, IPPROTO_SCTP,SCTP_EVENTS, &event,
	                   sizeof(event)) != 0) {
	                   perror("setevent failed");
	                   exit(1);
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
    if (tmp->af == AF_INET && (ent = getprotobyname("sctp")) != NULL)
    {
        setsockopt(tmp->socket, ent->p_proto,
                   SCTP_NODELAY, (char *)&flag, sizeof(flag));  /* naresh */
    }

    *newInfo = tmp;

    /* fini */
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SKSCTP_SOCK_Read.
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
SKSCTP_SOCK_Read(ITS_SocketInfo* info, char *buf, int nbytes)
{
    int     nleft;                    /* Amount of data left to read */
    int     nread;                    /* Amount of data we have read */
    int     done = ITS_FALSE;             /* Loop terminator for EOF      */

    struct sctp_sndrcvinfo sndrcvinfo;  /* naresh */
    int flags;

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
 *      SKSCTP_SOCK_Write.
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
SKSCTP_SOCK_Write(ITS_SocketInfo* info, char *buf, int nbytes)
{
    int    nleft;
    int    nwritten;

    /* Set up how much we need to write */
    nleft = nbytes;

    if (!info)
    {
        return (0);
    }

#ifdef USE_IPV6
    struct sockaddr_in6 addr6;
    socklen_t addr6Sz = sizeof(struct sockaddr_in6);
    if (getpeername(info->socket, &addr6, &addr6Sz) != 0)
    {
        //printf("getpeername failed...errno = %d\n\n", errno);
        return (ITS_EBADSOCKET);
    }
#endif

    struct sockaddr addr;
    socklen_t addrSz = sizeof(struct sockaddr);
    if (getpeername(info->socket, &addr, &addrSz) != 0)
    {
        //printf("getpeername failed...errno = %d\n\n", errno);
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

