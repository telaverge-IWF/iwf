/*****************************************************************************
 *
 * mvipuser.h - Message passed across dual port ram from host pc applications
 *             to MVIP task for controlling TX2000 MVIP adapter switch fabric.
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

#ifndef _MVIPUSER_H
#define _MVIPUSER_H

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

#include "tdmuser.h"
#include "dpruser.h"
#include <txnuser.h>            /* primitive field type definitions */

#if 0

/******************************************************************************
* MVIP Command Codes
******************************************************************************/
#define CONFIG_CLOCK          0x20
#define CHANNEL_STATUS        0x11
#define QUERY_SWITCH_CAPS     0x01
#define CONTROL_SWITCH        0x00
#define CHANNEL_CONNECT       0x10
#define SWITCH_STATUS         0x80

/******************************************************************************
* MVIP Control_Switch Command Operations
******************************************************************************/
#define RESET_SWITCH          0
#define DISABLE_SWITCH        1
#define ENABLE_SWITCH         2

/* defines for duplex connection specification */
#define HALF_DUPLEX           0
#define FULL_DUPLEX           1

/******************************************************************************
* defines for MVIP bus channel directions
******************************************************************************/
#define FORWARD_DIR           0
#define BACKWARD_DIR          1

#endif

/* mvip device type - here for lack of a better place */
#define DEVTYPE_MVIP  109

/* General header included in all requests from host PC */

typedef struct txMvipReqHdr
{
    U16             rqstCode;   /* request codes from tdmuser.h */
    U8              tag;        /* opaque tag passed back in response */
    U8              avail[3];
}
TxMvipReqHdr;


/* General header included in all responses back to PC */

typedef struct txMvipRespHdr
{
    U16             rqstCode;   /* request codes from tdmuser.h */
    U8              tag;        /* opaque tag passed back in response */
    U8              avail[3];
    S16             status;     /* status of operation */
}
TxMvipRespHdr;


/* Config Clock Request
 *
 * Request code:	CONFIG_CLOCK (0x20)
 */

typedef struct configClockReq
{
    TxMvipReqHdr    rqst;       /* request header */
    U8              clockMode;  /* mode for main MVIP bus clocks */
    U8              sec8kMode;  /* mode for MVIP bus sec8K clock */
    U8              network;    /* which t1/e1 is source for clock when
                                 * one of above modes specifies network src */
    U8              spare1;     /* pad to even byte length */
}
ConfigClockReq;

typedef struct configClockResp
{
    TxMvipRespHdr   resp;       /* response header */
}
ConfigClockResp;


/* Channel Status Request
 *
 * Request code:	CHANNEL_STATUS (0x11)
 */

typedef struct channelStatusReq
{
    TxMvipReqHdr    rqst;       /* request header */
    U8              stream;     /* switch block stream number [0..15, 16, 18] */
    U8              timeslot;   /* timeslot number [0..31] */
}
ChannelStatusReq;

typedef struct channelStatusResp
{
    TxMvipRespHdr   resp;       /* response header */
    U8              chanMode;   /* disabled | pattern | connected (tdmuser.h) */
    U8              srcStream;  /* source stream [0..15, 16, 18] when connected */
    U8              srcTimeslot;    /* source timeslot [0..31] when connected */
    U8              direction;  /* direction (fwd/reverse) for MVIP only */
    U8              indirection;    /* direction (fwd/reverse) of src chan */
    U8              pattern;    /* current output when in pattern mode */
    U8              inputSample;    /* last input sample byte */
    U8              filler;     /* evenizes the structure size */
}
ChannelStatusResp;


/* Query Swich Capabilities Request
 *
 * Request code:	QUERY_SWITCH_CAPS (0x01)
 */

typedef struct querySwitchCapsReq
{
    TxMvipReqHdr    rqst;       /* request header */
}
QuerySwitchCapsReq;

typedef struct querySwitchCapsResp
{
    TxMvipRespHdr   resp;       /* response header */
    U16             domain;     /* domain bit mask (see mvip-90 spec) */
    U16             routing;    /* routing capabilities bit mask */
    U16             blocking;   /* blocking potential bit mask */
    U16             networks;   /* number of network streams (0 or 2) */
    U16             channels[2];    /* channels on each network interface:
                                     * channels[1] = T1/E1-A, channels[2] = T1/E1-B */
}
QuerySwitchCapsResp;


/* Control Swich Request
 *
 * Request code:	CONTROL_SWITCH (0x00)
 */

typedef struct ctrlSwitchReq
{
    TxMvipReqHdr    rqst;       /* request header */
    U8              command;    /* desired operation: reset, disable, enable */
    U8              spare1;     /* pad to even byte length */
}
CtrlSwitchReq;

typedef struct ctrlSwitchResp
{
    TxMvipRespHdr   resp;       /* response header */
}
CtrlSwitchResp;


/* Channel Connect Request
 *
 * Request code:	CHANNEL_CONNECT (0x10)
 */

typedef struct chanConnReq
{
    TxMvipReqHdr    rqst;       /* request header */
    U8              stream;     /* output stream number [0..15, 16, 18] */
    U8              timeslot;   /* output timeslot number [0..31] */
    U8              chanMode;   /* disabled | pattern | connected (tdmuser.h) */
    U8              srcStream;  /* source stream [0..15, 16, 18] */
    U8              srcTimeslot;    /* source timeslot [0..31] */
    U8              duplex;     /* half or full duplex connection */
    U8              message;    /* pattern to output when mode = pattern */
    U8              spare1;     /* pad to even byte length */
}
ChanConnReq;

typedef struct chanConnResp
{
    TxMvipRespHdr   resp;       /* response header */
}
ChanConnResp;


/* Switch Status Request
 *
 * Request code:	SWITCH_STATUS (0x80)
 */

typedef struct switchStatusReq
{
    TxMvipReqHdr    rqst;       /* request header */
}
SwitchStatusReq;

typedef struct switchStatusResp
{
    TxMvipRespHdr   resp;       /* response header */
    U8              clockMode;  /* mode for main MVIP bus clocks */
    U8              sec8kMode;  /* mode for MVIP bus sec8K clock */
    U8              network;    /* which t1/e1 is source for clock when
                                 * one of above modes specifies network src */
    U8              swStatus;   /* switch status: reset, disabled, enabled */
}
SwitchStatusResp;

/* define union of all possible requests and responses */
typedef union allMvipPkts
{
    TxMvipReqHdr    req;        /* common request header */
    TxMvipRespHdr   resp;       /* common response header */
    ConfigClockReq  confClockReq;
    ConfigClockResp confClockResp;
    ChannelStatusReq chanStatReq;
    ChannelStatusResp chanStatResp;
    QuerySwitchCapsReq querySwCapsReq;
    QuerySwitchCapsResp querySwCapsResp;
    CtrlSwitchReq   ctrlSwReq;
    CtrlSwitchResp  ctrlSwResp;
    ChanConnReq     chanConReq;
    ChanConnResp    chanConResp;
    SwitchStatusReq swStatReq;
    SwitchStatusResp swStatResp;
}
AllMvipPkts;

#define MVIPPKTS_SIZ    sizeof( AllMvipPkts )

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

#endif  /* _MVIPUSER_H */
