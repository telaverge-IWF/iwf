/*****************************************************************************
 *
 * mviptype.h - Data type declarations and constant values for MVIP API
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
#ifndef _MVIPTYPE_H
#define _MVIPTYPE_H

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
#include <txnuser.h>

/******************************************************************************
* For board selection
******************************************************************************/
#ifndef TXBOARD_DEF
#define  TXBOARD_DEF 1
typedef U8 TXBOARD_T;    /* board numbers 1..8 */
#endif

/******************************************************************************
* FOR network interface selection
******************************************************************************/
#ifndef NETWORK_DEF
#define NETWORK_DEF 1
typedef U16 NETWORK_T;
#endif

/******************************************************************************
* MVIP Config Clock Defines
******************************************************************************/
typedef U8 CLOCK_T;

#define CLOCK_REF_MVIP          0
#define CLOCK_REF_SEC8K         1
#define CLOCK_REF_OSC           2
#define CLOCK_REF_NET           3
#define CLOCK_REF_OSC_DA        4      /* Drive H.100 A Clock */
#define CLOCK_REF_OSC_DB        5      /* Drive H.100 B Clock */
#define CLOCK_REF_MVIP_SA       6      /* Source from H.100 A Clock */
#define CLOCK_REF_MVIP_SB       7      /* Source from H.100 B Clock */
#define CLOCK_REF_NET_DA        8      /* Drive H.100 A Clock */
#define CLOCK_REF_NET_DB        9      /* Drive H.100 B Clock */

typedef U8 SEC8K_T;

#define SEC8K_NOT_DRIVEN        1
#define SEC8K_DRIVEN_BY_OSC     2
#define SEC8K_DRIVEN_BY_NET     3

/******************************************************************************
* defines for network interface selection (T1/E1-A or T1/E1-B)
******************************************************************************/
#ifndef TXBOARD_DEF
#define  TXBOARD_DEF 1
typedef U8 TXBOARD_T;    /* board numbers 1..8 */
#endif

#ifndef NET_T1A                     /* same as T1/E1 API NET_T1A */
#define NET_T1A               1
#endif
#ifndef NET_T1B                     /* same as T1/E1 API NET_T1B */
#define NET_T1B               2
#endif
#ifndef NET_T1C                     /* same as T1/E1 API NET_T1C */
#define NET_T1C               3
#endif
#ifndef NET_T1D                     /* same as T1/E1 API NET_T1D */
#define NET_T1D               4
#endif
#ifndef NET_T1E                     /* same as T1/E1 API NET_T1E */
#define NET_T1E               5
#endif
#ifndef NET_T1F                     /* same as T1/E1 API NET_T1F */
#define NET_T1F               6
#endif
#ifndef NET_T1G                     /* same as T1/E1 API NET_T1G */
#define NET_T1G               7
#endif
#ifndef NET_T1H                     /* same as T1/E1 API NET_T1H */
#define NET_T1H               8
#endif

/******************************************************************************
* types for streams, timeslots and actual data samples
******************************************************************************/
typedef U16 STREAM_T;
typedef U16 TIMESLOT_T;
typedef U8 DATA_T;   /* 8 bit data samples/patterns */

/******************************************************************************
* MVIP Tristate_Switch state values
******************************************************************************/
typedef U16 TRISTATE_T;

#define ENABLE_OUTPUT		0
#define TRISTATE_OUTPUT		1

/******************************************************************************
* MVIP Channel_connect Defines
******************************************************************************/
typedef U8 MODE_T;

#define DISABLE_MODE		0
#define PATTERN_MODE		1
#define CONNECT_MODE		2

/******************************************************************************
* MVIP Error Codes
******************************************************************************/
#define SUCCESS                         0
#define MVIP_INVALID_COMMAND            200
#define MVIP_DLL_INVALID_DEVICE         201
#define MVIP_DEVICE_ERROR               202
#define MVIP_NO_RESOURCES               204
#define MVIP_INVALID_STREAM             210
#define MVIP_INVALID_TIMESLOT           211
#define MVIP_MISSING_PARAMETERS         212
#define MVIP_INVALID_CLOCK_PARM         213
#define MVIP_INVALID_MODE               216
#define MVIP_INVALID_MINOR_SWITCH       217
#define MVIP_INVALID_PARAMETER          218
#define MVIP_NO_PATH                    220
#define MVIP_SWITCH_VERIFY_ERROR        221
#define MVIP_INTERNAL_CONFLICT          222
#define MVIP_CONNECTION_NOT_SUPPORTED   223
#define MVIP_INVALID_LENGTH             224

/* driver/API related errors */
#define MVIP_INVALID_HANDLE             -1
#define MVIP_NO_DRIVER					-2
#define MVIP_OPEN_FAIL					-3
#define MVIP_BAD_BOARD					-4
#define	MVIP_SEND_ERROR					-5
#define	MVIP_NO_RESPONSE				-6
#define MVIP_RECV_ERROR					-7


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

#endif /* _MVIPTYPE_H */
