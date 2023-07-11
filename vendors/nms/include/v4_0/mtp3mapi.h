/*************************************************************************
**                                                                      **
**                         PROPRIETARY NOTICE                           **
**                                                                      **
**                         Copyright (c) 1997                           **
**                       by Natural MicroSystems                        **
**                                                                      **
**  The following is licensed program material and is considered        **
**  proprietary and confidential.  No part of this program may be       **
**  reproduced or used in any form or by any means without the express  **
**  written permission of Natural MicroSystems                          **
**                                                                      **
*************************************************************************/

#ifndef _MTP3MAPI_H_
#define _MTP3MAPI_H_

#include "ss7type.h"
#include "txcpi.h"

/* define the calling conventions for the API functions for various
 * operating systems - NOTE: API callers should never define the
 * preprocessor constant "_TX_MTP3_SOURCE_"; this is only for use
 * by the MTP3 API source code itself.
 */

/* OS2: MTP3 API is a DLL */
#ifdef __OS2__
#ifdef _TX_MTP3_SOURCE_
	/* MTP3 API source definition */
#define     TXMTP3FUNC               extern _export _syscall
#else
	/* MTP3 API caller's definition */
#define     TXMTP3FUNC               _syscall
#endif	/* _TX_MTP3_SOURCE_ */

/* WIN32: MTP3 API is a DLL */
#elif  WIN32	                        /* WIN32 */
#ifdef _TX_MTP3_SOURCE_
	/* MTP3 API source definition */
#define     TXMTP3FUNC               __declspec( dllexport ) WINAPI
#else
	/* MTP3 API caller's definition */
#define     TXMTP3FUNC               WINAPI
#endif	/* _TX_MTP3_SOURCE_ */

/* all others: statically linked library */
#else
#define     TXMTP3FUNC
#endif

#ifdef UNIX
#ifndef TRUE
#define TRUE  1
#define FALSE 0
#endif
#endif

/* Timer resolutions */
#define RES_TENTHS  1       /* These are also used as multipliers in MTP3CFG */
#define RES_SECONDS 10      /* Important that these remain one and ten */

/* Macro for initializing a timer (value 0 => disable) */
#define MTP3_SET_TIMER( atimer, avalue )                    \
    atimer.value = avalue;                                  \
    if( atimer.value != 0 )                                 \
        atimer.enable = 1;                                  \
    else                                                    \
        atimer.enable = 0;

/* Constants */

#ifndef MTP_MAX_LINKS
#define MTP_MAX_LINKS            32
#endif

#define MTP3LNKTSTMAX   16      /* Max size of link test pattern */
#define MTP3MAXMASKS    8       /* Max number of routing masks */
#define MTP3MAXCMBLNK   256     /* Max number of combined link sets (routes per linkset) */

/* Signalling point types */
#define MTP3TYPE_SP     0       /* signalling point without transfer function */
#define MTP3TYPE_STP    1       /* signalling transfer point */

/* Link types */
#define MTP3LNK_DEFAULT           0   /* link type for management message */
#define MTP3LNK_ANSI              1   /* link type ANSI */
#define MTP3LNK_CCITT             2   /* link type CCITT */
#define MTP3LNK_ANSI88            3   /* link type ANSI 88 */
#define MTP3LNK_JNTT              7   /* link type Japan (NTT variant) */
#define MTP3LNK_JTTC              8   /* link type Japan (TTC variant) */

/* Subservice selections */
#define MTP3SSF_INTL              0       /* international */
#define MTP3SSF_SPARE             1       /* spare */
#define MTP3SSF_NAT               2       /* national */
#define MTP3SSF_RES               3       /* reserved */

/* Routing directions */
#define MTP3_RTE_DN             1   /* down / outbound route */
#define MTP3_RTE_UP             2   /* up   / inbound route  */

/* Control Request codes */
#define MTP3_CTRL_ALARM_ENA		101	/* Enable Alarms */
#define MTP3_CTRL_ALARM_DIS		102	/* Disable Alarms */
#define MTP3_CTRL_FLOWCTL_ON	103	/* Start flow control */
#define MTP3_CTRL_FLOWCTL_OFF	104	/* Flow Control off */
#define MTP3_CTRL_TRACE_ON      109 /* Start trace data */
#define MTP3_CTRL_TRACE_OFF     110 /* Trace Data off */

