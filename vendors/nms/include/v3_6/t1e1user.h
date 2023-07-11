/*****************************************************************************
******************************************************************************
**
**   t1e1user.h
**
**      Message passed across dual port ram from host pc applications
**		to T1E1 task for controlling TX2000 T1/E1 adapter.
**
**   Revision History:
**
**   ! Date    ! Who ! Tag ! Comments
**   ----------------------------------------------------------------------
**   03 Apr 95  JMD           Created
******************************************************************************
*****************************************************************************/

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

#ifndef _T1E1USER_H_
#define _T1E1USER_H_

#include "t1e1type.h"
#include "dpruser.h"

#ifdef __sun
#pragma pack(1)
#endif	/* __sun */

/* Note: request codes, parameter value "defines" and status
 * codes are defined in tdmuser.h.
 */

/* t1e1 device type - here for lack of a better place */
#define DEVTYPE_T1E1  110

/*
 * T1/E1 Command Codes
 */
#if 0

#define T1_CONFIG_CARRIER               0x30
#define T1_CARRIER_STATUS               0x33
#define T1_CONDITION_CHAN               0x34
#define T1_SUPERVISE_CARRIER            0x37
#define T1_CONTROL_CARRIER              0x42
#define T1_CONFIG_CHANNEL               0x43
#define T1_CHANNEL_STATUS               0x44
#define T1_CONTROL_CHAN                 0x45

#endif

#define T1_PERF_REPORT					0x46

/* General header included in all requests from host PC */

typedef struct txT1E1ReqHdr
{
  DPRH            hdr;      /* standard dpr header from dpruser.h */
	unsigned short	rqstCode;	/* request codes from tdmuser.h */
  unsigned char   carrier;  /* which T1/E1 line (A or B) */
  unsigned char   spare1;   /* spare byte for alignment */
  unsigned long   tag;      /* opaque tag passed back in response */
} TxT1E1ReqHdr;


/* General header included in all responses back to PC */

typedef struct txT1E1RespHdr
{
  DPRH            hdr;        /* standard dpr header from dpruser.h */
  unsigned short  rqstCode;   /* request codes from tdmuser.h */
  unsigned char   carrier;    /* which T1/E1 line (A or B) */
  unsigned char   spare1;     /* spare byte for alignment */
  unsigned long   tag;        /* opaque tag passed back in response */
  short           status;     /* status of operation */
  unsigned char   pad_end[2]; /* pad to 32-bit aligned structure size */
} TxT1E1RespHdr;


/* Config Carrier Request
 *
 * Request code:	CONFIG_CARRIER (0x30)
 */

typedef struct configCarrierReq
{
  TxT1E1ReqHdr    rqst;       /* request header */
  unsigned char   frameMode;  /* framing mode for line */
  unsigned char   coding;     /* coding technique */
  unsigned char   lineBldOut; /* equalization/line build out */
  unsigned char   debounce;   /* reserved for future use */
  unsigned char   robbedBit;  /* enables or disables robbed
                               * bit signalling on this line */
  unsigned char   loopMaster; /* sets TX2000 as timing master or slave */
  unsigned char   pad_end[2]; /* pad to 32-bit aligned structure size */
} ConfigCarrierReq;

typedef struct configCarrierResp
{
  TxT1E1RespHdr   resp;       /* response header */
} ConfigCarrierResp;


/* Carrier Status Request
 *
 * Request code:	CARRIER_STATUS (0x33)
 */

typedef struct carrierStatusReq
{
  TxT1E1ReqHdr    rqst;       /* request header */
  unsigned char   flags;      /* options */
  unsigned char   spare1;     /* spare for alignment */
  unsigned char   pad_end[2]; /* pad to 32-bit aligned structure size */
} CarrierStatusReq;

typedef struct carrierStatusResp
{
  TxT1E1RespHdr   resp;         /* response header */
  unsigned char   alarmState;   /* alarm status */
  unsigned char   lastAlmState; /* previous alarm status */
  unsigned char   wordalign;
  unsigned char   syncState;    /* current synchronization state */
  unsigned char   frameMode;    /* current framing mode */
  unsigned char   coding;       /* coding technique */
  unsigned char   lineBldOut;   /* equalization/line build out */
  unsigned char   debounce;     /* reserved for future use */
  unsigned char   robbedBit;    /* robbed bit signalling enabled/disabled */
  unsigned char   loopMaster;   /* TX2000 timing master or slave */
  unsigned short  currInt;      /* number of seconds in current interval */
  TxT1E1Stats     currStats;    /* current interval statistics */
  unsigned short  validInts;    /* number of 15-min intervals in summary */
  unsigned char   pad_1[2];     /* natural alignment padding */
  TxT1E1Stats     sumStats;     /* 24-hour summary statistics */
  unsigned short  pvcs;         /* Accumulated path code violations */
  unsigned short  lvcs;         /* Accumulated line code violations */
  unsigned short  slips;        /* Accumulated controlled slips */
  unsigned short  ebits;        /* Accumulated E-bit counts (E1) */
} CarrierStatusResp;

/* Performance Report Request
 *
 * Request code:	PERF_REPORT (0x46)
 */

typedef struct perfReportReq
{
  TxT1E1ReqHdr    rqst;       /* request header */
  unsigned char   flags;      /* options */
  unsigned char   spare1;     /* spare for alignment */
  unsigned char   pad_end[2]; /* pad to 32-bit aligned structure size */
} PerfReportReq;

