/*********************************-*-C-*-************************************
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
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: transport.c,v 9.4.36.1 2010/02/19 08:16:44 kramesh Exp $
 *
 * LOG: $Log: transport.c,v $
 * LOG: Revision 9.4.36.1  2010/02/19 08:16:44  kramesh
 * LOG: Issue 2559: Changes for NMS 4k. Replaced select() system call with poll().
 * LOG:
 * LOG: Revision 9.4  2005/07/18 22:40:25  randresol
 * LOG: Modification to use cpia*_ asynchronous library for NMS4000 TX board.
 * LOG:
 * LOG: Revision 9.3  2005/07/07 05:44:13  mmanikandan
 * LOG: Changes to run on windows.
 * LOG:
 * LOG: Revision 9.2  2005/05/06 10:08:39  mmanikandan
 * LOG: PR6.5.1 Validation Bug(1793) Fix.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:56:16  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.5  2005/03/21 13:55:40  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.5.2.4.6.3.6.3  2005/01/05 12:27:03  craghavendra
 * LOG: Syslog Enhancement.
 * LOG:
 * LOG: Revision 7.5.2.4.6.3.6.2  2005/01/05 10:30:11  snagesh
 * LOG: removed tabs
 * LOG:
 * LOG: Revision 7.5.2.4.6.3.6.1  2005/01/03 16:23:28  snagesh
 * LOG: MTP2 OAM changes
 * LOG:
 * LOG: Revision 7.5.2.4.6.3  2004/09/15 06:05:56  mmanikandan
 * LOG: XML Persistency propagation.
 * LOG:
 * LOG: Revision 7.5.2.4.6.2  2004/07/09 11:08:22  sswami
 * LOG: CC compiler related changes in printf's
 * LOG:
 * LOG: Revision 7.5.2.4.6.1  2004/07/09 07:22:52  dsatish
 * LOG: Merging activity for timeslot changes
 * LOG:
 * LOG: Revision 7.5.2.4  2003/07/22 19:34:09  lbana
 * LOG: Bug fixes in mtp3.c and transport.c file for ECT.
 * LOG:
 * LOG: Revision 7.5.2.3  2003/05/07 11:35:37  ssingh
 * LOG: New ISUP function is added in vendor Class.
 * LOG:
 * LOG: Revision 7.5.2.2  2003/03/19 00:11:05  randresol
 * LOG: Add the include file mtp2_sh.h
 * LOG:
 * LOG: Revision 7.5.2.1  2003/02/19 17:41:17  randresol
 * LOG: Correct include files
 * LOG:
 * LOG: Revision 7.5  2003/01/16 16:23:34  mmiers
 * LOG: Tandem port, large context changes.
 * LOG:
 * LOG: Revision 7.4  2002/11/26 21:04:15  ngoel
 * LOG: merge prc changes from pr6.2
 * LOG:
 * LOG: Revision 7.3  2002/11/09 20:40:26  randresol
 * LOG: add mtp3SrcEnt to resource manager
 * LOG:
 * LOG: Revision 7.2  2002/09/06 19:34:32  yranade
 * LOG: remove C++ style comments
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:11:09  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.7  2002/08/08 16:26:12  sjaddu
 * LOG: Merge form ISUP_PR7 to Current.
 * LOG:
 * LOG: Revision 6.6  2002/06/17 19:07:34  hcho
 * LOG: ClassName has to split.
 * LOG:
 * LOG: Revision 6.5  2002/06/10 23:24:58  sjaddu
 * LOG: Bug fix in the Class initilizatin for ANSI.
 * LOG:
 * LOG: Revision 6.4  2002/05/20 16:30:38  sjaddu
 * LOG: Merge from PR6.
 * LOG:
 * LOG: Revision 6.3  2002/05/17 16:09:10  randresol
 * LOG: Bug fixes for resource generation code
 * LOG:
 * LOG: Revision 6.2  2002/05/16 15:51:10  hcho
 * LOG: Modifications for v3_6 build.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:15:06  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.26.2.4  2002/05/09 15:57:17  labuser
 * LOG: Remove conflict after merge.
 * LOG:
 * LOG: Revision 5.26.2.3  2002/04/19 20:45:04  hcho
 * LOG: Typo fix.
 * LOG:
 * LOG: Revision 5.26.2.2.2.1  2002/04/30 16:55:58  labuser
 * LOG: compilation problem fixed in transport.c
 * LOG:
 * LOG: Revision 5.26.2.2  2002/04/18 20:00:12  sjaddu
 * LOG: NMS 3.8 changes in PR6
 * LOG:
 * LOG: Revision 5.26.2.1  2002/03/01 18:55:37  ssharma
 * LOG: Add check for NMS version.
 * LOG:
 * LOG: Revision 5.26  2002/02/06 19:06:29  ssharma
 * LOG: Check for NMS_VERSION >= 3080
 * LOG:
 * LOG: Revision 5.25  2002/02/01 21:28:49  mmiers
 * LOG: Fix vframe def
 * LOG:
 * LOG: Revision 5.24  2002/01/31 22:53:56  mmiers
 * LOG: Make it family independent.
 * LOG:
 * LOG: Revision 5.23  2002/01/31 20:29:28  mmiers
 * LOG: Wrong class
 * LOG:
 * LOG: Revision 5.22  2002/01/10 19:45:16  mmiers
 * LOG: A few bugs fixed
 * LOG:
 * LOG: Revision 5.21  2002/01/10 16:50:08  mmiers
 * LOG: Switch to refcounting transports.
 * LOG:
 * LOG: Revision 5.20  2002/01/08 15:58:01  mmiers
 * LOG: Note method is static.
 * LOG:
 * LOG: Revision 5.19  2001/12/18 21:59:19  mmiers
 * LOG: Standardize on exports for vendors
 * LOG:
 * LOG: Revision 5.18  2001/12/17 21:09:22  mmiers
 * LOG: Finish the vendor framework.  Works with NMS MTP2.
 * LOG:
 * LOG: Revision 5.17  2001/12/15 01:19:50  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.16  2001/12/14 00:05:04  mmiers
 * LOG: Generic vendor framework.
 * LOG:
 * LOG: Revision 5.15  2001/12/11 15:21:53  mmiers
 * LOG: Bug remnants
 * LOG:
 * LOG: Revision 5.14  2001/11/30 23:43:14  mmiers
 * LOG: Start testing config-d (route management).
 * LOG:
 * LOG: Revision 5.13  2001/11/20 23:39:57  mmiers
 * LOG: Cut the debug output a bit.
 * LOG:
 * LOG: Revision 5.12  2001/11/20 20:15:52  mmiers
 * LOG: Tab removal
 * LOG:
 * LOG: Revision 5.11  2001/11/16 23:37:40  mmiers
 * LOG: Today's round of testing.
 * LOG:
 * LOG: Revision 5.10  2001/11/14 16:32:56  mmiers
 * LOG: Handle multiple instances
 * LOG:
 * LOG: Revision 5.9  2001/11/09 20:19:55  mmiers
 * LOG: Don't force the vendor lib to be part of the engine.  Make into
 * LOG: DLL instead.
 * LOG:
 * LOG: Revision 5.8  2001/10/19 20:49:00  mmiers
 * LOG: Get things working with the engine.
 * LOG:
 * LOG: Revision 5.7  2001/10/16 20:39:48  mmiers
 * LOG: Change variable names to avoid collisions
 * LOG:
 * LOG: Revision 5.6  2001/10/12 23:14:52  mmiers
 * LOG: Fun with NMS.  The MTP2 API now works.
 * LOG:
 * LOG: Revision 5.5  2001/10/09 23:24:59  mmiers
 * LOG: Bug fixes.
 * LOG:
 * LOG: Revision 5.4  2001/10/06 23:30:33  mmiers
 * LOG: Finish the MTP2 API.
 * LOG:
 * LOG: Revision 5.3  2001/10/05 22:59:42  mmiers
 * LOG: NMS MTP2 API is taking shape.
 * LOG:
 * LOG: Revision 5.2  2001/09/05 20:35:48  mmiers
 * LOG: Consolidate the NMS libraries.  Only the root library so far.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:35  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.3  2001/08/16 17:14:54  hcho
 * LOG: Backported from PR4 for event cleaning up.
 * LOG:
 * LOG: Revision 3.16.2.6  2001/08/16 16:46:49  hcho
 * LOG: Clean up ENABLE_xxx_INDICS and event waiting function.
 * LOG:
 * LOG: Revision 3.16.2.5  2001/06/27 19:47:58  hcho
 * LOG: Uses string macros for opc, dpc, sio matching.
 * LOG:
 * LOG: Revision 3.16.2.4  2001/06/26 19:07:37  labuser
 * LOG: Added a hash define for ISUP.
 * LOG:
 * LOG: Revision 3.16.2.3  2001/06/13 16:43:23  hxing
 * LOG: Win32
 * LOG:
 * LOG: Revision 3.16.2.2  2001/06/12 23:04:50  labuser
 * LOG: Dont return from "remoteSSN" ini lookup. It cost me 3 hours
 * LOG:
 * LOG: Revision 3.16.2.1  2001/05/16 17:36:13  rsonak
 * LOG: ISUP stuff needs to be in #define
 * LOG:
 * LOG: Revision 3.16  2001/05/04 15:56:05  hcho
 * LOG: Get config data from the resource manager if not STANDALONE.
 * LOG:
 * LOG: Revision 3.15  2001/02/28 15:58:52  hxing
 * LOG: Problem fixed with Enqueue
 * LOG:
 * LOG: Revision 3.14  2001/02/13 23:07:10  mmiers
 * LOG: Correct a load of signatures.
 * LOG:
 * LOG: Revision 3.13  2001/02/12 17:48:52  hxing
 * LOG: Add flag for ctaInitialize
 * LOG:
 * LOG: Revision 3.12  2001/02/06 21:09:36  hxing
 * LOG: Work around ctaInitialize
 * LOG:
 * LOG: Revision 3.11  2001/02/06 17:14:00  hxing
 * LOG: Check return errors
 * LOG:
 * LOG: Revision 3.10  2001/02/06 00:15:12  hxing
 * LOG: Remove warnings
 * LOG:
 * LOG: Revision 3.9  2001/02/05 23:34:53  hxing
 * LOG: Problem tcap indication
 * LOG:
 * LOG: Revision 3.8  2001/01/30 17:25:50  hxing
 * LOG: Change to use ITS_Free
 * LOG:
 * LOG: Revision 3.7  2000/12/20 16:38:01  hxing
 * LOG: Add one more entry to thte context struct
 * LOG:
 * LOG: Revision 3.6  2000/12/06 22:43:06  hxing
 * LOG: Work in progress
 * LOG:
 * LOG: Revision 3.5  2000/12/01 00:51:50  hxing
 * LOG: isup integration
 * LOG:
 * LOG: Revision 3.4  2000/10/20 14:40:02  labuser
 * LOG: Debug in solaris
 * LOG:
 * LOG: Revision 3.3  2000/10/04 15:53:45  hxing
 * LOG: Add ISUP to SS7_GetNextEvent for solaris.
 * LOG:
 * LOG: Revision 3.2  2000/08/31 16:49:33  hxing
 * LOG: Remove warning for indic_flag(UNIX only)
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:10:56  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.9  2000/08/04 19:10:08  labuser
 * LOG:
 * LOG: Merged changes done for Solaris port.
 * LOG:
 * LOG: Revision 1.5  2000/08/04 17:20:55  yranade
 * LOG: Finishing up merging
 * LOG:
 * LOG: Revision 1.4  2000/08/04 16:48:31  labuser
 * LOG:
 * LOG: Merge the changes made in the nms/src/ directory.
 * LOG:
 * LOG: Revision 1.3  2000/08/04 14:10:31  labuser
 * LOG:
 * LOG: Fix compile error.
 * LOG:
 * LOG: Revision 1.2  2000/07/21 14:31:06  labuser
 * LOG:
 * LOG: Testing on solaris.
 * LOG:
 * LOG: Revision 1.1  2000/07/18 15:27:41  yranade
 * LOG:
 * LOG: Initial version.
 * LOG:
 * LOG: Revision 2.3  2000/05
 /11 22:12:08  randresol
 * LOG: Intetration with VMI
 * LOG:
 * LOG: Revision 2.2  2000/01/28 00:47:09  rsonak
 * LOG:
 * LOG: Commit the PR2 patch. Added MTPS Pause and Resume callbacks for the STANDALONE
 * LOG: and INTEGRATED cases
 * LOG:
 * LOG: Revision 1.17.2.2  2000/01/27 23:16:53  rsonak
 * LOG:
 * LOG: Added MTP3 Pause and Resumes for the INTEGRATED and STANDALONE modes
 * LOG:
 * LOG: Revision 1.17.2.1  1999/12/17 20:08:25  mmiers
 * LOG: Disable SCCP calls when only using TCAP.
 * LOG:
 * LOG: Revision 1.17  1999/11/08 18:49:07  lbana
 * LOG:
 * LOG:
 * LOG: Use the common INI file for WITH_TOOLKIT and INTEGRATED builds.
 * LOG:
 * LOG: Revision 1.16  1999/11/05 23:29:37  mmiers
 * LOG:
 * LOG:
 * LOG: Sanitize the build.  Single configuration now.
 * LOG:
 * LOG: Revision 1.15  1999/10/07 17:43:52  mmiers
 * LOG:
 * LOG:
 * LOG: Try to bring some sanity to the build process.
 * LOG:
 * LOG: Revision 1.14  1999/10/06 22:12:43  cbascon
 * LOG:
 * LOG: Temporary change. Added #defines for disregarding SCCP and TCAP if only MTP3 is needed
 * LOG:
 * LOG: Revision 1.13  1999/09/24 19:34:23  ite
 * LOG:
 * LOG: fhasle: fixed some bugs.
 * LOG:
 * LOG: Revision 1.12  1999/04/30 22:33:37  labuser
 * LOG: Changed from ITS_SS7 to ITS_SS7_MASK  when initializing NMS.
 * LOG:
 * LOG: Revision 1.11  1998/12/02 22:06:20  jpakrasi
 * LOG: Put the declaration of nms_debug within #ifdef DEBUG, so that it is
 * LOG: turned off when compiling the Release version.
 * LOG:
 * LOG: Revision 1.10  1998/11/25 23:57:39  mmiers
 * LOG: SS7 integration is complete.
 * LOG:
 * LOG: Revision 1.9  1998/11/23 21:26:53  mmiers
 * LOG: Fix init bugs.
 * LOG:
 * LOG: Revision 1.8  1998/11/20 23:07:55  mmiers
 * LOG: Fix some integration bugs.
 * LOG:
 * LOG: Revision 1.7  1998/11/13 18:42:12  mmiers
 * LOG: Fix this up for HNS.
 * LOG:
 * LOG: Revision 1.6  1998/11/05 23:29:42  ite
 * LOG: Build tweak
 * LOG:
 * LOG: Revision 1.5  1998/11/05 21:30:34  mmiers
 * LOG: Working on pause/resume.
 * LOG:
 * LOG: Revision 1.4  1998/10/28 00:27:20  mmiers
 * LOG: More fixes for NMS SCCP/MTP3.
 * LOG:
 * LOG: Revision 1.3  1998/10/27 21:44:30  mmiers
 * LOG: Add in MTP3.
 * LOG:
 * LOG: Revision 1.2  1998/10/27 21:38:32  mmiers
 * LOG: Add in MTP3.
 * LOG:
 * LOG: Revision 1.1  1998/10/26 23:54:18  mmiers
 * LOG: Rework so that we can integrate with our SCCP and TCAP.
 * LOG:
 * LOG: Revision 1.27  1998/10/15 23:07:03  jpakrasi
 * LOG: Work in ac_name for ITU92 TCAP.
 * LOG:
 * LOG: Revision 1.26  1998/09/04 19:03:44  jpakrasi
 * LOG: Minor mods to compile with latest IntelliSS7 libraries (CCITT ver).
 * LOG:
 * LOG: Revision 1.25  1998/08/06 20:26:58  ite
 * LOG: List buffering free() bug.
 * LOG:
 * LOG: Revision 1.24  1998/08/06 16:26:52  mmiers
 * LOG: Rename the ini files.
 * LOG:
 * LOG: Revision 1.23  1998/06/17 20:46:35  mmiers
 * LOG: Add vendor IntelliNet.
 * LOG:
 * LOG: Revision 1.22  1998/05/19 14:03:01  mmiers
 * LOG: Cover modifications made to TCAP.
 * LOG:
 * LOG: Revision 1.21  1998/04/29 23:03:18  mmiers
 * LOG: Change ITS_TCAP to ITS_TCAP_SRC.  Same with SCCP.
 * LOG:
 * LOG: Revision 1.20  1998/04/21 00:09:38  mmiers
 * LOG: adjust for new prototype.
 * LOG:
 * LOG: Revision 1.19  1998/04/09 14:50:55  mmiers
 * LOG: Remove printf() when unable to retrieve a message from the board.  Fix bug
 * LOG: reporting the wrong status (sccp).
 * LOG:
 * LOG: Revision 1.18  1998/04/08 15:39:03  ite
 * LOG: Fixed small bug
 * LOG:
 * LOG: Revision 1.17  1998/04/07 15:41:55  mmiers
 * LOG: Remove error text function from vendor library (event.c).
 * LOG:
 * LOG: Add reception of sccp messages (sccp.c).  Update dsp file to reflect
 * LOG: death of queue.c.
 * LOG:
 * LOG: Revision 1.16  1998/04/06 22:47:43  mmiers
 * LOG: event.c, tcap.c: Change over to use the new support library in IntelliSS7
 * LOG:
 * LOG: queue.c, queue.h: These are no longer relevant due to the above change.
 * LOG:
 * LOG: Revision 1.15  1998/04/06 15:46:10  ite
 * LOG: commit bug fix for ITE.
 * LOG:
 * LOG: Revision 1.14  1998/03/03 16:15:26  mmiers
 * LOG: Work around Wei's whining about not knowing the subsystem number.  The app
 * LOG: has to know this anyway (local address, yes?) but this is quicker than
 * LOG: arguing.
 * LOG:
 * LOG: Revision 1.13  1998/02/26 18:46:52  mmiers
 * LOG: Add SCCP notifications to the event handling.
 * LOG:
 * LOG: Revision 1.12  1998/02/26 15:45:58  mmiers
 * LOG: Modifications to bring NMS signatures in line with everyone else.  INI files
 * LOG: are now read for the initial parameters (sapid, srcInst, boardNum, etc).
 * LOG:
 * LOG: Revision 1.11  1998/02/24 17:16:50  ite
 * LOG: Debugging the response problem.  The error code must be formed correctly or
 * LOG: NMS will not send it.  NOTE: NMS will NOT tell the sender that it couldn't
 * LOG: send the message -- it just happily eats the message without any indication.
 * LOG:
 * LOG: Revision 1.10  1998/02/11 15:22:18  mmiers
 * LOG: Update for new function signatures.
 * LOG:
 * LOG: Revision 1.9  1998/02/06 15:37:50  ite
 * LOG: Build after modifying its headers.
 * LOG:
 * LOG: Revision 1.8  1998/02/06 14:14:53  mmiers
 * LOG: Change ITS_INAP to ITS_TCAP.
 * LOG:
 * LOG: Revision 1.7  1998/02/05 16:17:42  mmiers
 * LOG: Case problem for nms_errno.
 * LOG:
 * LOG: Revision 1.6  1998/02/04 18:51:03  ite
 * LOG: Debug for TCAP test applications
 * LOG:
 * LOG: Revision 1.5  1998/01/28 02:01:49  rsonak
 * LOG: Forgot to complete ANSI build (Mitch).  Cleanup to reflect this.
 * LOG:
 * LOG: Revision 1.4  1998/01/27 23:34:04  mmiers
 * LOG: Finish up the port.
 * LOG:
 * LOG: Revision 1.3  1998/01/27 15:41:41  mmiers
 * LOG: NMS baseline for ITS
 * LOG:
 * LOG: Revision 1.2  1998/01/26 04:42:28  mmiers
 * LOG: Basic cleanup for NMS usage.  Need to add queue handling for correctness.
 * LOG:
 * LOG: Revision 1.1.1.1  1997/11/04 20:13:16  mmiers
 * LOG: Baseline
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>

#include <its.h>
#include <its_intern.h>
#include <its_ss7_trans.h>
#if INCLUDE_VMI
#include <its_vmi.h>
#endif
#include <its_assertion.h>

#include <engine.h>

#if defined (UNIX)
#include <unistd.h>
#elif defined (WIN32)
#include <windows.h>
#include <winbase.h>
#include <io.h>
#include <fcntl.h>
#endif

#if defined(ANSI)
#include <ansi/mtp3.h>
#elif defined(CCITT)
#include <itu/mtp3.h>
#elif defined(PRC)
#include <china/mtp3.h>
#endif

#include <mtp2_sn.h>
#include <vframe.h>

#include <sys/types.h>

#define ITS_INFINITE    -1

#define ITS_MAX_HANDLES     8

#define NMS_INI_SECTION_NAME            "NMS-TRACE"

/*
 * error reporting
 */
