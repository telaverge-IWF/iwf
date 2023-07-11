/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2011 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: app_itu_msgs.cpp,v $
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.16.2.5.2.2.2.8  2015/05/25 05:11:54  jkchaitanya
 * LOG: Cap-Ro test tool enhancement to support automatic user configuration mode for automation purpose, Review 4059
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.16.2.5.2.2.2.7  2015/05/18 07:06:57  kpnithin
 * LOG: MSC for Provide roaming number Send routing info Update location messages IE addition and negative responses
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.16.2.5.2.2.2.6  2015/05/05 06:45:25  jkchaitanya
 * LOG: changes for bug 6371
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.16.2.5.2.2.2.5  2015/04/29 06:35:57  rsanjay
 * LOG:  Map Tool Message implementation Multiple ISD Send Routing info Send Routing Info-SM Provide Roaming Number Update location Messages are implemented newly
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.16.2.5.2.2.2.4  2015/03/13 04:49:53  jkchaitanya
 * LOG: changes for printing readyforsm response printing
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.16.2.5.2.2.2.3  2014/12/16 05:40:13  jkchaitanya
 * LOG: changes merged from TSL branch
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.16.2.5.2.3  2014/12/10 10:48:55  kpnithin
 * LOG: changes for bug 5688
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.16.2.5.2.2  2014/09/22 10:01:11  jkchaitanya
 * LOG: changes for enhancement bug 4994
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.16.2.5.2.1  2014/09/15 06:37:05  jsarvesh
 * LOG: Changes done for Encoding OpCode for ERB returnResultLast
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.16.2.5  2014/08/26 09:27:31  jsarvesh
 * LOG: Changes done for fixing MAP-S6a bugs 4809, 4808, 4797
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.16.2.4  2014/07/24 12:27:45  jkchaitanya
 * LOG: changes for not releasing the invoke id for map-s6a and s6a-map calls
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.16.2.3  2014/07/15 10:51:09  jsarvesh
 * LOG: Setting Return on error option in outgoing TCAP message from IWF
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.16.2.2  2014/07/15 05:07:27  jkchaitanya
 * LOG: changes merged from VOICE branch for UDTS message changes
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.16.2.1  2014/06/27 10:16:42  jkchaitanya
 * LOG: changes for InvokeId release and send UAbort option to user
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.16  2014/06/11 09:11:27  jkchaitanya
 * LOG: changes for giving option to send ERB or ACR in a single dialogue first
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.15  2014/05/08 05:04:18  jkchaitanya
 * LOG: changes for setting opc and dpc which is missed
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.14  2014/05/06 13:11:02  jkchaitanya
 * LOG: changes for ccfh feature
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.13  2014/04/28 11:46:24  jsarvesh
 * LOG: Changes done for IDPSMS handling of TCAP_Error and TCAP_Result scenarios
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.12  2014/04/14 08:45:40  jkchaitanya
 * LOG: changes for parsing json file from current path and support local/remote calls
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.11  2014/04/09 11:12:23  jkchaitanya
 * LOG: changes for msc to support TcapResult and TcapError messages and for bug 3510
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.10  2014/04/08 06:28:51  jkchaitanya
 * LOG: changes to avoid restart of tool for followon cases
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.9  2014/04/04 05:08:16  jkchaitanya
 * LOG: changes to set invokeid internally for InterimTcCont/TcEnd messages
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.8  2014/04/03 15:03:24  jkchaitanya
 * LOG: changes for building Activity Response with same InvokeId as request
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.7  2014/04/03 04:43:37  jkchaitanya
 * LOG: changes for bug 3450
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.6  2014/03/25 10:19:11  jkchaitanya
 * LOG: changes for msc tool to support all the callflows for TSL
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.5  2014/03/14 10:50:06  jsarvesh
 * LOG: chnages for v1 messages
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.4  2014/03/13 10:14:17  jsarvesh
 * LOG: Implementation for Voice CallFlows
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.3  2014/03/11 06:24:12  jsarvesh
 * LOG: Modifed code to send only ACR in TC_End and to handle connect info
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.2  2014/03/09 12:16:57  jsarvesh
 * LOG: Chnage to Encode V2 ERB and ACR in TC_end
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1.4.1  2014/03/07 13:40:46  jsarvesh
 * LOG: Implmentation for Voice CallFlows
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5.2.1  2014/02/13 06:02:08  jkchaitanya
 * LOG: changes for sleep time before sending ERBSMS
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.5  2014/01/23 09:51:20  jkchaitanya
 * LOG: changes for merging iwf code from poc to productization
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.4  2013/12/31 04:44:52  millayaraja
 * LOG: merged code from B-IWF-0100-01 to B-IWF-0100-02 with GTT support
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.3  2013/12/27 13:53:04  jkchaitanya
 * LOG: changes for the bug 2301
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.2  2013/12/24 06:52:45  jkchaitanya
 * LOG: changes for the bug 2660
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27.2.1  2013/12/06 13:20:42  jkchaitanya
 * LOG: changes to handle reject component
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.27  2013/10/03 12:34:37  jkchaitanya
 * LOG: changes for displaying 146 as MSC SSN
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.26  2013/09/27 05:58:36  jkchaitanya
 * LOG: changes in conditions to send cap response if MSC SSN is 146
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.25  2013/09/03 12:55:52  jkchaitanya
 * LOG: changes for the bug 2164 removed unwanted flag in json
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.24  2013/09/02 06:07:00  jkchaitanya
 * LOG: changes for the bug 2145
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.23  2013/08/30 07:10:48  jkchaitanya
 * LOG: changes for AddressIndicator for bug 1165
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.22  2013/08/29 10:52:34  jkchaitanya
 * LOG: changes for bug 2085
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.21  2013/08/29 06:06:59  jsarvesh
 * LOG: Changes done for Conflicts in OpCodes and encoding of PDN_GW_Update
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.20  2013/08/20 08:43:34  jkchaitanya
 * LOG: changes for the bug 2061
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.19  2013/08/13 09:18:33  jkchaitanya
 * LOG: changes for the issue mentioned in the bug 1986(ERB in Tc_Cont and ACR in Tc_End)
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.18  2013/08/12 15:35:14  jkchaitanya
 * LOG: changes to enhance cap tool for bug 1896
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.17  2013/08/12 04:47:27  jkchaitanya
 * LOG: changes to remove warning
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.16  2013/08/12 04:38:17  jkchaitanya
 * LOG: changes for missing code in CVS for bug 2022
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.15  2013/08/06 13:35:57  jkchaitanya
 * LOG: changes are done to move set sleep time changes to default case place if continue comes to simulate ASR case
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.14  2013/08/02 06:51:36  jkchaitanya
 * LOG: changes for tool enhancements
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.13  2013/07/31 08:42:47  jkchaitanya
 * LOG: changes for the bug 1964
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.12  2013/07/30 11:48:47  jkchaitanya
 * LOG: changes to change the Exit option value in switch case
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.11  2013/07/30 05:03:52  jkchaitanya
 * LOG: changes to handle Release for SMS
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.10  2013/07/30 04:46:55  jkchaitanya
 * LOG: changes to ahndle RRB and Continue for SMS
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.9  2013/07/29 12:27:45  jkchaitanya
 * LOG: changes for sms support messages in cap tool and asn
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.8  2013/07/23 09:11:05  jkchaitanya
 * LOG: change in the application context for cap messages
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.7  2013/07/23 05:41:16  jkchaitanya
 * LOG: changes for the tool bug 1896
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.6  2013/07/22 09:45:08  jkchaitanya
 * LOG: changes for the bug 1902 printing SSN values for MSC and SCP
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.5  2013/07/18 08:36:48  jkchaitanya
 * LOG: changes to restrict ERB and ACR in case os Ro-ACR
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.4  2013/07/17 03:49:52  jkchaitanya
 * LOG: changes done for not sending ERB and ACR in TcCont for ASR case is reverted back, which is not required
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.3  2013/07/16 07:06:15  jkchaitanya
 * LOG: changes for review comments and release call decode
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.2  2013/07/12 06:47:08  jkchaitanya
 * LOG: changes in map tool to enhance cap supported changes for some cases like ASR and RAR testing
 * LOG:
 * LOG: Revision 1.1.1.1.2.29.2.1  2013/07/09 11:27:21  jkchaitanya
 * LOG: changes for cap tool enhancement
 * LOG:
 * LOG: Revision 1.1.1.1.2.29  2013/06/14 08:39:33  jsarvesh
 * LOG: Added the PurgeMSArg option for Load
 * LOG:
 * LOG: Revision 1.1.1.1.2.28  2013/06/10 07:09:12  jsarvesh
 * LOG: enhanced for Load Run from MAP-Tool
 * LOG:
 * LOG: Revision 1.1.1.1.2.27  2013/06/03 10:17:05  jsarvesh
 * LOG: Changes done for setting application context for sending UGLRes and not to send ResetArg and Ready_For_SMArg as TCAP_Begin
 * LOG:
 * LOG: Revision 1.1.1.1.2.26  2013/06/03 07:33:51  jkchaitanya
 * LOG: changes for the bugs 1652,1655,1657
 * LOG:
 * LOG: Revision 1.1.1.1.2.25  2013/05/29 07:43:37  jsarvesh
 * LOG: Added Logs For SSN Number And Hardcoding GTT Route To 1 As Not Supported Now
 * LOG:
 * LOG: Revision 1.1.1.1.2.24  2013/05/29 04:28:47  jvikram
 * LOG: changed the log for reset
 * LOG:
 * LOG: Revision 1.1.1.1.2.23  2013/05/28 15:21:55  jsarvesh
 * LOG: Taking Input for OSSN and DSSN
 * LOG:
 * LOG: Revision 1.1.1.1.2.22  2013/05/24 13:31:53  millayaraja
 * LOG: Added Activate and Deactivate Trace Mode mapping
 * LOG:
 * LOG: Revision 1.1.1.1.2.21  2013/05/23 12:28:00  jkchaitanya
 * LOG: changes for the bug fixes for 1579,1581,1587,1588,1591,1592 and IDR-to-InsertSubDataArg changes
 * LOG:
 * LOG: Revision 1.1.1.1.2.20  2013/05/22 15:24:47  jsarvesh
 * LOG: IWF Phase-II Changes
 * LOG:
 * LOG: Revision 1.1.1.1.2.19  2013/05/21 11:17:28  jsarvesh
 * LOG: enhancement for MAP-DIAMETER translator Phase-II
 * LOG:
 * LOG: Revision 1.1.1.1.2.18  2013/05/02 04:33:23  jsarvesh
 * LOG: IWFPhaseII Changes for UGL, SAI and PurgeMS
 * LOG:
 * LOG: Revision 1.1.1.1.2.17  2013/04/05 05:30:00  jsarvesh
 * LOG: changed for simulator crash if no reponse is received from iwf
 * LOG:
 * LOG: Revision 1.1.1.1.2.16  2013/04/02 11:25:09  jsarvesh
 * LOG: added application context for srever initiated messages
 * LOG:
 * LOG: Revision 1.1.1.1.2.15  2013/03/21 04:53:33  jsarvesh
 * LOG: change in sendauthnticationinfo error code
 * LOG:
 * LOG: Revision 1.1.1.1.2.14  2013/03/15 07:39:51  jsarvesh
 * LOG: enhancement for map simulator added Activate tracemode reset arg deactivate trace mode
 * LOG:
 * LOG: Revision 1.1.1.1.2.13  2013/03/08 05:11:23  jsarvesh
 * LOG: implementation for map message through json
 * LOG:
 * LOG: Revision 1.1.1.1.2.12  2013/03/08 04:19:34  jsarvesh
 * LOG: implementation for map message through json
 * LOG:
 * LOG: Revision 1.1.1.1.2.11  2013/03/05 18:42:42  brajappa
 * LOG: BugId: 1165 - setting the network Indicator for CPA
 * LOG:
 * LOG: Revision 1.1.1.1.2.10  2013/02/22 19:59:13  lakshman
 * LOG: add gtt test info.
 * LOG:
 * LOG: Revision 1.1.1.1.2.9  2013/02/15 15:50:26  jvikas
 * LOG: PUR/PurgeMS related code changes.
 * LOG:
 * LOG: Revision 1.1.1.1.2.8  2013/02/15 12:46:28  brajappa
 * LOG: Sending and receiving Cancel Location Arg
 * LOG:
 * LOG: Revision 1.1.1.1.2.7  2013/02/14 09:55:16  brajappa
 * LOG: ISD sending withing UGLA is handled through command line, handling readyForSM
 * LOG:
 * LOG: Revision 1.1.1.1.2.6  2013/01/31 19:31:28  arnabd
 * LOG: Handling of SendAuthenticationInfoArg
 * LOG:
 * LOG: Revision 1.1.1.1.2.5  2013/01/24 15:10:12  lakshman
 * LOG: tart testing delete subscriber data....
 * LOG:
 * LOG: Revision 1.1.1.1.2.4  2013/01/23 21:04:37  lakshman
 * LOG: verified provideSubscriberArg and tcap error scenarios.
 * LOG:
 * LOG: Revision 1.1.1.1.2.3  2013/01/17 23:49:15  lakshman
 * LOG: Update DeleteSubscriberdata and TCAP error handling function with few tests.
 * LOG:
 * LOG: Revision 1.1.1.1.2.2  2013/01/15 21:21:30  lakshman
 * LOG: get Delete subscriber and Insert subscriber conversions in cvs.
 * LOG:
 * LOG: Revision 1.1.1.1.2.1  2013/01/15 16:06:31  arnabd
 * LOG: Proper handling of ULR --- UpdateGprsLocationArg --- UpdateGprsLocationRes --- ULA scenario
 * LOG:
 * LOG: Revision 1.1.1.1  2013/01/09 16:41:37  brajappa
 * LOG: Initial import
 * LOG:
 * LOG: Revision 1.1.2.8  2013/01/05 20:18:40  lakshman
 * LOG: add updatelocarg decode func
 * LOG:
 * LOG: Revision 1.1.2.7  2013/01/05 20:06:02  lakshman
 * LOG: update to manage invoke ids and dump insertSubRes
 * LOG:
 * LOG: Revision 1.1.2.6  2013/01/05 17:39:56  lakshman
 * LOG: increase the probability on tcap-end.
 * LOG:
 * LOG: Revision 1.1.2.5  2013/01/05 15:52:06  lakshman
 * LOG: send both cpts
 * LOG:
 * LOG: Revision 1.1.2.4  2013/01/05 15:26:30  lakshman
 * LOG: checkin updategrps loc res msg
 * LOG:
 * LOG: Revision 1.1.2.3  2013/01/03 21:22:27  lakshman
 * LOG: update address info
 * LOG:
 * LOG: Revision 1.1.2.2  2013/01/03 02:44:43  lakshman
 * LOG: update tcap tests - add gprs and randomize responses.
 * LOG:
 * LOG: Revision 1.1.2.1  2012/12/28 13:45:14  lakshman
 * LOG: checkin first version of MAP test along with CAP.
 * LOG:
 * LOG: Revision 1.3  2011/04/18 15:24:17  nvijikumar
 * LOG: More UT updates
 * LOG:
 * LOG: Revision 1.2  2011/04/15 11:35:46  nvijikumar
 * LOG: UT Updates
 * LOG:
 * LOG: Revision 1.1.1.1  2011/04/13 08:12:31  nvijikumar
 * LOG: Initial Draft for SSG
 * LOG:
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: app_itu_msgs.cpp,v 1.1.1.1.2.29.2.27.2.5.2.1.4.16.2.5.2.2.2.8 2015/05/25 05:11:54 jkchaitanya Exp $"

#undef TTC
#undef PRC
#undef CCITT
#undef ANSI
#define CCITT

#if defined (CCITT)

#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <stdio.h>
#include <engine++.h>
#include <its_route.h>
#include <its_sctp.h>
#include <sys/timeb.h>

#include <map>

#include <app_cmn.h>
#include <app_const.h>
#include <app_msgs.h>
#include <app_trace.h>
#include <app_stats.h>
#include <app_timer.h>
#include "tcap_intern.h"
#include <itu/tcap.h>

#include "app_cap_msgs.cpp"
#if defined (Q)
#include <quantify.h>
#endif

ITS_OCTET AC_NAMEIDP[] = {0x04,0x00,0x00,0x01,0x00,0x32,0x01}; 
//ITS_OCTET AC_NAMEIDP[] = {0x04,0x00,0x00,0x01,0x00,0x14,0x03,0x04};

using namespace std;
using namespace its;

static void SetGlobalTitleAddr(its::SCCP_Address&);

extern TcapStats      stats;
extern TransportState transStateInfo;
extern ITS_INT transportInstance;

extern Octets recvOctet;
void  EncodeMsg(AsnObject* p, Octets** octets);

//int sleep_value; // declare sleep value
//int get_invokeid;

#if defined(USE_ANSI_SCCP)

#undef CCITT
#define ANSI
#include <ansi/sccp.h>
    its::SCCP_CalledPartyAddr_ANSI    cdp_itu;
    its::SCCP_CallingPartyAddr_ANSI   cpa_itu;
#if defined(DUAL_TCAP)
#define ISS7_Stack ISS7_CCITT_Stack
#else
#define ISS7_Stack ISS7_ANSI_Stack
#endif
#undef ANSI
#define CCITT

#elif defined(USE_TTC_SCCP)

#undef CCITT
#define TTC
#include <japan/sccp.h>
    its::SCCP_CalledPartyAddr_TTC     cdp_itu;
    its::SCCP_CallingPartyAddr_TTC    cpa_itu;
#define ISS7_Stack ISS7_TTC_Stack
#undef TTC
#define CCITT

#elif defined(USE_PRC_SCCP)

#undef CCITT
#define PRC
#include <china/sccp.h>
    SCCP_CalledPartyAddr_PRC     cdp_itu;
    SCCP_CallingPartyAddr_PRC    cpa_itu;
#define ISS7_Stack ISS7_PRC_Stack
#undef PRC
#define CCITT

#else
#include <itu/sccp.h>
    its::SCCP_CalledPartyAddr_CCITT   cdp_itu;
    its::SCCP_CallingPartyAddr_CCITT  cpa_itu;
#define ISS7_Stack ISS7_CCITT_Stack
#endif

#define TCAP_L_CANCEL_TYPE   TCPPT_TC_L_CANCEL
#define TCAP_END_TYPE        TCPPT_TC_END
#define TCAP_BEGIN_TYPE      TCPPT_TC_BEGIN
#define TCAP_UNI_TYPE        TCPPT_TC_UNI
#define TCAP_CONTINUE_TYPE   TCPPT_TC_CONTINUE
#define TCAP_P_ABORT_TYPE    TCPPT_TC_P_ABORT
#define TCAP_U_ABORT_TYPE    TCPPT_TC_U_ABORT
#define TCAP_ERROR_TYPE      TCPPT_TC_U_ERROR
#define TCAP_R_REJECT_TYPE   TCPPT_TC_R_REJECT
#define TCAP_U_REJECT_TYPE   TCPPT_TC_U_REJECT
#define TCAP_L_REJECT_TYPE   TCPPT_TC_L_REJECT

#define OCTS_185_LEN 184 // sizeof(itstest::octs185)/sizeof(ITS_OCTET)
ITS_CTXT did = 0;

ITS_UINT dPC=0;
ITS_UINT oPC=0;
ITS_UINT sSN=149;
ITS_UINT oSN=6;
//ITS_UINT sSN=6;
//ITS_UINT oSN=149;

string gRecvImsi;
static bool gInitGlobals = false;
static ITUTcapMsgs * ituTcapMsgs = NULL;
int GetReqChoice();
ITS_ULONG GetMapOpCodeForChoice(ITS_INT choice);
int invkId = 0;
int ATInvkId = 0;
ITS_BOOLEAN  LastCptRcvd = ITS_FALSE;
bool IsReleaseIfdurationExceededisSet = false;
int NumOfERBandACHinTc_Cont = 0;
bool sendERBandACRinTcEnd = false;
int TcapAbortReason = 0;
int ISD_counter =1;
int isd_invk_id = 20;
//bool isTransparentFirstFlowExecuted = false;
extern void BuildImsiList();
void
ITUTcapMsgs::InitExternals()
{
    if (!gInitGlobals)
    {
        BuildImsiList();
        gInitGlobals = true;
    }
}

ITUTcapMsgs *
ITUTcapMsgs::GetItuInstance()
{
    if(ituTcapMsgs == NULL)
    {
        ituTcapMsgs = new ITUTcapMsgs;
    }
    return ituTcapMsgs;
}

    int 
ITUTcapMsgs::HandleMessage(engine::Worker *work, its::ITS_Event& evt)
{
    TCAP_Dialogue*  its_dlg = NULL; /* Receive dialogue*/
    TCAP_Component* its_cpt = NULL; /* Receive component*/

    ITS_USHORT   cpt_type_recvd = 0x00;
    ITS_USHORT   dlg_type_recvd = 0x00;

    Json::Value l_jsonRoot = parseMapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["map_v13"];

    switch (TCAP_MSG_TYPE(&evt.GetEvent()))
    {
        case ITS_TCAP_CPT:
            its_dlg = reinterpret_cast<TCAP_Dialogue *>(work->GetUserData());

            TCAP_Component::Receive(ISS7_Stack, evt, its_dlg, &its_cpt);

            APP_TRACE_DEBUG(("Received: Component Type %02x",
                        its_cpt->GetComponentType()));

            cpt_type_recvd = its_cpt->GetComponentType();
            APP_TRACE_DEBUG(("Received: InvokeId %02x, InvokeType %02x",
                        its_cpt->GetInvokeID(), cpt_type_recvd));
            ATInvkId = its_cpt->GetInvokeID();
            stats.UpdateRecvStats(its_cpt->GetComponentType());

            PrintComponentType(cpt_type_recvd);

            if(cpt_type_recvd == TCAP_L_CANCEL_TYPE)
            {
            }
            else
            {
                /*
                 * replys to multiple components is a problem here
                 * somehow we need to track received cpt types, operation
                 * and invoke ids
                 */
                if(its_cpt->GetLast()) /*Last component received*/
                {
                    LastCptRcvd = ITS_TRUE; /*we got all cpts*/
                }
            }

            APP_TRACE_DEBUG(("Last CPT received? = %d", LastCptRcvd));

            if(cpt_type_recvd != TCAP_L_CANCEL_TYPE ||
                    LastCptRcvd )
            {
                if((sSN == 149 && oSN == 6) || (sSN == 6 && oSN == 149))
                {
                    SendMAPResponse(its_dlg, &its_cpt, work);
                }
                else if((sSN == 146 && oSN == 149) || (sSN == 146 && oSN == 146))
                {
                    SendCAPResponse(its_dlg, &its_cpt, work);
                }
            }

            if(its_cpt)
            {
                delete its_cpt;
                its_cpt = NULL;
            }
            //NOTE: Delteting the dialogue after processing of the last component received in a single dialogue.
            if(its_dlg && cpt_type_recvd != TCAP_L_CANCEL_TYPE && cpt_type_recvd != TCAP_L_REJECT_TYPE && LastCptRcvd)
            {
                delete its_dlg;
                its_dlg = NULL;
                LastCptRcvd = ITS_FALSE;
            }
            break;

        case ITS_TCAP_DLG:
            {
                ITS_OCTET flags = 0x00;
                ITS_OCTET slsKey = 0x00;
                ITS_OCTET priority = 0x00;
                ITS_OCTET acName[100];
                ITS_OCTET networkInd = 0x00;
                int acNameLen = 0;
                ITS_OCTET userInfo[100];
                int userInfoLen = 0;
                LastCptRcvd = ITS_FALSE;
                TCAP_Dialogue::Receive(ISS7_Stack, evt, &its_dlg);

                APP_TRACE_DEBUG(("Received: Dialogue Type %02x: Dialogue ID %02x",
                            its_dlg->GetDialogueType(),
                            its_dlg->GetDialogueID()));

                dlg_type_recvd = its_dlg->GetDialogueType();
                PrintDialogueType(dlg_type_recvd);

                stats.UpdateRecvStats(dlg_type_recvd);

                APP_TRACE_DEBUG(("Received: dialogueID = %02x, DialogueType = %02x",
                            its_dlg->GetDialogueID(), dlg_type_recvd));

                its_dlg->GetQualityOfService(flags, slsKey, priority, networkInd);

                if (flags)
                {
                    APP_TRACE_DEBUG((" =====> Prot Version: %02x \n", flags));
                }
                its_dlg->GetApplicationContext(acName, acNameLen);

                if (acNameLen)
                {
                    int i;

                    APP_TRACE_DEBUG((" =====> AC NAME : \n"));

                    for (i = 0; i < acNameLen; i++)
                    {
                        printf("%02x ", acName[i]);
                    }

                    printf("\n");
                }

                its_dlg->GetUserInfo(userInfo, userInfoLen);

                if (userInfoLen)
                {
                    int i;

                    APP_TRACE_DEBUG((" =====> USER INFO : \n"));

                    for (i = 0; i < userInfoLen; i++)
                    {
                        printf("%02x ", userInfo[i]);
                        if (i%15 == 0)
                            printf("\n");
                    }

                    printf("\n");
                }
                if (its_dlg->IsComponentPresent())
                {
                    APP_TRACE_DEBUG(("**** TEST: DLG has COMPONENT ****\n"));
                    work->SetUserData(its_dlg);
                }
                else
                {
                    APP_TRACE_DEBUG(("**** TEST: DLG has NO COMPONENT ****\n"));

                    its_cpt = NULL;

                    if((sSN == 149 && oSN == 6) || (sSN == 6 && oSN == 149))
                    {
                        SendMAPResponse(its_dlg, &its_cpt, work);
                    }
                    else if((sSN == 146 && oSN == 149) || (sSN == 146 && oSN == 146))
                    {
                        SendCAPResponse(its_dlg, &its_cpt, work);
                    }

                    delete its_dlg;
                    its_dlg = NULL;
                }

                break;
            }
        default:
            APP_TRACE_ERROR(("Received neither Dlg not CPT."));
            break;
    }

    return ITS_SUCCESS;
}

static void SetReceivedImsi(const map_v13::IMSI &usrid)
{
    const std::vector<byte> &array = usrid.GetArray();
    char *fromdg = 0;

    TCAPUtils::ConvertOctsToString(&fromdg, (ITS_OCTET *)&array[0], (int)array.size(), true);
    gRecvImsi = fromdg;
    free(fromdg);
    fromdg = 0;
}

