/*****************************************************************************
******************************************************************************
**
**   tcapmapi.h
**
**      Constants, Structures, and Function prototype necessary for utilization
**      of the TCAP Management API.
**
*****************************************************************************/

/*************************************************************************
**                                                                      **
**                         PROPRIETARY NOTICE                           **
**                                                                      **
**                        Copyright (c) 1997, 2001                      **
**                      by Natural MicroSystems, Inc.                   **
**                                                                      **
**  The following is licensed program material and is considered        **
**  proprietary and confidential.  No part of this program may be       **
**  reproduced or used in any form or by any means without the express  **
**  written permission of Natural MicroSystems, Inc.                    **
**                                                                      **
*************************************************************************/

#ifndef _TCAPMAPI_H_
#define _TCAPMAPI_H_

/* define the calling conventions for the API functions for various
 * operating systems - NOTE: API callers should never define the
 * preprocessor constant "_TX_TCAPMAPI_SOURCE_"; this is only for use
 * by the TCAP MAPI source code itself.
 */

/* OS2: TCAP MAPI is a DLL */
#ifdef __OS2__
#ifdef _TX_TCAPMAPI_SOURCE_
    /* TCAP MAPI source definition */
#define     TXTCAPMGMTFUNC               extern _export _syscall
#else
    /* TCAP MAPI caller's definition */
#define     TXTCAPMGMTFUNC               _syscall
#endif  /* _TX_TCAPMAPI_SOURCE_ */

/* WIN32: TCAP MAPI is a DLL */
#elif  WIN32	                        /* WIN32 */
#ifdef _TX_TCAPMAPI_SOURCE_
    /* TCAP MAPI source definition */
#define     TXTCAPMGMTFUNC               __declspec( dllexport ) WINAPI
#else
    /* TCAP MAPI caller's definition */
#define     TXTCAPMGMTFUNC               WINAPI
#endif  /* _TX_TCAPMAPI_SOURCE_ */

/* all others: statically linked library */
#else
#define     TXTCAPMGMTFUNC
#endif

/* Turn on structure packing for Solaris */
#ifdef UNIX
#pragma pack(1)
#endif

#include "ss7type.h"

/* Return Codes */
#define TCAPM_SUCCESS   0
#define TCAPM_BOARD     1
#define TCAPM_DRIVER    2
#define TCAPM_UNINIT    3
#define TCAPM_INDEX     4
#define TCAPM_NOMSG     5
#define TCAPM_OVERFLOW  6
#define TCAPM_PARAM     7
#define TCAPM_TIMEOUT   8
#define TCAPM_FAILED    9
#define TCAPM_NULLPTR   10
#define TCAPM_TOOMANY   11
#define TCAPM_SWTYPE    12
#define TCAPM_RANGE     13

/* from task */
#define TCAPM_BADHDR    20      /* Error in Mgmt packet header */
#define TCAPM_CFGDUP    21      /* Duplicate General Configuration Request */
#define TCAPM_MAXSAPS   22      /* Configured maxSaps exceeds maximum */
#define TCAPM_BADPARAM  23      /* Parameter out of range (see alarm log) */
#define TCAPM_NOMEM     24      /* Unable to allocate sufficient memory */
#define TCAPM_RESOURCE  25      /* Internal resource error (see alarm log) */
#define TCAPM_BADSAP    26      /* Invalid/undefined SAP ID */

/* Flags values used for turning on/off buffer tracing */
#define TCAP_BUFTRACE_OFF   0x00
#define TCAP_BUFTRACE_ON    0x01

/* Configurable Alarm Levels */
#define TCAP_ALARMLVL_DIS       0   /* All alarms disabled */
#define TCAP_ALARMLVL_DFLT      1   /* (default) Significant & abnormal events logged */
#define TCAP_ALARMLVL_DEBUG     2   /* + Some normal events for troubleshooting */
#define TCAP_ALARMLVL_DETAIL    3   /* + Some detailed events for troubleshooting */

/* TCAP General configuration parameters structure */

typedef struct Tcap_Gen_Cfg
{
    S16 maxSaps;                /* Max Number of SCCP Saps (UPPER) */
    S16 maxDlgs;                /* Max number of dialogs; system-wide */
    S16 maxInvs;                /* Max number of invokes; system-wide */
    S16 timeRes;                /* Timer Resolution */
    PDesc smPst;                /* post structure for stack manager */
    PDesc stPstMate;            /* post structure for mate board */
    U8  alarmLvl;               /* alarm level */
    U8  minTidLen;              /* minimum transaction ID length (ITU only) */
    U8  haState;                /* high availability state */
    U8  mcState;                /* mate connection state */
    U8  traceData;              /* trace data flag */
    U8  fill;                   /* fill for alignment */
    /* low memory (msg buffer pool) thresholds trigger congestion onset levels;
     * specified as percentage [1..99] of pool memory available
     */
    U16 memThresh1;            /* % memory available => congestion level 1 */
    U16 memThresh2;            /* % memory available => congestion level 2 */
    U16 memThresh3;            /* % memory available => congestion level 3 */
} TcapGenCfg;

