/*****************************************************************************
 *
 * txalarm.h - TXALARM Structure Definitions
 *
 * This file defines the alarm message structure used for all alarm messages
 * issued from a TX-based task (or the TX operating system) to a host-based
 * application that has registered to receive alarm messages.
 *
 * Alarm messages are the most common type of TX-based logging.
 * Other types of logging are also available (see log_type choices).
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

#ifndef _TXALARM_H
#define _TXALARM_H

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
#include <txnuser.h>            /* primitive field type definitions */
#include <dpriface.h>           /* well-known channel definitions */

/*---------------------------------------------------------------------------*
 * Log header (common to all types of log records)
 *---------------------------------------------------------------------------*/
#define TXLOG_TASKNAME_SZ   (8+2)   /* size of task name (+ 2 so NULL-term'd) */

typedef struct __txlog_hdr
{
    U32     secs_epoch;         /* seconds since epoch - log record timestamp */
    U8      avail1[8];          /* available for future expansion */
    S8      task_name[TXLOG_TASKNAME_SZ];   /* name of task that issued log record */
    U8      log_type;           /* type of log record */
#define TXLOG_TYPE_ALARM    0   /* alarm message */
#define TXLOG_TYPE_PRINTF   1   /* ASCII trace message (gen'd by printf) */
#define TXLOG_TYPE_TRACE    2   /* binary trace record */
#define TXLOG_TYPE_MAX      3

    U8      avail2;             /* pad to 32-bit aligned structure size */
    U32     logs_lost;          /* count of log records lost [not delivered to receiver] */
} TXLOG_HDR;

/*---------------------------------------------------------------------------*
 * Alarm Buffer
 *---------------------------------------------------------------------------*/
#define TXLOG_ALARM_SZ  128     /* max size of alarm string */

typedef struct __txlog_alarm
{
    U16     number;             /* unique number identifying alarm */
    U16     severity;           /* severity of alarm */
#define TXALARM_SPECIFIC    0   /* severity determined by specific alarm number */
#define TXALARM_INFO        1   /* Informational */
#define TXALARM_WARNING     2   /* Warning */
#define TXALARM_ERROR       3   /* Error */
#define TXALARM_CRITICAL    4   /* Critical Error */

    U8      avail[12];          /* available for future expansion */
    U32     secs_epoch;         /* seconds since epoch [LEGACY duplicate of header field] */
    S8      message[TXLOG_ALARM_SZ+2]; /* alarm message: <task name><0><text string><0> */
} TXLOG_ALARM;

/*---------------------------------------------------------------------------*
 * Printf Buffer
 *---------------------------------------------------------------------------*/
#define TXLOG_PRINTF_SZ 128     /* max size of printf string */

typedef struct __txlog_printf
{
    U8      avail[12];                  /* available for future expansion */
    S8      text[TXLOG_PRINTF_SZ+2];    /* printf text string (+2 for NULL-terminator) */
} TXLOG_PRINTF;

/*---------------------------------------------------------------------------*
 * Trace Buffer
 *---------------------------------------------------------------------------*/
#define TXLOG_TRACE_MAX 1536    /* max size of trace buffer */

typedef struct __txlog_trace_info
{
    U32     trace_id;           /* trace identifier */
    U32     trace_type;         /* ID-specific type of trace record */
    U32     trace_length;       /* byte length of trace data */
    U8      avail[12];          /* available for future expansion */
} TXLOG_TRACE_INFO;

typedef struct __txlog_trace
{
    TXLOG_TRACE_INFO    info;                   /* information about trace record */
    U8                  data[TXLOG_TRACE_MAX];  /* binary trace record */
} TXLOG_TRACE;

/*---------------------------------------------------------------------------*
 * Complete Log Message Definitions
 *---------------------------------------------------------------------------*/

/* ----- alarm message ----- */
typedef struct __txlog_alarm_msg
{
    TXLOG_HDR       hdr;        /* common message header */
    TXLOG_ALARM     alarm;      /* alarm-specific information */
} TXLOG_ALARM_MSG;

/* define minimum possible size of alarm message */
#define TXLOG_ALARM_MIN_SZ  (sizeof(TXLOG_ALARM_MSG) - (TXLOG_ALARM_SZ+2) + 4)

