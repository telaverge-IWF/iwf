/*********************************-*HPP*-************************************
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
 * LOG: $Log: dia_timer_handler.cpp,v $
 * LOG: Revision 3.10.72.1.8.1.6.3  2020/02/14 11:36:11  jkchaitanya
 * LOG: TCP Timeout fix ported from DRE
 * LOG:
 * LOG: Revision 3.10.72.1.8.1.6.2  2014/12/17 05:19:08  jkchaitanya
 * LOG: changes to revert back the server down crash changes
 * LOG:
 * LOG: Revision 3.10.72.1.8.1  2014/07/02 06:37:11  millayaraja
 * LOG: updated to handle answer message without mandatory field missing
 * LOG:
 * LOG: Revision 3.10.72.1  2014/01/06 09:22:32  cprem
 * LOG: Changes in diameter stack to support session replication. Review request 1611.
 * LOG:
 * LOG: Revision 3.10  2009/04/14 08:56:22  rajeshak
 * LOG: Remove PeerEntry changed for peers in Open state after TTL Timeout.
 * LOG:
 * LOG: Revision 3.9  2009/04/13 13:36:57  rajeshak
 * LOG: Peer Discovery changes.
 * LOG:
 * LOG: Revision 3.8  2009/02/05 09:55:23  ssaxena
 * LOG: Changes for Redirect Agent code reviews.
 * LOG:
 * LOG: Revision 3.7  2009/02/04 05:51:59  nvijikumar
 * LOG: Changes for 64 Peer support with fixed number of threads
 * LOG: Dedicated thread initiates connections with Peers
 * LOG:
 * LOG: Revision 3.6  2009/02/03 10:21:11  ssaxena
 * LOG: Modifications done for Redirect Agent functionality.
 * LOG:
 * LOG: Revision 3.5  2009/01/03 05:57:44  rajeshak
 * LOG: Introduced common func to send all indications
 * LOG:
 * LOG: Revision 3.4  2008/12/12 12:29:02  nvijikumar
 * LOG: Peg increment is moved to common place
 * LOG:
 * LOG: Revision 3.3  2008/12/12 07:59:41  sureshj
 * LOG: Statistics Support
 * LOG:
 * LOG: Revision 3.2  2008/10/28 12:06:28  nvijikumar
 * LOG: IssueID: none
 * LOG: FeatureID: none
 * LOG: Description: Porting Performance changes from 3.0 branch
 * LOG:
 * LOG: Revision 3.1.2.1  2008/10/07 10:39:01  nvijikumar
 * LOG: Changed the DEBUG traces to WARN traces for timeouts. Made changes in
 * LOG: Auth-Session-Timeout for correct handling of PendingQ.
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:32  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.31  2008/03/27 12:14:08  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.28.4.12  2008/01/10 14:03:45  avinashks
 * LOG: Changes made to provide fix for issue no 28 raised by Dhiranand
 * LOG: during the validation of Bridgewater ticket 1836.
 * LOG:
 * LOG: Revision 2.28.4.11  2008/01/05 16:39:20  avinashks
 * LOG: Changes made to provide fix for issue no.19 raised by Dhiranand during
 * LOG: the validation of bcgi ticket 1807.
 * LOG:
 * LOG: Revision 2.28.4.10  2007/12/27 15:17:43  avinashks
 * LOG: Changes made to fix issue no.2 (testcase No.1)
 * LOG: raised during the validation of bcgi ticket 1807.
 * LOG:
 * LOG: Revision 2.28.4.9  2007/12/14 11:24:48  hbhatnagar
 * LOG: Removed the DeviceWatchDog Timer related functionality and added
 * LOG: WatchDog Transport Thread related functionality.
 * LOG:
 * LOG: Revision 2.28.4.8  2007/11/14 17:14:49  hbhatnagar
 * LOG: Rolling back changes of 2.28.4.7, removed the state change from
 * LOG: DWTimeout() and let the state machine start the Retry Timer.
 * LOG:
 * LOG: Revision 2.28.4.7  2007/10/30 06:54:23  hbhatnagar
 * LOG: Made changes for transport reconnection after disconnection due to Device
 * LOG: Watchdog timeout in HandleDWTimeout().
 * LOG:
 * LOG: Revision 2.28.4.6  2007/09/25 09:46:25  hbhatnagar
 * LOG: Acquire the Mutex for peer entry  in HandleDWtimeout() before the oldtimer
 * LOG: check.
 * LOG:
 * LOG: Revision 2.28.4.5  2007/09/17 09:09:51  hbhatnagar
 * LOG: Added more traces and comments for Bridgewater ticket 1752.
 * LOG:
 * LOG: Revision 2.28.4.4  2007/09/03 15:02:40  hbhatnagar
 * LOG: Fix for Bridgewater Ticket 1752 transport shutdown due to DWTimeout.
 * LOG: Added serialId from ITS_EVENT passed as argument to HandleDWTimeout().
 * LOG:
 * LOG: Revision 2.28.4.3  2007/06/18 15:12:27  nvijikumar
 * LOG: Handle EXPIRY Timer
 * LOG:
 * LOG: Revision 2.28.4.2  2007/03/16 08:10:34  nvijikumar
 * LOG: Fix for Hop-By-Hop Id issue for DWR.
 * LOG:
 * LOG: Revision 2.28.4.1  2007/03/08 14:53:54  nvijikumar
 * LOG: Absent of two DWA after disconnecting the Transport change state to closed.
 * LOG:
 * LOG: Revision 2.28  2007/01/24 16:02:03  tpanda
 * LOG: Fix for Bug # 5151
 * LOG:
 * LOG: Revision 2.27  2007/01/16 07:15:35  nvijikumar
 * LOG: Give Interim timeout indication to App.
 * LOG:
 * LOG: Revision 2.26  2007/01/04 11:15:18  nvijikumar
 * LOG: Correct for Session Id Debug print.
 * LOG:
 * LOG: Revision 2.25  2006/12/29 06:56:18  nanaparthi
 * LOG: SCTP Multihoming related changes (baseline code base)
 * LOG:
 * LOG: Revision 2.24  2006/12/21 15:26:04  tpanda
 * LOG: AddOriginStateId option is added to check if OriginStateId be added to cmd
 * LOG:
 * LOG: Revision 2.23  2006/12/20 14:53:29  tpanda
 * LOG: Device Watch Dog messages should be sent to the same transport
 * LOG: instance, for which the timeout has occured
 * LOG:
 * LOG: Revision 2.22  2006/12/11 13:51:25  tpanda
 * LOG: REDUNDANCY_SLOT_CHANGES are removed and code seems to be stable
 * LOG:
 * LOG: Revision 2.21  2006/12/11 04:52:02  kamakshilk
 * LOG: SessionId appended with null in Indications
 * LOG:
 * LOG: Revision 2.20  2006/12/10 13:42:42  tpanda
 * LOG: Redundancy Bug Fixes and enhancements--Transport Order Fix
 * LOG:
 * LOG: Revision 2.19  2006/12/01 13:51:26  nvijikumar
 * LOG: Fixes for Pending Queue issues.
 * LOG: Set stopFailover flag, incase of Failback.
 * LOG:
 * LOG: Revision 2.18  2006/11/30 18:54:24  tpanda
 * LOG: Redundancy slot changes backed out. TODO: Refer (REDUNDANCY_SLOT_CHANGES) defines
 * LOG: Failover and failback bug fixes
 * LOG:
 * LOG: Revision 2.16  2006/11/25 17:36:42  nvijikumar
 * LOG: Change  peer state to closed state before retransmitting the pending msgs.
 * LOG:
 * LOG: Revision 2.15  2006/11/25 03:57:20  tpanda
 * LOG: Changes for Msg based redundancy
 * LOG:
 * LOG: Revision 2.14  2006/11/24 03:47:32  nvijikumar
 * LOG: Alternate peer lookup from hostname and realm (Failover).
 * LOG:
 * LOG: Revision 2.13  2006/11/22 10:49:37  nvijikumar
 * LOG: Baseline PendingQ ( Failover ) Changes.
 * LOG:
 * LOG: Revision 2.12  2006/11/09 14:31:26  tpanda
 * LOG: clientId handling for IDS at the stack level
 * LOG:
 * LOG: Revision 2.11  2006/10/28 12:33:20  yranade
 * LOG: Update traces.
 * LOG:
 * LOG: Revision 2.10  2006/10/27 09:50:03  yranade
 * LOG: Start GracePeriod timer after Lifetime timeout.
 * LOG:
 * LOG: Revision 2.9  2006/10/27 09:17:05  nvijikumar
 * LOG: Accounting Timeout(Session / Iterim) indications to Application.
 * LOG:
 * LOG: Revision 2.8  2006/10/27 04:41:06  nvijikumar
 * LOG: Updates for Accouting Session Timeout handling.
 * LOG: Updates for Accounting Interim timeout handling.
 * LOG:
 * LOG: Revision 2.7  2006/10/25 12:48:24  yranade
 * LOG: On Retry Timeout, restart connector only when peer is not in OPEN state.
 * LOG:
 * LOG: Revision 2.6  2006/10/24 14:17:00  yranade
 * LOG: Updates to send timeout indications to application.
 * LOG:
 * LOG: Revision 2.5  2006/10/16 06:32:46  yranade
 * LOG: AuthSessionTimer Handling. AuthSM related updates.
 * LOG:
 * LOG: Revision 2.4  2006/10/12 14:13:41  yranade
 * LOG: Finish up Device Watchdog handling. Bug Fix: 4464
 * LOG:
 * LOG: Revision 2.3  2006/10/09 06:27:49  yranade
 * LOG: Timer related updates, still to be finished.
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
 *
 * ID: $Id: dia_timer_handler.cpp,v 3.10.72.1.8.1.6.3 2020/02/14 11:36:11 jkchaitanya Exp $
 ****************************************************************************/