#define MTP3_CTRL_LINK_ENA		111	/* Enable Link */
#define MTP3_CTRL_LINK_DIS		112	/* Disable Link */
#define MTP3_CTRL_LINK_INH		113	/* Inhibit Link */
#define MTP3_CTRL_LINK_UNINH	114	/* Uninhibit Link */
#define MTP3_CTRL_LINK_SPRST	115	/* SP Restart Request for Link */
#define MTP3_CTRL_LINK_DEL      116 /* Delete Link */
#define MTP3_CTRL_LINK_LPO      117 /* Start local processor outage */
#define MTP3_CTRL_LINK_LPR      118 /* End local processor outage */
#define MTP3_CTRL_LINK_EMG      119 /* Emergency condition on */
#define MTP3_CTRL_LINK_NRM      120 /* Emergency condition off */

#define MTP3_CTRL_LINKSET_ENA	121	/* Enable Linkset */
#define MTP3_CTRL_LINKSET_DIS	122	/* Disable Linkset */

#define MTP3_CTRL_LINK_TRCON    123 /* Start Link trace data */
#define MTP3_CTRL_LINK_TRCOFF   124 /* Link Trace Data off */

/*
 * configuration packets
 */

#ifdef UNIX
#pragma pack(1)
#endif

/* MTP3 General timers configuration structure */

typedef struct _MTP3GenTimerCfg
{
   TimerCfg t15;        /* t15 - waiting to start route set congestion test */
   TimerCfg t16;        /* t16 - waiting for route set congestion status update */
   /* ITU restart timers */
   TimerCfg t18_itu;    /* ITU only - time at restarting STP to wait for TFP, TFR, TFA until enough
                                      TRA's received.  Then send TFP, TFR's. */
   TimerCfg t20_itu;    /* ITU only - overall restart time at restarting SP/STP */

   /* ANSI restart timers */
   TimerCfg t22_ansi;   /* ANSI only - time at restarting SP to wait for links to become available */
   TimerCfg t23_ansi;   /* ANSI only - time at restarting SP, after T22, to wait for all TRA's */
   TimerCfg t24_ansi;   /* ANSI only - time at restarting STP, after T23, waiting to send all TRA's */
   TimerCfg t26_ansi;   /* ANSI only - time at restarting SP waiting to repeat TRW */
   TimerCfg t27_ansi;   /* ANSI only - minimum duration of unavailability for full restart */

   TimerCfg tRteInst;   /* Route instance life timer */
   TimerCfg tResync;    /* internal timer for re-syncing checkpointing */
} MTP3GenTimerCfg;

/* Mtp3 General configuration parameters structure */

typedef struct _MTP3GenCfg
{
   U32 spCode1;                 /* our DPC for CCITT version */
   U32 spCode2;                 /* our DPC for ANSI or CHINA version */
   U8 typeSP;                   /* type of signalling point */
   Bool disableUPU;             /* disable sending of User Part Unavailable messages */
   Bool ssfValid;               /* ssf validation required */
   Bool rstReq;                 /* restarting procedure required */
   U16 nmbLinks;                /* number of MTP Data Links */
   U16 nmbNSap;                 /* number of Upper Layer Saps */
   U16 nmbRouts;                /* maximum number of routing entries */
   U16 nmbLnkSets;              /* number of link sets */
   U16 nmbRteInst;              /* number of simultaneous Rte instances */
   U8 nmbMasks;                 /* number of masks */
   U8 pcDispFmt;                /* point code display format */
   U32 masks[MTP3MAXMASKS];     /* route masks */
   S16 cbTimeRes;               /* time resolution */
   S16 icbTimeRes;              /* time resolution */
   S16 spTimeRes;               /* time resolution */
   S16 rteTimeRes;              /* time resolution */
   MTP3GenTimerCfg tmr;         /* general timer configuration */
   PDesc stkmgr;                /* stack manager */
   U8 traceData;                /* trace data flag */
   Bool opcRouting;             /* opc routing */
   Bool transparentMode;        /* transparent mode */
   U8  spare2;                  /* Make an even number of longs */
} MTP3GenCfg;

