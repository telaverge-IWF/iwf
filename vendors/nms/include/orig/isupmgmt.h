/*************************************************************************
**                                                                      **
**                         PROPRIETARY NOTICE                           **
**                                                                      **
**                         Copyright (c) 1996                           **
**                          by TEKnique, Inc.                           **
**                                                                      **
**  The following is licensed program material and is considered        **
**  proprietary and confidential.  No part of this program may be       **
**  reproduced or used in any form or by any means without the express  **
**  written permission of TEKnique, Inc.                                **
**                                                                      **
*************************************************************************/

#ifndef _ISUPUSER_H_
#define _ISUPUSER_H_

/* define the calling conventions for the API functions for various
 * operating systems - NOTE: API callers should never define the
 * preprocessor constant "_TX_SCCP_SOURCE_"; this is only for use
 * by the SCCP API source code itself.
 */

/* OS2: SCCP API is a DLL */
#ifdef __OS2__
#ifdef _TX_ISUPMGMT_SOURCE_
    /* ISUP management API source definition */
#define     TXISUPMGMTFUNC               extern _export _syscall
#else
    /* ISUP management API caller's definition */
#define     TXISUPMGMTFUNC               _syscall
#endif  /* _TX_ISUPMGMT_SOURCE_ */

/* WIN32: ISUP management API is a DLL */
#elif  WIN32	                        /* WIN32 */
#ifdef _TX_ISUPMGMT_SOURCE_
    /* ISUP management API source definition */
#define     TXISUPMGMTFUNC               __declspec( dllexport ) WINAPI
#else
    /* ISUP management API caller's definition */
#define     TXISUPMGMTFUNC               WINAPI
#endif  /* _TX_ISUPMGMT_SOURCE_ */

/* all others: statically linked library */
#else
#define     TXISUPMGMTFUNC
#endif

#define MAX_GLT_SZ          32
#define MAX_DATA_SZ         1200
#define EXTADDRLEN          16

#define ORGNETWORK         0x00         /* network originatied              */
#define ORGENDUSER         0x01         /* user originatied                 */

/* API return values */
#define ISUP_SUCCESS       0           /* API call was successful          */
#define ISUP_OVERRUN       0x1001      /* data length too large to send    */
#define ISUP_UNDERRUN      0x1002      /* received message too large       */
#define ISUP_UNBOUND       0x1003      /* not bound to specified board     */
#define ISUP_BOARD         0x1004      /* board number out of range        */
#define ISUP_DRIVER        0x1005      /* CPI driver returned error        */
#define ISUP_NOMSG         0x1006      /* No event messages waiting        */
#define ISUP_NOTBOUND      0x1007      /* User failed to call              */
#define ISUP_FAILED        0x1008      /* request failed                   */


#ifndef MAXSSNS
#define MAXSSNS           8        /* Max Subsystems allowed per Dpc */
#endif

#ifndef MAXDPC
#define MAXDPC          10        /* Max Concerned Point Code per Dpc */
#endif

#ifndef ISUPADDRLEN
#define ISUPADDRLEN     20         /* Address Mask Length */
#endif

/* Switch types for NSaps, addresses, & routes - defines protocol behavior */
#define ISUP_SW_ITU     1               /* ITUT - General */
#define ISUP_SW_ANS     2               /* ANSI - General */

/* Network SAP Types */
#define ISUP_SAP_MTP	0
#define ISUP_SAP_SCCP	1

/* Circuit Types */

#define ISUP_CTL_INCOMING	0
#define ISUP_CTL_OUTGOING   1
#define ISUP_CTL_BOTHWAY    2

/* Bearer Profiles */

#define ISUP_PROF_VOICE		 1
#define ISUP_PROF_DATA       2           /* unrestricted data */
#define ISUP_PROF_RESDATA    4           /* restricted data */
#define ISUP_PROF_AUDIO3     8           /* 3.1 audio */
#define ISUP_PROF_AUDIO7    16           /* 7 audio */
#define ISUP_PROF_VIDEO     32           /* video */
#define ISUP_PROF_VD        33           /* both voice and data */