#ident "$Id: dia_timer_handler.cpp,v 3.10.72.1.8.1.6.3 2020/02/14 11:36:11 jkchaitanya Exp $"

#include <its_dia_config.h>
#include <dia_cmn.h>
#include <dia_trace.h>
#include <dia_fsm.h>
#include <dia_utils.h>
#include <dia_connector.h>
#include <dia_session_auth_fsm.h>
#include <dia_session_acct_fsm.h>
#include <dia_timer_handler.h>
#include <dia_session_table.h>
#include <dia_ip_trans.h>
#include <dia_msg_router.h>
#include <dia_cache_table.h>
#include <dia_mgmt.h>
#include <dia_peer_discovery.h>

#if defined (ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
#endif

int 
DiaTimerMsgHandler::HandleMessage(DIAThread *thr, its::Event &ev)
{
    DIA_TIMER_TYPE timerType;
    DIA_TIMER_CTXT ctxt;
    ITS_TimerData *td;
    td = (ITS_TimerData*)ev.GetData();

    //DT_DBG(("HandleTimeout For Timer %d", td->serial));

    memcpy(&ctxt, td->context, sizeof(DIA_TIMER_CTXT));
    timerType = ctxt.timerType;
    ITS_SERIAL serialEvent = td->serial;

    switch (timerType)
    {
    case RETRY:
        HandleRetryTimeout(&ctxt);
        break;
    case EXPIRY:
        HandleExpiryTimeout(&ctxt);
        break;
    case AUTH_SESSION_TIMER:
        HandleAuthSessionTimeout(&ctxt);
        break;
    case AUTH_SESSION_LIFETIME:
        HandleLifeTimeTimeout(&ctxt);
        break;
    case AUTH_SESSION_GRACE_PERIOD:
        HandleGracePeriodTimeout(&ctxt);
        break;
    case AUTH_SESSION_RETRY_ABORT:
        HandleRetryAbortTimeout(&ctxt);
        break;
    case ACCT_SESSION_TIMER:
        HandleAcctSessionTimeout(&ctxt);
        break;
    case ACCT_SESSION_INTERIM_INTERVAL:
        HandleInterimIntervalTimeout(&ctxt);
        break;
    case ACCT_SESSION_REALTIME:
        HandleRealTimeTimeout(&ctxt);
        break;
    case CACHE_TIMER:
        HandleCacheTimeout(&ctxt);
        break;
    case TTL_TIMER:
        HandleTTLTimeout(&ctxt);
        break;
    case RETRMISSION_TIMER:
        HandleRetransmissionTimeout(&ctxt);
	break;
    case SOCK_FLUSH_TIMER:
	HandleFlushTimeout(&ctxt);
	break;
    default:
        break;
    }

    return (ITS_SUCCESS);
}

