/*****************************************************************************
 *
 * t1e1api.h - Prototypes for t1/e1 controller task API routines.
 *
 *****************************************************************************/

/*****************************************************************************
 *
 *                         PROPRIETARY NOTICE
 *
 *                      Copyright (c) 1988-2003
 *                       by NMS Communications.
 *
 *  The following is licensed program material and is considered
 *  proprietary and confidential.  No part of this program may be
 *  reproduced or used in any form or by any means without the express
 *  written permission of NMS Communications.
 *
 *****************************************************************************/

#ifndef _T1E1API_H
#define _T1E1API_H

/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
 * PACKING: pack on 1-byte boundaries
 *xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
#ifdef UNIX
#pragma pack(1)
#endif
#ifdef __HIGHC__
#pragma Push_align_members(1)
#endif
#ifdef _WINNT
#pragma pack(1)
#endif

#include "t1e1type.h"
#include <txnuser.h>

#ifdef TXXPORT
#       undef   TXXPORT
#endif

/* explicitly define calling convenetions for API functions */
#ifdef WIN32

#ifdef _TX_T1E1API_SOURCE_          /* Library build. */
#       define  TXXPORT         __declspec( dllexport )
#       define  TXT1E1FUNC      WINAPI
#else   /* Library use. */
#       define  TXXPORT
#       define  TXT1E1FUNC      WINAPI

#endif /*_TX_T1E1API_SOURCE_*/

#endif  /* WIN32 */

#ifdef UNIX
#       define  TXXPORT
#       define  TXT1E1FUNC
#endif  /* UNIX */

#ifdef __cplusplus
extern          "C"
{
#endif

    TXXPORT S16 TXT1E1FUNC TxT1E1Open(TXBOARD_T board,
                                        U16 swint);

    TXXPORT void TXT1E1FUNC TxT1E1Close(S16 handle);

    TXXPORT S16 TXT1E1FUNC TxT1E1ConfigCarrier(S16 handle,
                                                 U8 carrier,
                                                 TxT1E1Config * pConfig);

    TXXPORT S16 TXT1E1FUNC TxT1E1CarrierStatus(S16 handle,
                                                 U8 carrier,
                                                 U8 flags,
                                                 U8 *pAlarmState,
                                                 U8 *pLastAlmState,
                                                 U8 *pSyncState,
                                                 TxT1E1Config * pConfig,
                                                 U16
                                                 *pCurrInterval,
                                                 TxT1E1Stats * pCurrStats,
                                                 U16
                                                 *pValidInterval,
                                                 TxT1E1Stats * pSummaryStats,
                                                 U16 *pPvcs,
                                                 U16 *pLvcs,
                                                 U16 *pSlips,
                                                 U16 *pEbits);

    TXXPORT S16 TXT1E1FUNC TxT1E1PerfReport(S16 handle,
                                              U8 carrier,
                                              U8 flags,
                                              U16 *pCurrInterval,
                                              TxT1E1Stats * pCurrStats,
                                              U16 *pValidInterval,
                                              TxT1E1Stats * pIntervalStats,
                                              TxT1E1Stats * pSummaryStats,
                                              U16 *pPvcs,
                                              U16 *pLvcs,
                                              U16 *pSlips,
                                              U16 *pEbits);

    TXXPORT S16 TXT1E1FUNC TxT1E1CtrlCarrier(S16 handle,
                                               U8 carrier,
                                               U8 loopback,
                                               U8 alarmState);

    TXXPORT S16 TXT1E1FUNC TxT1E1ConditionChan(S16 handle,
                                                 U8 carrier,
                                                 U8 channel,
                                                 U8 control,
                                                 U8 pattern);

    TXXPORT S16 TXT1E1FUNC TxT1E1ConfigChan(S16 handle,
                                              U8 carrier,
                                              U8 channel,
                                              U8 transparent);

    TXXPORT S16 TXT1E1FUNC TxT1E1ChannelStatus(S16 handle,
                                                 U8 carrier,
                                                 U32 *pTransparent,
                                                 U32 *pRxABCD,
                                                 U32 *pTxABCD);

    TXXPORT S16 TXT1E1FUNC TxT1E1SuperviseCarrier(S16 handle,
                                                    U8 carrier,
                                                    U8 notifMask);


#ifdef __cplusplus
}
#endif

/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
 * PACKING: return to default
 *xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
#ifdef UNIX
#pragma pack()
#endif
#ifdef _WINNT
#pragma pack()
#endif
#ifdef __HIGHC__
#pragma Pop_align_members
#endif

#endif  /* _T1E1API_H */
