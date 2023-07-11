/*********************************-*-CPP-*-**********************************
 *                                                                          *
 *             Copyright 2004 IntelliNet Technologies, Inc.                 *
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
 *  ID: $Id: dmc_common.cpp,v 1.17.46.1 2013/02/27 08:49:07 jvikram Exp $
 *
 *  LOG: $Log: dmc_common.cpp,v $
 *  LOG: Revision 1.17.46.1  2013/02/27 08:49:07  jvikram
 *  LOG: Warnings raised by Coverity have been fixed
 *  LOG:
 *  LOG: Revision 1.17  2010/08/19 11:22:23  nvijikumar
 *  LOG: Porting changes from B-MOTO-IDIA-0421-00
 *  LOG: 1. New Overload implimentation changes are not being ported.
 *  LOG: 2. Force disconnect changes are not being ported
 *  LOG:
 *  LOG: Revision 1.16  2009/10/14 10:49:04  sureshj
 *  LOG: forceDisconectPeer, getPeerTimers, GetLocalHostInfo mml APIs
 *  LOG: added. (motorola helpDesk issues 2219, 2238)
 *  LOG:
 *  LOG: Revision 1.15  2009/09/17 08:36:29  rajeshak
 *  LOG: API to enable/disable DMC hex dump.
 *  LOG:
 *  LOG: Revision 1.14  2009/09/07 05:04:08  rajeshak
 *  LOG: MML Support to set/get HMI Heartbeat interval.
 *  LOG:
 *  LOG: Revision 1.13  2009/07/24 09:45:02  rajeshak
 *  LOG: Following Changes are included
 *  LOG:  1. New MML API's added to get/remove default route,get/set overload limits
 *  LOG:     Enable/Disable HMI
 *  LOG:  2. Stats changes (to include option to clear stats in get)
 *  LOG:
 *  LOG: Revision 1.12  2009/07/14 10:10:50  rajeshak
 *  LOG: Changes done to include peer realm name in destination
 *  LOG: (addDestination, removeDestination, modifyPriority).
 *  LOG:
 *  LOG: Revision 1.11  2009/07/13 08:33:36  rajeshak
 *  LOG: 1. Reverting back session table changes.
 *  LOG: 2. MML API to set/get the HMI Retry.
 *  LOG:
 *  LOG: Revision 1.10  2009/06/29 14:57:28  rajeshak
 *  LOG: 1. MML Commands added to set HMI Check Interval and Timeout.
 *  LOG: 2. Changes for Queue stats and session table size.
 *  LOG:
 *  LOG: Revision 1.9  2009/05/11 06:33:52  rajeshak
 *  LOG: 1. Get/Set Heartbeat Interval changes
 *  LOG: 2. Connection Establishment time in Peer Status
 *  LOG:
 *  LOG: Revision 1.8  2009/04/13 13:48:24  rajeshak
 *  LOG: MML Api added for Peer discovery and modify destination priority.
 *  LOG:
 *  LOG: Revision 1.7  2009/03/30 15:11:08  chandral
 *  LOG: Fix for Issue on PP50
 *  LOG:
 *  LOG: Revision 1.6  2009/03/26 09:39:36  rajeshak
 *  LOG: GetPeerStatus MML API Support
 *  LOG:
 *  LOG: Revision 1.5  2009/03/26 06:01:53  nvijikumar
 *  LOG: GetPeerStatus API Support
 *  LOG:
 *  LOG: Revision 1.4  2009/03/26 05:25:19  nvijikumar
 *  LOG: GetDiaMiscStats API Support
 *  LOG:
 *  LOG: Revision 1.3  2009/03/19 08:51:21  rajeshak
 *  LOG: Added new SetDefaultRoute API to set default route in realm table.
 *  LOG:
 *  LOG: Revision 1.2  2009/03/18 12:59:27  rajeshak
 *  LOG: Enhanced MML API support.
 *  LOG:
 *  LOG: Revision 1.1  2009/03/02 04:39:44  nvijikumar
 *  LOG: Initial draft for MML API Support
 *  LOG:
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: dmc_common.cpp,v 1.17.46.1 2013/02/27 08:49:07 jvikram Exp $"

#include <stdlib.h>
#include <string.h>
#include <its++.h>
#include <engine++.h>

#include <dmc_common.h>

ITS_BOOLEAN traceEnabled = ITS_TRUE;
ITS_BOOLEAN hexEnabled = ITS_FALSE;

void
PrintString(std::string &str)
{
    const char *data = str.c_str();
    printf(" Str len = %zu\n", str.length());
    for(int i=0; i < str.length(); i++)
    {
        if ((i) % 8 == 0)
            printf("\n");
        printf("0x%02x, ",data[i]);
    }
    printf("\n\n");
    fflush(stdout);
}

ITS_INT 
DmcCodec::DecodeDmMsgStats(ITS_OCTET* inStr, DM_MSG_STATS *mStats)
{
    int len = 0;
    int indx = 0;
    ITS_OCTET *evData = inStr;

    if ((len = DecodeInt(&evData[indx], mStats->reqIn)) == -1)
    {
        DMC_TRACE_ERR(("mStats->reqIn decodeInt failed"));
        return -1;
    }
    indx += len;
    if ((len = DecodeInt(&evData[indx], mStats->reqOut)) == -1)
    {       
        DMC_TRACE_ERR(("mStats->reqOut decodeInt failed"));
        return -1;
    }
    indx += len;
    if ((len = DecodeInt(&evData[indx], mStats->ansIn)) == -1)
    {
        DMC_TRACE_ERR(("mStats->ansIn decodeInt failed"));
        return -1;
    }
    indx += len;
    if ((len = DecodeInt(&evData[indx], mStats->ansOut)) == -1)
    {
        DMC_TRACE_ERR(("mStats->ansOut decodeInt failed"));
        return -1;
    }
    indx += len;
    return indx;
}
/*.implementation: DmcCodec::Encode
 *  ****************************************************************************
 *  Purpose:
 *     Encode IDS Management Message
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
 Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_INT
DmcCodec::Encode(DM_MSG *msg, ITS_EVENT *ev)
{
    int ret = ITS_SUCCESS;
    int indx = 0, size = 0;
    std::string strBuff="";
    ITS_OCTET tridData[2]; 

    if (msg == NULL || msg->mType == MSG_TYPE_RES)
    {
        DMC_TRACE_ERR(("DmcCodec::Encode::Failed to Encode"));
        return !ITS_SUCCESS;
    }
    DMC_TRACE_DBG(("DmcCodec::Encode cmd = %s",DM_CMD_TO_TEXT(msg->u.req.cmd)));
    /* Header */
    ITS_OCTET mType = msg->mType;
    strBuff.append((const char *)&mType, sizeof(ITS_OCTET));
    ITS_OCTET cmd = msg->u.req.cmd;
    strBuff.append((const char *)&cmd, sizeof(ITS_OCTET));
    ShortToData(tridData, msg->u.req.trId);
    strBuff.append((const char*)tridData, 2);

    switch(msg->u.req.cmd)
    {
        case EN_STATS:
        case DIS_STATS:
        case RESET_STATS:
        //case GET_INDC_STATS:
        //case GET_MISC_STATS:
        //case GET_SESS_STATS:
        //case GET_PEER_STATS:
        case START_ALL_PEERS:
        case GET_SESSION_TBL_SIZE:
        case GET_DIA_TRACE_STATS:
        case GET_DIA_Q_STATS:
        case EN_PEER_DISCOVERY:
        case DIS_PEER_DISCOVERY:
        case GET_DISCOVERY_INTERVAL:
        case GET_HEARTBEAT_INTERVAL:
        case GET_HEARTBEAT_RETRY:
        case GET_HMI_CHECK_INTERVAL:
        case GET_HMI_TIMEOUT:
        case GET_HMI_RETRY:
        case GET_HMI_HB_INTERVAL:
        case ENABLE_HMI:
        case DISABLE_HMI:
        case HMI_STATUS:
        case GET_OV_LIMIT:
        case GET_DEFAULT_ROUTE:
        case REMOVE_DEFAULT_ROUTE:
        case GET_PEER_TIMERS:
        case GET_LOCAL_HOST_INFO:
        case GET_ROUTE_SCHEME:
        {
            break;
        }
        case EN_TRACE:
        case DIS_TRACE:
        {
            ITS_OCTET traceData = 0x00;
            DM_TRACE *trace = NULL;
            if (msg->u.req.cmd == EN_TRACE)
            {
                trace = &msg->u.req.param.eTrace;
            }
            else
            {
                trace = &msg->u.req.param.dTrace;
            }

            if (trace->all)
            {
                traceData |= DM_BIT_1;
            }
            else
            {
                if (trace->dbg)
                    traceData |= DM_BIT_2;
                if (trace->wrn)
                    traceData |= DM_BIT_3;
                if (trace->err)
                    traceData |= DM_BIT_4;
                if (trace->crt)
                    traceData |= DM_BIT_5;
            }
            strBuff.append((const char*)&traceData, sizeof(ITS_OCTET));
            break;
        }
        case ADD_PEER:
        {
            DM_PEER_ENTRY *addPeer = &msg->u.req.param.addPeer;
            EncodeString(strBuff,addPeer->peerName);
            EncodeString(strBuff,addPeer->realmName);
            EncodeOctet(strBuff,addPeer->trType);
            EncodeString(strBuff,addPeer->ipAddr);
            EncodeShort(strBuff,addPeer->port);
            break;
        }
        case MODIFY_ALTERNATE_PEER:
        case ADD_ALTERNATE_PEER:
        {
            DM_ALT_PEER_INFO *aPeer = NULL;
            if (msg->u.req.cmd == ADD_ALTERNATE_PEER)
            {
                aPeer = &msg->u.req.param.addAltPeer;
            }
            else
            {
                aPeer = &msg->u.req.param.modiAltPeer;
            }
            
            EncodeString(strBuff,aPeer->peerName);
            EncodeString(strBuff,aPeer->realmName);
            EncodeString(strBuff,aPeer->altHost);
            EncodeString(strBuff,aPeer->altRealmName);
            EncodeOctet(strBuff,aPeer->isFailoverEnable);
            EncodeOctet(strBuff,aPeer->isFailbackEnable);
            EncodeOctet(strBuff,aPeer->isRedundantMate);
            break;
        }
        case REMOVE_ALTERNATE_PEER:
        {
            DM_PEER_INFO *pInfo = &msg->u.req.param.rmAltPeer;

            EncodeString(strBuff,pInfo->peerName);
            EncodeString(strBuff,pInfo->realmName);
            break;
        }
        case GET_PEER_STATUS:
        {
            DM_PEER_INFO *pInfo = &msg->u.req.param.peerStatus;
            EncodeString(strBuff,pInfo->peerName);
            EncodeString(strBuff,pInfo->realmName);
            break;
        }
        case START_PEER:
        case REMOVE_PEER:
        case SET_DEFAULT_ROUTE:
        {
            DM_PEER_INFO *pInfo = NULL;
            if (msg->u.req.cmd == START_PEER)
            {
                pInfo = &msg->u.req.param.strPeer;
            }
            else if (msg->u.req.cmd == REMOVE_PEER)
            {
                pInfo = &msg->u.req.param.rmPeer;
            }
            else
            {
                pInfo = &msg->u.req.param.defRoute;
            }
            EncodeString(strBuff, pInfo->peerName);
            EncodeString(strBuff, pInfo->realmName);
            break;
        }
        case DISCONNECT_PEER:
        {
            DM_PEER_DISC *pDisc = &msg->u.req.param.peerDisc;
            EncodeString(strBuff, pDisc->peer.peerName);
            EncodeString(strBuff, pDisc->peer.realmName);
            EncodeInt(strBuff, pDisc->discCause);
            break;
        }
        case FORCE_DISCONNECT_PEER:
        {
            DM_PEER_DISC *pDisc = &msg->u.req.param.peerDisc;
            EncodeString(strBuff, pDisc->peer.peerName);
            EncodeString(strBuff, pDisc->peer.realmName);
            EncodeInt(strBuff, pDisc->discCause);
            EncodeInt(strBuff, pDisc->expiry);
            break;
        }
        case DISCONNECT_ALL_PEER:
        {
            ITS_UINT peerDiscCause = msg->u.req.param.discAllPeers;
            EncodeInt(strBuff, peerDiscCause);
            break;
        }
        case GET_IDC_CONN_STATUS:
        {
            ITS_UINT clientId = msg->u.req.param.clientId;
            EncodeInt(strBuff, clientId);
            break;
        }
        case ADD_REALM:
        {
            DM_REALM_ENTRY *rEntry = &msg->u.req.param.addRealm;
            EncodeString(strBuff, rEntry->realmName);
            EncodeString(strBuff, rEntry->localAction);
            EncodeOctet(strBuff, rEntry->isProxyEnabled);
            break;
        }
        case REMOVE_REALM:
        case EN_PROXY_INFO_AVP:
        case DIS_PROXY_INFO_AVP:
        {
            DM_REALM_INFO *rInfo = NULL;
            if (msg->u.req.cmd == REMOVE_REALM)
            {
                rInfo = &msg->u.req.param.rmRealm;
            }
            else if (msg->u.req.cmd == EN_PROXY_INFO_AVP)
            {
                rInfo = &msg->u.req.param.enProxyInfo;
            }
            else
            {
                rInfo = &msg->u.req.param.disProxyInfo;
            }
            EncodeString(strBuff, rInfo->realmName);
            break;
        }
        case ADD_DESTINATION:
        case REMOVE_DESTINATION:
        case MODIFY_DESTINATION:
        {
            DM_DEST_INFO *dest = NULL;
            if (msg->u.req.cmd == ADD_DESTINATION)
            {
                dest = &msg->u.req.param.addDest;
            }
            else if (msg->u.req.cmd == REMOVE_DESTINATION)
            {
                dest = &msg->u.req.param.rmDest;
            }
            else
            {
                dest = &msg->u.req.param.modDest;
            }
            EncodeString(strBuff, dest->realmName);
            EncodeString(strBuff, dest->peerName);
            EncodeString(strBuff, dest->peerRealm);
            EncodeInt(strBuff, dest->appId);
            EncodeInt(strBuff, dest->vendId);
            EncodeInt(strBuff, dest->priority);
            break;
        }
        case SET_LOCAL_HOST_INFO:
        {
            DM_HOST_INFO* pHostInfo = NULL;
            pHostInfo = &msg->u.req.param.hostInfo;
            EncodeString(strBuff, pHostInfo->hostName);
            EncodeString(strBuff, pHostInfo->realmName);
            EncodeString(strBuff, pHostInfo->ipAddr);
            break;
        }
        case SET_PEER_TIMERS:
        {
            DM_PEER_TIMER* peerTimer = &msg->u.req.param.peerTimer;
            EncodeInt(strBuff, peerTimer->wd);
            EncodeInt(strBuff, peerTimer->retry);
            EncodeInt(strBuff, peerTimer->expiry);
            break;
        }
        case SET_SESSION_TIMERS:
        {
            DM_SESS_TIMER* sessTimer = &msg->u.req.param.sessTimer;
            EncodeInt(strBuff, sessTimer->sessTimeout);
            EncodeInt(strBuff, sessTimer->lifeTimeout);
            EncodeInt(strBuff, sessTimer->graceTimeout); 
            break;
        }
        case DIA_COMMIT:
        {
            DM_XML_COMMIT *xCommit = &msg->u.req.param.xmlCommit;
            EncodeString(strBuff, xCommit->fileName);
            break;
        }
        case ADD_TO_DISCOVERY_LIST:
        case DEL_FROM_DISCOVERY_LIST:
        {
            DM_PEER_INFO *pInfo = NULL;
            if (msg->u.req.cmd == ADD_TO_DISCOVERY_LIST)
            {
                pInfo = &msg->u.req.param.addDiscList;
            }
            else
            {
                pInfo = &msg->u.req.param.delDiscList;
            }
            EncodeString(strBuff,pInfo->peerName);
            EncodeString(strBuff,pInfo->realmName);
            break;
        }
        case SET_DISCOVERY_INTERVAL:
        {
            EncodeInt(strBuff, msg->u.req.param.discInterval);
            break;
        }
        case SET_HEARTBEAT_INTERVAL:
        {
            EncodeInt(strBuff, msg->u.req.param.hbInterval);
            break;
        }
        case SET_HEARTBEAT_RETRY:
        {
            EncodeInt(strBuff, msg->u.req.param.hbRetry);
            break;
        }
        case SET_HMI_CHECK_INTERVAL:
        {
            EncodeInt(strBuff, msg->u.req.param.hmiInterval);
            break;
        }
        case SET_HMI_TIMEOUT:
        {
            EncodeInt(strBuff, msg->u.req.param.hmiTimeout);
            break;
        }
        case SET_HMI_RETRY:
        {
            EncodeInt(strBuff, msg->u.req.param.hmiRetry);
            break;
        }
        case SET_HMI_HB_INTERVAL:
        {
            EncodeInt(strBuff, msg->u.req.param.hmiHBInterval);
            break;
        }
        case SET_OV_LIMIT:
        {
            EncodeInt(strBuff, msg->u.req.param.ovLimits.maxTh);
            EncodeInt(strBuff, msg->u.req.param.ovLimits.minTh);
            break;
        }
        case GET_INDC_STATS:
        case GET_MISC_STATS:
        case GET_SESS_STATS:
        case GET_PEER_STATS:
        {
            EncodeInt(strBuff, msg->u.req.param.statsClearOpt);
            break;
        }
        case SET_ROUTE_SCHEME:
        {
            EncodeOctet(strBuff, msg->u.req.param.routeScheme);
            break;
        }
        default:
            DMC_TRACE_ERR (("Invalid cmd type"));
            ret = !ITS_SUCCESS;
            break;
    }
    if (ret == ITS_SUCCESS)
    {
        size = strBuff.length();
        ITS_EVENT_INIT(ev,DIA_DM_APP_SRC,size);
        memcpy(ev->data,strBuff.c_str(),size);
    } 
    return ret;
}

