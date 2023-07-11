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
 * LOG: $Log: dia_connector.cpp,v $
 * LOG: Revision 3.43.4.5.4.12.2.1.2.4.4.1.8.4  2015/02/17 06:22:44  jkchaitanya
 * LOG: changes for peer down crash ported from stack branch for bugs 5507, 6067
 * LOG:
 * LOG: Revision 3.43.4.5.4.12.2.1.2.4.4.1.8.3  2014/12/17 05:19:08  jkchaitanya
 * LOG: changes to revert back the server down crash changes
 * LOG:
 * LOG: Revision 3.43.4.5.4.12.2.1.2.4.4.1  2014/03/07 06:41:50  jvikram
 * LOG: BUGID=3286 Invalid Read Fixes
 * LOG:
 * LOG: Revision 3.43.4.5.4.12.2.1.2.4  2014/01/06 09:22:32  cprem
 * LOG: Changes in diameter stack to support session replication. Review request 1611.
 * LOG:
 * LOG: Revision 3.43.4.5.4.12.2.1.2.3  2013/12/09 04:52:26  ncshivakumar
 * LOG: Fixed bug 2439,2443,2368,1898
 * LOG:
 * LOG: Revision 3.43.4.5.4.12.2.1.2.2  2013/10/26 07:42:21  ncshivakumar
 * LOG: RFC 6733 changes
 * LOG:
 * LOG: Revision 3.43.4.5.4.12.2.1.2.1  2013/09/10 08:36:39  ncshivakumar
 * LOG: RFC6733 Changes
 * LOG:
 * LOG: Revision 3.43.4.5.4.12.2.1  2013/07/01 07:35:15  nazad
 * LOG: changes for memory Leak, Review Request 1041
 * LOG:
 * LOG: Revision 3.43.4.5.4.12  2013/04/18 13:17:15  millayaraja
 * LOG: updated peer transport stats
 * LOG:
 * LOG: Revision 3.43.4.5.4.11  2013/04/12 04:16:25  vsarath
 * LOG: Logs improvement
 * LOG:
 * LOG: Revision 3.43.4.5.4.10  2013/04/09 07:21:51  ncshivakumar
 * LOG: Used proper socket data structure for tcp ipv6 connection
 * LOG:
 * LOG: Revision 3.43.4.5.4.9  2013/04/07 03:54:21  cprem
 * LOG: Changes made to fix HA bugs. Review Request 784
 * LOG:
 * LOG: Revision 3.43.4.5.4.8  2013/03/22 06:33:33  pramana
 * LOG: Changes for HA feature
 * LOG:
 * LOG: Revision 3.43.4.5.4.7  2013/03/21 12:35:26  ncshivakumar
 * LOG: Added checks for validating whether dre is having TCP listeners or not in the case of while connecting to TCP peer
 * LOG:
 * LOG: Revision 3.43.4.5.4.6  2013/03/07 05:50:11  ncshivakumar
 * LOG: fixed crash when configued transport type TCP for DRE.
 * LOG:
 * LOG: Revision 3.43.4.5.4.5  2013/03/06 06:10:17  ncshivakumar
 * LOG: Updated for multihoming
 * LOG:
 * LOG: Revision 3.43.4.5.4.4  2013/03/05 10:38:01  ncshivakumar
 * LOG: Updated for multihoming
 * LOG:
 * LOG: Revision 3.43.4.5.4.3  2013/03/05 06:53:06  ncshivakumar
 * LOG: Multihome changes
 * LOG:
 * LOG: Revision 3.43.4.5.4.2  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.43.4.5.4.1  2013/02/25 13:16:24  mallikarjun
 * LOG: Bug 623 changes
 * LOG:
 * LOG: Revision 3.43.4.5  2013/01/15 12:00:50  cprem
 * LOG: Fixed bug 932 where Connection closure stats were updated wrongly
 * LOG:
 * LOG: Revision 3.43.4.4  2013/01/15 09:45:48  rgovardhan
 * LOG: Peer Table Mutex Lock Issue Fix
 * LOG:
 * LOG: Revision 3.43.4.3  2013/01/11 07:18:23  rgovardhan
 * LOG: Release Mutex on Exceptions - Bugs 819, 916
 * LOG:
 * LOG: Revision 3.43.4.2  2012/11/20 17:39:44  pramana
 * LOG: Merged from CMAPI branch for 212-07 release
 * LOG:
 * LOG: Revision 3.43.4.1.8.3  2012/11/19 08:35:52  millayaraja
 * LOG: modified for Transport Stats
 * LOG:
 * LOG: Revision 3.43.4.1.8.2  2012/11/15 03:17:17  millayaraja
 * LOG: updated for peer stack stats
 * LOG:
 * LOG: Revision 3.43.4.1.8.1  2012/11/14 08:32:30  millayaraja
 * LOG: modified to accomdate Peer stack stats
 * LOG:
 * LOG: Revision 3.43.4.1  2012/10/19 17:54:43  brajappa
 * LOG: BugId 15: IPv6 support enhancements
 * LOG:
 * LOG: Revision 3.43  2011/08/23 04:11:19  vkumara
 * LOG: DataToInt is being changed to DataToUInt.
 * LOG: To fix CmdCode decode error for an unsigned values from abnf.
 * LOG: (Extra FF was returning from existing DataToInt ()).
 * LOG:
 * LOG: Revision 3.42  2011/07/14 14:04:51  vkumara
 * LOG: ForceDisconnect Requirement - Not to initiate connection.
 * LOG:
 * LOG: Revision 3.41  2011/07/04 09:17:20  nvijikumar
 * LOG: Fix for disabling connection initiation issue.
 * LOG: Connection initiation flag is checked before starting RETRY timer
 * LOG:
 * LOG: Revision 3.40  2011/06/28 08:09:51  rajeshak
 * LOG: Motorola (PSG) ForceDisconnect Issue
 * LOG:
 * LOG: Revision 3.39  2010/12/14 00:40:47  nvijikumar
 * LOG: 1. DO_NOT_WANT_TO_TALK_TO_YOU disc cause implimentation
 * LOG: 2. SCTP Sock read failure
 * LOG:
 * LOG: Revision 3.38  2010/11/04 07:19:47  vkumara
 * LOG: port number is not required
 * LOG:
 * LOG: Revision 3.37  2010/11/03 12:54:24  vkumara
 * LOG: DSCP support for IPV6
 * LOG:
 * LOG: Revision 3.36  2010/10/12 09:03:38  rajeshak
 * LOG: Initialize port before bind
 * LOG:
 * LOG: Revision 3.35  2010/10/11 07:57:26  rajeshak
 * LOG: Solaris IPV6 Support
 * LOG:
 * LOG: Revision 3.34  2010/08/27 12:28:12  nvijikumar
 * LOG: DSCP value support (IP header) - Vasanth
 * LOG:
 * LOG: Revision 3.33  2010/08/19 11:21:26  nvijikumar
 * LOG: Porting changes from B-MOTO-IDIA-0421-00
 * LOG: 1. New Overload implimentation changes are not being ported.
 * LOG: 2. Force disconnect changes are not being ported.
 * LOG:
 * LOG: Revision 3.32.2.7  2010/07/15 13:02:26  rajeshak
 * LOG: Fix for HelpDesk Ticket-2395
 * LOG:
 * LOG: Revision 3.32.2.6  2010/05/11 05:43:30  rajeshak
 * LOG: Porting the changes from 4.2.1 Patch branch to Moto branch
 * LOG: (Releasing the mutex before Connect after changing the peer state)
 * LOG:
 * LOG: Revision 3.32.2.5  2010/03/17 02:12:15  rajeshak
 * LOG: ForceDisconnect Changes.
 * LOG: 1. Raise an alarm (15011) if peer is moved to closed state after
 * LOG: executing ForceDisconnect.
 * LOG: 2. Stop initiating connection after forceDisconnect.
 * LOG:
 * LOG: Revision 3.32.2.4  2010/03/12 06:51:19  rajeshak
 * LOG: Added check to handle connect returning success for invalid sockets.
 * LOG:
 * LOG: Revision 3.32.2.3  2010/02/25 03:05:18  rajeshak
 * LOG: Starting retry timer in SendCER failed --> Closed state.
 * LOG:
 * LOG: Revision 3.32.2.2  2010/02/19 06:56:23  rajeshak
 * LOG: Removed Stoping of expiry timer. Expiry Timeout will move the peer to
 * LOG: Closed state.
 * LOG:
 * LOG: Revision 3.32.2.1  2010/02/19 03:02:42  rajeshak
 * LOG: Fix for HelpDesk Ticket 2313 & 2297.
 * LOG: (Coredump after executing forceDisconnect cmd)
 * LOG:
 * LOG: Revision 3.32  2009/09/11 09:31:02  rajeshak
 * LOG: Reduced the micro seconds sleep to fix CER Initiation timer Issue.
 * LOG:
 * LOG: Revision 3.31  2009/09/10 13:56:48  rajeshak
 * LOG: Fixed a bug in Reader Thread.
 * LOG:
 * LOG: Revision 3.30  2009/09/07 06:23:10  rajeshak
 * LOG: Introduced micro second sleep instead of 1sec sleep
 * LOG:
 * LOG: Revision 3.29  2009/07/01 11:20:44  nvijikumar
 * LOG: Fix for RETRY timer issue (CER is not initiated properly)
 * LOG:
 * LOG: Revision 3.28  2009/06/29 14:52:26  rajeshak
 * LOG: HMI Changes to improve the performance.
 * LOG:
 * LOG: Revision 3.27  2009/05/12 08:42:31  rajeshak
 * LOG: Klockwork reported Issue fix.
 * LOG:
 * LOG: Revision 3.26  2009/04/17 09:31:05  rajeshak
 * LOG: Fix for Issue:1818. (Core dump due to multiple thread accessing the
 * LOG: trTable peerEntry List)
 * LOG: Provided a lock-unlock function.
 * LOG:
 * LOG: Revision 3.25  2009/04/10 06:36:11  sureshj
 * LOG: Removed compilation flag HMI_ENABLE & added dynamic configuration option.
 * LOG:
 * LOG: Revision 3.24  2009/04/07 13:54:37  sureshj
 * LOG: HMI Monitoring is enabled for DiaConnector thread.
 * LOG:
 * LOG: Revision 3.23  2009/03/19 13:31:54  sureshj
 * LOG: DIA_VERSION check added
 * LOG:
 * LOG: Revision 3.22  2009/03/19 12:42:34  nvijikumar
 * LOG: Global instance is created for the Class ITSDiaConfig to avoid function
 * LOG: call overhead as ITSDiaConfig::GetITSDiaConfig() was called max time
 * LOG:
 * LOG: Revision 3.21  2009/03/19 11:17:30  chandrashekharbs
 * LOG: Changes for IPV6 SCTP support
 * LOG:
 * LOG: Revision 3.20  2009/03/19 08:07:04  nvijikumar
 * LOG: Reverting back HMI changes (App hangs and drop in TPS)
 * LOG:
 * LOG: Revision 3.19  2009/03/16 11:22:26  sureshj
 * LOG: FeatureId: HMI Enhancement for monitoring raw threads.
 * LOG: Description: connector thread added for HMI monitoring.
 * LOG:
 * LOG: Revision 3.18  2009/03/03 06:55:44  chandrashekharbs
 * LOG: Changes for IPV6 TCP support
 * LOG:
 * LOG: Revision 3.17  2009/02/06 09:32:53  nvijikumar
 * LOG: Enhancement in tracing
 * LOG:
 * LOG: Revision 3.16  2009/02/05 13:51:01  rajeshak
 * LOG: Fix for Issue:1476.
 * LOG: After Initiating a connection, initiate flag is not cleared.
 * LOG:
 * LOG: Revision 3.15  2009/02/04 05:49:58  nvijikumar
 * LOG: Changes for 64 Peer support with fixed number of threads
 * LOG: 1. One thread for accepting connections and other for initiate connections
 * LOG: 2. One thread to Read from I-Connections and other for R-Connections
 * LOG:
 * LOG: Revision 3.14  2009/02/02 06:43:44  rajeshak
 * LOG: Passing sctp config params in constructor
 * LOG:
 * LOG: Revision 3.13  2009/01/09 09:06:50  nvijikumar
 * LOG: Added Alarm for Decode failure and Receive failure
 * LOG:
 * LOG: Revision 3.12  2008/12/23 15:02:35  ssaxena
 * LOG: Fixes for Dynamic Peer Configuration issues (Yogesh, Shivendra)
 * LOG: Issue Id:1375 and some legacy issues
 * LOG:
 * LOG: Revision 3.11  2008/12/23 12:25:04  sureshj
 * LOG: E-bit check added before updating Statistics. Fix for issue 1379.
 * LOG:
 * LOG: Revision 3.10  2008/12/12 12:32:08  nvijikumar
 * LOG: Updated with statistic support
 * LOG:
 * LOG: Revision 3.9  2008/12/11 11:08:57  nvijikumar
 * LOG: Mutex not required as single thread does read from the socket
 * LOG:
 * LOG: Revision 3.8  2008/11/26 12:03:28  nvijikumar
 * LOG: Local IP binding for Client Sockets
 * LOG:
 * LOG: Revision 3.7  2008/10/31 05:48:30  nvijikumar
 * LOG: IssueID:1189
 * LOG: FeatureID:none
 * LOG: Description: Code Optimization
 * LOG:
 * LOG: Revision 3.6  2008/10/28 12:06:28  nvijikumar
 * LOG: IssueID: none
 * LOG: FeatureID: none
 * LOG: Description: Porting Performance changes from 3.0 branch
 * LOG:
 * LOG: Revision 3.5  2008/09/09 10:13:54  sureshj
 * LOG: Propagated fix for BW issue 2006 from 2.1.
 * LOG:
 * LOG: Revision 3.4  2008/09/05 10:14:52  nvijikumar
 * LOG: Fix for PBN ID:1089
 * LOG: Deleted thr, but peerEntry refence not made as NULL
 * LOG:
 * LOG: Revision 3.3  2008/07/09 10:50:11  vnarang
 * LOG: Adding a check for TLS_ENABLED flag during compilation
 * LOG:
 * LOG: Revision 3.2  2008/06/13 11:24:38  hbhatnagar
 * LOG: Added code to implement the TLS feature. Modified the Read and Write
 * LOG: for the sockets
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.19  2008/03/27 12:14:08  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.17.2.12  2008/01/10 14:50:11  hbhatnagar
 * LOG: Changes made to provide fix for the issue no 29 raised by Dhiranand.
 * LOG:
 * LOG: Revision 2.17.2.11  2008/01/07 20:16:01  hbhatnagar
 * LOG: If in case of WAIT-CONN-NACK if _doExit is set do not
 * LOG: reconnect.
 * LOG:
 * LOG: Revision 2.17.2.10  2008/01/07 18:03:25  hbhatnagar
 * LOG: Changes made to provide fix for various issues 20,22 and 23
 * LOG: calling SetExit() API in place of _doExit = ITS_TRUE.
 * LOG:
 * LOG: Revision 2.17.2.9  2008/01/07 15:18:50  avinashks
 * LOG: Added some debug prints for clarity.
 * LOG:
 * LOG: Revision 2.17.2.8  2008/01/07 13:22:50  avinashks
 * LOG: Fix for Issue No.17 raised by Dhirananda during
 * LOG: validation of BCGI ticket 1807.
 * LOG:
 * LOG: Revision 2.17.2.7  2007/12/14 11:24:48  hbhatnagar
 * LOG: Removed the DeviceWatchDog Timer related functionality and added
 * LOG: WatchDog Transport Thread related functionality.
 * LOG:
 * LOG: Revision 2.17.2.6  2007/11/22 14:23:19  hbhatnagar
 * LOG: Rollback the changes in EstablishCommunication() to previous revision.
 * LOG:
 * LOG: Revision 2.17.2.5  2007/11/14 17:17:13  hbhatnagar
 * LOG: Starting Retry Timer in case of failure in Execute(), also removing the
 * LOG: second call of EstablishCommunication() call.
 * LOG:
 * LOG: Revision 2.17.2.4  2007/09/25 09:51:39  hbhatnagar
 * LOG: Acquired Mutex for StartTimer in HandleMessage to solve DWTimeout issue.
 * LOG:
 * LOG: Revision 2.17.2.3  2007/05/28 14:03:29  nvijikumar
 * LOG: Return Error Response if request message failed to decode.
 * LOG:
 * LOG: Revision 2.17.2.2  2007/05/25 04:16:50  nvijikumar
 * LOG: Removed commentted Code.
 * LOG:
 * LOG: Revision 2.17.2.1  2007/05/25 04:13:01  nvijikumar
 * LOG: Decode Base protocol Messages to BaseGenericCmd, this commad will be
 * LOG: converted to Base specific command in the peer SM.
 * LOG:
 * LOG: Revision 2.17  2007/02/17 07:26:33  nanaparthi
 * LOG: Fix for Follwing issue (Bug 5237)
 * LOG:  On non-redundant static setup with SCTP transport if you kill the client
 * LOG:  abnormally on peer side trace prints Exception Caught: CodecException ,
 * LOG:  Error Cause: Wrong Command Header length
 * LOG:
 * LOG: Revision 2.16  2007/01/19 11:08:17  nvijikumar
 * LOG: Moved Start RETRY timer to Peer SM after getting PEER_DISC indication event.
 * LOG:
 * LOG: Revision 2.15  2007/01/16 07:20:55  nvijikumar
 * LOG: Unset _ifMarkedDown after re establishing the connectivity.
 * LOG:
 * LOG: Revision 2.14  2007/01/04 14:11:08  nvijikumar
 * LOG: Call respected platform API for SCTP Multihoming.
 * LOG:
 * LOG: Revision 2.13  2007/01/04 13:44:17  nvijikumar
 * LOG: Enabled SCTP Multihoming only for Linux. Avoid compilation error from solaris.
 * LOG:
 * LOG: Revision 2.12  2006/12/29 06:56:18  nanaparthi
 * LOG: SCTP Multihoming related changes (baseline code base)
 * LOG:
 * LOG: Revision 2.11  2006/12/19 13:50:05  nvijikumar
 * LOG: Fix for BUG ID 5073 ( Retry after abnormal exit).
 * LOG:
 * LOG: Revision 2.10  2006/12/17 03:34:44  tpanda
 * LOG: Fix for bug# 5067 and default route handling
 * LOG:
 * LOG: Revision 2.9  2006/12/11 13:51:25  tpanda
 * LOG: REDUNDANCY_SLOT_CHANGES are removed and code seems to be stable
 * LOG:
 * LOG: Revision 2.8  2006/12/10 13:42:42  tpanda
 * LOG: Redundancy Bug Fixes and enhancements--Transport Order Fix
 * LOG:
 * LOG: Revision 2.7  2006/10/30 15:59:59  yranade
 * LOG: Exception Handling.
 * LOG:
 * LOG: Revision 2.6  2006/10/25 12:50:55  yranade
 * LOG: 1. Updated traces a bit.
 * LOG: 2. Solve a tricky issue, when CER received from Unknown peer.
 * LOG:
 * LOG: Revision 2.5  2006/10/24 13:43:08  yranade
 * LOG: Print host and port details when trying to reconnect.
 * LOG:
 * LOG: Revision 2.4  2006/10/16 16:01:17  yranade
 * LOG: Exit in case of SM failure.
 * LOG:
 * LOG: Revision 2.3  2006/10/12 14:13:41  yranade
 * LOG: Finish up Device Watchdog handling. Bug Fix: 4464
 * LOG:
 * LOG: Revision 2.2  2006/10/05 13:21:54  yranade
 * LOG: Getting there.
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:44  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:29  yranade
 * LOG: Initial Version of ITS-Diameter (Yogesh, Viji, Tushar)
 * LOG:
 * ID: $Id: dia_connector.cpp,v 3.43.4.5.4.12.2.1.2.4.4.1.8.4 2015/02/17 06:22:44 jkchaitanya Exp $
 ****************************************************************************/
