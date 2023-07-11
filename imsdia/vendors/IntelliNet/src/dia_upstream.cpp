/**********************************-CPP-*************************************
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
 * LOG: $Log: dia_upstream.cpp,v $
 * LOG: Revision 3.31.12.12.4.8.2.1.2.5.4.2.2.1.4.1.2.2  2015/03/20 05:19:55  jkchaitanya
 * LOG: changes for customer tickets 714
 * LOG:
 * LOG: Revision 3.31.12.12.4.8.2.1.2.5.4.2.2.1.4.1.2.1  2014/12/18 04:32:42  jkchaitanya
 * LOG: changes for setting OriginHost as sgsn address and crash fix in stack for mandatory avp missing
 * LOG:
 * LOG: Revision 3.31.12.12.4.8.2.1.2.5.4.2.2.1.4.1  2014/11/17 05:03:39  jkchaitanya
 * LOG: changes for HA Bug Fixes
 * LOG:
 * LOG: Revision 3.31.12.12.4.8.2.1.2.5.4.2.2.1  2014/07/02 06:37:11  millayaraja
 * LOG: updated to handle answer message without mandatory field missing
 * LOG:
 * LOG: Revision 3.31.12.12.4.8.2.1.2.5.4.2  2014/06/13 06:29:13  jkchaitanya
 * LOG: reverted back the Leak fix for answer message without sessionID
 * LOG:
 * LOG: Revision 3.31.12.12.4.8.2.1.2.5.4.1  2014/06/11 09:03:27  millayaraja
 * LOG: fixed memory leak for Answer Message without Session-Id
 * LOG:
 * LOG: Revision 3.31.12.12.4.8.2.1.2.5  2014/01/06 09:22:32  cprem
 * LOG: Changes in diameter stack to support session replication. Review request 1611.
 * LOG:
 * LOG: Revision 3.31.12.12.4.8.2.1.2.4  2013/09/10 08:36:39  ncshivakumar
 * LOG: RFC6733 Changes
 * LOG:
 * LOG: Revision 3.31.12.12.4.8.2.1.2.3  2013/08/15 05:27:44  ncshivakumar
 * LOG: Generic state machine changes
 * LOG:
 * LOG: Revision 3.31.12.12.4.8.2.1.2.2  2013/07/25 04:40:20  ncshivakumar
 * LOG: Changed log level for traces dor TPS based licensing
 * LOG:
 * LOG: Revision 3.31.12.12.4.8.2.1.2.1  2013/07/25 04:38:15  ncshivakumar
 * LOG: Fix for dre crash during load.Refer bug 1639.
 * LOG:
 * LOG: Revision 3.31.12.12.4.8.2.1  2013/07/04 10:54:43  ncshivakumar
 * LOG: Updated for TPS based licensning
 * LOG:
 * LOG: Revision 3.31.12.12.4.8  2013/04/18 13:38:24  jsarvesh
 * LOG: changes done for interface stats increment for req in message
 * LOG:
 * LOG: Revision 3.31.12.12.4.7  2013/04/16 09:06:11  jsarvesh
 * LOG: changes if resultcode avp is not present in message
 * LOG:
 * LOG: Revision 3.31.12.12.4.6  2013/04/15 11:33:02  mallikarjun
 * LOG: Bug 1450 chages
 * LOG:
 * LOG: Revision 3.31.12.12.4.5  2013/04/12 04:18:33  vsarath
 * LOG: Logs improvement
 * LOG:
 * LOG: Revision 3.31.12.12.4.4  2013/04/01 05:59:13  vsarath
 * LOG: Fix for Coverity warnings
 * LOG:
 * LOG: Revision 3.31.12.12.4.3  2013/03/22 05:56:57  jvikram
 * LOG: Corrected the issues related to message handling related to same session id
 * LOG: by queuing the messages. Also included debug logs.
 * LOG:
 * LOG: Revision 3.31.12.12.4.2  2013/02/27 04:43:14  millayaraja
 * LOG: modified for interface stats
 * LOG:
 * LOG: Revision 3.31.12.12.4.1  2013/02/19 11:05:57  jsarvesh
 * LOG: dre global stats implementation
 * LOG:
 * LOG: Revision 3.31.12.12  2013/01/04 03:22:11  ncshivakumar
 * LOG: Fix for bug 721 and 772
 * LOG:
 * LOG: Revision 3.31.12.11  2012/12/21 05:31:54  ncshivakumar
 * LOG: Modified for tracing
 * LOG:
 * LOG: Revision 3.31.12.10  2012/11/20 17:39:45  pramana
 * LOG: Merged from CMAPI branch for 212-07 release
 * LOG:
 * LOG: Revision 3.31.12.6.8.2  2012/11/20 10:31:24  rgovardhan
 * LOG: merge from 00 Nov20Rel
 * LOG:
 * LOG: Revision 3.31.12.6  2012/10/15 10:55:40  vsarath
 * LOG: Backing out the changes on the revision 3.31.12.5
 * LOG:
 * LOG: Revision 3.31.12.4  2012/10/03 15:08:43  cprem
 * LOG: Merged from ERLBF branch B-DRE-0212-02
 * LOG:
 * LOG: Revision 3.31.12.3.2.2  2012/09/20 08:11:44  cprem
 * LOG: Support for multiple dictionary id configuration per peer.
 * LOG:
 * LOG: Revision 3.31.12.3.2.1  2012/09/13 11:41:50  cprem
 * LOG: Adding incoming peer instance to the DiaMsgFlow object.
 * LOG:
 * LOG: Revision 3.31.12.3  2012/09/06 13:08:45  ncshivakumar
 * LOG: fix for bug 113
 * LOG:
 * LOG: Revision 3.31.12.2  2012/09/06 11:30:46  jvikas
 * LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
 * LOG:
 * LOG: Revision 3.31.14.2  2012/08/23 11:32:29  jvikas
 * LOG: 1. Reading dictId from Peer Table Configuration
 * LOG: 2. Calling BaseGenericCmd Destructor in DiaMsgFlow Destructor
 * LOG: 3. Changed DictId ITS_UINT
 * LOG: 4. Added HandleTransConfig
 * LOG:
 * LOG: Revision 3.31.14.1  2012/08/21 06:16:25  jvikas
 * LOG: Checkin Working Modified Stack Code -Need to Cleanup and Fix Issues.
 * LOG:
 * LOG: Revision 3.31.12.1  2012/08/21 08:55:57  ksalil
 * LOG: Merge from branch B-DRE-IDIA-0100-00
 * LOG:
 * LOG: Revision 3.31.10.1  2012/08/13 09:33:42  ncshivakumar
 * LOG: code change for bug-138
 * LOG:
 * LOG: Revision 3.31  2009/08/14 06:20:01  rajeshak
 * LOG: Removed Redundant code.
 * LOG:
 * LOG: Revision 3.30  2009/08/13 10:05:33  rajeshak
 * LOG: Fix for Issue Id-2297 (ACTIVE HOT REDUNDANCY Core dump)
 * LOG: Added a check for redundancy before doing GetEventReference from event.
 * LOG:
 * LOG: Revision 3.29  2009/03/20 05:45:14  ssaxena
 * LOG: Changes DIA_CFG() to Global instance itsDiaConfig.
 * LOG:
 * LOG: Revision 3.28  2009/03/19 16:22:15  ssaxena
 * LOG: Modification done to add Redirect Agent Application.
 * LOG:
 * LOG: Revision 3.27  2009/03/19 12:34:50  nvijikumar
 * LOG: Global instance is created for the Class ITSDiaConfig to avoid function
 * LOG: call overhead as ITSDiaConfig::GetITSDiaConfig() was called max time
 * LOG:
 * LOG: Revision 3.26  2009/03/12 07:08:13  nvijikumar
 * LOG: Replaced strlen with std::string length()
 * LOG: Used GetEventReference
 * LOG:
 * LOG: Revision 3.25  2009/03/06 07:02:22  nvijikumar
 * LOG: Reverting back evt reference changes as no difference found w.r.t tps
 * LOG:
 * LOG: Revision 3.24  2009/03/03 10:26:10  nvijikumar
 * LOG: Using GetEventReference utility function to get actual
 * LOG: payload event (Performance changes)
 * LOG:
 * LOG: Revision 3.23  2009/02/20 04:42:16  nvijikumar
 * LOG: Indentation and Cleanup
 * LOG:
 * LOG: Revision 3.22  2009/02/19 14:04:10  ssaxena
 * LOG: Partial fix for the whizible issue Id 1493, 1481 and 1482.
 * LOG: Default routing failed and Relay/Proxy failed to forward
 * LOG: ASR/RAR.
 * LOG:
 * LOG: Revision 3.21  2009/02/19 13:14:55  ssaxena
 * LOG: Change in signature of HandleRedirectReqMsg from its::Event to
 * LOG: ITS_USHORT. Performance changes(Viji).
 * LOG:
 * LOG: Revision 3.20  2009/02/19 09:36:26  nvijikumar
 * LOG: Setting ptr to delete the encoded buffer of BaseCommand
 * LOG:
 * LOG: Revision 3.19  2009/02/05 09:54:10  ssaxena
 * LOG: Changes for Redirect Agent code reviews.
 * LOG:
 * LOG: Revision 3.18  2009/02/03 10:21:11  ssaxena
 * LOG: Modifications done for Redirect Agent functionality.
 * LOG:
 * LOG: Revision 3.17  2008/12/23 08:33:28  rajeshak
 * LOG: Moved and renamed InitNInsertAcctSession & InitNInsertAuthSession function
 * LOG: from dia_utils to dia_session_table
 * LOG:
 * LOG: Revision 3.16  2008/12/19 06:07:51  rajeshak
 * LOG: Issue ID: 1376
 * LOG: Feature ID: None
 * LOG: Description: Added return statement after sending Error response.
 * LOG:
 * LOG: Revision 3.15  2008/12/18 09:32:08  rajeshak
 * LOG: Removed unused codes.
 * LOG:
 * LOG: Revision 3.14  2008/12/12 18:30:48  rajeshak
 * LOG: Lightweight Decode for base AVPS
 * LOG: New Command class is introduced (BaseCommand)
 * LOG:
 * LOG: Revision 3.13  2008/12/07 09:48:08  rajeshak
 * LOG: Moved the functionality of relay to dia_relay.cpp and functionality
 * LOG: of proxy to dia_proxy.cpp. Code Cleanup
 * LOG:
 * LOG: Revision 3.12  2008/10/31 06:13:03  nvijikumar
 * LOG: IssueID:1189
 * LOG: FeatureID:none
 * LOG: Description: 1. Code Optimization and  stack tunning
 * LOG:              2. Code Cleanup
 * LOG:
 * LOG: Revision 3.11  2008/10/28 12:06:28  nvijikumar
 * LOG: IssueID: none
 * LOG: FeatureID: none
 * LOG: Description: Porting Performance changes from 3.0 branch
 * LOG:
 * LOG: Revision 3.9.2.1  2008/10/12 10:42:59  nvijikumar
 * LOG: Removed the unecessary code in HandleMessage and added few checks for
 * LOG: Pointer handling.
 * LOG:
 * LOG: Revision 3.9  2008/04/23 00:19:03  hbhatnagar
 * LOG: Provided fix for the issue 889, 875 and 869 in whizible.
 * LOG:
 * LOG: Revision 3.8  2008/04/22 21:07:23  hbhatnagar
 * LOG: Provided fix for the issues 874 and 875 in whizible.
 * LOG:
 * LOG: Revision 3.7  2008/04/16 12:17:00  hbhatnagar
 * LOG: fix for issue 720 in whizible. Miscellaneous changes and
 * LOG: code cleanup
 * LOG:
 * LOG: Revision 3.6  2008/04/08 19:09:01  avinashks
 * LOG: Removed check for MsgStatus at appropriate places and also for upstream
 * LOG: answer changed call for modify entry.
 * LOG:
 * LOG: Revision 3.5  2008/04/08 15:10:22  hbhatnagar
 * LOG: Made Changes for the MsgStatus for Proxy
 * LOG:
 * LOG: Revision 3.4  2008/04/08 14:14:52  avinashks
 * LOG: Made changes in the ProcessRelayMessage() to avoid coredumps
 * LOG:
 * LOG: Revision 3.3  2008/04/07 18:16:32  hbhatnagar
 * LOG: Fix for issues 700, 701 and 702 in whizible. Also handled the
 * LOG: request for which the RequestForwarding is possible as agents.
 * LOG: Done Error handling for requests and answers as well as sent
 * LOG: indication to application.
 * LOG:
 * LOG: Revision 3.2  2008/04/01 16:30:26  hbhatnagar
 * LOG: Changes for Proxy and Relay support 3.0 release - (Viji, Hemant)
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:32  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.44  2008/03/27 12:14:08  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.39.2.5  2007/12/16 06:09:05  hbhatnagar
 * LOG: Made changes to provide fix for issue No.11 raised during the validation
 * LOG: of bcgi ticket 1807.
 * LOG:
 * LOG: Revision 2.39.2.4  2007/05/30 09:13:57  nvijikumar
 * LOG: Validate Inbound Message with local CER
 * LOG: Fix for PBN Bug Id: 5929
 * LOG:
 * LOG: Revision 2.39.2.3  2007/05/28 14:09:34  nvijikumar
 * LOG: 1. Return Error Response if request message failed to decode.
 * LOG: 2. Handle Error Response if does not have sessionId.
 * LOG:
 * LOG: Revision 2.39.2.2  2007/04/24 09:37:27  nvijikumar
 * LOG: Process the incomming message on backup side even peer conection is not
 * LOG: established.
 * LOG:
 * LOG: Revision 2.39.2.1  2007/04/19 09:23:03  nvijikumar
 * LOG: Session Context should not be removed if Rc= 2xxx
 * LOG:
 * LOG: Revision 2.39  2007/02/26 04:53:17  nvijikumar
 * LOG: Session Context should not be removed if Rc= ITS_DIA_LIMITED_SUCCESS.
 * LOG:
 * LOG: Revision 2.38  2007/01/16 07:13:50  nvijikumar
 * LOG: Fix for Bug ID 5176.
 * LOG:
 * LOG: Revision 2.37  2007/01/04 11:18:50  nvijikumar
 * LOG: Full implementation of Accounting State Machine.
 * LOG:
 * LOG: Revision 2.36  2006/12/20 14:52:23  tpanda
 * LOG: ValidateMessage checking disabled for backup server facilitating session
 * LOG: insertion even though peer isn't in open state
 * LOG:
 * LOG: Revision 2.35  2006/12/11 13:51:25  tpanda
 * LOG: REDUNDANCY_SLOT_CHANGES are removed and code seems to be stable
 * LOG:
 * LOG: Revision 2.34  2006/12/10 13:42:42  tpanda
 * LOG: Redundancy Bug Fixes and enhancements--Transport Order Fix
 * LOG:
 * LOG: Revision 2.33  2006/11/30 18:54:24  tpanda
 * LOG: Redundancy slot changes backed out. TODO: Refer (REDUNDANCY_SLOT_CHANGES) defines
 * LOG: Failover and failback bug fixes
 * LOG:
 * LOG: Revision 2.32  2006/11/29 11:52:14  tpanda
 * LOG: Redundancy related enhancements and fixes for few bugs raised for redundancy
 * LOG:
 * LOG: Revision 2.31  2006/11/25 03:57:20  tpanda
 * LOG: Changes for Msg based redundancy
 * LOG:
 * LOG: Revision 2.30  2006/11/22 10:49:37  nvijikumar
 * LOG: Baseline PendingQ ( Failover ) Changes.
 * LOG:
 * LOG: Revision 2.29  2006/11/13 06:11:51  tpanda
 * LOG: clientId related fix for IDS
 * LOG:
 * LOG: Revision 2.28  2006/11/09 14:31:26  tpanda
 * LOG: clientId handling for IDS at the stack level
 * LOG:
 * LOG: Revision 2.27  2006/11/03 14:03:26  nvijikumar
 * LOG: 64 bit Compilation support.
 * LOG:
 * LOG: Revision 2.26  2006/10/31 13:54:16  yranade
 * LOG: Don't send error response, in response to an invalid answer
 * LOG:
 * LOG: Revision 2.25  2006/10/30 21:34:04  yranade
 * LOG: Fix issues. (Early morning 31st, Oct)
 * LOG:
 * LOG: Revision 2.24  2006/10/30 15:59:11  yranade
 * LOG: Updates to Handle RAR/RAA.
 * LOG:
 * LOG: Revision 2.23  2006/10/30 11:42:58  nvijikumar
 * LOG: Route Message throygh Auth State Machine ( only for GA1.1)
 * LOG:
 * LOG: Revision 2.22  2006/10/28 12:32:19  yranade
 * LOG: 1. Don't allow naked RAR's: Bug Fix 4634
 * LOG: 2. Cleanup SessionContext for Stateless Sessions.
 * LOG:  a. In case of server, cleanup after sending answer to peer.
 * LOG:  b. In case of client, cleanup after receiving answer from peer
 * LOG:     and sending it to application.
 * LOG:
 * LOG: Revision 2.21  2006/10/25 15:17:08  yranade
 * LOG: Error Handling related updates.
 * LOG:
 * LOG: Revision 2.20  2006/10/25 10:44:20  nvijikumar
 * LOG: Session Index feature is added for Accounting Messages.
 * LOG:
 * LOG: Revision 2.19  2006/10/25 05:15:21  nvijikumar
 * LOG: Setting SessionIndex for Accounting Request Message.
 * LOG:
 * LOG: Revision 2.18  2006/10/24 14:17:51  yranade
 * LOG: 1. ValidateMessage changes.
 * LOG: 2. Bug Fixes and Updates.
 * LOG:
 * LOG: Revision 2.17  2006/10/18 12:37:33  hbhatnagar
 * LOG: Missed out setting sIdx in messages with existing session context.(yranade)
 * LOG:
 * LOG: Revision 2.16  2006/10/17 18:46:45  yranade
 * LOG: Add some error traces.
 * LOG:
 * LOG: Revision 2.15  2006/10/17 18:13:39  yranade
 * LOG: Validate inbound message with CE stored for that peer from which message
 * LOG: is received.
 * LOG:
 * LOG: Revision 2.14  2006/10/17 17:14:13  tpanda
 * LOG: SetSessionIndex changed to setSessionIndex
 * LOG:
 * LOG: Revision 2.13  2006/10/17 09:54:20  nanaparthi
 * LOG: Changes for Solaris Build.
 * LOG:
 * LOG: Revision 2.12  2006/10/16 16:54:06  nvijikumar
 * LOG: Baseline Accounting Statemachine implementation.
 * LOG:
 * LOG: Revision 2.11  2006/10/16 16:02:58  yranade
 * LOG: Bug-Fixes and Updates.
 * LOG:
 * LOG: Revision 2.10  2006/10/16 06:32:46  yranade
 * LOG: AuthSessionTimer Handling. AuthSM related updates.
 * LOG:
 * LOG: Revision 2.9  2006/10/13 16:50:44  yranade
 * LOG: Fix 4448. Update error handling.
 * LOG:
 * LOG: Revision 2.8  2006/10/09 13:41:39  yranade
 * LOG: Get RealmRouting working.
 * LOG:
 * LOG: Revision 2.7  2006/10/09 11:32:58  yranade
 * LOG: Updates for Stateless server sessions.
 * LOG:
 * LOG: Revision 2.6  2006/10/09 06:30:44  yranade
 * LOG: Add some traces.
 * LOG:
 * LOG: Revision 2.5  2006/10/07 12:48:34  yranade
 * LOG: Pass correct SESSION_ENTRY context to SM.
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

#include <dia_cmn.h>
#include <dia_utils.h>
#include <dia_trace.h>
#include <dia_err.h>
#include <dia_msg_router.h>
#include <dia_upstream.h>
#include <dia_realm_table.h>
#include <dia_session_table.h>
#include <dia_session_auth_fsm.h>
#include <dia_session_acct_fsm.h>
#include <dia_msg_router.h>
#include <dia_relay.h>
#include <dia_proxy.h>
#include <dia_redirect.h>
#include <dia_stack.h>
#include <dia_tracer.h>
#include <DiameterDictionaryStats.h>
#include <dia_rate_filter.h>
#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
using namespace diameter;
using namespace diameter::base;
#endif
extern "C" ITSDLLAPI unsigned int LICENSE_AllowedMsgRate(void);

/* Local Routing Handlers */
int
DiaUpStreamMsgHandler::HandleLocalAcctAnsMessage(DIA_BASE_CMD *&cmd, its::Event &ev)
{
    int ret = ITS_SUCCESS;
    ITS_USHORT trInst = ITS_GET_CTXT(ev.GetData());
    DIA_BASE_CMD *msg = (DIA_BASE_CMD *)cmd;
    std::string sessionId;
    ITS_UINT resultCode = ITS_DIA_SUCCESS;
    ITS_UINT recType =0;

    DT_DBG(("HandleLocalAcctAnsMessage"));

    /* If Answer is received from the Peer and it doesn't
       contain resultCode, we treat it as succesfull indication
       that the User is Authorized
    */
    if (msg->getResultCode())
    {
        resultCode = msg->getResultCode()->value();
    }

    if (msg->getSessionId() != NULL)
    {
        sessionId = msg->getSessionId()->value();

        /**
         * Checking it recordtype exists and then copy.
         * fix for core dump
         */
        if (msg->getAccountingRecordType())
        {
            recType = msg->getAccountingRecordType()->value();
        }

        SESSION_ENTRY *ent = NULL;
        DT_DBG(("SessionId = %s", sessionId.c_str()));

        if (SESSION_TABLE->FindEntry(ent,
                                     (ITS_OCTET *)sessionId.c_str(),
                                     (sessionId.length())) != ITS_SUCCESS)
        {
            DT_ERR(("Entry Not found "));
            ret = DiaErrHandler::HandleError(trInst, msg,
                                             SEND_ERROR_TO_PEER,
                                             ITS_DIA_MISSING_AVP);

            delete cmd;
            cmd = NULL;
            return ret;
        }

        /**
         * Verifying whether Hop-by-hop id received in answer is same as
         * stored in the session entry. Fix for the issue 701 raised during
         * unit testing of relay feature.
         */
        DIA_HDR &header = (DIA_HDR&)msg->getHeader();
        if (!DIA_SE_IS_AGENT(ent) && (header.hh != DIA_SE_RX_HH(ent)))
        {
            //back-up redudant node  doesn't need to check the hop-by-hop id
            ITS_NODE_STATE state;
            if ( !itsDiaConfig.IsMsgRedundancyEnabled() ||
                 ((ITS_GetNodeState(&state) == ITS_SUCCESS) &&
                    (state == ITS_STATE_PRIMARY) ))
            {
                UPDATE_DIA_STATS_MISC(DIA_HBYHDROPMSGS);
                DT_ERR(("Invalid Hop-by-Hop id received in answer message"));
                /* update the stats for validate failure invalid msgs */
                DIA_INC_INTERFACE_INVALID_MSG_COUNT((cmd->GetDictId()),(cmd->getCommandCode()));
                delete cmd;
                cmd = NULL;
                return !ITS_SUCCESS;
            }
        }

        /**
         * Save the resultCode in the session entry
         * if the the node is agent
         */

        //NOTE: Result Code received in the Answer is only needed for Proxy
        if (DIA_SE_IS_AGENT(ent))
        {
            /**
             * Verifying whether the message is proxiable.
             * Fix for issue 702 in whizible raised during unit
             * testing for proxy feature.
             */
            if (!cmd->isProxyable())
            {
                DT_ERR(("Non-Proxiable message received for Agent"));
                /* update the stats for validate failure invalid msgs */
                DIA_INC_INTERFACE_INVALID_MSG_COUNT((cmd->GetDictId()),(cmd->getCommandCode()));

                delete cmd;
                cmd = NULL;
                return !ITS_SUCCESS;
            }
            DIA_SE_RESULT_CODE(ent) = resultCode;
        }
        else
        {
            /**
             * Fix for issue 874 in whizible.
             * If the Node is not agent (i.e. msg is for local Consumption)
             * then check for the duplicate Answer as defined in the section 3
             * of rfc3588 under End-To-End Id. Match the EE Id with the session
             * entry. If same that means correct answer received. Make
             * EE Id as 0 for the session. If duplicate answer received check
             * whether EE is 0 then Discard sliently.
             */
            if (DIA_SE_RX_EE(ent) == 0)
            {
                 DT_DBG(("Duplicate Answer recvd for the session. Discarding" \
                         " Message..."));
                delete cmd;
                cmd  = NULL;
                return !ITS_SUCCESS;
            }

            if (DIA_SE_RX_EE(ent) == header.ee)
            {
                DT_DBG(("Answer Received with correct End-To-End id."));
                DIA_SE_RX_EE(ent) = 0;
            }
            else
            {
                //back-up redudant node  doesn't need to check the hop-by-hop id
                ITS_NODE_STATE state;
                if (!itsDiaConfig.IsMsgRedundancyEnabled()||
                   ((ITS_GetNodeState(&state) == ITS_SUCCESS) &&
                   (state == ITS_STATE_PRIMARY) ))
                {
                    DT_WRN(("Answer Received with In-correct End-To-End id." \
                         " Discarding Message..."));
                    /* update the stats for validate failure invalid msgs */
                    DIA_INC_INTERFACE_INVALID_MSG_COUNT((cmd->GetDictId()),(cmd->getCommandCode()));
                    delete cmd;
                    cmd  = NULL;
                    return !ITS_SUCCESS;
                }
            }
        }

        /**
         * If Entry is found check whether this message is to be
         * relayed.
         */
        /* Set the saved clientid in the message */
        msg->setClientId(DIA_SE_CLIENTID(ent));

        /* Set the saved index, in the message */
        msg->setSessionIndex(DIA_SE_SINDX(ent));

        if (DIA_SE_AGENT_TYPE(ent) == ITS_DIA_RELAY)        //relay processing
        {
            DiaRelayHandler::HandleAnsMessage(cmd, ent);
        }
        else if(DIA_SE_AGENT_TYPE(ent) == ITS_DIA_PROXY)    //proxy processing
        {
            DiaTracer::SessTraceCheckAndLog(msg, ent, sessionId.c_str(), trInst);
            ret = DiaProxyHandler::HandleProxyAcctAnsMsg(cmd, ent, ev);
            //if ret == fsm update , modify session entry can be removed from
            //proxy handling and can be done at end
            return ret;
        }
        else    //processing for local
        {
            DT_DBG(("FSM Type = %s",
                         STATE_MACHINE_TYPE_TO_TEXT(DIA_SE_FSM_TYPE(ent))));

            switch (DIA_SE_ACC_FSM_TYPE(ent))
            {
            case STATEFUL_SERVER_ACCT_FSM:
            case STATELESS_SERVER_ACCT_FSM:
                /* Stateless and Stateful Server Acct FSM */
                break;
            case CLIENT_ACCT_FSM:
            {
                if (cmd->getCommandCode() != DIA_MSG_AC)
                {
                    DT_ERR((" Non Accounting Answer Received "));
                    return (!ITS_SUCCESS);
                }
                if (!cmd->isError())
                {
                    ITS_UINT recType;
                    recType = msg->getAccountingRecordType()->value();

                    if (resultCode >= ITS_DIA_SUCCESS_MIN_RANGE &&
                        resultCode <= ITS_DIA_SUCCESS_MAX_RANGE)
                    {
                        DT_DBG((" Successful Accounting Answer Received"));
                        DIA_SE_EVT_TYPE(ent) = ACCT_SESSION_EVT_RX_ACA_OK;
                    }
                    else if ((recType ==  AccountingRecordType::EVENT_RECORD) ||
                             (recType ==  AccountingRecordType::STOP_RECORD))
                    {
                        DT_WRN((" Failed Accounting Answer Received"));
                        DIA_SE_EVT_TYPE(ent) = ACCT_SESSION_EVT_RX_ACA_FAIL;
                    }
                    else
                    {
                        DT_WRN((" Accounting Answer Received"));
                        if (msg->countAccountingRealtimeRequired() &&
                            (msg->getAccountingRealtimeRequired()->value()
                             == AccountingRealtimeRequired::GRANT_AND_LOSE))
                        {
                            DT_DBG(("AcctingRealtimeRequired==GRANT_AND_LOSE"));
                            DIA_SE_EVT_TYPE(ent) =
                                          ACCT_SESSION_EVT_RX_ACA_FAIL_AND_GAL;
                        }
                        else
                        {
                            DT_DBG(("AcctingRealtimeRequired!=GRANT_AND_LOSE"));
                            DIA_SE_EVT_TYPE(ent) =
                                           ACCT_SESSION_EVT_RX_ACA_FAIL_NOT_GAL;
                        }
                    }
                    ret = clientAcctFsm.SubmitToSM(ent, &ev.GetEvent());
                }
                else
                {
                    /* Received Error Response */
                    DiaMsgRouter::SendMsgToApp(ent, &ev.GetEvent());
                    if (DIA_SE_STYPE(ent) == DIA_ACCOUNTING)
                    {
                        if((ret = SESSION_TABLE->RemoveEntry(ent,
                                                 (ITS_OCTET *)sessionId.c_str(),
                                                   (sessionId.length()))) 
                                                        != ITS_SUCCESS)
                        {
                            DT_ERR(("Failed to Remove Session Context"));
                        }
                    }
                    else
                    {
                        SESSION_TABLE->StopTimer(ACCT_SESSION_INTERIM_INTERVAL,
                                                 ent);
                        ret = FSM_STATE_UPDATE;
                        DIA_SE_ACC_STATE(ent) = ACCT_SESSION_ST_IDLE;
                    }
                }
                if (ret == FSM_STATE_UPDATE)
                {
                    if ((ret = SESSION_TABLE->ModifyEntry(ent,
                                                 (ITS_OCTET *)sessionId.c_str(),
                                                   sessionId.size()))
                            != ITS_SUCCESS)
                    {
                        DT_ERR(("Failed to update Session Context"));
                    }
                }
                break;
            }
            default:
                DT_ERR(("Invalid FSM Type"));
                delete cmd;
                cmd = NULL;
                return ret;
            }
        }

        if (ret == FSM_STATE_UPDATE)
        {
            if (SESSION_TABLE->ModifyEntry(ent,
                                          (ITS_OCTET *)sessionId.c_str(),
                                          sessionId.size())
                              == ITS_SUCCESS)
            {
                 DT_DBG(("Succesfully Updated Session Context"));
            }
        }
        else if (ret == ITS_EBADSTATE)
        {
            DT_ERR(("Failed to SubmitToSM"));
            delete cmd;
            cmd = NULL;
            return ret;
        }
    }
    else
    {
        DT_ERR(("Ans Message without SessionId"));
        if (cmd->isError())
        {
            /* Received Error Response */
            ret = DiaMsgRouter::SendPeerMsgToApp((DIA_BASE_CMD *)cmd);
            return ret;
        }

        delete cmd;
        cmd = NULL;
        return (!ITS_SUCCESS);
    }

    return (ITS_SUCCESS);
}

