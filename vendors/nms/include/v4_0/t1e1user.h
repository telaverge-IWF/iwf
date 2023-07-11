/*****************************************************************************
 *
 * t1e1user.h - Message passed across dual port ram from host pc applications
 *              to T1E1 task for controlling TX T1/E1 trunks.
 *
 *****************************************************************************/

/*****************************************************************************
 *
 *                         PROPRIETARY NOTICE
 *
 *                      Copyright (c) 1988-2003
 *                       by NMS Communications.
 *
 *  The following is licensed program material and is considered
 *  proprietary and confidential.  No part of this program may be
 *  reproduced or used in any form or by any means without the express
 *  written permission of NMS Communications.
 *
 *****************************************************************************/

#ifndef _T1E1USER_H
#define _T1E1USER_H

/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
 * PACKING: pack on 1-byte boundaries
 *xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
#ifdef UNIX
#pragma pack(1)
#endif
#ifdef __HIGHC__
#pragma Push_align_members(1)
#endif
#ifdef _WINNT
#pragma pack(1)
#endif
#ifdef _XCODE_
#pragma maxalign(1)
#endif

#include <txnuser.h>            /* primitive field type definitions */
#include "dpruser.h"
#include "t1e1type.h"

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
    U16         rqstCode;   /* request codes from tdmuser.h */
    U8          carrier;    /* which T1/E1 line (A or B) */
    U8          tag;        /* opaque tag passed back in response */
}
TxT1E1ReqHdr;


/* General header included in all responses back to PC */

typedef struct txT1E1RespHdr
{
    U16         rqstCode;   /* request codes from tdmuser.h */
    U8          carrier;    /* which T1/E1 line (A or B) */
    U8          tag;        /* opaque tag passed back in response */
    S16         status;     /* status of operation */
    U8          pad_end[2]; /* pad to 32-bit aligned structure size */
}
TxT1E1RespHdr;


/* Config Carrier Request
 *
 * Request code:	CONFIG_CARRIER (0x30)
 */

typedef struct configCarrierReq
{
    TxT1E1ReqHdr    rqst;       /* request header */
    U8              frameMode;  /* framing mode for line */
    U8              coding;     /* coding technique */
    U8              lineBldOut; /* equalization/line build out */
    U8              debounce;   /* reserved for future use */
    U8              robbedBit;  /* enables or disables robbed
                                 * bit signalling on this line */
    U8              loopMaster; /* sets TX as timing master or slave */
    U8              pad_end[2]; /* pad to 32-bit aligned structure size */
}
ConfigCarrierReq;

typedef struct configCarrierResp
{
    TxT1E1RespHdr   resp;       /* response header */
}
ConfigCarrierResp;


/* Carrier Status Request
 *
 * Request code:	CARRIER_STATUS (0x33)
 */

typedef struct carrierStatusReq
{
    TxT1E1ReqHdr  rqst;       /* request header */
    U8            flags;      /* options */
    U8            spare1;     /* spare for alignment */
    U8            pad_end[2]; /* pad to 32-bit aligned structure size */
}
CarrierStatusReq;

typedef struct carrierStatusResp
{
    TxT1E1RespHdr   resp;       /* response header */
    U8              alarmState; /* alarm status */
    U8              lastAlmState;   /* previous alarm status */
    U8              wordalign;
    U8              syncState;  /* current synchronization state */
    U8              frameMode;  /* current framing mode */
    U8              coding;     /* coding technique */
    U8              lineBldOut; /* equalization/line build out */
    U8              debounce;   /* reserved for future use */
    U8              robbedBit;  /* robbed bit signalling enabled/disabled */
    U8              loopMaster; /* TX timing master or slave */
    U16             currInt;    /* number of seconds in current interval */
    TxT1E1Stats     currStats;  /* current interval statistics */
    U16             validInts;  /* number of 15-min intervals in summary */
    U8              pad_1[2];   /* natural alignment padding */
    TxT1E1Stats     sumStats;   /* 24-hour summary statistics */
    U16             pvcs;       /* Accumulated path code violations */
    U16             lvcs;       /* Accumulated line code violations */
    U16             slips;      /* Accumulated controlled slips */
    U16             ebits;      /* Accumulated E-bit counts (E1) */
}
CarrierStatusResp;

/* Performance Report Request
 *
 * Request code:	PERF_REPORT (0x46)
 */

typedef struct perfReportReq
{
    TxT1E1ReqHdr    rqst;       /* request header */
    U8              flags;      /* options */
    U8              spare1;     /* spare for alignment */
    U8              pad_end[2]; /* pad to 32-bit aligned structure size */
}
PerfReportReq;

