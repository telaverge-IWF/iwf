/*************************************************************************
**                                                                      **
**                         PROPRIETARY NOTICE                           **
**                                                                      **
**                         Copyright (c) 1998                           **
**                      by Natural MicroSystems, Inc.                   **
**                                                                      **
**  The following is licensed program material and is considered        **
**  proprietary and confidential.  No part of this program may be       **
**  reproduced or used in any form or by any means without the express  **
**  written permission of Natural MicroSystems, Inc.                    **
**                                                                      **
*************************************************************************/

/* --------------------------------------------------------------------------
 * sccpmapi.h
 *
 * The file contains constants, structures, and function prototypes
 * required for using the SS7 SCCP Management API.
 *
 * $Log: sccpmapi.h,v $
 * Revision 9.1  2005/03/23 12:56:02  cvsadmin
 * Begin PR6.5
 *
 * Revision 8.2  2005/03/21 13:55:29  cvsadmin
 * PR6.4.2 Source Propagated to Current
 *
 * Revision 7.1  2002/08/26 22:11:00  mmiers
 * Begin PR6.2
 *
 * Revision 6.1  2002/02/28 16:14:55  mmiers
 * Begin PR7.
 *
 * Revision 1.1  2001/10/05 16:52:37  mmiers
 * Add 3.8 beta
 *
*
* 5     8/24/98 11:36a Marcn
* Added DllImport definition
*
* 4     8/24/98 11:04a Marcn
* Added pragmas
*
* 3     8/20/98 10:27a Marcn
* Fixed spelling of DllExport
*
* 2     8/19/98 3:40p Dodren
* Removed dllimport #define since it is not used.
*
* 1     8/19/98 2:48p Dodren
* Initial version of SCCP Management API files.  Note that SCCPDEFS.H now
* contains #defines that are shared between the protocol and management
* APIs.
 * $Nokeywords$
 * -------------------------------------------------------------------------- */

#if !defined( _SCCPMAPI_H_ )
#define _SCCPMAPI_H_

#include "ss7type.h"        /* Defines standard data types (S8, U8, etc.)     */
#include "sccpdef.h"        /* Defines shared between SCCP API and SCCP MAPI  */

/* --------------------------------------------------------------------------
 * API Calling Convention
 *
 * The API Calling Convention is defined here for multiple operating systems.
 *
 * NOTE: Users of the API should never define the preprocessor constant
 *       "_TX_SCCPMAPI_SOURCE_"; this is only for use by the SCCP MAPI source
 *       code itself.
 * -------------------------------------------------------------------------- */

#if defined( __OS2__ )                  /* OS2: API is a DLL                  */

#define DllExport   extern _export
#define DllImport   ?????????
#if defined( _TX_SCCPMAPI_SOURCE_ )
#define TXSCCPMGMTFUNC  DllExport _syscall
#else
#define TXSCCPMGMTFUNC  _syscall
#endif

#elif defined( WIN32 )                  /* WIN32: API is a DLL                */

#define DllExport       __declspec( dllexport )
#define DllImport       __declspec( dllimport )
#if defined( _TX_SCCPMAPI_SOURCE_ )
#define TXSCCPMGMTFUNC  DllExport WINAPI
#else
#define TXSCCPMGMTFUNC  WINAPI
#endif

#else                                   /* Other OS: API statically linked    */

#define DllExport
#define DllImport
#define TXSCCPMGMTFUNC

#endif

/* --------------------------------------------------------------------------
 * Constants used in sizing arrays:
 * -------------------------------------------------------------------------- */

#define SCCP_MAXCONPC   8       /* Max Concerned Point Codes per Dpc          */
#define SCCP_LENADDR    32      /* SCCP Address Name/Mask Length              */
#define SCCP_MAXSSNS    8       /* Max Subsystems allowed per Dpc             */

/* --------------------------------------------------------------------------
 * Switch Types (define protocol behavior):
 *   for Network SAPs, Addresses & Routes use:  SCCP_SW_[ITU | ANS]
 *   for User SAPs use:                         SCCP_SW_[ITU | ANS][88 | 92]
 * -------------------------------------------------------------------------- */