int
DiaUpStreamMsgHandler::HandleLocalAcctReqMessage(DIA_BASE_CMD *&cmd, its::Event &ev,
                                                 bool isProxy)
{
    int ret;
    DiaSocketTransport *tr = NULL;
    ITS_USHORT trInst = ITS_GET_CTXT(ev.GetData());
    DIA_BASE_CMD *msg = (DIA_BASE_CMD *)cmd;
    std::string sessionId;
    PEER_ENTRY *peer = NULL;
    ITS_NODE_STATE state;
    DIA_GEN_CMD *ce = NULL;

    DT_DBG(("HandleLocalAcctReqMessage"));

    /*
     * For redundant backup node, don't throw error
     * if peer is not connected yet.
     */
    if ((ev.GetSource() != DIA_GCS_NET_INST) ||
        ((ITS_GetNodeState(&state) == ITS_SUCCESS) &&
        state == ITS_STATE_PRIMARY))
    {
        tr = trTable[trInst];
        if (tr == NULL)
        {
            DT_ERR(("Invalid transport"));

            if (cmd)
            {
                delete cmd;
                cmd = NULL;
            }
            return (ITS_EBADTRANSPORT);
        }

        peer = tr->GetPeer();
        /* ce = DIA_PE_CE_CACHE(peer); */
        ce = (DIA_GEN_CMD *)itsDiaConfig.GetLocalCER();
    }

    if ((ret = DiaMsgRouter::ValidateMessage(ce, msg))
          != ITS_SUCCESS)
    {
        /* for redundant backup node, don't throw error
         * response if message validate fails
         */
        if ((ev.GetSource() != DIA_GCS_NET_INST) ||
           ((ITS_GetNodeState(&state) == ITS_SUCCESS) &&
           state == ITS_STATE_PRIMARY))
        {
           DT_ERR(("Validate Request Failure...NO_COMMON_APP"));
           ret = DiaErrHandler::HandleError(trInst, msg,
                                         SEND_ERROR_TO_PEER,
                                         ret);

           delete cmd;
           cmd = NULL;
           return ret;
        }
    }

    if (msg && msg->getSessionId() != NULL)
    {
        sessionId = msg->getSessionId()->value();

        DT_DBG(("SessionId = %s", sessionId.c_str()));

        SESSION_ENTRY ent;
        SESSION_ENTRY *e = NULL;

        if (SESSION_TABLE->FindEntry(e,
                                     (ITS_OCTET *)sessionId.c_str(),
                                     (sessionId.length())) != ITS_SUCCESS)
        {
            DT_DBG(("Entry Not found "));

            /**
             * Memsetting the session entry variable
             */
            memset(&ent,0,sizeof(SESSION_ENTRY));
            bool isStateless = false;

            /* This is the first inbound request */
           /* default agent flag is off, set if required */
            DIA_SE_IS_AGENT(&ent)     = false;
            DIA_SE_AGENT_TYPE(&ent)   = ITS_DIA_LOCAL;
            DIA_SE_ACC_FSM_TYPE(&ent) = STATEFUL_SERVER_ACCT_FSM;
            DIA_SE_MSG_STATUS(&ent)   = REQ_RCV_FROM_PEER;

#if 0
	    if (!(msg->getAccountingRealtimeRequired()) ||
                (msg->getAccountingRealtimeRequired()->value() !=
                 AccountingRealtimeRequired::DELIVER_AND_GRANT))
            {
                DT_DBG(("AccountingRealtimeRequired != DELIVER_AND_GRANT"));

                isStateless = true;
                DIA_SE_ACC_FSM_TYPE(&ent) = STATELESS_SERVER_ACCT_FSM;
            }
#endif
//Fix for issue 113, to make the accounting request stateful, so that DRE maintain the session

            SESSION_ENTRY *pEntry = &ent;

            ret = SESSION_TABLE->InsertAcctSession(msg, sessionId.c_str(),
                                                   pEntry, ev, isStateless);
            return ret;
        }
        else
        {
            /* Save off the header */
            DIA_SE_RX_FLAGS(e) = msg->getHeader().flags;
            DIA_SE_RX_HH(e)    = msg->getHeader().hh;
            DIA_SE_RX_EE(e)    = msg->getHeader().ee;

            /**
             * Fix for the issue 875 in whizible. Updating the transport
             * everytime a request is received.(Updating the fix for issue
             * 875 by updating proper peer Transport for ASR and RAR)
             */
            ITS_UINT cmdCode = msg->getCommandCode();
            if ( cmdCode == DIA_MSG_AS ||
                 cmdCode == DIA_MSG_RA)
            {
                DIA_SE_PEER_INST_AGENT(e)= trInst;
            }
            else
            {
                DIA_SE_PEER_INST(e)= trInst;
            }

            /* Set the saved clientid in the message */
            msg->setClientId(DIA_SE_CLIENTID(e));

           /* Set the saved index, in the message */
            msg->setSessionIndex(DIA_SE_SINDX(e));

            /* If session type is Authorized considering as stateless SM.
               Because even if submit to statefull SM seperate timer need
               not to be started.
             */
            if ((DIA_SE_STYPE(e) == DIA_AUTHORIZATION) &&
                (DIA_SE_STATE(e) == AUTH_SESSION_ST_OPEN))
            {
                DT_DBG(("Received Accounting Request on Authorized Session"));
                DIA_SE_ACC_FSM_TYPE(e) = STATELESS_SERVER_ACCT_FSM;
            }
            DT_DBG(("Found Session Context for :: %s", sessionId.c_str()));

        }

        if (msg->getAuthApplicationId())
        {
            DIA_SE_APP_ID(e) = msg->getAuthApplicationId()->value();
        }
        else
        {
            DIA_SE_APP_ID(e) = msg->getHeader().appId;
        }

        switch (DIA_SE_ACC_FSM_TYPE(e))
        {
        /* Stateful Server Acct FSM */
        case STATEFUL_SERVER_ACCT_FSM:
        {
            DIA_SE_EVT_TYPE(e) = ACCT_SESSION_EVT_REQUEST_ACCESS;
            ret = statefulServerAcctFsm.SubmitToSM(e, &ev.GetEvent());
            if (SESSION_TABLE->ModifyEntry(e, (ITS_OCTET *)sessionId.c_str(),
                                           sessionId.size()) != ITS_SUCCESS)
            {
                DT_ERR(("Failed to update session context"));
            }
            break;
        }
        case STATELESS_SERVER_ACCT_FSM:
        {
            ret = DiaMsgRouter::SendMsgToApp(e, &ev.GetEvent());
            if (ret != ITS_SUCCESS)
            {
                DT_ERR(("Failed to SendMsgToApp"));
                ret = DiaErrHandler::HandleError(trInst, msg,
                                                 SEND_ERROR_TO_PEER,
                                                 ITS_DIA_UNABLE_TO_DELIVER);
                return ret;
            }
            break;
        }
        case CLIENT_ACCT_FSM:
            DT_ERR(("Invalid Msg"));
            break;
        default:
            DT_DBG((" Invalid FSM Type"));
            break;
        }
    }
    else
    {
        DT_DBG(("Application Level Message without SessionId"));
        if (msg)
        {
            ret = DiaErrHandler::HandleError(trInst, msg,
                                             SEND_ERROR_TO_PEER,
                                             ITS_DIA_UNKNOWN_SESSION_ID);
            if (cmd)
            {
                delete cmd;
                cmd = NULL;
            }

        }
        return ret;
    }

    return (ITS_SUCCESS);
}

