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
 *  ID: $Id: prc-scoc.c,v 1.5 2008/07/18 05:42:01 ssingh Exp $
 *
 * LOG: $Log: prc-scoc.c,v $
 * LOG: Revision 1.5  2008/07/18 05:42:01  ssingh
 * LOG: SDS ID:: ID :: D0240 Warning removal for Solaris Compilation
 * LOG:
 * LOG: Revision 1.4  2008/06/17 06:39:08  nvijikumar
 * LOG: Updated for ITU over PRC support (split stack)
 * LOG: ACC-CG-SDS-SS7-V1.0.02::D7030,D7070
 * LOG:
 * LOG: Revision 1.3  2008/06/04 10:51:02  ssingh
 * LOG: ALU porting, B-0100LX-LUSG-00 (june 04,2008 base)
 * LOG:
 * LOG: Revision 1.2  2007/02/01 13:26:39  yranade
 * LOG: Add prc files
 * LOG:
 * LOG: $Log: prc-scoc.c,v $
 * LOG: Revision 1.5  2008/07/18 05:42:01  ssingh
 * LOG: SDS ID:: ID :: D0240 Warning removal for Solaris Compilation
 * LOG:
 * LOG: Revision 1.4  2008/06/17 06:39:08  nvijikumar
 * LOG: Updated for ITU over PRC support (split stack)
 * LOG: ACC-CG-SDS-SS7-V1.0.02::D7030,D7070
 * LOG:
 * LOG: Revision 1.3  2008/06/04 10:51:02  ssingh
 * LOG: ALU porting, B-0100LX-LUSG-00 (june 04,2008 base)
 * LOG:
 * LOG: Revision 1.1.2.5  2007/10/04 05:31:43  mshanmugam
 * LOG: Fix for issue 105
 * LOG:
 * LOG: Revision 1.1.2.4  2007/04/11 07:04:04  mshanmugam
 * LOG: Modifications to allow PRC and ITU stacks to run in parallel
 * LOG:
 * LOG: Revision 1.1.2.3  2007/02/13 04:05:48  raghavendrabk
 * LOG: Changed alarm format to put family at beginning
 * LOG:
 * LOG: Revision 1.1.2.2  2007/02/02 14:32:48  raghavendrabk
 * LOG: Parallel Stack changes for Alarms and Statistics
 * LOG:
 * LOG: Revision 1.1.2.1  2007/01/25 10:59:34  randresol
 * LOG: Modify PRC stack to allow it to run in parallel with ITU, TTC or ANSI stacks
 * LOG:
 * LOG: Revision 9.3.8.8  2006/11/22 11:26:20  ssingh
 * LOG: temporary fix for issue# 4839
 * LOG:
 * LOG: Revision 9.3.8.7  2006/11/13 05:24:53  rdangi
 * LOG: Added call for alarms 656 and 657
 * LOG:
 * LOG: Revision 9.3.8.6  2006/10/17 05:44:27  mshanmugam
 * LOG: Changes made for Q752 to get ssn from the context for DT1/DT2/ED messages
 * LOG: received from network.
 * LOG:
 * LOG: Revision 9.3.8.5  2006/10/13 09:47:47  mshanmugam
 * LOG: Fix for Bug with Id 4366 and removing check for configured ssn.
 * LOG:
 * LOG: Revision 9.3.8.4  2006/09/25 13:50:18  mshanmugam
 * LOG: Fix for the Bug ids 4366, 4359 and removing the Q752 compilation flag
 * LOG:
 * LOG: Revision 9.3.8.3  2006/08/18 12:37:54  mshanmugam
 * LOG: Added new SCCP Pegs for Q.752 Implementation.
 * LOG:
 * LOG: Revision 9.3.8.2  2005/11/17 10:45:08  ssingh
 * LOG: Bug fix for 3046
 * LOG:
 * LOG: Revision 9.3.8.1  2005/09/21 14:11:25  mmanikandan
 * LOG: Changes for Segment reassembly in DT1.
 * LOG:
 * LOG: Revision 9.3  2005/05/06 13:35:36  mmanikandan
 * LOG: PR6.5.1 Validation Bug Fix. (1804, 1798, 1781, 1784, 1749, 1801,
 * LOG: 1802, 1803).
 * LOG:
 * LOG: Revision 9.2  2005/04/06 11:26:22  mmanikandan
 * LOG: Bug Propagation and Validation bug Fix.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:42  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.13  2005/03/21 13:53:47  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.2.14.2.4.12.5  2005/02/21 09:13:42  csireesh
 * LOG: OAM Validation Bug Fix
 * LOG:
 * LOG: Revision 7.2.2.14.2.4.12.4  2005/02/01 07:36:19  dsatish
 * LOG: Ansi over prc changes after merging.
 * LOG:
 * LOG: Revision 7.2.2.14.2.4.12.3  2005/01/25 07:26:29  csireesh
 * LOG: Fixed Bug 1445 and removed Tab spaces
 * LOG:
 * LOG: Revision 7.2.2.14.2.4.12.2  2004/12/29 13:58:43  csireesh
 * LOG: SCCP bug propogation and OAM Changes
 * LOG:
 * LOG: Revision 7.2.2.14.2.4.12.1  2004/12/17 03:57:44  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.2.2.14.2.4.6.1  2004/10/25 20:34:12  randresol
 * LOG: Start Japan SS7 Implementation
 * LOG:
 * LOG: Revision 7.2.2.14.2.4  2004/06/23 11:54:43  csireesh
 * LOG: PEGS UPDATED.
 * LOG:
 * LOG: Revision 7.2.2.14.2.3  2004/06/22 11:47:53  csireesh
 * LOG: ALARMS and PEGS Propogation from TCS branch.
 * LOG:
 * LOG: Revision 7.2.2.14.2.2  2004/02/17 12:59:28  mmanikandan
 * LOG: RepeatRelease and Interval timers are added.
 * LOG:
 * LOG: Revision 7.2.2.14.2.1  2004/01/27 05:45:22  yranade
 * LOG: Porting SCCP-CO Message Based Redundancy Changes from Kineto Branch.
 * LOG:
 * LOG: Revision 7.2.2.14  2003/12/12 10:25:23  aganguly
 * LOG: Log changes in HandleDownERR method.
 * LOG:
 * LOG: Revision 7.2.2.13  2003/12/11 14:25:24  aganguly
 * LOG: Bug fixes for SCCP.
 * LOG:
 * LOG: Revision 7.2.2.12  2003/10/17 19:36:27  hcho
 * LOG: Handled SCOC routing failure to the user.
 * LOG:
 * LOG: Revision 7.2.2.11  2003/09/13 10:35:43  aganguly
 * LOG: While sending notifcation to application if any error occurs then memory allocated for temporary event is released.
 * LOG:
 * LOG: Revision 7.2.2.10  2003/09/11 09:08:53  aganguly
 * LOG: Allocated memory for temporary event is freed .
 * LOG:
 * LOG: Revision 7.2.2.9  2003/09/08 08:38:39  aganguly
 * LOG: Routing failure handler got modified also some more changes are done for SCOC bug fixes.
 * LOG:
 * LOG: Revision 7.2.2.8  2003/07/03 09:14:08  aganguly
 * LOG: Bug fix propagation from current and DSM commit changes are added.
 * LOG:
 * LOG: Revision 7.2.2.7  2003/05/22 08:55:36  aganguly
 * LOG: Handling of credit negotiation in CR and CC.
 * LOG:
 * LOG: Revision 7.2.2.6  2003/05/21 05:17:04  aganguly
 * LOG: Check for orginating PC received equal to the PC stored locally is added.
 * LOG:
 * LOG: Revision 7.2.2.5  2003/05/14 12:16:56  aganguly
 * LOG: Changes done for sending notification to application for ERR and RLSD messages.
 * LOG:
 * LOG: Revision 7.2.2.4  2003/05/05 07:28:42  aganguly
 * LOG: Modification done for sequence check in DT2 message.
 * LOG:
 * LOG: Revision 7.2.2.3  2003/05/05 06:31:18  aganguly
 * LOG: Handling of ERR message and sequence id check is done for DT2 messages.
 * LOG:
 * LOG: Revision 7.2.2.2  2003/04/30 06:29:34  aganguly
 * LOG: Bug fix for SCOC.
 * LOG:
 * LOG: Revision 7.2.2.1  2003/04/04 12:23:29  aganguly
 * LOG: SCCP CO changes for ITU.
 * LOG:
 * LOG: Revision 7.2  2003/01/16 16:23:34  mmiers
 * LOG: Tandem port, large context changes.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:28  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.18  2002/08/16 22:07:09  mmiers
 * LOG: Include China variant.
 * LOG:
 * LOG: Revision 6.17  2002/07/29 18:05:58  ngoel
 * LOG: correct peg type
 * LOG:
 * LOG: Revision 6.16  2002/06/04 15:24:08  ngoel
 * LOG: use correct slr value in RLSD, RLC messages during chaining
 * LOG:
 * LOG: Revision 6.15  2002/05/30 15:14:04  ngoel
 * LOG: correct assocRef for chaining
 * LOG:
 * LOG: Revision 6.14  2002/05/20 21:15:41  mmiers
 * LOG: Typo
 * LOG:
 * LOG: Revision 6.13  2002/05/20 21:11:50  mmiers
 * LOG: Flip PCs.  Add OAM implementation.  Try chaining fix.
 * LOG:
 * LOG: Revision 6.12  2002/05/17 20:45:56  mmiers
 * LOG: Typo
 * LOG:
 * LOG: Revision 6.11  2002/05/17 18:28:32  mmiers
 * LOG: Wrong commit.
 * LOG:
 * LOG: Revision 6.10  2002/05/17 17:51:04  mmiers
 * LOG: Cut/paste bug.
 * LOG:
 * LOG: Revision 6.9  2002/04/17 23:02:25  hdivoux
 * LOG: FT/HA integration.
 * LOG:
 * LOG: Revision 6.8  2002/03/27 17:48:12  mmiers
 * LOG: Convert to using shared timers.
 * LOG:
 * LOG: Revision 6.7  2002/03/22 14:23:51  ngoel
 * LOG: add error handling for segmentation reassembly
 * LOG:
 * LOG: Revision 6.6  2002/03/20 23:48:08  mmiers
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 6.5  2002/03/20 23:30:18  mmiers
 * LOG: Many warnings removed.
 * LOG:
 * LOG: Revision 6.4  2002/03/14 21:39:11  mmiers
 * LOG: Convert SCCP for OAM
 * LOG:
 * LOG: Revision 6.3  2002/03/08 21:31:27  mmiers
 * LOG: Formatting complete.  TODO: CPC lists.
 * LOG:
 * LOG: Revision 6.2  2002/03/07 22:21:30  mmiers
 * LOG: Merge ITU SCCP.  Doesn't build (have to work on CPC impl).
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:39  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.5  2002/01/02 21:02:44  mmiers
 * LOG: Back out the routing label change.  It breaks hybrid stack builds.
 * LOG:
 * LOG: Revision 5.4  2002/01/02 19:56:08  mmiers
 * LOG: Convert to using long names (everything but TCAP).
 * LOG:
 * LOG: Revision 5.3  2001/12/15 01:19:50  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:28  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:06  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.3  2000/11/14 00:18:19  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.3  2000/10/20 22:23:14  omayor
 * LOG: Add SOR, SOG SCMG procedure for duplicate SSN. Also LUDT, LUDTS
 * LOG: procedures for ITU SCCP
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:07:26  mmiers
 * LOG: Zero copy is in.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:37  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/01/26 03:05:48  mmiers
 * LOG:
 * LOG:
 * LOG: Commit some more changes to get us on an OO footing.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:31:37  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.3  1999/08/26 23:45:01  labuser
 * LOG:
 * LOG:
 * LOG: Alter GTT to include original PC (if any) and SSN (if any).
 * LOG:
 * LOG: Revision 1.2  1999/03/17 21:37:50  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol framework complete.  Now for implementation.
 * LOG:
 * LOG: Revision 1.1  1999/03/17 18:39:49  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol commit.  Still have to finish TCAP.
 * LOG:
 * LOG: Revision 1.33  1998/11/19 01:31:54  mmiers
 * LOG: Build with warning at max.  5 bugs found.
 * LOG:
 * LOG: Revision 1.32  1998/11/13 17:05:43  mmiers
 * LOG: Fix bad timer message.
 * LOG:
 * LOG: Revision 1.31  1998/11/13 02:49:54  mmiers
 * LOG: Do SST.
 * LOG:
 * LOG: Revision 1.30  1998/11/12 02:48:32  mmiers
 * LOG: Clean up some connection oriented bugs.
 * LOG:
 * LOG: Revision 1.29  1998/11/11 00:45:32  mmiers
 * LOG: Work on CPC/CSSN information.
 * LOG:
 * LOG: Revision 1.28  1998/11/10 16:10:13  mmiers
 * LOG: More work on SCMG.
 * LOG:
 * LOG: Revision 1.27  1998/11/10 02:23:02  mmiers
 * LOG: Fix IT timers, rework stack-sent messages, add guard timer, add
 * LOG: behavior control.
 * LOG:
 * LOG: Revision 1.26  1998/11/10 00:40:58  mmiers
 * LOG: Enable IT release.
 * LOG:
 * LOG: Revision 1.25  1998/11/09 23:30:24  mmiers
 * LOG: Put in intermediate node code.
 * LOG:
 * LOG: Revision 1.24  1998/11/04 02:45:19  mmiers
 * LOG: Enable connection timers, elucidate on pause/resume AFA how to do it.
 * LOG:
 * LOG: Revision 1.23  1998/10/30 21:31:34  whu
 * LOG: Disable connection timers, add mutex around reference allocation.
 * LOG:
 * LOG: Revision 1.22  1998/10/30 00:34:49  whu
 * LOG: Adjust timer handling in scoc.c
 * LOG:
 * LOG: Revision 1.21  1998/10/29 15:32:48  whu
 * LOG: Add DEBUG for timeouts.
 * LOG:
 * LOG: Revision 1.20  1998/10/28 00:40:23  mmiers
 * LOG: SendRLC, not SendCREF, if release times out.
 * LOG:
 * LOG: Revision 1.19  1998/10/20 16:22:28  mmiers
 * LOG: Fix compilation warnings.
 * LOG:
 * LOG: Revision 1.18  1998/10/20 01:40:24  mmiers
 * LOG: include all SCCP timers.  More work on inactivity test.  Thinking
 * LOG: about SCMG.
 * LOG:
 * LOG: Revision 1.17  1998/10/19 23:53:25  mmiers
 * LOG: Start adding in error cases.
 * LOG:
 * LOG: Revision 1.16  1998/10/19 23:45:44  mmiers
 * LOG: More bullet-proofing of SCCP.
 * LOG:
 * LOG: Revision 1.15  1998/10/19 00:40:38  mmiers
 * LOG: Strengthen for PCLASS_3
 * LOG:
 * LOG: Revision 1.14  1998/10/16 20:45:23  mmiers
 * LOG: The "NEW! And IMPROVED!" SCCP.  Let the bug reports begin.
 * LOG:
 * LOG: Revision 1.13  1998/10/16 01:44:47  mmiers
 * LOG: Put my current thoughts into bytes.  This stuff is f*cking confusing,
 * LOG: and needs review.
 * LOG:
 * LOG: Revision 1.12  1998/10/15 14:35:51  mmiers
 * LOG: WIN32 compilation changes.
 * LOG:
 * LOG: Revision 1.11  1998/10/15 03:39:30  mmiers
 * LOG: Get the names right (source), make sure GTT is present (Makefile).
 * LOG:
 * LOG: Revision 1.10  1998/10/15 01:45:04  mmiers
 * LOG: Add -D_REENTRANT for alpha.  Add connRef to SCCP_CONN_CTXT.
 * LOG:
 * LOG: Revision 1.9  1998/10/15 01:19:18  mmiers
 * LOG: Remove assert().  We shouldn't terminate, we should gracefully work
 * LOG: around errors.
 * LOG:
 * LOG: More work on SCCP COC.  Added connection timer, release timer,
 * LOG: reset timer.  Check for proper handling of missing information.
 * LOG:
 * LOG: Revision 1.8  1998/09/28 17:37:53  mmiers
 * LOG: More work on SCCP.  Starting to take better shape.
 * LOG:
 * LOG: Revision 1.7  1998/09/28 00:41:25  mmiers
 * LOG: More work on connection-oriented.
 * LOG:
 * LOG: Revision 1.6  1998/09/28 00:11:24  mmiers
 * LOG: Work on connection oriented.
 * LOG:
 * LOG: Revision 1.5  1998/09/27 00:17:56  mmiers
 * LOG: More work on SCCP
 * LOG:
 * LOG: Revision 1.4  1998/09/24 23:27:31  mmiers
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
#include <stdlib.h>

#undef ANSI
#undef CCITT

#if defined(SPLIT_STACK) && defined(USE_PRC_SCCP)
#define PRC
#endif

#if !defined(PRC) && !defined(TTC)
#define CCITT
#endif

#include <its.h>
#include <its_dsm.h>
#include <its_mutex.h>
#include <its_thread.h>
#include <its_route.h>
#include <its_tq_trans.h>
#include <its_timers.h>
#include <its_pegs.h>
#ident "$Id: prc-scoc.c,v 1.5 2008/07/18 05:42:01 ssingh Exp $"

#if defined(PRC)  || defined (USE_PRC_SCCP)
#undef CCITT
#if !defined(PRC)
#define PRC
#endif
#include <china/sccp.h>
#elif defined(TTC)  || defined (USE_TTC_SCCP)
#undef CCITT
#define TTC
#include <japan/sccp.h>
#else
#include <itu/sccp.h>
#endif

#include "sccp_intern.h"

#define DSM_LockTable        DSM_LockTableLocal
#define DSM_UnlockTable      DSM_UnlockTableLocal
#define DSM_AllocNoLock      DSM_AllocNoLockLocal
#define DSM_FindNoLock       DSM_FindNoLockLocal
#define DSM_FreeNoLock       DSM_FreeNoLockLocal
#define DSM_CommitNoLock     DSM_CommitNoLockLocal
#define DSM_Alloc            DSM_AllocLocal
#define DSM_Find             DSM_FindLocal
#define DSM_Free             DSM_FreeLocal
#define DSM_Commit           DSM_CommitLocal


/* Q752 Implementation */
extern sccpOmBuffer omBuf;

/* extern for redundancy clearance */
extern ITS_BOOLEAN isSCCPBackup;

/*
 * extern
 */
extern int INTELLINET_GetSCCPNextRef_PRC(ITS_SS7_HANDLE handle,
                                                ITS_CTXT *cref);
/*
 * disable this if connection timers are causing problems
 */
#define CONNECTION_TIMERS

static int
SCCP_SendToAPP(MTP3_HEADER * mtp3,ITS_HDR* hdr, ITS_OCTET type,
               ITS_EVENT* ev)
{
    ITS_USHORT dest;
    int ret;
    SCCP_MSG_DESC* desc;
    ITS_SCCP_IE ies[32]; 
    int ieCount;
    ITS_EVENT* tempev = NULL;

    SCCP_DEBUG(("SendToAPP: hdr->context: %02x\n",
                hdr->context.conref));

    switch (type)
    {
        case SCCP_MSG_UDT:
        case SCCP_MSG_XUDT:
        case SCCP_MSG_UDTS:
        case SCCP_MSG_XUDTS:
        case SCCP_MSG_LUDT:
        case SCCP_MSG_LUDTS:
            SCCP_ERROR(("SendToAPP: send connectionless from CO procedure\n"));
            return (ITS_EINVALIDARGS);

        case SCCP_MSG_CR:
            desc = &SCCP_CR_Desc;
            break;

        case SCCP_MSG_CC:
             desc = &SCCP_CC_Desc;  
             break;

        case SCCP_MSG_CREF:
             desc = &SCCP_CREF_Desc;  
             break;

        default:
            SCCP_DEBUG(("SendToAPP: send connection-oriented message\n"));

            return ROUTE_SendToApplication(hdr, ev);
    }
    SCCP_DEBUG(("SendToAPP: send connection initiator\n"));

    tempev = malloc(sizeof(ITS_EVENT));

    memcpy(tempev, ev, sizeof(ITS_EVENT));

    dest = ROUTE_SelectApplication(hdr, ev, ITS_TRUE);

    if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
    {
        SCCP_WARNING(("SendToAPP: no route to dest.\n"));

        if (tempev != NULL)
        {
            free(tempev);

            tempev = NULL;
        }

        ret = ITS_ENOTRANSPORT;
        return ITS_SUCCESS;
    } 
    else
    {
        ret = TRANSPORT_PutEvent(dest, ev);

        SCCP_DEBUG(("SendToAPP: PutEvent returned %d\n", ret));
    }

    if (ret != ITS_SUCCESS)
    {
        if ((ret = SCCP_Decode(ies, &ieCount, tempev, desc)) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SendToAPP:  Couldn't decode SCCP Message" ));
            
            if (tempev != NULL)
            {
                free(tempev);

                tempev = NULL;
            }

            return (ret);
        }
        if (tempev != NULL)
        {
            free(tempev);

            tempev = NULL;
        }

        return SCOCHandleRoutingFailure_PRC(mtp3,type,ies, ieCount,
                                                  SCCP_REF_DEST_UKNOWN);
    }
    else
    {
        if (tempev != NULL)
        {
            free(tempev);

            tempev = NULL;
        }
        return ret;
    }

}

static void
SendCREF(SCCP_CONN_CTXT* ctxt, ITS_OCTET cause,
         ITS_BOOLEAN toApp)
{
    ITS_SCCP_IE ies[32];
    int ieCount = 0;

    ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
    ies[ieCount].param_length = sizeof(MTP3_HEADER);
    if (toApp)
    {
        MTP3_POINT_CODE tmp, tmp2;

        ies[ieCount].param_data.routingLabel = ctxt->outLabel;
        MTP3_RL_GET_OPC(ctxt->outLabel.label, tmp);
        MTP3_RL_GET_DPC(ctxt->outLabel.label, tmp2);
        MTP3_RL_SET_OPC(ctxt->outLabel.label, tmp2);
        MTP3_RL_SET_DPC(ctxt->outLabel.label, tmp);
    }
    else
    {
        ies[ieCount].param_data.routingLabel = ctxt->inLabel;
    }
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_DEST_LOCAL_REF;
    ies[ieCount].param_length = sizeof(SCCP_REF_NUM);
    if (toApp)
    {
        RN_SET_REF_NUM(ies[ieCount].param_data.destinationLocalReference,
                       ctxt->slref);
    }
    else
    {
        RN_SET_REF_NUM(ies[ieCount].param_data.destinationLocalReference,
                       ctxt->dlref);
    }
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_REFUSAL_CAUSE;
    ies[ieCount].param_length = sizeof(SCCP_REF_CAUSE);
    ies[ieCount].param_data.refusalCause.cause = cause;
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
    ies[ieCount].param_length = sizeof(SCCP_ADDR);
    if (toApp)
    {
        ies[ieCount].param_data.calledPartyAddr =
            ctxt->oaddr;
    }
    else
    {
        ies[ieCount].param_data.calledPartyAddr =
            ctxt->daddr;
    }
    ieCount++;

    if (toApp)
    {
        SCOCHandleSCRCMsg_PRC(&ies[0].param_data.routingLabel,
                                SCCP_MSG_CREF, ies, ieCount,
                                0, SCCP_SSN_NONE, ITS_FALSE);
    }
    else
    {
        ITS_EVENT ev;
        ITS_HDR hdr;

        hdr.type = ITS_SCCP;
        hdr.context.conref = ctxt->connRef;

        ev.src = ITS_SCCP_SRC;
        if (SCCP_Encode(ies, ieCount, SCCP_MSG_CREF, &ev, &hdr,
                        &SCCP_CREF_Desc) == ITS_SUCCESS)
        {
            SCOCHandleAPPMsg_PRC(&ev);
        }

        ITS_EVENT_TERM(&ev);
    }
}

static void
SendRLSD(SCCP_CONN_CTXT* ctxt, ITS_OCTET cause,
         ITS_BOOLEAN toApp)
{
    ITS_SCCP_IE ies[32];
    int ieCount = 0;

    ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
    ies[ieCount].param_length = sizeof(MTP3_HEADER);

    if (toApp)
    {
        MTP3_POINT_CODE tmp, tmp2;

        ies[ieCount].param_data.routingLabel = ctxt->inLabel;
        MTP3_RL_GET_OPC(ctxt->outLabel.label, tmp);
        MTP3_RL_GET_DPC(ctxt->outLabel.label, tmp2);
        MTP3_RL_SET_OPC(ctxt->outLabel.label, tmp2);
        MTP3_RL_SET_DPC(ctxt->outLabel.label, tmp);
    }
    else
    {
        ies[ieCount].param_data.routingLabel = ctxt->inLabel;
    }
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_DEST_LOCAL_REF;
    ies[ieCount].param_length = sizeof(SCCP_REF_NUM);

    if (toApp)
    {
        RN_SET_REF_NUM(ies[ieCount].param_data.destinationLocalReference,
                       ctxt->slref);
    }
    else
    {
        RN_SET_REF_NUM(ies[ieCount].param_data.destinationLocalReference,
                       ctxt->dlref);
    }
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_SRC_LOCAL_REF;
    ies[ieCount].param_length = sizeof(SCCP_REF_NUM);

    if (toApp)
    {
        RN_SET_REF_NUM(ies[ieCount].param_data.sourceLocalReference,
                       ctxt->dlref);
    }
    else
    {
        RN_SET_REF_NUM(ies[ieCount].param_data.sourceLocalReference,
                       ctxt->slref);
    }
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_RELEASE_CAUSE;
    ies[ieCount].param_length = sizeof(SCCP_REL_CAUSE);
    ies[ieCount].param_data.releaseCause.cause = cause;
    ieCount++;

    if (toApp)
    {
        ies[ieCount].param_data.calledPartyAddr =
            ctxt->oaddr;
    }
    else
    {
        ies[ieCount].param_data.calledPartyAddr =
            ctxt->daddr;
    }

    if (toApp)
    {
        SCOCHandleSCRCMsg_PRC(&ies[0].param_data.routingLabel,
                                SCCP_MSG_RLSD, ies, ieCount,
                                0, SCCP_SSN_NONE, ITS_FALSE);
    }
    else
    {
        ITS_EVENT ev;
        ITS_HDR hdr;

        hdr.type = ITS_SCCP;
        hdr.context.conref = ctxt->connRef;

        ev.src = ITS_SCCP_SRC;
        if (SCCP_Encode(ies, ieCount, SCCP_MSG_RLSD, &ev, &hdr,
                        &SCCP_RLSD_Desc) == ITS_SUCCESS)
        {
            SCOCHandleAPPMsg_PRC(&ev);
        }

        ITS_EVENT_TERM(&ev);
    }
}

static void
SendRLC(SCCP_CONN_CTXT* ctxt, ITS_OCTET cause,
        ITS_BOOLEAN toApp)
{
    ITS_SCCP_IE ies[32];
    int ieCount = 0;

    ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
    ies[ieCount].param_length = sizeof(MTP3_HEADER);
    if (toApp)
    {
        MTP3_POINT_CODE tmp, tmp2;

        ies[ieCount].param_data.routingLabel = ctxt->inLabel;
        MTP3_RL_GET_OPC(ctxt->outLabel.label, tmp);
        MTP3_RL_GET_DPC(ctxt->outLabel.label, tmp2);
        MTP3_RL_SET_OPC(ctxt->outLabel.label, tmp2);
        MTP3_RL_SET_DPC(ctxt->outLabel.label, tmp);
    }
    else
    {
        ies[ieCount].param_data.routingLabel = ctxt->inLabel;
    }
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_DEST_LOCAL_REF;
    ies[ieCount].param_length = sizeof(SCCP_REF_NUM);
    if (toApp)
    {
        RN_SET_REF_NUM(ies[ieCount].param_data.destinationLocalReference,
                       ctxt->slref);
    }
    else
    {
        RN_SET_REF_NUM(ies[ieCount].param_data.destinationLocalReference,
                       ctxt->dlref);
    }
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_SRC_LOCAL_REF;
    ies[ieCount].param_length = sizeof(SCCP_REF_NUM);
    if (toApp)
    {
        RN_SET_REF_NUM(ies[ieCount].param_data.sourceLocalReference,
                       ctxt->dlref);
    }
    else
    {
        RN_SET_REF_NUM(ies[ieCount].param_data.sourceLocalReference,
                       ctxt->slref);
    }
    ieCount++;

    if (toApp)
    {
        ies[ieCount].param_data.calledPartyAddr = ctxt->oaddr;
    }
    else
    {
        ies[ieCount].param_data.calledPartyAddr = ctxt->daddr;
    }

    if (toApp)
    {
        SCOCHandleSCRCMsg_PRC(&ies[0].param_data.routingLabel,
                          SCCP_MSG_RLC, ies, ieCount,
                          0, SCCP_SSN_NONE, ITS_FALSE);
    }
    else
    {
        ITS_EVENT ev;
        ITS_HDR hdr;

        hdr.type = ITS_SCCP;
        hdr.context.conref = ctxt->connRef;

        ev.src = ITS_SCCP_SRC;
        if (SCCP_Encode(ies, ieCount, SCCP_MSG_RLC, &ev, &hdr,
                        &SCCP_RLC_Desc) == ITS_SUCCESS)
        {
            SCOCHandleAPPMsg_PRC(&ev);
        }

        ITS_EVENT_TERM(&ev);
    }
}

static void
SendERR(SCCP_CONN_CTXT* ctxt, ITS_OCTET cause,
        ITS_BOOLEAN toApp)
{
    ITS_SCCP_IE ies[32];
    int ieCount = 0;

    ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
    ies[ieCount].param_length = sizeof(MTP3_HEADER);
    if (toApp)
    {
        MTP3_POINT_CODE tmp, tmp2;

        ies[ieCount].param_data.routingLabel = ctxt->inLabel;
        MTP3_RL_GET_OPC(ctxt->outLabel.label, tmp);
        MTP3_RL_GET_DPC(ctxt->outLabel.label, tmp2);
        MTP3_RL_SET_OPC(ctxt->outLabel.label, tmp2);
        MTP3_RL_SET_DPC(ctxt->outLabel.label, tmp);
    }
    else
    {
        ies[ieCount].param_data.routingLabel = ctxt->inLabel;
    }
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_DEST_LOCAL_REF;
    ies[ieCount].param_length = sizeof(SCCP_REF_NUM);
    if (toApp)
    {
        RN_SET_REF_NUM(ies[ieCount].param_data.destinationLocalReference,
                       ctxt->slref);
    }
    else
    {
        RN_SET_REF_NUM(ies[ieCount].param_data.destinationLocalReference,
                       ctxt->dlref);
    }
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_ERROR_CAUSE;
    ies[ieCount].param_length = sizeof(SCCP_ERR_CAUSE);
    ies[ieCount].param_data.errorCause.cause = cause;
    ieCount++;

    if (toApp)
    {
        ies[ieCount].param_data.calledPartyAddr =
            ctxt->oaddr;
    }
    else
    {
        ies[ieCount].param_data.calledPartyAddr =
            ctxt->daddr;
    }

    if (toApp)
    {
        SCOCHandleSCRCMsg_PRC(&ies[0].param_data.routingLabel,
                          SCCP_MSG_ERR, ies, ieCount,
                          0, SCCP_SSN_NONE, ITS_FALSE);
    }
    else
    {
        ITS_EVENT ev;
        ITS_HDR hdr;

        hdr.type = ITS_SCCP;
        hdr.context.conref = ctxt->connRef;

        ev.src = ITS_SCCP_SRC;
        if (SCCP_Encode(ies, ieCount, SCCP_MSG_ERR, &ev, &hdr,
                        &SCCP_ERR_Desc) == ITS_SUCCESS)
        {
            SCOCHandleAPPMsg_PRC(&ev);
        }

        ITS_EVENT_TERM(&ev);
    }
}

