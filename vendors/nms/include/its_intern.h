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
 *  ID: $Id: its_intern.h,v 9.4.24.1 2010/04/14 11:40:51 ssingh Exp $
 *
 * LOG: $Log: its_intern.h,v $
 * LOG: Revision 9.4.24.1  2010/04/14 11:40:51  ssingh
 * LOG: put a check for configuration.template for protocol
 * LOG:
 * LOG: Revision 9.4  2007/01/11 12:43:44  yranade
 * LOG: Merge changes from 6.5.3 and Lucent branches
 * LOG:
 * LOG: Revision 9.3.6.1  2006/09/26 21:58:11  omayor
 * LOG: Propagated fix for ticket #1217. BCGI: MTP2 hangs when congestion
 * LOG: indication is received from NMS.
 * LOG:
 * LOG: Revision 9.3.8.1  2006/08/23 21:21:55  omayor
 * LOG: Fix for trouble ticket 1217. When congestion indications are received from
 * LOG: NMS MTP2, we must reply with the same congestion level. The congestion
 * LOG: level is manitained in the context on a per link basis.
 * LOG:
 * LOG: Revision 9.3  2005/07/20 23:02:40  randresol
 * LOG: Add NMSHandleNotification function for the asynchonous library.
 * LOG:
 * LOG: Revision 9.2  2005/05/06 10:07:04  mmanikandan
 * LOG: PR6.5.1 Validation Bug(1793) Fix.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:43  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:55:04  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.10.1.12.2  2005/01/05 12:22:29  craghavendra
 * LOG: Syslog Enhancement.
 * LOG:
 * LOG: Revision 7.2.10.1.12.1  2005/01/03 15:52:12  snagesh
 * LOG: MTP2 OAM changes
 * LOG:
 * LOG: Revision 7.2.10.1  2004/07/09 07:26:39  dsatish
 * LOG: Merging activity for timeslot changes
 * LOG:
 * LOG: Revision 7.2  2002/11/26 21:01:26  ngoel
 * LOG: merge prc changes from pr6.2
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:51  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.5  2002/08/08 19:28:28  sjaddu
 * LOG: Merge from ISUP_PR7 to Current.
 * LOG:
 * LOG: Revision 6.4  2002/07/05 16:38:26  mmiers
 * LOG: Clean up for chinese TCAP
 * LOG:
 * LOG: Revision 6.3  2002/05/20 16:30:38  sjaddu
 * LOG: Merge from PR6.
 * LOG:
 * LOG: Revision 6.2  2002/05/16 15:53:32  hcho
 * LOG: Modifications for v3_6.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:54  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.14.2.3  2002/05/13 21:32:40  hcho
 * LOG: Add dual protocols and Queue flag.
 * LOG:
 * LOG: Revision 5.14.2.2  2002/04/19 19:40:30  hcho
 * LOG: Isup macros needed.
 * LOG:
 * LOG: Revision 5.14.2.1  2002/04/19 15:01:58  sjaddu
 * LOG: Add a #define for MTP3_SVCID.
 * LOG:
 * LOG: Revision 5.14  2002/02/15 23:12:21  ssharma
 * LOG: Change the signature of the MTP3 send func to match
 * LOG: VFRAME
 * LOG:
 * LOG: Revision 5.13  2001/12/20 23:46:48  mmiers
 * LOG: Trying for consistency
 * LOG:
 * LOG: Revision 5.12  2001/12/18 21:59:19  mmiers
 * LOG: Standardize on exports for vendors
 * LOG:
 * LOG: Revision 5.11  2001/12/17 21:09:22  mmiers
 * LOG: Finish the vendor framework.  Works with NMS MTP2.
 * LOG:
 * LOG: Revision 5.10  2001/11/30 23:43:14  mmiers
 * LOG: Start testing config-d (route management).
 * LOG:
 * LOG: Revision 5.9  2001/11/16 23:37:40  mmiers
 * LOG: Today's round of testing.
 * LOG:
 * LOG: Revision 5.8  2001/11/09 20:19:55  mmiers
 * LOG: Don't force the vendor lib to be part of the engine.  Make into
 * LOG: DLL instead.
 * LOG:
 * LOG: Revision 5.7  2001/10/19 20:49:00  mmiers
 * LOG: Get things working with the engine.
 * LOG:
 * LOG: Revision 5.6  2001/10/16 20:39:48  mmiers
 * LOG: Change variable names to avoid collisions
 * LOG:
 * LOG: Revision 5.5  2001/10/06 23:30:33  mmiers
 * LOG: Finish the MTP2 API.
 * LOG:
 * LOG: Revision 5.4  2001/10/05 22:59:42  mmiers
 * LOG: NMS MTP2 API is taking shape.
 * LOG:
 * LOG: Revision 5.3  2001/09/05 23:05:45  mmiers
 * LOG: Working MTP2 into the scene.
 * LOG:
 * LOG: Revision 5.2  2001/09/05 20:35:47  mmiers
 * LOG: Consolidate the NMS libraries.  Only the root library so far.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:34  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/08/16 19:25:20  hcho
 * LOG: ISUP symboles are required.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:07  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.7  2001/05/04 15:44:55  hcho
 * LOG: Add NMSOpenISUP for ISUP binding.
 * LOG:
 * LOG: Revision 3.6  2001/03/14 22:07:09  mmiers
 * LOG: Include ISUP in the engine.
 * LOG:
 * LOG: Revision 3.5  2001/02/06 21:09:36  hxing
 * LOG: Work around ctaInitialize
 * LOG:
 * LOG: Revision 3.4  2000/12/20 16:38:01  hxing
 * LOG: Add one more entry to thte context struct
 * LOG:
 * LOG: Revision 3.3  2000/12/05 17:39:49  hxing
 * LOG: Add more fields to the context for isup integration
 * LOG:
 * LOG: Revision 3.2  2000/09/08 21:48:47  hxing
 * LOG: Add cta handle and queue handle to ITS_SS7_CONTEXT (for isup) for ver 3.5
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:10:42  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.5  2000/08/04 19:12:43  labuser
 * LOG:
 * LOG: Include configuration.template on both platforms.
 * LOG:
 * LOG: Revision 2.4  2000/07/25 20:00:32  hxing
 * LOG:
 * LOG:
 * LOG: Sanitize the source.  Get layer builds working for all 4 parts.
 * LOG:
 * LOG: Revision 2.3  2000/07/21 14:31:05  labuser
 * LOG:
 * LOG: Testing on solaris.
 * LOG:
 * LOG: Revision 2.2  2000/06/21 17:43:30  hxing
 * LOG: add isupFD to struct ITS_SS7_CONTEXT
 * LOG:
 * LOG: Revision 2.1  1999/12/17 21:34:02  rsonak
 * LOG:
 * LOG: Fix mixed stack configuration.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:33:03  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.12  1999/11/05 23:29:35  mmiers
 * LOG:
 * LOG:
 * LOG: Sanitize the build.  Single configuration now.
 * LOG:
 * LOG: Revision 1.11  1999/10/07 17:43:47  mmiers
 * LOG:
 * LOG:
 * LOG: Try to bring some sanity to the build process.
 * LOG:
 * LOG: Revision 1.10  1998/11/20 23:07:54  mmiers
 * LOG: Fix some integration bugs.
 * LOG:
 * LOG: Revision 1.9  1998/11/13 18:42:09  mmiers
 * LOG: Fix this up for HNS.
 * LOG:
 * LOG: Revision 1.8  1998/10/28 00:27:18  mmiers
 * LOG: More fixes for NMS SCCP/MTP3.
 * LOG:
 * LOG: Revision 1.7  1998/10/27 21:44:29  mmiers
 * LOG: Add in MTP3.
 * LOG:
 * LOG: Revision 1.6  1998/10/27 21:37:33  mmiers
 * LOG: Include MTP3 stuff as well.
 * LOG:
 * LOG: Revision 1.5  1998/10/27 18:24:03  mmiers
 * LOG: Continue implementing NMS SCCP.
 * LOG:
 * LOG: Revision 1.4  1998/10/27 18:02:34  mmiers
 * LOG: Continue NMS/SCCP update.
 * LOG:
 * LOG: Revision 1.3  1998/10/27 16:19:34  mmiers
 * LOG: Recreate a header file.
 * LOG:
 * LOG: Revision 1.2  1998/06/17 20:46:35  mmiers
 * LOG: Add vendor IntelliNet.
 * LOG:
 * LOG: Revision 1.1  1998/04/22 18:57:22  mmiers
 * LOG: What I should have done in the first place.  There is no important
 * LOG: shared data in the ITS_CONTEXT.
 * LOG:
 * LOG: Revision 1.11  1998/04/20 22:04:44  mmiers
 * LOG: Integrate in the worker code.  Trying to maintain backwards
 * LOG: compatibility with existing vendor code.
 * LOG:
 * LOG: Revision 1.10  1998/03/19 00:19:32  rsonak
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.9  1998/03/18 01:34:55  rsonak
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.8  1998/02/11 15:21:46  mmiers
 * LOG: Fix a few bugs in these files.
 * LOG:
 * LOG: Revision 1.7  1998/02/06 15:29:55  ite
 * LOG: update for changes to nms header location.
 * LOG:
 * LOG: Revision 1.6  1998/02/06 14:48:51  mmiers
 * LOG: Cleanup to reflect vendor tree split
 * LOG:
 * LOG: Revision 1.5  1998/02/04 22:54:46  rsonak
 * LOG: working file
 * LOG:
 * LOG: Revision 1.4  1998/01/29 16:10:01  rsonak
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.3  1998/01/29 16:05:40  rsonak
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.2  1998/01/24 22:36:58  mmiers
 * LOG: Tree cleanup.
 * LOG:
 * LOG: Revision 1.1  1998/01/21 18:14:10  rsonak
 * LOG: Added its.h its_intern.h (timestamp problem with other files).
 * LOG:
 *
 ****************************************************************************/
