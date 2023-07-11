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
#ifndef _MTP2MAPI_H_
#define _MTP2MAPI_H_

#include "ss7type.h"
#include "txcpi.h"

/* define the calling conventions for the API functions for various
 * operating systems - NOTE: API callers should never define the
 * preprocessor constant "_TX_MTP2_SOURCE_"; this is only for use
 * by the MTP2 API source code itself.
 */

/* OS2: MTP2 API is a DLL */
#ifdef __OS2__
#ifdef _TX_MTP2_SOURCE_
	/* MTP2 API source definition */
#define     TXMTP2FUNC               extern _export _syscall
#else
	/* MTP2 API caller's definition */
#define     TXMTP2FUNC               _syscall
#endif	/* _TX_MTP2_SOURCE_ */

/* WIN32: MTP2 API is a DLL */
#elif  WIN32	                        /* WIN32 */
#ifdef _TX_MTP2_SOURCE_
	/* MTP2 API source definition */
#define     TXMTP2FUNC               __declspec( dllexport ) WINAPI
#else
	/* MTP2 API caller's definition */
#define     TXMTP2FUNC               WINAPI
#endif	/* _TX_MTP2_SOURCE_ */

/* all others: statically linked library */
#else
#define     TXMTP2FUNC
#endif

#ifdef UNIX
#ifndef TRUE
#define TRUE  1
#define FALSE 0
#endif
#endif

/* Macro for initializing a timer (value 0 => disable) */
#define MTP2_SET_TIMER( atimer, avalue )                    \
    atimer.value = avalue;                                  \
    if( atimer.value != 0 )                                 \
        atimer.enable = 1;                                  \
    else                                                    \
        atimer.enable = 0;

/* Constants */

#ifndef MTP_MAX_LINKS
#define MTP_MAX_LINKS            32
#endif

/* Link types */
#define MTP2LNK_DEFAULT           0   /* link type for management message */
#define MTP2LNK_ANSI              1   /* link type ANSI */
#define MTP2LNK_CCITT             2   /* link type CCITT */
#define MTP2LNK_ANSI88            3   /* link type ANSI 88 */
#define MTP2LNK_JNTT              7   /* link type Japan (NTT variant) */
#define MTP2LNK_JTTC              8   /* link type Japan (TTC variant) */

/* Subservice selections */
#define MTP2SSF_INTL              0       /* international */
#define MTP2SSF_SPARE             1       /* spare */
#define MTP2SSF_NAT               2       /* national */
#define MTP2SSF_RES               3       /* reserved */

/* Control Request codes */
#define MTP2_CTRL_ALARM_LVL		101	/* Set Alarm level */
#define MTP2_CTRL_FLOWCTL_ON	102	/* Start flow control */
#define MTP2_CTRL_FLOWCTL_OFF	103	/* Flow Control off */

/*** Mtp1 link cfg definitions ***/

/* share flag enable */
#define NO_FLG_SHARE 0  /* do not share flags between  frames */
#define FLG_SHARE    1  /* share flags between frames */

/* transmit flags/idles */
#define TX_IDLES     0  /* transmit idles between frames */
#define TX_FLGS      1  /* transmit flags between frames */

/* Data encoding */
#define DAT_NRZ      0 /* data format is NRZ */
#define DAT_NRZI     1 /* data format is NRZI */

/* Allowed baud rates for SS7 */
#define BD_4800          0x0d        /* 4800 baud, x.3, scc */
#define BD_9600          0x0e        /* 9600 baud, x.3, scc */
#define BD_14440         0x16        /* 14440 baud, scc */
#define BD_19200         0x0f        /* 19200 baud, x.3, scc */
#define BD_38400         0x18        /* 38400 baud, scc */
#define BD_48000         0x10        /* 48000 baud, x.3, scc */
#define BD_56000         0x11        /* 56000 baud, x.3, scc */
#define BD_64000         0x12        /* 64000 baud, x.3, scc */
#define BD_512000        0x19        /* 512,000 baud, x.3, scc */

/* physIntType */

#define INT_DTE          0           /* acts as dte */
#define INT_DCE          1           /* acts as dce */
#define INT_DTE_MODEM    2           /* acts as dte with modem signals */
#define INT_DCE_MODEM    3           /* acts as dce with modem signals */

#ifdef UNIX
#pragma pack(1)
#endif

/* High speed link bit definitions used in hsBits below */
#define HS_LINK         0x01            /* High speed links are in effect if set */
#define HS_EXT_SEQ      0x02            /* Extended sequence numbers are in effect if set */

/*** Mtp2 Link configuration parameters structure ***/

