/*********************************-*-CPP-*-**********************************
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
 * LOG: $Log: dia_peer_states.cpp,v $
 * LOG: Revision 3.59.2.1.2.8.4.12.2.1.2.6.14.3  2020/02/14 11:36:11  jkchaitanya
 * LOG: TCP Timeout fix ported from DRE
 * LOG:
 * LOG: Revision 3.59.2.1.2.8.4.12.2.1.2.6.14.2  2017/12/21 04:37:21  jkchaitanya
 * LOG: Ticket 1149 changes to support case insensitivity for peers, hosts 7 realms
 * LOG:
 * LOG: Revision 3.59.2.1.2.8.4.12.2.1.2.6.14.1  2015/04/02 12:59:05  jkchaitanya
 * LOG: Changes made for handling peer notifications to app
 * LOG:
 * LOG: Revision 3.59.2.1.2.8.4.12.2.1.2.6  2013/12/13 09:34:58  vsarath
 * LOG: Merged the session-splict changes
 * LOG:
 * LOG: Revision 3.59.2.1.2.8.4.12.2.1.2.5  2013/12/09 04:52:26  ncshivakumar
 * LOG: Fixed bug 2439,2443,2368,1898
 * LOG:
 * LOG: Revision 3.59.2.1.2.8.4.12.2.1.2.4  2013/11/14 08:54:54  ncshivakumar
 * LOG: RFC6733 changes
 * LOG:
 * LOG: Revision 3.59.2.1.2.8.4.12.2.1.2.3  2013/10/26 13:31:59  ncshivakumar
 * LOG: Updated for RFC6733
 * LOG:
 * LOG: Revision 3.59.2.1.2.8.4.12.2.1.2.2  2013/10/26 07:42:21  ncshivakumar
 * LOG: RFC 6733 changes
 * LOG:
 * LOG: Revision 3.59.2.1.2.8.4.12.2.1.2.1  2013/09/10 08:36:39  ncshivakumar
 * LOG: RFC6733 Changes
 * LOG:
 * LOG: Revision 3.59.2.1.2.8.4.12.2.1  2013/05/22 09:59:50  ncshivakumar
 * LOG: Merged from 300 Branch
 * LOG:
 * LOG: Revision 3.59.2.1.2.8.4.13  2013/04/25 06:59:54  millayaraja
 * LOG: updated the macro for transport stats which was getting updated wrongly
 * LOG:
 * LOG: Revision 3.59.2.1.2.8.4.12  2013/04/18 13:19:08  millayaraja
 * LOG: updated peer transport stats
 * LOG:
 * LOG: Revision 3.59.2.1.2.8.4.11  2013/04/18 07:04:31  jvikram
 * LOG: Included changes relatd to log segregation.
 * LOG:
 * LOG: Revision 3.59.2.1.2.8.4.10  2013/04/12 04:17:55  vsarath
 * LOG: Logs improvement
 * LOG:
 * LOG: Revision 3.59.2.1.2.8.4.9  2013/04/04 09:07:48  mallikarjun
 * LOG: MemLeak Fixes Bug 1361
 * LOG:
 * LOG: Revision 3.59.2.1.2.8.4.8  2013/04/01 05:57:11  vsarath
 * LOG: Fix for Coverity warnings
 * LOG:
 * LOG: Revision 3.59.2.1.2.8.4.7  2013/03/14 09:39:26  vsarath
 * LOG: Reverting back the delete[] for coverity fix
 * LOG:
 * LOG: Revision 3.59.2.1.2.8.4.6  2013/03/12 09:34:26  vsarath
 * LOG: Fix for coverity issues
 * LOG:
 * LOG: Revision 3.59.2.1.2.8.4.5  2013/03/12 04:50:36  vsarath
 * LOG: Fix for coverity issue
 * LOG:
 * LOG: Revision 3.59.2.1.2.8.4.4  2013/03/06 08:31:00  jvikram
 * LOG: BUGID=1016, 1027, 803. Fixed the specified bugs.
 * LOG:
 * LOG: Revision 3.59.2.1.2.8.4.3  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.59.2.1.2.8.4.2  2013/02/12 05:45:19  vsarath
 * LOG: Changes for TLS enable/disable
 * LOG:
 * LOG: Revision 3.59.2.1.2.8.4.1  2013/02/01 11:34:15  pramana
 * LOG: Merged from branch 0212 to 0300.
 * LOG:
 * LOG: Revision 3.59.2.1.2.10  2013/01/25 02:56:44  mallikarjun
 * LOG: Bug-PeerConn-Stats
 * LOG:
 * LOG: Revision 3.59.2.1.2.9  2013/01/18 05:35:46  cprem
 * LOG: Fix for bugs 936,937.Handling Error CER in WAIT_CONN_ACK
 * LOG:
 * LOG: Revision 3.59.2.1.2.8  2013/01/04 06:59:47  millayaraja
 * LOG: modified to update Error stats
 * LOG:
 * LOG: Revision 3.59.2.1.2.7  2012/12/19 09:02:23  mallikarjun
 * LOG: Bug 741 changes
 * LOG:
 * LOG: Revision 3.59.2.1.2.6  2012/12/06 08:32:11  jsarvesh
 * LOG: changes done for CER increment
 * LOG:
 * LOG: Revision 3.59.2.1.2.5  2012/11/20 17:39:44  pramana
 * LOG: Merged from CMAPI branch for 212-07 release
 * LOG:
 * LOG: Revision 3.59.2.1.2.2.16.3  2012/11/20 10:31:24  rgovardhan
 * LOG: merge from 00 Nov20Rel
 * LOG:
 * LOG: Revision 3.59.2.1.2.2  2012/09/06 11:30:46  jvikas
 * LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
 * LOG:
 * LOG:
 * LOG: Revision 3.59.2.3  2012/08/01 07:55:28  millayaraja
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 3.59.2.2  2012/07/26 08:13:57  millayaraja
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 3.59.2.1.4.3  2012/08/28 03:49:54  cprem
 * LOG: Added includes for json.
 * LOG:
 * LOG: Revision 3.59.2.1.4.2  2012/08/22 12:53:43  jvikas
 * LOG: Fixed Linking Errors and Included XML Config for Transformation.
 * LOG:
 * LOG: Revision 3.59.2.1.4.1  2012/08/21 06:16:25  jvikas
 * LOG: Checkin Working Modified Stack Code -Need to Cleanup and Fix Issues.
 * LOG:
 * LOG: Revision 3.59.2.1.2.1  2012/08/21 08:55:57  ksalil
 * LOG: Merge from branch B-DRE-IDIA-0100-00
 * LOG:
 * LOG: Revision 3.59.2.1  2012/03/07 13:23:08  brajappa
 * LOG: Changes made for the DRE demo
 * LOG:
 * LOG: Revision 3.59  2011/07/14 14:04:51  vkumara
 * LOG: ForceDisconnect Requirement - Not to initiate connection.
 * LOG:
 * LOG: Revision 3.58  2011/07/04 09:17:20  nvijikumar
 * LOG: Fix for disabling connection initiation issue.
 * LOG: Connection initiation flag is checked before starting RETRY timer
 * LOG:
 * LOG: Revision 3.57  2011/06/24 09:15:20  rajeshak
 * LOG: Fix for Motorola (PSG) remove peer issue
 * LOG:
 * LOG: Revision 3.56  2010/12/14 00:37:57  nvijikumar
 * LOG: DO_NOT_WANT_TO_TALK_TO_YOU discCause implimentation
 * LOG:
 * LOG: Revision 3.55  2010/10/05 05:54:40  nvijikumar
 * LOG: Start RETRY timer after Expiry timeout in Closing State
 * LOG:
 * LOG: Revision 3.54  2010/08/19 11:21:27  nvijikumar
 * LOG: Porting changes from B-MOTO-IDIA-0421-00
 * LOG: 1. New Overload implimentation changes are not being ported.
 * LOG: 2. Force disconnect changes are not being ported.
 * LOG:
 * LOG: Revision 3.53  2009/11/26 08:44:14  sureshj
 * LOG: Alarm not reported CER sent & CEA not received from Peer.
 * LOG: Motorola ticket 2271.
 * LOG:
 * LOG: Revision 3.52  2009/08/31 05:55:07  rajeshak
 * LOG: New Alarm for Connection close after DPA sent/receive (AlarmID:15010).
 * LOG:
 * LOG: Revision 3.51  2009/08/28 08:57:57  rajeshak
 * LOG: Fix for Issue:2334 (IDS do not retry to establish connection with Peer)
 * LOG: Peer Connection Init Flag is made false only after accepting CER.
 * LOG:
 * LOG: Revision 3.50  2009/08/28 07:00:35  sureshj
 * LOG: E bit is set in the DWA IDS is dumping core. Motorola issue 2206.
 * LOG: E bit handling in DPA, CEA, DWA.
 * LOG:
 * LOG: Revision 3.49  2009/08/20 09:29:59  rajeshak
 * LOG: Added separate AlarmID for Result code failure for CEA/DWA/DPA.
 * LOG:
 * LOG: Revision 3.48  2009/08/14 08:10:18  rajeshak
 * LOG: Passing commandi code in Alarm Test for CEA/DWA/DPA failed Result Code.
 * LOG:
 * LOG: Revision 3.47  2009/07/13 06:46:21  rajeshak
 * LOG: Reverting back session table changes.
 * LOG:
 * LOG: Revision 3.46  2009/06/29 14:54:53  rajeshak
 * LOG: Changes done for performance enhancement (splitting the session table).
 * LOG:
 * LOG: Revision 3.45  2009/04/14 08:56:22  rajeshak
 * LOG: Remove PeerEntry changed for peers in Open state after TTL Timeout.
 * LOG:
 * LOG: Revision 3.44  2009/04/13 13:36:57  rajeshak
 * LOG: Peer Discovery changes.
 * LOG:
 * LOG: Revision 3.43  2009/03/25 14:03:01  rajeshak
 * LOG: Fix for Issue 1637 (Core dumps on receiving DPR message)
 * LOG:
 * LOG: Revision 3.42  2009/03/25 12:46:38  sureshj
 * LOG: Alarm raised when CEA received and no common appId matching,
 * LOG: and when failed DPA received with result code not Success.
 * LOG:
 * LOG: Revision 3.41  2009/03/20 11:03:31  chandral
 * LOG: Fix for compilation issue with TLS
 * LOG:
 * LOG: Revision 3.40  2009/03/19 13:42:26  nvijikumar
 * LOG: Porting from 3.2 branch
 * LOG:
 * LOG: Revision 3.39  2009/03/19 13:29:52  sureshj
 * LOG: check for FirmwareRevision added
 * LOG:
 * LOG: Revision 3.38  2009/03/19 12:38:15  nvijikumar
 * LOG: Global instance is created for the Class ITSDiaConfig to avoid function
 * LOG: call overhead as ITSDiaConfig::GetITSDiaConfig() was called max time
 * LOG:
 * LOG: Revision 3.37  2009/03/19 11:29:00  rajeshak
 * LOG: Memory leak fix for error scenario.
 * LOG:
 * LOG: Revision 3.36  2009/03/19 10:52:50  nvijikumar
 * LOG: Fix for Issue Id 1749
 * LOG: Disconnect if local and remote Identities are same
 * LOG:
 * LOG: Revision 3.35  2009/03/19 05:33:43  sureshj
 * LOG: Result Code other than SUCCESS triggers an alarm.
 * LOG:
 * LOG: Revision 3.34  2009/03/12 07:11:00  nvijikumar
 * LOG: Used PutEventReference to aviod malloc and memcpy
 * LOG:
 * LOG: Revision 3.33  2009/03/06 07:02:22  nvijikumar
 * LOG: Reverting back evt reference changes as no difference found w.r.t tps
 * LOG:
 * LOG: Revision 3.32  2009/03/03 11:17:20  rajeshak
 * LOG: Klockwork reported issue fix
 * LOG:
 * LOG: Revision 3.31  2009/03/03 10:27:27  nvijikumar
 * LOG: Using PutEventReference() API Performance changes
 * LOG:
 * LOG: Revision 3.30  2009/01/09 10:22:18  rajeshak
 * LOG: Klockwork reported issue fix.
 * LOG:
 * LOG: Revision 3.29  2009/01/03 05:48:52  rajeshak
 * LOG: Introduced common func to send all indications
 * LOG:
 * LOG: Revision 3.28  2008/12/26 09:58:41  chandrashekharbs
 * LOG: Fix for issue 1399
 * LOG:
 * LOG: Revision 3.27  2008/12/23 09:36:12  nvijikumar
 * LOG: Alarm 15002 support
 * LOG: 15002: Transport connection failure with peer
 * LOG:
 * LOG: Revision 3.26  2008/12/12 16:34:51  nvijikumar
 * LOG: Raising Alarms
 * LOG:
 * LOG: Revision 3.25  2008/12/12 12:29:02  nvijikumar
 * LOG: Peg increment is moved to common place
 * LOG:
 * LOG: Revision 3.24  2008/12/12 08:02:50  sureshj
 * LOG: Support for Stack statistics
 * LOG:
 * LOG: Revision 3.23  2008/12/01 07:13:56  sureshj
 * LOG: Updats to send proper disconnect cause with DPR
 * LOG:
 * LOG: Revision 3.22  2008/11/05 13:59:45  sureshj
 * LOG: Release 3.1.1 feature
 * LOG: Peer Connection Status Information
 * LOG:
 * LOG: Revision 3.21  2008/10/31 06:02:42  nvijikumar
 * LOG: IssueID:none
 * LOG: FeatureID:none
 * LOG: Description: Code cleanup
 * LOG:
 * LOG: Revision 3.20  2008/09/10 04:51:48  ssaxena
 * LOG: Fix for whizibile Issue Id 1144. Added check before sending Failover and
 * LOG: Failback Indication.
 * LOG:
 * LOG: Revision 3.19  2008/09/08 11:27:16  ssaxena
 * LOG: Fix for whizibile Issue Id 1138.
 * LOG:
 * LOG: Revision 3.18  2008/09/08 09:33:01  sureshj
 * LOG:  Fix for the Whizible issue 990.After TLS Handshake at server failed, on
 * LOG:  receiving R-Conn-CER in CLOSED state application dumps core.
 * LOG:
 * LOG: Revision 3.17  2008/09/02 17:05:14  ssaxena
 * LOG: Changes made to provide partial fix for whizible issue ID: 1119.
 * LOG:
 * LOG: Revision 3.16  2008/08/28 04:39:01  ssaxena
 * LOG: Modify disCause value as 0 in sendIndToApp.
 * LOG:
 * LOG: Revision 3.15  2008/08/25 05:34:48  ssaxena
 * LOG: 1. Failback Indication to Application
 * LOG: 2. Initiate Failover on receival of DISCONNECT trigger
 * LOG:
 * LOG: Revision 3.14  2008/08/21 06:25:39  nvijikumar
 * LOG: Memory leak fixes
 * LOG:
 * LOG: Revision 3.13  2008/08/18 11:27:10  vnarang
 * LOG: ISSUE 1098: Fix TlsFactoryClass * tlsObj should be initialized to NULL & Check for tlsObj for NULL should be after calling GetInstance
 * LOG:
 * LOG: Revision 3.12  2008/08/18 09:24:40  vnarang
 * LOG: Removing Problem while unit testing
 * LOG:
 * LOG: Revision 3.11  2008/08/07 14:41:23  vnarang
 * LOG: Defect 1088, Avoid Dump while Verification of certificates at server
 * LOG:
 * LOG: Revision 3.10  2008/08/07 09:17:40  sureshj
 * LOG: Compilation flag APP_ID_EXCLUSIVE added to disable the check
 * LOG: for vendorId and Supported VendorId.
 * LOG:
 * LOG: Revision 3.9  2008/07/23 13:52:07  ssaxena
 * LOG: Added Disconect Cause in Disconect indication
 * LOG:
 * LOG: Revision 3.8  2008/07/11 07:21:12  vnarang
 * LOG: Removing Compilation Error
 * LOG:
 * LOG: Revision 3.7  2008/07/09 14:00:14  vnarang
 * LOG: Using New Tls Class API integrated for GNU TLS & OPEN SSL & Adding Copilation option
 * LOG:
 * LOG: Revision 3.6  2008/06/13 11:45:10  hbhatnagar
 * LOG: Added functionality to implement TLS Client and server Procedures and related changes
 * LOG:
 * LOG: Revision 3.5  2008/04/23 17:00:45  hbhatnagar
 * LOG: Provided fix for the issue 902 in whizible where we check the
 * LOG: RelayAppId while processing CEA
 * LOG:
 * LOG: Revision 3.4  2008/04/11 18:46:55  hbhatnagar
 * LOG: Fix for the issue 779 in whizible for relay AppId.
 * LOG:
 * LOG: Revision 3.3  2008/04/07 18:46:09  hbhatnagar
 * LOG: Using a macro in place of magic number 0xffffffff.
 * LOG:
 * LOG: Revision 3.2  2008/04/01 16:38:53  hbhatnagar
 * LOG: Changes for Proxy and Relay support 3.0 release - (Viji, Hemant)
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:32  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.37  2008/03/27 12:14:08  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.32.2.18  2008/01/11 05:39:02  avinashks
 * LOG: Changes done for compilation issue due to missing braces in case statement.
 * LOG:
 * LOG: Revision 2.32.2.17  2008/01/10 14:54:03  hbhatnagar
 * LOG: Changes made to provide some additional traces and properly updating
 * LOG: Instance in WaitReturns state. Also closing the acceptor in case of
 * LOG: Expiry timeout.
 * LOG:
 * LOG: Revision 2.32.2.16  2008/01/10 14:03:44  avinashks
 * LOG: Changes made to provide fix for issue no 28 raised by Dhiranand
 * LOG: during the validation of Bridgewater ticket 1836.
 * LOG:
 * LOG: Revision 2.32.2.15  2008/01/07 20:17:01  hbhatnagar
 * LOG: Proper Handling of I-PEER-DISC and R-PEER-DISC in respective
 * LOG: states.
 * LOG:
 * LOG: Revision 2.32.2.14  2008/01/07 17:03:06  hbhatnagar
 * LOG: Changes made to provide fix for issue no 25(After Election) raised
 * LOG: by Dhiranand during the validation of Bridgewater ticket 1836.
 * LOG:
 * LOG: Revision 2.32.2.13  2008/01/07 15:18:50  avinashks
 * LOG: Added some debug prints for clarity.
 * LOG:
 * LOG: Revision 2.32.2.12  2007/12/22 15:54:06  hbhatnagar
 * LOG: Added Expiry timer for Closing state as we send the DPR in STOP
 * LOG: Event. Fix for issue no.2 (Case 5 in peer state machine) raised
 * LOG: by Dhiranand during the validation of bcgi ticket 1807.
 * LOG:
 * LOG: Revision 2.32.2.11  2007/12/16 06:02:56  hbhatnagar
 * LOG: Made changes to provide fix for the issues No. 2,4,5,6 and 10 raised
 * LOG: during the validation of bcgi ticket 1807.
 * LOG:
 * LOG: Revision 2.32.2.10  2007/12/14 11:24:48  hbhatnagar
 * LOG: Removed the DeviceWatchDog Timer related functionality and added
 * LOG: WatchDog Transport Thread related functionality.
 * LOG:
 * LOG: Revision 2.32.2.9  2007/11/22 14:26:06  hbhatnagar
 * LOG: Updated the current handle and Instance with acceptor specs appopriately.
 * LOG:
 * LOG: Revision 2.32.2.8  2007/06/18 15:16:04  nvijikumar
 * LOG: Start EXPIRY timer when START evt triggered.
 * LOG: Stop EXPIRY timer when peer goes to OPEN state.
 * LOG:
 * LOG: Revision 2.32.2.7  2007/05/31 10:45:12  nvijikumar
 * LOG: RETRY timer need not start once CER is rejected in the OPEN state.
 * LOG:
 * LOG: Revision 2.32.2.6  2007/05/30 13:45:19  nvijikumar
 * LOG: Return proper Error Code if basegeneric cmdd failed to convert as base cmd
 * LOG:
 * LOG: Revision 2.32.2.5  2007/05/30 09:41:33  nvijikumar
 * LOG: Fix for Bug Ids: 5927,5928,5931.
 * LOG: 1. In open state if Recvd CER and process failed, stop DWR and Start
 * LOG:    RETRY timer.
 * LOG: 2. Send CEA with proper error even for first CER.
 * LOG:
 * LOG: Revision 2.32.2.4  2007/05/28 14:15:50  nvijikumar
 * LOG: Handling Inbound Error response.
 * LOG:
 * LOG: Revision 2.32.2.3  2007/05/25 04:08:55  nvijikumar
 * LOG: 1. Convert Base Generic Command to perticular base command before
 * LOG:    processing the message.
 * LOG: 2. Debug trace and peer notifications check is replaced with static fun.
 * LOG: 3. if debug trace and peerNotifaction both flags are set Command is printed
 * LOG:    as well as given to Application.
 * LOG:
 * LOG: Revision 2.32.2.2  2007/04/04 05:58:06  nvijikumar
 * LOG: Print CEA,DWA,DPA before sending it to the peer.
 * LOG:
 * LOG: Revision 2.32.2.1  2007/03/08 15:00:50  nvijikumar
 * LOG: Issues Fixed:
 * LOG: 1. Provided TO_TEXT macro in ProcessCER function.
 * LOG: 2. Stop RETRY Timer while changing state to OPEN only at first time.
 * LOG: 3. BCGI DPR issue, Give DPR to App only after sending DPA.
 * LOG: 4. After Election Disconnect R-Transport.
 * LOG:
 * LOG: Revision 2.32  2007/02/19 15:00:44  nvijikumar
 * LOG: IOT:: Fix for below issues.
 * LOG: 1. Explicit FirmwareRevision Check not mandated.
 * LOG: 2. Fix for Election Issue.
 * LOG: 3. Start peer RETRY timer in appropriate places.
 * LOG:
 * LOG: Revision 2.31  2007/01/31 16:32:29  kamakshilk
 * LOG: Braces added to the case I_PEER_DISC
 * LOG:
 * LOG: Revision 2.30  2007/01/31 16:21:02  kamakshilk
 * LOG: Disc(tr) removed from I-Conn-Nack and added after I-Peer-Disc
 * LOG:
 * LOG: Revision 2.29  2007/01/30 16:39:44  kamakshilk
 * LOG: Disconnect Connector tranport when received I-Conn-Nack.
 * LOG: Stop DW Timers in I-Peer-Disc and R-Peer-Disc
 * LOG:
 * LOG: Revision 2.28  2007/01/19 11:17:44  nvijikumar
 * LOG: Start RETRY timers once once peer gets transport disconnect indications.
 * LOG: These timers are moved from dia_acceptor and dia_connector files.
 * LOG:
 * LOG: Revision 2.27  2007/01/12 13:54:58  nvijikumar
 * LOG: Peer transport disconnect indication to App.
 * LOG:
 * LOG: Revision 2.26  2006/12/20 14:57:42  tpanda
 * LOG: Other bug fixes related to redundancy(Issue#5075,5073,5069,5057 etc)
 * LOG:
 * LOG: Revision 2.25  2006/12/15 15:36:18  tpanda
 * LOG: Disconnect peer problem in redundancy bug# 5068
 * LOG:
 * LOG: Revision 2.24  2006/12/15 13:14:40  tpanda
 * LOG: Fix for disconnection with backup if DPR sent from active (bug# 5068)
 * LOG:
 * LOG: Revision 2.23  2006/12/11 14:27:34  nvijikumar
 * LOG: Send Peer based msgs to application, if peerMsgToApp flag is set in the XML.
 * LOG:
 * LOG: Revision 2.22  2006/12/01 13:51:26  nvijikumar
 * LOG: Fixes for Pending Queue issues.
 * LOG: Set stopFailover flag, incase of Failback.
 * LOG:
 * LOG: Revision 2.21  2006/11/30 18:54:24  tpanda
 * LOG: Redundancy slot changes backed out. TODO: Refer (REDUNDANCY_SLOT_CHANGES) defines
 * LOG: Failover and failback bug fixes
 * LOG:
 * LOG: Revision 2.20  2006/11/30 11:55:01  tpanda
 * LOG: Two CER exchanging issue if Peer restarting
 * LOG:
 * LOG: Revision 2.19  2006/11/29 11:52:14  tpanda
 * LOG: Redundancy related enhancements and fixes for few bugs raised for redundancy
 * LOG:
 * LOG: Revision 2.18  2006/11/25 03:57:20  tpanda
 * LOG: Changes for Msg based redundancy
 * LOG:
 * LOG: Revision 2.17  2006/11/22 10:49:37  nvijikumar
 * LOG: Baseline PendingQ ( Failover ) Changes.
 * LOG:
 * LOG: Revision 2.16  2006/11/17 20:42:37  tpanda
 * LOG: Upstream Message multicasted by backup node if received(redundancy)
 * LOG:
 * LOG: Revision 2.15  2006/11/13 07:31:18  yranade
 * LOG: Reset Initiator/Connector handle on receiving DPR.
 * LOG:
 * LOG: Revision 2.14  2006/10/30 12:17:49  yranade
 * LOG: 1. Update trace: BugFix:4671
 * LOG: 2. Reset Pending flag, on changing state to CLOSED state.BugFix:4672
 * LOG:
 * LOG: Revision 2.13  2006/10/28 12:35:34  yranade
 * LOG: Complete bug fix 4635, Send the CEA on the R-Conn. Update the handle
 * LOG: correctly.
 * LOG:
 * LOG: Revision 2.12  2006/10/27 09:37:23  yranade
 * LOG: Reorganize SendCEA. Use CER from stored cache. Bug Fix: 4635
 * LOG:
 * LOG: Revision 2.11  2006/10/25 15:19:58  yranade
 * LOG: Updated traces. Bug Fix 4489, 4557
 * LOG:
 * LOG: Revision 2.10  2006/10/25 12:50:55  yranade
 * LOG: 1. Updated traces a bit.
 * LOG: 2. Solve a tricky issue, when CER received from Unknown peer.
 * LOG:
 * LOG: Revision 2.9  2006/10/24 17:00:10  nvijikumar
 * LOG: Fix for Bug Id: 4485
 * LOG: Checking for FirmwareRevision match while validating CER.
 * LOG:
 * LOG: Revision 2.8  2006/10/24 14:10:34  yranade
 * LOG: 1. Bug Fix 4575. Don't remove entry from peer table for DO_NOT_WANT_TO_TALK
 * LOG:    just don't retry connections.
 * LOG: 2. Schedule client reconnect in R-OPEN -->R-Peer-Disc.
 * LOG:
 * LOG: Revision 2.7  2006/10/17 17:35:07  yranade
 * LOG: After Disconnecting transports reset the handle's in the Peer Entry to
 * LOG: NULL.
 * LOG:
 * LOG: Revision 2.6  2006/10/17 05:28:09  tpanda
 * LOG: Fix for Vendor-Specific-App Id crash with no common appId
 * LOG:
 * LOG: Revision 2.5  2006/10/16 16:02:58  yranade
 * LOG: Bug-Fixes and Updates.
 * LOG:
 * LOG: Revision 2.4  2006/10/12 14:13:41  yranade
 * LOG: Finish up Device Watchdog handling. Bug Fix: 4464
 * LOG:
 * LOG: Revision 2.3  2006/10/11 15:04:53  yranade
 * LOG: Fixes for issues: 4451, 4452, 4454, 4457.
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
 * LOG:
 ****************************************************************************/