#ifndef ITS_INTERN_H
#define ITS_INTERN_H

#if defined(CCITT)
#include <configuration.template.ccitt>
#elif defined(ANSI)
#include <configuration.template.ansi>
#else
#error "Protocol specific configuration.template not defined."
#endif

#include <its.h>
#include <its_mlist.h>
#include <its_ss7_trans.h>

#if defined(CCITT)
#include <itu/tcap.h>
#include <itu/isup.h>
#elif defined(ANSI)
#include <ansi/tcap.h>
#include <ansi/isup.h>
#include <itu/isup_macros.h>
#elif defined(PRC)
#include <china/tcap.h>
#include <china/isup.h>
#else
#error "Protocol family not defined."
#endif

#include <ss7type.h>
#include <ctadef.h>

#if defined(INCLUDE_MTP3)
#if NMS_VERSION < 3080
#include <mtp3api.h>
#else
#include <mtp3def.h>
#endif
#endif

#if defined(INCLUDE_ISUP)
#if NMS_VERSION >= 3050
#include <isup_translate.h>
#endif
#define _NEW_ISUP_
#include <isupmgmt.h>
#endif

#if defined(INCLUDE_SCCP) || defined(INCLUDE_TCAP)

#if NMS_VERSION >= 3000
#define _NEW_SCCP_
#include <sccpdef.h>
#endif
#include <sccpapi.h>
#endif

