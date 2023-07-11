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
 *  ID: $Id: dmc_api.cpp,v 1.15 2010/08/19 11:22:23 nvijikumar Exp $
 *
 *  LOG: $Log: dmc_api.cpp,v $
 *  LOG: Revision 1.15  2010/08/19 11:22:23  nvijikumar
 *  LOG: Porting changes from B-MOTO-IDIA-0421-00
 *  LOG: 1. New Overload implimentation changes are not being ported.
 *  LOG: 2. Force disconnect changes are not being ported
 *  LOG:
 *  LOG: Revision 1.14  2009/10/14 10:51:50  sureshj
 *  LOG: forceDisconectPeer, getPeerTimers, GetLocalHostInfo mml APIs
 *  LOG: added. (motorola helpDesk issues 2219, 2238)
 *  LOG:
 *  LOG: Revision 1.13  2009/09/07 05:04:08  rajeshak
 *  LOG: MML Support to set/get HMI Heartbeat interval.
 *  LOG:
 *  LOG: Revision 1.12  2009/07/24 09:45:02  rajeshak
 *  LOG: Following Changes are included
 *  LOG:  1. New MML API's added to get/remove default route,get/set overload limits
 *  LOG:     Enable/Disable HMI
 *  LOG:  2. Stats changes (to include option to clear stats in get)
 *  LOG:
 *  LOG: Revision 1.11  2009/07/13 12:14:41  rajeshak
 *  LOG: Converting HMITimeout value into milli sec.
 *  LOG:
 *  LOG: Revision 1.10  2009/07/13 08:32:16  rajeshak
 *  LOG: New MML API to set/get HMI Retry value.
 *  LOG:
 *  LOG: Revision 1.9  2009/06/29 14:57:28  rajeshak
 *  LOG: 1. MML Commands added to set HMI Check Interval and Timeout.
 *  LOG: 2. Changes for Queue stats and session table size.
 *  LOG:
 *  LOG: Revision 1.8  2009/05/11 06:32:53  rajeshak
 *  LOG: API to Get/Set Heartbeat Interval changes
 *  LOG:
 *  LOG: Revision 1.7  2009/04/13 13:48:24  rajeshak
 *  LOG: MML Api added for Peer discovery and modify destination priority.
 *  LOG:
 *  LOG: Revision 1.6  2009/03/26 06:01:53  nvijikumar
 *  LOG: GetPeerStatus API Support
 *  LOG:
 *  LOG: Revision 1.5  2009/03/26 05:26:26  nvijikumar
 *  LOG: GetDiaMiscStats and ResetAllStats API Support
 *  LOG:
 *  LOG: Revision 1.4  2009/03/19 08:51:21  rajeshak
 *  LOG: Added new SetDefaultRoute API to set default route in realm table.
 *  LOG:
 *  LOG: Revision 1.3  2009/03/18 12:59:27  rajeshak
 *  LOG: Enhanced MML API support.
 *  LOG:
 *  LOG: Revision 1.2  2009/03/10 10:37:33  sureshj
 *  LOG: Issue id 1734.
 *  LOG:
 *  LOG: Revision 1.1  2009/03/02 04:39:44  nvijikumar
 *  LOG: Initial draft for MML API Support
 *  LOG:
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: dmc_api.cpp,v 1.15 2010/08/19 11:22:23 nvijikumar Exp $"

#include <stdlib.h>
#include <string.h>
#include <its++.h>
#include <engine++.h>

#include <dmc_common.h>
#include <dmc_api.h>

void
DMCApi::AllocateTransactionId(ITS_USHORT &transcId)
{
    static ITS_USHORT trId;
    DMC_TRACE_DBG(("AllocateTransactionId"));

    MUTEX_AcquireMutex(&guard);

    /* Allocation of Session index */
    trId++;
    if (!trId)
    {
        trId++;
    }
    else if (trId >= 32000)
    {
        trId = 1;
    }

    transcId = trId;

    MUTEX_ReleaseMutex(&guard);

}

