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
 * ID: $Id: ids_common.h,v 3.11.46.1 2013/04/01 05:19:09 vsarath Exp $
 *
 * LOG: $Log: ids_common.h,v $
 * LOG: Revision 3.11.46.1  2013/04/01 05:19:09  vsarath
 * LOG: Fix for Coverity warnings
 * LOG:
 * LOG: Revision 3.11  2010/09/22 05:23:49  nvijikumar
 * LOG: GlobalUniqueAddr based routing/distribution support
 * LOG:
 * LOG: Revision 3.10  2009/08/28 12:28:45  rajeshak
 * LOG: Fix for Issue 2330 (IDS sends Heartbeat to IDC after double the time
 * LOG: configured in XML)
 * LOG: Changed the Previous heartbeat Implementation
 * LOG:
 * LOG: Revision 3.9  2009/08/25 10:16:32  rajeshak
 * LOG: Fix for Issue:2322 (IDS unable to send Heartbeat Message to DMC client)
 * LOG: Passing TrHandle properly.
 * LOG:
 * LOG: Revision 3.8  2009/03/18 13:08:43  rajeshak
 * LOG: Added new Callback for getting IDC connection info.
 * LOG:
 * LOG: Revision 3.7  2009/02/19 05:33:40  nvijikumar
 * LOG: Introduced sock write mutex as these functions are being called from
 * LOG: multiple threads
 * LOG:
 * LOG: Revision 3.6  2009/01/04 06:35:24  nvijikumar
 * LOG: Platform transport replaced with new TCP transport to handle IDC traffic
 * LOG:
 * LOG: Revision 3.5  2008/11/06 07:49:09  nvijikumar
 * LOG: IDS Connection Status Information (Establishment time)
 * LOG:
 * LOG: Revision 3.4  2008/11/06 06:57:06  nvijikumar
 * LOG: IssueID: none
 * LOG: FeatureID: 3.1.1 release feature
 * LOG: Description: UDP Transport support between IDS and IDC
 * LOG:
 * LOG: Revision 3.3  2008/10/31 05:32:03  nvijikumar
 * LOG: IssueID:1189
 * LOG: FeatureID: none
 * LOG: Description: 1. Introducing additional TQs and Threads for better
 * LOG:                 Performance on PP50 and initial stack tunning
 * LOG:              2. Unwanted code cleanup
 * LOG:
 * LOG: Revision 3.2  2008/09/08 11:36:33  ssaxena
 * LOG: Added new Type-To-Text to print the Active/BackUp Connection
 * LOG: of the Nodei (Hemant).
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:04  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.8  2008/03/27 11:21:05  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.6.8.1  2007/04/04 06:09:28  nvijikumar
 * LOG: Get AppIdType from IDC.
 * LOG:
 * LOG: Revision 2.6  2006/11/17 05:55:29  kamakshilk
 * LOG: Release session definitions added
 * LOG:
 * LOG: Revision 2.5  2006/11/14 06:54:01  kamakshilk
 * LOG: Added DIASERVER_NOTIFY_MSG type. GenericSessionInfo removed
 * LOG:
 * LOG: Revision 2.4  2006/11/08 06:13:38  kamakshilk
 * LOG: Changes for 64-bit support. ITS_ULONG changed to ITS_UINT
 * LOG:
 * LOG: Revision 2.3  2006/10/31 10:03:34  kamakshilk
 * LOG: IDSCL_Print function added
 * LOG:
 * LOG: Revision 2.2  2006/10/16 14:16:31  kamakshilk
 * LOG: Changes to work with ITS-Diameter
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:39  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.10  2006/08/08 04:42:52  kamakshilk
 * LOG: Fix for Bug Ids 4111, 4112 and 4118
 * LOG:
 * LOG: Revision 1.9  2006/06/29 08:13:05  kamakshilk
 * LOG: Flag added to Identify the Session initiated by Peer
 * LOG:
 * LOG: Revision 1.8  2006/06/19 08:08:46  tpanda
 * LOG: STR/ASR sending on inactive session index:Issue 3925
 * LOG:
 * LOG: Revision 1.7  2006/06/14 09:23:33  kamakshilk
 * LOG: Enhancements for sending Application Id to the client.
 * LOG:
 * LOG: Revision 1.6  2006/05/23 06:18:59  adutta
 * LOG: Clearing session record on STA/Abort
 * LOG:
 * LOG: Revision 1.5  2006/05/19 12:18:29  adutta
 * LOG: Fixed issue# 3799
 * LOG:
 * LOG: Revision 1.4  2006/04/06 07:49:31  adutta
 * LOG: Added session struct.
 * LOG:
 * LOG: Revision 1.3  2006/03/13 05:18:48  adutta
 * LOG: Modified the AppId position
 * LOG:
 * LOG: Revision 1.2  2006/03/06 13:17:26  adutta
 * LOG: Define APP_SRC
 * LOG:
 * LOG: Revision 1.1  2006/03/02 12:48:31  adutta
 * LOG: First cut
 * LOG:
 ****************************************************************************/
