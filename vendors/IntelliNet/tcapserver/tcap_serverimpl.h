/****************************************************************************
 *                                                                          *
 *     Copyright 2003 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * $Id: tcap_serverimpl.h,v 9.1 2005/03/23 12:55:02 cvsadmin Exp $ID   $
 * ID:
 *
 * $Log: tcap_serverimpl.h,v $
 * Revision 9.1  2005/03/23 12:55:02  cvsadmin
 * Begin PR6.5
 *
 * Revision 1.5  2003/10/23 06:41:47  ssingh
 * Changes done for message routing to respective clients
 * based on RouteInfo stored.
 *
 * Revision 1.4  2003/10/22 06:05:58  ssingh
 * Changes done to handle LID table finding based on DID and
 * DID to LID table entry for appInitiated message on receive
 * of Dialouge from Client. LID to DID structure changed.
 *
 * Revision 1.3  2003/10/11 09:55:42  ssingh
 * Code changes done for Application initiated and response
 * from Remote for Application Initiated message.
 *
 * Revision 1.2  2003/10/10 08:51:37  vjatti
 * Changed the signature for  GetRouteStyle to ITS_OCTET from int.
 * as it returns style which is of type ITS_OCTET
 *
 * Revision 1.1  2003/10/07 12:29:19  sswami
 * Multiple TCAP applications binding initial commits
 * Log  $
 * Log:
 *
 ****************************************************************************/

#ifndef SERVERIMPL_H
#define SERVERIMPL_H

#if defined ANSI
#include<ansi/tcap.h>
#else
#include<itu/tcap.h>
#endif

#include<stdlib.h>
#include<tcap_intern.h>

char* style;
/* Server Event types */
#define SL_SRC_SERVER 0x11

/* These are app type */
#define SL_APP_TCAP_SRC          0x02
#define SL_TCAP_REGISTER_EVENT   0x02
#define SL_TCAP_DEREGISTER_EVENT 0x04

/* Request Events */
#define SL_TCAP_ALLOC_DID           0x08
#define SL_TCAP_REGISTER_RESP       0xF1
#define SL_TCAP_DEREGISTER_RESP     0xF2
#define SL_TCAP_ALLOC_DID_RESP      0xF7

#define ROUTE_DPC_STRING "dpc"
#define ROUTE_SSN_STRING "ssn"
#define ROUTE_OPC_DPC_STRING "opc-dpc"
#define ROUTE_DPC_SIO_STRING "dpc-sio"
#define ROUTE_DPC_SSN_STRING "dpc-ssn"
#define ROUTE_OPC_DPC_SIO_STRING "opc-dpc-sio"
#define ROUTE_OPC_DPC_SSN_STRING "opc-dpc-ssn"
#define ROUTE_OPC_DPC_SIO_SSN_STRING "opc-dpc-sio-ssn"

/* Table Ids */
#define SL_TCAP_ROUTING_INFO_RID      1
#define SL_TCAP_LID_TO_DID_TABLE_ID   2
#define SL_TCAP_DID_TO_LID_TABLE_ID   3

typedef enum
{
    DPC,
    SSN,
    OPC_DPC,
    DPC_SIO,
    DPC_SSN,
    OPC_DPC_SIO,
    OPC_DPC_SSN,
    OPC_DPC_SIO_SSN
}
ROUTE_STYLE;


typedef struct
{
        ITS_OCTET           route_style;
        MTP3_POINT_CODE     opc;
        MTP3_POINT_CODE     dpc;
        ITS_OCTET           sio;
        ITS_OCTET           ssn;
}
SL_ROUTE_KEY;

typedef struct _sl_tcap_routing_info
{
    struct _sl_tcap_routing_info *next; 
    SL_ROUTE_KEY                 rKey;
    ITS_UINT                     client_id;
}
SL_TCAP_ROUTING_INFO;