int ITUTcapMsgs::SendMAPResponse(TCAP_Dialogue* dlg, 
                               TCAP_Component** cpt,
                               engine::Worker* work)
{
   int ret = 0;
   
   ITS_USHORT dlg_type = 0x00;
   ITS_USHORT cpt_type = 0x00;
   ITS_USHORT dlg_id;
   ITS_USHORT ivk_id;

   if(dlg != NULL)
   {
      dlg_type = dlg->GetDialogueType();
      dlg_id   = dlg->GetDialogueID();
   }

   if(*cpt != NULL)
   {
      cpt_type = (*cpt)->GetComponentType();
      ivk_id   = (*cpt)->GetInvokeID();
   }

   APP_TRACE_DEBUG(("Inside SendMAPResponse() function."));

   ITS_LONG op ;

   try
   {
       switch ((*cpt)->GetComponentType())
       {
           case TCPPT_TC_INVOKE:
           {
               TCAP_Invoke *ivk = dynamic_cast<TCAP_Invoke *>(*cpt);
               ivk->GetOperation(op);

               if (op == map_common::OP_updateGprsLocation)
               {
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   map_v13::UpdateGprsLocationArg uglarg;
                   Octets octs(param);
                   uglarg.Decode(octs);
                   uglarg.Print(cout);

                   const map_v13::IMSI &usrid = uglarg.GetImsi();
                   SetReceivedImsi(usrid);
               }
               else if (op == map_common::OP_updateLocation)
               {
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   map_v13::UpdateLocationArg ularg;
                   Octets octs(param);
                   ularg.Decode(octs);
                   ularg.Print(cout);
               }	 
               else if (op == map_common::OP_sendRoutingInfo)
               {
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   map_v9::SendRoutingInfoArg sriarg;
                   Octets octs(param);
                   sriarg.Decode(octs);
                   sriarg.Print(cout);
               }
                else if (op == map_common::OP_provideRoamingNumber)
               {
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   map_v9::ProvideRoamingNumberRes prrnres;
                   Octets octs(param);
                   prrnres.Decode(octs);
                   prrnres.Print(cout);
               }
               else if (op == map_common::OP_sendRoutingInfoForSM)
               {
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   map_v9::RoutingInfoForSM_Res srifsmr;
                   Octets octs(param);
                   srifsmr.Decode(octs);
                   srifsmr.Print(cout);
               }	
               else if (op == map_common::OP_sendAuthenticationInfo)
               {
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   map_v13::SendAuthenticationInfoArg saiarg;
                   Octets octs(param);
                   saiarg.Decode(octs);
                   saiarg.Print(cout);
               }
               else if (op == map_common::OP_purgeMS)
               {
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   map_v13::PurgeMS_Arg pumsarg;
                   Octets octs(param);
                   pumsarg.Decode(octs);
                   pumsarg.Print(cout);
               }

               else if (op == map_common::OP_readyForSM)
               {
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   map_v13::ReadyForSM_Arg rfsa;
                   Octets octs(param);
                   rfsa.Decode(octs);
                   rfsa.Print(cout);
               }
               else if (op == map_common::OP_insertSubscriberData)
               {
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   map_v13::InsertSubscriberDataArg isda;
                   Octets octs(param);
                   isda.Decode(octs);
                   isda.Print(cout);
               }
               
               else if (op == map_common::OP_deleteSubscriberData)
               {    
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   map_v13::DeleteSubscriberDataArg dsda;
                   Octets octs(param);
                   dsda.Decode(octs);
                   dsda.Print(cout);
               }
               else if (op == map_common::OP_cancelLocation)
               {
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   map_v13::CancelLocationArg cla;
                   Octets octs(param);
                   cla.Decode(octs);
                   cla.Print(cout);
               }
               else if (op == map_common::OP_provideSubscriberInfo)
               {    
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   map_v13::ProvideSubscriberInfoArg psia;
                   Octets octs(param);
                   psia.Decode(octs);
                   psia.Print(cout);
               }    
               else if (op == map_common::OP_reset)
               {
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   map_v13::ResetArg rsa;
                   Octets octs(param);
                   rsa.Decode(octs);
                   rsa.Print(cout);
               }
               else if (op == map_common::OP_activateTraceMode)
               {
                   std::vector<byte> param;
                   ivk->GetParameter(param);
                   map_v13::ActivateTraceModeArg atma;
                   Octets octs(param);
                   atma.Decode(octs);
                   atma.Print(cout);
               }
           }
           break;

           case TCPPT_TC_RESULT_L:
           case TCPPT_TC_RESULT_NL:
           {
               TCAP_Result *resl = dynamic_cast<TCAP_Result *>(*cpt);
               resl->GetOperation(op); 

               (*cpt)->Print(cout);
               if (op == map_common::OP_insertSubscriberData)
               {
                   std::vector<byte> param;
                   resl->GetParameter(param);
                   map_v13::InsertSubscriberDataRes isres;
                   Octets octs(param);
                   isres.Decode(octs);
                   isres.Print(cout);
               }
               else if (op == map_common::OP_deleteSubscriberData)
               {
                   std::vector<byte> param;
                   resl->GetParameter(param);
                   map_v13::DeleteSubscriberDataRes dsres;
                   Octets octs(param);
                   dsres.Decode(octs);
                   dsres.Print(cout);
               }
               else if (op == map_common::OP_cancelLocation)
               {
                   std::vector<byte> param;
                   resl->GetParameter(param);
                   map_v13::CancelLocationRes clRes;
                   Octets octs(param);
                   clRes.Decode(octs);
                   clRes.Print(cout);
               }
               else if (op == map_common::OP_updateGprsLocation)
               {
                   std::vector<byte> param;
                   resl->GetParameter(param);
                   map_v13::UpdateGprsLocationRes uglres;
                   Octets octs(param);
                   uglres.Decode(octs);
                   uglres.Print(cout);
               }
               else if (op == map_common::OP_updateLocation)
               {
                   std::vector<byte> param;
                   resl->GetParameter(param);
                   map_v13::UpdateLocationArg ularg;
                   Octets octs(param);
                   ularg.Decode(octs);
                   ularg.Print(cout);
               }	 
               else if (op == map_common::OP_sendRoutingInfo)
               {
                   std::vector<byte> param;
                   resl->GetParameter(param);
                   map_v9::SendRoutingInfoRes srires;
                   Octets octs(param);
                   srires.Decode(octs);
                   srires.Print(cout);
               }
               else if (op == map_common::OP_sendRoutingInfoForSM)
               {
                   std::vector<byte> param;
                   resl->GetParameter(param);
                   map_v9::RoutingInfoForSM_Res srifsmr;
                   Octets octs(param);
                   srifsmr.Decode(octs);
                   srifsmr.Print(cout);
               }
               else if (op == map_common::OP_provideRoamingNumber)
               {
                   std::vector<byte> param;
                   resl->GetParameter(param);
                   map_v9::ProvideRoamingNumberRes prrnres;
                   Octets octs(param);
                   prrnres.Decode(octs);
                   prrnres.Print(cout);
               }
               else if (op == map_common::OP_sendAuthenticationInfo)
               {
                   std::vector<byte> param;
                   resl->GetParameter(param);
                   map_v13::SendAuthenticationInfoRes saires;
                   Octets octs(param);
                   saires.Decode(octs);
                   saires.Print(cout);
               }
               else if (op == map_common::OP_purgeMS)
               {
                   std::vector<byte> param;
                   resl->GetParameter(param);
                   map_v13::PurgeMS_Res pmsres;
                   Octets octs(param);
                   pmsres.Decode(octs);
                   pmsres.Print(cout);
               } 
               else if (op == map_common::OP_provideSubscriberInfo)
               {
                   std::vector<byte> param;
                   resl->GetParameter(param);
                   map_v13::ProvideSubscriberInfoRes psires;
                   Octets octs(param);
                   psires.Decode(octs);
                   psires.Print(cout);
               }
               else if (op == map_common::OP_deactivateTraceMode)
               {
                   std::vector<byte> param;
                   resl->GetParameter(param);
                   map_v13::DeactivateTraceModeRes dtmr;
                   Octets octs(param);
                   dtmr.Decode(octs);
                   dtmr.Print(cout);
               }
               else if (op == map_common::OP_readyForSM)
               {    
                   std::vector<byte> param;
                   resl->GetParameter(param);
                   map_v13::ReadyForSM_Res rfss;
                   Octets octs(param);
                   rfss.Decode(octs);
                   rfss.Print(cout);
               }    
           }
           break;

           default:
           break;
       }
   }
   catch (AsnDecodeError &exc)
   {
       cout << exc.GetDescription() << endl;
   }
   SendResponses(dlg, *cpt);

   return ret;
}

int ITUTcapMsgs::SendCAPResponse(TCAP_Dialogue* dlg, 
                               TCAP_Component** cpt,
                               engine::Worker* work)
{
   int ret = 0;
   
   ITS_USHORT dlg_type = 0x00;
   ITS_USHORT cpt_type = 0x00;
   ITS_USHORT dlg_id;
   ITS_USHORT ivk_id;

   if(dlg != NULL)
   {
      dlg_type = dlg->GetDialogueType();
      dlg_id   = dlg->GetDialogueID();
      IDP_DIALOGUE_ID = dlg_id;
   }

   if(*cpt != NULL)
   {
      cpt_type = (*cpt)->GetComponentType();
      ivk_id   = (*cpt)->GetInvokeID();
   }
   else
   {
       APP_TRACE_ERROR(("Received Dlg without CPT."));
       return !ITS_SUCCESS;
   }
   APP_TRACE_DEBUG(("Inside SendCAPResponse() function."));

   ITS_LONG op ;

   try
   {
       switch ((*cpt)->GetComponentType())
       {
           case TCPPT_TC_INVOKE:
               {
                   TCAP_Invoke *ivk = dynamic_cast<TCAP_Invoke *>(*cpt);
                   ivk->GetOperation(op);

                   if (op == cap::OP_requestReportBCSMEvent)
                   {
                       std::vector<byte> param;
                       ivk->GetParameter(param);
                       cap_v3::RequestReportBCSMEventArg rrb;
                       if(IDPVersionBuilt == IDP_V2)
                       {
                           cap_v2::RequestReportBCSMEventArg rrb;
                       }
                       else if(IDPVersionBuilt == IDP_V1)
                       {
                           cap_v1::RequestReportBCSMEventArg rrb;
                       }
                       Octets octs(param);
                       rrb.Decode(octs);
                       rrb.Print(cout);
                   }
                   else if (op == cap::OP_applyCharging)
                   {
                       std::vector<byte> param;
                       ivk->GetParameter(param);
                       if(IDPVersionBuilt == IDP_V2)
                       {
                           cap_v2::ApplyChargingArg ach;
                           Octets octs(param);
                           ach.Decode(octs);
                           ach.Print(cout);
                           cap_v2::AChBillingChargingCharacteristics acc = ach.GetAChBillingChargingCharacteristics();
                           const std::vector<byte>& vec = acc.GetArray();
                           Octets camelach(vec,vec.size());
                           cap_v2::CAMEL_AChBillingChargingCharacteristics camelACH;
                           camelACH.Decode(camelach);
                           camelACH.Print(cout);

                       }
                       else if(IDPVersionBuilt == IDP_V3)
                       {
                           cap_v3::ApplyChargingArg ach;
                           Octets octs(param);
                           ach.Decode(octs);
                           ach.Print(cout);
                           cap_v3::AChBillingChargingCharacteristics acc = ach.GetAChBillingChargingCharacteristics();
                           const std::vector<byte>& vec = acc.GetArray();
                           Octets camelach(vec,vec.size());
                           cap_v3::CAMEL_AChBillingChargingCharacteristics camelACH;
                           camelACH.Decode(camelach);
                           camelACH.Print(cout);

                           if(camelACH.ChoiceTimeDurationCharging())
                           {
                               cap_v3::CAMEL_AChBillingChargingCharacteristics::TimeDurationCharging tdc = camelACH.GetChoiceTimeDurationCharging();
                               if(tdc.GetReleaseIfdurationExceeded().GetValue() == true)
                               {
                                   IsReleaseIfdurationExceededisSet = true; 
                               }
                           }
                       }
                   }
                   else if (op == cap::OP_continue)
                   {
                       APP_TRACE_DEBUG(("Continue Received"));
                       //NOTE: Nothing to do as this is just an indication from IWF to continue
                   }
                   else if (op == cap::OP_connect)
                   {
                       std::vector<byte> param;
                       ivk->GetParameter(param);
                       if(IDPVersionBuilt == IDP_V2)
                       {
                           cap_v2::ConnectArg connArg;
                           Octets octs(param);
                           connArg.Decode(octs);
                           connArg.Print(cout);
                       }
                       else if(IDPVersionBuilt == IDP_V1)
                       {
                           cap_v1::ConnectArg connArg;
                           Octets octs(param);
                           connArg.Decode(octs);
                           connArg.Print(cout);
                       }
                   }
                   else if (op == cap::OP_releaseCall)
                   {
                       //NOTE: Nothing to do as this is just a release call
                       std::vector<byte> param;
                       ivk->GetParameter(param);
                       Octets octs(param);
                       cap_v3::Cause cau;
                       cau.Decode(octs);
                       cau.Print(cout);
                   }
                   else if (op == cap::OP_requestReportSMSEvent)
                   {
                       std::vector<byte> param;
                       ivk->GetParameter(param);
                       cap_v3::RequestReportSMSEventArg rrsms;
                       Octets octs(param);
                       rrsms.Decode(octs);
                       rrsms.Print(cout);
                   }
                   else if (op == cap::OP_continueSMS)
                   {
                       //NOTE: Nothing to do as this is just an indication from IWF to continue
                   }
                   else if (op == cap::OP_releaseSMS)
                   {
                       std::vector<byte> param;
                       ivk->GetParameter(param);
                       cap_v3::ReleaseSMSArg rsmsa;
                       Octets octs(param);
                       rsmsa.Decode(octs);
                       rsmsa.Print(cout);
                   }
                   else if (op == cap::OP_activityTest)
                   {
                       APP_TRACE_DEBUG(("ActivityTest Message Received"));
                   }
               }
               break;

           case TCPPT_TC_RESULT_L:
           case TCPPT_TC_RESULT_NL:
               {
                   TCAP_Result *resl = dynamic_cast<TCAP_Result *>(*cpt);
                   resl->GetOperation(op); 

                   (*cpt)->Print(cout);
               }
               break;

           case TCPPT_TC_L_REJECT:
               {
                   TCAP_Reject *rejc = dynamic_cast<TCAP_Reject *>(*cpt);
                   ITS_OCTET family, code;
                   rejc->GetProblem(family, code);
                   cout  << "Problem Type: " << (int)family << endl;
                   cout  << "Problem Code: " << (int)code << endl;
                   APP_TRACE_DEBUG(("Reject Component Received"));
                   (*cpt)->Print(cout);
                   //NOTE: Reject Component is received, MSC neednot send any response so just return the function.
                   return ret;
               }
               break;

           default:
               break;
       }
   }
   catch (AsnDecodeError &exc)
   {
       cout << exc.GetDescription() << endl;
   }
   SendResponses(dlg, *cpt);

   return ret;
}

void
ITUTcapMsgs::InteractiveSendPreArrangedEnd(ITS_HANDLE hdl)
{
   int ret = 0;
   ITS_USHORT dlgid;

   TCAP_End end;
   cout << endl <<"Enter Dialog ID:";
   cin >> dlgid;

   end.SetDialogueID(dlgid);

   end.SetPreArrangedEnd(true);

   ret = TCAP_Dialogue::Send(ISS7_Stack, &end);

   if(ret == ITS_SUCCESS)
   {
       stats.UpdateSendStats(end.GetDialogueType(), true);
       APP_TRACE_DEBUG(("Send prearranged end success:\n"));
   }

  return;
}

void ITUTcapMsgs::PrintComponentType(ITS_USHORT compType)
{
   switch (compType)
   {
      case TCPPT_TC_INVOKE:
            APP_TRACE_DEBUG(("**** TEST: Received INVOKE CPT **** \n"));
            break;
      case TCPPT_TC_RESULT_L:
            APP_TRACE_DEBUG(("**** TEST: Received RESULT LAST CPT **** \n"));
            break;
      case TCPPT_TC_RESULT_NL:
            APP_TRACE_DEBUG(("**** TEST: Received RESULT_NL CPT **** \n"));
            break;
      case TCAP_L_CANCEL_TYPE:
            APP_TRACE_DEBUG(("**** TEST: Received LOCAL CANCEL CPT **** \n"));
            break;
      case TCAP_ERROR_TYPE:
            APP_TRACE_DEBUG(("**** TEST: Received ERROR CPT **** \n"));
            break;
      case TCAP_R_REJECT_TYPE:
            APP_TRACE_DEBUG(("**** TEST: Received R_REJECT CPT **** \n"));
            break;
      case TCAP_U_REJECT_TYPE:
            APP_TRACE_DEBUG(("**** TEST: Received U_REJECT CPT **** \n"));
            break;
      case TCAP_L_REJECT_TYPE:
            APP_TRACE_DEBUG(("**** TEST: Received L_REJECT CPT **** \n"));
            break;
       default:
            break;

   }

}

void ITUTcapMsgs::PrintDialogueType(ITS_USHORT compType)
{
   switch (compType)
   {
       case TCAP_END_TYPE:
            APP_TRACE_DEBUG(("**** TEST: Received END DLG ****\n"));
            break;
       case TCAP_BEGIN_TYPE:
            APP_TRACE_DEBUG(("**** TEST: Received BEGIN DLG ****\n"));
            break;
       case TCAP_UNI_TYPE:
            APP_TRACE_DEBUG(("**** TEST: Received UNI DLG ****\n"));
            break;
       case TCAP_CONTINUE_TYPE:
            APP_TRACE_DEBUG(("**** TEST: Received CONTINUE DLG ****\n"));
            break;
       case TCAP_P_ABORT_TYPE:
            APP_TRACE_DEBUG(("**** TEST: Received P_ABORT DLG ****\n"));
            break;
       case TCAP_U_ABORT_TYPE:
            APP_TRACE_DEBUG(("**** TEST: Received U_ABORT DLG ****\n"));
            break;
       default:
            break;
   }
}
static void
SetGlobalTitleAddr(its::SCCP_Address& address)
{
   ITS_OCTET  octs[15];
   ITS_OCTET  gtt_arr[15];

   ITS_BOOLEAN eFlag = ITS_FALSE;

   int gtt_len = 0;
   int gtt_type = 0;
   int gtt_tt = 0;
   int gtt_np = 0;
   int gtt_nai = 0;
   int gtttype = 0;
   bool isNull;
   Json::Value l_jsonRootcap = parseMapConfig();
   Json::Value* m_jsonRoot1 = &l_jsonRootcap;
   Json::Value* cfg = &(*m_jsonRoot1)["GTT_configuration"];
   isNull = (*cfg)["GTT_Type"].isNull();
   if(!isNull)
   {
       gtttype = (*cfg)["GTT_Type"].asInt();
       if(gtttype == 4)
           gtt_type = SCCP_CPA_GTTI_ALL;
       else if(gtttype == 3)
           gtt_type = SCCP_CPA_GTTI_TNE;
       else if(gtttype == 2)
           gtt_type = SCCP_CPA_GTTI_TRANS;
       else if(gtttype == 1)
           gtt_type = SCCP_CPA_GTTI_NATURE;
   }

   isNull = (*cfg)["GTT_TT"].isNull();
   if(!isNull)
   {
       gtt_tt = (*cfg)["GTT_TT"].asInt();
   }

   isNull = (*cfg)["GTT_NP"].isNull();
   if(!isNull)
   {
       gtt_np = (*cfg)["GTT_NP"].asInt();
   }

   isNull = (*cfg)["GTT_NAI"].isNull();
   if(!isNull)
   {
       gtt_nai = (*cfg)["GTT_NAI"].asInt();     
   }
   memset(octs, 0, 15);

   if(address.GetID() == SCCP_PRM_CALLED_PARTY_ADDR)
   {
       isNull = (*cfg)["CalledPartyAddrDigits"].isNull();
       if(!isNull)
       {
           std::string gtdigits = (*cfg)["CalledPartyAddrDigits"].asString();
           const char * addrdigit = gtdigits.c_str();
           itstest::dE164 = const_cast<char *>(addrdigit); /*Temp for GTT Test - Arnab */
           printf("*****DESTGTT VALUE IS:%s\n",itstest::dE164);

           TCAPUtils::ConvertStringToOctets(octs, itstest::dE164, gtt_len, eFlag);
       }
   }
   else if(address.GetID() == SCCP_PRM_CALLING_PARTY_ADDR)
   {
       isNull = (*cfg)["CallingPartyAddrDigits"].isNull();
       if(!isNull)
       {
           std::string gtdigits = (*cfg)["CallingPartyAddrDigits"].asString();
           const char * addrdigit = gtdigits.c_str();
           itstest::oE164 = const_cast<char *>(addrdigit); /*Temp for GTT Test - Arnab */
           printf("*****ORIGGTT VALUE IS:%s\n",itstest::oE164);

           TCAPUtils::ConvertStringToOctets(octs, itstest::oE164, gtt_len, eFlag);
       }
   }
   else
   {
       APP_TRACE_ERROR(("SetGlobalTitleAddr: Invalid Address "));
   }
    int start = 0;
   if(gtt_type == SCCP_CPA_GTTI_NATURE)
   {
       start = 1;
       gtt_arr[0] = gtt_nai;
       if(!eFlag)
       {
           gtt_arr[0] |= 0x80;
       }
   }
   else if(gtt_type == SCCP_CPA_GTTI_TRANS)
   {
       start = 1;
       gtt_arr[0] = gtt_tt;
   }
   else if(gtt_type == SCCP_CPA_GTTI_TNE)
   {
       start = 2;
       gtt_arr[0] = gtt_tt;
       gtt_arr[1] = gtt_np;
   }
   else if(gtt_type == SCCP_CPA_GTTI_ALL)
   {
       start = 3;
       gtt_arr[0] = gtt_tt;
       gtt_arr[1] = gtt_np;
       gtt_arr[2] = gtt_nai;
   }

   memcpy(&gtt_arr[start], &octs[0], gtt_len);

   /*gtt type, bytes, length */
   address.SetGlobalTitle(gtt_type, gtt_arr, gtt_len + start);
}

void 
ITUTcapMsgs::SetSCCPAddress()
{
    bool networkInd = false;
    char buf[256];
    switch(itstest::appMode)
    {
        case UNIT_TEST:
            {
                printf("=====$ ITUITcapMsgs::SetSCCPAddress $====\n");

                int include_pc_in_sccp_addr=0;
                int routtype_fromuser=0;

                cout <<endl <<"=== >Enter OPC: ";
                cin >> oPC;

                cout <<endl <<"=== >Enter DPC: ";
                cin >> dPC;

                cout << endl << "=== > IF you want to include PC in SCCP Address, enter \"1\", else enter \"0\": ";
                cin >> include_pc_in_sccp_addr;

                if (include_pc_in_sccp_addr)
                {
                    cpa_itu.SetPointCode(oPC);
                    cdp_itu.SetPointCode(dPC);
                }

                cout <<endl <<"=== >SSN for HLR = \"6\"    SSN for SGSN = \"149\"";
                cout <<endl <<"=== >SSN for MSC = \"146\"    SSN for SCP = \"146\"";
                cout <<endl <<"=== >Enter Destination SSN: ";
                cin >> sSN;
                cdp_itu.SetSSN(sSN);
                cout <<endl <<"=== >SSN for HLR = \"6\"    SSN for SGSN = \"149\"";
                cout <<endl <<"=== >SSN for MSC = \"146\"    SSN for SCP = \"146\"";
                cout <<endl <<"=== >Enter Source SSN: ";
                cin >> oSN;
                cpa_itu.SetSSN(oSN);

                if(itstest::apc == 0)
                {
                    /* User did not set the adjacent pc so assume 
                     * our adjacent is destination pc 
                     */
                    //itstest::apc = itstest::dpc;
                }

                cout << endl << "=== > IF you want GTT enter \"0\", else enter \"1\": ";
                cin >> routtype_fromuser;
                if (!routtype_fromuser)
                {
                    itstest::routeType=0; /*Temp for GTT Test - Ahil */
                }
                else
                {
                    itstest::routeType=1;
                }

                //cout << endl << "ROUTETYPE = " << itstest::routeType << endl;

                //itstest::routeType=1;
                cdp_itu.SetRouteByPCSSN(itstest::routeType);

                cout <<endl <<"=== >SetInternationalRouting 0/1: ";
                cin >> networkInd;
            }
            break;
        case UNIT_AUTO:
            {
                UserAutoData userdata;
                ParseAndSetSCCPAddress(&userdata);
                if (userdata.opc)
                {
                    cpa_itu.SetPointCode(userdata.opc);
                    cdp_itu.SetPointCode(userdata.dpc);
                }
                cdp_itu.SetSSN(userdata.destinationSSN);
                cpa_itu.SetSSN(userdata.sourceSSN);

                if (!userdata.gtt)
                {
                    itstest::routeType=0; /*Temp for GTT Test - Ahil */
                }
                else
                {
                    itstest::routeType=1;
                }
                cdp_itu.SetRouteByPCSSN(itstest::routeType);

                networkInd = userdata.setInternationalRouting;
            }
            break;
        default:
            {
                printf("Invalid Test Mode\n");
            }
    }
    cdp_itu.SetInternationalRouting(networkInd);
    cpa_itu.SetInternationalRouting(networkInd);

    if(!itstest::routeType)
    {
        SetGlobalTitleAddr(cdp_itu);
    }

    //APP_TRACE_DEBUG(("OPC = %d DPC = %d ", itstest::opc, itstest::dpc));

    APP_TRACE_DEBUG((buf, "OE164 = %s DE164 = %s ", itstest::oE164, itstest::dE164));

    cpa_itu.SetRouteByPCSSN(itstest::routeType);

    cpa_itu.SetInternationalRouting(networkInd);

    if(!itstest::routeType)
    {
        SetGlobalTitleAddr(cpa_itu);
    }
}

void
ITUTcapMsgs::InteractiveSendAbort(ITS_HANDLE hdl)
{
    ITS_INT ret;
    TCAP_Dialogue* dlg;
    //TCAP_Component* cpt;
    TCAP_Abort     abortDlg;
    ITS_USHORT localDid;
    //ITS_OCTET abrtInfo[3] = {0xd8,0x01,0x01};
    ITS_UINT abrtReason;

    cout << "\n======> Enter did : <======\n";
    cin >> localDid;

    abortDlg.SetDialogueID(localDid);


    abortDlg.SetApplicationContext(itstest::AC_NAME, 7);
    cout << "\n======> Enter Abort Reason (Cause) : <======\n";
    cin >> abrtReason;
    abortDlg.SetAbortReason(abrtReason);

    dlg = &abortDlg;

    cout << "**** Sending on DID " << localDid << endl;

    ret = TCAP_Dialogue::Send(ISS7_Stack, dlg);

    if(ret != ITS_SUCCESS)
    {
         cout << "====>TCAP_TEST: Failed to send Dialogue< =====" << endl;
    }
    else
    {
         cout << "==>TCAP_TEST: Dialogue send succes PTYPE ="
              << dlg->GetDialogueType() << endl;
    }

}


AsnObject* BuildProtocolMsg(int opcode)
{
    if (opcode >= MAP_V13_UPDATE_GPRS_LOC) {
        // Set Application Context for MAP
        return BuildMapMsg((MAP_OPCODE)opcode);
    }
    return BuildCapMsg(opcode);
}

