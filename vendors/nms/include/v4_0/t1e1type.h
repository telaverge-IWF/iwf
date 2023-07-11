/*****************************************************************************
 *
 * t1e1type.h - Data types for t1e1 api applications
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

#ifndef _T1E1TYPE_H
#define _T1E1TYPE_H

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
#include "tdmuser.h"

/* NOTE: The J1 mode is not defined as part of the MVIP 95 standard include file.
 *       An extension literal is defined here so the J1 type can be identified.
 */
#define MVIP95_X_J1_TRUNK_DEVICE    0x00A0

/******************************************************************************
* For board selection
******************************************************************************/
#ifndef TXBOARD_DEF
#define  TXBOARD_DEF 1
typedef U8          TXBOARD_T;    /* board numbers 1..8 */
#endif

/******************************************************************************
* defines for network interface selection (T1/E1-A or T1/E1-B)
******************************************************************************/
#ifndef NETWORK_DEF
#define NETWORK_DEF 1
typedef U16           NETWORK_T;
#endif

#ifndef NET_T1A                     /* same as MVIP API NET_T1A */
#define NET_T1A               1
#endif

#ifndef NET_T1B                     /* same as MVIP API NET_T1B */
#define NET_T1B				  2
#endif

#ifndef NET_T1C                     /* same as MVIP API NET_T1C */
#define NET_T1C               3
#endif

#ifndef NET_T1D                     /* same as MVIP API NET_T1D */
#define NET_T1D               4
#endif

#ifndef NET_T1E                     /* same as MVIP API NET_T1E */
#define NET_T1E               5
#endif

#ifndef NET_T1F                     /* same as MVIP API NET_T1F */
#define NET_T1F               6
#endif

#ifndef NET_T1G                     /* same as MVIP API NET_T1G */
#define NET_T1G               7
#endif

#ifndef NET_T1H                     /* same as MVIP API NET_T1H */
#define NET_T1H               8
#endif

#if 0

/*******************************************************************************
* T1/E1 Indication Codes
*******************************************************************************/
#define STATUS_CARRIER                  0x80
#define CARRIER_ALARM                   0x81
#define ABCD_CHANGE                     0x82

#endif

#define PERFREP_15MIN					0x83
#define PERFREP_24HR					0x84

/*******************************************************************************
* T1/E1 Framing Values
*******************************************************************************/
#define FRAMING_NONE                    0
#define FRAMING_D4                      1   /* T1 */
#define FRAMING_ESF                     2   /* T1 */
#define FRAMING_CCS                     3   /* E1 */
#define FRAMING_CAS                     4   /* E1 */
#define FRAMING_CCSCRC4                 5   /* E1 */
#define FRAMING_CASCRC4                 6   /* E1 */
#define FRAMING_F4                      7   /* T1 */
#define FRAMING_F72                     8   /* T1 */

/*******************************************************************************
* T1/E1 Encoding Values
*******************************************************************************/
#define ENCODING_NONE                   0
#define ENCODING_NOZCS                  1   /* T1|E1 */
#define ENCODING_BIT7_ZCS               2   /* T1 */
#define ENCODING_B8ZS                   3   /* T1 */
#define ENCODING_HDB3                   4   /* E1 */

/*******************************************************************************
* T1 Line Build out
*******************************************************************************/
/* Build out values in short haul mode */
#define BUILDOUT_133                    0   /* 0 to 133 feet */
#define BUILDOUT_266                    1   /* 133 to 266 feet */
#define BUILDOUT_399                    2   /* 266 to 399 feet */
#define BUILDOUT_533                    3   /* 399 to 533 feet */
#define BUILDOUT_655                    4   /* 533 to 655 feet */
#define BUILDOUT_MAX                    4   /* maximum line build out [short haul mode] */

/* Build out values in long haul mode [ANSI T1.403] */
#define BUILDOUT_LH_0                   0   /* 0 dB */
#define BUILDOUT_LH_7_5                 1   /* -7.5 dB */
#define BUILDOUT_LH_15                  2   /* -15 dB */
#define BUILDOUT_LH_22_5                3   /* -22.5 dB */
#define BUILDOUT_LH_MAX                 3   /* maximum line build out [long haul mode] */

