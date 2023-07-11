
/****************************************************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
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
 *                                                                          *
 * CONTRACT: Daewoo testbed                                                 *
 *                                                                          *
 *     FILE: its_intern.h                                                   *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: its_intern.h,v 9.3 2007/01/11 12:43:44 yranade Exp $
 *
 * LOG: $Log: its_intern.h,v $
 * LOG: Revision 9.3  2007/01/11 12:43:44  yranade
 * LOG: Merge changes from 6.5.3 and Lucent branches
 * LOG:
 * LOG: Revision 9.2.6.5  2006/12/23 10:07:00  randresol
 * LOG: Modifications to allow TTC and ITU stacks to run in parallel
 * LOG:
 * LOG: Revision 9.2.6.4  2006/05/17 14:54:31  lbana
 * LOG: Scrambling bit PBN Issue ID 3288
 * LOG:
 * LOG: Revision 9.2.6.3  2006/05/17 14:49:43  lbana
 * LOG: PBN Issue ID 3288:Made scrambling bit configurable
 * LOG:
 * LOG: Revision 9.2.6.2  2005/11/11 22:42:22  randresol
 * LOG: Add Service Option Parameters for ATM
 * LOG:
 * LOG: Revision 9.2.6.1  2005/09/12 04:33:52  randresol
 * LOG: New implementation for ADAX ATMII platform
 * LOG:
 * LOG: Revision 9.2  2005/05/06 10:04:53  mmanikandan
 * LOG: PR6.5.1 Validation Bug(1793) Fix.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:25  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:54:38  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.14.1.14.4  2005/02/18 11:38:17  dsatish
 * LOG: Changes related to TTC
 * LOG:
 * LOG: Revision 7.1.14.1.14.3  2005/01/05 12:28:19  craghavendra
 * LOG: Syslog Enhancement.
 * LOG:
 * LOG: Revision 7.1.14.1.14.2  2005/01/03 15:08:18  snagesh
 * LOG: MTP2 OAM changes
 * LOG:
 * LOG: Revision 7.1.14.1.14.1  2004/12/16 14:56:36  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.1.14.1.6.1  2004/10/25 20:34:14  randresol
 * LOG: Start Japan SS7 Implementation
 * LOG:
 * LOG: Revision 7.1.14.1  2004/07/09 07:14:01  dsatish
 * LOG: Merging activity done for timeslot and 56kbps changes
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:40  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:52  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 1.10  2001/12/28 18:43:40  mmiers
 * LOG: A few mistakes to fix.
 * LOG:
 * LOG: Revision 1.9  2001/12/19 23:54:02  mmiers
 * LOG: Get ADAX vendor lib working.
 * LOG:
 * LOG: Revision 1.8  2001/12/18 21:59:19  mmiers
 * LOG: Standardize on exports for vendors
 * LOG:
 * LOG: Revision 1.7  2001/12/18 21:34:51  mmiers
 * LOG: Interim version
 * LOG:
 * LOG: Revision 1.6  2001/12/18 21:23:37  mmiers
 * LOG: New format vendor
 * LOG:
 * LOG: Revision 1.5  2001/10/26 19:14:43  ngoel
 * LOG: add multiple links per transport
 * LOG:
 * LOG: Revision 1.4  2001/10/25 21:44:46  ngoel
 * LOG: add multiple links per transport
 * LOG:
 * LOG: Revision 1.3  2001/10/25 17:23:02  ngoel
 * LOG: add xml parser extension
 * LOG:
 * LOG: Revision 1.2  2001/10/22 21:13:53  ngoel
 * LOG: work in progress
 * LOG:
 * LOG: Revision 1.1  2001/10/22 18:42:47  ngoel
 * LOG: first commit
 * LOG:
 ****************************************************************************/

#if defined(WIN32)

#if defined(ADAX_IMPLEMENTATION)
#define ADAXDLLAPI __declspec(dllexport)
#else
#define ADAXDLLAPI __declspec(dllimport)
#endif

#else  /* WIN32 */

#define ADAXDLLAPI

#endif /* WIN32 */

#define BAUD_RATE_56  56
#define BAUD_RATE_64  64
#define BAUD_RATE_48  48

#define ADAX_E1     1
#define ADAX_T1     2
#define ADAX_OC3    3
#define ADAX_J1     4
#define ADAX_64Kbps 0xff
#define ADAX_56Kbps 0xfe
#define ADAX_48Kbps 0xfd
#define ADAX_8Kbps  0x80

