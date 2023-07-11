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
 * LOG: $Log: dia_session_auth_states.cpp,v $
 * LOG: Revision 3.20.2.1.2.9.4.5.4.3.4.1.8.1  2017/12/21 04:37:21  jkchaitanya
 * LOG: Ticket 1149 changes to support case insensitivity for peers, hosts 7 realms
 * LOG:
 * LOG: Revision 3.20.2.1.2.9.4.5.4.3.4.1  2014/05/06 13:09:12  jkchaitanya
 * LOG: changes for ccfh feature
 * LOG:
 * LOG: Revision 3.20.2.1.2.9.4.5.4.3  2014/01/06 09:22:32  cprem
 * LOG: Changes in diameter stack to support session replication. Review request 1611.
 * LOG:
 * LOG: Revision 3.20.2.1.2.9.4.5.4.2  2013/09/10 08:36:39  ncshivakumar
 * LOG: RFC6733 Changes
 * LOG:
 * LOG: Revision 3.20.2.1.2.9.4.5.4.1  2013/08/15 05:27:05  ncshivakumar
 * LOG: Generic state machine changes
 * LOG:
 * LOG: Revision 3.20.2.1.2.9.4.5  2013/04/18 07:04:31  jvikram
 * LOG: Included changes relatd to log segregation.
 * LOG:
 * LOG: Revision 3.20.2.1.2.9.4.4  2013/04/12 04:18:22  vsarath
 * LOG: Logs improvement
 * LOG:
 * LOG: Revision 3.20.2.1.2.9.4.3  2013/03/08 09:11:59  mallikarjun
 * LOG: Bug 86 changes
 * LOG:
 * LOG: Revision 3.20.2.1.2.9.4.2  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.20.2.1.2.9.4.1  2013/02/01 11:34:16  pramana
 * LOG: Merged from branch 0212 to 0300.
 * LOG:
 * LOG: Revision 3.20.2.1.2.11  2013/01/26 05:13:23  pramana
 * LOG: Fix for crash observed while CCR-I received with no Destination-host
 * LOG:
 * LOG: Revision 3.20.2.1.2.10  2013/01/23 03:09:12  vsarath
 * LOG: Fix for issue 976
 * LOG:
 * LOG: Revision 3.20.2.1.2.9  2012/12/21 08:38:58  jsarvesh
 * LOG: redundant code removal
 * LOG:
 * LOG: Revision 3.20.2.1.2.8  2012/12/03 08:41:20  ncshivakumar
 * LOG: Changes done for adding static routing table
 * LOG:
 * LOG: Revision 3.20.2.1.2.7  2012/11/20 17:39:44  pramana
 * LOG: Merged from CMAPI branch for 212-07 release
 * LOG:
 * LOG: Revision 3.20.2.1.2.3.8.2  2012/11/20 10:31:24  rgovardhan
 * LOG: merge from 00 Nov20Rel
 * LOG:
 * LOG: Revision 3.20.2.1.2.3  2012/10/13 04:45:18  jsarvesh
 * LOG: Bug 23 receiving unknown sessionid for update msg if server is down
 * LOG:
 * LOG: Revision 3.20.2.1.2.2  2012/09/17 05:03:26  rsanjay
 * LOG: Fixes for the bugs 17, 104 and 121, Handling the case where message for proxy is received for an existing session and destination host is down. And also handling a case where the destination-host in destination-host avp is down when a proxy request(stateless) is received.
 * LOG:
 * LOG: Revision 3.20.2.1.2.1  2012/08/21 08:55:57  ksalil
 * LOG: Merge from branch B-DRE-IDIA-0100-00
 * LOG:
 * LOG: Revision 3.20.2.2  2012/08/02 08:01:28  ncshivakumar
 * LOG: fix for sessioncount increment when server is down
 * LOG:
 * LOG: Revision 3.20.2.1  2012/03/07 13:23:08  brajappa
 * LOG: Changes made for the DRE demo
 * LOG:
 * LOG: Revision 3.20  2011/07/04 09:59:41  nvijikumar
 * LOG: Fix for Session time issue
 * LOG: Session timer values will be retrieved from XML if missing in the message
 * LOG: when it is in OPEN state
 * LOG:
 * LOG: Revision 3.19  2011/04/28 04:01:15  nvijikumar
 * LOG: Introduced XML config parameter to disable stack initiated STR while
 * LOG: handling Session Timeout
 * LOG:
 * LOG: Revision 3.18  2011/04/26 06:12:33  nvijikumar
 * LOG: Introduced XML config parameter to disable stack initiated STR while
 * LOG: handling ASA
 * LOG:
 * LOG: Revision 3.17  2010/12/21 20:37:44  nvijikumar
 * LOG: Fix for ASA/STR sequence Issue (Invalid Hop-by-Hop ID issue)
 * LOG:
 * LOG: Revision 3.16  2009/11/12 12:15:17  sureshj
 * LOG: No matching Peer found warning Trace changed to Debug trace.
 * LOG: Motorola ticket 2264.
 * LOG:
 * LOG: Revision 3.15  2009/06/29 14:54:53  rajeshak
 * LOG: Changes done for performance enhancement (splitting the session table).
 * LOG:
 * LOG: Revision 3.14  2009/03/19 12:36:10  nvijikumar
 * LOG: Global instance is created for the Class ITSDiaConfig to avoid function
 * LOG: call overhead as ITSDiaConfig::GetITSDiaConfig() was called max time
 * LOG:
 * LOG: Revision 3.13  2009/03/12 07:09:31  nvijikumar
 * LOG: Replaced strlen with std::string length()
 * LOG:
 * LOG: Revision 3.12  2009/03/03 11:17:20  rajeshak
 * LOG: Klockwork reported issue fix
 * LOG:
 * LOG: Revision 3.11  2009/01/09 10:28:28  rajeshak
 * LOG: Klockworks reported issue fix.
 * LOG:
 * LOG: Revision 3.10  2008/12/12 18:30:48  rajeshak
 * LOG: Lightweight Decode for base AVPS
 * LOG: New Command class is introduced (BaseCommand)
 * LOG:
 * LOG: Revision 3.9  2008/10/31 06:01:38  nvijikumar
 * LOG: IssueID:1189
 * LOG: FeatureID:none
 * LOG: Description: updates according to Architecture changes
 * LOG:
 * LOG: Revision 3.8  2008/08/21 06:25:39  nvijikumar
 * LOG: Memory leak fixes
 * LOG:
 * LOG: Revision 3.7  2008/04/22 22:23:50  hbhatnagar
 * LOG: Fix for the issue 874. Properly putting the context variable.
 * LOG:
 * LOG: Revision 3.6  2008/04/22 21:08:33  hbhatnagar
 * LOG: Provided fix for the issue 874 in whizible.
 * LOG:
 * LOG: Revision 3.5  2008/04/16 12:14:04  hbhatnagar
 * LOG: Made changes to populate DestinationRealm in session entry.
 * LOG: Also properly set DestinationRealm in the SendSTR and other misc
 * LOG: code cleanup
 * LOG:
 * LOG: Revision 3.4  2008/04/08 18:39:46  avinashks
 * LOG: removed unwanted code for proxy agents
 * LOG:
 * LOG: Revision 3.3  2008/04/07 17:49:19  hbhatnagar
 * LOG: Made changes for hop-by-Hop Id and also removed unwanted code.
 * LOG: Also done Error handling for request message.
 * LOG:
 * LOG: Revision 3.2  2008/04/01 16:49:43  hbhatnagar
 * LOG: Changes for Proxy and Relay support 3.0 release - (Hemant)
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:32  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.31  2008/03/27 12:14:08  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.26.4.6  2008/03/25 13:35:41  rajesh
 * LOG: **As per Plan B**
 * LOG: Starting of Auth-Session related Timers are commented out. This is done because of performance degradation with session increase.
 * LOG:
 * LOG: Revision 2.26.4.5  2007/12/16 06:04:46  hbhatnagar
 * LOG: Made changes to provide fix for issue No.11 raised during the validation
 * LOG: of bcgi ticket 1807.
 * LOG:
 * LOG: Revision 2.26.4.4  2007/05/25 03:56:54  nvijikumar
 * LOG: Restart Auth Timers if msg contains Timer AVPs in IDLE and OPEN state.
 * LOG:
 * LOG: Revision 2.26.4.3  2007/04/27 06:16:53  nvijikumar
 * LOG: Remove the session if timeout happened in the IDLE state.
 * LOG:
 * LOG: Revision 2.26.4.2  2007/04/26 04:06:34  nvijikumar
 * LOG: Fix for coredump issue PBN bug Id:5660
 * LOG:
 * LOG: Revision 2.26.4.1  2007/04/24 09:41:14  nvijikumar
 * LOG: Dont over ride the destination Host and Realm on backup side.
 * LOG:
 * LOG: Revision 2.26  2007/01/30 03:52:46  nvijikumar
 * LOG: get Session Id from Msg before handover to the App
 * LOG:
 * LOG: Revision 2.25  2007/01/29 13:19:21  yranade
 * LOG: Bug Fix: 5276. Missing case.
 * LOG:
 * LOG: Revision 2.24  2007/01/24 15:34:14  nvijikumar
 * LOG: Remove Session Entry Ctxt on Pending State after Session timeout.
 * LOG:
 * LOG: Revision 2.23  2006/12/21 15:20:58  tpanda
 * LOG: Fix for bug# 5011 and check if to add OriginStateId
 * LOG:
 * LOG: Revision 2.22  2006/12/11 13:51:25  tpanda
 * LOG: REDUNDANCY_SLOT_CHANGES are removed and code seems to be stable
 * LOG:
 * LOG: Revision 2.21  2006/11/30 18:54:24  tpanda
 * LOG: Redundancy slot changes backed out. TODO: Refer (REDUNDANCY_SLOT_CHANGES) defines
 * LOG: Failover and failback bug fixes
 * LOG:
 * LOG: Revision 2.20  2006/11/29 16:17:01  tpanda
 * LOG: Fix for crash while sending RAR from server
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
 * LOG: Revision 2.16  2006/10/30 21:34:04  yranade
 * LOG: Fix issues. (Early morning 31st, Oct)
 * LOG:
 * LOG: Revision 2.15  2006/10/30 15:59:11  yranade
 * LOG: Updates to Handle RAR/RAA.
 * LOG:
 * LOG: Revision 2.14  2006/10/30 12:12:28  yranade
 * LOG: 1. Set Origin-State-Id
 * LOG: 2. Codecleanup (removed #if 0)
 * LOG: 3. Set DestinationHost in STR.
 * LOG:
 * LOG: Revision 2.13  2006/10/28 15:04:53  nvijikumar
 * LOG: Use the msg context, before sending to app, to avoid possibility of
 * LOG: cleanup by the app.
 * LOG:
 * LOG: Revision 2.12  2006/10/28 12:30:52  yranade
 * LOG: 1. Don't allow naked RAR's: Bug Fix 4634
 * LOG: 2. Cleanup SessionContext for Stateless Sessions.
 * LOG:  a. In case of server, cleanup after sending answer to peer.
 * LOG:  b. In case of client, cleanup after receiving answer from peer
 * LOG:     and sending it to application.
 * LOG:
 * LOG: Revision 2.11  2006/10/27 09:50:03  yranade
 * LOG: Start GracePeriod timer after Lifetime timeout.
 * LOG:
 * LOG: Revision 2.10  2006/10/25 15:27:45  yranade
 * LOG: Missed setting sessionId from msg, for cleanup.
 * LOG:
 * LOG: Revision 2.9  2006/10/24 14:14:16  yranade
 * LOG: 1. Header changes. Use header by reference from the message.
 * LOG: 2. Cleanups.
 * LOG:
 * LOG: Revision 2.8  2006/10/17 18:46:12  yranade
 * LOG: Send Error message also to app.
 * LOG:
 * LOG: Revision 2.7  2006/10/16 06:32:46  yranade
 * LOG: AuthSessionTimer Handling. AuthSM related updates.
 * LOG:
 * LOG: Revision 2.6  2006/10/13 16:46:06  yranade
 * LOG: Server initiated RAR and fix 4448.
 * LOG:
 * LOG: Revision 2.5  2006/10/11 15:04:53  yranade
 * LOG: Fixes for issues: 4451, 4452, 4454, 4457.
 * LOG:
 * LOG: Revision 2.4  2006/10/09 06:30:10  yranade
 * LOG: Updates to cleanup context.
 * LOG:
 * LOG: Revision 2.3  2006/10/07 12:24:55  yranade
 * LOG: Today's round of updates.
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
 *
 ****************************************************************************/


/**
 * Includes
 */
#include <its++.h>
#include <engine++.h>
#include <its_timers.h>

#include <itsdiameter.h>
#include <dia_err.h>
#include <dia_cmn.h>
#include <dia_utils.h>
#include <dia_trace.h>
#include <dia_session_auth_fsm.h>
#include <dia_session_table.h>
#include <dia_ip_trans.h>
#include <dia_msg_router.h>

#if defined (ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
#endif

static int
Cleanup(SESSION_ENTRY *ctxt, string& sessionId)
{
    DT_DBG(("Session Cleanup"));

    if (SESSION_TABLE->RemoveEntry(ctxt, (ITS_OCTET *)sessionId.c_str(),
                                   (sessionId.length())) == ITS_SUCCESS)
    {
        DT_DBG(("Freed Session Entry"));
    }

    return (ITS_SUCCESS);
}

static int
Cleanup(SESSION_ENTRY *ctxt, const char *sessionId)
{
    DT_DBG(("Session Cleanup"));

    if (SESSION_TABLE->RemoveEntry(ctxt, (ITS_OCTET *)sessionId,
                                   strlen(sessionId)) == ITS_SUCCESS)
    {
        DT_DBG(("Freed Session Entry"));
    }

    return (ITS_SUCCESS);
}

static int
SendASA(bool error,
        bool retrans,
        ITS_UINT rCode,
        SESSION_ENTRY *ctxt)
{
    return (ITS_SUCCESS);
}

static int
SendSTR(char *sessionId, TerminationCause cause, bool error,
        bool retrans, SESSION_ENTRY *ctxt)
{
    int ret = ITS_SUCCESS;

    DIA_CER *lcer = NULL;
    DiaSocketTransport *tr = NULL;
    PEER_ENTRY *peer = NULL;
    ITS_USHORT inst = 0;

    DT_DBG(("SendSTR"));

    if (ctxt == NULL)
    {
        return (ITS_ESENDFAIL);
    }

    DIA_STR *str = new DIA_STR(error, retrans);
    if (str == NULL)
    {
        return (ITS_ESENDFAIL);
    }

    DIA_GEN_CMD *gCmd = (DIA_GEN_CMD *)str;
    DIA_HDR &hdr = (DIA_HDR &)gCmd->getHeader();
    hdr.hh = DiaUtils::GenerateHopByHopId();

    if (DIA_SE_IS_AGENT(ctxt))
    {
        inst = DIA_SE_PEER_INST_AGENT(ctxt);
        /**
         * Saving locally generated hop-by-hop id in the context for
         * both the RX and Local.
         */
        DIA_SE_LOCAL_HH(ctxt) = hdr.hh;
        DIA_SE_RX_HH(ctxt) = hdr.hh;
    }
    else
    {
        inst = DIA_SE_PEER_INST(ctxt);
        DIA_SE_RX_HH(ctxt) = hdr.hh;
    }
    tr = trTable[inst];
    if (tr == NULL)
    {
       if (str)
       {
           delete str;
       }
       return (ITS_EBADTRANSPORT);
    }
    peer = tr->GetPeer();

    if (peer == NULL)
    {
       if (str)
       {
           delete str;
       }
        return (ITS_ENOTFOUND);
    }

    lcer = itsDiaConfig.GetLocalCER();

    hdr.ee = DiaUtils::GenerateEndToEndId();
    /**
     * Partial fix for issue 874, the end to end id is not saved
     * properly in the session earlier. Saving the same
     */
    DIA_SE_RX_EE(ctxt) = hdr.ee;

    if (gCmd->getOriginStateId())
    {
        ITS_UINT &o = (ITS_UINT &)gCmd->getOriginStateId()->value();
        o = itsDiaConfig.GetOriginStateId();
    }
    else if(itsDiaConfig.GetOriginStateIdOpt())
    {
        OriginStateId oid(itsDiaConfig.GetOriginStateId());
        AVPContainerDerived &avpCont = (AVPContainerDerived &)
                                       gCmd->getContainer();
        avpCont.add(oid.name(), oid, false);
    }

    str->setSessionId(SessionId((char *)sessionId));
    str->setOriginHost(lcer->getOriginHost());
    str->setOriginRealm(lcer->getOriginRealm());

    /**
     * Adding the Proper destination realm in the STR 
     * from the context.
     */
    str->setDestinationRealm(DestinationRealm(DIA_SE_DEST_REALM(ctxt)));
    str->setAuthApplicationId(AuthApplicationId(DIA_SE_APP_ID(ctxt)));
    str->setTerminationCause(TerminationCause(cause));

    //Warning Fix  - suggest parentheses around assignment used as truth value
    if ((ret = DiaMsgRouter::SendCmdToPeer(inst,
                                          &hdr, str)) != ITS_SUCCESS)
    {
        DT_ERR(("Failed to send STR : ret = %d", ret));
    }

    /* fix the memory leak (Yogesh) */
    if (str)
    {
        delete str;
    }

    return ret;
}

static int
InsertEntry(DIA_BASE_CMD *&gCmd, SESSION_ENTRY *&sessInfo)
{
    const char* sessionId = NULL;
    if (gCmd->getSessionId())
    {
        sessionId = gCmd->getSessionId()->value().c_str();

        SESSION_TABLE->StartTimer(sessionId,
                                  AUTH_SESSION_TIMER,
                                 itsDiaConfig.GetAuthSessionConfig().GetTimeout(),
                                  sessInfo);

        if (SESSION_TABLE->InsertEntry(*sessInfo,
                                      (ITS_OCTET *)sessionId,
                                      (strlen(sessionId))) == ITS_SUCCESS)
        {
            DT_DBG(("Created Session Context for %s", sessionId));
            return (ITS_SUCCESS);
        }
        else
        {
            DT_ERR(("Failed to create Session Context for %s",
                    sessionId));

            SESSION_TABLE->StopTimer(AUTH_SESSION_TIMER, sessInfo);

            return (ITS_DIA_UNABLE_TO_DELIVER);
        }
    }

    //Warning Fix - control reaches end of non-void return function
    return (!ITS_SUCCESS);
}

static int
ModifyEntry(DIA_BASE_CMD *&gCmd, SESSION_ENTRY *&sessInfo)
{
    std::string sessionId;
    if (gCmd->getSessionId())
    {
        sessionId = gCmd->getSessionId()->value();
        if (SESSION_TABLE->ModifyEntry(sessInfo, (ITS_OCTET *)sessionId.c_str(),
                                      sessionId.size()) != ITS_SUCCESS)
        {
             DT_ERR(("Failed to  Update Session Context"));
             return (ITS_DIA_UNABLE_TO_DELIVER);
        }
        return (ITS_SUCCESS);
    }

    return (!ITS_SUCCESS);
}

/****************************************************************************
 *  Purpose:
 *        Process the messages in StatefulServerAuthFsm state
 *
 *  Input Parameters:      
 *        evt : Event to process
 *  
 *  Input/Output Parameters:
 *      ctxt:  Context pointer
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *        ITS_SUCCESS : On successful StatefulServerAuthFsm state process
 *  
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
ITS_INT 
StatefulServerAuthFsm_Idle::ProcessEvent(void *vctxt, ITS_EVENT *evt)
{  
    int ret = FSM_NO_STATE_UPDATE;
    DIA_BASE_CMD *msg = NULL;
    SESSION_ENTRY* ctxt = (SESSION_ENTRY*)vctxt; 
    ITS_UINT st = 0, lt = 0, gp = 0;
    string sessionId;
    ITS_USHORT peerInstance = UNKNOWN_PEER_INST; 
    ITS_BOOLEAN isSTRequired = ITS_FALSE;
 
    DT_DBG(("StatefulServerAuthFsm::Idle --> Evt Type %s", 
             AUTH_SESSION_EVENT_TO_TEXT(DIA_SE_EVT_TYPE(ctxt))));

    switch(DIA_SE_EVT_TYPE(ctxt))
    {
    case AUTH_SESSION_EVT_REQUEST_ACCESS:
        DiaUtils::GetCmdFromData(&msg, &evt->data[sizeof(ITS_USHORT)]);
        //sessionId = msg->getSessionId()->value();

        /* Restart all the Auth Timers */
	//Bug id 1875- Timers commented as per Plan-B requirement 
#ifndef _BRIDGE_WATER_PLAN_B
        SESSION_TABLE->ReStartAllAuthTimers(ctxt, msg);
#endif
        DiaMsgRouter::SendMsgToApp(ctxt, evt);
        break;

    /**
     * Case added for the Downstream request messages received from proxy
     */
    case AUTH_SESSION_EVT_TX_SSAA_AGENT:
    {
        DiaUtils::GetCmdFromEvent(&msg, evt);
        DIA_BASE_CMD *cmd = (DIA_BASE_CMD *)msg;

        if (evt->len == sizeof(DiaMsgToPeerEvt))
        {
            peerInstance = ((DiaMsgToPeerEvt*)(evt->data))->toPeer;
        }

        if (peerInstance != UNKNOWN_PEER_INST)
        {
            DT_DBG(("Application routing. Peer = %d", peerInstance));
            DIA_HDR &hdr = (DIA_HDR&)cmd->getHeader();
            hdr.hh = DiaUtils::GenerateHopByHopId();
            DiaUtils::AddRouteRecordAvp(cmd, ctxt);
            DIA_SE_LOCAL_HH(ctxt) = hdr.hh;
            ret = ITS_SUCCESS;
        }
        else
        {
            /* Try Peer Table Based Routing */
            ret = DiaMsgRouter::RequestForwarding(cmd, ctxt, peerInstance);
            
            if( (cmd->getDestinationHost() != NULL))
            {
                PEER_ENTRY * peerEntry=NULL;
                if(PEER_TABLE->FindEntry(cmd->getDestinationHost()->value().c_str(),peerEntry))
                {
                    if (ret == ITS_DIA_UNABLE_TO_DELIVER && DIA_PE_ALT_HOST(peerEntry) == NULL )
                    {
                        ret = DiaErrHandler::HandleError(DIA_SE_PEER_INST(ctxt), msg,
                                SEND_ERROR_TO_PEER,ITS_DIA_UNABLE_TO_DELIVER);
                        return ret;
                    }
                }
            }
            if(ret != ITS_SUCCESS)
            {
                DT_DBG(("No matching Peer found or Peer isn't active"));
                /*  Try Routing using static routing table */
                ret = DiaMsgRouter::StaticRouting(cmd,ctxt,peerInstance,NULL);

            }
            if (ret != ITS_SUCCESS)
            {
                DT_DBG(("Routing using destination/static routing table failed.try realm routing"));
                /* Try Realm Routing */
                ret = DiaMsgRouter::RequestRouting(cmd,
                        ctxt,
                        peerInstance,
                        NULL);
            }
        }

        if(ret == ITS_SUCCESS && itsDiaConfig.isPredictiveLoopAvoidanceEnable())
        {
            DiaSocketTransport *tr = trTable[peerInstance];
            PEER_ENTRY* pEntry = tr->GetPeer();

            const char *destHost = DIA_PE_HOST(pEntry);
            if(DiaMsgRouter::IsPredectiveLoopDetected(cmd,destHost))
            {
                SESSION_ENTRY *ent     = NULL;
                const char    *sessId  = NULL;
                sessId = msg->getSessionId()->value().c_str();
                if (sessId && SESSION_TABLE->FindEntry(ent,(ITS_OCTET *)sessId,strlen(sessId)) != ITS_SUCCESS)
                {
                    DT_ERR(("Session entry not found.Can not perform predictive loop checking"));
                }
                else if(DiaMsgRouter::SelectAlternatePeerToRoute(destHost,cmd,ent,peerInstance)== ITS_DIA_UNABLE_TO_DELIVER)
                {
                    return ITS_DIA_UNABLE_TO_DELIVER;
                }
                else
                {
                    ret = ITS_SUCCESS;
                }
            }
        }

        if (ret == ITS_SUCCESS)
        {
            DIA_SE_PEER_INST_AGENT(ctxt) = peerInstance;
            if ((ModifyEntry(msg, ctxt) != ITS_SUCCESS))
            {
                 DT_ERR(("Failed to update"));
            }

            DIA_HDR &hdr = (DIA_HDR&)msg->getHeader();

            ret = DiaMsgRouter::SendCmdToPeer(peerInstance,
                                             &hdr,
                                             cmd);
            return ret;

        }
        else
        {
            DT_ERR(("RequestRouting Failed"));
            /**
             * Send Error response as not able to deliver the messge.
             */
            
            ret = DiaErrHandler::HandleError(DIA_SE_PEER_INST(ctxt), msg,
                                             SEND_ERROR_TO_PEER,
                                             ITS_DIA_UNABLE_TO_DELIVER);
            //fix for session count
            if (msg->getSessionId())
            {
                SESSION_ENTRY *ent     = NULL;
                const char    *sessId  = NULL;
                sessId = msg->getSessionId()->value().c_str();
                if (sessId && SESSION_TABLE->FindEntry(ent,(ITS_OCTET *)sessId,strlen(sessId)) == ITS_SUCCESS)
                {
                    ITS_USHORT trInst = DIA_SE_PEER_INST(ent);
                    ((DIA_HDR&)cmd->getHeader()).hh = DIA_SE_RX_HH(ent);
                    if (SESSION_TABLE->RemoveEntry( ent,(ITS_OCTET *)sessId,strlen(sessId)) != ITS_SUCCESS)
                    {
                        DT_WRN(("Failed to remove session Entry : %s", sessId));
                    }
                }
                else
                {
                    DT_WRN(("Session Entry Not found"));
                }
            }
            else
            {
                DT_WRN(("Session Entry Not found"));
            }

            
            return (ret);
        }
        break;
    }

    /**
     * Case Added for the upstream answer message for Proxy
     */ 
    case AUTH_SESSION_EVT_RX_SSAA_AGENT:
        DiaMsgRouter::SendMsgToApp(ctxt, evt);
        break;

    case AUTH_SESSION_EVT_TX_SSAA_OK:
    case AUTH_SESSION_EVT_TX_SSAA_FAIL:
    case AUTH_SESSION_EVT_TX_STA:
    {
        DiaUtils::GetCmdFromEvent(&msg, evt);
        DIA_BASE_CMD *cmd = (DIA_BASE_CMD *)msg;
        sessionId = msg->getSessionId()->value();

        DIA_HDR &hdr = (DIA_HDR &)msg->getHeader();
        hdr.flags.p = (DIA_SE_RX_FLAGS(ctxt)).p;
        hdr.flags.t = (DIA_SE_RX_FLAGS(ctxt)).t;
        hdr.hh = DIA_SE_RX_HH(ctxt);
        hdr.ee = DIA_SE_RX_EE(ctxt);

        /* Validate the ResultCode for Agents */
        if (DIA_SE_IS_AGENT(ctxt) &&
            (isSTRequired = DiaUtils::IsResultCodeModified(msg, ctxt))
                                                   == ITS_TRUE)
        {
            //Warning Fix - suggest parentheses around assignment used as truth value
            if ((ret = DiaMsgRouter::SendCmdToPeer(DIA_SE_PEER_INST(ctxt),
                                                  &hdr,
                                                  cmd)) != ITS_SUCCESS)
            {
               DT_ERR(("Failed to send to Peer ret= %d", ret));
            }
            TerminationCause c(TerminationCause::DIAMETER_ADMINISTRATIVE);
            DT_DBG(("Result Code Modified, Sending STR to Peer"));
            SendSTR((char*)sessionId.c_str(), c, false, false, ctxt);

            DIA_SE_STATE(ctxt) = AUTH_SESSION_ST_DISCON;
            ret = FSM_STATE_UPDATE;
            return ret;
        }


        if (DIA_SE_EVT_TYPE(ctxt) == AUTH_SESSION_EVT_TX_SSAA_OK ||
            DIA_SE_EVT_TYPE(ctxt) == AUTH_SESSION_EVT_RX_SSAA_AGENT)
        {
            /* Restart the Auth Timers based on the AVP values*/
	    //Bug id 1875- Timers commented as per Plan-B requirement
#ifndef _BRIDGE_WATER_PLAN_B
            SESSION_TABLE->ReStartAuthTimers(ctxt, msg);
#endif
        }

        if (DiaMsgRouter::SendCmdToPeer(DIA_SE_PEER_INST(ctxt),
                                        &hdr,
                                        cmd) != ITS_SUCCESS)
        {
            return (ITS_ESENDFAIL);
        }

        if (DIA_SE_EVT_TYPE(ctxt) == AUTH_SESSION_EVT_TX_SSAA_OK)
        {
            DIA_SE_STATE(ctxt) = AUTH_SESSION_ST_OPEN;
            ret = FSM_STATE_UPDATE;
        }
        else if (DIA_SE_EVT_TYPE(ctxt) == AUTH_SESSION_EVT_TX_STA ||
                (DIA_SE_EVT_TYPE(ctxt) == AUTH_SESSION_EVT_TX_SSAA_FAIL))
        {
            Cleanup(ctxt, sessionId);
        }
        break;
    }
    case AUTH_SESSION_EVT_RX_ASA:
        /* No State Change */
        break;
    case AUTH_SESSION_EVT_RX_STR:

        /* Send Inbound STR to Application */
        DiaMsgRouter::SendMsgToApp(ctxt, evt);
        break;
    case AUTH_SESSION_EVT_SESSION_TOUT_ST: /* Un-official cutomization */
    {
        DT_DBG(("Action: Cleanup"));
        char *sessionId = (char *)evt->data;
        Cleanup(ctxt, sessionId);
        ret = FSM_NO_STATE_UPDATE;
        break;

    }
    default:
        DT_ERR(("Invalid Event Type %d",  DIA_SE_EVT_TYPE(ctxt)));

        return (ITS_EBADSTATE);
        
    }          
    return (ret);
}

