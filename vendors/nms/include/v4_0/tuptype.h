/**************************************************************************
 **
 **                         PROPRIETARY NOTICE
 **
 **                         Copyright (c) 1997
 **                     By Natural MicroSystems, Inc.
 **
 **
 **  The following is licensed program material and is considered
 **  proprietary and confidential.  No part of this program may be
 **  reproduced or used in any form or by any means without the express
 **  written permission of Natural MicroSystems, Inc.
 **
 **  This product also contains software that is protected by the
 **  following copyrights.
 **
 **        (c) Copyright 1989-1995, Trillium Digital Systems, Inc.
 *************************************************************************/


/* File:    TUPtype.h
 *
 * Basic data types needed by TUP API.
 */
#ifndef _TUPTYPE_H_
#define _TUPTYPE_H_

#include "txnuser.h"

#ifndef TUP_TASK
#include "ss7type.h"
#endif
/* define the calling conventions for the API functions for various
 * operating systems - NOTE: API callers should never define the
 * preprocessor constant "_TX_TUPAPI_SOURCE_"; this is only for use
 * by the TUP API source code itself.
 */

/* OS2: TUP API is a DLL */
#ifdef __OS2__
#ifdef _TX_TUPAPI_SOURCE_
    /* TUP API source definition */
#define     TXTUPAPIFUNC               extern _export _syscall
#else
    /* TUP API caller's definition */
#define     TXTUPAPIFUNC               _syscall
#endif  /* _TX_TUPAPI_SOURCE_ */

/* WIN32: TUP API is a DLL */
#elif  WIN32                            /* WIN32 */
#ifdef _TX_TUPAPI_SOURCE_
    /* TUP API source definition */
#define     TXTUPAPIFUNC               __declspec( dllexport ) WINAPI
#else
    /* TUP API caller's definition */
#define     TXTUPAPIFUNC               WINAPI
#endif  /* _TX_TUPAPI_SOURCE_ */

/* all others: statically linked library */
#else
#define     TXTUPAPIFUNC
#endif

/* Turn on structure packing for UNIX env. */
#ifndef TUP_TASK
#ifdef UNIX
#pragma pack(1)
#endif
#endif

/* Other Data Types */

#ifndef Bool
#define Bool unsigned char
#endif

#ifndef Void
#define Void void
#endif


/*#ifndef TUP_CFG*/
/* common structures */

typedef U32   CirIdx;             /* circuit Index - Added to make API parameters more descriptive*/

typedef U32 TupInstId;            /* instance id */

typedef U8 TupEnt;                   /* entity */

typedef U8 TupInst;                  /* instance */

typedef S16 TupSuId;                 /* service user sap id */

typedef S16 TupSpId;                 /* service provider sap id */



#define PUBLIC

/* structure passed back from TUPRecvMessage to identify type, etc., of
 * indication/confirmation received from TUP layer.
 */
typedef struct _tuprcvInfoBlk {
    U8          indType;            /* indication/confirmation type */
    U8          evntType;           /* event type for status & connection
                                       status indications only */
    TupSuId     suId;               /* service user (SAP) id - all */
    TupInstId   suInstId;           /* caller's reference number - all */
    TupInstId   spInstId;           /* TUP's reference number - all */
    CirIdx      circuit;            /* circuit index - all */
} TupRcvInfoBlk;


/* return codes */

#define TUP_SUCCESS     0       /* request successful */
#define TUP_NO_MSG      1       /* no message waiting */
#define TUP_NOT_BOUND   -1      /* TUP primitive called before bind */
#define TUP_UNKEVENT    -2      /* unknown event type passed to primitive */
#define TUP_OSERROR     -3      /* OS-specific error */
#define TUP_RESOURCES   -4      /* unable to allocate resources (buffer) */
#define TUP_BADMSG      -5      /* unrecognized msg rec'd from TUP */
#define TUP_INVBOARD    -6      /* Board number invalid */
#define TUP_MISS_PARAM  -7      /* There is a parameter missing from the request */

#define TUP_ENT     0x1D                /* Telephone User Part Prorocol Handler     */
#define MTP3_ENT    0x15                /* Message Transfer Part Layer 3            */

#ifndef TUP_TASK
#ifdef UNIX
#pragma pack()
#endif
#endif

#endif