typedef struct _MTP2LinkCfg         /* MTP level 2 data link SAP configuration */
{
   MemoryId mem;                /* memory region and pool id */
   MemoryId memMac;             /* memory region and pool id for MAC */
   S16  swtch;                  /* protocol type */
   U8   priorDl;                /* priority for data link layer */
   U8   routeDl;                /* route for data link layer */
   U8   selectorDl;             /* upper interface selector */
   U8   entMac;                 /* entity for MAC */
   U8   instMac;                /* instance for MAC */
   U8   priorMac;               /* priority for MAC layer */
   U8   routeMac;               /* route for MAC layer */
   U8   selectorMac;            /* lower interface selector */
   U8   maxOutsFrms;            /* maximum outstanding frames */
   Bool errType;                /* cyclical or normal error checking */
   TimerCfg t1;                 /* timer 1 configuration structure */
   TimerCfg t2;                 /* timer 2 configuration structure */
   TimerCfg t3;                 /* timer 3 configuration structure */
/*   TimerCfg t4;    Removed in Trillium merge */             /* timer 4 configuration structure */
   TimerCfg t5;                 /* timer 5 configuration structure */
   TimerCfg t6;                 /* timer 6 configuration structure */
   TimerCfg t7;                 /* timer 7 configuration structure */
   TimerCfg t10;                /* timer 10 configuration structure */
   TimerCfg t11;                /* timer 11 configuration structure */
   TimerCfg t12;                /* timer 12 configuration structure */
   TimerCfg t13;                /* timer 13 configuration structure */
   TimerCfg congTmr;            /* congestion timer configuration structure */
   U16  provEmrgcy;             /* emergency proving period */
   U16  provNormal;             /* normal proving period */
   U8   lssuLen;                /* one or two byte LSSU length */
   U8   hsBits;                 /* High speed link bits defined above this structure.  Formerly align1 */
   U16  maxFrmLen;              /* max frame length for MSU */
   U8   cfmType;                /* when to send connect confirm */
   Bool congDisc;               /* congestion discard TRUE or FALSE */
   U16  sdD;                    /* Error count decrement rate <JMP> */
   U8   sdT;                    /* SUERM error rate threshold */
   U8   sdTie;                  /* AERM emergency error rate threshold */
   U8   sdTin;                  /* AERM normal error rate threshold */
   U8   sdN1;                   /* maximum number of MSUs for retransmission */
   U16  sdN2;                   /* maximum number of MSU octets for retrans */
   U8   sdCp;                   /* maximum number of alignment attempts */
   U8   align2;                 /* alignment byte */
   S16  spIdSE;                 /* service provider id */
   U16  dstProcId;              /* processor id */
   U16  isoThresh;              /* Number of packets to queue before sending SIPOs */
   U16  txqThresh1;             /* Threshold level one on MTP2's Tx Queue */
   U16  txqThresh1Abate;        /* Abatement threshold for level two on MTP2's Tx Queue */
   U16  txqThresh2;             /* Threshold level two on MTP2's Tx Queue */
   U16  txqThresh2Abate;        /* Abatement threshold for level two on MTP2's Tx Queue */
   U16  sapThresh;              /* Threshold level on MTP2's upward bound SAP queue */
   U16  sapThreshAbate;         /* Abatement threshold level for MTP2's SAP Queue */
   /* MTP level 1 parameters <JMP> */
   S16  baud;                   /* baud rate (4.8, 9.6, 19.2, 28.8, 38.4, 56, 64) */
   U8   portNum;                /* port number */
   U8   portType;               /* port type */
   S16  physIntType;            /* Physical interface type (DCE/DTE) */
   U8   dataEncoding;           /* Data encoding (NRZ/NRZI) */
   U8   flgShare;               /* Share flags ? */
   U8   flgIdle;                /* Use idles (True) or flags (False) */
   U8   numFlg;                 /* Number of additional flag chars between frames */
   U32  idleFreq;               /* Transmit frequency of FISU's when done by software (in ms). Done at config */
   U32  rtFreq;                 /* Retransmit frequency of other SU's when done by software (in ms). Done at transmit */
} MTP2LinkCfg;