/**
 * Includes
 */
#include <its++.h>
#include <engine++.h>
#include <its_timers.h>
#include <json/json.h>

#include <dia_cmn.h>
#include <dia_msg_flow.h>
#include <dia_stack.h>
#include <dia_trace.h>
#include <dia_err.h>
#include <dia_utils.h>

//Added for DTF
#include <Sync.h>
#include <PluginObj.h>
#include <DiameterTransformer.h>
#include <dtf.h>
////End of DTF addition

#include <dia_peer_fsm.h>
#include <dia_peer_table.h>
#include <dia_ip_trans.h>
#include <dia_msg_router.h>
#include <dia_wd_trans.h>
#include <dia_mgmt.h>
#include <dia_stack_alarms.h>

#if defined (ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
#endif

#ifdef TLS_ENABLED
static ITS_INT TlsClientProcedure(PEER_STATE_CTXT* ctxt);

static ITS_INT TlsServerProcedure(PEER_STATE_CTXT* ctxt);

ITS_INT TlsServerProcedure(ITS_SocketInfo* info,DiaSocketTransport* trHandl);
#endif

#include <fstream>
#include <sys/time.h>

#ifdef CALC_LATENCY

class MsgTimeStore
{
 public:

    enum
    {
        MAX_ENTRIES = (40*1024*1024)
    };

    class Entry
    {
     public:
        void add(uint32_t h2h, uint32_t e2e)
        {
            m_h2h = h2h;
            m_e2e = e2e;
            gettimeofday(&m_ts, NULL);
        }

        uint32_t m_h2h;
        uint32_t m_e2e;
        struct timeval m_ts;
    };

    MsgTimeStore()
        : m_count(0),
          m_lock(PTHREAD_MUTEX_INITIALIZER)
    {
    }

    void AddEntry(uint32_t h2h, uint32_t e2e)
    {
        ITS_THROW_ASSERT(m_count < MAX_ENTRIES);

        pthread_mutex_lock(&m_lock);
        m_entries[m_count].add(h2h, e2e);

        m_count++;
        pthread_mutex_unlock(&m_lock);
    }

    void dumpToFile()
    {
        ofstream ofile("/tmp/msg_dump.txt");
        pthread_mutex_lock(&m_lock);
        Entry *ent;

        for(int i = 0; i < m_count; i++)
        {
            ent = &m_entries[i];
            ofile << ent->m_h2h << " " << ent->m_e2e << " "
                  << ent->m_ts.tv_sec << ":" << ent->m_ts.tv_usec << std::endl;
        }
        m_count = 0;
        pthread_mutex_unlock(&m_lock);
    }

 private:
    Entry m_entries[MAX_ENTRIES];
    pthread_mutex_t m_lock;
    uint32_t m_count;
};

static MsgTimeStore msgTimeStore;

void DumpMsgStatsToFile()
{
    msgTimeStore.dumpToFile();
}

#endif

static
bool IsDebugTraceEnabled()
{
    if (DIA_TRACE()->IsEnabled() && DIA_TRACE()->IsEnabled(DIA_DEBUG))
    {
        return true;
    }
    return false;
}

static
bool IsPeerMsgToAppEnabled()
{
    if (itsDiaConfig.IsPeerMsgToAppEnabled())
    {
        return true;
    }
    return false;
}

static
int ConvertToBaseCmd(PEER_STATE_CTXT* ctxt)
{
    DIA_CMD *cmd = NULL;
    try
    {
        if (DIA_PEER_ST_CURR_CMD(ctxt)->isError() &&
              DIA_PEER_ST_CURR_CMD(ctxt)->isRequest())
        {
            if (DIA_PEER_ST_CURR_CMD(ctxt)->isProxyable())
            {
               DT_DBG (("Received Error Response : PROXYABLEERROR"));

               PROXYABLEERROR *err =
                 new PROXYABLEERROR(*(DIA_GEN_CMD*)DIA_PEER_ST_CURR_CMD(ctxt));

               if (IsDebugTraceEnabled() && err)
               {
                   cout<<endl<<*err<<endl;
               }
               if (err)
               {
                   delete err;
               }
            }
            else
            {
               DT_DBG (("Received Error Response : NONPROXYABLEERROR"));

               NONPROXYABLEERROR *err =
               new NONPROXYABLEERROR(*(DIA_GEN_CMD*)DIA_PEER_ST_CURR_CMD(ctxt));

               if (IsDebugTraceEnabled() && err)
               {
                   cout<<endl<<*err<<endl;
               }
               if (err)
               {
                   delete err;
               }
            }
            if (DIA_PEER_ST_CURR_CMD(ctxt))
            {
                delete DIA_PEER_ST_CURR_CMD(ctxt);
            }

            DIA_PEER_ST_CURR_CMD(ctxt) = cmd;
            return (!ITS_SUCCESS);
        }
        switch (DIA_PEER_ST_CURR_CMD(ctxt)->getCommandCode())
        {
        case DIA_MSG_CE:
        {
            if (DIA_PEER_ST_CURR_CMD(ctxt)->isRequest())
            {
                cmd = new DIA_CER(*(DIA_GEN_CMD*)DIA_PEER_ST_CURR_CMD(ctxt));
            }
            else
            {
                cmd = new DIA_CEA(*(DIA_GEN_CMD*)DIA_PEER_ST_CURR_CMD(ctxt));
            }
            break;
        }
        case DIA_MSG_DW:
        {
            if (DIA_PEER_ST_CURR_CMD(ctxt)->isRequest())
            {
                cmd = new DIA_DWR(*(DIA_GEN_CMD*)DIA_PEER_ST_CURR_CMD(ctxt));
            }
            else
            {
                cmd = new DIA_DWA(*(DIA_GEN_CMD*)DIA_PEER_ST_CURR_CMD(ctxt));
            }
            break;
        }
        case DIA_MSG_DP:
        {
            if (DIA_PEER_ST_CURR_CMD(ctxt)->isRequest())
            {
                cmd = new DIA_DPR(*(DIA_GEN_CMD*)DIA_PEER_ST_CURR_CMD(ctxt));
            }
            else
            {
                cmd = new DIA_DPA(*(DIA_GEN_CMD*)DIA_PEER_ST_CURR_CMD(ctxt));
            }
            break;
        }
        case DIA_MSG_CUR:
        {
            if (DIA_PEER_ST_CURR_CMD(ctxt)->isRequest())
            {
                cmd = new DIA_CUR(*(DIA_GEN_CMD*)DIA_PEER_ST_CURR_CMD(ctxt));
            }
            else
            {
                cmd = new DIA_CUA(*(DIA_GEN_CMD*)DIA_PEER_ST_CURR_CMD(ctxt));
            }
            break;
        }
        default:
            break;
        }
        if (DIA_PEER_ST_CURR_CMD(ctxt))
        {
            delete DIA_PEER_ST_CURR_CMD(ctxt);
        }

        DIA_PEER_ST_CURR_CMD(ctxt) = cmd;
    }
    catch (NoSuchAttributeException e)
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));

        return (ITS_DIA_MISSING_AVP);
    }
    catch (WrongCommandTypeException e)
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));

        return (ITS_DIA_CMD_UNSUPPORTED);
    }
    catch (UnknownTypeException e)
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));

        return (ITS_DIA_INVALID_BIT_IN_HDR);
    }
    catch (CodecException e)
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));

        return (e.errcode());
    }
    catch (...)
    {
        DT_ERR(("Unknown Exception Caught"));

        return (ITS_DIA_MISSING_AVP);
    }
    return ITS_DIA_SUCCESS;
}

static
int Validate(PEER_STATE_CTXT* ctxt, ITS_EVENT *evt)
{
    ITS_BOOLEAN ret = ITS_FALSE;
    ITS_BOOLEAN matchSecurity = ITS_FALSE;
    int i=0, j=0;

    DT_DBG(("ValidatePeer"));

    /* Validate the peer
       Check the CER received with the localCER
       saved in our Configuration */
    try
    {
        DIA_CER *cer = (DIA_CER *)ctxt->currCmd;

        DIA_CER *lcer;
        lcer = itsDiaConfig.GetLocalCER();

        /* First Check the Inband Security Id */
        if (cer->countInbandSecurityId())
        {
            DIA_PE_IS_INBAND_SEC_MATCH(
            DIA_PEER_ST_ENTRY(ctxt)) = ITS_FALSE;
            for (i = 0; i < lcer->countInbandSecurityId(); i++)
            {
                for (j = 0; j < cer->countInbandSecurityId(); j++)
                {
                    if (lcer->getInbandSecurityId(i).value() ==
                        cer->getInbandSecurityId(j).value())
                    {
                        matchSecurity = ITS_TRUE;
                        if (lcer->getInbandSecurityId(i).value() == \
                            DIA_TLS)
                        {
                            DIA_PE_IS_INBAND_SEC_MATCH(
                                DIA_PEER_ST_ENTRY(ctxt)) = ITS_TRUE;
                            DT_DBG(("Validate: Inband security matched "\
                                    "as TLS."));
                        }
                        break;
                    }
                }
            }

            if (cer->containsFirmwareRevision())
            {
                if (cer->getFirmwareRevision().value() !=
                 lcer->getFirmwareRevision().value())
               {
                  DT_WRN(("Firmware Revision Mismatch"));
                  DIA_Alarm(15400, __FILE__, __LINE__, "FirmwareRevisionMismatch");
               }
            }

            if (!matchSecurity)
            {
                return (ITS_DIA_NO_COMMON_SECURITY);
            }
        }

        /*
         * when CER message is received with P-bit set, stack is returning
         * CEA message with result code 2001 (DIAMETER_SUCCESS)
         * It has to send CEA with error code 3008 (DIAMETER_INVALID_HDR_BITS)
         */

        if(cer->isProxyable())
        {
            DT_DBG(("ValidatePeer:Proxyable bit set in CER Message"));
            DT_DBG(("ValidatePeer:Return Error code 3008"));

            return (ITS_DIA_INVALID_HDR_BITS);
        }


        /*
         * Check for Relay agent support
         */
        DIA_PE_IS_RELAY(ctxt->pEntry) = false;
        for (j = 0; j < cer->countAuthApplicationId(); j++)
        {
             if (cer->getAuthApplicationId(j).value() ==
                 RESFILE_ParseNum(DIA_RELAY_APP_ID_STRING))
             {
                 DIA_PE_IS_RELAY(ctxt->pEntry) = true;
                 /**
                  * If the Relay AppId is found in the incoming
                  * CER then accept the CER and return SUCCESS.
                  * Fix for the issue 779 in Whizible.
                  */
                 return ITS_SUCCESS;
             }
        }


#ifndef APP_ID_EXCLUSIVE
        if (lcer->getVendorId().value() == cer->getVendorId().value())
        {
            return ITS_SUCCESS;
        }

        for (i = 0; i < lcer->countSupportedVendorId(); i++)
        {
            for (j = 0; j < cer->countSupportedVendorId(); j++)
            {
                 if (lcer->getSupportedVendorId(i).value() ==
                     cer->getSupportedVendorId(j).value())
                 {
                     return ITS_SUCCESS;
                 }
            }
        }
#endif
        for (i = 0; i < lcer->countAuthApplicationId(); i++)
        {
            for (j = 0; j < cer->countAuthApplicationId(); j++)
            {
                 if (lcer->getAuthApplicationId(i).value() ==
                     cer->getAuthApplicationId(j).value())
                 {
                     return ITS_SUCCESS;
                 }
            }
        }

        for (i = 0; i < lcer->countAcctApplicationId(); i++)
        {
            for (j = 0; j < cer->countAcctApplicationId(); j++)
            {
                 if (lcer->getAcctApplicationId(i).value() ==
                     cer->getAcctApplicationId(j).value())
                 {
                     return ITS_SUCCESS;
                 }
            }
        }

        for (i = 0; i < lcer->countVendorSpecificApplicationId(); i++)
        {
            for (j = 0; j < cer->countVendorSpecificApplicationId(); j++)
            {
                const VendorSpecificApplicationId& lvs =
                     lcer->getVendorSpecificApplicationId(i);

                const VendorSpecificApplicationId& vs =
                     cer->getVendorSpecificApplicationId(j);

                if (lvs.containsAuthApplicationId() &&
                    vs.containsAuthApplicationId())
                {
                    if (lvs.getAuthApplicationId().value() ==
                       (vs.getAuthApplicationId().value()))
                    {
                         return ITS_SUCCESS;
                    }
                }

                if (lvs.containsAcctApplicationId() &&
                    vs.containsAcctApplicationId())
                {
                    if (lvs.getAcctApplicationId().value() ==
                       (vs.getAcctApplicationId().value()))
                    {
                         return ITS_SUCCESS;
                    }
                }

#ifndef APP_ID_EXCLUSIVE
                for (int k = 0; k < lvs.countVendorId(); k++)
                {
                    for (int l = 0; l < vs.countVendorId(); l++)
                    {
                        if (lvs.getVendorId(k).value() ==
                            vs.getVendorId(l).value())
                        {
                            return ITS_SUCCESS;
                        }
                    }
                }
#endif

            }
        }

        /**
         * Check to verify if the self Node is advertised as relay then,
         * Accept the CER. Fix for the issue 779 in Whizible.
         */
        if (itsDiaConfig.IsAdvertisedRelay())
        {
            DT_DBG(("ValidatePeer:Failed to find Common Criteria in Message"));
            DT_DBG(("ValidatePeer:Relay Advertisement in Local CER." \
                    " Accepting Peer..."));
            return ITS_SUCCESS;
        }

    }
    catch (NoSuchAttributeException e)
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));

        return (ITS_DIA_NO_COMMON_APP);
    }
    catch (WrongCommandTypeException e)
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));

        return (ITS_DIA_NO_COMMON_APP);
    }
    catch (UnknownTypeException e)
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));

        return (ITS_DIA_NO_COMMON_APP);
    }
    catch (CodecException e)
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));

        return (ITS_DIA_NO_COMMON_APP);
    }
    catch (...)
    {
        DT_ERR(("Unknown Exception Caught"));

        return (ITS_DIA_NO_COMMON_APP);
    }

    return (ITS_DIA_NO_COMMON_APP);
}


static
int Elect(PEER_STATE_CTXT* ctxt, ITS_EVENT *evt)
{
    int ret;
    ITS_OCTET pad = 0x80;

    DT_DBG(("Election::"));

    /* Section 5.6.4 */
    DIA_CER *lcer;
        lcer = itsDiaConfig.GetLocalCER();

    DIA_CER *cer = (DIA_CER *)DIA_PE_CE_CACHE(ctxt->pEntry);

    std::string loh = lcer->getOriginHost().value();
    std::string roh = cer->getOriginHost().value();

    if (strcasecmp(loh.c_str(), roh.c_str()) == 0)
    {
        /* TODO Terminate Connection */
        return (!ITS_SUCCESS);
    }
    else if (loh.length() < roh.length())
    {
        loh += std::string(roh.length() - loh.length(), char(pad));
    }
    /**
     * Correcting a typo "changing "<" with ">" symbol.
     * Partial Fix for issues 4 and 6 raised by Dhiranand during the
     * validation of bcgi ticket 1807.
     */
    else if (loh.length() > roh.length())
    {
        roh += std::string(loh.length() - roh.length(), char(pad));
    }

    /* IOT::Election Issue with DigitalRoute */
    DIA_PE_STATE(ctxt->pEntry) = PEER_ST_WAIT_RETURNS;
    DT_DBG(("PeerFsm:: State::PEER_ST_WAIT_RETURNS"));

    for (int i=0; i < loh.size(); i++)
    {
        if (std::tolower(loh[i]) > std::tolower(roh[i]))
        {
            /* SubmitToSM */
            /* Lock on Entry should be already acquired to reach
               here */
            ctxt->evtType = PEER_EVT_WIN_ELECTION;

            DT_DBG(("Election::Win Election"));

            if ((ret = DIA_PEER_ST_FSM(ctxt)->SubmitToSM(ctxt, evt)) == ITS_SUCCESS)
            {
                DT_DBG(("SubmitToSM:Success"));
                return (ITS_SUCCESS);
            }
            else
            {
                DT_ERR(("SubmitToSM: Error ret = %d", ret));
                return (!ITS_SUCCESS);
            }
        }
        else if (std::tolower(loh[i]) < std::tolower(roh[i]))
        {
            DT_DBG(("Election::Lost Election"));
            /**
             * If Lost Election, return Success as the election
             * process completed waiting for CEA Message.
             * (Partial fix for issues 4 and 6 raised by Dhiranand
             * during the  validation of bcgi ticket 1807.
             */
            return (ITS_SUCCESS);
        }
    }

    return (!ITS_SUCCESS);
}

static
int Disc(DiaSocketTransport *tr)
{
    DT_DBG(("Disc::Disconnect Connection"));

    /* Disconnect connection */
    if (tr)
    {
        tr->SetExit();
    }

    return (ITS_SUCCESS);
}

/* It is always R-Reject */
static
int Reject(PEER_STATE_CTXT* ctxt, ITS_EVENT *evt)
{
    DT_DBG(("Reject:: Disconnecting Incoming Connection"));

    PEER_ENTRY *peer = ctxt->pEntry;

    /* Disconnect all R-Connection Irrespective of Type */
    DiaSocketTransport *tr =
       (DiaSocketTransport *)DIA_PE_ACC_SPECS(peer).trHandle;

    /* Disconnect connection */
    if (tr)
    {
        Disc(tr);
        DIA_PE_ACC_SPECS(peer).trHandle = NULL;
        DIA_PE_ACC_SPECS(peer).trInst = 0;
    }

    return (ITS_SUCCESS);
}

static
int Cleanup(PEER_STATE_CTXT* ctxt)
{
    DT_DBG(("Cleanup:: Free Resources"));

    if (DIA_PEER_ST_CURR_CMD(ctxt) == DIA_PE_CE_CACHE(ctxt->pEntry))
    {
         delete DIA_PEER_ST_CURR_CMD(ctxt);
         DIA_PEER_ST_CURR_CMD(ctxt) = NULL;
         DIA_PE_CE_CACHE(ctxt->pEntry) = NULL;
         return (ITS_SUCCESS);
    }

    if (DIA_PEER_ST_CURR_CMD(ctxt))
    {
        DIA_GEN_CMD* cmd = (DIA_GEN_CMD*)DIA_PEER_ST_CURR_CMD(ctxt);
        /* don't delete the command here for following conditions
         * 1. if it is error response to the peer.
         * 2. if it is device watch dog request (Device watch dog
         *    may be tried to be sent before open state, don't delete
         *    here because it is stack object
         * 3. if it is session based messages(all applicaion messages)
         */
        if (cmd->getCommandCode() != DIA_MSG_DW && cmd->isError() == false
           && cmd->getSessionId() == NULL)
        {
            delete DIA_PEER_ST_CURR_CMD(ctxt);
            DIA_PEER_ST_CURR_CMD(ctxt) = NULL;
        }
    }

    if (DIA_PE_CE_CACHE(ctxt->pEntry))
    {
        delete DIA_PE_CE_CACHE(ctxt->pEntry);
        DIA_PE_CE_CACHE(ctxt->pEntry) = NULL;
    }

    return (ITS_SUCCESS);
}

