/**************************-*-Dia-*-*************************************
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
 *  LOG: $Log: dia_mgmt.h,v $
 *  LOG: Revision 3.38.6.9.4.13.2.3.2.4.6.1.4.1  2014/09/16 09:52:26  jsarvesh
 *  LOG: Chnages done for Peer wise Statistics enhancement
 *  LOG:
 *  LOG: Revision 3.38.6.9.4.13.2.3.2.4.6.1  2014/07/02 06:37:11  millayaraja
 *  LOG: updated to handle answer message without mandatory field missing
 *  LOG:
 *  LOG: Revision 3.38.6.9.4.13.2.3.2.4  2013/12/13 09:34:58  vsarath
 *  LOG: Merged the session-splict changes
 *  LOG:
 *  LOG: Revision 3.38.6.9.4.13.2.3.2.3  2013/10/26 12:46:23  ncshivakumar
 *  LOG: Included header unorederd_map
 *  LOG:
 *  LOG: Revision 3.38.6.9.4.13.2.3.2.2  2013/10/26 07:42:21  ncshivakumar
 *  LOG: RFC 6733 changes
 *  LOG:
 *  LOG: Revision 3.38.6.9.4.13.2.3.2.1  2013/09/10 08:36:39  ncshivakumar
 *  LOG: RFC6733 Changes
 *  LOG:
 *  LOG: Revision 3.38.6.9.4.13.2.3  2013/06/07 05:19:38  jkchaitanya
 *  LOG: Bug 1615,1614, ReviewRequest 1018
 *  LOG:
 *  LOG: Revision 3.38.6.9.4.13.2.2  2013/05/24 10:35:56  ncshivakumar
 *  LOG: Fix for bug 1580
 *  LOG:  VS: ----------------------------------------------------------------------
 *  LOG:
 *  LOG: Revision 3.38.6.9.4.13.2.1  2013/05/10 08:49:52  ncshivakumar
 *  LOG: Updated for Static routing table configuaration
 *  LOG:
 *  LOG: Revision 3.38.6.9.4.13  2013/04/16 05:41:34  ncshivakumar
 *  LOG: changes for bug1418
 *  LOG:
 *  LOG: Revision 3.38.6.9.4.12  2013/04/01 05:43:03  vsarath
 *  LOG: Fix for Coverity warnings
 *  LOG:
 *  LOG: Revision 3.38.6.9.4.11  2013/03/12 04:49:43  vsarath
 *  LOG: Fix for coverity issue
 *  LOG:
 *  LOG: Revision 3.38.6.9.4.10  2013/03/05 06:52:02  ncshivakumar
 *  LOG: Multihome changes
 *  LOG:
 *  LOG: Revision 3.38.6.9.4.9  2013/02/27 08:49:07  jvikram
 *  LOG: Warnings raised by Coverity have been fixed
 *  LOG:
 *  LOG: Revision 3.38.6.9.4.8  2013/02/25 13:46:12  mallikarjun
 *  LOG: Undo Previous changes
 *  LOG:
 *  LOG: Revision 3.38.6.9.4.7  2013/02/25 13:34:57  mallikarjun
 *  LOG: Bug 623 changes DWR
 *  LOG:
 *  LOG: Revision 3.38.6.9.4.6  2013/02/25 13:16:42  mallikarjun
 *  LOG: Bug 623 changes
 *  LOG:
 *  LOG: Revision 3.38.6.9.4.5  2013/02/21 11:17:29  ncshivakumar
 *  LOG: modified for multitransport support
 *  LOG:
 *  LOG: Revision 3.38.6.9.4.4  2013/02/21 10:20:34  jkchaitanya
 *  LOG: Mar31 CMAPI Features
 *  LOG:
 *  LOG: Revision 3.38.6.9.4.3  2013/02/19 11:05:57  jsarvesh
 *  LOG: dre global stats implementation
 *  LOG:
 *  LOG: Revision 3.38.6.9.4.2  2013/01/30 04:16:18  pramana
 *  LOG: Used std::string in AssociateDict.
 *  LOG:
 *  LOG: Revision 3.38.6.9.4.1  2013/01/29 11:37:40  pramana
 *  LOG: DDL Changes
 *  LOG:
 *  LOG: Revision 3.38.6.9  2012/12/20 12:12:50  pramana
 *  LOG: Merging changes from CMGR branch
 *  LOG:
 *  LOG: Revision 3.38.6.8  2012/12/13 04:06:59  jsarvesh
 *  LOG: changes done for stop peer functionality
 *  LOG:
 *  LOG: Revision 3.38.6.7.2.2  2012/12/16 12:16:52  rgovardhan
 *  LOG: Logging Configuration for DTF
 *  LOG:
 *  LOG: Revision 3.38.6.7.2.1  2012/12/12 12:11:28  rgovardhan
 *  LOG: DRE Config related and dia_mgmt changes
 *  LOG:
 *  LOG: Revision 3.38.6.7  2012/11/20 17:39:44  pramana
 *  LOG: Merged from CMAPI branch for 212-07 release
 *  LOG:
 *  LOG: Revision 3.38.6.1.8.3  2012/11/20 10:28:35  rgovardhan
 *  LOG: merge from 00 Nov20Rel
 *  LOG:
 *  LOG: Revision 3.38.6.1  2012/10/17 14:31:03  jsarvesh
 *  LOG: modification for dictionary id
 *  LOG:
 *  LOG: Revision 3.38  2010/10/11 05:08:57  nvijikumar
 *  LOG: Motorola's changes incorporation for field compilation issue
 *  LOG:
 *  LOG: Revision 3.37  2010/09/30 06:45:03  vkumara
 *  LOG: Introduced APIs to Enable/Disable DSCP
 *  LOG:
 *  LOG: Revision 3.36  2010/08/27 12:29:23  nvijikumar
 *  LOG: DSCP value support IP Header (Vasanth)
 *  LOG:
 *  LOG: Revision 3.35  2009/10/14 10:28:10  sureshj
 *  LOG: forceDisconectPeer, getPeerTimers, GetLocalHostInfo mml commands
 *  LOG: added. (motorola helpDesk issues 2219, 2238).
 *  LOG:
 *  LOG: Revision 3.34  2009/09/07 05:01:01  rajeshak
 *  LOG: MML Support to set/get HMI Heartbeat interval.
 *  LOG:
 *  LOG: Revision 3.33  2009/07/24 09:30:28  rajeshak
 *  LOG: Changes done for
 *  LOG:  1. new MML Command to print and remove default route
 *  LOG:  2. Stats changes (to include option to clear stats in get)
 *  LOG:
 *  LOG: Revision 3.32  2009/07/14 10:05:46  rajeshak
 *  LOG: Changes done to include peer realm name  in destination.
 *  LOG:
 *  LOG: Revision 3.31  2009/07/13 06:47:22  rajeshak
 *  LOG: 1. Reverting back session table changes.
 *  LOG: 2. MML command to set/get the HMI Retry.
 *  LOG:
 *  LOG: Revision 3.30  2009/06/29 14:44:41  rajeshak
 *  LOG: 1. MML Commands added to set HMI Check Interval and Timeout.
 *  LOG: 2. Changes for Queue stats and session table size.
 *  LOG:
 *  LOG: Revision 3.29  2009/05/11 06:18:09  rajeshak
 *  LOG: Following Changes are done.
 *  LOG:   1. Added API to Get/Set Heartbeat Interval and Retry.
 *  LOG:   2. Added variable for storing Conn Establishment time in Peer Status.
 *  LOG:
 *  LOG: Revision 3.28  2009/04/17 10:39:08  rajeshak
 *  LOG: Changes for compilation error in static pkg
 *  LOG:
 *  LOG: Revision 3.27  2009/04/17 09:32:28  rajeshak
 *  LOG: Function to print Peer discovery List
 *  LOG:
 *  LOG: Revision 3.26  2009/04/13 13:43:51  rajeshak
 *  LOG: Peer Discovery changes and changes for new MML Modify destination Priority.
 *  LOG:
 *  LOG: Revision 3.25  2009/04/11 09:55:51  nvijikumar
 *  LOG: Provided APIs to get/set HexDump values
 *  LOG: Provided API to GetOvloadThresholds
 *  LOG:
 *  LOG: Revision 3.24  2009/04/10 06:24:12  sureshj
 *  LOG: APIs to Enable and Disable Health Monitor Interface using MML commands.
 *  LOG:
 *  LOG: Revision 3.23  2009/04/07 14:00:13  sureshj
 *  LOG: SetOverloadThreshold API defined for setting threshold values
 *  LOG: for Overload control.
 *  LOG:
 *  LOG: Revision 3.22  2009/03/26 09:36:54  rajeshak
 *  LOG: GetPeerStatus MML API Support
 *  LOG:
 *  LOG: Revision 3.21  2009/03/26 05:32:47  nvijikumar
 *  LOG: GetDiaMiscStats and ResetAllStats API Support
 *  LOG:
 *  LOG: Revision 3.20  2009/03/19 08:44:20  rajeshak
 *  LOG: Added function to set default route.
 *  LOG:
 *  LOG: Revision 3.19  2009/03/18 12:50:31  rajeshak
 *  LOG: Added functions for new MML command and API.
 *  LOG:
 *  LOG: Revision 3.18  2009/03/17 10:05:44  sureshj
 *  LOG: IssueId: 1730
 *  LOG: Description: IDS dumps core when using printRealmtable after removing
 *  LOG: dynamically added Peer which was added as Destination for dynamically
 *  LOG: added Realm.
 *  LOG:
 *  LOG: Revision 3.17  2009/03/03 13:47:24  sureshj
 *  LOG: APIs added for Dynamic configuration of timers and localhost Info.
 *  LOG:
 *  LOG: Revision 3.16  2009/03/02 04:42:33  nvijikumar
 *  LOG: Enhancements for MML API Support
 *  LOG:
 *  LOG: Revision 3.15  2009/01/28 06:45:49  chandrashekharbs
 *  LOG: Initial Commit for xml persistency
 *  LOG:
 *  LOG: Revision 3.14  2008/12/23 15:04:51  ssaxena
 *  LOG: Renaming Disconnect API
 *  LOG:
 *  LOG: Revision 3.13  2008/12/22 06:38:36  sureshj
 *  LOG: Return values changed from void to ITS_UINT .
 *  LOG:
 *  LOG: Revision 3.12  2008/12/12 07:54:26  sureshj
 *  LOG: Initial draft for Stack Statistics support (Suresh)
 *  LOG:
 *  LOG: Revision 3.11  2008/12/01 07:14:43  sureshj
 *  LOG: API to start individual Peer
 *  LOG:
 *  LOG: Revision 3.10  2008/09/08 12:13:33  ssaxena
 *  LOG: Added APIs SwitchOver() and GetNodeState() for redundancy. (Viji)
 *  LOG:
 *  LOG: Revision 3.9  2008/08/27 10:53:54  ssaxena
 *  LOG: Added failback option in addAlternatePeer command.
 *  LOG:
 *  LOG: Revision 3.8  2008/08/25 06:48:51  nvijikumar
 *  LOG: Proper declaration of member funcs GetTableSize(), GetSessionTableSize()
 *  LOG: PrintSessionTable()
 *  LOG:
 *  LOG: Revision 3.7  2008/08/21 06:07:08  yranade
 *  LOG: Added APIs to print QSize, SessionTable size and SessionTable details.
 *  LOG:
 *  LOG: Revision 3.6  2008/07/23 12:23:47  ssaxena
 *  LOG: Provided Dynamic API to send DPR from MML (Requested by Motorola)
 *  LOG:
 *  LOG: Revision 3.5  2008/04/25 10:59:58  nanaparthi
 *  LOG: Fix for Issue #891
 *  LOG:
 *  LOG: Revision 3.4  2008/04/21 11:59:55  nanaparthi
 *  LOG: Fix for Issue #849 : Changed Prototype
 *  LOG:
 *  LOG: Revision 3.3  2008/04/16 11:53:36  hbhatnagar
 *  LOG: Made changes to incorporate review comments (Avinash).
 *  LOG:
 *  LOG: Revision 3.2  2008/04/01 16:07:37  hbhatnagar
 *  LOG: Changes for Proxy and Relay support 3.0 release - (Viji, Hemant)
 *  LOG:
 *  LOG: Revision 1.2  2007/01/29 13:46:56  nanaparthi
 *  LOG: Enhancements made for AddPeer() , AddAlternatePeer() APIs
 *  LOG:
 *  LOG: Revision 1.1  2007/01/12 05:58:27  nanaparthi
 *  LOG: APIs for Dynamic Configuration Support
 *  LOG:
 *  LOG: 
 ****************************************************************************/
