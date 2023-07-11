/*********************************-*-CPP-*-**********************************
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
 *  ID: $Id: dia_err_handler.cpp,v 3.17.4.4.4.4.4.1.4.1.8.2 2017/12/21 04:37:20 jkchaitanya Exp $
 *
 *  LOG: $Log: dia_err_handler.cpp,v $
 *  LOG: Revision 3.17.4.4.4.4.4.1.4.1.8.2  2017/12/21 04:37:20  jkchaitanya
 *  LOG: Ticket 1149 changes to support case insensitivity for peers, hosts 7 realms
 *  LOG:
 *  LOG: Revision 3.17.4.4.4.4.4.1.4.1.8.1  2015/02/12 12:23:27  jkchaitanya
 *  LOG: changes for bug 5173 setting proxy bit in answer message in mandatory fields are missing in req message
 *  LOG:
 *  LOG: Revision 3.17.4.4.4.4.4.1.4.1  2014/04/03 09:34:54  millayaraja
 *  LOG: DiaMsgFlow Copy constructor and avoid crash while sending message to application, indication with data
 *  LOG:
 *  LOG: Revision 3.17.4.4.4.4.4.1  2013/08/06 09:57:59  jkchaitanya
 *  LOG: bug:- 1978, Review Request:- 1269
 *  LOG:
 *  LOG: Revision 3.17.4.4.4.4  2013/04/04 09:06:11  mallikarjun
 *  LOG: MemLeak Fixes Bug 1205 1298
 *  LOG:
 *  LOG: Revision 3.17.4.4.4.3  2013/04/04 03:48:30  ksalil
 *  LOG: Added the alarm for unable to deliver
 *  LOG:
 *  LOG: Revision 3.17.4.4.4.2  2013/02/27 08:49:07  jvikram
 *  LOG: Warnings raised by Coverity have been fixed
 *  LOG:
 *  LOG: Revision 3.17.4.4.4.1  2013/02/15 12:23:41  jsarvesh
 *  LOG: we have to move error realm_not_served and unknown_peer to global stats so commenting it out
 *  LOG:
 *  LOG: Revision 3.17.4.4  2013/01/04 06:57:58  millayaraja
 *  LOG: modified to update Error stats
 *  LOG:
 *  LOG: Revision 3.17.4.3  2012/12/21 05:31:54  ncshivakumar
 *  LOG: Modified for tracing
 *  LOG:
 *  LOG: Revision 3.17.4.2  2012/12/17 05:34:17  mallikarjun
 *  LOG: Bug 699 T bit
 *  LOG:
 *  LOG: Revision 3.17.4.1  2012/11/20 17:39:44  pramana
 *  LOG: Merged from CMAPI branch for 212-07 release
 *  LOG:
 *  LOG: Revision 3.17.28.2  2012/11/17 07:28:01  millayaraja
 *  LOG: modified for stack stats
 *  LOG:
 *  LOG: Revision 3.17.28.1  2012/11/14 08:33:07  millayaraja
 *  LOG: modified to accomdate Peer stack stats
 *  LOG:
 *  LOG: Revision 3.17  2011/08/23 04:12:18  vkumara
 *  LOG: DataToInt is being changed to DataToUInt.
 *  LOG: To fix CmdCode decode error for an unsigned values from abnf.
 *  LOG: (Extra FF was returning from existing DataToInt ()).
 *  LOG:
 *  LOG: Revision 3.16  2009/07/24 09:22:18  rajeshak
 *  LOG: Changes done for IDC-IDS Heartbeat with Custom AVP in DWR.
 *  LOG:
 *  LOG: Revision 3.15  2009/03/19 12:41:20  nvijikumar
 *  LOG: Global instance is created for the Class ITSDiaConfig to avoid function
 *  LOG: call overhead as ITSDiaConfig::GetITSDiaConfig() was called max time
 *  LOG:
 *  LOG: Revision 3.14  2009/01/09 10:06:39  rajeshak
 *  LOG: Klockwork reported issue fix.
 *  LOG:
 *  LOG: Revision 3.13  2009/01/05 09:20:59  nvijikumar
 *  LOG: Tracing enhancement
 *  LOG:
 *  LOG: Revision 3.12  2009/01/03 05:43:30  rajeshak
 *  LOG: Introduced common func to send all indications
 *  LOG:
 *  LOG: Revision 3.11  2009/01/01 08:19:08  nvijikumar
 *  LOG: Fix for Issue Id:1412 (Alarm for loopback messages)
 *  LOG:
 *  LOG: Revision 3.10  2008/12/12 18:30:47  rajeshak
 *  LOG: Lightweight Decode for base AVPS
 *  LOG: New Command class is introduced (BaseCommand)
 *  LOG:
 *  LOG: Revision 3.9  2008/12/12 12:32:08  nvijikumar
 *  LOG: Updated with statistic support
 *  LOG:
 *  LOG: Revision 3.8  2008/12/07 09:42:20  rajeshak
 *  LOG: Added definition of new function SendErrResToPeerNApp to Handle error.
 *  LOG:
 *  LOG: Revision 3.7  2008/10/28 12:06:28  nvijikumar
 *  LOG: IssueID: none
 *  LOG: FeatureID: none
 *  LOG: Description: Porting Performance changes from 3.0 branch
 *  LOG:
 *  LOG: Revision 3.6  2008/08/20 07:40:41  sureshj
 *  LOG: Fix for the issue 1092. IDS dumps core on receiving message without
 *  LOG: fixed or mandatory part from IDC.
 *  LOG:
 *  LOG: Revision 3.5  2008/04/16 12:07:16  hbhatnagar
 *  LOG: Made changes in error response function for not adding local proxy
 *  LOG: info AVP
 *  LOG:
 *  LOG: Revision 3.4  2008/04/08 10:06:21  hbhatnagar
 *  LOG: changing the API call for proxyable error from setProxyInfo to addProxyInfo
 *  LOG: according to  changes done in abnf.
 *  LOG:
 *  LOG: Revision 3.3  2008/04/07 18:09:26  hbhatnagar
 *  LOG: Declaration of pinfoCount is done to remove compilation errors.
 *  LOG:
 *  LOG: Revision 3.2  2008/04/07 17:30:37  hbhatnagar
 *  LOG: Changed SendErrorRes to include the Proxy-Info AVP in the case of
 *  LOG: PROXYABLE error.
 *  LOG:
 *  LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 2.11  2008/03/27 12:14:08  hbhatnagar
 *  LOG: Converting 2.1 branch to CURRENT
 *  LOG:
 *  LOG: Revision 2.9.2.2  2007/05/30 09:33:33  nvijikumar
 *  LOG: Check occurence of sessionId AVP before try to get Session Id
 *  LOG: Fix for Bug Id: 5932.
 *  LOG:
 *  LOG: Revision 2.9.2.1  2007/05/28 14:17:28  nvijikumar
 *  LOG: Provided new function to Send Error Response if message failed to decode.
 *  LOG:
 *  LOG: Revision 2.9  2007/02/19 15:02:52  nvijikumar
 *  LOG: IOT:: Issue
 *  LOG: Fix for error response with appropriate appId.
 *  LOG:
 *  LOG: Revision 2.8  2006/11/14 13:26:21  kamakshilk
 *  LOG: Address of IND_WITH_DATA msg changed to ITS_ULONG for 64-bit compatibility
 *  LOG:
 *  LOG: Revision 2.7  2006/11/13 06:11:51  tpanda
 *  LOG: clientId related fix for IDS
 *  LOG:
 *  LOG: Revision 2.6  2006/10/27 09:46:47  yranade
 *  LOG: Set the header in the error response with correct values.
 *  LOG:
 *  LOG: Revision 2.5  2006/10/24 13:52:38  yranade
 *  LOG: Header changes. Use header by reference from the message.
 *  LOG:
 *  LOG: Revision 2.4  2006/10/13 16:42:00  yranade
 *  LOG: Updated error handling.
 *  LOG:
 *  LOG: Revision 2.3  2006/10/12 14:05:37  yranade
 *  LOG: Small updates.
 *  LOG:
 *  LOG: Revision 2.2  2006/10/11 15:00:58  yranade
 *  LOG: Updated Error Handling a bit, still a WIP.
 *  LOG:
 *  LOG: Revision 2.1  2006/10/05 13:53:58  yranade
 *  LOG: Update version
 *  LOG:
 *  LOG: Revision 1.1  2006/10/05 13:51:32  yranade
 *  LOG: Error Handler.
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: dia_err_handler.cpp,v 3.17.4.4.4.4.4.1.4.1.8.2 2017/12/21 04:37:20 jkchaitanya Exp $"

#include <its++.h>
#include <engine++.h>

#include <dia_err.h>
#include <dia_cmn.h>
#include <dia_utils.h>
#include <dia_trace.h>
#include <dia_upstream.h>
#include <dia_msg_router.h>
#include <dia_realm_table.h>
#include <dia_session_table.h>
#include <dia_session_auth_fsm.h>
#include <dia_session_acct_fsm.h>

#include "dia_tracer.h"

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
using namespace diameter;
using namespace diameter::base;
#endif

#define SESSIONID_AVP_CODE 263

static int
SendErrorRes(ITS_USHORT inst, DIA_BASE_CMD *inMsg, bool error, bool retrans, ITS_UINT rCode)
{
    int ret;
    int pinfo_count = 0;

    DT_ERR(("ErrHandler::SendErrorResponse"));

    if (!inMsg)
    {
        DT_ERR(("ErrHandler::Invalid inbound cmd...Discarding"));
        return (ITS_SUCCESS);
    }

    if ((rCode == ITS_DIA_UNABLE_TO_DELIVER) || (rCode == ITS_DIA_REALM_NOT_SERVED))
    {
	    if (inMsg->getDestinationHost())
	    {
		    const char* hostName;
		    const char* realmName;
		    hostName = inMsg->getDestinationHost()->value().c_str();
		    if (inMsg->getDestinationRealm())
		    {
			    realmName = inMsg->getDestinationRealm()->value().c_str(); 
			    DIA_Alarm(15104, __FILE__, __LINE__, "Peer =%s: Realm=%s",
					    hostName, realmName);
		    }
		    else
		    {
			    DIA_Alarm(15104, __FILE__, __LINE__, "Peer =%s: Realm=Not Present",
					    hostName);
		    }
	    }
	    else
	    {
		    const char* realmName;
		    if (inMsg->getDestinationRealm())
		    {
			    realmName = inMsg->getDestinationRealm()->value().c_str();
			    DIA_Alarm(15104, __FILE__, __LINE__, "Peer = Not Present: Realm=%s",
					    realmName);
		    }
		    else 
		    {
			    realmName = inMsg->getDestinationRealm()->value().c_str();
			    DIA_Alarm(15104, __FILE__, __LINE__, "Peer = Not Present: Realm= Not Present");
		    }
	    }
    }

    DIA_CER *lcer = itsDiaConfig.GetLocalCER();

    DIA_HDR &hdr = (DIA_HDR&)inMsg->getHeader();

    PROXYABLEERROR pErr(error, retrans, inMsg->getCommandCode());
    NONPROXYABLEERROR nErr(error, retrans, inMsg->getCommandCode());
    DIA_GEN_CMD *cmd;
    if (inMsg->isProxyable())
    {
        if (inMsg->getSessionId())
        {
            SessionId sid(inMsg->getSessionId()->value());
            pErr.setSessionId(sid);
        }
        pErr.setOriginHost(lcer->getOriginHost());
        pErr.setOriginRealm(lcer->getOriginRealm());
        pErr.setResultCode(ResultCode(rCode));

        /**
         * Adding the Proxy-Info AVP in error response
         * from message.
         */
        pinfo_count = inMsg->countProxyInfo();
        for(int i=0; i<pinfo_count; i++)
        {
            PROXY_INFO* pInfo = (inMsg->getProxyInfo(i));

            /**
             * While adding ProxyInfo AVPs Check for whether
             * added locally in request. If yes omit in Error
             * response.
             */
            if (!strcasecmp(pInfo->getProxyHost()->value().c_str(),
                lcer->getOriginHost().value().c_str()))
            {
                continue;
            }
            ProxyInfo proxyInfo;
            ProxyHost phost(pInfo->getProxyHost()->value().c_str());
            proxyInfo.setProxyHost(phost);

            ProxyState pstate(pInfo->getProxyState()->value().c_str());
            proxyInfo.setProxyState(pstate);

            /**
             * changing the API from setProxyInfo to addProxyInfo
             * according to  changes done in abnf
             */
            pErr.addProxyInfo(proxyInfo);
        }

        cmd = (DIA_GEN_CMD *)&pErr;
    }
    else
    {
        if (inMsg->getSessionId())
        {
            SessionId sid(inMsg->getSessionId()->value());
            nErr.setSessionId(sid);
        }
        nErr.setOriginHost(lcer->getOriginHost());
        nErr.setOriginRealm(lcer->getOriginRealm());
        nErr.setResultCode(ResultCode(rCode));
        cmd = (DIA_GEN_CMD *)&nErr;
    }

    /* Fix for error response with appropriate appId while InterOP with Aricent */
    ((DIA_HDR&)cmd->getHeader()).appId   = hdr.appId;
    ((DIA_HDR&)cmd->getHeader()).flags.p = hdr.flags.p;
    ((DIA_HDR&)cmd->getHeader()).hh = hdr.hh;
    ((DIA_HDR&)cmd->getHeader()).ee = hdr.ee;

    //Warning Fix - suggest parentheses around assignment used as truth value
    if ((ret = DiaMsgRouter::SendCmdToPeer(inst, &hdr, cmd,PEER_EVT_SEND_MESSAGE,true)) != ITS_SUCCESS)
    {
        DT_ERR(("Failed to send Err Response for : ret = %d", ret));
    }
    else
    {
        DiaTracer::LogProtoMsg(cmd, inst);
    }

    UPDATE_DIA_ERR_ANSOUT();

    return (ret);
}