static
int ProcessError(PEER_STATE_CTXT* ctxt, ITS_EVENT *evt)
{
    DiaSocketTransport *tr = NULL;

    DT_ERR(("Error:: Disconnect Connection && Free Resources"));

    /* Schedule CONN_RETRY timer */

    Cleanup(ctxt);

    tr = (DiaSocketTransport *)DIA_PE_HANDLE(ctxt->pEntry);
    if (tr)
    {
        Disc(tr);
        tr = NULL;
    }

    return (ITS_SUCCESS);
}

static void
HandleDPRDisconnectCause(DIA_DPR *dpr,PEER_ENTRY *pEntry)
{
    DT_DBG(("Disconnect Cause = %d\n", dpr->getDisconnectCause().value()));

    int subComponentId = STACK_MESSAGE_PROCESSING;
    const char *peerName = DIA_PE_HOST(pEntry);
    std::vector<std::string> variables;
    variables.push_back(peerName);

    if(dpr->getDisconnectCause().value() ==
            DisconnectCause::DO_NOT_WANT_TO_TALK_TO_YOU)
    {
        std::string alarmText("Raising alarm for receiving DPR with cause as DO_NOT_WANT_TO_TALK_TO_YOU.");
        int alarmId = DPR_RECEIVED_WITH_CAUSE_DO_NOT_WANT_TO_TALK_TO_YOU;
        //DIA_STACK_ALARM->RaiseAlarm(subComponentId,alarmId,alarmText, variables);
        DIA_INC_PEER_RCVD_DPR_WITH_CAUSE_DO_NOT_WANT_TO_TALK_TO_YOU(pEntry);
    }
    else if(dpr->getDisconnectCause().value() ==
            DisconnectCause::BUSY)
    {
        std::string alarmText("Raising alarm for receiving DPR with cause as BUSY.");
        int alarmId = DPR_RECEIVED_WITH_CAUSE_BUSY;
        //DIA_STACK_ALARM->RaiseAlarm(subComponentId,alarmId,alarmText, variables);
        DIA_INC_PEER_RCVD_DPR_WITH_CAUSE_BUSY(pEntry);
    }
    else
    {
        std::string alarmText("Raising alarm for receiving DPR with cause as REBOOT.");
        int alarmId = DPR_RECEIVED_WITH_CAUSE_REBOOT;
        //DIA_STACK_ALARM->RaiseAlarm(subComponentId,alarmId,alarmText, variables);
    }

    //RFC6733 complaint implementation
    if(DIA_PE_DISCONNECT_CAUSE_SUPPORT(pEntry))
    {
        DIA_PEER_GET_DIS_CAUSE(pEntry) = dpr->getDisconnectCause().value();
        if (dpr->getDisconnectCause().value() ==
                DisconnectCause::DO_NOT_WANT_TO_TALK_TO_YOU)
        {
            DT_DBG(("Disconnect Cause is DO_NOT_WANT_TO_TALK_TO_YOU.Retry Timer value for this cause is %d\n",
                        DIA_PE_DO_NOT_WANT_TO_TALK_TO_YOU_RECONNECT_TIMER(pEntry)));
            if(DIA_PE_DO_NOT_WANT_TO_TALK_TO_YOU_RECONNECT_TIMER(pEntry)> 0)
            {
                if (DIA_PE_RETRY_TIMER(pEntry) != TIMER_BAD_SERIAL)
                {
                    PeerTable::StopTimer(RETRY, pEntry);
                }
                if (itsDiaConfig.GetInitiateConnsOpt())
                {
                    PeerTable::StartTimer(RETRY, pEntry,
                            DIA_PE_DO_NOT_WANT_TO_TALK_TO_YOU_RECONNECT_TIMER(pEntry));
                }
            }
            else
            {
                DT_DBG(("Not starting RETRY Timer as Retry value configured is 0 for the cause"));
            }

        }
        else if(dpr->getDisconnectCause().value() ==
                DisconnectCause::BUSY) 
        {
            if(DIA_PE_BUSY_RECONNECT_TIMER(pEntry) > 0)
            {

                DT_DBG(("Disconnect Cause is BUSY.Retry Timer value for this cause is %d\n",
                            DIA_PE_BUSY_RECONNECT_TIMER(pEntry)));
                if (DIA_PE_RETRY_TIMER(pEntry) != TIMER_BAD_SERIAL)
                {
                    PeerTable::StopTimer(RETRY,pEntry);
                }
                if (itsDiaConfig.GetInitiateConnsOpt())
                {
                    PeerTable::StartTimer(RETRY, pEntry,
                            DIA_PE_BUSY_RECONNECT_TIMER(pEntry));
                }
            }
            else
            {
                DT_DBG(("Not starting RETRY Timer as Retry value configured is 0 for the cause"));
            }

        }
        else
        {
            if (DIA_PE_RETRY_TIMER(pEntry) != TIMER_BAD_SERIAL)
            {
                PeerTable::StopTimer(RETRY, pEntry);
            }
            if (itsDiaConfig.GetInitiateConnsOpt())
            {
                PeerTable::StartTimer(RETRY, pEntry);
            }
        }
    }
    //RFC3588 complaint implementation
    else if (dpr->getDisconnectCause().value() !=
            DisconnectCause::DO_NOT_WANT_TO_TALK_TO_YOU)
    {
        /* Retry connection after disconnect */
        if (DIA_PE_RETRY_TIMER(pEntry) != TIMER_BAD_SERIAL)
        {
            PeerTable::StopTimer(RETRY, pEntry);
        }
        if (itsDiaConfig.GetInitiateConnsOpt())
        {
            PeerTable::StartTimer(RETRY, pEntry);
        }

    }
    else
    {
        DIA_PEER_GET_DIS_CAUSE(pEntry) = DisconnectCause::DO_NOT_WANT_TO_TALK_TO_YOU;
    }
}


static
int DecodeSupportedApp(PEER_STATE_CTXT* ctxt)
{
    DESTINATION_INFO destInfo;
    const char* realmName = DIA_PE_REALM(ctxt->pEntry);
    const char* peerName = DIA_PE_HOST(ctxt->pEntry);
    DIA_GEN_CMD * gCmd = DIA_PE_CE_CACHE(ctxt->pEntry);
    int appId = 0;
    int venId = 0;

    if (gCmd)
    {
        int vIdCnt = gCmd->countVendorSpecificApplicationId();


        for (int i=0; i<vIdCnt; i++)
        {

            if (gCmd->getVendorSpecificApplicationId(i)->
                               containsAcctApplicationId())
            {
                appId = gCmd->getVendorSpecificApplicationId(i)->
                                 getAcctApplicationId().value();
            }
            else if (gCmd->getVendorSpecificApplicationId(i)->
                                containsAuthApplicationId())
            {
                appId = gCmd->getVendorSpecificApplicationId(i)->
                                 getAuthApplicationId().value();
            }

            venId = gCmd->getVendorSpecificApplicationId(i)->
                               getVendorId().value();

            destInfo.realmName = realmName;
            destInfo.peerName = peerName;
            destInfo.peerRealm = NULL;
            destInfo.applicationId = appId;
            destInfo.vendorId = venId;
            destInfo.priority = 0;

            DiaMgmt::GetDiaMgmt()->AddDestination(&destInfo);

            /* if vend Id inside vendorSpecific AppId does not match with
            * vendor Id, insert one more entry into Destination with
            * other vendor Id.
            */
            if (venId != gCmd->getVendorId()->value())
            {
                destInfo.vendorId = gCmd->getVendorId()->value();
                DiaMgmt::GetDiaMgmt()->AddDestination(&destInfo);
            }

        }
        for(int i = 0; i < gCmd->countAuthApplicationId();i++)
        {
            appId = gCmd->getAuthApplicationId(i)->value();
            if(appId > 0)
            {
                DT_DBG(("Adding auth App id %d to routing table",appId));
                destInfo.realmName = realmName;
                destInfo.peerName = peerName;
                destInfo.peerRealm = realmName;
                destInfo.applicationId = appId;
                destInfo.vendorId = gCmd->getVendorId()->value();
                destInfo.priority = 0;

                DiaMgmt::GetDiaMgmt()->AddDestination(&destInfo);
            }
        }

        for(int i = 0; i < gCmd->countAcctApplicationId();i++)
        {
            appId = gCmd->getAcctApplicationId(i)->value();
            if(appId > 0)
            {
                DT_DBG(("Adding Acct App id %d to routing table",appId));
                destInfo.realmName = realmName;
                destInfo.peerName = peerName;
                destInfo.peerRealm = realmName;
                destInfo.applicationId = appId;
                destInfo.vendorId = gCmd->getVendorId()->value();
                destInfo.priority = 0;

                DiaMgmt::GetDiaMgmt()->AddDestination(&destInfo);
            }
        }
        DT_DBG(("Succesfully Added Destination Entry"));

        return ITS_SUCCESS;
    }

    return !ITS_SUCCESS;
}



static
int AssociateDictIdForPeerRcvdCER(DIA_CER* cer,PEER_ENTRY* pEntry)
{
    std::string DictionaryNames[MAX_DICT_IDS_PER_PEER];
    APPLICATION_TYPE type[MAX_DICT_IDS_PER_PEER];
    int noOfDict = 0;
    PEER_INFO pInfo;


    for (int noOfAppIds = 0; noOfAppIds < cer->countAuthApplicationId(); noOfAppIds++)
    {
        if(cer->getAuthApplicationId(noOfAppIds).value() !=0)
        {
            const char* dictName = DiaMgmt::GetDiaMgmt()->GetDictionaryName(cer->getAuthApplicationId(noOfAppIds).value());
            if(dictName != NULL)
            {
                DictionaryNames[noOfDict] = dictName;
                delete []dictName;
                type[noOfDict++] = DIA_AUTH_APP;
            }

        }
    }
    for (int noOfAcctIds = 0; noOfAcctIds < cer->countAcctApplicationId(); noOfAcctIds++)
    {
        if(cer->getAcctApplicationId(noOfAcctIds).value() !=0)
        {
            const char* dictName = DiaMgmt::GetDiaMgmt()->GetDictionaryName(cer->getAcctApplicationId(noOfAcctIds).value());
            if(dictName != NULL)
            {
                DictionaryNames[noOfDict] = dictName;
                delete []dictName;
                type[noOfDict++] = DIA_ACCT_APP;
            }

        }
    }
    pInfo.peerName = DIA_PE_HOST(pEntry);
    pInfo.realmName = DIA_PE_REALM(pEntry);
    if(DiaMgmt::GetDiaMgmt()->AssociateDictToPeer(&pInfo,noOfDict,DictionaryNames,type,true) == ITS_SUCCESS)
    {
        DT_DBG(("Sucessfully associated dict ids for newly discovered peer %s",pInfo.peerName));
    }
    else
    {
        DT_ERR(("Failed to  associate dict ids for newly discovered peer %s",pInfo.peerName));
    }
    return ITS_SUCCESS;
}

static
int ProcessCER(PEER_STATE_CTXT* ctxt, ITS_EVENT *evt)
{
    int ret;
    DT_DBG(("CER Received from the peer"));
    DT_DBG(("ProcessCER::"));

    /* Process-CER */
    if (DIA_PE_CE_CACHE(ctxt->pEntry))
    {
        delete DIA_PE_CE_CACHE(ctxt->pEntry);
        DIA_PE_CE_CACHE(ctxt->pEntry) = NULL;
    }
    DIA_PE_CE_CACHE(ctxt->pEntry) = (DIA_GEN_CMD *)ctxt->currCmd;

    if ((ret = Validate(ctxt, evt)) != ITS_SUCCESS)
    {
        DT_ERR(("Process-CER::Failure Error : %s", PERM_ERR_CODE_TO_TEXT(ret)));
        return (ret);
    }
    /* Convert The BaseGenCmdToCer */
    if ((ret = ConvertToBaseCmd(ctxt)) != ITS_DIA_SUCCESS)
    {
        DT_ERR(("Process-CER::Decode Failure : %s",PERM_ERR_CODE_TO_TEXT(ret)));
        return (ret);
    }

    /* Update DIA_PE_CE_CACHE after successful decode */
    DIA_PE_CE_CACHE(ctxt->pEntry) = (DIA_GEN_CMD *)ctxt->currCmd;

    /* check if dynamic discovery is Enabled &
     * CEA is received from Dynamically discovered PEER
     */
        if ((itsDiaConfig.isPeerDiscoveryEnabled())
             && (DIA_PE_IS_DISCOVERED(ctxt->pEntry))
             && (DIA_PE_IS_FIRST_CAP_EXCH(ctxt->pEntry)))
        {
            if (DecodeSupportedApp(ctxt) == ITS_SUCCESS)
            {
                DT_DBG(("Successfully added Destination Host Added to Realm\n"));
                DIA_PE_IS_FIRST_CAP_EXCH(ctxt->pEntry) = false;
            }
            else
            {
                DT_DBG(("Failed to  add Destination Host Added to Realm\n"));
            }
        }

    /* Send Message with Indication to App , if flag enabled*/
    if (IsPeerMsgToAppEnabled())
    {
        DiaMsgRouter::SendPeerMsgToApp(new DIA_BASE_CMD((DIA_GEN_CMD *)
                                       (DIA_PE_CE_CACHE(ctxt->pEntry))));
    }
    if (IsDebugTraceEnabled())
    {
        cout << *((DIA_CER *)(DIA_PE_CE_CACHE(ctxt->pEntry))) << endl;
    }
    
    
    if(DIA_PE_IS_DISCOVERED(ctxt->pEntry))
    {
        AssociateDictIdForPeerRcvdCER(((DIA_CER *)(DIA_PE_CE_CACHE(ctxt->pEntry))),ctxt->pEntry);     
    }

    return (ret);
}



static 
int AssociateDictIdForPeerRcvdCEA(DIA_CEA* cea,PEER_ENTRY* pEntry)
{
    std::string DictionaryNames[MAX_DICT_IDS_PER_PEER];
    APPLICATION_TYPE type[MAX_DICT_IDS_PER_PEER];
    int noOfDict = 0;
    PEER_INFO pInfo;


    for (int noOfAppIds = 0; noOfAppIds < cea->countAuthApplicationId(); noOfAppIds++)
    {
        if(cea->getAuthApplicationId(noOfAppIds).value() !=0)
        {
            const char* dictName = DiaMgmt::GetDiaMgmt()->GetDictionaryName(cea->getAuthApplicationId(noOfAppIds).value());
            if(dictName != NULL)
            {
                DictionaryNames[noOfDict] = dictName;
                delete []dictName;
                type[noOfDict++] = DIA_AUTH_APP;
            }

        }
    }
    for (int noOfAcctIds = 0; noOfAcctIds < cea->countAcctApplicationId(); noOfAcctIds++)
    {
        if(cea->getAcctApplicationId(noOfAcctIds).value() !=0)
        {
            const char* dictName = DiaMgmt::GetDiaMgmt()->GetDictionaryName(cea->getAcctApplicationId(noOfAcctIds).value());
            if(dictName != NULL)
            {
                DictionaryNames[noOfDict] = dictName;
                delete []dictName;
                type[noOfDict++] = DIA_ACCT_APP;
            }

        }
    }
    pInfo.peerName = DIA_PE_HOST(pEntry);
    pInfo.realmName = DIA_PE_REALM(pEntry);
    if(DiaMgmt::GetDiaMgmt()->AssociateDictToPeer(&pInfo,noOfDict,DictionaryNames,type,true) == ITS_SUCCESS)
    {
        DT_DBG(("Sucessfully associated dict ids for newly discovered peer %s",pInfo.peerName));
    }
    else
    {
        DT_ERR(("Failed to  associate dict ids for newly discovered peer %s",pInfo.peerName));
    }
    return ITS_SUCCESS;
}


static
int ProcessCEA(PEER_STATE_CTXT* ctxt, ITS_EVENT *evt)
{
    int ret = ITS_SUCCESS;
    ITS_BOOLEAN matchSecurity = ITS_FALSE;
    ITS_BOOLEAN isCommonAppId = ITS_FALSE;
    /* Process-CEA */
    /* Check the Result Code
       If Result Code is success
       return ITS_SUCCESS else return error
    */

    DT_DBG(("ProcessCEA::"));

    DIA_CEA *lcea;
    lcea = itsDiaConfig.GetLocalCEA();

    if (ConvertToBaseCmd(ctxt) != ITS_DIA_SUCCESS)
    {
        DT_ERR(("ProcessCEA::Failed to Decode"));

        if (DIA_PE_CE_CACHE(ctxt->pEntry))
        {
            delete DIA_PE_CE_CACHE(ctxt->pEntry);
            DIA_PE_CE_CACHE(ctxt->pEntry) = NULL;
        }

        return (!ITS_SUCCESS);
    }

    DIA_CEA *cea = ((DIA_CEA *)DIA_PEER_ST_CURR_CMD(ctxt));
    DT_DBG(("CEA Received from the peer"));

    //Verify H-by-H Id and E-to-E Id of CER and CEA
    DIA_CER *cer = (DIA_CER*)DIA_PE_CE_CACHE(ctxt->pEntry);
    if(( NULL == cer) || (NULL == cea))
    {
	return (!ITS_SUCCESS);
    }
    stringstream ssCer,ssCea;
    DT_DBG(("CER Details %s ",cer->formDiameterMessageForRuleEngine(ssCer).str().c_str()));
    DT_DBG(("CEA Details %s ",cea->formDiameterMessageForRuleEngine(ssCea).str().c_str()));

    if( ((DIA_HDR&)((DIA_GEN_CMD *)cer)->getHeader()).hh != ((DIA_HDR&)((DIA_GEN_CMD *)cea)->getHeader()).hh ||
        ((DIA_HDR&)((DIA_GEN_CMD *)cer)->getHeader()).ee != ((DIA_HDR&)((DIA_GEN_CMD *)cea)->getHeader()).ee )
    {
	DT_ERR(("CEA Received with mismatch H-by-H-ID or E-to-E-ID"));
	DT_ERR(("CER [  H-by-H-ID : %u |  E-to-E-ID : %u  ] ",((DIA_HDR&)((DIA_GEN_CMD *)cer)->getHeader()).hh , ((DIA_HDR&)((DIA_GEN_CMD *)cer)->getHeader()).ee ));
	DT_ERR(("CEA [  H-by-H-ID : %u |  E-to-E-ID : %u  ] ",((DIA_HDR&)((DIA_GEN_CMD *)cea)->getHeader()).hh , ((DIA_HDR&)((DIA_GEN_CMD *)cea)->getHeader()).ee ));
	DIA_Alarm(15000, __FILE__, __LINE__," CER [  H-by-H-ID : %u |  E-to-E-ID : %u  ] CEA [  H-by-H-ID : %u |  E-to-E-ID : %u  ] ",
			((DIA_HDR&)((DIA_GEN_CMD *)cer)->getHeader()).hh , ((DIA_HDR&)((DIA_GEN_CMD *)cer)->getHeader()).ee,
			((DIA_HDR&)((DIA_GEN_CMD *)cea)->getHeader()).hh , ((DIA_HDR&)((DIA_GEN_CMD *)cea)->getHeader()).ee);
 	return !ITS_SUCCESS;
    }

    /* Send Message with Indication to App , if flag enabled*/
    if (IsPeerMsgToAppEnabled())
    {
        DiaMsgRouter::SendPeerMsgToApp(new DIA_BASE_CMD((DIA_GEN_CMD *)cea));
    }
    if (IsDebugTraceEnabled())
    {
        cout << *cea << endl;
    }

    const OriginHost& oh = cea->getOriginHost();
    const OriginRealm& orlm = cea->getOriginRealm();

    const char* hostName = oh.value().c_str();
    const char* realmName = orlm.value().c_str();

    const char*lHost = itsDiaConfig.getLocalHostName();
    const char*lRealm = itsDiaConfig.getLocalRealmName();

    if ((strcasecmp(realmName, lRealm) == 0) && (strcasecmp(hostName, lHost) == 0))
    {
        DT_ERR(("Local and Remote identity is same peerName = %s, Realm = %s",
                 hostName, realmName));

        DIA_Alarm(15000, __FILE__, __LINE__, "Peer =%s: Realm=%s",
                   hostName, realmName);
        return !ITS_SUCCESS;
    }

    PEER_ENTRY *entry = NULL;

    if (!PEER_TABLE->FindEntry(hostName,
                              realmName,
                              entry))
    {
        DT_ERR(("CEA Received from Unknown Peer"));
        DIA_Alarm(15006, __FILE__, __LINE__, "Peer =%s:Realm=%s",
                  DIA_PE_HOST(ctxt->pEntry), DIA_PE_REALM(ctxt->pEntry));
        return !ITS_SUCCESS;
    }
    if (cea->getResultCode().value() != ITS_DIA_SUCCESS || cea->isError())
    {
        ret = cea->getResultCode().value();
        if( cea->isError())
        {
            DT_WRN(("CEA Received with E bit set"));
        }
        DT_WRN(("CEA Received with Resultcode:%d", ret));
        DIA_Alarm(15005, __FILE__, __LINE__, "Peer =%s:Realm=%s:CmdCode=%d:ResultCode=%d",
                  DIA_PE_HOST(ctxt->pEntry), DIA_PE_REALM(ctxt->pEntry),
                  cea->getCommandCode(), ret);
    }

    if (cea->containsErrorMessage())
    {
        DT_ERR(("ProcessCEA: CEA Contains Error Message %s",
                          cea->getErrorMessage().value().c_str()));
    }

    /*
     * Check Whether the Peer has advertised itself as Relay in CEA.
     * If Relay AppId is found, save it as relay in peerEntry.
     * Fix for the issue 902 in whizible.
     */
    DIA_PE_IS_RELAY(ctxt->pEntry) = false;
    for (int j = 0; j < cea->countAuthApplicationId(); j++)
    {
        if (cea->getAuthApplicationId(j).value() ==
            RESFILE_ParseNum(DIA_RELAY_APP_ID_STRING))
        {
            DIA_PE_IS_RELAY(ctxt->pEntry) = true;
            break;
        }
    }

    /* First Check the Inband Security Id */
    if (cea->countInbandSecurityId())
    {
        DIA_PE_IS_INBAND_SEC_MATCH(
                DIA_PEER_ST_ENTRY(ctxt)) = ITS_FALSE;
        for (int i = 0; i < lcea->countInbandSecurityId(); i++)
        {
            for (int j = 0; j < cea->countInbandSecurityId(); j++)
            {
                if (lcea->getInbandSecurityId(i).value() ==
                    cea->getInbandSecurityId(j).value())
                {
                    matchSecurity = ITS_TRUE;
                    if (lcea->getInbandSecurityId(i).value() ==
                        DIA_TLS)
                    {
                        DIA_PE_IS_INBAND_SEC_MATCH(
                            DIA_PEER_ST_ENTRY(ctxt)) = ITS_TRUE;
                        DT_DBG(("ProcessCEA: Inband security matched as TLS."));
                    }
                    break;
                }
            }
        }

        if (!matchSecurity)
        {
            ret = ITS_DIA_NO_COMMON_SECURITY;
            DT_ERR(("Process-CER::Failure Error : %s", PERM_ERR_CODE_TO_TEXT(ret)));
            return ret;
        }
    }

    for (int m = 0; m < lcea->countAuthApplicationId(); m++)
    {
        for (int n = 0; n < cea->countAuthApplicationId(); n++)
       {
           if (lcea->getAuthApplicationId(m).value() ==
                 cea->getAuthApplicationId(n).value())
           {
               isCommonAppId = ITS_TRUE;
           }
       }
    }

    for (int m = 0; m < lcea->countAcctApplicationId(); m++)
    {
        for (int n = 0; n < cea->countAcctApplicationId(); n++)
        {
            if (lcea->getAcctApplicationId(m).value() ==
                  cea->getAcctApplicationId(n).value())
            {
                isCommonAppId = ITS_TRUE;
            }
        }
    }

    for (int i = 0; i < lcea->countVendorSpecificApplicationId(); i++)
    {
        for (int j = 0; j < cea->countVendorSpecificApplicationId(); j++)
        {
            const VendorSpecificApplicationId& lvs =
                     lcea->getVendorSpecificApplicationId(i);

            const VendorSpecificApplicationId& vs =
                     cea->getVendorSpecificApplicationId(j);

            if (lvs.containsAuthApplicationId() &&
                    vs.containsAuthApplicationId())
            {
                if (lvs.getAuthApplicationId().value() ==
                       (vs.getAuthApplicationId().value()))
                {
                        isCommonAppId = ITS_TRUE;
                }
            }

            if (lvs.containsAcctApplicationId() &&
                    vs.containsAcctApplicationId())
            {
                if (lvs.getAcctApplicationId().value() ==
                       (vs.getAcctApplicationId().value()))
                {
                     isCommonAppId = ITS_TRUE;
                }
            }

            for (int k = 0; k < lvs.countVendorId(); k++)
            {
                for (int l = 0; l < vs.countVendorId(); l++)
                {
                    if (lvs.getVendorId(k).value() ==
                            vs.getVendorId(l).value())
                    {
                       isCommonAppId = ITS_TRUE;
                    }
                }
            }

        }
    }
    
    if(isCommonAppId && DIA_PE_IS_DISCOVERED(ctxt->pEntry))
    {
        AssociateDictIdForPeerRcvdCEA(cea,ctxt->pEntry);     
    }

    if (!isCommonAppId)
    {
        int retVal = ITS_DIA_NO_COMMON_APP;
        DT_WRN(("Process-CEA::%s", PERM_ERR_CODE_TO_TEXT(retVal)));
        DIA_Alarm(15000, __FILE__, __LINE__, "Peer =%s: Realm=%s: ret=%s",
                   DIA_PE_HOST(ctxt->pEntry), DIA_PE_REALM(ctxt->pEntry),
                                          PERM_ERR_CODE_TO_TEXT(retVal));
    }


    if (DIA_PE_CE_CACHE(ctxt->pEntry))
    {
        delete DIA_PE_CE_CACHE(ctxt->pEntry);
        DIA_PE_CE_CACHE(ctxt->pEntry) = NULL;
    }

    DIA_PE_CE_CACHE(ctxt->pEntry) = (DIA_GEN_CMD *)ctxt->currCmd;

    time(&(DIA_PE_CONEST_TIME(ctxt->pEntry)));

    if (ret == ITS_SUCCESS)
    {
       DIA_Alarm(15002, __FILE__, __LINE__, "Peer =%s: Realm=%s",
                  DIA_PE_HOST(ctxt->pEntry), DIA_PE_REALM(ctxt->pEntry));

       /* check if dynamic discovery is Enabled &
        * CEA is received from Dynamically discovered PEER
        */
       if ((itsDiaConfig.isPeerDiscoveryEnabled())
             && (DIA_PE_IS_DISCOVERED(entry))
             && (DIA_PE_IS_FIRST_CAP_EXCH(entry)))
       {
           if (DecodeSupportedApp(ctxt) == ITS_SUCCESS)
           {
               DT_DBG(("Successfully added Destination Host Added to Realm\n"));
               DIA_PE_IS_FIRST_CAP_EXCH(entry) = false;
           }
           else
           {
               DT_DBG(("Failed to  add Destination Host Added to Realm\n"));
           }
       }
    }

    return (ret);
}

