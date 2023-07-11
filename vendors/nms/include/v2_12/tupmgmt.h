/*************************************************************************
**                                                                      **
**                         PROPRIETARY NOTICE                           **
**                                                                      **
**                         Copyright (c) 1997                           **
**                          by NMS, Inc.                                **
**                                                                      **
**  The following is licensed program material and is considered        **
**  proprietary and confidential.  No part of this program may be       **
**  reproduced or used in any form or by any means without the express  **
**  written permission of TEKnique, Inc.                                **
**                                                                      **
*************************************************************************/

#ifndef _TUPMGMT_H_
#define _TUPMGMT_H_

/* define the calling conventions for the API functions for various
 * operating systems - NOTE: API callers should never define the
 * preprocessor constant "_TX_SCCP_SOURCE_"; this is only for use
 * by the SCCP API source code itself.
 */

/* OS2: SCCP API is a DLL */
#ifdef __OS2__
#ifdef _TX_TUPMGMT_SOURCE_
    /* TUP management API source definition */
#define     TXTUPMGMTFUNC               extern _export _syscall
#else
    /* TUP management API caller's definition */
#define     TXTUPMGMTFUNC               _syscall
#endif  /* _TX_TUPMGMT_SOURCE_ */

/* WIN32: TUP management API is a DLL */
#elif  WIN32                            /* WIN32 */
#ifdef _TX_TUPMGMT_SOURCE_
    /* TUP management API source definition */
#define     TXTUPMGMTFUNC               __declspec( dllexport ) WINAPI
#else
    /* TUP management API caller's definition */
#define     TXTUPMGMTFUNC               WINAPI
#endif  /* _TX_TUPMGMT_SOURCE_ */

/* all others: statically linked library */
#else
#define     TXTUPMGMTFUNC
#endif

/* Turn on structure packing for Solaris */
#ifdef __sun
#pragma pack(1)
#endif

#define MAX_GLT_SZ          32
#define MAX_DATA_SZ         1200
#define EXTADDRLEN          16

#define ORGNETWORK          0x00        /* network originatied              */
#define ORGENDUSER          0x01        /* user originatied                 */

/* API return values */
#define TUP_SUCCESS         0           /* API call was successful          */
#define TUP_OVERRUN         0x1001      /* data length too large to send    */
#define TUP_UNDERRUN        0x1002      /* received message too large       */
#define TUP_UNBOUND         0x1003      /* not bound to specified board     */
#define TUP_BOARD           0x1004      /* board number out of range        */
#define TUP_DRIVER          0x1005      /* CPI driver returned error        */
#define TUP_NOMSG           0x1006      /* No event messages waiting        */
#define TUP_NOTBOUND        0x1007      /* User failed to call              */
#define TUP_FAILED          0x1008      /* request failed                   */


#ifndef MAXSSNS
#define MAXSSNS             8           /* Max Subsystems allowed per Dpc */
#endif

#ifndef MAXDPC
#define MAXDPC              16          /* Max Concerned Point Code per Dpc */
#endif

#ifndef TUPADDRLEN
#define TUPADDRLEN          20          /* Address Mask Length */
#endif

/* Switch types for NSaps, USAPs, addresses, & routes -
    defines protocol behavior */
#define TUP_SW_ITU          1           /* ITUT - General */
#define TUP_SW_CHN          2           /* CHINA - General */

/* Network SAP Types */
#define TUP_SAP_MTP         0
#define TUP_SAP_SCCP        1

/* Subservice Types */
#define SSF_INTL    0
#define SSF_SPARE   1
#define SSF_NAT     2
#define SSF_RES     3

/* Blocking/Unblocking Types */
#define TUP_MBLOCK              8           /* Maintenance Block */
#define TUP_SBLOCK              9           /* Software Block */
#define TUP_HBLOCK             10           /* Hardware Block */
#define TUP_MUNBLOCK           11           /* Maintenance Unblock */
#define TUP_SUNBLOCK           12           /* Software Unblock */
#define TUP_HUNBLOCK           13           /* Hardware Unblock */

/* Event codes for configuration requests */
#define TUP_CFGREQ      0x3c            /* Configuration request */

