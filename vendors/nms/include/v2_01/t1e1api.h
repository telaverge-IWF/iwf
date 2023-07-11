/*
 * File:    t1e1api.h
 *
 * Prototypes for t1/e1 controller task API routines.
 *
 */
/**************************************************************************
 **
 **			   PROPRIETARY NOTICE
 **
 **			   Copyright (c) 1995
 **			    By TEKnique, Inc.
 **
 **
 **  The following is licensed program material and is considered
 **  proprietary and confidential.  No part of this program may be
 **  reproduced or used in any form or by any means without the express
 **  written permission of TEKnique, Inc.
 **
 *************************************************************************/
#ifndef _T1E1API_H_
#define _T1E1API_H_

#include "t1e1type.h"

/* explicitly define calling convenetions for API functions */
#ifdef WIN32      /* 32 bit Windows OS */
#define     TXT1E1FUNC               WINAPI
#endif /* WIN32 */

#ifdef __OS2__      /*IBM OS/2: now a DLL*/
#ifdef _TX_T1E1API_SOURCE_
    /* CPI API source definition */
#define     TXT1E1FUNC               _export _System
#else
    /* CPI API caller's definition */
#define     TXT1E1FUNC               _System
#endif
#endif /* __OS2__ */

#ifdef UNIX       /* UNIX OS */
#define     TXT1E1FUNC
#endif /* UNIX */

#ifdef __cplusplus
extern "C" {
#endif

short TXT1E1FUNC TxT1E1Open( TXBOARD_T board, unsigned short swint );

void TXT1E1FUNC TxT1E1Close( short handle );

short TXT1E1FUNC TxT1E1ConfigCarrier( short handle, unsigned char carrier,
						   TxT1E1Config	*pConfig );

short TXT1E1FUNC TxT1E1CarrierStatus( short handle, unsigned char carrier,
						   unsigned char flags,
						   unsigned char *pAlarmState,
                     unsigned char *pLastAlmState,
                     unsigned char *pSyncState,
						   TxT1E1Config	*pConfig,
						   unsigned short *pCurrInterval,
						   TxT1E1Stats *pCurrStats,
						   unsigned short *pValidInterval,
						   TxT1E1Stats *pSummaryStats,
						   unsigned short *pPvcs,
						   unsigned short *pLvcs,
                     unsigned short *pSlips,
                     unsigned short *pEbits );

short TXT1E1FUNC TxT1E1PerfReport( short handle, unsigned char carrier,
						unsigned char flags,
						unsigned short *pCurrInterval,
						TxT1E1Stats *pCurrStats,
						unsigned short *pValidInterval,
						TxT1E1Stats *pIntervalStats,
						TxT1E1Stats *pSummaryStats,
						unsigned short *pPvcs,
						unsigned short *pLvcs,
                  unsigned short *pSlips,
                  unsigned short *pEbits );

short TXT1E1FUNC TxT1E1CtrlCarrier( short handle, unsigned char carrier,
						 unsigned char loopback,
						 unsigned char alarmState );

short TXT1E1FUNC TxT1E1ConditionChan( short handle, unsigned char carrier,
						   unsigned char channel,
						   unsigned char control,
						   unsigned char pattern );

short TXT1E1FUNC TxT1E1ConfigChan( short handle, unsigned char carrier,
						unsigned char channel,
						unsigned char transparent );

short TXT1E1FUNC TxT1E1ChannelStatus( short handle, unsigned char carrier,
						   unsigned long *pTransparent,
						   unsigned long *pRxABCD,
						   unsigned long *pTxABCD );

short TXT1E1FUNC TxT1E1SuperviseCarrier( short handle, unsigned char carrier,
							  unsigned char notifMask );


#ifdef __cplusplus
}
#endif

#endif


