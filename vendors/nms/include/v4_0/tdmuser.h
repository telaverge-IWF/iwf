/*****************************************************************************
 *
 * tdmuser.h - TDM/MVIP LEVEL 1 DRIVER ACCESS DEFINITIONS
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

#ifndef _TDMUSER_H
#define _TDMUSER_H

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

#include <txnuser.h>            /* primitive field type definitions */

/*******************************************************************************
* T1E1 Carrier Status Response
*******************************************************************************/
typedef struct _t1e1status
{
    U8            yellowalarm;
    U8            bluealarm;
    U8            syncstate;
    U8            framemode;
    U8            encoding;
    U8            linebldout;
    U8            debounce;
    U8            loopmaster;
    U8            robbedbit;
    U8            loopback;
    U16           currsecs;
    U16           escount;
    U16           lescount;
    U16           bescount;
    U16           sescount;
    U16           uascount;
    U16           ccscount;
    U16           lofcount;
    U8            pad_1[2];   /* padding for natural alignment */
    U32           pcvcnt;
    U32           lcvcnt;
    U32           slipcnt;
    U32           ebitcnt;
    U8            ts16aisalarm;
    U8            ts16failalarm;
    U8            distmfalarm;
    U8            align;
}
T1E1STATUS;


/*******************************************************************************
* T1 Status Registration and notification bits
*******************************************************************************/
#define  T1_LOOP_UP_DETECT    0x80000000    /* Loop Up Code Detected */
#define  T1_LOOP_DOWN_DETECT  0x40000000    /* Loop Down Code Detected */
#define  T1_LOSS_OF_TXCLK     0x20000000    /* Loss of Transmit Clock */
#define  T1_RX_SLIP           0x10000000    /* Receive Elastic Store Slip */
#define  T1_RXBLUE_ALARM      0x08000000    /* Receive Blue Alarm */
#define  T1_RXYELLOW_ALARM    0x04000000    /* Receive Yellow Alarm */
#define  T1_RX_CARRIERLOSS    0x02000000    /* Receive Carrier Loss */
#define  T1_RX_SYNCLOSS       0x01000000    /* Receive Loss of Sync */

#define  T1_FRAME_ALIGN       0x00008000    /* Change of Frame Alignment */
#define  T1_8ZERO_DETECT      0x00004000    /* Eight Zero Detect */
#define  T1_16ZERO_DETECT     0x00002000    /* Sixteen Zero Detect */
#define  T1_RXESTORE_FULL     0x00001000    /* Receive Elastic Store Full */
#define  T1_RXESTORE_EMPTY    0x00000800    /* Receive Elastic Store Empty */
#define  T1_SEVERLY_ERROR_F   0x00000400    /* Severely Errored Framing Event */
#define  T1_B8ZS_CODE_WORD    0x00000200    /* B8ZS Code Word Detcect */
#define  T1_FRAME_BIT_ERR     0x00000100    /* Frame Bit Error */

#define  T1_TXESTORE_FULL     0x00000020    /* Transmit Elastic Store Full */
#define  T1_TXESTORE_EMPTY    0x00000010    /* Transmit Elastci Store Empty */
#define  T1_TXSLIP            0x00000008    /* Transmit Elastic Store Slip */
#define  T1_JITTER_TRIP       0x00000004    /* Jitter Attenuator Limit Trip */
#define  T1_RXPDV             0x00000002    /* Receive Pulse Density Violation */
#define  T1_TXPDV             0x00000001    /* Transmit Pulse Density Violation */

/*******************************************************************************
* E1 Status Registration and notification bits
*******************************************************************************/
#define  E1_RX_SIGNAL_ONES    0x80000000    /* Rx Signaling all Ones Detected */
#define  E1_RX_DISTANT_MFALM  0x40000000    /* Rx Distant MF Alarm Detected */
#define  E1_RX_SIGNAL_ZEROS   0x20000000    /* Rx Signaling all Zeros Detected */
#define  E1_SLIP              0x10000000    /* Elastic Store Slip */
#define  E1_RX_UNFRAMED_ONES  0x08000000    /* Rx Unframed all Ones Detected */
#define  E1_RX_REMOTE_ALM     0x04000000    /* Rx Remote Alarm */
#define  E1_RX_CARRIERLOSS    0x02000000    /* Receive Carrier Loss */
#define  E1_RX_SYNCLOSS       0x01000000    /* Receive Loss of Sync */

#define  E1_JITTER_TRIP       0x00002000    /* Jitter Limit Trip */
#define  E1_ESTORE_FULL       0x00001000    /* Elastic Store Full */
#define  E1_ESTORE_EMPTY      0x00000800    /* Elastic Store Empty */
#define  E1_FAS_RESYNC        0x00000200    /* FAS Resync Criteria Met */
#define  E1_CAS_RESYNC        0x00000100    /* CAS Resync Criteria Met */