/* Switch types for User SAPs only - defines protocol behavior */
#define ISUP_SW_ITU88   2               /* ITU-T 1988 operation */
#define ISUP_SW_ITU92   3               /* ITU-T 1992 operation */
#define ISUP_SW_ANS88   2               /* ANSI-1988 operation */
#define ISUP_SW_ANS92   3               /* ANSI-1992 operation */

/* Subservice Types */

#define ISUP_SSF_INTL   0
#define ISUP_SSF_NAT 	2

/* Event codes for configuration requests */
#define ISUP_CFGREQ     0x3c             /* Configuration request */

#define ISUP_GEN_CFG     1           /* general Parameters */
#define ISUP_USAP_CFG    34          /* ISUP User SAP */
#define ISUP_NSAP_CFG    3           /* network SAP */
#define ISUP_ROUT_CFG    10          /* route configuration*/
#define ISUP_ROUT_DEL    30          /* delete route */
#define ISUP_CIRC_CFG    35          /* address mapping cofiguration */

/* Resolution for all ISUP timers */
#define ISUP_TIMER_RES  10              /* 10 ticks/second */

/* Selector value for ISUP upper (application) and lower (MTP3) interfaces */
#define ISUP_SEL_LC     0               /* loose coupling */

/* route status values */
#define ISUP_ONLINE     0x01            /* Destination is accessible        */
#define ISUP_CONG       0x02            /* Destination is congested (this   */
                                        /* status is reported back by ISUP  */
                                        /* to application and not be set by */
                                        /* application)                     */
#define ISUP_TRANS      0x04            /* This signalling point is a       */
                                        /* translator node                  */
#define ISUP_ADJACENT   0x08            /* This signalling point is         */
                                        /* adjacent for ISUP point code &   */
                                        /* subsystem management procedures  */

/* Status values for route configuration subsystem list */
#define ISUP_SNR        0x01            /* Subsystem is normal routed (not  */
                                        /* backup routed)                   */
#define ISUP_ACC        0x02            /* This subsystem is accessible     */

/* ISUP routing types for address map tables */
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
#define NP_DATA             0x03         /* data numbering - X.121          */
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

typedef struct _IsupAddr        /* ISUP address (global title digits) */
{
   U8 length;                   /* length bytes */
   U8 string[ISUPADDRLEN];      /* address value - ASCII hex digits */

#if !(ISUPADDRLEN % 2)
   U8 fill;                     /* alignment */
#endif

} IsupAddr;

typedef struct _IsupAddr AddrMask;

/* general configuration parameters */


typedef struct _IsupGenParms
{
    U16         maxSaps;                /* Max Number of ISUP User Saps */
    U16			maxNetSaps;             /* Max Number of Network Saps (MTP3) */
    U32 		maxCircuits;            /* Max Number of Circuits */
    U16 		maxCircGrp;             /* Max Number of Circuit Groups */
    U32 		maxCallRefs;            /* Max Number of Call References */
    U16 		maxRoutes;              /* Max Number of Routes */
	U32			orgPointCode;
	Bool		sccpSupport;
	U8			fill1;
	IsupAddr	comLLID;				/* Common language location identifier */
	S16			poolUpper;
	S16			poolLower;
	S16 		timerRes;				/* Timer resolution */

	TimerCfg	t18;
	TimerCfg	t19;
	TimerCfg	t20;
	TimerCfg	t21;
	TimerCfg	t22;
	TimerCfg	t23;
#if SS7_ANS88
   	TimerCfg 	tFrstGrpRx;     /* first group received timer */
#endif
   	TimerCfg 	tGrpReset;      /* group reset timer */
	PDesc		stkMgr;
} IsupGenParms;

/* upper sap configuration structure */