int
DiaTimerMsgHandler::HandleFlushTimeout(DIA_TIMER_CTXT *ctxt)
{
    int                    ret;
    PEER_ENTRY             *pEntry = ctxt->data.peerInfo.peer;
    DiaPeerSockTransport   *tr = (DiaPeerSockTransport *)DIA_PE_HANDLE(pEntry);
    ITS_BOOLEAN            isPeerToBeDisconnected = ITS_FALSE;

    DT_WRN(("DiaTimerMsgHandler::HandleFlushTimeout"));
    DT_WRN(("TimerType = %s", TIMER_TO_TEXT(ctxt->timerType)));

    if ( (DIA_PE_STATE(pEntry) == PEER_ST_I_OPEN) ||
         (DIA_PE_STATE(pEntry) == PEER_ST_R_OPEN))
    {
        MUTEX_AcquireMutex(tr->getWriteLock());

        ret = tr->FlushData(isPeerToBeDisconnected, ITS_FALSE);

        MUTEX_ReleaseMutex(tr->getWriteLock());

        if (isPeerToBeDisconnected)
        {
            ITS_UINT evtType = PEER_EVT_I_PEER_DISC;

            if (DIA_PE_STATE(pEntry) == PEER_ST_I_OPEN)
            {
                evtType = PEER_EVT_I_PEER_DISC;
            }
            else
            {
                evtType = PEER_EVT_R_PEER_DISC;
            }

            if ( (ret = DiaMsgRouter::UpdatePeerSM(NULL, pEntry,
                            evtType, DIA_PE_HANDLE(pEntry),
                            NULL)) == ITS_SUCCESS)
            {
                DT_DBG(("Succesfully Submitted Message to Peer SM"));
            }
            else
            {
                DT_ERR(("Failed to Handle Message in Peer SM = %d", ret));

                /* Start Retry Timer after the state machine returns failure
                */
                if (DIA_PE_RETRY_TIMER(pEntry) != TIMER_BAD_SERIAL)
                {
                    PeerTable::StopTimer(RETRY, pEntry);
                }

                PeerTable::StartTimer(RETRY, pEntry);
            }
        }
    }
    else
    {
        DT_WRN(("DiaTimerMsgHandler::HandleFlushTimeout Peer is not in OPEN state, ignoring the same."));
    }

    return (ITS_SUCCESS);
}