static int
SendErrorRes(ITS_USHORT inst, ITS_OCTET *msg,  bool error, 
             bool retrans, ITS_UINT rCode)
{
    int ret;
    ITS_OCTET cmdFlag = 0x0;
    ITS_UINT cmdCode = 0;
    ITS_UINT appId = 0;
    ITS_UINT firstAvpCode = 0;
    ITS_UINT hh = 0;
    ITS_UINT ee = 0;
    int sessLen = 0;
    char sessId[256];
    DIA_HDR hdr;

    if (!msg)
    {
        DT_ERR(("ErrHandler::Invalid inbound msg...Discarding"));
        return (ITS_SUCCESS);
    }
    cmdFlag = msg[4];

    DT_ERR(("ErrHandler::SendErrorResponse"));

    cmdCode = DiaUtils::DataToUInt(&msg[5], (sizeof(ITS_UINT) - 1));
    hdr.appId = DiaUtils::DataToInt(&msg[8], sizeof(ITS_UINT));
    hdr.hh = DiaUtils::DataToInt(&msg[12], sizeof(ITS_UINT));
    hdr.ee = DiaUtils::DataToInt(&msg[16], sizeof(ITS_UINT));
    hdr.flags.p = PROXY_BIT_SET(cmdFlag);
    firstAvpCode = DiaUtils::DataToInt(&msg[20], sizeof(ITS_UINT));

    if (firstAvpCode == SESSIONID_AVP_CODE)
    {
        sessLen = DiaUtils::DataToInt(&msg[25],(sizeof(ITS_UINT) - 1));
        memcpy(sessId, &msg[28], sessLen);
    }

    DIA_CER *lcer = itsDiaConfig.GetLocalCER();

    PROXYABLEERROR pErr(error, retrans, cmdCode);
    NONPROXYABLEERROR nErr(error, retrans, cmdCode);
    DIA_GEN_CMD *cmd;
    if (PROXY_BIT_SET(cmdFlag))
    {
        /* Set Session Id if exists */
        if (sessLen)
        {
            pErr.setSessionId(SessionId(sessId));
        }
        pErr.setOriginHost(lcer->getOriginHost());
        pErr.setOriginRealm(lcer->getOriginRealm());
        pErr.setResultCode(ResultCode(rCode));
        cmd = (DIA_GEN_CMD *)&pErr;
        ((DIA_HDR&)cmd->getHeader()).flags.p = SET_PROXY_BIT(((DIA_HDR&)cmd->getHeader()).flags.p);
    }
    else
    {
        /* Set Session Id if exists */
        if (sessLen)
        {
            nErr.setSessionId(SessionId(sessId));
        }
        nErr.setOriginHost(lcer->getOriginHost());
        nErr.setOriginRealm(lcer->getOriginRealm());
        nErr.setResultCode(ResultCode(rCode));
        cmd = (DIA_GEN_CMD *)&nErr;
    }

    ((DIA_HDR&)cmd->getHeader()).appId   = hdr.appId;
    ((DIA_HDR&)cmd->getHeader()).hh = hdr.hh;
    ((DIA_HDR&)cmd->getHeader()).ee = hdr.ee;

    //Warning Fix - suggest parentheses around assignment used as truth value
    if ((ret = DiaMsgRouter::SendCmdToPeer(inst, &hdr, cmd,PEER_EVT_SEND_MESSAGE,true)) != ITS_SUCCESS)
    {
        DT_ERR(("Failed to send Err Response for : ret = %d", ret));
    }
    else 
    {
        DiaTracer::LogProtoMsg(cmd, inst);
    }
        
    UPDATE_DIA_ERR_ANSOUT();

    return (ret);
}

