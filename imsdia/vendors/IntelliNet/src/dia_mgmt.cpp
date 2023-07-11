/**************************-*-Dia-*-*************************************
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
 *  LOG: $Log: dia_mgmt.cpp,v $
 *  LOG: Revision 3.72.4.16.4.21.2.3.2.10.4.1.2.1.4.1.2.3  2020/02/14 11:36:11  jkchaitanya
 *  LOG: TCP Timeout fix ported from DRE
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.21.2.3.2.10.4.1.2.1.4.1.2.2  2017/12/21 04:37:21  jkchaitanya
 *  LOG: Ticket 1149 changes to support case insensitivity for peers, hosts 7 realms
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.21.2.3.2.10.4.1.2.1.4.1.2.1  2014/12/04 12:00:26  pramana
 *  LOG: Added support for allowing requests for a different hosts
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.21.2.3.2.10.4.1.2.1.4.1  2014/09/16 09:52:26  jsarvesh
 *  LOG: Chnages done for Peer wise Statistics enhancement
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.21.2.3.2.10.4.1.2.1  2014/07/02 06:37:11  millayaraja
 *  LOG: updated to handle answer message without mandatory field missing
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.21.2.3.2.10.4.1  2014/02/12 07:15:00  millayaraja
 *  LOG: changes done for conditional compilation for IWF/DRE and IWF specific changes
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.21.2.3.2.10  2013/12/27 12:47:28  ncshivakumar
 *  LOG: Fix for bug Bug 2639
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.21.2.3.2.9  2013/12/16 09:33:51  ncshivakumar
 *  LOG: Added the trace wgile adding a peer with securePort
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.21.2.3.2.8  2013/12/13 09:34:58  vsarath
 *  LOG: Merged the session-splict changes
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.21.2.3.2.7  2013/12/11 06:26:25  ncshivakumar
 *  LOG: Fixed bug 2444
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.21.2.3.2.6  2013/12/09 04:52:26  ncshivakumar
 *  LOG: Fixed bug 2439,2443,2368,1898
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.21.2.3.2.5  2013/11/14 08:54:54  ncshivakumar
 *  LOG: RFC6733 changes
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.21.2.3.2.4  2013/10/28 07:11:06  ncshivakumar
 *  LOG: Updated application id
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.21.2.3.2.3  2013/10/26 07:42:21  ncshivakumar
 *  LOG: RFC 6733 changes
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.21.2.3.2.2  2013/09/10 08:36:39  ncshivakumar
 *  LOG: RFC6733 Changes
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.21.2.3.2.1  2013/07/31 07:32:20  vsarath
 *  LOG: Fix for coverity warnings
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.21.2.3  2013/06/07 05:19:38  jkchaitanya
 *  LOG: Bug 1615,1614, ReviewRequest 1018
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.21.2.2  2013/05/24 10:35:56  ncshivakumar
 *  LOG: Fix for bug 1580
 *  LOG:  VS: ----------------------------------------------------------------------
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.21.2.1  2013/05/10 08:49:52  ncshivakumar
 *  LOG: Updated for Static routing table configuaration
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.21  2013/04/16 09:43:33  ncshivakumar
 *  LOG: Updated for bug1418
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.20  2013/04/16 05:41:00  ncshivakumar
 *  LOG: Changes for bug1418
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.19  2013/04/12 04:17:35  vsarath
 *  LOG: Logs improvement
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.18  2013/04/01 05:49:44  vsarath
 *  LOG: Fix for Coverity warnings
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.17  2013/03/28 08:48:54  vsarath
 *  LOG: Added for the Dynamic Loading of DTF Plugins
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.16  2013/03/15 11:10:56  mallikarjun
 *  LOG: BUG-1013-Chages
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.15  2013/03/12 04:50:22  vsarath
 *  LOG: Fix for coverity issue
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.14  2013/03/06 09:12:26  ncshivakumar
 *  LOG: Update for multihoming
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.13  2013/03/06 08:31:00  jvikram
 *  LOG: BUGID=1016, 1027, 803. Fixed the specified bugs.
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.12  2013/03/05 06:53:06  ncshivakumar
 *  LOG: Multihome changes
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.11  2013/02/27 08:49:07  jvikram
 *  LOG: Warnings raised by Coverity have been fixed
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.10  2013/02/25 13:16:24  mallikarjun
 *  LOG: Bug 623 changes
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.9  2013/02/21 11:17:07  ncshivakumar
 *  LOG: Modified for multitransport support
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.8  2013/02/21 10:20:45  jkchaitanya
 *  LOG: Mar31 CMAPI Features
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.7  2013/02/21 04:54:14  jsarvesh
 *  LOG: added one more error enum for deleting a peer from realm with wrong vendor id
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.6  2013/02/19 11:05:57  jsarvesh
 *  LOG: dre global stats implementation
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.5  2013/02/18 10:00:29  jsarvesh
 *  LOG: debug log changed for localhost configuration
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.4  2013/02/01 11:34:15  pramana
 *  LOG: Merged from branch 0212 to 0300.
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.3  2013/01/30 04:15:57  pramana
 *  LOG: Used std::string in AssociateDict.
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.2  2013/01/29 11:39:32  pramana
 *  LOG: DDL Changes
 *  LOG:
 *  LOG: Revision 3.72.4.16.4.1  2013/01/29 09:38:06  mallikarjun
 *  LOG: Alternate Peer Crash Resolution
 *  LOG:
 *  LOG: Revision 3.72.4.18  2013/01/25 08:25:16  rgovardhan
 *  LOG: delete last destination error fix
 *  LOG:
 *  LOG: Revision 3.72.4.17  2013/01/18 04:48:00  jsarvesh
 *  LOG: cppcheck changes
 *  LOG:
 *  LOG: Revision 3.72.4.16  2013/01/08 02:27:58  cprem
 *  LOG: Added returing appropriate error codes
 *  LOG:
 *  LOG: Revision 3.72.4.15  2013/01/04 11:10:36  rgovardhan
 *  LOG: Fix for bug 850
 *  LOG:
 *  LOG: Revision 3.72.4.14  2013/01/03 07:47:40  rgovardhan
 *  LOG: Fix for bugs 797 and 815
 *  LOG:
 *  LOG: Revision 3.72.4.13  2012/12/26 09:43:32  mallikarjun
 *  LOG: bug-743-changes
 *  LOG:
 *  LOG: Revision 3.72.4.12  2012/12/21 09:53:33  rgovardhan
 *  LOG: Merge from CMGR branch
 *  LOG:
 *  LOG: Revision 3.72.4.8.2.5  2012/12/20 04:47:31  millayaraja
 *  LOG: modified for Logger Config of DTF
 *  LOG:
 *  LOG: Revision 3.72.4.8.2.4  2012/12/16 12:16:43  rgovardhan
 *  LOG: Logging Configuration for DTF
 *  LOG:
 *  LOG: Revision 3.72.4.8.2.3  2012/12/16 12:01:55  rgovardhan
 *  LOG: modify peer fixes
 *  LOG:
 *  LOG: Revision 3.72.4.8.2.2  2012/12/16 08:41:41  rgovardhan
 *  LOG: Private build bugs fix
 *  LOG:
 *  LOG: Revision 3.72.4.8.2.1  2012/12/12 12:12:16  rgovardhan
 *  LOG: DRE Config related and dia_mgmt changes
 *  LOG:
 *  LOG: Revision 3.72.4.8  2012/11/20 17:39:44  pramana
 *  LOG: Merged from CMAPI branch for 212-07 release
 *  LOG:
 *  LOG: Revision 3.72.4.2.8.6  2012/11/20 10:31:24  rgovardhan
 *  LOG: merge from 00 Nov20Rel
 *  LOG:
 *  LOG: Revision 3.72.4.2  2012/10/17 14:31:37  jsarvesh
 *  LOG: modification for dictionary id
 *  LOG:
 *  LOG: Revision 3.72.4.1  2012/09/06 11:30:45  jvikas
 *  LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
 *  LOG:
 *  LOG: Revision 3.72.6.1  2012/08/27 11:05:22  cprem
 *  LOG: Added json includes.
 *  LOG:
 *  LOG: Revision 3.72  2011/07/14 14:04:51  vkumara
 *  LOG: ForceDisconnect Requirement - Not to initiate connection.
 *  LOG:
 *  LOG: Revision 3.71  2010/12/14 14:43:51  nvijikumar
 *  LOG: Stop RETRY timer for disconnnectAllPeers (DO_NOT_WANT_TO_TALK_TO_YOU)
 *  LOG: discause even in CLOSED state
 *  LOG:
 *  LOG: Revision 3.70  2010/12/14 00:39:27  nvijikumar
 *  LOG: Changes not to initiate peer connection if RETRY timer already running
 *  LOG:
 *  LOG: Revision 3.69  2010/10/01 05:14:18  vkumara
 *  LOG: startAllPeers MML command allowed for both static/dynamic peers
 *  LOG:
 *  LOG: Revision 3.68  2010/09/30 06:42:59  vkumara
 *  LOG: MML commands to set/get DSCP
 *  LOG:
 *  LOG: Revision 3.67  2010/09/20 05:13:32  nvijikumar
 *  LOG: 1. trIndx -1 is invalid for unsigned short
 *  LOG: 2. Introduced delay in dynamic peer start (dia_mgmt.cpp)
 *  LOG:
 *  LOG: Revision 3.66  2010/08/27 12:28:12  nvijikumar
 *  LOG: DSCP value support (IP header) - Vasanth
 *  LOG:
 *  LOG: Revision 3.65  2010/08/19 11:21:26  nvijikumar
 *  LOG: Porting changes from B-MOTO-IDIA-0421-00
 *  LOG: 1. New Overload implimentation changes are not being ported.
 *  LOG: 2. Force disconnect changes are not being ported.
 *  LOG:
 *  LOG: Revision 3.64  2010/07/07 08:24:46  nvijikumar
 *  LOG: TCS compilation flags support
 *  LOG:
 *  LOG: Revision 3.63  2010/01/28 13:15:45  sureshj
 *  LOG: Fix for modify priority issue HelpDesk Ticket 2298. Entire Route entry
 *  LOG: is removed from the Realmtable when tried to modifyPriority.
 *  LOG:
 *  LOG: Revision 3.62  2009/10/14 10:37:44  sureshj
 *  LOG: forceDisconectPeer, getPeerTimers, GetLocalHostInfo mml commands
 *  LOG: added. (motorola helpDesk issues 2219, 2238).
 *  LOG:
 *  LOG: Revision 3.61  2009/09/07 05:01:02  rajeshak
 *  LOG: MML Support to set/get HMI Heartbeat interval.
 *  LOG:
 *  LOG: Revision 3.60  2009/08/26 11:57:16  rajeshak
 *  LOG: Fix for Issue:2328(IDS dumps core when trying to remove peer which
 *  LOG: is only destination in Realm)
 *  LOG: Fixed issue in RemoveAllDestination function.
 *  LOG:
 *  LOG: Revision 3.59  2009/08/24 04:46:27  rajeshak
 *  LOG: Fix for Issue 2319. (IDS sends messages to first destination entry
 *  LOG: in Realm Table even though it has lesser priority than other Peer,
 *  LOG: after changing its Priority using "modifyPriority" MML command.)
 *  LOG: Reordering Destination entries after ModifyPriority.
 *  LOG:
 *  LOG: Revision 3.58  2009/08/13 11:43:59  rajeshak
 *  LOG: Inserting peers into realmEntry destination list based on priority
 *  LOG:
 *  LOG: Revision 3.57  2009/07/24 09:30:28  rajeshak
 *  LOG: Changes done for
 *  LOG:  1. new MML Command to print and remove default route
 *  LOG:  2. Stats changes (to include option to clear stats in get)
 *  LOG:
 *  LOG: Revision 3.56  2009/07/15 11:31:35  rajeshak
 *  LOG: Added Check to verify HMITimeout is less than HMICheckInterval before set.
 *  LOG:
 *  LOG: Revision 3.55  2009/07/14 10:05:46  rajeshak
 *  LOG: Changes done to include peer realm name  in destination.
 *  LOG:
 *  LOG: Revision 3.54  2009/07/13 06:47:22  rajeshak
 *  LOG: 1. Reverting back session table changes.
 *  LOG: 2. MML command to set/get the HMI Retry.
 *  LOG:
 *  LOG: Revision 3.53  2009/06/29 14:44:41  rajeshak
 *  LOG: 1. MML Commands added to set HMI Check Interval and Timeout.
 *  LOG: 2. Changes for Queue stats and session table size.
 *  LOG:
 *  LOG: Revision 3.52  2009/05/12 08:42:31  rajeshak
 *  LOG: Klockwork reported Issue fix.
 *  LOG:
 *  LOG: Revision 3.51  2009/05/11 06:25:24  rajeshak
 *  LOG: 1. API to Get/Set Heartbeat Interval & retry
 *  LOG: 2. addDestination Issue Fix
 *  LOG: 3. removePeer Issue fix (not removing realm when last destination is removed)
 *  LOG:
 *  LOG: Revision 3.50  2009/04/17 10:38:09  rajeshak
 *  LOG: Changes for compilation error in static pkg
 *  LOG:
 *  LOG: Revision 3.49  2009/04/17 09:26:45  rajeshak
 *  LOG: AddDestination and RemoveDestination changes
 *  LOG:
 *  LOG: Revision 3.48  2009/04/16 04:54:36  rajeshak
 *  LOG: Fix For Issue: 1816 (IDS dumps core after diaCommit if Default RealmEntry is NULL)
 *  LOG: Added a NULL check before Printing Default Realm Section.
 *  LOG:
 *  LOG: Revision 3.47  2009/04/14 06:40:05  sureshj
 *  LOG: HMI,initiateConnsOpt, ipv6, PeerDiscovery flags added to DiaCommit.
 *  LOG:
 *  LOG: Revision 3.46  2009/04/13 13:40:19  rajeshak
 *  LOG: Peer Discovery changes and changes for new MML Modify destination Priority.
 *  LOG:
 *  LOG: Revision 3.45  2009/04/11 09:55:26  nvijikumar
 *  LOG: Provided APIs to get/set HexDump values
 *  LOG: Provided API to GetOvloadThresholds
 *  LOG:
 *  LOG: Revision 3.44  2009/04/10 06:34:54  sureshj
 *  LOG: EnableHMI. DisableHMI & IsHMIEnabled MML commands added.
 *  LOG:
 *  LOG: Revision 3.43  2009/04/07 13:52:05  sureshj
 *  LOG: MML API SetOvloadThresholds() to set overload Thresholds
 *  LOG: MinT and MaxT added for overload control feature.
 *  LOG:
 *  LOG: Revision 3.42  2009/04/07 12:39:49  rajeshak
 *  LOG: Checking Destination count before inserting into realm destination list.
 *  LOG: (fix for motorala core dump issue when no of destination is more than 64)
 *  LOG:
 *  LOG: Revision 3.41  2009/03/26 09:35:29  rajeshak
 *  LOG: GetPeerStatus MML API Support
 *  LOG:
 *  LOG: Revision 3.40  2009/03/26 05:35:09  nvijikumar
 *  LOG: GetDiaMiscStats and ResetAllStats API Support
 *  LOG:
 *  LOG: Revision 3.39  2009/03/24 09:13:02  rajeshak
 *  LOG: Removed check for static Peer to allow disconnection of statically
 *  LOG: configured peer.
 *  LOG:
 *  LOG: Revision 3.38  2009/03/19 12:39:28  nvijikumar
 *  LOG: Global instance is created for the Class ITSDiaConfig to avoid function
 *  LOG: call overhead as ITSDiaConfig::GetITSDiaConfig() was called max time
 *  LOG:
 *  LOG: Revision 3.37  2009/03/19 08:42:33  rajeshak
 *  LOG: Added function to set default route.
 *  LOG:
 *  LOG: Revision 3.36  2009/03/19 06:00:05  chandrashekharbs
 *  LOG: Local Configuration section updated with publicServerIpAddr in persisted xml
 *  LOG:
 *  LOG: Revision 3.35  2009/03/19 05:35:44  sureshj
 *  LOG: check for 0 input added for SetPeerTimers. If 0 input prev value
 *  LOG: is retained.
 *  LOG:
 *  LOG: Revision 3.34  2009/03/18 12:42:00  rajeshak
 *  LOG: Added new functions for new MML command and API.
 *  LOG:
 *  LOG: Revision 3.33  2009/03/17 10:18:43  sureshj
 *  LOG: Issue Id: 1730
 *  LOG: Description: IDS dumps core when using printRealmtable. New API added
 *  LOG: to remove all destinations of a peer when RemovePeer called.
 *  LOG:
 *  LOG: Revision 3.32  2009/03/16 13:40:26  sureshj
 *  LOG: added static configuration changes to setLocalHostInfo API.
 *  LOG:
 *  LOG: Revision 3.31  2009/03/16 04:37:05  sureshj
 *  LOG: IssueId: 1741
 *  LOG: Feature Id: None
 *  LOG: Description: MML Command: 'setAcctTimers' is taking 'realtime' value
 *  LOG: as an input parameter.
 *  LOG:
 *  LOG: Revision 3.30  2009/03/03 13:46:17  sureshj
 *  LOG: APIs added for Dynamic configuration of timers and localhost Info.
 *  LOG:
 *  LOG: Revision 3.29  2009/03/03 11:17:20  rajeshak
 *  LOG: Klockwork reported issue fix
 *  LOG:
 *  LOG: Revision 3.28  2009/03/02 04:44:36  nvijikumar
 *  LOG: Enhancements for MML API Support
 *  LOG:
 *  LOG: Revision 3.27  2009/02/11 11:08:22  chandrashekharbs
 *  LOG: Fix for Issue Id 1479 (wrong Local Server name) and
 *  LOG: issue id 1480 (newly commited file does not contain old realm section)
 *  LOG:
 *  LOG: Revision 3.26  2009/02/06 06:46:42  chandrashekharbs
 *  LOG: Fix for Issue 1475 and other possible core dump issues
 *  LOG:
 *  LOG: Revision 3.25  2009/02/04 09:37:24  chandrashekharbs
 *  LOG: changes to fix the issue 1474
 *  LOG:
 *  LOG: Revision 3.24  2009/02/04 05:54:17  nvijikumar
 *  LOG: Changes for 64 Peer support with fixed number of threads
 *  LOG: Dedicated thread initiates connections with Peers
 *  LOG:
 *  LOG: Revision 3.23  2009/01/28 06:50:07  chandrashekharbs
 *  LOG: Added changes for xml persistency
 *  LOG:
 *  LOG: Revision 3.22  2009/01/06 14:01:23  nvijikumar
 *  LOG: Removed FreeEntry API since it is duplicated with peer table API
 *  LOG:
 *  LOG: Revision 3.21  2009/01/06 10:41:48  chandrashekharbs
 *  LOG: Generate Alarm for RemovePeer only if successfylly removed
 *  LOG:
 *  LOG: Revision 3.20  2009/01/03 07:12:18  nvijikumar
 *  LOG: 1. Introduced new array to maintain the transports Slots
 *  LOG: 2. Used slots should not be allocated for newly added peers
 *  LOG:
 *  LOG: Revision 3.19  2008/12/23 14:59:23  ssaxena
 *  LOG: Fixes for Dynamic Peer Configuration issues (Viji, Yogesh, Shivendra)
 *  LOG: Issue Id:1375 and some legacy issues
 *  LOG:
 *  LOG: Revision 3.18  2008/12/22 06:30:21  sureshj
 *  LOG: Updates for statistics. return value changes.
 *  LOG:
 *  LOG: Revision 3.17  2008/12/15 05:41:08  hbhatnagar
 *  LOG: Fix for compilation issue on solaris
 *  LOG:
 *  LOG: Revision 3.16  2008/12/12 17:09:05  nvijikumar
 *  LOG: Alarm Support
 *  LOG:
 *  LOG: Revision 3.15  2008/12/12 07:58:09  sureshj
 *  LOG: Initial draft for statistics support
 *  LOG:
 *  LOG: Revision 3.14  2008/12/01 07:12:25  sureshj
 *  LOG: API to disable/disconnect Peer
 *  LOG: API to start individual Peer
 *  LOG:
 *  LOG: Revision 3.13  2008/11/22 10:55:40  ssaxena
 *  LOG: Fix for IssueId : 1292
 *  LOG: getNodeState and switchOver MML commands are not working for Redundancy
 *  LOG:
 *  LOG: Revision 3.12  2008/09/08 12:17:05  ssaxena
 *  LOG: Added APIs SwitchOver() and GetNodeState() for redundancy (Viji).
 *  LOG:
 *  LOG: Revision 3.11  2008/08/27 10:55:14  ssaxena
 *  LOG: Added failback option in addAlternatePeer command.
 *  LOG:
 *  LOG: Revision 3.10  2008/08/21 06:07:08  yranade
 *  LOG: Added APIs to print QSize, SessionTable size and SessionTable details.
 *  LOG:
 *  LOG: Revision 3.9  2008/07/24 05:30:04  ssaxena
 *  LOG: Reverting back duplicate code from DisconectPeer MML
 *  LOG:
 *  LOG: Revision 3.8  2008/07/23 12:00:37  ssaxena
 *  LOG: Provided Dynamic API to send DPR from MML (Requested by Motorola)
 *  LOG:
 *  LOG: Revision 3.7  2008/04/24 14:05:03  nanaparthi
 *  LOG: Fix for Issues #885, #891
 *  LOG:
 *  LOG: Revision 3.6  2008/04/24 06:09:06  nanaparthi
 *  LOG: Fix for Issue #907
 *  LOG:
 *  LOG: Revision 3.5  2008/04/23 11:31:45  nanaparthi
 *  LOG: Fix for Issue #881
 *  LOG:
 *  LOG: Revision 3.4  2008/04/21 12:20:01  nanaparthi
 *  LOG: Fix for Issues #849, #855, #867, #870
 *  LOG:
 *  LOG: Revision 3.3  2008/04/16 12:08:16  hbhatnagar
 *  LOG: Made changes to incorporate review comments (Avinash).
 *  LOG:
 *  LOG: Revision 3.2  2008/04/01 16:47:43  hbhatnagar
 *  LOG: Changes for Proxy and Relay support 3.0 release - (Hemant, Avinash)
 *  LOG:
 *  LOG: Revision 1.6  2008/03/27 12:14:08  hbhatnagar
 *  LOG: Converting 2.1 branch to CURRENT
 *  LOG:
 *  LOG: Revision 1.5.4.1  2008/01/05 16:39:20  avinashks
 *  LOG: Changes made to provide fix for issue no.19 raised by Dhiranand during
 *  LOG: the validation of bcgi ticket 1807.
 *  LOG:
 *  LOG: Revision 1.5  2007/01/31 16:18:29  kamakshilk
 *  LOG: Fix for Bug Id 5205. Retry timer stopped
 *  LOG:
 *  LOG: Revision 1.4  2007/01/30 09:01:06  nanaparthi
 *  LOG: Enhancements made for RemovePeer() API
 *  LOG:
 *  LOG: Revision 1.3  2007/01/29 14:07:06  nanaparthi
 *  LOG: Enhancements made for AddPeer() , AddAlternatePeer(), AddIp() APIs
 *  LOG:
 *  LOG: Revision 1.2  2007/01/23 15:30:20  nanaparthi
 *  LOG: Fix for Bug id 5205 , 5206
 *  LOG:
 *  LOG: Revision 1.1  2007/01/12 05:59:51  nanaparthi
 *  LOG: APIs for Dynamic Configuration Support
 *  LOG:
 *  LOG:
 ****************************************************************************/

