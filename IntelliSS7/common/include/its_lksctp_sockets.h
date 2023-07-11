/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 2006 IntelliNet Technologies, Inc.                 *
 *                            All Rights Reserved.                          *
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
 *  ID: $Id: its_lksctp_sockets.h,v 1.1.4.1.8.1 2013/11/05 09:49:37 jvikram Exp $
 *
 *  LOG: $Log: its_lksctp_sockets.h,v $
 *  LOG: Revision 1.1.4.1.8.1  2013/11/05 09:49:37  jvikram
 *  LOG: Merge from TNSI
 *  LOG:
 *  LOG: Revision 1.3.64.1  2013/06/25 10:00:04  jvikram
 *  LOG: Merged changes from DRE Branch.
 *  LOG:
 *  LOG: Revision 1.3  2009/03/19 11:05:23  chandrashekharbs
 *  LOG: Support for IPV6 SCTP
 *  LOG:
 *  LOG: Revision 1.2  2009/02/02 06:58:24  rajeshak
 *  LOG: Changes for socket configuration
 *  LOG:
 *  LOG: Revision 1.1.1.1  2008/08/07 13:49:59  vnarang
 *  LOG: Light wieght IntelliSS7 ( AcceleroCore)
 *  LOG:
 *  LOG: Revision 1.1.2.4  2007/02/17 07:58:22  nanaparthi
 *  LOG: Fix for Follwing issue (Bug 5237)
 *  LOG:  On non-redundant static setup with SCTP transport if you kill the client
 *  LOG:  abnormally on peer side trace prints Exception Caught: CodecException ,
 *  LOG:  Error Cause: Wrong Command Header length
 *  LOG:
 *  LOG: Revision 1.1.2.3  2007/01/01 13:48:11  nanaparthi
 *  LOG: Support for SCTP MultiHoming
 *  LOG:
 *  LOG: Revision 1.1.2.2  2006/10/06 05:35:12  nanaparthi
 *  LOG: Support for SCTP MultiHoming server
 *  LOG:
 *  LOG: Revision 1.1.2.1  2006/09/26 06:59:21  nanaparthi
 *  LOG: Baseline LKSCTP support for Linux ( Naresh, Viji).
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: its_lksctp_sockets.h,v 1.1.4.1.8.1 2013/11/05 09:49:37 jvikram Exp $"

#ifndef ITS_LKSCTP_SOCKETS_H
#define ITS_LKSCTP_SOCKETS_H

#include <its_sockets.h>

/*
 * Forward Decls for procedures
 */
#ifdef __cplusplus
extern "C" {
#endif

/*
 * open and initialize a MultiHomed server socket
 */
ITSDLLAPI extern int LKSCTP_SOCK_MultiHomeServerOpen(ITS_SocketInfo **info,
                                           ITS_SOCK_DOMAIN domain,
                                           const char *host_or_path[],
                                           int port,int no_ips,ITS_SockConfigOpt* sockOpt);

/*
 * open and initialize a Server socket
 */
ITSDLLAPI extern int LKSCTP_SOCK_ServerOpen(ITS_SocketInfo **info,
                                           ITS_SOCK_DOMAIN domain,
                                           const char *host_or_path,
                                           int port);
/*
 * open and initialize a MultiHomed client socket
 */
ITSDLLAPI extern int LKSCTP_SOCK_MultiHomeClientOpen(ITS_SocketInfo **info,
                                           ITS_SOCK_DOMAIN domain,
                                           const char *host_or_path[],
                                           int port,int no_ips, 
                                           ITS_SockConfigOpt* sockOpt);   


/*
 * open and initialize a client socket
 */
ITSDLLAPI extern int LKSCTP_SOCK_ClientOpen(ITS_SocketInfo **info,
                                           ITS_SOCK_DOMAIN domain,
                                           const char *host_or_path,
                                           int port, ITS_SockConfigOpt* sockOpt);

/*
 * accept a connection on a server socket
 */
ITSDLLAPI extern int LKSCTP_SOCK_ServerAccept(ITS_SocketInfo* sock,
                                          ITS_SocketInfo** newInfo);
/*
 * accept a connection on a server socket ipv6 
 */
ITSDLLAPI extern int LKSCTP_SOCK_Ipv6ServerAccept(ITS_SocketInfo* sock,
                                          ITS_SocketInfo** newInfo);


/*
 * connect to a server from a client
 */
ITSDLLAPI extern int LKSCTP_SOCK_ClientConnect(ITS_SocketInfo* sock);

/*
 * connect to a server from a client
 */
ITSDLLAPI extern int LKSCTP_SOCK_Ipv6ClientConnect(ITS_SocketInfo* sock);

/*
 * read data from a socket
 */
ITSDLLAPI extern int LKSCTP_SOCK_Read(ITS_SocketInfo* sock,
                                    char *buf, int nbytes);

/*
 * write data to a socket
 */
ITSDLLAPI extern int LKSCTP_SOCK_Write(ITS_SocketInfo* sock,
                                    char *buf, int nbytes);

ITSDLLAPI extern int LKSCTP_SOCK_Stream_Write(ITS_SocketInfo* sock,
                                    char *buf, int nbytes, 
                                    int *streamNo, int maxOutStream);

#ifdef __cplusplus
}
#endif

