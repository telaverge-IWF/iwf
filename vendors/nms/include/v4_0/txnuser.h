/*****************************************************************************
 *
 * txnuser.h - TXn000 Base User Interface File
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

#ifndef _TXNUSER_H
#define _TXNUSER_H

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

/* ----- General 'C' Constants */
#ifndef NULL
#define NULL    (void *)0
#endif

/* ----- define basic types ----- */
#ifdef _XCODE_

#ifndef DWORD
#define DWORD unsigned long
#endif

#ifndef WORD
#define WORD unsigned short
#endif

#ifndef BYTE
#define BYTE unsigned char
#endif

#ifndef INT32
#define INT32 long
#endif

#ifndef INT16
#define INT16 short
#endif

#else  /* _XCODE_ */

#ifdef __HIGHC__

#ifndef DWORD
#define DWORD unsigned long
#endif

#ifndef WORD
#define WORD unsigned short
#endif

#ifndef BYTE
#define BYTE unsigned char
#endif

#ifndef INT32
#define INT32 long
#endif

#ifndef INT16
#define INT16 short
#endif

#else

#include <nmstypes.h>           /* primitive field type definitions */

#endif /* _HIGHC_ */
#endif /* _XCODE_ */

/*===========================================================================
 * Base Variable Types
 *
 * The following base variable types are used to build all other structure
 * definitions used to access TXn000 APIs.
 *===========================================================================*/
#ifndef U32
#define U32 DWORD
#endif

#ifndef U16
#define U16 WORD
#endif

#ifndef U8
#define U8 BYTE
#endif

#ifndef S32
#define S32 INT32
#endif

#ifndef S16
#define S16 INT16
#endif

#ifndef S8
#define S8 char
#endif

/*===========================================================================
 * Structure Alignment Control
 *
 * NMSTX_ALIGN_32 - structures should use the following alignment rules:
 *                  * shorts aligned to even 16-bit boundary
 *                  * longs aligned to even 32-bit boundary
 *                  * structures always begin on even 32-bit boundary
 *                    (structures padded to even 32-bit size to aid alignment)
 *
 *===========================================================================*/

#ifdef __sparc
#define NMSTX_ALIGN_32
#endif

/*===========================================================================
 * Short / Long Byte Ordering Control
 *
 * TX board is BIG ENDIAN (most significant byte stored in lowest byte address)
 *
 * HOSTS can be BIG ENDIAN or LITTLE ENDIAN
 *
 * NMSTX_HOST_BIGENDIAN - the host uses a BIG ENDIAN based processor
 *
 *===========================================================================*/

#ifdef __sparc
#define NMSTX_HOST_BIGENDIAN
#endif

/*****************************************************************************
 * The following definitions allow a short or long to be converted from
 * one type of processor's native storage format to another.
 *
 * NOTE:  The NMSTX_SWABLONG and NMSTX_SWABSHORT definitions should NOT be used
 *        directly.  Use the macros derived from these SWAB macros to ensure
 *        proper host processor independence.
 *****************************************************************************/

#define NMSTX_SWABLONG(longval) (\
(DWORD) (\
   ( ( ((DWORD)(longval)) & 0x000000ff) << 24) | \
   ( ( ((DWORD)(longval)) & 0x0000ff00) << 8) | \
   ( ( ((DWORD)(longval)) & 0x00ff0000) >> 8) | \
   ( ( ((DWORD)(longval)) & 0xff000000) >> 24) \
       ) \
)

#define NMSTX_SWABSHORT(shortval) (\
(WORD) (\
   (( ((WORD)(shortval)) & 0x00ff) << 8) | ( (((WORD)(shortval)) & 0xff00) >> 8) \
        )\
)

/*****************************************************************************
 * The following definitions are derived from the platform control
 * definitions above (NMSTX_xxx).
 *
 * These macros allow developers to create host-independent code that can
 * be used to access TX interface structures regardless of the type of
 * platform that the code is executing on.
 *
 * NOTE:  Modifications / extensions to the following macros should be made
 *        with care.  These macros are used by applications, APIs, and drivers.
 *
 * Use CPTOH / HTOCP macros when converting shorts and longs used between
 * the host and tasks running on the TX board (or CP).
 *
 * Use LE2H / H2LE macros when accessing certain TX hardware interfaces
 * (such as the DEC 21554 PCI bridge) that use LITTLE ENDIAN storage format.
 * Use of LE2H / H2LE is usually restricted to driver level accesses.
 *
 *****************************************************************************/
#ifdef NMSTX_HOST_BIGENDIAN

/* ----- BIG ENDIAN host ----- */
#define NMSTX_CPTOH_S(x) ((U16)(x))
#define NMSTX_CPTOH_L(x) ((U32)(x))
#define NMSTX_HTOCP_S(x) ((U16)(x))
#define NMSTX_HTOCP_L(x) ((U32)(x))

#define NMSTX_LE2H_S(x) NMSTX_SWABSHORT(x)
#define NMSTX_LE2H_L(x) NMSTX_SWABLONG(x)
#define NMSTX_H2LE_S(x) NMSTX_SWABSHORT(x)
#define NMSTX_H2LE_L(x) NMSTX_SWABLONG(x)

#else

/* ----- LITTLE ENDIAN host ----- */

#define NMSTX_CPTOH_S(x) NMSTX_SWABSHORT(x)
#define NMSTX_CPTOH_L(x) NMSTX_SWABLONG(x)
#define NMSTX_HTOCP_S(x) NMSTX_SWABSHORT(x)
#define NMSTX_HTOCP_L(x) NMSTX_SWABLONG(x)

#define NMSTX_LE2H_S(x) ((U16)(x))
#define NMSTX_LE2H_L(x) ((U32)(x))
#define NMSTX_H2LE_S(x) ((U16)(x))
#define NMSTX_H2LE_L(x) ((U32)(x))

#endif  /* NMSTX_HOST_BIGENDIAN */

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

#endif  /* _TXNUSER_H */
