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

/* File: isupapi.h
 *
 * Data types, function prototypes, and return codes for SS7 ISUP API.
 *
 */
#ifndef _ISUPAPI_H_
#define _ISUPAPI_H_

#include "isuptype.h"
#include "isupmsgs.h"

/* Indication/confirmation types for received messages */

#define EVTSITBNDREQ      0x04  /* Bind request */

#define EVTSITCONREQ      0x0C  /* Connct request */
#define EVTSITCONCFM      0x0D  /* Connct confirm */
#define EVTSITCONRSP      0x0F  /* Connect response */
#define EVTSITCONIND      0x0E  /* Connect indication */

#define EVTSITCNSTREQ     0x58  /* Connection progress status request */
#define EVTSITCNSTIND     0x5A  /* Connection progress status indication */

#define EVTSITDATREQ      0x14  /* Data request */
#define EVTSITDATIND      0x16  /* Data indication */

#define EVTSITFACREQ      0x68  /* Call facility request */
#define EVTSITFACIND      0x6A  /* Call facility indication */
#define EVTSITFACRSP      0x6B  /* Call facility response */
#define EVTSITFACCFM      0x69  /* Call facility confirm */

#define EVTSITRELREQ      0x5C  /* Connection release request */
#define EVTSITRELRSP      0x5F  /* Connection release response */
#define EVTSITRELIND      0x5E  /* Connection release indication */
#define EVTSITRELCFM      0x5D  /* Connection release confirmation */

#define EVTSITSUSPREQ     0x38  /* Call suspend request */
#define EVTSITSUSPIND     0x3A  /* Call suspend indication */

#define EVTSITRESMREQ     0x34  /* Call resume request */
#define EVTSITRESMIND     0x36  /* Call resume indication */

#define EVTSITSTAREQ      0x78  /* Status request */
#define EVTSITSTAIND      0x7A  /* Status indication */

/* events for Connect Status Request/Indication */

#define ADDRCMPLT         0     /* address complete */
#define MODIFY            1     /* modify */
#define MODCMPLT          2     /* modify complete */
#define MODREJ            3     /* modify reject */
#define PROGRESS          4     /* progress */
#define FRWDTRSFR         5     /* forward transfer */
#define INFORMATION       6     /* information */
#define INFORMATREQ       7     /* information request */
#define SUBSADDR          8     /* subsequent address */

/* events for status request/indication primitives */

#define   REATTMEMP        1      /* reattemp indication */
#define   ERRORIND         2      /* error indication */
#define   CONTCHK          3      /* continuity check */
#define   CONTREP          4      /* continuity report */
#define   STPCONTIN        5      /* stop continuity */
#define   CIRGRPQRYRSP     6      /* circuit group query response */
#define   CONFUSION        7      /* confusion */
#define   LOOPBCKACK       8      /* loop-back acknowledge */
#define   CIRRESERVE       9      /* circuit reservation request */
#define   CIRRESERVEACK    0x0a   /* circuit reservation acknowledge  */
#define   CIRBLKREQ        0x14   /* circuit block request */
#define   CIRBLKRSP        0x15   /* circuit block response */
#define   CIRUNBLKREQ      0x16   /* circuit unblock request */
#define   CIRUNBLKRSP      0x17   /* circuit unblock response */
#define   CIRRESREQ        0x18   /* circuit reset request */
#define   CIRGRPBLKREQ     0x1c   /* circuit group block request */
#define   CIRGRPUNBLKREQ   0x1d   /* circuit group unblock request */
#define   CIRGRPQRYREQ     0x1e   /* circuit group query request */
#define   CIRGRPBLKRSP     0x1f   /* circuit group block response */
#define   CIRGRPUNBLKRSP   0x20   /* circuit group unblock response */
#define   CIRGRPRESREQ     0x21   /* circuit group reset request */
#define   CIRUNEQPD        0x22   /* circuit unequipped */
#define   CIRGRPRESACK     0x23   /* circuit group reset acknowledge */

/* ISUP API functions */

OS_FD TXISUPAPIFUNC ISUPBindReq( U8 board, SpId spId, Ent srcEnt, Inst srcInst, SuId suId );
OS_HSYNC TXISUPAPIFUNC ISUPSyncObj( OS_FD fd, S16 *errval );
short TXISUPAPIFUNC ISUPRetrieveMessage(OS_FD fd, SiAllSdus *event, RcvInfoBlk *infoBlk, Bool wait);
short TXISUPAPIFUNC ISUPConnectReq( U8 board, SuId suId, SiInstId suInstId, SiInstId spInstId,
					  Bool cirSelFlg, CirId circuit, SiConEvnt *conEvnt) ;
short TXISUPAPIFUNC ISUPConnectResp( U8 board, SuId suId, SiInstId suInstId, SiInstId spInstId,
					  CirId circuit, SiConEvnt *conEvnt) ;
short TXISUPAPIFUNC ISUPConnectStatusReq( U8 board, SuId suId, SiInstId suInstId, SiInstId spInstId,
					  		CirId circuit, SiCnStEvnt *conStEvnt, U8 eventType) ;
short TXISUPAPIFUNC ISUPReleaseReq( U8 board, SuId suId, SiInstId suInstId, SiInstId spInstId,
					  CirId circuit, SiRelEvnt *relEvnt) ;
short TXISUPAPIFUNC ISUPReleaseResp( U8 board, SuId suId, SiInstId suInstId, SiInstId spInstId,
					   CirId circuit, SiRelEvnt *relEvnt) ;
short TXISUPAPIFUNC ISUPDataReq( U8 board, SuId suId, SiInstId suInstId, SiInstId spInstId,
					  CirId circuit, SiInfoEvnt *infoEvnt) ;
short TXISUPAPIFUNC ISUPSuspendReq( U8 board, SuId suId, SiInstId suInstId, SiInstId spInstId,
					  CirId circuit, SiSuspEvnt *suspEvnt) ;
short TXISUPAPIFUNC ISUPResumeReq( U8 board, SuId suId, SiInstId suInstId, SiInstId spInstId,
				     CirId circuit, SiResmEvnt *resmEvnt) ;
short TXISUPAPIFUNC ISUPStatusReq( U8 board, SuId suId, SiInstId suInstId, SiInstId spInstId,
					 Bool globalFlg, CirId circuit, U8 eventType,
					 SiStaEvnt *statEvnt) ;
short TXISUPAPIFUNC ISUPFacilityReq( U8 board, SuId suId, SiInstId suInstId, SiInstId spInstId,
					  CirId circuit, SiFacEvnt *facEvnt) ;
short TXISUPAPIFUNC ISUPFacilityResp( U8 board, SuId suId, SiInstId suInstId, SiInstId spInstId,
					  	CirId circuit, SiFacEvnt *facEvnt) ;

#endif
