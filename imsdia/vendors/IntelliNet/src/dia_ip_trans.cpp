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
 * LOG: $Log: dia_ip_trans.cpp,v $
 * LOG: Revision 3.15.6.3.4.2.4.3.14.5  2020/02/14 11:38:22  jkchaitanya
 * LOG: removed unwanted test logs for tcp time out fix
 * LOG:
 * LOG: Revision 3.15.6.3.4.2.4.3.14.4  2020/02/14 11:36:11  jkchaitanya
 * LOG: TCP Timeout fix ported from DRE
 * LOG:
 * LOG: Revision 3.15.6.3.4.2.4.3.14.3  2015/02/17 06:22:44  jkchaitanya
 * LOG: changes for peer down crash ported from stack branch for bugs 5507, 6067
 * LOG:
 * LOG: Revision 3.15.6.3.4.2.4.3.14.2  2014/12/17 05:19:08  jkchaitanya
 * LOG: changes to revert back the server down crash changes
 * LOG:
 * LOG: Revision 3.15.6.3.4.2.4.3  2013/10/26 07:42:21  ncshivakumar
 * LOG: RFC 6733 changes
 * LOG:
 * LOG: Revision 3.15.6.3.4.2.4.2  2013/09/10 08:36:39  ncshivakumar
 * LOG: RFC6733 Changes
 * LOG:
 * LOG: Revision 3.15.6.3.4.2.4.1  2013/07/25 04:38:15  ncshivakumar
 * LOG: Fix for dre crash during load.Refer bug 1639.
 * LOG:
 * LOG: Revision 3.15.6.3.4.2  2013/04/12 04:17:30  vsarath
 * LOG: Logs improvement
 * LOG:
 * LOG: Revision 3.15.6.3.4.1  2013/03/28 07:25:34  ncshivakumar
 * LOG: Fix for bug 1312
 * LOG:
 * LOG: Revision 3.15.6.3  2012/12/28 09:25:17  mallikarjun
 * LOG: Bug 757 chages
 * LOG:
 * LOG: Revision 3.15.6.2  2012/11/20 17:39:44  pramana
 * LOG: Merged from CMAPI branch for 212-07 release
 * LOG:
 * LOG: Revision 3.15.6.1.8.1  2012/11/19 08:35:43  millayaraja
 * LOG: modified for Transport Stats
 * LOG:
 * LOG: Revision 3.15.6.1  2012/10/19 17:54:43  brajappa
 * LOG: BugId 15: IPv6 support enhancements
 * LOG:
 * LOG: Revision 3.15  2010/11/03 12:54:24  vkumara
 * LOG: DSCP support for IPV6
 * LOG:
 * LOG: Revision 3.14  2010/10/11 07:57:26  rajeshak
 * LOG: Solaris IPV6 Support
 * LOG:
 * LOG: Revision 3.13  2009/07/24 09:17:28  rajeshak
 * LOG: Reverting back the split SessionTable changes (missing)
 * LOG:
 * LOG: Revision 3.12  2009/06/29 14:53:12  rajeshak
 * LOG: Write Mutex changes.
 * LOG:
 * LOG: Revision 3.11  2009/03/19 12:41:20  nvijikumar
 * LOG: Global instance is created for the Class ITSDiaConfig to avoid function
 * LOG: call overhead as ITSDiaConfig::GetITSDiaConfig() was called max time
 * LOG:
 * LOG: Revision 3.10  2009/03/19 11:17:56  chandrashekharbs
 * LOG: Changes for IPV6 SCTP support
 * LOG:
 * LOG: Revision 3.9  2009/03/03 06:53:47  chandrashekharbs
 * LOG: Changes for IPV6 TCP support
 * LOG:
 * LOG: Revision 3.8  2009/02/19 08:32:15  rajeshak
 * LOG: IssueID: 1574 & 1637
 * LOG: FeatureID:none
 * LOG: Description: Coredump on getting DPR on SCTP transport.
 * LOG: Clearing the transport instance from the trTable after socket delete.
 * LOG:
 * LOG: Revision 3.7  2009/02/04 05:57:11  nvijikumar
 * LOG: Changes for 64 Peer support with fixed number of threads
 * LOG:
 * LOG: Revision 3.6  2009/02/02 06:44:31  rajeshak
 * LOG: Passing sctp config params in constructor
 * LOG:
 * LOG: Revision 3.5  2008/12/12 16:36:06  nvijikumar
 * LOG: Updates to raise Alarms
 * LOG:
 * LOG: Revision 3.4  2008/10/28 12:06:28  nvijikumar
 * LOG: IssueID: none
 * LOG: FeatureID: none
 * LOG: Description: Porting Performance changes from 3.0 branch
 * LOG:
 * LOG: Revision 3.3  2008/07/09 10:52:45  vnarang
 * LOG: Adding a check for TLS_ENABLED flag during compilation
 * LOG:
 * LOG: Revision 3.2  2008/06/13 11:24:38  hbhatnagar
 * LOG: Added code to implement the TLS feature. Modified the Read and Write
 * LOG: for the sockets
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.17  2008/03/27 12:14:08  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.16.2.2  2008/01/07 17:59:45  hbhatnagar
 * LOG: Reverting back the changes done in NonBlockingRead API() for solaris 2.1
 * LOG: branch (For Bridgwater ticket 1836). After a detailed discussion with
 * LOG: Yogesh and Rachel it was decided to use Blocking version of Read in
 * LOG: Diameter ReadEvent() API (as it was earlier). Instead send  signal to
 * LOG: particular thread which is on Blocking read so that read is interrupted and
 * LOG: we can shutdown the sockets. This resolution is preferred over the
 * LOG: NonBlockingRead() for performance reasons as  NBR involves polling.
 * LOG: The branch tag B-IDIA-0210-00 ( cut for both IntelliSS7 and imsdia)
 * LOG: created to provide the interim patch to Bridgewater for the ticket 1836
 * LOG: remains unchanged ( discussed with Rachel) and NonBlockingRead() will
 * LOG: be used in it.
 * LOG:
 * LOG: Fix for issue no 15 and partial fix for issue no 23.
 * LOG:
 * LOG: Revision 2.16.2.1  2007/12/27 11:34:03  avinashks
 * LOG: Replaced the Read() with NonBlockingRead() API for solaris and solaris64.
 * LOG: for the bridgewater ticket 1836.
 * LOG:
 * LOG: Revision 2.16  2007/02/26 14:26:51  nvijikumar
 * LOG: Fix: SCTP fix for solaris 64 ( Added #if defined(solairs64) statement).
 * LOG:
 * LOG: Revision 2.15  2007/02/17 07:27:31  nanaparthi
 * LOG: Fix for Follwing issue (Bug 5237)
 * LOG:  On non-redundant static setup with SCTP transport if you kill the client
 * LOG:  abnormally on peer side trace prints Exception Caught: CodecException ,
 * LOG:  Error Cause: Wrong Command Header length
 * LOG:
 * LOG: Revision 2.14  2006/12/29 06:56:18  nanaparthi
 * LOG: SCTP Multihoming related changes (baseline code base)
 * LOG:
 * LOG: Revision 2.13  2006/12/11 13:51:25  tpanda
 * LOG: REDUNDANCY_SLOT_CHANGES are removed and code seems to be stable
 * LOG:
 * LOG: Revision 2.12  2006/12/10 13:42:42  tpanda
 * LOG: Redundancy Bug Fixes and enhancements--Transport Order Fix
 * LOG:
 * LOG: Revision 2.11  2006/11/28 13:31:04  nvijikumar
 * LOG: Fix for multiple peer connection core dump ( Tushar).
 * LOG:
 * LOG: Revision 2.10  2006/11/25 03:57:20  tpanda
 * LOG: Changes for Msg based redundancy
 * LOG:
 * LOG: Revision 2.9  2006/11/06 05:16:24  nvijikumar
 * LOG: SCTP support for 64bit solaris compilation.
 * LOG:
 * LOG: Revision 2.8  2006/10/24 17:23:35  nvijikumar
 * LOG: Fix for BugId: 4494.
 * LOG: Exit from the thread if failed to create socket.
 * LOG:
 * LOG: Revision 2.7  2006/10/17 17:33:59  yranade
 * LOG: Display Type of transport when shutting down, for readability in tracing.
 * LOG:
 * LOG: Revision 2.6  2006/10/16 06:19:35  yranade
 * LOG: Remove unwanted trace.
 * LOG:
 * LOG: Revision 2.5  2006/10/07 12:24:55  yranade
 * LOG: Today's round of updates.
 * LOG:
 * LOG: Revision 2.4  2006/10/05 13:21:54  yranade
 * LOG: Getting there.
 * LOG:
 * LOG: Revision 2.3  2006/09/26 06:05:56  nvijikumar
 * LOG: SCTP changes ( Viji, Naresh)
 * LOG:
 * LOG: Revision 2.2  2006/09/13 16:06:59  yranade
 * LOG: Ensure socket is initialized.
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:44  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:29  yranade
 * LOG: Initial Version of ITS-Diameter (Yogesh, Viji, Tushar)
 * LOG:
 * ID: $Id: dia_ip_trans.cpp,v 3.15.6.3.4.2.4.3.14.5 2020/02/14 11:38:22 jkchaitanya Exp $
 ****************************************************************************/
#ident "$Id: dia_ip_trans.cpp,v 3.15.6.3.4.2.4.3.14.5 2020/02/14 11:38:22 jkchaitanya Exp $"

#include <net/if.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <arpa/nameser.h>
#include <errno.h>

#if defined TRY_AGAIN
#undef TRY_AGAIN
#endif

#include <its_dia_config.h>

#include <dia_cmn.h>
#include <dia_err.h>
#include <dia_utils.h>
#include <dia_trace.h>
#include <dia_ip_trans.h>
#include <dia_peer_fsm.h>
#include <dia_peer_table.h>
#include <dia_msg_router.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
#endif

its::ITS_Mutex  __TIGate(0);
DiaSocketTransportContainer trTable;

#if !defined(linux) || defined(USE_SELECT)
extern DiaSelectSockContainer connSelectTbl;
extern DiaSelectSockContainer accSelectTbl;
#endif



ITS_USHORT
DiaSocketTransport::InsertInstance(ITS_USHORT instance)
{
    const_cast<ITS_Mutex&>(__TIGate).Acquire();
    if (_type != ITS_DIA_CLIENT_SOCK_TRANS &&
        instance && trTable.getAt(instance) == NULL)
    {
       trTable.addAt(instance, this);
       const_cast<ITS_Mutex&>(__TIGate).Release();
       return instance;
    }
    const_cast<ITS_Mutex&>(__TIGate).Release();
    return instance;
}
void
DiaSocketTransport::ClearTrInstance()
{
   const_cast<ITS_Mutex&>(__TIGate).Acquire();
    if (_type != ITS_DIA_CLIENT_SOCK_TRANS &&
        trTable.getAt(_instance) != NULL)
    {
       trTable.addAt(_instance, NULL);
       const_cast<ITS_Mutex&>(__TIGate).Release();
    }
    const_cast<ITS_Mutex&>(__TIGate).Release();

}

ITS_USHORT
DiaSocketTransport::AllocateInstance()
{
    int i;

    const_cast<ITS_Mutex&>(__TIGate).Acquire();

    for (i = 1; i < MAX_LOCAL_TRANSPORTS; i++)
    {
        if (trTable[i] == NULL)
        {
            //this function will be deprecated soon
            //trTable[i] = this;

            const_cast<ITS_Mutex&>(__TIGate).Release();

            return (i);
        }

        if (i >= MAX_LOCAL_TRANSPORTS)
        {
            const_cast<ITS_Mutex&>(__TIGate).Release();
            return (0);
        }
    }

    const_cast<ITS_Mutex&>(__TIGate).Release();

    return (0);
}

ITS_UINT
DiaSocketTransport::Initialize(const char* serverHostName, ITS_USHORT portNo)
{
    _hostName = serverHostName;
    _portNo = portNo;
    DT_DBG(("Transport [%d] Initialize", this->GetInstance()));
    try
    {
        if (_type == ITS_DIA_CLIENT_SOCK_TRANS)
        {
            if (DiaUtils::IsIPv6Address(serverHostName) == true)
            {
                _socket = new its::ClientSocket(INET6_DOMAIN,
                                serverHostName,
                                portNo, true);
                return (ITS_SUCCESS);
            }
            else
            {
                _socket = new its::ClientSocket(INET_DOMAIN,
                                                serverHostName,
                                                portNo, true);
                return (ITS_SUCCESS);

            }
        }
        else if (_type == ITS_DIA_SERVER_SOCK_TRANS)
        {
            if (DiaUtils::IsIPv6Address(serverHostName) == true)
            {
                _socket = new its::ServerSocket(INET6_DOMAIN,
                                                serverHostName,
                                                portNo);
				return (ITS_SUCCESS);
            }
            else
            {
                _socket = new its::ServerSocket(INET_DOMAIN,
                                                serverHostName,
                                                portNo);
                return (ITS_SUCCESS);
            }
        }
        else if (_type == ITS_DIA_SERVER_DYN_SOCK_TRANS)
        {
            /* DO Nothing */
            return (ITS_SUCCESS);
        }

    }
    catch (...)
    {
        DT_ERR(("Failed to Init Transport for Host %s : Port %d: Check IP ",
                serverHostName, portNo));

        if (_socket == NULL)
        {
	    throw "Failed to Init Transport";
        }

        return (!ITS_SUCCESS);
    }

    return (!ITS_SUCCESS);
}

ITS_UINT
DiaSocketTransport::Initialize(const char* serverHostName, ITS_USHORT portNo,
         const char *multiHomeipaddrs[], ITS_USHORT  noIPs) //SCTP MultiHoming
{
    _hostName = serverHostName;
    _portNo = portNo;
    _multiHomeipaddrs =  multiHomeipaddrs;    // SCTP MultiHoming
    _noIPs = noIPs;
    ITS_INT dscp = itsDiaConfig.getLocalIpv6DscpVal();

    DT_DBG(("Transport [%d] Initialize", this->GetInstance()));
    try
    {
        ITS_SockConfigOpt* sockOpt = NULL;
        sockOpt = itsDiaConfig.GetStreamSocketConfig();
        if (_type == ITS_DIA_SCTP_CLIENT_SOCK_TRANS)
        {

#if defined(linux)
        if (DiaUtils::IsIPv6Address(serverHostName) == true)
        {
            _socket = new its::LKSctpClientSocket(INET6_DOMAIN,
                                              multiHomeipaddrs,
                                              portNo,
                                              noIPs, sockOpt);
        }
        else
        {
            _socket = new its::LKSctpClientSocket(INET_DOMAIN,
                                  multiHomeipaddrs,
                                  portNo,
                                  noIPs, sockOpt);
        }
        ITS_SocketInfo *sockInfo = _socket->GetSocketInfo();
        //Hard coded ppid need to be changed when supporting DTLS
        sockInfo->ppid = SCTP_PPID_FOR_CLEAR_TEXT;
        _socket->SetSocketInfo(sockInfo);
#elif defined(solaris) || defined(solaris64)
        /* SCTP MultiHoming not yet supported for solaris */
        if (DiaUtils::IsIPv6Address(serverHostName) == true)
        {
            _socket = new its::SKSctpClientSocket(INET6_DOMAIN,
                                                  serverHostName,
                                                  portNo);
        }
        else
        {
            _socket = new its::SKSctpClientSocket(INET_DOMAIN,
                                                  serverHostName,
                                                  portNo);
        }
#endif
            return (ITS_SUCCESS);
        }
        else if (_type == ITS_DIA_SCTP_SERVER_SOCK_TRANS)
        {
#if defined(linux)
            if (DiaUtils::IsIPv6Address(serverHostName) == true)
            {
                _socket = new its::LKSctpServerSocket(INET6_DOMAIN,
                                                  multiHomeipaddrs,
                                                  portNo,
                                                  noIPs,sockOpt); //  SCTP MultiHoming
            }
            else
            {
                _socket = new its::LKSctpServerSocket(INET_DOMAIN,
                                                  multiHomeipaddrs,
                                                  portNo,
                                                  noIPs,sockOpt); //  SCTP MultiHoming
            }

            ITS_SocketInfo *sockInfo = _socket->GetSocketInfo();
            //Hard coded ppid need to be changed when supporting DTLS
            sockInfo->ppid = SCTP_PPID_FOR_CLEAR_TEXT;
            _socket->SetSocketInfo(sockInfo);
#elif defined(solaris) || defined(solaris64)
            /* SCTP MultiHoming not yet supported for solaris */
            if (DiaUtils::IsIPv6Address(serverHostName) == true)
            {
                _socket = new its::SKSctpServerSocket(INET6_DOMAIN,
                                                  serverHostName,
                                                  portNo,
                                                  dscp );
            }
            else
            {
                _socket = new its::SKSctpServerSocket(INET_DOMAIN,
                                                  serverHostName,
                                                  portNo,
                                                  dscp);
            }
#endif
            return (ITS_SUCCESS);
        }
        else if (_type == ITS_DIA_SCTP_SERVER_DYN_SOCK_TRANS)
        {
            /* DO Nothing */
            return (ITS_SUCCESS);
        }

    }
    catch (...)
    {
        DT_ERR(("Failed to Init Transport for Host %s : Port %d: Check IP ",
                serverHostName, portNo));

        if (_socket == NULL)
        {
	    throw "Failed to Init Transport";
        }
        return (!ITS_SUCCESS);
    }
    return (!ITS_SUCCESS);
}

void
DiaSocketTransport::Shutdown()
{
    //DIA_INC_PEER_CONNECTION_TOTAL_TRANSPORT_DOWN_COUNT();
    /*TODO: Invoke PeerDisconnectCb to inform to
      user
    */
    DT_WRN(("Transport [%d] Type = [%s] Shutdown",
            GetInstance(), ITS_DIA_SOCK_TRANS_TYPE_TO_TEXT(GetType())));
#if !defined(linux) || defined(USE_SELECT)
    if (_transSpec == DIA_TRANS_ACCEPTOR)
    {
        accSelectTbl.UnsetSelectSock(_fdIndex);
    }
    else
    {
        connSelectTbl.UnsetSelectSock(_fdIndex);
    }
#endif
    trTable.addAt(GetInstance(), NULL);
    delete this;
}

int
DiaSocketTransport::ReadEvent(ITS_EVENT *cEvt)
{
    int ret = ITS_SUCCESS;
    ITS_OCTET buf[sizeof(ITS_UINT)];

#ifdef TLS_ENABLED
    if(_tlsSess != NULL)
    {
        /* Read the Length */
        ret = _tlsSess->RecordRecieve((char *)buf, sizeof(ITS_UINT));
    }
    else
    {
#endif
        /* Read the Length */
        if (GetType() == ITS_DIA_SCTP_SERVER_SOCK_TRANS ||
            GetType() == ITS_DIA_SCTP_CLIENT_SOCK_TRANS)
        {
            fflush(stdout);
            if(_socket != NULL)
            {
#if defined(linux)
                ret = ((its::LKSctpServerSocket *)_socket)->
                    SctpRead((char *)buf, sizeof(ITS_UINT));
#elif defined(solaris) || defined(solaris64)
                ret = ((its::SKSctpServerSocket *)_socket)->
                    SctpRead((char *)buf, sizeof(ITS_UINT));
#endif
            }
            else
            {
                DT_DBG(("Socket is already deleted"));
            }
        }
        else
        {
            /**
             * Reverting back the changes done for the NonBlockingRead() API
             * for solaris. Keeping the Blocking Read() (As discussed with
             * Yogesh).
             */
            ret = this->_socket->Read((char *)buf, sizeof(ITS_UINT));
        }
#ifdef TLS_ENABLED
    }
#endif

    if (ret != sizeof(ITS_UINT))
    {
        return (0);
    }

    /* IMP: ITS_EVENT: Len is a USHORT: */

    int msgLen = 0;
    msgLen = DiaUtils::DataToInt(&buf[1], (sizeof(ITS_UINT) - 1));

    DT_DBG(("MsgLen = %d\n", msgLen));

    cEvt->len = msgLen + sizeof(ITS_USHORT);

    cEvt->data = NULL;
    cEvt->data = (ITS_OCTET *)ITS_Malloc(msgLen + sizeof(ITS_USHORT));

    if (cEvt->data == NULL)
    {
        return (ITS_ENOMEM);
    }

    /* Copy in the trInstance */
    ITS_SET_CTXT(cEvt->data, this->GetInstance());
#if 0
    cEvt->data[0] = (this->GetInstance() & 0x000000FF);
    cEvt->data[1] = (this->GetInstance() & 0x0000FF00) >> 8;
#endif

    /* Now copy in the payload */
    memcpy(&cEvt->data[sizeof(ITS_USHORT)], buf, sizeof(ITS_UINT));

    ITS_UINT bytesRead = 0;
    ITS_UINT bytesToRead = ((cEvt->len) - sizeof (ITS_USHORT) -
                             sizeof(ITS_UINT) - bytesRead);

    /* Read the data */
    int index = sizeof(ITS_USHORT) + sizeof(ITS_UINT) + bytesRead;
#ifdef TLS_ENABLED
    if(_tlsSess != NULL)
    {
        bytesRead = _tlsSess->RecordRecieve((char *)&cEvt->data[index],
                                            bytesToRead);
    }
    else
    {
#endif
        if (GetType() == ITS_DIA_SCTP_SERVER_SOCK_TRANS ||
            GetType() == ITS_DIA_SCTP_CLIENT_SOCK_TRANS)
        {
            fflush(stdout);
#if defined(linux)
            bytesRead  = ((its::LKSctpServerSocket *)_socket)->
                           SctpRead((char *)&cEvt->data[index],bytesToRead);
#elif defined(solaris) || defined(solaris64)
            bytesRead  = ((its::SKSctpServerSocket *)_socket)->
                           SctpRead((char *)&cEvt->data[index],bytesToRead);
#endif
        }
        else
        {
            /**
             * Reverting back the changes done for the NonBlockingRead() API
             * for solaris. Keeping the Blocking Read() (As discussed with
             * Yogesh).
             */
            bytesRead = this->_socket->Read((char *)&cEvt->data[index],
                                            bytesToRead);
        }
#ifdef TLS_ENABLED
    }
#endif
    if (bytesRead != bytesToRead)
    {
        DT_CRT(("ReadEvent::Failure:ret = %d,errno = %d, bytesRead = %d, \
                                    bytesToRead = %d msgLen = %d",
                                    ret, errno, bytesRead, bytesToRead,msgLen));
        ITS_Free(cEvt->data);
        cEvt->data = NULL;
        cEvt->len = 0;

        DIA_Alarm(15100, __FILE__, __LINE__, "ret =%d,errno = %d",ret, errno);

        return (ITS_ERCVFAIL);
    }

    return bytesRead;
}

void
DiaSocketTransport::Shutdown(DiaEpollSockContainer* epollTbl)
{
    /*TODO: Invoke PeerDisconnectCb to inform to
     *    user
     *        */
    DT_WRN(("Transport [%d] Type = [%s] Shutdown",
                GetInstance(), ITS_DIA_SOCK_TRANS_TYPE_TO_TEXT(GetType())));
#if !defined(linux) || defined(USE_SELECT)
    if (_transSpec == DIA_TRANS_ACCEPTOR)
    {
        accSelectTbl.UnsetSelectSock(_fdIndex);
    }
    else
    {
        connSelectTbl.UnsetSelectSock(_fdIndex);
    }
#else
    //trTable.addAt(GetInstance(), NULL);
    //delete this;
    if (epollTbl != NULL)
    {
        epollTbl->DelEpollSock(this);
    }
#endif
    trTable.addAt(GetInstance(), NULL);

    markDown();
    if (IsDelayTimerStarted())
    {
        DT_ERR(("Transport delete delay timer is already started"));
    }
    else
    {
        SetStartedDelayTimer();
        StartTrHandleDeleteDelayTimer();
    }
}

int
DiaSocketTransport::WriteData(ITS_OCTET *data, ITS_UINT len)
{
    int          ret = !ITS_SUCCESS;
    int          bytesSent = 0;
    ITS_OCTET    *dataToSend = NULL;
    ITS_INT      lenToSend = 0;
    ITS_INT      error = 0;
    ITS_BOOLEAN  isSocketCongested = ITS_FALSE;
   
    if (CheckIfMarkedDown())
    {	

        return ret;
    }

    /* If unsent bytes are left, then attempt to send them first */
    if (_unsentDataLen)
    {

        dataToSend = _unsentData;
        lenToSend  = _unsentDataLen;

#ifdef TLS_ENABLED
        if (_tlsSess != NULL)
        {
            bytesSent = _tlsSess->RecordSend( (char *)dataToSend, lenToSend);
        }
        else
#endif
        {
            if (GetType() == ITS_DIA_SCTP_SERVER_SOCK_TRANS ||
                GetType() == ITS_DIA_SCTP_CLIENT_SOCK_TRANS)
            {
#if defined(linux)
                bytesSent = ((its::LKSctpServerSocket *)_socket)->
                        SctpWrite((char *)dataToSend, lenToSend);
#elif defined(solaris) || defined(solaris64)
                bytesSent = ((its::SKSctpServerSocket *)_socket)->
                        SctpWrite((char *)dataToSend, lenToSend);
#endif
            }
            else
            {
                bytesSent = this->_socket->Write((char *)dataToSend, lenToSend, &error);
            }
        }
        if (bytesSent == lenToSend)
	{

	    /* If we make the unsetDataLen to 0, then we can try to
 	     * send the new message out
 	     */
	    _unsentDataLen = 0;

	    free(_unsentData);
	    _unsentData = NULL;
		
	    /* Reset the last update and set the socket congestion flag to false,
             * this will stop the timer
             */
	     ResetSockFlushLastUpdate();
	     SetSockCongestionFlag(ITS_FALSE);
	     isSocketCongested = ITS_FALSE;
	
	     ret = ITS_SUCCESS;
	}
        else
	{
	    /* Here we aren't handling bytesSent == 0 case as that would be
             * only if the socket is blocked.  In such case we just check if
             * the timer is running or not.  If not start the timer.
             * Now, adjust the _unsentData pointer only if we send
             * something on socket
             */
	     if (bytesSent > 0)
	     {
		
	
		_unsentDataLen -= bytesSent;

		ITS_OCTET *tempBuf = (ITS_OCTET* )calloc(1, _unsentDataLen);
	
		if (tempBuf)
		{
		    memcpy(tempBuf, dataToSend + bytesSent, _unsentDataLen);
		    
		    free(_unsentData);

		    _unsentData = tempBuf;
		}
		ret = ITS_SUCCESS;
	     }
	     
	     if (DIA_PE_SOCK_FLUSH_RETRY_CNT(_peer) != 0)
	     {
		if ( (DIA_PE_SOCK_FLUSH_RETRY_CNT(_peer) == -1) ||
		     (DIA_PE_SOCK_FLUSH_CNT(_peer) < DIA_PE_SOCK_FLUSH_RETRY_CNT(_peer)))
		{
		    if (!IsSocketCongested())
		    {
			/* Reset the last update and set the socket congestion flag to true,
 			 * this will start the timer
 			 */
		
			ResetSockFlushLastUpdate();
			SetSockCongestionFlag(ITS_TRUE);
			isSocketCongested = ITS_TRUE; 
		    }
		}
	     }
	     else
	     {
	
		/* Mark this flag true, so that indication will be given to application */
	        isSocketCongested = ITS_TRUE;
	     }    	 
	}
    }

    /* Check for the message length here again.  This is because if the first write for
     * _unsentData is successful, then try to send the new message
     */
    if (_unsentDataLen == 0)
    {
	dataToSend = data;
	lenToSend  = len;


#ifdef TLS_ENABLED
	if (_tlsSess != NULL)
	{
	    
	    bytesSent = _tlsSess->RecordSend( (char *)dataToSend, lenToSend);
	}
	else
#endif
	{
	     if (GetType() == ITS_DIA_SCTP_SERVER_SOCK_TRANS ||
			GetType() == ITS_DIA_SCTP_CLIENT_SOCK_TRANS)
	     {
#if defined(linux)
		bytesSent = ( (its::LKSctpServerSocket *)_socket)->SctpWrite( (char *)dataToSend, lenToSend);
#elif (defined(solaris) || defined(solaris64))
		bytesSent = ( (its::SKSctpServerSocket *)_socket)->SctpWrite( (char *)dataToSend, lenToSend);
#endif
	     }
	     else
	     {
	
		bytesSent = this->_socket->Write((char *)dataToSend, lenToSend, &error);

	     }	
	}
	
	if (bytesSent == lenToSend)
	{

	    ret = ITS_SUCCESS;
	}
	else
	{
	    /* Here we aren't handling bytesSent == 0 case as that would be
             * only if the socket is blocked.  In such case we just check if
             * the timer is running or not.  If not start the timer.
             * Now, adjust the _unsentData pointer only if we send
             * something on socket
             */

	     if (bytesSent > 0)
	     {

		_unsentDataLen = lenToSend - bytesSent;
		
		/* This is the first time we have hit the socket block case.  Store the
 		 * unsent bytes in the member variables.
 		 */
		_unsentData = (ITS_OCTET* )calloc(1, _unsentDataLen);

		memcpy(_unsentData, dataToSend + bytesSent, _unsentDataLen);
		
		ret = ITS_SUCCESS;
		 
	     }

	     if (DIA_PE_SOCK_FLUSH_RETRY_CNT(_peer) != 0)
	     {
		if ( (DIA_PE_SOCK_FLUSH_RETRY_CNT(_peer) == -1) ||
		     (DIA_PE_SOCK_FLUSH_CNT(_peer) < DIA_PE_SOCK_FLUSH_RETRY_CNT(_peer)))
		{


		    if (!IsSocketCongested())
		    {

			/* Reset the last update and set the socket congestion flag to true,
 			 * this will start the timer
 			 */

			ResetSockFlushLastUpdate();
			SetSockCongestionFlag(ITS_TRUE);
			isSocketCongested = ITS_TRUE; 
		    }
		}
	     }
	     else
	     {

		/* Mark this flag true, so that indication will be given to application */
		isSocketCongested = ITS_TRUE;
	     } 
	}
    } 
    
    /* If the socket flush timer is running, then it means
     * that the socket is congested.  In such case give
     * PEER_CONG_START_IND_FROM_STACK to application
     */

     if (isSocketCongested) 
     {

	/* If indication isn't given earlier, then give indication to application */
	if (!DIA_PE_PEER_CONG_IND(_peer))
	{

	    if (itsDiaConfig.IsPeerMsgToAppEnabled())
	    {
		if (DiaMsgRouter::SendIndication(NULL, _peer, NULL, PEER_CONG_START_IND_FROM_STACK) != ITS_SUCCESS)
		{
		    DT_ERR(("Failed To send Congestion Abated Indication to application"));
		}
		
		DIA_PE_PEER_CONG_IND(_peer) = true;
	    }
	}
     }
     else
     {

	/* If indication is given earlier, then give indication to application */
	if (DIA_PE_PEER_CONG_IND(_peer))
	{

	    if (itsDiaConfig.IsPeerMsgToAppEnabled())
	    {
		if (DiaMsgRouter::SendIndication(NULL, _peer, NULL, PEER_CONG_ABATE_IND_FROM_STACK) != ITS_SUCCESS)
		{
		    DT_ERR(("Failed To send Congestion Abated Indication to application"));
		}

		DIA_PE_PEER_CONG_IND(_peer) = false;
	    }

	    DIA_PE_SOCK_FLUSH_CNT(_peer) = 0;
	}
     }
    

    return (ret);
}

int
DiaSocketTransport::FlushData(ITS_BOOLEAN &isPeerToBeDisconnected, ITS_BOOLEAN delUnsentData)
{
    int          ret = !ITS_SUCCESS;
    int          bytesSent = 0;
    ITS_OCTET    *dataToSend = NULL;
    ITS_INT      lenToSend = 0;
    ITS_INT      error = 0;
    ITS_SocketInfo *Info = this->_socket->GetSocketInfo();
  

    isPeerToBeDisconnected = ITS_FALSE;


    if (delUnsentData)
    {


        if (_unsentData)
        {

            free(_unsentData);
            _unsentData = NULL;
            _unsentDataLen = 0;
        }

        /* Reset the last update and set the socket congestion flag to false,
         * this will stop the timer
         */

        ResetSockFlushLastUpdate();
        SetSockCongestionFlag(ITS_FALSE);


        DIA_PE_SOCK_FLUSH_CNT(_peer) = 0;

        ret = ITS_SUCCESS;
    }
    else
    {


        if (CheckIfMarkedDown())
        {

            return ret;
        }
	

        /* If unsent bytes are left, then attempt to send them first */
        if (_unsentDataLen)
        {

            dataToSend = _unsentData;
            lenToSend  = _unsentDataLen;

#ifdef TLS_ENABLED
            if (_tlsSess != NULL)
            {

                bytesSent = _tlsSess->RecordSend( (char *)dataToSend, lenToSend);  
            }
            else
#endif
            {
                if (GetType() == ITS_DIA_SCTP_SERVER_SOCK_TRANS ||
		    GetType() == ITS_DIA_SCTP_CLIENT_SOCK_TRANS)
		{
#if defined(linux)
		    bytesSent = ( (its::LKSctpServerSocket *)_socket)->SctpWrite( (char *)dataToSend, lenToSend);
#elif (defined(solaris) || defined(solaris64))
		    bytesSent = ( (its::SKSctpServerSocket *)_socket)->SctpWrite( (char *)dataToSend, lenToSend);
#endif
                }
                else
                {

                    bytesSent = this->_socket->Write((char *)dataToSend, lenToSend, &error);

                }
            }

            /* restart the timer or any operation is required only if send
             * is successful or failed due to EWOULDBLOCK / EAGAIN
             */
            if (bytesSent == lenToSend)
            {

                /* If we make the unsetDataLen to 0, then we can try to
                 * send the new message out
                 */
                _unsentDataLen = 0;

                free(_unsentData);
                _unsentData = NULL;

                /* Reset the last update and set the socket congestion flag to false,
                 * this will stop the timer
                 */

                ResetSockFlushLastUpdate();
                SetSockCongestionFlag(ITS_FALSE);

                /* If indication is given earlier, then give indication to application */
                if (DIA_PE_PEER_CONG_IND(_peer))
                {

                    if (itsDiaConfig.IsPeerMsgToAppEnabled())
                    {
                        if (DiaMsgRouter::SendIndication(NULL, _peer, NULL, PEER_CONG_ABATE_IND_FROM_STACK) != ITS_SUCCESS)
                        {
                            DT_ERR(("Failed To send Congestion Abated Indication to application"));
                        }

                        DIA_PE_PEER_CONG_IND(_peer) = false;
                    }


                    DIA_PE_SOCK_FLUSH_CNT(_peer) = 0;

                }
            }
            else
            {
                /* Here we aren't handling bytesSent == 0 case as that would be
                 * only if the socket is blocked.  In such case we just check if
                 * the timer is running or not.  If not start the timer.
                 * Now, adjust the _unsentData pointer only if we send
                 * something on socket
                 */

                if (bytesSent > 0)
                {

                    _unsentDataLen -= bytesSent;

                    ITS_OCTET *tempBuf = (ITS_OCTET* )calloc(1, _unsentDataLen);

                    if (tempBuf)
                    {
                        memcpy(tempBuf, dataToSend + bytesSent, _unsentDataLen);

                        free(_unsentData);

                        _unsentData = tempBuf;
                    }
                }


                if ( (DIA_PE_SOCK_FLUSH_RETRY_CNT(_peer) == -1) ||
                     (DIA_PE_SOCK_FLUSH_CNT(_peer) < DIA_PE_SOCK_FLUSH_RETRY_CNT(_peer)))
                {

                    /* Reset the last update and set the socket congestion flag to true,
                     * this will start the timer
                     */

                    ResetSockFlushLastUpdate();
                    SetSockCongestionFlag(ITS_TRUE);
		    

                    DIA_PE_SOCK_FLUSH_CNT(_peer)++;

                }
            }
	    ret = ITS_SUCCESS;
        }
    }



    if (DIA_PE_SOCK_FLUSH_RETRY_CNT(_peer) != 0)
    {
        if ( (DIA_PE_SOCK_FLUSH_RETRY_CNT(_peer) > 0) && (DIA_PE_SOCK_FLUSH_CNT(_peer) >= DIA_PE_SOCK_FLUSH_RETRY_CNT(_peer)))
        {
	     
            isPeerToBeDisconnected = ITS_TRUE;

            /* Reset the last update and set the socket congestion flag to false,
             * this will stop the timer
             */

            ResetSockFlushLastUpdate();
            SetSockCongestionFlag(ITS_FALSE);
        }
    }

    return (ret);
}


void
DiaSocketTransport::GetSockInfo(ITS_SocketInfo *info)
{
    struct hostent *hostinfo;
    struct in_addr in;

    DT_DBG(("sock_debug_dump: SOCKET DEBUG INFO:\n"));
    DT_DBG(("sock_debug_dump: fd: %d  address family: %s\n",
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
            DT_DBG(( "address: %-16.16s  hostname: %s\n",
                    inet_ntoa(in), hostinfo->h_name));
        }
        else
        {
            DT_DBG (("address: %-16.16s  hostname: unresolved\n",
                    inet_ntoa(in)));
        }

        DT_DBG (("port: %d\n",
             ntohs(((struct sockaddr_in *)info->addr)->sin_port)));
    }
    /* This is not a socket, it must be a stream */
    else
    {
    }

    /* fini */
    return;

}

void DiaSocketTransport::StartTrHandleDeleteDelayTimer()
{
    int duration = TRANSPORT_DEL_DELAY_TIMER_VALUE;
    DIA_TIMER_CTXT timerCtxt;
    DT_DBG(("Delay transport delete for %d secs",duration));
    timerCtxt.timerType = TRANSPORT_DEL_DELAY_TIMER;
    timerCtxt.data.transportInfo.trHandle = this;
    ITS_SERIAL retransmissionTimer = TIMERS_StartTimer(DIASTACK_TQ_INST, duration, &timerCtxt, sizeof(DIA_TIMER_CTXT));
}