int nms_errno = 0;
#ifdef DEBUG
int nms_debug = 1;
#else
int nms_debug = 0;
#endif

extern TRACE_LevelInitializer MTP2_TraceMap[];

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Start parsing NMS information in XML files.
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
 ****************************************************************************/
VSS7DLLAPI void
NMS_ParseStart(ENGINE_ParserExtension ext,
               const char *el, const char **attr)
{
    XML_ParseData *pd;
    ITS_SS7_CONTEXT *ctxt;

    /* NOTE: this can't handle nested XML */
    /* NOTE: But it needs to handle multiple instances */

    pd = calloc(1, sizeof(XML_ParseData));
    ITS_C_ASSERT(pd != NULL);

    pd->next = ENGINE_PE_USER_DATA(ext);
    ENGINE_PE_USER_DATA(ext) = pd;

    ctxt = (ITS_SS7_CONTEXT *)&pd->ctxt;

    while (*attr)
    {
        if (strcmp(*attr, "sectionName") == 0)
        {
            attr++;

            pd->sectionName = strdup(*attr);
            ITS_C_ASSERT(pd->sectionName != NULL);

            attr++;
        }
        if (strcmp(*attr, "boardNum") == 0)
        {
            attr++;

            ctxt->boardNum = RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, "sapId") == 0)
        {
            attr++;

            ctxt->sapid = RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, "mtp3SapId") == 0)
        {
            attr++;

            ctxt->mtp3Sapid = RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, "isupSapId") == 0)
        {
            attr++;

            ctxt->isupSapid = RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, "srcEnt") == 0)
        {
            attr++;

            ctxt->srcEnt = RESFILE_ParseNum(*attr);

            attr++;
        }