#define SCCP_SW_ITU     1       /* ITU-T - General                            */
#define SCCP_SW_ANS     2       /* ANSI  - General                            */
#define SCCP_SW_ITU88   3       /* ITU-T 1988 operation                       */
#define SCCP_SW_ITU92   4       /* ITU-T 1992 operation                       */
#define SCCP_SW_ANS88   5       /* ANSI-1988 operation                        */
#define SCCP_SW_ANS92   6       /* ANSI-1992 operation                        */
#define SCCP_SW_ITU96   7       /* ITU-T 1996 operation                       */
#define SCCP_SW_ANS96   8       /* ANSI-1996 operation                        */

/* --------------------------------------------------------------------------
 * Local Status (LS) and Route Status (RS) Values:
 * -------------------------------------------------------------------------- */
#define SCCP_OFFLINE    0x00    /* LS: Signalling point is offline            */
#define SCCP_ONLINE     0x01    /* LS: Signalling point is online             */
                                /* RS: Destination is accessible              */
#define SCCP_CONG       0x02    /* RS: Destination is congested (this status  */
                                /*     is reported back by SCCP to application*/
                                /*     and not be set by application)         */
#define SCCP_TRANS      0x04    /* RS: This signalling pnt is translator node */
#define SCCP_ADJACENT   0x08    /* RS: This signalling point is adjacent for  */
                                /*     SCCP point code & subsystem mgmt procs */

/* --------------------------------------------------------------------------
 * Status Values for Route Configuration Subsystem List:
 * -------------------------------------------------------------------------- */

#define SCCP_SNR        0x10    /* Subsystem normal routed, not backup routed */
#define SCCP_ACC        0x01    /* Subsystem is accessible                    */

/* --------------------------------------------------------------------------
 * Subservice Selections:
 * -------------------------------------------------------------------------- */

#define SCCP_SSF_INTL    0       /* International                             */
#define SCCP_SSF_SPARE   1       /* Spare                                     */
#define SCCP_SSF_NAT     2       /* National                                  */
#define SCCP_SSF_RES     3       /* Reserved                                  */

/* --------------------------------------------------------------------------
 * Alarm Levels:
 * -------------------------------------------------------------------------- */
#define SCCP_ALARMLVL_DISABLE   0   /* All alarms disabled                    */
#define SCCP_ALARMLVL_DEFAULT   1   /* Default - significant/abnormal events  */
#define SCCP_ALARMLVL_DEBUG     2   /* + Some normal events for toubleshooting*/
#define SCCP_ALARMLVL_DETAIL    3   /* + Detailed events for troubleshooting  */

/* --------------------------------------------------------------------------
 * Trace flags:
 * -------------------------------------------------------------------------- */
#define SCCP_TRACE_DATA     1   /* Turns on data tracing                      */

/* --------------------------------------------------------------------------
 * User SAP Status bits
 * -------------------------------------------------------------------------- */
#define SCCP_STA_BND        0x01        /* bind                               */
#define SCCP_STA_FLCOFF     0x02        /* flow control off                   */
#define SCCP_STA_GUARD      0x04        /* guarding                           */
#define SCCP_STA_BRT        0x08        /* backup routed                      */
#define SCCP_STA_GRNT       0x10        /* waiting for grant                  */
#define SCCP_STA_IGNR       0x20        /* ignore                             */
#define SCCP_STA_PROH       0x40        /* prohibited                         */
#define SCCP_STA_REST       0x80        /* restarting                         */

/* --------------------------------------------------------------------------
 * Timer Resolutions:
 * -------------------------------------------------------------------------- */

#define SCCP_TIMER_RES  10      /* Resolution for all SCCP timers - ticks/sec */

/* --------------------------------------------------------------------------
 * SCCP Major redundancy states, for General stats block (spRunState)
 * -------------------------------------------------------------------------- */
