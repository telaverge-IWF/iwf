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
 * ID: $Id: idc_common.h,v 3.7.46.1 2013/02/27 08:49:06 jvikram Exp $
 *
 * LOG: $Log: idc_common.h,v $
 * LOG: Revision 3.7.46.1  2013/02/27 08:49:06  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.7  2010/09/22 05:22:54  nvijikumar
 * LOG: GlobalUniqueAddr based routing/distribution support
 * LOG:
 * LOG: Revision 3.6  2010/07/07 08:31:04  nvijikumar
 * LOG: TCS compilation flags support
 * LOG:
 * LOG: Revision 3.5  2009/07/13 11:54:39  rajeshak
 * LOG: Option to set TCP keepalive timers.
 * LOG:
 * LOG: Revision 3.4  2009/04/14 09:15:06  sureshj
 * LOG: OVERLOAD & OVERLOAD_ABATED enums added
 * LOG:
 * LOG: Revision 3.3  2008/12/06 12:51:06  nvijikumar
 * LOG: Connection Disconnect Callback support
 * LOG:
 * LOG: Revision 3.2  2008/11/06 07:20:01  nvijikumar
 * LOG: UDP Transport support between IDS and IDC
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:00  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.12  2008/03/27 11:18:28  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.6.8.3  2007/10/01 19:28:05  hbhatnagar
 * LOG: Added IDS_CALLBACK_INFO struct and changed the signature of callback
 * LOG:
 * LOG: Revision 2.6.8.2  2007/04/12 10:53:56  rrath
 * LOG: Chnages to print Indication and Session-ID
 * LOG:
 * LOG: Revision 2.6.8.1  2007/04/04 06:13:54  nvijikumar
 * LOG: Send appIdType while registering with IDS.
 * LOG:
 * LOG: Revision 2.6  2006/11/17 06:08:56  kamakshilk
 * LOG: ReleaseSession and DccaEnabled APIs added
 * LOG:
 * LOG: Revision 2.5  2006/11/14 09:04:21  kamakshilk
 * LOG: Notification message type added
 * LOG:
 * LOG: Revision 2.4  2006/11/08 06:15:46  kamakshilk
 * LOG: Changes for 64-bit support.ITS_ULONG changed to ITS_UINT
 * LOG:
 * LOG: Revision 2.3  2006/10/31 10:00:06  kamakshilk
 * LOG: IDSCL_Print function added
 * LOG:
 * LOG: Revision 2.2  2006/10/16 14:22:01  kamakshilk
 * LOG: Changes to work with ITS-Diameter
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:39  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.7  2006/07/25 13:34:56  sumag
 * LOG: Updates to support Java.
 * LOG:
 * LOG: Revision 1.6  2006/06/14 09:20:09  kamakshilk
 * LOG: Added appIdentifier in IDS_DIAMETER structure.
 * LOG:
 * LOG: Revision 1.5  2006/04/25 12:29:57  adutta
 * LOG: Registration enum modified
 * LOG:
 * LOG: Revision 1.4  2006/04/07 13:56:39  adutta
 * LOG: Documentation using doxygen
 * LOG:
 * LOG: Revision 1.3  2006/04/06 08:03:09  adutta
 * LOG: Changes in Reg/D-reg struct
 * LOG:
 * LOG: Revision 1.2  2006/03/13 05:22:07  adutta
 * LOG: Impl. changes for diameter encode/decode
 * LOG:
 * LOG: Revision 1.1  2006/03/02 12:11:15  adutta
 * LOG: First cut
 * LOG:
 ****************************************************************************/
#ident "$Id: idc_common.h,v 3.7.46.1 2013/02/27 08:49:06 jvikram Exp $"


#ifndef IDS_CL_CMN_H
#define IDS_CL_CMN_H 

/** @file */ 

#include <idc_errors.h>


#if defined(WIN32)
 #if defined(IDSCL_IMPLEMENTATION)
    #define IDSCL_DLLAPI __declspec(dllexport)
 #else
    #define IDSCL_DLLAPI __declspec(dllimport)
 #endif
#else
  #define IDSCL_DLLAPI
#endif