static void
SendIT(SCCP_CONN_CTXT* ctxt)
{
    ITS_SCCP_IE ies[32];
    int ieCount = 0;
    ITS_EVENT ev;
    ITS_HDR hdr;

    ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
    ies[ieCount].param_length = sizeof(MTP3_HEADER);
    ies[ieCount].param_data.routingLabel = ctxt->outLabel;
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_DEST_LOCAL_REF;
    ies[ieCount].param_length = sizeof(SCCP_REF_NUM);
    RN_SET_REF_NUM(ies[ieCount].param_data.destinationLocalReference,
                   ctxt->dlref);
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_SRC_LOCAL_REF;
    ies[ieCount].param_length = sizeof(SCCP_REF_NUM);
    RN_SET_REF_NUM(ies[ieCount].param_data.sourceLocalReference,
                   ctxt->slref);
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_PROTOCOL_CLASS;
    ies[ieCount].param_length = sizeof(SCCP_PROT_CLASS);
    ies[ieCount].param_data.protocolClass.pclass = ctxt->pclass;
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_SEQUENCE_SEGMENT;
    ies[ieCount].param_length = sizeof(SCCP_SEQ_SEG);
    memset(&ies[ieCount].param_data.sequenceSegment, 0,
           sizeof(SCCP_SEQ_SEG));
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_CREDIT;
    ies[ieCount].param_length = sizeof(SCCP_CREDIT);
    ies[ieCount].param_data.credit.win_size = ctxt->windowSize;
    ieCount++;

    ies[ieCount].param_data.calledPartyAddr = ctxt->daddr;


    hdr.type = ITS_SCCP;
    hdr.context.conref = ctxt->connRef;

    ev.src = ITS_SCCP_SRC;
    if (SCCP_Encode(ies, ieCount, SCCP_MSG_IT, &ev, &hdr,
                    &SCCP_IT_Desc) == ITS_SUCCESS)
    {
         SCOCHandleAPPMsg_PRC(&ev);
    }

    ITS_EVENT_TERM(&ev);
}
/* sends notification of RLSD message to App */
static int 
NotifyRLSDToApp(ITS_USHORT conref,MTP3_HEADER* mtp3,
           ITS_SCCP_IE* ies,int releasemsgID,ITS_OCTET cause)
{
    ITS_EVENT event;
    ITS_HDR hdrntfy;

    /* Incremented by 2 as ies contains both slr and dlr.Counter releasemsgID
       contains the value of dlr */

    releasemsgID += 2;

    ies[releasemsgID].param_id = SCCP_PRM_RELEASE_CAUSE;
    ies[releasemsgID].param_length = sizeof(SCCP_REL_CAUSE);
    ies[releasemsgID].param_data.errorCause.cause = cause;

    releasemsgID++;

    ies[releasemsgID].param_id = SCCP_PRM_ROUTING_LABEL;
    ies[releasemsgID].param_length = sizeof(MTP3_HEADER);
    ies[releasemsgID].param_data.routingLabel = *mtp3;

    releasemsgID++;

    hdrntfy.type = ITS_SCCP;
    event.src = ITS_SCCP_SRC;
    hdrntfy.context.conref =conref ;
    
    SCCP_DEBUG(("NotifyRLSDToApp: Ntfy for RLSD is send to App\n"));

    if (SCCP_Encode(ies, releasemsgID, SCCP_MSG_RLSD, &event, &hdrntfy,
                  &SCCP_RLSD_Desc)!=ITS_SUCCESS)
    {
        SCCP_ERROR(("NotifyRLSDToApp: Error in encoding RLSD message\n"));

        return (ITS_ENOMSG);
    }

    ITS_SET_CTXT(&event.data[1], hdrntfy.context.conref);

    /* send to the application */

    if (SCCP_SendToAPP(mtp3, &hdrntfy, SCCP_MSG_RLSD, &event)!=ITS_SUCCESS)
    {
        SCCP_ERROR(("NotifyRLSDToApp:Error while sending to Application."));
        return (ITS_ENOMSG);
    }
    
    return(ITS_SUCCESS);
}
/* sends notification of ERR to Application */

static int 
NotifyERRToApp(ITS_USHORT conref,MTP3_HEADER* mtp3,
           ITS_SCCP_IE* ies,int errormsgID,ITS_OCTET cause)
{
    ITS_EVENT event;
    ITS_HDR hdrntfy;

    errormsgID++;

    ies[errormsgID].param_id = SCCP_PRM_ERROR_CAUSE;
    ies[errormsgID].param_length = sizeof(SCCP_ERR_CAUSE);
    ies[errormsgID].param_data.errorCause.cause = cause;

    errormsgID++;

    ies[errormsgID].param_id = SCCP_PRM_ROUTING_LABEL;
    ies[errormsgID].param_length = sizeof(MTP3_HEADER);
    ies[errormsgID].param_data.routingLabel = *mtp3;

    errormsgID++;

    hdrntfy.type = ITS_SCCP;
    event.src = ITS_SCCP_SRC;
    hdrntfy.context.conref = conref;
    
    SCCP_DEBUG(("NotifyERRToApp: Ntfy for ERR is send to App and resources\
                 are released\n"));

    if (SCCP_Encode(ies, errormsgID, SCCP_MSG_ERR, &event, &hdrntfy,
                  &SCCP_ERR_Desc)!=ITS_SUCCESS)
    {
        SCCP_ERROR(("NotifyERRToApp: Error in encoding ERR message\n"));

        return (ITS_ENOMSG);
    }

    ITS_SET_CTXT(&event.data[1], hdrntfy.context.conref);

    /* send to the application */

    if (SCCP_SendToAPP(mtp3, &hdrntfy, SCCP_MSG_ERR, &event)!=ITS_SUCCESS)
    {
        SCCP_ERROR(("NotifyERRToApp:Error while sending to Application."));
    }

    SCCP_DEBUG(("NotifyERRToApp:Releasing the resources blocked for the\
                                connection\n"));

    SCCP_DeleteLocalReference_PRC(conref);
    return(ITS_SUCCESS);
}

/*
 * send a connection request to MTP3
 */
static int
HandleAppCR(ITS_HDR* hdr, MTP3_HEADER* mtp3,
            ITS_SCCP_IE* ies, int ieCount)
{
    SCCP_CONN_CTXT copyCtxt, *foundCtxt;
    SCCP_ADDR *cdp = NULL, *clp = NULL;
    SCCP_REF_NUM *sl = NULL;
    SCCP_PROT_CLASS *pc = NULL;
    SCCP_CREDIT *cred = NULL;
    MTP3_HEADER *rl = NULL;
    int i, error;

    SCCP_DEBUG(("HandleAppCR\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
            case SCCP_PRM_CALLING_PARTY_ADDR:
                clp = &ies[i].param_data.callingPartyAddr;
                break;

            case SCCP_PRM_CALLED_PARTY_ADDR:
                cdp = &ies[i].param_data.calledPartyAddr;
                break;

            case SCCP_PRM_SRC_LOCAL_REF:
                sl = &ies[i].param_data.sourceLocalReference;
                break;

            case SCCP_PRM_PROTOCOL_CLASS:
                pc = &ies[i].param_data.protocolClass;
                break;

            case SCCP_PRM_CREDIT:
                cred = &ies[i].param_data.credit;
                break;

            case SCCP_PRM_ROUTING_LABEL:
                rl = &ies[i].param_data.routingLabel;
                break;
        }
    }

    /* user must have allocated the local reference */
    if (cdp == NULL || sl == NULL || rl == NULL || pc == NULL)
    {
        SCCP_ERROR(("HandleAppCR: ConnectionRequest is missing CDP, "
                    "LocalRef, PClass, or MTP3 label\n"));

        if (rl == NULL)
        {
            return (ITS_EMISSMAND);
        }
    }
    if (RN_GET_REF_NUM(*sl) != hdr->context.conref)
    {
        SCCP_ERROR(("HandleAppCR: ConnectionRequest and context mismatch\n"));

        /* Outgoing Message - Local Reference does not match Context.*/

        return (ITS_EINVALIDARGS);
    }

    /* process it */

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT, 
                                           (ITS_OCTET *)&hdr->context.conref, 
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_CRITICAL(("HandleAppCR: Couldn't acquire DSM Row"
                               " mutex.\n"));

                break;
            case (ITS_EINUSE):
                SCCP_CRITICAL(("HandleAppCR: DSM Row Locked.\n"));

                break;
            case (ITS_ENOTFOUND):
                SCCP_CRITICAL(("HandleAppCR: Can't find ConnectionReference in"
                               " DSM table.\n"));

                break;
        }

        return (ITS_ENOCONN);
    }

    if (cdp == NULL)
    {
        copyCtxt = *foundCtxt;

        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppCR: DSM unable to Commit Reference in order"
                        " to Release Lock.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        SendCREF(&copyCtxt, SCCP_REF_DEST_UKNOWN, ITS_TRUE);

        SCCP_DeleteLocalReference_PRC(hdr->context.conref);

        return (ITS_ENOCONN);
    }

    if (sl == NULL || pc == NULL)
    {
        copyCtxt = *foundCtxt;


        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppCR: DSM unable to Commit Reference in order"
                        " to Release Lock.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        SendCREF(&copyCtxt, SCCP_REF_UNQUAL, ITS_TRUE);

        SCCP_DeleteLocalReference_PRC(hdr->context.conref);

        return (ITS_ENOCONN);
    }

    foundCtxt->outLabel = *rl;
    foundCtxt->daddr = *cdp;

    if (clp)
    {
        foundCtxt->oaddr = *clp;
    }

    foundCtxt->sequenceOn = ITS_FALSE;
    foundCtxt->sequenceSLS = 0;

    switch ((pc->pclass & SCCP_PCLASS_MASK))
    {
        case SCCP_PCLASS_2:
            foundCtxt->windowSize = 0;
            foundCtxt->pclass = SCCP_PCLASS_2;
            foundCtxt->fsn = 0;
            foundCtxt->rsn = 0;
            break;

        case SCCP_PCLASS_3:
            if (cred)
            {
                foundCtxt->windowSize = cred->win_size;
            }
            foundCtxt->pclass = SCCP_PCLASS_3;
            foundCtxt->fsn = 0;
            foundCtxt->rsn = 0;
            break;

        default:
            SCCP_WARNING(("Invalid protocol class for connection\n"));
            /* Protocol Class of Message does not match Connection. */
            SCCP_Alarm_PRC(686, __FILE__, __LINE__, "family=%s:pclass=%x",
                           "PRC", pc->pclass);

            error = DSM_Commit(DSM_SccpFtGroupId,
                               DSM_TABLE_ITU_SCCP_CTXT,
                               (ITS_OCTET *)&hdr->context.conref, 
                               sizeof(hdr->context.conref), foundCtxt);

            if (error != ITS_SUCCESS)
            {
                SCCP_ERROR(("HandleAppCR: DSM unable to Commit Reference in"
                            " order to Release Lock.\n"));

                /* Unable to Commit Session Context to CTXT Table. */
            }

            return (ITS_ENOCONN);
    }

    foundCtxt->state = SCCP_CONN_OUT_PEND;

#if defined(CONNECTION_TIMERS)

    foundCtxt->connectTimer =
        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                     SCCP_T_conn),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
#endif
 
    *mtp3 = *rl;

    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleAppCR: DSM unable to Commit Reference in order"
                    " to Release Lock.\n"));

        /* Unable to Commit Session Context to CTXT Table. */
    }

    if (gcsMessageBasedRedundancyIsActive)
    {
        ITS_EVENT dummyEvent;
        ITS_UINT  dest;

        SCCP_DEBUG(("GCS Message Based Redundancy is ACTIVE\n"));

        dummyEvent.src  = ITS_GCS_EVENT_TO_NETWORK;
        dummyEvent.data = 0;

        dest = ROUTE_SelectApplication(hdr, &dummyEvent, ITS_TRUE);

        if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
        {
            /* Don't send message for routing to the network */
            SCCP_WARNING(("Message is consumed by SCCP: ctxt = 0x%x\n",
                          hdr->context.conref));
            return ITS_SUCCESS;
        }

    }

    SCCP_DEBUG(("Sending message to Network: ctxt = 0x%x  $$$\n",
                 hdr->context.conref));


    return SCRCHandleSCOCMsg_PRC(mtp3, SCCP_MSG_CR, ies, ieCount, cdp);
}

static int
HandleDownCR(ITS_HDR* hdr, MTP3_HEADER* mtp3,
             ITS_SCCP_IE* ies, int ieCount,
             ITS_UINT dpc, ITS_OCTET ssn, ITS_BOOLEAN needCouple)
{
    SCCP_CONN_CTXT copyCtxt, *foundCtxt = NULL, *foundCtxt2 = NULL;
    SCCP_REF_NUM *sl = NULL;
    SCCP_ADDR *cdp = NULL, *clp = NULL;
    SCCP_PROT_CLASS *pc = NULL;
    SCCP_CREDIT *cred = NULL;
    SCCP_HOP_COUNT* hc = NULL;
    MTP3_POINT_CODE tmp, tmp2;
    ITS_INT slref;
    ITS_HDR chain;
    int i, error;

    SCCP_DEBUG(("HandleDownCR\n"));

    PEG_IncrPeg(PRC_SCCP_Pegs, PEG_SCCP_REMOTE_CR_RCVD);

    /* Q752 Implementation */
    /* message CR recieved from remote */    
    SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.messageCRRcvd++;

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
            case SCCP_PRM_CALLED_PARTY_ADDR:
                cdp = &ies[i].param_data.calledPartyAddr;
                break;

            case SCCP_PRM_CALLING_PARTY_ADDR:
                clp = &ies[i].param_data.callingPartyAddr;
                break;

            case SCCP_PRM_SRC_LOCAL_REF:
                sl = &ies[i].param_data.sourceLocalReference;
                break;

            case SCCP_PRM_PROTOCOL_CLASS:
                pc = &ies[i].param_data.protocolClass;
                break;

            case SCCP_PRM_CREDIT:
                cred = &ies[i].param_data.credit;
                break;

            case SCCP_PRM_HOP_COUNTER:
                hc = &ies[i].param_data.hopCount;
                break;
        }
    }

    /* Q752 Implementation */
    if (sl == NULL)
    {
        /* Discarding Message - Missing Mandatory Parameter. */
        SCCP_ERROR(("HandleDownCR: Missing source reference number \n"));
        
        /* Syntax Error Detected Value error */
        SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++;
        return (ITS_EMISSMAND);
    }
     

    /* we allocate the reference */
    if (cdp == NULL || sl == NULL)
    {
        SCCP_ERROR(("Missing mandatories\n"));

        return (ITS_EMISSMAND);
    }

    if (INTELLINET_GetSCCPNextRef_PRC(NULL,
                                        &hdr->context.conref) != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownCR: Out of local ConnectionReference numbers"
                    "\n"));

        return (ITS_ENOMSG);
    }


    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT, 
                                           (ITS_OCTET *)&hdr->context.conref, 
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_CRITICAL(("HandleDownCR: Couldn't acquire DSM Row"
                               " mutex.\n"));

                break;
            case (ITS_EINUSE):
                SCCP_CRITICAL(("HandleDownCR: DSM Row Locked.\n"));

                break;
            case (ITS_ENOTFOUND):
                SCCP_CRITICAL(("HandleDownCR: Can't find ConnectionReference"
                               " in DSM table.\n"));

                break;
        }

        return (ITS_ENOCONN);
    }

    slref = RN_GET_REF_NUM(*sl);
    foundCtxt->slref = hdr->context.conref;
    foundCtxt->dlref = slref;
    foundCtxt->oaddr = *cdp;
    foundCtxt->inLabel = *mtp3;
    foundCtxt->outLabel = *mtp3;
    MTP3_RL_GET_OPC(foundCtxt->outLabel.label, tmp);
    MTP3_RL_GET_DPC(foundCtxt->outLabel.label, tmp2);
    MTP3_RL_SET_OPC(foundCtxt->outLabel.label, tmp2);
    MTP3_RL_SET_DPC(foundCtxt->outLabel.label, tmp);

    if (clp)
    {
        foundCtxt->daddr = *clp;
    }
    else
    {
        /* fix: daddr is mandatory for our stack to do routing
        **      based on PC&SSN.
        */
        ITS_OCTET addrInd = SCCP_CPA_HAS_SSN|SCCP_CPA_ROUTE_SSN;
        SCCP_EncodeAddr(&foundCtxt->daddr, addrInd, 0, ITS_SS7_DEFAULT_SSN, 
                        NULL, 0);
    }

    foundCtxt->sequenceOn = ITS_FALSE;
    foundCtxt->sequenceSLS = 0;

    switch ((pc->pclass & SCCP_PCLASS_MASK))
    {
        case SCCP_PCLASS_2:
            foundCtxt->windowSize = 0;
            foundCtxt->pclass = SCCP_PCLASS_2;
            foundCtxt->fsn = 0;
            foundCtxt->rsn = 0;
            break;

        case SCCP_PCLASS_3:
            foundCtxt->windowSize = 0;
            foundCtxt->pclass = SCCP_PCLASS_3;
            if (cred)
            {
                foundCtxt->windowSize = cred->win_size;
            }
            foundCtxt->fsn = 0;
            foundCtxt->rsn = 0;
            break;

        default:
            SCCP_WARNING(("HandleDownCR: Invalid protocol class for"
                          " connection\n"));
            /* Protocol Class of Message does not match Connection.*/
            SCCP_Alarm_PRC(685, __FILE__, __LINE__, "family=%s:pclass=%x",
                           "PRC", pc->pclass);

            error = DSM_Commit(DSM_SccpFtGroupId,
                               DSM_TABLE_ITU_SCCP_CTXT,
                               (ITS_OCTET *)&hdr->context.conref, 
                               sizeof(hdr->context.conref), foundCtxt);

            if (error != ITS_SUCCESS)
            {
                SCCP_ERROR(("HandleDownCR: DSM unable to Commit Reference in"
                            " order to Release Lock.\n"));

                /* Unable to Commit Session Context to CTXT Table. */
            }

            return (ITS_ENOCONN);
    }

    foundCtxt->state = SCCP_CONN_IN_PEND;

#if defined(CONNECTION_TIMERS)

    foundCtxt->connectTimer =
        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                     SCCP_T_conn),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
#endif
 
    if (hc && pc && pc->pclass == SCCP_PCLASS_3)
    {
        hc->count--;

        /***   equal-to    or    less-than  **/
        if (hc->count == 0 || hc->count == 255)
        {

            SCCP_ERROR(("HandleDownCR: Hop count exceeded\n"));
            /* ERROR - Incoming Message - Hop Count Exceeded. */
     
            PEG_IncrPeg(PRC_SCCP_Pegs, PEG_SCCP_HOP_COUNTER_VIOLATION_ERR);
  
            /*Q752 Implementation Hop counter violation */ 
            SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.hopCounterViolationErr++;
 
            /* Make a copy of ctxt to use in SendCREF after release row lock. */
            copyCtxt = *foundCtxt;

            /* Release row lock & push change to context to other nodes */
            error = DSM_Commit(DSM_SccpFtGroupId,
                               DSM_TABLE_ITU_SCCP_CTXT,
                               (ITS_OCTET *)&hdr->context.conref, 
                               sizeof(hdr->context.conref), foundCtxt);

            if (error != ITS_SUCCESS)
            {
                SCCP_ERROR(("HandleDownCR: DSM unable to Commit Reference in"
                            " order to Release Lock.\n"));

                /* Unable to Commit Session Context to CTXT Table. */
            }

            SendCREF(&copyCtxt, SCCP_REF_SCCP_ORG, ITS_FALSE);

            return (ITS_EMISSMAND);
        }
    }

    if (needCouple)
    {
        ITS_OCTET addrInd = 0;
 

        foundCtxt->isIntermediate = ITS_TRUE;

        if ((mtp3->sio & MTP3_NIC_MASK) == MTP3_NIC_INTERNATIONAL)
        {
            addrInd |= SCCP_CPA_ROUTE_INT;
        }
        else if ((mtp3->sio & MTP3_NIC_MASK) == MTP3_NIC_NATIONAL)
        {
            addrInd |= SCCP_CPA_ROUTE_NAT;
        }

        addrInd |= SCCP_CPA_ROUTE_SSN|SCCP_CPA_HAS_PC|SCCP_CPA_HAS_SSN;
        SCCP_EncodeAddr(&foundCtxt->oaddr, addrInd,
                        MTP3_RL_GET_DPC_VALUE(mtp3->label), ssn, NULL, 0);

        if (INTELLINET_GetSCCPNextRef_PRC(NULL, 
                                          &chain.context.conref) != ITS_SUCCESS)
        {
            SCCP_WARNING(("HandleDownCR: Can't allocation coupled connection"
                          " reference\n"));

            /* Make a copy of ctxt to use in SendCREF after release row lock. */
            copyCtxt = *foundCtxt;

            error = DSM_Commit(DSM_SccpFtGroupId,
                               DSM_TABLE_ITU_SCCP_CTXT,
                               (ITS_OCTET *)&hdr->context.conref, 
                               sizeof(hdr->context.conref), foundCtxt);

            if (error != ITS_SUCCESS)
            {
                SCCP_ERROR(("HandleDownCR: DSM unable to Commit Reference in"
                             " order to Release Lock.\n"));

                /* Unable to Commit Session Context to CTXT Table. */
            }

            SendCREF(&copyCtxt, ITS_FALSE, SCCP_REF_NOT_OBTAINABLE);

            return (ITS_ENOCONN);
        }

        chain.type = ITS_SCCP;
        RN_SET_REF_NUM(*sl, chain.context.conref);

        foundCtxt->assocRef = chain.context.conref;

        if (clp)
        {
            *clp = foundCtxt->oaddr;
        }

        MTP3_RL_GET_DPC(mtp3->label, tmp);
        MTP3_RL_SET_OPC(mtp3->label, tmp);
        MTP3_RL_SET_DPC_VALUE(mtp3->label, dpc);

        copyCtxt = *foundCtxt; /* Make copy for use after release Row lock */

        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownCR: DSM unable to Commit Reference in order"
                        " to Release Lock.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        foundCtxt = NULL;        /* Not safe to use with out lock     */

        foundCtxt2 = (SCCP_CONN_CTXT *)
                           DSM_Find(DSM_SccpFtGroupId,
                                    DSM_TABLE_ITU_SCCP_CTXT, 
                                    (ITS_OCTET *)&chain.context.conref, 
                                    sizeof(chain.context.conref), &error);

        if (error != ITS_SUCCESS)
        {

            switch(error)
            {
                case (ITS_EBADMUTEX):
                    SCCP_CRITICAL(("HandleDownCR: Couldn't acquire DSM Row"
                                   " mutex.\n"));

                    break;

                case (ITS_EINUSE):
                    SCCP_CRITICAL(("HandleDownCR: DSM Row Locked.\n"));

                    break;

                case (ITS_ENOTFOUND):
                    SCCP_WARNING(("HandleDownCR: Can't find ConnectionReference"      
                                                              " in DSM table.\n"));

                    break;
            }

            SCCP_DeleteLocalReference_PRC(chain.context.conref);

            SendCREF(&copyCtxt, ITS_FALSE, SCCP_REF_NOT_OBTAINABLE);

            return (ITS_ENOCONN);
        }
 
        foundCtxt2->isIntermediate = ITS_TRUE;
        foundCtxt2->assocRef = hdr->context.conref;

        ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[ieCount].param_length = sizeof(MTP3_HEADER);
        ies[ieCount].param_data.routingLabel = *mtp3;
        ieCount++;

        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&chain.context.conref, 
                           sizeof(chain.context.conref), foundCtxt2);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownCR: DSM unable to Commit Reference in order"
                        " to Release Lock.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }
    }
    else
    {
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownCR: DSM unable to Commit Reference in order"
                        " to Release Lock.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }
    }
    
    if (needCouple)
    {
        return HandleAppCR(&chain, mtp3, ies, ieCount);
    }

    return (ITS_SUCCESS);
}

/*
 * send a connection confirm
 */
static int
HandleAppCC(ITS_HDR* hdr, MTP3_HEADER* mtp3,
            ITS_SCCP_IE* ies, int ieCount)
{
    SCCP_CONN_CTXT *foundCtxt;
    SCCP_ADDR *cdp = NULL, local;
    SCCP_REF_NUM *sl = NULL, *dl = NULL;
    SCCP_PROT_CLASS *pc = NULL;
    int i, error;
    int isCREFtobesent = 0;
    ITS_EVENT event;
    ITS_HDR hdrntfy;
    int crefid = 0;
    ITS_OCTET creditvalue = 0;

    SCCP_DEBUG(("HandleAppCC\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
            case SCCP_PRM_CALLED_PARTY_ADDR:
                cdp = &ies[i].param_data.calledPartyAddr;
                break;

            case SCCP_PRM_SRC_LOCAL_REF:
                sl = &ies[i].param_data.sourceLocalReference;
                break;

            case SCCP_PRM_DEST_LOCAL_REF:
                dl = &ies[i].param_data.destinationLocalReference;
                crefid = i;
                break;

            case SCCP_PRM_PROTOCOL_CLASS:
                pc = &ies[i].param_data.protocolClass;
                break;
       
            case SCCP_PRM_CREDIT:
                creditvalue = ies[i].param_data.credit.win_size;  
                if (!(0x0F & creditvalue))
                {
                    SCCP_ERROR(("HandleAppCC: CC with credit value zero \n"));
                    isCREFtobesent = 1;

                }
                break;
        }
    }

    /* we allocated the local reference */
    if (sl == NULL || dl == NULL || pc == NULL)
    {
        SCCP_ERROR(("HandleAppCC: Missing source, destination reference number "
                    "or PClass\n"));

        return (ITS_EMISSMAND);
    }

    if (RN_GET_REF_NUM(*sl) != hdr->context.conref)
    {
        SCCP_ERROR(("HandleAppCC: ConnectionConfirm and context mismatch\n"));

        return (ITS_EINVALIDARGS);
    }

    /* process it */

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);

    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("HandleAppCC: Couldn't acquire mutex.\n"));

                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleAppCC: DSM Row Locked.\n"));

                break;
            case (ITS_ENOTFOUND):
                SCCP_WARNING(("HandleAppCC: Can't find ConnectionReference"
                              " in table.\n"));

                break;
        }

        return (ITS_ENOCONN);
    }

    if (isCREFtobesent == 1)
    {
        SCCP_DEBUG(("HandleAppCC:CREF is sent to the other end\n"));

        SendCREF(foundCtxt, SCCP_REF_BAD_USER_DATA, ITS_FALSE);

        /* Send NTFY to app for CREF */
        RN_SET_REF_NUM(ies[crefid].param_data.destinationLocalReference,
                       foundCtxt->slref);
        crefid++;
                       
        ies[crefid].param_id = SCCP_PRM_REFUSAL_CAUSE;
        ies[crefid].param_length = sizeof(SCCP_REF_CAUSE);
        ies[crefid].param_data.refusalCause.cause = SCCP_REF_BAD_USER_DATA;

        crefid++;
    
        ies[crefid].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[crefid].param_length = sizeof(MTP3_HEADER);
        ies[crefid].param_data.routingLabel = *mtp3;

        crefid++;

        ieCount = crefid;

        hdrntfy.type = ITS_SCCP;
        event.src = ITS_SCCP_SRC;
        hdrntfy.context.conref = foundCtxt->connRef;

        SCCP_DEBUG(("HandleAppCC:Ntfy for CREF is send to App\n"));

        if (SCCP_Encode(ies, ieCount, SCCP_MSG_CREF, &event, &hdrntfy,
                              &SCCP_CREF_Desc)!=ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppCC:Error in encoding ERR message\n"));
            return (ITS_ENOMSG);
        }
        ITS_SET_CTXT(&event.data[1], hdrntfy.context.conref);

        /* send to the application */
        if (SCCP_SendToAPP(mtp3, &hdrntfy, SCCP_MSG_CREF, &event)!=ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppCC:Error while sending to Application."));
        }
        foundCtxt = NULL;

        return(ITS_ESENDFAIL);
    }

    foundCtxt->state = SCCP_DATA_TRANSFER;
    foundCtxt->dataState = SCCP_DATA_NORMAL;
    *mtp3 = foundCtxt->outLabel;

    if (cdp == NULL)
    {
        local = foundCtxt->daddr;
        cdp = &local;
    }
    else
    {
        /*
         * FIXME:: This fix is with the assumption that CC received
         * in response of CR received from Network (with/without 
         * calling partry address) will always have optional param
         * called party address filled.
         */
        ITS_OCTET tmpAddrInd = 0;
        ITS_UINT  pc = 0;
        ITS_OCTET ssn = 0xFF; /* how ITS_SS7_DEFAULT_SSN */
        ITS_OCTET* gttInfo = NULL;
        ITS_USHORT gttLen = 0;

        SCCP_DecodeAddr(&foundCtxt->daddr, &tmpAddrInd, 
                        &pc, &ssn, gttInfo, &gttLen);

        /* Check if daddr is already having valid destination Add!! */
        if (pc == 0 && ssn == 0xFF)
        {
           /* Get it from received cdp and fill it.. */
           foundCtxt->daddr = *cdp;
        }
    }

    switch ((pc->pclass & SCCP_PCLASS_MASK))
    {
        case SCCP_PCLASS_2:
            if (foundCtxt->pclass == SCCP_PCLASS_3)
            {
                foundCtxt->windowSize = 0;
                foundCtxt->pclass = SCCP_PCLASS_2;
            }
            break;

        case SCCP_PCLASS_3:
            if (foundCtxt->pclass == SCCP_PCLASS_2)
            {
                SCCP_WARNING(("HandleAppCC: Invalid protocol class for"
                              " connection\n"));

                /* Outgoing Message - Protocol Class of Message does not 
                   match Connection. */

                error = DSM_Commit(DSM_SccpFtGroupId,
                                   DSM_TABLE_ITU_SCCP_CTXT,
                                   (ITS_OCTET *)&hdr->context.conref, 
                                   sizeof(hdr->context.conref), foundCtxt);

                if (error != ITS_SUCCESS)
                {
                    SCCP_ERROR(("HandleAppCC: DSM unable to free Reference."
                                "\n"));

                    /* Unable to Commit Session Context to CTXT Table. */
                }


                 return (ITS_ENOCONN);
            }

            if (foundCtxt->windowSize < creditvalue)
            {
                SCCP_DEBUG(("HandleAppCC:Invalid Credit value sent in CC from"
                           " the application, message is discarded\n"));

                return(ITS_EBADCHKSUM);
           }
           break;

        default:
            SCCP_WARNING(("HandleAppCC: Invalid protocol class for connection"
                          "\n"));

            error = DSM_Commit(DSM_SccpFtGroupId,
                               DSM_TABLE_ITU_SCCP_CTXT,
                               (ITS_OCTET *)&hdr->context.conref, 
                               sizeof(hdr->context.conref), foundCtxt);

            if (error != ITS_SUCCESS)
            {
                SCCP_ERROR(("HandleAppCC: DSM unable to free Reference.\n"));

                /* Unable to Commit Session Context to CTXT Table. */
            }

            return (ITS_ENOCONN);
    }

#if defined(CONNECTION_TIMERS)
    TIMERS_CancelTimer(foundCtxt->connectTimer);

    foundCtxt->sendInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                     SCCP_T_ias),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
     foundCtxt->receiveInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                     SCCP_T_iar),
                                foundCtxt, sizeof(SCCP_CONN_CTXT)); 
#endif
 
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleAppCC: DSM unable to free Reference.\n"));

        /* Unable to Commit Session Context to CTXT Table. */
    }

    if (gcsMessageBasedRedundancyIsActive)
    {
        ITS_EVENT dummyEvent;
        ITS_UINT  dest;

        SCCP_DEBUG(("GCS Message Based Redundancy is ACTIVE\n"));

        dummyEvent.src  = ITS_GCS_EVENT_TO_NETWORK;
        dummyEvent.data = 0;

        dest = ROUTE_SelectApplication(hdr, &dummyEvent, ITS_TRUE);

        if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
        {
            /* Don't send message for routing to the network */
            SCCP_WARNING(("Message is consumed by SCCP: ctxt = 0x%x\n",
                          hdr->context.conref));
            return ITS_SUCCESS;
        }

    }

    SCCP_DEBUG(("Sending message to Network: ctxt = 0x%x  $$$\n",
                 hdr->context.conref));

    return SCRCHandleSCOCMsg_PRC(mtp3, SCCP_MSG_CC, ies, ieCount, cdp);
}
/*
 * send released
 */
