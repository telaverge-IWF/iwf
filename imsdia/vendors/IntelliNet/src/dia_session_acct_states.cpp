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
 * LOG: $Log: dia_session_acct_states.cpp,v $
 * LOG: Revision 3.13.20.6.4.4.2.2  2013/06/05 11:19:11  ncshivakumar
 * LOG: Fix for bug 1571
 * LOG:
 * LOG: Revision 3.13.20.6.4.4.2.1  2013/05/22 06:57:48  ncshivakumar
 * LOG: Fix for bug 1571
 * LOG:
 * LOG: Revision 3.13.20.6.4.4  2013/04/18 07:04:31  jvikram
 * LOG: Included changes relatd to log segregation.
 * LOG:
 * LOG: Revision 3.13.20.6.4.3  2013/04/12 04:18:15  vsarath
 * LOG: Logs improvement
 * LOG:
 * LOG: Revision 3.13.20.6.4.2  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.13.20.6.4.1  2013/02/01 11:34:16  pramana
 * LOG: Merged from branch 0212 to 0300.
 * LOG:
 * LOG: Revision 3.13.20.7  2013/01/22 03:27:53  mallikarjun
 * LOG: Bug 859 changes
 * LOG:
 * LOG: Revision 3.13.20.6  2012/12/03 08:41:20  ncshivakumar
 * LOG: Changes done for adding static routing table
 * LOG:
 * LOG: Revision 3.13.20.5  2012/11/20 17:39:44  pramana
 * LOG: Merged from CMAPI branch for 212-07 release
 * LOG:
 * LOG: Revision 3.13.20.1.16.2  2012/11/20 10:31:24  rgovardhan
 * LOG: merge from 00 Nov20Rel
 * LOG:
 * LOG: Revision 3.13.20.1  2012/09/06 13:04:03  ncshivakumar
 * LOG: fix for bug 113
 * LOG:
 * LOG: Revision 3.13  2009/03/19 12:36:10  nvijikumar
 * LOG: Global instance is created for the Class ITSDiaConfig to avoid function
 * LOG: call overhead as ITSDiaConfig::GetITSDiaConfig() was called max time
 * LOG:
 * LOG: Revision 3.12  2009/03/19 11:29:00  rajeshak
 * LOG: Memory leak fix for error scenario.
 * LOG:
 * LOG: Revision 3.11  2009/01/03 05:54:35  rajeshak
 * LOG: Fixes for memory leak
 * LOG:
 * LOG: Revision 3.10  2008/12/23 12:17:25  sureshj
 * LOG: Removed macro to update Acconting Ansout statistics.
 * LOG: Fix for issue 1379.
 * LOG:
 * LOG: Revision 3.9  2008/12/22 06:27:54  sureshj
 * LOG:  Fix for the whizible issue id 1379. Updating acconting messages
 * LOG:  statistics.
 * LOG:
 * LOG: Revision 3.8  2008/12/12 18:30:47  rajeshak
 * LOG: Lightweight Decode for base AVPS
 * LOG: New Command class is introduced (BaseCommand)
 * LOG:
 * LOG: Revision 3.7  2008/12/07 09:46:12  rajeshak
 * LOG: Added missing code in SendACR to send cmd to peer.
 * LOG:
 * LOG: Revision 3.6  2008/10/31 06:00:27  nvijikumar
 * LOG: IssueID:1189
 * LOG: FeatureID:none
 * LOG: Description: Changes according to Architecture Changes
 * LOG:
 * LOG: Revision 3.5  2008/04/22 13:31:44  avinashks
 * LOG: Fix for Whizible Issue id: 876
 * LOG: Changes done to resolve IDS returning Result-Code value "1" instead of "3002"
 * LOG: when Peer was not active in stateful accounting mode.
 * LOG:
 * LOG: Revision 3.4  2008/04/16 12:11:13  hbhatnagar
 * LOG: Made changes to send ACR Stop with proper destination Realm and
 * LOG: Code cleanup
 * LOG:
 * LOG: Revision 3.3  2008/04/07 17:38:00  hbhatnagar
 * LOG: Made changes for the Hop-by-Hop id and also done error handling.
 * LOG:
 * LOG: Revision 3.2  2008/04/01 16:49:43  hbhatnagar
 * LOG: Changes for Proxy and Relay support 3.0 release - (Hemant)
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:32  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.13  2008/03/27 12:14:08  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.8.4.4  2007/05/25 03:59:06  nvijikumar
 * LOG: Restart Timer after sending the ACR START Answer message.
 * LOG:
 * LOG: Revision 2.8.4.3  2007/05/04 06:18:10  nvijikumar
 * LOG: Fix for PBN Bug Id 5714 issue.
 * LOG: Proper result code for loopback ACR message.
 * LOG:
 * LOG: Revision 2.8.4.2  2007/04/27 06:21:49  nvijikumar
 * LOG: Remove the session if timeout happened in the IDLE state.
 * LOG:
 * LOG: Revision 2.8.4.1  2007/03/30 12:38:43  nvijikumar
 * LOG: Fix for Hop-By-Hop issue on ACA.
 * LOG:
 * LOG: Revision 2.8  2007/01/16 07:17:34  nvijikumar
 * LOG: Fix for PBN Bug Id 5175.
 * LOG:
 * LOG: Revision 2.7  2007/01/04 13:42:46  nvijikumar
 * LOG: Error bypassing the switch statement.
 * LOG:
 * LOG: Revision 2.6  2007/01/04 11:18:50  nvijikumar
 * LOG: Full implementation of Accounting State Machine.
 * LOG:
 * LOG: Revision 2.5  2006/11/29 11:52:14  tpanda
 * LOG: Redundancy related enhancements and fixes for few bugs raised for redundancy
 * LOG:
 * LOG: Revision 2.4  2006/10/27 04:48:27  nvijikumar
 * LOG: Timer handling ( session timer and Interim timer).
 * LOG:
 * LOG: Revision 2.3  2006/10/17 05:45:08  nvijikumar
 * LOG: fix for Compilation on 3.4.2
 * LOG:
 * LOG: Revision 2.2  2006/10/16 16:58:32  nvijikumar
 * LOG: Baseline Accounting Statemachine implementation.
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
#include <dia_session_acct_fsm.h>
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
                                   strlen(sessionId.c_str())) == ITS_SUCCESS)
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
SendACRStop(char *sessionId, ITS_UINT accRecordNum, SESSION_ENTRY *ctxt)
{         
    int ret = ITS_SUCCESS;   
        
    int len = 0;
    DIA_CER *lcer = NULL;
    DiaSocketTransport *tr = NULL;
    PEER_ENTRY *peer = NULL;
    ITS_USHORT inst = 0;

    DT_DBG(("SendACRStop"));
    
    if (ctxt == NULL)
    {
        return (ITS_ESENDFAIL);
    }
    inst = DIA_SE_PEER_INST_AGENT(ctxt);
    tr = trTable[inst];
    if (tr == NULL)
    {
       return (ITS_EBADTRANSPORT);
    }
    peer = tr->GetPeer();

    if (peer == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    lcer = itsDiaConfig.GetLocalCER();

    DIA_ACR *acr = new DIA_ACR(false, false);
    DIA_GEN_CMD *gCmd = (DIA_GEN_CMD *)acr;
    DIA_HDR &hdr = (DIA_HDR &)gCmd->getHeader();

    hdr.hh = DiaUtils::GenerateHopByHopId();
    if (DIA_SE_IS_AGENT(ctxt))
    {
        /**
         * Saving locally generated hop-by-hop id in the context for
         * both the RX and Local.
         */
        DIA_SE_LOCAL_HH(ctxt) = hdr.hh;
        DIA_SE_RX_HH(ctxt) = hdr.hh;
        hdr.ee = DiaUtils::GenerateEndToEndId();
        DIA_SE_RX_EE(ctxt) = hdr.ee;
    }
    else
    {
        DIA_SE_RX_HH(ctxt) = hdr.hh;
    }


    acr->setSessionId(SessionId((char *)sessionId));
    acr->setOriginHost(lcer->getOriginHost());
    acr->setOriginRealm(lcer->getOriginRealm());
    /**
     * Adding the Proper destination realm in the Accounting message
     * from the context.
     */
    acr->setDestinationRealm(DestinationRealm(DIA_SE_DEST_REALM(ctxt)));

    AccountingRecordType accr(AccountingRecordType::STOP_RECORD);
    acr->setAccountingRecordType(accr);

    AccountingRecordNumber arn(accRecordNum);
    acr->setAccountingRecordNumber(arn);

    acr->setAcctApplicationId(AcctApplicationId(DIA_SE_APP_ID(ctxt)));

    //Warning Fix - suggest parentheses around assignment used as truth value
    if ((ret = DiaMsgRouter::SendCmdToPeer(inst,
                                          &hdr, acr)) != ITS_SUCCESS)
    {
        DT_ERR(("Failed to send ACR Stop : ret = %d", ret));
    }
    
     UPDATE_DIA_STATS_REQOUT(DIA_MSG_AC);     
    return ret;
}

static int 
SendACR(SESSION_ENTRY *ctxt, ITS_EVENT *evt, DIA_BASE_CMD *&gCmd)
{
    int ret;
    ITS_USHORT peerInstance;

    DiaUtils::GetCmdFromEvent(&gCmd, evt);
    DIA_BASE_CMD *cmd = (DIA_BASE_CMD *)gCmd;

    /* Try Peer Table Based Routing */
    ret = DiaMsgRouter::RequestForwarding(cmd, ctxt, peerInstance);

    if (ret != ITS_SUCCESS)
    {
        DT_WRN(("No matching Peer found or Peer isn't active"));
        /*  Try Routing using static routing table */
        ret = DiaMsgRouter::StaticRouting(cmd,ctxt,peerInstance,NULL);
    }
    if (ret != ITS_SUCCESS)
    {
        DT_DBG(("Routing using static routing table failed.try realm routing"));
        /* Try Realm Routing */
        //Warning Fix - suggest parentheses around assignment used as truth value
        if ((ret = DiaMsgRouter::RequestRouting(cmd,
                                               ctxt,
                                               peerInstance,
                                               NULL)) != ITS_SUCCESS)
        {
            DT_ERR(("RequestRouting Failed"));
            /**
             * Send Error response as not able to deliver the messge.
             */
            ret = DiaErrHandler::HandleError(DIA_SE_PEER_INST(ctxt), gCmd,
                                             SEND_ERROR_TO_PEER,
                                             ITS_DIA_UNABLE_TO_DELIVER);
            return ITS_DIA_UNABLE_TO_DELIVER;
        }
    }
    else if (ret != ITS_SUCCESS)
    {
        DT_ERR(("Failed to send to Peer ret= %d", ret));
        return (ret);
    }

    /**
     * check for the agents for correct Transport
     */
    if (DIA_SE_IS_AGENT(ctxt))
    {
        DIA_SE_PEER_INST_AGENT(ctxt) = peerInstance;
    }
    else
    {
        DIA_SE_PEER_INST(ctxt) = peerInstance;
    }
   
    UPDATE_DIA_STATS_REQOUT(DIA_MSG_AC);
   
    return (ITS_SUCCESS);
}

static int 
SendACA(SESSION_ENTRY *ctxt, ITS_EVENT *evt)
{
    DIA_BASE_CMD *msg = NULL;
    DiaUtils::GetCmdFromEvent(&msg, evt);
    DIA_BASE_CMD *cmd = (DIA_BASE_CMD *)msg;

    DIA_HDR &hdr = (DIA_HDR &)msg->getHeader();
    hdr.flags.p = (DIA_SE_RX_FLAGS(ctxt)).p;
    hdr.flags.t = (DIA_SE_RX_FLAGS(ctxt)).t;
    hdr.hh = DIA_SE_RX_HH(ctxt);
    hdr.ee = DIA_SE_RX_EE(ctxt);

    if (DiaMsgRouter::SendCmdToPeer(DIA_SE_PEER_INST(ctxt), &hdr,
                                             cmd) != ITS_SUCCESS)
    {
        return (ITS_ESENDFAIL);
    }
    return (ITS_SUCCESS);
}

static int
StartAcctSessionTimer(SESSION_ENTRY *ctxt, DIA_BASE_CMD *msg)
{

    if (DIA_SE_STYPE(ctxt) != DIA_ACCOUNTING)
    {
        return (ITS_SUCCESS);
    }

    ITS_UINT st = 0;
    string sessionId = msg->getSessionId()->value();

    if (msg->getSessionTimeout())
    {
        DT_DBG(("Start Session Timer"));
        st = msg->getSessionTimeout()->value();
    }
    else
    {
        st = itsDiaConfig.GetAcctSessionConfig().GetTimeout();
    }

    SESSION_TABLE->StartTimer(sessionId.c_str(),
                              ACCT_SESSION_TIMER,
                              st,
                              ctxt);
    return (ITS_SUCCESS);
}

static int
StartAcctIntTimer(SESSION_ENTRY *ctxt, DIA_BASE_CMD *msg)
{
    ITS_UINT interTime = 0;
    string sessionId = msg->getSessionId()->value();

    if (msg->getAcctInterimInterval())
    {
        interTime = msg->getAcctInterimInterval()->value();
    }
    else
    {
        interTime = itsDiaConfig.GetAcctSessionConfig().GetInterimIntvl();
    }

    SESSION_TABLE->StartTimer(sessionId.c_str(),
                                  ACCT_SESSION_INTERIM_INTERVAL,
                                  interTime,
                                  ctxt);
    return (ITS_SUCCESS);
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

    //Warning Fix - control reaches end of non-void function
    return (!ITS_SUCCESS);
}

static int
InsertEntry(DIA_BASE_CMD *&gCmd, SESSION_ENTRY *&sessInfo)
{
    std::string sessionId;
    if (gCmd->getSessionId())
    {
        sessionId = gCmd->getSessionId()->value();

        if (DIA_SE_STYPE(sessInfo) == DIA_ACCOUNTING)
        {
            SESSION_TABLE->StartTimer(sessionId.c_str(),
                                  ACCT_SESSION_TIMER,
                              itsDiaConfig.GetAcctSessionConfig().GetTimeout(),
                                      sessInfo);
        
            if (SESSION_TABLE->InsertEntry(*sessInfo,
                                      (ITS_OCTET *)sessionId.c_str(),
                                    strlen(sessionId.c_str())) == ITS_SUCCESS)              
            {
                DT_DBG(("Created Session Context for %s", sessionId.c_str()));
                return (ITS_SUCCESS);
            }
            else
            {
                DT_ERR(("Failed to create Session Context for %s",
                        sessionId.c_str()));

                SESSION_TABLE->StopTimer(AUTH_SESSION_TIMER, sessInfo);
    
                return (ITS_DIA_UNABLE_TO_DELIVER);
            }
       }
       else
       {
           return ModifyEntry(gCmd,sessInfo);
       }
    }

    return (!ITS_SUCCESS);
}

/****************************************************************************
 *  Purpose:
 *        Process the messages in StatefulServerAcctFsm state
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
 *        ITS_SUCCESS : On successful StatefulServerAcctFsm state process
 *  
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
ITS_INT 
StatefulServerAcctFsm_Idle::ProcessEvent(void *vctxt, ITS_EVENT *evt)
{   
    int ret = FSM_NO_STATE_UPDATE;
    DIA_BASE_CMD *msg = NULL;
    SESSION_ENTRY* ctxt = (SESSION_ENTRY*)vctxt; 
    ITS_BOOLEAN isStopReq = ITS_FALSE;
    std::string sessionId;


 
    DT_DBG(("StatefulServerAcctFsm::Idle --> Evt Type %s",
             ACCT_SESSION_EVENT_TO_TEXT(DIA_SE_EVT_TYPE(ctxt))));

    switch(DIA_SE_EVT_TYPE(ctxt))
    {
    case ACCT_SESSION_EVT_REQUEST_ACCESS:
        DiaUtils::GetCmdFromData(&msg, &evt->data[sizeof(ITS_USHORT)]);

        SESSION_TABLE->StopAllAcctTimers(ctxt);
        /* Start Session Timer */
        StartAcctSessionTimer(ctxt, msg);

        DiaMsgRouter::SendMsgToApp(ctxt, evt);

        break;
    case ACCT_SESSION_EVT_RX_ACR_START_OK:
    {
        DT_DBG(("Action: Send Accounting start answer : Start Ts"));
        DiaUtils::GetCmdFromEvent(&msg, evt);
        DIA_BASE_CMD *cmd = (DIA_BASE_CMD*)msg;
        DIA_HDR &hdr = (DIA_HDR &)msg->getHeader();
        sessionId = msg->getSessionId()->value();

        /* Restart Session Timer */
        SESSION_TABLE->StopAllAcctTimers(ctxt);
        StartAcctSessionTimer(ctxt, msg);

        /* Validate the ResultCode for Agents */
        if (DIA_SE_IS_AGENT(ctxt) &&
            (DiaUtils::IsResultCodeModified(msg, ctxt)) == ITS_TRUE)
        {
            //Fix for coverity CID11716.Fetch accRecNum before SendCmdToPeer
            //as msg will be freed in that method
            DIA_ACA *aca = (DIA_ACA *)msg;
            ITS_UINT accRecNum = aca->getAccountingRecordNumber().value();
            //End for coverity CID11716 
            //Warning Fix - suggest parentheses around assignment used as truth value
            if ((ret = DiaMsgRouter::SendCmdToPeer(DIA_SE_PEER_INST(ctxt),
                                                  &hdr,
                                                  cmd)) != ITS_SUCCESS)
            {
               DT_ERR(("Failed to send to Peer ret= %d", ret));
            }
                        
            DT_DBG(("Result Code Modified, Sending ACR Stop to Peer"));
            SendACRStop((char*)sessionId.c_str(),(++accRecNum),ctxt);
            DIA_SE_MSG_STATUS(ctxt) = WAIT_ANS_FROM_PEER;

            ret = FSM_STATE_UPDATE;
            return ret;
        }


        SendACA(ctxt, evt);

        DIA_SE_ACC_STATE(ctxt) = ACCT_SESSION_ST_OPEN;
        ret = FSM_STATE_UPDATE;

        break;
    } 
    case ACCT_SESSION_EVT_RX_ACR_EV_OK:
        DT_DBG(("Action: Send Accounting event answer "));
        SendACA(ctxt, evt);
        if (DIA_SE_STYPE(ctxt) == DIA_ACCOUNTING)
        {
            DiaUtils::GetCmdFromEvent(&msg, evt);
            string sessionId = msg->getSessionId()->value();
            Cleanup(ctxt, sessionId);
        }

        break;
    case ACCT_SESSION_EVT_RX_ACR_NO_BUF:
    case ACCT_SESSION_EVT_RX_ACR_FAIL:
    {
        DiaUtils::GetCmdFromEvent(&msg, evt);
        DIA_HDR &hdr = (DIA_HDR &)msg->getHeader();
        DIA_BASE_CMD* cmd = (DIA_BASE_CMD*)msg;
        sessionId = msg->getSessionId()->value();


        /* Validate the ResultCode for Agents */
        if (DIA_SE_IS_AGENT(ctxt) &&
            (DiaUtils::IsResultCodeModified(msg, ctxt)) == ITS_TRUE)
        {
            //Warning Fix - suggest parentheses around assignment used as truth value
            if ((ret = DiaMsgRouter::SendCmdToPeer(DIA_SE_PEER_INST(ctxt),
                                                  &hdr,
                                                  cmd)) != ITS_SUCCESS)
            {
               DT_ERR(("Failed to send to Peer ret= %d", ret));
            }

            DIA_ACA *aca = (DIA_ACA *)msg; 
            ITS_UINT accRecNum = aca->getAccountingRecordNumber().value();
                        
            DT_DBG(("Result Code Modified, Sending ACR Stop to Peer"));
            SendACRStop((char*)sessionId.c_str(),(++accRecNum),ctxt);
            DIA_SE_MSG_STATUS(ctxt) = WAIT_ANS_FROM_PEER;

            ret = FSM_STATE_UPDATE;
            return ret;
        }

        SendACA(ctxt, evt);
        if (DIA_SE_STYPE(ctxt) == DIA_ACCOUNTING)
        {
            DiaUtils::GetCmdFromEvent(&msg, evt);
            string sessionId = msg->getSessionId()->value(); 
            Cleanup(ctxt, sessionId);
        }

        break;
    }
    case ACCT_SESSION_EVT_SESSION_TOUT: // Un-Official customization.
    {
        DT_DBG(("Action: Stop Ts Clean up"));

        /* SESSION_TABLE->StopAllAcctTimers(ctxt); */
        /* Timers stoped inside the Cleanup */
        char *sessionId = (char *)evt->data;
        Cleanup(ctxt, sessionId);

        break;
    }
 
    /**
     * Case added for the downstream agent accounting request
     */  
    case ACCT_SESSION_EVT_ACCESS_TX_AGENT:
    {
        DIA_BASE_CMD *gCmd = NULL; 
        ITS_USHORT peerInstance = UNKNOWN_PEER_INST;
         
        DT_DBG(("Action: Send Accounting request on Agent session")); 

     

        if (evt->len == sizeof(DiaMsgToPeerEvt))
        {
            peerInstance = ((DiaMsgToPeerEvt*)(evt->data))->toPeer;
        }

        if (peerInstance != UNKNOWN_PEER_INST)
        {
            DiaUtils::GetCmdFromEvent(&msg, evt);
            gCmd = (DIA_BASE_CMD *)msg;
            DT_DBG(("Application routing. Peer = %d", peerInstance));
            DIA_HDR &hdr = (DIA_HDR&)gCmd->getHeader();
            hdr.hh = DiaUtils::GenerateHopByHopId();
            DiaUtils::AddRouteRecordAvp(gCmd, ctxt);
            DIA_SE_LOCAL_HH(ctxt) = hdr.hh;
            ret = ITS_SUCCESS;
        }
        else if ((ret = SendACR(ctxt, evt, gCmd)) == ITS_SUCCESS)
        {

            if (!DIA_SE_IS_AGENT(ctxt))
            {
                peerInstance = DIA_SE_PEER_INST(ctxt);
            }
            else
            {
                peerInstance = DIA_SE_PEER_INST_AGENT(ctxt);
            }
#if 0
            if ((ret = InsertEntry(gCmd, ctxt)) == ITS_SUCCESS)
            {
                DIA_HDR &hdr = (DIA_HDR&)gCmd->getHeader();
                ret = DiaMsgRouter::SendCmdToPeer(peerInstance,
                                                 &hdr,
                                                 gCmd);
            }
#endif
//fix for 113, to avoid the duplication of same session entry

        }
        if(ret == ITS_SUCCESS)
        {
	        DIA_HDR &hdr = (DIA_HDR&)gCmd->getHeader();
            DIA_SE_PEER_INST_AGENT(ctxt) = peerInstance;
            if(msg == NULL)
            {
                DiaUtils::GetCmdFromEvent(&msg, evt);
            }
            if ((ModifyEntry(msg, ctxt) != ITS_SUCCESS))
            {
                DT_ERR(("Failed to update"));
            }
            ret = DiaMsgRouter::SendCmdToPeer(peerInstance,
                                              &hdr,
                                              gCmd);
        }
        else
        {
            DT_WRN((" Not able to send the request")); 
        }
        break;
    }

    /**
     * Case added for the upstream agent accounting answer
     */  
    case ACCT_SESSION_EVT_ACCESS_RX_AGENT:
    {
        DT_DBG(("Action: Send Message to Application")); 
        DiaMsgRouter::SendMsgToApp(ctxt, evt);
        break;
    }

    /**
     * Case Added for the ACA recived or the ACRStop  
     * sent by Proxy.
     */
    case ACCT_SESSION_EVT_RX_ACA_OK:
    case ACCT_SESSION_EVT_RX_ACA_FAIL:
    {
        DT_DBG(("Action: Send Message to Application")); 
        DiaMsgRouter::SendMsgToApp(ctxt, evt);
        DiaUtils::GetCmdFromData(&msg, &evt->data[sizeof(ITS_USHORT)]);
        sessionId = msg->getSessionId()->value();
        Cleanup(ctxt, sessionId);
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
StatefulServerAcctFsm_Open::ProcessEvent(void *vctxt, ITS_EVENT *evt)
{
    int ret = FSM_NO_STATE_UPDATE;
    DIA_BASE_CMD *msg = NULL;
    SESSION_ENTRY* ctxt = (SESSION_ENTRY*)vctxt; 
    ITS_BOOLEAN isStopReq = ITS_FALSE;
    std::string sessionId;

    DT_DBG(("StatefulServerAcctFsm::Open --> Evt Type %s",
             ACCT_SESSION_EVENT_TO_TEXT(DIA_SE_EVT_TYPE(ctxt))));

    switch(DIA_SE_EVT_TYPE(ctxt))
    {
    case ACCT_SESSION_EVT_REQUEST_ACCESS:
        DiaMsgRouter::SendMsgToApp(ctxt, evt);

        break;
    case ACCT_SESSION_EVT_RX_ACR_INT_OK: 
    {
        DT_DBG(("Action: Send Interim answer : Restarts Ts"));
        DiaUtils::GetCmdFromEvent(&msg, evt);
        DIA_HDR &hdr = (DIA_HDR &)msg->getHeader();
        DIA_BASE_CMD *cmd = (DIA_BASE_CMD*)msg;
        sessionId = msg->getSessionId()->value();

        /* Validate the ResultCode for Agents */
        if (DIA_SE_IS_AGENT(ctxt) &&
            (DiaUtils::IsResultCodeModified(msg, ctxt)) == ITS_TRUE)
        {
            //Fix for coverity CID11716.Fetch accRecNum before SendCmdToPeer
            //as msg will be freed in that method
            DIA_ACA *aca = (DIA_ACA *)msg;
            ITS_UINT accRecNum = aca->getAccountingRecordNumber().value();
            //End for coverity CID11716 

            //Warning Fix - suggest parentheses around assignment used as truth value
            if ((ret = DiaMsgRouter::SendCmdToPeer(DIA_SE_PEER_INST(ctxt),
                                                  &hdr,
                                                  cmd)) != ITS_SUCCESS)
            {
               DT_ERR(("Failed to send to Peer ret= %d", ret));
            }

                        
            DT_DBG(("Result Code Modified, Sending ACR Stop to Peer"));
            SendACRStop((char*)sessionId.c_str(),(++accRecNum),ctxt);
            DIA_SE_MSG_STATUS(ctxt) = WAIT_ANS_FROM_PEER;

            ret = FSM_STATE_UPDATE;
            return ret;
        }

        /* Restart Session Timer */
        SESSION_TABLE->StopAllAcctTimers(ctxt);
        StartAcctSessionTimer(ctxt, msg);

        SendACA(ctxt, evt);

        break;
    }
    case ACCT_SESSION_EVT_RX_ACR_STOP_OK: 
        DT_DBG(("Action: Send Acct Stop answer : Stop Ts"));
        DiaUtils::GetCmdFromEvent(&msg, evt);

        SendACA(ctxt, evt);
        
        /* SESSION_TABLE->StopAllAcctTimers(ctxt); */
        /* Timers stoped inside the Cleanup */
        if (DIA_SE_STYPE(ctxt) == DIA_ACCOUNTING)
        {
            string sessionId = msg->getSessionId()->value();
            Cleanup(ctxt, sessionId);
        }
        else
        {
            DIA_SE_ACC_STATE(ctxt) = ACCT_SESSION_ST_IDLE;
            ret = FSM_STATE_UPDATE;
        }

        break;
    case ACCT_SESSION_EVT_RX_ACR_NO_BUF: 
    case ACCT_SESSION_EVT_RX_ACR_FAIL:
    {
        DiaUtils::GetCmdFromEvent(&msg, evt);
        DIA_HDR &hdr = (DIA_HDR &)msg->getHeader();
        DIA_BASE_CMD *cmd = (DIA_BASE_CMD*)msg;
        sessionId = msg->getSessionId()->value();

        /* Validate the ResultCode for Agents */
        if (DIA_SE_IS_AGENT(ctxt) &&
            (DiaUtils::IsResultCodeModified(msg, ctxt)) == ITS_TRUE)
        {
            //Warning Fix - suggest parentheses around assignment used as truth value
            if ((ret = DiaMsgRouter::SendCmdToPeer(DIA_SE_PEER_INST(ctxt),
                                                  &hdr,
                                                  cmd)) != ITS_SUCCESS)
            {
               DT_ERR(("Failed to send to Peer ret= %d", ret));
            }

            DIA_ACA *aca = (DIA_ACA *)msg; 
            ITS_UINT accRecNum = aca->getAccountingRecordNumber().value();
                        
            DT_DBG(("Result Code Modified, Sending ACR Stop to Peer"));
            SendACRStop((char*)sessionId.c_str(),(++accRecNum),ctxt);
            DIA_SE_MSG_STATUS(ctxt) = WAIT_ANS_FROM_PEER;

            ret = FSM_STATE_UPDATE;
            return ret;
        }

        SendACA(ctxt, evt);

        /* SESSION_TABLE->StopAllAcctTimers(ctxt); */
        /* Timers stoped inside the Cleanup */
        if (DIA_SE_STYPE(ctxt) == DIA_ACCOUNTING)
        {
            string sessionId = msg->getSessionId()->value();
            Cleanup(ctxt, sessionId);
        }
        else
        {
            DIA_SE_ACC_STATE(ctxt) = ACCT_SESSION_ST_IDLE;
            ret = FSM_STATE_UPDATE;
        }

        break;
    }
    case ACCT_SESSION_EVT_SESSION_TOUT: 
    {
        DT_DBG(("Action: Stop Ts"));

        /* SESSION_TABLE->StopAllAcctTimers(ctxt); */
        /* Timers stoped inside the Cleanup */
        char *sessionId = (char *)evt->data;
        Cleanup(ctxt, sessionId);

        break;
    }
 
    /**
     * Case added for the downstream agent accounting request
     */
    case ACCT_SESSION_EVT_ACCESS_TX_AGENT:
    {
        DT_DBG(("Sending Accounting request on Agent Session to Peer"));
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

        /* Setting or Overiding destination host
         * On an existing session both peers are known
         * hence destination host are automatically set by stack
         * if wrong value is set by application
         */
        ITSDiaConfig* cfg = &itsDiaConfig;
        ITS_NODE_STATE state;

        if (gCmd->getDestinationHost() &&
            (!cfg->IsMsgRedundancyEnabled() ||
             ((ITS_GetNodeState(&state) == ITS_SUCCESS) &&
             state == ITS_STATE_PRIMARY)))
        {
            PEER_ENTRY* peer = NULL;
            DiaSocketTransport* tr = NULL;

            DT_DBG(("Setting/Overiding destination host and realm  "));
            tr = trTable[DIA_SE_PEER_INST(ctxt)];
            if (tr == NULL)
            {
                DT_ERR(("Invalid Transport"));
                return (!ITS_SUCCESS);
            }
            else
            {
                peer = tr->GetPeer();
                if (peer == NULL)
                {
                    DT_ERR(("Peer not found for transport"));
                    return (!ITS_SUCCESS);
                }
            }
            /* set correct destHost or destRealm properly*/
            DestinationHost dHost(DIA_PE_HOST(peer));
            DestinationRealm dRealm(DIA_PE_REALM(peer));
            
            String dhBuff, rhBuff;
            dHost.Encode(dhBuff);
            dRealm.Encode(rhBuff);

            gCmd->addAvpBuf(dhBuff.c_str(), strlen(dhBuff.c_str()));
            gCmd->addAvpBuf(rhBuff.c_str(), strlen(rhBuff.c_str()));
            /* Make sure these deletes are removed if we move to original 
               STL string */
            dhBuff.Free();
            rhBuff.Free(); 
        }

        //Warning Fix - suggest parentheses around assignment used as truth value
        if ((ret = DiaMsgRouter::SendCmdToPeer(DIA_SE_PEER_INST_AGENT(ctxt),
                                              &hdr, cmd)) != ITS_SUCCESS)
        {
            DT_ERR(("Failed to send Cmd : ret = %d", ret));
        }
        break;
    } 

    /**
     * Case added for the upstream agent accounting answer
     */
    case ACCT_SESSION_EVT_ACCESS_RX_AGENT:
    {
        DT_DBG(("Action: Send Message to Application"));
        DiaMsgRouter::SendMsgToApp(ctxt, evt);
        break;
    }

    /**
     * Case Added for the ACA recived or the ACRStop               
     * sent by Proxy.
     */
    case ACCT_SESSION_EVT_RX_ACA_OK:
    case ACCT_SESSION_EVT_RX_ACA_FAIL:
    {
        DT_DBG(("Action: Send Message to Application"));
        DiaMsgRouter::SendMsgToApp(ctxt, evt);
        DiaUtils::GetCmdFromData(&msg, &evt->data[sizeof(ITS_USHORT)]);
        sessionId = msg->getSessionId()->value();
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
 *        Process the messages in ClientAcctFsm state
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
 *        ITS_SUCCESS : On successful ClientAcctFsm state process
 *  
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
ITS_INT 
ClientAcctFsm_Idle::ProcessEvent(void *vctxt, ITS_EVENT *evt)
{  
    int ret = FSM_NO_STATE_UPDATE;
    DIA_BASE_CMD *msg = NULL;
    SESSION_ENTRY* ctxt = (SESSION_ENTRY*)vctxt; 
 
    DT_DBG(("ClientAcctFsm::Idle --> Evt Type %s",
             ACCT_SESSION_EVENT_TO_TEXT(DIA_SE_EVT_TYPE(ctxt))));

    switch(DIA_SE_EVT_TYPE(ctxt))
    {
    case ACCT_SESSION_EVT_REQUEST_ACCESS:
    {
        DIA_BASE_CMD *gCmd = NULL;
        DT_DBG(("Action: Send Accounting Start req"));
        
        if ((ret = SendACR(ctxt, evt, gCmd)) == ITS_SUCCESS)
        {
            DIA_SE_ACC_STATE(ctxt) = ACCT_SESSION_ST_PENDING_S;
            ret = FSM_STATE_UPDATE;
            ITS_USHORT peerInstance = 0;

            if (!DIA_SE_IS_AGENT(ctxt))
            {
                peerInstance = DIA_SE_PEER_INST(ctxt);
            }
            else
            {
                peerInstance = DIA_SE_PEER_INST_AGENT(ctxt);
            }

            if ((ret = InsertEntry(gCmd, ctxt)) == ITS_SUCCESS)
            {
                DIA_HDR &hdr = (DIA_HDR&)gCmd->getHeader();
                ret = DiaMsgRouter::SendCmdToPeer(peerInstance,
                                                 &hdr,
                                                 gCmd);
            }

        }
        else
        {
            DiaUtils::GetCmdFromEvent(&msg, evt);
            DT_ERR(("Failed To Send ACR Start Request"));
            //DIA_ACR *acr = (DIA_ACR *)msg;
            DIA_BASE_CMD *acr = (DIA_BASE_CMD *)msg;
            ITS_UINT realtime = 0;

            if (msg && msg->countAccountingRealtimeRequired())
            {
                realtime = msg->getAccountingRealtimeRequired()->value();
            }
            if (acr->IsStorageSpaceAvailable() &&
                (realtime != AccountingRealtimeRequired::DELIVER_AND_GRANT))
            {   
                DT_DBG(("Action: Store Accounting Start Record"));
                DiaErrHandler::HandleError(0, msg,
                                             LOOP_TO_APP,
                                             ITS_DIA_UNABLE_TO_DELIVER);

                StartAcctIntTimer(ctxt, msg);
                DIA_SE_ACC_STATE(ctxt) = ACCT_SESSION_ST_OPEN;
                ret = FSM_STATE_UPDATE;
            }
            else if (realtime == AccountingRealtimeRequired::GRANT_AND_LOSE)
            {
                DiaErrHandler::HandleError(0, msg,
                                             LOOP_TO_APP,
                                             ITS_DIA_UNABLE_TO_DELIVER);

                StartAcctIntTimer(ctxt, msg);
                DIA_SE_ACC_STATE(ctxt) = ACCT_SESSION_ST_OPEN;
                ret = FSM_STATE_UPDATE;
            }
        }

        break;
    }
    case ACCT_SESSION_EVT_REQUEST_ONETIME_ACCESS:
    {
        DIA_BASE_CMD *gCmd = NULL;
        DT_DBG(("Action: Send Accounting Event req"));

        if ((ret = SendACR(ctxt, evt, gCmd)) == ITS_SUCCESS)
        {
            DIA_SE_ACC_STATE(ctxt) = ACCT_SESSION_ST_PENDING_E;
            ret = FSM_STATE_UPDATE;
            ITS_USHORT peerInstance = 0;

            if (!DIA_SE_IS_AGENT(ctxt))
            {
                peerInstance = DIA_SE_PEER_INST(ctxt);
            }
            else
            {
                peerInstance = DIA_SE_PEER_INST_AGENT(ctxt);
            }

            if ((ret = InsertEntry(gCmd, ctxt)) == ITS_SUCCESS)
            {
                DIA_HDR &hdr = (DIA_HDR&)gCmd->getHeader();
                ret = DiaMsgRouter::SendCmdToPeer(peerInstance,
                                                 &hdr,
                                                 gCmd);
            }

        }

        break;
    }
    case ACCT_SESSION_EVT_REC_IN_STORAGE:
    {
        DIA_BASE_CMD *gCmd = NULL;
        DT_DBG(("Action: Send Record"));

        if ((ret = SendACR(ctxt, evt, gCmd)) == ITS_SUCCESS)
        {
            DIA_SE_ACC_STATE(ctxt) = ACCT_SESSION_ST_PENDING_B;
            ret = FSM_STATE_UPDATE;
            ITS_USHORT peerInstance = 0;

            if (!DIA_SE_IS_AGENT(ctxt))
            {
                peerInstance = DIA_SE_PEER_INST(ctxt);
            }
            else
            {
                peerInstance = DIA_SE_PEER_INST_AGENT(ctxt);
            }

            if ((ret = InsertEntry(gCmd, ctxt)) == ITS_SUCCESS)
            {
                DIA_HDR &hdr = (DIA_HDR&)gCmd->getHeader();
                ret = DiaMsgRouter::SendCmdToPeer(peerInstance,
                                                 &hdr,
                                                 gCmd);
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
 *        Process the messages in ClientAcctFsm state
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
 *        ITS_SUCCESS : On successful ClientAcctFsm state process
 *
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
ITS_INT
ClientAcctFsm_Open::ProcessEvent(void *vctxt, ITS_EVENT *evt)
{
    int ret = FSM_NO_STATE_UPDATE;
    DIA_BASE_CMD *msg = NULL;
    SESSION_ENTRY* ctxt = (SESSION_ENTRY*)vctxt;

    DT_DBG(("ClientAcctFsm::Open --> Evt Type %s",
           ACCT_SESSION_EVENT_TO_TEXT(DIA_SE_EVT_TYPE(ctxt))));

    switch(DIA_SE_EVT_TYPE(ctxt))
    {
    case ACCT_SESSION_EVT_INT_EXPIRE:
    {
        DIA_BASE_CMD *gCmd = NULL;
        // Evt: Interim interval elapses
        DT_DBG(("Action: Sending Accounting Interim record"));
        if ((ret = SendACR(ctxt,evt, gCmd)) == ITS_SUCCESS)
        {
            DIA_SE_ACC_STATE(ctxt) = ACCT_SESSION_ST_PENDING_I;
            ret = FSM_STATE_UPDATE;
            ITS_USHORT peerInstance = 0;

            if (!DIA_SE_IS_AGENT(ctxt))
            {
                peerInstance = DIA_SE_PEER_INST(ctxt);
            }
            else
            {
                peerInstance = DIA_SE_PEER_INST_AGENT(ctxt);
            }

            if ((ret = ModifyEntry(gCmd, ctxt)) == ITS_SUCCESS)
            {
                DIA_HDR &hdr = (DIA_HDR&)gCmd->getHeader();
                ret = DiaMsgRouter::SendCmdToPeer(peerInstance,
                                                 &hdr,
                                                 gCmd);
            }

        }
        else
        {
            DiaUtils::GetCmdFromEvent(&msg, evt);
            DT_ERR(("Failed To Send ACR Interim Request"));
            DIA_BASE_CMD *acr = (DIA_BASE_CMD *)msg;

            ITS_UINT realtime = 0;

            if (msg && msg->countAccountingRealtimeRequired())
            {
                realtime = msg->getAccountingRealtimeRequired()->value();
            }
            if (acr->IsStorageSpaceAvailable() &&
                (realtime != AccountingRealtimeRequired::DELIVER_AND_GRANT))
            {
                DT_DBG(("Action: Store Accounting Start Record"));
                DiaErrHandler::HandleError(0, msg,
                                             LOOP_TO_APP,
                                             ITS_DIA_UNABLE_TO_DELIVER);

                /* Restart All timers */
                SESSION_TABLE->StopAllAcctTimers(ctxt);
                StartAcctSessionTimer(ctxt, msg);
                StartAcctIntTimer(ctxt, msg);

                DIA_SE_ACC_STATE(ctxt) = ACCT_SESSION_ST_OPEN;
                ret = FSM_STATE_UPDATE;
            }
            else if (realtime == AccountingRealtimeRequired::GRANT_AND_LOSE)
            {
                DiaErrHandler::HandleError(0, msg,
                                             LOOP_TO_APP,
                                             ITS_DIA_UNABLE_TO_DELIVER);

                /* Restart All timers */
                SESSION_TABLE->StopAllAcctTimers(ctxt);
                StartAcctSessionTimer(ctxt, msg);
                StartAcctIntTimer(ctxt, msg);

                DIA_SE_ACC_STATE(ctxt) = ACCT_SESSION_ST_OPEN;
                ret = FSM_STATE_UPDATE;
            }
            else
            {
                if (DIA_SE_STYPE(ctxt) == DIA_ACCOUNTING)
                {
                    string sessionId = msg->getSessionId()->value(); 
                    Cleanup(ctxt, sessionId);
                }
                else
                {
                    DiaErrHandler::HandleError(0, msg,
                                             LOOP_TO_APP,
                                             ITS_DIA_UNABLE_TO_DELIVER);
                    DIA_SE_ACC_STATE(ctxt) = ACCT_SESSION_ST_IDLE;
                    ret = FSM_STATE_UPDATE;
                }
            }
        }

        break;
    }
    case ACCT_SESSION_EVT_STOP:
    {
        DIA_BASE_CMD *gCmd = NULL;
        // Evt: User service terminated
        DT_DBG(("Action: Sending Accounting stop record"));
        if ((ret = SendACR(ctxt,evt, gCmd)) == ITS_SUCCESS)
        {
            DIA_SE_ACC_STATE(ctxt) = ACCT_SESSION_ST_PENDING_L;
            ret = FSM_STATE_UPDATE;
            ITS_USHORT peerInstance = 0;

            if (!DIA_SE_IS_AGENT(ctxt))
            {
                peerInstance = DIA_SE_PEER_INST(ctxt);
            }
            else
            {
                peerInstance = DIA_SE_PEER_INST_AGENT(ctxt);
            }

            if ((ret = ModifyEntry(gCmd, ctxt)) == ITS_SUCCESS)
            {
                DIA_HDR &hdr = (DIA_HDR&)gCmd->getHeader();
                ret = DiaMsgRouter::SendCmdToPeer(peerInstance,
                                                 &hdr,
                                                 gCmd);
            }

        }
        else
        {   
            DiaUtils::GetCmdFromEvent(&msg, evt);
            DT_ERR(("Failed To Send ACR Start Request"));

            if (DIA_SE_STYPE(ctxt) == DIA_ACCOUNTING)
            {
                string sessionId = msg->getSessionId()->value(); 
                Cleanup(ctxt, sessionId);
                DiaErrHandler::HandleError(0, msg,
                                             LOOP_TO_APP,
                                             ITS_DIA_UNABLE_TO_DELIVER);
            }
            else
            {
                DiaErrHandler::HandleError(0, msg,
                                             LOOP_TO_APP,
                                             ITS_DIA_UNABLE_TO_DELIVER);

                DIA_SE_ACC_STATE(ctxt) = ACCT_SESSION_ST_IDLE;
                ret = FSM_STATE_UPDATE;
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
 *        Process the messages in ClientAcctFsm state
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
 *        ITS_SUCCESS : On successful ClientAcctFsm state process
 *  
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
ITS_INT
ClientAcctFsm_Pending_S::ProcessEvent(void *vctxt, ITS_EVENT *evt)
{
    int ret = FSM_NO_STATE_UPDATE;
    DIA_BASE_CMD *msg = NULL;
    SESSION_ENTRY* ctxt = (SESSION_ENTRY*)vctxt;

    DT_DBG(("ClientAcctFsm::Pending_S --> Evt Type %s",
           ACCT_SESSION_EVENT_TO_TEXT(DIA_SE_EVT_TYPE(ctxt))));

    switch(DIA_SE_EVT_TYPE(ctxt))
    {
    case ACCT_SESSION_EVT_RX_ACA_OK:
    case ACCT_SESSION_EVT_RX_ACA_FAIL_AND_GAL:
    {
        DiaUtils::GetCmdFromData(&msg, &evt->data[sizeof(ITS_USHORT)]);

        /* Restart All timers */
        SESSION_TABLE->StopAllAcctTimers(ctxt);
        StartAcctSessionTimer(ctxt, msg);
        StartAcctIntTimer(ctxt, msg);

        DiaMsgRouter::SendMsgToApp(ctxt, evt);

        DIA_SE_ACC_STATE(ctxt) = ACCT_SESSION_ST_OPEN;
        ret = FSM_STATE_UPDATE;

        break;
    }
    case ACCT_SESSION_EVT_FTS_NOT_DAG:
        DT_DBG(("Action: Store start record"));
        // TODO Store start record
        DIA_SE_ACC_STATE(ctxt) = ACCT_SESSION_ST_OPEN;
        ret = FSM_STATE_UPDATE;

        break;
    case ACCT_SESSION_EVT_FTS_NOT_GAL:
        DT_DBG(("Action: None"));
        DIA_SE_ACC_STATE(ctxt) = ACCT_SESSION_ST_OPEN;
        ret = FSM_STATE_UPDATE;

        break;
    case ACCT_SESSION_EVT_RX_ACA_FAIL_NOT_GAL:
    {
        DT_DBG(("Action: Disconnect user device"));

        if (DIA_SE_STYPE(ctxt) == DIA_ACCOUNTING)
        {
            DiaUtils::GetCmdFromData(&msg, &evt->data[sizeof(ITS_USHORT)]);
            string sessionId = msg->getSessionId()->value();
            Cleanup(ctxt, sessionId);
        }
        else
        {
            DIA_SE_ACC_STATE(ctxt) = ACCT_SESSION_ST_OPEN;
            ret = FSM_STATE_UPDATE;
        }
        DiaMsgRouter::SendMsgToApp(ctxt, evt);

        break;
    }
    case ACCT_SESSION_EVT_FTS_AND_GAL:
        break;
    case ACCT_SESSION_EVT_STOP:
        // Evt: User svc terminated
        DT_DBG(("Action:store stop record "));
        // TODO Store start record
        break;
    default:
        DT_ERR(("Invalid Event Type"));
        return (ITS_EBADSTATE);
    }
    return (ret);
}

/****************************************************************************
 *  Purpose:
 *        Process the messages in ClientAcctFsm state
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
 *        ITS_SUCCESS : On successful ClientAcctFsm state process
 *
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
ITS_INT
ClientAcctFsm_Pending_E::ProcessEvent(void *vctxt, ITS_EVENT *evt)
{
    int ret = FSM_NO_STATE_UPDATE;
    DIA_BASE_CMD *msg = NULL;
    SESSION_ENTRY* ctxt = (SESSION_ENTRY*)vctxt;

    DT_DBG(("ClientAcctFsm::Pending_E --> Evt Type %s",
           ACCT_SESSION_EVENT_TO_TEXT(DIA_SE_EVT_TYPE(ctxt))));

    switch(DIA_SE_EVT_TYPE(ctxt))
    {
    case ACCT_SESSION_EVT_RX_ACA_OK:
    case ACCT_SESSION_EVT_RX_ACA_FAIL:

        if (DIA_SE_STYPE(ctxt) == DIA_ACCOUNTING)
        {
            DiaUtils::GetCmdFromData(&msg, &evt->data[sizeof(ITS_USHORT)]);
            string sessionId = msg->getSessionId()->value();
            Cleanup(ctxt, sessionId);
        }
        else
        {
            DIA_SE_ACC_STATE(ctxt) = ACCT_SESSION_ST_IDLE;
            ret = FSM_STATE_UPDATE;
        }
        DiaMsgRouter::SendMsgToApp(ctxt, evt);

        break;
    case ACCT_SESSION_EVT_FTS_BUF:
        // FTS Buffer available
        DT_DBG(("Action: Store event record."));
        DIA_SE_ACC_STATE(ctxt) = ACCT_SESSION_ST_IDLE;
        ret = FSM_STATE_UPDATE;

        break;
    case ACCT_SESSION_EVT_FTS_NO_BUF:
        break;
    default:
        DT_ERR(("Invalid Event Type"));
        return (ITS_EBADSTATE);
    }
    return (ret);
}

/****************************************************************************
 *  Purpose:
 *        Process the messages in ClientAcctFsm state
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
 *        ITS_SUCCESS : On successful ClientAcctFsm state process
 *
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
ITS_INT
ClientAcctFsm_Pending_B::ProcessEvent(void *vctxt, ITS_EVENT *evt)
{
    int ret = FSM_NO_STATE_UPDATE;
    DIA_BASE_CMD *msg = NULL;
    SESSION_ENTRY* ctxt = (SESSION_ENTRY*)vctxt;

    DT_DBG(("ClientAcctFsm::Pending_B --> Evt Type %s",
           ACCT_SESSION_EVENT_TO_TEXT(DIA_SE_EVT_TYPE(ctxt))));

    switch(DIA_SE_EVT_TYPE(ctxt))
    {
    case ACCT_SESSION_EVT_RX_ACA_OK:
    case ACCT_SESSION_EVT_RX_ACA_FAIL:
    case ACCT_SESSION_EVT_RX_ACA_FAIL_AND_GAL:
    case ACCT_SESSION_EVT_RX_ACA_FAIL_NOT_GAL:

        DT_DBG(("Action: Delete record"));

        if (DIA_SE_STYPE(ctxt) == DIA_ACCOUNTING)
        {
            DiaUtils::GetCmdFromData(&msg, &evt->data[sizeof(ITS_USHORT)]);
            string sessionId = msg->getSessionId()->value();
            Cleanup(ctxt, sessionId);
        }
        else
        {
            DIA_SE_ACC_STATE(ctxt) = ACCT_SESSION_ST_IDLE;
            ret = FSM_STATE_UPDATE;
        }
        DiaMsgRouter::SendMsgToApp(ctxt, evt);

        break;
    case ACCT_SESSION_EVT_FTS:
        DT_DBG(("Action: None"));
        DIA_SE_ACC_STATE(ctxt) = ACCT_SESSION_ST_IDLE;
        ret = FSM_STATE_UPDATE;

        break;
    default:
        DT_ERR(("Invalid Event Type"));
        return (ITS_EBADSTATE);

    }
    return (ret);
}

/****************************************************************************
 *  Purpose:
 *        Process the messages in ClientAcctFsm state
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
 *        ITS_SUCCESS : On successful ClientAcctFsm state process
 *
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
ITS_INT
ClientAcctFsm_Pending_I::ProcessEvent(void *vctxt, ITS_EVENT *evt)
{
    int ret = FSM_NO_STATE_UPDATE;
    DIA_BASE_CMD *msg = NULL;
    SESSION_ENTRY* ctxt = (SESSION_ENTRY*)vctxt;

    DT_DBG(("ClientAcctFsm::Pending_I --> Evt Type %s",
           ACCT_SESSION_EVENT_TO_TEXT(DIA_SE_EVT_TYPE(ctxt))));

    switch(DIA_SE_EVT_TYPE(ctxt))
    {
    case ACCT_SESSION_EVT_RX_ACA_OK:
    case ACCT_SESSION_EVT_RX_ACA_FAIL_AND_GAL:
    {
        DiaUtils::GetCmdFromData(&msg, &evt->data[sizeof(ITS_USHORT)]);
       
        /* Restart Timers */ 
        SESSION_TABLE->StopAllAcctTimers(ctxt);
        StartAcctSessionTimer(ctxt,msg);
        StartAcctIntTimer(ctxt,msg);
        DiaMsgRouter::SendMsgToApp(ctxt, evt);

        DIA_SE_ACC_STATE(ctxt) = ACCT_SESSION_ST_OPEN;
        ret = FSM_STATE_UPDATE;
        break;
    } 
    case ACCT_SESSION_EVT_FTS_AND_GAL:
       // Evt: Received interim ACA or FTS_AND_GAL or RX_ACA_FAIL_AND_GAL
        DT_DBG(("Action: None"));
        DIA_SE_ACC_STATE(ctxt) = ACCT_SESSION_ST_OPEN;
        ret = FSM_STATE_UPDATE;

        break;
    case ACCT_SESSION_EVT_FTS_NOT_DAG:
        DT_DBG(("Action: Store interim record"));
        // TODO Store interim record
        DIA_SE_ACC_STATE(ctxt) = ACCT_SESSION_ST_OPEN;
        ret = FSM_STATE_UPDATE;

        break;
    case ACCT_SESSION_EVT_FTS_NOT_GAL:
        break;
    case ACCT_SESSION_EVT_RX_ACA_FAIL_NOT_GAL:
    {
        DT_DBG(("Action: Disconnect user device"));

        if ( DIA_SE_STYPE(ctxt) == DIA_ACCOUNTING)
        {
            DiaUtils::GetCmdFromData(&msg, &evt->data[sizeof(ITS_USHORT)]);
            string sessionId = msg->getSessionId()->value();
            Cleanup(ctxt, sessionId);
        }
        else
        {
            DIA_SE_ACC_STATE(ctxt) = ACCT_SESSION_ST_IDLE;
            ret = FSM_STATE_UPDATE;
        }
        DiaMsgRouter::SendMsgToApp(ctxt, evt);
        break;
    }
    case ACCT_SESSION_EVT_STOP:
        DT_DBG(("Action: Store stop record"));

        break;
    default:
        DT_ERR(("Invalid Event Type"));
        return (ITS_EBADSTATE);
    }
    return (ret);
}

/****************************************************************************
 *  Purpose:
 *        Process the messages in ClientAcctFsm state
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
 *        ITS_SUCCESS : On successful ClientAcctFsm state process
 *
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
ITS_INT
ClientAcctFsm_Pending_L::ProcessEvent(void *vctxt, ITS_EVENT *evt)
{
    int ret = FSM_NO_STATE_UPDATE;
    DIA_BASE_CMD *msg = NULL;
    SESSION_ENTRY* ctxt = (SESSION_ENTRY*)vctxt;

    DT_DBG(("ClientAcctFsm::Pending_L --> Evt Type %s",
           ACCT_SESSION_EVENT_TO_TEXT(DIA_SE_EVT_TYPE(ctxt))));

    switch(DIA_SE_EVT_TYPE(ctxt))
    {
    case ACCT_SESSION_EVT_RX_ACA_OK:
    case ACCT_SESSION_EVT_RX_ACA_FAIL:
        // Stop ACA  Received or FTS no buf available or Failed stop ACA Recvd 
        DT_DBG(("Action: None"));
        if ( DIA_SE_STYPE(ctxt) == DIA_ACCOUNTING)
        {
            DiaUtils::GetCmdFromData(&msg, &evt->data[sizeof(ITS_USHORT)]);
            string sessionId = msg->getSessionId()->value();
            Cleanup(ctxt, sessionId);
        }
        else
        {
            DIA_SE_ACC_STATE(ctxt) = ACCT_SESSION_ST_IDLE;
            ret = FSM_STATE_UPDATE;
        }
        DiaMsgRouter::SendMsgToApp(ctxt, evt);

        break;
    case ACCT_SESSION_EVT_FTS_BUF:
        DT_DBG(("Action: Store stop record."));
        // TODO Store stop record.
        DIA_SE_ACC_STATE(ctxt) = ACCT_SESSION_ST_IDLE;
        ret = FSM_STATE_UPDATE;

        break;
    case ACCT_SESSION_EVT_FTS_NO_BUF:
        break;
    default:
        DT_ERR(("Invalid Event Type"));
        return (ITS_EBADSTATE);
    }
    return (ret);
}