/* TCAP User SAP configuration structure */

typedef struct Tcap_Sap_Cfg
{
    S16 swtch;                  /* Protocol Switch */
#define TCAP_SW_ITU88     1     /* ITU 88 */
#define TCAP_SW_ITU92     2     /* ITU 92 */
#define TCAP_SW_ANS88     3     /* ANSI 88 */
#define TCAP_SW_ANS92     4     /* ANSI 92 */
#define TCAP_SW_ITU97     5     /* ITU 97 */
#define TCAP_SW_ANS96     6     /* ANSI 96 */

    U8 selectorUser;            /* selector for TCAP User */
    U8 spare1;                  /* spare for alignment */
    MemoryId memUser;           /* user memory region & pool id - not used */
    U8 priorUser;               /* priority - not used */
    U8 routeUser;               /* route - not used */
    U8 seqTimer;                /* duration to maintain SLS for sequential delivery */
    U8 selectorSP;              /* selector for SCCP */
    TimerCfg t1;                /* default invocation timer */
    TimerCfg t2;                /* wait for rejection timer */

    /* configuration parameters for lower SAP */
    MemoryId memSP;             /* memory region & pool id for SCCP - not used */
    U16 procIdSP;               /* processor Id - not used */
    U8 entSP;                   /* SCCP entity ID - always ENT_SCCP */
    U8 instSP;                  /* SCCP instance ID = board number */
    U8 priorSP;                 /* SCCP priority - not used */
    U8 routeSP;                 /* SCCP route - not used */
    S16 spIdSP;                 /* SCCP SAP ID for this TCAP SAP */
    U8  altParamLen;            /* Use alternate method of determining parameter length */
    U8 chkpt ;                  /* checkpoint value */
#define CHKPT_NONE  0
#define CHKPT_SEND  1
#define CHKPT_ALL   2
    U8 addrOverride;            /* override SCCP address */
    U8 allowInvkEnd;            /* allow invoke End msg */
    TimerCfg inactvTimer;       /* Inactivity Timer */

    /* user queue length thresholds trigger inbound congestion onset levels;
     * specified as absolute number of buffers on user queue, in addition
     * to the 16 that may be pending in the driver.
     */
    S16 qThresh1;               /* messages on queue => congestion level 1 */
    S16 qThresh2;               /* messages on queue => congestion level 2 */
    S16 qThresh3;               /* messages on queue => congestion level 3 */
    U16 spare2;                 /* spare for alignment */
} TcapSapCfg;


/* The following event structure included in some TCAP SAP statistics inclues both
 * a count and the time (in hundreths of a second since system boot).
 */
typedef struct Tcap_Ev_Cnt      /* TCAP count and 1st occurrence of events */
{
   S32 cnt;                     /* event count */
   U32 first;                   /* when it first happened */
} TcapEvCnt;

/* High Availability State definitions */
#define ST_HAST_STARTING    0
#define ST_HAST_STANDALONE  1
#define ST_HAST_PRIMARY     2
#define ST_HAST_BACKUP      3

/* Mate Connection State definitions */
#define ST_MCST_ISOLATED    0
#define ST_MCST_CONNECTED   1

/* TCAP General statistics structure */
typedef struct TCAP_Gen_Stats
{
   U8    haSt;                  /* high availability state */
   U8    mcSt;                  /* mate connection state */
   U8    fill;                  /* fill for alignment */
   U8    fill2;                 /* fill for alignment */
} TcapGenStatus;