/* Network SAP definition structure */

typedef struct _MTP3NSapCfg
{
   S16 p0QLen;                  /* size of the priority 0 Q */
   S16 p1QLen;                  /* size of the priority 1 Q */
   S16 p2QLen;                  /* size of the priority 2 Q */
   S16 p3QLen;                  /* size of the priority 3 Q */
   U8 lnkType;                  /* link type ANSI or CCITT */
   U8 selector;                 /* upper layer selector */
   U16 spare1;                  /* alignment */
   MemoryId mem;                /* memory region and pool id */
   U8 dpcLen;                   /* dpc or opc length */
   U8 prior;                    /* priority */
   U8 route;                    /* route */
   U8 spare2;                   /* alignment */
   U32 opc;                     /* default opc for UDatReq from user layer */
} MTP3NSapCfg;

/* Data Link Sap Timers configuration structure */

typedef struct _MTP3LinkTimerCfg
{
   TimerCfg t1;                 /* t1 - delay to avoid missequencing on changeover */
   TimerCfg t2;                 /* t2 - waiting for changeover ack */
   TimerCfg t3;                 /* t3 - delay to avoid missequencing on changeback */
   TimerCfg t4;                 /* t4 - waiting for first changeback ack */
   TimerCfg t5;                 /* t5 - waiting for second changeback ack */
   TimerCfg t6;                 /* t6 - delay to avoid missequencing on rerouting */
   TimerCfg t7;                 /* t7 - waiting for link connection ack */
   TimerCfg t11;                /* t11 - transfer restricted timer */
   TimerCfg t12;                /* t12 - waiting for uninhibit ack */
   TimerCfg t13;                /* t13 - waiting for forced uninhibit */
   TimerCfg t14;                /* t14 - waiting for inhibition ack */
   TimerCfg t17;                /* t17 - delay to avoid oscillation of initial alignment failure */
   TimerCfg t22;                /* t22 - local inhibit test timer */
   TimerCfg t23;                /* t23 - remote inhibit test timer */
   TimerCfg t24;                /* t24 - stabilizing timer */
   TimerCfg t31;                /* t31 - BSN requested timer */
   TimerCfg t32;                /* t32 - SLT timer */
   TimerCfg t33;                /* t33 - connecting timer */
   TimerCfg t34;                /* t34 - periodic signalling link test timer */
   TimerCfg t40;                /* Redundancy bind timer */
   TimerCfg t41;                /* Redundancy disconnect request timer */
   TimerCfg t42;                /* Redundancy flow control request timer */
   TimerCfg t43;                /* Redundancy local processor status timer */
   TimerCfg t44;                /* Redundancy unbind timer */
} MTP3LinkTimerCfg;


/* High speed link bit definitions used in hsBits below */
#define HS_LINK         0x01            /* High speed link is in effect if set */
#define HS_EXT_SEQ      0x02            /* Extended sequence numbers are in effect if set */