#if NMS_VERSION >= 3080
        else if (strcmp(*attr, "mtp2SrcEnt") == 0)
        {
            attr++;

            ctxt->mtp2SrcEnt = RESFILE_ParseNum(*attr);

            attr++;
        }
#endif
        else if (strcmp(*attr, "mtp3SrcEnt") == 0)
        {
            attr++;

            ctxt->mtp3SrcEnt = RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, "isupMgmtSrcEnt") == 0)
        {
            attr++;

            ctxt->isupMgmtSrcEnt = RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, "isupSrcEnt") == 0)
        {
            attr++;

            ctxt->isupSrcEnt = RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, "srcInst") == 0)
        {
            attr++;

            ctxt->srcInst = RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, "servUserId") == 0)
        {
            attr++;

            ctxt->servUserId = RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, "localSSN") == 0)
        {
            char buf[ITS_PATH_MAX];
            char *tmp = buf, *ptr = buf;
            int i;

            attr++;

            strncpy(buf, *attr, ITS_PATH_MAX);

            for (i = 0; (tmp = strstr(tmp, ",")) != NULL && i < MAX_LOCAL_SUBS - 1; i++)
            {
                *tmp = 0;
                ctxt->ssn[i] = (U8)RESFILE_ParseNum(ptr);
                ctxt->maxSubs++;
                tmp++;
                ptr = tmp;
            }
            if (i < MAX_LOCAL_SUBS - 1)
            {
                ctxt->ssn[i] = (U8)RESFILE_ParseNum(ptr);
                ctxt->maxSubs++;
            }

            attr++;
        }
        else if (strcmp(*attr, "remoteSSN") == 0)
        {
            attr++;

            ctxt->destSsn = RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, ORIG_POINT_CODE_STRING) == 0)
        {
            attr++;

            sscanf(*attr, "%x", &ctxt->opc);

            attr++;
        }
        else if (strcmp(*attr, DEST_POINT_CODE_STRING) == 0)
        {
            attr++;

            sscanf(*attr, "%x", &ctxt->dpc);

            attr++;
        }
        else if (strcmp(*attr, "NIC") == 0)
        {
            attr++;

            sscanf(*attr, "%x", &ctxt->type);

            attr++;
        }
        else if (strcmp(*attr, SIO_STRING) == 0)
        {
            attr++;

            ctxt->sio = (U8)RESFILE_ParseNum(*attr);

            attr++;
        }
#if NMS_VERSION >= 3080
        else if (strcmp(*attr, LINK_SETS_STRING) == 0)
        {
            attr++;

            ctxt->linkSet = (U8)RESFILE_ParseNum(*attr);

            attr++;
        }
#endif
#if NMS_VERSION >= 3080
        else if (strcmp(*attr, LINK_PORTS_STRING) == 0)
        {
            char buf[ITS_PATH_MAX];
            char *tmp = buf, *ptr = buf;
            int i;

            attr++;

            strncpy(buf, *attr, ITS_PATH_MAX);

            for (i = 0; (tmp = strstr(tmp, ",")) != NULL && i < MAX_LINK_CODES; i++)
            {
                *tmp = 0;
                ctxt->dataLink[i].linkPort = (U8)RESFILE_ParseNum(ptr);
                ctxt->numLinkCodes++;
                tmp++;
                ptr = tmp;
            }
            if (i < MAX_LINK_CODES)
            {
                ctxt->dataLink[i].linkPort = (U8)RESFILE_ParseNum(ptr);
                ctxt->numLinkCodes++;
            }

            attr++;
        }
#endif
        else
        {
            attr += 2;
        }
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Term parsing NMS information in XML files.
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
 ****************************************************************************/
VSS7DLLAPI void
NMS_ParseEnd(ENGINE_ParserExtension ext, const char *el)
{
    /* don't care */
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Convert NMS information in XML files.
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
 ****************************************************************************/
VSS7DLLAPI void
NMS_ConvertParserData(RESFILE_Manager *appRes,
                      ENGINE_ParserExtension ext)
{
    int ret, i;
    char tmp[ITS_PATH_MAX];
    XML_ParseData *pd = (XML_ParseData *)ENGINE_PE_USER_DATA(ext);
    ITS_SS7_CONTEXT *ctxt;


    while (pd != NULL)
    {
        ctxt = (ITS_SS7_CONTEXT *)&pd->ctxt;

        /* convert the extension data to resources */
        sprintf(tmp, "%d", ctxt->boardNum);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "boardNum", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->sapid);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "sapId", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->mtp3Sapid);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "mtp3SapId", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->isupSapid);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "isupSapId", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->srcEnt);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "srcEnt", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

#if NMS_VERSION >= 3080
        sprintf(tmp, "%d", ctxt->mtp2SrcEnt);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "mtp2SrcEnt", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