int 
DMCApi::AddPeer(DM_PEER_ENTRY* pEntry, ITS_USHORT trId)
{
    if (pEntry == NULL)
    {
        return !ITS_SUCCESS;
    }
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG)); 
    msg.mType      = MSG_TYPE_REQ;
    msg.u.req.cmd  = ADD_PEER;
    msg.u.req.trId = trId;
    memcpy(&msg.u.req.param.addPeer, pEntry, sizeof(DM_PEER_ENTRY));
    return Send(&msg);
}

int 
DMCApi::AddAlternatePeer(DM_ALT_PEER_INFO* aEntry, ITS_USHORT trId)
{
    if (aEntry == NULL)
    {
        return !ITS_SUCCESS;
    }
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType      = MSG_TYPE_REQ;
    msg.u.req.cmd  = ADD_ALTERNATE_PEER;
    msg.u.req.trId = trId;
    memcpy(&msg.u.req.param.addAltPeer, aEntry, sizeof(DM_ALT_PEER_INFO));
    return Send(&msg);
}

int
DMCApi::ModifyAlternatePeer(DM_ALT_PEER_INFO* aEntry, ITS_USHORT trId)
{
    if (aEntry == NULL)
    {
        return !ITS_SUCCESS;
    }
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType      = MSG_TYPE_REQ;
    msg.u.req.cmd  = MODIFY_ALTERNATE_PEER;
    msg.u.req.trId = trId;
    memcpy(&msg.u.req.param.modiAltPeer, aEntry, sizeof(DM_ALT_PEER_INFO));
    return Send(&msg);
}

int
DMCApi::RemoveAlternatePeer(const char* hostName, const char* realmName, ITS_USHORT trId)
{
    if ((hostName == NULL) || (realmName == NULL))
    {
        return !ITS_SUCCESS;
    }
    DM_MSG msg;    
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType      = MSG_TYPE_REQ;
    msg.u.req.cmd  = REMOVE_ALTERNATE_PEER;
    msg.u.req.trId = trId;

    DM_PEER_INFO *pInfo = &msg.u.req.param.rmAltPeer;
    memcpy(pInfo->peerName, hostName, strlen(hostName));
    memcpy(pInfo->realmName, realmName, strlen(realmName));
    return Send(&msg);
}

int 
DMCApi::StartAllPeers(ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType      = MSG_TYPE_REQ;
    msg.u.req.cmd  = START_ALL_PEERS;
    msg.u.req.trId = trId;
    return Send(&msg);
}

int 
DMCApi::StartPeer(const char* hostName, const char* realmName, ITS_USHORT trId)
{
    if (hostName == NULL || realmName == NULL)
    {
        return !ITS_SUCCESS;
    }
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = START_PEER;
    msg.u.req.trId      = trId;
    DM_PEER_INFO *pInfo = &msg.u.req.param.strPeer;
    memcpy(pInfo->peerName, hostName, strlen(hostName));
    memcpy(pInfo->realmName, realmName, strlen(realmName));
    return Send(&msg);
}

int 
DMCApi::RemovePeer(const char* hostName, const char* realmName, ITS_USHORT trId)
{
    if (hostName == NULL || realmName == NULL)
    {
        return !ITS_SUCCESS;
    }
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = REMOVE_PEER;
    msg.u.req.trId      = trId;
    DM_PEER_INFO *pInfo = &msg.u.req.param.rmPeer;
    memcpy(pInfo->peerName, hostName, strlen(hostName));
    memcpy(pInfo->realmName, realmName, strlen(realmName));
    return Send(&msg);
}

int
DMCApi::GetPeerStatus(const char* hostName, const char* realmName, ITS_USHORT trId)
{
    if (hostName == NULL || realmName == NULL)
    {
        return !ITS_SUCCESS;
    }
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = GET_PEER_STATUS;
    msg.u.req.trId      = trId;
    DM_PEER_INFO *pInfo = &msg.u.req.param.peerStatus;
    memcpy(pInfo->peerName, hostName, strlen(hostName));
    memcpy(pInfo->realmName, realmName, strlen(realmName));
    return Send(&msg);
}