/*******************************************************************************
* T1/E1 Carrier Sync Values
*******************************************************************************/
#define CARRIER_NONE                    0
#define CARRIER_SYNC                    1
#define CARRIER_NOSYNC                  2
#define CARRIER_LOST                    3

/*******************************************************************************
* T1/E1 Robbed bit enable/disable
*******************************************************************************/
#define ROBBEDBIT_DIS					0
#define ROBBEDBIT_ENA					1

/*******************************************************************************
* T1/E1 Loop timing master or slave
*******************************************************************************/
#define LOOPTIMING_SLAVE				0
#define LOOPTIMING_MASTER				1

/*******************************************************************************
* T1/E1 Carrier Status Options
*******************************************************************************/
#define T1E1_RESET_COUNTS				1

/*******************************************************************************
* T1/E1 Conditioning on/off
*******************************************************************************/
#define T1E1_COND_OFF					0
#define T1E1_COND_ON					1

/* general selector for choosing all channels */
#define T1E1_CHAN_ALL					0xFF

/*******************************************************************************
* T1/E1 Channel Transparency on/off
*******************************************************************************/
#define T1E1_CHAN_NORMAL				0
#define T1E1_CHAN_TRANSPARENT			1

/*******************************************************************************
* T1/E1 Carrier alarm states (These are now bit masks as well as values)
* To set an alarm state, use the value.  On status updates, the alarmstate is
* returned as a bit mask of all alarms currently detected.
*******************************************************************************/
#define NO_ALARM                        0
#define YELLOW_ALARM                    0x01
#define BLUE_ALARM                      0x02
#define TS16AIS_ALARM                   0x04
#define TS16SIG_ALARM                   0x08
#define DISTANTMF_ALARM                 0x10
#define RED_ALARM                       0x20
#define TS16LOS_ALARM                   0x40

/*******************************************************************************
* T1/E1 Loopback Values
*******************************************************************************/
#define LOOPBACK_NONE                   0
#define LOOPBACK_LOCAL                  1
#define LOOPBACK_REMOTE                 2

/*******************************************************************************
* T1/E1 notification options
*******************************************************************************/
#define T1E1_REG_STATUS					1   /* register for status changes */
#define T1E1_REG_ALARMS					2   /* register for alarm notif. */
#define T1E1_REG_15MIN_REPORT			4   /* register for 15-min. perf. report */
#define T1E1_REG_24HR_REPORT			8   /* register for 24-hour perf. report */

/*******************************************************************************
* T1E1 Error Codes
*******************************************************************************/
#define T1E1_SUCCESS					0
#define T1E1_INVALID_COMMAND            200
#define T1E1_DEVICE_ERROR               202
#define T1E1_NO_RESOURCES               204
#define T1E1_INVALID_TIMESLOT           211
#define T1E1_MISSING_PARAMETERS         212
#define T1E1_INVALID_MODE               216
#define T1E1_INVALID_PARAMETER          218
#define T1E1_INTERNAL_CONFLICT          222
#define T1E1_CONNECTION_NOT_SUPPORTED   223
#define T1E1_INVALID_LENGTH     		224
#define T1E1_INVALID_CARRIER			225
#define T1E1_INVALID_FRAMING    		226
#define T1E1_INVALID_CODING		   		227
#define T1E1_INVALID_BLDOUT		   		228
#define T1E1_INVALID_LOOPBACK			229

/* driver/API related errors */
#define T1E1_INVALID_HANDLE             -1
#define T1E1_NO_DRIVER					-2
#define T1E1_OPEN_FAIL					-3
#define T1E1_BAD_BOARD					-4
#define	T1E1_SEND_ERROR					-5
#define	T1E1_NO_RESPONSE				-6
#define T1E1_RECV_ERROR					-7

