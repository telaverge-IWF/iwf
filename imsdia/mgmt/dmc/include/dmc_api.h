/****************************************************************************
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
 * ID: $Id: dmc_api.h,v 1.15 2010/08/19 11:22:23 nvijikumar Exp $
 *
 * LOG: $Log: dmc_api.h,v $
 * LOG: Revision 1.15  2010/08/19 11:22:23  nvijikumar
 * LOG: Porting changes from B-MOTO-IDIA-0421-00
 * LOG: 1. New Overload implimentation changes are not being ported.
 * LOG: 2. Force disconnect changes are not being ported
 * LOG:
 * LOG: Revision 1.14  2009/10/14 10:47:33  sureshj
 * LOG: forceDisconectPeer, getPeerTimers, GetLocalHostInfo mml APIs
 * LOG: added. (motorola helpDesk issues 2219, 2238)
 * LOG:
 * LOG: Revision 1.13  2009/09/17 08:36:29  rajeshak
 * LOG: API to enable/disable DMC hex dump.
 * LOG:
 * LOG: Revision 1.12  2009/09/07 05:04:08  rajeshak
 * LOG: MML Support to set/get HMI Heartbeat interval.
 * LOG:
 * LOG: Revision 1.11  2009/07/24 09:45:02  rajeshak
 * LOG: Following Changes are included
 * LOG:  1. New MML API's added to get/remove default route,get/set overload limits
 * LOG:     Enable/Disable HMI
 * LOG:  2. Stats changes (to include option to clear stats in get)
 * LOG:
 * LOG: Revision 1.10  2009/07/13 08:32:16  rajeshak
 * LOG: New MML API to set/get HMI Retry value.
 * LOG:
 * LOG: Revision 1.9  2009/06/29 14:57:28  rajeshak
 * LOG: 1. MML Commands added to set HMI Check Interval and Timeout.
 * LOG: 2. Changes for Queue stats and session table size.
 * LOG:
 * LOG: Revision 1.8  2009/05/11 06:43:49  nvijikumar
 * LOG: Re-connect functionality is moved to Application
 * LOG:
 * LOG: Revision 1.7  2009/05/11 06:31:47  rajeshak
 * LOG: API to Get/Set Heartbeat Interval changes
 * LOG:
 * LOG: Revision 1.6  2009/04/13 13:47:46  rajeshak
 * LOG: MML Api added for Peer discovery and modify destination priority.
 * LOG:
 * LOG: Revision 1.5  2009/03/26 06:02:15  nvijikumar
 * LOG: GetPeerStatus API Support
 * LOG:
 * LOG: Revision 1.4  2009/03/26 05:27:39  nvijikumar
 * LOG: GetDiaMiscStats and ResetAllStats API Support
 * LOG:
 * LOG: Revision 1.3  2009/03/19 08:50:33  rajeshak
 * LOG: Added new SetDefaultRoute API to set default route in realm table.
 * LOG:
 * LOG: Revision 1.2  2009/03/18 12:58:27  rajeshak
 * LOG: Enhanced MML API support.
 * LOG:
 * LOG: Revision 1.1  2009/03/02 04:39:43  nvijikumar
 * LOG: Initial draft for MML API Support
 * LOG:
 * LOG:
 ****************************************************************************/
#ident "$Id: dmc_api.h,v 1.15 2010/08/19 11:22:23 nvijikumar Exp $"

#ifndef _DMC_API_H
#define _DMC_API_H

#include <string>

#include <dmc_common.h>
#include <dmc_trans.h>

class DMCApi;
static DMCApi *dmcApi = NULL;
extern ITS_BOOLEAN hexEnabled;

/** Interface:
 *      DMCApi 
 *      
 *  Purpose:
 *
 *      DMCApi class is used for\n
 *      a. Initialize client library\n
 *      b. Connect to the server\n
 *      c. Exchange messages\n
 **/
class DMCApi
{
public:
    static DMCApi * GetDmcApi()
    {
        if (dmcApi == NULL)
        {
            dmcApi = new DMCApi;
        }
        return dmcApi;
    }