#ident "$Id: ids_common.h,v 3.11.46.1 2013/04/01 05:19:09 vsarath Exp $"

#ifndef IDS_CMN_H
#define IDS_CMN_H 

#include <its.h>
#include <its_types.h>

#include <ids_errors.h>

#if defined(WIN32)
 #if defined(IDSCL_IMPLEMENTATION)
    #define IDSAPP_DLLAPI __declspec(dllexport)
 #else
    #define IDSAPP_DLLAPI __declspec(dllimport)
 #endif
#else
  #define IDSAPP_DLLAPI
#endif

#define DT_ERR DIA_TRACE_ERROR
#define DT_DBG DIA_TRACE_DEBUG
#define DT_WRN DIA_TRACE_WARNING
#define DT_CRT DIA_TRACE_CRITICAL

#define IDS_TCP_SEND_MSG_QUEUE_NAME "TCP Send Msg Queue"

/* Q & Thread defines */
#define IDS_NUM_OF_THREADS          4 
#define IDS_WORKITEM_QUEUE          20000
#define IDS_MSG_QUEUE               ITS_MAB_SRC
#define IDS_APP_TO_STACK_MSG_QUEUE  (0xFFE1U)
#define IDS_TCP_SEND_MSG_QUEUE      (0xFFE3U)
/* Event Source */
#define IDS_APPDATA_SRC             (0x01U)  

/* IP address length */
#define IDS_IP_ADDR_LEN             15

/* HeartBeat defines */
#define MAX_HB_TRIES                3 
#define MAX_HB_PERIOD               10

/* Max Buffer Size */
#define IDS_MAX_BUF_SIZE            255 

#define IDS_DIA_APPID_POS           8
#define IDS_DIA_SES_AVP_POS         23 
#define IDS_DIA_MSG_POS             9 
#define IDS_MSG_TYPE_POS            4
#define IDS_DIA_HDR_SIZE            20

#define IDS_MIN_MSG_SIZE            5 

#define IDS_DIA_MSG_TYPE_NEW_REQ   (0x0FU)
#define IDS_DIA_MSG_TYPE_SES_RLS   (0x0EU)

#define IDS_GET_APPID(data,index,id)                  \
     id |= data[IDS_DIA_APPID_POS + index + 3];       \
     id |= data[IDS_DIA_APPID_POS + index + 2] << 8;  \
     id |= data[IDS_DIA_APPID_POS + index + 1] << 16; \
     id |= data[IDS_DIA_APPID_POS + index] << 24;


//input to IDS_CMD_CODE : ptr to diameter payload, returns code
#define IDS_GET_CMD_CODE(data, index, code)                  \
     code = 0;                                        \
     code |= data[IDS_DIA_APPID_POS + index -1];       \
     code |= data[IDS_DIA_APPID_POS + index -2] << 8;  \
     code |= data[IDS_DIA_APPID_POS + index -3] << 16; 
     

typedef enum
{
    IDS_ROUND_ROBIN = 1,
    IDS_BROADCAST   = 2,
    IDS_GLOBAL_UNIQ_ADDR = 3
}
IDS_ROUTING_SCHEME;

typedef enum
{
    IDS_PRIMARY_CONNECTION = 1,
    IDS_BACKUP_CONNECTION
}
IDS_CONNECTION_TYPE;

/**
 * Added new Type to text to print the 
 * Active or BackUp Connection of the Node.
 */
#define IDS_CONNECTION_TYPE_TO_TEXT(x) \
    ((x==IDS_PRIMARY_CONNECTION)         ? "ACTIVE_CONNECTION"      : \
    ((x==IDS_BACKUP_CONNECTION)          ? "BACKUP_CONNECTION"      : \
      "INVALID"))

#define IDS_GUA_LIST_SIZE          32

