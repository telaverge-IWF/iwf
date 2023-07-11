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
 * ID: $Id: dmc_test.cpp,v 1.16 2010/07/07 08:35:35 nvijikumar Exp $
 *
 * LOG: $Log: dmc_test.cpp,v $
 * LOG: Revision 1.16  2010/07/07 08:35:35  nvijikumar
 * LOG: TCS compilation flags support
 * LOG:
 * LOG: Revision 1.15  2010/02/19 09:40:42  rajeshak
 * LOG: Removing unwanted code
 * LOG:
 * LOG: Revision 1.14  2009/10/14 10:53:46  sureshj
 * LOG: forceDisconectPeer, getPeerTimers, GetLocalHostInfo mml APIs
 * LOG: testing code added.
 * LOG:
 * LOG: Revision 1.13  2009/09/17 08:37:21  rajeshak
 * LOG: API to enable/disable DMC hex dump.
 * LOG:
 * LOG: Revision 1.12  2009/09/07 05:04:08  rajeshak
 * LOG: MML Support to set/get HMI Heartbeat interval.
 * LOG:
 * LOG: Revision 1.11  2009/07/27 11:57:19  rajeshak
 * LOG: DMC Test Application changes for Stats.
 * LOG:
 * LOG: Revision 1.10  2009/07/24 09:45:02  rajeshak
 * LOG: Following Changes are included
 * LOG:  1. New MML API's added to get/remove default route,get/set overload limits
 * LOG:     Enable/Disable HMI
 * LOG:  2. Stats changes (to include option to clear stats in get)
 * LOG:
 * LOG: Revision 1.9  2009/07/13 08:33:36  rajeshak
 * LOG: 1. Reverting back session table changes.
 * LOG: 2. MML API to set/get the HMI Retry.
 * LOG:
 * LOG: Revision 1.8  2009/06/29 14:57:28  rajeshak
 * LOG: 1. MML Commands added to set HMI Check Interval and Timeout.
 * LOG: 2. Changes for Queue stats and session table size.
 * LOG:
 * LOG: Revision 1.7  2009/05/11 06:46:14  nvijikumar
 * LOG: Re-connect functionality is moved to Application
 * LOG: It is mandatory that Application has to call Connect after Initialize
 * LOG:
 * LOG: Revision 1.6  2009/05/11 06:37:56  rajeshak
 * LOG: 1. Get/Set Heartbeat Interval changes
 * LOG: 2. Connection Establishment time in Peer Status
 * LOG:
 * LOG: Revision 1.5  2009/03/26 09:40:12  rajeshak
 * LOG: GetPeerStatus MML API Support
 * LOG:
 * LOG: Revision 1.4  2009/03/26 06:01:16  nvijikumar
 * LOG: API to Get Peer Status
 * LOG:
 * LOG: Revision 1.3  2009/03/26 05:29:22  nvijikumar
 * LOG: Enhanced for GetDiaMiscStats and ResetAllStats API
 * LOG:
 * LOG: Revision 1.2  2009/03/26 04:10:19  rajeshak
 * LOG: Enhanced Test Application.
 * LOG:
 * LOG: Revision 1.1  2009/03/02 04:39:44  nvijikumar
 * LOG: Initial draft for MML API Support
 * LOG:
 * LOG:
 ****************************************************************************/

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <iostream.h>
#include <string.h>
#include <stdlib.h>

#include <its++.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
#endif

#include <dmc_api.h>

/* gloabal variables */

/* public variable */
static char* hostIpAddress;
static int serverPort;
DMCApi *api = NULL;

void 
CallBackFunc(DMC_CB_INFO dmCbInfo)
{
    printf("CallBackFunc\n");
    if (dmCbInfo.type == DMC_CONNECT)
    {
        printf("$$$$$$$ Connected $$$$$$$$\n");
    }
    else if(dmCbInfo.type == DMC_DISCONNECT)
    {
        printf("$$$$$$$ Disconnected $$$$$$$$\n");
    }
}