#define SCCP_INITIAL        0           /* initial state */
#define SCCP_BACKUP         1           /* backup member of redundant pair */
#define SCCP_PRIMARY        2           /* primary member of redundant pair */
#define SCCP_STANDALONE     3           /* non-redundant mode */

/* --------------------------------------------------------------------------
 * SCCP mate communication path status, for General stats block (spMateState)
 * -------------------------------------------------------------------------- */
#define SCCP_MATE_ISOLATED  0           /* isolated, no communication w/mate */
#define SCCP_MATE_CONNECTED 1           /* connected, communicating w/mate */


/* Set compiler structure packing option */
#ifdef UNIX
#pragma pack(1)
#endif

/* --------------------------------------------------------------------------
 * General Configuration Parameters type definition:
 * -------------------------------------------------------------------------- */

typedef struct {
    U8  maxSaps;                /* Max Number of SCCP User Saps               */
    U8  maxNSaps;               /* Max Number of Network Saps (MTP3)          */
    U16 maxScli;                /* Max Number of Sequence Con'less Instances  */
    U16 maxAddrs;               /* Max Number of Addresses                    */
    U16 maxRtes;                /* Max Number of Routes                       */
    U8  DefRouting;             /* Flag for Default Routing  TRP              */
    U8  ConnDrop;               /* Flag prevents Connection Drop on link loss */
    U16 maxAdjDpc;              /* Max Number of Adjacent Point Codes         */
    U16 maxMsgDrn;              /* Max msg to drain  (max: 65535)             */
    U16 maxXUDTs;               /* Max ext. unit data control blocks (ITU92)  */
    U16 maxXUDTref;             /* Obsolete, not used                         */
    U8  status;                 /* Local Status -- SCCP_ONLINE | SCCP_OFFLINE */
    U8  pcDispFmt;              /* point code display format                  */
    S16 sogThresh;              /* Threshold for granting state change        */
    S16 scliTimeRes;            /* Time Resolution                            */
    S16 rteTimeRes;             /* Time Resolution                            */
    S16 sapTimeRes;             /* Time Resolution                            */
    S16 nsapTimeRes;            /* Time resolution                            */
    S16 xrefTimeRes;            /* Time Resolution                            */
    S16 asmbTimeRes;            /* Time Resolution                            */
    U16 spare2;                 /* Alignment                             */
    TimerCfg scliTimer;         /* default SCLI timer                         */
    TimerCfg sstTimer;          /* default SST timer                          */
    TimerCfg nsapTimer;         /* default network sap timer                  */
    TimerCfg srtTimer;          /* Default Timer for SRT                      */
    TimerCfg ignoreTimer;       /* default ignore SST timer                   */
    TimerCfg coordTimer;        /* default Cord State Change SST timer        */
    TimerCfg xrefFrzTimer;      /* default timer for freezing external
                                 *   unit data reference (ITU-92)             */
    TimerCfg defAsmbTmr;        /* default timer for external unit data
                                 *   assembly (CCITT92)                       */
    PDesc stkmgr;               /* Stack Manager                              */
    U16 maxConn;                /* max number of connections                  */
    S16 connThresh;             /* Connection Threshold                       */
    S16 queueThresh;            /* Queue Threshold                            */
    S16 conTimeRes;             /* connection Timer resolution                */
    S16 frzTimeRes;             /* freeze Timer resolution                    */
    U16 spare3;                 /* Alignment                             */
    TimerCfg freezeTimer;       /* default lcl reference freeze timer         */
    TimerCfg connTimer;         /* default connection timer                   */
    TimerCfg txInactTimer;      /* time to allow conn to exist with no tx pkts*/
    TimerCfg rxInactTimer;      /* time to allow conn to exist with no rx pkts*/
    TimerCfg relTimer;          /* default release timer                      */
    TimerCfg repRelTimer;       /* default repeat release timer (ITU-92 only) */
    TimerCfg intvalTimer;       /* default report abnormal release timer      */
    TimerCfg guardTimer;        /* default restart timer                      */
    TimerCfg resetTimer;        /* default reset timer                        */
    TimerCfg aicTimer;          /* default application inactivity control timer */
    TimerCfg aicRespTimer;      /* default application inactivity response timer */
    TimerCfg conRespTimer;      /* default connection indication response timer */
    U8  alarmLevel;             /* Alarm flags                                */
    U8  traceFlags;             /* Trace flags                                */
    U8 spare4;                  /* alignment */
    U8 spare5;                  /* alignment */
    U32 memThresh1;             /* memory congestion threshold 1 */
    U32 memThresh2;             /* memory congestion threshold 2 */
    U32 memThresh3;             /* memory congestion threshold 3 */
} SccpGenCfg;