/*.implementation:DmcCodec::Decode
 *  ****************************************************************************
 *  Purpose:
 *     Decode IDS Management Message
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
ITS_INT
DmcCodec::Decode(DM_MSG *msg, ITS_EVENT *ev)
{
    int ret = ITS_SUCCESS;
    int indx = 0;
    ITS_OCTET *evData = NULL;

    if (msg == NULL || ev == NULL)
    {
        DMC_TRACE_ERR(("DmcCodec::Decode Failed"));
        return !ITS_SUCCESS;
    }

    evData = ev->data;

    msg->mType = (DM_MSG_TYPE)ev->data[indx++];

    if (msg->mType == MSG_TYPE_RES)
    {
         msg->u.res.cmd = (DM_CMD)ev->data[indx++];
         msg->u.res.trId = DataToShort(&ev->data[indx]);
         indx += sizeof(ITS_USHORT);
         msg->u.res.rCode = (DM_RCODE)ev->data[indx++];
    }
    else
    {  
        DMC_TRACE_ERR(("DmcCodec::Decode Message type != Response"));
        return !ITS_SUCCESS;
    }
   
    switch(msg->u.res.cmd)
    {
        case GET_INDC_STATS:
        {
            int len = 0;
            DM_INDIC_STATS *stats = &msg->u.res.param.indicStats;
            if ((len=DecodeInt(&evData[indx], stats->numDisconnInd))== -1)
            {
                DMC_TRACE_ERR(("DecodeInt failed:: numDisconnInd"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len=DecodeInt(&evData[indx], stats->numSessTimeoutInd))== -1)
            {
                DMC_TRACE_ERR(("DecodeInt failed:: numSessTimeoutInd"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len=DecodeInt(&evData[indx],stats->numAuthLifeTimeoutInd))==-1)
            {
                DMC_TRACE_ERR(("DecodeInt failed:: numAuthLifeTimeoutInd"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if((len=DecodeInt(&evData[indx],stats->numAuthGraceTimeoutInd))==-1)
            {
                DMC_TRACE_ERR(("DecodeInt failed:: numAuthGraceTimeoutInd"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len=DecodeInt(&evData[indx], stats->numAbortInd))== -1)
            {
                DMC_TRACE_ERR(("DecodeInt failed:: numAbortInd"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len=DecodeInt(&evData[indx], stats->numCorruptMsgInd))== -1)
            {
                DMC_TRACE_ERR(("DecodeInt failed:: numCorruptMsgInd"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len=DecodeInt(&evData[indx], stats->numUnknownInd))== -1)
            {
                DMC_TRACE_ERR(("DecodeInt failed:: numUnknownInd"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len=DecodeInt(&evData[indx], stats->numFailOverInd))== -1)
            {
                DMC_TRACE_ERR(("DecodeInt failed:: numFailOverInd"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len=DecodeInt(&evData[indx], stats->numFailBackInd))== -1)
            {
                DMC_TRACE_ERR(("DecodeInt failed:: numFailBackInd"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            break;
        }
        case GET_MISC_STATS:
        {
            int len = 0;
            DM_MISC_STATS *stats = &msg->u.res.param.miscStats;
            if ((len=DecodeInt(&evData[indx], stats->redirectEvents))== -1)
            {
                DMC_TRACE_ERR(("DecodeInt failed:: redirectEvents"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len=DecodeInt(&evData[indx], stats->totalRetrans))== -1)
            {
                DMC_TRACE_ERR(("DecodeInt failed:: totalRetrans"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len=DecodeInt(&evData[indx],stats->hhDropMsgs))==-1)
            {
                DMC_TRACE_ERR(("DecodeInt failed:: hhDropMsgs"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if((len=DecodeInt(&evData[indx],stats->unknownTypes))==-1)
            {
                DMC_TRACE_ERR(("DecodeInt failed:: unknownTypes"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len=DecodeInt(&evData[indx],stats->protocolErrs))==-1)
            {
                DMC_TRACE_ERR(("DecodeInt failed:: protocolErrs"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if((len=DecodeInt(&evData[indx],stats->transientErrs))==-1)
            {
                DMC_TRACE_ERR(("DecodeInt failed:: transientErrs"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if((len=DecodeInt(&evData[indx],stats->permanentErrs))==-1)
            {
                DMC_TRACE_ERR(("DecodeInt failed:: permanentErrs"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            break;
        }
        case GET_SESS_STATS:
        {
            int len = 0;
            DM_SESS_STATS *stats = &msg->u.res.param.sessStats;

            if ((len = DecodeDmMsgStats(&evData[indx], &stats->app))== -1)
            {
                DMC_TRACE_ERR(("DecodeDmMsgStats failed:: app"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;

            if ((len = DecodeDmMsgStats(&evData[indx], &stats->ac)) == -1)
            {
                DMC_TRACE_ERR(("DecodeDmMsgStats failed:: ac"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;

            if ((len = DecodeDmMsgStats(&evData[indx], &stats->as)) == -1)
            {
                DMC_TRACE_ERR(("DecodeDmMsgStats failed:: as"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;

            if ((len = DecodeDmMsgStats(&evData[indx], &stats->ra)) == -1)
            {
                DMC_TRACE_ERR(("DecodeDmMsgStats failed:: ra"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;

            if ((len = DecodeDmMsgStats(&evData[indx], &stats->st))  == -1)
            {
                DMC_TRACE_ERR(("DecodeDmMsgStats failed:: st"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;

            if ((len = DecodeDmMsgStats(&evData[indx], &stats->err)) == -1)
            {
                DMC_TRACE_ERR(("DecodeDmMsgStats failed:: err"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;

            if ((len = DecodeInt(&evData[indx], stats->decodeFailure)) == -1)
            {
                DMC_TRACE_ERR(("DecodeInt failed:: decodeFailure"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;

            break;
        }
        case GET_PEER_STATS:
        {
            int len = 0;
            DM_PEER_STATS *stats = &msg->u.res.param.peerStats;

            if ((len = DecodeDmMsgStats(&evData[indx], &stats->total)) == -1)
            {
                DMC_TRACE_ERR(("DecodeDmMsgStats failed:: total"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;

            if ((len = DecodeDmMsgStats(&evData[indx], &stats->ce)) == -1)
            {
                DMC_TRACE_ERR(("DecodeDmMsgStats failed:: ce"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;

            if ((len = DecodeDmMsgStats(&evData[indx], &stats->dw)) == -1)
            {
                DMC_TRACE_ERR(("DecodeDmMsgStats failed:: dw"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;

            if ((len = DecodeDmMsgStats(&evData[indx], &stats->dp)) == -1)
            {
                DMC_TRACE_ERR(("DecodeDmMsgStats failed:: dp"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            break;
        }
        case GET_SESSION_TBL_SIZE:
        {
            int len = 0;
            DM_STATS* stats = &msg->u.res.param.sessTableSize;
            if ((len = DecodeInt(&evData[indx], stats->stats)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;
            break;
        }
        case GET_IDC_CONN_STATUS:
        {
            int len = 0;
            DM_IDC_CONN_INFO* pConnInfo = &msg->u.res.param.idcConnInfo;

            if ((len = DecodeInt(&evData[indx], pConnInfo->appIdentifier)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;

            if ((len = DecodeInt(&evData[indx], pConnInfo->appIdType)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;

            break;
        }
        case GET_DIA_Q_STATS:
        {
            int len = 0;
            DM_QUEUE_STATS* qStats = &msg->u.res.param.qStats;
            if ((len = DecodeInt(&evData[indx], qStats->upQCount)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;

            if ((len = DecodeInt(&evData[indx], qStats->downQCount)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;

            break;
        }
        case GET_DIA_TRACE_STATS:
        {
            int len;
            DM_TRACE* diaTrace =  &msg->u.res.param.diaTrace;

            if ((len = DecodeInt(&evData[indx], diaTrace->all)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;

            if ((len = DecodeInt(&evData[indx], diaTrace->dbg)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;

            if ((len = DecodeInt(&evData[indx], diaTrace->wrn)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;

            if ((len = DecodeInt(&evData[indx], diaTrace->err)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;

            if ((len = DecodeInt(&evData[indx], diaTrace->crt)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;

            break;
        } 
        case GET_PEER_STATUS:
        {
            int len;
            DM_PEER_STATUS *status = &msg->u.res.param.peerStatus;

            if ((len = DecodeString(&evData[indx], (ITS_OCTET*)status->peerName)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;

            if ((len = DecodeString(&evData[indx], (ITS_OCTET*)status->realmName)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;

            if ((len = DecodeOctet(&evData[indx], (ITS_OCTET&)status->type)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;

            if ((len = DecodeString(&evData[indx], (ITS_OCTET*)status->ipAddr)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;

            if ((len = DecodeShort(&evData[indx], status->port)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;

            if ((len = DecodeOctet(&evData[indx], (ITS_OCTET&)status->pState)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;

            if ((len = DecodeInt(&evData[indx], status->isStatic)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;

            if ((len = DecodeInt(&evData[indx], (ITS_UINT&)status->connEstTime)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;

            break;
        }
        case GET_DISCOVERY_INTERVAL:
        {
            int len;
            if ((len = DecodeInt(&evData[indx], msg->u.res.param.discInterval)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;
            break;
        }
        case GET_HEARTBEAT_INTERVAL:
        {
            int len;
            if ((len = DecodeInt(&evData[indx], msg->u.res.param.hbInterval)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;
            break;
        }
        case GET_HEARTBEAT_RETRY:
        {
            int len;
            if ((len = DecodeInt(&evData[indx], msg->u.res.param.hbRetry)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;
            break;
        }
        case GET_HMI_CHECK_INTERVAL:
        {
            int len;
            if ((len = DecodeInt(&evData[indx], msg->u.res.param.hmiInterval)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;
            break;
        }
        case GET_HMI_TIMEOUT:
        {
            int len;
            if ((len = DecodeInt(&evData[indx], msg->u.res.param.hmiTimeout)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;
            break;
        }
        case GET_HMI_RETRY:
        {
            int len;
            if ((len = DecodeInt(&evData[indx], msg->u.res.param.hmiRetry)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;
            break;
        }
        case GET_PEER_TIMERS:
        {
            int len;
            if ((len = DecodeInt(&evData[indx], msg->u.res.param.peerTimer.wd)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;
            if ((len = DecodeInt(&evData[indx], msg->u.res.param.peerTimer.retry)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;
            if ((len = DecodeInt(&evData[indx], msg->u.res.param.peerTimer.expiry)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;
            break;
        }
        case GET_HMI_HB_INTERVAL:
        {
            int len;
            if ((len = DecodeInt(&evData[indx], msg->u.res.param.hmiHBInterval)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;
            break;
        }
        case HMI_STATUS:
        {
            int len;
            if ((len = DecodeInt(&evData[indx], msg->u.res.param.hmiStatus)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;
            break;
        }
        case GET_OV_LIMIT:
        {
            int len;
            if ((len = DecodeInt(&evData[indx], msg->u.res.param.ovLimits.maxTh)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;

            if ((len = DecodeInt(&evData[indx], msg->u.res.param.ovLimits.minTh)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;
            break;
        }
        case GET_DEFAULT_ROUTE:
        {
            int len;
            DM_PEER_INFO *pInfo = &msg->u.res.param.defRoute;

            if ((len = DecodeString(&evData[indx], (ITS_OCTET*)pInfo->peerName)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;
            if ((len = DecodeString(&evData[indx], (ITS_OCTET*)pInfo->realmName)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;
            break;     
        }
        case GET_LOCAL_HOST_INFO:
        {
            int len;
            DM_HOST_INFO *hInfo = &msg->u.res.param.hostInfo;

            if ((len = DecodeString(&evData[indx], (ITS_OCTET*)hInfo->hostName)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;
            if ((len = DecodeString(&evData[indx], (ITS_OCTET*)hInfo->realmName)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;
             if ((len = DecodeString(&evData[indx], (ITS_OCTET*)hInfo->ipAddr)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;
            break;
        }
        case GET_ROUTE_SCHEME:
        {
            int len;
            if ((len = DecodeOctet(&evData[indx], (ITS_OCTET&)msg->u.res.param.routeScheme)) == -1)
            {
                DMC_TRACE_ERR(("Decode failed"));
                ret = !ITS_SUCCESS;
            }
            indx += len;
            break;
        }
        default:
            break;
    } 
    return ret;
}