/* ----- printf message ----- */
typedef struct __txlog_printf_msg
{
    TXLOG_HDR       hdr;        /* common message header */
    TXLOG_PRINTF    printf;     /* printf-specific information */
} TXLOG_PRINTF_MSG;

/* ----- trace message ----- */
typedef struct __txlog_trace_msg
{
    TXLOG_HDR       hdr;        /* common message header */
    TXLOG_TRACE     trace;      /* trace-specific information */
} TXLOG_TRACE_MSG;

/* ----- union of all message types ----- */
typedef struct __txlog_msg
{
    TXLOG_HDR       hdr;        /* common message header */

    union
    {
        TXLOG_ALARM     alarm;  /* alarm-specific information */
        TXLOG_PRINTF    printf; /* printf-specific information */
        TXLOG_TRACE     trace;  /* trace-specific information */
    } log;

} TXLOG_MSG;

/*###########################################################################*
 *
 * LEGACY DEFINITIONS
 *
 * The following literal/structure definitions are provided for backwards
 * compatibility; allowing legacy applications to build cleanly
 * and process alarms without requiring changes to source code.
 *
 * Note that several of the fields defined below are not actually filled
 * with meaningful data.  It is highly recommended that alarm processing
 * applications be recoded using the structures defined above when possible.
 *
 *###########################################################################*/

#define DEFAULTALARMCHAN  PT_ALARM
#define ANODENSIZE        8
#define ASTRSIZE          80
#define ALARM_MTU         1514

/*---------------------------------------------------------------------------*
 * LEGACY timestamp record - !!! NO LONGER USED !!!
 *
 * Timestamps are now provided as seconds since epoch.
 * For legacy applications, 'seconds since epoch' are provided as 'infalmn2'.
 * Use the function 'localtime' to convert this value to a timestamp record.
 *---------------------------------------------------------------------------*/
typedef struct txtimestamp
{
    WORD            year;
    BYTE            month;
    BYTE            day;
    BYTE            hour;
    BYTE            min;
    BYTE            sec;
    signed char     zone;
    WORD            msec;
    BYTE            pad_e[2];               /* pad to 32-bit aligned structure size */
}
txtimestamp_t;

/*---------------------------------------------------------------------------*
 * LEGACY alarm record header - !!! NO LONGER USED !!!
 *
 * No field information from this header record remains valid.
 * Legacy applications should use the information in the txalarm_buf
 * record that follows this header record.
 *---------------------------------------------------------------------------*/
typedef struct txalarm_hdr
{
    txtimestamp_t   datetime;               /* !!! NO LONGER USED !!! (see infalmn2) */
    char            nodename[ANODENSIZE];   /* !!! NO LONGER USED !!! */
    WORD            nodenlen;               /* !!! NO LONGER USED !!! */
    BYTE            board;                  /* !!! NO LONGER USED !!! (get source board from CPIPKT header) */
    BYTE            hopsleft;               /* !!! NO LONGER USED !!! */
    WORD            datalen;                /* !!! NO LONGER USED !!! */
    BYTE            pad_e[2];               /* pad to 32-bit aligned structure size */
}
txalarm_hdr_t;

/*---------------------------------------------------------------------------*
 * LEGACY alarm data buffer
 *---------------------------------------------------------------------------*/
typedef struct txalarm_buf
{
    WORD            infalarm;               /* alarm number */
    WORD            infalms1;               /* !!! NO LONGER USED !!! */
    WORD            infalms2;               /* !!! NO LONGER USED !!! */
    BYTE            pad_1[2];               /* pad to re-align to even long boundary */
    DWORD           infalmn0;               /* !!! NO LONGER USED !!! */
    DWORD           infalmn1;               /* !!! NO LONGER USED !!! */
    DWORD           infalmn2;               /* seconds since epoch - use 'localtime' to convert to timestamp */
    char            infalmstr[ASTRSIZE];    /* <taskname [padded to 8 characters]><0><alarm text><0> */
}
txalarm_buf_t;

/*---------------------------------------------------------------------------*
 * LEGACY alarm record
 *---------------------------------------------------------------------------*/
typedef struct txalarm
{
    txalarm_hdr_t   hdr;                    /* !!! NO LONGER USED !!! */
    txalarm_buf_t   data;                   /* alarm data buffer */
}
txalarm_t;

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

#endif  /* _TXALARM_H */
