/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *                  
 * CONTRACT: INTERNAL
 *      
 *  ID: $Id: m3ua.c,v 9.19.2.1.4.6.4.1.20.2 2014/09/15 10:57:40 jsarvesh Exp $
 *
 *  LOG: $Log: m3ua.c,v $
 *  LOG: Revision 9.19.2.1.4.6.4.1.20.2  2014/09/15 10:57:40  jsarvesh
 *  LOG: Changes done for encoding large size component
 *  LOG:
 *  LOG: Revision 9.19.2.1.4.6.4.1.16.1  2014/09/15 07:20:40  jsarvesh
 *  LOG: Changes done for removing Warnings
 *  LOG:
 *  LOG: Revision 9.19.2.1.4.6.4.1  2011/04/13 07:47:58  nvijikumar
 *  LOG: Fix for compilation issue
 *  LOG:
 *  LOG: Revision 9.19.2.1.4.6  2010/11/19 10:10:08  rajeshak
 *  LOG: Fix for TCS-SMLC Helpdesk Ticket:2443
 *  LOG:
 *  LOG: Revision 9.19.2.1.4.5  2010/07/12 10:07:25  ssingh
 *  LOG: SMLC fix for bug #3056
 *  LOG:
 *  LOG: Revision 9.19.2.1.4.4  2010/05/31 14:16:43  ssingh
 *  LOG: fixing issue #2915; Audit Timer Expiry Handling
 *  LOG:
 *  LOG: Revision 9.19.2.1.4.3  2010/05/17 13:51:45  nvijikumar
 *  LOG: Fix for Id 2851, Destination status updated failed at application
 *  LOG:
 *  LOG: Revision 9.19.2.1.4.2  2010/05/17 12:14:52  nvijikumar
 *  LOG: Fix for 2838 CheckAndStartOrStopAuditTimer func moved from UAL to M3UA since UAL is not protocol dependent
 *  LOG:
 *  LOG: Revision 9.19.2.1.4.1  2010/05/12 09:28:30  ssingh
 *  LOG: fixing smlc issue#2809
 *  LOG:
 *  LOG: Revision 9.19.2.1  2009/03/12 09:01:39  kramesh
 *  LOG: Removed Send_Parm_Error for UAL_CLASS_SNM as its already performed
 *  LOG: using CHECK_M3UA_DECODEMSG_ERROR MACRO.
 *  LOG:
 *  LOG: Revision 9.19  2008/07/17 14:04:14  ssingh
 *  LOG: Warning removal for Solaris Compilation
 *  LOG:
 *  LOG: Revision 9.18  2008/07/16 11:15:08  skatta
 *  LOG: Fix for issue #1052 - when SNMM messages are received, SG discards DUNA,DAVA,DRST and DUPU messages and ASP discards DAUD message
 *  LOG:
 *  LOG: Revision 9.17  2008/06/29 15:09:53  skatta
 *  LOG: M3UA header version is filled with UAL_GL_VERSION
 *  LOG:
 *  LOG: Revision 9.16  2008/06/20 09:36:05  mshanmugam
 *  LOG: Accelero CGI Phase I: D0030, D0040, D0070, D0100-D0140
 *  LOG:
 *  LOG: Revision 9.15  2008/05/09 12:11:39  skatta
 *  LOG: Fix for issue #911 in whizible
 *  LOG:
 *  LOG: Revision 9.14  2008/05/08 13:15:57  kramesh
 *  LOG: Whizipble bug 882 Fixed. DAUD message handle properly.
 *  LOG: Whizipble bug 882 Fixed. Cores after recieving DAUD message & Handling of DRST.
 *  LOG:
 *  LOG: Revision 9.13  2008/05/01 14:54:31  kramesh
 *  LOG: Reverted back changes for Personeta issue 1714.
 *  LOG: Propagated TCS issue 1033. Sigtran 4 association issue.
 *  LOG:
 *  LOG: Revision 9.12  2008/04/22 10:05:50  kramesh
 *  LOG: Propagated TCS issue 1095. Pause not propagated After 4 Duna sent to each
 *  LOG: association from STP
 *  LOG: Propagated Personeta issue 1714. Sigtran Solaris10 message send failure.
 *  LOG:
 *  LOG: Revision 9.11  2008/04/15 05:03:14  kramesh
 *  LOG: Merged Persistent Branch Changes to current.
 *  LOG:
 *  LOG: Revision 9.10.2.12  2007/07/06 07:20:39  pspl
 *  LOG: Added check for dest->status to be AVAILABLE/UNAVAILABLE to enable Resume
 *  LOG: Callback to work (PSPL/Rajnikant)
 *  LOG:
 *  LOG: Revision 9.10.2.11  2007/06/26 10:35:26  pspl
 *  LOG: (PSPL, abhijeet) trid added as an extra added to allow checking of ASP state
 *  LOG:
 *  LOG: Revision 9.10.2.10  2007/06/22 11:50:35  pspl
 *  LOG: Auditing support for receipt of SSNM message (SCON/DUNA/DRST)
 *  LOG:
 *  LOG: Revision 9.10.2.9  2007/05/23 12:31:05  pspl
 *  LOG: Corrected Log level of message from WARNING to DEBUG(Manish)
 *  LOG:
 *  LOG: Revision 9.10.2.8  2007/05/18 14:46:46  yranade
 *  LOG: Fix to avoid crash when mi_start or ma_start command on SIGTRAN
 *  LOG: Warning removal.
 *  LOG:
 *  LOG: Revision 9.10.2.7  2007/05/02 08:30:00  pspl
 *  LOG: (PSPL, abhijeet) misc review comment changes
 *  LOG:
 *  LOG: Revision 9.10.2.6  2007/04/30 11:19:31  pspl
 *  LOG: (PSPL, abhijeet) added alarm (4039) for invalid msgType
 *  LOG:
 *  LOG: Revision 9.10.2.5  2007/04/26 10:01:55  pspl
 *  LOG: (PSPL, abhijeet) removal of extra error being sent and updating Peg count
 *  LOG:
 *  LOG: Revision 9.10.2.4  2007/04/26 06:52:51  pspl
 *  LOG: (PSPL, abhijeet)
 *  LOG: - added msg param validity checking,
 *  LOG:   CheckParam()- checks params for a particulaer msg
 *  LOG:   CheckParamLength() - checks for fixed length and max length
 *  LOG:                        for corresponding params
 *  LOG: - mandatory and optional param count checks also have been added
 *  LOG: - DecodeMsg errors are translated into sending an error
 *  LOG:   back to the remote site (using a macro)
 *  LOG:
 *  LOG: Revision 9.10.2.3  2007/04/24 12:50:48  pspl
 *  LOG: 1. Modified the macro(M3UA_FLIP_IE_PC) to flip point code for itu.
 *  LOG: 2. Added a defensive check for size of MTP3_MSG_USER_DATA
 *  LOG:
 *  LOG: Revision 9.10.2.2  2007/04/05 14:38:10  pspl
 *  LOG: - Peg counter increments replaced by a function call UAL_Incrementxxxx()
 *  LOG: - checks for MGMT messages on stream ID '0'
 *  LOG: - M3UA_To_MTP3_Codec() structure changed to be more redable.
 *  LOG: - other misc changes
 *  LOG:
 *  LOG: Revision 9.10.2.1  2007/03/29 05:29:04  pspl
 *  LOG: Rahul, minor m3ua changes
 *  LOG:
 *  LOG: Revision 9.10  2007/01/10 11:15:01  yranade
 *  LOG: Merge changes from 6.5.3 and Lucent branches
 *  LOG:
 *  LOG: Revision 9.9  2005/12/09 20:01:17  cbashyam
 *  LOG: Bug fixes for Bugs:2479 and 2480
 *  LOG: Added new M3UA alarms
 *  LOG:
 *  LOG: Revision 9.8  2005/12/09 03:52:25  clin
 *  LOG: Add SSNM pegs for M3UA.
 *  LOG:
 *  LOG: Revision 9.7  2005/11/09 16:50:32  cbashyam
 *  LOG: Fix for Bug ID : 2456
 *  LOG: Removed the if condition that checks if dbclass != NULL and
 *  LOG: included the line DBC_AddDoCommand(M3UA_Console);
 *  LOG: without the if condition
 *  LOG:
 *  LOG: Revision 9.6  2005/07/04 02:49:56  randresol
 *  LOG: M3UA Enhancement for Accelero Rel 6.5
 *  LOG:
 *  LOG: Revision 9.5  2005/05/06 09:36:38  mmanikandan
 *  LOG: PR6.5.1 Validation Bug(1773) Fix.
 *  LOG:
 *  LOG: Revision 9.4  2005/05/05 05:53:24  adutta
 *  LOG: Fix for #1795
 *  LOG:
 *  LOG: Revision 9.3  2005/04/06 06:06:52  adutta
 *  LOG: Fix for Bug# 1670/1557
 *  LOG:
 *  LOG: Revision 9.2  2005/04/01 12:01:22  ssingh
 *  LOG: Sigtran related Bug Fix Propagation to PR6.5/current.
 *  LOG:
 *  LOG: Revision 9.1  2005/03/23 12:52:17  cvsadmin
 *  LOG: Begin PR6.5
 *  LOG:
 *  LOG: Revision 8.2  2005/03/21 13:50:18  cvsadmin
 *  LOG: PR6.4.2 Source Propagated to Current
 *  LOG:
 *  LOG: Revision 7.1.4.14.2.4.4.10  2005/02/22 11:22:58  adutta
 *  LOG: Fix for Bug#1557
 *  LOG:
 *  LOG: Revision 7.1.4.14.2.4.4.9  2005/02/21 12:02:16  dsatish
 *  LOG: changes propagated from KINETO BRANCH(Revision 7.1.4.6.2.15/16)
 *  LOG: DAUD support.
 *  LOG:
 *  LOG: Revision 7.1.4.14.2.4.4.8  2005/02/09 10:54:42  csireesh
 *  LOG: Validation Bug Fix(Alarms).
 *  LOG:
 *  LOG: Revision 7.1.4.14.2.4.4.7  2005/01/11 11:48:45  craghavendra
 *  LOG: Syslog Enhancements.
 *  LOG:
 *  LOG: Revision 7.1.4.14.2.4.4.6  2005/01/04 15:23:36  sbabu
 *  LOG: M3UA OAM changes
 *  LOG:
 *  LOG: Revision 7.1.4.14.2.4.4.5  2004/12/25 10:48:58  ssingh
 *  LOG: Fix for Bug No #1332
 *  LOG:
 *  LOG: Revision 7.1.4.14.2.4.4.4  2004/12/16 02:15:06  randresol
 *  LOG: Add JAPAN variant implementation
 *  LOG:
 *  LOG: Revision 7.1.4.14.2.4.4.3  2004/12/15 16:31:40  dsatish
 *  LOG: typo corrected
 *  LOG:
 *  LOG: Revision 7.1.4.14.2.4.4.2  2004/12/15 12:10:32  asingh
 *  LOG: separate traces for M3UA
 *  LOG:
 *  LOG: Revision 7.1.4.14.2.4.4.1  2004/12/09 15:31:16  snagesh
 *  LOG: Modifications for Chinese variant
 *  LOG:
 *  LOG: Revision 7.1.4.14.2.4  2004/10/06 09:16:16  mmanikandan
 *  LOG: Support for windows build.
 *  LOG:
 *  LOG: Revision 7.1.4.14.2.3  2004/10/06 08:44:03  ssingh
 *  LOG: Modified SLS setting for MTP3_To_M3UA based on avaliable outstreams.
 *  LOG:
 *  LOG: Revision 7.1.4.14.2.2  2004/09/29 09:57:41  asingh
 *  LOG: Changes for linux ES 30 operating system; compilation issue.
 *  LOG:
 *  LOG: Revision 7.1.4.14.2.1  2004/05/03 13:21:30  ssingh
 *  LOG: Fixes for 775/776/777/778/779/804/805 bugs.
 *  LOG:
 *  LOG: Revision 7.1.4.14  2003/11/17 21:42:06  hcho
 *  LOG: Missing pc for resume callback.
 *  LOG:
 *  LOG: Revision 7.1.4.13  2003/11/17 21:31:18  hcho
 *  LOG: Payload shall not send on stream 0.
 *  LOG:
 *  LOG: Revision 7.1.4.12  2003/10/21 14:33:29  lbana
 *  LOG: fix long name issues in routing notification
 *  LOG:
 *  LOG: Revision 7.1.4.11  2003/10/14 20:47:55  lbana
 *  LOG: TCS bug fixes and removed begin and end tags for each fix.
 *  LOG:
 *  LOG: Revision 7.1.4.10  2003/09/21 14:11:34  lbana
 *  LOG: send error for invalid param in DUPU
 *  LOG:
 *  LOG: Revision 7.1.4.9  2003/09/21 13:27:38  lbana
 *  LOG: add DRST tag
 *  LOG:
 *  LOG: Revision 7.1.4.8  2003/09/20 20:13:24  lbana
 *  LOG: add mtp3 status feature for DUPU and SCON
 *  LOG:
 *  LOG: Revision 7.1.4.7  2003/09/19 05:24:36  lbana
 *  LOG: send error message in case if we get invalid version or missing
 *  LOG: mandatory param.
 *  LOG:
 *  LOG: Revision 7.1.4.6  2003/09/11 01:13:40  lbana
 *  LOG: code clean up.
 *  LOG:
 *  LOG: Revision 7.1.4.5  2003/09/11 00:43:59  lbana
 *  LOG: Code reorganized for Pause/Resumes and tested config with 2linksets
 *  LOG:
 *  LOG: Revision 7.1.4.4  2003/08/04 23:34:07  hcho
 *  LOG: Fixed Pause/Resume reverse placed.
 *  LOG:
 *  LOG: Revision 7.1.4.3  2003/07/11 21:12:52  labuser
 *  LOG: DUNA/DAVA functionality is added.
 *  LOG:
 *  LOG: Revision 7.1.4.2  2003/04/04 16:12:54  pmandal
 *  LOG: Finish porting.
 *  LOG:
 *  LOG: Revision 7.1.4.1  2003/04/04 16:02:58  lbana
 *  LOG: fix ansi point code bug
 *  LOG:
 *  LOG: Revision 7.1  2002/08/26 22:09:22  mmiers
 *  LOG: Begin PR6.2
 *  LOG:
 *  LOG: Revision 6.7  2002/08/15 19:41:54  mmiers
 *  LOG: Warning removal
 *  LOG:
 *  LOG: Revision 6.6  2002/08/05 15:46:05  labuser
 *  LOG: Plug memory leak. (clin)
 *  LOG:
 *  LOG: Revision 6.5  2002/07/03 19:54:53  mmiers
 *  LOG: China fixes
 *  LOG:
 *  LOG: Revision 6.4  2002/06/12 16:19:15  lbana
 *  LOG: Take message out of MTP3 too.
 *  LOG:
 *  LOG: Revision 6.3  2002/05/20 16:19:13  lbana
 *  LOG: have to include sccp/include dir in makefile.
 *  LOG:
 *  LOG: Revision 6.2  2002/05/20 16:02:50  lbana
 *  LOG: m3ua ver 10 codec
 *  LOG:
 *  LOG: Revision 1.1.2.14  2002/04/05 20:42:38  lbana
 *  LOG: flip 2 bytes of point code in codec
 *  LOG:
 *  LOG: Revision 1.1.2.13  2002/04/04 17:07:05  lbana
 *  LOG: Bug fix for network indicator
 *  LOG:
 *  LOG: Revision 1.1.2.12  2002/04/02 17:45:01  lbana
 *  LOG: bug fix in setting sio
 *  LOG:
 *  LOG: Revision 1.1.2.11  2002/03/26 23:09:03  omayor
 *  LOG: Bug in getting routing context.
 *  LOG:
 *  LOG: Revision 1.1.2.10  2002/03/12 21:50:06  omayor
 *  LOG: Routing Context now in Data for V10.
 *  LOG:
 *  LOG: Revision 1.1.2.9  2002/03/12 21:03:38  lbana
 *  LOG: changed Codec signature
 *  LOG:
 *  LOG: Revision 1.1.2.8  2002/03/05 20:58:17  omayor
 *  LOG: fixes provided in Bakeoff
 *  LOG:
 *  LOG: Revision 1.1.2.7  2002/02/21 20:23:05  omayor
 *  LOG: More on STATUS - SCON.
 *  LOG:
 *  LOG: Revision 1.1.2.6  2002/02/15 00:13:06  omayor
 *  LOG: Add some ERROR Traces.
 *  LOG:
 *  LOG: Revision 1.1.2.5  2002/02/13 22:29:31  omayor
 *  LOG: Typo in message class selection.
 *  LOG:
 *  LOG: Revision 1.1.2.4  2002/02/04 16:46:39  lbana
 *  LOG: include ual.h file
 *  LOG:
 *  LOG: Revision 1.1.2.3  2002/01/30 19:51:49  lbana
 *  LOG: added printf event func
 *  LOG:
 *  LOG: Revision 1.1.2.2  2002/01/30 16:59:13  labuser
 *  LOG: Fix one bug in M3UA to MTP3 conversion (wrong msg type for MGNT).
 *  LOG:
 *  LOG: Revision 1.1.2.1  2002/01/30 16:47:00  labuser
 *  LOG: M3UA V10 Codec.
 *  LOG:
 *                 
 ****************************************************************************/
