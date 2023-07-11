/*******************************-*CPP-*-*************************************
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
 *
 *  LOG: $Log: dia_stack.cpp,v $
 *  LOG: Revision 3.37.4.1.2.19.4.19.2.3.2.6.4.2.2.1.2.1  2014/10/27 08:28:39  millayaraja
 *  LOG: changes for HA HotStandBy
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.19.2.3.2.6.4.2.2.1  2014/08/26 10:24:47  pramana
 *  LOG: Logging related refinements
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.19.2.3.2.6.4.2  2014/03/07 06:41:50  jvikram
 *  LOG: BUGID=3286 Invalid Read Fixes
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.19.2.3.2.6.4.1  2014/02/20 14:24:00  jkchaitanya
 *  LOG: mh fixes
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.19.2.3.2.6  2014/01/06 09:22:32  cprem
 *  LOG: Changes in diameter stack to support session replication. Review request 1611.
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.19.2.3.2.5  2013/12/13 09:34:58  vsarath
 *  LOG: Merged the session-splict changes
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.19.2.3.2.4  2013/12/09 04:52:26  ncshivakumar
 *  LOG: Fixed bug 2439,2443,2368,1898
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.19.2.3.2.3  2013/10/26 07:42:21  ncshivakumar
 *  LOG: RFC 6733 changes
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.19.2.3.2.2  2013/09/10 08:36:39  ncshivakumar
 *  LOG: RFC6733 Changes
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.19.2.3.2.1  2013/07/15 06:33:08  jvikram
 *  LOG: Fixed crash during service restart
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.19.2.3  2013/07/04 10:54:43  ncshivakumar
 *  LOG: Updated for TPS based licensning
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.19.2.2  2013/07/01 06:53:26  ncshivakumar
 *  LOG: CHanges for fixing crash.Refer review board http://172.16.1.100/reviewboard/r/1016/
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.19.2.1  2013/06/10 09:37:12  cprem
 *  LOG: Review request 1016.
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.19  2013/04/17 13:33:11  mallikarjun
 *  LOG: Bug 1472 Changes
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.18  2013/04/16 17:28:49  cprem
 *  LOG: Changed log to meaningful one
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.17  2013/04/16 05:33:19  mallikarjun
 *  LOG: Bug 1425 chages
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.16  2013/04/12 04:18:27  vsarath
 *  LOG: Logs improvement
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.15  2013/04/10 05:41:27  mallikarjun
 *  LOG: TLS initilisation Chages bug 1363
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.14  2013/04/07 09:44:40  cprem
 *  LOG: Commented unused code
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.13  2013/04/07 03:54:21  cprem
 *  LOG: Changes made to fix HA bugs. Review Request 784
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.12  2013/04/05 13:00:45  jvikram
 *  LOG: Changes related to cx/dx/sh have been included
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.11  2013/03/28 08:49:50  vsarath
 *  LOG: Removed the code as a part of DDL enhancement
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.10  2013/03/22 07:16:54  jvikas
 *  LOG: Fix for 1257
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.9  2013/03/22 06:33:33  pramana
 *  LOG: Changes for HA feature
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.8  2013/03/13 11:03:13  ncshivakumar
 *  LOG: Added alarm for local ip down
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.7  2013/03/06 08:31:00  jvikram
 *  LOG: BUGID=1016, 1027, 803. Fixed the specified bugs.
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.6  2013/03/05 06:53:06  ncshivakumar
 *  LOG: Multihome changes
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.5  2013/03/05 06:44:57  vsarath
 *  LOG: Fix for issue 272
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.4  2013/02/27 08:49:07  jvikram
 *  LOG: Warnings raised by Coverity have been fixed
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.3  2013/02/21 11:17:07  ncshivakumar
 *  LOG: Modified for multitransport support
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.2  2013/02/12 05:45:31  vsarath
 *  LOG: Changes for TLS enable/disable
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19.4.1  2013/01/29 11:37:00  pramana
 *  LOG: DDL Changes
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.19  2012/12/28 09:25:16  mallikarjun
 *  LOG: Bug 757 chages
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.18  2012/12/21 05:31:54  ncshivakumar
 *  LOG: Modified for tracing
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.17  2012/12/20 18:37:21  rsanjay
 *  LOG: Dictionary name changes
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.16  2012/12/15 06:06:31  vsarath
 *  LOG: Provided option for own Certificate path
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.15  2012/12/11 04:03:36  cprem
 *  LOG: Changed Dictionary array to take fixed size.
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.14  2012/12/07 14:13:14  cprem
 *  LOG: Removing loading of Rx-Rel-6 dictionary since it is not meant for DRE.
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.13  2012/11/20 12:23:23  pramana
 *  LOG: *** empty log message ***
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.8.14.2  2012/11/20 04:19:40  pramana
 *  LOG: merged from 00 branch
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.11  2012/11/06 16:31:21  pramana
 *  LOG: Reverse merged from B-DRE-0212-00-COMP and B-DRE-0212-00-TLS branches for 212-06 release
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.8.12.3  2012/11/06 10:06:38  cprem
 *  LOG: Merged from 00 branch for 0212-06 release
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.8.12.2  2012/11/06 08:58:41  vsarath
 *  LOG: Added for TLS enhancements
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.8.12.1  2012/11/05 03:38:46  vsarath
 *  LOG: Added for TLS enhancements
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.10  2012/11/05 11:56:05  jvikas
 *  LOG: Code cleanup and converted the public static members to protected
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.9  2012/10/23 08:07:37  cprem
 *  LOG: Support for loading transformation plugins from configuration.
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.8  2012/10/11 09:13:24  vsarath
 *  LOG: DTF::Changes for Logging
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.7  2012/10/08 10:33:08  vsarath
 *  LOG: Fix for issue 251
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.6  2012/10/03 15:08:43  cprem
 *  LOG: Merged from ERLBF branch B-DRE-0212-02
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.5  2012/09/21 05:37:21  jvikas
 *  LOG: Fixed Bug 252 - Removed Diameter Dict Init out of DTFEnabled Check.
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.4.2.1  2012/09/20 08:21:13  cprem
 *  LOG: Added functionality to validate dictioary id's configured per peer.
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.4  2012/09/12 05:27:01  jvikas
 *  LOG: Included Dictionary Initialization if DTF is enabled.
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.3  2012/09/07 14:04:11  cprem
 *  LOG: Moved the dictionary table initialization out of DTF Configuration check since
 *  LOG: Dictionaries can be used by Rule Engine eventhough DTF is disabled.
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.2  2012/09/06 11:30:46  jvikas
 *  LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
 *  LOG:
 *  LOG:
 *  LOG: Revision 3.37.4.2  2012/08/01 06:14:12  ncshivakumar
 *  LOG: Code changes for Bug-119
 *  LOG:
 *  LOG: Revision 3.37.4.1.4.8  2012/08/31 04:59:29  cprem
 *  LOG: Remomoved Debug suffix for transformation plugins.
 *  LOG:
 *  LOG: Revision 3.37.4.1.4.7  2012/08/30 12:59:27  jvikas
 *  LOG: Fixed SendCmdToPeer from Test App
 *  LOG:
 *  LOG: Revision 3.37.4.1.4.6  2012/08/30 05:36:26  cashok
 *  LOG: Added the config parameter for plugin path
 *  LOG:
 *  LOG: Revision 3.37.4.1.4.5  2012/08/28 08:48:34  cprem
 *  LOG: Moved the DEBUG usage above since DEBUG is undefined.
 *  LOG:
 *  LOG: Revision 3.37.4.1.4.4  2012/08/27 10:57:22  cprem
 *  LOG: Added code to initialize dictionary table with Interface libraries that shall be shipped as part of DRE.
 *  LOG:
 *  LOG: Revision 3.37.4.1.4.3  2012/08/24 07:40:43  jvikas
 *  LOG: Fixed Compilation Issue for Rule Engine.
 *  LOG:
 *  LOG: Revision 3.37.4.1.4.2  2012/08/23 11:32:29  jvikas
 *  LOG: 1. Reading dictId from Peer Table Configuration
 *  LOG: 2. Calling BaseGenericCmd Destructor in DiaMsgFlow Destructor
 *  LOG: 3. Changed DictId ITS_UINT
 *  LOG: 4. Added HandleTransConfig
 *  LOG:
 *  LOG: Revision 3.37.4.1.4.1  2012/08/21 06:16:25  jvikas
 *  LOG: Checkin Working Modified Stack Code -Need to Cleanup and Fix Issues.
 *  LOG:
 *  LOG: Revision 3.37.4.1.2.1  2012/08/21 08:55:57  ksalil
 *  LOG: Merge from branch B-DRE-IDIA-0100-00
 *  LOG:
 *  LOG: Revision 3.37.4.1  2012/03/07 13:23:08  brajappa
 *  LOG: Changes made for the DRE demo
 *  LOG:
 *  LOG: Revision 3.37  2010/07/22 06:05:59  rajeshak
 *  LOG: Fix for IssueID:3013
 *  LOG:
 *  LOG: Revision 3.36  2010/06/30 04:06:36  nvijikumar
 *  LOG: abort if TLS enabled and failed to initialize
 *  LOG:
 *  LOG: Revision 3.35  2010/06/17 04:40:09  nvijikumar
 *  LOG: DiaConfig::ParserInitialize() introduced to support with engine XML
 *  LOG:
 *  LOG: Revision 3.34  2010/01/12 12:08:34  sureshj
 *  LOG: char* to ITS_BOOLEAN compilation error for 64 bit compilation.
 *  LOG: changed ITS_BOOLEAN to bool.
 *  LOG:
 *  LOG: Revision 3.33  2009/09/07 05:09:45  rajeshak
 *  LOG: Changes for HMI Heartbeat Callback
 *  LOG:
 *  LOG: Revision 3.32  2009/08/24 11:44:47  rajeshak
 *  LOG: Fix for Issue 2317(ACTIVE COLD REDUNDANCY::IDC not able to send
 *  LOG: messages to ACTIVE server)
 *  LOG:
 *  LOG: Revision 3.31  2009/07/13 06:46:21  rajeshak
 *  LOG: Reverting back session table changes.
 *  LOG:
 *  LOG: Revision 3.30  2009/06/29 14:54:53  rajeshak
 *  LOG: Changes done for performance enhancement (splitting the session table).
 *  LOG:
 *  LOG: Revision 3.29  2009/06/16 12:30:03  rajeshak
 *  LOG: Removed HMI Alarm suppressing code for MML Console, DiaOAMServer & DMServer.
 *  LOG: (Fix for Issue 2021)
 *  LOG:
 *  LOG: Revision 3.28  2009/05/12 08:42:31  rajeshak
 *  LOG: Klockwork reported Issue fix.
 *  LOG:
 *  LOG: Revision 3.27  2009/04/17 09:25:07  rajeshak
 *  LOG: Suppressing DMServer Hung thread Alarm.
 *  LOG:
 *  LOG: Revision 3.26  2009/04/13 13:36:57  rajeshak
 *  LOG: Peer Discovery changes.
 *  LOG:
 *  LOG: Revision 3.25  2009/04/10 06:32:07  sureshj
 *  LOG: Compilation flag HMI_ENABLE removed & Dynamic configuration
 *  LOG: for HMI added. Fix for the issue 1815 in whizible.Description of the
 *  LOG: Stack Shutdown/Termination Alarm is incorrect
 *  LOG:
 *  LOG: Revision 3.24  2009/04/07 13:48:20  sureshj
 *  LOG: HMI and OVERLOAD Control callback functions added.
 *  LOG:
 *  LOG: Revision 3.23  2009/03/19 12:34:50  nvijikumar
 *  LOG: Global instance is created for the Class ITSDiaConfig to avoid function
 *  LOG: call overhead as ITSDiaConfig::GetITSDiaConfig() was called max time
 *  LOG:
 *  LOG: Revision 3.22  2009/03/19 08:08:06  nvijikumar
 *  LOG: Reverting back HMI changes (App hangs and drop in TPS)
 *  LOG:
 *  LOG: Revision 3.21  2009/03/16 11:19:00  sureshj
 *  LOG: FeatureId: support for Health Monitoring Interface.
 *  LOG: Description: HMI callback registration is done in stack.
 *  LOG:
 *  LOG: Revision 3.20  2009/02/27 06:15:52  rajeshak
 *  LOG: Printing SCTP params configured in XML.
 *  LOG:
 *  LOG: Revision 3.19  2009/02/04 05:55:46  nvijikumar
 *  LOG: Changes for 64 Peer support with fixed number of threads
 *  LOG: 1. One thread for accepting connections and other for initiate connections
 *  LOG: 2. One thread to Read from I-Connections and other for R-Connections
 *  LOG:
 *  LOG: Revision 3.18  2009/01/03 07:02:14  nvijikumar
 *  LOG: Proper usage of trIndex
 *  LOG:
 *  LOG: Revision 3.17  2008/12/31 06:43:44  rajeshak
 *  LOG: IssueID: 1406
 *  LOG: FeatureID:none
 *  LOG: Description: (SCTP transport: dumping core on expiry of retrytimer)
 *  LOG: trindex set in PeerTable for SCTP transport also.
 *  LOG:
 *  LOG: Revision 3.16  2008/12/23 15:03:43  ssaxena
 *  LOG: Keeping next trtable index in the peer table
 *  LOG:
 *  LOG: Revision 3.15  2008/12/12 18:30:48  rajeshak
 *  LOG: Lightweight Decode for base AVPS
 *  LOG: New Command class is introduced (BaseCommand)
 *  LOG:
 *  LOG: Revision 3.14  2008/12/12 16:34:51  nvijikumar
 *  LOG: Raising Alarms
 *  LOG:
 *  LOG: Revision 3.13  2008/12/12 08:02:50  sureshj
 *  LOG: Support for Stack statistics
 *  LOG:
 *  LOG: Revision 3.12  2008/12/05 04:29:55  nvijikumar
 *  LOG: Issue:: number of UpStreamThreadCount was hard coded to "1"
 *  LOG:
 *  LOG: Revision 3.11  2008/11/28 13:39:12  ssaxena
 *  LOG: Issue ID: 1327
 *  LOG: Feature ID: None
 *  LOG: Description: Provided check in case of Active-ColdStandby not to  process
 *  LOG:              message when acting as backup Node.
 *  LOG:
 *  LOG: Revision 3.10  2008/11/22 10:55:40  ssaxena
 *  LOG: Fix for IssueId : 1292
 *  LOG: getNodeState and switchOver MML commands are not working for Redundancy
 *  LOG:
 *  LOG: Revision 3.9  2008/11/06 07:51:22  nvijikumar
 *  LOG: IssueID: none
 *  LOG: FeatureID: none
 *  LOG: Description: Incorporating Code review Comments renaming StackTunning
 *  LOG:              with QueueMgmt
 *  LOG:
 *  LOG: Revision 3.8  2008/10/31 05:56:55  nvijikumar
 *  LOG: IssueID:1189
 *  LOG: FeatureID: none
 *  LOG: Description: 1. Introducing additional TQs and Threads for better
 *  LOG:                 Performance on PP50 and initial stack tunning
 *  LOG:              2. Unwanted code cleanup
 *  LOG:
 *  LOG: Revision 3.7  2008/09/08 12:20:35  ssaxena
 *  LOG: Reverting back the changes done in revision 3.4 and also adding a new
 *  LOG: event source in RedundancyConfigCallback()for proper handling of redundancy
 *  LOG: events.(Hemant)
 *  LOG:
 *  LOG: Revision 3.6  2008/08/21 06:07:08  yranade
 *  LOG: Added APIs to print QSize, SessionTable size and SessionTable details.
 *  LOG:
 *  LOG: Revision 3.5  2008/07/09 14:01:51  vnarang
 *  LOG: Using New Tls Class API integrated for GNU TLS & OPEN SSL & Adding Copilation option
 *  LOG:
 *  LOG: Revision 3.4  2008/07/07 11:03:39  sureshj
 *  LOG:     Fix for the issue: IDS sending two notofications to IDC for an event
 *  LOG:
 *  LOG: Revision 3.3  2008/06/13 11:46:24  hbhatnagar
 *  LOG: Added GlobalInit , GlobalDeInit and client and certificate Initializations for TLS
 *  LOG:
 *  LOG: Revision 3.2  2008/04/01 16:32:58  hbhatnagar
 *  LOG: Changes for Proxy and Relay support 3.0 release - (Viji, Hemant)
 *  LOG:
 *  LOG: Revision 3.1  2008/03/31 10:33:32  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 2.37  2008/03/27 12:14:08  hbhatnagar
 *  LOG: Converting 2.1 branch to CURRENT
 *  LOG:
 *  LOG: Revision 2.34.2.7  2008/01/05 16:39:20  avinashks
 *  LOG: Changes made to provide fix for issue no.19 raised by Dhiranand during
 *  LOG: the validation of bcgi ticket 1807.
 *  LOG:
 *  LOG: Revision 2.34.2.6  2007/12/28 13:32:39  avinashks
 *  LOG: One space at the end of line was causing problem
 *  LOG: in compilation on Solaris Machine.
 *  LOG:
 *  LOG: Revision 2.34.2.5  2007/12/27 15:16:55  avinashks
 *  LOG: Changes made to fix issue no.2 (testcase No.1)
 *  LOG: raised during the validation of bcgi ticket 1807.
 *  LOG:
 *  LOG: Revision 2.34.2.4  2007/12/27 09:26:30  avinashks
 *  LOG: Changes made to fix issue no.13 raised during
 *  LOG: the validation of bcgi ticket 1807.
 *  LOG:
 *  LOG: Revision 2.34.2.3  2007/12/14 11:24:48  hbhatnagar
 *  LOG: Removed the DeviceWatchDog Timer related functionality and added
 *  LOG: WatchDog Transport Thread related functionality.
 *  LOG:
 *  LOG: Revision 2.34.2.2  2007/03/30 12:36:02  nvijikumar
 *  LOG: Fix for Addition of same appId multiple times to the CER.
 *  LOG: Bridgewater requirement.
 *  LOG:
 *  LOG: Revision 2.34.2.1  2007/03/12 04:51:44  nvijikumar
 *  LOG: Send DPR only incase of OPEN state for gracefull exit.
 *  LOG:
 *  LOG: Revision 2.34  2007/02/19 15:24:53  nvijikumar
 *  LOG: Fix for not to realm name to SessionId String if host name is FQDN.
 *  LOG:
 *  LOG: Revision 2.33  2007/01/31 17:33:56  kamakshilk
 *  LOG: Fix for Bug Id 5251. delete msgRouter removed from Terminate()
 *  LOG:
 *  LOG: Revision 2.32  2007/01/22 07:31:29  nanaparthi
 *  LOG: Modification for finding whether peer active or not
 *  LOG:
 *  LOG: Revision 2.31  2006/12/29 06:56:18  nanaparthi
 *  LOG: SCTP Multihoming related changes (baseline code base)
 *  LOG:
 *  LOG: Revision 2.30  2006/12/20 15:54:05  nvijikumar
 *  LOG: Elimination of multiple ITS_FindFeature function calls(DCCA & Redundancy).
 *  LOG:
 *  LOG: Revision 2.29  2006/12/15 12:38:41  tpanda
 *  LOG: Redundancy Config-Callback added,state change events to App via this function
 *  LOG:
 *  LOG: Revision 2.28  2006/12/11 13:51:25  tpanda
 *  LOG: REDUNDANCY_SLOT_CHANGES are removed and code seems to be stable
 *  LOG:
 *  LOG: Revision 2.27  2006/12/11 11:50:21  tpanda
 *  LOG: Minor changes to the Node state change callback function
 *  LOG:
 *  LOG: Revision 2.26  2006/12/11 11:40:49  tpanda
 *  LOG: Fix for standby node not handling transaction when peer gcs down(bug#4960)
 *  LOG:
 *  LOG: Revision 2.25  2006/12/11 06:15:07  nvijikumar
 *  LOG: Return value added for solaris compilation.
 *  LOG:
 *  LOG: Revision 2.24  2006/12/10 13:42:42  tpanda
 *  LOG: Redundancy Bug Fixes and enhancements--Transport Order Fix
 *  LOG:
 *  LOG: Revision 2.23  2006/11/30 18:54:24  tpanda
 *  LOG: Redundancy slot changes backed out. TODO: Refer (REDUNDANCY_SLOT_CHANGES) defines
 *  LOG: Failover and failback bug fixes
 *  LOG:
 *  LOG: Revision 2.22  2006/11/26 19:45:35  tpanda
 *  LOG: Inbound and outbound session index syncronisation
 *  LOG:
 *  LOG: Revision 2.21  2006/11/25 03:47:15  nvijikumar
 *  LOG: DCCA functions moved to downstream file for redundancy
 *  LOG:
 *  LOG: Revision 2.20  2006/11/24 17:20:12  hbhatnagar
 *  LOG: made changes for the new signature of Dcca Access functions
 *  LOG:
 *  LOG: Revision 2.19  2006/11/16 14:49:16  tpanda
 *  LOG: Redundancy support for ITS-Diameter--Baseline code
 *  LOG:
 *  LOG: Revision 2.18  2006/11/13 07:32:43  yranade
 *  LOG: On termination, hold off cleanup for a sec, to accomodate for DPA's
 *  LOG: from peer.
 *  LOG:
 *  LOG: Revision 2.17  2006/11/13 07:15:13  yranade
 *  LOG: Add AppId's in local CEA as well, in RegisterApplication.
 *  LOG:
 *  LOG: Revision 2.16  2006/11/07 11:18:01  tpanda
 *  LOG: codec library separated from stack library
 *  LOG:
 *  LOG: Revision 2.15  2006/11/03 14:03:26  nvijikumar
 *  LOG: 64 bit Compilation support.
 *  LOG:
 *  LOG: Revision 2.14  2006/10/31 09:07:38  hbhatnagar
 *  LOG: DCCA Integration.
 *  LOG:
 *  LOG: Revision 2.13  2006/10/30 15:57:41  yranade
 *  LOG: ReleaseSession API is Asychronous.
 *  LOG:
 *  LOG: Revision 2.12  2006/10/28 12:26:23  yranade
 *  LOG: Added ReleaseSession API to provide a hook for an application to
 *  LOG: clear session from sessionDb. May need revisit (to make it asynchronous)
 *  LOG:
 *  LOG: Revision 2.11  2006/10/27 09:56:52  hbhatnagar
 *  LOG: made a check for the AuthAppId in SendMsgToPeer. (Hemant)
 *  LOG:
 *  LOG: Revision 2.10  2006/10/27 09:34:34  yranade
 *  LOG: Send DPR when terminating. Bug Fix: 4644.
 *  LOG:
 *  LOG: Revision 2.9  2006/10/26 09:47:46  nvijikumar
 *  LOG: Fix for PBN Bug Id: 4590
 *  LOG: Changes for Transport terminate.
 *  LOG:
 *  LOG: Revision 2.8  2006/10/25 13:25:31  tpanda
 *  LOG: For extensible AVP support
 *  LOG:
 *  LOG: Revision 2.7  2006/10/25 06:29:39  hbhatnagar
 *  LOG: Integration with ITS_Diameter First Cut (badri)
 *  LOG:
 *  LOG: Revision 2.6  2006/10/24 14:24:41  yranade
 *  LOG: 1. RegisterWithAppId now takes AppId type.
 *  LOG: 2. Start(): No configFile argument needed.
 *  LOG: 3. Reorganize Initialization a bit, while sending message check if appId
 *  LOG: is registered.
 *  LOG:
 *  LOG: Revision 2.5  2006/10/16 06:31:48  yranade
 *  LOG: Generate sessionIndex in Allocate.
 *  LOG:
 *  LOG: Revision 2.4  2006/10/13 16:47:07  yranade
 *  LOG: API Updates.
 *  LOG:
 *  LOG: Revision 2.3  2006/10/05 13:21:54  yranade
 *  LOG: Getting there.
 *  LOG:
 *  LOG: Revision 2.2  2006/09/26 06:05:08  nvijikumar
 *  LOG: SCTP Changes ( Viji, Naresh)
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:44  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.1  2006/09/12 15:56:29  yranade
 *  LOG: Initial Version of ITS-Diameter (Yogesh, Viji, Tushar)
 *  LOG:
 *
 ****************************************************************************/