void SendTracingReq()
{
    int choice;
    ITS_USHORT trId;

    DM_TRACE trace;
    trace.all = ITS_FALSE;
    trace.dbg = ITS_TRUE;
    trace.wrn = ITS_TRUE;
    trace.err = ITS_TRUE;
    trace.crt = ITS_TRUE;
    printf("Enter 0 to disable trace\n");
    printf("Enter 1 to enable trace\n");
    scanf("%d",&choice);
    if (choice)
    {
        api->AllocateTransactionId(trId);
        api->EnableTrace(&trace, trId);
    }
    else
    {
        api->AllocateTransactionId(trId);
        api->DisableTrace(&trace, trId);
    }
    return;
}
void SendStatsReq()
{
    int choice;
    ITS_USHORT trId;
    printf("Enter 0 to disable stats\n");
    printf("Enter 1 to enable stats\n");
    printf("Enter 2 to get indication stats \n");
    printf("Enter 3 to get session stats\n");
    printf("Enter 4 to get peer stats \n");
    printf("Enter 5 to get Session table size\n");
    printf("Enter 6 to get IDc conn table size\n");
    printf("Enter 7 to get DiaTrace Stats\n");
    printf("Enter 8 to get DiaQueue Stats\n");
    printf("Enter 9 to Reset All Stats\n");
    printf("Enter 10 to get Misc Stats\n");
    printf("Enter 11 to get Peer Status\n");
    scanf("%d",&choice);

    api->AllocateTransactionId(trId);
    switch (choice)
    {
        case 0:
        {
            api->DisableStats(trId);
            break;
        }
        case 1:
        {
            api->EnableStats(trId);
            break;
        }
        case 2:
        {
            api->GetDiaIndStats(true, trId);
            break;
        }
        case 3:
        {
            api->GetDiaSessStats(true, trId);
            break;
        }
        case 4:
        {
            api->GetDiaPeerStats(true, trId);
            break;
        }
        case 5:
        {
            api->GetSessionTableSize(trId);
            break;
        }        
        case 6:
        {
            api->GetIdcConnStatus(12, trId);
            break;
        }
        case 7:
        {
            api->GetDiaTraceStatus(trId);
            break;
        }
        case 8:
        {
            api->GetDiaQueueStats(trId);
            break;
        }
        case 9:
        {
            api->ResetAllStats(trId);
            break;
        }
        case 10:
        {
            api->GetDiaMiscStats(true, trId);
            break;
        }
        case 11:
        {
            api->GetPeerStatus("nemocl", "india.internal.net", trId);
            break;
        }

        default:
           printf("Invalid choice\n");
           break;
    }
    return;
}