static int
HandleAppRLSD(ITS_HDR* hdr, MTP3_HEADER* mtp3,
              ITS_SCCP_IE* ies, int ieCount)
{
    SCCP_CONN_CTXT *foundCtxt;
    SCCP_REF_NUM *sl = NULL, *dl = NULL;
    SCCP_ADDR local, *cdp = &local;
    int i, error;
    ITS_OCTET cause = 0;

    SCCP_DEBUG(("HandleAppRLSD\n"));

    //PEG_IncrPeg(PRC_SCCP_Pegs,PEG_SCCP_RLSD_TO_REMOTE_SENT);

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
            case SCCP_PRM_SRC_LOCAL_REF:
                sl = &ies[i].param_data.sourceLocalReference;
                break;

            case SCCP_PRM_DEST_LOCAL_REF:
                dl = &ies[i].param_data.destinationLocalReference;
                break;

            case SCCP_PRM_RELEASE_CAUSE:
                cause =  ies[i].param_data.releaseCause.cause;
                break;
        }
    }

    if (RN_GET_REF_NUM(*sl) != hdr->context.conref)
    {
        SCCP_ERROR(("HandleAppRLSD: Released and context mismatch\n"));

        return (ITS_EINVALIDARGS);
    }

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("HandleAppRLSD: Couldn't acquire mutex.\n"));

                break;

            case (ITS_EINUSE):
                SCCP_ERROR(("HandleAppRLSD: DSM Row Locked.\n"));

                break;

            case (ITS_ENOTFOUND):
                SCCP_WARNING(("HandleAppRLSD: Can't find ConnectionReference"
                              " in table.\n"));

                break;
        }

        return (ITS_ENOCONN);
    }

   if (foundCtxt->state == SCCP_CONN_IN_PEND)
   {
       SCCP_ERROR(("HandleAppRLSD:RLSD received in Connection Pending state\
                    hence  CREF is sent to the other endpoint"));
       SendCREF(foundCtxt, SCCP_REF_BAD_USER_DATA, ITS_FALSE);

       return(ITS_EMISSMAND);
   }

   /*
   This is the case where RLSD came from before CC came from the other end.
   Here waiting for CC or CREF and state is not changed.  
   Note if the Application while sending RLSD is it asks for RLSD
   cause also then this logic need to be changed.At present by default
   this release cause is send from the application.
  */
   else if (foundCtxt->state == SCCP_CONN_OUT_PEND 
            && cause == SCCP_RLC_END_USER_ORG) 
   {
        SCCP_ERROR(("RLSD is received in Outgoing Connection pending state\
                     hence waiting for CC or CREF and state is not changed.\n"));

        /* Unknown message in this state*/
   }
   else if (foundCtxt->state == SCCP_CONN_OUT_PEND)
   {
       /* SCCP_Alarm_PRC(658, __FILE__, __LINE__, "family=%s", "PRC"); */
   }
   else
   {
       foundCtxt->state = SCCP_OUT_RELEASE_PEND; 
   }

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->connectTimer)
    {
        SCCP_DEBUG(("HandleAppRLSD:Connect timer is killed\n"));
        TIMERS_CancelTimer(foundCtxt->sendInactivity);
    }
    if (foundCtxt->releaseTimer)
    {
        SCCP_DEBUG(("HandleAppRLSD:Release timer is killed\n"));
        TIMERS_CancelTimer(foundCtxt->sendInactivity);
    }

    foundCtxt->releaseTimer =
        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                     SCCP_T_release),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
 
    if (foundCtxt->sendInactivity)
    {
         SCCP_DEBUG(("HandleAppRLSD:SendInactivity timer is killed\n")); 
        TIMERS_CancelTimer(foundCtxt->sendInactivity);
    }

    if (foundCtxt->receiveInactivity)
    {
        SCCP_DEBUG(("HandleAppRLSD:ReceiveInactivity timer is killed\n"));
        TIMERS_CancelTimer(foundCtxt->receiveInactivity);
    }

#endif

    *mtp3 = foundCtxt->outLabel;

    local = foundCtxt->daddr;

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleAppRLSD: DSM unable to free Reference.\n"));

        /* Unable to Commit Session Context to CTXT Table. */
    }

    if (foundCtxt->state==SCCP_CONN_OUT_PEND)
    {
        SCCP_DEBUG(("HandleAppRLSD:RLSD is not propogated to the other end\
                      as waiting for CC or CREF\n"));

        foundCtxt = NULL;
        return(ITS_SUCCESS);
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (gcsMessageBasedRedundancyIsActive)
    {
        ITS_EVENT dummyEvent;
        ITS_UINT  dest;

        SCCP_DEBUG(("GCS Message Based Redundancy is ACTIVE\n"));

        dummyEvent.src  = ITS_GCS_EVENT_TO_NETWORK;
        dummyEvent.data = 0;

        dest = ROUTE_SelectApplication(hdr, &dummyEvent, ITS_TRUE);

        if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
        {
            /* Don't send message for routing to the network */
            SCCP_WARNING(("Message is consumed by SCCP: ctxt = 0x%x\n",
                          hdr->context.conref));
            return ITS_SUCCESS;
        }

    }

    SCCP_DEBUG(("Sending message to Network: ctxt = 0x%x  $$$\n",
                 hdr->context.conref));

    return SCRCHandleSCOCMsg_PRC(mtp3, SCCP_MSG_RLSD, ies, ieCount, cdp);
}


/*
 * reset request
 */
static int
HandleAppRSR(ITS_HDR* hdr, MTP3_HEADER* mtp3,
             ITS_SCCP_IE* ies, int ieCount)
{
    SCCP_CONN_CTXT *foundCtxt;
    SCCP_REF_NUM *sl = NULL, *dl = NULL;
    SCCP_ADDR local, *cdp = &local;
    int i, error;
    
    SCCP_DEBUG(("HandleAppRSR\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
        case SCCP_PRM_SRC_LOCAL_REF:
            sl = &ies[i].param_data.sourceLocalReference;
            break;

        case SCCP_PRM_DEST_LOCAL_REF:
            dl = &ies[i].param_data.destinationLocalReference;
            break;
        }
    }

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("HandleAppRSR: Couldn't acquire mutex.\n"));

                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleAppRSR: DSM Row Locked.\n"));

                break;
            case (ITS_ENOTFOUND):
                SCCP_WARNING(("HandleAppRSR: Can't find ConnectionReference"
                              " in table.\n"));

                break;
        }

        return (ITS_ENOCONN);
    }

    if (foundCtxt->pclass != SCCP_PCLASS_3)
    {
        SCCP_ERROR(("HandleAppRSR: RSR is invalid for protocol class.\n"));
        /* Outgoing Message - Discarding Message - Message Type not valid 
           for Protocol Class of Connection. */

        SCCP_Alarm_PRC(671, __FILE__, __LINE__, "family=%s:pclass=%x",
                       "PRC", foundCtxt->pclass);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppRSR: DSM unable to free Reference.\n"));

        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EINVALIDARGS);
    }

    foundCtxt->state = SCCP_OUT_RESET_PEND;

    *mtp3 = foundCtxt->outLabel;

    local = foundCtxt->daddr;

#if defined(CONNECTION_TIMERS)
    foundCtxt->resetTimer =
        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                     SCCP_T_reset),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
    if (foundCtxt->sendInactivity)
    {
        TIMERS_CancelTimer(foundCtxt->sendInactivity);
    }
    foundCtxt->sendInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                     SCCP_T_ias),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
#endif
 
    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleAppRSR: DSM unable to free Reference.\n"));

        /* Unable to Commit Session Context to CTXT Table. */
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    PEG_IncrPeg(PRC_SCCP_Pegs, PEG_SCCP_RSR_TO_REMOTE_SENT);

    if (gcsMessageBasedRedundancyIsActive)
    {
        ITS_EVENT dummyEvent;
        ITS_UINT  dest;

        SCCP_DEBUG(("GCS Message Based Redundancy is ACTIVE\n"));

        dummyEvent.src  = ITS_GCS_EVENT_TO_NETWORK;
        dummyEvent.data = 0;

        dest = ROUTE_SelectApplication(hdr, &dummyEvent, ITS_TRUE);

        if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
        {
            /* Don't send message for routing to the network */
            SCCP_WARNING(("Message is consumed by SCCP: ctxt = 0x%x\n",
                          hdr->context.conref));
            return ITS_SUCCESS;
        }

    }

    SCCP_DEBUG(("Sending message to Network: ctxt = 0x%x  $$$\n",
                 hdr->context.conref));

    return SCRCHandleSCOCMsg_PRC(mtp3, SCCP_MSG_RSR, ies, ieCount, cdp);
}


static int
HandleDownCC(ITS_HDR* hdr, MTP3_HEADER* mtp3,
             ITS_SCCP_IE* ies, int ieCount, ITS_BOOLEAN* sendToApp)
{
    SCCP_CONN_CTXT *foundCtxt, *foundCtxt2;
    ITS_INT dlref, slref;
    SCCP_REF_NUM *sl = NULL, *dl = NULL;
    SCCP_ADDR *cdp = NULL;
    SCCP_ADDR *clp = NULL;
    SCCP_PROT_CLASS *pc = NULL;
    ITS_CTXT        tempAssocRef;
    ITS_BOOLEAN     tempIsIntermediate;
    int i, error;
    int isRLSDtobesent = 0;
    int releaseID = 0;
    ITS_EVENT event;
    ITS_HDR hdrntfy;
    ITS_OCTET creditvalue = 0;

    SCCP_DEBUG(("HandleDownCC\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
            case SCCP_PRM_CALLED_PARTY_ADDR:
                cdp = &ies[i].param_data.calledPartyAddr;
                break;

            case SCCP_PRM_CALLING_PARTY_ADDR:
                clp = &ies[i].param_data.callingPartyAddr;
                break;

            case SCCP_PRM_SRC_LOCAL_REF:
                sl = &ies[i].param_data.sourceLocalReference;
                break;

            case SCCP_PRM_DEST_LOCAL_REF:
                dl = &ies[i].param_data.destinationLocalReference;
                releaseID = i;  
                break;

            case SCCP_PRM_PROTOCOL_CLASS:
                pc = &ies[i].param_data.protocolClass;
                break;

            case SCCP_PRM_CREDIT:   
                creditvalue = ies[i].param_data.credit.win_size;
                if (!(0x0F & creditvalue))
                {
                    SCCP_ERROR(("HandleDownCC: credit value is zero in CC\n"));
                    isRLSDtobesent = 1; 

                }
                break;
        }
    }

    if (dl == NULL)
    {
        /* Discarding Message - Missing Mandatory Parameter. */
        SCCP_ERROR(("HandleDownCC: Missing destination reference number \n"));

        /*Q752 Implementation Syntax Error Detected Value Error */
        SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++; 

        return (ITS_EMISSMAND);
    }

    dlref = RN_GET_REF_NUM(*dl); 

#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[0] != 0)
    {
        SCCP_DEBUG(("HandleDownCC:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif

    hdr->context.conref = (ITS_CTXT)dlref;

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("HandleDownCC: Couldn't acquire mutex.\n"));
                break;

            case (ITS_EINUSE):
                SCCP_ERROR(("HandleDownCC: DSM Row Locked.\n"));
                break;

            case (ITS_ENOTFOUND):
                SCCP_WARNING(("HandleDownCC:ConnectionReference not in table"
                              "\n"));                            
                break;
        }

        return (ITS_ENOCONN);
    }
    
    /* Q752 Implementation */
    if (sl == NULL)
    {
        /* Discarding Message - Missing Mandatory Parameter. */
        SCCP_ERROR(("HandleDownCC: Missing source reference number \n"));

        /* Syntax Error Detected Value Error */ 
        SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++;
        return (ITS_EMISSMAND);
    }


    slref = RN_GET_REF_NUM(*sl);

    /*CC recveived in Data Transfer state hence the messsage is discarded */

    if (foundCtxt->state == SCCP_DATA_TRANSFER
        ||foundCtxt->state == SCCP_OUT_RELEASE_PEND
        || foundCtxt->state == SCCP_CONN_IN_PEND)
    {
        SCCP_ERROR(("HandleDownCC:CC received in Data Transfer state\
                    or in Release Pending state, hence message discarded\n"));

        /* Unknown message in this state*/
        SCCP_Alarm_PRC(656, __FILE__, __LINE__, "family=%s", "PRC");

        return (ITS_EINVALIDARGS);
       
    }
    else if (foundCtxt->state == SCCP_IN_RESET_PEND)
    {
        SCCP_DEBUG(("HandleDownCC:CC received in Reset pending state\n"));
        SCCP_Alarm_PRC(656, __FILE__, __LINE__, "family=%s", "PRC");

        *sendToApp = ITS_FALSE;
        ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[ieCount].param_length = sizeof(MTP3_HEADER);
        ies[ieCount].param_data.routingLabel = *mtp3;

        ieCount++;

        hdrntfy.type = ITS_SCCP;
        event.src = ITS_SCCP_SRC;
        hdrntfy.context.conref = hdr->context.conref;

        SCCP_DEBUG(("HandleDownCC:Ntfy for CC is send to application\n"));

        if (SCCP_Encode(ies, ieCount, SCCP_MSG_CC, &event, &hdrntfy,
                              &SCCP_CC_Desc)!=ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownCC:Error in encoding CC  message\n"));

            return (ITS_ENOMSG);
        }

        ITS_SET_CTXT(&event.data[1], hdrntfy.context.conref);

        /* send to the application */
        if (SCCP_SendToAPP(mtp3, &hdrntfy, SCCP_MSG_CC, &event)!=ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownCC:Error while sending to Application."));
        }

        SCCP_DEBUG(("HandleDownCC:RSR is sent to the remote end\n"));

        RN_SET_REF_NUM(ies[releaseID].param_data.destinationLocalReference,
                       foundCtxt->dlref);
        releaseID++;

        RN_SET_REF_NUM(ies[releaseID].param_data.sourceLocalReference,
                       foundCtxt->slref);
        releaseID++;

        ies[releaseID].param_id = SCCP_PRM_RESET_CAUSE;
        ies[releaseID].param_length = sizeof(SCCP_RES_CAUSE);
        ies[releaseID].param_data.resetCause.cause =SCCP_RES_NETWORK_OP;

        releaseID++;

        ieCount = releaseID;
        
#if defined(CONNECTION_TIMERS)

        if (foundCtxt->receiveInactivity)
        {
            SCCP_DEBUG(("HandleDownCC:Receive inactivity timer is killed\n"));
            TIMERS_CancelTimer(foundCtxt->receiveInactivity);
        }
        foundCtxt->receiveInactivity =
            TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                    TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                          SCCP_T_iar),
                                            foundCtxt, sizeof(SCCP_CONN_CTXT));
        SCCP_DEBUG(("HandleDownCC:Receive inactivity timer is restarted\n"));
#endif

        error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownCC: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        if (HandleAppRSR(hdr, mtp3, ies, ieCount)!= ITS_SUCCESS)
        {
            SCCP_DEBUG(("HandleDownCC:Error occured  while sending RSR\n"));

        }
        return (ITS_EBADSTATE);
    }    

    foundCtxt->dlref = slref;
    if (isRLSDtobesent == 1
        || foundCtxt->state == SCCP_IN_RELEASE_PEND)
    {
        SCCP_Alarm_PRC(656, __FILE__, __LINE__, "family=%s", "PRC");
        if (isRLSDtobesent)
        {
            SCCP_DEBUG(("HandleDownCC:Credit Value in CC is Zero\n"));
        }
        else
        {
            SCCP_DEBUG(("HandleDownCC:CC received in incoming"
                        " Release Pending state\n" ));
        }
#if defined(CONNECTION_TIMERS)
        if (foundCtxt->connectTimer)
        {
            SCCP_DEBUG(("HandleDownCC:Connect timer is killed\n"));

            TIMERS_CancelTimer(foundCtxt->connectTimer);
        }
        if (foundCtxt->releaseTimer)
        {
            SCCP_DEBUG(("HandleDownCC:Release timer is killed\n"));

            TIMERS_CancelTimer(foundCtxt->releaseTimer);
        }

#endif  
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownCC: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        SCCP_DEBUG(("HandleDownCC:Notification for RLSD is sent to app and"
                    " RLSD is sent to remote\n"));

        SendRLSD(foundCtxt, SCCP_RLC_INCONSISTENT_DATA , ITS_FALSE);

        NotifyRLSDToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_RLC_INCONSISTENT_DATA);

        foundCtxt = NULL;
        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE); 
    }

    foundCtxt->inLabel = *mtp3;

    foundCtxt->state = SCCP_DATA_TRANSFER;
    foundCtxt->dataState = SCCP_DATA_NORMAL;

    switch ((pc->pclass & SCCP_PCLASS_MASK))
    {
        case SCCP_PCLASS_2:
            if (foundCtxt->pclass == SCCP_PCLASS_3)
            {
                foundCtxt->windowSize = 0;
                foundCtxt->pclass = SCCP_PCLASS_2;
            }
            break;

        case SCCP_PCLASS_3:
            if (foundCtxt->pclass == SCCP_PCLASS_2)
            {
                SCCP_WARNING(("HandleDownCC: Invalid protocol class for"
                              " connection\n"));

                /* Incoming Message - Protocol Class of Message does not match 
                   Connection. */

                error = DSM_Commit(DSM_SccpFtGroupId,
                                   DSM_TABLE_ITU_SCCP_CTXT,
                                   (ITS_OCTET *)&hdr->context.conref, 
                                    sizeof(hdr->context.conref), foundCtxt);

                if (error != ITS_SUCCESS)
                {
                    SCCP_ERROR(("HandleDownCC: DSM unable to free Reference."
                                "\n"));

                    /* Unable to Commit Session Context to CTXT Table. */
                }

                SCCP_ERROR(("HandleDownCC:Relase procedure is initiated by"
                            " stack,sending RLSD to the remote end\n"));

                SendRLSD(foundCtxt, SCCP_RLC_INCONSISTENT_DATA , ITS_FALSE);
                NotifyRLSDToApp(hdr->context.conref, mtp3, ies, releaseID,
                                SCCP_RLC_INCONSISTENT_DATA);

                *sendToApp = ITS_FALSE;
                return (ITS_ENOCONN);
            }

           if (foundCtxt->windowSize < creditvalue)
           {


               SCCP_DEBUG(("HandleDownCC:Invalid Credit value sent in CC from"
                           " the application,message is discarded\n"));

               return(ITS_EBADCHKSUM);
           }

           break;

        default:
            SCCP_WARNING(("HandleDownCC: Invalid protocol class for"
                          " connection\n"));

        /* Incoming Message - Protocol Class of Message does not match 
           Connection. */

            error = DSM_Commit(DSM_SccpFtGroupId,
                               DSM_TABLE_ITU_SCCP_CTXT,
                               (ITS_OCTET *)&hdr->context.conref, 
                                sizeof(hdr->context.conref), foundCtxt);

            if (error != ITS_SUCCESS)
            {
                SCCP_ERROR(("HandleDownCC: DSM unable to free Reference.\n"));

                /* Unable to Commit Session Context to CTXT Table. */
            }

            return (ITS_ENOCONN);
    }

#if defined(CONNECTION_TIMERS)
    TIMERS_CancelTimer(foundCtxt->connectTimer);

    if(foundCtxt->releaseTimer)
    {
        SCCP_DEBUG(("HandleDownCC:ReleaseTimer is killed as waiting CC"
                    "  received.\n "));       

        TIMERS_CancelTimer(foundCtxt->releaseTimer);
        
        SCCP_DEBUG(("HandleDownCC:RLSD is sent to the other end for received"
                    "  CC\n"));

        SendRLSD(foundCtxt, SCCP_REF_ACCESS_CONG , ITS_FALSE);

        *sendToApp = ITS_FALSE;

        return(ITS_SUCCESS);
    }

    foundCtxt->sendInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                     SCCP_T_ias),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));

    foundCtxt->receiveInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                     SCCP_T_iar),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
#endif

    /*Save these fields so can use after release lock on row */
    tempAssocRef = foundCtxt->assocRef;
    tempIsIntermediate = foundCtxt->isIntermediate;

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownCC: DSM unable to free Reference.\n"));

        /* Unable to Commit Session Context to CTXT Table. */
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */
    
    if (tempIsIntermediate)
    {
        *sendToApp = ITS_FALSE;

        foundCtxt2 = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                                DSM_TABLE_ITU_SCCP_CTXT, 
                                                (ITS_OCTET *)&tempAssocRef, 
                                                sizeof(tempAssocRef), &error);

        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
                case (ITS_EBADMUTEX):
                    SCCP_ERROR(("HandleDownCC: Couldn't acquire mutex.\n"));

                    break;
                case (ITS_EINUSE):
                    SCCP_ERROR(("HandleDownCC: DSM Row Locked.\n"));

                    break;
                case (ITS_ENOTFOUND):
                    SCCP_WARNING(("HandleDownCC: Can't find Connection"
                                  "Reference in table.\n"));

                    break;
            }

            return (ITS_ENOCONN);
        }

        RN_SET_REF_NUM(*sl, foundCtxt2->slref);
        RN_SET_REF_NUM(*dl, foundCtxt2->dlref);

        *mtp3 = foundCtxt2->outLabel;

        hdr->context.conref = foundCtxt2->slref;

        if (cdp)
        {
            *cdp = foundCtxt2->daddr;
        }

        ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[ieCount].param_length = sizeof(MTP3_HEADER);
        ies[ieCount].param_data.routingLabel = foundCtxt2->outLabel;
        ieCount++;

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&tempAssocRef, 
                           sizeof(tempAssocRef), foundCtxt2);

        foundCtxt2 = NULL;    /* Not safe to use with out lock */

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownCC: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

    }

    if (!*sendToApp)
    {
        return HandleAppCC(hdr, mtp3, ies, ieCount);
    }

    return (ITS_SUCCESS);
}

/*
 * send connection refused
 */
static int
HandleAppCREF(ITS_HDR* hdr, MTP3_HEADER* mtp3,
              ITS_SCCP_IE* ies, int ieCount)
{
    SCCP_CONN_CTXT *foundCtxt;
    SCCP_ADDR *cdp = NULL, local;
    SCCP_REF_NUM *dl = NULL;
    int i, error;

    SCCP_DEBUG(("HandleAppCREF\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
            case SCCP_PRM_CALLED_PARTY_ADDR:
                cdp = &ies[i].param_data.calledPartyAddr;
                break;

            case SCCP_PRM_DEST_LOCAL_REF:
                dl = &ies[i].param_data.destinationLocalReference;
                break;
        }
    }

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT, 
                                           (ITS_OCTET *)&hdr->context.conref, 
                                           sizeof(hdr->context.conref), &error);

    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("HandleAppCREF: Couldn't acquire mutex.\n"));

                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleAppCREF: DSM Row Locked.\n"));

                break;
            case (ITS_ENOTFOUND):
                SCCP_WARNING(("HandleAppCREF: Can't find ConnectionReference"
                              " in table.\n"));

                break;
        }

        return (ITS_ENOCONN);
    }

    *mtp3 = foundCtxt->outLabel;

    if (cdp == NULL)
    {
        local = foundCtxt->daddr;
        cdp = &local;
    }

#if defined(CONNECTION_TIMERS)
    TIMERS_CancelTimer(foundCtxt->connectTimer);
#endif

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleAppCREF: DSM unable to free Reference.\n"));

        /* Unable to Commit Session Context to CTXT Table. */
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    PEG_IncrPeg(PRC_SCCP_Pegs, PEG_SCCP_CREF_TO_REMOTE_SENT);

    /*Q752 Implementation Message CREF Recieved */
    SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.messageCREFSent++;

    /* we allocated this one.  Release it */
    SCCP_DeleteLocalReference_PRC(hdr->context.conref);

    if (gcsMessageBasedRedundancyIsActive)
    {
        ITS_EVENT dummyEvent;
        ITS_UINT  dest;

        SCCP_DEBUG(("GCS Message Based Redundancy is ACTIVE\n"));

        dummyEvent.src  = ITS_GCS_EVENT_TO_NETWORK;
        dummyEvent.data = 0;

        dest = ROUTE_SelectApplication(hdr, &dummyEvent, ITS_TRUE);

        if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
        {
            /* Don't send message for routing to the network */
            SCCP_WARNING(("Message is consumed by SCCP: ctxt = 0x%x\n",
                          hdr->context.conref));
            return ITS_SUCCESS;
        }

    }

    SCCP_DEBUG(("Sending message to Network: ctxt = 0x%x  $$$\n",
                 hdr->context.conref));

    return SCRCHandleSCOCMsg_PRC(mtp3, SCCP_MSG_CREF, ies, ieCount, cdp);
}

static int
HandleDownCREF(ITS_HDR* hdr, MTP3_HEADER* mtp3,
               ITS_SCCP_IE* ies, int ieCount, ITS_BOOLEAN* sendToApp)
{
    ITS_INT dlref;
    SCCP_REF_NUM *dl = NULL;
    SCCP_ADDR *cdp = NULL;
    SCCP_CONN_CTXT *foundCtxt, *foundCtxt2;
    ITS_CTXT        tempAssocRef;
    ITS_BOOLEAN     tempIsIntermediate;
    int i, error;
    int releaseID = 0;

    SCCP_DEBUG(("HandleDownCREF\n"));

    PEG_IncrPeg(PRC_SCCP_Pegs, PEG_SCCP_REMOTE_CREF_RCVD);

    /*Q752 Implementation Message CREF Recieved */ 
    SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.messageCREFRcvd++;

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
            case SCCP_PRM_CALLED_PARTY_ADDR:
                cdp = &ies[i].param_data.calledPartyAddr;
                break;

            case SCCP_PRM_DEST_LOCAL_REF:
                dl = &ies[i].param_data.destinationLocalReference;
                releaseID = i;
                break;
        }
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleDownCREF: Missing destination reference number \n"));

        /* Q752 Implementation Syntax Error Detected Value Error */ 
        SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++;
         
        /* Incoming Message - Discarding Message - Missing Mandatory 
           Parameter. */

        return (ITS_EMISSMAND);
    }
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[0] != 0)
    {
        SCCP_DEBUG(("HandleDownCREF:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif

    dlref = RN_GET_REF_NUM(*dl); 
    hdr->context.conref = (ITS_CTXT)dlref;

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);

    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("HandleDownCREF: Couldn't acquire mutex.\n"));

                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleDownCREF: DSM Row Locked.\n"));

                break;
            case (ITS_ENOTFOUND):
                SCCP_WARNING(("HandleDownCREF: Can't find ConnectionReference"
                          " in table.\n"));

                SCCP_ERROR(("HandleDownCREF:CREF received with unassigned DLR"
                            " hence the message is discarded\n"));
                break;
        }

        return (ITS_ENOCONN);
    }

    if (foundCtxt->state == SCCP_DATA_TRANSFER
       || foundCtxt->state == SCCP_OUT_RELEASE_PEND
       || foundCtxt->state == SCCP_CONN_IN_PEND)
    {
        SCCP_ERROR(("HandleDownCREF:CREF received in state = %x,dicarded",
                     foundCtxt->state));

        /* Unknown message in this state*/
        SCCP_Alarm_PRC(657, __FILE__, __LINE__, "family=%s", "PRC");

        return (ITS_EINVALIDARGS);
    }
    if (foundCtxt->state == SCCP_IN_RELEASE_PEND)
    {
        SCCP_DEBUG(("HandleDownCREF:CREF received in incoming"
                    " Release Pending state\n" ));
        SCCP_Alarm_PRC(657, __FILE__, __LINE__, "family=%s", "PRC");
        
#if defined(CONNECTION_TIMERS)
        
        if (foundCtxt->releaseTimer)
        {
            SCCP_DEBUG(("HandleDownCREF:Release timer is killed\n"));

            TIMERS_CancelTimer(foundCtxt->releaseTimer);
        }
#endif
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownCREF: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        SCCP_DEBUG(("HandleDownCREF:Notification for RLSD is sent to app and"
                    " RLSD is sent to remote\n"));

        SendRLSD(foundCtxt, SCCP_RLC_INCONSISTENT_DATA , ITS_FALSE);

        /*Notification for the application*/
         releaseID++;

        RN_SET_REF_NUM(ies[releaseID].param_data.sourceLocalReference,
                       foundCtxt->slref);
        releaseID--;

        NotifyRLSDToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_RLC_INCONSISTENT_DATA);

        foundCtxt = NULL;

        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);
    }

#if defined(CONNECTION_TIMERS)
    TIMERS_CancelTimer(foundCtxt->connectTimer);

    if(foundCtxt->releaseTimer)
    {
        SCCP_DEBUG(("HandleDownCREF:ReleaseTimer is killed as waiting CREF"
                    "  received."));

        TIMERS_CancelTimer(foundCtxt->releaseTimer);

        SCCP_DEBUG(("HandleDownCREF:RLSD is sent to the other end for"
                     " received CREF\n"));

        SendRLSD(foundCtxt, SCCP_REF_ACCESS_CONG, ITS_FALSE);
         /*Release the lock*/
         error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref,
                       sizeof(hdr->context.conref), foundCtxt);
         if (error != ITS_SUCCESS)
         {
             SCCP_ERROR(("HandleDownCREF: DSM unable to free Reference.\n"));

             /* Unable to Commit Session Context to CTXT Table. */
         }

        foundCtxt = NULL;
        *sendToApp = ITS_FALSE;

        return(ITS_SUCCESS);
    }
#endif

    /*Save these fields so can use after release lock on row */
    tempAssocRef = foundCtxt->assocRef;
    tempIsIntermediate = foundCtxt->isIntermediate;

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownCREF: DSM unable to free Reference.\n"));

        /* Unable to Commit Session Context to CTXT Table. */
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (tempIsIntermediate)
    {
        *sendToApp = ITS_FALSE;

        foundCtxt2 = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                                DSM_TABLE_ITU_SCCP_CTXT, 
                                                (ITS_OCTET *)&tempAssocRef, 
                                                sizeof(tempAssocRef), &error);

        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
                case (ITS_EBADMUTEX):
                    SCCP_ERROR(("HandleDownCREF: Couldn't acquire mutex.\n"));

                    break;
                case (ITS_EINUSE):
                    SCCP_ERROR(("HandleDownCREF: DSM Row Locked.\n"));

                    break;
                case (ITS_ENOTFOUND):
                    SCCP_WARNING(("HandleDownCREF: Can't find Connection"
                                  "Reference in table.\n"));

                    break;
            }

            return (ITS_ENOCONN);
        }

        RN_SET_REF_NUM(*dl, foundCtxt2->dlref);

        *mtp3 = foundCtxt2->outLabel;

        hdr->context.conref = foundCtxt2->slref;

        ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[ieCount].param_length = sizeof(MTP3_HEADER);
        ies[ieCount].param_data.routingLabel = foundCtxt2->outLabel;
        ieCount++;

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&tempAssocRef, 
                           sizeof(tempAssocRef), foundCtxt2);
        foundCtxt2 = NULL;    /* Not safe to use with out lock */
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownCREF: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }
    }


    SCCP_DeleteLocalReference_PRC(hdr->context.conref);

    if (!*sendToApp)
    {
        return HandleAppCREF(hdr, mtp3, ies, ieCount);
    }

    return (ITS_SUCCESS);
}

/*
 * send release complete
 */
static int
HandleAppRLC(ITS_HDR* hdr, MTP3_HEADER* mtp3,
             ITS_SCCP_IE* ies, int ieCount)
{
    SCCP_CONN_CTXT *foundCtxt;
    SCCP_REF_NUM *sl = NULL, *dl = NULL;
    SCCP_ADDR local, *cdp = &local;
    int i, error;

    SCCP_DEBUG(("HandleAppRLC\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
            case SCCP_PRM_SRC_LOCAL_REF:
                sl = &ies[i].param_data.sourceLocalReference;
                break;

            case SCCP_PRM_DEST_LOCAL_REF:
                dl = &ies[i].param_data.destinationLocalReference;
                break;
        }
    }

    if (RN_GET_REF_NUM(*sl) != hdr->context.conref)
    {
        SCCP_ERROR(("HandleAppRLC: Released and context mismatch\n"));

        /* Outgoing Message - Local Reference does not match Context. */

        return (ITS_EINVALIDARGS);
    }

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("HandleAppRLC: Couldn't acquire mutex.\n"));

                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleAppRLC: DSM Row Locked.\n"));

                break;
            case (ITS_ENOTFOUND):
                SCCP_WARNING(("HandleAppRLC: Can't find ConnectionReference"
                              " in table.\n"));

                break;
        }

        return (ITS_ENOCONN);
    }

    *mtp3 = foundCtxt->outLabel;

    local = foundCtxt->daddr;

#if defined(CONNECTION_TIMERS)
    TIMERS_CancelTimer(foundCtxt->releaseTimer);
