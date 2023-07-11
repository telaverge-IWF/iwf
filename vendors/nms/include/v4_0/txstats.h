/*****************************************************************************
 *
 * txstats.h - TX Communications Statistics Definitions
 *
 *****************************************************************************/

/*****************************************************************************
 *
 *                         PROPRIETARY NOTICE
 *
 *                      Copyright (c) 2003
 *                       by NMS Communications.
 *
 *  The following is licensed program material and is considered
 *  proprietary and confidential.  No part of this program may be
 *  reproduced or used in any form or by any means without the express
 *  written permission of NMS Communications.
 *
 *****************************************************************************/

#ifndef _TXSTATS_H
#define _TXSTATS_H

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

/*###########################################################################*
 *
 * TX Statistics: breakdown of options
 *
 * Options for TX-related statistics requests are provided as a single U32
 * with the following breakdown:
 *     <0xccbb-SLO>
 *         O=operation, L=layer, S=scope, bb=board number, cc=channel number
 *
 *###########################################################################*/

/* ----- TX Statistics options: operations */
#define TX_STATS_OPER       0x0000000F  /* operation mask */
#define TX_STATS_GET            0       /* just get current statistics */
#define TX_STATS_ZERO           (1<<0)  /* get and then zero statistics */
#define TX_STATS_NAME           (2<<0)  /* get names of common statistics */
#define TX_STATS_NAME_LAYER     (3<<0)  /* get names of layer-specific statistics */
#define TX_STATS_DESC           (4<<0)  /* get description of common statistics */
#define TX_STATS_DESC_LAYER     (5<<0)  /* get description of layer-specific statistics */

/* ----- TX Statistics options: layers */
#define TX_STATS_LAYER      0x000000F0  /* layer mask */
#define TX_STATS_API            0       /* statistics provided by API layer (CPI) */
#define TX_STATS_HOST           (1<<4)  /* statistics provided by host driver layer */
#define TX_STATS_TX             (2<<4)  /* statistics provided by TX board */

/* ----- TX Statistics options: scope */
#define TX_STATS_SCOPE      0x00000F00  /* scope mask */
#define TX_STATS_HANDLE         0       /* all activity for the given handle */
#define TX_STATS_CHANNEL        (1<<8)  /* all activity across specified channel */
#define TX_STATS_BOARD          (2<<8)  /* all activity to specified TX board */
#define TX_STATS_GLOBAL         (3<<8)  /* totals of all activity across all TX boards */

/* ----- TX Statistics options: board number */
#define TX_STATS_BOARD_MASK     0x00FF0000  /* board number mask */
#define TX_STATS_BOARD_SHIFT    16          /* bits to shift to get board number out of options */

/* ----- TX Statistics options: channel number */
#define TX_STATS_CHANNEL_MASK   0xFF000000  /* CPI channel mask */
#define TX_STATS_CHANNEL_SHIFT  24          /* bits to shift to get cpi channel out of options */

/* ----- TX Statistics: general definitions */
#define TX_STATS_SRC_CHAN   0xFF        /* special source channel identifying stats responses */
#define TX_STATS_INFO_SZ    40          /* space for information about each statistic */
#define TX_STATS_MAX        64          /* maximum number of statistics (in any single request) */

/*###########################################################################*
 *
 * TX Statistics: Error Code Definitions
 *
 * These error codes are placed in txlast, rxlast, and anomaly
 *
 *###########################################################################*/