#define TUP_GEN_CFG     1               /* general Parameters */
#define TUP_USAP_CFG    34              /* TUP User SAP */
#define TUP_NSAP_CFG    3               /* network SAP */
#define TUP_ROUT_CFG    10              /* route configuration*/
#define TUP_ROUT_DEL    30              /* delete route */
#define TUP_CIRC_CFG    35              /* address mapping cofiguration */

/* Resolution for all TUP timers */
#define TUP_TIMER_RES   10              /* 10 ticks/second */

/* Selector value for TUP upper (application) and lower (MTP3) interfaces */
#define TUP_SEL_LC      0               /* loose coupling */

/* route status values */
#define TUP_ONLINE      0x01            /* Destination is accessible        */
#define TUP_CONG        0x02            /* Destination is congested (this   */
                                        /* status is reported back by TUP  */
                                        /* to application and not be set by */
                                        /* application)                     */
#define TUP_TRANS       0x04            /* This signalling point is a       */
                                        /* translator node                  */
#define TUP_ADJACENT    0x08            /* This signalling point is         */
                                        /* adjacent for TUP point code &   */
                                        /* subsystem management procedures  */

/* Status values for route configuration subsystem list */
#define TUP_SNR         0x01            /* Subsystem is normal routed (not  */
                                        /* backup routed)                   */
#define TUP_ACC         0x02            /* This subsystem is accessible     */

/* TUP routing types for address map tables */
#define ROUTE_GLT           0x00        /* route using global title only    */
#define ROUTE_PC_SN         0x01        /* route usint point code + SSN     */

/* national/international address indicator values for address translations */
#define ADDRIND_NAT         0x00        /* National address indicator       */
#define ADDRIND_INT         0x01        /* International address indicator  */

/* encoding scheme values */
#define ENC_UNKNOWN         0x00        /* Encoding unknown                 */
#define ENC_BCD_ODD         0x01        /* BCD, odd number of digits        */
#define ENC_BCD_EVEN        0x02        /* BCD, even number of digits       */

/* numbering plan values */
#define NP_UNK              0x00        /* unknown                          */
#define NP_ISDN             0x01        /* ISDN/telephony - E.164/E.163     */
#define NP_TEL              0x02        /* telephony numbering - E.163      */
#define NP_DATA             0x03        /* data numbering - X.121           */
#define NP_TELEX            0x04        /* telex numbering - Recomm. F.69   */
#define NP_MARITIME         0x05        /* Maritime mobile numbering        */
#define NP_LANDMOB          0x06        /* Land mobile numbering            */
#define NP_ISDNMOB          0x07        /* ISDN/mobile numbering            */
#define NP_NATIONAL         0x08        /* national standard numbering      */
#define NP_PRIVATE          0x09        /* private numbering                */
#define NP_EXT              0x0F        /* reserved for extension           */

/* nature of address indicator values */
#define NATIND_SUBS         0x01        /* Subscriber number                */
#define NATIND_NATL         0x03        /* national number                  */
#define NATIND_INTNATL      0x04        /* international number             */

typedef struct _TUPAddr         /* TUP address (global title digits) */
{
   U8 length;                   /* length bytes */
   U8 string[TUPADDRLEN];       /* address value - ASCII hex digits */

#if !(TUPADDRLEN % 2)
   U8 fill;                     /* alignment */
#endif

} TUPAddr;


/* group configuration structure */

typedef struct _TUPGrpCfg
{
    U32         dpc;                    /* destination pointcode */
    U16         cic;                    /* start circuit id code */
    U32         circId;                 /* circuit ID of first circuit in group */
    U16         groupId;
    U8          range;
    U8          fill;
    U16         count;                  /* number of circuits in group */
    TimerCfg    t20;
    TimerCfg    t21;
    TimerCfg    t22;
    TimerCfg    t23;
    TimerCfg    t24;
    TimerCfg    t25;
    TimerCfg    t26;
    TimerCfg    t27;
    TimerCfg    t28;
    TimerCfg    t29;
    TimerCfg    t30;
    TimerCfg    t31;
    TimerCfg    t32;
    TimerCfg    t33;
    TimerCfg    t34;
    TimerCfg    t35;
    TimerCfg    t36;
    TimerCfg    t37;
    TimerCfg    t38;
    TimerCfg    t39;
    TimerCfg    t40;
    TimerCfg    t41;

} TUPGrpCfg;