#include <json/json.h>

#include <dia_err.h>
#include <dia_utils.h>
#include <dia_ip_trans.h>
#include <dia_connector.h>
#include <dia_acceptor.h>
#include <dia_peer_table.h>
#include <dia_realm_table.h>
#include <dia_msg_router.h>
#include <dia_stack.h>
#include <dia_stack_stats.h>
#include <its_dia_config.h>
#include <dia_peer_discovery.h>
#include <dia_config.h>
#include <dia_mgmt.h>
#include <map>
#include <sstream>
#include <dia_static_routing_table.h>
#include "ErrorResp.h"
#include <dia_capabilities_update_application.h>
#define EMPTYDICTIONARY 0
#ifdef DEBUG
#define DEBUGSUFFIX "D"
#else
#define DEBUGSUFFIX ""
#endif


using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;

extern void FreeEntry(PEER_ENTRY *entryParam);
extern void PrintEntry(std::ostream& os, const PEER_ENTRY* entry);
extern DiaStackStats diaStackStats;

/* For xml persistency */
extern FILE* tempfp;
static ITSDiaConfig *config = NULL;

extern bool IsDefaultEnabled();
extern bool IsSecurityEnabled();
ITS_INT tab = 0;
extern ITS_INT maxThreshold, minThreshold;

static DiaMgmt* itMgmt = NULL;

/* Added for ddl, use this array for creating the combo
 * and use the map to get the plugin for a selected combo
 */

ITS_USHORT ddlPluginArray[(MAX_DICT_IDS_PER_PEER * 2) + 1];

map<string, string> ddlPluginMap;

int
DiaMgmt::GetSessionTableSize()
{
    return SessionTable::GetSessionTable()->GetTableSize();
}

int
DiaMgmt::GetSessionTableSize(int index)
{
    return SessionTable::GetSessionTable()->GetTableSize(index);
}

int
DiaMgmt::GetSessionTableSize(DIA_ST_STATS* stStats)
{
    int count = 0;
    int numThreads = 1;
    stStats->noOfSessTables = 0;
    memset(stStats->stSize, 0 , MAX_ROUTER_THREADS);

    if (itsDiaConfig.IsQueueMgmtEnabled())
    {
        numThreads = itsDiaConfig.GetQueueMgmt().GetMsgRouterThreadCount();
    }

    stStats->noOfSessTables = numThreads;

    for (int i=0; i<numThreads; i++)
    {
        count = SessionTable::GetSessionTable()->GetTableSize(i);
        stStats->stSize[i] = count;
    }

    return ITS_SUCCESS;
}

int
DiaMgmt::GetDiaQStat(DIA_QUEUE_STATS* qStats)
{
    int count = 0;
    qStats->noOfQueues = 0;
    memset(qStats->qCount, 0 , MAX_ROUTER_THREADS);
    int numThreads = 1;

    if (itsDiaConfig.IsQueueMgmtEnabled())
    {
        numThreads = itsDiaConfig.GetQueueMgmt().GetMsgRouterThreadCount();
    }

    for (int i=0; i<numThreads; i++)
    {
        int cnt = 0;
        if ((cnt = DiaStackClass::GetDiaStackQCount(i)) < 0)
        {
            cnt = 0;
        }
        qStats->qCount[i] = cnt;
    }

    qStats->noOfQueues = numThreads;

    return ITS_SUCCESS;
}

void initMap()
{
    ddlPluginMap["6:7"] = "s6ar8_s6ar10_transform";
    ddlPluginMap["1:2"] = "gyr8_gyr10_transform";
}

#if 0
int
DiaMgmt::GetSessionTableSize()
{
    return SessionTable::GetSessionTable()->GetTableSize();
}
#endif

int
DiaMgmt::PrintSessionTable(std::ostream& oss)
{
    oss << *(SessionTable::GetSessionTable());
    return ITS_SUCCESS;
}

ITS_UINT
DiaMgmt::EnableStatistics()
{
    itsDiaConfig.SetStatisticsEnabled();
    return ITS_SUCCESS;
}

ITS_UINT 
DiaMgmt::DisableStatistics()
{
    itsDiaConfig.SetStatisticsDisabled();
    return ITS_SUCCESS;
}
 
bool 
DiaMgmt::IsStatsEnabled()
{
    return (itsDiaConfig.IsStatisticsEnabled());
}

ITS_UINT 
DiaMgmt::EnableHexDump()
{
    itsDiaConfig.SetHexDumpEnabled();
    return ITS_SUCCESS;
}
ITS_UINT 
DiaMgmt::DisableHexDump()
{
    itsDiaConfig.SetHexDumpDisabled();
    return ITS_SUCCESS;
}

bool 
DiaMgmt::IsHexDumpEnabled()
{
    return(itsDiaConfig.IsHexDumpEnabled());
}



void 
DiaMgmt::GetDiaStackStats(std::ostream& oss, bool clrFlag)
{
    diaStackStats.Print(oss);
    if (clrFlag)
    {
        diaStackStats.ResetAll();
    }
}

void
DiaMgmt::GetDiaSessionStats(std::ostream& oss, bool clrFlag)
{
    diaStackStats.PrintSessionStats(oss); 
    if (clrFlag)
    {
        diaStackStats.ResetSessionStats();
    }
}

void
DiaMgmt::GetDiaPeerStats(std::ostream& oss, bool clrFlag)
{
    diaStackStats.PrintPeerStats(oss);
    if (clrFlag)
    {
        diaStackStats.ResetPeerStats();
    }
}

void
DiaMgmt::GetDiaPeerStatus(std::ostream& oss, PEER_INFO* pInfo)
{
    int ret;
    PEER_ENTRY *pEntry = NULL;

    if (PeerTable::GetPeerTable()->FindEntry(pInfo->peerName,
                                             pInfo->realmName,
                                             pEntry))
    {
        PrintEntry(oss, pEntry);        
    }
    else
    {
        oss << "Invalid Peer Name. Discarding";
    }
}

void
DiaMgmt::GetDiaIndicStats(std::ostream& oss, bool clrFlag)
{
    diaStackStats.PrintIndicStats(oss);
    if (clrFlag)
    {
        diaStackStats.ResetIndicStats();
    }
}
void
DiaMgmt::GetDiaMiscStats(std::ostream& oss, bool clrFlag)
{
    diaStackStats.PrintMiscStats(oss);
    if (clrFlag)
    {
        diaStackStats.ResetMiscStats();
    }
}

ITS_UINT
DiaMgmt::ResetStackStats()
{
    diaStackStats.ResetAll();
    return ITS_SUCCESS;
}

ITS_UINT
DiaMgmt::ResetTotMsgStats()
{
    diaStackStats.ResetTotalMsgStats();
    return ITS_SUCCESS;
}

int 
DiaMgmt::ResetSessionErrorStats()
{
    diaStackStats.ResetSessionErrorStats();
    return ITS_SUCCESS;
}

int 
DiaMgmt::GetDiaIndStats(void *arg, bool clrFlag)
{
    DIA_INDIC_STATS *indStats = (DIA_INDIC_STATS *)arg;
    int ret = diaStackStats.GetDiaIndStats(indStats);

    if ((ret == ITS_SUCCESS) && clrFlag)
    {
        diaStackStats.ResetIndicStats();
    }
    return ret;
}
int 
DiaMgmt::GetDiaSessStats(void *arg, bool clrFlag)
{
    DIA_SESS_STATS *sessStats = (DIA_SESS_STATS *)arg;
    int ret = diaStackStats.GetDiaSessStats(sessStats);
    if ((ret == ITS_SUCCESS) && clrFlag)
    {
        diaStackStats.ResetSessionStats();
    }
    return ret;
}

int
DiaMgmt::GetDiaTotMessageStats()
{
    int totalmess = diaStackStats.GetDiaTotalMessages();
    return totalmess;
}

int 
DiaMgmt::GetDiaPeerStats(void *arg, bool clrFlag)
{
    DIA_PEER_STATS *peerStats = (DIA_PEER_STATS *)arg;
    int ret = diaStackStats.GetDiaPeerStats(peerStats);
    if ((ret == ITS_SUCCESS) && clrFlag)
    {
        diaStackStats.ResetPeerStats();
    }
    return ret;
}

int
DiaMgmt::GetDiaPeerStatus(void *arg, PEER_INFO* pInfo)
{
    int ret;
    char tempBuf[MAX_PARAM_LEN];
    struct tm tbuf;

    PEER_ENTRY *pEntry = NULL;

    DIA_PEER_STATUS* peerStatus = (DIA_PEER_STATUS*)arg;

    if (PeerTable::GetPeerTable()->FindEntry(pInfo->peerName,
                                             pInfo->realmName,
                                             pEntry))
    {
        peerStatus->pState = (PEER_FSM_STATE) DIA_PE_STATE(pEntry);
        peerStatus->isStatic = DIA_PE_STATIC(pEntry);
        if (DIA_PE_CONN_TINFO(pEntry).type == ITS_DIA_T_SCTP)
        {
            peerStatus->type = DIA_TRANS_SCTP;
        }
        else
        {
            peerStatus->type = DIA_TRANS_TCP;
        }

        peerStatus->port = DIA_PE_CONN_TINFO(pEntry).portNo;

        peerStatus->connEstTime = 0;

        if (DIA_PE_STATE(pEntry) == PEER_ST_I_OPEN ||
            DIA_PE_STATE(pEntry) == PEER_ST_R_OPEN)
        {
            peerStatus->connEstTime = DIA_PE_CONEST_TIME(pEntry);
        }

        strncpy(peerStatus->peerName, DIA_PE_HOST(pEntry), MAX_PARAM_LEN);

        strncpy(peerStatus->realmName, DIA_PE_REALM(pEntry), MAX_PARAM_LEN);

        strncpy(peerStatus->ipAddr, DIA_PE_CONN_TINFO(pEntry).serverIpAddr,
                                                        MAX_PARAM_LEN); 
        ret = ITS_SUCCESS;
    }
    else
    {
        DT_CRT(("Invalid Peer Name Discarding"));
        ret = ITS_DIA_UNKNOWN_PEER;
    }
    return ret;
}


int
DiaMgmt::GetDiaMiscStats(void *arg, bool clrFlag)
{
    DIA_MISC_STATS_STR *mStats = (DIA_MISC_STATS_STR *)arg;
    int ret = diaStackStats.GetDiaMiscStats(mStats);

    if ((ret == ITS_SUCCESS) && clrFlag)
    {
        diaStackStats.ResetMiscStats();
    }
    return ret;
}

int
DiaMgmt::GetIdcConnStatus(int clientId, DIA_DIST_CONN_INFO* connInfo)
{
    int ret = !ITS_SUCCESS;
    if (IDSCmdProcessCallBack != NULL) 
    {
        ret =IDSCmdProcessCallBack(GET_IDC_CONN_INFO, &clientId, connInfo);    
    }
    return ret;
}
 
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *  To call the SendStateChangeEventToStack() in case of redundancy. 
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
 *      Integer : (ITS_SUCCESS / !ITS_SUCCESS)
 *  
 *  Notes:
 *  
 *  See Also:
 *
 * Revision History:
 * ---------------------------------------------------------------------------
 *  Name          Date        Reference               Description
 * ---------------------------------------------------------------------------
 *
 ****************************************************************************/
