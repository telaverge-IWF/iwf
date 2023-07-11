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
 * ID: $Id: dm_msgs.h,v 1.17 2010/08/19 11:22:23 nvijikumar Exp $
 *
 * LOG: $Log: dm_msgs.h,v $
 * LOG: Revision 1.17  2010/08/19 11:22:23  nvijikumar
 * LOG: Porting changes from B-MOTO-IDIA-0421-00
 * LOG: 1. New Overload implimentation changes are not being ported.
 * LOG: 2. Force disconnect changes are not being ported
 * LOG:
 * LOG: Revision 1.16  2009/10/14 10:42:33  sureshj
 * LOG: forceDisconectPeer, getPeerTimers, GetLocalHostInfo mml commands
 * LOG: added. (motorola helpDesk issues 2219, 2238)
 * LOG:
 * LOG: Revision 1.15  2009/09/07 05:02:10  rajeshak
 * LOG: MML Support to set/get HMI Heartbeat interval.
 * LOG:
 * LOG: Revision 1.14  2009/07/24 09:42:15  rajeshak
 * LOG: Following Changes are include
 * LOG:  1. New MML API's added to get/remove default route,get/set overload limits
 * LOG:     Enable/Disable HMI
 * LOG:  2. Stats changes (to include option to clear stats in get)
 * LOG:
 * LOG: Revision 1.13  2009/07/14 10:10:12  rajeshak
 * LOG: Changes done to include peer realm name in destination
 * LOG: (addDestination, removeDestination, modifyPriority).
 * LOG:
 * LOG: Revision 1.12  2009/07/13 08:34:55  rajeshak
 * LOG: 1. Reverting back session table changes.
 * LOG: 2. MML API to set/get the HMI Retry.
 * LOG:
 * LOG: Revision 1.11  2009/06/29 14:58:19  rajeshak
 * LOG: 1. MML Commands added to set HMI Check Interval and Timeout.
 * LOG: 2. Changes for Queue stats and session table size.
 * LOG:
 * LOG: Revision 1.10  2009/05/11 06:28:48  rajeshak
 * LOG: 1. Get/Set Heartbeat Interval changes
 * LOG: 2. Connection Establishment time in Peer Status
 * LOG:
 * LOG: Revision 1.9  2009/04/17 12:13:27  rajeshak
 * LOG: Compilation Error.
 * LOG:
 * LOG: Revision 1.8  2009/04/13 13:46:28  rajeshak
 * LOG: MML Api added for Peer discovery and modify destination priority.
 * LOG:
 * LOG: Revision 1.7  2009/04/13 04:38:39  nvijikumar
 * LOG: Heartbeat Support
 * LOG:
 * LOG: Revision 1.6  2009/03/26 09:37:58  rajeshak
 * LOG: GetPeerStatus MML API Support
 * LOG:
 * LOG: Revision 1.5  2009/03/26 06:03:16  nvijikumar
 * LOG: GetPeerStatus API Support
 * LOG:
 * LOG: Revision 1.4  2009/03/26 05:31:38  nvijikumar
 * LOG: GetDiaMiscStats and ResetAllStats API Support
 * LOG:
 * LOG: Revision 1.3  2009/03/19 08:47:05  rajeshak
 * LOG: Changes for SetDefaultRoute API support.
 * LOG:
 * LOG: Revision 1.2  2009/03/18 12:56:12  rajeshak
 * LOG: Enhanced MML API support.
 * LOG:
 * LOG: Revision 1.1  2009/03/02 04:39:44  nvijikumar
 * LOG: Initial draft for MML API Support
 * LOG:
 * LOG:
 ****************************************************************************/
#ident "$Id: dm_msgs.h,v 1.17 2010/08/19 11:22:23 nvijikumar Exp $"

#ifndef _DM_MSGS_H
#define _DM_MSGS_H 

#include <its.h>
#include <its_types.h>

#define MAX_PARAM_LEN 128

#define DIA_DM_APP_SRC                (0x03U)

#define DT_DBG DIA_TRACE_DEBUG 
#define DT_ERR DIA_TRACE_ERROR 
#define DT_WRN DIA_TRACE_WARNING 
#define DT_CRT DIA_TRACE_CRITICAL 