/********************************************************************/
/** Purpose:
 *      Process the Message in the Open State
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
StatefulServerAuthFsm_Open::ProcessEvent(void *vctxt, ITS_EVENT *evt)
{
    int ret = FSM_NO_STATE_UPDATE;
    SESSION_ENTRY* ctxt = (SESSION_ENTRY*)vctxt; 
    ITS_USHORT peerInst = 0;
    ITS_BOOLEAN isSTRequired; 

    DT_DBG(("StatefulServerAuthFsm::Open --> Evt Type %s", 
             AUTH_SESSION_EVENT_TO_TEXT(DIA_SE_EVT_TYPE(ctxt))));

    switch(DIA_SE_EVT_TYPE(ctxt))
    {
    case AUTH_SESSION_EVT_REQUEST_ACCESS:
    case AUTH_SESSION_EVT_RX_STR:
    case AUTH_SESSION_EVT_RX_ASA:
    case AUTH_SESSION_EVT_RX_RAA_OK:
    case AUTH_SESSION_EVT_RX_RAA_FAIL:
    {
        DIA_BASE_CMD *msg = NULL;
        DiaUtils::GetCmdFromData(&msg, &evt->data[sizeof(ITS_USHORT)]);
        //string sessionId = msg->getSessionId()->value();
        /* No State Change */

        if (DIA_SE_EVT_TYPE(ctxt) == AUTH_SESSION_EVT_RX_RAA_OK &&
            (!DIA_SE_IS_AGENT(ctxt)))
        {
            /* Restart all the Auth Timers */
	    //Bug id 1875- Timers commented as per Plan-B requirement
#ifndef _BRIDGE_WATER_PLAN_B
            SESSION_TABLE->ReStartAllAuthTimers(ctxt, msg);
#endif
        }

        DiaMsgRouter::SendMsgToApp(ctxt, evt);

        break;
    }
    case AUTH_SESSION_EVT_TX_SSAA_OK:
    case AUTH_SESSION_EVT_TX_SSAA_FAIL:
    case AUTH_SESSION_EVT_TX_ASR:
    case AUTH_SESSION_EVT_TX_RAR:
    case AUTH_SESSION_EVT_TX_STA:
    case AUTH_SESSION_EVT_TX_APP_SPECIFIC_REQ_MSG:
    {
        DIA_BASE_CMD *msg = NULL;
        DiaUtils::GetCmdFromEvent(&msg, evt);
        DIA_BASE_CMD *cmd = (DIA_BASE_CMD *)msg;
        string sessionId = msg->getSessionId()->value(); 

        DIA_HDR &hdr = (DIA_HDR &)msg->getHeader();
        if (DIA_SE_EVT_TYPE(ctxt) == AUTH_SESSION_EVT_TX_ASR ||
            DIA_SE_EVT_TYPE(ctxt) == AUTH_SESSION_EVT_TX_RAR )
        {
            hdr.hh = DiaUtils::GenerateHopByHopId();
            if (DIA_SE_IS_AGENT(ctxt))
            {
                DIA_SE_LOCAL_HH(ctxt) = hdr.hh;
                DiaUtils::AddRouteRecordAvp(msg, ctxt);
            }
            else
            {
                hdr.ee = DiaUtils::GenerateEndToEndId();
                /**
                 * Partial fix for issue 874, the end to end id is not saved
                 * properly in the session earlier. Saving the same
                 */
                DIA_SE_RX_EE(ctxt) = hdr.ee;

                /**
                 * In case of non agent the hop by hop should 
                 * be saved in the session context.
                 */
                DIA_SE_RX_HH(ctxt) = hdr.hh;
            }
        }
        else
        {
            hdr.flags.p = (DIA_SE_RX_FLAGS(ctxt)).p;
            hdr.flags.t = (DIA_SE_RX_FLAGS(ctxt)).t;
            hdr.hh = DIA_SE_RX_HH(ctxt);
            hdr.ee = DIA_SE_RX_EE(ctxt);
        }
        /**
         * setting the peer instance outside any scope as it is 
         * valid for all.
         */ 
        peerInst = DIA_SE_PEER_INST(ctxt);

        if (DIA_SE_EVT_TYPE(ctxt) == AUTH_SESSION_EVT_TX_SSAA_OK)
        {
            /* Restart the Auth Timers based on the AVP values*/
	    //Bug id 1875- Timers commented as per Plan-B requirement
#ifndef _BRIDGE_WATER_PLAN_B
            SESSION_TABLE->ReStartAllAuthTimers(ctxt, msg);
#endif
        }

        /* Validate the ResultCode for Agents */
        if (DIA_SE_IS_AGENT(ctxt) &&
            (isSTRequired = DiaUtils::IsResultCodeModified(msg, ctxt))
                                                   == ITS_TRUE)
        {
            //Warning Fix - suggest parentheses around assignment used as truth value
            if ((ret = DiaMsgRouter::SendCmdToPeer(DIA_SE_PEER_INST(ctxt),
                                                  &hdr,
                                                  cmd)) != ITS_SUCCESS)
            {
               DT_ERR(("Failed to send to Peer ret= %d", ret));
            }
            TerminationCause c(TerminationCause::DIAMETER_ADMINISTRATIVE);
            DT_DBG(("Result Code Modified, Sending STR to Peer"));
            SendSTR((char*)sessionId.c_str(), c, false, false, ctxt);

            DIA_SE_STATE(ctxt) = AUTH_SESSION_ST_DISCON;
            ret = FSM_STATE_UPDATE;
            return ret;
        }

        
        if (DiaMsgRouter::SendCmdToPeer(peerInst, &hdr,
                                        cmd) != ITS_SUCCESS)
        {
            return (ITS_ESENDFAIL);
        }

        if (DIA_SE_EVT_TYPE(ctxt) == AUTH_SESSION_EVT_TX_SSAA_FAIL ||
            DIA_SE_EVT_TYPE(ctxt) == AUTH_SESSION_EVT_TX_STA)
        {
            //Fix for coverity issue CID 11718.
            //msg is already freed in SendCmdToPeer
            Cleanup(ctxt, sessionId);
        }
        else if (DIA_SE_EVT_TYPE(ctxt) == AUTH_SESSION_EVT_TX_ASR)
        {
            DIA_SE_STATE(ctxt) = AUTH_SESSION_ST_DISCON;
            ret = FSM_STATE_UPDATE;
        }

        break;
    }

    /**
     * Case added for downstream messages in case of agents
     */ 
    case AUTH_SESSION_EVT_TX_SSAA_AGENT:
    {
        /* Message on an already existing session
           && with a Known peer
           No State Change
        */
        DIA_BASE_CMD *gCmd = NULL;
        DiaUtils::GetCmdFromEvent(&gCmd, evt);
        DIA_BASE_CMD *cmd = (DIA_BASE_CMD *)gCmd;
        string sessionId = gCmd->getSessionId()->value();
        ITS_USHORT peerInstance = UNKNOWN_PEER_INST;
        /*Check if the transport exist to the destination, if no handle by
         * sending 3002 error back to the client*/
        DiaSocketTransport *tr = trTable[DIA_SE_PEER_INST_AGENT(ctxt)];
        if(tr == NULL)
        {
            DT_ERR(("Invalid transport ,Destination host is down"));
            DiaErrHandler::HandleError( DIA_SE_PEER_INST(ctxt),
                                        gCmd, SEND_ERROR_TO_PEER ,
                                        ITS_DIA_UNABLE_TO_DELIVER);
            DIA_SE_MSG_STATUS(ctxt) = ANS_SND_TO_PEER; 

            //Replicate session info
            if( (SessionTable::replicateSessions) && 
                    (SessionTable::sessUpdateCbk!= NULL))
            {
                SessionTable::sessUpdateCbk(sessionId.c_str(),ctxt);
            }
            break;

        }
        else
        {
            PEER_ENTRY *peer = tr->GetPeer();
            if(peer == NULL)
            {
                DT_ERR(("Dest host down,Peer not found for transport"));
                DiaErrHandler::HandleError( DIA_SE_PEER_INST(ctxt),
                                            gCmd, SEND_ERROR_TO_PEER ,
                                            ITS_DIA_UNABLE_TO_DELIVER);
                DIA_SE_MSG_STATUS(ctxt) = ANS_SND_TO_PEER; 

                //Replicate session info
                if( (SessionTable::replicateSessions) && 
                        (SessionTable::sessUpdateCbk!= NULL))
                {
                    SessionTable::sessUpdateCbk(sessionId.c_str(),ctxt);
                }

                break;

            }
            if(gCmd->getDestinationHost() != NULL)
            {
                if(strcasecmp(gCmd->getDestinationHost()->value().c_str(),DIA_PE_HOST(peer))!=0)
                {
                    DT_DBG(("DestinationHost in msg does not match stored peer inst.May be app specific server msg"));
                    PEER_ENTRY * peerEntry = NULL;
                    if(PEER_TABLE->FindEntry(gCmd->getDestinationHost()->value().c_str(), peerEntry))
                    {
                        ITS_USHORT inst = DIA_PE_INST(peerEntry);
                        DiaSocketTransport* DestHostTr = trTable[inst];
                        if (DestHostTr != NULL)
                        {
                            peerInstance = inst;
                        } 

                    }

                }
                else
                {
                    DT_DBG(("DestinationHost in msg match stored peer inst."));
                }

            }

        }

        DIA_HDR &hdr = (DIA_HDR &)gCmd->getHeader();
        /**
         * Add the Route-Record AVP Here
         */
        DiaUtils::AddRouteRecordAvp(gCmd, ctxt);
        hdr.hh = DiaUtils::GenerateHopByHopId();
        DIA_SE_LOCAL_HH(ctxt) = hdr.hh;

        if(peerInstance == UNKNOWN_PEER_INST)
        {
            peerInstance = DIA_SE_PEER_INST_AGENT(ctxt);
        }

        //Warning Fix - suggest parentheses around assignment used as truth value
        if ((ret = DiaMsgRouter::SendCmdToPeer(peerInstance,
                                              &hdr, cmd)) != ITS_SUCCESS)
        {
            DT_ERR(("Failed to send Cmd : ret = %d", ret));
        }

        break;
    }


    /**
     * Case added for upstream messages in case of agents
     */
    case AUTH_SESSION_EVT_RX_SSAA_AGENT:
    {
        DiaMsgRouter::SendMsgToApp(ctxt, evt);
        break;
    }
   
    /**
     * Case added for agent RAA messages
     */ 
    case AUTH_SESSION_EVT_TX_RAA_OK:
    case AUTH_SESSION_EVT_TX_RAA_FAIL:
    {
        DIA_BASE_CMD *gCmd = NULL;
        DiaUtils::GetCmdFromEvent(&gCmd, evt);
        DIA_BASE_CMD *cmd = (DIA_BASE_CMD *)gCmd;
        DIA_HDR &hdr = (DIA_HDR &)gCmd->getHeader();

        if (DIA_SE_EVT_TYPE(ctxt) == AUTH_SESSION_EVT_TX_RAA_OK)
        {
            /* Restart all the Auth Timers */
	    //Bug id 1875- Timers commented as per Plan-B requirement
#ifndef _BRIDGE_WATER_PLAN_B
            SESSION_TABLE->ReStartAllAuthTimers(ctxt, gCmd);
#endif
        }
        //Warning Fix - suggest parentheses around assignment used as truth value
        if ((ret = DiaMsgRouter::SendCmdToPeer(DIA_SE_PEER_INST_AGENT(ctxt),
                                                 &hdr, cmd)) != ITS_SUCCESS)
        {
            DT_ERR(("Failed to send Cmd : ret = %d", ret));
        }
        break;
    }
        
    case AUTH_SESSION_EVT_LIFETIME_TOUT:
    {
        DT_DBG(("StatefulServerAuthFsm:: Open ---> LIFETIME_TOUT"));
        DT_DBG(("Action: Cleanup"));
        char *sessionId = (char *)evt->data;

        Cleanup(ctxt, sessionId);
        ret = FSM_NO_STATE_UPDATE;

        break;
    }
    case AUTH_SESSION_EVT_SESSION_TOUT_ST:
    {
        DT_DBG(("StatefulServerAuthFsm:: Open ---> SESSION_TOUT_ST"));
        DT_DBG(("Action: Cleanup"));
        char *sessionId = (char *)evt->data;

        Cleanup(ctxt, sessionId);
        ret = FSM_NO_STATE_UPDATE;

        break;
    }
    default:
        DT_ERR(("Invalid Event Type"));

        return (ITS_EBADSTATE);
    }
    return (ret);
}

