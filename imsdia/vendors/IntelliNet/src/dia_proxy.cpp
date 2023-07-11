/*********************************-*CPP*-************************************
 *                                                                          *
 *     Copyright 2008 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: dia_proxy.cpp,v $
 * LOG: Revision 1.7.18.1.2.9.4.7.4.4  2014/01/06 09:22:32  cprem
 * LOG: Changes in diameter stack to support session replication. Review request 1611.
 * LOG:
 * LOG: Revision 1.7.18.1.2.9.4.7.4.3  2013/12/20 05:38:49  vsarath
 * LOG: Session split changes
 * LOG:
 * LOG: Revision 1.7.18.1.2.9.4.7.4.2  2013/12/13 09:34:58  vsarath
 * LOG: Merged the session-splict changes
 * LOG:
 * LOG: Revision 1.7.18.1.2.9.4.7.4.1  2013/09/10 08:36:39  ncshivakumar
 * LOG: RFC6733 Changes
 * LOG:
 * LOG: Revision 1.7.18.1.2.9.4.7  2013/04/18 13:38:24  jsarvesh
 * LOG: changes done for interface stats increment for req in message
 * LOG:
 * LOG: Revision 1.7.18.1.2.9.4.6  2013/04/16 09:06:11  jsarvesh
 * LOG: changes if resultcode avp is not present in message
 * LOG:
 * LOG: Revision 1.7.18.1.2.9.4.5  2013/04/12 04:18:02  vsarath
 * LOG: Logs improvement
 * LOG:
 * LOG: Revision 1.7.18.1.2.9.4.4  2013/04/04 09:06:11  mallikarjun
 * LOG: MemLeak Fixes Bug 1205 1298
 * LOG:
 * LOG: Revision 1.7.18.1.2.9.4.3  2013/03/22 05:56:57  jvikram
 * LOG: Corrected the issues related to message handling related to same session id
 * LOG: by queuing the messages. Also included debug logs.
 * LOG:
 * LOG: Revision 1.7.18.1.2.9.4.2  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 1.7.18.1.2.9.4.1  2013/02/01 11:34:16  pramana
 * LOG: Merged from branch 0212 to 0300.
 * LOG:
 * LOG: Revision 1.7.18.1.2.10  2013/01/23 03:08:16  vsarath
 * LOG: Fix for issue 976
 * LOG:
 * LOG: Revision 1.7.18.1.2.9  2012/12/21 05:31:54  ncshivakumar
 * LOG: Modified for tracing
 * LOG:
 * LOG: Revision 1.7.18.1.2.8  2012/12/17 05:34:17  mallikarjun
 * LOG: Bug 699 T bit
 * LOG:
 * LOG: Revision 1.7.18.1.2.7  2012/12/03 08:41:20  ncshivakumar
 * LOG: Changes done for adding static routing table
 * LOG:
 * LOG: Revision 1.7.18.1.2.6  2012/12/03 02:36:15  mallikarjun
 * LOG: Bug-148-Alternate-Peer
 * LOG:
 * LOG: Revision 1.7.18.1.2.5  2012/09/21 09:23:21  jvikas
* LOG: Bug-210: Added Route-Record AVP in case ERLBF is enabled.
* LOG:
* LOG: Revision 1.7.18.1.2.4  2012/09/17 05:03:26  rsanjay
* LOG: Fixes for the bugs 17, 104 and 121, Handling the case where message for proxy is received for an existing session and destination host is down. And also handling a case where the destination-host in destination-host avp is down when a proxy request(stateless) is received.
* LOG:
* LOG: Revision 1.7.18.1.2.3  2012/09/06 13:04:15  ncshivakumar
* LOG: fix for bug 113
* LOG:
* LOG: Revision 1.7.18.1.2.2  2012/09/04 07:49:55  pramana
* LOG: To fix the issue with application sent ULA
* LOG:
* LOG: Revision 1.7.18.1.2.1  2012/08/21 08:55:57  ksalil
* LOG: Merge from branch B-DRE-IDIA-0100-00
* LOG:
* LOG: Revision 1.7.18.2  2012/08/06 04:16:09  rsanjay
* LOG: Bug No 103: Changes to handle  peer selection by the DRE application using app routing algorithm
* LOG:
* LOG: Revision 1.7.18.1  2012/03/07 13:23:08  brajappa
* LOG: Changes made for the DRE demo
* LOG:
* LOG: Revision 1.7  2009/03/19 12:37:16  nvijikumar
* LOG: Global instance is created for the Class ITSDiaConfig to avoid function
* LOG: call overhead as ITSDiaConfig::GetITSDiaConfig() was called max time
* LOG:
* LOG: Revision 1.6  2009/02/19 14:07:45  ssaxena
* LOG: Partial fix for the whizible issue Id 1493, 1481 and 1482.
* LOG: Default routing failed and Relay/Proxy failed to forward
* LOG: ASR/RAR.
* LOG:
* LOG: Revision 1.5  2008/12/24 08:36:08  rajeshak
* LOG: IssueID:1387
* LOG: FeatureID:none
* LOG: Description: (Proxy:Invalid Hop-by-Hop id received
        * LOG: in answer message for RAR sent from server IDC)
    * LOG: Copied the original hop-by-hop id from the session entry
* LOG: (server hop-by-hop id)
    * LOG:
    * LOG: Revision 1.4  2008/12/23 14:57:51  rajeshak
    * LOG: IssueID:1387
    * LOG: FeatureID:none
    * LOG: Description: (Stateless Proxy agent not sending
            * LOG: the request message to server IDS.)
    * LOG: SendCmdToPeer call was missing in stateless.
    * LOG:
    * LOG: Revision 1.3  2008/12/23 08:31:25  rajeshak
    * LOG: Moved and renamed InitNInsertAcctSession & InitNInsertAuthSession function
    * LOG: from dia_utils to dia_session_table
    * LOG:
    * LOG: Revision 1.2  2008/12/12 18:30:47  rajeshak
    * LOG: Lightweight Decode for base AVPS
* LOG: New Command class is introduced (BaseCommand)
    * LOG:
    * LOG: Revision 1.1  2008/12/07 09:56:56  rajeshak
    * LOG: Added new file to separate the functionality of proxy from main stack.
    * LOG:
    *
    * ID: $Id: dia_proxy.cpp,v 1.7.18.1.2.9.4.7.4.4 2014/01/06 09:22:32 cprem Exp $
    ****************************************************************************/
#ident "$Id: dia_proxy.cpp,v 1.7.18.1.2.9.4.7.4.4 2014/01/06 09:22:32 cprem Exp $"

#include <dia_err.h>
#include <dia_cmn.h>
#include <dia_utils.h>
#include <dia_msg_router.h>
#include <dia_proxy.h>
#include <dia_session_auth_fsm.h>
#include <dia_session_acct_fsm.h>
#include <dia_incoming_msg_q.h>
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

    int 
