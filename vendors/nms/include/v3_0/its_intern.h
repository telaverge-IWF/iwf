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
 *  ID: $Id: its_intern.h,v 9.1 2005/03/23 12:55:51 cvsadmin Exp $
 *
 * LOG: $Log: its_intern.h,v $
 * LOG: Revision 9.1  2005/03/23 12:55:51  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:55:14  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:52  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:54  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 1.1  2001/09/05 20:35:47  mmiers
 * LOG: Consolidate the NMS libraries.  Only the root library so far.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:39  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:07  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:11:23  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.3  2000/06/09 22:02:27  randresol
 * LOG: Adding file to current tree
 * LOG:
 * LOG: Revision 1.1  2000/05/11 22:01:53  randresol
 * LOG: Creation of NMS directory for SS7 Version 3.
 * LOG: Creation of VMI Interface on top of NMS HMI library to support redundancy.
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

#include <configuration.template>

#include <ss7type.h>
#include <mtp3api.h>


#include <sccpapi.h>
#include <tcapapi.h>
#include <tcapfunc.h>


#include <its.h>

#if defined(CCITT)
#include <itu/tcap.h>
#include <itu/isup.h>
#elif defined(ANSI)
#include <ansi/tcap.h>
#include <ansi/isup.h>
#else
#error "Protocol family not defined."
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#define NMS_MSG_SIZE    800

#define MAX_LOCAL_SUBS  3

/*
 * internal format for the ITS_SS7_HANDLE
 */
typedef struct
{
    ITS_UINT    mask;
    ITS_USHORT  instance;
    ITS_USHORT  pad;
    OS_HSYNC    mtp3Sync;
    OS_HSYNC    isupSync;
    OS_HSYNC    sccpSync;
    OS_HSYNC    tcapSync;
    OS_FD       sccpFD;
    S16         sapid;
    S16         servUserId;
    U8          boardNum;
    U8          srcEnt;
    U8          srcInst;
    U8          type;
    U32         opc;
    U32         dpc;
    U8          ssn[MAX_LOCAL_SUBS];
    U8          maxSubs;
    U8          currentSub;
    U8          destSsn;
    U8          sio;
    U8          pad2;
}
ITS_SS7_CONTEXT;

void NMSBuildSCCPCoordEvent(ITS_SS7_CONTEXT *context, int isInd,
                            TcapCoordEvent *coord, ITS_EVENT *ev);
void NMSBuildSCCPSSCEvent(ITS_SS7_CONTEXT *context,
                          TcapSsnStateEvent *state, ITS_EVENT *ev);
void NMSBuildSCCPReturnEvent(ITS_SS7_CONTEXT *context,
                             TcapNotifEvent *note, ITS_EVENT *ev);

int NMSInitializeMTP3(ITS_SS7_HANDLE handl);
int NMSTermMTP3(ITS_SS7_HANDLE handl);
int NMSRetrieveMTP3Message(ITS_SS7_HANDLE handl);
int NMSSendMTP3Event(ITS_SS7_HANDLE handle, MTP3_HEADER *mtp3,
                     ITS_OCTET *data, ITS_USHORT dlen);

int NMSInitializeISUP(ITS_SS7_HANDLE handl);
int NMSTermISUP(ITS_SS7_HANDLE handl);
int NMSRetrieveISUPMessage(ITS_SS7_HANDLE handl);
int NMSSendISUPEvent(ITS_SS7_HANDLE handl, ITS_OCTET type, ITS_HDR* hdr,
                     ITS_ISUP_IE* ies, int iecount, ISUP_MSG_DESC* desc);

int NMSInitializeSCCP(ITS_SS7_HANDLE handl);
int NMSTermSCCP(ITS_SS7_HANDLE handl);
int NMSRetrieveSCCPMessage(ITS_SS7_HANDLE handl);
int NMSSendSCCPEvent(ITS_HANDLE handl, ITS_OCTET type, ITS_HDR* hdr,
                     ITS_SCCP_IE* ies, int iecount, SCCP_MSG_DESC* desc);

int NMSInitializeTCAP(ITS_SS7_HANDLE handl);
int NMSTermTCAP(ITS_SS7_HANDLE handl);
int NMSRetrieveTCAPMessage(ITS_SS7_HANDLE handl);
int NMSSendDialogue(ITS_SS7_HANDLE handle, ITS_HDR *hdr, TCAP_DLG *dlg);
int NMSSendComponent(ITS_SS7_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt);

#ifdef __cplusplus
}
#endif

#endif /* ITS_INTERN_H */