/* Data Link SAP configuration structure */
typedef struct _MTP3LinkCfg
{
   U16 lnkSetId;                /* link set ID */
   U16 lnkId;                   /* signalling link identity */
   U32 opc;                     /* Alternate Origination Point Code */
   U32 adjDpc;                  /* Adjacent Destination Point Code */
   U8 lnkPrior;                 /* link priority within the link set */
   U8 usePrior;                 /* use message priority, or blast zero for all priorities */
   U16 msgSize;                 /* message length */
   U8 msgPrior;                 /* management message priority */
   U8 lnkType;                  /* link type ANSI or CCITT */
   U8 maxSLTtry;                /* maximun times to retry SLTM */
   U8 hsBits;                   /* High speed link bits defined above this structure.  Formerly spare1 */
   S16 p0QLen;                  /* size of the priority 0 Q */
   S16 p1QLen;                  /* size of the priority 1 Q */
   S16 p2QLen;                  /* size of the priority 2 Q */
   S16 p3QLen;                  /* size of the priority 3 Q */
   U8 discPrior;                /* discard priority */
   U8 ssf;                      /* sub service field */
   U8 lnkTstSLC;                /* link selection code for link test */
   U8 tstLen;                   /* link test pattern length */
   U8 tst[MTP3LNKTSTMAX];       /* link test pattern */
   MTP3LinkTimerCfg tmr;        /* timer configuration */
   U16 dstProcId;               /* destination processor id */
   U8 dstEnt;                   /* entity */
   U8 dstInst;                  /* instance */
   U8 prior;                    /* priority */
   U8 route;                    /* route */
   U8 selector;                 /* lower layer selector */
   U8 spare2;                   /* alignment */
   MemoryId mem;                /* memory region and pool id */
   U8 dpcLen;                   /* dpc or opc length */
   U8 lnkIndex;                 /* Index into link array.  0 to n-1 in order defined in config */
   S16 spId;                    /* service provider id */
   U8 dis;                      /* initial link state (enabled/disabled) JMK */
   U8 portType;                 /* port type - T1/E1/MVIP or Serial - TEK */
   U8 traceData;                /* trace data flag */
   U8 spare3;                   /* End structure on even 4-byte boundardy */
} MTP3LinkCfg;

typedef struct _MTP3CmbLnkSet   /* MTP Level 3 combined link set cfg */
{
   U16 cmbLnkSetId;             /* combined link set ID */
   U8 lnkSetPrior;              /* link set priority */
   U8 spare1;                   /* alignment */
} MTP3CmbLnkSet;

typedef struct _MTP3LnkSetCfg   /* MTP Level 3 link set configuration */
{
   U16 lnkSetId;                /* link set ID */
   U16 spare1;                  /* alignment */
   U32 opc;                     /* alternative Origination Point Code */
   U32 adjDpc;                  /* adjacent Destination Point Code */
   U16 minNmbActLnk;            /* MAXIMUM number of active links */
   U16 nmbCmbLnkSet;            /* number of combined link sets */
   MTP3CmbLnkSet cmbLnkSet[MTP3MAXCMBLNK];   /* combined link sets */
} MTP3LinkSetCfg;

/* Route timers structure */

typedef struct _MTP3RteTimerCfg
{
   TimerCfg t8;                 /* t8 - transfer prohibited inhibition timer */
   TimerCfg t10;                /* t10 - waiting to repeat route set test */
   /* ITU restart timers */
   TimerCfg t19_itu;            /* ITU only - time after sending a TRA to ignore rcvd TRA's */
   TimerCfg t21_itu;            /* ITU only - overall restart time at adjacent SP/STP */
   /* ANSI restart timers */
   TimerCfg t25_ansi;           /* ANSI only - time at adjacent SP waiting for TRA */
   TimerCfg t28_ansi;           /* ANSI only - time at adjacent SP waiting for TRW */
   TimerCfg t29_ansi;           /* ANSI only - timer started when TRA sent in response to unexpected TRW or TRA */
   TimerCfg t30_ansi;           /* ANSI only - timer to limit sending of TFP's and TFR's in response to
                                               unexpected TRW or TRA */
} MTP3RteTimerCfg;

typedef struct _MTP3RoutCfg     /* MTP Level 3 routing configuration */
{
   U32 dpc;                     /* destination point code */
   U32 opc;                     /* origination point code */
   U8 spType;                   /* signalling point type */
   U8 swtchType;                /* switch type */
   U16 cmbLnkSetId;             /* combined link set ID */
   U8 dir;                      /* direction */
   Bool rteToAdjSp;             /* flag indicating this route to adjacent SP */
   Bool rteToCluster;           /* flag indicating this route to a cluster */
   U8 ssf;                      /* sub service field */
   MTP3RteTimerCfg tmr;         /* route timer configuration */
} MTP3RouteCfg;