#endif

        sprintf(tmp, "%d", ctxt->mtp3SrcEnt);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "mtp3SrcEnt", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->isupMgmtSrcEnt);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "isupMgmtSrcEnt", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->isupSrcEnt);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "isupSrcEnt", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->srcInst);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "srcInst", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->servUserId);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "servUserId", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        tmp[0] = 0;
        for (i = ctxt->maxSubs; i > 0; i--)
        {
            char buf[ITS_PATH_MAX];

            sprintf(buf, "%d,", ctxt->ssn[i-1]);
            strcat(tmp, buf);
        }
        if (ctxt->maxSubs >= 1)
        {
            tmp[strlen(tmp)-1] = 0;
        }
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "localSSN", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->destSsn);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "remoteSSN", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->opc);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  ORIG_POINT_CODE_STRING, tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->dpc);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  DEST_POINT_CODE_STRING, tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->type);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "NIC", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->sio);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  SIO_STRING, tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

#if NMS_VERSION >= 3080
        sprintf(tmp, "%d", ctxt->linkSet);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  LINK_SETS_STRING, tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
#endif

#if NMS_VERSION >= 3080
        tmp[0] = 0;
        for (i = ctxt->numLinkCodes; i > 0; i--)
        {
            char buf[ITS_PATH_MAX];

            sprintf(buf, "%d,", ctxt->dataLink[i-1].linkPort);
            strcat(tmp, buf);
        }
        if (ctxt->numLinkCodes >= 1)
        {
            tmp[strlen(tmp)-1] = 0;
        }
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  LINK_PORTS_STRING, tmp);

        ITS_C_ASSERT(ret == ITS_SUCCESS);
#endif

        pd = pd->next;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Diff NMS information in XML files.
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
 ****************************************************************************/
VSS7DLLAPI void
NMS_Diff(RESFILE_Manager *appRes,
         ENGINE_ParserExtension ext1,
         ENGINE_ParserExtension ext2)
{
    /* don't care */
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      read the instance specific config file
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
 ****************************************************************************/
static int
ReadInstance_STANDALONE(ITS_SS7_HANDLE hand, ITS_USHORT instance)
{
    ITS_SS7_CONTEXT *handle = (ITS_SS7_CONTEXT *)hand;
    char *env, buf[1024];
    U8 boardNum = 0;
    S16 sapid = 0, mtp3Sapid = 0, isupSapid = 0;
    U8 srcEnt = 0, mtp2SrcEnt = 0, mtp3SrcEnt = 0,
       isupSrcEnt = 0, isupMgmtSrcEnt = 0;
    U8 srcInst = 0;
    S16 servUserId = 0;
    U32 opc = 0;
    U8 ssn = 0;
    U32 dpc = 0;
    U8 destSsn = 0;
    U8 type = 0;
    U8 sio = 0;
    FILE *f;

    if ((env = getenv("VENDOR_CONFIG_DIR")) == NULL)
    {
        if (nms_debug)
        {
            printf("Can't find config directory\n");
        }

        return 0;
    }

#if defined(WIN32)
    sprintf(buf, "%s\\NMS_Inst%d.ini", env, instance);
#elif defined(UNIX)
    sprintf(buf, "%s/NMS_Inst%d.ini", env, instance);
#endif
    if ((f = fopen(buf, "r")) == NULL)
    {
        if (nms_debug)
        {
            printf("Can't open config file for this instance.\n");
        }
        
        return 0;
    }

    if (nms_debug)
    {
        printf("Reading from config file: %s\n", buf);
    }

    while (fgets(buf, 256, f) != NULL)
    {
        char *tok;

        if (buf[0] == '#' || buf[0] == ';' || buf[0] == '\n')
        {
            continue;
        }

        if ((tok = strchr(buf, '=')) == NULL)
        {
            if (nms_debug)
            {
                printf("Malformed line in config file:\n%s\n\n", buf);
            }

            continue;
        }

        *tok = 0;
        tok++;

        if (strncmp(buf, "boardNum", strlen("boardNum")) == 0)
        {
            boardNum = atoi(tok);
        }
        else if (strncmp(buf, "sapId", strlen("sapId")) == 0)
        {
            sapid = atoi(tok);
        }
        else if (strncmp(buf, "mtp3SapId", strlen("mtp3SapId")) == 0)
        {
            mtp3Sapid = atoi(tok);
        }
        else if (strncmp(buf, "isupSapId", strlen("isupSapId")) == 0)
        {
            isupSapid = atoi(tok);
        }

        else if (strncmp(buf, "srcEnt", strlen("srcEnt")) == 0)
        {
            srcEnt = atoi(tok);
        }
        else if (strncmp(buf, "mtp2SrcEnt", strlen("mtp2SrcEnt")) == 0)
        {
            mtp2SrcEnt = atoi(tok);
        }
        else if (strncmp(buf, "mtp3SrcEnt", strlen("mtp3SrcEnt")) == 0)
        {
            mtp3SrcEnt = atoi(tok);
        }
        else if (strncmp(buf, "isupMgmtSrcEnt", strlen("isupMgmtSrcEnt")) == 0)
        {
            isupMgmtSrcEnt = atoi(tok);
        }
        else if (strncmp(buf, "isupSrcEnt", strlen("isupSrcEnt")) == 0)
        {
            isupSrcEnt = atoi(tok);
        }

        else if (strncmp(buf, "srcInst", strlen("srcInst")) == 0)
        {
            srcInst = atoi(tok);
        }
        else if (strncmp(buf, "servUserId", strlen("servUserId")) == 0)
        {
            servUserId = atoi(tok);
        }
        else if (strncmp(buf, "localSSN", strlen("localSSN")) == 0)
        {
            ssn = atoi(tok);
            handle->maxSubs++;
            if (handle->maxSubs > MAX_LOCAL_SUBS)
            {
                handle->maxSubs--;
                if (nms_debug)
                {
                    printf("Too many local SSNs: stop at %02x\n",
                           handle->ssn[handle->maxSubs-1]);
                }
            }
            else
            {
                handle->ssn[handle->maxSubs-1] = ssn;
            }
        }
        else if (strncmp(buf, "remoteSSN", strlen("remoteSSN")) == 0)
        {
            destSsn = atoi(tok);
        }
        else if (strncmp(buf, ORIG_POINT_CODE_STRING,
                         strlen(ORIG_POINT_CODE_STRING)) == 0)
        {
            sscanf(tok, "%x", &opc);
        }
        else if (strncmp(buf, DEST_POINT_CODE_STRING,
                         strlen(DEST_POINT_CODE_STRING)) == 0)
        {
            sscanf(tok, "%x", &dpc);
        }
        else if (strncmp(buf, "NIC", strlen("NIC")) == 0)
        {
            sscanf(tok, "%x", &type);
        }
        else if (strncmp(buf, SIO_STRING, strlen(SIO_STRING)) == 0)
        {
            sio = atoi(tok);
            /* sscanf(tok, "%x", &sio); */
        }
        else
        {
            if (nms_debug)
            {
                printf("Invalid line in ini file: %s\n", buf);
            }
        }
    }

    handle->boardNum = boardNum;
    handle->sapid= sapid;
    handle->mtp3Sapid = mtp3Sapid;
    handle->isupSapid = isupSapid;
    handle->srcEnt = srcEnt;
#if NMS_VERSION >= 3080
    handle->mtp2SrcEnt = mtp2SrcEnt;
#endif
    handle->mtp3SrcEnt = mtp3SrcEnt;
    handle->isupMgmtSrcEnt = isupMgmtSrcEnt;
    handle->isupSrcEnt = isupSrcEnt;
    handle->srcInst = srcInst;
    handle->servUserId = servUserId;
    handle->opc = opc;
    handle->dpc = dpc;
    handle->destSsn = destSsn;
    handle->type = type;
    handle->sio = sio;

    if (nms_debug)
    {
        printf("ITS read the following:\n");
        printf("  boardNum: %d\n", boardNum);
        printf("     sapId: %d\n", sapid);
        printf(" mtp3Sapid: %d\n", mtp3Sapid);
        printf(" isupSapid: %d\n", isupSapid);
        printf("    srcEnt: %d\n", srcEnt);
#if NMS_VERSION >= 3080
        printf("mtp2SrcEnt: %d\n", mtp2SrcEnt);
#endif
        printf("mtp3SrcEnt: %d\n", mtp3SrcEnt);
        printf("isupSrcEnt: %d\n", isupSrcEnt);
        printf("   srcInst: %d\n", srcInst);
        printf("servUserId: %d\n", servUserId);
        printf("       opc: %d\n", opc);
        printf("       dpc: %d\n", dpc);
        printf("       ssn: %d\n", ssn);
        printf("   destSsn: %d\n", destSsn);
        printf("      type: %d\n", type);
        printf("       sio: %d\n", sio);
    }

    return 1;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      read the instance specific information from the resource DB.
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
 ****************************************************************************/
static int
ReadInstance_INTEGRATED(ITS_SS7_HANDLE hand, ITS_USHORT instance)
{
    char buf[1024];
    ITS_SS7_CONTEXT *handle = (ITS_SS7_CONTEXT *)hand;
    TRANSPORT_Control *tr = TRANSPORT_FindTransport(instance);
    char key[ITS_PATH_MAX], value[ITS_PATH_MAX];
    ITS_OCTET currentLinkCode;
    ITS_USHORT currentCircuit;
    int j;

    if (tr == NULL)
    {
        return 0;
    }

    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name, "boardNum",
                              buf, 1024) == ITS_SUCCESS)
    {
        handle->boardNum = atoi(buf);
    }

    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name, "sapId",
                              buf, 1024) == ITS_SUCCESS)
    {
        handle->sapid = atoi(buf);
    }

    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name,
                              "mtp3SapId", buf, 1024) == ITS_SUCCESS)
    {
        handle->mtp3Sapid = atoi(buf);
    }

    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name,
                              "isupSapId", buf, 1024) == ITS_SUCCESS)
    {
        handle->isupSapid = atoi(buf);
    }

    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name, "srcEnt",
                              buf, 1024) == ITS_SUCCESS)
    {
        handle->srcEnt = atoi(buf);
    }