#if defined(INCLUDE_TCAP)
#if NMS_VERSION <= 3000
#include <tcapapi.h>
#include <tcapfunc.h>
#else
#include <tcapdef.h>
#endif

#endif

#include <mtp2mapi.h>
#include <its_trace.h>
#include <dbc_serv.h>
#include <ss7_mgmt.h>


#define MTP3_SVCID  0x21

#ifdef __cplusplus
extern "C"
{
#endif

#define NMS_MSG_SIZE    800

#define MAX_LOCAL_SUBS  3
#define MAX_LINK_CODES  16


#define LINK_SETS_STRING    "linkSets"

#define LINK_PORTS_STRING   "linkPorts"

#define MAX_DATA_LINKS      64

/*
 * MTP2 Tracing information
 */
extern TRACE_Data* MTP2_NMS_TraceData;

#define MTP2_TRACE_CRITICAL  0
#define MTP2_TRACE_ERROR     1
#define MTP2_TRACE_WARNING   2
#define MTP2_TRACE_DEBUG     3

#define MTP2_CRITICAL(args) \
    TRACE(MTP2_NMS_TraceData, MTP2_TRACE_CRITICAL, args)

#define MTP2_ERROR(args) \
    TRACE(MTP2_NMS_TraceData, MTP2_TRACE_ERROR, args)

#define MTP2_WARNING(args) \
    TRACE(MTP2_NMS_TraceData, MTP2_TRACE_WARNING, args)

#define MTP2_DEBUG(args) \
    TRACE(MTP2_NMS_TraceData, MTP2_TRACE_DEBUG, args)

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
    ITS_BOOLEAN     traceOn;     /* on(1), off(0) */
    ITS_CHAR        traceType[ITS_PATH_MAX];
    ITS_CHAR        traceOutput[ITS_PATH_MAX];
}
MTP2GeneralCfg;