typedef struct _IsupUSapCfg
{
   S16  	switchType;             /* Protocol Switch */
   Bool 	wildCardRoute;          /* Wild Card Routing Flag */
   U8 		wildCardMask[ISUPADDRLEN];   /* Wild Card Mask */
   Bool 	sidInsert;              /* SID insertion Flag */
   Bool 	sidVerify;              /* SID verification Flag */
   U8       fill1;
   IsupAddr sid;                    /* SID */
   U8 		natAddrInd;             /* SID Nature of Addres Indicator */
   U8 		sidNumPlan;             /* SID Numbering Plan */
   U8 		sidPresInd;             /* default presentation indicator */
   Bool 	incSidPresRes;          /* Presentation Restriction of incoming SID */
   Bool 	sidPresRes;             /* Presentation Restriction */
   Bool 	reqOpt;                 /* Request option */
   Bool 	allowCallMod;           /* call modification allowed */
   U8 		maxMsgLength;           /* Max length of user to user messages */
   TimerCfg t1;                     /* t1 timer - release sent */
   TimerCfg t2;                     /* t2 timer - suspend received */
   TimerCfg t5;                     /* t5 timer - initial release sent */
   TimerCfg t6;                     /* t6 timer - suspend received */
   TimerCfg t7;                     /* t7 timer - latest address sent */
   TimerCfg t8;                     /* t8 timer - initial address received */
   TimerCfg t9;                     /* t9 timer - latest address sent after ACM */
   TimerCfg t31;                    /* t31 timer - call reference frozen period */
   TimerCfg t33;                    /* t33 timer - INR sent */

   TimerCfg tCCR;                   /* tCCR timer - continuity recheck timer */
   TimerCfg t27;                    /* t27 timer - waiting for continuity recheck */
   TimerCfg t34;                    /* t33 timer - waiting for continuity after recheck */

   TimerCfg tEx;                    /* tEx timer - Exit to be sent */
#if SS7_ANS92
   TimerCfg tCRM;                   /* circuit reservation message timer */
   TimerCfg tCRA;                   /* circuit reservation ack.  timer */
#endif
   U8    	prior;                  /* priority */
   U8    	route;                  /* route */
   U8    	selector;               /* selector */
   U8		fill2;
   MemoryId memory;                 /* memory region & pool id */

} IsupUSapCfg;

/* network sap configuration structure */

typedef struct _IsupNSapCfg     /* ISUP Network Sap Config. struct (LOWER) */
{
   S16 		switchType;         /* Protocol Switch */
   S16 		spId;               /* service providor id */
   U8  		ssf;                /* sub service field */
   U8  		dstEntity;          /* entity */
   U8  		dstInstance;        /* instance */
   U8  		priority;           /* priority */
   U8  		route;              /* route */
   U8       fill1;
   U16 		dstProcId;          /* destination processor id */
   S16 		sapType;            /* sap type */
   U8  		numResInd;          /* max simultaneous res ind to upper */
   U8  		selector;           /* selector */
   MemoryId mem;                /* memory region & pool id */

} IsupNSapCfg;

/* subsytem configuration structure */

typedef struct _IsupCircCfg
{
   U32 		circuitId;             	/* circuit id code */
   U16 		cic;                	/* cic */
   U32		dstPointCode;           /* destination point code */
   U8 		controlType;            /* type of control */
   U8 		bearerProfile;          /* bearer profile */
   Bool 	contCheckReq;           /* continuity check required */
   Bool 	nonSS7Con;              /* connecting to non SS7 network */
   IsupAddr outTrunkGrp;            /* outgoing trunk group number */
   IsupAddr comLLID;		 		/* Common language location identifier */
   TimerCfg t4;                   	/* t4 timer - user part test sent */
   TimerCfg t12;                  	/* t12 timer - blocking sent */
   TimerCfg t13;                  	/* t13 timer - initial blocking sent */
   TimerCfg t14;                  	/* t14 timer - unblocking sent */
   TimerCfg t15;                  	/* t15 timer - initial unblocking sent */
   TimerCfg tVal;                 	/* circuit validation timer */
} IsupCircCfg;

/* route configuration structure */