#ident "$Id: dia_mgmt.h,v 3.38.6.9.4.13.2.3.2.4.6.1.4.1 2014/09/16 09:52:26 jsarvesh Exp $"
 
#ifndef _DIAMETER_MGMT_H
#define _DIAMETER_MGMT_H


#include <its++.h>
#include <dia_defines.h>
#include <iostream>
#include <unordered_map>


#define MAX_PARAM_LEN 128
typedef enum
{
   DIA_AUTH_APP = 1,
   DIA_ACCT_APP,
   DIA_VENDOR_SPECIFIC_AUTH_APP,
   DIA_VENDOR_SPECIFIC_ACTT_APP
}
APPLICATION_TYPE;
typedef enum
{
    DIA_TRANS_TCP = 0,
    DIA_TRANS_SCTP,
    DIA_TRANS_INVALID
}
MGMT_TR_TYPE;

typedef struct
{
    ITS_UINT noOfQueues;
    ITS_UINT qCount[MAX_ROUTER_THREADS];
}DIA_QUEUE_STATS;

typedef struct
{
    ITS_UINT noOfSessTables;
    ITS_UINT stSize[MAX_ROUTER_THREADS];
}DIA_ST_STATS;

/***************************************************************
 * This definition is used in function SetProxyInfoAVPEnabled  *
 * Defined to use only for MML commands.                       *
 ***************************************************************/