void SendPeerReq()
{
    int choice;
    ITS_USHORT trId;
    printf("Enter 0 to delete peer\n");
    printf("Enter 1 to add peer\n");
    printf("Enter 2 to disc peer\n");
    printf("Enter 3 to Start all peers\n");
    printf("Enter 4 to Start peer\n");
    printf("Enter 5 to add alt peer\n");
    printf("Enter 6 to modify alt peer\n");
    printf("Enter 7 to remove alt peer\n");
    printf("Enter 8 to Disconnect All peers\n");
    printf("Enter 9 to Set Peer Timers\n");
    printf("Enter 10 to Set Session Timers\n");
    printf("Enter 11 to Set Local Host Info\n");
    printf("Enter 12 to Set HMI Interval\n");
    printf("Enter 13 to Get HMI Interval\n");
    printf("Enter 14 to Set HMI Timeout\n");
    printf("Enter 15 to Get HMI Timeout\n");
    printf("Enter 16 to Set HMI Retry\n");
    printf("Enter 17 to Get HMI Retry\n");
    printf("Enter 18 to Enable HMI\n");
    printf("Enter 19 to Disable HMI\n");
    printf("Enter 20 to Get HMI Status\n");
    printf("Enter 21 to Get HMI HB Interval\n");
    printf("Enter 22 to Set HMI HB Interval\n");
    printf("Enter 23 to Get Overload Threshold\n");
    printf("Enter 24 to Set Overload Threshold\n");
    printf("Enter 25 to Get Default Route\n");
    printf("Enter 26 to Remove Default Route\n");
    printf("Enter 27 to Disconnect Peer Forcefully\n");
    printf("Enter 28 to Get Peer timers\n");
    printf("Enter 29 to Get local host information\n");
    scanf("%d",&choice);

    api->AllocateTransactionId(trId);

    switch (choice)
    {
    case 0:
    {
        api->RemovePeer("nemo", "india.internal.net", trId);
        break;
    }
    case 1:
    {
        DM_PEER_ENTRY pEntry;
        printf("Enter peerName\n");
        scanf("%s",pEntry.peerName);
        printf("Enter realmName\n");
        scanf("%s",pEntry.realmName);
        printf("Enter ipAddr\n");
        scanf("%s",pEntry.ipAddr);
        pEntry.trType = DM_DIA_TR_TCP;
        pEntry.port = 9911;
        api->AddPeer(&pEntry, trId);
        break;
    }
    case 2:
    {
        ITS_INT cause = 0;
        api->DisconnectPeer("nemocl10", "india.internal.net", cause, trId);
        break;
    }
    case 3:
    {
        api->StartAllPeers(trId);
        break;
    }
    case 4:
    {
        api->StartPeer("nemocl", "india.internal.net", trId);
        break;
    }
    case 5:
    {
        DM_ALT_PEER_INFO pEntry;
        printf("Enter peerName\n");
        scanf("%s",pEntry.peerName);
        printf("Enter realmName\n");
        scanf("%s",pEntry.realmName);
        printf("Enter altHost\n");
        scanf("%s",pEntry.altHost);
        printf("Enter altRealmName\n");
        scanf("%s",pEntry.altRealmName);
        pEntry.isFailoverEnable = true;
        pEntry.isFailbackEnable = true;
        pEntry.isRedundantMate = false;

        api->AddAlternatePeer(&pEntry, trId);
        break;
    }
    case 6:
    {
        DM_ALT_PEER_INFO pEntry;
        printf("Enter peerName\n");
        scanf("%s",pEntry.peerName);
        printf("Enter realmName\n");
        scanf("%s",pEntry.realmName);
        printf("Enter altHost\n");
        scanf("%s",pEntry.altHost);
        printf("Enter altRealmName\n");
        scanf("%s",pEntry.altRealmName);
        pEntry.isFailoverEnable = true;
        pEntry.isFailbackEnable = true;
        pEntry.isRedundantMate = false;

        api->ModifyAlternatePeer(&pEntry, trId);
        break;
    }
    case 7:
    {
        DM_PEER_INFO pEntry;
        printf("Enter peerName\n");
        scanf("%s",pEntry.peerName);
        printf("Enter realmName\n");
        scanf("%s",pEntry.realmName);

        api->RemoveAlternatePeer((const char*)pEntry.peerName, (const char*)pEntry.realmName, trId);
        break;
    }
    case 8:
    {
        api->DisconnectAllPeers(0, trId);
        break;
    }
    case 9:
    {
        DM_PEER_TIMER pTimer;
        printf("Enter Retry");
        scanf("%d", &pTimer.retry);
        printf("Enter Expiry");
        scanf("%d", &pTimer.expiry);
        printf("Enter Watchdog");
        scanf("%d", &pTimer.wd);
        api->SetPeerTimers(&pTimer, trId);
        break;
    }
    case 10:
    {
        DM_SESS_TIMER pTimer;

        printf("Enter sessionTimeout\n");
        scanf("%d", &pTimer.sessTimeout);
        printf("Enter LifeTimeout");
        scanf("%d", &pTimer.lifeTimeout);
        printf("Enter GracePeriod");
        scanf("%d", &pTimer.graceTimeout);

        api->SetSessionTimers(&pTimer, trId);
        break;
    }
    case 11:
    {
        const char* pName = "Alice-123";
        const char* pRName = "diameter.com";
        const char* pIp =  "172.1.1.1";

        api->SetLocalHostInfo(pName, pRName, pIp, trId);
        break;
    }
    case 12:
    {
        int val = 0;
        printf("Enter HMI Interval");
        scanf("%d", &val);
        api->SetHMIInterval(val, trId);
        break;
    }
    case 13:
    {
        api->GetHMIInterval(trId);
        break;
    }
    case 14:
    {
        int val = 0;
        printf("Enter HMI Timeout");
        scanf("%d", &val);
        api->SetHMITimeout(val, trId);
        break;
    }
    case 15: 
    {
        api->GetHMITimeout(trId);
        break;
    }
    case 16:
    {
        int val = 0;
        printf("Enter HMI Retry\n");
        scanf("%d", &val);
        api->SetHMIRetry(val, trId);
        break;
    }
    case 17:
    {
        api->GetHMIRetry(trId);
        break;
    }
    case 18:
    {
        api->EnableHMI(trId);
        break;
    }
    case 19:
    {
        api->DisableHMI(trId);
        break;
    }
    case 20:
    {
        api->IsHMIEnabled(trId);
        break;
    }
    case 21:
    {
        api->GetHMIHBInterval(trId);
        break;
    }
    case 22:
    {
        int val = 0;
        printf("Enter HMI HB Interval\n");
        scanf("%d", &val);
        api->SetHMIHBInterval(val, trId);
        break;
    }
    case 23:
    {   
        api->GetOvloadThresholds(trId);
        break;
    }
    case 24:
    {
        int minVal = 0, maxVal = 0;
        printf("Enter MaxTh");
        scanf("%d", &maxVal);

        printf("Enter MinTh");
        scanf("%d", &minVal);

        api->SetOvloadThresholds(maxVal, minVal, trId);
        break;
    }
    case 25:
    {
        api->GetDefaultRoute(trId);
        break;
    }
    case 26:
    {
        api->RemoveDefaultRoute(trId);
        break;
    }

    case 27:
    {
        api->ForceDisconnectPeer("nemocl10", "india.internal.net", 0, 30, trId);
        break;
    }
    case 28:
    {
        api->GetPeerTimers(trId);
        break;
    }
    case 29:
    {
        api->GetLocalHostInfo(trId);
        break;
    }
   
    default:
        printf("Invalid Command\n");
        break;
    }
    return;
}