void
ITUTcapMsgs::InteractiveSendUniDlg(ITS_HANDLE hdl)
{
    ITS_INT ret;
    TCAP_Dialogue* dlg;
    TCAP_Component* cpt;
    TCAP_Unidirectional uniDlg;
    int hasAC = 0;
    int hasProtVer = 0;
    int hasUserInfo = 0;
    bool hasInvoke = false;
    int  invokeCount =  1;
    hasInvoke = true;
    TCAP_AllocateDialogueId(ISS7_Stack, &did);

    printf("\n ******** Allocated DID %d *******\n", did);
    uniDlg.SetDialogueID(did);
    uniDlg.SetOrigAddr(cpa_itu);
    //uniDlg.SetOPC(itstest::opc);
    uniDlg.SetOPC(oPC);
    uniDlg.SetDestAddr(cdp_itu);
    //uniDlg.SetDPC(itstest::apc);
    uniDlg.SetDPC(dPC);

    cout << "=====> Enter 1 for Prot Version <=====\n";
    cin >> hasProtVer;

    if (hasProtVer)
    {
         uniDlg.SetQualityOfService(QOSI_PROT_VER|QOSI_RET_OPT, 0, 0);
    }

    cout << "=====> Enter 1 for AC Name <=====\n";
    cin >> hasAC;

    if (hasAC)
    {
         uniDlg.SetApplicationContext(itstest::AC_NAME, 7);
    }

    cout << "=====> Enter 1 for UserInfo <=====\n";
    cin >> hasUserInfo;

    if (hasUserInfo)
    {
         uniDlg.SetUserInfo(itstest::USER_INFO, 25);
    }

    dlg = &uniDlg;

    cout << "======> \n";
    cout << "======> How many invokes? <======\n";
    cin >> invokeCount;

    for (int i = 1; i <= invokeCount; i++)
    {
         TCAP_Invoke    invoke;
         int invokeId;
         int opClass;

         cout << "========> \n";
         cout << "========> Enter Invoke Id: <======== \n";
         cin >> invokeId;

         invoke.SetInvokeID(invokeId);

         cout << "==========> \n";
         cout << "==========> Enter Operation Class (1, 2, 3 or 4): <======== \n";
         cin >> opClass;

         invoke.SetClass(opClass);

         int opCode= -1;
         opCode = GetReqChoice();

         if(opCode != MAP_V13_RESET_ARG && opCode != MAP_V13_READY_FOR_SM_ARG)
         {
             cout << "Invalid Choice..!! Send either ResetArg or Ready_For_SMArg" << endl;
             return;
         }

         Octets *encOctets;
         AsnObject *obj = BuildProtocolMsg(opCode);

         if (opCode >= MAP_V13_UPDATE_GPRS_LOC)
         {
             opCode = GetMapOpCodeForChoice(opCode);
         }
         invoke.SetOperation(opCode);

         EncodeMsg(obj, &encOctets);

         if (obj == NULL)
         {
            cout << "\n **** Object is Null ****" << endl;
         }
         cout << obj;

        if(opCode == map_common::OP_reset)
         {
             std::vector<byte> acEnc = map_common::EncodeApplicationContext(map_common::resetContext_v2);
             uniDlg.SetApplicationContext(&acEnc[0], acEnc.size());
         }
         else if(opCode == map_common::OP_readyForSM)
         {
             std::vector<byte> acEnc = map_common::EncodeApplicationContext(map_common::mwdMngtContext_v3);
             uniDlg.SetApplicationContext(&acEnc[0], acEnc.size());
         }


         //invoke.SetParameter(itstest::LocationArg, LOC_ARG_LEN);
         invoke.SetParameter(encOctets->GetArray());

         invoke.SetTimeOut(350);

         cpt = &invoke;

         ret = TCAP_Component::Send(ISS7_Stack, dlg, cpt);
         if(ret == ITS_SUCCESS)
         {
              cout << "\n **** TEST: TCAP Send component successful *****" << endl;
         }
         else
         {
              cout << "\n **** TEST: Component send failed ****" << endl;
         }
    }
    cout << "**** Sending on DID " << did << endl;

    ret = TCAP_Dialogue::Send(ISS7_Stack, dlg);

    if(ret != ITS_SUCCESS)
    {
         cout << "====>Failed to send Dialogue<====" << endl;
    }
    else
    {
         cout << "TCAP_TEST: Dialogue send succes PTYPE ="
              << dlg->GetDialogueType() << endl;
    }
}

int
GetReqChoice()
{
    int choice = 0;
    int op = -1;
    bool loop = true;
    printf("Enter the choice ");
    do
    {
        if(itstest::appMode == UNIT_TEST)
        {
            printf("Enter the operation you want to send\n");
            printf("\t8.Exit\n");
            printf("\t1.Initial DP - Version3\n");
            printf("\t2.Initial DP SMS - Version3\n");
            printf("\t3.Initial DP - Version2\n");
            printf("\t4.Initial DP - Version1\n");
            printf("\t5.Event Report BCSM Arg\n");
            printf("\t6.Apply Charging Report Arg \n");
#if 0
            printf("\t3.Event Report BCSM\n");
            printf("\t4.Apply Charging Report\n");
            printf("\t5.Release Call\n");
            printf("\t6.Activity Test\n");
            printf("\t7.Event Report SMS\n");
#endif
            printf("\t%d.MapV3 UpdateGprsLocation\n", MAP_V13_UPDATE_GPRS_LOC);
            printf("\t%d.MapV3 UpdateLocation\n", MAP_V13_UPDATE_LOC);
            printf("\t%d.MapV3 UpdateLocation Res\n", MAP_V13_UPDATE_LOC_RES);
            printf("\t%d.MapV3 InsertSubscriberData\n", MAP_V13_INSERT_SUB_DATA);
            printf("\t%d.MapV13 ProvideSubscriberInfoArg\n", MAP_V13_PROVIDE_SUB_INFO);
            printf("\t%d.MapV13 DeleteSubscriberDataArg\n", MAP_V13_DELETE_SUB_DATA);
            printf("\t%d.MapV13 Cancel Location Arg\n", MAP_V13_CANCEL_LOCATION);
            printf("\t%d.MapV13 Purge MS Res\n", MAP_V13_PURGEMS_RES);
            printf("\t%d.MapV13 TraceActivateModeArg\n", MAP_V13_TRACE_ACTIVATE_MODE_ARG);
            printf("\t%d.MapV13 TraceDeActivateModeArg\n", MAP_V13_TRACE_DEACTIVATE_MODE_ARG);
            printf("\t%d.MapV13 ResetArg\n", MAP_V13_RESET_ARG);
            printf("\t%d.MapV13 PurgeMSArg\n", MAP_V13_PURGE_MS_ARG);
            printf("\t%d.MapV13 SendAuthenticationInfoArg\n", MAP_V13_SEND_AUTH_INFO_ARG);
            printf("\t%d.MapV13 ReadyForSM_Arg\n", MAP_V13_READY_FOR_SM_ARG);
            printf("\t%d.MapV3  SendRoutingInformation\n", MAP_V3_SEND_ROUTING_INFO_ARG);
            //printf("\t%d.MapV3  ProvideRoamingNumber\n", MAP_V3_PROVIDE_ROAMING_NUMBER_ARG);
            printf("\t%d.MapV3  SendRoutingInformationForSM\n", MAP_V9_ROUTING_INFO_FOR_SM_ARG);

            printf("Choice : ");
            scanf("%d",&choice);
        }
        else if(itstest::appMode == UNIT_AUTO)
        {
            UserAutoData userData;
            ParseTransactionInput(&userData);
            choice = userData.operation;
            loop = false;
        }
        switch (choice)
        {
            case 1:
                IDPVersionBuilt = IDP_V3;
                return OP_initialDP;

            case 2:
                return OP_initialDPSMS;

            case 3:
                IDPVersionBuilt = IDP_V2;
                return OP_initialDP;
	    
            case 4:
                IDPVersionBuilt = IDP_V1;
                return OP_initialDP;

            case 5:
                return OP_eventReportBCSM;
            
            case 6:
                return OP_applyChargingReport;

#if 0
            case 5:
                return OP_releaseCall;

            case 6:
                return OP_activityTest;
         
            case 7:
                return OP_eventReportSMS;
#endif       
            case 8:
                exit(0);

            default:
            {
               if (choice >= MAP_V13_UPDATE_GPRS_LOC && choice <= MAP_V9_ROUTING_INFO_FOR_SM_ARG)
               {
                   return choice;
               }
               printf ("Enter the proper option............\n\n");
            }
        }
    }while (loop);

    return op;
}

ITS_ULONG GetMapOpCodeForChoice(ITS_INT choice)
{
    switch (choice)
    {
        case MAP_V13_UPDATE_GPRS_LOC:
            return map_common::OP_updateGprsLocation;

        case MAP_V13_UPDATE_LOC:
            return map_common::OP_updateLocation;

         case MAP_V13_INSERT_SUB_DATA:
            return map_common::OP_insertSubscriberData;

        case MAP_V13_PROVIDE_SUB_INFO:
            return map_common::OP_provideSubscriberInfo;

        case MAP_V13_DELETE_SUB_DATA:
            return map_common::OP_deleteSubscriberData;

        case MAP_V13_CANCEL_LOCATION:
            return map_common::OP_cancelLocation;

        case MAP_V13_TRACE_ACTIVATE_MODE_ARG:
            return map_common::OP_activateTraceMode;

        case MAP_V13_TRACE_DEACTIVATE_MODE_ARG:
            return map_common::OP_deactivateTraceMode;

        case MAP_V13_RESET_ARG:
            return map_common::OP_reset;

        case MAP_V13_PURGE_MS_ARG:
            return map_common::OP_purgeMS;

        case MAP_V13_SEND_AUTH_INFO_ARG:
            return map_common::OP_sendAuthenticationInfo;

        case MAP_V13_READY_FOR_SM_ARG:
            return map_common::OP_readyForSM;

        case MAP_V3_SEND_ROUTING_INFO_ARG:
            return map_common::OP_sendRoutingInfo;

        case MAP_V9_PROVIDE_ROAMING_NUMBER_ARG:
            return map_common::OP_provideRoamingNumber;

          case MAP_V9_ROUTING_INFO_FOR_SM_ARG:
            return map_common::OP_sendRoutingInfoForSM;
       
        default:
            break;
    }
    return 0;
}

void
CharToDigits(char  *d,char tmpBuff[], ITS_INT& len)
{

    ITS_UINT imsiLen = strlen((const char*)tmpBuff);
    ITS_INT  nIdx    = 0;
    ITS_UINT oIdx    = 0;

cout<<"LEN ---->"<<imsiLen<<endl;
while(oIdx <= imsiLen)
{
    d[nIdx] = tmpBuff[oIdx];
    oIdx++;
    d[nIdx] |= (oIdx == 0) ?  0xF0 : ((tmpBuff[oIdx] << 4) & 0xF0);
    oIdx++;
    nIdx++;
    cout<<"INT VALEUE"<<nIdx<<"OIDX--->"<<oIdx<<endl;
    }
    len = nIdx;
}

void
ITUTcapMsgs::InteractiveSendBeginDlg(ITS_HANDLE hdl)
{
    ITS_INT ret;
    TCAP_Dialogue* dlg;
    TCAP_Component* cpt;
    TCAP_Begin* begin;
    //int hasAC = 0;
    int hasProtVer = 0;
    int hasUserInfo = 0;
    bool hasInvoke = false;
    int  invokeCount =  1;
    //int val = 0;
    TCAP_Begin Qwp;
    int pcls=0;
    bool isNull;

    Json::Value l_jsonRootcap = parseCapConfig();

    Json::Value* m_jsonRoot3 = &l_jsonRootcap;
    Json::Value* m_jsonRoot4 = &(*m_jsonRoot3)["cap"];

    //NOTE: making default value to 0 for Multiple Intermediate ERB and ACR 
    NumOfERBandACHinTc_Cont = 0;
    sendERBandACRinTcEnd = false;

    TCAP_Begin     beginDlg;
    begin = &beginDlg;
    printf("\n ******** Allocated DID: %d *******\n", did);
    TCAP_AllocateDialogueId(ISS7_Stack, &did);
    printf("\n ******** Allocated DID: %d *******\n", did);

    begin->SetDialogueID(did);
    IDP_DIALOGUE_ID = did;
    begin->SetOrigAddr(cpa_itu);
    begin->SetOPC(oPC);
    //begin->SetOPC(topc);
    begin->Print(cout);
    //begin->SetOPC(itstest::opc);
   //cdp_itu.SetPointCode(itstest::dpc);
   //cdp_itu.SetSSN(itstest::dssn);
   cdp_itu.SetRouteByPCSSN(itstest::routeType);


    begin->SetDestAddr(cdp_itu);
    begin->SetDPC(dPC);
    //begin->SetDPC(tdpc);
    begin->Print(cout);
    //begin->SetDPC(dPC);

    //cout << "=====> Enter 1 for SCCP PROTOCOL CLASS 1, else \"0\" is set <=====\n";
    //cin >> pcls;
    pcls = 1;
    if(pcls!=1)
      pcls=0;

    ITS_UINT compdialogSelection=0;
    //cout << "==== > Enter \"1\" for Component & Dialog Selection\n";
    //cin >> compdialogSelection;
    compdialogSelection = 1;

    if(compdialogSelection)
    {

    hasInvoke = true;

    hasProtVer = 1;

    if (hasProtVer & pcls)
    {
         begin->SetQualityOfService(QOSI_SEQ_CTRL | QOSI_PROT_VER|QOSI_RET_OPT, 0, 0);
    }
    else if (hasProtVer)
         begin->SetQualityOfService(QOSI_PROT_VER|QOSI_RET_OPT, 0, 0);



    //cout << "=====> Enter 1 for UserInfo <=====\n";
    //cin >> hasUserInfo;
    hasUserInfo = 1;

    if (hasUserInfo)
    {
         begin->SetUserInfo(itstest::USER_INFO, 25);
    }

    dlg = begin;

    //cout << "======> \n";
    //cout << "======> How many invokes? <======\n";
    //cin >> invokeCount;

    invokeCount = 1;

    for (int i = 1; i <= invokeCount; i++)
    {

         TCAP_Invoke    invoke;
         int invokeId;
         int opClass;

         cout << "========> \n";
         //cout << "========> Enter Invoke Id: <======== \n";
         //cin >> invokeId;
         invokeId = 0;

         invoke.SetInvokeID(invokeId);

         if(itstest::appMode == UNIT_TEST)
         {
             cout << "==========> \n";
             cout << "==========> Enter Operation Class (1, 2, 3 or 4): <======== \n";
             cin >> opClass;
         }
         else if(itstest::appMode == UNIT_AUTO)
         {
             UserAutoData userData;
             ParseTransactionInput(&userData);
             opClass = userData.operationClass;
         }
         invoke.SetClass(opClass);
         int opCode= -1;
         opCode = GetReqChoice();
         if( opCode == -1 || opCode == MAP_V13_RESET_ARG )
         {
             cout << "Invalid Choice! Cannnot Send ResetArg as TC_Begin!" << endl;
             cout << "Try Sending ResetArg as : \"TC_Uni.\" ..!!" << endl;
                return;
         }
         Octets *encOctets;
         AsnObject *obj = BuildProtocolMsg(opCode);
         if (opCode >= MAP_V13_UPDATE_GPRS_LOC)
         {
             opCode = GetMapOpCodeForChoice(opCode);
         }
         //Resetting the FollowOn Flag to false to avoid restart of tool
         simulateFollowOnCases = false;
         
         if(opCode == map_common::OP_updateGprsLocation)
         {
            std::vector<byte> acenc = map_common::EncodeApplicationContext(map_common::gprsLocationUpdateContext_v3);
            begin->SetApplicationContext(&acenc[0], acenc.size());
         }
         else   if(opCode == map_common::OP_updateLocation)
         {
            std::vector<byte> acenc = map_common::EncodeApplicationContext(map_common::networkLocUpContext_v2);
            begin->SetApplicationContext(&acenc[0], acenc.size());
         }
         else if(opCode == map_common::OP_sendRoutingInfo)
         {
             std::vector<byte> acEnc = map_common::EncodeApplicationContext(map_common::locationInfoRetrievalContext_v3);
             begin->SetApplicationContext(&acEnc[0], acEnc.size());
         }
         else if(opCode == map_common::OP_provideRoamingNumber)
         {
             std::vector<byte> acEnc = map_common::EncodeApplicationContext(map_common::roamingNumberEnquiryContext_v3);
             begin->SetApplicationContext(&acEnc[0], acEnc.size());
         }
         else if (opCode == map_common::OP_provideSubscriberInfo)
         {
            std::vector<byte> acenc = map_common::EncodeApplicationContext(map_common::subscriberInfoEnquiryContext_v3);
            begin->SetApplicationContext(&acenc[0], acenc.size());
         }
         else if(opCode == map_common::OP_sendRoutingInfoForSM)
         {
             std::vector<byte> acEnc = map_common::EncodeApplicationContext(map_common::shortMsgGatewayContext_v3);
             begin->SetApplicationContext(&acEnc[0], acEnc.size());
         }

     else if (opCode == map_common::OP_insertSubscriberData || opCode == map_common::OP_deleteSubscriberData)
         {
            std::vector<byte> acenc = map_common::EncodeApplicationContext(map_common::subscriberDataMngtContext_v3);
            begin->SetApplicationContext(&acenc[0], acenc.size());
         }
         else if(opCode == map_common::OP_activateTraceMode || opCode == map_common::OP_deactivateTraceMode)
         {
             std::vector<byte> acEnc = map_common::EncodeApplicationContext(map_common::tracingContext_v3);
             begin->SetApplicationContext(&acEnc[0], acEnc.size());
         }
         else if(opCode == map_common::OP_cancelLocation)
         {
             std::vector<byte> acEnc = map_common::EncodeApplicationContext(map_common::locationCancellationContext_v3);
             begin->SetApplicationContext(&acEnc[0], acEnc.size());
         }
         else if(opCode == map_common::OP_reset)
         {
             std::vector<byte> acEnc = map_common::EncodeApplicationContext(map_common::resetContext_v2);
             begin->SetApplicationContext(&acEnc[0], acEnc.size());
         }
         else if(opCode == map_common::OP_purgeMS)
         {
             std::vector<byte> acEnc = map_common::EncodeApplicationContext(map_common::msPurgingContext_v3);
             begin->SetApplicationContext(&acEnc[0], acEnc.size());
         }
         else if(opCode == map_common::OP_sendAuthenticationInfo)
         {
             std::vector<byte> acEnc = map_common::EncodeApplicationContext(map_common::infoRetrievalContext_v3);
             begin->SetApplicationContext(&acEnc[0], acEnc.size());
         }
         else if(opCode == map_common::OP_readyForSM)
         {
             std::vector<byte> acEnc = map_common::EncodeApplicationContext(map_common::mwdMngtContext_v3);
             begin->SetApplicationContext(&acEnc[0], acEnc.size());
         }
         else if(opCode == cap::OP_initialDP || opCode == cap::OP_eventReportBCSM || opCode == cap::OP_applyChargingReport)
         {
	     if(IDPVersionBuilt == IDP_V1)
	     {
	     	std::vector<byte> acenc = cap::EncodeApplicationContext(cap::CAPV1_gsmSSF_to_gsmSCF_AC);
             	begin->SetApplicationContext(&acenc[0], acenc.size());
             }
	     else
             {
             	std::vector<byte> acenc = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
             	begin->SetApplicationContext(&acenc[0], acenc.size());
             }
         }
         else if(opCode == cap::OP_eventReportSMS || opCode == cap::OP_initialDPSMS)
         {
             std::vector<byte> acenc = cap::EncodeApplicationContext(cap::CAPV3_cap3_sms_AC);
             begin->SetApplicationContext(&acenc[0], acenc.size());
         }
         invoke.SetOperation(opCode);
         EncodeMsg(obj, &encOctets);

         if (obj == NULL)
         {
            cout << "\n **** Object is Null ****" << endl;
         }
         cout << obj;

         invoke.SetParameter(encOctets->GetArray());
         //NOTE: Set InvokeTimeOut as per configured value in json
	 Json::Value* cfg = &(*m_jsonRoot4)["InvokeTimeOut"];
         isNull = (*cfg)["Value"].isNull();
	 if(!isNull)
 	 {
	     ConfiguredInvokeTimeOut = (*cfg)["Value"].asInt();
	     invoke.SetTimeOut(ConfiguredInvokeTimeOut);
	     cout << "\n InvokeTimeOut Set = " << (*cfg)["Value"].asInt() << endl;
         }
	 else
             invoke.SetTimeOut(30);

         cpt = &invoke;

         ret = TCAP_Component::Send(ISS7_Stack, dlg, cpt);

         if(ret == ITS_SUCCESS)
         {
              cout << "\n **** TEST: TCAP Send component successful *****" << endl;
         }
         else
         {
              cout << "\n **** TEST: Component send failed ****" << endl;
         }
    }

    }
    else
    {
        dlg = begin;
    }
    cout << "**** Sending on DID : " << did << endl;
    dlg->Print(cout);

    ret = TCAP_Dialogue::Send(ISS7_Stack, dlg);

    if(ret != ITS_SUCCESS)
    {
         cout << "**** Failed to send Dialogue ****" << endl;
    }
    else
    {
         cout << "TCAP_TEST: Dialogue send succes PTYPE ="
              << dlg->GetDialogueType() << endl;
    }
}
#if 0
void
ITUTcapMsgs::InteractiveSendEnd(ITS_HANDLE hdl)
{
    ITS_INT ret;
    TCAP_Dialogue* dlg;
    TCAP_Component* cpt;
    TCAP_End       endDlg;
    int numResult = 0, outcome = 0;
    int invokeId;
    ITS_USHORT localDid;
    //ITS_UINT rejectType;
    //ITS_UINT rejectCode;
    ITS_BOOLEAN hasProtVer=0;
    ITS_BOOLEAN hasAC= 0 ;
    ITS_BOOLEAN hasUserInfo = 0;

    cout << "======> \n";
    cout << "======> Enter did : <======\n";
    cin >> localDid;
    endDlg.SetDialogueID(localDid);
    dlg = &endDlg;

    ITS_UINT compdialogSelection=0;
    cout <<"==== > Enter \"1\" for component & Dialog Selection: ";
    cin >> compdialogSelection;

    if(compdialogSelection)
    {
        cout << "======> \n";
        cout << "======> OutCome of transaction (1-success, 0-failure) <======\n";
        cin >> outcome;

        if (outcome)
        {
            cout << "=====> Enter 1 for Prot Version <=====\n";
            cin >> hasProtVer;
            if (hasProtVer)
                dlg->SetQualityOfService(QOSI_PROT_VER, 0, 0);
            cout << "=====> Enter 1 for AC Name <=====\n";
            cin >> hasAC;

            if (hasAC)
            {
                int no_AC=0;
                cout << "====> LENGTH OF AC NAME:" << endl;
                cin >>no_AC;
                dlg->SetApplicationContext(itstest::AC_NAME, no_AC);
            }

            cout << "=====> Enter 1 for UserInfo <=====\n";
            cin >> hasUserInfo;

            if (hasUserInfo)
            {
                dlg->SetUserInfo(itstest::USER_INFO, 25);
            }

            //ITS_OCTET testByte[1];

            cout << "========> \n";
            cout << "========>How many Return Results? <========\n";
            cin >> numResult;
            for (int i = 1; i <= numResult; i++)
            {
                TCAP_Result    result;

                int resNL=0;
                cout <<"=== > If you want RETURN RESULT NOT LAST press \"0\":  ";
                cin >> resNL;
                if(!resNL)
                    result  = TCAP_Result(false);
                else
                    result  = TCAP_Result(true);

                cout << "==========> \n";
                cout << "==========> Enter Invoke Id: <==========\n";
                cin >> invokeId;

                result.SetInvokeID(invokeId);

                result.SetOperation(2);
                result.SetParameter(itstest::LocationArg, LOC_ARG_LEN);

                cpt = &result;

                ret = TCAP_Component::Send(ISS7_Stack, dlg, cpt);

                if(ret == ITS_SUCCESS)
                {
                     cout << "\n **** TEST: TCAP_Comp RESULT send successful ****" << endl;
                }
                else
                {
                     cout << "\n **** TEST: TCAP_Comp RESULT failed to send. ****" << endl;
                }
           }
       }
       else
       {
           TCAP_Cancel cancel;
           cout << "==========> Enter Invoke Id: <==========\n";
            cin >> invokeId;
            cancel.SetInvokeID(invokeId);
            cpt = &cancel;

            ret = TCAP_Component::Send(ISS7_Stack, dlg, cpt);

            APP_TRACE_DEBUG(("ComponentType = %02x", cpt->GetComponentType()));

            if(ret == ITS_SUCCESS)
            {
                cout << "\n **** TEST: TCAP_Comp send successful ****" << endl;
            }
            else
            {
                cout << "\n **** TEST: TCAP_Comp ERROR failed to send: "  <<ret << endl;
            }
        }
    }

    cout << "**** Sending on DID " << localDid << endl;

    ret = TCAP_Dialogue::Send(ISS7_Stack, dlg);

    if(ret != ITS_SUCCESS)
    {
        cout << "Failed to send Dialogue" << endl;
    }
    else
    {
        cout << "TCAP_TEST: Dialogue send succes PTYPE ="
             << dlg->GetDialogueType() << endl;
    }
}
#endif
void ITUTcapMsgs::InteractiveSendEnd(ITS_HANDLE hdl)
{
    ITS_UINT ret;
    int numResult = 0;
    int numInvoke = 0;
    int invokeId;
    int i = 0;
    TCAP_Dialogue* dlg;
    TCAP_Component* cpt;
    TCAP_End* end;

    TCAP_End end_dialogue;
    end = &end_dialogue;
    ITS_USHORT localDid;
    if(IDP_DIALOGUE_ID)
    {
            cout << "IDP_DIALOGUE_ID = " << IDP_DIALOGUE_ID <<endl;
	    end->SetDialogueID(IDP_DIALOGUE_ID);
    }
    else
    {
	    cout << "======> \n";
	    cout << "======> Enter did : <======\n";
	    cin >> localDid;
	    end->SetDialogueID(localDid);
    }
    dlg = end;

    int  noterror=1;

    dlg->SetQualityOfService(QOSI_SEQ_CTRL | QOSI_PROT_VER|QOSI_RET_OPT, 0, 0);
    if(IDPVersionBuilt == IDP_V1)
    {
        std::vector<byte> acenc = cap::EncodeApplicationContext(cap::CAPV1_gsmSSF_to_gsmSCF_AC);
        dlg->SetApplicationContext(&acenc[0], acenc.size());
    }
    else
    {
        std::vector<byte> acenc = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
        dlg->SetApplicationContext(&acenc[0], acenc.size());
    }

    cout << "======> \n";

    numInvoke = 1;
    for (i = 1; i <= numInvoke; i++)
    {
        TCAP_Invoke    invoke;

        //cout << "=== >Enter Invoke Id: \n";
        //cin >> invokeId;

        invoke.SetInvokeID(++invkId);
        int opCode= -1;
        opCode = GetReqChoice();
        if( opCode == -1)
        {
            return;
        }
        Octets *encOctets;
        AsnObject *obj = BuildCapEndMsg(opCode);
        invoke.SetOperation(opCode);
        EncodeMsg(obj, &encOctets);

        if (obj == NULL)
        {
            cout << "\n **** Object is Null ****" << endl;
        }
        cout << obj;

        invoke.SetParameter(encOctets->GetArray());
        invoke.SetClass(1);
        invoke.SetTimeOut(ConfiguredInvokeTimeOut);

        cpt = &invoke;

        ret = TCAP_Component::Send(ISS7_Stack, dlg, cpt);
        if(ret == ITS_SUCCESS)
        {
            cout << "TCAP Send component success" << endl;
        }
        else
        {
            cout << "Component send failed :" << endl;
        }
    }

    cout << "**** Sending on DID " << IDP_DIALOGUE_ID << endl;

    ret = TCAP_Dialogue::Send(ISS7_Stack, dlg);

    if(ret != ITS_SUCCESS)
    {
        cout << "Failed to send Dialogue" << endl;
    }
    else
    {
        cout << "TCAP_TEST: Dialogue send succes PTYPE ="
            << dlg->GetDialogueType() << endl;
    }
}