/********************************************************************/
/** Purpose:
 *      Process the Message in Disconnect State
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
StatefulServerAuthFsm_Discon::ProcessEvent(void *vctxt, ITS_EVENT *evt)
{
    int ret = FSM_NO_STATE_UPDATE;
    SESSION_ENTRY* ctxt = (SESSION_ENTRY*)vctxt;
    ITS_USHORT peerInst;
 
    DT_DBG(("StatefulServerAuthFsm::Discon --> Evt Type %s", 
             AUTH_SESSION_EVENT_TO_TEXT(DIA_SE_EVT_TYPE(ctxt))));

    switch(DIA_SE_EVT_TYPE(ctxt))
    {
    case AUTH_SESSION_EVT_TX_ASR_FAIL:
        DT_DBG(("StatefulServerAuthFsm::Discon --->Fail to send ASR"));
        DT_DBG(("Action: Wait : Resend ASR"));

        break;

    case AUTH_SESSION_EVT_RX_ASA_OK:
    case AUTH_SESSION_EVT_RX_ASA:
    case AUTH_SESSION_EVT_RX_ASA_FAIL:
    case AUTH_SESSION_EVT_RX_STR:
     case AUTH_SESSION_EVT_REQUEST_ACCESS:
    {
        DIA_BASE_CMD *msg = NULL;
        DiaUtils::GetCmdFromData(&msg, &evt->data[sizeof(ITS_USHORT)]);
        string sessionId = msg->getSessionId()->value();
        DiaMsgRouter::SendMsgToApp(ctxt, evt);

        if (DIA_SE_EVT_TYPE(ctxt) == AUTH_SESSION_EVT_RX_ASA_FAIL &&
            !(DIA_SE_IS_AGENT(ctxt)))
        {
            Cleanup(ctxt, sessionId);
        }

        break;
    }
    case AUTH_SESSION_EVT_TX_STA:
    case AUTH_SESSION_EVT_TX_APP_SPECIFIC_REQ_MSG:
    {
        DIA_BASE_CMD *msg = NULL;
        DiaUtils::GetCmdFromEvent(&msg, evt);
        DIA_BASE_CMD *cmd = (DIA_BASE_CMD *)msg;
        string sessionId = msg->getSessionId()->value();

        DIA_HDR &hdr = (DIA_HDR &)msg->getHeader();
        hdr.flags.p = (DIA_SE_RX_FLAGS(ctxt)).p;
        hdr.flags.t = (DIA_SE_RX_FLAGS(ctxt)).t;
        hdr.hh = DIA_SE_RX_HH(ctxt);
        hdr.ee = DIA_SE_RX_EE(ctxt);
        if (DiaMsgRouter::SendCmdToPeer(DIA_SE_PEER_INST(ctxt),
                                        &hdr,
                                        cmd) != ITS_SUCCESS)
        {
            return (ITS_ESENDFAIL);
        }
        if( AUTH_SESSION_EVT_TX_STA == DIA_SE_EVT_TYPE(ctxt))
        {
            Cleanup(ctxt, sessionId);
        }
        break;
    }
    
    /**
     * Case added for when the result code in modified 
     * from success to failure and STR is sent.
     * Handling the STA received
     */ 
    case AUTH_SESSION_EVT_RX_STA:
    {
        if(!(DIA_SE_IS_AGENT(ctxt)))
        {
           DT_ERR(("Invalid Event Type"));
           return (ITS_EBADSTATE);
        }
       
        DIA_BASE_CMD *msg = NULL;
        DiaUtils::GetCmdFromData(&msg, &evt->data[sizeof(ITS_USHORT)]);
        DiaMsgRouter::SendMsgToApp(ctxt, evt);
        string sessionId = msg->getSessionId()->value();
        Cleanup(ctxt, sessionId);
        break;
    }

    /**
     * Case added for upstream messages in case of agents
     */
    case AUTH_SESSION_EVT_RX_SSAA_AGENT:
    {
        DiaMsgRouter::SendMsgToApp(ctxt, evt);
        break;
    }

    /**
     * Case added for the ASA
     */
    case AUTH_SESSION_EVT_TX_ASA_OK:
    case AUTH_SESSION_EVT_TX_ASA_FAIL:
    {
        DIA_BASE_CMD *msg = NULL;
        DiaUtils::GetCmdFromEvent(&msg, evt);
        DIA_BASE_CMD *cmd = (DIA_BASE_CMD *)msg;
        DIA_HDR &hdr = (DIA_HDR &)msg->getHeader();
        string sessionId = msg->getSessionId()->value();

        if (DiaMsgRouter::SendCmdToPeer(DIA_SE_PEER_INST_AGENT(ctxt),
                                        &hdr,
                                        cmd) != ITS_SUCCESS)
        {
            return (ITS_ESENDFAIL);
        }

        if (DIA_SE_EVT_TYPE(ctxt) == AUTH_SESSION_EVT_RX_ASA_FAIL)
        {
            Cleanup(ctxt, sessionId);
        }
        break;
     
    }

    /**
     * Case added for downstream messages in case of agents
     */
    case AUTH_SESSION_EVT_TX_SSAA_AGENT:
    {
        /* Message on an already existing session
           && with a Known peer
           No State Change
        */
        DIA_BASE_CMD *gCmd = NULL;
        DiaUtils::GetCmdFromEvent(&gCmd, evt);
        DIA_BASE_CMD *cmd = (DIA_BASE_CMD *)gCmd;
        string sessionId = gCmd->getSessionId()->value();

        DIA_HDR &hdr = (DIA_HDR &)gCmd->getHeader();
        /**
         * Add the Route-Record AVP Here
         */
        DiaUtils::AddRouteRecordAvp(gCmd, ctxt);
        hdr.hh = DiaUtils::GenerateHopByHopId();
        DIA_SE_LOCAL_HH(ctxt) = hdr.hh;

        //Warning Fix - suggest parentheses around assignment used as truth value
        if ((ret = DiaMsgRouter::SendCmdToPeer(DIA_SE_PEER_INST_AGENT(ctxt),
                                              &hdr, cmd)) != ITS_SUCCESS)
        {
            DT_ERR(("Failed to send Cmd : ret = %d", ret));
        }
break;
    }
      
 case AUTH_SESSION_EVT_TX_SSAA_OK:
    {
	DIA_BASE_CMD *msg = NULL;
	ITS_BOOLEAN isSTRequired = ITS_FALSE;
        DiaUtils::GetCmdFromEvent(&msg, evt);
        DIA_BASE_CMD *cmd = (DIA_BASE_CMD *)msg;
        string sessionId = msg->getSessionId()->value();

        DIA_HDR &hdr = (DIA_HDR &)msg->getHeader();
        hdr.flags.p = (DIA_SE_RX_FLAGS(ctxt)).p;
        hdr.flags.t = (DIA_SE_RX_FLAGS(ctxt)).t;
        hdr.hh = DIA_SE_RX_HH(ctxt);
        hdr.ee = DIA_SE_RX_EE(ctxt);

        if (DIA_SE_IS_AGENT(ctxt) &&
            (isSTRequired = DiaUtils::IsResultCodeModified(msg, ctxt))
                                                   == ITS_TRUE)
        {
            if ((ret = DiaMsgRouter::SendCmdToPeer(DIA_SE_PEER_INST(ctxt),
                                                  &hdr,
                                                  cmd)) != ITS_SUCCESS)
            {
               DT_ERR(("Failed to send to Peer ret= %d", ret));
            }
            TerminationCause c(TerminationCause::DIAMETER_ADMINISTRATIVE);
            DT_DBG(("Result Code Modified, Sending STR to Peer"));
            SendSTR((char*)sessionId.c_str(), c, false, false, ctxt);

            DIA_SE_STATE(ctxt) = AUTH_SESSION_ST_DISCON;
            ret = FSM_STATE_UPDATE;
            return ret;
        }


        if (DiaMsgRouter::SendCmdToPeer(DIA_SE_PEER_INST(ctxt),
                                        &hdr,
                                        cmd) != ITS_SUCCESS)
        {
            return (ITS_ESENDFAIL);
        }
        break;
    }  

    default:
        DT_ERR(("Invalid Event Type"));

        return (ITS_EBADSTATE);

    }
    return (ret);
}