/*#include <netinet/in.h>*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <its.h>
#include <its_assertion.h>

#include <m3ua.h>

#include <its_sockets.h>
#include <its_transports.h>
#include <its_route_rwlock.h>
#include <its_trace.h>
#include <its_sctp_trans.h>

#include <its_ual.h>
#include <its_alarm.h>

#include <ual_intern.h>

#include <engine.h>

#if defined (CCITT)
#include <itu/sccp.h>
#endif

#define CHECK_M3UA_DECODEMSG_ERROR(transMgr, retVal) {                                   \
    switch((retVal))                                                                     \
    {                                                                                    \
        case UAL_ERR_UNEXP_PARAM:                                                        \
            Send_Parm_ERROR(transMgr, UAL_ERR_UNEXP_PARAM, NULL);                        \
    	    UAL_IncrementMIBStats(TRANSPORT_INSTANCE(transMgr), UAL_PEG_ERR_SENT_ID);    \
            break;                                                                       \
        case UAL_ERR_PARM_FIELD_ERR:                                                     \
            Send_Parm_ERROR(transMgr, UAL_ERR_PARM_FIELD_ERR, NULL);                     \
    	    UAL_IncrementMIBStats(TRANSPORT_INSTANCE(transMgr), UAL_PEG_ERR_SENT_ID);    \
            break;                                                                       \
        case ITS_EOVERFLOW:                                                              \
            Send_Parm_ERROR(transMgr, UAL_ERR_PROT_ERROR, NULL);                         \
    	    UAL_IncrementMIBStats(TRANSPORT_INSTANCE(transMgr), UAL_PEG_ERR_SENT_ID);    \
            break;                                                                       \
        case ITS_EMISSMAND:                                                              \
            Send_Parm_ERROR(transMgr, UAL_ERR_MISSING_PARAM, NULL);                      \
    	    UAL_IncrementMIBStats(TRANSPORT_INSTANCE(transMgr), UAL_PEG_ERR_SENT_ID);    \
            break;                                                                       \
        case ITS_SUCCESS:                                                                \
            break;                                                                       \
        default:                                                                         \
            M3UA_ERROR(("Problem in checking return value from of M3UA_DecodeMsg()\n")); \
            break;                                                                       \
    }                                                                                    \
}    

/*
 * These are required because NA and RC are optional
 * in DUNA/DAVA/SCON packet.
 */
#define M3UA_SIO_0      0x00
#define M3UA_SIO_40     0x40
#define M3UA_UNUSED_SIO 0xFF
#define M3UA_DATA_HDR_LEN 12
UALDLLAPI extern CALLBACK_Manager*   __UAL_MgntCallBack;

static ITS_BOOLEAN      started = ITS_FALSE;

static void InitTraceSettings(TRANSPORT_Control*);