#define T1E1_MAX_CARRIERS               16  /* max carriers on single board */
/*****************************************************************************
 * TxT1E1Types - type of each carrier E1/T1/J1
 *****************************************************************************/
typedef struct _txt1e1Types
{
    U8          count;                      /* count of carriers available on board */
    U8          avail[3];
    U8          mode[T1E1_MAX_CARRIERS];    /* currently config'd type of carrier */
} TxT1E1Types;

/* define structure of statistics block passed back from TX board
 * to application for 15-minute or 24-hour intervals.
 */
typedef struct _txt1e1Stats
{
    U16            errSecs;         /* errored seconds */
    U16            lineErrSecs;     /* line errored seconds */
    U16            burstyErrSecs;   /* bursty errored seconds */
    U16            severlyErrSecs;  /* severely errored seconds */
    U16            unaSecs;         /* unavailable seconds */
    U8             slipSecs;        /* controlled slip seconds */
    U8             lofCnt;          /* loss of frame count */
}
TxT1E1Stats;

/* Define structure for configuration block passed between application and
 * API to define/retrieve carrier configuration. Fields are as follows.
 *
 *	frameMode	Framing type for this carrier (D4 or ESF)
 *
 *	lineCode	Line coding for this carrier (bit 7 zcs, b8zs, no code
 * 				substitution).
 *
 *	lineBldout	Line build out for this carrier (controls transmitter
 *				wave shaping based on length of cables).
 *
 *	debounce	Reserved for future use.
 *
 *	robbedBit	Specifies whether robbed bit signalling is used on this
 *				carrier (reserved for future use).
 *
 *  loopMaster  Specifies whether TX board is timing master or slave for
 *				this carrier.
 */
typedef struct _txt1e1Config
{
    U8            frameMode;  /* framing mode for line */
    U8            coding;     /* coding technique */
    U8            lineBldOut; /* equalization/line build out */
    U8            debounce;   /* reserved for future use */
    U8            robbedBit;  /* enables or disables robbed
                                 * bit signalling on this line */
    U8            loopMaster; /* sets TX board as timing master or slave */
    U8            pad_end[2]; /* pad to 32-bit aligned structure size */
}
TxT1E1Config;

/*****************************************************************************
 * TxT1E1ConfigEx - extended E1/T1/J1 carrier config
 *****************************************************************************/