void
ITUTcapMsgs::InteractiveSendContinue(ITS_HANDLE hdl)
{
    ITS_UINT ret;
    int numResult = 0;
    int numInvoke = 0;
    int invokeId;
    int i = 0;
    TCAP_Dialogue* dlg;
    TCAP_Component* cpt;
    TCAP_Continue* cont;
    TCAP_Continue Cwp;
    ITS_UINT rejectCode;

    TCAP_Continue  continueDlg;
    cont = &continueDlg;

    ITS_USHORT localDid;
    if(IDP_DIALOGUE_ID)
    {
            cout << "IDP_DIALOGUE_ID = " << IDP_DIALOGUE_ID <<endl;
	    cont->SetDialogueID(IDP_DIALOGUE_ID);
    }
    else
    {
	    cout << "======> \n";
	    cout << "======> Enter did : <======\n";
	    cin >> localDid;
	    cont->SetDialogueID(localDid);
    }
    cont->SetOPC(oPC);
    dlg = cont;
    ITS_UINT compdialogSelection=1;

    if(compdialogSelection)
    {
    int  noterror=1;
    //cout <<endl<<"=====>Enter 1 for Return Result & Invoke Component selection \"0\" for Error Component"<<endl;
    //cin >> noterror;

    if(noterror)
    {
        if (1)
        {
            //dlg->SetQualityOfService(QOSI_PROT_VER, 0, 0);
            dlg->SetQualityOfService(QOSI_SEQ_CTRL | QOSI_PROT_VER|QOSI_RET_OPT, 0, 0);
        }
        if(IDPVersionBuilt == IDP_V1)
        {
            std::vector<byte> acenc = cap::EncodeApplicationContext(cap::CAPV1_gsmSSF_to_gsmSCF_AC);
            dlg->SetApplicationContext(&acenc[0], acenc.size());
        }
        else
        {
            std::vector<byte> acenc = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
            dlg->SetApplicationContext(&acenc[0], acenc.size());
        }
        //int no_AC=8;
        //dlg->SetApplicationContext(AC_NAMEIDP, no_AC);

        cout << "======> \n";
        //cout << "======>How many Return Results? \n";
        //cin >> numResult;
        

        for (i = 0; i < numResult; i++)
        {
            TCAP_Result    result;

            int resNL=0;
            cout <<"=== > If you want RETURN RESULT NOT LAST press 0: ";
            cin >> resNL;
            if(!resNL)
            {
                result  = TCAP_Result(false);
            }
            else
            {
                result  = TCAP_Result(true);
            }

            cout << "Enter Invoke Id: \n";
            cin >> invokeId;

            result.SetInvokeID(invokeId);
            result.SetOperation(2);
            result.SetParameter(itstest::LocationArg, LOC_ARG_LEN);

            cpt = &result;

            ret = TCAP_Component::Send(ISS7_Stack, dlg, cpt);

            if(ret == ITS_SUCCESS)
            {
                cout << "TCAP_Comp RESULT send success:" << endl;
            }
            else
            {
                cout << "TCAP_Comp RESULT failed to send.:" << endl;
            }
        }

        //cout << "How many Invokes? \n";
        //cin >> numInvoke ;
        numInvoke = 1;
        for (i = 1; i <= numInvoke; i++)
        {
            TCAP_Invoke    invoke;

            //cout << "=== >Enter Invoke Id: \n";
            //cin >> invokeId;

            invoke.SetInvokeID(++invkId);
            int opCode= -1;
            opCode = GetReqChoice();
            if( opCode == -1)
            {
                return;
            }
            Octets *encOctets;
            AsnObject *obj = BuildCapMsg(opCode);
            invoke.SetOperation(opCode);
            EncodeMsg(obj, &encOctets);

            if (obj == NULL)
            {
                cout << "\n **** Object is Null ****" << endl;
            }
            cout << obj;

            invoke.SetParameter(encOctets->GetArray());
            invoke.SetClass(1);
            invoke.SetTimeOut(ConfiguredInvokeTimeOut);

            cpt = &invoke;

            ret = TCAP_Component::Send(ISS7_Stack, dlg, cpt);
            if(ret == ITS_SUCCESS)
            {
                cout << "TCAP Send component success" << endl;
            }
            else
            {
                cout << "Component send failed :" << endl;
            }
        }

    }
    else
    {

        int choice = 0;

        cout << "==========> \n";
        cout << "==========> Choose RetError (0), or Reject (1). <==========\n";
        cin >> choice;
        if (choice)
        {
            TCAP_Reject reject;
            cout << "==========> Enter Invoke Id: <==========\n";
            cin >> invokeId;

            reject.SetInvokeID(invokeId);
            reject.SetProblem(0x81U, 0x01U);

            cpt = &reject;
        }
        else
        {

            TCAP_Error error;

            cout << "==========> \n";
            cout << "==========> Enter Invoke Id: <==========\n";
            cin >> invokeId;

            error.SetInvokeID(invokeId);

            cout << "==========> \n";
            cout << "==========> Enter Error Code: <==========\n";
            cin >> rejectCode;

            error.SetError(rejectCode);
            cpt = &error;
        }
        ret = TCAP_Component::Send(ISS7_Stack, dlg, cpt);
        if(ret == ITS_SUCCESS)
        {
            cout << "TCAP Send Error component success" << endl;
        }
        else
        {
            cout << "Component send failed :" << endl;
        }
    }
    }

    cout << "**** Sending on DID " << IDP_DIALOGUE_ID << endl;

    ret = TCAP_Dialogue::Send(ISS7_Stack, dlg);

    if(ret != ITS_SUCCESS)
    {
        cout << "Failed to send Dialogue" << endl;
    }
    else
    {
        cout << "TCAP_TEST: Dialogue send succes PTYPE ="
            << dlg->GetDialogueType() << endl;
    }
}

void
ITUTcapMsgs::SendBeginDlg(ITS_HANDLE hdl, int inst, ITS_BOOLEAN addR)
{
   int         ret = 0;
   ITS_CTXT    dlgid;
   TCAP_Begin  begin;
   TCAP_Invoke ivk;
   ITS_HDR     hdr;
   ITS_UINT    timeout = 100;


   TCAP_AllocateDialogueId(ISS7_Stack, &dlgid);

   hdr.type = ITS_TCAP;
   hdr.context.dialogue_id = dlgid;

   begin.SetDialogueID(dlgid);
   begin.SetOrigAddr(cpa_itu);
   begin.SetOPC(oPC);

   begin.SetDestAddr(cdp_itu);
   begin.SetDPC(dPC); 

   APP_TRACE_DEBUG(("Send: DialogueId = %02x , DialogueType = %02x", dlgid, 
           begin.GetDialogueType()));

   ivk.SetInvokeID(GetInvokeID());
   ivk.SetTimeOut(timeout);

   ivk.SetClass(2);
   ivk.SetOperation(2);
 
   APP_TRACE_DEBUG(("Invokeid = %02x", ivk.GetInvokeID()));

   srand(time(NULL));

   if(0) //(rand() % 11) <= 5)
   {
       ivk.SetParameter(itstest::octs185, OCTS_185_LEN);
   }
   else
   {
       ivk.SetParameter(itstest::LocationArg, LOC_ARG_LEN);
   }

   ret = TCAP_Component::Send(ISS7_Stack, &begin, &ivk);

   if(ret == ITS_SUCCESS)
   {
       ret = TCAP_Dialogue::Send(ISS7_Stack, &begin);
       if(ret == ITS_SUCCESS)
       {
           stats.UpdateSendStats(begin.GetDialogueType());
           stats.UpdateSendStats(ivk.GetComponentType());
           
           APP_TRACE_DEBUG(("Send Dialogue Type = %02x Dlgid = %d", 
                          begin.GetDialogueType(), dlgid));
           APP_TRACE_DEBUG(("TCAP Cpt and DlgType Send success."));
       }
   }

   return;
}

void
ITUTcapMsgs::SendBeginDlg(ITS_HANDLE hdl, int inst, ITS_BOOLEAN addR, int opCode)
{
   int         ret = 0;
   ITS_CTXT    dlgid;
   TCAP_Begin  begin;
   TCAP_Invoke ivk;
   ITS_HDR     hdr;
   ITS_UINT    timeout = 100;


   TCAP_AllocateDialogueId(ISS7_Stack, &dlgid);

   hdr.type = ITS_TCAP;
   hdr.context.dialogue_id = dlgid;

   begin.SetDialogueID(dlgid);
   begin.SetOrigAddr(cpa_itu);
   begin.SetOPC(oPC);

   begin.SetDestAddr(cdp_itu);
   begin.SetDPC(dPC); 


   APP_TRACE_DEBUG(("Send: DialogueId = %02x , DialogueType = %02x", dlgid, 
           begin.GetDialogueType()));

   ivk.SetInvokeID(GetInvokeID());
   ivk.SetTimeOut(timeout);

   ivk.SetClass(3);

   Octets *encOctets;
   AsnObject *obj = BuildProtocolMsg(opCode);
   EncodeMsg(obj, &encOctets);

   if (obj == NULL)
   {
       cout << "\n **** Object is Null ****" << endl;
   }
   cout << obj;

   if (opCode >= MAP_V13_UPDATE_GPRS_LOC)
   {
       opCode = GetMapOpCodeForChoice(opCode);
   }

   ivk.SetOperation(opCode);
 
   APP_TRACE_DEBUG(("Invokeid = %02x", ivk.GetInvokeID()));

   srand(time(NULL));

   /*if(0) //(rand() % 11) <= 5)
   {
       ivk.SetParameter(itstest::octs185, OCTS_185_LEN);
   }
   else
   {
       ivk.SetParameter(itstest::LocationArg, LOC_ARG_LEN);
   }*/
   switch(opCode)
   {
        case map_common::OP_updateGprsLocation:
            {
                ivk.SetParameter(encOctets->GetArray());
                //ivk.SetParameter(itstest::LocationArg, LOC_ARG_LEN);
                break;
            }
        case map_common::OP_purgeMS:
            {   
                ivk.SetParameter(encOctets->GetArray());
                break;
            }
        case map_common::OP_sendAuthenticationInfo:
            {
                ivk.SetParameter(encOctets->GetArray());
                //ivk.SetParameter(itstest::AuthenticationArg, AUTH_ARG_LEN);
                break;
            }
   }

   ret = TCAP_Component::Send(ISS7_Stack, &begin, &ivk);

   if(ret == ITS_SUCCESS)
   {
       ret = TCAP_Dialogue::Send(ISS7_Stack, &begin);
       if(ret == ITS_SUCCESS)
       {
           stats.UpdateSendStats(begin.GetDialogueType());
           stats.UpdateSendStats(ivk.GetComponentType());

           APP_TRACE_DEBUG(("Send Dialogue Type = %02x Dlgid = %d", 
                          begin.GetDialogueType(), dlgid));
           APP_TRACE_DEBUG(("TCAP Cpt and DlgType Send success."));
       }
   }

   return;
}

void
ITUTcapMsgs::SendPreArrangedEnd(ITS_HANDLE hdl, ITS_USHORT dlgid)
{
   int ret = 0;

   TCAP_End end;

   end.SetDialogueID(dlgid);

   end.SetPreArrangedEnd(true);

   APP_TRACE_DEBUG(("SendPreArrangedEnd: DialogueId = %02x , DialogueType = %02x", dlgid, 
           end.GetDialogueType()));

   ret = TCAP_Dialogue::Send(ISS7_Stack, &end);

   if(ret == ITS_SUCCESS)
   {
       stats.UpdateSendStats(end.GetDialogueType(), true);
       APP_TRACE_DEBUG(("Send prearranged end success:\n"));
   }

  return;
}

void ITUTcapMsgs::BuildTCAPErrorCpt(TCAP_Dialogue *dlg, ITS_OCTET invokeId, TCAP_Error **tcapErr,  ITS_OCTET errVal)
{

    APP_TRACE_DEBUG(("Inside ITUTcapMsgs::BuildTCAPErrorCpt"));
    Octets *enc2 = 0;
    bool isNull;
    bool isAVPEnabled;
    TCAP_Error *terr = new TCAP_Error();


    terr->SetInvokeID(invokeId);

    terr->SetError(errVal);

    switch(errVal)
    {
        case map_common::ERR_unknownSubscriber:
            {
                Json::Value* cfg = &(*m_jsonRoot1)["UnknownSubscriberParam"];
                map_v13::UnknownSubscriberParam *unkwnSubs = new map_v13::UnknownSubscriberParam();
                isNull = (*cfg)["UnknownSubscriberDiagnostic"]["Value"].isNull();
                isAVPEnabled = (*cfg)["UnknownSubscriberDiagnostic"]["Enabled"].asBool();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::UnknownSubscriberDiagnostic unknsubdia((*cfg)["UnknownSubscriberDiagnostic"]["Value"].asInt());
                    unkwnSubs->SetUnknownSubscriberDiagnostic(unknsubdia);
                }
                EncodeMsg(unkwnSubs, &enc2);
                terr->SetParameter(enc2->GetArray());
                break;
            }
        case map_common::ERR_roamingNotAllowed:
            {
                Json::Value* cfg = &(*m_jsonRoot1)["RoamingNotAllowedParam"];
                map_v13::RoamingNotAllowedParam *roamNot = new map_v13::RoamingNotAllowedParam();
                isNull = (*cfg)["RoamingNotAllowedCause"]["Value"].isNull();
                if(!isNull)
                {
                    map_v13::RoamingNotAllowedCause rnac((*cfg)["RoamingNotAllowedCause"]["Value"].asInt());
                    roamNot->SetRoamingNotAllowedCause(rnac);
                }

                isNull = (*cfg)["AdditionalRoamingNotAllowedCause"]["Value"].isNull();
                isAVPEnabled = (*cfg)["AdditionalRoamingNotAllowedCause"]["Enabled"].asBool();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::AdditionalRoamingNotAllowedCause arnac((*cfg)["AdditionalRoamingNotAllowedCause"]["Value"].asInt());
                    roamNot->SetAdditionalRoamingNotAllowedCause(arnac);
                }
                EncodeMsg(roamNot, &enc2);
                terr->SetParameter(enc2->GetArray());
                break;
            }
        case map_common::ERR_dataMissing:
            {
                map_v13::DataMissingParam *datamiss = new map_v13::DataMissingParam();
                EncodeMsg(datamiss, &enc2);
                terr->SetParameter(enc2->GetArray());
                break;
            }
        case map_common::ERR_unexpectedDataValue:
            {
                Json::Value* cfg = &(*m_jsonRoot1)["UnexpectedDataParam"];
                map_v13::UnexpectedDataParam *udp = new map_v13::UnexpectedDataParam();

                isAVPEnabled = (*cfg)["unexpectedSubscriber"]["Enabled"].asBool();
                isNull = (*cfg)["unexpectedSubscriber"]["Enabled"].isNull();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::UnexpectedDataParam::UnexpectedSubscriber us;
                    udp->SetUnexpectedSubscriber(us);
                }
                EncodeMsg(udp, &enc2);
                terr->SetParameter(enc2->GetArray());
                break;
            }
        case map_common::ERR_facilityNotSupported:
            {
                Json::Value* cfg = &(*m_jsonRoot1)["FacilityNotSupParam"];
                map_v13::FacilityNotSupParam *fns = new map_v13::FacilityNotSupParam();

                isAVPEnabled = (*cfg)["shapeOfLocationEstimateNotSupported"]["Enabled"].asBool();
                isNull = (*cfg)["shapeOfLocationEstimateNotSupported"]["Enabled"].isNull();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::FacilityNotSupParam::ShapeOfLocationEstimateNotSupported solens;
                    fns->SetShapeOfLocationEstimateNotSupported(solens);
                }
                isAVPEnabled = (*cfg)["neededLcsCapabilityNotSupportedInServingNode"]["Enabled"].asBool();
                isNull = (*cfg)["neededLcsCapabilityNotSupportedInServingNode"]["Enabled"].isNull();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::FacilityNotSupParam::NeededLcsCapabilityNotSupportedInServingNode nlc;
                    fns->SetNeededLcsCapabilityNotSupportedInServingNode(nlc);
                }
                EncodeMsg(fns, &enc2);
                terr->SetParameter(enc2->GetArray());
                break;
            }
        case map_common::ERR_systemFailure:
            {
                Json::Value* cfg = &(*m_jsonRoot1)["SystemFailureParam"];
                map_v13::SystemFailureParam *sfp = new map_v13::SystemFailureParam();

                isAVPEnabled = (*cfg)["NetworkResource"]["Enabled"].asBool();
                isNull = (*cfg)["NetworkResource"]["Value"].isNull();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::SystemFailureParam::NetworkResource nr((*cfg)["NetworkResource"]["Value"].asInt());
                    sfp->SetChoiceNetworkResource(nr);
                }
                isAVPEnabled = (*cfg)["ExtensibleSystemFailureParam"]["Enabled"].asBool();
                isNull = (*cfg)["ExtensibleSystemFailureParam"]["Enabled"].isNull();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::SystemFailureParam::ExtensibleSystemFailureParam esfp;
                    isAVPEnabled = (*cfg)["ExtensibleSystemFailureParam"]["NetworkResource"]["Enabled"].asBool();
                    isNull = (*cfg)["ExtensibleSystemFailureParam"]["NetworkResource"]["Value"].isNull();
                    if((!isNull) && isAVPEnabled)
                    {
                        map_v13::SystemFailureParam::ExtensibleSystemFailureParam::NetworkResource nr((*cfg)["ExtensibleSystemFailureParam"]["NetworkResource"]["Value"].asInt());
                        esfp.SetNetworkResource(nr);
                    }
                    isAVPEnabled = (*cfg)["ExtensibleSystemFailureParam"]["AdditionalNetworkResource"]["Enabled"].asBool();
                    isNull = (*cfg)["ExtensibleSystemFailureParam"]["AdditionalNetworkResource"]["Value"].isNull();
                    if((!isNull) && isAVPEnabled)
                    {
                        map_v13::SystemFailureParam::ExtensibleSystemFailureParam::AdditionalNetworkResource anr((*cfg)["ExtensibleSystemFailureParam"]["AdditionalNetworkResource"]["Value"].asInt());
                        esfp.SetAdditionalNetworkResource(anr);
                    }
                    isAVPEnabled = (*cfg)["ExtensibleSystemFailureParam"]["FailureCauseParam"]["Enabled"].asBool();
                    isNull = (*cfg)["ExtensibleSystemFailureParam"]["FailureCauseParam"]["Value"].isNull();
                    if((!isNull) && isAVPEnabled)
                    {
                        map_v13::SystemFailureParam::ExtensibleSystemFailureParam::FailureCauseParam fcp((*cfg)["ExtensibleSystemFailureParam"]["FailureCauseParam"]["Value"].asInt());
                        esfp.SetFailureCauseParam(fcp);
                    }
                    sfp->SetChoiceExtensibleSystemFailureParam(esfp);
                }
                EncodeMsg(sfp, &enc2);
                terr->SetParameter(enc2->GetArray());
                break;
            }
        case map_common::ERR_illegalSubscriber:
            {
                map_v13::IllegalSubscriberParam *isp = new map_v13::IllegalSubscriberParam();
                EncodeMsg(isp, &enc2);
                terr->SetParameter(enc2->GetArray());
                break;
            }
        case map_common::ERR_illegalEquipment:
            {
                map_v13::IllegalEquipmentParam *iep = new map_v13::IllegalEquipmentParam();
                EncodeMsg(iep, &enc2);
                terr->SetParameter(enc2->GetArray());
                break;
            }
        case map_common::ERR_absentSubscriber:
            {
                Json::Value* cfg = &(*m_jsonRoot1)["AbsentSubscriberParam"];
                map_v13::AbsentSubscriberParam *asp = new map_v13::AbsentSubscriberParam();

                isAVPEnabled = (*cfg)["AbsentSubscriberReason"]["Enabled"].asBool();
                isNull = (*cfg)["AbsentSubscriberReason"]["Value"].isNull();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::AbsentSubscriberParam::AbsentSubscriberReason asr((*cfg)["AbsentSubscriberReason"]["Value"].asInt());
                    asp->SetAbsentSubscriberReason(asr);
                }
                EncodeMsg(asp, &enc2);
                terr->SetParameter(enc2->GetArray());
                break;
            }
        case map_common::ERR_unidentifiedSubscriber:
            {
                map_v13::UnidentifiedSubParam *usp = new map_v13::UnidentifiedSubParam();
                EncodeMsg(usp, &enc2);
                terr->SetParameter(enc2->GetArray());
                break;
            }
        case map_common::ERR_tracingBufferFull:
            {
                map_v13::TracingBufferFullParam *tbfp = new map_v13::TracingBufferFullParam();
                EncodeMsg(tbfp, &enc2);
                terr->SetParameter(enc2->GetArray());
                break;
            }
    }
            

    *tcapErr = terr;

}
int prevCptInvoke = -1;

std::map<ITS_CTXT, ITS_OCTET> gInvokeList;