typedef unsigned int     IDS_BOOLEAN;
typedef unsigned char    IDS_OCTET;
typedef unsigned short   IDS_USHORT;
typedef unsigned int     IDS_UINT;
typedef unsigned long    IDS_ULONG;
typedef char             IDS_CHAR;
typedef short            IDS_SHORT;
typedef int              IDS_INT;
typedef long             IDS_LONG;
typedef float            IDS_FLOAT;
typedef double           IDS_DOUBLE;
typedef void *           IDS_HANDLE;
typedef void *           IDS_SS7_HANDLE;
typedef char *           IDS_POINTER;

typedef IDS_OCTET       ITS_OCTET;
typedef IDS_INT         ITS_INT;
typedef IDS_UINT        ITS_UINT;
typedef IDS_ULONG       ITS_ULONG;

#define IDS_FALSE       (0U)
#define IDS_TRUE        (!IDS_FALSE)
#define IDS_SUCCESS     (0U)

#include <diameter/Command.h>

/* Event source */

#define IDS_APPDATA_SRC         (0x01U)




/* Max Diameter event size */
#define MAX_MSG_EVT                       20000
#define IDSCL_IP_ADDR_LEN                 16
#define IDS_DIA_MSG_TYPE_NEW_REQ          (0x0FU)
#define IDS_DIA_MSG_TYPE_SES_RLS          (0x0EU)
 
typedef enum
{
    IDS_TCP=0,
    IDS_UDP
}IDS_TRANS_TYPE;
/** Enumerated:
 *      IDS_CONNECTION_TYPE
 *
 *  Purpose:
 *      IDS_CONNECTION_TYPE defines connection type towards sever
 *
 *  Variables:
 *   \n IDS_PRIMARY_CONNECTION
 *   \n IDS_BACKUP_CONNECTION
 **/
typedef enum
{
    IDS_PRIMARY_CONNECTION = 1,
    IDS_BACKUP_CONNECTION
}
IDS_CONNECTION_TYPE;

/** Enumerated:
 *      IDS_REG_STATUS 
 *
 *  Purpose:
 *      IDS_REG_STATUS defines the registration status
 *
 *  Variables:
 *   \n SUCCESS
 *   \n FAILURE
 **/
typedef enum
{   
    SUCCESS,
    FAILURE,
    NOTREGISTERED
}
IDS_REG_STATUS;

/** Enumerated:
 *      IDS_ROUTING_CRITERIA
 *
 *  Purpose:
 *      IDS_ROUTING_CRITERIA defines the route criteria types
 *
 *  Variables:
 *   \n IDS_APP_IDENTIFIER
 **/
typedef enum
{
     IDS_APP_IDENTIFIER
}
IDS_ROUTING_CRITERIA;

/** Enumerated:
 *      IDS_MESSAGE_TYPE
 *
 *  Purpose:
 *      IDS_MESSAGE_TYPE  Different message types from server 
 *
 *  Variables:
 *   \n REGISTER_MSG
 *   \n DEREGISTER_MSG
 *   \n REGISTER_ACK_MSG
 *   \n DERGISTER_ACK_MSG
 *   \n SERVER_STATUS_MSG
 *   \n DIAMETER_MSG
 *   \n HEARTBEAT_MSG
 **/
typedef enum
{
    REGISTER_MSG,  
    DEREGISTER_MSG,
    REGISTER_ACK_MSG,
    DEREGISTER_ACK_MSG,
    SERVER_STATUS_MSG,
    DIAMETER_MSG,
    HEARTBEAT_MSG,
    DIASERVER_NOTIFY_MSG,
    GLOBAL_UNIQ_ADDR_MSG,
    GLOBAL_UNIQ_ADDR_ACK_MSG
}
IDS_MESSAGE_TYPE;


/** Structure:
 *      IDS_STATUS
 *
 *  Purpose:
 *      IDS_STATUS  Server status description in case of redundant
 *      server.
 *
 *  Variables:
 *   \n IDS_UINT             msgType        (Port number of the server)
 *   \n IDS_CHAR             ipAddr         (Server IP address)
 *   \n IDS_CONNECTION_TYPE  conType        (Primary/backup connection)
 **/
typedef struct
{
    IDS_UINT port;
    IDS_CHAR ipAddr[IDSCL_IP_ADDR_LEN];
    IDS_CONNECTION_TYPE conType;
}
IDS_STATUS;