typedef struct _txt1e1ConfigEx
{
    TxT1E1Config    std;    /* standard configuration */

    U8              alarmDetect;        /* extended alarm handling / error detection */
#define T1E1_X_EXZE     (1<<0)  /* set = extended code violation or excessive zero detection */

#define E1_X_ALM        (1<<1)  /* set = AIS alarm detected according to ITU-T G.775
                                 * clr = AIS alarm detected according to ETS300233 */
#define E1_X_SA6SY      (1<<2)  /* set = detection of the Sa6-bit pattern done synchronously to multiframe
                                 * clr = detection of Sa6-bit pattern indep. of multiframe sync state */
#define E1_X_EXTIW      (1<<3)  /* set = extended CRC4 to Non-CRC4 interworking (searches after 400 ms timer)
                                 * clr = CRC4 to Non-CRC4 interworking according to ITU-T G.706 Annex B */

#define T1_X_SRAF       (1<<1)  /* clr = remote (yellow) alarm format F12:bit2=0; ESF:pattern $FF00
                                 * set = F12:FS-bit of frame 12; ESF:bit2=0 */
#define T1_X_AIS3       (1<<2)  /* clr = AIS indicated when < 3 zeros detected in n frames
                                 * set = AIS detection only in asynchronous state */
#define T1_X_SSC2       (1<<3)  /* set = LFA declared if more than 320 CRC6 errors per second */
#define T1_X_RRAM       (1<<4)  /* set = allow detection of remote (yellow) alarm even during bit error rates */
#define T1_X_LOS1       (1<<5)  /* set = additional condition for LOS alarm cleared: GR-499-CORE */
#define J1_X_SJR        (1<<6)  /* set = alarm handling done according to ITU-T JG. 704+706 */

    U8      autoEnable;         /* automatic mode control (disabled by default) */
#define T1E1_X_AXRA     (1<<0)  /* set = remote alarm bit set automatically if receiver in async state */
#define T1E1_X_CRCI     (1<<1)  /* set = automatic CRC[4] bit inversion */
#define T1E1_X_XCRCI    (1<<2)  /* set = transmit CRC[4|6] bit inversion */
#define T1E1_X_DCOXC    (1<<3)  /* set = center function of transmit circuitry is enabled */

#define E1_X_ALMF       (1<<4)  /* set = automatic loss of multiframe alignment if excessive CRC errors */
#define E1_X_AXS        (1<<5)  /* set = automatic transmission of submultiframe status */
#define E1_X_EBP        (1<<6)  /* set = in async state, E-bit is set [only valid if AXS set] */

#define T1_X_AFRS       (1<<4)  /* set = search for next candidate automatically */

    U8              autoDisable;        /* automatic mode control (enabled by default) */
#define T1E1_X_DAIS     (1<<0)  /* set = automatic AIS insertion disabled
                                 * clr = AIS automatically inserted if in asynchronous state */
#define T1E1_X_DAXLT    (1<<1)  /* set = disable automatic high impedence of transmit pins on short detect */
#define T1E1_X_DXJA     (1<<2)  /* set = disable internal transmit jitter attenuation */
#define T1E1_X_DCF      (1<<3)  /* set = disable center function of receive circuitry */
#define T1E1_X_CMIPRE   (1<<4)  /* set = disable CMI {HDB3 [E1], B8ZS [T1/J1]} precoding */

#define E1_X_AFR        (1<<5)  /* set = disable automatic search for doubleframe alignment
                                 * clr = search for doubleframe alignment automatically
                                 *       initiated if multiframe patterns not found */
#define T1_X_AUTO       (1<<5)  /* set = disable automatic resynchronization */
#define T1_X_CRC        (1<<6)  /* set = disable CRC6 check/generation [ESF format only] */

    U8      spareBits;          /* spare bit handling */
#define E1_X_XSIS       (1<<0)  /* first bit of the service word (default 1) */
#define E1_X_XSIF       (1<<1)  /* transmit spare bit for international use [FAS word] (default 1) */
#define E1_X_XS13       (1<<2)  /* transmit spare bit (frame 13, CRC-multiframe) (default 1) */
#define E1_X_XS15       (1<<3)  /* transmit spare bit (frame 15, CRC-multiframe) (default 1) */

    U8      spareNational;      /* spare bits for national use (0..31) */
#define E1_X_SPARE_NATIONAL 0x1F    /* default: all bits set for E1 */

    U8              serviceWord;        /* service word condition control */
#define E1_X_SWD        (1<<0)  /* set = disable loss of sync based on service word */
#define E1_X_ASY4       (1<<1)  /* clr = 3 consecutive incorrect FAS words causes LOS
                                 * set = 4 consecutive incorrect FAS words causes LOS */

    U8              txPulseMask[4];     /* transmit pulse shape mask (0..31 for 1st-4th level) */
#define E1_XPM_0    0xFF        /* default E1 transmit pulse shape [0] (FF = use default values) */
#define E1_XPM_1    0xFF        /* default E1 transmit pulse shape [1] */
#define E1_XPM_2    0xFF        /* default E1 transmit pulse shape [2] */
#define E1_XPM_3    0xFF        /* default E1 transmit pulse shape [3] */
#define T1_XPM_0    0xFF        /* default T1/J1 transmit pulse shape [0] (FF = set by lineBldOut) */
#define T1_XPM_1    0xFF        /* default T1/J1 transmit pulse shape [1] */
#define T1_XPM_2    0xFF        /* default T1/J1 transmit pulse shape [2] */
#define T1_XPM_3    0xFF        /* default T1/J1 transmit pulse shape [3] */

    U8              rxControl;          /* receive control */
#define T1E1_X_EQON     (1<<0)  /* clr = -10 dB receiver; short haul mode
                                 * set = [E1: -43 dB,T1/J1: -36 dB] receiver; long haul mode */
#define T1E1_X_RLM      (1<<1)  /* set = receiver mode for receive line monitoring */
#define T1E1_X_CLOS     (1<<2)  /* set = received data is cleared as soon as LOS detected */
#define T1E1_X_SCF      (1<<3)  /* set = corner frequency of DCO-R circuitry reduced
                                 *       by factor of 10 to [E1: 0.2 Hz,T1/J1: 0.6 Hz] */
#define T1_X_MFBS       (1<<4)  /* set = RMFB marks beginning of every received multiframe */

    U8              rxInputThresh;      /* receive input threshold (0..7) */
#define T1E1_X_RX_IN_THRESH 2   /* default T1/E1 receive input threshold (~0.6V - G.775) */
    U8              rxSlicerThresh;     /* voltage threshold when receive slicer generates a mark */

#define T1E1_X_SLICER_55    0   /* mark generated if receive line exceeds 55% of peak amplitude */
#define T1E1_X_SLICER_67    1   /* mark generated if receive line exceeds 67% of peak amplitude */
#define T1E1_X_SLICER_50    2   /* mark generated if receive line exceeds 50% of peak amplitude */
#define T1E1_X_SLICER_45    3   /* mark generated if receive line exceeds 45% of peak amplitude */

    U8      pulseDetect;        /* LOS alarm if no transitions in 16x(pulseDetect+1) consec pulse pos's */
#define T1E1_X_PULSE_DETECT 10  /* default: LOS alarm if no transitions in 176 consec pulse pos's */
    U8      pulseRecovery;      /* LOS alarm cleared if pulseRecovery+1 pulses in pulseDetect time interval */
#define T1E1_X_PULSE_RECOVERY 21    /* default: LOS alarm cleared if 22 pulses in pulseDetect time interval */

    U8              syncProc;           /* [re]synchronization procedure control */
#define T1_X_MCSP       (1<<0)  /* multiple candidates synchronization procedure */
#define T1_X_SSP        (1<<1)  /* select synchronization/resynchronization procedure */

    U8              selectSync;         /* select sync conditions */
#define T1_X_SYNC_2OF4      0   /* 2 out of 4 framing bits */
#define T1_X_SYNC_2OF5      1   /* 2 out of 5 framing bits */
#define T1_X_SYNC_2OF6      2   /* 2 out of 6 framing bits */
#define T1_X_SYNC_4CONSEC   3   /* 4 consecutive multiframe pattern in ESF format */

    U8              idle;               /* pattern to send out for idle channels */
#define T1E1_X_IDLE     0x55    /* default idle pattern */

    U8              reserved[34];       /* reserved for future expansion (should be zero-filled) */
} TxT1E1ConfigEx;