/****************************************************************************
 *  Purpose:
 *        Process the messages in StatefulClientAuthFsm state
 *
 *  Input Parameters:      
 *        evt : Event to process
 *  
 *  Input/Output Parameters:
 *      ctxt:  Context pointer
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *        ITS_SUCCESS : On successful StatefulClientAuthFsm state process
 *  
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
ITS_INT 
StatefulClientAuthFsm_Idle::ProcessEvent(void *vctxt, ITS_EVENT *evt)
{  
    int ret = FSM_NO_STATE_UPDATE; 
    SESSION_ENTRY* ctxt = (SESSION_ENTRY*)vctxt; 
 
    DT_DBG(("StatefulClientAuthFsm::Idle --> Evt Type %s", 
             AUTH_SESSION_EVENT_TO_TEXT(DIA_SE_EVT_TYPE(ctxt))));

    switch(DIA_SE_EVT_TYPE(ctxt))
    {
    case AUTH_SESSION_EVT_REQUEST_ACCESS:
      {
        ITS_USHORT peerInstance;

        DIA_BASE_CMD *gCmd = NULL;
        DiaUtils::GetCmdFromEvent(&gCmd, evt);
        DIA_BASE_CMD *cmd = (DIA_BASE_CMD *)gCmd;

        /* Try Peer Table Based Routing */
        ret = DiaMsgRouter::RequestForwarding(cmd, ctxt, peerInstance);

        if (ret == ITS_DIA_UNABLE_TO_DELIVER)
        {
            // If the destination host is present and is a peer, then indicate
            // the application about the request forwarding failure.
            DT_DBG(("Unable to deliver to peer mentioned in Destination Host!"));
            return ret;
        }

        if (ret !=ITS_SUCCESS)
        {
            DT_DBG(("No matching Peer found or Peer isn't active"));
            /*  Try Routing using static routing table */
            ret = DiaMsgRouter::StaticRouting(cmd,ctxt,peerInstance,NULL);
        } 
        
        if (ret !=ITS_SUCCESS)
        {
            DT_DBG(("Routing using static routing table failed.try realm routing"));
            
            /* Try Realm Routing */
            ret = DiaMsgRouter::RequestRouting(cmd,
                                               ctxt,
                                               peerInstance,
                                               NULL);
            if (ret != ITS_SUCCESS)
            {
                DT_ERR(("No matching Realm Found"));
                return (ret);
            }
        }

        DIA_SE_STATE(ctxt) = AUTH_SESSION_ST_PENDING;
        DIA_SE_PEER_INST(ctxt) = peerInstance;
        //Fix for coverity CID11717.Fetch session id.
        //As msg will be freed in SendCmdToPeer
        std::string sessionId;
        if (gCmd->getSessionId())
        {
            sessionId = gCmd->getSessionId()->value();
        }
        //End of fix for CID11717
        if ((ret = InsertEntry(gCmd, ctxt)) == ITS_SUCCESS)
        {
            DIA_HDR &hdr = (DIA_HDR&)gCmd->getHeader();
            ret = DiaMsgRouter::SendCmdToPeer(peerInstance,
                                             &hdr,
                                             cmd);
        } 
        if (ret != ITS_SUCCESS)
        {
            if (SESSION_TABLE->RemoveEntry(ctxt, (ITS_OCTET *)sessionId.c_str(),
                                            (sessionId.length()))
                                            != ITS_SUCCESS)
            {
                DT_ERR(("Failed to remove session Entry"));
            }
        }
      }  
      break;

    default:
        DT_ERR(("Invalid Event Type"));

        return (ITS_EBADSTATE);
        
    }          
    return (ret);
}