#define TX_STATS_ERROR_BASE         0x80000000
#define TX_STATS_UNKNOWN_PRIM       0x80000001  /* unknown primitive provided */
#define TX_STATS_SENDPRIM_FAIL      0x80000002  /* error while sending primitive */
#define TX_STATS_SENDPRIM_RSP       0x80000003  /* error while reading primitive response */
#define TX_STATS_SENDPRIM_TYPE      0x80000004  /* unknown primitive type in response to send */
#define TX_STATS_SENDCTRL_UNKNOWN   0x80000005  /* unknown send control request */
#define TX_STATS_SENDCTRL_FAIL      0x80000006  /* error while sending control */
#define TX_STATS_SENDCTRL_RSP       0x80000007  /* error while reading control response */
#define TX_STATS_SENDCTRL_TYPE      0x80000008  /* unknown primitive type in response to ctrl */
#define TX_STATS_SENDDATA_UNKNOWN   0x80000009  /* unknown send data request */
#define TX_STATS_SENDDATA_FAIL      0x8000000A  /* error while sending data */
#define TX_STATS_SENDDATA_RSP       0x8000000B  /* error while reading data response */
#define TX_STATS_SENDDATA_BADSEQ    0x8000000C  /* sequence # mismatch on send data response */
#define TX_STATS_SENDDATA_TYPE      0x8000000D  /* unknown primitive type in response to data */
#define TX_STATS_RECVDATA_FAIL      0x8000000E  /* error while trying to receive data */
#define TX_STATS_RECVDATA_UNKNOWN   0x8000000F  /* unknown primitive while trying to receive data */
#define TX_STATS_GETDATA_FAIL       0x80000010  /* error while trying to get data */
#define TX_STATS_DATAACK_FAIL       0x80000011  /* error while sending DATAACK */
#define TX_STATS_INTR_UNKNOWN       0x80000012  /* unknown primitive received in cpia_intr */
#define TX_STATS_INTR_FAIL          0x80000013  /* error while trying to receive in cpia_intr */
#define TX_STATS_TXNOTIF_NOTACK     0x80000014  /* non-ACK received when expecting TX notif */
#define TX_STATS_LOWER_WINDOW_FULL  0x80000015  /* window to lower layer is full */
#define TX_STATS_NULL_PARAM         0x80000016  /* NULL provided as parameter when NULL not allowed */
#define TX_STATS_OUT_OF_MEMORY      0x80000017  /* out-of-memory condition encountered */
#define TX_STATS_NO_FREE_MESSAGES   0x80000018  /* no free messages available */
#define TX_STATS_CORRUPT_MESSAGE    0x80000019  /* corrupted message detected */
#define TX_STATS_TIMEOUT            0x8000001A  /* timeout while waiting for event */
#define TX_STATS_NOTRACK_AVAIL      0x8000001B  /* no tracking entry available */
#define TX_STATS_RXNOTIF_NOACK      0x8000001C  /* receive notifcation when no pending RX ACK */
#define TX_STATS_RXRING_OVERFLOW    0x8000001D  /* receive ring overflow */
#define TX_STATS_ATTACH_CORRUPT     0x8000001E  /* corruption detected in channel <=> device attachment */
#define TX_STATS_BUFFER_TOO_SMALL   0x8000001F  /* associated data buffer too small for operation */
#define TX_STATS_DATA_WHEN_CLOSING  0x80000020  /* data being passed to host app when close in progress */
#define TX_STATS_UNKNOWN_EVENT      0x80000021  /* unknown event received */
#define TX_STATS_INVALID_MODE       0x80000022  /* invalid mode for requested operation */
#define TX_STATS_SHARED_CORRUPTED   0x80000023  /* shared memory window has become corrupted */
#define TX_STATS_PUTQ_FAILED        0x80000024  /* unable to put message to queue (failed putq) */

/*###########################################################################*
 *
 * TX Statistics: Structure Definitions
 *
 *###########################################################################*/

#define TX_STAT_COL_2   28  /* raw stat index: stat to begin column 2 output */

/*****************************************************************************
 * Common statistics (provided by all layers)
 *****************************************************************************/