#if NMS_VERSION >= 3080
    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name,
                              "mtp2SrcEnt", buf, 1024) == ITS_SUCCESS)
    {
        handle->mtp2SrcEnt = atoi(buf);
    }
#endif

    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name,
                              "mtp3SrcEnt", buf, 1024) == ITS_SUCCESS)
    {
        handle->mtp3SrcEnt = atoi(buf);
    }

    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name,
                              "isupSrcEnt", buf, 1024) == ITS_SUCCESS)
    {
        handle->isupSrcEnt = atoi(buf);
    }

    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name,
                              "isupMgmtSrcEnt", buf, 1024) == ITS_SUCCESS)
    {
        handle->isupMgmtSrcEnt = atoi(buf);
    }

    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name, "srcInst",
                              buf, 1024) == ITS_SUCCESS)
    {
        handle->srcInst = atoi(buf);
    }

    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name,
                              "servUserId",
                              buf, 1024) == ITS_SUCCESS)
    {
        handle->servUserId = atoi(buf);
    }

    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name, "localSSN",
                              buf, 1024) == ITS_SUCCESS)
    {
        handle->ssn[handle->maxSubs] = atoi(buf);
        handle->maxSubs++;

        while (RESFILE_GetKeyName(tr->transport.res, tr->transport.name,
                                  buf, 1024) == ITS_SUCCESS &&
               strcmp(buf, "localSSN") == 0)
        {
            if (RESFILE_GetKeyValue(tr->transport.res, tr->transport.name,
                                    buf, 1024) != ITS_SUCCESS)
            {
                TRANSPORT_UnfindTransport(tr);

                return 0;
            }

            if (handle->maxSubs > MAX_LOCAL_SUBS)
            {
                handle->maxSubs--;
                if (nms_debug)
                {
                    printf("Too many local SSNs: stop at %02x\n",
                           handle->ssn[handle->maxSubs-1]);
                }

                break;
            }
            else
            {
                handle->ssn[handle->maxSubs-1] = atoi(buf);
            }
        }
    }

    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name,
                              "remoteSSN", buf, 1024) == ITS_SUCCESS)    
    {
        handle->destSsn = atoi(buf);
    }

    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name,
                              ORIG_POINT_CODE_STRING,
                              buf, 1024) == ITS_SUCCESS)
    {
        handle->opc = (U32)RESFILE_ParseNum(buf);
    }

    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name,
                              DEST_POINT_CODE_STRING,
                              buf, 1024) == ITS_SUCCESS)
    {
       handle->dpc = (U32)RESFILE_ParseNum(buf); 
    }

    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name, "NIC",
                              buf, 1024) == ITS_SUCCESS)
    {
        handle->type = (U8)RESFILE_ParseNum(buf);
    }

    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name,
                              SIO_STRING,
                              buf, 1024) == ITS_SUCCESS)
    {
        handle->sio = (U8)RESFILE_ParseNum(buf);
    }

#if NMS_VERSION >= 3080
    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name,
                              LINK_SETS_STRING,
                              buf, 1024) == ITS_SUCCESS)
    {
        handle->linkSet = (U8)RESFILE_ParseNum(buf);
    }
#endif

#if NMS_VERSION >= 3080
    if (RESFILE_GetKeyValueOf(tr->transport.res, tr->transport.name,
                              LINK_PORTS_STRING,
                              buf, 1024) == ITS_SUCCESS)
    {
        char *tmp = buf, *ptr = buf;
        int i;

      
        for (i = 0; (tmp = strstr(tmp, ",")) != NULL && i < MAX_LINK_CODES; i++)
        {
            *tmp = 0;
            handle->dataLink[i].linkPort = (U8)RESFILE_ParseNum(ptr);
            handle->numLinkCodes++;
            tmp++;
            ptr = tmp;
        }
        if (i < MAX_LINK_CODES)
        {
            handle->dataLink[i].linkPort = (U8)RESFILE_ParseNum(ptr);
            handle->numLinkCodes++;
        }
    }


    RESFILE_Lock(tr->transport.res);
    RESFILE_Rewind(tr->transport.res, tr->transport.name);
    while (RESFILE_GetKeyName(tr->transport.res, tr->transport.name,
                              key,  1024) == ITS_SUCCESS &&
           RESFILE_GetKeyValue(tr->transport.res, tr->transport.name,
                               value, 1024) == ITS_SUCCESS)
    {
        if (strcmp(key, LINK_CODE_STRING) == 0 )
        {
            currentLinkCode =  atoi(value);
            printf("$$$$$$$$$ %d$$$$$$$$$\n",currentLinkCode);
            if (nms_debug)
            {
                 printf("$$$$ keyName = %s  value = %s $$$$\n", key, value);
            }
        }
        if (strcmp(key, LINK_DATA_LINK_STRING) == 0)
        {
            currentCircuit = atoi(value);
            if (nms_debug)
            {
                printf("$$$$ keyName = %s  value = %s linkPort = %d $$$$\n",
                        key, value, currentCircuit);
            }
            for (j = 0; j < MAX_DATA_LINKS; j++)
            {
                printf("this linkPort: idx %d linkPort %d\n", 
                        j,handle->dataLink[j].linkPort);
                if (handle->dataLink[j].linkPort == currentCircuit)
                {
                    handle->dataLink[j].linkCode = currentLinkCode;

                   if (nms_debug)
                   {
                        printf("$$$$ idx = %d , linkPort = %d ,"
                               "linkCode = %d $$ $$\n ",
                                j, handle->dataLink[j].linkPort,
                                handle->dataLink[j].linkCode );
                    }
                    break;
                }
            }
            if (j == MAX_DATA_LINKS)
            {
                if (nms_debug)
                {
                    printf("$$$ ERROR: NO LinkCode - Circuit Matching $$$\n");
                }
            }
        }

    }
    RESFILE_Unlock(tr->transport.res);

#endif

    if ((MTP2_NMS_TraceData = TRACE_Constructor("NMS-MTP2",
                                                MTP2_TraceMap, 4)) == NULL)
    {
        return (ITS_ENOMEM);
    }

    /* Critical Trace */
    if (RESFILE_GetKeyValueOf(tr->transport.res, NMS_INI_SECTION_NAME,
                              MTP2_TRACE_CRITICAL_STRING, buf, 1024) == ITS_SUCCESS)
    {
        ITS_BOOLEAN flag = ITS_FALSE;

        if (strstr(buf, MTP2_STDOUT_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_STDOUT_STRING, ITS_TRUE);
            flag = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_STDOUT_STRING, ITS_FALSE);
        }
        if (strstr(buf, MTP2_FILE_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_FILE_STRING, ITS_TRUE);
            flag = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_FILE_STRING, ITS_FALSE);
        }
        if (strstr(buf, MTP2_SYSLOG_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_SYSLOG_STRING, ITS_TRUE);
            flag = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_SYSLOG_STRING, ITS_FALSE);
        }
                 
        if (flag)
        {
            TRACE_SetLevelOnOffByName(MTP2_NMS_TraceData,
                                      MTP2_CRITICAL_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetLevelOnOffByName(MTP2_NMS_TraceData,
                                      MTP2_CRITICAL_STRING, ITS_FALSE);
        }
    }

    /* Error Trace */
    if (RESFILE_GetKeyValueOf(tr->transport.res, NMS_INI_SECTION_NAME,
                              MTP2_TRACE_ERROR_STRING, buf, 1024) == ITS_SUCCESS)
    {
        ITS_BOOLEAN flag = ITS_FALSE;

        if (strstr(buf, MTP2_STDOUT_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_STDOUT_STRING, ITS_TRUE);
            flag = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_STDOUT_STRING, ITS_FALSE);
        }
        if (strstr(buf, MTP2_FILE_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_FILE_STRING, ITS_TRUE);
            flag = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_FILE_STRING, ITS_FALSE);
        }
        if (strstr(buf, MTP2_SYSLOG_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_SYSLOG_STRING, ITS_TRUE);
            flag = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_SYSLOG_STRING, ITS_FALSE);
        }

        if (flag)
        {
            TRACE_SetLevelOnOffByName(MTP2_NMS_TraceData,
                                      MTP2_ERROR_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetLevelOnOffByName(MTP2_NMS_TraceData,
                                      MTP2_ERROR_STRING, ITS_FALSE);
        }
    }

    /* Warning Trace */
    if (RESFILE_GetKeyValueOf(tr->transport.res, NMS_INI_SECTION_NAME,
                              MTP2_TRACE_WARNING_STRING, buf, 1024) == ITS_SUCCESS)
    {
        ITS_BOOLEAN flag = ITS_FALSE;

        if (strstr(buf, MTP2_STDOUT_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_STDOUT_STRING, ITS_TRUE);
            flag = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_STDOUT_STRING, ITS_FALSE);
        }
        if (strstr(buf, MTP2_FILE_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_FILE_STRING, ITS_TRUE);
            flag = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_FILE_STRING, ITS_FALSE);
        }
        if (strstr(buf, MTP2_SYSLOG_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_SYSLOG_STRING, ITS_TRUE);
            flag = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_SYSLOG_STRING, ITS_FALSE);
        }

        if (flag)
        {
            TRACE_SetLevelOnOffByName(MTP2_NMS_TraceData,
                                      MTP2_WARNING_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetLevelOnOffByName(MTP2_NMS_TraceData,
                                      MTP2_WARNING_STRING, ITS_FALSE);
        }
    }

    /* Debug Trace */
    if (RESFILE_GetKeyValueOf(tr->transport.res, NMS_INI_SECTION_NAME,
                              MTP2_TRACE_DEBUG_STRING, buf, 1024) == ITS_SUCCESS)
    {
        ITS_BOOLEAN flag = ITS_FALSE;

        if (strstr(buf, MTP2_STDOUT_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_STDOUT_STRING, ITS_TRUE);
            flag = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_STDOUT_STRING, ITS_FALSE);
        }
        if (strstr(buf, MTP2_FILE_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_FILE_STRING, ITS_TRUE);
            flag = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_FILE_STRING, ITS_FALSE);
        }
        if (strstr(buf, MTP2_SYSLOG_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_SYSLOG_STRING, ITS_TRUE);
            flag = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_SYSLOG_STRING, ITS_FALSE);
        }

        if (flag)
        {
            TRACE_SetLevelOnOffByName(MTP2_NMS_TraceData,
                                      MTP2_DEBUG_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetLevelOnOffByName(MTP2_NMS_TraceData,
                                      MTP2_DEBUG_STRING, ITS_FALSE);
        }
    }

    if (nms_debug)
    {
        printf("ITS read the following:\n");
        printf("      boardNum: %d\n", handle->boardNum);
        printf("         sapId: %d\n", handle->sapid);
        printf("     mtp3SapId: %d\n", handle->mtp3Sapid);
        printf("     isupSapId: %d\n", handle->isupSapid);
        printf("        srcEnt: %d\n", handle->srcEnt);
#if NMS_VERSION >= 3080
        printf("    mtp2SrcEnt: %d\n", handle->mtp2SrcEnt);
#endif
        printf("    mtp3SrcEnt: %d\n", handle->mtp3SrcEnt);
        printf("isupMgmtSrcEnt: %d\n", handle->isupMgmtSrcEnt);
        printf("    isupSrcEnt: %d\n", handle->isupSrcEnt);
        printf("       srcInst: %d\n", handle->srcInst);
        printf("    servUserId: %d\n", handle->servUserId);
        printf("           opc: %ld\n", handle->opc);
        printf("           dpc: %ld\n", handle->dpc);
        printf("           ssn: %d\n", handle->ssn[0]);
        printf("       destSsn: %d\n", handle->destSsn);
        printf("          type: %d\n", handle->type);
        printf("           sio: %d\n", handle->sio);
    }

    TRANSPORT_UnfindTransport(tr);

    return (ITS_SUCCESS);
}