/****************************************************************************
 *  Purpose:
 *        Process the messages in StatefulClientAuthFsm state
 *
 *  Input Parameters:      
 *        evt : Event to process
 *  
 *  Input/Output Parameters:
 *      ctxt:  Context pointer
 *      evt:   ITS_EVENT pointer
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *        ITS_SUCCESS : On successful StatefulClientAuthFsm state process
 *  
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
ITS_INT
StatefulClientAuthFsm_Pending::ProcessEvent(void *vctxt, ITS_EVENT *evt)
{
    int ret = FSM_NO_STATE_UPDATE;

    SESSION_ENTRY* ctxt = (SESSION_ENTRY*)vctxt;
    DIA_BASE_CMD *msg = NULL;
    DIA_BASE_CMD *cmd = NULL;
    ITS_UINT st = 0, lt = 0, gp = 0;
    string sessionId;

    DT_DBG(("StatefulClientAuthFsm::Pending --> Evt Type %s", 
             AUTH_SESSION_EVENT_TO_TEXT(DIA_SE_EVT_TYPE(ctxt))));

    switch(DIA_SE_EVT_TYPE(ctxt))
    {
    case AUTH_SESSION_EVT_RX_APP_SPECIFIC_REQ_MSG:
        { 
           //TODO :: to be droped or tobe processed ?
           DiaUtils::GetCmdFromData(&msg, &evt->data[sizeof(ITS_USHORT)]);
           DiaMsgRouter::SendMsgToApp(ctxt, evt);
           break;

        }
    case AUTH_SESSION_EVT_RX_SSAA_OK:
        DiaUtils::GetCmdFromData(&msg, &evt->data[sizeof(ITS_USHORT)]);
        cmd = (DIA_BASE_CMD *)msg;
        sessionId = msg->getSessionId()->value();

        /* Restart all the Auth Timers */
        SESSION_TABLE->ReStartAllAuthTimers(ctxt, msg);
        
        DiaMsgRouter::SendMsgToApp(ctxt, evt);
       
        /* State Change */
        DIA_SE_STATE(ctxt) = AUTH_SESSION_ST_OPEN;

        DT_DBG(("StatefulClient-->OPEN State"));

        ret = FSM_STATE_UPDATE;

        break;
    case AUTH_SESSION_EVT_RX_SSAA_FAIL:
    {
        DiaUtils::GetCmdFromData(&msg, &evt->data[sizeof(ITS_USHORT)]);
        sessionId = msg->getSessionId()->value();

        DiaMsgRouter::SendMsgToApp(ctxt, evt);

        Cleanup(ctxt, sessionId);

        break;
    }
    case AUTH_SESSION_EVT_TX_STR:   
    {
        /* STR Will be sent by application 
           to depict service not provided 
           or error processing successful auth answer
        */
        DiaUtils::GetCmdFromEvent(&msg, evt);
        cmd = (DIA_BASE_CMD *)msg;

        DT_DBG(("StatefulClientAuthFsm::Pending --->STR"));
        DT_DBG(("Action: Sent STR"));

        DIA_HDR &hdr = (DIA_HDR &)msg->getHeader();
        hdr.hh = DiaUtils::GenerateHopByHopId();
        /**
         * In case of non agent the hop by hop should 
         * be saved in the session context.
         */
        DIA_SE_RX_HH(ctxt) = hdr.hh;

        hdr.ee = DiaUtils::GenerateEndToEndId(); 
        /**
         * Partial fix for issue 874, the end to end id is not saved
         * properly in the session earlier. Saving the same
         */
        /* State Change */
        DIA_SE_RX_EE(ctxt) = hdr.ee;
        DIA_SE_STATE(ctxt) = AUTH_SESSION_ST_DISCON;

        if ((ModifyEntry(msg, ctxt) != ITS_SUCCESS))
        {
             DT_ERR(("Failed to update"));
        }

        if (DiaMsgRouter::SendCmdToPeer(DIA_SE_PEER_INST(ctxt),
                                        &hdr,
                                        cmd) != ITS_SUCCESS)
        {
            return (ITS_ESENDFAIL);
        }

        break;
    }
    case AUTH_SESSION_EVT_TX_APP_SPECIFIC_RES_MSG:
    {
        /* Message on an already existing session
         * && with a Known peer  No State Change
         */
        DiaUtils::GetCmdFromEvent(&msg, evt);
        cmd = (DIA_BASE_CMD *)msg;

        DIA_HDR &hdr = (DIA_HDR &)msg->getHeader();
        hdr.flags.p = (DIA_SE_RX_FLAGS(ctxt)).p;
        hdr.flags.t = (DIA_SE_RX_FLAGS(ctxt)).t;
        hdr.hh = DIA_SE_RX_HH(ctxt);
        hdr.ee = DIA_SE_RX_EE(ctxt);

        if (ret = DiaMsgRouter::SendCmdToPeer(DIA_SE_PEER_INST(ctxt),
                    &hdr, cmd) != ITS_SUCCESS)
        {
            DT_ERR(("Failed to send Cmd : ret = %d", ret));
        }
        break;
    }
    case AUTH_SESSION_EVT_REQUEST_ACCESS: /* Un-official cutomization for loadtest */
    {     
        DiaUtils::GetCmdFromEvent(&msg, evt);
        cmd = (DIA_BASE_CMD *)msg;
        ITS_USHORT peerInstance;

        /* Try Peer Table Based Routing */
        ret = DiaMsgRouter::RequestForwarding(cmd, ctxt, peerInstance);

        if (ret == ITS_DIA_UNABLE_TO_DELIVER)
        {
            // If the destination host is present and is a peer, then indicate
            // the application about the request forwarding failure.
            DT_DBG(("Unable to deliver to peer mentioned in Destination Host!"));
            return ret;
        }
       
        if (ret != ITS_SUCCESS)
        {
            DT_DBG(("No matching Peer found or Peer isn't active"));
            /*  Try Routing using static routing table  */
            ret = DiaMsgRouter::StaticRouting(cmd,ctxt,peerInstance,NULL);
        } 
        if (ret != ITS_SUCCESS)
        {
            DT_DBG(("Routing using static routing table failed.try realm routing"));

            /* Try Realm Routing */
            ret = DiaMsgRouter::RequestRouting(cmd,
                                               ctxt,
                                               peerInstance,
                                               NULL);
            if (ret != ITS_SUCCESS)
            {
                DT_ERR(("No matching Realm Found"));
                return (ret);
            }
        }

        DIA_SE_STATE(ctxt) = AUTH_SESSION_ST_PENDING;
        DIA_SE_PEER_INST(ctxt) = peerInstance;

        if (ret == ITS_SUCCESS)
        {
            if ((ModifyEntry(msg, ctxt) != ITS_SUCCESS))
            {
                 DT_ERR(("Failed to update"));
            }

            DIA_HDR &hdr = (DIA_HDR&)msg->getHeader();

            ret = DiaMsgRouter::SendCmdToPeer(peerInstance,
                                             &hdr,
                                             cmd);
            return ret;

        }

        break;
    }
    case AUTH_SESSION_EVT_SESSION_TOUT_ST: /* Un-official cutomization */
    {
        char *sessionId = (char *)evt->data;
        Cleanup(ctxt, sessionId);

        break;
    }
    default:
        DT_ERR(("Invalid Event Type"));

        return (ITS_EBADSTATE);
    }

    return (ret);
}