int 
DMCApi::DisconnectPeer(const char* hostName, const char* realmName, 
                       ITS_INT disCause, ITS_USHORT trId)
{
    if (hostName == NULL || realmName == NULL)
    {
        return !ITS_SUCCESS;
    }
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = DISCONNECT_PEER;
    msg.u.req.trId      = trId;
    DM_PEER_DISC *pDisc = &msg.u.req.param.peerDisc;
    pDisc->discCause    = disCause;
    memcpy(pDisc->peer.peerName, hostName, strlen(hostName));
    memcpy(pDisc->peer.realmName, realmName, strlen(realmName));
    return Send(&msg);
}

int 
DMCApi::ForceDisconnectPeer(const char* hostName, const char* realmName, 
                       ITS_UINT disCause, ITS_INT expiry, ITS_USHORT trId)
{
    if (hostName == NULL || realmName == NULL)
    {
        return !ITS_SUCCESS;
    }
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = FORCE_DISCONNECT_PEER;
    msg.u.req.trId      = trId;
    DM_PEER_DISC *pDisc = &msg.u.req.param.peerDisc;
    pDisc->expiry    = expiry;
    pDisc->discCause  = disCause;
    memcpy(pDisc->peer.peerName, hostName, strlen(hostName));
    memcpy(pDisc->peer.realmName, realmName, strlen(realmName));
    return Send(&msg);
}

int 
DMCApi::AddRealm(const char* realmName,const char* localAction,
                 ITS_BOOLEAN isProxyEnabled, ITS_USHORT trId)
{
    if (localAction == NULL || realmName == NULL)
    {
        return !ITS_SUCCESS;
    }
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType              = MSG_TYPE_REQ;
    msg.u.req.cmd          = ADD_REALM;
    msg.u.req.trId         = trId;
    DM_REALM_ENTRY *aRealm = &msg.u.req.param.addRealm;
    aRealm->isProxyEnabled = isProxyEnabled;
    memcpy(aRealm->realmName, realmName, strlen(realmName));
    memcpy(aRealm->localAction, localAction, strlen(localAction));
    return Send(&msg);
}

int 
DMCApi::RemoveRealm(const char* realmName, ITS_USHORT trId)
{
    if (realmName == NULL)
    {
        return !ITS_SUCCESS;
    }
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType            = MSG_TYPE_REQ;
    msg.u.req.cmd        = REMOVE_REALM;
    msg.u.req.trId       = trId;

    DM_REALM_INFO *rInfo = &msg.u.req.param.rmRealm;
    memcpy(rInfo->realmName, realmName, strlen(realmName));
    return Send(&msg);
}

int 
DMCApi::AddDestination(DM_DEST_INFO* dest, ITS_USHORT trId)
{
    if (dest == NULL)
    {
        return !ITS_SUCCESS;
    }
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType              = MSG_TYPE_REQ;
    msg.u.req.cmd          = ADD_DESTINATION;
    msg.u.req.trId         = trId;
    DM_DEST_INFO *dInfo    = &msg.u.req.param.addDest;
    memcpy(dInfo, dest, sizeof(DM_DEST_INFO));
    return Send(&msg);
}

int 
DMCApi::RemoveDestination(DM_DEST_INFO* dest, ITS_USHORT trId)
{
    if (dest == NULL)
    {
        return !ITS_SUCCESS;
    }
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType              = MSG_TYPE_REQ;
    msg.u.req.cmd          = REMOVE_DESTINATION;
    msg.u.req.trId         = trId;
    DM_DEST_INFO *dInfo    = &msg.u.req.param.rmDest;
    memcpy(dInfo, dest, sizeof(DM_DEST_INFO));
    return Send(&msg);
}