#ident "$Id: dia_connector.cpp,v 3.43.4.5.4.12.2.1.2.4.4.1.8.4 2015/02/17 06:22:44 jkchaitanya Exp $"

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
#include <dia_trace.h>
#include <dia_utils.h>
#include <dia_connector.h>
#include <dia_peer_fsm.h>
#include <dia_peer_table.h>
#include <dia_msg_router.h>
#include <its_dia_config.h>
#include <dia_stack_statistics.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/sctp.h>
#include <dia_capabilities_update_application.h>
#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
#endif

#define REQUEST_BIT_SET(x)      (x & 0x80)
#define PROXY_BIT_SET(x)        (x & 0x40)
#define ERROR_BIT_SET(x)        (x & 0x20)
#define RETRANSMIT_BIT_SET(x)   (x & 0x10)

#if !defined(linux) || defined(USE_SELECT)
DiaSelectSockContainer connSelectTbl;
#else
DiaEpollSockContainer  connEpollTbl;
#endif


int
DiaConnector::Bind(bool isIPv6)
{

    ITS_SocketInfo *info = GetSocket()->GetSocketInfo();
    ITSDiaConfig *cfg = &itsDiaConfig;

    if (cfg->GetLocalIpAddr() == NULL)
    {
        return !ITS_SUCCESS;
    }
    if(GetType() == ITS_DIA_SCTP_CLIENT_SOCK_TRANS)
    {
        int noIPsPassed = 0;
        if(isIPv6)
        {
            struct sockaddr_in6 connectingSocket[MAX_IP_ADDRS];
            memset(connectingSocket, 0, sizeof(sockaddr_in6) * MAX_IP_ADDRS);
            for (noIPsPassed = 0;noIPsPassed < noIPV6IPs;noIPsPassed++)
            {
                connectingSocket[noIPsPassed].sin6_family = AF_INET6;
                connectingSocket[noIPsPassed].sin6_port = 0;
                if ( inet_pton(AF_INET6, ipv6AddrsToUseInBind[noIPsPassed],
                                &(connectingSocket[noIPsPassed].sin6_addr)) == 0 )
                {
                    return (ITS_EBADHOST);
                }
            }
            if (sctp_bindx(info->socket,
                          (sockaddr *)connectingSocket,
                          noIPsPassed,
                          SCTP_BINDX_ADD_ADDR) < 0)
            {
                DT_ERR(("bind failed.errno = %d.",errno));
                return (!ITS_SUCCESS);
            }

        }
        else
        {
            struct sockaddr_in connectingSocket[MAX_IP_ADDRS];
            memset(connectingSocket, 0, sizeof(sockaddr_in)*MAX_IP_ADDRS);
            for (noIPsPassed =0;noIPsPassed < noIPV4IPs;noIPsPassed++)
            {
                connectingSocket[noIPsPassed].sin_family = AF_INET;
                connectingSocket[noIPsPassed].sin_port = 0;
                connectingSocket[noIPsPassed].sin_addr.s_addr = inet_addr(ipv4AddrsToUseInBind[noIPsPassed]);
            }
            if (sctp_bindx(info->socket,
                          (sockaddr *)connectingSocket,
                          noIPsPassed,
                          SCTP_BINDX_ADD_ADDR) < 0)
            {
                DT_ERR(("bind failed.errno = %d.",errno));
                return (!ITS_SUCCESS);
            }
        }

    }
    else
    {
        int aSize;
        /* Buil sock addr */
        if(isIPv6)
        {
            struct sockaddr_in6 sin6;
            //Initializing - Uninitialized Scalar Value sin_zero of sin
            memset(&sin6, 0, sizeof(sin6));
            aSize = sizeof(struct sockaddr_in6);
            sin6.sin6_port = 0;

            if(TCPIPV6addrs!=NULL)
            {
               sin6.sin6_family = AF_INET6;
               if (inet_pton(AF_INET6, TCPIPV6addrs, &sin6.sin6_addr) == 0)
               {
                   return (ITS_EBADHOST);
               }

            }
            else
            {
               DT_ERR(("Dont have IPV6 TCP Listener.Pls configure"));
               return (!ITS_SUCCESS);
            }
            if(bind(info->socket,(sockaddr *)&sin6,(socklen_t)aSize) < 0)
            {
                DT_ERR(("DiaSockBind:: bind failed IP =%s  errno = %d\n",
                        TCPIPV6addrs, errno));
                return !ITS_SUCCESS;
            }

        }
        else
        {
            struct sockaddr_in sin;
            //Initializing - Uninitialized Scalar Value sin_zero of sin
            memset(&sin, 0, sizeof(sin));
            aSize = sizeof(struct sockaddr_in);
            sin.sin_port = 0;
            if(TCPIPV4addrs!=NULL)
            {
               sin.sin_family = AF_INET;
               sin.sin_addr.s_addr = inet_addr(TCPIPV4addrs);
            }
            else
            {
               DT_ERR(("Dont have IPV4 TCP Listener.Pls configure"));
               return (!ITS_SUCCESS);
            }
            if(bind(info->socket,(sockaddr *)&sin,(socklen_t)aSize) < 0)
            {
                DT_ERR(("DiaSockBind:: bind failed IP =%s  errno = %d\n",
                        TCPIPV4addrs, errno));
                return !ITS_SUCCESS;
            }

        }
    }
    return ITS_SUCCESS;
}