#endif

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleAppRLC: DSM unable to free Reference.\n"));

        /* Unable to Commit Session Context to CTXT Table. */
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    /* we allocated this one.  Release it */
    SCCP_DeleteLocalReference_PRC(hdr->context.conref);

    if (gcsMessageBasedRedundancyIsActive)
    {
        ITS_EVENT dummyEvent;
        ITS_UINT  dest;

        SCCP_DEBUG(("GCS Message Based Redundancy is ACTIVE\n"));

        dummyEvent.src  = ITS_GCS_EVENT_TO_NETWORK;
        dummyEvent.data = 0;

        dest = ROUTE_SelectApplication(hdr, &dummyEvent, ITS_TRUE);

        if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
        {
            /* Don't send message for routing to the network */
            SCCP_WARNING(("Message is consumed by SCCP: ctxt = 0x%x\n",
                          hdr->context.conref));
            return ITS_SUCCESS;
        }

    }

    SCCP_DEBUG(("Sending message to Network: ctxt = 0x%x  $$$\n",
                 hdr->context.conref));

    return SCRCHandleSCOCMsg_PRC(mtp3, SCCP_MSG_RLC, ies, ieCount, cdp);
}


/*****************************************************************************
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference                   Description
 *  --------------------------------------------------------------------------
 *  csireesh  04-04-2005  Bug ID:0621,
 *                        Bug ID:0622, Bug ID:0623
 *
 ****************************************************************************/
static int
HandleDownRLSD(ITS_HDR* hdr, MTP3_HEADER* mtp3,
               ITS_SCCP_IE* ies, int ieCount, ITS_BOOLEAN* sendToApp)
{
    ITS_INT dlref;
    SCCP_REF_NUM *sl = NULL, *dl = NULL;
    SCCP_CONN_CTXT *foundCtxt, *foundCtxt2;
    ITS_CTXT        tempAssocRef;
    ITS_BOOLEAN     tempIsIntermediate;
    ITS_INT i, error;
    int releaseID = 0;

    SCCP_DEBUG(("HandleDownRLSD\n"));
    
    /* Q752 Implementation */
        SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.providerInitiatedReleaseConn++;   
  
    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
            case SCCP_PRM_SRC_LOCAL_REF:
                sl = &ies[i].param_data.sourceLocalReference;
                break;

            case SCCP_PRM_DEST_LOCAL_REF:
                dl = &ies[i].param_data.destinationLocalReference;
                releaseID = i;
                break;
        }
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleDownRLSD: Missing destination reference number \n"));

        /*Q752 Implementation Syntax Error Detected Value Error */ 
        SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++;

        return (ITS_EMISSMAND);
    }

#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[0] != 0)
    {
        SCCP_DEBUG(("HandleDownRLSD:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif
    
    /* Q752 Implementation */
    if (sl == NULL)
    {
        SCCP_ERROR(("HandleDownRLSD: Missing source reference number \n"));
        /* Syntax Error Detected Value Error */
        SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++;
        return (ITS_EMISSMAND);
    }
 

    dlref = RN_GET_REF_NUM(*dl); 
    hdr->context.conref = (ITS_CTXT)dlref;

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("HandleDownRLSD: Couldn't acquire mutex.\n"));
                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleDownRLSD: DSM Row Locked.\n"));

                break;
            case (ITS_ENOTFOUND):
                SCCP_WARNING(("HandleDownRLSD: Can't find ConnectionReference"
                              " in table.\n"));
                break;
        }

        return (ITS_ENOCONN);
    }

    if (MTP3_RL_GET_DPC_VALUE(foundCtxt->outLabel.label)!=
        MTP3_RL_GET_OPC_VALUE(mtp3->label))
    {
        SCCP_ERROR(("HandleDownRLSD:Orignating Point Code received not equal\
                     to the Pc stored locally\n"));

        SendERR(foundCtxt, SCCP_ERR_PC_MISMATCH, ITS_FALSE);

        NotifyERRToApp(hdr->context.conref, mtp3, ies, releaseID,
                      SCCP_ERR_PC_MISMATCH);

        *sendToApp = ITS_FALSE;

        return(ITS_EINVALIDARGS);
    }

    if (foundCtxt->dlref != RN_GET_REF_NUM(*sl))
    {
        SCCP_DEBUG(("HandleDownRLSD:Connection context dlref mismatch with"
                     " the received slref"));
         /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownRLSD: DSM unable to free Reference.\n"));
        }

        SendERR(foundCtxt, SCCP_ERR_BAD_LRN, ITS_FALSE);

        NotifyERRToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_ERR_BAD_LRN);
        foundCtxt = NULL;

        *sendToApp = ITS_FALSE;

        return (ITS_EINVALIDARGS);
    }

    if(foundCtxt->state == SCCP_CONN_IN_PEND
       || foundCtxt->state == SCCP_IN_RELEASE_PEND)
    {
        SCCP_ERROR(("HandleDownRLSD:RLSD received in Connection Pending state" 
                     "or Release Pending state so message is discarded\n"));

        /* Unknown message in this state*/
        SCCP_Alarm_PRC(658, __FILE__, __LINE__, "family=%s", "PRC");

        SCCP_DeleteLocalReference_PRC(hdr->context.conref);

        return (ITS_EBADSTATE);
       
    }
    else if (foundCtxt->state == SCCP_CONN_OUT_PEND)
    {
        SCCP_DEBUG(("HandleDownRLSD:RLSD received in Outgoing Connection"
                    " Pending state\n"));
        SCCP_Alarm_PRC(658, __FILE__, __LINE__, "family=%s", "PRC");

#if defined(CONNECTION_TIMERS)
        if (foundCtxt->connectTimer)
        {
            SCCP_DEBUG(("HandleDownRLSD:Connect timer is killed\n"));

            TIMERS_CancelTimer(foundCtxt->connectTimer);
        }
#endif
        /*Release the DSM lock */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownRLSD: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
            SCCP_Alarm_PRC(658, __FILE__, __LINE__, "family=%s", "PRC");
        }
        foundCtxt = NULL;

        SCCP_DEBUG(("HandleDownRLSD:Notification is sent to app and"
                    " resources are cleared\n"));

        NotifyERRToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_ERR_UNQUAL);

        SCCP_DeleteLocalReference_PRC(hdr->context.conref);

        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);
   }
 
   foundCtxt->state = SCCP_IN_RELEASE_PEND;

#if defined(CONNECTION_TIMERS)
    foundCtxt->releaseTimer =
        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                     SCCP_T_release),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));

    if (foundCtxt->receiveInactivity)
    {
        TIMERS_CancelTimer(foundCtxt->receiveInactivity);
    }

    if (foundCtxt->sendInactivity)
    {
        TIMERS_CancelTimer(foundCtxt->sendInactivity);
    }
#endif

    /*Save these fields so can use after release lock on row */
    tempAssocRef = foundCtxt->assocRef;
    tempIsIntermediate = foundCtxt->isIntermediate;

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownRLSD: DSM unable to free Reference.\n"));

        /* Unable to Commit Session Context to CTXT Table. */
    }
    
    SCCP_DEBUG(("HandleDownRLSD:RLC is sent to MTP3\n"));

    RN_SET_REF_NUM(ies[releaseID].param_data.destinationLocalReference,
                       foundCtxt->dlref);
    releaseID++;

    RN_SET_REF_NUM(ies[releaseID].param_data.sourceLocalReference,
                       foundCtxt->slref);
    releaseID++;

    ieCount = releaseID++;

    if (HandleAppRLC( hdr,mtp3, ies, ieCount) != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownRLSD:Failure in Application RLC\n"));

        return(ITS_ENOCONN);
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (tempIsIntermediate)
    {
        *sendToApp = ITS_FALSE;

        foundCtxt2 = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                                DSM_TABLE_ITU_SCCP_CTXT, 
                                                (ITS_OCTET *)&tempAssocRef, 
                                                sizeof(tempAssocRef), &error);
        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
                case (ITS_EBADMUTEX):
                    SCCP_ERROR(("HandleDownRLSD: Couldn't acquire mutex.\n"));

                    break;
                case (ITS_EINUSE):
                    SCCP_ERROR(("HandleDownRLSD: DSM Row Locked.\n"));

                    break;
                case (ITS_ENOTFOUND):
                    SCCP_WARNING(("HandleDownRLSD: Can't find Connection"
                                  "Reference in table.\n"));

                    break;
            }

            return (ITS_ENOCONN);
        }

        RN_SET_REF_NUM(*sl, foundCtxt2->slref);
        RN_SET_REF_NUM(*dl, foundCtxt2->dlref);

        *mtp3 = foundCtxt2->outLabel;

        hdr->context.conref = foundCtxt2->slref;

        ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[ieCount].param_length = sizeof(MTP3_HEADER);
        ies[ieCount].param_data.routingLabel = foundCtxt2->outLabel;
        ieCount++;

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&tempAssocRef, 
                           sizeof(tempAssocRef), foundCtxt2);

        foundCtxt2 = NULL;    /* Not safe to use with out lock */

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownRLSD: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }
    }

    if (!*sendToApp)
    {
        return HandleAppRLSD(hdr, mtp3, ies, ieCount);
    }

    return (ITS_SUCCESS);
}

static int
HandleDownRLC(ITS_HDR* hdr, MTP3_HEADER* mtp3,
              ITS_SCCP_IE* ies, int ieCount, ITS_BOOLEAN* sendToApp)
{
    SCCP_CONN_CTXT *foundCtxt, *foundCtxt2;
    ITS_INT dlref;
    SCCP_REF_NUM *sl = NULL, *dl = NULL;
    ITS_CTXT        tempAssocRef;
    ITS_BOOLEAN     tempIsIntermediate;
    int i, error;
    int releaseID = 0;

    SCCP_DEBUG(("HandleDownRLC\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
            case SCCP_PRM_SRC_LOCAL_REF:
                sl = &ies[i].param_data.sourceLocalReference;
                break;

            case SCCP_PRM_DEST_LOCAL_REF:
                dl = &ies[i].param_data.destinationLocalReference;
                releaseID = i;
                break;
        }
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleDownRLC: Missing destination reference number \n"));

        /*Q752 Implementation Syntax Error Detected Value Error */     
        SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++;

       /* Incoming Message - Discarding Message - Missing Mandatory Parameter */

        return (ITS_EMISSMAND);
    }

    /* Q752 Implementation */
    if (sl == NULL)
    {
        SCCP_ERROR(("HandleDownRLC: Missing source reference number \n"));
 
        /* Syntax Error Detected Value Error */ 
        SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++;
       
        /* Incoming Message - Discarding Message - Missing Mandatory Parameter */

        return (ITS_EMISSMAND);
    }

#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[0] != 0)
    {
        SCCP_DEBUG(("HandleDownRLC:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif

    dlref = RN_GET_REF_NUM(*dl); 
    hdr->context.conref = (ITS_CTXT)dlref;

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("HandleDownRLC: Couldn't acquire mutex.\n"));

                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleDownRLC: DSM Row Locked.\n"));

                break;
            case (ITS_ENOTFOUND):
                SCCP_WARNING(("HandleDownRLC: Can't find ConnectionReference"
                              " in table.\n"));

                SCCP_ERROR(("HandleDownRLC:RLC received with unassigned DLR"
                            " hence the message is discarded\n"));

                break;
        }

        return (ITS_ENOCONN);
    }

    if (MTP3_RL_GET_DPC_VALUE(foundCtxt->outLabel.label)!=
        MTP3_RL_GET_OPC_VALUE(mtp3->label))
    {
        SCCP_ERROR(("HandleDownRLC:Orignating Point Code received not equal to\
                     the Pc stored locally hence the msg is discarded\n"));

        return(ITS_EINVALIDARGS);
    }

    if (foundCtxt->state == SCCP_CONN_OUT_PEND)
    {
        SCCP_DEBUG(("HandleDownRLC:RLC received in outgoing connection"
                    " pending state\n"));
        SCCP_Alarm_PRC(659, __FILE__, __LINE__, "family=%s", "PRC");

#if defined(CONNECTION_TIMERS)
        if (foundCtxt->connectTimer)
        {
            SCCP_DEBUG(("HandleDownRLC:Connect timer is killed\n"));

            TIMERS_CancelTimer(foundCtxt->connectTimer);
        }
#endif

        /*Release the DSM lock */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownRLC: DSM unable to free Reference.\n"));
        }

        foundCtxt = NULL;

        SCCP_DEBUG(("HandleDownRLC:Notification is sent to app and"
                    " resources are cleared\n"));

        NotifyERRToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_ERR_UNQUAL);

        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);
    }

    else if (foundCtxt->state == SCCP_DATA_TRANSFER
             || foundCtxt->state == SCCP_CONN_IN_PEND)
    {
        SCCP_ERROR(("HandleDownRLC:RLC received in Data Transfer or"
                    " incoming connection pending,msg discarded\n"));

        /* Unknown message in this state*/
        SCCP_Alarm_PRC(659, __FILE__, __LINE__, "family=%s", "PRC");

        return (ITS_EINVALIDARGS);
       
    } 
    if (foundCtxt->state == SCCP_IN_RELEASE_PEND)
    {
        SCCP_DEBUG(("HandleDownRLC:RLC received in incoming"
                    " Release Pending state\n" ));
        SCCP_Alarm_PRC(659, __FILE__, __LINE__, "family=%s", "PRC");

        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownRLC: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        SCCP_DEBUG(("HandleDownRLC:Notification for RLSD is sent to app and"
                    " RLSD is sent to remote\n"));

        SendRLSD(foundCtxt, SCCP_RLC_INCONSISTENT_DATA , ITS_FALSE);

        /*Notification for the application*/
        NotifyRLSDToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_RLC_INCONSISTENT_DATA);

        foundCtxt = NULL;

        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);
    }

    if (foundCtxt->dlref != RN_GET_REF_NUM(*sl))
    {
       SCCP_DEBUG(("HandleDownRLC:Connection context dlref mismatch with"
                     " the received slref"));

        *sendToApp = ITS_FALSE;

        return (ITS_EINVALIDARGS);
    }

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->releaseTimer)
    {
        TIMERS_CancelTimer(foundCtxt->releaseTimer);
    }

    if (foundCtxt->repeatReleaseTimer)
    {
        TIMERS_CancelTimer(foundCtxt->repeatReleaseTimer);
    }

    if (foundCtxt->intervalTimer)
    {
        TIMERS_CancelTimer(foundCtxt->intervalTimer);
    }
#endif

    /*Save these fields so can use after release lock on row */
    tempAssocRef = foundCtxt->assocRef;
    tempIsIntermediate = foundCtxt->isIntermediate;

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownRLC: DSM unable to free Reference.\n"));

        /* Unable to Commit Session Context to CTXT Table. */
    }
    
    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (tempIsIntermediate)
    {
        *sendToApp = ITS_FALSE;

        foundCtxt2 = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                                DSM_TABLE_ITU_SCCP_CTXT, 
                                                (ITS_OCTET *)&tempAssocRef, 
                                                sizeof(tempAssocRef), &error);

        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
                case (ITS_EBADMUTEX):
                    SCCP_ERROR(("HandleDownRLC: Couldn't acquire mutex.\n"));

                    break;
                case (ITS_EINUSE):
                    SCCP_ERROR(("HandleDownRLC: DSM Row Locked.\n"));

                    break;
                case (ITS_ENOTFOUND):
                    SCCP_WARNING(("HandleDownRLC: Can't find Connection"
                                  "Reference in table.\n"));

                    break;
            }

            return (ITS_ENOCONN);
        }

        RN_SET_REF_NUM(*sl, foundCtxt2->slref);
        RN_SET_REF_NUM(*dl, foundCtxt2->dlref);

        *mtp3 = foundCtxt2->outLabel;

        hdr->context.conref = foundCtxt2->slref;

        ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[ieCount].param_length = sizeof(MTP3_HEADER);
        ies[ieCount].param_data.routingLabel = foundCtxt2->outLabel;
        ieCount++;

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&tempAssocRef, 
                           sizeof(tempAssocRef), foundCtxt2);

        foundCtxt2 = NULL;    /* Not safe to use with out lock */

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownRLC: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }
    }

    SCCP_DeleteLocalReference_PRC((ITS_CTXT)dlref);

    if (!*sendToApp)
    {
        return HandleAppRLC(hdr, mtp3, ies, ieCount);
    }

    return (ITS_SUCCESS);
}

/*
 * Send DT1
 */
static int
HandleAppDT1(ITS_HDR* hdr, MTP3_HEADER* mtp3,
             ITS_SCCP_IE* ies, int ieCount)
{
    SCCP_CONN_CTXT *foundCtxt;
    SCCP_REF_NUM *dl = NULL;
    SCCP_ADDR local, *cdp = &local;
    int i, error;
    ITS_OCTET    data[SCCP_LONG_DATA_MAX];
    int          dataLen = -1;
    int          dataIndex = -1;
    int          segIndex = -1;
    int          ret = ITS_SUCCESS;
    ITS_OCTET    totalSegment;
    ITS_UINT ref;

    //Q752
    ITS_OCTET ssn, ai;
    ITS_UINT pc;

    SCCP_DEBUG(("HandleAppDT1\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_DEST_LOCAL_REF)
        {
            dl = &ies[i].param_data.destinationLocalReference;
            break;
        }
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleAppDT1: Missing destination reference number \n"));

        /*Q752 Implementation Syntax Error Detected Value Error */
        SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++;

        /* Outgoing Message - Discarding Message - Missing Mandatory 
           Parameter. */

        return (ITS_EMISSMAND);
    }

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);

    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("HandleAppDT1: Couldn't acquire mutex.\n"));

                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleAppDT1: DSM Row Locked.\n"));

                break;
            case (ITS_ENOTFOUND):
                SCCP_WARNING(("HandleAppDT1: Can't find ConnectionReference"
                              " in table.\n"));

                break;
        }

        return (ITS_ENOCONN);
    }

    if (foundCtxt->pclass != SCCP_PCLASS_2)
    {
        SCCP_ERROR(("HandleAppDT1: DT1 is invalid for protocol class.\n"));

        /* Outgoing Message - Discarding Message - Message Type not valid 
           for Protocol Class of Connection. */

        SCCP_Alarm_PRC(672, __FILE__, __LINE__, "family=%s:pclass=%x",
                       "PRC", foundCtxt->pclass);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppDT1: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EINVALIDARGS);
    }

    if (foundCtxt->state != SCCP_DATA_TRANSFER)
    {
        SCCP_ERROR(("HandleAppDT1: DT1 is invalid for connection state.\n"));
        SCCP_Alarm_PRC(660, __FILE__, __LINE__, "family=%s", "PRC");

        /* Outgoing Message - Discarding Message - Message Type not valid 
           for State of Connection. */

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppDT1: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */

        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EBADSTATE);
    }

    *mtp3 = foundCtxt->outLabel;

    local = foundCtxt->daddr;

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->sendInactivity)
    {
        TIMERS_CancelTimer(foundCtxt->sendInactivity);
    }

    foundCtxt->sendInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                     SCCP_T_ias),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
#endif
 
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_DATA)
        {
            dataIndex = i;
            dataLen = ies[i].param_length;

            memcpy(data, ies[i].param_data.userData.data, dataLen);
        }
        else if (ies[i].param_id == SCCP_PRM_LONG_DATA)
        {
            dataIndex = i;
            dataLen = ies[i].param_data.longData.len;

            memcpy(data, ies[i].param_data.longData.data, dataLen);
            ies[i].param_id = SCCP_PRM_DATA;
        }
        if (ies[i].param_id == SCCP_PRM_SEGMENT_REASSEM)
        {
            segIndex = i;
        }
    }

    totalSegment = dataLen / SCCP_MAX_DATA;

    if (dataIndex < 0)
    {
        SCCP_ERROR(("HandleAppDT1: Missing Data IE \n"));

        /* Outgoing Message - Discarding Message - Missing 
          Mandatory Parameter. */

        return (ITS_EMISSMAND);
    }

    if (dataLen % SCCP_MAX_DATA)
    {
        totalSegment++;
    }

    /* add an extra IE temparay for failure handling */
    ref = hdr->context.conref;
    ies[ieCount].param_id = SCCP_PRM_SRC_LOCAL_REF;
    ies[ieCount].param_length = sizeof(SCCP_REF_NUM);
    ies[ieCount].param_data.sourceLocalReference.refno[0] = (ref >> 16) & 0xFFU;
    ies[ieCount].param_data.sourceLocalReference.refno[1] = (ref >> 8) & 0xFFU;
    ies[ieCount].param_data.sourceLocalReference.refno[2] = (ref) & 0xFFU;
    ieCount++;

    for (i = 0;i < totalSegment; i++)
    {
        if (segIndex < 0)
        {
            SCCP_ERROR(("HandleAppDT1: Missing  segment reassem ie \n"));

            /* Outgoing Message - Discarding Message - Missing 
             Mandatory Parameter. */

            return (ITS_EMISSMAND);
        }

/*        if (dataLen < (SCCP_MAX_DATA + (i * SCCP_MAX_DATA)))
        {
            ies[dataIndex].param_length = dataLen - (i * SCCP_MAX_DATA);

            memcpy(ies[dataIndex].param_data.userData.data, 
                   &(data[i * SCCP_MAX_DATA]), dataLen - (i * SCCP_MAX_DATA));
        }
        else if (dataLen == i * SCCP_MAX_DATA)
        {
            return ITS_SUCCESS;
        }
        else
        {
            ies[dataIndex].param_length = SCCP_MAX_DATA;

            memcpy(ies[dataIndex].param_data.userData.data, 
                   &(data[i * SCCP_MAX_DATA]), SCCP_MAX_SEG_DATA);
        }*/

        ies[segIndex].param_id = SCCP_PRM_SEGMENT_REASSEM; 

        if(i == (totalSegment - 1))
        {
            ies[dataIndex].param_length = dataLen % SCCP_MAX_DATA;

            memcpy(ies[dataIndex].param_data.userData.data,
                   &(data[i * SCCP_MAX_DATA]), dataLen % SCCP_MAX_DATA);

            /* last segment */
            ies[segIndex].param_data.segmentingReassembly.seg_res = 
                                                        SCCP_SR_END_OF_DATA;
        }
        else
        {
            ies[dataIndex].param_length = SCCP_MAX_DATA;

            memcpy(ies[dataIndex].param_data.userData.data,
                   &(data[i * SCCP_MAX_DATA]), SCCP_MAX_DATA);

            ies[segIndex].param_data.segmentingReassembly.seg_res = 
                                                          SCCP_SR_MORE_DATA;
        }

        if (gcsMessageBasedRedundancyIsActive)
        {
            ITS_EVENT dummyEvent;
            ITS_UINT  dest;

            SCCP_DEBUG(("GCS Message Based Redundancy is ACTIVE\n"));

            dummyEvent.src  = ITS_GCS_EVENT_TO_NETWORK;
            dummyEvent.data = 0;

            dest = ROUTE_SelectApplication(hdr, &dummyEvent, ITS_TRUE);

            if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
            {
                /* Don't send message for routing to the network */
                SCCP_WARNING(("Message is consumed by SCCP: ctxt = 0x%x\n",
                              hdr->context.conref));

                continue;
            }

        }

        SCCP_DEBUG(("Sending message to Network: ctxt = 0x%x  $$$\n",
                     hdr->context.conref));

        ret = SCRCHandleSCOCMsg_PRC(mtp3, SCCP_MSG_DT1, ies, 
                                      ieCount, cdp);

        /* Q752 Implementation */
        if (SCCP_DecodeAddr(cdp, &ai, &pc, &ssn, NULL, NULL) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleSCOCMsg:  Couldn't decode addr\n"));
 
            return (ITS_EINVALIDARGS);
        }

             /* Increment SSN Peg for DT1 Sent */
                SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].ssn = ssn;
                SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].DT1SentPerSourceSSN++;

        if (ret != ITS_SUCCESS)
        {
            return ret;
        }
    }

    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT, 
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleAppDT1: DSM unable to free Reference.\n"));

        /* Unable to Commit Session Context to CTXT Table. */
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    return ret;
}

static int
HandleDownDT1(ITS_HDR* hdr, MTP3_HEADER* mtp3,
              ITS_SCCP_IE* ies, int ieCount, ITS_BOOLEAN* sendToApp)
{
    SCCP_CONN_CTXT *foundCtxt, *foundCtxt2;
    ITS_INT dlref;
    SCCP_REF_NUM *dl = NULL;
    ITS_CTXT        tempAssocRef;
    ITS_BOOLEAN     tempIsIntermediate;
    int i, error;
    int segIndex = -1;
    int dataIndex = -1;
    ITS_OCTET   dataLen;
    ITS_OCTET   data[SCCP_MAX_DATA];
    int         ret;
    /*Used for sending Error Ntfy to App*/
    int         errormsgid = 0;

    //Q752
    SCCP_ADDR cdp;
    ITS_OCTET ssn, ai;
    ITS_UINT pc;

    SCCP_DEBUG(("HandleDownDT1\n"));

    PEG_IncrPeg(PRC_SCCP_Pegs, PEG_SCCP_REMOTE_DT1_RCVD);

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_DEST_LOCAL_REF)
        {
            dl = &ies[i].param_data.destinationLocalReference;
            errormsgid = i;
        }
        if (ies[i].param_id == SCCP_PRM_SEGMENT_REASSEM)
        {
            segIndex = i;
        }
        if (ies[i].param_id == SCCP_PRM_DATA)
        {
            dataIndex = i;
        }
    }

    if (dataIndex < 0)
    {
        SCCP_ERROR(("HandleAppDT1: Missing data \n"));

        /* Outgoing Message - Discarding Message - Missing Mandatory 
          Parameter. */

        return (ITS_EMISSMAND);
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleDownDT1: Missing destination reference number \n"));

        /*Q752 Implementation Syntax Error Detected Value Error */
        SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++;

        /* Incoming Message - Discarding Message - Missing Mandatory 
           Parameter. */

        return (ITS_EMISSMAND);
    }
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[0] != 0)
    {
        SCCP_DEBUG(("HandleDownDT1:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif

    dlref = RN_GET_REF_NUM(*dl); 
    hdr->context.conref = (ITS_CTXT)dlref;

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT, 
                                           (ITS_OCTET *)&hdr->context.conref, 
                                           sizeof(hdr->context.conref), &error);

    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("HandleDownDT1: Couldn't acquire mutex.\n"));

                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleDownDT1: DSM Row Locked.\n"));

                break;
            case (ITS_ENOTFOUND):
                SCCP_WARNING(("HandleDownDT1: Can't find ConnectionReference"
                              " in table.\n"));

                SCCP_ERROR(("HandleDownDT1:DT1 received with un assigned DLR"
                            "hence the message is discarded\n"));

                break;
        }

        return (ITS_ENOCONN);
    }

    //Q752
    cdp = foundCtxt->daddr;
 
    /* Q752 Implementation */
        if (SCCP_DecodeAddr(&cdp, &ai, &pc, &ssn, NULL, NULL) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleSCOCMsg:  Couldn't decode addr\n"));
 
            return (ITS_EINVALIDARGS);
        }
 
 
        /* Increment SSN Peg for DT1 Sent */
           SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].ssn = ssn;
           SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].DT1RcvdPerSinkSSN++;

    if (MTP3_RL_GET_DPC_VALUE(foundCtxt->outLabel.label)!=
        MTP3_RL_GET_OPC_VALUE(mtp3->label))
    {
        SCCP_ERROR(("HandleDT1:Orignating Point Code received not equal to\
                     the Pc stored locally hence the msg is discarded\n"));

        return(ITS_EINVALIDARGS);
    }

    if (foundCtxt->pclass != SCCP_PCLASS_2)
    {
        SCCP_ERROR(("HandleDownDT1: DT1 is invalid for protocol class.\n"));
        SCCP_Alarm_PRC(673, __FILE__, __LINE__, "family=%s:pclass=%x",
                       "PRC", foundCtxt->pclass);

        /* Incoming Message - Discarding Message - Message Type not valid for 
           Protocol Class of Connection. */

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownDT1: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EINVALIDARGS);
    }
    if(foundCtxt->state == SCCP_CONN_OUT_PEND)
    {
        SCCP_DEBUG(("HandleDownDT1:DT1 received in outgoing connection"
                    " pending state\n"));    
        SCCP_Alarm_PRC(661, __FILE__, __LINE__, "family=%s", "PRC");

#if defined(CONNECTION_TIMERS)
        if (foundCtxt->connectTimer)
        {
            SCCP_DEBUG(("HandleDownDT1:Connect timer is killed\n"));

            TIMERS_CancelTimer(foundCtxt->connectTimer);
        }
#endif

        /*Release the DSM lock */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownDT1: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        foundCtxt = NULL;

        SCCP_DEBUG(("HandleDownDT1:Notification is sent to app and"
                    " resources are cleared\n"));

        NotifyERRToApp(hdr->context.conref, mtp3, ies, errormsgid,
                       SCCP_ERR_UNQUAL);

        *sendToApp = ITS_FALSE;

         return(ITS_EBADSTATE); 
    }
    if (foundCtxt->state == SCCP_IN_RELEASE_PEND)
    {
        SCCP_DEBUG(("HandleDownDT1:DT1 received in incoming"
                    " Release Pending state\n" ));
        SCCP_Alarm_PRC(661, __FILE__, __LINE__, "family=%s", "PRC");

        
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownDT1: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        SCCP_DEBUG(("HandleDownDT1:Notification for RLSD is sent to app and"
                    " RLSD is sent to remote\n"));

        SendRLSD(foundCtxt, SCCP_RLC_INCONSISTENT_DATA , ITS_FALSE);

        /*Used for sending notification to application*/  
         errormsgid++;

        RN_SET_REF_NUM(ies[errormsgid].param_data.sourceLocalReference,
                       foundCtxt->slref);
        errormsgid--;

        NotifyRLSDToApp(hdr->context.conref, mtp3, ies, errormsgid,
                       SCCP_RLC_INCONSISTENT_DATA);

        foundCtxt = NULL;

        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);
    }

    if (foundCtxt->state != SCCP_DATA_TRANSFER)
    {
        SCCP_ERROR(("HandleDownDT1: DT1 is invalid for connection state.\n"));
        /* Incoming Message - Message Type not valid for State of Connection. */
        SCCP_Alarm_PRC(661, __FILE__, __LINE__, "family=%s", "PRC");

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownDT1: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EBADSTATE);
    }

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->receiveInactivity)
    {
        TIMERS_CancelTimer(foundCtxt->receiveInactivity);
    }

    foundCtxt->receiveInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                     SCCP_T_iar),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
