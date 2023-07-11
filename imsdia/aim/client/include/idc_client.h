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
 * ID: $Id: idc_client.h,v 3.5 2009/07/13 11:54:39 rajeshak Exp $
 *
 * LOG: $Log: idc_client.h,v $
 * LOG: Revision 3.5  2009/07/13 11:54:39  rajeshak
 * LOG: Option to set TCP keepalive timers.
 * LOG:
 * LOG: Revision 3.4  2009/03/25 04:04:05  nvijikumar
 * LOG: Provided API to bind local IP and Port
 * LOG:
 * LOG: Revision 3.3  2008/11/06 07:20:01  nvijikumar
 * LOG: UDP Transport support between IDS and IDC
 * LOG:
 * LOG: Revision 3.2  2008/10/28 12:03:32  nvijikumar
 * LOG: IssueID: none
 * LOG: FeatureID: none
 * LOG: Description: Porting Performance changes from 3.0 branch
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:00  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.9  2008/03/27 11:18:28  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.4  2006/11/17 06:08:56  kamakshilk
 * LOG: ReleaseSession and DccaEnabled APIs added
 * LOG:
 * LOG: Revision 2.3  2006/11/08 06:15:46  kamakshilk
 * LOG: Changes for 64-bit support.ITS_ULONG changed to ITS_UINT
 * LOG:
 * LOG: Revision 2.2  2006/10/16 14:22:01  kamakshilk
 * LOG: Changes to work with ITS-Diameter
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:39  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.6  2006/09/06 11:24:38  kamakshilk
 * LOG: IDS_INSERT_APPID definition changed to IntToData()
 * LOG:
 * LOG: Revision 1.5  2006/07/25 13:34:56  sumag
 * LOG: Updates to support Java.
 * LOG:
 * LOG: Revision 1.4  2006/05/30 09:37:50  yranade
 * LOG: Changes to compile with CC compiler on solaris 10.
 * LOG:
 * LOG: Revision 1.3  2006/04/06 08:02:29  adutta
 * LOG: Macro added to set app-Id
 * LOG:
 * LOG: Revision 1.2  2006/03/13 05:22:07  adutta
 * LOG: Impl. changes for diameter encode/decode
 * LOG:
 * LOG: Revision 1.1  2006/03/02 12:11:15  adutta
 * LOG: First cut
 * LOG:
 ****************************************************************************/
#ident "$Id: idc_client.h,v 3.5 2009/07/13 11:54:39 rajeshak Exp $"

#ifndef CLIENTAPI_H
#define CLIENTAPI_H

#include <idc_common.h>

#if defined(WIN32)
#if defined(IDSCL_IMPLEMENTATION)
#define IDSCL_DLLAPI __declspec(dllexport)
#else
#define IDSCL_DLLAPI __declspec(dllimport)
#endif
#else
#define IDSCL_DLLAPI
#endif


#define IDS_IP_ADDR_LENi              15
#define SOC_CONNECT_INTERVAL          5 
#define IDS_ROUTING_INFO              0

#define IDS_DIA_APPID_POS             8 

#define IDS_INSERT_APPID(data,index, id)            \
     IDSCL_IntToData(data+index+IDS_DIA_APPID_POS,id);

typedef struct
{
    ITS_THREAD          info;
    ITS_THREAD_FUNC     func;
    IDS_BOOLEAN         isRunning;
}
IDS_THR_INFO;

typedef struct
{
    IDS_BOOLEAN         isSet;
    IDS_UINT            port;
    IDS_CHAR            ipAddr[IDSCL_IP_ADDR_LEN];
}IDC_SOCKBIND_INFO;
                                                                                
typedef struct
{
    ITS_SocketInfo      *sockInfo;
    IDS_THR_INFO        thrInfo;
    ITS_MUTEX           readLock;
    ITS_MUTEX           writeLock;
    IDS_BOOLEAN         isUp;
    IDS_REG_STATUS      regStatus;
    IDS_UINT            port;
    IDS_CHAR            ipAddr[IDSCL_IP_ADDR_LEN];
    IDS_BOOLEAN         isInitialized;
    IDS_BOOLEAN         isClose;
    IDS_BOOLEAN         isPrimary;
    IDS_TRANS_TYPE      transType;
    IDC_SOCKBIND_INFO   lSockBindInfo;
}
IDS_CONNECTION_INFO;

typedef struct
{
    EMLIST_Manager       *taskQue;
    IDS_UINT             noCurrEnts;
}
IDS_TRANS_QUE;

typedef struct
{
    IDS_CONNECTION_INFO    primaryInfo;
    IDS_CONNECTION_INFO    backupInfo;
    IDS_TRANS_QUE          taskTrans;
    IDS_TRANS_QUE          outBoundTaskTrans;
    IDS_CALLBACK           func;
    IDS_UINT               clid; 
    IDS_OCTET              *reRegInfo;
    IDS_USHORT             regInfoLen;
    IDS_BOOLEAN            isDccaEnabled;
    IDS_TCP_TIMER          tcpTimer;
}
IDS_CONNECTION;

typedef struct
{
    ITS_OCTET       *originHost;
    ITS_OCTET       *originRealm;
}
IDS_HOSTINFO;



/*
 * Write the event to Server
 */

IDSCL_DLLAPI IDS_INT
IDSCL_WriteEvent(IDS_HANDLE handle, ITS_EVENT *evt);
                                                                                
/*
 * Read the event from Server
 */
IDSCL_DLLAPI IDS_INT
IDSCL_ReadEvent(IDS_HANDLE handle, ITS_EVENT *evt);
                                                                                
/*
 * This function handles the client events
 */
IDSCL_DLLAPI IDS_INT
IDSCL_HandleClientEvent(ITS_EVENT *evt);


IDSCL_DLLAPI IDS_INT
IDSCL_SendEvent(IDS_HANDLE handle, ITS_EVENT *evt);
                                                                                
/* 
 * Connect to the server
 */
IDSCL_DLLAPI IDS_INT
IDSCL_Connect(IDS_CONNECTION_INFO *info, IDS_TCP_TIMER* timerVal);

/* Close the connection with the connection type */
                                                                                
IDSCL_DLLAPI IDS_INT
IDSCL_CloseCon(IDS_HANDLE handle , IDS_CONNECTION_TYPE type);

/* Put event on the Queue */
                                                                                
IDSCL_DLLAPI IDS_INT
IDSCL_PutEventOnTaskQue(IDS_TRANS_QUE *taskTran, ITS_EVENT *evt);

/* Get event from the Queue */                                                                                
IDSCL_DLLAPI IDS_INT
IDSCL_GetEventFromTaskQue(IDS_TRANS_QUE *taskTran, ITS_EVENT *evt);

/* To varify whehter the registration info is correct or not */

IDSCL_DLLAPI IDS_INT
IDSCL_ValidateContext(IDS_REGISTER *reginfo);


/*
 * Close the connection, for the user
 */
IDSCL_DLLAPI IDS_INT
IDSCL_CloseConnection(IDS_CONNECTION_TYPE type);


extern "C"
{
/* Populates the struct from event data*/
IDSCL_DLLAPI int
IDSCL_Decode(IDS_MESSAGE *msg, ITS_EVENT *event);

IDSCL_DLLAPI int
IDSCL_decode(IDS_MESSAGE_BUFF *msg, ITS_EVENT *event);

/* Populates the event data from struct*/
IDSCL_DLLAPI int
IDSCL_Encode(IDS_MESSAGE *msg, ITS_EVENT *event);

}


#endif