/** Structure:
 *      IDS_REGISTER
 *
 *  Purpose:
 *      IDS_REGISTER Cointains the route criteria for registration
 *      to server.
 *
 *  Variables:
 *   \n IDS_ROUTING_CRITERIA msgType        (Enumerated data for client routes)
 *   \n IDS_UINT             appIdentifier  (Application Id)
 *   \n IDS_CONNECTION_TYPE  connectionType (Primary/backup connection)
 *   \n IDS_UINT             appIdType      (Type of Application Id)
 **/
typedef struct 
{
     IDS_ROUTING_CRITERIA routing_criteria;
     IDS_UINT appIdentifier;
     IDS_CONNECTION_TYPE connectionType;
     IDS_UINT appIdType;
}
IDS_REGISTER;

/** Structure:
 *      IDS_REGISTER_ACK
 *
 *  Purpose:
 *      IDS_REGISTER_ACK acknowledge information
 *      coming from server.
 *
 *  Variables:
 *   \n IDS_ROUTING_CRITERIA msgType   (Enumerated data for client routes)
 *   \n IDS_OCTET            result    (Success/Fail)
 *   \n IDS_CHAR             errorCode (If fail, error code)
 *   \n IDS_CHAR             ipAddr    (IP address of the server connected)
 *   \n IDS_INT              port      (Port number of the server connected)
 *   \n IDS_CONNECTION_TYPE  conType   (Primary/Backup connection)
 **/
typedef struct 
{
    IDS_ROUTING_CRITERIA     routing_criteria;
    IDS_REG_STATUS  result; /* If result is not SUCCESS look at errorcode */
    IDS_CHAR errorCode;
    IDS_CHAR isDccaEnabled;
    IDS_CHAR ipAddr[16];
    IDS_INT port;
    IDS_CONNECTION_TYPE conType;
}
IDS_REGISTER_ACK;

/** Structure:
 *      IDS_DEREGISTER_ACK
 *
 *  Purpose:
 *      IDS_DEREGISTER_ACK acknowledge information  
 *      coming from server.
 *
 *  Variables:
 *   \n IDS_ROUTING_CRITERIA msgType   (Enumerated data for client routes)
 *   \n IDS_OCTET            result    (Success/Fail)
 *   \n IDS_CHAR             errorCode (If fail, error code)
 **/
typedef struct
{
    IDS_ROUTING_CRITERIA     routing_criteria;
    IDS_OCTET  result;
    IDS_CHAR errorCode;
}
IDS_DEREGISTER_ACK;

/** Structure:
 *      IDS_DEREGISTER
 *
 *  Purpose:
 *      IDS_DEREGISTER Cointains the route criteria for de-registration
 *      from server.
 *
 *  Variables:
 *   \n IDS_ROUTING_CRITERIA msgType   (Enumerated data for client routes)
 **/
typedef struct
{
    IDS_ROUTING_CRITERIA routing_criteria;
} 
IDS_DEREGISTER;    

/** Structure:
 *      IDS_DIAMETER
 *
 *  Purpose:
 *      IDS_DIAMETER Contains the diameter message information
 *      coming from server.
 *
 *  Variables:
 *   \n IDS_OCTET            msgType       (Indication/Diameter Message)
 *   \n IDS_OCTET            indication    (Indication type)
 *   \n IDS_UINT             sessionIndex  (Session Index)
 *   \n IDS_UINT             appIdentifier (Application Id)
 *   \n diameter::CommandImpl* cImpl       (Pointer to DiameterCommand object)
 **/
typedef struct
{
    IDS_OCTET msgType;
    IDS_OCTET indication;
    IDS_UINT  sessionIndex;    
    IDS_UINT  appIdentifier;    
    diameter::CommandImpl* cImpl;
    ITS_OCTET data[4096];
}
IDS_DIAMETER;

typedef struct
{
    IDS_OCTET msgType;
    IDS_OCTET indication;
    IDS_UINT  sessionIndex;
    IDS_UINT  appIdentifier;
    ITS_OCTET data[4096];
    IDS_UINT  dataLen;
}
IDS_DIAMETER_BUFF;

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
IDS_DIASERVER_NOTIFY;

typedef enum
{
   IDS_GUA_ADD,
   IDS_GUA_DEL
}IDS_GUA_ACTION;