/* -------------------------- starts here -----------------*/
typedef struct
{
    ITS_CTXT                     lid;
    MTP3_POINT_CODE              opc;
    MTP3_POINT_CODE              dpc;
    ITS_OCTET                    ssn;
    ITS_UINT                     client_id;
}
SL_LID_XPORT_ID;

typedef struct _sl_tcap_lid_to_did
{
    struct _sl_tcap_lid_to_did   *next;
    SL_LID_XPORT_ID              lidXportKey;
    ITS_CTXT                     did;
    ITS_UINT                     clientId;
}
SL_TCAP_LID_TO_DID_INFO;

typedef struct _sl_tcap_did_to_lid
{
    struct _sl_tcap_did_to_lid   *next;
    ITS_CTXT                     didKey;
    SL_LID_XPORT_ID              lidXport;
    ITS_BOOLEAN                  toDelete;
}
SL_TCAP_DID_TO_LID_INFO;

/* -------------------------- ends here -----------------*/

/* Initializes the server hash tables */
int SL_Init_HashTables();

/* Deletes the hash tables */
int SL_Term_HashTables();

/* Register TCAP App */
int SL_Register(int sockId, ITS_EVENT *evt);

/* DeRegister the cleint */
int SL_Deregister(int sockId, ITS_EVENT *evt);

/* Get the Routing Style */
ITS_OCTET GetRouteStyle(char*);

/* Display the Routing Info based on the style */
void SL_PrintRouteStyle(SL_ROUTE_KEY rKey);

/* Alloc Entry in the table */
int SL_AllocTCAPRoutingInfo(int sockId, SL_ROUTE_KEY rKey); 

/* Delete Entry in the table for this cleint */
int SL_DelTCAPRoutingInfo(int sockId, SL_ROUTE_KEY rKey);

/* Alloc Entry in the table */
int SL_FindTCAPRoutingInfo(SL_ROUTE_KEY rKey, SL_TCAP_ROUTING_INFO *rInfo);

/* Hash Iterate function */
int SL_TCAPRoutingIterate(HASH_IterateEntryProc proc, void *in, void *out);

/* Clean up routing tables for this cleint */
int SL_DeleteClientRoutingInfo(int clientId);

/* This function proc to delete client entry */
int SL_DelIterProc(ITS_INT context, ITS_POINTER data, void *in, void *out);

/* This function forms the event in response to the request for 
   registration and * deregistration */
int SL_SendRegDeregResponse(int sockId, SL_ROUTE_KEY rKey,
                                ITS_UINT ret, ITS_INT eventType);

/* -------------------------- starts here -----------------*/
/* This part is for LID 2 DID and DID 2 LID tables */

/* Alloc Entry in the table */
int SL_AllocTCAPLidToDid (ITS_CTXT did, SL_LID_XPORT_ID lidXportKey);

/* Alloc Entry in the table */
int SL_FindTCAPLidToDid (SL_TCAP_LID_TO_DID_INFO *lidToDidInfo,
                         SL_LID_XPORT_ID lidXportKey);

/* Delete Entry in the table for this cleint */
int SL_DeleteTCAPLidToDid(SL_LID_XPORT_ID lidXportKey);

/* Alloc Entry in the table */
int SL_AllocTCAPDidToLid(SL_LID_XPORT_ID lidXport, ITS_CTXT didKey);

/* Alloc Entry in the table */
int SL_FindTCAPDidToLid(SL_TCAP_DID_TO_LID_INFO *didToLidInfo,
                                              ITS_CTXT didKey);

/* Delete Entry in the table for this cleint */
int SL_DeleteTCAPDidToLid(ITS_CTXT didKey);

/* Send DID/LID allocate response to respective app */
void TCAP_SendDidAllocResp(ITS_CTXT did, SL_ROUTE_KEY rKey);

/* function to get routing info with the help of DID */
int SL_FindClientRoutingInfo(ITS_CTXT did, ITS_USHORT *socketId);

/* -------------------------- ends here -----------------*/

#endif