static
int ProcessMsg(PEER_STATE_CTXT* ctxt, ITS_EVENT *evt)
{
    /* ProcessMsg */
    int ret = ITS_SUCCESS;
    DT_DBG(("ProcessMsg::"));

#ifdef CALC_LATENCY
    {
        ITS_OCTET *msg = &evt->data[sizeof(ITS_USHORT)];
        ITS_UINT msgLen = (evt->len - sizeof(ITS_USHORT));
        if (msgLen >= 20)
        {
            ITS_UINT h2h = ntohl(*((ITS_UINT*)(msg+12)));
            ITS_UINT e2e = ntohl(*((ITS_UINT*)(msg+16)));
            msgTimeStore.AddEntry(h2h, e2e);
        }
    }
#endif

    evt->src = DIA_NET_INST;
    if (itsDiaConfig.IsMsgRedundancyEnabled())
    {
        //multicast the message to active  and back node
        if (DSM_MulticastStackEventToFtGroupMembers(
                      SESSION_TABLE_FT_GROUP_ID,
                      *evt,
                      DIA_GCS_NET_INST,
                      DIASTACK_TQ_INST) == ITS_SUCCESS)
        {
            DT_DBG(("Upstream Msg Multicasted"));
        }
        else
        {
            //ret = TRANSPORT_PutEvent(DIASTACK_TQ_INST, evt);
            ret = DiaUtils::PutEventReference(DIASTACK_TQ_INST, evt);
        }
    }
    else
    {
        ITS_OCTET *msg = &evt->data[sizeof(ITS_USHORT)];
        int evtLen = evt->len - sizeof(ITS_USHORT);

        int dest = DIASTACK_TQ_INST;
        string sId = "";

        if (DiaUtils::GetSessionString(msg, sId) == ITS_SUCCESS)
        {
            if (sId.length() > 0)
            {
                dest = DiaUtils::GetStackTQInst(sId.c_str());
            }
        }

        ret = DiaUtils::PutEventReference(dest, evt);
        DT_DBG(("ProcessMsg::Ret = %d\n Dest = %d", ret, dest));

    }
    DT_DBG(("ProcessMsg::Ret = %d\n", ret));


    if (DIA_PEER_ST_CURR_CMD(ctxt))
    {
        delete DIA_PEER_ST_CURR_CMD(ctxt);
        DIA_PEER_ST_CURR_CMD(ctxt) = NULL;
    }

    return ret;
}

static
int ProcessDWR(PEER_STATE_CTXT* ctxt, ITS_EVENT *evt)
{
   int ret;

    /* ProcessDWR */
    DT_DBG(("ProcessDWR::"));

    if ((ret = ConvertToBaseCmd(ctxt)) != ITS_DIA_SUCCESS)
    {
        DT_ERR(("ProcessDWR::Decode Failed : %s",PERM_ERR_CODE_TO_TEXT(ret)));
    }

    if (IsDebugTraceEnabled() && ret == ITS_DIA_SUCCESS)
    {
        cout << "DWR Received " << endl;
        cout << *((DIA_DWR *)(DIA_PEER_ST_CURR_CMD(ctxt))) << endl;
    }

    if (DIA_PEER_ST_CURR_CMD(ctxt))
    {
        delete DIA_PEER_ST_CURR_CMD(ctxt);
        DIA_PEER_ST_CURR_CMD(ctxt) = NULL;
    }

    return (ret);
}

static
int ProcessDWA(PEER_STATE_CTXT* ctxt, ITS_EVENT *evt)
{
    int ret = ITS_SUCCESS;
    /* ProcessDWA */
    DT_DBG(("ProcessDWA::"));

    if (ConvertToBaseCmd(ctxt) != ITS_DIA_SUCCESS)
    {
        DT_ERR(("ProcessDWA::Decode Failure"));
        ret = !ITS_SUCCESS;
    }

    DIA_DWA *dwa = ((DIA_DWA *)DIA_PEER_ST_CURR_CMD(ctxt));
    const OriginHost& oh = dwa->getOriginHost();
    const OriginRealm& orlm = dwa->getOriginRealm();
    PEER_ENTRY *entry = NULL;

    if (!PEER_TABLE->FindEntry(oh.value().c_str(),
                              orlm.value().c_str(),
                              entry))
    {
        DT_ERR(("DWA Received from Unknown Peer"));
        DIA_Alarm(15006, __FILE__, __LINE__, "Peer =%s:Realm=%s",
                  DIA_PE_HOST(ctxt->pEntry), DIA_PE_REALM(ctxt->pEntry));
    }

    if (dwa->getResultCode().value() != ITS_DIA_SUCCESS || dwa->isError())
    {
        ret = dwa->getResultCode().value();
        if(dwa->isError())
        {
             DT_WRN(("DWA Received with E bit set"));
             cout << *((DIA_DWA *)(DIA_PEER_ST_CURR_CMD(ctxt))) << endl;
        }
        DT_WRN(("DWA Received with Resultcode:%d", ret));
        DIA_Alarm(15007, __FILE__, __LINE__, "Peer =%s:Realm=%s:CmdCode=%d:ResultCode=%d",
                  DIA_PE_HOST(ctxt->pEntry), DIA_PE_REALM(ctxt->pEntry),
                  dwa->getCommandCode(), ret);
    }

    if (IsDebugTraceEnabled() && ret == ITS_SUCCESS)
    {
        cout << "DWA Received " << endl;
        cout << *((DIA_DWA *)(DIA_PEER_ST_CURR_CMD(ctxt))) << endl;
    }

    if (DIA_PEER_ST_CURR_CMD(ctxt))
    {
        delete DIA_PEER_ST_CURR_CMD(ctxt);
        DIA_PEER_ST_CURR_CMD(ctxt) = NULL;
    }

    return (ret);
}

static
int SendCER(PEER_STATE_CTXT* ctxt, ITS_EVENT *evt)
{
    int ret;
    int len;
    ITS_OCTET *buff;

    DT_DBG(("SentCER::"));
    DIA_CER *cer;
    if(DIA_PE_CONN_TINFO(DIA_PEER_ST_ENTRY(ctxt)).securePort == 0)
    {
        cer = itsDiaConfig.GetLocalCER();
    }
    else
    {
        cer = itsDiaConfig.GetRFC6733LocalCER();
    }
  
    DiaSocketTransport *handle = DIA_PEER_ST_TRANS(ctxt);
   
 
    DiaUtils::EncodeMsg(cer, &buff, len);


    //set H-by-H Id and E-to-E Id 
    ITS_UINT hId = DiaUtils::GenerateHopByHopId();
    ITS_UINT eId = DiaUtils::GenerateEndToEndId();
    DIA_SET_HOP_BY_HOP(&buff[ITS_DIA_HHID_LOC], hId);
    DIA_SET_END_TO_END(&buff[ITS_DIA_EEID_LOC], eId);

    //Store the CER sent to Peer in the Peer_Entry, used to validate the H-H-Id and E-E-Id
    DIA_CER *lPeerCer=new DIA_CER(buff, len);
    DIA_PE_CE_CACHE(ctxt->pEntry) = (DIA_GEN_CMD *)lPeerCer;    

    ret = DiaMsgRouter::SendToPeer(handle, buff, len);
    if(ret == ITS_SUCCESS)
    {
        DIA_INC_PEER_CER_SENT(ctxt->pEntry);
    }

    free((char*) buff);
    buff = NULL;

    UPDATE_DIA_STATS_REQOUT(DIA_MSG_CE);

    return ret;

}

static
int SendCEA(int rCode, PEER_STATE_CTXT* ctxt, ITS_EVENT *evt)
{
    ITS_OCTET *buff = NULL, *msg = NULL;
    int ret, len = 0;
    DIA_GEN_CMD *cer = NULL;
    DIA_CEA *cea = NULL;
    DiaSocketTransport *handle = NULL;

    DT_DBG(("SentCEA::"));
    cer = DIA_PE_CE_CACHE(ctxt->pEntry);

    if(DIA_PE_TLS_EN(DIA_PEER_ST_ENTRY(ctxt)) &&
       DIA_PE_CONN_TINFO(DIA_PEER_ST_ENTRY(ctxt)).securePort==0)
    {
        cea = itsDiaConfig.GetLocalCEA();
    }
    else
    {
        cea = itsDiaConfig.GetRFC6733LocalCEA();
    }

    if (cer == NULL || cea == NULL)
    {
        DT_ERR(("SendCEA:: No CER Received or Invalid CEA in Cache"));
        return (!ITS_SUCCESS);
    }

    handle = DIA_PEER_ST_TRANS(ctxt);

    if (handle == NULL)
    {
        DT_ERR(("SendCEA:: Invalid Peer Transport"));
        return (!ITS_SUCCESS);
    }

    /* Set the Hop-By-Hop from CER Received */
    ((DIA_HDR&)((DIA_GEN_CMD *)cea)->getHeader()).hh =
            cer->getHeader().hh;

    /* Set the End-To-End from CER Received */
    ((DIA_HDR&)((DIA_GEN_CMD *)cea)->getHeader()).ee =
            cer->getHeader().ee;

    /*
     * check for the result code if its is not success set the error bit
     */

    if(rCode != ITS_DIA_SUCCESS)
    {
        DT_DBG(("SendCEA:Error code received setting error flag"));
        (((DIA_HDR&)((DIA_GEN_CMD *)cea)->getHeader()).flags).e=1;
    }
    else
    {
         (((DIA_HDR&)((DIA_GEN_CMD *)cea)->getHeader()).flags).e=0;
    }


    /* Set the Result Code */
    cea->setResultCode(ResultCode(rCode));

    /*
     * Print Answer message before sending to peer
     * Bridgewater requirement.
     */
    if (IsDebugTraceEnabled())
    {
        DT_DBG(("Send CEA"));
        cout << *cea << endl;
    }

    if (DiaUtils::EncodeMsg(cea, &buff, len) != ITS_SUCCESS)
    {
        DT_ERR(("Failed to Encode CEA"));
        return (!ITS_SUCCESS);
    }

    if ((buff == NULL) || (len ==0))
    {
        DT_ERR(("NULL CEA"));
        free((char*) buff);
        buff = NULL;
        return (!ITS_SUCCESS);
    }

    ret = DiaMsgRouter::SendToPeer(handle, buff, len);
    if (ret != ITS_SUCCESS)
    {
        DT_ERR(("SendCEA:: Failed to send CEA to Peer"));
    }
    else
    {
         time(&(DIA_PE_CONEST_TIME(ctxt->pEntry)));
         DIA_INC_PEER_CEA_SENT(ctxt->pEntry);
    }
    free((char*) buff);
    buff = NULL;

    UPDATE_DIA_STATS_ANSOUT(DIA_MSG_CE);

    if (ret == ITS_SUCCESS && rCode == ITS_DIA_SUCCESS)
    {
       DIA_Alarm(15002, __FILE__, __LINE__, "Peer =%s: Realm=%s",
                  DIA_PE_HOST(ctxt->pEntry), DIA_PE_REALM(ctxt->pEntry));
    }
    else
    {
        DIA_Alarm(15000, __FILE__, __LINE__, "Peer =%s: Realm=%s",
                   DIA_PE_HOST(ctxt->pEntry), DIA_PE_REALM(ctxt->pEntry));
        DiaErrHandler::UpdateErrorStats((ITS_UINT)(DIA_PE_INST(ctxt->pEntry)),rCode);
    }
    return ret;
}

static
int SendDPR(bool error, bool retrans,
            DisconnectCause cause, PEER_STATE_CTXT* ctxt, ITS_EVENT *evt)
{
    ITS_OCTET *buff;
    int ret, len;
    ITS_UINT hId = DiaUtils::GenerateHopByHopId();
    ITS_UINT eId = DiaUtils::GenerateEndToEndId();

    DT_DBG(("SentDPR::"));
    //DiaSocketTransport *handle = (DiaSocketTransport *)ctxt->trHandle;
    DiaSocketTransport *handle = DIA_PEER_ST_TRANS(ctxt);
    DIA_DPR dpr(error, false);
    DIA_CER *lcer;
    lcer = itsDiaConfig.GetLocalCER();

    dpr.setOriginHost(lcer->getOriginHost());
    dpr.setOriginRealm(lcer->getOriginRealm());
    dpr.setDisconnectCause(cause);

    if (ctxt->pEntry->disconectCause == DisconnectCause::BUSY)
    {
        DisconnectCause dCause(DisconnectCause::BUSY);
        dpr.setDisconnectCause(dCause);
    }
    else if (ctxt->pEntry->disconectCause == DisconnectCause::REBOOTING)
    {
        dpr.setDisconnectCause(cause);
    }
    else
    {
        // DO_NOT_WANT_TO_TALK_TO_YOU
        DisconnectCause dCause(DisconnectCause::DO_NOT_WANT_TO_TALK_TO_YOU);
        dpr.setDisconnectCause(dCause);
    }

    DiaUtils::EncodeMsg(&dpr, &buff, len);

    /*  Hop-By-Hop in the Message */
    DIA_SET_HOP_BY_HOP(&buff[12], hId);

    /* End-To-End in the Message */
    DIA_SET_END_TO_END(&buff[16], eId);

    ret = DiaMsgRouter::SendToPeer(handle, buff, len);
    if(ITS_SUCCESS == ret)
    {
        DIA_INC_PEER_DPR_SENT(ctxt->pEntry);
    }
    free((char*) buff);
    buff = NULL;

    UPDATE_DIA_STATS_REQOUT(DIA_MSG_DP);

    return ret;
}

static
int SendDPA(bool error, bool retrans,
            ITS_UINT result, PEER_STATE_CTXT* ctxt, ITS_EVENT *evt)
{
    ITS_OCTET *buff;
    int ret, len;

    DT_DBG(("SentDPA::"));
    ITS_OCTET *msg = &evt->data[sizeof(ITS_USHORT)];
    ITS_UINT msgLen = (evt->len - sizeof(ITS_USHORT));

    DiaSocketTransport *handle = DIA_PEER_ST_TRANS(ctxt);

    DIA_CER *lcer;
    lcer = itsDiaConfig.GetLocalCER();

    DIA_DPA dpa(error, retrans);
    dpa.setResultCode(ResultCode(result));
    dpa.setOriginHost(lcer->getOriginHost());
    dpa.setOriginRealm(lcer->getOriginRealm());

    /*
     * Print Answer message before sending to peer
     * Bridgewater requirement.
     */
    if (IsDebugTraceEnabled())
    {
        DT_DBG(("Send DPA"));
        cout << dpa << endl;
    }

    DiaUtils::EncodeMsg(&dpa, &buff, len);

    /* Copy in the Hop-By-Hop from the Message */
    memcpy(&buff[12], &msg[12], sizeof(ITS_UINT));

    /* Copy in the End-To-End from the Message */
    memcpy(&buff[16], &msg[16], sizeof(ITS_UINT));

    ret = DiaMsgRouter::SendToPeer(handle, buff, len);
    if(ITS_SUCCESS == ret)
    {
        DIA_INC_PEER_DPA_SENT(ctxt->pEntry);
        if(result != ITS_DIA_SUCCESS)
        {
            DiaErrHandler::UpdateErrorStats((ITS_UINT)(DIA_PE_INST(ctxt->pEntry)),result);
        }
    }

    free((char*) buff);
    buff = NULL;

    UPDATE_DIA_STATS_ANSOUT(DIA_MSG_DP);

    return ret;
}

static
int SendDWA(bool error, bool retrans,
            ITS_UINT result, PEER_STATE_CTXT* ctxt, ITS_EVENT *evt)
{
    ITS_OCTET *buff;
    int ret, len;
    ITS_OCTET *msg = &evt->data[sizeof(ITS_USHORT)];
    ITS_UINT msgLen = (evt->len - sizeof(ITS_USHORT));
    DiaSocketTransport *handle = DIA_PEER_ST_TRANS(ctxt);

    DT_DBG(("SentDWA::"));
    DIA_CER *lcer;
    lcer = itsDiaConfig.GetLocalCER();

    DIA_DWA dwa(error, retrans);

    dwa.setResultCode(ResultCode(result));
    dwa.setOriginHost(lcer->getOriginHost());
    dwa.setOriginRealm(lcer->getOriginRealm());

    /*
     * Print Answer message before sending to peer
     * Bridgewater requirement.
     */
    if (IsDebugTraceEnabled())
    {
        DT_DBG(("Send DWA"));
        cout << dwa << endl;
    }

    DiaUtils::EncodeMsg(&dwa, &buff, len);

    /* Copy in the Hop-By-Hop from the Message */
    memcpy(&buff[12], &msg[12], sizeof(ITS_UINT));

    /* Copy in the End-To-End from the Message */
    memcpy(&buff[16], &msg[16], sizeof(ITS_UINT));

    ret = DiaMsgRouter::SendToPeer(handle, buff, len);
    if(ITS_SUCCESS == ret)
    {
        DIA_INC_PEER_DWA_SENT(ctxt->pEntry);
        if(result != ITS_DIA_SUCCESS)
        {
            DiaErrHandler::UpdateErrorStats((ITS_UINT)(DIA_PE_INST(ctxt->pEntry)),result);
        }
    }

    free((char*) buff);
    buff = NULL;

    UPDATE_DIA_STATS_ANSOUT(DIA_MSG_DW);
    return ret;
}

static int
SendFailbackIndToApp(PEER_ENTRY *peer)
{
    /* Send Indication to Application */
    if (DiaMsgRouter::SendIndication(NULL, peer, NULL, FAILBACK_IND_FROM_STACK)
                                                       != ITS_SUCCESS)
    {
        DT_ERR(("Failed To send Indication to application"));
    }

   return (ITS_SUCCESS);


}


static
int SendMsg(PEER_STATE_CTXT* ctxt, ITS_EVENT *evt)
{
    ITS_OCTET *buff;
    int ret, len;
    ITS_OCTET *msg = evt->data;
    ITS_UINT msgLen = evt->len;
    buff = evt->data;
    len = evt->len;
    //DiaSocketTransport *handle = (DiaSocketTransport *)ctxt->trHandle;
    DiaSocketTransport *handle = DIA_PEER_ST_TRANS(ctxt);

#ifdef CALC_LATENCY
    {
        ITS_OCTET *msg = buff;
        ITS_UINT msgLen = len;
        if (msgLen >= 20)
        {
            ITS_UINT h2h = ntohl(*((ITS_UINT*)(msg+12)));
            ITS_UINT e2e = ntohl(*((ITS_UINT*)(msg+16)));
            msgTimeStore.AddEntry(h2h, e2e);
        }
    }
#endif

    ret = DiaMsgRouter::SendToPeer(handle, buff, len);

    return (ret);
}

static int
Failback(PEER_ENTRY *peer)
{
   DT_DBG(("FAILBACK:: Initiated"));
   /*
    * Retransmit the pending messages if pendingQ enabled.
    */
   if (DIA_PE_PENDING_Q(peer))
   {
        /* Set Failback true */
        DIA_PE_PENDING_Q(peer)->SetStopFailover(true);

        if (DiaMsgRouter::Failback(peer) != ITS_SUCCESS)
        {
            DT_ERR(("Failback:: Unable to Initiate Failback."));
        }
        else
        {
           DIA_PEER_CHK_IS_FAILOVERED(peer) = false;

           DT_DBG(("Failback::SUCCESS"));
           if (IsPeerMsgToAppEnabled())
           {
               SendFailbackIndToApp(peer);
           }
        }
   }
   return (ITS_SUCCESS);
}