/* general configuration parameters */


typedef struct _TUPGenParms
{
    U16         maxSaps;                /* Max Number of TUP User Saps */
    U16         maxNetSaps;             /* Max Number of Network Saps (MTP3) */
    U32         maxCircuits;            /* Max Number of Circuits */
    U16         maxCircGrp;             /* Max Number of Circuit Groups */
    U16         maxRoutes;              /* Max Number of Routes */
    U16         alarmLevel;             /* Alarm level */
    S16         poolUpper;
    S16         poolLower;
    S16         timerRes;                /* Timer resolution */
    TUPGrpCfg   dfltGrpCfg;
    PDesc       stkMgr;
} TUPGenParms;

/* upper sap configuration structure */

typedef struct _TUPUSapCfg
{
    S16         switchType;             /* ITU-T or CHINA */
} TUPUSapCfg;

/* network sap configuration structure */

typedef struct _TUPNSapCfg     /* TUP Network Sap Config. struct (LOWER) */
{
    S16         spId;               /* Sap ID of this NSap layer */
    S16         mtpSpId;            /* Sap ID of MTP layer */
    S16         switchType;         /* ITU-T or CHINA */
    U8          ssf;                /* Sub-service field */
    U8          priority;           /* Msg priority to MTP layer */
    U32         orgPointCode;       /* Local point code */
    U8          traceInd;           /* trace indicator: non zero - trace enabled */
} TUPNSapCfg;

/* circuit configuration structure */

typedef struct _TUPCircCfg
{
    U32         circuitId;              /* circuit id code */
    U16         cic;                    /* cic */
    U32         dstPointCode;           /* destination point code */
    U16         groupId;                /* group ID */
    U16         numCircs;               /* number of circuits in the group */
    S16         switchType;             /* ITU-T or CHINA */
    U16         nsapId;                 /* nsap Identification */

    TimerCfg    t1;                     /* t1 timer - release sent */
    TimerCfg    t2;                     /* t2 timer - suspend received */
    TimerCfg    t3;                     /* t3 timer - */
    TimerCfg    t4;                     /* t4 timer - */
    TimerCfg    t5;                     /* t5 timer - initial release sent */
    TimerCfg    t6;                     /* t6 timer - suspend received */
    TimerCfg    t7;                     /* t7 timer - latest address sent */
    TimerCfg    t8;                     /* t8 timer - initial address received */
    TimerCfg    t9;                     /* t9 timer - latest address sent after ACM */
    TimerCfg    t10;                    /* t10 timer - */

    TimerCfg    t11;                    /* t11 timer -  */
    TimerCfg    t12;                      /* t12 timer - blocking sent */
    TimerCfg    t13;                      /* t13 timer - initial blocking sent */
    TimerCfg    t14;                      /* t14 timer - unblocking sent */
    TimerCfg    t15;                      /* t15 timer - initial unblocking sent */
    TimerCfg    t16;                    /* t16 timer -  */
    TimerCfg    t17;                    /* t17 timer -  */
    TimerCfg    t18;
    TimerCfg    t19;
} TUPCircCfg;


/* route configuration structure */

typedef struct _TUPRouteCfg
{
    TUPAddr     address;            /* address */
    S16         numDstPointCode;    /* # of Dpc leading to a specific rout */
    struct
        {
        U32   dstPointCode;         /* destination point code */
        Bool  TUPAvail;             /* TUP available */
        U8    priority;             /* priority */
        } dst[MAXDPC];
    Bool        loadShare;          /* load sharing indication */
    U8          fill1;
} TUPRouteCfg;

/* sap statistics structure */

typedef struct _TUPUSapStats
{
   S32 OOSReqGr;  /* Subsystem out-of-service request granted */
   S32 OOSReqDn;  /* Subsystem out-of-service request denied */
   S32 TxBackup;  /* msgs sent to backup subsystem */

} TUPUSapStats;

/* Circuit status structure */

typedef struct _TUPCircStatus         /* TUP Circuit status */
{
   DateTime dt;                     /* date and time */
   U16      circuitState;           /* circuit transient state */
   U16      callState;              /* circuit call processing state */

} TUPCircStatus;

/* Group status structure */

