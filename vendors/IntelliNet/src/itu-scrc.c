/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
 *                            All Rights Reserved.                          *
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
 *  ID: $Id: itu-scrc.c,v 9.13.6.2.36.1 2014/09/17 07:01:58 jsarvesh Exp $
 *
 * LOG: $Log: itu-scrc.c,v $
 * LOG: Revision 9.13.6.2.36.1  2014/09/17 07:01:58  jsarvesh
 * LOG: Changes done for removing warnings
 * LOG:
 * LOG: Revision 9.13.6.2.30.1  2014/09/15 07:23:33  jsarvesh
 * LOG: Changes done for removing Warnings
 * LOG:
 * LOG: Revision 9.13.6.2  2010/04/16 22:38:17  ssingh
 * LOG: in -r9.13.6.1, setting sls got removed; bringing back
 * LOG:
 * LOG: Revision 9.13.6.1  2010/03/29 09:05:00  ssingh
 * LOG: issue fixing in support of SMLC-2591
 * LOG:
 * LOG: Revision 9.13  2008/07/18 05:35:49  ssingh
 * LOG: SDS ID:: ID :: D0240 Warning removal for Solaris Compilation
 * LOG:
 * LOG: Revision 9.12  2008/06/20 09:11:14  ssingh
 * LOG: updated with code review comments, ipDestination check
 * LOG: removed as not working in ASP configuration.
 * LOG:
 * LOG: Revision 9.11  2008/06/12 12:51:49  nvijikumar
 * LOG: Renaming from COT to CPOT (CCITT prime - 16bit)
 * LOG: ACC-CG-SDS-SS7-V1.0.02::ID:: D6030
 * LOG:
 * LOG: Revision 9.10  2008/06/04 10:36:35  ssingh
 * LOG: ALU porting, B-0100LX-LUSG-00 (june 04,2008 base)
 * LOG:
 * LOG: Revision 9.9  2008/04/15 05:03:18  kramesh
 * LOG: Merged Persistent Branch Changes to current.
 * LOG:
 * LOG: Revision 9.8.2.3  2007/08/16 12:40:58  pspl
 * LOG: Fixed Bug 28, added a check at SCCP level in function SCCP_SendToMTP3() to
 * LOG: check node state and then send SCCP message down to MTP3. (Vipul)
 * LOG:
 * LOG: Revision 9.8.2.2  2007/07/31 11:25:31  pspl
 * LOG: Added check for valid GTT Length and GT Indicator (Abhijeet/Rajnikant-PSPL)
 * LOG:
 * LOG: Revision 9.8.2.1  2007/04/24 14:11:23  pspl
 * LOG: Added check for hop counter range value and protocol class (Rahul)
 * LOG:
 * LOG: Revision 9.8  2007/01/11 12:43:38  yranade
 * LOG: Merge changes from 6.5.3 and Lucent branches
 * LOG:
 * LOG: Revision 9.7  2005/12/09 21:01:13  cbashyam
 * LOG: Bug fixes for Bug ID : 2595
 * LOG: $Log:
 * LOG: Revision 9.6.4.13  2008/04/11 15:08:02  ssodhi
 * LOG: All messages in a connection should go on same link
 * LOG:
 * LOG: Revision 9.6.4.12  2008/04/10 12:34:14  ssodhi
 * LOG: Fixing warnings
 * LOG:
 * LOG: Revision 9.6.4.11  2008/01/03 04:43:49  skatta
 * LOG: changes for loadsharing on more than 16 links
 * LOG:
 * LOG: Revision 9.6.4.10  2007/10/05 11:05:28  mshanmugam
 * LOG: CPOT Stack support as per Desin Id - D0050
 * LOG:
 * LOG: Revision 9.6.4.9  2007/05/11 10:47:53  raghavendrabk
 * LOG: ROUTE_GetRoutingKeyRouteInfo API called to get RoutingKey Route info
 * LOG:
 * LOG: Revision 9.6.4.8  2007/02/13 12:02:25  raghavendrabk
 * LOG: Warning removed for Alarms
 * LOG:
 * LOG: Revision 9.6.4.7  2007/02/13 03:58:47  raghavendrabk
 * LOG: Changed alarm format to put family at beginning
 * LOG:
 * LOG: Revision 9.6.4.6  2007/02/02 14:27:32  raghavendrabk
 * LOG: Parallel Stack changes for Alarms and Statistics
 * LOG:
 * LOG: Revision 9.6  2005/06/02 12:37:14  adutta
 * LOG: Fixed issue#1919
 * LOG:
 * LOG: Revision 9.5  2005/05/25 06:33:05  adutta
 * LOG: LUDT implementation
 * LOG:
 * LOG: Revision 9.4  2005/04/29 12:35:08  ssingh
 * LOG: Revision 9.2 is taken back as breaking ACTIVE-ACTIVE redundancy.
 * LOG:
 * LOG: Revision 9.3  2005/04/06 11:26:23  mmanikandan
 * LOG: Bug Propagation and Validation bug Fix.
 * LOG:
 * LOG: Revision 9.2  2005/04/01 10:29:33  ssingh
 * LOG: Bug Fix Propagation to PR6.5, Bug# 817
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:43  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.6  2005/03/21 13:53:48  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.5.2.4.2.3.4.4  2005/01/31 09:32:46  dsatish
 * LOG: ANSI over TTC, ANSI over PRC split stack changes merged in DVLP branch.
 * LOG:
 * LOG: Revision 7.5.2.4.2.3.4.3  2004/12/29 14:00:11  csireesh
 * LOG: SCCP bug propogation and OAM Changes
 * LOG:
 * LOG: Revision 7.5.2.4.2.3.4.2  2004/12/17 03:57:46  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.5.2.4.2.3.4.1  2004/12/07 11:47:18  mmanikandan
 * LOG: Bug in Event Dump.
 * LOG:
 * LOG: Revision 7.5.2.4.2.3  2004/11/25 11:22:29  yranade
 * LOG: Oops.
 * LOG:
 * LOG: Revision 7.5.2.4.2.2  2004/11/22 12:45:35  yranade
 * LOG: Printing Hex Dumps change done by Abhijit.
 * LOG:
 * LOG: Revision 7.5.2.4.2.1  2004/06/22 11:47:54  csireesh
 * LOG: ALARMS and PEGS Propogation from TCS branch.
 * LOG:
 * LOG: Revision 7.5.2.4  2003/10/17 19:36:27  hcho
 * LOG: Handled SCOC routing failure to the user.
 * LOG:
 * LOG: Revision 7.5.2.3  2003/09/08 08:36:10  aganguly
 * LOG: Hop counter logic got modified.
 * LOG:
 * LOG: Revision 7.5.2.2  2003/05/21 14:01:08  aganguly
 * LOG: Modified the log statement for Invalid protocol class.
 * LOG:
 * LOG: Revision 7.5.2.1  2003/05/13 06:48:14  aganguly
 * LOG: Bug fix for SCLC involving protocol class check.
 * LOG:
 * LOG: Revision 7.5  2003/02/05 17:34:29  aganguly
 * LOG: Changes for SCCP Alarms: Clean up of unwanted alarms left for Release 6.4
 * LOG:
 * LOG: Revision 7.4  2002/12/16 18:12:23  ngoel
 * LOG: use ssn=1 for sst routing
 * LOG:
 * LOG: Revision 7.3  2002/11/09 22:02:25  randresol
 * LOG: Do not invoke ITS_EVENT_TERM when message is passed to our MTP3
 * LOG:
 * LOG: Revision 7.2  2002/09/11 19:34:44  yranade
 * LOG: Loadsharing logic fix
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:28  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.10  2002/08/22 16:19:13  mmiers
 * LOG: Short names for SCMG
 * LOG:
 * LOG: Revision 6.9  2002/08/16 22:07:09  mmiers
 * LOG: Include China variant.
 * LOG:
 * LOG: Revision 6.8  2002/07/29 18:08:37  ngoel
 * LOG: increment total message peg
 * LOG:
 * LOG: Revision 6.7  2002/06/21 22:49:38  mmiers
 * LOG: Adding support for China variant
 * LOG:
 * LOG: Revision 6.6  2002/06/20 16:42:22  mmiers
 * LOG: spell it right
 * LOG:
 * LOG: Revision 6.5  2002/06/20 16:41:10  mmiers
 * LOG: hop counter detection
 * LOG:
 * LOG: Revision 6.4  2002/06/20 16:26:23  mmiers
 * LOG: Allow sending untranslated addresses to upper layers.  Whether
 * LOG: this is legal or not is open to interpretation of the spec,
 * LOG: but I believe it is within limits.
 * LOG:
 * LOG: Revision 6.3  2002/03/14 21:39:11  mmiers
 * LOG: Convert SCCP for OAM
 * LOG:
 * LOG: Revision 6.2  2002/03/07 22:21:30  mmiers
 * LOG: Merge ITU SCCP.  Doesn't build (have to work on CPC impl).
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:39  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.11  2002/01/02 19:56:09  mmiers
 * LOG: Convert to using long names (everything but TCAP).
 * LOG:
 * LOG: Revision 5.10  2001/11/08 21:16:44  mmiers
 * LOG: Bug fix for OPC.
 * LOG:
 * LOG: Revision 5.9  2001/10/17 22:14:12  mmiers
 * LOG: Forgot a comment.
 * LOG:
 * LOG: Revision 5.8  2001/10/17 22:03:12  mmiers
 * LOG: More debugging
 * LOG:
 * LOG: Revision 5.7  2001/10/04 21:31:34  mmiers
 * LOG: Today's installment.  Really need hardware at this point.
 * LOG:
 * LOG: Revision 5.6  2001/09/25 21:35:20  mmiers
 * LOG: Fix up SCCP routing and SCMG.
 * LOG:
 * LOG: Revision 5.5  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.4  2001/09/06 17:25:02  mmiers
 * LOG: Straighten out routing a bit.
 * LOG:
 * LOG: Revision 5.3  2001/09/06 00:39:57  mmiers
 * LOG: Work in the MTP2 codec.
 * LOG:
 * LOG: Revision 5.2  2001/09/05 21:07:22  mmiers
 * LOG: Small corrections.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:29  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.5  2001/07/13 16:57:45  mmiers
 * LOG: GTT on the way out bug.
 * LOG:
 * LOG: Revision 4.4  2001/06/19 19:51:18  mmiers
 * LOG: Redirect only on input.
 * LOG:
 * LOG: Revision 4.3  2001/06/11 21:42:39  mmiers
 * LOG: Pass the label to the callbacks.
 * LOG:
 * LOG: Revision 4.2  2001/05/10 16:53:58  mmiers
 * LOG: Add user intervention callbacks.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:06  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.4  2001/01/18 17:44:44  omayor
 * LOG: Use the PC from routing label to send SST.
 * LOG:
 * LOG: Revision 3.3  2000/11/14 00:18:19  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.3  2000/10/20 22:23:15  omayor
 * LOG: Add SOR, SOG SCMG procedure for duplicate SSN. Also LUDT, LUDTS
 * LOG: procedures for ITU SCCP
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:07:26  mmiers
 * LOG: Zero copy is in.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:38  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  1999/12/06 21:30:11  mmiers
 * LOG:
 * LOG:
 * LOG: Debug with HP's GDI.
 * LOG:
 * LOG: Revision 1.13.2.1  1999/12/06 21:27:31  mmiers
 * LOG:
 * LOG:
 * LOG: Debug with HP's GDI.
 * LOG:
 * LOG: Revision 1.13  1999/10/13 15:47:08  rsonak
 * LOG:
 * LOG: When GTT is performend, the OPC is now changed to the local PC
 * LOG:
 * LOG: Revision 1.12  1999/08/27 00:51:21  mmiers
 * LOG:
 * LOG:
 * LOG: Commit more work, mostly just formatting, but include ies in
 * LOG: GTT callback.  User can really get himself in trouble now.
 * LOG:
 * LOG: Revision 1.11  1999/08/26 23:45:02  labuser
 * LOG:
 * LOG:
 * LOG: Alter GTT to include original PC (if any) and SSN (if any).
 * LOG:
 * LOG: Revision 1.10  1999/08/26 20:34:01  mmiers
 * LOG:
 * LOG:
 * LOG: Fix warnings.
 * LOG:
 * LOG: Revision 1.9  1999/08/26 19:58:49  rsonak
 * LOG:
 * LOG:
 * LOG: Some protocol fixes.
 * LOG:
 * LOG: Revision 1.8  1999/07/29 21:34:03  rsonak
 * LOG:
 * LOG:
 * LOG: Rework GTT a little.
 * LOG:
 * LOG: Revision 1.7  1999/06/29 15:24:23  mmiers
 * LOG:
 * LOG:
 * LOG: Modify global title behavior a bit (allow setting of DPC only).
 * LOG:
 * LOG: Revision 1.6  1999/06/25 16:24:28  mmiers
 * LOG:
 * LOG:
 * LOG: We must modify the routing label if global title translation results
 * LOG: in a new DPC.
 * LOG:
 * LOG: Revision 1.5  1999/06/22 18:18:50  mmiers
 * LOG:
 * LOG:
 * LOG: Correct GTT handling.
 * LOG:
 * LOG: Revision 1.4  1999/06/22 16:17:26  mmiers
 * LOG:
 * LOG:
 * LOG: Add in global title translation.
 * LOG:
 * LOG: Revision 1.3  1999/06/21 22:57:53  mmiers
 * LOG:
 * LOG:
 * LOG: Fix GTT handling bugs in SCCP.
 * LOG:
 * LOG: Revision 1.2  1999/03/17 21:37:51  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol framework complete.  Now for implementation.
 * LOG:
 * LOG: Revision 1.1  1999/03/17 18:39:50  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol commit.  Still have to finish TCAP.
 * LOG:
 * LOG: Revision 1.32  1999/02/26 04:10:22  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.
 * LOG:
 * LOG: Revision 1.31  1998/12/14 23:45:30  rsonak
 * LOG: Tracking down the AT&T routing label bug.  Fixed.
 * LOG:
 * LOG: Revision 1.30  1998/11/25 23:57:38  mmiers
 * LOG: SS7 integration is complete.
 * LOG:
 * LOG: Revision 1.29  1998/11/19 01:32:00  mmiers
 * LOG: Build with warning at max.  5 bugs found.
 * LOG:
 * LOG: Revision 1.28  1998/11/17 22:37:40  mmiers
 * LOG: Propagate SCMG (SSP/SSA)
 * LOG:
 * LOG: Revision 1.27  1998/11/17 03:08:57  mmiers
 * LOG: Finish off SCMG.
 * LOG:
 * LOG: Revision 1.26  1998/11/11 03:47:38  mmiers
 * LOG: Clean up some SCCP stuff.
 * LOG:
 * LOG: Revision 1.25  1998/11/09 23:30:25  mmiers
 * LOG: Put in intermediate node code.
 * LOG:
 * LOG: Revision 1.24  1998/11/02 17:07:48  mmiers
 * LOG: Add DEBUG dump of routing label.
 * LOG:
 * LOG: Revision 1.23  1998/10/28 23:51:48  mmiers
 * LOG: Halfway through SCMG.
 * LOG:
 * LOG: Revision 1.22  1998/10/22 00:51:33  whu
 * LOG: Fix Routing Control so that we forward messages if a) we know the
 * LOG: route to them, and b) the route is available.
 * LOG:
 * LOG: Revision 1.21  1998/10/20 01:40:29  mmiers
 * LOG: include all SCCP timers.  More work on inactivity test.  Thinking
 * LOG: about SCMG.
 * LOG:
 * LOG: Revision 1.20  1998/10/16 20:45:24  mmiers
 * LOG: The "NEW! And IMPROVED!" SCCP.  Let the bug reports begin.
 * LOG:
 * LOG: Revision 1.19  1998/10/16 01:44:49  mmiers
 * LOG: Put my current thoughts into bytes.  This stuff is f*cking confusing,
 * LOG: and needs review.
 * LOG:
 * LOG: Revision 1.18  1998/10/15 23:52:39  mmiers
 * LOG: Update SCCP.  About ready to cut over.
 * LOG:
 * LOG: Revision 1.17  1998/10/01 00:11:48  mmiers
 * LOG: Port to alpha
 * LOG:
 * LOG: Revision 1.16  1998/09/30 14:22:45  mmiers
 * LOG: Fix some overnight bugs from home.
 * LOG:
 * LOG: Revision 1.15  1998/09/30 02:41:01  mmiers
 * LOG: Compromise on what we can do with SCCP.
 * LOG:
 * LOG: Revision 1.14  1998/09/29 21:39:10  mmiers
 * LOG: Revert to previous version.  This needs more thought.
 * LOG:
 * LOG: Revision 1.12  1998/09/29 17:33:06  mmiers
 * LOG: Working on MTP3/SCCP integration.
 * LOG:
 * LOG: Revision 1.11  1998/09/29 01:43:47  mmiers
 * LOG: We need PC in IsSSNAllowed_CCITT() as our SCCP is process-distributed.
 * LOG:
 * LOG: Revision 1.10  1998/09/28 17:37:54  mmiers
 * LOG: More work on SCCP.  Starting to take better shape.
 * LOG:
 * LOG: Revision 1.9  1998/09/27 00:58:49  mmiers
 * LOG: Minor tweaks preparing for connection-oriented cleanup.  Still need to
 * LOG: propagate MTP3 header to relevant pieces.
 * LOG:
 * LOG: Revision 1.8  1998/09/27 00:53:12  mmiers
 * LOG: Start cleaning up connectionless.
 * LOG:
 * LOG: Revision 1.7  1998/09/27 00:04:18  mmiers
 * LOG: More work on SCCP.
 * LOG:
 * LOG: Revision 1.6  1998/09/26 00:00:46  mmiers
 * LOG: More work on true SCCP.
 * LOG:
 * LOG: Revision 1.5  1998/09/25 21:10:57  mmiers
 * LOG: Fixup for trace.
 * LOG:
 * LOG: Revision 1.4  1998/09/24 23:27:32  mmiers
 * LOG: Continue work on improved SCCP.
 * LOG:
 * LOG: Revision 1.3  1998/09/24 19:24:39  mmiers
 * LOG: More work on SCCP.
 * LOG:
 * LOG: Revision 1.2  1998/09/24 17:31:52  mmiers
 * LOG: More working with SCCP.
 * LOG:
 * LOG: Revision 1.1  1998/09/24 16:33:13  mmiers
 * LOG: Rearrange vendor lib a little for smarter SCCP.
 * LOG:
 * LOG:
 *
 ****************************************************************************/