#define ERROR_REALM_NOT_CORRECT 2

/** Structure:
 *      PEER_INFO
 *       
 *  Purpose:
 *      PEER_INFO structure is used to represent an Peer Configuration 
 *      
 **/
typedef struct peer_entry
{
    const char         *peerName;
    const char         *realmName;
    MGMT_TR_TYPE       type;
    const char         *ipAddr;
    const char         **multiHomeipaddrs;
    unsigned int       noIPs;
    unsigned short     port;
    bool		tlsEnabled;
    bool		status;
    ITS_UINT   		expiry;
    ITS_UINT   		retry;
    ITS_UINT   		watchdog;
    ITS_UINT   		retransIntvl;
    ITS_UINT   		retransCount;
    ITS_UINT        busyReconnectTimerVal;
    ITS_UINT        doNotWantToTalkYouReconnectTimerVal;
    bool            isSupportDisconnectCause;
    unsigned short  securePort;
    bool            isRetransmissionEnabled;
    peer_entry():status(true)
    {
       peerName  =  NULL;
       realmName = NULL;
       type = DIA_TRANS_INVALID;
       ipAddr = NULL;
       port = 0;
       tlsEnabled = false;
       status = true;
       noIPs = 0;
       multiHomeipaddrs = NULL;
       expiry = 0;
       retry = 0;
       watchdog = 0;
       retransIntvl = 0;
       retransCount = 0;
       busyReconnectTimerVal = 0;
       doNotWantToTalkYouReconnectTimerVal = 0;
       isSupportDisconnectCause = false;
       securePort = 0;
       isRetransmissionEnabled = false;
    }
}
PEER_INFO;