/* --------------------------------------------------------------------------
 * SCCP Address Name (i.e., Global Title Digits) and Mask type definitions:
 * -------------------------------------------------------------------------- */

typedef struct {
    U8  length;                 /* length bytes                               */
    U8 spare1;                  /* alignment */
    U8 spare2;                  /* alignment */
    U8 spare3;                  /* alignment */
    U8  strg[SCCP_LENADDR];     /* address value - Hexidecimal BCD digits     */
} SccpAddrName, SccpAddrMask;

/* --------------------------------------------------------------------------
 * User SAP Configuration Parameters type definition:
 * -------------------------------------------------------------------------- */

typedef struct {
    S16 swType;                 /* Protocol Switch type/version               */
    U8  selector;               /* selector                                   */
    U8  spare1;                 /* alignment                                  */
    MemoryId mem;               /* memory region & pool id                    */
    U8  bkupPcInd;              /* backup point code indicator (0==none)      */
    U8  aicEnabled;             /* application inactivity timing enabled (1=y)*/
    U16 numConPc;               /* number of concerned point codes            */
    U32 bkupPc;                 /* backup point code                          */
    U32 conPcList[SCCP_MAXCONPC]; /* list of concerned point codes            */
    SccpAddrMask addrMsk;       /* address mask for outgoing pkts on this SAP */
    U8  useMsk;                 /* use address mask? (0=no, 1=yes)            */
    U8  priority;               /* priority                                   */
    U8  route;                  /* route                                      */
    U8  hopCnt;                 /* default Hop Count (between 1 and 15)       */
    U32 qThresh1;               /* inbound queue congestion threshold 1 */
    U32 qThresh2;               /* inbound queue congestion threshold 2 */
    U32 qThresh3;               /* inbound queue congestion threshold 3 */
} SccpUSapCfg;

/* --------------------------------------------------------------------------
 * Network SAP Configuration Parameters type definition:
 * -------------------------------------------------------------------------- */

typedef struct {
    S16 swType;                 /* Protocol Switch type/version               */
    U8  dpcLen;                 /* dpc length: PCLEN_ANSI (24 bits)           */
                                /*             PCLEN_ITU  (14 bits)           */
    U8  useMsk;                 /* use address mask? (0=no, 1=yes)            */
    U32 dpc;                    /* point code for this nsap (switch)          */
    S16 maxMsgLen;              /* max message length for MTP3 on this SAP    */
    S16 txQThr;                 /* max msgs queued to MTP3 before discarding  */
    SccpAddrMask addrMsk;       /* address mask for incoming pkts on this SAP */
    MemoryId mem;               /* memory region & pool id                    */
    U16 dstProcId;              /* destination processor id                   */
    S16 spId;                   /* service provider id                        */
    U8  selector;               /* selector                                   */
    U8  priority;               /* priority                                   */
    U8  route;                  /* route                                      */
    U8  dstEnt;                 /* destination entity                         */
    U8  dstInst;                /* detination instance                        */
    U8  hopCnt;                 /* default Hop Count (between 1 and 15)       */
    U8  ssf;                    /* subsytem part of SIO to be used on NSAP    */
    U8  niInd;                  /* network indicator (0..1) for SCCP mgmt msgs*/
    U16 spare1;                 /* future use                                 */
    U16 spare2;                 /* future use                                 */
} SccpNSapCfg;

/* --------------------------------------------------------------------------
 * Subsytem Configuration Parameters type definition:
 * -------------------------------------------------------------------------- */

