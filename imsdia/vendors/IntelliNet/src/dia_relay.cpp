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
 * LOG: $Log: dia_relay.cpp,v $
 * LOG: Revision 1.5.20.5.4.3.4.1  2013/09/10 08:36:39  ncshivakumar
 * LOG: RFC6733 Changes
 * LOG:
 * LOG: Revision 1.5.20.5.4.3  2013/04/18 13:38:24  jsarvesh
 * LOG: changes done for interface stats increment for req in message
 * LOG:
 * LOG: Revision 1.5.20.5.4.2  2013/04/12 04:18:08  vsarath
 * LOG: Logs improvement
 * LOG:
 * LOG: Revision 1.5.20.5.4.1  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 1.5.20.5  2012/12/17 05:36:47  mallikarjun
 * LOG: Bug 650 static routing for relay
 * LOG:
 * LOG: Revision 1.5.20.4  2012/11/20 17:39:44  pramana
 * LOG: Merged from CMAPI branch for 212-07 release
 * LOG:
 * LOG: Revision 1.5.44.2  2012/11/20 10:31:24  rgovardhan
 * LOG: merge from 00 Nov20Rel
 * LOG:
 * LOG: Revision 1.5  2009/03/19 12:37:16  nvijikumar
 * LOG: Global instance is created for the Class ITSDiaConfig to avoid function
 * LOG: call overhead as ITSDiaConfig::GetITSDiaConfig() was called max time
 * LOG:
 * LOG: Revision 1.4  2009/02/19 13:56:39  ssaxena
 * LOG: Fix for the whizible issue Id 1478. Relay failed to send
 * LOG: STR message to server.
 * LOG:
 * LOG: Revision 1.3  2009/01/06 12:55:27  rajeshak
 * LOG: Proper debug print
 * LOG:
 * LOG: Revision 1.2  2008/12/12 18:30:47  rajeshak
 * LOG: Lightweight Decode for base AVPS
 * LOG: New Command class is introduced (BaseCommand)
 * LOG:
 * LOG: Revision 1.1  2008/12/07 09:57:43  rajeshak
 * LOG: Added new file to separate the functionality of relay from main stack.
 * LOG:
 *
 ****************************************************************************/

#include <dia_msg_router.h>
#include <dia_relay.h>
#include <dia_utils.h>
#include <dia_session_auth_fsm.h>
#include <dia_stack.h>
#include <DiameterDictionaryStats.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
using namespace diameter;
using namespace diameter::base;
#endif