int
DMCApi::ModifyPriority(DM_DEST_INFO* dest, ITS_USHORT trId)
{
    if (dest == NULL)
    {
        return !ITS_SUCCESS;
    }
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType              = MSG_TYPE_REQ;
    msg.u.req.cmd          = MODIFY_DESTINATION;
    msg.u.req.trId         = trId;
    DM_DEST_INFO *dInfo    = &msg.u.req.param.modDest;
    memcpy(dInfo, dest, sizeof(DM_DEST_INFO));
    return Send(&msg);
}

int 
DMCApi::EnableProxyInfoAVP(const char* realmName, ITS_USHORT trId)
{
    if (realmName == NULL)
    {
        return !ITS_SUCCESS;
    }
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType              = MSG_TYPE_REQ;
    msg.u.req.cmd          = EN_PROXY_INFO_AVP;
    msg.u.req.trId         = trId;

    DM_REALM_INFO *rInfo   = &msg.u.req.param.enProxyInfo;
    memcpy(rInfo->realmName, realmName, strlen(realmName));
    return Send(&msg);
}

int 
DMCApi::DisableProxyInfoAVP(const char* realmName, ITS_USHORT trId)
{
    if (realmName == NULL)
    {
        return !ITS_SUCCESS;
    }
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType              = MSG_TYPE_REQ;
    msg.u.req.cmd          = DIS_PROXY_INFO_AVP;
    msg.u.req.trId         = trId;

    DM_REALM_INFO *rInfo   = &msg.u.req.param.disProxyInfo;
    memcpy(rInfo->realmName, realmName, strlen(realmName));
    return Send(&msg);
}

int 
DMCApi::DiaCommit(const char * fileName, ITS_USHORT trId)
{
    if (fileName == NULL)
    {
        return !ITS_SUCCESS;
    }
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType             = MSG_TYPE_REQ;
    msg.u.req.cmd         = DIA_COMMIT;
    msg.u.req.trId        = trId;

    DM_XML_COMMIT *xCmt   = &msg.u.req.param.xmlCommit;
    memcpy(xCmt->fileName, fileName, strlen(fileName));
    return Send(&msg);
}

int 
DMCApi::EnableTrace(DM_TRACE *enTrace, ITS_USHORT trId)
{
    if (enTrace == NULL)
    {
        return !ITS_SUCCESS;
    }
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType      = MSG_TYPE_REQ;
    msg.u.req.cmd  = EN_TRACE;
    msg.u.req.trId = trId;

    DM_TRACE *trace   = &msg.u.req.param.eTrace;
    memcpy(trace, enTrace, sizeof(DM_TRACE));
    return Send(&msg);
}

int 
DMCApi::DisableTrace(DM_TRACE *enTrace, ITS_USHORT trId)
{
    if (enTrace == NULL)
    {
        return !ITS_SUCCESS;
    }
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType         = MSG_TYPE_REQ;
    msg.u.req.cmd     = DIS_TRACE;
    msg.u.req.trId    = trId;

    DM_TRACE *trace   = &msg.u.req.param.dTrace;
    memcpy(trace, enTrace, sizeof(DM_TRACE));
    return Send(&msg);
}

/* Get Statistics */
int 
DMCApi::EnableStats(ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType         = MSG_TYPE_REQ;
    msg.u.req.cmd     = EN_STATS;
    msg.u.req.trId    = trId;
    return Send(&msg);

}
int 
DMCApi::DisableStats(ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType         = MSG_TYPE_REQ;
    msg.u.req.cmd     = DIS_STATS;
    msg.u.req.trId    = trId;
    return Send(&msg);
}
int 
DMCApi::GetDiaIndStats(bool clrFlag, ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType         = MSG_TYPE_REQ;
    msg.u.req.cmd     = GET_INDC_STATS;
    msg.u.req.trId    = trId;
    msg.u.req.param.statsClearOpt = 0;

    if (clrFlag)
    {
        msg.u.req.param.statsClearOpt = 1;
    }
    return Send(&msg);

}
int 
DMCApi::GetDiaSessStats(bool clrFlag, ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType         = MSG_TYPE_REQ;
    msg.u.req.cmd     = GET_SESS_STATS;
    msg.u.req.trId    = trId;
    msg.u.req.param.statsClearOpt = 0;

    if (clrFlag)
    {
        msg.u.req.param.statsClearOpt = 1;
    }
    return Send(&msg);
}