typedef struct
{
    ITS_USHORT linkPort;
    ITS_OCTET  linkCode;
    ITS_OCTET  flcLevel; 
}
DataLink;

/*
 * internal format for the ITS_SS7_HANDLE
 *
 * NOTE: WATCH THE PADDING OF THIS STRUCT.  REMEMBER NMS REQUIRES
 * #pragma pack(1)
 */
typedef struct
{
    /* inheritance */
    VENDOR_Instance inst;

    /* general: start is word aligned */
    S16             sapid;
    S16             servUserId;
    U8              boardNum;
    U8              srcEnt;
    U8              srcInst;
    U8              type;

    /* MTP2: start is word aligned */
#if NMS_VERSION >= 3080
    TX_HANDLE       txHandle;
#if defined(WIN32)
    short           pad2;
#endif
    CPI_WAIT_TYPE   mtp2Sync;
    U8              mtp2SrcEnt;
    ITS_OCTET       linkSet;
    ITS_OCTET       numLinkCodes;
    ITS_OCTET       pad4;
    DataLink        dataLink[MAX_DATA_LINKS]; 
    ITS_USHORT      emergency;
    ITS_USHORT      pad5;
#endif

    /* MTP3: start is word aligned */
    OS_HSYNC        mtp3Sync;
    S16             mtp3Sapid;
    U8              mtp3SrcEnt;
    U8              sio;
    U32             opc;
    U32             dpc;
#if NMS_VERSION >= 3080
    CTAQUEUEHD      mtp3CtaQueueHd;     /* for nms ss7 ver 3.8 */
    CTAHD           mtp3CtaHd;          /* for nms ss7 ver 3.8 */
#endif

    /* ISUP: start is word aligned */
    OS_HSYNC        isupSync; /* not used for ver3.5 */
    OS_FD           isupFD; /* not used for ver3.5 */
    S16             isupSapid;
    U8              isupMgmtSrcEnt;
    U8              isupSrcEnt;
#if NMS_VERSION >= 3050
    CTAQUEUEHD      isupCtaQueueHd;     /* for nms ss7 ver 3.5 */
    CTAHD           isupCtaHd;          /* for nms ss7 ver 3.5 */
#endif

    /* SCCP: start is word aligned */
    OS_HSYNC        sccpSync;
    OS_FD           sccpFD;
    U8              ssn[MAX_LOCAL_SUBS];
    U8              destSsn;
    U8              maxSubs;
    U8              currentSub;
    ITS_OCTET       pad3[2];

    /* TCAP: start is word aligned */
    OS_HSYNC        tcapSync;
    ITS_BOOLEAN     isQueueInitialized;
}
ITS_SS7_CONTEXT;



/*
 * a helper for the parser extension
 */
typedef struct __XML_ParseData
{
    struct __XML_ParseData  *next;
    ITS_SS7_CONTEXT         ctxt;
    char                    *sectionName;
}
XML_ParseData;

/*
 * implementation signatures
 */