typedef struct local_host_info
{
    const char *hostName;
    const char *realmName;
    const char *ipAddr;
}
LOCAL_HOST_INFO;


/** Structure:
 *      ALT_PEER_INFO
 *
 *  Purpose:
 *      ALT_PEER_INFO structure is used to represent an Alternate Peer 
 *      Configuration
 *
 **/
typedef struct alternate_peer_entry
{
    const char         *peerName;
    const char         *realmName;
    const char         *altHost;
    const char         *altRealmName;
    bool               isFailoverEnable;
    bool               isFailbackEnable;
    bool               isRedundantMate;
}
ALT_PEER_INFO;

/** Structure:
 *      DIA_TRACE_INFO
 *
 *  Purpose:
 *      DIA_TRACE_INFO structure is used to represent DiaTrace information
 *
 **/
typedef struct 
{
    ITS_BOOLEAN all;
    ITS_BOOLEAN dbg;
    ITS_BOOLEAN wrn;
    ITS_BOOLEAN err;
    ITS_BOOLEAN crt;
}    
DIA_TRACE_INFO;

/** Structure:
 *      DIA_QUEUE_STATS
 *
 *  Purpose:
 *      DIA_QUEUE_STATS structure is used to represent DiaQueueStats information
 *
 **/
/*typedef struct 
{
    ITS_UINT upQCount;
    ITS_UINT downQCount;
}DIA_QUEUE_STATS;
*/
/** Structure:
 *      DESTINATION_INFO
 *
 *  Purpose:
 *      DESTINATION_INFO structure is used to represent an Peer Configuration 
 *      
 **/
typedef struct dest_entry
{
    const char         *realmName;
    const char         *peerName;
    const char         *peerRealm;
    unsigned int       applicationId;
    unsigned int       vendorId;
    unsigned int       priority;
}
DESTINATION_INFO;

/** Structure:
 *      
 *
 *  Purpose:
 *      Tranport Type of Distributed server & client connection
 *
 *  Note:
 *      This should be same as IDC_CONN_STATUS_INFO defined in ids_common.h 
 *      & DM_IDC_CONN_INFO defined in mgmt
 *
 **/
