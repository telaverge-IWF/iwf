/*****************************************************************************
 *
 * txswi.h - CPKOS Switching Control Packet Protocol Definitions
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

#ifndef _TXSWI_H
#define _TXSWI_H

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

/* ----- dependent includes ----- */
#include <txnuser.h>
/* NOTE: The include file <swidef.h> must be included before including this file.
 *       For TX-based code, include <cosswi.h> (which will include <swidef.h>).
 *       For host-based code, include <swidef.h> directly.
 */

/* NOTE: All fields passed between the TX board and the host system
 *       must be in network byte order.
 *       Use the functions: cpi_cptoh_s(x), cpi_cptoh_l(x),
 *                          cpi_htocp_s(x), cpi_htocp_l(x) as needed.
 */

/*###########################################################################*
 *
 * TX LOCAL STREAM DEFINITIONS
 *
 *###########################################################################*/

/* ----- streams  0 - 63: trunk access (up to 32 trunks - limit based on TX board type) */
#define TX_LS_TRUNK_BASE            0   /* 0 and 1 = Trunk 1 */
#define TX_LS_TRUNK_DELTA           4   /* 4 and 5 = Trunk 2 */
#define TX_LS_TRUNK(trunk_num)      (TX_LS_TRUNK_BASE+((trunk_num - 1)*TX_LS_TRUNK_DELTA))
#define TX_LS_TRUNK_MAX             (TX_LS_TRUNK(32))

/* ----- streams 64 - 71: RESERVED FOR FUTURE USE */

/* ----- streams 72 - 79: communications processor connections */
#define TX_LS_COMM_PRIMARY          72  /* 72 and 73 = primary connection to communications processor */
#define TX_LS_COMM_SECONDARY        74  /* 74 and 75 = secondary connection to communications processor */

/* ----- streams 80 - 95: trunk access when using MVIPAPI */
#define TX_LS_MV_TRUNK_BASE         80  /* 80 = Trunk 1; [trunk numbering scheme used by MVIPAPI] */
#define TX_LS_MV_TRUNK_DELTA         1  /* 81 = Trunk 2 */
#define TX_LS_MV_TRUNK(trunk_num)   (TX_LS_MV_TRUNK_BASE+((trunk_num - 1)*TX_LS_MV_TRUNK_DELTA))

#define TX_LS_COUNT                 96  /* maximum count of TX local streams (actual count board-specific) */

/* ----- raw mode: internal pseudo stream number base when local stream mapping inhibited */
#define TX_LS_RAW       (1<<7)          /* bit set in stream number to indicate RAW MODE */

/* ----- timeslot ranges */
#define TX_LS_TIMESLOT_BASE         0   /* all local stream timeslots begin from this base */
#define TX_LS_TIMESLOT_MAX_T1       23  /* max local timeslot when local stream maps to T1/J1 trunk */
#define TX_LS_TIMESLOT_MAX_E1       31  /* max local timeslot when local stream maps to E1 trunk */
#define TX_LS_TIMESLOT_MAX_COMM     31  /* max local timeslot when local stream maps to communications processor */
#define TX_LS_TIMESLOT_MAX          31  /* maximum local stream timeslot [across all local stream types] */

/*###########################################################################*
 *
 * TX EXTENSIONS TO MVIP95 INTERFACE
 *
 *###########################################################################*/

#define MVIP95_X_MASTER_COMPAT      (3<<2)  /* mask of bits controlling master of compatibility clocks */
#define MVIP95_X_MASTER_COMPAT_2    (1<<2)  /* master compatibility clocks @ 2 MHz */
#define MVIP95_X_MASTER_COMPAT_4    (2<<2)  /* master compatibility clocks @ 4 MHz */
#define MVIP95_X_MASTER_COMPAT_8    (3<<2)  /* master compatibility clocks @ 8 MHz */
#define MVIP95_X_MTP1_NOBOUNCE      (1<<31) /* bit set = inhibit automatic bouncing of all MTP1 channels */

