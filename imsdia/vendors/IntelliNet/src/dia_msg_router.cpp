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
 * LOG: $Log: dia_msg_router.cpp,v $
 * LOG: Revision 3.38.6.16.4.8.2.2.2.8.4.2.2.3.2.1.2.5  2017/12/21 04:37:21  jkchaitanya
 * LOG: Ticket 1149 changes to support case insensitivity for peers, hosts 7 realms
 * LOG:
 * LOG: Revision 3.38.6.16.4.8.2.2.2.8.4.2.2.3.2.1.2.4  2015/04/02 12:59:05  jkchaitanya
 * LOG: Changes made for handling peer notifications to app
 * LOG:
 * LOG: Revision 3.38.6.16.4.8.2.2.2.8.4.2.2.3.2.1.2.3  2014/12/17 05:19:08  jkchaitanya
 * LOG: changes to revert back the server down crash changes
 * LOG:
 * LOG: Revision 3.38.6.16.4.8.2.2.2.8.4.2.2.3.2.1.2.1  2014/12/04 12:00:26  pramana
 * LOG: Added support for allowing requests for a different hosts
 * LOG:
 * LOG: Revision 3.38.6.16.4.8.2.2.2.8.4.2.2.3.2.1  2014/10/27 08:28:39  millayaraja
 * LOG: changes for HA HotStandBy
 * LOG:
 * LOG: Revision 3.38.6.16.4.8.2.2.2.8.4.2.2.3  2014/08/26 10:27:39  pramana
 * LOG: Compilation warning fixes in imsdia
 * LOG:
 * LOG: Revision 3.38.6.16.4.8.2.2.2.8.4.2.2.2  2014/08/05 12:37:20  jsarvesh
 * LOG: Changes done for handling exception thrown and sending indication to Application
 * LOG:
 * LOG: Revision 3.38.6.16.4.8.2.2.2.8.4.2.2.1  2014/07/02 06:37:11  millayaraja
 * LOG: updated to handle answer message without mandatory field missing
 * LOG:
 * LOG: Revision 3.38.6.16.4.8.2.2.2.8.4.2  2014/05/12 05:48:52  millayaraja
 * LOG: merged changes for Hop-By-Hop Id fix from B-DRE-0400-01-AICENT-POC branch
 * LOG:
 * LOG: Revision 3.38.6.16.4.8.2.2.2.8.4.1  2014/04/03 09:34:54  millayaraja
 * LOG: DiaMsgFlow Copy constructor and avoid crash while sending message to application, indication with data
 * LOG:
 * LOG: Revision 3.38.6.16.4.8.2.2.2.8  2014/01/06 09:22:32  cprem
 * LOG: Changes in diameter stack to support session replication. Review request 1611.
 * LOG:
 * LOG: Revision 3.38.6.16.4.8.2.2.2.7  2013/12/27 12:47:59  ncshivakumar
 * LOG:  Fix for bug Bug 2654
 * LOG:
 * LOG: Revision 3.38.6.16.4.8.2.2.2.6  2013/12/13 09:34:58  vsarath
 * LOG: Merged the session-splict changes
 * LOG:
 * LOG: Revision 3.38.6.16.4.8.2.2.2.5  2013/12/11 06:26:25  ncshivakumar
 * LOG: Fixed bug 2444
 * LOG:
 * LOG: Revision 3.38.6.16.4.8.2.2.2.4  2013/12/09 04:52:26  ncshivakumar
 * LOG: Fixed bug 2439,2443,2368,1898
 * LOG:
 * LOG: Revision 3.38.6.16.4.8.2.2.2.3  2013/11/14 08:54:54  ncshivakumar
 * LOG: RFC6733 changes
 * LOG:
 * LOG: Revision 3.38.6.16.4.8.2.2.2.2  2013/10/26 07:42:21  ncshivakumar
 * LOG: RFC 6733 changes
 * LOG:
 * LOG: Revision 3.38.6.16.4.8.2.2.2.1  2013/09/10 08:36:39  ncshivakumar
 * LOG: RFC6733 Changes
 * LOG:
 * LOG: Revision 3.38.6.16.4.8.2.2  2013/07/01 07:35:49  nazad
 * LOG: changes for memory Leak, Review Request 1041
 * LOG:
 * LOG: Revision 3.38.6.16.4.8.2.1  2013/06/04 04:55:03  ncshivakumar
 * LOG: During static routing check for application id also
 * LOG:
 * LOG: Revision 3.38.6.16.4.8  2013/04/12 04:17:42  vsarath
 * LOG: Logs improvement
 * LOG:
 * LOG: Revision 3.38.6.16.4.7  2013/04/04 09:06:11  mallikarjun
 * LOG: MemLeak Fixes Bug 1205 1298
 * LOG:
 * LOG: Revision 3.38.6.16.4.6  2013/04/04 03:47:25  ksalil
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 3.38.6.16.4.5  2013/04/01 05:54:05  vsarath
 * LOG: Fix for Coverity warnings
 * LOG:
 * LOG: Revision 3.38.6.16.4.4  2013/03/15 11:10:56  mallikarjun
 * LOG: BUG-1013-Chages
 * LOG:
 * LOG: Revision 3.38.6.16.4.3  2013/03/12 06:46:54  vsarath
 * LOG: Fix for coverity issues
 * LOG:
 * LOG: Revision 3.38.6.16.4.2  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.38.6.16.4.1  2013/02/27 04:43:50  millayaraja
 * LOG: modified for interface stats
 * LOG:
 * LOG: Revision 3.38.6.16  2013/01/08 03:53:04  jvikas
 * LOG: Bug 769: Added check on DiaMsgFlow if its having BaseGenCommand before allocating memory.
 * LOG:
 * LOG: Revision 3.38.6.15  2012/12/21 05:31:54  ncshivakumar
 * LOG: Modified for tracing
 * LOG:
 * LOG: Revision 3.38.6.14  2012/12/17 05:36:47  mallikarjun
 * LOG: Bug 650 static routing for relay
 * LOG:
 * LOG: Revision 3.38.6.13  2012/12/03 08:41:20  ncshivakumar
 * LOG: Changes done for adding static routing table
 * LOG:
 * LOG: Revision 3.38.6.12  2012/12/03 02:39:01  mallikarjun
 * LOG: Bug-148-Alternate-Peer
 * LOG:
 * LOG: Revision 3.38.6.11  2012/11/28 07:34:58  vsarath
 * LOG: Fix for issue 361
 * LOG:
 * LOG: Revision 3.38.6.10  2012/11/20 17:39:44  pramana
 * LOG: Merged from CMAPI branch for 212-07 release
 * LOG:
 * LOG: Revision 3.38.6.4.12.4  2012/11/20 10:31:24  rgovardhan
 * LOG: merge from 00 Nov20Rel
 * LOG:
 * LOG: Revision 3.38.6.4  2012/10/03 15:08:43  cprem
 * LOG: Merged from ERLBF branch B-DRE-0212-02
 * LOG:
 * LOG: Revision 3.38.6.3  2012/09/22 08:57:44  pramana
 * LOG: Fix for bug 241
 * LOG:
 * LOG: Revision 3.38.6.2  2012/09/20 14:58:20  cprem
 * LOG: Fix for bug 245. Added check for invalid dict-id configuration.
 * LOG:
 * LOG: Revision 3.38.6.1.2.1  2012/09/20 07:53:09  cprem
 * LOG: Support for multiple dictionary id configuration per peer.
 * LOG:
 * LOG: Revision 3.38.6.1  2012/09/06 11:30:45  jvikas
 * LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
 * LOG:
 * LOG: Revision 3.38.8.8  2012/09/05 12:14:13  jvikas
 * LOG: Bug 218: Sending Back ULA with result code instead of crash.
 * LOG:
 * LOG: Revision 3.38.8.7  2012/08/30 11:45:01  jvikas
 * LOG: Fixed issues with DiaMsgFlow Constructor and SendCmdToPeer used by Test App
 * LOG:
 * LOG: Revision 3.38.8.6  2012/08/28 12:51:43  jvikas
 * LOG: Completed Set for Encoded Buffer and Len on the outMsg
 * LOG:
 * LOG: Revision 3.38.8.5  2012/08/27 11:05:53  cprem
 * LOG: Added json includes.
 * LOG:
 * LOG: Revision 3.38.8.4  2012/08/27 09:45:17  jvikas
 * LOG: Fixed Header Copy Issue in Answer Message
 * LOG:
 * LOG: Revision 3.38.8.3  2012/08/23 11:32:29  jvikas
 * LOG: 1. Reading dictId from Peer Table Configuration
 * LOG: 2. Calling BaseGenericCmd Destructor in DiaMsgFlow Destructor
 * LOG: 3. Changed DictId ITS_UINT
 * LOG: 4. Added HandleTransConfig
 * LOG:
 * LOG: Revision 3.38.8.2  2012/08/22 12:53:43  jvikas
 * LOG: Fixed Linking Errors and Included XML Config for Transformation.
 * LOG:
 * LOG: Revision 3.38.8.1  2012/08/21 06:16:25  jvikas
 * LOG: Checkin Working Modified Stack Code -Need to Cleanup and Fix Issues.
 * LOG:
 * LOG: Revision 3.38  2010/08/19 11:21:26  nvijikumar
 * LOG: Porting changes from B-MOTO-IDIA-0421-00
 * LOG: 1. New Overload implimentation changes are not being ported.
 * LOG: 2. Force disconnect changes are not being ported.
 * LOG:
 * LOG: Revision 3.37  2009/12/08 08:20:42  sureshj
 * LOG: IDS core dump when command received with Destination-Host and
 * LOG: Destination-Realm AVPs missing.
 * LOG:
 * LOG: Revision 3.36  2009/09/11 09:28:56  rajeshak
 * LOG: Added Debug prints to print Auth AppId/Acct AppId and vendorId in msg
 * LOG:
 * LOG: Revision 3.35  2009/06/10 03:40:05  rajeshak
 * LOG: Added a check for Peer open state in overloaded SendCmdToPeer.
 * LOG:
 * LOG: Revision 3.34  2009/04/13 12:44:38  rajeshak
 * LOG: Raising an Alarm if Destination Host is not there in Peer Table.
 * LOG:
 * LOG: Revision 3.33  2009/04/07 13:49:47  sureshj
 * LOG: Overload Control Indications added.
 * LOG:
 * LOG: Revision 3.32  2009/03/19 16:22:15  ssaxena
 * LOG: Modification done to add Redirect Agent Application.
 * LOG:
 * LOG: Revision 3.31  2009/03/19 12:31:49  nvijikumar
 * LOG: Global instance is created for the Class ITSDiaConfig to avoid function
 * LOG: call overhead as ITSDiaConfig::GetITSDiaConfig() was called max time
 * LOG:
 * LOG: Revision 3.30  2009/03/19 11:29:00  rajeshak
 * LOG: Memory leak fix for error scenario.
 * LOG:
 * LOG: Revision 3.29  2009/02/19 14:05:57  ssaxena
 * LOG: Partial fix for the whizible issue Id 1493, 1481 and 1482.
 * LOG: Default routing failed and Relay/Proxy failed to forward
 * LOG: ASR/RAR.
 * LOG:
 * LOG: Revision 3.28  2009/02/19 12:45:58  nvijikumar
 * LOG: Previous commit changes were done to wrong API, correcting the same
 * LOG:
 * LOG: Revision 3.27  2009/02/19 12:31:23  nvijikumar
 * LOG: Commented mutex from UpdatePeerStatmachine() due to performance issues,
 * LOG: may be it is not required for down stream handling
 * LOG:
 * LOG: Revision 3.26  2009/02/19 09:43:14  nvijikumar
 * LOG: BaseCommand takes care of deleting the encoded buffer
 * LOG:
 * LOG: Revision 3.25  2009/02/12 04:19:20  nvijikumar
 * LOG: Message Processing at IDS layer using Callback function in upstream
 * LOG: thread scope
 * LOG:
 * LOG: Revision 3.24  2009/02/05 09:58:00  ssaxena
 * LOG: Changes for Redirect Agent code reviews.
 * LOG:
 * LOG: Revision 3.23  2009/02/03 10:21:11  ssaxena
 * LOG: Modifications done for Redirect Agent functionality.
 * LOG:
 * LOG: Revision 3.22  2009/01/06 12:51:17  rajeshak
 * LOG: comments added
 * LOG:
 * LOG: Revision 3.21  2009/01/03 05:42:15  rajeshak
 * LOG: 1. Fixes for memory leak in OriginStateId
 * LOG: 2. Introduced common func to send all indications
 * LOG:
 * LOG: Revision 3.20  2008/12/26 10:38:46  ssaxena
 * LOG: Issue Id : 1400 ( IntiateFailover success on alternate peer down ).
 * LOG: Description : Added Check for alternate Peer is in OPEN state.
 * LOG:
 * LOG: Revision 3.19  2008/12/23 12:19:37  sureshj
 * LOG: Removed statistics updates from this file. Fix for issue 1379.
 * LOG:
 * LOG: Revision 3.18  2008/12/22 10:58:23  rajeshak
 * LOG: IssueID:1360
 * LOG: FeatureID:none
 * LOG: Description: Fix for Memory Leak.
 * LOG: (in error scenario encoded buffer was not getting deleted)
 * LOG:
 * LOG: Revision 3.17  2008/12/12 18:30:47  rajeshak
 * LOG: Lightweight Decode for base AVPS
 * LOG: New Command class is introduced (BaseCommand)
 * LOG:
 * LOG: Revision 3.16  2008/12/12 16:36:06  nvijikumar
 * LOG: Updates to raise Alarms
 * LOG:
 * LOG: Revision 3.15  2008/12/12 12:32:08  nvijikumar
 * LOG: Updated with statistic support
 * LOG:
 * LOG: Revision 3.14  2008/12/11 11:16:59  nvijikumar
 * LOG: Provided IsLocalMatchFound for downstream handling
 * LOG:
 * LOG: Revision 3.13  2008/12/10 11:28:12  nvijikumar
 * LOG: Avoid ROUTE_SelectApplication call incase of Distributed Scenario
 * LOG: Direct PutEvent on distributed task queue
 * LOG:
 * LOG: Revision 3.12  2008/12/07 09:43:31  rajeshak
 * LOG: Made Indentation properly
 * LOG:
 * LOG: Revision 3.11  2008/11/24 15:59:04  ssaxena
 * LOG: Issue-Id: 1305
 * LOG: Feature-Id: None
 * LOG: Description:Check added in case of Cold-Standby Backup Node
 * LOG:             should not send message to upstream.
 * LOG:
 * LOG: Revision 3.10  2008/10/31 05:51:03  nvijikumar
 * LOG: IssueID:1189
 * LOG: FeatureID:none
 * LOG: Description: Code Optimization and  stack tunning
 * LOG:
 * LOG: Revision 3.9  2008/09/02 17:06:54  ssaxena
 * LOG: Added miscellenous debug print.
 * LOG:
 * LOG: Revision 3.8  2008/08/25 05:32:42  ssaxena
 * LOG: Check Alternative trInst before Initiating failover
 * LOG:
 * LOG: Revision 3.7  2008/08/21 06:25:39  nvijikumar
 * LOG: Memory leak fixes
 * LOG:
 * LOG: Revision 3.6  2008/04/24 11:38:52  avinashks
 * LOG: Fix for Whizible Issue id: 912
 * LOG: Changes done to print the traces properly.
 * LOG:
 * LOG: Revision 3.5  2008/04/22 21:09:58  hbhatnagar
 * LOG: Provided fix for issues 814, 844, 847, 874, 880 in whizible.
 * LOG:
 * LOG: Revision 3.4  2008/04/11 18:44:25  hbhatnagar
 * LOG: Debug prints in CheckDesinationPeer and RealmRouting are added/changed
 * LOG: for proper understanding.
 * LOG:
 * LOG: Revision 3.3  2008/04/07 17:34:53  hbhatnagar
 * LOG: Changed the signature for the RequestForwarding and RequestRouting APIs.
 * LOG: Also made changes for Hop-by-hop id and added a new API
 * LOG: VerifyIfReqForwarding().
 * LOG:
 * LOG: Revision 3.2  2008/04/01 16:53:18  hbhatnagar
 * LOG: Changes for Proxy and Relay support 3.0 release - (Viji, Hemant)
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.61  2008/03/27 12:14:08  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.55.2.7  2007/12/22 15:58:39  hbhatnagar
 * LOG: Changing the place for ReleaseMutex() in UpdatePeerSM(). Fix
 * LOG: for issues 1,4, 6 and 8 raised during the validation of
 * LOG: bcgi ticket 1807.
 * LOG:
 * LOG: Revision 2.55.2.6  2007/12/16 05:59:11  hbhatnagar
 * LOG: Made changes to provide fix for issue No.11 raised during the validation
 * LOG: of bcgi ticket 1807.
 * LOG:
 * LOG: Revision 2.55.2.5  2007/04/26 04:15:18  nvijikumar
 * LOG: Get the trInstance before droping the message from the backup peer.
 * LOG:
 * LOG: Revision 2.55.2.4  2007/04/24 09:39:55  nvijikumar
 * LOG: Fixes:
 * LOG: 1. Memory leak issue in redundant mode.
 * LOG: 2. Dont reject any message in the backup if it is multicasted one.
 * LOG:
 * LOG: Revision 2.55.2.3  2007/03/30 12:46:42  nvijikumar
 * LOG: Alway allow Base protocol message explicit registration is not required.
 * LOG:
 * LOG: Revision 2.55.2.2  2007/03/22 16:15:26  nvijikumar
 * LOG: Fix for Hop-by-Hop and End-To-End issue incase of redundant mode.
 * LOG: Reported by BCGI.
 * LOG:
 * LOG: Revision 2.55.2.1  2007/03/08 14:51:50  nvijikumar
 * LOG: 1. Fix for realm based routing between two deferent realms.
 * LOG: 2. Failover should happen if there is DestinationHost and that is not
 * LOG:    there in the peerTable.
 * LOG:
 * LOG: Revision 2.55  2007/02/21 10:18:47  nvijikumar
 * LOG: Control Hexdump print from XML.
 * LOG:
 * LOG: Revision 2.54  2006/12/22 09:27:22  nvijikumar
 * LOG: Fix for Double removal of session entries in case of DCCA
 * LOG:
 * LOG: Revision 2.53  2006/12/21 15:26:04  tpanda
 * LOG: AddOriginStateId option is added to check if OriginStateId be added to cmd
 * LOG:
 * LOG: Revision 2.52  2006/12/20 15:54:05  nvijikumar
 * LOG: Elimination of multiple ITS_FindFeature function calls(DCCA & Redundancy).
 * LOG:
 * LOG: Revision 2.51  2006/12/19 13:55:29  nvijikumar
 * LOG: Return ITS_DIA_APP_UNSUPPORTED from Validate fun if App is not registered.
 * LOG:
 * LOG: Revision 2.50  2006/12/17 03:34:44  tpanda
 * LOG: Fix for bug# 5067 and default route handling
 * LOG:
 * LOG: Revision 2.49  2006/12/15 05:44:28  nvijikumar
 * LOG: Redundancy: Remove msg and return incase of Backup server in SendMsgToApp fun.
 * LOG:
 * LOG: Revision 2.48  2006/12/14 13:45:49  tpanda
 * LOG: Fix for sending STR failing from peer to backup(bug#5053)
 * LOG:
 * LOG: Revision 2.47  2006/12/13 14:26:52  tpanda
 * LOG: Fix for DWR/DWA exchanges with the backup node(bug#5050)
 * LOG:
 * LOG: Revision 2.46  2006/12/12 15:45:12  hbhatnagar
 * LOG: made changes for the loopback message handling for DCCA
 * LOG:
 * LOG: Revision 2.45  2006/12/12 14:55:12  tpanda
 * LOG: Fix for getting alt-transport Instance if main peer is down
 * LOG:
 * LOG: Revision 2.44  2006/12/11 14:27:34  nvijikumar
 * LOG: Send Peer based msgs to application, if peerMsgToApp flag is set in the XML.
 * LOG:
 * LOG: Revision 2.43  2006/12/11 13:51:25  tpanda
 * LOG: REDUNDANCY_SLOT_CHANGES are removed and code seems to be stable
 * LOG:
 * LOG: Revision 2.42  2006/12/10 13:42:42  tpanda
 * LOG: Redundancy Bug Fixes and enhancements--Transport Order Fix
 * LOG:
 * LOG: Revision 2.41  2006/12/01 13:51:26  nvijikumar
 * LOG: Fixes for Pending Queue issues.
 * LOG: Set stopFailover flag, incase of Failback.
 * LOG:
 * LOG: Revision 2.40  2006/12/01 13:03:17  hbhatnagar
 * LOG: made changes for the correct error response for DCCA
 * LOG:
 * LOG: Revision 2.39  2006/11/30 18:54:24  tpanda
 * LOG: Redundancy slot changes backed out. TODO: Refer (REDUNDANCY_SLOT_CHANGES) defines
 * LOG: Failover and failback bug fixes
 * LOG:
 * LOG: Revision 2.38  2006/11/30 13:46:14  hbhatnagar
 * LOG: put check for sending error response in case of request only.
 * LOG:
 * LOG: Revision 2.37  2006/11/30 10:36:29  hbhatnagar
 * LOG: made changes for the error handling of DCCA errors.
 * LOG:
 * LOG: Revision 2.36  2006/11/29 15:07:02  kamakshilk
 * LOG: Fix for Bug Id 4982
 * LOG:
 * LOG: Revision 2.35  2006/11/29 11:52:14  tpanda
 * LOG: Redundancy related enhancements and fixes for few bugs raised for redundancy
 * LOG:
 * LOG: Revision 2.34  2006/11/28 13:29:33  nvijikumar
 * LOG: Failover and Multicasting clientId changes ( viji and kamakshi).
 * LOG:
 * LOG: Revision 2.33  2006/11/27 15:01:24  hbhatnagar
 * LOG: made changes for the Release session indication for upstream
 * LOG:
 * LOG: Revision 2.32  2006/11/27 05:15:11  nvijikumar
 * LOG: Dont insert re-transmitted message to queue.
 * LOG:
 * LOG: Revision 2.31  2006/11/25 11:03:13  nvijikumar
 * LOG: DCCA Indication function pointer correction. (Tushar).
 * LOG:
 * LOG: Revision 2.30  2006/11/25 03:57:20  tpanda
 * LOG: Changes for Msg based redundancy
 * LOG:
 * LOG: Revision 2.29  2006/11/25 02:42:43  nvijikumar
 * LOG: changes for msg based redundancy
 * LOG:
 * LOG: Revision 2.28  2006/11/24 17:20:12  hbhatnagar
 * LOG: made changes for the new signature of Dcca Access functions
 * LOG:
 * LOG: Revision 2.27  2006/11/24 03:49:17  nvijikumar
 * LOG: Failback retransmit the pending requests to the same peer.
 * LOG:
 * LOG: Revision 2.26  2006/11/23 09:17:48  tpanda
 * LOG: Fix for crash for peer messages exchange
 * LOG:
 * LOG: Revision 2.25  2006/11/22 10:49:37  nvijikumar
 * LOG: Baseline PendingQ ( Failover ) Changes.
 * LOG:
 * LOG: Revision 2.24  2006/11/16 14:49:16  tpanda
 * LOG: Redundancy support for ITS-Diameter--Baseline code
 * LOG:
 * LOG: Revision 2.23  2006/11/09 14:31:26  tpanda
 * LOG: clientId handling for IDS at the stack level
 * LOG:
 * LOG: Revision 2.22  2006/10/31 08:47:39  yranade
 * LOG: Get RealmBased routing working. BugFix: 4680.
 * LOG:
 * LOG: Revision 2.21  2006/10/30 12:10:49  yranade
 * LOG: Set Orgin-State-Id.
 * LOG:
 * LOG: Revision 2.20  2006/10/26 14:50:13  hbhatnagar
 * LOG: made changes in SendMsgToApp for sending the Indications to DCCA module ( Hemant)
 * LOG:
 * LOG: Revision 2.19  2006/10/25 12:52:44  yranade
 * LOG: Realm routing issue seen when vendorId *may* not be set.
 * LOG:
 * LOG: Revision 2.18  2006/10/25 11:29:23  nvijikumar
 * LOG: Print Byte dump Only if traces are enabled.
 * LOG:
 * LOG: Revision 2.17  2006/10/25 06:30:38  hbhatnagar
 * LOG: Integration with ITS_Diameter First Cut (badri)
 * LOG:
 * LOG: Revision 2.16  2006/10/24 15:47:08  yranade
 * LOG: Bug Fix 4596. Return appropriate error code from Validate.
 * LOG:
 * LOG: Revision 2.15  2006/10/24 13:58:19  yranade
 * LOG: 1. Code cleanup & Bug Fixes
 * LOG: 2. Header changes. Use header by reference from the message.
 * LOG: 3. Finish up realm routing. Get default routing working.
 * LOG: 4. Improved Traces.
 * LOG: 5. ValidateMessage Signature update.
 * LOG:
 * LOG: Revision 2.14  2006/10/18 06:27:35  yranade
 * LOG: Allow AuthAppId == 0 & AcctAppId == 3, in Validate.
 * LOG:
 * LOG: Revision 2.13  2006/10/17 18:45:28  yranade
 * LOG: ValidateMessage in MessageForwarding rather than SendCmdToPeer.
 * LOG:
 * LOG: Revision 2.12  2006/10/17 18:09:06  yranade
 * LOG: ValidateMessage API
 * LOG:
 * LOG: Revision 2.11  2006/10/16 16:02:17  yranade
 * LOG: Format our custom Header to application in Big-Endian style
 * LOG:
 * LOG: Revision 2.10  2006/10/13 16:44:35  yranade
 * LOG: Error handling related updates.
 * LOG:
 * LOG: Revision 2.9  2006/10/12 07:21:22  nvijikumar
 * LOG: Check for sending a message in the Peer Wait CEA state.
 * LOG:
 * LOG: Revision 2.8  2006/10/11 15:04:53  yranade
 * LOG: Fixes for issues: 4451, 4452, 4454, 4457.
 * LOG:
 * LOG: Revision 2.7  2006/10/09 13:41:39  yranade
 * LOG: Get RealmRouting working.
 * LOG:
 * LOG: Revision 2.6  2006/10/09 11:31:46  yranade
 * LOG: Lookup Default Realm Entry.
 * LOG:
 * LOG: Revision 2.5  2006/10/09 06:29:02  yranade
 * LOG: Fix issues seen in realm based routing.
 * LOG:
 * LOG: Revision 2.4  2006/10/07 12:24:55  yranade
 * LOG: Today's round of updates.
 * LOG:
 * LOG: Revision 2.3  2006/10/05 13:21:54  yranade
 * LOG: Getting there.
 * LOG:
 * LOG: Revision 2.2  2006/09/26 06:09:25  nvijikumar
 * LOG: Added return statements ( issue with Sun CC Compiler).
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:44  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:29  yranade
 * LOG: Initial Version of ITS-Diameter (Yogesh, Viji, Tushar)
 * LOG:
 *
 ****************************************************************************/

#include <its++.h>
#include <engine++.h>
#include <json/json.h>

#include <itsdiameter.h>
#include <dia_cmn.h>
#include <dia_msg_flow.h>
#include <dia_stack.h>
#include <dia_defines.h>
#include <dia_trace.h>
#include <dia_err.h>
#include <dia_utils.h>
#include <dia_msg_router.h>
#include <its_dia_config.h>
#include <dia_peer_table.h>
#include <dia_realm_table.h>
#include <dcca_feature.h>
#include <dia_redirect.h>
#include <DTFLog.h>
#include <dia_stack_statistics.h>
#include <dia_static_routing_table.h>
#include <DiameterDictionaryStats.h>

#include "dia_tracer.h"

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
using namespace diameter;
using namespace diameter::base;
#endif

static ITS_USHORT CheckDestinationPeer(REALM_ENTRY *rEntry, int index);
extern ITS_BOOLEAN overLoadF;

IncomingMsgQ* DiaMsgRouter::diaInMsgQ = NULL;

int 
DiaMsgRouter::ValidateMessage(DIA_GEN_CMD *ce, DIA_BASE_CMD *msg)
{
    int i = 0, j = 0;
    if (ce == NULL || msg == NULL)
    {
        return (ITS_DIA_UNABLE_TO_DELIVER);
    } 
   
    /*
     * Validation is not required for Base Protocol Messages.
     */
    if (msg->getApplicationId() == 0)
    {
        return (ITS_SUCCESS);
    }
    ITS_UINT appId[3] = {msg->getApplicationId(), msg->getApplicationId(),
                        msg->getApplicationId()};
    if (msg->getAuthApplicationId())
    {
        if (msg->getAuthApplicationId()->value() == 0)
        {
            return (ITS_SUCCESS);
        }
        appId[0] = msg->getAuthApplicationId()->value();
    }
    else
    { 
        appId[0] = msg->getHeader().appId;
    }

    if (msg->getAcctApplicationId())
    {
        if (msg->getAcctApplicationId()->value() == 3)
        {
            return (ITS_SUCCESS);
        }
        appId[1] = msg->getAcctApplicationId()->value();
    }
    else
    { 
        appId[1] = msg->getHeader().appId;
    }

    if (msg->getVendorSpecificApplicationId()) 
    {
        if (msg->getVendorSpecificApplicationId()->containsAuthApplicationId())
        {
           appId[2] = msg->getVendorSpecificApplicationId()->getAuthApplicationId().value();
        }
        else if(msg->getVendorSpecificApplicationId()->containsAcctApplicationId())
        {
           appId[2] = msg->getVendorSpecificApplicationId()->getAcctApplicationId().value();
        }
    }
    else
    { 
        appId[2] = msg->getHeader().appId;
    }

    for (
         i = 0; 
         i < ce->countAuthApplicationId() ||
         i < ce->countAcctApplicationId() ||
         i < ce->countVendorSpecificApplicationId(); 
         i++)
    {
        if (i < ce->countAuthApplicationId() &&
           (appId[0] == ce->getAuthApplicationId(i)->value() ||
            appId[2] == ce->getAuthApplicationId(i)->value()))
        {
            return ITS_SUCCESS;
        }
        else if(i < ce->countAcctApplicationId() &&
               (appId[1] == ce->getAcctApplicationId(i)->value()||
                appId[2] == ce->getAcctApplicationId(i)->value()))
        {
            return ITS_SUCCESS;
        }
        else if(i < ce->countVendorSpecificApplicationId())
        {
            const VendorSpecificApplicationId *lvs =
               ce->getVendorSpecificApplicationId(i);
            if (lvs->containsAuthApplicationId())
            {
                if (lvs->getAuthApplicationId().value() == appId[0] ||
                    lvs->getAuthApplicationId().value() == appId[2])
                {
                    return ITS_SUCCESS;
                }
            }
            else if(lvs->containsAcctApplicationId())
            {
                if (lvs->getAcctApplicationId().value() == appId[1] ||
                    lvs->getAcctApplicationId().value() == appId[2])
                {
                    return ITS_SUCCESS;
                }
            }
        }
    }

    if (msg->getCommandCode() == DIA_MSG_CE)
    {
        return (ITS_DIA_NO_COMMON_APP);
    }
    return (ITS_DIA_APP_UNSUPPORTED);
}

int 
DiaMsgRouter::ValidateMessage(DIA_GEN_CMD *ce, DIA_GEN_CMD *msg)
{
    int i = 0, j = 0;

    if (ce == NULL || msg == NULL)
    {
        return (ITS_DIA_UNABLE_TO_DELIVER);
    } 
   
    /*
     * Validation is not required for Base Protocol Messages.
     */
    if (msg->getApplicationId() == 0)
    {
        return (ITS_SUCCESS);
    }

    ITS_UINT appId[3] = {msg->getApplicationId(), msg->getApplicationId(),
                        msg->getApplicationId()};

    if (msg->getAuthApplicationId())
    {
        if (msg->getAuthApplicationId()->value() == 0)
        {
            return (ITS_SUCCESS);
        }
        appId[0] = msg->getAuthApplicationId()->value();
    }
    if (msg->getAcctApplicationId())
    {
        if (msg->getAcctApplicationId()->value() == 3)
        {
            return (ITS_SUCCESS);
        }
        appId[1] = msg->getAcctApplicationId()->value();
    }
    if (msg->getVendorSpecificApplicationId()) 
    {
        if (msg->getVendorSpecificApplicationId()->containsAuthApplicationId())
        {
           appId[2] = msg->getVendorSpecificApplicationId()->getAuthApplicationId().value();
        }
        else if(msg->getVendorSpecificApplicationId()->containsAcctApplicationId())
        {
           appId[2] = msg->getVendorSpecificApplicationId()->getAcctApplicationId().value();
        }
    }
       

    for (
         i = 0; 
         i < ce->countAuthApplicationId() ||
         i < ce->countAcctApplicationId() ||
         i < ce->countVendorSpecificApplicationId(); 
         i++)
    {
        if (i < ce->countAuthApplicationId() &&
           (appId[0] == ce->getAuthApplicationId(i)->value() ||
            appId[2] == ce->getAuthApplicationId(i)->value()))
        {
            return ITS_SUCCESS;
        }
        else if(i < ce->countAcctApplicationId() &&
               (appId[1] == ce->getAcctApplicationId(i)->value()||
                appId[2] == ce->getAcctApplicationId(i)->value()))
        {
            return ITS_SUCCESS;
        }
        else if(i < ce->countVendorSpecificApplicationId())
        {
            const VendorSpecificApplicationId *lvs =
               ce->getVendorSpecificApplicationId(i);
            if (lvs->containsAuthApplicationId())
            {
                if (lvs->getAuthApplicationId().value() == appId[0] ||
                    lvs->getAuthApplicationId().value() == appId[2])
                {
                    return ITS_SUCCESS;
                }
            }
            else if(lvs->containsAcctApplicationId())
            {
                if (lvs->getAcctApplicationId().value() == appId[1] ||
                    lvs->getAcctApplicationId().value() == appId[2])
                {
                    return ITS_SUCCESS;
                }
            }
        }
    }
    if (msg->getCommandCode() == DIA_MSG_CE)
    {
        return (ITS_DIA_NO_COMMON_APP);
    }

    return (ITS_DIA_APP_UNSUPPORTED);
}

int DiaMsgRouter::CheckIfMsgTobeQueued(DIA_BASE_CMD *msg,SESSION_ENTRY *ent,ITS_EVENT &ev)
{
     DT_DBG(("ENTER CheckIfMsgTobeQueued "));
     ITS_INT retVal= (!ITS_SUCCESS);
        if( (msg->getHeader().flags.t == ITS_DIA_MASK_FLAG ) &&
        (DIA_SE_RX_HH(ent) == msg->getHeader().hh)  &&
        (DIA_SE_RX_EE(ent) == msg->getHeader().ee) )
    {
                return retVal;
        }

    if( DIA_SE_MSG_STATUS(ent) != ANS_SND_TO_PEER)
    {


                ITS_USHORT trInst = ITS_GET_CTXT(ev.data);
                ITS_OCTET trdata[sizeof(ITS_USHORT)];
                ITS_SET_CTXT(trdata, trInst);

                ITS_OCTET* aData= (ITS_OCTET*)msg->getEncodedBuf();
                ITS_USHORT aLen= msg->getEncodedBufLen() + sizeof(ITS_USHORT);
                ITS_EVENT *lEvent=new ITS_EVENT;
                lEvent->len = aLen;
                lEvent->src=ev.src;
                ITS_EVENT_INIT(lEvent,ev.src, aLen);
                memcpy(&lEvent->data[0],trdata, sizeof(ITS_USHORT));
                memcpy(&lEvent->data[sizeof(ITS_USHORT)], aData, msg->getEncodedBufLen());

                DT_DBG(("InsertMsgEvent Event-Src = %d ,Trans-Inst = %d ,  Data-Len = %d ",lEvent->src,trInst,aLen));

                if(diaInMsgQ->InsertMsgEvent(DIA_SE_SINDX(ent),DIA_SE_MESSAGES_PENDING(ent),lEvent) == ITS_SUCCESS)
                {
                  DT_DBG(("InsertMsgEvent Success -  Sess-Id = %s , Sess-IndX = %d ,Cmd-code = %d , Sess-Entry PendingMsg status = %d ",msg->getSessionId()->value().c_str(),DIA_SE_SINDX(ent),msg->getCommandCode(),DIA_SE_MESSAGES_PENDING(ent)));
          retVal=ITS_SUCCESS;
        }
    }
            else
        {
         DT_DBG(("No Need to InsertMsgEvent"));
        }

    DT_DBG(("LEAVE CheckIfMsgTobeQueued  Ret-Val = %d ",retVal));
    return retVal;
}
ITS_INT DiaMsgRouter::RepostPendingMessageOfSession(SESSION_ENTRY* aSessEntry,ITS_OCTET * sessionId)
{
        DT_DBG(("ENTER RepostPendingMessageOfSession"));

        ITS_EVENT *lEvent=NULL;
        ITS_INT retVal = (!ITS_SUCCESS);

                retVal=diaInMsgQ->GetMsgEvent(DIA_SE_SINDX(aSessEntry),DIA_SE_MESSAGES_PENDING(aSessEntry),&lEvent);
                /*if(  (!DIA_SE_MESSAGES_PENDING(aSessEntry)) )
                {
                        INCOMING_MESSAGEQ->RemoveMsgEventEntry(DIA_SE_SINDX(aSessEntry));       
                DT_ERR(("Session Queue is empty , -RemoveMsgEventEntry-"));
                }*/

                //SESSION_TABLE->ModifyEntry(aSessEntry, (ITS_OCTET *)sessionId,strlen((const char*)sessionId));  
                if(NULL != lEvent)
                {
                   lEvent->src = DIA_NET_INST;
                   int dest = DIASTACK_TQ_INST;
                   dest = DiaUtils::GetStackTQInst((const char*)sessionId);
                    retVal=DiaUtils::PutEventReference(dest, lEvent);
                    delete lEvent;
                    DT_DBG(("PutEventReference Return Val = %d",retVal));
                }
                else
                {
                    DT_ERR(("Enevt is Null , Could not Repost "));
                }
        DT_DBG(("LEAVE RepostPendingMessageOfSession  Ret-Val = %d",retVal));
        return retVal;
}

ITS_INT DiaMsgRouter::RemoveMsgQEventEntry(ITS_UINT sesIndex)
{
   diaInMsgQ->RemoveMsgEventEntry(sesIndex);
}

int
DiaMsgRouter::UpdatePeerSM(DIA_CMD *cmd, PEER_ENTRY* pEntry,
                           ITS_UINT evtType, ITS_HANDLE trHandle,
                           ITS_EVENT *event)
{
    int ret;
    PEER_STATE_CTXT ctxt;
    PEER_STATE_CTXT *p = &ctxt;

    DT_DBG(("UpdatePeerSM::"));

    if (pEntry == NULL)
    {
        return (!ITS_SUCCESS);
    }
    MUTEX_AcquireMutex(&DIA_PE_MUX(pEntry));

    DIA_PE_HANDLE(pEntry)   = trHandle;

    DIA_PEER_ST_EVT_TYPE(p) = evtType;
    DIA_PEER_ST_ENTRY(p)    = pEntry;
    DIA_PEER_ST_CURR_CMD(p) = cmd;


    if ((ret = DIA_PE_FSM(pEntry)->SubmitToSM(p, event)) != ITS_SUCCESS)
    {
        DT_ERR(("SubmitToSM: Error ret = %d", ret));
    }

    /**
     *Releasing the Mutex after SubmitToSM is called as this operation should be
     * exclusive and atomic before any other thread tries to change the state
     * of state machine. This is fix for issues no.1,4,6 and 8 raised by 
     * Dhiranand during the validation of bcgi ticket 1807. 
     */
    MUTEX_ReleaseMutex(&DIA_PE_MUX(pEntry));
    return ret;
}

int
DiaMsgRouter::UpdatePeerStateMachine(DIA_BASE_CMD *cmd, PEER_ENTRY* pEntry,
                                     ITS_UINT evtType, ITS_HANDLE trHandle,
                                     ITS_EVENT *event)
{
    int ret;
    PEER_STATE_CTXT ctxt;
    PEER_STATE_CTXT *p = &ctxt;

    DT_DBG(("UpdatePeerStateMachine::"));

    if (pEntry == NULL)
    {
        return (!ITS_SUCCESS);
    }
/*
 * Commenting Due to performance issues, may be it is not required for down
 * stream handling
 */
#if 0
    MUTEX_AcquireMutex(&DIA_PE_MUX(pEntry));
#endif

    DIA_PE_HANDLE(pEntry)   = trHandle;

    DIA_PEER_ST_EVT_TYPE(p) = evtType;
    DIA_PEER_ST_ENTRY(p)    = pEntry;
    DIA_PEER_ST_CURR_CMD(p) = (DIA_CMD*)cmd;


    if ((ret = DIA_PE_FSM(pEntry)->SubmitToSM(p, event)) != ITS_SUCCESS)
    {
        DT_ERR(("SubmitToSM: Error ret = %d", ret));
    }
    /**
     *Releasing the Mutex after SubmitToSM is called as this operation should be
     * exclusive and atomic before any other thread tries to change the state
     * of state machine. This is fix for issues no.1,4,6 and 8 raised by
     * Dhiranand during the validation of bcgi ticket 1807.
     */
#if 0
    MUTEX_ReleaseMutex(&DIA_PE_MUX(pEntry));
#endif

    return ret;
}

int
DiaMsgRouter::SendToPeer(ITS_USHORT inst, ITS_EVENT *cEvt)
{
    int ret = ITS_SUCCESS;
    DT_DBG(("SendToPeer::"));

    PEER_ENTRY *pEntry = NULL;
    ITS_OCTET *msg = &cEvt->data[sizeof(ITS_USHORT)];
    ITS_OCTET cmdFlag = msg[4];
    bool isRequestMsg;
    
    if (trTable[inst] != NULL)
    {
        if (cEvt->len)
        {
            ret = trTable[inst]->WriteData(cEvt->data, cEvt->len);

            if (ret == cEvt->len)
            {

                DiaSocketTransport *tr = trTable[inst];
                pEntry = tr->GetPeer();
                if(REQUEST_BIT_SET(cmdFlag))
                {
                    DIA_INC_PEER_TOTAL_REQUEST_SENT(pEntry);
                }
                else
                {
                    DIA_INC_PEER_TOTAL_RESPONSE_SENT(pEntry);
                }
                return (ITS_SUCCESS);
            }
        }
    }

    DIA_Alarm(15101, __FILE__, __LINE__, "Transport = %d", inst);

    return (ITS_ESENDFAIL);
}

int
DiaMsgRouter::SendToPeer(ITS_HANDLE handle, ITS_OCTET *buff, int len)
{

    PEER_ENTRY *pEntry = NULL;
    ITS_OCTET cmdFlag = buff[4];
    bool isRequestMsg;
    
    DT_DBG(("SendToPeer::"));
    
    try
    {
        if (handle != NULL)
        {
            if (((DiaSocketTransport *)handle)->WriteData(buff, len)
                 != ITS_SUCCESS)
            {
                DT_ERR(("Send::WriteEvent::Failure error no: [%d] [%s]", errno, strerror(errno)));
                return !ITS_SUCCESS;
            }
            else
            {
                pEntry = ((PEER_ENTRY *)(((DiaSocketTransport *)handle)->GetPeer()));
                if(REQUEST_BIT_SET(cmdFlag))
                {
                    DIA_INC_PEER_TOTAL_REQUEST_SENT(pEntry);
                }
                else
                {
                    DIA_INC_PEER_TOTAL_RESPONSE_SENT(pEntry);
                }
            }
        }
        else
        {
            DT_ERR(("Send::Invalid Peer Transport"));
            return !ITS_SUCCESS;
        }
    }
    catch(...)
    {
        DT_ERR(("Send::Invalid Handle"));
        return !ITS_SUCCESS;
    }

    return (ITS_SUCCESS);
}

static int
BuildStackMsgToApp(ITS_OCTET mType, ITS_UINT sessIndex,
                   ITS_UINT appId, ITS_OCTET* payload,
                   ITS_USHORT payloadLen,
                   ITS_OCTET* data, ITS_USHORT& msgLen)
{

    int index = 0;

    /* Set Msg Type */
    data[index++] = mType;

    /* Set Session Index */
    memcpy(&data[index], &sessIndex, sizeof(ITS_UINT));
    index += sizeof(ITS_UINT);

    /* Set Application Id */
    memcpy(&data[index], &appId, sizeof(ITS_UINT));
    index += sizeof(ITS_UINT);

     /* Now copy in the data received */
    memcpy(&data[index], &payload[0], payloadLen);
    index += payloadLen;

    msgLen = index;

    return (ITS_SUCCESS);

}

int
DiaMsgRouter::SendCmdToPeer(ITS_USHORT inst, DIA_HDR *hdr, DIA_CMD *cmd,
                            ITS_UINT evtType,bool errFlag)
{
    int ret, len = 0;
    DiaSocketTransport *tr = NULL;
    PEER_ENTRY *peer = NULL;
    ITS_EVENT evt;
    DIA_GEN_CMD *msg = (DIA_GEN_CMD *)cmd;

    /*
     * Redundancy::Send message to peer if the node is active only
     */ 
    ITSDiaConfig* cfg = &itsDiaConfig;
    ITS_NODE_STATE state;
    if (hdr == NULL || cmd == NULL)
    {
        DT_ERR(("Invalid Hdr or Command"));
        return (ITS_ESENDFAIL);
    }

    if (cfg->IsMsgRedundancyEnabled() &&
        (ITS_GetNodeState(&state) == ITS_SUCCESS) &&
        state != ITS_STATE_PRIMARY && cmd->getCommandCode() != DIA_MSG_DW)
    {
        //back-up redudant node doesn't allow any application message to be 
        //sent to peer. Device watch dog message should be allowed
        return DIA_SUCCESS;
    }

    tr = trTable[inst];
    if (tr == NULL)
    {
       DT_ERR(("Invalid transport"));
       return (ITS_EBADTRANSPORT);
    }
    peer = tr->GetPeer();

    if (peer == NULL)
    {
        DT_ERR(("Peer not found for transport"));
        return (ITS_ENOTFOUND);
    }

    CommandImplDerived& ImplDer = (CommandImplDerived&)cmd->getImpl();
    ITS_EVENT* userEvent = (ITS_EVENT*)ImplDer.getUserData();
    if (userEvent)
    {
       //already encoded, only if redundancy enabled
       evt.data = &userEvent->data[1+sizeof(ITS_ULONG)+2*sizeof(ITS_UINT)];
       evt.len  = userEvent->len - 2*sizeof(ITS_UINT)
                         - sizeof(ITS_ULONG) - 1;
       unsigned char buff[4];        
       DIA_SET_INT(buff, hdr->hh);
       memcpy(&evt.data[12], buff, 4);        
       DIA_SET_INT(buff, hdr->ee);
       memcpy(&evt.data[16], buff, 4);


    }
    else
    {
        DT_DBG(("Endcoding the message"));
        //Warning Fix - suggest parentheses around assignment used as truth value
        if ((ret = DiaUtils::EncodeMsg(cmd, &evt.data, len)) != ITS_SUCCESS)
        {
           DT_ERR(("Encode Failure"));

           return (ITS_ESENDFAIL);
        }
        evt.len = len;
    }

    if (itsDiaConfig.IsHexDumpEnabled()) 
    {
        printf("\nMessage to Peer FSM :%d\n",evt.len);
        for (int i=0;i<evt.len;i++)
        {
            if ((i + 1) % 8 == 0) printf("\n");
            printf("0x%02x, ",evt.data[i]);
        }
        printf("\n");
    }
    
    /* TODO: Verify the PeerInformation is correct */
    if ((ret = DiaMsgRouter::UpdatePeerSM(cmd, peer,
                                          evtType,
                                          tr, &evt)) != ITS_SUCCESS)
    {
        DT_ERR(("Failed to Handle Message in Peer SM = %d", ret));
    }
    /*
     * Add request message pointer to pending-Q if enabled.
     * Dont add entry if the request message is DWR.
     */

    if (msg->isRequest() && msg->getSessionId()
					&& DIA_PE_PENDING_Q(peer) )
	{

		DIA_TIMER_CTXT timerCtxt;

		timerCtxt.timerType = RETRMISSION_TIMER;
		timerCtxt.data.retransInfo.peer = peer;
		timerCtxt.data.retransInfo.hopid = msg->getHeader().hh;


		ITS_SERIAL retransmissionTimer = TIMERS_StartTimer(DIASTACK_TQ_INST,
						DIA_PE_EXPIRY_TIME_VAL(peer),
						&timerCtxt,
						sizeof(DIA_TIMER_CTXT));
		DT_DBG(("Add to Pending Queue Hop-by-Hop = %d", msg->getHeader().hh));
		if (DIA_PE_PENDING_Q(peer)->InsertEntry(msg,retransmissionTimer) != ITS_SUCCESS)
		{   
				DT_ERR(("Failed to Add to the Pending Queue"));
				TIMERS_CancelTimer(retransmissionTimer);
		}
	}
	if(errFlag || DIA_MSG_ST  == cmd->getCommandCode())
	{
			if(evt.data)
	{
		free((char*)evt.data);
		evt.data = NULL;
	}
    }
    return ret;
}

int
DiaMsgRouter::SendCmdToPeer(ITS_USHORT inst, DIA_HDR *hdr, DIA_BASE_CMD *cmd, 
                            ITS_UINT evtType)
{
    int ret =0, len = 0, dtfRet=0;
    bool msgType = false;
    DiaSocketTransport *tr = NULL;
    PEER_ENTRY *peer = NULL;
    ITS_EVENT evt;
    DIA_BASE_CMD *msg = (DIA_BASE_CMD *)cmd;
    DIA_BASE_CMD* outMsg = NULL;
    std::string sessionId;
    DT_DBG(("In Dictionary Id is %d", msg->GetDictId()));

    /*
     * Redundancy::Send message to peer if the node is active only
     */ 
    ITSDiaConfig* cfg = &itsDiaConfig;
    ITS_NODE_STATE state;
    if (hdr == NULL || cmd == NULL)
    {
        DT_ERR(("Invalid Hdr or Command")); // removed previous to avoid crash
        return (ITS_ESENDFAIL);
    }

    tr = trTable[inst];
    if (tr == NULL)
    {
       DT_ERR(("Invalid transport.Inst id=%u",inst));
       DIA_INC_INTERFACE_INVALID_MSG_COUNT(cmd->GetDictId(),cmd->getCommandCode());
       return (ITS_EBADTRANSPORT);
    }
    peer = tr->GetPeer();

    if (peer == NULL)
    {
        DT_ERR(("Peer not found for transport"));
        return (ITS_ENOTFOUND);
    }

    if (cfg->IsMsgRedundancyEnabled() &&
        (ITS_GetNodeState(&state) == ITS_SUCCESS) &&
        state != ITS_STATE_PRIMARY && cmd->getCommandCode() != DIA_MSG_DW)
    {
        //back-up redudant node doesn't allow any application message to be
        //sent to peer. Device watch dog message should be allowed
        return DIA_SUCCESS;
    }

    /*DTF Changes*/
    if(cfg->IsDTFEnabled())
    {
        DT_DBG(("cfg->IsDTFEnabled() is %d", cfg->IsDTFEnabled()));
        DT_DBG(("Calling CheckAndInvokeTramsform"));
     
        /*Fetch DictId from Peer Entry Table*/
        ITS_UINT dictId = DiaStackClass::GetDtf().getDictIdForAppId(hdr->appId,
        DiaStackClass::GetDictionaryTable(),peer->dictId);

	    DT_DBG(("outdictId is %d", dictId));
        /*DTF::Check and Invoke Transform*/
        dtfRet = DiaStackClass::GetDtf().CheckAndInvokeTransform(*msg, dictId, &outMsg);
        DT_DBG(("GetDtf().CheckAndInvokeTransform is %d", dtfRet));

        /*TODO: Need to map exceptions to respective Diameter Error Code*/
        if((dtfRet==TRANSFORM_FAILURE) || (dtfRet==TRANSFORM_INVALID_IN_MSG) || (dtfRet==TRANSFORM_DECODE_ERR))
        {
            DT_ERR(("DTF Transformation failure: Setting Diameter Error Code"));
            dtfRet = ITS_DIA_MISSING_AVP;
        }

        /*Error Handling from DTF*/
        if ((dtfRet == ITS_SUCCESS) && outMsg)
        {
            DT_DBG(("DTF Transformation is Successful"));
	    outMsg->getHeader().hh= hdr->hh;
	    outMsg->getHeader().ee= hdr->ee;
            msg = outMsg;
            msgType = true;
            DT_DBG(("messageType is OUTMSG: msgType is %d", msgType));
        }
        else if(dtfRet == TRANSFORM_NOT_DONE )
        {
            /*Nothing To Do because msg will be an INMSG*/
            DT_WRN(("DTF Transformation not required!"));
        }
		else if (dtfRet == TRANSFORM_PLUGIN_NOT_FOUND)
		{
			//Transformation did not happen, hence send INMSG
			DT_ERR(("Transformation not done since plugin is not available.Forwarding the original message."));
		}
        else
        {
            DT_ERR(("DiaMsgRouter::DTF Failure"));
            SESSION_ENTRY *e = NULL;
            if (msg->getSessionId())
            {
                sessionId = msg->getSessionId()->value();
            }
            if (SESSION_TABLE->FindEntry(e,
                        (ITS_OCTET *)sessionId.c_str(),
                        (sessionId.length())) == ITS_SUCCESS)
            {
                DT_DBG(("DiaMsgRouter::Session Entry Found"));
                DT_DBG(("peerInst %d sessionIdx %d", e->peerInst, e->sessIndx));

            }

            /* Send Error Response to peer back if failed to decode*/
            ret = DiaErrHandler::HandleError(e->peerInst, msg, SEND_ERROR_TO_PEER, dtfRet);

            if (outMsg)
            {
                delete outMsg;
                outMsg = NULL;
            }

            return (ret);
        }
    }

    /* This SendCmdToPeer is called only when peer is in open state */
    /* So if peer is not in open state, return error. */
    if ((DIA_PE_STATE(peer) == PEER_ST_I_OPEN)||
        (DIA_PE_STATE(peer) == PEER_ST_R_OPEN))
    {
        //CommandImplDerived& ImplDer = (CommandImplDerived&)cmd->getImpl();
        //ITS_EVENT* userEvent = (ITS_EVENT*)ImplDer.getUserData();
        ITS_EVENT* userEvent = (ITS_EVENT*)msg->getUserData();
        if (userEvent && userEvent->len)
        {
           DT_DBG(("DIAMSGROUTER:: Encoding done through userEvent"));
           //already encoded, only if redundancy enabled
           evt.data = &userEvent->data[1+sizeof(ITS_ULONG)+2*sizeof(ITS_UINT)];
           evt.len  = userEvent->len - 2*sizeof(ITS_UINT)
                         - sizeof(ITS_ULONG) - 1;
           unsigned char buff[4];        
           DIA_SET_INT(buff, hdr->hh);
           memcpy(&evt.data[12], buff, 4);        
           DIA_SET_INT(buff, hdr->ee);
           memcpy(&evt.data[16], buff, 4);
        }
        else
        {
            if (msg->getEncodedBuf() != NULL)
            {
                DT_DBG(("DIAMSGROUTER:: Encoding done through INMSG GetEncodedBuf"));
                evt.data = (ITS_OCTET*) msg->getEncodedBuf();
                evt.len = msg->getEncodedBufLen();
                unsigned char buff[4];
                DIA_SET_INT(buff, hdr->hh);
                memcpy(&evt.data[12], buff, 4);
                DIA_SET_INT(buff, hdr->ee);
                memcpy(&evt.data[16], buff, 4);
            
                Dia_Flags flags = hdr->flags;
                unsigned char ucFlags = 0;

                if (hdr->flags.r == 1)
                {
                    ucFlags = SET_REQUEST_BIT(ucFlags);
                    if (hdr->flags.t == 1)
                    {
                        ucFlags = SET_RETRANSMIT_BIT(ucFlags);
                    }
                }

                if(hdr->flags.p == 1)
                {
                    ucFlags = SET_PROXY_BIT(ucFlags);
                }

                if (hdr->flags.e == 1)
                {
                    ucFlags = SET_ERROR_BIT(ucFlags);
                }
                evt.data[4] = ucFlags;
            }
            else
            {
                DT_ERR(("SendCmdToPeer:: Failed"));
                return (ITS_ESENDFAIL);
            }
        }

        if (itsDiaConfig.IsHexDumpEnabled()) 
        {
            printf("\nMessage to Peer FSM :%d\n",evt.len);
            for (int i=0;i<evt.len;i++)
            {
                if ((i + 1) % 8 == 0) printf("\n");
                printf("0x%02x, ",evt.data[i]);
            }
            printf("\n");
        }

        /* TODO: Verify the PeerInformation is correct */
        if ((ret = DiaMsgRouter::UpdatePeerStateMachine(cmd, peer,
                                          evtType,
                                          tr, &evt)) != ITS_SUCCESS)
        {
            DT_ERR(("Failed to Handle Message in Peer SM = %d", ret));
        }
        else
        {
            DiaTracer::LogProtoMsg(msg, peer);
            if(cmd->isRequest())
            {
                DIA_INC_INTERFACE_TOTAL_REQUEST_SENT(cmd->GetDictId(),cmd->getCommandCode());
            }
            else
            {
                DIA_INC_INTERFACE_TOTAL_RESPONSE_SENT(cmd->GetDictId(),cmd->getCommandCode());
            }
        } 

        /*
         * Add request message pointer to pending-Q if enabled.
         * Dont add entry if the request message is DWR.
         */
        if (msg->isRequest() && msg->getSessionId() 
            && DIA_PE_PENDING_Q(peer) )
		{
				DIA_TIMER_CTXT timerCtxt;

				timerCtxt.timerType = RETRMISSION_TIMER;
				timerCtxt.data.retransInfo.peer = peer;
				timerCtxt.data.retransInfo.hopid = msg->getHeader().hh;


				ITS_SERIAL retransmissionTimer = TIMERS_StartTimer(DIASTACK_TQ_INST,
                                DIA_PE_EXPIRY_TIME_VAL(peer),
								&timerCtxt,
								sizeof(DIA_TIMER_CTXT));
				DT_DBG(("Add to Pending Queue Hop-by-Hop = %d", msg->getHeader().hh));
				if (DIA_PE_PENDING_Q(peer)->InsertEntry(msg,retransmissionTimer) != ITS_SUCCESS)
				{   
						DT_ERR(("Failed to Add to the Pending Queue"));
						TIMERS_CancelTimer(retransmissionTimer);
				}
		}

        /*
         * In BaseCommand destructor it is already taken care
         */
#if 0
    if (userEvent == NULL)
    {
       /* To avoid double delete of buff, set encodedBuf to NULL */
       if (cmd)
       {
           cmd->setEncodedBuf(NULL);
       }

       delete [] evt.data;
       evt.data = NULL;
    }
#endif
        /* DTF Changes: Delete OUT message, IN msg deleted in 
         * DiaDownStreamMsgHandler::HandleMessage */
        if(outMsg) {
            delete outMsg;
            outMsg = NULL;
        }

        return ret;
    }
    else
    {
        DT_ERR(("Peer not in open state"));
        return (ITS_ENOTFOUND);
    }
}

int 
DiaMsgRouter::SendMsgToApp(ITS_UINT msgType, ITS_UINT sessIndx,
                           ITS_UINT appId, ITS_OCTET *payload,
                           ITS_UINT payloadLen, ITS_UINT clientId)
{
    ITS_USHORT dest;
    ITS_HDR hdr;
    ITS_EVENT ev;
    int index = 0;
    int msgIdx = 0;

    if (itsDiaConfig.GetDccaFeature() != NULL)
    {
        if (msgType == ITS_DIA_MSG_TYPE_IND)
        {
            ITS_UINT indFromStack = payload[0];
            ITS_OCTET* sessionId = (ITS_OCTET*) &payload[1];
            if (DCCAAccessIndFp(indFromStack, sessionId, appId, 0) != ITS_SUCCESS)
            {
                return DIA_FAILURE;
            }
        }
        else if (msgType == ITS_DIA_MSG_TYPE_IND_WITH_DATA)
        {
            DIA_BASE_CMD *msg = NULL;
            DiaUtils::GetCmdFromData(&msg, &payload[0]);
            ITS_INT ret = DCCAAccessFp(msg, sessIndx, 1, appId);

            if (ret == DCCA_RELEASE_SESSION_IND)
            {
                const char* sessId = msg->getSessionId()->value().c_str();
                Event remev(DIA_APP_REM_SESS_INST, strlen(sessId) + 1,
                                                 (ITS_OCTET *)sessId);
                if (itsDiaConfig.IsMsgRedundancyEnabled())
                {
                    remev.SetSource(DIA_GCS_APP_REM_SESS_INST);
                }
                int dest = DIASTACK_TQ_INST;
                dest = DiaUtils::GetStackTQInst(sessId);
                its::Transport::PutEvent(dest, remev);
            }
        }
    }
    //give message to app if the node is active only
    ITSDiaConfig* cfg = &itsDiaConfig;
    ITS_NODE_STATE state;
    if (cfg->IsMsgRedundancyEnabled() &&
       (ITS_GetNodeState(&state) == ITS_SUCCESS) &&
        state != ITS_STATE_PRIMARY)
    {
        if (msgType == ITS_DIA_MSG_TYPE_IND_WITH_DATA)
        {
            DIA_BASE_CMD *msg = NULL;
            DiaUtils::GetCmdFromData(&msg, &payload[0]);
            if(msg)
            {
                delete msg;
                msg = NULL;
            }
        }
        return DIA_SUCCESS;
    }

    if (clientId)
    {
       ITS_EVENT_INIT(&ev, ITS_DIA_SRC, ITS_DIA_HDR_SIZE + payloadLen + sizeof(ITS_UINT));
    }
    else
    {
       ITS_EVENT_INIT(&ev, ITS_DIA_SRC, ITS_DIA_HDR_SIZE + payloadLen);
    }

    memset(&hdr, 0, sizeof(ITS_HDR));

    DT_DBG(("SendMsgToApp::"));

    /* Set Msg Type */
    ev.data[index++] = msgType;

    /* Set Session Index */
    DIA_SET_INT(&ev.data[index], sessIndx);
    index += sizeof(ITS_UINT);

    /* Set Application Id */
    DIA_SET_INT(&ev.data[index], appId);
    index += sizeof(ITS_UINT);

     /* Now copy in the data received */
    if (payloadLen)
    {
        memcpy(&ev.data[index], payload, payloadLen);
        msgIdx = index;
        index += payloadLen;

        /* Common place to update all indication stats */
        if (msgType == ITS_DIA_MSG_TYPE_IND)
        {
            UPDATE_DIA_STATS_INDC(payload[0]);
        }
    }

    if (clientId)
    {
        DIA_SET_INT(&ev.data[index],clientId);
        index += sizeof(ITS_UINT);
    }

    hdr.type = ITS_DIAMETER;
    hdr.context.appId = appId;

    DT_DBG(("SendMessageToApp:: AppId = %u, SessionIndex = %d",
             hdr.context.appId, sessIndx));

    if (itsDiaConfig.IsHexDumpEnabled()) 
    {
        printf("\nMessage to Application event len:%d\n",ev.len);
        for (int i=0;i<index;i++)
        {
            if ((i + 1) % 8 == 0) printf("\n");
            printf("0x%02x, ",ev.data[i]);
        }
        printf("\n");
    }
    
    if (itsDiaConfig.IsDistScenario())
    {
       /* It should be same as declared in IDS */
        dest = ITS_MAB_SRC;
 
        /* If Callback is registered from IDS No need of PutEvent */
        if (IDSMsgProcessCallBack != NULL)
        {
            IDSMsgProcessCallBack(&ev);
            ITS_EVENT_TERM(&ev);
            return DIA_SUCCESS;
        }
    }
    else
    {
        dest = ROUTE_SelectApplication(&hdr, &ev, ITS_TRUE);
    }

    if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
    {
        if ( (dest != ITS_MAB_SRC) && (msgType == ITS_DIA_MSG_TYPE_IND_WITH_DATA))
        {
            DIA_BASE_CMD *msg = NULL;
            DiaUtils::GetCmdFromData(&msg, &ev.data[msgIdx]);

            //converting from base cmd to generic command - for static setup only
            // Base gen cmd might have been already set for session tracing
            DIA_GEN_CMD* gCmd = msg->GetBaseGenCommand();
            SESSION_ENTRY *ent = NULL;
            if (gCmd == NULL)
            {
                ITS_OCTET* sessionId = (ITS_OCTET*) msg->getSessionId()->value().c_str();

                SESSION_TABLE->FindEntry(ent,  (ITS_OCTET *)sessionId,
                        strlen((const char*)sessionId));
                try
                {
                    gCmd = new DIA_GEN_CMD((const ITS_OCTET*)msg->getEncodedBuf(),
                                                        msg->getEncodedBufLen());
                }
                catch (diameter::CodecExceptionToApp& e) 
                {   
                    //fixing Big parameter passing by value
                    DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                            e.name() ,e.what()));
                    if(ent != NULL)
                    {
                        if (DiaMsgRouter::SendIndication(ent, NULL, (char*)sessionId, MANDATORY_AVP_MISSING_IND_FROM_STACK)
                                != ITS_SUCCESS)
                        {
                            DT_ERR(("Failed To send Indication to application"));
                        }
                    }
                    return e.errcode();
                }
                catch (...)
                {   
                    DT_ERR(("Unknown Exception Caught"));
                    return DIA_FAILURE;
                } 
                msg->SetBaseGenCommand(gCmd);
            }
            DT_DBG(("DTF::SendMessageToApp:: BaseGenCommand %x dict id =%d",gCmd, msg->GetDictId()));

            //copy the new generic command pointer
            memcpy(&ev.data[msgIdx], &msg, payloadLen);
        }

        if (its::Transport::PutEvent(dest, &ev) == ITS_SUCCESS)
        {
            DT_DBG(("DiaStack: Sent Message to Application = %d\n", dest));
            return DIA_SUCCESS;
        }
    }
    else
    {
        DT_ERR(("Incoming - No Route to Application\n"));
    }

    /* fix the memory leak ( fix by Yogesh)*/
    ITS_EVENT_TERM(&ev);

    return DIA_FAILURE;
}