int
DiaConnector::Connect()
{
   its::Socket *_socket = GetSocket();
   PEER_ENTRY *entry = GetPeer();
   ITS_INT dscp = 0;
   bool isIPv6 = (_socket->GetSocketInfo()->af == AF_INET6);

   /* Socket Bind */
   if (Bind(isIPv6) != ITS_SUCCESS)
   {
        DT_ERR(("Client socket bind failed\n"));
        //Increment statistics counter for bind fail
        DIA_INC_PEER_CONNECTION_SOCKET_BIND_FAIL_COUNT(entry);
        return (!ITS_SUCCESS);
   }
   else
   {
        //Increment statistics counter for bind success
        DIA_INC_PEER_CONNECTION_SOCKET_BIND_SUCCESS_COUNT(entry);
   }


   if(GetType() == ITS_DIA_CLIENT_SOCK_TRANS)
   {
        if (isIPv6 == true)
        {
            return ((its::ClientSocket *)_socket)->Connect_Ipv6();
        }
        else
        {
            return ((its::ClientSocket *)_socket)->Connect(itsDiaConfig.GetTcpSocketConfig());
        }
   }
   else if(GetType() == ITS_DIA_SCTP_CLIENT_SOCK_TRANS)  // SCTP MultiHoming
   {
#if defined(linux)
        if (isIPv6 == true)
        {
            return ((its::LKSctpClientSocket *)_socket)->Connect_Ipv6();
        }
        else
        {
            return ((its::LKSctpClientSocket *)_socket)->Connect();
        }
#elif defined(solaris) || defined(solaris64)
        if (isIPv6 == true)
        {
            if( DIA_PE_DSCP_EN(entry) == ITS_TRUE )
            {
                dscp = DIA_PE_DSCP_VAL(entry);
            }
            return ((its::SKSctpClientSocket *)_socket)->Connect_Ipv6(dscp);
        }
        else
        {
            return ((its::SKSctpClientSocket *)_socket)->Connect();
        }
#endif
   }

   //Warning Fix - control reaches end of non-void function
   return (ITS_SUCCESS);
}

