/**************************************************************************
 **
 **                         PROPRIETARY NOTICE
 **
 **                         Copyright (c) 1997
 **                     By Natural MicroSystems, Inc.
 **
 **
 **  The following is licensed program material and is considered
 **  proprietary and confidential.  No part of this program may be
 **  reproduced or used in any form or by any means without the express
 **  written permission of Natural MicroSystems, Inc.
 **
 **  This product also contains software that is protected by the
 **  following copyrights.
 **
 **        (c) Copyright 1989-1995, Trillium Digital Systems, Inc.
 *************************************************************************/

/* File: tupapi.h
 *
 * Data types, function prototypes, and return codes for SS7 TUP API.
 *
 */
#ifndef _TUPAPI_H_
#define _TUPAPI_H_

#include "tuptype.h"
#include "tupmsgs.h"
#include "tupdef.h"

/* TUP API functions */
#ifdef __cplusplus
extern "C" {
#endif

short TXTUPAPIFUNC      TUPBindReq( U8 board, TupSpId spId, TupEnt srcEnt, TupInst srcInst, TupSuId suId );
short TXTUPAPIFUNC      TUPUnBindReq( U8 board, TupSpId spId );
OS_HSYNC TXTUPAPIFUNC   TUPSyncObj( U8 board, S16 *errval );
short TXTUPAPIFUNC      TUPRetrieveMessage(U8 board, TupAllSdus *event, TupRcvInfoBlk *infoBlk);
short TXTUPAPIFUNC      TUPConnectReq( U8 board, TupSuId suId, TupInstId suInstId,
                                    TupInstId spInstId, Bool cirSelFlg, CirIdx circuit,
                                    TupConEvnt *conEvnt) ;
short TXTUPAPIFUNC      TUPConnectResp( U8 board, TupSuId suId, TupInstId suInstId,
                                    TupInstId spInstId, CirIdx circuit,
                                    TupConRspEvnt *conRspEvnt) ;
short TXTUPAPIFUNC      TUPConnectStatusReq( U8 board, TupSuId suId, TupInstId suInstId,
                                    TupInstId spInstId, CirIdx circuit,
                                    TupCnStEvnt *conStEvnt, U8 eventType) ;
short TXTUPAPIFUNC      TUPReleaseReq( U8 board, TupSuId suId, TupInstId suInstId,
                                    TupInstId spInstId,
                                    CirIdx circuit, TupRelEvnt *relEvnt) ;
short TXTUPAPIFUNC      TUPReleaseResp( U8 board, TupSuId suId, TupInstId suInstId,
                                    TupInstId spInstId,
                                    CirIdx circuit, TupRelEvnt *relEvnt) ;
short TXTUPAPIFUNC      TUPStatusReq( U8 board, TupSuId suId, TupInstId suInstId,
                                    TupInstId spInstId, CirIdx circuit,
                                    U8 eventType, TupStaEvnt *statEvnt) ;
void TXTUPAPIFUNC       TUPASCIItoADDR( char *ascii, TupTknStr *addrSigs, short length );
void TXTUPAPIFUNC       TUPADDRtoASCII( TupTknStr *addrSigs, char *ascii );

void TXTUPAPIFUNC       TUPInitConnectEvent( TupConEvnt *conEvnt, char *addrSigs,
                                    short aLen, char *calling, short cLen);
#ifdef   __cplusplus
}
#endif

#endif