#include <sys/time.h>
#include <string>
#include <list>
#include <map>
#include <json/json.h>

#include <its++.h>
#include <its_route.h>
#include <its_transports.h>

#include <dia_config.h>

#include <dia_cmn.h>
#include <dia_msg_flow.h>
//Added for DTF
#include <Sync.h>
#include <PluginObj.h>
#include <DiameterTransformer.h>
#include <DiameterDictionary.h>
#include <DictionaryTable.h>
#include <dtf.h>
//End of DTF addition
#include <dia_acceptor.h>
#include <dia_connector.h>
#include <dia_stack.h>
#include <dia_trace.h>
#include <dia_err.h>
#include <dia_utils.h>
#include <dia_msg_router.h>
#include <its_dia_config.h>
#include <dia_peer_table.h>
#include <dia_realm_table.h>
#include <dia_session_table.h>
#include <dia_dict_parse.h>
#include <dia_peer_discovery.h>
/**
 * Adding a new header for Watchdog Thread
 */
#include <dia_wd_trans.h>

#include <dia_stack_stats.h>

#include "Tracer.h"

#ifdef DEBUG
#define DEBUGSUFFIX "D"
#else
#define DEBUGSUFFIX ""
#endif

#if defined (DEBUG)
#undef DEBUG
#endif