int DiaMsgRouter::
SendMsgToApp(SESSION_ENTRY *ctxt, ITS_EVENT *evt,
             ITS_UINT msgType)
{
    int msgIndex = 0;
    ITS_USHORT dest;
    ITS_HDR hdr;
    ITS_EVENT ev;
    int index = 0;
    ITS_USHORT trInst = ITS_GET_CTXT(evt->data);

    if (itsDiaConfig.GetDccaFeature() != NULL)
    {   
        DIA_BASE_CMD *msg = NULL;
        DiaUtils::GetCmdFromData(&msg, &evt->data[sizeof(ITS_USHORT)]);
        ITS_UINT sIdxDcca = msg->getSessionIndex();

        /* check for bcgi or normal appId */
        ITS_UINT appIdDcca = 0;
        appIdDcca = DIA_SE_APP_ID(ctxt);

        ITS_INT ret = DCCAAccessFp(msg, sIdxDcca, 1, appIdDcca);
        if (ret == DCCA_RELEASE_SESSION_IND)
        {
            const char* sessId = msg->getSessionId()->value().c_str();
            Event remev(DIA_APP_REM_SESS_INST, strlen(sessId) + 1, (ITS_OCTET *)sessId);
            if (itsDiaConfig.IsMsgRedundancyEnabled())
            {
                remev.SetSource(DIA_GCS_APP_REM_SESS_INST);
            }
            int dest = DIASTACK_TQ_INST;
            dest = DiaUtils::GetStackTQInst(sessId);
            its::Transport::PutEvent(dest, remev);
        }
        else if (ret != ITS_SUCCESS)
        {
            DT_ERR(("DCCAAccess::Failed to Deliver"));
            /* only send error response if message is request. */
            if( msg->isRequest())
            {
                ret = DiaErrHandler::HandleError(trInst, msg,
                                                 SEND_ERROR_TO_PEER,
                                                 ret);
            }

            if (msg)
               delete msg;

            return ret;
        }
    }
    //give message to app if the node is active only
    ITSDiaConfig* cfg = &itsDiaConfig;
    ITS_NODE_STATE state;
    /**
     * Fix for the whizible issue id 1305. Check added in case of
     * Cold-Standby Backup should not send message to upstream.
     */ 
    if (cfg->IsRedundancyEnabled() &&
       (ITS_GetNodeState(&state) == ITS_SUCCESS) &&
        state != ITS_STATE_PRIMARY)
    {
        DT_ERR(("SendMsgToApp::Redundancy Enabled. Node is Backup. Discarding Message..."));

        /*for backup server, command isn't delivered to the application 
        hence should be deleted here. */
        DIA_BASE_CMD *msg = NULL;
        DiaUtils::GetCmdFromData(&msg, &evt->data[sizeof(ITS_USHORT)]);
        if (msg)
        {
            delete msg;
            msg = NULL;
        }
        return DIA_SUCCESS;
    }

    ITS_OCTET *msg = &evt->data[sizeof(ITS_USHORT)];
    ITS_UINT msgLen = (evt->len - sizeof(ITS_USHORT));

    ITS_EVENT_INIT(&ev, ITS_DIA_SRC, ITS_DIA_HDR_SIZE + msgLen);
    memset(&hdr, 0, sizeof(ITS_HDR));
    DT_DBG(("SendMsgToApp::"));

    /* Set Msg Type */
    ev.data[index++] = msgType;

    /* Set Session Index */
    DIA_SET_INT(&ev.data[index], DIA_SE_SINDX(ctxt));
    index += sizeof(ITS_UINT);

    /* Set Application Id */
    DIA_SET_INT(&ev.data[index], DIA_SE_APP_ID(ctxt));
    index += sizeof(ITS_UINT);

     /* Now copy in the data received */
    memcpy(&ev.data[index], &msg[0], msgLen);
    msgIndex = index;
    index += msgLen;

    hdr.type = ITS_DIAMETER;
    hdr.context.appId = DIA_SE_APP_ID(ctxt);

    DT_DBG(("SendMessageToApp:: AppId = %d, SessionIndex = %d",
             hdr.context.appId, DIA_SE_SINDX(ctxt)));

    if (itsDiaConfig.IsHexDumpEnabled()) 
    {
        printf("\nMessage to Application event len:%d\n",ev.len);
        for (int i=0;i<index;i++)
        {
            if ((i + 1) % 8 == 0) printf("\n");
            printf("0x%02x, ",ev.data[i]);
        }
        printf("\n");
    }

    if (itsDiaConfig.IsDistScenario())
    {
       /* It should be same as declared in IDS */
        dest = ITS_MAB_SRC;
        /* If Callback is registered from IDS No need of PutEvent */
        if (IDSMsgProcessCallBack != NULL)
        {
            IDSMsgProcessCallBack(&ev);
            ITS_EVENT_TERM(&ev);
            return DIA_SUCCESS;
        }
    }
    else
    {
        dest = ROUTE_SelectApplication(&hdr, &ev, ITS_TRUE);
    }

    if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
    {
        if (dest != ITS_MAB_SRC)
        {
            DIA_BASE_CMD *msg = NULL;
            DiaUtils::GetCmdFromData(&msg, &ev.data[msgIndex]);

            /* Check if DiaMsgFlow already has BaseGenericCmd set before allocating memory*/
            if(msg && msg->GetBaseGenCommand()== NULL)
            {
                ITS_OCTET* sessionId = (ITS_OCTET*) msg->getSessionId()->value().c_str();
                DIA_GEN_CMD* gCmd = NULL;
                try
                {
                    //converting from base cmd to generic command - for static setup only
                    gCmd = new DIA_GEN_CMD((const ITS_OCTET*)msg->getEncodedBuf()
                            , msg->getEncodedBufLen());
                }
                catch (diameter::CodecExceptionToApp& e) 
                {   
                    //fixing Big parameter passing by value
                    DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                            e.name() ,e.what()));
                    if (DiaMsgRouter::SendIndication(ctxt, NULL, (char*)sessionId, MANDATORY_AVP_MISSING_IND_FROM_STACK)
                            != ITS_SUCCESS)
                    {
                        DT_ERR(("Failed To send Indication to application"));
                    }

                    return e.errcode();
                }
                catch (...)
                {   
                    DT_ERR(("Unknown Exception Caught"));
                    return DIA_FAILURE;
                } 
 
                if (gCmd->countSessionId() <= 0)
                {
                    DT_DBG(("No SessionId in BaseGenericCommand setting it from DiaMsgFlow : %s"
                                ,msg->getSessionId()->value().c_str()));
                    SessionId sessionId(msg->getSessionId()->value());
                    gCmd->addAVP(sessionId, true);
                }
                msg->SetBaseGenCommand(gCmd); 

                DT_DBG(("SendMsgToApp: Memory allocated for DIA_GEN_CMD and set to DiaMsgFlow \n"));
            }

            //copy the new generic command pointer
            memcpy(&ev.data[msgIndex], &msg, sizeof(ITS_ULONG));

        }
        if (its::Transport::PutEvent(dest, &ev) == ITS_SUCCESS)
        {
            DT_DBG(("DiaStack: Sent Message to Application = %d\n", dest));

            return DIA_SUCCESS;
        }
    }
    else
    {
        DT_ERR(("Incoming - No Route to Application\n"));
    }

    /* fix the memory leak ( fix by Yogesh)*/
    ITS_EVENT_TERM(&ev);

    return DIA_FAILURE;
}