#endif
 
    /*Save these fields so can use after release lock on row */
    tempAssocRef = foundCtxt->assocRef;
    tempIsIntermediate = foundCtxt->isIntermediate;
    
    if (tempIsIntermediate)
    {
        *sendToApp = ITS_FALSE;

        foundCtxt2 = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                                DSM_TABLE_ITU_SCCP_CTXT, 
                                                (ITS_OCTET *)&tempAssocRef, 
                                                sizeof(tempAssocRef), &error);

        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
                case (ITS_EBADMUTEX):
                    SCCP_ERROR(("HandleDownDT1: Couldn't acquire mutex.\n"));

                    break;
                case (ITS_EINUSE):
                    SCCP_ERROR(("HandleDownDT1: DSM Row Locked.\n"));

                    break;
                case (ITS_ENOTFOUND):
                    SCCP_WARNING(("HandleDownDT1: Can't find Connection"
                                  "Reference in table.\n"));

                    break;
            }

            return (ITS_ENOCONN);
        }

        RN_SET_REF_NUM(*dl, foundCtxt2->dlref);

        *mtp3 = foundCtxt2->outLabel;

        hdr->context.conref = foundCtxt2->slref;

        ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[ieCount].param_length = sizeof(MTP3_HEADER);
        ies[ieCount].param_data.routingLabel = foundCtxt2->outLabel;
        ieCount++;

         /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&tempAssocRef, 
                           sizeof(tempAssocRef), foundCtxt2);

        foundCtxt2 = NULL;    /* Not safe to use with out lock */

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownDT1: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }
    }
    else
    {
        if (segIndex < 0)
        {
            SCCP_ERROR(("HandleDownDT1: Missing segment ie \n"));

            PEG_IncrPeg(PRC_SCCP_Pegs, PEG_SCCP_REMOTE_REASSEMBLE_ERR);

            /*Q752 Implementation Reassembly Error Reassembly Failed */
            SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.reassemblyErrReassemblyFailed++;

            return (ITS_EMISSMAND);
        }

        if (ies[segIndex].param_data.segmentingReassembly.seg_res == 
                                                          SCCP_SR_MORE_DATA)
        {

            /* If total length of all fragments exceeds LONG_DATA_MAX
             * should not happen usually*/
            if (ies[dataIndex].param_length + foundCtxt->totalDataLen >
                                                            SCCP_LONG_DATA_MAX)
            {
                dataLen = ies[dataIndex].param_length;

                memcpy(data, ies[dataIndex].param_data.userData.data, 
                       dataLen);

                if (foundCtxt->totalDataLen >= SCCP_MAX_DATA)
                {
                    ies[dataIndex].param_id = SCCP_PRM_LONG_DATA;
                    ies[dataIndex].param_data.longData.len = 
                                                      foundCtxt->totalDataLen;

                    SCOC_GetDataFromFragList(ies[dataIndex].param_data.
                                     longData.data, &(foundCtxt->startFragKey));

                    foundCtxt->startFragKey = 0;
                }
                else
                {
                    ies[dataIndex].param_id = SCCP_PRM_DATA;
                    ies[dataIndex].param_length = foundCtxt->totalDataLen;

                    SCOC_GetDataFromFragList(ies[dataIndex].param_data.userData.
                                      data, &(foundCtxt->startFragKey));

                    foundCtxt->startFragKey = 0;
                }

                foundCtxt->totalDataLen = dataLen;

                ret = SCOC_PutDataInFragList(&(foundCtxt->startFragKey), 
                                        foundCtxt->slref, data, dataLen);

                if(ret != ITS_SUCCESS)
                {
                    SCCP_ERROR(("SCOC_PutDataInFragList Failed \n"));
                }
            }
            else
            {
                ret = SCOC_PutDataInFragList(&(foundCtxt->startFragKey), 
                                        foundCtxt->slref,
                                        ies[dataIndex].param_data.userData.data,
                                        ies[dataIndex].param_length);

                if(ret != ITS_SUCCESS)
                {
                    SCCP_ERROR(("SCOC_PutDataInFragList Failed \n"));
                }

                foundCtxt->totalDataLen += ies[dataIndex].param_length;

                *sendToApp = ITS_FALSE;

                error = DSM_Commit(DSM_SccpFtGroupId,
                                   DSM_TABLE_ITU_SCCP_CTXT, 
                                   (ITS_OCTET *)&hdr->context.conref, 
                                   sizeof(hdr->context.conref), foundCtxt);

                if (error != ITS_SUCCESS)
                {
                    SCCP_ERROR(("HandleDownDT1: DSM unable to "
                                "free Reference.\n"));

                    /* Unable to Commit Session Context to CTXT Table. */
                }

                return ITS_SUCCESS;
            }
        }
        else
        {
            if (ies[dataIndex].param_length + foundCtxt->totalDataLen >
                                                            SCCP_LONG_DATA_MAX)
            {
                dataLen = ies[dataIndex].param_length;
                memcpy(data, ies[dataIndex].param_data.userData.data, 
                       dataLen);

                if (foundCtxt->totalDataLen >= SCCP_MAX_DATA)
                {
                    ies[dataIndex].param_id = SCCP_PRM_LONG_DATA;
                    ies[dataIndex].param_data.longData.len = 
                                                      foundCtxt->totalDataLen;

                    SCOC_GetDataFromFragList(ies[dataIndex].param_data.longData.
                                     data, &(foundCtxt->startFragKey));

                    foundCtxt->startFragKey = 0;
                }
                else
                {
                    ies[dataIndex].param_id = SCCP_PRM_DATA;
                    ies[dataIndex].param_length = foundCtxt->totalDataLen;

                    SCOC_GetDataFromFragList(ies[dataIndex].param_data.userData.
                                      data, &(foundCtxt->startFragKey));

                    foundCtxt->startFragKey = 0;

                }

                foundCtxt->totalDataLen = dataLen;

                ret = SCOC_PutDataInFragList(&(foundCtxt->startFragKey), 
                                        foundCtxt->slref, 
                                        data, dataLen);

                if(ret != ITS_SUCCESS)
                {
                    SCCP_ERROR(("SCOC_PutDataInFragList Failed \n"));
                }

                ies[segIndex].param_data.segmentingReassembly.seg_res = 
                                                             SCCP_SR_MORE_DATA;
            }
            else
            {
                ret = SCOC_PutDataInFragList(&(foundCtxt->startFragKey), 
                                        foundCtxt->slref, 
                                        ies[dataIndex].param_data.userData.data,
                                        ies[dataIndex].param_length);

                if(ret != ITS_SUCCESS)
                {
                    SCCP_ERROR(("SCOC_PutDataInFragList Failed \n"));
                }

                foundCtxt->totalDataLen += ies[dataIndex].param_length;

                if(foundCtxt->totalDataLen >= SCCP_MAX_DATA)
                {
                    ies[dataIndex].param_id = SCCP_PRM_LONG_DATA;
                    ies[dataIndex].param_data.longData.len = 
                                                      foundCtxt->totalDataLen;

                    SCOC_GetDataFromFragList(ies[dataIndex].param_data.longData.
                                        data, &(foundCtxt->startFragKey));
                }
                else
                {
                    ies[dataIndex].param_id = SCCP_PRM_DATA;
                    ies[dataIndex].param_length = foundCtxt->totalDataLen;

                    SCOC_GetDataFromFragList(ies[dataIndex].param_data.userData.
                                        data, &(foundCtxt->startFragKey));
                }

                foundCtxt->startFragKey = 0;
                foundCtxt->totalDataLen = 0;
            }
        }
    }
            
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT, 
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownDT1: DSM unable to free Reference.\n"));

        /* Unable to Commit Session Context to CTXT Table. */
    } 

    if (!*sendToApp)
    {
        return HandleAppDT1(hdr, mtp3, ies, ieCount);
    }

    return (ITS_SUCCESS);
}

/*
 * send DT2
 */
static int
HandleAppDT2(ITS_HDR* hdr, MTP3_HEADER* mtp3,
             ITS_SCCP_IE* ies, int ieCount)
{
    SCCP_CONN_CTXT *foundCtxt;
    SCCP_REF_NUM *dl = NULL;
    SCCP_ADDR local, *cdp = &local;
    int i, error;

    //Q752
    ITS_OCTET ssn, ai;
    ITS_UINT pc;

    SCCP_DEBUG(("HandleAppDT2\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_DEST_LOCAL_REF)
        {
            dl = &ies[i].param_data.destinationLocalReference;
            break;
        }
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleAppDT2: Missing destination reference number \n"));

        /*Q752 Implementation Syntax Error Detected Construction Error */
        SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.syntaxConstructionErrDetected++;

        /* Discarding Outgoing Message - Missing Mandatory Parameter. */

        return (ITS_EMISSMAND);
    }

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("HandleAppDT2: Couldn't acquire mutex.\n"));

                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleAppDT2: DSM Row Locked.\n"));

                break;
            case (ITS_ENOTFOUND):
                SCCP_WARNING(("HandleAppDT2: Can't find ConnectionReference"
                              " in table.\n"));

                break;
        }

        return (ITS_ENOCONN);
      }

    if (foundCtxt->pclass != SCCP_PCLASS_3)
    {
        SCCP_ERROR(("HandleAppDT2: DT2 is invalid for protocol class.\n"));

        /* Discarding Outgoing Message - Message Type not valid for Protocol Class of Connection. */
         SCCP_Alarm_PRC(674, __FILE__, __LINE__, "family=%s:pclass=%x",
                        "PRC", foundCtxt->pclass);


        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppDT2: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EINVALIDARGS);
    }

    if (foundCtxt->state != SCCP_DATA_TRANSFER)
    {
        SCCP_ERROR(("HandleAppDT2: DT2 is invalid for connection state.\n"));
        /* Outgoing Message - Message Type not valid for State of Connection. */
        SCCP_Alarm_PRC(662, __FILE__, __LINE__, "family=%s", "PRC");

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppDT2: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EBADSTATE);
    }

    *mtp3 = foundCtxt->outLabel;

    local = foundCtxt->daddr;

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->sendInactivity)
    {
        TIMERS_CancelTimer(foundCtxt->sendInactivity);
    }
    foundCtxt->sendInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                     SCCP_T_ias),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
#endif
    
    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleAppDT2: DSM unable to free Reference.\n"));

        /* Unable to Commit Session Context to CTXT Table. */
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (gcsMessageBasedRedundancyIsActive)
    {
        ITS_EVENT dummyEvent;
        ITS_UINT  dest;

        SCCP_DEBUG(("GCS Message Based Redundancy is ACTIVE\n"));

        dummyEvent.src  = ITS_GCS_EVENT_TO_NETWORK;
        dummyEvent.data = 0;

        dest = ROUTE_SelectApplication(hdr, &dummyEvent, ITS_TRUE);

        if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
        {
            /* Don't send message for routing to the network */
            SCCP_WARNING(("Message is consumed by SCCP: ctxt = 0x%x\n",
                          hdr->context.conref));
            return ITS_SUCCESS;
        }

    }

    SCCP_DEBUG(("Sending message to Network: ctxt = 0x%x  $$$\n",
                 hdr->context.conref));

    /* Q752 Implementation */
    if (SCCP_DecodeAddr(cdp, &ai, &pc, &ssn, NULL, NULL) != ITS_SUCCESS)
    {
        SCCP_ERROR(("SCRCHandleSCOCMsg:  Couldn't decode addr\n"));
 
        return (ITS_EINVALIDARGS);
    }
             
    /* Increment SSN Peg for DT2 Sent */
    SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].ssn = ssn;
    SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].DT2SentPerSourceSSN++;

    return SCRCHandleSCOCMsg_PRC(mtp3, SCCP_MSG_DT2, ies, ieCount, cdp);
}


static int
HandleDownDT2(ITS_HDR* hdr, MTP3_HEADER* mtp3,
              ITS_SCCP_IE* ies, int ieCount, ITS_BOOLEAN* sendToApp)
{
    SCCP_CONN_CTXT *foundCtxt, *foundCtxt2;
    ITS_INT dlref;
    SCCP_REF_NUM *dl = NULL;
    ITS_CTXT        tempAssocRef;
    ITS_BOOLEAN     tempIsIntermediate;
    int i, error;
    int releaseID = 0;
    ITS_EVENT event;
    ITS_HDR hdrntfy;

    //Q752
    SCCP_ADDR cdp;
    ITS_OCTET ssn, ai;
    ITS_UINT pc;

    /* Holds the reference of Previous P(S).*/
    static ITS_OCTET prevSentSeqID = 0;
    int improperDataSeq = 0;

    SCCP_DEBUG(("HandleDownDT2\n"));

    PEG_IncrPeg(PRC_SCCP_Pegs, PEG_SCCP_REMOTE_DT2_RCVD);

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
            case SCCP_PRM_DEST_LOCAL_REF:
                dl = &ies[i].param_data.destinationLocalReference;
                releaseID = i;
                break;

            case SCCP_PRM_SEQUENCE_SEGMENT:

                if (prevSentSeqID!=0)
                {
                    if ( prevSentSeqID == 
                        ((ies[i].param_data.sequenceSegment.tsn & 0xFE)>>1))
                    {
                        prevSentSeqID++;
                        SCCP_DEBUG (("HandleDownDT2:Sequence number in DT2 is"
                                     " correct\n"));
                    }
                
                    else
                    {
                        SCCP_DEBUG(("HandleDownDT2:Mismatch in P(S)\n"));

                        improperDataSeq = 1;
                    }

                }
                else
                {
                    SCCP_DEBUG(("HandleDownDT2:Prev sequence id is assigned"
                                "\n"));

                    prevSentSeqID =
                            (ies[i].param_data.sequenceSegment.tsn & 0xFE)>>1;

                    prevSentSeqID++;
                }
                break;
        }

        if (improperDataSeq == 1)
        {
            prevSentSeqID = 0;
            break;
        }
         
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleDownDT2: Missing destination reference number \n"));

        /*Q752 Implementation Syntax Error Detected Value Error */
        SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++;

       /* Incoming Message - Discarding Message - Missing Mandatory Parameter */

        return (ITS_EMISSMAND);
    }
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[0] != 0)
    {
        SCCP_DEBUG(("HandleDownDT2:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif

    dlref = RN_GET_REF_NUM(*dl); 
    hdr->context.conref = (ITS_CTXT)dlref;

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);

    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("HandleDownDT2: Couldn't acquire mutex.\n"));

                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleDownDT2: DSM Row Locked.\n"));

                break;
            case (ITS_ENOTFOUND):
                SCCP_WARNING(("HandleDownDT2: Can't find ConnectionReference"
                              " in table.\n"));

                SCCP_ERROR(("HandleDownDT2:DT2 received with unassigned DLR"
                            " hence the message is discarded\n"));

                break;
        }

        return (ITS_ENOCONN);
    }

    //Q752
    cdp = foundCtxt->daddr;
 
    /* Q752 Implementation */
        if (SCCP_DecodeAddr(&cdp, &ai, &pc, &ssn, NULL, NULL) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleSCOCMsg:  Couldn't decode addr\n"));
 
            return (ITS_EINVALIDARGS);
        }
 
 
        /* Increment SSN Peg for DT1 Sent */
           SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].ssn = ssn;
           SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].DT2RcvdPerSinkSSN++;

    if (MTP3_RL_GET_DPC_VALUE(foundCtxt->outLabel.label)!=
        MTP3_RL_GET_OPC_VALUE(mtp3->label))
    {
        SCCP_ERROR(("HandleDownDT2:Orignating Point Code received not equal to\
                     the Pc stored locally hence the msg is discarded\n"));

        return(ITS_EINVALIDARGS);
    }

    if (foundCtxt->pclass != SCCP_PCLASS_3)
    {
        SCCP_ERROR(("HandleDownDT2: DT2 is invalid for protocol class.\n"));
        /* Incoming Message - Discarding Message - Message Type not valid for 
           Protocol Class of Connection. */

        SCCP_Alarm_PRC(675, __FILE__, __LINE__, "family=%s:pclass=%x",
                       "PRC", foundCtxt->pclass);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownDT2: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EINVALIDARGS);
    }

    if  (foundCtxt->state == SCCP_CONN_OUT_PEND)
    {
        SCCP_DEBUG(("HandleDownDT2:DT2 received in Invalid state\n"));
        SCCP_Alarm_PRC(663, __FILE__, __LINE__, "family=%s", "PRC");

#if defined(CONNECTION_TIMERS)
        if (foundCtxt->connectTimer)
        {
            SCCP_DEBUG(("HandleDownDT2:Connect timer is killed\n"));

            TIMERS_CancelTimer(foundCtxt->connectTimer);
        }
#endif
        /*Release the DSM lock */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownDT2: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }
        foundCtxt = NULL;

        SCCP_DEBUG(("HandleDownDT2:Notification is sent to app and"
                    " resources are cleared\n"));

        NotifyERRToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_ERR_UNQUAL);

        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);
    }
    else if (foundCtxt->state == SCCP_IN_RESET_PEND)
    {
        SCCP_DEBUG(("HandleDownDT2:DT2 received in Reset pending state\n")); 
        SCCP_Alarm_PRC(663, __FILE__, __LINE__, "family=%s", "PRC");

        *sendToApp = ITS_FALSE;
        ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[ieCount].param_length = sizeof(MTP3_HEADER);
        ies[ieCount].param_data.routingLabel = *mtp3;

        ieCount++;

        hdrntfy.type = ITS_SCCP;
        event.src = ITS_SCCP_SRC;
        hdrntfy.context.conref = hdr->context.conref;

        SCCP_DEBUG(("HandleDownDT2:Ntfy for DT2 is send to application\n")); 


        if (SCCP_Encode(ies, ieCount, SCCP_MSG_DT2, &event, &hdrntfy,
                              &SCCP_DT2_Desc)!=ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownDT2:Error in encoding DT2  message\n"));

            return (ITS_ENOMSG);
        }

        ITS_SET_CTXT(&event.data[1], hdrntfy.context.conref);

        /* send to the application */
        if (SCCP_SendToAPP(mtp3, &hdrntfy, SCCP_MSG_DT2, &event)!=ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownDT2:Error while sending to Application."));
        }

        SCCP_DEBUG(("HandleDownDT2:RSR is sent to the remote end\n"));
        
        RN_SET_REF_NUM(ies[releaseID].param_data.destinationLocalReference,
                       foundCtxt->dlref);
        releaseID++;

        ies[releaseID].param_id = SCCP_PRM_SRC_LOCAL_REF;
        ies[releaseID].param_length = sizeof(SCCP_REF_NUM);
        RN_SET_REF_NUM(ies[releaseID].param_data.sourceLocalReference,
                       foundCtxt->slref);
        releaseID++;

        ies[releaseID].param_id = SCCP_PRM_RESET_CAUSE;
        ies[releaseID].param_length = sizeof(SCCP_RES_CAUSE);
        ies[releaseID].param_data.resetCause.cause =SCCP_RES_NETWORK_OP;

        releaseID++;

        ieCount = releaseID;

#if defined(CONNECTION_TIMERS)

        if (foundCtxt->receiveInactivity)
        {
            SCCP_DEBUG(("HandleDownDT2:Receive inactivity timer is killed\n"));
            TIMERS_CancelTimer(foundCtxt->receiveInactivity);
        }

        foundCtxt->receiveInactivity =
            TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                    TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                          SCCP_T_iar),
                                            foundCtxt, sizeof(SCCP_CONN_CTXT));

        SCCP_DEBUG(("HandleDownDT2:Receive inactivity timer is restarted\n"));
#endif

        error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownDT2: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        if (HandleAppRSR(hdr, mtp3, ies, ieCount)!= ITS_SUCCESS)
        {
            SCCP_DEBUG(("HandleDownDT2:Error occured  while sending RSR\n"));

        }
        return (ITS_EBADSTATE);
    }
    if (foundCtxt->state == SCCP_IN_RELEASE_PEND)
    {
        SCCP_DEBUG(("HandleDownDT2:DT1 received in incoming"
                     " Release Pending state\n" ));
        SCCP_Alarm_PRC(663, __FILE__, __LINE__, "family=%s", "PRC");
        
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownDT2: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        SCCP_DEBUG(("HandleDownDT2:Notification for RLSD is sent to app and"
                    " RLSD is sent to remote\n"));

        SendRLSD(foundCtxt, SCCP_RLC_INCONSISTENT_DATA , ITS_FALSE);
      
        releaseID++;

        RN_SET_REF_NUM(ies[releaseID].param_data.sourceLocalReference,
                       foundCtxt->slref);
        releaseID--;

        NotifyRLSDToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_RLC_INCONSISTENT_DATA);

        foundCtxt = NULL;

        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);
    }

    if (foundCtxt->state != SCCP_DATA_TRANSFER)
    {
        SCCP_ERROR(("HandleDownDT2: DT2 is invalid for connection state.\n"));
        /* Incoming Message - Message Type not valid for State of Connection. */
        SCCP_Alarm_PRC(663, __FILE__, __LINE__, "family=%s", "PRC");

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownDT2: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */

        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EBADSTATE);
    }

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->receiveInactivity)
    {
        TIMERS_CancelTimer(foundCtxt->receiveInactivity);
    }

    foundCtxt->receiveInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                     SCCP_T_iar),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
#endif
 
    /*Save these fields so can use after release lock on row */
    tempAssocRef = foundCtxt->assocRef;
    tempIsIntermediate = foundCtxt->isIntermediate;

    if (improperDataSeq == 1)
    {
        if (foundCtxt->sequenceOn == ITS_TRUE)
        {
            SCCP_DEBUG(("HandleDownDT2:Sequence is on for the Connection\
                         context.\n"));
            /* The value of i is of Seq/segment  hence i is decremented */
            i--;

            RN_SET_REF_NUM(ies[i].param_data.destinationLocalReference,
                       foundCtxt->dlref);
            i++;
            ies[i].param_id = SCCP_PRM_SRC_LOCAL_REF;
            ies[i].param_length = sizeof(SCCP_REF_NUM);

            RN_SET_REF_NUM(ies[i].param_data.sourceLocalReference,
                           foundCtxt->slref);

            i++;

            ies[i].param_id = SCCP_PRM_RESET_CAUSE;
            ies[i].param_length = sizeof(SCCP_RES_CAUSE);
            ies[i].param_data.resetCause.cause =SCCP_RES_NETWORK_OP;

            i++;

            ieCount = i;

            SCCP_DEBUG(("HandleDownDT2:RSR is send to the remote end\n"));

            error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);
            if (error != ITS_SUCCESS)
            {
                SCCP_ERROR(("HandleDownDT2: DSM unable to free Reference.\n"));

                /* Unable to Commit Session Context to CTXT Table. */
            }

            return HandleAppRSR(hdr, mtp3, ies, ieCount);
        }
        else
        {
            SCCP_DEBUG(("HandleDownDT2:Sequence is not on for the connection\
                       context.Sequence id is updated for  the connection\n"));
            prevSentSeqID++;
        }
    }

    foundCtxt->sequenceOn = ITS_TRUE;

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownDT2: DSM unable to free Reference.\n"));

        /* Unable to Commit Session Context to CTXT Table. */
    }
    
    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (tempIsIntermediate)
    {
        *sendToApp = ITS_FALSE;

        foundCtxt2 = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                                DSM_TABLE_ITU_SCCP_CTXT, 
                                                (ITS_OCTET *)&tempAssocRef, 
                                                sizeof(tempAssocRef), &error);

        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
                case (ITS_EBADMUTEX):
                    SCCP_ERROR(("HandleDownDT2: Couldn't acquire mutex.\n"));

                    break;
                case (ITS_EINUSE):
                    SCCP_ERROR(("HandleDownDT2: DSM Row Locked.\n"));

                    break;
                case (ITS_ENOTFOUND):
                    SCCP_WARNING(("HandleDownDT2: Can't find Connection"
                                  "Reference in table.\n"));

                    break;
            }

            return (ITS_ENOCONN);
        }

        RN_SET_REF_NUM(*dl, foundCtxt2->dlref);

        *mtp3 = foundCtxt2->outLabel;

        hdr->context.conref = foundCtxt2->slref;

        ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[ieCount].param_length = sizeof(MTP3_HEADER);
        ies[ieCount].param_data.routingLabel = foundCtxt2->outLabel;
        ieCount++;

         /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&tempAssocRef, 
                           sizeof(tempAssocRef), foundCtxt2);

        foundCtxt2 = NULL;    /* Not safe to use with out lock */

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownDT2: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }
    }

    if (!*sendToApp)
    {
        return HandleAppDT2(hdr, mtp3, ies, ieCount);
    }

    return (ITS_SUCCESS);
}

/*
 * send AK
 */
static int
HandleAppAK(ITS_HDR* hdr, MTP3_HEADER* mtp3,
            ITS_SCCP_IE* ies, int ieCount)
{
    SCCP_CONN_CTXT *foundCtxt;
    SCCP_REF_NUM *dl = NULL;
    SCCP_ADDR local, *cdp = &local;
    int i, error;

    SCCP_DEBUG(("HandleAppAK\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_DEST_LOCAL_REF)
        {
            dl = &ies[i].param_data.destinationLocalReference;
            break;
        }
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleAppAK: Missing destination reference number \n"));

        /* Outgoing Message - Discarding Message - Missing Mandatory 
           Parameter. */

        return (ITS_EMISSMAND);
    }

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);

    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("HandleAppAK: Couldn't acquire mutex.\n"));

                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleAppAK: DSM Row Locked.\n"));

                break;
            case (ITS_ENOTFOUND):
                SCCP_WARNING(("HandleAppAK: Can't find ConnectionReference"
                              " in table.\n"));

                break;
        }

        return (ITS_ENOCONN);
    }

    if (foundCtxt->pclass != SCCP_PCLASS_3)
    {
        SCCP_ERROR(("HandleAppAK: AK is invalid for protocol class.\n"));
        /* Outgoing Message - Discarding Message - Message Type not valid for 
           Protocol Class of Connection. */

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppAK: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EINVALIDARGS);
    }

    if (foundCtxt->state != SCCP_DATA_TRANSFER)
    {
        SCCP_ERROR(("HandleAppAK: AK is invalid for connection state.\n"));
        SCCP_Alarm_PRC(664, __FILE__, __LINE__, "family=%s", "PRC");

        /* Outgoing Message - Message Type not valid for State of Connection. */

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppAK: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EBADSTATE);
    }

    *mtp3 = foundCtxt->outLabel;

    local = foundCtxt->daddr;

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->sendInactivity)
    {
        TIMERS_CancelTimer(foundCtxt->sendInactivity);
    }
    foundCtxt->sendInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                     SCCP_T_ias),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
#endif
    
    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleAppAK: DSM unable to free Reference.\n"));

        /* Unable to Commit Session Context to CTXT Table. */
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (gcsMessageBasedRedundancyIsActive)
    {
        ITS_EVENT dummyEvent;
        ITS_UINT  dest;

        SCCP_DEBUG(("GCS Message Based Redundancy is ACTIVE\n"));

        dummyEvent.src  = ITS_GCS_EVENT_TO_NETWORK;
        dummyEvent.data = 0;

        dest = ROUTE_SelectApplication(hdr, &dummyEvent, ITS_TRUE);

        if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
        {
            /* Don't send message for routing to the network */
            SCCP_WARNING(("Message is consumed by SCCP: ctxt = 0x%x\n",
                          hdr->context.conref));
            return ITS_SUCCESS;
        }

    }

    SCCP_DEBUG(("Sending message to Network: ctxt = 0x%x  $$$\n",
                 hdr->context.conref));


    return SCRCHandleSCOCMsg_PRC(mtp3, SCCP_MSG_AK, ies, ieCount, cdp);
}

static int
HandleDownAK(ITS_HDR* hdr, MTP3_HEADER* mtp3,
             ITS_SCCP_IE* ies, int ieCount, ITS_BOOLEAN* sendToApp)
{
    SCCP_CONN_CTXT *foundCtxt, *foundCtxt2;
    ITS_INT dlref;
    SCCP_REF_NUM *dl = NULL;
    ITS_CTXT        tempAssocRef;
    ITS_BOOLEAN     tempIsIntermediate;
    int i, error;
    int errormsgid = 0;

    SCCP_DEBUG(("HandleDownAK\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_DEST_LOCAL_REF)
        {
            dl = &ies[i].param_data.destinationLocalReference;
            errormsgid = i;
            break;
        }
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleDownAK: Missing destination reference number \n"));
        
        /*Q752 Implementation Syntax Error Detected Value Error */ 
        SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++;

        /* Incoming Message - Discarding Message - Missing Mandatory 
           Parameter. */

        return (ITS_EMISSMAND);
    }
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[0] != 0)
    {
        SCCP_DEBUG(("HandleDownAK:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif

    dlref = RN_GET_REF_NUM(*dl); 
    hdr->context.conref = (ITS_CTXT)dlref;

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);

    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("HandleDownAK: Couldn't acquire mutex.\n"));

                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleDownAK: DSM Row Locked.\n"));

                break;
            case (ITS_ENOTFOUND):
                SCCP_WARNING(("HandleDownAK: Can't find ConnectionReference"
                              " in table.\n"));

                SCCP_ERROR(("HandleDownAK:AK received with unassigned DLR"
                            " hence the message is discarded\n"));

                break;
        }

        /* Incoming Message - Discarding Message - Message Type not valid for 
           Protocol Class of Connection.*/

        return (ITS_ENOCONN);
    }

    if (foundCtxt->pclass != SCCP_PCLASS_3)
    {
        SCCP_ERROR(("HandleDownAK: AK is invalid for protocol class.\n"));

        /*Q752 Implementation Syntax Error Detected Value Error */
        SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++;

        SCCP_Alarm_PRC(677, __FILE__, __LINE__, "family=%s:pclass=%x",
                       "PRC", foundCtxt->pclass);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownAK: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EINVALIDARGS);
    }
    if(foundCtxt->state == SCCP_CONN_OUT_PEND)
    {
        SCCP_DEBUG(("HandleDownAK:AK received in outgoing connection"
                    " pending state\n"));
        SCCP_Alarm_PRC(665, __FILE__, __LINE__, "family=%s", "PRC");

#if defined(CONNECTION_TIMERS)
        if (foundCtxt->connectTimer)
        {
            SCCP_DEBUG(("HandleDownACK:Connect timer is killed\n"));

            TIMERS_CancelTimer(foundCtxt->connectTimer);
        }
#endif
        /*Release the DSM lock */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownACK: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }
        foundCtxt = NULL;

        SCCP_DEBUG(("HandleDownACK:Notification is sent to app and"
                    " resources are cleared\n"));

        NotifyERRToApp(hdr->context.conref, mtp3, ies, errormsgid,
                       SCCP_ERR_UNQUAL);

        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);
    }
    if (foundCtxt->state == SCCP_IN_RELEASE_PEND)
    {
        SCCP_DEBUG(("HandleDownAK:AK received in incoming"
                    " Release Pending state\n" ));
        SCCP_Alarm_PRC(665, __FILE__, __LINE__, "family=%s", "PRC");

        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownAK: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        SCCP_DEBUG(("HandleDownAK:Notification for RLSD is sent to app and"
                    " RLSD is sent to remote\n"));

        SendRLSD(foundCtxt, SCCP_RLC_INCONSISTENT_DATA , ITS_FALSE);

        errormsgid++;

        RN_SET_REF_NUM(ies[errormsgid].param_data.sourceLocalReference,
                       foundCtxt->slref);
        errormsgid--;

        NotifyRLSDToApp(hdr->context.conref, mtp3, ies, errormsgid,
                       SCCP_RLC_INCONSISTENT_DATA);

        foundCtxt = NULL;

        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);
    }

    if (foundCtxt->state != SCCP_DATA_TRANSFER)
    {
        SCCP_ERROR(("HandleDownAK: AK is invalid for connection state.\n"));
        /* Incoming Message - Message Type not valid for State of Connection. */
        SCCP_Alarm_PRC(665, __FILE__, __LINE__, "family=%s", "PRC");

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownAK: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EBADSTATE);
    }

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->receiveInactivity)
    {
        TIMERS_CancelTimer(foundCtxt->receiveInactivity);
    }
    foundCtxt->receiveInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                     SCCP_T_iar),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
#endif
    
    /*Save these fields so can use after release lock on row */
    tempAssocRef = foundCtxt->assocRef;
    tempIsIntermediate = foundCtxt->isIntermediate;

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownAK: DSM unable to free Reference.\n"));

        /* Unable to Commit Session Context to CTXT Table. */
    }
    
    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (tempIsIntermediate)
    {
        *sendToApp = ITS_FALSE;

        foundCtxt2 = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                                DSM_TABLE_ITU_SCCP_CTXT, 
                                                (ITS_OCTET *)&tempAssocRef, 
                                                sizeof(tempAssocRef), &error);

        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
                case (ITS_EBADMUTEX):
                    SCCP_ERROR(("HandleDownAK: Couldn't acquire mutex.\n"));

                    break;
                case (ITS_EINUSE):
                    SCCP_ERROR(("HandleDownAK: DSM Row Locked.\n"));

                    break;
                case (ITS_ENOTFOUND):
                    SCCP_WARNING(("HandleDownAK: Can't find ConnectionReference" 
                                 "in table.\n"));

                    break;
            }

            return (ITS_ENOCONN);
        }

        RN_SET_REF_NUM(*dl, foundCtxt2->dlref);

        *mtp3 = foundCtxt2->outLabel;

        hdr->context.conref = foundCtxt2->slref;

        ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[ieCount].param_length = sizeof(MTP3_HEADER);
        ies[ieCount].param_data.routingLabel = foundCtxt2->outLabel;
        ieCount++;
        SCCP_Alarm_PRC(677, __FILE__, __LINE__, "family=%s:pclass=%x",
                       "PRC", foundCtxt->pclass);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&tempAssocRef, 
                           sizeof(tempAssocRef), foundCtxt2);

        foundCtxt2 = NULL;    /* Not safe to use with out lock */

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownAK: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }
    }

    if (!*sendToApp)
    {
        return HandleAppAK(hdr, mtp3, ies, ieCount);
    }

    return (ITS_SUCCESS);
}

/*
 * expedited data
 */