#ifdef WIN32

/*implementation:static
***************************************************************************
*  Purpose:
*      Wait used in the PeekNextEvent and GetNextEvent 
*
*  Input Parameters:
*      handle, millisecs
*
*  Input/Output Parameters:
*      indic_flag.
*
*  Output Parameters:
*      None.
*
*  Return Value:
*      ITS_SUCCESS.
***************************************************************************/
static int
WaitForIndication(ITS_SS7_HANDLE handle,
                  int *indic_flag, int millisecs)
{
    int hcount = 0, i;
    ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *)handle;    
    unsigned long waitRes;
    int lastError;
    HANDLE handles[ITS_MAX_HANDLES];
    int indics[ITS_MAX_HANDLES];
    CTA_EVENT  event;

    i = 0;
    hcount = 0;
    memset(indics, 0, sizeof(int) * ITS_MAX_HANDLES);
    *indic_flag = 0;

    /*
     * if NMS can do multiple parts at the same time, remove the else
     * from "else if"
     */
    if ((TRANSPORT_MASK(VENDOR_OWNING_TRANSPORT(context)) & ITS_TCAP) == ITS_TCAP)
    {
        indics[hcount] = EVENT_FROM_TCAP;
        handles[hcount++] = context->tcapSync;
    }
    if ((TRANSPORT_MASK(VENDOR_OWNING_TRANSPORT(context)) & ITS_SCCP) == ITS_SCCP)
    {
        indics[hcount] = EVENT_FROM_SCCP;
        handles[hcount++] = context->sccpSync;
    }

#if NMS_VERSION >= 3050

#if defined(INCLUDE_ISUP)

    if ((TRANSPORT_MASK(VENDOR_OWNING_TRANSPORT(context)) & ITS_ISUP) == ITS_ISUP)
    {
        unsigned int size;
        unsigned int nbfd = 0;

        if (ctaQueryWaitObjects(context->isupCtaQueueHd,
                                NULL, 0, &nbfd) != SUCCESS)
        {
            printf("Unable to query WaitObjects\n");

            NMSTermISUP(handle);

            exit(7);
        }

        if (hcount + nbfd >= ITS_MAX_HANDLES)
        {
            printf("Handle count overflow\n");

            NMSTermISUP(handle);

            exit(8);
        }

        size = sizeof(CTA_WAITOBJ) * nbfd;

        if (ctaQueryWaitObjects(context->isupCtaQueueHd, 
                                (CTA_WAITOBJ *)&handles[hcount],
                                size, &nbfd) != SUCCESS)
        {
            printf("Unable to query WaitObjects\n");

            NMSTermISUP(handle);

            exit(9);
        }

        for (i = hcount; i < hcount + nbfd; i++)
        {
            indics[i] = EVENT_FROM_ISUP;
        }

        hcount += nbfd;
    }

#endif /* INCLUDE_ISUP */

#endif

#if NMS_VERSION < 3080

    if ((TRANSPORT_MASK(VENDOR_OWNING_TRANSPORT(context)) & ITS_MTP3) == ITS_MTP3)
    {
        indics[hcount] = EVENT_FROM_MTP3;
        handles[hcount++] = context->mtp3Sync;
    }
#else

#if defined(INCLUDE_MTP3)

    if ((TRANSPORT_MASK(VENDOR_OWNING_TRANSPORT(context)) & ITS_MTP3) == ITS_MTP3)
    {
        unsigned int size;
        unsigned int nbfd = 0;

        if (ctaQueryWaitObjects(context->mtp3CtaQueueHd,
                                NULL, 0, &nbfd) != SUCCESS)
        {
            printf("Unable to query WaitObjects\n");

            NMSTermMTP3(handle);

            exit(4);
        }

        if (hcount + nbfd >= ITS_MAX_HANDLES)
        {
            printf("Handle count overflow\n");

            NMSTermMTP3(handle);

            exit(5);
        }

        size = sizeof(CTA_WAITOBJ) * nbfd;

        if (ctaQueryWaitObjects(context->mtp3CtaQueueHd, 
                                (CTA_WAITOBJ *)&handles[hcount],
                                size, &nbfd) != SUCCESS)
        {
           printf("Unable to query WaitObjects\n");

           ctaDestroyQueue (context->isupCtaQueueHd);

           exit(6);
        }

        for (i = hcount; i < hcount + (int)nbfd; i++)
        {
            indics[i] = EVENT_FROM_MTP3;
        }

        hcount += nbfd;
    }

#endif /* INCLUDE_MTP3 */

#endif

#if NMS_VERSION >= 3080
    if ((TRANSPORT_MASK(VENDOR_OWNING_TRANSPORT(context)) & ITS_MTP2) == ITS_MTP2)
    {
        indics[hcount] = EVENT_FROM_MTP2;
        handles[hcount++] = context->mtp2Sync;
    }

	waitRes = ctaWaitEvent(context->mtp2Sync, &event, millisecs);
                            

    switch (waitRes)
    {
    case CTAEVN_WAIT_TIMEOUT:
        return ITS_ETIMEOUT;

    case SUCCESS:
        *indic_flag = EVENT_FROM_MTP2;
        return (ITS_SUCCESS);

    default:
		*indic_flag |= EVENT_FROM_MTP2;
        return ITS_SUCCESS;
    }

#endif

    /*
     * wait for something to be signalled
     */
    waitRes = WaitForMultipleObjects(hcount, handles, ITS_FALSE, millisecs);

    switch (waitRes)
    {
    case WAIT_FAILED:
        lastError = GetLastError();

        return ITS_ERCVFAIL;

    case WAIT_TIMEOUT:
        return ITS_ETIMEOUT;

    default: /* AKA WAIT_OBJECT_0 */
        waitRes -= WAIT_OBJECT_0;

        *indic_flag = indics[waitRes];
        return (ITS_SUCCESS); 
    }

    /* NOTREACHED */
    return (ITS_SUCCESS);
}

#endif

#if defined(UNIX)

/*implementation:static
***************************************************************************
*  Purpose:
*      Wait used in the PeekNextEvent and GetNextEvent 
*
*  Input Parameters:
*      handle, millisecs
*
*  Input/Output Parameters:
*      indic_flag.
*
*  Output Parameters:
*      None.
*
*  Return Value:
*      ITS_SUCCESS.
***************************************************************************/
static int
WaitForIndication(ITS_SS7_HANDLE handle,
                  int *indic_flag, int millisecs)
{

    ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *)handle;    