static TRACE_OutputInitializer fileCritTrace =
{
    M3UA_FILE_STRING,
    ITS_TRUE,
    M3UA_TRACE_CRITICAL_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileErrTrace =
{
    M3UA_FILE_STRING,
    ITS_TRUE,
    M3UA_TRACE_ERROR_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileWarnTrace =
{
    M3UA_FILE_STRING,
    ITS_TRUE,
    M3UA_TRACE_WARNING_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileDebugTrace =
{
    M3UA_FILE_STRING,
    ITS_TRUE,
    M3UA_TRACE_DEBUG_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer stdoutTrace =
{
    M3UA_STDOUT_STRING,
    ITS_TRUE,
    NULL,
    TRACE_TO_DISPLAY
};

static TRACE_OutputInitializer syslogTrace =
{
    M3UA_SYSLOG_STRING,
    ITS_TRUE,
    NULL,
#if defined(WIN32)
    TRACE_TO_NT_EVENT_LOG
#else
    TRACE_TO_SYSLOG
#endif
};

static TRACE_LevelInitializer M3UA_TraceMap[] =
{
    {M3UA_CRITICAL_STRING, ITS_TRUE,  3, { &stdoutTrace, &fileCritTrace, &syslogTrace  } },
    {M3UA_ERROR_STRING,    ITS_TRUE,  3, { &stdoutTrace, &fileErrTrace, &syslogTrace   } },
    {M3UA_WARNING_STRING,  ITS_TRUE,  3, { &stdoutTrace, &fileWarnTrace, &syslogTrace  } },
    {M3UA_DEBUG_STRING,    ITS_FALSE, 3, { &stdoutTrace, &fileDebugTrace, &syslogTrace } }
};

TRACE_Data* M3UA_TraceData = NULL;

static void
PauseCallback(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData);
static void
ResumeCallback(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData);
static void
StatusCallback(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData);

void M3UA_Alarm(int which, const char *file, const int line, char *format, ...);

int M3UA_Commit(FILE* fp);


/*
 * DATA
 */
static ITS_USHORT    dataMArgs[] =
{
    M3UA_PRM_DATA
};

static ITS_USHORT    dataOArgs[] =
{
    M3UA_PRM_NET_APP,
    M3UA_PRM_ROUT_CTX,
    M3UA_PRM_COR_ID
};


M3UA_MSG_DESC M3UA_DATA_Desc =
{
    dataMArgs, sizeof(dataMArgs) / sizeof(ITS_USHORT),
    dataOArgs, sizeof(dataOArgs) / sizeof(ITS_USHORT)
};


/*
 * DUNA 
 */
static ITS_USHORT    dunaMArgs[] =
{
    M3UA_PRM_AFFECTED_PC
};

static ITS_USHORT    dunaOArgs[] =
{
    M3UA_PRM_NET_APP,
    M3UA_PRM_ROUT_CTX,
    M3UA_PRM_INFO_STR
};

M3UA_MSG_DESC M3UA_DUNA_Desc =
{
    dunaMArgs, sizeof(dunaMArgs) / sizeof(ITS_USHORT),
    dunaOArgs, sizeof(dunaOArgs) / sizeof(ITS_USHORT)
};


/*
 * DAVA 
 */
static ITS_USHORT    davaMArgs[] =
{
    M3UA_PRM_AFFECTED_PC
};

static ITS_USHORT    davaOArgs[] =
{
    M3UA_PRM_NET_APP,
    M3UA_PRM_ROUT_CTX,
    M3UA_PRM_INFO_STR
};

M3UA_MSG_DESC M3UA_DAVA_Desc =
{
    davaMArgs, sizeof(davaMArgs) / sizeof(ITS_USHORT),
    davaOArgs, sizeof(davaOArgs) / sizeof(ITS_USHORT)
};

/*
 * SCON 
 */
static ITS_USHORT    sconMArgs[] =
{
    M3UA_PRM_AFFECTED_PC
};

static ITS_USHORT    sconOArgs[] =
{
    M3UA_PRM_NET_APP,
    M3UA_PRM_CONGEST_LEVEL,
    M3UA_PRM_INFO_STR,
    M3UA_PRM_CONCERN_PC,
    M3UA_PRM_ROUT_CTX
};


M3UA_MSG_DESC M3UA_SCON_Desc =
{
    sconMArgs, sizeof(sconMArgs) / sizeof(ITS_USHORT),
    sconOArgs, sizeof(sconOArgs) / sizeof(ITS_USHORT)
};


/*
 * DUPU 
 */
static ITS_USHORT    dupuMArgs[] =
{
    M3UA_PRM_AFFECTED_PC,
    M3UA_PRM_CAUSE_USER
};

static ITS_USHORT    dupuOArgs[] =
{
    M3UA_PRM_NET_APP,
    M3UA_PRM_INFO_STR,
    M3UA_PRM_ROUT_CTX
};

M3UA_MSG_DESC M3UA_DUPU_Desc =
{
    dupuMArgs, sizeof(dupuMArgs) / sizeof(ITS_USHORT),
    dupuOArgs, sizeof(dupuOArgs) / sizeof(ITS_USHORT)
};

/*
 * DAUD
 */
static ITS_USHORT    daudMArgs[] =
{
    M3UA_PRM_AFFECTED_PC
};

static ITS_USHORT    daudOArgs[] =
{
    M3UA_PRM_NET_APP,
    M3UA_PRM_ROUT_CTX,
    M3UA_PRM_INFO_STR
};

M3UA_MSG_DESC M3UA_DAUD_Desc =
{
    daudMArgs, sizeof(daudMArgs) / sizeof(ITS_USHORT),
    daudOArgs, sizeof(daudOArgs) / sizeof(ITS_USHORT)
};

/*
 * ERR
 */
static ITS_USHORT    errMArgs[] =
{
    UAL_PRM_ERROR_CODE
};

static ITS_USHORT    errOArgs[] =
{
    M3UA_PRM_INFO_STR,
    M3UA_PRM_ROUT_CTX,
    M3UA_PRM_NET_APP,
    M3UA_PRM_AFFECTED_PC
};

M3UA_MSG_DESC M3UA_ERROR_Desc =
{
    errMArgs, sizeof(errMArgs) / sizeof(ITS_USHORT),
    errOArgs, sizeof(errOArgs) / sizeof(ITS_USHORT)
};


/*
 * application server process maintenance messages
 */

int
M3UA_GetPadding(int size)
{
    if ((size % 4) == 0)
    {
        return 0;
    }
    else
    {
        return 4 - (size % 4);
    }
}


static int
FindMatch(ITS_POINTER entry, void *in, void *out)
{
    ROUTE_Info *rinfo = (ROUTE_Info *)entry;
    ITS_UINT pc = *(ITS_UINT*)in;
    ITS_BOOLEAN *concerned = (ITS_BOOLEAN*)out;

    if (rinfo && (rinfo->basic.dpc == pc)
              && (rinfo->basic.type == REMOTE_ROUTE))
    {
        *concerned = ITS_TRUE;
        return (-1); /* stop iterations */
    }
    return (ITS_SUCCESS);
}


ITS_BOOLEAN
M3UA_IsConcernedPC(ITS_UINT pc)
{
    ITS_BOOLEAN concerned = ITS_FALSE;

    if (ROUTE_LockTable() != ITS_SUCCESS)
    {
        return ITS_FALSE;
    }

    DSM_TableIterate(DSM_RoutingFtGroupId, DSM_TABLE_ROUTES,
                     &pc, &concerned, FindMatch);

    ROUTE_UnlockTable();

    return concerned;
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This is a helper function that prints a M3UA IE element.
 *     
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      IE - pointer to the M3UA_IE to be displayed.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      void
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
void
M3UA_PrintM3UA_IES(ITS_M3UA_IE *IE)
{
    if (IE != NULL)
    {
        int i;

        printf("------------ M3UA_IE Begin ------------\n");
        printf("Prarmeter Type: 0x%04x \n", IE->param_id);
        printf("Parameter len : 0x%04x \n", IE->param_length);

        for (i = 0; i < IE->param_length; i++)
        {
            printf("0x%02x ", *((unsigned char *)&(IE->param_data) + i));
        }
        printf("\n------------ M3UA_IE End ------------\n");
    }
    else
    {
        printf("IE * is NULL \n");
    }

    return;
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This is a helper function that find a M3UA IE element.
 *     
 *  Input Parameters:
 *      ies - pointer to th first element of an array of ITS_M3UA_IE
 *      ieCount - Number of ies in the array
 *      paramId - ie Id of the searched IE
 *
 *  Input/Output Parameters:
 *      None
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      pointer to the IE if found, else NULL
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
M3UADLLAPI ITS_M3UA_IE*
M3UA_FindM3UAIE(ITS_M3UA_IE *ies, int ieCount, ITS_USHORT paramId)
{
    int i;
    
    for (i=0; i < ieCount; i++)
    {
        if (ies[i].param_id == paramId)
        {
            return &ies[i];
        }
    }

    return NULL;
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is used to change the common message header from host
 *      to network format.
 *     
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      msgHdr - pointer to the message common message header.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      void
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
void
M3UA_HComHdrToN(M3UA_MSG_HDR *msgHdr)
{
    msgHdr->msgLen = SOCK_HToNL(msgHdr->msgLen);

    return;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is used to convert the common message header from
 *      network to host format.
 *     
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      msgHdr - pointer to the message common message header.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
void
M3UA_NComHdrToH(M3UA_MSG_HDR *msgHdr)
{

    msgHdr->msgLen = SOCK_NToHL(msgHdr->msgLen);

    return;
}



/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is used to change an ITS_M3UA_IE array to the network 
 *      format
 *     
 *  Input Parameters:
 *      ieCount - number of element in the array.
 *
 *  Input/Output Parameters:
 *      ies - pointer to the first element of the array.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
void
M3UA_Hm3uaIESToN(ITS_M3UA_IE *ies, int ieCount)
{
    int i = 0;

    for (i=0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
        case M3UA_PRM_MSG_HDR:

            ies[i].param_data.msgHeader.msgLen = 
                              SOCK_HToNL(ies[i].param_data.msgHeader.msgLen);
            
            break;

        case M3UA_PRM_CAUSE_USER:

            ies[i].param_data.causeUsr.cause = 
                              SOCK_HToNS(ies[i].param_data.causeUsr.cause);

            ies[i].param_data.causeUsr.user = 
                              SOCK_HToNS(ies[i].param_data.causeUsr.user);
            
            break;

        case M3UA_PRM_CONGEST_LEVEL:

            ies[i].param_data.congestion.level = 
                              SOCK_HToNL(ies[i].param_data.congestion.level);

            break;
        
        }
    }

    return;
}



/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is used to change an ITS_M3UA_IE array to the HOST 
 *      format.
 *     
 *  Input Parameters:
 *      ieCount - number of element in the array.
 *
 *  Input/Output Parameters:
 *      ies - pointer to the first element of the array.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
void
M3UA_Nm3uaIESToH(ITS_M3UA_IE *ies, int ieCount)
{
    int i = 0;

    for (i=0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
        case M3UA_PRM_MSG_HDR:

            ies[i].param_data.msgHeader.msgLen = 
                              SOCK_NToHL(ies[i].param_data.msgHeader.msgLen);
            
            break;

        case M3UA_PRM_CAUSE_USER:

            ies[i].param_data.causeUsr.cause = 
                              SOCK_NToHS(ies[i].param_data.causeUsr.cause);

            ies[i].param_data.causeUsr.user = 
                              SOCK_NToHS(ies[i].param_data.causeUsr.user);
            
            break;

        case M3UA_PRM_CONGEST_LEVEL:

            ies[i].param_data.congestion.level = 
                              SOCK_NToHL(ies[i].param_data.congestion.level);

            break;
        
        }
    }

    return;
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is used to encode a M3UA message from a given array of
 *      M3UA IES.
 *     
 *  Input Parameters:
 *      ies - pointer to the first element of IES array (common msg header).
 *      ieCount - number of IES in the array.
 *      desc - pointer to M3UA message descriptor.
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *      event - pointer to ITS_EVENT containing the built M3UA message.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
M3UADLLAPI int
M3UA_EncodeMsg(ITS_M3UA_IE *ies, int ieCount,ITS_EVENT *event,
               M3UA_MSG_DESC* desc)
{
    int i, j, offset, evoffset;
    ITS_M3UA_IE* ieRef[ITS_MAX_M3UA_IES];
    ITS_USHORT *margs = desc->mParam;
    int nmargs = desc->nmParam;
    ITS_USHORT *oargs = desc->oParam;
    int noargs = desc->noParam;
    ITS_USHORT len = 0, padding = 0;
    ITS_BOOLEAN sawOpt = ITS_FALSE;

    assert(event != NULL);

    M3UA_DEBUG(("M3UA_EncodeMsg: \n"));

    /* sanity */
    if (ieCount > ITS_MAX_M3UA_IES)
    {
        M3UA_Alarm(4041, __FILE__, __LINE__, NULL);
        return (ITS_EOVERFLOW);
    }
     

    /* change the params to network format */
    M3UA_Hm3uaIESToN(ies, ieCount);

    /* 
     * The first step is to use a temporary array of IES* to
     * store ptrs to the message parameters in the following order
     * - the common header
     * - the madatory parameters
     * - the optional parameters if any
     * In the meanwhile we can check if all mandatory parameters are 
     * present for sanity purposes
     */

    /*
     * The first IE int the array should be the common message header
     * this is common to all M3UA messages
     */
    if(ies[0].param_id != M3UA_PRM_MSG_HDR)
    {
        M3UA_Alarm(4041, __FILE__, __LINE__, NULL);
        return (ITS_EINVALIDARGS);
    }

    ieRef[0] = ies;

    /* start at one, 0 is the common msg header */
    offset = 1;

    /* find the mandatory parameters */
    for (i = 0; i < nmargs; i++)
    {
        for (j = 1; j < ieCount; j++) /* we can start at 1, 0 is message header */
        {
            if (ies[j].param_id == margs[i])
            {
                ieRef[offset] = &ies[j];
                offset++;
                break;
            }
        }

        /* is it missing? */
        if (j == ieCount)
        {
            M3UA_Alarm(4041, __FILE__, __LINE__, NULL);
            return (ITS_EMISSMAND);
        }
    }
    
    /* find the optionals */
    for (i = 0; i < noargs; i++)
    {
        for (j = 0; j < ieCount; j++)
        {
            if (ies[j].param_id == oargs[i])
            {
                ieRef[offset] = &ies[j];
                offset++;
                sawOpt = ITS_TRUE;
                break;
            }
        }
        /* if missing, that's ok */
    }

    /* skip extras */
    while (offset <= ieCount)   /* we use <= because of the common 
                                   message header offset starts at 1 */
    {
        ieRef[offset] = NULL;
        offset++;
    }

    evoffset = sizeof(M3UA_MSG_HDR);

    /* copy in the mandatories */
    for (i = 1; i <= nmargs; i++)
    {
        /* cpy param id */
        ieRef[i]->param_id = SOCK_HToNS(ieRef[i]->param_id);

        memcpy(&event->data[evoffset], &ieRef[i]->param_id, 
               sizeof(ITS_USHORT));
        evoffset += 2;
        /* cpy param len */
        len = ieRef[i]->param_length;
        padding = M3UA_GetPadding(len);
        ieRef[i]->param_length = SOCK_HToNS((ITS_USHORT)(len + 4));

        memcpy(&event->data[evoffset], &ieRef[i]->param_length, 
               sizeof(ITS_USHORT));

        evoffset += 2;

        memset(&event->data[evoffset], 0, (len + padding)); 
        memcpy(&event->data[evoffset], &ieRef[i]->param_data, len);
  
        evoffset += (len + padding);
    }

    /* copy in the optionals */

    for (i = 1; i <= noargs; i++)
    {
        if (ieRef[i + nmargs] == NULL )
        {
            break;
        }

        /* cpy param id */
        ieRef[i + nmargs]->param_id = SOCK_HToNS(ieRef[i+nmargs]->param_id);


        memcpy(&event->data[evoffset], &ieRef[i+nmargs]->param_id, 
               sizeof(ITS_USHORT));
        evoffset += 2;
        /* cpy param len */
        len = ieRef[i+nmargs]->param_length;
        padding = M3UA_GetPadding(len);
        ieRef[i + nmargs]->param_length = 
                                 SOCK_HToNS((ITS_USHORT)(len + 4));


        memcpy(&event->data[evoffset], &ieRef[i+nmargs]->param_length, 
               sizeof(ITS_USHORT));

        evoffset += 2;


        memset(&event->data[evoffset], 0, (len + padding));
        memcpy(&event->data[evoffset], &ieRef[i+nmargs]->param_data, len);
            
        evoffset += (len + padding);
    }

    /* set final length */
    event->len = evoffset;

    /* take care of the message length */
    ieRef[0]->param_data.msgHeader.msgLen = SOCK_HToNL(event->len);

    /* copy in the message header with updated message pointers */
    memcpy(&event->data[0], &ieRef[0]->param_data, sizeof(M3UA_MSG_HDR));

    /* WHAT ABOUT THE EVENT SOURCE -> left to the user to fill in */

    return (ITS_SUCCESS);

}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is used to check if param_id passed is valid for message. 
 *
 *  Input Parameters:
 *            param_id - Parameter ID
 *             desc - pointer to the message descriptor.
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      0 - Invalid Prameter,(Param_id not matching with message description)
 *      1 - Mandatory Parameter Found
 *      2 - Optional Paramter Found
 *  Notes:
 *      This function is used internally that is not directly by the user.
 *
 *  See Also:
 ******************************************************************************/
ITS_INT
M3UA_CheckParam(ITS_USHORT param_id,M3UA_MSG_DESC *desc)
{
    ITS_INT i=0;
    
    /*check for Mandatory Parameter*/
    for(i=0; i < desc->nmParam; i++)
    {
        if(desc->mParam[i] == param_id)
        {
            return MANDATORY_PARAMETER;     
        }
    }
    
    /*check for Optional Parameter*/
    for(i=0; i < desc->noParam; i++)
    {
        if(desc->oParam[i] == param_id)
        {
            return OPTIONAL_PARAMETER;
        }
    } 

    /*If Parameter id not matches to Mandatory and Optional*/
   return PARAMETER_NOT_FOUND;
}



/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is used to decode a M3UA message to an array of M3UA IES.
 *     
 *  Input Parameters:
 *      ev - pointer to ITS_EVENT containing the M3UA message to be decoded.
 *      desc - pointer to the message descriptor.
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *      ies - pointer to the array of IES where the message is decoded.
 *      ieCount - number of decode IES in the array.
 *
 *  Return Value:
 *      ITS_SUCCESS - any other return value would indicate an IntelliSS7 
 *                    error has occured.
 *
 *  Notes:
 *      This function is used internally that is not directly by the user.
 *
 *  See Also:
 *      M3UA_EncodeMsg().
 *
 ******************************************************************************/
M3UADLLAPI int
M3UA_DecodeMsg(ITS_M3UA_IE *ies, int *ieCount, ITS_EVENT *ev,
              M3UA_MSG_DESC *desc)
{
    ITS_USHORT msgLen = ev->len;
    int evOffset = 0;
    ITS_M3UA_IE *ieRef = ies;

    /* to check madetory and optional parameters */
    ITS_INT mParamCount=0,oParamCount=0;
    ITS_INT retVal = 0;
    *ieCount = 0;

    M3UA_DEBUG(("M3UA_DecodeMsg: \n"));

    /* take care of the common msg header */
    ies[0].param_id = M3UA_PRM_MSG_HDR;
    ies[0].param_length = sizeof(M3UA_MSG_HDR);
    memcpy(&ies[0].param_data.msgHeader, &ev->data[evOffset], 
           sizeof(M3UA_MSG_HDR));

    M3UA_NComHdrToH(&ies[0].param_data.msgHeader);

    (*ieCount)++;
    ies++;
    evOffset += sizeof(M3UA_MSG_HDR);

    /* Getting all Parametrs from event buffer */
    while (evOffset < msgLen)
    {
        ies[0].param_id = ev->data[evOffset] << 8 | 
                          ev->data[evOffset + 1];
        evOffset += 2;
        
        /* Check if parameter is valid for this message and Update check list */
        retVal= M3UA_CheckParam(ies[0].param_id,desc);
        if (retVal == MANDATORY_PARAMETER)
	{
            mParamCount++;
        }
        else if (retVal == OPTIONAL_PARAMETER)
        {
            /*If required we can add check for number of 
              optional Parameters present (oParamCount) */
            oParamCount++;
        }
        else
        {
            M3UA_ERROR(("Unexpected Parameter=%0x:  Message dropped\n",(ies[0].param_id)));
            M3UA_Alarm(4040, __FILE__, __LINE__, NULL);
            return (UAL_ERR_UNEXP_PARAM);
        } 

        /* param_length has to be minimum of 4 bytes,
	 * param_id(2bytes) + param_length (2 bytes)
	 */
	ies[0].param_length = (ev->data[evOffset] << 8 | 
                              ev->data[evOffset + 1]) - 4;

        evOffset += 2;
        
        /* check for valid Parameter length */
        if(UAL_CheckParamLength(ies[0].param_id,ies[0].param_length) == ITS_FALSE)
        {
            M3UA_ERROR(("Invalid Parameter Length for ParamID=%0x: : Message dropped\n",ies[0].param_id));
            M3UA_Alarm(4040, __FILE__, __LINE__, NULL);
            return (UAL_ERR_PARM_FIELD_ERR);
        }

        if ((ies[0].param_length < msgLen) && (evOffset < ev->len))
        { 
            memcpy(&ies[0].param_data.data, &ev->data[evOffset], 
                   ies[0].param_length);
             
            evOffset += ies[0].param_length + M3UA_GetPadding(ies[0].param_length); 

            (*ieCount)++;

            if (*ieCount > ITS_MAX_M3UA_IES)
            {
                M3UA_Alarm(4040, __FILE__, __LINE__, NULL);
                return (ITS_EOVERFLOW);
            }

            ies++;
        }
        else
        {
            M3UA_Alarm(4040, __FILE__, __LINE__, NULL);
            return ITS_EOVERFLOW;
        }
    }
    
    if(mParamCount > desc->nmParam)
    {
        M3UA_WARNING(("One or more mandatory parameter(s) repeated!!"));
    }
    /* check for all the Mandatory Parameters are present */
    else if(mParamCount != desc->nmParam)
    {
        M3UA_ERROR(("Mandatory parameter missing: Message dropped\n"));
        M3UA_Alarm(4040, __FILE__, __LINE__, NULL);
        return (ITS_EMISSMAND);   
    }

    /* put the params in the host format */
    M3UA_Nm3uaIESToH(ieRef, *ieCount);

    return (ITS_SUCCESS);
}

static void
M3UA_Pause(MTP3_PAUSE_RESUME *pause, UALMgntData *mgnt, SCTPTRAN_Manager *tc)
{
    MTP3_HEADER hdr;
    ITS_EVENT   evt;

    M3UA_DEBUG(("M3UA_Pause: \n"));

    hdr.sio = mgnt->cdata.info.sio;
    MTP3_RL_SET_OPC_VALUE(hdr.label, MTP3_PC_GET_VALUE(pause->affected));
    MTP3_RL_SET_DPC_VALUE(hdr.label, mgnt->cdata.info.pc);
    MTP3_RL_SET_SLS(hdr.label, 0);

    MTP3_Encode(&evt, MTP3_MSG_PAUSE, &hdr,
                (ITS_OCTET *)pause, sizeof(MTP3_PAUSE_RESUME));

    CALLBACK_CallCallbackList(MTP3_ManagementCallbacks,
                              (ITS_POINTER) tc,
                              (ITS_POINTER) &evt);

    ITS_EVENT_TERM(&evt);
}


static void 
M3UA_Resume(MTP3_PAUSE_RESUME *resume, UALMgntData *mgnt, SCTPTRAN_Manager *tc)
{
    MTP3_HEADER hdr;
    ITS_EVENT   evt;

    M3UA_DEBUG(("M3UA_Resume: \n"));

    hdr.sio = mgnt->cdata.info.sio;
    MTP3_RL_SET_OPC_VALUE(hdr.label, MTP3_PC_GET_VALUE(resume->affected));
    MTP3_RL_SET_DPC_VALUE(hdr.label, mgnt->cdata.info.pc);
    MTP3_RL_SET_SLS(hdr.label, 0);

    MTP3_Encode(&evt, MTP3_MSG_RESUME, &hdr,
                (ITS_OCTET *)resume, sizeof(MTP3_PAUSE_RESUME)); 

    CALLBACK_CallCallbackList(MTP3_ManagementCallbacks,
                              (ITS_POINTER) tc,
                              (ITS_POINTER) &evt);

    ITS_EVENT_TERM(&evt);
}

static void
Send_Parm_ERROR(SCTPTRAN_Manager *m, ITS_UINT ecode, ITS_M3UA_IE *Ies)
{
    ITS_EVENT evt;
    ITS_INT   ieC = 0;
    ITS_INT   ret = 0;
    ITS_M3UA_IE ies[10];

    M3UA_DEBUG(("Send_Parm_ERROR: \n"));

    memset(ies, 0, 10 * sizeof(ITS_M3UA_IE));

    ies[ieC].param_id = M3UA_PRM_MSG_HDR;
    ies[ieC].param_length =  sizeof(M3UA_MSG_HDR);
    ies[ieC].param_data.msgHeader.msgClass = UAL_CLASS_MGMT; 
    ies[ieC].param_data.msgHeader.msgType  = UAL_MSG_ERR;
    ies[ieC].param_data.msgHeader.version  = UAL_GL_VERSION;
    ies[ieC].param_data.msgHeader.reserved = 0;

    ieC++;    

    ies[ieC].param_id = UAL_PRM_ERROR_CODE;
    ies[ieC].param_length =  sizeof(UAL_ERROR_CODE);
    ies[ieC].param_data.errorCode.eCode = SOCK_HToNL(ecode);
    
    ieC++;

    if (Ies != NULL)
    {
        /* Add additional ies depending on error codes */
        memcpy(&ies[ieC], Ies, sizeof(ITS_M3UA_IE));

        ieC++;
    }

    ITS_EVENT_INIT(&evt, UAL_MANAGER_INSTANCE, 256);

    ret = M3UA_EncodeMsg(ies, ieC, &evt, &M3UA_ERROR_Desc);

    if (ret == ITS_SUCCESS)
    {
        TRANSPORT_PutEvent(TRANSPORT_INSTANCE(m), &evt);
    }
    else
    {
        M3UA_ERROR(("Send_Parm_ERROR: encode failed. ret = %d\n", ret));
    }

     ITS_EVENT_TERM(&evt);
}
 
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Convert from M3UA to MTP3
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  DATA ---> MTP3-Transfer 
 *  DUNA ---> MTP-Pause
 *  DAVA ---> MTP-Resume
 *  DAUD ---> MTP-Status
 * 
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name      Date        Reference      Description
 * -----------------------------------------------------------------------------
 * ssingh    04-01-2005                 Modified to change Traces from  
 *                                      ITS_TRACE to M3UA.
 * adutta    04-06-2005  BugId:1670     Peg count for DAUD incremented.
 *
 * gdevanand 05-03-2005  BugId:1795     Peg count for DAUD incremented.
 *
 * kramesh   05-07-2008  BugId:882       SG Application is exiting on recepit of 
 *                                       DAUD message from ASP. 
 *
 * skatta    05-08-2008  BugId:911      SG should not respond with DAUD 
 *                                      on recepit of SCON message from ASP. 
 *  See Also:
 ****************************************************************************/
M3UADLLAPI int
M3UA_To_MTP3_Codec(SCTPTRAN_Manager* m, ITS_EVENT *evt, ITS_BOOLEAN *isMgmt, 
                   ITS_OCTET *sls)
{
    int ret = ITS_SUCCESS;
    M3UA_MSG_HDR commonHdr;
    ITS_M3UA_IE ies[10];
    int ieCount = 0;
    MTP3_POINT_CODE pc;

    M3UA_DEBUG(("M3UA_To_MTP3_Codec: \n"));
    PRINT_EVENT(evt);

    memcpy(&commonHdr, evt->data, sizeof(M3UA_MSG_HDR));

    if (commonHdr.msgLen < sizeof(M3UA_MSG_HDR))
    {
       M3UA_Alarm(4045, __FILE__, __LINE__, NULL);
       /* 1 - version, 1 - reserved, 1 - msgClass, 1 - msgType, 4 - msgLen */
       Send_Parm_ERROR (m, UAL_ERR_PARM_FIELD_ERR, NULL);

       UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_ERR_SENT_ID);

       return ITS_EPROTERR;
    }

    /* 
     * Header should have the version to be M3UA_PROT_VER1
     */
    if(commonHdr.version != UAL_GL_VERSION)
    {
        Send_Parm_ERROR (m, UAL_ERR_INV_VESION, NULL);

        UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_ERR_SENT_ID);
        return ITS_EPROTERR;
    }

    int retVal = ITS_SUCCESS;
    switch (commonHdr.msgClass)
    {
        case UAL_CLASS_MGMT:
        {
	    *isMgmt = ITS_TRUE;
	    /* MGMT messages should be sent ONLY on stream '0' */
	    if(*sls != 0x00)
	    {
                switch(commonHdr.msgType)
                {
                    case UAL_MSG_ERR:
                    {
                        M3UA_Alarm(4044, __FILE__, __LINE__, NULL);
                        M3UA_ERROR(("MGMT class msg (ERROR) received on Invalid Stream (id=%d). Message dropped\n"));
                        retVal = ITS_EPROTERR;
                        break;
    	            }
                    case UAL_MSG_NOTIFY:
                    {
                        M3UA_Alarm(4044, __FILE__, __LINE__, NULL);
                        M3UA_ERROR(("MGMT class msg (NOTIFY) received on Invalid Stream (id=%d). Message dropped\n"));
                        Send_Parm_ERROR (m, UAL_ERR_INV_STREAM_ID, NULL);
                        UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_ERR_SENT_ID);
                        retVal = ITS_EPROTERR;
    	                break;
    	            }
    		    default:
    		    {
                        M3UA_Alarm(4039, __FILE__, __LINE__, NULL);
            	        M3UA_ERROR(("MGMT class msg received with invalid msg Type. Message dropped\n"));
                        Send_Parm_ERROR (m, UAL_ERR_UNSUP_MSG_TYPE, NULL);
                        UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_ERR_SENT_ID);
            	        retVal = ITS_FALSE;
    		        break;
    		    }
		}    
    	    }
	    break;
	}
        case UAL_CLASS_SNM:
        {
            switch(commonHdr.msgType)
            {
                case M3UA_MSG_DUNA:
                {
                    if(UAL_GL_ITW_MODE == UAL_ITW_SG)
                    {
                        M3UA_ERROR(("SG is discarding DUNA message\n"));
                        ITS_EVENT_TERM(evt);
                        return ITS_SUCCESS;
                    }
                    /* converts to an MTP_PAUSE msg */
                    MTP3_PAUSE_RESUME pause;
                    MTP3_HEADER       hdr;
                    ITS_M3UA_IE       *ieTmp = NULL;   
                    UALMgntData       ualData;
        
                    /* log an alarm */
                    M3UA_Alarm(4027, __FILE__, __LINE__, NULL);
        
                    ret = M3UA_DecodeMsg(ies, &ieCount, evt, &M3UA_DUNA_Desc);
		            CHECK_M3UA_DECODEMSG_ERROR(m, ret);
                    if (ret != ITS_SUCCESS)
                    {
                        M3UA_ERROR(("Error Decoding DUNA msg\n"));
                        break;
                    }
        
                    ieTmp = M3UA_FindM3UAIE(ies, ieCount, M3UA_PRM_ROUT_CTX);
                    if (ieTmp != NULL)
                    {
                        ITS_UINT rCtxts[M3UA_MAX_RK_NUM]; /* TODO may need larger Array...*/
                        int      numRctxt = 0;
        
                        ret = M3UA_DecodeRoutingContext(ieTmp->param_data.rCtxt.rCtxt,
                                                        ieTmp->param_length, rCtxts,
                                                        &numRctxt);
                        if (ret != ITS_SUCCESS)
                        {
                            M3UA_ERROR(("M3UA, malformed Routing Ctxt.\n"));
  
                            ITS_EVENT_TERM(evt); 
                            return ITS_EMISSMAND;

                        }
        
                        if (!UAL_IsRCtxtValid(*rCtxts))
                        {
                            Send_Parm_ERROR(m, UAL_ERR_INV_ROUT_CTXT, ieTmp);
        
                            UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_ERR_SENT_ID);
                            ITS_EVENT_TERM(evt); 
                            return ITS_EMISSMAND;
                        }
                    }
        
                    ieTmp = M3UA_FindM3UAIE(ies, ieCount, M3UA_PRM_AFFECTED_PC);
                    if (ieTmp == NULL)
                    {
                        M3UA_ERROR(("Missing Affected PC in DUNA msg\n"));
        
                        ret=ITS_EMISSMAND;
                        break;
                    }
        
                    UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_DUNA_RECV_ID);
        
                    M3UA_FLIP_IE_PC(pause.affected.data,
                                    ieTmp->param_data.apc.apc.data);
                    ITS_EVENT_TERM(evt); 

                    /* 
                     * If we don't have a remote route for this PC, ignore.
                     */
                    if (!M3UA_IsConcernedPC(MTP3_PC_GET_VALUE(pause.affected)))
                    {
                        M3UA_WARNING(("M3UA_To_MTP3_Codec: Ignoring DUNA for PC %d\n",
                                      MTP3_PC_GET_VALUE(pause.affected)));
                        ret = (ITS_ENOTFOUND);
                        break;
                    }

                    ret = MTP3_Encode(evt, MTP3_MSG_PAUSE, &hdr,
                                      (ITS_OCTET*)&pause, sizeof(MTP3_PAUSE_RESUME));
                    if (ret != ITS_SUCCESS)
                    {
                        M3UA_ERROR(("Error encoding PAUSE\n"));
        
                        return ret;
                    }
        
                    ualData.type = UAL_MTP3_PAUSE;
                    ualData.cdata.mtp3_info.pc = MTP3_PC_GET_VALUE(pause.affected);

                    /* generate the STATUS-DAUD msg */
		    MTP3_STATUS status;
                    MTP3_PC_SET_VALUE(status.affected, ualData.cdata.mtp3_info.pc);
                    status.cause = MTP3_STATUS_AUDIT;
                    status.congLevel = ITS_SUCCESS; /* used as a sentinal value */
		    
                    CheckAndStartOrStopAuditTimer((ITS_POINTER)&status, TRANSPORT_INSTANCE(m), ITS_FALSE);
                    PauseCallback((ITS_POINTER)m, (ITS_POINTER)&pause, (ITS_POINTER)&ualData);
        
                    break;
                }
                case M3UA_MSG_DAVA:
                case M3UA_MSG_DRST:
                {
                    if(UAL_GL_ITW_MODE == UAL_ITW_SG)
                    {
                        M3UA_ERROR(("SG is discarding DAVA/DRST message\n"));
                        ITS_EVENT_TERM(evt);
                        return ITS_SUCCESS;
                    }
                    /* converts to an MTP_RESUME msg */
                    MTP3_PAUSE_RESUME resume;
                    MTP3_HEADER       hdr;
                    ITS_M3UA_IE       *ieTmp = NULL;   
                    UALMgntData       ualData;
        
                    ret = M3UA_DecodeMsg(ies, &ieCount, evt, &M3UA_DAVA_Desc);
		    CHECK_M3UA_DECODEMSG_ERROR(m, ret);
                    if (ret != ITS_SUCCESS)
                    {
                        if (commonHdr.msgType == M3UA_MSG_DAVA)
                        {
                            M3UA_ERROR(("Error Decoding DAVA msg\n"));
                        }
			else
                        {
                            M3UA_ERROR(("Error Decoding DRST msg\n"));
                        }
			break;
                    }
                    if (commonHdr.msgType == M3UA_MSG_DAVA)
                    {
                        M3UA_Alarm(4028, __FILE__, __LINE__, NULL);
                        UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_DAVA_RECV_ID);
                    }
                    else
                    {
                        M3UA_Alarm(4031, __FILE__, __LINE__, NULL);
                        UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_DRST_RECV_ID);
                    }
        
                    ieTmp = M3UA_FindM3UAIE(ies, ieCount, M3UA_PRM_ROUT_CTX);
                    if (ieTmp != NULL)
                    {
                        ITS_UINT rCtxts[M3UA_MAX_RK_NUM]; /* TODO may need larger Array...*/
                        int numRctxt = 0;
        
                        ret = M3UA_DecodeRoutingContext(ieTmp->param_data.rCtxt.rCtxt,
                                                        ieTmp->param_length, rCtxts,
                                                        &numRctxt);
                        if (ret != ITS_SUCCESS)
                        {
                            M3UA_ERROR(("M3UA, malformed Routing Ctxt.\n"));
                            ITS_EVENT_TERM(evt);
                            return ITS_EMISSMAND;
                        }
        
                        if (!UAL_IsRCtxtValid(*rCtxts))
                        {
                            Send_Parm_ERROR(m, UAL_ERR_INV_ROUT_CTXT, ieTmp);
                            
        		    UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_ERR_SENT_ID);
                            ITS_EVENT_TERM(evt); 
                            return ITS_EMISSMAND;
                        }
                    }
        
                    ieTmp = M3UA_FindM3UAIE(ies, ieCount, M3UA_PRM_AFFECTED_PC);
                    if (ieTmp == NULL)
                    {
                        M3UA_ERROR(("Missing Affected PC in DAVA msg\n"));
        		UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_ERR_SENT_ID);
                        ret=ITS_EMISSMAND;
                        break;
                    }
        
                    M3UA_FLIP_IE_PC(resume.affected.data, 
                                    ieTmp->param_data.apc.apc.data);
                    ITS_EVENT_TERM(evt); 

                    /* 
                     * If we don't have a remote route for this PC, ignore.
                     */
                    if (!M3UA_IsConcernedPC(MTP3_PC_GET_VALUE(resume.affected)))
                    {
                        M3UA_WARNING(("M3UA_To_MTP3_Codec: Ignoring DAVA for PC %d\n",
                                      MTP3_PC_GET_VALUE(resume.affected)));
                        ret = (ITS_ENOTFOUND);
                        break;
                    }                

                    ret = MTP3_Encode(evt, MTP3_MSG_RESUME, &hdr,
                                      (ITS_OCTET*)&resume, sizeof(MTP3_PAUSE_RESUME));
                    if (ret != ITS_SUCCESS)
                    {
                        M3UA_ERROR(("Error encoding RESUME\n"));
        
                        return ret;
                    }
        
                    ualData.type = UAL_MTP3_RESUME;
                    ualData.cdata.mtp3_info.pc = MTP3_PC_GET_VALUE(resume.affected);
       
                    ITS_BOOLEAN isDAVA = ITS_TRUE;
		   
                    if (commonHdr.msgType == M3UA_MSG_DRST)
                    {
		        isDAVA = ITS_FALSE;
	            }
                    /* generate the STATUS-DAUD msg */
		    MTP3_STATUS status;
                    MTP3_PC_SET_VALUE(status.affected, ualData.cdata.mtp3_info.pc);
                    status.cause = MTP3_STATUS_AUDIT;
                    status.congLevel = ITS_SUCCESS; /* used as a sentinal value */

		    CheckAndStartOrStopAuditTimer((ITS_POINTER)&status, TRANSPORT_INSTANCE(m), isDAVA);
                    ResumeCallback((ITS_POINTER)m, (ITS_POINTER)&resume, 
                                   (ITS_POINTER)&ualData);
        
                    break;
                }
                case M3UA_MSG_SCON:
                {
                    MTP3_STATUS status;
                    MTP3_HEADER hdr;
                    ITS_M3UA_IE *ieTmp = NULL;   
        
                    /* log an alarm */
                    M3UA_Alarm(4029, __FILE__, __LINE__, NULL);
        
                    ret = M3UA_DecodeMsg(ies, &ieCount, evt, &M3UA_SCON_Desc);
		    CHECK_M3UA_DECODEMSG_ERROR(m, ret);
		    if (ret != ITS_SUCCESS)
		    {
                        M3UA_ERROR(("Error Decoding message\n"));
                        ITS_EVENT_TERM(evt); 
                        return ret;
		    }
                    else
		    {
                        ieTmp = M3UA_FindM3UAIE(ies, ieCount, M3UA_PRM_ROUT_CTX);
                        if (ieTmp != NULL)
                        {
                            ITS_UINT rCtxts[M3UA_MAX_RK_NUM]; /* TODO may need larger Array...*/
                            int numRctxt = 0;
        
                            ret = M3UA_DecodeRoutingContext(ieTmp->param_data.rCtxt.rCtxt,
                                                            ieTmp->param_length, rCtxts,
                                                            &numRctxt);
                            if (ret != ITS_SUCCESS)
                            {
                                M3UA_ERROR(("M3UA, malformed Routing Ctxt.\n"));
                                ITS_EVENT_TERM(evt); 
                                return ITS_EMISSMAND;
                            }
        
                            if (!UAL_IsRCtxtValid(*rCtxts))
                            {
                                Send_Parm_ERROR(m, UAL_ERR_INV_ROUT_CTXT, ieTmp);
        		        UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_ERR_SENT_ID);
                                ITS_EVENT_TERM(evt); 
                                return ITS_EMISSMAND;
                            }
                        }
        
                        ieTmp = M3UA_FindM3UAIE(ies, ieCount, M3UA_PRM_AFFECTED_PC);
        
                        if (ieTmp == NULL || ret != ITS_SUCCESS)
                        {
                            M3UA_ERROR(("Missing Affected PC in SCON msg\n"));
            	            UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_ERR_SENT_ID);
                            ret = ITS_EMISSMAND;
                            break;
                        }
        
        	        UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_SCON_RECV_ID);
        
                        M3UA_FLIP_IE_PC(status.affected.data, ieTmp->param_data.apc.apc.data);
       
                        ITS_BOOLEAN congLevelPresent = ITS_FALSE; 

                        ieTmp = M3UA_FindM3UAIE(ies, ieCount, M3UA_PRM_CONGEST_LEVEL);
                        if (ieTmp == NULL)
                        {
                            M3UA_DEBUG(("Missing Cong Level in SCON msg\n"));
                        }
                        else
                        {
                            status.congLevel = (ieTmp->param_data.congestion.level & 0xFF);
        
                            if (ieTmp->param_data.congestion.level < 0 || 
                                ieTmp->param_data.congestion.level > 3)
                            {
                                 Send_Parm_ERROR(m, UAL_ERR_INV_PARM_VALUE, NULL);

        	                 UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_ERR_SENT_ID);
                                 ITS_EVENT_TERM(evt);
                                 return ITS_EMISSMAND;
                            }
                            congLevelPresent = ITS_TRUE;
                        }
            
                        status.cause = MTP3_STATUS_CONGESTED;
                        ITS_EVENT_TERM(evt);
                        ret = MTP3_Encode(evt, MTP3_MSG_STATUS, &hdr,
                                          (ITS_OCTET*)&status, sizeof(MTP3_STATUS));
                        if (ret != ITS_SUCCESS)
                        {
                            M3UA_ERROR(("Error encoding STATUS\n"));
            
                            return ret;
                        }
            
                        /* generate the STATUS-DAUD msg */
                        if(UAL_GL_ITW_MODE != UAL_ITW_SG)
                        {
    		            MTP3_STATUS newStatus;
                            MTP3_PC_SET_VALUE(newStatus.affected, MTP3_PC_GET_VALUE(status.affected));
                            newStatus.cause = MTP3_STATUS_AUDIT;
                            newStatus.congLevel = ITS_SUCCESS; /* used as a sentinal value */

                            /* set the status.congLevel to !ITS_SUCCESS to help the 
                             * CheckAndStartOrStopAuditTimer() to differentiate between
                             * SCON with congLevel 0 (zero) and other SCON messages */
                            if(congLevelPresent  == ITS_TRUE && status.congLevel == 0)  
                            {
                                newStatus.congLevel = !ITS_SUCCESS;
                            }

    		            CheckAndStartOrStopAuditTimer((ITS_POINTER)&newStatus, TRANSPORT_INSTANCE(m), ITS_FALSE);
                        }
                        StatusCallback((ITS_POINTER)m, NULL, (ITS_POINTER)evt);
        
                    }
		    break;
                }
                case M3UA_MSG_DUPU:
                {
					if(UAL_GL_ITW_MODE == UAL_ITW_SG)
					{
						M3UA_ERROR(("SG is discarding DUPU message\n"));
						return ITS_SUCCESS;
					}
                    MTP3_STATUS     status;
                    MTP3_HEADER     hdr;
#if defined(CCITT) || defined(TTC)
                    //MTP3_POINT_CODE pc;
#endif
                    int             i, j, c;
                    ITS_M3UA_IE *ieTmp = NULL;   
        
                    i = j = -1;
        
                    M3UA_Alarm(4032, __FILE__, __LINE__, NULL);
        
                    ret = M3UA_DecodeMsg(ies, &ieCount, evt, &M3UA_DUPU_Desc);
		    CHECK_M3UA_DECODEMSG_ERROR(m, ret);
                    if (ret != ITS_SUCCESS)
                    {
                        M3UA_ERROR(("Error Decoding DUPUsg\n"));
                        break;
                    }
        
                    for (c = 0; (ret == ITS_SUCCESS) && (c < ieCount); c++)
                    {
                        if (ies[c].param_id == M3UA_PRM_AFFECTED_PC)
                        {
                            i = c;  /* Affected point code index */
                        }
                        else if (ies[c].param_id == M3UA_PRM_CAUSE_USER)
                        {
                            j = c;  /* USER and CAUSE param index */
                        }
                    }
        
                    if (i == -1 || j == -1)
                    {
                       ret = ITS_EMISSMAND;
                       break;
                    }
        	    UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_DUPU_RECV_ID);
                    ieTmp = M3UA_FindM3UAIE(ies, ieCount, M3UA_PRM_ROUT_CTX);
                    if (ieTmp != NULL)
                    {
                        ITS_UINT rCtxts[M3UA_MAX_RK_NUM]; /* TODO may need larger Array...*/
                        int numRctxt = 0;
        
                        ret = M3UA_DecodeRoutingContext(ieTmp->param_data.rCtxt.rCtxt,
                                                        ieTmp->param_length, rCtxts,
                                                        &numRctxt);
                        if (ret != ITS_SUCCESS)
                        {
                            M3UA_ERROR(("M3UA, malformed Routing Ctxt.\n"));
                            ITS_EVENT_TERM(evt); 
                            return ITS_EMISSMAND;
                        }
        
                        if (!UAL_IsRCtxtValid(*rCtxts))
                        {
                            Send_Parm_ERROR(m, UAL_ERR_INV_ROUT_CTXT, ieTmp);
        
        	            UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_ERR_SENT_ID);
                            ITS_EVENT_TERM(evt); 
                            return ITS_EMISSMAND;
                        }
                    }
        
                    M3UA_FLIP_IE_PC(status.affected.data, ies[i].param_data.apc.apc.data);
        
                    c = (ies[j].param_data.causeUsr.cause & 0xFF);
        
                    if (c == M3UA_UNKNOWN_CAUSE)
                    {
                        status.cause = MTP3_STATUS_UPU_UNKNOWN;
                    }
                    else if (c == M3UA_UNEQUIP_REMOTE_USR)
                    {
                        status.cause = MTP3_STATUS_UPU_UNEQUIP;
                    }
                    else if (c == M3UA_INACCESS_REMOTE_USR)
                    {
                        status.cause = MTP3_STATUS_UPU_INACCESS;
                    }
                    else
                    {
                        Send_Parm_ERROR(m, UAL_ERR_INV_PARM_VALUE, NULL);
                        
        	        UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_ERR_SENT_ID);
        
                        M3UA_WARNING(("Received Invalid cause.\n"));
                        ITS_EVENT_TERM(evt); 
                        return !ITS_SUCCESS;
                    }
                    ITS_EVENT_TERM(evt); 
                    ret = MTP3_Encode(evt, MTP3_MSG_STATUS, &hdr,
                                      (ITS_OCTET*)&status, sizeof(MTP3_STATUS));
                    if (ret != ITS_SUCCESS)
                    {
                        M3UA_ERROR(("Error encoding STATUS\n"));
        
                        return ret;
                    }
        
                    StatusCallback((ITS_POINTER)m, NULL, (ITS_POINTER)evt);
        
                    break;
                }
                case M3UA_MSG_DAUD:
                {
					if(UAL_GL_ITW_MODE == UAL_ITW_ASP)
					{
						M3UA_ERROR(("ASP is discarding DAUD message\n"));
						return ITS_SUCCESS;
					}
                    ITS_M3UA_IE       *ieTmp  = NULL;
                    ITS_UINT          ieCount = 0;
                    MTP3_PAUSE_RESUME pr;
                    ITS_UINT          dpc = 0;
                    ITS_EVENT         m3uaEvt;
                    SS7_Family        family = FAMILY_ITU;
                    SS7_Destination   *dest  = NULL;
                    ROUTE_Info        *rinfo = NULL;
                    int               count  = 0;
                    const int         max_look_ups = 4;
                    ITS_OCTET         sio     = M3UA_UNUSED_SIO;
                    ITS_OCTET         msgType = 0;
                    ITS_BOOLEAN       niFound = ITS_FALSE;
        
                    M3UA_Alarm(4030, __FILE__, __LINE__, NULL);
        
                    ret = M3UA_DecodeMsg(ies, (int *) &ieCount, evt, &M3UA_DAUD_Desc);
		    CHECK_M3UA_DECODEMSG_ERROR(m, ret);
                    if (ret != ITS_SUCCESS)
                    {
                        M3UA_ERROR(("Error Decoding DAUD msg\n"));
                        ITS_EVENT_TERM(evt);
                        return ret;
                    }
        
                    ieTmp = M3UA_FindM3UAIE(ies, ieCount, M3UA_PRM_AFFECTED_PC);
                    if (ieTmp == NULL)
                    {
                        M3UA_ERROR(("Missing Affected PC in DAUD msg\n"));
        
                        Send_Parm_ERROR(m, UAL_ERR_MISSING_PARAM, NULL);
        
        	        UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_ERR_SENT_ID);
                        ITS_EVENT_TERM(evt); 
                        return ITS_EMISSMAND;
                    }
        
        	    UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_DAUD_RECV_ID);
        
                    /*
                     * TODO: Add multiple destinations support in DAUD.
                     */
                    M3UA_FLIP_IE_PC(pr.affected.data, ieTmp->param_data.apc.apc.data);
                    