typedef struct _MTP3GenStats   /* MTP Level 3 singalling point statistics */
{
    DateTime DT;                /* Date / timestamp */
    Duration Dura;              /* Duration */
    S16 Action;                 /* Action to take (ZEROSTS or NOZEROSTS) */
    S16 spare1;                 /* Alignment */
    U32 usrUnavailRx;           /* user part unavailable received */
    U32 usrUnavailTx;           /* user part unavailable transmitted */
    U32 traTx;                  /* traffic restrt allowed transmitted */
    U32 traRx;                  /* traffic restrt allowed received */
    U32 trwTx;                  /* traffic restrt waiting transmitted */
    U32 trwRx;                  /* traffic restrt waiting received */
    U32 msuDropRteErr;          /* MSU dropped due to a routing data error */
} MTP3GenStats;

typedef struct _MTP3LinkStats  /* MTP Level 3 link statistics */
{
    DateTime DT;                /* Date / timestamp */
    Duration Dura;              /* Duration */
    S16 Action;                 /* Action to take (ZEROSTS or NOZEROSTS) */
    S16 spare1;                 /* Alignment */
    U32 changeOverTx;           /* changeover, order transmitted */
    U32 changeOverRx;           /* changeover, order received */
    U32 changeOverAckTx;        /* changeover, ack transmitted */
    U32 changeOverAckRx;        /* changeover, ack transmitted */
    U32 changeBackTx;           /* changeback, declaration transmitted */
    U32 changeBackRx;           /* changeback, declaration received */
    U32 changeBackAckTx;        /* changeback, ack transmitted */
    U32 changeBackAckRx;        /* changeback, ack received */
    U32 emChangeOverTx;         /* emergency changeover transmitted */
    U32 emChangeOverRx;         /* emergency changeover received */
    U32 emChangeOverAckTx;      /* emergency changeover ack transmitted */
    U32 emChangeOverAckRx;      /* emergency changeover ack received */
    U32 lnkInhTx;               /* link inhibit transmitted */
    U32 lnkInhRx;               /* link inhibit received */
    U32 lnkUninhTx;             /* link uninhibit transmitted */
    U32 lnkUninhRx;             /* link uninhibit received */
    U32 lnkInhAckTx;            /* link inhibited ack transmitted */
    U32 lnkInhAckRx;            /* link inhibited ack received */
    U32 lnkUninhAckTx;          /* link uninhibited ack transmitted */
    U32 lnkUninhAckRx;          /* link uninhibited ack received */
    U32 lnkInhDenTx;            /* link inhibit denied transmitted */
    U32 lnkInhDenRx;            /* link inhibit denied received */
    U32 lnkForceUninhTx;        /* force link uninhibit transmitted */
    U32 lnkForceUninhRx;        /* force link uninhibit received */
    U32 lnkLocInhTstTx;         /* local link inhibit test transmitted */
    U32 lnkLocInhTstRx;         /* local link inhibit test received */
    U32 lnkRmtInhTstTx;         /* remote link inhibit test transmitted */
    U32 lnkRmtInhTstRx;         /* remote link inhibit test received */
    U32 lnkConOrdTx;            /* link connection order transmitted */
    U32 lnkConOrdRx;            /* link connection order received */
    U32 lnkConAckTx;            /* link connection ack transmitted */
    U32 lnkConAckRx;            /* link connection ack received */
    U32 txCntrlRx;              /* transfer controlled received */
    U32 txCntrlTx;              /* transfer controlled transmitted */
    U32 lnkTstRx;               /* link test received */
    U32 lnkTstTx;               /* link test transmitted */
    U32 lnkTstAckRx;            /* link test ack received */
    U32 lnkTstAckTx;            /* link test ack transmitted */
    U32 txDrop;                 /* transmit messages dropped */
    U32 txCongDrop;             /* MSUs dropped due to link congestion */
    U32 sifOctTx;               /* number of SIF octets transmitted */
    U32 sifOctRx;               /* number of SIF octets received */
    U32 sioOctTx;               /* number of SIO octets transmitted */
    U32 sioOctRx;               /* number of SIO octets received */
    U32 msuTx;                  /* number of MSU transmitted */
    U32 msuRx;                  /* number of MSU received */
    U32 cong0;                  /* link congestion at threshold 0 */
    U32 cong1;                  /* link congestion at threshold 1 */
    U32 cong2;                  /* link congestion at threshold 2 */
    U32 cong3;                  /* link congestion at threshold 3 */
    U16 tqCnt;                  /* message count in transmit queue */
    U16 rtqCnt;                 /* message count in retransmit queue */
    U16 hiTqCnt;                /* high water message count in transmit queue */
    U16 hiRtqCnt;               /* high water essage count in retransmit queue */
    U32 durLnkUnav;             /* duration of link unavailability */
    U32 durLnkCong;             /* duration of link congestion */
} MTP3LinkStats;