    ITS_INT 
    Initialize(const ITS_CHAR *host, ITS_INT port)
    {
        EnableTrace();
        if (dmcTrans != NULL)
        {
            return dmcTrans->Initialize(host, port);
        }
        return !ITS_SUCCESS;
    }

    ITS_INT Connect()
    {
        if (dmcTrans != NULL)
        {
            return dmcTrans->Connect();
        }
        return !ITS_SUCCESS;
    };

    void EnableTrace()
    {
        traceEnabled = ITS_TRUE;
    }

    void DisableTrace()
    {
        traceEnabled = ITS_FALSE;
    }

    void EnableHexDump()
    {
        hexEnabled = ITS_TRUE;
    }

    void DisableHexDump()
    {
        hexEnabled = ITS_FALSE;
    }

    ITS_INT
    ReceiveEvent(DM_MSG *msg)
    {
        if (msg == NULL)
        {
            return (ITS_ENULLPTR);
        }
        if (dmcTrans != NULL)
        {
            return dmcTrans->ReceiveEvent(msg);
        }
        return (!ITS_SUCCESS);
    }

    ITS_INT
    CloseConnection()
    {
        if (dmcTrans != NULL)
        {
            return dmcTrans->CloseConnection();
        }
        return (!ITS_SUCCESS);
    }

    ITS_BOOLEAN
    IsConnectionUp()
    {
        if (dmcTrans != NULL)
        {
            return dmcTrans->IsConnectionUp();
        }
        return ITS_FALSE;
    }

    void
    RegisterCallBack(DMC_CB func)
    {
        if (dmcTrans != NULL)
        {
            dmcTrans->RegisterCallBack(func);
        }
    }

    void AllocateTransactionId(ITS_USHORT &transcId);
    int AddPeer(DM_PEER_ENTRY* pEntry, ITS_USHORT trId);
    int AddAlternatePeer(DM_ALT_PEER_INFO* aEntry, ITS_USHORT trId);
    int ModifyAlternatePeer(DM_ALT_PEER_INFO* aEntry, ITS_USHORT trId);
    int RemoveAlternatePeer(const char* hostName, 
                            const char* realmName, ITS_USHORT trId);
    int StartAllPeers(ITS_USHORT trId);
    int StartPeer(const char* hostName, const char* realmName, ITS_USHORT trId);
    int RemovePeer(const char* hostName,const char* realmName, ITS_USHORT trId);
    int DisconnectPeer(const char* hostName, const char* realmName, 
                       ITS_INT disCause, ITS_USHORT trId);
    int ForceDisconnectPeer(const char* hostName, const char* realmName, 
                       ITS_UINT disCause, ITS_INT expiry, ITS_USHORT trId);
    int AddRealm(const char* realmName,const char* localAction,
                 ITS_BOOLEAN isProxyEnabled, ITS_USHORT trId);
    int RemoveRealm(const char* realmName, ITS_USHORT trId);
    int SetDefaultRoute(const char* hostName, const char* realmName,
                                                   ITS_USHORT trId);
    int AddDestination(DM_DEST_INFO* dest, ITS_USHORT trId);
    int RemoveDestination(DM_DEST_INFO* destInfo, ITS_USHORT trId);
    int ModifyPriority(DM_DEST_INFO* destInfo, ITS_USHORT trId);
    int EnableProxyInfoAVP(const char* realmName, ITS_USHORT trId);
    int DisableProxyInfoAVP(const char* realmName, ITS_USHORT trId);
    int DiaCommit(const char * filename, ITS_USHORT trId);
    int EnableTrace(DM_TRACE *enTrace, ITS_USHORT trId);
    int DisableTrace(DM_TRACE *enTrace, ITS_USHORT trId);

    int DisconnectAllPeers(ITS_UINT discCause, ITS_USHORT trId);

    /* Get Statistics */
    int EnableStats(ITS_USHORT trId);
    int DisableStats(ITS_USHORT trId);
    int GetDiaIndStats(bool clrFlag, ITS_USHORT trId);
    int GetDiaSessStats(bool clrFlag, ITS_USHORT trId);
    int GetDiaPeerStats(bool clrFlag, ITS_USHORT trId);
    int GetDiaQueueStats(ITS_USHORT trId);
    int GetDiaMiscStats(bool clrFlag, ITS_USHORT trId);
    int ResetAllStats(ITS_USHORT trId);