int DiaRelayHandler::HandleReqMessage(ITS_USHORT trInst, 
                                    DIA_BASE_CMD *&cmd, REALM_ENTRY *realm )
{

    /**
     * Processing Message here in case of relay
     */
    int errCode = 0;
    int ret = ITS_SUCCESS;
    ITS_USHORT peerInstance = 0;
    ITS_BOOLEAN isRlyAdv = ITS_FALSE;
    DIA_BASE_CMD* gCmd = (DIA_BASE_CMD*)cmd;

    std::string sessionId;

    /*update the stats for number of request message received for dictionary
    * id*/
    DIA_INC_INTERFACE_TOTAL_REQUEST_RECEIVED(gCmd->GetDictId(),(gCmd->getCommandCode()));

    /**
     * Verifying whether the message is proxiable.
     * Fix for issue 702 in whizible raised during unit
     * testing for relay feature.
     */
    if (!cmd->isProxyable())
    {
        DT_ERR(("Non-Proxiable message received for Agent"));
        errCode = ITS_DIA_UNABLE_TO_DELIVER;
    }

    /**
     * Check for loops in RouteRecordAVP for relay
     */
    if (DiaMsgRouter::IsLoopDetected(gCmd))
    {
        DT_ERR(("Loop detected for the message"));
        errCode = ITS_DIA_LOOP_DETECTED;
    }

    if (errCode)
    {
        DT_ERR(("HandleReqMessage::Sending back Error Response"));

        ret = DiaErrHandler::HandleError(trInst, gCmd,
                                   SEND_ERROR_TO_PEER,
                                   errCode);
        if (cmd)
        {
            delete cmd;
            cmd = NULL;
            return ret;
        }
    }

    if(gCmd->getSessionId())
    {
        sessionId = gCmd->getSessionId()->value();
    }

    DT_DBG(("SessionId = %s", sessionId.c_str()));

    SESSION_ENTRY ent;
    SESSION_ENTRY *e = NULL;

    /**
     * Finding and entry and if found then check whether the session is relay
     * or proxy. If Proxy is found send the ASR and RAR to the state machine
     * else send error to peer for relay. partial fix for the issue 869
     * in whizible.
     */
    if (SESSION_TABLE->FindEntry(e,
                             (ITS_OCTET *)sessionId.c_str(),
                             strlen(sessionId.c_str())) == ITS_SUCCESS)
    {
        DT_DBG(("Session Entry found "));

        /**
         * Fix for Issue: 1478 
         * dont generate error incase agent is waiting for ASA and
         * received a STR before getting a ASA.
         */
        if(DIA_SE_EVT_TYPE(e) != AUTH_SESSION_EVT_RX_ASR)
        {
            /**
             * If the session already exists then check whether it is a
             * proxy session and also if the request received is ASR or
             * RAR. If yes then send the message to state machine else
             * print error traces.
             */

            DT_ERR(("Failed to process Request. Session already exists."));

            ret = DiaErrHandler::HandleError(trInst, gCmd,
                                             SEND_ERROR_TO_PEER,
                                             ITS_DIA_UNABLE_TO_DELIVER);
            if (cmd)
            {
                delete cmd;
                cmd = NULL;
                return ret;
            }
        }
    }
    else
    {
        DT_DBG(("Entry Not found "));
        memset(&ent,0,sizeof(SESSION_ENTRY));

        /* This is the first inbound request */
        DIA_SE_RX_FLAGS(&ent)     = gCmd->getHeader().flags;
        DIA_SE_RX_HH(&ent)        = gCmd->getHeader().hh;
        DIA_SE_RX_EE(&ent)        = gCmd->getHeader().ee;
        DIA_SE_PEER_INST(&ent)    = trInst;
        DIA_SE_CLIENTID(&ent)     = 0;
        DIA_SE_FSM_TYPE(&ent)     = RELAY_AGENT_FSM;
        DIA_SE_STYPE(&ent)        = DIA_AUTHORIZATION;

        /* default agent flag is off, set if required */
        DIA_SE_IS_AGENT(&ent)     = ITS_TRUE;
        DIA_SE_AGENT_TYPE(&ent)   = ITS_DIA_RELAY;

        if (gCmd->getCommandCode() == DIA_MSG_AC)
        {
            DIA_SE_STYPE(&ent)        = DIA_ACCOUNTING;
            DIA_SE_ACC_FSM_TYPE(&ent) = RELAY_AGENT_FSM;
        }

        /* Fix for Issue: 1478 - change the evt Type if ASR is received */
        if (gCmd->getCommandCode() == DIA_MSG_AS )
        {
            DIA_SE_EVT_TYPE(&ent)     = AUTH_SESSION_EVT_RX_ASR;
        }

        e = &ent;

        /**
         * Fix for the issue 889 in whizible, where complete processing
         * from the downstream for relay is shifted here for Accounting
         * and Auth Request  message.
         * As per discussion with Ajay and Sarvesh.
         */
        SESSION_TABLE->StartTimer(sessionId.c_str(),
                      AUTH_SESSION_TIMER,
                      itsDiaConfig.GetAuthSessionConfig().GetTimeout(), &ent);
	
        if (SESSION_TABLE->InsertEntry(ent,
                                       (ITS_OCTET *)sessionId.c_str(),
                                       strlen(sessionId.c_str()))
                                       == ITS_SUCCESS)
        {
            DT_DBG(("Created Session Context for %s", sessionId.c_str()));
        }
        else
        {
            DT_CRT(("Failed to create Session Context for %s",
                     sessionId.c_str()));

            SESSION_TABLE->StopTimer(AUTH_SESSION_TIMER, &ent);

            ret = DiaErrHandler::HandleError(trInst, gCmd,
                                            SEND_ERROR_TO_PEER,
                                            ITS_DIA_UNABLE_TO_DELIVER);
            delete cmd;
            cmd = NULL;
            return ret;
        }

        DT_DBG(("Relaying Request message"));

        REALM_ENTRY *realmEntry = NULL;
        /**
         * Relay request processing with requestForwarding first
         */
        if( (ret = DiaMsgRouter::RequestForwarding(cmd, e, peerInstance)) == ITS_SUCCESS)
        {
            DT_DBG(("RequestForwarding via Realm Table succesfull"));

            DIA_SE_LOCAL_HH(&ent)   = ((DIA_BASE_CMD *)cmd)->getHeader().hh;
            DIA_SE_PEER_INST_AGENT(&ent) = peerInstance;
            if (SESSION_TABLE->ModifyEntry(&ent, (ITS_OCTET *)sessionId.c_str(),
                                                  sessionId.size()) == ITS_SUCCESS)
            {
                 DT_DBG(("Succesfully Updated Session Context"));
            }
            DIA_HDR &hdr = (DIA_HDR&)((DIA_BASE_CMD *)cmd)->getHeader();

            ret = DiaMsgRouter::SendCmdToPeer(peerInstance,
                                             &hdr,
                                             cmd);
        }

	if (ret != ITS_SUCCESS)
        {
            DT_DBG(("RequestForwarding Failed - Try Routing using static routing table "));
           /*  Try Routing using static routing table */
            ret = DiaMsgRouter::StaticRouting(cmd,e,peerInstance,NULL);
        }

        
        if (ret != ITS_SUCCESS)
	{
            DT_WRN(("RequestForwarding and StaticRouting both failed, Trying RequestRouting"));
            /* Realm Routing */
            if ((ret = DiaMsgRouter::RequestRouting(cmd, e,
                                           peerInstance,
                                           realmEntry)) != ITS_SUCCESS)
            {
                DT_ERR(("RequestRouting Failed"));
                /**
                 * Send Error response as not able to deliver the messge.
                 */
                ret = DiaErrHandler::HandleError(DIA_SE_PEER_INST(&ent), gCmd,
                                                 SEND_ERROR_TO_PEER,
                                                 ITS_DIA_UNABLE_TO_DELIVER);

                if ((ret = SESSION_TABLE->RemoveEntry(&ent,
                                            (ITS_OCTET *)sessionId.c_str(),
                                            strlen(sessionId.c_str())))
                                            != ITS_SUCCESS)
                {
                    DT_ERR(("Failed to remove session Entry %d", ret));
                }

                delete cmd;
                cmd = NULL;
                return ret;
            }
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

           if( ret == ITS_SUCCESS) 
            {
                DIA_SE_LOCAL_HH(&ent)        = ((DIA_BASE_CMD *)cmd)->getHeader().hh;
                DIA_SE_PEER_INST_AGENT(&ent) = peerInstance;
                if (SESSION_TABLE->ModifyEntry(&ent, (ITS_OCTET *)sessionId.c_str(),
                                              strlen((const char*)sessionId.c_str())) == ITS_SUCCESS)
                {
                     DT_DBG(("Succesfully Updated Session Context"));
                }
                DIA_HDR &hdr = (DIA_HDR&)gCmd->getHeader();

                ret = DiaMsgRouter::SendCmdToPeer(peerInstance,
                                                 &hdr,
                                                 cmd);
            }

        
    }
    return (ret);
}


int DiaRelayHandler::HandleAnsMessage(DIA_BASE_CMD *&cmd, SESSION_ENTRY *ent)
{
    int ret = ITS_SUCCESS;
    DIA_BASE_CMD* msg = (DIA_BASE_CMD*) cmd;
    std::string sessionId;
    if (DIA_SE_AGENT_TYPE(ent) != ITS_DIA_RELAY)
    {
        delete cmd;
        cmd = NULL;
        ret = !ITS_SUCCESS;
        return ret;
    }

    if (msg->getSessionId())
    {
        sessionId = msg->getSessionId()->value();
    }
    /**
     * Verifying whether Hop-by-hop id received in answer is same as
     * stored in the session entry. Fix for the issue 701 raised during
     * unit testing of relay feature.
     */
    DIA_HDR &header = (DIA_HDR&)msg->getHeader();
    if ((DIA_SE_IS_AGENT(ent) && (header.hh != DIA_SE_LOCAL_HH(ent)))) 
    {
        DT_ERR(("Invalid Hop-by-Hop id received in answer message"));
        delete cmd;
        cmd = NULL; 
        ret = !ITS_SUCCESS;
        return ret;
    } 

    /**
     * If Entry is found check whether this message is to be
     * relayed.
     */
    if ((ret = DiaUtils::RemoveProxyInfoAvp(msg)) == ITS_SUCCESS)
    {
        /**
         * Fix for the issue 889 in whizible, where complete processing
         * from the downstream for relay is shifted here for Accounting
         * Answer message. As per discussion with Ajay and Sarvesh.
         */
        DT_DBG(("Relaying the Acct/Auth Answer message"));
        DIA_HDR &hdr = (DIA_HDR&)msg->getHeader();
        hdr.hh = DIA_SE_RX_HH(ent);

        ret = DiaMsgRouter::SendCmdToPeer(DIA_SE_PEER_INST(ent),
                                                  &hdr,
                                                  cmd);
        if (ret != ITS_SUCCESS)
        {
            DT_ERR(("Failed to send to Peer ret = %d", ret));
            return (ITS_DIA_UNABLE_TO_DELIVER);
        }

        if (SESSION_TABLE->RemoveEntry(ent, (ITS_OCTET *)sessionId.c_str(),
                                         sessionId.size()) != ITS_SUCCESS)
        {
            DT_WRN(("Failed to remove transaction Context"));
        }
    }
   //Fix for coverity issue CID11713.Dont free cmd
   //as it will be freed in SendCmdToPeer
   /*
    delete cmd;
    cmd = NULL; 
   */
    return ret;
}