typedef struct
{
    ITS_UINT appIdentifier;
    ITS_UINT appIdType;
}
DIA_DIST_CONN_INFO;

/*
 * enum PEER_STATE
 *
 */
typedef enum
{
    PEER_CLOSED,
    PEER_WAIT_CONN_ACK,
    PEER_WAIT_I_CEA,
    PEER_WAIT_CONN_ACK_ELECT,
    PEER_WAIT_RETURNS,
    PEER_I_OPEN,
    PEER_R_OPEN,
    PEER_CLOSING,
    PEER_MAX
}PEER_FSM_STATE;


/** Structure:
 *  
 *
 *  Purpose:
 *      Peer Status 
 *
 *  Note:
 *
 **/
typedef struct
{
    char            peerName[MAX_PARAM_LEN];
    char            realmName[MAX_PARAM_LEN];
    MGMT_TR_TYPE    type;
    char            ipAddr[MAX_PARAM_LEN];
    unsigned short  port;
    PEER_FSM_STATE  pState;
    ITS_UINT        isStatic;  
    time_t          connEstTime;
}
DIA_PEER_STATUS;

typedef struct
{
   char *peerName;
   char *realmName;
   PEER_FSM_STATE  pState;
   bool  isRetransmissionEnabled;
}
DIA_PEER_STATES;


struct _peer_entry;

/** Interface:
 *      DiaMgmt
 *
 *  Purpose:
 *      DiaMgmt class is used for Dynamic Configuration
 *      to or from the Diameter Stack.
 **/
class DiaMgmt
{
public:
    
