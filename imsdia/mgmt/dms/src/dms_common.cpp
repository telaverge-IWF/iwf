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
 *  ID: $Id: dms_common.cpp,v 1.17.46.2 2013/02/27 08:49:07 jvikram Exp $
 *
 *  LOG: $Log: dms_common.cpp,v $
 *  LOG: Revision 1.17.46.2  2013/02/27 08:49:07  jvikram
 *  LOG: Warnings raised by Coverity have been fixed
 *  LOG:
 *  LOG: Revision 1.17.46.1  2013/02/21 11:49:06  ncshivakumar
 *  LOG: Removed 3rd parameter from SetLocalHostInfo() as it does not accept ip address
 *  LOG: ----------------------------------------------------------------------
 *  LOG:
 *  LOG: Revision 1.17  2010/08/19 11:22:23  nvijikumar
 *  LOG: Porting changes from B-MOTO-IDIA-0421-00
 *  LOG: 1. New Overload implimentation changes are not being ported.
 *  LOG: 2. Force disconnect changes are not being ported
 *  LOG:
 *  LOG: Revision 1.16  2009/10/14 10:46:09  sureshj
 *  LOG: forceDisconectPeer, getPeerTimers, GetLocalHostInfo mml commands
 *  LOG: added. (motorola helpDesk issues 2219, 2238).
 *  LOG:
 *  LOG: Revision 1.15  2009/09/11 10:47:35  sureshj
 *  LOG: Dms Hex dumps are getting printed in IDS.out even enableHexDump = 0.
 *  LOG: Motorola ticket 2211.
 *  LOG:
 *  LOG: Revision 1.14  2009/09/07 05:02:10  rajeshak
 *  LOG: MML Support to set/get HMI Heartbeat interval.
 *  LOG:
 *  LOG: Revision 1.13  2009/07/24 09:42:15  rajeshak
 *  LOG: Following Changes are include
 *  LOG:  1. New MML API's added to get/remove default route,get/set overload limits
 *  LOG:     Enable/Disable HMI
 *  LOG:  2. Stats changes (to include option to clear stats in get)
 *  LOG:
 *  LOG: Revision 1.12  2009/07/14 10:10:12  rajeshak
 *  LOG: Changes done to include peer realm name in destination
 *  LOG: (addDestination, removeDestination, modifyPriority).
 *  LOG:
 *  LOG: Revision 1.11  2009/07/13 12:41:54  nvijikumar
 *  LOG: Fix for Invalid Transport Type Issue (Peer entry added via MML API)
 *  LOG:
 *  LOG: Revision 1.10  2009/07/13 08:34:55  rajeshak
 *  LOG: 1. Reverting back session table changes.
 *  LOG: 2. MML API to set/get the HMI Retry.
 *  LOG:
 *  LOG: Revision 1.9  2009/06/29 14:58:19  rajeshak
 *  LOG: 1. MML Commands added to set HMI Check Interval and Timeout.
 *  LOG: 2. Changes for Queue stats and session table size.
 *  LOG:
 *  LOG: Revision 1.8  2009/05/11 06:29:50  rajeshak
 *  LOG: 1. Get/Set Heartbeat Interval changes
 *  LOG: 2. Connection Establishment time in Peer Status
 *  LOG:
 *  LOG: Revision 1.7  2009/04/13 13:47:09  rajeshak
 *  LOG: MML Api added for Peer discovery and modify destination priority.
 *  LOG:
 *  LOG: Revision 1.6  2009/03/30 15:13:10  chandral
 *  LOG: Fix for Issue on PP50
 *  LOG:
 *  LOG: Revision 1.5  2009/03/26 09:37:58  rajeshak
 *  LOG: GetPeerStatus MML API Support
 *  LOG:
 *  LOG: Revision 1.4  2009/03/26 05:30:12  nvijikumar
 *  LOG: GetDiaMiscStats and ResetAllStats API Support
 *  LOG:
 *  LOG: Revision 1.3  2009/03/19 08:48:08  rajeshak
 *  LOG: Changes for SetDefaultRoute API support.
 *  LOG:
 *  LOG: Revision 1.2  2009/03/18 12:56:47  rajeshak
 *  LOG: Enhanced MML API support.
 *  LOG:
 *  LOG: Revision 1.1  2009/03/02 04:39:44  nvijikumar
 *  LOG: Initial draft for MML API Support
 *  LOG:
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: dms_common.cpp,v 1.17.46.2 2013/02/27 08:49:07 jvikram Exp $"

#include <stdlib.h>
#include <string.h>
#include <its++.h>
#include <engine++.h>

#include <dia_trace.h>
#include <dms_common.h>
#include <dia_mgmt.h>
#include <dia_config.h>
#include <ids_common.h>

//#include <dia_stack_stats.h>

//using namespace diameter;

/*
 *  Transport handle for Mgmt Server
 */
extern ITS_HANDLE dmsHandle;
extern IDS_ROUTING_SCHEME routeScheme;

void
PrintEvent(ITS_EVENT *ev)
{
    DiaMgmt *diaMgmt = DiaMgmt::GetDiaMgmt();
    if(diaMgmt->IsHexDumpEnabled())
    {
        printf("Event len %u\n", ev->len);
        for(int i=0; i < ev->len; i++)
        {
            if ((i) % 8 == 0)
                printf("\n");
            printf("0x%02x, ",ev->data[i]);
        }
        printf("\n\n");
        fflush(stdout);
    }
}

void 
ConverDestInfo(DM_DEST_INFO *dmInfo, DESTINATION_INFO *dInfo)
{
    dInfo->realmName     = (const char*)&dmInfo->realmName;
    dInfo->peerName      = (const char*)&dmInfo->peerName;
    dInfo->peerRealm     = (const char*)&dmInfo->peerRealm;
    dInfo->applicationId = dmInfo->appId;
    dInfo->vendorId      = dmInfo->vendId;
    dInfo->priority      = dmInfo->priority;
}

void 
DmsMsgHandler::EncodeDmMsgStats(std::string &str, DM_MSG_STATS *mStats)
{
    EncodeInt(str, mStats->reqIn);
    EncodeInt(str, mStats->reqOut);
    EncodeInt(str, mStats->ansIn);
    EncodeInt(str, mStats->ansOut);
}