static 
int LoopBackMsg(DIA_BASE_CMD *inMsg, bool error, bool retrans, ITS_UINT rCode)
{
    DT_ERR(("ErrHandler::LoopBackMsg"));

    if (!inMsg)
    {
        DT_ERR(("ErrHandler::Invalid inbound cmd...Discarding"));
        return (ITS_SUCCESS);
    }

    DIA_CER *lcer = itsDiaConfig.GetLocalCER();

    DIA_HDR hdr;

    hdr = inMsg->getHeader();
    DIA_GEN_CMD *cmd;

    ITS_OCTET data[sizeof(ITS_ULONG)];
    DIA_BASE_CMD* bCmd =  NULL;
    if (inMsg->isProxyable())
    {
        PROXYABLEERROR *pErr = new PROXYABLEERROR(error, 
                                                  retrans, 
                                                  inMsg->getCommandCode());
        //const SessionId* sid = inMsg->getSessionId();
        if (inMsg->getSessionId())
        {
            SessionId sid(inMsg->getSessionId()->value());
            pErr->setSessionId(sid);
        }
        pErr->setOriginHost(lcer->getOriginHost());
        pErr->setOriginRealm(lcer->getOriginRealm());
        pErr->setResultCode(ResultCode(rCode));
        cmd = (DIA_GEN_CMD *)pErr;

    }
    else
    {
        NONPROXYABLEERROR *nErr = new NONPROXYABLEERROR(error, 
                                                        retrans, 
                                                        inMsg->getCommandCode());
       	 //const SessionId* sid = inMsg->getSessionId();
        if (inMsg->getSessionId())
        {	
    	    SessionId sid(inMsg->getSessionId()->value());
            nErr->setSessionId(sid);
        }
        nErr->setOriginHost(lcer->getOriginHost());
        nErr->setOriginRealm(lcer->getOriginRealm());
        nErr->setResultCode(ResultCode(rCode));
        cmd = (DIA_GEN_CMD *)nErr;
        //memcpy(&data[0], &nErr, sizeof(ITS_ULONG));
    }
    
    int dataLen;
    ITS_OCTET* pData=NULL;

    if(cmd)
    {
        /* no need to delete cmd, it will be deleted when the DiaMsgFlow is deleted */
        bCmd = new DIA_BASE_CMD(cmd);
        memcpy(&data[0], &bCmd, sizeof(ITS_ULONG));

        /* Fix for error response with appropriate appId while InterOP with Aricent */
        ((DIA_HDR&)bCmd->getHeader()).appId   = hdr.appId;

        UPDATE_DIA_ERR_ANSIN();

        DIA_Alarm(15101, __FILE__, __LINE__, "CmdCode=%d:AppId=%d",
                  hdr.code,hdr.appId);

        return DiaMsgRouter::SendMsgToApp(ITS_DIA_MSG_TYPE_IND_WITH_DATA,
                                          inMsg->getSessionIndex(), 
                                          inMsg->getHeader().appId,
                                          data,
                                          sizeof(ITS_ULONG), inMsg->getClientId());
    }

    //Warning Fix - control reaches end of non-void function 
    return ITS_SUCCESS;
}

