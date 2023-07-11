/*****************************************************************************
 *
 * dpruser.h - USER ACCESSABLE Dual Port Ram definitions file
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

#ifndef _DPRUSER_H
#define _DPRUSER_H

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

#include <txnuser.h>                /* primitive field type definitions */
#include <dpriface.h>

/* ----- DPR Packet Header Structure   <D0> */
typedef struct __dprh
{
    U8            srcch;      /* Source channel number */
    U8            srcbd;      /* Source board number (0 = PC) */
    U8            dstch;      /* Destination channel number */
    U8            dstbd;      /* Destination board # (0 = PC) */
    U16           len;        /* Len of message body (incl hdr) */

#ifdef NMSTX_ALIGN_32
    U8            pad_end[2]; /* pad to 32-bit aligned structure size */
#endif
}
DPRH;

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

#endif /* _DPRUSER_H */