typedef struct perfReportResp
{
  TxT1E1RespHdr   resp;         /* response header */
  unsigned short  currInt;      /* number of seconds in current interval */
  unsigned char   pad_1[2];     /* natural alignment padding */
  TxT1E1Stats     currStats;    /* current interval statistics */
  unsigned short  validInts;    /* number of 15-min intervals so far */
  unsigned char   pad_2[2];     /* natural alignment padding */
  TxT1E1Stats     intStats[96]; /* last 96 15-min interval statistics */
  TxT1E1Stats     sumStats;     /* 24-hour summary statistics */
  unsigned short  pvcs;         /* Accumulated path code violations */
  unsigned short  lvcs;         /* Accumulated line code violations */
  unsigned short  slips;        /* Accumulated controlled slips */
  unsigned short  ebits;        /* Accumulated E-bit counts (E1) */
} PerfReportResp;


/* Control Carrier Request
 *
 * Request code:	CONTROL_CARRIER (0x42)
 */

typedef struct ctrlCarrierReq
{
  TxT1E1ReqHdr    rqst;         /* request header */
  unsigned char   alarmState;   /* sets line into alarm state */
  unsigned char   loopback;     /* sets line into loopback mode */
  unsigned char   pad_end[2];   /* pad to 32-bit aligned structure size */
} CtrlCarrierReq;

typedef struct ctrlCarrierResp
{
  TxT1E1RespHdr   resp;         /* response header */
} CtrlCarrierResp;


/* Condition Channel Request
 *
 * Request code:	CONDITION_CHAN (0x34)
 */

typedef struct condChanReq
{
  TxT1E1ReqHdr    rqst;     /* request header */
  unsigned char   channel;  /* channel number: 0-31 or 0xFF (all) */
  unsigned char   control;  /* conditioning on or off */
  unsigned char   pattern;  /* conditioning pattern (if on) */
  unsigned char   spare1;   /* pad to even byte length */
} CondChanReq;

typedef struct condChanResp
{
  TxT1E1RespHdr   resp;     /* response header */
} CondChanResp;


/* Channel Connect Request
 *
 * Request code:	CONFIG_CHANNEL (0x43)
 */

typedef struct configChanReq
{
  TxT1E1ReqHdr    rqst;         /* request header */
  unsigned char   channel;      /* channel number: 0-31 */
  unsigned char   transparent;  /* sets channel to transparent mode */
  unsigned char   pad_end[2];   /* pad to 32-bit aligned structure size */
} ConfigChanReq;

typedef struct configChanResp
{
  TxT1E1RespHdr   resp;         /* response header */
} ConfigChanResp;


/* Channel Status Request
 *
 * Request code:	CHANNEL_STATUS (0x44)
 */

typedef struct channelStatusReq
{
  TxT1E1ReqHdr    rqst;         /* request header */
} ChannelStatusReq;

typedef struct channelStatusResp
{
  TxT1E1RespHdr   resp;         /* response header */
  unsigned long   transparent;  /* bit mask identifies transparent channels */
  unsigned long   rxABCD[4];    /* received ABCD bit values for all channels */
  unsigned long   txABCD[4];    /* transmit ABCD bit values for all channels */
} ChannelStatusResp;

/* Supervise Carrier Request
 *
 * Request code:	SUPERVISE_CARRIER (0x37)
 */

typedef struct supvCarrierReq
{
  TxT1E1ReqHdr    rqst;         /* request header */
  unsigned char   notifMask;    /* notification options */
  unsigned char   spare1;       /* spare for alignment */
  unsigned char   pad_end[2];   /* pad to 32-bit aligned structure size */
} SupvCarrierReq;

typedef struct supvCarrierResp
{
  TxT1E1RespHdr   resp;         /* response header */
} SupvCarrierResp;

/* unsolicited messages to host on T1E1 status channel; these are
 * notifications of carrier status changes, alarm conditions, or
 * performance reports.
 */
typedef struct notifUmsg
{
  DPRH            hdr;        /* standard dpr header from dpruser.h */
  union { /* msg bodies from t1e1type.h */
    TxT1E1UHdr    uhdr;       /* common header for all unsolicited msgs */
    TxT1E1UStat   stat;       /* alarm or synch state change */
    TxT1E1Perf15  perf15;     /* 15-minute performance report */
    TxT1E1Perf24  perf24;     /* 24-hour performance report */
		} umsg;
} NotifUmsg;


/* define union of all possible requests and responses */
typedef union allT1E1Pkts {
  TxT1E1ReqHdr        req;            /* common request header */
  TxT1E1RespHdr       resp;           /* common response header */
  ConfigCarrierReq    confCarrReq;
	ConfigCarrierResp		confCarrResp;
	CarrierStatusReq		carrStatReq;
	CarrierStatusResp		carrStatResp;
  PerfReportReq       perfRepReq;
	PerfReportResp			perfRepResp;
	CtrlCarrierReq			ctrlCarrReq;
	CtrlCarrierResp			ctrlCarrResp;
  CondChanReq         condChanReq;
  CondChanResp        condChanResp;
  ConfigChanReq       confChanReq;
	ConfigChanResp			confChanResp;
	ChannelStatusReq		chanStatReq;
	ChannelStatusResp		chanStatResp;
	SupvCarrierReq			supvCarrReq;
	SupvCarrierResp			supvCarrResp;
  NotifUmsg           notifMsg;
} AllT1E1Pkts;

#define T1E1PKTS_SIZ    sizeof( AllT1E1Pkts )

#ifdef __sun
#pragma pack()
#endif	/* __sun */

#endif