#define DM_BIT_1       (1<<0)
#define DM_BIT_2       (1<<1)
#define DM_BIT_3       (1<<2)
#define DM_BIT_4       (1<<3)
#define DM_BIT_5       (1<<4)

#define DM_CMD_TO_TEXT(x)  \
    ((x==EN_STATS)          ? "EN_STATS"           : \
    ((x==DIS_STATS)         ? "DIS_STATS"          : \
    ((x==RESET_STATS)       ? "RESET_STATS"        : \
    ((x==GET_INDC_STATS)    ? "GET_INDC_STATS"     : \
    ((x==GET_SESS_STATS)    ? "GET_SESS_STATS"     : \
    ((x==GET_PEER_STATS)    ? "GET_PEER_STATS"     : \
    ((x==GET_PEER_STATUS)   ? "GET_PEER_STATUS"    : \
    ((x==START_ALL_PEERS)   ? "START_ALL_PEERS"    : \
    ((x==EN_TRACE)          ? "EN_TRACE"           : \
    ((x==DIS_TRACE)         ? "DIS_TRACE"          : \
    ((x==ADD_PEER)          ? "ADD_PEER"           : \
    ((x==ADD_ALTERNATE_PEER)? "ADD_ALTERNATE_PEER" : \
    ((x==START_PEER)        ? "START_PEER"         : \
    ((x==REMOVE_PEER)       ? "REMOVE_PEER"        : \
    ((x==DISCONNECT_PEER)   ? "DISCONNECT_PEER"    : \
    ((x==FORCE_DISCONNECT_PEER)?"FORCE_DISCONNECT_PEER" : \
    ((x==ADD_REALM)         ? "ADD_REALM"          : \
    ((x==REMOVE_REALM)      ? "REMOVE_REALM"       : \
    ((x==ADD_DESTINATION)   ? "ADD_DESTINATION"    : \
    ((x==REMOVE_DESTINATION)? "REMOVE_DESTINATION" : \
    ((x==MODIFY_DESTINATION)? "MODIFY_DESTINATION" : \
    ((x==EN_PROXY_INFO_AVP) ? "EN_PROXY_INFO_AVP"  : \
    ((x==DIS_PROXY_INFO_AVP)? "DIS_PROXY_INFO_AVP" : \
    ((x==DIA_COMMIT)        ? "DIA_COMMIT"         : \
    ((x==MODIFY_ALTERNATE_PEER  ? "MODIFY_ALTERNATE_PEER"  : \
    ((x==REMOVE_ALTERNATE_PEER) ? "REMOVE_ALTERNATE_PEER"  : \
    ((x==GET_SESSION_TBL_SIZE)  ? "GET_SESSION_TBL_SIZE"   : \
    ((x==GET_IDC_CONN_STATUS)   ? "GET_IDC_CONN_STATUS"    : \
    ((x==GET_DIA_TRACE_STATS)   ? "GET_DIA_TRACE_STATS"    : \
    ((x==GET_DIA_Q_STATS)       ? "GET_DIA_Q_STATS"        : \
    ((x==SET_PEER_TIMERS)       ? "SET_PEER_TIMERS"        : \
    ((x==GET_PEER_TIMERS)       ? "GET_PEER_TIMERS"        : \
    ((x==SET_SESSION_TIMERS)    ? "SET_SESSION_TIMERS"     : \
    ((x==DISCONNECT_ALL_PEER)   ? "DISCONNECT_ALL_PEER"    : \
    ((x==SET_LOCAL_HOST_INFO)   ? "SET_LOCAL_HOST_INFO"    : \
    ((x==GET_LOCAL_HOST_INFO)   ? "GET_LOCAL_HOST_INFO"    : \
    ((x==SET_DEFAULT_ROUTE)     ? "SET_DEFAULT_ROUTE"      : \
    ((x==EN_PEER_DISCOVERY)     ? "EN_PEER_DISCOVERY"      : \
    ((x==DIS_PEER_DISCOVERY)    ? "DIS_PEER_DISCOVERY"     : \
    ((x==ADD_TO_DISCOVERY_LIST) ? "ADD_TO_DISCOVERY_LIST"  : \
    ((x==DEL_FROM_DISCOVERY_LIST) ? "DEL_FROM_DISCOVERY_LIST"  : \
    ((x==GET_DISCOVERY_INTERVAL) ? "GET_DISCOVERY_INTERVAL": \
    ((x==SET_DISCOVERY_INTERVAL) ? "SET_DISCOVERY_INTERVAL": \
    ((x==GET_HEARTBEAT_INTERVAL) ? "GET_HEARTBEAT_INTERVAL": \
    ((x==SET_HEARTBEAT_INTERVAL) ? "SET_HEARTBEAT_INTERVAL": \
    ((x==GET_HEARTBEAT_RETRY)    ? "GET_HEARTBEAT_RETRY"   : \
    ((x==SET_HEARTBEAT_RETRY)    ? "SET_HEARTBEAT_RETRY"   : \
    ((x==GET_HMI_CHECK_INTERVAL) ? "GET_HMI_CHECK_INTERVAL": \
    ((x==SET_HMI_CHECK_INTERVAL) ? "SET_HMI_CHECK_INTERVAL": \
    ((x==GET_HMI_TIMEOUT)        ? "GET_HMI_TIMEOUT"       : \
    ((x==SET_HMI_TIMEOUT)        ? "SET_HMI_TIMEOUT"       : \
    ((x==GET_HMI_RETRY)          ? "GET_HMI_RETRY"         : \
    ((x==SET_HMI_RETRY)          ? "SET_HMI_RETRY"         : \
    ((x==GET_HMI_HB_INTERVAL)    ? "GET_HMI_HB_INTERVAL"   : \
    ((x==SET_HMI_HB_INTERVAL)    ? "SET_HMI_HB_INTERVAL"   : \
    ((x==ENABLE_HMI)             ? "ENABLE_HMI"            : \
    ((x==DISABLE_HMI)            ? "DISABLE_HMI"           : \
    ((x==HMI_STATUS)             ? "HMI_STATUS"            : \
    ((x==SET_OV_LIMIT)           ? "SET_OV_LIMIT"          : \
    ((x==GET_OV_LIMIT)           ? "GET_OV_LIMIT"          : \
    ((x==REMOVE_DEFAULT_ROUTE)   ? "REMOVE_DEFAULT_ROUTE"  : \
    ((x==GET_DEFAULT_ROUTE)      ? "GET_DEFAULT_ROUTE"     : \
    ((x==SET_ROUTE_SCHEME)       ? "SET_ROUTE_SCHEME"      : \
    ((x==GET_ROUTE_SCHEME)       ? "GET_ROUTE_SCHEME"      : \
    "INVALID")))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))
	
typedef enum
{
   /* Parameters with no parameters */
    EN_STATS = 1,
    DIS_STATS,
    RESET_STATS,
    GET_INDC_STATS,
    GET_PEER_STATS,
    GET_PEER_STATUS,
    GET_SESS_STATS,
    START_ALL_PEERS,
    GET_SESSION_TBL_SIZE,
    GET_IDC_CONN_STATUS,
    GET_DIA_TRACE_STATS,
    GET_DIA_Q_STATS,
   /* Parameters with parameters */
    EN_TRACE,
    DIS_TRACE,
    ADD_PEER,
    ADD_ALTERNATE_PEER,
    REMOVE_ALTERNATE_PEER,
    MODIFY_ALTERNATE_PEER,
    START_PEER,
    REMOVE_PEER,
    DISCONNECT_PEER,
    FORCE_DISCONNECT_PEER,
    DISCONNECT_ALL_PEER,
    ADD_REALM,
    REMOVE_REALM,
    ADD_DESTINATION,
    REMOVE_DESTINATION,
    MODIFY_DESTINATION,
    EN_PROXY_INFO_AVP,
    DIS_PROXY_INFO_AVP,
    SET_PEER_TIMERS,
    GET_PEER_TIMERS,
    SET_SESSION_TIMERS,
    DIA_COMMIT,
    SET_LOCAL_HOST_INFO,
    GET_LOCAL_HOST_INFO,
    SET_DEFAULT_ROUTE,
    GET_MISC_STATS,
    EN_PEER_DISCOVERY,
    DIS_PEER_DISCOVERY,
    ADD_TO_DISCOVERY_LIST,
    DEL_FROM_DISCOVERY_LIST,
    GET_DISCOVERY_INTERVAL,
    SET_DISCOVERY_INTERVAL,
    GET_HEARTBEAT_INTERVAL,
    SET_HEARTBEAT_INTERVAL,
    GET_HEARTBEAT_RETRY,
    SET_HEARTBEAT_RETRY,
    GET_HMI_CHECK_INTERVAL,
    SET_HMI_CHECK_INTERVAL,
    GET_HMI_TIMEOUT,
    SET_HMI_TIMEOUT,
    GET_HMI_RETRY,
    SET_HMI_RETRY,
    GET_HMI_HB_INTERVAL,
    SET_HMI_HB_INTERVAL,
    ENABLE_HMI,
    DISABLE_HMI,    
    HMI_STATUS,
    SET_OV_LIMIT,
    GET_OV_LIMIT,
    REMOVE_DEFAULT_ROUTE,
    GET_DEFAULT_ROUTE,
    SET_ROUTE_SCHEME,
    GET_ROUTE_SCHEME
}DM_CMD;

/* This structure should be identical to DIA_MSG_STATS as defined 
 * in the dia_stack_stats.h */
typedef struct _dmCmdStats
{
     ITS_UINT reqIn;
     ITS_UINT reqOut;
     ITS_UINT ansIn;
     ITS_UINT ansOut;
}DM_MSG_STATS;

/* This structure should be identical to DIA_PEER_STATS as defined 
 * in the dia_stack_stats.h */
typedef struct _dmPeerStats
{
     DM_MSG_STATS total;
     DM_MSG_STATS ce;
     DM_MSG_STATS dw;
     DM_MSG_STATS dp;
}DM_PEER_STATS;

/* This structure should be identical to DIA_SESS_STATS as defined 
 * in the dia_stack_stats.h */
typedef struct _dmSessStats
{
     DM_MSG_STATS app;
     DM_MSG_STATS ac;
     DM_MSG_STATS as;
     DM_MSG_STATS ra;
     DM_MSG_STATS st;
     DM_MSG_STATS err;
     ITS_UINT     decodeFailure;
}DM_SESS_STATS;

/* This structure should be identical to DIA_INDIC_STATS as defined 
 * in the dia_stack_stats.h */
typedef struct _dmIndStats
{
    ITS_UINT numDisconnInd;
    ITS_UINT numSessTimeoutInd;
    ITS_UINT numAuthLifeTimeoutInd;
    ITS_UINT numAuthGraceTimeoutInd;
    ITS_UINT numAbortInd;
    ITS_UINT numCorruptMsgInd;
    ITS_UINT numUnknownInd;
    ITS_UINT numFailOverInd;
    ITS_UINT numFailBackInd;
}DM_INDIC_STATS;

typedef struct _dmMiscStats
{
    ITS_UINT redirectEvents;
    ITS_UINT totalRetrans;
    ITS_UINT hhDropMsgs;
    ITS_UINT unknownTypes;
    ITS_UINT protocolErrs;
    ITS_UINT transientErrs;
    ITS_UINT permanentErrs;
}DM_MISC_STATS;

typedef struct _diaPeerTimers
{
    ITS_SERIAL retry;
    ITS_SERIAL expiry;
    ITS_SERIAL wd;
} DM_PEER_TIMER;

typedef struct _diaSessTimers
{
    ITS_SERIAL sessTimeout;
    ITS_SERIAL lifeTimeout;
    ITS_SERIAL graceTimeout;
}DM_SESS_TIMER;

typedef struct _diaQueueStats
{
    ITS_UINT upQCount;
    ITS_UINT downQCount;
}DM_QUEUE_STATS;

typedef enum
{
    DM_DT_OCTET = 1,
    DM_DT_SHORT,
    DM_DT_INT,
    DM_DT_STR
}DM_DATA_TYPE;

typedef enum
{
    MSG_TYPE_REQ = 1,
    MSG_TYPE_RES = 2,
    MSG_TYPE_HB  = 6 /* Same as IDS */
}
DM_MSG_TYPE;

typedef struct _dm__trace
{
    ITS_BOOLEAN all;
    ITS_BOOLEAN dbg;
    ITS_BOOLEAN wrn;
    ITS_BOOLEAN err;
    ITS_BOOLEAN crt;
}
DM_TRACE;

typedef enum
{
    RC_SUCCESS = 0,
    RC_EPARAM,
    RC_FAILURE,
    RC_INVALID_CMD
}
DM_RCODE;

typedef enum
{
    DM_DIA_TR_TCP = 0,
    DM_DIA_TR_SCTP
}
DM_DIA_TR_TYPE;

/** Structure:
 *      DM_PEER_ENTRY
 *       
 *  Purpose:
 *      DM_PEER_ENTRY structure is used to represent an Peer Configuration 
 *      
 **/
typedef struct _mgmt_peer_entry
{
    ITS_OCTET        peerName[MAX_PARAM_LEN];
    ITS_OCTET        realmName[MAX_PARAM_LEN];
    DM_DIA_TR_TYPE   trType;
    ITS_OCTET        ipAddr[MAX_PARAM_LEN];
    unsigned short   port;
}
DM_PEER_ENTRY;

/** Structure:
 *      DM_HOST_INFO
 *
 *  Purpose:
 *      DM_HOST_INFO structure is used to represent an Peer Configuration
 *
 **/
typedef struct _mgmt_host_info
{
    ITS_OCTET        hostName[MAX_PARAM_LEN];
    ITS_OCTET        realmName[MAX_PARAM_LEN];
    ITS_OCTET        ipAddr[MAX_PARAM_LEN];
}
DM_HOST_INFO;


/** Structure:
 *      DM_ALT_PEER_INFO
 *
 *  Purpose:
 *      DM_ALT_PEER_INFO structure is used to represent an Alternate Peer 
 *      Configuration
 *
 **/
typedef struct _alternate_peer_entry
{
    ITS_OCTET        peerName[MAX_PARAM_LEN];
    ITS_OCTET        realmName[MAX_PARAM_LEN];
    ITS_OCTET        altHost[MAX_PARAM_LEN];
    ITS_OCTET        altRealmName[MAX_PARAM_LEN];
    bool             isFailoverEnable;
    bool             isFailbackEnable;
    bool             isRedundantMate;
}
DM_ALT_PEER_INFO;

/** Structure:
 *      DM_DEST_INFO
 *
 *  Purpose:
 *      DM_DEST_INFO structure is used to represent an Peer Configuration 
 *      
 **/
typedef struct _dest_entry
{   
    ITS_OCTET        realmName[MAX_PARAM_LEN];
    ITS_OCTET        peerName[MAX_PARAM_LEN];
    ITS_OCTET        peerRealm[MAX_PARAM_LEN];
    unsigned int     appId;
    unsigned int     vendId;
    unsigned int     priority;
}
DM_DEST_INFO;

typedef struct _peer_info
{
    ITS_OCTET         peerName[MAX_PARAM_LEN];
    ITS_OCTET         realmName[MAX_PARAM_LEN];
}
DM_PEER_INFO;

typedef struct _peer_disc
{
    DM_PEER_INFO peer;
    ITS_UINT     discCause;
    ITS_UINT     expiry;
}
DM_PEER_DISC;

typedef struct _mgmt_realm_entry
{
    ITS_OCTET        realmName[MAX_PARAM_LEN];
    ITS_OCTET        localAction[MAX_PARAM_LEN];
    ITS_BOOLEAN      isProxyEnabled;
}
DM_REALM_ENTRY;

typedef struct _realm_info
{
    ITS_OCTET        realmName[MAX_PARAM_LEN];
}
DM_REALM_INFO;

typedef struct _xml_commit
{
    ITS_OCTET        fileName[MAX_PARAM_LEN];
}
DM_XML_COMMIT;

typedef struct _dm_stats
{
    ITS_UINT stats;
}DM_STATS;

/*
 * This stores the IDC connection status info
 * 
 */
typedef struct
{
    ITS_UINT appIdentifier;
    ITS_UINT appIdType;
}
DM_IDC_CONN_INFO;

typedef enum
{
    DM_PEER_CLOSED,
    DM_PEER_WAIT_CONN_ACK,
    DM_PEER_WAIT_I_CEA,
    DM_PEER_WAIT_CONN_ACK_ELECT,
    DM_PEER_WAIT_RETURNS,
    DM_PEER_I_OPEN,
    DM_PEER_R_OPEN,
    DM_PEER_CLOSING,
    DM_PEER_MAX
}DM_PEER_STATE;

typedef enum
{
    DM_ROUTE_ROUND_ROBIN,
    DM_ROUTE_BROADCAST
}DM_ROUTE_SCHEME;

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
    ITS_OCTET       peerName[MAX_PARAM_LEN];
    ITS_OCTET       realmName[MAX_PARAM_LEN];
    DM_DIA_TR_TYPE  type;
    ITS_OCTET       ipAddr[MAX_PARAM_LEN];
    ITS_USHORT      port;
    DM_PEER_STATE   pState;
    ITS_UINT        isStatic;
    time_t          connEstTime;
}
DM_PEER_STATUS;

typedef struct 
{
     ITS_UINT minTh;
     ITS_UINT maxTh;
}DM_OVERLOAD_TH;


typedef struct _mgmt_msg_req
{
    DM_CMD     cmd;
    ITS_USHORT trId;
    union
    {
        ITS_UINT         discAllPeers;
        ITS_UINT         clientId;
        DM_TRACE         eTrace;
        DM_TRACE         dTrace;
        DM_PEER_ENTRY    addPeer;
        DM_ALT_PEER_INFO addAltPeer;
        DM_ALT_PEER_INFO modiAltPeer;
        DM_PEER_INFO     rmPeer;
        DM_PEER_INFO     strPeer;
        DM_PEER_DISC     peerDisc;
        DM_REALM_ENTRY   addRealm;
        DM_REALM_INFO    rmRealm;
        DM_DEST_INFO     addDest;
        DM_DEST_INFO     rmDest;
        DM_DEST_INFO     modDest;
        DM_REALM_INFO    enProxyInfo;
        DM_REALM_INFO    disProxyInfo;
        DM_XML_COMMIT    xmlCommit;
        DM_PEER_INFO     rmAltPeer;
        DM_SESS_TIMER    sessTimer;
        DM_PEER_TIMER    peerTimer;
        DM_HOST_INFO     hostInfo;
        DM_PEER_INFO     defRoute;
        DM_PEER_INFO     peerStatus;
        DM_PEER_INFO     addDiscList;
        DM_PEER_INFO     delDiscList;
        ITS_UINT         discInterval;
        ITS_UINT         hbInterval;
        ITS_UINT         hbRetry;
        ITS_UINT         hmiInterval;
        ITS_UINT         hmiTimeout;
        ITS_UINT         hmiRetry;
        ITS_UINT         hmiHBInterval;
        DM_OVERLOAD_TH   ovLimits;
        ITS_UINT         statsClearOpt;
        DM_ROUTE_SCHEME  routeScheme;
    }param;
}DM_MSG_REQ;

typedef struct _mgmt_msg_res
{
    DM_CMD     cmd;
    ITS_USHORT trId;
    DM_RCODE   rCode;
    union
    {
        DM_TRACE          diaTrace;
        DM_STATS          stats; 
        DM_STATS          sessTableSize; 
        DM_QUEUE_STATS    qStats;
        DM_INDIC_STATS    indicStats;
        DM_MISC_STATS     miscStats;
        DM_SESS_STATS     sessStats;
        DM_PEER_STATS     peerStats;
        DM_PEER_TIMER     peerTimer;
        DM_HOST_INFO      hostInfo;
        DM_IDC_CONN_INFO  idcConnInfo;
        DM_PEER_STATUS    peerStatus;
        ITS_UINT          discInterval;
        ITS_UINT          hbInterval;
        ITS_UINT          hbRetry;
        ITS_UINT          hmiInterval;
        ITS_UINT          hmiTimeout;
        ITS_UINT          hmiRetry;
        ITS_UINT          hmiHBInterval;
        ITS_BOOLEAN       hmiStatus;
        DM_OVERLOAD_TH    ovLimits;
        DM_PEER_INFO      defRoute;
        DM_ROUTE_SCHEME   routeScheme;
    }param;
}DM_MSG_RES;

typedef struct _mgmt_msg
{
    DM_MSG_TYPE mType;
    union
    {
        DM_MSG_REQ req;
        DM_MSG_RES res;
    }u;
}DM_MSG;

class DmCodecUtils
{
public:
    DmCodecUtils(){};
    ~DmCodecUtils(){};
    static ITS_USHORT DataToShort(unsigned char *d)
    {
        ITS_USHORT x = 0;
        
        for (int i = 0; i < 2; i++)
        {
           x <<= 8;
           if (i == 0)
           {
              x |= (signed char)d[i];
           }
           else
           {
              x |= d[i];
           }
         }
         return x;
    }

    static ITS_UINT DataToInt(unsigned char *d)
    {
        ITS_UINT x = 0;

        for (int i = 0; i < 4; i++)
        {
           x <<= 8;
           if (i == 0)
           {
              x |= (signed char)d[i];
           }
           else
           {
              x |= d[i];
           }
         }
         return x;
    }

    static void ShortToData(ITS_OCTET *d, ITS_USHORT val)
    {
        int c = 2;
        for(int i=0; i< c; ++i)
        {
           d[i] = (val >> ((c-i-1)<<3)) & 0xFFU;
        }
    }

    static void IntToData(ITS_OCTET *d, ITS_UINT val)
    {
        int c = 4;
        for(int i=0; i< c; ++i)
        {
           d[i] = (val >> ((c-i-1)<<3)) & 0xFFU;
        }
    }

    static int EncodeString(std::string& str, ITS_OCTET* val)
    {
        ITS_OCTET lenData[sizeof(ITS_USHORT)];
        ITS_OCTET dType;
        const char*data = (const char*)val;
        dType = (char)DM_DT_STR;
        str.append((const char*)&dType, sizeof(ITS_OCTET));
        ShortToData(lenData, strlen(data));
        str.append((const char*)lenData, sizeof(ITS_USHORT));
        str.append(data);
        return ITS_SUCCESS;
    }

    static int DecodeString(ITS_OCTET* inStr, ITS_OCTET* outStr)
    {
        ITS_USHORT len = 0;
        int indx = 0;
        if (inStr[indx++] != DM_DT_STR)
        {
           return -1;
        }
        len = DataToShort(&inStr[indx]);
        if (len >= MAX_PARAM_LEN)
        {
           return -1;
        }
        indx += sizeof(ITS_USHORT);
        memcpy(outStr, &inStr[indx],len);
        indx += len;
        return indx;
    }

    static int EncodeInt(std::string& str, ITS_UINT val)
    {
        ITS_OCTET data[sizeof(ITS_UINT)];
        ITS_OCTET dType;
        dType = (char)DM_DT_INT;
        str.append((const char*)&dType, sizeof(ITS_OCTET));
        IntToData(data, val);
        str.append((const char*)data, sizeof(ITS_UINT));
        return ITS_SUCCESS;
    }

    static int DecodeInt(ITS_OCTET *inStr, ITS_UINT &val)
    {
        int indx = 0;
        if (inStr[indx++] != DM_DT_INT)
        {
           return -1;
        }
        val = DataToInt(&inStr[indx]);
        indx += sizeof(ITS_UINT);
        return indx;
    }

    static int EncodeShort(std::string& str, ITS_USHORT val)
    {
        ITS_OCTET data[sizeof(ITS_USHORT)];
        ITS_OCTET dType;
        dType = (char)DM_DT_SHORT;
        str.append((const char*)&dType, sizeof(ITS_OCTET));
        ShortToData(data, val);
        str.append((const char*)data, sizeof(ITS_USHORT));
        return ITS_SUCCESS;
    }

    static int DecodeShort(ITS_OCTET *inStr, ITS_USHORT &val)
    {
        int indx = 0;
        if (inStr[indx++] != DM_DT_SHORT)
        {
           return -1;
        }
        val = DataToShort(&inStr[indx]);
        indx += sizeof(ITS_USHORT);
        return indx;
    }

    static int EncodeOctet(std::string& str, ITS_OCTET val)
    {
        ITS_OCTET dType;
        dType = (char)DM_DT_OCTET;
        str.append((const char*)&dType, sizeof(ITS_OCTET));
        str.append((const char*)&val, sizeof(ITS_OCTET));
        return ITS_SUCCESS;
    }

    static int DecodeOctet(ITS_OCTET *inStr, ITS_OCTET &val)
    {
        int indx = 0;
        if (inStr[indx++] != DM_DT_OCTET)
        {
           return -1;
        }
        val = inStr[indx];
        indx += sizeof(ITS_OCTET);
        return indx;
    }
};

#endif