    /********************************************************************/
    /** Purpose:
    *       API to add the Peer Configuration of the type PEER_INFO
    *
    *  Input Parameters:
    *       PEER_INFO
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/

    int AddPeer(PEER_INFO* pEntry);

    int ModifyDictId(PEER_INFO* pEntry,int& dict_count,int* dict_id);

    /********************************************************************/
    /** Purpose:
    *       API to add the Associate Dictionary to the Peer
    *
    *  Input Parameters:
    *       PEER_INFO, Dict Count, Array of DictNames
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    int AssociateDictToPeer(PEER_INFO* pInfo, int& dict_count,
                            std::string *dictNames,APPLICATION_TYPE type[],bool checkIsDictNelwyLoadded = false);

    int RemoveDictId(PEER_INFO* pInfo, int& dict_count, int* dict_Id); 
    /********************************************************************/
    /** Purpose:
    *       API to add the Alternate Peer Configuration
    *
    *  Input Parameters:
    *      ALT_PEER_INFO 
    *                    
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *              
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/

    int AddAlternatePeer(ALT_PEER_INFO* aEntry); 

    
    /********************************************************************/
    /** Purpose:
    *       API to modify the Alternate Peer Configuration
    *
    *  Input Parameters:
    *      ALT_PEER_INFO
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/

    int GetAlternatePeerForPeer(ALT_PEER_INFO* aEntry);
    int ModifyAlternatePeer(ALT_PEER_INFO* aEntry);


    /********************************************************************/
    /** Purpose:
    *       API to remove the Alternate Peer Configuration
    *
    *  Input Parameters:
    *      const char* hostName, const char* realmName
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/

    int RemoveAlternatePeer(const char* hostName, const char* realmName);
    
    /********************************************************************/
    /** Purpose:
    *       API to remove the secondary ip address of peer
    *
    *  Input Parameters:
    *      hostName, realmName,Secondary ips to
    *      be removed, number of ips
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/

    int RemoveSecondaryIp(const char* hostName, const char* realmName,
                          char** multiHomeIpAddrs,int noIPs);
    
    /********************************************************************/
    /** Purpose:
    *       API to Add the secondary ip address of peer
    *
    *  Input Parameters:
    *      hostName, realmName,Secondary ips to
    *      be added, number of ips
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/

    int AddSecondaryIp(const char* hostName, const char* realmName,
                          char** multiHomeIpAddrs,int noIPs);

    /********************************************************************/
    /** Purpose:
    *       API to get the IDC connection status information 
    *
    *  Input Parameters:
    *      clientId, DIA_DIST_CONN_INFO
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/

    int GetIdcConnStatus(int clientId, DIA_DIST_CONN_INFO* connInfo);

    /********************************************************************/
    /** Purpose:
    *       API to Get the DiaTrace info
    *  
    *  Input Parameters:
    *      DIA_TRACE_INFO
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/

    int GetDiaTrace(void* arg);

    /********************************************************************/
    /** Purpose:
    *       API to Get the DiaQueur stats
    *
    *  Input Parameters:
    *      int
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/

    int GetDiaQStat(DIA_QUEUE_STATS* stats);

    /********************************************************************/
    /** Purpose:
    *       API to starts all the Peers which are configured
    *  
    *  Input Parameters:
    *       None
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
   
    int StartAllPeers();

    /********************************************************************/
    /** Purpose:
    *       API to start the Peer which is configured
    *  
    *  Input Parameters:
    *       None
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
 
    int StartPeer(const char* hostName,
                   const char* realmName);
    
    /********************************************************************/
    /** Purpose:
    *       API to Removes the Peer entry 
    *  
    *  Input Parameters:
    *      hostName, realmName 
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/

    int RemovePeer(const char* hostName,
                   const char* realmName);

 
    /********************************************************************/
    /** Purpose:
    *       API to DisconnectPeer  the Peer
    *  
    *  Input Parameters:
    *      hostName, realmName, disCause 
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
 
    int DisconnectPeer(const char* hostName,
        const char* realmName, ITS_INT disCause);

    /* API to Disconnect Peer Forcefully */
    int ForceDisconectPeer(const char* hostName, const char* realmName, 
                           ITS_INT disCause ,ITS_INT expiry);
    /********************************************************************/
    /** Purpose:
    *       API to DisconnectAllPeer  the Peer
    *
    *  Input Parameters:
    *      disCause
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/

    int DisconnectAllPeers(ITS_UINT disCause);

    /********************************************************************/
    /** Purpose:
    *       API to Add the Realm entry
    *
    *  Input Parameters:
    *      realmName
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/

    int AddRealm(const char* realmName,const char* localAction,ITS_BOOLEAN isProxyEnabled);

    /********************************************************************/
    /** Purpose:
    *      API to set the default RealmEntry
    *
    *  Input Parameters:
    *      peerName, realmName
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/

    int SetDefaultRoute(const char* peerName, const char* realmName);

    /********************************************************************/
    /** Purpose:
    *       API to Removes the Realm entry
    *
    *  Input Parameters:
    *      realmName
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/

    int RemoveRealm(const char* realmName);


    /********************************************************************/
    /** Purpose:
    *       API to add Destination entry of type DESTINATION_INFO for Realm
    *
    *  Input Parameters:
    *      DESTINATION_INFO*
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/

    int AddDestination(DESTINATION_INFO* dest);

    /********************************************************************/
    /** Purpose:
    *       API to Modify Destination Priority 
    *
    *  Input Parameters:
    *      DESTINATION_INFO*
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/

    int ModifyDestinationPriority(DESTINATION_INFO* destInfo);

    /********************************************************************/
    /** Purpose:
    *       API to remove Destination entry of type DESTINATION_INFO for Realm
    *
    *  Input Parameters:
    *      DESTINATION_INFO*
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/

    int RemoveDestination(DESTINATION_INFO* destInfo);   
 
    /********************************************************************
    * Purpose:
    *       API to remove all Destinations of a Peer.
    *
    *  Input Parameters:
    *      DESTINATION_INFO*
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *********************************************************************/
 
    int RemoveAllDestination(DESTINATION_INFO* destInfo);    

    /********************************************************************/
    /** Purpose:
    *       API to add IP address for Peer under SCTP tranport
    *
    *  Input Parameters:
    *      peerName, ipAddr
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/

    int AddIp(const char* peerName, const char* ipAddr);


    /********************************************************************/
    /** Purpose:
    *       Get Peer Status 
    *
    *  Input Parameters:
    *      peerName, realmName
    *
    *  Input/Output Parameters:
    *      PEER_STATUS.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/

    int GetDiaPeerStatus(void *arg, PEER_INFO* pInfo);

    /********************************************************************/
    /** Purpose:
    *      API to set Proxy Info AVP Enabled in Realm Configuration. 
    *
    *  Input Parameters:
    *      None
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/

    int SetProxyInfoAVPEnabled(const char* realmName, ITS_BOOLEAN pinfoEnable);


    /*.implementation:public
     ****************************************************************************
     *  Purpose:
     *  API to display whether proxyInfoAvpEnabled is enabled or not.
     *
     *  Input Parameters:
     *      realmName
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      Integer
     *
     *  Notes:
     *
     *  See Also:
     *
     ****************************************************************************/
    int IsProxyInfoAvpEnabled(std::ostream& oss, const char *realmName);