DiaProxyHandler::HandleAcctReqMsgFromApp(DIA_BASE_CMD *cmd, 
        ITS_OCTET * sessionId, 
        SESSION_ENTRY *e, its::Event &ev)
{
    int ret = ITS_SUCCESS;
    ITS_UINT appId = 0;
    ITS_UINT sessIndx = 0;
    ITS_USHORT peerInstance = 0;
    DIA_BASE_CMD *msg = (DIA_BASE_CMD *)cmd;
    ITS_UINT recType = msg->getAccountingRecordType()->value();
    REALM_ENTRY *rEntry = NULL;

    switch (DIA_SE_ACC_FSM_TYPE(e))
    {
        case STATEFUL_SERVER_ACCT_PXY_FSM:
            {
                DT_DBG(("Stateful Proxy Accounting Server"));
                if (DIA_SE_MSG_STATUS(e) == WAIT_REQ_FROM_APP)
                {
                    DT_DBG(("Proxy Request received from Application"));
                    DIA_SE_MSG_STATUS(e)   = WAIT_ANS_FROM_PEER;
                }
                else
                {
                    ret = DiaErrHandler::SendErrorResponse(e, msg);
                    return ret;
                }

                if (!DIA_SE_IS_AGENT(e))
                {
                    DT_ERR(("Invalid SMType: %d",DIA_SE_ACC_FSM_TYPE(e)));
                    /* Error Response if first acr is STOP/INTERIM on AuthSess */
                    DiaErrHandler::HandleError(0, msg, LOOP_TO_APP,
                            ITS_DIA_UNKNOWN_SESSION_ID);
                    break;
                }

                DT_DBG(("Accounting Request Received from Application on" \
                            " Proxy Session"));
                switch(recType)
                {
                    case AccountingRecordType::EVENT_RECORD:
                        DT_DBG(("Accounting Event Request"));
                        break;
                    case AccountingRecordType::START_RECORD:
                        DT_DBG(("Accounting Start Request"));
                        break;
                    case AccountingRecordType::INTERIM_RECORD:
                        DT_DBG(("Accounting Interim Request"));
                        break;
                    case AccountingRecordType::STOP_RECORD:
                        DT_DBG(("Accounting Stop Request"));
                        break;
                    default:
                        DT_WRN(("Invalid Accounting Record Type"));
                        /* Error Response if first acr is STOP/INTERIM on ActSess */
                        ret = DiaErrHandler::HandleError(0, msg, LOOP_TO_APP,
                                ITS_DIA_INVALID_EVENT);
                        return ret;

                }
                DIA_SE_EVT_TYPE(e) = ACCT_SESSION_EVT_ACCESS_TX_AGENT;

                /**
                 * Same statefulServerAcctFsm is used for Accounting Proxy stateful
                 * Server also.
                 */ 
                ret = statefulServerAcctFsm.SubmitToSM(e, &ev.GetEvent());

                if (ret == FSM_STATE_UPDATE)
                {
                    //Warning Fix - suggest parentheses around assignment used as truth value
                    if ((ret = SESSION_TABLE->ModifyEntry(e,
                                    (ITS_OCTET *)sessionId, strlen((const char*)sessionId)))
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
        case STATELESS_SERVER_ACCT_PXY_FSM:
            {
                DT_DBG(("Stateless Proxy Accounting Server"));
                if (DIA_SE_MSG_STATUS(e) == WAIT_REQ_FROM_APP)
                {
                    DT_DBG(("Proxy Request received from Application"));
                    DIA_SE_MSG_STATUS(e)   = WAIT_ANS_FROM_PEER;
                }
                else
                {
                    ret = DiaErrHandler::SendErrorResponse(e, msg);
                    return ret;
                }

                if (!DIA_SE_IS_AGENT(e))
                {
                    DT_ERR(("Invalid SMType: %d",DIA_SE_ACC_FSM_TYPE(e)));
                    /* Error Response if first acr is STOP/INTERIM on AuthSess */
                    DiaErrHandler::HandleError(0, msg, LOOP_TO_APP,
                            ITS_DIA_UNKNOWN_SESSION_ID);
                    break;
                }
                DT_DBG(("Stateless Accounting Server Session for agent"));
                DIA_BASE_CMD *msg = NULL;
                DiaUtils::GetCmdFromEvent(&msg, &ev.GetEvent());
                DIA_BASE_CMD *cmd = (DIA_BASE_CMD *)msg;

                DT_DBG(("Sending Message to Peer"));
                /* Try Peer Table Based Routing */
                ret = DiaMsgRouter::RequestForwarding(cmd, e, peerInstance);


                if (ret != ITS_SUCCESS)
                {
                    DT_DBG(("No matching Peer found or Peer isn't active"));
                    /*  Try Routing using static routing table  */
                    ret = DiaMsgRouter::StaticRouting(cmd,e,peerInstance,NULL);

                }
                if (ret != ITS_SUCCESS)
                {
                    DT_WRN(("Static Routing failed, Trying RequestRouting"));
                    /* Realm Routing */
                    if ((ret = DiaMsgRouter::RequestRouting(cmd, e,
                                    peerInstance,
                                    rEntry)) != ITS_SUCCESS)
                    {
                        DT_ERR(("RequestRouting Failed"));
                        /**
                         * Send Error response as not able to deliver the messge.
                         */
                        ret = DiaErrHandler::HandleError(DIA_SE_PEER_INST(e), msg,
                                SEND_ERROR_TO_PEER,
                                ITS_DIA_UNABLE_TO_DELIVER);
                        return (ret);
                    }

                    DT_DBG(("RequestRouting via Realm Table succesfull"));
                } 

                if((ret == ITS_SUCCESS)&&(itsDiaConfig.isPredictiveLoopAvoidanceEnable()))
                {
                    DiaSocketTransport *tr = trTable[peerInstance];
                    PEER_ENTRY* pEntry = tr->GetPeer();

                    const char *destHost = DIA_PE_HOST(pEntry);
                    if(DiaMsgRouter::IsPredectiveLoopDetected(cmd,destHost)) 
                    {
                        if(DiaMsgRouter::SelectAlternatePeerToRoute(destHost,cmd,e,peerInstance)== ITS_DIA_UNABLE_TO_DELIVER)
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
                    DIA_SE_LOCAL_HH(e)        = ((DIA_BASE_CMD *)cmd)->getHeader().hh;
                    DIA_SE_PEER_INST_AGENT(e) = peerInstance;
                    if (SESSION_TABLE->ModifyEntry(e, (ITS_OCTET *)sessionId,
                                strlen((const char*)sessionId)) == ITS_SUCCESS)
                    {
                        DT_DBG(("Succesfully Updated Session Context"));
                    }
                    DIA_HDR &hdr = (DIA_HDR&)msg->getHeader();

                    ret = DiaMsgRouter::SendCmdToPeer(peerInstance,
                            &hdr,
                            cmd);
                }
                break;
            }
        default:
            DT_ERR(("Invalid SMType: %d",DIA_SE_ACC_FSM_TYPE(e)));
            /* Error Response if first acr is STOP/INTERIM on AuthSess */
            DiaErrHandler::HandleError(0, msg, LOOP_TO_APP,
                    ITS_DIA_UNKNOWN_SESSION_ID);

            break;
    }
    return ret;    
}

    int 
DiaProxyHandler::HandleAuthReqMsgFromApp(DIA_BASE_CMD *cmd, 
        ITS_OCTET * sessionId, 
        SESSION_ENTRY *e, its::Event &ev)
{
    int ret = ITS_SUCCESS;
    ITS_UINT appId = 0;
    ITS_UINT sessIndx = 0;
    ITS_USHORT peerInstance = 0;
    DIA_BASE_CMD *msg = (DIA_BASE_CMD *)cmd;

    //SESSION_TABLE->Lock();
    switch (DIA_SE_FSM_TYPE(e))
    {
        case STATEFUL_SERVER_AUTH_PXY_FSM:
            {
                DT_DBG(("Stateful Proxy Server"));
                /**
                 * Relaxing the Proxy msg status checks for the ASR/STR
                 */
                if (DIA_SE_MSG_STATUS(e) == WAIT_REQ_FROM_APP ||
                        msg->getCommandCode() ==  DIA_MSG_AS ||
                        msg->getCommandCode() ==  DIA_MSG_ST)
                {
                    DT_DBG(("Proxy Request received from Application"));
                    DIA_SE_MSG_STATUS(e)   = WAIT_ANS_FROM_PEER; 
                }
                else
                {
                    DIA_SE_CLIENTID(e) = msg->getClientId();
                    ret = DiaErrHandler::SendErrorResponse(e, msg);
                    //SESSION_TABLE->Unlock();
                    return ret; 
                } 

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
                        DT_DBG(("Sending Proxy Request to State Machine"));
                        DIA_SE_EVT_TYPE(e) = AUTH_SESSION_EVT_TX_SSAA_AGENT;
                        ret = statefulServerAuthFsm.SubmitToSM(e, &ev.GetEvent());
                        break;
                }
                if (ret == FSM_STATE_UPDATE)
                {
                    //Warning Fix - suggest parentheses around assignment used as truth value
                    if ((ret = SESSION_TABLE->ModifyEntry(e,
                                    (ITS_OCTET *)sessionId,
                                    strlen((const char*)sessionId)))
                            != ITS_SUCCESS)
                    {
                        DT_ERR(("Failed to update Session Context"));
                    }
                }
                //SESSION_TABLE->Unlock();
                break;
            }
        case STATELESS_SERVER_AUTH_PXY_FSM:
            {
                DT_DBG(("Stateless Proxy Server"));
                REALM_ENTRY *rEntry = NULL;

                if (DIA_SE_MSG_STATUS(e) == WAIT_REQ_FROM_APP)
                {
                    DT_DBG(("Proxy Request received from Application"));
                    DIA_SE_MSG_STATUS(e)   = WAIT_ANS_FROM_PEER;
                }
                else
                {
                    ret = DiaErrHandler::SendErrorResponse(e, msg);
                    return ret;
                }

                //check if event source is from the app
                if(ev.GetSource() == DIA_APP_INST)
                {

                    ITS_EVENT   *evt    = &ev.GetEvent();
                    DT_DBG(("An event is received that is from the application"));
                    //check if event is a DiaMsgToPeerEvt
                    if(evt->len == sizeof(DiaMsgToPeerEvt))
                    {
                        peerInstance = ((DiaMsgToPeerEvt*) (evt->data))->toPeer;

                        //check if we got the peer instance from the application
                        if(peerInstance != UNKNOWN_PEER_INST)
                        {
                            //we got a peer selected by the application using some routing algorithm
                            DT_DBG(("Application Routing peer = %d", peerInstance));
                            /*Bug-210::Generate HopByHopId and Fill Route-Record AVP.*/
                            DIA_HDR &hdr = (DIA_HDR&)cmd->getHeader();
                            DT_DBG(("ERLBF enabled, Peer Instance Selected, Setting HopByHopId"));
                            hdr.hh = DiaUtils::GenerateHopByHopId();
                            if (e && DIA_SE_AGENT_TYPE(e) != ITS_DIA_LOCAL)
                            {
                                DiaUtils::AddRouteRecordAvp(cmd, e);
                                DIA_SE_LOCAL_HH(e) = hdr.hh;
                            }
                            ret = ITS_SUCCESS;
                        }
                        else
                        {
                            ret = !ITS_SUCCESS;
                        }
                    }
                }

                if( ret != ITS_SUCCESS)
                {
                    DT_DBG(("Sending Message to Peer"));
                    /* Try Peer Table Based Routing */
                    ret = DiaMsgRouter::RequestForwarding(cmd, e, peerInstance);

                    //Below Fix is blocking AltermatePeer Functionality,The bugs that require below fix are no more valid with the latest relase 
                    /* check if destination host avp is present and if transport is down
                     * for that peer*/
                    PEER_ENTRY * peerEntry = NULL;

                    if( (cmd->getDestinationHost() != NULL) && (ret == ITS_DIA_UNABLE_TO_DELIVER ))
                    {
                        PEER_TABLE->FindEntry(cmd->getDestinationHost()->value().c_str(), peerEntry );

                        if((DIA_PE_ALT_HOST(peerEntry) == NULL ) &&  (DIA_PEER_CHK_IS_FAILOVER_ENABLED(peerEntry) == false ))
                        {


                            /*The return value of RequestForwarding function will be
                             * ITS_DIA_UNABLE_TO_DELIVER if the host in Destination-Host avp is
                             * down so handling this scenario by sending 3002 error back*/

                            DT_ERR(("Destination-Host %s is Down", cmd->getDestinationHost()->value().c_str()));
                            ret = DiaErrHandler::HandleError(DIA_SE_PEER_INST(e), msg,
                                    SEND_ERROR_TO_PEER,
                                    ITS_DIA_UNABLE_TO_DELIVER);
                            return (ret);

                        }
                    }
                }

                if (ret != ITS_SUCCESS)
                {
                    DT_DBG(("No matching Peer found or Peer isn't active"));
                    /*  Try Routing using static routing table */
                    ret = DiaMsgRouter::StaticRouting(cmd,e,peerInstance,NULL);
                }	
                if (ret != ITS_SUCCESS)
                {
                    DT_WRN(("Static routing failed, Trying RequestRouting"));
                    /* Realm Routing */
                    if ((ret = DiaMsgRouter::RequestRouting(cmd, e,
                                    peerInstance,
                                    rEntry)) != ITS_SUCCESS)
                    {
                        DT_ERR(("RequestRouting Failed"));
                        /**
                         * Send Error response as not able to deliver the messge.
                         */
                        ret = DiaErrHandler::HandleError(DIA_SE_PEER_INST(e), msg,
                                SEND_ERROR_TO_PEER,
                                ITS_DIA_UNABLE_TO_DELIVER);
                        return (ret);
                    }
                    DT_DBG(("RequestRouting via Realm Table succesfull"));
                }

                if(ret == ITS_SUCCESS && itsDiaConfig.isPredictiveLoopAvoidanceEnable())
                {
                    DiaSocketTransport *tr = trTable[peerInstance];
                    PEER_ENTRY* pEntry = tr->GetPeer();

                    const char *destHost = DIA_PE_HOST(pEntry);
                    if(DiaMsgRouter::IsPredectiveLoopDetected(cmd,destHost)) 
                    {
                        if(DiaMsgRouter::SelectAlternatePeerToRoute(destHost,cmd,e,peerInstance)== ITS_DIA_UNABLE_TO_DELIVER)
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
                    DIA_SE_LOCAL_HH(e)        = ((DIA_BASE_CMD *)cmd)->getHeader().hh;
                    DIA_SE_PEER_INST_AGENT(e) = peerInstance;
                    if (SESSION_TABLE->ModifyEntry(e, (ITS_OCTET *)sessionId,
                                strlen((const char*)sessionId)) != ITS_SUCCESS)
                    {
                        DT_ERR(("Failed to update Session Context"));
                    }
                    DIA_HDR &hdr = (DIA_HDR&)msg->getHeader();

                    ret = DiaMsgRouter::SendCmdToPeer(peerInstance,
                            &hdr,
                            cmd);
                }
                break;
            }
        default:
            DT_ERR(("Invalid SMType: %d",DIA_SE_FSM_TYPE(e)));
            ret = !ITS_SUCCESS;
            break;
    }
    return ret;
}

    int 
DiaProxyHandler::HandleAcctAnsMsgFromApp(DIA_BASE_CMD *cmd, 
        ITS_OCTET * sessionId, 
        SESSION_ENTRY *ent, its::Event &ev)
{
    int ret = ITS_SUCCESS;
    ITS_UINT appId = 0;
    ITS_UINT sessIndx = 0;
    ITS_UINT resultCode = ITS_DIA_SUCCESS;
    DIA_BASE_CMD *gCmd = (DIA_BASE_CMD *)cmd;

    /* If Answer is received from the Application and it doesn't
       contain resultCode, we treat it as succesfull indication
       that the User is Authorized
       */
    if (gCmd->getResultCode())
    {
        resultCode = gCmd->getResultCode()->value();
    }

    switch (DIA_SE_ACC_FSM_TYPE(ent))
    {
        case STATEFUL_SERVER_ACCT_PXY_FSM:
            {
                DT_DBG(("Stateful Proxy Accounting Server Session"));
                /*if (DIA_SE_MSG_STATUS(ent) == WAIT_ANS_FROM_APP)
                  {
                  DT_DBG(("Proxy Answer received from App."));
                  DIA_SE_MSG_STATUS(ent)   = ANS_SND_TO_PEER;
                  }
                  else*/
                if( DIA_SE_MSG_STATUS(ent) != WAIT_ANS_FROM_APP)
                {
                    if (DIA_SE_MSG_STATUS(ent) == WAIT_REQ_FROM_APP)
                    {
                        /**
                         * Send Error response as message received is Invalid.
                         */
                        DT_ERR(("Message received not proper," \
                                    " Sending error response"));

                        DIA_HDR &hdr = (DIA_HDR&)gCmd->getHeader();
                        hdr.hh = DIA_SE_RX_HH(ent);
                        hdr.ee = DIA_SE_RX_EE(ent);
                        hdr.flags = DIA_SE_RX_FLAGS(ent);
                        hdr.appId =  DIA_SE_APP_ID(ent); 
                    }

                    DT_ERR(("Invalid Answer received from App. Discarding..."));
                    DT_DBG(("Sending Error indication to Application"));

                    ret = DiaErrHandler::SendErrorResponse(ent, gCmd);
                    return ret;
                }

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
                DIA_SE_CLIENTID(ent)  = ((DIA_BASE_CMD *)cmd)->getClientId();


                DIA_SE_MSG_STATUS(ent)   = ANS_SND_TO_PEER;

                if (ret == FSM_STATE_UPDATE)
                {
                    if (SESSION_TABLE->ModifyEntry(ent,
                                (ITS_OCTET *)sessionId,
                                strlen((const char*)sessionId))
                            == ITS_SUCCESS)
                    {
                        DT_DBG(("Succesfully Updated Entry"));
                        //Replicate session info
                        if( (SessionTable::replicateSessions) &&
                                (SessionTable::sessUpdateCbk!= NULL))
                        {
                            SessionTable::sessUpdateCbk((char *)sessionId,ent);
                        }

                    }
                }
                if( ( DIA_SE_MESSAGES_PENDING(ent) == true ) && (DiaMsgRouter::RepostPendingMessageOfSession(ent,(ITS_OCTET *)sessionId)==ITS_SUCCESS) )
                {return ret;}
                break;
            }
        case STATELESS_SERVER_ACCT_PXY_FSM:
            {
                DT_DBG(("Stateless Proxy Accounting Server Session"));
                /*if (DIA_SE_MSG_STATUS(ent) == WAIT_ANS_FROM_APP)
                  {   
                  DT_DBG(("Proxy Answer received from Peer."));
                  DIA_SE_MSG_STATUS(ent)   = ANS_SND_TO_PEER;
                  }   
                  else*/
                if (DIA_SE_MSG_STATUS(ent) != WAIT_ANS_FROM_APP)
                { 
                    if (DIA_SE_MSG_STATUS(ent) == WAIT_REQ_FROM_APP)
                    {
                        /**
                         * Send Error response as message received is Invalid.
                         */
                        DT_ERR(("Message received not proper," \
                                    " Sending error response"));

                        DIA_HDR &hdr = (DIA_HDR&)gCmd->getHeader();
                        hdr.hh = DIA_SE_RX_HH(ent);
                        hdr.ee = DIA_SE_RX_EE(ent);
                        hdr.flags = DIA_SE_RX_FLAGS(ent);
                        hdr.appId =  DIA_SE_APP_ID(ent);
                    }

                    DT_ERR(("Invalid Answer received from App. Discarding..."));
                    DT_DBG(("Sending Error indication to Application"));

                    ret = DiaErrHandler::SendErrorResponse(ent, gCmd);
                    return ret; 
                }  

                DIA_BASE_CMD *msg = NULL;
                DiaUtils::GetCmdFromEvent(&msg, &ev.GetEvent());
                //Fixing Parse Warning - Hides existing cmd
                DIA_BASE_CMD *lcmd = (DIA_BASE_CMD *)msg;
                DIA_HDR &hdr = (DIA_HDR &)msg->getHeader();
                hdr.flags.p = (DIA_SE_RX_FLAGS(ent)).p;
                hdr.flags.t = (DIA_SE_RX_FLAGS(ent)).t;
                hdr.hh = DIA_SE_RX_HH(ent);
                hdr.ee = DIA_SE_RX_EE(ent);

                /* Validate the ResultCode for Stateless Agents */
                DiaUtils::IsResultCodeModified(gCmd, ent);

                if (DiaMsgRouter::SendCmdToPeer(DIA_SE_PEER_INST(ent),
                            &hdr,
                            lcmd) != ITS_SUCCESS)
                {
                    DT_ERR(("Failed to Send To Peer"));
                    return (ITS_ESENDFAIL);
                }

                DIA_SE_MSG_STATUS(ent)   = ANS_SND_TO_PEER;

                if( (DIA_SE_MESSAGES_PENDING(ent)  == true)&& (DiaMsgRouter::RepostPendingMessageOfSession(ent,(ITS_OCTET *)sessionId)==ITS_SUCCESS) )
                {return ret;}
                if (DIA_SE_STYPE(ent) == DIA_ACCOUNTING)
                {
                    if ((ret = SESSION_TABLE->RemoveEntry(ent,
                                    (ITS_OCTET *)sessionId,
                                    strlen((const char*)sessionId)))
                            != ITS_SUCCESS)
                    {
                        DT_ERR(("Failed to remove session Entry %d", ret));
                    }
                }
                break;
            }
        default:
            DT_ERR(("Invalid SM %d\n", DIA_SE_FSM_TYPE(ent)));
            break;
    }
    return ret;
}

    int 
DiaProxyHandler::HandleAuthAnsMsgFromApp(DIA_BASE_CMD *cmd, 
        ITS_OCTET * sessionId, 
        SESSION_ENTRY *ent, its::Event &ev)
{
    int ret = ITS_SUCCESS;
    ITS_UINT appId = 0;
    ITS_UINT sessIndx = 0;
    ITS_UINT resultCode = ITS_DIA_SUCCESS;
    DIA_BASE_CMD *gCmd = (DIA_BASE_CMD *)cmd;

    /* If Answer is received from the Application and it doesn't
       contain resultCode, we treat it as succesfull indication
       that the User is Authorized
       */
    //SESSION_TABLE->Lock();
    if (gCmd->getResultCode())
    {
        resultCode = ((DIA_BASE_CMD *)cmd)->getResultCode()->value();
    }

    switch (DIA_SE_FSM_TYPE(ent))
    {
        case STATEFUL_SERVER_AUTH_PXY_FSM:
            {
                DT_DBG(("Stateful Proxy Server Session"));
                /**
                 * Relaxing the Proxy msg status checks for the ASA/STA
                 */

                /*if (DIA_SE_MSG_STATUS(ent) == WAIT_ANS_FROM_APP ||
                  gCmd->getCommandCode() ==  DIA_MSG_AS ||
                  gCmd->getCommandCode() ==  DIA_MSG_ST)
                  {
                  DT_DBG(("Proxy Answer received from App."));
                  DIA_SE_MSG_STATUS(ent)   = ANS_SND_TO_PEER;
                  }
                  else*/
                if ( (DIA_SE_MSG_STATUS(ent) != WAIT_ANS_FROM_APP) &&
                        (gCmd->getCommandCode() !=  DIA_MSG_AS) && 
                        (gCmd->getCommandCode() !=  DIA_MSG_ST) )
                {
                    if (DIA_SE_MSG_STATUS(ent) == WAIT_REQ_FROM_APP)
                    {
                        /**
                         * Send Error response as message received is Invalid.
                         */
                        DT_ERR(("Message received not proper," \
                                    " Sending error response"));

                        DIA_HDR &hdr = (DIA_HDR&)gCmd->getHeader();
                        hdr.hh = DIA_SE_RX_HH(ent);
                        hdr.ee = DIA_SE_RX_EE(ent);
                        hdr.flags = DIA_SE_RX_FLAGS(ent);
                        hdr.appId =  DIA_SE_APP_ID(ent);
                    }
                    DIA_SE_CLIENTID(ent) = gCmd->getClientId();
                    DT_ERR(("Invalid Answer received from App. Discarding..."));
                    DT_DBG(("Sending Error indication to Application"));
                    ret = DiaErrHandler::SendErrorResponse(ent, gCmd);
                    //SESSION_TABLE->Unlock();
                    return ret; 
                }

                ITS_UINT commandCode = gCmd->getCommandCode();

                if (resultCode >= ITS_DIA_SUCCESS_MIN_RANGE &&
                        resultCode <= ITS_DIA_SUCCESS_MAX_RANGE)
                {
                    if (commandCode == DIA_MSG_AS)
                    {
                        DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_TX_ASA_OK;
                    }
                    else if (commandCode == DIA_MSG_RA)
                    {
                        DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_TX_RAA_OK;
                    }
                    else
                    {
                        DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_TX_SSAA_OK;
                    }
                }
                else
                {
                    if (commandCode == DIA_MSG_AS)
                    {
                        DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_TX_ASA_FAIL;
                    }
                    else if (commandCode == DIA_MSG_RA)
                    {
                        DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_TX_RAA_FAIL;
                    }
                    else
                    {
                        DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_TX_SSAA_FAIL;
                    }
                }
                if (gCmd->getAuthSessionState() &&
                        (gCmd->getAuthSessionState()->value() ==
                         AuthSessionState::NO_STATE_MAINTAINED))
                {
                    DT_DBG(("Answer::AuthSessionState::NO_STATE_MAINTAINED"));
                    DIA_HDR &hdr = (DIA_HDR &)gCmd->getHeader();
                    hdr.flags.p = (DIA_SE_RX_FLAGS(ent)).p;
                    hdr.flags.t = (DIA_SE_RX_FLAGS(ent)).t;
                    hdr.hh = DIA_SE_RX_HH(ent);
                    hdr.ee = DIA_SE_RX_EE(ent);

                    /* Validate the ResultCode for Stateless Agents */
                    DiaUtils::IsResultCodeModified(gCmd, ent);

                    if (DiaMsgRouter::SendCmdToPeer(DIA_SE_PEER_INST(ent),
                                &hdr,
                                cmd) != ITS_SUCCESS)
                    {
                        DT_ERR(("Failed to Send To Peer"));
                        return (ITS_ESENDFAIL);
                    }

                    if( (DIA_SE_MESSAGES_PENDING(ent)==true) && (DiaMsgRouter::RepostPendingMessageOfSession(ent,(ITS_OCTET *)sessionId)==ITS_SUCCESS) )
                    {return ret;}


                    if ((ret = SESSION_TABLE->RemoveEntry(ent,
                                    (ITS_OCTET *)sessionId,
                                    strlen((const char*)sessionId)))
                            != ITS_SUCCESS)
                    {
                        DT_ERR(("Failed to remove session Entry %d", ret));
                    }
                    //SESSION_TABLE->Unlock();
                }
                else
                {
                    /* fix for whizible issue 1388 */
                    if ((commandCode == DIA_MSG_RA) || (commandCode == DIA_MSG_AS))
                    {
                        DIA_HDR &hdr = (DIA_HDR&)gCmd->getHeader();
                        hdr.flags.p = (DIA_SE_RX_FLAGS(ent)).p;
                        hdr.flags.t = (DIA_SE_RX_FLAGS(ent)).t;
                        hdr.hh = DIA_SE_RX_HH(ent);
                        hdr.ee = DIA_SE_RX_EE(ent);
                    }

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
                            DIA_SE_CLIENTID(ent)  = gCmd->getClientId();

                            DIA_SE_MSG_STATUS(ent)   = ANS_SND_TO_PEER;	

                            if (ret == FSM_STATE_UPDATE)
                            {
                                if (SESSION_TABLE->ModifyEntry(ent,
                                            (ITS_OCTET *)sessionId,
                                            strlen((const char*)sessionId))
                                        == ITS_SUCCESS)
                                {
                                    DT_DBG(("Succesfully Updated Entry"));
                                    // Replicate session info
                                    if( (SessionTable::replicateSessions) &&
                                            (SessionTable::sessUpdateCbk!= NULL))
                                    {
                                        SessionTable::sessUpdateCbk((char *)sessionId,ent);
                                    }

                                }
                            }
                            //SESSION_TABLE->Unlock();

                            if( (DIA_SE_MESSAGES_PENDING(ent)==true) && (DiaMsgRouter::RepostPendingMessageOfSession(ent,(ITS_OCTET *)sessionId)==ITS_SUCCESS) )
                            {return ret;}
                            break;
                    }
                }
                break;
            }
        case STATELESS_SERVER_AUTH_PXY_FSM:
            {
                DT_DBG(("Stateless Proxy Server Session"));
                /*	
                    if (DIA_SE_MSG_STATUS(ent) == WAIT_ANS_FROM_APP)
                    {
                    DT_DBG(("Proxy Answer received from Peer."));
                    DIA_SE_MSG_STATUS(ent)   = ANS_SND_TO_PEER;
                    }
                    else if (gCmd->isError())
                    {
                    DT_DBG(("Proxy Error Answer received from App."));
                    DIA_SE_MSG_STATUS(ent)   = ANS_SND_TO_PEER;
                    }
                    else*/
                if( (DIA_SE_MSG_STATUS(ent) != WAIT_ANS_FROM_APP) && (!gCmd->isError()))
                { 
                    if (DIA_SE_MSG_STATUS(ent) == WAIT_REQ_FROM_APP)
                    {
                        /**
                         * Send Error response as message received is Invalid.
                         */
                        DT_ERR(("Message received not proper," \
                                    " Sending error response"));

                        DIA_HDR &hdr = (DIA_HDR&)gCmd->getHeader();
                        hdr.hh = DIA_SE_RX_HH(ent);
                        hdr.ee = DIA_SE_RX_EE(ent);
                        hdr.flags = DIA_SE_RX_FLAGS(ent);
                        hdr.appId =  DIA_SE_APP_ID(ent);
                    }
                    DIA_SE_CLIENTID(ent) = gCmd->getClientId();
                    DT_ERR(("Invalid Answer received from App. Discarding..."));
                    DT_DBG(("Sending Error indication to Application"));
                    ret = DiaErrHandler::SendErrorResponse(ent, gCmd);
                    return ret; 
                }   

                DIA_BASE_CMD *msg = NULL;
                DiaUtils::GetCmdFromEvent(&msg, &ev.GetEvent());
                //Fixing - Parse Warning - Decleration Hides existing parameter
                DIA_BASE_CMD *lcmd = (DIA_BASE_CMD *)msg;

                if (msg->getAuthSessionState() &&
                        (msg->getAuthSessionState()->value() ==
                         AuthSessionState::NO_STATE_MAINTAINED))
                {
                    DIA_HDR &hdr = (DIA_HDR &)msg->getHeader();
                    hdr.flags.p = (DIA_SE_RX_FLAGS(ent)).p;
                    hdr.flags.t = (DIA_SE_RX_FLAGS(ent)).t;
                    hdr.hh = DIA_SE_RX_HH(ent);
                    hdr.ee = DIA_SE_RX_EE(ent);

                    if (!gCmd->isError())
                    {
                        /* Validate the ResultCode for Stateless Agents */
                        DiaUtils::IsResultCodeModified(gCmd, ent);
                    }

                    if (DiaMsgRouter::SendCmdToPeer(DIA_SE_PEER_INST(ent),
                                &hdr,
                                lcmd) != ITS_SUCCESS)
                    {
                        DT_ERR(("Failed to Send To Peer"));
                        return (ITS_ESENDFAIL);
                    }

                    DIA_SE_MSG_STATUS(ent)	 = ANS_SND_TO_PEER;
                    if( (DIA_SE_MESSAGES_PENDING(ent)==true) && (DiaMsgRouter::RepostPendingMessageOfSession(ent,(ITS_OCTET *)sessionId)==ITS_SUCCESS) )
                    { 
                        return ret;
                    }

                    if ((ret = SESSION_TABLE->RemoveEntry(ent,
                                    (ITS_OCTET *)sessionId,
                                    strlen((const char*)sessionId)))
                            != ITS_SUCCESS)
                    {
                        DT_ERR(("Failed to remove session Entry %d", ret));
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
                    DIA_SE_CLIENTID(ent)  = msg->getClientId();


                    DIA_SE_MSG_STATUS(ent)	 = ANS_SND_TO_PEER;

                    if (ret == FSM_STATE_UPDATE)
                    {
                        if (SESSION_TABLE->ModifyEntry(ent,
                                    (ITS_OCTET *)sessionId,
                                    strlen((const char*)sessionId)) != ITS_SUCCESS)
                        {
                            DT_ERR(("Failed to update Entry"));
                        }
                        else
                        {
                            // Replicate session info
                            if( (SessionTable::replicateSessions) &&
                                    (SessionTable::sessUpdateCbk!= NULL))
                            {
                                SessionTable::sessUpdateCbk((char *)sessionId,ent);
                            }
                        }
                    }

                    if( (DIA_SE_MESSAGES_PENDING(ent)==true) && (DiaMsgRouter::RepostPendingMessageOfSession(ent,(ITS_OCTET *)sessionId)==ITS_SUCCESS) )
                    {
                        return ret;
                    }
                }
                break;
            }
        default:
            DT_ERR(("Invalid SM %d\n", DIA_SE_FSM_TYPE(ent)));
            break;
    }
    return ret;
}

    int 
DiaProxyHandler::HandleReqMessage(DIA_BASE_CMD *cmd, its::Event &ev)
{
    int ret = ITS_SUCCESS, errCode = 0;
    DIA_BASE_CMD *gCmd = (DIA_BASE_CMD *)cmd;
    ITS_USHORT trInst = ITS_GET_CTXT(ev.GetData());

    ITS_Event pEvt;
    ITS_OCTET data[ITS_DIA_PTR_DATA_LEN];

    pEvt.SetSource(ev.GetSource());

    /* Set the Transport Instance */
    ITS_SET_CTXT(data, trInst);

    /* Copy in the Pointer address */
    memcpy(&data[sizeof(ITS_USHORT)], &cmd, sizeof(ITS_ULONG));
    pEvt.SetData(data, ITS_DIA_PTR_DATA_LEN);

    /**
     * Verifying whether the message is proxiable.
     * Fix for issue 702 in whizible raised during unit
     * testing for proxy feature.
     */
    if (!cmd->isProxyable())
    {
        DT_ERR(("Non-Proxiable message received for Agent"));
        errCode = ITS_DIA_UNABLE_TO_DELIVER;
    }

    /**
     * Check for loops in RouteRecordAVP for Proxy
     */
    if (DiaMsgRouter::IsLoopDetected(gCmd))
    {
        DT_ERR(("Loop detected for the message"));
        errCode = ITS_DIA_LOOP_DETECTED;
    }


    if (errCode)
    { 
        ret = DiaErrHandler::HandleError(trInst, gCmd,
                SEND_ERROR_TO_PEER,
                errCode);
        /*update the stats for number of request message received for dictionary
         * id*/
        DIA_INC_INTERFACE_TOTAL_REQUEST_RECEIVED(gCmd->GetDictId(),(gCmd->getCommandCode()));
        if (cmd)
        {
            delete cmd;
            cmd = NULL;
            return ret;
        }
    }

    /* 
     * Accounting Message submit to Accounting statemachine
     * by default submit to Auth statemachine
     */
    switch (gCmd->getCommandCode())
    {
        case DIA_MSG_AC:
            ret = HandleProxyAcctReqMsg(cmd, pEvt);
            break;
        default:

            ret = HandleProxyAuthReqMsg(cmd, pEvt);
    }

    return ret;
}

    int 
DiaProxyHandler::HandleProxyAuthReqMsg(DIA_BASE_CMD *&cmd, its::Event &ev)
{
    int ret;
    DiaSocketTransport *tr = NULL;
    ITS_USHORT trInst = ITS_GET_CTXT(ev.GetData());
    DIA_BASE_CMD *msg = (DIA_BASE_CMD *)cmd;
    std::string sessionId;
    ITS_USHORT peerInstance = 0;
    PEER_ENTRY *peer = NULL;
    ITS_NODE_STATE state;
    DIA_GEN_CMD *ce = NULL;
    ITS_UINT dRlen = 0;
    ITS_CHAR *destRlm = NULL;


    DT_DBG(("HandleProxyAuthReqMessage"));

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
        bool mod = true;

        if (SESSION_TABLE->FindEntry(e,
                    (ITS_OCTET *)sessionId.c_str(),
                    strlen(sessionId.c_str())) != ITS_SUCCESS)
        {
            DT_DBG(("Entry Not found "));

            /**
             * Memsetting the session entry variable
             */
            memset(&ent, 0, sizeof(SESSION_ENTRY));

            /* Session Termination, Abort Session and Re-Auth Requests
               need to have an existing session context in db
               */

            /*update the stats for number of request message received for dictionary
             * id*/
            DIA_INC_INTERFACE_TOTAL_REQUEST_RECEIVED(msg->GetDictId(),(msg->getCommandCode()));

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

            bool isStateless = false;

            /* This is the first inbound request */
            /* If the Message is to be proxied set the flags */
            DIA_SE_IS_AGENT(&ent)  = true;
            DIA_SE_AGENT_TYPE(&ent)= ITS_DIA_PROXY;
            DIA_SE_FSM_TYPE(&ent) = STATEFUL_SERVER_AUTH_PXY_FSM;
            DIA_SE_MSG_STATUS(&ent) = WAIT_REQ_FROM_APP;

            if (msg->getAuthSessionState())
            {
                if (msg->getAuthSessionState()->value() ==
                        AuthSessionState::NO_STATE_MAINTAINED)
                {
                    isStateless = true;
                    DIA_SE_FSM_TYPE(&ent) = STATELESS_SERVER_AUTH_PXY_FSM;
                }
            }
            SESSION_ENTRY *pEntry = &ent;

            DiaTracer::SessTraceCheckAndLog(msg, pEntry, sessionId.c_str(), trInst);

            ret = SESSION_TABLE->InsertAuthSession(msg, sessionId.c_str(), 
                    pEntry, ev, isStateless); 
            return ret;

        }
        else
        {
            //SESSION_TABLE->Lock();
            // if( ( DIA_SE_MSG_STATUS(e) != ANS_SND_TO_PEER) &&(ret =DiaProxyHandler::CheckIfMsgTobeQueued(msg,e,ev.GetEvent())) == ITS_SUCCESS)
            if( ( DIA_SE_MSG_STATUS(e) != ANS_SND_TO_PEER) &&(ret =DiaMsgRouter::CheckIfMsgTobeQueued(msg,e,ev.GetEvent())) == ITS_SUCCESS)
            { 

                delete cmd;
                cmd = NULL;
                //SESSION_TABLE->Unlock();
                return ret;
            }
            /*update the stats for number of request message received for dictionary
             * id*/
            DIA_INC_INTERFACE_TOTAL_REQUEST_RECEIVED(msg->GetDictId(),(msg->getCommandCode()));
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
            /*
             * Received a new request on existing session for the
             * proxy agent then set the proxy message status
             */
            DIA_SE_MSG_STATUS(&ent)   = REQ_RCV_FROM_PEER;

            DT_DBG(("Found Session Context for :: %s", sessionId.c_str()));

            DiaTracer::SessTraceCheckAndLog(msg, e, sessionId.c_str(), trInst);
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
            case STATEFUL_SERVER_AUTH_PXY_FSM:
                {
                    DT_DBG(("Stateful Proxy Server"));
                    DT_DBG(("Proxy Request Received from Peer."));

                    switch (msg->getCommandCode())
                    {
                        case DIA_MSG_ST:
                            DIA_SE_EVT_TYPE(e) = AUTH_SESSION_EVT_RX_STR;
                            DIA_SE_MSG_STATUS(e)   = WAIT_REQ_FROM_APP;
                            ret = statefulServerAuthFsm.SubmitToSM(e, &ev.GetEvent());
                            break;
                        case DIA_MSG_AS:
                            DIA_SE_EVT_TYPE(e) = AUTH_SESSION_EVT_REQUEST_ACCESS;
                            DIA_SE_MSG_STATUS(e)   = WAIT_REQ_FROM_APP;
                            ret = statefulServerAuthFsm.SubmitToSM(e, &ev.GetEvent());
                            break;
                        default:
                            if ( (DIA_SE_MSG_STATUS(e) == ANS_SND_TO_PEER) || (msg->getHeader().flags.t == ITS_DIA_MASK_FLAG ) )
                            {  
                                DIA_SE_EVT_TYPE(e) = AUTH_SESSION_EVT_REQUEST_ACCESS;
                                DIA_SE_MSG_STATUS(e)   = WAIT_REQ_FROM_APP;

                                //mod = false;

                                ret = statefulServerAuthFsm.SubmitToSM(e, &ev.GetEvent());
                            }
                            else
                            {
                                ret = DiaErrHandler::HandleError(trInst, msg,
                                        SEND_ERROR_TO_PEER,
                                        ITS_DIA_UNKNOWN_SESSION_ID);
                                //SESSION_TABLE->Unlock();
                                delete msg;
                                cmd = NULL;
                                return ret;
                            }
                            if (mod && SESSION_TABLE->ModifyEntry(e,
                                        (ITS_OCTET *)sessionId.c_str(),
                                        sessionId.size())
                                    != ITS_SUCCESS)
                            {
                                DT_ERR(("Failed to update session context"));
                            }
                            //SESSION_TABLE->Unlock();
                            break;
                    }
                }
                break;
            case STATELESS_SERVER_AUTH_PXY_FSM:
                {
                    DT_DBG(("Stateless Proxy Server"));
                    DT_DBG(("Proxy Request Received from Peer."));
                    DIA_SE_MSG_STATUS(e)   = WAIT_REQ_FROM_APP;

                    /* Stateless Server Auth FSM */
                    switch (msg->getCommandCode())
                    {
                        case DIA_MSG_ST:
                        case DIA_MSG_AS:
                            DT_ERR(("Received STR/ASR For Stateless Proxy Server Session" \
                                        ". Discarding Message..."));
                            /* Good Indication to free the entry though */
                            if (SESSION_TABLE->RemoveEntry(e, (ITS_OCTET *)sessionId.c_str(),
                                        sessionId.size()) != ITS_SUCCESS)
                            {
                                DT_ERR(("Failed to free session context"));
                            }

                            break;
                        default:

                            if( msg->getHeader().flags.t == ITS_DIA_MASK_FLAG )
                            {
                                SESSION_TABLE->ReStartAuthTimers(e,msg);
                                ret = DiaMsgRouter::SendMsgToApp(e, &ev.GetEvent());
                            }
                            else
                            {
                                DT_ERR(("Received new request on existing Stateless Proxy Server" \
                                            "Session. Discarding Message..."));

                                ret = DiaErrHandler::HandleError(trInst, msg,
                                        SEND_ERROR_TO_PEER,
                                        ITS_DIA_UNABLE_TO_DELIVER);
                                delete cmd;
                                cmd = NULL;
                                return ret;
                            }

                            break;
                    }
                }
                break;
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
/**
 * upstream
 */
    int
DiaProxyHandler::HandleProxyAcctReqMsg(DIA_BASE_CMD *&cmd, its::Event &ev)
{
    int ret;
    DiaSocketTransport *tr = NULL;
    ITS_USHORT trInst = ITS_GET_CTXT(ev.GetData());
    DIA_BASE_CMD *msg = (DIA_BASE_CMD *)cmd;
    std::string sessionId;
    ITS_USHORT peerInstance = 0;
    PEER_ENTRY *peer = NULL;
    ITS_NODE_STATE state;
    DIA_GEN_CMD *ce = NULL;
    ITS_UINT dRlen = 0;
    ITS_CHAR *destRlm = NULL;

    DT_DBG(("HandleProxyAcctReqMessage"));

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
                    strlen(sessionId.c_str())) != ITS_SUCCESS)
        {
            DT_DBG(("Entry Not found "));

            bool isStateless = false;
            /**
             * Memsetting the session entry variable
             */

            memset(&ent,0,sizeof(SESSION_ENTRY));

            /*update the stats for number of request message received for dictionary
             * id*/
            DIA_INC_INTERFACE_TOTAL_REQUEST_RECEIVED(msg->GetDictId(),(msg->getCommandCode()));
            //in case of proxy 
            DIA_SE_IS_AGENT(&ent)     = true;
            DIA_SE_AGENT_TYPE(&ent)   = ITS_DIA_PROXY;
            DIA_SE_MSG_STATUS(&ent)   = WAIT_REQ_FROM_APP;

#if 0           
            if (!(msg->getAccountingRealtimeRequired()) ||
                    (msg->getAccountingRealtimeRequired()->value() !=
                     AccountingRealtimeRequired::DELIVER_AND_GRANT))
            {
                DT_DBG(("AccountingRealtimeRequired != DELIVER_AND_GRANT"));

                isStateless = true;
                DIA_SE_ACC_FSM_TYPE(&ent) = STATELESS_SERVER_ACCT_PXY_FSM;
            }
            else
            {
                DIA_SE_ACC_FSM_TYPE(&ent) = STATEFUL_SERVER_ACCT_PXY_FSM;
            }
#endif
            //Fix for 113, to make the accounting request stateful, so that DRE maintain the session

            DIA_SE_ACC_FSM_TYPE(&ent) = STATEFUL_SERVER_ACCT_PXY_FSM;//for else part

            SESSION_ENTRY *pEntry = &ent;

            DiaTracer::SessTraceCheckAndLog(msg, pEntry, sessionId.c_str(), trInst);

            ret = SESSION_TABLE->InsertAcctSession(msg, sessionId.c_str(), 
                    pEntry, ev, isStateless); 
            return ret;

        }
        else
        {
            if( ( DIA_SE_MSG_STATUS(e) != ANS_SND_TO_PEER) && (ret =DiaMsgRouter::CheckIfMsgTobeQueued(msg,e,ev.GetEvent())) == ITS_SUCCESS)
            { 

                delete cmd;
                cmd = NULL;
                return ret;
            }
            /*update the stats for number of request message received for dictionary
             * id*/
            DIA_INC_INTERFACE_TOTAL_REQUEST_RECEIVED(msg->GetDictId(),(msg->getCommandCode()));
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
                //DIA_SE_ACC_FSM_TYPE(e) = STATELESS_SERVER_ACCT_FSM;

                DIA_SE_ACC_FSM_TYPE(e) = STATELESS_SERVER_ACCT_PXY_FSM;

            }
            DT_DBG(("Found Session Context for :: %s", sessionId.c_str()));

            DiaTracer::SessTraceCheckAndLog(msg, e, sessionId.c_str(), trInst);
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
            case STATEFUL_SERVER_ACCT_PXY_FSM:
                {
                    DT_DBG(("Stateful Proxy Server"));
                    /**
                     * Update proxy message status, to track the message
                     */
                    if (DIA_SE_MSG_STATUS(e) == ANS_SND_TO_PEER ||
                            DIA_SE_MSG_STATUS(e) == REQ_RCV_FROM_PEER)
                    {
                        DT_DBG(("Proxy Request Received from Peer."));
                        DIA_SE_MSG_STATUS(e)   = WAIT_REQ_FROM_APP;
                    }
                    else
                    {
                        ret = DiaErrHandler::HandleError(trInst, msg,
                                SEND_ERROR_TO_PEER,
                                ITS_DIA_UNABLE_TO_DELIVER);
                        return ret;
                    }

                    DIA_SE_EVT_TYPE(e) = ACCT_SESSION_EVT_REQUEST_ACCESS;
                    ret = statefulServerAcctFsm.SubmitToSM(e, &ev.GetEvent());
                    if (SESSION_TABLE->ModifyEntry(e, (ITS_OCTET *)sessionId.c_str(),
                                sessionId.size()) != ITS_SUCCESS)
                    {
                        DT_ERR(("Failed to update session context"));
                    }
                    break;
                }
            case STATELESS_SERVER_ACCT_PXY_FSM:
                {
                    DT_DBG(("Stateless Proxy Server"));
                    /**
                     * Update proxy message status, to track the message
                     */
                    if (DIA_SE_MSG_STATUS(e) == REQ_RCV_FROM_PEER)
                    {
                        DT_DBG(("Proxy Request Received from Peer."));
                        DIA_SE_MSG_STATUS(e)   = WAIT_REQ_FROM_APP;
                    }

                    ret = DiaMsgRouter::SendMsgToApp(e, &ev.GetEvent());
                    if (ret != ITS_SUCCESS)
                    {
                        DT_ERR(("Failed to SendMsgToApp"));
                        ret = DiaErrHandler::HandleError(trInst, msg,
                                SEND_ERROR_TO_PEER,
                                ITS_DIA_UNABLE_TO_DELIVER);
                        return ret;
                    }

                    /**
                     * Modifying the entry for the message status
                     */ 
                    if (SESSION_TABLE->ModifyEntry(e, (ITS_OCTET *)sessionId.c_str(),
                                sessionId.size()) != ITS_SUCCESS)
                    {
                        DT_ERR(("Failed to update session context"));
                    }
                    break;
                }
            default:
                DT_DBG((" Invalid FSM Type"));
                break;
        }
    }
    else
    {
        DT_ERR(("Application Level Message without SessionId"));
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
DiaProxyHandler::HandleProxyAuthAnsMsg(DIA_BASE_CMD *&cmd, 
        SESSION_ENTRY *ent, its::Event &ev)
{
    int ret = ITS_SUCCESS;
    ITS_UINT resultCode = ITS_DIA_SUCCESS;
    ITS_USHORT trInst = ITS_GET_CTXT(ev.GetData());
    DIA_BASE_CMD *msg = (DIA_BASE_CMD *)cmd;
    DIA_HDR &header = (DIA_HDR&)msg->getHeader();
    std::string sessionId;

    DT_DBG(("HandleLocalAuthAnsMessage"));

    /* If Answer is received from the Peer and it doesn't
       contain resultCode, we treat it as succesfull indication
       that the User is Authorized
       */
    if(msg->getResultCode())
    {
        resultCode = msg->getResultCode()->value();
    }

    sessionId = msg->getSessionId()->value();
    //SESSION_TABLE->Lock();
    /* states based on existence (or lack of)
       Auth-Session-State AVP
       If AuthSessionState AVP is present and
       the value is NO_STATE_MAINTAINED then it's
       Stateless Server else Stateful Server
       */
    DT_DBG(("FSM Type = %s", STATE_MACHINE_TYPE_TO_TEXT(DIA_SE_FSM_TYPE(ent))));
    switch (DIA_SE_FSM_TYPE(ent))
    {
        case STATEFUL_SERVER_AUTH_PXY_FSM:
            {
                DT_DBG(("Stateful Proxy Server"));
                /**
                 * Relaxing the Proxy msg status checks for the ASA/STA
                 */
                if (DIA_SE_MSG_STATUS(ent) == WAIT_ANS_FROM_PEER ||
                        (msg->getCommandCode() ==  DIA_MSG_AS) ||
                        (msg->getCommandCode() == DIA_MSG_ST))
                {
                    DT_DBG(("Proxy Answer received from Peer."));
                    DIA_SE_MSG_STATUS(ent)   = WAIT_ANS_FROM_APP;
                }
                else
                {
                    DT_ERR(("Invalid Message received. Discarding..."));
                    return !(ITS_SUCCESS);
                }
                DIA_HDR &hdr = (DIA_HDR&)msg->getHeader();

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

                    case DIA_MSG_ST:
                        if (header.hh == DIA_SE_RX_HH(ent))
                        {
                            DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_RX_STA;
                            break;
                        }
                    default:
                        DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_RX_SSAA_AGENT;
                        break;
                }

                hdr.hh = DIA_SE_RX_HH(ent);
                /**
                 * Added Modify entry to update the Proxy message status.
                 */ 
                //Warning Fix - suggest parentheses around assignment used as truth value
                if ((ret = SESSION_TABLE->ModifyEntry(ent,
                                (ITS_OCTET *)sessionId.c_str(),
                                sessionId.size()))
                        != ITS_SUCCESS)
                {
                    DT_ERR(("Failed to update Session Context"));
                }
                ret = statefulServerAuthFsm.SubmitToSM(ent, &ev.GetEvent());

                //SESSION_TABLE->Unlock();
                break;
            }
        case STATELESS_SERVER_AUTH_PXY_FSM:
            {
                /* Stateless Server Auth FSM */
                DT_DBG(("Stateless Proxy Server"));
                if (DIA_SE_MSG_STATUS(ent) == WAIT_ANS_FROM_PEER)
                {
                    DT_DBG(("Proxy Answer received from Peer."));
                    DIA_SE_MSG_STATUS(ent)   = WAIT_ANS_FROM_APP;
                }
                else
                {
                    DT_DBG(("Invalid Message received. Discarding..."));
                    return !(ITS_SUCCESS);
                }

                DIA_HDR &hdr = (DIA_HDR&)msg->getHeader();
                hdr.hh = DIA_SE_RX_HH(ent);
                DIA_SE_EVT_TYPE(ent) = AUTH_SESSION_EVT_RX_SSAA_AGENT;
                /**
                 * Added Modify entry to update the Proxy message status.
                 */
                //Warning Fix - suggest parentheses around assignment used as truth value
                if ((ret = SESSION_TABLE->ModifyEntry(ent,
                                (ITS_OCTET *)sessionId.c_str(),
                                sessionId.size()))
                        != ITS_SUCCESS)
                {
                    DT_ERR(("Failed to update Session Context"));
                }
                ret = DiaMsgRouter::SendMsgToApp(ent, &ev.GetEvent());

                break;
            }
        default:
            DT_ERR(("Invalid FSM Type"));
            delete cmd;
            cmd = NULL;
            return ret;
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
    return (ITS_SUCCESS);
}

    int
DiaProxyHandler::HandleProxyAcctAnsMsg(DIA_BASE_CMD *&cmd, 
        SESSION_ENTRY *ent, its::Event &ev)
{
    int ret = ITS_SUCCESS;
    DIA_BASE_CMD *msg = (DIA_BASE_CMD *)cmd;
    std::string sessionId;
    ITS_UINT resultCode = ITS_DIA_SUCCESS;
    ITS_UINT recType =0;

    if (msg->getAccountingRecordType())
    {
        recType = msg->getAccountingRecordType()->value();
    }

    DT_DBG(("HandleLocalAcctAnsMessage"));

    DT_DBG(("FSM Type = %s",
                STATE_MACHINE_TYPE_TO_TEXT(DIA_SE_FSM_TYPE(ent))));

    switch (DIA_SE_ACC_FSM_TYPE(ent))
    {
        case STATEFUL_SERVER_ACCT_PXY_FSM:
            {
                /* Stateful Server ACCT FSM */
                DT_DBG(("Stateful Proxy Server"));
                if (DIA_SE_MSG_STATUS(ent) == WAIT_ANS_FROM_PEER)
                {
                    DT_DBG(("Proxy Answer received from Peer."));
                    DIA_SE_MSG_STATUS(ent)   = WAIT_ANS_FROM_APP;
                }
                else
                {
                    DT_ERR(("Invalid Message received. Discarding..."));
                    return !(ITS_SUCCESS);
                }

                DIA_HDR &hdr = (DIA_HDR&)msg->getHeader();
                switch(recType)
                {
                    case AccountingRecordType::EVENT_RECORD:
                        DT_DBG(("Accounting Event Answer"));
                        DIA_SE_EVT_TYPE(ent) = ACCT_SESSION_EVT_ACCESS_RX_AGENT;
                        break;
                    case AccountingRecordType::START_RECORD:
                        DT_DBG(("Accounting Start Answer"));
                        DIA_SE_EVT_TYPE(ent) = ACCT_SESSION_EVT_ACCESS_RX_AGENT;
                        break;
                    case AccountingRecordType::INTERIM_RECORD:
                        DT_DBG(("Accounting Interim Answer"));
                        DIA_SE_EVT_TYPE(ent) = ACCT_SESSION_EVT_ACCESS_RX_AGENT;
                        break;
                    case AccountingRecordType::STOP_RECORD:
                        DT_DBG(("Accounting Stop Answer"));
                        if (hdr.hh == DIA_SE_RX_HH(ent))
                        {
                            if (resultCode >= ITS_DIA_SUCCESS_MIN_RANGE &&
                                    resultCode <= ITS_DIA_SUCCESS_MAX_RANGE)
                            {
                                DT_DBG(("Successful Accounting Answer Received"));
                                DIA_SE_EVT_TYPE(ent) = ACCT_SESSION_EVT_RX_ACA_OK;
                            }
                            else
                            {
                                DT_WRN(("Failed Accounting Answer Received"));
                                DIA_SE_EVT_TYPE(ent) = ACCT_SESSION_EVT_RX_ACA_FAIL;
                            }
                        }
                        else
                        {
                            DIA_SE_EVT_TYPE(ent) = ACCT_SESSION_EVT_ACCESS_RX_AGENT;
                        }
                        break;
                    default:
                        DT_WRN(("Invalid Accounting Record Type, discarding Answer"));
                        return ret;
                }

                hdr.hh = DIA_SE_RX_HH(ent);
                /**
                 * Added Modify entry to update the Proxy message status.
                 */
                //Warning Fix - suggest parentheses around assignment used as truth value
                if ((ret = SESSION_TABLE->ModifyEntry(ent,
                                (ITS_OCTET *)sessionId.c_str(),
                                sessionId.size()))
                        != ITS_SUCCESS)
                {
                    DT_ERR(("Failed to update Session Context"));
                }
                ret = statefulServerAcctFsm.SubmitToSM(ent, &ev.GetEvent());

                break;
            }
        case STATELESS_SERVER_ACCT_PXY_FSM:
            {
                /* Stateless Server ACCT FSM */
                DT_DBG(("Stateless Proxy Server"));
                if (DIA_SE_MSG_STATUS(ent) == WAIT_ANS_FROM_PEER)
                {
                    DT_DBG(("Proxy Answer received from Peer."));
                    DIA_SE_MSG_STATUS(ent)   = WAIT_ANS_FROM_APP;
                }
                else
                {
                    DT_ERR(("Invalid Message received. Discarding..."));
                    return !(ITS_SUCCESS);
                }

                DIA_HDR &hdr = (DIA_HDR&)msg->getHeader();
                hdr.hh = DIA_SE_RX_HH(ent);
                /**
                 * Added Modify entry to update the Proxy message status.
                 */
                //Warning Fix - suggest parentheses around assignment used as truth value
                if ((ret = SESSION_TABLE->ModifyEntry(ent,
                                (ITS_OCTET *)sessionId.c_str(),
                                sessionId.size()))
                        != ITS_SUCCESS)
                {
                    DT_ERR(("Failed to update Session Context"));
                }
                ret = DiaMsgRouter::SendMsgToApp(ent, &ev.GetEvent());

                break;
            }
        default:
            DT_ERR(("Invalid FSM Type"));
            delete cmd;
            cmd = NULL;
            return ret;
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

    return (ITS_SUCCESS);
}

#if 0
int DiaProxyHandler::CheckIfMsgTobeQueued(DIA_BASE_CMD *msg,SESSION_ENTRY *ent,ITS_EVENT &ev)
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

        if( INCOMING_MESSAGEQ->InsertMsgEvent(DIA_SE_SINDX(ent),DIA_SE_MESSAGES_PENDING(ent),lEvent) == ITS_SUCCESS)
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

ITS_INT DiaProxyHandler::RepostPendingMessageOfSession(SESSION_ENTRY* aSessEntry,ITS_OCTET * sessionId)
{
    DT_DBG(("ENTER RepostPendingMessageOfSession"));

    ITS_EVENT *lEvent=NULL;
    ITS_INT retVal = (!ITS_SUCCESS);

    retVal=INCOMING_MESSAGEQ->GetMsgEvent(DIA_SE_SINDX(aSessEntry),DIA_SE_MESSAGES_PENDING(aSessEntry),&lEvent);
    /*if(  (!DIA_SE_MESSAGES_PENDING(aSessEntry)) )
      {
      INCOMING_MESSAGEQ->RemoveMsgEventEntry(DIA_SE_SINDX(aSessEntry));	
      DT_ERR(("Session Queue is empty , -RemoveMsgEventEntry-"));
      }*/

    //SESSION_TABLE->ModifyEntry(aSessEntry, (ITS_OCTET *)sessionId,strlen((const char*)sessionId));  
    if(NULL != lEvent)
    {
        lEvent->src = DIA_NET_INST;
        retVal=DiaUtils::PutEventReference(DIASTACK_TQ_INST, lEvent);
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
#endif