static
int HeartbeatMsg(DIA_BASE_CMD *inMsg, ITS_UINT rCode)
{
    DT_DBG(("Heartbeat Message"));

    if (!inMsg)
    {
        DT_ERR(("ErrHandler::Invalid inbound cmd...Discarding"));
        return (ITS_SUCCESS);
    }

    DIA_CER *lcer = itsDiaConfig.GetLocalCER();

    DIA_HDR hdr;

    hdr = inMsg->getHeader();
    DIA_GEN_CMD *cmd;

    ITS_OCTET data[sizeof(ITS_ULONG)];
    DIA_BASE_CMD* bCmd =  NULL;

    NONPROXYABLEERROR *nErr = new NONPROXYABLEERROR(true, false,
                                                    inMsg->getCommandCode());

    if (nErr)
    {
        nErr->setOriginHost(lcer->getOriginHost());
        nErr->setOriginRealm(lcer->getOriginRealm());
        nErr->setResultCode(ResultCode(rCode));
        nErr->setResultCode(ResultCode(rCode));

        IDCIDSHeartbeat idcHb(rCode);
        nErr->addExtra(idcHb);

        cmd = (DIA_GEN_CMD *)nErr;

        bCmd = new DIA_BASE_CMD(cmd);

        delete cmd;

        memcpy(&data[0], &bCmd, sizeof(ITS_ULONG));

        /* Fix for error response with appropriate appId while InterOP with Aricent */
        ((DIA_HDR&)bCmd->getHeader()).appId   = hdr.appId;

        return DiaMsgRouter::SendMsgToApp(ITS_DIA_MSG_TYPE_IND_WITH_DATA,
                                          inMsg->getSessionIndex(),
                                          inMsg->getHeader().appId,
                                          data,
                                          sizeof(ITS_ULONG), inMsg->getClientId());
    }

    return (!ITS_SUCCESS);
}

