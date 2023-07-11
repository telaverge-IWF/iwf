/*
 * File:    mvipapi.h
 *
 * Prototypes for mvip controller task API routines.
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

/*****************************************************************************
 *
 * DD-MMM-YY Who      Tag        Comment
 * ========= ======== ========== =============================================
 * 07-NOV-95 JMD                 Initial Creation
 *
 ****************************************************************************/
#ifndef _MVIPAPI_H_
#define _MVIPAPI_H_

#include "mviptype.h"

/* explicitly define calling convenetions for API functions */
#ifdef WIN32      /* 32 bit Windows OS */
#define     TXMVIPFUNC               WINAPI
#endif /* WIN32 */

#ifdef __OS2__      /*IBM OS/2*/
#ifdef _TX_MVIPAPI_SOURCE_
    /* CPI API source definition */
#define     TXMVIPFUNC              _export _System
#else
    /* CPI API caller's definition */
#define     TXMVIPFUNC              _System
#endif
#endif /* __OS2__ */

#ifdef UNIX       /* UNIX OS */
#define     TXMVIPFUNC
#endif /* UNIX */

#ifdef __cplusplus
extern "C" {
#endif

short TXMVIPFUNC TxMvipOpen( TXBOARD_T board, unsigned short swint  );
void TXMVIPFUNC TxMvipClose( short handle );

short TXMVIPFUNC TxConfigClock( short handle,
                     CLOCK_T clock,
                     SEC8K_T sec8k,
                     NETWORK_T network );

short TXMVIPFUNC TxQueryOutput( short        handle,
                     STREAM_T     outputStream,
                     TIMESLOT_T   outputTimeslot,
                     MODE_T       *mode,
                     STREAM_T     *inputStream,
                     TIMESLOT_T   *inputTimeslot,
                     DATA_T       *message );

short TXMVIPFUNC TxQuerySwitchCaps( short handle, int size, int *revision,
                         unsigned short *domain,
                         unsigned short *routing,
                         unsigned short *blocking,
                         unsigned short *networks,
                         unsigned short *channels );

short TXMVIPFUNC TxResetSwitch( short handle );

short TXMVIPFUNC TxSampleInput( short      handle,
                     STREAM_T   inputStream,
                     TIMESLOT_T inputTimeslot,
					 DATA_T     *inputSample );

short TXMVIPFUNC TxSetOutput( short      handle,
                   STREAM_T   outputStream,
                   TIMESLOT_T outputTimeslot,
                   MODE_T     mode,
                   STREAM_T   inputStream,
                   TIMESLOT_T inputTimeslot,
				   DATA_T     message );

short TXMVIPFUNC TxSetOutputFdx( short      handle,
                      STREAM_T   outputStream,
                      TIMESLOT_T outputTimeslot,
                      MODE_T     mode,
                      STREAM_T   inputStream,
                      TIMESLOT_T inputTimeslot,
                      DATA_T     message );

short TXMVIPFUNC TxTristateSwitch( short handle, TRISTATE_T state );

short TXMVIPFUNC TxSwitchStatus( short     handle,
					  CLOCK_T	*clock,
					  SEC8K_T	*sec8k,
					  NETWORK_T	*network,
					  TRISTATE_T *state );

#ifdef __cplusplus
}
#endif

#endif