/* ----- additional device type choices ----- */
#define MVIP95_X_TRUNK_DEVICE       0xA0    /* T1/E1/J1 trunk device */
#define MVIP95_X_COMMPROC_DEVICE    0xA1    /* communications processor device */
#define MVIP95_X_FRAMER_DEVICE      0xB0    /* connection to quad T1/E1 framer */
#define MVIP95_X_NOTUSED_DEVICE     0xF0    /* local stream is not used (or field not used) */

/* ----- additional bus type choices (used when defining a port) ----- */
#define MVIP95_X_E1_MAXSLOT         31      /* max unmapped E1 timeslot (E1 range:0..31) */
#define MVIP95_X_T1_MAXSLOT         23      /* max unmapped T1|J1 timeslot (T1/J1 range:0..23) */

/* ----- additional clock source choices ----- */
#define MVIP95_X_SOURCE_HMVIP       0x10    /* /C16+/-, /C4, C2 and /FR_COMP */
#define MVIP95_X_SOURCE_SC2         0x11    /* SCLKX2 and /FR_COMP [2.048 MHz clock] */
#define MVIP95_X_SOURCE_SC4         0x12    /* SCLK, SCLKX2 and /FR_COMP [4.096 MHz clock] */
#define MVIP95_X_SOURCE_SC8         0x13    /* SCLK, SCLKX2 and /FR_COMP [8.192 MHz clock] */

/* ----- additional clock options ----- */
#define MVIP95_X_CLK_OPTIONS        (0xFF<<16)  /* mask of all clock options */
#define MVIP95_X_CLK_PAS            (1<<16) /* alternate phase alignment (SLIDE) [default SNAP] */
#define MVIP95_X_CLK_CKI            (1<<17) /* invert clock output [default NORMAL] */
#define MVIP95_X_CLK_C8IS           (1<<18) /* MC-1, A and B clock inputs interpreted as /C4 [default ECTF] */
#define MVIP95_X_CLK_C8C4           (1<<19) /* MC-1, inverted 4.096 MHz [default ECTF] */
#define MVIP95_X_CLK_CFW            (1<<20) /* Wide (244 ns) /FR_COMP [default NARROW (122 ns)] */

/* ----- additional stream speed values ----- */
#define MVIP95_X_3STATE_STREAM_SPEED    0xFF    /* stream speed at 3-state setting */

/*###########################################################################*
 *
 * TX EXTENSIONS TO THE SWI INTERFACE
 *
 *###########################################################################*/

/*****************************************************************************
 * EXTENDED Switch Status - supporting MVIP-90 MVIPAPI request: TxSwitchStatus
 *****************************************************************************/
typedef struct
{
    U32 state;                    /* current state of the switch */
#define MVIP95_X_STATE_ENABLED  1   /* switch is currently enabled */
#define MVIP95_X_STATE_DISABLED 2   /* switch is currently disabled */

    U32 clocksource;
    U32 network;
    U32 sec8ksource;

} SWIX_QUERY_SWITCH_ARGS;

U32 NMSAPI swiXGetStatus( SWIHD swihd,
                            SWIX_QUERY_SWITCH_ARGS *args,
                            unsigned size );

/*****************************************************************************
 * EXTENDED Local Stream Map - provides map of all local streams
 *****************************************************************************/

/* ----- limit definitions ----- */
#define SWIX_MAX_H100_STREAM     31     /* maximum H.100/H.110 stream number */
#define SWIX_MAX_H100_TIMESLOT   127    /* maximum H.100/H.110 timeslot */
#define SWIX_MAX_LOCAL_STREAM    15     /* maximum LOCAL stream number */
#define SWIX_MAX_LOCAL_TIMESLOT  127    /* maximum LOCAL timeslot */
#define SWIX_MAX_ARRAY_COUNT     256    /* maximum number of array elements */
#define SWIX_MAX_LOCAL_BUFFER    1536   /* maximum size of local stream buffer */
#define SWIX_MAX_LOCAL_DEVICE    4      /* maximum local devices on single local stream */
#define SWIX_MAX_TIMESLOT        127    /* max timeslot (H.100/H.110 or LOCAL) */
#define SWIX_MAX_CARRIER         16     /* maximum carrier number (network number) */
#define SWIX_MAX_PORT            32     /* maximum supported port number (1..n) */