typedef struct _TUPGrpStatus         /* TUP Circuit status */
{
    DateTime    dt;                     /* date and time */
    U32         dpc;
    U16         cic;
    U8          range;
    U8          fill;
    U16         count;
    U8          locHMask[32];
    U8          locMMask[32];
    U8          locSMask[32];
    U8          remHMask[32];
    U8          remMMask[32];
    U8          remSMask[32];
} TUPGrpStatus;

/* transient states */

#define IDLE              0      /* idle */
#define UNEQUIP           1      /* unequipped */
#define LOCBLKED          2      /* locally blocked */
#define BLKACK            3      /* waiting for blocking ack */
#define UNBLKACK          4      /* waiting for unblocking ack */
#define LOCBLKRSP         5      /* locally blocked, waiting for blocking
                                    response */
#define LOCUNBLKRSP       6      /* locally blocked, waiting for unblocking
                                    response */
#define RMTBLKACK         7      /* remotely blocked, waiting for blocking
                                    ack */
#define RMTUNBLKACK       8      /* remotely blocked, waiting for unblocking
                                    ack */
#define LOCRMTBCKED       9      /* locally and remotely blocked */
#define BLKACKRSP         10     /* waiting for blocking ack and blocking
                                    response */
#define UNBLKACKUNRSP     11     /* waiting for unblocking ack and unblocking
                                    response */
#define BLKACKUNRSP       12     /* waiting for blocking ack and unblocking
                                    response */
#define UNBLKACKRSP       13     /* waiting for unblocking ack and blocking
                                    response */
#define BLKRSP            14     /* waiting for blocking response */
#define UNBLKRSP          15     /* waiting for unblocking response */
#define RMTBLKED          16     /* remotely blocked */

/* call processing states */

#define CALL_IDLE         0x0c   /* idle */
#define INCBUSY           0x04   /* incoming busy */
#define OUTBUSY           0x08   /* outgoing busy */
#define TRANS             0x00   /* transient */
#define COTCHK            0x01   /* continuity check  */

/* Circuit statistics structure */

typedef struct _TUPCircStats
{
   DateTime dt;           /* date and time */
   Duration dura;         /* duration */
   S32  blockTx;                /* Circuit Blocking Transmitted */
   S32  blockAckTx;             /* Circuit Blocking Ack Transmitted */
   S32  unblockTx;              /* Circuit Unblocking Transmitted */
   S32  unblockAckTx;           /* Circuit Unblocking Ack Transmitted */
   S32  cirResTx;               /* Circuit Reset Transmitted */
   S32  adrCmpltTx;             /* Address complete transmitted */
   S32  answerTx;               /* Answer transmitted */
   S32  contiTx;                /* Continuity transmitted */
   S32  conChkReqTx;            /* Continuity Check Request transmitted */
   S32  ccfTx;                  /* Continuity Check Failure transmitted */
   S32  fotTx;                  /* Forward transmitted */
   S32  clfTx;                  /* Release transmitted */
   S32  cclTx;                  /* Caller clear transmitted */
   S32  rlgTx;                  /* Release Complete transmitted */
   S32  cbkTx;                  /* clear back transmitted */
   S32  ranTx;                  /* Reanswer transmitted */
   S32  oprTx;                  /* operator transmitted */
   S32  mpmTx;                  /* meter pulse transmitted */
   S32  accTx;                  /* auto cong level transmitted */
   S32  ubmTx;                  /* UBM transmitted, including SLB and STB */
   S32  initAdrTx;              /* Initial Address transmitted */
   S32  infoTx;                 /* Info transmitted */
   S32  infoReqTx;              /* Info Request transmitted */
   S32  subsAdrTx;              /* Subsequent Address transmitted */
   S32  malTx;                  /* Malicious Call Print transmitted */
   S32  chargeTx;               /* Charge transmitted */


   S32  blockRx;                /* Circuit Blocking Received */
   S32  blockAckRx;             /* Circuit Blocking Ack Received */
   S32  unblockRx;              /* Circuit Unblocking Received */
   S32  unblockAckRx;           /* Circuit Unblocking Ack Received */
   S32  cirResRx;               /* Circuit Reset Received */
   S32  adrCmpltRx;             /* Address complete received */
   S32  answerRx;               /* Answer received */
   S32  contiRx;                /* Continuity received */
   S32  conChkReqRx;            /* Continuity Check Request received */
   S32  ccfRx;                  /* Continuity Check Failure received */
   S32  fotRx;                  /* Forward received */
   S32  clfRx;                  /* Release received */
   S32  cclRx;                  /* Caller clear received */
   S32  rlgRx;                  /* Release Complete received */
   S32  cbkRx;                  /* clear back received */
   S32  ranRx;                  /* Reanswer received */
   S32  oprRx;                  /* operator received */
   S32  mpmRx;                  /* meter pulse received */
   S32  accRx;                  /* auto cong level received */
   S32  ubmRx;                  /* UBM received, including SLB and STB */
   S32  initAdrRx;              /* Initial Address received */
   S32  infoRx;                 /* Info received */
   S32  infoReqRx;              /* Info Request received */
   S32  subsAdrRx;              /* Subsequent Address received */
   S32  malRx;                  /* Malicious Call Print received */
   S32  chargeRx;               /* Charge received */
} TUPCircStats ;