void SendRealmReq()
{
    int choice;
    ITS_USHORT trId;
    printf("Enter 0 to delete realm\n");
    printf("Enter 1 to add realm\n");
    printf("Enter 2 to remove destination\n");
    printf("Enter 3 to add destination\n");
    printf("Enter 4 to disable proxy info\n");
    printf("Enter 5 to enable proxy info\n");
    printf("Enter 6 to set Default Route\n");
    scanf("%d",&choice);

    api->AllocateTransactionId(trId);

    switch (choice)
    {
    case 0:
    {
        api->RemoveRealm("india.internal.com", trId);
        break;
    }
    case 1:
    {
        api->AddRealm("india.internal.com", "proxy", ITS_TRUE, trId);
        break;
    }
    case 2:
    {
        DM_DEST_INFO dInfo;
        printf("Enter peerName\n");
        scanf("%s",dInfo.peerName);
        printf("Enter realmName\n");
        scanf("%s",dInfo.realmName);
        dInfo.appId    = 16777216;
        dInfo.vendId   = 1045;
        dInfo.priority = 10;
        api->RemoveDestination(&dInfo, trId);
        break;
    }
    case 3:
    {
        DM_DEST_INFO dInfo;
        printf("Enter peerName\n");
        scanf("%s",dInfo.peerName);
        printf("Enter realmName\n");
        scanf("%s",dInfo.realmName);
        dInfo.appId    = 16777216;
        dInfo.vendId   = 1045;
        dInfo.priority = 10;
        api->AddDestination(&dInfo, trId);
        break;
    }
    case 4:
    {
        api->EnableProxyInfoAVP("india.internal.net", trId);
        break;
    }
    case 5:
    {
        api->DisableProxyInfoAVP("india.internal.net", trId);
        break;
    }
    case 6:
    {
        DM_PEER_INFO pInfo;
        printf("Enter peerName\n");
        scanf("%s",pInfo.peerName);
        printf("Enter realmName\n");
        scanf("%s",pInfo.realmName);
        api->SetDefaultRoute((const char*)pInfo.peerName, (const char*)pInfo.realmName, trId);
        break;
    }
    default:
       printf("Invalid Command\n");
       break;
    }
    return;
}

void SendCommitReq()
{
    int choice;
    ITS_USHORT trId;
    api->AllocateTransactionId(trId);
    api->DiaCommit("itsdiaserverNew", trId);
    return;
}