int
DiaMsgRouter::SendPeerMsgToApp(DIA_GEN_CMD *gCmd, ITS_UINT msgType)
{
    ITS_USHORT dest;
    ITS_HDR hdr;
    ITS_EVENT ev;
    int index = 0;
    int msgIdx = 0;

    DIA_GEN_CMD* msg = new DIA_GEN_CMD(*((DIA_GEN_CMD *)gCmd)); 

    ITS_EVENT_INIT(&ev, ITS_DIA_SRC, 2*sizeof(ITS_UINT)+ sizeof (ITS_OCTET) + sizeof(ITS_ULONG));
    memset(&hdr, 0, sizeof(ITS_HDR));

    DT_DBG(("SendPeerMsgToApp::"));

    /* Set Msg Type */
    ev.data[index++] = msgType;

    /* Set Session Index , dummy session Index, not relevant for peer mesg*/
    DIA_SET_INT(&ev.data[index], 0);
    index += sizeof(ITS_UINT);

    /* Set Application Id default Base appId */
    DIA_SET_INT(&ev.data[index], msg->getApplicationId());
    index += sizeof(ITS_UINT);

     /* Now copy in the data received */
    memcpy(&ev.data[index], &msg, sizeof(ITS_ULONG));
    msgIdx = index;
    index += sizeof(ITS_ULONG);

    hdr.type = ITS_DIAMETER;

    /* Set Application Id default Base appId */
    hdr.context.appId = msg->getApplicationId();

    if (itsDiaConfig.IsHexDumpEnabled()) 
    {
        printf("\nMessage to Application event len:%d\n",ev.len);
        for (int i=0;i<index;i++)
        {
            if ((i + 1) % 8 == 0) printf("\n");
            printf("0x%02x, ",ev.data[i]);
        }
        printf("\n");
    }
    
    if (itsDiaConfig.IsDistScenario())
    {
       /* It should be same as declared in IDS */
        dest = ITS_MAB_SRC;

        //distributed setup - convert to baseCommad and send
        DIA_BASE_CMD* bCmd = new DIA_BASE_CMD(msg);
        memcpy(&ev.data[msgIdx], &bCmd, sizeof(ITS_ULONG));
        //delete the old msg, not used any more
        delete msg;

        /* If Callback is registered from IDS No need of PutEvent */
        if (IDSMsgProcessCallBack != NULL)
        {
            IDSMsgProcessCallBack(&ev);
            ITS_EVENT_TERM(&ev);
            return DIA_SUCCESS;
        }

    }
    else
    {
        dest = ROUTE_SelectApplication(&hdr, &ev, ITS_TRUE);
    }

    if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
    {
        if (its::Transport::PutEvent(dest, &ev) == ITS_SUCCESS)
        {
            DT_DBG(("DiaStack: Sent Message to Application = %d\n", dest));

            return DIA_SUCCESS;
        }
    }
    else
    {
        DT_ERR(("Incoming - No Route to Application\n"));
    }

    /* fix the memory leak ( fix by Yogesh)*/
    ITS_EVENT_TERM(&ev);

    return DIA_FAILURE;
}