int 
DiaTimerMsgHandler::HandleRetransmissionTimeout(DIA_TIMER_CTXT *ctxt)
{
    int ret;
    DT_WRN(("DiaTimerMsgHandler::HandleRetransmissionTimeout"));

    PEER_ENTRY *entry = ctxt->data.retransInfo.peer;
    unsigned int hopId = ctxt->data.retransInfo.hopid;

    DIA_BASE_CMD *cmd = DIA_PE_PENDING_Q(entry)->GetEntry(hopId);
    DIA_PE_PENDING_Q(entry)->RemoveEntry(hopId);
    
    return (ITS_SUCCESS);
}


/* TRANSPORT RELATED */
int 
DiaTimerMsgHandler::HandleRetryTimeout(DIA_TIMER_CTXT *ctxt)
{
    int ret;
    DT_WRN(("DiaTimerMsgHandler::HandleRetryTimeout"));
    DT_WRN(("TimerType = %s", TIMER_TO_TEXT(ctxt->timerType)));

    PEER_ENTRY *entry = ctxt->data.peerInfo.peer;

    if (entry &&
        (DIA_PE_STATE(entry) == PEER_ST_I_OPEN ||
         DIA_PE_STATE(entry) == PEER_ST_R_OPEN))
    {
        return ITS_SUCCESS;
    }
    DIA_PE_INIT_CONN(entry) = true;
    return (ITS_SUCCESS);
}

