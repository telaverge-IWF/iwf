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
 * LOG: $Log: dia_acceptor.cpp,v $
 * LOG: Revision 3.40.2.1.2.7.4.14.4.7.14.5  2020/02/14 11:36:11  jkchaitanya
 * LOG: TCP Timeout fix ported from DRE
 * LOG:
 * LOG: Revision 3.40.2.1.2.7.4.14.4.7.14.4  2015/02/17 06:22:44  jkchaitanya
 * LOG: changes for peer down crash ported from stack branch for bugs 5507, 6067
 * LOG:
 * LOG: Revision 3.40.2.1.2.7.4.14.4.7.14.3  2014/12/17 05:19:08  jkchaitanya
 * LOG: changes to revert back the server down crash changes
 * LOG:
 * LOG: Revision 3.40.2.1.2.7.4.14.4.7  2014/01/06 09:22:32  cprem
 * LOG: Changes in diameter stack to support session replication. Review request 1611.
 * LOG:
 * LOG: Revision 3.40.2.1.2.7.4.14.4.6  2013/12/11 09:59:45  vsarath
 * LOG: Fix for issues 1639, 2143
 * LOG:
 * LOG: Revision 3.40.2.1.2.7.4.14.4.5  2013/12/09 04:52:26  ncshivakumar
 * LOG: Fixed bug 2439,2443,2368,1898
 * LOG:
 * LOG: Revision 3.40.2.1.2.7.4.14.4.4  2013/10/26 07:42:21  ncshivakumar
 * LOG: RFC 6733 changes
 * LOG:
 * LOG: Revision 3.40.2.1.2.7.4.14.4.3  2013/09/10 08:36:39  ncshivakumar
 * LOG: RFC6733 Changes
 * LOG:
 * LOG: Revision 3.40.2.1.2.7.4.14.4.2  2013/08/01 05:12:52  vsarath
 * LOG: Reverting back the fix for 1520
 * LOG:
 * LOG: Revision 3.40.2.1.2.7.4.14  2013/04/18 13:16:31  millayaraja
 * LOG: updated peer transport stats
 * LOG:
 * LOG: Revision 3.40.2.1.2.7.4.13  2013/04/18 07:04:30  jvikram
 * LOG: Included changes relatd to log segregation.
 * LOG:
 * LOG: Revision 3.40.2.1.2.7.4.12  2013/04/12 04:15:40  vsarath
 * LOG: Logs improvement
 * LOG:
 * LOG: Revision 3.40.2.1.2.7.4.11  2013/04/07 03:54:21  cprem
 * LOG: Changes made to fix HA bugs. Review Request 784
 * LOG:
 * LOG: Revision 3.40.2.1.2.7.4.10  2013/04/01 05:46:09  vsarath
 * LOG: Fix for Coverity warnings
 * LOG:
 * LOG: Revision 3.40.2.1.2.7.4.9  2013/03/22 06:33:33  pramana
 * LOG: Changes for HA feature
 * LOG:
 * LOG: Revision 3.40.2.1.2.7.4.8  2013/03/22 04:23:56  mallikarjun
 * LOG: Bug-1194-correction
 * LOG:
 * LOG: Revision 3.40.2.1.2.7.4.7  2013/03/21 11:49:22  mallikarjun
 * LOG: Bug-1194-Changes
 * LOG:
 * LOG: Revision 3.40.2.1.2.7.4.6  2013/03/20 05:14:32  mallikarjun
 * LOG: dia_utils.cpp
 * LOG:
 * LOG: Revision 3.40.2.1.2.7.4.5  2013/03/15 10:25:45  mallikarjun
 * LOG: BUG-1194-Chages
 * LOG:
 * LOG: Revision 3.40.2.1.2.7.4.4  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.40.2.1.2.7.4.3  2013/02/21 11:17:07  ncshivakumar
 * LOG: Modified for multitransport support
 * LOG:
 * LOG: Revision 3.40.2.1.2.7.4.2  2013/02/01 11:34:15  pramana
 * LOG: Merged from branch 0212 to 0300.
 * LOG:
 * LOG: Revision 3.40.2.1.2.7.4.1  2013/01/29 13:13:16  mallikarjun
 * LOG: Bug 1001 changes
 * LOG:
 * LOG: Revision 3.40.2.1.2.9  2013/01/25 02:56:44  mallikarjun
 * LOG: Bug-PeerConn-Stats
 * LOG:
 * LOG: Revision 3.40.2.1.2.8  2013/01/18 04:48:00  jsarvesh
 * LOG: cppcheck changes
 * LOG:
 * LOG: Revision 3.40.2.1.2.7  2013/01/15 12:01:17  cprem
 * LOG: Fixed bug 932 where Connection closure stats were updated wrongly
 * LOG:
 * LOG: Revision 3.40.2.1.2.6  2013/01/03 04:05:01  vsarath
 * LOG: Fix for issue 833
 * LOG:
 * LOG: Revision 3.40.2.1.2.5  2012/11/26 04:57:07  mallikarjun
 * LOG: Bug-569-Changes
 * LOG:
 * LOG: Revision 3.40.2.1.2.4  2012/11/20 17:39:44  pramana
 * LOG: Merged from CMAPI branch for 212-07 release
 * LOG:
 * LOG: Revision 3.40.2.1.2.2.8.3  2012/11/20 03:53:06  millayaraja
 * LOG: updated for peer stats
 * LOG:
 * LOG: Revision 3.40.2.1.2.2.8.2  2012/11/19 13:00:18  millayaraja
 * LOG: modified for Peer Stack Statistics
 * LOG:
 * LOG: Revision 3.40.2.1.2.2.8.1  2012/11/19 08:36:07  millayaraja
 * LOG: modified for Transport Stats
 * LOG:
 * LOG: Revision 3.40.2.1.2.2  2012/10/19 17:54:43  brajappa
 * LOG: BugId 15: IPv6 support enhancements
 * LOG:
 * LOG: Revision 3.40.2.1.2.1  2012/08/21 08:55:57  ksalil
 * LOG: Merge from branch B-DRE-IDIA-0100-00
 * LOG:
 * LOG: Revision 3.40.2.2  2012/08/01 07:57:22  millayaraja
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 3.40.2.1  2012/07/10 08:34:11  ncshivakumar
 * LOG: Updated code to send error code 3003 and 3010 in case of unknown realm and unknown peer respectively
 * LOG:
 * LOG: Revision 3.40  2011/11/14 04:59:21  rajeshak
 * LOG: "Slot in use" issue fix
 * LOG:
 * LOG: Revision 3.39  2011/08/23 04:10:29  vkumara
 * LOG: DataToInt is being changed to DataToUInt.
 * LOG: To fix CmdCode decode error for an unsigned values from abnf.
 * LOG: (Extra FF was returning from existing DataToInt ()).
 * LOG:
 * LOG: Revision 3.38  2011/07/14 14:04:51  vkumara
 * LOG: ForceDisconnect Requirement - Not to initiate connection.
 * LOG:
 * LOG: Revision 3.37  2011/07/04 09:17:20  nvijikumar
 * LOG: Fix for disabling connection initiation issue.
 * LOG: Connection initiation flag is checked before starting RETRY timer
 * LOG:
 * LOG: Revision 3.36  2011/06/28 08:09:51  rajeshak
 * LOG: Motorola (PSG) ForceDisconnect Issue
 * LOG:
 * LOG: Revision 3.35  2010/12/14 00:40:47  nvijikumar
 * LOG: 1. DO_NOT_WANT_TO_TALK_TO_YOU disc cause implimentation
 * LOG: 2. SCTP Sock read failure
 * LOG:
 * LOG: Revision 3.34  2010/10/11 07:57:26  rajeshak
 * LOG: Solaris IPV6 Support
 * LOG:
 * LOG: Revision 3.33  2010/08/27 12:28:11  nvijikumar
 * LOG: DSCP value support (IP header) - Vasanth
 * LOG:
 * LOG: Revision 3.32  2010/08/19 11:21:26  nvijikumar
 * LOG: Porting changes from B-MOTO-IDIA-0421-00
 * LOG: 1. New Overload implimentation changes are not being ported.
 * LOG: 2. Force disconnect changes are not being ported.
 * LOG:
 * LOG: Revision 3.31  2009/09/10 13:56:48  rajeshak
 * LOG: Fixed a bug in Reader Thread.
 * LOG:
 * LOG: Revision 3.30  2009/08/28 08:57:57  rajeshak
 * LOG: Fix for Issue:2334 (IDS do not retry to establish connection with Peer)
 * LOG: Peer Connection Init Flag is made false only after accepting CER.
 * LOG:
 * LOG: Revision 3.29  2009/08/24 11:51:19  rajeshak
 * LOG: changes for non-blocking accept.
 * LOG:
 * LOG: Revision 3.28  2009/07/01 11:21:39  nvijikumar
 * LOG: Fix for RETRY timer issue (CER is not initiated properly)
 * LOG:
 * LOG: Revision 3.27  2009/06/29 14:52:26  rajeshak
 * LOG: HMI Changes to improve the performance.
 * LOG:
 * LOG: Revision 3.26  2009/05/12 08:42:31  rajeshak
 * LOG: Klockwork reported Issue fix.
 * LOG:
 * LOG: Revision 3.25  2009/04/10 06:37:16  sureshj
 * LOG: Compilation flag HMI_ENABLE removed & added dynamic configuration.
 * LOG:
 * LOG: Revision 3.24  2009/04/07 13:57:01  sureshj
 * LOG: HMI monitoring is enabled for DiaAcceptorReader thread.
 * LOG:
 * LOG: Revision 3.23  2009/03/19 13:33:30  sureshj
 * LOG: DIA_VERSION check added
 * LOG:
 * LOG: Revision 3.22  2009/03/19 12:42:34  nvijikumar
 * LOG: Global instance is created for the Class ITSDiaConfig to avoid function
 * LOG: call overhead as ITSDiaConfig::GetITSDiaConfig() was called max time
 * LOG:
 * LOG: Revision 3.21  2009/03/19 11:18:18  chandrashekharbs
 * LOG: Changes for IPV6 SCTP support
 * LOG:
 * LOG: Revision 3.20  2009/03/03 11:32:07  rajeshak
 * LOG: IssueID:1681
 * LOG: FeatureID:None
 * LOG: Description: (IDS dumps core when it receives CER with NO COMMON APPLICATION)
 * LOG: Problem due to double delete of CER.
 * LOG:
 * LOG: Revision 3.19  2009/03/03 11:17:20  rajeshak
 * LOG: Klockwork reported issue fix
 * LOG:
 * LOG: Revision 3.18  2009/03/03 06:54:50  chandrashekharbs
 * LOG: Changes for IPV6 TCP support
 * LOG:
 * LOG: Revision 3.17  2009/02/12 12:51:59  rajeshak
 * LOG: IssueID:1489
 * LOG: FeatureID:None
 * LOG: Description: (IDS is dumping core when receiving CER from unknown peer)
 * LOG: Moved First CER flag clearing code to proper place.
 * LOG:
 * LOG: Revision 3.16  2009/02/04 05:49:58  nvijikumar
 * LOG: Changes for 64 Peer support with fixed number of threads
 * LOG: 1. One thread for accepting connections and other for initiate connections
 * LOG: 2. One thread to Read from I-Connections and other for R-Connections
 * LOG:
 * LOG: Revision 3.15  2009/01/09 09:47:20  rajeshak
 * LOG: Klockwork reported issue fix.
 * LOG:
 * LOG: Revision 3.14  2009/01/09 09:06:50  nvijikumar
 * LOG: Added Alarm for Decode failure and Receive failure
 * LOG:
 * LOG: Revision 3.13  2009/01/03 07:01:07  nvijikumar
 * LOG: Proper usage of trIndex
 * LOG:
 * LOG: Revision 3.12  2009/01/03 05:32:21  rajeshak
 * LOG: Fix for KLOCK Work reported issues
 * LOG:
 * LOG: Revision 3.11  2008/12/31 13:22:26  nvijikumar
 * LOG: Fix for PBN Issue Id: 1410 (Invalid pointer access GetPeer())
 * LOG: and Fix for Motorola core dump issue
 * LOG:
 * LOG: Revision 3.10  2008/12/23 12:23:29  sureshj
 * LOG: Updates for Statistics. Fix for issue 1379.
 * LOG:
 * LOG: Revision 3.9  2008/12/12 12:32:08  nvijikumar
 * LOG: Updated with statistic support
 * LOG:
 * LOG: Revision 3.8  2008/12/11 11:08:57  nvijikumar
 * LOG: Mutex not required as single thread does read from the socket
 * LOG:
 * LOG: Revision 3.7  2008/11/19 05:21:01  nvijikumar
 * LOG: IssueID:None
 * LOG: FeatureID:None
 * LOG: Description:Made Peer IP Check as configurable option
 * LOG:
 * LOG: Revision 3.6  2008/10/31 05:47:22  nvijikumar
 * LOG: IssueID:1189
 * LOG: FeatureID: none
 * LOG: Description: Code Optimization
 * LOG:
 * LOG: Revision 3.5  2008/10/28 12:06:28  nvijikumar
 * LOG: IssueID: none
 * LOG: FeatureID: none
 * LOG: Description: Porting Performance changes from 3.0 branch
 * LOG:
 * LOG: Revision 3.4  2008/09/09 10:12:07  sureshj
 * LOG: Propagated fix for BW issue 2006 from 2.1.
 * LOG:
 * LOG: Revision 3.3  2008/07/09 10:48:14  vnarang
 * LOG: Adding a check for TLS_ENABLED flag during compilation
 * LOG:
 * LOG: Revision 3.2  2008/06/13 11:24:38  hbhatnagar
 * LOG: Added code to implement the TLS feature. Modified the Read and Write
 * LOG: for the sockets
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.21  2008/03/27 12:14:08  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.19.2.9  2008/01/07 18:03:25  hbhatnagar
 * LOG: Changes made to provide fix for various issues 20,22 and 23
 * LOG: calling SetExit() API in place of _doExit = ITS_TRUE.
 * LOG:
 * LOG: Revision 2.19.2.8  2008/01/07 13:22:50  avinashks
 * LOG: Fix for Issue No.17 raised by Dhirananda during
 * LOG: validation of BCGI ticket 1807.
 * LOG:
 * LOG: Revision 2.19.2.7  2008/01/05 16:39:20  avinashks
 * LOG: Changes made to provide fix for issue no.19 raised by Dhiranand during
 * LOG: the validation of bcgi ticket 1807.
 * LOG:
 * LOG: Revision 2.19.2.6  2007/12/16 15:00:39  hbhatnagar
 * LOG: Changes made to fix issue no.3 raised during the validation of bcgi
 * LOG: ticket 1807.
 * LOG:
 * LOG: Revision 2.19.2.5  2007/12/14 11:24:48  hbhatnagar
 * LOG: Removed the DeviceWatchDog Timer related functionality and added
 * LOG: WatchDog Transport Thread related functionality.
 * LOG:
 * LOG: Revision 2.19.2.4  2007/11/14 17:21:13  hbhatnagar
 * LOG: Passing the acceptor handle and instance to current handle and instance
 * LOG: only if the connector is down (Fix for abnormal DWTimeout).
 * LOG:
 * LOG: Revision 2.19.2.3  2007/09/25 09:48:32  hbhatnagar
 * LOG: Acquired Mutex for StartTimer in HandleMessage to solve DWTimeout issue.
 * LOG:
 * LOG: Revision 2.19.2.2  2007/05/28 14:02:23  nvijikumar
 * LOG: Return Error Response if request message failed to decode.
 * LOG:
 * LOG: Revision 2.19.2.1  2007/05/25 04:18:02  nvijikumar
 * LOG: Decode Base protocol Messages to BaseGenericCmd, this commad will be
 * LOG: converted to Base specific command in the peer SM.
 * LOG:
 * LOG: Revision 2.19  2007/02/17 07:24:19  nanaparthi
 * LOG: Fix for Follwing issue (Bug 5237)
 * LOG:  On non-redundant static setup with SCTP transport if you kill the client
 * LOG:  abnormally on peer side trace prints Exception Caught: CodecException ,
 * LOG:  Error Cause: Wrong Command Header length
 * LOG:
 * LOG: Revision 2.18  2007/01/29 13:56:15  nanaparthi
 * LOG: (1)Enhancements made for DiaAcceptor::AcceptConnections()function
 * LOG: (2)Gave fix for Bugs 5239, 5211
 * LOG:
 * LOG: Revision 2.17  2007/01/24 16:02:03  tpanda
 * LOG: Fix for Bug # 5151
 * LOG:
 * LOG: Revision 2.16  2007/01/19 11:08:17  nvijikumar
 * LOG: Moved Start RETRY timer to Peer SM after getting PEER_DISC indication event.
 * LOG:
 * LOG: Revision 2.15  2006/12/29 06:56:18  nanaparthi
 * LOG: SCTP Multihoming related changes (baseline code base)
 * LOG:
 * LOG: Revision 2.14  2006/12/20 14:57:42  tpanda
 * LOG: Other bug fixes related to redundancy(Issue#5075,5073,5069,5057 etc)
 * LOG:
 * LOG: Revision 2.13  2006/12/17 03:34:44  tpanda
 * LOG: Fix for bug# 5067 and default route handling
 * LOG:
 * LOG: Revision 2.12  2006/12/11 13:51:25  tpanda
 * LOG: REDUNDANCY_SLOT_CHANGES are removed and code seems to be stable
 * LOG:
 * LOG: Revision 2.11  2006/12/10 13:42:42  tpanda
 * LOG: Redundancy Bug Fixes and enhancements--Transport Order Fix
 * LOG:
 * LOG: Revision 2.10  2006/11/30 18:54:24  tpanda
 * LOG: Redundancy slot changes backed out. TODO: Refer (REDUNDANCY_SLOT_CHANGES) defines
 * LOG: Failover and failback bug fixes
 * LOG:
 * LOG: Revision 2.9  2006/11/30 11:52:49  tpanda
 * LOG: Fix for sending DWR to one peer (bug if 4992)
 * LOG:
 * LOG: Revision 2.8  2006/11/25 03:57:20  tpanda
 * LOG: Changes for Msg based redundancy
 * LOG:
 * LOG: Revision 2.7  2006/11/06 05:16:24  nvijikumar
 * LOG: SCTP support for 64bit solaris compilation.
 * LOG:
 * LOG: Revision 2.6  2006/10/30 15:59:59  yranade
 * LOG: Exception Handling.
 * LOG:
 * LOG: Revision 2.5  2006/10/16 16:00:03  yranade
 * LOG: Shutdown the transport for CER from unknown peer. Need to add
 * LOG: callback to provide option to the app, to accept CER from unknown peers.
 * LOG:
 * LOG: Revision 2.4  2006/10/12 14:13:41  yranade
 * LOG: Finish up Device Watchdog handling. Bug Fix: 4464
 * LOG:
 * LOG: Revision 2.3  2006/10/05 13:21:54  yranade
 * LOG: Getting there.
 * LOG:
 * LOG: Revision 2.2  2006/09/26 06:07:14  nvijikumar
 * LOG: SCTP Changes ( Viji, Naresh)
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:44  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:29  yranade
 * LOG: Initial Version of ITS-Diameter (Yogesh, Viji, Tushar)
 * LOG:
 * ID: $Id: dia_acceptor.cpp,v 3.40.2.1.2.7.4.14.4.7.14.5 2020/02/14 11:36:11 jkchaitanya Exp $
 ****************************************************************************/
#ident "$Id: dia_acceptor.cpp,v 3.40.2.1.2.7.4.14.4.7.14.5 2020/02/14 11:36:11 jkchaitanya Exp $"

#include <net/if.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <arpa/nameser.h>

#if defined TRY_AGAIN
#undef TRY_AGAIN
#endif

#include <its_dia_config.h>

#include <dia_cmn.h>
#include <dia_err.h>
#include <dia_utils.h>
#include <dia_trace.h>
#include <dia_acceptor.h>
#include <dia_peer_fsm.h>
#include <dia_peer_table.h>
#include <dia_msg_router.h>
#include <its_dia_config.h>
#include <dia_capabilities_update_application.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
#endif
#ifdef TLS_ENABLED
extern ITS_INT TlsServerProcedure(ITS_SocketInfo* info,DiaSocketTransport* trHandl);
#endif
#if !defined(linux) || defined(USE_SELECT)
DiaSelectSockContainer accSelectTbl;
#endif

int DiaAcceptorReader::VerifyPeerConnectionIpAddress(PEER_ENTRY* aPeerEntry)
{
    DT_DBG(("ENTER VerifyPeerConnectionIpAddress\n"));
    ITSDiaConfig *cfg = &itsDiaConfig;
    if(!cfg->IsPeerIpCheckEnabled())
    {
        return true;
    }
    bool retVal=false;
    ITS_BOOLEAN ipV4Flag=ITS_TRUE;
    its::Socket* info = trHandle->GetSocket();
    ITS_SocketInfo * ainfo	= ((its::ServerSocket *)trHandle->GetSocket())->GetSocketInfo();
    char connectedIpAddr[IP_ADDRESS_LEN];
    char *ptr = connectedIpAddr;
    memset ( connectedIpAddr, '\0', IP_ADDRESS_LEN );
    if (ainfo->af == AF_INET6)
    {
        ipV4Flag=ITS_FALSE;
    }
    info->GetIpAddress(&ptr, IP_ADDRESS_LEN, ipV4Flag);
    //Let fetch the ip addrs from 0th index.anyways ip addrs will be same
    DIA_TRANS_TYPE type = DIA_PE_CONN_SPECS(aPeerEntry).tInfo[0].type;
    DT_DBG(("Tranport-Type = %d  ::  AF-Type = %d  :: Connected-IP = %s ",type,ainfo->af,connectedIpAddr));
    if( type == ITS_DIA_T_TCP )
    {
        const char *configuredPeerIP = DIA_PE_CONN_SPECS(aPeerEntry).tInfo[0].serverIpAddr;
        DT_DBG(("TCP :: Connected-IP = %s , Configured-Ip = %s \n",connectedIpAddr,configuredPeerIP));
        if(DiaUtils::CompareIPAddress(connectedIpAddr,configuredPeerIP, ainfo->af))
        {
            DT_DBG(("CompareIPAddress Success"));
            retVal=true;
        }
        else
        {
            DT_DBG(("CompareIPAddress Failure"));
        }
    }
    else if( type == ITS_DIA_T_SCTP)
    {
	/**Limitation for SCTP ::
 	* All the Multihome Ip Addresses are not verified. if any one of them matches the connected ip then validation will be through
 	* */
         const char **multihomeips = DIA_PE_CONN_SPECS(aPeerEntry).tInfo[0].multiHomeipaddrs;
         ITS_USHORT no_ips = DIA_PE_CONN_SPECS(aPeerEntry).tInfo[0].noIPs;
         DT_DBG(("SCTP :: Number of Multihome IP's = %d \n",no_ips));
         for(int index=0;index < no_ips;index++)
         {
	     //If Any one of the Configured multihome ip Address's matches then brerak the loop
	     //For SCTP Ideal Implementation would be, to verify the the Host-Ip-Address Avp's
	     //in the CER with the configured,
	     DT_DBG(("SCTP :: Connected-IP = %s , Configured-Ip = %s \n",connectedIpAddr,multihomeips[index]));
	     if(DiaUtils::CompareIPAddress(connectedIpAddr,multihomeips[index], ainfo->af))
             {
                 DT_DBG(("CompareIPAddress Success"));
                 retVal=true;
		 break;

             }
             else
             {
                 DT_DBG(("CompareIPAddress Failure"));
             }
    	}
    }
    else
    {
	 DT_ERR((" Unknown Transport type = %d ",type));
    }
    DT_DBG(("LEAVE VerifyPeerConnectionIpAddress -- Return Value = %d \n",retVal));
    return retVal;
}

int
DiaAcceptorReader::HandleFirstCER(ITS_EVENT *event)
{
    int ret;
    int cnt;
    ITS_OCTET cmdFlag = 0x0;
    ITS_UINT cmdCode = 0;
    PEER_ENTRY *entry = NULL;
    PEER_STATE_CTXT pCtxt;
    bool ipVerify=false;

    if (event == NULL)
    {
       DT_ERR(("Received NULL Event"));
       return (!ITS_SUCCESS);
    }


    ITS_USHORT trInst = ITS_GET_CTXT(event->data);
    ITS_OCTET *msg = &event->data[sizeof(ITS_USHORT)];
    ITS_UINT msgLen = (event->len - sizeof(ITS_USHORT));
    DT_DBG(("Received Event with Length: %d From Source: %d", event->len, event->src, trInst));

    /* Section 5.6.1 */
    cmdFlag = msg[4];
    cmdCode = DiaUtils::DataToUInt(&msg[5], (sizeof(ITS_UINT) - 1));

    DT_DBG(("CommandFlag: %d CommandCode: %d Inst %d", cmdFlag, cmdCode, trInst));

    if (REQUEST_BIT_SET(cmdFlag))
    {
        DIA_CER *cer = NULL;
        try
        {

            DT_DBG(("Creating DIA_CER."));
            cer = new DIA_CER(msg, msgLen);

            if (cer == NULL)
            {
                DT_ERR(("Error in allocating memory for DIA_CER. Returning.."));
                return (!ITS_SUCCESS);
            }

            const OriginHost& oh = cer->getOriginHost();
            const OriginRealm& orlm = cer->getOriginRealm();

            const char* hostName = oh.value().c_str();
            const char* realmName = orlm.value().c_str();

            DT_DBG(("OriginHost = %s OriginRealm", hostName, realmName));

            ITS_USHORT trInst;
            if ( (PEER_TABLE->FindEntry(hostName,
                                      realmName,
                                      entry,trInst)) &&
				      (!DIA_PE_IS_FORCE_DISCONNECTED(entry)) &&
				      ( (ipVerify=VerifyPeerConnectionIpAddress(entry)) == true ) )
            {
                DT_DBG(("Succesfully Retrieved Entry for %s", hostName));

                //make correction if there is any error trInstance set
                //while accepting the connection

                trInst++;

                if (trInst != trHandle->_instance)
                {
                    DT_DBG(("Received CER on New Trnaport Connection"));
                    if (DIA_PE_STATE(entry) == PEER_ST_I_OPEN ||
                        DIA_PE_STATE(entry) == PEER_ST_R_OPEN)
                    {
                        DT_ERR(("Peer already in open state. "
                                "Rejecting new connecting."));
                        if (cer)
                        {
                            DT_DBG(("Deleting DIA_CER"));
                            delete cer;
                            cer = NULL;
                        }
                        DIA_INC_PEER_CONNECTION_CLOSE_BY_DRE_COUNT(entry);
                        DIA_INC_PEER_CONNECTION_TOTAL_TRANSPORT_DOWN_COUNT(entry);
                        Shutdown();
                        return (!ITS_SUCCESS);
                    }

                    if (trTable.swap(trInst, trHandle->_instance) != ITS_SUCCESS)
                    {
                        DT_ERR(("Unable to Swap Transport Intance: %d with %d", trInst, trHandle->_instance));
                        if (cer)
                        {
                            DT_DBG(("Deleting DIA_CER"));
                            delete cer;
                        }
                        return (!ITS_SUCCESS);
                    }

                    DT_DBG(("Setting New Transport Instance %d", trInst));
                    trHandle->_instance = trInst;
                }

                if (DIA_PE_CONN_SPECS(entry).trHandle == NULL ||
                    DIA_PE_HANDLE(entry) == NULL)
                {
                    DT_DBG(("Setting TransportHandle and PEER_Entry"));
                    DIA_PE_HANDLE(entry) = trHandle;
                    DIA_PE_INST(entry) = GetInstance();
                }

                DIA_PE_ACC_SPECS(entry).trHandle = trHandle;
                DIA_PE_ACC_SPECS(entry).trInst = GetInstance();
                SetPeer(entry);
                if (GetType() == ITS_DIA_SERVER_DYN_SOCK_TRANS)
                {
                    DIA_PE_ACC_TINFO(entry).type = ITS_DIA_T_TCP;
                }
                else if(GetType() == ITS_DIA_SCTP_SERVER_DYN_SOCK_TRANS)
                {
                     DIA_PE_ACC_TINFO(entry).type = ITS_DIA_T_SCTP;
                }

                DT_DBG(("Transport Type: %d", DIA_PE_ACC_TINFO(entry).type));

                DIA_INC_PEER_CER_RECEIVED(entry);
                DIA_INC_PEER_TOTAL_REQUEST_RECEIVED(entry);

                DT_DBG(("Succesfully Set Acceptor Handle for %s", hostName));

                if ((ret = DiaMsgRouter::UpdatePeerSM(cer, entry,
                                                      PEER_EVT_R_CONN_CER,
                                               trHandle, event)) == ITS_SUCCESS)
                {
                    //Increment the stats for first CER's
                    /*
                     * Fix for Issue1489:
                     * (coredump after receiving CER from Unknown Peer)
                     */
                    if (trHandle != NULL)
                    {
                        ((DiaPeerSockTransport *)trHandle)->UnsetFirstCERFlag();
                        ((DiaPeerSockTransport *) trHandle)->SetTLSHandShakeComplete();
                    }
                }
                else
                {
                    /* Fix for Issue 1681 - (due to double delete)*/
#if 0
                    if (cer)
                    {
                        delete cer;
                    }
#endif
                    DT_ERR(("Failed to handle CER ret = %d", ret));
                }
            }
            else
            {
                DT_DBG(("Could not find entry in PEER_TABLE for HostName: %s and RealName: %s", hostName, realmName));

                ITS_OCTET *buff = NULL;
                int len = 0;
                int resultCode = 0;
                DIA_CEA *cea = NULL;
                cea = itsDiaConfig.GetLocalCEA();
                ((DIA_HDR&)((DIA_GEN_CMD *)cea)->getHeader()).hh =
                ((DIA_HDR&)((DIA_GEN_CMD *)cer)->getHeader()).hh;

                ((DIA_HDR&)((DIA_GEN_CMD *)cea)->getHeader()).ee =
                ((DIA_HDR&)((DIA_GEN_CMD *)cer)->getHeader()).ee;
                resultCode = PEER_TABLE->GetCERFailureResultCode(hostName,realmName);

		if( (NULL != entry) && ((DIA_PE_IS_FORCE_DISCONNECTED(entry)) || (ipVerify ==false)) )
		{
			resultCode = ITS_DIA_UNKNOWN_PEER;
		}

                cea->setResultCode(ResultCode(resultCode));

                /* set the 'E' bit if the result code is not success*/
                if(resultCode != ITS_DIA_SUCCESS)
                {
                    (((DIA_HDR&)((DIA_GEN_CMD *)cea)->getHeader()).flags).e=1;
                }

                DT_DBG(("Send CEA"));
                if (DIA_TRACE()->IsEnabled() && DIA_TRACE()->IsEnabled(DIA_DEBUG))
                {
                    cout << *cea << endl;
                }

                if (DiaUtils::EncodeMsg(cea, &buff, len) != ITS_SUCCESS)
                {
                    DT_ERR(("Failed to Encode CEA"));
                    return (!ITS_SUCCESS);
                }

                ret = DiaMsgRouter::SendToPeer(trHandle, buff, len);
                DIA_Alarm(15006, __FILE__, __LINE__, "No match of Origin-Host/Origin-Realm in peer tables");
                if (ret != ITS_SUCCESS)
                {
                    DT_ERR(("SendCEA:: Failed to send CEA to Peer. RetVal: %d", ret));
                }
                free((char*) buff);
                buff = NULL;

                if (cer)
                {
                    DT_DBG(("Deleting DIA_CER"));
                    delete cer;
                }

                DT_WRN(("CER Received from Unknown Peer"));

                DT_WRN(("Invoke AuthorizePeer Callback"));
                /* Invoke Authorize Peer Callback
                   Pass the Peer Information in the Callback
                   If the User has registered the callback, and wants to accept this
                   peer, (based on return value) create and entry in
                   the peer table and submit to state machine
                   Default Handling will be to reject this peer
                */
		/*Updatng the Peer stats for CONNECTION_CLOSE_BY_DRE and ONNECTION_TOTAL_TRANSPORT_DOWN are removed , since they are not valid for Unknowm peer*/
		if( (NULL != entry) && (DIA_PE_IS_FORCE_DISCONNECTED(entry)))
		{
			DIA_INC_PEER_CONNECTION_CLOSE_BY_DRE_COUNT(entry);
	   		DIA_INC_PEER_CONNECTION_TOTAL_TRANSPORT_DOWN_COUNT(entry);
		}
                Shutdown();
            }
        }
        catch(...)
        {
            DT_ERR(("Failed to decode CER"));
            DIA_Alarm(15100, __FILE__, __LINE__, "CmdCode =%d",DIA_MSG_CE);
            PEER_ENTRY *peerEntry = GetPeer();
            if (peerEntry != NULL)
            {
                DT_DBG(("Setting Peer tate to PEER_ST_CLOSED"));
                DIA_PE_STATE(peerEntry) = PEER_ST_CLOSED;
                DIA_INC_PEER_CONNECTION_CLOSE_BY_DRE_COUNT(peerEntry);
                DIA_INC_PEER_CONNECTION_TOTAL_TRANSPORT_DOWN_COUNT(peerEntry);
            }
            Shutdown();
        }
    }
    else
    {
        DT_ERR(("Received CEA, when expecting CER"));
        DT_ERR(("Discarding::Shutdown Connection"));
        PEER_ENTRY *peerEntry = GetPeer();
        if (peerEntry != NULL)
        {
            DIA_INC_PEER_CONNECTION_CLOSE_BY_DRE_COUNT(peerEntry);
            DT_DBG(("Setting Peer tate to PEER_ST_CLOSED"));
            DIA_PE_STATE(peerEntry) = PEER_ST_CLOSED;
            DIA_INC_PEER_CONNECTION_TOTAL_TRANSPORT_DOWN_COUNT(peerEntry);
        }
        Shutdown();
    }
    return (ITS_SUCCESS);
}

int
DiaAcceptorReader::HandleMessage(ITS_EVENT *event)
{
    if (event == NULL)
    {
       DT_ERR(("Received Null ITS_EVENT. Returning.."));
       return (!ITS_SUCCESS);
    }

    int ret = ITS_SUCCESS;;
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

    DT_DBG(("Received Event with Length: %d From Source: %d TransInstance: %d\n", event->len, event->src, trInst));

    /* TODO Steps:
     *  1: Decode the Event
     *  2: Recover the Identity from the Message
     *     (hostname, realmname)
     *  3. Lookup the Peer Table with the identity as the key
     *  4.
     *    a. If an Entry is not found in the Peer Table
     *     This is the first message from this peer.
     *     Check the message type: It has to be a CER. (section 5.6.1)
     *     If it not CER discard the message and drop the connection
     *     ie. basically return from this function setting the
     *     doExit flag to true.
     *     If it is CER,
     *     Create an Entry in the Peer Table: Store the instance of
     *     this dynamic in the Peer Table. Very Important
     *     Submit the message to Peers State Machine for Message Handling
     *    b. If an Entry is found in the Peer Table
     *       Recover the Entry and Submit the message to the Peer State
     *       Machine to handle the event
     *
     */
    cmdCode = DiaUtils::DataToUInt(&msg[5], (sizeof(ITS_UINT) - 1));
    DT_DBG(("Received Cmd = %d", cmdCode));

    if( versionNum != DIA_VERSION)
    {
         DT_WRN(("Invalid Version Number in Header "));
         DIA_Alarm(15400, __FILE__, __LINE__, "InvalidVersion=%d:CommandCode=%d",versionNum,cmdCode);
    }

    if (IsAwaitFirstCER())
    {
        DT_DBG(("Handling First CER..."));
        int iRetVal = 0;
        if ((iRetVal=HandleFirstCER(event)) != ITS_SUCCESS)
        {
           DT_ERR(("Error in handling First CER. RetVal: %d", iRetVal));
        }
        UPDATE_DIA_STATS_REQIN(DIA_MSG_CE);
	return (ITS_SUCCESS);
    }

    if ((entry = GetPeer()) == NULL)
    {
        /* Fatal Error */
    }

    try
    {
        switch (cmdCode)
        {
        case DIA_MSG_CE:
        {
            DT_DBG(("Decoding CE"));
            ret = DiaUtils::DecodeMsg(&cmd, msg, msgLen);
            if (cmd == NULL || ret != ITS_SUCCESS)
            {
                DT_ERR(("Decode Failure. Retval: %d", ret));

                /* Send Error Response if the cmd is request*/
                if (REQUEST_BIT_SET(cmdFlag))
                {
                    ret = DiaErrHandler::HandleError(trInst, msg, ret);
                }

                return (ret);
            }

            if (REQUEST_BIT_SET(cmdFlag))
            {
                evtType = PEER_EVT_R_RCV_CER;
		        DIA_INC_PEER_CER_RECEIVED(entry);
            }
            else
            {
                evtType = PEER_EVT_R_RCV_CEA;
		        DIA_INC_PEER_CEA_RECEIVED(entry);
            }

            DT_DBG(("Received CE Command Type: %d", evtType));
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
                evtType = PEER_EVT_R_RCV_DWR;
		        DIA_INC_PEER_DWR_RECEIVED(entry);
            }
            else
            {
                evtType = PEER_EVT_R_RCV_DWA;
		        DIA_INC_PEER_DWA_RECEIVED(entry);
            }

            DT_DBG(("Received DW Command Type: %d", evtType));
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
                evtType = PEER_EVT_R_RCV_DPR;
                DIA_INC_PEER_DPR_RECEIVED(entry);
            }
            else
            {
                evtType = PEER_EVT_R_RCV_DPA;
                DIA_INC_PEER_DPA_RECEIVED(entry);
            }

            DT_DBG(("Received DP Command Type: %d", evtType));
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
        DT_DBG(("Application Spec Message Received: cmdCode %d", cmdCode));
        cmd = NULL;
        evtType = PEER_EVT_R_RCV_MESSAGE;
        DT_DBG(("Received Application Spec Command Type: %d", evtType));

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
            DT_DBG(("Succesfully Updated Peer SM"));
        }
        else
        {
            DT_ERR(("Failed to Handle Message in Peer SM = %d", ret));
            return (ITS_DIA_EINVALID_PEER_STATE);
        }
    }
    catch (NoSuchAttributeException& e) //Fixing Big parameter passing by value
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));
        return (!ITS_SUCCESS);
    }
    catch (WrongCommandTypeException& e) //Fixing Big parameter passing by value
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));
        return (!ITS_SUCCESS);
    }
    catch (UnknownTypeException& e) //Fixing Big parameter passing by value
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));
        return (!ITS_SUCCESS);
    }
    catch (CodecException& e) //Fixing Big parameter passing by value
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));
        return (!ITS_SUCCESS);
    }
    catch (...)
    {
        DT_ERR(("DiaAcceptorReader::HandleMessage: Unknown Exception Caught:"));
        return (!ITS_SUCCESS);
    }

    return (ITS_SUCCESS);

}