typedef struct _MTP2LinkStats         /* MTP level 2 link statistics */
{
    DateTime DT;                 /* Date / timestamp */
    Duration Dura;               /* Duration */
    S16   Action;                /* Action to take (ZEROSTS or NOZEROSTS) */
    S16   spare1;                /* Alignment */
    U32   inService;             /* start of in-service */
    U32   lclBusy;               /* duration of local-busy */
    U32   slFailAll;             /* all reasons for a signalling link failure */
    U32   slFailAb;              /* Abnormal FIBR/BSNR link failure */
    U32   slFailAck;             /* delay of acknowledgement link failure */
    U32   slFailErr;             /* excessive error rate link failure */
    U32   slFailCong;            /* excessive congestion link failure */
    U32   slFailAlign;           /* alignment link failure */
    U32   slNSUErr;              /* number of signal units in error */
    U32   slNegAck;              /* number of negative acknowledgements */
    U32   nSifSioTx;             /* number of SIF/SIO packets transmitted */
    U32   nRetrans;              /* number of octets transmitted */
    U32   mTx;                   /* information frames transmitted */
    U32   lTx;                   /* receive ready frames transmitted */
    U32   fTx;                   /* receive not ready frames transmitted */
    U32   nSifSioRx;             /* number of SIF/SIO packets received */
    U32   mRx;                   /* information frames received */
    U32   lRx;                   /* receive ready frames received */
    U32   fRx;                   /* receive not ready frames received */
    U16   txCnt;                 /* Number of messages on the transmit queue */
    U16   hiTxCnt;               /* Hiqh water number of messages on the transmit queue */
    U16   rtbCnt;                /* Number of messages on the retransmit queue */
    U16   hiRtbCnt;              /* Hiqh water number of messages on the retransmit queue */
    U16   ltxCnt;                /* Number of messages on the lower transmit queue */
    U16   hiLtxCnt;              /* Hiqh water number of messages on the lower transmit queue */
    U16   sapCnt;                /* Number of messages on the inbound sap queue */
    U16   hiSapCnt;              /* Hiqh water number of messages on the inbound sap queue */
} MTP2LinkStats;


typedef struct _MTP2LinkStatus         /* MTP level 2 - Link status */
{
    DateTime DT;                 /* Date / timestamp */
    U8   hlSt;                   /* sap state */
    U8   psOutsFrm;              /* outstanding frames to MAC */
    S16  cntMaDrop;              /* frames dropped by MAC */
    U8   llSt;                   /* link level matrix state */
    U8   lclBsy;                 /* local busy */
    Bool remBsy;                 /* remote busy */
    U8   fsn;                    /* forward sequence number */
    U8   bsn;                    /* backward sequence number */
    U8   flcSt;                  /* flow control state */
} MTP2LinkStatus;

typedef struct _MTP2CtrlRqst            /* MTP Level 3 - control request */
{
    DateTime DT;                /* Date / timestamp */
    U8  subAction;              /* Sub action */
    U8  action;                 /* Main action */
    U8  spare1;                 /* Alignment */
    U8  spare2;                 /* Alignment */
} MTP2CtrlRqst;

#ifdef UNIX
#pragma pack()
#endif

/* Error type returned by API functions */
typedef S16 MTP2_STATUS;   /* redefine for portability */

/* Mgmt API return codes */
#define MTP2_SUCCESS    0           /* Successful */
#define MTP2_LNKTYPE    0x1001      /* Invalid link/switch type */
#define MTP2_PARAM      0x1002      /* Invalid parameter */
#define MTP2_BOARD      0x1004      /* board number out of range */
#define MTP2_DRIVER     0x1005      /* CPI driver returned error        */
#define MTP2_HANDLE     0x1006      /* Board not previously initialized */
#define MTP2_TIMEOUT    0x1007      /* No response from board */
#define MTP2_RESPONSE   0x1008      /* Wrong response from board */

#ifdef __cplusplus
extern "C" {
#endif

void        TXMTP2FUNC Mtp2Geterror       ( MTP2_STATUS errcode, char **pMsg );
MTP2_STATUS TXMTP2FUNC Mtp2MgmtInit       ( U8 board, U8 srcEnt, U8 srcInst );
MTP2_STATUS TXMTP2FUNC Mtp2MgmtTerm       ( U8 board );
MTP2_STATUS TXMTP2FUNC Mtp2MgmtCtrl       ( U8 board, S16 entity, U8 action );

MTP2_STATUS TXMTP2FUNC Mtp2InitLinkCfg    ( U8 board, MTP2LinkCfg *pLinkCfg, S16 linkNo, U8 linkType );
MTP2_STATUS TXMTP2FUNC Mtp2SetLinkCfg     ( U8 board, MTP2LinkCfg *pLinkCfg );
MTP2_STATUS TXMTP2FUNC Mtp2GetLinkCfg     ( U8 board, MTP2LinkCfg *pLinkCfg, S16 linkNo);

MTP2_STATUS TXMTP2FUNC Mtp2LinkStatus     ( U8 board, S16 linkNo, MTP2LinkStatus *pStatus);
MTP2_STATUS TXMTP2FUNC Mtp2LinkStats      ( U8 board, S16 linkNo, MTP2LinkStats *pStats, Bool bReset);

#ifdef __cplusplus
}
#endif


#endif	/* _MTP2MAPI_H_	 */