static int
HandleAppED(ITS_HDR* hdr, MTP3_HEADER* mtp3,
            ITS_SCCP_IE* ies, int ieCount)
{
    SCCP_CONN_CTXT *foundCtxt;
    SCCP_REF_NUM *dl = NULL;
    SCCP_ADDR local, *cdp = &local;
    int i, error;

    //Q752
    ITS_OCTET ssn, ai;
    ITS_UINT pc;

    SCCP_DEBUG(("HandleAppED\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_DEST_LOCAL_REF)
        {
            dl = &ies[i].param_data.destinationLocalReference;
            break;
        }
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleAppED: Missing destination reference number \n"));

        /*Q752 Implementation Syntax Error Detected Construction Error */
        SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.syntaxConstructionErrDetected++;

        /* Outgoing Message - Discarding Message - Missing Mandatory 
           Parameter. */

        return (ITS_EMISSMAND);
    }

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);

    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("HandleAppED: Couldn't acquire mutex.\n"));

                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleAppED: DSM Row Locked.\n"));

                break;
            case (ITS_ENOTFOUND):
                SCCP_WARNING(("HandleAppED: Can't find ConnectionReference"
                              " in table.\n"));
                break;
        }

        return (ITS_ENOCONN);
    }

    if (foundCtxt->pclass != SCCP_PCLASS_3)
    {
        SCCP_ERROR(("HandleAppED: ED is invalid for protocol class.\n"));
        /* Outgoing Message - Discarding Message - Message Type not valid for 
           Protocol Class of Connection. */
        SCCP_Alarm_PRC(678, __FILE__, __LINE__, "family=%s:pclass=%x",
                       "PRC", foundCtxt->pclass);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppED: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EINVALIDARGS);
    }

    if (foundCtxt->state != SCCP_DATA_TRANSFER)
    {
        SCCP_ERROR(("HandleAppED: ED is invalid for connection state.\n"));
        SCCP_Alarm_PRC(666, __FILE__, __LINE__, "family=%s", "PRC");

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppED: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EBADSTATE);
    }

    switch (foundCtxt->dataState)
    {
        case SCCP_DATA_NORMAL:
            foundCtxt->dataState = SCCP_DATA_OUT_ED;
            break;

        case SCCP_DATA_IN_ED:
            foundCtxt->dataState = SCCP_DATA_BOTH_ED;
            break;

        case SCCP_DATA_OUT_ED:
        case SCCP_DATA_BOTH_ED:
            break;
    }

    *mtp3 = foundCtxt->outLabel;

    local = foundCtxt->daddr;

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->sendInactivity)
    {
        TIMERS_CancelTimer(foundCtxt->sendInactivity);
    }

    foundCtxt->sendInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                     SCCP_T_ias),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
#endif

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref,
                       sizeof(hdr->context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleAppED: DSM unable to free Reference.\n"));

        /* Unable to Commit Session Context to CTXT Table. */
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (gcsMessageBasedRedundancyIsActive)
    {
        ITS_EVENT dummyEvent;
        ITS_UINT  dest;

        SCCP_DEBUG(("GCS Message Based Redundancy is ACTIVE\n"));

        dummyEvent.src  = ITS_GCS_EVENT_TO_NETWORK;
        dummyEvent.data = 0;

        dest = ROUTE_SelectApplication(hdr, &dummyEvent, ITS_TRUE);

        if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
        {
            /* Don't send message for routing to the network */
            SCCP_WARNING(("Message is consumed by SCCP: ctxt = 0x%x\n",
                          hdr->context.conref));
            return ITS_SUCCESS;
        }

    }

    SCCP_DEBUG(("Sending message to Network: ctxt = 0x%x  $$$\n",
                 hdr->context.conref));

    /* Q752 Implementation */
    if (SCCP_DecodeAddr(cdp, &ai, &pc, &ssn, NULL, NULL) != ITS_SUCCESS)
    {
        SCCP_ERROR(("SCRCHandleSCOCMsg:  Couldn't decode addr\n"));

        return (ITS_EINVALIDARGS);
    }
             
    /* Increment SSN Peg for ED Sent */
    SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].ssn = ssn;
    SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].EDSentPerSourceSSN++;

    return SCRCHandleSCOCMsg_PRC(mtp3, SCCP_MSG_ED, ies, ieCount, cdp);
}

/*
 * Send EA
 */
static int
HandleAppEA(ITS_HDR* hdr, MTP3_HEADER* mtp3,
            ITS_SCCP_IE* ies, int ieCount)
{
    SCCP_CONN_CTXT *foundCtxt;
    SCCP_REF_NUM *dl = NULL;
    SCCP_ADDR local, *cdp = &local;
    int i, error;

    SCCP_DEBUG(("HandleAppEA\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_DEST_LOCAL_REF)
        {
            dl = &ies[i].param_data.destinationLocalReference;
            break;
        }
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleAppEA: Missing destination reference number \n"));

        /*Q752 Implementation Syntax Error Detected Construction Error */
        SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.syntaxConstructionErrDetected++;

        return (ITS_EMISSMAND);
    }

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);

    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("HandleAppEA: Couldn't acquire mutex.\n"));

                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleAppEA: DSM Row Locked.\n"));

                break;
            case (ITS_ENOTFOUND):
                SCCP_WARNING(("HandleAppEA: Can't find ConnectionReference"
                              " in table.\n"));

                break;
        }

        return (ITS_ENOCONN);
    }

    if (foundCtxt->pclass != SCCP_PCLASS_3)
    {
        SCCP_ERROR(("HandleAppEA: EA is invalid for protocol class.\n"));
        /* Outgoing Message - Discarding Message - Message Type not valid for 
           State of Connection. */
        SCCP_Alarm_PRC(679, __FILE__, __LINE__, "family=%s:pclass=%x",
                       "PRC", foundCtxt->pclass);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppEA: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EINVALIDARGS);
    }

    if (foundCtxt->state != SCCP_DATA_TRANSFER)
    {
        SCCP_ERROR(("HandleAppEA: EA is invalid for connection state.\n"));
        SCCP_Alarm_PRC(668, __FILE__, __LINE__, "family=%s", "PRC");

        /* Outgoing Message - Discarding Message - Message Type not valid for 
           State of Connection. */

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppEA: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EBADSTATE);
    }

    switch (foundCtxt->dataState)
    {
        case SCCP_DATA_BOTH_ED:
            foundCtxt->dataState = SCCP_DATA_IN_ED;
            break;

        case SCCP_DATA_IN_ED:
            foundCtxt->dataState = SCCP_DATA_NORMAL;
            break;

        case SCCP_DATA_OUT_ED:
        case SCCP_DATA_NORMAL:
            break;
    }

    *mtp3 = foundCtxt->outLabel;

    local = foundCtxt->daddr;

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->sendInactivity)
    {
        TIMERS_CancelTimer(foundCtxt->sendInactivity);
    }
    foundCtxt->sendInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                     SCCP_T_ias),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
#endif
    
    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleAppEA: DSM unable to free Reference.\n"));

        /* Unable to Commit Session Context to CTXT Table. */
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (gcsMessageBasedRedundancyIsActive)
    {
        ITS_EVENT dummyEvent;
        ITS_UINT  dest;

        SCCP_DEBUG(("GCS Message Based Redundancy is ACTIVE\n"));

        dummyEvent.src  = ITS_GCS_EVENT_TO_NETWORK;
        dummyEvent.data = 0;

        dest = ROUTE_SelectApplication(hdr, &dummyEvent, ITS_TRUE);

        if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
        {
            /* Don't send message for routing to the network */
            SCCP_WARNING(("Message is consumed by SCCP: ctxt = 0x%x\n",
                          hdr->context.conref));
            return ITS_SUCCESS;
        }

    }

    SCCP_DEBUG(("Sending message to Network: ctxt = 0x%x  $$$\n",
                 hdr->context.conref));

    return SCRCHandleSCOCMsg_PRC(mtp3, SCCP_MSG_EA, ies, ieCount, cdp);
}


static int
HandleDownED(ITS_HDR* hdr, MTP3_HEADER* mtp3,
             ITS_SCCP_IE* ies, int ieCount, ITS_BOOLEAN* sendToApp)
{
    SCCP_CONN_CTXT *foundCtxt, *foundCtxt2;
    ITS_INT dlref;
    SCCP_REF_NUM *dl = NULL;
    ITS_CTXT        tempAssocRef;
    ITS_BOOLEAN     tempIsIntermediate;
    int i, error;
    /*Used for sending error notification to app*/
    int errormsgid = 0;

    //Q752
    SCCP_ADDR cdp;
    ITS_OCTET ssn, ai;
    ITS_UINT pc;

    SCCP_DEBUG(("HandleDownED\n"));

    PEG_IncrPeg(PRC_SCCP_Pegs, PEG_SCCP_REMOTE_ED_RCVD);

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_DEST_LOCAL_REF)
        {
            dl = &ies[i].param_data.destinationLocalReference;
            errormsgid = i;
            break;
        }
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleDownED: Missing destination reference number \n"));

        /*Q752 Implementation Syntax Error Detected Value Error */
        SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++;

        /* Incoming Message - Discarding Message - Missing Mandatory 
           Parameter. */

        return (ITS_EMISSMAND);
    }
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[0] != 0)
    {
        SCCP_DEBUG(("HandleDownED:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif

    dlref = RN_GET_REF_NUM(*dl); 
    hdr->context.conref = (ITS_CTXT)dlref;

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);

    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("HandleDownED: Couldn't acquire mutex.\n"));

                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleDownED: DSM Row Locked.\n"));

                break;
            case (ITS_ENOTFOUND):
                SCCP_WARNING(("HandleDownED: Can't find ConnectionReference"
                              " in table.\n"));

                SCCP_ERROR(("HandleDownED:ED received with unassigned DLR"
                            " the message is discarded\n"));

                break;
        }

        return (ITS_ENOCONN);
    }

    //Q752
    cdp = foundCtxt->daddr;
 
    /* Q752 Implementation */
        if (SCCP_DecodeAddr(&cdp, &ai, &pc, &ssn, NULL, NULL) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleSCOCMsg:  Couldn't decode addr\n"));
 
            return (ITS_EINVALIDARGS);
        }
 
 
        /* Increment SSN Peg for DT1 Sent */
           SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].ssn = ssn;
           SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].EDRcvdPerSinkSSN++;

    if (MTP3_RL_GET_DPC_VALUE(foundCtxt->outLabel.label)!=
        MTP3_RL_GET_OPC_VALUE(mtp3->label))
    {
        SCCP_ERROR(("HandleED:Orignating Point Code received not equal to"
                    "  the Pc stored locally hence the msg is discarded\n"));

        return(ITS_EINVALIDARGS);
    }
    if (foundCtxt->state == SCCP_IN_RELEASE_PEND)
    {
        SCCP_DEBUG(("HandleDownED:ED received in incoming"
                        " Release Pending state\n" ));
        SCCP_Alarm_PRC(667, __FILE__, __LINE__, "family=%s", "PRC");

        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownED: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        SCCP_DEBUG(("HandleDownED:Notification for RLSD is sent to app and"
                    " RLSD is sent to remote\n"));

        SendRLSD(foundCtxt, SCCP_RLC_INCONSISTENT_DATA , ITS_FALSE);
      
        errormsgid++;

        RN_SET_REF_NUM(ies[errormsgid].param_data.sourceLocalReference,
                       foundCtxt->slref);
        errormsgid--;

        NotifyRLSDToApp(hdr->context.conref, mtp3, ies, errormsgid,
                       SCCP_RLC_INCONSISTENT_DATA);
        foundCtxt = NULL;

        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);
    }

    if (foundCtxt->pclass != SCCP_PCLASS_3)
    {
        SCCP_ERROR(("HandleDownED: ED is invalid for protocol class.\n"));
        SCCP_Alarm_PRC(680, __FILE__, __LINE__, "family=%s:pclass=%x",
                       "PRC", foundCtxt->pclass);

        /*Q752 Implementation Syntax Error Detected Value Error */ 
        SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++;

        /* Incoming Message - Discarding Message - Message Type not valid for 
           Protocol Class of Connection. */

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownED: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EINVALIDARGS);
    }
    if(foundCtxt->state == SCCP_CONN_OUT_PEND)
    {
        SCCP_DEBUG(("HandleDownED:ED received in outgoing connection"
                    " pending state\n"));
        SCCP_Alarm_PRC(667, __FILE__, __LINE__, "family=%s", "PRC");

#if defined(CONNECTION_TIMERS)
        if (foundCtxt->connectTimer)
        {
            SCCP_DEBUG(("HandleDownED:Connect timer is killed\n"));

            TIMERS_CancelTimer(foundCtxt->connectTimer);
        }
#endif
        /*Release the DSM lock */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownED: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }
        foundCtxt = NULL;

        SCCP_DEBUG(("HandleDownED:Notification is sent to app and"
                    " resources are cleared\n"));

        NotifyERRToApp(hdr->context.conref, mtp3, ies, errormsgid,
                       SCCP_ERR_UNQUAL);

        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);
    }

    if (foundCtxt->state != SCCP_DATA_TRANSFER)
    {
        SCCP_ERROR(("HandleDownED: ED is invalid for connection state.\n"));
        /* Incoming Message - Discarding Message - Message Type not valid for 
           State of Connection. */
        SCCP_Alarm_PRC(667, __FILE__, __LINE__, "family=%s", "PRC");

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownED: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EBADSTATE);
    }

    switch (foundCtxt->dataState)
    {
        case SCCP_DATA_NORMAL:
            foundCtxt->dataState = SCCP_DATA_IN_ED;
            break;

        case SCCP_DATA_OUT_ED:
            foundCtxt->dataState = SCCP_DATA_BOTH_ED;
            break;

        case SCCP_DATA_IN_ED:
        case SCCP_DATA_BOTH_ED:
            break;
    }

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->receiveInactivity)
    {
        TIMERS_CancelTimer(foundCtxt->receiveInactivity);
    }
    foundCtxt->receiveInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                     SCCP_T_iar),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
#endif
    
    /*Save these fields so can use after release lock on row */
    tempAssocRef = foundCtxt->assocRef;
    tempIsIntermediate = foundCtxt->isIntermediate;

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownED: DSM unable to free Reference.\n"));

        /* Unable to Commit Session Context to CTXT Table. */
    }

    if (tempIsIntermediate)
    {
        *sendToApp = ITS_FALSE;

        foundCtxt2 = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                                DSM_TABLE_ITU_SCCP_CTXT, 
                                                (ITS_OCTET *)&tempAssocRef, 
                                                sizeof(tempAssocRef), &error);

        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
                case (ITS_EBADMUTEX):
                    SCCP_ERROR(("HandleDownED: Couldn't acquire mutex.\n"));

                    break;
                case (ITS_EINUSE):
                    SCCP_ERROR(("HandleDownED: DSM Row Locked.\n"));

                    break;
                case (ITS_ENOTFOUND):
                    SCCP_WARNING(("HandleDownED: Can't find ConnectionReference"
                                  " in table.\n"));

                    break;
            }

            return (ITS_ENOCONN);
        }

        RN_SET_REF_NUM(*dl, foundCtxt2->dlref);

        *mtp3 = foundCtxt2->outLabel;

        hdr->context.conref = foundCtxt2->slref;

        ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[ieCount].param_length = sizeof(MTP3_HEADER);
        ies[ieCount].param_data.routingLabel = foundCtxt2->outLabel;
        ieCount++;

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&tempAssocRef, 
                           sizeof(tempAssocRef), foundCtxt2);

        foundCtxt2 = NULL;    /* Not safe to use with out lock */

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownED: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }
    }

    if (!*sendToApp)
    {
        return HandleAppED(hdr, mtp3, ies, ieCount);
    }
    RN_SET_REF_NUM(ies[i].param_data.destinationLocalReference,
                       foundCtxt->dlref);

    if (HandleAppEA( hdr, mtp3, ies,ieCount) != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownED: Failed to sent EA \n"));

        return (ITS_EINVALIDARGS);
    }

    foundCtxt = NULL;

    return (ITS_SUCCESS);
}

static int
HandleDownEA(ITS_HDR* hdr, MTP3_HEADER* mtp3,
             ITS_SCCP_IE* ies, int ieCount, ITS_BOOLEAN* sendToApp)
{
    SCCP_CONN_CTXT *foundCtxt, *foundCtxt2;
    ITS_INT dlref;
    SCCP_REF_NUM *dl = NULL;
    ITS_CTXT        tempAssocRef;
    ITS_BOOLEAN     tempIsIntermediate;
    int i, error;
    int errormsgid = 0;
    SCCP_DEBUG(("HandleDownEA\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_DEST_LOCAL_REF)
        {
            dl = &ies[i].param_data.destinationLocalReference;
            errormsgid = i;
            break;
        }
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleDownEA: Missing destination reference number \n"));

        /*Q752 Implementation Syntax Error Detected Value Error */
        SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++;

        /* Incoming Message - Discarding Message - Missing Mandatory 
           Parameter. */

        return (ITS_EMISSMAND);
    }
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[0] != 0)
    {
        SCCP_DEBUG(("HandleDownEA:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif

    dlref = RN_GET_REF_NUM(*dl); 
    hdr->context.conref = (ITS_CTXT)dlref;

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);

    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("HandleDownEA: Couldn't acquire mutex.\n"));

                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleDownEA: DSM Row Locked.\n"));

                break;
            case (ITS_ENOTFOUND):
                SCCP_WARNING(("HandleDownEA: Can't find ConnectionReference"
                              " in table.\n"));

                SCCP_ERROR(("HandleDownEA:EA received with unassigned DLR"
                            " hence the message is discarded\n"));

                break;
        }

        return (ITS_ENOCONN);
    }

    if (MTP3_RL_GET_DPC_VALUE(foundCtxt->outLabel.label)!=
        MTP3_RL_GET_OPC_VALUE(mtp3->label))
    {
        SCCP_ERROR(("HandleDownEA:Orignating Point Code received not equal to"
                     " the Pc stored locally hence the msg is discarded\n"));

        return(ITS_EINVALIDARGS);
    }

    if (foundCtxt->pclass != SCCP_PCLASS_3)
    {
        SCCP_ERROR(("HandleDownEA: EA is invalid for protocol class.\n"));
        /* Incoming Message - Discarding Message - Message Type not valid for 
           Protocol Class of Connection. */
        SCCP_Alarm_PRC(681, __FILE__, __LINE__, "family=%s:pclass=%x",
                       "PRC", foundCtxt->pclass);

        /*Q752 Implementation Syntax Error Detected Value Error */
        SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++;

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownEA: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EINVALIDARGS);
    }
    if(foundCtxt->state == SCCP_CONN_OUT_PEND)
    {
        SCCP_DEBUG(("HandleDownEA:EA received in outgoing connection"
                    " pending state\n"));
        SCCP_Alarm_PRC(669, __FILE__, __LINE__, "family=%s", "PRC");

#if defined(CONNECTION_TIMERS)
        if (foundCtxt->connectTimer)
        {
            SCCP_DEBUG(("HandleDownEA:Connect timer is killed\n"));

            TIMERS_CancelTimer(foundCtxt->connectTimer);
        }
#endif
        /*Release the DSM lock */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownEA: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }
        foundCtxt = NULL;

        SCCP_DEBUG(("HandleDownEA:Notification is sent to app and"
                    " resources are cleared\n"));

        NotifyERRToApp(hdr->context.conref, mtp3, ies, errormsgid,
                       SCCP_ERR_UNQUAL);

        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);
    }
    if (foundCtxt->state == SCCP_IN_RELEASE_PEND)
    {
        SCCP_DEBUG(("HandleDownEA:EA received in incoming"
                    " Release Pending state\n" ));
        SCCP_Alarm_PRC(669, __FILE__, __LINE__, "family=%s", "PRC");
        
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownEA: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        SCCP_DEBUG(("HandleDownEA:Notification for RLSD is sent to app and"
                    " RLSD is sent to remote\n"));

        SendRLSD(foundCtxt, SCCP_RLC_INCONSISTENT_DATA , ITS_FALSE);
        errormsgid++;

        RN_SET_REF_NUM(ies[errormsgid].param_data.sourceLocalReference,
                       foundCtxt->slref);
        errormsgid--;

        NotifyRLSDToApp(hdr->context.conref, mtp3, ies, errormsgid,
                       SCCP_RLC_INCONSISTENT_DATA);      

        foundCtxt = NULL;

        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);
    }

    if (foundCtxt->state != SCCP_DATA_TRANSFER)
    {
        SCCP_ERROR(("HandleDownEA: EA is invalid for connection state.\n"));
        SCCP_Alarm_PRC(669, __FILE__, __LINE__, "family=%s", "PRC");

        /* Incoming Message - Discarding Message - Message Type not valid for 
           State of Connection. */

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownEA: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EBADSTATE);
    }

    switch (foundCtxt->dataState)
    {
        case SCCP_DATA_BOTH_ED:
            foundCtxt->dataState = SCCP_DATA_OUT_ED;
            break;

        case SCCP_DATA_OUT_ED:
            foundCtxt->dataState = SCCP_DATA_NORMAL;
            break;

        case SCCP_DATA_IN_ED:
        case SCCP_DATA_NORMAL:
            break;
    }

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->receiveInactivity)
    {
        TIMERS_CancelTimer(foundCtxt->receiveInactivity);
    }
    foundCtxt->receiveInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                     SCCP_T_iar),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
#endif
    
    /*Save these fields so can use after release lock on row */
    tempAssocRef = foundCtxt->assocRef;
    tempIsIntermediate = foundCtxt->isIntermediate;

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownEA: DSM unable to free Reference.\n"));

        /* Unable to Commit Session Context to CTXT Table. */
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (tempIsIntermediate)
    {
        *sendToApp = ITS_FALSE;

        foundCtxt2 = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                                DSM_TABLE_ITU_SCCP_CTXT, 
                                                (ITS_OCTET *)&tempAssocRef, 
                                                sizeof(tempAssocRef), &error);

        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
                case (ITS_EBADMUTEX):
                    SCCP_ERROR(("HandleDownEA: Couldn't acquire mutex.\n"));

                    break;
                case (ITS_EINUSE):
                    SCCP_ERROR(("HandleDownEA: DSM Row Locked.\n"));

                    break;
                case (ITS_ENOTFOUND):
                    SCCP_WARNING(("HandleDownEA: Can't find ConnectionReference"
                                  " in table.\n"));

                    break;
            }

            return (ITS_ENOCONN);
        }

        RN_SET_REF_NUM(*dl, foundCtxt2->dlref);

        *mtp3 = foundCtxt2->outLabel;

        hdr->context.conref = foundCtxt2->slref;

        ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[ieCount].param_length = sizeof(MTP3_HEADER);
        ies[ieCount].param_data.routingLabel = foundCtxt2->outLabel;
        ieCount++;

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&tempAssocRef, 
                           sizeof(tempAssocRef), foundCtxt2);

        foundCtxt2 = NULL;    /* Not safe to use with out lock */

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownEA: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }
    }

    if (!*sendToApp)
    {
        return HandleAppEA(hdr, mtp3, ies, ieCount);
    }

    return (ITS_SUCCESS);
}

static int
HandleDownRSR(ITS_HDR* hdr, MTP3_HEADER* mtp3,
              ITS_SCCP_IE* ies, int ieCount, ITS_BOOLEAN* sendToApp)
{
    SCCP_CONN_CTXT *foundCtxt, *foundCtxt2;
    ITS_INT dlref;
    SCCP_REF_NUM *sl = NULL, *dl = NULL;
    ITS_CTXT        tempAssocRef;
    ITS_BOOLEAN     tempIsIntermediate;

    int i, error;
    int errormsgID = 0;

    SCCP_DEBUG(("HandleDownRSR\n"));

    PEG_IncrPeg(PRC_SCCP_Pegs, PEG_SCCP_REMOTE_RSR_RCVD);

    /*Q752 Implementation Message RSR Recieved */
    SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.providerInitiatedResetConn++;

    SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.messageRSRRcvd++;

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
            case SCCP_PRM_SRC_LOCAL_REF:
                sl = &ies[i].param_data.sourceLocalReference;
                break;

            case SCCP_PRM_DEST_LOCAL_REF:
                dl = &ies[i].param_data.destinationLocalReference;
                errormsgID = i;
                break;
        }
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleDownRSR: Missing destination reference number \n"));
        
        /*Q752 Implementation Syntax Error Detected Value Error */
        SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++;
  
        /* Incoming Message - Discarding Message - Missing Mandatory 
           Parameter. */

        return (ITS_EMISSMAND);
    }

    /* Q752 Implementation */
    if (sl == NULL)
    {
        SCCP_ERROR(("HandleDownRSR: Missing source reference number \n"));

        /* Syntax Error Detected Value Error */
        SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++;

        /* Incoming Message - Discarding Message - Missing Mandatory
           Parameter. */

        return (ITS_EMISSMAND);
    }

#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[0] != 0)
    {
        SCCP_DEBUG(("HandleDownRSR:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif

    dlref = RN_GET_REF_NUM(*dl); 
    hdr->context.conref = (ITS_CTXT)dlref;

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);

    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("HandleDownRSR: Couldn't acquire mutex.\n"));

                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleDownRSR: DSM Row Locked.\n"));

                break;
            case (ITS_ENOTFOUND):
                SCCP_WARNING(("HandleDownRSR: Can't find ConnectionReference"
                              " in table.\n"));

                break;
        }

        return (ITS_ENOCONN);
    }

    if (MTP3_RL_GET_DPC_VALUE(foundCtxt->outLabel.label)!=
        MTP3_RL_GET_OPC_VALUE(mtp3->label))
    {
        SCCP_ERROR(("HandleDownRSR:Orignating Point Code received not equal to\
                    the Pc stored locally\n"));

        SendERR(foundCtxt, SCCP_ERR_PC_MISMATCH, ITS_FALSE);

        NotifyERRToApp(hdr->context.conref, mtp3, ies, errormsgID,
                      SCCP_ERR_PC_MISMATCH);

        *sendToApp = ITS_FALSE;

        return(ITS_EINVALIDARGS);
    }

    if (foundCtxt->dlref != RN_GET_REF_NUM(*sl))
    {
        SCCP_DEBUG(("HandleDownRSR:Connection context dlref mismatch with"
                     " the received slref"));
        SendERR(foundCtxt, SCCP_ERR_BAD_LRN, ITS_FALSE);

        NotifyERRToApp(hdr->context.conref, mtp3, ies, errormsgID,
                       SCCP_ERR_BAD_LRN);
        *sendToApp = ITS_FALSE;

        return (ITS_EINVALIDARGS);
    }

    if (foundCtxt->pclass != SCCP_PCLASS_3)
    {
        SCCP_ERROR(("HandleDownRSR: RSR is invalid for protocol class.\n"));
        /* Incoming Message - Discarding Message - Message Type not valid for 
           Protocol Class of Connection. */
        SCCP_Alarm_PRC(682, __FILE__, __LINE__, "family=%s:pclass=%x",
                       "PRC", foundCtxt->pclass);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownRSR: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EINVALIDARGS);
    }
    if(foundCtxt->state == SCCP_CONN_OUT_PEND)
    {
        SCCP_DEBUG(("HandleDownRSR:RSR received in outgoing connection"
                    " pending state\n"));

#if defined(CONNECTION_TIMERS)
        if (foundCtxt->connectTimer)
        {
            SCCP_DEBUG(("HandleDownRSR:Connect timer is killed\n"));

            TIMERS_CancelTimer(foundCtxt->connectTimer);
        }
#endif
        /*Release the DSM lock */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownRSR: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }
        foundCtxt = NULL;

        SCCP_DEBUG(("HandleDownRSR:Notification is sent to app and"
                    " resources are cleared\n"));

        NotifyERRToApp(hdr->context.conref, mtp3, ies, errormsgID,
                       SCCP_ERR_UNQUAL);

        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);
    }
    if (foundCtxt->state == SCCP_IN_RELEASE_PEND)
    {
        SCCP_DEBUG(("HandleDownRSR:RSR received in incoming"
                " Release Pending state\n" ));
       
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownRSR: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        SCCP_DEBUG(("HandleDownRSR:Notification for RLSD is sent to app and"
                    " RLSD is sent to remote\n"));

        SendRLSD(foundCtxt, SCCP_RLC_INCONSISTENT_DATA , ITS_FALSE);
      
        NotifyRLSDToApp(hdr->context.conref, mtp3, ies, errormsgID,
                       SCCP_RLC_INCONSISTENT_DATA);

        foundCtxt = NULL;

        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);
    }

    foundCtxt->state = SCCP_IN_RESET_PEND;

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->receiveInactivity)
    {
        TIMERS_CancelTimer(foundCtxt->receiveInactivity);
    }
    foundCtxt->receiveInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                     SCCP_T_iar),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
#endif
    
    /*Save these fields so can use after release lock on row */
    tempAssocRef = foundCtxt->assocRef;
    tempIsIntermediate = foundCtxt->isIntermediate;

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownRSR: DSM unable to free Reference.\n"));

        /* Unable to Commit Session Context to CTXT Table. */
    }
    
    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (tempIsIntermediate)
    {
        *sendToApp = ITS_FALSE;

        foundCtxt2 = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                                DSM_TABLE_ITU_SCCP_CTXT, 
                                                (ITS_OCTET *)&tempAssocRef, 
                                                sizeof(tempAssocRef), &error);

        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
                case (ITS_EBADMUTEX):
                    SCCP_ERROR(("HandleDownRSR: Couldn't acquire mutex.\n"));

                    break;
                case (ITS_EINUSE):
                    SCCP_ERROR(("HandleDownRSR: DSM Row Locked.\n"));

                    break;
                case (ITS_ENOTFOUND):
                    SCCP_WARNING(("HandleDownRSR: Can't find Connection"
                                  "Reference in table.\n"));

                    break;
            }

            return (ITS_ENOCONN);
        }

        RN_SET_REF_NUM(*dl, foundCtxt2->dlref);

        *mtp3 = foundCtxt2->outLabel;

        hdr->context.conref = foundCtxt2->slref;

        ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[ieCount].param_length = sizeof(MTP3_HEADER);
        ies[ieCount].param_data.routingLabel = foundCtxt2->outLabel;
        ieCount++;

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&tempAssocRef, 
                           sizeof(tempAssocRef), foundCtxt2);

        foundCtxt2 = NULL;    /* Not safe to use with out lock */

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownRSR: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }
    }

    if (!*sendToApp)
    {
        return HandleAppRSR(hdr, mtp3, ies, ieCount);
    }

    return (ITS_SUCCESS);
}

/*
 * reset confirm
 */
static int
HandleAppRSC(ITS_HDR* hdr, MTP3_HEADER* mtp3,
             ITS_SCCP_IE* ies, int ieCount)
{
    SCCP_CONN_CTXT *foundCtxt;
    SCCP_REF_NUM *sl = NULL, *dl = NULL;
    SCCP_ADDR local, *cdp = &local;
    ITS_INT error;

    int i;
    
    SCCP_DEBUG(("HandleAppRSC\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
            case SCCP_PRM_SRC_LOCAL_REF:
                sl = &ies[i].param_data.sourceLocalReference;
                break;

            case SCCP_PRM_DEST_LOCAL_REF:
                dl = &ies[i].param_data.destinationLocalReference;
                break;
        }
    }

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);

    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("HandleAppRSC: Couldn't acquire mutex.\n"));

                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleAppRSC: DSM Row Locked.\n"));

                break;
            case (ITS_ENOTFOUND):
                SCCP_WARNING(("HandleAppRSC: Can't find ConnectionReference"
                              " in table.\n"));

                break;
        }

        return (ITS_ENOCONN);
    }

    if (foundCtxt->pclass != SCCP_PCLASS_3)
    {
        SCCP_ERROR(("HandleAppRSC: RSC is invalid for protocol class.\n"));
        SCCP_Alarm_PRC(683, __FILE__, __LINE__, "family=%s:pclass=%x",
                       "PRC", foundCtxt->pclass);

        /* Incoming Message - Discarding Message - Message Type not valid for 
           Protocol Class of Connection. */

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppRSC: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EINVALIDARGS);
    }

    foundCtxt->state = SCCP_DATA_TRANSFER;

    *mtp3 = foundCtxt->outLabel;

    local = foundCtxt->daddr;

#if defined(CONNECTION_TIMERS)
    TIMERS_CancelTimer(foundCtxt->resetTimer);

    if (foundCtxt->sendInactivity)
    {
        TIMERS_CancelTimer(foundCtxt->sendInactivity);
    }

    foundCtxt->sendInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                     SCCP_T_ias),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
#endif
    
    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleAppRSC: DSM unable to free Reference.\n"));

        /* Unable to Commit Session Context to CTXT Table. */
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (gcsMessageBasedRedundancyIsActive)
    {
        ITS_EVENT dummyEvent;
        ITS_UINT  dest;

        SCCP_DEBUG(("GCS Message Based Redundancy is ACTIVE\n"));

        dummyEvent.src  = ITS_GCS_EVENT_TO_NETWORK;
        dummyEvent.data = 0;

        dest = ROUTE_SelectApplication(hdr, &dummyEvent, ITS_TRUE);

        if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
        {
            /* Don't send message for routing to the network */
            SCCP_WARNING(("Message is consumed by SCCP: ctxt = 0x%x\n",
                          hdr->context.conref));
            return ITS_SUCCESS;
        }

    }

    SCCP_DEBUG(("Sending message to Network: ctxt = 0x%x  $$$\n",
                 hdr->context.conref));


    return SCRCHandleSCOCMsg_PRC(mtp3, SCCP_MSG_RSC, ies, ieCount, cdp);
}