static int
SendIndToApp(PEER_ENTRY *peer, int indicType)
{
    /* Send Indication to Application */
    if (DiaMsgRouter::SendIndication(NULL, peer, NULL, indicType)
            != ITS_SUCCESS)
    {   
        DT_ERR(("Failed To send Indication to application"));
    }
    return (ITS_SUCCESS);
}

static int
SendDiscIndToApp(PEER_ENTRY *peer)
{
    /* Send Indication to Application */
    if (DiaMsgRouter::SendIndication(NULL, peer, NULL, DISCONECT_IND_FROM_STACK)
                                                       != ITS_SUCCESS)
    {
        DT_ERR(("Failed To send Indication to application"));
    }

   return (ITS_SUCCESS);
}

/****************************************************************************
 *  Purpose:
 *        Process the messages in CLOSED state
 *
 *  Input Parameters:
 *        evt : Event to process
 *
 *  Input/Output Parameters:
 *      ctxt: PEER Context base class pointer
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *        ITS_SUCCESS : On successful CLOSED state process
 *        !ITS_SUCCESS: On unsuccessful CLOSED state process
 *
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
ITS_INT
Closed::ProcessEvent(void *vctxt, ITS_EVENT *evt)
{
    int ret;

    DiaSocketTransport *tr = NULL;
    DiaSocketTransport *accTr = NULL;
    DiaSocketTransport *connTr = NULL;

    PEER_STATE_CTXT* ctxt = (PEER_STATE_CTXT*)vctxt;

    /**
     * Fix for issue no 23 raised by Dhiranand.
     */
    if ((ctxt->evtType ==  PEER_EVT_I_PEER_DISC) ||
        (ctxt->evtType ==  PEER_EVT_R_PEER_DISC))
        return ITS_SUCCESS;


    DT_DBG(("PeerFsm:: ProcessEvent in CLOSED State"));
    switch(ctxt->evtType)
    {
    case PEER_EVT_START:
        DT_DBG(("PeerFsm:: CLOSED --> START"));
        DT_DBG(("Action: I-Snd-Conn-Req"));

        /*
         * IOT Bridgewater::Start Expiry timer if failed connect by this time
         * trigger timeout event
         */
        if (DIA_PE_EXPIRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
        {
            PeerTable::StopTimer(EXPIRY, ctxt->pEntry);
        }
        PeerTable::StartTimer(EXPIRY, ctxt->pEntry);

        DIA_PE_STATE(ctxt->pEntry) = PEER_ST_WAIT_CONN_ACK;
        DT_DBG(("PeerFsm:: State::PEER_ST_WAIT_CONN_ACK"));

        break;
    case PEER_EVT_R_CONN_CER:
    {
        DT_DBG(("PeerFsm:: CLOSED ---> R-Conn-CER"));

        DT_DBG(("Action: Process-CER: Send-CEA"));

        /* Process-CER */
        if ((ret = ProcessCER(ctxt, evt)) == ITS_DIA_SUCCESS)
        {
            DT_DBG(("Process-CER::Success"));
            /* Send CEA */
            if ((ret = SendCEA(ret, ctxt, evt)) == ITS_SUCCESS)
            {
                DIA_PE_STATE(ctxt->pEntry) = PEER_ST_R_OPEN;

                /* Make sure Initiator thread doesn't try to connect */
                DIA_PE_INIT_CONN(ctxt->pEntry) = false;
                DIA_PE_INIT_COUNT(ctxt->pEntry) = 0;

                /*
                 * Stop the RETRY Timer if already running.
                 */
                if (DIA_PE_RETRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
                {
                    PeerTable::StopTimer(RETRY, ctxt->pEntry);
                }

                /*
                 * Stop the EXPIRY Timer if already running.
                 */
                if (DIA_PE_EXPIRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
                {
                    PeerTable::StopTimer(EXPIRY, ctxt->pEntry);
                }

                DT_DBG(("SendCEA::Success::State::PEER_ST_R_OPEN"));

                /* Check for Initiate Failback after Sending CEA */

                if (DIA_PEER_CHK_IS_FAILBACK_ENABLED(ctxt->pEntry) &&
                            DIA_PEER_CHK_IS_FAILOVERED(ctxt->pEntry))
                {
                   Failback(ctxt->pEntry);
                }

                connTr =
                (DiaSocketTransport *)DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle;

                if (connTr)
                {
                    DT_WRN(("Signaling shutdown of connector transport"));
                    Disc(connTr);
                    DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
                    DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
                }
                /**
                 * The current Handle and Instance of Peer is updated with
                 * acceptor specs as it becomes active.
                 */
                DIA_PE_HANDLE(DIA_PEER_ST_ENTRY(ctxt)) =
                        DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle;
                DIA_PE_INST(DIA_PEER_ST_ENTRY(ctxt)) =
                        DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst;

#ifdef TLS_ENABLED
                ITSDiaConfig* cfg = &itsDiaConfig;
                if(cfg->isTlsEnable())
                {   
                    /**
                     * Initiating the TLS ServerProcedure
                     */
                    if (DIA_PE_TLS_EN(DIA_PEER_ST_ENTRY(ctxt)) &&
                            DIA_PE_IS_INBAND_SEC_MATCH(DIA_PEER_ST_ENTRY(ctxt)))
                    {
                        DT_DBG(("TLS Enabled for Peer"));
                        if (TlsServerProcedure(ctxt) != ITS_SUCCESS)
                        {

                            DT_ERR(("The TLS Server Procedure Failed.Aborting..."));
                            DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;
                            DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));
                            Cleanup(ctxt);

                            if (DIA_PEER_ST_TRANS(ctxt))
                            {
                                Disc(DIA_PEER_ST_TRANS(ctxt));
                                DIA_PEER_ST_ENTRY(ctxt)->trHandle = NULL;
                                DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
                                DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
                            }

                            connTr =
                                (DiaSocketTransport *)DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle;
                            if (connTr)
                            {
                                DT_WRN(("Signaling shutdown of connector transport"));
                                Disc(connTr);
                                DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
                                DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
                            }
                            /* Starting the Retry Timer after TLS Handshake failed */
                            PeerTable::StartTimer(RETRY, ctxt->pEntry);
                        }
                    }
                }
#endif
            }
            else
            {
                /* TODO: Check what the state should be? */
                DT_ERR(("SendCEA::Failure ret = %d", ret));
            }
        }
        else
        {
            DT_ERR(("Process-CER::Failure ret = %d", ret));

            /* Send CEA With appropriate error code*/
            ret = SendCEA(ret, ctxt, evt);
            DT_DBG(("SendCEA::Success"));

            if (DIA_PEER_ST_TRANS(ctxt))
            {
                Disc(DIA_PEER_ST_TRANS(ctxt));
                DIA_PEER_ST_ENTRY(ctxt)->trHandle = NULL;
                DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
                DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
            }

            connTr =
                (DiaSocketTransport *)DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle;
            if (connTr)
            {
                DT_WRN(("Signaling shutdown of connector transport"));
                Disc(connTr);
                DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
                DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
            }
        }

        break;
    }
    default:
        DT_ERR(("Invalid Event Type %d", ctxt->evtType));
        return (!ITS_SUCCESS);
    }

    return ITS_SUCCESS;
}

/********************************************************************/
/** Purpose:
 *      Process the Message in the Wait-Conn-Ack State
 *
 *  Input Parameters:
 *      None
 *
 *  Input/Output Parameters:
 *      void *vctxt, ITS_EVENT *evt.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for Sucessful.
 *
 *  Notes:
 *      None
 *
 *  See Also:
 *      None
 *
 **/
 /* Revision History:
 *
 *********************************************************************/
ITS_INT
WaitConnAck::ProcessEvent(void *vctxt, ITS_EVENT *evt)
{
    int ret = ITS_SUCCESS;
    DiaSocketTransport *accTr = NULL;
    DiaSocketTransport *connTr = NULL;


    DT_DBG(("PeerFsm:: ProcessEvent in WAIT-CONN-ACK State"));
    DiaSocketTransport *tr = NULL;

    PEER_STATE_CTXT* ctxt = (PEER_STATE_CTXT*)vctxt;

    switch(ctxt->evtType)
    {
    case PEER_EVT_I_RCV_CONN_ACK:
    {
        DT_DBG(("PeerFsm:: WAIT-CONN-ACK ---> I-Rcv-Conn-Ack"));
#ifdef TLS_ENABLED
        
        if(DIA_PE_TLS_EN(DIA_PEER_ST_ENTRY(ctxt)) &&
           DIA_PE_CONN_TINFO(DIA_PEER_ST_ENTRY(ctxt)).securePort!=0)
        {
            DT_DBG(("As the Peer is rfc6733 compliant, initiating the TLS handshake."));
            ret = TlsClientProcedure(ctxt);
        }
#endif
        if(ret != ITS_SUCCESS)
        {
            DT_ERR(("TLS handshake failed"));
            return !ITS_SUCCESS;
        }
        else if ((ret = SendCER(ctxt, evt)) == ITS_SUCCESS)
        {
            DT_DBG(("Send-CER::Success"));

            /**
             * Fix for issue No. 28 raised by Dhiranand
             * during validation of bridgewater ticket 1836.
             * The expiry timer was stopped due to NACK.
             * So the expiry timer is started if it is not
             * already started.
             */
            if (DIA_PE_EXPIRY_TIMER(ctxt->pEntry) == TIMER_BAD_SERIAL)
            {
                PeerTable::StartTimer(EXPIRY, ctxt->pEntry);
            }
            DIA_PE_STATE(ctxt->pEntry) = PEER_ST_WAIT_I_CEA;

            DT_DBG(("PeerFsm:: State::PEER_ST_WAIT_I_CEA"));
        }
        else
        {
            DT_ERR(("Send-CER::Failure ret = %d", ret));
        }

        break;
    }
    case PEER_EVT_I_RCV_CONN_NACK:
    {
        DT_DBG(("PeerFsm:: WAIT-CONN-ACK ---> I-Rcv-Conn-NAck"));
        DT_DBG(("Action: Cleanup"));

        DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;

        DIA_Alarm(15000, __FILE__, __LINE__, "Peer =%s: Realm=%s",
                  DIA_PE_HOST(ctxt->pEntry), DIA_PE_REALM(ctxt->pEntry));

        Cleanup(ctxt);

        DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));

        break;
    }
    case PEER_EVT_R_CONN_CER:
        DT_DBG(("PeerFsm:: WAIT-CONN-ACK ---> R-Conn-CER"));
        DT_DBG(("Action: Accept : Process-CER"));

        /* Process-CER */
        if ((ret = ProcessCER(ctxt, evt)) == ITS_DIA_SUCCESS)
        {
            DT_DBG(("Process-CER::Success"));

            DIA_PE_STATE(ctxt->pEntry) = PEER_ST_WAIT_CONN_ACK_ELECT;

            DT_DBG(("PeerFsm:: State::PEER_ST_WAIT_CONN_ACK_ELECT"));
        }
        else
        {
            DT_ERR(("Process-CER::Failure ret = %d", ret));
	   /* Send CEA With appropriate error code*/
	    ret = SendCEA(ret, ctxt, evt);
	    if (DIA_PEER_ST_TRANS(ctxt))
	    {
		    Disc(DIA_PEER_ST_TRANS(ctxt));
		    DIA_PEER_ST_ENTRY(ctxt)->trHandle = NULL;
		    DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
		    DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
		    connTr = (DiaSocketTransport *)DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle;
		    if (connTr)
		    {
			    DT_WRN(("Signaling shutdown of connector transport"));
			    Disc(connTr);
			    DIA_INC_PEER_CONNECTION_CLOSE_BY_DRE_COUNT(DIA_PEER_ST_ENTRY(ctxt));
			    DIA_INC_PEER_CONNECTION_TOTAL_TRANSPORT_DOWN_COUNT(DIA_PEER_ST_ENTRY(ctxt));
			    DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
			    DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
		    }
		    DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;
	    }
	}

	break;

    case PEER_EVT_TIMEOUT:

	DT_DBG(("PeerFsm:: WAIT-CONN-ACK ---> Timeout"));
	DT_DBG(("Action: Error"));

	ProcessError(ctxt, evt);

	DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;
	DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));

         /**
         * Starting the Retry timer after the peer moved to closed state
         * due to Expiry Timeout.(issue 2 raised by Dhiranand during
         * validation of bcgi ticket 1807).
         */
        DIA_PE_HANDLE(ctxt->pEntry) = NULL;
        if (DIA_PE_RETRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
        {
            PeerTable::StopTimer(RETRY, ctxt->pEntry);
        }
        PeerTable::StartTimer(RETRY, ctxt->pEntry);

        break;

    case PEER_EVT_R_PEER_DISC:
            accTr =
                (DiaSocketTransport *)DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle;

            if (accTr)
            {
                DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
                DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
            }
        break;
    case PEER_EVT_STOP:
        DT_DBG(("PeerFsm:: WAIT-CONN-ACK ---> Stop"));
        DT_DBG(("Action: Set State as PEER_ST_CLOSED"));

        DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;
        DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));

        /*
         * Stop the RETRY Timer if already running.
         */
        if (DIA_PE_RETRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
        {
           PeerTable::StopTimer(RETRY, ctxt->pEntry);
        }

        /*
         * Stop the EXPIRY Timer if already running.
         */
        if (DIA_PE_EXPIRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
        {
            PeerTable::StopTimer(EXPIRY, ctxt->pEntry);
        }

        break;

    default:
        DT_ERR(("Invalid Event Type"));

        return !ITS_SUCCESS;
    }

    return ITS_SUCCESS;
}

/********************************************************************/
/** Purpose:
 *      Process the Message in WAIT-I-CEA State
 *
 *  Input Parameters:
 *      None
 *
 *  Input/Output Parameters:
 *      void *vctxt, ITS_EVENT *evt.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for Sucessful.
 *
 *  Notes:
 *      None
 *
 *  See Also:
 *      None
 *
 **/
 /* Revision History:
 *
 *********************************************************************/
ITS_INT
WaitICEA::ProcessEvent(void *vctxt, ITS_EVENT *evt)
{
    int ret;
    DT_DBG(("PeerFsm:: ProcessEvent in WAIT-I-CEA State"));
    DiaSocketTransport *accTr = NULL, *connTr = NULL;

    PEER_STATE_CTXT* ctxt = (PEER_STATE_CTXT*)vctxt;

    switch(ctxt->evtType)
    {
    case PEER_EVT_I_RCV_CEA:

        DT_DBG(("PeerFsm:: WAIT-I-CEA ---> I-Rcv-CEA"));
        DT_DBG(("Action: Process-CEA"));

        /* Process-CEA */
        if ((ret = ProcessCEA(ctxt, evt)) == ITS_SUCCESS)
        {
            DT_DBG(("Process-CEA::Success"));
            DIA_PE_STATE(ctxt->pEntry) = PEER_ST_I_OPEN;
            DT_DBG(("PeerFsm:: State::PEER_ST_I_OPEN"));
            /*
             * Stop the RETRY Timer if already running.
             */
            if (DIA_PE_RETRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
            {
                PeerTable::StopTimer(RETRY, ctxt->pEntry);
            }

            /*
            * Stop the EXPIRY Timer if already running.
            */
            if (DIA_PE_EXPIRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
            {
                PeerTable::StopTimer(EXPIRY, ctxt->pEntry);
            }

            /**
             * Check for Initiate Failback after receiving CEA
             * Partial fix for issue Id:1119.
             */
            if (DIA_PEER_CHK_IS_FAILBACK_ENABLED(ctxt->pEntry) &&
                DIA_PEER_CHK_IS_FAILOVERED(ctxt->pEntry))
            {
                Failback(ctxt->pEntry);
            }

#ifdef TLS_ENABLED
            ITSDiaConfig* cfg = &itsDiaConfig;
            if(cfg->isTlsEnable())
            {
                /**
                 * Initiating the TLS ClientProcedure
                 */
                if (DIA_PE_TLS_EN(DIA_PEER_ST_ENTRY(ctxt)) && 
                   (DIA_PE_CONN_TINFO(DIA_PEER_ST_ENTRY(ctxt)).securePort==0)&&
                    DIA_PE_IS_INBAND_SEC_MATCH(DIA_PEER_ST_ENTRY(ctxt)))
                {
                    DT_DBG(("TLS Enabled for Peer"));
                    if (TlsClientProcedure(ctxt) != ITS_SUCCESS)
                    {

                        DT_ERR(("The TLS Client Procedure Failed.Aborting..."));
                        DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;
                        DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));
                        Cleanup(ctxt);

                        if (DIA_PEER_ST_TRANS(ctxt))
                        {
                            Disc(DIA_PEER_ST_TRANS(ctxt));
                            DIA_PEER_ST_ENTRY(ctxt)->trHandle = NULL;
                            DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
                            DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
                        }

                        if (DIA_PE_RETRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
                        {
                            PeerTable::StopTimer(RETRY, ctxt->pEntry);
                        }

                        /* Starting the Retry Timer after TLS Handshake failed */
                        PeerTable::StartTimer(RETRY, ctxt->pEntry);
                    }
                }
            }
#endif
        }
        else
        {
            DT_ERR(("Process-CEA::Failure ret = %d", ret));

            DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;
            DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));

            Cleanup(ctxt);

            accTr =
                (DiaSocketTransport *)DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle;

            connTr =
                (DiaSocketTransport *)DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle;

            if (accTr)
            {
                DT_WRN(("Signaling shutdown of acceptor transport"));
                Disc(accTr);
                DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
                DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
            }

            if (connTr)
            {
                DT_WRN(("Signaling shutdown of connector transport"));
                Disc(connTr);
                DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
                DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
            }

            if (DIA_PE_RETRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
            {
                PeerTable::StopTimer(RETRY, ctxt->pEntry);
            }

            /* Process CEA Failed. Start Retry Timer */
            PeerTable::StartTimer(RETRY, ctxt->pEntry);

            DIA_PEER_ST_ENTRY(ctxt)->trHandle = NULL;

            if (DIA_PE_RETRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
            {
                 PeerTable::StopTimer(RETRY, ctxt->pEntry);
            }

            /* Process CEA Failed. Start Retry Timer */
            PeerTable::StartTimer(RETRY, ctxt->pEntry);
        }

        break;

    case PEER_EVT_R_CONN_CER:

        DT_DBG(("PeerFsm:: WAIT-I-CEA ---> R-Conn-CER"));
        DT_DBG(("Action: Accept: Process-CER : Elect"));

        /* Process-CER */
        if ((ret = ProcessCER(ctxt, evt)) == ITS_DIA_SUCCESS)
        {
            DT_DBG(("Process-CER::Success"));
        }
        else
        {
            DT_ERR(("Process-CER::Failure ret = %d", ret));

            Cleanup(ctxt);

            return ret;
        }

        /* Elect */
        if ((ret = Elect(ctxt, evt)) == ITS_SUCCESS)
        {
            DT_DBG(("Elect::Success"));

            /* IOT::Election Issue: DigitalRoute
               DIA_PE_STATE(ctxt->pEntry) = PEER_ST_WAIT_RETURNS;
            */
        }
        else
        {
            DT_ERR(("Elect::Failure ret = %d", ret));
        }

        break;

    case PEER_EVT_I_PEER_DISC:

        DT_DBG(("PeerFsm:: WAIT-I-CEA ---> I-Peer_Disc"));

        DT_DBG(("Action: Disc"));

        DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;

        DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));
        if (DIA_PEER_ST_TRANS(ctxt))
        {
            Disc(DIA_PEER_ST_TRANS(ctxt));
            DIA_PEER_ST_ENTRY(ctxt)->trHandle = NULL;
            DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
            DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
        }

        /* IOT::Retry connection after disconnect */
        if (DIA_PE_RETRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
        {
            PeerTable::StopTimer(RETRY, ctxt->pEntry);
        }
        PeerTable::StartTimer(RETRY, ctxt->pEntry);

        break;


    case PEER_EVT_TIMEOUT:

        DT_DBG(("PeerFsm:: WAIT-I-CEA ---> Timeout"));
        DT_DBG(("Action: Error"));

        ProcessError(ctxt, evt);

        DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;
        DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));

        DIA_Alarm(15000, __FILE__, __LINE__, "Peer =%s: Realm=%s",
                DIA_PE_HOST(ctxt->pEntry), DIA_PE_REALM(ctxt->pEntry));

        /**
         * Starting the Retry timer after the peer moved to closed state
         * due to Expiry Timeout.(issue 2 raised by Dhiranand during
         * validation of bcgi ticket 1807).
         */
        DIA_PE_HANDLE(ctxt->pEntry) = NULL;
        if (DIA_PE_RETRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
        {
            PeerTable::StopTimer(RETRY, ctxt->pEntry);
        }
        PeerTable::StartTimer(RETRY, ctxt->pEntry);

        break;

    case PEER_EVT_R_PEER_DISC:

            accTr =
                (DiaSocketTransport *)DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle;
            if (accTr)
            {
                DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
                DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
            }
        break;

    default:
    case PEER_EVT_I_RCV_NON_CEA:
        DT_DBG(("PeerFsm:: WAIT-I-CEA ---> I-Rcv-Non-CEA"));
        DT_DBG(("Action: Error"));

        ProcessError(ctxt, evt);

        DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;
        DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));

        /**
         * Setting the Peer Entry Handle as Null
         */
        DIA_PE_HANDLE(ctxt->pEntry) = NULL;

        /* Retry connection after disconnect */
        if (DIA_PE_RETRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
        {
            PeerTable::StopTimer(RETRY, ctxt->pEntry);
        }
        PeerTable::StartTimer(RETRY, ctxt->pEntry);

        break;
    case PEER_EVT_STOP:
        DT_DBG(("PeerFsm:: WAIT-I-CEA ---> Stop"));
        DT_DBG(("Action: Set State as PEER_ST_CLOSED"));

        DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;
        DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));
 	Cleanup(ctxt);

        accTr =
            (DiaSocketTransport *)DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle;

        connTr =
            (DiaSocketTransport *)DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle;

        if (accTr)
        {
            DT_WRN(("Signaling shutdown of acceptor transport"));
            Disc(accTr);
            DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
            DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
        }

        if (connTr)
        {
            DT_WRN(("Signaling shutdown of connector transport"));
            Disc(connTr);
            DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
            DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
        }

        /*
         * Stop the RETRY Timer if already running.
         */
        if (DIA_PE_RETRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
        {
           PeerTable::StopTimer(RETRY, ctxt->pEntry);
        }

        /*
         * Stop the EXPIRY Timer if already running.
         */
        if (DIA_PE_EXPIRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
        {
            PeerTable::StopTimer(EXPIRY, ctxt->pEntry);
        }

        break;

    }
    return ITS_SUCCESS;
}

/********************************************************************/
/** Purpose:
 *      Process the event in the WAIT-CONN-ACK/ELECT State
 *
 *  Input Parameters:
 *      None
 *
 *  Input/Output Parameters:
 *      void *vctxt, ITS_EVENT *evt.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for Sucessful.
 *
 *  Notes:
 *      None
 *
 *  See Also:
 *      None
 *
 **/
 /* Revision History:
 *
 *********************************************************************/