int 
DMCApi::GetDiaPeerStats(bool clrFlag, ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType         = MSG_TYPE_REQ;
    msg.u.req.cmd     = GET_PEER_STATS;
    msg.u.req.trId    = trId;
    msg.u.req.param.statsClearOpt = 0;

    if (clrFlag)
    {
        msg.u.req.param.statsClearOpt = 1;
    }
    return Send(&msg);
}

int 
DMCApi::GetDiaTraceStatus(ITS_USHORT trId)
{    
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType         = MSG_TYPE_REQ;
    msg.u.req.cmd     = GET_DIA_TRACE_STATS;
    msg.u.req.trId    = trId;
    return Send(&msg);
}

int 
DMCApi::GetDiaQueueStats(ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType         = MSG_TYPE_REQ;
    msg.u.req.cmd     = GET_DIA_Q_STATS;
    msg.u.req.trId    = trId;
    return Send(&msg);
}

int
DMCApi::ResetAllStats(ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType         = MSG_TYPE_REQ;
    msg.u.req.cmd     = RESET_STATS;
    msg.u.req.trId    = trId;
    return Send(&msg);
}

int
DMCApi::GetDiaMiscStats(bool clrFlag, ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType         = MSG_TYPE_REQ;
    msg.u.req.cmd     = GET_MISC_STATS;
    msg.u.req.trId    = trId;
    msg.u.req.param.statsClearOpt = 0;

    if (clrFlag)
    {
        msg.u.req.param.statsClearOpt = 1;
    }
    return Send(&msg);
}

int 
DMCApi::GetSessionTableSize(ITS_USHORT trId)
{   
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType         = MSG_TYPE_REQ;
    msg.u.req.cmd     = GET_SESSION_TBL_SIZE;
    msg.u.req.trId    = trId;
    return Send(&msg);
}

int
DMCApi::GetIdcConnStatus(ITS_UINT clientID, ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType         = MSG_TYPE_REQ;
    msg.u.req.cmd     = GET_IDC_CONN_STATUS;
    msg.u.req.trId    = trId;

    ITS_UINT* pId = &msg.u.req.param.clientId;
    memcpy(pId, &clientID, sizeof(ITS_UINT));
    return Send(&msg);
}

int 
DMCApi::DisconnectAllPeers(ITS_UINT discCause, ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType         = MSG_TYPE_REQ;
    msg.u.req.cmd     = DISCONNECT_ALL_PEER;
    msg.u.req.trId    = trId;
    
    ITS_UINT* peerDiscCause = &msg.u.req.param.discAllPeers;
    memcpy(peerDiscCause, &discCause, sizeof(ITS_UINT));
    return Send(&msg);
}

int
DMCApi::SetSessionTimers(DM_SESS_TIMER* pTimer, ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType         = MSG_TYPE_REQ;
    msg.u.req.cmd     = SET_SESSION_TIMERS;
    msg.u.req.trId    = trId;

    DM_SESS_TIMER* sessTimer = &msg.u.req.param.sessTimer;
    memcpy(sessTimer, pTimer, sizeof(DM_SESS_TIMER));

    return Send(&msg);
}

int
DMCApi::SetPeerTimers(DM_PEER_TIMER* pTimer, ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType         = MSG_TYPE_REQ;
    msg.u.req.cmd     = SET_PEER_TIMERS;
    msg.u.req.trId    = trId;

    DM_PEER_TIMER* peerTimer = &msg.u.req.param.peerTimer;
    memcpy(peerTimer, pTimer, sizeof(DM_PEER_TIMER));
    return Send(&msg);
}