/****************************************************************************
 *  Purpose:
 *        Process the messages in StatefulClientAuthFsm state
 *
 *  Input Parameters:      
 *        evt : Event to process
 *  
 *  Input/Output Parameters:
 *      vctxt:  Context pointer
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *        ITS_SUCCESS : On successful StatefulClientAuthFsm state process
 *  
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
ITS_INT
StatefulClientAuthFsm_Open::ProcessEvent(void *vctxt, ITS_EVENT *evt)
{
    int ret = FSM_NO_STATE_UPDATE;
    SESSION_ENTRY* ctxt = (SESSION_ENTRY*)vctxt;

    DT_DBG(("StatefulClientAuthFsm::Open --> Evt Type %s", 
             AUTH_SESSION_EVENT_TO_TEXT(DIA_SE_EVT_TYPE(ctxt))));

    switch(DIA_SE_EVT_TYPE(ctxt))
    {
    case AUTH_SESSION_EVT_REQUEST_ACCESS:
    case AUTH_SESSION_EVT_TX_STR:
    case AUTH_SESSION_EVT_TX_ASA_OK:
    case AUTH_SESSION_EVT_TX_ASA_FAIL:
    case AUTH_SESSION_EVT_TX_RAA_OK:
    case AUTH_SESSION_EVT_TX_RAA_FAIL:
    case AUTH_SESSION_EVT_TX_APP_SPECIFIC_RES_MSG:
     {
        /* Message on an already existing session
           && with a Known peer
           No State Change
        */
        DIA_BASE_CMD *gCmd = NULL;
        DiaUtils::GetCmdFromEvent(&gCmd, evt);
        DIA_BASE_CMD *cmd = (DIA_BASE_CMD *)gCmd;
        string sessionId = gCmd->getSessionId()->value();

        DIA_HDR &hdr = (DIA_HDR &)gCmd->getHeader();
        if (cmd->GetFlags() & diameter::DIA_REROUTE_REQ)
        {
            ITS_USHORT peerInstance = UNKNOWN_PEER_INST;
            // Rerouting requested, added for DCCA Retry
            /* Try Peer Table Based Routing */
            ret = DiaMsgRouter::RequestForwarding(cmd, ctxt, peerInstance);

            if (ret == ITS_DIA_UNABLE_TO_DELIVER)
            {
                DT_DBG(("Reroute failed: Peer down, unable to deliver"));
                return ret;
            }

            if (ret != ITS_SUCCESS)
            {
                DT_DBG(("Reroute: No matching Peer found or Peer isn't active"));
                /*  Try Routing using static routing table */
                ret = DiaMsgRouter::StaticRouting(cmd,ctxt,peerInstance,NULL);
            } 

            if (ret !=ITS_SUCCESS)
            {
                DT_DBG(("Reroute: Routing using static routing table failed.try realm routing"));

                /* Try Realm Routing */
                ret = DiaMsgRouter::RequestRouting(cmd,
                        ctxt,
                        peerInstance,
                        NULL);
                if (ret != ITS_SUCCESS)
                {
                    DT_ERR(("Reroute: No matching Realm Found"));
                    return (ret);
                }
            }
            DT_DBG(("Reroute: selected peer %d", peerInstance));
            DIA_SE_PEER_INST(ctxt) = peerInstance;
        }
        else if (DIA_SE_EVT_TYPE(ctxt) == AUTH_SESSION_EVT_REQUEST_ACCESS ||
            DIA_SE_EVT_TYPE(ctxt) == AUTH_SESSION_EVT_TX_STR)
        {
            hdr.hh = DiaUtils::GenerateHopByHopId();
            /**
             * In case of non agent the hop by hop should 
             * be saved in the session context.
             */
            DIA_SE_RX_HH(ctxt) = hdr.hh;

            hdr.ee = DiaUtils::GenerateEndToEndId(); 
            /**
             * Partial fix for issue 874, the end to end id is not saved
             * properly in the session earlier. Saving the same
             */
            DIA_SE_RX_EE(ctxt) = hdr.ee;
        }
        else
        {
            hdr.flags.p = (DIA_SE_RX_FLAGS(ctxt)).p;
            hdr.flags.t = (DIA_SE_RX_FLAGS(ctxt)).t;
            hdr.hh = DIA_SE_RX_HH(ctxt);
            hdr.ee = DIA_SE_RX_EE(ctxt);
        }

        /* Setting or Overiding destination host
         * On an existing session both peers are known
         * hence destination host are automatically set by stack
         * if wrong value is set by application
         */
        ITSDiaConfig* cfg = &itsDiaConfig;
        ITS_NODE_STATE state;


        if ((DIA_SE_EVT_TYPE(ctxt) == AUTH_SESSION_EVT_TX_STR) ||
            (DIA_SE_EVT_TYPE(ctxt) == AUTH_SESSION_EVT_TX_ASA_OK &&
              itsDiaConfig.DisableStackInitiatedSTR() == false))
        {
            /* State Change */
            DIA_SE_STATE(ctxt) = AUTH_SESSION_ST_DISCON;
            if ((ModifyEntry(gCmd, ctxt) != ITS_SUCCESS))
            {
                 DT_ERR(("Failed to update"));
            }
        }

        //Warning Fix - suggest parentheses around assignment used as truth value
        if ((ret = DiaMsgRouter::SendCmdToPeer(DIA_SE_PEER_INST(ctxt),
                                              &hdr, cmd)) != ITS_SUCCESS)
        {
            DT_ERR(("Failed to send Cmd : ret = %d", ret));
            if (ret == ITS_EBADTRANSPORT || ret == ITS_ENOTFOUND)
            {
                // Peer down or not in open state
                return ITS_DIA_UNABLE_TO_DELIVER;
            }
        }

        if (DIA_SE_EVT_TYPE(ctxt) == AUTH_SESSION_EVT_TX_ASA_OK)
        {
            if (itsDiaConfig.DisableStackInitiatedSTR() == false)
            {
                TerminationCause c(TerminationCause::DIAMETER_LOGOUT);
                SendSTR((char *)sessionId.c_str(), c, false, false, ctxt);
            }
        }

        break;
     }
    case AUTH_SESSION_EVT_RX_SSAA_OK:
    case AUTH_SESSION_EVT_RX_SSAA_FAIL:
    case AUTH_SESSION_EVT_RX_ASR:
    case AUTH_SESSION_EVT_RX_APP_SPECIFIC_REQ_MSG:
    case AUTH_SESSION_EVT_RX_RAR:
    {
        DIA_BASE_CMD *msg = NULL;
        DiaUtils::GetCmdFromData(&msg, &evt->data[sizeof(ITS_USHORT)]);
        string sessionId = msg->getSessionId()->value();

        if (DIA_SE_EVT_TYPE(ctxt) == AUTH_SESSION_EVT_RX_SSAA_OK)
        {
            /* Restart the Auth Timers based on the AVPs*/
            SESSION_TABLE->ReStartAllAuthTimers(ctxt, msg);
        }

        DiaMsgRouter::SendMsgToApp(ctxt, evt);

        if (DIA_SE_EVT_TYPE(ctxt) == AUTH_SESSION_EVT_RX_SSAA_FAIL)
        {
            /* CHECK ME */
            Cleanup(ctxt, sessionId);
        }

        break; 
    }
    case AUTH_SESSION_EVT_SESSION_TOUT_ST:
    {
        if (itsDiaConfig.DisableStackInitiatedSTR() == false)
        {
            char *sessionId = (char *)evt->data;
            TerminationCause c(TerminationCause::DIAMETER_SESSION_TIMEOUT);
            SendSTR(sessionId, c,
                    false, false, ctxt);

            DIA_SE_STATE(ctxt) = AUTH_SESSION_ST_DISCON;
            ret = FSM_STATE_UPDATE;
        } 
        break;
    }
    case AUTH_SESSION_EVT_LIFETIME_TOUT:
    {
        if (itsDiaConfig.DisableStackInitiatedSTR() == false)
        {
            char *sessionId = (char *)evt->data;
            TerminationCause c(TerminationCause::DIAMETER_AUTH_EXPIRED);
            SendSTR(sessionId, c, false, false, ctxt);

            DIA_SE_STATE(ctxt) = AUTH_SESSION_ST_DISCON;
            ret = FSM_STATE_UPDATE;
        }
        break;
    }
    default:
        DT_ERR(("Invalid Event Type"));

        return (ITS_EBADSTATE);

    }
    return (ret); 
}