/*.implementation:DmsMsgHandler::ProcessMsg
 ****************************************************************************
 *  Purpose:
 *     Process IDS Management Message
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
DmsMsgHandler::ProcessMsg(ITS_EVENT *ev)
{
    int ret = ITS_SUCCESS;
    DiaMgmt *diaMgmt = DiaMgmt::GetDiaMgmt();
    ITS_EVENT evt;
    DM_MSG msgIn;
    DM_MSG msgOut;

    DT_DBG(("DmsMsgHandler::ProcessMsg"));
    PrintEvent(ev);

    memset(&msgIn,0,sizeof(DM_MSG));
    memset(&msgOut,0,sizeof(DM_MSG));

    ITS_OCTET mType = ev->data[0];

    if (mType == MSG_TYPE_RES)
    {
        return !ITS_SUCCESS;
    }
    if (Decode(&msgIn, ev) != ITS_SUCCESS)
    {
        DT_ERR(("DmsMsgHandler::ProcessMsg decode failed\n"));
        return !ITS_SUCCESS;
    }
    /* Setting common parameters */
    msgOut.mType = MSG_TYPE_RES;
    msgOut.u.req.cmd = msgIn.u.req.cmd;
    msgOut.u.req.trId = msgIn.u.req.trId;

    switch(msgIn.u.req.cmd)
    {
        case EN_TRACE:
        {
            if (msgIn.u.req.param.eTrace.all)
            {
                DiaTrace::GetDiaTrace()->Enable();
            }
            else
            {
                if (msgIn.u.req.param.eTrace.dbg)
                {
                    DiaTrace::GetDiaTrace()->Enable(DIA_DEBUG);
                }
                if (msgIn.u.req.param.eTrace.wrn)
                {
                    DiaTrace::GetDiaTrace()->Enable(DIA_WARNING);
                }
                if (msgIn.u.req.param.eTrace.err)
                {
                    DiaTrace::GetDiaTrace()->Enable(DIA_ERROR);
                }
                if (msgIn.u.req.param.eTrace.crt)
                {
                    DiaTrace::GetDiaTrace()->Enable(DIA_CRITICAL);
                }
            } 
            msgOut.u.res.rCode = RC_SUCCESS;
            break;
        }
        case DIS_TRACE:
        {
            if (msgIn.u.req.param.dTrace.all)
            {
                DiaTrace::GetDiaTrace()->Disable();
            }
            else
            {
                if (msgIn.u.req.param.dTrace.dbg)
                {
                    DiaTrace::GetDiaTrace()->Disable(DIA_DEBUG);
                }
                if (msgIn.u.req.param.dTrace.wrn)
                {
                    DiaTrace::GetDiaTrace()->Disable(DIA_WARNING);
                }
                if (msgIn.u.req.param.dTrace.err)
                {
                    DiaTrace::GetDiaTrace()->Disable(DIA_ERROR);
                }
                if (msgIn.u.req.param.dTrace.crt)
                {
                    DiaTrace::GetDiaTrace()->Disable(DIA_CRITICAL);
                }
            }
            msgOut.u.res.rCode = RC_SUCCESS;
            break;
        }
        case EN_STATS:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            if(diaMgmt->EnableStatistics() != ITS_SUCCESS)
            {
                DT_ERR((" Failed Enabled statistics"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case DIS_STATS:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            if(diaMgmt->DisableStatistics() != ITS_SUCCESS)
            {
                DT_ERR((" Failed Disable statistics"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case RESET_STATS:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            if(diaMgmt->ResetStackStats() != ITS_SUCCESS)
            {
                DT_ERR((" Failed reset statistics"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case START_ALL_PEERS:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            if(diaMgmt->StartAllPeers() != ITS_SUCCESS)
            {
                DT_ERR((" Failed to start all peers"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case GET_INDC_STATS:
        {
            DM_INDIC_STATS *dStats = &msgOut.u.res.param.indicStats;

            msgOut.u.res.rCode = RC_SUCCESS;
            bool clrFlag = false;
            if (msgIn.u.req.param.statsClearOpt == 1)
            {
                clrFlag = true;
            }

            if(diaMgmt->GetDiaIndStats(dStats, clrFlag) != ITS_SUCCESS)
            {
                DT_ERR((" Failed to get indication stats"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case GET_MISC_STATS:
        {
            DM_MISC_STATS *dStats = &msgOut.u.res.param.miscStats;

            msgOut.u.res.rCode = RC_SUCCESS;
            bool clrFlag = false;
            if (msgIn.u.req.param.statsClearOpt == 1)
            {
                clrFlag = true;
            }

            if(diaMgmt->GetDiaMiscStats(dStats, clrFlag) != ITS_SUCCESS)
            {
                DT_ERR((" Failed to get indication stats"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case GET_SESS_STATS:
        {
            msgOut.u.res.rCode = RC_SUCCESS;

            bool clrFlag = false;
            if (msgIn.u.req.param.statsClearOpt == 1)
            {
                clrFlag = true;
            }

            DM_SESS_STATS *dStats = &msgOut.u.res.param.sessStats;

            if(diaMgmt->GetDiaSessStats(dStats, clrFlag) != ITS_SUCCESS)
            {
                DT_ERR((" Failed to get session stats"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case GET_PEER_STATS:
        {
            msgOut.u.res.rCode = RC_SUCCESS;

            bool clrFlag = false;
            if (msgIn.u.req.param.statsClearOpt == 1)
            {
                clrFlag = true;
            }

            DM_PEER_STATS *dStats = &msgOut.u.res.param.peerStats;

            if(diaMgmt->GetDiaPeerStats(dStats, clrFlag) != ITS_SUCCESS)
            {
                DT_ERR((" Failed to get peer stats"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case GET_PEER_STATUS:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            
            PEER_INFO        pEntry;
            DM_PEER_STATUS*  peerStatus = &msgOut.u.res.param.peerStatus;

            memset(&pEntry, 0, sizeof(PEER_INFO));
            memset(peerStatus, 0, sizeof(DM_PEER_STATUS));

            DM_PEER_INFO* pInfo = &msgIn.u.req.param.peerStatus;

            pEntry.peerName = (const char*)pInfo->peerName;
            pEntry.realmName = (const char*)pInfo->realmName;

            if (diaMgmt->GetDiaPeerStatus((void*)peerStatus, &pEntry) != ITS_SUCCESS)
            {
                DT_ERR(("Failed to Get Peer status"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
 
            break;
        }
        case GET_DIA_TRACE_STATS:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            DM_TRACE* diaTrace = &msgOut.u.res.param.diaTrace;

            if(diaMgmt->GetDiaTrace(diaTrace) != ITS_SUCCESS)
            {
                DT_ERR((" Failed to get dia Trace stats"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case GET_DIA_Q_STATS:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            DM_QUEUE_STATS* qStats = &msgOut.u.res.param.qStats;

            if(diaMgmt->GetDiaQStat((DIA_QUEUE_STATS*)qStats) != ITS_SUCCESS)
            {
                DT_ERR(("Failed to get dia Queue stats"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case ADD_PEER:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            PEER_INFO pEntry;
            DM_PEER_ENTRY *dPeer = &msgIn.u.req.param.addPeer;

            pEntry.peerName      = (const char*)&dPeer->peerName;
            pEntry.realmName     = (const char*)&dPeer->realmName;
            pEntry.type          = (MGMT_TR_TYPE)dPeer->trType;
            pEntry.ipAddr        = (const char*)&dPeer->ipAddr;
            pEntry.port          = dPeer->port;
             
            if (diaMgmt->AddPeer(&pEntry) != ITS_SUCCESS)
            {
                DT_ERR(("Failed to add Peer"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case ADD_ALTERNATE_PEER:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            DM_ALT_PEER_INFO *dAltPeer = &msgIn.u.req.param.addAltPeer;
            ALT_PEER_INFO altPeer;

            /* Convert DM_ALT_PEER_INFO to ALT_PEER_INFO */
            altPeer.peerName         = (const char*)&dAltPeer->peerName;
            altPeer.realmName        = (const char*)&dAltPeer->realmName;
            altPeer.altHost          = (const char*)&dAltPeer->altHost;
            altPeer.altRealmName     = (const char*)&dAltPeer->altRealmName;
            altPeer.isFailoverEnable = dAltPeer->isFailoverEnable;
            altPeer.isFailbackEnable = dAltPeer->isFailbackEnable;
            altPeer.isRedundantMate  = dAltPeer->isRedundantMate;
             
            if (diaMgmt->AddAlternatePeer(&altPeer) != ITS_SUCCESS)
            {
                DT_ERR(("Failed to add alternative Peer"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case MODIFY_ALTERNATE_PEER:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            DM_ALT_PEER_INFO *dAltPeer = &msgIn.u.req.param.modiAltPeer;
            ALT_PEER_INFO altPeer;

            /* Convert DM_ALT_PEER_INFO to ALT_PEER_INFO */
            altPeer.peerName         = (const char*)&dAltPeer->peerName;
            altPeer.realmName        = (const char*)&dAltPeer->realmName;
            altPeer.altHost          = (const char*)&dAltPeer->altHost;
            altPeer.altRealmName     = (const char*)&dAltPeer->altRealmName;
            altPeer.isFailoverEnable = dAltPeer->isFailoverEnable;
            altPeer.isFailbackEnable = dAltPeer->isFailbackEnable;
            altPeer.isRedundantMate  = dAltPeer->isRedundantMate;

            if (diaMgmt->ModifyAlternatePeer(&altPeer) != ITS_SUCCESS)
            {
                DT_ERR(("Failed to Modify alternative Peer"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case REMOVE_ALTERNATE_PEER:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            DM_PEER_INFO* pInfo = &msgIn.u.req.param.rmAltPeer;

            const char* peerName         = (const char*)&pInfo->peerName;
            const char* realmName        = (const char*)&pInfo->realmName;

            if (diaMgmt->RemoveAlternatePeer(peerName, realmName) != ITS_SUCCESS)
            {
                DT_ERR(("Failed to Modify alternative Peer"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case GET_SESSION_TBL_SIZE:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            msgOut.u.res.param.sessTableSize.stats = diaMgmt->GetSessionTableSize();
            break;
        }
        case GET_IDC_CONN_STATUS:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            ITS_UINT clientId = msgIn.u.req.param.clientId;
            DIA_DIST_CONN_INFO* connInfo = 
                     (DIA_DIST_CONN_INFO*) &msgOut.u.res.param.idcConnInfo;

            if (diaMgmt->GetIdcConnStatus(clientId, connInfo) != ITS_SUCCESS)
            {
                DT_ERR(("Failed to Get IDC Connection Table size."));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case START_PEER:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            DM_PEER_INFO *pInfo = &msgIn.u.req.param.strPeer;

            if (diaMgmt->StartPeer((const char *)&pInfo->peerName, 
                                   (const char *)&pInfo->realmName) 
                                   != ITS_SUCCESS)
            {
                DT_ERR(("Failed to start Peer"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case REMOVE_PEER:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            DM_PEER_INFO *pInfo = &msgIn.u.req.param.rmPeer;

            if (diaMgmt->RemovePeer((const char *)&pInfo->peerName, 
                                    (const char *)&pInfo->realmName) 
                                                      != ITS_SUCCESS)
            {
                DT_ERR(("Failed to remove Peer"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case DISCONNECT_PEER:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            DM_PEER_DISC *disPeer = &msgIn.u.req.param.peerDisc;

            if (diaMgmt->DisconnectPeer((const char *)&disPeer->peer.peerName, 
                                    (const char *)&disPeer->peer.realmName, 
                                    disPeer->discCause)  != ITS_SUCCESS)
            {
                DT_ERR(("Failed to disconnect Peer"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case FORCE_DISCONNECT_PEER:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            DM_PEER_DISC *disPeer = &msgIn.u.req.param.peerDisc;
 
            if (diaMgmt->ForceDisconectPeer((const char *)&disPeer->peer.peerName,
                               (const char *)&disPeer->peer.realmName,
                               disPeer->discCause, disPeer->expiry)  != ITS_SUCCESS)
            {
                DT_ERR(("Failed to disconnect Peer"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case DISCONNECT_ALL_PEER:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            ITS_UINT discCause = msgIn.u.req.param.discAllPeers;
            if (diaMgmt->DisconnectAllPeers(discCause) != ITS_SUCCESS)
            {
                DT_ERR(("Failed to disconnect all Peer"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case ADD_REALM:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            DM_REALM_ENTRY *rEntry = &msgIn.u.req.param.addRealm;
            if (diaMgmt->AddRealm((const char *)&rEntry->realmName, 
                                  (const char *)&rEntry->localAction,
                                  rEntry->isProxyEnabled) != ITS_SUCCESS)
            {
                DT_ERR(("Failed to add Realm "));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case REMOVE_REALM:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            DM_REALM_INFO *rInfo = &msgIn.u.req.param.rmRealm;
            if (diaMgmt->RemoveRealm((const char *)&rInfo->realmName) 
                                                      != ITS_SUCCESS) 
            {
                DT_ERR(("Failed to remove Realm "));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case ADD_DESTINATION:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            DESTINATION_INFO dest;

            ConverDestInfo(&msgIn.u.req.param.addDest, &dest); 
            if (diaMgmt->AddDestination(&dest) != ITS_SUCCESS)
            {
                DT_ERR(("Failed to add destination "));
                msgOut.u.res.rCode = RC_FAILURE;
            }

            break;
        }
        case REMOVE_DESTINATION:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            DESTINATION_INFO dest;

            ConverDestInfo(&msgIn.u.req.param.rmDest, &dest);
            if (diaMgmt->RemoveDestination(&dest) != ITS_SUCCESS)
            {
                DT_ERR(("Failed to remove destination "));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case MODIFY_DESTINATION:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            DESTINATION_INFO dest;

            ConverDestInfo(&msgIn.u.req.param.modDest, &dest);
            if (diaMgmt->ModifyDestinationPriority(&dest) != ITS_SUCCESS)
            {
                DT_ERR(("Failed to Modify destination"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case EN_PROXY_INFO_AVP:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            DM_REALM_INFO *rInfo = & msgIn.u.req.param.enProxyInfo;
            if(diaMgmt->SetProxyInfoAVPEnabled((const char*)&rInfo->realmName, 
                                               ITS_TRUE) != ITS_SUCCESS)
            {
                DT_ERR(("Failed to enable proxy info "));
                msgOut.u.res.rCode = RC_FAILURE;
            }
 
            break;
        }
        case DIS_PROXY_INFO_AVP:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            DM_REALM_INFO *rInfo = & msgIn.u.req.param.disProxyInfo;
            if(diaMgmt->SetProxyInfoAVPEnabled((const char*)&rInfo->realmName, 
                                               ITS_FALSE) != ITS_SUCCESS)
            {
                DT_ERR(("Failed to disable proxy info"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case SET_PEER_TIMERS:
        {
            msgOut.u.res.rCode = RC_SUCCESS;

            DM_PEER_TIMER* pTimer = & msgIn.u.req.param.peerTimer;
            if (diaMgmt->SetPeerTimers(pTimer->wd, pTimer->retry, 
                                       pTimer->expiry) != ITS_SUCCESS)
            {
                DT_ERR(("Failed to Set peer timer"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case GET_PEER_TIMERS:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
 
            DM_PEER_TIMER pTimer; 
            if (diaMgmt->GetPeerTimers(pTimer.wd, pTimer.retry,
                                            pTimer.expiry)!= ITS_SUCCESS)
            {
                DT_ERR(("Failed to Get peer timer"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            else 
            {
                msgOut.u.res.param.peerTimer.wd = pTimer.wd;
                msgOut.u.res.param.peerTimer.retry= pTimer.retry;
                msgOut.u.res.param.peerTimer.expiry = pTimer.expiry;
            }           
            break;
        }
        case SET_SESSION_TIMERS:
        {
            msgOut.u.res.rCode = RC_SUCCESS;

            DM_SESS_TIMER* pTimer = &msgIn.u.req.param.sessTimer;
            if (diaMgmt->SetAuthSessionTimers(pTimer->lifeTimeout, 
                                              pTimer->graceTimeout, 
                                              pTimer->sessTimeout) != ITS_SUCCESS)
            {
                DT_ERR(("Failed to Set session timer"));
                msgOut.u.res.rCode = RC_FAILURE;
            }

            break;
        }
        case SET_LOCAL_HOST_INFO:
        {
            msgOut.u.res.rCode = RC_SUCCESS;

            DM_HOST_INFO* pHostInfo = &msgIn.u.req.param.hostInfo;

            if (diaMgmt->SetLocalHostInfo((const char*)pHostInfo->hostName,
                                          (const char*)pHostInfo->realmName) != ITS_SUCCESS)
            {
                DT_ERR(("Failed to Set Local Host info"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case SET_DEFAULT_ROUTE:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            
            DM_PEER_INFO *defRoute = &msgIn.u.req.param.defRoute;

            if (diaMgmt->SetDefaultRoute((const char *)&defRoute->peerName,
                                         (const char *)&defRoute->realmName)
                                                      != ITS_SUCCESS)
            {
                DT_ERR(("Failed to Set Default Route"));
                msgOut.u.res.rCode = RC_FAILURE;
            }

            break;
        }
        case DIA_COMMIT:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            DM_XML_COMMIT *xCommit = & msgIn.u.req.param.xmlCommit;

            if (diaMgmt->DIA_Commit((char*)xCommit->fileName) 
                                                     != ITS_SUCCESS) 
            {
                DT_ERR(("XML Commit failed"));
                msgOut.u.res.rCode = RC_FAILURE;
            }

            break;
        }
        case EN_PEER_DISCOVERY:
        {
            msgOut.u.res.rCode = RC_SUCCESS;

            if (diaMgmt->EnablePeerDiscovery() != ITS_SUCCESS)
            {
                DT_ERR(("Enable Peer Discovery failed"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case DIS_PEER_DISCOVERY:
        {
            msgOut.u.res.rCode = RC_SUCCESS;

            if (diaMgmt->DisablePeerDiscovery() != ITS_SUCCESS)
            {
                DT_ERR(("Disable Peer Discovery failed"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case ADD_TO_DISCOVERY_LIST:
        {
            msgOut.u.res.rCode = RC_SUCCESS;

            DM_PEER_INFO *pInfo = &msgIn.u.req.param.addDiscList;
            if (diaMgmt->InsertIntoDiscoveryList((const char*)pInfo->realmName, 
                                    (const char*)pInfo->peerName) != ITS_SUCCESS)
            {
                DT_ERR(("Insert into Peer Discovery List failed"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case DEL_FROM_DISCOVERY_LIST:
        {
            msgOut.u.res.rCode = RC_SUCCESS;

            DM_PEER_INFO *pInfo = &msgIn.u.req.param.delDiscList;
            if (diaMgmt->RemoveFromDiscoveryList((const char*)pInfo->realmName, 
                                    (const char*)pInfo->peerName) != ITS_SUCCESS)
            {
                DT_ERR(("Remove from Peer Discovery List failed"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case SET_DISCOVERY_INTERVAL:
        {
            msgOut.u.res.rCode = RC_SUCCESS;

            ITS_UINT timerVal  = msgIn.u.req.param.discInterval;
            if (diaMgmt->SetPeerDiscoveryInterval(timerVal) != ITS_SUCCESS)
            {
                DT_ERR(("Set Peer Discovery Timer Failed"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case GET_DISCOVERY_INTERVAL:
        {
             msgOut.u.res.rCode = RC_SUCCESS;

             int timerVal = diaMgmt->GetPeerDiscoveryInterval();
             msgOut.u.res.param.discInterval = timerVal;
             break;
        }
        case SET_HEARTBEAT_INTERVAL:
        {
            msgOut.u.res.rCode = RC_SUCCESS;

            ITS_UINT timerVal  = msgIn.u.req.param.hbInterval;
            if (diaMgmt->SetHBInterval(timerVal) != ITS_SUCCESS)
            {
                DT_ERR(("Set Heartbeat Interval Failed"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case GET_HEARTBEAT_INTERVAL:
        {
             msgOut.u.res.rCode = RC_SUCCESS;

             int timerVal = diaMgmt->GetHBInterval();
             msgOut.u.res.param.hbInterval = timerVal;
             break;
        }
        case SET_HEARTBEAT_RETRY:
        {
            msgOut.u.res.rCode = RC_SUCCESS;

            ITS_UINT retry  = msgIn.u.req.param.hbRetry;
            if (diaMgmt->SetHBRetry(retry) != ITS_SUCCESS)
            {
                DT_ERR(("Set Heartbeat Interval Failed"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case GET_HEARTBEAT_RETRY:
        {
             msgOut.u.res.rCode = RC_SUCCESS;

             int retry = diaMgmt->GetHBRetry();
             msgOut.u.res.param.hbRetry = retry;
             break;
        }
        case GET_HMI_CHECK_INTERVAL:
        {
             msgOut.u.res.rCode = RC_SUCCESS;

             int interv = diaMgmt->GetHMICheckInterval();
             msgOut.u.res.param.hmiInterval = interv;
             break;
        }
        case SET_HMI_CHECK_INTERVAL:
        {
             msgOut.u.res.rCode = RC_SUCCESS;

             int interv = msgIn.u.req.param.hmiInterval; 
             if (diaMgmt->SetHMICheckInterval(interv) != ITS_SUCCESS)
             {
                 DT_ERR(("Set HMI Check Interaval Failed"));
                 msgOut.u.res.rCode = RC_FAILURE;
             }
             break;
        }
        case GET_HMI_TIMEOUT:
        {
             msgOut.u.res.rCode = RC_SUCCESS;

             int val = diaMgmt->GetHMITimeout();
             msgOut.u.res.param.hmiTimeout = val;
             break;
        }
        case SET_HMI_TIMEOUT:
        {
             msgOut.u.res.rCode = RC_SUCCESS;

             int val = msgIn.u.req.param.hmiTimeout;
             if (diaMgmt->SetHMITimeout(val) != ITS_SUCCESS)
             {
                 DT_ERR(("Set HMI Timeout Failed"));
                 msgOut.u.res.rCode = RC_FAILURE;
             }
             break;
        }
        case GET_HMI_RETRY:
        {
             msgOut.u.res.rCode = RC_SUCCESS;

             int val = diaMgmt->GetHMIRetry();
             msgOut.u.res.param.hmiRetry = val;
             break;
        }
        case SET_HMI_RETRY:
        {
             msgOut.u.res.rCode = RC_SUCCESS;

             int val = msgIn.u.req.param.hmiRetry;
             if (diaMgmt->SetHMIRetry(val) != ITS_SUCCESS)
             {
                 DT_ERR(("Set HMI Retry Failed"));
                 msgOut.u.res.rCode = RC_FAILURE;
             }
             break;
        }
        case GET_HMI_HB_INTERVAL:
        {
             msgOut.u.res.rCode = RC_SUCCESS;

             int val = diaMgmt->GetHMIHBInterval();
             msgOut.u.res.param.hmiHBInterval = val;
             break;
        }
        case SET_HMI_HB_INTERVAL:
        {
             msgOut.u.res.rCode = RC_SUCCESS;

             int val = msgIn.u.req.param.hmiHBInterval;
             if (diaMgmt->SetHMIHBInterval(val) != ITS_SUCCESS)
             {
                 DT_ERR(("Set HMI Heartbeat Interval Failed"));
                 msgOut.u.res.rCode = RC_FAILURE;
             }
             break;
        }
        case ENABLE_HMI:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            if (diaMgmt->EnableHMI() != ITS_SUCCESS)
            {
                DT_ERR(("HMI Enabled Failed"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case DISABLE_HMI:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            if (diaMgmt->DisableHMI() != ITS_SUCCESS)
            {
                DT_ERR(("HMI Disable Failed"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case HMI_STATUS:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            msgOut.u.res.param.hmiStatus = ITS_FALSE;

            if (diaMgmt->IsHMIEnabled())
            {
                msgOut.u.res.param.hmiStatus = ITS_TRUE;
            }
            break;
        }
        case SET_OV_LIMIT:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            int maxVal = msgIn.u.req.param.ovLimits.maxTh;
            int minVal = msgIn.u.req.param.ovLimits.minTh;

            if (diaMgmt->SetOvloadThresholds(maxVal, minVal) != ITS_SUCCESS)
            {
                DT_ERR(("Set Overload Failed"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case GET_OV_LIMIT:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            int maxVal, minVal;

            if (diaMgmt->GetOvloadThresholds(maxVal, minVal) != ITS_SUCCESS)
            {
                DT_ERR(("Set Overload Failed"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            else
            {
                msgOut.u.res.param.ovLimits.maxTh = maxVal;
                msgOut.u.res.param.ovLimits.minTh = minVal;
            }
            break;
        }
        case REMOVE_DEFAULT_ROUTE:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            if (diaMgmt->RemoveDefaultRoute() != ITS_SUCCESS)
            {
                DT_ERR(("Remove Default Route Failed"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            break;
        }
        case GET_DEFAULT_ROUTE:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            DESTINATION_INFO dstInfo;
            if (diaMgmt->GetDefaultRoute(&dstInfo) != ITS_SUCCESS)
            {
                DT_ERR(("Get Default Route Failed"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            else
            {
                DM_PEER_INFO *pInfo = NULL;
                pInfo = &msgOut.u.res.param.defRoute;

                //Fixing Buffer not null terminated
                memset(pInfo->peerName, 0, MAX_PARAM_LEN);
                memset(pInfo->realmName, 0, MAX_PARAM_LEN);
                strncpy((char*)pInfo->peerName, dstInfo.peerName, MAX_PARAM_LEN);
                strncpy((char*)pInfo->realmName, dstInfo.peerRealm, MAX_PARAM_LEN);
            }
            break;
        }

        case GET_LOCAL_HOST_INFO:
        {
            msgOut.u.res.rCode = RC_SUCCESS;
            LOCAL_HOST_INFO  lHostInfo;
            if (diaMgmt->GetLocalHostInfo(&lHostInfo) != ITS_SUCCESS)
            {
                DT_ERR(("Get Default Route Failed"));
                msgOut.u.res.rCode = RC_FAILURE;
            }
            else
            {
                DM_HOST_INFO *dHostInfo=NULL;
                dHostInfo = &msgOut.u.res.param.hostInfo;
                strncpy((char*)dHostInfo->hostName, lHostInfo.hostName, MAX_PARAM_LEN);     
                strncpy((char*)dHostInfo->realmName, lHostInfo.realmName, MAX_PARAM_LEN);     
                strncpy((char*)dHostInfo->ipAddr, lHostInfo.ipAddr, MAX_PARAM_LEN);     
            }
            break;
        }
        case SET_ROUTE_SCHEME:
        {
            DT_ERR(("DmsMsgHandler::ProcessMsg SET_ROUTE_SCHEME cmd Received"));
            msgOut.u.res.rCode = RC_SUCCESS;

            DiaConfig *cfg = DiaConfig::GetDiaConfig();
            char szScheme[MAX_ROUTE_SCHEME_LENGTH+1];
            memset(szScheme, 0, MAX_ROUTE_SCHEME_LENGTH+1);

            if (msgIn.u.req.param.routeScheme == DM_ROUTE_ROUND_ROBIN)
            {
                //Correcting Calling risky function
                strncpy(szScheme, "roundrobin", MAX_ROUTE_SCHEME_LENGTH);
                cfg->SetRouteScheme(szScheme);
                routeScheme = IDS_ROUND_ROBIN;
            }
            else
            {
                //Fixing Calling risky function
                strncpy(szScheme, "broadcast", MAX_ROUTE_SCHEME_LENGTH);
                cfg->SetRouteScheme(szScheme);
                routeScheme = IDS_BROADCAST;
            }
            break;
        }
        case GET_ROUTE_SCHEME:
        {
            DT_ERR(("DmsMsgHandler::ProcessMsg GET_ROUTE_SCHEME cmd Received"));
            msgOut.u.res.rCode = RC_SUCCESS;

            if (IDS_ROUND_ROBIN == routeScheme)
            {
                msgOut.u.res.param.routeScheme = DM_ROUTE_ROUND_ROBIN;
            }
            else
            {
                msgOut.u.res.param.routeScheme = DM_ROUTE_BROADCAST;
            }
            break;
        }

        default:
            DT_ERR (("Invalid cmd type"));
            msgOut.u.res.rCode = RC_INVALID_CMD;
            break;
    }
   
    /*
     * Send Response
     */
    if (Encode(&msgOut,&evt) == ITS_SUCCESS)
    {
        PrintEvent(&evt);
        ITS_USHORT dest = TRANSPORT_INSTANCE(dmsHandle);
        if (TRANSPORT_PutEvent(dest, &evt) != ITS_SUCCESS)
        {
            DT_ERR (("Failed to send response"));
            ITS_EVENT_TERM(&evt);
            ret = !ITS_SUCCESS;
        }
    }
    else
    {
        DT_ERR (("Failed to Encode the message"));
        ITS_EVENT_TERM(&evt);
        ret = !ITS_SUCCESS;
    }

    return ret;
}

/*.implementation: DmsMsgHandler::Encode
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
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_INT
DmsMsgHandler::Encode(DM_MSG *msg, ITS_EVENT *ev)
{
    int ret = ITS_SUCCESS;
    int indx = 0, size = 0;
    std::string strBuff="";
    ITS_OCTET tridData[2];
    if (msg->mType != MSG_TYPE_RES)
    {
        DT_ERR(("DmsMsgHandler::Encode:: Message type != Response"));
        ret = !ITS_SUCCESS;
    }

    /* Header */
    ITS_OCTET mType = msg->mType;
    strBuff.append((const char*)&mType,sizeof(ITS_OCTET));
    ITS_OCTET cmd = (ITS_OCTET )msg->u.res.cmd;
    strBuff.append((const char*)&cmd,sizeof(ITS_OCTET));
    ShortToData(tridData, msg->u.res.trId);
    strBuff.append((const char*)tridData, 2);
    ITS_OCTET rCode = (ITS_OCTET )msg->u.res.rCode;
    strBuff.append((const char*)&rCode,sizeof(ITS_OCTET));

    switch (msg->u.res.cmd)
    {
        case GET_INDC_STATS:
        {
            DM_INDIC_STATS *stats = &msg->u.res.param.indicStats;
            EncodeInt(strBuff,stats->numDisconnInd);
            EncodeInt(strBuff,stats->numSessTimeoutInd);
            EncodeInt(strBuff,stats->numAuthLifeTimeoutInd);
            EncodeInt(strBuff,stats->numAuthGraceTimeoutInd);
            EncodeInt(strBuff,stats->numAbortInd);
            EncodeInt(strBuff,stats->numCorruptMsgInd);
            EncodeInt(strBuff,stats->numUnknownInd);
            EncodeInt(strBuff,stats->numFailOverInd);
            EncodeInt(strBuff,stats->numFailBackInd);
            break;
        } 
        case GET_MISC_STATS:
        {
            DM_MISC_STATS *stats = &msg->u.res.param.miscStats;
            EncodeInt(strBuff,stats->redirectEvents);
            EncodeInt(strBuff,stats->totalRetrans);
            EncodeInt(strBuff,stats->hhDropMsgs);
            EncodeInt(strBuff,stats->unknownTypes);
            EncodeInt(strBuff,stats->protocolErrs);
            EncodeInt(strBuff,stats->transientErrs);
            EncodeInt(strBuff,stats->permanentErrs);
            break;
        }
        case GET_SESS_STATS:
        {
            DM_SESS_STATS *stats = &msg->u.res.param.sessStats;
            EncodeDmMsgStats(strBuff, &stats->app);
            EncodeDmMsgStats(strBuff, &stats->ac);
            EncodeDmMsgStats(strBuff, &stats->as);
            EncodeDmMsgStats(strBuff, &stats->ra);
            EncodeDmMsgStats(strBuff, &stats->st);
            EncodeDmMsgStats(strBuff, &stats->err);
            EncodeInt(strBuff, stats->decodeFailure);
            break;
        }
        case GET_PEER_STATS:
        {
            DM_PEER_STATS *stats = &msg->u.res.param.peerStats;
            EncodeDmMsgStats(strBuff, &stats->total);
            EncodeDmMsgStats(strBuff, &stats->ce);
            EncodeDmMsgStats(strBuff, &stats->dw);
            EncodeDmMsgStats(strBuff, &stats->dp);
            break;
        }
        case GET_PEER_STATUS:
        {
            DM_PEER_STATUS *status = &msg->u.res.param.peerStatus;
            EncodeString(strBuff, (ITS_OCTET*)status->peerName);
            EncodeString(strBuff, (ITS_OCTET*)status->realmName);

            EncodeOctet(strBuff, (ITS_OCTET)status->type); 

            EncodeString(strBuff, (ITS_OCTET*)status->ipAddr);
            EncodeShort(strBuff, status->port);

            EncodeOctet(strBuff, (ITS_OCTET)status->pState);

            EncodeInt(strBuff, status->isStatic); 
            EncodeInt(strBuff, status->connEstTime);

            break;
        }
        case GET_SESSION_TBL_SIZE:
        {
            DM_STATS *stats = &msg->u.res.param.sessTableSize;
            EncodeInt(strBuff, stats->stats);
            break;
        }
        case GET_IDC_CONN_STATUS:
        {
            DM_IDC_CONN_INFO *connInfo = &msg->u.res.param.idcConnInfo;
            EncodeInt(strBuff, connInfo->appIdentifier);
            EncodeInt(strBuff, connInfo->appIdType);
            break;
        }
        case GET_DIA_Q_STATS:
        {
            DM_QUEUE_STATS* qStats = &msg->u.res.param.qStats;
            EncodeInt(strBuff, qStats->upQCount);
            EncodeInt(strBuff, qStats->downQCount);
            break;
        }
        case GET_DIA_TRACE_STATS:
        {
            DM_TRACE* trace = &msg->u.res.param.diaTrace;

            EncodeInt(strBuff, trace->all);
            EncodeInt(strBuff, trace->dbg);
            EncodeInt(strBuff, trace->wrn);
            EncodeInt(strBuff, trace->err);
            EncodeInt(strBuff, trace->crt);
            break;
        }
        case GET_DISCOVERY_INTERVAL:
        {
            EncodeInt(strBuff, msg->u.res.param.discInterval);
            break;
        }
        case GET_HEARTBEAT_INTERVAL:
        {
            EncodeInt(strBuff, msg->u.res.param.hbInterval);
            break;
        }
        case GET_HEARTBEAT_RETRY:
        {
            EncodeInt(strBuff, msg->u.res.param.hbRetry);
            break;
        }
        case GET_HMI_CHECK_INTERVAL:
        {
            EncodeInt(strBuff, msg->u.res.param.hmiInterval);
            break;
        }
        case GET_HMI_TIMEOUT:
        {
            EncodeInt(strBuff, msg->u.res.param.hmiTimeout);
            break;
        }
        case GET_HMI_RETRY:
        {
            EncodeInt(strBuff, msg->u.res.param.hmiRetry);
            break;
        }
        case GET_HMI_HB_INTERVAL:
        {
            EncodeInt(strBuff, msg->u.res.param.hmiHBInterval);
            break;
        }
        case HMI_STATUS:
        {
            EncodeInt(strBuff, msg->u.res.param.hmiStatus);
            break;
        }
        case GET_OV_LIMIT:
        {
            EncodeInt(strBuff, msg->u.res.param.ovLimits.maxTh);
            EncodeInt(strBuff, msg->u.res.param.ovLimits.minTh);
            break;
        }
        case GET_DEFAULT_ROUTE:
        {
            DM_PEER_INFO *pInfo = &msg->u.res.param.defRoute;
            EncodeString(strBuff, (ITS_OCTET*)pInfo->peerName);
            EncodeString(strBuff, (ITS_OCTET*)pInfo->realmName);
            break;
        }
        case GET_LOCAL_HOST_INFO:
        {
            DM_HOST_INFO *hInfo = &msg->u.res.param.hostInfo;
            EncodeString(strBuff, (ITS_OCTET*)hInfo->hostName);
            EncodeString(strBuff, (ITS_OCTET*)hInfo->realmName);
            EncodeString(strBuff, (ITS_OCTET*)hInfo->ipAddr);
            break;

        }  
        case GET_PEER_TIMERS:
        {
            DM_PEER_TIMER *pTimer = &msg->u.res.param.peerTimer;
            EncodeInt(strBuff, pTimer->wd); 
            EncodeInt(strBuff, pTimer->retry); 
            EncodeInt(strBuff, pTimer->expiry); 
            break;
        }
        case GET_ROUTE_SCHEME:
        {
            ITS_OCTET val = msg->u.res.param.routeScheme;
            EncodeOctet(strBuff, val);
            break;
        }



        default:
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

/*.implementation:DmsMsgHandler::Decode
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
DmsMsgHandler::Decode(DM_MSG *msg, ITS_EVENT *ev)
{
    int ret = ITS_SUCCESS;
    int indx = 0;
    ITS_OCTET *evData = ev->data;
    /* Decode Header */
    msg->mType = (DM_MSG_TYPE)evData[indx++];
    msg->u.req.cmd = (DM_CMD)evData[indx++];
    msg->u.req.trId = DataToShort(&evData[indx]);
    indx += sizeof(ITS_USHORT);

    if (msg->mType == MSG_TYPE_RES)
    {
        DT_ERR(("DmsMsgHandler::Decode Message type != Request"));
        return !ITS_SUCCESS;
    }

    switch(msg->u.req.cmd)
    {
        case EN_TRACE:
        case DIS_TRACE:
        {
            ITS_OCTET trData = ev->data[indx];
            DM_TRACE *trace = NULL;
            if (msg->u.req.cmd == EN_TRACE)
            {
                trace = &msg->u.req.param.eTrace;
            }
            else
            {
                trace = &msg->u.req.param.dTrace;
            }
            trace->all = (trData & DM_BIT_1)?ITS_TRUE:ITS_FALSE;
            trace->dbg = (trData & DM_BIT_2)?ITS_TRUE:ITS_FALSE;
            trace->wrn = (trData & DM_BIT_3)?ITS_TRUE:ITS_FALSE;
            trace->err = (trData & DM_BIT_4)?ITS_TRUE:ITS_FALSE;
            trace->crt = (trData & DM_BIT_5)?ITS_TRUE:ITS_FALSE;
            break;
        }
        case ADD_PEER:
        {
            int len = 0;
            DM_PEER_ENTRY *addPeer = &msg->u.req.param.addPeer;

            if ((len = DecodeString(&evData[indx], addPeer->peerName)) == -1)
            {
                DT_ERR(("peername decodeString failed"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len = DecodeString(&evData[indx], addPeer->realmName)) == -1)
            {
                DT_ERR(("DecodeString failed:: realmName"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            ITS_OCTET octVar = 0;
            if ((len = DecodeOctet(&evData[indx], octVar)) == -1)
            {
                DT_ERR(("DecodeOctet failed:: trType"));
                ret = !ITS_SUCCESS;
                break;
            }
            addPeer->trType = (DM_DIA_TR_TYPE)octVar;
            indx += len;

            if ((len = DecodeString(&evData[indx], addPeer->ipAddr)) == -1)
            {
                DT_ERR(("DecodeString failed:: ipAddr"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len = DecodeShort(&evData[indx], addPeer->port)) == -1)
            {
                DT_ERR(("DecodeShort failed:: port"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            break;
        }
        case ADD_ALTERNATE_PEER:
        case MODIFY_ALTERNATE_PEER:
        {
            int len = 0;
            //Fixing Expression has no effect
            DM_ALT_PEER_INFO *altPeer = NULL;

            if (msg->u.req.cmd == ADD_ALTERNATE_PEER)
            {
                altPeer = &msg->u.req.param.addAltPeer;
            }
            else
            {
                altPeer = &msg->u.req.param.modiAltPeer;
            }

            if ((len = DecodeString(&evData[indx], altPeer->peerName)) == -1)
            {
                DT_ERR(("DecodeString failed:: peerName"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len = DecodeString(&evData[indx], altPeer->realmName)) == -1)
            {
                DT_ERR(("DecodeString failed:: realmName"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len = DecodeString(&evData[indx], altPeer->altHost)) == -1)
            {
                DT_ERR(("DecodeString failed:: altHost"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len = DecodeString(&evData[indx], altPeer->altRealmName))== -1)
            {
                DT_ERR(("DecodeString failed:: altRealmName"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if((len=DecodeOctet(&evData[indx], 
                                (ITS_OCTET&)altPeer->isFailoverEnable))== -1)
            {
                DT_ERR(("DecodeOctet failed:: isFailoverEnable"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if((len=DecodeOctet(&evData[indx], 
                                 (ITS_OCTET&)altPeer->isFailbackEnable))== -1)
            {
                DT_ERR(("DecodeOctet failed:: isFailbackEnable"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if((len=DecodeOctet(&evData[indx], 
                                (ITS_OCTET&)altPeer->isRedundantMate))== -1)
            {
                DT_ERR(("DecodeOctet failed:: isRedundantMate"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            break;
        }
        case REMOVE_ALTERNATE_PEER:
        {
            int len = 0;
            DM_PEER_INFO *pInfo = &msg->u.req.param.rmAltPeer;

            if ((len = DecodeString(&evData[indx], pInfo->peerName)) == -1)
            {
                DT_ERR(("peername decodeString failed"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len = DecodeString(&evData[indx], pInfo->realmName)) == -1)
            {
                DT_ERR(("DecodeString failed:: realmName"));
                ret = !ITS_SUCCESS;
                break;
            }

            indx += len;
            break;
        }
        case GET_PEER_STATUS:
        {
            int len = 0;
            DM_PEER_INFO *pInfo = &msg->u.req.param.peerStatus;
            if ((len = DecodeString(&evData[indx], pInfo->peerName)) == -1)
            {
                DT_ERR(("peername decodeString failed"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len = DecodeString(&evData[indx], pInfo->realmName)) == -1)
            {
                DT_ERR(("DecodeString failed:: realmName"));
                ret = !ITS_SUCCESS;
                break;
            }

            indx += len;

            break;
        }
       
        case SET_LOCAL_HOST_INFO:
        {
            int len = 0;

            DM_HOST_INFO* pHostInfo = &msg->u.req.param.hostInfo;
            if ((len = DecodeString(&evData[indx], pHostInfo->hostName)) == -1)
            {
                DT_ERR(("HostName decodeString failed"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len = DecodeString(&evData[indx], pHostInfo->realmName)) == -1)
            {
                DT_ERR(("DecodeString failed:: Host realmName"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len = DecodeString(&evData[indx], pHostInfo->ipAddr)) == -1)
            {
                DT_ERR(("DecodeString failed:: Host IpAddr"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            break;
        }

        case START_PEER:
        case REMOVE_PEER:
        case SET_DEFAULT_ROUTE:
        {
            int len = 0;
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

            if ((len = DecodeString(&evData[indx], pInfo->peerName)) == -1)
            {
                DT_ERR(("DecodeString failed:: peerName"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len = DecodeString(&evData[indx], pInfo->realmName)) == -1)
            {
                DT_ERR(("DecodeString failed:: realmName"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            break;
        }
        case DISCONNECT_PEER:
        {
            int len = 0;
            DM_PEER_DISC *pDisc = &msg->u.req.param.peerDisc;
            if ((len = DecodeString(&evData[indx], pDisc->peer.peerName)) == -1)
            {
                DT_ERR(("DecodeString failed:: peerName"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len=DecodeString(&evData[indx], pDisc->peer.realmName))== -1)
            {
                DT_ERR(("DecodeString failed:: realmName"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len=DecodeInt(&evData[indx], pDisc->discCause))== -1)
            {
                DT_ERR(("DecodeInt failed:: discCause"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            break;
        }

        case FORCE_DISCONNECT_PEER:
        {       
            int len = 0;
            DM_PEER_DISC *pDisc = &msg->u.req.param.peerDisc;
            if ((len = DecodeString(&evData[indx], pDisc->peer.peerName)) == -1)
            {
                DT_ERR(("DecodeString failed:: peerName"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len=DecodeString(&evData[indx], pDisc->peer.realmName))== -1)
            {                       
                DT_ERR(("DecodeString failed:: realmName"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len=DecodeInt(&evData[indx], pDisc->discCause))== -1)
            {
                DT_ERR(("DecodeInt failed:: discCause"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len=DecodeInt(&evData[indx], pDisc->expiry))== -1)
            {
                DT_ERR(("DecodeInt failed:: expiry"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            break;
        }

        case DISCONNECT_ALL_PEER:
        {
            int len = 0;
            ITS_UINT* discCause = &msg->u.req.param.discAllPeers;
            if ((len=DecodeInt(&evData[indx], *discCause))== -1)
            {
                DT_ERR(("DecodeInt failed:: discCause"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;

            break;
        }
        case GET_IDC_CONN_STATUS:
        {
            int len = 0;
            ITS_UINT *clientId = &msg->u.req.param.clientId;

            if ((len=DecodeInt(&evData[indx], *clientId))== -1)
            {
                DT_ERR(("DecodeInt failed:: ClientID"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;

            break;
        }
        case ADD_REALM:
        {
            int len = 0;
            DM_REALM_ENTRY *rEntry = &msg->u.req.param.addRealm;
            if ((len=DecodeString(&evData[indx], rEntry->realmName))== -1)
            {
                DT_ERR(("DecodeString failed:: realmName"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len=DecodeString(&evData[indx], rEntry->localAction))== -1)
            {
                DT_ERR(("DecodeString failed:: localAction"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len=DecodeOctet(&evData[indx], 
                                 (ITS_OCTET&)rEntry->isProxyEnabled))== -1)
            {
                DT_ERR(("DecodeString failed:: isProxyEnabled"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            break;
        }
        case REMOVE_REALM:
        case EN_PROXY_INFO_AVP:
        case DIS_PROXY_INFO_AVP:
        {
            int len = 0;
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

            if ((len=DecodeString(&evData[indx], rInfo->realmName))== -1)
            {
                DT_ERR(("DecodeString failed:: realmName"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            break;
        }
        case SET_PEER_TIMERS:
        {
            int len = 0;
            DM_PEER_TIMER* peerTimer = &msg->u.req.param.peerTimer;

            if ((len=DecodeInt(&evData[indx], peerTimer->wd))== -1)
            {
                DT_ERR(("DecodeInt failed:: Watchdog"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len=DecodeInt(&evData[indx], peerTimer->retry))== -1)
            {
                DT_ERR(("DecodeInt failed:: Retry"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len=DecodeInt(&evData[indx], peerTimer->expiry))== -1)
            {
                DT_ERR(("DecodeInt failed:: Expiry"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            break; 
        }
        case SET_SESSION_TIMERS:
        {
            int len = 0;

            DM_SESS_TIMER* sessTimer = &msg->u.req.param.sessTimer;
            if ((len=DecodeInt(&evData[indx], sessTimer->sessTimeout))== -1)
            {
                DT_ERR(("DecodeInt failed:: Session Timeout"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len=DecodeInt(&evData[indx], sessTimer->lifeTimeout))== -1)
            {
                DT_ERR(("DecodeInt failed:: Lifetimeout"));
                ret = !ITS_SUCCESS;
                break;
            }   
            indx += len;
            if ((len=DecodeInt(&evData[indx], sessTimer->graceTimeout))== -1)
            {
                DT_ERR(("DecodeInt failed:: GraceTimeout"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            break;
        }
        case ADD_DESTINATION:
        case REMOVE_DESTINATION:
        case MODIFY_DESTINATION:
        {
            int len = 0;
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
            if ((len=DecodeString(&evData[indx], dest->realmName))== -1)
            {
                DT_ERR(("DecodeString failed:: realmName"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len=DecodeString(&evData[indx], dest->peerName))== -1)
            {
                DT_ERR(("DecodeString failed:: peerName"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len=DecodeString(&evData[indx], dest->peerRealm))== -1)
            {
                DT_ERR(("DecodeString failed:: peerRealm"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len=DecodeInt(&evData[indx], dest->appId))== -1)
            {
                DT_ERR(("DecodeInt failed:: appId"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len=DecodeInt(&evData[indx], dest->vendId))== -1)
            {
                DT_ERR(("DecodeInt failed:: vendId"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len=DecodeInt(&evData[indx], dest->priority))== -1)
            {
                DT_ERR(("DecodeInt failed:: priority"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            break;
        }
        case DIA_COMMIT:
        {
            int len = 0;
            DM_XML_COMMIT *xCommit = &msg->u.req.param.xmlCommit;
            if ((len=DecodeString(&evData[indx], xCommit->fileName))== -1)
            {
                DT_ERR(("DecodeInt failed:: priority"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            break;
        }
        case ADD_TO_DISCOVERY_LIST:
        {
            int len = 0;
            DM_PEER_INFO *pInfo = &msg->u.req.param.addDiscList;

            if ((len = DecodeString(&evData[indx], pInfo->peerName)) == -1)
            {
                DT_ERR(("peername decodeString failed"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            if ((len = DecodeString(&evData[indx], pInfo->realmName)) == -1)
            {
                DT_ERR(("DecodeString failed:: realmName"));
                ret = !ITS_SUCCESS;
                break;
            }

            indx += len;
            break;
        }
        case DEL_FROM_DISCOVERY_LIST:
        {
            int len = 0;
            DM_PEER_INFO *pInfo = &msg->u.req.param.delDiscList;
        
            if ((len = DecodeString(&evData[indx], pInfo->peerName)) == -1)
            {
                DT_ERR(("peername decodeString failed"));
                ret = !ITS_SUCCESS;
                break;
            }   
            indx += len;
            if ((len = DecodeString(&evData[indx], pInfo->realmName)) == -1)
            {
                DT_ERR(("DecodeString failed:: realmName"));
                ret = !ITS_SUCCESS;
                break;
            }   

            indx += len;
            break;
        }
        case SET_DISCOVERY_INTERVAL:
        {
            int len = 0;
            if ((len = DecodeInt(&evData[indx], msg->u.req.param.discInterval))
                                                                    == -1)
            {
                DT_ERR(("DecodeInt failed::"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            break;
        }
        case SET_HEARTBEAT_INTERVAL:
        {
            int len = 0;
            if ((len = DecodeInt(&evData[indx], msg->u.req.param.hbInterval))
                                                                    == -1)
            {
                DT_ERR(("DecodeInt failed::"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            break;
        }
        case SET_HEARTBEAT_RETRY:
        {
            int len = 0;
            if ((len = DecodeInt(&evData[indx], msg->u.req.param.hbRetry))
                                                                    == -1)
            {
                DT_ERR(("DecodeInt failed::"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            break;
        }
        case SET_HMI_CHECK_INTERVAL:
        {
            int len = 0;
            if ((len = DecodeInt(&evData[indx], msg->u.req.param.hmiInterval))
                                                                    == -1)
            {
                DT_ERR(("DecodeInt failed::"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            break;
        }
        case SET_HMI_TIMEOUT:
        {
            int len = 0;
            if ((len = DecodeInt(&evData[indx], msg->u.req.param.hmiTimeout))
                                                                    == -1)
            {
                DT_ERR(("DecodeInt failed::"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            break;
        }
        case SET_HMI_RETRY:
        {
            int len = 0;
            if ((len = DecodeInt(&evData[indx], msg->u.req.param.hmiRetry))
                                                                    == -1)
            {
                DT_ERR(("DecodeInt failed::"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            break;
        }
        case SET_HMI_HB_INTERVAL:
        {
            int len = 0;
            if ((len = DecodeInt(&evData[indx], msg->u.req.param.hmiHBInterval))
                                                                    == -1)
            {
                DT_ERR(("DecodeInt failed::"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            break;
        }
        case SET_OV_LIMIT:
        {
            int len = 0;
            if ((len = DecodeInt(&evData[indx], msg->u.req.param.ovLimits.maxTh))
                                                                    == -1)
            {
                DT_ERR(("DecodeInt failed::"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;

            if ((len = DecodeInt(&evData[indx], msg->u.req.param.ovLimits.minTh))
                                                                    == -1)
            {
                DT_ERR(("DecodeInt failed::"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;

            break;
        }
        case GET_INDC_STATS:
        case GET_PEER_STATS:
        case GET_MISC_STATS:
        case GET_SESS_STATS:
        {
            int len = 0;
            if ((len = DecodeInt(&evData[indx], msg->u.req.param.statsClearOpt))
                                                                    == -1)
            {
                DT_ERR(("DecodeInt failed::"));
                ret = !ITS_SUCCESS;
                break;
            }
            indx += len;
            break;
        }
        case SET_ROUTE_SCHEME:
        {
            int len = 0;
            ITS_OCTET octVar = 0;

            if ((len = DecodeOctet(&evData[indx], octVar)) == -1)
            {
                DT_ERR(("DecodeOctet failed:: route scheme"));
                ret = !ITS_SUCCESS;
                break;
            }
            msg->u.req.param.routeScheme = (DM_ROUTE_SCHEME)octVar;
            indx += len;

            break;
        }
        default:
            break;
    }
    return ret;
}