int
DiaMsgRouter::SendPeerMsgToApp(DIA_BASE_CMD *gCmd, ITS_UINT msgType)
{
    ITS_USHORT dest;
    ITS_HDR hdr;
    ITS_EVENT ev;
    int index = 0;
    int msgIdx = 0;

    DIA_BASE_CMD* msg = new DIA_BASE_CMD(*gCmd);

    ITS_EVENT_INIT(&ev, ITS_DIA_SRC, 2*sizeof(ITS_UINT)+ sizeof (ITS_OCTET) + sizeof(ITS_ULONG));
    memset(&hdr, 0, sizeof(ITS_HDR));

    DT_DBG(("SendPeerMsgToApp::"));

    /* Set Msg Type */
    ev.data[index++] = msgType;

    /* Set Session Index , dummy session Index, not relevant for peer mesg*/
    DIA_SET_INT(&ev.data[index], 0);
    index += sizeof(ITS_UINT);

    /* Set Application Id default Base appId */
    DIA_SET_INT(&ev.data[index], msg->getApplicationId());
    index += sizeof(ITS_UINT);

     /* Now copy in the data received */
    memcpy(&ev.data[index], &msg, sizeof(ITS_ULONG));
    msgIdx = index;
    index += sizeof(ITS_ULONG);

    hdr.type = ITS_DIAMETER;

    /* Set Application Id default Base appId */
    hdr.context.appId = msg->getApplicationId();

    if (itsDiaConfig.IsHexDumpEnabled())
    {
        printf("\nMessage to Application event len:%d\n",ev.len);
        for (int i=0;i<index;i++)
        {
            if ((i + 1) % 8 == 0) printf("\n");
            printf("0x%02x, ",ev.data[i]);
        }
        printf("\n");
    }

    if (itsDiaConfig.IsDistScenario())
    {
       /* It should be same as declared in IDS */
        dest = ITS_MAB_SRC;

        //distributed setup - convert to baseCommad and send
        DIA_BASE_CMD* bCmd = new DIA_BASE_CMD(msg->GetBaseGenCommand());
        memcpy(&ev.data[msgIdx], &bCmd, sizeof(ITS_ULONG));
        //delete the old msg, not used any more
        delete msg;

        /* If Callback is registered from IDS No need of PutEvent */
        if (IDSMsgProcessCallBack != NULL)
        {
            IDSMsgProcessCallBack(&ev);
            ITS_EVENT_TERM(&ev);
            return DIA_SUCCESS;
        }

    }
    else
    {
        dest = ROUTE_SelectApplication(&hdr, &ev, ITS_TRUE);
    }

    if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
    {
        if (its::Transport::PutEvent(dest, &ev) == ITS_SUCCESS)
        {
            DT_DBG(("DiaStack: Sent Message to Application = %d\n", dest));

            return DIA_SUCCESS;
        }
    }
    else
    {
        DT_ERR(("Incoming - No Route to Application\n"));
    }

    /* fix the memory leak ( fix by Yogesh)*/
    ITS_EVENT_TERM(&ev);

    return DIA_FAILURE;
}