int
DMCApi::GetPeerTimers(ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType         = MSG_TYPE_REQ;
    msg.u.req.cmd     = GET_PEER_TIMERS;
    msg.u.req.trId    = trId;
 
    return Send(&msg);
}
int 
DMCApi::SetLocalHostInfo(const char* hostName, const char* realmName,
                         const char* publicIp, ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType         = MSG_TYPE_REQ;
    msg.u.req.cmd     = SET_LOCAL_HOST_INFO;
    msg.u.req.trId    = trId;

    DM_HOST_INFO* pHostInfo = &msg.u.req.param.hostInfo;
    memcpy(pHostInfo->hostName, hostName, strlen(hostName));
    memcpy(pHostInfo->realmName, realmName, strlen(realmName));
    memcpy(pHostInfo->ipAddr, publicIp, strlen(publicIp));

    return Send(&msg);
}

int
DMCApi::SetDefaultRoute(const char* hostName, const char* realmName, ITS_USHORT trId)
{
    if (hostName == NULL || realmName == NULL)
    {
        return !ITS_SUCCESS;
    }
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = SET_DEFAULT_ROUTE;
    msg.u.req.trId      = trId;
    DM_PEER_INFO *pInfo = &msg.u.req.param.defRoute;
    memcpy(pInfo->peerName, hostName, strlen(hostName));
    memcpy(pInfo->realmName, realmName, strlen(realmName));
    return Send(&msg);
}

int
DMCApi::EnablePeerDiscovery(ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = EN_PEER_DISCOVERY;
    msg.u.req.trId      = trId;
    return Send(&msg);
}

int 
DMCApi::DisablePeerDiscovery(ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = DIS_PEER_DISCOVERY;
    msg.u.req.trId      = trId;
    return Send(&msg);
}

int 
DMCApi::InsertIntoDiscoveryList(const char* hostName, const char* realmName,
                                ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = ADD_TO_DISCOVERY_LIST;
    msg.u.req.trId      = trId;

    DM_PEER_INFO *pInfo = &msg.u.req.param.addDiscList;
    memcpy(pInfo->peerName, hostName, strlen(hostName));
    memcpy(pInfo->realmName, realmName, strlen(realmName));
    return Send(&msg);
}
    
int 
DMCApi::RemoveFromDiscoveryList(const char* hostName, const char* realmName,
                                ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = DEL_FROM_DISCOVERY_LIST;
    msg.u.req.trId      = trId;

    DM_PEER_INFO *pInfo = &msg.u.req.param.delDiscList;
    memcpy(pInfo->peerName, hostName, strlen(hostName));
    memcpy(pInfo->realmName, realmName, strlen(realmName));
    return Send(&msg);
}

int
DMCApi::SetPeerDiscoveryInterval(ITS_UINT timerVal, ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = SET_DISCOVERY_INTERVAL;
    msg.u.req.trId      = trId;

    msg.u.req.param.discInterval = timerVal;
    return Send(&msg);
}

int
DMCApi::GetPeerDiscoveryInterval(ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = GET_DISCOVERY_INTERVAL;
    msg.u.req.trId      = trId;

    return Send(&msg);
}

int 
DMCApi::SetHeartbeatInterval(ITS_UINT interval, 
                             ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = SET_HEARTBEAT_INTERVAL;
    msg.u.req.trId      = trId;

    msg.u.req.param.hbInterval = interval;
    return Send(&msg);
}

int
DMCApi::GetHeartbeatInterval(ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = GET_HEARTBEAT_INTERVAL;
    msg.u.req.trId      = trId;

    return Send(&msg);
}

int
DMCApi::SetHeartbeatRetry(ITS_UINT retry,
                             ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = SET_HEARTBEAT_RETRY;
    msg.u.req.trId      = trId;

    msg.u.req.param.hbRetry = retry;
    return Send(&msg);
}

