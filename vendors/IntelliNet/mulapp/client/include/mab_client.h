/****************************************************************************
 *                                                                          *
 *     Copyright 2002 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * ID: $Id: mab_client.h,v 1.2 2005/06/02 13:50:31 adutta Exp $
 *
 * LOG: $Log: mab_client.h,v $
 * LOG: Revision 1.2  2005/06/02 13:50:31  adutta
 * LOG: Changes done for redundancy.
 * LOG:
 * LOG: Revision 1.1  2005/05/25 10:13:58  mmanikandan
 * LOG: Initial Commit Multiple Application Binding.
 * LOG:
 *
 ****************************************************************************/

#ifndef CLIENTAPI_H
#define CLIENTAPI_H

#include <mab_cmn.h>
#include <its_sockets.h>
#include <its_emlist.h>
#include <its_hmi.h>
#include <its_thread.h>

#if defined(WIN32)
#if defined(MABCL_IMPLEMENTATION)
#define MABCL_DLLAPI __declspec(dllexport)
#else
#define MABCL_DLLAPI __declspec(dllimport)
#endif
#else
#define MABCL_DLLAPI
#endif

#if defined(CCITT)
#include <itu/tcap.h>
#include <itu/isup.h>
#elif defined(ANSI)
#include <ansi/tcap.h>
#include <ansi/isup.h>
#endif

#define MABCL_IP_ADDR_LEN 15
#define SOC_CONNECT_INTERVAL  1
#define CL_ROUTING_INFO 0

typedef enum
{
    MABCL_PRIMARY_CONNECTION =0,
    MABCL_BACKUP_CONNECTION
}
MABCL_CONNECTION_TYPE;
                                                                                
typedef enum
{
    INIT,
    SUCCESS,
    FAILURE
}
REG_STATUS;

typedef struct
{
    ITS_THREAD          info;
    ITS_THREAD_FUNC     func;
    ITS_BOOLEAN         isRunning;
}
MABCL_THR_INFO;
                                                                                
typedef struct
{
    ITS_SocketInfo      *sockInfo;
    MABCL_THR_INFO      thrInfo;
    ITS_MUTEX           readLock;
    ITS_MUTEX           writeLock;
    ITS_BOOLEAN         isUp;
    REG_STATUS          regStatus;
    ITS_UINT            port;
    char                ipAddr[MABCL_IP_ADDR_LEN];
    ITS_BOOLEAN         isInitialized;
    ITS_BOOLEAN         isClose;
    ITS_BOOLEAN         isPrimary;
}
MABCL_CONNECTION_INFO;

typedef struct
{
    EMLIST_Manager       *taskQue;
    ITS_UINT             noCurrEnts;
}
MABCL_TRANS_QUE;

typedef struct
{
    MABCL_CONNECTION_INFO    primaryInfo;
    MABCL_CONNECTION_INFO    backupInfo;
    MABCL_TRANS_QUE          taskTrans;
    ITS_CTXT                 ltid;
    ITS_CTXT                 utid;
    ITS_ULONG                clid; 
    ITS_OCTET                *reRegInfo;
    ITS_USHORT               regInfoLen;
}
MABCL_CONNECTION;



HASH_Table _CL_CTXT_info;

/*
 * Send the event to Server
 */

MABCL_DLLAPI ITS_INT
MABCL_WriteEvent(ITS_HANDLE handle, ITS_EVENT *evt);
                                                                                
/*
 * Read the event from Server
 */
MABCL_DLLAPI ITS_INT
MABCL_ReadEvent(ITS_HANDLE handle, ITS_EVENT *evt);
                                                                                
/*
 * This function handles the client events
 */
MABCL_DLLAPI ITS_INT
MABCL_HandleClientEvent(ITS_EVENT *evt);

/* 
 * Send the event to the server
 */

MABCL_DLLAPI ITS_INT
MABCL_SendEvent(ITS_HANDLE handle, ITS_EVENT *evt);
                                                                                
/* 
 * Connect to the server
 */
MABCL_DLLAPI ITS_INT
MABCL_Connect(MABCL_CONNECTION_INFO *info);

/* Close the connection with the connection type */
                                                                                
MABCL_DLLAPI ITS_INT
MABCL_CloseCon(ITS_HANDLE handle , MABCL_CONNECTION_TYPE type);

/* Put event on the Queue */
                                                                                
MABCL_DLLAPI ITS_INT
MABCL_PutEventOnTaskQue(MABCL_TRANS_QUE *taskTran, ITS_EVENT *evt);

/* Get event from the Queue */                                                                                
MABCL_DLLAPI ITS_INT
MABCL_GetEventFromTaskQue(MABCL_TRANS_QUE *taskTran, ITS_EVENT *evt);

/* To varify whehter the registration info is correct or not */

MABCL_DLLAPI ITS_INT
MABCL_ValidateContext(MABCL_REGISTER *reginfo);
/*
 * Pre initialization function
 */
MABCL_DLLAPI ITS_INT
MABCL_PreInitialize(ITS_HANDLE *handle);

MABCL_DLLAPI ITS_HANDLE
MABCL_GetHandle();


/*
 * initialization function
 */
MABCL_DLLAPI ITS_INT
MABCL_Initialize(const char *host, ITS_INT port, 
                 MABCL_CONNECTION_TYPE type);

/*
 * Do the clean up during Terminate 
 */
MABCL_DLLAPI void
MABCL_Terminate();

/*
 * Close the connection, for the user
 */
MABCL_DLLAPI ITS_INT
MABCL_CloseConnection(MABCL_CONNECTION_TYPE type);

/*
 * Registration function
 */
MABCL_DLLAPI ITS_INT
MABCL_Register(ITS_HANDLE handle, MABCL_MESSAGE *ctxt);


/*
 * Deregister function
 */
MABCL_DLLAPI ITS_INT
MABCL_Deregister(ITS_HANDLE handle, MABCL_MESSAGE *ctxt);


/*
 * GetNextEvent function
 */
MABCL_DLLAPI ITS_INT
MABCL_GetNextEvent(ITS_HANDLE handle, ITS_EVENT *evt);
/* This function checks whether one of the connections is up for
   writing on to the socket. Returns true or false */

MABCL_DLLAPI ITS_INT
MABCL_IsRegistered(ITS_HANDLE handle);

MABCL_DLLAPI ITS_INT
GetISUPEvent(ITS_EVENT *evt, ITS_OCTET *buf, ITS_USHORT len);


MABCL_DLLAPI ITS_INT
MABCL_UpdateAddrsAndQOS(TCAP_DLG *dlg, SCCP_ADDR origaddr, 
                        SCCP_ADDR destaddr, DLG_QOS qos, 
                        MTP3_POINT_CODE *opc, MTP3_POINT_CODE *dpc);

MABCL_DLLAPI ITS_INT
MABCL_GetDlgComponent(TCAP_DLG  *dlg, ITS_CTXT *dlgid, 
                      TCAP_CPT  *cpt, ITS_OCTET  *numCpts,
                      ITS_OCTET *data,ITS_USHORT len);
#endif