static int
HandleDownRSC(ITS_HDR* hdr, MTP3_HEADER* mtp3,
              ITS_SCCP_IE* ies, int ieCount, ITS_BOOLEAN* sendToApp)
{
    SCCP_CONN_CTXT *foundCtxt, *foundCtxt2;
    ITS_INT dlref;
    SCCP_REF_NUM *sl = NULL, *dl = NULL;
    ITS_CTXT        tempAssocRef;
    ITS_BOOLEAN     tempIsIntermediate;
    int i, error;
    int resetID = 0;
    ITS_EVENT event;
    ITS_HDR hdrntfy;

    SCCP_DEBUG(("HandleDownRSC\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
            case SCCP_PRM_SRC_LOCAL_REF:
                sl = &ies[i].param_data.sourceLocalReference;
                break;

            case SCCP_PRM_DEST_LOCAL_REF:
                dl = &ies[i].param_data.destinationLocalReference;
                resetID = i;
                break;
        }
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleDownRSC: Missing destination reference number \n"));

        /*Q752 Implementation Syntax Error Detected Value Error */
        SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++;

        /* Incoming Message - Discarding Message - Missing Mandatory 
           Parameter. */

        return (ITS_EMISSMAND);
    }
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[0] != 0)
    {
        SCCP_DEBUG(("HandleDownRSC:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif

    dlref = RN_GET_REF_NUM(*dl); 
    hdr->context.conref = (ITS_CTXT)dlref;

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);

    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("HandleDownRSC: Couldn't acquire mutex.\n"));

                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleDownRSC: DSM Row Locked.\n"));

                break;
            case (ITS_ENOTFOUND):
                SCCP_WARNING(("HandleDownRSC: Can't find ConnectionReference"
                              " in table.\n"));

                break;
        }

         return (ITS_ENOCONN);
    }

    if (MTP3_RL_GET_DPC_VALUE(foundCtxt->outLabel.label)!=
        MTP3_RL_GET_OPC_VALUE(mtp3->label))
    {
        SCCP_ERROR(("HandleDownRSC:Orignating Point Coder received not equal to\
                    the Pc stored locally\n"));

        SendERR(foundCtxt, SCCP_ERR_PC_MISMATCH, ITS_FALSE);

        NotifyERRToApp(hdr->context.conref, mtp3, ies, resetID,
                       SCCP_ERR_PC_MISMATCH);

        *sendToApp = ITS_FALSE;

        return(ITS_EINVALIDARGS);
    }

    if (foundCtxt->dlref != RN_GET_REF_NUM(*sl))
    {
        SCCP_DEBUG(("HandleDownRSC:Connection context dlref mismatch with\
                     the received slref"));

        SendERR(foundCtxt, SCCP_ERR_BAD_LRN, ITS_FALSE);

        NotifyERRToApp(hdr->context.conref, mtp3, ies, resetID,
                       SCCP_ERR_BAD_LRN);

        *sendToApp = ITS_FALSE;

        return (ITS_EINVALIDARGS);
    }

    if (foundCtxt->pclass != SCCP_PCLASS_3)
    {
        SCCP_ERROR(("HandleDownRSC: RSC is invalid for protocol class.\n"));
        /* Incoming Message - Discarding Message - Message Type not valid for 
           Protocol Class of Connection. */
        SCCP_Alarm_PRC(684, __FILE__, __LINE__, "family=%s:pclass=%x",
                       "PRC", foundCtxt->pclass);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownRSC: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EINVALIDARGS);
    }
    if(foundCtxt->state == SCCP_CONN_OUT_PEND)
    {
        SCCP_DEBUG(("HandleDownRSC:RSC received in outgoing connection"
                    " pending state\n"));

#if defined(CONNECTION_TIMERS)
        if (foundCtxt->connectTimer)
        {
            SCCP_DEBUG(("HandleDownRSC:Connect timer is killed\n"));

            TIMERS_CancelTimer(foundCtxt->connectTimer);
        }
#endif
        /*Release the DSM lock */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownRSC: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }
        foundCtxt = NULL;

        SCCP_DEBUG(("HandleDownRSC:Notification is sent to app and"
                    " resources are cleared\n"));

        NotifyERRToApp(hdr->context.conref, mtp3, ies, resetID,
                       SCCP_ERR_UNQUAL);

        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);
    }
    if (foundCtxt->state == SCCP_IN_RELEASE_PEND)
    {
        SCCP_DEBUG(("HandleDownRSC:RSC received in incoming"
                    " Release Pending state\n" ));
        
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownRSC: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        SCCP_DEBUG(("HandleDownRSC:Notification for RLSD is sent to app and"
                    " RLSD is sent to remote\n"));

        SendRLSD(foundCtxt, SCCP_RLC_INCONSISTENT_DATA , ITS_FALSE);
      
        NotifyRLSDToApp(hdr->context.conref, mtp3, ies, resetID,
                       SCCP_RLC_INCONSISTENT_DATA);         

        foundCtxt = NULL;

        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);
    }

    if (foundCtxt->state == SCCP_IN_RESET_PEND
        || foundCtxt->state == SCCP_DATA_TRANSFER)
    {
        SCCP_DEBUG(("HandleDownRSC:RSC received in Data Transfer state or in"
                    " Reset pending hence RSR is sent to the remote end\n"));

        *sendToApp = ITS_FALSE;

        SCCP_DEBUG(("HandleDownRSC:Sending notification to the application\n"));
   
        ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[ieCount].param_length = sizeof(MTP3_HEADER);
        ies[ieCount].param_data.routingLabel = *mtp3;
        ieCount++;

        hdrntfy.type = ITS_SCCP;
        event.src = ITS_SCCP_SRC;
        hdrntfy.context.conref = hdr->context.conref;

        SCCP_DEBUG(("HandleDownRSC:Ntfy for RSC is send to App\n"));


        if (SCCP_Encode(ies, ieCount, SCCP_MSG_RSC, &event, &hdrntfy,
                              &SCCP_RSC_Desc)!=ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownRSC:Error in encoding RSC message\n"));

            return (ITS_ENOMSG);
        }

        ITS_SET_CTXT(&event.data[1], hdrntfy.context.conref);

        /* send to the application */
        if (SCCP_SendToAPP(mtp3, &hdrntfy, SCCP_MSG_RSC, &event)!=ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownRSC:Error while sending to Application."));
        }

        RN_SET_REF_NUM(ies[resetID].param_data.destinationLocalReference,
                       foundCtxt->dlref);
        resetID++;

        ies[resetID].param_id = SCCP_PRM_SRC_LOCAL_REF;
        ies[resetID].param_length = sizeof(SCCP_REF_NUM);
        RN_SET_REF_NUM(ies[resetID].param_data.sourceLocalReference,
                       foundCtxt->slref);
        resetID++;

        ies[resetID].param_id = SCCP_PRM_RESET_CAUSE;
        ies[resetID].param_length = sizeof(SCCP_RES_CAUSE);
        ies[resetID].param_data.resetCause.cause =SCCP_RES_NETWORK_OP;

        resetID++;

        ieCount = resetID;

#if defined(CONNECTION_TIMERS)

        if (foundCtxt->receiveInactivity)
        {
            SCCP_DEBUG(("HandleDownRSC:Receive inactivity timer is killed\n"));
            TIMERS_CancelTimer(foundCtxt->receiveInactivity);
        }

        foundCtxt->receiveInactivity =
            TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                    TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                          SCCP_T_iar),
                                            foundCtxt, sizeof(SCCP_CONN_CTXT));

        SCCP_DEBUG(("HandleDownRSC:Receive inactivity timer is restarted\n"));
#endif

        error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownRSC: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        if (HandleAppRSR(hdr, mtp3, ies, ieCount)!= ITS_SUCCESS)
        {
            SCCP_DEBUG(("HandleDownRSC:Error occured  while sending RSR\n"));
          
        }
        SCCP_DEBUG(("HandleDownRSC:Sending notification to the application\n"));

        return(ITS_EBADSTATE);
    }
    foundCtxt->state = SCCP_DATA_TRANSFER;

#if defined(CONNECTION_TIMERS)
    TIMERS_CancelTimer(foundCtxt->resetTimer);

    if (foundCtxt->receiveInactivity)
    {
        TIMERS_CancelTimer(foundCtxt->receiveInactivity);
    }

    foundCtxt->receiveInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                     SCCP_T_iar),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
#endif 

    /*Save these fields so can use after release lock on row */
    tempAssocRef = foundCtxt->assocRef;
    tempIsIntermediate = foundCtxt->isIntermediate;

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownRSC: DSM unable to free Reference.\n"));

        /* Unable to Commit Session Context to CTXT Table. */
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (tempIsIntermediate)
    {
        *sendToApp = ITS_FALSE;

        foundCtxt2 = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                                DSM_TABLE_ITU_SCCP_CTXT, 
                                                (ITS_OCTET *)&tempAssocRef, 
                                                sizeof(tempAssocRef), &error);

        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
                case (ITS_EBADMUTEX):
                    SCCP_ERROR(("HandleDownRSC: Couldn't acquire mutex.\n"));

                    break;
                case (ITS_EINUSE):
                    SCCP_ERROR(("HandleDownRSC: DSM Row Locked.\n"));

                    break;
                case (ITS_ENOTFOUND):
                    SCCP_WARNING(("HandleDownRSC: Can't find Connection"
                                  "Reference in table.\n"));

                    break;
            }

            return (ITS_ENOCONN);
        }

        RN_SET_REF_NUM(*dl, foundCtxt2->dlref);

        *mtp3 = foundCtxt2->outLabel;

        hdr->context.conref = foundCtxt2->slref;

        ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[ieCount].param_length = sizeof(MTP3_HEADER);
        ies[ieCount].param_data.routingLabel = foundCtxt2->outLabel;
        ieCount++;

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&tempAssocRef, 
                           sizeof(tempAssocRef), foundCtxt2);

        foundCtxt2 = NULL;    /* Not safe to use with out lock */

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownRSC: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }
    }

    if (!*sendToApp)
    {
        return HandleAppRSC(hdr, mtp3, ies, ieCount);
    }

    return (ITS_SUCCESS);
}

/*
 * err
 */
static int
HandleAppERR(ITS_HDR* hdr, MTP3_HEADER* mtp3,
             ITS_SCCP_IE* ies, int ieCount)
{
    SCCP_CONN_CTXT *foundCtxt;
    SCCP_REF_NUM *dl = NULL;
    SCCP_ADDR local, *cdp = &local;
    int i, error;

    SCCP_DEBUG(("HandleAppERR\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_DEST_LOCAL_REF)
        {
            dl = &ies[i].param_data.destinationLocalReference;
            break;
        }
    }

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);

    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("HandleAppERR: Couldn't acquire mutex.\n"));

                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleAppERR: DSM Row Locked.\n"));

                break;
            case (ITS_ENOTFOUND):
                SCCP_WARNING(("HandleAppERR: Can't find ConnectionReference"
                              " in table.\n"));

                break;
        }

        return (ITS_ENOCONN);
    }


    *mtp3 = foundCtxt->outLabel;

    local = foundCtxt->daddr;

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->sendInactivity)
    {
        TIMERS_CancelTimer(foundCtxt->sendInactivity);
    }

    foundCtxt->sendInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                     SCCP_T_ias),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
#endif
    
    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleAppERR: DSM unable to free Reference.\n"));

        /* Unable to Commit Session Context to CTXT Table. */
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    PEG_IncrPeg(PRC_SCCP_Pegs, PEG_SCCP_ERR_TO_REMOTE_SENT);

    /*Q752 Implementation Message Error Sent */
    SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.messageErrSent++;

    if (gcsMessageBasedRedundancyIsActive)
    {
        ITS_EVENT dummyEvent;
        ITS_UINT  dest;

        SCCP_DEBUG(("GCS Message Based Redundancy is ACTIVE\n"));

        dummyEvent.src  = ITS_GCS_EVENT_TO_NETWORK;
        dummyEvent.data = 0;

        dest = ROUTE_SelectApplication(hdr, &dummyEvent, ITS_TRUE);

        if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
        {
            /* Don't send message for routing to the network */
            SCCP_WARNING(("Message is consumed by SCCP: ctxt = 0x%x\n",
                          hdr->context.conref));
            return ITS_SUCCESS;
        }

    }

    SCCP_DEBUG(("Sending message to Network: ctxt = 0x%x  $$$\n",
                 hdr->context.conref));

    return SCRCHandleSCOCMsg_PRC(mtp3, SCCP_MSG_ERR, ies, ieCount, cdp);
}

static int
HandleDownERR(ITS_HDR* hdr, MTP3_HEADER* mtp3,
              ITS_SCCP_IE* ies, int ieCount, ITS_BOOLEAN* sendToApp)
{
    ITS_INT dlref;
    SCCP_REF_NUM *dl = NULL;
    SCCP_CONN_CTXT *foundCtxt, *foundCtxt2;
    ITS_CTXT        tempAssocRef;
    ITS_BOOLEAN     tempIsIntermediate;
    int i, error;
    int releaseID = 0;
    ITS_OCTET cause = 0 ;

    SCCP_DEBUG(("HandleDownERR\n"));

    PEG_IncrPeg(PRC_SCCP_Pegs, PEG_SCCP_REMOTE_ERR_RCVD);

    /*Q752 Implementation Message Error Recieved */   
    SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.messageErrRcvd++;

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
            case SCCP_PRM_DEST_LOCAL_REF:
                dl = &ies[i].param_data.destinationLocalReference;
                releaseID = i;
                break;

            case SCCP_PRM_ERROR_CAUSE:
                cause =  ies[i].param_data.errorCause.cause;
                break;
        }
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleDownERR: Missing destination reference number \n"));

        /*Q752 Implementation Syntax Error Detected Value Error */
        SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++;

        return (ITS_EMISSMAND);
    }
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[0] != 0)
    {
        SCCP_DEBUG(("HandleDownERR:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif

    dlref = RN_GET_REF_NUM(*dl); 
    hdr->context.conref = (ITS_CTXT)dlref;

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);

    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("HandleDownERR: Couldn't acquire mutex.\n"));

                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleDownERR: DSM Row Locked.\n"));

                break;
            case (ITS_ENOTFOUND):
                SCCP_WARNING(("HandleDownERR: Can't find ConnectionReference"
                              " in table.\n"));

                SCCP_ERROR(("HandleDownERR:ERR received with unassigned DLR"
                            " hence the message is discarded\n"));

            break;
        }

        return (ITS_ENOCONN);
    }
    if (foundCtxt->state == SCCP_CONN_IN_PEND)
    {
        SCCP_ERROR(("HandleDownERR:ERR received in incoming connection"
                    " pending,msg discarded\n"));

        /* Unknown message in this state*/

        return (ITS_EINVALIDARGS);
    }

    if(foundCtxt->state == SCCP_CONN_OUT_PEND
       || foundCtxt->state == SCCP_OUT_RELEASE_PEND
       || foundCtxt->state == SCCP_IN_RELEASE_PEND)
    {
        SCCP_DEBUG(("HandleDownERR:ERR received in state %x\n",foundCtxt->state));

#if defined(CONNECTION_TIMERS)
        if (foundCtxt->connectTimer)
        {
            SCCP_DEBUG(("HandleDownERR:Connect timer is killed\n"));

            TIMERS_CancelTimer(foundCtxt->connectTimer);
        }
#endif
        /*Release the DSM lock */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownERR: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }
        foundCtxt = NULL;

        SCCP_DEBUG(("HandleDownERR:Notification is sent to app and"
                    " resources are cleared\n"));

        NotifyERRToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_ERR_UNQUAL);

        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);
    }

    if (MTP3_RL_GET_DPC_VALUE(foundCtxt->outLabel.label)!=
        MTP3_RL_GET_OPC_VALUE(mtp3->label))
    {
        SCCP_ERROR(("HandleDownERR:Orignating Point Code received not equal to\
                     the Pc stored locally hence the msg is discarded\n"));

        return (ITS_EINVALIDARGS);
    }

    /* Save these fields so can use after release lock on row */ 
    tempAssocRef = foundCtxt->assocRef;
    tempIsIntermediate = foundCtxt->isIntermediate;

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref,
                       sizeof(hdr->context.conref), foundCtxt);

    if (error!= ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownERR:DSM unable to free reference \n"));

        /* Unable to Commit Session Context to CTXT table */
    }

    if (tempIsIntermediate)
    {
        *sendToApp = ITS_FALSE;

        foundCtxt2 = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                                DSM_TABLE_ITU_SCCP_CTXT, 
                                                (ITS_OCTET *)&tempAssocRef, 
                                                sizeof(tempAssocRef), &error);
        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
                case (ITS_EBADMUTEX):
                    SCCP_ERROR(("HandleDownERR: Couldn't acquire mutex.\n"));

                    break;
                case (ITS_EINUSE):
                    SCCP_ERROR(("HandleDownERR: DSM Row Locked.\n"));

                    break;
                case (ITS_ENOTFOUND):
                    SCCP_WARNING(("HandleDownERR: Can't find Connection"
                                  "Reference in table.\n"));

                    break;
            }

            return (ITS_ENOCONN);
        }

        RN_SET_REF_NUM(*dl, foundCtxt2->dlref);

        *mtp3 = foundCtxt2->outLabel;

        hdr->context.conref = foundCtxt2->slref;

        ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[ieCount].param_length = sizeof(MTP3_HEADER);
        ies[ieCount].param_data.routingLabel = foundCtxt2->outLabel;
        ieCount++;

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&tempAssocRef, 
                           sizeof(tempAssocRef), foundCtxt2);

        foundCtxt2 = NULL;    /* Not safe to use with out lock */

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownCREF: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }
    }

    if (!*sendToApp)
    {
        return HandleAppERR(hdr, mtp3, ies, ieCount);
    }

    if (!BEHAVIORS_GetBehavior(&PRC_SCCP_Behaviors,
                               SCCP_B_propagate_ERR))
    {
        *sendToApp = ITS_FALSE;
    }

    if (cause == SCCP_ERR_SCLASS_MIS)
    {
        *sendToApp = ITS_FALSE;
        SCCP_DEBUG(("HandleDownERR:RLSD is sent to the remote end as the error"
                    " cause is service class mismatch"));

        RN_SET_REF_NUM(ies[releaseID].param_data.destinationLocalReference,
                       foundCtxt->dlref);

        releaseID++;

        ies[releaseID].param_id = SCCP_PRM_SRC_LOCAL_REF;
        ies[releaseID].param_length = sizeof(SCCP_REF_NUM);
        RN_SET_REF_NUM(ies[releaseID].param_data.sourceLocalReference,
                       foundCtxt->slref);
        releaseID++;

        ies[releaseID].param_id = SCCP_PRM_RELEASE_CAUSE;
        ies[releaseID].param_length = sizeof(SCCP_REL_CAUSE);
        ies[releaseID].param_data.releaseCause.cause =
                                                  SCCP_RLC_INCONSISTENT_DATA;
        releaseID++;
        ieCount = releaseID;

        return(HandleAppRLSD(hdr, mtp3, ies, ieCount));
    }  
    else 
    {
#if defined(CONNECTION_TIMERS)
        SCCP_ERROR(("HandleDownERR:All the timers for the connection"
                     " are killed"));

        if (foundCtxt->receiveInactivity)
        {
            TIMERS_CancelTimer(foundCtxt->receiveInactivity);
        }

        if (foundCtxt->connectTimer)
        {
            TIMERS_CancelTimer(foundCtxt->connectTimer);
        }

        if (foundCtxt->sendInactivity)
        {
            TIMERS_CancelTimer(foundCtxt->sendInactivity);
        }

        if (foundCtxt->releaseTimer)
        {
            TIMERS_CancelTimer(foundCtxt->releaseTimer);
        }

        if (foundCtxt->repeatReleaseTimer)
        {
            TIMERS_CancelTimer(foundCtxt->repeatReleaseTimer);
        }

        if (foundCtxt->intervalTimer)
        {
            TIMERS_CancelTimer(foundCtxt->intervalTimer);
        }

        if(foundCtxt->resetTimer)
        {
            TIMERS_CancelTimer(foundCtxt->resetTimer);
        }
#endif
        SCCP_DEBUG(("HandleDownERR:Connection reference is cleared\n"));

        SCCP_DeleteLocalReference_PRC(hdr->context.conref);

    }

    foundCtxt = NULL;

    return (ITS_SUCCESS);
}

/*
 * IT
 */
static int
HandleAppIT(ITS_HDR* hdr, MTP3_HEADER* mtp3,
            ITS_SCCP_IE* ies, int ieCount)
{
    SCCP_CONN_CTXT *foundCtxt;
    SCCP_REF_NUM *sl = NULL, *dl = NULL;
    SCCP_ADDR local, *cdp = &local;
    int i, error;
       
    SCCP_DEBUG(("HandleAppIT\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
            case SCCP_PRM_SRC_LOCAL_REF:
                sl = &ies[i].param_data.sourceLocalReference;
                break;

            case SCCP_PRM_DEST_LOCAL_REF:
                dl = &ies[i].param_data.destinationLocalReference;
                break;
        }
    }

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);

    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("HandleAppIT: Couldn't acquire mutex.\n"));

                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleAppIT: DSM Row Locked.\n"));

                break;
            case (ITS_ENOTFOUND):
                SCCP_WARNING(("HandleAppIT: Can't find ConnectionReference"
                              " in table.\n"));

                break;
        }

        return (ITS_ENOCONN);
    }

    *mtp3 = foundCtxt->outLabel;

    local = foundCtxt->daddr;

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->sendInactivity)
    {
        TIMERS_CancelTimer(foundCtxt->sendInactivity);
    }
    foundCtxt->sendInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                     SCCP_T_ias),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
#endif
    
    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleAppIT: DSM unable to free Reference.\n"));

        /* Unable to Commit Session Context to CTXT Table. */
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (gcsMessageBasedRedundancyIsActive)
    {
        ITS_EVENT dummyEvent;
        ITS_UINT  dest;

        SCCP_DEBUG(("GCS Message Based Redundancy is ACTIVE\n"));

        dummyEvent.src  = ITS_GCS_EVENT_TO_NETWORK;
        dummyEvent.data = 0;

        dest = ROUTE_SelectApplication(hdr, &dummyEvent, ITS_TRUE);

        if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
        {
            /* Don't send message for routing to the network */
            SCCP_WARNING(("Message is consumed by SCCP: ctxt = 0x%x\n",
                          hdr->context.conref));
            return ITS_SUCCESS;
        }

    }

    SCCP_DEBUG(("Sending message to Network: ctxt = 0x%x  $$$\n",
                 hdr->context.conref));


    return SCRCHandleSCOCMsg_PRC(mtp3, SCCP_MSG_IT, ies, ieCount, cdp);
}

static int
HandleDownIT(ITS_HDR* hdr, MTP3_HEADER* mtp3,
             ITS_SCCP_IE* ies, int ieCount, ITS_BOOLEAN* sendToApp)
{
    ITS_UINT dlref;
    SCCP_REF_NUM *sl = NULL, *dl = NULL;
    SCCP_CONN_CTXT *foundCtxt,copyCtxt;
    ITS_OCTET pclass = 0;
    ITS_OCTET creditvalue = 0;
    int i, error;
    int releaseID = 0;

    SCCP_DEBUG(("HandleDownIT\n"));

    *sendToApp = ITS_FALSE;

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
            case SCCP_PRM_SRC_LOCAL_REF:
                sl = &ies[i].param_data.sourceLocalReference;
                break;

            case SCCP_PRM_DEST_LOCAL_REF:
                dl = &ies[i].param_data.destinationLocalReference;
                releaseID = i;
                break;
    
            case SCCP_PRM_PROTOCOL_CLASS:
                pclass = ies[i].param_data.protocolClass.pclass;
                break;

            case SCCP_PRM_CREDIT:
                creditvalue = ies[i].param_data.credit.win_size;
                break;
        }
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleDownIT: Missing destination reference number \n"));

        /*Q752 Implementation Syntax Error Detected Value Error */
        SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++;

        /* Incoming Message - Discarding Message - Missing Mandatory 
           Parameter. */

        return (ITS_EMISSMAND);
    }

    /* Q752 Implementation */
    if (sl == NULL)
    {
        SCCP_ERROR(("HandleDownIT: Missing source reference number \n"));
        /* Syntax Error Detected Value Error */
        SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.syntaxValueErrDetected++;

        /* Incoming Message - Discarding Message - Missing Mandatory
           Parameter. */

        return (ITS_EMISSMAND);
    }

#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[0] != 0)
    {
        SCCP_DEBUG(("HandleDownIT:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif

    dlref = RN_GET_REF_NUM(*dl); 

    hdr->context.conref = (ITS_CTXT)dlref;

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);

    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("HandleDownIT: Couldn't acquire mutex.\n"));

                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleDownIT: DSM Row Locked.\n"));

                break;
            case (ITS_ENOTFOUND):
                SCCP_WARNING(("HandleDownIT: Can't find ConnectionReference"
                              " in table.\n"));

                SCCP_ERROR(("HandleDownIT:IT received with unassigned DLR"
                             ", the message is discarded\n"));

                break;
        }

        return (ITS_ENOCONN);
    }

    if (MTP3_RL_GET_DPC_VALUE(foundCtxt->outLabel.label)!=
        MTP3_RL_GET_OPC_VALUE(mtp3->label))
    {
        SCCP_ERROR(("HandleDownIT:Orignating Point Code received not equal to\
                     the Pc stored locally hence the msg is discarded\n"));

        return(ITS_EINVALIDARGS);
    }

    if (foundCtxt->dlref != RN_GET_REF_NUM(*sl))
    {
        SCCP_DEBUG(("HandleDownIT:Connection context dlref mismatch with"
                     " the received slref\n"));
        copyCtxt = *foundCtxt;
        copyCtxt.dlref = RN_GET_REF_NUM(*sl);

        SCCP_DEBUG(("HandleDownIT:RLSD is sent to the remote end on basis of"
                " information from the received message & ntfy to app\n"));  
         /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownIT: DSM unable to free Reference.\n"));
        }

        SendRLSD(&copyCtxt, SCCP_REF_DEST_UKNOWN, ITS_FALSE);

        NotifyRLSDToApp(hdr->context.conref, mtp3, ies, releaseID,
                        SCCP_REF_DEST_UKNOWN);
     
        SCCP_DEBUG(("HandleDownIT:RLSD is sent to the remote end on basis of"
                   " information stored locally & ntfy to app\n"));

        SendRLSD(foundCtxt, SCCP_RLC_INCONSISTENT_DATA, ITS_FALSE);

        NotifyRLSDToApp(foundCtxt->dlref, mtp3, ies, releaseID,
                        SCCP_RLC_INCONSISTENT_DATA);
        foundCtxt = NULL;
        *sendToApp = ITS_FALSE;

        return (ITS_EINVALIDARGS);
    }
    if (foundCtxt->state == SCCP_OUT_RELEASE_PEND
        || foundCtxt->state == SCCP_CONN_IN_PEND)
    {
        SCCP_ERROR(("HandleDownIT:IT received in state = %x,dicarded",
                     foundCtxt->state));

         /* Unknown message in this state*/

        return (ITS_EINVALIDARGS);
    }
    if(foundCtxt->state == SCCP_CONN_OUT_PEND)
    {
        SCCP_DEBUG(("HandleDownIT:IT received in outgoing connection"
                    " pending state\n"));

#if defined(CONNECTION_TIMERS)
        if (foundCtxt->connectTimer)
        {
            SCCP_DEBUG(("HandleDownIT:Connect timer is killed\n"));

            TIMERS_CancelTimer(foundCtxt->connectTimer);
        }
#endif
        /*Release the DSM lock */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownIT: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }
        foundCtxt = NULL;

        SCCP_DEBUG(("HandleDownIT:Notification is sent to app and"
                    " resources are cleared\n"));

        NotifyERRToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_ERR_UNQUAL);

        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);
    }
    if ((foundCtxt->state == SCCP_IN_RELEASE_PEND)
        ||((( pclass & SCCP_PCLASS_MASK) != foundCtxt->pclass)
        || (dlref != foundCtxt->slref)))
    {
        SCCP_DEBUG(("HandleDownIT:IT received in incoming Release Pending"
                    "  state or mismatch in protocol class or source"
                    "reference number\n" ));
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownIT: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }

        SCCP_DEBUG(("HandleDownIT:Notification for RLSD is sent to app and"
                    " RLSD is sent to remote\n"));

        SendRLSD(foundCtxt, SCCP_RLC_INCONSISTENT_DATA , ITS_FALSE);
      
        NotifyRLSDToApp(foundCtxt->dlref, mtp3, ies, releaseID,
                        SCCP_RLC_INCONSISTENT_DATA);

        foundCtxt = NULL;

        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);
    } 

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->receiveInactivity)
    {
        TIMERS_CancelTimer(foundCtxt->receiveInactivity);
    }
    foundCtxt->receiveInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                     SCCP_T_iar),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
#endif
    
    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownIT: DSM unable to free Reference.\n"));

        /* Unable to Commit Session Context to CTXT Table. */
    }

    if (creditvalue != foundCtxt->windowSize)
    {
        SCCP_DEBUG(("HandleDownIT:Credit value missmatch so RSR is send\n"));


        RN_SET_REF_NUM(ies[releaseID].param_data.destinationLocalReference,
                       foundCtxt->dlref);
        releaseID++;
        RN_SET_REF_NUM(ies[releaseID].param_data.sourceLocalReference,
                       foundCtxt->slref);
        releaseID++;

        ies[releaseID].param_id = SCCP_PRM_RESET_CAUSE;
        ies[releaseID].param_length = sizeof(SCCP_RES_CAUSE);
        ies[releaseID].param_data.resetCause.cause =SCCP_RES_NETWORK_OP;

        releaseID++;
        ieCount = releaseID;

        if(HandleAppRSR(hdr, mtp3, ies, ieCount)!=ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownIT:Error in sending RSR to the\
                         other end\n"));

            return(ITS_ENOMSG);
        }
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (!BEHAVIORS_GetBehavior(&PRC_SCCP_Behaviors,
                               SCCP_B_propagate_IT))
    {
        *sendToApp = ITS_FALSE;
    }

    return (ITS_SUCCESS);
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
 *  csireesh   04-04-2005  Bug ID:0576            Sending CREF by swaping the
 *                                                MTP3 Routing Lable.
 *  csireesh   06-05-2005  Bug ID:1801, 1802      Sending CREF if DSM Find failed
 *                                                in Invalied Connection State.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
SCOCHandleRoutingFailure_PRC(MTP3_HEADER* mtp3, ITS_OCTET mType,
                               ITS_SCCP_IE* ies, int ieCount,
                               ITS_OCTET reason)
{
    ITS_INT opc, dpc;
    ITS_OCTET sls;
    SCCP_CONN_CTXT *foundCtxt = NULL;
    SCCP_REF_NUM *sl = NULL;
    SCCP_REF_NUM *dl = NULL;
    int error, i;
    ITS_HDR hdr;
    ITS_BOOLEAN toApp = ITS_FALSE;
    ITS_OCTET ni = MTP3_HDR_GET_SIO_PRC(*mtp3) & MTP3_NIC_MASK;
    SCCP_ADDR *cgp = NULL;

    SCCP_DEBUG(("SCOCHandleRoutingFailure:\n"));

    /* INCR Number of Routing Failures */
    PEG_IncrPeg(PRC_SCCP_Pegs, PEG_SCCP_ROUTING_FAILURE);

    opc = MTP3_RL_GET_OPC_VALUE(mtp3->label);
    dpc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
    sls = MTP3_RL_GET_SLS(mtp3->label);

    if (mType == SCCP_MSG_RLC || mType == SCCP_MSG_CREF)
    {
        SCCP_DEBUG(("SCOCHandleRoutingFailure: Drop the message\n"));

        return (ITS_SUCCESS);
    } 

    if (SCCP_IsSSNEquipped(ni, opc, SCCP_SSN_SCCPMGMT))
    {
        toApp = ITS_TRUE;
        SCCP_DEBUG(("SCOCHandleRoutingFailure: for local\n"));
    }
    else if (SCCP_IsSSNEquipped(ni, dpc, SCCP_SSN_SCCPMGMT))
    {
        toApp = ITS_FALSE;
        SCCP_DEBUG(("SCOCHandleRoutingFailure: for remote\n"));
    }
    else
    {
        /* Not much we can do - bail out */
        return ITS_SUCCESS;
    }

    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
            case SCCP_PRM_SRC_LOCAL_REF:
                sl = &ies[i].param_data.sourceLocalReference;
                break;

            case SCCP_PRM_DEST_LOCAL_REF:
                dl = &ies[i].param_data.destinationLocalReference;
                break;

            case SCCP_PRM_CALLING_PARTY_ADDR:
                cgp = &ies[i].param_data.callingPartyAddr;
                break;

        }
    }

    hdr.type = ITS_SCCP;

    if (toApp)  
    {
        hdr.context.conref = (ITS_CTXT)RN_GET_REF_NUM(*sl);
    }
    else
    {
        if (dl)
        {
            hdr.context.conref = (ITS_CTXT)RN_GET_REF_NUM(*dl);
        }
        else
        {
            hdr.context.conref = (ITS_CTXT)RN_GET_REF_NUM(*sl);

            sendConnectionRefuse(mtp3, hdr.context.conref, cgp);
            return (ITS_ENOCONN);
        }
    }

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr.context.conref,
                                           sizeof(hdr.context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("SCOCHandleRoutingFailure: Couldn't acquire DSM Row "
                           "mutex.\n"));
            break;

        case (ITS_EINUSE):
            SCCP_ERROR(("SCOCHandleRoutingFailure: DSM Row Locked.\n"));
            break;

        case (ITS_ENOTFOUND):
            sendConnectionRefuse(mtp3, hdr.context.conref, cgp);
            SCCP_ERROR(("SCOCHandleRoutingFailure: Can't find "
                        "ConnectionReference in DSM table.\n"));
            break;
        }

        return (ITS_ENOCONN);
    }

    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&hdr.context.conref,
                       sizeof(hdr.context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("SCOCHandleRoutingFailure: DSM unable to Commit"
                    "Reference in order to Release Lock.\n"));
    }

    switch (mType)
    {
        case SCCP_MSG_CR:    
            SendCREF(foundCtxt, SCCP_REF_DEST_UNAVAIL, toApp);
            SCCP_DEBUG(("SCOCHandleRoutingFailure: CREF sent\n"));
            break;

        case SCCP_MSG_RLSD:    
            SendRLC(foundCtxt, SCCP_REF_DEST_UNAVAIL, toApp);
            SCCP_DEBUG(("SCOCHandleRoutingFailure: RLC sent\n"));
            break;

        case SCCP_MSG_CC:    
        case SCCP_MSG_DT1:
            if (toApp)
            {   
                /* To send back to app, fake it from remote */
                MTP3_POINT_CODE tmp, tmp2;

                MTP3_RL_GET_OPC(foundCtxt->outLabel.label, tmp);
                MTP3_RL_GET_DPC(foundCtxt->outLabel.label, tmp2);
                MTP3_RL_SET_OPC(foundCtxt->outLabel.label, tmp2);
                MTP3_RL_SET_DPC(foundCtxt->outLabel.label, tmp);
            }

            SendRLSD(foundCtxt, SCCP_REF_DEST_UNAVAIL, toApp);
            SCCP_DEBUG(("SCOCHandleRoutingFailure: RLSD sent\n"));     
            break;
    } 

    foundCtxt = NULL;

    return (ITS_SUCCESS);
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
 *  Notes:
 *
 *  See Also:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  gharipriya 12-10-2006 Bug Id 4472            Remove the check for SSN 
 *
 *  gharipriya 25-09-2006 Bug ID:4366     DT1/DT2/ED Pegs Implementation.
 *
 ****************************************************************************/