/*****************************************************************************
 * TxT1E1Cmd - E1/T1/J1 commands
 *****************************************************************************/
typedef struct _txt1e1Cmd
{
    U8      command;            /* command to perform */
#define T1E1_X_CMD_ENABLE   1   /* Enable framer */
#define T1E1_X_CMD_DISABLE  2   /* Disable framer */
#define T1E1_X_CMD_RESYNC   3   /* Force framer Resynchronization */
#define T1E1_X_CMD_AIS      4   /* Transmit Alarm Indication Signal */
#define T1E1_X_CMD_RA       5   /* Transmit Remote Alarm */
#define T1E1_X_CMD_LLBDOWN  6   /* Transmit Line Loopback Deactivate code */
#define T1E1_X_CMD_LLBUP    7   /* Transmit Line Loopback Activate code */
#define T1E1_X_CMD_LOOP     8   /* Place entire framer in Loop mode */
#define T1E1_X_CMD_CHANLOOP 9   /* Place single framer Channel(s) in Loop mode */
#define T1E1_X_CMD_PRBS     10  /* Transmit Pseudo Random Bit Sequence */
#define T1E1_X_CMD_DEFECT   11  /* Insert Single Bit Defect(s) */
#define T1E1_X_CMD_SIM      12  /* Initiate alarm Simulation (or advance to next test) */

    U8      flags;                  /* command-specific flags */
/* RESYNC - Force framer Resynchronization */
#define E1_X_RESYNC_MULTI   (1<<0)  /* only resync multiframe (when in multiframe mode) [E1] */
#define T1_X_RESYNC_EXLOSS  (1<<1)  /* external loss of frame [T1/J1] */
/* AIS - Transmit Alarm Indication Signal */
#define T1E1_X_AIS_SYS      (1<<0)  /* send AIS over system (local board) interface */
#define T1E1_X_AIS_LINE     (1<<1)  /* send AIS over line (to remote) interface */
/* RA - Transmit Remote Alarm */
#define T1E1_X_RA_SEND      (1<<0)  /* send Remote Alarm */
/* LLB - Transmit Line Loopback Activate|Deactivate code */
#define T1E1_X_LLB_SEND     (1<<0)  /* set = send llb code; clr = stop sending code */
#define T1E1_X_LLB_FIXED    (1<<1)  /* fixed line loopback code (ANSI T1.403) */
#define T1E1_X_LLB_UNFRAMED (1<<2)  /* line loopback code is transmitted unframed */
/* LOOP - Place entire framer in Loop mode */
#define T1E1_X_LOOP_JITTER  (1<<0)  /* remote loop jitter attenuator active */
#define T1E1_X_LOOP_AIS     (1<<1)  /* send AIS (to Sys [payload]; out Line [local]) */
#define T1E1_X_LOOP_TRANS   (1<<2)  /* framing bits not generated but passed transparently */
/* CHANLOOP - Place single framer Channel in Loop mode */
#define T1E1_X_CHANLOOP_OFF (1<<0)  /* set = disable channel loopback; else enable channel loopback */
/* PRBS - Transmit Pseudo Random Bit Sequence */
#define T1E1_X_PRBS_SEND    (1<<0)  /* set = send PRBS; clr = stop sending PRBS */
#define T1E1_X_PRBS_INVERT  (1<<1)  /* PRBS transmitted inverted */
#define T1E1_X_PRBS_GEN20   (1<<2)  /* set = generated according to 2^20 - 1; clr = 2^15 - 1 */
#define T1E1_X_PRBS_FRAMED  (1<<3)  /* set = PRBS generated framed (else unframed) */
#define T1E1_X_PRBS_MONITOR (1<<4)  /* set = monitor PRBS bit errors */
/* DEFECT - Insert Single Bit Defect(s) */
#define T1E1_X_DEFECT_FAS       (1<<0)  /* insert single FAS defect */
#define T1E1_X_DEFECT_MULTI     (1<<1)  /* insert single Multiframe defect */
#define T1E1_X_DEFECT_CRC       (1<<2)  /* insert single CRC defect */
#define T1E1_X_DEFECT_CAS       (1<<3)  /* insert single CAS defect */
#define T1E1_X_DEFECT_PRBS      (1<<4)  /* insert single PRBS defect */
#define T1E1_X_DEFECT_BIPOLAR   (1<<5)  /* insert single Bipolar Violation */
/* SIM - Initiate alarm Simulation (or advance to next test) */
#define T1E1_X_STOP_SIM     (1<<0)  /* set = stop alarm simulation */

    U8      llb_code;               /* llbup, llbdown: line loopback code to be transmitted */
    U8      llb_bits;               /* llbup, llbdown: line loopback code bit length (5..8) */

    U8      loop_mode;              /* loop: place entire framer in Loop mode */
#define T1E1_X_LOOP_OFF     0       /* loopback mode off */
#define T1E1_X_LOOP_REMOTE  1       /* remote loopback  (Line RX => Line TX) */
#define T1E1_X_LOOP_PAYLOAD 2       /* payload loopback (Line RX => Sys & Line TX) */
#define T1E1_X_LOOP_LOCAL   3       /* local loopback   (Sys TX => Sys RX) */

    U8      chanloop_channel;       /* channel address for loopback */

} TxT1E1Cmd;