typedef struct _sockinfo_
{
    ITS_HANDLE handle;
    ITS_USHORT tries;
}
IDS_SOCK_INFO;

typedef struct _server_status_
{
    ITS_UINT port;
    ITS_CHAR ipAddr[IDS_IP_ADDR_LEN];
    IDS_CONNECTION_TYPE conType;
}
IDS_STATUS;

/* Registration status */
typedef enum
{   
    SUCCESS,
    FAILURE,
}
IDS_REG_STATUS;

typedef enum
{
     IDS_APP_IDENTIFIER
}
IDS_ROUTING_CRITERIA;

typedef struct _route_data_
{
    ITS_UINT appIdentifier;
}
IDS_ROUTE_DATA;


/*******************************************************************************
 * This structure will be filled when we want to send the registration event.
 *******************************************************************************/ 

typedef struct _aim_register 
{
     IDS_ROUTING_CRITERIA routing_criteria;
     ITS_UINT appIdentifier;
     IDS_CONNECTION_TYPE connectionType;
     ITS_UINT appIdType;
}
IDS_REGISTER;

/********************************************************************************
 * This structure is filled when we get the RGISTER ACK from the server    
 ********************************************************************************/
typedef struct _aim_register_ack 
{
    IDS_ROUTING_CRITERIA     routing_criteria;
    IDS_REG_STATUS result; /* If result is not success then look at errorcode */
    ITS_CHAR errorCode;
    ITS_CHAR isDccaEnbl;
    ITS_CHAR ipAddr[16];
    ITS_INT port;
    IDS_CONNECTION_TYPE conType;
}
IDS_REGISTER_ACK;

/*******************************************************************************
 * This structure is filled when we get the DERGISTER ACK from the server     
 *******************************************************************************/
typedef struct _aim_dergister_ack
{
    ITS_OCTET  result;
    ITS_CHAR errorCode;
    IDS_ROUTING_CRITERIA routing_criteria;
}
IDS_DEREGISTER_ACK;

typedef struct _aim_deregister
{
    IDS_ROUTING_CRITERIA  routing_criteria;
} 
IDS_DEREGISTER;    

typedef struct _ids_diameter_
{
    ITS_USHORT len;
    ITS_OCTET* data;
    ITS_OCTET  msgType;
    ITS_UINT   sessIdx;
    ITS_UINT   appId;
}
IDS_DIAMETER;

/* Indications to distributed applications */
typedef enum
{
     IDS_MSG_ENCODE_FAIL_IND = 1,
     IDS_SENDTO_STACK_FAIL_IND,
     IDS_RELEASE_SESS_FAIL_IND,
     IDS_RELEASE_SESS_SUCCESS_IND
}
IDS_APP_IND_TYPE;

typedef struct _ids_dia_app_notify_
{
    ITS_UINT length;
    IDS_APP_IND_TYPE indType;
    ITS_UINT sessionIndex;
    ITS_UINT appId;
    ITS_OCTET* data;
}
IDS_DIASRV_NOTIFY;


/***************************************************************************
 * This is a main structure used by the client layer. When a event is 
 * recived it will be decoded and put in to this structure only the 
 * required fields. The opposite process will be done when sending the
 * event out. We only stuff the required fileds out of many from the 
 * structure and form the event. For example if we are sending a 
 * register event, we only need to have the clientID, msg_type & 
 * REGISTER structure. So prepare the event with these contents 
 * and send to the server layer. 
 ***************************************************************************/ 

/* Message defines */


typedef enum
{
    REGISTER_MSG,
    DEREGISTER_MSG,
    REGISTER_ACK_MSG,
    DERGISTER_ACK_MSG,
    SERVER_STATUS_MSG,
    DIAMETER_MSG,
    HEARTBEAT_MSG,
    DIASERVER_NOTIFY_MSG,
    GLOBAL_UNIQ_ADDR_MSG,
    GLOBAL_UNIQ_ADDR_ACK_MSG
}
IDS_MESSAGE_TYPE;

typedef enum
{
   IDS_GUA_ADD,
   IDS_GUA_DEL
}IDS_GUA_ACTION;

typedef struct _aim_gua_info
{
    IDS_GUA_ACTION action;
    ITS_UINT count;
    ITS_CHAR ipAddr[IDS_IP_ADDR_LEN]; 
}IDS_GUA_INFO;