typedef struct perfReportResp
{
    TxT1E1RespHdr   resp;       /* response header */
    U16             currInt;    /* number of seconds in current interval */
    U8              pad_1[2];   /* natural alignment padding */
    TxT1E1Stats     currStats;  /* current interval statistics */
    U16             validInts;  /* number of 15-min intervals so far */
    U8              pad_2[2];   /* natural alignment padding */
    TxT1E1Stats     intStats[96];   /* last 96 15-min interval statistics */
    TxT1E1Stats     sumStats;   /* 24-hour summary statistics */
    U16             pvcs;       /* Accumulated path code violations */
    U16             lvcs;       /* Accumulated line code violations */
    U16             slips;      /* Accumulated controlled slips */
    U16             ebits;      /* Accumulated E-bit counts (E1) */
}
PerfReportResp;


/* Control Carrier Request
 *
 * Request code:	CONTROL_CARRIER (0x42)
 */

typedef struct ctrlCarrierReq
{
    TxT1E1ReqHdr    rqst;       /* request header */
    U8              alarmState; /* sets line into alarm state */
    U8              loopback;   /* sets line into loopback mode */
    U8              pad_end[2]; /* pad to 32-bit aligned structure size */
}
CtrlCarrierReq;

typedef struct ctrlCarrierResp
{
    TxT1E1RespHdr   resp;       /* response header */
}
CtrlCarrierResp;


/* Condition Channel Request
 *
 * Request code:	CONDITION_CHAN (0x34)
 */

typedef struct condChanReq
{
    TxT1E1ReqHdr    rqst;       /* request header */
    U8              channel;    /* channel number: 0-31 or 0xFF (all) */
    U8              control;    /* conditioning on or off */
    U8              pattern;    /* conditioning pattern (if on) */
    U8              spare1;     /* pad to even byte length */
}
CondChanReq;

typedef struct condChanResp
{
    TxT1E1RespHdr   resp;       /* response header */
}
CondChanResp;


/* Channel Connect Request
 *
 * Request code:	CONFIG_CHANNEL (0x43)
 */

typedef struct configChanReq
{
    TxT1E1ReqHdr    rqst;       /* request header */
    U8              channel;    /* channel number: 0-31 */
    U8              transparent;    /* sets channel to transparent mode */
    U8              pad_end[2]; /* pad to 32-bit aligned structure size */
}
ConfigChanReq;

typedef struct configChanResp
{
    TxT1E1RespHdr   resp;       /* response header */
}
ConfigChanResp;


/* Channel Status Request
 *
 * Request code:	CHANNEL_STATUS (0x44)
 */

typedef struct channelStatusReq
{
    TxT1E1ReqHdr    rqst;       /* request header */
}
ChannelStatusReq;

typedef struct channelStatusResp
{
    TxT1E1RespHdr   resp;       /* response header */
    U32             transparent;    /* bit mask identifies transparent channels */
    U32             rxABCD[4];  /* received ABCD bit values for all channels */
    U32             txABCD[4];  /* transmit ABCD bit values for all channels */
}
ChannelStatusResp;

/* Supervise Carrier Request
 *
 * Request code:	SUPERVISE_CARRIER (0x37)
 */

typedef struct supvCarrierReq
{
    TxT1E1ReqHdr    rqst;       /* request header */
    U8              notifMask;  /* notification options */
    U8              spare1;     /* spare for alignment */
    U8              pad_end[2]; /* pad to 32-bit aligned structure size */
}
SupvCarrierReq;

typedef struct supvCarrierResp
{
    TxT1E1RespHdr   resp;       /* response header */
}
SupvCarrierResp;

/* define union of all possible requests and responses */
typedef union allT1E1Pkts
{
    TxT1E1ReqHdr    req;        /* common request header */
    TxT1E1RespHdr   resp;       /* common response header */
    ConfigCarrierReq confCarrReq;
    ConfigCarrierResp confCarrResp;
    CarrierStatusReq carrStatReq;
    CarrierStatusResp carrStatResp;
    PerfReportReq   perfRepReq;
    PerfReportResp  perfRepResp;
    CtrlCarrierReq  ctrlCarrReq;
    CtrlCarrierResp ctrlCarrResp;
    CondChanReq     condChanReq;
    CondChanResp    condChanResp;
    ConfigChanReq   confChanReq;
    ConfigChanResp  confChanResp;
    ChannelStatusReq chanStatReq;
    ChannelStatusResp chanStatResp;
    SupvCarrierReq  supvCarrReq;
    SupvCarrierResp supvCarrResp;
}
AllT1E1Pkts;

/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
 * PACKING: return to default
 *xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
#ifdef _XCODE_
#pragma maxalign()
#endif

/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
 * PACKING: return to default
 *xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
#ifdef UNIX
#pragma pack()
#endif
#ifdef _WINNT
#pragma pack()
#endif
#ifdef __HIGHC__
#pragma Pop_align_members
#endif

#endif  /* _T1E1USER_H */
