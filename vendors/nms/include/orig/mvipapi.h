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

#ifdef __cplusplus
extern "C" {
#endif

short TxMvipOpen( TXBOARD_T board, unsigned short swint  );
void TxMvipClose( short handle );

short TxConfigClock( short handle,
                     CLOCK_T clock,
                     SEC8K_T sec8k,
                     NETWORK_T network );

short TxQueryOutput( short        handle,
                     STREAM_T     outputStream,
                     TIMESLOT_T   outputTimeslot,
                     MODE_T       *mode,
                     STREAM_T     *inputStream,
                     TIMESLOT_T   *inputTimeslot,
                     DATA_T       *message );

short TxQuerySwitchCaps( short handle, int size, int *revision,
                         unsigned short *domain,
                         unsigned short *routing,
                         unsigned short *blocking,
                         unsigned short *networks,
                         unsigned short *channels );

short TxResetSwitch( short handle );

short TxSampleInput( short      handle,
                     STREAM_T   inputStream,
                     TIMESLOT_T inputTimeslot,
					 DATA_T     *inputSample );

short TxSetOutput( short      handle,
                   STREAM_T   outputStream,
                   TIMESLOT_T outputTimeslot,
                   MODE_T     mode,
                   STREAM_T   inputStream,
                   TIMESLOT_T inputTimeslot,
				   DATA_T     message );

short TxSetOutputFdx( short      handle,
                      STREAM_T   outputStream,
                      TIMESLOT_T outputTimeslot,
                      MODE_T     mode,
                      STREAM_T   inputStream,
                      TIMESLOT_T inputTimeslot,
                      DATA_T     message );

short TxTristateSwitch( short handle, TRISTATE_T state );

short TxSwitchStatus( short		handle,
					  CLOCK_T	*clock,
					  SEC8K_T	*sec8k,
					  NETWORK_T	*network,
					  TRISTATE_T *state );

#ifdef __cplusplus
}
#endif                  

#endif