#if NMS_VERSION < 3080

    int selstat;        
    struct timeval tm;
    fd_set fds;
    unsigned int nbdesc = 0, maxfds = 0;
    int fd, i;
    CTA_WAITOBJ waitobjs[ITS_MAX_HANDLES];
    unsigned nbfd, size; 
    OS_HSYNC synch = 0;

    *indic_flag = 0;

    FD_ZERO(&fds);      

    if ((TRANSPORT_MASK(VENDOR_OWNING_TRANSPORT(context)) & ITS_TCAP) == ITS_TCAP)
    {
        synch = context->tcapSync;

        if (nms_debug)
        {
            printf("ss7_tcap_sync = %d\n", synch);
        }

        FD_SET(synch, &fds);   

        maxfds = max(maxfds, synch);
    } 

    if ((TRANSPORT_MASK(VENDOR_OWNING_TRANSPORT(context)) & ITS_SCCP) == ITS_SCCP)
    {
        synch = context->sccpSync;

        if (nms_debug)
        {
            printf("ss7_sccp_synch = %d\n", synch);
        }

        FD_SET(synch, &fds);

        maxfds = max(maxfds, synch);
    }

#if NMS_VERSION >= 3050

#if defined(INCLUDE_ISUP)

    if ((TRANSPORT_MASK(VENDOR_OWNING_TRANSPORT(context)) & ITS_ISUP) == ITS_ISUP)
    {
        if (ctaQueryWaitObjects(context->isupCtaQueueHd,
                                NULL, 0, &nbfd) != SUCCESS)
        {
            printf("Unable to query WaitObjects\n");

            NMSTermISUP(handle);

            exit(4);
        }

        size = sizeof(CTA_WAITOBJ) * nbfd;

        if (nbfd >= ITS_MAX_HANDLES)
        {
            printf("Handle count overflow\n");

            NMSTermMTP3(handle);

            exit(5);
        }

        if (ctaQueryWaitObjects(context->isupCtaQueueHd, 
                                waitobjs, size, &nbfd) != SUCCESS)
        {
           printf("Unable to query WaitObjects\n");

           NMSTermISUP(handle);

           exit(6);
        }

        if (nms_debug)
        {
            for (i = 0; i < nbfd; i++)
            {           
               printf("i: %d - fd: %d\n", i, waitobjs[i].fd);
            }
        }

        for (i = 0; i < nbfd; i++)
        {
           fd = waitobjs[i].fd;
           FD_SET(fd, &fds);
           nbdesc = fd > nbdesc ? fd : nbdesc;
        }

        maxfds = max(maxfds, nbdesc); 
    }

#endif /* INCLUDE_ISUP */

#endif

    if ((TRANSPORT_MASK(VENDOR_OWNING_TRANSPORT(context)) & ITS_MTP3) == ITS_MTP3)
    {
        synch = context->mtp3Sync;

        if (nms_debug)
        {
            printf("ss7_mtp3_synch = %d\n", synch); 
        }

        FD_SET(synch, &fds);

        maxfds = max(maxfds, synch); 
    }

    maxfds++;
    if (nms_debug)
    {
        printf("NMSVendor: maxfd = %d\n", maxfds); 
    }

    if (millisecs == ITS_INFINITE)
    {
        selstat = select(maxfds, &fds, 0, 0, 0);

        if (selstat < 0)
        {
            if (nms_debug)
            {
                printf("NMSVendor: No event\n");
            }

            return ITS_ENOMSG;
        }
    }
    else
    {
        memset((char *)&tm, 0, sizeof(struct timeval));

        tm.tv_usec = (millisecs % 1000) * 10;
        tm.tv_sec = millisecs / 1000;        
        selstat = select(maxfds, &fds, 0, 0, &tm);

        if (selstat <= 0)
        {
            if (nms_debug)
            {
                printf("NMSVendor: No event\n");  
            }

            return ITS_ENOMSG;
        }
    }

    if ((TRANSPORT_MASK(VENDOR_OWNING_TRANSPORT(context)) & ITS_TCAP) == ITS_TCAP)
    {
        if (FD_ISSET(context->tcapSync, &fds))
        {
            if (nms_debug)
            {
                printf("NMSVendor: flag for TCAP set\n");
            }

            *indic_flag |= EVENT_FROM_TCAP; 

            return ITS_SUCCESS;
        }
    }

    if ((TRANSPORT_MASK(VENDOR_OWNING_TRANSPORT(context)) & ITS_SCCP) == ITS_SCCP)
    {
        if (FD_ISSET(context->sccpSync, &fds))
        {
            if (nms_debug)
            {
                printf("NMSVendor: flag for SCCP set\n");
            }

            *indic_flag |= EVENT_FROM_SCCP; 

            return ITS_SUCCESS;
        }
    }

    if ((TRANSPORT_MASK(VENDOR_OWNING_TRANSPORT(context)) & ITS_ISUP) == ITS_ISUP)
    {
        for (i = 0; i < nbfd; i++)
        {
            fd = waitobjs[i].fd;           
            if (FD_ISSET(fd, &fds))
            {
                if (nms_debug)
                {
                    printf("NMSVendor: flag for ISUP set\n");
                }

                *indic_flag |= EVENT_FROM_ISUP;

                return ITS_SUCCESS;
            }
        }
    }

    if ((TRANSPORT_MASK(VENDOR_OWNING_TRANSPORT(context)) & ITS_MTP3) == ITS_MTP3)
    {
        if (FD_ISSET(context->mtp3Sync, &fds))
        {
            if (nms_debug)
            {
                /*printf("NMSVendor: flag for MTP3 set\n");*/
            }

            *indic_flag |= EVENT_FROM_MTP3; 

            return ITS_SUCCESS;
        }
    }

    return (ITS_ENOMSG);

#else  /*>= 3080*/

#if defined(INCLUDE_MTP3)

    CTA_EVENT ctaEvent;

    if (nms_debug)
    {
        printf("Calling ctaWaitEvent() in WaitForIndication ------- \n");
    }
    
    if (ctaWaitEvent(context->mtp3CtaQueueHd, &ctaEvent, CTA_WAIT_FOREVER) != SUCCESS )
    {
        printf("ctaWaitEvent failed in WaitForIndication ...\n");
        return !ITS_SUCCESS;
    }
    switch (ctaEvent.id)
    {
    case MTP3EVN_DATA:
        *indic_flag = EVENT_FROM_MTP3;
        if(nms_debug)
        {
            printf("Received MTP3EVN_DATA ...\n");
        }
        break;
#if defined(INCLUDE_ISUP)
    case ISUPEVN_DATA:
        *indic_flag =EVENT_FROM_ISUP;
        if(nms_debug)
        {
            printf("Received ISUPEVN_DATA ...\n");
        }
        break;
#endif
    case CTAEVN_OPEN_SERVICES_DONE:
        if(nms_debug)
        {
            printf("Received CTAEVN_OPEN_SERVICES_DONE ...\n");
        }
        return ITS_ENOMSG;
    default:
        if(nms_debug)
        {
            printf("Received Unknown event...\n");
        }
        return ITS_ENOMSG;
    }
    return ITS_SUCCESS;

#else /* INCLUDE_MTP3*/

    OS_HSYNC synch = 0;

    struct pollfd fds[1];
    int timeout_msecs = 200000;
    FD_ZERO(&fds);
    
    if ((TRANSPORT_MASK(VENDOR_OWNING_TRANSPORT(context)) & ITS_MTP2) == ITS_MTP2)
    {
        synch = context->mtp2Sync;

        if (nms_debug)
        {
            printf("ss7_mtp2_synch = %d\n", synch);
        }

        fds[0].fd = synch;
        fds[0].events = POLLIN;
        fds[0].revents = 0;
    }

    if (poll(fds, 1, timeout_msecs) <= 0)
    {
        if (nms_debug)
        {
            printf("NMSVendor: No event\n");  /* tmp commented - hari */
        }

        return ITS_ENOMSG;
    }

    if ((TRANSPORT_MASK(VENDOR_OWNING_TRANSPORT(context)) & ITS_MTP2) == ITS_MTP2
)
    {
        if(fds[0].revents && POLLIN)
        {
            if (nms_debug)
            {
                printf("NMSVendor: flag for MTP2 set\n");
            }

            *indic_flag |= EVENT_FROM_MTP2;

            return ITS_SUCCESS;
        }
    }
    return ITS_SUCCESS;

#endif

#endif /* >= 3080 */

}
#endif /* (UNIX) */

#if defined(ANSI)

int
ClassInit(ITS_Class objClass)
{
    ITS_CLASS_SUPERCLASS(itsNMS_ClassANSI) = itsSS7STACK_ClassANSI;

    return (ITS_SUCCESS);
}