#if defined(CCITT)
                    /* affected destination */
                    dpc    = MTP3_PC_GET_VALUE_CCITT(pr.affected);
                    family = FAMILY_ITU;
#elif defined(ANSI)
                    /* affected destination */
                    dpc    = MTP3_PC_GET_VALUE_ANSI(pr.affected);
                    family = FAMILY_ANSI;
#endif
        
                    M3UA_DEBUG(("Affected PC = %d", dpc));
        
                    ieTmp = M3UA_FindM3UAIE(ies, ieCount, M3UA_PRM_ROUT_CTX);
        
                    if (ieTmp != NULL)
                    {
                        ITS_UINT rCtxts[M3UA_MAX_RK_NUM];
                        int      numRctxt = 0;
        
                        ret = M3UA_DecodeRoutingContext(ieTmp->param_data.rCtxt.rCtxt,
                                                        ieTmp->param_length, rCtxts,
                                                        &numRctxt);
        
                        
                        if (!UAL_IsRCtxtValid(*rCtxts))
                        {
                            Send_Parm_ERROR(m, UAL_ERR_INV_ROUT_CTXT, ieTmp);
        
        	            UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_ERR_SENT_ID);
                            ITS_EVENT_TERM(evt); 
                            return ITS_EMISSMAND;
                        }
        
                        if (ret == ITS_SUCCESS)
                        {
                            ROUTE_Info **tmp;
                            if (ROUTE_FindRoutingKeyInfo(rCtxts[0], &tmp) == ITS_SUCCESS)
                            {
                                rinfo = *tmp;
                                if (rinfo)
                                {
                                    sio   = rinfo->basic.criteria.sio;
                                    niFound = ITS_TRUE;
                                }
                            }
                        }
                        else
                        {
                            M3UA_ERROR(("M3UA routing context decode failed.\n"));
                        }
                    }
        
                    if(niFound == ITS_TRUE)
                    {
                        dest = ROUTE_FindDestination(dpc, sio, family);
                    }
                    else
                    {
                        sio = M3UA_SIO_0;
        
                        /*
                         * We have DPC, lookup for the Destination in 
                         * the routing table. 
                         * Check for all the Network Indicators
                         *   INTERNATIONAL          0x00
                         *   INTERNATIONAL-SPARE    0x40
                         *   NATIONAL               0x80
                         *   NATIONAL-SPARE         0xC0
                         */
                        while (count < max_look_ups)
                        {
                            dest = ROUTE_FindDestination(dpc, sio, family);
                            if (dest != NULL)
                            {
                                break;
                            }  
                            sio  = sio + M3UA_SIO_40;
                            count++;
                        }
                    }

                    if (dest == NULL)
                    {
                        return !ITS_SUCCESS; 
                    }
         
                    /* TO DO::::  The destination structure should have CONGESTION 
                       state also.  This will be implemented when the Overload 
                       Congestion Feature is available.
                       If the destination is congested and available, then a SCON message
                       should be sent followed by DAVA.
                       Iif the destination is congested and restricted, then a
                       SCON message should be sent followed by DRST.
                       If the destination is unavailable, a DUNA message is sent.
                    */
                    if (dest->status == DESTINATION_UNAVAILABLE)
                    {
                        msgType = M3UA_MSG_DUNA;
                    }
                    else if (dest->status == DESTINATION_RESTRICTED)
                    {
                        msgType = M3UA_MSG_DRST;
                    }
                    else if (dest->status == DESTINATION_AVAILABLE)
                    {
                        msgType = M3UA_MSG_DAVA;
                    }
        
                    /*Get the SLS value */
                    *sls = 1 % 32;
        
                    ies[0].param_id      = M3UA_PRM_MSG_HDR;
                    ies[0].param_length  = sizeof(M3UA_MSG_HDR);
        
                    ies[0].param_data.msgHeader.msgClass = UAL_CLASS_SNM;
                    ies[0].param_data.msgHeader.msgType  = msgType;
                    ies[0].param_data.msgHeader.version  = UAL_GL_VERSION;
                    ies[0].param_data.msgHeader.reserved = 0;
        
                    ies[1].param_id     = M3UA_PRM_AFFECTED_PC;
                    ies[1].param_length = sizeof(M3UA_AFFECTED_PC);
        
                    ies[1].param_data.apc.apc.mask = 0x00;
        
                    M3UA_FLIP_IE_PC(pc.data, ies[1].param_data.apc.apc.data);
        
                    ITS_EVENT_INIT(&m3uaEvt, UAL_MANAGER_INSTANCE, 256);
        
                    if (msgType == M3UA_MSG_DAVA)
                    {
                        ret = M3UA_EncodeMsg(ies, 2, &m3uaEvt, &M3UA_DAVA_Desc);
	                UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_DAVA_SENT_ID);
                    }
                    else if (msgType == M3UA_MSG_DUNA)
                    {
                        ret = M3UA_EncodeMsg(ies, 2, &m3uaEvt, &M3UA_DUNA_Desc);
	                UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_DUNA_SENT_ID);
                    }
                    else if(msgType == M3UA_MSG_DRST)
                    {
                        ret = M3UA_EncodeMsg(ies, 2, &m3uaEvt, &M3UA_DRST_Desc);
	                UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_DRST_SENT_ID);
                    }
        
                    if (ret == ITS_SUCCESS)
                    {
                        ret = TRANSPORT_PutEvent(TRANSPORT_INSTANCE(m), &m3uaEvt);
                        if (ret == ITS_SUCCESS)
                        {
                           if (msgType == M3UA_MSG_DAVA)
                           {
                               M3UA_Alarm(4034, __FILE__, __LINE__, NULL);
                           }
                           else if (msgType == M3UA_MSG_DUNA)
                           {
                               M3UA_Alarm(4033, __FILE__, __LINE__, NULL);
                           }
                        }
                        else
                        {
                           M3UA_ERROR(("Error Sending DAUD Resp, ret = %d\n", ret));
                        }
                    }
                    else
                    {
                        M3UA_ERROR(("Error Sending DAUD Resp, ret = %d\n", ret));
                    }
        
                    ITS_EVENT_TERM(evt);
        
                    /* Stop processing here; rcvd event responded */
                    return (!ITS_SUCCESS);
        
                    break;
                }
                default:
		{
                    M3UA_Alarm(4039, __FILE__, __LINE__, NULL);
                    Send_Parm_ERROR(m, UAL_ERR_UNSUP_MSG_TYPE, NULL);
        	    UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_ERR_SENT_ID);
                    break;
                } 
            }
   
	    retVal = ret;
	    break;
        }
        case UAL_CLASS_TRANSFER:
        {
            ITS_M3UA_IE     *ieTmp = NULL;
            MTP3_HEADER     hdr;
            MTP3_POINT_CODE pc;
            UAL_ASP_STATE   aspState;
            ITS_USHORT      trid = TRANSPORT_INSTANCE(m);
    
            /* Check for ASP state before processing */
            ret = UAL_GetASPState(trid, &aspState);
            if (ret == ITS_SUCCESS) 
            {
               if (aspState != UAL_ASP_ACTIVE) 
               {
                  if (UAL_GetIntWorkingMode() == UAL_ITW_SG)
                  {
                      Send_Parm_ERROR (m, UAL_ERR_UNEPECTED_MSG, ieTmp);
                      UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_ERR_SENT_ID);
                  }
                  else
                  {
                      M3UA_ERROR(("Message discarded, ASP state = %d\n", aspState));
                  }
                  return ITS_EBADSTATE;
               }
            }
            else
            {
               return ret;
            }
    
            switch(commonHdr.msgType)
            {
                case M3UA_MSG_PAYLOAD_DATA:
                {
                    ret = M3UA_DecodeMsg(ies, &ieCount, evt, &M3UA_DATA_Desc);
		    CHECK_M3UA_DECODEMSG_ERROR(m, ret);
                    if (ret != ITS_SUCCESS)
                    {
                        M3UA_ERROR(("Failed to decode M3UA DATA Msg\n"));
                        break;                
                    }
        
        	    UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_DATA_RECV_ID);
        
                    /* We look if the Routing Context param is present */
                    ieTmp = M3UA_FindM3UAIE(ies, ieCount, M3UA_PRM_ROUT_CTX);
                    if (ieTmp != NULL)
                    {
                        ITS_UINT rCtxts[M3UA_MAX_RK_NUM];
                        int numRctxt = 0;
        
                        ret = M3UA_DecodeRoutingContext(ieTmp->param_data.rCtxt.rCtxt,
                                                        ieTmp->param_length, rCtxts, 
                                                        &numRctxt);

                        if (ret != ITS_SUCCESS)
                        {
                            M3UA_ERROR(("M3UA, malformed Routing Ctxt.\n"));
        
                            return ITS_EMISSMAND;  
                        }
        
                        /* M3UA Payload Data should have only one RC */
                        if(numRctxt > 1)
                        {
                            M3UA_ERROR(("M3UA, Invalid Routing Context Parameter\n"));
                            return !ITS_SUCCESS;
                        }

                        if (!UAL_IsRCtxtValid(*rCtxts))
                        {
                            Send_Parm_ERROR(m, UAL_ERR_INV_ROUT_CTXT, ieTmp);
        
        	            UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_ERR_SENT_ID);
        
                            return ITS_EMISSMAND;
                        } 
                    }
        
                    ieTmp = M3UA_FindM3UAIE(ies, ieCount, M3UA_PRM_DATA);
                    if (ieTmp == NULL) 
                    {
                        M3UA_ERROR(("Failed to decode M3UA DATA Msg\n"));
        	        UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_ERR_SENT_ID);
                        return ITS_EMISSMAND;
                        break;
                    }
        
                    M3UA_FLIP_IE_PC(pc.data, ieTmp->param_data.data.dpc.data);
                    MTP3_RL_SET_DPC(hdr.label, pc);
        
                    M3UA_FLIP_IE_PC(pc.data, ieTmp->param_data.data.opc.data);
                    MTP3_RL_SET_OPC(hdr.label, pc);
                    MTP3_RL_SET_SLS(hdr.label, ieTmp->param_data.data.sls);
        
                    hdr.sio = ieTmp->param_data.data.si;
                    hdr.sio |= ((ieTmp->param_data.data.ni << 6) & 0xC0); 
        
                    /*deallocate memory if it has been already been allocated for evt*/
                    ITS_EVENT_TERM(evt);