ITS_INT
WaitConnAckElect::ProcessEvent(void *vctxt, ITS_EVENT *evt)
{
    int ret = ITS_SUCCESS;

    DT_DBG(("PeerFsm:: ProcessEvent in WAIT-CONN-ACK/ELECT State"));
    DiaSocketTransport *accTr = NULL, *connTr = NULL;

    PEER_STATE_CTXT* ctxt = (PEER_STATE_CTXT*)vctxt;

    switch(ctxt->evtType)
    {
    case PEER_EVT_I_RCV_CONN_ACK:

        DT_DBG(("PeerFsm:: WAIT-CONN-ACK/ELECT ---> I-Rcv-Conn-Ack"));
#ifdef TLS_ENABLED

        if( DIA_PE_TLS_EN(DIA_PEER_ST_ENTRY(ctxt)) &&
            DIA_PE_CONN_TINFO(DIA_PEER_ST_ENTRY(ctxt)).securePort!=0)
        {
            DT_DBG(("Start the TLS hand shake before CER"));
            ret = TlsClientProcedure(ctxt);
        }
#endif
        if(ret != ITS_SUCCESS)
        {
            DT_ERR(("TLS handshake failed"));
            return !ITS_SUCCESS;
        }
        else if ((ret = SendCER(ctxt, evt)) == ITS_SUCCESS)
        {
            DT_DBG(("Send-CER::Success"));
        }
        else
        {
            DT_ERR(("Send-CER::Failure ret = %d", ret));
            return !ITS_SUCCESS;
        }

        /* Elect */
        if ((ret = Elect(ctxt, evt)) == ITS_SUCCESS)
        {
            DT_DBG(("Elect::Success"));

            /**
             * Commenting out the State change as after
             * successful Election the state is changed
             * inside Elect(). Fix for issue no 25 raised by
             * Dhiranand during the validation of Bridgewater
             * ticket 1807.
             */
#if 0
            DIA_PE_STATE(ctxt->pEntry) = PEER_ST_WAIT_RETURNS;
            DT_DBG(("PeerFsm:: State::PEER_ST_WAIT_RETURNS"));
#endif
        }
        else
        {
            DT_ERR(("Elect::Failure ret = %d", ret));
        }

        break;

    case PEER_EVT_I_RCV_CONN_NACK:

        DT_DBG(("PeerFsm:: WAIT-CONN-ACK/ELECT ---> I-Rcv-Conn-NAck"));
        DT_DBG(("Action: Send-CEA"));

        /* Update the handle to that of the Acceptor */
        DIA_PEER_ST_ENTRY(ctxt)->trHandle =
            DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle;
        /* Update the instance to that of the Acceptor */
        DIA_PEER_ST_ENTRY(ctxt)->trInst =
            DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst;

        /* Send CEA */
        if ((ret = SendCEA(ITS_DIA_SUCCESS, ctxt, evt)) == ITS_SUCCESS)
        {
            DT_DBG(("SendCEA::Success"));

            DIA_PE_STATE(ctxt->pEntry) = PEER_ST_R_OPEN;

            DT_DBG(("PeerFsm:: State::PEER_ST_R_OPEN"));
            /*
             * Stop the RETRY Timer if already running.
             */
            if (DIA_PE_RETRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
            {
                PeerTable::StopTimer(RETRY, ctxt->pEntry);
            }

            DiaSocketTransport *tr = (DiaSocketTransport *)
                  (DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle);
            if (tr)
            {
                Disc(tr);
                DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
                DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
            }
        }
        else
        {
            /* TODO: Check what the state should be? */
            DT_ERR(("SendCEA::Failure ret = %d", ret));
        }

        break;

    case PEER_EVT_R_PEER_DISC:
        DT_DBG(("PeerFsm:: WAIT-CONN-ACK/ELECT ---> R-Peer-Disc"));
        DT_DBG(("Action: Disc"));

        DIA_PE_STATE(ctxt->pEntry) = PEER_ST_WAIT_CONN_ACK;
    DT_DBG(("PeerFsm:: State::PEER_ST_WAIT_CONN_ACK"));

        if (DIA_PEER_ST_TRANS(ctxt))
        {
            Disc(DIA_PEER_ST_TRANS(ctxt));
            DIA_PEER_ST_ENTRY(ctxt)->trHandle = NULL;
            DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
            DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
        }

        break;

    case PEER_EVT_R_CONN_CER:

        DT_DBG(("PeerFsm:: WAIT-CONN-ACK/ELECT ---> R-Conn-CER"));
        DT_DBG(("Action: Reject"));

        Reject(ctxt, evt);

        DIA_PE_STATE(ctxt->pEntry) = PEER_ST_WAIT_CONN_ACK_ELECT;
    DT_DBG(("PeerFsm:: State::PEER_ST_WAIT_CONN_ACK_ELECT"));

        break;

    case PEER_EVT_TIMEOUT:

        DT_DBG(("PeerFsm:: WAIT-CONN-ACK/ELECT ---> Timeout"));
        DT_DBG(("Action: Error"));

        ProcessError(ctxt, evt);

        DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;
        DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));

        /**
         * Starting the Retry timer after the peer moved to closed state
         * due to Expiry Timeout.(issue 2 raised by Dhiranand during
         * validation of bcgi ticket 1807).
         */
        DIA_PE_HANDLE(ctxt->pEntry) = NULL;
        if (DIA_PE_RETRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
        {
            PeerTable::StopTimer(RETRY, ctxt->pEntry);
        }
        PeerTable::StartTimer(RETRY, ctxt->pEntry);

        break;
    case PEER_EVT_STOP:
        DT_DBG(("PeerFsm:: WAIT-CONN-ACK/ELECT ---> Stop"));
        DT_DBG(("Action: Set State as PEER_ST_CLOSED"));

        DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;
        DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));

        /*
         * Stop the RETRY Timer if already running.
         */
        if (DIA_PE_RETRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
        {
           PeerTable::StopTimer(RETRY, ctxt->pEntry);
        }

        /*
         * Stop the EXPIRY Timer if already running.
         */
        if (DIA_PE_EXPIRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
        {
            PeerTable::StopTimer(EXPIRY, ctxt->pEntry);
        }
	
	Cleanup(ctxt);

        accTr =
            (DiaSocketTransport *)DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle;

        connTr =
            (DiaSocketTransport *)DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle;

        if (accTr)
        {
            DT_WRN(("Signaling shutdown of acceptor transport"));
            Disc(accTr);
            DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
            DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
        }

        if (connTr)
        {
            DT_WRN(("Signaling shutdown of connector transport"));
            Disc(connTr);
            DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
            DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
        }

        break;

    default:
        DT_ERR(("Invalid Event Type"));

        return !ITS_SUCCESS;

    }
    return ITS_SUCCESS;
}


/********************************************************************/
/** Purpose:
 *      Process the event in the WAIT-RETURNS State
 *
 *  Input Parameters:
 *      None
 *
 *  Input/Output Parameters:
 *      void *vctxt, ITS_EVENT *evt.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for Sucessful.
 *
 *  Notes:
 *      None
 *
 *  See Also:
 *      None
 *
 **/
 /* Revision History:
 *
 *********************************************************************/
ITS_INT WaitReturns::ProcessEvent(void *vctxt, ITS_EVENT *evt)
{
    int ret;
    DiaSocketTransport *accTr = NULL, *connTr = NULL;

    DT_DBG(("PeerFsm:: ProcessEvent in WAIT-RETURNS State"));

    PEER_STATE_CTXT* ctxt = (PEER_STATE_CTXT*)vctxt;

    switch(ctxt->evtType)
    {
    case PEER_EVT_WIN_ELECTION:
    case PEER_EVT_I_PEER_DISC:
    {
        DT_DBG(("Action: I-Disc : R-Send-CEA"));

       /* I-Disconnect after successful election */
        DiaSocketTransport *tr = (DiaSocketTransport *)
              (DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle);

        if (tr)
        {
            DT_WRN(("Signaling shutdown of connector transport"));
            Disc(tr);
            DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
            DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
        }

        DIA_PEER_ST_ENTRY(ctxt)->trHandle =
             DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle;
        /* Update the instance to that of the Acceptor */
        DIA_PEER_ST_ENTRY(ctxt)->trInst =
            DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst;

        /* Send CEA on responder*/
        if ((ret = SendCEA(ITS_DIA_SUCCESS, ctxt, evt)) == ITS_SUCCESS)
        {
            DT_DBG(("SendCEA::Success"));

            DIA_PE_STATE(ctxt->pEntry) = PEER_ST_R_OPEN;

            DT_DBG(("PeerFsm:: State::PEER_ST_R_OPEN"));
            /*
             * Stop the RETRY Timer if already running.
             */
            if (DIA_PE_RETRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
            {
                PeerTable::StopTimer(RETRY, ctxt->pEntry);
            }

#ifdef TLS_ENABLED
            ITSDiaConfig* cfg = &itsDiaConfig;
            if(cfg->isTlsEnable())
            {
                /**
                 * Initiating the TLS ServerProcedure
                 */
                if (DIA_PE_TLS_EN(DIA_PEER_ST_ENTRY(ctxt)) &&
                    (DIA_PE_CONN_TINFO(DIA_PEER_ST_ENTRY(ctxt)).securePort==0) &&
                        DIA_PE_IS_INBAND_SEC_MATCH(DIA_PEER_ST_ENTRY(ctxt)))
                {
                    DT_DBG(("TLS Enabled for Peer"));
                    if (TlsServerProcedure(ctxt) != ITS_SUCCESS)
                    {
                        DT_ERR(("The TLS Server Procedure Failed.Aborting..."));
                        DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;
                        DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));
                        Cleanup(ctxt);

                        if (DIA_PEER_ST_TRANS(ctxt))
                        {
                            Disc(DIA_PEER_ST_TRANS(ctxt));
                            DIA_PEER_ST_ENTRY(ctxt)->trHandle = NULL;
                            DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
                            DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
                        }

                        connTr =
                            (DiaSocketTransport *)DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle;
                        if (connTr)
                        {
                            DT_WRN(("Signaling shutdown of connector transport"));
                            Disc(connTr);
                            DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
                            DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
                        }
                        
                        /* Starting the Retry Timer after TLS Handshake failed */
                        PeerTable::StartTimer(RETRY, ctxt->pEntry);
                    }
                }
            }
#endif

        }
        else
        {
            /* TODO: Check what the state should be? */
            DT_ERR(("SendCEA::Failure ret = %d", ret));
        }

        break;
    }
    case PEER_EVT_I_RCV_CEA:
    {
        DT_DBG(("PeerFsm:: WAIT-RETURNS ---> I-Rcv-CEA"));
        DT_DBG(("Action: R-Disc"));

        /* Disconnect responder */
        /* R-Disconnect after successful election */
        DiaSocketTransport *tr = (DiaSocketTransport *)
              (DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle);

        if (tr)
        {
            DT_WRN(("Signaling shutdown of acceptor transport"));
            Disc(tr);
            DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
            DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
        }

        DT_DBG(("Action: Process-CEA"));

        /* Process-CEA */
        if ((ret = ProcessCEA(ctxt, evt)) == ITS_SUCCESS)
        {
            DIA_PEER_ST_ENTRY(ctxt)->trHandle =
                 DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle;
            /* Update the instance to that of the Connector */
            DIA_PEER_ST_ENTRY(ctxt)->trInst =
                 DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst;


            DIA_PE_STATE(ctxt->pEntry) = PEER_ST_I_OPEN;
            DT_DBG(("PeerFsm:: State::PEER_ST_I_OPEN"));
            /*
             * Stop the RETRY Timer if already running.
             */
            if (DIA_PE_RETRY_TIMER(ctxt->pEntry) !=TIMER_BAD_SERIAL)
            {
                PeerTable::StopTimer(RETRY, ctxt->pEntry);
            }
#ifdef TLS_ENABLED
            ITSDiaConfig* cfg = &itsDiaConfig;
            if(cfg->isTlsEnable())
            {
                /**
                 * Initiating the TLS ClientProcedure
                 */
                if (DIA_PE_TLS_EN(DIA_PEER_ST_ENTRY(ctxt)) &&
                        DIA_PE_IS_INBAND_SEC_MATCH(DIA_PEER_ST_ENTRY(ctxt)))
                {
                    DT_DBG(("TLS Enabled for Peer"));
                    if (TlsClientProcedure(ctxt) != ITS_SUCCESS)
                    {

                        DT_ERR(("The TLS Client Procedure Failed.Aborting..."));
                        DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;
                        DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));
                        Cleanup(ctxt);

                        if (DIA_PEER_ST_TRANS(ctxt))
                        {
                            Disc(DIA_PEER_ST_TRANS(ctxt));
                            DIA_PEER_ST_ENTRY(ctxt)->trHandle = NULL;
                            DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
                            DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
                        }

                        /* Starting the Retry Timer after TLS Handshake failed */
                        PeerTable::StartTimer(RETRY, ctxt->pEntry);
                    }
                }
                else
                {
                    DT_DBG(("TLS is not Enabled for Peer"));
                }
            }
#endif
        }
        else
        {
            DT_ERR(("Process-CEA::Failure ret = %d", ret));

            DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;
            DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));

            Cleanup(ctxt);

            connTr =
                (DiaSocketTransport *)DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle;

            if (connTr)
            {
                DT_WRN(("Signaling shutdown of connector transport"));
                Disc(connTr);
                DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
                DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
            }

            DIA_PEER_ST_ENTRY(ctxt)->trHandle = NULL;
        }

        break;
    }
    case PEER_EVT_R_PEER_DISC:

        DT_DBG(("PeerFsm:: WAIT-RETURNS ---> R-Peer-Disc"));
        DT_DBG(("Action: R-Disc"));

        /* Disconnect responder */
        if (DIA_PEER_ST_TRANS(ctxt))
        {
            Disc(DIA_PEER_ST_TRANS(ctxt));
            DIA_PEER_ST_ENTRY(ctxt)->trHandle = NULL;
            DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
            DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
        }

        DIA_PE_STATE(ctxt->pEntry) = PEER_ST_WAIT_I_CEA;
    DT_DBG(("PeerFsm:: State::PEER_ST_WAIT_I_CEA"));

        break;
    case PEER_EVT_R_CONN_CER:
        DT_DBG(("PeerFsm:: WAIT-RETURNS ---> R-Conn-CER"));
        DT_DBG(("Action: R-Reject"));

        Reject(ctxt, evt);

        DIA_PE_STATE(ctxt->pEntry) = PEER_ST_WAIT_RETURNS;
    DT_DBG(("PeerFsm:: State::PEER_ST_WAIT_RETURNS"));

        break;
    case PEER_EVT_TIMEOUT:
    {
    DT_DBG(("PeerFsm:: WAIT-RETURNS ---> Timeout"));
        DT_DBG(("Action: Error"));

        ProcessError(ctxt, evt);

        /**
         * In case of timeout both Connector and Acceptor should be
         * closed.
         */
        DiaSocketTransport *tr = (DiaSocketTransport *)
              (DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle);
        if (tr)
        {
            DT_WRN(("Signaling shutdown of acceptor transport"));
            Disc(tr);
            DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
            DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
        }

        DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;
        DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));

        /**
         * Starting the Retry timer after the peer moved to closed state
         * due to Expiry Timeout.(issue 2 raised by Dhiranand during
         * validation of bcgi ticket 1807).
         */
        DIA_PE_HANDLE(ctxt->pEntry) = NULL;
        if (DIA_PE_RETRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
        {
            PeerTable::StopTimer(RETRY, ctxt->pEntry);
        }
        PeerTable::StartTimer(RETRY, ctxt->pEntry);
    }
        break;
    case PEER_EVT_STOP:
        DT_DBG(("PeerFsm:: WAIT-RETURNS ---> Stop"));
        DT_DBG(("Action: Set State as PEER_ST_CLOSED"));

        DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;
        DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));

        /*
         * Stop the RETRY Timer if already running.
         */
        if (DIA_PE_RETRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
        {
           PeerTable::StopTimer(RETRY, ctxt->pEntry);
        }

        /*
         * Stop the EXPIRY Timer if already running.
         */
        if (DIA_PE_EXPIRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
        {
            PeerTable::StopTimer(EXPIRY, ctxt->pEntry);
        }

	Cleanup(ctxt);

        accTr =
            (DiaSocketTransport *)DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle;

        connTr =
            (DiaSocketTransport *)DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle;

        if (accTr)
        {
            DT_WRN(("Signaling shutdown of acceptor transport"));
            Disc(accTr);
            DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
            DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
        }

        if (connTr)
        {
            DT_WRN(("Signaling shutdown of connector transport"));
            Disc(connTr);
            DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
            DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
        }

        break;

    default:
        DT_ERR(("Invalid Event Type"));
        return !ITS_SUCCESS;
    }
    return ITS_SUCCESS;
}

/********************************************************************/
/** Purpose:
 *      Process the event in the R-OPEN State
 *
 *  Input Parameters:
 *      None
 *
 *  Input/Output Parameters:
 *      void *vctxt, ITS_EVENT *evt.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for Sucessful.
 *
 *  Notes:
 *      None
 *
 *  See Also:
 *      None
 *
 **/
 /* Revision History:
 *
 *********************************************************************/
ITS_INT ROpen::ProcessEvent(void *vctxt, ITS_EVENT *evt)
{
    int ret;
    PEER_STATE_CTXT* ctxt = (PEER_STATE_CTXT*)vctxt;
    DiaSocketTransport *tr = NULL, *connTr = NULL;

    DT_DBG(("PeerFsm:: ProcessEvent in R-OPEN State"));

    switch(ctxt->evtType)
    {
    case PEER_EVT_SEND_MESSAGE:
        DT_DBG(("PeerFsm:: R-OPEN ---> Send-Message"));

        DT_DBG(("Action: Send-Message"));

        /* R-Send-Message */
        /* Make sure the trHandle is that of the R-Conn */

        if ((ret = SendMsg(ctxt, evt)) == ITS_SUCCESS)
        {
            DT_DBG(("SendMsg::Success"));

            DIA_PE_STATE(ctxt->pEntry) = PEER_ST_R_OPEN;

        }
        else
        {
            DT_ERR(("SendMsg::Failure ret = %d", ret));
        }
        break;

    case PEER_EVT_R_RCV_MESSAGE:
        DT_DBG(("PeerFsm:: R-OPEN ---> R-Rcv-Message"));
        DT_DBG(("Action: Process"));

        if ((ret = ProcessMsg(ctxt, evt)) == ITS_SUCCESS)
        {
            DIA_PE_STATE(ctxt->pEntry) = PEER_ST_R_OPEN;

            DT_DBG(("ProcessMsg::Success"));
        }
        else
        {
            DT_ERR(("ProcessMsg::Failure ret = %d", ret));
        }

        break;

    case PEER_EVT_R_RCV_DWR:
    {
        DT_DBG(("PeerFsm:: R-OPEN ---> R-Rcv-DWR"));
        DT_DBG(("Action: Process-DWR : Send-DWA"));
        ITS_UINT rCode = ITS_DIA_SUCCESS;

        /* Process DWR */
        if ((rCode = ProcessDWR(ctxt, evt)) == ITS_DIA_SUCCESS)
        {
            DT_DBG(("ProcessDWR::Success"));
        }
        else
        {
            DT_ERR(("ProcessDWR::Failure ret = %d", rCode));
        }
        /* Send DWA */
        if ((ret = SendDWA(false, false, rCode, ctxt, evt)) == ITS_SUCCESS)
        {
            DIA_PE_STATE(ctxt->pEntry) = PEER_ST_R_OPEN;

            DT_DBG(("SendDWA::Success"));
        }
        else
        {
            DT_ERR(("SendDWA::Failure ret = %d", ret));
        }
        break;
    }
    case PEER_EVT_R_RCV_DWA:
        DT_DBG(("PeerFsm:: R-OPEN ---> R-Rcv-DWA"));
        DT_DBG(("Action: Process-DWA"));

        /* Process DWA */
        if ((ret = ProcessDWA(ctxt, evt)) == ITS_SUCCESS)
        {
            DT_DBG(("ProcessDWA::Success"));
            DIA_PE_STATE(ctxt->pEntry) = PEER_ST_R_OPEN;
        }
        else
        {
            DT_ERR(("ProcessDWA::Failure ret = %d", ret));
        }

        break;
    case PEER_EVT_R_CONN_CER:
        DT_DBG(("PeerFsm:: R-OPEN ---> R-Conn-CER"));
        DT_DBG(("Action: Rejecting the new incoming connection"));

        /**
         * Do not call Reject() as it is already in R-Open state
         * and will disconnect the acceptor. Hence commenting out
         * the Reject(). Fix for issue 5 raised by Dhirananda during
         * the validation of bcgi ticket 1807.
         */
#if 0
        Reject(ctxt, evt);
#endif

        DIA_PE_STATE(ctxt->pEntry) = PEER_ST_R_OPEN;

        break;

    case PEER_EVT_STOP:
    {
        DT_DBG(("PeerFsm:: R-OPEN ---> Stop"));
        DT_DBG(("Action: Send-DPR"));

        if (DIA_PEER_ST_CURR_CMD(ctxt) != NULL)
        {
            SendMsg(ctxt, evt);
        }
        else
        {
            DisconnectCause discause(DisconnectCause::REBOOTING);
            SendDPR(false, false, discause, ctxt, evt);
        }

        DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSING;
        DT_DBG(("PeerFsm:: State::PEER_ST_CLOSING"));

        /**
         * Added Expiry timer for Closing state as we send the
         * DPR. If DPA is not received, expiry timer will bring the
         * the state machine to closed state. Provided fix for issue
         * no.2 (Case 5 in peer state machine) raised by Dhiranand
         * during the validation of bcgi ticket 1807.
         */
        if (DIA_PE_EXPIRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
        {
            PeerTable::StopTimer(EXPIRY, ctxt->pEntry);
        }

	/* Flush the unsent data */
	DiaSocketTransport *tr = (DiaSocketTransport *)DIA_PE_HANDLE(ctxt->pEntry);
	/* This is an out parameter to FlushData method and we don't use it here */
	ITS_BOOLEAN isPeerToBeDisconnected = ITS_FALSE;
	tr->FlushData(isPeerToBeDisconnected, ITS_TRUE);

        PeerTable::StartTimer(EXPIRY, ctxt->pEntry);

        break;
    }
    case PEER_EVT_R_RCV_DPR:
    {
        int ret;
        PEER_ENTRY *peer = ctxt->pEntry;
        DT_DBG(("PeerFsm:: R-OPEN ---> R-Rcv-DPR"));

        if ((ret = ConvertToBaseCmd(ctxt)) != ITS_DIA_SUCCESS)
        {
            DT_ERR(("Decode Failure : %s",PERM_ERR_CODE_TO_TEXT(ret)));
        }

        DIA_DPR *dpr = (DIA_DPR *)DIA_PEER_ST_CURR_CMD(ctxt);
        DT_DBG(("DPR Received from the Peer"));
        if (IsDebugTraceEnabled() && (ret == ITS_DIA_SUCCESS))
        {
            cout << *dpr << endl;
        }

        DT_DBG(("Action: Send-DPA : R-Disc"));
        SendDPA(false, false, ret, ctxt, evt);

        /*
         * Remove the Entries from the Pending queue (Failover)
         */
        if (DIA_PE_PENDING_Q(ctxt->pEntry))
        {
            DIA_PE_PENDING_Q(ctxt->pEntry)->RemoveAllEntry();
        }

        DIA_PE_STATE(peer) = PEER_ST_CLOSED;
        DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));

        PEER_TABLE->ResetIsFailoveredFlag(ctxt->pEntry);

        DIA_Alarm(15010, __FILE__, __LINE__, "Peer =%s: Realm=%s",
                  DIA_PE_HOST(peer), DIA_PE_REALM(peer));

        /* Send Message with Indication to App, if flag enabled
           Give DPR to Application only after changing to CLOSED
           State no impact if app send DPA*/
        if (IsPeerMsgToAppEnabled() && ret == ITS_DIA_SUCCESS)
        {
            DiaMsgRouter::SendPeerMsgToApp(new DIA_BASE_CMD((DIA_GEN_CMD *)dpr));
        }

        // Disconnect Dynamic
        tr = (DiaSocketTransport *)DIA_PE_HANDLE(peer);

	/* This is an out parameter to FlushData method and we don't use it here */
	ITS_BOOLEAN isPeerToBeDisconnected = ITS_FALSE;
	tr->FlushData(isPeerToBeDisconnected, ITS_TRUE);
	
	Disc(tr);
        DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
        DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;

#if 0
        /* Removed this code to fix Issue 1637
         * In R-Open, connector socket is not there.
         */
         connTr =
           (DiaSocketTransport *)DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle;
        Disc(connTr);
#endif
        DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
        DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;

        /**
         * Setting the Peer Entry Handle as Null
         */
        DIA_PE_HANDLE(ctxt->pEntry) = NULL;

        HandleDPRDisconnectCause(dpr,ctxt->pEntry);
        Cleanup(ctxt);
        break;
    }
    case PEER_EVT_R_PEER_DISC:
    {
        PEER_ENTRY *peer = ctxt->pEntry;
        DT_DBG(("PeerFsm:: R-OPEN ---> R-Peer-Disc, Peer  = %s", DIA_PE_HOST(peer)));

        /* No need to perform action, dynamic should
           have already been disconnected
        */
        DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;
        DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));

        /* Send Transport Disconnect Indication to App */
        if (IsPeerMsgToAppEnabled())
        {
            SendDiscIndToApp(ctxt->pEntry);
        }
        DIA_Alarm(15001, __FILE__, __LINE__, "Reer=%s:Relam=%s",
                  DIA_PE_HOST(ctxt->pEntry), DIA_PE_REALM(ctxt->pEntry));

        /**
         * Disconnect and Initiate Failover
         * Partial fix for issue Id:1119.
         * Added check for isFailovered.
         */
        if(DIA_PEER_CHK_IS_FAILOVERED(ctxt->pEntry))
        {
           DT_DBG(("Failover Already Happened OR In-Progress."));
        }
        else if (DIA_PEER_CHK_IS_FAILOVER_ENABLED(ctxt->pEntry))
        {
           if ((ret = DiaWatchDogTransport::InitiateFailover
                      (DIA_PE_INST(ctxt->pEntry))) == ITS_SUCCESS)
           {
               DIA_PEER_CHK_IS_FAILOVERED(ctxt->pEntry) = true;

               DT_DBG(("InitiateFailover::Success."));
               if (IsPeerMsgToAppEnabled())
               {
                   DiaWatchDogTransport::SendFailoverIndToApp(ctxt->pEntry);
               }
           }
           else
           {
              DT_ERR(("InitiateFailover::Failed:%d",ret));
           }
        }
        else
        {
           DT_DBG(("Failover is NOT Enabled."));
        }

        /**
         * Commenting out the StopDWTimer functionality
         * as is being replaced by separate DW Thread.
         */