int
DiaConnector::EstablishCommunication()
{
    int ret;
    PEER_ENTRY *entry = GetPeer();
    if (entry != NULL)
    {

        ITS_USHORT index = DIA_PE_INDEX(entry);

        ret = Connect();     //TCP or SCTP

        if (trTable.GetPeer(index/4) == NULL)
        {
            DT_ERR(("Peer Already removed."));
            return (!ITS_SUCCESS);
        }

        if (ret != ITS_SUCCESS)
        {
            if ((ret = DiaMsgRouter::UpdatePeerSM(NULL, entry,
                                                PEER_EVT_I_RCV_CONN_NACK,
                                                trHandle, NULL)) == ITS_SUCCESS)
            {
                DT_DBG(("Succesfully Updated SM"));
            }
            else
            {
                DT_ERR(("Failed to Update State ret = %d", ret));
            }
            return (!ITS_SUCCESS);
        }

        if (trHandle->CheckIfMarkedDown())
        {
            DT_ERR(("Invalid Socket. Socket Marked down."));
            return (!ITS_SUCCESS);
        }

        DT_DBG(("DiaConnector: Succesfully Established Communication"));

        if (DIA_PE_STATE(entry) == PEER_ST_CLOSED)
        {
            DIA_PE_STATE(entry) = PEER_ST_WAIT_CONN_ACK;
            DT_DBG(("PeerFsm:: State::PEER_ST_WAIT_CONN_ACK"));
        }
        if (DIA_PE_DSCP_EN(entry) == ITS_TRUE)
        {
            GetSocket()->SetDscpMarking(DIA_PE_DSCP_VAL(entry));
        }
        DIA_PE_CONN_SPECS(entry).trHandle = trHandle;
        if ((ret = DiaMsgRouter::UpdatePeerSM(NULL, entry,
                                              PEER_EVT_I_RCV_CONN_ACK,
                                              trHandle, NULL)) == ITS_SUCCESS)
        {
            DT_DBG(("Succesfully Updated SM"));

            /**
             * In Case of Win Election on Connector, if the state is
             * is R-Open we should not change the Peer State machine
             * Handle and Instance. Fix for issue no 29 raised by
             * Dhiranand.
             */
            if (DIA_PE_STATE(entry) != PEER_ST_R_OPEN)
            {
                DIA_PE_HANDLE(entry) = trHandle;
                DIA_PE_INST(entry) = this->GetInstance();
            }
            trTable.addAt(GetInstance(), trHandle);

            /**
             * If the Connector specs handle is Null update Connector
             * specs with current thread's handle and Instance.
             */
            if (DIA_PE_CONN_SPECS(entry).trHandle == NULL)
            {
                DIA_PE_CONN_SPECS(entry).trHandle = trHandle;
                DIA_PE_CONN_SPECS(entry).trInst = this->GetInstance();

            }

            /* if marked down previously, unset this flag */
            trHandle->_ifMarkedDown        = false;
        }
        else
        {
            DT_ERR(("Failed to Update State = %d", ret));
            /* Fix for PBN Id:1089 */
            DIA_PE_CONN_SPECS(entry).trHandle = NULL;
            DIA_PE_CONN_SPECS(entry).trInst = 0;
            return !ITS_SUCCESS;
        }
    }
    else
    {
        DT_ERR(("Failed to Find Entry for Peer"));
        return !ITS_SUCCESS;
    }
    return (ITS_SUCCESS);
}