int ITUTcapMsgs::SendResponses(TCAP_Dialogue *dlg,
                                 TCAP_Component *cpt)
{

    APP_TRACE_DEBUG(("Inside SendResponses() function."));
    TCAP_Continue tc_cont;
    TCAP_End      tc_end;
    TCAP_Invoke   isdr;
    TCAP_Invoke   erbr;
    TCAP_Result  ula;
    TCAP_Result   ugla;
    TCAP_Result   saia;
    TCAP_Result   rfsr;
    TCAP_Result   puMsa;
    TCAP_Unidirectional tc_uni;
    bool isNull;
    int errVal = 0;
    TCAP_Error *tcapErr = NULL;

    //APP_TRACE_DEBUG(("Inside ITUTcapMsgs::SendCAPResponse"));
    ITS_ByteArray app_ctxt = map_common::EncodeApplicationContext(map_common::networkLocUpContext_v3);
    tc_end.SetApplicationContext(app_ctxt);
    tc_cont.SetApplicationContext(app_ctxt);

    srand(time(0));
    //int num = rand() % 17;

    if (dlg->GetDialogueType() == TCPPT_TC_BEGIN && cpt->GetComponentType() == TCPPT_TC_INVOKE) 
    {
        TCAP_Invoke *ivk = dynamic_cast<TCAP_Invoke *> (cpt);
        ITS_LONG op;
        ivk->GetOperation(op);

        if (op == map_common::OP_sendAuthenticationInfo) 
        {
            Json::Value* cfg = &(*m_jsonRoot1)["SendAuthenticationInfoErrRes"];
            isNull = (*cfg)["Enabled"].isNull();
            if((!isNull) && (*cfg)["Enabled"].asBool())
            {
                errVal = (*cfg)["Value"].asInt();
                if(errVal > 0 && errVal <= 72)
                {
                    app_ctxt = map_common::EncodeApplicationContext(map_common::infoRetrievalContext_v3);
                    tc_end.SetApplicationContext(app_ctxt);

                    BuildTCAPErrorCpt(dlg, cpt->GetInvokeID(), &tcapErr, errVal);

                    tc_end.SetDialogueID(dlg->GetDialogueID());

                    if (TCAP_Component::Send(ISS7_Stack, &tc_end, tcapErr) == ITS_SUCCESS) 
                    {
                        if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                        {
                            APP_TRACE_DEBUG(("Sent SendAuthenticationInfoError v3"));
                        }
                    }
                }
                else
                {
                    APP_TRACE_ERROR(("Invalid Error Value %c", errVal));
                }
            }
            else
            {
                app_ctxt = map_common::EncodeApplicationContext(map_common::infoRetrievalContext_v3);
                tc_end.SetApplicationContext(app_ctxt);

                AsnObject *tempSaia = BuildMapMsg(MAP_V13_SEND_AUTHENTICATION_INFO_RES);
                Octets *enc2 = 0;

                saia.SetInvokeID(cpt->GetInvokeID());

                EncodeMsg(tempSaia, &enc2);

                saia.SetParameter(enc2->GetArray());
                saia.SetOperation(map_common::OP_sendAuthenticationInfo);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, &saia) == ITS_SUCCESS) 
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                    {
                        APP_TRACE_DEBUG(("Sent SendAuthenticationInfoRes v3"));
                    }
                }

                delete enc2;
                delete tempSaia;
                enc2 = 0;
                tempSaia = 0;
            }
        }
        else if (op == map_common::OP_purgeMS) 
        {
            Json::Value* cfg = &(*m_jsonRoot1)["PurgeMSErr_Res"];
            isNull = (*cfg)["Enabled"].isNull();
            if((!isNull) && (*cfg)["Enabled"].asBool())
            {
                errVal = (*cfg)["Value"].asInt();
                BuildTCAPErrorCpt(dlg, cpt->GetInvokeID(), &tcapErr, errVal);

                app_ctxt = map_common::EncodeApplicationContext(map_common::msPurgingContext_v3);
                tc_end.SetApplicationContext(app_ctxt);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, tcapErr) == ITS_SUCCESS) 
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                    {
                        APP_TRACE_DEBUG(("Sent iPurgeMs_Err v3"));
                    }
                }
            }
            else
            {
                app_ctxt = map_common::EncodeApplicationContext(map_common::msPurgingContext_v3);
                tc_end.SetApplicationContext(app_ctxt);

                AsnObject *temppuMsa = BuildMapMsg(MAP_V13_PURGEMS_RES);
                Octets *enc2 = 0;

                puMsa.SetInvokeID(cpt->GetInvokeID());

                EncodeMsg(temppuMsa, &enc2);

                puMsa.SetParameter(enc2->GetArray());
                puMsa.SetOperation(map_common::OP_purgeMS);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, &puMsa) == ITS_SUCCESS) 
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                    {
                        APP_TRACE_DEBUG(("Sent PurgeMs_Res v3"));
                    }
                }

                delete enc2;
                delete temppuMsa;
                enc2 = 0;
                temppuMsa = 0;
            }
        }

        else if (op == map_common::OP_updateGprsLocation && 
                itstest::noISD)
        {
            Json::Value* cfg = &(*m_jsonRoot1)["UpdateGprsLocationErrRes"];
            isNull = (*cfg)["Enabled"].isNull();
            if((!isNull) && (*cfg)["Enabled"].asBool())
            {
                errVal = (*cfg)["Value"].asInt();
                BuildTCAPErrorCpt(dlg, cpt->GetInvokeID(), &tcapErr, errVal);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, tcapErr) == ITS_SUCCESS) 
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                    {
                        APP_TRACE_DEBUG(("Sent UpdateGprsLocationRes v3"));
                    }
                }
            }
            else
            {
                app_ctxt = map_common::EncodeApplicationContext(map_common::gprsLocationUpdateContext_v3);
                tc_end.SetApplicationContext(app_ctxt);

                AsnObject *tempUgla = BuildMapMsg(MAP_V13_UPDATE_GPRS_LOC_RES);
                Octets *enc2 = 0;
                std::map<ITS_CTXT, ITS_OCTET>::iterator itr = gInvokeList.find(dlg->GetDialogueID());

                if (itr != gInvokeList.end()) 
                {
                    ugla.SetInvokeID((*itr).second);
                    gInvokeList.erase(itr);
                } 
                else 
                {
                    ugla.SetInvokeID(cpt->GetInvokeID());
                }

                EncodeMsg(tempUgla, &enc2);

                ugla.SetParameter(enc2->GetArray());
                ugla.SetOperation(map_common::OP_updateGprsLocation);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, &ugla) == ITS_SUCCESS) 
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                    {
                        APP_TRACE_DEBUG(("Sent UpdateGprsLocationRes"));
                    }
                }

                delete enc2;
                delete tempUgla;
                enc2 = 0;
                tempUgla = 0;

                gRecvImsi.clear();
            }
        }
        else if (op == map_common::OP_updateGprsLocation && 
                !itstest::noISD)
        {
            Json::Value* cfg = &(*m_jsonRoot1)["UpdateGprsLocationErrRes"];
            isNull = (*cfg)["Enabled"].isNull();
            if((!isNull) && (*cfg)["Enabled"].asBool())
            {
                errVal = (*cfg)["Value"].asInt();
                BuildTCAPErrorCpt(dlg, cpt->GetInvokeID(), &tcapErr, errVal);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, tcapErr) == ITS_SUCCESS) 
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                    {
                        APP_TRACE_DEBUG(("Sent UpdateGprsLocationRes v3"));
                    }
                }
            }
            else
            {
                app_ctxt = map_common::EncodeApplicationContext(map_common::subscriberDataMngtContext_v3);
                tc_end.SetApplicationContext(app_ctxt);

                AsnObject *tempIsdr = BuildMapMsg(MAP_V13_INSERT_SUB_DATA);
                Octets *enc1 = 0;

                EncodeMsg(tempIsdr, &enc1);
                ITS_UINT pointCode = 0; 
                bool isNational = false;
                ITS_OCTET ssn = 0;
                TCAP_Begin *begin = (TCAP_Begin*)dlg;
                begin->GetOrigAddr(isNational, pointCode, ssn);
                isdr.SetParameter(enc1->GetArray());
                isdr.SetClass(1);
                isdr.SetInvokeID(10);
                isdr.SetOperation(map_common::OP_insertSubscriberData);

                tc_cont.SetDialogueID(dlg->GetDialogueID());
                tc_cont.SetOrigAddr(isNational, oPC, oSN);

                std::pair<ITS_CTXT, ITS_OCTET> idpair(dlg->GetDialogueID(), cpt->GetInvokeID());
                gInvokeList.insert(idpair);

                if (TCAP_Component::Send(ISS7_Stack, &tc_cont, &isdr) != ITS_SUCCESS) 
                {
                    cout << "Failed To Send Component 1" << endl;
                }
                if (TCAP_Dialogue::Send(ISS7_Stack, &tc_cont) != ITS_SUCCESS) 
                {
                    cout << "Failed To send Dialogue Continue" << endl;
                }

                delete enc1;
                delete tempIsdr;
                enc1 = 0;
                tempIsdr = 0;            
            }
        }
        else if (op == map_common::OP_readyForSM)
        {
            Json::Value* cfg = &(*m_jsonRoot1)["ReadyForSMErrRes"];
            isNull = (*cfg)["Enabled"].isNull();
            if((!isNull) && (*cfg)["Enabled"].asBool())
            {
                errVal = (*cfg)["Value"].asInt();
                BuildTCAPErrorCpt(dlg, cpt->GetInvokeID(), &tcapErr, errVal);
                
                app_ctxt = map_common::EncodeApplicationContext(map_common::mwdMngtContext_v3);
                tc_end.SetApplicationContext(app_ctxt);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, tcapErr) == ITS_SUCCESS) 
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                    {
                        APP_TRACE_DEBUG(("Sent ReadyForSMErrRes v3"));
                    }
                }
            }
            else
            {
                app_ctxt = map_common::EncodeApplicationContext(map_common::mwdMngtContext_v3);
                tc_end.SetApplicationContext(app_ctxt);

                AsnObject *tempRfsr = BuildMapMsg(MAP_V13_READY_FOR_SM_RES);
                Octets *enc2 = 0;

                rfsr.SetInvokeID(cpt->GetInvokeID());

                EncodeMsg(tempRfsr, &enc2);

                rfsr.SetParameter(enc2->GetArray());
                rfsr.SetOperation(map_common::OP_readyForSM);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, &rfsr) == ITS_SUCCESS) 
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                    {
                        APP_TRACE_DEBUG(("Sent SendAuthenticationInfoRes v3"));
                    }
                }

                delete enc2;
                delete tempRfsr;
                enc2 = 0;
                tempRfsr = 0;
            }
        }



        else if (op == map_common::OP_insertSubscriberData)
        {   
            int sleep_value;
            int get_invokeid;
            bool isNull;
            bool isAVPEnabled;
            //Json::Value l_jsonRoot = parseMapConfig();
            //Json::Value* m_jsonRoot1 = &l_jsonRoot;
            Json::Value* m_jsonRoot2 = &(*m_jsonRoot1)["Sleep"];
            Json::Value* cfg = &(*m_jsonRoot2)["Sleep_Insert_Subscriber"];
            isNull = (*cfg)["Value"].isNull();            
            isAVPEnabled = (*cfg)["Enabled"].asBool();
            sleep_value = (*cfg)["Value"].asInt();
            APP_TRACE_DEBUG(("Sleep_Value set is %d", sleep_value)); 
            get_invokeid = cpt->GetInvokeID(); 
            if(!isNull && isAVPEnabled)
            {
                SendResponseOnTimeOutInsertSubscriberData(dlg->GetDialogueID(),sleep_value,get_invokeid);
            }
            else
            {

                Json::Value* cfg = &(*m_jsonRoot1)["InsertSubscriberDataErrRes"];
                isNull = (*cfg)["Enabled"].isNull();
                if((!isNull) && (*cfg)["Enabled"].asBool())
                {
                    errVal = (*cfg)["Value"].asInt();
                    BuildTCAPErrorCpt(dlg, cpt->GetInvokeID(), &tcapErr, errVal);

                    app_ctxt = map_common::EncodeApplicationContext(map_common::subscriberDataMngtContext_v3);
                    tc_end.SetApplicationContext(app_ctxt);

                    tc_end.SetDialogueID(dlg->GetDialogueID());

                    if (TCAP_Component::Send(ISS7_Stack, &tc_end, tcapErr) == ITS_SUCCESS) 
                    {
                        if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                        {
                            APP_TRACE_DEBUG(("Sent InsertSubscriberDataRes v3"));
                        }
                    }
                }
            else
            {
                app_ctxt = map_common::EncodeApplicationContext(map_common::subscriberDataMngtContext_v3);
                tc_end.SetApplicationContext(app_ctxt);

                AsnObject *tempRfsr = BuildMapMsg(MAP_V13_INSERT_SUB_DATA_RES);
                Octets *enc2 = 0;

                rfsr.SetInvokeID(cpt->GetInvokeID());

                EncodeMsg(tempRfsr, &enc2);

                rfsr.SetParameter(enc2->GetArray());
                rfsr.SetOperation(map_common::OP_insertSubscriberData);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, &rfsr) == ITS_SUCCESS) 
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                    {
                        APP_TRACE_DEBUG(("Sent InsertSubscriberDataRes v3"));
                    }
                }

                delete enc2;
                delete tempRfsr;
                enc2 = 0;
                tempRfsr = 0;
            }
            }
        }

        else if (op == map_common::OP_deleteSubscriberData)
        {
            int sleep_value;
            int get_invokeid;
            bool isNull;
            bool isAVPEnabled;
            //Json::Value l_jsonRoot = parseMapConfig();
            //Json::Value* m_jsonRoot3 = &l_jsonRoot;
            Json::Value* m_jsonRoot4 = &(*m_jsonRoot1)["Sleep"];
            Json::Value* cfg = &(*m_jsonRoot4)["Sleep_Delete_Subscriber"];
            isNull = (*cfg)["Value"].isNull();            
            isAVPEnabled = (*cfg)["Enabled"].asBool();
            sleep_value = (*cfg)["Value"].asInt();
            get_invokeid = cpt->GetInvokeID(); 
            if(!isNull && isAVPEnabled)
            {
                APP_TRACE_DEBUG(("Sleep_Value set is %d", sleep_value)); 
                SendResponseOnTimeOutDeleteSubscriberData(dlg->GetDialogueID(),sleep_value,get_invokeid);
            }

            else
            {

                Json::Value* cfg = &(*m_jsonRoot1)["DeleteSubscriberDataErrRes"];
                isNull = (*cfg)["Enabled"].isNull();
                if((!isNull) && (*cfg)["Enabled"].asBool())
                {
                    errVal = (*cfg)["Value"].asInt();
                    BuildTCAPErrorCpt(dlg, cpt->GetInvokeID(), &tcapErr, errVal);

                    app_ctxt = map_common::EncodeApplicationContext(map_common::subscriberDataMngtContext_v3);
                    tc_end.SetApplicationContext(app_ctxt);

                    tc_end.SetDialogueID(dlg->GetDialogueID());

                    if (TCAP_Component::Send(ISS7_Stack, &tc_end, tcapErr) == ITS_SUCCESS) 
                    {
                        if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                        {
                            APP_TRACE_DEBUG(("Sent DeleteSubscriberDataRes v3"));
                        }
                    }
                }
                else
                {
                    app_ctxt = map_common::EncodeApplicationContext(map_common::subscriberDataMngtContext_v3);
                    tc_end.SetApplicationContext(app_ctxt);

                    AsnObject *tempRfsr = BuildMapMsg(MAP_V13_DELETE_SUB_DATA_RES);
                    Octets *enc2 = 0;

                    rfsr.SetInvokeID(cpt->GetInvokeID());

                    EncodeMsg(tempRfsr, &enc2);

                    rfsr.SetParameter(enc2->GetArray());
                    rfsr.SetOperation(map_common::OP_deleteSubscriberData);

                    tc_end.SetDialogueID(dlg->GetDialogueID());
                    //tc_end.SetDialogueID(900);

                    if (TCAP_Component::Send(ISS7_Stack, &tc_end, &rfsr) == ITS_SUCCESS)
                    {
                        if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS)
                        {
                            APP_TRACE_DEBUG(("Sent DeleteSubscriberDataRes v3"));
                        }
                    }

                    delete enc2;
                    delete tempRfsr;
                    enc2 = 0;
                    tempRfsr = 0;
                }
            }
        }
        else if (op == map_common::OP_cancelLocation)
        {
            int sleep_value;
            int get_invokeid;
            bool isNull;
            bool isAVPEnabled;
            int invalid_invokeid;
            int invalid_tid;
            bool isNull1,isNull2,isNull3,isNull4,isNull5;
            bool isAVPEnabled5,isAVPEnabled1,isAVPEnabled2,isAVPEnabled3,isAVPEnabled4;

            //Json::Value l_jsonRoot = parseMapConfig();
            //Json::Value* m_jsonRoot1 = &l_jsonRoot;
            Json::Value* m_jsonRoot2 = &(*m_jsonRoot1)["Sleep"];
            Json::Value* cfg = &(*m_jsonRoot2)["Sleep_Cancel_Location"];
            isNull = (*cfg)["Value"].isNull();            
            isAVPEnabled = (*cfg)["Enabled"].asBool();
            sleep_value = (*cfg)["Value"].asInt();
            get_invokeid = cpt->GetInvokeID(); 
            if(!isNull && isAVPEnabled)
            {   
                APP_TRACE_DEBUG(("Sleep_Value set is %d", sleep_value)); 
                APP_TRACE_DEBUG(("Invoke ID received %d", get_invokeid));
                SendResponseOnTimeOutCancelLocation(dlg->GetDialogueID(),sleep_value,get_invokeid);
            }
            else
            {
                Json::Value* cfg = &(*m_jsonRoot1)["CancelLocationErrRes"];
                isNull = (*cfg)["Enabled"].isNull();
                errVal = (*cfg)["Value"].asInt();
                if((!isNull) && (*cfg)["Enabled"].asBool())
                {      
                    BuildTCAPErrorCpt(dlg, cpt->GetInvokeID(), &tcapErr, errVal);
                    app_ctxt = map_common::EncodeApplicationContext(map_common::locationCancellationContext_v3);
                    tc_end.SetApplicationContext(app_ctxt);

                    tc_end.SetDialogueID(dlg->GetDialogueID());

                    if (TCAP_Component::Send(ISS7_Stack, &tc_end, tcapErr) == ITS_SUCCESS) 
                    {
                        if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                        {
                            APP_TRACE_DEBUG(("Sent CancelLocationRes v3"));
                        }
                    }
                }
                else
                {
                    //Json::Value l_jsonRoot1 = parseMapConfig();
                    //Json::Value* m_jsonRoot3 = &l_jsonRoot1;
                    Json::Value* m_jsonRoot4 = &(*m_jsonRoot1)["Negative_case"];
                    Json::Value* cfg2 = &(*m_jsonRoot4)["Invalid_invokeid"];
                    Json::Value* cfg1 = &(*m_jsonRoot4)["Invalid_tid"];

                    isNull5 = (*cfg2)["Value"].isNull();            
                    isAVPEnabled5 = (*cfg2)["Enabled"].asBool();
                    invalid_invokeid  = (*cfg2)["Value"].asInt();

                    isNull1 = (*cfg1)["Value"].isNull();            
                    isAVPEnabled1 = (*cfg1)["Enabled"].asBool();
                    invalid_tid = (*cfg1)["Value"].asInt();
                    
                    if(!isNull5 && isAVPEnabled5)
                    {

                        APP_TRACE_DEBUG(("Invalid Invoke ID  is %d ", invalid_invokeid)); 
                        app_ctxt = map_common::EncodeApplicationContext(map_common::locationCancellationContext_v3);
                        tc_end.SetApplicationContext(app_ctxt);

                        AsnObject *tempRfsr = BuildMapMsg(MAP_V13_CANCEL_LOCATION_RES);
                        Octets *enc2 = 0;

                        //rfsr.SetInvokeID(cpt->GetInvokeID());
                        rfsr.SetInvokeID(invalid_invokeid);  // set invalid invoke ID parsed from JSON

                        EncodeMsg(tempRfsr, &enc2);

                        rfsr.SetParameter(enc2->GetArray());
                        rfsr.SetOperation(map_common::OP_cancelLocation);

                        tc_end.SetDialogueID(dlg->GetDialogueID());

                        if (TCAP_Component::Send(ISS7_Stack, &tc_end, &rfsr) == ITS_SUCCESS) 
                        {
                            if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                            {
                                APP_TRACE_DEBUG(("Sent CancelLocationRes v3"));
                            }
                        }

                        delete enc2;
                        delete tempRfsr;
                        enc2 = 0;
                        tempRfsr = 0;
                    }

                    else if(!isNull1 && isAVPEnabled1)
                    {

                        APP_TRACE_DEBUG(("Invalid TID  is %d ", invalid_tid)); 
                        app_ctxt = map_common::EncodeApplicationContext(map_common::locationCancellationContext_v3);
                        tc_end.SetApplicationContext(app_ctxt);

                        AsnObject *tempRfsr = BuildMapMsg(MAP_V13_CANCEL_LOCATION_RES);
                        Octets *enc2 = 0;

                        rfsr.SetInvokeID(cpt->GetInvokeID());

                        EncodeMsg(tempRfsr, &enc2);

                        rfsr.SetParameter(enc2->GetArray());
                        rfsr.SetOperation(map_common::OP_cancelLocation);

                        tc_end.SetDialogueID(invalid_tid);

                        if (TCAP_Component::Send(ISS7_Stack, &tc_end, &rfsr) == ITS_SUCCESS) 
                        {
                            if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                            {
                                APP_TRACE_DEBUG(("Sent CancelLocationRes v3"));
                            }
                        }

                        delete enc2;
                        delete tempRfsr;
                        enc2 = 0;
                        tempRfsr = 0;

                    }

                    else
                    {

                        app_ctxt = map_common::EncodeApplicationContext(map_common::locationCancellationContext_v3);
                        tc_end.SetApplicationContext(app_ctxt);

                        AsnObject *tempRfsr = BuildMapMsg(MAP_V13_CANCEL_LOCATION_RES);
                        Octets *enc2 = 0;

                        rfsr.SetInvokeID(cpt->GetInvokeID());

                        EncodeMsg(tempRfsr, &enc2);

                        rfsr.SetParameter(enc2->GetArray());
                        rfsr.SetOperation(map_common::OP_cancelLocation);

                        tc_end.SetDialogueID(dlg->GetDialogueID());

                        if (TCAP_Component::Send(ISS7_Stack, &tc_end, &rfsr) == ITS_SUCCESS) 
                        {
                            if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                            {
                                APP_TRACE_DEBUG(("Sent CancelLocationRes v3"));
                            }
                        }

                        delete enc2;
                        delete tempRfsr;
                        enc2 = 0;
                        tempRfsr = 0;
                    }
                }
            }
        }
        else if (op == map_common::OP_sendRoutingInfoForSM)
        {
            app_ctxt = map_common::EncodeApplicationContext(map_common::shortMsgGatewayContext_v3);
            tc_end.SetApplicationContext(app_ctxt);

            AsnObject *tempRfsr = BuildMapMsg(MAP_V9_ROUTING_INFO_FOR_SM_RES);
            Octets *enc2 = 0;

            rfsr.SetInvokeID(cpt->GetInvokeID());

            EncodeMsg(tempRfsr, &enc2);

            rfsr.SetParameter(enc2->GetArray());
            rfsr.SetOperation(map_common::OP_sendRoutingInfoForSM);

            tc_end.SetDialogueID(dlg->GetDialogueID());

            if (TCAP_Component::Send(ISS7_Stack, &tc_end, &rfsr) == ITS_SUCCESS) 
            {
                if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                {
                    APP_TRACE_DEBUG(("Sent SendRoutingInfoForSMRes v3"));
                }
            }

            delete enc2;
            delete tempRfsr;
            enc2 = 0;
            tempRfsr = 0;
        }
        else if (op == map_common::OP_provideSubscriberInfo)
        {
            Json::Value* cfg = &(*m_jsonRoot1)["ProvideSubscriberInfoErrRes"];
            isNull = (*cfg)["Enabled"].isNull();
            if((!isNull) && (*cfg)["Enabled"].asBool())
            {
                errVal = (*cfg)["Value"].asInt();
                BuildTCAPErrorCpt(dlg, cpt->GetInvokeID(), &tcapErr, errVal);

                app_ctxt = map_common::EncodeApplicationContext(map_common::subscriberInfoEnquiryContext_v3);
                tc_end.SetApplicationContext(app_ctxt);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, tcapErr) == ITS_SUCCESS) 
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                    {
                        APP_TRACE_DEBUG(("Sent ProvideSubscriberInfoRes v3"));
                    }
                }
            }
            else
            {
                app_ctxt = map_common::EncodeApplicationContext(map_common::subscriberInfoEnquiryContext_v3);
                tc_end.SetApplicationContext(app_ctxt);

                AsnObject *tempRfsr = BuildMapMsg(MAP_V13_PROVIDE_SUB_INFO_RES);
                Octets *enc2 = 0;

                rfsr.SetInvokeID(cpt->GetInvokeID());

                EncodeMsg(tempRfsr, &enc2);

                rfsr.SetParameter(enc2->GetArray());
                rfsr.SetOperation(map_common::OP_provideSubscriberInfo);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, &rfsr) == ITS_SUCCESS)
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS)
                    {
                        APP_TRACE_DEBUG(("Sent ProvideSubscriberInfoRes v3"));
                    }
                }

                delete enc2;
                delete tempRfsr;
                enc2 = 0;
                tempRfsr = 0;
            }
        }
        else if (op == map_common::OP_deactivateTraceMode)
        {
            Json::Value* cfg = &(*m_jsonRoot1)["DeactivateTraceModeErrRes"];
            isNull = (*cfg)["Enabled"].isNull();
            if((!isNull) && (*cfg)["Enabled"].asBool())
            {
                errVal = (*cfg)["Value"].asInt();
                BuildTCAPErrorCpt(dlg, cpt->GetInvokeID(), &tcapErr, errVal);

                app_ctxt = map_common::EncodeApplicationContext(map_common::tracingContext_v3);
                tc_end.SetApplicationContext(app_ctxt);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, tcapErr) == ITS_SUCCESS) 
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                    {
                        APP_TRACE_DEBUG(("Sent DeactivateTraceModeErrRes v3"));
                    }
                }
            }
            else
            {
                app_ctxt = map_common::EncodeApplicationContext(map_common::tracingContext_v3);
                tc_end.SetApplicationContext(app_ctxt);

                AsnObject *tempRfsr = BuildMapMsg(MAP_V13_TRACE_DEACTIVATE_MODE_RES);
                Octets *enc2 = 0;

                rfsr.SetInvokeID(cpt->GetInvokeID());

                EncodeMsg(tempRfsr, &enc2);

                rfsr.SetParameter(enc2->GetArray());
                rfsr.SetOperation(map_common::OP_deactivateTraceMode);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, &rfsr) == ITS_SUCCESS)
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS)
                    {
                        APP_TRACE_DEBUG(("Sent DeactivateTraceModeRes v3"));
                    }
                }

                delete enc2;
                delete tempRfsr;
                enc2 = 0;
                tempRfsr = 0;
            }
        }
        else if (op == map_common::OP_updateLocation) 
        {
            Json::Value* cfg = &(*m_jsonRoot1)["UpdateLocationErrRes"];
            isNull = (*cfg)["Enabled"].isNull();
            if((!isNull) && (*cfg)["Enabled"].asBool())
            {
                errVal = (*cfg)["Value"].asInt();
                BuildTCAPErrorCpt(dlg, cpt->GetInvokeID(), &tcapErr, errVal);

                app_ctxt = map_common::EncodeApplicationContext(map_common::networkLocUpContext_v2);
                tc_end.SetApplicationContext(app_ctxt);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, tcapErr) == ITS_SUCCESS) 
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                    {
                        APP_TRACE_DEBUG(("Sent  Update Location Response v2"));
                    }
                }
            }
            else

            {
                app_ctxt = map_common::EncodeApplicationContext(map_common::networkLocUpContext_v2);
                tc_end.SetApplicationContext(app_ctxt);
                AsnObject *tempUla = BuildMapMsg(MAP_V13_UPDATE_LOC_RES);
                Octets *enc2 = 0;
                std::map<ITS_CTXT, ITS_OCTET>::iterator itr = gInvokeList.find(dlg->GetDialogueID());

                if (itr != gInvokeList.end()) 
                {
                    ula.SetInvokeID((*itr).second);
                    gInvokeList.erase(itr);
                } 
                else 
                {
                    ula.SetInvokeID(cpt->GetInvokeID());
                }

                EncodeMsg(tempUla, &enc2);

                ula.SetParameter(enc2->GetArray());
                ula.SetOperation(map_common::OP_updateLocation);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, &ula) == ITS_SUCCESS) 
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                    {
                        APP_TRACE_DEBUG(("Sent UpdateLocationRes"));
                    }
                }

                delete enc2;
                delete tempUla;
                enc2 = 0;
                tempUla = 0;

                gRecvImsi.clear();
            }
        }

        else if (op == map_common::OP_sendRoutingInfo)
        {
            Json::Value* cfg = &(*m_jsonRoot1)["SendRoutingInfoErrRes"];
            isNull = (*cfg)["Enabled"].isNull();
            if((!isNull) && (*cfg)["Enabled"].asBool())
            {
                errVal = (*cfg)["Value"].asInt();
                BuildTCAPErrorCpt(dlg, cpt->GetInvokeID(), &tcapErr, errVal);

                app_ctxt = map_common::EncodeApplicationContext(map_common::locationInfoRetrievalContext_v3);
                tc_end.SetApplicationContext(app_ctxt);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, tcapErr) == ITS_SUCCESS) 
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                    {
                        APP_TRACE_DEBUG(("Sent SendRoutingInfoRes v3"));
                    }
                }
            }

            else
            {
                app_ctxt = map_common::EncodeApplicationContext(map_common::locationInfoRetrievalContext_v3);
                tc_end.SetApplicationContext(app_ctxt);

                AsnObject *tempRfsr = BuildMapMsg(MAP_V3_SEND_ROUTING_INFO_RES);
                Octets *enc2 = 0;

                rfsr.SetInvokeID(cpt->GetInvokeID());

                EncodeMsg(tempRfsr, &enc2);

                rfsr.SetParameter(enc2->GetArray());
                rfsr.SetOperation(map_common::OP_sendRoutingInfo);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, &rfsr) == ITS_SUCCESS) 
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                    {
                        APP_TRACE_DEBUG(("Sent SendRoutingInfo Responsev3"));
                    }
                }

                delete enc2;
                delete tempRfsr;
                enc2 = 0;
                tempRfsr = 0;
            }
        }

            
        else if (op == map_common::OP_provideRoamingNumber)
        {

            Json::Value* cfg = &(*m_jsonRoot1)["ProvideRoamingNumberErrRes"];
            isNull = (*cfg)["Enabled"].isNull();
            if((!isNull) && (*cfg)["Enabled"].asBool())
            {
                errVal = (*cfg)["Value"].asInt();
                BuildTCAPErrorCpt(dlg, cpt->GetInvokeID(), &tcapErr, errVal);

                app_ctxt = map_common::EncodeApplicationContext(map_common::roamingNumberEnquiryContext_v3);
                tc_end.SetApplicationContext(app_ctxt);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, tcapErr) == ITS_SUCCESS) 
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                    {
                        APP_TRACE_DEBUG(("Sent ProvideRoamingNumberRes v3"));
                    }
                }
            }
            else
            {

                app_ctxt = map_common::EncodeApplicationContext(map_common::roamingNumberEnquiryContext_v3);
                tc_end.SetApplicationContext(app_ctxt);

                AsnObject *tempRfsr = BuildMapMsg(MAP_V9_PROVIDE_ROAMING_NUMBER_RES);
                Octets *enc2 = 0;

                rfsr.SetInvokeID(cpt->GetInvokeID());

                EncodeMsg(tempRfsr, &enc2);

                rfsr.SetParameter(enc2->GetArray());
                rfsr.SetOperation(map_common::OP_provideRoamingNumber);

                tc_end.SetDialogueID(dlg->GetDialogueID());

                if (TCAP_Component::Send(ISS7_Stack, &tc_end, &rfsr) == ITS_SUCCESS)
                {
                    if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS)
                    {
                        APP_TRACE_DEBUG(("Sent SendRoutingInfo Responsev3"));
                    }
                }

                delete enc2;
                delete tempRfsr;
                enc2 = 0;
                tempRfsr = 0;
            }
        } 
            else if (op == map_common::OP_activateTraceMode)
            {
                Json::Value* cfg = &(*m_jsonRoot1)["ActivateTraceModeErrRes"];
                isNull = (*cfg)["Enabled"].isNull();
                if((!isNull) && (*cfg)["Enabled"].asBool())
                {
                    errVal = (*cfg)["Value"].asInt();
                    BuildTCAPErrorCpt(dlg, cpt->GetInvokeID(), &tcapErr, errVal);

                    app_ctxt = map_common::EncodeApplicationContext(map_common::tracingContext_v3);
                    tc_end.SetApplicationContext(app_ctxt);

                    tc_end.SetDialogueID(dlg->GetDialogueID());

                    if (TCAP_Component::Send(ISS7_Stack, &tc_end, tcapErr) == ITS_SUCCESS) 
                    {
                        if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                        {
                            APP_TRACE_DEBUG(("Sent ActivateTraceModeErrRes v3"));
                        }
                    }
                }
                else
                {
                    app_ctxt = map_common::EncodeApplicationContext(map_common::tracingContext_v3);
                    tc_end.SetApplicationContext(app_ctxt);

                    AsnObject *tempRfsr = BuildMapMsg(MAP_V13_TRACE_ACTIVATE_MODE_RES);
                    Octets *enc2 = 0;

                    rfsr.SetInvokeID(cpt->GetInvokeID());

                    EncodeMsg(tempRfsr, &enc2);

                    rfsr.SetParameter(enc2->GetArray());
                    rfsr.SetOperation(map_common::OP_activateTraceMode);

                    tc_end.SetDialogueID(dlg->GetDialogueID());

                    if (TCAP_Component::Send(ISS7_Stack, &tc_end, &rfsr) == ITS_SUCCESS)
                    {
                        if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS)
                        {
                            APP_TRACE_DEBUG(("Sent ActivateTraceModeRes v3"));
                        }
                    }

                    delete enc2;
                    delete tempRfsr;
                    enc2 = 0;
                    tempRfsr = 0;
                }
            }

        }
    else if (dlg->GetDialogueType() == TCPPT_TC_UNI && cpt->GetComponentType() == TCPPT_TC_INVOKE)
    {
        TCAP_Invoke *ivk = dynamic_cast<TCAP_Invoke *> (cpt);
        ITS_LONG op;
        ivk->GetOperation(op);
        if(op == map_common::OP_reset)
        {
            APP_TRACE_DEBUG(("Received Reset Arg.. Consume It..!!"));
        }
    }
    else if (dlg->GetDialogueType() == TCPPT_TC_CONTINUE && cpt->GetComponentType() == TCPPT_TC_RESULT_L)
    {
        // We received a Continue; send an End

        TCAP_Result *res = dynamic_cast<TCAP_Result *> (cpt);
        ITS_LONG op;
        res->GetOperation(op);

        // To send multiple  ISD messages

        if ((op == map_common::OP_insertSubscriberData) && (itstest::noOfTimesISD > ISD_counter))
        {   

            std::vector<byte> acenc = map_common::EncodeApplicationContext(map_common::subscriberDataMngtContext_v3);
            tc_end.SetApplicationContext(app_ctxt);
            AsnObject *tempIsdr = BuildMapMsg(MAP_V13_INSERT_SUB_DATA);
            Octets *enc1 = 0;

            EncodeMsg(tempIsdr, &enc1);
            ITS_UINT pointCode = 0; 
            bool isNational = false;
            ITS_OCTET ssn = 0;
            TCAP_Begin *begin = (TCAP_Begin*)dlg;
            begin->GetOrigAddr(isNational, pointCode, ssn);
            isdr.SetParameter(enc1->GetArray());
            isdr.SetClass(1);
            isdr.SetInvokeID(isd_invk_id);
            isdr.SetOperation(map_common::OP_insertSubscriberData);

            tc_cont.SetDialogueID(dlg->GetDialogueID());
            tc_cont.SetOrigAddr(isNational, oPC, oSN);

            std::pair<ITS_CTXT, ITS_OCTET> idpair(dlg->GetDialogueID(), cpt->GetInvokeID());
            gInvokeList.insert(idpair);

            if (TCAP_Component::Send(ISS7_Stack, &tc_cont, &isdr) != ITS_SUCCESS) 
            {
                cout << "Failed To Send Component 1" << endl;
            }
            if (TCAP_Dialogue::Send(ISS7_Stack, &tc_cont) != ITS_SUCCESS) 
            {
                cout << "Failed To send Dialogue Continue" << endl;
            }
            delete enc1;
            delete tempIsdr;
            enc1 = 0;
            ISD_counter++;
            isd_invk_id++;
        }

        else if(op == map_common::OP_insertSubscriberData)
            
        {
            AsnObject *tempUgla = BuildMapMsg(MAP_V13_UPDATE_GPRS_LOC_RES);
            Octets *enc2 = 0;
            std::map<ITS_CTXT, ITS_OCTET>::iterator itr = gInvokeList.find(dlg->GetDialogueID());

            if (itr != gInvokeList.end()) 
            {
                ugla.SetInvokeID((*itr).second);
                gInvokeList.erase(itr);
            } else 
            {
                ugla.SetInvokeID(cpt->GetInvokeID());
            }

            EncodeMsg(tempUgla, &enc2);

            ugla.SetParameter(enc2->GetArray());
            ugla.SetOperation(map_common::OP_updateGprsLocation);

            tc_end.SetDialogueID(dlg->GetDialogueID());

            if (TCAP_Component::Send(ISS7_Stack, &tc_end, &ugla) == ITS_SUCCESS) 
            {
                if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                {
                    APP_TRACE_DEBUG(("Sent UpdateGprsLocationRes"));
                }
            }

            delete enc2;
            delete tempUgla;
            enc2 = 0;
            tempUgla = 0;
        }

        else if(op == cap::OP_releaseCall)
        {
            APP_TRACE_DEBUG(("Nothing To do for after receiving Release Call"));
        }

    }
    else if (dlg->GetDialogueType() == TCPPT_TC_CONTINUE && cpt->GetComponentType() == TCPPT_TC_INVOKE)
    {
        TCAP_Invoke *ivk = dynamic_cast<TCAP_Invoke *> (cpt);
        ITS_LONG op;
        ivk->GetOperation(op);

        bool isNull;
        bool isAVPEnabled;

        Json::Value l_jsonRootcap = parseCapConfig();

        Json::Value* m_jsonRoot3 = &l_jsonRootcap;
        Json::Value* m_jsonRoot4 = &(*m_jsonRoot3)["cap"];


        if (op == map_common::OP_insertSubscriberData)
        {
            app_ctxt = map_common::EncodeApplicationContext(map_common::subscriberDataMngtContext_v3);
            tc_cont.SetApplicationContext(app_ctxt);

            AsnObject *tempRfsr = BuildMapMsg(MAP_V13_INSERT_SUB_DATA_RES);
            Octets *enc2 = 0;

            rfsr.SetInvokeID(cpt->GetInvokeID());

            EncodeMsg(tempRfsr, &enc2);

            rfsr.SetParameter(enc2->GetArray());
            rfsr.SetOperation(map_common::OP_insertSubscriberData);

            tc_cont.SetOrigAddr(false, oPC, oSN);
            tc_cont.SetDialogueID(dlg->GetDialogueID());

            if (TCAP_Component::Send(ISS7_Stack, &tc_cont, &rfsr) == ITS_SUCCESS) 
            {
                if (TCAP_Dialogue::Send(ISS7_Stack, &tc_cont) == ITS_SUCCESS) 
                {
                    APP_TRACE_DEBUG(("Sent InsertSubscriberDataRes v3"));
                }
            }

            delete enc2;
            delete tempRfsr;
            enc2 = 0;
            tempRfsr = 0;
        }
     
          else if (op == map_common::OP_activateTraceMode)
        {
            app_ctxt = map_common::EncodeApplicationContext(map_common::tracingContext_v3);
            tc_cont.SetApplicationContext(app_ctxt);

            AsnObject *tempRfsr = BuildMapMsg(MAP_V13_TRACE_ACTIVATE_MODE_RES);
            Octets *enc2 = 0;

            rfsr.SetInvokeID(cpt->GetInvokeID());

            EncodeMsg(tempRfsr, &enc2);

            rfsr.SetParameter(enc2->GetArray());
            rfsr.SetOperation(map_common::OP_activateTraceMode);

            tc_cont.SetOrigAddr(false, oPC, oSN);
            tc_cont.SetDialogueID(dlg->GetDialogueID());

            if (TCAP_Component::Send(ISS7_Stack, &tc_cont, &rfsr) == ITS_SUCCESS)
            {
                if (TCAP_Dialogue::Send(ISS7_Stack, &tc_cont) == ITS_SUCCESS)
                {
                    APP_TRACE_DEBUG(("Sent ActivateTraceModeRes v3"));
                }
            }

            delete enc2;
            delete tempRfsr;
            enc2 = 0;
            tempRfsr = 0;
        }
        else if(op == cap::OP_requestReportSMSEvent)
        {
            APP_TRACE_DEBUG(("Request Report SMS Event received in Tc_Cont"));
        }
        else if(op == cap::OP_continueSMS)
        {
            APP_TRACE_DEBUG(("Continue SMS Event received in Tc_Cont"));
            
            Json::Value* cfg = &(*m_jsonRoot4)["SendResponse_After_Receiving_ContinueSMS"]["Send_Only_TCAP_Abort"];
            isNull = (*cfg)["Value"].isNull();
            isAVPEnabled = (*cfg)["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                sleep((*cfg)["Value"].asInt());
                TcapAbortReason = (*cfg)["Reason"].asInt();
                SendTcapAbort(dlg);
            }

            cfg = &(*m_jsonRoot4)["SendResponse_After_Receiving_ContinueSMS"]["Send_Only_TCAP_U_Abort"];
            isNull = (*cfg)["Value"].isNull();
            isAVPEnabled = (*cfg)["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                sleep((*cfg)["Value"].asInt());
                TcapAbortReason = (*cfg)["Reason"].asInt();
                SendTcapUAbort(dlg);
            }

            cfg = &(*m_jsonRoot4)["SendResponse_After_Receiving_ContinueSMS"]["Send_ERBSMS_in_ReturnResult_in_TcCont"];
            isAVPEnabled = (*cfg)["Enabled"].asBool();
            isNull = (*cfg)["Value"].isNull();
            if(!isNull && isAVPEnabled)
            {
                sleep((*cfg)["Value"].asInt());
                SendERBInReturnResultLastInCont(dlg);
            }

            cfg = &(*m_jsonRoot4)["SendResponse_After_Receiving_ContinueSMS"]["Send_ERBSMS_in_ReturnResult_in_TcEnd"];
            isAVPEnabled = (*cfg)["Enabled"].asBool();
            isNull = (*cfg)["Value"].isNull();
            if(!isNull && isAVPEnabled)
            {
                sleep((*cfg)["Value"].asInt());
                SendERBInReturnResultLastInEnd(dlg);
            }

            cfg = &(*m_jsonRoot4)["SendResponse_After_Receiving_ContinueSMS"]["Send_TCAP_Error_in_TcCont"];
            isAVPEnabled = (*cfg)["Enabled"].asBool();
            isNull = (*cfg)["Value"].isNull();
            if(!isNull && isAVPEnabled)
            {
                sleep((*cfg)["Value"].asInt());
                SendTcapErrorInContinue(dlg);
            }

            cfg = &(*m_jsonRoot4)["SendResponse_After_Receiving_ContinueSMS"]["Send_TCAP_Error_in_TcEnd"];
            isAVPEnabled = (*cfg)["Enabled"].asBool();
            isNull = (*cfg)["Value"].isNull();
            if(!isNull && isAVPEnabled)
            {
                sleep((*cfg)["Value"].asInt());
                SendTcapErrorInEnd(dlg);
            }

            cfg = &(*m_jsonRoot4)["SendResponse_After_Receiving_ContinueSMS"]["Send_ERBSMSArg_in_TcEnd"];
            isAVPEnabled = (*cfg)["Enabled"].asBool();
            isNull = (*cfg)["Value"].isNull();
            if(!isNull && isAVPEnabled)
            {
                sleep((*cfg)["Value"].asInt());
                SendEventReportSMSArginTcEnd(dlg); 
            }

        }
        else if(op == cap::OP_requestReportBCSMEvent)
        {
            APP_TRACE_DEBUG(("Nothing To do for after receiving RRB"));         
        }
        else if(op == cap::OP_releaseCall)
        {
            APP_TRACE_DEBUG(("Release Call Recieved in Tc_Cont"));
            BuildAndSendERBandACRinTcEnd(dlg);
        }
        else if(op == cap::OP_applyCharging && LastCptRcvd)
        {
            try {
                if(IsReleaseIfdurationExceededisSet)
                {
                    APP_TRACE_DEBUG((" ACH came with ReleaseIfdurationExceeded as true"));
                    Json::Value* cfg = &(*m_jsonRoot4)["SendERBandACRinTcCont_if_ReleaseIfdurationExceeded"];
                    isNull = (*cfg)["Enabled"].isNull();
                    isAVPEnabled = (*cfg)["Enabled"].asBool();
                    if(!isNull && isAVPEnabled)
                    {
                        sendERBandACRinTcContAgain = true;
                        BuildAndSendERBandACRinTcCont(dlg,true);
                        sendERBandACRinTcContAgain = false;
                    }
                    else
                    {
                       BuildAndSendERBandACRinTcEnd(dlg); 
                    }
                    IsReleaseIfdurationExceededisSet = false;
                }
                else
                {
                    if(NumOfERBandACHinTc_Cont == 0 && sendERBandACRinTcEnd == false)
                    {
                        Json::Value* cfg = &(*m_jsonRoot4)["SendERBAndACRinTcContAgain"];
                        isNull = (*cfg)["Value"].isNull();
                        isAVPEnabled = (*cfg)["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            NumOfERBandACHinTc_Cont = (*cfg)["Value"].asInt();
                            sendERBandACRinTcContAgain = true;
                            BuildAndSendERBandACRinTcCont(dlg);
                            sendERBandACRinTcContAgain = false;
                            NumOfERBandACHinTc_Cont--;
                            if(NumOfERBandACHinTc_Cont == 0)
                                sendERBandACRinTcEnd = true;
                        }
                        else
                        {
                            BuildAndSendERBandACRinTcEnd(dlg);
                        }
                    }
                    else if(NumOfERBandACHinTc_Cont)
                    {
                        sendERBandACRinTcContAgain = true;
                        BuildAndSendERBandACRinTcCont(dlg);
                        sendERBandACRinTcContAgain = false;
                        NumOfERBandACHinTc_Cont--;
                        if(NumOfERBandACHinTc_Cont == 0)
                            sendERBandACRinTcEnd = true;
                    }
                    else if(NumOfERBandACHinTc_Cont == 0 && sendERBandACRinTcEnd == true)
                    {
                        BuildAndSendERBandACRinTcEnd(dlg);
                        sendERBandACRinTcEnd = false;
                    }
                }
            }
            catch(...)
            {    
                APP_TRACE_DEBUG((" Encode Failed "));
            }
        }
        else if(op == cap::OP_continue || op == cap::OP_connect)
        {
            try {
                Json::Value* cfg = &(*m_jsonRoot4)["NoERBACRForRoASR"];
                isNull = (*cfg)["Enabled"].isNull();
                isAVPEnabled = (*cfg)["Enabled"].asBool();
                if(!(!isNull && isAVPEnabled))
                {
                    if(IsReleaseIfdurationExceededisSet)
                    {
                        APP_TRACE_DEBUG((" ACH came with ReleaseIfdurationExceeded as true"));
                        cfg = &(*m_jsonRoot4)["SendERBandACRinTcCont_if_ReleaseIfdurationExceeded"];
                        isNull = (*cfg)["Enabled"].isNull();
                        isAVPEnabled = (*cfg)["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            BuildAndSendERBandACRinTcCont(dlg);
                        }
                        else
                        {
                            //NOTE: Sending ERB with o_Answer first and wait for few seconds 
                            SendEventReportBCSMArgInTcCont(dlg);
                            sleep(2);
                            //ERB with o_disconnect and ACR with callActive false
                            BuildAndSendERBandACRinTcEnd(dlg); 
                        }
                        IsReleaseIfdurationExceededisSet = false;
                    }
                    else
                    {
                        Json::Value* m_jsonRoot5 = NULL; 
                        if(simulateFollowOnCases)
                        {
                            m_jsonRoot5 = &(*m_jsonRoot4)["Send_Intermediate_CAP_ERB_ACR_For_FollowOn"];
                            cfg = &(*m_jsonRoot5)["Version_of_FollowOn_msgs"];
                            isNull = (*cfg)["Value"].isNull();
                            isAVPEnabled = (*cfg)["Enabled"].asBool();
                            if(!isNull && isAVPEnabled)
                            {
                                IDPVersionBuilt == (*cfg)["Value"].asInt();
                            }
                        }
                        else
                        {
                            m_jsonRoot5 = &(*m_jsonRoot4)["Send_Multiple_CAP_ERB_ACR"];
                        }
                        
                        cfg = &(*m_jsonRoot5)["Send_UDTS_Message"];
                        isNull = (*cfg)["Value"].isNull();
                        isAVPEnabled = (*cfg)["Enabled"].asBool();

                        if(!isNull && isAVPEnabled)
                        {
                            sleep((*cfg)["Value"].asInt());
                            BuildUDTSMessage(dlg);
                        }
                        
                        cfg = &(*m_jsonRoot5)["Send_Only_ERB_in_TcCont"];
                        isNull = (*cfg)["Value"].isNull();
                        isAVPEnabled = (*cfg)["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            sleep((*cfg)["Value"].asInt());

                            APP_TRACE_DEBUG((" Send ERB in TC_Cont "));
                            SendEventReportBCSMArgInTcCont(dlg);
                            //To Simulate Local Control in IWF
                            cfg = &(*m_jsonRoot5)["Send_Only_ERB_in_TcCont"]["Send_ERB_in_TcCont_Again"];
                            isNull = (*cfg)["Value"].isNull();
                            isAVPEnabled = (*cfg)["Enabled"].asBool();
                            if(!isNull && isAVPEnabled)
                            {
                                sleep((*cfg)["Value"].asInt());
                                sendERBandACRinTcContAgain = true;
                                SendEventReportBCSMArgInTcCont(dlg);
                                sendERBandACRinTcContAgain = false;
                            }
                            cfg = &(*m_jsonRoot5)["Send_Only_ERB_in_TcCont"]["Send_ERB_in_TcEnd_Again"];
                            isNull = (*cfg)["Value"].isNull();
                            isAVPEnabled = (*cfg)["Enabled"].asBool();
                            if(!isNull && isAVPEnabled)
                            {
                                sleep((*cfg)["Value"].asInt());
                                SendEventReportBCSMArgInTcEnd(dlg);
                            }
                        }

                        cfg = &(*m_jsonRoot5)["Send_Only_ACR_in_TcCont"];
                        isNull = (*cfg)["Value"].isNull();
                        isAVPEnabled = (*cfg)["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            sleep((*cfg)["Value"].asInt());
                            APP_TRACE_DEBUG((" Send ACR in TC_Cont "));
                            SendApplyChargingReportArgInTcCont(dlg);
                        }

                        cfg = &(*m_jsonRoot5)["Send_Only_ERB_in_TcEnd"];
                        isNull = (*cfg)["Value"].isNull();
                        isAVPEnabled = (*cfg)["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            sleep((*cfg)["Value"].asInt());
                            SendEventReportBCSMArgInTcEnd(dlg);
                        }

                        cfg = &(*m_jsonRoot5)["Send_Only_ACR_in_TcEnd"];
                        isNull = (*cfg)["Value"].isNull();
                        isAVPEnabled = (*cfg)["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            sleep((*cfg)["Value"].asInt());
                            APP_TRACE_DEBUG((" Send ACR in TC_End "));
                            SendApplyChargingReportInTcEnd(dlg);
                        }

                        cfg = &(*m_jsonRoot5)["Send_Only_TCAP_Abort"];
                        isNull = (*cfg)["Value"].isNull();
                        isAVPEnabled = (*cfg)["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            sleep((*cfg)["Value"].asInt());
                            TcapAbortReason = (*cfg)["Reason"].asInt();
                            SendTcapAbort(dlg);
                        }

                        cfg = &(*m_jsonRoot5)["Send_Only_TCAP_U_Abort"];
                        isNull = (*cfg)["Value"].isNull();
                        isAVPEnabled = (*cfg)["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            sleep((*cfg)["Value"].asInt());
                            TcapAbortReason = (*cfg)["Reason"].asInt();
                            SendTcapUAbort(dlg);
                        }
                        
                        cfg = &(*m_jsonRoot5)["Send_Both_ERB_ACR_in_TcCont"];
                        isNull = (*cfg)["Value"].isNull();
                        isAVPEnabled = (*cfg)["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            sleep((*cfg)["Value"].asInt());
                            APP_TRACE_DEBUG((" Send ERB in TC_Cont "));
                            SendEventReportBCSMArgInTcCont(dlg);
                            if(IsBusyornoAnswerSet == false)
                            {
                                APP_TRACE_DEBUG((" Send ACR in TC_Cont "));
                                SendApplyChargingReportArgInTcCont(dlg);
                            }
                            else
                                IsBusyornoAnswerSet = false;
                        }
                        
                        cfg = &(*m_jsonRoot5)["Send_Both_ACR_ERB_in_TcCont"];
                        isNull = (*cfg)["Value"].isNull();
                        isAVPEnabled = (*cfg)["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            sleep((*cfg)["Value"].asInt());
                            APP_TRACE_DEBUG((" Send ACR in TC_Cont "));
                            SendApplyChargingReportArgInTcCont(dlg);
                            APP_TRACE_DEBUG((" Send ERB in TC_Cont "));
                            SendEventReportBCSMArgInTcCont(dlg);
                        }

                        cfg = &(*m_jsonRoot5)["Send_Both_ERB_ACR_in_Single_TcCont"];
                        isNull = (*cfg)["Value"].isNull();
                        isAVPEnabled = (*cfg)["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            sleep((*cfg)["Value"].asInt());
                            APP_TRACE_DEBUG((" Send ERB and ACR in TC_Cont "));
                            sendERBandACRinTcContAgain = true;
                            SendERBandACRInTcCont(dlg);
                            sendERBandACRinTcContAgain = false;
                        }           
                        
                        cfg = &(*m_jsonRoot5)["Send_Both_ACR_ERB_in_Single_TcCont"];
                        isNull = (*cfg)["Value"].isNull();
                        isAVPEnabled = (*cfg)["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            sleep((*cfg)["Value"].asInt());
                            APP_TRACE_DEBUG((" Send ACR and ERB in TC_Cont "));
                            sendERBandACRinTcContAgain = true;
                            SendERBandACRInTcCont(dlg, true);
                            sendERBandACRinTcContAgain = false;
                        }

                        cfg = &(*m_jsonRoot5)["Send_Both_ERB_ACR_in_TcEnd"];
                        isNull = (*cfg)["Value"].isNull();
                        isAVPEnabled = (*cfg)["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            sleep((*cfg)["Value"].asInt());
                            APP_TRACE_DEBUG((" Send ERB and ACR in TC_End "));
                            SendERBandACRInTcEnd(dlg);
                        }

                        cfg = &(*m_jsonRoot5)["Send_Both_ACR_ERB_in_TcEnd"];
                        isNull = (*cfg)["Value"].isNull();
                        isAVPEnabled = (*cfg)["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            sleep((*cfg)["Value"].asInt());
                            APP_TRACE_DEBUG((" Send ACR and ERB in TC_End "));
                            SendERBandACRInTcEnd(dlg, true);
                        }

                        cfg = &(*m_jsonRoot5)["Send_ERB_in_ReturnResult_in_TcCont"];
                        isNull = (*cfg)["Value"].isNull();
                        isAVPEnabled = (*cfg)["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            sleep((*cfg)["Value"].asInt());
                            APP_TRACE_DEBUG((" Send ERB in Return Result in TcCont "));
                            SendERBInReturnResultLastInCont(dlg);
                        }

                        cfg = &(*m_jsonRoot5)["Send_ERB_in_ReturnResult_in_TcEnd"];
                        isNull = (*cfg)["Value"].isNull();
                        isAVPEnabled = (*cfg)["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            sleep((*cfg)["Value"].asInt());
                            APP_TRACE_DEBUG((" Send ERB in Return Result in TcEnd "));
                            SendERBInReturnResultLastInEnd(dlg);
                        }

                        cfg = &(*m_jsonRoot5)["Send_TCAP_Error_in_TcCont"];
                        isNull = (*cfg)["Value"].isNull();
                        isAVPEnabled = (*cfg)["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            sleep((*cfg)["Value"].asInt());
                            APP_TRACE_DEBUG((" Send Tcap Error in TcCont "));
                            SendTcapErrorInContinue(dlg);
                        }

                        cfg = &(*m_jsonRoot5)["Send_TCAP_Error_in_TcEnd"];
                        isNull = (*cfg)["Value"].isNull();
                        isAVPEnabled = (*cfg)["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            sleep((*cfg)["Value"].asInt());
                            APP_TRACE_DEBUG((" Send Tcap Error in TcEnd "));
                            SendTcapErrorInEnd(dlg);
                        }

                        cfg = &(*m_jsonRoot5)["SimulateFollowOnCases"];
                        isNull = (*cfg)["Enabled"].isNull();
                        isAVPEnabled = (*cfg)["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            simulateFollowOnCases = true;
                        }
                        else
                            simulateFollowOnCases = false;
                    }
                }
                else
                {
                    APP_TRACE_DEBUG((" Restricting Sending ERB and ACR in Tc_Cont to simulate ASR case "));
                }
            }
            catch(...)
            {    
                APP_TRACE_DEBUG((" Encode Failed "));
            }
        }
        else if (op == cap::OP_activityTest) 
        {
            SendActivityResponseInTcCont(dlg);
        }
    }
    else if (dlg->GetDialogueType() == TCPPT_TC_END && cpt->GetComponentType() == TCPPT_TC_INVOKE)
    {
        TCAP_Invoke *ivk = dynamic_cast<TCAP_Invoke *> (cpt);
        ITS_LONG op;
        ivk->GetOperation(op);
        if(op == cap::OP_releaseCall)
        {
            APP_TRACE_DEBUG(("Release Call Recieved in Tc_End, no need to send response"));
        }
        else if(op == cap::OP_releaseSMS)
        {
            APP_TRACE_DEBUG(("Release SMS Recieved in Tc_End, no need to send response"));
        }
        else if(op == cap::OP_connect)
        {
            APP_TRACE_DEBUG(("Connect Received in Tc_End, no need to send response"));
        }
    }


    if(sSN == 146)
    {
        ReleaseInvokeId(dlg->GetDialogueID(), cpt->GetInvokeID());
    }
    return 0;
}