#define MAX_DICT_COUNT 16                

#if defined (ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
#endif

ITS_Mutex DiaStackClass::guard(0);
static DiaMsgRouter *msgRouter[MAX_ROUTER_THREADS];

ITS_Mutex DIAThreadIdList::lock(0);
int DIAThreadIdList::count(0);
DIAThreadIdList::Entry DIAThreadIdList::table[MAX_ROUTER_THREADS];
static DiaMsgSender *msgSender = NULL;
static DiaPeerDiscovery *peerDiscovery = NULL;
const unsigned int EPOCH = 2208988800; // delta between epoch time and ntp time

diameter::DTF DiaStackClass::mDtf;
diameter::DictionaryTable DiaStackClass::mDictTable;
/* flag to indicate, if the interface stats to be enabled or not */
bool DiaStackClass::m_interfaceStatsEnabled;

DiaStackStats diaStackStats;
ITSDiaConfig itsDiaConfig;
/**
 * Defining and Initializing the client and server
 * Certificates.
 */
#ifdef TLS_ENABLED
Certificate *clientCertificate = NULL;
Certificate *serverCertificate = NULL;
#endif

/**
 * Added these objects for redundancy
 */
ITS_NODE_STATE state;
static ITS_BOOLEAN isActiveUpOrJoined = ITS_FALSE;
void CheckBackupNode();

ITS_BOOLEAN overLoadF=ITS_FALSE;

/**
 * Declaring pointer for WatchDog Thread
 */
static DiaWatchDogTransport *watchDogTransport = NULL;
char* GetDiastackTqName(int i) 
{
    static char tqName[ITS_PATH_MAX] = {0};
    memset(tqName, 0, ITS_PATH_MAX);
    sprintf(tqName,"%s%d",DIASTACK_TQ_NAME,i);
    return tqName;
}

DiaStackClass::DiaStackClass()
{

    ITSDiaConfig* cfg = &itsDiaConfig;
    ITS_UINT numThreads = 1;

    printf("DiaStackClass Init\n");

    /* XML Parsing is first */
    /* Initialize Accelero XML Configuration Reader */
    DiaConfig *dCfg = DiaConfig::GetDiaConfig();

    /* Parser configs from Accelero XML*/
    dCfg->ParserInitialize();

    /* Initialize Diameter Stack XML Configuration Reader */
    cfg->DiaParserInitialize(dCfg->GetConfigFile());

    if (itsDiaConfig.IsQueueMgmtEnabled())
    {
        numThreads = itsDiaConfig.GetQueueMgmt().GetMsgRouterThreadCount();
    }
    for (int i=0; i<numThreads; i++)
    {
        msgRouter[i] = new DiaMsgRouter(1, DIASTACK_TQ_INST+i,
                                           GetDiastackTqName(i));
    }

    /**
     * Creating and adding new thread for WatchDog
     */
    watchDogTransport = new DiaWatchDogTransport();
        
    /* Initialize Dictionary XML for AVP extensibility support */
    DiaDictParserInitialize(cfg->GetProductInfo().GetDictionary());

    for (int accIdx = 0; accIdx < DIA_STACK_MAX_ACCEPTORS; accIdx++)
    {
        acceptor[accIdx] = NULL;
        accReader[accIdx] = NULL;
    }
    connector = NULL;
    connReader = NULL;
    numAcceptor = 0;
    started = false;
    m_tokenUpdateThread = NULL;
    m_startTokenThread = NULL;
    m_interfaceStatsEnabled = false;
}

int DiaStackClass::ValidatePeerDictionaries()
{
	bool ret;
	PEER_ENTRY *pEntry = PeerTable::GetPeerTable()->FindFirstEntry();
	if (pEntry != NULL)
	{
		try
		{
			do 
			{
				ret = DiaStackClass::GetDtf().validateDictIds(DiaStackClass::GetDictionaryTable(),pEntry->dictId);
				if(!ret)
				{
					DT_ERR(("Dictionary Id's configured for Peer name %s are invalid.",DIA_PE_HOST(pEntry)));
					return !ITS_SUCCESS;
				}
				pEntry = PeerTable::GetPeerTable()->FindNextEntry(pEntry);
			}while(pEntry!=NULL);
		}
		catch(eAccelero::PluginException& x)
		{
			DT_ERR(("PluginException:: %s",x.what()));
			return !ITS_SUCCESS;
		}

	} 
	else
	{
		DT_ERR(("No diameter Peers Configured."));
	}
	return ITS_SUCCESS;
}

int
DiaStackClass::InitDictionaryTable()
{
    if(!itsDiaConfig.getpluginpathname())
    {
        DT_ERR(("Plugin Path not configured"));
        return !ITS_SUCCESS;
    }
    std::string pluginpath(itsDiaConfig.getpluginpathname());
	eAccelero::PluginLoader::SetPluginDir(pluginpath);

	return ITS_SUCCESS;
}
int
DiaStackClass::InitTransformationTable()
{
	
	bool eFlag = false;
	ITS_UINT count = 0;

    if(!itsDiaConfig.getpluginpathname())
    {
        DT_ERR(("Plugin Name not configured"));
        return !ITS_SUCCESS;
    }

    std::string pluginpath(itsDiaConfig.getpluginpathname());
    eAccelero::PluginLoader::SetPluginDir(pluginpath);

	ITS_UINT pluginCount = itsDiaConfig.GetTransfromPluginCount();
	DT_DBG(("Loading the Transformation Plugins"));

	for (int i = 0; i < pluginCount; i++)
	{
		try
		{
			DIA_TRANFORM_PLUGIN &pobj = itsDiaConfig.GetTranformPluginAt(i);
			cout<<"Loading Plugin:"<<pobj.pluginName<<endl;
		
			DiameterDictionaryRef dRef1;
			DiameterDictionaryRef dRef2;

			dRef1 = DiaStackClass::GetDictionaryTable().fetchDictionaryObject(pobj.dictId1);
			dRef2 = DiaStackClass::GetDictionaryTable().fetchDictionaryObject(pobj.dictId2);

			if(dRef1.IsNull() || dRef2.IsNull())
			{
				DT_ERR(("***Invalid Dictionary name configured***"));
				continue;
			}

			ITS_UINT dictId1 = dRef1->getDictionaryId();
			ITS_UINT dictId2 = dRef2->getDictionaryId();
			
		    if(DiaStackClass::GetDtf().LoadTransformerObject(dictId1, dictId2, pobj.pluginName, pobj.config) == ITS_SUCCESS)
            {
			    cout<<pobj.pluginName<<": loaded successfully"<<endl;
			    count++;
            }
		}
	
		catch (eAccelero::PluginException& x)
		{
			DT_CRT(("PluginException::%s ", x.what()));
			eFlag = true;
		}
	}

	DT_DBG(("Number of plugins Loaded:%d",count));

	if (count == 0 || eFlag == true)
	{
		return !ITS_SUCCESS;
	}
	else
	{
		return ITS_SUCCESS;
	}

}