int 
DiaTimerMsgHandler::HandleExpiryTimeout(DIA_TIMER_CTXT *ctxt)
{
    int ret;
    PEER_ENTRY *entry = ctxt->data.peerInfo.peer;

    if (entry &&
        (DIA_PE_STATE(entry) == PEER_ST_I_OPEN ||
         DIA_PE_STATE(entry) == PEER_ST_R_OPEN ||
         DIA_PE_STATE(entry) == PEER_ST_CLOSED))
    {
        /**
         * Fix for issue No. 28 raised by Dhiranand 
         * during validation of bridgewater ticket 1836.
         * Expiry timer for the entry is set to stop 
         * during Expiry timeout.
         */
         
        DIA_PE_EXPIRY_TIMER(entry) = TIMER_BAD_SERIAL;
        return ITS_SUCCESS;
    }

    DT_WRN(("DiaTimerMsgHandler::HandleExpiryTimeout"));
    DT_WRN(("TimerType = %s", TIMER_TO_TEXT(ctxt->timerType)));

    if ((ret = DiaMsgRouter::UpdatePeerSM(NULL, entry,
                                          PEER_EVT_TIMEOUT,
                                          DIA_PE_HANDLE(entry),
                                          NULL)) == ITS_SUCCESS)
    {
        DT_DBG(("Succesfully Submitted Message to Peer SM"));
    }

    /**
     * Fix for issue No. 28 raised by Dhiranand 
     * during validation of bridgewater ticket 1836.
     * Expiry timer for the entry is set to stop 
     * during Expiry timeout.
     */
    DIA_PE_EXPIRY_TIMER(entry) = TIMER_BAD_SERIAL;
    
    return (ITS_SUCCESS);
}

/* SESSION RELATED */
int 
DiaTimerMsgHandler::HandleAuthSessionTimeout(DIA_TIMER_CTXT *ctxt)
{
    int ret;
    DiaSocketTransport *tr = NULL;
    PEER_ENTRY *peer = NULL;
    SESSION_ENTRY *ent = NULL;
    char* sessionId = ctxt->data.sessionInfo.sessionId;
    ITS_EVENT evt;

    DT_WRN(("DiaTimerMsgHandler::HandleAuthSessionTimeout"));
    DT_WRN(("TimerType = %s, SessionId = %s", 
            TIMER_TO_TEXT(ctxt->timerType), sessionId));

    if (SESSION_TABLE->FindEntry(ent,
                                 (ITS_OCTET *)sessionId,
                                 strlen(sessionId)) != ITS_SUCCESS)
    {
        DT_ERR(("Entry Not found "));
        return (!ITS_SUCCESS);
    }

    /* 
     * Remove the entry from PendigQ if exists.
     */
    ITS_USHORT inst = DIA_SE_PEER_INST(ent);

    tr = trTable[inst];
    if (tr)
    {
        peer = tr->GetPeer();

        if (peer != NULL && DIA_PE_PENDING_Q(peer))
        {
            DT_DBG(("DiaTimerMsgHandler::Removing entry from PendingQ"));
            DIA_PE_PENDING_Q(peer)->RemoveEntry(sessionId);
        }
    }

    if (DiaMsgRouter::SendIndication(ent, NULL, sessionId, TIME_OUT_IND_FROM_STACK) 
                                                       != ITS_SUCCESS)
    {
        DT_ERR(("Failed To send Indication to application"));
    }

    /* Act accordingly */
    DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_SESSION_TOUT_ST;
    evt.data = (ITS_OCTET *)sessionId;

    switch(DIA_SE_FSM_TYPE(ent))
    {
    case STATEFUL_CLIENT_AUTH_FSM:
    {
        /* Send STR */
        ret = statefulClientAuthFsm.SubmitToSM(ent, &evt);
        if (ret == FSM_STATE_UPDATE)
        {
            if (SESSION_TABLE->ModifyEntry(ent,
                                           (ITS_OCTET *)sessionId,
                                           strlen(sessionId)) != ITS_SUCCESS)
            {
                DT_ERR(("Failed to Update Entry"));
            }
        } 
        break;
    }
    case STATEFUL_SERVER_AUTH_FSM:
    {
        /* Cleanup */
        ret = statefulServerAuthFsm.SubmitToSM(ent, &evt);
        break;
    }
    default:
        if (SESSION_TABLE->RemoveEntry(ent, (ITS_OCTET *)sessionId,
                                       strlen(sessionId)) == ITS_SUCCESS)
        {
            DT_DBG(("Freed Session Entry"));
        }
        return (ITS_SUCCESS);
    }


    return (ITS_SUCCESS);
}