void
DiaConnector::InitConnections()
{
    HMIThread_Info* hmiInfo = NULL;
    int ret;
    PEER_ENTRY *entry = NULL;
    ITSDiaConfig *cfg = &itsDiaConfig;
    ITS_INT thrID = THREAD_GetCurrentThreadID();

    bool isPeerSlotLocked = false;

    hmiInfo = HMI_AddToMonList(&monList, "DiaConnector", (ITS_THREAD*)thrID);

    DT_DBG(("DiaConnector::InitConnections"));

    while (!_doExit)
    {
        ITSDiaConfig *cfg = &itsDiaConfig;
        if(cfg->IsHMIEnabled())
        {
            HMI_ResetCounter(hmiInfo);
        }
        //Check if we are Activated and then only connect to Peers.
        if(!m_bDeActivated)
        {
            for (int i=0; (i < MAX_PEER_CONNS) && (!m_bDeActivated); i++)
            {
                if(cfg->IsHMIEnabled())
                {
                    HMI_ResetCounter(hmiInfo);
                }

                trTable.LockPeerSlot();
                isPeerSlotLocked = true;
                entry = trTable.GetPeer(i);

                if (entry == NULL)
                {
                    trTable.UnlockPeerSlot();
                    isPeerSlotLocked = false;
                    continue;
                }

                if (entry &&
                        (DIA_PE_STATE(entry) == PEER_ST_I_OPEN ||
                         DIA_PE_STATE(entry) == PEER_ST_R_OPEN ||
                         !DIA_PE_INIT_CONN(entry) ||
                         DIA_PE_IS_FORCE_DISCONNECTED(entry)))
                {
                    trTable.UnlockPeerSlot();
                    isPeerSlotLocked = false;
                    continue;
                }

                ITS_SERIAL tc = DIA_PE_RETRY_TIME_VAL(entry);
                if(DIA_PE_DISCONNECT_CAUSE_SUPPORT(entry))
                {
                    if(DIA_PEER_GET_DIS_CAUSE(entry)== DisconnectCause::DO_NOT_WANT_TO_TALK_TO_YOU)
                    {
                        tc = DIA_PE_DO_NOT_WANT_TO_TALK_TO_YOU_RECONNECT_TIMER(entry);
                    }
                    else if(DIA_PEER_GET_DIS_CAUSE(entry)== DisconnectCause::BUSY)
                    {
                        tc = DIA_PE_BUSY_RECONNECT_TIMER(entry);
                    }

                }

                if (DIA_PE_INIT_COUNT(entry) != 0 &&
                        DIA_PE_INIT_COUNT(entry) < tc*2)
                {
                    DIA_PE_INIT_COUNT(entry)++;
                    trTable.UnlockPeerSlot();
                    isPeerSlotLocked = false;
                    continue;
                }

                /* Let the count start from here */
                DIA_PE_INIT_COUNT(entry) = 1;
                ITS_USHORT index = DIA_PE_INDEX(entry);
                const char *realm = DIA_PE_REALM(entry);
                ITS_USHORT trInstance = DIA_PE_INST(entry);
                for(int j =0;(j < DIA_PE_CONN_TRANS_COUNT(entry)) && (!m_bDeActivated) ;j++)
                {
                    int type = DIA_PE_CONN_SPECS(entry).tInfo[j].type;
                    const char *ip = DIA_PE_CONN_SPECS(entry).tInfo[j].serverIpAddr;
                    ITS_USHORT port = 0;
                    if(DIA_PE_CONN_SPECS(entry).tInfo[j].securePort)
                    {
                        if(DIA_PE_TLS_EN(entry))
                        {
                            port = DIA_PE_CONN_SPECS(entry).tInfo[j].securePort;
                        }
                        else
                        {
                            DT_ERR(("TLS not enabled for Peer %s so not trying connection to secure port",
                                     DIA_PE_HOST(entry)));
                             trTable.UnlockPeerSlot();
                             isPeerSlotLocked = false;
                            continue;
                        }
                    }
                    else
                    {
                        port = DIA_PE_CONN_SPECS(entry).tInfo[j].portNo;
                    }
                    DT_DBG(("Connecting to port %d and transport %s for peer %s",
                    port,DIA_TRANS_TYPE_TO_TEXT(type),DIA_PE_HOST(entry)));
                    DIA_PE_CONN_SPECS(entry).currentTinfoIndex = j;


                    const char **multiHomeipaddrs =
                        DIA_PE_CONN_SPECS(entry).tInfo[j].multiHomeipaddrs;
                    ITS_USHORT noIPs = DIA_PE_CONN_SPECS(entry).tInfo[j].noIPs;

                    if ((trInstance % 4) == 2)
                    {
                        trInstance -=1;
                    }
                    DiaPeerSockTransport *connect = NULL;
                    its::Socket *conSocket = NULL;

                    try
                    {
                        if (type == ITS_DIA_T_TCP)
                        {
                            connect =
                                new DiaPeerSockTransport(ITS_DIA_CLIENT_SOCK_TRANS, index);

                            if (connect)
                            {
                                //Increment counter for number of connection attemts
                                //count
                                DIA_INC_PEER_CONNECTION_ATTEMPTED_COUNT(entry);
                                if (connect->Initialize(ip, port) == ITS_SUCCESS)
                                {
                                    /* IMP keep the valid reference for trHandle*/
                                    trHandle = connect;
                                    connect->SetPeer(entry);

                                    if (!SetSocketFd())
                                    {
                                        //Increment the statistics counter for connection
                                        //Failure
                                        DIA_INC_PEER_CONNECTION_CONNECTION_FAILED_COUNT(entry);
                                        if (connect != NULL)
                                        {
                                            delete connect;
                                            connect = NULL;
                                        }
                                        trTable.UnlockPeerSlot();
                                        isPeerSlotLocked = false;
                                        continue;
                                    }

                                    if ((ret = DiaMsgRouter::UpdatePeerSM(NULL, entry,
                                                    PEER_EVT_START, trHandle, NULL)) == ITS_SUCCESS)
                                    {
                                        DT_DBG(("Succesfully Updated SM"));
                                    }
                                    else
                                    {
                                        DT_ERR(("Failed to Update State = %d", ret));
                                    }

                                    /* Releasing the mutex after changing the state
                                     * In intermediate state peer cannot be removed so
                                     * its ok to release the mutex
                                     */
                                    trTable.UnlockPeerSlot();
                                    isPeerSlotLocked = false;

                                    if (EstablishCommunication() != ITS_SUCCESS)
                                    {
                                        DT_ERR(("Failed to connect to Peer = %s",
                                                    DIA_PE_HOST(entry)));

                                        if (connect != NULL)
                                        {
                                            DIA_PE_CONN_SPECS(entry).trHandle = NULL;
                                            trTable.addAt(GetInstance(), NULL);
                                            delete connect;
                                            connect = NULL;
                                        }
                                        //Increment the statistics counter for connection
                                        //Failure
                                        DIA_INC_PEER_CONNECTION_CONNECTION_FAILED_COUNT(entry);
                                        /* trTable.UnlockPeerSlot(); */
                                        continue;
                                    }
#if !defined(linux) || defined(USE_SELECT)
                                    ret = connSelectTbl.SetSelectSock(connect);
#else
                                    ret = connEpollTbl.SetEpollSock(connect);
#endif

                                    if (ret  != ITS_SUCCESS)
                                    {
                                        DT_ERR(("Error establishCommunication while Setting fdset"));
                                        if (connect != NULL)
                                        {
                                            delete connect;
                                            connect = NULL;
                                        }
                                        //Increment the statistics counter for connection
                                        //Failure
                                        DIA_INC_PEER_CONNECTION_CONNECTION_FAILED_COUNT(entry);
                                        /* trTable.UnlockPeerSlot(); */
                                        continue;
                                    }
                                    //Increment the statistics counter for connection
                                    //success
                                    DIA_INC_PEER_CONNECTION_CONNECTION_SUCCESS_COUNT(entry);

                                    DIA_PE_CONN_SPECS(entry).trHandle = connect;
                                    DIA_PE_CONN_SPECS(entry).trInst = connect->GetInstance();
                                    DIA_PE_INIT_CONN(entry) = false;
                                    DIA_PE_INIT_COUNT(entry) = 0;
                                }
                                else
                                {
                                    //Increment the statistics counter for connection
                                    //Failure
                                    DIA_INC_PEER_CONNECTION_CONNECTION_FAILED_COUNT(entry);
                                }
                            }
                        }
                        else if (type == ITS_DIA_T_SCTP)
                        {
                            connect = new
                                DiaPeerSockTransport(ITS_DIA_SCTP_CLIENT_SOCK_TRANS, index);

                            if (connect)
                            {
                                //Increment counter for number of connection attemts
                                //count
                                DIA_INC_PEER_CONNECTION_ATTEMPTED_COUNT(entry);
                                if (connect->Initialize(ip, port,multiHomeipaddrs, noIPs)
                                        == ITS_SUCCESS)
                                {
                                    /* IMP keep the valid reference for trHandle*/
                                    trHandle = connect;
                                    (connect)->SetPeer(entry);

                                    if (!SetSocketFd())
                                    {
                                        if (connect != NULL)
                                        {
                                            delete connect;
                                            connect = NULL;
                                        }
                                        //Increment the statistics counter for connection
                                        //Failure
                                        DIA_INC_PEER_CONNECTION_CONNECTION_FAILED_COUNT(entry);

                                        trTable.UnlockPeerSlot();
                                        isPeerSlotLocked = false;
                                        continue;
                                    }

                                    if ((ret = DiaMsgRouter::UpdatePeerSM(NULL, entry,
                                                    PEER_EVT_START, trHandle, NULL)) == ITS_SUCCESS)
                                    {
                                        DT_DBG(("Succesfully Updated SM"));
                                    }
                                    else
                                    {
                                        DT_ERR(("Failed to Update State = %d", ret));
                                    }

                                    /* Releasing the mutex after changing the state
                                     * In intermediate state peer cannot be removed so
                                     * its ok to release the mutex
                                     */
                                    trTable.UnlockPeerSlot();
                                    isPeerSlotLocked = false;

                                    if (EstablishCommunication() != ITS_SUCCESS)
                                    {
                                        DT_ERR(("Failed to connect to Peer = %s",
                                                    DIA_PE_HOST(entry)));

                                        if (connect != NULL)
                                        {
                                            DIA_PE_CONN_SPECS(entry).trHandle = NULL;
                                            trTable.addAt(GetInstance(), NULL);
                                            delete connect;
                                            connect = NULL;
                                        }
                                        //Increment the statistics counter for connection
                                        //Failure
                                        DIA_INC_PEER_CONNECTION_CONNECTION_FAILED_COUNT(entry);
                                        /* trTable.UnlockPeerSlot(); */
                                        continue;
                                    }
#if !defined(linux) || defined(USE_SELECT)
                                    ret = connSelectTbl.SetSelectSock(connect);
#else
                                    ret = connEpollTbl.SetEpollSock(connect);
#endif

                                    if (ret  != ITS_SUCCESS)
                                    {
                                        DT_ERR(("Error while Setting fdset"));
                                        if (connect)
                                        {
                                            delete connect;
                                            connect = NULL;
                                        }
                                        //Increment the statistics counter for connection
                                        //Failure
                                        DIA_INC_PEER_CONNECTION_CONNECTION_FAILED_COUNT(entry);
                                        /* trTable.UnlockPeerSlot(); */
                                        continue;
                                    }
                                    //Increment statistics counter for connection
                                    //Success
                                    DIA_INC_PEER_CONNECTION_CONNECTION_SUCCESS_COUNT(entry);

                                    DIA_PE_CONN_SPECS(entry).trHandle = connect;
                                    DIA_PE_CONN_SPECS(entry).trInst =connect->GetInstance();
                                    DIA_PE_INIT_CONN(entry) = false;
                                    DIA_PE_INIT_COUNT(entry) = 0;
                                }
                                else
                                {
                                    //Increment the statistics counter for connection
                                    //Failure
                                    DIA_INC_PEER_CONNECTION_CONNECTION_FAILED_COUNT(entry);
                                }
                            }
                        }
                    }
                    catch (...)
                    {
                        DT_ERR(("Failed to Initialize Connector:"));
                        if ( isPeerSlotLocked == true)
                        {
                            trTable.UnlockPeerSlot();
                            isPeerSlotLocked = false;
                            DT_DBG(("Peer Slot Lock Released "));
                        }

                        if (connect)
                        {
                            delete connect;
                            connect = NULL;
                        }
                    }
                    /* trTable.UnlockPeerSlot(); */
                    break;//Try connecting to other peer in the peer list
                }
            }
        }
        else
        {
            DT_WRN(("Connector DeActivated..hence not initiating Peer Transport Connections."));
        }
        //DiaUtils::HmiSleep(hmiInfo, tc);
        /**
         * Putting the timer sleep of 1 second
         */
        TIMERS_USleep(500000);
    }
    HMI_RemoveFromMonList(&monList, (ITS_THREAD*)thrID);
}


    void