void ITUTcapMsgs::ReleaseInvokeId(ITS_CTXT dialogueId, ITS_OCTET invokeId, bool isOutGoingMsg)
{
    APP_TRACE_DEBUG(("ITUTcapMsgs::ReleaseInvokeId Entry"));

    TCAP_INVOKE_ENTRY *cptCtxt = NULL;
    TCAP_CPT  tcpCpt;
    tcpCpt.u.invoke.invoke_id.len = 3;
    tcpCpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG;
    tcpCpt.u.invoke.invoke_id.data[1] = 1;
    tcpCpt.u.invoke.invoke_id.data[2] = invokeId;

    /* Finding the InvokeContext */
    if(isOutGoingMsg)
    {
        cptCtxt = TCAP_FindInvokeContext_CCITT(dialogueId, &tcpCpt.u.invoke.invoke_id, INV_OUTGOING);
    }
    else
    {
        cptCtxt = TCAP_FindInvokeContext_CCITT(dialogueId, &tcpCpt.u.invoke.invoke_id, INV_INCOMING);
    }

    if(cptCtxt != NULL)
    {
        APP_TRACE_DEBUG(("Freeing the Invoke Context for did : %d and invokeId : %d", dialogueId, invokeId));
        /* FreeInvokeContext */
        TCAP_FreeInvokeContext_CCITT(cptCtxt);
    }
    else
    {
        /* InvokeContext not Found */
        APP_TRACE_ERROR(("Invoke Context Not Found for did : %d and invokeId : %d", dialogueId, invokeId));
    }
    APP_TRACE_DEBUG(("ITUTcapMsgs::ReleaseInvokeId Exit"));
}

