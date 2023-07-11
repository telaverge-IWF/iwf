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
 * LOG: $Log: dia_downstream.cpp,v $
 * LOG: Revision 3.32.8.1.2.9.4.4.4.2.4.2.6.2.2.1  2017/12/21 04:37:20  jkchaitanya
 * LOG: Ticket 1149 changes to support case insensitivity for peers, hosts 7 realms
 * LOG:
 * LOG: Revision 3.32.8.1.2.9.4.4.4.2.4.2.6.2  2014/11/17 05:03:39  jkchaitanya
 * LOG: changes for HA Bug Fixes
 * LOG:
 * LOG: Revision 3.32.8.1.2.9.4.4.4.2.4.2.6.1  2014/10/27 08:28:39  millayaraja
 * LOG: changes for HA HotStandBy
 * LOG:
 * LOG: Revision 3.32.8.1.2.9.4.4.4.2.4.2  2014/05/06 13:09:12  jkchaitanya
 * LOG: changes for ccfh feature
 * LOG:
 * LOG: Revision 3.32.8.1.2.9.4.4.4.2.4.1  2014/02/12 07:15:00  millayaraja
 * LOG: changes done for conditional compilation for IWF/DRE and IWF specific changes
 * LOG:
 * LOG: Revision 3.32.8.1.2.9.4.4.4.2  2013/12/27 12:47:59  ncshivakumar
 * LOG:  Fix for bug Bug 2654
 * LOG:
 * LOG: Revision 3.32.8.1.2.9.4.4.4.1  2013/08/15 05:25:45  ncshivakumar
 * LOG: Generic state machine changes
 * LOG:
 * LOG: Revision 3.32.8.1.2.9.4.4  2013/04/12 04:16:34  vsarath
 * LOG: Logs improvement
 * LOG:
 * LOG: Revision 3.32.8.1.2.9.4.3  2013/03/22 05:56:57  jvikram
 * LOG: Corrected the issues related to message handling related to same session id
 * LOG: by queuing the messages. Also included debug logs.
 * LOG:
 * LOG: Revision 3.32.8.1.2.9.4.2  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.32.8.1.2.9.4.1  2013/02/27 04:43:40  millayaraja
 * LOG: modified for interface stats
 * LOG:
 * LOG: Revision 3.32.8.1.2.9  2012/12/21 05:31:54  ncshivakumar
 * LOG: Modified for tracing
 * LOG:
 * LOG: Revision 3.32.8.1.2.8  2012/12/07 06:05:02  mallikarjun
 * LOG: Bug 356 changes
 * LOG:
 * LOG: Revision 3.32.8.1.2.7  2012/11/20 17:39:44  pramana
 * LOG: Merged from CMAPI branch for 212-07 release
 * LOG:
 * LOG: Revision 3.32.8.1.2.2.16.2  2012/11/20 10:31:55  rgovardhan
 * LOG: merge from 00 Nov20Rel
 * LOG:
 * LOG: Revision 3.32.8.1.2.2.16.1  2012/11/06 10:00:03  millayaraja
 * LOG: merging from B-DRE-0212-00 branch
 * LOG:
 * LOG: Revision 3.32.8.1.2.3  2012/11/05 11:57:19  jvikas
 * LOG: Code cleanup
 * LOG:
 * LOG: Revision 3.32.8.1.2.5  2012/11/19 07:53:32  jvikas
 * LOG: Deleted the IN msg, which was causing Invalid Reads.
 * LOG:
 * LOG: Revision 3.32.8.1.2.4  2012/11/06 16:31:20  pramana
 * LOG: Reverse merged from B-DRE-0212-00-COMP and B-DRE-0212-00-TLS branches for 212-06 release
 * LOG:
 * LOG: Revision 3.32.8.1.2.2.20.1  2012/11/06 10:06:29  cprem
 * LOG: Merged from 00 branch for 0212-06 release
 * LOG:
 * LOG: Revision 3.32.8.1.2.3  2012/11/05 11:57:19  jvikas
 * LOG: Code cleanup
 * LOG:
 * LOG: Revision 3.32.8.1.2.2  2012/09/06 11:30:45  jvikas
 * LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
 * LOG:
 * LOG: Revision 3.32.8.2  2012/08/01 04:35:03  pramana
 * LOG: code changes for Bug-36
 * LOG:
 * LOG: Revision 3.32.8.1.4.2  2012/08/28 12:54:26  jvikas
 * LOG: Removed New for DiaMsgFlow which is already present in Event.
 * LOG:
 * LOG: Revision 3.32.8.1.4.1  2012/08/21 06:16:25  jvikas
 * LOG: Checkin Working Modified Stack Code -Need to Cleanup and Fix Issues.
 * LOG:
 * LOG: Revision 3.32.8.1.2.1  2012/08/21 08:55:57  ksalil
 * LOG: Merge from branch B-DRE-IDIA-0100-00
 * LOG:
 * LOG: Revision 3.32.8.1  2012/03/07 13:23:08  brajappa
 * LOG: Changes made for the DRE demo
 * LOG:
 * LOG: Revision 3.32  2009/11/26 08:39:52  sureshj
 * LOG: find Peer Instance before removeEntry. Motorola ticket 2266.
 * LOG:
 * LOG: Revision 3.31  2009/09/11 09:26:39  rajeshak
 * LOG: HelpDesk Issue 2209 Fix. (Duplicate Ans to HSS when Multiple IDC
 * LOG: responds to a reuest)
 * LOG: Removing the Entry before SendCmdToPeer
 * LOG:
 * LOG: Revision 3.30  2009/08/20 09:22:16  rajeshak
 * LOG: Fix for Issue Id:2310 (ACTIVE HOT REDUNDANCY Core dump)
 * LOG: (Backup core dumps after receiving multicasted Answer message)
 * LOG: Allocated memory for encoded buffer in BaseCommand.
 * LOG:
 * LOG: Revision 3.29  2009/08/13 10:05:33  rajeshak
 * LOG: Fix for Issue Id-2297 (ACTIVE HOT REDUNDANCY Core dump)
 * LOG: Added a check for redundancy before doing GetEventReference from event.
 * LOG:
 * LOG: Revision 3.28  2009/07/24 09:22:18  rajeshak
 * LOG: Changes done for IDC-IDS Heartbeat with Custom AVP in DWR.
 * LOG:
 * LOG: Revision 3.27  2009/07/13 06:46:21  rajeshak
 * LOG: Reverting back session table changes.
 * LOG:
 * LOG: Revision 3.26  2009/06/29 14:54:53  rajeshak
 * LOG: Changes done for performance enhancement (splitting the session table).
 * LOG:
 * LOG: Revision 3.25  2009/03/19 16:22:14  ssaxena
 * LOG: Modification done to add Redirect Agent Application.
 * LOG:
 * LOG: Revision 3.24  2009/03/19 12:42:34  nvijikumar
 * LOG: Global instance is created for the Class ITSDiaConfig to avoid function
 * LOG: call overhead as ITSDiaConfig::GetITSDiaConfig() was called max time
 * LOG:
 * LOG: Revision 3.23  2009/03/19 11:29:25  nvijikumar
 * LOG: Fix for Issue Id 1736
 * LOG: Changes to handle decode failure (Invalid AVP len)
 * LOG:
 * LOG: Revision 3.22  2009/03/12 07:09:31  nvijikumar
 * LOG: Replaced strlen with std::string length()
 * LOG:
 * LOG: Revision 3.21  2009/03/03 10:30:24  nvijikumar
 * LOG: 1. Moved IDS downstream message decoded to stack downstream scope as stack
 * LOG:    can dispatch multiple threads
 * LOG: 2. Using GetEventReference for better performance
 * LOG:
 * LOG: Revision 3.20  2009/01/03 05:34:16  rajeshak
 * LOG: Fix for whizible  Issue 1415
 * LOG:
 * LOG: Revision 3.19  2008/12/23 12:21:03  sureshj
 * LOG: Updating statistics added. fix for issue 1379.
 * LOG:
 * LOG: Revision 3.18  2008/12/22 10:59:12  rajeshak
 * LOG: IssueID:1360
 * LOG: FeatureID:none
 * LOG: Description: Fix for Memory Leak.
 * LOG: (in error scenario encoded buffer was not getting deleted)
 * LOG:
 * LOG: Revision 3.17  2008/12/22 06:23:44  sureshj
 * LOG: Fix for the issue in whizible 1379. updating outbound req and ans
 * LOG: for application based and accounting.
 * LOG:
 * LOG: Revision 3.16  2008/12/12 18:30:47  rajeshak
 * LOG: Lightweight Decode for base AVPS
 * LOG: New Command class is introduced (BaseCommand)
 * LOG:
 * LOG: Revision 3.15  2008/12/11 11:20:22  nvijikumar
 * LOG: Provided IsLocalMatchFound for downstream handling
 * LOG:
 * LOG: Revision 3.14  2008/12/07 09:40:20  rajeshak
 * LOG: Moved the Proxy functionality to dia_proxy.cpp. Code cleanup
 * LOG:
 * LOG: Revision 3.13  2008/11/06 07:51:22  nvijikumar
 * LOG: IssueID: none
 * LOG: FeatureID: none
 * LOG: Description: Incorporating Code review Comments renaming StackTunning
 * LOG:              with QueueMgmt
 * LOG:
 * LOG: Revision 3.12  2008/10/31 06:13:03  nvijikumar
 * LOG: IssueID:1189
 * LOG: FeatureID:none
 * LOG: Description: 1. Code Optimization and  stack tunning
 * LOG:              2. Code Cleanup
 * LOG:
 * LOG: Revision 3.11  2008/07/07 11:57:01  sureshj
 * LOG:      Mate Host and Realm check added for Redundancy
 * LOG:
 * LOG: Revision 3.10  2008/04/23 00:21:45  hbhatnagar
 * LOG: As part of fix provided for issue 889 in whizible, some of the
 * LOG: Relay related code is commented.
 * LOG:
 * LOG: Revision 3.9  2008/04/21 12:12:36  hbhatnagar
 * LOG: fix for issue 846 in whizible. Put check if OriginHost and OriginRealm
 * LOG: in the message matches with local configuration.
 * LOG:
 * LOG: Revision 3.8  2008/04/16 12:05:42  hbhatnagar
 * LOG: Provided fixes for issue for 720 and 786 and other misc changes.
 * LOG:
 * LOG: Revision 3.7  2008/04/11 18:45:28  hbhatnagar
 * LOG: Added traces for proper understanding.
 * LOG:
 * LOG: Revision 3.6  2008/04/08 20:36:43  avinashks
 * LOG: Removing entries in case of Relay Agents
 * LOG:
 * LOG: Revision 3.5  2008/04/08 20:12:37  avinashks
 * LOG: Added errorhandling code and called RemoveEntry at appropriate places.
 * LOG:
 * LOG: Revision 3.4  2008/04/07 18:19:26  hbhatnagar
 * LOG: Done changes for hop-by-hop id and error handling and sending the
 * LOG: proper indication to application in case of proxy. Removed unwanted
 * LOG: code.
 * LOG:
 * LOG: Revision 3.3  2008/04/02 10:57:21  hbhatnagar
 * LOG: Removed unecessary initialization of transport for stateful proxy FSM
 * LOG:
 * LOG: Revision 3.2  2008/04/01 16:27:53  hbhatnagar
 * LOG: Changes for Proxy and Relay support 3.0 release - (Viji, Hemant)
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.45  2008/03/27 12:14:08  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.39.4.5  2008/03/25 13:35:41  rajesh
 * LOG: **As per Plan B**
 * LOG: Starting of Auth-Session related Timers are commented out. This is done because of performance degradation with session increase.
 * LOG:
 * LOG: Revision 2.39.4.4  2007/05/28 13:23:52  hbhatnagar
 * LOG: made changes for the DCCAAccess Failure trace.
 * LOG:
 * LOG: Revision 2.39.4.3  2007/04/27 06:24:51  nvijikumar
 * LOG: Multicast only session based messages.
 * LOG:
 * LOG: Revision 2.39.4.2  2007/04/24 09:35:27  nvijikumar
 * LOG: Fix for mem leak issue on redundant mode.
 * LOG:
 * LOG: Revision 2.39.4.1  2007/04/19 09:20:05  nvijikumar
 * LOG: Session Context should not be removed if Rc=2xxx
 * LOG:
 * LOG: Revision 2.39  2007/01/16 07:17:34  nvijikumar
 * LOG: Fix for PBN Bug Id 5175.
 * LOG:
 * LOG: Revision 2.38  2007/01/04 11:18:50  nvijikumar
 * LOG: Full implementation of Accounting State Machine.
 * LOG:
 * LOG: Revision 2.37  2006/12/29 06:56:18  nanaparthi
 * LOG: SCTP Multihoming related changes (baseline code base)
 * LOG:
 * LOG: Revision 2.36  2006/12/22 09:27:22  nvijikumar
 * LOG: Fix for Double removal of session entries in case of DCCA
 * LOG:
 * LOG: Revision 2.35  2006/12/21 15:26:04  tpanda
 * LOG: AddOriginStateId option is added to check if OriginStateId be added to cmd
 * LOG:
 * LOG: Revision 2.34  2006/12/20 15:54:05  nvijikumar
 * LOG: Elimination of multiple ITS_FindFeature function calls(DCCA & Redundancy).
 * LOG:
 * LOG: Revision 2.33  2006/12/20 14:57:42  tpanda
 * LOG: Other bug fixes related to redundancy(Issue#5075,5073,5069,5057 etc)
 * LOG:
 * LOG: Revision 2.32  2006/12/14 15:04:45  nvijikumar
 * LOG: Fix for huge memory leak in redundancy mode.
 * LOG:
 * LOG: Revision 2.31  2006/11/30 13:45:32  hbhatnagar
 * LOG: put check for sending loop back in case of request only.
 * LOG:
 * LOG: Revision 2.30  2006/11/30 10:38:12  hbhatnagar
 * LOG: made changes for the error handling of DCCA errors.
 * LOG:
 * LOG: Revision 2.29  2006/11/29 15:07:02  kamakshilk
 * LOG: Fix for Bug Id 4982
 * LOG:
 * LOG: Revision 2.28  2006/11/28 13:29:33  nvijikumar
 * LOG: Failover and Multicasting clientId changes ( viji and kamakshi).
 * LOG:
 * LOG: Revision 2.27  2006/11/28 04:40:11  nvijikumar
 * LOG: Fix for PBN issue 4889. ( double deletion problem for RA message)
 * LOG:
 * LOG: Revision 2.26  2006/11/25 03:57:20  tpanda
 * LOG: Changes for Msg based redundancy
 * LOG:
 * LOG: Revision 2.25  2006/11/22 10:49:37  nvijikumar
 * LOG: Baseline PendingQ ( Failover ) Changes.
 * LOG:
 * LOG: Revision 2.24  2006/11/13 06:11:51  tpanda
 * LOG: clientId related fix for IDS
 * LOG:
 * LOG: Revision 2.23  2006/11/09 14:31:26  tpanda
 * LOG: clientId handling for IDS at the stack level
 * LOG:
 * LOG: Revision 2.22  2006/10/30 21:34:04  yranade
 * LOG: Fix issues. (Early morning 31st, Oct)
 * LOG:
 * LOG: Revision 2.21  2006/10/30 16:58:18  nvijikumar
 * LOG: Adding flower braces for case DIA_APP_REM_SESS_INST:
 * LOG: issue while compiling with GCC 3.4.2
 * LOG:
 * LOG: Revision 2.20  2006/10/30 15:57:41  yranade
 * LOG: ReleaseSession API is Asychronous.
 * LOG:
 * LOG: Revision 2.19  2006/10/30 12:10:13  yranade
 * LOG: Set Orgin-State-Id AVP.
 * LOG:
 * LOG: Revision 2.18  2006/10/30 11:42:58  nvijikumar
 * LOG: Route Message throygh Auth State Machine ( only for GA1.1)
 * LOG:
 * LOG: Revision 2.17  2006/10/28 12:30:52  yranade
 * LOG: 1. Don't allow naked RAR's: Bug Fix 4634
 * LOG: 2. Cleanup SessionContext for Stateless Sessions.
 * LOG:  a. In case of server, cleanup after sending answer to peer.
 * LOG:  b. In case of client, cleanup after receiving answer from peer
 * LOG:     and sending it to application.
 * LOG:
 * LOG: Revision 2.16  2006/10/27 09:44:33  yranade
 * LOG: Bug Fix 4636. Update from StatelessServer to StatefulServer if Answer
 * LOG: from Application doesn't contain AuthSessionState AVP, or if present
 * LOG: is set with STATE_MAINTAINED
 * LOG:
 * LOG: Revision 2.15  2006/10/27 04:21:20  nvijikumar
 * LOG: Check: Accounting Interim and Stop record requests should be on
 * LOG: only existing Session Id.
 * LOG:
 * LOG: Revision 2.14  2006/10/25 10:44:20  nvijikumar
 * LOG: Session Index feature is added for Accounting Messages.
 * LOG:
 * LOG: Revision 2.13  2006/10/24 13:51:54  yranade
 * LOG: 1. Code cleanup. Remove spread out deletes and do cleanup in one place.
 * LOG: 2. Header changes. Use header by reference from the message.
 * LOG: 3. Improved traces.
 * LOG: 4. StartTimer is now done in procs.
 * LOG:
 * LOG: Revision 2.12  2006/10/17 17:10:04  tpanda
 * LOG: GetSessionIndex changed to getSessionIndex
 * LOG:
 * LOG: Revision 2.11  2006/10/16 16:54:06  nvijikumar
 * LOG: Baseline Accounting Statemachine implementation.
 * LOG:
 * LOG: Revision 2.10  2006/10/16 16:02:58  yranade
 * LOG: Bug-Fixes and Updates.
 * LOG:
 * LOG: Revision 2.9  2006/10/16 06:32:46  yranade
 * LOG: AuthSessionTimer Handling. AuthSM related updates.
 * LOG:
 * LOG: Revision 2.8  2006/10/13 16:40:30  yranade
 * LOG: Cleanup, BugFix 4448, Updated Error Handling.
 * LOG:
 * LOG: Revision 2.7  2006/10/11 15:04:53  yranade
 * LOG: Fixes for issues: 4451, 4452, 4454, 4457.
 * LOG:
 * LOG: Revision 2.6  2006/10/09 13:41:39  yranade
 * LOG: Get RealmRouting working.
 * LOG:
 * LOG: Revision 2.5  2006/10/07 12:49:45  yranade
 * LOG: Remove unwanted code.
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

#include <itsdiameter.h>
#include <dia_err.h>
#include <dia_cmn.h>
#include <dia_trace.h>
#include <dia_utils.h>
#include <dia_msg_router.h>
#include <dia_downstream.h>
#include <dia_proxy.h>
#include <dia_peer_table.h>
#include <dia_realm_table.h>
#include <dia_session_table.h>
#include <dia_session_auth_fsm.h>
#include <dia_session_acct_fsm.h>
#include <dcca_feature.h>
#include <dia_stack_stats.h>
#include <dia_tracer.h>
#include <dia_stack.h>
#include <DiameterDictionaryStats.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
using namespace diameter;
using namespace diameter::base;
#endif

DCCA_ACCESS_FP     DCCAAccessFp    = NULL;
DCCA_ACCESS_IND_FP DCCAAccessIndFp = NULL;


/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
DiaDownStreamMsgHandler::HandleAcctReqMessage(its::Event &ev)
{
    int ret;
    std::string sessionId;
    DIA_BASE_CMD *cmd = NULL;
    PEER_ENTRY *peer = NULL;
    DiaSocketTransport *tr = NULL;
    REALM_ENTRY* rEntry = NULL;
    ITS_UINT sessIndx = 0;
    ITS_UINT appId = 0;
    ITS_UINT dRlen = 0;
    ITS_CHAR *destRlm = NULL;
    DIA_CER *ce = NULL;


    DT_DBG(("DiaDownStreamMsgHandler::HandleAcctReqMessage"));

    /* Message is processed in the following order
      1. If for localHost: Follow 6.1.4

      2. If for Peer: Follow 6.1.5: RequestForwarding
      3. Follow request routing: Follow 6.1.6

      4. None, then return an answer with UNABLE_TO_DELIVER
    */

    ITS_OCTET *buff = NULL;
    int len;

    DIA_BASE_CMD *msg = NULL;
    DIA_BASE_CMD *acr = NULL;
    DiaUtils::GetCmdFromEvent(&msg, &ev.GetEvent());
    cmd = (DIA_BASE_CMD *)msg;
    acr = (DIA_BASE_CMD *)msg;

    if (msg->getSessionId())
    {
        sessionId = msg->getSessionId()->value();
    }
    else
    {
        ret = DiaErrHandler::HandleError(0, msg,
                                         LOOP_TO_APP,
                                         ITS_DIA_UNKNOWN_SESSION_ID);
        return ITS_DIA_UNKNOWN_SESSION_ID;
    }

    ret = DiaMsgRouter::IsLocalMatchFound(cmd);

    if (ret == ITS_DIA_LOCAL_HOST_MATCH)
    {
        DT_ERR(("Message for LocalHost::Looped Back"));

        ret = DiaErrHandler::HandleError(0, msg,
                                         LOOP_TO_APP,
                                        ITS_DIA_LOOP_DETECTED);

        return (ITS_DIA_LOOP_DETECTED);
    }

    SESSION_ENTRY ent;
    SESSION_ENTRY *e = NULL;
    ITS_UINT recType = msg->getAccountingRecordType()->value();

    if (SESSION_TABLE->FindEntry(e,
                                 (ITS_OCTET *)sessionId.c_str(),
                                 (sessionId.length())) != ITS_SUCCESS)
    {
        DT_DBG(("Session %s Context Not Found", sessionId.c_str()));

        /* If local action for the command is Proxy
         * ignore the message
         */
        REALM_ENTRY *rEntry = NULL;
        ret = DiaMsgRouter::IsLocalRouting(cmd, rEntry);
        if (rEntry && DIA_RE_L_ACTION(rEntry) == ITS_DIA_PROXY)
        {
            DT_ERR(("For Command: %d New Session Id %s received from App With Action as Proxy. Ignoring..", cmd->getCommandCode(), sessionId.c_str()));
            return ITS_DIA_UNKNOWN_SESSION_ID;
        }

        /**
         * Memsetting the session entry variable
         */
        memset(&ent,0,sizeof(SESSION_ENTRY));

        /* Accounting Event Start, Iterim and Stop Requests
           need to have an existing session context in db
        */
        if (!acr->IsLastRecordInStorage() &&
            (recType == AccountingRecordType::INTERIM_RECORD ||
             recType == AccountingRecordType::STOP_RECORD))
        {
            DT_ERR((" For RecType %d New Session Id %s received from App. Ignoring..", recType, sessionId.c_str()));
            ret = DiaErrHandler::HandleError(0, msg,
                                             LOOP_TO_APP,
                                             ITS_DIA_UNKNOWN_SESSION_ID);
            return ITS_DIA_UNKNOWN_SESSION_ID;
        }

        DIA_SE_PEER_INST(&ent)     = UNKNOWN_PEER_INST;
        DIA_SE_ACC_STATE(&ent)     = ACCT_SESSION_ST_IDLE;
        DIA_SE_STYPE(&ent)         = DIA_ACCOUNTING;
        DIA_SE_ACC_FSM_TYPE(&ent)  = CLIENT_ACCT_FSM;
        DIA_SE_EVT_TYPE(&ent)      = ACCT_SESSION_EVT_REQUEST_ACCESS;
        DIA_SE_SINDX(&ent)         = msg->getSessionIndex();
        DIA_SE_CLIENTID(&ent)      = msg->getClientId();

       /* default agent flag is off, set if required */
        DIA_SE_IS_AGENT(&ent)  = ITS_FALSE;
 

        /**
         * Destination Realm in session entry populated from the message.
         * Parial fix for issue 720 in Whizible.
         */
        destRlm = (ITS_CHAR*)(msg->getDestinationRealm())->value().c_str();
        if ((dRlen = strlen (destRlm)) <= SESSION_DEST_REALM_MAX_SIZE)
        {
            memcpy(DIA_SE_DEST_REALM(&ent), destRlm, dRlen);
            DT_DBG(("The Destination-Realm in the Message is: %s", destRlm));
        }
        else
        {
            DT_CRT(("The Destination Realm Name in the Message Exceeds" \
                         " size defined in session entry"));
            return !(ITS_SUCCESS);
        }

        if (msg->getAuthApplicationId())
        {
            DIA_SE_APP_ID(&ent) = msg->getAuthApplicationId()->value();
        }
        else
        {
            DIA_SE_APP_ID(&ent) = msg->getHeader().appId;
        }

        switch(recType)
        {
        case AccountingRecordType::START_RECORD:
            DT_DBG(("Accounting Start Request"));
            DIA_SE_EVT_TYPE(&ent) = ACCT_SESSION_EVT_REQUEST_ACCESS;
            break;
        case AccountingRecordType::EVENT_RECORD:
            DT_DBG(("Accounting Event Request"));
            DIA_SE_EVT_TYPE(&ent) = ACCT_SESSION_EVT_REQUEST_ONETIME_ACCESS;
            break;
        default:
            DT_DBG(("Invalid Accounting Record Type"));
            break;
        }

        /* Check whether acr is of last record */
        if (acr->IsLastRecordInStorage())
        {
            DT_DBG((" Accounting Record is in Storage"));
            DIA_SE_EVT_TYPE(&ent) = ACCT_SESSION_EVT_REC_IN_STORAGE;
        }

        ret = clientAcctFsm.SubmitToSM(&ent, &ev.GetEvent());

        if (ret == ITS_SUCCESS)
        {
            return ret;
        }
        else if (ret == FSM_STATE_UPDATE)
        {
            SESSION_TABLE->StartTimer(sessionId.c_str(),
                                      ACCT_SESSION_TIMER,
                                      itsDiaConfig.GetAcctSessionConfig().GetTimeout(),
                                      &ent);

            if (SESSION_TABLE->InsertEntry(ent,
                                           (ITS_OCTET *)sessionId.c_str(),
                                           (sessionId.length()))
                                           == ITS_SUCCESS)
            {
                DT_DBG(("Created Session Context for %s", sessionId.c_str()));
                return (ITS_SUCCESS);
            }
            else
            {
                DT_CRT(("Failed to create Session Context for %s",
                         sessionId.c_str()));

                SESSION_TABLE->StopTimer(AUTH_SESSION_TIMER, &ent);

                return (ITS_DIA_UNABLE_TO_DELIVER);
            }
        }
        else if (ret != ITS_SUCCESS)
        {
            ret = DiaErrHandler::HandleError(0, msg,
                                             LOOP_TO_APP,
                                             ret);
            return (ITS_DIA_UNABLE_TO_DELIVER);
        }
    }
    else
    {
        DT_DBG(("Found Session Context for :: %s", sessionId.c_str()));
        /**
         * In case of Proxy the request message from application
         * contains the latest session index and clientID
         */

        /**
         * Adding Debug prints for Client and Application
         */
        DT_DBG(("Message Received from Client: %d and Application: %d",
                 msg->getClientId(), msg->getHeader().appId));
        DIA_SE_SINDX(e)     = msg->getSessionIndex();
        DIA_SE_CLIENTID(e)  = msg->getClientId();

        if ((DIA_SE_STYPE(e) == DIA_AUTHORIZATION)   &&
            (DIA_SE_STATE(e) == AUTH_SESSION_ST_OPEN))
        {
            /* Check whether acr is of last record */
            if (acr->IsLastRecordInStorage())
            {
                DIA_SE_ACC_FSM_TYPE(e) = CLIENT_ACCT_FSM;
                DIA_SE_ACC_STATE(e)    = ACCT_SESSION_ST_IDLE;
                DIA_SE_EVT_TYPE(e)     = ACCT_SESSION_EVT_REC_IN_STORAGE;
            }
            else if (recType == AccountingRecordType::START_RECORD)
            {
                DIA_SE_ACC_FSM_TYPE(e) = CLIENT_ACCT_FSM;
                DIA_SE_ACC_STATE(e)    = ACCT_SESSION_ST_IDLE;
                DIA_SE_EVT_TYPE(e)     = ACCT_SESSION_EVT_REQUEST_ACCESS;
            }
            else if (recType == AccountingRecordType::EVENT_RECORD)
            {
                DIA_SE_ACC_FSM_TYPE(e) = CLIENT_ACCT_FSM;
                DIA_SE_ACC_STATE(e)    = ACCT_SESSION_ST_IDLE;
                DIA_SE_EVT_TYPE(e)     = ACCT_SESSION_EVT_REQUEST_ONETIME_ACCESS;
            }
        }
        else if ((DIA_SE_STYPE(e) != DIA_ACCOUNTING))
        {
            DT_ERR(("Cannot Send ACR on an Authorization Session which is not in OPEN State"));

            ret = DiaErrHandler::HandleError(0, msg,
                                             LOOP_TO_APP,
                                             ITS_DIA_UNKNOWN_SESSION_ID);
            return ITS_DIA_UNKNOWN_SESSION_ID;
        }
    }


    if(DIA_SE_AGENT_TYPE(e) == ITS_DIA_PROXY)
    {
        ret = DiaProxyHandler::HandleAcctReqMsgFromApp(cmd,
                                        (ITS_OCTET *)sessionId.c_str(), e, ev);
        return ret;
    }

    switch (DIA_SE_ACC_FSM_TYPE(e))
    {
    case CLIENT_ACCT_FSM:
        switch(recType)
        {
        case AccountingRecordType::INTERIM_RECORD:
            DIA_SE_EVT_TYPE(e) = ACCT_SESSION_EVT_INT_EXPIRE;
            break;
        case AccountingRecordType::STOP_RECORD:
            DIA_SE_EVT_TYPE(e) = ACCT_SESSION_EVT_STOP;
            break;
        default:
            break;
        }
        ret = clientAcctFsm.SubmitToSM(e, &ev.GetEvent());

        if (ret == FSM_STATE_UPDATE)
        {
            //Warning Fix - suggest parentheses around assignment used as truth value
            if ((ret = SESSION_TABLE->ModifyEntry(e,
                                                 (ITS_OCTET *)sessionId.c_str(),
                                                 sessionId.size()))
                                                 != ITS_SUCCESS)
            {
                DT_ERR(("Failed to update Session Context"));
            }
        }
        else if (ret == ITS_EBADSTATE)
        {
            DT_ERR(("Failed to Update State, discarding message"));
        }
        break;
    case STATEFUL_SERVER_ACCT_FSM:
    case STATELESS_SERVER_ACCT_FSM:
        DT_ERR(("Server Cannot initiate Req SMType:%d",DIA_SE_ACC_FSM_TYPE(e)));
        /* Error Response if first acr is STOP/INTERIM on AuthSess */
        DiaErrHandler::HandleError(0, msg, LOOP_TO_APP,
                                   ITS_DIA_UNKNOWN_SESSION_ID);

        break;
    default:
        DT_ERR(("Invalid SMType: %d",DIA_SE_ACC_FSM_TYPE(e)));
        /* Error Response if first acr is STOP/INTERIM on AuthSess */
        DiaErrHandler::HandleError(0, msg, LOOP_TO_APP,
                                   ITS_DIA_UNKNOWN_SESSION_ID);

        break;
    }

    return (ret);

}

int
DiaDownStreamMsgHandler::HandleAcctAnsMessage(its::Event &ev)
{
    int ret;
    ITS_OCTET cmdFlag = 0x0;
    ITS_UINT cmdCode = 0;
    PEER_ENTRY *entry = NULL;
    PEER_STATE_CTXT pCtxt;
    ITS_UINT resultCode = ITS_DIA_SUCCESS;
    std::string sessionId;
    DIA_BASE_CMD *cmd = NULL;
    ITS_UINT sessIndx = 0;
    ITS_UINT appId = 0;


    DT_DBG(("DiaDownStreamMsgHandler::HandleAcctAnsMessage"));

    DIA_BASE_CMD *gCmd = NULL;
    DiaUtils::GetCmdFromEvent(&gCmd, &ev.GetEvent());
    cmd = (DIA_BASE_CMD *)gCmd;

    DT_DBG(("DownStream: AnswerMsg"));
    if (gCmd->getSessionId())
    {
        sessionId = gCmd->getSessionId()->value();
    }
    else
    {
        ret = DiaErrHandler::HandleError(0, gCmd,
                                         LOOP_TO_APP,
                                         ITS_DIA_MISSING_AVP );
        DIA_INC_INTERFACE_INVALID_MSG_COUNT(cmd->GetDictId(),cmd->getCommandCode());
        return ret;
    }

    /* If Answer is received from the Application and it doesn't
       contain resultCode, we treat it as succesfull indication
       that the User is Authorized
    */
    if (gCmd->getResultCode())
    {
        resultCode = ((DIA_BASE_CMD *)cmd)->getResultCode()->value();
    }

    SESSION_ENTRY *ent;
    if (SESSION_TABLE->FindEntry(ent,
                                 (ITS_OCTET *)sessionId.c_str(),
                                 (sessionId.length())) == ITS_SUCCESS)
    {
        DT_DBG(("FindEntry: Success"));


        if(DIA_SE_AGENT_TYPE(ent) == ITS_DIA_PROXY)
        {
            ret = DiaProxyHandler::HandleAcctAnsMsgFromApp(cmd,
                                        (ITS_OCTET *)sessionId.c_str(), ent, ev);
            return ret;
        }

        switch (DIA_SE_ACC_FSM_TYPE(ent))
        {
        case STATEFUL_SERVER_ACCT_FSM:
        {
            DT_DBG(("Stateful Accounting Server Session"));
            if (resultCode >= ITS_DIA_SUCCESS_MIN_RANGE &&
                resultCode <= ITS_DIA_SUCCESS_MAX_RANGE)
            {
                switch(((DIA_BASE_CMD *)cmd)->getAccountingRecordType()->value())
                {
                case AccountingRecordType::START_RECORD:
                    DT_DBG((" Accounting Start Answer"));
                    DIA_SE_EVT_TYPE(ent) = ACCT_SESSION_EVT_RX_ACR_START_OK;
                    break;
                case AccountingRecordType::EVENT_RECORD:
                    DT_DBG((" Accounting Event Answer"));
                    DIA_SE_EVT_TYPE(ent) = ACCT_SESSION_EVT_RX_ACR_EV_OK;
                    break;
                case AccountingRecordType::INTERIM_RECORD:
                    DT_DBG((" Accounting Interim Answer"));
                    DIA_SE_EVT_TYPE(ent) = ACCT_SESSION_EVT_RX_ACR_INT_OK;
                    break;
                case AccountingRecordType::STOP_RECORD:
                    DT_DBG((" Accounting Stop Answer"));
                    DIA_SE_EVT_TYPE(ent) = ACCT_SESSION_EVT_RX_ACR_STOP_OK;
                    break;
                default:
                    DT_DBG(("Invalid Accounting Record Type"));
                    break;
                }
            }
            else if (resultCode == ITS_DIA_OUT_OF_SPACE)
            {
                DT_DBG((" Accounting Answer with Out Of Space for Records"));
                DIA_SE_EVT_TYPE(ent) = ACCT_SESSION_EVT_RX_ACR_NO_BUF;
            }
            else
            {
                DT_DBG((" Accounting Answer with ResultCode Not Success"));
                DIA_SE_EVT_TYPE(ent) = ACCT_SESSION_EVT_RX_ACR_FAIL;
            }

            ret = statefulServerAcctFsm.SubmitToSM(ent, &ev.GetEvent());
            //client Id must be set in the context, for correct routing for IDS
            if (ret == FSM_STATE_UPDATE)
            {
                DIA_SE_CLIENTID(ent)  = ((DIA_BASE_CMD *)cmd)->getClientId();
                if (SESSION_TABLE->ModifyEntry(ent,
                                               (ITS_OCTET *)sessionId.c_str(),
                                               sessionId.size())
                                               == ITS_SUCCESS)
                {
                    DT_DBG(("Succesfully Updated Entry"));
                }
            }
            break;
        }
        case STATELESS_SERVER_ACCT_FSM:
        {
            DT_DBG(("Stateless Accounting Server Session"));
            DIA_BASE_CMD *msg = NULL;
            DiaUtils::GetCmdFromEvent(&msg, &ev.GetEvent());
            DIA_BASE_CMD *cmd = (DIA_BASE_CMD *)msg;
            DIA_HDR &hdr = (DIA_HDR &)msg->getHeader();
            hdr.flags.p = (DIA_SE_RX_FLAGS(ent)).p;
            hdr.flags.t = (DIA_SE_RX_FLAGS(ent)).t;
            hdr.hh = DIA_SE_RX_HH(ent);
            hdr.ee = DIA_SE_RX_EE(ent);

            if (DiaMsgRouter::SendCmdToPeer(DIA_SE_PEER_INST(ent),
                                            &hdr,
                                            cmd) != ITS_SUCCESS)
            {
                DT_ERR(("Failed to Send To Peer"));
                return (ITS_ESENDFAIL);
            }
            if (DIA_SE_STYPE(ent) == DIA_ACCOUNTING)
            {
                if ((ret = SESSION_TABLE->RemoveEntry(ent,
                                                 (ITS_OCTET *)sessionId.c_str(),
                                                 (sessionId.length())))
                                                 != ITS_SUCCESS)
                {
                    DT_ERR(("Failed to remove session Entry %d", ret));
                }
            }
            break;
        }
        case CLIENT_ACCT_FSM:
            DT_DBG((" Accounting Client Session"));
            break;

        default:
            DT_ERR(("Invalid SM %d\n", DIA_SE_FSM_TYPE(ent)));
            break;
        }
    }
    else
    {
        DT_ERR(("New Command Message with SessionId: %s Received from App. Ignoring..",
                sessionId.c_str()));
        DiaErrHandler::HandleError(0, gCmd,
                                   LOOP_TO_APP,
                                   ITS_DIA_UNKNOWN_SESSION_ID);

        return (!ITS_SUCCESS);
    }

    return (ITS_SUCCESS);
}

int
DiaDownStreamMsgHandler::HandleAuthReqMessage(its::Event &ev)
{
    int ret;
    std::string sessionId;
    DIA_BASE_CMD *cmd = NULL;
    PEER_ENTRY *peer = NULL;
    DiaSocketTransport *tr = NULL;
    ITS_UINT sessIndx = 0;
    ITS_UINT appId = 0;
    ITS_UINT dRlen = 0;
    ITS_CHAR *destRlm = NULL;
    DIA_CER *ce = NULL;

    DT_DBG(("DiaDownStreamMsgHandler::HandleAuthReqMessage"));

    /* Message is processed in the following order
      1. If for localHost: Follow 6.1.4

      2. If for Peer: Follow 6.1.5: RequestForwarding

      3. Follow request routing: Follow 6.1.6

      4. None, then return an answer with UNABLE_TO_DELIVER
    */

    ITS_OCTET *buff = NULL;
    int len;

    DIA_BASE_CMD *msg = NULL;
    DiaUtils::GetCmdFromEvent(&msg, &ev.GetEvent());
    cmd = (DIA_BASE_CMD *)msg;

    if (msg->getSessionId())
    {
        sessionId = msg->getSessionId()->value();
    }
    else
    {
        ret = DiaErrHandler::HandleError(0, msg,
                                         LOOP_TO_APP,
                                         ITS_DIA_UNKNOWN_SESSION_ID);
        return ITS_DIA_UNKNOWN_SESSION_ID;
    }

    ret = DiaMsgRouter::IsLocalMatchFound(cmd);

    if (ret == ITS_DIA_LOCAL_HOST_MATCH)
    {
        DT_ERR(("Message for LocalHost::Looped Back"));

        ret = DiaErrHandler::HandleError(0, msg,
                                         LOOP_TO_APP,
                                        ITS_DIA_LOOP_DETECTED);
        return (ITS_DIA_LOOP_DETECTED);
    }

    SESSION_ENTRY ent;
    SESSION_ENTRY *e = NULL;

    if (SESSION_TABLE->FindEntry(e,
                                 (ITS_OCTET *)sessionId.c_str(),
                                 (sessionId.length())) != ITS_SUCCESS)
    {
        DT_DBG(("Session %s Context Not Found", sessionId.c_str()));

        /**
         * Memsetting the session entry variable
         */
        memset(&ent,0,sizeof(SESSION_ENTRY));

        /* Session Termination, Abort Session and ReAuth requests
           need to have an existing session context in db
        */
        switch (msg->getCommandCode())
        {
        case DIA_MSG_ST:
        case DIA_MSG_AS:
        case DIA_MSG_RA:
            DT_ERR(("Received Msg %d New Session %s Context From App", msg->getCommandCode(), sessionId.c_str()));
            ret = DiaErrHandler::HandleError(0, msg,
                                             LOOP_TO_APP,
                                             ITS_DIA_UNKNOWN_SESSION_ID);
            return ITS_DIA_UNKNOWN_SESSION_ID;
        }

        /* If local action for the command is Proxy
         * ignore the message it is expected to have a
         * session entry in normal scenario.
         */
        REALM_ENTRY *rEntry = NULL;
        ret = DiaMsgRouter::IsLocalRouting(cmd, rEntry);
        if (rEntry && DIA_RE_L_ACTION(rEntry) == ITS_DIA_PROXY)
        {
            DT_ERR(("For Command: %d New Session Id %s received from App With Action as Proxy. Ignoring..", msg->getCommandCode(), sessionId.c_str()));
            return ITS_DIA_UNKNOWN_SESSION_ID;
        }

        DIA_SE_PEER_INST(&ent) = UNKNOWN_PEER_INST;
        DIA_SE_STATE(&ent)     = AUTH_SESSION_ST_IDLE;
        DIA_SE_STYPE(&ent)     = DIA_AUTHORIZATION;
        DIA_SE_FSM_TYPE(&ent)  = STATEFUL_CLIENT_AUTH_FSM;
        DIA_SE_EVT_TYPE(&ent)  = AUTH_SESSION_EVT_REQUEST_ACCESS;
        DIA_SE_SINDX(&ent)     = msg->getSessionIndex();
        DIA_SE_CLIENTID(&ent)  = msg->getClientId();
       /* default agent flag is off, set if required */
        DIA_SE_IS_AGENT(&ent)  = ITS_FALSE;
        DIA_SE_AGENT_TYPE(&ent)= ITS_DIA_LOCAL;

        /**
         * Destination Realm in session entry populated from the message.
         * Parial fix for issue 720 in Whizible.
         */
        destRlm = (ITS_CHAR*)(msg->getDestinationRealm())->value().c_str();
        //Fixing - Out-of-bounds write
        if ((dRlen = strlen (destRlm)) < SESSION_DEST_REALM_MAX_SIZE)
        {
            memcpy(DIA_SE_DEST_REALM(&ent), destRlm, dRlen);
            DIA_SE_DEST_REALM(&ent)[dRlen] = '\0';
            DT_DBG(("The Destination-Realm in the Message is: %s", destRlm));
        }
        else
        {
            DT_CRT(("The Destination Realm Name in the Message Exceeds" \
                         " size defined in session entry"));
            DIA_INC_INTERFACE_INVALID_MSG_COUNT(cmd->GetDictId(),cmd->getCommandCode());
            return !(ITS_SUCCESS);
        }

        if (msg->getAuthApplicationId())
        {
            DIA_SE_APP_ID(&ent) = msg->getAuthApplicationId()->value();
        }
        else
        {
            DIA_SE_APP_ID(&ent) = msg->getHeader().appId;
        }

        if (msg->getAuthSessionState())
        {
            if (msg->getAuthSessionState()->value() ==
                         AuthSessionState::NO_STATE_MAINTAINED)
            {
                DT_DBG(("Application Set's AuthSessionState to NO_STATE_MAINTAINED"));
                DIA_SE_FSM_TYPE(&ent) = STATELESS_CLIENT_AUTH_FSM;
            }
        }

        if (DIA_SE_FSM_TYPE(&ent) == STATELESS_CLIENT_AUTH_FSM)
        {
            ret = statelessClientAuthFsm.SubmitToSM(&ent, &ev.GetEvent());
        }
        else
        {
            ret = statefulClientAuthFsm.SubmitToSM(&ent, &ev.GetEvent());
        }

        if (ret == ITS_SUCCESS)
        {
            return (ITS_SUCCESS);
        }
        else if (ret == FSM_STATE_UPDATE)
        {
            SESSION_TABLE->StartTimer(sessionId.c_str(),
                                  AUTH_SESSION_TIMER,
                                 itsDiaConfig.GetAuthSessionConfig().GetTimeout(),
                                      &ent);

            if (SESSION_TABLE->InsertEntry(ent,
                                      (ITS_OCTET *)sessionId.c_str(),
                                     (sessionId.length())) == ITS_SUCCESS)
            {
                DT_DBG(("Created Session Context for %s", sessionId.c_str()));

                return (ITS_SUCCESS);
            }
            else
            {
                DT_CRT(("Failed to create Session Context for %s",
                                               sessionId.c_str()));

                SESSION_TABLE->StopTimer(AUTH_SESSION_TIMER, &ent);

                return (ITS_DIA_UNABLE_TO_DELIVER);
            }
        }
        else if (ret != ITS_SUCCESS)
        {
            DT_ERR(("Failed to deliver message ret = %d", ret));
            ret = DiaErrHandler::HandleError(0, msg,
                                             LOOP_TO_APP,
                                             ret);
            return (ITS_DIA_UNABLE_TO_DELIVER);
        }
    }
    else
    {
        DT_DBG(("Found Session Context for :: %s", sessionId.c_str()));

        /**
         * In case of Proxy the request message from application
         * contains the latest session index and clientID
         */
        DIA_SE_SINDX(e)     = msg->getSessionIndex();
        DIA_SE_CLIENTID(e)  = msg->getClientId();

        if (DIA_SE_NEWLY_REP_SESSION(e))
        {
            DIA_SE_NEWLY_REP_SESSION(e) = ITS_FALSE;
        }

        if (DIA_SE_STYPE(e) != DIA_AUTHORIZATION)
        {
            DT_ERR(("Invalid Session Type: %d",DIA_SE_STYPE(e)));
            ret = DiaErrHandler::HandleError(0, msg,
                                             LOOP_TO_APP,
                                             ITS_DIA_UNABLE_TO_DELIVER);
            return (ITS_DIA_UNABLE_TO_DELIVER);
        }
    }


    if(DIA_SE_AGENT_TYPE(e) == ITS_DIA_PROXY)
    {
        ret = DiaProxyHandler::HandleAuthReqMsgFromApp(cmd,
                                (ITS_OCTET *)sessionId.c_str(), e, ev);
        return ret;
    }

    switch (DIA_SE_FSM_TYPE(e))
    {
    /* Stateful Client Auth FSM */
    case STATEFUL_CLIENT_AUTH_FSM:
        {
            DT_DBG(("Stateful Client"));
            switch (msg->getCommandCode())
            {
            case DIA_MSG_ST:
                DIA_SE_EVT_TYPE(e) = AUTH_SESSION_EVT_TX_STR;
                break;
            case DIA_MSG_AS:
                DIA_SE_EVT_TYPE(e) = AUTH_SESSION_EVT_TX_ASR;
                break;
            default:
                DIA_SE_EVT_TYPE(e) = AUTH_SESSION_EVT_REQUEST_ACCESS;
                break;
            }
            ret = statefulClientAuthFsm.SubmitToSM(e, &ev.GetEvent());

            if (ret == FSM_STATE_UPDATE)
            {
                if ((ret = SESSION_TABLE->ModifyEntry(e,
                                               (ITS_OCTET *)sessionId.c_str(),
                                               sessionId.size()))
                        != ITS_SUCCESS)
                {
                    DT_ERR(("Failed to update Session Context"));
                }
            }
            else if (ret == ITS_EBADSTATE)
            {
                DT_ERR(("Failed to Update State, discarding message"));
            }
            else if (ret == ITS_DIA_UNABLE_TO_DELIVER)
            {
                DT_DBG(("State transtion failed. Unable to deliver reported <%s>",
                            sessionId.c_str()));
                // Send error message to application about unable to deliver
                DiaErrHandler::HandleError(0, msg,
                        LOOP_TO_APP,
                        ITS_DIA_UNABLE_TO_DELIVER);
                return ITS_DIA_UNABLE_TO_DELIVER;
            }


        }
        break;
    case STATELESS_CLIENT_AUTH_FSM:
        {
            DT_DBG(("Stateless Client"));
            /* Stateless Client Auth FSM */
            switch (msg->getCommandCode())
            {
            case DIA_MSG_ST:
            case DIA_MSG_AS:
                DT_ERR(("STR/ASA for Stateless Client Sessions...Discarding"));
                break;
            default:
                DIA_SE_EVT_TYPE(e) = AUTH_SESSION_EVT_REQUEST_ACCESS;
                ret = statelessClientAuthFsm.SubmitToSM(e, &ev.GetEvent());
                if (ret == FSM_STATE_UPDATE)
                {
                    if ((ret = SESSION_TABLE->ModifyEntry(e,
                                                   (ITS_OCTET *)sessionId.c_str(),
                                                   sessionId.size()))
                                          != ITS_SUCCESS)
                    {
                        DT_ERR(("Failed to update Session Context"));
                    }
                }
                else if (ret == ITS_EBADSTATE)
                {
                    DT_ERR(("Failed to Update State, discarding message"));
                }


                break;
            }
        }
        break;
    case STATEFUL_SERVER_AUTH_FSM:
        {
            DT_DBG(("Stateful Server"));
            switch (msg->getCommandCode())
            {
            case DIA_MSG_AS:
                DIA_SE_EVT_TYPE(e) = AUTH_SESSION_EVT_TX_ASR;
                ret = statefulServerAuthFsm.SubmitToSM(e, &ev.GetEvent());
                break;
            case DIA_MSG_RA:
                DT_DBG(("Server Initiated Re-Auth"));
                DIA_SE_EVT_TYPE(e) = AUTH_SESSION_EVT_TX_RAR;
                ret = statefulServerAuthFsm.SubmitToSM(e, &ev.GetEvent());
                break;
            default:
                DT_DBG(("Server Initiated App specific message received"));
                DIA_SE_EVT_TYPE(e) = AUTH_SESSION_EVT_TX_APP_SPECIFIC_REQ_MSG;
                ret = statefulServerAuthFsm.SubmitToSM(e, &ev.GetEvent());
                break;
            }
            if (ret == FSM_STATE_UPDATE)
            {
                //Warning Fix - suggest parentheses around assignment used as truth value
                if ((ret = SESSION_TABLE->ModifyEntry(e,
                                               (ITS_OCTET *)sessionId.c_str(),
                                               sessionId.size()))
                                      != ITS_SUCCESS)
                {
                    DT_ERR(("Failed to update Session Context"));
                }
            }
        }
        break;
    case STATELESS_SERVER_AUTH_FSM:
        DT_DBG(("Stateless Server...cannot send requests...discarding"));
	ret = DiaErrHandler::HandleError(msg->GetIncomingPeerInst(), msg,
                                             SEND_ERROR_TO_PEER,
                                             ITS_DIA_UNABLE_TO_DELIVER);
        break;
    default:
        DT_ERR(("Invalid SMType: %d",DIA_SE_FSM_TYPE(e)));
        ret = !ITS_SUCCESS;
        break;
    }

    return (ret);
}

int
DiaDownStreamMsgHandler::HandleAuthAnsMessage(its::Event &ev)
{
    int ret;
    ITS_OCTET cmdFlag = 0x0;
    ITS_UINT cmdCode = 0;
    PEER_ENTRY *entry = NULL;
    PEER_STATE_CTXT pCtxt;
    ITS_UINT resultCode = ITS_DIA_SUCCESS;
    std::string sessionId;
    DIA_BASE_CMD *cmd = NULL;
    ITS_UINT sessIndx = 0;
    ITS_UINT appId = 0;

    DT_DBG(("DiaDownStreamMsgHandler::HandleAuthAnsMessage"));

    DIA_BASE_CMD *gCmd = NULL;
    DiaUtils::GetCmdFromEvent(&gCmd, &ev.GetEvent());
    cmd = (DIA_BASE_CMD *)gCmd;

    DT_DBG(("DownStream: AnswerMsg"));
    if (gCmd->getSessionId())
    {
        sessionId = gCmd->getSessionId()->value();
    }
    else
    {
        ret = DiaErrHandler::HandleError(0, gCmd,
                                   LOOP_TO_APP,
                                   ITS_DIA_MISSING_AVP);
        return ret;
    }

    /* If Answer is received from the Application and it doesn't
       contain resultCode, we treat it as succesfull indication
       that the User is Authorized
    */
    if (gCmd->getResultCode())
    {
        resultCode = ((DIA_BASE_CMD *)cmd)->getResultCode()->value();
    }

    SESSION_ENTRY *ent;
    if (SESSION_TABLE->FindEntry(ent,
                                 (ITS_OCTET *)sessionId.c_str(),
                                 (sessionId.length())) == ITS_SUCCESS)
    {
        DT_DBG(("FindEntry: Success"));

        if (DIA_SE_NEWLY_REP_SESSION(ent))
        {
            DIA_SE_NEWLY_REP_SESSION(ent) = ITS_FALSE;
        }

        if(DIA_SE_AGENT_TYPE(ent) == ITS_DIA_PROXY)
        {
            ret = DiaProxyHandler::HandleAuthAnsMsgFromApp(cmd,
                                            (ITS_OCTET *)sessionId.c_str(),
                                            ent, ev);
            return ret;
        }

        switch (DIA_SE_FSM_TYPE(ent))
        {
        case STATEFUL_SERVER_AUTH_FSM:
        {
            DT_DBG(("Stateful Server Session"));

            if (resultCode >= ITS_DIA_SUCCESS_MIN_RANGE &&
                resultCode <= ITS_DIA_SUCCESS_MAX_RANGE)
            {
                DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_TX_SSAA_OK;
            }
            else
            {
                DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_TX_SSAA_FAIL;
            }

            if (gCmd->getAuthSessionState() &&
                (gCmd->getAuthSessionState()->value() ==
                    AuthSessionState::NO_STATE_MAINTAINED))
            {
                DT_DBG(("Answer::AuthSessionState::NO_STATE_MAINTAINED"));
                DT_DBG(("Updated to Stateless Server Session"));
                DIA_HDR &hdr = (DIA_HDR &)gCmd->getHeader();
                hdr.flags.p = (DIA_SE_RX_FLAGS(ent)).p;
                hdr.flags.t = (DIA_SE_RX_FLAGS(ent)).t;
                hdr.hh = DIA_SE_RX_HH(ent);
                hdr.ee = DIA_SE_RX_EE(ent);

                ITS_USHORT peerInst = DIA_SE_PEER_INST(ent);
                if ((ret = SESSION_TABLE->RemoveEntry(ent,
                                                (ITS_OCTET *)sessionId.c_str(),
                                                (sessionId.length())))
                     == ITS_SUCCESS)
                {
                    if (DiaMsgRouter::SendCmdToPeer(peerInst,
                                                &hdr,
                                                cmd) != ITS_SUCCESS)
                    {
                        DT_ERR(("Failed to Send To Peer"));
                        return (ITS_ESENDFAIL);
                    }
                }
                else
                {
                    DT_ERR(("Dropping Duplicate Ans Msg from Application"));
                }
            }
            else
            {
                switch (cmd->getCommandCode())
                {
                case DIA_MSG_ST:
                    DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_TX_STA;
                    ret = statefulServerAuthFsm.SubmitToSM(ent, &ev.GetEvent());
                    break;
                default:
                    ret = statefulServerAuthFsm.SubmitToSM(ent, &ev.GetEvent());

                    /*
                     * client Id must be set in the context,
                     * for correct routing for IDS
                     */

                    if (ret == FSM_STATE_UPDATE)
                    {
                        DIA_SE_CLIENTID(ent)  = gCmd->getClientId();
                        if (SESSION_TABLE->ModifyEntry(ent,
                                            (ITS_OCTET *)sessionId.c_str(),
                                            sessionId.size())
                                            == ITS_SUCCESS)
                        {
                            DT_DBG(("Succesfully Updated Entry"));
                        }
                    }
                    break;
                }
            }
            break;
        }
        case STATELESS_SERVER_AUTH_FSM:
        {
            DT_DBG(("Stateless Server Session"));

            DIA_BASE_CMD *msg = NULL;
            DiaUtils::GetCmdFromEvent(&msg, &ev.GetEvent());
            DIA_BASE_CMD *cmd = (DIA_BASE_CMD *)msg;

            if (msg->getAuthSessionState() &&
                (msg->getAuthSessionState()->value() ==
                    AuthSessionState::NO_STATE_MAINTAINED))
            {
                DIA_HDR &hdr = (DIA_HDR &)msg->getHeader();
                hdr.flags.p = (DIA_SE_RX_FLAGS(ent)).p;
                hdr.flags.t = (DIA_SE_RX_FLAGS(ent)).t;
                hdr.hh = DIA_SE_RX_HH(ent);
                hdr.ee = DIA_SE_RX_EE(ent);

                ITS_USHORT peerInst = DIA_SE_PEER_INST(ent);
                if ((ret = SESSION_TABLE->RemoveEntry(ent,
                                                (ITS_OCTET *)sessionId.c_str(),
                                                (sessionId.length())))
                     == ITS_SUCCESS)
                {
                    if (DiaMsgRouter::SendCmdToPeer(peerInst,
                                                &hdr,
                                                cmd) != ITS_SUCCESS)
                    {
                        DT_ERR(("Failed to Send To Peer"));
                        return (ITS_ESENDFAIL);
                    }
                }
                else
                {
                    DT_ERR(("Dropping Duplicate Ans Msg from Application"));
                }
            }
            else
            {
                DT_DBG(("No AuthSessionState Set or Set to STATE_MAINTAINED"));
                DT_DBG(("StatefulServerSession"));
                /* Update State and Submit to Stateful Server SM */
                DIA_SE_FSM_TYPE(ent)  = STATEFUL_SERVER_AUTH_FSM;
                DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_TX_SSAA_OK;

                /* Restart all the Auth Timers */
                SESSION_TABLE->ReStartAllAuthTimers(ent, msg);

                ret = statefulServerAuthFsm.SubmitToSM(ent, &ev.GetEvent());

                /*
                 * client Id must be set in the context,
                 * for correct routing for IDS
                 */

                if (ret == FSM_STATE_UPDATE)
                {
                    DIA_SE_CLIENTID(ent)  = msg->getClientId();

                    if (SESSION_TABLE->ModifyEntry(ent,
                                        (ITS_OCTET *)sessionId.c_str(),
                                        sessionId.size())
                                        != ITS_SUCCESS)
                    {
                        DT_ERR(("Failed to update Entry"));
                    }
                }
            }

            break;
        }
        case STATEFUL_CLIENT_AUTH_FSM:
            DT_DBG(("Stateful Client Session"));

            switch (cmd->getCommandCode())
            {
            case DIA_MSG_AS:
                if ((resultCode >= ITS_DIA_SUCCESS_MIN_RANGE &&
                     resultCode <= ITS_DIA_SUCCESS_MAX_RANGE) &&
                    !cmd->isError())
                {
                    DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_TX_ASA_OK;
                }
                else
                {
                    DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_TX_ASA_FAIL;
                }

                break;
            case DIA_MSG_RA:
                if ((resultCode >= ITS_DIA_SUCCESS_MIN_RANGE &&
                     resultCode <= ITS_DIA_SUCCESS_MAX_RANGE) &&
                    !cmd->isError())
                {
                    DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_TX_RAA_OK;
                }
                else
                {
                    DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_TX_RAA_FAIL;
                }

                break;
            default:
                DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_TX_APP_SPECIFIC_RES_MSG;
                break;
            }

            ret = statefulClientAuthFsm.SubmitToSM(ent, &ev.GetEvent());
            //client Id must be set in the context, for correct routing for IDS
            DIA_SE_CLIENTID(ent)  = gCmd->getClientId();
            if (SESSION_TABLE->ModifyEntry(ent,
                                           (ITS_OCTET *)sessionId.c_str(),
                                           sessionId.size())
                                  == ITS_SUCCESS)
            {
                DT_DBG(("Succesfully Updated Session Context"));
            }
            break;
        case STATELESS_CLIENT_AUTH_FSM:
            DT_DBG(("Stateless Client Session"));
            break;
        case REDIRECT_AGENT_FSM:
        {
            DT_DBG(("Redirect Session"));

            ITS_USHORT trInst = DIA_SE_PEER_INST(ent);
            DiaSocketTransport *tr = trTable[trInst];
            gCmd->setClientId(DIA_SE_CLIENTID(ent));
            DIA_HDR &hdr = (DIA_HDR&)gCmd->getHeader();
            hdr.hh = DIA_SE_RX_HH(ent);
            hdr.ee = DIA_SE_RX_EE(ent);

            /**
             * Sending Redirected Answer.
             */
            if ( tr != NULL)
            {
                if (DiaMsgRouter::SendCmdToPeer(trInst, &hdr, gCmd) ==
                                                          ITS_SUCCESS)
                {
                    DT_DBG(("Send Redirected Ans to Peer :: SUCCESS"));
                }
                else
                {
                    DT_ERR(("Send Redirected Ans to Peer :: FAILED"));
                }
            }
            else
            {
                DT_WRN(("Requested Peer is Not UP."));
            }

            /**
             * Remove the session entry.
             */
            if ((ret = SESSION_TABLE->RemoveEntry(ent,
                                                  (ITS_OCTET *)sessionId.c_str(),
                                                  strlen(sessionId.c_str())))
                                                  != ITS_SUCCESS)
            {
                DT_ERR(("Failed to remove redirect session Entry %d", ret));
                ret = !ITS_SUCCESS;
            }
            DT_DBG(("Redirect session entry removed sucessfully %d", ret));
        }
        break;

        default:
            DT_ERR(("Invalid SM %d\n", DIA_SE_FSM_TYPE(ent)));
            break;
        }
    }
    else
    {
        DT_ERR(("Auth Answer From App Message with Invalid SessionId: Discarding %s",
                                             sessionId.c_str()));

        DiaErrHandler::HandleError(0, gCmd,
                                   LOOP_TO_APP,
                                   ITS_DIA_UNKNOWN_SESSION_ID);
        DIA_INC_INTERFACE_INVALID_MSG_COUNT(cmd->GetDictId(),cmd->getCommandCode());
        return (!ITS_SUCCESS);
    }

    return (ITS_SUCCESS);
}

int
DiaDownStreamMsgHandler::ReleaseSession(const char* sessionId)
{
    int ret = ITS_SUCCESS;
    SESSION_ENTRY *ent = NULL;

    if (SESSION_TABLE->FindEntry(ent,
                                 (ITS_OCTET *)sessionId,
                                 strlen(sessionId)) != ITS_SUCCESS)
    {
        DT_ERR(("No active session found for %s", sessionId));
        return (!ITS_SUCCESS);
    }

    if ((ret = SESSION_TABLE->RemoveEntry(ent, (ITS_OCTET *)sessionId,
                                          strlen(sessionId))) != ITS_SUCCESS)
    {
         DT_ERR(("Failed to remove session Entry"));
    }

    return ret;
}

int
DiaDownStreamMsgHandler::HandleMessage(DIAThread *thr, its::Event &ev)
{
    int ret;
    ITS_UINT cmdCode = 0;
    ITS_UINT evtType = PEER_EVT_SEND_MESSAGE;
    DIA_BASE_CMD *gCmd = NULL;
    DIA_BASE_CMD *cmd = NULL;

    // Clear any previous thread specific session trace object
    DiaTracer::ClearThreadTraceObj();

    DT_DBG(("Received event from [%d]", ev.GetSource()));

    switch (ev.GetSource())
    {
    case DIA_APP_REM_SESS_INST:
    {
        ITS_USHORT dest = DIASTACK_TQ_INST;
        if (itsDiaConfig.IsQueueMgmtEnabled())
        {
            dest = DIASTACK_SENDER_TQ_INST;
        }

        DT_DBG(("Received Indication to Remove Session Entry", ev.GetLength()));
        if (itsDiaConfig.IsMsgRedundancyEnabled())
        {
           if (DSM_MulticastStackEventToFtGroupMembers(
                      SESSION_TABLE_FT_GROUP_ID,
                      ev.GetEvent(),
                      DIA_GCS_APP_REM_SESS_INST,
                      dest) == ITS_SUCCESS)
           {
              DT_DBG(("Multicasted Message"));
              return ITS_SUCCESS;
           }
        }

        char* sessId = (char *)ev.GetData();

        if ((itsDiaConfig.GetDccaFeature() != NULL) && DCCAAccessIndFp)
        {
            // If DCCA module is enabled, then send application initiated
            // session release indication to DCCA
            DT_DBG(("Sending session release indication to DCCA module for %s",
                    sessId));
            DCCAAccessIndFp(APP_REL_SESS_IND_FROM_STACK, (ITS_OCTET*)sessId, 4, 0);
        }

        if ((ret = ReleaseSession(sessId)) != ITS_SUCCESS)
        {
            DT_ERR(("Failed to Remove Entry %s", sessId));
        }
        else
        {
            DT_DBG(("Succesfully Removed Session Entry %s", sessId));
        }
        return ret;
    }
    case DIA_GCS_APP_REM_SESS_INST:
    {
        char* sessId = (char *)ev.GetData();
        if ((ret = ReleaseSession(sessId)) != ITS_SUCCESS)
        {
            DT_ERR(("Failed to Remove Entry %s", sessId));
        }
        else
        {
            DT_DBG(("Succesfully Removed Session Entry %s", sessId));
        }
        return ret;
    }
    case DIA_GCS_APP_INST:
    {
       if (ev.GetData()[sizeof(ITS_ULONG)] == DSM_GetNodeId())
       {
          DiaUtils::GetCmdFromData(&gCmd, (ITS_OCTET*)&ev.GetData()[0]);
          cmd = (DIA_BASE_CMD *)gCmd;
          cmd->setUserData(&ev.GetEvent());
       }
       else
       {
          ITS_UINT len = ev.GetLength() - 2*sizeof(ITS_UINT)
                         - sizeof(ITS_ULONG) - 1;
          ret = DiaUtils::DecodeMsg(&cmd,
                (unsigned char*)&ev.GetData()[1+sizeof(ITS_ULONG)+
                 2*sizeof(ITS_UINT)], len);

          if (ret != ITS_SUCCESS)
          {
                DT_ERR(("Decode error"));
                return ret;
          }
          gCmd = (DIA_BASE_CMD *)cmd;

          ITS_OCTET *enBuff = (ITS_OCTET *)malloc(len);
          if (enBuff == NULL)
          {
              throw CodecException(__FILE__, __LINE__,"Malloc Failed",
                                  ITS_DIA_RESOURCES_EXCEEDED);
          }

          memcpy(enBuff,&ev.GetData()[1+sizeof(ITS_ULONG)+
                 2*sizeof(ITS_UINT)], len);
          gCmd->setEncodedBuf(enBuff);

          ITS_UINT sessIndex;
          memcpy(&sessIndex,
                &ev.GetData()[1+sizeof(ITS_ULONG)],
                sizeof(ITS_UINT));
          gCmd->setSessionIndex(sessIndex);
          ITS_UINT clientId;
          memcpy(&clientId,
                &ev.GetData()[1+sizeof(ITS_ULONG)+sizeof(ITS_UINT)],
                sizeof(ITS_UINT));
          gCmd->setClientId(clientId);
          memcpy((ITS_OCTET*)&ev.GetData()[0], &gCmd, sizeof(ITS_ULONG));

          cmd->setUserData(&ev.GetEvent());
       }
       break;
    }
    case ITS_REP_EVENT_FROM_APP:
    {

        DT_DBG(("ITS_REP_EVENT_FROM_APP recieved."));
        ITS_OCTET* sessionData = (ITS_OCTET*)ev.GetData();
        ITS_UINT appId;
        ITS_UINT sessIdx;
        int sessionDataLength = sizeof(ITS_USHORT) + // peerInst
                                sizeof(ITS_UINT) +   // timeout
                                sizeof(ITS_UINT) +   // lifetime
                                sizeof(ITS_UINT) +   // gracePeriod
                                sizeof(ITS_UINT) +   // appId
                                sizeof(ITS_UINT) +   // session start time stamp
                                sizeof(ITS_UINT);    // last CCR sent time stamp
        std::string strSessionId ((char*)(sessionData  + sessionDataLength),
                                  ev.GetLength() - sessionDataLength);
        //char* sessionId = (char*)(sessionData  + sessionDataLength);
        char* sessionId = (char*)strSessionId.c_str();

        if ((ret = ReCreateSessionEntry(sessionId, sessionData, sessIdx, appId)) != ITS_SUCCESS)
        {
            DT_ERR(("Failed to Create Session Entry [%s]", sessionId));
            return !ITS_SUCCESS;
        }

        if ((itsDiaConfig.GetDccaFeature() != NULL) && DCCAAccessIndFp)
        {
            // If DCCA module is enabled, then send application initiated
            // session creation indication to DCCA
            DT_DBG(("Sending session recreation indication to DCCA module for [%s]",
                    sessionId));
            DCCAAccessIndFp(APP_CREATE_SESS_IND_FROM_STACK, (ITS_OCTET*)sessionId,
                            appId, 0);
        }

       return ITS_SUCCESS;
    }
    default:
    {
       if (ev.GetSource() == DIA_IDS_APP_INST)
       {
            ITS_EVENT evt;
            ITS_UINT clientId = 0;
            ITS_UINT appId = 0;
            ITS_UINT clIdx = 0;
            ITS_UINT index = 0;
            ITS_USHORT offset = 0;
            ITS_USHORT evtLen = 0;
            ITS_OCTET* evtData = NULL;
            ITS_OCTET accRecInfo = 0x00;

            if (DiaUtils::GetEventReference(&ev, &evt) != ITS_SUCCESS)
            {
                DT_ERR(("Failed to GetEventReference"));
                return !ITS_SUCCESS;
            }

            evtLen = evt.len;
            evtData = evt.data;

            /* Get the client ID */
            clientId = DiaUtils::DataToInt(evtData+index, sizeof(ITS_UINT));
            index += sizeof(ITS_UINT);
            /* Next client Session Index */
            index += sizeof(ITS_UINT);

            /* Get  Accounting record information if ACR */
            accRecInfo = evtData[index];
            index += sizeof(ITS_OCTET);

            /* Get Diameter message type */
            index++;

            //offset = 2*sizeof(ITS_UINT) + 2*sizeof(ITS_OCTET);
            offset = 10; /*2*sizeof(ITS_UINT) + 2*sizeof(ITS_OCTET);*/

            try
            {
                /*DTF Changes*/
                DiaUtils::GetCmdFromEvent(&gCmd, &ev.GetEvent());

                gCmd->setClientId(clientId);
                
                // Set the trace object to the thread, if tracing is enabled
                // and the trace object is set
                DiaTracer::SetTraceObj(gCmd);

                if (gCmd->isRequest() && (gCmd->getCommandCode() == 271))
                {

                    bool storageSpaceFlag = true;
                    bool lastRecFlag = false;
                    /* Get last bit i.e storageSpaceFlag */
                    storageSpaceFlag = (accRecInfo & 0x01);

                    /* Get last but one bit i.e lastRecFlag */
                    lastRecFlag = ((accRecInfo & 0x02) >> 1);

                    /* Set respective flags */
                    gCmd->setStorageSpaceAvailable(storageSpaceFlag);
                    gCmd->setLastRecordInStorage(lastRecFlag);
                }
            }
            catch(...)
            {
                DT_ERR(("Decode error"));
                return !ITS_SUCCESS;
            }

           /*
            * Set Buffer in the message and set evt->data to NULL
            * to avoid multple deletes
            */
           gCmd->setPtrToFreeBuf((void *)evtData);

           /*
            * Dont get confused over writing event data to point gCmd address
            * Original event data is stored as encode buffer and it will be
            * freed once message is sent via BaseCommand destructor
            */

           /* Update first bytes of event with gCmd Ptr,
            * as some func tries to get Cmd ptr from event
            */
            memcpy((void *)&ev.GetData()[0], &gCmd,sizeof(ITS_ULONG));
       }
       else
       {
           DiaUtils::GetCmdFromEvent(&gCmd, &ev.GetEvent());
       }
       cmd = (DIA_BASE_CMD *)gCmd;
       if (itsDiaConfig.IsMsgRedundancyEnabled() &&
          gCmd->getSessionId())
       {
           unsigned char* buff;
           int len = 0;
            ITS_USHORT dest = DIASTACK_TQ_INST;
            if (itsDiaConfig.IsQueueMgmtEnabled())
            {
                dest = DIASTACK_SENDER_TQ_INST;
            }

           //gCmd->encode(buff, len);
           buff = (unsigned char*) gCmd->getEncodedBuf();
           len = gCmd->getEncodedBufLen();

           ITS_EVENT gcsev;
           ITS_EVENT_INIT(&gcsev, DIA_GCS_APP_INST,
                         len+1+sizeof(ITS_ULONG)+2*sizeof(ITS_UINT));
           memcpy(&gcsev.data[0], &gCmd, sizeof(ITS_ULONG));
           gcsev.data[sizeof(ITS_ULONG)] = DSM_GetNodeId();
           ITS_UINT sessIndex = gCmd->getSessionIndex();
           memcpy(&gcsev.data[1+sizeof(ITS_ULONG)],
                 &sessIndex, sizeof(ITS_UINT));
           ITS_UINT clientId = gCmd->getClientId();
           memcpy(&gcsev.data[1+sizeof(ITS_ULONG)+sizeof(ITS_UINT)],
                 &clientId, sizeof(ITS_UINT));
           memcpy(&gcsev.data[1+sizeof(ITS_ULONG)+2*sizeof(ITS_UINT)],
                 (ITS_OCTET*)buff, len);

            /* This will be deleted with cmd delete */
            //delete [] buff;
            buff = NULL;

            /* Fix for Issue 1415 :IDS is dumping core
             * while trying to send back answer message to the Peer.
             */
            cmd->setEncodedBuf(NULL);

           if (DSM_MulticastStackEventToFtGroupMembers(
                      SESSION_TABLE_FT_GROUP_ID,
                      gcsev,
                      DIA_GCS_APP_INST,
                      dest) == ITS_SUCCESS)
           {
               DT_DBG(("DiaDownStream:Message Multicasted"));
           }
           else
           {
               DT_WRN(("DiaDownStream:Message Multicasted Failed"));
           }
           ITS_EVENT_TERM(&gcsev);
           return ITS_SUCCESS;
       }
    }
    }

        // Set the trace object to the thread, if tracing is enabled
        // and the trace object is set
        DiaTracer::SetTraceObj(gCmd);

        DT_DBG(("Message Received from Application"));

        const std::string& oriHostStr =
            itsDiaConfig.GetLocalCER()->getOriginHost().value();

        if (itsDiaConfig.GetDccaFeature() != NULL &&
                (strcasecmp(oriHostStr.c_str(),gCmd->getOriginHost()->value().c_str()) == 0))
        {
            /* Agent messages won't come here */
            /* check for bcgi or normal appId */
            ITS_UINT appIdDcca = 0;
            if ( (appIdDcca = gCmd->getHeader().appId) == 0 )
            {
                if (gCmd->getAuthApplicationId())
                {
                    appIdDcca = gCmd->getAuthApplicationId()->value();
                }
            }
            ITS_INT sessionInd = gCmd->getSessionIndex();

            ITS_INT ret = DCCAAccessFp(gCmd, sessionInd,
                    0, appIdDcca);
            if (ret == DCCA_RELEASE_SESSION_IND)
            {
                const char* sessId = gCmd->getSessionId()->value().c_str();
                Event remev(DIA_APP_REM_SESS_INST, strlen(sessId) + 1, (ITS_OCTET *)sessId);
                if (itsDiaConfig.IsMsgRedundancyEnabled())
                {
                    remev.SetSource(DIA_GCS_APP_REM_SESS_INST);
                }

                ITS_USHORT dest = DIASTACK_TQ_INST;
                if (itsDiaConfig.IsQueueMgmtEnabled())
                {
                    dest = DIASTACK_SENDER_TQ_INST;
                }
                its::Transport::PutEvent(dest, remev);
            }
            else if (ret != ITS_SUCCESS)
            {
                DT_ERR(("DCCAAccess::Failed to process Message:%d.", ret));
                /* send loop back only if the message is request */
                if( gCmd->isRequest())
                {
                    DiaErrHandler::HandleError(0, gCmd,
                            LOOP_TO_APP,
                            ret);
                }
                if(gCmd)
                {
                    delete gCmd;
                    gCmd = NULL;
                }
                return ret;
            }
        }

        cmdCode = gCmd->getCommandCode();

        switch(cmdCode)
        {
            case DIA_MSG_CE:
            case DIA_MSG_DW:
            case DIA_MSG_DP:
                {
                    /* check for custom AVP in DWR message */
                    if ((cmdCode == DIA_MSG_DW) && gCmd->containsIDCIDSHeartbeat())
                    {
                        ITS_UINT rCode = gCmd->getIdcIdsHBValue();
                        DiaErrHandler::HandleError(0, gCmd, HEARTBEAT, rCode);
                        break;
                    }

                    /* Peer Table Based Routing
                       Since the above commands do not have any
                       Dest-Host or Dest-Realm AVP's, we just send
                       them to all the Peer's that are connected
                       */
                    PEER_ENTRY *entry = PeerTable::GetPeerTable()->FindFirstEntry();
                    while (entry != NULL)
                    {
                        if (DIA_PE_STATE(entry) != PEER_ST_I_OPEN &&
                                DIA_PE_STATE(entry) != PEER_ST_R_OPEN)
                        {
                            DT_ERR (("Failed to send Peer Based Msg.%s not in open state",
                                        DIA_PE_HOST(entry)));
                            entry = PeerTable::GetPeerTable()->FindNextEntry(entry);
                            continue;
                        }
                        ITS_USHORT inst = DIA_PE_INST(entry);

                        /*
                         **  take theoriginal buffer and decode to get the generic command object
                         */

                        DIA_CMD *pCmd = NULL;

                        unsigned char* buff = (unsigned char*) cmd->getEncodedBuf();
                        int len = cmd->getEncodedBufLen();

                        int ret = DiaUtils::DecodeMsg(&pCmd, buff, len);
                        if (ret != ITS_SUCCESS)
                        {
                            DT_ERR(("DiaDownStreamMsgHandler::HandleMessage:Decode error"));
                            DT_ERR(("DiaDownStreamMsgHandler:: Droping Message"));
                            /* update the Stats for invalid message received for 
                             * interface */
                            DIA_INC_INTERFACE_INVALID_MSG_COUNT(gCmd->GetDictId(),gCmd->getCommandCode());
                            if (cmd != NULL)
                            {
                                delete cmd;
                                cmd = NULL;
                            }
                            return ret;
                        }

                        DIA_GEN_CMD *genCmd = (DIA_GEN_CMD*) pCmd;

                        DIA_HDR &hdr = (DIA_HDR&)genCmd->getHeader();

                        hdr.hh = DiaUtils::GenerateHopByHopId();
                        hdr.ee = DiaUtils::GenerateEndToEndId();

                        if (genCmd->getOriginStateId())
                        {
                            ITS_UINT &o = (ITS_UINT &)gCmd->getOriginStateId()->value();
                            o = itsDiaConfig.GetOriginStateId();
                        }
                        else if(itsDiaConfig.GetOriginStateIdOpt())
                        {
                            OriginStateId oid(itsDiaConfig.GetOriginStateId());
                            AVPContainerDerived &avpCont = (AVPContainerDerived &)
                                genCmd->getContainer();
                            avpCont.add(oid.name(), oid, false);
                        }

                        if (cmdCode == DIA_MSG_DP)
                        {
                            evtType = PEER_EVT_STOP;
                        }

                        //Warning Fix - suggest parentheses around assignment used as truth value
                        if ((ret = DiaMsgRouter::SendCmdToPeer(inst, &hdr, genCmd, evtType)) != ITS_SUCCESS)
                        {
                            DT_ERR(("Failed to send To Peer %s: ret = %d", DIA_PE_HOST(entry), ret));
                        }

                        if (pCmd)
                        {
                            delete pCmd;
                            pCmd = NULL;
                        }

                        entry = PeerTable::GetPeerTable()->FindNextEntry(entry);
                    }
                    break;
                }
            case DIA_MSG_AC:
                if(gCmd->isRequest())
                {
                    UPDATE_DIA_STATS_REQOUT(cmdCode);
                    HandleAcctReqMessage(ev);
                }
                else
                {
                    if ( (gCmd->getHeader().flags.e) == 0x01)
                    {
                        DIA_INC_INTERFACE_ERROR_MSG_COUNT(gCmd->GetDictId(),gCmd->getCommandCode());
                        UPDATE_DIA_ERR_ANSOUT();
                    }
                    else
                    {
                        UPDATE_DIA_STATS_ANSOUT(cmdCode);
                    }
                    HandleAcctAnsMessage(ev);
                }
                break;
            default:
                {
                    if(gCmd->isRequest())
                    {
                    UPDATE_DIA_STATS_REQOUT(cmdCode);
                            ret = HandleAuthReqMessage(ev);
                    }
                    else
                    {
                        if ((gCmd->getHeader().flags.e) == 0x01)
                        {
                            DIA_INC_INTERFACE_ERROR_MSG_COUNT(gCmd->GetDictId(),gCmd->getCommandCode());
                            UPDATE_DIA_ERR_ANSOUT();
                        }
                        else
                        {
                            UPDATE_DIA_STATS_ANSOUT(cmdCode);
                        }

                        HandleAuthAnsMessage(ev);
                    }
                }
        }

        if (ev.GetLength() == sizeof(DiaMsgToPeerEvt))
        {
            // Application has requested for session removal
            ITS_UINT flags = ((DiaMsgToPeerEvt*)(ev.GetData()))->flags;
            if (flags & DIA_SEND_FLAG_REL_SESSION)
            {
                const char* sessId = gCmd->getSessionId()->value().c_str();
                Event remev(DIA_APP_REM_SESS_INST, strlen(sessId) + 1, (ITS_OCTET *)sessId);
                if (itsDiaConfig.IsMsgRedundancyEnabled())
                {
                    remev.SetSource(DIA_GCS_APP_REM_SESS_INST);
                }

                ITS_USHORT dest = DIASTACK_TQ_INST;
                if (itsDiaConfig.IsQueueMgmtEnabled())
                {
                    dest = DIASTACK_SENDER_TQ_INST;
                }
                dest = DiaUtils::GetStackTQInst(sessId);
                its::Transport::PutEvent(dest, remev);
            }
        }

        /* This is where DiaMsgFlow created at Upstream is getting deleted */
        if(cmd)
        {
            delete cmd;
            cmd = NULL;
        }

    return (ITS_SUCCESS);
}


int DiaDownStreamMsgHandler::ReCreateSessionEntry(char* sessionId, ITS_OCTET* sessionData, ITS_UINT& sessionIndex, ITS_UINT& appId)
{
    SESSION_ENTRY ent = {0};
    SESSION_ENTRY *e = NULL;

    if (SessionTable::AllocateClientSessionIndex(sessionIndex) == ITS_SUCCESS)
    {
        DIA_SE_SINDX(&ent) = sessionIndex;
        DT_DBG(("Allocated SessIndex [%d]", sessionIndex));
    }
    else
    {
        DT_CRT(("Alloc Failure For Session Index"));
        return ITS_DIA_ALLOCFAIL;
    }

    DIA_SE_PEER_INST(&ent) = ((ITS_USHORT)sessionData[0] << 8) | sessionData[1];
    DIA_SE_STATE(&ent)     = AUTH_SESSION_ST_OPEN;
    DIA_SE_STYPE(&ent)     = DIA_AUTHORIZATION;
    DIA_SE_FSM_TYPE(&ent)  = STATEFUL_CLIENT_AUTH_FSM;
    DIA_SE_EVT_TYPE(&ent)  = AUTH_SESSION_EVT_RX_SSAA_OK;
    DIA_SE_CLIENTID(&ent)  = 0; // Not required
    DIA_SE_IS_AGENT(&ent)  = ITS_FALSE;
    DIA_SE_NEWLY_REP_SESSION(&ent)  = ITS_TRUE;
    DIA_SE_AGENT_TYPE(&ent)= ITS_DIA_LOCAL;
    DIA_SE_AUTH_TIMERS(&ent).timeoutDuration = (ITS_UINT)sessionData[2] << 24 |
                                        (ITS_UINT)sessionData[3] << 16 |
                                        (ITS_UINT)sessionData[4] << 8  |
                                        (ITS_UINT)sessionData[5];

    if (!DIA_SE_AUTH_TIMERS(&ent).timeoutDuration)
    {
        DIA_SE_AUTH_TIMERS(&ent).timeoutDuration = itsDiaConfig.GetAuthSessionConfig().GetTimeout();
    }

    DIA_SE_AUTH_TIMERS(&ent).lifetimeDuration = (ITS_UINT)sessionData[6] << 24 |
                                        (ITS_UINT)sessionData[7] << 16 |
                                        (ITS_UINT)sessionData[8] << 8  |
                                        (ITS_UINT)sessionData[9];
    if (!DIA_SE_AUTH_TIMERS(&ent).lifetimeDuration)
    {
        DIA_SE_AUTH_TIMERS(&ent).lifetimeDuration = itsDiaConfig.GetAuthSessionConfig().GetLifeTime();
    }

    DIA_SE_AUTH_TIMERS(&ent).gracePeriodDuration = (ITS_UINT)sessionData[10] << 24 |
                                        (ITS_UINT)sessionData[11] << 16 |
                                        (ITS_UINT)sessionData[12] << 8  |
                                        (ITS_UINT)sessionData[13];
    if (!DIA_SE_AUTH_TIMERS(&ent).gracePeriodDuration)
    {
        DIA_SE_AUTH_TIMERS(&ent).gracePeriodDuration = itsDiaConfig.GetAuthSessionConfig().GetGracePeriod();
    }

    appId = (ITS_UINT)sessionData[14] << 24 |
                          (ITS_UINT)sessionData[15] << 16 |
                          (ITS_UINT)sessionData[16] << 8  |
                          (ITS_UINT)sessionData[17];
    if (!appId)
    {
        appId = 4; // If not replicated, use whatever is known
    }

    DIA_SE_APP_ID(&ent) = appId;

    time_t currentTime = time(NULL);
    ITS_UINT duration = MAX_SWITCHOVER_TIME_CORRECTION;

    ITS_UINT sessionStartTime = (ITS_UINT)sessionData[18] << 24 |
                          (ITS_UINT)sessionData[19] << 16 |
                          (ITS_UINT)sessionData[20] << 8  |
                          (ITS_UINT)sessionData[21];

    ITS_UINT lastCCRSentTime = (ITS_UINT)sessionData[22] << 24 |
                          (ITS_UINT)sessionData[23] << 16 |
                          (ITS_UINT)sessionData[24] << 8  |
                          (ITS_UINT)sessionData[25];

    // Check if the time difference is more than the timeout, in which case start the timer
    // with 3 seconds more
    if (DIA_SE_AUTH_TIMERS(&ent).timeoutDuration < (currentTime - sessionStartTime))
    {
        duration = MAX_SWITCHOVER_TIME_CORRECTION;
    }
    else
    {
        duration = (DIA_SE_AUTH_TIMERS(&ent).timeoutDuration -
                   (currentTime - sessionStartTime)) + MAX_SWITCHOVER_TIME_CORRECTION;
    }

    SESSION_TABLE->StartTimer(sessionId, AUTH_SESSION_TIMER, duration, &ent);

    DIA_TIMER_TYPE timerToStart;
    if (DIA_SE_AUTH_TIMERS(&ent).lifetimeDuration < (currentTime - lastCCRSentTime))
    {
        timerToStart = AUTH_SESSION_GRACE_PERIOD;
        if ((DIA_SE_AUTH_TIMERS(&ent).lifetimeDuration +
             DIA_SE_AUTH_TIMERS(&ent).gracePeriodDuration) < (currentTime - lastCCRSentTime))
        {
            duration = MAX_SWITCHOVER_TIME_CORRECTION;
        }
        else
        {
            duration = ((DIA_SE_AUTH_TIMERS(&ent).lifetimeDuration +
                         DIA_SE_AUTH_TIMERS(&ent).gracePeriodDuration) -
                           (currentTime - lastCCRSentTime)) + MAX_SWITCHOVER_TIME_CORRECTION;
        }
    }
    else
    {
        timerToStart = AUTH_SESSION_LIFETIME;
        duration = (DIA_SE_AUTH_TIMERS(&ent).lifetimeDuration - (currentTime - lastCCRSentTime))
                   + MAX_SWITCHOVER_TIME_CORRECTION;
    }

    SESSION_TABLE->StartTimer(sessionId, timerToStart, duration, &ent);

    if (SESSION_TABLE->InsertEntry(ent,
                (ITS_OCTET *)sessionId,
                strlen(sessionId)) == ITS_SUCCESS)
    {
        DT_DBG(("Created Session Context for [%s]", sessionId));

        return (ITS_SUCCESS);
    }
    else
    {
        DT_CRT(("Failed to create Session Context for [%s]", sessionId));

        SESSION_TABLE->StopTimer(AUTH_SESSION_TIMER, &ent);
        SESSION_TABLE->StopTimer(timerToStart, &ent);

        return (ITS_DIA_UNABLE_TO_DELIVER);
    }
}