static
int HandleErrorStatistics(ITS_UINT inst, ITS_UINT rCode)
{
    PEER_ENTRY *peerEntry = NULL;
    DiaSocketTransport *tr = trTable[inst];
    if(NULL != tr)
    {
        peerEntry = tr->GetPeer();
        if(NULL == peerEntry)
        {
            return !ITS_SUCCESS;
        }
    }
    else
    {
        return !ITS_SUCCESS;
    }
    switch(rCode)
    {
        case ITS_DIA_UNABLE_TO_DELIVER :
                DIA_INC_PEER_UNABLE_TO_DELIVER_COUNT(peerEntry);
                break;
        //case ITS_DIA_REALM_NOT_SERVED :
        //        DIA_INC_PEER_REALM_NOT_SERVED_COUNT(peerEntry);
        //        break;
        //case ITS_DIA_UNKNOWN_PEER :
        //        DIA_INC_PEER_UNKNOWN_PEER_COUNT(peerEntry);
        //        break;
        case ITS_DIA_UNKNOWN_SESSION_ID :
                DIA_INC_PEER_UNKNOWN_SESSION_ID_COUNT(peerEntry);
                break;
        case ITS_DIA_INVALID_AVP_VALUE :
                DIA_INC_PEER_INVALID_AVP_VALUE_COUNT(peerEntry);
                break;
        case ITS_DIA_MISSING_AVP :
                DIA_INC_PEER_MISSING_AVP_COUNT(peerEntry);
                break;
        case ITS_DIA_NO_COMMON_APP :
                DIA_INC_PEER_NO_COMMON_APP_COUNT(peerEntry);
                break;
        case ITS_DIA_INVALID_AVP_LENGTH :
                DIA_INC_PEER_INVALID_AVP_LENGTH_COUNT(peerEntry);
                break;
        case ITS_DIA_INVALID_MSG_LENGTH :
                DIA_INC_PEER_INVALID_MESSAGE_LENGTH_COUNT(peerEntry);
                break;
        case ITS_DIA_LOOP_DETECTED :
                DIA_INC_PEER_LOOP_DETECTED_COUNT(peerEntry);
                break;
        case ITS_DIA_APP_UNSUPPORTED :
                DIA_INC_PEER_APP_UNSUPPORTED_COUNT(peerEntry);
                break;
        default :
                DIA_INC_PEER_OTHER_ERRORS_COUNT(peerEntry);
                break;
    }
    return ITS_SUCCESS;
}