/*---------------------------------------------------------------------------*
 * EXTENDED Per-Device Local Stream Usage
 *---------------------------------------------------------------------------*/
typedef struct
{
    U32   netnum;     /* network number (1-based number for netref location) */
    U32   ts_cnt;     /* count of local stream timeslots in use */
    U32   ts_start;   /* starting timeslot # for given device */
    U32   ts_delta;   /* delta to apply to get to next local timeslot for device */
} SWIX_LOCAL_USAGE;

/*---------------------------------------------------------------------------*
 * EXTENDED Local Stream Information
 *---------------------------------------------------------------------------*/
typedef struct
{
    U32                 ls_number;  /* local stream number */
    U32                 connection; /* where local stream is connected */
/* see mvip95.h: MVIP95_xxx_DEVICE OR (above): MVIP95_X_xxx_DEVICE */

    U32                 device_cnt; /* count of devices sharing local stream */
    SWIX_LOCAL_USAGE    device[SWIX_MAX_LOCAL_DEVICE];    /* per-device info */
} SWIX_LOCAL_INFO;

/*---------------------------------------------------------------------------*
 * EXTENDED Local Stream Map
 *---------------------------------------------------------------------------*/
typedef struct
{
    SWIX_LOCAL_INFO stream[SWIX_MAX_LOCAL_STREAM+1];  /* info about each local stream */
} SWIX_LOCAL_MAP;

/*---------------------------------------------------------------------------*
 * EXTENDED Local Timeslot Config
 *---------------------------------------------------------------------------*/
typedef struct
{
    U32             port_num;       /* communications port number */
    U32             speed;          /* speed of connection (64, 56, 48) Kb */
#define TX_X_SPEED_64KB         1
#define TX_X_SPEED_56KB         2
#define TX_X_SPEED_48KB         3
#define TX_X_SPEED_HSL          4   /* speed value for high speed link (spanning all timeslots of trunk) */
#define TX_X_SPEED_HYPERCHAN    5   /* speed indicator for hyperchannels (64 Kb * # of timeslots) */

    SWI_TERMINUS    outterm;        /* output terminus description */
#define TX_X_SLOT_HSL           0x7FFFFFFF  /* indicates use of all timeslots of trunk (for high speed link) */
#define TX_X_SLOT_RANGE         (1<<31)     /* BIT: indicates a timeslot range (<low value> in upper word; <high value> in lower word) */

} SWIX_LOCAL_TIMESLOT_CONFIG;

/*---------------------------------------------------------------------------*
 * EXTENDED Communications Port Config [single port]
 *---------------------------------------------------------------------------*/
typedef struct
{
    SWI_TERMINUS    interm;         /* input terminus description */
    SWI_TERMINUS    outterm;        /* output terminus description */
    U32             speed;          /* speed of connection (TX_X_SPEED_xxKB) */
} SWIX_COMM_PORT;

/*---------------------------------------------------------------------------*
 * EXTENDED Communications Port Config [all commun. ports]
 *---------------------------------------------------------------------------*/
typedef struct
{
    SWIX_COMM_PORT  port[SWIX_MAX_PORT+1];  /* per-port config ([0] dummy entry) */
} SWIX_COMM_PORT_ALL;

/*---------------------------------------------------------------------------*
 * EXTENDED local stream mapping
 *---------------------------------------------------------------------------*/
#define SWIX_LS_MAP_DONE    0x7FFFFF
#define SWIX_MAP_INVALID    0xFFFF

typedef struct
{
    U32     external_stream;    /* stream number presented outside kernel */
    U32     external_id;        /* stream type ID */
    U32     trunk_number;       /* trunk number when map to T1/E1/J1 trunk */
    U32     internal_stream;    /* physical local stream number */
    U32     flags;              /* control flags */
#define SWIX_LS_MAP_SHADOW  (1<<0)  /* set = this local stream is shadow of previous entry */
#define SWIX_LS_MAP_MVIPAPI (1<<1)  /* set = stream used by legacy MVIPAPI */

} SWIX_LS_MAP;