DiaConnector::CopyIpAddresses()
{
    ITSDiaConfig *cfg = NULL;

    cfg = &itsDiaConfig;

    for (int i = 0; i < cfg->GetHostInfoList().count; i++)
    {

        for (int j = 0;
                j < cfg->GetHostInfoList().arr[i].transCnt;
                j++)
        {
            const char **multiHomeipaddrs = cfg->GetHostInfoList().
                arr[i].transList[j].multiHomeipaddrs;
            ITS_USHORT noIPs = cfg->GetHostInfoList().arr[i].transList[j].noIPs;
            int type = cfg->GetHostInfoList().arr[i].transList[j].type;

            if(type == ITS_DIA_T_TCP)
            {
                if(DiaUtils::IsIPv6Address(cfg->GetHostInfoList().arr[i].transList[j].serverIpAddr) == true)
                {
                    if(TCPIPV6addrs == NULL)
                    {
                        TCPIPV6addrs = strdup(cfg->GetHostInfoList().arr[i].transList[j].serverIpAddr);
                    }
                }
                else
                {
                    if(TCPIPV4addrs == NULL)
                    {
                        TCPIPV4addrs = strdup(cfg->GetHostInfoList().arr[i].transList[j].serverIpAddr);
                    }
                }
                continue;
            }
            for(int k = 0;k < noIPs; k++)
            {
                if(DiaUtils::IsIPv6Address(multiHomeipaddrs[k]) == true)
                {
                    bool isIPPresent = false;
                    int l = 0;
                    for(l = 0; l < noIPV6IPs; l++)
                    {
                        if(strcmp(ipv6AddrsToUseInBind[l],multiHomeipaddrs[k])==0)
                        {
                            isIPPresent = true;
                            break;
                        }
                    }
                    if(!isIPPresent)
                    {
                        ipv6AddrsToUseInBind[l] = strdup(multiHomeipaddrs[k]);
                        noIPV6IPs++;
                    }
                }
                else
                {
                    bool isIPPresent = false;
                    int l = 0;
                    for(l = 0; l < noIPV4IPs; l++)
                    {
                        if(strcmp(ipv4AddrsToUseInBind[l],multiHomeipaddrs[k])==0)
                        {
                            isIPPresent = true;
                            break;
                        }
                    }
                    if(!isIPPresent)
                    {
                        ipv4AddrsToUseInBind[l] = strdup(multiHomeipaddrs[k]);
                        noIPV4IPs++;
                    }
                }
            }
        }
    }
}


    void