int
DiaUpStreamMsgHandler::HandleLocalAuthAnsMessage(DIA_BASE_CMD *&cmd, its::Event &ev)
{
    int ret = ITS_SUCCESS;
    ITS_USHORT trInst = ITS_GET_CTXT(ev.GetData());
    DIA_BASE_CMD *msg = (DIA_BASE_CMD *)cmd;
    std::string sessionId;
    ITS_UINT resultCode = ITS_DIA_SUCCESS;
    bool isStateFull = true;

    DT_DBG(("HandleLocalAuthAnsMessage"));

    /* If Answer is received from the Peer and it doesn't
       contain resultCode, we treat it as succesfull indication
       that the User is Authorized
    */
    if (msg->getResultCode())
    {
        resultCode = msg->getResultCode()->value();
    }

    if (msg->getSessionId() != NULL)
    {
        sessionId = msg->getSessionId()->value();

        SESSION_ENTRY *ent = NULL;
        DT_DBG(("SessionId = %s", sessionId.c_str()));

        if (SESSION_TABLE->FindEntry(ent,
                                     (ITS_OCTET *)sessionId.c_str(),
                                     (sessionId.length())) != ITS_SUCCESS)
        {
            DT_ERR(("Entry Not found...Discarding"));
            delete cmd;
            cmd = NULL;
            return ret;
        }

        /**
         * Verifying whether Hop-by-hop id received in answer is same as
         * stored in the session entry. Fix for the issue 701 raised during
         * unit testing of relay feature.
         */
        DIA_HDR &header = (DIA_HDR&)msg->getHeader();
        if (DIA_SE_NEWLY_REP_SESSION(ent) || (!DIA_SE_IS_AGENT(ent) && (header.hh != DIA_SE_RX_HH(ent))))
        {
            //back-up redudant node  doesn't need to check the hop-by-hop id
            ITS_NODE_STATE state;
            if ( !itsDiaConfig.IsMsgRedundancyEnabled() ||
                 ((ITS_GetNodeState(&state) == ITS_SUCCESS) &&
                    (state == ITS_STATE_PRIMARY) ))
            {
                UPDATE_DIA_STATS_MISC(DIA_HBYHDROPMSGS);
                DT_ERR(("Invalid Hop-by-Hop id received in answer message"));
                /* update the stats for validate failure invalid msgs */
                DIA_INC_INTERFACE_INVALID_MSG_COUNT((cmd->GetDictId()),(cmd->getCommandCode()));
                delete cmd;
                cmd = NULL;
                return !ITS_SUCCESS;
            }
        }

        /**
         * Save the resultCode in the session entry
         * if the the node is agent
         */

        //Note: For PROXY ONLY
        if (!DIA_SE_IS_AGENT(ent))
        {
            /**
             * Fix for issue 874 in whizible.
             * If the Node is not agent (i.e. msg is for local Consumption)
             * then check for the duplicate Answer as defined in the section 3
             * of rfc3588 under End-To-End Id. Match the EE Id with the session
             * entry. If same that means correct answer received. Make
             * EE Id as 0 for the session. If duplicate answer received check
             * whether EE is 0 then Discard sliently.
             */
            if (!DIA_SE_NEWLY_REP_SESSION(ent))
            {
            if (DIA_SE_RX_EE(ent) == 0)
            {
             DT_DBG(("Duplicate Answer received for the session. Discarding" \
                     " Message..."));
                delete cmd;
                cmd  = NULL;
                return !ITS_SUCCESS;
            }

            if (DIA_SE_RX_EE(ent) == header.ee)
            {
                DT_DBG(("Answer Received with correct End-To-End id."));
                DIA_SE_RX_EE(ent) = 0;
            }
            else
            {
                DT_WRN(("Answer Received with In-correct End-To-End id." \
                         " Discarding Message..."));
                /* update the stats for validate failure invalid msgs */
                DIA_INC_INTERFACE_INVALID_MSG_COUNT((cmd->GetDictId()),(cmd->getCommandCode()));
                delete cmd;
                cmd  = NULL;
                return !ITS_SUCCESS;
            }
        }
        }
        else
        {
            /**
             * Verifying whether the message is proxiable.
             * Fix for issue 702 in whizible raised during unit
             * testing for proxy feature.
             */
            if (!cmd->isProxyable())
            {
                DT_ERR(("Non-Proxiable message received for Agent"));

                /* update the stats for validate failure invalid msgs */
                DIA_INC_INTERFACE_INVALID_MSG_COUNT((cmd->GetDictId()),(cmd->getCommandCode()));

                delete cmd;
                cmd  = NULL;
                return !ITS_SUCCESS;
            }
            DIA_SE_RESULT_CODE(ent) = resultCode;
        }

        /**
         * If Entry is found check whether this message is to be
         * relayed.
         */
        //DIA_SE_RX_HDR(ent) = msg->getHeader();
        /* Set the saved clientid in the message */
        msg->setClientId(DIA_SE_CLIENTID(ent));
        /* Set the saved index, in the message */
        msg->setSessionIndex(DIA_SE_SINDX(ent));

        if (DIA_SE_AGENT_TYPE(ent) == ITS_DIA_RELAY)        //relay processing
        {
            DT_DBG(("Answer Message received is to be relayed."));
            DiaRelayHandler::HandleAnsMessage(cmd, ent);
        }
        else if(DIA_SE_AGENT_TYPE(ent) == ITS_DIA_PROXY)    //proxy processing
        {
            DT_DBG(("Answer Message received is to be proxied."));
            DiaTracer::SessTraceCheckAndLog(msg, ent, sessionId.c_str(), trInst);
            ret = DiaProxyHandler::HandleProxyAuthAnsMsg(cmd, ent, ev);
            //if ret == fsm update , modify session entry can be removed from
            //proxy handling and can be done at end
            return ret;
        }
        else    //processing for local
        {
            /* states based on existence (or lack of)
               Auth-Session-State AVP
               If AuthSessionState AVP is present and
               the value is NO_STATE_MAINTAINED then it's
               Stateless Server else Stateful Server
            */
            DT_DBG(("FSM Type = %s",
                     STATE_MACHINE_TYPE_TO_TEXT(DIA_SE_FSM_TYPE(ent))));
            switch (DIA_SE_FSM_TYPE(ent))
            {
            case STATEFUL_SERVER_AUTH_FSM:
            {
                /* Stateful Server Auth FSM */
                switch (msg->getCommandCode())
                {
                case DIA_MSG_AS:
                    if ((resultCode >= ITS_DIA_SUCCESS_MIN_RANGE &&
                         resultCode <= ITS_DIA_SUCCESS_MAX_RANGE) &&
                        !cmd->isError())
                    {
                        DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_RX_ASA_OK;
                    }
                    else
                    {
                        DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_RX_ASA_FAIL;
                    }
                    break;
                case DIA_MSG_RA:
                    if ((resultCode >= ITS_DIA_SUCCESS_MIN_RANGE &&
                         resultCode <= ITS_DIA_SUCCESS_MAX_RANGE) &&
                        !cmd->isError())
                    {
                        DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_RX_RAA_OK;
                    }
                    else
                    {
                        DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_RX_RAA_FAIL;
                    }
                    break;
                default:
                    DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_RX_SSAA_OK;
                    break;
                }
                ret = statefulServerAuthFsm.SubmitToSM(ent, &ev.GetEvent());
                break;
            }
            case STATELESS_SERVER_AUTH_FSM:
            {
                /* Stateless Server Auth FSM */
                ret = DiaMsgRouter::SendMsgToApp(ent, &ev.GetEvent());
                break;
            }
            case STATEFUL_CLIENT_AUTH_FSM:
            {
                switch (msg->getCommandCode())
                {
                case DIA_MSG_ST:
                    DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_RX_STA;
                    break;
                default:
                    if ((resultCode >= ITS_DIA_SUCCESS_MIN_RANGE &&
                         resultCode <= ITS_DIA_SUCCESS_MAX_RANGE) &&
                        !cmd->isError())
                    {
                        DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_RX_SSAA_OK;
                    }
                    else
                    {
                        if(resultCode >= ITS_DIA_PROT_ERR_MIN_RANGE && resultCode <= ITS_DIA_PROT_ERR_MAX_RANGE)
                        {
                            DT_ERR(("Received Error Response for CmdCode = %d",
                                        cmd->getCommandCode()));
                        }
                        else
                        {
                            DT_WRN(("Received 4xxx/5xxx Response for CmdCode = %d",
                                        cmd->getCommandCode()));
                        }
                        DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_RX_SSAA_FAIL;
                    }
                    break;
                }

                if (DIA_SE_STATE(ent) == AUTH_SESSION_ST_PENDING)
                {
                    /* IF Auth-State-AVP Not Present or has STATE_MAINTAINED
                       it means Stateful
                    */

                    if (msg->getAuthSessionState())
                    {
                        /* State is not maintained on the server;
                           Update the State Machine Type, to Stateless Client
                           and Submit the message to Stateless Client SM
                        */
                        if (msg->getAuthSessionState()->value() ==
                                 AuthSessionState::NO_STATE_MAINTAINED)
                        {
                            DIA_SE_FSM_TYPE(ent) = STATELESS_CLIENT_AUTH_FSM;
                            isStateFull = false;

                            ret = statelessClientAuthFsm.SubmitToSM(ent,
                                                                &ev.GetEvent());
                            break;
                        }
                    }
                }

                ret = statefulClientAuthFsm.SubmitToSM(ent, &ev.GetEvent());
                break;
            }
            case STATELESS_CLIENT_AUTH_FSM:
                switch (msg->getCommandCode())
                {
                case DIA_MSG_ST:
                case DIA_MSG_AS:
                    DT_ERR(("STA/ASA recvd for Stateless Client ..Discarding"));
                    delete cmd;
                    cmd = NULL;
                    return (ITS_SUCCESS);
                default:
                    if (cmd->isError())
                    {
                        DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_RX_SSAA_FAIL;
                    }
                    else
                    {
                        DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_RX_SSAA_OK;
                    }

                    if (DIA_SE_STATE(ent) == AUTH_SESSION_ST_PENDING ||
                        DIA_SE_NEWLY_REP_SESSION(ent))
                    {
                        /* State is maintained on the server;
                           Update the State Machine Type, to Stateful Client
                           and Submit the message to Stateful Client SM
                        */
                        if (msg->getAuthSessionState() &&
                            msg->getAuthSessionState()->value() ==
                            AuthSessionState::NO_STATE_MAINTAINED)
                        {
                            DIA_SE_FSM_TYPE(ent) = STATELESS_CLIENT_AUTH_FSM;
                            isStateFull = false;
                            ret = statelessClientAuthFsm.SubmitToSM(ent,
                                                            &ev.GetEvent());
                        }
                        else
                        {
                            DIA_SE_FSM_TYPE(ent) = STATEFUL_CLIENT_AUTH_FSM;
                            ret = statefulClientAuthFsm.SubmitToSM(ent,
                                                                &ev.GetEvent());
                        }
                    }

                }
                break;

            case RELAY_AGENT_FSM:
            {
                /*
                 * Error occurred hence deleting the message
                 */
                if(cmd)
                {
                    delete cmd;
                    cmd =NULL;
                }
                return ret;
                break;
            }
            default:
                DT_ERR(("Invalid FSM Type"));
                delete cmd;
                cmd = NULL;
                return ret;
            }
        }

        if (isStateFull && DIA_SE_NEWLY_REP_SESSION(ent))
        {
            DIA_SE_NEWLY_REP_SESSION(ent) = ITS_FALSE;
        }

        if (ret == FSM_STATE_UPDATE)
        {
            if (SESSION_TABLE->ModifyEntry(ent, (ITS_OCTET *)sessionId.c_str(),
                                          sessionId.size()) == ITS_SUCCESS)
            {
                 DT_DBG(("Succesfully Updated Session Context"));
            }
        }
        else if (ret == ITS_EBADSTATE)
        {
            DT_ERR(("Failed to SubmitToSM"));
            delete cmd;
            cmd = NULL;
            return ret;

        }

    }
    else
    {
        DT_ERR(("Ans Message without SessionId"));
        if (cmd->isError())
        {
            /* Received Error Response */
            ret = DiaMsgRouter::SendPeerMsgToApp((DIA_BASE_CMD *)cmd);
            return (ret);
        }

        delete cmd;
        cmd = NULL;
        return (!ITS_SUCCESS);
    }

    return (ITS_SUCCESS);
}