int
DiaAcceptorReader::Read(ITS_EVENT *event)
{
    if (event == NULL)
    {
       DT_ERR(("Received NULL ITS_EVENT"));
       return (!ITS_SUCCESS);
    }

#ifdef TLS_ENABLED
    if(!IsTLSHandShakeComplete() && startTLSHandShakeFirst )
    {
        if(TlsServerProcedure(trHandle->GetSocket()->GetSocketInfo(),trHandle)==ITS_SUCCESS)
        {
            SetTLSHandShakeComplete();
            return ITS_SUCCESS;
        }
        DT_ERR(("TLS hand shake failed.Close the connection"));
        Shutdown();
        return !ITS_SUCCESS;
    }
#endif
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
             * on socket.
             */
            DIA_PE_DWA_PENDING(GetPeer()) = 0;
            MUTEX_ReleaseMutex(&DIA_PE_MUX(GetPeer()));
        }
        if (trHandle->CheckIfMarkedDown())
        {
           //just make sure that doExit isn't set befor handling
           DT_ERR(("Transport Handle is Marked Down. Returning.."));
           return !ITS_SUCCESS;
        }
        HandleMessage(event);
    }
    else if (ret == 0)
    {
        PEER_ENTRY* pEntry = GetPeer();
        DT_ERR(("Peer %s Disconnected. Exising Tranaport", pEntry->hostIdentity));
        trHandle->SetExit();
        ret = HandleSocketError(pEntry);
        return !ITS_SUCCESS;
    }
    else
    {
        DT_ERR(("Failed to read event ret = %d", ret));
        DIA_Alarm(15100, __FILE__, __LINE__, "ret =%d", ret);
        return !ITS_SUCCESS;
    }
    return ITS_SUCCESS;
}