typedef struct _MTP3LinkSetStats  /* MTP Level 3 link set statistics */
{
    DateTime DT;                /* Date / timestamp */
    Duration Dura;              /* Duration */
    S16 Action;                 /* Action to take (ZEROSTS or NOZEROSTS) */
    S16 spare1;                 /* Alignment */
    U32 strtLnkSetFail;         /* start of linkset failure */
    U32 stopLnkSetFail;         /* stop of linkset failure */
    U32 durLnkSetUnav;          /* duration of linkset unavailability */
} MTP3LinkSetStats;

typedef struct _MTP3RouteStats  /* MTP Level 3 route statistics */
{
    DateTime DT;                /* Date / timestamp */
    Duration Dura;              /* Duration */
    S16 Action;                 /* Action to take (ZEROSTS or NOZEROSTS) */
    S16 spare1;                 /* Alignment */
    U32 dpc;                    /* dpc */
    U32 opc;                    /* opc */
    U32 routeTstTx;             /* route set test transmitted */
    U32 routeTstRx;             /* route set test received */
    U32 congTstRx;              /* route set congestion test received */
    U32 congTstTx;              /* route set congestion test transmitted */
    U32 txProhibTx;             /* transfer prohibited transmitted */
    U32 txProhibRx;             /* transfer prohibited received */
    U32 txRestrictRx;           /* transfer restricted received */
    U32 txAllowTx;              /* transfer allowed transmitted */
    U32 txAllowRx;              /* transfer allowed received */
    U32 rteUnavCnt;             /* route unavailable */
    U32 sifOctTx;               /* number of SIF octets transmitted */
    U32 sioOctTx;               /* number of SIO octets transmitted */
    U32 durRteUnav;             /* duration of route unavailability */
} MTP3RouteStats;



typedef struct _MTP3GenStatus          /* MTP Level 3 - signalling point status */
{
    DateTime DT;                /* Date / timestamp */
    Bool spRst;                 /* SP restarting flag */
    U8 haState;                 /* High availability state */
    U8 spare1;                  /* Alignment */
    U8 spare2;                  /* Alignment */
} MTP3GenStatus;

/* High Availability states */
#define SN_HAST_STANDALONE      0   /* Stand-alone (non-redundant) state */
#define SN_HAST_STARTING        1   /* Initial redundant state */
#define SN_HAST_PRIMARY         2   /* This MTP3 is the primary */
#define SN_HAST_BACKUP          3   /* This MTP3 is the backup */

typedef struct _MTP3NSapStatus   /* MTP Level 3 - SAP status */
{
    DateTime DT;                /* Date / timestamp */
    U8 sapState;                /* sap state */
    U8 flcSt;                   /* flow control state */
    U8 spare1;                  /* Alignment */
    U8 spare2;                  /* Alignment */
    U32 congDiscard;            /* Number of messages discarded due to congestion */
} MTP3NSapStatus;

/* These are the link states for the state element in the structure below */
#define MTP3_LNK_INACTIVE       0       /* link is inactive */
#define MTP3_LNK_CONN           1       /* link is connecting */
#define MTP3_LNK_ACTIVE         2       /* link is active, data flow possible */
#define MTP3_LNK_FAILED         3       /* link has failed */
#define MTP3_LNK_WAITCON        4       /* link is waiting for remote connect */
#define MTP3_LNK_BINDING        5       /* Have sent a bind request to MTP2.  Waiting for bind cfm */       /* 3.0 */
#define MTP3_LNK_UNBINDING      6       /* Have sent an unbind req to MTP2.  Waiting for an unbind cfm */   /* 3.0 */
#define MTP3_LNK_UNBOUND        7       /* Not bound to MTP2 link */                                        /* 3.0 */

