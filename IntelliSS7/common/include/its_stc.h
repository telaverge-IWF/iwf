/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                  
 * CONTRACT: INTERNAL
 *      
 ****************************************************************************
 *
 *  LOG: $Log: its_stc.h,v $
 *  LOG: Revision 9.1  2007/01/10 11:15:04  yranade
 *  LOG: Merge changes from 6.5.3 and Lucent branches
 *  LOG:
 *  LOG: Revision 1.1.2.4  2006/11/03 18:37:49  ssingh
 *  LOG: APIs for Get/Set of Global Data
 *  LOG:
 *  LOG: Revision 1.1.2.3  2005/11/10 05:40:36  clin
 *  LOG: Fix bug #2984
 *  LOG:
 *  LOG: Revision 1.1.2.2  2005/09/29 04:02:55  clin
 *  LOG: Adding pegs.
 *  LOG:
 *  LOG: Revision 1.1.2.1  2005/09/15 15:47:16  clin
 *  LOG: Initial check in.
 *  LOG:
 *                 
 ****************************************************************************/
#ifndef _STC_H
#define _STC_H


#include <its.h>
#include <its_object.h>
#include <its_callback.h>
#include <its_route.h>
#include <its_trace.h>

#include <stdio.h>

#if defined(__cplusplus)
extern "C"
{
#endif

#if defined (WIN32)

#if defined STC_IMPLEMENTATION
#define STCDLLAPI __declspec (dllexport)
#else
#define STCDLLAPI __declspec (dllimport)
#endif

#else
#define STCDLLAPI
#endif

/*
 * class name and Parser extension
 * parameters for stc.
 */
#define STC_CLASS_NAME                 "STC-CCITT Stack"
#define STC_DATA_CLASS_NAME            "STC_Data"

/*
 * resource file keys
 */
#define STC_VERSION_STRING             "version"
#define STC_INFO_STRING                "StcInfo"
#define STC_OPC_STRING                 "OPC"
#define STC_DPC_STRING                 "DPC"
#define STC_SIO_STRING                 "SIO"
#define STC_MAX_LENGTH_STRING          "maxDataLength"
#define STC_TIMER_T29_STRING           "vTimer_Short"
#define STC_TIMER_T30_STRING           "vTimer_Long"
#define STC_CONG_LEVEL_NO_STRING       "CLnc"
#define STC_CONG_LEVEL_MAX_STRING      "CLmc"
#define STC_CONG_LEVEL_STEP_STRING     "CLst"


STCDLLAPI extern CALLBACK_Manager*     MTP3_ManagementCallbacks;
STCDLLAPI HASH_Table                   __STC_Entry_Table;

#define STC_VERSION_1999               1999
#define STC_VERSION_2001               2001
#define STC_MAX_LEN                    4096

/*
 * class record
 */
STCDLLAPI extern ITS_Class itsSTC_Class;

typedef struct _stcKeyList
{
    struct _stcKeyList*   next;
    ITS_UINT               dpc;
    ITS_UINT               opc;
    ITS_SERIAL             t29;          /* value of Timer_Short */
    ITS_SERIAL             t30;          /* value of Timer_Long */
    ITS_USHORT             len;          /* value of Max_Length */
    ITS_OCTET              sio;
    /*ITS_OCTET              clnc;*/         /* value of no congestion */
    /*ITS_OCTET              clmc;*/         /* value of max congestion */
    ITS_OCTET              clst;         /* value of congestion step */
}
STC_KeyInfo;

typedef struct
{
    ITS_UINT               version;      /* Version identifier */
    ITS_SERIAL             t29;          /* value of Timer_Short */
    ITS_SERIAL             t30;          /* value of Timer_Long */
    ITS_USHORT             len;          /* value of Max_Length */
#if 0
    ITS_OCTET              clnc;         /* value of no congestion */
    ITS_OCTET              clmc;         /* value of max congestion */
#endif
    ITS_OCTET              clst;         /* value of congestion step */
    STC_KeyInfo*           keyList;      /* List of STC entries */
}
STC_ParseInfo;

typedef enum _STC_PEG_ID
{   
    PEG_STC_IN_SERVICE_ID,
    PEG_STC_OUT_OF_SERVICE_ID,
    PEG_STC_CONGESTION_ID,
    PEG_STC_TRANSFER_REQ_ID,
    PEG_STC_TRANSFER_IND_ID,
    PEG_STC_INVALID_ID,

    ALL_STC_PEGS = 99
}
STC_PEG_ID;

typedef struct _STC_MIB_STATS
{
    ITS_UINT     inServ;  /* count of IN-SERVICE sent to app */
    ITS_UINT     outServ; /* count of OUT-OF-SERVICE sent to app */
    ITS_UINT     cong;    /* count of CONGESTION sent to app */
    ITS_UINT     tReq;    /* count of TRANSFER Request sent */
    ITS_UINT     tInd;    /* count of TRANSFER Indication sent */
}
STC_MIB_STATS;

/*
 * service between STC and GST-SAP
 */
typedef enum
{
    STC_START_INFO,
    STC_IN_SERVICE,
    STC_OUT_OF_SERVICE,
    STC_CONGESTION,
    STC_TRANSFER
}
STC_Service;

typedef enum
{
    TRANSFER_REQ,           /* AALT2 to STC */
    MTP3_RESUME_IND,
    MTP3_PAUSE_IND,
    MTP3_TRANSFER_IND,      /* MTP3 to STC */
    MTP3_STATUS_IND,
    POWER_UP
}
STC_Event;

#define CIC_CONTROL_EVEN    2
#define CIC_CONTROL_ODD     1


/*
 * the global control flag defined for STC
 */
extern TRACE_Data* STC_TraceData;

/*
 * tracing
 */
#define STC_TRACE_CRITICAL  0
#define STC_TRACE_ERROR     1
#define STC_TRACE_WARNING   2
#define STC_TRACE_DEBUG     3

#define STC_CRITICAL(args) \
    TRACE(STC_TraceData, STC_TRACE_CRITICAL, args)

#define STC_ERROR(args) \
    TRACE(STC_TraceData, STC_TRACE_ERROR, args)

#define STC_WARNING(args) \
    TRACE(STC_TraceData, STC_TRACE_WARNING, args)

#define STC_DEBUG(args) \
    TRACE(STC_TraceData, STC_TRACE_DEBUG, args)

/*
 * resource strings
 */
#define STC_TRACE_CRITICAL_STRING  "TRACE_CRITICAL"
#define STC_TRACE_ERROR_STRING     "TRACE_ERROR"
#define STC_TRACE_WARNING_STRING   "TRACE_WARNING"
#define STC_TRACE_DEBUG_STRING     "TRACE_DEBUG"

#define STC_CRITICAL_STRING        ITS_CRITICAL_STRING
#define STC_ERROR_STRING           ITS_ERROR_STRING
#define STC_WARNING_STRING         ITS_WARNING_STRING
#define STC_DEBUG_STRING           ITS_DEBUG_STRING
#define STC_SYSLOG_STRING          ITS_SYSLOG_STRING

#define STC_STDOUT_STRING          ITS_STDOUT_STRING
#define STC_FILE_STRING            ITS_FILE_STRING
#define STC_SYSLOG_STRING          ITS_SYSLOG_STRING

#define STC_TRACE_CRITICAL_FILE    ".stc-traceCritical"
#define STC_TRACE_ERROR_FILE       ".stc-traceError"
#define STC_TRACE_WARNING_FILE     ".stc-traceWarning"
#define STC_TRACE_DEBUG_FILE       ".stc-traceDebug"


/*
 * format of a message to/from STC
 *
 * data[0]     - message type
 * data[1-2]   - stc opc
 * data[3-4]   - stc dpc
 * data[5-6]   - stc sio
 * data[7-8]   - data length
 * data[9-n]   - data
 *
 */
#define STC_HEADER_SIZE         9

#define STC_MSG_TYPE(ev)        ((ev)->data[0])
#define STC_GET_OPC(ev)         ((((ev)->data[1]) & 0x3FFFU) | \
                                  ((ev)->data[2] << 8))