/* lower sap statistics structure */

typedef struct _TUPNSapStats
{
   DateTime dt;           /* date and time */
   Duration dura;         /* duration */
   S32      pktTx;
   S32      pktRx;
} TUPNSapStats;

typedef struct _TUPGrpStats
{
   DateTime dt;           /* date and time */
   Duration dura;         /* duration */
   S32  cirHwGrBlockRx;         /* HW Circuit Group Blocking Received */
   S32  cirHwGrBlockAckRx;      /* HW Circuit Group Blocking Ack Received */
   S32  cirHwGrUnBlockRx;       /* HW Circuit Group Unblocking Received */
   S32  cirHwGrUnBlockAckRx;    /* HW Circuit Group Unblocking Ack Received */
   S32  cirSwGrBlockRx;         /* SW Circuit Group Blocking Received */
   S32  cirSwGrBlockAckRx;      /* SW Circuit Group Blocking Ack Received */
   S32  cirSwGrUnBlockRx;       /* SW Circuit Group Unblocking Received */
   S32  cirSwGrUnBlockAckRx;    /* SW Circuit Group Unblocking Ack Received */
   S32  cirMGrBlockRx;          /* Maint Circuit Group Blocking Received */
   S32  cirMGrBlockAckRx;       /* Maint Circuit Group Blocking Ack Received */
   S32  cirMGrUnBlockRx;        /* Maint Circuit Group Unblocking Received */
   S32  cirMGrUnBlockAckRx;     /* Maint Circuit Group Unblocking Ack Received */
   S32  cirGrResRx;             /* Circuit Group Reset Received */
   S32  cirGrResAckRx;          /* Circuit Group Reset Ack Received */
   S32  cirHwGrBlockTx;         /* HW Circuit Group Blocking Received */
   S32  cirHwGrBlockAckTx;      /* HW Circuit Group Blocking Ack Received */
   S32  cirHwGrUnBlockTx;       /* HW Circuit Group Unblocking Received */
   S32  cirHwGrUnBlockAckTx;    /* HW Circuit Group Unblocking Ack Received */
   S32  cirSwGrBlockTx;         /* SW Circuit Group Blocking Received */
   S32  cirSwGrBlockAckTx;      /* SW Circuit Group Blocking Ack Received */
   S32  cirSwGrUnBlockTx;       /* SW Circuit Group Unblocking Received */
   S32  cirSwGrUnBlockAckTx;    /* SW Circuit Group Unblocking Ack Received */
   S32  cirMGrBlockTx;          /* Maint Circuit Group Blocking Received */
   S32  cirMGrBlockAckTx;       /* Maint Circuit Group Blocking Ack Received */
   S32  cirMGrUnBlockTx;        /* Maint Circuit Group Unblocking Received */
   S32  cirMGrUnBlockAckTx;     /* Maint Circuit Group Unblocking Ack Received */
   S32  cirGrResTx;             /* Circuit Group Reset Received */
   S32  cirGrResAckTx;          /* Circuit Group Reset Ack Received */
} TUPGrpStats;

#ifdef __sun
#pragma pack()
#endif

