/*****************************************************************************
 *
 * txswiapi.h - TX SWI API
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

#ifndef _TXSWIAPI_H
#define _TXSWIAPI_H

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

/* ----- dependent includes ----- */
#include <txcpi.h>
#include <txnuser.h>
#include <swidef.h>
#include <txswi.h>

#ifdef TXXPORT
#       undef   TXXPORT
#endif

/* explicitly define calling convenetions for API functions */
#ifdef WIN32

#ifdef _TX_SWIAPI_SOURCE_          /* Library build. */
#       define  TXXPORT         __declspec( dllexport )
#       define  TXSWIFUNC       WINAPI
#else   /* Library use. */
#       define  TXXPORT
#       define  TXSWIFUNC       WINAPI

#endif /*_TX_SWIAPI_SOURCE */

#endif  /* WIN32 */

#ifdef UNIX
#       define  TXXPORT
#       define  TXSWIFUNC
#endif  /* UNIX */

#ifdef __cplusplus
extern          "C"
{
#endif

/* ----- Request message creation functions */
TXXPORT void TXSWIFUNC txswiAddress             ( CPIPKT *pkt, U32 req_size, U16 board, U16 host_chan );

TXXPORT U32  TXSWIFUNC txswiGetSwitchCaps       ( CPIPKT *pkt );
TXXPORT U32  TXSWIFUNC txswiConfigBoardClock    ( CPIPKT *pkt,
                                                  SWI_CLOCK_ARGS *args );
TXXPORT U32  TXSWIFUNC txswiConfigNetrefClock   ( CPIPKT *pkt,
                                                  SWI_NETREF_CLOCK_ARGS *args );
TXXPORT U32  TXSWIFUNC txswiConfigSec8KClock    ( CPIPKT *pkt,
                                                  U32 source, U32 network );
TXXPORT U32  TXSWIFUNC txswiGetBoardClock       ( CPIPKT *pkt );
TXXPORT U32  TXSWIFUNC txswiGetBoardInfo        ( CPIPKT *pkt );
TXXPORT U32  TXSWIFUNC txswiEnableSwitch        ( CPIPKT *pkt );
TXXPORT U32  TXSWIFUNC txswiDisableSwitch       ( CPIPKT *pkt );
TXXPORT U32  TXSWIFUNC txswiResetSwitch         ( CPIPKT *pkt );
TXXPORT U32  TXSWIFUNC txswiXGetStatus          ( CPIPKT *pkt );
TXXPORT U32  TXSWIFUNC txswiMakeConnection      ( CPIPKT *pkt,
                                                  SWI_TERMINUS input[],
                                                  SWI_TERMINUS output[],
                                                  unsigned count );
TXXPORT U32  TXSWIFUNC txswiSendPattern         ( CPIPKT *pkt,
                                                  U8 pattern[],
                                                  SWI_TERMINUS output[],
                                                  unsigned count );
TXXPORT U32  TXSWIFUNC txswiDisableOutput       ( CPIPKT *pkt,
                                                  SWI_TERMINUS output[],
                                                  unsigned count );
TXXPORT U32  TXSWIFUNC txswiSampleInput         ( CPIPKT *pkt,
                                                  SWI_TERMINUS input[],
                                                  unsigned count );
TXXPORT U32  TXSWIFUNC txswiGetOutputState      ( CPIPKT *pkt,
                                                  SWI_TERMINUS output[],
                                                  unsigned count );
TXXPORT U32  TXSWIFUNC txswiGetTimingReference  ( CPIPKT *pkt,
                                                  U32 referencesource,
                                                  U32 network );

TXXPORT U32  TXSWIFUNC txswiConfigLocalStream   ( CPIPKT *pkt,
                                                  SWI_LOCALSTREAM_ARGS *args,
                                                  void *buffer, unsigned size );
TXXPORT U32  TXSWIFUNC txswiConfigLocalTimeslot ( CPIPKT *pkt,
                                                  SWI_LOCALTIMESLOT_ARGS *args,
                                                  void *buffer, unsigned size );
TXXPORT U32  TXSWIFUNC txswiGetLocalStreamInfo  ( CPIPKT *pkt,
                                                  SWI_LOCALSTREAM_ARGS *args,
                                                  void *buffer, unsigned size );

/* ----- Reply (Response or Notif) handling functions */
TXXPORT TXSWI_MSG * TXSWIFUNC txswiReply      ( CPIPKT *pkt, S16 len, U32 *ccode );

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

#endif  /* _TXSWIAPI_H */