/* Bug id  51 (ITU) , 65(ANSI)
   Description : If a  malformed MTP3_MSG_USER_DATA is sent with  length less than
                 12 there was a core. Added this defensive check
*/
                    if((ITS_USHORT)(ieTmp->param_length) >= M3UA_DATA_HDR_LEN)
                    {
                          ret = MTP3_Encode(evt, MTP3_MSG_USER_DATA, &hdr,
                                      (ieTmp->param_data.data.data),
                                      (ITS_USHORT)(ieTmp->param_length - M3UA_DATA_HDR_LEN));
                    
                          if (ret != ITS_SUCCESS)
                          {
                               M3UA_ERROR(("Failed to encode M3UA DATA Msg\n"));
        
                               return ret;
                          }
                    }
                    else
                    {
                         M3UA_ERROR(("Failed to encode M3UA DATA Msg : There isn't any user data in message\n"));
                         return ITS_EINVLEN ;
                    }

                    break;           
        
                }
                default:
                {
                    M3UA_Alarm(4039, __FILE__, __LINE__, NULL);
		    Send_Parm_ERROR(m, UAL_ERR_UNSUP_MSG_TYPE, NULL);
        	    UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_ERR_SENT_ID);
        
                    break;
		}    
            }
    
	    retVal = ret;
	    break;
        }
        case UAL_CLASS_ASPSM:
        case UAL_CLASS_ASPTM:
        case UAL_CLASS_RKM:
        {
            *isMgmt = ITS_TRUE;
            break;
	}

        default:
        {
            M3UA_ERROR(("Got Unknown class Message (class=%d, type=%d\n", commonHdr.msgClass, commonHdr.msgType));
            Send_Parm_ERROR(m, UAL_ERR_UNSUP_MSG_CLASS, NULL);
    
    	    UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_ERR_SENT_ID);
	    retVal = !ITS_SUCCESS;
	    break;
        }
    }	

    return retVal;
}