int
DiaStackClass::Start(bool activateStack)
//DiaStackClass::Start(bool initLocalTransports, bool initPeerTransports)
{
    int ret;

    DT_DBG(("DiaStackClass:: Start"));

    ITSDiaConfig *cfg = &itsDiaConfig;

    cfg->Print();
    
    if(cfg->isTlsEnable())
    {
       InitTLS();
    }

    ITS_Class redunClass = ITS_FindFeature(REDUNDANCY_CLASS_NAME);

    /* Store the ITS_Class of redundancy feature just to avoid multiple finds */
    itsDiaConfig.SetRedundancyFeature(redunClass);
    if (redunClass)
    {
       /* for active-active multicasitng of message not required
        * needs further discussion
        */
       if (REDUNDANCY_CONFIGURED_TYPE(redunClass) == ITS_ACTIVE_ACTIVE)
       {
          return DIA_SUCCESS;
       }

       /* Register for callback funnction to receive Redundancy related
          events */
       CALLBACK_Manager* cb = REDUNDANCY_CALLBACK_MGR(redunClass);
       if (cb)
       {
          CALLBACK_AddCallback(REDUNDANCY_CALLBACK_MGR(redunClass),
                               RedundancyConfigCallback,
                               NULL);
       }

       /**
        * Procedure to check if the Local Node is backup or not.
        * If backup wait to become active or get Alive or join indications
        * from mate, before actually initializing the stack. Fix for issue
        * no 13 raised by Dhiranand during the validation of bcgi ticket
        * 1807.
        */
       CheckBackupNode();
    }
    
#if 0
    if (msgRouter)
    {
        msgRouter->Start();
        if (msgSender)
        {
            msgSender->Start();
        }
        else
        {
            DT_WRN(("DiaStackClass:: Dedicated msgSender not Initialized"));
        }
#endif
        int numThreads = 1;
        if (itsDiaConfig.IsQueueMgmtEnabled())
        {
            numThreads = itsDiaConfig.GetQueueMgmt().GetMsgRouterThreadCount();
        }
    
        for (int i=0; i<numThreads; i++)
        {
            if (msgRouter[i])
            {
                msgRouter[i]->Start();
            }
        }

        DT_DBG(("DiaStackClass:: ITS Diameter Stack Started"));

        DT_DBG(("DiaStackClass::Checking for IsDTFEnabled %d", cfg->IsDTFEnabled()));

        DT_DBG(("DiaStackClass::Initializing Dictionary Table"));
        ret = DiaStackClass::InitDictionaryTable();
        if (ret == ITS_SUCCESS)
        {
            DT_DBG(("DiaStackClass::Succesfully Initialized Diameter Dictionary"));
        }
        else
        {
            DT_ERR(("DiaStackClass::Initialized Diameter Dictionary Failed"));
        }
        if(cfg->IsDTFEnabled())
	    {
            DiaStackClass::GetDtf().InitLog();

			//Validate the Peer configuration for valid Dict Id's
			DT_DBG(("DiaStackClass::Validating Peer Dictionary Configuration"));
			ret = DiaStackClass::ValidatePeerDictionaries();
			if (ret == ITS_SUCCESS)
			{
				DT_DBG(("DiaStackClass::Succesfully Validated Peer Dictionary Configuration."));
			}
			else 
			{
				DT_CRT(("DiaStackClass::Peer Dictionary validation Failed"));
				return (!ITS_SUCCESS);	
			}
	    }


        if(TOKEN_BUCKET_FILTER->MessageRate() != 0xFFFFFFFF)
        {
            DT_DBG(("Creating Token Update thread"));
            m_tokenUpdateThread = new TokenUpdateThread();
            m_startTokenThread= new eAccelero::Thread("Token UpdateThread");
            m_startTokenThread->Start((eAccelero::Runnable*)m_tokenUpdateThread);
        }
        else
        {
            DT_DBG(("Not creating Token Update thread as license is not based on msg rate"));
        }
        
        DT_DBG(("DiaStackClass::Initializing Local Transports"));

        //if (initLocalTransports)
        //{
            ret = InitLocalTransports(activateStack);
            if (ret != ITS_SUCCESS)
            {
                DT_ERR((" :: FAILURE :: DiaStackClass::Initialized Local Transports "));
                return (!ITS_SUCCESS);
            }
        //}
        //if (initPeerTransports)
        //{
            ret = InitPeerTransports(activateStack);
            if (ret == ITS_SUCCESS)
            {
                DT_DBG(("DiaStackClass::Succesfully Initialized Peer Transports"));
            }
            //If Stack is not Activated then disable Transports.
            /*if(!activateStack)
            {
                GoStandby();
            }*/

        //}
#if 0
    }
    else
    {
        DT_CRT(("DiaStackClass:: Fatal Error:: Failed to start"));
        DIA_Alarm(15200, __FILE__, __LINE__, NULL);
        return DIA_FAILURE;
    }
#endif
    started = true;

    /* is Peer discovery Enabled */
    if (cfg->isPeerDiscoveryEnabled())
    {
        /* start Peer discovery thread */
        peerDiscovery = new DiaPeerDiscovery();
        if (peerDiscovery)
        {
            peerDiscovery->Start();
        }
    }

    /* Store the ITS_Class of DCCA feature just to avoid multiple finds */
    itsDiaConfig.SetDccaFeature(ITS_FindFeature
                                                    (DCCA_FEATURE_NAME));

    /*
     * Multicast the message to nodes and if successful set the flag.
     * A dummy event multicasted just to check if redundancy enabled
     */
    ITS_EVENT ev;
    ITS_EVENT_INIT(&ev, DIA_GCS_NO_SRC_INST, 1);
    ev.data[0]=0;//dummy value
    if (DSM_MulticastStackEventToFtGroupMembers(
                  SESSION_TABLE_FT_GROUP_ID,
                  ev,
                  DIA_GCS_NO_SRC_INST,
                  DIASTACK_TQ_INST) == ITS_SUCCESS)
    {
        DT_DBG(("DiaStackClass:: Redundancy is enabled"));
        cfg->setMsgRedundancyEnabled();
    }
    ITS_EVENT_TERM(&ev);

    return DIA_SUCCESS;
}

/*int
DiaStackClass::Start()
{
    int ret;

    DT_DBG(("DiaStackClass:: Start"));

    ITSDiaConfig *cfg = &itsDiaConfig;

    cfg->Print();

    ITS_Class redunClass = ITS_FindFeature(REDUNDANCY_CLASS_NAME);*/

    /* Store the ITS_Class of redundancy feature just to avoid multiple finds */
   /* itsDiaConfig.SetRedundancyFeature(redunClass);
    if (redunClass)
    {*/
       /* for active-active multicasitng of message not required
        * needs further discussion
        */
       /*if (REDUNDANCY_CONFIGURED_TYPE(redunClass) == ITS_ACTIVE_ACTIVE)
       {
          return DIA_SUCCESS;
       }*/

       /* Register for callback funnction to receive Redundancy related
          events */
      /* CALLBACK_Manager* cb = REDUNDANCY_CALLBACK_MGR(redunClass);
       if (cb)
       {
          CALLBACK_AddCallback(REDUNDANCY_CALLBACK_MGR(redunClass),
                               RedundancyConfigCallback,
                               NULL);
       }*/

       /**
        * Procedure to check if the Local Node is backup or not.
        * If backup wait to become active or get Alive or join indications
        * from mate, before actually initializing the stack. Fix for issue
        * no 13 raised by Dhiranand during the validation of bcgi ticket
        * 1807.
        */
       /*CheckBackupNode();
    }
    
    if (msgRouter)
    {
        msgRouter->Start();
        if (msgSender)
        {
            msgSender->Start();
        }
        else
        {
            DT_WRN(("DiaStackClass:: Dedicated msgSender not Initialized"));
        }

        DT_DBG(("DiaStackClass:: ITS Diameter Stack Started"));

        DT_DBG(("DiaStackClass::Checking for IsDTFEnabled %d", cfg->IsDTFEnabled()));

        DT_DBG(("DiaStackClass::Initializing Dictionary Table"));
        ret = DiaStackClass::InitDictionaryTable();
        if (ret == ITS_SUCCESS)
        {
            DT_DBG(("DiaStackClass::Succesfully Initialized Diameter Dictionary"));
        }
        else
        {
            DT_ERR(("DiaStackClass::Initialized Diameter Dictionary Failed"));
        }
        if(cfg->IsDTFEnabled())
	    {
            DiaStackClass::GetDtf().InitLog();
            DT_DBG(("DiaStackClass::Initializing Transformation Table"));
            ret = DiaStackClass::InitTransformationTable();
            if (ret == ITS_SUCCESS)
            {
                DT_DBG(("DiaStackClass::Succesfully Initialized Transformation Dictionary"));
            }
            else
            {
                DT_CRT(("DiaStackClass::Initialized Transformation Dictionary Failed"));
            }

			//Validate the Peer configuration for valid Dict Id's
			DT_DBG(("DiaStackClass::Validating Peer Dictionary Configuration"));
			ret = DiaStackClass::ValidatePeerDictionaries();
			if (ret == ITS_SUCCESS)
			{
				DT_DBG(("DiaStackClass::Succesfully Validated Peer Dictionary Configuration."));
			}
			else 
			{
				DT_ERR(("DiaStackClass::Peer Dictionary validation Failed"));
				exit(0);
			}
	    }

        DT_DBG(("DiaStackClass::Initializing Local Transports"));

        ret = InitLocalTransports();
        if (ret != ITS_SUCCESS)
        {
	   DT_ERR((" :: FAILURE :: DiaStackClass::Initialized Local Transports "));
	   return (!ITS_SUCCESS);
        }

        ret = InitPeerTransports();
        if (ret == ITS_SUCCESS)
        {
            DT_DBG(("DiaStackClass::Succesfully Initialized Peer Transports"));
        }

    }
    else
    {
        DT_CRT(("DiaStackClass:: Fatal Error:: Failed to start"));
        DIA_Alarm(15200, __FILE__, __LINE__, NULL);
        return DIA_FAILURE;
    }
    started = true;*/

    /* is Peer discovery Enabled */
   // if (cfg->isPeerDiscoveryEnabled())
   // {
        /* start Peer discovery thread */
   /*     peerDiscovery = new DiaPeerDiscovery();
        if (peerDiscovery)
        {
            peerDiscovery->Start();
        }
    }*/

    /* Store the ITS_Class of DCCA feature just to avoid multiple finds */
    //itsDiaConfig.SetDccaFeature(ITS_FindFeature
     //                                               (DCCA_FEATURE_NAME));

    /*
     * Multicast the message to nodes and if successful set the flag.
     * A dummy event multicasted just to check if redundancy enabled
     */
    /*ITS_EVENT ev;
    ITS_EVENT_INIT(&ev, DIA_GCS_NO_SRC_INST, 1);
    ev.data[0]=0;//dummy value
    if (DSM_MulticastStackEventToFtGroupMembers(
                  SESSION_TABLE_FT_GROUP_ID,
                  ev,
                  DIA_GCS_NO_SRC_INST,
                  DIASTACK_TQ_INST) == ITS_SUCCESS)
    {
        DT_DBG(("DiaStackClass:: Redundancy is enabled"));
        cfg->setMsgRedundancyEnabled();
    }
    ITS_EVENT_TERM(&ev);

    return DIA_SUCCESS;
}*/