typedef struct _MTP3LinkStatus     /* MTP Level 3 - signalling link status */
{
    DateTime DT;                /* Date / timestamp */
    U8 state;                   /* link state */
    U8 flcSt;                   /* flow control state */
    Bool blkd;                  /* link is blocked */
    Bool locBlkd;               /* link is blocked locally */
    Bool rmtBlkd;               /* link is blocked remotely */
    Bool inhbt;                 /* link is inhibited */
    Bool locInhbt;              /* local inhibit indication */
    Bool rmtInhbt;              /* remote inhibit indication */
    Bool uninhbt;               /* uninhibit signalling indication */
    Bool cong;                  /* link is congested */
    Bool emerg;                 /* emergency indication */
    U8  spare1;                 /* End structures on 4-byte boundaries */
} MTP3LinkStatus;

typedef struct _MTP3LinkSetStatus      /* MTP Level 3 - link set status */
{
    DateTime DT;                /* Date / timestamp */
    Bool cfgFlg;                /* configuration flag */
    U8 spare1;                  /* alignment */
    U16 nmbActLnks;             /* number of active links */
    U16 nmbCongLnks;            /* number of congested links */
    Bool cong;                  /* link set is congested */
    U8 state;                   /* link set state */
} MTP3LinkSetStatus;

typedef struct _MTP3RouteStatus        /* MTP Level 3 - route status */
{
    DateTime DT;                /* Date / timestamp */
    U32 dpc;                    /* dpc */
    U32 opc;                    /* opc */
    U16 nmbActvLnkSets;         /* number of active link sets */
    U16 nmbCongLnkSets;         /* number of congested link sets */
    U8 state;                   /* route state */
    Bool cong;                  /* route set is congested */
    Bool rstFlg;                /* SP restarting flag */
    U8  spare1;                 /* End structures on 4-byte boundaries */
} MTP3RouteStatus;


typedef struct _MTP3CtrlRqst            /* MTP Level 3 - control request */
{
    DateTime DT;                /* Date / timestamp */
    U8  action;                 /* Main action */
    U8  subAction;              /* Sub action */
    U8  spare1;                 /* End structures on 4-byte boundaries */
    U8  spare2;                 /* End structures on 4-byte boundaries */
    U32 dpc;
} MTP3CtrlRqst;

#ifdef UNIX
#pragma pack()
#endif

/* Error type returned by API functions */
typedef S16 MTP3_STATUS;   /* redefine for portability */

/* Mgmt API return codes */
#define MTP3_SUCCESS    0           /* Successful */
#define MTP3_LNKTYPE    0x1001      /* Invalid link/switch type */
#define MTP3_PARAM      0x1002      /* Invalid parameter */
#define MTP3_BOARD      0x1004      /* board number out of range */
#define MTP3_DRIVER     0x1005      /* CPI driver returned error        */
#define MTP3_HANDLE     0x1006      /* Board not previously initialized */
#define MTP3_TIMEOUT    0x1007      /* No response from board */
#define MTP3_RESPONSE   0x1008      /* Wrong response from board */