void
DiaAcceptorReader::Execute(void *arg)
{
    HMIThread_Info* hmiInfo = NULL;
    int i = 0, ret = 0, readCount;
    int threadCancelType;
    ITS_EVENT event;
    ITSDiaConfig *cfg = &itsDiaConfig;
    ITS_EVENT_INIT(&event, ITS_DIA_SRC, 0);
#if defined(linux) && !defined(USE_SELECT)
    struct epoll_event epollEvts[MAX_PEER_CONNS];
#endif

    DT_DBG(("DiaAcceptorReader::Execute"));

    ITS_INT thrID = THREAD_GetCurrentThreadID();
    hmiInfo = HMI_AddToMonList(&monList, "DiaAcceptorReader", (ITS_THREAD*)thrID);
    while (!_doExit)
    {
        ITS_EVENT_TERM(&event);
        if(cfg->IsHMIEnabled())
        {
            HMI_ResetCounter(hmiInfo);
        }
#if !defined(linux) || defined(USE_SELECT)
        ret = accSelectTbl.SelectSock();
        if (ret == 0)
        {
            continue;
        }
        //for(i=0; i < accSelectTbl.fdCount; i++)
        for(i=0, readCount=0; i < MAX_PEER_CONNS; i++)
        {
            /* IMP keep the valid reference for trHandle*/
            trHandle = accSelectTbl.desc[i];
            if(trHandle && accSelectTbl.IsReadable(trHandle->_socketFd))
            {
                Read(&event);
                readCount++;
            }

            if (ret == readCount)
                break;
        }
#else
        ret = accEpollTbl->EpollWait(epollEvts);
        if (ret < 0)
        {
            DT_ERR (("epoll_wait failed with error %d.",errno));
            continue ;
        }
        for(i=0;i<ret;i++)
        {
            /* IMP keep the valid reference for trHandle*/
            trHandle = (DiaSocketTransport *)epollEvts[i].data.ptr;
            if (trHandle != NULL)
            {
                if (epollEvts[i].events & EPOLLIN)
                {
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

    DT_DBG(("Exiting DiaAcceptorReader::Execute"));
    HMI_RemoveFromMonList(&monList, (ITS_THREAD*)thrID);
    return;
}

void
DiaAcceptor::AcceptConnections()
{
    fd_set acptfd;
    fd_set tempfd;
    struct timeval tv;
    ITSDiaConfig *cfg = &itsDiaConfig;
    HMIThread_Info* hmiInfo = NULL;
    ITS_INT thrID = THREAD_GetCurrentThreadID();
    ITS_SocketInfo * info  = ((its::ServerSocket *)_socket)->GetSocketInfo();

    FD_ZERO(&acptfd);
    FD_SET(info->socket, &acptfd);

    hmiInfo = HMI_AddToMonList(&monList, "PeerConnAcceptor", (ITS_THREAD*)thrID);

    DT_DBG(("DiaAcceptor::AcceptConnections"));

    while (!_doExit)
    {
        int ret = !ITS_SUCCESS;
        its::Socket *connection = NULL;

        tv.tv_sec = 1;
        tv.tv_usec = 0;
        memcpy(&tempfd, &acptfd, sizeof(acptfd));

        int rCode =  select(info->socket+1, &tempfd, NULL, NULL, &tv);

        if(rCode < 0)
        {
            DT_ERR(("Select failed with error %d.",errno));
        }

        /* Reset HMI Counter */
        if(cfg->IsHMIEnabled())
        {
            HMI_ResetCounter(hmiInfo);
        }

        if (rCode == 0)
        {
            continue ;
        }

        if (FD_ISSET(info->socket, &tempfd))
        {
            if ( GetType() == ITS_DIA_SERVER_SOCK_TRANS )
            {
                if (info->af == AF_INET6)
                {
                    ret = ((its::ServerSocket *)
                                      _socket)->Accept_Ipv6(&connection, true);
                }
                else
                {
                    ret = ((its::ServerSocket *)_socket)->Accept(&connection, true);
                }
            }
            else if ( GetType() == ITS_DIA_SCTP_SERVER_SOCK_TRANS )
            {
#if defined(linux)
                if (info->af == AF_INET6)
                {
                    ret = ((its::LKSctpServerSocket *)
                                      _socket)->Accept_Ipv6(&connection);
                }
                else
                {
                    ret = ((its::LKSctpServerSocket *)
                                      _socket)->Accept(&connection);
                }
                ITS_SocketInfo *sockInfo = connection->GetSocketInfo();
                sockInfo->ppid = SCTP_PPID_FOR_CLEAR_TEXT;
                connection->SetSocketInfo(sockInfo);
#elif defined(solaris) || defined(solaris64)
                if (info->af == AF_INET6)
                {
                    ret = ((its::SKSctpServerSocket *)
                                      _socket)->Accept_Ipv6(&connection, true);
                }
                else
                {
                    ret = ((its::SKSctpServerSocket *)_socket)->Accept(&connection, true);
                }

#endif
            }
            //related to NULL check of connection variable
            if ((ret == ITS_SUCCESS) && (connection != NULL))
            {
                //Check if we are Standby node and close the socket.
                if(m_bDropNewConnections)
                {
                    DT_ERR(("Received a new connection request when in Standby, hence closing the Connection."));
                    delete connection;
                    connection = NULL;
                    continue;
                }
                DT_DBG(("Accepting connections...\n"));

                PEER_ENTRY *entry = PeerTable::GetPeerTable()->FindFirstEntry();
                int index = 1;
                bool found = false;
                bool slotFull = false;
                ITS_SocketInfo *info = connection->GetSocketInfo();
                char strIpAddr[64];
                char *ptr = strIpAddr;
		        memset ( strIpAddr, '\0', 64 );
                if (info->af == AF_INET6)
                {
                    connection->GetIpAddress(&ptr, 64, ITS_FALSE);
                }
                else
                {
                    connection->GetIpAddress(&ptr, 64, ITS_TRUE);
                }

                DT_DBG(("Accepted Connection From IpAddress: %s", ptr));

                while(entry != NULL)
                {

                    DIA_TRANS_TYPE type = DIA_PE_CONN_SPECS(entry).tInfo[0].type;

                    index = DIA_PE_INDEX(entry);

                    if (type == ITS_DIA_T_TCP)
                    {
                        const char *ip = DIA_PE_CONN_SPECS(entry).tInfo[0].
                                                           serverIpAddr;
                        /**
                         * Splitting the checks to see if the connector/acceptor
                         * slots are already in use. Fix for issue no 3 raised
                         * during the validation of bcgi ticket 1807.
                         */

			if (!(cfg->IsPeerIpCheckEnabled()) ||
                              (strncmp(strIpAddr, ip, 64) == NULL))
                        {
                            if (trTable.getAt(index+1) == NULL)
                            {
                                DiaSocketTransport* tr = trTable.getAt(index);
                                if (tr == NULL ||
                                    tr->CheckIfMarkedDown() == false)
                                {
                                    found = true;
                                    break;
                                }
                                else
                                {
                                    slotFull = true;
                                    DT_DBG(("The TCP Transport slot for peer"\
                                    ": %s is in use.\n", strIpAddr));
                                }
                            }
                            else
                            {
                                slotFull = true;
                                DT_DBG(("The TCP Transport slot for peer"\
			        ": %s is in use.\n", strIpAddr));
                            }
                        }
                    }
                    else if (type == ITS_DIA_T_SCTP)
                    {
                        const char **multihomeips = DIA_PE_CONN_SPECS(entry).
                                                tInfo[0].multiHomeipaddrs;
                        ITS_USHORT no_ips = DIA_PE_CONN_SPECS(entry).
                                               tInfo[0].noIPs;

                        for(int i=0;i < no_ips;i++)
                        {
                            /**
                             * Splitting the checks to see if the connector/acceptor
                             * slots are already in use. Fix for issue no 3 raised
                             * during the validation of bcgi ticket 1807.
                             */
                            if (!(cfg->IsPeerIpCheckEnabled()) ||
                                (strncmp(strIpAddr, multihomeips[i],
                                64)) == NULL )
                            {
                                if (trTable.getAt(index+1) == NULL)
                                {
                                    DiaSocketTransport* tr = trTable.getAt(index);
                                    if (tr == NULL ||
                                        tr->CheckIfMarkedDown() == false)
                                    {
                                        found = true;
                                        break;
                                    }
                                    else
                                    {
                                        slotFull = true;
                                        DT_DBG(("The SCTP Transport slot for peer"\
                                        ": %s is in use.\n", strIpAddr));
                                    }
                                }
                                else
                                {
                                    slotFull = true;
                                    DT_DBG(("The SCTP Transport slot for peer"\
                                    ": %s is in use.\n", strIpAddr));
                                }
                            }
                        }
                    }
                    if(found == true)
                    {
                        break;
                    }
                    entry = PeerTable::GetPeerTable()->FindNextEntry(entry);
                }
                if (found == false )
                {
                    /**
                     * Check the flag to see if the connector/acceptor
                     * slots are already in use, else the peer is not
                     * configured through xml or added dynamically.
                     */
                    if (slotFull == false)
                    {
                        DT_WRN(( "Accepting connection from: %s  peer"\
                            " not configured\n", strIpAddr));
                    }

                    /**
                     * BW Issue 2006
                     */
                    if(connection != NULL)
                    {
                        delete connection;
                        connection = NULL;
                    }
                    continue;
                }
                else
                {
                    if (DIA_PE_DSCP_EN(entry) == ITS_TRUE)
                    {
                        connection->SetDscpMarking(DIA_PE_DSCP_VAL(entry));
                    }
                }

                //reserve the accepting slot for the peer
                DiaPeerSockTransport *dyn = NULL;
                DT_DBG(("Starting acceptor...\n"));
                _noDynamics++;
                try
                {   int type;
                    type = GetType();
                    dyn = new DiaPeerSockTransport(type, index, DIA_TRANS_ACCEPTOR);

                    if (dyn)
                    {
                        dyn->SetConnection(connection);
                        dyn->SetPeer(entry);

                        //DIA_PE_INIT_CONN(entry) = false;
                        //DIA_PE_INIT_COUNT(entry) = 0;
#if !defined(linux) || defined(USE_SELECT)
                        ret = accSelectTbl.SetSelectSock(dyn);
#else
                        ret = accEpollTbl->SetEpollSock(dyn);
#endif
                        if (ret != ITS_SUCCESS)
                        {
                            DT_ERR(("Error while Setting fdset"));
                            if (dyn)
                            {
                                delete dyn;
                                dyn = NULL;
                            }
                        }
                        DT_DBG(("Started acceptor...\n"));
                    }
                }
                catch(...)
                {
                    DT_ERR(("Couldn't start the acceptor : acceptor connection failed\n"));
                    if (dyn)
                    {
                        delete dyn;
                    }
                }
	        DIA_INC_PEER_CONNECTION_CONNECTION_SUCCESS_COUNT(entry);
            }
            else
            {
                DT_CRT(("Couldn't accept connection: %d.\n", ret));
            }
        }
    }
    HMI_RemoveFromMonList(&monList, (ITS_THREAD*)thrID);
}

void
DiaAcceptor::Execute(void *arg)
{
    AcceptConnections();
}

int
DiaAcceptorReader::HandleSocketError(PEER_ENTRY *pEntry)
{
    int ret = 0;

#if !defined(linux) || defined(USE_SELECT)
    accSelectTbl.UnsetSelectSock(trHandle->_fdIndex);
#else
    accEpollTbl->DelEpollSock(trHandle);
#endif
    if (DIA_PE_STATE(pEntry) == PEER_ST_CLOSED)
    {
        DT_WRN(("Peer is in Closed State"));
        //NOTE: Need to integrate this below dia stats count
        //DIA_INC_PEER_CONNECTION_CLOSE_BY_STACK_COUNT(pEntry);
        DIA_INC_PEER_CONNECTION_TOTAL_TRANSPORT_DOWN_COUNT(pEntry);
        /* Pass Null since fd already removed */
        Shutdown(NULL);
        DIA_PE_ACC_SPECS(pEntry).trHandle = NULL;
        DIA_PE_ACC_SPECS(pEntry).trInst = 0;
        if (DIA_PE_RETRY_TIMER(pEntry) != TIMER_BAD_SERIAL)
        {
            PeerTable::StopTimer(RETRY, pEntry);
        }
        //RFC3588 complaint implementation
        if(DIA_PEER_GET_DIS_CAUSE(pEntry) != DisconnectCause::DO_NOT_WANT_TO_TALK_TO_YOU)
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
    if ( (ret = DiaMsgRouter::UpdatePeerSM(NULL, GetPeer(),
                    PEER_EVT_R_PEER_DISC,
                    trHandle, NULL)) == ITS_SUCCESS)
    {
        DT_DBG(("Succesfully Submitted Message to Peer SM with Peer State PEER_EVT_R_PEER_DISC"));
    }
    else
    {
        DT_ERR(("Failed to Handle Message in Peer SM for Setting Peer State: PEER_EVT_R_PEER_DISC With Retval= %d", ret));
    }

    Shutdown(accEpollTbl);
    return !ITS_SUCCESS;
}