int
SCOCHandleAPPMsg_PRC(ITS_EVENT *event)
{
    MTP3_HEADER localStore, *mtp3 = &localStore;
    ITS_SCCP_IE ies[32];
    ITS_HDR hdr;
    int ieCount, ret;

    SCCP_PROT_CLASS* pclass = NULL;

    hdr.type = ITS_SCCP;
    hdr.context.conref = ITS_GET_CTXT(&event->data[1]);

    PEG_IncrPeg(PRC_SCCP_Pegs,PEG_SCCP_USER_MSG_SENT);
   
    /*Q752 Implementation Message From Remote SubSystem */
    SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.messageFromLocalSS++;

    /* process based on type */
    switch (SCCP_MSG_TYPE(event))
    {
        case SCCP_MSG_CR:

            PEG_IncrPeg(PRC_SCCP_Pegs,PEG_SCCP_USER_CR_SENT);
            
            /*Q752 Implementation Number of CR messages Sent */
            SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.messageCRSent++;

            if ((ret = SCCP_Decode(ies, &ieCount, event,
                                   &SCCP_CR_Desc)) != ITS_SUCCESS)
            {
                /* Outgoing Message - Discarding Message - Invalid or 
                   Corrupted. */

                return (ret);
            }

            return HandleAppCR(&hdr, mtp3, ies, ieCount);

        case SCCP_MSG_CC:

            if ((ret = SCCP_Decode(ies, &ieCount, event,
                                   &SCCP_CC_Desc)) != ITS_SUCCESS)
            {
                /* Outgoing Message - Discarding Message - Invalid or 
                   Corrupted. */

                return (ret);
            }

            return HandleAppCC(&hdr, mtp3, ies, ieCount);

        case SCCP_MSG_CREF:
              
            /*Q752 Implementation CREF Messges Sent */
            SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.messageCREFSent++;

            if ((ret = SCCP_Decode(ies, &ieCount, event,
                               &SCCP_CREF_Desc)) != ITS_SUCCESS)
            {
               /* Outgoing Message - Discarding Message - Invalid or 
                  Corrupted. */

                return (ret);
            }

            return HandleAppCREF(&hdr, mtp3, ies, ieCount);

        case SCCP_MSG_RLSD:

            PEG_IncrPeg(PRC_SCCP_Pegs, PEG_SCCP_USER_INITIATED_RLS);
   
            /*Q752 Implementation User Initiated Release */
            SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.userInitiatedReleaseConn++;
            
            if ((ret = SCCP_Decode(ies, &ieCount, event,
                               &SCCP_RLSD_Desc)) != ITS_SUCCESS)
            {
                return (ret);
            }

            return HandleAppRLSD(&hdr, mtp3, ies, ieCount);

        case SCCP_MSG_RLC:
            if ((ret = SCCP_Decode(ies, &ieCount, event,
                                   &SCCP_RLC_Desc)) != ITS_SUCCESS)
            {
                /* Outgoing Message - Discarding Message - Invalid or 
                   Corrupted. */

                return (ret);
            }

            return HandleAppRLC(&hdr, mtp3, ies, ieCount);

        case SCCP_MSG_DT1:

            PEG_IncrPeg(PRC_SCCP_Pegs, PEG_SCCP_USER_DT1_SENT);

            if ((ret = SCCP_Decode(ies, &ieCount, event,
                                   &SCCP_DT1_Desc)) != ITS_SUCCESS)
            {
                return (ret);
            }

            return HandleAppDT1(&hdr, mtp3, ies, ieCount);

        case SCCP_MSG_DT2:

            PEG_IncrPeg(PRC_SCCP_Pegs,PEG_SCCP_USER_DT2_SENT);
            
            if ((ret = SCCP_Decode(ies, &ieCount, event,
                                   &SCCP_DT2_Desc)) != ITS_SUCCESS)
            {
                /* Outgoing Message - Discarding Message - Invalid or 
                   Corrupted. */

                return (ret);
            }

            return HandleAppDT2(&hdr, mtp3, ies, ieCount);

        case SCCP_MSG_AK:
            if ((ret = SCCP_Decode(ies, &ieCount, event,
                                   &SCCP_AK_Desc)) != ITS_SUCCESS)
            {
                /* Outgoing Message - Discarding Message - Invalid or 
                   Corrupted. */

                return (ret);
            }

            return HandleAppAK(&hdr, mtp3, ies, ieCount);

        case SCCP_MSG_ED:

            PEG_IncrPeg(PRC_SCCP_Pegs, PEG_SCCP_USER_ED_SENT);

            if ((ret = SCCP_Decode(ies, &ieCount, event,
                                   &SCCP_ED_Desc)) != ITS_SUCCESS)
            {
                /* Outgoing Message - Discarding Message - Invalid or 
                   Corrupted. */

                return (ret);
            }

            return HandleAppED(&hdr, mtp3, ies, ieCount);
    
        case SCCP_MSG_EA:
            if ((ret = SCCP_Decode(ies, &ieCount, event,
                                   &SCCP_EA_Desc)) != ITS_SUCCESS)
            {
                /* Outgoing Message - Discarding Message - Invalid or 
                   Corrupted. */

                return (ret);
            }

            return HandleAppEA(&hdr, mtp3, ies, ieCount);

        case SCCP_MSG_RSR:
             
            /*Q752 Implementation RSR message Sent */ 
            SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.messageRSRSent++;
  
            PEG_IncrPeg(PRC_SCCP_Pegs,PEG_SCCP_USER_INITITATED_RESET);
            
            /*Q752 Implementation User Initiated Reset */ 
            SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.userInitiatedResetConn++; 

            if ((ret = SCCP_Decode(ies, &ieCount, event,
                                   &SCCP_RSR_Desc)) != ITS_SUCCESS)
            {
                /* Outgoing Message - Discarding Message - Invalid or 
                   Corrupted. */

                return (ret);
            }

            return HandleAppRSR(&hdr, mtp3, ies, ieCount);

        case SCCP_MSG_RSC:
            if ((ret = SCCP_Decode(ies, &ieCount, event,
                                   &SCCP_RSC_Desc)) != ITS_SUCCESS)
            {
                /* Outgoing Message - Discarding Message - Invalid or 
                    Corrupted. */
                return (ret);
            }

            return HandleAppRSC(&hdr, mtp3, ies, ieCount);

        case SCCP_MSG_ERR:
     
            /*Q752 Implementation ERR Message Sent */
            SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.messageErrSent++;

            if ((ret = SCCP_Decode(ies, &ieCount, event,
                                   &SCCP_ERR_Desc)) != ITS_SUCCESS)
            {
                /* Outgoing Message - Discarding Message - Invalid or 
                   Corrupted. */

                return (ret);
            }

            return HandleAppERR(&hdr, mtp3, ies, ieCount);

        case SCCP_MSG_IT:
            if ((ret = SCCP_Decode(ies, &ieCount, event,
                                   &SCCP_IT_Desc)) != ITS_SUCCESS)
            {
                /* Outgoing Message - Discarding Message - Invalid or 
                   Corrupted. */

                return (ret);
            }

            return HandleAppIT(&hdr, mtp3, ies, ieCount);

        default:
            SCCP_ERROR(("SCOCHandleAPPMsg_PRC: Invalid msg type.\n"));
            return (ITS_ENOCONN);
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
 *  Notes:
 *
 *  See Also:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  gharipriya 12-10-2006 Bug Id 4472,    Remove the check for SSN for  
 *                        4366            DT1/DT2           
 *
 *  gharipriya 25-09-2006 Bug ID:4359     DT1/DT2/ED pegs Implementation.
 *
 ****************************************************************************/
int
SCOCHandleSCRCMsg_PRC(MTP3_HEADER* mtp3, ITS_OCTET mType,
                        ITS_SCCP_IE* ies, int ieCount,
                        ITS_UINT pc, ITS_OCTET ssn, ITS_BOOLEAN needCouple)
{
    ITS_HDR hdr;
    ITS_EVENT event;
    int ret = ITS_EINVALIDARGS;
    ITS_BOOLEAN sendToApp = ITS_TRUE;
    ITS_OCTET ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

    SCCP_DEBUG(("SCOCHandleSCRCMsg_PRC\n"));

    PEG_IncrPeg(PRC_SCCP_Pegs, PEG_SCCP_REMOTE_MSG_RECEIVED);
    

    /*Q752 Implementation Message From Remote SS */ 
    SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.messageFromRemoteSS++;

    /* process based on type */
    switch (mType)
    {
        case SCCP_MSG_CR:
            ret = HandleDownCR(&hdr, mtp3, ies, ieCount, pc, ssn, needCouple);

            if (needCouple)
            {
                return (ret);
            }

            if (ret == ITS_SUCCESS)
            {
                ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
                ies[ieCount].param_length = sizeof(MTP3_HEADER);
                ies[ieCount].param_data.routingLabel = *mtp3;
                ieCount++;

                ret = SCCP_Encode(ies, ieCount, mType, &event, &hdr,
                                  &SCCP_CR_Desc);
            }
            else
            {
                SCCP_ERROR(("HandleSCRCMsg: Couldn't process message\n"));
                
                return ret;
            }
            break;

        case SCCP_MSG_CC:

            ret = HandleDownCC(&hdr, mtp3, ies, ieCount, &sendToApp);

            if (!sendToApp)
            {
                return ret;
            }

            if (ret == ITS_SUCCESS)
            {
                ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
                ies[ieCount].param_length = sizeof(MTP3_HEADER);
                ies[ieCount].param_data.routingLabel = *mtp3;
                ieCount++;

                ret = SCCP_Encode(ies, ieCount, mType, &event, &hdr,
                                  &SCCP_CC_Desc);
            }
            else
            {
                SCCP_ERROR(("HandleSCRCMsg: Couldn't process message\n"));
                SCCP_Alarm_PRC(656, __FILE__, __LINE__, "family=%s", "PRC");

                return ret;
            }
            break;

        case SCCP_MSG_CREF:
            ret = HandleDownCREF(&hdr, mtp3, ies, ieCount, &sendToApp);

            if (!sendToApp)
            {
                return ret;
            }

            if (ret == ITS_SUCCESS)
            {
                ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
                ies[ieCount].param_length = sizeof(MTP3_HEADER);
                ies[ieCount].param_data.routingLabel = *mtp3;
                ieCount++;

                ret = SCCP_Encode(ies, ieCount, mType, &event, &hdr,
                                  &SCCP_CREF_Desc);
            }
            else
            {
                SCCP_ERROR(("HandleSCRCMsg: Couldn't process message\n"));
                SCCP_Alarm_PRC(657, __FILE__, __LINE__, "family=%s", "PRC");

                return ret;
            }
            break;

        case SCCP_MSG_RLSD:
            ret = HandleDownRLSD(&hdr, mtp3, ies, ieCount, &sendToApp);

            if (!sendToApp)
            {
                return ret;
            }

            if (ret == ITS_SUCCESS)
            {
                ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
                ies[ieCount].param_length = sizeof(MTP3_HEADER);
                ies[ieCount].param_data.routingLabel = *mtp3;
                ieCount++;

                ret = SCCP_Encode(ies, ieCount, mType, &event, &hdr,
                                  &SCCP_RLSD_Desc);
            }
            else
            {
                SCCP_ERROR(("HandleSCRCMsg: Couldn't process message\n"));

                SCCP_Alarm_PRC(658, __FILE__, __LINE__, "family=%s", "PRC");

                return ret;
            }
            break;

        case SCCP_MSG_RLC:
            ret = HandleDownRLC(&hdr, mtp3, ies, ieCount, &sendToApp);

            if (!sendToApp)
            {
                return ret;
            }

            if (ret == ITS_SUCCESS)
            {
                ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
                ies[ieCount].param_length = sizeof(MTP3_HEADER);
                ies[ieCount].param_data.routingLabel = *mtp3;
                ieCount++;

                ret = SCCP_Encode(ies, ieCount, mType, &event, &hdr,
                                  &SCCP_RLC_Desc);
            }
            else
            {
                SCCP_ERROR(("HandleSCRCMsg: Couldn't process message\n"));

                return ret;
            }
            break;

        case SCCP_MSG_DT1:
                                                                                                                             
            ret = HandleDownDT1(&hdr, mtp3, ies, ieCount, &sendToApp);

            if (!sendToApp)
            {
                return ret;
            }

            if (ret == ITS_SUCCESS)
            {
                ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
                ies[ieCount].param_length = sizeof(MTP3_HEADER);
                ies[ieCount].param_data.routingLabel = *mtp3;
                ieCount++;

                ret = SCCP_Encode(ies, ieCount, mType, &event, &hdr,
                                  &SCCP_DT1_Desc);
            }
            else
            {
                SCCP_ERROR(("HandleSCRCMsg: Couldn't process message\n"));

                return ret;
            }
            break;

        case SCCP_MSG_DT2:
 
            ret = HandleDownDT2(&hdr, mtp3, ies, ieCount, &sendToApp);

            if (!sendToApp)
            {
                return ret;
            }

            if (ret == ITS_SUCCESS)
            {
                ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
                ies[ieCount].param_length = sizeof(MTP3_HEADER);
                ies[ieCount].param_data.routingLabel = *mtp3;
                ieCount++;

                ret = SCCP_Encode(ies, ieCount, mType, &event, &hdr,
                                  &SCCP_DT2_Desc);
            }
            else
            {
                SCCP_ERROR(("HandleSCRCMsg: Couldn't process message\n"));

                return ret;
            }
            break;

        case SCCP_MSG_AK:
            ret = HandleDownAK(&hdr, mtp3, ies, ieCount, &sendToApp);

            if (!sendToApp)
            {
                return ret;
            }

            if (ret == ITS_SUCCESS)
            {
                ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
                ies[ieCount].param_length = sizeof(MTP3_HEADER);
                ies[ieCount].param_data.routingLabel = *mtp3;
                ieCount++;

                ret = SCCP_Encode(ies, ieCount, mType, &event, &hdr,
                                  &SCCP_AK_Desc);
            }
            else
            {
                SCCP_ERROR(("HandleSCRCMsg: Couldn't process message\n"));

                return ret;
            }
            break;

        case SCCP_MSG_ED:

            ret = HandleDownED(&hdr, mtp3, ies, ieCount, &sendToApp);

            if (!sendToApp)
            {
                return ret;
            }

            if (ret == ITS_SUCCESS)
            {
                ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
                ies[ieCount].param_length = sizeof(MTP3_HEADER);
                ies[ieCount].param_data.routingLabel = *mtp3;
                ieCount++;

                ret = SCCP_Encode(ies, ieCount, mType, &event, &hdr,
                                  &SCCP_ED_Desc);
            }
            else
            {
                SCCP_ERROR(("HandleSCRCMsg: Couldn't process message\n"));

                return ret;
            }
            break;

        case SCCP_MSG_EA:
            ret = HandleDownEA(&hdr, mtp3, ies, ieCount, &sendToApp);

            if (!sendToApp)
            {
                return ret;
            }

            if (ret == ITS_SUCCESS)
            {
                ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
                ies[ieCount].param_length = sizeof(MTP3_HEADER);
                ies[ieCount].param_data.routingLabel = *mtp3;
                ieCount++;

                ret = SCCP_Encode(ies, ieCount, mType, &event, &hdr,
                                  &SCCP_EA_Desc);
            }
            else
            {
                SCCP_ERROR(("HandleSCRCMsg: Couldn't process message\n"));

                return ret;
            }
            break;

        case SCCP_MSG_RSR:
            ret = HandleDownRSR(&hdr, mtp3, ies, ieCount, &sendToApp);

            if (!sendToApp)
            {
                return ret;
            }

            if (ret == ITS_SUCCESS)
            {
                ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
                ies[ieCount].param_length = sizeof(MTP3_HEADER);
                ies[ieCount].param_data.routingLabel = *mtp3;
                ieCount++;

                ret = SCCP_Encode(ies, ieCount, mType, &event, &hdr,
                                  &SCCP_RSR_Desc);
            }
            else
            {
                SCCP_ERROR(("HandleSCRCMsg: Couldn't process message\n"));

                return ret;
             }
             break;

        case SCCP_MSG_RSC:
            ret = HandleDownRSC(&hdr, mtp3, ies, ieCount, &sendToApp);

            if (!sendToApp)
            {
                return ret;
            }

            if (ret == ITS_SUCCESS)
            {
                ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
                ies[ieCount].param_length = sizeof(MTP3_HEADER);
                ies[ieCount].param_data.routingLabel = *mtp3;
                ieCount++;

                ret = SCCP_Encode(ies, ieCount, mType, &event, &hdr,
                                  &SCCP_RSC_Desc);
            }
            else
            {
                SCCP_ERROR(("HandleSCRCMsg: Couldn't process message\n"));

                return ret;
            }
            break;

        case SCCP_MSG_ERR:
            ret = HandleDownERR(&hdr, mtp3, ies, ieCount, &sendToApp);

            if (!sendToApp)
            {
                return ret;
            }

            if (ret == ITS_SUCCESS)
            {
                ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
                ies[ieCount].param_length = sizeof(MTP3_HEADER);
                ies[ieCount].param_data.routingLabel = *mtp3;
                ieCount++;

                ret = SCCP_Encode(ies, ieCount, mType, &event, &hdr,
                                  &SCCP_ERR_Desc);
            }
            else
            {
                SCCP_ERROR(("HandleSCRCMsg: Couldn't process message\n"));

                return ret;
            }
            break;

        case SCCP_MSG_IT:
            ret = HandleDownIT(&hdr, mtp3, ies, ieCount, &sendToApp);

            if (!sendToApp)
            {
                return ret;
            }

            if (ret == ITS_SUCCESS)
            {
                ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
                ies[ieCount].param_length = sizeof(MTP3_HEADER);
                ies[ieCount].param_data.routingLabel = *mtp3;
                ieCount++;

                ret = SCCP_Encode(ies, ieCount, mType, &event, &hdr,
                                  &SCCP_IT_Desc);
            }
            else
            {
                SCCP_ERROR(("HandleSCRCMsg: Couldn't process message\n"));

                return ret;
            }
            break;

        default:
            SCCP_ERROR(("SCOCHandleSCRCMsg_PRC: Discard unknown type\n"));
            break;
    }

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    hdr.type = ITS_SCCP;

    event.src = ITS_SCCP_SRC;
    ITS_SET_CTXT(&event.data[1], hdr.context.conref);

    /* send to the application */
    ret = SCCP_SendToAPP(mtp3, &hdr, mType, &event);

    ITS_EVENT_TERM(&event);

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
 ****************************************************************************/
int
SCOCHandleTimer_PRC(ITS_TimerData* td)
{
    SCCP_CONN_CTXT copyCtxt, *foundCtxt = NULL;
    ITS_CTXT        tempConnRef;
    int error;


    memcpy(&copyCtxt, td->context, sizeof(SCCP_CONN_CTXT));
    tempConnRef = copyCtxt.connRef;

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_CTXT, 
                                           (ITS_OCTET *)&tempConnRef, 
                                           sizeof(tempConnRef), &error);

    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("SCOCHandleTimer_PRC: Couldn't acquire mutex."
                            "\n"));

                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("SCOCHandleTimer_PRC: DSM Row Locked.\n"));

                break;
            case (ITS_ENOTFOUND):
                SCCP_WARNING(("SCOCHandleTimer_PRC: Can't find Connection"
                               "Reference in table.\n"));

                break;
        }

        return (ITS_ENOCONN);
    }

    copyCtxt = *foundCtxt;

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ITU_SCCP_CTXT,
                       (ITS_OCTET *)&tempConnRef, 
                       sizeof(tempConnRef), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("SCOCHandleTimer_PRC: DSM unable to free Reference.\n"));

        /* Unable to Commit Session Context to CTXT Table. */
    }

    if (isSCCPBackup)
    {
       SCCP_DeleteLocalReference_PRC(copyCtxt.connRef);

       /* FIXME::
        * We may need to send Indication to Application
        * to clear Application data base, if there
        */
       return ITS_SUCCESS;
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    switch (copyCtxt.state)
    {
        case SCCP_CONN_OUT_PEND:
        case SCCP_CONN_IN_PEND:
            SCCP_ERROR(("SCOCHandleTimer_PRC: Connection segment expired: ref %04x\n",copyCtxt.connRef));

            /* Message - Inbound or Outbound Message Segment not received 
              within time limit. */

            /* send CREF to originator */
            if (copyCtxt.state == SCCP_CONN_IN_PEND)
            {
                SendCREF(&copyCtxt, SCCP_REF_CONN_EXPIRY, ITS_FALSE);
            }
            else if (copyCtxt.state == SCCP_CONN_OUT_PEND)
            {
                SendCREF(&copyCtxt, SCCP_REF_CONN_EXPIRY, ITS_TRUE);
            }

            SCCP_DeleteLocalReference_PRC(copyCtxt.connRef);
            break;

        case SCCP_OUT_RESET_PEND:
        case SCCP_IN_RESET_PEND:
            SCCP_ERROR(("SCOCHandleTimer_PRC: Reset expired: ref %04x\n",
                        copyCtxt.connRef));

            SCCP_DEBUG(("On expiry of Reset Timer RLSD is send \
                         to the other end\n")); 

            SendRLSD(&copyCtxt, SCCP_REF_CONN_EXPIRY, ITS_FALSE);
            break;

        case SCCP_OUT_RELEASE_PEND:
        case SCCP_IN_RELEASE_PEND:
            SCCP_ERROR(("SCOCHandleTimer_PRC: HandleTIMER: Release expired:"
                        "ref %04x\n",copyCtxt.connRef));

            /* SCCP Context - Inbound or Outbound Release timer expired - 
               Sending Release Complete. */

            /* delete local context, send RLC to originator */
            if (copyCtxt.state == SCCP_IN_RELEASE_PEND)
            {
                SendRLC(&copyCtxt, SCCP_REF_CONN_EXPIRY, ITS_FALSE);
            }
            else if (copyCtxt.state == SCCP_OUT_RELEASE_PEND)
            {
                SendRLSD(&copyCtxt,  SCCP_REF_CONN_EXPIRY, ITS_FALSE);

                SCCP_DEBUG(("SCOCHandleTimer_PRC:Released send to MTP3 After"
                            "Timer Expiry\n"));
                break;

            }

            SCCP_DeleteLocalReference_PRC(copyCtxt.connRef);
            break;

        default:
            if (td->serial == copyCtxt.sendInactivity)
            {
                SCCP_DEBUG(("SCOCHandleTimer_PRC: SendInactivity: ref %04x\n",
                             copyCtxt.connRef));

                /* send inactivity */
                SendIT(&copyCtxt);
            }
            else if (td->serial == copyCtxt.receiveInactivity)
            {
                SCCP_DEBUG(("SCOCHandLeTimer_PRC: RecieveInactivity: ref %04x" 
                            "\n",copyCtxt.connRef));

                /* receive inactivity */    
                /* should release connection on this. */
                PEG_IncrPeg(PRC_SCCP_Pegs, PEG_SCCP_TIMER_TIAR_EXPIRY);
       
                /*Q752 Implementation Timer Tair Expiry */
                SccpGenOmImage_PRC[omBuf.activeOm].SCCPGenPegs.timerTiarExpiry++;
 
                SendRLSD(&copyCtxt, SCCP_RLC_INACT_EXPIRY, ITS_FALSE);
            }
            else if (td->serial == copyCtxt.releaseTimer)
            {
                SCCP_DEBUG(("SCOCHandleTimer_PRC: Release Timer Expired : ref %04x\n",
                          copyCtxt.connRef));

#if defined(CONNECTION_TIMERS)

                copyCtxt.repeatReleaseTimer =
                    TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                     SCCP_T_repeatRelease),
                                &copyCtxt, sizeof(SCCP_CONN_CTXT));

                copyCtxt.intervalTimer =
                    TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                     SCCP_T_interval),
                                &copyCtxt, sizeof(SCCP_CONN_CTXT));

#endif

                SendRLSD(&copyCtxt, SCCP_RLC_RPC_ERROR,ITS_FALSE);
            }
            else if (td->serial == copyCtxt.repeatReleaseTimer)
            {
                SCCP_DEBUG(("SCOCHandleTimer_PRC: Repeat Release Timer Expired : ref %04x\n",
                          copyCtxt.connRef));

#if defined(CONNECTION_TIMERS)

                copyCtxt.repeatReleaseTimer =
                    TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&PRC_SCCP_Timers,
                                                     SCCP_T_repeatRelease),
                                &copyCtxt, sizeof(SCCP_CONN_CTXT));

#endif

                SendRLSD(&copyCtxt, SCCP_RLC_RPC_ERROR,ITS_FALSE);
            }
            else if (td->serial == copyCtxt.intervalTimer)
            {
                SCCP_DEBUG(("SCOCHandleTimer_PRC: Interval Timer Expired : ref %04x\n",
                          copyCtxt.connRef));

                if (copyCtxt.repeatReleaseTimer)
                {
                    TIMERS_CancelTimer(copyCtxt.repeatReleaseTimer);
                }

                SCCP_DeleteLocalReference_PRC(copyCtxt.connRef);
            }
            else
            {
                SCCP_DEBUG(("SCOCHandleTimer_PRC: Unknown timer: ref %04x"
                           " serial  %08x\n",copyCtxt.connRef, td->serial));
            }
            break;
    }

    return (ITS_SUCCESS);
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
int
SCOC_PutDataInFragList(ITS_UINT *startKey, ITS_UINT segRefNum, ITS_OCTET *data, 
                  ITS_OCTET len)
{
    SCCP_DATA_FRAG* fptr;  
    int size = sizeof(SCCP_DATA_FRAG);
    int error;
    int key = *startKey;

    if(*startKey == 0)
    {
        *startKey = segRefNum | 0x80000000;
        key = *startKey;

        fptr = (SCCP_DATA_FRAG *)DSM_Find(DSM_SccpFtGroupId,
                                          DSM_TABLE_ITU_SCCP_CTXT,
                                          (ITS_OCTET *)&key, 
                                          sizeof(key), &error);

        if (error != ITS_ENOTFOUND && (error != ITS_SUCCESS))
        {
            SCCP_CRITICAL(("PutDataInFragList: Couldn't alloc segment.\n"));

            /* Segmention Fragment already in use in CTXT Table. */
    
            return (ITS_ENOMEM);
        }

        if (error == ITS_ENOTFOUND)
        {

            fptr = (SCCP_DATA_FRAG *) DSM_Alloc(DSM_SccpFtGroupId,
                                                DSM_TABLE_ITU_SCCP_CTXT,
                                                (ITS_OCTET *)&key, 
                                                sizeof(key), size, 
                                                &error);

            if (error != ITS_SUCCESS)
            {
                switch(error)
                {
                    case (ITS_EBADMUTEX):
                        SCCP_CRITICAL(("GetNextLocalRef: Couldn't acquire"
                                       " mutex.\n"));
                        break;
                    case (ITS_ENOMEM):
                        SCCP_CRITICAL(("GetNextLocalRef: No Memory.\n"));
                        break;
                }

                /* Unable to Allocate Memory for Segmention Fragment in CTXT 
                   Table. */

                return (error);
            }
        }

        memcpy(&(fptr->data[fptr->len]), data, len);
        fptr->len += len;

        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&key, 
                           sizeof(key), fptr);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("PutDataInFragList: Couldn't add context.\n"));

            /* Unable to Commit Segmention Fragment to CTXT Table. */

            return (error);
        }
    }
    else
    {
        fptr = (SCCP_DATA_FRAG *)DSM_Find(DSM_SccpFtGroupId,
                                          DSM_TABLE_ITU_SCCP_CTXT,
                                          (ITS_OCTET *)&key, 
                                          sizeof(key), &error);

        if (error == ITS_ENOTFOUND)
        {
            SCCP_CRITICAL(("PutDataInFragList: Couldn't alloc segment.\n"));
    
            /* Segmention Fragment not found in CTXT Table.*/

            return (ITS_ENOMEM);
        }

        memcpy(&(fptr->data[fptr->len]), data, len);
        fptr->len += len;

        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ITU_SCCP_CTXT,
                           (ITS_OCTET *)&key, 
                           sizeof(key), fptr);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("PutDataInFragList: Couldn't add context.\n"));

            /* Unable to Commit Segmention Fragment to CTXT Table. */

            return (error);
        }
    }

    return ITS_SUCCESS;
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
int
SCOC_GetDataFromFragList(ITS_OCTET *data, ITS_UINT *startKey)
{
    SCCP_DATA_FRAG* fptr;
    int error = 0;
    int key = *startKey;

    fptr = (SCCP_DATA_FRAG *)DSM_Find(DSM_SccpFtGroupId,
                                      DSM_TABLE_ITU_SCCP_CTXT,
                                      (ITS_OCTET *)&key, 
                                      sizeof(key), &error);

    if (error == ITS_ENOTFOUND)
    {
        SCCP_CRITICAL(("GetDataInFragList: Couldn't alloc segment.\n"));

        /* Segmention Fragment not found in CTXT Table. */

        return (ITS_ENOMEM);
    }

    memcpy(data, fptr->data, fptr->len);

    error = DSM_Free(DSM_SccpFtGroupId,
                     DSM_TABLE_ITU_SCCP_CTXT, 
                     (ITS_OCTET *)&key,
                     sizeof(key), fptr);

    *startKey = 0;
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("GetDataFromFragList: DSM unable to free Segment.\n"));

        /* Unable to Free Segment Reference in CTXT Table. */
    }
    
    return ITS_SUCCESS;
}