typedef struct {
    S16 swType;                 /* Protocol Switch type/version               */
    U8  ssn;                    /* subsystem number                           */
    U8  status;                 /* status                                     */
    U8  bkupPcInd;              /* backup point code indicator (0=none)       */
    U8  spare1;                 /* alignment                                  */
    U16 numConPc;               /* number of concerned point codes            */
    U32 bkupPc;                 /* backup point code                          */
    U32 conPcList[SCCP_MAXCONPC]; /* concerned point codes                    */
} SccpSsnCfg;

/* --------------------------------------------------------------------------
 * Route Configuration Parameters type definition:
 * -------------------------------------------------------------------------- */

typedef struct {
    S16 swType;                 /* Protocol Switch type/version               */
    U8  status;                 /* adjacent/translator flags                  */
    U8  bkupPcInd;              /* backup point code indicator (0=none)       */
    U32 dpc;                    /* destination point code                     */
    U32 bkupPc;                 /* backup point code                          */
    U8  numSsns;                /* number of subsystems                       */
    U8  spare1;                 /* alignment                                  */
    U16 spare2;                 /* alignment                                  */
    SccpSsnCfg ssnList[SCCP_MAXSSNS]; /* subsystems for this dpc              */
} SccpRouteCfg;

/* --------------------------------------------------------------------------
 * Global Title Configuration Parameters type definition:
 * -------------------------------------------------------------------------- */

typedef struct {
   U8 format;                   /* format type                                */
   U8 spare1;                   /* alignment                                  */
   U16 spare2;                  /* alignment                                  */
   union {
      struct {                  /* FORMAT 1:                                  */
         U8 oddEven;            /* odd/even indicator                         */
         U8 natAddr;            /* nature of address                          */
         U8 spare1;             /* alignment                                  */
         U8 spare2;             /* alignment                                  */
      } f1;
      struct {                  /* FORMAT 2                                   */
         U8 tType;              /* translation type                           */
         U8 spare1;             /* alignment                                  */
         U8 spare2;             /* alignment                                  */
         U8 spare3;             /* alignment                                  */
      } f2;
      struct {                  /* FORMAT 3                                   */
         U8 tType;              /* translation type                           */
         U8 numPlan;            /* numbering plan                             */
         U8 encSch;             /* encoding scheme                            */
         U8 spare1;             /* alignment                                  */
      } f3;
      struct {                  /* FORMAT 4                                   */
         U8 tType;              /* translation type                           */
         U8 numPlan;            /* numbering plan                             */
         U8 encSch;             /* encoding scheme                            */
         U8 natAddr;            /* nature of address                          */
      } f4;
   } gt;
   SccpAddrName addr;           /* address digits (BCD Hex )                  */
} SccpGlbTitleCfg;

/* --------------------------------------------------------------------------
 * Address Configuration Parameters type definition:
 * -------------------------------------------------------------------------- */

typedef struct {
   U8  pres;                    /* address is present (always 1)              */
   U8  spare1;                  /* alignment                                  */
   S16 swType;                  /* variant switch                             */
   U8  niInd;                   /* national/international indicator           */
   U8  rtgInd;                  /* routing indicator                          */
   U8  ssnInd;                  /* subsystem number indicator                 */
   U8  pcInd;                   /* point code indicator                       */
   U8  ssn;                     /* subsystem number                           */
   U8  spare2;                  /* alignment                                  */
   U16 spare3;                  /* alignment                                  */
   U32 pc;                      /* point code                                 */
   SccpGlbTitleCfg gt;          /* global title                               */
} SccpAddrCfg;

/* --------------------------------------------------------------------------
 *  Address Map Configuration Parameters type definition:
 * -------------------------------------------------------------------------- */

typedef struct {
    SccpAddrName gtI;           /* Global Title (incoming)                    */
    U8 replGt;                  /* replace Gt (0=leave glt, 1=replace glt)    */
    U8 spare1;                  /* alignment                                  */
    U16 spare2;                 /* alignment                                  */
    SccpAddrCfg addr;           /* outgoing address                           */
} SccpAddrMapCfg;