/*****************************************************************************
 * TxT1E1CarrierStatus - E1/T1/J1 carrier status
 *
 * NOTE: This structure must remain in sync with CarrierStatusResp (t1e1user.h)
 *****************************************************************************/
typedef struct _txt1e1_CarrierStatus
{
    U8          alarmState;     /* alarm status */
    U8          lastAlmState;   /* previous alarm status */
    U8          wordalign;
    U8          syncState;      /* current synchronization state */
    U8          frameMode;      /* current framing mode */
    U8          coding;         /* coding technique */
    U8          lineBldOut;     /* equalization/line build out */
    U8          debounce;       /* reserved for future use */
    U8          robbedBit;      /* robbed bit signalling enabled/disabled */
    U8          loopMaster;     /* TX board timing master or slave */
    U16         currInt;        /* number of seconds in current interval */
    TxT1E1Stats currStats;      /* current interval statistics */
    U16         validInts;      /* number of 15-min intervals in summary */
    U8          pad_1[2];       /* natural alignment padding */
    TxT1E1Stats sumStats;       /* 24-hour summary statistics */
    U16         pvcs;           /* Accumulated path code violations */
    U16         lvcs;           /* Accumulated line code violations */
    U16         slips;          /* Accumulated controlled slips */
    U16         ebits;          /* Accumulated E-bit counts (E1) */
} TxT1E1_CarrierStatus;