int
DiaMsgRouter::IsLocalRouting(DIA_BASE_CMD *&cmd, REALM_ENTRY *&rEntry)
{
    DIA_BASE_CMD *base = (DIA_BASE_CMD *)cmd;
    DIA_CER *lcer;
    const char *realm = NULL;
    rEntry = NULL;
    ITS_BOOLEAN isSelfRealm = ITS_FALSE;
    const char* localRealm=
                           itsDiaConfig.getLocalRealmName();
    DT_DBG(("IsLocalRouting"));

    if (base->getDestinationRealm() != NULL)
    {
        realm = base->getDestinationRealm()->value().c_str();

        DT_DBG(("IsLocalRouting::DestRealm = %s", realm));
        /* Fix for local routing while doing InterOP with IBM */
        /* No realm entry in realm table, but matched with origin realm */
        /* process it locally, later validation with respect to local CER*/
        /* appId will be put required only for upstream*/
        if (strcasecmp(realm, localRealm) != 0)
        {
            DT_DBG(("IsLocalRouting::DestRealm does not matches the" \
                    " local realm"));
        }
        else
        {
            DT_DBG(("IsLocalRouting::DestRealm matches the local realm"));
            isSelfRealm = ITS_TRUE;
        }
        /* Check if Destination Host Matches Local Host Identity */
        if (base->getDestinationHost() != NULL )
        {
            const char *oHost = NULL;
            const char* localHost=
                            itsDiaConfig.getLocalHostName();            
            const char* mateHost =
                            itsDiaConfig.getMateHostName();

            oHost =  base->getDestinationHost()->value().c_str();

            //Warning Fix - suggest parentheses around assignment used as truth value
            if (((!strcasecmp(realm,localRealm)) && (!strcasecmp(oHost,localHost))) ||
                ((mateHost && (strlen(mateHost) > 0) && (strlen(oHost) > 0)  && (strcasecmp(oHost, mateHost)==0))) ||
                (itsDiaConfig.IsInterWorkingMode()))
            {
                if (isSelfRealm)
                {
                    DT_DBG(("IsLocalRouting::Message for Local Consumption"));
                    return (ITS_DIA_LOCAL_HOST_MATCH);
                }
            }
            else
            {
                /**
                 * Fix for the issue 847 in whizible where if the Destination
                 * Host AVP is present and not equal to local Host or mate
                 * host then return ITS_DIA_LOCAL_HOST_MISMATCH
                 */
                DT_DBG(("IsLocalRouting: The Destination Host AVP is present" \
                        "  but not matches with the local host."));

                if(REALM_TABLE->FindEntry(realm, rEntry))
                {
                    DT_DBG(("DestRealm = %s entry exists", realm));

                }
                else if (REALM_TABLE->FindDefaultEntry(realm, rEntry))
                {
                    ITS_USHORT peerInstance = CheckDestinationPeer(rEntry, 0);
                    DT_DBG(("IsLocalRouting::Default Entry Found"));
                }
                else
                {
                    DT_ERR(("IsLocalRouting::Failed to find Realm In Realm Table"));
                }
                return (ITS_DIA_LOCAL_HOST_MISMATCH);
            }

        }
        else
        {
            DT_DBG(("The Destination-Host is not present"));
        }

        /**
         * Fix for issue 814 in whizible where if the Realm in message
         * is same as localRealm then check whether it is configured in
         * the realm Table as Relay and Proxy. If configured return
         * ITS_DIA_LOCAL_REALM_MISMATCH
         */
        if(REALM_TABLE->FindEntry(realm, rEntry))
        {
            DT_DBG(("DestRealm = %s entry exists", realm));

            if (rEntry != NULL)
            {
                if (isSelfRealm                                 &&
                    ((DIA_RE_L_ACTION(rEntry) == ITS_DIA_RELAY) ||
                    (DIA_RE_L_ACTION(rEntry) == ITS_DIA_PROXY)))
                {
                    DT_DBG(("IsLocalRouting::DestRealm LocalAction is" \
                            " Relay or Proxy for own Realm"));
                    return (ITS_DIA_LOCAL_REALM_MISMATCH);
                }
            }
        }
        else if (REALM_TABLE->FindDefaultEntry(realm, rEntry))
        {
            ITS_USHORT peerInstance = CheckDestinationPeer(rEntry, 0);
            DT_DBG(("IsLocalRouting::Default Entry Found"));
        }
        else
        {
            DT_ERR(("IsLocalRouting::Failed to find Realm In Realm Table"));
        }

        if (isSelfRealm)
        {
            DT_DBG(("IsLocalRouting:: Message for Local Consumption"));
            return (ITS_DIA_LOCAL_REALM_MATCH);

        }
        else
        {
            return (ITS_DIA_LOCAL_REALM_MISMATCH);
        }
    }
    else
    {
        /* Both the Destination-Host and Destination-Realm AVP's are
           not present
        */
        if (base->getDestinationHost() == NULL &&
            base->getDestinationRealm() == NULL && (!base->isRequest()))
        {
            DT_DBG(("IsLocalRouting::No Dest Host and Dest Realm"));
            return (ITS_DIA_LOCAL_HOST_MATCH);
        }
    }

    return (!ITS_SUCCESS);
}