static ITS_USHORT
SelectStream(ITS_OCTET sls, ITS_USHORT availStreams)
{
    ITS_USHORT stream = 0;

    M3UA_DEBUG(("SelectStream: \n"));

    stream = (sls % availStreams);

    /* avoid sending on stream 0 */
    if (stream == 0)
    {
        stream++;
    }

    return stream;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Convert from MTP3 to M3UA
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name        Date        Reference      Description
 * -----------------------------------------------------------------------------
 *
 * kramesh     05-07-2008  	           Fix for issue sending out DRST message
 *                                     from stack.. 
 *
 *  Notes:
 *  See Also:
 ****************************************************************************/
M3UADLLAPI int
MTP3_To_M3UA_Codec(SCTPTRAN_Manager* m, ITS_EVENT *evt, ITS_BOOLEAN *isMgmt, 
                   ITS_OCTET *sls)
{
    ITS_OCTET     msgType = 0, data[MTP3_MAX_SIF_LENGTH] = {0};
    ITS_USHORT    len = 0, outStreams = 1;
    MTP3_HEADER   hdr;
    ITS_M3UA_IE   ies[6];
    int           ret = ITS_SUCCESS;
    ITS_UINT      ieCount = 0;
    ITS_EVENT     m3uaEvt;
    ITS_USHORT    trid = TRANSPORT_INSTANCE(m); 
    UAL_ASP_STATE aspState;

    assert(evt != NULL);

    M3UA_DEBUG(("MTP3_To_M3UA_Codec: \n"));

    if (*isMgmt)
    {
        *sls = 0x00;
        return ITS_SUCCESS;
    }

    /* Check if ASP is ACTIVE first */
    M3UA_DEBUG((" ----- checking ASP STATE -----\n"));

    ret = UAL_GetASPState(trid, &aspState);
    if (ret != ITS_SUCCESS)
    {
        M3UA_ERROR(("Send failed no ASP State.\n"));

        return ret;
    }

    if (aspState != UAL_ASP_ACTIVE)
    {
        M3UA_Alarm(4043, __FILE__, __LINE__, NULL);

        UAL_CB_Context cb_ctxt;

        memset(&cb_ctxt, 0, sizeof(UAL_CB_Context));

        M3UA_ERROR(("M3UA Codec, User trying to Send while not ACTIVE.\n"));

        UAL_CB_CTXT_TYPE(&cb_ctxt)      = UAL_CB_RT_FAIL_CTXT;
        UAL_CB_CTXT_MSU_LEN(&cb_ctxt)   = evt->len;
        memcpy(UAL_CB_CTXT_MSU_DATA(&cb_ctxt), evt->data, evt->len); 

        CALLBACK_CallCallbackList(__UAL_MgntCallBack, NULL,
                                  (ITS_POINTER)&cb_ctxt);

        ITS_EVENT_TERM(evt);

        return (ITS_EBADSTATE);
    }

    ITS_EVENT_INIT(&m3uaEvt, ITS_MTP3_SRC, M3UA_MAX_DATA_SIZE);

     
    /* if event source is MTP3, skip the 3 first bytes */
    if (evt->src == ITS_MTP3_CCITT_SRC ||
        evt->src == ITS_MTP3_ANSI_SRC ||
        evt->src == ITS_MTP3_TTC_SRC ||
        evt->src == ITS_MTP3_PRC_SRC)
    {
        if (evt->data[0] == L3_L2_DATA)
        {
            m3uaEvt.data[0] = MTP3_MSG_USER_DATA;
            memcpy(&(m3uaEvt.data[1]), &(evt->data[4]), (evt->len - 4));
            m3uaEvt.len = evt->len - 3;
        }
        else
        {
            M3UA_WARNING(("M3UA Codec: Ignored MTP3 Primitive %02x\n",
                           evt->data[0]));
            ITS_EVENT_TERM(evt);
            ITS_EVENT_TERM(&m3uaEvt);   
            return ret;
        }
    }
    else
    {
        memcpy(m3uaEvt.data, evt->data, evt->len);

        m3uaEvt.len = evt->len;
    }

    ITS_EVENT_TERM(evt);

    ret = MTP3_Decode(&m3uaEvt, &msgType, &hdr, data, &len);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Get the SLS value */
    /*TODO: Get valid stream number from transport */
    *sls = SelectStream(MTP3_RL_GET_SLS(hdr.label), outStreams);

    switch(msgType)
    {
    case MTP3_MSG_USER_DATA:
    {
        MTP3_POINT_CODE pc, pcTmp;

        ies[ieCount].param_id = M3UA_PRM_MSG_HDR;
        ies[ieCount].param_length = sizeof(M3UA_MSG_HDR);
        ies[ieCount].param_data.msgHeader.msgClass = UAL_CLASS_TRANSFER;
        ies[ieCount].param_data.msgHeader.msgType = M3UA_MSG_PAYLOAD_DATA;
        ies[ieCount].param_data.msgHeader.version = UAL_GL_VERSION;
        ies[ieCount].param_data.msgHeader.reserved = 0;
       
        ieCount++;

        ies[ieCount].param_id = M3UA_PRM_DATA;
        ies[ieCount].param_length = len + M3UA_HDR_SIZE;

#if defined(CCITT) || defined(TTC)
        /* DPC */
        MTP3_RL_GET_DPC(hdr.label, pcTmp);

        memset(&ies[ieCount].param_data.data.dpc, 0, sizeof(M3UA_PC));

        pc.data[0] = pcTmp.data[1]; 
        pc.data[1] = pcTmp.data[0]; 

        memcpy(&ies[ieCount].param_data.data.dpc.data[1], pc.data, 2);

        /* OPC */
        MTP3_RL_GET_OPC(hdr.label, pcTmp);

        memset(&ies[ieCount].param_data.data.opc, 0, sizeof(M3UA_PC));

        pc.data[0] = pcTmp.data[1];
        pc.data[1] = pcTmp.data[0]; 

        memcpy(&ies[ieCount].param_data.data.opc.data[1], pc.data, 2);

        /* SLS */
        ies[ieCount].param_data.data.sls = MTP3_RL_GET_SLS(hdr.label); 

#elif defined(ANSI)

        MTP3_RL_GET_OPC(hdr.label, pcTmp);

        /* flip the point code */
        pc.data[0] = pcTmp.data[2];
        pc.data[1] = pcTmp.data[1];
        pc.data[2] = pcTmp.data[0];
   
        /* OPC */
        memset(&ies[ieCount].param_data.data.opc, 0, sizeof(M3UA_PC));

        memcpy(ies[ieCount].param_data.data.opc.data, pc.data, 3);

        MTP3_RL_GET_DPC(hdr.label, pcTmp);

        /* flip the point code */
        pc.data[0] = pcTmp.data[2];
        pc.data[1] = pcTmp.data[1];
        pc.data[2] = pcTmp.data[0];
   
        /* DPC */
        memset(&ies[ieCount].param_data.data.dpc, 0, sizeof(M3UA_PC));

        memcpy(ies[ieCount].param_data.data.dpc.data, pc.data, 3);

        /* SLS */
        ies[ieCount].param_data.data.sls = MTP3_RL_GET_SLS_ANSI(hdr.label); 

#elif defined(PRC)

        MTP3_RL_GET_OPC(hdr.label, pcTmp);

        /* flip the point code */
        pc.data[0] = pcTmp.data[2];
        pc.data[1] = pcTmp.data[1];
        pc.data[2] = pcTmp.data[0];

        /* OPC */
        memcpy(ies[ieCount].param_data.data.opc.data, pc.data,
               sizeof(MTP3_POINT_CODE));

        MTP3_RL_GET_DPC(hdr.label, pcTmp);

        /* flip the point code */
        pc.data[0] = pcTmp.data[2];
        pc.data[1] = pcTmp.data[1];
        pc.data[2] = pcTmp.data[0];

        /* DPC */
        memcpy(ies[ieCount].param_data.data.dpc.data, pc.data,
               sizeof(MTP3_POINT_CODE));

        /* SLS */
        ies[ieCount].param_data.data.sls = MTP3_RL_GET_SLS_PRC(hdr.label);
#endif 
        /* SIO */
        ies[ieCount].param_data.data.si = hdr.sio & 0x0F;
        ies[ieCount].param_data.data.ni = (hdr.sio & 0xC0) >> 6;

        memcpy(ies[ieCount].param_data.data.data, data, len);

        ieCount++;
  
        ret = M3UA_EncodeMsg(ies, ieCount, &m3uaEvt, &M3UA_DATA_Desc);
        
	UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_DATA_SENT_ID);
        break;
    }
    case MTP3_MSG_PAUSE:
    {
        MTP3_PAUSE_RESUME pause;
        MTP3_POINT_CODE pc;

        if (len > sizeof(MTP3_PAUSE_RESUME))
        {
            return ITS_EINVLEN;
        }

        memcpy(&pause, data, sizeof(MTP3_PAUSE_RESUME));
        
        ies[0].param_id = M3UA_PRM_MSG_HDR;
        ies[0].param_length = sizeof(M3UA_MSG_HDR);
        ies[0].param_data.msgHeader.msgClass = UAL_CLASS_SNM;
        ies[0].param_data.msgHeader.msgType = M3UA_MSG_DUNA;
        ies[0].param_data.msgHeader.version = UAL_GL_VERSION;
        ies[0].param_data.msgHeader.reserved = 0;

        ies[1].param_id = M3UA_PRM_AFFECTED_PC;
        ies[1].param_length = sizeof(M3UA_AFFECTED_PC);
        ies[1].param_data.apc.apc.mask = 0x00;

#if defined(CCITT) || defined(TTC)
        ies[1].param_data.apc.apc.data[0] = 0x00;
        pc.data[0] = pause.affected.data[1];
        pc.data[1] = pause.affected.data[0];
        memcpy(&ies[1].param_data.apc.apc.data[1], pc.data,
               sizeof(MTP3_POINT_CODE));
        
#elif defined(ANSI)
        ies[1].param_data.apc.apc.data[0] = 0x00;
        pc.data[0] = pause.affected.data[2];
        pc.data[1] = pause.affected.data[1];
        pc.data[2] = pause.affected.data[0];
        memcpy(ies[1].param_data.apc.apc.data, pc.data, 
               sizeof(MTP3_POINT_CODE_ANSI));
#elif defined(PRC)
        ies[1].param_data.apc.apc.data[0] = 0x00;
        pc.data[0] = pause.affected.data[2];
        pc.data[1] = pause.affected.data[1];
        pc.data[2] = pause.affected.data[0];
        memcpy(ies[1].param_data.apc.apc.data, pc.data,
               sizeof(MTP3_POINT_CODE_PRC));
#endif

        ret = M3UA_EncodeMsg(ies, 2, &m3uaEvt, &M3UA_DUNA_Desc);
        if (ret != ITS_SUCCESS)
        {
            M3UA_ERROR(("Error Encoding DUNA msg\n"));
        }

        M3UA_Alarm(4033, __FILE__, __LINE__, NULL);

	UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_DUNA_SENT_ID);
        break;
        
    }
    case MTP3_MSG_RESUME:
    {
        MTP3_PAUSE_RESUME resume;
        MTP3_POINT_CODE pc;
        ITS_UINT dpc;
        ITS_UINT count = 0;
        ITS_UINT max_look_ups = 4;
        ITS_OCTET sio = M3UA_UNUSED_SIO;
        SS7_Family family;
        SS7_Destination *dest  = NULL;

        if (len > sizeof(MTP3_PAUSE_RESUME))
        {
            return ITS_EINVLEN;
        }

        memcpy(&resume, data, sizeof(MTP3_PAUSE_RESUME));
        
        ies[0].param_id = M3UA_PRM_MSG_HDR;
        ies[0].param_length = sizeof(M3UA_MSG_HDR);
        ies[0].param_data.msgHeader.msgClass = UAL_CLASS_SNM;
        ies[0].param_data.msgHeader.version = UAL_GL_VERSION;
        ies[0].param_data.msgHeader.reserved = 0;

        ies[1].param_id = M3UA_PRM_AFFECTED_PC;
        ies[1].param_length = sizeof(M3UA_AFFECTED_PC);
        ies[1].param_data.apc.apc.mask = 0x00;

#if defined(CCITT)
        ies[1].param_data.apc.apc.data[0] = 0x00;
        pc.data[0] = resume.affected.data[1];
        pc.data[1] = resume.affected.data[0];
        memcpy(&ies[1].param_data.apc.apc.data[1], pc.data,
               sizeof(MTP3_POINT_CODE));
        dpc    = MTP3_PC_GET_VALUE_CCITT(resume.affected);
        family = FAMILY_ITU;
#elif defined(ANSI)
        ies[1].param_data.apc.apc.data[0] = 0x00;
        pc.data[0] = resume.affected.data[2];
        pc.data[1] = resume.affected.data[1];
        pc.data[2] = resume.affected.data[0];
        memcpy(ies[1].param_data.apc.apc.data, pc.data, 
               sizeof(MTP3_POINT_CODE));
        dpc    = MTP3_PC_GET_VALUE_ANSI(resume.affected);
        family = FAMILY_ANSI;
#elif defined(PRC)
        ies[1].param_data.apc.apc.data[0] = 0x00;
        pc.data[0] = resume.affected.data[2];
        pc.data[1] = resume.affected.data[1];
        pc.data[2] = resume.affected.data[0];
        memcpy(ies[1].param_data.apc.apc.data, pc.data,
               sizeof(MTP3_POINT_CODE));
        dpc    = MTP3_PC_GET_VALUE_PRC(resume.affected);
        family = FAMILY_CHINA;
#elif defined(TTC)
        ies[1].param_data.apc.apc.data[0] = 0x00;
        pc.data[0] = resume.affected.data[1];
        pc.data[1] = resume.affected.data[0];
        memcpy(&ies[1].param_data.apc.apc.data[1], pc.data,
               sizeof(MTP3_POINT_CODE));
        dpc    = MTP3_PC_GET_VALUE_TTC(resume.affected);
        family = FAMILY_JAPAN;
#endif

        sio = M3UA_SIO_0;
        
        /*
         * We have DPC, lookup for the Destination in 
         * the routing table. 
         * Check for all the Network Indicators
         *   INTERNATIONAL          0x00
         *   INTERNATIONAL-SPARE    0x40
         *   NATIONAL               0x80
         *   NATIONAL-SPARE         0xC0
         */
        while (count < max_look_ups)
        {
            dest = ROUTE_FindDestination(dpc, sio, family);
            if (dest != NULL)
            {
                break;
            }  
            sio  = sio + M3UA_SIO_40;
            count++;
        }
        if (dest == NULL)
        {
            return !ITS_SUCCESS; 
        }

        if (dest->status == DESTINATION_RESTRICTED)
        {
            ies[0].param_data.msgHeader.msgType = M3UA_MSG_DRST;
	    UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_DRST_SENT_ID);
        }
        else if(dest->status == DESTINATION_AVAILABLE)
        {
            ies[0].param_data.msgHeader.msgType = M3UA_MSG_DAVA;
	    UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_DAVA_SENT_ID);
        }
        
        ret = M3UA_EncodeMsg(ies, 2, &m3uaEvt, &M3UA_DAVA_Desc);
        if (ret != ITS_SUCCESS)
        {
            M3UA_ERROR(("Error Encoding DAVA msg\n"));
        }

        M3UA_Alarm(4034, __FILE__, __LINE__, NULL);

        break;
        
    }
    case MTP3_MSG_STATUS:
    {
        MTP3_STATUS status;
        MTP3_POINT_CODE pc;

        if (len > sizeof(MTP3_STATUS))
        {
            return ITS_EINVLEN;
        }

        memcpy(&status, data, sizeof(MTP3_STATUS));

        ies[0].param_id = M3UA_PRM_MSG_HDR;
        ies[0].param_length = sizeof(M3UA_MSG_HDR);
        ies[0].param_data.msgHeader.msgClass = UAL_CLASS_SNM;
        ies[0].param_data.msgHeader.version = UAL_GL_VERSION;
        ies[0].param_data.msgHeader.reserved = 0;

        ies[1].param_id = M3UA_PRM_AFFECTED_PC;
        ies[1].param_length = sizeof(M3UA_AFFECTED_PC);
        ies[1].param_data.apc.apc.mask = 0x00;

#if defined(CCITT) || defined(TTC)
        ies[1].param_data.apc.apc.data[0] = 0x00;
        pc.data[0] = status.affected.data[1];
        pc.data[1] = status.affected.data[0];
        memcpy(&ies[1].param_data.apc.apc.data[1], pc.data,
               sizeof(MTP3_POINT_CODE));
        
#elif defined(ANSI)
        ies[1].param_data.apc.apc.data[0] = 0x00;
        pc.data[0] = status.affected.data[2];
        pc.data[1] = status.affected.data[1];
        pc.data[2] = status.affected.data[0];
        memcpy(ies[1].param_data.apc.apc.data, pc.data, 
               sizeof(MTP3_POINT_CODE));
#elif defined(PRC)
        ies[1].param_data.apc.apc.data[0] = 0x00;
        pc.data[0] = status.affected.data[2];
        pc.data[1] = status.affected.data[1];
        pc.data[2] = status.affected.data[0];
        memcpy(ies[1].param_data.apc.apc.data, pc.data,
               sizeof(MTP3_POINT_CODE));
#endif
        if (status.cause == MTP3_STATUS_CONGESTED)
        {
            /* Send SCON message.*/
              
            ies[0].param_data.msgHeader.msgType = M3UA_MSG_SCON;

            ies[2].param_id = M3UA_PRM_CONGEST_LEVEL;
            ies[2].param_length = sizeof(M3UA_CONG_LEVEL);
            memset(&ies[2].param_data.congestion.level, 0, sizeof(M3UA_CONG_LEVEL));
            ies[2].param_data.congestion.level = status.congLevel;

            ret = M3UA_EncodeMsg(ies, 3, &m3uaEvt, &M3UA_SCON_Desc);
            if (ret != ITS_SUCCESS)
            {
                M3UA_ERROR(("Error Encoding SCOM msg\n"));
            }
            else
            {
	        UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_SCON_SENT_ID);
                M3UA_Alarm(4035, __FILE__, __LINE__, NULL);
            }
        }
        else if(status.cause == MTP3_STATUS_AUDIT)
        {
            /* Send DAUD message.*/
            ies[0].param_data.msgHeader.msgType = M3UA_MSG_DAUD;

            ret = M3UA_EncodeMsg(ies, 2, &m3uaEvt, &M3UA_DAUD_Desc);
            if (ret != ITS_SUCCESS)
            {
                M3UA_ERROR(("Error Encoding DAUD msg\n"));
            }
            else
            {
	        UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_DAUD_SENT_ID);
                M3UA_Alarm(4036, __FILE__, __LINE__, NULL);
            }
        }
        else
        {
            /* Send DUPU message. */
            if( status.cause == MTP3_STATUS_UPU_UNKNOWN ||
                  status.cause == MTP3_STATUS_UPU_UNEQUIP ||
                    status.cause == MTP3_STATUS_UPU_INACCESS )
            { 
                ies[0].param_data.msgHeader.msgType = M3UA_MSG_DUPU;
            }
            else /* Invalid Cause, hence ignore the message */
            {
                 return !ITS_SUCCESS;
            }
#if 0
            else
            {
                ies[0].param_data.msgHeader.msgType = M3UA_MSG_DRST;
            }
#endif

 #if defined(TTC)
             if((ies[0].param_data.msgHeader.msgType == M3UA_MSG_DRST) ||
                 (ies[0].param_data.msgHeader.msgType = M3UA_MSG_DUPU))
             {
                 return -1;
             }
 #endif

            ies[2].param_id     = M3UA_PRM_CAUSE_USER;
            ies[2].param_length = sizeof(M3UA_CAUSE_USER);

            if (status.cause == MTP3_STATUS_UPU_UNKNOWN)
            {
                ies[2].param_data.causeUsr.cause = M3UA_UNKNOWN_CAUSE;
            }
            else if (status.cause == MTP3_STATUS_UPU_UNEQUIP)
            {
                ies[2].param_data.causeUsr.cause = M3UA_UNEQUIP_REMOTE_USR;
            }
            else if (status.cause == MTP3_STATUS_UPU_INACCESS)
            {
                ies[2].param_data.causeUsr.cause = M3UA_INACCESS_REMOTE_USR;
            }
            else
            {
                M3UA_WARNING(("MTP3 Invalid Status Cause.\n"));
            }

            /*
             * FIXME: M3UA is not aware of which user is unavailable.
             *        Need to fix this in MTP3_STATUS indicator. 
             */
            ies[2].param_data.causeUsr.user = M3UA_USER_SCCP;

            if(ies[0].param_data.msgHeader.msgType == M3UA_MSG_DUPU)
            {
                ret = M3UA_EncodeMsg(ies, 3, &m3uaEvt, &M3UA_DUPU_Desc);
                if (ret != ITS_SUCCESS)
                {
                    M3UA_ERROR(("M3UA Encode failed for DUPU.\n"));
                }
                else
                {
	            UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_DUPU_SENT_ID);
                }
            }
            M3UA_Alarm(4038, __FILE__, __LINE__, NULL);
#if 0
            else
            {
                ret = M3UA_EncodeMsg(ies, 2, &m3uaEvt, &M3UA_DRST_Desc);
                if (ret != ITS_SUCCESS)
                {
                    M3UA_ERROR(("M3UA Encode failed for DRST.\n"));
                }
                else
                {
                    UAL_IncrementMIBStats(TRANSPORT_INSTANCE(m), UAL_PEG_DRST_SENT_ID);
                }
            }

            if(ies[0].param_data.msgHeader.msgType == M3UA_MSG_DRST)
            {
                M3UA_Alarm(4037, __FILE__, __LINE__, NULL);
            }
            else
            {
                M3UA_Alarm(4038, __FILE__, __LINE__, NULL);
            }
#endif
        }

        break;
    }
    default:
        break;
    }    

    evt->len = m3uaEvt.len;
    evt->data = m3uaEvt.data;
    evt->src = m3uaEvt.src;

    return (ret);
}