DiaConnector::Execute(void *arg)
{
    InitConnections();
}

    int
DiaConnectorReader::HandleMessage(ITS_EVENT *event)
{
    int ret;
    ITS_OCTET cmdFlag = 0x0;
    ITS_UINT cmdCode = 0;

    PEER_ENTRY *entry = NULL;
    PEER_STATE_CTXT pCtxt;
    ITS_INT evtType;
    DIA_CMD *cmd = NULL;

    ITS_USHORT trInst = ITS_GET_CTXT(event->data);
    ITS_OCTET *msg = &event->data[sizeof(ITS_USHORT)];
    ITS_UINT msgLen = (event->len - sizeof(ITS_USHORT));

    cmdFlag = msg[4];
    ITS_OCTET versionNum = msg [0];

    PRINT_EVENT(event);

    /* Established Communication with the Peer
       I-Rcv-Conn-Ack --> SendCER-->Wait-I-CEA
       Lookup the Peer Table:
           Here we need to check the acceptor connection state also
           Peer election related things might happen here.
           SendCER
           Update the State Associated
    */

    cmdCode = DiaUtils::DataToUInt(&msg[5], (sizeof(ITS_UINT) - 1));
    DT_DBG(("Received Cmd = %d", cmdCode));

    if( versionNum != DIA_VERSION)
    {
         DT_WRN(("Invalid Version Number"));
         DIA_Alarm(15400, __FILE__, __LINE__, "InvalidVesion=%d:CommandCode=%d", versionNum, cmdCode);
    }

    if ((entry = this->GetPeer()) == NULL)
    {
        /* Fatal Error */
        DT_ERR(("Connector Without a Valid Peer...Shutting Down"));
        trHandle->SetExit();
        return (!ITS_SUCCESS);
    }

    try
    {
        switch (cmdCode)
        {
        case DIA_MSG_CE:
        {
            ret = DiaUtils::DecodeMsg(&cmd, msg, msgLen);
            if (cmd == NULL || ret != ITS_SUCCESS)
            {
                DT_ERR(("Decode Failure"));

                /* Send Error Response if the cmd is request*/
                if (REQUEST_BIT_SET(cmdFlag))
                {
                    ret = DiaErrHandler::HandleError(trInst, msg, ret);
                }

                return (ret);
            }

            if (REQUEST_BIT_SET(cmdFlag))
            {
                evtType = PEER_EVT_I_RCV_CER;
                //increment the Peer CER stats
                DIA_INC_PEER_CER_RECEIVED(entry);
            }
            else
            {
                evtType = PEER_EVT_I_RCV_CEA;
                //increment the peer CEA stats
                DIA_INC_PEER_CEA_RECEIVED(entry);
            }
            break;
        }
        case DIA_MSG_DW:
        {
            ret = DiaUtils::DecodeMsg(&cmd, msg, msgLen);
            if (cmd == NULL || ret != ITS_SUCCESS)
            {
                DT_ERR(("Decode Failure"));

                /* Send Error Response if the cmd is request*/
                if (REQUEST_BIT_SET(cmdFlag))
                {
                    ret = DiaErrHandler::HandleError(trInst, msg, ret);
                }

                return (ret);
            }

            if (REQUEST_BIT_SET(cmdFlag))
            {
                evtType = PEER_EVT_I_RCV_DWR;
                DIA_INC_PEER_DWR_RECEIVED(entry);
            }
            else
            {
                evtType = PEER_EVT_I_RCV_DWA;
                DIA_INC_PEER_DWA_RECEIVED(entry);
            }
            break;
        }
        case DIA_MSG_DP:
        {
            ret = DiaUtils::DecodeMsg(&cmd, msg, msgLen);
            if (cmd == NULL || ret != ITS_SUCCESS)
            {
                DT_ERR(("Decode Failure"));

                /* Send Error Response if the cmd is request*/
                if (REQUEST_BIT_SET(cmdFlag))
                {
                    ret = DiaErrHandler::HandleError(trInst, msg, ret);
                }

                return (ret);
            }

            if (REQUEST_BIT_SET(cmdFlag))
            {
                evtType = PEER_EVT_I_RCV_DPR;
                DIA_INC_PEER_DPR_RECEIVED(entry);
            }
            else
            {
                evtType = PEER_EVT_I_RCV_DPA;
                DIA_INC_PEER_DPA_RECEIVED(entry);
            }

            break;
        }
        case DIA_MSG_CUR:
        {
            ret = DiaUtils::DecodeMsg(&cmd, msg, msgLen);
            if (cmd == NULL || ret != ITS_SUCCESS)
            {
                DT_ERR(("Decode Failure"));

                /* Send Error Response if the cmd is request*/
                if (REQUEST_BIT_SET(cmdFlag))
                {
                    ret = DiaErrHandler::HandleError(trInst, msg, ret);
                }

                return (ret);
            }

            if (REQUEST_BIT_SET(cmdFlag))
            {
                CAPABILITIES_UPDATE_APPLICATION->ProcessCUR(cmd,entry,event);
                UPDATE_DIA_STATS_REQIN(cmdCode);
                DIA_INC_PEER_TOTAL_REQUEST_RECEIVED(entry);
            }
            else
            {
                CAPABILITIES_UPDATE_APPLICATION->ProcessCUA(cmd,entry);
                if (ERROR_BIT_SET(cmdFlag))
                {
                    UPDATE_DIA_ERR_ANSIN();
                }
                else
                {
                    UPDATE_DIA_STATS_ANSIN(cmdCode);
                    DIA_INC_PEER_TOTAL_RESPONSE_RECEIVED(entry);
                }
            }
            //Return from here so that message will not be sent to peer state machine
            //This is done instead of checking the cmdCode != DIA_MSG_CUR
            //before calling UpdatePeerSM
            return ITS_SUCCESS;
            break;
        }
        default:
            DT_DBG(("Application Spec Message Received: cmdCode = %d", cmdCode));
            cmd = NULL;
            evtType = PEER_EVT_I_RCV_MESSAGE;

            break;
        }

        if (REQUEST_BIT_SET(cmdFlag))
        {
            UPDATE_DIA_STATS_REQIN(cmdCode);
            DIA_INC_PEER_TOTAL_REQUEST_RECEIVED(entry);
        }
        else
        {
            if (ERROR_BIT_SET(cmdFlag))
            {
                UPDATE_DIA_ERR_ANSIN();
            }
            else
            {
                UPDATE_DIA_STATS_ANSIN(cmdCode);
                DIA_INC_PEER_TOTAL_RESPONSE_RECEIVED(entry);
            }
        }

        if ((ret = DiaMsgRouter::UpdatePeerSM(cmd, entry,
                                              evtType,
                                              trHandle, event)) == ITS_SUCCESS)
        {
            DT_DBG(("Succesfully Submitted Message to Peer SM"));
        }
        else
        {
            DT_ERR(("Failed to Handle Message in Peer SM = %d", ret));
            return (ITS_DIA_EINVALID_PEER_STATE);
        }

    }
    catch (NoSuchAttributeException& e) //Fixing Big Parameter passing by value
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));
        return (!ITS_SUCCESS);
    }
    catch (WrongCommandTypeException& e) //Fixing Big Parameter passing by value
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));
        return (!ITS_SUCCESS);
    }
    catch (UnknownTypeException& e) //Fixing Big Parameter passing by value
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));
        return (!ITS_SUCCESS);
    }
    catch (CodecException& e) //Fixing Big Parameter passing by value
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));
        return (!ITS_SUCCESS);
    }
    catch (...)
    {
        DT_ERR(("DiaConnectorReader::HandleMessage: Unknown Exception Caught:"));
        return (!ITS_SUCCESS);
    }

    return (ITS_SUCCESS);
}