int
DiaStackClass::AllocateSession(unsigned int appId, unsigned int& sessIdx,
                               std::string& sessIdString)
{
    int ret = DIA_SUCCESS;
    unsigned int index = 0;

    if (started)
    {
        ITS_ASSERT(guard.Acquire() == ITS_SUCCESS);
        static unsigned int count = 0;

        count++;
        DIA_CER *lcer;
        lcer = itsDiaConfig.GetLocalCER();

        sessIdString = lcer->getOriginHost().value();

        /* Dont add realm to SessionId String if host is FQDN */
        if (sessIdString.find('.') == -1)
        {
            sessIdString += ".";
            sessIdString += lcer->getOriginRealm().value();
        }
        sessIdString += ";";
        timeval tv;
        gettimeofday(&tv, NULL);
        char timeval[100];
        //Correcting Calling rixky function
        memset(&timeval, 0, 100);
        //Warning Fix - format "%d" expects type "int", but argument x has type "__time_t"
        //Warning Fix - format "%d" expects type "int", but argument x has type "__susecond_t"
        snprintf(timeval,99, "%u;%u", tv.tv_sec+EPOCH, count);

        sessIdString +=timeval;

        if (SessionTable::AllocateClientSessionIndex(index) == ITS_SUCCESS)
        {
            sessIdx = index;
            DT_DBG(("Allocated SessIndex %d", index));
        }
        else
        {
            DT_CRT(("Alloc Failure"));
            ret = ITS_DIA_ALLOCFAIL;
        }
    }
    else
    {
        ret = ITS_DIA_INITFAIL;
    }
    guard.Release();

    return (ret);
}


void
DiaStackClass::ReleaseClientSession(unsigned int sessId)
{
}

int
DiaStackClass::ReleaseSession(const char* sessionId)
{
    int ret = ITS_SUCCESS;
    ITS_USHORT dest = DIASTACK_TQ_INST;
    if (itsDiaConfig.IsQueueMgmtEnabled())
    {
        dest = DIASTACK_SENDER_TQ_INST;
    }

    dest = DiaUtils::GetStackTQInst(sessionId);

    Event ev(DIA_APP_REM_SESS_INST, strlen(sessionId) + 1, (ITS_OCTET *)sessionId);
    ret = its::Transport::PutEvent(dest, ev);

    return ret;
}

int DiaStackClass::GetDiaStackQCount(int index)
{
    int count = 0;
    if (msgRouter[index] != NULL)
    {
        its::TaskQueueTransport *tq = msgRouter[index]->GetTransport();
        if (tq != NULL)
        {
            const TRANSPORT_Control *tc = tq->GetTC();
            TQUEUETRAN_Manager *tqM = (TQUEUETRAN_Manager *)tc;
            EMLIST_Manager *lm = TQUEUETRAN_EMLIST(tqM);
            count = LIST_COUNT((LIST_Manager *)(lm));
        }
    }
    else
    {
        return ITS_ENOQUEUE;
    }

    return count;
}

int DiaStackClass::GetDiaStackQCount()
{
    int count = 0;
/*    if (msgRouter != NULL)
    {
        its::TaskQueueTransport *tq = msgRouter->GetTransport();
        if (tq != NULL)
        {
            const TRANSPORT_Control *tc = tq->GetTC();
            TQUEUETRAN_Manager *tqM = (TQUEUETRAN_Manager *)tc;
            EMLIST_Manager *lm = TQUEUETRAN_EMLIST(tqM);
            count = LIST_COUNT((LIST_Manager *)(lm));
        }
    }
    else
    {
        return ITS_ENOQUEUE;
    }*/

    return count;
}
int DiaStackClass::GetDiaStackSenderQCount()
{
    int count = 0;
    /*if (msgSender != NULL)
    {
        its::TaskQueueTransport *tq = msgSender->GetTransport();
        if (tq != NULL)
        {
            const TRANSPORT_Control *tc = tq->GetTC();
            TQUEUETRAN_Manager *tqM = (TQUEUETRAN_Manager *)tc;
            EMLIST_Manager *lm = TQUEUETRAN_EMLIST(tqM);
            count = LIST_COUNT((LIST_Manager *)(lm));
        }
    }
    else
    {
        return ITS_ENOQUEUE;
    }*/
    return count;
}

DTF& DiaStackClass::GetDtf()
{
        return mDtf;
}

DictionaryTable& DiaStackClass::GetDictionaryTable()
{
        return mDictTable;
}

DiaStackClass::~DiaStackClass()
{
    Terminate();
}

int DiaStackClass::GetMsgRouterThreadCount()                                  
{    
   return itsDiaConfig.GetQueueMgmt().GetMsgRouterThreadCount();             
}                                                                            

void
DiaStackClass::Terminate()
{
    TermTransports(false);

    int numThreads = itsDiaConfig.GetQueueMgmt().GetMsgRouterThreadCount();

    for (int i=0; i<numThreads; i++)
    {
        if (msgRouter[i])
        {
            msgRouter[i]->Stop();
        }
        started = false;
    }
#ifdef TLS_ENABLED
    ITSDiaConfig* cfg = &itsDiaConfig;
    if(cfg->isTlsEnable())
    {
        /**
         * De-Initializing TLS related parameters.
         */
        if(clientCertificate)
        {
            delete clientCertificate;
            clientCertificate = NULL;
        }

        if(serverCertificate)
        {
            delete serverCertificate;
            serverCertificate = NULL;
        }
        TlsFactoryClass::DeInitializeTls();
    }

#endif

    /**
     * Exiting the WatchDog Transport and
     * deleting the transport Object
     */
    if (watchDogTransport)
    {
        watchDogTransport->SetExit();
	sleep(1);
        delete watchDogTransport;
        watchDogTransport = NULL;
    }

    //Free Resources allocated for Peers in Peer Table
    //PeerTable::GetPeerTable()->DropAllPeers();
    DIA_Alarm(15201, __FILE__, __LINE__, "Diameter Stack Termination");
}

int
DiaStackClass::SendMsgToPeer(const diameter::Command* mesg, unsigned int sessionInd,
                             ITS_USHORT toPeer, ITS_UINT flags)
{
    // ITS_OCTET data[sizeof(ITS_UINT) + sizeof(ITS_ULONG)];
    DiaMsgToPeerEvt data;

    if (started)
    {
        ITS_USHORT dest = DIASTACK_TQ_INST;
        if (itsDiaConfig.IsQueueMgmtEnabled())
        {
            dest = DIASTACK_SENDER_TQ_INST;
        }

        ITSDiaConfig* cfg = &itsDiaConfig;
        //send message to peer if the node is active only
        ITS_NODE_STATE state;
        if (cfg->IsMsgRedundancyEnabled() &&
           (ITS_GetNodeState(&state) == ITS_SUCCESS) &&
            state != ITS_STATE_PRIMARY)
        {
            DT_ERR(("Backup Node: Message can't be delivered to peer"));
            return DIA_FAILURE;
        }
        DIA_CER *cer = itsDiaConfig.GetLocalCER();

        DIA_GEN_CMD *msg = (DIA_GEN_CMD *)mesg;

        if (DiaMsgRouter::ValidateMessage((DIA_GEN_CMD *)cer, msg) != ITS_SUCCESS)
        {
            DT_ERR(("Validate Failure: Application Not Supported"));
            return DIA_APP_ID_NOT_REGISTERED;
        }

        DIA_BASE_CMD* bCmd = new DIA_BASE_CMD((DIA_GEN_CMD *)mesg);

        ITS_UINT cmdCode  = bCmd->getCommandCode();
        DT_DBG(("SendMsgToPeer:: CMD = %d\n\n", cmdCode));

        data.cmd = bCmd;
        data.sessionIdx = sessionInd;
        data.toPeer = toPeer;
        data.flags = flags;
        Event ev(DIA_APP_INST, sizeof(data), (ITS_OCTET*)&data);
 
        dest = DiaUtils::GetStackTQInst(bCmd);
        DT_DBG(("Dest = %d\n",dest));

        its::Transport::PutEvent(dest, ev);

        return DIA_SUCCESS;
    }

    return DIA_FAILURE;
}

/*DTF changes */
int DiaStackClass::SendMsgToPeer(const DIA_BASE_CMD* mesg, unsigned int sessionInd,
                             ITS_USHORT toPeer, ITS_UINT flags)
{
    DiaMsgToPeerEvt data;

    if (started)
    {
        ITS_USHORT dest = DIASTACK_TQ_INST;
        if (itsDiaConfig.IsQueueMgmtEnabled())
        {
            dest = DIASTACK_SENDER_TQ_INST;
        }

        ITSDiaConfig* cfg = &itsDiaConfig;
        //send message to peer if the node is active only
        ITS_NODE_STATE state;
        if (cfg->IsMsgRedundancyEnabled() &&
           (ITS_GetNodeState(&state) == ITS_SUCCESS) &&
            state != ITS_STATE_PRIMARY)
        {
            DT_ERR(("Backup Node: Message can't be delivered to peer"));
            return DIA_FAILURE;
        }
        DIA_CER *cer = itsDiaConfig.GetLocalCER();

        DIA_BASE_CMD *gmsg = (DIA_BASE_CMD*) mesg;
        DIA_GEN_CMD *msg = gmsg->GetBaseGenCommand();

        if (DiaMsgRouter::ValidateMessage((DIA_GEN_CMD *)cer, msg) != ITS_SUCCESS)
        {
            DT_ERR(("Validate Failure: Application Not Supported"));
            return DIA_APP_ID_NOT_REGISTERED;
        }

        ITS_UINT cmdCode  = mesg->getCommandCode();
        DT_DBG(("SendMsgToPeer:: CMD = %d\n\n", cmdCode));

        data.cmd = gmsg;
        data.sessionIdx = sessionInd;
        data.toPeer = toPeer;
        data.flags = flags;
        Event ev(DIA_APP_INST, sizeof(data), (ITS_OCTET*)&data);
        dest = DiaUtils::GetStackTQInst(gmsg);
        DT_DBG(("Dest = %d\n",dest));
        its::Transport::PutEvent(dest, ev);

        return DIA_SUCCESS;
    }

    return DIA_FAILURE;
}

