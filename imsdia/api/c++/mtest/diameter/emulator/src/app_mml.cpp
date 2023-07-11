/*********************************-*-C-*-************************************
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
 * LOG: $Log: app_mml.cpp,v $
 * LOG: Revision 1.1.2.1  2013/04/01 06:23:58  vsarath
 * LOG: Added new for emulator
 * LOG:
 * LOG: Revision 1.1.2.2  2013/02/21 12:00:31  ncshivakumar
 * LOG: removed 3rd parameter from SetLocalHostInfo as it does not accept ip address now
 * LOG: CVS-------------------------------------------------------------------
 * LOG:
 * LOG: Revision 1.1.2.1  2013/01/28 15:54:23  pramana
 * LOG: Committing the simulator code
 * LOG:
 * LOG: Revision 3.8  2011/03/16 08:30:41  vkumara
 * LOG: Stats Via API test MML included
 * LOG:
 * LOG: Revision 3.7  2011/02/15 05:45:53  nvijikumar
 * LOG: dia_msg_router.h should not be included here
 * LOG:
 * LOG: Revision 3.6  2010/09/30 06:49:22  vkumara
 * LOG: MML commands to enable/disable DSCP
 * LOG:
 * LOG: Revision 3.5  2010/09/23 13:11:35  vkumara
 * LOG: getDiaTrace MML command added
 * LOG:
 * LOG: Revision 3.4  2010/08/31 09:34:22  vkumara
 * LOG: DSCP set and get MML Commands.
 * LOG:
 * LOG: Revision 3.3  2010/08/19 11:25:29  nvijikumar
 * LOG: Removing DCCA deps
 * LOG:
 * LOG: Revision 3.2  2010/08/19 04:21:55  vkumara
 * LOG: MOTOROLA PSG Req:MML Commands on static set up.
 * LOG: MML commads are ported from aim/src/ids_mml.cpp to itsdemo/src/app_mml.cpp
 * LOG: and app_stat/src/app_mml.cpp on current branch.
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:07  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2006/12/19 07:59:44  kamakshilk
 * LOG: Common files required for static setup
 * LOG:
 * LOG: Revision 1.3  2006/11/22 10:44:53  hbhatnagar
 * LOG: Made changes for the load test
 * LOG:
 * LOG: Revision 1.2  2006/11/13 08:55:34  hbhatnagar
 * LOG: made changes for the new MML commands for DCCA.
 * LOG:
 * LOG: Revision 1.1  2006/10/17 06:28:20  tpanda
 * LOG: Baseline ITS Demo.
 * LOG:
 * LOG: Revision 1.8  2006/06/21 09:57:29  kamakshilk
 * LOG: Modification for Copyright info.
 * LOG:
 * LOG: Revision 1.7  2006/05/11 13:36:47  rrath
 * LOG: Added output information in MML console.
 * LOG:
 * LOG: Revision 1.6  2006/05/04 20:48:17  yranade
 * LOG: Added commands to enable/disable all traces.
 * LOG:
 * LOG: Revision 1.5  2006/04/28 18:23:58  yranade
 * LOG: Changes for accelero based OD tracing.
 * LOG:
 * LOG: Revision 1.4  2006/04/27 16:04:57  yranade
 * LOG: Added Commands to Enable/Disable Diameter Traces.
 * LOG:
 * LOG: Revision 1.3  2006/04/25 14:07:30  adsouza
 * LOG: 1. Code Enhancements (Added Comments, Flowerboxes)
 * LOG: 2. Method to Inject Hex Dumps
 * LOG:
 * LOG: Revision 1.2  2006/04/22 00:06:20  ahanda
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1  2006/04/17 16:07:29  yranade
 * LOG: MML Server Support.
 * LOG:
 *
 * ID: $Id: app_mml.cpp,v 1.1.2.1 2013/04/01 06:23:58 vsarath Exp $
 ****************************************************************************/

#include <dia_trace.h>

#include <app.h>
#include <app_mml.h>
#include <dia_stats.h>
#include <app_trace.h>
#include <dcca_api.h>
#include <dia_mgmt.h>
#include <its_redundancy.h>

/* Conflict Resolution on Linux
*/

#if defined(IPPROTO_SCTP)
#undef IPPROTO_SCTP
#endif

#include <dia_frame.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
#endif

LoadGenFunc TrafficGeneratorFunc = NULL;

extern void StratTraffic(ostream& os,int duration, int burstSize, int slpTime);
extern void StopTraffic();
extern void PrintStats(std::ostream& oss);
extern void ResetStats();
extern void CalculateTPS(std::ostrstream& oss);