typedef struct _IsupRouteCfg
{
   IsupAddr	address;                   /* address */
   S16 		numDstPointCode;        /* number of Dpc leading to a specific rout */
   struct
   {
      U32	dstPointCode;           /* destination point code */
      Bool 	isupAvail;              /* ISUP available */
      U8 	priority;        		/* priority */

   } dst[MAXDPC];

   Bool loadShare;               /* load sharing indication */
   U8   fill1;
} IsupRouteCfg;

/* sap statistics structure */

typedef struct _IsupSapStats
{
   S32 OOSReqGr;  /* Subsystem out-of-service request granted */
   S32 OOSReqDn;  /* Subsystem out-of-service request denied */
   S32 TxBackup;  /* msgs sent to backup subsystem */

} IsupSapStats;

/* Circuit status structure */

typedef struct _IsupCircStatus         /* ISUP Circuit status */
{
   DateTime dt;           /* date and time */
   U8 transState;               /* circuit transient state */
   U8 callState;                /* circuit call processing state */

} IsupCircStatus;

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

typedef struct _IsupCircStats
{
   DateTime dt;           /* date and time */
   Duration dura;         /* duration */
   S32  blockTx;                /* Circuit Blocking Transmitted */
   S32  blockAckTx;             /* Circuit Blocking Ack Transmitted */
   S32  unblockTx;              /* Circuit Unblocking Transmitted */
   S32  unblockAckTx;           /* Circuit Unblocking Ack Transmitted */
   S32  cirResTx;               /* Circuit Reset Transmitted */
   S32  cirGrBlockTx;           /* Circuit Group Blocking Transmitted */
   S32  cirGrBlockAckTx;        /* Circuit Group Blocking Ack Transmitted */
   S32  cirGrUnBlockTx;         /* Circuit Group Unblocking Transmitted */
   S32  cirGrUnBlockAckTx;      /* Circuit Group Unblocking Ack Transmitted */
   S32  cirGrQTx;               /* Circuit Group Query Transmitted */
   S32  cirGrQAckTx;            /* Circuit Group Query Acknowledge
                                   Transmitted */
   S32  cirGrResTx;             /* Circuit Group Reset Transmitted */
   S32  cirGrResAckTx;          /* Circuit Group Reset Ack Transmitted */
   S32  usrPrtTstTx;            /* User Part Test Transmitted */
   S32  usrPrtAvTx;             /* User Part Available Transmitted */
#if (SS7_ANS88 || SS7_ANS92)
   S32  cirValTstTx;            /* Circuit Validation Test Transmitted */
   S32  cirValRspTx;            /* Circuit Validation Response Transmitted */
#endif
   S32  blockRx;                /* Circuit Blocking Received */
   S32  blockAckRx;             /* Circuit Blocking Ack Received */
   S32  unblockRx;              /* Circuit Unblocking Received */
   S32  unblockAckRx;           /* Circuit Unblocking Ack Received */
   S32  cirResRx;               /* Circuit Reset Received */
   S32  cirGrBlockRx;           /* Circuit Group Blocking Received */
   S32  cirGrBlockAckRx;        /* Circuit Group Blocking Ack Received */
   S32  cirGrUnBlockRx;         /* Circuit Group Unblocking Received */
   S32  cirGrUnBlockAckRx;      /* Circuit Group Unblocking Ack Received */
   S32  cirGrQRx;               /* Circuit Group Query Received */
   S32  cirGrQAckRx;            /* Circuit Group Query Acknowledge
                                   Transmitted */
   S32  cirGrResRx;             /* Circuit Group Reset Received */
   S32  cirGrResAckRx;          /* Circuit Group Reset Ack Received */
   S32  usrPrtTstRx;            /* User Part Test Received */
   S32  usrPrtAvRx;             /* User Part Available Received */
#if (SS7_ANS88 || SS7_ANS92)
   S32  cirValTstRx;            /* Circuit Validation Test received */
   S32  cirValRspRx;            /* Circuit Validation Response received */
#endif
} IsupCircStats ;

/* lower sap statistics structure */