int
DiaConnectorReader::Read(ITS_EVENT *event)
{
    int ret = 0;

    ret = ReadEvent(event);

    if (ret > 0)
    {
        /* Maintaining count instead of timestamps to initiate DW /
           transport failure
           SetLastUpdate(TIMERS_Time());
         */
        DT_DBG(("Received Data. RetVal: %d", ret));
        ResetLastUpdate();

        if (GetPeer() && DIA_PE_DWA_PENDING(GetPeer()))
        {
            MUTEX_AcquireMutex(&DIA_PE_MUX(GetPeer()));
            /**
             * Replacing the StopDWTimer and boolean flag by
             * DWA pending. Setting it to 0 after data received
             * on socket and securing it under the peer mutex.
             */
            DIA_PE_DWA_PENDING(GetPeer()) = 0;
            MUTEX_ReleaseMutex(&DIA_PE_MUX(GetPeer()));
        }
        HandleMessage(event);
    }
    else if (ret == 0)
    {
        PEER_ENTRY* pEntry = GetPeer();
        DT_WRN(("Connector EOF on Socket Read Peer = %s\n",
                                    DIA_PE_HOST(pEntry)));
        ret = HandleSocketError(pEntry);
        return ret;
    }
    else
    {
        DT_CRT(("Failed to read event ret = %d", ret));
        DIA_Alarm(15100, __FILE__, __LINE__, "ret =%d", ret);
        return !ITS_SUCCESS;
    }
    return ITS_SUCCESS;
}

void
DiaConnectorReader::Execute(void *arg)
{
    HMIThread_Info* hmiInfo = NULL;
    ITS_EVENT event;
    ITS_EVENT_INIT(&event, ITS_DIA_SRC, 0);
    int i = 0, ret = 0, readCount;
    int threadCancelType;
    ITSDiaConfig *cfg = &itsDiaConfig;
#if defined(linux) && !defined(USE_SELECT)
    struct epoll_event epollEvts[MAX_PEER_CONNS];
#endif

    DT_DBG(("DiaConnectorReader::Execute"));

    ITS_INT thrID = THREAD_GetCurrentThreadID();
    hmiInfo = HMI_AddToMonList(&monList, "DiaConnectorReader", (ITS_THREAD*)thrID);
    while (!_doExit)
    {
        ITS_EVENT_TERM(&event);
        if(cfg->IsHMIEnabled())
        {
            HMI_ResetCounter(hmiInfo);
        }
#if !defined(linux) || defined(USE_SELECT)
        ret = connSelectTbl.SelectSock();
        if (ret == 0)
        {
            continue;
        }
        //for(i=0; i < connSelectTbl.fdCount; i++)
        for(i=0, readCount=0; i < MAX_PEER_CONNS; i++)
        {
            /* IMP keep the valid reference for trHandle*/
            trHandle = connSelectTbl.desc[i];
            if(trHandle && connSelectTbl.IsReadable(trHandle->_socketFd))
            {
                Read(&event);
                readCount++;
            }

            if (readCount == ret)
            {
                break;
            }
        }
#else
        ret = connEpollTbl.EpollWait(epollEvts);
        if (ret < 0)
        {
            DT_ERR (("epoll_wait failed with error %d.",errno));
            continue ;
        }
        for(i=0;i<ret;i++)
        {
            /* IMP keep the valid reference for trHandle*/
            trHandle = (DiaSocketTransport* )epollEvts[i].data.ptr;
            if (trHandle != NULL)
            {
                if (epollEvts[i].events & EPOLLIN)
                {
                    /* call read in case of EPOLLIN event */
                Read(&event);
                }
                else if ( (epollEvts[i].events & EPOLLERR) || (epollEvts[i].events & EPOLLHUP))
                {
                    DT_WRN(("EPOLL ERROR/HangUp Event 0x%x for peer: %s", epollEvts[i].events, DIA_PE_HOST(trHandle->GetPeer())));
                    HandleSocketError(trHandle->GetPeer());
                }
            }
            else
            {
                DT_ERR(("trHandle is NULL. Event is 0x%x", epollEvts[i].events));
            }
        }
#endif

    }
    HMI_RemoveFromMonList(&monList, (ITS_THREAD*)thrID);
    DT_ERR(("DiaConnector Set Exit...Shutting down"));
}

int DiaConnectorReader::HandleSocketError(PEER_ENTRY *pEntry)
{
    int ret = ITS_SUCCESS;
    /* mark the transport down, hence no connection will be
     *      * accepted for this peer unless two Device Watch Dog
     *           * messages failed */
    markDown();
    /*explicitely delete the socket from epoll list since there are chance of getting
     *      * epoll event after shutdown too
     *           */
#if defined(linux) && !defined(USE_SELECT)
    connEpollTbl.DelEpollSock(trHandle);
#endif
    MUTEX_AcquireMutex(&DIA_PE_MUX(pEntry));
    if (DIA_PE_STATE(pEntry) == PEER_ST_CLOSED)
    {
        DT_WRN(("Peer is in Closed State"));
        //DIA_INC_PEER_CONNECTION_CLOSE_BY_STACK_COUNT(pEntry);
        DIA_INC_PEER_CONNECTION_TOTAL_TRANSPORT_DOWN_COUNT(pEntry);
        Shutdown(NULL);
        DIA_PE_CONN_SPECS(pEntry).trHandle = NULL;
        DIA_PE_CONN_SPECS(pEntry).trInst = 0;
        /* restarting the retry timer */
        if (DIA_PE_RETRY_TIMER(pEntry) != TIMER_BAD_SERIAL)
        {
            PeerTable::StopTimer(RETRY, pEntry);
        }
        else if (DIA_PEER_GET_DIS_CAUSE(pEntry) != DisconnectCause::DO_NOT_WANT_TO_TALK_TO_YOU)
        {
            if (itsDiaConfig.GetInitiateConnsOpt())
            {
                PeerTable::StartTimer(RETRY, pEntry);
            }
        }
        else
        {
            DIA_PEER_GET_DIS_CAUSE(pEntry) = DisconnectCause::REBOOTING;
        }

        MUTEX_ReleaseMutex(&DIA_PE_MUX(pEntry));
        return !ITS_SUCCESS;
    }

    MUTEX_ReleaseMutex(&DIA_PE_MUX(pEntry));

    if ( (ret = DiaMsgRouter::UpdatePeerSM(NULL, pEntry,
                    PEER_EVT_I_PEER_DISC,
                    trHandle, NULL)) == ITS_SUCCESS)
    {
        DT_DBG(("Succesfully Submitted Message to Peer SM"));
    }
    else
    {
        DT_ERR(("Failed to Handle Message in Peer SM = %d", ret));

        /* Start Retry Timer after the state machine returns failure*/
        if (DIA_PE_RETRY_TIMER(pEntry) != TIMER_BAD_SERIAL)
        {
            PeerTable::StopTimer(RETRY, pEntry);
        }
        if (DIA_PEER_GET_DIS_CAUSE(pEntry) != DisconnectCause::DO_NOT_WANT_TO_TALK_TO_YOU)
        {
            if (itsDiaConfig.GetInitiateConnsOpt())
            {
                PeerTable::StartTimer(RETRY, pEntry);
            }
        }
        else
        {
            DIA_PEER_GET_DIS_CAUSE(pEntry) = DisconnectCause::REBOOTING;
        }
    }
    DIA_INC_PEER_CONNECTION_CLOSE_BY_PEER_COUNT(pEntry);
    DIA_INC_PEER_CONNECTION_TOTAL_TRANSPORT_DOWN_COUNT(pEntry);

    Shutdown(&connEpollTbl);
    return !ITS_SUCCESS;
}
