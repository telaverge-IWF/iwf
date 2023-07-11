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
 * LOG: $Log: ids_mml.cpp,v $
 * LOG: Revision 3.44.46.1  2013/02/21 11:55:18  ncshivakumar
 * LOG: Removed 3rd parameter from SetLocalHostInfo as it does not accept ip address
 * LOG:
 * LOG: Revision 3.44  2010/09/30 07:22:46  vkumara
 * LOG: MML for Enable/Disable Dscp
 * LOG:
 * LOG: Revision 3.43  2010/09/22 05:27:27  nvijikumar
 * LOG: GlobalUniqueAddr based routing/distribution support
 * LOG:
 * LOG: Revision 3.42  2010/08/31 09:35:41  vkumara
 * LOG: DSCP set and get MML commands.
 * LOG:
 * LOG: Revision 3.41  2010/08/19 11:23:06  nvijikumar
 * LOG: Porting changes from B-MOTO-IDIA-0421-00
 * LOG: 1. New Overload implimentation changes are not being ported.
 * LOG: 2. Force disconnect changes are not being ported.
 * LOG:
 * LOG: Revision 3.40  2009/10/14 10:16:52  sureshj
 * LOG: forceDisconectPeer, getPeerTimers, GetLocalHostInfo mml commands
 * LOG: added. (motorola helpDesk issues 2219, 2238).
 * LOG:
 * LOG: Revision 3.39  2009/09/07 05:05:15  rajeshak
 * LOG: MML Support to set/get HMI Heartbeat interval.
 * LOG:
 * LOG: Revision 3.38  2009/07/24 09:32:04  rajeshak
 * LOG: Changes done for
 * LOG:  1. new MML Command to print and remove default route
 * LOG:  2. Stats changes (to include option to clear stats in get)
 * LOG:
 * LOG: Revision 3.37  2009/07/15 11:33:39  rajeshak
 * LOG: Printing Proper Error when Set HMI Timers fails.
 * LOG:
 * LOG: Revision 3.36  2009/07/14 10:08:06  rajeshak
 * LOG: Changes done to include peer realm name in destination
 * LOG: (addDestination, removeDestination, modifyPriority).
 * LOG:
 * LOG: Revision 3.35  2009/07/13 12:13:01  rajeshak
 * LOG: 1. Removed printDiscoveryList MML Command.
 * LOG: 2. Converting HMITimeout value into milli sec.
 * LOG:
 * LOG: Revision 3.34  2009/07/13 06:01:57  rajeshak
 * LOG: 1. Reverting back session table changes.
 * LOG: 2. MML command to set/get the HMI Retry.
 * LOG:
 * LOG: Revision 3.33  2009/06/29 14:39:27  rajeshak
 * LOG: MML Commands added to set HMI Check Interval and Timeout.
 * LOG:
 * LOG: Revision 3.32  2009/05/08 11:18:39  rajeshak
 * LOG: Changes for MML cmd to set/get Heartbeat interval.
 * LOG:
 * LOG: Revision 3.31  2009/04/17 09:11:35  rajeshak
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 3.30  2009/04/13 13:50:33  rajeshak
 * LOG: MML Api added for Peer discovery and modify destination priority.
 * LOG:
 * LOG: Revision 3.29  2009/04/11 09:57:26  nvijikumar
 * LOG: Provided following commands:
 * LOG: enHexDump, getOverloadLimits, disHexDump, isHexDumpEnabled
 * LOG:
 * LOG: Revision 3.28  2009/04/10 06:41:57  sureshj
 * LOG: enableHMI, disableHMI, isHMIEnabled  MML Commands added.
 * LOG:
 * LOG: Revision 3.27  2009/04/07 14:04:36  sureshj
 * LOG: MML command setOverloadThresholds added to set overload control
 * LOG: threshold values minT and MaxThreshold.
 * LOG:
 * LOG: Revision 3.26  2009/04/07 12:41:39  rajeshak
 * LOG: removed priority in removeDestination MML command.
 * LOG:
 * LOG: Revision 3.25  2009/03/26 09:41:02  rajeshak
 * LOG: GetPeerStatus MML API Support
 * LOG:
 * LOG: Revision 3.24  2009/03/24 09:17:25  rajeshak
 * LOG: MML APIs disconnectAllPeer, removeAltPeer, modifyAltPeer Added.
 * LOG:
 * LOG: Revision 3.23  2009/03/24 03:09:08  nvijikumar
 * LOG: Changes in Command names
 * LOG:
 * LOG: Revision 3.22  2009/03/19 12:43:31  rajeshak
 * LOG: MML command to set the default route.
 * LOG:
 * LOG: Revision 3.21  2009/03/16 04:34:01  sureshj
 * LOG: IssueId: 1741
 * LOG: Feature Id: None
 * LOG: Description: MML Command: 'setAcctTimers' is taking 'realtime' value
 * LOG: as an input parameter.
 * LOG:
 * LOG: Revision 3.20  2009/03/03 13:49:21  sureshj
 * LOG: MML commands added for setting Peer, AuthSession timer values and
 * LOG: LocalHost info Dynamically.
 * LOG:
 * LOG: Revision 3.19  2009/03/03 10:34:09  nvijikumar
 * LOG: Removed IDS upstream and IDS downstream pegs as these queue are no more
 * LOG:
 * LOG: Revision 3.18  2009/02/04 09:34:38  chandrashekharbs
 * LOG: xml persistency command changed to diaCommit from dia_commit
 * LOG:
 * LOG: Revision 3.17  2009/01/28 06:54:08  chandrashekharbs
 * LOG: Debug console command dia_commit added
 * LOG:
 * LOG: Revision 3.16  2008/12/23 15:07:27  ssaxena
 * LOG: Renaming Disconnect API
 * LOG:
 * LOG: Revision 3.15  2008/12/22 06:40:51  sureshj
 * LOG: Output display added for statistics mml commands.
 * LOG:
 * LOG: Revision 3.14  2008/12/12 08:05:54  sureshj
 * LOG: Support for Stack Statistics
 * LOG:
 * LOG: Revision 3.13  2008/12/01 07:22:50  sureshj
 * LOG: 1. New MML command to start individual Peer
 * LOG: 2. Updates for disconnetPeer to send proper disc cause
 * LOG:
 * LOG: Revision 3.12  2008/11/06 07:46:26  rajeshak
 * LOG: IDS Connection Status Information (Establishment time)
 * LOG:
 * LOG: Revision 3.11  2008/10/31 05:35:24  nvijikumar
 * LOG: IssueID:1189
 * LOG: FeatureID: none
 * LOG: Description: 1. Introducing additional TQs and Threads for better
 * LOG:                 Performance on PP50 and initial stack tunning
 * LOG:              2. Unwanted code cleanup
 * LOG:
 * LOG: Revision 3.10  2008/09/08 11:23:36  ssaxena
 * LOG: Added new MML Command switchOver and getNodeState for redundancy.
 * LOG: (Viji/Hemant).
 * LOG:
 * LOG: Revision 3.9  2008/08/27 10:52:41  ssaxena
 * LOG: Added failback option in addAlternatePeer command.
 * LOG:
 * LOG: Revision 3.8  2008/08/21 06:08:14  yranade
 * LOG: Added commands to print QSize, SessionTable size and SessionTable details.
 * LOG:
 * LOG: Revision 3.7  2008/07/23 12:17:54  ssaxena
 * LOG: Provided Dynamic API to send DPR from MML (Requested by Motorola)
 * LOG:
 * LOG: Revision 3.6  2008/04/25 08:46:13  nanaparthi
 * LOG: Commented the addIp MML Command functionality
 * LOG:
 * LOG: Revision 3.5  2008/04/24 14:13:27  nanaparthi
 * LOG: Added removeDestination for Issue #891
 * LOG:
 * LOG: Revision 3.4  2008/04/22 16:46:37  nanaparthi
 * LOG: Fix for Whizible Issue id: 849
 * LOG: Changes done to support new addRealm dynamic API.
 * LOG:
 * LOG: Revision 3.3  2008/04/16 13:20:01  hbhatnagar
 * LOG: Incorporated changes for Code review comments(Avinash)
 * LOG:
 * LOG: Revision 3.2  2008/04/01 16:55:16  hbhatnagar
 * LOG: Changes for Proxy and Relay support 3.0 release - (Hemant, Avinash)
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:04  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2007/01/30 04:54:25  nanaparthi
 * LOG: MML application for Distributed mode
 * LOG:
 *
 * ID: $Id: ids_mml.cpp,v 3.44.46.1 2013/02/21 11:55:18 ncshivakumar Exp $
 ****************************************************************************/