int
DMCApi::GetHeartbeatRetry(ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = GET_HEARTBEAT_RETRY;
    msg.u.req.trId      = trId;

    return Send(&msg);
}
int 
DMCApi::SetHMIInterval(ITS_UINT value, ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = SET_HMI_CHECK_INTERVAL;
    msg.u.req.trId      = trId;

    msg.u.req.param.hmiInterval = value;
    return Send(&msg);
}

int 
DMCApi::GetHMIInterval(ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = GET_HMI_CHECK_INTERVAL;
    msg.u.req.trId      = trId;

    return Send(&msg);
}

int 
DMCApi::SetHMITimeout(ITS_UINT value, ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = SET_HMI_TIMEOUT;
    msg.u.req.trId      = trId;

    msg.u.req.param.hmiTimeout = value * 1000;
    return Send(&msg);
}

int 
DMCApi::GetHMITimeout(ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = GET_HMI_TIMEOUT;
    msg.u.req.trId      = trId;

    return Send(&msg);
}

int
DMCApi::SetHMIRetry(ITS_UINT value, ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = SET_HMI_RETRY;
    msg.u.req.trId      = trId;

    msg.u.req.param.hmiRetry = value;
    return Send(&msg);
}

int
DMCApi::GetHMIRetry(ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = GET_HMI_RETRY;
    msg.u.req.trId      = trId;

    return Send(&msg);
}

int 
DMCApi::EnableHMI(ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = ENABLE_HMI;
    msg.u.req.trId      = trId;

    return Send(&msg);
}
int 
DMCApi::DisableHMI(ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = DISABLE_HMI;
    msg.u.req.trId      = trId;

    return Send(&msg);
}

int 
DMCApi::IsHMIEnabled(ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = HMI_STATUS;
    msg.u.req.trId      = trId;

    return Send(&msg);
}

int 
DMCApi::SetHMIHBInterval(ITS_UINT value, ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = SET_HMI_HB_INTERVAL;
    msg.u.req.trId      = trId;

    msg.u.req.param.hmiRetry = value;
    return Send(&msg);
}

int 
DMCApi::GetHMIHBInterval(ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = GET_HMI_HB_INTERVAL;
    msg.u.req.trId      = trId;

    return Send(&msg);
}

int
DMCApi::SetOvloadThresholds(ITS_INT maxT, ITS_INT minT, ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = SET_OV_LIMIT;
    msg.u.req.trId      = trId;

    msg.u.req.param.ovLimits.maxTh = maxT;
    msg.u.req.param.ovLimits.minTh = minT;
    return Send(&msg);
}

int
DMCApi::GetOvloadThresholds(ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = GET_OV_LIMIT;
    msg.u.req.trId      = trId;

    return Send(&msg);
}

int
DMCApi::GetDefaultRoute(ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = GET_DEFAULT_ROUTE;
    msg.u.req.trId      = trId;

    return Send(&msg);
}

int
DMCApi::GetLocalHostInfo(ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = GET_LOCAL_HOST_INFO;
    msg.u.req.trId      = trId;

    return Send(&msg);
}

int
DMCApi::RemoveDefaultRoute(ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = REMOVE_DEFAULT_ROUTE;
    msg.u.req.trId      = trId;

    return Send(&msg);
}

int
DMCApi::GetIdsRouteScheme(ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = GET_ROUTE_SCHEME;
    msg.u.req.trId      = trId;

    return Send(&msg);
}
int
DMCApi::SetIdsRouteScheme(DM_ROUTE_SCHEME route, ITS_USHORT trId)
{
    DM_MSG msg;
    memset(&msg, 0, sizeof(DM_MSG));
    msg.mType           = MSG_TYPE_REQ;
    msg.u.req.cmd       = SET_ROUTE_SCHEME;
    msg.u.req.trId      = trId;

    msg.u.req.param.routeScheme = route;

    return Send(&msg);
}