int
DiaStackClass::SendMsgToPeer(const diameter::Command* mesg)
{
    //ITS_OCTET data[sizeof(ITS_UINT)];
    ITS_OCTET data[sizeof(ITS_ULONG)];

    if (started)
    {
        ITS_USHORT dest = DIASTACK_TQ_INST;
        if (itsDiaConfig.IsQueueMgmtEnabled())
        {
            dest = DIASTACK_SENDER_TQ_INST;
        }

        ITSDiaConfig* cfg = &itsDiaConfig;
        //send message to peer if the node is active only
        ITS_NODE_STATE state;

        /**
         * Partial Fix for the whizible issue 1327. Provided check
         * for Active-ColdStandby not process message when backup.
         */
        if (cfg->IsRedundancyEnabled() &&
           (ITS_GetNodeState(&state) == ITS_SUCCESS) &&
            state != ITS_STATE_PRIMARY)
        {
            DT_ERR(("Backup Node: Message can't be delivered to peer"));
            return DIA_FAILURE;
        }
        DIA_CER *cer = itsDiaConfig.GetLocalCER();

        DIA_GEN_CMD *msg = (DIA_GEN_CMD *)mesg;

        if (DiaMsgRouter::ValidateMessage((DIA_GEN_CMD *)cer, msg) != ITS_SUCCESS)
        {
            DT_ERR(("Validate Failure: Application Not Supported"));
            return DIA_APP_ID_NOT_REGISTERED;
        }

        /*DTF Changes*/
        const CommandImpl& impl = mesg->getImpl();
        DIA_GEN_CMD* gCmd = new DIA_GEN_CMD(const_cast<CommandImpl&>(impl));
        DIA_BASE_CMD* bCmd = new DIA_BASE_CMD(gCmd);
        DT_DBG(("SendMsgToPeer:: CMD = %u\n\n", mesg));
        DT_DBG(("SendMsgToPeer:: BASEGENRICCMD = %u\n\n", (DIA_GEN_CMD *)mesg));

        ITS_UINT cmdCode  = bCmd->getCommandCode();
        DT_DBG(("SendMsgToPeer:: CMD = %d\n\n", cmdCode));

        memcpy(&data[0], &bCmd, sizeof(ITS_ULONG));
        Event ev(DIA_APP_INST, sizeof(ITS_ULONG), data);
        dest = DiaUtils::GetStackTQInst(bCmd);
        DT_DBG(("Dest = %d\n",dest));
        its::Transport::PutEvent(dest, ev);

	return DIA_SUCCESS;
    }

    return DIA_FAILURE;
}

unsigned int
DiaStackClass::RegisterWithAppId(unsigned int id, unsigned int type)
{
    DIA_CER *cer = itsDiaConfig.GetLocalCER();
    DIA_CEA *cea = itsDiaConfig.GetLocalCEA();
    bool found = false;

    if (type == DIA_AUTHORIZATION)
    {
        for (int i=0; i<cer->countAuthApplicationId();i++)
        {
            if (id == cer->getAuthApplicationId(i).value())
            {
                found = true;
                break;
            }
        }
        if(!found)
        {
            cer->addAuthApplicationId(AuthApplicationId(id));
            cea->addAuthApplicationId(AuthApplicationId(id));
        }
    }
    else if (type == DIA_ACCOUNTING)
    {
        for (int i=0; i<cer->countAcctApplicationId();i++)
        {
            if (id == cer->getAcctApplicationId(i).value())
            {
                found = true;
                break;
            }
        }
        if(!found)
        {
            cer->addAcctApplicationId(AcctApplicationId(id));
            cea->addAcctApplicationId(AcctApplicationId(id));
        }
    }
    else
    {
        DT_ERR(("Invalid session type...Failed to register %d ", id));
        return DIA_FAILURE;
    }

    return DIA_SUCCESS;
}

int
DiaStackClass::SendAuthSuccToPeer(diameter::Command& mesg)
{
    return DIA_SUCCESS;
}

int
DiaStackClass::SendAuthRequestToPeer(diameter::Command& mesg)
{
    return DIA_SUCCESS;
}
int 
DiaStackClass::InitTLS()
{

    ITSDiaConfig* cfg = &itsDiaConfig;
#ifdef TLS_ENABLED
    TlsFactoryClass * tlsObj = NULL;
    char *certFile = NULL, *keyFile = NULL, *caTrustFile = NULL , *caPath = NULL;
    std::string ownCertPathClient, ownKeyPathClient, ownCertPathServer, ownKeyPathServer;
    if(cfg->isTlsEnable())
    {
        tlsObj =  TlsFactoryClass::InitializeTls(TLS_TYPE(cfg->GetSecurityConfig().GetTlsType()));
        if(tlsObj != NULL)
        {
            caPath  = (char *)cfg->GetSecurityConfig().GetCAPath();

            ITSDiaConfig::SecurityConfig& secConf = cfg->GetSecurityConfig();
            int count = secConf.GetTrustedCACount();
            std::string cAFiles;


            for(int i=0; i < count; i++)
            {
                its::CertificateAuthority* CA = secConf.GetTrustedCA(i);
                cAFiles.append((CA)->GetCertificateFileName());
                cAFiles.append(":");
            }

            std::string masterCA(MASTER_CA);

            DiaUtils::InitTrustedCAs(masterCA, caPath, cAFiles);
	//call the SetX509TrustFile using caPath
	if(cfg->GetSecurityConfig().GetOwnCertPath() != NULL)
            {
                ownCertPathClient.append(cfg->GetSecurityConfig().GetOwnCertPath());
                ownKeyPathClient.append(cfg->GetSecurityConfig().GetOwnCertPath());


                certFile = (char*) cfg->GetSecurityConfig().GetClientCertFile();
                ownCertPathClient.append(certFile);

                keyFile =  (char*) cfg->GetSecurityConfig().GetClientKeyFile();
                ownKeyPathClient.append(keyFile);
            }

            clientCertificate = tlsObj->CreateCertificate(CLIENT);
 //Pass this vector to EnableCrlCheck
  vector<its::CertificateAuthority*> CAPtr = secConf.GetCertificateAuthority();
            std::string crlPath = secConf.GetCrlPath();

            if(clientCertificate != NULL)
            {
                clientCertificate->SetX509TrustFile(MASTER_CA, caPath);
                if((clientCertificate->SetX509KeyFile(const_cast<char *>(ownCertPathClient.c_str()), 
                                const_cast<char *>(ownKeyPathClient.c_str()))) != 1)
                {
                    DT_ERR(("Error while loading Client certificate or key!"));
                }
                if(secConf.GetCrlVerify())
                {
                    int ret = clientCertificate->EnableCrlCheck(CAPtr, crlPath);
                    if(ret == ERRCLOOKOBJ)
                    {
                        DT_ERR(("Error in creating lookup object"));
                    }
                    else if(ret == ERRLCRLF)
                    {
                        DT_ERR(("Error in loading CRL file"));
                    }
                }
            }

            if(cfg->GetSecurityConfig().GetOwnCertPath() != NULL)
            {
                ownCertPathServer.append(cfg->GetSecurityConfig().GetOwnCertPath());
                ownKeyPathServer.append(cfg->GetSecurityConfig().GetOwnCertPath());

                certFile = (char*) cfg->GetSecurityConfig().GetServCertFile();
                ownCertPathServer.append(certFile);

                keyFile =  (char*) cfg->GetSecurityConfig().GetServKeyFile();
                ownKeyPathServer.append(keyFile);
            }

            serverCertificate = tlsObj->CreateCertificate(SERVER);

            if(serverCertificate != NULL)
            {
                serverCertificate->SetX509TrustFile(MASTER_CA, caPath);
                if((serverCertificate->SetX509KeyFile(const_cast<char *>(ownCertPathServer.c_str()), 
                                const_cast<char *>(ownKeyPathServer.c_str()))) != 1)
                {
                    DT_ERR(("Error while loading Server certificate or key!"));
                }
                if(secConf.GetCrlVerify())
                {
                    int ret = serverCertificate->EnableCrlCheck(CAPtr, crlPath);
                    if(ret == ITS_ENOMEM)
                    {
                        DT_ERR(("Error in creating lookup object"));
                    }
                    else if(ret == ITS_EIESNULL)
                    {
                        DT_ERR(("error in loading CRL file"));
                    }
                }
            }

            tlsObj->SetDebug(cfg->GetSecurityConfig().GetTLSTraceLevel());
        }
        else
        {
		printf("$$$$$$$ Failed to Initialize TLS Factory class Type = %s$$$\n",
                    DIA_TLS_TYPE_TO_TEXT(cfg->GetSecurityConfig().GetTlsType()));
            ITS_ASSERT(tlsObj != NULL);
        }
    }
   else
   {
  	DT_WRN(("DIA_TLS Disabled"));
   }
#else
   DT_DBG(("Tls Macro Not Defined"));
#endif
 return DIA_SUCCESS;
}