int
DiaErrHandler::HandleError(ITS_USHORT inst, DIA_BASE_CMD *inMsg,
                           DIA_ERR_ACTION_TYPE act,
                           ITS_UINT rCode)
{
    int ret;
    bool error=false;

    const char* hostName;
    const char* realmName;

    if((ret = HandleErrorStatistics(inst,rCode)) != ITS_SUCCESS)
    {
        DT_ERR(("Unable to log Error Statistics"));
    }
    switch (act)
    {
    case SEND_ERROR_TO_PEER:
        if( (rCode >ITS_DIA_PROT_ERR_MIN_RANGE) && (rCode <=ITS_DIA_PROT_ERR_MAX_RANGE))
        { error=true;}
        return SendErrorRes(inst, inMsg, error, false, rCode);
    case LOOP_TO_APP:
        return LoopBackMsg(inMsg, true, false, rCode);
        break;
    case HEARTBEAT:
        return HeartbeatMsg(inMsg, rCode);
    default:
        DT_ERR(("Invalid DIA_ERR_ACTION_TYPE"));
        break;
    }

    return (ITS_SUCCESS);
}

int
DiaErrHandler::HandleError(ITS_USHORT inst, ITS_OCTET *msg, ITS_UINT rCode)
{
    int ret;
    DT_ERR(("HandleError"));
    if((HandleErrorStatistics(inst,rCode)) != ITS_SUCCESS)
    {
        DT_ERR(("Unable to log Error Statistics"));
    }
    return SendErrorRes(inst,msg,true, false, rCode);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      For sending error indication to Application and error response to peer.
 *      The session entry will be removed from session table.
 *
 *  Input Parameters:
 *      SESSION_ENTRY and DIA_CMD.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Return ITS_SUCCESS after removing the session from session table
 *      else error.
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int 
DiaErrHandler::SendErrorResponse(SESSION_ENTRY* e, DIA_BASE_CMD* msg)
{
    int ret = ITS_SUCCESS;
    ITS_OCTET * sessionId = (ITS_OCTET*) msg->getSessionId()->value().c_str();

    /**
     * Send Error response as message received is Invalid.
     */
    DT_ERR(("Message received not proper, Sending error response"));
    ret = DiaErrHandler::HandleError(DIA_SE_PEER_INST(e), msg,
                                     SEND_ERROR_TO_PEER,
                                     ITS_DIA_UNABLE_TO_DELIVER);

    DT_DBG(("Sending Error indication to Application"));
    /* Send Indication to Application */
    if (DiaMsgRouter::SendIndication(e, NULL, (char*)sessionId, MSG_INVALID_IND_FROM_STACK)
                                                       != ITS_SUCCESS)
    {
        DT_ERR(("Failed To send Indication to application"));
    }

    if ((ret = SESSION_TABLE->RemoveEntry(e,
                                        (ITS_OCTET *)sessionId,
                                        strlen((const char*)sessionId)))
                                        != ITS_SUCCESS)
    {
        DT_ERR(("Failed to remove session Entry %d", ret));
    }
    UPDATE_DIA_ERR_ANSIN();    

    return ret;
}

int 
DiaErrHandler::UpdateErrorStats(ITS_UINT trInst, ITS_UINT rCode)
{
    int ret = ITS_SUCCESS;
    if((HandleErrorStatistics(trInst,rCode)) != ITS_SUCCESS)
    {
        ret = !ITS_SUCCESS;
        DT_ERR(("Unable to log Error Statistics"));
    }
    return ret;
}
