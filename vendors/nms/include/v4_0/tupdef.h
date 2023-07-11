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
 *************************************************************************/


/* File:    tupdef.h
 *
 * Defines used for interfacing with TUP API
 */
#ifndef _TUPDEF_H_
#define _TUPDEF_H_

/* Prevent C++ name mangling. */
#ifdef __cplusplus
extern "C"
{
#endif



/* Indication/confirmation types for received messages */

#define EVTTUPBNDREQ        0x04    /* Bind request */
#define EVTTUPBNDCFM        0x05    /* Bind Confirm */

#define EVTTUPCONREQ        0x0C    /* Connct request */
#define EVTTUPCONCFM        0x0D    /* Connct confirm */
#define EVTTUPCONRSP        0x0F    /* Connect response */
#define EVTTUPCONIND        0x0E    /* Connect indication */

#define EVTTUPRESTOREREQ    0x2D    /* Checkpoint Request from backup to primary
                                     * to restore status of all configured circuits */
#define EVTTUPRESTORERSP    0x2E    /* Checkpoint restore response from primary which
                                     * contains the state information of configured
                                     * circuits */
#define EVTTUPCKPTIND       0x2F    /* Checkpoint indications sent from primary to backup */

#define EVTTUPCNSTREQ       0x58    /* Connection progress status request */
#define EVTTUPCNSTIND       0x5A    /* Connection progress status indication */

#define EVTTUPRELREQ        0x5C    /* Connection release request */
#define EVTTUPRELRSP        0x5F    /* Connection release response */
#define EVTTUPRELIND        0x5E    /* Connection release indication */
#define EVTTUPRELCFM        0x5D    /* Connection release confirmation */

#define EVTTUPSTAREQ        0x78    /* Status request */
#define EVTTUPSTAIND        0x7A    /* Status indication */
#define EVTTUPMGTSTAIND     0x7B    /* Status indication */

/* events for Connect Status Request/Indication */

#define     TUPADDRCMPLT       0       /* address complete (ACM)*/
#define     TUPCHARGEMSG       4       /* charge message (CHG)*/
#define     TUPFRWDTRSFR       5       /* forward transfer (FOT)*/
#define     TUPINFORMATION     6       /* information (GSM)*/
#define     TUPINFORMATREQ     7       /* information request (GRQ)*/
#define     TUPSUBSADDR        8       /* subsequent address (SAM)*/
#define     TUPSUBADDRONE      9       /* one subsequest addr (SAO)*/
#define     TUPMALICIOUS       10      /* malicious call signal (MAL) (China only) */
#define     TUPREANSWER        11      /* reanswer signal (RAN) */
#define     TUPOPERATOR        12      /* operator signal (OPR) (China only) */
#define     TUPCALLCLEAR       13      /* calling party clear(CCL)*/
#define     TUPMETERPULSE      14      /* metering pulse msg (MPM) (China only) */
#define     TUPAUTOCONG        15      /* auto-congestion lvl(ACC) */

/* events for status request/indication primitives */

#define     TUPREATTMEMP        1     /* reattempt indication */
#define     TUPERRORIND         2     /* error indication */
#define     TUPCONTCHK          3     /* continuity check (CCR)*/
#define     TUPCONTREP          4     /* continuity report (COT)*/
#define     TUPCONFAIL          5     /* continuity failure (CCF)*/
#define     TUPCONFUSION        7     /* confusion */

#define     TUPMTP3PAUSE        8     /* a pause was Rxed from MTP */
#define     TUPMTP3RESUME       9     /* a resume was Rxed from MTP */

#define     TUPCIRBLKREQ        10    /* circuit block request (BLO)*/
#define     TUPCIRUNBLKREQ      11    /* circuit unblock request (UBL)*/

#define     TUPCIRRESREQ        12    /* circuit reset request (RSC)*/

#define     TUPCIRGRPRESREQ     13    /* circuit group reset request (GRS)*/

#define     TUPCRMGRPBLKREQ     14    /* maint circ grp block request (MGB)*/
#define     TUPCRMGRPUNBLKREQ   15    /* maint circ grp unblock request (MBA)*/

#define     TUPCRHGRPBLKREQ     16    /* h/w circ grp block request (HGB)*/
#define     TUPCRHGRPUNBLKREQ   17    /* h/w circ grp unblock request (HBA)*/

#define     TUPCRSGRPBLKREQ     18    /* s/w circ grp block request (SGB)*/
#define     TUPCRSGRPUNBLKREQ   19    /* s/w circ grp unblock request (SBA)*/

#define     TUPMTP3PRIMARY      20    /* a Primary event was Rxed from MTP */
#define     TUPMTP3BACKUP       21    /* a Backup event was Rxed from MTP */
#define     TUPMTP3STANDALONE   22    /* a Standalone event was Rxed from MTP */
#define     TUPMTP3CONGESTION   23    /* a congestion event was Rxed from MTP */
#define     TUPMTP3STOPCONGESTION  24 /* a stop congestion event was Rxed from MTP */
#define     TUPTASKCONGESTION   25    /* task memory congestion */
#define     TUPMTP3PAUSETMREXP  26    /* Pause timer popped */

#define     TUPCIRGRPRESACK     27    /* circuit group reset request (GRS)*/


/** release cause indicators **/
#define TUPSWITCHCONG              0x81        /* SEC */
#define TUPCIRCUITCONG             0x82        /* CGC */
#define TUPNATIONALCONG            0x83        /* NNC */
#define TUPADDRESSINCOMP           0x84        /* ADI */
#define TUPCALLFAILURE             0x85        /* CFL */
#define TUPSUBBUSY                 0x86        /* SSB */
#define TUPUNALLOCATEDNUM          0x87        /* UNN */
#define TUPOUTOFSERVICE            0x88        /* LOS */
#define TUPSENDSPECIAL             0x89        /* SST */
#define TUPACCESSBARRED            0x8a        /* ACB */
#define TUPNODIGITAL               0x8b        /* DPN */
#define TUPEXTENDEDINFO            0x8c        /* EUM */
#define TUPCLEARFWD                0x8d        /* CLF */
#define TUPCLEARBKW                0x8e        /* CBK */
#define TUPMISDIALEDPREFIX         0x8f        /* MPR, not China */
#define TUPSUBLOCALBUSY            0x91        /* SLB, China only */
#define TUPSUBTOLLBUSY             0x92        /* STB, China only */
#define TUPDUALSEIZURE             0x93        /* When an incoming IAM controls an outgoing one */

/* error codes */

#define TUP_NOMEM       1
#define TUP_INVNSAP     2
#define TUP_INVUSAP     3
#define TUP_INVGRP      4
#define TUP_INVCIRC     5
#define TUP_SAPEXIST    6
#define TUP_CIRCEXIST   7
#define TUP_MTPERR      8
#define TUP_INVSTATE    9
#define TUP_UNKEVT      10
#define TUP_INVENT      11
#define TUP_INVPKT      12
#define TUP_INVINST     13
#define TUP_BLOCKED     14
#define TUP_INVSWITCH   15

#define TRCMSGTX         11          /* trace - message transmitted */
#define TRCMSGRX         12          /* trace- message received */


/*#define DEFAULTTRACECHAN    0x18 */   /* default trace entity */
#define DEFAULTTRACECHAN    0x2f   /* default trace entity */

/*-----------------------------------------------------------------------------
  NUP Version Ids
    - These id's are used to identify the revision level of this service.
  ---------------------------------------------------------------------------*/
#define TUP_MAJORREV                        1
#define TUP_MINORREV                        0


/****************************************************************************/
/* important constants and common data structures                           */
/****************************************************************************/
/* TRP - return code definitions */

#define TUP_SUCCESS         0           /* API call was successful          */
#define TUP_OVERRUN         0x200      /* data length too large to send    */
#define TUP_UNDERRUN        0x201      /* received message too large       */
#define TUP_UNBOUND         0x203      /* not bound to specified board     */
#define TUP_BOARD           0x204      /* board number out of range        */
#define TUP_DRIVER          0x205      /* CPI driver returned error        */
#define TUP_NOMSG           0x206      /* No event messages waiting        */
#define TUP_NOTBOUND        0x207      /* User failed to call              */
#define TUP_FAILED          0x208      /* request failed                   */
#define TUP_UNINIT          0x209
#define TUP_INDEX           0x20a
#define TUP_PARAM           0x20b
#define TUP_OVERFLOW        0x20c

/* Event generated by TUP Service and sent back to client for all strings  */
/* TCAPEVN_DATA =  (TUP_SVCID << 16) | 0x2000 | 0x01  */

#define TUPEVN_DATA                 0x2F2001
#define TUPEVN_CONGEST              0x2F2002

/******* Set compiler structure packing option */
#ifndef TUP_TASK
#pragma pack(1)
#endif
/****************************************************************************/
/* TUP API Statistics returned by TUPGetApiStats()                        */
/****************************************************************************/
typedef struct
{
    U32 qCount;             /* number of API messages currently queued to TUP layer */
    U32 qPeak;              /* max number of API messages ever queued to TUP layer */
    U32 txPending;          /* current number of outstanding transmit rqsts to TUP layer */
    U32 txPendPeak;         /* max number of transmit rqsts ever outstanding to TUP layer */
    U32 txSuccess;          /* number of successful transmit requests completed */
    U32 txFailed;           /* number of failed transmit requests */
    U32 txLastErr;          /* error code from last failed transmit request */
    U32 rxSuccess;          /* number of events received from TUP layer */
    U8  apiQCongLvl;        /* current outbound queue congestion level [0..3] */
    U8  tupCongLvl;        /* current TUP layer congestion level [0..3] */
    U8  tupCongSrc;        /* reason for TUP layer congestion */
    U8  spare1;             /* spare for alignment */
} TUPAPISTATS;

#ifndef TUP_TASK
#pragma pack()
#endif

#ifdef __cplusplus
}
#endif

#endif