/*****************************************************************************
 * TxT1E1PerfReport - E1/T1/J1 performance report
 *
 * NOTE: This structure must remain in sync with PerfReportResp (t1e1user.h)
 *****************************************************************************/
typedef struct _txt1e1_PerfReport
{
    U16         currInt;        /* number of seconds in current interval */
    U8          pad_1[2];       /* natural alignment padding */
    TxT1E1Stats currStats;      /* current interval statistics */
    U16         validInts;      /* number of 15-min intervals so far */
    U8          pad_2[2];       /* natural alignment padding */
    TxT1E1Stats intStats[96];   /* last 96 15-min interval statistics */
    TxT1E1Stats sumStats;       /* 24-hour summary statistics */
    U16         pvcs;           /* Accumulated path code violations */
    U16         lvcs;           /* Accumulated line code violations */
    U16         slips;          /* Accumulated controlled slips */
    U16         ebits;          /* Accumulated E-bit counts (E1) */
} TxT1E1_PerfReport;

/*****************************************************************************
 * TxT1E1ControlCarrier - E1/T1/J1 control carrier
 *
 * NOTE: This structure must remain in sync with CtrlCarrierReq    (t1e1user.h)
 *****************************************************************************/
typedef struct _txt1e1_ControlCarrier
{
    U8          alarmState;     /* sets line into alarm state */
    U8          loopback;       /* sets line into loopback mode */
    U8          pad_end[2];     /* pad to 32-bit aligned structure size */
} TxT1E1_ControlCarrier;

/*****************************************************************************
 * TxT1E1SupvCarrier - E1/T1/J1 supervise carrier
 *
 * NOTE: This structure must remain in sync with SupvCarrierReq    (t1e1user.h)
 *****************************************************************************/
typedef struct _txt1e1_SupvCarrier
{
    U8          notifMask;      /* notification options */
    U8          spare1;         /* spare for alignment */
    U8          pad_end[2];     /* pad to 32-bit aligned structure size */
} TxT1E1_SupvCarrier;

/*****************************************************************************
 * TxT1E1ChannelStatus - E1/T1/J1 channel status
 *
 * NOTE: This structure must remain in sync with ChannelStatusResp (t1e1user.h)
 *****************************************************************************/