/* Peer Table Based */
int
DiaMsgRouter::RequestForwarding(DIA_BASE_CMD *&cmd, SESSION_ENTRY *&sessInfo,
                                ITS_USHORT &peerInstance)
{
    int ret;
    peerInstance = 0;
    PEER_ENTRY *entry = NULL;
    const char* hostName;
    const char* realmName;
    DIA_BASE_CMD *gCmd = (DIA_BASE_CMD *)cmd;
    ITSDiaConfig* cfg = &itsDiaConfig;
    ITS_NODE_STATE state;
    REALM_ENTRY *realm = NULL;

    DT_DBG(("DiaMsgRouter::RequestForwarding"));

    if (gCmd->getDestinationHost() == NULL)
    {
        DT_DBG(("RequestForwarding: No Destination Host"));
        return (ITS_DIA_UNKNOWN_PEER);
    }

    hostName = gCmd->getDestinationHost()->value().c_str();

    if (gCmd->getDestinationRealm() == NULL)
    {
        DT_ERR(("RequestForwarding::Missing Destination Realm"));
        return (ITS_DIA_MISSING_AVP);
    }

    realmName = gCmd->getDestinationRealm()->value().c_str();

    if (PEER_TABLE->FindEntry(hostName,
                              realmName,
                              entry, peerInstance))
    {
        /* Get the peer Instanece and return if backup */
        if (cfg->IsMsgRedundancyEnabled() &&
            (ITS_GetNodeState(&state) == ITS_SUCCESS) &&
             state != ITS_STATE_PRIMARY)
        {
            // Process the message at back-up redundant node.
            // if message is multicasted.
            return ITS_SUCCESS;
        }

        DiaSocketTransport* tr = trTable[peerInstance];
        if (tr != NULL)
        {
           entry = tr->GetPeer();
           /**
            * Adding a check for peer not null.
            * (issue no 11 raised by Lakshmi during ticket
            *  1807 validation).
            */
           if (entry == NULL)
           {
               DT_ERR(("Peer not found for transport"));
               return (ITS_DIA_UNABLE_TO_DELIVER);
           }
        }
        else
        {
            DT_ERR(("Invalid transport for peer instace: %d", peerInstance));
            return (ITS_DIA_UNABLE_TO_DELIVER);
        }

        DIA_GEN_CMD *ce = DIA_PE_CE_CACHE(entry);
        if (itsDiaConfig.IsDefaultRealmRoutingEnabled()
           && ce == NULL)
        {
           return (ITS_DIA_UNKNOWN_PEER);
        }

        /**
         * Partial Fix for issue 880 in whizible. Added check if the peer is
         * advertised as relay
         */
        if(DIA_PE_IS_RELAY(entry) != true)
        {
            if ((ret = ValidateMessage(ce, gCmd)) != ITS_SUCCESS)
            {
                if (ret == ITS_DIA_APP_UNSUPPORTED)
                    ret = ITS_DIA_UNABLE_TO_DELIVER;
                DT_ERR(("Validate Request Failure...%d", ret));
                return (ret);
            }
            DT_DBG(("RequestForwarding::Validate Message Success"));
        }
        else
        {
            DT_DBG(("RequestForwarding::Peer advertised as Relay"));
        }

        DIA_HDR &hdr = (DIA_HDR&)gCmd->getHeader();

        hdr.hh = DiaUtils::GenerateHopByHopId();

        if (sessInfo && DIA_SE_AGENT_TYPE(sessInfo) != ITS_DIA_LOCAL)
        {
            /**
             * Add the Route-Record AVP and save the
             * local Hop-By-Hop Id in the sessInfo
             */
            DiaUtils::AddRouteRecordAvp(gCmd, sessInfo);
            DIA_SE_LOCAL_HH(sessInfo) = hdr.hh;
            if (DIA_SE_AGENT_TYPE(sessInfo) == ITS_DIA_RELAY)
            {
                if (itsDiaConfig.IsAdvertisedRelay())
                {
                    /* IsLocalRouting used only to get realmEntry */
                    ret = DiaMsgRouter::IsLocalRouting(cmd, realm);
                    if (realm)
                    {
                        // check whether ProxyInfo AVP Flag is
                        // true in realm entry
                        if (DIA_RE_PXY_INFO_ENABLED(realm))
                        {
                            DT_DBG((" Adding ProxyInfo AVP for relay"));
                            DiaUtils::AddProxyInfoAvp(gCmd);
                        }
                    }
               }
               else
               {
                   DT_ERR(("Node not Advertised as Relay."));
                   return (ITS_DIA_UNABLE_TO_DELIVER);
               }
            }
        }
        else
        {
            hdr.ee = DiaUtils::GenerateEndToEndId();
            /**
             * Partial fix for issue 874, the end to end id is not saved
             * properly in the session earlier. Saving the same
             */
            DIA_SE_RX_EE(sessInfo) = hdr.ee;

            DIA_SE_RX_HH(sessInfo) = hdr.hh;
        }

        if (gCmd->getOriginStateId())
        {
            ITS_UINT &o = (ITS_UINT &)gCmd->getOriginStateId()->value();
            o = itsDiaConfig.GetOriginStateId();
        }
        else if(itsDiaConfig.GetOriginStateIdOpt())
        {
            /* TODO - adding originStateId in case of redundancy */ 
            if (!cfg->IsMsgRedundancyEnabled()) 
            {
                OriginStateId oid(itsDiaConfig.GetOriginStateId());
                diameter::String stateIdString;
                oid.Encode(stateIdString);
                if(stateIdString.length())
                {
                    gCmd->addAvpBuf(stateIdString.c_str(), stateIdString.length());
                }

                /* Make sure these deletes are removed if we move to original
                   STL string */
                stateIdString.Free();
            }
        }

        /*
           Since it is needed to insert/updated entry before calling
           SendCmdToPeer this function just returns the peerInstance after
           Insert/Updated, SendCmdToPeer is called out of this func scope
         */
#if 0
        int ret = DiaMsgRouter::SendCmdToPeer(peerInstance,
                                              &hdr,
                                              cmd);
        if (ret != ITS_SUCCESS)
        {
            DT_ERR(("Failed to send to Peer for hostname %s Realm %s ret = %d",
                    hostName, realmName, ret));
            return (ITS_DIA_UNABLE_TO_DELIVER);
        }
#endif
        peerInstance = DIA_PE_INST(entry);
    }
    else
    {
        /* DestHost & DestRealm AVP Present: But entry not found
           in Peer Table. Flag Error
        */
        DT_ERR(("No Peer for hostname %s Realm %s connected",
                  hostName, realmName));
//        DIA_Alarm(15104, __FILE__, __LINE__, "Peer =%s: Realm=%s",
//                  hostName, realmName);
        return (ITS_DIA_UNKNOWN_PEER);
        //return (ITS_DIA_UNABLE_TO_DELIVER);
    }

    return (ITS_SUCCESS);
}

ITS_USHORT CheckDestinationPeer(REALM_ENTRY *rEntry, int index)
{
    PEER_ENTRY *peer = NULL, *altPeer = NULL;
    ITS_USHORT peerInstance = UNKNOWN_PEER_INST;
    DiaSocketTransport *tr = NULL; 
    ITSDiaConfig* cfg = &itsDiaConfig;
    ITS_NODE_STATE state;

    if (DIA_RE_IS_DEFAULT(rEntry))
    {
        DT_DBG(("Default Realm Entry Found"));
        peer = DIA_RE_DEST_PEER(rEntry, 0);
    }
    else
    {
        /* Check Priority
           The Dest Specs are kept *ordered* on priority
           max-->lowest (max being 0): Ex 0 --> Highest Priority
                                          1 --> Medium
                                          2 --> Low
        */
        peer = DIA_RE_DEST_PEER(rEntry, index);
    }


    /* Get the peer Instanece and return if backup */

    if (peer && cfg->IsMsgRedundancyEnabled() &&
        (ITS_GetNodeState(&state) == ITS_SUCCESS) &&
         state != ITS_STATE_PRIMARY)
    {
        peerInstance = DIA_PE_INST(peer);
        return peerInstance;
    }

    if ((peer  != NULL) && !DIA_PEER_CHK_IS_FAILBACK_ENABLED(peer) &&
            DIA_PEER_CHK_IS_FAILOVERED(peer))
    {
        if(DIA_PE_ALT_HOST(peer)==NULL ||
                DIA_PE_ALT_REALM(peer) == NULL)
        {
            DT_DBG(("AlternateHost not configured/removed"));
            DIA_PEER_CHK_IS_FAILOVERED(peer) = false;
        }
        else if (PEER_TABLE->FindEntry(DIA_PE_ALT_HOST(peer),
                    DIA_PE_ALT_REALM(peer),
                    altPeer))
        {
            if ((DIA_PE_STATE(altPeer) == PEER_ST_I_OPEN) ||
                    (DIA_PE_STATE(altPeer) == PEER_ST_R_OPEN))
            {
                DT_DBG(("AlternateHost: PeerInstance = %d", DIA_PE_INST(altPeer)));

                ITS_USHORT inst = DIA_PE_INST(altPeer);
                tr = trTable[inst];
                if (tr != NULL)
                {
                    peerInstance = DIA_PE_INST(altPeer);
                    return peerInstance;
                }
            }
            DIA_PEER_CHK_IS_FAILOVERED(peer) = false;
        }
    }

    if (peer &&
        (DIA_PE_STATE(peer) == PEER_ST_I_OPEN ||
         DIA_PE_STATE(peer) == PEER_ST_R_OPEN))
    {
        DT_DBG(("CheckDestinationPeer: Found Peer in Open State"));

        DT_DBG(("CheckDestinationPeer: PeerInstance = %d", DIA_PE_INST(peer)));
 
        ITS_USHORT inst = DIA_PE_INST(peer);
        tr = trTable[inst];
        if (tr != NULL)
        {
           peerInstance = DIA_PE_INST(peer);
           return peerInstance;
        }
    }
    else if (peer)
    {
        DT_DBG(("CheckDestinationPeer: Peer NOT in Open State"));
    }
    else
    {
        DT_DBG(("CheckDestinationPeer: Peer NOT Found"));
    }

    return (UNKNOWN_PEER_INST);
}

int
DiaMsgRouter::StaticRouting(DIA_BASE_CMD *&cmd, SESSION_ENTRY *&sessInfo,
                             ITS_USHORT &peerInstance,
                             REALM_ENTRY *rEntry)
{
    int ret;

    DiaSocketTransport *tr = NULL;
    PEER_ENTRY *peer = NULL;
    peerInstance = UNKNOWN_PEER_INST;
    DIA_BASE_CMD *gCmd = (DIA_BASE_CMD *)cmd;
    const char* realm = NULL;
    const char* destHost = NULL;
    char peerName[256] = {'\0'};

    DT_DBG(("DiaMsgRouter::RequestRouting using static routing table"));

    if(gCmd->getDestinationHost() == NULL )
    {
        DT_DBG(("Destination Host not present.RequestRouting using static routing table not possible"));
        return (!ITS_SUCCESS);
    }

    destHost = gCmd->getDestinationHost()->value().c_str();
    realm = gCmd->getDestinationRealm()->value().c_str();

    if(realm == NULL)
    {
        DT_ERR(("Destination realm not present.RequestRouting using static routing table not possible"));
        return (!ITS_SUCCESS);
    }
    bool FoundRoute = STATIC_ROUTING_TABLE->FindPeer(realm,destHost,peerName,peerInstance,gCmd->getApplicationId());

    if(FoundRoute != ITS_SUCCESS)
    {
        DT_ERR(("Peer not configured for routing in static routing table"));
        return (!ITS_SUCCESS);
    }

    if (rEntry == NULL)
    {
        /*  Look up the RealmName from the Destination Realm AVP */ 
         REALM_TABLE->FindEntry(realm, rEntry);
    }
    
    if (rEntry != NULL && DIA_RE_L_ACTION(rEntry) == ITS_DIA_RELAY)
    {
        if (itsDiaConfig.IsAdvertisedRelay())
        {
           // check whether ProxyInfo AVP Flag is true in realm entry
           if (DIA_RE_PXY_INFO_ENABLED(rEntry))
           {
               DT_DBG(("Adding ProxyInfo AVP for relay"));
               DiaUtils::AddProxyInfoAvp(gCmd);
           }
        }
        else
        {
            DT_ERR(("Realm Configured but Node not Advertised as Relay"));
            return (!ITS_SUCCESS);
        }
    }

    if (peerInstance != UNKNOWN_PEER_INST)
    {
        DiaSocketTransport* tr = trTable[peerInstance];
        if (tr != NULL)
        {
            peer = tr->GetPeer();
            if (peer == NULL)
            {
                DT_ERR(("Peer not found for transport"));
                return (ITS_DIA_UNABLE_TO_DELIVER);
            }
            else
            {
                if(DIA_PE_IS_RELAY(peer) != true)
                {
                    DIA_GEN_CMD *ce = DIA_PE_CE_CACHE(peer);
                    if ((ret = ValidateMessage(ce, gCmd)) != ITS_SUCCESS)
                    {
                        if (ret == ITS_DIA_APP_UNSUPPORTED)
                            ret = ITS_DIA_UNABLE_TO_DELIVER;
                        DT_ERR(("Validate Request Failure...%d", ret));
                        return (ret);
                    }
                    DT_DBG(("RequestRouting::Validate Message Success"));
                }
                else
                {
                    DT_DBG(("RequestRouting::Peer advertised as Relay"));
                }
            }
        }
        else
        {
            DT_ERR(("Invalid transport"));
            return (ITS_DIA_UNABLE_TO_DELIVER);
        }
        DIA_HDR &hdr = (DIA_HDR&)gCmd->getHeader();
        hdr.hh = DiaUtils::GenerateHopByHopId();
      
        /* *
        * Generate End-To-End id only for the originator of the message
        * i.e. when the local action is local and destHost for this realm
        * is not redirect agent.
        */ 
        if (DIA_RE_L_ACTION(rEntry) == ITS_DIA_LOCAL)
        {
        
           /* *
            * Partial fix for issue 874, the end to end id is not saved
            * properly in the session earlier. Saving the same
            */
            hdr.ee = DiaUtils::GenerateEndToEndId();
            DIA_SE_RX_EE(sessInfo) = hdr.ee;
            DIA_SE_RX_HH(sessInfo) = hdr.hh;
        }
        else
        {
           /* *
            * Add the Route-Record AVP Here and save the
            * local hop-by-hop id in the sessionInfo
            */
           DiaUtils::AddRouteRecordAvp(gCmd, sessInfo);
            DIA_SE_LOCAL_HH(sessInfo) = hdr.hh;
        }

        return ITS_SUCCESS;
    }

    return (!ITS_SUCCESS);
}
 