#include <dia_trace.h>

#include <ids_msghandler.h>
#include <ids_mml.h>
#include <ids_conndb.h>

#include <dia_mgmt.h>
#include <dia_config.h>
#include <dia_stack_stats.h>
#include <ids_routedb.h>

/* Conflict Resolution on Linux
*/

#if defined(IPPROTO_SCTP)
#undef IPPROTO_SCTP
#endif

#include <dia_frame.h>
#include <dia_msg_router.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
#endif

extern ConnectionTable conTable;
extern MsgHandler    *msgHandler;
extern AppToStackMsgHandler  *appMsgHandler;
extern RouteTable routeTable;

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
IDSMMLServer::DoCommand(istream& commandLine)
{
    string dummy;
    DiaMgmt *diaMgmt = DiaMgmt::GetDiaMgmt();
    PEER_INFO pInfo;
    ALT_PEER_INFO aInfo;
    DESTINATION_INFO dInfo;
    int found = 0;
    /* 
     * Command to display the TPS
     */
    if (Cmd("enTrace", "Enable All Traces"))
    {
        DiaTrace::GetDiaTrace()->Enable();

	oss <<"*****All the traces are enabled*****" << endl;
    }
    else if (Cmd("disTrace", "Disable All Traces"))
    {
        DiaTrace::GetDiaTrace()->Disable();

	oss <<"*****All the traces are disabled*****" << endl;
    }
    else if (Cmd("enDiaDebTrace", "Enable Dia Debug Traces"))
    {
        DiaTrace::GetDiaTrace()->Enable(DIA_DEBUG);
	
	oss <<"*******Diameter Debug Traces are enabled*******" << endl;
    }
    else if (Cmd("enDiaErrTrace", "Enable Dia Error Traces"))
    {
        DiaTrace::GetDiaTrace()->Enable(DIA_ERROR);

	oss <<"*******Diameter Error Traces are enabled*******" << endl;
    }
    else if (Cmd("enDiaWarnTrace", "Enable Dia Warning Traces"))
    {
        DiaTrace::GetDiaTrace()->Enable(DIA_WARNING);
	
	oss <<"*******Diameter Warning Traces are enabled*******" << endl;
    }
    else if (Cmd("enDiaCritTrace", "Enable Dia Critical Traces"))
    {
        DiaTrace::GetDiaTrace()->Enable(DIA_CRITICAL);

	oss <<"*******Diameter Critical Traces are enabled*******" << endl;
    }
    else if (Cmd("disDiaDebTrace", "Disable Dia Debug Traces"))
    {
        DiaTrace::GetDiaTrace()->Disable(DIA_DEBUG);

	oss <<"*******Diameter Debug Traces are disabled*******" << endl;
    }
    else if (Cmd("disDiaErrTrace", "Disable Dia Error Traces"))
    {
        DiaTrace::GetDiaTrace()->Disable(DIA_ERROR);

	oss <<"*******Diameter Error Traces are disabled*******" << endl;
    }
    else if (Cmd("disDiaCritTrace", "Disable Dia Critical Traces"))
    {
        DiaTrace::GetDiaTrace()->Disable(DIA_CRITICAL);

	oss <<"*******Diameter Critical Traces are disabled*******" << endl;
    }
    else if (Cmd("disDiaWarnTrace", "Disable Dia Warning Traces"))
    {
        DiaTrace::GetDiaTrace()->Disable(DIA_WARNING);

	oss <<"*******Diameter Warning Traces are disabled*******" << endl;
    }
    else if (Cmd("getDiaTrace", "Get Dia Tracing Info"))
    {
        DiaTrace::GetDiaTrace()->Display(oss);
    }
    else if (Cmd("enStatistics", "Enable Dia Stack Statistics "))
    {
        if(diaMgmt->EnableStatistics() == ITS_SUCCESS)
        {
            oss<<" Successfully Enabled statistics"<<endl;  
        }
    }
    else if (Cmd("disStatistics", "Disable Dia Stack Statistics "))
    {
        if(diaMgmt->DisableStatistics() == ITS_SUCCESS)
        {
            oss<<" Successfully Disabled statistics"<<endl;
        } 
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
        unsigned int clrFlag = 0;

        commandLine >> dummy >> clrFlag;

        if (clrFlag == 0)
        {
            diaMgmt->GetDiaStackStats(oss, false);
        }
        else if (clrFlag == 1)
        {
            diaMgmt->GetDiaStackStats(oss, true);
        }
        else
        {
            oss<<" ********Invalid Option ********";
        }
    }
    else if (Cmd("getDiaSesionStats", "Display Dia Session command statistics"))
    {
        unsigned int clrFlag = 0;

        commandLine >> dummy >> clrFlag;

        if (clrFlag == 0)
        {
            diaMgmt->GetDiaSessionStats(oss, false);
        }
        else if (clrFlag == 1)
        {
            diaMgmt->GetDiaSessionStats(oss, true);
        }
        else
        {
            oss<<" ********Invalid Option ********";
        }
    }
    else if (Cmd("getDiaPeerStats", "Display DiaPeer based message statistics"))
    {
        unsigned int clrFlag = 0;

        commandLine >> dummy >> clrFlag;

        if (clrFlag == 0)
        {
            diaMgmt->GetDiaPeerStats(oss, false);
        }
        else if (clrFlag == 1)
        {
            diaMgmt->GetDiaPeerStats(oss, true);
        }
        else
        {
            oss<<" ********Invalid Option ********"; 
        }
    }
    else if (Cmd("getDiaIndications", "Display Stack Indications"))
    {
        unsigned int clrFlag = 0;
        commandLine >> dummy >> clrFlag;

        if (clrFlag == 0)
        {
            diaMgmt->GetDiaIndicStats(oss, false);
        }
        else if (clrFlag == 1)
        {
            diaMgmt->GetDiaIndicStats(oss, true);
        }
        else
        {
            oss<<" ********Invalid Option ********";
        }
    }
    else if (Cmd("getDiaMiscStats", "Display Miscellaneous Stats"))
    {
        unsigned int clrFlag = 0;

        commandLine >> dummy >> clrFlag;

        if (clrFlag == 0)
        {
            diaMgmt->GetDiaMiscStats(oss, false);
        }
        else if (clrFlag == 1)
        {
            diaMgmt->GetDiaMiscStats(oss, true);
        }
        else
        {
            oss<<" ********Invalid Option ********";
        }
    }
    else if (Cmd("getPeerStatus", "Display Peer Status"))
    {
        std::string hostName = "";
        std::string realmName = "";
        memset(&pInfo, 0, sizeof(PEER_INFO));

        commandLine >> dummy >> hostName >> realmName ;

        pInfo.peerName = hostName.c_str();
        pInfo.realmName = realmName.c_str();

        diaMgmt->GetDiaPeerStatus(oss, &pInfo); 
    }
    else if (Cmd("resetStackStats", "Reset Dia statistics Info"))
    {
        if(diaMgmt->ResetStackStats() == ITS_SUCCESS)
        {
            oss << " Successfully Reset statistics" << endl;
        }
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
    else if (Cmd("idcConns", "Prints All IDC connection Info"))
    {
	oss << conTable ;
    }
    else if (Cmd("printIdsRouteTbl", "Prints All IDS rounte Table Info"))
    {
	routeTable.Print(oss);
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
    else if (Cmd("setRouteScheme"," Set Route Scheme"))
    {
        std::string routescheme = "";
         DiaConfig *cfg = DiaConfig::GetDiaConfig();
         char *routingScheme;
         commandLine>> dummy >>routescheme;

         if(cfg)
         {
             routingScheme = cfg->SetRouteScheme(const_cast<char *>(routescheme.c_str()));
         }
         else
         {
             oss << "cfg is NULL" << endl;
         }

         if ( (routingScheme != NULL) && !strcmp(routingScheme, "roundrobin"))
         {
             routeScheme = IDS_ROUND_ROBIN;
             oss << "Successfully set routing scheme as roundrobin " << endl;
         }
         else if ( (routingScheme != NULL) && !strcmp(routingScheme, "broadcast"))
         {
             routeScheme = IDS_BROADCAST;
             oss << "Successfully set routing scheme as broadcast " << endl;
         }
         else if ( (routingScheme != NULL) && !strcmp(routingScheme, "globaluniqueaddr"))
         {
             routeScheme = IDS_GLOBAL_UNIQ_ADDR;
             oss << "Successfully set routing scheme as globaluniqueaddr " << endl;
         }
         else
         {
             oss << "Fail : routing scheme input should be roundrobin or broadcast" << endl;
         }
    }
    else if (Cmd("getRouteScheme"," Get Route Scheme"))
    {
         if (routeScheme == IDS_ROUND_ROBIN )
         {
             oss << "Configured Routing Scheme : roundrobin"<< endl;
         }
         else if(routeScheme == IDS_BROADCAST )
         {
             oss << "Configured Routing Scheme : broadcast "<< endl;
         }
         else if(routeScheme == IDS_GLOBAL_UNIQ_ADDR )
         {
             oss << "Configured outing Scheme : Global Unique Addr "<< endl;
         }
         else
         {
             oss << "Fail : Invalid  Route Scheme "<< endl;

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

}