#define ADAX_FAILED     -1
#define MAX_CTL_BUF     128

#define MAX_DATA_LINKS  64

/* ATM Forum Traffic Management 4.1 traffic class defines for AAL5 and AAL0 */
#define ATMF_AAL50_1PCR 0 /* 1/Peak Cell Rate Bit Rate Traffic Shaping */
#define ATMF_AAL50_VBR  1 /* Variable Bit Rate Traffic Shaping */
#define ATMF_AAL50_ABR  2 /* Absolute Bit Rate Traffic Shaping */
#define ATMF_AAL50_BAD  3 /* Invalid traffic management option for AAL5/0 */


#include <ansi/mtp3.h>
#include <itu/mtp3.h>
#include <ansi/isup.h>
#include <itu/isup.h>

#include <vframe.h>
#include <its_trace.h>
#include <dbc_serv.h>
#include <ss7_mgmt.h>

#define ATM_SCRAMB_CELL_PAYLOAD_STR "cellPayload"
#define ATM_SCRAMB_DS3_STR          "ds3-scramb"
#define ATM_SCRAM_E3_STR            "e3-scramb"
#define ATM_SCRAMBLE_ENABLE_STR     "enable"
#define ATM_SCRAMBLE_DISABLE_STR    "disable"

#define ADAX_CLASS_NAME_ANSI "ADAX Vendor Class ANSI"
#define ADAX_CLASS_NAME_CCITT "ADAX Vendor Class CCITT"
#define ADAX_CLASS_NAME_PRC "ADAX Vendor Class PRC"
#define ADAX_CLASS_NAME_TTC "ADAX Vendor Class TTC"

/*
 * MTP2 Tracing information
 */
extern TRACE_Data* MTP2_ADAX_TraceData;

#define MTP2_TRACE_CRITICAL  0
#define MTP2_TRACE_ERROR     1
#define MTP2_TRACE_WARNING   2
#define MTP2_TRACE_DEBUG     3

#define MTP2_CRITICAL(args) \
    TRACE(MTP2_ADAX_TraceData, MTP2_TRACE_CRITICAL, args)

#define MTP2_ERROR(args) \
    TRACE(MTP2_ADAX_TraceData, MTP2_TRACE_ERROR, args)

#define MTP2_WARNING(args) \
    TRACE(MTP2_ADAX_TraceData, MTP2_TRACE_WARNING, args)

#define MTP2_DEBUG(args) \
    TRACE(MTP2_ADAX_TraceData, MTP2_TRACE_DEBUG, args)

#define MTP2_TRACE_CRITICAL_STRING  ITS_TRACE_CRITICAL_STRING
#define MTP2_TRACE_ERROR_STRING     ITS_TRACE_ERROR_STRING
#define MTP2_TRACE_WARNING_STRING   ITS_TRACE_WARNING_STRING
#define MTP2_TRACE_DEBUG_STRING     ITS_TRACE_DEBUG_STRING

#define MTP2_CRITICAL_STRING        ITS_CRITICAL_STRING
#define MTP2_ERROR_STRING           ITS_ERROR_STRING
#define MTP2_WARNING_STRING         ITS_WARNING_STRING
#define MTP2_DEBUG_STRING           ITS_DEBUG_STRING

#define MTP2_STDOUT_STRING          ITS_STDOUT_STRING
#define MTP2_FILE_STRING            ITS_FILE_STRING
#define MTP2_SYSLOG_STRING          ITS_SYSLOG_STRING

#define MTP2_TRACE_CRITICAL_FILE    ".mtp2-traceCritical"
#define MTP2_TRACE_ERROR_FILE       ".mtp2-traceError"
#define MTP2_TRACE_WARNING_FILE     ".mtp2-traceWarning"
#define MTP2_TRACE_DEBUG_FILE       ".mtp2-traceDebug"

typedef struct
{
    MGMT_AlarmLevel alarmLevel;
    ITS_BOOLEAN     traceOn;
    ITS_CHAR        traceType[ITS_PATH_MAX];
    ITS_CHAR        traceOutput[ITS_PATH_MAX];
}
MTP2GeneralCfg;