/* Realm Table Based */
int
DiaMsgRouter::RequestRouting(DIA_BASE_CMD *&cmd, SESSION_ENTRY *&sessInfo,
                             ITS_USHORT &peerInstance,
                             REALM_ENTRY *rEntry)
{
    int ret, i = 0, j = 0;

    DiaSocketTransport *tr = NULL; 
    PEER_ENTRY *peer = NULL;
    peerInstance = UNKNOWN_PEER_INST;
    DIA_BASE_CMD *gCmd = (DIA_BASE_CMD *)cmd;
    const char* realm = NULL;

    DT_DBG(("DiaMsgRouter::RequestRouting"));

    //since it is possible that auth appid,acct id and
    // vendor app can be present only in header
    /*if (gCmd->getAuthApplicationId() == NULL &&
        gCmd->getAcctApplicationId() == NULL &&
        gCmd->getVendorSpecificApplicationId() == NULL)
    {
        return (!ITS_SUCCESS);
    }
    */
    ITS_UINT appId[3] = {gCmd->getApplicationId(), gCmd->getApplicationId(),
                        gCmd->getApplicationId()};

    DT_DBG(("Message Header AppId value = %d", appId[0]));

    if (gCmd->getAuthApplicationId())
    {
        appId[0] = gCmd->getAuthApplicationId()->value();
        DT_DBG(("Message Auth AppId AVP value = %d", appId[0]));
    }
    if (gCmd->getAcctApplicationId())
    {
        appId[1] = gCmd->getAcctApplicationId()->value();
        DT_DBG(("Message Acct AppId AVP value = %d", appId[1]));
    }
    if (gCmd->getVendorSpecificApplicationId())
    {
        if (gCmd->getVendorSpecificApplicationId()->containsAuthApplicationId())
        {
           appId[2] = gCmd->getVendorSpecificApplicationId()->getAuthApplicationId().value();
        }
        else if(gCmd->getVendorSpecificApplicationId()->containsAcctApplicationId())
        {
           appId[2] = gCmd->getVendorSpecificApplicationId()->getAcctApplicationId().value();
        }

        DT_DBG(("Message VendorSpecific AVP Auth/Acct AppId value = %d", 
                                                            appId[2]));
    }
 
    if (gCmd->getVendorId())
    {
        DT_DBG(("Message VendorId AVP value = %d", 
                       gCmd->getVendorId()->value()));
    }

    /* May have been found during check for Local Request 
     */
    if (rEntry == NULL)
    {
        /* Look up the RealmName from the Destination Realm AVP */
        if (gCmd->getDestinationRealm())
        {
            realm = gCmd->getDestinationRealm()->value().c_str();
            DT_DBG(("RealmRouting::Realm To Find = %s", realm));
            if (REALM_TABLE->FindEntry(realm, rEntry))
            {
                DT_DBG(("RealmRouting::Realm Match Found"));
            }
        }
        /* TODO: Look up the RealmName from the User-Name AVP */
    }
    /**
     * Removing earlier check for ITS_DIA_LOCAL in order to provide
     * fix for isue 844 in whizible. Checking Destination checks for 
     * Relay also.
     */
    if (rEntry != NULL)
    {
        /* Find Best Match and Check Priority
           The Dest Specs are kept *ordered* on priority
           max-->lowest (max being 0): Ex 0 --> Highest Priority
                                          1 --> Medium
                                          2 --> Low
        */
        for (i = 0; i < DIA_RE_DEST_CNT(rEntry);i++)
        {
	      if (((DIA_RE_DEST_APP_ID(rEntry, i)).appId  == appId[0]) ||
                 ((DIA_RE_DEST_APP_ID(rEntry, i)).appId  == appId[1])  ||
                 ((DIA_RE_DEST_APP_ID(rEntry, i)).appId  == appId[2]))
             {
                if (gCmd->getVendorId())
                {
                    if ((DIA_RE_DEST_APP_ID(rEntry, i)).vendorId ==
                        (gCmd->getVendorId()->value()))
                    {
                        peerInstance = CheckDestinationPeer(rEntry, i);
                        if (peerInstance != UNKNOWN_PEER_INST)
                        {
                            break;
                        }
                    }
                }
                else if ((DIA_RE_DEST_APP_ID(rEntry, i)).vendorId == 0)
                {
                    peerInstance = CheckDestinationPeer(rEntry, i);
                    if (peerInstance != UNKNOWN_PEER_INST)
                    {
                        break;
                    }
                }
            }
        }
    }

    if (peerInstance == UNKNOWN_PEER_INST)
    {
        /**
         * Before default routing check in Local Cache.
         * Return true when it set the proper Instance for Req.
         * If return false continue with default routing.
         */
        if ( DiaRedirectHandler::CheckInLocalCache( gCmd,
                                                    sessInfo,
                                                    peerInstance,
                                                    rEntry) )
        {
            return ITS_SUCCESS;
        }
 
        /* if any of the above route fails, then try for default
         * try to route the command using default route if any */
 
        DT_DBG(("RealmRouting:: Configuration values does not match for" \
                " the message."));
        DT_DBG(("RealmRouting:: Checking with Default Route"));
        if (realm && REALM_TABLE->FindDefaultEntry(realm, rEntry))
        {
            peerInstance = CheckDestinationPeer(rEntry, 0);
            DT_DBG(("RealmRouting::Default Entry Found"));
        }
    }

    if (rEntry != NULL && DIA_RE_L_ACTION(rEntry) == ITS_DIA_RELAY)
    {
        /* You are here for RELAY action*/
        /* Find Best Match and Check Priority
           The Dest Specs are kept *ordered* on priority
           max-->lowest (max being 0): Ex 0 --> Highest Priority
                                          1 --> Medium
                                          2 --> Low
        */
        if (itsDiaConfig.IsAdvertisedRelay())
        {
           // check whether ProxyInfo AVP Flag is true in realm entry
           if (DIA_RE_PXY_INFO_ENABLED(rEntry))
           {
               DT_DBG(("Adding ProxyInfo AVP for relay"));
               DiaUtils::AddProxyInfoAvp(gCmd);
           }
        }
        else
        {
            DT_ERR(("Realm Configured but Node not Advertised as Relay"));
            return (!ITS_SUCCESS);
        }
    }
    if (peerInstance != UNKNOWN_PEER_INST)
    {
        DiaSocketTransport* tr = trTable[peerInstance];
        if (tr != NULL)
        {
            peer = tr->GetPeer();
            if (peer == NULL)
            {
                DT_ERR(("Peer not found for transport"));
                return (ITS_DIA_UNABLE_TO_DELIVER);
            }
            else
            {
                /**
                 * Fix for issue 880 in whizible. Provided complete
                 * solution for AppId advertisement as agent or server.
                 */
                if(DIA_PE_IS_RELAY(peer) != true)
                {
                    DIA_GEN_CMD *ce = DIA_PE_CE_CACHE(peer);
                    if ((ret = ValidateMessage(ce, gCmd)) != ITS_SUCCESS)
                    {
                        if (ret == ITS_DIA_APP_UNSUPPORTED)
                            ret = ITS_DIA_UNABLE_TO_DELIVER;
                        DT_ERR(("Validate Request Failure...%d", ret));
                        return (ret);
                    }
                    DT_DBG(("RequestRouting::Validate Message Success"));
                }
                else
                {
                    DT_DBG(("RequestRouting::Peer advertised as Relay"));
                }
            }
        }
        else
        {
            DT_ERR(("Invalid transport"));
            return (ITS_DIA_UNABLE_TO_DELIVER);
        }
        DIA_HDR &hdr = (DIA_HDR&)gCmd->getHeader();
        hdr.hh = DiaUtils::GenerateHopByHopId();
        /**
         * Generate End-To-End id only for the originator of the message
         * i.e. when the local action is local and destHost for this realm
         * is not redirect agent.
         */
        if (DIA_RE_L_ACTION(rEntry) == ITS_DIA_LOCAL)
        {
            /**
             * Partial fix for issue 874, the end to end id is not saved
             * properly in the session earlier. Saving the same
             */
            hdr.ee = DiaUtils::GenerateEndToEndId();
            DIA_SE_RX_EE(sessInfo) = hdr.ee;
            DIA_SE_RX_HH(sessInfo) = hdr.hh;
        }
        else
        {
            /**
             * Add the Route-Record AVP Here and save the
             * local hop-by-hop id in the sessionInfo
             */
            DiaUtils::AddRouteRecordAvp(gCmd, sessInfo);
            DIA_SE_LOCAL_HH(sessInfo) = hdr.hh;
        }
        /*
           Since it is needed to insert/updated entry before calling
           SendCmdToPeer this function just returns the peerInstance after
           Insert/Updated, SendCmdToPeer is called out of this func scope
         */
#if 0
        int ret = DiaMsgRouter::SendCmdToPeer(peerInstance,
                                             &hdr,
                                             cmd);
        return ret;
#endif
        return ITS_SUCCESS;
    }
    DT_ERR(("Failed to route via RealmTable"));

    return (ITS_DIA_REALM_NOT_SERVED);
}

/* Peer Table Based */
int
DiaMsgRouter::AnswerForwarding(DIA_CMD *&cmd, ITS_EVENT *evt,
                               ITS_USHORT &peerInstance)
{
    peerInstance = 0;
    DT_DBG(("DiaMsgRouter::AnswerForwarding"));
    return (ITS_SUCCESS);
}

/* Realm Table Based */
int
DiaMsgRouter::AnswerRouting(DIA_CMD *&cmd, ITS_EVENT *evt,
                             ITS_USHORT &peerInstance)
{
    peerInstance = 0;
    DT_DBG(("DiaMsgRouter::AnswerRouting"));
    return (ITS_SUCCESS);
}

/* Retransmit the messages incase of Failover */
int
DiaMsgRouter::Failover(PEER_ENTRY *peer)
{
    int ret;
    DIA_BASE_CMD *msg = NULL;
    PEER_ENTRY *altPeer = NULL;

    DT_DBG(("DiaMsgRouter::ReTransmit"));

    /*
     * Lookup for Alternate peer
     */
    DT_DBG(("Alternate Peer for Retransmit is : %s",
                                        DIA_PE_ALT_HOST(peer)));

   DIA_Alarm(15003, __FILE__, __LINE__, 
             "Peer =%s: Realm = %s: Alt Peer =%s : Alt Realm= %s",
             DIA_PE_HOST(peer),DIA_PE_REALM(peer),DIA_PE_ALT_HOST(peer),
             DIA_PE_ALT_REALM(peer));

   if ((PEER_TABLE->FindEntry(DIA_PE_ALT_HOST(peer),
                              DIA_PE_ALT_REALM(peer),
                              altPeer ))
                              == ITS_FALSE)
    {
        DT_ERR((" Alternate Peer not found"));
        DIA_PE_PENDING_Q(peer)->CancelAllRetransmitTimerAndRemoveAllEntry();
        return (!ITS_SUCCESS);
    }

    /*
     * Fix for Issue ID 1400.
     * Check alternate peer is in OPEN state.
     */
    if ( DIA_PE_STATE(altPeer) != PEER_ST_I_OPEN &&
         DIA_PE_STATE(altPeer) != PEER_ST_R_OPEN )
    {
        DT_WRN(("Alternate Peer is Not in OPEN state"));
        DIA_PE_PENDING_Q(peer)->CancelAllRetransmitTimerAndRemoveAllEntry();
        return (!ITS_SUCCESS);
    }

    /* Actual retransmission starts from here */
    msg = DIA_PE_PENDING_Q(peer)->PopFirstEntry();

    while (msg != NULL)
    {
        if (msg->getDestinationHost() != NULL)
        {
            /* 
             * Fix for failover scenario while doing Interop With Aricent 
             * and IBM (Alt-Peer) if peername isn't in the peertable, 
             * forward it to alternate table 
             */
            const char* peerName = msg->getDestinationHost()->value().c_str();
            PEER_ENTRY* peerEntry = NULL;
            if(PEER_TABLE->FindEntry(peerName, peerEntry))
            {
                DT_ERR(("Cannot retransmit since DestinationHost AVP exists"));
                ret = DiaErrHandler::HandleError(0, msg,
                                                 LOOP_TO_APP,
                                                 ITS_DIA_UNABLE_TO_DELIVER);
            }
            else
            {
                DIA_HDR &hdr = (DIA_HDR &)msg->getHeader();
                hdr.flags.t = 1;
                //Warning Fix - suggest parentheses around assignment used as truth value
                if ((ret = DiaMsgRouter::SendCmdToPeer(altPeer->trInst, &hdr,
                                                  msg)) == ITS_SUCCESS)
                {
                   DT_DBG(("Request retransmitted to alternate Peer"));
                }
                else
                {
                   DT_ERR(("Failed to retransmit the Msg : ret = %d",ret));
                }
            }
        }
        else
        {
            DIA_HDR &hdr = (DIA_HDR &)msg->getHeader();
            hdr.flags.t = 1;
            //Warning Fix - suggest parentheses around assignment used as truth value
            if ((ret = DiaMsgRouter::SendCmdToPeer(altPeer->trInst, &hdr,
                                                  msg)) == ITS_SUCCESS)
            {
                DT_DBG(("Request retransmitted to alternate Peer"));
            }
            else
            {
                DT_ERR(("Failed to retransmit the Msg : ret = %d",ret));
            }
        }
        //msg is alrady freed in DiaMsgFlow destructor

        if (DIA_PE_PENDING_Q(peer)->IsStopFailover())
        {
            break;
        }
        msg = DIA_PE_PENDING_Q(peer)->PopFirstEntry();
    }
    return (ITS_SUCCESS);
}

/* Retransmit the messages incase of Failback */
int
DiaMsgRouter::Failback(PEER_ENTRY *peer)
{
    int ret;
    DIA_BASE_CMD *msg = NULL;

    if ((DIA_PE_STATE(peer) != PEER_ST_I_OPEN) &&
        (DIA_PE_STATE(peer) != PEER_ST_R_OPEN))
    {
		DIA_PE_PENDING_Q(peer)->CancelAllRetransmitTimerAndRemoveAllEntry();
        DT_ERR(("DiaMsgRouter::Failback: Peer NOT in Open State"));
        return (!ITS_SUCCESS);
    }

    DIA_Alarm(15004, __FILE__, __LINE__,
             "Peer =%s: Realm = %s: Alt Peer =%s : Alt Realm= %s",
             DIA_PE_HOST(peer),DIA_PE_REALM(peer),DIA_PE_ALT_HOST(peer),
             DIA_PE_ALT_REALM(peer));

    msg = DIA_PE_PENDING_Q(peer)->PopFirstEntry();

    while (msg != NULL)
    {
        DIA_HDR &hdr = (DIA_HDR &)msg->getHeader();
        hdr.flags.t = 1;

        //Warning Fix - suggest parentheses around assignment used as truth value
        if ((ret = DiaMsgRouter::SendCmdToPeer(peer->trInst, &hdr,
                                              msg)) == ITS_SUCCESS)
        {
            DT_DBG(("DiaMsgRouter::Failback: Request retransmitted" \
                    "successfully"));
        }
        else
        {
            DT_ERR(("DiaMsgRouter::Failback: Failed to retransmit the Msg"));
        }

        //msg is alrady freed in DiaMsgFlow destructor
        msg = DIA_PE_PENDING_Q(peer)->PopFirstEntry();
    }

    DIA_PE_PENDING_Q(peer)->SetStopFailover(false);

    return (ITS_SUCCESS);
}

/****************************************************************************
 *  Purpose:
 *        Checks the request message whether Route-Record AVP is present or
 *        not. If present checks whether matches with the hosts identity.
 *
 *  Input Parameters:
 *        msg : Diameter Base Generic Command.
 *
 *  Input/Output Parameters:
 *      ctxt:  Context pointer
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *        ITS_TRUE  : If Loop is detected in the Path.
 *        ITS_FALSE : If Loop NOT detected.
 *
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
ITS_BOOLEAN 
DiaMsgRouter::IsLoopDetected(DIA_BASE_CMD *&msg)
{
    ITS_BOOLEAN isLoop = ITS_FALSE;
    int rrCount = msg->countRouteRecord();

    if (rrCount == 0)
        return isLoop; 

    DIA_CER *lcer = itsDiaConfig.GetLocalCER();
    const char* orgHost = lcer->getOriginHost().value().c_str();

    for (int i = 0; i < rrCount; i++)
    {
        const char *routeRec = msg->getRouteRecord(i)->value().c_str();

        if (!strcasecmp(routeRec, orgHost))
        {
            DT_ERR(("IsLoopDetected::RouteRecord AVP contains " \
                    "Node's Identity"));
            isLoop = ITS_TRUE;
            return isLoop;
        } 
    }    
    return isLoop;
}

/****************************************************************************
 *  Purpose:
 *        Checks for the request message if the DestinationHost in the message is 
 *        is directly connected and RequestForwarding is possible.
 *
 *  Input Parameters:
 *        msg : Diameter Base Generic Command.
 *
 *  Input/Output Parameters:
 *      None.
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *        ITS_TRUE  : If RequestForwarding is possible.
 *        ITS_FALSE : If not able Forward the request.
 *
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
/* Peer Table Based */

