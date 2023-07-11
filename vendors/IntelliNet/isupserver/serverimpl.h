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
 * $Id: serverimpl.h,v 9.1 2005/03/23 12:54:27 cvsadmin Exp $
 *
 * $Log: serverimpl.h,v $
 * Revision 9.1  2005/03/23 12:54:27  cvsadmin
 * Begin PR6.5
 *
 * Revision 1.2  2005/03/23 09:41:22  cvsadmin
 * PR6.4.2 sources propagated to Current.
 *
 * Revision 1.1.2.4.6.2.12.1  2004/12/15 05:52:46  mmanikandan
 * Windows Build Support.
 *
 * Revision 1.1.2.4.6.2  2004/01/27 14:30:59  sjaddu
 * Changes for active-backup configuration.
 *
 * Revision 1.1.2.4.6.1  2004/01/05 10:01:25  sjaddu
 * Merged code from tcs isup branch.
 *
 * Revision 1.1.2.4.2.2  2003/08/29 09:51:31  akumar
 * Modifications for Routing and Deregistration APi.
 *
 * Revision 1.1.2.4.2.1  2003/08/26 12:48:45  sjaddu
 * Redunadnacy changes done.
 *
 * Revision 1.1.2.4  2003/06/25 09:05:43  sjaddu
 * Changed the opcode values.
 *
 * Revision 1.1.2.3  2003/06/20 11:18:11  sjaddu
 * added isup_intern.h files.
 *
 * Revision 1.1.2.2  2003/06/18 08:17:13  tsanthosh
 * Added Request & Response functionality.
 *
 * Revision 1.1.2.1  2003/06/05 05:43:46  sjaddu
 * Added first revision of files for isupserver.
 *
 *
 ****************************************************************************/

#ifndef SERVERIMPL_H
#define SERVERIMPL_H

#if defined ANSI
#include<ansi/isup.h>
#else
#include<itu/isup.h>
#endif

#include<stdlib.h>
#include<isup_intern.h>

#if defined(WIN32)
#if defined(ISUP_SERVER_IMPLEMENTATION)
#define SRVDLLAPI __declspec(dllexport)
#else
#define SRVDLLAPI __declspec(dllimport)
#endif
#else
#define SRVDLLAPI
#endif

/* Server Event types */
#define SL_SRC_SERVER 0x11

/* These are app type */
#define SL_APP_ISUP_SRC   0x01
#define SL_APP_TCAP_SRC   0x02

#define SL_ISUP_REGISTER_EVENT 0x01
#define SL_TCAP_REGISTER_EVENT 0x02

#define SL_ISUP_DEREGISTER_EVENT 0x03
#define SL_TCAP_DEREGISTER_EVENT 0x04

/* Request Events */
#define SL_ISUP_RESERVE_CIC_REQ   0x05
#define SL_ISUP_UNRESERVE_CIC_REQ 0x09

/* For Backup Server */
#define SL_ISUP_REGISTER_BACKUP_EVENT   0x0A
#define SL_ISUP_DEREGISTER_BACKUP_EVENT 0x0B

#define SL_ISUP_RESERVE_CIC_RESP    0xF1
#define SL_ISUP_REGISTER_RESP       0xF2
#define SL_ISUP_DEREGISTER_RESP     0xF3
#define SL_ISUP_UNRESERVE_CIC_RESP  0xF4

#define SL_ISUP_ROUTING_INFO_RID 1

typedef enum
{
    SL_PRIMARY_CONNECTION =0,
    SL_BACKUP_CONNECTION
}
SL_CONNECTION_TYPE;

typedef struct 
{
    ITS_UINT  client_id;
    ITS_BOOLEAN  isUp;
}
SL_CONECTION;

typedef struct _sl_isup_routing_info
{
    struct _sl_isup_routing_info *next; 
    MTP3_HEADER                  opc_dpc_ni;
    SL_CONECTION                 primCon;
    SL_CONECTION                 backupCon;
}
SL_ISUP_ROUTING_INFO;

/*
 * Initializes the server hash tables
 */
int SL_Init_HashTables();


/*
 * Deletes the hash tables
 */
int SL_Term_HashTables();

/*
 * Register ISUP App
 */
int SL_Register(int sockId, ITS_EVENT *evt);

/*
 * DeRegister the cleint
 */
int SL_Deregister(int sockId, ITS_EVENT *evt);

/*
 * Alloc Entry in the table
 */
int SL_AllocISUPRoutingInfo(int sockId, 
                           MTP3_HEADER mtp3Hdr, 
                           SL_CONNECTION_TYPE type);


/*
 * Delete Entry in the table for this cleint
 */
int SL_DelISUPRoutingInfo(int sockId, MTP3_HEADER mtp3Hdr);

/*
 * Alloc Entry in the table
 */
int SL_FindISUPRoutingInfo(MTP3_HEADER mtp3Hdr, SL_ISUP_ROUTING_INFO *rInfo);

/*
 * Update the routing table
 */
int SL_UpdateISUPRoutingInfo(SL_ISUP_ROUTING_INFO *rInfo);


/*
 * Hash Iterate function
 */
int SL_ISUPRoutingIterate(HASH_IterateEntryProc proc, void *in, void *out);

/*
 * Clean up routing tables for this cleint
 */
int SL_DeleteClientRoutingInfo(int clientId);

/*
 * This function proc to delete client entry
 */
int SL_DelIterProc(ITS_INT context, ITS_POINTER data, void *in, void *out);

/*
 * This function handles request for Reserve cic api 
 */
ITS_INT SL_HandleReserveCICReq(ITS_UINT handle, ITS_EVENT *event);

/*
 * This function handles request for Reserve cic api 
 */
ITS_INT SL_HandleUnReserveCICReq(ITS_UINT handle, ITS_EVENT *event);

/*
 * This function forms the event in response to the request for reserve cic 
 */
ITS_INT SL_SendReserveCICResponse(ITS_UINT handle, ITS_EVENT *event, 
                                  ITS_UINT ret, ITS_OCTET cic_state, 
                                  ITS_CTXT vcic);

/*
 * This function forms the event in response to the request for unreserve cic 
 */
ITS_INT SL_SendUnReserveCICResponse(ITS_UINT handle, ITS_EVENT *event, 
                                    ITS_UINT ret);

/*
 * This function forms the event in response to the request for registration and * deregistration
 */
ITS_INT SL_SendRegDeregResponse(int sockId, MTP3_HEADER mtp3,
                                ITS_UINT ret, ITS_INT eventType);

ITS_INT SL_HandleStateChangeEventFromApp(ITS_EVENT *evt);

ITS_USHORT SL_HandleStateChangeEventFromStack(ITS_EVENT *evt);

#endif
