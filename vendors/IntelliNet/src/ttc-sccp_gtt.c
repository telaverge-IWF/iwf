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
 *  ID: $Id: ttc-sccp_gtt.c,v 9.3 2008/07/18 05:45:32 ssingh Exp $
 *
 * LOG: $Log: ttc-sccp_gtt.c,v $
 * LOG: Revision 9.3  2008/07/18 05:45:32  ssingh
 * LOG: SDS ID:: ID :: D0240 Warning removal for Solaris Compilation
 * LOG:
 * LOG: Revision 9.2  2008/06/17 06:38:02  nvijikumar
 * LOG: Updated for ITU over TTC support (Split Stack)
 * LOG: ACC-CG-SDS-SS7-V1.0.02::D7040,D7080
 * LOG:
 * LOG: Revision 9.1  2007/01/11 12:43:40  yranade
 * LOG: Merge changes from 6.5.3 and Lucent branches
 * LOG:
 * LOG: Revision 1.1.2.1  2006/12/23 10:05:37  randresol
 * LOG: Modifications to allow TTC and ITU stacks to run in parallel
 * LOG:
 * LOG: Revision 9.1.10.2  2006/09/25 13:53:52  mshanmugam
 * LOG: Removing the Q752 compilation flag
 * LOG:
 * LOG: Revision 9.1.10.1  2006/08/18 12:42:13  mshanmugam
 * LOG: Added new SCCP Pegs for Q.752 Implementation.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:42  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:53:47  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.14.1.12.3  2005/02/21 09:13:42  csireesh
 * LOG: OAM Validation Bug Fix
 * LOG:
 * LOG: Revision 7.1.14.1.12.2  2005/01/31 09:32:46  dsatish
 * LOG: ANSI over TTC, ANSI over PRC split stack changes merged in DVLP branch.
 * LOG:
 * LOG: Revision 7.1.14.1.12.1  2004/12/17 03:57:44  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.1.14.1.6.1  2004/10/25 20:34:12  randresol
 * LOG: Start Japan SS7 Implementation
 * LOG:
 * LOG: Revision 7.1.14.1  2004/06/22 11:47:53  csireesh
 * LOG: ALARMS and PEGS Propogation from TCS branch.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:28  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.3  2002/08/16 22:07:09  mmiers
 * LOG: Include China variant.
 * LOG:
 * LOG: Revision 6.2  2002/03/07 22:21:30  mmiers
 * LOG: Merge ITU SCCP.  Doesn't build (have to work on CPC impl).
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:39  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.5  2002/01/02 19:56:08  mmiers
 * LOG: Convert to using long names (everything but TCAP).
 * LOG:
 * LOG: Revision 5.4  2001/09/26 21:28:44  mmiers
 * LOG: SRM is essentially complete, but a few more tricks are needed.
 * LOG: Other stuff is more fixme removal.
 * LOG:
 * LOG: Revision 5.3  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.2  2001/09/05 21:07:22  mmiers
 * LOG: Small corrections.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:28  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.4  2001/06/19 20:10:54  mmiers
 * LOG: Data structure rename.
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
 * LOG: Revision 3.2  2001/02/06 17:58:42  mmiers
 * LOG: About 90% thread safe.  SCCP connection oriented isn't, neither
 * LOG: are simultaneous messages within a TCAP transaction.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:36  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:31:36  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.5  1999/08/27 00:51:21  mmiers
 * LOG:
 * LOG:
 * LOG: Commit more work, mostly just formatting, but include ies in
 * LOG: GTT callback.  User can really get himself in trouble now.
 * LOG:
 * LOG: Revision 1.4  1999/08/26 23:45:00  labuser
 * LOG:
 * LOG:
 * LOG: Alter GTT to include original PC (if any) and SSN (if any).
 * LOG:
 * LOG: Revision 1.3  1999/06/29 15:24:23  mmiers
 * LOG:
 * LOG:
 * LOG: Modify global title behavior a bit (allow setting of DPC only).
 * LOG:
 * LOG: Revision 1.2  1999/06/22 16:17:25  mmiers
 * LOG:
 * LOG:
 * LOG: Add in global title translation.
 * LOG:
 * LOG: Revision 1.1  1999/03/17 18:39:48  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol commit.  Still have to finish TCAP.
 * LOG:
 * LOG: Revision 1.3  1998/11/11 03:47:27  mmiers
 * LOG: Clean up some SCCP stuff.
 * LOG:
 * LOG: Revision 1.2  1998/10/15 01:19:13  mmiers
 * LOG: Remove assert().  We shouldn't terminate, we should gracefully work
 * LOG: around errors.
 * LOG:
 * LOG: More work on SCCP COC.  Added connection timer, release timer,
 * LOG: reset timer.  Check for proper handling of missing information.
 * LOG:
 * LOG: Revision 1.1  1998/09/28 17:37:52  mmiers
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
#include <stdlib.h>