/*****************************************************************************
 * EXTENDED Commands used by swiConfigLocalStream
 *****************************************************************************/
#define TX_X_CONFIG_CARRIER     0xC0    /* legacy support: TxT1E1ConfigCarrier */
                                        /* TxT1E1ConfigEx       (t1e1type.h) */
#define TX_X_CTRL_CARRIER       0xC3    /* legacy support: TxT1E1CtrlCarrier */
                                        /* CtrlCarrierReq       (t1e1user.h) */
#define TX_X_SUPERVISE_CARRIER  0xC7    /* legacy support: TxT1E1SuperviseCarrier */
                                        /* SupvCarrierReq       (t1e1user.h) */
#define TX_X_CMD_CARRIER        0xC9    /* TxT1E1Cmd            (t1e1type.h) */

/*****************************************************************************
 * EXTENDED Commands used by swiGetLocalStreamInfo
 *****************************************************************************/
#define TX_X_CARRIER_STATUS     0xC1    /* legacy support: TxT1E1CarrierStatus */
                                        /* high byte of deviceid used for flags */
                                        /* CarrierStatusResp    (t1e1user.h) */
#define TX_X_PERF_REPORT        0xC2    /* legacy support: TxT1E1PerfReport */
                                        /* high byte of deviceid used for flags */
                                        /* PerfReportResp       (t1e1user.h) */
#define TX_X_CHANNEL_STATUS     0xC8    /* legacy support: TxT1E1ChannelStatus */
                                        /* ChannelStatusResp    (t1e1user.h) */
#define TX_X_PORT_COMM_CONFIG   0xCB    /* get config of all commun. ports */
                                        /* SWIX_COMM_PORT_ALL */
#define TX_X_CARRIER_TYPES      0xCC    /* get type of all carrier lines */
                                        /* TxT1E1Types          (t1e1type.h) */

/* ----- control flags used in parameterid of swiGetLocalStreamInfo request */
#define TX_X_GETLOCALSTREAMINFO_FLAGS           0xFF000000  /* mask for optional flags */
#define TX_X_GETLOCALSTREAMINFO_RESET_COUNTS    (1<<31)     /* set = reset counters */

/*****************************************************************************
 * EXTENDED Commands used by swiConfigLocalTimeslot
 *****************************************************************************/
#define TX_X_CONDITION_CHAN     0xC4    /* legacy support: TxT1E1ConditionChan */
                                        /* CondChanReq          (t1e1user.h) */
#define TX_X_CONFIG_CHAN        0xC5    /* legacy support: TxT1E1ConfigChan */
                                        /* ConfigChanReq        (t1e1user.h) */
#define TX_X_CONFIG_PORT        0xC6    /* port configuration */
                                        /* SWIX_LOCAL_TIMESLOT_CONFIG */
#define TX_X_CONFIG_SPEED       0xCA    /* port speed configuration */
                                        /* SWIX_LOCAL_TIMESLOT_CONFIG */

/*****************************************************************************
 * EXTENDED Commands used for local stream notifications
 *****************************************************************************/
#define TX_X_LOCAL_STATUS_NOTIF 0xD0    /* alarm or sync state change */
                                        /* TxT1E1UStat          (t1e1user.h) */
#define TX_X_LOCAL_PERF15_NOTIF 0xD1    /* 15-minute performance report */
                                        /* TxT1E1Perf15         (t1e1user.h) */
#define TX_X_LOCAL_PERF24_NOTIF 0xD2    /* 24-hour performance report */
                                        /* TxT1E1Perf24         (t1e1user.h) */

/*###########################################################################*
 *
 * SWI (with TX EXTENSIONS) PACKET PROTOCOL DEFINITIONS
 *
 *###########################################################################*/

/*****************************************************************************
 * TXSWI_HDR - common header used for all SWI requests / responses
 *****************************************************************************/
