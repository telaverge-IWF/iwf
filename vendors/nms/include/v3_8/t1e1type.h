
/******************************************************************************
*
*       t1e1type.h - Data types for t1e1 api applications
*
*       DD-MMM-YY    Who                   Description                   Tag
*       =========  =======  ==========================================  ======
*       03-Apr-96  jmd		Created
******************************************************************************/
#ifndef _T1E1TYPE_H_
#define _T1E1TYPE_H_

#include "tdmuser.h"

/******************************************************************************
* For board selection
******************************************************************************/
#ifndef TXBOARD_DEF
#define  TXBOARD_DEF 1
typedef unsigned char TXBOARD_T;    /* board numbers 1..8 */
#endif

/******************************************************************************
* defines for network interface selection (T1/E1-A or T1/E1-B)
******************************************************************************/
#ifndef NETWORK_DEF
#define NETWORK_DEF 1
typedef unsigned short NETWORK_T;
#endif

#ifndef NET_T1A                     /* same as MVIP API NET_T1A */
#define NET_T1A               1
#endif

#ifndef NET_T1B                     /* same as MVIP API NET_T1B */
#define NET_T1B				  2
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
#define FRAMING_D4                      1
#define FRAMING_ESF                     2
#define FRAMING_CCS                     3
#define FRAMING_CAS                     4
#define FRAMING_CCSCRC4                 5
#define FRAMING_CASCRC4                 6

/*******************************************************************************
* T1/E1 Encoding Values
*******************************************************************************/
#define ENCODING_NONE                   0
#define ENCODING_NOZCS                  1
#define ENCODING_BIT7_ZCS               2
#define ENCODING_B8ZS                   3
#define ENCODING_HDB3                   4

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
#define NO_ALARM						0
#define YELLOW_ALARM             0x01
#define BLUE_ALARM               0x02
#define TS16AIS_ALARM            0x04
#define TS16SIG_ALARM            0x08
#define DISTANTMF_ALARM          0x10

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

/* define structure of statistics block passed back from TX2000 to
 * to application for 15-minute or 24-hour intervals.
 */
typedef struct _txt1e1Stats
{
    unsigned short  errSecs;    /* errored seconds */
    unsigned short  lineErrSecs;    /* line errored seconds */
    unsigned short  burstyErrSecs;  /* bursty errored seconds */
    unsigned short  severlyErrSecs; /* severely errored seconds */
    unsigned short  unaSecs;    /* unavailable seconds */
    unsigned char   slipSecs;   /* controlled slip seconds */
    unsigned char   lofCnt;     /* loss of frame count */
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
 *	loopMaster	Specifies whether TX2000 is timing master or slave for
 *				this carrier.
 */
typedef struct _txt1e1Config
{
    unsigned char   frameMode;  /* framing mode for line */
    unsigned char   coding;     /* coding technique */
    unsigned char   lineBldOut; /* equalization/line build out */
    unsigned char   debounce;   /* reserved for future use */
    unsigned char   robbedBit;  /* enables or disables robbed
                                 * bit signalling on this line */
    unsigned char   loopMaster; /* sets TX2000 as timing master or slave */
    unsigned char   pad_end[2]; /* pad to 32-bit aligned structure size */
}
TxT1E1Config;

/* Unsolicited Status message passed up the T1E1 Status channel (currently
 * channel 11) if requested through the supvCarrier API call
 */
typedef struct txT1E1UHdr       /* common header in all unsolicited msgs */
{
    unsigned short  statusCode; /* request codes from tdmuser.h */
    unsigned char   carrier;    /* which T1/E1 line (A or B) */
    unsigned char   spare1;     /* word align what follows */
}
TxT1E1UHdr;

typedef struct txT1E1UStat
{
    TxT1E1UHdr      uhdr;       /* status code (either STATUS_CARRIER or
                                 * CARRIER_ALARM) & carrier (A or B) */
    unsigned char   alarmState; /* alarm status (CARRIER_ALARM only ) */
    unsigned char   lastAlmState;   /* Previous alarm status (CARRIER_ALARM only ) */
    unsigned char   wordalign;
    unsigned char   syncState;  /* new synch state (STATUS_CARRIER only) */
}
TxT1E1UStat;

/* 15 minute unsolicted performance report message structure */
typedef struct txT1E1Perf15
{
    TxT1E1UHdr      uhdr;       /* status code (always PREFREP_15MIN)
                                 *  & carrier (A or B) */
    TxT1E1Stats     currStats;  /* current interval statistics */
    unsigned short  pcvs;       /* Accumulated path code violations */
    unsigned short  lcvs;       /* Accumulated line code violations */
    unsigned short  slips;      /* Accumulated controlled slips */
    unsigned short  ebits;      /* Accumulated E-bit Errors */
}
TxT1E1Perf15;

/* 24 hour unsolicted performance report message structure */
typedef struct txT1E1Perf24
{
    TxT1E1UHdr      uhdr;       /* status code (always PREFREP_24HR)
                                 *  & carrier (A or B) */
    unsigned short  validInts;  /* number of 15-min intervals included */
    unsigned char   pad_1[2];   /* pad to natural alignment */
    TxT1E1Stats     intStats[96];   /* last 96 15-min interval statistics */
    TxT1E1Stats     sumStats;   /* 24-hour summary statistics */
    unsigned short  pcvs;       /* Accumulated path code violations */
    unsigned short  lcvs;       /* Accumulated line code violations */
    unsigned short  slips;      /* Accumulated controlled slips */
    unsigned short  ebits;      /* Accumulated E-bit Errors */
}
TxT1E1Perf24;


#endif