void SendHBReq()
{
    int choice;
    int interval;
    ITS_USHORT trId;

    printf("Enter 1 to Set Heartbeat Interval\n");
    printf("Enter 2 to Get Heartbeat Interval\n");
    printf("Enter 3 to Set Heartbeat Retry\n");
    printf("Enter 4 to Get Heartbeat Retry\n");
    printf("Enter 9 to Return \n");
    scanf("%d",&choice);

    api->AllocateTransactionId(trId);

    switch (choice)
    {
    case 1:
    {
        printf("Enter Heartbeat Interval\n");
        scanf("%d",&interval);
        api->SetHeartbeatInterval(interval, trId);
        break;
    }
    case 2:
    {
        api->GetHeartbeatInterval(trId);
        break;
    }
    case 3:
    {
        printf("Enter Heartbeat Retry\n");
        scanf("%d",&interval);
        api->SetHeartbeatRetry(interval, trId);
        break;
    }
    case 4:
    {
        api->GetHeartbeatRetry(trId);
        break;
    }
    case 9:
        return;
    }

    return;
}

void
SendDiaMgmtRequest()
{
    int choice;
    std::string inStr;
    while(1)
    {
        do
        {
            printf("\n###############################\n");
            printf("Select the Commnad type \n");
            printf("1. Tracing \n");
            printf("2. Statistics \n");
            printf("3. Peer \n");
            printf("4. Realm \n");
            printf("5. XML Commit \n");
            printf("6. Heartbeat configuration\n");
            printf("9. Back to Previous Menu \n");
            printf("\n###############################\n");
            cin >> inStr;
            choice = atoi(inStr.c_str());
        }while((choice <1 || choice >6) && choice!=9);

        switch(choice)
        {
        case 1:
            SendTracingReq();
            break;
        case 2:
            SendStatsReq();
            break;
        case 3:
            SendPeerReq();
            break;
        case 4:
            SendRealmReq();
            break;
        case 5:
            SendCommitReq();
            break;
        case 6:
            SendHBReq();
            break;
        case 9:
            return;
        default:
            printf("Invalid request\n");
            break;

        }
    }
}

