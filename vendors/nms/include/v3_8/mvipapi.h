
/*
 * File:    mvipapi.h
 *
 * Prototypes for mvip controller task API routines.
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

#ifdef TXXPORT
#       undef   TXXPORT
#endif

/* explicitly define calling convenetions for API functions */
#ifdef WIN32

#ifdef _TX_MVIPAPI_SOURCE_          /* Library build. */
#       define  TXXPORT         __declspec( dllexport )
#       define  TXMVIPFUNC      WINAPI
#else   /* Library use. */
#       define  TXXPORT
#       define  TXMVIPFUNC      WINAPI

#endif /*_TX_MVIPAPI_SOURCE */

#endif  /* WIN32 */

#ifdef UNIX
#       define  TXXPORT
#       define  TXMVIPFUNC
#endif  /* UNIX */

#ifdef __cplusplus
extern          "C"
{
#endif

    TXXPORT short TXMVIPFUNC TxMvipOpen(TXBOARD_T board,
                                        unsigned short swint);
    TXXPORT void TXMVIPFUNC TxMvipClose(short handle);

    TXXPORT short TXMVIPFUNC TxConfigClock(short handle,
                                           CLOCK_T clock,
                                           SEC8K_T sec8k, NETWORK_T network);

    TXXPORT short TXMVIPFUNC TxQueryOutput(short handle,
                                           STREAM_T outputStream,
                                           TIMESLOT_T outputTimeslot,
                                           MODE_T * mode,
                                           STREAM_T * inputStream,
                                           TIMESLOT_T * inputTimeslot,
                                           DATA_T * message);

    TXXPORT short TXMVIPFUNC TxQuerySwitchCaps(short handle, int size,
                                               int *revision,
                                               unsigned short *domain,
                                               unsigned short *routing,
                                               unsigned short *blocking,
                                               unsigned short *networks,
                                               unsigned short *channels);

    TXXPORT short TXMVIPFUNC TxResetSwitch(short handle);

    TXXPORT short TXMVIPFUNC TxSampleInput(short handle,
                                           STREAM_T inputStream,
                                           TIMESLOT_T inputTimeslot,
                                           DATA_T * inputSample);

    TXXPORT short TXMVIPFUNC TxSetOutput(short handle,
                                         STREAM_T outputStream,
                                         TIMESLOT_T outputTimeslot,
                                         MODE_T mode,
                                         STREAM_T inputStream,
                                         TIMESLOT_T inputTimeslot,
                                         DATA_T message);

    TXXPORT short TXMVIPFUNC TxSetOutputFdx(short handle,
                                            STREAM_T outputStream,
                                            TIMESLOT_T outputTimeslot,
                                            MODE_T mode,
                                            STREAM_T inputStream,
                                            TIMESLOT_T inputTimeslot,
                                            DATA_T message);

    TXXPORT short TXMVIPFUNC TxTristateSwitch(short handle, TRISTATE_T state);

    TXXPORT short TXMVIPFUNC TxSwitchStatus(short handle,
                                            CLOCK_T * clock,
                                            SEC8K_T * sec8k,
                                            NETWORK_T * network,
                                            TRISTATE_T * state);

#ifdef __cplusplus
}
#endif

#endif