#include <string.h>
#include <assert.h>
#include <stdlib.h>

#undef ANSI
#undef CCITT
#if !defined(PRC) && !defined(TTC)
#define CCITT
#endif

#include <its.h>
#include <its_hash.h>
#include <its_mutex.h>
#include <its_thread.h>
#include <its_route.h>
#include <its_tq_trans.h>

#ident "$Id: itu-scrc.c,v 9.13.6.2.36.1 2014/09/17 07:01:58 jsarvesh Exp $"

#if defined(PRC) || defined(USE_PRC_SCCP)
#undef CCITT
#define PRC
#include <china/sccp.h>
#elif defined(TTC) || defined (USE_TTC_SCCP)
#undef CCITT
#define TTC
#include <japan/sccp.h>
#else
#include <itu/sccp.h>
#endif

#include "sccp_intern.h"

/* Q752 Implementation */
extern sccpOmBuffer omBuf;

extern ITS_BOOLEAN isSCCPBackup;

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
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  csireesh  20-05-2005  R0220-R0250             LUDT/LUDTS Implementation 
 * 
 *  skatta    05-Oct-2007 Design Id:             16bit-ITU-SCCP over TTC-MTP3
 *                          D0050                 Stack Support
 *
 ****************************************************************************/
static int
SCCP_SendToMTP3(MTP3_HEADER* mtp3, ITS_OCTET mType,
                ITS_SCCP_IE* ies, int ieCount,
                ITS_UINT pc, ITS_OCTET ssn)
{
    ITS_EVENT ev;
    int ret = ITS_EINVALIDARGS;
    ITS_USHORT len;
    ITS_OCTET buf[SCCP_LONG_DATA_MAX];
    ITS_OCTET ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;
    ITS_INT count;
    ITS_CHAR *buff;
    ITS_CHAR TempBuffer[10];
    //ITS_UINT sio;
    //ITS_BOOLEAN ipDestination = ITS_FALSE;
    ITS_OCTET sls;

    switch (mType)
    {
    case SCCP_MSG_CR:
        ret = SCCP_EncodeMTP3(buf, &len, mType,
                              ies, ieCount, &SCCP_CR_Desc);
        break;

    case SCCP_MSG_CC:
        ret = SCCP_EncodeMTP3(buf, &len, mType,
                              ies, ieCount, &SCCP_CC_Desc);
        break;

    case SCCP_MSG_CREF:
        ret = SCCP_EncodeMTP3(buf, &len, mType,
                              ies, ieCount, &SCCP_CREF_Desc);
        break;

    case SCCP_MSG_RLSD:
        ret = SCCP_EncodeMTP3(buf, &len, mType,
                              ies, ieCount, &SCCP_RLSD_Desc);
        break;

    case SCCP_MSG_RLC:
        ret = SCCP_EncodeMTP3(buf, &len, mType,
                              ies, ieCount, &SCCP_RLC_Desc);
        break;

    case SCCP_MSG_DT1:
        /* remove slr IE before encode */
        ieCount--;

        ret = SCCP_EncodeMTP3(buf, &len, mType,
                              ies, ieCount, &SCCP_DT1_Desc);
        break;

    case SCCP_MSG_DT2:
        ret = SCCP_EncodeMTP3(buf, &len, mType,
                              ies, ieCount, &SCCP_DT2_Desc);
        break;

    case SCCP_MSG_AK:
        ret = SCCP_EncodeMTP3(buf, &len, mType,
                              ies, ieCount, &SCCP_AK_Desc);
        break;

    case SCCP_MSG_UDT:
        ret = SCCP_EncodeMTP3(buf, &len, mType,
                              ies, ieCount, &SCCP_UDT_Desc);
        break;

    case SCCP_MSG_XUDT:
        ret = SCCP_EncodeMTP3(buf, &len, mType,
                              ies, ieCount, &SCCP_XUDT_Desc);
        break;

    case SCCP_MSG_UDTS:
        ret = SCCP_EncodeMTP3(buf, &len, mType,
                              ies, ieCount, &SCCP_UDTS_Desc);
        break;

    case SCCP_MSG_XUDTS:
        ret = SCCP_EncodeMTP3(buf, &len, mType,
                              ies, ieCount, &SCCP_XUDTS_Desc);
        break;

    case SCCP_MSG_LUDT:
        ret = SCCP_EncodeMTP3(buf, &len, mType,
                              ies, ieCount, &SCCP_LUDT_Desc);
        break;

    case SCCP_MSG_LUDTS:
        ret = SCCP_EncodeMTP3(buf, &len, mType,
                              ies, ieCount, &SCCP_LUDTS_Desc);
        break;

    case SCCP_MSG_ED:
        ret = SCCP_EncodeMTP3(buf, &len, mType,
                              ies, ieCount, &SCCP_ED_Desc);
        break;

    case SCCP_MSG_EA:
        ret = SCCP_EncodeMTP3(buf, &len, mType,
                              ies, ieCount, &SCCP_EA_Desc);
        break;

    case SCCP_MSG_RSR:
        ret = SCCP_EncodeMTP3(buf, &len, mType,
                              ies, ieCount, &SCCP_RSR_Desc);
        break;

    case SCCP_MSG_RSC:
        ret = SCCP_EncodeMTP3(buf, &len, mType,
                              ies, ieCount, &SCCP_RSC_Desc);
        break;

    case SCCP_MSG_ERR:
        ret = SCCP_EncodeMTP3(buf, &len, mType,
                              ies, ieCount, &SCCP_ERR_Desc);
        break;

    case SCCP_MSG_IT:
        ret = SCCP_EncodeMTP3(buf, &len, mType,
                              ies, ieCount, &SCCP_IT_Desc);
        break;
    }

    if (ret != ITS_SUCCESS)
    {
        SCCP_ERROR(("SCRCSendToMTP3:SCCP Encode MTP3 failed for message"));
        return (ret);
    }


    SCCP_DEBUG(("SCRCSendToMTP3: RoutingLabel: SIO %02x OPC %08x "
                "DPC %08x SLS %02x\n",
                mtp3->sio,
                MTP3_RL_GET_OPC_VALUE(mtp3->label),
                MTP3_RL_GET_DPC_VALUE(mtp3->label),
                MTP3_RL_GET_SLS(mtp3->label)));

    if ((ret = MTP3_Encode(&ev, MTP3_MSG_USER_DATA, mtp3,
                           buf, len)) != ITS_SUCCESS)
    {
        SCCP_ERROR(("SCRCSendToMTP3: MTP3_Encode failed\n"));

        /* Incr discard counter for this message type */

        return (ret);
    }
    ev.src = ITS_SCCP_SRC;

    SCCP_DEBUG(("SCRCSendToMTP3: Sending to route: pc %08x ssn %02x\n",
                pc, ssn));

    if (TRACE_IsLevelOn(SCCP_CCITT_TraceData,
                        SCCP_TRACE_DEBUG))
    {
        buff = (ITS_CHAR*)calloc(ev.len*6+1, sizeof(ITS_CHAR));

        for (count = 1; count < ev.len; count++)
        {
            sprintf(TempBuffer, "0x%02x ",ev.data[count]);
            strcat(buff,TempBuffer);
            if (!(count % 15))
            {
                strcat(buff,"\n");
            }
        }
        SCCP_DEBUG(("\n\nData send to MTP: \n\n%s\n\n",buff));
        free(buff);
    }

    /* in support with SMLC-2591 issue; equivalent check replaced */
    if (HAModeType == HA_NON_REDUNDANT || isSCCPBackup == ITS_FALSE)
    {
#if 0
        /* FIXME::this check is working only for IPSP/SG configuration
         * for ASP configuration, due to not having information about
         * routingKey route of SG, this check always fails
         * needs modification, commenting for now as of code-review input
         */

        /* Before sending the message out, check whether the message is for
           SS7 destination or IP destination... If the SCCP message is for
           IP Destination, then parse through the Routing Subsystem, else
           if the message is to the SS7 destination and the MTP3 is IntelliNet's
           then call the TRANSPORT_PutEvent - which directly puts the SCCP
           message to IntelliNet's MTP3
        */

        sio = MTP3_HDR_GET_SIO(*mtp3);

        /*Check routing key info*/
        ret = ROUTE_GetRoutingKeyRouteInfo(pc, sio, ssn, &ipDestination);

        if(ipDestination == ITS_TRUE && ret == ITS_SUCCESS)
        {
#endif
           sls = MTP3_RL_GET_SLS(mtp3->label);

            /* try to send by SSN routing */
            ret = ROUTE_SendToRouteContext(pc, &ev,
                                       ROUTE_DPC_SIO_SSN,
                                       FAMILY_ITU,
                                       ROUTE_SIO_SCCP | ni,
                                       ssn,
                                       ITS_SS7_DEFAULT_LINK_SET,
                                       ITS_SS7_DEFAULT_LINK_CODE,
                                       ITS_SS7_DEFAULT_PRI,
                                       sls);
  
#if 0
            if(ret != ITS_SUCCESS)
            {
                SCCP_ERROR(("SCRC_SendToMTP3: Failed to send SCCP Data\n"));
            }        
        }
        else
        {
            if (ev.data)
            {
#endif
            /* give to MTP3 for delivery */
            /* For CPOT stack, MTP3 SRC should be of TTC */
    
            if (ret != ITS_SUCCESS && ev.data)
            {
#if defined(CPOT_SPLIT_STACK)
                return TRANSPORT_PutEvent(ITS_MTP3_TTC_SRC, &ev);
#else
                return TRANSPORT_PutEvent(ITS_MTP3_SRC, &ev);
#endif
            }
#if 0
        }
#endif
    }
    ITS_EVENT_TERM(&ev);

    return (ret);
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
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  csireesh  04-04-2005  Bug ID:0576             Sending CREF by swaping the
 *                                                MTP3 Routing Lable.
 *
 ****************************************************************************/
int
sendConnectionRefuse(MTP3_HEADER* mtp3, ITS_USHORT conref, SCCP_ADDR *cgp)
{
    ITS_SCCP_IE info_elem[32];
    int info_Count = 0;
    MTP3_HEADER localMTP3;
    ITS_OCTET cause = SCCP_REF_DEST_UKNOWN;
    ITS_OCTET mType = SCCP_MSG_CREF;
    ITS_OCTET *gttInfo = NULL;
    ITS_USHORT gttLen = 0;
    ITS_OCTET ssn = SCCP_SSN_NONE, addrInd = 0;
    ITS_UINT pc, cgppc;
    MTP3_POINT_CODE opc, dpc;

    memset((char *)&info_elem, 0, sizeof(info_elem));

    info_elem[info_Count].param_id = SCCP_PRM_ROUTING_LABEL;
    info_elem[info_Count].param_length = sizeof(MTP3_HEADER);

    MTP3_RL_GET_DPC(mtp3->label, dpc);
    MTP3_RL_GET_OPC(mtp3->label, opc);

    pc = MTP3_RL_GET_OPC_VALUE(mtp3->label);

    MTP3_RL_SET_DPC(localMTP3.label, opc);
    MTP3_RL_SET_OPC(localMTP3.label, dpc);

    localMTP3.sio = mtp3->sio;

    info_elem[info_Count].param_data.routingLabel = localMTP3;
    info_Count++;

    info_elem[info_Count].param_id = SCCP_PRM_DEST_LOCAL_REF;
    info_elem[info_Count].param_length = sizeof(SCCP_REF_NUM);
    RN_SET_REF_NUM(info_elem[info_Count].param_data.destinationLocalReference,
                       conref);
    info_Count++;

    info_elem[info_Count].param_id = SCCP_PRM_REFUSAL_CAUSE;
    info_elem[info_Count].param_length = sizeof(SCCP_REF_CAUSE);
    info_elem[info_Count].param_data.refusalCause.cause = cause;
    info_Count++;

    if (cgp)
    {
        info_elem[info_Count].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
        info_elem[info_Count].param_length = sizeof(SCCP_ADDR);

        info_elem[info_Count].param_data.calledPartyAddr = *cgp;
        info_Count++;
        if (SCCP_DecodeAddr_CCITT(cgp, &addrInd, &cgppc, &ssn,
                            gttInfo, &gttLen) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleSCOCMsg:  Couldn't decode addr\n"));

            return (ITS_EINVALIDARGS);
        }
    }

    return SCCP_SendToMTP3(&localMTP3, mType, info_elem, info_Count, pc, ssn);
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
 ****************************************************************************/
static int
SCRCHandleRoutingFailure(MTP3_HEADER* mtp3, ITS_OCTET mType,
                         ITS_SCCP_IE* ies, int ieCount,
                         ITS_OCTET reason)
{
    switch (mType)
    {
         case SCCP_MSG_UDT:
         case SCCP_MSG_XUDT:
         case SCCP_MSG_UDTS:
         case SCCP_MSG_XUDTS:
         case SCCP_MSG_LUDT:
         case SCCP_MSG_LUDTS:
             return SCLCHandleRoutingFailure_CCITT(mtp3, mType, ies, ieCount, reason);

         default:
             return SCOCHandleRoutingFailure_CCITT(mtp3, mType, ies, ieCount, reason);
    }
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
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  ghpriya   14-02-2006  Bug ID:954              Taking NI value from MTP3
 *                                                routing label instead of
 *                                                SCCP Calling and
 *                                                CalledParty Address.
 *
 *  csireesh  04-04-2005  ACC650-SDS-PENH-1.0.1   Taking NI value from Calling
 *                        ID::B0698               and CalledParty Address.
 *
 ****************************************************************************/
static int
SCRCDeliverMTP3Ind(MTP3_HEADER* mtp3, ITS_OCTET mType,
                   ITS_SCCP_IE* ies, int ieCount,
                   ITS_OCTET addrInd, ITS_UINT pc, ITS_OCTET ssn)
{
    ITS_OCTET ni = MTP3_HDR_GET_SIO_CCITT(*mtp3) & MTP3_NIC_MASK;

    SCCP_DEBUG(("SCRCDeliverMTP3Ind\n"));

    if (!SCCP_IsSSNEquipped(ni, pc, ssn))
    {
        /* SCCP s   `t's not for us.  We can't be that tough --
         * our SCCP is distributed */
        if (SCCP_IsSSNAllowed(ni, pc, ssn))
        {
            /* deliver it --  NOT Equipped & Allowed*/
            switch (mType)
            {
                 case SCCP_MSG_UDT:
                 case SCCP_MSG_XUDT:
                 case SCCP_MSG_UDTS:
                 case SCCP_MSG_XUDTS:
                 case SCCP_MSG_LUDT:
                 case SCCP_MSG_LUDTS:
                      return SCRCHandleSCLCMsg_CCITT(mtp3, mType, ies, ieCount);

                 default:
                      /* EEK! WE'RE AN INTERMEDIATE!! */
                      return SCOCHandleSCRCMsg_CCITT(mtp3, mType, ies, ieCount,
                                               pc, ssn, ITS_TRUE);
            }
        }
        else
        {
            SCCP_DEBUG(("DeliverMTP3Ind: pc %08x ssn %02x\n",
                        pc, ssn));

            SCCP_Alarm_CCITT(643, __FILE__, __LINE__,
                             "family=%s:type=%s:pc=%x:ni=%x:ssn=%x", "CCITT", "local",
                             pc, ni, ssn);

            return SCRCHandleRoutingFailure(mtp3, mType, ies, ieCount,
                                            SCCP_RET_UNEQUIPPED_USER);
        }
    }
    else if (!SCCP_IsSSNAllowed(ni, pc, ssn))
    {
        /* Message received for unavailable subsystem */
        SCCP_Alarm_CCITT(643, __FILE__, __LINE__, 
                         "family=%s:type=%s:pc=%x:ni=%x:ssn=%x", "CCITT", "local",
                         pc, ni, ssn);

        return SCMGSSPCHandleMsgForProhibitedSSN_CCITT(mtp3, mType, ies, ieCount,
                                                       pc, ssn,
                                                       SCCP_RET_SUBSYS_FAIL);
    }
    else
    {
        /* deliver it */
        switch (mType)
        {
            case SCCP_MSG_UDT:
            case SCCP_MSG_XUDT:
            case SCCP_MSG_UDTS:
            case SCCP_MSG_XUDTS:
            case SCCP_MSG_LUDT:
            case SCCP_MSG_LUDTS:
            /* Equipped and Allowed Connection Less */
            return SCLCHandleSCRCMsg_CCITT(mtp3, mType, ies, ieCount, pc, ssn);

            default:
            /* Equipped and Allowed Connection Orientated */
            return SCOCHandleSCRCMsg_CCITT(mtp3, mType, ies, ieCount,
                                           pc, ssn, ITS_FALSE);
        }
    }

    /* NOTREACHED */
    /* return (ITS_SUCCESS); */
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
 ****************************************************************************/
static int
SCRCDeliverLocal(MTP3_HEADER* mtp3, ITS_OCTET mType,
                 ITS_SCCP_IE* ies, int ieCount,
                 ITS_OCTET addrInd, ITS_UINT pc, ITS_OCTET ssn)
{
    PEG_IncrPeg(CCITT_SCCP_Pegs,PEG_SCCP_REMOTE_MSG_FOR_LOCAL_SS_RCVD);

    /* Q752 Implementation */
    SccpGenOmImage[omBuf.activeOm].SCCPGenPegs.messageForLocalSS++;

    if (addrInd & SCCP_CPA_HAS_SSN)
    {
        return SCRCDeliverMTP3Ind(mtp3, mType, ies, ieCount,
                                  addrInd, pc, ssn);
    }
    else
    {
        switch (mType)
        {
            case SCCP_MSG_UDT:
            case SCCP_MSG_XUDT:
            case SCCP_MSG_UDTS:
            case SCCP_MSG_XUDTS:
            case SCCP_MSG_LUDT:
            case SCCP_MSG_LUDTS:
            SCCP_ERROR(("SCRCDeliverLocal: Cannot perform local delivery\n"));

            /* Incr discard counter for this type message */

            /* Incoming Message - Discarding Message - No SSN in Called Party Address.*/
            SCCP_Alarm_CCITT(644, __FILE__, __LINE__, "mType=%x", mType);

            return (ITS_EINVALIDARGS);

            default:
            return SCOCHandleSCRCMsg_CCITT(mtp3, mType, ies, ieCount,
                                           pc, ssn, ITS_FALSE);
        }
    }

    /* NOTREACHED */
    /* return (ITS_SUCCESS); */
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
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  ghpriya   14-02-2006  Bug ID:954              Taking NI value from MTP3 
 *                                                routing label instead of
 *                                                SCCP Calling and
 *                                                CalledParty Address.
 *
 *  csireesh  04-04-2005  ACC650-SDS-PENH-1.0.1   Taking NI value from Calling
 *                        ID::B0698               and CalledParty Address.
 *
 ****************************************************************************/
static int
SCRCDeliverRemote(MTP3_HEADER* mtp3, ITS_OCTET mType,
                  ITS_SCCP_IE* ies, int ieCount,
                  ITS_OCTET addrInd, ITS_UINT pc, ITS_OCTET ssn)
{
    ITS_OCTET ni = MTP3_HDR_GET_SIO_CCITT(*mtp3) & MTP3_NIC_MASK;

    if (addrInd & SCCP_CPA_HAS_SSN)
    {
        SCCP_DEBUG(("DeliverRemote: pc %08x ssn %02x\n", pc, ssn));
        
        if (!SCCP_IsSSNAllowed(ni, pc, ssn))
        {
            /* SSN is not allowed */
             SCCP_Alarm_CCITT(648, __FILE__, __LINE__,
                              "family=%s:type=%s:pc=%x:ni=%x:ssn=%x", "CCITT", "remote",
                              pc, ni, ssn);

            /* Incr discard counter for this type message */

            return SCRCHandleRoutingFailure(mtp3, mType, ies, ieCount,
                                            SCCP_RET_NETWORK_FAIL);
        }

        if (SCCP_IsSSNCongested(ni, pc, ssn))
        {

            /* Incr discard counter for this type message */

            return SCRCHandleRoutingFailure(mtp3, mType, ies, ieCount,
                                            SCCP_RET_NETWORK_CONG);
        }
    }

    return SCCP_SendToMTP3(mtp3, mType, ies, ieCount, pc, ssn);
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
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  ghpriya   14-02-2006  Bug ID:954              Taking NI value from MTP3
 *                                                routing label instead of
 *                                                SCCP Calling and
 *                                                CalledParty Address.
 * 
 *  csireesh  04-04-2005  Bug ID:0698             Taking NI value from Calling
 *                                                and CalledParty Address.
 *
 ****************************************************************************/
static int
SCRCDeliverByGTT(MTP3_HEADER* mtp3, ITS_OCTET mType,
                 ITS_SCCP_IE* ies, int ieCount, ITS_OCTET ai,
                 ITS_UINT pc, ITS_OCTET ssn,
                 ITS_OCTET *gttInfo, ITS_USHORT gttLen)
{
    SCCP_ADDR transAddr;
    ITS_UINT dpc, npc, thispc;
    ITS_OCTET nssn = SCCP_SSN_NONE, addrInd = 0;
    ITS_OCTET ni;
    int i;

    /*
       Bug ID : 6199,6201
       Description : The check for valid GTT Length and GT Indicator
    */

    if( (gttLen > 0 && ((ai & SCCP_CPA_GET_GTI) == 0))
        ||
        (gttLen <= 0 && ((ai & SCCP_CPA_GET_GTI) != 0)) )
    {
        SCCP_ERROR(("SCRCDeliverByGTT : Problem with value of GT Indicatior and/or GT Address, in CalledPartyAddress\n"));
        return SCRCHandleRoutingFailure(mtp3, mType, ies, ieCount,
                                        SCCP_RET_NO_TRANS_THIS_ADDR);
    }

    if (SCCP_GTTTranslate_CCITT(mtp3, &dpc, ai, pc, ssn, gttInfo, gttLen,
                                &transAddr, ies, ieCount) != ITS_SUCCESS)
    {
        /* Inform maintenance */
        SCCP_WARNING(("SCRCDeliverByGTT: GTT Translation failed.\n"));

        /* Q752 Implementation */
        SccpGenOmImage[omBuf.activeOm].SCCPGenPegs.syntaxConstructionErrDetected++;

        /* GTT - Global Title Translation failed. */
        SCCP_Alarm_CCITT(645, __FILE__, __LINE__, "family=%s", "CCITT");

        return SCRCHandleRoutingFailure(mtp3, mType, ies, ieCount,
                                        SCCP_RET_NO_TRANS_THIS_ADDR);
    }

    ni = MTP3_HDR_GET_SIO_CCITT(*mtp3) & MTP3_NIC_MASK;

    /* replace the CDP with the translated info */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_CALLED_PARTY_ADDR)
        {
            ies[i].param_data.calledPartyAddr = transAddr;
        }
        else if (ies[i].param_id == SCCP_PRM_HOP_COUNTER)
        {
           /* Bug id : 8
             *  Description : modified check for Hop counter violation
             */
            if (ies[i].param_data.hopCount.count <= 0 || ies[i].param_data.hopCount.count > 15)
            {
                ies[i].param_data.hopCount.count = 0;

                PEG_IncrPeg(CCITT_SCCP_Pegs,PEG_SCCP_HOP_COUNTER_VIOLATION_ERR);
   
                /* Q752 Implementation */
                SccpGenOmImage[omBuf.activeOm].SCCPGenPegs.hopCounterViolationErr++;

                
                return SCRCHandleRoutingFailure(mtp3, mType, ies, ieCount,
                                                SCCP_RET_HOP_COUNT_EXCEEDED);
            }

            ies[i].param_data.hopCount.count--;
        }
    }

    /* we must get a point code back from this */
    if (SCCP_DecodeAddr(&transAddr, &addrInd, &npc, &nssn,
                        NULL, NULL) != ITS_SUCCESS)
    {
        SCCP_ERROR(("SCRCDeliverByGTT:  Couldn't decode translated addr\n"));

        /* Incr discard counter for this Msg Type */
  
        /* SCCP Decode address failed */
        SCCP_Alarm_CCITT(646, __FILE__, __LINE__, "family=%s", "CCITT");

        return (ITS_EINVALIDARGS);
    }

    /*
     * Now we can go ahead and change the DPC as follows.
     * We can do this unconditionally, as the user has to specify
     * it (whether it changed or not).
     */

    /*
     * we need to check the point code.
     */
    thispc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
    if (!(addrInd & SCCP_CPA_HAS_PC))
    {
        MTP3_RL_SET_DPC_VALUE(mtp3->label, dpc);
        npc = dpc;
    }
    else
    {
        /* we have to change the DPC in the routing label.  This is
         * akin to what we did above with the called party addr */
        MTP3_RL_SET_DPC_VALUE(mtp3->label, npc);
        dpc = npc;
    }

    /*
     * now we have a problem.  We've got one of:
     * 1. DPC
     * 2. DPC+SSN
     * 3. DPC+GTT
     * 4. DPC+GTT+SSN
     *
     * Cases 2 and 4 are ok, we know how to deliver those.  Cases 1 and 3
     * are a problem, as our internal routing is by PC+SSN, so we don't
     * quite know which destination to deliver on, as we don't have the
     * SSN.
     *
     * How to fix this?  Well, here's the solution: GTT that translates
     * into NO SSN PRESENT *MUST* *NOT* terminate to our point code.
     * We will have to force this issue.
     */
    if (!(addrInd & SCCP_CPA_HAS_SSN))
    {
        /* without an SSN we don't know who to deliver to */
        /* force it by seeing if the pc matches a known local route */
        if (SCCP_IsSSNEquipped(ni, npc, SCCP_SSN_SCCPMGMT))
        {
            SCCP_DEBUG(("DeliverGTT: npc %08x ssn %02x\n",
                        npc, SCCP_SSN_SCCPMGMT));

            /* Q752 Implementation */
            SccpGenOmImage[omBuf.activeOm].SCCPGenPegs.syntaxConstructionErrDetected++;

            /* Incr discard counter for this Msg Type */

            return SCRCHandleRoutingFailure(mtp3, mType, ies, ieCount,
                                            SCCP_RET_NETWORK_FAIL);
        }
        else
        {
            /*
             * It isn't going to us, so we need to set a new OPC (us).
             * We need to change the OPC to the local Point Code (which
             * is equal to the DPC in the RL now)
             */

            MTP3_RL_SET_OPC_VALUE(mtp3->label, thispc);

            return SCRCDeliverRemote(mtp3, mType, ies, ieCount,
                                     addrInd, npc, SCCP_SSN_NONE);
        }
    }
    else if (!(addrInd & SCCP_CPA_ROUTE_SSN))
    {
        /*
         * By definition, this CANNOT be local.  We cannot be
         * asked to perform two translations, as this would
         * allow recursion.  Exception: translation says that
         * the new addres *is* local, but translation doesn't
         * change the CdPA.
         */
        if (addrInd & SCCP_CPA_HAS_SSN)
        {
            if (SCCP_IsSSNEquipped(ni, npc, nssn))
            {
                SCCP_DEBUG(("DeliverGTT: npc %08x nssn %02x\n",
                            npc, nssn));

                /*
                 * Don't change the OPC, we are delivering a message to ourself
                 * even though we performed translation
                 */
                return SCRCDeliverLocal(mtp3, mType, ies, ieCount,
                                        addrInd, npc, nssn);
            }
            else
            {
                /*
                 * It isn't going to us, so we need to set a new OPC (us).
                 * We need to change the OPC to the local Point Code (which
                 * is equal to the DPC in the RL now)
                 */

                MTP3_RL_SET_OPC_VALUE(mtp3->label, thispc);

                return SCRCDeliverRemote(mtp3, mType, ies, ieCount,
                                         addrInd, npc, nssn);
            }
        }
        else
        {
            /* Incr discard counter for this Msg Type */

            return SCRCHandleRoutingFailure(mtp3, mType, ies, ieCount,
                                            SCCP_RET_NETWORK_FAIL);
        }
    }
    else
    {
        /*
         * Don't change the OPC, we are delivering a message to ourself
         * even though we performed translation
         */
        return SCRCDeliverLocal(mtp3, mType, ies, ieCount,
                                addrInd, npc, nssn);
    }
}

/*.implementation:extern
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
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  csireesh  03-06-2005  Issue ID::1919          Protcol Class Check Added
 *
 *  csireesh  20-05-2005  R0220-R0250             LUDT/LUDTS Implementation
 *
 ****************************************************************************/
int
SCRCHandleMTP3Msg_CCITT(ITS_EVENT* ev)
{
    ITS_UINT pc;
    ITS_OCTET ssn = SCCP_SSN_NONE, addrInd = 0, gttInfo[32], lpclass = 0;
    ITS_USHORT gttLen = 0;
    ITS_OCTET mType;
    SCCP_ADDR* cdp = NULL;
    MTP3_HEADER hdr3;
    ITS_OCTET data[SCCP_LONG_DATA_MAX];
    ITS_USHORT len;
    ITS_SCCP_IE ies[32];
    int ieCount, i;

    SCCP_DEBUG(("SCRCHandleMTP3Msg:\n"));

    if (MTP3_Decode(ev, &mType, &hdr3, data, &len) != ITS_SUCCESS)
    {
        SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

        /* Incr discard counter for this type of message */


        return (ITS_EINVALIDARGS);
    }

    SCCP_DEBUG(("SCRCHandleMTP3Msg: RoutingLabel: SIO %02x OPC %08x "
                "DPC %08x SLS %02x\n",
                hdr3.sio,
                MTP3_RL_GET_OPC_VALUE(hdr3.label),
                MTP3_RL_GET_DPC_VALUE(hdr3.label),
                MTP3_RL_GET_SLS(hdr3.label)));

    if (mType != MTP3_MSG_USER_DATA)
    {
        return SCMGHandleMTP3Msg_CCITT(&hdr3, mType, data, len);
    }

    /* get the new message type */
    mType = data[0];

    /* Incr message received counter for this message */

    /* figure out how to handle it */
    switch (mType)
    {
         case SCCP_MSG_CC:
         if (SCCP_DecodeMTP3(data, len, &mType,
                            ies, &ieCount,
                            &SCCP_CC_Desc) != ITS_SUCCESS)
         {
             SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

             /* Incr message discard counter for this type message */

             return (ITS_EINVALIDARGS);
        }
        /* Q752 Implementation */
            for (i = 0; i < ieCount; i++)
            {
                if (ies[i].param_id == SCCP_PRM_PROTOCOL_CLASS)
                {
                    lpclass = (0x0F & ies[i].param_data.protocolClass.pclass);

                    if (lpclass == SCCP_PCLASS_0 || lpclass == SCCP_PCLASS_1)
                    {
                        SCCP_ERROR(("SCRCHandleMTP3Msg:Invalid protocol class\n"));

                        SccpGenOmImage[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++;

                        return (ITS_EINVALIDARGS);
                    }

                    break;
                }
            }

        return SCOCHandleSCRCMsg_CCITT(&hdr3, mType, ies, ieCount,
                                       0, ssn, ITS_FALSE);

        case SCCP_MSG_CREF:
        if (SCCP_DecodeMTP3(data, len, &mType,
                            ies, &ieCount,
                            &SCCP_CREF_Desc) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            /* Incr message discard counter for this type message */
            return (ITS_EINVALIDARGS);
        }


        return SCOCHandleSCRCMsg_CCITT(&hdr3, mType, ies, ieCount,
                                       0, ssn, ITS_FALSE);

        case SCCP_MSG_RLSD:
        if (SCCP_DecodeMTP3(data, len, &mType,
                            ies, &ieCount,
                            &SCCP_RLSD_Desc) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            /* Incr message discard counter for this type message */
            return (ITS_EINVALIDARGS);
        }


        return SCOCHandleSCRCMsg_CCITT(&hdr3, mType, ies, ieCount,
                                       0, ssn, ITS_FALSE);

        case SCCP_MSG_RLC:
        if (SCCP_DecodeMTP3(data, len, &mType,
                            ies, &ieCount,
                            &SCCP_RLC_Desc) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            return (ITS_EINVALIDARGS);
        }


        return SCOCHandleSCRCMsg_CCITT(&hdr3, mType, ies, ieCount,
                                       0, ssn, ITS_FALSE);

        case SCCP_MSG_DT1:
        if (SCCP_DecodeMTP3(data, len, &mType,
                            ies, &ieCount,
                            &SCCP_DT1_Desc) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            /* Incr message discard counter for this type message */

            return (ITS_EINVALIDARGS);
        }


        return SCOCHandleSCRCMsg_CCITT(&hdr3, mType, ies, ieCount,
                                       0, ssn, ITS_FALSE);

        case SCCP_MSG_DT2:
        if (SCCP_DecodeMTP3(data, len, &mType,
                            ies, &ieCount,
                            &SCCP_DT2_Desc) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            /* Incr message discard counter for this type message */

            return (ITS_EINVALIDARGS);
        }


        return SCOCHandleSCRCMsg_CCITT(&hdr3, mType, ies, ieCount,
                                       0, ssn, ITS_FALSE);

        case SCCP_MSG_AK:
        if (SCCP_DecodeMTP3(data, len, &mType,
                            ies, &ieCount,
                            &SCCP_AK_Desc) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            /* Incr message discard counter for this type message */
            return (ITS_EINVALIDARGS);
        }


        return SCOCHandleSCRCMsg_CCITT(&hdr3, mType, ies, ieCount,
                                       0, ssn, ITS_FALSE);

        case SCCP_MSG_ED:
        if (SCCP_DecodeMTP3(data, len, &mType,
                            ies, &ieCount,
                            &SCCP_ED_Desc) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            /* Incr message discard counter for this type message */


            return (ITS_EINVALIDARGS);
        }


        return SCOCHandleSCRCMsg_CCITT(&hdr3, mType, ies, ieCount,
                                       0, ssn, ITS_FALSE);

        case SCCP_MSG_EA:
        if (SCCP_DecodeMTP3(data, len, &mType,
                            ies, &ieCount,
                            &SCCP_EA_Desc) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            /* Incr message discard counter for this type message */

            return (ITS_EINVALIDARGS);
        }


        return SCOCHandleSCRCMsg_CCITT(&hdr3, mType, ies, ieCount,
                                       0, ssn, ITS_FALSE);

        case SCCP_MSG_RSR:
        if (SCCP_DecodeMTP3(data, len, &mType,
                            ies, &ieCount,
                            &SCCP_RSR_Desc) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            /* Incr message discard counter for this type message */

            return (ITS_EINVALIDARGS);
        }


        return SCOCHandleSCRCMsg_CCITT(&hdr3, mType, ies, ieCount,
                                       0, ssn, ITS_FALSE);

        case SCCP_MSG_RSC:
        if (SCCP_DecodeMTP3(data, len, &mType,
                            ies, &ieCount,
                            &SCCP_RSC_Desc) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            /* Incr message discard counter for this type message */

            return (ITS_EINVALIDARGS);
        }


        return SCOCHandleSCRCMsg_CCITT(&hdr3, mType, ies, ieCount,
                                       0, ssn, ITS_FALSE);

        case SCCP_MSG_ERR:
        if (SCCP_DecodeMTP3(data, len, &mType,
                            ies, &ieCount,
                            &SCCP_ERR_Desc) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            /* Incr message discard counter for this type message */

            return (ITS_EINVALIDARGS);
        }


        return SCOCHandleSCRCMsg_CCITT(&hdr3, mType, ies, ieCount,
                                       0, ssn, ITS_FALSE);

        case SCCP_MSG_IT:
        if (SCCP_DecodeMTP3(data, len, &mType,
                            ies, &ieCount,
                            &SCCP_IT_Desc) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            /* Incr message discard counter for this type message */

            return (ITS_EINVALIDARGS);
        }
  
        /* Q752 Implementation */
            for (i = 0; i < ieCount; i++)
            {
                if (ies[i].param_id == SCCP_PRM_PROTOCOL_CLASS)
                {
                    lpclass = (0x0F & ies[i].param_data.protocolClass.pclass);

                    if (lpclass == SCCP_PCLASS_0 || lpclass == SCCP_PCLASS_1)
                    {
                        SCCP_ERROR(("SCRCHandleMTP3Msg:Invalid protocol class\n"));

                        SccpGenOmImage[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++;

                        return (ITS_EINVALIDARGS);
                    }

                    break;
                }
            }


        return SCOCHandleSCRCMsg_CCITT(&hdr3, mType, ies, ieCount,
                                       0, ssn, ITS_FALSE);

    /*
     * everything after this point falls into the rest of the function
     */
        case SCCP_MSG_CR:
        if (SCCP_DecodeMTP3(data, len, &mType,
                            ies, &ieCount,
                            &SCCP_CR_Desc) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            /* Incr message discard counter for this type message */

            return (ITS_EINVALIDARGS);
        }
        /* Q752 Implementation*/ 
            for (i = 0; i < ieCount; i++)
            {
                if (ies[i].param_id == SCCP_PRM_PROTOCOL_CLASS)
                {
                    lpclass = (0x0F & ies[i].param_data.protocolClass.pclass);

                    if (lpclass == SCCP_PCLASS_0 || lpclass == SCCP_PCLASS_1)
                    {
                        SCCP_ERROR(("SCRCHandleMTP3Msg:Invalid protocol class\n"));
      
                        SccpGenOmImage[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++;
 
                        return (ITS_EINVALIDARGS);
                    }

                    break;
                }
            } 
       
        break;

        case SCCP_MSG_UDT:
        if (SCCP_DecodeMTP3(data, len, &mType,
                            ies, &ieCount,
                            &SCCP_UDT_Desc) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            /* Incr message discard counter for this type message */

            return (ITS_EINVALIDARGS);
        }


        for (i = 0; i < ieCount; i++)
        {
            if (ies[i].param_id == SCCP_PRM_PROTOCOL_CLASS)
            {
                lpclass = (0x0F & ies[i].param_data.protocolClass.pclass);

                if (lpclass == SCCP_PCLASS_1)
                {
                     SCCP_DEBUG(("SCRCHandleMTP3Msg_CCITT: \
                                  Protocol class 1 received\n"));

                }
                else if (lpclass == SCCP_PCLASS_0)
                {
                     SCCP_DEBUG(("SCRCHandleMTP3Msg: \
                                  Protocol class 0 received\n"));
                }
                else
                {
                    SCCP_ERROR(("SCRCHandleMTP3Msg:Invalid protocol class\n"));
             

                    /* Q752 Implementation */
                    SccpGenOmImage[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++;

                    SCCP_Alarm_CCITT(670, __FILE__, __LINE__,
                                     "family=%s:pclass=%x", "CCITT", lpclass);

                    return (ITS_EINVALIDARGS);
                }

                break;
            }

        }

        break;

        case SCCP_MSG_XUDT:
        if (SCCP_DecodeMTP3(data, len, &mType,
                            ies, &ieCount,
                            &SCCP_XUDT_Desc) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            /* Incr message discard counter for this type message */

            return (ITS_EINVALIDARGS);
        }

        for (i = 0; i < ieCount; i++)
        {
            if (ies[i].param_id == SCCP_PRM_PROTOCOL_CLASS)
            {
                lpclass = (0x0F & ies[i].param_data.protocolClass.pclass);
                /* Bug Id :9
                 * Description : Check for XUDT protocol classes
                 */
                if (lpclass == SCCP_PCLASS_1)
                {
                    SCCP_DEBUG(("SCRCHandleMTP3Msg_CCITT: \
                                  Protocol class 1 received\n"));
                }
                else if (lpclass == SCCP_PCLASS_0)
                {
                    SCCP_DEBUG(("SCRCHandleMTP3Msg: \
                                  Protocol class 0 received\n"));
                }

                if (lpclass == SCCP_PCLASS_2 || lpclass == SCCP_PCLASS_3)
                {
                    SCCP_ERROR(("SCRCHandleMTP3Msg:Invalid protocol class\n"));

                    /* Q752 Implementation */
                    SccpGenOmImage[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++;
/*  TODO: Should an alarm be generated here as in case of UDT ??
 In that case what should be the value of alarm id ? */

/*                    SCCP_Alarm_CCITT(670, __FILE__, __LINE__, "pclass=%x",
                                     lpclass); */

                    return (ITS_EINVALIDARGS);
                }

                break;
            }
        }

        break;

        case SCCP_MSG_UDTS:
        if (SCCP_DecodeMTP3(data, len, &mType,
                            ies, &ieCount,
                            &SCCP_UDTS_Desc) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            /* Incr message discard counter for this type message */

            return (ITS_EINVALIDARGS);
        }

        break;

        case SCCP_MSG_XUDTS:
        if (SCCP_DecodeMTP3(data, len, &mType,
                            ies, &ieCount,
                            &SCCP_XUDTS_Desc) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            /* Incr message discard counter for this type message */

            return (ITS_EINVALIDARGS);
        }

        break;

        case SCCP_MSG_LUDT:
        if (SCCP_DecodeMTP3(data, len, &mType,
                            ies, &ieCount,
                            &SCCP_LUDT_Desc) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            /* Incr message discard counter for this type message */

            return (ITS_EINVALIDARGS);
        }

        for (i = 0; i < ieCount; i++)
        {
            if (ies[i].param_id == SCCP_PRM_PROTOCOL_CLASS)
            {
                lpclass = (0x0F & ies[i].param_data.protocolClass.pclass);

                if (lpclass == SCCP_PCLASS_1)
                {
                     SCCP_DEBUG(("SCRCHandleMTP3Msg_CCITT: \
                                  Protocol class 1 received\n"));

                }
                else if (lpclass == SCCP_PCLASS_0)
                {
                     SCCP_DEBUG(("SCRCHandleMTP3Msg: \
                                  Protocol class 0 received\n"));
                }
                else
                {
                    SCCP_ERROR(("SCRCHandleMTP3Msg:Invalid protocol class\n"));

                    /* Q752 Implementation Syntax Value Error OAM(Peg) implementation */ 
                    SccpGenOmImage[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++;

                    SCCP_Alarm_CCITT(670, __FILE__, __LINE__,
                                     "family=%s:pclass=%x",  "CCITT", lpclass);

                    return (ITS_EINVALIDARGS);
                }

                break;
            }
        }

        break;

        case SCCP_MSG_LUDTS:
        if (SCCP_DecodeMTP3(data, len, &mType,
                            ies, &ieCount,
                            &SCCP_LUDTS_Desc) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            /* Incr message discard counter for this type message */

            return (ITS_EINVALIDARGS);
        }

        break;

        default:
        SCCP_ERROR(("SCRCHandleMTP3Msg: invalid message type\n"));
 
        /* Q752 Implementation */ 
        SccpGenOmImage[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++;
 
        SCCP_Alarm_CCITT(636, __FILE__, __LINE__, "family=%s:mType=%x", "CCITT", mType);
        return (ITS_EINVALIDARGS);
    }

    /*
     * this is fallthru for CR, UDT, XUDT, UDTS, XUDTS
     */

    /*
     * find the CalledPartyAddress
     */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_CALLED_PARTY_ADDR)
        {
            cdp = &ies[i].param_data.calledPartyAddr;

            break;
        }
    }

    if (i == ieCount)
    {
        SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't find called party\n"));

        /* Incr message discard counter for this type message */

        /* Called party is absent in Address Indicator.*/
        SCCP_Alarm_CCITT(647, __FILE__, __LINE__, "family=%s:pc=%x",
                         "CCITT", MTP3_RL_GET_OPC_VALUE(hdr3.label)); 

        return (ITS_EINVALIDARGS);
    }

    /*
     * decode CalledPartyAddress
     */
    if (SCCP_DecodeAddr(cdp, &addrInd, &pc, &ssn,
                        gttInfo, &gttLen) != ITS_SUCCESS)
    {
        SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode called party\n"));

        /* Incr message discard counter for this type message */

        /* Called party is absent in SCCP message.*/
        SCCP_Alarm_CCITT(647, __FILE__, __LINE__, "family=%s:pc=%x",
                         "CCITT", MTP3_RL_GET_OPC_VALUE(hdr3.label));

        return (ITS_EINVALIDARGS);
    }

    if (!(addrInd & SCCP_CPA_HAS_PC))
    {
        pc = MTP3_RL_GET_DPC_VALUE(hdr3.label);
    }

    /* do we have GTT */
    if (addrInd & SCCP_CPA_ROUTE_SSN)
    {
        SCCP_ADDR transAddr;

        /* copy the address */
        transAddr = *cdp;

        /* possible user intervention */
        if (SCCP_UserIntervention_CCITT(&hdr3, addrInd, pc, ssn,
                                        gttInfo, gttLen, &transAddr,
                                        ies, ieCount) != ITS_SUCCESS)
        {
            /* Inform maintenance */
            SCCP_WARNING(("SCRCDeliverRemote: User intervention failed.\n"));

            return SCRCHandleRoutingFailure(&hdr3, mType, ies, ieCount,
                                            SCCP_RET_NETWORK_FAIL);
        }

        /* replace the CDP with the translated info */
        *cdp = transAddr;

        /* we might get a point code back from this */
        if (SCCP_DecodeAddr(&transAddr, &addrInd, &pc, &ssn,
                            NULL, NULL) != ITS_SUCCESS)
        {
            SCCP_ERROR(("Couldn't decode translated addr\n"));

            return (ITS_EINVALIDARGS);
        }

        if (!(addrInd & SCCP_CPA_ROUTE_SSN))
        {
            SCCP_ERROR(("User on fire (intervention failed)\n"));

            return (ITS_EINVALIDARGS);
        }

        if (addrInd & SCCP_CPA_HAS_SSN)
        {
            if (!(addrInd & SCCP_CPA_HAS_PC))
            {
                /* if CPA has no PC then use DPC from label */
                pc = MTP3_RL_GET_DPC_VALUE(hdr3.label);
            }
            /* Send MTP3 Ind. to Routing Function */
            return SCRCDeliverMTP3Ind(&hdr3, mType, ies, ieCount,
                                      addrInd, pc, ssn);
        }
        else
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg: MTP3Indication is "
                        "undeliverable (no SSN).\n"));

            /* Incr message discard counter for this type message */

            /* MTP3 Indication is undeliverable */
            SCCP_Alarm_CCITT(644, __FILE__, __LINE__, "family=%s:mType=%x",
                             "CCITT", mType);

            return SCRCHandleRoutingFailure(&hdr3, mType, ies, ieCount,
                                            SCCP_RET_NETWORK_FAIL);
        }
    }
    else
    {
        /* Send to Routing Control to Route on GT */
        return SCRCDeliverByGTT(&hdr3, mType, ies, ieCount, addrInd,
                                pc, ssn, gttInfo, gttLen);
    }
}

/*.implementation:extern
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
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference      Description
 *  --------------------------------------------------------------------------
 *  ghpriya   14-02-2006  Bug ID:954     Taking NI value from MTP3 routing 
 *                                       label instead of SCCP Calling and
 *                                       CalledParty Address.  
 *  
 *  csireesh  04-04-2005  Bug ID:0698    Taking NI value from Calling
 *                                       and CalledParty Address.
 *
 *  ssingh    04-01-2005  BugId: 817     Bug Fix propagation.
 *                                       Outgoing SCLC messages based 
 *                                       on App Route Selector Criteria.
 *
 *  ssingh    04-29-2005  BugId: 1771    Removed the bug (817) propagation
 *                                       fix as ACTIVE-ACTIVE redundancy 
 *                                       is not working with.
****************************************************************************/
int
SCRCHandleSCLCMsg_CCITT(MTP3_HEADER* mtp3, ITS_OCTET mType,
                        ITS_SCCP_IE* ies, int ieCount)
{
    ITS_UINT pc;
    ITS_OCTET ssn = SCCP_SSN_NONE, addrInd = 0, gttInfo[32];
    ITS_USHORT gttLen = 0;
    SCCP_ADDR* cdp = NULL, *clp = NULL;
    ITS_OCTET *scmgData = NULL;
    ITS_USHORT dlen = 0;
    ITS_OCTET ni = MTP3_HDR_GET_SIO_CCITT(*mtp3) & MTP3_NIC_MASK;
    int i;

    /*
     * find the CalledPartyAddress
     */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_CALLED_PARTY_ADDR)
        {
            cdp = &ies[i].param_data.calledPartyAddr;
        }
        else if (ies[i].param_id == SCCP_PRM_CALLING_PARTY_ADDR)
        {
            clp = &ies[i].param_data.calledPartyAddr;  
        }
        else if (ies[i].param_id == SCCP_PRM_DATA)
        {
            scmgData = ies[i].param_data.userData.data;
          /*  data = &ies[i].param_data.userData;  */
            dlen = ies[i].param_length;
        }
        else if (ies[i].param_id == SCCP_PRM_LONG_DATA)
        { 
            scmgData = ies[i].param_data.longData.data;
            dlen = ies[i].param_data.longData.len;
        }
    }

    if (cdp == NULL)
    {
        SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't find called party\n"));

        /* Incr the discard count for this type message */

        return (ITS_EINVALIDARGS);
    }


    /* Decode Called Party address into component parts  */
    if (SCCP_DecodeAddr(cdp, &addrInd, &pc, &ssn,
                        gttInfo, &gttLen) != ITS_SUCCESS)
    {
        SCCP_ERROR(("SCRCHandleSCLCMsg:  Couldn't decode addr\n"));

        /* Q752 Implementation */
        SccpGenOmImage[omBuf.activeOm].SCCPGenPegs.syntaxConstructionErrDetected++;

        /* Incr the discard count for this type message */

        return (ITS_EINVALIDARGS);
    }

    /*
     * WARNING: If this condition is true:
     * 1.  This message MUST be from local SCMG
     * 2.  This message MUST be outbound ONLY.
     * 3.  SSN is the only thing present in the addr.
     */
    if (BEHAVIORS_GetBehavior(&CCITT_SCCP_Behaviors,
                              SCCP_B_use_SCMG) &&
        (addrInd & SCCP_CPA_HAS_SSN) && ssn == SCCP_SSN_SCCPMGMT)
    {
        /*
         * Now it gets fun.  This message is one of two types.  It's either
         * 1. Notification of change of status of a local subsystem.
         * 2. Notification of change of status of a concerned subsystem.
         *
         * The problem is we don't necessarily *know* the destination, as it
         * may have a point code that is part of our distributed local PC.
         * If we were a "real" SCCP, this wouldn't be an issue as the SCCP
         * wouldn't be distributed.
         *
         * How to fix?  Well, by kludging SCMG, of course.  What we'll do
         * is put the destination ssn in the calling party address.
         * 1. If DPC/SSN is equipped (local), we shouldn't get here, so
         *    we discard.
         * 2. If DPC/SSN is not equipped (remote), we want to send to the
         *    route that has that DPC/SSN as a destination.  NOTE THAT THIS
         *    may be a wild-card destination! So use ROUTE_SelectRoute().
         */
        SCCP_SCMG scmg;
        ITS_UINT dpc, opc;
        ITS_OCTET gttI[SCCP_MAX_ADDR_LEN];
        ITS_USHORT gttLen;

        SCCP_DEBUG(("SCRCHandleSCLCMsg: Handle SCMG message\n"));

        if (dlen != sizeof(SCCP_SCMG) || clp == NULL)
        {
            SCCP_ERROR(("SCRCHandleSCLCMsg: Invalid SCMG message\n"));

            /* Incr the discard count for this type message */

            /* Q752 Implementation */
            SccpGenOmImage[omBuf.activeOm].SCCPGenPegs.syntaxConstructionErrDetected++;

            return (ITS_EMISSMAND);
        }

        memcpy(&scmg, scmgData, sizeof(SCCP_SCMG));

        SCCP_DEBUG(("SCRCHandleSCLCMsg: SCMG type %02x\n", scmg.type));

        /* This msg gets counted as a SCCP Management message also */

        switch (scmg.type)
        {
            case SCCP_SCMG_SS_UIS:
            case SCCP_SCMG_SS_UOS:
            case SCCP_SCMG_SS_CONG:
            /* deliver these to local SCCP MGMT */
            break;

            case SCCP_SCMG_SS_STATUS_TEST:
            ssn = SCCP_SSN_SCCPMGMT;
            dpc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
            opc = MTP3_RL_GET_OPC_VALUE(mtp3->label);

            /*
             * We *need* this information, at the destination, IF THE DEST
             * IS US.  Else we cannot determine who to send the response to!
             */
            if (pc != opc)
            {
                if (SCCP_EncodeAddr(clp, addrInd, dpc, SCCP_SSN_SCCPMGMT,
                                    NULL, 0) != ITS_SUCCESS)
                {
                    SCCP_ERROR(("SCRCHandleSCLCMsg:  Bad addr info\n"));

                    /* Incr Discart counter */
                    /* Q752 Implementation */
                    SccpGenOmImage[omBuf.activeOm].SCCPGenPegs.syntaxConstructionErrDetected++;

                   return (ITS_EINVALIDARGS);
                }
            }

            SCCP_DEBUG(("SCRCHandleSCLCMsg: Sending SCMG message\n"));

            /* pc is 0 so use the dpc to send the SST */

            return SCCP_SendToMTP3(mtp3, mType, ies, ieCount, dpc, ssn);

            default:
            pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
            opc = MTP3_RL_GET_OPC_VALUE(mtp3->label);

            if (SCCP_DecodeAddr(clp, &addrInd, &dpc, &ssn,
                                gttI, &gttLen) != ITS_SUCCESS)
            {
                SCCP_ERROR(("SCRCHandleSCLCMsg:  Couldn't decode addr\n"));

                /* Incr discard counter for this message */
                /* Q752 Implementation */
                SccpGenOmImage[omBuf.activeOm].SCCPGenPegs.syntaxConstructionErrDetected++;

                return (ITS_EINVALIDARGS);
            }

            if (!(addrInd & SCCP_CPA_HAS_SSN))
            {
                SCCP_ERROR(("SCRCHandleSCLCMsg:  Invalid addr\n"));

                /* Incr discard counter for this message */

                return (ITS_EINVALIDARGS);
            }

            SCCP_DEBUG(("SCRCHandleSCLC: Send to %08x:%02x\n", pc, ssn));

            /*
             * We *need* this information, at the destination, IF THE DEST
             * IS US.  Else we cannot determine who to send the response to!
             */
            if (pc != opc)
            {
                if (SCCP_EncodeAddr(clp, addrInd, dpc, SCCP_SSN_SCCPMGMT,
                                    gttI, gttLen) != ITS_SUCCESS)
                {
                    SCCP_ERROR(("SCRCHandleSCLCMsg:  Bad addr info\n"));

                    /* Q752 Implementation */
                    SccpGenOmImage[omBuf.activeOm].SCCPGenPegs.syntaxConstructionErrDetected++;


                    /* Incr discard counter for this message */

                    return (ITS_EINVALIDARGS);
                }
            }

            SCCP_DEBUG(("SCRCHandleSCLCMsg: Sending SCMG message\n"));

            return SCCP_SendToMTP3(mtp3, mType, ies, ieCount, pc, ssn);
        }

    }

    /* is GTT? */
    if (addrInd & SCCP_CPA_ROUTE_SSN)
    {
        /* No. */
        if (addrInd & SCCP_CPA_HAS_SSN)
        {
            if (!(addrInd & SCCP_CPA_HAS_PC))
            {
                pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
            }

            if (SCCP_IsSSNEquipped(ni, pc, ssn))
            {
                SCCP_DEBUG(("SCRCHandleSCLCMsg: SCLC Local pc %08x ssn %02x\n",
                            pc, ssn));

                return SCRCDeliverLocal(mtp3, mType, ies, ieCount,
                                        addrInd, pc, ssn);
            }
            else
            {
                SCCP_DEBUG(("SCRCHandleSCLCMsg: SCLC Remote pc %08x ssn %02x\n",
                            pc, ssn));

                return SCRCDeliverRemote(mtp3, mType, ies, ieCount,
                                         addrInd, pc, ssn);
            }
        }
        else
        {
            SCCP_ERROR(("SCRCHandleSCLCMsg: Package is "
                        "undeliverable (no SSN).\n"));

            /* Incr the discard count for this type message */

            /* Address Indicator is without SSN but Route by SSN is true.*/
            SCCP_Alarm_CCITT(644, __FILE__, __LINE__, "family=%s:mType=%x",
                             "CCITT", mType);

            return (ITS_EMISSMAND);
        }
    }
    else
    {
        /* We (IntelliSS7) cannot deliver without SSN. */
        if (addrInd & SCCP_CPA_HAS_SSN)
        {
            if (!(addrInd & SCCP_CPA_HAS_PC))
            {
                pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
            }

            if (SCCP_IsSSNEquipped(ni, pc, ssn))
            {
                SCCP_DEBUG(("SCRCHandleSCLCMsg: SCLC Local pc %08x ssn %02x\n",
                            pc, ssn));

                return SCRCDeliverLocal(mtp3, mType, ies, ieCount,
                                        addrInd, pc, ssn);
            }
            else
            {
                SCCP_DEBUG(("SCRCHandleSCLCMsg: SCLC Remote pc %08x ssn %02x\n",
                            pc, ssn));

                return SCRCDeliverRemote(mtp3, mType, ies, ieCount,
                                         addrInd, pc, ssn);
            }
        }
        else
        {
            if (!(addrInd & SCCP_CPA_HAS_PC))
            {
                pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
            }

            if (!SCCP_IsSSNEquipped(ni, pc, ITS_SS7_DEFAULT_SSN))
            {
                SCCP_DEBUG(("SCRCHandleSCLCMsg: SCLC Local pc %08x ssn %02x\n",
                            pc, ssn));

                return SCRCDeliverRemote(mtp3, mType, ies, ieCount,
                                         addrInd, pc, ITS_SS7_DEFAULT_SSN);
            }

            return SCRCDeliverByGTT(mtp3, mType, ies, ieCount, addrInd,
                                    pc, ITS_SS7_DEFAULT_SSN, gttInfo, gttLen);
        }
    }
}

/*.implementation:extern
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
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  ghpriya   14-02-2006  Bug ID:954     Taking NI value from MTP3 routing
 *                                       label instead of SCCP Calling and
 *                                       CalledParty Address.
 *
 *  csireesh  04-04-2005  Bug ID:0698    Taking NI value from Calling
 *                                       and CalledParty Address.
 *
 ****************************************************************************/
int
SCRCHandleSCOCMsg_CCITT(MTP3_HEADER* mtp3, ITS_OCTET mType,
                        ITS_SCCP_IE* ies, int ieCount,
                        SCCP_ADDR* cdp)
{
    ITS_UINT pc;
    ITS_OCTET ssn = SCCP_SSN_NONE, addrInd = 0, gttInfo[32];
    ITS_OCTET ni = MTP3_HDR_GET_SIO_CCITT(*mtp3) & MTP3_NIC_MASK;
    ITS_USHORT gttLen = 0;

    /*printf("Result in CO =%x",MTP3_HDR_GET_SIO_CCITT(*mtp3));*/

    /* we always get CDP, so don't check the return code */
    if (SCCP_DecodeAddr(cdp, &addrInd, &pc, &ssn,
                        gttInfo, &gttLen) != ITS_SUCCESS)
    {
        SCCP_ERROR(("SCRCHandleSCOCMsg:  Couldn't decode addr\n"));

        /* Incr the discard counter for this message type */

        return (ITS_EINVALIDARGS);
    }

    if (mType != SCCP_MSG_CR)
    {
        if (!(addrInd & SCCP_CPA_HAS_PC))
        {
            pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        }

        /* we never do GTT for this, as we got a CC,
         * and we recorded the calling party from that */
        if (!(addrInd & SCCP_CPA_HAS_SSN))
        {
            SCCP_ERROR(("SCRCHandleSCLCMsg: Package is "
                        "undeliverable (no SSN).\n"));

            /* Incr the discard counter for this message type */

            /* Address Indicator is without SSN.*/
            SCCP_Alarm_CCITT(644, __FILE__, __LINE__, "family=%s:mType=%x",
                             "CCITT", mType);

            return (ITS_EMISSMAND);
        }
        else
        {
            /* local delivery? */
            if (SCCP_IsSSNEquipped(ni, pc, ssn))
            {
                return SCRCDeliverLocal(mtp3, mType, ies, ieCount,
                                        addrInd, pc, ssn);
            }
            else
            {
                return SCRCDeliverRemote(mtp3, mType, ies, ieCount,
                                         addrInd, pc, ssn);
            }
        }
    }
    else
    {
        /*
         * This is an outbound connection request.
         *
         * If we are an intermediate node, we formulated this
         * based on the received connection request handled
         * as an MTP3 indication via DeliverMTP3Ind.
         */
        /* is GTT? */
        if (addrInd & SCCP_CPA_ROUTE_SSN)
        {
            /* No. */
            if (addrInd & SCCP_CPA_HAS_SSN)
            {
                if (!(addrInd & SCCP_CPA_HAS_PC))
                {
                    pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
                }

                if (SCCP_IsSSNEquipped(ni, pc, ssn))
                {
                    return SCRCDeliverLocal(mtp3, mType, ies, ieCount,
                                            addrInd, pc, ssn);
                }
                else
                {
                    return SCRCDeliverRemote(mtp3, mType, ies, ieCount,
                                             addrInd, pc, ssn);
                }
            }
            else
            {
                SCCP_ERROR(("SCRCHandleSCLCMsg: Package is "
                            "undeliverable (no SSN).\n"));

                /* Incr the discard counter for this message type */

               /* Address Indicator is without SSN but Route by SSN is true */
                SCCP_Alarm_CCITT(644, __FILE__, __LINE__, "family=%s:mType=%x",
                                 "CCITT", mType);

                return (ITS_EMISSMAND);
            }
        }
        else
        {
            /* We (IntelliSS7) cannot deliver without SSN. */
            if (addrInd & SCCP_CPA_HAS_SSN)
            {
                if (!(addrInd & SCCP_CPA_HAS_PC))
                {
                    pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
                }
                if (SCCP_IsSSNEquipped(ni, pc, ssn))
                {
                    SCCP_DEBUG(("SCRCHandleSCLCMsg: SCLC Local pc %08x ssn %02x\n",
                                pc, ssn));

                    return SCRCDeliverLocal(mtp3, mType, ies, ieCount,
                                            addrInd, pc, ssn);
                }
                else
                {
                    SCCP_DEBUG(("SCRCHandleSCLCMsg: SCLC Remote pc %08x ssn %02x\n",
                                pc, ssn));

                    return SCRCDeliverRemote(mtp3, mType, ies, ieCount,
                                             addrInd, pc, ssn);
                }
            }
            else
            {
                if (!(addrInd & SCCP_CPA_HAS_PC))
                {
                    pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
                }

                if (!SCCP_IsSSNEquipped(ni, pc, ITS_SS7_DEFAULT_SSN))
                {
                    SCCP_DEBUG(("SCRCHandleSCLCMsg: SCLC Local pc %08x ssn %02x\n",
                                pc, ssn));

                    return SCRCDeliverRemote(mtp3, mType, ies, ieCount,
                                             addrInd, pc, ITS_SS7_DEFAULT_SSN);
                }

                return SCRCDeliverByGTT(mtp3, mType, ies, ieCount, addrInd,
                                        pc, ITS_SS7_DEFAULT_SSN, gttInfo, gttLen);
            }
        }
    }
}