    /*.implementation:public
     ****************************************************************************
     *  Purpose:
     *  API to Remove Default Route.
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
     *      Integer
     *
     *  Notes:
     *
     *  See Also:
     *
     ****************************************************************************/
    int RemoveDefaultRoute();

    /*.implementation:public
     ****************************************************************************
     *  Purpose:
     *  API to Get the Default Realm Route.
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
     *      Integer
     *
     *  Notes:
     *
     *  See Also:
     *
     ****************************************************************************/
    int GetDefaultRoute(DESTINATION_INFO *dstInfo);

    /*.implementation:public
     ****************************************************************************
     *  Purpose:
     *  APIs to enable, disable, &  whether statistics Enabled is enabled 
     *  or not.
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
     *      None,None,boolean. 
     *
     *  Notes:
     *
     *  See Also:
     *
     ****************************************************************************/

    ITS_UINT EnableStatistics();
    ITS_UINT DisableStatistics();   
    bool IsStatsEnabled();

    ITS_UINT EnableHexDump();
    ITS_UINT DisableHexDump();
    bool IsHexDumpEnabled();

    /* Print functions */      
    void GetDiaStackStats(std::ostream& oss, bool clrFlag=false);
    void GetDiaSessionStats(std::ostream& oss, bool clrFlag=false);
    void GetDiaPeerStats(std::ostream& oss, bool clrFlag=false);
    void GetDiaPeerStatus(std::ostream& oss, PEER_INFO* pInfo);
    void GetDiaIndicStats(std::ostream& oss, bool clrFlag=false);
    void GetDiaMiscStats(std::ostream& oss, bool clrFlag=false);
    ITS_UINT ResetStackStats();
    DIA_PEER_STATES* GetPeersState(unsigned int& nPeers);
    ITS_UINT ResetTotMsgStats();
    int ResetSessionErrorStats();
  
    /* Get Statistics */
    int GetDiaIndStats(void *indStats, bool clrFlag=false);
    int GetDiaSessStats(void *sessStats, bool clrFlag=false);
    int GetDiaPeerStats(void *peerStats, bool clrFlag=false);
    int GetDiaMiscStats(void *peerStats, bool clrFlag=false);
    int GetDiaTotMessageStats(); 

    /********************************************************************/
    /** Purpose:
    *       API to Shows Peer Table Information
    *
    *  Input Parameters:
    *      None
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/

    int PrintPeerTable(std::ostream& oss);

    
    /********************************************************************/
    /** Purpose:
    *       API to Shows Realm Table Information
    *
    *  Input Parameters:
    *      None
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    int PrintRealmTable(std::ostream& oss);

    int GetSessionTableSize();

    int GetSessionTableSize(int index);
    int GetSessionTableSize(DIA_ST_STATS* stStats);

    /* API for the redundancy to do SwitchOver.*/
    int SwitchOver();
    
    /* API to get the status of Node (Active/Backup).*/
    bool GetNodeState(ITS_USHORT &state);

    int PrintSessionTable(std::ostream& oss);

    void PrintPeerStats(std::ostream& oss, std::string peer, std::string realm);