int
DiaMgmt::SwitchOver()
{
    ITS_NODE_STATE state;
    ITS_INT ret;
    ITSDiaConfig* cfg = &itsDiaConfig;
    if (!cfg->IsMsgRedundancyEnabled() && !cfg->IsRedundancyEnabled() )
    {
        DT_WRN(("Valid only for the Redundant Configuration."));
        return (!ITS_SUCCESS);
    }
    else if ((ret = ITS_GetNodeState(&state)) == ITS_SUCCESS)
    {
        if (state != ITS_STATE_PRIMARY)
        {
             ret = ITS_SendStateChangeEventToStack(ITS_STATE_PRIMARY);
 
             if (ret != ITS_SUCCESS)
             {
                 DT_ERR(("SendStateChangeEventToStack::Failed"));
             }
        }
        else
        {
             DT_WRN(("Node is in ACTIVE STATE, Unable to do SwitchOver"));
             return (!ITS_SUCCESS);
        }
    }
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *  To Initiate all Peer entries which added dynamically
 *  
 *  Input Parameters:
 *      None.
 *  
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *     outParam: Contains the value of the Node state
 *                Primary: 0.
 *                Standby: 1.
 *                BackUp : 2. 
 *  
 *  Return Value:
 *     bool: (true /false) 
 *  
 *  Notes:
 *  
 *  See Also:
 *
 * Revision History:
 * ---------------------------------------------------------------------------
 *  Name          Date        Reference               Description
 * ---------------------------------------------------------------------------
 *
 ****************************************************************************/ 
bool
DiaMgmt::GetNodeState(ITS_USHORT &outParam)
{
    ITS_NODE_STATE state;
    bool ret = false;
    ITSDiaConfig* cfg = &itsDiaConfig;
 
    if (!cfg->IsMsgRedundancyEnabled() && !cfg->IsRedundancyEnabled() )
    {
        return ret;
    }
    else
    {
        ret =true;
        ITS_GetNodeState(&state);
        outParam = (ITS_USHORT)state;
    }
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *  To Print Peer entries
 *  
 *  Input Parameters:
 *      None.
 *  
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *     outParam: Contains the value of the Node state
 *                Primary: 0.
 *                Standby: 1.
 *                BackUp : 2. 
 *  
 *  Return Value:
 *     void
 *  
 *  Notes:
 *  
 *  See Also:
 *
 * Revision History:
 * ---------------------------------------------------------------------------
 *  Name          Date        Reference               Description
 * ---------------------------------------------------------------------------
 *
 ****************************************************************************/ 
void
DiaMgmt::PrintPeerStats(std::ostream& oss, std::string peer, std::string realm)
{
    PeerTable::GetPeerTable()->PrintPeerStats(oss, peer, realm); 
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *  To Initiate all Peer entries which added dynamically
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
 *      Integer
 *  
 *  Notes:
 *  
 *  See Also:
 *
 * Revision History:
 * ---------------------------------------------------------------------------
 *  Name          Date        Reference               Description
 * ---------------------------------------------------------------------------
 *  Naresh        23-04-2008   ST-IDIA-0300-01     Fix for Issue #881
 *                                                Adding Transport index 
 *
 *  Naresh        23-04-2008   ST-IDIA-0300-01     Fix for Issue #885
 *                                                Incrementing Transport index 
 *
 ****************************************************************************/
static int InitDynamics()
{
    int ret;

    PEER_ENTRY *entry = PeerTable::GetPeerTable()->FindFirstEntry();

    while (entry != NULL)
    {
        if (DIA_PE_ACTIVE(entry) || 
            (DIA_PE_STATE(entry) != PEER_ST_CLOSED))
        {
            entry = PeerTable::GetPeerTable()->FindNextEntry(entry);
            continue;
        }
        if (DIA_PE_RETRY_TIMER(entry) == TIMER_BAD_SERIAL)
        { 
            DIA_PE_INIT_CONN(entry) = true;
        }
        else
        {
          DT_WRN(("Already RETRY timer is running\n"));
        }

        usleep(10000);
        entry = PeerTable::GetPeerTable()->FindNextEntry(entry);
    }

    return (ITS_SUCCESS);
}


/**
InitDyanamicsPeer
*/

static int
InitDynamicsPeer(const char* hostName,
                    const char* realmName)
{
    int ret;
    PEER_ENTRY *entry =  NULL;
 
    if (PEER_TABLE->FindEntry(hostName, realmName, entry)) 
    {
        if (DIA_PE_ACTIVE(entry) ||
            (DIA_PE_STATE(entry) != PEER_ST_CLOSED))
        {
            DT_WRN(("Failed to Initialize Connector:Peer not in closed state"));
            //return !ITS_SUCCESS;
            return SET_PEERSTATUS_ERR_PEER_NOT_IN_CLOSED_STATE;
        }
        DIA_PE_IS_FORCE_DISCONNECTED(entry) = false;
        if (DIA_PE_RETRY_TIMER(entry) == TIMER_BAD_SERIAL) 
        {
            DIA_PE_INIT_CONN(entry) = true;
        }
        else
        {
          DT_WRN(("Already RETRY timer is running\n"));
        }

        return (ITS_SUCCESS);  
    }
    return (!ITS_SUCCESS);  
}

/***************************************************************************
 *                                                                         *
 *									   *
 *									   *
 *									   *
 * *************************************************************************/
int DiaMgmt::ModifyDictId(PEER_INFO* pInfo, int& dict_count, int* dict_Id)
{
    int ret = (!ITS_SUCCESS);
    PEER_ENTRY *pEntry = NULL;
    int addIndex, arrayIndex;
    DT_DBG(("DiaMgmt::ModifyDictId"));
    if (PeerTable::GetPeerTable()->FindEntry(pInfo->peerName, 
                pInfo->realmName, pEntry))
    {
        if(dict_count != 0 && dict_count <= MAX_DICT_IDS_PER_PEER)
        {
            for ( addIndex = 0; addIndex < dict_count ; addIndex++)
            {
                for (arrayIndex = 0; arrayIndex < MAX_DICT_IDS_PER_PEER; arrayIndex++)
                {
                    if (pEntry->dictId[arrayIndex] == 0)
                    {
                        pEntry->dictId[arrayIndex] = dict_Id[addIndex];
                        DT_DBG(("Added Dictionary Id[%d] = %d",arrayIndex, pEntry->dictId[arrayIndex]));
                        break;
                    }

                    if (pEntry->dictId[arrayIndex] == dict_Id[addIndex])
                    {
                        DT_DBG(("Dictionary Id[%d] already present = %d",addIndex,pEntry->dictId[arrayIndex]));
                        break;
                    }
                }

                if ( arrayIndex == MAX_DICT_IDS_PER_PEER)
                {
                    DT_WRN(("Peer reached MAX dictionary entries"));
                    ret = !ITS_SUCCESS;
                    return ret;
                }
            }
            ret = ITS_SUCCESS;
        }
        else
        {
            DT_ERR(("No Dictionary Id Present"));
            ret = (!ITS_SUCCESS); 
        }
    }
    return ret;
}

/***************************************************************************
 *                                                                         *
 *									   *
 *									   *
 *									   *
 * *************************************************************************/
int DiaMgmt::AssociateDictToPeer(PEER_INFO* pInfo, int& dict_count,
                                 std::string *dictNames,APPLICATION_TYPE type[],
                                 bool checkIsDictNelwyLoaded)
{
    int ret;
    PEER_ENTRY *pEntry = NULL;
    int addIndex, arrayIndex;
    int sId =-1;
    unsigned int authorizationAppId[MAX_DICT_IDS_PER_PEER] = {0};
    unsigned int accountingAppId[MAX_DICT_IDS_PER_PEER] = {0};
    int numOfAuthAppId = 0;
    int numOfAcctAppId = 0;
    DT_DBG(("DiaMgmt::AssociateDictToPeer"));
    if (PeerTable::GetPeerTable()->FindEntry(pInfo->peerName, 
                pInfo->realmName, pEntry))
    {
        if(dict_count != 0 && dict_count <= MAX_DICT_IDS_PER_PEER)
        {
            for ( addIndex = 0; addIndex < dict_count ; addIndex++)
            {
                bool isDictNewlyLoaded = false;
                DT_DBG(("Application Type is %d",type[addIndex]));
                int Id = DiaStackClass::GetDictionaryTable().loadDictionary(dictNames[addIndex]+DEBUGSUFFIX,
                                                                            isDictNewlyLoaded);

                if(!checkIsDictNelwyLoaded)
                {
                    isDictNewlyLoaded = false;
                }

                if(isDictNewlyLoaded)
                {
                    DT_DBG(("Library newly loaded"));
                    unsigned int applicationId = (DiaStackClass::GetDictionaryTable()[Id]).Get()->getApplicationId();
                    if(type[addIndex] == DIA_AUTH_APP && DiaMsgRouter::IsCapabilityUpdated(applicationId,true))
                    {
                        authorizationAppId[numOfAuthAppId]= applicationId;
                        numOfAuthAppId++;
                    }
                    else if(type[addIndex] == DIA_ACCT_APP && DiaMsgRouter::IsCapabilityUpdated(applicationId))
                    {
                        accountingAppId[numOfAcctAppId]= applicationId;
                        numOfAcctAppId++;
                    }
                }
                for (arrayIndex = 0; arrayIndex < MAX_DICT_IDS_PER_PEER; arrayIndex++)
                {
                    if (pEntry->dictId[arrayIndex] == 0)
                    {
                        if(Id > 0)
                        {
                            pEntry->dictId[arrayIndex] = Id;
                            ddlPluginArray[Id] = 1;

                            if (sId ==-1)
                                sId = arrayIndex;
                            DT_DBG(("Associated Dictionary Id[%d] = %d",arrayIndex, pEntry->dictId[arrayIndex]));
                            break;
                        }
                        else
                        {
                            DT_ERR(("Failed to Load Dictionary for [%s]",dictNames[addIndex].c_str()));
                            //*failedDictId = arrayIndex;
                            for (int x = sId; ((sId != -1) && (x < MAX_DICT_IDS_PER_PEER)); x++)
                            {
                                pEntry->dictId[x] = 0;
                            }
                            return ADD_DICTID_ERR_LOAD_DICTIONARY_FAILED;
                        }
                    }

                    if (pEntry->dictId[arrayIndex] == Id)
                    {
                        DT_DBG(("Dictionary Id[%d] already present = %d",addIndex,pEntry->dictId[arrayIndex]));
                        break;
                    }
                }

                if ( arrayIndex == MAX_DICT_IDS_PER_PEER)
                {
                    DT_WRN(("Peer reached MAX dictionary entries"));
                    return ADD_DICTID_ERR_DICTNAME_MAX_COUNT_REACHED;
                }
            }
            ret = ITS_SUCCESS;
        }
        else
        {
            DT_ERR(("No Dictionary Id Present"));
            ret = ADD_DICTID_ERR_INVALID_DICT_COUNT; 
        }

        if((CAPABILITIES_UPDATE_APPLICATION->IsCapabilityUpdateIsSupported()) &&
           (numOfAuthAppId > 0 || numOfAcctAppId > 0) && (ret == ITS_SUCCESS))
        {
            DiaMsgRouter::SendCUR(authorizationAppId,numOfAuthAppId,accountingAppId,numOfAcctAppId);
        }
        ITSDiaConfig *cfg = &itsDiaConfig;

        if(ret == ITS_SUCCESS && cfg->IsDTFEnabled())
        {
            for(ITS_UINT i = 1; i < (MAX_DICT_IDS_PER_PEER * 2); i++)
            {
                if((ddlPluginArray[i] != 0xFFFF) && (ddlPluginArray[i] == 1)
                                            &&  (ddlPluginArray[i+1] == 1))
                {
                    initMap();
                    stringstream combo, config;
                    string plugin, filejson;

                    combo<<i<<":"<<i+1;
                    plugin = ddlPluginMap[combo.str()];

                    if(plugin.length() == 0)
                        continue;

                    ddlPluginArray[i] = 0xFFFF;
                    config<<ddlPluginMap[combo.str()]<<".json";
                    filejson = config.str();

                    try
                    {
                        if(DiaStackClass::GetDtf().LoadTransformerObject(i,
                                    i+1, plugin, filejson) == ITS_SUCCESS)
                        {
                            DT_DBG(("Plugin %s loaded successfully\n",
                                        plugin.c_str()));
                        }
                    }
                    catch (eAccelero::PluginException& x)
                    {
                        DT_CRT(("PluginException::%s ", x.what()));
                    }

                }
            }
        }
    }
    else
    {
        DT_ERR(("Peer Not Present"));
        ret = ADD_DICTID_ERR_PEER_NOT_PRESENT;
    }
    return ret;
}

int DiaMgmt::RemoveDictId(PEER_INFO* pInfo, int& dict_count, int* dict_Id)
{
    int ret = ITS_SUCCESS;
    PEER_ENTRY *pEntry = NULL;
    int deleteIndex, arrayIndex;
    DT_DBG(("DiaMgmt::RemoveDictId"));
    if (PeerTable::GetPeerTable()->FindEntry(pInfo->peerName, 
                pInfo->realmName, pEntry))
    {
        if(dict_count > 0 && dict_count <= MAX_DICT_IDS_PER_PEER)
        {
            for(deleteIndex = 0; deleteIndex < dict_count; deleteIndex++)
            {
                for (arrayIndex = 0; arrayIndex < MAX_DICT_IDS_PER_PEER; arrayIndex++)
                {
                    if(pEntry->dictId[arrayIndex] == dict_Id[deleteIndex])
                    {
                        /* Unload of Dictionary is not called here
                         * Only the associations will be cleared.*/
                        for (int tmpIndex  = arrayIndex; tmpIndex < MAX_DICT_IDS_PER_PEER; tmpIndex++)
                        {
                            //Fixing Out-of-bounds read
                            pEntry->dictId[tmpIndex] = (((tmpIndex+1) < MAX_DICT_IDS_PER_PEER) ? pEntry->dictId[tmpIndex+1] : EMPTYDICTIONARY);
                        }
                        // pEntry->dictId[MAX_DICT_IDS_PER_PEER] = EMPTYDICTIONARY; not required, fix for coverity issue 10650
                        break;
                    }
                    if ( arrayIndex == MAX_DICT_IDS_PER_PEER )
                    {
                        DT_ERR(("Dictionary Id %d not found for Peer %s", dict_Id[deleteIndex], pInfo->peerName));
                    }
                }
            }
            ret = ITS_SUCCESS;
        }
        else
        {
            DT_ERR(("No Dictionary Id Present"));
            ret = (!ITS_SUCCESS); 
        }
    }
    return ret;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *  To add Peer entry of type PEER_INFO dynamically
 *
 *  Input Parameters:
 *      PEER_INFO*
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Integer
 *
 *  Notes:
 *
 *  See Also:
 *
 * Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *  Naresh        21-04-2008   ST-IDIA-0300-01     Fix for Issue #855
 *                                                 Modification feature added
 ****************************************************************************/

int
DiaMgmt::AddPeer(PEER_INFO* pInfo)
{
    DT_DBG((" > AddPeer\n"));
    int ret;
    PEER_ENTRY *pEntry = NULL;
    ITS_USHORT trIndx = 0;
    ITS_INT val = 0;

    if (PeerTable::GetPeerTable()->FindEntry(pInfo->peerName, 
                                             pInfo->realmName, 
                                             pEntry))
    {
        if (DIA_PE_STATE(pEntry) == PEER_ST_CLOSED)
        {
            DIA_PE_STATIC(pEntry)= ITS_FALSE;
            DIA_PE_STATE(pEntry) = PEER_ST_CLOSED;
            DIA_PE_FSM(pEntry)   = new PeerFsm();
            //Allocate memeory for Peer stack stats
            //DIA_PE_STATS(pEntry) = new DiaStackPeerStats();
            DIA_PE_CONN_TINFO(pEntry).type = (DIA_TRANS_TYPE)pInfo->type;
            DIA_PE_CONN_TINFO(pEntry).serverIpAddr = strdup(pInfo->ipAddr);
            if(pInfo->port !=0 )
            {
               DIA_PE_CONN_TINFO(pEntry).portNo = pInfo->port;
            }
            if(pInfo->securePort !=0)
            {
               DIA_PE_CONN_TINFO(pEntry).securePort = pInfo->securePort;
            }
            else
            {
               DIA_PE_CONN_TINFO(pEntry).securePort = 0;
            }
	        pEntry->tlsEnabled = pInfo->tlsEnabled;
            DIA_PE_DSCP_EN(pEntry) = ITS_FALSE;
            DIA_PE_DSCP_VAL(pEntry) = val;
    	    DIA_PE_IS_FORCE_DISCONNECTED(pEntry) = (!pInfo->status);

            if (DIA_PE_CONN_TINFO(pEntry).type == ITS_DIA_T_SCTP)
            {
                DIA_PE_CONN_TINFO(pEntry).multiHomeipaddrs[0] =
                                   DIA_PE_CONN_TINFO(pEntry).serverIpAddr;
            }
            for(int i =1;i <= pInfo->noIPs;i++)
            {
                DIA_PE_CONN_TINFO(pEntry).multiHomeipaddrs[i] = pInfo->multiHomeipaddrs[i-1];
            }

            DIA_PE_CONN_TINFO(pEntry).noIPs = 1 + pInfo->noIPs;
            DT_DBG(("Succesfully Updated Peer Entry For %s\n",
                             pEntry->hostIdentity));
            return ITS_SUCCESS;
        }
        else
        {
            DT_ERR(("Failed to Add Peer Entry : Peer is in OPEN state and Entry Exists For %s\n",
                 pInfo->peerName));

            DIA_Alarm(15250, __FILE__, __LINE__, "Peer=%s:Realm=%s",
                      DIA_PE_HOST(pEntry), DIA_PE_REALM(pEntry));

            return ITS_DIA_EINVALID_PEER;
        }
    }
 
    /* get trIndex for Peer */
    trIndx = trTable.GetNextTrIndex();

    if (trIndx == 0)
    {
            DT_ERR(("Max trans limit reached failed allocate trIndex For %s\n",
                 pInfo->peerName));

            DIA_Alarm(15250, __FILE__, __LINE__, "Peer=%s:Realm=%s",
                      pInfo->peerName, pInfo->realmName);

            //return ITS_DIA_EINVALID_PEER;
            return SET_PEER_ERR_MAX_TRANSPORTS_REACHED;

    }

    pEntry = (PEER_ENTRY *)malloc(sizeof(PEER_ENTRY));
    if  (pEntry == NULL)
    {
        throw "Error: Malloc failed";   
    }
    memset(pEntry, 0, sizeof(PEER_ENTRY));

    //If retransmission of msg is required
    //create pendingQ
    if(pInfo->isRetransmissionEnabled)
    {
        DIA_PE_RETRANSMISSION_ENABLED(pEntry) = true;
        DIA_PE_PENDING_Q(pEntry) = new PendingQ();
    }
    DIA_PE_HOST(pEntry)  = strdup(pInfo->peerName);
    DIA_PE_REALM(pEntry) = strdup(pInfo->realmName);
    DIA_PE_STATIC(pEntry)= ITS_FALSE;
    DIA_PE_STATE(pEntry) = PEER_ST_CLOSED;
    DIA_PE_FSM(pEntry)   = new PeerFsm();
    DIA_PE_INDEX(pEntry)  = trIndx;
    DIA_PE_IS_FORCE_DISCONNECTED(pEntry) = (!pInfo->status);
    pEntry->tlsEnabled = pInfo->tlsEnabled;
    //Allocate memory for Peer stats
    //DIA_PE_STATS(pEntry) = new DiaStackPeerStats();

    if(pInfo->type != DIA_TRANS_INVALID &&(pInfo->port !=0 || pInfo->securePort !=0))
    {
        DT_DBG(("Add peer %s with transport %d and port %d and secure port %d",
                 pInfo->peerName,pInfo->type,pInfo->port,pInfo->securePort));
        int index = 0;
        if(pInfo->type == DIA_TRANS_SCTP && pInfo->securePort > 0)
        {
            DT_DBG(("Configuring secure port for sctp transport type is not supported"));
            return SET_PEER_SECURE_PORT_NOT_SUPPORTED_FOR_SCTP;
        }
        
        if(pInfo->type == DIA_TRANS_TCP)
        {
            if(pInfo->securePort != 0 && (!pInfo->tlsEnabled))
            {
                DT_DBG(("TLS is not enabled to configure securePort for peer %s.Failed to configure",
                        pInfo->peerName));
                return SET_PEER_SECURE_PORT_TLS_NOT_ENABLED;
            }

            if(pInfo->securePort != 0)
            {
                DIA_PE_CONN_TINFO_INDEX(pEntry,index).securePort = pInfo->securePort;
                DIA_PE_CONN_TINFO_INDEX(pEntry,index).serverIpAddr = strdup(pInfo->ipAddr);
                DIA_PE_CONN_TINFO_INDEX(pEntry,index).type = (DIA_TRANS_TYPE)(pInfo->type);
                index++;
            }
        }
        if(pInfo->port !=0)
        {
            DIA_PE_CONN_TINFO_INDEX(pEntry,index).portNo = pInfo->port;
            DIA_PE_CONN_TINFO_INDEX(pEntry,index).serverIpAddr = strdup(pInfo->ipAddr);
            DIA_PE_CONN_TINFO_INDEX(pEntry,index).type = (DIA_TRANS_TYPE)(pInfo->type);
            if (DIA_PE_CONN_TINFO_INDEX(pEntry,index).type == ITS_DIA_T_SCTP)
            {
                DIA_PE_CONN_TINFO_INDEX(pEntry,index).multiHomeipaddrs[0] =
                    DIA_PE_CONN_TINFO_INDEX(pEntry,index).serverIpAddr;
                for(int i =1;i <= pInfo->noIPs;i++)
                {
                    DIA_PE_CONN_TINFO_INDEX(pEntry,index).multiHomeipaddrs[i] = pInfo->multiHomeipaddrs[i-1];
                }

                DIA_PE_CONN_TINFO_INDEX(pEntry,index).noIPs = 1 + pInfo->noIPs;
            }
            index++;
        }
        DIA_PE_CONN_TRANS_COUNT(pEntry) = index;
    }
    else if(pInfo->type != DIA_TRANS_INVALID &&(pInfo->port == 0 && pInfo->securePort ==0))
    {
        int index = 0;
        if(pInfo->type == DIA_TRANS_TCP)
        {
            DT_DBG(("Add peer %s with transport %d and default port %d and default tls port %d",
                    pInfo->peerName,pInfo->type,DEFAULT_TCP_OR_SCTP_PORT,DEFAULT_TLS_OR_DTLS_PORT));
            DIA_PE_CONN_TINFO_INDEX(pEntry,index).serverIpAddr = strdup(pInfo->ipAddr);
            DIA_PE_CONN_TINFO_INDEX(pEntry,index).securePort = DEFAULT_TLS_OR_DTLS_PORT;
            DIA_PE_CONN_TINFO_INDEX(pEntry,index).type = (DIA_TRANS_TYPE)(pInfo->type);
            index++;
        }
        DIA_PE_CONN_TINFO_INDEX(pEntry,index).serverIpAddr = strdup(pInfo->ipAddr);
        DIA_PE_CONN_TINFO_INDEX(pEntry,index).portNo = DEFAULT_TCP_OR_SCTP_PORT;
        DIA_PE_CONN_TINFO_INDEX(pEntry,index).type = (DIA_TRANS_TYPE)(pInfo->type);
        if (DIA_PE_CONN_TINFO_INDEX(pEntry,index).type == ITS_DIA_T_SCTP)
        {
            DT_DBG(("Add peer %s with transport %d and default port %d",
                     pInfo->peerName,pInfo->type,DEFAULT_TCP_OR_SCTP_PORT));
            DIA_PE_CONN_TINFO_INDEX(pEntry,index).multiHomeipaddrs[0] =
                DIA_PE_CONN_TINFO_INDEX(pEntry,index).serverIpAddr;
            DIA_PE_CONN_TINFO_INDEX(pEntry,index).noIPs = 1;
        }
        index++;
        DIA_PE_CONN_TRANS_COUNT(pEntry) = index;
    }
    else if(pInfo->type == DIA_TRANS_INVALID && (pInfo->port != 0 || pInfo->securePort !=0))
    {
        if(pInfo->port != 0)
        {
            DT_DBG(("Add peer %s with transport TCP,SCTP and port = %d",
                    pInfo->peerName,pInfo->port));
        }
        if(pInfo->securePort != 0) 
        {
            DT_DBG(("Add peer %s with transport TCP and SecurePort = %d",
                    pInfo->peerName,pInfo->securePort));
        }
        if(pInfo->securePort != 0 && (!pInfo->tlsEnabled))
        {
            DT_DBG(("TLS is not enabled to configure securePort for peer %s.Failed to configure",
                        pInfo->peerName));
            return SET_PEER_SECURE_PORT_TLS_NOT_ENABLED;
        }
        int index = 0;
        if(pInfo->securePort != 0)
        {
            DIA_PE_CONN_TINFO_INDEX(pEntry,index).serverIpAddr = strdup(pInfo->ipAddr);
            DIA_PE_CONN_TINFO_INDEX(pEntry,index).securePort = pInfo->securePort;
            DIA_PE_CONN_TINFO_INDEX(pEntry,index).type = ITS_DIA_T_TCP;
            index++;
        }
        if(pInfo->port != 0)
        {
            DIA_PE_CONN_TINFO_INDEX(pEntry,index).serverIpAddr = strdup(pInfo->ipAddr);
            DIA_PE_CONN_TINFO_INDEX(pEntry,index).portNo = pInfo->port;
            DIA_PE_CONN_TINFO_INDEX(pEntry,index).type = ITS_DIA_T_TCP;
            index++;

            DIA_PE_CONN_TINFO_INDEX(pEntry,index).serverIpAddr = strdup(pInfo->ipAddr);
            DIA_PE_CONN_TINFO_INDEX(pEntry,index).portNo = pInfo->port;
            DIA_PE_CONN_TINFO_INDEX(pEntry,index).type = ITS_DIA_T_SCTP;
            DIA_PE_CONN_TINFO_INDEX(pEntry,index).multiHomeipaddrs[0] =
                DIA_PE_CONN_TINFO_INDEX(pEntry,index).serverIpAddr;
            DIA_PE_CONN_TINFO_INDEX(pEntry,index).noIPs = 1;
            index++;
        }
        DIA_PE_CONN_TRANS_COUNT(pEntry) = index;

    }
    else
    {
        DT_DBG(("Add peer %s with default transport info",pInfo->peerName));
        int index = 0;
        //minus since DTLS is not supported
        for(int i =0;i<(MAX_TRANS_PER_LIST-1);i++)
        {
            DIA_PE_CONN_TINFO_INDEX(pEntry,i).serverIpAddr = strdup(pInfo->ipAddr);
        }
        //configure trsnport in the order TLS,DTLS,TCP and SCTP
        DIA_PE_CONN_TINFO_INDEX(pEntry,index).securePort = DEFAULT_TLS_OR_DTLS_PORT;
        DIA_PE_CONN_TINFO_INDEX(pEntry,index).type = (DIA_TRANS_TYPE)(DIA_TRANS_TCP);
        index++;

        //DIA_PE_CONN_TINFO_INDEX(pEntry,ndex).securePort = DEFAULT_TLS_OR_DTLS_PORT;
        //DIA_PE_CONN_TINFO_INDEX(pEntry,index).type = DIA_TRANS_SCTP;
        //index++

        DIA_PE_CONN_TINFO_INDEX(pEntry,index).portNo = DEFAULT_TCP_OR_SCTP_PORT;
        DIA_PE_CONN_TINFO_INDEX(pEntry,index).type = (DIA_TRANS_TYPE)(DIA_TRANS_TCP);
        index++;

        DIA_PE_CONN_TINFO_INDEX(pEntry,index).portNo = DEFAULT_TCP_OR_SCTP_PORT;
        DIA_PE_CONN_TINFO_INDEX(pEntry,index).type = (DIA_TRANS_TYPE)(DIA_TRANS_SCTP);
        DIA_PE_CONN_TINFO_INDEX(pEntry,index).multiHomeipaddrs[0] =
            DIA_PE_CONN_TINFO_INDEX(pEntry,index).serverIpAddr;
        DIA_PE_CONN_TINFO_INDEX(pEntry,index).noIPs = 1;
        index++;

        DIA_PE_CONN_TRANS_COUNT(pEntry) = index;
    }
    
    if (MUTEX_CreateMutex(&DIA_PE_MUX(pEntry), 0) != ITS_SUCCESS)
    {
        FreeEntry(pEntry);
        throw its::Error(ITS_EBADMUTEX, __FILE__, __LINE__);
        return ITS_DIA_ALLOCFAIL;
    }

    ret = PeerTable::GetPeerTable()->InsertEntry(pEntry);

    if (ret == ITS_SUCCESS)
    {
        DT_DBG(("Succesfully Added Peer Entry For %s\n",
                         pEntry->hostIdentity));

    }
    else
    {
        DT_ERR(("Failed to Add Peer Entry: Entry Exists For %s\n",
                 pEntry->hostIdentity));

        DIA_Alarm(15250, __FILE__, __LINE__, "Peer=%s:Realm=%s",
                  DIA_PE_HOST(pEntry), DIA_PE_REALM(pEntry));

        FreeEntry(pEntry);

        return ITS_DIA_EINVALID_PEER;
    }

    DT_DBG((" < AddPeer\n"));
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *  To add Alternate Peer dynamically
 *
 *  Input Parameters:
 *      peerName,altPeerName,altRealmName,isRedundantMate
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Integer
 *
 *  Notes:
 *
 *  See Also:
 *
 * Revision History:
 * ---------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 * ---------------------------------------------------------------------------
 *  Naresh        24-04-2008   ST-IDIA-0300-02     Fix for Issue #907
 *                                                 Modification added to 
 *                                                 isFailoverEnable 
 *
 ****************************************************************************/
int
DiaMgmt::AddAlternatePeer(ALT_PEER_INFO* aInfo)
{
    int ret = ITS_SUCCESS;
    char* hostId    = NULL;
    char* hostRealm = NULL;
    PEER_ENTRY *pEntry = NULL;
    PEER_ENTRY *aEntry = NULL;
    if (PeerTable::GetPeerTable()->FindEntry(aInfo->peerName, 
                                             aInfo->realmName, pEntry)) 
    {
        if (PeerTable::GetPeerTable()->FindEntry(aInfo->altHost, 
                                                 aInfo->altRealmName, aEntry)) 
        {
            if(pEntry->altHost)
            {
                /* Return Error- AltHost Present, Call Modify Entry to modify */
                DT_DBG(("Alternate Host Already Present:  %s ",pEntry->altHost));
                return !ITS_SUCCESS;
            }
            else
            {
                hostId   = strdup(aInfo->altHost);
                hostRealm = strdup(aInfo->altRealmName);
                if (aInfo->isFailoverEnable || aInfo->isRedundantMate)
                {
                    if (aInfo->isFailoverEnable && (!DIA_PE_RETRANSMISSION_ENABLED(pEntry)) )
                    {
                        DIA_PE_PENDING_Q(pEntry) = new PendingQ();
                    }
                    DIA_PE_ALT_HOST(pEntry)  = hostId;
                    DIA_PE_ALT_REALM(pEntry) = hostRealm;
                    DIA_PEER_CHK_IS_FAILOVER_ENABLED(pEntry) = 
                                                     aInfo->isFailoverEnable;
                    DIA_PEER_CHK_IS_FAILBACK_ENABLED(pEntry) =
                                                     aInfo->isFailbackEnable;
                    DIA_PEER_CHK_IF_REDUNDANT_MATE(pEntry) = 
                                                     aInfo->isRedundantMate;
                }
                else
                {
                    if(DIA_PE_PENDING_Q(pEntry) && (!DIA_PE_RETRANSMISSION_ENABLED(pEntry)))
                    {
                        delete DIA_PE_PENDING_Q(pEntry);
                    }    
                    free(hostId);
                    free(hostRealm); 
                    return !ITS_SUCCESS;
                }
            }   
        }
        else
        {
            DT_ERR(("Invalid Peer Entry : %s ",aInfo->altHost));
            return ITS_DIA_EINVALID_PEER;
        }
    }
    else
    {
        DT_ERR(("Invalid Peer Entry : %s ",aInfo->peerName));
        return ITS_DIA_EINVALID_PEER;
    }

    return ret;
}

int
DiaMgmt::GetAlternatePeerForPeer(ALT_PEER_INFO* aInfo)
{
    int ret = ITS_SUCCESS;
    PEER_ENTRY *pEntry = NULL;
    PEER_ENTRY *aEntry = NULL;

    if ((aInfo->peerName == NULL) || (aInfo->realmName == NULL)
       ||(aInfo->altHost == NULL) || (aInfo->altRealmName == NULL))
    {
        DT_ERR(("Invalid Parameter Passed"));
        return !ITS_SUCCESS;
    }

    if (PeerTable::GetPeerTable()->FindEntry(aInfo->peerName,
                                             aInfo->realmName, pEntry))
    {
        if(pEntry->altHost)
        {
            ret = ITS_SUCCESS;
        }
        else
        {
            ret = !ITS_SUCCESS;
        }
    }
    else
    {
        /*
         * Peer Not Present in Peer Table
         */
        DT_DBG(("Invalid Peer Entry : %s ",aInfo->peerName));
        ret = ITS_DIA_EINVALID_PEER;
    }

    return ret;
}

int
DiaMgmt::ModifyAlternatePeer(ALT_PEER_INFO* aInfo)
{
    int ret = ITS_SUCCESS;
    char* hostId    = NULL;
    char* hostRealm = NULL;
    PEER_ENTRY *pEntry = NULL;
    PEER_ENTRY *aEntry = NULL;

    if ((aInfo->peerName == NULL) || (aInfo->realmName == NULL)
       ||(aInfo->altHost == NULL) || (aInfo->altRealmName == NULL))
    {
        DT_ERR(("Invalid Parameter Passed"));
        return !ITS_SUCCESS;
    }

    if (PeerTable::GetPeerTable()->FindEntry(aInfo->peerName,
                                             aInfo->realmName, pEntry))
    {
        if (PeerTable::GetPeerTable()->FindEntry(aInfo->altHost,
                                                 aInfo->altRealmName, aEntry))
        {
            if(pEntry->altHost)
            {
                /* Acquire lock before modifying */
                MUTEX_AcquireMutex(&DIA_PE_MUX(pEntry));

                DIA_PEER_CHK_IS_FAILOVER_ENABLED(pEntry) =
                                                      aInfo->isFailoverEnable;
                DIA_PEER_CHK_IS_FAILBACK_ENABLED(pEntry) =
                                                      aInfo->isFailbackEnable;
                DIA_PEER_CHK_IF_REDUNDANT_MATE(pEntry) =
                                                      aInfo->isRedundantMate;

                /*
                 * If Failover was Enabled previously and now disabled
                 * delete the pending Queue
                 */
                if (!aInfo->isFailoverEnable &&
                                  DIA_PE_PENDING_Q(pEntry) != NULL && (!DIA_PE_RETRANSMISSION_ENABLED(pEntry)))
                {
                    delete DIA_PE_PENDING_Q(pEntry);
                    DIA_PE_PENDING_Q(pEntry) = NULL;
                }

                /* update Alternate host & realm name if it is not matching */
                if ((strcasecmp(DIA_PE_ALT_HOST(pEntry), aInfo->altHost) !=0)
                 || (strcasecmp(DIA_PE_ALT_REALM(pEntry), aInfo->altRealmName) !=0))
                {
                    if (aInfo->isFailoverEnable || aInfo->isRedundantMate)
                    {
                        /* Enable Pending queue if it is not enabled */
                        if (aInfo->isFailoverEnable &&
                            DIA_PE_PENDING_Q(pEntry) == NULL)
                        {
                            DIA_PE_PENDING_Q(pEntry) = new PendingQ(); 
                        }

                        /* Free previous values */
                        char* hostName = (char*)DIA_PE_ALT_HOST(pEntry);
                        char* hostRealm = (char*)DIA_PE_ALT_REALM(pEntry);

                        free(hostName);
                        free(hostRealm);

                        DIA_PE_ALT_HOST(pEntry)  = strdup(aInfo->altHost);
                        DIA_PE_ALT_REALM(pEntry) = strdup(aInfo->altRealmName);
                     }
                }
                /* Release Mutex */
                MUTEX_ReleaseMutex(&DIA_PE_MUX(pEntry));
            }
            else
            {
                /* 
                 * Alternate Host Not set, return AltHost Not Set Error
                 * Call AddAlternate Peer before calling Modify
                 */
                DT_ERR(("Invalid Peer Entry : %s ",aInfo->altHost));
                ret = ITS_DIA_EINVALID_PEER;
            }
        }
        else
        {
            /*
             * Alternate Host Not Present in Peer Table
             * Call Add Peer 
             */
            DT_ERR(("Invalid Peer Entry : %s ",aInfo->altHost));
            ret = ITS_DIA_EINVALID_PEER;
        }
    }
    else
    {
        /*
         * Peer Not Present in Peer Table
         */
        DT_ERR(("Invalid Peer Entry : %s ",aInfo->peerName));
        ret = ITS_DIA_EINVALID_PEER;
    }

    return ret;
}


int DiaMgmt::RemoveSecondaryIp(const char* hostName, const char* realmName,
                          char** multiHomeIpAddrs,int noIPs)
{
    int ret = !ITS_SUCCESS;
    PEER_ENTRY *pEntry = NULL;

    if (PeerTable::GetPeerTable()->FindEntry(hostName,
                                             realmName, pEntry))
    {
        if (DIA_PE_STATE(pEntry) == PEER_ST_CLOSED)
        { 
            for(int i=0;i< noIPs;i++)
            { 
                for(int j=1;j< DIA_PE_CONN_TINFO(pEntry).noIPs;j++)
                {
                    if(strcmp(multiHomeIpAddrs[i],DIA_PE_CONN_TINFO(pEntry).multiHomeipaddrs[j])==NULL)
                    {
                        DT_DBG(("Found secondary ip %s to remove ",multiHomeIpAddrs[i]));
                        DIA_PE_CONN_TINFO(pEntry).noIPs = DIA_PE_CONN_TINFO(pEntry).noIPs - 1;
                        free((char *)DIA_PE_CONN_TINFO(pEntry).multiHomeipaddrs[j]);
                        DIA_PE_CONN_TINFO(pEntry).multiHomeipaddrs[j]=NULL;
                        
                        int k = j;
                        for(;k < DIA_PE_CONN_TINFO(pEntry).noIPs;k++)
                        {
                            DIA_PE_CONN_TINFO(pEntry).multiHomeipaddrs[k] = 
                            DIA_PE_CONN_TINFO(pEntry).multiHomeipaddrs[k + 1];
                        }
                        DIA_PE_CONN_TINFO(pEntry).multiHomeipaddrs[k]=NULL;
                       
                        ret = ITS_SUCCESS;
                        break;
                    }
                }
            }
            DT_DBG(("Peer %s Ips",hostName));
            for(int index = 0; index < DIA_PE_CONN_TINFO(pEntry).noIPs;index++)
            {
                DT_DBG(("Ip Addrs[%d] = %s",index,DIA_PE_CONN_TINFO(pEntry).multiHomeipaddrs[index]));
            }
        }
        else
        {
            DT_ERR(("Peer %s is not in closed state.Sec ips can not be deleted",hostName));
            ret = DEL_SECONDARYIP_ERR_PEER_NOT_IN_CLOSED_STATE;
        }
    }
    else
    {
        DT_ERR(("Peer %s not found for del request for sec ip",hostName));
        ret = DEL_SECONDARYIP_ERR_UNKNOWN_PEER;
    }
    return ret;
}

int DiaMgmt::AddSecondaryIp(const char* hostName, const char* realmName,
                          char** multiHomeIpAddrs,int noIPs)
{
    int ret = !ITS_SUCCESS;
    PEER_ENTRY *pEntry = NULL;

    if (PeerTable::GetPeerTable()->FindEntry(hostName,
                                             realmName, pEntry))
    {
        if (DIA_PE_STATE(pEntry) == PEER_ST_CLOSED)
        {
            if(DIA_PE_CONN_TINFO(pEntry).noIPs == MAX_NO_IPS)
            {
                DT_ERR(("Peer %s is already having max sec ips configured",hostName));
                ret = MOD_PEER_ERR_PEER_MAX_SEC_IPS_CONFIGURED;
            }

            int i = 0;
            int numberIPsRcvd = noIPs; 
            for(int j=DIA_PE_CONN_TINFO(pEntry).noIPs;j< MAX_NO_IPS && numberIPsRcvd;j++)
            { 
                DIA_PE_CONN_TINFO(pEntry).noIPs = DIA_PE_CONN_TINFO(pEntry).noIPs + 1;
                DIA_PE_CONN_TINFO(pEntry).multiHomeipaddrs[j] = multiHomeIpAddrs[i];
                i++;
                numberIPsRcvd--;
                ret = ITS_SUCCESS;
            }
            DT_DBG(("Peer %s Ips",hostName));
            for(int index = 0; index < DIA_PE_CONN_TINFO(pEntry).noIPs;index++)
            {
                DT_DBG(("Ip Addrs%d = %s",index,DIA_PE_CONN_TINFO(pEntry).multiHomeipaddrs[index]));
            }
           
        }
        else
        {
            DT_ERR(("Peer %s is not in closed state.Sec ip can not be added",hostName));
            ret = MOD_PEER_ERR_PEER_IN_OPEN_STATE;
        }
    }
    else
    {
        DT_ERR(("Peer %s not found for add request for sec ip",hostName));
        ret = MOD_PEER_ERR_PEER_NOT_PRESENT;
    }
    return ret;
}

int
DiaMgmt::RemoveAlternatePeer(const char* hostName, const char* realmName)
{
    int ret = ITS_SUCCESS;
    char* hostId    = NULL;
    char* hostRealm = NULL;
    PEER_ENTRY *pEntry = NULL;
    PEER_ENTRY *aEntry = NULL;

    if ((hostName == NULL) || (realmName == NULL))
    {
        DT_ERR(("Invalid Parameter Passed"));
        return !ITS_SUCCESS;
    }

    if (PeerTable::GetPeerTable()->FindEntry(hostName,
                                             realmName, pEntry))
    {
        if(pEntry->altHost)
        {
            /* Acquire lock before modifying */
            MUTEX_AcquireMutex(&DIA_PE_MUX(pEntry));

            //Fixing - Parse Warning - Decleration Hides existing param
            /* Free previous values */
            char* lhostName = (char*)DIA_PE_ALT_HOST(pEntry);
            char* lhostRealm = (char*)DIA_PE_ALT_REALM(pEntry);

            free(lhostName);
            free(lhostRealm);

            DIA_PE_ALT_HOST(pEntry) = NULL;
            DIA_PE_ALT_REALM(pEntry) = NULL;

            DIA_PEER_CHK_IS_FAILOVER_ENABLED(pEntry) = false;
            DIA_PEER_CHK_IS_FAILBACK_ENABLED(pEntry) = false;
            DIA_PEER_CHK_IF_REDUNDANT_MATE(pEntry) = false;

            if (DIA_PE_PENDING_Q(pEntry) != NULL && !(DIA_PE_RETRANSMISSION_ENABLED(pEntry)))
            {
                delete DIA_PE_PENDING_Q(pEntry);
                DIA_PE_PENDING_Q(pEntry) = NULL;
            }

            /* Release Mutex */
            MUTEX_ReleaseMutex(&DIA_PE_MUX(pEntry));
        }
        else
        {
            DT_WRN(("Alternate Host Not Configured for this peer\n"));
            ret = ITS_DIA_EINVALID_PEER;
        }
    }
    else
    {
        DT_ERR(("Peer Entry not Found\n"));
        ret =  ITS_DIA_EINVALID_PEER;
    }

    return ret;
}

int
DiaMgmt::GetDiaTrace(void *arg)
{
    DIA_TRACE_INFO* diaTace = (DIA_TRACE_INFO*)arg;

    if (diaTace == NULL)
    {
        DT_ERR(("Invalid Parameter Passed"));
        return !ITS_SUCCESS;
    }

    diaTace->dbg = ITS_FALSE;
    diaTace->wrn = ITS_FALSE;
    diaTace->err = ITS_FALSE;
    diaTace->crt = ITS_FALSE;

    if (DIA_TRACE()->IsEnabled(DIA_DEBUG) == true)
    {
        diaTace->dbg = ITS_TRUE;
    }
    if (DIA_TRACE()->IsEnabled(DIA_WARNING) == true)
    {
        diaTace->wrn = ITS_TRUE;
    }
    if (DIA_TRACE()->IsEnabled(DIA_ERROR) == true)
    {
        diaTace->err = ITS_TRUE;
    }
    if (DIA_TRACE()->IsEnabled(DIA_CRITICAL) == true)
    {
        diaTace->crt = ITS_TRUE;
    }

    return ITS_SUCCESS;
}

/*
int
DiaMgmt::GetDiaQStat(DIA_QUEUE_STATS* qStats)
{
    int count = 0;
    qStats->upQCount = 0;
    qStats->downQCount = 0;

    if ((count = DiaStackClass::GetDiaStackQCount()) < 0)
    {
        count = 0;
    }

    qStats->upQCount = count;

    if ((count = DiaStackClass::GetDiaStackSenderQCount()) >= 0)
    {
       qStats->downQCount = count; 
    }

    return ITS_SUCCESS;
}*/


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *  API to starts all the Peers which are configured
 *
 *  Input Parameters:
 *      None
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Integer
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
DiaMgmt::StartAllPeers()
{
    int ret;
    if ((ret = InitDynamics()) == ITS_SUCCESS)
    {
        DT_DBG(("DiaStackClass::Succesfully Initialized Peer Transports"));
    }
    else
    {
        DT_CRT(("DiaStackClass:: Fatal Error:: Failed to start"));
        ret = DIA_FAILURE;
    }
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *  API to Start Individual Peer 
 *
 *  Input Parameters:
 *      hostName, realmName
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Integer
 *
 *  Notes:
 *
 *  See Also:
 *
 * Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *  Suresh                                             3.2 Feature
 ****************************************************************************/
int 
DiaMgmt::StartPeer(const char* hostName,
                    const char* realmName)
{
    int ret;
    if ((ret = InitDynamicsPeer(hostName,realmName)) == ITS_SUCCESS)
    {
        DT_DBG(("DiaStackClass::Succesfully Initialized Peer Transport"));
    }
    else
    {
        DT_CRT(("DiaStackClass:: Fatal Error:: Failed to start"));
        //ret = DIA_FAILURE;        
    }
    return ret;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *  API to Removes the Peer entry
 *
 *  Input Parameters:
 *      hostName, realmName
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Integer
 *
 *  Notes:
 *
 *  See Also:
 *
 * Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *   Naresh      30-01-07    Enhancement     RemoveEntry called after connector 
 *                                           /acceptor thread removal.
 *   Naresh      31-01-07    Bug Id 5205     Retry Timer Stopped.
 *
 *   Naresh      21-04-2008  ST-IDIA-0300-01 Fix for Issue #867
 * 
 ****************************************************************************/

int
DiaMgmt::RemovePeer(const char* hostName,
                    const char* realmName)
{
    int ret;
    PEER_ENTRY *pEntry = NULL;
    DESTINATION_INFO destInfo;
 
    DT_DBG(("DiaMgmt::RemovePeer"));

    if (hostName == NULL || realmName == NULL)
    {
        return !ITS_SUCCESS;
    }

    if (PeerTable::GetPeerTable()->FindEntry(hostName, realmName, pEntry))
    {
        if (DIA_PE_STATIC(pEntry))
        {
            DT_ERR(("Cannot remove statically configured Peer"));
            //ret = ITS_DIA_EINVALID_PEER;
            ret = DEL_PEER_ERR_PEER_CONFIGURED_IN_FILE;
        }
        else if (DIA_PE_STATE(pEntry) != PEER_ST_CLOSED)
        {
            //Need to Force Disconnection and the remove.
            DT_ERR(("Found Peer is Not in CLOSED state : Unable to remove peer"));
            //ret = ITS_DIA_TOO_BUSY;
            ret = DEL_PEER_ERR_PEER_NOT_IN_CLOSED_STATE;
        }
        else
        {
            ret = ITS_SUCCESS;
 
            /* Remove all destinations before removing peer*/
            destInfo.peerRealm = realmName;
            destInfo.peerName = hostName ;
 
            if( RemoveAllDestination(&destInfo) != ITS_SUCCESS)
            {
                DT_ERR(("Failed to remove Destinations"));
            }
 
            DiaSocketTransport *connTr =
                (DiaSocketTransport *)DIA_PE_CONN_SPECS(pEntry).trHandle;
            if (connTr)
            {
                DT_WRN(("Signaling shutdown of connector transport"));
                connTr->SetExit(); 
                DIA_PE_CONN_SPECS(pEntry).trHandle = NULL;
                DIA_PE_CONN_SPECS(pEntry).trInst = 0;
            }
            DiaSocketTransport *accTr =
                (DiaSocketTransport *)DIA_PE_ACC_SPECS(pEntry).trHandle;
            if (accTr)
            {
                DT_WRN(("Signaling shutdown of acceptor transport"));
                accTr->SetExit(); 
                DIA_PE_ACC_SPECS(pEntry).trHandle = NULL;
                DIA_PE_ACC_SPECS(pEntry).trInst = 0;
            }
            if (DIA_PE_PENDING_Q(pEntry) != NULL)
            {
                delete DIA_PE_PENDING_Q(pEntry);
                DIA_PE_PENDING_Q(pEntry) = NULL;
            }
            //check and remove the Peer Stack statistics pointer
            /*
            if( ( DIA_PE_STATS(pEntry)) != NULL )
            {
                delete DIA_PE_STATS(pEntry);
                DIA_PE_STATS(pEntry) = NULL;
            }
            */
            DIA_PE_INST(pEntry) = 0;
            DIA_PE_HANDLE(pEntry) = NULL;

            /* Retry connection after disconnect */
            if (DIA_PE_RETRY_TIMER(pEntry) != TIMER_BAD_SERIAL)
            {
                PeerTable::GetPeerTable()->StopTimer(RETRY, pEntry);
            }
            /* Expiry connection after disconnect */
            if (DIA_PE_EXPIRY_TIMER(pEntry) != TIMER_BAD_SERIAL)
            {
                PeerTable::GetPeerTable()->StopTimer(EXPIRY, pEntry);
            }

            if (PeerTable::GetPeerTable()->RemoveEntry(hostName, realmName)
                     != ITS_SUCCESS)
            {
                DT_ERR(("Failed to remove Peer Entry"));
                ret = ITS_DIA_EINVALID_PEER;
            }
            else
            {
                DIA_Alarm(15251, __FILE__, __LINE__, "Peer =%s:Realm=%s",
                          hostName,realmName);
            }
        }
    }
    else
    {
        DT_CRT(("Invalid Peer Name %s in Destination: Discarding", hostName));
        ret = ITS_DIA_UNKNOWN_PEER;
    }
    return ret;
}
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *  API to Disconnect Peer forcefully with run time expiry timeout  
 *
 *  Input Parameters:
 *      hostName, realmName
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Integer
 *
 *  Notes:
 *
 *  See Also:
 *
 * Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ---------------------------------------------------------------------------
 * 
 ****************************************************************************/
int
DiaMgmt::ForceDisconectPeer(const char* hostName, const char* realmName,
                         ITS_INT disCause, ITS_INT expiry)
{
    int ret = ITS_SUCCESS;
    PEER_ENTRY *peerEntry = NULL;
    DiaSocketTransport *tr = NULL;

    DT_DBG(("DiaMgmt::ForceDisconectPeer"));

    if (PeerTable::GetPeerTable()->FindEntry(hostName, realmName, peerEntry))
    {
        /* ForceDisconnect Requirement - Not to initiate connection */
        DIA_PE_IS_FORCE_DISCONNECTED(peerEntry) = true;

        if (DIA_PE_STATE(peerEntry) != PEER_ST_CLOSED)
        {
            /* Set the Disconect cause value */
            peerEntry->disconectCause = disCause;

            /* Cancel the Peer Retry Timer */
            if (DIA_PE_RETRY_TIMER(peerEntry) != TIMER_BAD_SERIAL)
            {
              PeerTable::GetPeerTable()->StopTimer(RETRY, peerEntry);
            }

            if (DIA_PE_EXPIRY_TIMER(peerEntry) != TIMER_BAD_SERIAL)
            {
              PeerTable::GetPeerTable()->StopTimer(EXPIRY, peerEntry);
            }
            tr = trTable[peerEntry->trInst];
            if (tr == NULL)
            {
               //Log an error and continue
               DT_ERR(("Invalid transport"));
            }
            
            DIA_PE_EXPIRY_TIME_VAL(peerEntry) = expiry;
    
            //Warning Fix - suggest parentheses around assignment used as truth value
            if ((ret = DiaMsgRouter::UpdatePeerSM(NULL, peerEntry,
                    PEER_EVT_STOP,tr, NULL)) != ITS_SUCCESS)
            {
              DT_ERR(("SendDPR to peer Failed"));
              //return !ITS_SUCCESS;
              return SET_PEERSTATUS_ERR_DISC_FAIL_SENDING_DPR_FAILED;
            }
            else
            {
              peerEntry->isActive=ITS_FALSE;
            }
        }
        else
        {
            DT_DBG(("Peer is in CLOSED state, setting the status to inactive"));  
            /*
             * Stop the RETRY Timer if already running.
             */
            if (DIA_PE_RETRY_TIMER(peerEntry) != TIMER_BAD_SERIAL)
            {
                PeerTable::StopTimer(RETRY, peerEntry);
            }

            ret = ITS_SUCCESS;
        } 
    }
    else
    {
        DT_WRN(("Invalid Peer Name %s in Destination: Discarding", hostName));
        ret = ITS_DIA_UNKNOWN_PEER;
    }
    return ret;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *  API to Disable the Peer entry by sending DPR in I-OPEN or R-OPEN state
 *  
 *  Input Parameters:
 *      hostName, realmName, disCause
 *  
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      Integer
 *  
 *  Notes:
 *  
 *  See Also:
 * 
 * Revision History:
 * 
 ****************************************************************************/
int
DiaMgmt::DisconnectPeer(const char* hostName,
    const char* realmName, ITS_INT disCause)
{
    int ret = ITS_SUCCESS;
    PEER_ENTRY *peerEntry = NULL;
    DiaSocketTransport *tr = NULL;
 
    DT_DBG(("DiaMgmt::DisconectPeer"));
    
    if (PeerTable::GetPeerTable()->FindEntry(hostName, realmName, peerEntry))
    {
        if (DIA_PE_STATE(peerEntry) != PEER_ST_I_OPEN &&
                    DIA_PE_STATE(peerEntry) != PEER_ST_R_OPEN)
        {
            DT_WRN(("Disconect Failed :: Peer is not in I_OPEN | R_OPEN state"));
            if (DIA_PE_STATE(peerEntry) == PEER_ST_CLOSED && disCause == 2)
            {
                /* Cancel the Peer Retry Timer */
                if (DIA_PE_RETRY_TIMER(peerEntry) != TIMER_BAD_SERIAL)
                {
                  PeerTable::GetPeerTable()->StopTimer(RETRY, peerEntry);
                }
            }
            ret = ITS_DIA_TOO_BUSY;
        }
        else
        {   
            /* Set the Disconect cause value */
            peerEntry->disconectCause = disCause;

            /* Cancel the Peer Retry Timer */
            if (DIA_PE_RETRY_TIMER(peerEntry) != TIMER_BAD_SERIAL)
            {
              PeerTable::GetPeerTable()->StopTimer(RETRY, peerEntry);
            }
    
            tr = trTable[peerEntry->trInst];
            if (tr == NULL)
            {
               DT_ERR(("Invalid transport"));
               return (ITS_EBADTRANSPORT);
            }
            //Warning Fix - suggest parentheses around assignment used as truth value
            if ((ret = DiaMsgRouter::UpdatePeerSM(NULL, peerEntry,
                    PEER_EVT_STOP,tr, NULL)) != ITS_SUCCESS)
            {
              DT_ERR(("SendDPR to peer Failed"));
              return !ITS_SUCCESS;
            }
            else
            {
              peerEntry->isActive=ITS_FALSE;
              DT_DBG(("DiaMgmt::Successfully Disconected  the Peer"));
              return ret;
            }
        }
    }
    else
    {
        DT_WRN(("Invalid Peer Name %s in Destination: Discarding", hostName));
        ret = ITS_DIA_UNKNOWN_PEER;
    }
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *  API to Add the Realm entry
 *               
 *  Input Parameters:
 *      realmName
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Integer
 *
 *  Notes:
 *
 *  See Also:
 *
 * Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *  Naresh        21-04-2008  ST-IDIA-0300-01          Fix for Issue #849
 *
 ****************************************************************************/
int
DiaMgmt::AddRealm(const char* realmName,const char* localAction,ITS_BOOLEAN isProxyEnabled)
{
    int ret;
    REALM_ENTRY *rEntry = NULL;

    if(strcasecmp(localAction, "RELAY") != 0 && isProxyEnabled == ITS_TRUE)
    {
       DT_ERR(("\n Invalid Realm entry :: IsProxyEnabled should be True with localAction is RELAY"));
        DIA_Alarm(15253, __FILE__, __LINE__,
                 "Realm=%s:LocalAction=%s:Reason=INVALID_LOCAL_ACTION",
                  realmName, localAction);

       return ITS_DIA_EINVALID_REALM;
    }

    if (RealmTable::GetRealmTable()->FindEntry(realmName, rEntry))
    {
        DT_DBG(("\n Realm entry is already added"));
        DIA_Alarm(15253, __FILE__, __LINE__,
                 "Realm=%s:LocalAction=%s:Reason=REALM_EXIST",
                  realmName, localAction);

        return ITS_DIA_LOCAL_REALM_MATCH;
    }

    rEntry = (REALM_ENTRY *)malloc(sizeof(REALM_ENTRY));
    if (rEntry == NULL)
    {
        //throw Error - malloc failed
        throw "Error: Malloc failed";
    }

    memset(rEntry, 0, sizeof(REALM_ENTRY));
    rEntry->isDefault = ITS_FALSE;
    rEntry->realmName = strdup(realmName);
    rEntry->isStatic = ITS_FALSE;
    rEntry->destCnt = 0;
  
    if(strcasecmp(localAction, "LOCAL") == 0)
    {
        rEntry->localAction = ITS_DIA_LOCAL; 
    }
    if(strcasecmp(localAction, "RELAY") == 0)
    {
        rEntry->localAction = ITS_DIA_RELAY; 
    }
    if(strcasecmp(localAction, "PROXY") == 0)
    {
        rEntry->localAction = ITS_DIA_PROXY;
    }
    if(strcasecmp(localAction, "REDIRECT") == 0)
    {
        rEntry->localAction = ITS_DIA_REDIRECT;
    }
    rEntry->proxyInfoAvpEnabled = isProxyEnabled; 

    ret = RealmTable::GetRealmTable()->InsertEntry(rEntry);
    if (ret == ITS_SUCCESS)
    {
        DT_DBG(("Succesfully Added Realm Entry"));
        ret = ITS_SUCCESS;
    }
    else
    {
        free ((void *)rEntry->realmName);
        free ((void *)rEntry);
        DT_ERR(("Failed to Add Realm Entry "));
        DIA_Alarm(15253, __FILE__, __LINE__,
                 "Realm=%s:LocalAction=%s:Reason=ERROR",
                  realmName, localAction);

        ret = ITS_DIA_LOCAL_REALM_MISMATCH;
    }
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *  API to Removes the Realm entry
 *
 *  Input Parameters:
 *      realmName
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Integer
 *
 *  Notes:
 *
 *  See Also:
 *
 * Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *  Naresh        21-04-2008   ST-IDIA-0300-01        Fix for Issue #870
 ****************************************************************************/
int
DiaMgmt::RemoveRealm(const char* realmName)
{
    int ret;
    REALM_ENTRY *rEntry = NULL;

    if (RealmTable::GetRealmTable()->FindEntry(realmName, rEntry))
    {
        if (DIA_RE_IS_STATIC(rEntry))
        {
            DT_ERR(("Cannot remove statically configured Realm"));
            //ret = ITS_DIA_REALM_NOT_SERVED;
            ret = DEL_REALM_ERR_CANNOT_MODIFY_REALM_IN_XML;
        }
        else if (RealmTable::GetRealmTable()->RemoveEntry(realmName)!= ITS_SUCCESS)
        {
            DT_ERR(("Failed to remove Realm Entry"));
            ret = ITS_DIA_LOCAL_REALM_MISMATCH;
        }
        else
        {
            DT_DBG(("Succesfully Removed Realm Entry"));
            ret = ITS_SUCCESS;
        }
    }
    else
    {
        DT_CRT(("Invalid Realm Name %s in Destination: Discarding", realmName));
        ret = ITS_DIA_LOCAL_REALM_MISMATCH;
    }
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *  API to add Destination entry of type DESTINATION_INFO for Realm
 *
 *  Input Parameters:
 *      DESTINATION_INFO*
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Integer
 *
 *  Notes:
 *
 *  See Also:
 *
 * Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *  Naresh        23-04-2008   ST-IDIA-0300-01      Enhancement to avoid 
 *                                                  Duplicate Entries
 *
 ****************************************************************************/
int
DiaMgmt::AddDestination(DESTINATION_INFO* destInfo)
{
    int ret = !ITS_SUCCESS;
    bool isSuccess = true;
    static ITS_UINT rDstCnt = 0; 
    ITS_UINT found = 0;
    PEER_ENTRY *pEntry = NULL;
    REALM_ENTRY *rEntry = NULL;

    if (!(RealmTable::GetRealmTable()->FindEntry( destInfo->realmName, rEntry)))
    {
        DT_WRN(("Realm not Present. Adding Realm Entry"));
        if ((ret = AddRealm(destInfo->realmName, "LOCAL", false)) != ITS_SUCCESS)
        {
            DT_WRN(("Add Realm Failed with Return Code:%d", ret));
            DIA_Alarm(15252, __FILE__, __LINE__,
                     "Peer=%s:PeerRealm=%s:Realm=%s:Reason=REALM_ERROR",
                      destInfo->peerName, destInfo->peerRealm,
                      destInfo->realmName);
            return ret;
        }
       
        /* To get realmEntry */
        if (RealmTable::GetRealmTable()->FindEntry( destInfo->realmName, rEntry))
        {
            isSuccess = true;
        }
        else
        {
            DIA_Alarm(15252, __FILE__, __LINE__,
                     "Peer=%s:PeerRealm=%s:Realm=%s:Reason=REALM_ERROR",
                      destInfo->peerName, destInfo->peerRealm,
                      destInfo->realmName);

            DT_ERR(("Cannot Find Realm Entry"));
            //return !ITS_SUCCESS;
            return SET_DEST_ERR_REALM_NOT_PRESENT;
        }
    }

    if (isSuccess)
    {
        rDstCnt = rEntry->destCnt;

        /* check destination count before inserting */
        if (rDstCnt >= MAX_LIST_SIZE)
        {
            DT_WRN(("Add Destination Failed. Maximum No of Destination per realm is %d", 
                                                                        MAX_LIST_SIZE));
            DIA_Alarm(15252, __FILE__, __LINE__,
                     "Peer=%s:PeerRealm=%s:Realm=%s:Reason=MAX_DEST",
                      destInfo->peerName, destInfo->peerRealm,
                      destInfo->realmName);

            //return !ITS_SUCCESS;
            return SET_DEST_ERR_MAX_NO_OF_DEST_PER_REALM_REACHED;
        }

        if (PeerTable::GetPeerTable()->FindEntry(destInfo->peerName, 
                                                 destInfo->peerRealm, pEntry))
        {
            for(int i=0;i<rDstCnt;i++)
            {
                if((rEntry->destSpecs[i].peer == pEntry) &&
                  (rEntry->destSpecs[i].appIdentifier.appId ==
                  destInfo->applicationId))
                {
                    found = 1;
                    DT_WRN(("Destination Entry already Exist ,Failed to Add"));
                    DIA_Alarm(15252, __FILE__, __LINE__,
                             "Peer=%s:PeerRealm=%s:Realm=%s:Reason=DEST_EXIST",
                              destInfo->peerName, destInfo->peerRealm,
                              destInfo->realmName);

                    return !ITS_SUCCESS;  
                }
            }
            if(found != 1)
            { 
                if (RealmTable::InsertDestination(rEntry, pEntry,
                                             destInfo->applicationId, 
                                             destInfo->vendorId, 
                                             destInfo->priority) == ITS_SUCCESS)
                {
                    DT_DBG(("Succesfully Added Destination Entry"));
                    return ITS_SUCCESS;
                }
                else
                {
                    DT_ERR(("Destination Entry already Exist for this peer"));
                    DT_ERR(("for same App Id & Vendor Id in this realm"));
                    DT_ERR(("Failed to Add Destination"));
                    DIA_Alarm(15252, __FILE__, __LINE__,
                             "Peer=%s:PeerRealm=%s:Realm=%s:Reason=DEST_EXIST",
                              destInfo->peerName, destInfo->peerRealm,
                              destInfo->realmName);

                    return !ITS_SUCCESS;
                }
            }
        }
        else
        {
            DT_CRT(("Invalid Peer Name %s in Destination: Discarding", 
                                                  destInfo->peerName));
            DIA_Alarm(15252, __FILE__, __LINE__,
                     "Peer=%s:PeerRealm=%s:Realm=%s:Reason=INVALID_PEER",
                      destInfo->peerName, destInfo->peerRealm,
                      destInfo->realmName);

            return ITS_DIA_EINVALID_PEER;
        }
    }
    return ret;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *  API to Modify the Destination Priority.
 *
 *  Input Parameters:
 *      DESTINATION_INFO*
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Integer
 *
 *  Notes:
 *
 *  See Also:
 *
 *
 ****************************************************************************/
int
DiaMgmt::ModifyDestinationPriority(DESTINATION_INFO* destInfo)
{
    int rDstCnt = 0;
    bool found = false;
    PEER_ENTRY *pEntry = NULL;
    REALM_ENTRY *rEntry = NULL;

    if (RealmTable::GetRealmTable()->FindEntry(destInfo->realmName, rEntry))
    {
        rDstCnt = rEntry->destCnt;

        if (PeerTable::GetPeerTable()->FindEntry(destInfo->peerName,
                                                 destInfo->peerRealm, pEntry))
        {
            for(int i=0;i<rDstCnt;i++)
            {
                if((rEntry->destSpecs[i].peer == pEntry) &&
                   (rEntry->destSpecs[i].appIdentifier.appId ==
                                     destInfo->applicationId) &&
                   (rEntry->destSpecs[i].appIdentifier.vendorId ==
                                     destInfo->vendorId))
                {
                    found = true;
                    /* Entry found. Remove old entry.*/
                    RemoveDestination(destInfo);
                    break;
                }
            }

            if(found)
            {

                /* Old entry removed. Insert new priority. */
                if(AddDestination(destInfo)==ITS_SUCCESS)
                {
                    DT_DBG(("Succesfully Modified destination priority"));
                    return ITS_SUCCESS;
                }
            }
        }
    }

    DT_ERR(("Destination Entry Not Found"));
    return !ITS_SUCCESS;
}

/************************************************************************
 *  Purpose:
 *  API to Set Default Route 
 *
 *  Input Parameters:
 *      PeerName, RealmName
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Integer
 *
 *  Notes:
 *
 *  See Also:
 *
 *****************************************************************************/
int
DiaMgmt::SetDefaultRoute(const char* peerName, const char* realmName)
{
    int ret = ITS_SUCCESS;
    PEER_ENTRY *entry =  NULL;
    REALM_ENTRY *rEntry = NULL;

    if (PEER_TABLE->FindEntry(peerName, realmName, entry))
    {
        if (REALM_TABLE->FindDefaultEntry(realmName, rEntry))
        {
            /* 
             * check if it is default route, 
             * if yes remove that and insert new entry
             */
            if (rEntry->realmName)
            {
                free((void *)rEntry->realmName);
                rEntry->realmName = NULL;
            }
 
            free((void *)rEntry);
            rEntry = NULL;
        }

        //insert new realm entry 
        rEntry = (REALM_ENTRY *)malloc(sizeof(REALM_ENTRY));
        if (rEntry == NULL)
        {
            throw "Error: Malloc failed";
        }

        memset(rEntry, 0, sizeof(REALM_ENTRY));
        rEntry->isDefault = ITS_TRUE;
        rEntry->realmName = strdup(realmName);
        rEntry->isStatic = ITS_FALSE;
        rEntry->destCnt = 0;
        rEntry->destSpecs[0].peer = entry;
        rEntry->destSpecs[0].isRedirectAgent = false;

        ret = RealmTable::GetRealmTable()->InsertEntry(rEntry);
        if (ret == ITS_SUCCESS)
        {
            DT_DBG(("Succesfully Added Realm Entry"));
            ret = ITS_SUCCESS;
        }
        else
        {
            free ((void *)rEntry->realmName);
            free ((void *)rEntry);
            DT_ERR(("Failed to Add Default Realm Entry "));
            ret = !ITS_SUCCESS;
        }
    }
    else
    {
        /* peer entry not present. add peer before setdefaultRoute */
        ret = ITS_DIA_EINVALID_PEER;
    }

    return ret;
}

int
DiaMgmt::RemoveDefaultRoute()
{
    REALM_ENTRY *rEntry = NULL;
    int ret = !ITS_SUCCESS;

    if (REALM_TABLE->FindDefaultEntry(NULL, rEntry))
    {
        if (rEntry->realmName)
        {
            free((void *)rEntry->realmName);
            rEntry->realmName = NULL;
        }

        free((void *)rEntry);
        rEntry = NULL;

        ret = REALM_TABLE->RemoveDefaultEntry();
    }
    return ret;
}


int 
DiaMgmt::GetDefaultRoute(DESTINATION_INFO *dstInfo)
{
    int ret = !ITS_SUCCESS;

    REALM_ENTRY *rEntry = NULL;

    if (REALM_TABLE->FindDefaultEntry(NULL, rEntry))
    {
        dstInfo->realmName = NULL;
        dstInfo->applicationId = 0;
        dstInfo->vendorId = 0;
        dstInfo->priority = 0;

        dstInfo->peerName = rEntry->destSpecs[0].peer->hostIdentity;
        dstInfo->peerRealm = rEntry->destSpecs[0].peer->realmName; 

        ret = ITS_SUCCESS;
    }
    return ret;
}

int
DiaMgmt::GetLocalHostInfo(LOCAL_HOST_INFO *lHostInfo) 
{
    int ret = !ITS_SUCCESS;
    lHostInfo->hostName = itsDiaConfig.getLocalHostName();
    lHostInfo->realmName = itsDiaConfig.getLocalRealmName();
    lHostInfo->ipAddr = itsDiaConfig.GetLocalIpAddr();
    ret = ITS_SUCCESS; 
    return ret;
}

/************************************************************************
 *  Purpose:
 *  API to Remove All Destinations of a Peer
 *
 *  Input Parameters:
 *      DESTINATION_INFO*
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Integer
 *
 *  Notes:
 *
 *  See Also:
 *
 *****************************************************************************/
int
DiaMgmt::RemoveAllDestination(DESTINATION_INFO* destInfo)
{
    REALM_ENTRY *rEntry = NULL;
    PEER_ENTRY *pEntry = NULL;
    int totalRealm = REALM_TABLE->FindRealmCount();
 
    if (!PEER_TABLE->FindEntry(destInfo->peerName,
                               destInfo->peerRealm,
                               pEntry) )
    {
        DT_ERR(("Invalid Destination "));
        return !ITS_SUCCESS;
    }

    REALM_TABLE->RemoveAllDestination(pEntry);
 
    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *  API to Remove Destination entry of type DESTINATION_INFO for Realm
 *
 *  Input Parameters:
 *      DESTINATION_INFO*
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Integer
 *
 *  Notes:
 *
 *  See Also:
 *
 * Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *  Naresh        23-04-2008   ST-IDIA-0300-01      Enhancement for #891
 *                                                  in Whizible     
 *
 ****************************************************************************/
int
DiaMgmt::RemoveDestination(DESTINATION_INFO* destInfo)
{
    //Initializing Uninitialized Scalar variable
    int ret = ITS_SUCCESS;
    static ITS_UINT reDstCnt = 0;
    ITS_UINT found = 0;
    PEER_ENTRY *pEntry = NULL;
    REALM_ENTRY *rEntry = NULL;

    if (RealmTable::GetRealmTable()->FindEntry( destInfo->realmName, rEntry))
    {
        reDstCnt = rEntry->destCnt;

        if (PeerTable::GetPeerTable()->FindEntry(destInfo->peerName,
                                                 destInfo->peerRealm, pEntry))
        {
           for(int i=0;i<reDstCnt;i++)
           {
             if((rEntry->destSpecs[i].peer == pEntry) && 
                (rEntry->destSpecs[i].appIdentifier.appId ==
                destInfo->applicationId) &&
                (rEntry->destSpecs[i].appIdentifier.vendorId ==
                destInfo->vendorId))
             {
                if (reDstCnt == 1)
                {
                    rEntry->destSpecs[i].peer = NULL;
                    if (DIA_PE_IS_DISCOVERED(pEntry))
                    {
                        if(RemoveRealm(destInfo->realmName) == ITS_SUCCESS)
                        {
                            DT_DBG(("Succesfully Removed Destination Entry"));
                            rEntry->destCnt = 0;
                            return ITS_SUCCESS;
                        }
                    }
                }
                found = 1;
                rEntry->destSpecs[i].peer = NULL;
                if(i == reDstCnt-1)
                {
                   break;
                }
             }
             if(found == 1 && i<reDstCnt-1)
             {
                rEntry->destSpecs[i].peer =
                rEntry->destSpecs[i+1].peer;
                rEntry->destSpecs[i].appIdentifier.appId =
                rEntry->destSpecs[i+1].appIdentifier.appId;
                rEntry->destSpecs[i].appIdentifier.vendorId =
                rEntry->destSpecs[i+1].appIdentifier.vendorId;
                rEntry->destSpecs[i].priority =
                rEntry->destSpecs[i+1].priority;
             }
           }
           if(found == 1)
           {
               rEntry->destCnt = reDstCnt-1;
               rEntry->destSpecs[rEntry->destCnt].peer = NULL;
               DT_DBG(("Succesfully Removed Destination Entry"));
               return ITS_SUCCESS;
           }
           else
           {
               DT_WRN(("AppId, VendorId, Priority Combination not found"));
               return DEL_DEST_ERR_COMB_APPID_VENDID_PRIORITY_NOT_FOUND; 
           } 
        }
        else
        {
            DT_CRT(("Invalid Peer Name %s in Destination: Discarding",
                                                  destInfo->peerName));
            return ITS_DIA_EINVALID_PEER;
        }
    }
    else
    {
        DT_CRT(("Invalid RealmName "));
        ret = ITS_DIA_LOCAL_REALM_MISMATCH;
    }
    return ret;

}
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *  API to set Proxy Info AVP Enabled in Realm Configuration. 
 *      
 *  Input Parameters:
 *      realmName, pinfoEnable
 *      
 *  Input/Output Parameters:
 *      None.
 *          
 *  Output Parameters:
 *      None.
 *      
 *  Return Value:
 *      Integer
 *      
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/

//Proxy-Info AVP for Relay 
int
DiaMgmt::SetProxyInfoAVPEnabled(const char* realmName, ITS_BOOLEAN pinfoEnable)
{
    int ret;
    REALM_ENTRY *rEntry = NULL;
    
    if (RealmTable::GetRealmTable()->FindEntry(realmName, rEntry))
    {
        if (DIA_RE_L_ACTION(rEntry) != ITS_DIA_RELAY)
        {
            DT_ERR(("Invalid Configuration:"));
            DT_ERR(("Cannot change Proxy-Info AVP status when localAction is" \
                    "LOCAL or PROXY or REDIRECT\n"));
            ret = (!ITS_SUCCESS);
        }
        else
        {
            DIA_RE_PXY_INFO_ENABLED(rEntry) = pinfoEnable;
            if(pinfoEnable == ITS_TRUE)
            {
                DT_DBG(("Proxy-Info AVP for Relay is Enabled"));
            }
            else
            {
                DT_DBG(("Proxy-Info AVP for Relay is Disabled"));
            }
            ret = ITS_SUCCESS;
        }
    }
    else
    {
        DT_ERR(("Realm Entry Not Found"));
        ret = ERROR_REALM_NOT_CORRECT;
    }
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *  API to Shows Peer Table Information
 *
 *  Input Parameters:
 *      None
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Integer
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
DiaMgmt::IsProxyInfoAvpEnabled(std::ostream& oss, const char *realmName)
{
    REALM_ENTRY *rEntry = NULL;

    if (RealmTable::GetRealmTable()->FindEntry(realmName, rEntry))
    {
        oss << "Proxy-Info AVP Enabled : "<<
        ((rEntry->proxyInfoAvpEnabled == 0) ? "No" : "Yes")<<endl;
        return ITS_SUCCESS;
    }
    oss << "Entry for "<<realmName<<" is not found"<<endl;
    return !ITS_SUCCESS; 
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *  API to add IP address for Peer under SCTP tranport
 *      
 *  Input Parameters:
 *      peerName, ipAddr
 *      
 *  Input/Output Parameters:
 *      None.
 *          
 *  Output Parameters:
 *      None.
 *      
 *  Return Value:
 *      Integer
 *      
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/

//SCTP MultiHoming
int
DiaMgmt::AddIp(const char* peerName, const char* ipAddr) 
{
    int ret;
    const char **dynIPaddrs = NULL;
    PEER_ENTRY *pEntry = NULL;
    
    if (PeerTable::GetPeerTable()->FindEntry(peerName, pEntry))
    {   
        
        if (DIA_PE_STATIC(pEntry))
        {
            DT_ERR(("Cannot add IP to statically configured Peer"));
            return ITS_DIA_EINVALID_PEER;
        }
        if (DIA_PE_CONN_TINFO(pEntry).type == ITS_DIA_T_SCTP)
        {    
            dynIPaddrs = DIA_PE_CONN_TINFO(pEntry).multiHomeipaddrs;
            if (DIA_PE_CONN_TINFO(pEntry).noIPs == 1)
            {
                dynIPaddrs[0] = (char *)DIA_PE_CONN_TINFO(pEntry).serverIpAddr;
            }
            dynIPaddrs[DIA_PE_CONN_TINFO(pEntry).noIPs]  = strdup(ipAddr);
            DIA_PE_CONN_TINFO(pEntry).noIPs ++;
            ret = ITS_SUCCESS;
        }
        else
        {
            DT_DBG(("Not SCTP Tranport type"));
            return ITS_DIA_LIMITED_SUCCESS;
        }
    }
    else
    {
        DT_ERR(("Invalid Peer Entry"));
        return ITS_DIA_EINVALID_PEER;
    }
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *  API to Shows Peer Table Information
 *
 *  Input Parameters:
 *      None
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Integer
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
DiaMgmt::PrintPeerTable(std::ostream& oss)
{
    oss << *(PeerTable::GetPeerTable());
    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *  API to Shows Realm Table Information
 *
 *  Input Parameters:
 *      None
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Integer
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
DiaMgmt::PrintRealmTable(std::ostream& oss)
{
    oss << *(RealmTable::GetRealmTable());
    return ITS_SUCCESS;
}

#ifdef TLS_ENABLED
static void 
HandleSessionTraceTLSSections()
{
    ITS_INT i;
    bool trace;
    ITS_CHAR tlsCipherSuite[30];
    ITS_CHAR tlsCertificateType[30];
    
    memset(tlsCertificateType, 0, 30);
    memset(tlsCipherSuite, 0, 30);

    ITSDiaConfig::AuthSessionConfig& authsCfg = config->GetAuthSessionConfig();

    fprintf(tempfp, "\n%*c<%s>\n",
		    tab*2, ' ', DIA_SESSION_CFG_STRING);

    /* AuthSession Section. start */
    fprintf(tempfp, "%*c<%s \n"
                     "%*c%4s = \"%d\" \n"
                     "%*c%4s = \"%d\" \n"
                     "%*c%4s = \"%d\" >\n"
                     "%*c</%s> \n",
                     tab*2, ' ',
                     DIA_SESSION_AUTH_STRING,
                     tab*2, ' ', DIA_SESSION_TIMEOUT_STRING,
                     authsCfg.GetTimeout(),
                     tab*2, ' ', DIA_SESSION_LIFETIME_STRING,
                     authsCfg.GetLifeTime(),
                     tab*2, ' ', DIA_SESSION_GRACE_STRING,
                     authsCfg.GetGracePeriod(),
                     tab*2, ' ', DIA_SESSION_AUTH_STRING);
    /* AuthSession Section end */
    /* Accounting session start */
    ITSDiaConfig::AcctSessionConfig& acctsCfg = config->GetAcctSessionConfig();
    fprintf(tempfp, "%*c<%s \n"
                    "%*c%4s = \"%d\" \n"
                    "%*c%4s = \"%d\"> \n"
                    "%*c</%s> \n",
                    tab*2, ' ', DIA_SESSION_ACCT_STRING,
                    tab*2, ' ', DIA_SESSION_TIMEOUT_STRING,
                    acctsCfg.GetTimeout(),
                    tab*2, ' ', DIA_SESSION_INTERIM_INTVL_STRING,
                    acctsCfg.GetInterimIntvl(),
                    tab*2, ' ', DIA_SESSION_ACCT_STRING);
    /* Accounting session end */
    fprintf(tempfp, "%*c</%s>\n\n",tab*2, ' ',DIA_SESSION_CFG_STRING);

    /* TraceSubsystem Section start */
    fprintf(tempfp, "%*c<%s>\n"
                     "%*c<%s %s = \"%s\"/> \n"
                     "%*c<%s %s = \"%s\"/> \n"
                     "%*c<%s %s = \"%s\"/> \n"
                     "%*c<%s %s = \"%s\"/> \n"
                     "%*c</%s>\n\n",tab*2, ' ', DIA_TRACE_SUBSYSTEM_STRING, 
                     tab*2, ' ', DIA_CRITICAL_STRING,
                     DIA_TRACE_OUTPUT_STRING,
                     (((DIA_TRACE()->IsEnabled(DIA_CRITICAL)) == true) ? "stdout":""),
                     tab*2, ' ', DIA_ERROR_STRING,
                     DIA_TRACE_OUTPUT_STRING,
                     (((DIA_TRACE()->IsEnabled(DIA_ERROR)) == true) ? "stdout":""),
                     tab*2, ' ', DIA_WARNING_STRING,
                     DIA_TRACE_OUTPUT_STRING,
                     (((DIA_TRACE()->IsEnabled(DIA_WARNING)) == true) ? "stdout":""),
                     tab*2, ' ', DIA_DEBUG_STRING,
                     DIA_TRACE_OUTPUT_STRING,
                     (((DIA_TRACE()->IsEnabled(DIA_DEBUG)) == true) ? "stdout":""), 
                     tab*2, ' ',DIA_TRACE_SUBSYSTEM_STRING);

    /* TraceSubsystem Section end */
   
    ITSDiaConfig::SecurityConfig& sConf = config->GetSecurityConfig();
    if (sConf.GetTlsType() == 0)
    {
        /* If TLS Security is not configured don't write it to xml */
        return;
    }
    
    switch (sConf.GetCipherSuite())
    {
        case TLS_RSA_WITH_RC4_128_MD5:
            strncpy(tlsCipherSuite, DIA_CIPHER_RSA_RC4_MD5_STRING, strlen(DIA_CIPHER_RSA_RC4_MD5_STRING));
            break;

        case TLS_RSA_WITH_RC4_128_SHA:
            strncpy(tlsCipherSuite, DIA_CIPHER_RSA_RC4_SHA_STRING, strlen(DIA_CIPHER_RSA_RC4_SHA_STRING));
            break;

        case TLS_RSA_WITH_3DES_EDE_CBC_SHA:
            strncpy(tlsCipherSuite, DIA_CIPHER_RSA_3DESEDECBC_SHA_STRING, strlen(DIA_CIPHER_RSA_3DESEDECBC_SHA_STRING));
            break;

        case TLS_RSA_WITH_AES_128_CBC_SHA:
            strncpy(tlsCipherSuite, "RSA-RC4128-SHA", strlen("RSA-RC4128-SHA"));
            break;

        case TLS_RFC_3588_ALL:
            strncpy(tlsCipherSuite, DIA_CIPHER_RFC_3588_ALL_STRING, strlen(DIA_CIPHER_RFC_3588_ALL_STRING));
            break;
        
        default:
            strncpy(tlsCipherSuite, DIA_CIPHER_RFC_3588_ALL_STRING, strlen(DIA_CIPHER_RFC_3588_ALL_STRING));
            break;
    }

    switch(sConf.GetCertificateType())
    {
        case NO_CERT:
            //Correcting Calling risky function  
            strncpy(tlsCertificateType, "NO-Certificate",strlen("NO-Certificate"));
            break;

        case ITS_X509:
            //Correcting Calling risky function  
            strncpy(tlsCertificateType, "X.509", strlen("X.509"));
            break;

        case OPENSSL:
            //Correcting Calling risky function  
            strncpy(tlsCertificateType, "OpenSSL", strlen("OpenSSL"));
            break;

        default:
            //Correcting Calling risky function  
            strncpy(tlsCertificateType, "X.509", strlen("X.509"));
            break;
    }

    fprintf(tempfp, "%*c<%s \n"
                     "%*c%4s = \"%s\" \n"
                     "%*c%4s = \"%d\" \n"
                     "%*c%4s = \"%s\" \n"
                     "%*c%4s = \"%s\" \n"
                     "%*c%4s = \"%s\" \n"
                     "%*c%4s = \"%s\" \n"
                     "%*c%4s = \"%s\" \n"
                     "%*c%4s = \"%s\" \n"
                     "%*c%4s = \"%s\" >\n"
                     "%*c</%s>\n",tab*2, ' ', 
                     DIA_SECURITY_STRING,
                     tab*2, ' ', DIA_TLS_TYPE_STRING,
                     DIA_TLS_TYPE_TO_TEXT(sConf.GetTlsType()),
                     tab*2, ' ', DIA_TLS_TRACE_LEVEL_STRING,
                     sConf.GetTLSTraceLevel(),
                     tab*2, ' ', DIA_IDENTITY_VERIFICATION_STRING,
                     ((sConf.IsIdentityVerifyEnabled() == true)? "yes":"no"),
                     tab*2, ' ', DIA_CIPHER_SUITE_STRING,tlsCipherSuite,
                     tab*2, ' ', DIA_CERTIFICATE_TYPE_STRING,
                     tlsCertificateType,
                     tab*2, ' ', DIA_CL_CERTIFICATE_FILE_STRING,
                     sConf.GetClientCertFile(),
                     tab*2, ' ', DIA_CL_KEY_FILE_STRING,
                     sConf.GetClientKeyFile(),
                     tab*2, ' ', 
                     DIA_SER_CERTIFICATE_FILE_STRING,sConf.GetServCertFile(),
                     tab*2, ' ', 
                     DIA_SER_KEY_FILE_STRING,sConf.GetServKeyFile(),
                     tab*2, ' ', DIA_SECURITY_STRING);
} 
#endif

static void 
HandleLocalConfiguration()
{
    DIA_HOST_INFO_LIST& hInfoList = config->GetHostInfoList();
    const char* mateHost  = NULL;
    DIA_CER *cer;
    ITS_INT i = 0, j = 0; /* Local variables */
    cer = itsDiaConfig.GetLocalCER();

    fprintf(tempfp, "%*c<%4s   %4s = \"%d\" /> \n",tab*2, ' ', 
                     DIA_INSECURITY_ID_STRING,
                     DIA_VALUE_STRING, cer->getInbandSecurityId(0).value());

    fprintf(tempfp, "%*c<%4s %15s = \"%d\" /> \n",tab*2, ' ',
                     DIA_VENDOR_ID_STRING,
                     DIA_VALUE_STRING, cer->getVendorId().value());
    for (i = 0; i<(cer->countSupportedVendorId());)
    {
        fprintf(tempfp, "%*c<%4s  %4s = \"%d\" /> \n",tab*2, ' ', 
                     DIA_SUPP_VENDOR_ID_STRING,
                     DIA_VALUE_STRING, cer->getSupportedVendorId(i++).value());
    }
 
    /* AuthorizationApplicationId Start */
    for(i = 0; i<(cer->countAuthApplicationId());)
    {
        fprintf(tempfp, "%*c<%4s  %4s = \"%d\" /> \n",tab*2, ' ',
                         DIA_AUTH_APP_ID_STRING,
                         DIA_VALUE_STRING, 
                         cer->getAuthApplicationId(i++).value());
    }
    /* AuthorizationApplicationId End */

    fprintf(tempfp, "\n");

    /* AccountingApplicationId starts */
    for (i=0;i<cer->countAcctApplicationId(); )
    {
        fprintf(tempfp, "%*c<%4s %4s = \"%d\" /> \n",tab*2, ' ', 
                         DIA_ACCT_APP_ID_STRING,
                         DIA_VALUE_STRING, 
                         cer->getAcctApplicationId(i++).value());
    }

    /* AccountingApplicationId end */
  
    fprintf(tempfp, "\n%*c%s\n", tab*2, ' ', 
                    "<!-- Vendor-Specific-Application-Id -->");

    /* VendorSpecificApplicationIds Section Starts*/

    for (i = 0; i < cer->countVendorSpecificApplicationId(); i++)
    {
        const base::VendorSpecificApplicationId *lvs = 
                                       &cer->getVendorSpecificApplicationId(i);
        if (lvs->containsAuthApplicationId())
        {
           /* Authorisation info 1st */
            fprintf(tempfp, "%*c<%4s> \n",tab*2, ' ', 
                             DIA_VENDOR_SPEC_APP_ID_STRING);
            fprintf(tempfp, "%*c<%4s  %4s = \"%d\"/> \n"
                             "%*c<%4s %4s = \"%d\"/> \n", tab*2, ' ', 
                             DIA_VENDOR_ID_STRING,DIA_VALUE_STRING,
                             lvs->getVendorId(i).value(), tab*2, ' ', 
                             DIA_AUTH_APP_ID_STRING,DIA_VALUE_STRING,
                             lvs->getAuthApplicationId().value());

            fprintf(tempfp, "%*c</%s> \n\n",tab*2, ' ', 
                             DIA_VENDOR_SPEC_APP_ID_STRING);
        }
        else if(lvs->containsAcctApplicationId())
        {
            fprintf(tempfp, "%*c<%s> \n",tab*2, ' ', 
                            DIA_VENDOR_SPEC_APP_ID_STRING);
            ITS_UINT accId =0;
            accId = lvs->getAcctApplicationId().value();

            fprintf(tempfp, "%*c<%4s        %4s = \"%d\"/> \n"
                            "%*c<%4s %4s = \"%d\"/> \n", tab*2, ' ',
                            DIA_VENDOR_ID_STRING,DIA_VALUE_STRING,
                            lvs->getVendorId(0).value(), tab*2, ' ',
                            DIA_ACCT_APP_ID_STRING,DIA_VALUE_STRING,accId);

            fprintf(tempfp, "%*c</%s> \n\n",tab*2, ' ', 
                            DIA_VENDOR_SPEC_APP_ID_STRING);

         }

    }

    /* VendorSpecificApplicationIds Section ends */

    for(int i=0;i<hInfoList.count;i++)
    { 
        DIA_HOST_INFO hInfo = hInfoList.arr[i];
        fprintf(tempfp, "\t\t<%s" 
                     " %4s = \"%s\" \n",
                      DIA_HOST_INFO_STRING,
                      DIA_SERV_HOST_NAME_STRING,hInfo.servHostName);

        mateHost = itsDiaConfig.getMateHostName();

        if (mateHost != NULL)
        {
            fprintf(tempfp, "\t\t           %4s   = \"%s\"\n",
                            DIA_MATE_HOST_NAME_STRING,
                            mateHost);
        }
        fprintf(tempfp, "\t\t           %4s      = \"%s\" > \n",
                        DIA_REALM_NAME_STRING,hInfo.realmName);



        for(int j=0;j<hInfo.transCnt;j++)
        {  
            DIA_TRANS_INFO tInfo=hInfo.transList[j];
            fprintf(tempfp, "\n\t\t\t<%s \n",DIA_TRANS_STRING);
            fprintf(tempfp, "\t\t\t%4s = \"%s\"\n"
                            "\t\t\t%4s = \"%s\" \n",
                DIA_TRANS_TYPE_STRING,
                ((tInfo.type == ITS_DIA_T_TCP) ? "TCP":"SCTP"),
                DIA_SERV_IP_STRING,
                tInfo.serverIpAddr);

            if (tInfo.publicServerIpAddr)
            {
                fprintf(tempfp, "\t\t\t%4s = \"%s\" \n",
                                 DIA_PUBLIC_SERV_IP_STRING,
                                 tInfo.publicServerIpAddr);
            }

            fprintf(tempfp, "\t\t\t%4s = \"%d\" > \n",
                DIA_PORT_INFO_STRING,
                tInfo.portNo);

            fprintf(tempfp, "\t\t\t</%s>\n\n",DIA_TRANS_STRING);
        }   
    }
    fprintf(tempfp, "\t\t</%s>\n", DIA_HOST_INFO_STRING);
    
#ifdef TLS_ENABLED
    HandleSessionTraceTLSSections();
#endif
    if (itsDiaConfig.IsQueueMgmtEnabled())
    {
        fprintf(tempfp, "\t<%s   enable = \"yes\"\n", DIA_QUEUE_MGMT_STRING);
    }
    else
    {
        fprintf(tempfp, "\t<%s   enable = \"no\"\n", DIA_QUEUE_MGMT_STRING);
    }

    int count = itsDiaConfig.GetQueueMgmt().GetDownStreamThreadCount();
    fprintf(tempfp, "\t\t%s   = \"%d\">\n", DIA_NUM_DOWNSTREAM_THREADS, count);

    count = itsDiaConfig.GetQueueMgmt().GetUpStreamThreadCount();
    fprintf(tempfp, "\t\t%s   = \"%d\">\n", DIA_NUM_UPSTREAM_THREADS, count);

    fprintf(tempfp, "\t</%s>\n", DIA_QUEUE_MGMT_STRING);
}

static void 
HandlePeerConfiguration()
{
    ITSDiaConfig::PeerTimersConfig& ptConf = config->GetPeerTimers();
    PEER_ENTRY *entry = PeerTable::GetPeerTable()->FindFirstEntry();


    fprintf(tempfp, "%*c<%s>\n"
                            "%*c<%4s %s = \"%s\" %s = \"%d\" /> \n"
                            "%*c<%4s %s = \"%s\" %s = \"%d\" /> \n"
                            "%*c<%4s %s = \"%s\" %s = \"%d\" /> \n\n"
                            "%*c<%4s %s = \"%d\" /> \n"
                            "%*c<%4s %s = \"%d\" /> \n\n",
                            tab*1, ' ', DIA_PEER_CONFIG_STRING,
                            tab*2, ' ', DIA_TIMER_STRING, 
                            DIA_NAME_STRING, "Tc",
                            DIA_VALUE_STRING, ptConf.GetRetry(),
                            tab*2, ' ', DIA_TIMER_STRING, 
                            DIA_NAME_STRING, "Expiry",
                            DIA_VALUE_STRING, ptConf.GetExpiry(),
                            tab*2, ' ', DIA_TIMER_STRING, 
                            DIA_NAME_STRING, "Watchdog",
                            DIA_VALUE_STRING, ptConf.GetWatchdog(),
                            tab*2, ' ', DIA_RETRANS_INTVL_STRING, 
                            DIA_VALUE_STRING, ptConf.GetRetransIntvl(),
                            tab*2, ' ', DIA_RETRANS_COUNT_STRING, 
                            DIA_VALUE_STRING, ptConf.GetRetransCount()); 

    while(entry != NULL)
    {
        fprintf(tempfp, "%*c<%4s \n"
                         "%*c%4s = \"%s\" \n"
                         "%*c%4s = \"%s\" \n"
                         "%*c%4s = \"%s\" \n"
                         "%*c%4s = \"%s\" >\n",tab*2, ' ', DIA_PEER_STRING,
                         tab*2, ' ', DIA_SERV_HOST_NAME_STRING,
                         DIA_PE_HOST(entry),
                         tab*2, ' ', DIA_REALM_NAME_STRING,
                         DIA_PE_REALM(entry),
                         tab*2, ' ', DIA_TLS_ENABLED_STRING,
                         ((DIA_PE_TLS_EN(entry) == ITS_TRUE)? "yes":"no"),
                         tab*2, ' ', DIA_DSCP_ENABLED_STRING,
                         ((DIA_PE_DSCP_EN(entry) == ITS_TRUE)? "yes":"no"));

        fprintf(tempfp,"%*c<%s \n"
                         "%*c%4s = \"%s\" \n"
                         "%*c%4s = \"%s\" \n"
                         "%*c%4s = \"%d\" > \n"
                         "%*c</%s> \n", tab*2, ' ', DIA_TRANS_STRING,
                         tab*2, ' ', DIA_TRANS_TYPE_STRING, 
                         ((DIA_PE_CONN_TINFO(entry).type == ITS_DIA_T_TCP) ? 
                           "TCP":"SCTP"),
                         tab*2, ' ', DIA_SERV_IP_STRING, 
                         DIA_PE_CONN_TINFO(entry).serverIpAddr,
                         tab*2, ' ', DIA_PORT_INFO_STRING,
                         DIA_PE_CONN_TINFO(entry).portNo,
                         tab*2, ' ', DIA_TRANS_STRING);

       fprintf(tempfp,"%*c<%s \n"
                         "%*c%4s = \"%d\"/> \n",
                         tab*2, ' ', DIA_DSCP_STRING,
                         tab*2, ' ', DIA_VALUE_STRING,
                         DIA_PE_DSCP_VAL(entry));
        
        if (entry->altHost)
        {
            if (((DIA_PEER_CHK_IS_FAILOVER_ENABLED(entry)) == true))
            {
                fprintf(tempfp,"\n%*c<%s %4s         = \"%s\"\n"
                    "%*c  %4s = \"%s\"> \n\n", tab*2, ' ',
                    DIA_FAILOVER_STRING, 
                    DIA_ENABLE_STRING, 
                    (((DIA_PEER_CHK_IS_FAILOVER_ENABLED(entry)) == true)? 
                                                                "yes":"no"),
                    tab*3, ' ', 
                    DIA_ENABLE_FAILBACK_STRING, 
                    (((DIA_PEER_CHK_IS_FAILBACK_ENABLED(entry)) == true)? 
                                                                "yes":"no"));

                fprintf(tempfp,"%*c<%s %4s = \"%s\"\n"
                    "%*c       %4s      = \"%s\"\n"
                    "%*c       %4s         = \"%s\" > \n",
                    tab*3, ' ',
                    DIA_ALT_PEER_STRING,
                    DIA_SERV_HOST_NAME_STRING,
                    entry->altHost,
                    tab*4, ' ', 
                    DIA_REALM_NAME_STRING, 
                    entry->altRealmName,
                    tab*4, ' ', 
                    DIA_ISMATE_STRING,
                    (((DIA_PEER_CHK_IF_REDUNDANT_MATE(entry)) == true)? 
                                                               "yes":"no"));

                fprintf(tempfp,"%*c</%s> \n\n", tab*3, ' ', 
                                                DIA_ALT_PEER_STRING);   

                fprintf(tempfp,"%*c</%s> \n\n", tab*2, ' ', 
                                                DIA_FAILOVER_STRING);

            }
            else if (((DIA_PEER_CHK_IF_REDUNDANT_MATE(entry)) == true))
            {
                fprintf(tempfp,"\n%*c<%s %4s         = \"%s\">\n\n", 
                            tab*2, ' ',
                            DIA_FAILOVER_STRING, 
                            DIA_ENABLE_STRING, 
                            (((DIA_PEER_CHK_IS_FAILOVER_ENABLED(entry)) == 
                                                            true)? "yes":"no"));      
                fprintf(tempfp,"%*c<%s %4s = \"%s\"\n"
                       "%*c       %4s      = \"%s\"\n"
                       "%*c       %4s         = \"%s\" > \n",
                       tab*3, ' ',
                       DIA_ALT_PEER_STRING,
                       DIA_SERV_HOST_NAME_STRING,
                       entry->altHost,
                       tab*4, ' ', 
                       DIA_REALM_NAME_STRING, 
                       entry->altRealmName,
                       tab*4, ' ', 
                       DIA_ISMATE_STRING,
                       (((DIA_PEER_CHK_IF_REDUNDANT_MATE(entry)) == true)? 
                                                              "yes":"no"));
                fprintf(tempfp,"%*c</%s> \n\n", tab*3, ' ', 
                                DIA_ALT_PEER_STRING);   

                fprintf(tempfp,"%*c</%s> \n\n", tab*2, ' ', 
                                DIA_FAILOVER_STRING);
            }

        }
        else 
        {
            /* No Alternate Peers */
        }


        fprintf(tempfp, "%*c</%s> \n\n", tab*2, ' ', DIA_PEER_STRING);
        entry = PeerTable::GetPeerTable()->FindNextEntry(entry);
    }

    fprintf(tempfp,"%*c</%s> \n", tab*1, ' ', DIA_PEER_CONFIG_STRING);
}
static void 
HandleRealmConfiguration()
{
    ITS_INT count, i, inc = 0;
    ITS_INT test;

    fprintf(tempfp, "%*c<%s>\n", tab*1, ' ', DIA_REALM_CONFIG_STRING);

    REALM_ENTRY *rlmentry = NULL;

    count = RealmTable::GetRealmTable()->FindRealmCount();

    if (count > 0)
    {
        for (inc = 1; inc <= count; inc++)
        {
            rlmentry = NULL;

            rlmentry = RealmTable::GetRealmTable()->FindNextEntry(inc);

            if (rlmentry != NULL)
            {
                fprintf(tempfp, "%*c<%s \n"
                                "%*c%s = \"%s\" \n"
                                "%*c%s =  " ,
                                tab*2, ' ', DIA_ROUTE_STRING,
                                tab*2, ' ', DIA_REALM_NAME_STRING,
                                rlmentry->realmName,
                                tab*2, ' ', DIA_LOCAL_ACTION_STRING);

                if (rlmentry->localAction == ITS_DIA_LOCAL)
                {
                    fprintf(tempfp, "\"%s\">\n", DIA_LA_LOCAL_STRING);
                }
                else if (rlmentry->localAction == ITS_DIA_RELAY)
                {
                    fprintf(tempfp, "\"%s\"\n", DIA_LA_RELAY_STRING);

                    fprintf(tempfp, "%*c%s = \"%s\" >\n", tab*2, ' ',
                                DIA_PROXY_INFO_AVP_EN_STRING,
                                ((rlmentry->proxyInfoAvpEnabled == 0) ? 
                                                             "no" : "yes"));
                }
                else if (rlmentry->localAction == ITS_DIA_PROXY)
                {
                    fprintf(tempfp, "\"%s\">\n", DIA_LA_PROXY_STRING);
                }
                else if (rlmentry->localAction == ITS_DIA_REDIRECT)
                {
                    fprintf(tempfp, "\"%s\">\n", DIA_LA_REDIRECT_STRING);
                }
            }
            else
            {
                continue;
            }

            if (rlmentry->destCnt <= 0)
            {
                fprintf(tempfp, "%*c</%s>\n\n", tab*2, ' ', DIA_ROUTE_STRING);
                //fprintf(tempfp, "%*c</%s>\n", tab*2, ' ', DIA_REALM_CONFIG_STRING);
                continue;
            }
            else
            {

                for (i=0; i<rlmentry->destCnt; i++)
                {
                    fprintf(tempfp, "%*c<%4s \n"
                             "%*c%8s = \"%s\" \n"
                             "%*c%8s = \"%d\" \n"
                             "%*c%8s = \"%d\" \n"
                             "%*c%8s = \"%d\" > \n"
                             "%*c</%4s> \n",
                             tab*2, ' ', DIA_DESTINATION_STRING,
                             tab*2, ' ', DIA_PEER_NAME_STRING,
                             DIA_PE_HOST(rlmentry->destSpecs[i].peer),
                             tab*2, ' ', DIA_APPLICATION_ID_STRING,
                             rlmentry->destSpecs[i].appIdentifier.appId,
                             tab*2, ' ', DIA_DEST_VENDOR_ID_STRING,
                             rlmentry->destSpecs[i].appIdentifier.vendorId,
                             tab*2, ' ', DIA_PRIORITY_STRING,
                             rlmentry->destSpecs[i].priority,
                             tab*2, ' ', DIA_DESTINATION_STRING);
                }

                fprintf(tempfp, "%*c</%s>\n\n", tab*2, ' ', DIA_ROUTE_STRING);
            }//else

        }//For for iteration
    }

    rlmentry = RealmTable::GetRealmTable()->FindDefaultEntry(rlmentry);

    if (rlmentry)
    {
        fprintf(tempfp, "%*c<%s \n"
                     "%*c%4s = \"%s\" \n"
                     "%*c%4s =  \"%s\">\n" ,
                     tab*2, ' ', DIA_ROUTE_STRING,
                     tab*2, ' ',DIA_REALM_NAME_STRING,
                     rlmentry->realmName,
                     tab*2, ' ', DIA_DEFAULT_STRING,
                     "yes" );

        fprintf(tempfp, "%*c<%s \n"
                     "%*c%s = \"%s\" > \n"
                     "%*c</%s> \n", tab*2, ' ', DIA_DESTINATION_STRING,
                     tab*2, ' ', DIA_PEER_NAME_STRING,
                     DIA_PE_HOST(rlmentry->destSpecs[0].peer),
                     tab*2, ' ', DIA_DESTINATION_STRING);     
        fprintf(tempfp, "%*c</%s>\n\n", tab*2, ' ', DIA_ROUTE_STRING);
    }

    fprintf(tempfp, "%*c</%s>\n", tab*1, ' ', DIA_REALM_CONFIG_STRING);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *  To add Peer entry of type PEER_INFO dynamically
 *
 *  Input Parameters:
 *      PEER_INFO*
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Integer
 *
 *  Notes:
 *
 *  See Also:
 *
 * Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *  ChandraBS     28-01-2009                        Initial Commit for 
 *                                                   XML persistency
 ****************************************************************************/
int
DiaMgmt::DIA_Commit(char * filename)
{
    ITS_CHAR filename1[ITS_PATH_MAX];
    time_t t = time(0);
    struct tm* time_now = localtime(&t);

    //Correcting risky function
    memset(filename1, 0, ITS_PATH_MAX);
    snprintf(filename1, ITS_PATH_MAX-1,
            "%s_%02d_%02d_%04d_%02d_%02d_%02d.tmp",
            filename,
            time_now->tm_mday, time_now->tm_mon+1, time_now->tm_year+1900,
            time_now->tm_hour, time_now->tm_min, time_now->tm_sec);

    tempfp = fopen(filename1,"w+");
    if (tempfp == NULL)
    {
        DT_ERR(("Failed to open file for writing"));
        return !ITS_SUCCESS;
    }

    /* Write Version string in the starting */
    fprintf(tempfp, "<?xml version=\"1.0\"?>\n\n");

    /* Persist info like version, dictionary file */
    config = &itsDiaConfig;
    ITSDiaConfig::ProductInfo& pInfo = config->GetProductInfo();
    tab = 8;

    fprintf(tempfp, "<%s",DIA_STRING);
   
    //if (pInfo.GetVersionNo() != NULL)
    //Warning Fix - NULL used in arithmetic
    if (pInfo.GetVersionNo() != 0)
    {
        fprintf(tempfp, "    %s                 = \"%d\" \n", 
                         DIA_VER_STRING, pInfo.GetVersionNo());
    }

    if (pInfo.GetDictionary() != NULL)
    {
       fprintf(tempfp,"%*c %s          = \"%s\" \n", tab*2, ' ', 
                       DIA_DICT_FILE_STRING,pInfo.GetDictionary());
    }

    if (pInfo.GetProdName() != NULL)
    {
       fprintf(tempfp,"%*c %s             = \"%s\" \n", tab*2, ' ', 
                       DIA_PRODUCT_NAME_STRING,pInfo.GetProdName());
    }

    fprintf(tempfp,"%*c %s    = \"%x\" \n", tab*2, ' ', 
                    DIA_DEFAULT_ROUTING_STRING, 
                    itsDiaConfig.IsDefaultRealmRoutingEnabled());

    fprintf(tempfp,"%*c %s  = \"%x\" \n", tab*2, ' ', 
                    DIA_PEER_MSG_TO_APP_STRING, 
                    itsDiaConfig.IsPeerMsgToAppEnabled());
    
    fprintf(tempfp,"%*c %s     = \"%x\" \n", tab*2, ' ', 
                    DIA_ADD_ORIG_STATE_ID_STRING, 
                    itsDiaConfig.GetOriginStateIdOpt());

    fprintf(tempfp,"%*c %s       = \"%x\" \n", tab*2, ' ', 
                    DIA_ENABLE_PEER_IPCHECK_STRING, 
                    itsDiaConfig.IsPeerIpCheckEnabled());

    fprintf(tempfp,"%*c %s        = \"%x\" \n", tab*2, ' ', 
                    DIA_ENABLE_STACK_STATS_STRING, 
                    itsDiaConfig.IsStatisticsEnabled());

    fprintf(tempfp, "%*c %s           = \"%x\" \n", tab*2, ' ', 
                     DIA_ENABLE_HEXDUMP_STRING,
                     itsDiaConfig.IsHexDumpEnabled());
     
    fprintf(tempfp, "%*c %s               = \"%x\" \n", tab*2, ' ', 
                     DIA_ENABLE_HMI_STRING,
                     itsDiaConfig.IsHMIEnabled());

    fprintf(tempfp, "%*c %s        = \"%x\" \n", tab*2, ' ', 
                      DIA_INITIATE_CONNS_STRING,
                     itsDiaConfig.GetInitiateConnsOpt());

    fprintf(tempfp, "%*c %s              = \"%x\" \n", tab*2, ' ', 
                      DIA_ENABLE_IPV6,
                     itsDiaConfig.isIpv6Enabled());

    fprintf(tempfp, "%*c %s     = \"%x\" \n", tab*2, ' ', 
                      DIA_ENABLE_PEER_DISCOVERY,
                     itsDiaConfig.isPeerDiscoveryEnabled());

    fprintf(tempfp, "%*c %s   = \"%d\" > \n\n", tab*2, ' ', 
                      DIA_DISCOVERY_INTERVAL,
                     itsDiaConfig.getDiscoveryInterval());

    fprintf(tempfp, "%*c %s           = \"%x\" \n", tab*2, ' ', 
                     DIA_INTER_WORKING_MODE_STRING,
                     itsDiaConfig.IsInterWorkingMode());
     
    /* Handle Local Configuration */
    fprintf(tempfp, "%*c<%s>\n", tab*1, ' ', DIA_LOCAL_STRING);
    HandleLocalConfiguration();
    fprintf(tempfp, "%*c</%s>\n\n", tab*1, ' ', DIA_LOCAL_STRING);

    /* Handle Peer Configuration */
    HandlePeerConfiguration();
    
    /* Handle Realm Configuration */
    HandleRealmConfiguration();

    fprintf(tempfp, "</%s>", DIA_STRING);

    fclose(tempfp);

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *  To set Peer, AuthSession and AcctSession Timers.    
 *  
 *  Input Parameters:
 *      timer values
 *  
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      Integer : (ITS_SUCCESS / !ITS_SUCCESS)
 *  
 *  Notes:
 *  
 *  See Also:
 *
 * Revision History:
 * ---------------------------------------------------------------------------
 *  Name          Date        Reference               Description
 * ---------------------------------------------------------------------------
 * Suresh J      3/MAR/09    4.0 release       Dynamic configuration                     
 ****************************************************************************/
int  
DiaMgmt::SetPeerTimers(ITS_SERIAL wdval, ITS_SERIAL tcval, ITS_SERIAL expiryval)
{
    ITSDiaConfig* config = &itsDiaConfig;
    ITSDiaConfig::PeerTimersConfig& ptConf = config->GetPeerTimers();
    if( wdval !=0)
    {
        ptConf.SetWatchdog(wdval);
    }
    if( expiryval !=0)
    {
        ptConf.SetExpiry(expiryval);
    }
    if( tcval !=0) 
    {
        ptConf.SetRetry(tcval);
    }
     
    return ITS_SUCCESS; 
}

int
DiaMgmt::GetPeerTimers(ITS_SERIAL &wdval, ITS_SERIAL &tcval, ITS_SERIAL &expiryval)
{   
    ITSDiaConfig* config = &itsDiaConfig;
    ITSDiaConfig::PeerTimersConfig& ptConf = config->GetPeerTimers();
    wdval = ptConf.GetWatchdog();
    tcval = ptConf.GetRetry();
    expiryval = ptConf.GetExpiry();
    return ITS_SUCCESS;
}
// To set Auth Session Timer values 
int
DiaMgmt::SetAuthSessionTimers(ITS_SERIAL lifetime, ITS_SERIAL gracetime, 
                               ITS_SERIAL timeout)
{
    ITSDiaConfig* config = &itsDiaConfig;
    ITSDiaConfig::AuthSessionConfig& authsCfg = config->GetAuthSessionConfig();
    authsCfg.SetLifeTime(lifetime);
    authsCfg.SetGracePeriod(gracetime);  
    authsCfg.SetTimeout(timeout);
    return ITS_SUCCESS;
}

//To Set Accounting session timer values. 
int
DiaMgmt::SetAcctSessionTimers(ITS_SERIAL interim, ITS_SERIAL timeout)
{
    ITSDiaConfig* config = &itsDiaConfig;
    ITSDiaConfig::AcctSessionConfig& accCfg = config->GetAcctSessionConfig();
    accCfg.SetInterimIntvl(interim);
    accCfg.SetTimeout(timeout);
    return ITS_SUCCESS;
}

//To set local host information 
int
DiaMgmt::SetLocalHostInfo(const char* serverHostName, const char* realmName)
{
    int ret = ITS_SUCCESS;
    DIA_CER *cer;
    DIA_CEA *cea;
    DIA_CER *rfc6733CER;
    DIA_CEA *rfc6733CEA;
    cer = itsDiaConfig.GetLocalCER();    
    cea = itsDiaConfig.GetLocalCEA();    
    rfc6733CER = itsDiaConfig.GetRFC6733LocalCER();    
    rfc6733CEA = itsDiaConfig.GetRFC6733LocalCEA();    
    OriginHost ohost(serverHostName);
    OriginRealm orealm(realmName);
        
   ((DIA_CER *)cer)->setOriginHost(ohost);
   ((DIA_CEA *)cea)->setOriginHost(ohost);
   ((DIA_CER *)cer)->setOriginRealm(orealm);
   ((DIA_CEA *)cea)->setOriginRealm(orealm);

   ((DIA_CER *)rfc6733CER)->setOriginHost(ohost);
   ((DIA_CEA *)rfc6733CEA)->setOriginHost(ohost);
   ((DIA_CER *)rfc6733CER)->setOriginRealm(orealm);
   ((DIA_CEA *)rfc6733CEA)->setOriginRealm(orealm);

   itsDiaConfig.setLocalHostInfo(serverHostName, realmName);
   return ret;
}

//To set local transport information 
int
DiaMgmt::SetLocalTransportInfo(const char* serverIpAddr, int type,
                               ITS_USHORT port,const char** multiHomeIpps,int noIPs,
                               const char* publicServerIpAddr,ITS_USHORT securePort)
{   
    int ret = !ITS_SUCCESS;
    itsDiaConfig.setLocalTptInfo(serverIpAddr, (DIA_TRANS_TYPE)type, port,multiHomeIpps,
                                 noIPs,publicServerIpAddr,securePort);

    DIA_CER *cer;
    DIA_CEA *cea;
    DIA_CER *rfc6733CER;
    DIA_CEA *rfc6733CEA;
    cer = itsDiaConfig.GetLocalCER();
    cea = itsDiaConfig.GetLocalCEA();
    rfc6733CER = itsDiaConfig.GetRFC6733LocalCER();    
    rfc6733CEA = itsDiaConfig.GetRFC6733LocalCEA();    
    try
    {
        Address::Family familyType=Address::IPV4;
        if (DiaUtils::IsIPv6Address(serverIpAddr))
        { familyType=Address::IPV6;}

        Address oaddr( familyType ,serverIpAddr);
        HostIPAddress hostIp(oaddr);
        if(publicServerIpAddr == NULL)
        {
            ((DIA_CER *)cer)->addHostIPAddress(hostIp);
            ((DIA_CEA *)cea)->addHostIPAddress(hostIp);
            ((DIA_CER *)rfc6733CER)->addHostIPAddress(hostIp);
            ((DIA_CEA *)rfc6733CEA)->addHostIPAddress(hostIp);
        }
        else
        {
            Address::Family publicServerAddrFamilyType=Address::IPV4;
            if (DiaUtils::IsIPv6Address(publicServerIpAddr))
            {
                publicServerAddrFamilyType = Address::IPV6;
            }
            Address publicAddr(publicServerAddrFamilyType,publicServerIpAddr);
            HostIPAddress publicIP(publicAddr);
            ((DIA_CER *)cer)->addHostIPAddress(publicIP);
            ((DIA_CEA *)cea)->addHostIPAddress(publicIP);
            ((DIA_CER *)rfc6733CER)->addHostIPAddress(publicIP);
            ((DIA_CEA *)rfc6733CEA)->addHostIPAddress(publicIP);
        }

         if(itsDiaConfig.GetLocalIpAddr() == NULL)
         {
             itsDiaConfig.SetLocalIpAddr(serverIpAddr);
         }
         ret = ITS_SUCCESS;
     }
     catch(const char *e)
     {
       DT_ERR(("Failed to create Address object  :: = %s", e));
     }
     catch(...)
     {
       DT_ERR(("Unknown Exception"));
     }
     return ret;
}

DiaMgmt*
DiaMgmt::GetDiaMgmt()
{
    if (itMgmt == NULL)
    {
        itMgmt = new DiaMgmt;
    }

    return itMgmt;
}

int
DiaMgmt::DisconnectAllPeers(ITS_UINT disCause)
{
    PEER_ENTRY *entry = PeerTable::GetPeerTable()->FindFirstEntry();
    while (entry != NULL) 
    {
        DisconnectPeer(DIA_PE_HOST(entry), DIA_PE_REALM(entry),disCause);
        entry = PeerTable::GetPeerTable()->FindNextEntry(entry); 
    }
    return ITS_SUCCESS;
}    

int
DiaMgmt::InsertIntoDiscoveryList(const char* realmName, const char* hostName)
{   
    int ret = !ITS_SUCCESS;

    if (realmName == NULL)
    {
        return NULL;
    }

    DIA_PEER_DISC_INFO* pInfo = (DIA_PEER_DISC_INFO*) malloc (sizeof(DIA_PEER_DISC_INFO));
    if (pInfo)
    {
        memset(pInfo, 0, sizeof(DIA_PEER_DISC_INFO));
        pInfo->realmName = strdup(realmName);
        if (hostName)
        {
            pInfo->hostName = strdup(hostName);
        }

        ret = DiscoveryList::GetDiscoveryList()->InsertEntry(pInfo);

        free(pInfo);
        return ret;
    }
    return !ITS_SUCCESS;
} 

int
DiaMgmt::RemoveFromDiscoveryList(const char* realmName, const char* hostName)
{
    return DiscoveryList::GetDiscoveryList()->RemoveEntry(realmName, hostName);
}

int
DiaMgmt::EnablePeerDiscovery()
{
    itsDiaConfig.setPeerDiscoveryEnabled();
    return ITS_SUCCESS;
}

int
DiaMgmt::DisablePeerDiscovery()
{
    itsDiaConfig.unsetPeerDiscoveryEnabled();
    return ITS_SUCCESS;
}

bool
DiaMgmt::IsPeerDiscoveryEnable()
{
    return itsDiaConfig.isPeerDiscoveryEnabled();
}

int
DiaMgmt::SetPeerDiscoveryInterval(int val)
{
    itsDiaConfig.setDiscoveryInterval(val);
    return ITS_SUCCESS;
}

int
DiaMgmt::GetPeerDiscoveryInterval()
{
    return itsDiaConfig.getDiscoveryInterval();
}

int
DiaMgmt::SetOvloadThresholds(ITS_INT maxT, ITS_INT minT)
{
    if( maxT == 0 || minT == 0) 
    {
         return !ITS_SUCCESS; 
    }
    maxThreshold = maxT;
    minThreshold = minT;
   
    return ITS_SUCCESS; 
}

int
DiaMgmt::GetOvloadThresholds(ITS_INT &maxT, ITS_INT &minT)
{
    if( maxThreshold == 0 || minThreshold == 0)
    {
         return !ITS_SUCCESS;
    }
    maxT = maxThreshold;
    minT = minThreshold;

    return ITS_SUCCESS;
}

int
DiaMgmt::EnableHMI()
{
    itsDiaConfig.SetHMIEnabled();
    return ITS_SUCCESS;
}
int
DiaMgmt::DisableHMI()
{
    itsDiaConfig.SetHMIDisabled();
    return ITS_SUCCESS;
}
int
DiaMgmt::IsHMIEnabled()
{
    if(itsDiaConfig.IsHMIEnabled())
    {
        return ITS_SUCCESS ;
    }
    return !ITS_SUCCESS;
}

int
DiaMgmt::PrintPeerDiscoveryTable(std::ostream& oss)
{
    DiscoveryList::GetDiscoveryList()->Print(oss);
    return ITS_SUCCESS;
}

int
DiaMgmt::SetHBInterval(ITS_UINT hbInterval)
{
    DiaConfig *cfg = DiaConfig::GetDiaConfig();
    cfg->SetHeartBeatInterval(hbInterval);
    return ITS_SUCCESS;
}
 
int
DiaMgmt::SetHBRetry(ITS_UINT retry)
{
    DiaConfig *cfg = DiaConfig::GetDiaConfig();
    cfg->SetHeartBeatRetry(retry);
    return ITS_SUCCESS;
}
 
int
DiaMgmt::GetHBInterval()
{
    DiaConfig *cfg = DiaConfig::GetDiaConfig();
    return cfg->GetHeartBeatInterval();
}
 
int
DiaMgmt::GetHBRetry()
{
    DiaConfig *cfg = DiaConfig::GetDiaConfig();
    return cfg->GetHeartBeatRetry();
}

int
DiaMgmt::GetHMICheckInterval()
{
    return HMI_GetCheckInterval();
}

int
DiaMgmt::SetHMICheckInterval(int val)
{
    /* Timeout in milli sec */
    int tmOut = HMI_GetTimeOutInterval() / 1000;
    if (val > tmOut)
    {
        HMI_SetCheckInterval(val);
        return ITS_SUCCESS;
    }
    else
    {
        DT_ERR(("HMICheckInterval should be greater than HMITimeout"));
        return !ITS_SUCCESS;
    }
}

int
DiaMgmt::GetHMITimeout()
{
    return HMI_GetTimeOutInterval();
}

int
DiaMgmt::SetHMITimeout(int val)
{
    /* Timeout in milli sec */
    int tmOut = val / 1000;
    if (tmOut < HMI_GetCheckInterval())
    {
        HMI_SetTimeOutInterval(val);
        return ITS_SUCCESS;
    }
    else
    {
        DT_ERR(("HMITimeout should be less than HMICheckInterval"));
        return !ITS_SUCCESS;
    }
}

int
DiaMgmt::GetHMIRetry()
{
    return HMI_GetRetry();
}

int
DiaMgmt::SetHMIRetry(int val)
{
    HMI_SetRetry(val);
    return ITS_SUCCESS;
}

int
DiaMgmt::GetHMIHBInterval()
{
    return HMI_GetHBInterval();
}

int
DiaMgmt::SetHMIHBInterval(int val)
{
    /* Timeout in milli sec */
    HMI_SetHBInterval(val);
    DT_DBG(("Set HMI Heartbeat Interval")); 
    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      hostName, realmName
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Integer
 *
 *  Notes:
 *
 *  See Also:
 *
 * Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ---------------------------------------------------------------------------
 * 
 ****************************************************************************/
int
DiaMgmt::SetDscpValue(const char* hostName, const char* realmName, ITS_INT val)
{
    int ret = ITS_SUCCESS;
    PEER_ENTRY *peerEntry = NULL;

    DT_DBG(("DiaMgmt::SetDscpValue"));

    if (PeerTable::GetPeerTable()->FindEntry(hostName, realmName, peerEntry))
    {
         DIA_PE_DSCP_EN(peerEntry) = ITS_TRUE;
         DIA_PE_DSCP_VAL(peerEntry) = val;
         if (DIA_PE_DSCP_EN(peerEntry) == ITS_TRUE)
         {
             if(DIA_PE_HANDLE(peerEntry))
             {
                 if ((DIA_PE_STATE(peerEntry) == PEER_ST_CLOSED))
                 {
                     DT_WRN(("Failed to Initialize Connector:Peer is in closed state"));
                     return !ITS_SUCCESS;
                 }
                 else 
                 { 
                     DT_DBG(("DiaMgmt::SetDscpValue to the already exists fd"));
                     ((DiaSocketTransport*)DIA_PE_HANDLE(peerEntry))->
                                              GetSocket()->SetDscpMarking(DIA_PE_DSCP_VAL(peerEntry));
                 }
             }
         }

    }
    else
    {
        DT_WRN(("Invalid Peer Name %s  Realm %s Discarding", hostName, realmName));
        ret = ITS_DIA_UNKNOWN_PEER;
    }
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      hostName, realmName
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Integer
 *
 *  Notes:
 *
 *  See Also:
 *
 * Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ---------------------------------------------------------------------------
 * 
 ****************************************************************************/
int
DiaMgmt::GetDscpValue(const char* hostName, const char* realmName)
{
    int val = 0;
    PEER_ENTRY *peerEntry = NULL;

    DT_DBG(("DiaMgmt::GetDscpValue"));

    if (PeerTable::GetPeerTable()->FindEntry(hostName, realmName, peerEntry))
    {
        if (DIA_PE_DSCP_EN(peerEntry) == ITS_TRUE)
        {
            DT_DBG(("DiaMgmt::GetDscpValue to the already exists fd"));
            val = DIA_PE_DSCP_VAL(peerEntry);
            return val;
        }
        else
        {
            DT_WRN(("DSCP feature not enabled "));
        }
    }
    else
    {
        DT_WRN(("Invalid Peer Name %s  Realm %s Discarding", hostName, realmName));
    }
    return val;
}

ITS_UINT
DiaMgmt::EnableDscp(const char* hostName, const char* realmName)
{
    int ret = ITS_SUCCESS;
    PEER_ENTRY *peerEntry = NULL;

    DT_DBG(("DiaMgmt::EnableDscp"));

    if (PeerTable::GetPeerTable()->FindEntry(hostName, realmName, peerEntry))
    {
        DIA_PE_DSCP_EN(peerEntry) = ITS_TRUE;
    }
    else
    {
        DT_WRN(("Invalid Peer Name %s  Realm %s Discarding", hostName, realmName));
    }
    return ret;
}

ITS_UINT
DiaMgmt::DisableDscp(const char* hostName, const char* realmName)
{
    int ret = ITS_SUCCESS;
    PEER_ENTRY *peerEntry = NULL;

    DT_DBG(("DiaMgmt::DisableDscp"));

    if (PeerTable::GetPeerTable()->FindEntry(hostName, realmName, peerEntry))
    {
        DIA_PE_DSCP_EN(peerEntry) = ITS_FALSE;
    }
    else
    {
        DT_WRN(("Invalid Peer Name %s  Realm %s Discarding", hostName, realmName));
    }
    return ret;
}

int DiaMgmt::GetAuthSessionTimers(ITS_SERIAL& lifeTime, ITS_SERIAL& graceTime, ITS_SERIAL& timeOut)
{
    int ret = ITS_SUCCESS;
    lifeTime = itsDiaConfig.GetAuthSessionConfig().GetLifeTime();
    graceTime = itsDiaConfig.GetAuthSessionConfig().GetGracePeriod();
    timeOut = itsDiaConfig.GetAuthSessionConfig().GetTimeout();
    return ret;
}

int DiaMgmt::GetAcctSessionTimers(ITS_SERIAL& interval, ITS_SERIAL& timeOut)
{
    int ret = ITS_SUCCESS;
    interval = itsDiaConfig.GetAcctSessionConfig().GetInterimIntvl();
    timeOut = itsDiaConfig.GetAcctSessionConfig().GetTimeout();
    return ret;
}

int DiaMgmt::GetLocalTransportInfo(MGMT_TR_TYPE transportType, int lport)
{
    int ret = ITS_SUCCESS;
    //Correcting Reliance on Integer endianness
    ITS_USHORT usPort = 0;
    itsDiaConfig.getLocalTptInfo((int *) &transportType, (ITS_USHORT *) &usPort);
    lport = usPort;
    return ret;
}

int DiaMgmt::GetPeer(PEER_INFO *PeerData)
{
    int ret = ITS_SUCCESS;
    PEER_ENTRY *pEntry = NULL;
    
    if (PeerTable::GetPeerTable()->FindEntry(PeerData->peerName, PeerData->realmName, pEntry))
    {
        PeerData->ipAddr = DIA_PE_CONN_TINFO(pEntry).serverIpAddr;
        PeerData->port = DIA_PE_CONN_TINFO(pEntry).portNo;
        PeerData->type = (MGMT_TR_TYPE ) DIA_PE_CONN_TINFO(pEntry).type;
        PeerData->tlsEnabled = pEntry->tlsEnabled;
    } else {
        ret = !ITS_SUCCESS;
    }

    return ret;
}

int DiaMgmt::ModifyPeer(PEER_INFO *PeerData,ITS_BOOLEAN isTlsFlagModified)
{
    int ret = ITS_SUCCESS;
    PEER_ENTRY *pEntry = NULL;

    if (PeerTable::GetPeerTable()->FindEntry(PeerData->peerName, PeerData->realmName, pEntry))
    {
        if (DIA_PE_STATE(pEntry) == PEER_ST_CLOSED)
        {
            if(PeerData->type == DIA_TRANS_SCTP )
            {
                for(int i = 0;i < DIA_PE_CONN_TRANS_COUNT(pEntry);i++)
                {
                    if(DIA_PE_CONN_TINFO_INDEX(pEntry,i).securePort > 0)
                    {
                        DT_DBG(("Configuring secure port for sctp transport type is not supported"));
                        return  MOD_PEER_SECURE_PORT_NOT_SUPPORTED_FOR_SCTP;
                    }
                }
            }
            //Chnage the transport type if it was configured earlier
            //If it was not then we would have configured both transport
            if(PeerData->type != DIA_TRANS_INVALID) 
            {
                if(DIA_PE_CONN_TRANS_COUNT(pEntry) == (MAX_TRANS_PER_LIST-1))
                {
                    DT_DBG(("Configured both TCP and SCTP during startup.Now Modify not allowed"));
                    return MOD_PEER_CONFIGURED_ALL_THE_TRANSPORTS_DURING_STARTUP;

                }
                DT_DBG(("Changing the transport type to %s",DIA_TRANS_TYPE_TO_TEXT(PeerData->type)));

                for(int i = 0;i < DIA_PE_CONN_TRANS_COUNT(pEntry);i++)
                {
                    DIA_PE_CONN_TINFO_INDEX(pEntry,i).type = (DIA_TRANS_TYPE)(PeerData->type);
                }
            }
            if(PeerData->ipAddr!=NULL)
            {
                DT_DBG(("Changing the ip address from %s to %s",
                            DIA_PE_CONN_TINFO_INDEX(pEntry,0).serverIpAddr,PeerData->ipAddr));

                for(int i = 0;i < DIA_PE_CONN_TRANS_COUNT(pEntry);i++)
                {
                    free((char *)(DIA_PE_CONN_TINFO_INDEX(pEntry,i).serverIpAddr));
                    DIA_PE_CONN_TINFO_INDEX(pEntry,i).serverIpAddr = strdup(PeerData->ipAddr);
                    if (DIA_PE_CONN_TINFO_INDEX(pEntry,i).type == ITS_DIA_T_SCTP)
                    {
                        DIA_PE_CONN_TINFO_INDEX(pEntry,i).multiHomeipaddrs[0] = 
                            DIA_PE_CONN_TINFO_INDEX(pEntry,i).serverIpAddr;
                    }
                }
            }
            if(PeerData->port)
            {
                for(int i = 0;i < DIA_PE_CONN_TRANS_COUNT(pEntry);i++)
                {
                    if(DIA_PE_CONN_TINFO_INDEX(pEntry,i).portNo != 0)
                    {
                        DT_DBG(("Changing the port from %d to %d",
                                 DIA_PE_CONN_TINFO_INDEX(pEntry,i).portNo,PeerData->port));
                        DIA_PE_CONN_TINFO_INDEX(pEntry,i).portNo = PeerData->port;
                    }
                }
            }
            if(PeerData->securePort)
            {
                for(int i = 0;i < DIA_PE_CONN_TRANS_COUNT(pEntry);i++)
                {
                    if(DIA_PE_CONN_TINFO_INDEX(pEntry,i).securePort != 0)
                    {
                        DT_DBG(("Changing the secure port from %d to %d",
                                 DIA_PE_CONN_TINFO_INDEX(pEntry,i).securePort,PeerData->securePort));
                        DIA_PE_CONN_TINFO_INDEX(pEntry,i).securePort = PeerData->securePort;
                    }
                }
            }
            if(isTlsFlagModified)
            {
                pEntry->tlsEnabled = PeerData->tlsEnabled;
                DT_DBG(("For Peer %s TLS Enabled flag value is %d",
                         pEntry->hostIdentity,pEntry->tlsEnabled));
            }

        } else {
            ret = !ITS_SUCCESS;
        }
    } else {
        ret = !ITS_SUCCESS;
    }
    return ret;
}

int DiaMgmt::GetAlternatePeer(ALT_PEER_INFO* aInfo)
{
    int ret = (!ITS_SUCCESS);
    PEER_ENTRY *aEntry = NULL;

    if (PeerTable::GetPeerTable()->FindEntry(aInfo->altHost, aInfo->altRealmName, aEntry))
    {
        aInfo->isFailoverEnable = DIA_PEER_CHK_IS_FAILOVER_ENABLED(aEntry);
        aInfo->isFailbackEnable = DIA_PEER_CHK_IS_FAILBACK_ENABLED(aEntry);
        aInfo->isRedundantMate = DIA_PEER_CHK_IF_REDUNDANT_MATE(aEntry);
	ret = ITS_SUCCESS;
    }
    return ret;
}

int DiaMgmt::SetRealmLocalAction(const char *realm, const char *laction)
{
    int ret = ITS_SUCCESS;
    REALM_ENTRY *rEntry = NULL;

    if (RealmTable::GetRealmTable()->FindEntry(realm, rEntry))
    {
        if (rEntry->proxyInfoAvpEnabled && (strcasecmp(laction, "RELAY") != 0))
        {
            ret = !ITS_SUCCESS;
        } else {
            if(strcasecmp(laction, "LOCAL") == 0)
            {
                rEntry->localAction = ITS_DIA_LOCAL;
            }
            if(strcasecmp(laction, "RELAY") == 0)
            {
                rEntry->localAction = ITS_DIA_RELAY;
            }
            if(strcasecmp(laction, "PROXY") == 0)
            {
                rEntry->localAction = ITS_DIA_PROXY;
            }
            if(strcasecmp(laction, "REDIRECT") == 0)
            {
                rEntry->localAction = ITS_DIA_REDIRECT;
            }
        }
    } else {
        ret = !ITS_SUCCESS;
    }
    return ret;
}

int DiaMgmt::ModifyRedirectUsage(const char *realm,  unsigned int rdUsage)
{
    int ret = ITS_SUCCESS;
    REALM_ENTRY *rEntry = NULL;

    if (RealmTable::GetRealmTable()->FindEntry(realm, rEntry))
    {
        rEntry->redirectUsage = rdUsage;
    } else {
        ret = !ITS_SUCCESS;
    }
 
    return ret;
}

int DiaMgmt::ModifyRedirectCacheTime(const char *realm,  unsigned int rdmaxCacheTime)
{
    int ret = ITS_SUCCESS;
    REALM_ENTRY *rEntry = NULL;

    if (RealmTable::GetRealmTable()->FindEntry(realm, rEntry))
    {
        rEntry->redMaxCacheTime = rdmaxCacheTime;
    } else {
        ret = !ITS_SUCCESS;
    }
 
    return ret;
}


int DiaMgmt::SetDTFLoggingConfig(const unsigned int channel, const unsigned int level)
{
    config = &itsDiaConfig;
    if(config->IsDTFEnabled())
    {
        DT_DBG(("SetDTFLoggingConfig"));
        DiaStackClass::GetDtf().SetLogChannel(channel);
        DiaStackClass::GetDtf().SetLogLevel(level);    
        return ITS_SUCCESS;
    }
    else
    {
        DT_WRN(("DTF logger object not created unable to set DTF Logger"));
        return !ITS_SUCCESS;
    }
}

int DiaMgmt::SetDTFLogChannel(const unsigned int channel)
{
    config = &itsDiaConfig;
    if(config->IsDTFEnabled())
    {
        DT_DBG(("SetDTFLogChannel"));
        DiaStackClass::GetDtf().SetLogChannel(channel);
        return ITS_SUCCESS;
    }
    else
    {
        DT_WRN(("DTF logger object not created unable to set DTF Logger"));
        return !ITS_SUCCESS;
    }
}

int DiaMgmt::SetDTFLogLevel(const unsigned int level)
{
    config = &itsDiaConfig;
    if(config->IsDTFEnabled())
    {
        DT_DBG(("SetDTFLogLevel"));
        DiaStackClass::GetDtf().SetLogLevel(level);
        return ITS_SUCCESS;
    }
    else
    {
        DT_WRN(("DTF logger object not created unable to set DTF Logger"));
        return !ITS_SUCCESS;
    }
}

// User of the GetPeersState need to delete the memory allocated by this method.
//
//unsigned int DiaMgmt::GetPeersState(DIA_PEER_STATES *peersPtr)
DIA_PEER_STATES* DiaMgmt::GetPeersState(unsigned int& nPeers)
{
   unsigned int numPeers = 0;
   unsigned int peerIdx = 0;
   DIA_PEER_STATES *peersPtr = NULL;
   numPeers = PeerTable::GetPeerTable()->GetPeerTableSize();
   if (numPeers > 0)
   {
       peersPtr = new DIA_PEER_STATES[numPeers];
       if (peersPtr == NULL)
       {
          // Error
          numPeers = 0;
       } else {
             PEER_ENTRY *pentry = PeerTable::GetPeerTable()->FindFirstEntry();
             while ((pentry != NULL) && peerIdx < numPeers)
             {
                peersPtr[peerIdx].peerName  = (char *) DIA_PE_HOST(pentry);
                peersPtr[peerIdx].realmName = (char *) DIA_PE_REALM(pentry);
                peersPtr[peerIdx].pState    = (PEER_FSM_STATE) DIA_PE_STATE(pentry);
                pentry = PeerTable::GetPeerTable()->FindNextEntry(pentry);
                peerIdx += 1;
             }
       }
   }
   nPeers = numPeers;
   return peersPtr;
}

int DiaMgmt::SetPeerTimers(PEER_INFO *PeerData)
{
    int ret = (!ITS_SUCCESS);
    PEER_ENTRY *aEntry = NULL;
    if (PeerTable::GetPeerTable()->FindEntry(PeerData->peerName, PeerData->realmName, aEntry))
    {
        DIA_PE_DW_TIME_VAL(aEntry) = PeerData->watchdog;
        DIA_PE_RETRY_TIME_VAL(aEntry) = PeerData->retry;
        DIA_PE_EXPIRY_TIME_VAL(aEntry) = PeerData->expiry;
	/*Following are the deafult values 
  	 * for sockFlushTimerVal, sockFlushCnt
  	 * sockFlushRetryCnt
  	 */  
        DIA_PE_SOCK_FLUSH_TIMER_VAL(aEntry) = 2; 
        DIA_PE_SOCK_FLUSH_CNT(aEntry) = 0;
	DIA_PE_SOCK_FLUSH_RETRY_CNT(aEntry) = -1;
        ret = ITS_SUCCESS;
    }
    return ret;
}

int DiaMgmt::SetPeerIsDisconnectCauseSupported(PEER_INFO *PeerData)
{
    int ret = (!ITS_SUCCESS);
    PEER_ENTRY *aEntry = NULL;
    if (PeerTable::GetPeerTable()->FindEntry(PeerData->peerName, PeerData->realmName, aEntry))
    {
        DIA_PE_DISCONNECT_CAUSE_SUPPORT(aEntry) = PeerData->isSupportDisconnectCause;
        ret = ITS_SUCCESS;
    }
    return ret;
}
int DiaMgmt::SetPeerDPRCauseReconnectimers(PEER_INFO *PeerData)
{
    int ret = (!ITS_SUCCESS);
    PEER_ENTRY *aEntry = NULL;
    if (PeerTable::GetPeerTable()->FindEntry(PeerData->peerName, PeerData->realmName, aEntry))
    {
        DIA_PE_BUSY_RECONNECT_TIMER(aEntry) = PeerData->busyReconnectTimerVal;
        DIA_PE_DO_NOT_WANT_TO_TALK_TO_YOU_RECONNECT_TIMER(aEntry) = 
            PeerData->doNotWantToTalkYouReconnectTimerVal;
        ret = ITS_SUCCESS;
    }
    return ret;
}

int DiaMgmt::GetPeerTimers(PEER_INFO& PeerData)
{
    int ret = (!ITS_SUCCESS);
    PEER_ENTRY *aEntry = NULL;
    if (PeerTable::GetPeerTable()->FindEntry(PeerData.peerName, PeerData.realmName, aEntry))
    {
	PeerData.watchdog = DIA_PE_DW_TIME_VAL(aEntry);
	PeerData.retry = DIA_PE_RETRY_TIME_VAL(aEntry);
	PeerData.expiry = DIA_PE_EXPIRY_TIME_VAL(aEntry);
        ret = ITS_SUCCESS;
    }
    return ret;
}
int DiaMgmt::AddStaticRoutingConfig(const char* destHost,const char* destRealm,const char*peer,
                               const char* realm,int appId,int priority)
{
    int ret = ITS_SUCCESS;

    STATIC_ROUTE_ENTRY* staticRouteEntry = new STATIC_ROUTE_ENTRY; 

    staticRouteEntry->destinationHostName = destHost;
    staticRouteEntry->realmName = destRealm;
    staticRouteEntry->peerName = peer;
    staticRouteEntry->appId = appId;
    staticRouteEntry->priority =  priority;   
    STATIC_ROUTING_TABLE->InsertEntry(staticRouteEntry);
    return ret;

}


int DiaMgmt::ModifyStaticRoutingPriority(const char* destHost,const char*peer,
                                         int priority,int appId)
{
   int ret = ITS_SUCCESS;

   if(STATIC_ROUTING_TABLE->ModifyPriorityOfEntry(destHost,peer,priority,appId) !=ITS_SUCCESS)
   {
       ret = MOD_STATIC_ROUTING_ERR_ROUTE_NOT_PRESENT;
   }
   return ret;
}

int DiaMgmt::DeleteStaticRoutingEntry(const char* destHost,const char*peer,int appId)
{
   int ret = ITS_SUCCESS;

   if(STATIC_ROUTING_TABLE->RemoveEntry(destHost,peer,appId) !=ITS_SUCCESS)
   {
       ret = DEL_STATIC_ROUTING_ERR_ROUTE_DOESNT_EXIST;
   }
   return ret;
}

const char* DiaMgmt::GetDictionaryName(unsigned int appId)
{
    AppIdToDictMap::iterator it;
    char * dictionaryName = NULL;

    DT_DBG(("Find dictionary name for AppId %u",appId));

    it = m_appIdToDictMap.find(appId);
    if(it == m_appIdToDictMap.end())
    {
        DT_ERR(("No Dictionary is configured for appId %u",appId));
    }
    else
    {
        dictionaryName = new char [strlen(it->second.c_str()) + 1];
        strcpy(dictionaryName,it->second.c_str());
        DT_DBG(("Dictionary name for AppId %u is %s",
                 appId,dictionaryName));
    }
    return dictionaryName;
}

DiaMgmt::DiaMgmt()
{
    m_appIdToDictMap.insert(std::make_pair<unsigned int,std::string>(4,"gy_3gpp_r10_5"));
    m_appIdToDictMap.insert(std::make_pair<unsigned int,std::string>(16777238,"gx_3gpp_r10_6"));
    m_appIdToDictMap.insert(std::make_pair<unsigned int,std::string>(16777236,"rx_3gpp_r10_6"));
    m_appIdToDictMap.insert(std::make_pair<unsigned int,std::string>(16777266,"gxx_3gpp_r10_6"));
    m_appIdToDictMap.insert(std::make_pair<unsigned int,std::string>(16777251,"s6a_3gpp_r10_6"));
    m_appIdToDictMap.insert(std::make_pair<unsigned int,std::string>(16777267,"s9_3gpp_r10_6"));
    m_appIdToDictMap.insert(std::make_pair<unsigned int,std::string>(16777216,"cxdx_3gpp_r7_1"));
    m_appIdToDictMap.insert(std::make_pair<unsigned int,std::string>(16777302,"sy_3gpp_r11_4"));
    m_appIdToDictMap.insert(std::make_pair<unsigned int,std::string>(3,"gz_3gpp_r10_6"));
}

void DiaMgmt::ModifyIsRetransmissionFlag(PEER_INFO *PeerData,ITS_BOOLEAN isRetransmissionEnabled)
{
    PEER_ENTRY *pEntry = NULL;

    if (PeerTable::GetPeerTable()->FindEntry(PeerData->peerName, PeerData->realmName, pEntry))
    {
        DT_DBG(("Setting IsRetransmissionEnabled flag to %d",isRetransmissionEnabled));

        if(isRetransmissionEnabled && DIA_PE_PENDING_Q(pEntry)== NULL)
        {
            DT_DBG(("Setting retransmission enable flag to true.Creating pending Queue"));
            DIA_PE_RETRANSMISSION_ENABLED(pEntry) = true;
            DIA_PE_PENDING_Q(pEntry) = new PendingQ();
        }
        else if(isRetransmissionEnabled && DIA_PE_PENDING_Q(pEntry)!= NULL)
        {
            DT_DBG(("Setting retransmission enable flag to true.PendingQ already exists"));
            DIA_PE_RETRANSMISSION_ENABLED(pEntry) = true;
        }
        else if((!isRetransmissionEnabled) &&(DIA_PE_PENDING_Q(pEntry)!= NULL))
        {
            DIA_PE_RETRANSMISSION_ENABLED(pEntry) = false;
            if(DIA_PEER_CHK_IS_FAILOVER_ENABLED(pEntry)
                    || DIA_PEER_CHK_IS_FAILBACK_ENABLED(pEntry))
            {
                DT_DBG(("Diable Retransmission for peer %s. \
                            Failover/failback enabled cannot delete pendingQ",DIA_PE_HOST(pEntry)));
            }
            else
            {
                DT_DBG(("Remove all entries in pendingQ and delete it"));
                //DIA_PE_PENDING_Q(pEntry)->CancelAllRetransmitTimerAndRemoveAllEntry();
                delete DIA_PE_PENDING_Q(pEntry);
                DIA_PE_PENDING_Q(pEntry) = NULL;

            }
        }
        else if((!isRetransmissionEnabled) &&(DIA_PE_PENDING_Q(pEntry)== NULL))
        {
            DT_DBG(("Diable Retransmission for peer %s",DIA_PE_HOST(pEntry)));
            DIA_PE_RETRANSMISSION_ENABLED(pEntry) = false;
        }
    }
}


