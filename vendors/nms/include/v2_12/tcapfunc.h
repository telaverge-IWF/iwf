/*****************************************************************************
******************************************************************************
*-----------------------------------------------------------------------------
*-----------------------------------------------------------------------------
**
**   tcapfunc.h
**
**      Function prototypes necessary for utilization
**      of the TCAP API.
**
*-----------------------------------------------------------------------------
* $Log: tcapfunc.h,v $
* Revision 9.1  2005/03/23 12:55:48  cvsadmin
* Begin PR6.5
*
* Revision 8.2  2005/03/21 13:55:12  cvsadmin
* PR6.4.2 Source Propagated to Current
*
* Revision 7.1  2002/08/26 22:10:51  mmiers
* Begin PR6.2
*
* Revision 6.1  2002/02/28 16:14:54  mmiers
* Begin PR7.
*
* Revision 1.1  2001/09/05 20:35:47  mmiers
* Consolidate the NMS libraries.  Only the root library so far.
*
* Revision 5.1  2001/08/16 20:46:37  mmiers
* Start PR6.
*
* Revision 4.1  2001/05/04 16:22:07  mmiers
* Start PR5.
*
* Revision 1.1  2000/08/31 17:28:38  hxing
* Add project for NMS SS7 2.12
* $NoKeywords: $
* 
* 3     11/19/97 10:49a Tedd
* Added extern "C" ifdefs for C++ compiplation.
*
* 2     10/01/97 1:06p Maf
* Added newline to end of file
*
* 1     5/16/97 2:56p Tedd
* Initial Check-in
*-----------------------------------------------------------------------------
******************************************************************************
*****************************************************************************/

/*************************************************************************
**                                                                      **
**                         PROPRIETARY NOTICE                           **
**                                                                      **
**                         Copyright (c) 1997                           **
**                      by Natural MicroSystems, Inc.                   **
**                                                                      **
**  The following is licensed program material and is considered        **
**  proprietary and confidential.  No part of this program may be       **
**  reproduced or used in any form or by any means without the express  **
**  written permission of Natural MicroSystems, Inc.                    **
**                                                                      **
*************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
S16 TXTCAPFUNC TCAPAddComp(U8 *pMessage, TcapComp *pComp, U16 paramLen, U8 *pParamBuf);
S16 TXTCAPFUNC TCAPBindReq(U8 board, S16 suId, S16 spId, U8 ssn);
S16 TXTCAPFUNC TCAPCoordReq(U8 board, S16 spId, U8 aSsn);
S16 TXTCAPFUNC TCAPCoordResp(U8 board, S16 spId, U8 aSsn);
S16 TXTCAPFUNC TCAPGetComp(U8 *pMessage, U8 index, TcapComp *pComp, U16 *pParamLen,
                           U8 *pParamBuf);
S16 TXTCAPFUNC TCAPInitAPI(U8 board, U8 srcEnt, U8 srcInst);
S16 TXTCAPFUNC TCAPInitTrans(U8 *pMessage, TcapTransInfo *pTinfo, TcapDlgSect *pDlgPart,
                             U16 userInfoLen, U8 *pUserInfo);
S16 TXTCAPFUNC TCAPRetrieveMessage(U8 board, U8 *pMessage, TcapRecvInfo *pInfoBlk);
S16 TXTCAPFUNC TCAPStateReq(U8 board, S16 spId, U8 aSsn, U8 status);
OS_HSYNC TXTCAPFUNC TCAPSyncObj(U8 board, S16 *errval);
S16 TXTCAPFUNC TCAPTermAPI(U8 board);
S16 TXTCAPFUNC TCAPTransRqst(U8 board, S16 spId, U8 *pMessage);
S16 TXTCAPFUNC TCAPUnbindReq(U8 board, S16 spId, U8 reason);
#ifdef __cplusplus
}
#endif