VENDOR_ClassRec itsNMS_ClassRecANSI =
{
    /* core */
    {
        NULL,                       /* superclass */
        sizeof(ITS_SS7_CONTEXT),    /* instance size */
        ITS_FALSE,                  /* not initted */
        0,                          /* initial ref count */
        "itsNMS_ClassANSI",           /* class name: replace with your vendor */
        ClassInit,                  /* no class init */
        ITS_CLASS_NO_DEST,          /* no class dest */
        ITS_CLASS_PART_NO_INIT,     /* class part init */
        ITS_CLASS_PART_NO_DEST,     /* class part destroy */
        ITS_INST_NO_CONST,          /* no instantiate */
        ITS_INST_NO_DEST,           /* no destroy */
        NULL                        /* extension */
    },
    /* stack (everything inherits from vframe) */
    {
        NULL,               /* getNextEvent */
        NULL,               /* peekNextEvent */
        NULL                /* putEvent */
    },
    /* vendor */
    {
#if defined(STANDALONE)
        ReadInstance_STANDALONE,
#else
        ReadInstance_INTEGRATED,
#endif
        WaitForIndication,
        /* MTP2 */
        {
#if defined(INCLUDE_MTP2)
            NMSInitializeMTP2,
            NMSTermMTP2,
#if NMS_VERSION >= 4000
            NMSHandleNotification,
#else
            NMSRetrieveMTP2Message,
#endif
            NMSSendMTP2Event,
            NMSCommit
#else
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
#endif
        },
        /* MTP3 */
        {
#if defined(INCLUDE_MTP3)
            NMSInitializeMTP3,
            NMSTermMTP3,
            NMSRetrieveMTP3Message,
            NMSSendMTP3Event,
            NULL,
            NULL,
            NULL
#else
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
#endif
        },
        /* ISUP */
        {
#if defined(INCLUDE_ISUP)
            NMSInitializeISUP,
            NMSTermISUP,
            NULL,
            NULL,
            NMSRetrieveISUPMessage,
            NULL,
            NULL,
            NMSSendISUPEvent,
            NULL,
            NULL
#else
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
#endif
        },
        /* SCCP */
        {
#if defined(INCLUDE_SCCP)
            NMSInitializeSCCP,
            NMSTermSCCP,
            NMSGetNextLocalRef,
            NMSRetrieveSCCPMessage,
            NMSSendSCCPEvent,
            NMSSendUserOutOfService,
            NMSSendUserInService,
            NMSSetCongestion,
            NULL
#else
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
#endif
        },
        /* TCAP */
        {
#if defined(INCLUDE_TCAP)
            NMSInitializeTCAP,
            NMSTermTCAP,
            NMSAllocDID,
            NMSRetrieveTCAPMessage,
            NMSSendComponent,
            NMSSendDialogue,
            NULL,
            NULL,
            NULL,
            NULL,
            NMSSendTCAPUOS,
            NMSSendTCAPUIS,
            NMSSetTCAPCong,
            NULL
#else
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
#endif
        }
    }
};

VSS7DLLAPI ITS_Class itsNMS_ClassANSI = (ITS_Class)&itsNMS_ClassRecANSI;

#elif defined(CCITT)

int
ClassInit(ITS_Class objClass)
{
    ITS_CLASS_SUPERCLASS(itsNMS_ClassCCITT) = itsSS7STACK_ClassCCITT;

    return (ITS_SUCCESS);
}

VENDOR_ClassRec itsNMS_ClassRecCCITT =
{
    /* core */
    {
        NULL,                       /* superclass */
        sizeof(ITS_SS7_CONTEXT),    /* instance size */
        ITS_FALSE,                  /* not initted */
        0,                          /* initial ref count */
        "itsNMS_ClassCCITT",          /* class name: replace with your vendor */
        ClassInit,                  /* no class init */
        ITS_CLASS_NO_DEST,          /* no class dest */
        ITS_CLASS_PART_NO_INIT,     /* class part init */
        ITS_CLASS_PART_NO_DEST,     /* class part destroy */
        ITS_INST_NO_CONST,          /* no instantiate */
        ITS_INST_NO_DEST,           /* no destroy */
        NULL                        /* extension */
    },
    /* stack (everything inherits from vframe) */
    {
        NULL,               /* getNextEvent */
        NULL,               /* peekNextEvent */
        NULL                /* putEvent */
    },
    /* vendor */
    {
#if defined(STANDALONE)
        ReadInstance_STANDALONE,
#else
        ReadInstance_INTEGRATED,
#endif
        WaitForIndication,
        /* MTP2 */
        {
#if defined(INCLUDE_MTP2)
            NMSInitializeMTP2,
            NMSTermMTP2,
#if NMS_VERSION >= 4000
            NMSHandleNotification,
#else
            NMSRetrieveMTP2Message,
#endif
            NMSSendMTP2Event,
            NMSCommit
#else
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
#endif
        },
        /* MTP3 */
        {
#if defined(INCLUDE_MTP3)
            NMSInitializeMTP3,
            NMSTermMTP3,
            NMSRetrieveMTP3Message,
            NULL,
            NMSSendMTP3Event,
            NULL,
            NULL
#else
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
#endif
        },
        /* ISUP */
        {
#if defined(INCLUDE_ISUP)
            NMSInitializeISUP,
            NMSTermISUP,
            NULL,
            NULL,
            NMSRetrieveISUPMessage,
            NULL,
            NULL,
            NULL,
            NMSSendISUPEvent,
            NULL
#else
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
#endif
        },
        /* SCCP */
        {
#if defined(INCLUDE_SCCP)
            NMSInitializeSCCP,
            NMSTermSCCP,
            NMSGetNextLocalRef,
            NMSRetrieveSCCPMessage,
            NMSSendSCCPEvent,
            NMSSendUserOutOfService,
            NMSSendUserInService,
            NMSSetCongestion,
            NULL
#else
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
#endif
        },
        /* TCAP */
        {
#if defined(INCLUDE_TCAP)
            NMSInitializeTCAP,
            NMSTermTCAP,
            NMSAllocDID,
            NMSRetrieveTCAPMessage,
            NMSSendComponent,
            NMSSendDialogue,
            NULL,
            NULL,
            NULL,
            NULL,
            NMSSendTCAPUOS,
            NMSSendTCAPUIS,
            NMSSetTCAPCong,
            NULL
#else
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
#endif
        }
    }
};

VSS7DLLAPI ITS_Class itsNMS_ClassCCITT = (ITS_Class)&itsNMS_ClassRecCCITT;

#elif defined(PRC)

int
ClassInit(ITS_Class objClass)
{
    ITS_CLASS_SUPERCLASS(itsNMS_ClassPRC) = itsSS7STACK_ClassPRC;

    return (ITS_SUCCESS);
}

VENDOR_ClassRec itsNMS_ClassRecPRC =
{
    /* core */
    {
        NULL,                       /* superclass */
        sizeof(ITS_SS7_CONTEXT),    /* instance size */
        ITS_FALSE,                  /* not initted */
        0,                          /* initial ref count */
        "itsNMS_ClassPRC",          /* class name: replace with your vendor */
        ClassInit,                  /* no class init */
        ITS_CLASS_NO_DEST,          /* no class dest */
        ITS_CLASS_PART_NO_INIT,     /* class part init */
        ITS_CLASS_PART_NO_DEST,     /* class part destroy */
        ITS_INST_NO_CONST,          /* no instantiate */
        ITS_INST_NO_DEST,           /* no destroy */
        NULL                        /* extension */
    },
    /* stack (everything inherits from vframe) */
    {
        NULL,               /* getNextEvent */
        NULL,               /* peekNextEvent */
        NULL                /* putEvent */
    },
    /* vendor */
    {
#if defined(STANDALONE)
        ReadInstance_STANDALONE,
#else
        ReadInstance_INTEGRATED,
#endif
        WaitForIndication,
        /* MTP2 */
        {
#if defined(INCLUDE_MTP2)
            NMSInitializeMTP2,
            NMSTermMTP2,
#if NMS_VERSION >= 4000
            NMSHandleNotification,
#else
            NMSRetrieveMTP2Message,
#endif
            NMSSendMTP2Event,
            NMSCommit
#else
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
#endif
        },
        /* MTP3 */
        {
#if defined(INCLUDE_MTP3)
            NMSInitializeMTP3,
            NMSTermMTP3,
            NMSRetrieveMTP3Message,
            NULL,
            NULL,
            NMSSendMTP3Event,
            NULL
#else
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL 
#endif
        },
        /* ISUP */
        {
#if defined(INCLUDE_ISUP)
            NMSInitializeISUP,
            NMSTermISUP,
            NULL,
            NULL,
            NMSRetrieveISUPMessage,
            NULL,
            NULL,
            NULL,
            NMSSendISUPEvent,
            NULL
#else
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
#endif
        },
        /* SCCP */
        {
#if defined(INCLUDE_SCCP)
            NMSInitializeSCCP,
            NMSTermSCCP,
            NMSGetNextLocalRef,
            NMSRetrieveSCCPMessage,
            NMSSendSCCPEvent,
            NMSSendUserOutOfService,
            NMSSendUserInService,
            NMSSetCongestion,
            NULL
#else
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
#endif
        },
        /* TCAP */
        {
#if defined(INCLUDE_TCAP)
            NMSInitializeTCAP,
            NMSTermTCAP,
            NMSAllocDID,
            NMSRetrieveTCAPMessage,
            NMSSendComponent,
            NMSSendDialogue,
            NULL,
            NULL,
            NULL,
            NULL,
            NMSSendTCAPUOS,
            NMSSendTCAPUIS,
            NMSSetTCAPCong,
            NULL
#else
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
#endif
        }
    }
};

VSS7DLLAPI ITS_Class itsNMS_ClassPRC = (ITS_Class)&itsNMS_ClassRecPRC;

#endif

#if defined(STANDALONE)
#if defined(ANSI)
VSS7DLLAPI ITS_Class itsSS7STANDALONE_Class = (ITS_Class)&itsNMS_ClassRecANSI;
#elif defined(CCITT)
VSS7DLLAPI ITS_Class itsSS7STANDALONE_Class = (ITS_Class)&itsNMS_ClassRecCCITT;
#elif defined(PRC)
VSS7DLLAPI ITS_Class itsSS7STANDALONE_Class = (ITS_Class)&itsNMS_ClassRecPRC;
#endif
#endif