typedef struct __txswi_hdr
{
    U32     msgfunc;                    /* message function */
#define TXSWI_DISABLE_SWITCH            0x01
#define TXSWI_ENABLE_SWITCH             0x02
#define TXSWI_DISABLE_OUTPUT            0x03
#define TXSWI_GET_OUTPUT_STATE          0x04
#define TXSWI_MAKE_CONNECTION           0x05
#define TXSWI_MAKE_FRAMED_CONNECTION    0x06
#define TXSWI_GET_SWITCH_CAPS           0x07
#define TXSWI_RESET_SWITCH              0x08
#define TXSWI_SAMPLE_INPUT              0x09
#define TXSWI_SEND_PATTERN              0x0A
#define TXSWI_CONFIG_NETREF_CLOCK       0x0B
#define TXSWI_GET_BOARD_CLOCK           0x0C
#define TXSWI_GET_TIMING_REFERENCE      0x0D
#define TXSWI_CONFIG_BOARD_CLOCK        0x0E
#define TXSWI_CONFIG_SEC8K_CLOCK        0x0F
#define TXSWI_CONFIG_8KREF_CLOCK        0x10
#define TXSWI_CONFIG_STREAM_SPEED       0x11
#define TXSWI_GET_STREAMS_BY_SPEED      0x12
#define TXSWI_CONFIG_LOCAL_STREAM       0x13
#define TXSWI_GET_LOCAL_STREAM_INFO     0x14
#define TXSWI_CONFIG_LOCAL_TIMESLOT     0x15
#define TXSWI_GET_LOCAL_TIMESLOT_INFO   0x16
#define TXSWI_GET_BOARD_INFO            0x17
#define TXSWI_GET_DRIVER_INFO           0x18
#define TXSWI_GET_LAST_ERROR            0x19
#define TXSWI_SET_VERIFY                0x1A
/* ----- TX extensions to SWI interface ----- */
#define TXSWI_X_GET_STATUS              0x80
#define TXSWI_X_LOCAL_STREAM_NOTIF      0x81

    U32     msgtype;                    /* type of message */
#define TXSWI_REQUEST                   0x01
#define TXSWI_RESPONSE                  0x02
#define TXSWI_NOTIFICATION              0x03

    U32     msgkey;                     /* key (provided by user in REQUEST; duplicated in RESPONSE) */
    U32     msgcount;                   /* count of array entries (in dynamic portion of message) */
    U32     rspcode;                    /* response completion code [not used for REQUEST packets]
                                         * (see coserror.h - SCCSWI_xxx error codes) */
} TXSWI_HDR;

/*****************************************************************************
 * TXSWI_CONNECT - connection description
 *****************************************************************************/
typedef struct __txswi_connect
{
    SWI_TERMINUS        input;
    SWI_TERMINUS        output;
} TXSWI_CONNECT;

/*****************************************************************************
 * TXSWI_TERMDATA - terminus and data description
 *****************************************************************************/
typedef struct __txswi_termdata
{
    SWI_TERMINUS        terminus;
    U8                  data;
    U8                  avail[3];
} TXSWI_TERMDATA;

/*****************************************************************************
 * TXSWI_TERMMODE - terminus and mode description
 *****************************************************************************/
typedef struct __txswi_termmode
{
    SWI_TERMINUS        interm;
    U8                  mode;
    U8                  data;
    U8                  avail[2];
} TXSWI_TERMMODE;

/*****************************************************************************
 * TXSWI_CLOCK_SOURCE - information identifying source of clock signal
 *****************************************************************************/
typedef struct __txswi_clock_source
{
    U32                 source;
    U32                 network;
} TXSWI_CLOCK_SOURCE;

/*****************************************************************************
 * TXSWI_LASTERROR - last error information
 *****************************************************************************/
typedef struct __txswi_lasterror
{
    U32                 errorcode;  /* from coserror.h (SCCSWI_xxx) */
} TXSWI_LASTERROR;

/*****************************************************************************
 * TXSWI_VERIFY - verify setting
 *****************************************************************************/
typedef struct __txswi_verify
{
    U32                 verify;
#define TXSWI_VERIFY_DISABLE    0
#define TXSWI_VERIFY_ENABLE     0xFFFFFFFF

} TXSWI_VERIFY;