int
DiaTimerMsgHandler::HandleLifeTimeTimeout(DIA_TIMER_CTXT *ctxt)
{
    const char* sessionId = ctxt->data.sessionInfo.sessionId;
    DT_WRN(("DiaTimerMsgHandler::HandleLifeTimeTimeout"));
    DT_WRN(("TimerType = %s, SessionId = %s", 
            TIMER_TO_TEXT(ctxt->timerType), sessionId));

    SESSION_ENTRY *ent = NULL;

    if (SESSION_TABLE->FindEntry(ent,
                                 (ITS_OCTET *)sessionId,
                                 strlen(sessionId)) != ITS_SUCCESS)
    {
        DT_ERR(("Entry Not found "));
        return (!ITS_SUCCESS);
    }

    if (DiaMsgRouter::SendIndication(ent, NULL, (char*)sessionId, AUTH_LIFE_TIME_OUT_IND_FROM_STACK)
                                                       != ITS_SUCCESS)
    {
        DT_ERR(("Failed To send Indication to application"));
    }

    /* Now start the Grace Period Timer */
    SESSION_TABLE->StartTimer(sessionId,
                              AUTH_SESSION_GRACE_PERIOD,
                              DIA_SE_AUTH_TIMERS(ent).gracePeriod,
                              ent);
    if (SESSION_TABLE->ModifyEntry(ent,
                                   (ITS_OCTET *)sessionId,
                                   strlen(sessionId)) != ITS_SUCCESS)
    {
        DT_ERR(("Failed to Update Entry"));
    }

    return (ITS_SUCCESS);
}

int 
DiaTimerMsgHandler::HandleGracePeriodTimeout(DIA_TIMER_CTXT *ctxt)
{
    char* sessionId = ctxt->data.sessionInfo.sessionId;
    int ret;
    SESSION_ENTRY *ent = NULL;
    DT_WRN(("DiaTimerMsgHandler::HandleGracePeriodTimeout"));
    DT_WRN(("TimerType = %s, SessionId = %s", 
            TIMER_TO_TEXT(ctxt->timerType), sessionId));

    ITS_EVENT evt;

    if (SESSION_TABLE->FindEntry(ent,
                                 (ITS_OCTET *)sessionId,
                                 strlen(sessionId)) != ITS_SUCCESS)
    {
        DT_ERR(("Entry Not found "));
        return (!ITS_SUCCESS);
    }

    if (DiaMsgRouter::SendIndication(ent, NULL, sessionId, AUTH_GRACE_TIME_OUT_IND_FROM_STACK)
                                                       != ITS_SUCCESS)
    {
        DT_ERR(("Failed To send Indication to application"));
    }

    DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_LIFETIME_TOUT;
    evt.data = (ITS_OCTET *)sessionId;

    /* Act According to the appropriate SM */
    switch(DIA_SE_FSM_TYPE(ent))
    {
    case STATEFUL_CLIENT_AUTH_FSM:
    {
        /* Send STR */

        ret = statefulClientAuthFsm.SubmitToSM(ent,
                                               &evt);
        if (ret == FSM_STATE_UPDATE)
        {
            if (SESSION_TABLE->ModifyEntry(ent,
                                           (ITS_OCTET *)sessionId,
                                           strlen(sessionId)) == ITS_SUCCESS)
            {
                DT_ERR(("Updated Entry"));
            }
        }
        break;
    }
    case STATEFUL_SERVER_AUTH_FSM:
    {
        /* Cleanup */
        ret = statefulServerAuthFsm.SubmitToSM(ent,
                                               &evt);
        break;
    }
    default:
        if (SESSION_TABLE->RemoveEntry(ent, (ITS_OCTET *)sessionId,
                                       strlen(sessionId)) == ITS_SUCCESS)
        {
            DT_DBG(("Freed Session Entry"));
        }
    }

    return (ITS_SUCCESS);
}