typedef struct _IsupNSapStats
{
   DateTime dt;           /* date and time */
   Duration dura;         /* duration */
   S32  adrCmpltTx;             /* Address complete transmitted */
   S32  answerTx;               /* Answer transmitted */
   S32  progressTx;             /* Progress transmitted */
   S32  contiTx;                /* Continuity transmitted */
   S32  conChkReqTx;            /* Continuity Check Request transmitted */
   S32  loopBckAckTx;           /* Lookback Acknowledge transmitted */
   S32  confusTx;               /* Confusion transmitted */
   S32  callModReqTx;           /* Call Modification Request transmitted */
   S32  callModRejTx;           /* Call Modification Reject transmitted */
   S32  callModComTx;           /* Call Modification Complete transmitted */
   S32  suspTx;                 /* Suspend transmitted */
   S32  resmTx;                 /* Resume transmitted */
   S32  forwTx;                 /* Forward transmitted */
   S32  conTx;                  /* Connect transmitted */
   S32  relTx;                  /* Release transmitted */
   S32  overldTx;               /* Overload transmitted */
   S32  relCmpltTx;             /* Release Complete transmitted */
   S32  facTx;                  /* Facility Request transmitted */
   S32  facAckTx;               /* Facility Ack transmitted */
   S32  facRejTx;               /* Facility Reject transmitted */
   S32  initAdrTx;              /* Initial Address transmitted */
   S32  infoTx;                 /* Info transmitted */
   S32  infoReqTx;              /* Info Request transmitted */
   S32  passAlongTx;            /* Pass Along transmitted */
   S32  subsAdrTx;              /* Subsequent Address transmitted */
   S32  usrToUsrTx;             /* User to User transmitted */
   S32  uneqCirIdTx;            /* Unequipped Circuit ID transmitted */
#if SS7_ANS92
   S32  cirReserveTx;           /* circuit reservation  transmitted */
   S32  cirResAckTx;            /* circuit reservation ack transmitted */
#endif
#if (SS7_ANS88 || SS7_ANS92)
   S32  exitTx;                 /* exit transmitted */
#endif
   S32  netResMgmtTx;           /* Network Resourse transmitted */
   S32  netIdReqTx;             /* Network Id Request transmitted */
   S32  netIdRspTx;             /* Network Id Request transmitted */
#if SS7_SINGTEL
   S32  malCllPrntTx;           /* Malicious Call Print transmitted */
   S32  chargeTx;               /* Charge transmitted */
   S32  trfChngeTx;             /* Tariff change transmitted */
   S32  chargeAckTx;            /* Charge ack transmitted */
#endif
#if SS7_Q767IT
   S32  comTx;                  /* Call Offering transmitted */
#endif
   S32  adrCmpltRx;             /* Address complete received */
   S32  answerRx;               /* Answer received */
   S32  progressRx;             /* Progress received */
   S32  contiRx;                /* Continuity received */
   S32  conChkReqRx;            /* Continuity Check Request received */
   S32  loopBckAckRx;           /* Lookback Acknowledge received */
   S32  confusRx;               /* Confusion received */
   S32  callModReqRx;           /* Call Modification Request received */
   S32  callModRejRx;           /* Call Modification Reject received */
   S32  callModComRx;           /* Call Modification Complete received */
   S32  suspRx;                 /* Suspend received */
   S32  resmRx;                 /* Resume received */
   S32  forwRx;                 /* Forward received */
   S32  conRx;                  /* Connect received */
   S32  overldRx;               /* Overload received */
   S32  relRx;                  /* Release received */
   S32  relCmpltRx;             /* Release Complete received */
   S32  facRx;                  /* Facility Request received */
   S32  facAckRx;               /* Facility Ack received */
   S32  facRejRx;               /* Facility Reject received */
   S32  initAdrRx;              /* Initial Address received */
   S32  infoReqRx;              /* Info Request received */
   S32  infoRx;                 /* Info received */
   S32  passAlongRx;            /* Pass Along received */
   S32  subsAdrRx;              /* Subsequent Address received */
   S32  usrToUsrRx;             /* User to User received */
   S32  uneqCirIdRx;            /* Unequipped Circuit ID received */
#if SS7_ANS92
   S32  cirReserveRx;           /* circuit reservation  received */
   S32  cirResAckRx;            /* circuit reservation ack received */
#endif
#if (SS7_ANS88 || SS7_ANS92)
   S32  exitRx;                 /* exit received */
#endif
   S32  netResMgmtRx;           /* Network Resourse received */
   S32  netIdReqRx;             /* Network Id Request received */
   S32  netIdRspRx;             /* Network Id Request received */
#if SS7_SINGTEL
   S32  malCllPrntRx;           /* Malicious Call Print received */
   S32  chargeRx;               /* Charge received */
   S32  trfChngeRx;             /* Tariff change received */
   S32  chargeAckRx;            /* Charge ack received */
#endif
#if SS7_Q767IT
   S32  comRx;                  /* Call Offering received */
#endif
} IsupNSapStats;