/*---------------------------------------------------------------------------*
 * The following table descibes the messages used
 * for each type of REQUEST and RESPONSE:
 *
 * All request and response messages begin with a TXSWI_HDR structure.
 * The TXSWI_HDR structure is represented as '^' below (to save space).
 * Any message that uses hdr.msgcount is shown with '[]' for the counted array.
 *
 * msgfunc                  REQUEST                   RESPONSE
 * ======================== ========================= =========================
 * DISABLE_SWITCH           ^                         ^
 * ENABLE_SWITCH            ^                         ^
 * DISABLE_OUTPUT           ^+SWI_TERMINUS[]          ^
 * GET_OUTPUT_STATE         ^+SWI_TERMINUS[]          ^+TXSWI_TERMMODE[]
 * MAKE_CONNECTION          ^+TXSWI_CONNECT[]         ^
 * MAKE_FRAMED_CONNECTION   ^+TXSWI_CONNECT[]         ^
 * GET_SWITCH_CAPS          ^                         ^+SWI_SWITCHCAPS_ARGS
 *                                                     +SWI_LOCALDEV_DESC[]
 * RESET_SWITCH             ^                         ^
 * SAMPLE_INPUT             ^+SWI_TERMINUS[]          ^+U8[]
 * SEND_PATTERN             ^+TXSWI_TERMDATA[]        ^
 * CONFIG_NETREF_CLOCK      ^+SWI_NETREF_CLOCK_ARGS   ^
 * GET_BOARD_CLOCK          ^                         ^+SWI_QUERY_CLOCK_ARGS
 * GET_TIMING_REFERENCE     ^                         ^+SWI_QUERY_TIMING_REFERENCE_ARGS
 * CONFIG_BOARD_CLOCK       ^+SWI_CLOCK_ARGS          ^
 * CONFIG_SEC8K_CLOCK       ^+TXSWI_CLOCK_SOURCE      ^
 * CONFIG_8KREF_CLOCK       ^+TXSWI_CLOCK_SOURCE      ^
 * CONFIG_STREAM_SPEED      ^+TXSWI_SPEED             ^
 *                           +TXSWI_STREAM[]
 * GET_STREAMS_BY_SPEED     ^+TXSWI_SPEED             ^+TXSWI_STREAM[]
 * CONFIG_LOCAL_STREAM      ^+SWI_LOCALSTREAM_ARGS    ^
 *                           +U8[]
 * GET_LOCAL_STREAM_INFO    ^+SWI_LOCALSTREAM_ARGS    ^+SWI_LOCALSTREAM_ARGS
 *                                                     +U8[]
 * CONFIG_LOCAL_TIMESLOT    ^+SWI_LOCALTIMESLOT_ARGS  ^
 *                           +U8[]
 * GET_LOCAL_TIMESLOT_INFO  ^                         ^+SWI_LOCALTIMESLOT_ARGS
 *                                                     +U8[]
 * GET_BOARD_INFO           ^                         ^+SWI_BOARDINFO_ARGS
 * GET_DRIVER_INFO          ^                         ^+SWI_DRIVERINFO_ARGS
 * GET_LAST_ERROR           ^                         ^+TXSWI_LASTERROR
 * SET_VERIFY               ^+TXSWI_VERIFY            ^
 * X_GET_STATUS             ^                         ^+SWIX_QUERY_SWITCH_ARGS
 *
 * msgfunc                  NOTIFICATION
 * ======================== ==================================================
 * X_LOCAL_STREAM_NOTIF     ^+SWI_LOCALSTREAM_ARGS
 *                           +U8[]
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*
 * MINIMAL MESSAGE DEFINITIONS
 *
 * NOTE: Several messages end with a structure that is actually an array
 *       of structures.  These are defined here as arrays of 1 element
 *       so that the minimal message can be defined.
 *---------------------------------------------------------------------------*/

typedef struct __txswi_msg_terminus
{
    TXSWI_HDR                   hdr;
    SWI_TERMINUS                terminus[1];
} TXSWI_MSG_TERMINUS;