/* --------------------------------------------------------------------------
 * General (Global) Statistics type definition:
 * -------------------------------------------------------------------------- */

typedef struct {
    DateTime dt;                /* Date and Time                              */
    Duration dura;              /* Duration                                   */
                                /* Routing failure                            */
    S32 rfNTASN;                /*   no translation for address of such nature*/
    S32 rfNTSA;                 /*   no translation for this specific address */
    S32 rfNetFail;              /*   network failure (point code unavailable) */
    S32 rfNetCong;              /*   network congestion */
    S32 rfSsnFail;              /*   subsystem failure */
    S32 rfSsnCong;              /*   subsystem congestion */
    S32 rfUnequip;              /*   unequiped user                           */
    S32 rfHopViolate;           /*   Hop counter violation                    */
    S32 synError;               /*   Syntax Error                             */
    S32 rfUnknown;              /*   reason unknown                           */

    S32 uDataTx;                /* unit data sent                             */
    S32 uDataSrvTx;             /* unit data service sent                     */
    S32 uDataRx;                /* unit data received                         */
    S32 uDataSrvRx;             /* unit data service received                 */

    S32 xuDataTx;               /* extended unit data sent                    */
    S32 xuDataSrvTx;            /* extended unit data service sent            */
    S32 xuDataRx;               /* extended unit data received                */
    S32 xuDataSrvRx;            /* extended unit data service received        */

    S32 msgHand;                /* total msgs handled                         */
    S32 msgLoc;                 /* total msgs intended for local subsystems   */
    S32 gttReq;                 /* msgs. requiring GT translation             */
    S32 msgTxC0;                /* total msgs sent, class 0                   */
    S32 msgTxC1;                /* total msgs sent, class 1                   */
    S32 msgRxC0;                /* total msgs recieved, class 0               */
    S32 msgRxC1;                /* total msgs recieved, class 1               */
    U8  spRunState;             /* current redundancy state */
    U8  spMateState;            /* current mate state (connected/isolated) */
    U8  memCongLevel;           /* task memory congestion level */
    U8  spare1;                 /* spare for alignment */
    S32 inCongDisc;             /* inbound msgs discarded due to congestion */
} SccpGenStats;

/* --------------------------------------------------------------------------
 * User SAP Statistics type definition:
 * -------------------------------------------------------------------------- */

typedef struct {
    DateTime dt;                /* Date and Time                              */
    Duration dura;              /* Duration                                   */
    S32 ssOOSReqGr;             /* Subsystem out-of-service request granted   */
    S32 ssOOSReqDn;             /* Subsystem out-of-service request denied    */
    S32 msgTxBSS;               /* Msgs sent to backup subsystem              */
    S32 inCongDisc;             /* inbound msgs discarded due to congestion */
    S32 inCongRtnd;             /* inbound msgs returned due to congestion */
    S32 outCongDisc;            /* outbound msgs discarded due to congestion */
    S32 outCongRtnd;            /* outbound msgs returned due to congestion */
} SccpUSapStats;

/* --------------------------------------------------------------------------
 * Network SAP Statistics type definition:
 * -------------------------------------------------------------------------- */

typedef struct {
    DateTime dt;                /* Date and Time                              */
    Duration dura;              /* Duration                                   */
    S32 ssAllTx;                /* SS allowed transmitted                     */
    S32 ssOutGTx;               /* SS out of service grant transmitted        */
    S32 ssOutRTx;               /* SS out of service request transmitted      */
    S32 ssProhTx;               /* SS prohibited transmitted                  */
    S32 ssStatTx;               /* SS status test transmitted                 */
    S32 ssAllRx;                /* SS allowed received                        */
    S32 ssOutGRx;               /* SS out of service grant received           */
    S32 ssOutRRx;               /* SS out of service request received         */
    S32 ssProhRx;               /* SS prohibited received                     */
    S32 ssStatRx;               /* SS status test received                    */
    S32 connActive;             /* number of currently active connections     */
} SccpNSapStats;