    int GetSessionTableSize(ITS_USHORT trId);
    int GetIdcConnStatus(ITS_UINT clientID, ITS_USHORT trId);
    int GetDiaTraceStatus(ITS_USHORT trId);
    int GetPeerStatus(const char* hostName, const char* rName, ITS_USHORT trId);

    int SetLocalHostInfo(const char* hostName, const char* realmName,
                         const char* publicIp, ITS_USHORT trId);

    int GetLocalHostInfo(ITS_USHORT trId);
    /* set Timers */
    int SetPeerTimers(DM_PEER_TIMER* pTimer, ITS_USHORT trId);
    int GetPeerTimers(ITS_USHORT trId);
    int SetSessionTimers(DM_SESS_TIMER* pTimer, ITS_USHORT trId);

    int EnablePeerDiscovery(ITS_USHORT trId);
    int DisablePeerDiscovery(ITS_USHORT trId);
    int InsertIntoDiscoveryList(const char* hostName, const char* realmName,
                                ITS_USHORT trId);
    int RemoveFromDiscoveryList(const char* hostName, const char* realmName,
                                ITS_USHORT trId);
    int SetPeerDiscoveryInterval(ITS_UINT timerVal, ITS_USHORT trId);
    int GetPeerDiscoveryInterval(ITS_USHORT trId);
    int SetHeartbeatInterval(ITS_UINT interval, ITS_USHORT trId);
    int GetHeartbeatInterval(ITS_USHORT trId);
    int SetHeartbeatRetry(ITS_UINT retry, ITS_USHORT trId);
    int GetHeartbeatRetry(ITS_USHORT trId);

    int SetHMIInterval(ITS_UINT value, ITS_USHORT trId);
    int GetHMIInterval(ITS_USHORT trId);
    int SetHMITimeout(ITS_UINT value, ITS_USHORT trId);
    int GetHMITimeout(ITS_USHORT trId);
    int SetHMIRetry(ITS_UINT value, ITS_USHORT trId);
    int GetHMIRetry(ITS_USHORT trId);
    int SetHMIHBInterval(ITS_UINT value, ITS_USHORT trId);
    int GetHMIHBInterval(ITS_USHORT trId);

    int EnableHMI(ITS_USHORT trId);
    int DisableHMI(ITS_USHORT trId);
    int IsHMIEnabled(ITS_USHORT trId);
    int SetOvloadThresholds(ITS_INT maxT, ITS_INT minT, ITS_USHORT trId);
    int GetOvloadThresholds(ITS_USHORT trId);

    int GetDefaultRoute(ITS_USHORT trId);
    int RemoveDefaultRoute(ITS_USHORT trId);
    int GetIdsRouteScheme(ITS_USHORT trId);
    int SetIdsRouteScheme(DM_ROUTE_SCHEME route, ITS_USHORT trId);


private:
    DMCApi()
    {
        if (MUTEX_CreateMutex(&guard, 0) != ITS_SUCCESS)
        {
            throw its::Error(ITS_EBADMUTEX, __FILE__, __LINE__);
        }
        dmcTrans = new DmcTransport; 
        if (dmcTrans != NULL)
        {
            dmcTrans->PreInitialize();
        }
    }

    ~DMCApi() 
    {
        MUTEX_DeleteMutex(&guard);
        if (dmcTrans != NULL)
        {
            delete dmcTrans;
            dmcTrans = NULL;
        }
    }

    ITS_INT
    Send(DM_MSG *msg)
    {
        if (msg == NULL)
        {
            return (ITS_ENULLPTR);
        }
        if (dmcTrans != NULL)
        {
            return dmcTrans->Send(msg);
        }
        return (!ITS_SUCCESS);
    }
private:
    ITS_MUTEX guard;
    static ITS_BOOLEAN bInitialize;
    DmcTransport *dmcTrans;
};
#endif