/* TCAP SAP statistics structure */
typedef struct Tcap_Sap_Stats
{
   S16 swtch;                   /* protocol variant switch */
   S16 fill;                    /* fill for alignment */
   S32 openTrans;               /* number of open transactions */
   S32 frmTx;                   /* frames transmitted */
   S32 invTx;                   /* invoke components transmitted */
   S32 resTx;                   /* result components transmitted */
   S32 rejTx;                   /* reject components transmitted */
   S32 errTx;                   /* error components transmitted */
   S32 uniTx;                   /* unidirectional messages transmitted */
   S32 beginTx;                 /* begin messages transmitted */
   S32 contTx;                  /* continue messages transmitted */
   S32 endTx;                   /* end messages transmitted */
   S32 abortTx;                 /* abort messages transmitted */
   S32 qryPrmTx;                /* query with permission transmitted */
   S32 qryNoPrmTx;              /* query without permission transmitted */
   S32 conPrmTx;                /* conversation with permission transmitted */
   S32 conNoPrmTx;              /* conversation without permission transmitted */
   S32 respTx;                  /* response transmitted */
   S32 frmRx;                   /* frames received */
   S32 invRx;                   /* invoke components received */
   S32 resRx;                   /* result components received */
   S32 rejRx;                   /* reject components received */
   S32 errRx;                   /* error components received */
   S32 uniRx;                   /* unidirectional messages received */
   S32 beginRx;                 /* begin messages received */
   S32 contRx;                  /* continue messages received */
   S32 endRx;                   /* end messages received */
   S32 abortRx;                 /* abort messages received */
   S32 qryPrmRx;                /* query wiRh permission received */
   S32 qryNoPrmRx;              /* query without permission received */
   S32 conPrmRx;                /* conversation with permission received */
   S32 conNoPrmRx;              /* conversation without permission received */
   S32 respRx;                  /* response received */
   S32 drop;                    /* frames dropped */
   TcapEvCnt urPkg;             /* unrecognized package type */
   TcapEvCnt inTrn;             /* incorrect transaction portion */
   TcapEvCnt bdTrn;             /* badly structured transaction portion */
   TcapEvCnt urTrn;             /* unrecognized transaction ID */
   TcapEvCnt prTrn;             /* permission to release problem */
   TcapEvCnt ruTrn;             /* resource unavailable */
   TcapEvCnt urCmp;             /* general - unrecognized component */
   TcapEvCnt inCmp;             /* general - incorrect component portion */
   TcapEvCnt bdCmp;             /* general - badly structured component prtn */
   TcapEvCnt dupId;             /* invoke - duplicate Invoke Id */
   TcapEvCnt urOp;              /* invoke - unrecognized operation code */
   TcapEvCnt inPrm;             /* invoke - incorrect parameters */
   TcapEvCnt iurId;             /* invoke - unrecognized correlation ID */
   TcapEvCnt rurId;             /* return result - unrecognize correlation ID*/
   TcapEvCnt uxRes;             /* return result - unexpected return result */
   TcapEvCnt eurId;             /* return error - unrecognized correlation ID*/
   TcapEvCnt uxRer;             /* return error - unexpected return error */
   TcapEvCnt urErr;             /* return error - unrecognized error code */
   TcapEvCnt uxErr;             /* return error - enexpected error */
   TcapEvCnt enPrm;             /* return error - incorrect parameter */
   /* Congestion control counts */
   S32  outCongAbort;           /* outbound transactions refused due to cong. */
   S32  outCongDisc;            /* outbound msgs discarded due to cong. */
   S32  inbCongAbort;           /* inbound transactions aborted due to cong. */
   S32  inbCongDisc;            /* outbound msgs discarded due to cong. */
   U8   currInbCongLvl;         /* current inbound congestion level [0..3]*/
   U8   currOutbCongLvl;        /* currrent outbound congestion level [0..3] */
   U16  spare1;                 /* spare for alignment */
} TcapSapStats;


#ifdef UNIX
#pragma pack()
#endif

/* function prototypes */
#ifdef __cplusplus
extern "C" {
#endif

S16 TXTCAPMGMTFUNC TCAPInitMgmtAPI( U8 board, U8 srcEnt, U8 srcInst );
S16 TXTCAPMGMTFUNC TCAPTermMgmtAPI(U8 board);
S16 TXTCAPMGMTFUNC TCAPInitGenCfg(TcapGenCfg *cfg );
S16 TXTCAPMGMTFUNC TCAPGenCfg(U8 board, TcapGenCfg *cfg);
S16 TXTCAPMGMTFUNC TCAPGetGenCfg(U8 board, TcapGenCfg *cfg);
S16 TXTCAPMGMTFUNC TCAPInitSapCfg( U8 board, S16 spId, S16 swProt, TcapSapCfg *cfg);
S16 TXTCAPMGMTFUNC TCAPSapCfg(U8 board, TcapSapCfg *cfg, U16 sapId);
S16 TXTCAPMGMTFUNC TCAPGetSapCfg(U8 board, TcapSapCfg *cfg, U16 sapId);
S16 TXTCAPMGMTFUNC TCAPAlarmControl(U8 board, U8 alarmLvl);
S16 TXTCAPMGMTFUNC TCAPTraceControl( U8 board, U32 flags );
S16 TXTCAPMGMTFUNC TCAPSapStats(U8 board, S16 sapId, TcapSapStats *stats, U8 reset);
S16 TXTCAPMGMTFUNC TCAPGenStatus(U8 board, TcapGenStatus *status);

#ifdef __cplusplus
}
#endif

#endif /* _TCAPMAPI_H_ */