/* --------------------------------------------------------------------------
 * User SAP Status type definition:
 * -------------------------------------------------------------------------- */
typedef struct {
    DateTime dt;
    S16 status;                 /* status */
    U8  inCongLevel;            /* inbound queue congestion level */
    U8  spare1;                 /* alignment */
} SccpUSapStatus;

#ifdef UNIX
#pragma pack()
#endif


/* --------------------------------------------------------------------------
 * Return Status Values for SCCP Management API:
 * -------------------------------------------------------------------------- */

#ifndef SCCP_SUCCESS
#define SCCP_SUCCESS       0      /* API completed successfully               */
#endif

#define SCCP_OVERRUN       0x1001 /* Data length too large to send            */
#define SCCP_UNDERRUN      0x1002 /* Received message too large               */
#define SCCP_UNBOUND       0x1003 /* Not bound to specified board             */
#define SCCP_BOARD         0x1004 /* Board number out of range                */
#define SCCP_DRIVER        0x1005 /* CPI driver reported an error             */
#define SCCP_NOMSG         0x1006 /* No event messages waiting                */
#define SCCP_NOTBOUND      0x1007 /* User failed to call SCCPBindTqst() first */
#define SCCP_RESOURCES     0x1008 /* Couldn't allocate msg buffer             */
#define SCCP_UNINIT        0x1009 /* User failed to call SccpMgmtInit() first */
#define SCCP_TOOMANY       0x100a /* Too many handles open for specified board*/
#define SCCP_INSTANCE      0x100b /* Instance ID out of range                 */
#define SCCP_TIMEOUT       0x100c /* No response from board                   */
#define SCCP_SWTYPE        0x100d /* Invalid switch type (i.e., protocol)     */
#define SCCP_PARAM         0x100e /* Invalid parameter                        */
#define SCCP_NOGENCFG      0x100f /* Board has not received SccpGenCfg yet    */
#define SCCP_NOTFOUND      0x1010 /* Specified address or route not found     */
#define SCCP_EXCEEDMAXCFG  0x1011 /* Insufficient resources allocated in gen  */
                                  /*   cfg for a USAP, NSAP, ROUTE or ADDRESS */
#define SCCP_INTERNAL      0x1012 /* An internal error occured.               */
#define SCCP_BUFLEN        0x1013 /* Address/mask too long to fit in buffer   */
                                  /*   or numConPc > conPcList array size     */
                                  /*   or numSsns > ssnList array size.       */
#define SCCP_BADDIGIT      0x1014 /* Address/mask contains an invalid digit   */
#define SCCP_MAXROUTES     0x1015 /* SccpGenCfg maxRtes is out of range       */
#define SCCP_NULLPTR       0x1016 /* A null pointer was passed as a parameter */
#define SCCP_TIMERVALUE    0x1017 /* An enabled timer has a value of 0        */
#define SCCP_HOPCOUNT      0x1018 /* Invalid hop count                        */
#define SCCP_POINTCODE     0x1019 /* Invalid point code                       */
#define SCCP_RANGE         0x101a /* An input field is out of range           */

/* --------------------------------------------------------------------------
 * SCCP Management API Function Prototypes:
 * -------------------------------------------------------------------------- */

typedef S16 SCCP_STATUS;                /* Status type returned by API        */