typedef struct __txswi_msg_termmode
{
    TXSWI_HDR                   hdr;
    TXSWI_TERMMODE              termmode[1];
} TXSWI_MSG_TERMMODE;

typedef struct __txswi_msg_connect
{
    TXSWI_HDR                   hdr;
    TXSWI_CONNECT               connect[1];
} TXSWI_MSG_CONNECT;

typedef struct __txswi_msg_localcaps
{
    TXSWI_HDR                   hdr;
    SWI_SWITCHCAPS_ARGS         args;
    SWI_LOCALDEV_DESC           localdev[1];
} TXSWI_MSG_LOCALCAPS;

typedef struct __txswi_msg_data
{
    TXSWI_HDR                   hdr;
    U8                          data[1];
} TXSWI_MSG_DATA;

typedef struct __txswi_msg_termdata
{
    TXSWI_HDR                   hdr;
    TXSWI_TERMDATA              termdata[1];
} TXSWI_MSG_TERMDATA;

typedef struct __txswi_msg_localdata
{
    TXSWI_HDR                   hdr;
    SWI_LOCALSTREAM_ARGS        args;
    U8                          data[1];
} TXSWI_MSG_LOCALDATA;

typedef struct __txswi_msg_netref
{
    TXSWI_HDR                   hdr;
    SWI_NETREF_CLOCK_ARGS       args;
} TXSWI_MSG_NETREF;

typedef struct __txswi_msg_queryclk
{
    TXSWI_HDR                   hdr;
    SWI_QUERY_CLOCK_ARGS        args;
} TXSWI_MSG_QUERYCLK;

typedef struct __txswi_msg_timingref
{
    TXSWI_HDR                   hdr;
    U32                         referencesource;
    U32                         network;
} TXSWI_MSG_TIMINGREF;

typedef struct __txswi_msg_timing
{
    TXSWI_HDR                           hdr;
    SWI_QUERY_TIMING_REFERENCE_ARGS     args;
} TXSWI_MSG_TIMING;

typedef struct __txswi_msg_clock
{
    TXSWI_HDR                   hdr;
    SWI_CLOCK_ARGS              args;
} TXSWI_MSG_CLOCK;

typedef struct __txswi_msg_8kclock
{
    TXSWI_HDR                   hdr;
    TXSWI_CLOCK_SOURCE          clock;
} TXSWI_MSG_8KCLOCK;

typedef struct __txswi_msg_streamspeed
{
    TXSWI_HDR                   hdr;
    U32                         speed;
    U32                         count;
    U32                         stream[32];
} TXSWI_MSG_STREAMSPEED;

typedef struct __txswi_msg_speed
{
    TXSWI_HDR                   hdr;
    U32                         speed;
} TXSWI_MSG_SPEED;

typedef struct __txswi_msg_stream
{
    TXSWI_HDR                   hdr;
    U32                         stream[1];
} TXSWI_MSG_STREAM;

typedef struct __txswi_msg_streamdata
{
    TXSWI_HDR                   hdr;
    SWI_LOCALSTREAM_ARGS        args;
    U8                          buffer[1];
} TXSWI_MSG_STREAMDATA;

typedef struct __txswi_msg_slotdata
{
    TXSWI_HDR                   hdr;
    SWI_LOCALTIMESLOT_ARGS      args;
    U8                          buffer[1];
} TXSWI_MSG_SLOTDATA;

typedef struct __txswi_msg_boardinfo
{
    TXSWI_HDR                   hdr;
    SWI_BOARDINFO_ARGS          args;
} TXSWI_MSG_BOARDINFO;

typedef struct __txswi_msg_driverinfo
{
    TXSWI_HDR                   hdr;
    SWI_DRIVERINFO_ARGS         args;
} TXSWI_MSG_DRIVERINFO;

typedef struct __txswi_msg_lasterror
{
    TXSWI_HDR                   hdr;
    TXSWI_LASTERROR             last;
} TXSWI_MSG_LASTERROR;

typedef struct __txswi_msg_verify
{
    TXSWI_HDR                   hdr;
    TXSWI_VERIFY                args;
} TXSWI_MSG_VERIFY;