int 
DiaTimerMsgHandler::HandleRetryAbortTimeout(DIA_TIMER_CTXT *ctxt)
{
    char* sessionId = ctxt->data.sessionInfo.sessionId;
    DT_WRN(("DiaTimerMsgHandler::HandleRetryAbortTimeout"));
    DT_WRN(("TimerType = %s, SessionId = %s", 
            TIMER_TO_TEXT(ctxt->timerType), sessionId));

    return (ITS_SUCCESS);
}

int 
DiaTimerMsgHandler::HandleAcctSessionTimeout(DIA_TIMER_CTXT *ctxt)
{
    int ret;
    SESSION_ENTRY *ent;
    char* sessionId = ctxt->data.sessionInfo.sessionId;
    ITS_EVENT evt;

    DT_WRN(("DiaTimerMsgHandler::HandleAcctSessionTimeout"));
    DT_WRN(("TimerType = %s, SessionId = %s",
            TIMER_TO_TEXT(ctxt->timerType), sessionId));

    if (SESSION_TABLE->FindEntry(ent,
                                 (ITS_OCTET *)sessionId,
                                 strlen(sessionId)) != ITS_SUCCESS)
    {
        DT_ERR(("Entry Not found "));
        return (!ITS_SUCCESS);
    }


    DIA_SE_EVT_TYPE(ent) = ACCT_SESSION_EVT_SESSION_TOUT;
    evt.data = (ITS_OCTET *)sessionId;

    if (DiaMsgRouter::SendIndication(ent, NULL, sessionId, TIME_OUT_IND_FROM_STACK)
                                                       != ITS_SUCCESS)
    {
        DT_ERR(("Failed To send Indication to application"));
    }

    /* Act According to the appropriate SM */
    switch(DIA_SE_ACC_FSM_TYPE(ent))
    {
    case STATEFUL_SERVER_ACCT_FSM:
    {
        /* Stop TS */
        ret = statefulServerAcctFsm.SubmitToSM(ent,
                                               &evt);
        if (ret == FSM_STATE_UPDATE)
        {
            if (SESSION_TABLE->ModifyEntry(ent,
                                           (ITS_OCTET *)sessionId,
                                           strlen(sessionId)) != ITS_SUCCESS)
            {
                DT_ERR(("Updated Entry"));
            }
        }
        break;
    }
    default:
        if (SESSION_TABLE->RemoveEntry(ent, (ITS_OCTET *)sessionId,
                                       strlen(sessionId)) == ITS_SUCCESS)
        {
            DT_DBG(("Freed Session Entry"));
        }
    }

    return (ITS_SUCCESS);
}

int 
DiaTimerMsgHandler::HandleInterimIntervalTimeout(DIA_TIMER_CTXT *ctxt)
{
    int ret;
    SESSION_ENTRY *ent;
    char* sessionId = ctxt->data.sessionInfo.sessionId;
    ITS_EVENT evt;

    DT_WRN(("DiaTimerMsgHandler::HandleInterimIntervalTimeout"));
    DT_WRN(("TimerType = %s, SessionId = %s",
            TIMER_TO_TEXT(ctxt->timerType), sessionId));
    if (SESSION_TABLE->FindEntry(ent,
                                 (ITS_OCTET *)sessionId,
                                 strlen(sessionId)) != ITS_SUCCESS)
    {
        DT_ERR(("Entry Not found "));
        return (!ITS_SUCCESS);
    }


    DIA_SE_EVT_TYPE(ent) = ACCT_SESSION_EVT_INT_EXPIRE;
    evt.data = (ITS_OCTET *)sessionId;

    if (DiaMsgRouter::SendIndication(ent, NULL, sessionId, ACCT_INTERIM_TIME_OUT_IND_FROM_STACK)
                                                       != ITS_SUCCESS)
    {
        DT_ERR(("Failed To send Indication to application"));
    }

    return (ITS_SUCCESS);
}