#ifdef __cplusplus
    extern "C" {
#endif

SCCP_STATUS TXSCCPMGMTFUNC SccpMgmtInit( U8 board, U8 srcEnt, U8 srcInst );
SCCP_STATUS TXSCCPMGMTFUNC SccpMgmtTerm( U8 board );

SCCP_STATUS TXSCCPMGMTFUNC SccpInitGenCfg( SccpGenCfg *pCfg );
SCCP_STATUS TXSCCPMGMTFUNC SccpSetGenCfg( U8 board, SccpGenCfg *pCfg );
SCCP_STATUS TXSCCPMGMTFUNC SccpGetGenCfg( U8 board, SccpGenCfg *pCfg );

SCCP_STATUS TXSCCPMGMTFUNC SccpInitUSapCfg( SccpUSapCfg *pCfg, S16 swType );
SCCP_STATUS TXSCCPMGMTFUNC SccpSetUSapCfg( U8 board, SccpUSapCfg *pCfg, U16 sapId );
SCCP_STATUS TXSCCPMGMTFUNC SccpGetUSapCfg( U8 board, SccpUSapCfg *pCfg, U16 sapId );

SCCP_STATUS TXSCCPMGMTFUNC SccpInitNSapCfg( SccpNSapCfg *pCfg, U16 sapId, U32 dpc, S16 swType );
SCCP_STATUS TXSCCPMGMTFUNC SccpSetNSapCfg( U8 board, SccpNSapCfg *pCfg, U16 sapId );
SCCP_STATUS TXSCCPMGMTFUNC SccpGetNSapCfg( U8 board, SccpNSapCfg *pCfg, U16 sapId );

SCCP_STATUS TXSCCPMGMTFUNC SccpInitAddrCfg( SccpAddrMapCfg *pCfg, U8 *pGtIn, U8 nBytes );
SCCP_STATUS TXSCCPMGMTFUNC SccpSetAddrCfg( U8 board, SccpAddrMapCfg *pCfg );
SCCP_STATUS TXSCCPMGMTFUNC SccpGetAddrCfg( U8 board, SccpAddrMapCfg *pCfg, U8 *pGtIn, U8 nBytes );
SCCP_STATUS TXSCCPMGMTFUNC SccpDelAddrCfg( U8 board, U8 *pGtIn, U8 nBytes );

SCCP_STATUS TXSCCPMGMTFUNC SccpInitRteCfg( SccpRouteCfg *pCfg, U32 dpc );
SCCP_STATUS TXSCCPMGMTFUNC SccpSetRteCfg( U8 board, SccpRouteCfg *pCfg );
SCCP_STATUS TXSCCPMGMTFUNC SccpGetRteCfg( U8 board, SccpRouteCfg *pCfg, U32 dpc );
SCCP_STATUS TXSCCPMGMTFUNC SccpDelRteCfg( U8 board, U32 dpc );

SCCP_STATUS TXSCCPMGMTFUNC SccpAlarmControl( U8 board, U8 level );
SCCP_STATUS TXSCCPMGMTFUNC SccpTraceControl( U8 board, U8 bTraceOn, U8 flags );

SCCP_STATUS TXSCCPMGMTFUNC SccpGetGenStats( U8 board, SccpGenStats *pStats, U8 bReset );
SCCP_STATUS TXSCCPMGMTFUNC SccpGetUSapStats( U8 board, SccpUSapStats *pStats, U16 sapId, U8 bReset );
SCCP_STATUS TXSCCPMGMTFUNC SccpGetNSapStats( U8 board, SccpNSapStats *pStats, U16 sapId, U8 bReset );

SCCP_STATUS TXSCCPMGMTFUNC SccpGetUSapStatus( U8 board, SccpUSapStatus *pStatus, U16 sapId );

SCCP_STATUS TXSCCPMGMTFUNC SccpAsciiNumToBcd(  char *pAscii, U8 *pBcdBuf, U32 nBcdBufLen, U32 *pnDigits );
SCCP_STATUS TXSCCPMGMTFUNC SccpAsciiMaskToBcd( char *pAscii, U8 *pBcdBuf, U32 nBcdBufLen, U32 *pnDigits );
SCCP_STATUS TXSCCPMGMTFUNC SccpBcdNumToAscii(  U8 *pBcd, U32 nDigits, char *pAsciiBuf, U32 nAsciiBufLen );
SCCP_STATUS TXSCCPMGMTFUNC SccpBcdMaskToAscii( U8 *pBcd, U32 nDigits, char *pAsciiBuf, U32 nAsciiBufLen );

#ifdef __cplusplus
    } /* extern "C" */
#endif

#endif /* !defined( _SCCPMAPI_H_) */