int NMSInitializeMTP2(ITS_SS7_HANDLE handle);
int NMSTermMTP2(ITS_SS7_HANDLE handle);
int NMSRetrieveMTP2Message(ITS_SS7_HANDLE handl);
int NMSHandleNotification(ITS_SS7_HANDLE handl);
int NMSSendMTP2Event(ITS_SS7_HANDLE handle,
                     ITS_OCTET *data, ITS_USHORT dlen);
void NMS_MTP2_Console(DBC_Server *dbc, const char *cmdLine);
int NMSCommit(FILE* fp);

int NMSInitializeMTP3(ITS_SS7_HANDLE handl);
int NMSTermMTP3(ITS_SS7_HANDLE handl);
int NMSRetrieveMTP3Message(ITS_SS7_HANDLE handl);
int NMSSendMTP3Event(ITS_SS7_HANDLE handle,
                     ITS_OCTET mType,
                     MTP3_HEADER *mtp3,
                     ITS_OCTET *data, ITS_USHORT dlen);

#if defined(CCITT)
#define NMSRetrieveISUPMessage        NMSRetrieveISUPMessage_CCITT
#define NMSSendISUPEvent              NMSSendISUPEvent_CCITT
#elif defined(ANSI)
#define NMSRetrieveISUPMessage        NMSRetrieveISUPMessage_ANSI
#define NMSSendISUPEvent              NMSSendISUPEvent_ANSI
#endif

int NMSInitializeISUP(ITS_SS7_HANDLE handl);
int NMSOpenISUP(ITS_SS7_HANDLE handl);
int NMSTermISUP(ITS_SS7_HANDLE handl);
int NMSRetrieveISUPMessage(ITS_SS7_HANDLE handl);
int NMSSendISUPEvent(ITS_SS7_HANDLE handl, ITS_OCTET type, ITS_HDR* hdr,
                     ITS_ISUP_IE* ies, int iecount, ISUP_MSG_DESC* desc);

int NMSInitializeSCCP(ITS_SS7_HANDLE handl);
int NMSTermSCCP(ITS_SS7_HANDLE handl);
int NMSGetNextLocalRef(ITS_SS7_HANDLE handl, ITS_USHORT *ref);
int NMSRetrieveSCCPMessage(ITS_SS7_HANDLE handl);
int NMSSendSCCPEvent(ITS_SS7_HANDLE handl, ITS_OCTET type, ITS_HDR* hdr,
                     ITS_SCCP_IE* ies, int iecount, SCCP_MSG_DESC* desc);
int NMSSendUserOutOfService(ITS_SS7_HANDLE handle, ITS_OCTET ni,
                            ITS_UINT pc, ITS_OCTET ssn);
int NMSSendUserInService(ITS_SS7_HANDLE handle, ITS_OCTET ni,
                         ITS_UINT pc, ITS_OCTET ssn);
int NMSSetCongestion(ITS_SS7_HANDLE handle, ITS_OCTET ni,
                     ITS_UINT pc, ITS_OCTET ssn, ITS_OCTET cong);

int NMSInitializeTCAP(ITS_SS7_HANDLE handl);
int NMSTermTCAP(ITS_SS7_HANDLE handl);
int NMSRetrieveTCAPMessage(ITS_SS7_HANDLE handl);
int NMSSendDialogue(ITS_SS7_HANDLE handle, ITS_HDR *hdr, TCAP_DLG *dlg);
int NMSSendComponent(ITS_SS7_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt);
int NMSSendTCAPUOS(ITS_SS7_HANDLE handle, ITS_OCTET ni,
                   ITS_UINT pc, ITS_OCTET ssn);
int NMSSendTCAPUIS(ITS_SS7_HANDLE handle, ITS_OCTET ni,
                   ITS_UINT pc, ITS_OCTET ssn);
int NMSSetTCAPCong(ITS_SS7_HANDLE handle, ITS_OCTET ni,
                   ITS_UINT pc, ITS_OCTET ssn, ITS_OCTET cong);
int NMSAllocDID(ITS_SS7_HANDLE handle, ITS_USHORT *did);

#ifdef __cplusplus
}
#endif

#endif /* ITS_INTERN_H */