/*  implementation: public
****************************************************************************
*  Purpose:
*      All Commands that need to be displayed to the MMLConsole need to be
*      Defined Here.This function also processes the commands received by the
*      from the User Driven MML Console.
*
*  Input Parameters:
*      istream& commandLine: User Input from MML Console.
*
*  Input/Output Parameters:
*      None.
*
*  Output Parameters:
*      None.
*
*  Return Value:
*      None
*
*  Notes:
*
*  See Also:
****************************************************************************/
void
APPMMLServer::DoCommand(istream& commandLine)
{
    string dummy;
    PEER_INFO pInfo;
    ALT_PEER_INFO aInfo;
    DESTINATION_INFO dInfo;
    int found = 0;

    DiaMgmt *diaMgmt = DiaMgmt::GetDiaMgmt();

    /*
     * Command to print the statistics
     */
    if (Cmd("stats", "Show Statistics"))
    {
        PrintStats(oss);
    }
    /*
     * Command to clear the statistics
     */
    else if (Cmd("clear", "Clear Statistics"))
    {
        ResetStats();      
	oss <<"*****Cleared Statistics *****" << endl;
    }
    /* 
     * Command to start the traffic during load testing
     */
    if (Cmd("start-traffic", "Start Traffic", "duration, burstSize,\
                  sleepBetweenBurst"))
    {
        int duration = 0, burstSize = 0, slpTime =0;

        commandLine >> dummy >> duration >> burstSize >> slpTime;
        StratTraffic(oss, duration, burstSize, slpTime);
    }

    /* 
     * Command to stop the traffic
     */
    else if (Cmd("stop-traffic", "Stop Traffic"))
    {
        StopTraffic();
	oss <<"***** Traffic Generation Stopped *****" << endl;
    }
    else if (Cmd("enTrace", "Enable All Traces"))
    {
        EnableAPPTracing();
        EnableDiaTracing();

	oss <<"*****All the traces are enabled*****" << endl;
    }
    else if (Cmd("disTrace", "Disable All Traces"))
    {
        DisableAPPTracing();
        DisableDiaTracing();

	oss <<"*****All the traces are disabled*****" << endl;
    }
    else if (Cmd("tps", "TPS"))
    {
        CalculateTPS(oss);
    }
    else if (Cmd("enDiaTrace", "Enable All Dia Traces"))
    {
        EnableDiaTracing();

	oss <<"*******All Diameter Traces are enabled*******" << endl; 
    }
    else if (Cmd("disDiaTrace", "Disable All Dia Traces"))
    {
        DisableDiaTracing();

	oss <<"*******All Diameter Traces are disabled*******" << endl;
    }
    else if (Cmd("enDiaDebTrace", "Enable Dia Debug Traces"))
    {
        EnableDiaDebugTracing();

	oss <<"*******Diameter Debug Traces are enabled*******" << endl;
    }
    else if (Cmd("enDiaErrTrace", "Enable Dia Error Traces"))
    {
        EnableDiaErrorTracing();	

	oss <<"*******Diameter Error Traces are enabled*******" << endl;
    }
    else if (Cmd("enDiaWarnTrace", "Enable Dia Warning Traces"))
    {
        EnableDiaWarnTracing();
	
	oss <<"*******Diameter Warning Traces are enabled*******" << endl;
    }
    else if (Cmd("enDiaCritTrace", "Enable Dia Critical Traces"))
    {
        EnableDiaCriticalTracing();

	oss <<"*******Diameter Critical Traces are enabled*******" << endl;
    }
    else if (Cmd("disDiaDebTrace", "Disable Dia Debug Traces"))
    {
        DisableDiaDebugTracing();

	oss <<"*******Diameter Debug Traces are disabled*******" << endl;
    }
    else if (Cmd("disDiaErrTrace", "Disable Dia Error Traces"))
    {
        DisableDiaErrorTracing();

	oss <<"*******Diameter Error Traces are disabled*******" << endl;
    }
    else if (Cmd("disDiaCritTrace", "Disable Dia Critical Traces"))
    {
        DisableDiaCriticalTracing();

	oss <<"*******Diameter Critical Traces are disabled*******" << endl;
    }
    else if (Cmd("disDiaWarnTrace", "Disable Dia Warning Traces"))
    {
        DisableDiaWarnTracing();

	oss <<"*******Diameter Warning Traces are disabled*******" << endl;
    }
    else if (Cmd("DisplayDiaTrace", "Display Dia Tracing Info"))
    {
        DisplayDiaTracing(oss);
    }
    else if (Cmd("getDiaTrace", "Get Dia Tracing Info"))
    {
        DiaTrace::GetDiaTrace()->Display(oss);
    }
    else if (Cmd("di", "Hex Dump Injector", "TransportInstance"))
    {
        ITS_UINT inst;
        commandLine >> dummy >> inst;
        InjectDump(inst);
    }
    else if (Cmd("enStatistics", "Enable Dia Stack Statistics "))
    {
        diaMgmt->EnableStatistics();
    }
    else if (Cmd("disStatistics", "Disable Dia Stack Statistics "))
    {
        diaMgmt->DisableStatistics();
    }
    else if (Cmd("isStatsEnabled", "Is Dia Stack Statistics Enabled"))
    {
        if(diaMgmt->IsStatsEnabled())
        {
            oss<<" ********Statistics Enabled ********";
        }
        else
        {
           oss<<" ******** Statistics Disabled ********";
        }
    }
    else if (Cmd("getStackStats", "Display Dia Stack statistics"))
    {
        diaMgmt->GetDiaStackStats(oss);
    }
    else if (Cmd("getDiaSesionStats", "Display Dia Session command statistics"))
    {
        diaMgmt->GetDiaSessionStats(oss);
    }
    else if (Cmd("getDiaPeerStats", "Display DiaPeer based message statistics"))
    {
        diaMgmt->GetDiaPeerStats(oss);
    }
    else if (Cmd("getDiaIndications", "Display Stack Indications"))
    {
        diaMgmt->GetDiaIndicStats(oss);
    }
    else if (Cmd("getDiaMiscStats", "Display Miscellaneous Stats"))
    {
        diaMgmt->GetDiaMiscStats(oss);
    }
    else if (Cmd("resetStackStats", "Reset Dia statistics Info"))
    {
        diaMgmt->ResetStackStats();
    }
    else if (Cmd("addPeer","Add Peer"))
    {
        std::string hostName = "";
        std::string realmName = "";
        std::string type = "";
        std::string ipAddr = "";
        std::string port = "";
        memset(&pInfo, 0, sizeof(PEER_INFO));
        unsigned short porttemp;
 
        commandLine >> dummy >> hostName >> realmName >> type >>
                       ipAddr >> port;
 
        if (strcmp(port.c_str(),"") == 0)
        {
            oss << "Invalid Number of arguments" << endl;
            return;
        }
        pInfo.peerName = hostName.c_str();
        pInfo.realmName = realmName.c_str();
        if (strcmp(type.c_str(),"TCP") == 0)
        {
            pInfo.type = DIA_TRANS_TCP;
        }
        else if(strcmp(type.c_str(),"SCTP") == 0)
        {
            pInfo.type = DIA_TRANS_SCTP;
        }
        else
        {
            oss << "Invalid Transport type"<<endl;
            return;
        }
        pInfo.ipAddr = strdup(ipAddr.c_str());
 
        if (sscanf(port.c_str(),"%hu", &porttemp) > 0)
        {
            pInfo.port = porttemp;
        }
        try
        {
            if (diaMgmt->AddPeer(&pInfo) == ITS_SUCCESS)
            {
                oss << "Successfully PeerConfiguration added" << endl;
            }
            else
            {
                oss << "Failed to add PeerConfiguration" << endl;
            }
        }
        catch(...)
        {
            oss<<"Exception is thrown";
        }
    }
    else if (Cmd("addAlternatePeer","Add Alternate Peer"))
    {
        std::string hostName = "";
        std::string realmName = "";
        std::string altpeerName = "";
        std::string altrealmName = "";
        std::string failoverEnable = "";
        std::string failbackEnable = "";
        std::string isMate = "";
 
        commandLine >> dummy >> hostName >> realmName >>
                       altpeerName >> altrealmName >> failoverEnable >>
                       failbackEnable >>isMate;
 
        if (strcmp(isMate.c_str(),"") == 0)
        {
            oss << "Invalid Number of arguments" << endl;
            return;
        }
        aInfo.peerName = hostName.c_str();
        aInfo.realmName = realmName.c_str();
        aInfo.altHost = altpeerName.c_str();
        aInfo.altRealmName = altrealmName.c_str();
 
        if (strcmp(failoverEnable.c_str(),"yes") == 0)
        {
            aInfo.isFailoverEnable = true;
        }
        else if(strcmp(failoverEnable.c_str(),"no")== 0)
        {
            aInfo.isFailoverEnable = false;
        }
        else
        {
            oss << "Invalid failoverEnable value"<< endl;
        }
 
        if (strcmp(failbackEnable.c_str(),"yes") == 0)
        {
            aInfo.isFailbackEnable = true;
        }
        else if(strcmp(failbackEnable.c_str(),"no")== 0)
        {
            aInfo.isFailbackEnable = false;
        }
        else
        {
            oss << "Invalid failbackEnable value"<< endl;
        }
 
        if (strcmp(isMate.c_str(),"yes")== 0)
        {
            aInfo.isRedundantMate = true;
        }
        else if (strcmp(isMate.c_str(),"no") == 0)
        {
            aInfo.isRedundantMate = false;
        }
        else
        {
            oss << "Invalid Ismate value"<< endl;
        }
 
        if (diaMgmt->AddAlternatePeer(&aInfo) == ITS_SUCCESS)
        {
            oss << "Successfully Alternate PeerConfiguration added" << endl;
        }
        else
        {
            oss << "Failed to add Alternate PeerConfiguration" << endl;
        }
    }
    else if (Cmd("modifyAltPeer","Modify Alternate Peer"))
    {
        std::string hostName = "";
        std::string realmName = "";
        std::string altpeerName = "";
        std::string altrealmName = "";
        std::string failoverEnable = "";
        std::string failbackEnable = "";
        std::string isMate = "";
 
        commandLine >> dummy >> hostName >> realmName >>
                       altpeerName >> altrealmName >> failoverEnable >>
                       failbackEnable >>isMate;
 
        if (strcmp(isMate.c_str(),"") == 0)
        {
            oss << "Invalid Number of arguments" << endl;
            return;
        }
        aInfo.peerName = hostName.c_str();
        aInfo.realmName = realmName.c_str();
        aInfo.altHost = altpeerName.c_str();
        aInfo.altRealmName = altrealmName.c_str();
 
        if (strcmp(failoverEnable.c_str(),"yes") == 0)
        {
            aInfo.isFailoverEnable = true;
        }
        else if(strcmp(failoverEnable.c_str(),"no")== 0)
        {
            aInfo.isFailoverEnable = false;
        }
        else
        {
            oss << "Invalid failoverEnable value"<< endl;
        }
 
        if (strcmp(failbackEnable.c_str(),"yes") == 0)
        {
            aInfo.isFailbackEnable = true;
        }
        else if(strcmp(failbackEnable.c_str(),"no")== 0)
        {
            aInfo.isRedundantMate = true;
        }
        else if (strcmp(isMate.c_str(),"no") == 0)
        {
            aInfo.isRedundantMate = false;
        }
        else
        {
            oss << "Invalid Ismate value"<< endl;
        }
 
        if (diaMgmt->ModifyAlternatePeer(&aInfo) == ITS_SUCCESS)
        {
            oss << "Successfully Modified Alternate PeerConfiguration" << endl;
        }
        else
        {
            oss << "Failed to Modified Alternate PeerConfiguration" << endl;
        }
    }
    else if (Cmd("removeAltPeer", "Remove Alternate Peer"))
    {
        std::string hostName = "";
        std::string realmName = "";
 
        commandLine >> dummy >> hostName >> realmName;
        if(strcmp(realmName.c_str(),"") == 0)
        {
            oss << "Invalid Number of arguments" << endl;
            return;
        }
 
        if (diaMgmt->RemoveAlternatePeer(hostName.c_str(), realmName.c_str())
                                == ITS_SUCCESS)
        {
            oss << "Successfully removed Alternate Peer" << endl;
        }
        else
        {
            oss << "Failed to Remove Alternate Peer" << endl;
        }
    }
    else if (Cmd("startAllPeers","Starts all Peers which are configured"))
    {
        commandLine >> dummy;
 
        if (diaMgmt->StartAllPeers() == ITS_SUCCESS)
        {
            oss << "Successfully Peer started" << endl;
        }
        else
        {
            oss << "Failed to start Peer" << endl;
        }
    }
    else if (Cmd("removePeer","Removes peer entry"))
    {
        std::string hostName = "";
        std::string realmName = "";
 
        commandLine >> dummy >> hostName >> realmName;
        if(strcmp(realmName.c_str(),"") == 0)
        {
            oss << "Invalid Number of arguments" << endl;
            return;
        }
        if (diaMgmt->RemovePeer(hostName.c_str(), realmName.c_str())
                                == ITS_SUCCESS)
        {
            oss << "Successfully Peer removed" << endl;
        }
        else
        {
            oss << "Failed to remove Peer" << endl;
        }
    }
    else if (Cmd("forceDisconectPeer","Removes peer entry Forcefully"))
    {
        std::string hostName = "";
        std::string realmName = "";
        std::string disCause = "";
        ITS_SERIAL expiry;
 
        commandLine >> dummy >> hostName >> realmName>> disCause >> expiry;
        if(strcmp(realmName.c_str(),"") == 0)
        {
            oss << "Invalid Number of arguments" << endl;
            return;
        }
        if(strcmp(disCause.c_str(),"") == 0)
        {
            oss << "Invalid Number of arguments" << endl;
            return;
        }
        if ( (strcmp(disCause.c_str(),"0") != 0) &&
                (strcmp(disCause.c_str(),"1")!= 0) &&
                   (strcmp(disCause.c_str(),"2") != 0))
        {
            oss << "Invalid DisconnectCause value"<< endl;
            return;
        }
        if (diaMgmt->ForceDisconectPeer(hostName.c_str(), realmName.c_str(),
                         atoi(disCause.c_str()), expiry)== ITS_SUCCESS)
        {
            oss << "Forcefully Peer Disconnected" << endl;
        }
        else
        {
            oss << "Failed to Disconnect Peer " << endl;
        }
    }
    else if (Cmd("disconnectPeer","DisconnectPeer"))
    {
        std::string hostName = "";
        std::string realmName = "";
        std::string disCause = "";
 
        commandLine >> dummy >> hostName >> realmName >> disCause;
        if(strcmp(disCause.c_str(),"") == 0)
        {
            oss << "Invalid Number of arguments" << endl;
            return;
        }
 
        if ( (strcmp(disCause.c_str(),"0") != 0) &&
                (strcmp(disCause.c_str(),"1")!= 0) &&
                   (strcmp(disCause.c_str(),"2") != 0))
        {
            oss << "Invalid DisconnectCause value"<< endl;
            return;
        }
 
        if (diaMgmt->DisconnectPeer(hostName.c_str(), realmName.c_str(),
            atoi(disCause.c_str())) == ITS_SUCCESS)
        {
            oss << "Successfully Disconnected Peer" << endl;
        }
        else
        {
            oss << "Failed to Disconnect Peer" << endl;
        }
    }
    else if (Cmd("disconnectAllPeer","Disconnect All Peers"))
    {
        std::string disCause = "";
 
        commandLine >> dummy >> disCause;
        if(strcmp(disCause.c_str(),"") == 0)
        {
            oss << "Invalid Number of arguments" << endl;
            return;
        }
 
        if ( (strcmp(disCause.c_str(),"0") != 0) &&
                (strcmp(disCause.c_str(),"1")!= 0) &&
                   (strcmp(disCause.c_str(),"2") != 0))
        {
            oss << "Invalid DisconnectCause value"<< endl;
            return;
        }
 
        if (diaMgmt->DisconnectAllPeers(atoi(disCause.c_str())) ==
                                       ITS_SUCCESS)
        {
            oss << "Executed Disconnect All Peers Successfully" << endl;
        }
        else
        {
            oss << "Failed to Execute Disconnect All Peers" << endl;
        }
    }
    else if (Cmd("addRealm","Adds Realm "))
    {
        std::string realmName = "";
        std::string localAction = "local";
        std::string proxyEnabled= "no";
        ITS_BOOLEAN isProxyEnabled = ITS_FALSE;
 
        commandLine >> dummy >> realmName >> localAction >> proxyEnabled;
 
        if (strcasecmp(proxyEnabled.c_str(), "YES") == 0)
        {
            isProxyEnabled = ITS_TRUE;
        }
 
        if (strcmp(realmName.c_str(),"") == 0)
        {
            oss << "Invalid Number of arguments" << endl;
            return;
        }
 
        if (diaMgmt->AddRealm(realmName.c_str(), \
                              localAction.c_str(), isProxyEnabled) == ITS_SUCCESS)
        {
            oss << "Successfully Realm added" << endl;
        }
        else
        {
            oss << "Failed to add Realm" << endl;
        }
    }
    else if (Cmd("removeRealm","Removes realm entry"))
    {
        std::string realmName = "";
        commandLine >> dummy >> realmName;
 
        if (strcmp(realmName.c_str(),"") == 0)
        {
            oss << "Invalid Number of arguments" << endl;
            return;
        }
        if (diaMgmt->RemoveRealm(realmName.c_str()) == ITS_SUCCESS)
        {
            oss << "Successfully Realm removed" << endl;
        }
        else
        {
            oss << "Failed to remove Realm" << endl;
        }
    }
    else if (Cmd("addDestination","Adds Destination for Realm"))
    {
 
        std::string realmName = "";
        std::string peerName = "";
        std::string peerRealm = "";
        std::string applicationId = "";
        std::string vendorId = "";
        std::string priority = "";
        unsigned int appId;
        unsigned int vendorid;
        unsigned int Priority;
        commandLine >> dummy >> realmName >> peerName >> peerRealm >>
                       applicationId >> vendorId >> priority;
 
        if (strcmp(priority.c_str(),"") == 0)
        {
            oss << "Invalid Number of arguments" << endl;
            return;
        }
        dInfo.realmName = realmName.c_str();
        dInfo.peerName = peerName.c_str();
        dInfo.peerRealm = peerRealm.c_str();
        if (sscanf(applicationId.c_str(),"%u", &appId) > 0)
        {
            dInfo.applicationId = appId;
        }
        else
        {
            oss << "Invalid applicationId" << endl;
        }
        if (sscanf(vendorId.c_str(),"%u", &vendorid) > 0)
        {
            dInfo.vendorId = vendorid;
        }
        else
        {
            oss << "Invalid vendorid" << endl;
        }
        if (sscanf(priority.c_str(),"%u", &Priority) > 0)
        {
            dInfo.priority = Priority;
        }
        else
        {
            oss << "Invalid Priority" << endl;
        }
        if (diaMgmt->AddDestination(&dInfo) == ITS_SUCCESS)
        {
            oss << "Successfully DestinationConfiguration added" << endl;
        }
        else
        {
            oss << "Failed to add DestinationConfiguration" << endl;
        }
    }
    else if (Cmd("removeDestination","Removes Destination for Realm"))
    {
        std::string realmName = "";
        std::string peerName = "";
        std::string peerRealm = "";
        std::string applicationId = "";
        std::string vendorId = "";
        unsigned int appId;
        unsigned int vendorid;
        commandLine >> dummy >> realmName >> peerName >> peerRealm >>
                       applicationId >> vendorId;
 
        dInfo.realmName = realmName.c_str();
        dInfo.peerName = peerName.c_str();
        dInfo.peerRealm = peerRealm.c_str();
        dInfo.priority = 0;
        if (sscanf(applicationId.c_str(),"%u", &appId) > 0)
        {
            dInfo.applicationId = appId;
        }
        else
        {
            oss << "Invalid applicationId" << endl;
        }
 
        if (sscanf(vendorId.c_str(),"%u", &vendorid) > 0)
        {
            dInfo.vendorId = vendorid;
        }
        else
        {
            oss << "Invalid vendorid" << endl;
        }
 
        if (diaMgmt->RemoveDestination(&dInfo) == ITS_SUCCESS)
        {
            oss << "Successfully removed Destination " << endl;
        }
        else
        {
            oss << "Failed to remove Destination" << endl;
        }
    }
    else if (Cmd("modifyPriority", "Modify Destination Priority"))
    {
        std::string realmName = "";
        std::string peerName = "";
        std::string peerRealm = "";
        std::string applicationId = "";
        std::string vendorId = "";
        std::string priority = "";
        unsigned int appId;
        unsigned int vendorid;
        unsigned int Priority;
 
        commandLine >> dummy >> realmName >> peerName >> peerRealm >>
                       applicationId >> vendorId >> priority;
 
        dInfo.realmName = realmName.c_str();
        dInfo.peerName = peerName.c_str();
        dInfo.peerRealm = peerRealm.c_str();
        if (sscanf(applicationId.c_str(),"%u", &appId) > 0)
        {
            dInfo.applicationId = appId;
        }
        else
        {
            oss << "Invalid applicationId" << endl;
        }
 
        if (sscanf(vendorId.c_str(),"%u", &vendorid) > 0)
        {
            dInfo.vendorId = vendorid;
        }
        else
        {
            oss << "Invalid vendorid" << endl;
        }
 
        if (sscanf(priority.c_str(),"%u", &Priority) > 0)
        {
            dInfo.priority = Priority;
        }
        else
        {
            oss << "Invalid Priority" << endl;
        }
 
        if (diaMgmt->ModifyDestinationPriority(&dInfo) == ITS_SUCCESS)
        {
            oss << "Successfully Modified Destination Priority" << endl;
        }
        else
        {
           oss << "Failed to Modifiy Destination Priority" << endl;
        }
    }
    else if (Cmd("enProxyInfoAvp","Enables Proxy Info AVP"))
    {
        std::string realmName = "";
 
        commandLine >> dummy >> realmName;
        if(strcmp(realmName.c_str(),"") == 0)
        {
            oss << "Invalid Number of arguments" << endl;
            return;
        }
 
        found = diaMgmt->SetProxyInfoAVPEnabled(realmName.c_str(), ITS_TRUE);
        if (found == ITS_SUCCESS)
        {
            oss << "Successfully Enabled Proxy-Info AVP" << endl;
        }
        else if (found == ERROR_REALM_NOT_CORRECT)
        {
            oss << "Realm does not exist." << endl;
            oss << "Failed to Enable Proxy Info AVP." << endl;
        }
        else
        {
            oss << "Local Action is Not RELAY.";
            oss << "Failed to Enable Proxy Info AVP." << endl;
        }
    }
    else if (Cmd("disProxyInfoAvp","Disables Proxy Info AVP"))
    {
        std::string realmName = "";
 
        commandLine >> dummy >> realmName;
        if(strcmp(realmName.c_str(),"") == 0)
        {
            oss << "Invalid Number of arguments" << endl;
            return;
        }
 
        found = diaMgmt->SetProxyInfoAVPEnabled(realmName.c_str(), ITS_FALSE);
        if (found == ITS_SUCCESS)
        {
            oss << "Successfully Disabled Proxy-Info AVP" << endl;
        }
        else if (found == ERROR_REALM_NOT_CORRECT)
        {
            oss << "Realm deosnot exist." << endl;
            oss << "Failed to Enable Proxy Info AVP." << endl;
        }
    }
    else if (Cmd("isProxyInfoAvpEnabled","Prints Proxy Info AVP Enabled or Not."))
    {
        std::string realmName = "";
 
        commandLine >> dummy >> realmName;
        if(strcmp(realmName.c_str(),"") == 0)
        {
            oss << "Invalid Number of arguments" << endl;
            return;
        }
        if (diaMgmt->IsProxyInfoAvpEnabled(oss, realmName.c_str())
                                != ITS_SUCCESS)
        {
            oss << "Realm deosnot exist." << endl;
        }
    }
    else if (Cmd("printPeerTable","Prints Peer Table "))
    {
        diaMgmt->PrintPeerTable(oss);
        diaMgmt->PrintPeerTable(cout);
    }
    else if (Cmd("printRealmTable","Prints Realm Table "))
    {
        diaMgmt->PrintRealmTable(oss);
        diaMgmt->PrintRealmTable(cout);
    }
    else if (Cmd("qCount", "Prints Diameter Q Count "))
    {
        oss << "Diameter Stack Q Count = " << DiaStackClass::GetDiaStackQCount() << endl;
    }
    else if (Cmd("printSessionTable", "Prints Session Table "))
    {
        diaMgmt->PrintSessionTable(oss);
    }
    else if (Cmd("switchOver", "Standby to Active"))
    {
        if (diaMgmt->SwitchOver() == ITS_SUCCESS)
        {
            oss << "Switch Over is Successfull";
        }
        else
        {
            oss << "Switch Over Failed";
        }
    }
    else if (Cmd("getNodeState", "Gets the state of the node"))
    {
        ITS_USHORT state;
        if (diaMgmt->GetNodeState(state))
        {
            if (state == ITS_STATE_PRIMARY)
            {
                oss << "Current state is ACTIVE";
            }
            else
            {
                oss << "Current state is STANDBY";
            }
        }
        else
        {
            oss << "getNodeState Failed: Command valid only for Redundant"\
                   "Configuration";
        }
    }
    else if (Cmd("downStreamQCount", "Prints Diameter DownStream Q Count "))
    {
        ITS_INT count;
        if ((count = DiaStackClass::GetDiaStackSenderQCount()) >= 0)
        {
            oss << "Diameter Stack DownStream Q Count = "
                << count << endl;
        }
        else
        {
            oss << "Diameter Stack DownStream Q Not Initialized"
                << endl;
        }
    }
    else if (Cmd("stSize", "Prints Diameter Session Table Size "))
    {
        oss << "Diameter Session Table Size = "
            << diaMgmt->GetSessionTableSize() << endl;
    }
    else if (Cmd("qStats", "Prints All Q Counts Not preferred in load mode"))
    {
        ITS_INT count;
        if ((count = DiaStackClass::GetDiaStackQCount()) >= 0)
        {
            oss << "Diameter Stack Upstream Q Count = "
                << count << endl;
        }
        else
        {
            oss << "Diameter Stack Upstream Q Not Initialized"
                << endl;
        }
        if ((count = DiaStackClass::GetDiaStackSenderQCount()) >= 0)
        {
            oss << "Diameter Stack DownStream Q Count = "
                << count << endl;
        }
    }
    else if (Cmd("startPeer"," Starts a Peer which is configured"))
    {
        std::string hostName = "";
        std::string realmName = "";
 
        commandLine >> dummy >>  hostName >> realmName;
 
        if(strcmp(realmName.c_str(),"") == 0)
        {
            oss << "Invalid Number of arguments" << endl;
            return;
        }
        if (diaMgmt->StartPeer(hostName.c_str(), realmName.c_str())
                                == ITS_SUCCESS)
        {
            oss << "Successfully Peer Started" << endl;
        }
        else
        {
            oss << "Failed to Start Peer" << endl;
        }
    }
    else if (Cmd("diaCommit"," Commit the xml file to the file mentioned"))
    {
        char filename[ITS_PATH_MAX];
        char buf[ITS_PATH_MAX*2];
        char* bakfile = NULL;
        memset(filename,0,ITS_PATH_MAX);
 
        commandLine >> dummy >>  filename;
 
        if (strlen(filename) <= 0)
        {
            oss << "File name not specified SYNTAX:-   dia_commit <filename>" <<endl;
            return;
        }
 
        diaMgmt->DIA_Commit(filename);
 
        DBC_AppendText(dbc, "\nCommit Success\n");
    }
    else if (Cmd("setPeerTimers"," Set Peer timer values"))
    {
         ITS_SERIAL  wdval, tcval, expiryval;
 
         commandLine>> dummy >> wdval >> tcval >> expiryval;
 
         if(diaMgmt->SetPeerTimers(wdval, tcval, expiryval) != ITS_SUCCESS)
         {
             oss << "Failed to Set Peer timers " << endl;
         }
         else
         {
             oss << "Successfully Peer timers Set " << endl;
         }
    }
    else if (Cmd("getPeerTimers"," Get Peer timer values"))
    {
        ITS_SERIAL  wdval, tcval, expiryval;
        if(diaMgmt->GetPeerTimers(wdval, tcval, expiryval) != ITS_SUCCESS)
         {
             oss << "Failed to Set Peer timers " << endl;
         }
         else
         {
             oss << "*** PEER TIMER VALUES *** " << endl;
             oss << "Watchdog : " << wdval << endl;
             oss << "Retry    : " << tcval << endl;
             oss << "Expiry   : " << expiryval << endl;
         }
 
    }
    else if (Cmd("setAuthTimers", " Set Auth Session timer values"))
    {
         ITS_SERIAL  lifetime, gracetime, timeout;
         commandLine>> dummy >>lifetime >>gracetime>> timeout;
 
         if((lifetime+gracetime)> timeout)
         {
             oss << "Set correct timeout value " << endl;
             timeout = lifetime + gracetime;
         }
 
         if(diaMgmt->SetAuthSessionTimers(lifetime, gracetime, timeout) != ITS_SUCCESS)
         {
             oss << "Failed to set Auth Session Timers " << endl;
         }
         else
         {
             oss << "Successfully Auth Session Timers Set " << endl;
         }
    }
    else if (Cmd("setAcctTimers"," Set Acct Session Timer  values"))
    {
         ITS_SERIAL interim, timeout;
         commandLine>> dummy >> interim >> timeout;
 
         if(diaMgmt->SetAcctSessionTimers(interim, timeout) != ITS_SUCCESS)
         {
             oss << "Failed to set Acc Session Timers " << endl;
         }
         else
         {
             oss << "Successfully Acc Session Timers set" << endl;
         }
    }
    else if (Cmd("setLocalHostInfo"," Set Local Host information"))
    {
         std::string hostName = "";
         std::string realmName = "";
         std::string publicServIp = "";
         commandLine>> dummy >>hostName  >> realmName >> publicServIp;
 
         if(diaMgmt->SetLocalHostInfo(hostName.c_str(), realmName.c_str()) != ITS_SUCCESS)
         {
             oss << "Failed to set Local information " << endl;
         }
         else
         {
             oss << "Successfully Local Information  set" << endl;
         }
    }
    else if (Cmd("getLocalHostInfo"," Get Local Host information"))
    {
         LOCAL_HOST_INFO lHostInfo;
         if(diaMgmt->GetLocalHostInfo(&lHostInfo)!= ITS_SUCCESS)
         {
             oss << "Failed to get Local information " << endl;
         }
         else
         {
             oss << " Local Host Name   :"<< lHostInfo.hostName << endl;
             oss << " Local Realm Name  :"<< lHostInfo.realmName << endl;
             oss << " Local IP address  :"<< lHostInfo.ipAddr << endl;
         }
    }
    else if (Cmd("setDefaultRoute", "Set Default Route Realm Entry"))
    {
        std::string hostName = "";
        std::string realmName = "";
 
        commandLine>> dummy >>hostName  >> realmName;
 
        if(diaMgmt->SetDefaultRoute(hostName.c_str(), realmName.c_str())
                                                  != ITS_SUCCESS)
        {
            oss << "Failed to set Default Route" << endl;
        }
        else
        {
             oss << "Default route Successfully set" << endl;
        }
    }
    else if (Cmd("discoverPeer", "Discover Peer"))
    {
        std::string hostName = "";
        std::string realmName = "";
 
        commandLine>> dummy >> hostName >> realmName;
 
        if (realmName.length() > 0)
        {
            if (diaMgmt->InsertIntoDiscoveryList(realmName.c_str(), hostName.c_str())
                                                  != ITS_SUCCESS)
            {
                oss << "Failed to Add Peer to Discovery List" << endl;
            }
            else
            {
                 oss << "Successfully added Peer to Discovery List" << endl;
            }
        }
        else if (hostName.length() > 0)
        {
            realmName = hostName;
            if (diaMgmt->InsertIntoDiscoveryList(realmName.c_str(), NULL)
                                                  != ITS_SUCCESS)
            {
                oss << "Failed to Add to Discovery List" << endl;
            }
            else
            {
                 oss << "Successfully added to Discovery List" << endl;
            }
        }
        else
        {
            oss << "Invalid Option" << endl;
            return;
        }
    }
    else if (Cmd("removeFromPeerDiscovery", "Remove from Peer Discovery List"))
    {
        std::string hostName = "";
        std::string realmName = "";
 
        commandLine>> dummy >> hostName >> realmName;
 
        if (realmName.length() > 0)
        {
            if (diaMgmt->RemoveFromDiscoveryList(realmName.c_str(), hostName.c_str())
                                                  != ITS_SUCCESS)
            {
                oss << "Failed to Remove from Discovery List" << endl;
            }
            else
            {
                oss << "Removed from Discovery List" << endl;
            }
        }
        else if (hostName.length() > 0)
        {
            realmName = hostName;
            if (diaMgmt->RemoveFromDiscoveryList(realmName.c_str(), NULL)
                                                  != ITS_SUCCESS)
            {
                oss << "Failed to Remove from Discovery List" << endl;
            }
            else
            {
                oss << "Removed from Discovery List" << endl;
            }
        }
        else
        {
            oss << "Invalid Option" <<endl;
        }
    }
    else if (Cmd("enablePeerDiscovery", "Enable Peer Discovery"))
    {
        diaMgmt->EnablePeerDiscovery();
        oss << "Peer Discovery Enabled" << endl;
    }
    else if (Cmd("disablePeerDiscovery", "Disable Peer Discovery"))
    {
        diaMgmt->DisablePeerDiscovery();
        oss << "Peer Discovery Disabled" << endl;
    }
    else if (Cmd("isDiscoveryEnabled", "Is Peer Discovery Enabled"))
    {
        if (diaMgmt->IsPeerDiscoveryEnable())
        {
            oss << "Peer Discovery Enabled" << endl;
        }
        else
        {
            oss << "Peer Discovery Disabled" << endl;
        }
    }
    else if (Cmd("setDiscoveryInterval", "Set Peer Discovery Timer value"))
    {
        int val;
        std::string timerValue = "";
 
        commandLine>> dummy >> timerValue;
 
        if (sscanf(timerValue.c_str(),"%u", &val) > 0)
        {
            if (diaMgmt->SetPeerDiscoveryInterval(val) == ITS_SUCCESS)
            {
                oss << "Peer discovery Timer set" <<endl;
            }
            else
            {
                oss << "Failed To set Peer Discovery Timer" << endl;
            }
        }
        else
        {
            oss << "Invalid Parameter" << endl;
        }
    }
    else if (Cmd("getDiscoveryInterval", "Get Peer Discovery Timer value"))
    {
        int val = diaMgmt->GetPeerDiscoveryInterval();
        oss << "Peer discovery Interval = " << val <<endl;
    }
    else if (Cmd("setOverloadLimits", "Set overload Max and Min Threshold"))
    {
        ITS_INT maxT, minT;
        commandLine>> dummy >>maxT  >> minT;
 
        if(diaMgmt->SetOvloadThresholds(maxT, minT)!= ITS_SUCCESS)
        {
            oss << "Failed to set overload Threshold values" << endl;
        }
        else
        {
             oss << "Successfully Threshold values set" << endl;
        }
    }
    else if (Cmd("getOverloadLimits", "get overload Max and Min Threshold"))
    {
        ITS_INT maxT = 0, minT = 0;
        if(diaMgmt->GetOvloadThresholds(maxT, minT)!= ITS_SUCCESS)
        {
            oss << "Failed to get overload Threshold values" << endl;
        }
        else
        {
             oss << "Ovload Threshold value " << endl;
             oss << "Maximum Threshold :"<<maxT<< endl;
             oss << "Minimum Threshold :"<<minT<< endl;
        }
    }
    else if (Cmd("enableHMI", "Enable Health Monitoring Interface"))
    {
 
        if(diaMgmt->EnableHMI() != ITS_SUCCESS)
        {
            oss << "Failed to Enable HMI " << endl;
        }
        else
        {
             oss << "Successfully HMI Enabled" << endl;
        }
    }
    else if (Cmd("disableHMI", "Disable Health Monitoring Interface"))
    {
 
        if(diaMgmt->DisableHMI() != ITS_SUCCESS)
        {
            oss << "Failed to Disable HMI " << endl;
        }
        else
        {
             oss << "Successfully HMI Disabled" << endl;
        }
     }
 
    else if (Cmd("isHMIEnabled", "Is HMI enabled or not"))
    {
 
        if(diaMgmt->IsHMIEnabled() != ITS_SUCCESS)
        {
            oss << "HMI Disabled " << endl;
        }
        else
        {
             oss << " HMI Enabled" << endl;
        }
    }
    else if (Cmd("enHexDump", "Enable Dia Hex Dump "))
    {
        if(diaMgmt->EnableHexDump() == ITS_SUCCESS)
        {
            oss<<" Successfully Enabled Hex Dump"<<endl;
        }
    }
    else if (Cmd("disHexDump", "Disable Dia Hex Dump "))
    {
        if(diaMgmt->DisableHexDump() == ITS_SUCCESS)
        {
            oss<<" Successfully Disabled Hex Dump"<<endl;
        }
    }
    else if (Cmd("isHexDumpEnabled", "Is Dia Hex Dump Enabled"))
    {
        if(diaMgmt->IsHexDumpEnabled())
        {
            oss<<" ********Hex Dump Enabled ********";
        }
        else
        {
           oss<<" ******** Hex Dump Disabled ********";
        }
    }
    else if (Cmd("setHBInterval", "Set the Heartbeat Interval"))
    {
        ITS_UINT val;
        std::string timerValue = "";
 
        commandLine>> dummy >> timerValue;
 
        if (sscanf(timerValue.c_str(),"%u", &val) > 0)
        {
            if (diaMgmt->SetHBInterval(val) == ITS_SUCCESS)
            {
                oss << "Heartbeat Interval Set" <<endl;
            }
            else
            {
                oss << "Failed To set Heartbeat Interval" << endl;
            }
        }
        else
        {
            oss << "Invalid Parameter" << endl;
        }
    }
    else if (Cmd("setHBRetry", "Set the Heartbeat Retry"))
    {
        ITS_UINT val;
        std::string hbRetry = "";
 
        commandLine>> dummy >> hbRetry;
 
        if (sscanf(hbRetry.c_str(),"%u", &val) > 0)
        {
            if (diaMgmt->SetHBRetry(val) == ITS_SUCCESS)
            {
                oss << "Heartbeat Retry Set" <<endl;
            }
            else
            {
                oss << "Failed To set Heartbeat Retry" << endl;
            }
        }
        else
        {
            oss << "Invalid Parameter" << endl;
        }
    }
    else if (Cmd("getHBInterval", "Get the Heartbeat Interval"))
    {
        ITS_UINT val = diaMgmt->GetHBInterval();
        oss << "Heartbeat Interval = " << val <<endl;
    }
    else if (Cmd("getHBRetry", "Get the Heartbeat Retry"))
    {
        ITS_UINT val = diaMgmt->GetHBRetry();
        oss << "Heartbeat Retry = " << val <<endl;
    }
    else if (Cmd("setHMICheckInterval", "Set the HMI Check Interval"))
    {
        ITS_UINT val;
        std::string hmiInterval = "";
 
        commandLine>> dummy >> hmiInterval;
 
        if (sscanf(hmiInterval.c_str(),"%u", &val) > 0)
        {
            if (diaMgmt->SetHMICheckInterval(val) == ITS_SUCCESS)
            {
                oss << "HMI Check Interval Set" <<endl;
            }
            else
            {
                oss << "Failed To set HMI Check Interval" << endl;
                oss << "Warning:HMICheckInterval should be greater than HMITimeout"
                    << endl;
            }
        }
        else
        {
            oss << "Invalid Parameter" << endl;
        }
 
    }
    else if (Cmd("getHMICheckInterval", "Get the HMI Check Interval"))
    {
        ITS_UINT val = diaMgmt->GetHMICheckInterval();
        oss << "HMI Check Interval = " << val <<endl;
    }
    else if (Cmd("setHMITimeout", "Set the HMI Timeout"))
    {
        ITS_UINT val;
        std::string hmiTimeout = "";
 
        commandLine>> dummy >> hmiTimeout;
 
        if (sscanf(hmiTimeout.c_str(),"%u", &val) > 0)
        {
            if (diaMgmt->SetHMITimeout(val*1000) == ITS_SUCCESS)
            {
                oss << "HMI Timeout Set" <<endl;
            }
            else
            {
                oss << "Failed To set HMI Timeout" << endl;
                oss << "Warning:HMITimeout should be less than HMICheckInterval"
                    << endl;
            }
        }
        else
        {
            oss << "Invalid Parameter" << endl;
        }
    }
    else if (Cmd("getHMITimeout", "Get the HMI Timeout"))
    {
        ITS_UINT val = diaMgmt->GetHMITimeout();
        oss << "HMI Timeout = " << (val/1000) <<endl;
    }
    else if (Cmd("setHMIRetry", "Set the HMI Retry"))
    {
        ITS_UINT val;
        std::string hmiRetry = "";
 
        commandLine>> dummy >> hmiRetry;
 
        if (sscanf(hmiRetry.c_str(),"%u", &val) > 0)
        {
            if (diaMgmt->SetHMIRetry(val) == ITS_SUCCESS)
            {
                oss << "HMI Retry Set" <<endl;
            }
            else
            {
                oss << "Failed To set HMI Retry" << endl;
            }
        }
        else
        {
            oss << "Invalid Parameter" << endl;
        }
    }
    else if (Cmd("getHMIRetry", "Get the HMI Retry"))
    {
        ITS_UINT val = diaMgmt->GetHMIRetry();
        oss << "HMI Retry = " << val <<endl;
    }
    else if (Cmd("setHMIHBInterval", "Set the HMI Heartbeat Interval"))
    {
        ITS_UINT val;
        std::string hmiHB = "";
 
        commandLine>> dummy >> hmiHB;
 
        if (sscanf(hmiHB.c_str(),"%u", &val) > 0)
        {
            if (diaMgmt->SetHMIHBInterval(val) == ITS_SUCCESS)
            {
                oss << "HMI Heatbeat interval Set" <<endl;
            }
            else
            {
                oss << "Failed To set HMI Heartbeat Interval" << endl;
            }
        }
        else
        {
            oss << "Invalid Parameter" << endl;
        }
    }
    else if (Cmd("getHMIHBInterval", "Get the HMI Heartbeat Interval"))
    {
        ITS_UINT val = diaMgmt->GetHMIHBInterval();
        oss << "HMI Heartbeat Interval = " << val <<endl;
    }
    else if (Cmd("removeDefaultRoute", "Remove Default Realm Entry"))
    {
        diaMgmt->RemoveDefaultRoute();
        oss << "Removed Default Route" << endl;
    }
    else if (Cmd("printDefaultRoute", "Print Default Realm Route"))
    {
        DESTINATION_INFO dstInfo;
        if (diaMgmt->GetDefaultRoute(&dstInfo) == ITS_SUCCESS)
        {
            oss << "Default Realm Entry:" << endl;
            oss << "Peer Name  : " << dstInfo.peerName << endl;
            oss << "Realm Name : " << dstInfo.peerRealm << endl;
        }
        else
        {
            oss << "Default Realm Not Configured" << endl;
        }
    }
    else if (Cmd("setDscpValue","Sets Dscp Values"))
    {
        std::string hostName = "";
        std::string realmName = "";
        ITS_INT val;
 
        commandLine >> dummy >> hostName >> realmName>> val;
        if(strcmp(realmName.c_str(),"") == 0)
        {
            oss << "Invalid Number of arguments" << endl;
            return;
        }
 
        if ( (val >= 0) && (val <=255) )
        {
            if (diaMgmt->SetDscpValue(hostName.c_str(), realmName.c_str(),
                                                val)== ITS_SUCCESS)
            {
                oss << " Dscp value set to : " << val <<endl;
            }   
            else
            {
                oss << "Failed to Set Dscp Val " << endl;
            }   
         }
         else
         {
             oss << "Dscp value range is from  0-255" << endl;
         }
    }
    else if (Cmd("getDscpValue","Gets Dscp Values"))
    {
        std::string hostName = "";
        std::string realmName = "";
        ITS_INT val;
 
        commandLine >> dummy >> hostName >> realmName;
        if(strcmp(realmName.c_str(),"") == 0)
        {
            oss << "Invalid Number of arguments" << endl;
            return;
        }
        val = diaMgmt->GetDscpValue(hostName.c_str(), realmName.c_str());
        if (val != 0)
        {
            oss << " Dscp value : " << val <<endl;
        }
        else
        {
            oss << " Dscp value : " << val <<endl;
            oss << " Check if DSCP enabled " << endl;
        }
    }
    else if (Cmd("enDscp", "Enable Dscp  "))
    {
        std::string hostName = "";
        std::string realmName = "";

        commandLine >> dummy >> hostName >> realmName;
        if(strcmp(realmName.c_str(),"") == 0)
        {
            oss << "Invalid Number of arguments" << endl;
            return;
        }

        if (diaMgmt->EnableDscp(hostName.c_str(), realmName.c_str())
                                              == ITS_SUCCESS)
        {
             oss << " Enable Dscp Success " << endl;
        }
        else
        {
             oss << " Enable Dscp Failed  " << endl;
        }
    }
    else if (Cmd("disDscp", "Disable Dscp  "))
    {
        std::string hostName = "";
        std::string realmName = "";

        commandLine >> dummy >> hostName >> realmName;
        if(strcmp(realmName.c_str(),"") == 0)
        {
            oss << "Invalid Number of arguments" << endl;
            return;
        }

        if (diaMgmt->DisableDscp(hostName.c_str(), realmName.c_str())
                                              == ITS_SUCCESS)
        {
             oss << " Disable Dscp Success " << endl;
        }
        else
        {
             oss << " Disable Dscp Failed  " << endl;
        }
    }
    else if (Cmd("getDiaSesionStatsViaApi", "Display Dia Session command statistics"))
    {
        int ret;
        DIA_SESS_STATS sessStats;
        memset(&sessStats,0,sizeof(DIA_SESS_STATS));
        ret = diaMgmt->GetDiaSessStats(&sessStats, false);
        if (ret == ITS_SUCCESS)
        {
            printf("DiaSessionStats\n");
            cout<<"app.reqIn :"<<sessStats.app.reqIn<<endl;
            cout<<"app.reqOut :"<<sessStats.app.reqOut<<endl;
            cout<<"app.ansIn :"<<sessStats.app.ansIn<<endl;
            cout<<"app.ansOut :"<<sessStats.app.ansOut<<endl;
            cout<<"ac.reqIn :"<<sessStats.ac.reqIn<<endl;
            cout<<"ac.reqOut :"<<sessStats.ac.reqOut<<endl;
            cout<<"ac.ansIn :"<<sessStats.ac.ansIn<<endl;
            cout<<"ac.ansOut :"<<sessStats.ac.ansOut<<endl;
            cout<<"as.reqIn :"<<sessStats.as.reqIn<<endl;
            cout<<"as.reqOut :"<<sessStats.as.reqOut<<endl;
            cout<<"as.ansIn :"<<sessStats.as.ansIn<<endl;
            cout<<"as.ansOut :"<<sessStats.as.ansOut<<endl;
            cout<<"st.reqIn :"<<sessStats.st.reqIn<<endl;
            cout<<"st.reqOut :"<<sessStats.st.reqOut<<endl;
            cout<<"st.ansIn :"<<sessStats.st.ansIn<<endl;
            cout<<"st.ansOut :"<<sessStats.st.ansOut<<endl;
            cout<<"err.reqIn :"<<sessStats.err.reqIn<<endl;
            cout<<"err.reqOut :"<<sessStats.err.reqOut<<endl;
            cout<<"err.ansIn :"<<sessStats.err.ansIn<<endl;
            cout<<"err.ansOut :"<<sessStats.err.ansOut<<endl;
        }
    }
    else if (Cmd("getDiaPeerStatsViaApi", "Display DiaPeer based message statistics"))
    {
        int ret;
        DIA_PEER_STATS peerStats;
        memset(&peerStats, 0,sizeof(DIA_PEER_STATS));
        ret = diaMgmt->GetDiaPeerStats(&peerStats, false);
        if (ret == ITS_SUCCESS)
        {
            printf("DiaPeerStats\n");
            cout<<"ce.reqIn :"<<peerStats.ce.reqIn<<endl;
            cout<<"ce.reqOut :"<<peerStats.ce.reqOut<<endl;
            cout<<"ce.ansIn :"<<peerStats.ce.ansIn<<endl;
            cout<<"ce.ansOut :"<<peerStats.ce.ansOut<<endl;
            cout<<"dw.reqIn :"<<peerStats.dw.reqIn<<endl;
            cout<<"dw.reqOut :"<<peerStats.dw.reqOut<<endl;
            cout<<"dw.ansIn :"<<peerStats.dw.ansIn<<endl;
            cout<<"dw.ansOut :"<<peerStats.dw.ansOut<<endl;
            cout<<"dp.reqIn :"<<peerStats.dp.reqIn<<endl;
            cout<<"dp.reqOut :"<<peerStats.dp.reqOut<<endl;
            cout<<"dp.ansIn :"<<peerStats.dp.ansIn<<endl;
            cout<<"dp.ansOut :"<<peerStats.dp.ansOut<<endl;
        }
    }
    else if (Cmd("getDiaIndicationsViaApi", "Display Stack Indications"))
    {
        int ret;
        DIA_INDIC_STATS indStats;
        memset(&indStats, 0, sizeof(DIA_INDIC_STATS));
        ret = diaMgmt->GetDiaIndStats(&indStats, false);
        if (ret == ITS_SUCCESS)
        {
            printf("DiaIndicStats\n");
            cout<<"numDisconnInd :"<<indStats.numDisconnInd<<endl;
            cout<<"numSessTimeoutInd :"<<indStats.numSessTimeoutInd<<endl;
            cout<<"numAuthLifeTimeoutInd :"<<indStats.numAuthLifeTimeoutInd<<endl;
        }
    }
}