#define STC_SET_OPC(ev, v)      ((ev)->data[1] = (v) & 0xFFU, \
                                 (ev)->data[2] = ((v) >> 8) & 0x3FU)
#define STC_GET_DPC(ev)         ((((ev)->data[3]) & 0x3FFFU) | \
                                  ((ev)->data[4] << 8))
#define STC_SET_DPC(ev, v)      ((ev)->data[3] = (v) & 0xFFU, \
                                 (ev)->data[4] = ((v) >> 8) & 0x3FU)
#define STC_GET_SIO(ev)         ((ev)->data[5] | (ev)->data[6] << 8)
#define STC_SET_SIO(ev, v)      ((ev)->data[5] = (v), \
                                 (ev)->data[6] = (v) >> 8)
#define STC_GET_MSG_LEN(ev)     ((ev)->data[7] | (ev)->data[8] << 8)
#define STC_SET_MSG_LEN(ev, v)  ((ev)->data[7] = (v), \
                                 (ev)->data[8] = (v) >> 8)
#define STC_MSG_DATA(ev)        (&(ev)->data[9])

/* STC Global Data API structure */
typedef struct _stc_gl_data
{
    ITS_BOOLEAN setVersion;
    ITS_INT     stcVersion;
    ITS_BOOLEAN setVTimeLong;
    ITS_INT     stcVTimerLong;
    ITS_BOOLEAN setVTimeSort;
    ITS_INT     stcVTimerShort;
    ITS_BOOLEAN setMaxDataLen;
    ITS_INT     stcMaxDataLength;
    ITS_BOOLEAN setCongestion;
    ITS_INT     stcCongestionLevel;
}STC_GL_DATA;

STCDLLAPI ITS_INT STC_GetGlobalData(STC_GL_DATA *data);

STCDLLAPI ITS_INT STC_SetGlobalData(STC_GL_DATA data);

#if defined(__cplusplus)

}
#endif

#endif /* _STC_H */