   /********************************************************************/
   /** Purpose:
    *       API to Set Peer, AuthSession, AcctSession Timers  
    *       and LocalHost Information. 
    *
    *  Input Parameters:
    *      None
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/


    int SetAuthSessionTimers(ITS_SERIAL, ITS_SERIAL, ITS_SERIAL);
    int SetAcctSessionTimers(ITS_SERIAL, ITS_SERIAL); 
     
    int SetPeerTimers(ITS_SERIAL, ITS_SERIAL, ITS_SERIAL);
    int GetPeerTimers(ITS_SERIAL&, ITS_SERIAL&, ITS_SERIAL&);
    int SetPeerTimers(PEER_INFO *PeerData);
    int SetPeerIsDisconnectCauseSupported(PEER_INFO *PeerData);
    int SetPeerDPRCauseReconnectimers(PEER_INFO *PeerData);
    int GetPeerTimers(PEER_INFO& PeerData);
    int SetLocalHostInfo(const char* hostName, const char* realmName); 
    int GetLocalHostInfo(LOCAL_HOST_INFO *lHostInfo);
    int SetLocalTransportInfo(const char* serverIpAddr, int type, ITS_USHORT port); 
    int SetLocalTransportInfo(const char* serverIpAddr, int type, ITS_USHORT port,
                              const char** multiHomeIpps,int noIps,const char *publicServerIpAddr,
                              ITS_USHORT securePort); 

    // Add these functions
    int GetAuthSessionTimers(ITS_SERIAL&, ITS_SERIAL&, ITS_SERIAL&);
    int GetAcctSessionTimers(ITS_SERIAL&, ITS_SERIAL&);
    int GetLocalTransportInfo(MGMT_TR_TYPE transportType, int lport);
    int GetPeer(PEER_INFO *PeerData);
    int ModifyPeer(PEER_INFO *PeerData,ITS_BOOLEAN isTlsFlagModified);
    int GetAlternatePeer(ALT_PEER_INFO* aInfo);
    int SetRealmLocalAction(const char *realm, const char *laction);
    int ModifyRedirectUsage(const char *realm,  unsigned int rdUsage);
    int ModifyRedirectCacheTime(const char *realm,  unsigned int rdmaxCacheTime);
   
    /********************************************************************/
    /** Purpose:
    *       API to Set Overload threshold values MinT and MaxT.
    *
    *  Input Parameters:
    *     minT and maxT
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
 
    int SetOvloadThresholds(ITS_INT, ITS_INT);
    int GetOvloadThresholds(ITS_INT &maxT, ITS_INT &minT);

    /** APIs to Enable and Disable Health Monitor Interface 
    */ 
    int EnableHMI();
    int DisableHMI();  
    int IsHMIEnabled();  

    /*
     * Peer Discovery Related API
     */
    int PrintPeerDiscoveryTable(std::ostream& oss);
    int InsertIntoDiscoveryList(const char* realmName, const char* hostName);
    int RemoveFromDiscoveryList(const char* realmName, const char* hostName);
    int EnablePeerDiscovery();
    int DisablePeerDiscovery();
    bool IsPeerDiscoveryEnable();
    int SetPeerDiscoveryInterval(int val);
    int GetPeerDiscoveryInterval();

    /********************************************************************/
    /** Purpose:
    *       API to Commit xml for xml persistency
    *
    *  Input Parameters:
    *      filename
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    int  DIA_Commit(char * filename);

    static DiaMgmt* GetDiaMgmt();


    /********************************************************************/
    /** Purpose:
    *       API to Set HeartBeat Interval and Number of Retry.
    *
    *  Input Parameters:
    *     hbInterval and retry
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    int SetHBInterval(ITS_UINT hbInterval);
 
    int SetHBRetry(ITS_UINT retry);
 
    /********************************************************************/
    /** Purpose:
    *       API to Get HeartBeat Interval and Number of Retry.
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
    *      Integer
    *
    *  Notes:
    *      None
    *
    *  See Also:
    *      None
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    int GetHBInterval();
 
    int GetHBRetry();

    int GetHMICheckInterval();

    int SetHMICheckInterval(int val);

    int GetHMITimeout();

    int SetHMITimeout(int val);

    int GetHMIRetry();

    int SetHMIRetry(int val);

    int GetHMIHBInterval();

    int SetHMIHBInterval(int val);

    int SetDscpValue(const char* hostName, const char* realmName, ITS_INT val);
    int GetDscpValue(const char* hostName, const char* realmName);
    ITS_UINT EnableDscp(const char* hostName, const char* realmName);
    ITS_UINT DisableDscp(const char* hostName, const char* realmName);

    //API for setting the DTF Logging Configuration from CMAPI
    int SetDTFLoggingConfig(const unsigned int channel, const unsigned int level);
    int SetDTFLogChannel(const unsigned int channel);
    int SetDTFLogLevel(const unsigned int level);
    int AddStaticRoutingConfig(const char* destHost,const char* destRealm,const char*peer,
                               const char* realm,int appId,int priority);
    
    int ModifyStaticRoutingPriority(const char* destHost,const char*peer,int priority,int appId);
    
    int DeleteStaticRoutingEntry(const char* destHost,const char*peer,int appId);
    
    typedef std::unordered_map <unsigned int, std::string>AppIdToDictMap;
    
    const char * GetDictionaryName(unsigned int appId);

    void ModifyIsRetransmissionFlag(PEER_INFO *PeerData,ITS_BOOLEAN isRetransmissionEnabled);

private:

    /********************************************************************/
    /* Purpose:
    *      Class Constructor
    *      
    *  Input Parameters:
    *      None
    *    
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      None.
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
    DiaMgmt();
    DiaMgmt(const DiaMgmt&){};
    AppIdToDictMap m_appIdToDictMap;
};

#endif