#if 0
        if (DIA_PE_DW_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
        {
            PeerTable::StopTimer(DEVICE_WATCHDOG, ctxt->pEntry);
        }
#endif

        DiaSocketTransport *tr = (DiaSocketTransport *)
              (DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle);

        if (tr)
        {
            DT_WRN(("Signaling shutdown of acceptor transport"));
	    /* This is an out parameter to FlushData method and we don't use it here */
	    ITS_BOOLEAN isPeerToBeDisconnected = ITS_FALSE;
	    tr->FlushData(isPeerToBeDisconnected, ITS_TRUE);
	    Disc(tr);
            DIA_INC_PEER_CONNECTION_TOTAL_TRANSPORT_DOWN_COUNT(DIA_PEER_ST_ENTRY(ctxt));
            DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
            DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
        }

        /**
         * Reseting the Peer entry handle to NULL.( Fix for issue
         * no 10 raised by Dhiranand during the validation of
         * bcgi ticket 1807)
         */
         DIA_PE_HANDLE(ctxt->pEntry) = NULL;

        /* Retry connection after disconnect */
        if (DIA_PE_RETRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
        {
            PeerTable::StopTimer(RETRY, ctxt->pEntry);
        }

        PEER_TABLE->ResetIsFailoveredFlag(ctxt->pEntry);

        if (itsDiaConfig.GetInitiateConnsOpt())
        {
            PeerTable::StartTimer(RETRY, ctxt->pEntry);
        }

        break;
    }
    case PEER_EVT_R_RCV_CER:
        DT_DBG(("PeerFsm:: R-OPEN ---> R-Rcv-CER"));
        /* Process-CER */
        if ((ret = ProcessCER(ctxt, evt)) == ITS_DIA_SUCCESS)
        {
            DT_DBG(("Process-CER::Success"));

            /* Send CEA */
            if ((ret = SendCEA(ret, ctxt, evt)) == ITS_SUCCESS)
            {
                DIA_PE_STATE(ctxt->pEntry) = PEER_ST_R_OPEN;

                DT_DBG(("SendCEA::Success"));
            }
            else
            {
                /* TODO: Check what the state should be? */
                DT_ERR(("SendCEA::Failure ret = %d", ret));
            }
        }
        else
        {
            DT_ERR(("Process-CER::Failure ret = %d", ret));

            /* Send CEA With appropriate error code*/
            ret = SendCEA(ret, ctxt, evt);
            DT_DBG(("SendCEA::Success"));

            if (DIA_PEER_ST_TRANS(ctxt))
            {
                Disc(DIA_PEER_ST_TRANS(ctxt));
                DIA_PEER_ST_ENTRY(ctxt)->trHandle = NULL;
                DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
                DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
            }
            DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;
            DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));
	    if (IsPeerMsgToAppEnabled())
	    {
		    SendIndToApp(ctxt->pEntry, PEER_DOWN_IND_FROM_STACK);
	    }
	    /* Flush the unsent data */
	    DiaSocketTransport *tr = (DiaSocketTransport *)DIA_PE_HANDLE(ctxt->pEntry);
	    /* This is an out parameter to FlushData method and we don't use it here */
	    ITS_BOOLEAN isPeerToBeDisconnected = ITS_FALSE;
	    tr->FlushData(isPeerToBeDisconnected, ITS_TRUE);
	    PEER_TABLE->ResetIsFailoveredFlag(ctxt->pEntry);
        }
        break;
    case PEER_EVT_R_RCV_CEA:
        DT_DBG(("PeerFsm:: R-OPEN ---> R-Rcv-CEA"));
        DT_DBG(("Action: Process-CEA"));

        /* Process-CEA */
        if ((ret = ProcessCEA(ctxt, evt)) == ITS_SUCCESS)
        {
            DT_DBG(("Process-CEA::Success"));
            DIA_PE_STATE(ctxt->pEntry) = PEER_ST_R_OPEN;
        }
        else
        {
            DT_ERR(("Process-CEA::Failure ret = %d", ret));

            DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;
            DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));
	    //TODO: check additional code handling done in DRE in this case
	    if (IsPeerMsgToAppEnabled())
	    {
		    SendIndToApp(ctxt->pEntry, PEER_DOWN_IND_FROM_STACK);
	    }
	    /* Flush the unsent data */
	    DiaSocketTransport *tr = (DiaSocketTransport *)DIA_PE_HANDLE(ctxt->pEntry);
	    /* This is an out parameter to FlushData method and we don't use it here */
	    ITS_BOOLEAN isPeerToBeDisconnected = ITS_FALSE;
	    tr->FlushData(isPeerToBeDisconnected, ITS_TRUE);

            PEER_TABLE->ResetIsFailoveredFlag(ctxt->pEntry);
            /* TODO: Cleanup */
            Cleanup(ctxt);

        }

        break;
    case PEER_EVT_I_PEER_DISC:
    {
        break;
    }
    default:
        DT_ERR(("Invalid Event Type"));

        return (!ITS_SUCCESS);
    }

    return ITS_SUCCESS;
}

/********************************************************************/
/** Purpose:
 *      Process the event in the I-OPEN State
 *
 *  Input Parameters:
 *      None
 *
 *  Input/Output Parameters:
 *      void *vctxt, ITS_EVENT *evt.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for Sucessful.
 *
 *  Notes:
 *      None
 *
 *  See Also:
 *      None
 *
 **/
 /* Revision History:
 *
 *********************************************************************/
ITS_INT
IOpen::ProcessEvent(void *vctxt, ITS_EVENT *evt)
{
    int ret;
    PEER_STATE_CTXT* ctxt = (PEER_STATE_CTXT*)vctxt;

    DT_DBG(("PeerFsm:: ProcessEvent in I-OPEN State"));

    switch(ctxt->evtType)
    {
    case PEER_EVT_SEND_MESSAGE:
        DT_DBG(("PeerFsm:: I-OPEN ---> Send-Message"));
        DT_DBG(("Action: Send-Message"));

        /* I-Send-Message */
        /* Make sure the trHandle is that of the I-Conn */

        if ((ret = SendMsg(ctxt, evt)) == ITS_SUCCESS)
        {
            DIA_PE_STATE(ctxt->pEntry) = PEER_ST_I_OPEN;

            DT_DBG(("SendMsg::Success"));
        }
        else
        {
            DT_ERR(("SendMsg::Failure ret = %d", ret));
        }

        break;

    case PEER_EVT_I_RCV_MESSAGE:
        DT_DBG(("PeerFsm:: I-OPEN ---> I-Rcv-Message"));
        DT_DBG(("Action: Process"));

        if ((ret = ProcessMsg(ctxt, evt)) == ITS_SUCCESS)
        {
            DIA_PE_STATE(ctxt->pEntry) = PEER_ST_I_OPEN;

            DT_DBG(("ProcessMsg::Success"));
        }
        else
        {
            DT_ERR(("ProcessMsg::Failure ret = %d", ret));
        }
        break;

    case PEER_EVT_I_RCV_DWR:
    {
        DT_DBG(("PeerFsm:: I-OPEN ---> I-Rcv-DWR"));
        DT_DBG(("Action: Process DWR : Send-DWA"));
        ITS_UINT rCode = ITS_DIA_SUCCESS;

         /* Process DWR */
        if ((rCode = ProcessDWR(ctxt, evt)) == ITS_DIA_SUCCESS)
        {
            DT_DBG(("ProcessDWR::Success"));
        }
        else
        {
            DT_ERR(("ProcessDWR::Failure ret = %d", rCode));
        }
        /* Send DWA */
        if ((ret = SendDWA(false, false, rCode, ctxt, evt)) == ITS_SUCCESS)
        {
            DIA_PE_STATE(ctxt->pEntry) = PEER_ST_I_OPEN;

            DT_DBG(("SendDWA::DWA::Success"));
        }
        else
        {
            DT_ERR(("SendDWA::DWA::Failure ret = %d", ret));
        }
        break;
    }

    case PEER_EVT_I_RCV_DWA:
        DT_DBG(("PeerFsm:: I-OPEN ---> I-Rcv-DWA"));
        DT_DBG(("Action: Process DWA"));

        /* Process DWA */
        if ((ret = ProcessDWA(ctxt, evt)) == ITS_SUCCESS)
        {
            DT_DBG(("ProcessDWA::Success"));
            DIA_PE_STATE(ctxt->pEntry) = PEER_ST_I_OPEN;
        }
        else
        {
            DT_ERR(("ProcessDWA::Failure ret = %d", ret));
        }

        break;
    case PEER_EVT_R_CONN_CER:
        DT_DBG(("PeerFsm:: I-OPEN ---> R-Conn-CER"));
        DT_DBG(("Action: R-Reject"));

        /* R-Reject */
        Reject(ctxt, evt);

        DIA_PE_STATE(ctxt->pEntry) = PEER_ST_I_OPEN;

        break;
    case PEER_EVT_STOP: 
    {
        DT_DBG(("PeerFsm:: I-OPEN ---> Stop"));
        DT_DBG(("Action: Send-DPR"));

        if (DIA_PEER_ST_CURR_CMD(ctxt) != NULL)
        {
            SendMsg(ctxt, evt);
        }
        else
        {
            DisconnectCause discause(DisconnectCause::REBOOTING);
            SendDPR(false, false, discause, ctxt, evt);
        }

        DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSING;
    DT_DBG(("PeerFsm:: State::PEER_ST_CLOSING"));

        /**
         * Added Expiry timer for Closing state as we send the
         * DPR. If DPA is not received, expiry timer will bring the
         * the state machine to closed state. Provided fix for issue
         * no.2 (Case 5 in peer state machine) raised by Dhiranand
         * during the validation of bcgi ticket 1807.
         */
        if (DIA_PE_EXPIRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
        {
            PeerTable::StopTimer(EXPIRY, ctxt->pEntry);
        }

	/* Flush the unsent data */
	DiaSocketTransport *tr = (DiaSocketTransport *)DIA_PE_HANDLE(ctxt->pEntry);
	/* This is an out parameter to FlushData method and we don't use it here */
	ITS_BOOLEAN isPeerToBeDisconnected = ITS_FALSE;
	tr->FlushData(isPeerToBeDisconnected, ITS_TRUE);
	PeerTable::StartTimer(EXPIRY, ctxt->pEntry);

        break;
    }
    case PEER_EVT_I_RCV_DPR:
    {
        int ret;
        DT_DBG(("PeerFsm:: I-OPEN ---> I-Rcv-DPR"));
        DT_DBG(("Action: Send-DPA : I-Disc"));
        PEER_ENTRY *peer = ctxt->pEntry;

        if ((ret = ConvertToBaseCmd(ctxt)) != ITS_DIA_SUCCESS)
        {
            DT_ERR(("DPR Decode Failure : %s",PERM_ERR_CODE_TO_TEXT(ret)));
        }

        DIA_DPR *dpr = (DIA_DPR *)DIA_PEER_ST_CURR_CMD(ctxt);
        DT_DBG(("DPR Received from the Peer"));

        if (IsDebugTraceEnabled() && (ret == ITS_DIA_SUCCESS))
        {
            cout << *dpr << endl;
        }

        SendDPA(false, false, ret, ctxt, evt);

        /*
         * Remove the Entries from the Pending queue (Failover)
         */
        if (DIA_PE_PENDING_Q(ctxt->pEntry))
        {
            DIA_PE_PENDING_Q(ctxt->pEntry)->RemoveAllEntry();
        }

        DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;
        DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));

        DIA_Alarm(15010, __FILE__, __LINE__, "Peer =%s: Realm=%s",
                  DIA_PE_HOST(peer), DIA_PE_REALM(peer));

        /* Send Message with Indication to App, if flag enabled
           Give DPR to Application only after changing to CLOSED
           State no impact if app send DPA*/
        if (IsPeerMsgToAppEnabled() && ret == ITS_DIA_SUCCESS)
        {
            DiaMsgRouter::SendPeerMsgToApp(new DIA_BASE_CMD((DIA_GEN_CMD *)dpr));
        }

        DiaSocketTransport *tr = (DiaSocketTransport *)DIA_PE_HANDLE(ctxt->pEntry);
	/* This is an out parameter to FlushData method and we don't use it here */
	ITS_BOOLEAN isPeerToBeDisconnected = ITS_FALSE;
	tr->FlushData(isPeerToBeDisconnected, ITS_TRUE);
	Disc(tr);
        DIA_INC_PEER_CONNECTION_TOTAL_TRANSPORT_DOWN_COUNT(DIA_PEER_ST_ENTRY(ctxt));
        DIA_PEER_ST_ENTRY(ctxt)->trHandle = NULL;
        DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
        DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;

        PEER_TABLE->ResetIsFailoveredFlag(ctxt->pEntry);

        HandleDPRDisconnectCause(dpr,ctxt->pEntry);
        Cleanup(ctxt);

        break;
    }
    case PEER_EVT_I_PEER_DISC:
    {
        DT_DBG(("PeerFsm:: I-OPEN ---> I-Peer-Disc"));
        DT_DBG(("Action: I-Disc"));

        // TODO Disconnect I
        DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;
        DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));

        /* Send Transport Disconnect Indication to App */
        if (IsPeerMsgToAppEnabled())
        {
            SendDiscIndToApp(ctxt->pEntry);
        }
        DIA_Alarm(15001, __FILE__, __LINE__,"Peer =%s: Realm = %s",
                  DIA_PE_HOST(ctxt->pEntry),DIA_PE_REALM(ctxt->pEntry));

        PEER_TABLE->ResetIsFailoveredFlag(ctxt->pEntry);

        /**
         * Disconnect and Initiate Failover
         * Partial fix for issue Id:1119.
         * Added check for isFailovered.
         */
        if(DIA_PEER_CHK_IS_FAILOVERED(ctxt->pEntry))
        {
           DT_DBG(("Failover Already Happened OR In-Progress."));
        }
        else if (DIA_PEER_CHK_IS_FAILOVER_ENABLED(ctxt->pEntry))
        {
           if ((ret = DiaWatchDogTransport::InitiateFailover
                      (DIA_PE_INST(ctxt->pEntry))) == ITS_SUCCESS)
           {
               DIA_PEER_CHK_IS_FAILOVERED(ctxt->pEntry) = true;

               DT_DBG(("InitiateFailover::Success."));
               if (IsPeerMsgToAppEnabled())
               {
                   DiaWatchDogTransport::SendFailoverIndToApp(ctxt->pEntry);
               }
           }
           else
           {
              DT_ERR(("InitiateFailover::Failed:%d",ret));
           }
        }
        else
        {
           DT_DBG(("Failover is NOT Enabled."));
        }

        /**
         * Commenting out the StopDWTimer functionality
         * as is being replaced by separate DW Thread.
         */
#if 0
        if (DIA_PE_DW_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
        {
            PeerTable::StopTimer(DEVICE_WATCHDOG, ctxt->pEntry);
        }
#endif

        DiaSocketTransport *tr = (DiaSocketTransport *)
              (DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle);

        if (tr)
        {
            DT_WRN(("Signaling shutdown of connector transport"));
	    /* This is an out parameter to FlushData method and we don't use it here */
	    ITS_BOOLEAN isPeerToBeDisconnected = ITS_FALSE;
	    tr->FlushData(isPeerToBeDisconnected, ITS_TRUE);
	    Disc(tr);
            DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
            DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
        }

        DIA_PEER_ST_ENTRY(ctxt)->trHandle = NULL;

        /* Retry connection after disconnect */
        if (DIA_PE_RETRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
        {
            PeerTable::StopTimer(RETRY, ctxt->pEntry);
        }

        if (itsDiaConfig.GetInitiateConnsOpt())
        {
            PeerTable::StartTimer(RETRY, ctxt->pEntry);
        }

        break;
    }

    case PEER_EVT_I_RCV_CER:
    {
        DT_DBG(("PeerFsm:: I-OPEN ---> I-Rcv-CER"));

        /* Process-CER */
        if ((ret = ProcessCER(ctxt, evt)) == ITS_DIA_SUCCESS)
        {
            DT_DBG(("Process-CER::Success"));

            /* Send CEA */
            if ((ret = SendCEA(ret, ctxt, evt)) == ITS_SUCCESS)
            {
                DIA_PE_STATE(ctxt->pEntry) = PEER_ST_I_OPEN;

                DT_DBG(("SendCEA::Success"));

                DT_DBG(("PeerFsm:: State::PEER_ST_I_OPEN"));
            }
            else
            {
                /* TODO: Check what the state should be? */
                DT_ERR(("SendCEA::Failure ret = %d", ret));
            }
        }
        else
        {
            DT_ERR(("Process-CER::Failure ret = %d", ret));

            /* Send CEA With appropriate error code*/
            ret = SendCEA(ret, ctxt, evt);
            DT_DBG(("SendCEA::Success"));
            if (DIA_PEER_ST_TRANS(ctxt))
            {
                Disc(DIA_PEER_ST_TRANS(ctxt));
                DIA_PEER_ST_ENTRY(ctxt)->trHandle = NULL;
                DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
                DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
            }

            DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;
            DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));
            
	    if (IsPeerMsgToAppEnabled())
	    {
		    SendIndToApp(ctxt->pEntry, PEER_DOWN_IND_FROM_STACK);
	    }
	    /* Flush the unsent data */
	    DiaSocketTransport *tr = (DiaSocketTransport *)DIA_PE_HANDLE(ctxt->pEntry);
	    /* This is an out parameter to FlushData method and we don't use it here */
	    ITS_BOOLEAN isPeerToBeDisconnected = ITS_FALSE;
	    tr->FlushData(isPeerToBeDisconnected, ITS_TRUE);

	    PEER_TABLE->ResetIsFailoveredFlag(ctxt->pEntry);
        }

        break;
    }
    case PEER_EVT_I_RCV_CEA:
    {
	DT_DBG(("PeerFsm:: I-OPEN ---> I-Rcv-CEA"));
        DT_DBG(("Action: Process-CEA"));

        /* Process-CEA */
        if ((ret = ProcessCEA(ctxt, evt)) == ITS_SUCCESS)
        {
            DT_DBG(("Process-CEA::Success"));
            DIA_PE_STATE(ctxt->pEntry) = PEER_ST_I_OPEN;
        }
        else
        {
            DT_ERR(("Process-CEA::Failure ret = %d", ret));

            DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;
            DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));

	    if (IsPeerMsgToAppEnabled())
	    {
		    SendIndToApp(ctxt->pEntry, PEER_DOWN_IND_FROM_STACK);
	    }
	    /* Flush the unsent data */
	    DiaSocketTransport *tr = (DiaSocketTransport *)DIA_PE_HANDLE(ctxt->pEntry);
	    /* This is an out parameter to FlushData method and we don't use it here */
	    ITS_BOOLEAN isPeerToBeDisconnected = ITS_FALSE;
	    tr->FlushData(isPeerToBeDisconnected, ITS_TRUE);

            PEER_TABLE->ResetIsFailoveredFlag(ctxt->pEntry);

            /* TODO: Cleanup */
            Cleanup(ctxt);
        }

        break;
    }
    case PEER_EVT_R_PEER_DISC:
        {
            break;
        }
    default:
        DT_ERR(("Invalid Event Type"));

        return (!ITS_SUCCESS);
    }

    return ITS_SUCCESS;
}

/********************************************************************/
/** Purpose:
 *      Process the event in the CLOSING State
 *
 *  Input Parameters:
 *      None
 *
 *  Input/Output Parameters:
 *      void *vctxt, ITS_EVENT *evt.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for Sucessful.
 *
 *  Notes:
 *      None
 *
 *  See Also:
 *      None
 *
 **/
 /* Revision History:
 *
 *********************************************************************/