#undef ANSI
#undef CCITT

#if defined(SPLIT_STACK) && defined(USE_TTC_SCCP)
#define TTC
#endif

#if !defined(PRC) && !defined(TTC)
#define CCITT
#endif

#include <its.h>
#include <its_hash.h>
#include <its_mutex.h>

#ident "$Id: ttc-sccp_gtt.c,v 9.3 2008/07/18 05:45:32 ssingh Exp $"

#if defined(PRC) || defined (USE_PRC_SCCP)
#undef CCITT
#define PRC
#include <china/sccp.h>
#elif defined(TTC) || defined (USE_TTC_SCCP)
#undef CCITT
#if !defined(TTC)
#define TTC
#endif
#include <japan/sccp.h>
#else
#include <itu/sccp.h>
#endif

#include "sccp_intern.h"

/* Q752 Implementation */
extern sccpOmBuffer omBuf;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Perform global title translation callbacks.
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
SCCP_GTTTranslate_TTC(MTP3_HEADER *mtp3,
                        ITS_UINT *dpc, ITS_OCTET ai,
                        ITS_UINT pc, ITS_OCTET ssn,
                        ITS_OCTET* gttInfo, ITS_USHORT gttLen,
                        SCCP_ADDR* transAddr,
                        ITS_SCCP_IE *ies, int ieCount)
{
    SCCP_CALLBACK_DATA   data;

    data.mtp3 = mtp3;
    data.addrInd = ai;
    data.pc = pc;
    data.ssn = ssn;
    data.gttInfo = gttInfo;
    data.gttLen = gttLen;
    data.dpc = 0;
    data.transSuccess = ITS_FALSE;
    data.translation = transAddr;
    data.ies = ies;
    data.ieCount = ieCount;
    int ret;
    /* Incr GGT request counter */
    PEG_IncrPeg(TTC_SCCP_Pegs, PEG_SCCP_REMOTE_GTT_REQUEST);
   
    if ((ret = CALLBACK_CallCallbackListNoLock(SCCP_GlobalTitleTranslator,
                                               NULL, (void *)&data)) != ITS_SUCCESS)
    {
        /* Q752 Implementation Routing Failure- no translation for Address of such nature */ 
        SccpGenOmImage_TTC[omBuf.activeOm].SCCPGenPegs.routingFailureNoTransAddr++;
 
        return ret;
    }
 
    if (data.transSuccess == ITS_FALSE)
    {
        PEG_IncrPeg(TTC_SCCP_Pegs, PEG_SCCP_REMOTE_GTT_FAILURE);

        /* Q752 Implementation Routing Failure No translation for this specific address */
        SccpGenOmImage_TTC[omBuf.activeOm].SCCPGenPegs.routingFailureNoTransSpecificAddr++;

        return ITS_EMISSMAND;
    }
    else
    {
        *dpc = data.dpc;

        /* Incr GTT success counter */
        PEG_IncrPeg(TTC_SCCP_Pegs, PEG_SCCP_REMOTE_GTT_SUCCESS);

        return ITS_SUCCESS;
    }

    /* return (data.transSuccess ? ITS_SUCCESS : ITS_EMISSMAND); */
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Perform user intervention callbacks.
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
SCCP_UserIntervention_TTC(MTP3_HEADER *mtp3,
                            ITS_OCTET addrInd,
                            ITS_UINT pc, ITS_OCTET ssn,
                            ITS_OCTET *gttInfo, ITS_USHORT gttLen,
                            SCCP_ADDR* transAddr,
                            ITS_SCCP_IE *ies, int ieCount)
{
    SCCP_CALLBACK_DATA   data;
    int ret;

    data.mtp3 = mtp3;
    data.addrInd = addrInd;
    data.pc = pc;
    data.ssn = ssn;
    data.gttInfo = gttInfo;
    data.gttLen = gttLen;
    data.dpc = pc;
    data.transSuccess = ITS_TRUE;
    data.translation = transAddr;
    data.ies = ies;
    data.ieCount = ieCount;

    if ((ret = CALLBACK_CallCallbackListNoLock(SCCP_SSNRoutingCallbacks,
                                               NULL, (void *)&data)) != ITS_SUCCESS)
    {
        return ret;
    }

    /* Incr User Intervention request counter */

    if (data.transSuccess)
    {
        MTP3_RL_SET_DPC_VALUE(((MTP3_HEADER *)data.mtp3)->label, data.pc);
    }

    return (data.transSuccess ? ITS_SUCCESS : ITS_EMISSMAND);
}