typedef struct _aim_gua_ack
{
    IDS_GUA_ACTION action;
    IDS_REG_STATUS result; 
}IDS_GUA_INFO_ACK;

typedef struct _guaEntry_
{
    ITS_UINT appId;
    ITS_UINT startIp;
    ITS_UINT endIp;
}IDS_GUA_ENTRY;

typedef struct _aim_message
{
     ITS_UINT                 clientID;
     IDS_MESSAGE_TYPE         msg_type;
     union
     {
         IDS_REGISTER          regInfo;
         IDS_DEREGISTER        deregInfo;
         IDS_REGISTER_ACK      regAck;
         IDS_DEREGISTER_ACK    deregAck;
         IDS_STATUS            servInfo;
         IDS_DIAMETER          diaInfo;
         IDS_DIASRV_NOTIFY     notifyInfo;
         IDS_GUA_INFO          guaInfo;
         IDS_GUA_INFO_ACK      guaAck;
      }
      u;
}
IDS_MESSAGE;

typedef struct _clientRInfo_
{
    ITS_UINT     clientID;
    IDS_REGISTER regInfo;
    IDS_GUA_ENTRY *guaList[IDS_GUA_LIST_SIZE];
    ITS_CHAR      guaEntryCount;
}
ClientRoutingInfo;

typedef struct _ClientList_
{
    ITS_UINT* clientID;
    ITS_UINT count;
}
ClientList;

typedef enum
{   IDS_TCP=0,
    IDS_UDP
}
IDS_TRANS_TYPE;

typedef struct _dest_info_ 
{
    ITS_UINT port;
    ITS_CHAR ipAddr[IDS_IP_ADDR_LEN]; 
}
IDS_DEST_INFO;

typedef struct TransportInfo
{
        IDS_TRANS_TYPE type;
        time_t         estbTime;
        ITS_MUTEX      wMutex;
        union
        {
          ITS_UINT tcpInfo;
          IDS_DEST_INFO  udpInfo;
        }u;

}
IDS_TRANS_INFO;

typedef struct
{
    ITS_UINT appIdentifier;
    ITS_UINT appIdType;
} 
IDC_CONN_STATUS_INFO;


typedef struct _udp_bhInfo
{
    ITS_UINT clientId;
    ITS_UINT tries;
    //ITS_UINT lastUpdated;
    ITS_UINT count;
}UDP_HB_INFO;


#define TCP_SOCK_RST_LASTUPDT(x) \
{                                \
(((TCP_SOCK_INFO *)(x))->count = 0); \
(((TCP_SOCK_INFO *)(x))->tries = 0); \
}

#define TCP_SOCK_INCR_COUNTER(x) \
(((TCP_SOCK_INFO *)(x))->count++)

#define TCP_SOCK_RST_COUNTER(x)  \
(((TCP_SOCK_INFO *)(x))->count = 0)

#define TCP_SOCK_COUNTER(x)      \
(((TCP_SOCK_INFO *)(x))->count)

#define TCP_SOCK_RST_TRIES(x)    \
(((TCP_SOCK_INFO *)(x))->tries = 0)

#define TCP_SOCK_INCR_TRIES(x)   \
(((TCP_SOCK_INFO *)(x))->tries++)

#define TCP_SOCK_TRIES(x)        \
(((TCP_SOCK_INFO *)(x))->tries)

typedef struct _tcp_sock
{
    ITS_INT     socket;
    ITS_UINT    count;
    ITS_UINT    tries;
    ITS_USHORT  trId;
}TCP_SOCK_INFO;

extern "C"
{
/* Populates the struct from event data*/ 
MULAPP_DLLAPI int
IDSCL_Decode(IDS_MESSAGE *msg, ITS_EVENT *event);

/* Populates the event data from struct*/ 
MULAPP_DLLAPI int
IDSCL_Encode(IDS_MESSAGE *msg, ITS_EVENT *event);

/* Reads the byte buffer(network byte order) and returns the integer value */
IDSAPP_DLLAPI ITS_UINT
IDSCL_DataToInt(ITS_OCTET *d, ITS_INT c = 4);
                                                                                
/* Copies the integer value in to the byte buffer in network byte order */
IDSAPP_DLLAPI void
IDSCL_IntToData(ITS_OCTET *d, ITS_UINT val, ITS_INT c = 4);

/* Print the byte buffer*/
IDSAPP_DLLAPI void
IDSCL_Print(ITS_OCTET *buf, ITS_ULONG len);

}


#endif