/****************************************************************************
 *  Purpose:
 *        Process the messages in StatefulClientAuthFsm state
 *
 *  Input Parameters:      
 *        evt : Event to process
 *  
 *  Input/Output Parameters:
 *      vctxt:  Context pointer
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *        ITS_SUCCESS : On successful StatefulClientAuthFsm state process
 *  
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
ITS_INT
StatefulClientAuthFsm_Discon::ProcessEvent(void *vctxt, ITS_EVENT *evt)
{
    int ret = FSM_NO_STATE_UPDATE;
    SESSION_ENTRY* ctxt = (SESSION_ENTRY*)vctxt;

    DT_DBG(("StatefulClientAuthFsm::Discon --> Evt Type %s", 
             AUTH_SESSION_EVENT_TO_TEXT(DIA_SE_EVT_TYPE(ctxt))));

    switch(DIA_SE_EVT_TYPE(ctxt))
    {
    case AUTH_SESSION_EVT_RX_ASR:
    case AUTH_SESSION_EVT_RX_APP_SPECIFIC_REQ_MSG:
    case AUTH_SESSION_EVT_RX_STA:
    {
        DIA_BASE_CMD *msg = NULL;
        DiaUtils::GetCmdFromData(&msg, &evt->data[sizeof(ITS_USHORT)]);
        string sessionId = msg->getSessionId()->value();

        DiaMsgRouter::SendMsgToApp(ctxt, evt);

        if (DIA_SE_EVT_TYPE(ctxt) == AUTH_SESSION_EVT_RX_STA)
        {
            /* CHECK ME */
            Cleanup(ctxt, sessionId);
        }

        break;
    }
    case AUTH_SESSION_EVT_TX_APP_SPECIFIC_RES_MSG:
    case AUTH_SESSION_EVT_TX_ASA:
    {
         /* Message on an already existing session
           && with a Known peer
           No State Change
        */
        DIA_BASE_CMD *gCmd = NULL;
        DiaUtils::GetCmdFromEvent(&gCmd, evt);
        DIA_BASE_CMD *cmd = (DIA_BASE_CMD *)gCmd;

        DIA_HDR &hdr = (DIA_HDR &)gCmd->getHeader();
        hdr.flags.p = (DIA_SE_RX_FLAGS(ctxt)).p;
        hdr.flags.t = (DIA_SE_RX_FLAGS(ctxt)).t;
        hdr.hh = DIA_SE_RX_HH(ctxt);
        hdr.ee = DIA_SE_RX_EE(ctxt);

        //Warning Fix - suggest parentheses around assignment used as truth value
        if ((ret = DiaMsgRouter::SendCmdToPeer(DIA_SE_PEER_INST(ctxt),
                                              &hdr, cmd)) != ITS_SUCCESS)
        {
            DT_ERR(("Failed to send Cmd : ret = %d", ret));
        }

        break;
    }
    default:
        DT_ERR(("Invalid Event Type"));

        return (ITS_EBADSTATE);

    }
    return ret;
}

