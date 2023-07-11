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

#ifndef _TX_ISUPAPI_SOURCE_
#include "isupmsgs.h"
#endif
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
#define EXIT              9     /* exit */
#define NETRESMGT         10    /* network resource management  */
#define IDENTREQ          11    /* identification request  */
#define IDENTRSP          12    /* identification response  */
#define MALCLLPRNT        13    /* Malicious call print  */
#define CHARGE            14    /* Charge Info  */
#define TRFFCHGE          15    /* Tariff Change  */
#define CHARGEACK         16    /* Charge Acknowledge  */
#define CALLOFFMSG        17    /* Call Offering  */

/* events for status request/indication primitives */

#define   REATTEMPT        1      /* reattemp indication */
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
#define   CIRRESREQLOC     0x24   /* reset initiated locally by the software */

#define   MTPPAUSE         0x25   /* pause received from MTP */
#define   MTPRESUME        0x26   /* resume received from MTP */
#define   RMTUSRUNAVAIL    0x27   /* remote user unavailable */
#define   RMTUSRAVAIL      0x28   /* remote user available */
#define   MTPCONGEST       0x29   /* congestion received from MTP */
#define   MTPSTOPCONGEST   0x2a   /* stop congestion received from MTP */

/* events for general facility request */

#define FACILITY            0x00
#define FACILITYACC         0x01
#define FACILITYREJ         0x02
#define FACILITYINFO        0x03
#define FACILITYDEACT       0x04
#define FACILITYREQ         0x05


/* switchType values for buffer initialization functions */

#define ST_ITU      1
#define ST_ITUWHITE 1
#define ST_ANS88    2
#define ST_ANS92    3
#define ST_ITUBLUE  4
#define ST_ANS95    5
#define ST_Q767     6
#define ST_JNTT     7


/* ISUP API functions */
#ifdef __cplusplus
extern "C" {
#endif

OS_FD TXISUPAPIFUNC ISUPBindReq( U8 board, SpId spId, Ent srcEnt, Inst srcInst, SuId suId );
short TXISUPAPIFUNC ISUPUnBindReq( U8 board, SpId spId);
OS_HSYNC TXISUPAPIFUNC ISUPSyncObj( OS_FD fd, S16 *errval );
short TXISUPAPIFUNC ISUPRetrieveMessage(OS_FD fd, SiAllSdus *event, IsupRcvInfoBlk *infoBlk, Bool wait);
short TXISUPAPIFUNC ISUPConnectReq( U8 board, SuId suId, SiInstId suInstId, SiInstId spInstId,
                      Bool cirSelFlg, CirId circuit, SiConEvnt *conEvnt);
short TXISUPAPIFUNC ISUPConnectResp( U8 board, SuId suId, SiInstId suInstId, SiInstId spInstId,
                      CirId circuit, SiConEvnt *conEvnt);
short TXISUPAPIFUNC ISUPConnectStatusReq( U8 board, SuId suId, SiInstId suInstId, SiInstId spInstId,
                            CirId circuit, SiCnStEvnt *conStEvnt, U8 eventType);
short TXISUPAPIFUNC ISUPReleaseReq( U8 board, SuId suId, SiInstId suInstId, SiInstId spInstId,
                      CirId circuit, SiRelEvnt *relEvnt);
short TXISUPAPIFUNC ISUPReleaseResp( U8 board, SuId suId, SiInstId suInstId, SiInstId spInstId,
                       CirId circuit, SiRelEvnt *relEvnt);
short TXISUPAPIFUNC ISUPDataReq( U8 board, SuId suId, SiInstId suInstId, SiInstId spInstId,
                      CirId circuit, SiInfoEvnt *infoEvnt);
short TXISUPAPIFUNC ISUPSuspendReq( U8 board, SuId suId, SiInstId suInstId, SiInstId spInstId,
                      CirId circuit, SiSuspEvnt *suspEvnt);
short TXISUPAPIFUNC ISUPResumeReq( U8 board, SuId suId, SiInstId suInstId, SiInstId spInstId,
                     CirId circuit, SiResmEvnt *resmEvnt);
short TXISUPAPIFUNC ISUPStatusReq( U8 board, SuId suId, SiInstId suInstId, SiInstId spInstId,
					 Bool globalFlg, CirId circuit, U8 eventType,
                     SiStaEvnt *statEvnt);
short TXISUPAPIFUNC ISUPFacilityReq( U8 board, SuId suId, SiInstId suInstId, SiInstId spInstId,
                      CirId circuit, SiFacEvnt *facEvnt, U8 eventType);

S16 TXISUPAPIFUNC ISUPInitACM(S16 switchType, SiCnStEvnt *event);
S16 TXISUPAPIFUNC ISUPInitANM(S16 switchType, SiConEvnt *event);
S16 TXISUPAPIFUNC ISUPInitCON(S16 switchType, SiConEvnt *event);
S16 TXISUPAPIFUNC ISUPInitCOT (S16 switchType, SiStaEvnt *event, U8 contInd);
S16 TXISUPAPIFUNC ISUPInitCPG(S16 switchType, SiCnStEvnt *event);
S16 TXISUPAPIFUNC ISUPInitCRM(S16 switchType, SiStaEvnt *event);
S16 TXISUPAPIFUNC ISUPInitFAA(S16 switchType, SiFacEvnt *event);
S16 TXISUPAPIFUNC ISUPInitFAC(S16 switchType, SiFacEvnt *event);
S16 TXISUPAPIFUNC ISUPInitFAD(S16 switchType, SiFacEvnt *event);
S16 TXISUPAPIFUNC ISUPInitFAI(S16 switchType, SiFacEvnt *event);
S16 TXISUPAPIFUNC ISUPInitFAR(S16 switchType, SiFacEvnt *event);
S16 TXISUPAPIFUNC ISUPInitFRJ(S16 switchType, SiFacEvnt *event, U8 cause);
S16 TXISUPAPIFUNC ISUPInitFOT(S16 switchType, SiCnStEvnt *event);
S16 TXISUPAPIFUNC ISUPInitIAM(S16 switchType, SiConEvnt *event,
                              U8 *cdPty, U8 cdPtyLen, U8 *cgPty, U8 cgPtyLen);
S16 TXISUPAPIFUNC ISUPInitINF(S16 switchType, SiCnStEvnt *event);
S16 TXISUPAPIFUNC ISUPInitINR(S16 switchType, SiCnStEvnt *event);
S16 TXISUPAPIFUNC ISUPInitREL(S16 switchType, SiRelEvnt *event, U8 cause);
S16 TXISUPAPIFUNC ISUPInitSAM(S16 switchType, SiCnStEvnt *event,
                                              U8 *subAddr, U8 subAddrLen);
S16 TXISUPAPIFUNC ISUPInitSUS (S16 switchType, SiSuspEvnt *event);
S16 TXISUPAPIFUNC ISUPInitRES (S16 switchType, SiResmEvnt *event);
U8 TXISUPAPIFUNC ISUPASCIItoBCD( U8 *ascii, U8 *bcd, U8 length);
U8 TXISUPAPIFUNC ISUPBCDtoASCII( U8 *bcd, U8 bcdLen, U8 *ascii, U8 asciiLen);
#ifdef __cplusplus
}
#endif

#endif