typedef struct __txswi_msg_getstatus
{
    TXSWI_HDR                   hdr;
    SWIX_QUERY_SWITCH_ARGS      args;
} TXSWI_MSG_GETSTATUS;

/*****************************************************************************
 * FULL MESSAGE UNION - single structure overlay for all requests / responses
 *
 * NOTE: These are not really FULL message size definitions since many
 *       messages end with a variable length array.
 *       This message union fully describes the minimal structures for each
 *       message type.  Use the TXSWI_HDR field: msgcount to determine the
 *       actual number of array elements.
 *****************************************************************************/
typedef union __txswi_msg
{
    TXSWI_HDR                   common;

    union
    {
        TXSWI_HDR               disable_switch;
        TXSWI_HDR               enable_switch;
        TXSWI_MSG_TERMINUS      disable_output;
        TXSWI_MSG_TERMINUS      get_output_state;
        TXSWI_MSG_CONNECT       make_connection;
        TXSWI_MSG_CONNECT       make_framed_connection;
        TXSWI_HDR               get_switch_caps;
        TXSWI_HDR               reset_switch;
        TXSWI_MSG_TERMINUS      sample_input;
        TXSWI_MSG_TERMDATA      send_pattern;
        TXSWI_MSG_NETREF        config_netref_clock;
        TXSWI_HDR               get_board_clock;
        TXSWI_MSG_TIMINGREF     get_timing_reference;
        TXSWI_MSG_CLOCK         config_board_clock;
        TXSWI_MSG_8KCLOCK       config_sec8k_clock;
        TXSWI_MSG_8KCLOCK       config_8kref_clock;
        TXSWI_MSG_STREAMSPEED   config_stream_speed;
        TXSWI_MSG_SPEED         get_streams_by_speed;
        TXSWI_MSG_STREAMDATA    config_local_stream;
        TXSWI_MSG_STREAMDATA    get_local_stream_info;
        TXSWI_MSG_SLOTDATA      config_local_timeslot;
        TXSWI_HDR               get_local_timeslot_info;
        TXSWI_HDR               get_board_info;
        TXSWI_HDR               get_driver_info;
        TXSWI_HDR               get_last_error;
        TXSWI_MSG_VERIFY        set_verify;
        TXSWI_HDR               get_status;
    } request;

    union
    {
        TXSWI_HDR               disable_switch;
        TXSWI_HDR               enable_switch;
        TXSWI_HDR               disable_output;
        TXSWI_MSG_TERMMODE      get_output_state;
        TXSWI_HDR               make_connection;
        TXSWI_HDR               make_framed_connection;
        TXSWI_MSG_LOCALCAPS     get_switch_caps;
        TXSWI_HDR               reset_switch;
        TXSWI_MSG_DATA          sample_input;
        TXSWI_HDR               send_pattern;
        TXSWI_HDR               config_netref_clock;
        TXSWI_MSG_QUERYCLK      get_board_clock;
        TXSWI_MSG_TIMING        get_timing_reference;
        TXSWI_HDR               config_board_clock;
        TXSWI_HDR               config_sec8k_clock;
        TXSWI_HDR               config_8kref_clock;
        TXSWI_HDR               config_stream_speed;
        TXSWI_MSG_STREAMSPEED   get_streams_by_speed;
        TXSWI_HDR               config_local_stream;
        TXSWI_MSG_LOCALDATA     get_local_stream_info;
        TXSWI_HDR               config_local_timeslot;
        TXSWI_MSG_SLOTDATA      get_local_timeslot_info;
        TXSWI_MSG_BOARDINFO     get_board_info;
        TXSWI_MSG_DRIVERINFO    get_driver_info;
        TXSWI_MSG_LASTERROR     get_last_error;
        TXSWI_HDR               set_verify;
        TXSWI_MSG_GETSTATUS     get_status;
    } response;

    union
    {
        TXSWI_MSG_STREAMDATA    notif_local_stream;
    } notif;

} TXSWI_MSG;

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

#endif  /* _TXSWI_H */
