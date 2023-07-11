/**************************************************************************
 **
 **			   				PROPRIETARY NOTICE
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
 **	 This product also contains software that is protected by the
 **  following copyrights.
 **
 **		(c) Copyright 1989-1995, Trillium Digital Systems, Inc.
 *************************************************************************/


/* File:	isuptype.h
 *
 * Basic data types needed by ISUP API.
 */
#ifndef _ISUPTYPE_H_
#define _ISUPTYPE_H_

/* define the calling conventions for the API functions for various
 * operating systems - NOTE: API callers should never define the
 * preprocessor constant "_TX_ISUPAPI_SOURCE_"; this is only for use
 * by the ISUP API source code itself.
 */

/* OS2: ISUP API is a DLL */
#ifdef __OS2__
#ifdef _TX_ISUPAPI_SOURCE_
    /* ISUP API source definition */
#define     TXISUPAPIFUNC               extern _export _syscall
#else
    /* ISUP API caller's definition */
#define     TXISUPAPIFUNC               _syscall
#endif  /* _TX_ISUPAPI_SOURCE_ */

/* WIN32: ISUP API is a DLL */
#elif  WIN32	                        /* WIN32 */
#ifdef _TX_ISUPAPI_SOURCE_
    /* ISUP API source definition */
#define     TXISUPAPIFUNC               __declspec( dllexport ) WINAPI
#else
    /* ISUP API caller's definition */
#define     TXISUPAPIFUNC               WINAPI
#endif  /* _TX_ISUPAPI_SOURCE_ */

/* all others: statically linked library */
#else
#define     TXISUPAPIFUNC
#endif

/* Define abstract data types for:
 * 1. file descriptors, or handles, used to do I/O with TXn0000
 * 2. handles to "sychronization objects", which may or may not
 *    be the same as the file descriptor/handle, which can be
 *    useful/required on some host OS's deal with asynchonous
 *    events (e.g., incoming messages) multiple TxN000 and/or
 *    other devices.
 */

/* basic file descriptor/handle definition - note that the actual
 * definition for these for each supported operating system is
 * in the <txcpi.h> file.
 */
#ifdef TX_HANDLE
typedef TX_HANDLE	OS_FD;
#define OS_NULL_FD	CPI_INVALID_HANDLE
#else
typedef S32			OS_FD;
#define OS_NULL_FD	-1
#endif

/* synchronization handle definition - note that the actual
 * definition for these for each supported operating system is
 * in the <txcpi.h> file.
 */
#ifdef CPI_WAIT_TYPE
typedef CPI_WAIT_TYPE	OS_HSYNC;
#define OS_NULL_HSYNC	CPI_INVALID_WAIT_HANDLE
#else
typedef OS_FD			OS_HSYNC;
#define OS_NULL_HSYNC	OS_NULL_FD
#endif

/* Basic types */

typedef U32 CirId;                /* circuit Id */

typedef U32 SiInstId;             /* instance id */

typedef U8 Ent;                   /* entity */

typedef U8 Inst;                  /* instance */

typedef S16 SuId;                 /* service user sap id */

typedef S16 SpId;                 /* service provider sap id */



#define PUBLIC

/* structure passed back from ISUPRecvMessage to identify type, etc., of
 * indication/confirmation received from ISUP layer.
 */
typedef struct rcvInfoBlk {
	U8			indType;			/* indication/confirmation type */
	U8			evntType;			/* event type for status & connection
									 * status indications only */
	SuId		suId;				/* service user (SAP) id - all */
	SiInstId	suInstId;			/* caller's reference number - all */
	SiInstId	spInstId;			/* ISUP's reference number - all */
	CirId		circuit;			/* circuit id - all */
	Bool		globalFlg;			/* global/circuit specific flag - status
									 * indication only */
	U8			srcBoard;			/* source board number */
} RcvInfoBlk;


/* return codes */

#define ISUP_SUCCESS	0		/* request successful */
#define ISUP_NOMSG		1		/* no message waiting */
#define ISUP_NOTBOUND	-1      /* ISUP primitive called before bind */
#define ISUP_UNKEVENT	-2		/* unknown event type passed to primitive */
#define	ISUP_OSERROR	-3		/* OS-specific error */
#define ISUP_RESOURCES	-4		/* unable to allocate resources (buffer) */
#define ISUP_BADMSG		-5		/* unrecognized msg rec'd from ISUP */
#define ISUP_INVBOARD   -6		/* Board number invalid */

#endif