ITS_BOOLEAN 
DiaMsgRouter::VerifyIfReqForwarding(DIA_BASE_CMD *&gCmd)
{
    ITS_USHORT peerInstance = 0;
    PEER_ENTRY *entry = NULL;
    const char* hostName;
    const char* realmName;
    ITSDiaConfig* cfg = &itsDiaConfig;
    ITS_NODE_STATE state;

    DT_DBG(("DiaMsgRouter::VerifyIfReqForwarding"));

    if (gCmd->getDestinationHost() == NULL)
    {
        DT_DBG(("VerifyIfReqForwarding: No Destination Host in Message"));
        return (ITS_FALSE);
    }

    hostName = gCmd->getDestinationHost()->value().c_str();

    if (gCmd->getDestinationRealm() == NULL)
    {
        DT_ERR(("VerifyIfReqForwarding:Missing Destination Realm Message"));
        return (ITS_FALSE);
    }

    realmName = gCmd->getDestinationRealm()->value().c_str();

    if (PEER_TABLE->FindEntry(hostName,
                              realmName,
                              entry, peerInstance))
    {
        /* Get the peer Instanece and return if backup */
        if (cfg->IsMsgRedundancyEnabled() &&
            (ITS_GetNodeState(&state) == ITS_SUCCESS) &&
             state != ITS_STATE_PRIMARY)
        {
            // Process the message at back-up redundant node.
            // if message is multicasted.
            return (ITS_FALSE);
        }
        DT_DBG(("VerifyIfReqForwarding: Peer Configured for Message"));

        if (DIA_PE_STATE(entry) == PEER_ST_I_OPEN ||
            DIA_PE_STATE(entry) == PEER_ST_R_OPEN)
        {
            DT_DBG(("VerifyIfReqForwarding:Peer in Open State"));
            return ITS_TRUE;
        }
        else
        {
            DT_DBG(("VerifyIfReqForwarding:Peer NOT in Open State"));
            return (ITS_FALSE);
        }
    }
    else
    {
        DT_DBG(("VerifyIfReqForwarding:Peer is not configured for Message"));
        return (ITS_FALSE); 
    }
    return (ITS_FALSE); 
}

ITS_INT
DiaMsgRouter::IsLocalMatchFound(DIA_BASE_CMD *&cmd)
{
    DIA_BASE_CMD *base     = (DIA_BASE_CMD *)cmd;
    const char *realm      = NULL;
    const char* localRealm = NULL;
    const char *oHost      = NULL;
    const char* localHost  = NULL;
    const char* mateHost   = NULL;

    DT_DBG(("IsLocalMatchFound"));

    localRealm = itsDiaConfig.getLocalRealmName();

    if ((base->getDestinationHost() == NULL) &&
        (base->getDestinationRealm() == NULL))
    {
            DT_DBG(("IsLocalRouting::No Dest Host and Dest Realm"));
            return (ITS_DIA_LOCAL_HOST_MATCH);
    }

    if (base->getDestinationHost()  && base->getDestinationRealm())
    {
       realm = base->getDestinationRealm()->value().c_str();

       if (strcasecmp(realm, localRealm) == 0)
       {
            localHost = itsDiaConfig.getLocalHostName();
            mateHost = itsDiaConfig.getMateHostName();

            oHost =  base->getDestinationHost()->value().c_str();

            if ((!strcasecmp(oHost,localHost)) ||
                (mateHost && strcasecmp(oHost, mateHost)==0))
            {
                DT_DBG(("IsLocalRouting::Message for Local Consumption"));
                return (ITS_DIA_LOCAL_HOST_MATCH);
            }
       }

    }
    return ITS_SUCCESS;
}

int 
DiaMsgRouter::SendIndication( SESSION_ENTRY* ent, PEER_ENTRY* peer, 
                                       char* sessionId, int indicType )
{
    /* Send Indication to Application */
    ITS_OCTET indic[MAX_INDIC_BUFF_LEN];
    memset(indic, 0, MAX_INDIC_BUFF_LEN);
    ITS_UINT indicLen = 0;
    ITS_UINT sessIndx = 0;
    ITS_UINT appId = 0;
    ITS_UINT clientId = 0;

    indic[indicLen++] = indicType;

    switch(indicType)
    {
        case TIME_OUT_IND_FROM_STACK:
        case AUTH_LIFE_TIME_OUT_IND_FROM_STACK:
        case AUTH_GRACE_TIME_OUT_IND_FROM_STACK:
        case ACCT_INTERIM_TIME_OUT_IND_FROM_STACK:
        case MSG_INVALID_IND_FROM_STACK:
             {
                 sessIndx = DIA_SE_SINDX(ent);
                 appId = DIA_SE_APP_ID(ent);
                 clientId = DIA_SE_CLIENTID(ent); 

                 int sessIdLen = strlen(sessionId);

                 if (sessIdLen > MAX_SESSION_ID_LEN)
                 {
                     sessIdLen = MAX_SESSION_ID_LEN;
                 }

                 strncpy((char*)&indic[indicLen], sessionId, sessIdLen);
                 indicLen += sessIdLen;
                 indic[indicLen++] = '\0';
             }
             break;
        case FAILOVER_IND_FROM_STACK:
        case FAILBACK_IND_FROM_STACK:
             {
                 /* Added Primary Peer Information in Indication */
                 int len = strlen(DIA_PE_HOST(peer));
                 if (len > MAX_HOST_NAME_LEN)
                 {
                     len = MAX_HOST_NAME_LEN;
                 }
                 strncpy((char*)&indic[indicLen], DIA_PE_HOST(peer), len);
                 indicLen += len;
                 indic[indicLen++] = '.';

                 len = strlen(DIA_PE_REALM(peer));
                 if (len > MAX_REALM_NAME_LEN)
                 {
                     len = MAX_REALM_NAME_LEN;
                 }
                 strncpy((char*)&indic[indicLen], DIA_PE_REALM(peer), len);
                 indicLen += len;
                 indic[indicLen++] = ';';
 
                 /* Added Alternate Peer Information in Indication */
                 len = strlen(DIA_PE_ALT_HOST(peer));
                 if (len > MAX_ALT_HOST_NAME_LEN)
                 {
                     len = MAX_ALT_HOST_NAME_LEN;
                 }
                 strncpy((char*)&indic[indicLen], DIA_PE_ALT_HOST(peer), len);
                 indicLen += len;
                 indic[indicLen++] = '.';

                 len = strlen(DIA_PE_ALT_REALM(peer));
                 if (len > MAX_ALT_REALM_NAME_LEN)
                 {
                     len = MAX_ALT_REALM_NAME_LEN;
                 }
                 strncpy((char*)&indic[indicLen], DIA_PE_ALT_REALM(peer), len);
                 indicLen += len;
                 indic[indicLen++] = '\0';
             }
             break;
        case DISCONECT_IND_FROM_STACK:
             {
                 int len = strlen(DIA_PE_HOST(peer));
                 if (len > (2*MAX_HOST_NAME_LEN))
                 {
                     len = 2*MAX_HOST_NAME_LEN;
                 }
                 strncpy((char*)&indic[indicLen], DIA_PE_HOST(peer), len);
                 indicLen += len;
                 indic[indicLen++] = '|';

                 len = strlen(DIA_PE_REALM(peer));
                 if (len > (2*MAX_REALM_NAME_LEN))
                 {
                     len = 2*MAX_REALM_NAME_LEN;
                 }
                 strncpy((char*)&indic[indicLen], DIA_PE_REALM(peer), len);
                 indicLen += len;
                 /* Added REBOOTING(0)as a disconnect cause of DISCONNECT_IND */
                 indic[indicLen++] = '|';
                 indic[indicLen++] = '0';
                 indic[indicLen++] = '\0';
             }
             break;
 
        case OVERLOAD_IND_FROM_STACK:
        case OVLD_ABATED_IND_FROM_STACK:
             {
                 sessIndx = 0;
                 appId = 0;
                 clientId = 0;
                 indic[indicLen++] = '\0';
             }
             break;
        case MANDATORY_AVP_MISSING_IND_FROM_STACK:
             {
                 if (ent != NULL)
                 {
                     sessIndx = DIA_SE_SINDX(ent);
                     appId = DIA_SE_APP_ID(ent);
                     clientId = DIA_SE_CLIENTID(ent); 
                 }

                 int sessIdLen = strlen(sessionId);

                 if (sessIdLen > MAX_SESSION_ID_LEN)
                 {
                     sessIdLen = MAX_SESSION_ID_LEN;
                 }

                 strncpy((char*)&indic[indicLen], sessionId, sessIdLen);
                 indicLen += sessIdLen;
                 indic[indicLen++] = '\0';
             }
             break;
    }

    return DiaMsgRouter::SendMsgToApp(ITS_DIA_MSG_TYPE_IND,
                               sessIndx,
                               appId,
                               indic,
                               indicLen, clientId);
}

ITS_BOOLEAN
DiaMsgRouter::IsPredectiveLoopDetected(DIA_BASE_CMD *&msg,const char * destHost)
{
    ITS_BOOLEAN isPredictiveLoop = ITS_FALSE;
    int rrCount = msg->countRouteRecord();

    if (rrCount == 0)
        return isPredictiveLoop;

    for (int i = 0; i < rrCount; i++)
    {
        const char *routeRec = msg->getRouteRecord(i)->value().c_str();

        if (!strcasecmp(routeRec, destHost))
        {
            DT_ERR(("IsPredictiveLoopDetected::RouteRecord AVP contains " \
                        "Node's Identity:%s",destHost));
            isPredictiveLoop = ITS_TRUE;
            break;
        }
    }
    return isPredictiveLoop;
}


int DiaMsgRouter::SelectAlternatePeerToRoute(const char *destHost,DIA_BASE_CMD *&cmd,
        SESSION_ENTRY *e,ITS_USHORT &peerInstance)
{
    int ret = ITS_DIA_UNABLE_TO_DELIVER;
    PEER_ENTRY * peerEntry = NULL;
    peerInstance = UNKNOWN_PEER_INST;
    PEER_TABLE->FindEntry(destHost, peerEntry );


    if(DIA_PE_ALT_HOST(peerEntry) == NULL)
    {
        DT_ERR(("No Alt peer availabe for %s", destHost));
    }
    else
    {

        PEER_ENTRY * altPeer = NULL;
        if (PEER_TABLE->FindEntry(DIA_PE_ALT_HOST(peerEntry),
                    DIA_PE_ALT_REALM(peerEntry),
                    altPeer))
        {
            if(DIA_PE_STATE(altPeer) == PEER_ST_I_OPEN||
                    DIA_PE_STATE(altPeer) == PEER_ST_R_OPEN)
            {
                DT_DBG(("AlternateHost: PeerInstance = %d", DIA_PE_INST(altPeer)));

                ITS_USHORT inst = DIA_PE_INST(altPeer);
                DiaSocketTransport* tr = trTable[inst];
                if (tr != NULL)
                {
                    PEER_ENTRY* pEntry = tr->GetPeer();
                    if(DiaMsgRouter::IsPredectiveLoopDetected(cmd,DIA_PE_HOST(pEntry)))
                    {
                        DT_ERR(("Predictive loop detected for  Alt peer %s also", DIA_PE_HOST(pEntry)));
                    }
                    else
                    {
                        //No Need add route record here as its already added
                        //in RequestRouting or StaticRouting or RequestForwrding.
                        peerInstance = DIA_PE_INST(altPeer);
                        ret = ITS_SUCCESS;
                    }
                }
            }
        }
    }

    if(ret == ITS_DIA_UNABLE_TO_DELIVER)
    {
        DiaErrHandler::HandleError(DIA_SE_PEER_INST(e), cmd,
                SEND_ERROR_TO_PEER,
                ITS_DIA_UNABLE_TO_DELIVER);
    }
    return ret;
}

int DiaMsgRouter::IsCapabilityUpdated(unsigned int AppId,bool isAuthAppId)
{
    bool isCapabilityUpdated = true;
    DIA_CER* lcer = itsDiaConfig.GetLocalCER();


    if(isAuthAppId)
    {
        for(int i = 0; i < lcer->countAuthApplicationId(); i++)
        {
            if(AppId == lcer->getAuthApplicationId(i).value())
            {
                isCapabilityUpdated = false;
                break;
            }
        }
    }
    else
    {
        for(int i = 0; i < lcer->countAcctApplicationId(); i++)
        {
            if(AppId == lcer->getAcctApplicationId(i).value())
            {
                isCapabilityUpdated = false;
                break;
            }
        }
    }

    return isCapabilityUpdated;

}


int DiaMsgRouter::SendCUR(unsigned int* authorizationAppId,unsigned int numOfAuthAppId,
                          unsigned int* accountingAppId, unsigned int numOfAcctAppId)
{
    DIA_CER* lcer = itsDiaConfig.GetLocalCER();
    DIA_CER* lrfc6733cer = itsDiaConfig.GetRFC6733LocalCER();
    DIA_CEA* lcea = itsDiaConfig.GetLocalCEA();
    DIA_CEA* lrfc6733cea = itsDiaConfig.GetRFC6733LocalCEA();

    for(int i = 0;i < numOfAuthAppId;i++)
    {
        DT_DBG(("Send CUR for updated app Id %d",authorizationAppId[i]));
        AuthApplicationId authAppId(authorizationAppId[i]);

        lcer->addAuthApplicationId(authAppId);
        lcea->addAuthApplicationId(authAppId);
        lrfc6733cer->addAuthApplicationId(authAppId);
        lrfc6733cea->addAuthApplicationId(authAppId);

    }

    for(int i = 0;i < numOfAcctAppId;i++)
    {
        DT_DBG(("Send CUR for updated acct Id %d",accountingAppId[i]));
        AcctApplicationId acctAppId(accountingAppId[i]);
        
        lcer->addAcctApplicationId(acctAppId);
        lcea->addAcctApplicationId(acctAppId);
        lrfc6733cer->addAcctApplicationId(acctAppId);
        lrfc6733cea->addAcctApplicationId(acctAppId);
    }

   DIA_CUR curMsg(false,false,false);

   curMsg.setOriginHost(lcer->getOriginHost());
   curMsg.setOriginRealm(lcer->getOriginRealm());

   for(int i =0;i < lcer->countHostIPAddress();i++)
   {
       curMsg.addHostIPAddress(lcer->getHostIPAddress(i));
   }

   curMsg.setVendorId(lcer->getVendorId());
   curMsg.setProductName(lcer->getProductName());

   if(lcer->containsOriginStateId())
   {
       curMsg.setOriginStateId(lcer->getOriginStateId());
   }

   for(int i = 0; i < lcer->countSupportedVendorId();i++)
   {
       curMsg.addSupportedVendorId(lcer->getSupportedVendorId(i));
   }

   for(int i = 0; i < lcer->countAuthApplicationId();i++)
   {
       curMsg.addAuthApplicationId(lcer->getAuthApplicationId(i));
   }
   
   for(int i = 0; i < lcer->countAcctApplicationId();i++)
   {
       curMsg.addAcctApplicationId(lcer->getAcctApplicationId(i));
   }

   for(int i = 0; i < lcer->countVendorSpecificApplicationId();i++)
   {
       curMsg.addVendorSpecificApplicationId(lcer->getVendorSpecificApplicationId(i));
   }
   //FormCURMessage(&curMsg);
   PEER_ENTRY *pEntry = PeerTable::GetPeerTable()->FindFirstEntry();

   if(pEntry != NULL)
   {
       do
       {

           DIA_GEN_CMD *gCmd = DIA_PE_CE_CACHE(pEntry);

           if(gCmd != NULL && ((DIA_PE_STATE(pEntry) == PEER_ST_I_OPEN) ||
                       (DIA_PE_STATE(pEntry) == PEER_ST_R_OPEN)))
           {
               for(int i = 0; i < gCmd->countAuthApplicationId();i++)
               {
                   if(gCmd->getAuthApplicationId(i)->value() == 
                           DIA_CAPABILITIES_UPDATE_APPLICATION_ID) 
                   {
                       ITS_UINT hId = DiaUtils::GenerateHopByHopId();
                       ITS_UINT eId = DiaUtils::GenerateEndToEndId();
                       ITS_OCTET *buff = NULL;
                       int len = 0;
                       DiaSocketTransport *handle = NULL;

                       DT_DBG(("Send CUR to %s",DIA_PE_HOST(pEntry)));
                       DiaUtils::EncodeMsg(&curMsg, &buff, len);
                       DIA_SET_HOP_BY_HOP(&buff[12], hId);

                       handle = (DiaSocketTransport*)(DIA_PE_HANDLE(pEntry));

                       if(handle !=NULL)
                       {
                           if(DiaMsgRouter::SendToPeer(handle, buff, len) == ITS_SUCCESS)
                           {
                               DIA_INC_PEER_SENT_CUR(pEntry);
                           };
                       }
                       else
                       {
                           DT_ERR(("Invalid transport to Peer %s",DIA_PE_HOST(pEntry)));
                       }
                       free((char*) buff);
                   }
               }
           }
           pEntry = PeerTable::GetPeerTable()->FindNextEntry(pEntry);
       }
       while(pEntry != NULL);
   }
     
}