/****************************************************************************
 *  Purpose:
 *        Process the messages in StatelessClientAuthFsm state
 *
 *  Input Parameters:      
 *        evt : Event to process
 *  
 *  Input/Output Parameters:
 *      vctxt:  Context pointer
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *        ITS_SUCCESS : On successful StatelessClientAuthFsm state process
 *  
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
ITS_INT
StatelessClientAuthFsm_Idle::ProcessEvent(void *vctxt, ITS_EVENT *evt)
{
    ITS_USHORT peerInstance;
    int ret = FSM_NO_STATE_UPDATE;

    SESSION_ENTRY* ctxt = (SESSION_ENTRY*)vctxt;

    DT_DBG(("StatelessClientAuthFsm::Idle --> Evt Type %s", 
             AUTH_SESSION_EVENT_TO_TEXT(DIA_SE_EVT_TYPE(ctxt))));

    switch(DIA_SE_EVT_TYPE(ctxt))
    {
    case AUTH_SESSION_EVT_REQUEST_ACCESS:
    {
        DT_DBG(("StatelessClientAuthFsm::Idle --->Requests Access"));
        DT_DBG(("Action: Send SSAR"));

        DIA_BASE_CMD *msg = NULL;
        DiaUtils::GetCmdFromEvent(&msg, evt);
        DIA_BASE_CMD *cmd = (DIA_BASE_CMD *)msg;

        /* Try Peer Table Based Routing */
        ret = DiaMsgRouter::RequestForwarding(cmd, ctxt, peerInstance);

        if (ret == ITS_DIA_UNABLE_TO_DELIVER)
        {
            // If the destination host is present and is a peer, then indicate
            // the application about the request forwarding failure.
            DT_DBG(("Unable to deliver to peer mentioned in Destination Host!"));
            return ret;
        }
        if (ret != ITS_SUCCESS)
        {
            DT_DBG(("No matching Peer found or Peer isn't active"));
            /*  Try Routing using static routing table */
            ret = DiaMsgRouter::StaticRouting(cmd,ctxt,peerInstance,NULL);
        }
        if (ret != ITS_SUCCESS)
        {
            DT_DBG(("Routing using static routing table failed.try realm routing"));

            /* Try Realm Routing */
            ret = DiaMsgRouter::RequestRouting(cmd,
                                               ctxt,
                                               peerInstance,
                                               NULL);
            if (ret != ITS_SUCCESS)
            {
                DT_ERR(("No matching Realm Found"));
                return (ret);
            }
        }

        DIA_SE_STATE(ctxt) = AUTH_SESSION_ST_PENDING;
        DIA_SE_PEER_INST(ctxt) = peerInstance;
        //Fix for coverity CID11719.Fetch session id.in case of failure
        //as msg will be freed in SendCmdToPeer
        std::string sessionId;
        if (msg->getSessionId())
        {
            sessionId = msg->getSessionId()->value();
        }
        //End of fix for CID11719

        if ((ret = InsertEntry(msg, ctxt)) == ITS_SUCCESS)
        {
            DIA_HDR &hdr = (DIA_HDR&)msg->getHeader();
            ret = DiaMsgRouter::SendCmdToPeer(peerInstance,
                                             &hdr,
                                             cmd);
        }
        if (ret != ITS_SUCCESS)
        {
            if (SESSION_TABLE->RemoveEntry(ctxt, (ITS_OCTET *)sessionId.c_str(),
                                            (sessionId.length()))
                                            != ITS_SUCCESS)
            {
                DT_ERR(("Failed to remove session Entry"));
            }
        }

        break;
    }
    default:
        DT_ERR(("Invalid Event Type"));

        return (ITS_EBADSTATE);

    }
    return (ret);
}

/****************************************************************************
 *  Purpose:
 *        Process the messages in StatelessClientAuthFsm state
 *
 *  Input Parameters:      
 *        evt : Event to process
 *  
 *  Input/Output Parameters:
 *      vctxt:  Context pointer
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *        ITS_SUCCESS : On successful StatelessClientAuthFsm state process
 *  
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
ITS_INT
StatelessClientAuthFsm_Pending::ProcessEvent(void *vctxt, ITS_EVENT *evt)
{
    int ret = FSM_NO_STATE_UPDATE;
    SESSION_ENTRY* ctxt = (SESSION_ENTRY*)vctxt;
    DIA_BASE_CMD *msg = NULL;

    DT_DBG(("StatelessClientAuthFsm::Pending --> Evt Type %s", 
             AUTH_SESSION_EVENT_TO_TEXT(DIA_SE_EVT_TYPE(ctxt))));

    switch(DIA_SE_EVT_TYPE(ctxt))
    {
    case AUTH_SESSION_EVT_RX_SSAA_OK:
     {
        DT_DBG(("StatelessClientAuthFsm::Pending --->Received SSAA"));
        DiaUtils::GetCmdFromData(&msg, &evt->data[sizeof(ITS_USHORT)]);
        string sessionId = msg->getSessionId()->value();
        DiaMsgRouter::SendMsgToApp(ctxt, evt);
        Cleanup(ctxt, sessionId);

        break;
    }
    case AUTH_SESSION_EVT_RX_SSAA_FAIL:
    {
        DT_DBG(("StatelessClientAuthFsm::Pending --->Rcvd Failed SSAA"));
        DiaUtils::GetCmdFromData(&msg, &evt->data[sizeof(ITS_USHORT)]);
        string sessionId = msg->getSessionId()->value();
        DiaMsgRouter::SendMsgToApp(ctxt, evt);
        Cleanup(ctxt, sessionId);

        break;
    }
    default:
        DT_ERR(("Invalid Event Type"));

        return (ITS_EBADSTATE);

    }
    return (ret);
}

/****************************************************************************
 *  Purpose:
 *        Process the messages in StatelessClientAuthFsm state
 *
 *  Input Parameters:      
 *        evt : Event to process
 *  
 *  Input/Output Parameters:
 *      vctxt:  Context pointer
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *        ITS_SUCCESS : On successful StatelessClientAuthFsm state process
 *  
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
ITS_INT
StatelessClientAuthFsm_Open::ProcessEvent(void *vctxt, ITS_EVENT *evt)
{
    int ret = FSM_NO_STATE_UPDATE;
    SESSION_ENTRY* ctxt = (SESSION_ENTRY*)vctxt;

    DT_DBG(("StatelessClientAuthFsm::Open --> Evt Type %s", 
             AUTH_SESSION_EVENT_TO_TEXT(DIA_SE_EVT_TYPE(ctxt))));

    switch(DIA_SE_EVT_TYPE(ctxt))
    {
    case AUTH_SESSION_EVT_SESSION_TOUT_ST:
    {
        DT_DBG(("StatelessClientAuthFsm::Open --->Session Timeout"));
        DT_DBG(("Action: Disconnect user / device"));
        char *sessionId = (char *)evt->data; 
        Cleanup(ctxt, sessionId);

        break;
    }
    case AUTH_SESSION_EVT_STOP:
    {
        DT_DBG(("StatelessClientAuthFsm::Open --->Service to user terminated"));
        DT_DBG(("Action: Disconnect user / device"));
        char *sessionId = (char *)evt->data; 
        Cleanup(ctxt, sessionId);

        break;
    }
    default:
        DT_ERR(("Invalid Event Type"));

        return (ITS_EBADSTATE);

    }
    return (ret);
}