M3UADLLAPI int 
M3UA_EncodeRoutingContext(ITS_OCTET *data, ITS_USHORT *len, ITS_UINT *rkList, 
                         int size)
{
    int ret = ITS_SUCCESS, i;
    ITS_USHORT offset = 0;
    
    M3UA_DEBUG(("M3UA_EncodeRoutingContext: \n"));

    if (rkList == NULL)
    {
        *len = 0;
    }
    else
    {
        for (i = 0; i<size; i++)
        {
            rkList[i] = SOCK_HToNL(rkList[i]);
            memcpy(&data[offset], &rkList[i], sizeof(ITS_UINT));
            offset += sizeof(ITS_UINT);      
        }

        *len = offset;

    }
    return ret;
}


M3UADLLAPI int
M3UA_DecodeRoutingContext(ITS_OCTET *data, ITS_USHORT len, ITS_UINT *rkList,
                         int *size)
{
    int ret = ITS_SUCCESS;
    int num = len / sizeof(ITS_UINT);

    M3UA_DEBUG(("M3UA_DecodeRoutingContext: \n"));

    *size = 0;

    if (!(len % sizeof(ITS_UINT)) && (num < M3UA_MAX_RK_NUM))
    {
        int i;

        for (i = 0; i < num; i++)
        {
            memcpy(&rkList[i], data, sizeof(ITS_UINT));
            rkList[i] = SOCK_NToHL(rkList[i]);
            data += sizeof(ITS_UINT);
            (*size)++;
        }
    }
    else
    {
        M3UA_Alarm(4042, __FILE__, __LINE__, NULL);
        return -1; /* TODO pick error code */
    }

    return ret;
}


/*
 * UAL Callback functions
 */