int 
DiaTimerMsgHandler::HandleRealTimeTimeout(DIA_TIMER_CTXT *ctxt)
{
    char* sessionId = ctxt->data.sessionInfo.sessionId;
    DT_WRN(("DiaTimerMsgHandler::HandleRealTimeTimeout"));
    DT_WRN(("TimerType = %s, SessionId = %d", 
            TIMER_TO_TEXT(ctxt->timerType), sessionId));

    return (ITS_SUCCESS);
}

int 
DiaTimerMsgHandler::HandleCacheTimeout(DIA_TIMER_CTXT *ctxt)
{       
    int ret;
    CACHE_ENTRY *cEntry = NULL;
    const char* key = ctxt->data.cacheInfo.key;
    
    DT_WRN(("DiaTimerMsgHandler::HandleCacheTimeout"));
    DT_WRN(("TimerType = %s, Key = %s",
            TIMER_TO_TEXT(ctxt->timerType), key));
        
    /* Remove this entry from cache table */
    if ( CACHE_TABLE->RemoveEntry( key ) == ITS_SUCCESS )
    {   
        DT_DBG(("Freed Cache Entry"));
        return (ITS_SUCCESS);
    }
    else
    {
        return (!ITS_SUCCESS);
    }
}

int 
DiaTimerMsgHandler:: HandleTTLTimeout(DIA_TIMER_CTXT *ctxt)
{
    int ret = ITS_SUCCESS;
    DiaMgmt *diaMgmt = DiaMgmt::GetDiaMgmt();
    PEER_ENTRY* pEntry =  ctxt->data.peerInfo.peer;
    DIA_PEER_DISC_INFO * peerDiscInfo = NULL;
 
    DT_DBG(("DiaTimerMsgHandler::HandleTTLTimeout")); 
    DT_DBG(("TimerType = %s Peer = %s",
             TIMER_TO_TEXT(ctxt->timerType), DIA_PE_HOST(pEntry)));

    /* Cancel the Peer Retry Timer */
    if ( pEntry && (DIA_PE_TIME_TO_LIVE(pEntry) != TIMER_BAD_SERIAL))
    {
        PeerTable::GetPeerTable()->StopTTLTimer(TTL_TIMER, pEntry);
    }

    REALM_ENTRY *realmEntry = NULL;
 
    if (REALM_TABLE->FindEntry(DIA_PE_REALM(pEntry) ,realmEntry))
    {
        if (RealmTable::RemoveDestination(realmEntry, pEntry) == ITS_SUCCESS)
        {
            DT_DBG(("Removed Destination from Realm Table"));
        }
    }

    if (DIA_PE_STATE(pEntry) != PEER_ST_CLOSED)
    {
        ITS_INT disCause = DisconnectCause::DO_NOT_WANT_TO_TALK_TO_YOU; 
        diaMgmt->DisconnectPeer(DIA_PE_HOST(pEntry),
                              DIA_PE_REALM(pEntry), disCause);
    }

    if (DIA_PE_STATE(pEntry) == PEER_ST_CLOSED)
    {
        if (DiscoveryList::GetDiscoveryList()->FindEntry(DIA_PE_REALM(pEntry), 
                                                     DIA_PE_HOST(pEntry),
                                                     peerDiscInfo))
        {
            peerDiscInfo->peerDiscovered = false;
        }
        ret = diaMgmt->RemovePeer(DIA_PE_HOST(pEntry), DIA_PE_REALM(pEntry)); 
    }
    else
    {
        /* Peer not in closed state. set remove pending flag */
        if (DiscoveryList::GetDiscoveryList()->FindEntry(DIA_PE_REALM(pEntry),
                                               DIA_PE_HOST(pEntry), 
                                               peerDiscInfo))
        {
            peerDiscInfo->removePending = true;
        }
    }

    return ret;
}

