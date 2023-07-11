
/*****************************************************************************
******************************************************************************
**
**   mvipuser.h
**
**      Message passed across dual port ram from host pc applications
**		to MVIP task for controlling TX2000 MVIP adapter switch fabric.
**
**   Revision History:
**
**   ! Date    ! Who ! Tag ! Comments
**   ----------------------------------------------------------------------
**   02 Nov 95  JMD           Created
******************************************************************************
*****************************************************************************/

/*************************************************************************
**                                                                      **
**                         PROPRIETARY NOTICE                           **
**                                                                      **
**                      Copyright (c) 1995-2001                         **
**                       by NMS Communications                          **
**                                                                      **
**  The following is licensed program material and is considered        **
**  proprietary and confidential.  No part of this program may be       **
**  reproduced or used in any form or by any means without the express  **
**  written permission of NMS Communications.                           **
**                                                                      **
*************************************************************************/

#ifndef _MVIPUSER_H_
#define _MVIPUSER_H_

#include "tdmuser.h"
#include "dpruser.h"

#ifdef UNIX
#pragma pack(1)
#endif  /* UNIX */

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
    DPRH            hdr;        /* standard dpr header from dpruser.h */
    unsigned short  rqstCode;   /* request codes from tdmuser.h */
    unsigned long   tag;        /* opaque tag passed back in response */
}
TxMvipReqHdr;


/* General header included in all responses back to PC */

typedef struct txMvipRespHdr
{
    DPRH            hdr;        /* standard dpr header from dpruser.h */
    unsigned short  rqstCode;   /* request codes from tdmuser.h */
    unsigned long   tag;        /* opaque tag passed back in response */
    short           status;     /* status of operation */
}
TxMvipRespHdr;


/* Config Clock Request
 *
 * Request code:	CONFIG_CLOCK (0x20)
 */

typedef struct configClockReq
{
    TxMvipReqHdr    rqst;       /* request header */
    unsigned char   clockMode;  /* mode for main MVIP bus clocks */
    unsigned char   sec8kMode;  /* mode for MVIP bus sec8K clock */
    unsigned char   network;    /* which t1/e1 is source for clock when
                                 * one of above modes specifies network src */
    unsigned char   spare1;     /* pad to even byte length */
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
    unsigned char   stream;     /* switch block stream number [0..15, 16, 18] */
    unsigned char   timeslot;   /* timeslot number [0..31] */
}
ChannelStatusReq;

typedef struct channelStatusResp
{
    TxMvipRespHdr   resp;       /* response header */
    unsigned char   chanMode;   /* disabled | pattern | connected (tdmuser.h) */
    unsigned char   srcStream;  /* source stream [0..15, 16, 18] when connected */
    unsigned char   srcTimeslot;    /* source timeslot [0..31] when connected */
    unsigned char   direction;  /* direction (fwd/reverse) for MVIP only */
    unsigned char   indirection;    /* direction (fwd/reverse) of src chan */
    unsigned char   pattern;    /* current output when in pattern mode */
    unsigned char   inputSample;    /* last input sample byte */
    unsigned char   filler;     /* evenizes the structure size */
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
    unsigned short  domain;     /* domain bit mask (see mvip-90 spec) */
    unsigned short  routing;    /* routing capabilities bit mask */
    unsigned short  blocking;   /* blocking potential bit mask */
    unsigned short  networks;   /* number of network streams (0 or 2) */
    unsigned short  channels[2];    /* channels on each network interface:
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
    unsigned char   command;    /* desired operation: reset, disable, enable */
    unsigned char   spare1;     /* pad to even byte length */
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
    unsigned char   stream;     /* output stream number [0..15, 16, 18] */
    unsigned char   timeslot;   /* output timeslot number [0..31] */
    unsigned char   chanMode;   /* disabled | pattern | connected (tdmuser.h) */
    unsigned char   srcStream;  /* source stream [0..15, 16, 18] */
    unsigned char   srcTimeslot;    /* source timeslot [0..31] */
    unsigned char   duplex;     /* half or full duplex connection */
    unsigned char   message;    /* pattern to output when mode = pattern */
    unsigned char   spare1;     /* pad to even byte length */
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
    unsigned char   clockMode;  /* mode for main MVIP bus clocks */
    unsigned char   sec8kMode;  /* mode for MVIP bus sec8K clock */
    unsigned char   network;    /* which t1/e1 is source for clock when
                                 * one of above modes specifies network src */
    unsigned char   swStatus;   /* switch status: reset, disabled, enabled */
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

#ifdef UNIX
#pragma pack()
#endif  /* UNIX */

#endif