void ITUTcapMsgs::BuildAndSendERBandACRinTcEnd(TCAP_Dialogue *dlg)
{   
    bool isNull;
    bool isAVPEnabled;

    Json::Value l_jsonRootcap = parseCapConfig();

    Json::Value* m_jsonRoot3 = &l_jsonRootcap;
    Json::Value* m_jsonRoot4 = &(*m_jsonRoot3)["cap"]["Send_Response_After_Receiving_Only_ACH"];

    Json::Value* cfg = &(*m_jsonRoot4)["Send_Only_ERB_in_TcCont"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        APP_TRACE_DEBUG((" Send ERB in TC_Cont "));
        sendERBandACRinTcContAgain = true;
        SendEventReportBCSMArgInTcCont(dlg);
        sendERBandACRinTcContAgain = false;
    }

    cfg = &(*m_jsonRoot4)["Send_Only_ACR_in_TcCont"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        APP_TRACE_DEBUG((" Send ACR in TC_Cont "));
        sendERBandACRinTcContAgain = true;
        SendApplyChargingReportArgInTcCont(dlg);
        sendERBandACRinTcContAgain = false;
    }
    
    cfg = &(*m_jsonRoot4)["Send_Only_ERB_in_TcEnd"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        APP_TRACE_DEBUG((" Send ERB in TC_End "));
        SendEventReportBCSMArgInTcEnd(dlg);
    }

    cfg = &(*m_jsonRoot4)["Send_Only_ACR_in_TcEnd"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        APP_TRACE_DEBUG((" Send ACR in TC_End "));
        SendApplyChargingReportInTcEnd(dlg);
    }
    
    cfg = &(*m_jsonRoot4)["Send_Only_TCAP_Abort"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        TcapAbortReason = (*cfg)["Reason"].asInt();
        SendTcapAbort(dlg);
    }
    
    cfg = &(*m_jsonRoot4)["Send_Only_TCAP_U_Abort"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        TcapAbortReason = (*cfg)["Reason"].asInt();
        SendTcapUAbort(dlg);
    }

    cfg = &(*m_jsonRoot4)["Send_Both_ERB_ACR_in_TcCont"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        sendERBandACRinTcContAgain = true;
        APP_TRACE_DEBUG((" Send ERB in TC_Cont "));
        SendEventReportBCSMArgInTcCont(dlg);
        APP_TRACE_DEBUG((" Send ACR in TC_Cont "));
        SendApplyChargingReportArgInTcCont(dlg);
        sendERBandACRinTcContAgain = false;
    }
    
    cfg = &(*m_jsonRoot4)["Send_Both_ACR_ERB_in_TcCont"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        sendERBandACRinTcContAgain = true;
        APP_TRACE_DEBUG((" Send ACR in TC_Cont "));
        SendApplyChargingReportArgInTcCont(dlg);
        APP_TRACE_DEBUG((" Send ERB in TC_Cont "));
        SendEventReportBCSMArgInTcCont(dlg);
        sendERBandACRinTcContAgain = false;
    }

    cfg = &(*m_jsonRoot4)["Send_Both_ERB_ACR_in_Single_TcCont"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        APP_TRACE_DEBUG((" Send ERB and ACR in TC_Cont "));
        sendERBandACRinTcContAgain = true;
        SendERBandACRInTcCont(dlg);
        sendERBandACRinTcContAgain = false;
    }

    cfg = &(*m_jsonRoot4)["Send_Both_ACR_ERB_in_Single_TcCont"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        APP_TRACE_DEBUG((" Send ACR and ERB in TC_Cont "));
        sendERBandACRinTcContAgain = true;
        SendERBandACRInTcCont(dlg, true);
        sendERBandACRinTcContAgain = false;
    }

    cfg = &(*m_jsonRoot4)["Send_Both_ERB_ACR_in_TcEnd"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        APP_TRACE_DEBUG((" Send ERB and ACR in TC_End "));
        SendERBandACRInTcEnd(dlg);
    }

    cfg = &(*m_jsonRoot4)["Send_Both_ACR_ERB_in_TcEnd"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        APP_TRACE_DEBUG((" Send ACR and ERB in TC_End "));
        SendERBandACRInTcEnd(dlg, true);
    }

    cfg = &(*m_jsonRoot4)["Send_ERB_in_ReturnResult_in_TcCont"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        APP_TRACE_DEBUG((" Send ERB in Return Result in TcCont "));
        SendERBInReturnResultLastInCont(dlg);
    }

    cfg = &(*m_jsonRoot4)["Send_ERB_in_ReturnResult_in_TcEnd"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        APP_TRACE_DEBUG((" Send ERB in Return Result in TcEnd "));
        SendERBInReturnResultLastInEnd(dlg);
    }

    cfg = &(*m_jsonRoot4)["Send_TCAP_Error_in_TcCont"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        APP_TRACE_DEBUG((" Send Tcap Error in TcCont "));
        SendTcapErrorInContinue(dlg);
    }

    cfg = &(*m_jsonRoot4)["Send_TCAP_Error_in_TcEnd"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        APP_TRACE_DEBUG((" Send Tcap Error in TcEnd "));
        SendTcapErrorInEnd(dlg);
    }
}

void ITUTcapMsgs::BuildAndSendERBandACRinTcCont(TCAP_Dialogue *dlg,bool receivedonlyACH)
{
    bool isNull;
    bool isAVPEnabled;
    bool isERBorACRSent = false;

    Json::Value l_jsonRootcap = parseCapConfig();

    Json::Value* m_jsonRoot3 = &l_jsonRootcap;
    Json::Value* m_jsonRoot4 = NULL;

    if(receivedonlyACH)
        m_jsonRoot4 = &(*m_jsonRoot3)["cap"]["Send_Response_After_Receiving_Only_ACH"];
    else
        m_jsonRoot4 = &(*m_jsonRoot3)["cap"]["Send_Multiple_CAP_ERB_ACR"];

    Json::Value* cfg = &(*m_jsonRoot4)["Send_Only_ERB_in_TcCont"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        APP_TRACE_DEBUG((" Send ERB in TC_Cont "));
        SendEventReportBCSMArgInTcCont(dlg);
    }
    
    cfg = &(*m_jsonRoot4)["Send_Only_ACR_in_TcCont"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        APP_TRACE_DEBUG((" Send ACR in TC_Cont "));
        SendApplyChargingReportArgInTcCont(dlg);
    }
    
    cfg = &(*m_jsonRoot4)["Send_Only_ERB_in_TcEnd"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        APP_TRACE_DEBUG((" Send ERB in TC_End "));
        SendEventReportBCSMArgInTcEnd(dlg);
    }

    cfg = &(*m_jsonRoot4)["Send_Only_ACR_in_TcEnd"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        APP_TRACE_DEBUG((" Send ACR in TC_End "));
        SendApplyChargingReportInTcEnd(dlg);
    }

    cfg = &(*m_jsonRoot4)["Send_Only_TCAP_Abort"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        TcapAbortReason = (*cfg)["Reason"].asInt();
        SendTcapAbort(dlg);
    }
    
    cfg = &(*m_jsonRoot4)["Send_Only_TCAP_U_Abort"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        TcapAbortReason = (*cfg)["Reason"].asInt();
        SendTcapUAbort(dlg);
    }

    cfg = &(*m_jsonRoot4)["Send_Both_ERB_ACR_in_TcCont"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        APP_TRACE_DEBUG((" Send ERB in TC_Cont "));
        SendEventReportBCSMArgInTcCont(dlg);
        APP_TRACE_DEBUG((" Send ACR in TC_Cont "));
        SendApplyChargingReportArgInTcCont(dlg);
    }

    cfg = &(*m_jsonRoot4)["Send_Both_ACR_ERB_in_TcCont"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        APP_TRACE_DEBUG((" Send ACR in TC_Cont "));
        SendApplyChargingReportArgInTcCont(dlg);
        APP_TRACE_DEBUG((" Send ERB in TC_Cont "));
        SendEventReportBCSMArgInTcCont(dlg);
    }

    cfg = &(*m_jsonRoot4)["Send_Both_ERB_ACR_in_Single_TcCont"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        APP_TRACE_DEBUG((" Send ERB and ACR in TC_Cont "));
        sendERBandACRinTcContAgain = true;
        SendERBandACRInTcCont(dlg);
        sendERBandACRinTcContAgain = false;
    }
    
    cfg = &(*m_jsonRoot4)["Send_Both_ACR_ERB_in_Single_TcCont"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        APP_TRACE_DEBUG((" Send ACR and ERB in TC_Cont "));
        sendERBandACRinTcContAgain = true;
        SendERBandACRInTcCont(dlg, true);
        sendERBandACRinTcContAgain = false;
    }

    cfg = &(*m_jsonRoot4)["Send_Both_ERB_ACR_in_TcEnd"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        APP_TRACE_DEBUG((" Send ERB and ACR in TC_End "));
        SendERBandACRInTcEnd(dlg);
    }

    cfg = &(*m_jsonRoot4)["Send_Both_ACR_ERB_in_TcEnd"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        APP_TRACE_DEBUG((" Send ACR and ERB in TC_End "));
        SendERBandACRInTcEnd(dlg, true);
    }

    cfg = &(*m_jsonRoot4)["Send_ERB_in_ReturnResult_in_TcCont"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        APP_TRACE_DEBUG((" Send ERB in Return Result in TcCont "));
        SendERBInReturnResultLastInCont(dlg);
    }

    cfg = &(*m_jsonRoot4)["Send_ERB_in_ReturnResult_in_TcEnd"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        APP_TRACE_DEBUG((" Send ERB in Return Result in TcEnd "));
        SendERBInReturnResultLastInEnd(dlg);
    }

    cfg = &(*m_jsonRoot4)["Send_TCAP_Error_in_TcCont"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        APP_TRACE_DEBUG((" Send Tcap Error in TcCont "));
        SendTcapErrorInContinue(dlg);
    }

    cfg = &(*m_jsonRoot4)["Send_TCAP_Error_in_TcEnd"];
    isNull = (*cfg)["Value"].isNull();
    isAVPEnabled = (*cfg)["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep((*cfg)["Value"].asInt());
        APP_TRACE_DEBUG((" Send Tcap Error in TcEnd "));
        SendTcapErrorInEnd(dlg);
    }
}

int ITUTcapMsgs::SendEventReportSMSArginTcEnd(TCAP_Dialogue *dlg)
{
    TCAP_End tc_end;
    TCAP_Invoke erb;

    ITS_ByteArray app_ctxt = cap::EncodeApplicationContext(cap::CAPV3_cap3_sms_AC);
    tc_end.SetApplicationContext(app_ctxt);

    AsnObject *tempRfsr = BuildEventReportSMSArg();
    Octets *enc2 = 0;
 
    EncodeMsg(tempRfsr, &enc2);
    erb.SetParameter(enc2->GetArray());
    erb.SetClass(1);
    erb.SetInvokeID(++invkId);
    erb.SetOperation(cap::OP_eventReportSMS);

    tc_end.SetDialogueID(dlg->GetDialogueID());

    if (TCAP_Component::Send(ISS7_Stack, &tc_end, &erb) == ITS_SUCCESS)
    {
        if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
        {
            APP_TRACE_DEBUG(("Sent EventReportSMSArg in Tc_End"));
            ReleaseInvokeId(dlg->GetDialogueID(), erb.GetInvokeID(), true);
        }
    }

    delete enc2;
    delete tempRfsr;
    enc2 = 0;
    tempRfsr = 0;

    return 0;
}

int ITUTcapMsgs::SendActivityResponseInTcCont(TCAP_Dialogue *dlg)
{
    TCAP_Continue tc_cont;
    TCAP_Result   retResult;

    ITS_ByteArray app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
    tc_cont.SetApplicationContext(app_ctxt);

    retResult.SetInvokeID(ATInvkId);
    APP_TRACE_DEBUG(("AT SENT for INVOKEID : %d", ATInvkId));

    tc_cont.SetOrigAddr(false, oPC, oSN);
    tc_cont.SetDialogueID(dlg->GetDialogueID());

    if (TCAP_Component::Send(ISS7_Stack, &tc_cont, &retResult) == ITS_SUCCESS) 
    {
        if (TCAP_Dialogue::Send(ISS7_Stack, &tc_cont) == ITS_SUCCESS) 
        {
            APP_TRACE_DEBUG(("Sent returnResultLast for ActivityTEst"));
            ReleaseInvokeId(dlg->GetDialogueID(), retResult.GetInvokeID(), true);
        }
    }
    
    return 0;
}

int ITUTcapMsgs::SendERBInReturnResultLastInCont(TCAP_Dialogue *dlg)
{
    TCAP_Continue tc_cont;
    TCAP_Result   retResult;
    ITS_ByteArray app_ctxt;

    if(IDPVersionBuilt == IDP_V3)
    {
        app_ctxt = cap::EncodeApplicationContext(cap::CAPV3_cap3_sms_AC);
    }
    else if(IDPVersionBuilt == IDP_V2)
    {
        app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
    }
    tc_cont.SetApplicationContext(app_ctxt);

    AsnObject *tempRfsr = NULL;
    if(IDPVersionBuilt == IDP_V3)
        tempRfsr = BuildEventReportBCSMArginTcCont(); 
    else if(IDPVersionBuilt == IDP_V2)
        tempRfsr = BuildEventReportBCSMArginTcContV2();
    else if(IDPVersionBuilt == IDP_V1)
        tempRfsr = BuildEventReportBCSMArginTcContV1();

    Octets *enc2 = NULL;

    EncodeMsg(tempRfsr, &enc2);
    retResult.SetParameter(enc2->GetArray());
 
    retResult.SetInvokeID(ATInvkId);
    retResult.SetOperation(cap::OP_eventReportBCSM);

    tc_cont.SetOrigAddr(false, oPC, oSN);
    tc_cont.SetDialogueID(dlg->GetDialogueID());

    if (TCAP_Component::Send(ISS7_Stack, &tc_cont, &retResult) == ITS_SUCCESS) 
    {
        if (TCAP_Dialogue::Send(ISS7_Stack, &tc_cont) == ITS_SUCCESS) 
        {
            APP_TRACE_DEBUG(("Sent returnResultLast for ERB in TC_CONTINUE"));
            ReleaseInvokeId(dlg->GetDialogueID(), retResult.GetInvokeID(), true);
        }
    }

    if(enc2 != NULL)
    {
        delete enc2;
        enc2 = NULL;
    }
    if(tempRfsr != NULL)
    {
        delete tempRfsr;
        tempRfsr = NULL;
    }
    return 0;
}



int ITUTcapMsgs::SendERBInReturnResultLastInEnd(TCAP_Dialogue *dlg)
{
    TCAP_End tc_end;
    TCAP_Result   retResult;
    ITS_ByteArray app_ctxt;

    if(IDPVersionBuilt == IDP_V3)
    {
        app_ctxt = cap::EncodeApplicationContext(cap::CAPV3_cap3_sms_AC);
    }
    else if(IDPVersionBuilt == IDP_V2)
    {
        app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
    }
    tc_end.SetApplicationContext(app_ctxt);

    AsnObject *tempRfsr = NULL;
    if(IDPVersionBuilt == IDP_V3)
        tempRfsr = BuildEventReportBCSMArginTcCont(); 
    else if(IDPVersionBuilt == IDP_V2)
        tempRfsr = BuildEventReportBCSMArginTcContV2();
    else if(IDPVersionBuilt == IDP_V1)
        tempRfsr = BuildEventReportBCSMArginTcContV1();

    Octets *enc2 = NULL;

    EncodeMsg(tempRfsr, &enc2);
    retResult.SetParameter(enc2->GetArray());
 
    retResult.SetOperation(cap::OP_eventReportBCSM);

    retResult.SetInvokeID(ATInvkId);

    tc_end.SetDialogueID(dlg->GetDialogueID());

    if (TCAP_Component::Send(ISS7_Stack, &tc_end, &retResult) == ITS_SUCCESS) 
    {
        if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
        {
            APP_TRACE_DEBUG(("Sent returnResultLast for ERB in TC_END"));
            ReleaseInvokeId(dlg->GetDialogueID(), retResult.GetInvokeID(), true);
        }
    }

    if(enc2 != NULL)
    {
        delete enc2;
        enc2 = NULL;
    }
    if(tempRfsr != NULL)
    {
        delete tempRfsr;
        tempRfsr = NULL;
    }
    return 0;
}

int ITUTcapMsgs::SendTcapErrorInContinue(TCAP_Dialogue *dlg)
{
    TCAP_Continue tc_cont;
    TCAP_Error terr; 
    ITS_ByteArray app_ctxt;

    if(IDPVersionBuilt == IDP_V3)
    {
        app_ctxt = cap::EncodeApplicationContext(cap::CAPV3_cap3_sms_AC);
    }
    else if(IDPVersionBuilt == IDP_V2)
    {
        app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
    }
    tc_cont.SetApplicationContext(app_ctxt);

    terr.SetInvokeID(ATInvkId);

    terr.SetError(7);

    tc_cont.SetOrigAddr(false, oPC, oSN);
    tc_cont.SetDialogueID(dlg->GetDialogueID());

    if (TCAP_Component::Send(ISS7_Stack, &tc_cont, &terr) == ITS_SUCCESS) 
    {
        if (TCAP_Dialogue::Send(ISS7_Stack, &tc_cont) == ITS_SUCCESS) 
        {
            APP_TRACE_DEBUG(("Sent tcap Error in TC_CONTINUE"));
            ReleaseInvokeId(dlg->GetDialogueID(), terr.GetInvokeID(), true);
        }
    }
    
    return 0;
}

int ITUTcapMsgs::SendTcapErrorInEnd(TCAP_Dialogue *dlg)
{
    TCAP_End tc_end;
    TCAP_Error terr; 
    ITS_ByteArray app_ctxt;

    if(IDPVersionBuilt == IDP_V3)
    {
        app_ctxt = cap::EncodeApplicationContext(cap::CAPV3_cap3_sms_AC);
    }
    else if(IDPVersionBuilt == IDP_V2)
    {
        app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
    }
    tc_end.SetApplicationContext(app_ctxt);
    //retResult.SetOperation(cap::OP_eventReportBCSM);

    terr.SetInvokeID(ATInvkId);
    terr.SetError(7);

    tc_end.SetDialogueID(dlg->GetDialogueID());

    if (TCAP_Component::Send(ISS7_Stack, &tc_end, &terr) == ITS_SUCCESS) 
    {
        if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
        {
            APP_TRACE_DEBUG(("Sent Tcap Error in TC_END"));
            ReleaseInvokeId(dlg->GetDialogueID(), terr.GetInvokeID(), true);
        }
    }
    
    return 0;
}

int ITUTcapMsgs::SendERBandACRInTcCont(TCAP_Dialogue *dlg, bool sendACRFirst)
{
    TCAP_Continue tc_cont;
    TCAP_Invoke erb;
    TCAP_Invoke acr;

    ITS_ByteArray app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
    if(IDPVersionBuilt == IDP_V1)
        app_ctxt = cap::EncodeApplicationContext(cap::CAPV1_gsmSSF_to_gsmSCF_AC);



    tc_cont.SetApplicationContext(app_ctxt);

    AsnObject *tempRfsr = NULL;
    if(IDPVersionBuilt == IDP_V3)
        tempRfsr = BuildEventReportBCSMArginTcCont(); 
    else if(IDPVersionBuilt == IDP_V2)
        tempRfsr = BuildEventReportBCSMArginTcContV2();
    else if(IDPVersionBuilt == IDP_V1)
        tempRfsr = BuildEventReportBCSMArginTcContV1();

    Octets *enc2 = 0;

    EncodeMsg(tempRfsr, &enc2);
    erb.SetParameter(enc2->GetArray());
    erb.SetClass(1);
    erb.SetInvokeID(++invkId);
    erb.SetOperation(cap::OP_eventReportBCSM);

    tc_cont.SetOrigAddr(false, oPC, oSN);
    tc_cont.SetDialogueID(dlg->GetDialogueID());

    AsnObject *tempRfsr2 = NULL;
    if(IDPVersionBuilt == IDP_V3)
        tempRfsr2 = BuildApplyChargingReportinTcCont(); 
    else
        tempRfsr2 = BuildApplyChargingReportinTcContV2();
    Octets *enc3 = 0;

    EncodeMsg(tempRfsr2, &enc3);
    acr.SetParameter(enc3->GetArray());
    acr.SetClass(1);
    acr.SetInvokeID(++invkId);
    acr.SetOperation(cap::OP_applyChargingReport);

    if(sendACRFirst)
    {
        if (TCAP_Component::Send(ISS7_Stack, &tc_cont, &acr) == ITS_SUCCESS) 
        {
            if (TCAP_Component::Send(ISS7_Stack, &tc_cont, &erb) == ITS_SUCCESS)
            {
                if (TCAP_Dialogue::Send(ISS7_Stack, &tc_cont) == ITS_SUCCESS) 
                {
                    APP_TRACE_DEBUG(("Sent ApplyChargingReportArg & EventReportBCSMArg in a single dialogue"));
                    ReleaseInvokeId(dlg->GetDialogueID(), acr.GetInvokeID(), true);
                    ReleaseInvokeId(dlg->GetDialogueID(), erb.GetInvokeID(), true);
                }
            }
        }
    }
    else
    {
        if (TCAP_Component::Send(ISS7_Stack, &tc_cont, &erb) == ITS_SUCCESS) 
        {
            if (TCAP_Component::Send(ISS7_Stack, &tc_cont, &acr) == ITS_SUCCESS)
            {
                if (TCAP_Dialogue::Send(ISS7_Stack, &tc_cont) == ITS_SUCCESS) 
                {
                    APP_TRACE_DEBUG(("Sent EventReportBCSMArg & ApplyChargingReportArg in a single dialogue"));
                    ReleaseInvokeId(dlg->GetDialogueID(), acr.GetInvokeID(), true);
                    ReleaseInvokeId(dlg->GetDialogueID(), erb.GetInvokeID(), true);
                }
            }
        }
    }
    
    delete enc2;
    delete enc3;
    delete tempRfsr;
    delete tempRfsr2;
    enc2 = 0;
    enc3 = 0;
    tempRfsr = 0;
    tempRfsr2 = 0;

    return 0;
}

int ITUTcapMsgs::SendERBandACRInTcEnd(TCAP_Dialogue *dlg, bool sendACRFirst)
{
    TCAP_End tc_end;
    TCAP_Invoke erb;
    TCAP_Invoke acr;

    ITS_ByteArray app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
    if(IDPVersionBuilt == IDP_V1)
        app_ctxt = cap::EncodeApplicationContext(cap::CAPV1_gsmSSF_to_gsmSCF_AC);



    tc_end.SetApplicationContext(app_ctxt);

    AsnObject *tempRfsr = NULL;
    if(IDPVersionBuilt == IDP_V3)
        tempRfsr = BuildEventReportBCSMArginTcEnd(); 
    else if(IDPVersionBuilt == IDP_V2)
        tempRfsr = BuildEventReportBCSMArginTcEndV2();
    else if(IDPVersionBuilt == IDP_V1)
        tempRfsr = BuildEventReportBCSMArginTcEndV1();

    Octets *enc2 = 0;

    EncodeMsg(tempRfsr, &enc2);
    erb.SetParameter(enc2->GetArray());
    erb.SetClass(1);
    erb.SetInvokeID(++invkId);
    erb.SetOperation(cap::OP_eventReportBCSM);

    tc_end.SetDialogueID(dlg->GetDialogueID());

    AsnObject *tempRfsr2 = NULL;
    if(IDPVersionBuilt == IDP_V3)
        tempRfsr2 = BuildApplyChargingReportinTcEnd(); 
    else
        tempRfsr2 = BuildApplyChargingReportinTcEndV2();
    Octets *enc3 = 0;

    EncodeMsg(tempRfsr2, &enc3);
    acr.SetParameter(enc3->GetArray());
    acr.SetClass(1);
    acr.SetInvokeID(++invkId);
    acr.SetOperation(cap::OP_applyChargingReport);
    if(sendACRFirst)
    {
        if (TCAP_Component::Send(ISS7_Stack, &tc_end, &acr) == ITS_SUCCESS) 
        {
            if (TCAP_Component::Send(ISS7_Stack, &tc_end, &erb) == ITS_SUCCESS)
            {
                if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                {
                    APP_TRACE_DEBUG(("Sent ApplyChargingReportArg & EventReportBCSMArg in a single dialogue"));
                    ReleaseInvokeId(dlg->GetDialogueID(), acr.GetInvokeID(), true);
                    ReleaseInvokeId(dlg->GetDialogueID(), erb.GetInvokeID(), true);
                }
            }
        }
    }
    else
    {
        if (TCAP_Component::Send(ISS7_Stack, &tc_end, &erb) == ITS_SUCCESS) 
        {
            if (TCAP_Component::Send(ISS7_Stack, &tc_end, &acr) == ITS_SUCCESS)
            {
                if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
                {
                    APP_TRACE_DEBUG(("Sent EventReportBCSMArg & ApplyChargingReportArg in a single dialogue"));
                    ReleaseInvokeId(dlg->GetDialogueID(), acr.GetInvokeID(), true);
                    ReleaseInvokeId(dlg->GetDialogueID(), erb.GetInvokeID(), true);
                }
            }
        }
    }
    
    delete enc2;
    delete enc3;
    delete tempRfsr;
    delete tempRfsr2;
    enc2 = 0;
    enc3 = 0;
    tempRfsr = 0;
    tempRfsr2 = 0;

    return 0;
}