#if defined(USE_CPLUSPLUS)
#include <its_exception.h>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*.interface:LKSctpClientSocket
 *****************************************************************************
 *  Interface:
 *      LKSctpClientSocket
 *
 *  Purpose:
 *      Client sockets represent the connecting side of a SCTP transport
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
/*
 * client side
 */
class LKSctpClientSocket : public Socket
{
public:
    /*.implementation:public,inline,LKSctpClientSocket
     ************************************************************************
     *  Purpose:
     *      This method creates a  client socket
     *
     *  Input Parameters:
     *      domain - either INET or UNIX address families.
     *      host_or_path - the hostname of the server, or the pathname to the
     *          UNIX domain socket
     *      port - the port number to connect to on the server
     *
     *  Notes:
     *      This method can throw exceptions if the socket cannot be opened.
     *
     ************************************************************************/
    LKSctpClientSocket(ITS_SOCK_DOMAIN domain,
                 const char *host_or_path, int port, ITS_SockConfigOpt* sockOpt)
        : Socket()
    {
        if (LKSCTP_SOCK_ClientOpen(&info, domain, host_or_path, port, sockOpt) != ITS_SUCCESS)
        {
            throw Error(ITS_EBADSOCKET, __FILE__, __LINE__);
        }
    }
    LKSctpClientSocket(ITS_SOCK_DOMAIN domain,
                 const char *host_or_path[], int port,int no_ips, ITS_SockConfigOpt* sockOpt)
        : Socket()   // SCTP MultiHoming
    {
        if (LKSCTP_SOCK_MultiHomeClientOpen(&info, domain, host_or_path, port,no_ips, sockOpt) != ITS_SUCCESS)
        {
            throw Error(ITS_EBADSOCKET, __FILE__, __LINE__);
        }
    }

    /*.implementation:public,inline,LKSctpClientSocket
     ************************************************************************
     *  Purpose:
     *      This method destroyes  client sockets.
     *
     ************************************************************************/
    virtual ~LKSctpClientSocket()
    {
    }

    /*.implementation:public,inline,LKSctpClientSocket
     ************************************************************************
     *  Purpose:
     *      This method attempts to connect the  client socket to the
     *      server.
     *
     *  Return Value:
     *      If the return value is less than zero, an error is returned.
     *      Otherwise, zero indicates success.
     *
     ************************************************************************/
    int
    Connect()
    {
        ITS_THROW_ASSERT(info != NULL);

        return LKSCTP_SOCK_ClientConnect(info);
    }
	/*.implementation:public,inline,LKSctpClientSocket ipv6
     ************************************************************************
     *  Purpose:
     *      This method attempts to connect the  client socket to the
     *      server.
     *
     *  Return Value:
     *      If the return value is less than zero, an error is returned.
     *      Otherwise, zero indicates success.
     *
     ************************************************************************/
    int
    Connect_Ipv6()
    {
        ITS_THROW_ASSERT(info != NULL);

        return LKSCTP_SOCK_Ipv6ClientConnect(info);
    }

    /*.implementation:public,inline,Socket
     ************************************************************************
     *  Purpose:
     *      This method reads data from a  socket.
     *
     *  Input Parameters:
     *      nbytes - the maximum number of bytes to read
     *
     *  Return Value:
     *      If the return value is less than zero, an error occurred.
     *      Any other return value indicates the number of bytes read.
     *
     ************************************************************************/
    int
    SctpRead(char *buf, int nbytes)
    {  
        ITS_THROW_ASSERT(info != NULL);

        return LKSCTP_SOCK_Read(info, buf, nbytes);
    }

    /*.implementation:public,inline,Socket
     ************************************************************************
     *  Purpose:
     *      This method writes data to a  socket.
     *
     *  Input Parameters:
     *      buf - a pointer to the buffer to send
     *      nbytes - the maximum number of bytes to write
     *
     *  Return Value:
     *      If the return value is less than zero, an error occurred.
     *      Any other return value indicates the number of bytes written.
     *
     ************************************************************************/
    int
    SctpWrite(char *buf, int nbytes)
    {
        ITS_THROW_ASSERT(info != NULL);

        return LKSCTP_SOCK_Stream_Write(info, buf, nbytes, &info->stream_no, info->max_out_stream);
    }
    
private:
    /* sorry folks, no copying these */
    LKSctpClientSocket() {}
    LKSctpClientSocket(LKSctpClientSocket&) {}
    LKSctpClientSocket& operator=(LKSctpClientSocket&) { return *this; }
};

/*.interface:LKSctpServerSocket
 *****************************************************************************
 *  Interface:
 *      LKSctpServerSocket
 *
 *  Purpose:
 *      Server sockets represent the accepting side of a SCTP transport.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
/*
 * server side
 */
