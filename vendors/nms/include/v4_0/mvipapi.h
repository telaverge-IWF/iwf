/*****************************************************************************
 *
 * mvipapi.h - Prototypes for mvip controller task API routines.
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

#ifndef _MVIPAPI_H
#define _MVIPAPI_H

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

    TXXPORT S16 TXMVIPFUNC TxMvipOpen(TXBOARD_T board,
                                        U16 swint);
    TXXPORT void TXMVIPFUNC TxMvipClose(S16 handle);

    TXXPORT S16 TXMVIPFUNC TxConfigClock(S16 handle,
                                           CLOCK_T clock,
                                           SEC8K_T sec8k, NETWORK_T network);

    TXXPORT S16 TXMVIPFUNC TxQueryOutput(S16 handle,
                                           STREAM_T outputStream,
                                           TIMESLOT_T outputTimeslot,
                                           MODE_T * mode,
                                           STREAM_T * inputStream,
                                           TIMESLOT_T * inputTimeslot,
                                           DATA_T * message);

    TXXPORT S16 TXMVIPFUNC TxQuerySwitchCaps(S16 handle, int size,
                                               int *revision,
                                               U16 *domain,
                                               U16 *routing,
                                               U16 *blocking,
                                               U16 *networks,
                                               U16 *channels);

    TXXPORT S16 TXMVIPFUNC TxResetSwitch(S16 handle);

    TXXPORT S16 TXMVIPFUNC TxSampleInput(S16 handle,
                                           STREAM_T inputStream,
                                           TIMESLOT_T inputTimeslot,
                                           DATA_T * inputSample);

    TXXPORT S16 TXMVIPFUNC TxSetOutput(S16 handle,
                                         STREAM_T outputStream,
                                         TIMESLOT_T outputTimeslot,
                                         MODE_T mode,
                                         STREAM_T inputStream,
                                         TIMESLOT_T inputTimeslot,
                                         DATA_T message);

    TXXPORT S16 TXMVIPFUNC TxSetOutputFdx(S16 handle,
                                            STREAM_T outputStream,
                                            TIMESLOT_T outputTimeslot,
                                            MODE_T mode,
                                            STREAM_T inputStream,
                                            TIMESLOT_T inputTimeslot,
                                            DATA_T message);

    TXXPORT S16 TXMVIPFUNC TxTristateSwitch(S16 handle, TRISTATE_T state);

    TXXPORT S16 TXMVIPFUNC TxSwitchStatus(S16 handle,
                                            CLOCK_T * clock,
                                            SEC8K_T * sec8k,
                                            NETWORK_T * network,
                                            TRISTATE_T * state);

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

#endif  /* _MVIPAPI_H */