#ifndef _TX_ISUPMGMT_SOURCE_
S16  TXISUPMGMTFUNC isupInitMgmtAPI(U8 board, U8 srcEnt);
S16  TXISUPMGMTFUNC isupTermMgmtAPI(U8 board);
void TXISUPMGMTFUNC isupInitGenCfg(IsupGenParms *cfg, U32 opc);
S16  TXISUPMGMTFUNC isupGenCfg(U8 board, IsupGenParms *cfg);
void TXISUPMGMTFUNC isupInitUSapCfg(IsupUSapCfg *cfg, S16 switchType);
S16  TXISUPMGMTFUNC isupUSapCfg(U8 board, IsupUSapCfg *cfg, U16 sapId);
void TXISUPMGMTFUNC isupInitNSapCfg(IsupNSapCfg *cfg, S16 switchType);
S16  TXISUPMGMTFUNC isupNSapCfg(U8 board, IsupNSapCfg *cfg, S16 spId);
void TXISUPMGMTFUNC isupInitCircCfg(IsupCircCfg *cfg, U32 dpc);
S16  TXISUPMGMTFUNC isupCircCfg(U8 board, IsupCircCfg *cfg);
void TXISUPMGMTFUNC isupInitRouteCfg(IsupRouteCfg *cfg);
S16  TXISUPMGMTFUNC isupRouteCfg(U8 board, IsupRouteCfg *cfg);
S16  TXISUPMGMTFUNC isupResetCircuit(U8 board, U32 circId);
S16  TXISUPMGMTFUNC isupValidateCircuit(U8 board, U32 circId);
S16  TXISUPMGMTFUNC isupBlockCircuit(U8 board, U32 circId);
S16  TXISUPMGMTFUNC isupUnblockCircuit(U8 board, U32 circId);
S16  TXISUPMGMTFUNC isupDeleteCircuit(U8 board, U32 circId);
S16  TXISUPMGMTFUNC isupBillingControl(U8 board, S16 state);
S16  TXISUPMGMTFUNC isupStatusControl(U8 board, S16 state);
S16  TXISUPMGMTFUNC isupTraceControl(U8 board, U32 flags);
S16  TXISUPMGMTFUNC isupNSapStats(U8 board, S16 sapId, IsupNSapStats *stats);
S16  TXISUPMGMTFUNC isupCircuitStats(U8 board, U32 circId, IsupCircStats *stats);
S16  TXISUPMGMTFUNC isupCircuitStatus(U8 board, U32 circId, IsupCircStatus *status);
S16 TXISUPMGMTFUNC isupGetGenCfg(U8 board, IsupGenParms *cfg);
S16 TXISUPMGMTFUNC isupGetUSapCfg(U8 board, IsupUSapCfg *cfg, U16 sapId);
S16 TXISUPMGMTFUNC isupGetNSapCfg(U8 board, IsupNSapCfg *cfg, S16 spId);
S16 TXISUPMGMTFUNC isupGetCircCfg(U8 board, IsupCircCfg *cfg, U32 circuitId);
S16 TXISUPMGMTFUNC isupGetRouteCfg(U8 board, IsupRouteCfg *cfg);
#endif

#endif /* _ISUPUSER_H_ */