#ifdef __cplusplus
extern "C" {
#endif
/* #ifndef _TX_TUPMGMT_SOURCE_  Why was this here ???? */
S16  TXTUPMGMTFUNC TUPInitMgmtAPI(U8 board, U8 srcEnt);
S16  TXTUPMGMTFUNC TUPTermMgmtAPI(U8 board);
void TXTUPMGMTFUNC TUPInitGenCfg(TUPGenParms *cfg);
S16  TXTUPMGMTFUNC TUPSetGenCfg(U8 board, TUPGenParms *cfg);
S16  TXTUPMGMTFUNC TUPGetGenCfg(U8 board, TUPGenParms *cfg);

void TXTUPMGMTFUNC TUPInitUSapCfg(TUPUSapCfg *cfg);
S16  TXTUPMGMTFUNC TUPSetUSapCfg(U8 board, TUPUSapCfg *cfg, U16 sapId);
S16  TXTUPMGMTFUNC TUPGetUSapCfg(U8 board, TUPUSapCfg *cfg, U16 sapId);

void TXTUPMGMTFUNC TUPInitNSapCfg(TUPNSapCfg *cfg, S16 spId,
                                  S16 mtpSpId, U32 opc);
S16  TXTUPMGMTFUNC TUPSetNSapCfg(U8 board, TUPNSapCfg *cfg);
S16  TXTUPMGMTFUNC TUPGetNSapCfg(U8 board, TUPNSapCfg *cfg, S16 spId);

void TXTUPMGMTFUNC TUPInitCircCfg(TUPCircCfg *cfg, U32 circId, U32 dpc);
S16  TXTUPMGMTFUNC TUPSetCircCfg(U8 board, TUPCircCfg *cfg, S16 spId);
S16  TXTUPMGMTFUNC TUPGetCircCfg(U8 board, TUPCircCfg *cfg, U32 circId);

void TXTUPMGMTFUNC TUPInitRouteCfg(TUPRouteCfg *cfg);
S16  TXTUPMGMTFUNC TUPSetRouteCfg(U8 board, TUPRouteCfg *cfg, S16 spId);

void TXTUPMGMTFUNC TUPInitGrpCfg(TUPGrpCfg *cfg, U16 Count);
S16  TXTUPMGMTFUNC TUPGetGrpCfg(U8 board, TUPGrpCfg *cfg, U16 groupId);
S16  TXTUPMGMTFUNC TUPGetRouteCfg(U8 board, TUPRouteCfg *cfg, S16 spId);
S16  TXTUPMGMTFUNC TUPGetGrpStatus(U8 board, U16 groupId, TUPGrpStatus *status);
S16  TXTUPMGMTFUNC TUPGetGrpStats(U8 board, U16 groupId, TUPGrpStats *stats, U8 reset);

S16  TXTUPMGMTFUNC TUPResetCircuit(U8 board, U32 circId);
S16  TXTUPMGMTFUNC TUPBlockCircuit(U8 board, U32 circId);
S16  TXTUPMGMTFUNC TUPUnblockCircuit(U8 board, U32 circId);
S16  TXTUPMGMTFUNC TUPDeleteCircuit(U8 board, U32 circId, U16 count);

S16  TXTUPMGMTFUNC TUPResetGroup(U8 board, U16 groupId);
S16  TXTUPMGMTFUNC TUPDeleteGroup(U8 board, U16 groupId);
S16  TXTUPMGMTFUNC TUPBlockGroup(U8 board, U16 groupId, U8 blockType);
S16  TXTUPMGMTFUNC TUPUnblockGroup(U8 board, U16 groupId, U8 blockType);

S16  TXTUPMGMTFUNC TUPStatusControl(U8 board, S16 state);
S16  TXTUPMGMTFUNC TUPTraceControl(U8 board, U32 flags);
S16  TXTUPMGMTFUNC TUPAlarmControl(U8 board, U32 flags);
S16  TXTUPMGMTFUNC TUPGetNSapStats(U8 board, S16 sapId, TUPNSapStats *stats, U8 reset);
S16  TXTUPMGMTFUNC TUPGetCircStats(U8 board, U32 circId, TUPCircStats *stats, U8 reset);
S16  TXTUPMGMTFUNC TUPGetCircStatus(U8 board, U32 circId, TUPCircStatus *status);

S16  TXTUPMGMTFUNC TUPQuietReset(U8 board);
#ifdef   __cplusplus
}
#endif

/* #endif */

#endif /* _TUPMGMT_H_ */
