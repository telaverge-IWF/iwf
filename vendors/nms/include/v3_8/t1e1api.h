
/*
 * File:    t1e1api.h
 *
 * Prototypes for t1/e1 controller task API routines.
 *
 */

/**************************************************************************
 **
 **                        PROPRIETARY NOTICE
 **
 **                        Copyright (c) 1995-2001
 **                         By NMS Communications, Inc.
 **
 **
 **  The following is licensed program material and is considered
 **  proprietary and confidential.  No part of this program may be
 **  reproduced or used in any form or by any means without the express
 **  written permission of NMS Communications, Inc.
 **
 *************************************************************************/
#ifndef _T1E1API_H_
#define _T1E1API_H_

#include "t1e1type.h"

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

    TXXPORT short TXT1E1FUNC TxT1E1Open(TXBOARD_T board,
                                        unsigned short swint);

    TXXPORT void TXT1E1FUNC TxT1E1Close(short handle);

    TXXPORT short TXT1E1FUNC TxT1E1ConfigCarrier(short handle,
                                                 unsigned char carrier,
                                                 TxT1E1Config * pConfig);

    TXXPORT short TXT1E1FUNC TxT1E1CarrierStatus(short handle,
                                                 unsigned char carrier,
                                                 unsigned char flags,
                                                 unsigned char *pAlarmState,
                                                 unsigned char *pLastAlmState,
                                                 unsigned char *pSyncState,
                                                 TxT1E1Config * pConfig,
                                                 unsigned short
                                                 *pCurrInterval,
                                                 TxT1E1Stats * pCurrStats,
                                                 unsigned short
                                                 *pValidInterval,
                                                 TxT1E1Stats * pSummaryStats,
                                                 unsigned short *pPvcs,
                                                 unsigned short *pLvcs,
                                                 unsigned short *pSlips,
                                                 unsigned short *pEbits);

    TXXPORT short TXT1E1FUNC TxT1E1PerfReport(short handle,
                                              unsigned char carrier,
                                              unsigned char flags,
                                              unsigned short *pCurrInterval,
                                              TxT1E1Stats * pCurrStats,
                                              unsigned short *pValidInterval,
                                              TxT1E1Stats * pIntervalStats,
                                              TxT1E1Stats * pSummaryStats,
                                              unsigned short *pPvcs,
                                              unsigned short *pLvcs,
                                              unsigned short *pSlips,
                                              unsigned short *pEbits);

    TXXPORT short TXT1E1FUNC TxT1E1CtrlCarrier(short handle,
                                               unsigned char carrier,
                                               unsigned char loopback,
                                               unsigned char alarmState);

    TXXPORT short TXT1E1FUNC TxT1E1ConditionChan(short handle,
                                                 unsigned char carrier,
                                                 unsigned char channel,
                                                 unsigned char control,
                                                 unsigned char pattern);

    TXXPORT short TXT1E1FUNC TxT1E1ConfigChan(short handle,
                                              unsigned char carrier,
                                              unsigned char channel,
                                              unsigned char transparent);

    TXXPORT short TXT1E1FUNC TxT1E1ChannelStatus(short handle,
                                                 unsigned char carrier,
                                                 unsigned long *pTransparent,
                                                 unsigned long *pRxABCD,
                                                 unsigned long *pTxABCD);

    TXXPORT short TXT1E1FUNC TxT1E1SuperviseCarrier(short handle,
                                                    unsigned char carrier,
                                                    unsigned char notifMask);


#ifdef __cplusplus
}
#endif

#endif