extern "C" void*
Receive(void* args)
{
    printf("In Recieve thread\n");

    DM_MSG ev;
    
    while(1)
    { 
        memset(&ev, 0, sizeof(DM_MSG));
        api->ReceiveEvent(&ev);
        if (ev.mType == MSG_TYPE_RES)
        {
                printf("\n<----- IDS Management response message -------->\n");
                printf("\tIDS Management command = %s\n", 
                                            DM_CMD_TO_TEXT(ev.u.res.cmd));
                printf("\tTransaction Id         = %u\n", ev.u.res.trId);
                printf("\tResult Code            = %u\n", ev.u.res.rCode);
                printf("\n<--------------------------------------------->\n");
        }
        else
        {
                printf("\n<----- Invalid message received -------->\n");
        }
        cout << "Command Code : " << ev.u.res.cmd << endl;

        switch(ev.u.res.cmd)
        {
        case GET_INDC_STATS:
        {
            DM_INDIC_STATS *diaIndcStats = &ev.u.res.param.indicStats;
            cout << "------------------------------------------------------"
               << endl;    cout << "-- Dia Indication Stats --  " << endl;
            cout << "------------------------------------------------------"
               << endl;
            cout << "Num of Disconnect Indications       "
               << diaIndcStats->numDisconnInd << endl;

            cout << "Num of Timeout Indications          "
               << diaIndcStats->numSessTimeoutInd << endl;

            cout << "Num of AuthLifeTimeout Indications  "
               << diaIndcStats->numAuthLifeTimeoutInd << endl;

            cout << "Num of AuthGraceTimeout Indications "
               << diaIndcStats->numAuthGraceTimeoutInd << endl;

            cout << "Num of Abort Indications            "
               << diaIndcStats->numAbortInd << endl;

            cout << "Num of Corrupt Indications          "
               << diaIndcStats->numCorruptMsgInd << endl;
            cout << "Num of Unknown Indications          "
               << diaIndcStats->numUnknownInd << endl;

            cout << "Num of FailOver Indications         "
               << diaIndcStats->numFailOverInd << endl;

            cout << "Num of FailBack Indications         "
               << diaIndcStats->numFailBackInd << endl;
            cout << "------------------------------------------------------"
                 <<endl;
            break;
        }
        case GET_MISC_STATS:
        {
            DM_MISC_STATS *diaMiscStats = &ev.u.res.param.miscStats;
            cout << "------------------------------------------------------"
               << endl;    cout << "-- Dia Misc Stats --  " << endl;
            cout << "------------------------------------------------------"
               << endl;
            cout << "Num of Redirect Events       "
               << diaMiscStats->redirectEvents << endl;

            cout << "Num of Total Retransmits       "
               << diaMiscStats->totalRetrans << endl;

            cout << "Num of Permanent Failures  "
               << diaMiscStats->permanentErrs << endl;
            cout << "------------------------------------------------------"
                 <<endl;
            break;
        }
        case GET_SESS_STATS:
        {
           break;
        }
        case GET_PEER_STATS:
        {
           break;
        }
        case GET_SESSION_TBL_SIZE:
        {
            cout << "\n\nSession table size = "<< ev.u.res.param.sessTableSize.stats << endl;
            break;
        }
        case GET_IDC_CONN_STATUS:
        {
            cout << "\n\nIDC Conn AppId = "<< ev.u.res.param.idcConnInfo.appIdentifier << endl;
            cout << "AppId Type = "<< ev.u.res.param.idcConnInfo.appIdType << endl << endl;
            break;
        }
        case GET_DIA_TRACE_STATS:
        {
            cout << endl << "------------------------------------------------------" <<endl;
            if (ev.u.res.param.diaTrace.dbg == ITS_TRUE)
            {
                cout << "DEBUG Trace : Enabled" << endl;
            }
            else
            {
                cout << "DEBUG Trace : Disabled" << endl;
            }

            if (ev.u.res.param.diaTrace.wrn == ITS_TRUE)
            {
                cout << "WARNING Trace : Enabled" << endl;
            }
            else
            {
                cout << "WARNING Trace : Disabled" << endl;
            }

            if (ev.u.res.param.diaTrace.err == ITS_TRUE)
            {
                cout << "ERROR Trace : Enabled" << endl;
            }
            else
            {
                cout << "ERROR Trace : Disabled" << endl;
            }

            if (ev.u.res.param.diaTrace.crt == ITS_TRUE)
            {
                cout << "CRITICAL Trace : Enabled" << endl;
            }
            else
            {
                cout << "CRITICAL Trace : Disabled" << endl;
            }
            cout << "------------------------------------------------------" << endl << endl;

            break;
        }
        case GET_DIA_Q_STATS:
        {
            cout << "Queue Stats : "<< endl;
            cout << "Upstream Q Count = "<< ev.u.res.param.qStats.upQCount << endl;
            cout << "Downstream Q Count = "<< ev.u.res.param.qStats.downQCount << endl;
            break;
        }
        case GET_PEER_STATUS:
        {
            char tempBuf[2*DM_TIME_STRING_SIZE];
            struct tm tbuf;
            localtime_r(&(ev.u.res.param.peerStatus.connEstTime), &tbuf);
            strftime(tempBuf,(2*DM_TIME_STRING_SIZE), "[ %b %d %Y %H:%M:%S ]" ,&tbuf);

            cout << "Peer Name  : " << ev.u.res.param.peerStatus.peerName << endl;
            cout << "Realm Name : " << ev.u.res.param.peerStatus.realmName << endl;
            cout << "IP Add     : " << ev.u.res.param.peerStatus.ipAddr << endl;
            cout << "Port       : " << ev.u.res.param.peerStatus.port << endl;
            cout << "State      : " << ev.u.res.param.peerStatus.pState << endl;
            cout << "Type       : " << ev.u.res.param.peerStatus.type << endl;
            cout << "Static/Dyn : ";
            if (ev.u.res.param.peerStatus.isStatic == ITS_TRUE)
            {
                cout << "Static" << endl;
            }
            else
            {
                cout << "Dynamic" << endl;
            }

            cout << "Conn Time  : ";
            if( ev.u.res.param.peerStatus.pState == DM_PEER_I_OPEN || 
                ev.u.res.param.peerStatus.pState == DM_PEER_R_OPEN )
            {
                cout << tempBuf << endl;
            }
            else
            {
                cout << "Not Connected" <<endl;
            } 
            break;
        }
        case GET_DEFAULT_ROUTE:
        {
            cout << "Default Route " << endl;
            cout << "Peer Name  :" << ev.u.res.param.defRoute.peerName << endl;
            cout << "Realm Name :" << ev.u.res.param.defRoute.realmName << endl;
            break;
        }
        case GET_PEER_TIMERS:
        {
            cout << "Peer Timers ***  " << endl;
            cout << " WatchDog :" << ev.u.res.param.peerTimer.wd<< endl;
            cout << " Retry    :" << ev.u.res.param.peerTimer.retry << endl;
            cout << " Expiry   :" << ev.u.res.param.peerTimer.expiry << endl;
            break;
        }
        case GET_LOCAL_HOST_INFO: 
        {
           cout << " *** Local Host Information ***  " << endl;
            cout << " HostName   :" << ev.u.res.param.hostInfo.hostName<< endl;
            cout << " RealmName  :" << ev.u.res.param.hostInfo.realmName << endl;
            cout << " IP Address :" << ev.u.res.param.hostInfo.ipAddr << endl;
            break;
        }  

      }

    }
    return (NULL);
}
    