#ifdef __cplusplus
extern "C" {
#endif

MTP3_STATUS TXMTP3FUNC Mtp3MgmtInit       ( U8 board, U8 srcEnt, U8 srcInst );
MTP3_STATUS TXMTP3FUNC Mtp3MgmtTerm       ( U8 board );
MTP3_STATUS TXMTP3FUNC Mtp3MgmtCtrl       ( U8 board, S16 entity, U8 action );

MTP3_STATUS TXMTP3FUNC Mtp3InitGenCfg     ( MTP3GenCfg *pGencfg, U32 opc );
MTP3_STATUS TXMTP3FUNC Mtp3SetGenCfg      ( U8 board, MTP3GenCfg *pGencfg );
MTP3_STATUS TXMTP3FUNC Mtp3GetGenCfg      ( U8 board, MTP3GenCfg *pGencfg );
MTP3_STATUS TXMTP3FUNC Mtp3InitNSapCfg    ( MTP3NSapCfg *pNSapCfg, U8 linkType );
MTP3_STATUS TXMTP3FUNC Mtp3SetNSapCfg     ( U8 board, MTP3NSapCfg *pNSapCfg, S16 nSapNo );
MTP3_STATUS TXMTP3FUNC Mtp3GetNSapCfg     ( U8 board, MTP3NSapCfg *pNSapCfg, S16 nSapNo );
MTP3_STATUS TXMTP3FUNC Mtp3InitLinkCfg    ( U8 board, MTP3LinkCfg *pLinkCfg, S16 linkNo, U8 linkType, U32 dpc );
MTP3_STATUS TXMTP3FUNC Mtp3SetLinkCfg     ( U8 board, MTP3LinkCfg *pLinkCfg );
MTP3_STATUS TXMTP3FUNC Mtp3GetLinkCfg     ( U8 board, MTP3LinkCfg *pLinkCfg, S16 linkNo);
MTP3_STATUS TXMTP3FUNC Mtp3InitLinkSetCfg ( MTP3LinkSetCfg *pLnkSetCfg, S16 linkSetNo, U32 dpc );
MTP3_STATUS TXMTP3FUNC Mtp3SetLinkSetCfg  ( U8 board, MTP3LinkSetCfg *pLinkSetCfg );
MTP3_STATUS TXMTP3FUNC Mtp3GetLinkSetCfg  ( U8 board, MTP3LinkSetCfg *pLinkSetCfg, S16 linkSetNo );
MTP3_STATUS TXMTP3FUNC Mtp3InitRouteCfg   ( MTP3RouteCfg *pRouteCfg, S16 routeNo, U32 dpc, U8 swType );
MTP3_STATUS TXMTP3FUNC Mtp3SetRouteCfg    ( U8 board, MTP3RouteCfg *pRouteCfg );
MTP3_STATUS TXMTP3FUNC Mtp3GetRouteCfg    ( U8 board, MTP3RouteCfg *pRouteCfg, U32 dpc, U32 opc );

MTP3_STATUS TXMTP3FUNC Mtp3GenStatus      ( U8 board, MTP3GenStatus *pStatus);
MTP3_STATUS TXMTP3FUNC Mtp3NSapStatus     ( U8 board, S16 nsapNo, MTP3NSapStatus *pStatus);
MTP3_STATUS TXMTP3FUNC Mtp3LinkStatus     ( U8 board, S16 linkNo, MTP3LinkStatus *pStatus);
MTP3_STATUS TXMTP3FUNC Mtp3LinkSetStatus  ( U8 board, S16 linkSetNo, MTP3LinkSetStatus *pStatus);
MTP3_STATUS TXMTP3FUNC Mtp3RouteStatus    ( U8 board, U32 dpc, U32 opc, MTP3RouteStatus *pStatus);

MTP3_STATUS TXMTP3FUNC Mtp3GenStats       ( U8 board, MTP3GenStats *pStats, Bool bReset);
MTP3_STATUS TXMTP3FUNC Mtp3LinkStats      ( U8 board, S16 linkNo, MTP3LinkStats *pStats, Bool bReset);
MTP3_STATUS TXMTP3FUNC Mtp3LinkSetStats   ( U8 board, S16 linkSetNo, MTP3LinkSetStats *pStats, Bool bReset);
MTP3_STATUS TXMTP3FUNC Mtp3RouteStats     ( U8 board, U32 dpc, U32 opc, MTP3RouteStats *pStats, Bool bReset);

/*-----------------3/8/00 10:08AM-------------------
 * JNTT only entry point.  This initiates a Route Test
 * by sending an SRT
 * --------------------------------------------------*/
MTP3_STATUS TXMTP3FUNC Mtp3RouteTest      ( U8 board, U32 dpc);

#ifdef __cplusplus
}
#endif


#endif	/* _MTP3MAPI_H_	 */