int
DiaUpStreamMsgHandler::HandleLocalAuthReqMessage(DIA_BASE_CMD *&cmd,
                                                 its::Event &ev, bool isProxy)
{
    int ret;
    DiaSocketTransport *tr = NULL;
    ITS_USHORT trInst = ITS_GET_CTXT(ev.GetData());
    DIA_BASE_CMD *msg = (DIA_BASE_CMD *)cmd;
    std::string sessionId;
    PEER_ENTRY *peer = NULL;
    ITS_NODE_STATE state;
    DIA_GEN_CMD *ce = NULL;

    DT_DBG(("HandleLocalAuthReqMessage"));

    ce = (DIA_GEN_CMD *)itsDiaConfig.GetLocalCER();

    if ((ret = DiaMsgRouter::ValidateMessage(ce, msg)) != ITS_SUCCESS)
    {
        /* for redundant backup node, don't throw error
         * response if message validate fails
         */
           DT_ERR(("Validate Request Failure...NO_COMMON_APP"));
        if ((ev.GetSource() != DIA_GCS_NET_INST) ||
           ((ITS_GetNodeState(&state) == ITS_SUCCESS) &&
           state == ITS_STATE_PRIMARY))
        {
           DT_ERR(("Validate Request Failure...NO_COMMON_APP"));
           ret = DiaErrHandler::HandleError(trInst, msg,
                                         SEND_ERROR_TO_PEER,
                                         ret);

           delete cmd;
           cmd = NULL;
           return ret;
        }
    }

    if (msg && msg->getSessionId() != NULL)
    {
        sessionId = msg->getSessionId()->value();

        DT_DBG(("SessionId = %s", sessionId.c_str()));

        SESSION_ENTRY ent;
        SESSION_ENTRY *e = NULL;

        if (SESSION_TABLE->FindEntry(e,
                                     (ITS_OCTET *)sessionId.c_str(),
                                     (sessionId.length())) != ITS_SUCCESS)
        {
            DT_DBG(("Entry Not found "));

            /**
             * Memsetting the session entry variable
             */
            memset(&ent, 0, sizeof(SESSION_ENTRY));

            /* Session Termination, Abort Session and Re-Auth Requests
               need to have an existing session context in db
            */
            switch (msg->getCommandCode())
            {
            case DIA_MSG_ST:
            case DIA_MSG_AS:
            case DIA_MSG_RA:
                ret = DiaErrHandler::HandleError(trInst, msg,
                                                 SEND_ERROR_TO_PEER,
                                                 ITS_DIA_UNKNOWN_SESSION_ID);
                delete cmd;
                cmd = NULL;
                return ret;
            }

            /* This is the first inbound request */
           /* default agent flag is off, set if required */

            bool isStateless = false;

            DIA_SE_IS_AGENT(&ent)  = false;
            DIA_SE_AGENT_TYPE(&ent)= ITS_DIA_LOCAL;
            DIA_SE_FSM_TYPE(&ent) = STATEFUL_SERVER_AUTH_FSM;
            DIA_SE_MSG_STATUS(&ent)   = REQ_RCV_FROM_PEER;

            if (msg->getAuthSessionState())
            {
                if (msg->getAuthSessionState()->value() ==
                         AuthSessionState::NO_STATE_MAINTAINED)
                {
                    isStateless = true;
                    DIA_SE_FSM_TYPE(&ent) = STATELESS_SERVER_AUTH_FSM;
                }
            }
            SESSION_ENTRY *pEntry = &ent;
            ret = SESSION_TABLE->InsertAuthSession(msg, sessionId.c_str(),
                                                   pEntry, ev, isStateless);
            return ret;
        }
        else
        {
            /* Save off the header */
            DIA_SE_RX_FLAGS(e) = msg->getHeader().flags;
            DIA_SE_RX_HH(e)    = msg->getHeader().hh;
            DIA_SE_RX_EE(e)    = msg->getHeader().ee;

            /**
             * Fix for the issue 875 in whizible. Updating the transport
             * everytime a request is received. (Updating the fix for issue
             * 875 by updating proper peer Transport for ASR and RAR)
             */
            ITS_UINT cmdCode = msg->getCommandCode();
            if ( cmdCode == DIA_MSG_AS ||
                 cmdCode == DIA_MSG_RA)
            {
                DIA_SE_PEER_INST_AGENT(e)= trInst;
            }
            else
            {
                DIA_SE_PEER_INST(e)= trInst;
            }

            /* Set the saved clientid in the message */
            msg->setClientId(DIA_SE_CLIENTID(e));

            /* Set the saved index, in the message */
            msg->setSessionIndex(DIA_SE_SINDX(e));

            DT_DBG(("Found Session Context for :: %s", sessionId.c_str()));
        }

        if (msg->getAuthApplicationId())
        {
            DIA_SE_APP_ID(e) = msg->getAuthApplicationId()->value();
        }
        else
        {
            DIA_SE_APP_ID(e) = msg->getHeader().appId;
        }

        switch (DIA_SE_FSM_TYPE(e))
        {
        /* Stateful Server Auth FSM */
        case STATEFUL_SERVER_AUTH_FSM:
        {
            switch (msg->getCommandCode())
            {
            case DIA_MSG_ST:
                DIA_SE_EVT_TYPE(e) = AUTH_SESSION_EVT_RX_STR;
                ret = statefulServerAuthFsm.SubmitToSM(e, &ev.GetEvent());
                break;
            default:
                DIA_SE_EVT_TYPE(e) = AUTH_SESSION_EVT_REQUEST_ACCESS;
                ret = statefulServerAuthFsm.SubmitToSM(e, &ev.GetEvent());
                if (SESSION_TABLE->ModifyEntry(e,
                                               (ITS_OCTET *)sessionId.c_str(),
                                               sessionId.size())
                                      != ITS_SUCCESS)
                {
                    DT_ERR(("Failed to update session context"));
                }
                break;
            }
            break;
        }
        case STATELESS_SERVER_AUTH_FSM:
        {
            /* Stateless Server Auth FSM */
            switch (msg->getCommandCode())
            {
            case DIA_MSG_ST:
            case DIA_MSG_AS:
                 DT_ERR(("Recvd STR/ASR For Stateless Server Discarding Msg"));
                 /* Good Indication to free the entry though */
                 if (SESSION_TABLE->RemoveEntry(e,(ITS_OCTET*)sessionId.c_str(),
                                               sessionId.size()) != ITS_SUCCESS)
                 {
                     DT_ERR(("Failed to free session context"));
                 }

                 break;
            default:
                ret = DiaMsgRouter::SendMsgToApp(e, &ev.GetEvent());
                if (ret != ITS_SUCCESS)
                {
                    DT_ERR(("Failed to SendMsgToApp"));

                    ret = DiaErrHandler::HandleError(trInst, msg,
                                         SEND_ERROR_TO_PEER,
                                         ITS_DIA_UNABLE_TO_DELIVER);

                    delete cmd;
                    cmd = NULL;
                    return ret;
                }
                break;
            }
            break;
        }
        case STATEFUL_CLIENT_AUTH_FSM:
        {
            switch (msg->getCommandCode())
            {
            case DIA_MSG_AS:
            case DIA_MSG_RA:
                if (msg->getCommandCode() == DIA_MSG_AS)
                {
                    DIA_SE_EVT_TYPE(e) = AUTH_SESSION_EVT_RX_ASR;
                }
                else if (msg->getCommandCode() == DIA_MSG_RA)
                {
                   DIA_SE_EVT_TYPE(e) = AUTH_SESSION_EVT_RX_RAR;
                }
                ret = statefulClientAuthFsm.SubmitToSM(e, &ev.GetEvent());
                if (SESSION_TABLE->ModifyEntry(e,
                                               (ITS_OCTET *)sessionId.c_str(),
                                               sessionId.size())
                                      != ITS_SUCCESS)
                {
                    DT_ERR(("Failed to update session context"));
                }
                break;
            default:
               DT_DBG(("Server Initiated App specific Msg Received Msg"));
               DIA_SE_EVT_TYPE(e) = AUTH_SESSION_EVT_RX_APP_SPECIFIC_REQ_MSG;
               ret = statefulClientAuthFsm.SubmitToSM(e, &ev.GetEvent());
               break;
            }

            break;
        }
        default:
            DT_ERR(("Invalid FSM Type"));
            break;
        }
    }
    else
    {
        DT_DBG(("Application Level Message without SessionId"));
        if (msg)
        {
            ret = DiaErrHandler::HandleError(trInst, msg,
                                             SEND_ERROR_TO_PEER,
                                             ITS_DIA_UNKNOWN_SESSION_ID);
            delete cmd;
            cmd = NULL;
        }

        return ret;
    }

    return (ITS_SUCCESS);
}


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
DiaUpStreamMsgHandler::HandleAnsMessage(its::Event &ev)
{
    int ret;
    DiaSocketTransport *tr = NULL;
    ITS_USHORT trInst = ITS_GET_CTXT(ev.GetData());
    const ITS_OCTET *msg = &ev.GetData()[sizeof(ITS_USHORT)];
    ITS_UINT msgLen = ev.GetLength() - sizeof(ITS_USHORT);
    DIA_BASE_CMD *cmd = NULL;
    DIA_BASE_CMD *gCmd = NULL;
    DIA_BASE_CMD *reqCmd = NULL;
    PEER_ENTRY *peer = NULL;
    SESSION_ENTRY *sessEntry = NULL;
    bool addSessionId = false;
    std::string sessionId = "";
    DT_DBG(("HandleAnsMessage"));

    tr = trTable[trInst];
    if (tr)
    {
        peer = tr->GetPeer();
    }

    if (peer == NULL)
    {
       DT_ERR(("Peer not found for transport"));
       return (ITS_ENOTFOUND);
    }

    /* check if SessionID is present in the received msg, if not present get the
     * Hop-by-Hop Id from message access the PendingQ to get the request message
     * then extracet sessionId. Compute Hash and get the TQ_INST, if the
     * computed TQ_INST is same as the current thread, then decode msg after
     * decoding set the sessionId on the decoded msg, else post the received
     * event to the computed TQ_INST*/
    if (DiaUtils::GetSessionString((ITS_OCTET*)msg, sessionId) != ITS_SUCCESS)
    {
        ITS_OCTET cmdFlag = msg[DIA_CMD_FLAG_POS];
        /* extract Hop-By-Hop ID */
        unsigned int hopByHopId = ntohl(*(unsigned int*)(msg + 12));
        reqCmd = DIA_PE_PENDING_Q(peer)->GetEntry(hopByHopId);
        if (ERROR_BIT_SET(cmdFlag))
        {
            if (reqCmd != NULL)
            {
                DT_DBG(("Successfully fetched message from PendingQ"));
                if ( reqCmd->getSessionId())
                {
                    sessionId = reqCmd->getSessionId()->value();
                }
                ITS_INT currTrInst = DIAThreadIdList::GetTQInstance();
                ITS_INT compTrInst = DiaUtils::GetStackTQInst((const char*)sessionId.c_str());
                if( currTrInst == compTrInst)
                {
                    addSessionId = true;
                }
                else 
                {
                    /* put the event with computed transport instance */
                    its::Transport::PutEvent(compTrInst, ev);
                    return ITS_SUCCESS; 
                }
            }
            else
            {
                DT_WRN(("Unable to get the message from PendingQ"));
            }
        }
/*        else
        {
            DiaMsgRouter::SendIndication( NULL,NULL, (char*) sessionId.c_str(),
                    MANDATORY_AVP_MISSING_IND_FROM_STACK);
            if (peer != NULL && DIA_PE_PENDING_Q(peer))
            {
                DIA_PE_PENDING_Q(peer)->RemoveEntry(reqCmd->getHeader().hh);
            }
            return (ret);
        }
        */
    }
    ret = DiaUtils::DecodeMsg(&cmd, msg, msgLen);
    if (cmd == NULL || ret != ITS_SUCCESS)
    {
        DT_ERR(("DiaUpStreamMsgHandler::Decode Failure"));
        /* Decode failed because of Base Mandatory avp missing extract SessionId
         * from the message and send indication to application to handle it */
        std::string sessId;
        unsigned int hopByHopId;
        if (cmd && cmd->getSessionId())
        {
            sessId.assign(cmd->getSessionId()->value());
            hopByHopId = cmd->getHeader().hh;
        }
        else
        {
            ITS_OCTET cmdFlag = msg[DIA_CMD_FLAG_POS];
            /* extract Hop-By-Hop ID */
            hopByHopId = ntohl(*(unsigned int*)(msg + 12));
            DT_DBG(("hopByHopId recieved is: %d",hopByHopId));
            if (reqCmd)
            {
                sessId.assign(reqCmd->getSessionId()->value());
                DT_DBG(("session Id recieved is: %s",sessId.c_str()));
            }
            else
            {
                sessId.assign(sessionId);
                DT_DBG(("session Id recieved is: %s",sessId.c_str()));
            }
        }

        DT_ERR(("Decode failed for sessId : %s",sessId.c_str()));
        DT_DBG(("sending MANDATORY_AVP_MISSING_IND_FROM_STACK indication to application"));
        if (SESSION_TABLE->FindEntry(sessEntry,
                    (ITS_OCTET *)sessId.c_str(),
                    (sessId.length())) == ITS_SUCCESS)
        {
            DT_DBG(("Session Entry found"));
            if (DiaMsgRouter::SendIndication( sessEntry ,peer, (char*)sessId.c_str(),
                    MANDATORY_AVP_MISSING_IND_FROM_STACK ) != ITS_SUCCESS)
            {
                DT_ERR(("Failed To send Indication to application"));
            }
        }
        if (peer != NULL && DIA_PE_PENDING_Q(peer))
        {
            DIA_PE_PENDING_Q(peer)->CancelRetransmitTimerAndRemoveEntry(hopByHopId);
        }
        if (cmd)
        {
            cmd->setEncodedBuf(NULL);
            delete cmd;
            cmd = NULL;
        }

        if (reqCmd)
        {
            //reqCmd->setEncodedBuf(NULL);
            delete reqCmd;
            reqCmd = NULL;
        }

        return (ret);
    }
    if (addSessionId)
    {
        /* add SessionId to command as well set the avpbit mask*/
        cmd->setSessionId(sessionId, true);
        addSessionId = false;
    }

    ITS_UINT dictId=0;
    if(cmd->getHeader().appId > 0) 
    {
        dictId = DiaStackClass::GetDtf().getDictIdForAppId(cmd->getHeader().appId,
                DiaStackClass::GetDictionaryTable(), peer->dictId);
        cmd->SetDictId(dictId);
        DT_DBG(("indictId is %d", dictId));
    }

    cmd->SetIncomingPeerInst(DIA_PE_INST(peer));

    gCmd = (DIA_BASE_CMD *)cmd;

    /*update the stats for number of request message received for dictionary
     * id*/
    DIA_INC_INTERFACE_TOTAL_RESPONSE_RECEIVED(dictId,(gCmd->getCommandCode()));

    /* check if request msg contain error bit set if so update stats */
    if(gCmd->isError())
    {
        DIA_INC_INTERFACE_ERROR_MSG_COUNT(dictId,(gCmd->getCommandCode()));
    }

    /*
     *Set Buffer in the message and set evt->data to NULL
     * to avoid multple deletes
     */
    gCmd->setPtrToFreeBuf((void *)ev.GetEvent().data);
    ev.GetEvent().data = NULL;

    /**
     * Check for Redirected Answer.
     */
    if ( (gCmd->getHeader().flags.e) && gCmd->getResultCode() &&
         (gCmd->getResultCode()->value() == ITS_DIA_REDIRECT_INDICATION) )
    {
        int ret = DiaRedirectHandler::HandleRedirectedAnsMsg(cmd, peer);

        if ( ret != ITS_SUCCESS )
        {
            DT_DBG(("HandleRedirectedAnsMsg:: Error Handling."));

            SESSION_ENTRY *ent = NULL;
            ITS_INT errCode = ITS_DIA_UNABLE_TO_DELIVER;
            const char *sessId = NULL;

            if (gCmd->getSessionId())
            {
                sessId = gCmd->getSessionId()->value().c_str();
            }

            if (sessId &&
                 SESSION_TABLE->FindEntry(ent,
                                          (ITS_OCTET *)sessId,
                                          strlen(sessId)) == ITS_SUCCESS)
            {
                ITS_USHORT trInst = DIA_SE_PEER_INST(ent);
                cmd->getHeader().hh = DIA_SE_RX_HH(ent);

                ret = DiaErrHandler::HandleError( trInst,
                                                  cmd,
                                                  SEND_ERROR_TO_PEER,
                                                  errCode );

                if (SESSION_TABLE->RemoveEntry( ent,
                                                (ITS_OCTET *)sessId,
                                                strlen(sessId)) != ITS_SUCCESS)
                {
                    DT_WRN(("Failed to remove session Entry : %d", ret));
                }
            }
            else
            {
               DT_WRN(("Session Entry Not found::Unable to send Err Response"));
            }
        }

        if ( cmd )
        {
            delete cmd;
            cmd = NULL;
        }
        return ret;
    }

    /*
     * Remove entry from pending queue
     * after receiving answers (both error and correct answers)
     */
    if (peer != NULL && DIA_PE_PENDING_Q(peer))
    {
        DT_DBG((" Remove entry from Pending Queue %d",gCmd->getHeader().hh));
	DIA_PE_PENDING_Q(peer)->CancelRetransmitTimerAndRemoveEntry(gCmd->getHeader().hh);
    }

    /* Section 6.1 */

    /* Message is processed in the following order
      1. If for localHost: Follow 6.1.4

      2. If for Peer: Follow 6.1.5

      3. Follow request routing: Follow 6.1.6

      4. None, then return an answer with UNABLE_TO_DELIVER
    */

    // PTR Changes
    ITS_Event pEvt;
    ITS_OCTET data[ITS_DIA_PTR_DATA_LEN];

    pEvt.SetSource(ev.GetSource());

    /* Set the Transport Instance */
    ITS_SET_CTXT(data, trInst);

    /* Copy in the Pointer address */
    memcpy(&data[sizeof(ITS_USHORT)], &cmd, sizeof(ITS_ULONG));
    pEvt.SetData(data, ITS_DIA_PTR_DATA_LEN);

    /*
     * Accounting Message submit to Accounting statemachine
     * by default submit to Auth statemachine
     */

    switch (gCmd->getCommandCode())
    {
    case DIA_MSG_AC:

        DT_DBG(("Acct Answer Message for LocalHost::"));
        HandleLocalAcctAnsMessage(cmd, pEvt);
        break;
    default:
        DT_DBG(("Auth Answer Message for LocalHost::"));
        HandleLocalAuthAnsMessage(cmd, pEvt);
        break;
    }

    return (ITS_SUCCESS);
}