int
DiaStackClass::InitLocalTransports(bool activateStack)
{
    int ret;
    ITSDiaConfig* cfg = NULL;
    cfg = &itsDiaConfig;

    if (cfg == NULL)
    {
        DT_CRT(("InitLocalTransports::Invalid Configuration"));
        return (ITS_EINITFAIL);
    }

    DT_DBG(("DiaStackClass::InitLocalTransports"));

    numAcceptor = 0;

    for (int i = 0; i < cfg->GetHostInfoList().count; i++)
    {
        DT_DBG(("LocalHost: HostName = %s, Realm = %s",
                    cfg->GetHostInfoList().arr[i].servHostName,
                    cfg->GetHostInfoList().arr[i].realmName));

        for (int j = 0;
                j < cfg->GetHostInfoList().arr[i].transCnt;
                j++)
        {
            int type = cfg->GetHostInfoList().arr[i].transList[j].type;
            const char *ip = cfg->GetHostInfoList().arr[i].transList[j].serverIpAddr;
            ITS_USHORT port = 0;
            ITS_BOOLEAN startTLSFirst = false;
            if(cfg->GetHostInfoList().arr[i].transList[j].securePort &&
                type == ITS_DIA_T_TCP)
            {
                port = cfg->GetHostInfoList().arr[i].transList[j].securePort;
                DT_DBG(("Its a TLS Port %d",port));
                startTLSFirst = true;
            }
            else
            {
                port = cfg->GetHostInfoList().arr[i].transList[j].portNo;
            }

            const char **multiHomeipaddrs = cfg->GetHostInfoList().
                arr[i].transList[j].multiHomeipaddrs; // SCTP MultiHoming
            ITS_USHORT noIPs = cfg->GetHostInfoList().arr[i].transList[j].noIPs;

            DT_DBG(("HostInfo: Transport: Type = %d, IP Addr = %s, PortNo = %d\n",
                        type, ip, port));

            if (type == ITS_DIA_T_SCTP)
            {
                cfg->PrintStreamSocketConfig();
            }
            else if (type == ITS_DIA_T_TCP)
	    {
            cfg->PrintTcpSocketConfig();
	    }
            acceptor[numAcceptor] = NULL;
            accReader[numAcceptor] = NULL;
#if defined(linux) || !defined(USE_SELECT)
            DiaEpollSockContainer  *accEpollTbl = new DiaEpollSockContainer();//Create epoll container per transport
#endif
            try
            {
                if (type == ITS_DIA_T_TCP)
                {
                    DT_DBG(("Init TCP: IP Addr = %s, PortNo = %d\n",
                                ip, port));
#if !defined(linux) || defined(USE_SELECT)
                    acceptor[numAcceptor] = new DiaAcceptor(ITS_DIA_SERVER_SOCK_TRANS,activateStack);
#else
                    acceptor[numAcceptor] = new DiaAcceptor(ITS_DIA_SERVER_SOCK_TRANS,accEpollTbl,activateStack);
#endif 
                    if (acceptor[numAcceptor]->Initialize(ip, port) == ITS_SUCCESS)
                    {
                        /**
                         * Fix for issue No. 19 raised by Dhirananda.
                         * Printing appropriate error traces and normal
                         * exit.
                         */
                        if ((ret = acceptor[numAcceptor]->Start()) != ITS_SUCCESS)
                        {
                            DT_ERR(("Error while initiating thread request.:%d",
                                        ret));
                            exit(0);
                        }
                    }
                }
                else if (type == ITS_DIA_T_SCTP)
                {
                    DT_DBG(("Init SCTP: IP Addr = %s, PortNo = %d\n",
                                ip, port));
#if !defined(linux) || defined(USE_SELECT)
                    acceptor[numAcceptor] = new DiaAcceptor(ITS_DIA_SCTP_SERVER_SOCK_TRANS,activateStack);
#else
                    acceptor[numAcceptor] = new DiaAcceptor(ITS_DIA_SCTP_SERVER_SOCK_TRANS,accEpollTbl,activateStack);
#endif
                    if (acceptor[numAcceptor]->Initialize(ip, port, multiHomeipaddrs, noIPs)
                            == ITS_SUCCESS)  // SCTP MultiHoming
                    {
                        /**
                         * Fix for issue No. 19 raised by Dhirananda.
                         * Printing appropriate error traces and normal
                         * exit.
                         */
                        if ((ret = acceptor[numAcceptor]->Start()) != ITS_SUCCESS)
                        {
                            DT_ERR(("Error while initiating thread request:%d",
                                        ret));
                            exit(0);
                        }
                    }

                }
#if !defined(linux) || defined(USE_SELECT)
                accReader[numAcceptor] = new DiaAcceptorReader(startTLSFirst);
#else
                accReader[numAcceptor] = new DiaAcceptorReader(accEpollTbl,startTLSFirst);
#endif
                if ((ret = accReader[numAcceptor]->Start()) != ITS_SUCCESS)
                {
                    DT_ERR(("Error while initiating thread request.: %d",ret));
                    exit(0);
                }

            }
            catch(...)
            {
                if(type == ITS_DIA_T_TCP)
                {
                    DT_CRT(("Failed to Initialize Acceptor:Invalid Local Ip or IpAddress and Port already in use IP = %s :: Port = %d",ip,port));
                    DIA_Alarm(15200, __FILE__, __LINE__, "Invalid Local Ip or IpAddress and Port already in use IP = %s :: Port = %d",ip,port);
                }
                else
                {
                    char IpAddrs[512]={'\0'};
                    for(int i=0;i<noIPs;i++)
                    {
                        strcat(IpAddrs,multiHomeipaddrs[i]);
                        strcat(IpAddrs,"  ");
                    } 
                    DT_CRT(("Failed to Initialize Acceptor:Invalid Local Ip or IpAddress and Port already in use IP = %s :: Port = %d",IpAddrs,port));
                    DIA_Alarm(15200, __FILE__, __LINE__, "Invalid Local Ip or IpAddress and Port already in use IP = %s :: Port = %d",IpAddrs,port);
                }
		// Stopping all the acceptors
		for(int index=0;index<numAcceptor;index++)
		{
			if (acceptor[index])
	                {
			    acceptor[index]->SetExit();
	                }
	                if (accReader[index])
	                {
	                    accReader[index]->SetExit();
	                }

		}
		sleep(1);
		for(int index=0;index<numAcceptor;index++)
		{
			if (acceptor[index])
	                {
	                    delete acceptor[index];
	                    acceptor[index] = NULL;
	                }
	                if (accReader[index])
	                {
	                    delete accReader[index];
	                    accReader[index] = NULL;
	                }

		}
		numAcceptor=0;
                return (!ITS_SUCCESS);
            }
            numAcceptor++;
        }
    }

    // Starting the WatchDog Thread.
    /**
     * Fix for issue No. 19 raised by Dhirananda.
     * Printing appropriate error traces and normal
     * exit.
     */
    if (!watchDogTransport)
    {
        watchDogTransport = new DiaWatchDogTransport(activateStack);
    }
    if ((ret = watchDogTransport->Start()) != ITS_SUCCESS)
    {
        DT_ERR(("Error while initiating thread request.: %d",ret));
        exit(0);
    }
    return (ITS_SUCCESS);
}

int
DiaStackClass::InitPeerTransports(bool activateStack)
{
    int ret;
    ITSDiaConfig *cfg = NULL;
    connector = NULL;
    connReader = NULL;

    cfg = &itsDiaConfig;
    if (cfg == NULL)
    {
        DT_CRT(("InitLocalTransports::Invalid Configuration"));
        return (ITS_EINITFAIL);
    }

    DT_DBG(("DiaStackClass::InitPeerTransports"));

    try
    {
        connector = new DiaConnector(ITS_DIA_CLIENT_SOCK_TRANS,activateStack);
        if (connector)
        {
            connector->CopyIpAddresses();
            if ((ret = connector->Start()) != ITS_SUCCESS)
            {
                DT_ERR(("Error while initiating thread request.: %d",ret));
                exit(0);
            }
        }
        else
        {
            DT_ERR(("Error while initiating thread request.: %d",ret));
            exit(0);
        }

        connReader = new DiaConnectorReader;
        if (connReader)
        {
            if ((ret = connReader->Start()) != ITS_SUCCESS)
            {
                DT_ERR(("Error while initiating thread request.: %d",ret));
                exit(0);
            }
        }
        else
        {
            DT_ERR(("Error while initiating thread request.: %d",ret));
            exit(0);
        }
    }
    catch (...)
    {
        DT_ERR(("Failed to Initialize Connector:"));
        if (connector)
        {
            delete connector;
            connector = NULL;
        }
        if (connReader)
        {
            delete connReader;
            connReader = NULL;
        }
    }
    return (ITS_SUCCESS);
}

/*int
DiaStackClass::TermLocalTransports()
{
    if (connector)
    {
        connector->SetExit();
        //connector->Kill();
        delete connector;
        connector = NULL;
    }

    if (connReader)
    {
        connReader->SetExit();
        //connReader->Kill();
        delete connReader;
        connReader = NULL;
    }

    for (int idx = 0; idx < numAcceptor; idx++)
    {
        if (acceptor[idx])
        {
            acceptor[idx]->SetExit();
            //acceptor[idx]->Kill();
            delete acceptor[idx];
            acceptor[idx] = NULL;
        }

        if (accReader[idx])
        {
            accReader[idx]->SetExit();
            //accReader[idx]->Kill();
            delete accReader[idx];
            accReader[idx] = NULL;
        }
    }

    numAcceptor = 0;
*/
    /**
     * Exiting the WatchDog Transport and
     * deleting the transport Object
     */
   /* if (watchDogTransport)
    {
        watchDogTransport->SetExit();
        delete watchDogTransport;
        watchDogTransport = NULL;
    }


    return (ITS_SUCCESS);
}*/

int DiaStackClass::GoActive()
{
    int retVal = ITS_SUCCESS;

    if(started)
    {
        DT_DBG(("Activating Transport Threads"));
        //DeActivate Transport Threads so that no new connections are accepeted.

        if(this->ActivateTransportThreads() != ITS_SUCCESS)
        {
            DT_ERR(("Failed to Activate Transport Threads"));
            retVal = !(ITS_SUCCESS);
        }
        else
        {
            DT_DBG(("Successfully Activated Transport Threads"));
        }
    }

    return retVal; 
}

int DiaStackClass::ActivateTransportThreads()
{

    int id = 0;
    //Activate All Acceptors to start accepting new connections.
    for(id; id < numAcceptor ; id++)
    {
        acceptor[id]->Activate();
    }

    //Activate Connector to start connecting to Peers.
    connector->Activate();

    //Activate  WatchDog Thread.
    watchDogTransport->Activate();
    return ITS_SUCCESS;
}

int DiaStackClass::GoStandby()
{
    int retVal = ITS_SUCCESS;

    DT_DBG(("Terminating Peer Transports"));
    //Terminate Peer Transports.

    if(started)
    {
        if(this->DeActivateTransportThreads() != ITS_SUCCESS)
        {
            DT_ERR(("Failed to DeActivate Transport Threads"));
            retVal = !(ITS_SUCCESS);
        }
        else
        {
            DT_DBG(("Successfully DeActivated Transport Threads"));
        }

        if(this->TermTransports(true) != ITS_SUCCESS)
        {
            DT_ERR(("Failed to Terminate Peer Transports"));
            retVal = !(ITS_SUCCESS);
        }
        else
        {
            DT_DBG(("Successfully Terminated Peer Transports"));
        }

        DT_DBG(("DeActivating Transport Threads"));
        //DeActivate Transport Threads so that no new connections are accepeted.

    }

    return retVal; 
}

int DiaStackClass::DeActivateTransportThreads()
{
    int id = 0;
    //DeActivate All Acceptors to drop any new connection
    //that are accepted.
    for(id; id < numAcceptor ; id++)
    {
        if(acceptor[id])
        {
            acceptor[id]->DeActivate();
        }
    }

    //DeActivate Connector to stop connecting to Peers.
    if(connector)
    {
        connector->DeActivate();
    }

    //DeActivate watchdog thread
    if(watchDogTransport)
    {
        watchDogTransport->DeActivate();
    }
    return ITS_SUCCESS;
}