/*******************************************************************************
* T1/E1 Channel masks for channel status and Robbed bit registration
* and notification routines
*******************************************************************************/
#define T1_CHAN_1    0x00000001     /* Channel 1 */
#define T1_CHAN_2    0x00000002     /* Channel 2 */
#define T1_CHAN_3    0x00000004     /* Channel 3 */
#define T1_CHAN_4    0x00000008     /* Channel 4 */
#define T1_CHAN_5    0x00000010     /* Channel 5 */
#define T1_CHAN_6    0x00000020     /* Channel 6 */
#define T1_CHAN_7    0x00000040     /* Channel 7 */
#define T1_CHAN_8    0x00000080     /* Channel 8 */
#define T1_CHAN_9    0x00000100     /* Channel 9 */
#define T1_CHAN_10   0x00000200     /* Channel 10 */
#define T1_CHAN_11   0x00000400     /* Channel 11 */
#define T1_CHAN_12   0x00000800     /* Channel 12 */
#define T1_CHAN_13   0x00001000     /* Channel 13 */
#define T1_CHAN_14   0x00002000     /* Channel 14 */
#define T1_CHAN_15   0x00004000     /* Channel 15 */
#define T1_CHAN_16   0x00008000     /* Channel 16 */
#define T1_CHAN_17   0x00010000     /* Channel 17 */
#define T1_CHAN_18   0x00020000     /* Channel 18 */
#define T1_CHAN_19   0x00040000     /* Channel 19 */
#define T1_CHAN_20   0x00080000     /* Channel 20 */
#define T1_CHAN_21   0x00100000     /* Channel 21 */
#define T1_CHAN_22   0x00200000     /* Channel 22 */
#define T1_CHAN_23   0x00400000     /* Channel 23 */
#define T1_CHAN_24   0x00800000     /* Channel 24 */

#define T1_RBIT_A    0x01           /* Robbed bit A */
#define T1_RBIT_B    0x02           /* Robbed bit B */
#define T1_RBIT_C    0x04           /* Robbed bit C */
#define T1_RBIT_D    0x08           /* Robbed bit D */



/******************************************************************************
* MVIP Command Codes
******************************************************************************/
#define CONFIG_CLOCK            0x20
#define CHANNEL_STATUS          0x11
#define QUERY_SWITCH_CAPS       0x01
#define CONTROL_SWITCH          0x00
#define CHANNEL_CONNECT         0x10
#define SWITCH_STATUS           0x80

/******************************************************************************
* MVIP Control_Switch Command Operations
******************************************************************************/
#define RESET_SWITCH            0
#define DISABLE_SWITCH          1
#define ENABLE_SWITCH           2

/******************************************************************************
* MVIP Channel_connect and Channel_status Defines
******************************************************************************/
#define DISABLE_MODE            0
#define PATTERN_MODE            1
#define CONNECT_MODE            2

#define HALF_DUPLEX             0
#define FULL_DUPLEX             1

#define FORWARD_DIR             0
#define REVERSE_DIR             1

/******************************************************************************
* MVIP Error Codes
******************************************************************************/
#define SUCCESS                     0
#define MVIP_INVALID_COMMAND        200
#define MVIP_DLL_INVALID_DEVICE     201
#define MVIP_DEVICE_ERROR           202
#define MVIP_NO_RESOURCES           204
#define MVIP_INVALID_STREAM         210
#define MVIP_INVALID_TIMESLOT       211
#define MVIP_MISSING_PARAMETERS     212
#define MVIP_INVALID_CLOCK_PARM     213
#define MVIP_INVALID_MODE           216
#define MVIP_INVALID_MINOR_SWITCH   217
#define MVIP_INVALID_PARAMETER      218
#define MVIP_NO_PATH                220
#define MVIP_SWITCH_VERIFY_ERROR    221
#define MVIP_INTERNAL_CONFLICT      222
#define MVIP_CONNECTION_NOT_SUPPORTED   223


/******************************************************************************
* T1/E1 Command Codes
******************************************************************************/
#define T1_CONFIG_CARRIER       0x30
#define T1_CARRIER_STATUS       0x33
#define T1_CONDITION_CHAN       0x34
#define T1_SUPERVISE_CARRIER    0x37
#define T1_CONTROL_CARRIER      0x42
#define T1_CONFIG_CHANNEL       0x43
#define T1_CHANNEL_STATUS       0x44
#define T1_CONTROL_CHAN         0x45

/******************************************************************************
* T1/E1 Indication Codes
******************************************************************************/
#define STATUS_CARRIER          0x80
#define CARRIER_ALARM           0x81
#define ABCD_CHANGE             0x82