typedef enum
{
    ATMII_CBR = ATMF_AAL50_1PCR,
    ATMII_VBR = ATMF_AAL50_VBR,
    ATMII_ABR = ATMF_AAL50_ABR,
    ATMII_INVALID
}
TRAFFIC_CLASS;

typedef struct 
{
    TRAFFIC_CLASS trafficClass;
    ITS_UINT peekCellRate; 
    ITS_UINT minimumSustainableCellRate;
    ITS_UINT maxBurstSize;
    ITS_UINT initialCellRate;
    ITS_USHORT priority;
    ITS_USHORT bufferClass;

}
ATMII_ServiceOptions;

typedef struct _adaxAtmVcInfoList
{
    struct _adaxAtmVcInfoList* next;
    ITS_UINT                   vcId;
    ITS_UINT                   vpi;
    ITS_UINT                   vci;
    ITS_UINT                   vcCount;
    ITS_BOOLEAN          localServiceOptonsPresent;
    ATMII_ServiceOptions localServiceOptions;
}
ADAX_ATM_KeyInfo;



typedef struct
{
    ITS_USHORT       timeslot;
    ITS_OCTET        linkCode;
    ADAX_ATM_KeyInfo atmInfo;
}
DataLink;

typedef enum
{
    ATMII_AAL5,
    ATMII_HDLC,
    ATMII_AAL2,
    ATMII_AAL0
}
ATMII_CONNECTION_TYPE;

typedef enum
{
    ADAX_HDCII, /* default */
    ADAX_ATMII
}
ADAX_HARDWARE;

/* Scrambling is _valid only_ for OC3 ports. By default
 * payload scrambling is disabled.
 * On ATM_ET1 cards if port is set to T1 scrambling is disabled
 *              or  if port is set to E1 scrambling is enabled.
 * It is not possible to change the state of scrambling for
 * ATM_ET1 cards.
 */
typedef enum
{
    ATM_SCRAMB_NONE,
    ATM_CELL_PAYLOAD, /* Only this option is supported */
    ATM_DS3_SCRAMB,
    ATM_E3_SCRAMB
}
ATMII_SCRAMB_TYPE;

typedef struct
{
    VENDOR_Instance       inst;
    ITS_INT               fd[MAX_DATA_LINKS];
    ITS_UINT              which;
    ITS_UINT              trunk;
    ITS_UINT              channel;
    ITS_OCTET             trunkType;  /* T1 / E1 */
    ITS_OCTET             baudRate;   /* 64 / 56 */
    ITS_OCTET             linkSet;
    ITS_OCTET             numTimeslots;
    DataLink              dataLink[MAX_DATA_LINKS];
    ITS_OCTET             mtp2State;
    ITS_OCTET             mtp2Status;
    ITS_INT               pipefd[2];
    ADAX_HARDWARE         hardware;
    ATMII_CONNECTION_TYPE connectionType;
    ITS_BOOLEAN           globalServiceOptonsPresent;
    ATMII_SCRAMB_TYPE     scrambType;
    ATMII_ServiceOptions  globalServiceOptions;
}
ITS_SS7_CONTEXT;

#if defined (CCITT)
#define ADAXRetrieveMTP2Message   ADAXRetrieveMTP2Message_CCITT
#define ADAXSendMTP2Event         ADAXSendMTP2Event_CCITT
#elif defined (ANSI)
#define ADAXRetrieveMTP2Message   ADAXRetrieveMTP2Message_ANSI
#define ADAXSendMTP2Event         ADAXSendMTP2Event_ANSI
#elif defined (PRC)
#define ADAXRetrieveMTP2Message   ADAXRetrieveMTP2Message_PRC
#define ADAXSendMTP2Event         ADAXSendMTP2Event_PRC
#elif defined (TTC)
#define ADAXRetrieveMTP2Message   ADAXRetrieveMTP2Message_TTC
#define ADAXSendMTP2Event         ADAXSendMTP2Event_TTC
#endif

int ADAXInitializeMTP2(ITS_SS7_HANDLE handl);
int ADAXTermMTP2(ITS_SS7_HANDLE handle);
int ADAXRetrieveMTP2Message(ITS_SS7_HANDLE handl);
int ADAXSendMTP2Event(ITS_SS7_HANDLE handle, ITS_OCTET *data, ITS_USHORT dlen);
void ADAX_MTP2_Console(DBC_Server *dbc, const char *cmdLine);
int ADAXCommit(FILE* fp);