typedef struct
{
    /*      Name           Description
     *      ============   ======================================== */

    /* ----- upper layer interface ----- */
    U32     tx;         /* total number of transmit requests */
    U32     txsucc;     /* messages successfully transmitted */
    U32     txinprog;   /* transmits in progress to lower layer */
    U32     txqueued;   /* transmits queued (flow controlled) */
    U32     txfull;     /* transmits failed due to window full */
    U32     txstate;    /* transmits failed due to invalid state */
    U32     txcancel;   /* transmits cancelled (close/reset) */
    U32     txnochan;   /* transmits failed - no listener channel */
    U32     txfail;     /* transmits failed due to any other error */
    U32     txlast;     /* last transmit error (set when txfail++) */
    U32     txavail[2];

    U32     rx;         /* total number of messages received */
    U32     rxsucc;     /* successfully received (to upper layer) */
    U32     rxinprog;   /* receives in progress (to upper layer) */
    U32     rxqueued;   /* receive ACKs queued (flow controlled) */
    U32     rxtimeout;  /* receives failed due to timeout */
    U32     rxstate;    /* receives failed due to invalid state */
    U32     rxcancel;   /* receives cancelled (close/reset) */
    U32     rxnochan;   /* receives dropped (no receive channel) */
    U32     rxfail;     /* receives failed due to any other error */
    U32     rxlast;     /* last receive error (set when rxfail++) */
    U32     rxavail[2];

    U32     upperrecv;  /* total of all indications received from upper layer */
    U32     uppersucc;  /* total of all successful indications sent to upper layer */
    U32     upperfail;  /* total of all failure indications sent to upper layer */
    U32     upperavail;

    /* ----- current state ----- */
    U32     state;      /* current state of target entity */
#define TX_STATE_UNINITED   0   /* state has not been initialized */
#define TX_STATE_RESETTING  1   /* reset in progress */
#define TX_STATE_RUNNING    2   /* up and running normally */
#define TX_STATE_HALTED     3   /* operations halted due to unrecoverable error */
#define TX_STATE_OPEN       4   /* channel currently open for use */
#define TX_STATE_OPEN_SYNC  5   /* channel currently open for use in synchronous mode */
#define TX_STATE_OPEN_ASYNC 6   /* channel currently open for use in asynchronous mode */
#define TX_STATE_ATTACHED   7   /* channel attached to a device */
#define TX_STATE_BOUND      8   /* bound to receive channel */
#define TX_STATE_CLOSING    9   /* channel close in progress */
#define TX_STATE_MAX        9

    U32     connection; /* type of connection between upper and lower layers */
#define TX_CONNECT_IO       0   /* connection using standard I/O interface */
#define TX_CONNECT_MEM      1   /* connection using shared memory interface */
#define TX_CONNECT_MAX      1

    U32     connectavail;

    /* ----- internal proessing ----- */
    U32     interrupt;  /* number of times interrupt occurred */
    U32     deferred;   /* times that deferred processing occurred */
    U32     intmax;     /* maximum messages (single internal exec) */
    U32     intstray;   /* internal processing performed no work */
    U32     outstate;   /* errors due to invalid state */
    U32     outmem;     /* errors due to out-of-memory condition */
    U32     anomalies;  /* any other errors during internal exec */
    U32     anomaly;    /* last anomaly (set when anomalies++) */
    U32     intavail[2];

    /* ----- lower layer interface ----- */
    U32     senddata;   /* data requests posted to lower layer */
    U32     sendctl;    /* control requests posted to lower layer */
    U32     sendrxack;  /* receive acknowledgements posted to lower layer */
    U32     sendboot;   /* board booted messages to lower layer */
    U32     sendtime;   /* date/time messages sent to lower layer */
    U32     sendavail[2];

    U32     recvdata;   /* data indications received from lower layer */
    U32     recvctl;    /* control indications from lower layer */
    U32     recvtxack;  /* transmit acknowledgements received from lower layer */
    U32     recvboot;   /* board booted messages from lower layer */
    U32     recvtime;   /* date/time messages from lower layer */
    U32     recverror;  /* error indications from lower layer */
    U32     recvignore; /* messages received from lower layer but ignored */
    U32     recvinvalid;/* receives from lower layer determined to be invalid */
    U32     recvavail[2];

    /* ----- diagnostic stats (used to diagnose specific problem) */
    U32     diag[4];    /* diagnostic [temporary] statistics */

    U32     expand[2];  /* available for future expansion */

} TX_STATS_COMMON;

/*****************************************************************************
 * Layer-specific array of statistics
 *****************************************************************************/
typedef struct
{
    U32     stat[TX_STATS_MAX];    /* set of layer-specific statistics */

} TX_STATS_ARRAY;

/*---------------------------------------------------------------------------*
 * Header (provided as response to all TX_STATS operations)
 *---------------------------------------------------------------------------*/
typedef struct
{
    U32 options;                    /* options provided in cpi[a]_stats request */
    U8  avail[28];
} TX_STATSHDR;

/*---------------------------------------------------------------------------*
 * Response to TX_STATS_GET/TX_STATS_ZERO operation
 *---------------------------------------------------------------------------*/
typedef struct
{
    TX_STATS_COMMON     common;     /* statistics common to all layers */
    TX_STATS_ARRAY      layer;      /* statistics specific to the given layer */
} TX_STATSSET;

/*---------------------------------------------------------------------------*
 * Alternative overlay for response to TX_STATS_GET/TX_STATS_ZERO operation
 *---------------------------------------------------------------------------*/
typedef struct
{
    TX_STATS_ARRAY      common;     /* statistics common to all layers */
    TX_STATS_ARRAY      layer;      /* statistics specific to the given layer */
} TX_STATSRAW;

/*---------------------------------------------------------------------------*
 * Per-statistic information (part of response to TX_STATS_NAME/TX_STATS_DESC)
 *---------------------------------------------------------------------------*/
typedef struct
{
    S8  name[TX_STATS_INFO_SZ];     /* name or description information */
} TX_STATSNAME;

/*---------------------------------------------------------------------------*
 * Response to TX_STATS_NAME/TX_STATS_DESC operation
 *---------------------------------------------------------------------------*/
typedef struct
{
    S8              layer[TX_STATS_INFO_SZ];   /* name of layer providing statistics */
    TX_STATSNAME    stat[TX_STATS_MAX];        /* name (or description) of each statistic */
} TX_STATSINFO;

/*****************************************************************************
 * TX statistics message (responses to all TX STATS requests)
 *****************************************************************************/
typedef struct
{
    TX_STATSHDR     hdr;

    union
    {
        TX_STATSSET     stats;      /* TX_STATS_GET/TX_STATS_ZERO response */

        TX_STATSRAW     raw;        /* TX_STATS_GET/TX_STATS_ZERO response [as raw array] */

        TX_STATSINFO    info;       /* TX_STATS_NAME/TX_STATS_DESC response */
    } rsp;

} TX_STATS;

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

#endif  /* _TXSTATS_H */