class LKSctpServerSocket : public Socket
{
public:
    /*.implementation:public,inline,LKSctpServerSocket
     ************************************************************************
     *  Purpose:
     *      This method creates a  server socket.
     *
     *  Input Parameters:
     *      domain - either INET or UNIX address families.
     *      host_or_path - the hostname of the server, or the pathname to the
     *          UNIX domain socket
     *      port - the port number to connect to on the server
     *
     *  Notes:
     *      This method can throw exceptions if the socket cannot be opened.
     *
     ************************************************************************/
    LKSctpServerSocket(ITS_SOCK_DOMAIN domain,
                 const char *host_or_path, int port)
        : Socket()
    {
        if (LKSCTP_SOCK_ServerOpen(&info, domain, host_or_path, port) != ITS_SUCCESS)
        {
            throw Error(ITS_EBADSOCKET, __FILE__, __LINE__);
        }
    }
    LKSctpServerSocket(ITS_SOCK_DOMAIN domain,
                 const char *host_or_path[], int port,int no_ips,ITS_SockConfigOpt* sockOpt)
        : Socket()
    {
        if (LKSCTP_SOCK_MultiHomeServerOpen(&info, domain, host_or_path, port,no_ips,sockOpt) != ITS_SUCCESS)
        {
            throw Error(ITS_EBADSOCKET, __FILE__, __LINE__);
        }
    }

    /*.implementation:public,inline,LKSctpServerSocket
     ************************************************************************
     *  Purpose:
     *      This method destroys a  server socket.
     *
     ************************************************************************/
    virtual ~LKSctpServerSocket()
    {
    }

    /*.implementation:public,inline,LKSctpServerSocket
     ************************************************************************
     *  Purpose:
     *      This method accepts a connection on a  server socket.
     *
     *  Output Parameters:
     *      clone - an ITS_GatedSocket containing the new connection
     *
     *  Return Value:
     *      If a new client is successfully accepted, ITS_SUCCESS is returned.
     *      Any other value indicates an IntelliSS7 processing error.
     *
     ************************************************************************/
    int
    Accept(Socket** clone)
    {
        int ret;
        ITS_SocketInfo *tmp = NULL;

        ret = LKSCTP_SOCK_ServerAccept(info, &tmp);

        *clone = NULL;

        if (ret == ITS_SUCCESS)
        {
            *clone = new Socket;

            (*clone)->SetSocketInfo(tmp);
        }

        return ret;
    }
	/*.implementation:public,inline,LKSctpServerSocket
     ************************************************************************
     *  Purpose:
     *      This method accepts a connection on a  server socket.
     *
     *  Output Parameters:
     *      clone - an ITS_GatedSocket containing the new connection
     *
     *  Return Value:
     *      If a new client is successfully accepted, ITS_SUCCESS is returned.
     *      Any other value indicates an IntelliSS7 processing error.
     *
     ************************************************************************/
    int
    Accept_Ipv6(Socket** clone)
    {
        int ret;
        ITS_SocketInfo *tmp = NULL;

        ret = LKSCTP_SOCK_ServerAccept(info, &tmp);

        *clone = NULL;

        if (ret == ITS_SUCCESS)
        {
            *clone = new Socket;

            (*clone)->SetSocketInfo(tmp);
        }

        return ret;
    }
    /*.implementation:public,inline,Socket
     ************************************************************************
     *  Purpose:
     *      This method reads data from a  socket.
     *
     *  Input Parameters:
     *      nbytes - the maximum number of bytes to read
     *
     *  Return Value:
     *      If the return value is less than zero, an error occurred.
     *      Any other return value indicates the number of bytes read.
     *
     ************************************************************************/
    int
    SctpRead(char *buf, int nbytes)
    {
        ITS_THROW_ASSERT(info != NULL);

        return LKSCTP_SOCK_Read(info, buf, nbytes);
    }

    /*.implementation:public,inline,Socket
     ************************************************************************
     *  Purpose:
     *      This method writes data to a  socket.
     *
     *  Input Parameters:
     *      buf - a pointer to the buffer to send
     *      nbytes - the maximum number of bytes to write
     *
     *  Return Value:
     *      If the return value is less than zero, an error occurred.
     *      Any other return value indicates the number of bytes written.
     *
     ************************************************************************/
    int
    SctpWrite(char *buf, int nbytes)
    {
        ITS_THROW_ASSERT(info != NULL);

        return LKSCTP_SOCK_Stream_Write(info, buf, nbytes, &info->stream_no, info->max_out_stream);
    }

private:
    /* sorry folks, no copying these */
    LKSctpServerSocket() {}
    LKSctpServerSocket(LKSctpServerSocket&) {}
    LKSctpServerSocket& operator=(LKSctpServerSocket&) { return *this; }
};

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* USE_CPLUSPLUS */

#endif /* ITS_LKSCTP_SOCKETS_H */