int
DiaUpStreamMsgHandler::HandleReqMessage(its::Event &ev)
{
    int ret = ITS_SUCCESS;
    ITS_USHORT trInst = ITS_GET_CTXT(ev.GetData());
    const ITS_OCTET *msg = &ev.GetData()[sizeof(ITS_USHORT)];
    ITS_UINT msgLen = ev.GetLength() - sizeof(ITS_USHORT);
    DIA_BASE_CMD *cmd = NULL;
    DIA_BASE_CMD *gCmd = NULL;
    DiaSocketTransport *tr = NULL;
    std::string sessionId;
    bool isProxy = false;
    ITS_BOOLEAN isReqFwd = ITS_FALSE;
    ITS_BOOLEAN isRlyAdv = ITS_FALSE;

    DT_DBG(("HandleReqMessage"));

    ret = DiaUtils::DecodeMsg(&cmd, msg, msgLen);
    //unsigned int msgRate = LICENSE_AllowedMsgRate();
    //DT_DBG(("MESSAGE RATE = %u",msgRate));

    /*Fetch DictId from Peer Entry Table*/
     PEER_ENTRY* inPeer = NULL;
     ITS_UINT dictId=0;
     tr = trTable[trInst];
     if (tr == NULL)
     {
        DT_ERR(("Invalid transport"));
        return (ITS_EBADTRANSPORT);
     }
     inPeer = tr->GetPeer();
     if (inPeer == NULL)
     {
        DT_ERR(("Peer not found for transport"));
        return (ITS_ENOTFOUND);
     }
   
     if(TOKEN_BUCKET_FILTER->IsMessageBasedLicensingEnabled())
     {
         if(TOKEN_BUCKET_FILTER->Consume())
         {
             DT_DBG(("Message rate is allowing"));
         }
         else
         {
             DT_WRN(("Message rate exceed, rejecting the request with a Busy response"));
             DIA_INC_PEER_MSG_REJECTED_BY_RATE_LIMITING_FACTOR(inPeer);
             ret = DiaErrHandler::HandleError(trInst,(ITS_OCTET *) msg, ITS_DIA_TOO_BUSY);
             return (ret);
         }
     }

    if (cmd == NULL || ret != ITS_SUCCESS)
    {
        DT_ERR(("DiaUpStreamMsgHandler::Decode Failure"));
        if( msgLen > 20 )
        {
            ITS_UINT cmdCode = DiaUtils::DataToUInt((ITS_OCTET *)&msg[5], (sizeof(ITS_UINT) - 1)); ;
            ITS_UINT appId = DiaUtils::DataToUInt((ITS_OCTET *)&msg[8], (sizeof(ITS_UINT)));;

            if(appId > 0) 
            {
                dictId = DiaStackClass::GetDtf().getDictIdForAppId(appId ,
                        DiaStackClass::GetDictionaryTable(), inPeer->dictId);
            }
            /*update the stats for number of request message received for dictionary
             * id*/
            DIA_INC_INTERFACE_TOTAL_REQUEST_RECEIVED(dictId,cmdCode);
            DIA_INC_INTERFACE_INVALID_MSG_COUNT(dictId,cmdCode);
        }

        /* Send Error Response if failed to decode*/
        ret = DiaErrHandler::HandleError(trInst,(ITS_OCTET *) msg, ret);

        if (cmd)
        {
            cmd->setEncodedBuf(NULL);
            delete cmd;
            cmd = NULL;
        }

        return (ret);
    }

    if(cmd->getHeader().appId > 0) 
    {
        dictId = DiaStackClass::GetDtf().getDictIdForAppId(cmd->getHeader().appId ,
                DiaStackClass::GetDictionaryTable(), inPeer->dictId);
        cmd->SetDictId(dictId);
    }


    cmd->SetIncomingPeerInst(DIA_PE_INST(inPeer));

     DT_DBG(("indictId is %d", dictId));

     gCmd = (DIA_BASE_CMD *)cmd;

    /*
     *Set Buffer in the message and set evt->data to NULL
     * to avoid multple deletes
     */
    gCmd->setPtrToFreeBuf((void *)ev.GetEvent().data);
    ev.GetEvent().data = NULL;

    if (gCmd->getSessionId())
    {
        sessionId = gCmd->getSessionId()->value();
        DT_DBG(("SessionId: %s", sessionId.c_str()));
    }
    else
    {
        /*update the stats for number of request message received for dictionary
         * id*/
        DIA_INC_INTERFACE_TOTAL_REQUEST_RECEIVED(dictId,(gCmd->getCommandCode()));
        DT_ERR(("No SessionId Received In Message. Returning Error"));
        ret = DiaErrHandler::HandleError(trInst, gCmd,
                                         SEND_ERROR_TO_PEER,
                                         ITS_DIA_UNKNOWN_SESSION_ID);

        delete cmd;
        cmd = NULL;

        return ret;
    }

    // PTR Changes
    ITS_Event pEvt;
    ITS_OCTET data[ITS_DIA_PTR_DATA_LEN];

    pEvt.SetSource(ev.GetSource());

    /* Set the Transport Instance */
    ITS_SET_CTXT(data, trInst);

    /* Copy in the Pointer address */
    memcpy(&data[sizeof(ITS_USHORT)], &cmd, sizeof(ITS_ULONG));
    pEvt.SetData(data, ITS_DIA_PTR_DATA_LEN);

    /* Section 6.1 */

    /* Message is processed in the following order
      1. If for localHost: Follow 6.1.4

      2. If for Peer: Follow 6.1.5

      3. Follow request routing: Follow 6.1.6

      4. None, then return an answer with UNABLE_TO_DELIVER
    */
    REALM_ENTRY *rEntry = NULL;

    /**
     * IsLocalRouting gives a exact host or realm match in case of local
     * routing else it gives the realm entry match for localAction and
     * returns !ITS_SUCCESS.
     */
    ret = DiaMsgRouter::IsLocalRouting(cmd, rEntry);

    /**
     * Processing for Proxy Agent
     * Checking if entry not null then, local action is proxy
     */
    if (rEntry && DIA_RE_L_ACTION(rEntry) == ITS_DIA_PROXY)
    {
        isProxy = true;
        DT_DBG(("Message with SessionId %d is for Proxy", sessionId.c_str()));

        ret = DiaProxyHandler::HandleReqMessage(cmd, pEvt);

        DT_DBG(("Returning After Proxy Handling For Command With SessionId %s with RetVal: %d", sessionId.c_str(), ret));
        return ret;

    }

    /**
     * Processing for Local Host
     */
    if (ret == ITS_DIA_LOCAL_HOST_MATCH ||
        ret == ITS_DIA_LOCAL_REALM_MATCH)
    {
        DT_DBG(("Message with SessionId %s for LocalHost", sessionId.c_str()));

        /*
         * Accounting Message submit to Accounting statemachine
         * by default submit to Auth statemachine
         */

     /*update the stats for number of request message received for dictionary
      * id*/
     DIA_INC_INTERFACE_TOTAL_REQUEST_RECEIVED(dictId,(gCmd->getCommandCode()));
        switch (gCmd->getCommandCode())
        {
        case DIA_MSG_AC:

            ret = HandleLocalAcctReqMessage(cmd, pEvt, isProxy);
            break;
        default:

            ret = HandleLocalAuthReqMessage(cmd, pEvt, isProxy);
        }

        DT_DBG(("Returning After Handling Message with SessionId %s for LocalHost with Retval: %d", sessionId.c_str(), ret));
        return ret;
    }

    /**
     * Check for Redirect Request.
     */
    if (rEntry && DIA_RE_L_ACTION(rEntry) == ITS_DIA_REDIRECT)
    {
        DT_DBG(("Message with SessionId %s for Redirect", sessionId.c_str()));

        if ( itsDiaConfig.IsRedirectAppProcessing() )
        {
            DT_DBG(("Sending Redirect RequestMsg to Redirect Application for SessionId: %s", sessionId.c_str()));
            SESSION_ENTRY ent;
            const char *sessId;
            memset(&ent,0,sizeof(SESSION_ENTRY));

            if(gCmd->getSessionId())
            {
                sessId = gCmd->getSessionId()->value().c_str();
            }

            /**
             * Msg is statefull, stateless, authorization or accounting, we
             * maintain a authorization session. Because this message is
             * already identified as for redirection. we maintain session
             * till application fill the Redirecion Info.
             */
     /*update the stats for number of request message received for dictionary
      * id*/
     DIA_INC_INTERFACE_TOTAL_REQUEST_RECEIVED(dictId,(gCmd->getCommandCode()));

            DIA_SE_RX_FLAGS(&ent)     = cmd->getHeader().flags;
            DIA_SE_RX_HH(&ent)        = cmd->getHeader().hh;
            DIA_SE_RX_EE(&ent)        = cmd->getHeader().ee;
            DIA_SE_PEER_INST(&ent)    = trInst;
            DIA_SE_FSM_TYPE(&ent)     = REDIRECT_AGENT_FSM;
            DIA_SE_CLIENTID(&ent)     = ((DIA_BASE_CMD *)cmd)->getClientId();
            DIA_SE_STYPE(&ent)        = DIA_AUTHORIZATION;

            ITS_UINT timeout = itsDiaConfig.GetAuthSessionConfig().GetTimeout();

            /* Start the Auth Session Timer */
            SESSION_TABLE->StartTimer( sessionId.c_str(),
                                       AUTH_SESSION_TIMER,
                                       timeout,
                                       &ent );

            /* Maintain a Temporary Session */
            if (SESSION_TABLE->InsertEntry( ent,
                                            (ITS_OCTET *)sessId,
                                            strlen(sessId)) == ITS_SUCCESS )
            {
                DT_DBG(("Created Session Context for %s", sessId ));
                ret = ITS_SUCCESS;
            }
            else
            {
                DT_ERR(("Failed to create Session Context for %s", sessId ));
                SESSION_TABLE->StopTimer(AUTH_SESSION_TIMER, &ent);
                ret = !ITS_SUCCESS;
            }

            /* Added Result Code AVP */
            int rsltCode = ITS_DIA_REDIRECT_INDICATION;
            if ( ret == ITS_SUCCESS)
            {
                if (DiaUtils::AddResultCodeAvp( cmd, rsltCode ) != ITS_SUCCESS)
                {
                    ret = !ITS_SUCCESS;
                }
                DT_DBG(("Included Result Code AVP for %s", sessId ));
            }

            if ( ret == ITS_SUCCESS)
            {
                DT_DBG((" Added Result Code AVP"));

                ITS_OCTET data[sizeof(ITS_ULONG)];
                const unsigned char* enBuf =
                                    (const unsigned char*)cmd->getEncodedBuf();
                ITS_UINT enBufLen = cmd->getEncodedBufLen();

                DIA_BASE_CMD *bCmd = new DIA_BASE_CMD(enBuf, enBufLen, dictId);

                memcpy(&data[0], &bCmd, sizeof(ITS_ULONG));

                /* Sent Msg to Redirect Application */
                ret = DiaMsgRouter::SendMsgToApp( ITS_DIA_MSG_TYPE_IND_WITH_DATA,
                                                  cmd->getSessionIndex(),
                                                  DIA_RELAY_APP_ID,
                                                  data,
                                                  sizeof(ITS_ULONG),
                                                  cmd->getClientId());
            }
            if ( ret == ITS_SUCCESS)
            {
                DT_DBG(("Sucessfully sent Msg to Redirect Application for SessionId: %s", sessId));
                return ret;
            }
        }
        else
        {
            DT_DBG(("Sending Redirect RequestMsg to Diameter Stack for SessionId: %s", sessionId.c_str()));

            /*update the stats for number of request message received for dictionary
             * id*/
            ret = DiaRedirectHandler::HandleRedirectReqMsg(cmd, rEntry, trInst);

        }

        if ( ret != ITS_SUCCESS )
        {
            DT_DBG(("HandleRedirectReqMsg :: Error Handlng for SessionId: %s", sessionId.c_str()));

            ITS_INT errCode = ITS_DIA_UNABLE_TO_DELIVER;
            ret = DiaErrHandler::HandleError( trInst,
                                              cmd,
                                              SEND_ERROR_TO_PEER,
                                              errCode );
        }

        if (cmd)
        {
            delete cmd;
            cmd = NULL;
        }
        return ret;
    }

    /**
     * If the Realm entry is not found and the node is advertised as
     * relay, check whether the Destination Host is directly connected
     * to node. If yes RequestForward as relay to the other end else
     * send error response.
     */
    isRlyAdv = itsDiaConfig.IsAdvertisedRelay();
    if ((rEntry == NULL) && isRlyAdv)
    {
        isReqFwd = DiaMsgRouter::VerifyIfReqForwarding(gCmd);

        if (isReqFwd && isRlyAdv)
        {
            DT_DBG(("Destination Host Match Found in Peer Table"));
            DT_DBG(("Node is Advertised as Relay." \
                    " Request can be forwarded as Relay for SessionId: %s", sessionId.c_str()));
        }
        else
        {
           DT_DBG(("The Destination Host Mismatch or Node not Advertised" \
                   " as relay for SessionId: %s", sessionId.c_str()));
        }
    }

    /**
     * Re-Arranged the Code to provide fix for the issue 869 in whizible
     * The Local Check is shifted up here from bottom and removed the check
     * for relay.
     */
    if (rEntry && DIA_RE_L_ACTION(rEntry) == ITS_DIA_LOCAL)
    {
        DT_ERR(("Invalid local action for incoming request for Session" \
                "Context:%s", sessionId.c_str()));
        ret = DiaErrHandler::HandleError(trInst, gCmd,
                                         SEND_ERROR_TO_PEER,
                                         ITS_DIA_UNABLE_TO_DELIVER);


        if (cmd)
        {
            delete cmd;
            cmd = NULL;
        }

        return ret;
    }

    //Added for separation of Relay Functionality
    if (isReqFwd)
    {
        DT_DBG(("Realm Match Not Found, but Destination Host Connected"));
        DT_DBG(("Request Forwarding the Message as Relay for SessionId: %s", sessionId.c_str()));
        ret = DiaRelayHandler::HandleReqMessage(trInst, cmd, rEntry);
    }
    else if (rEntry && DIA_RE_L_ACTION(rEntry) == ITS_DIA_RELAY)
    {
        /**
         * Here Realm entry is present for realm in Realm Table.
         */
        /*update the stats for number of request message received for dictionary
         * id*/
        DT_DBG(("Realm Match Found for the Destination Realm."));
        DT_DBG(("LocalAction on the message is: RELAY for Sessionid: %s", sessionId.c_str()));
        ret = DiaRelayHandler::HandleReqMessage(trInst, cmd, rEntry);
    }
    else
    {
        /**
         * Send Error response. If try to send relay message on
         * on any other session.
         */
        DT_ERR(("Not able to send the message as Relay for SessionId: %s", sessionId.c_str()));
        ret = DiaErrHandler::HandleError(trInst, gCmd,
                                         SEND_ERROR_TO_PEER,
                                         ITS_DIA_REALM_NOT_SERVED);


    }

    if (cmd)
    {
        delete cmd;
        cmd = NULL;
    }
    return ret;
}