ITS_INT
Closing::ProcessEvent(void *vctxt, ITS_EVENT *evt)
{
    DiaSocketTransport *tr;
    int ret;
    PEER_STATE_CTXT* ctxt = (PEER_STATE_CTXT*)vctxt;
    DIA_DPA *dpa = NULL;
    DiaSocketTransport *accTr = NULL;
    DiaSocketTransport *connTr = NULL;


    DT_DBG(("PeerFsm:: ProcessEvent in CLOSING State"));

    switch(ctxt->evtType)
    {
    case PEER_EVT_I_RCV_DPA:
    {
        DT_DBG(("PeerFsm:: CLOSING ---> I-Rcv-DPA"));

        if ((ret = ConvertToBaseCmd(ctxt)) != ITS_DIA_SUCCESS)
        {
            DT_ERR(("DPA Decode Failure : %s",PERM_ERR_CODE_TO_TEXT(ret)));
        }

        dpa = (DIA_DPA *)DIA_PEER_ST_CURR_CMD(ctxt);
        DT_DBG(("DPA Received from the Peer"));

        if (dpa->getResultCode().value() != ITS_DIA_SUCCESS || dpa->isError())
        {
            int retVal = dpa->getResultCode().value();
            if(dpa->isError())
            {
                DT_WRN(("DPA Received with E bit set"));
            }
            DT_WRN(("DPA Received with Resultcode:%d", retVal));
            DIA_Alarm(15008, __FILE__, __LINE__, "Peer =%s:Realm=%s:CmdCode=%d:ResultCode=%d",
                      DIA_PE_HOST(ctxt->pEntry), DIA_PE_REALM(ctxt->pEntry),
                      dpa->getCommandCode(), retVal);
        }

        PEER_TABLE->ResetIsFailoveredFlag(ctxt->pEntry);

        DIA_Alarm(15010, __FILE__, __LINE__, "Peer =%s: Realm=%s",
                   DIA_PE_HOST(ctxt->pEntry), DIA_PE_REALM(ctxt->pEntry));

        /*
         * Fix for the whizible issue 1138.
         * Stopping the expiry timer when the DPA is received.
         */
        if (DIA_PE_EXPIRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
        {
            PeerTable::StopTimer(EXPIRY, ctxt->pEntry);
        }

        /* Send Message with Indication to App, if flag enabled */
        if (IsPeerMsgToAppEnabled() && ret == ITS_DIA_SUCCESS)
        {
            DiaMsgRouter::SendPeerMsgToApp(new DIA_BASE_CMD((DIA_GEN_CMD *)dpa));
        }
        if (IsDebugTraceEnabled() && ret == ITS_DIA_SUCCESS)
        {
            cout << *dpa << endl;
        }
        DT_DBG(("Action: I-Disc"));

        // TODO: Disconnect I
        if (DIA_PEER_ST_TRANS(ctxt))
        {
            Disc(DIA_PEER_ST_TRANS(ctxt));
	        DIA_INC_PEER_CONNECTION_CLOSE_BY_DRE_COUNT(DIA_PEER_ST_ENTRY(ctxt));
	        DIA_INC_PEER_CONNECTION_TOTAL_TRANSPORT_DOWN_COUNT(DIA_PEER_ST_ENTRY(ctxt));
            DIA_PEER_ST_ENTRY(ctxt)->trHandle = NULL;
            DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
            DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
        }

        /* Let Reader thread give indication before updating state */
        /* If peer entry is removed based on the state before reader thread
           handles signal it is panic */
        //DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;
        //DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));

        /* Fixing the memory leak (fix by Yogesh) */
        if (DIA_PEER_ST_CURR_CMD(ctxt))
        {
            delete DIA_PEER_ST_CURR_CMD(ctxt);
            DIA_PEER_ST_CURR_CMD(ctxt) = NULL;
        }
        break;
    }

    case PEER_EVT_R_RCV_DPA:
    {
        DT_DBG(("PeerFsm:: CLOSING ---> R-Rcv-DPA"));

        if ((ret = ConvertToBaseCmd(ctxt)) != ITS_DIA_SUCCESS)
        {
            DT_ERR(("Decode Failed : %s",PERM_ERR_CODE_TO_TEXT(ret)));
        }

        dpa = (DIA_DPA *)DIA_PEER_ST_CURR_CMD(ctxt);
        DT_DBG(("DPA Received from the Peer"));

        if (dpa->getResultCode().value() != ITS_DIA_SUCCESS || dpa->isError())
        {
            int retVal = dpa->getResultCode().value();
            if(dpa->isError())
            {
               DT_WRN(("DPA Received with E bit set"));
            }
            DT_WRN(("DPA Received with Resultcode:%d", retVal));
            DIA_Alarm(15008, __FILE__, __LINE__, "Peer =%s:Realm=%s:CmdCode=%d:ResultCode=%d",
                      DIA_PE_HOST(ctxt->pEntry), DIA_PE_REALM(ctxt->pEntry),
                      dpa->getCommandCode(), retVal);
        }

        PEER_TABLE->ResetIsFailoveredFlag(ctxt->pEntry);

        DIA_Alarm(15010, __FILE__, __LINE__, "Peer =%s: Realm=%s",
                  DIA_PE_HOST(ctxt->pEntry), DIA_PE_REALM(ctxt->pEntry));

        /*
         * Fix for the whizible issue 1138.
         * Stopping the expiry timer when the DPA is received.
         */
        if (DIA_PE_EXPIRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
        {
            PeerTable::StopTimer(EXPIRY, ctxt->pEntry);
        }

        /* Send Message with Indication to App , if flag enabled*/
        if (IsPeerMsgToAppEnabled() && ret == ITS_DIA_SUCCESS)
        {
            DiaMsgRouter::SendPeerMsgToApp(new DIA_BASE_CMD((DIA_GEN_CMD *)dpa));
        }
        if (IsDebugTraceEnabled() && ret == ITS_DIA_SUCCESS)
        {
            cout << *dpa << endl;
        }

        DT_DBG(("Action: R-Disc"));

        // TODO: Verify Disconnect R
        if (DIA_PEER_ST_TRANS(ctxt))
        {
            Disc(DIA_PEER_ST_TRANS(ctxt));
	        DIA_INC_PEER_CONNECTION_CLOSE_BY_DRE_COUNT(DIA_PEER_ST_ENTRY(ctxt));
	        DIA_INC_PEER_CONNECTION_TOTAL_TRANSPORT_DOWN_COUNT(DIA_PEER_ST_ENTRY(ctxt));
            DIA_PEER_ST_ENTRY(ctxt)->trHandle = NULL;
            DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
            DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
        }

        /* Let Reader thread give indication before updating state */
        /* If peer entry is removed based on the state before reader thread
           handles signal it is panic */

        //DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;
        //DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));

        /* Fixing the memory leak (fix by Yogesh) */
        if (DIA_PEER_ST_CURR_CMD(ctxt))
        {
            delete DIA_PEER_ST_CURR_CMD(ctxt);
            DIA_PEER_ST_CURR_CMD(ctxt) = NULL;
        }

        break;
    }
    case PEER_EVT_TIMEOUT:
    {
        DT_DBG(("PeerFsm:: CLOSING ---> Timeout"));
        DT_DBG(("Action: Error"));

        ProcessError(ctxt, evt);

        DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;
        DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));

        PEER_TABLE->ResetIsFailoveredFlag(ctxt->pEntry);


        /* Retry connection after disconnect */
        if (DIA_PE_RETRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
        {
          PeerTable::StopTimer(RETRY, ctxt->pEntry);
        }
        //PeerTable::StartTimer(RETRY, ctxt->pEntry);
        if (DIA_PEER_GET_DIS_CAUSE(ctxt->pEntry) != DisconnectCause::DO_NOT_WANT_TO_TALK_TO_YOU)
        {
            if (itsDiaConfig.GetInitiateConnsOpt())
            {
                PeerTable::StartTimer(RETRY, ctxt->pEntry);
            }
        }
        else
        {
            DIA_PEER_GET_DIS_CAUSE(ctxt->pEntry) = DisconnectCause::REBOOTING;
        }
        break;
    }
    case PEER_EVT_I_PEER_DISC:
    {
        DT_DBG(("PeerFsm:: CLOSING ---> I-Peer-Disc"));
        DT_DBG(("Action: I-Disc"));
        connTr =
                (DiaSocketTransport *)DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle;

        if (connTr)
        {
            DT_WRN(("Signaling shutdown of connector transport"));
            Disc(connTr);
	        DIA_INC_PEER_CONNECTION_CLOSE_BY_DRE_COUNT(DIA_PEER_ST_ENTRY(ctxt));
	        DIA_INC_PEER_CONNECTION_TOTAL_TRANSPORT_DOWN_COUNT(DIA_PEER_ST_ENTRY(ctxt));
            DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
            DIA_PE_CONN_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
        }

        if (DIA_PE_RETRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
        {
            PeerTable::StopTimer(RETRY, ctxt->pEntry);
        }
        if (DIA_PEER_GET_DIS_CAUSE(ctxt->pEntry) != DisconnectCause::DO_NOT_WANT_TO_TALK_TO_YOU)
        {
            if (itsDiaConfig.GetInitiateConnsOpt())
            {
                PeerTable::StartTimer(RETRY, ctxt->pEntry);
            }
        }
        else
        {
            DIA_PEER_GET_DIS_CAUSE(ctxt->pEntry) = DisconnectCause::REBOOTING;
        }

        DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;
        DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));

        PEER_TABLE->ResetIsFailoveredFlag(ctxt->pEntry);
        break;
    }
    case PEER_EVT_R_PEER_DISC:
    {
        DT_DBG(("PeerFsm:: CLOSING ---> R-Peer-Disc"));
        DT_DBG(("Action: R-Disc"));
            accTr =
                (DiaSocketTransport *)DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle;

        if (accTr)
        {
            DT_WRN(("Signaling shutdown of acceptor transport"));
            Disc(accTr);
	        DIA_INC_PEER_CONNECTION_CLOSE_BY_DRE_COUNT(DIA_PEER_ST_ENTRY(ctxt));
	        DIA_INC_PEER_CONNECTION_TOTAL_TRANSPORT_DOWN_COUNT(DIA_PEER_ST_ENTRY(ctxt));
            DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trHandle = NULL;
            DIA_PE_ACC_SPECS(DIA_PEER_ST_ENTRY(ctxt)).trInst = 0;
        }

        if (DIA_PE_RETRY_TIMER(ctxt->pEntry) != TIMER_BAD_SERIAL)
        {
            PeerTable::StopTimer(RETRY, ctxt->pEntry);
        }

        if (DIA_PEER_GET_DIS_CAUSE(ctxt->pEntry) != DisconnectCause::DO_NOT_WANT_TO_TALK_TO_YOU)
        {
            if (itsDiaConfig.GetInitiateConnsOpt())
            {
                PeerTable::StartTimer(RETRY, ctxt->pEntry);
            }
        }
        else
        {
            DIA_PEER_GET_DIS_CAUSE(ctxt->pEntry) = DisconnectCause::REBOOTING;
        }


        DIA_PE_STATE(ctxt->pEntry) = PEER_ST_CLOSED;
        DT_DBG(("PeerFsm:: State::PEER_ST_CLOSED"));
        PEER_TABLE->ResetIsFailoveredFlag(ctxt->pEntry);
        break;
    }
    default:
        DT_ERR(("Invalid Event Type"));

        return !ITS_SUCCESS;
    }
    return ITS_SUCCESS;
}

#ifdef TLS_ENABLED

/********************************************************************/
/** Purpose:
 *     To start a client TLS session procedure and associate with
 *     socket.
 *
 *  Input Parameters:
 *      ctxt: PEER_STATE_CTXT* pointer
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS for Sucessful.
 *      !ITS_SUCCESS for Failure.
 *
 *  Notes:
 *      None
 *
 *  See Also:
 *      None
 *
 **/
 /* Revision History:
 *
 *********************************************************************/
static ITS_INT
TlsClientProcedure(PEER_STATE_CTXT* ctxt )
{
    int ret;
    Certificate * cliCert;
    TlsFactoryClass * tlsObj = NULL;

    ITSDiaConfig *cfg =  &itsDiaConfig;

    ITS_SocketInfo* info = ((DiaSocketTransport*)DIA_PE_CONN_SPECS
            (DIA_PEER_ST_ENTRY(ctxt)).trHandle)->GetSocket()->GetSocketInfo();

    DT_DBG(("TlsClientProcedure:Starting the TLS Client procedure"));
    if (clientCertificate)
    {
        cliCert = clientCertificate;
    }
    else
    {
        DT_ERR(("TlsClientProcedure: The Client Certificate is "\
                    "not initialized."));
        return !ITS_SUCCESS;
    }

    tlsObj = TlsFactoryClass::GetTlsInstance();
    if(tlsObj == NULL)
    {
        DT_ERR(("TlsClientProcedure: TlsFactoryClass is not Initialized"));
        return !ITS_SUCCESS;
    }

    TlsSession *clSess = tlsObj->CreateSession(CLIENT, info->socket);
    if (clSess == NULL)
    {
        DT_ERR(("TlsClientProcedure: Unable to Initiate Client Session."));
        delete clSess;
        clSess = NULL;
        return !ITS_SUCCESS;
    }

    ITS_INT  list[CIPHER_SUITE_LIST] = {0};

    DiaUtils::PopulateCipherSuiteList(list);
    /*DiaUtils::PopulateCipherSuiteList(cfg->GetSecurityConfig().GetCipherSuite()
            ,list);*/
    ret = clSess->CredentialSet(cliCert);
    if(ret != ITS_SUCCESS)
    {
        DT_ERR(("TlsClientProcedure: Failed While Setting Credentials"));
        delete clSess;
        clSess = NULL;
        return !ITS_SUCCESS;
    }
    ret = clSess->SetCipherSuite(list);
    if(ret != ITS_SUCCESS)
    {
        DT_ERR(("TlsClientProcedure: Failed to Set Cipher Suites"));
        return !ITS_SUCCESS;
    }
    DT_DBG(("**************Client Handshake"));
    ret = clSess->Handshake(itsDiaConfig.GetPeerTimers().GetWatchdog()-1);

    if(ret != ITS_SUCCESS)
    {
        DT_ERR(("TLS HandShake at client failed %d", ret));
        delete clSess;
        clSess = NULL;
        return !ITS_SUCCESS;
    }
    else
    {
        ((DiaSocketTransport*)DIA_PE_CONN_SPECS
         (DIA_PEER_ST_ENTRY(ctxt)).trHandle)->SetTlsSession(clSess);
        DT_DBG(("TLS Client  procedure Completed Successfully"));
        return ITS_SUCCESS;
    }
    return !ITS_SUCCESS;
}


/********************************************************************/
/** Purpose:
 *     To start a server TLS session procedure and associate with
 *     socket.
 *
 *  Input Parameters:
 *      ctxt: PEER_STATE_CTXT* pointer
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS for Sucessful.
 *      !ITS_SUCCESS for Failure.
 *
 *  Notes:
 *      None
 *
 *  See Also:
 *      None
 *
 **/
/* Revision History:
 *
 *********************************************************************/
static ITS_INT
TlsServerProcedure(PEER_STATE_CTXT* ctxt)
{
    int ret;
    Certificate *servCert;
    std::string dnsName;
    TlsFactoryClass * tlsObj = NULL;

    DT_DBG(("Starting the TLS procedure for Server"));

    if (serverCertificate)
    {
        servCert = serverCertificate;
    }
    else
    {
        DT_ERR(("TlsServerProcedure: The ServerCertificate is not"\
                    " initialized."));
        return !ITS_SUCCESS;
    }

    ITSDiaConfig *cfg =  &itsDiaConfig;


    ITS_SocketInfo* info = ((DiaSocketTransport*)DIA_PE_ACC_SPECS
            (DIA_PEER_ST_ENTRY(ctxt)).trHandle)->GetSocket()->GetSocketInfo();

    tlsObj = TlsFactoryClass::GetTlsInstance();
    if(tlsObj == NULL)
    {
        DT_ERR(("TlsServerProcedure: TlsFactoryClass is not Initialized"));
        return !ITS_SUCCESS;
    }

    TlsSession  *serSess = tlsObj->CreateSession(SERVER,info->socket);
    if (serSess == NULL)
    {
        DT_ERR(("TlsServerProcedure: Unable to create TLS server session."));
        delete serSess;
        serSess = NULL;
        return !ITS_SUCCESS;
    }
    //Populate the Cipher suite list.
    ITS_INT  list[CIPHER_SUITE_LIST] = {0};

    DiaUtils::PopulateCipherSuiteList(list);

    ret = serSess->CredentialSet(servCert);
    if(ret != ITS_SUCCESS)
    {
        DT_ERR(("TlsServerProcedure: Failed While Setting Credentials"));
        delete serSess;
        serSess = NULL;
        return !ITS_SUCCESS;
    }
    ret = serSess->SetCipherSuite(list);
    if(ret != ITS_SUCCESS)
    {
        DT_ERR(("TlsClientProcedure: Failed to Set Cipher Suites"));
        return !ITS_SUCCESS;
    }

    serSess->CertificateRequest();

    if ((ret = serSess->Handshake(itsDiaConfig.GetPeerTimers().GetWatchdog()-1)) != ITS_SUCCESS)
    {
        DT_ERR(("TLS Handshake at server failed"));
        delete serSess;
        serSess = NULL;
    }
    else
    {
        /**
         * Verifying the certificate received from client with the OriginHost
         * and OriginRealm if the IdentityVerification is enabled in xml
         */
        if (cfg->GetSecurityConfig().IsIdentityVerifyEnabled())
        {
            DT_DBG(("TlsServerProcedure: IdentityVerification Enabled"));

            DIA_GEN_CMD *ce =
                DIA_PE_CE_CACHE(DIA_PEER_ST_ENTRY(ctxt));
            if (!ce)
            {
                DT_ERR(("TlsServerProcedure: Capabilties Exchange is "\
                            "not proper."));
                return !ITS_SUCCESS;
            }
            DT_DBG(("The Host Name is: %s.",ce->getOriginHost()->value().c_str()));
            DT_DBG(("The Realm Name is: %s.",ce->getOriginRealm()->value().c_str()));
            if (serSess->VerifyCertificate((char *)ce->getOriginHost()->value().c_str(),
                                           (char *)ce->getOriginRealm()->value().c_str())
                                           == ITS_SUCCESS)
            {
                ((DiaSocketTransport*)DIA_PE_ACC_SPECS
                 (DIA_PEER_ST_ENTRY(ctxt)).trHandle)->SetTlsSession(serSess);
                DT_DBG(("TlsServerProcedure: TLS procedure for Server"\
                            " completed successfully"));
                return ITS_SUCCESS;
            }
            else
            {
                DT_ERR(("The Certificate Verification Failed"));
            }
        }
        else
        {
            DT_DBG(("TlsServerProcedure: IdentityVerification NOT Enabled"));
            ((DiaSocketTransport*)DIA_PE_ACC_SPECS \
             (DIA_PEER_ST_ENTRY(ctxt)).trHandle)->SetTlsSession(serSess);
            DT_DBG(("TLS procedure for Server completed successfully"));
            return ITS_SUCCESS;
        }
    }
    return !ITS_SUCCESS;
}


ITS_INT
TlsServerProcedure(ITS_SocketInfo* info,DiaSocketTransport* trHandle)
{
    int ret;
    Certificate *servCert;
    std::string dnsName;
    TlsFactoryClass * tlsObj = NULL;

    DT_DBG(("Starting the TLS procedure for Server"));

    if (serverCertificate)
    {
        servCert = serverCertificate;
    }
    else
    {
        DT_ERR(("TlsServerProcedure: The ServerCertificate is not"\
                    " initialized."));
        return !ITS_SUCCESS;
    }

    ITSDiaConfig *cfg =  &itsDiaConfig;


    tlsObj = TlsFactoryClass::GetTlsInstance();
    if(tlsObj == NULL)
    {
        DT_ERR(("TlsServerProcedure: TlsFactoryClass is not Initialized"));
        return !ITS_SUCCESS;
    }

    TlsSession  *serSess = tlsObj->CreateSession(SERVER,info->socket);
    if (serSess == NULL)
    {
        DT_ERR(("TlsServerProcedure: Unable to create TLS server session."));
        delete serSess;
        serSess = NULL;
        return !ITS_SUCCESS;
    }
    //Populate the Cipher suite list.
    ITS_INT  list[CIPHER_SUITE_LIST] = {0};

    DiaUtils::PopulateCipherSuiteList(list);

    ret = serSess->CredentialSet(servCert);
    if(ret != ITS_SUCCESS)
    {
        DT_ERR(("TlsServerProcedure: Failed While Setting Credentials"));
        delete serSess;
        serSess = NULL;
        return !ITS_SUCCESS;
    }
    ret = serSess->SetCipherSuite(list);
    if(ret != ITS_SUCCESS)
    {
        DT_ERR(("TlsClientProcedure: Failed to Set Cipher Suites"));
        return !ITS_SUCCESS;
    }

    serSess->CertificateRequest();

    if ((ret = serSess->Handshake(itsDiaConfig.GetPeerTimers().GetWatchdog()-1)) != ITS_SUCCESS)
    {
        DT_ERR(("TLS Handshake at server failed"));
        delete serSess;
        serSess = NULL;
    }
    else
    {
        /**
         * Verifying the certificate received from client with the OriginHost
         * and OriginRealm if the IdentityVerification is enabled in xml
         */
        if (cfg->GetSecurityConfig().IsIdentityVerifyEnabled())
        {
            trHandle->SetTlsSession(serSess);
            DT_DBG(("TLS procedure for Server completed successfully"));
            return ITS_SUCCESS;
            /* 
            DT_DBG(("TlsServerProcedure: IdentityVerification Enabled"));

            DIA_GEN_CMD *ce =
                DIA_PE_CE_CACHE(DIA_PEER_ST_ENTRY(ctxt));
            if (!ce)
            {
                DT_ERR(("TlsServerProcedure: Capabilties Exchange is "\
                            "not proper."));
                return !ITS_SUCCESS;
            }
            DT_DBG(("The Host Name is: %s.",ce->getOriginHost()->value().c_str()));
            DT_DBG(("The Realm Name is: %s.",ce->getOriginRealm()->value().c_str()));
            if (serSess->VerifyCertificate((char *)ce->getOriginHost()->value().c_str(),
                                           (char *)ce->getOriginRealm()->value().c_str())
                                           == ITS_SUCCESS)
            {
                ((DiaSocketTransport*)DIA_PE_ACC_SPECS
                 (DIA_PEER_ST_ENTRY(ctxt)).trHandle)->SetTlsSession(serSess);
                DT_DBG(("TlsServerProcedure: TLS procedure for Server"\
                            " completed successfully"));
                return ITS_SUCCESS;
            }
            else
            {
                DT_ERR(("The Certificate Verification Failed"));
            }
            */
        }
        else
        {
            DT_DBG(("TlsServerProcedure: IdentityVerification NOT Enabled"));
            trHandle->SetTlsSession(serSess);
            DT_DBG(("TLS procedure for Server completed successfully"));
            return ITS_SUCCESS;
        }
    }
    return !ITS_SUCCESS;
}

#endif