extern "C" 
void * PrintMenu(void* args)
{
   int input = 0;
   int choice = 0;
   unsigned char buffer[256];

   while (1)
   {
       printf("\n############## Choice ###########\n");

       printf("1.Initialize\n");
       printf("2.Connect\n");
       printf("3.Send\n");
       printf("4.Disconnect\n");
       printf("5.Enable DMC Trace\n");
       printf("6.Disable DMC Trace\n");
       printf("7.Enable DMC Hex Dump\n");
       printf("8.Disable DMC Hex Dump\n");
       printf("0.Exit\n");

       printf("\n###############################\n");

       scanf("%d", &input);

       switch(input)
       {
           case 1:
               if (!api->IsConnectionUp())
               {
                   api->Initialize("172.16.3.50", 8686);
               }
               else
               {
                   printf("Transport already initialized\n");
               }
           break;
           case 2:
               if (api && !(api->IsConnectionUp()))
               {
                   if (api->Connect() == ITS_SUCCESS)
                   {
                       printf("Connection Sucessfull\n");
                   }
                   else
                   {   
                       printf("Connection Failed\n");
                   }

               }
               else
               {
                   printf("Connection is Already UP and Running\n");
               }
           break;
           case 3:
               if (api->IsConnectionUp())
               {
                   SendDiaMgmtRequest();
               }
               else
               {
                   printf("Err::Transport is not initialized\n");
               }
           break;
           case 4:
               if (api && api->IsConnectionUp())
               {
                   if (api->CloseConnection() == ITS_SUCCESS)
                   {
                       printf("CloseConnection Sucessfull\n");
                   }
                   else
                   {
                       printf("CloseConnection Failed\n");
                   }
               }
               else
               {
                       printf("Transport is not UP\n");
               }
           break;
           case 5:
               api->EnableTrace();
               break;
           case 6:
               api->DisableTrace();
               break;
           case 7:
               api->EnableHexDump();
               break;
           case 8:
               api->DisableHexDump();
               break;
           case 0:
               exit(1);
           break;

       }

   }
   return (NULL);
}


int main()
{
    pthread_t thread, threadPrint;
    int ret =0;
    api = DMCApi::GetDmcApi();
    api->RegisterCallBack(CallBackFunc);

    printf("\n\t *******************************************\n");
    printf("\t *****  IntelliNet Technologies, Inc.    *****\n");
    printf("\t *****  IntelliNet Diameter Mgmt Client Test *\n");
    printf("\t *******************************************\n\n\n");
    
    /* Receive thread */
    pthread_create(&thread, NULL, Receive, (void *)NULL);

    /* Send thread */
    pthread_create(&threadPrint, NULL, PrintMenu, (void *)NULL);

    /* Suspend the main */
    pthread_join(thread, NULL);
    
}