typedef struct _txt1e1_ChannelStatus
{
    U32         transparent;    /* bit mask identifies transparent channels */
    U32         rxABCD[4];      /* received ABCD bit values for all channels */
    U32         txABCD[4];      /* transmit ABCD bit values for all channels */
} TxT1E1_ChannelStatus;

/*****************************************************************************
 * TxT1E1CondChannel - E1/T1/J1 condition channel
 *
 * NOTE: This structure must remain in sync with CondChanReq (t1e1user.h)
 *****************************************************************************/
typedef struct _txt1e1_CondChannel
{
    U8          channel;        /* channel number: 0-31 or 0xFF (all) */
    U8          control;        /* conditioning on or off */
    U8          pattern;        /* conditioning pattern (if on) */
    U8          spare1;         /* pad to even byte length */
} TxT1E1_CondChannel;

/*****************************************************************************
 * TxT1E1ConfigChannel - E1/T1/J1 configure channel
 *
 * NOTE: This structure must remain in sync with ConfigChanReq (t1e1user.h)
 *****************************************************************************/
typedef struct _txt1e1_ConfigChannel
{
    U8          channel;        /* channel number: 0-31 */
    U8          transparent;    /* sets channel to transparent mode */
    U8          pad_end[2];     /* pad to 32-bit aligned structure size */
} TxT1E1_ConfigChannel;

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*
 * Unsolicited Status message passed up the T1E1 Status channel (currently
 * channel 11) if requested through the supvCarrier API call
 *@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct txT1E1UHdr       /* common header in all unsolicited msgs */
{
    U16           statusCode; /* request codes from tdmuser.h */
    U8            carrier;    /* which T1/E1 line (A or B) */
    U8            spare1;     /* word align what follows */
}
TxT1E1UHdr;

typedef struct txT1E1UStat
{
    TxT1E1UHdr    uhdr;       /* status code (either STATUS_CARRIER or
                                 * CARRIER_ALARM) & carrier (A or B) */
    U8            alarmState; /* alarm status (CARRIER_ALARM only ) */
    U8            lastAlmState;   /* Previous alarm status (CARRIER_ALARM only ) */
    U8            wordalign;
    U8            syncState;  /* new synch state (STATUS_CARRIER only) */
}
TxT1E1UStat;

/* 15 minute unsolicted performance report message structure */
typedef struct txT1E1Perf15
{
    TxT1E1UHdr     uhdr;       /* status code (always PREFREP_15MIN)
                               *  & carrier (A or B) */
    TxT1E1Stats    currStats;  /* current interval statistics */
    U16            pcvs;       /* Accumulated path code violations */
    U16            lcvs;       /* Accumulated line code violations */
    U16            slips;      /* Accumulated controlled slips */
    U16            ebits;      /* Accumulated E-bit Errors */
}
TxT1E1Perf15;

/* 24 hour unsolicted performance report message structure */
typedef struct txT1E1Perf24
{
    TxT1E1UHdr      uhdr;       /* status code (always PREFREP_24HR)
                                 *  & carrier (A or B) */
    U16             validInts;  /* number of 15-min intervals included */
    U8              pad_1[2];   /* pad to natural alignment */
    TxT1E1Stats     intStats[96];   /* last 96 15-min interval statistics */
    TxT1E1Stats     sumStats;   /* 24-hour summary statistics */
    U16             pcvs;       /* Accumulated path code violations */
    U16             lcvs;       /* Accumulated line code violations */
    U16             slips;      /* Accumulated controlled slips */
    U16             ebits;      /* Accumulated E-bit Errors */
}
TxT1E1Perf24;

typedef struct _txt1e1notifmsg
{
    union
    {                           /* msg bodies from t1e1type.h */
        TxT1E1UHdr      uhdr;   /* common header for all unsolicited msgs */
        TxT1E1UStat     stat;   /* alarm or synch state change */
        TxT1E1Perf15    perf15; /* 15-minute performance report */
        TxT1E1Perf24    perf24; /* 24-hour performance report */
    } umsg;
} TxT1E1NotifMsg;

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

#endif /* _T1E1TYPE_H */