int
DiaStackClass::TermTransports(bool cleanUpSockets)
{
    int i, ret;
    DiaSocketTransport *tr = NULL;
    PEER_ENTRY *peer = NULL;
    ITS_USHORT evtType = PEER_EVT_STOP;

    PEER_ENTRY *entry = PeerTable::GetPeerTable()->FindFirstEntry();
    while (entry != NULL)
    {
        ITS_USHORT inst = DIA_PE_INST(entry);
        tr = trTable[inst];
        if (tr != NULL)
        {
            peer = tr->GetPeer();
            if ((peer != NULL) &&
                (DIA_PE_STATE(peer) == PEER_ST_I_OPEN ||
                 DIA_PE_STATE(peer) == PEER_ST_R_OPEN))
            {
                if ((ret = DiaMsgRouter::UpdatePeerSM(NULL, peer,
                                                      evtType,
                                                      tr, NULL)) != ITS_SUCCESS)
                {
                    DT_ERR(("Failed to send DPR = %d", ret));
                }
            }
        }
        entry = PeerTable::GetPeerTable()->FindNextEntry(entry);
    }

    /* Hold off for a second, to allow responses
       from peers
    */
    TIMERS_Sleep(1);

    const_cast<ITS_Mutex&>(__TIGate).Acquire();

    for (i = 1; i < MAX_LOCAL_TRANSPORTS; i++)
    {
        if (trTable[i] != NULL)
        {
            // delete trTable[i];
            // trTable[i] = NULL;
            trTable[i]->SetExit();
            //Clean Up Sockets if specified
            //This will call Close on sockets.
            if(cleanUpSockets)
            {
                //delete trTable[i];
                DiaSocketTransport *tr1 = trTable[i];
                delete tr1;
                trTable.SetToNULL(i);
            }
        }
    }
    const_cast<ITS_Mutex&>(__TIGate).Release();

    return (ITS_SUCCESS);
}

int
DiaStackClass::StopAcceptors()
{
    for(int id = 0; id < numAcceptor ; id++)
    {
        if(acceptor[id])
        {
            acceptor[id]->SetExit();
        }

        if(accReader[id])
        {
            accReader[id]->SetExit();
        }
    }

   return (ITS_SUCCESS);
}

int
DiaStackClass::StopConnectors()
{
    if(connector)
    {
        connector->SetExit();
    }

    if(connReader)
    {
        connReader->SetExit();
    }

   return (ITS_SUCCESS);
}

int
DiaStackClass::StopWatchdog()
{
    if(watchDogTransport)
    {
        watchDogTransport->SetExit();
    }
}


int DiaStackClass::enableReplication()
{
    SessionTable::replicateSessions = true;
}

int DiaStackClass::disableReplication()
{
    SessionTable::replicateSessions = false;
}

int DiaStackClass::registerCreateSessionReplicationCbk(createSessionCbk createCbk)
{
    if(createCbk != NULL)
        SessionTable::sessCreateCbk = createCbk;
}

int DiaStackClass::registerUpdateSessionReplicationCbk(updateSessionCbk updateCbk)
{
    if(updateCbk != NULL)
        SessionTable::sessUpdateCbk = updateCbk;
}

int DiaStackClass::registerDeleteSessionReplicationCbk(deleteSessionCbk deleteCbk)
{
    if(deleteCbk != NULL)
        SessionTable::sessDeleteCbk = deleteCbk;
}

int DiaStackClass::registerFetchSessionReplicaCbk(fetchSessionCbk fetchCbk)
{
    if(fetchCbk != NULL)
        SessionTable::sessFetchCbk = fetchCbk;
}

int DiaStackClass::ReCreateSessionEntry(string& sessionId, ITS_EVENT& event)
{
    int retVal = ITS_SUCCESS;
    ITS_USHORT dest = DIASTACK_TQ_INST;

    DT_DBG(("DiaStackClass::ReCreateSessionEntry - entry"));
    if (itsDiaConfig.IsQueueMgmtEnabled())
    {
        dest = DIASTACK_SENDER_TQ_INST;
    }   

    dest = DiaUtils::GetStackTQInst(sessionId.c_str());

    //retVal = TRANSPORT_PutEvent(dest, &event);
    Event ev(&event);
    retVal = its::Transport::PutEvent(dest, ev);
    if (retVal == ITS_SUCCESS)
    {
        DT_DBG(("Successfully posted replication event to recreate Session entry"));
    }
    else
    {
        DT_DBG(("Failed to Post the replication event to recreate Session entry"));
    }

    DT_DBG(("DiaStackClass::ReCreateSessionEntry - entry"));

    return retVal;
}


ITSSS7DLLAPI void
NodeStateChangeCallback(ITS_POINTER object,
                   ITS_POINTER userData,
                   ITS_POINTER callData)
{
    /**
     * Fix for Whizibile Issue ID 1292.getNodeState and switchOver
     * MML commands are not working for Active-Cold Standby.
     */
    ITSDiaConfig *cfg = &itsDiaConfig;
    if ( !cfg->IsRedundancyEnabled() )
    {
        cfg->setRedundancyEnabled();
        DT_DBG(("NodeStateChangeCallback:: Redundancy is enabled"));
    }

    DT_DBG(("Redundancy :  NodeStateChangeCallback is called\n"));
    //Membership change callback handling
    DSM_MembershipChangeCbData *membershipChangeCbData =
                     (DSM_MembershipChangeCbData *) callData;
    ITS_USHORT concernedNodeId = membershipChangeCbData->memberNodeId;
    switch (membershipChangeCbData->membershipChangeType)
    {
       case DSM_FT_GROUP_COMM_LOST:
            DT_DBG(("Redundancy : Communication lost with nodeID %d\n",
                  concernedNodeId));
           //change state to active if current state is backup
           //this change is mandatory because at present GCS client
           //doesn't detect communication loss and change backup to active
           ITS_NODE_STATE state;
           if ((ITS_GetNodeState(&state) == ITS_SUCCESS)
              && state != ITS_STATE_PRIMARY)
           {
              ITS_SendStateChangeEventToStack(ITS_STATE_PRIMARY);
           }
           break;

       case DSM_FT_GROUP_MEMBER_JOIN:
           if (DSM_GetNodeId() != membershipChangeCbData->memberNodeId)
           {
               if (membershipChangeCbData->numFtGroupMembers == 2)
               {
                    /* Joined node is Mate. Change the flag to true. */
                    DT_DBG(("Mate Node Joined is ACTIVE"));
                    isActiveUpOrJoined = ITS_TRUE;
                    break;
                }
            }
            else
            {
                DT_DBG(("Joined node is self. Ignoring..\n"));
            }
       break;

       case ITS_STATE_CHANGE_EVENT:
           if (DSM_GetNodeId() != membershipChangeCbData->memberNodeId)
           {
               DT_DBG(("Mate Node is present\n"));
               if (!isActiveUpOrJoined)
                   isActiveUpOrJoined = ITS_TRUE;
               break;
           }
       break;

       default :
           return;
           //don't do anything
    }
}

ITSSS7DLLAPI void
RedundancyConfigCallback(ITS_POINTER ptr, ITS_POINTER ptr1, ITS_POINTER evtData)
{
   DT_DBG(("Redundancy : config callback\n"));
   ITS_HDR hdr;
   ITS_EVENT* evt  = (ITS_EVENT *)evtData;

   /**
    * Changing the source of the event from ITS_RED_MODULE_SRC to
    * DIA_REDUNDANCY_SRC. These Events are handled separately at IDS.
    */
   evt->src        = DIA_REDUNDANCY_SRC;

   memset((char*)&hdr, 0, sizeof(ITS_HDR));
   /* submit the redundancy related event to the application
    * application should check the source and handle
    * the event*/
    if (itsDiaConfig.IsDistScenario())
    {
        /* If Callback is registered from IDS No need of PutEvent */
        if (IDSRedundancyCallBack != NULL)
        {
            IDSRedundancyCallBack(evt);
            return ;
        }
    }
    else
    {
        ITS_USHORT dest = ROUTE_SelectApplication(&hdr, evt, ITS_TRUE);
        if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
        {
            Event ev(evt);
            if (its::Transport::PutEvent(dest, ev) == ITS_SUCCESS)
            {
                DT_DBG(("DiaStack: Sent Message to Application = %d\n", dest));
            }
        }
        else
        {
            DT_ERR(("Incoming - No Route to Application\n"));
        }
    }
}

void
CheckBackupNode()
{

    DT_DBG(("********Redundant Setup Enabled********"));
    if ((ITS_GetNodeState(&state) == ITS_SUCCESS)
       && (state != ITS_STATE_PRIMARY))
    {
        DT_DBG(("Host NODE_STATE is: \"%s\"", state?"BACKUP":"ACTIVE"));
        signal(SIGINT,SIG_DFL);
        DT_DBG(("Waiting for:Host Node to Become ACTIVE  OR " \
                           " Mate Node to Send ALIVE/JOIN"));
        while ((state != ITS_STATE_PRIMARY) && (!isActiveUpOrJoined))
        {
            TIMERS_Sleep(1);
            ITS_GetNodeState(&state);
        }
    }

}
void HMICallbackFunc(ITS_POINTER object,
                ITS_POINTER userData,
                ITS_POINTER callData)
{
    if(itsDiaConfig.IsHMIEnabled())
    {
        ITS_BOOLEAN rawThread = (ITS_BOOLEAN)*object;
        if (callData != NULL)
        {
            HMIThread_Info* thInfo= (HMIThread_Info*) callData;
            TRANSPORT_Control* ent =(TRANSPORT_Control*) callData;

            if((rawThread == ITS_TRUE) && thInfo->tName)
            {
                 DIA_TRACE_CRITICAL((" Hung Thread ::  %s \n", thInfo->tName));
                 DIA_Alarm(15350, __FILE__, __LINE__, "Hung Raw Thread  = %s", thInfo->tName);
            }
            else
            {
                 if(!strcmp(TRANSPORT_NAME(ent),"MSG Queue") == 0)
                 {
                     DIA_TRACE_CRITICAL((" Hung Transport Thread:: %s \n", TRANSPORT_NAME(ent)));
                     DIA_Alarm(15350, __FILE__, __LINE__, "Hung Transport Thread  = %s", TRANSPORT_NAME(ent));
                 }
            }
        }
    }
}

void
OverLoadCallbackFunc(ITS_POINTER object,
                ITS_POINTER userData,
                ITS_POINTER callData)
{
    if (callData != NULL)
    {
        overLoadF = (bool)callData;
        if( overLoadF == ITS_TRUE )
        {
            DiaMsgRouter::SendIndication( NULL,NULL, 0, OVERLOAD_IND_FROM_STACK);
            DIA_Alarm(15305, __FILE__, __LINE__, "overload");
        }
    }
    else
    {
        DiaMsgRouter::SendIndication( NULL,NULL, 0, OVLD_ABATED_IND_FROM_STACK);
        DIA_Alarm(15305, __FILE__, __LINE__, "overloadAbated");
    }
}

void HMIHeartbeatCBFunc(ITS_POINTER object,
                      ITS_POINTER userData,
                      ITS_POINTER callData)
{
    if(itsDiaConfig.IsHMIEnabled())
    {
        DIA_TRACE_DEBUG(("HMI Heartbeat Msg"));
        DIA_Alarm(15450, __FILE__, __LINE__, "HMI Hearbeat Message");
    }
}