int ITUTcapMsgs::BuildUDTSMessage(TCAP_Dialogue *dlg)
{
    /* build a message */
    SCCP_UnitDataService uds;
    
    /*return cause */
    SCCP_ReturnCause rc(SCCP_RET_ERR_IN_LOCAL_PROCESS);
    uds.AddIE(&rc);
    
    /* Called Party Address */                  //len=3 min
    SCCP_CalledPartyAddr called_pa;
    called_pa = cdp_itu;

    #if 0
    called_pa.SetPointCode(0);                  //1=address contains subsystem number
    called_pa.SetPointCode(cdp_itu.
    called_pa.SetSSN(REMOTE_SSN);          
    called_pa.SetRouteByPCSSN(true); 
    called_pa.SetInternationalRouting(false);   //set to national by default
    #endif
    
    uds.AddIE(&called_pa);
    
    /* Calling Party Address */                 //len=2 min
    SCCP_CallingPartyAddr calling_pa;
    calling_pa = cpa_itu;
    #if 0 
    calling_pa.SetPointCode(0);
    calling_pa.SetSSN(LOCAL_SSN);
    calling_pa.SetRouteByPCSSN(true);            //octet 1 bit 7
    calling_pa.SetInternationalRouting(false);   //set to national
    #endif
    
    uds.AddIE(&calling_pa);        
    
    /* Data */                                  //2-254
    SCCP_UserData ud;   
    //const std::vector<byte> data = enc->GetArray();

    const std::vector<byte> data = {0x65, 0x81, 0xb3, 0x48, 0x04, 0xff, 0xff,
                                    0xff, 0xfe, 0x49, 0x04, 0xff, 0xff, 0xff, 0xfe, 
                                    0x6b, 0x26, 0x28, 0x24, 0x06, 0x07, 0x00, 0x11,
                                    0x86, 0x05, 0x01, 0x01, 0x01, 0xa0, 0x19, 0x61,
                                    0x17, 0xa1, 0x09, 0x06, 0x07, 0x04, 0x00, 0x00,
                                    0x01, 0x00, 0x32, 0x01, 0xa2, 0x03, 0x02, 0x01, 
                                    0x00, 0xa3, 0x05, 0xa1, 0x03, 0x02, 0x01, 0x00,
                                    0x6c, 0x7d, 0xa1, 0x5d, 0x02, 0x01, 0x2c, 0x02, 
                                    0x01, 0x17, 0x30, 0x55, 0xa0, 0x53, 0x30, 0x0b, 
                                    0x80, 0x01, 0x05, 0x81, 0x01, 0x00, 0xa2, 0x03,
                                    0x80, 0x01, 0x02, 0x30, 0x10, 0x80, 0x01, 0x06, 
                                    0x81, 0x01, 0x00, 0xa2, 0x03, 0x80, 0x01, 0x02, 
                                    0xbe, 0x03, 0x81, 0x01, 0x1e, 0x30, 0x0b, 0x80, 
                                    0x01, 0x07, 0x81, 0x01, 0x01, 0xa2, 0x03, 0x80, 
                                    0x01, 0x02, 0x30, 0x0b, 0x80, 0x01, 0x09, 0x81,
                                    0x01, 0x01, 0xa2, 0x03, 0x80, 0x01, 0x01, 0x30, 
                                    0x0b, 0x80, 0x01, 0x09, 0x81, 0x01, 0x00, 0xa2, 
                                    0x03, 0x80, 0x01, 0x02, 0x30, 0x0b, 0x80, 0x01,
                                    0x04, 0x81, 0x01, 0x00, 0xa2, 0x03, 0x80, 0x01, 
                                    0x02, 0xa1, 0x14, 0x02, 0x01, 0x2d, 0x02, 0x01,
                                    0x23, 0x30, 0x0c, 0x80, 0x05, 0xa0, 0x03, 0x80, 
                                    0x01, 0x64, 0xa2, 0x03, 0x80, 0x01, 0x01, 0xa1,
                                    0x06, 0x02, 0x01, 0x2e, 0x02, 0x01, 0x1f}; 
    //const std::vector<byte> data = {0x00};

    /*fill data */
    //data = ptrData;
    
    #if 0
    data[0] = 1;
    data[1] = 2;
    data[2] = 3;
    data[3] = 4;
    data[4] = 5;
    #endif

    ud.SetUserData(data);
    
    uds.AddIE(&ud);
    
    /* Send the message  */
    ITS_HDR hdr;
    hdr.type = transportInstance;     
    hdr.context.ssn = 146;
    hdr.context.dialogue_id = dlg->GetDialogueID();
    cout << "Send results in: "
         << SCCP_MessageClass::Send(ISS7_Stack, &hdr, &uds)
         << endl;
    return 0;
}

int ITUTcapMsgs::SendCancelLocationResult(ITS_UINT dlgId,int invoke_id)
{
    APP_TRACE_DEBUG(("Entered SEND CANCEL LOCATION RESULT method"));
    TCAP_Continue tc_cont;
    TCAP_End      tc_end;
    TCAP_Invoke   isdr;
    TCAP_Invoke   erbr;
    TCAP_Result   ugla;
    TCAP_Result   saia;
    TCAP_Result   rfsr;
    TCAP_Result   puMsa;
    int invkId;
    TCAP_Unidirectional tc_uni;
    int errVal = 0;
    TCAP_Error *tcapErr = NULL;
    TCAP_Component* cpt = NULL;

    bool isNull1,isAVPEnabled1;
    //int TcapAbortReason = 0;


    Json::Value l_jsonRoot = parseMapConfig();
    Json::Value* m_jsonRoot = &l_jsonRoot;
    Json::Value* m_jsonRoot1= &(*m_jsonRoot)["map_v13"]; 
    Json::Value* cfg1 = &(*m_jsonRoot1)["Send_TCAP_abort_during_Cancel_loc_sleep"];
    
    isNull1 = (*cfg1)["Value"].isNull();
    isAVPEnabled1 = (*cfg1)["Enabled"].asBool();
    if(!isNull1 && isAVPEnabled1)
    {
        APP_TRACE_DEBUG(("Gonna send TCAP abort"));
        sleep((*cfg1)["Value"].asInt());
        TcapAbortReason = (*cfg1)["Reason"].asInt();
        SendTcapAbortMap(dlgId);
        APP_TRACE_DEBUG(("Already sent TCAP abort"));
    }

    else
    {

        ITS_ByteArray app_ctxt = map_common::EncodeApplicationContext(map_common::locationCancellationContext_v3);
        tc_end.SetApplicationContext(app_ctxt);

        AsnObject *tempRfsr = BuildMapMsg(MAP_V13_CANCEL_LOCATION_RES);
        Octets *enc2 = 0;

        //rfsr.SetInvokeID(cpt->GetInvokeID());
        rfsr.SetInvokeID(invoke_id);

        APP_TRACE_DEBUG(("Execution in progress- encoding in progress"));
        EncodeMsg(tempRfsr, &enc2);

        rfsr.SetParameter(enc2->GetArray());
        rfsr.SetOperation(map_common::OP_cancelLocation);

        //tc_end.SetDialogueID(dlg->GetDialogueID());
        tc_end.SetDialogueID(dlgId);

        APP_TRACE_DEBUG(("Execution in progress-Set the dialogue in TC_end"));

        //if (TCAP_Component::Send(ISS7_Stack, &tc_end, &rfsr) == ITS_SUCCESS) 
        if (TCAP_Component::Send(ISS7_Stack, &tc_end, &rfsr) == ITS_SUCCESS) 
        {

            APP_TRACE_DEBUG(("Execution in progress - Entered IF statement to send the TCAP component"));
            if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
            {
                APP_TRACE_DEBUG(("Sent CancelLocationRes v3"));
            }
        }

        delete enc2;
        delete tempRfsr;
        enc2 = 0;
        tempRfsr = 0;
    }
}

int ITUTcapMsgs::SendInsertSubscriberDataResult(ITS_UINT dlgId)
{
    APP_TRACE_DEBUG(("INSERT SUBSCRIBER DATA RESULT send in progress"));

    TCAP_Continue tc_cont;
    TCAP_End      tc_end;
    TCAP_Invoke   isdr;
    TCAP_Invoke   erbr;
    TCAP_Result   ugla;
    TCAP_Result   saia;
    TCAP_Result   rfsr;
    TCAP_Result   puMsa;
    int invkId;
    TCAP_Unidirectional tc_uni;
    int errVal = 0;
    TCAP_Error *tcapErr = NULL;
    TCAP_Component* cpt = NULL;


    ITS_ByteArray app_ctxt = map_common::EncodeApplicationContext(map_common::subscriberDataMngtContext_v3);
    tc_end.SetApplicationContext(app_ctxt);

    AsnObject *tempRfsr = BuildMapMsg(MAP_V13_INSERT_SUB_DATA_RES);
    Octets *enc2 = 0;

    //rfsr.SetInvokeID(cpt->GetInvokeID());

    EncodeMsg(tempRfsr, &enc2);

    rfsr.SetParameter(enc2->GetArray());
    rfsr.SetOperation(map_common::OP_insertSubscriberData);

    tc_end.SetDialogueID(dlgId);

    if (TCAP_Component::Send(ISS7_Stack, &tc_end, &rfsr) == ITS_SUCCESS) 
    {
        if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
        {
            APP_TRACE_DEBUG(("Sent InsertSubscriberDataRes v3"));
        }
    }

    delete enc2;
    delete tempRfsr;
    enc2 = 0;
    tempRfsr = 0;
}

int ITUTcapMsgs::SendDeleteSubscriberDataResult(ITS_UINT dlgId, int invoke_id)
{
    APP_TRACE_DEBUG(("DELETE  SUBSCRIBER DATA RESULT send in progress"));

    TCAP_Continue tc_cont;
    TCAP_End      tc_end;
    TCAP_Invoke   isdr;
    TCAP_Invoke   erbr;
    TCAP_Result   ugla;
    TCAP_Result   saia;
    TCAP_Result   rfsr;
    TCAP_Result   puMsa;
    int invkId;
    TCAP_Unidirectional tc_uni;
    int errVal = 0;
    TCAP_Error *tcapErr = NULL;
    TCAP_Component* cpt = NULL;

    ITS_ByteArray  app_ctxt = map_common::EncodeApplicationContext(map_common::subscriberDataMngtContext_v3);
    tc_end.SetApplicationContext(app_ctxt);

    AsnObject *tempRfsr = BuildMapMsg(MAP_V13_DELETE_SUB_DATA_RES);
    Octets *enc2 = 0;

    //rfsr.SetInvokeID(cpt->GetInvokeID());
    rfsr.SetInvokeID(invoke_id);  
    EncodeMsg(tempRfsr, &enc2);

    rfsr.SetParameter(enc2->GetArray());
    rfsr.SetOperation(map_common::OP_deleteSubscriberData);

    tc_end.SetDialogueID(dlgId);

    if (TCAP_Component::Send(ISS7_Stack, &tc_end, &rfsr) == ITS_SUCCESS)
    {
        if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS)
        {
            APP_TRACE_DEBUG(("Sent DeleteSubscriberDataRes v3"));
        }
    }
    delete enc2;
    delete tempRfsr;
    enc2 = 0;
    tempRfsr = 0;
}


int ITUTcapMsgs::SendApplyChargingReportArgInTcCont(TCAP_Dialogue *dlg)
{
    TCAP_Continue tc_cont;
    TCAP_Invoke   acr;

    ITS_ByteArray app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
    if(IDPVersionBuilt == IDP_V1)
        app_ctxt = cap::EncodeApplicationContext(cap::CAPV1_gsmSSF_to_gsmSCF_AC);

    tc_cont.SetApplicationContext(app_ctxt);

    AsnObject *tempRfsr = NULL;
    if(IDPVersionBuilt == IDP_V3)
        tempRfsr = BuildApplyChargingReportinTcCont(); 
    else
        tempRfsr = BuildApplyChargingReportinTcContV2();

    its::Octets *enc = 0;

    EncodeMsg(tempRfsr, &enc);
    acr.SetParameter(enc->GetArray());
    acr.SetClass(1);
    acr.SetInvokeID(++invkId);
    acr.SetOperation(cap::OP_applyChargingReport);

    tc_cont.SetOrigAddr(false, oPC, oSN);
    tc_cont.SetDialogueID(dlg->GetDialogueID());
    if (TCAP_Component::Send(ISS7_Stack, &tc_cont, &acr) == ITS_SUCCESS) 
    {
        if (TCAP_Dialogue::Send(ISS7_Stack, &tc_cont) == ITS_SUCCESS) 
        {
            APP_TRACE_DEBUG(("Sent ApplyChargingReportArg"));
            ReleaseInvokeId(dlg->GetDialogueID(), acr.GetInvokeID(), true);
        }
    }
       
    delete enc;
    enc = 0;
    delete tempRfsr;
    tempRfsr = 0;
    
    return 0;
}

int ITUTcapMsgs::SendApplyChargingReportInTcEnd(TCAP_Dialogue *dlg)
{
    TCAP_End tc_end;
    TCAP_Invoke acr;

    ITS_ByteArray app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
    if(IDPVersionBuilt == IDP_V1)
        app_ctxt = cap::EncodeApplicationContext(cap::CAPV1_gsmSSF_to_gsmSCF_AC);


    tc_end.SetApplicationContext(app_ctxt);

    tc_end.SetDialogueID(dlg->GetDialogueID());

    AsnObject *tempRfsr = NULL;
    if(IDPVersionBuilt == IDP_V3)
        tempRfsr = BuildApplyChargingReportinTcEnd(); 
    else if(IDPVersionBuilt == IDP_V2)
        tempRfsr = BuildApplyChargingReportinTcEndV2();

    Octets *enc = 0;

    EncodeMsg(tempRfsr, &enc);
    acr.SetParameter(enc->GetArray());
    acr.SetClass(1);
    acr.SetInvokeID(++invkId);
    acr.SetOperation(cap::OP_applyChargingReport);
    if (TCAP_Component::Send(ISS7_Stack, &tc_end, &acr) == ITS_SUCCESS)
    {
        if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
        {
            APP_TRACE_DEBUG(("Sent ApplyChargingReportArg in Tc_End"));
            ReleaseInvokeId(dlg->GetDialogueID(), acr.GetInvokeID(), true);
        }
    }

    delete enc;
    delete tempRfsr;
    enc = 0;
    tempRfsr = 0;
    
    return 0;
}

int ITUTcapMsgs::SendEventReportBCSMArgInTcEnd(TCAP_Dialogue *dlg)
{
    TCAP_End tc_end;
    TCAP_Invoke erb;

    ITS_ByteArray app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
    if(IDPVersionBuilt == IDP_V1)
        app_ctxt = cap::EncodeApplicationContext(cap::CAPV1_gsmSSF_to_gsmSCF_AC);


    tc_end.SetApplicationContext(app_ctxt);

    AsnObject *tempRfsr = NULL;
    if(IDPVersionBuilt == IDP_V3)
        tempRfsr = BuildEventReportBCSMArginTcEnd(); 
    else if(IDPVersionBuilt == IDP_V2)
        tempRfsr = BuildEventReportBCSMArginTcEndV2();
    else if(IDPVersionBuilt == IDP_V1)
        tempRfsr = BuildEventReportBCSMArginTcEndV1();

    Octets *enc2 = 0;

    EncodeMsg(tempRfsr, &enc2);
    erb.SetParameter(enc2->GetArray());
    erb.SetClass(1);
    erb.SetInvokeID(++invkId);

    erb.SetOperation(cap::OP_eventReportBCSM);

    tc_end.SetDialogueID(dlg->GetDialogueID());

    if (TCAP_Component::Send(ISS7_Stack, &tc_end, &erb) == ITS_SUCCESS) 
    {
            if (TCAP_Dialogue::Send(ISS7_Stack, &tc_end) == ITS_SUCCESS) 
            {
                APP_TRACE_DEBUG(("Sent EventReportBCSMArg"));
                ReleaseInvokeId(dlg->GetDialogueID(), erb.GetInvokeID(), true);
            }
    }
    
    delete enc2;
    delete tempRfsr;
    enc2 = 0;
    tempRfsr = 0;

    return 0;

}

int ITUTcapMsgs::SendEventReportBCSMArgInTcCont(TCAP_Dialogue *dlg)
{
    TCAP_Continue tc_cont;
    TCAP_Invoke   erbr;

    ITS_ByteArray app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
    if(IDPVersionBuilt == IDP_V1)
        app_ctxt = cap::EncodeApplicationContext(cap::CAPV1_gsmSSF_to_gsmSCF_AC);

    tc_cont.SetApplicationContext(app_ctxt);

    AsnObject *tempRfsr = NULL;
    if(IDPVersionBuilt == IDP_V3)
        tempRfsr = BuildEventReportBCSMArginTcCont(); 
    else if(IDPVersionBuilt == IDP_V2)
        tempRfsr = BuildEventReportBCSMArginTcContV2();
    else if(IDPVersionBuilt == IDP_V1)
        tempRfsr = BuildEventReportBCSMArginTcContV1();

    Octets *enc = 0;

    EncodeMsg(tempRfsr, &enc);
    erbr.SetParameter(enc->GetArray());
    erbr.SetClass(1);
    erbr.SetInvokeID(++invkId);
    erbr.SetOperation(cap::OP_eventReportBCSM);

    tc_cont.SetOrigAddr(false, oPC, oSN);
    tc_cont.SetDialogueID(dlg->GetDialogueID());
    if (TCAP_Component::Send(ISS7_Stack, &tc_cont, &erbr) == ITS_SUCCESS) 
    {
        if (TCAP_Dialogue::Send(ISS7_Stack, &tc_cont) == ITS_SUCCESS) 
        {
            APP_TRACE_DEBUG(("Sent EventReportBCSMArg"));
            ReleaseInvokeId(dlg->GetDialogueID(), erbr.GetInvokeID(), true);
        }
    }

    delete enc;
    enc = 0;
    delete tempRfsr;
    tempRfsr = 0;

    return 0;
}

int ITUTcapMsgs::SendTcapUAbort(TCAP_Dialogue *dlg)
{
    TCAP_Abort     abortDlg(true);

    if(TcapAbortReason)
    {
        abortDlg.SetAbortReason(TcapAbortReason);
        TcapAbortReason = 0;
    }
    else
        abortDlg.SetAbortReason(TCPABT_REASON_UNREC_TRANS_ID);

    abortDlg.SetApplicationContext(itstest::AC_NAME, 7);
    abortDlg.SetDialogueID(dlg->GetDialogueID());

    if (TCAP_Dialogue::Send(ISS7_Stack, &abortDlg) == ITS_SUCCESS) 
    {
        APP_TRACE_DEBUG(("Sent Tcap U_Abort Dialogue"));
    }

    return 0;
}

int
ITUTcapMsgs::SendTcapAbort(TCAP_Dialogue *dlg)
{
    TCAP_Abort     abortDlg(false);
    int result = 0;
    int choice = 0;

    //abortDlg.ptype = TCPPT_TC_P_ABORT;

    /* Selected user defined abort reason */
    //abortDlg.u.abort.abort_reason = TCPABT_REASON_UNREC_TRANS_ID;
    //abortDlg.SetOrigAddr(false, oPC, oSN);
    if(TcapAbortReason)
    {
        abortDlg.SetAbortReason(TcapAbortReason);
        TcapAbortReason = 0;
    }
    else
        abortDlg.SetAbortReason(TCPABT_REASON_UNREC_TRANS_ID);

    abortDlg.SetApplicationContext(itstest::AC_NAME, 7);
    //cout << "localDID" <<  localDid << endl;
    abortDlg.SetDialogueID(dlg->GetDialogueID());

    //dlg = &abortDlg;

    if (TCAP_Dialogue::Send(ISS7_Stack, &abortDlg) == ITS_SUCCESS) 
    {
        APP_TRACE_DEBUG(("Sent Abort Dialogue"));
    }

    //delete enc;
    //enc = 0;
    //delete tempRfsr;
    //tempRfsr = 0;

    return 0;
}

int ITUTcapMsgs::SendTcapAbortMap(ITS_UINT dlgId)
{

    APP_TRACE_DEBUG(("Entered TCAP_ABORT method"));
    TCAP_Abort     abortDlg(false);
    int result = 0;
    int choice = 0;
    //abortDlg.u.abort.abort_reason = TCPABT_REASON_UNREC_TRANS_ID;
    //abortDlg.SetOrigAddr(false, oPC, oSN);
    if(TcapAbortReason)
    {
        APP_TRACE_DEBUG(("Triggering IF part since TCAP abort found"));
        abortDlg.SetAbortReason(TcapAbortReason);
        TcapAbortReason = 0;
    }
    else
        abortDlg.SetAbortReason(TCPABT_REASON_UNREC_TRANS_ID);

    abortDlg.SetApplicationContext(itstest::AC_NAME, 7);
    //cout << "localDID" <<  localDid << endl;
    //abortDlg.SetDialogueID(dlg->GetDialogueID());
    abortDlg.SetDialogueID(dlgId);
    //dlg = &abortDlg;

    if (TCAP_Dialogue::Send(ISS7_Stack, &abortDlg) == ITS_SUCCESS) 
    {
        APP_TRACE_DEBUG(("Sent Abort Dialogue"));
    }

    //delete enc;
    //enc = 0;
    //delete tempRfsr;
    //tempRfsr = 0;

    return 0;
}

void ITUTcapMsgs::StartTimerHandling(ITS_UINT dlgId, ETimerType timerType, int32_t sleep_value)
{


    APP_TRACE_DEBUG(("Entered Start Timer handling method "));
    STimerContext sTimerCtxt;
    sTimerCtxt.m_eKeyType = EKeyType::DIALOG_ID;
    sTimerCtxt.m_uiDlgId = dlgId;
    sTimerCtxt.m_eTimerType = timerType;

    AppTimer timerObj;
#if 0
    unsigned int uiTimeout = 0;
    if(sTimerCtxt.m_eTimerType == ETimerType::ALLOCATED_GSU_TIMER)
    {
        uiTimeout = GSUTimer;
    }
    else if(sTimerCtxt.m_eTimerType == ETimerType::FOLLOW_ON_IVR_TIMER)
    {
        uiTimeout = IVR_CALL_TIMER; 
    }
#endif
    unsigned int timerId;
    timerId = timerObj.StartTimer(sTimerCtxt.m_eTimerType,sTimerCtxt,sleep_value);

    STimerInfo timerInfo;
    timerInfo.m_eTimerType = sTimerCtxt.m_eTimerType;
    timerInfo.m_uiDuration = sleep_value;
    timerInfo.m_uiTimerId = timerId;

    struct timeval tv;
    gettimeofday(&tv, 0);
    timerInfo.m_tStartTime = tv.tv_sec;   
   
    APP_TRACE_DEBUG(("Timer started"));
    /*APP_TRACE_DEBUG(("Started TimerType : %s, TimerId %d for dialogId %ud for time %d",
            GetStrTimerType(sTimerCtxt.m_eTimerType).c_str(),
            timerInfo.m_uiTimerId,
            sTimerCtxt.m_uiDlgId,
            TimerValue));
*/
}

/*std::string ITUTcapMsgs::GetStrTimerType(ETimerType& timerType)
{
    std::string strTimerType("");
    APP_TRACE_DEBUG(("ITUTcapMsgs::GetStrTimerType Entry"));
    switch(timerType)
    {
        case ALLOCATED_GSU_TIMER : 
            strTimerType = "ALLOCATED_GSU_TIMER";
            break;
        default :
            strTimerType = "";
            break;
    }
    APP_TRACE_DEBUG(("ITUTcapMsgs::GetStrTimerType Exit"));
    return strTimerType;
}*/


void ITUTcapMsgs::HandleTimeout(STimerContext& timerCtxt)
{
    APP_TRACE_DEBUG(("Entered Handle Time Out method"));
    gMtx.lock();
    std::unordered_map<ITS_CTXT, CallContext>::iterator itr = gCallFlowState.find(timerCtxt.m_uiDlgId);
    int invoke_id = itr->second.ivkId;
    switch(timerCtxt.m_eKeyType)
    {
        case DIALOG_ID : 
            {
                if(itr->second.currentState == CANCEL_LOC_REC)
                {
                    APP_TRACE_DEBUG(("Entered Cancel Location condition"));
                    SendCancelLocationResult(timerCtxt.m_uiDlgId,invoke_id);
                }
                else if(itr->second.currentState == INSERT_SUB_REC)
                {
                    APP_TRACE_DEBUG(("Entered Insert Subscriber Data condition")); 
                    SendInsertSubscriberDataResult(timerCtxt.m_uiDlgId);
                }
                else if(itr->second.currentState == DELETE_SUB_REC)
                {
                    APP_TRACE_DEBUG(("Entered Delete subscriber condition"));
                    SendDeleteSubscriberDataResult(timerCtxt.m_uiDlgId,invoke_id);
                }
                break;
            }

        default:
            {
                APP_TRACE_DEBUG(("ITUTcapMsgs:: HandleTimeout() TimerData keytype set to : %d.",timerCtxt.m_eKeyType));
                break;
            }
    }
}

void ITUTcapMsgs::SendResponseOnTimeOutCancelLocation(ITS_CTXT dlgId,int sleep_value,int get_invokeid)
{
    struct CallContext call_info;
    call_info.currentState = CANCEL_LOC_REC;
    call_info.ivkId = get_invokeid;
    APP_TRACE_DEBUG(("Invoke ID set for call_info.invkID %d ", call_info.ivkId)); 
    std::pair<ITS_CTXT,CallContext> idpair(dlgId,call_info); 
    gMtx.lock();
    gCallFlowState.insert(idpair);
    gMtx.unlock();

    StartTimerHandling(dlgId, ETimerType::ALLOCATED_GSU_TIMER, sleep_value);
}


void ITUTcapMsgs::SendResponseOnTimeOutInsertSubscriberData(ITS_CTXT dlgId,int sleep_value,int get_invokeid)
{
    struct CallContext call_info;
    call_info.currentState = INSERT_SUB_REC;
    call_info.ivkId = get_invokeid; 
    std::pair<ITS_CTXT,CallContext> idpair(dlgId,call_info); 
    gMtx.lock();
    gCallFlowState.insert(idpair);
    gMtx.unlock();

    StartTimerHandling(dlgId, ETimerType::ALLOCATED_GSU_TIMER, sleep_value);
}


void ITUTcapMsgs::SendResponseOnTimeOutDeleteSubscriberData(ITS_CTXT dlgId,int sleep_value,int get_invokeid)
{
    struct CallContext call_info;
    call_info.currentState = DELETE_SUB_REC;
    call_info.ivkId = get_invokeid; 
    std::pair<ITS_CTXT,CallContext> idpair(dlgId,call_info); 
    gMtx.lock();
    gCallFlowState.insert(idpair);
    gMtx.unlock();

    StartTimerHandling(dlgId, ETimerType::ALLOCATED_GSU_TIMER, sleep_value);
}

int
ITUTcapMsgs::SendResponse(ITS_HANDLE hdl, ITS_USHORT dlgid, ITS_INT ivkid)
{
   int            ret = 0;
   TCAP_Continue  cont;
   TCAP_End       end;
   TCAP_Invoke    ivk;
   TCAP_Result    resl;

   TCAP_Dialogue*  dlg = NULL;
   TCAP_Component* cpt = NULL;

   srand(time(NULL));

   APP_TRACE_DEBUG(("DialogueId = %d InvokeId = %d ",dlgid, ivkid));

   if(1) /*rand() % 17 <= 13)*/
   {
      ret = 1; /*Tell the application to call DeleteApplicationRoute */

      end.SetDialogueID(dlgid);
      resl.SetInvokeID(ivkid);
      resl.SetOperation(2); 
      resl.SetParameter(itstest::LocationArg, LOC_ARG_LEN);
      cpt = &resl;
      dlg = &end;
   }
   else
   {
      ret = 2;
      cont.SetDialogueID(dlgid);
      cont.SetOrigAddr(cpa_itu);
      //cont.SetOPC(itstest::opc);
      cont.SetOPC(oPC);
      ivk.SetInvokeID(GetInvokeID());
      ivk.SetTimeOut(10);
      ivk.SetClass(2);
      ivk.SetOperation(2);

      ivk.SetParameter(itstest::LocationArg, LOC_ARG_LEN);

     cpt = &ivk;
      dlg = &cont;
   }

   APP_TRACE_DEBUG(("SendResponse: DialogueId = %02x , DialogueType = %02x", dlgid, 
           dlg->GetDialogueType()));

   APP_TRACE_DEBUG(("SendResponse: InvokeId = %02x", cpt->GetInvokeID()));

   if(TCAP_Component::Send(ISS7_Stack, dlg, cpt) == ITS_SUCCESS)
   {
       if(TCAP_Dialogue::Send(ISS7_Stack, dlg) == ITS_SUCCESS)
       {
           stats.UpdateSendStats(dlg->GetDialogueType(), false);
           stats.UpdateSendStats(cpt->GetComponentType(), true);

           APP_TRACE_DEBUG(("DlgType = %02x  Dialogue ID = %02x ", 
                             dlg->GetDialogueType(), dlg->GetDialogueID()));
           APP_TRACE_DEBUG(("Dialogue/Component send Success:"));
       }
   }

   return ret;
}

#include "app_map_msgs.cpp"

/*****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      octets - used to store the encoded value of the inputted mesg .
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
void EncodeMsg(AsnObject* p, Octets** octets)
{
    cout << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Printing ASN value before encoding..." << endl;

    if (p == NULL)
    {
        return;
    }

    cout << endl << *p << endl;

    Octets* tmpOctets;

    try
    {
        tmpOctets = p->Encode();
    }
    catch (AsnEncodeError& exc)
    {
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Exception during encoding phase..." << endl;
        cout << exc.GetDescription() << endl;
        cout << "Exit test..." << endl;
    }

    cout << endl;
    cout << "--------------------------------------------------" << endl;
    *octets = tmpOctets;
}



#endif