/******************************************************************************
* T1/E1 Framing Values
******************************************************************************/
#define FRAMING_NONE            0
#define FRAMING_D4              1
#define FRAMING_ESF             2
#define FRAMING_CCS             3
#define FRAMING_CAS             4
#define FRAMING_CCSCRC4         5
#define FRAMING_CASCRC4         6

/******************************************************************************
* T1/E1 Encoding Values
******************************************************************************/
#define ENCODING_NONE           0
#define ENCODING_NOZCS          1
#define ENCODING_BIT7_ZCS       2
#define ENCODING_B8ZS           3
#define ENCODING_HDB3           4

/******************************************************************************
* T1/E1 Carrier Sync Values
******************************************************************************/
#define CARRIER_NONE            0
#define CARRIER_SYNC            1
#define CARRIER_NOSYNC          2
#define CARRIER_LOST            3

/******************************************************************************
* T1/E1 Loopback Values
******************************************************************************/
#define LOOPBACK_NONE           0
#define LOOPBACK_LOCAL          1
#define LOOPBACK_REMOTE         2

/******************************************************************************
* T1E1 Error Codes
******************************************************************************/
#define T1E1_INVALID_COMMAND        200
#define T1E1_DEVICE_ERROR           202
#define T1E1_NO_RESOURCES           204
#define T1E1_INVALID_TIMESLOT       211
#define T1E1_MISSING_PARAMETERS     212
#define T1E1_INVALID_MODE           216
#define T1E1_INVALID_PARAMETER      218
#define T1E1_INTERNAL_CONFLICT      222
#define T1E1_CONNECTION_NOT_SUPPORTED       223





/* ===== FUNCTION PROTOTYPES ===== */

S16           mvip_query_switch(U16 *domain,
                                  U16 *routing,
                                  U16 *blocking,
                                  U16 *networks,
                                  U16 *channels);

S16           mvip_config_clock(U16 clockmode,
                                  U16 sec8kmode,
                                  U16 network);

S16           mvip_control_switch(U16 operation);

S16           mvip_switch_status(U16 *clockmode,
                                   U16 *sec8kmode,
                                   U16 *network,
                                   U16 *swstatus);

S16           mvip_channel_connect(U16 outstream,
                                     U16 outslot,
                                     U16 chanmode,
                                     U16 srcstream,
                                     U16 srcslot,
                                     U16 pattern,
                                     U16 duplex);

S16           mvip_channel_status(U16 outstream,
                                    U16 outslot,
                                    U16 *chanmode,
                                    U16 *srcstream,
                                    U16 *srcslot,
                                    U16 *pattern,
                                    U16 *direction,
                                    U16 *indirection,
                                    U8 *inputsample);


S16           t1e1_config_carrier(U8 network,
                                    U8 framemode,
                                    U8 encoding,
                                    U8 linebldout,
                                    U8 robbedbit,
                                    U8 loopmaster);

S16           t1e1_carrier_status(U8 network,
                                    T1E1STATUS * t1e1status,
                                    U8 clrcount);

S16           t1e1_control_carrier(U8 network,
                                     U8 loopback,
                                     U8 yelalarm,
                                     U8 bluealarm,
                                     U8 ts16aisalm,
                                     U8 distmfalm);

S16           t1e1_condition_chan(U8 network,
                                    U8 channel,
                                    U8 pattern,
                                    U8 control);

S16           t1e1_config_chan(U8 network,
                                 U8 channel,
                                 U8 transparent);

S16           t1e1_channel_status(U8 network,
                                    U32 *transparent,
                                    U32 *rxsignal,
                                    U32 *txsignal);

S16           t1e1_reg_robbit(U8 network,
                                U32 chanmask,
                                U8 abcdmask,
                                void *userkey, void *rbit_notif);

/* Robbed bit Change Notification Prototype (user-defined function):
void <rbit_notif>( void *userkey,
                   U32 changemask,
                   U32 currabits,
                   U32 currbbits,
                   U32 currcbits,
                   U32 currdbits ); */

S16           t1e1_dereg_robbit(U8 network, void *userkey);

S16           t1e1_reg_status(U8 network,
                                U32 notifmask,
                                void *userkey, void *status_notif);

/* Status Change Notification Prototype (user-defined function):
void <status_notif>( void *userkey,
                     U32 changemask,
                     U32 currvalue ); */


S16           t1e1_dereg_status(U8 network, void *userkey);

S16           t1e1_reg_stats(U8 network,
                               void *userkey,
                               T1E1STATUS * statbuff, void *stats_notif);

/* Stats Change Notification Prototype (user-defined function):
void <stats_notif>( void *userkey,
                    T1E1STATUS *statbuff ); */

S16           t1e1_dereg_stats(U8 network, void *userkey);

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

#endif  /* _TDMUSER_H */
