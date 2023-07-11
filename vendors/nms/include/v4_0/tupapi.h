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


/* TUP API functions */
#ifdef __cplusplus
extern "C" {
#endif

DWORD NMSAPI     TUPRetrieveMessage(CTAHD ctahd, TupAllSdus *event, TupRcvInfoBlk *infoBlk);
DWORD NMSAPI     TUPGetApiStats( CTAHD ctahd, TUPAPISTATS *pstats, U8 bReset );
DWORD NMSAPI     TUPConnectReq(CTAHD ctahd, U8 board, TupSpId spId, TupInstId suInstId, TupInstId spInstId,
                               Bool cirSelFlg, CirIdx circuit, TupConEvnt *conEvnt);
DWORD NMSAPI     TUPConnectResp(CTAHD ctahd, U8 board, TupSpId spId, TupInstId suInstId, TupInstId spInstId,
                                CirIdx circuit, TupConRspEvnt *conRspEvnt);
DWORD NMSAPI     TUPConnectStatusReq(CTAHD ctahd, U8 board, TupSpId spId, TupInstId suInstId, TupInstId spInstId,
                                     CirIdx circuit, TupCnStEvnt *conStEvnt, U8 eventType);
DWORD NMSAPI     TUPReleaseReq(CTAHD ctahd, U8 board, TupSpId spId, TupInstId suInstId, TupInstId spInstId,
                               CirIdx circuit, TupRelEvnt *relEvnt);
DWORD NMSAPI     TUPReleaseResp(CTAHD ctahd, U8 board, TupSpId spId, TupInstId suInstId, TupInstId spInstId,
                                   CirIdx circuit, TupRelEvnt *relEvnt);
DWORD NMSAPI     TUPStatusReq(CTAHD ctahd, U8 board, TupSpId spId, TupInstId suInstId, TupInstId spInstId,
                              CirIdx circuit, U8 eventType, TupStaEvnt *statEvnt);
U8 NMSAPI        TUPASCIItoADDR( char *ascii, TupTknStr *addrSigs, short length);
U8 NMSAPI        TUPADDRtoASCII( TupTknStr *addrSigs, char *ascii);

#ifdef   __cplusplus
}
#endif

#endif
