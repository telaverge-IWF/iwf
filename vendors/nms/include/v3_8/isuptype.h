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

#include "txcpi.h"
#include "dpruser.h"

#ifdef UNIX
#pragma pack(1)
#endif

/* Define abstract data types for:
 * 1. file descriptors, or handles, used to do I/O with TXn0000
 * 2. handles to "sychronization objects", which may or may not
 *    be the same as the file descriptor/handle, which can be
 *    useful/required on some host OS's deal with asynchonous
 *    events (e.g., incoming messages) multiple TxN000 and/or
 *    other devices.
 */

/* Basic types */

typedef U32 CirId;                /* circuit Id */
typedef U32 SiInstId;             /* instance id */
typedef U8 Ent;                   /* entity */
typedef U8 Inst;                  /* instance */
typedef S16 SuId;                 /* service user sap id */
typedef S16 SpId;                 /* service provider sap id */

/* TRP - added MAX_BUF_SIZE and Buffer to get rid of gen.x ssi.x */
/*#define MAX_BUF_SIZE    1400

typedef struct
{
  DPRH        hdr;             * dual port RAM header *
  S16         start;           * offset of start of data *
  S16         end;             * offset of 1st unused byte past end of data *
  unsigned char buffer[(MAX_BUF_SIZE + 4) & 0xffc];
} Buffer;
*/

#define PUBLIC

/* structure passed back from ISUPRecvMessage to identify type, etc., of
 * indication/confirmation received from ISUP layer.
 */
typedef struct isupRcvInfoBlk {
  U8            indType;			/* indication/confirmation type */
  U8		evntType;			/* event type for status & connection
							 * status indications only */
  SuId          suId;                           /* service user (SAP) id - all */
  SiInstId	suInstId;			/* caller's reference number - all */
  SiInstId	spInstId;			/* ISUP's reference number - all */
  CirId		circuit;			/* circuit id - all */
  Bool		globalFlg;			/* global/circuit specific flag - status
						 * indication only */
  U8		srcBoard;			/* source board number */
  U16           fill1;
} IsupRcvInfoBlk;

#ifndef _NEW_ISUP_
typedef IsupRcvInfoBlk RcvInfoBlk;
#endif

#ifdef UNIX
#pragma pack()
#endif

#endif