typedef struct _aim_gua_info
{
    IDS_GUA_ACTION action;
    ITS_UINT count;
    ITS_CHAR ipAddr[IDSCL_IP_ADDR_LEN];
}IDS_GUA_INFO;

typedef struct _aim_gua_ack
{
    IDS_GUA_ACTION action;
    IDS_REG_STATUS result;
}IDS_GUA_INFO_ACK;

/** Structure:
 *      IDS_MESSAGE
 *      
 *  Purpose:
 *
 *      IDS_MESSAGE structure is used to exchange  
 *      following information between application and 
 *      distributed server.\n
 *      a. Client ID\n
 *      b. Message type (Reg/D-reg/Reg-Ack/D-reg-Ack/Server Status/Diameter)\n
 *      c. Register message/ack\n
 *      d. De-register message/ack\n 
 *      e. Server status (In case of redundant server setup)\n
 *      f. Diameter message\n
 *
 **/
typedef struct
{
     IDS_UINT             clientID;
     IDS_MESSAGE_TYPE     msg_type;
     union
     {
         IDS_REGISTER          regInfo;
         IDS_DEREGISTER        deregInfo;
         IDS_REGISTER_ACK      regAck;
         IDS_DEREGISTER_ACK    deregAck;
         IDS_STATUS            servInfo;
         IDS_DIAMETER          diaInfo;
         IDS_DIASERVER_NOTIFY  notifyInfo;
         IDS_GUA_INFO          guaInfo;
         IDS_GUA_INFO_ACK      guaAck;
      }
      u;
}
IDS_MESSAGE;


typedef struct
{
     IDS_UINT             clientID;
     IDS_MESSAGE_TYPE     msg_type;
     union
     {
         IDS_REGISTER          regInfo;
         IDS_DEREGISTER        deregInfo;
         IDS_REGISTER_ACK      regAck;
         IDS_DEREGISTER_ACK    deregAck;
         IDS_STATUS            servInfo;
         IDS_DIAMETER_BUFF     diaInfo;
         IDS_DIASERVER_NOTIFY  notifyInfo;
      }
      u;
}
IDS_MESSAGE_BUFF;

typedef enum
{
    IDS_CONNECT,
    IDS_DISCONNECT, 
    IDS_OVERLOAD, 
    IDS_OVERLOAD_ABATED 
}
IDS_CALLBACK_TYPE;

/* This struct contains callback info  and is passed to callback function
 * at the time of invocation. ( Added as enhancement to Bridgewater multiple
 * Registraion of Application Id).
 */

typedef struct 
{
    IDS_CALLBACK_TYPE type;
    IDS_STATUS        ids_stat;
    IDS_BOOLEAN       isConUp;
    IDS_REG_STATUS    regStatus;
    IDS_BOOLEAN       isConClose;
    IDS_BOOLEAN       isPrimary;
}
IDS_CALLBACK_INFO;

/* This struct contains TCP KeepAlive timer values.
 */
typedef struct
{
    IDS_UINT            keepAliveCnt;
    IDS_UINT            keepAliveIdle;
    IDS_UINT            keepAliveIntvl;
}
IDS_TCP_TIMER;


/* Changing the original signature of callback to accomodate the 
 * the mutliple registration enhancements.
 */
typedef void (*IDS_CALLBACK)(IDS_CALLBACK_INFO idsCbInfo);

extern "C"
{
/* Reads the byte buffer(network byte order) and returns the integer value */
IDSCL_DLLAPI ITS_UINT 
IDSCL_DataToInt(ITS_OCTET *d, ITS_INT c = 4);
                                                                                
/* Copies the integer value in to the byte buffer in network byte order */
IDSCL_DLLAPI void
IDSCL_IntToData(ITS_OCTET *d, ITS_UINT val, ITS_INT c = 4);

/* Prints the byte buffer */
IDSCL_DLLAPI void
IDSCL_Print(ITS_OCTET *buff, ITS_ULONG len);

/* Retrieves the session Index from the session Id string */
IDSCL_DLLAPI ITS_UINT
IDSCL_GetSessionIndex(std::string &sessStr);

IDSCL_DLLAPI ITS_INT
IDSCL_SendGlobalUniqAddrMsg(ITS_HANDLE handle, IDS_MESSAGE *msg);
}

#endif