M3UADLLAPI void
UAL_RoutingNotification(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    //TRANSPORT_Control *tc      = (TRANSPORT_Control *)object;
    UAL_CB_Context *ctxt  = (UAL_CB_Context *)callData;
    int            i, ret = ITS_SUCCESS;
    ITS_OCTET      mType  = SCCP_MSG_UDT;
    ITS_SCCP_IE    ies[10], respIes[10];
    int            ieCount = 0;
    SCCP_DATA      *data   = NULL;
    ITS_OCTET      dlen = 0, type, sccpMsg[500];
    ITS_USHORT     sccpLen = 0;
    SCCP_ADDR      *clp = NULL, *cdp = NULL;
    MTP3_HEADER    hdr, resp;
    ITS_EVENT      mtp3Evt, sccpEvt;
    ITS_UINT       tmp = 0;

    M3UA_DEBUG(("UAL_RoutingNotification: \n"));

    switch (UAL_CB_CTXT_TYPE(ctxt))
    {
        case UAL_CB_RT_FAIL_CTXT:
        {
            /* Now decode the message */
            mtp3Evt.len = UAL_CB_CTXT_MSU_LEN(ctxt);
            mtp3Evt.data = UAL_CB_CTXT_MSU_DATA(ctxt);

            ret = MTP3_Decode(&mtp3Evt, &type, &hdr, sccpMsg, &sccpLen);
            if (ret != ITS_SUCCESS)
            {
                M3UA_ERROR(("Failed to decode MTP3 message.\n"));

                return;
            }

            ret = SCCP_DecodeMTP3(sccpMsg, sccpLen, &mType, ies,
                                    &ieCount, &SCCP_UDT_Desc);
            if (ret != ITS_SUCCESS)
            {
                M3UA_ERROR(("Failed to DECODE SCCP Message \n"));

                break;
            }

            for (i = 0; i < ieCount; i++)
            {
                if (ies[i].param_id == SCCP_PRM_DATA)
                {
                    data = &ies[i].param_data.userData;
                    dlen = ies[i].param_length;
                }
                else if (ies[i].param_id == SCCP_PRM_CALLING_PARTY_ADDR)
                {
                    clp = &ies[i].param_data.callingPartyAddr;
                }
                else if (ies[i].param_id == SCCP_PRM_CALLED_PARTY_ADDR)
                {
                    cdp = &ies[i].param_data.calledPartyAddr;
                }
            }

            /* now build the Routing Label */
            resp.sio = hdr.sio;
            tmp = MTP3_RL_GET_DPC_VALUE(hdr.label);

            MTP3_RL_SET_OPC_VALUE(resp.label, tmp);
            tmp = MTP3_RL_GET_OPC_VALUE(hdr.label);

            MTP3_RL_SET_DPC_VALUE(resp.label, tmp);
            MTP3_RL_SET_SLS(resp.label, MTP3_RL_GET_SLS(hdr.label));

            /* return cause */
            respIes[0].param_id = SCCP_PRM_RETURN_CAUSE;
            respIes[0].param_length = sizeof(SCCP_RET_CAUSE);
            respIes[0].param_data.returnCause.cause = 0x01;

            /* calledParty */
            respIes[1].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
            respIes[1].param_length = sizeof(SCCP_ADDR);
            memcpy(&respIes[1].param_data.calledPartyAddr, clp, sizeof(SCCP_ADDR));

            /* callingParty */
            respIes[2].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
            respIes[2].param_length = sizeof(SCCP_ADDR);
            memcpy(&respIes[2].param_data.callingPartyAddr, cdp, sizeof(SCCP_ADDR));

            /* copy in data */
            respIes[3].param_id = SCCP_PRM_DATA;
            respIes[3].param_length = dlen;
            memcpy(respIes[3].param_data.userData.data, data->data, dlen);

            ret = SCCP_EncodeMTP3(sccpMsg, &sccpLen, SCCP_MSG_UDTS, respIes, 4,
                              &SCCP_UDTS_Desc);
            if (ret != ITS_SUCCESS)
            {
                M3UA_ERROR((" Failed to ENCODE SCCP Message \n"));

                break;
            } 

            ret = MTP3_Encode(&sccpEvt, 0x21, &resp, sccpMsg, sccpLen);

            sccpEvt.src = ITS_MTP3_SRC;

            ret = TRANSPORT_PutEvent(ITS_SCCP_SRC, &sccpEvt);
            if (ret != ITS_SUCCESS)
            {
                M3UA_ERROR((" Failed to Send UDTS Message \n"));
            }
        }

        case UAL_CB_INVALID_CTXT:
        case UAL_CB_ASP_CTXT:
        case UAL_CB_AS_CTXT:
        default:
            break;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Registering puase/resume/status callbacks.
 *      and addition of debug console feature.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name        Date        Reference      Description
 * -----------------------------------------------------------------------------
 *
 * gdevanand   04-06-2005  BugId:1557     Addition of debug console feature.
 * Mani        05-05-2005  BugId:1773
 * kramesh     05-01-2008  BugId:1033	  Propagated TCS Sigtran 4 assoc issue. 
 *
 *  See Also:
 ****************************************************************************/
static void
UALTRAN_Register(ITS_POINTER object, ITS_POINTER userData,
                 ITS_POINTER callData)
{
    TRANSPORT_Control *tc = (TRANSPORT_Control *)object;
    ITS_Class dbClass;

    if (!started)
    {
    	started = ITS_TRUE;

    /* Since M3UA has no transport of its own, this is being taken as */
    /* the starting point. This callback will always be hit, so       */
    /* tracing component to M3UA is being added here.                 */

    	if ((M3UA_TraceData = TRACE_Constructor("M3UA",
                                             M3UA_TraceMap, 4)) == NULL)
        {
            /* M3UA failed to Intialize -  No Memory. */
            started = ITS_FALSE;
            return;
        }

        if ((dbClass = ITS_FindFeature(DBC_CLASS_NAME)) != NULL)
        {
            DBC_AddDoCommand(M3UA_Console);
        }
        InitTraceSettings(tc);

        AddCommitCallback("M3UA",M3UA_Commit);
    }

}                        
                         
static void              
UALTRAN_Deregister(ITS_POINTER object, ITS_POINTER userData,
                   ITS_POINTER callData)
{                           
    //TRANSPORT_Control *tc = (TRANSPORT_Control *)object;

    started = ITS_FALSE;
                            
    M3UA_DEBUG(("UALTRAN_Deregister: \n"));

    return;
}                           
                            
M3UADLLAPI
void M3UA_RegisterTransportCallbacks()
{                           
    CALLBACK_AddCallback(TRANSPORT_registrations, UALTRAN_Register, NULL);
    CALLBACK_AddCallback(TRANSPORT_deregistrations, UALTRAN_Deregister, NULL);
    return;         
}

M3UADLLAPI
void  M3UA_DeregisterTransportCallbacks()
{
    CALLBACK_RemCallback(TRANSPORT_registrations, UALTRAN_Register, NULL);
    CALLBACK_RemCallback(TRANSPORT_deregistrations, UALTRAN_Deregister, NULL);

    return;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 * -----------------------------------------------------------------------------
 * Name      Date        Reference               Description
 * -----------------------------------------------------------------------------
 * ssingh    04-01-2005  BugId: 924/770/818   Bug Fix propagation.
 *                              826/861/867   changes for PAUSE/RESUME
 *                                            propagation at ASP.
 * kramesh   22-04-2008  BugID: 1095          Propagated TCS Issue.
 *                                      	  Pause Not being propagated
 *                                            After 4 Duna sent to each association
 *                                            from STP.        
 *
 ****************************************************************************/
static void
PauseCallback(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    TRANSPORT_Control *tc  = (TRANSPORT_Control *)object;
    ITS_UINT          type = UAL_TRANS_IND;
    ITS_UINT          dpc  = 0x00;
    UALMgntData       *ualData = (UALMgntData *)callData;
    MTP3_PAUSE_RESUME pause;

    memset(&pause, 0, sizeof(MTP3_PAUSE_RESUME));

    if (ualData)
    {
        type = ualData->type;
        dpc  = ualData->cdata.mtp3_info.pc;
    }

    /*
     * REWORK:
     * 1. Do not return if this callback is invoked by Transport.
     * 2. Check Link and LinkSet state.
     * 3. Mark the routes to UP/DOWN based on the links.
     *
     * 4. HANDLE Destination AUDIT from ASP/IPSP.
     * 5. Invoke TRANSPORT_SetState(ITS_FALSE) before deleting PENDING QUEUE.
     *
     */

    if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
    {
        M3UA_WARNING(("PauseCallback: link lock failed\n"));

        return;
    }

    if ((TRANSPORT_MASK(tc) & ITS_SS7_MASK) && TRANSPORT_RES(tc))
    {
        SS7_LinkPtr link;
        ITS_BOOLEAN pauseSent = ITS_FALSE;

        for (link = TRANSPORT_SS7_INFO(tc).linkInfo;
             link != NULL; link = link->next)
        {
            DSMQUEUE_Entry *tmp;
            ITS_UINT       count;

            if (type == UAL_TRANS_IND)
            {
                LINK_SetLinkState(link, ITS_FALSE);
            }

            for (count = 0, tmp = DSMQUEUE_HEAD(link->linkSet->routes);
                 tmp != NULL && count < DSMQUEUE_COUNT(link->linkSet->routes);
                 count++, tmp = DSMQUEUE_NEXT(link->linkSet->routes, tmp) )
            {
                ROUTE_Info      *rinfo;
                ROUTE_MatchInfo minfo;
                //SS7_Destination *dest;

                /* select one of concerned destinations */
                memcpy(&rinfo, tmp->data, sizeof(rinfo));

                /*
                 * We are interested in remote routes and affected
                 * dpc from DUNA in routing table.
                 */
                if (rinfo == NULL || rinfo->basic.type != REMOTE_ROUTE || 
                    (dpc != 0x00 && dpc != rinfo->basic.dpc))
                {
                    continue;
                }

                minfo.basic    = rinfo->basic;
                minfo.linkSet  = link->linkSet->linkSet;
                minfo.linkCode = link->linkCode;

                minfo.priority = ITS_SS7_DEFAULT_PRI;
                minfo.sls      = ITS_SS7_DEFAULT_SLS;
                
                if (ROUTE_SetRouteContextInfoStatus(&minfo, ITS_FALSE) != ITS_SUCCESS)
                {
                    /* route doesn't exist */
                    continue;
                }

                if (!pauseSent)
                {
                    ualData->type = UAL_MTP3_RESULT;
                    M3UA_DEBUG(("PauseCallbacks: setting state PC: %08x\n",
                                 rinfo->basic.dpc));

                    ualData->cdata.info.result = ITS_SUCCESS;
                    ualData->cdata.info.pc     = link->linkSet->lpc;
                    ualData->cdata.info.sio    = link->linkSet->ni;
     
                    M3UA_Pause((MTP3_PAUSE_RESUME *)userData, ualData,
                                (SCTPTRAN_Manager *)tc);
                    pauseSent = ITS_TRUE;
                }
            }
        }
    }

    ROUTE_UnlockWrite(routeRWLock);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name      Date        Reference               Description
 * -----------------------------------------------------------------------------
 * ssingh    04-01-2005  BugId: 924/770/818   Bug Fix propagation.
 *                              826/861/867   changes for PAUSE/RESUME
 *                                            propagation at ASP.
 *
 ****************************************************************************/
static void
ResumeCallback(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
   TRANSPORT_Control *tc      = (TRANSPORT_Control *)object;
   UALMgntData       *ualData = (UALMgntData *)callData;
   UAL_MTP3_TYPE     type     = UAL_TRANS_IND;
   ITS_UINT          dpc      = 0x00;
   MTP3_PAUSE_RESUME resume;

   M3UA_DEBUG (("ResumeCallback called:"));

   memset(&resume, 0, sizeof(MTP3_PAUSE_RESUME));

   if (ualData)
   {
       type = ualData->type;
       dpc  = ualData->cdata.mtp3_info.pc;
   }

   if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
   {
       M3UA_WARNING(("ResumeCallback: link lock failed\n"));

       return;
   }

   if (TRANSPORT_MASK(tc) & ITS_SS7_MASK && TRANSPORT_RES(tc))
   {
        SS7_LinkPtr link;

        for (link = TRANSPORT_SS7_INFO(tc).linkInfo;
             link != NULL; link = link->next)
        {
            DSMQUEUE_Entry *tmp;
            ITS_UINT       count;
            ITS_BOOLEAN    flag;
            //ITS_BOOLEAN    firstUp = ITS_FALSE;

            LINK_GetLinkState(link, &flag);

            if (!flag)
            {
                LINK_SetLinkState(link, ITS_TRUE);
            }

            for (count = 0, tmp = DSMQUEUE_HEAD(link->linkSet->routes);
                 tmp != NULL && count < DSMQUEUE_COUNT(link->linkSet->routes);
                 count++, tmp = DSMQUEUE_NEXT(link->linkSet->routes, tmp) )
            {
                ROUTE_Info      *rinfo;
                ROUTE_MatchInfo minfo;
                SS7_Destination *dest;

                /* select one of concerned destinations */
                memcpy(&rinfo, tmp->data, sizeof(rinfo));

                if (rinfo == NULL || rinfo->basic.type != REMOTE_ROUTE ||
                    (dpc != 0x00 && dpc != rinfo->basic.dpc))
                {
                    continue;
                }

                minfo.basic    = rinfo->basic;
                minfo.linkSet  = link->linkSet->linkSet;
                minfo.linkCode = link->linkCode;

                minfo.priority = ITS_SS7_DEFAULT_PRI;
                minfo.sls      = ITS_SS7_DEFAULT_SLS;

                if (ROUTE_SetRouteContextInfoStatus(&minfo, ITS_TRUE) != ITS_SUCCESS)
                {
                    /* route doesn't exist */
                    continue;
                }

                dest = ROUTE_FindDestination(minfo.basic.dpc, 
                                             minfo.basic.criteria.sio & ROUTE_NI_MASK,
                                             minfo.basic.family);

                /* determine if this is a newly up route */
                if (dest != NULL)
                {
		    dest->status = DESTINATION_AVAILABLE;

                    ualData->type = UAL_MTP3_RESULT;
                    ualData->cdata.info.result = ITS_SUCCESS;
                    ualData->cdata.info.pc     = link->linkSet->lpc;
                    ualData->cdata.info.sio    = link->linkSet->ni;

                    M3UA_Resume((MTP3_PAUSE_RESUME *)userData, ualData,
                                (SCTPTRAN_Manager *)tc);
                }
            }
        }
    }

    ROUTE_UnlockWrite(routeRWLock);

    return;
}

static void
StatusCallback(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    TRANSPORT_Control *tc = (TRANSPORT_Control *)object;

    CALLBACK_CallCallbackList(MTP3_ManagementCallbacks,
                              (ITS_POINTER)tc,
                              callData);
 
    return;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function initializes the M3UA transport subsytem.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the M3UA subsystem is initialized correctly, ITS_SUCCESS is
 *          returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ClassInitialize(ITS_Class objClass)
{
    ITS_Class ualClass;

    M3UA_DEBUG(("Initialize\n"));

    M3UA_RegisterTransportCallbacks();

    if ( (ualClass = ITS_FindFeature(UAL_CLASS_NAME)) == NULL)
    {
        if (ITS_AddFeature(itsUAL_Class) != ITS_SUCCESS)
        {
            M3UA_ERROR(("ClassInitialize: failed to add UAL featute class.\n"));
        }
    }
    else
    {
        M3UA_WARNING(("ClassInitialize: UAL Class feature exists.\n"));
    }

    if (ITS_InitializeClass(itsUAL_Class) != ITS_SUCCESS)
    {
        M3UA_ERROR(("ClassInitialize: UAL class initialization failed.\n"));
    }

    CALLBACK_AddCallback(__UAL_MgntCallBack,
                         UAL_RoutingNotification,
                         NULL);

    return SCTPTRAN_RegisterCodec(M3UA_CLASS_NAME, SCTP_PAYLOAD_M3UA,
                                  MTP3_To_M3UA_Codec, M3UA_To_MTP3_Codec);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function terminates the M3UA transport subsystem.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_Initialize()
 ****************************************************************************/
static void
ClassTerminate(ITS_Class objClass)
{
    M3UA_DEBUG(("Terminate:\n"));

    M3UA_DeregisterTransportCallbacks();

    SCTPTRAN_DeregisterCodec(M3UA_CLASS_NAME);
}

M3UADLLAPI ITS_ClassRec itsM3UA_ClassRec =
{
    /* core part */
    {
        NULL,                           /* no superclass */
        0,                              /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        M3UA_CLASS_NAME,                /* class name */
        ClassInitialize,                /* class init */
        ClassTerminate,                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ITS_INST_NO_CONST,              /* instance create */
        ITS_INST_NO_DEST,               /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    }
};

M3UADLLAPI ITS_Class itsM3UA_Class = &itsM3UA_ClassRec;
 
/* M3UA Alarms */

ITS_UINT M3UA_AlarmLevel = ALARM_LVL_OFF;

ALARM_FORMAT_SUBSYS(M3UA, 4027,
                    "Received DUNA",
                    ALARM_LVL_MINOR,         "M3UA_To_MTP3_Codec",
                    "M3UA", ITS_FALSE);

ALARM_FORMAT_SUBSYS(M3UA, 4028,
                    "Received DAVA",
                    ALARM_LVL_INFO,         "M3UA_To_MTP3_Codec",
                    "M3UA", ITS_FALSE);

ALARM_FORMAT_SUBSYS(M3UA, 4029,
                    "Received SCON",
                    ALARM_LVL_MINOR,         "M3UA_To_MTP3_Codec",
                    "M3UA", ITS_FALSE);

ALARM_FORMAT_SUBSYS(M3UA, 4030,
                    "Received DAUD",
                    ALARM_LVL_MINOR,         "M3UA_To_MTP3_Codec",
                    "M3UA", ITS_FALSE);

ALARM_FORMAT_SUBSYS(M3UA, 4031,
                    "Received DRST",
                    ALARM_LVL_MINOR,         "M3UA_To_MTP3_Codec",
                    "M3UA", ITS_FALSE);

ALARM_FORMAT_SUBSYS(M3UA, 4032,
                    "Received DUPU",
                    ALARM_LVL_MINOR,         "M3UA_To_MTP3_Codec",
                    "M3UA", ITS_FALSE);

ALARM_FORMAT_SUBSYS(M3UA, 4033,
                    "Sent DUNA",
                    ALARM_LVL_MINOR,         "MTP3_To_M3UA_Codec",
                    "M3UA", ITS_FALSE);

ALARM_FORMAT_SUBSYS(M3UA, 4034,
                    "Sent DAVA",
                    ALARM_LVL_MINOR,         "MTP3_To_M3UA_Codec",
                    "M3UA", ITS_FALSE);

ALARM_FORMAT_SUBSYS(M3UA, 4035,
                    "Sent SCON",
                    ALARM_LVL_MINOR,         "MTP3_To_M3UA_Codec",
                    "M3UA", ITS_FALSE);

ALARM_FORMAT_SUBSYS(M3UA, 4036,
                    "Sent DAUD",
                    ALARM_LVL_MINOR,         "MTP3_To_M3UA_Codec",
                    "M3UA", ITS_FALSE);

ALARM_FORMAT_SUBSYS(M3UA, 4037,
                    "Sent DRST",
                    ALARM_LVL_MINOR,         "MTP3_To_M3UA_Codec",
                    "M3UA", ITS_FALSE);

ALARM_FORMAT_SUBSYS(M3UA, 4038,
                    "Sent DUPU",
                    ALARM_LVL_MINOR,         "MTP3_To_M3UA_Codec",
                    "M3UA", ITS_FALSE);

ALARM_FORMAT_SUBSYS(M3UA, 4039,
                    "Received invalid message type",
                    ALARM_LVL_MINOR,         "M3UA_To_MTP3_Codec",
                    "M3UA", ITS_TRUE);

ALARM_FORMAT_SUBSYS(M3UA, 4040,
                    "M3UA Message Decode Failed",
                    ALARM_LVL_MAJOR,         "M3UA_DecodeMsg",
                    "M3UA", ITS_TRUE);

ALARM_FORMAT_SUBSYS(M3UA, 4041,
                    "M3UA Message Encode Failed",
                    ALARM_LVL_MAJOR,         "M3UA_EncodeMsg",
                    "M3UA", ITS_TRUE);

ALARM_FORMAT_SUBSYS(M3UA, 4042,
                    "M3UA Routing Context Decode Failed",
                    ALARM_LVL_MINOR,         "M3UA_DecodeRoutingContext",
                    "M3UA", ITS_TRUE);

ALARM_FORMAT_SUBSYS(M3UA, 4043,
                    "M3UA Message in Invalid State",
                    ALARM_LVL_MAJOR,         "MTP3_To_M3UA_Codec",
                    "M3UA", ITS_TRUE);

ALARM_FORMAT_SUBSYS(M3UA, 4044,
                    "M3UA Management Message in Invalid Stream",
                    ALARM_LVL_MAJOR,         "M3UA_To_MTP3_Codec",
                    "M3UA", ITS_TRUE);

ALARM_FORMAT_SUBSYS(M3UA, 4045,
                    "M3UA Message with Invalid Message Length",
                    ALARM_LVL_MAJOR,         "M3UA_To_MTP3_Codec",
                    "M3UA", ITS_TRUE);

ALARM_Format *M3UA_Alarms[] =
{
    &ALARM_M3UA4027,
    &ALARM_M3UA4028,
    &ALARM_M3UA4029,
    &ALARM_M3UA4030,
    &ALARM_M3UA4031,
    &ALARM_M3UA4032,
    &ALARM_M3UA4033,
    &ALARM_M3UA4034,
    &ALARM_M3UA4035,
    &ALARM_M3UA4036,
    &ALARM_M3UA4037,
    &ALARM_M3UA4038,
    &ALARM_M3UA4039,
    &ALARM_M3UA4040,
    &ALARM_M3UA4041,
    &ALARM_M3UA4042,
    &ALARM_M3UA4043,
    &ALARM_M3UA4044,
    &ALARM_M3UA4045
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method issues a UAL alarm.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.       
 *                  
 *  Return Value:
 *
 *  Notes:          
 *                  
 *  See Also:       
 ****************************************************************************/
void
M3UA_Alarm(int which, const char *file, const int line,
           char *format, ...)
{
    va_list alist;
    ALARM_Format *fmt;

    ITS_C_ASSERT(which >= M3UA_ALARM_START &&
                 which <= M3UA_ALARM_END);

    fmt = M3UA_Alarms[which - M3UA_ALARM_START];

    if (fmt->severity > M3UA_AlarmLevel)
    {
        return;
    }

    va_start(alist, format);

    ALARM_VIssueAlarm(itsALARM_Class, fmt, file, line, format, alist);

    va_end(alist);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Initialise M3UA trace settings.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.       
 *                  
 *  Return Value:
 *
 *  Notes:          
 *                  
 *  See Also:       
 ****************************************************************************/
static void
InitTraceSettings(TRANSPORT_Control* tc)
{
     /*
     * determine tracing from INI files
     */
    if (TRANSPORT_RES(tc) != NULL)
    {
        char value[ITS_PATH_MAX];
        RESFILE_Manager *res = TRANSPORT_RES(tc);
        char *name = "M3UA";

        /* critical */
        if (RESFILE_GetKeyValueOf(res, name, M3UA_TRACE_CRITICAL_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, M3UA_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_CRITICAL_STRING,
                                           M3UA_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_CRITICAL_STRING,
                                           M3UA_STDOUT_STRING, ITS_FALSE);

            }
            if (strstr(value, M3UA_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_CRITICAL_STRING,
                                           M3UA_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_CRITICAL_STRING,
                                           M3UA_FILE_STRING, ITS_FALSE);

            }
            if (strstr(value, M3UA_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_CRITICAL_STRING,
                                           M3UA_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_CRITICAL_STRING,
                                           M3UA_SYSLOG_STRING, ITS_FALSE);

            }
            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(M3UA_TraceData,
                                          M3UA_CRITICAL_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(M3UA_TraceData,
                                          M3UA_CRITICAL_STRING, ITS_FALSE);
            }
        }

        /* error */
        if (RESFILE_GetKeyValueOf(res, name, M3UA_TRACE_ERROR_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, M3UA_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_ERROR_STRING,
                                           M3UA_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_ERROR_STRING,
                                           M3UA_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, M3UA_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_ERROR_STRING,
                                           M3UA_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_ERROR_STRING,
                                           M3UA_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, M3UA_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_ERROR_STRING,
                                           M3UA_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_ERROR_STRING,
                                           M3UA_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(M3UA_TraceData,
                                          M3UA_ERROR_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(M3UA_TraceData,
                                          M3UA_ERROR_STRING, ITS_FALSE);
            }
        }

        /* warning */
        if (RESFILE_GetKeyValueOf(res, name, M3UA_TRACE_WARNING_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, M3UA_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_WARNING_STRING,
                                           M3UA_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_WARNING_STRING,
                                           M3UA_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, M3UA_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_WARNING_STRING,
                                           M3UA_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_WARNING_STRING,
                                           M3UA_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, M3UA_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_WARNING_STRING,
                                           M3UA_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_WARNING_STRING,
                                           M3UA_SYSLOG_STRING, ITS_FALSE);

            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(M3UA_TraceData,
                                          M3UA_WARNING_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(M3UA_TraceData,
                                          M3UA_WARNING_STRING, ITS_FALSE);
            }
        }

        /* debug */
        if (RESFILE_GetKeyValueOf(res, name, M3UA_TRACE_DEBUG_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, M3UA_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_DEBUG_STRING,
                                           M3UA_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_DEBUG_STRING,
                                           M3UA_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, M3UA_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_DEBUG_STRING,
                                           M3UA_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_DEBUG_STRING,
                                           M3UA_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, M3UA_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_DEBUG_STRING,
                                           M3UA_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_DEBUG_STRING,
                                           M3UA_SYSLOG_STRING, ITS_FALSE);

            }
            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(M3UA_TraceData,
                                          M3UA_DEBUG_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(M3UA_TraceData,
                                          M3UA_DEBUG_STRING, ITS_FALSE);
            }
        }
    }
}


/******************************************************************************
 * Purpose: This function checks if the AuditTimersTable has a valid entry (timer)
 *          for the affectedPC, which has come in current SSNM (SCON/DUNA/DAVA/DRST)
 *          message received.
 *          If yes, that means SSNM has come in response to the DAUD message
 *          for which a timer was started, which has not expired yet.
 *
 *          If no entry is found then a AuditTimer needs to be started in
 *          anticipation of getting a update for the current SSNM we have (except DAVA)
 *
 *          The SSNM message is discarded if the ASP is not in ASP_ACTIVE state
 *
 * Parameters:
 *     isDavaMsg [in] true, if the function is called for
 *                                   receipt of DAVA, false otherwise
 *     affectedPC [in] specifies value of the PC in the SSNM, this is used as a key
 *                            to find the entry in the AuditTimersTable
 *
 * return value:
 *     ITS_SUCCESS if everything goes fine, !ITS_SUCCESS otherwise.
 *****************************************************************************/
int
CheckAndStartOrStopAuditTimer(ITS_POINTER inStatus, ITS_USHORT trid, ITS_BOOLEAN isDavaMsg)
{
    int retVal = ITS_SUCCESS;
    ITS_SERIAL *timerVal = NULL;
    UAL_ASP_STATE   aspState;

    /* Check for ASP state before processing */
    retVal = UAL_GetASPState(trid, &aspState);
    if (retVal == ITS_SUCCESS)
    {
       if (aspState != UAL_ASP_ACTIVE)
       {
          M3UA_ERROR(("CheckAndStartOrStopAuditTimer: Message discarded, ASP state = %d\n", aspState));
          return ITS_EBADSTATE;
       }
    }
    else
    {
        M3UA_ERROR(("CheckAndStartOrStopAuditTimer: Error in getting ASP state\n"));
        return retVal;
    }

    MTP3_STATUS status;
    memcpy(&status, inStatus, sizeof(MTP3_STATUS));

    ITS_UINT pc = MTP3_PC_GET_VALUE(status.affected);

    M3UA_DEBUG(("CheckAndStartOrStopAuditTimer: Checking for PC=0x%0x\n", pc));
    /* Stop the Audit Timer for the PC in case of Both DUNA/DAVA */
    if(AuditTimersTable_FindEntry(pc, &timerVal) == ITS_SUCCESS)
    {
        if (TIMERS_CancelTimer(*timerVal) != ITS_SUCCESS)
        {
            M3UA_ERROR(("CheckAndStartOrStopAuditTimer: error in TIMERS_CancelTimer()\n"));
            return !ITS_SUCCESS;
        }

        M3UA_DEBUG(("CheckAndStartOrStopAuditTimer: Got an update from SGP, for PC=0x%0x, "
                    "canceled the timer=%d\n",pc, *timerVal));

        if(AuditTimersTable_RemoveEntry(pc) != ITS_SUCCESS)
        {
            M3UA_ERROR(("CheckAndStartOrStopAuditTimer: error in AuditTimersTable_RemoveEntry()\n"));
            return !ITS_SUCCESS;
        }
    }
    /* we donot start a timer if the message is a DAVA message */
    if(isDavaMsg == ITS_FALSE)
    {
        UAL_TimerCtx timerCtxt;
        memset(&timerCtxt, 0, sizeof(UAL_TimerCtx));

        /* extract required data from the timerCtxt */
        timerCtxt.type = UAL_DAUD_MESG;
        timerCtxt.len = sizeof(MTP3_STATUS);
        memcpy(timerCtxt.msg, &status, timerCtxt.len);

        /* NOTE: start a timer only if the congLevel
         * is ITS_SUCCESS, which is set to !ITS_SUCCESS
         * only on receipt of a SCON with congLevel = 0 */
        if (status.congLevel == ITS_SUCCESS)
        {
            ITS_SERIAL daudTimer
                           = TIMERS_StartTimer(UAL_MANAGER_INSTANCE,
                                               UAL_GL_AUD_TIMER, /*no of secs*/
                                               (void *)&timerCtxt,   /* context for timer*/
                                               sizeof(UAL_TimerCtx));

            M3UA_DEBUG(("CheckAndStartOrStopAuditTimer:Started timer=%d, for PC=0x%0x\n",daudTimer, pc));

            /* Adding timer entry in hash table */
            if(AuditTimersTable_AddEntry(pc, &daudTimer) != ITS_SUCCESS)
            {
                    M3UA_ERROR(("CheckAndStartOrStopAuditTimer: error in AuditTimersTable_AddEntry()\n"));
                retVal = !ITS_SUCCESS;
            }
        }
        else
        {
            M3UA_DEBUG(("Cong Level=0 in SCON msg, not starting audit Timer\n"));
            return !ITS_SUCCESS;
        }
    }
    return retVal;
}

/******************************************************************************
 * Purpose: This function checks to handle Audit timer Expiry 
 *
 * Parameters:
 *     Timer data and length
 *
 * return value:
 *     ITS_SUCCESS if everything goes fine, !ITS_SUCCESS otherwise.
 *****************************************************************************/
ITS_INT
AuditTimersTable_TimerExpiry(UAL_TimerCtx ctx)
{
    ITS_INT     ret = 0;
    MTP3_STATUS status;
    ITS_UINT    affectedPC;
    MTP3_HEADER hdr;
    ITS_EVENT   m3uaMsg;

    memcpy(&status, ctx.msg, ctx.len);

    affectedPC = MTP3_PC_GET_VALUE(status.affected);

    M3UA_DEBUG(("AuditTimersTable_TimerExpiry: DAUD timer Expiry for PC=0x%02x\n",
                 affectedPC));

    memset(&hdr, 0, sizeof(MTP3_HEADER));

    ret = MTP3_Encode(&m3uaMsg, MTP3_MSG_STATUS, &hdr, (ITS_OCTET*)&status,
                      sizeof(MTP3_STATUS));
    if (ret != ITS_SUCCESS)
    {
        M3UA_ERROR(("AuditTimersTable_TimerExpiry: Could not Encode STATUS(DAUD) ind\n"));
        return ret;
    }

    ret = TRANSPORT_PutEvent(UAL_MANAGER_INSTANCE, &m3uaMsg);
    if (ret != ITS_SUCCESS)
    {
        M3UA_ERROR(("AuditTimersTable_TimerExpiry: Could not send event, code %d", ret));
        return ret;
    }

    /* reset the timer */
    if(AuditTimersTable_RemoveEntry(affectedPC) != ITS_SUCCESS)
    {
        M3UA_ERROR(("AuditTimersTable_TimerExpiry: Error removing Audit Timer Entry\n"));
        ret = !ITS_SUCCESS;
    }

    ITS_SERIAL daudTimer = TIMERS_StartTimer(UAL_MANAGER_INSTANCE,
                                             UAL_GL_AUD_TIMER,
                                             (void *)&ctx,
                                             sizeof(UAL_TimerCtx));

    M3UA_DEBUG(("AuditTimersTable_TimerExpiry: Timer started %d for PC=0x%02x\n", 
                 daudTimer, affectedPC));

    if(AuditTimersTable_AddEntry(affectedPC, &daudTimer) != ITS_SUCCESS)
    {
        M3UA_ERROR(("AuditTimersTable_TimerExpiry: Error Adding Audit Timer Entry"));
        ret = !ITS_SUCCESS;
    }

    return ret;
}