int
DiaUpStreamMsgHandler::HandleMessage(DIAThread *thr, its::Event &ev)
{
    int ret;
    ITS_OCTET cmdFlag = 0x0;
    ITS_EVENT evt;
    
    // Clear any previous thread specific session trace object
    DiaTracer::ClearThreadTraceObj();

    DT_DBG(("%s: Received Event: %d ", __FUNCTION__, ev.GetSource() ));

    // Redundancy::Return if Source DIA_GCS_NO_SRC_INST
    if (ev.GetSource() == DIA_GCS_NO_SRC_INST)
    {
       //enable Redundancy flag
       ITSDiaConfig* cfg = &itsDiaConfig;
       cfg->setMsgRedundancyEnabled();
       DT_DBG(("Redundancy Check Message Received : Redundancy Enabled\n"));
       return ITS_SUCCESS;
    }

    if (!itsDiaConfig.IsMsgRedundancyEnabled())
    {
        if (DiaUtils::GetEventReference(&ev, &evt) != ITS_SUCCESS)
        {
            DT_ERR(("Failed to GetEventReference"));
            return !ITS_SUCCESS;
        }

        ITS_EVENT_TERM(&ev.GetEvent());
        /* From here Event ev carries full PDU not just reference */
        ev.GetEvent().len = evt.len;
        ev.GetEvent().data = evt.data;
    }

    const ITS_OCTET *msg = &ev.GetData()[sizeof(ITS_USHORT)];

    DT_DBG(("Message Received from PeerFSM\n"));

    PRINT_EVENT(&ev.GetEvent());

    cmdFlag = msg[4];

    if (REQUEST_BIT_SET(cmdFlag))
    {
        DT_DBG(("Received Request Message\n"));
        HandleReqMessage(ev);
    }
    else
    {
        DT_DBG(("Received Answer Message\n"));
        HandleAnsMessage(ev);
    }

    return (ITS_SUCCESS);
}

