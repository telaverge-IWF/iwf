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
 *  ID: $Id: ttc-sclc.c,v 9.4 2008/07/18 05:45:33 ssingh Exp $
 *
 * LOG: $Log: ttc-sclc.c,v $
 * LOG: Revision 9.4  2008/07/18 05:45:33  ssingh
 * LOG: SDS ID:: ID :: D0240 Warning removal for Solaris Compilation
 * LOG:
 * LOG: Revision 9.3  2008/06/17 06:38:02  nvijikumar
 * LOG: Updated for ITU over TTC support (Split Stack)
 * LOG: ACC-CG-SDS-SS7-V1.0.02::D7040,D7080
 * LOG:
 * LOG: Revision 9.2  2008/06/04 10:38:48  ssingh
 * LOG: ALU porting, B-0100LX-LUSG-00 (june 04,2008 base)
 * LOG:
 * LOG: Revision 9.1  2007/01/11 12:43:40  yranade
 * LOG: Merge changes from 6.5.3 and Lucent branches
 * LOG:
 * LOG: Revision 1.1.2.4  2007/07/27 13:08:47  kramesh
 * LOG: Ported the 16 bit pc changes from B-0100SL-CBSG-RST16 branch.
 * LOG: Ref SDS : ACC-FemtoBSG-16BitPC-SDS-GEN-V1.0
 * LOG:
 * LOG: Revision 1.1.2.3  2007/02/13 04:01:37  raghavendrabk
 * LOG: Changed alarm format to put family at beginning
 * LOG:
 * LOG: Revision 1.1.2.2  2007/02/02 14:18:22  raghavendrabk
 * LOG: Parallel Stack changes for Alarms and Statistics
 * LOG:
 * LOG: Revision 1.1.2.1  2006/12/23 10:05:37  randresol
 * LOG: Modifications to allow TTC and ITU stacks to run in parallel
 * LOG:
 * LOG: Revision 9.3.4.3  2006/10/13 09:49:43  mshanmugam
 * LOG: Fix for Bug Ids 4472 and removing the check for configured SSN.
 * LOG:
 * LOG: Revision 9.3.4.2  2006/09/25 13:48:17  mshanmugam
 * LOG: Fix for Bug ids 4361,4329,4328,4357,4330 and removing the Q752 compilation flag
 * LOG:
 * LOG: Revision 9.3.4.1  2006/08/18 12:35:48  mshanmugam
 * LOG: Added new SCCP Pegs for Q.752 Implementation
 * LOG:
 * LOG: Revision 9.3  2005/06/02 12:34:20  adutta
 * LOG: Fixed issue# 1920
 * LOG:
 * LOG: Revision 9.2  2005/05/25 06:30:53  adutta
 * LOG: Segmentation implemented
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:42  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.6  2005/03/21 13:53:47  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.4.2.1.6.1.12.5  2005/02/21 09:13:42  csireesh
 * LOG: OAM Validation Bug Fix
 * LOG:
 * LOG: Revision 7.4.2.1.6.1.12.4  2005/01/31 09:32:46  dsatish
 * LOG: ANSI over TTC, ANSI over PRC split stack changes merged in DVLP branch.
 * LOG:
 * LOG: Revision 7.4.2.1.6.1.12.3  2005/01/25 07:23:00  csireesh
 * LOG: Fixed Bug 1445 and removed Tab spaces
 * LOG:
 * LOG: Revision 7.4.2.1.6.1.12.2  2004/12/29 13:53:14  csireesh
 * LOG: SCCP bug propogation and OAM Changes
 * LOG:
 * LOG: Revision 7.4.2.1.6.1.12.1  2004/12/17 03:57:44  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.4.2.1.6.1.6.1  2004/10/25 20:34:12  randresol
 * LOG: Start Japan SS7 Implementation
 * LOG:
 * LOG: Revision 7.4.2.1.6.1  2004/06/22 11:47:53  csireesh
 * LOG: ALARMS and PEGS Propogation from TCS branch.
 * LOG:
 * LOG: Revision 7.4.2.1  2003/05/22 08:38:28  aganguly
 * LOG: XUDT with HopCounter violation, XUDTS is sent by the stack.
 * LOG:
 * LOG: Revision 7.4  2003/02/05 17:40:27  aganguly
 * LOG: Changes for SCCP alarms: clean up of unwanted alarms left for Release 6.4
 * LOG:
 * LOG: Revision 7.3  2003/01/16 16:23:34  mmiers
 * LOG: Tandem port, large context changes.
 * LOG:
 * LOG: Revision 7.2  2002/11/04 22:26:37  ngoel
 * LOG: swap clp, cdp before sending UDTS/XUDTS
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:28  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.12  2002/08/16 22:07:09  mmiers
 * LOG: Include China variant.
 * LOG:
 * LOG: Revision 6.11  2002/07/29 18:03:12  ngoel
 * LOG: correct peg type
 * LOG:
 * LOG: Revision 6.10  2002/07/05 21:12:01  mmiers
 * LOG: Flag fixing
 * LOG:
 * LOG: Revision 6.9  2002/07/05 18:52:26  ngoel
 * LOG: remove extra return
 * LOG:
 * LOG: Revision 6.8  2002/06/21 22:49:38  mmiers
 * LOG: Adding support for China variant
 * LOG:
 * LOG: Revision 6.7  2002/05/20 21:11:50  mmiers
 * LOG: Flip PCs.  Add OAM implementation.  Try chaining fix.
 * LOG:
 * LOG: Revision 6.6  2002/04/17 23:02:25  hdivoux
 * LOG: FT/HA integration.
 * LOG:
 * LOG: Revision 6.5  2002/03/22 14:32:13  ngoel
 * LOG: Add error handling
 * LOG:
 * LOG: Revision 6.4  2002/03/20 23:30:18  mmiers
 * LOG: Many warnings removed.
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
 * LOG: Revision 5.5  2002/01/02 21:02:44  mmiers
 * LOG: Back out the routing label change.  It breaks hybrid stack builds.
 * LOG:
 * LOG: Revision 5.4  2002/01/02 19:56:08  mmiers
 * LOG: Convert to using long names (everything but TCAP).
 * LOG:
 * LOG: Revision 5.3  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.2  2001/09/06 17:25:02  mmiers
 * LOG: Straighten out routing a bit.
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
 * LOG: Revision 3.2  2000/08/24 23:07:25  mmiers
 * LOG: Zero copy is in.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:36  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  1999/12/06 21:30:10  mmiers
 * LOG:
 * LOG:
 * LOG: Debug with HP's GDI.
 * LOG:
 * LOG: Revision 1.5.2.1  1999/12/06 21:27:30  mmiers
 * LOG:
 * LOG:
 * LOG: Debug with HP's GDI.
 * LOG:
 * LOG: Revision 1.5  1999/08/26 23:45:00  labuser
 * LOG:
 * LOG:
 * LOG: Alter GTT to include original PC (if any) and SSN (if any).
 * LOG:
 * LOG: Revision 1.4  1999/08/26 19:58:49  rsonak
 * LOG:
 * LOG:
 * LOG: Some protocol fixes.
 * LOG:
 * LOG: Revision 1.3  1999/06/21 23:20:40  mmiers
 * LOG:
 * LOG:
 * LOG: Fix UDTS transmission.
 * LOG:
 * LOG: Revision 1.2  1999/03/17 21:37:50  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol framework complete.  Now for implementation.
 * LOG:
 * LOG: Revision 1.1  1999/03/17 18:39:48  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol commit.  Still have to finish TCAP.
 * LOG:
 * LOG: Revision 1.16  1998/11/19 01:31:43  mmiers
 * LOG: Build with warning at max.  5 bugs found.
 * LOG:
 * LOG: Revision 1.15  1998/11/17 22:37:39  mmiers
 * LOG: Propagate SCMG (SSP/SSA)
 * LOG:
 * LOG: Revision 1.14  1998/11/17 03:08:54  mmiers
 * LOG: Finish off SCMG.
 * LOG:
 * LOG: Revision 1.13  1998/11/02 17:10:38  mmiers
 * LOG: Add information to trace output for tracking event dest.
 * LOG:
 * LOG: Revision 1.12  1998/10/29 03:11:18  mmiers
 * LOG: Handle UIS/UOS, UDTS/XUDTS correctly.  Need to work on SSA/SSP.
 * LOG:
 * LOG: Revision 1.11  1998/10/27 21:08:54  mmiers
 * LOG: Finish up round 1 of NMS/SCCP integration.
 * LOG:
 * LOG: Revision 1.10  1998/10/16 20:45:23  mmiers
 * LOG: The "NEW! And IMPROVED!" SCCP.  Let the bug reports begin.
 * LOG:
 * LOG: Revision 1.9  1998/10/16 01:44:47  mmiers
 * LOG: Put my current thoughts into bytes.  This stuff is f*cking confusing,
 * LOG: and needs review.
 * LOG:
 * LOG: Revision 1.8  1998/10/15 01:19:17  mmiers
 * LOG: Remove assert().  We shouldn't terminate, we should gracefully work
 * LOG: around errors.
 * LOG:
 * LOG: More work on SCCP COC.  Added connection timer, release timer,
 * LOG: reset timer.  Check for proper handling of missing information.
 * LOG:
 * LOG: Revision 1.7  1998/09/28 17:37:53  mmiers
 * LOG: More work on SCCP.  Starting to take better shape.
 * LOG:
 * LOG: Revision 1.6  1998/09/27 00:53:11  mmiers
 * LOG: Start cleaning up connectionless.
 * LOG:
 * LOG: Revision 1.5  1998/09/27 00:04:18  mmiers
 * LOG: More work on SCCP.
 * LOG:
 * LOG: Revision 1.4  1998/09/24 23:27:30  mmiers
 * LOG: Continue work on improved SCCP.
 * LOG:
 * LOG: Revision 1.3  1998/09/24 19:24:38  mmiers
 * LOG: More work on SCCP.
 * LOG:
 * LOG: Revision 1.2  1998/09/24 17:31:51  mmiers
 * LOG: More working with SCCP.
 * LOG:
 * LOG: Revision 1.1  1998/09/24 16:33:11  mmiers
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
#include <its_dsm.h>
#include <its_mutex.h>
#include <its_thread.h>
#include <its_route.h>
#include <its_tq_trans.h>

#ident "$Id: ttc-sclc.c,v 9.4 2008/07/18 05:45:33 ssingh Exp $"

#if defined(PRC)  || defined(USE_PRC_SCCP)
#undef CCITT
#define PRC
#include <china/sccp.h>
#elif defined(TTC)  || defined(USE_TTC_SCCP)
#undef  CCITT
#if !defined(TTC)
#define TTC
#endif
#include <japan/sccp.h>
#else
#include <itu/sccp.h>
#endif

#include "sccp_intern.h"

extern ITS_UINT         __local_seg_ref_number;

#define REASSEMBLY_TIMERS

/* Q752 Implementation */
extern sccpOmBuffer omBuf;

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
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  gharipriya  25-09-2006 Bug Id:4361   LUDTS Sent Peg implementation.
 *
 ****************************************************************************/
int
SCLCHandleRoutingFailure_TTC(MTP3_HEADER* mtp3, ITS_OCTET mType,
                               ITS_SCCP_IE* ies, int ieCount,
                               ITS_OCTET reason)
{
    int ret = ITS_SUCCESS, i;
    ITS_SCCP_IE lies[32];
    ITS_OCTET addrInd = 0, ssn = 0;
    MTP3_HEADER resp;
    ITS_UINT tmp;
    SCCP_PROT_CLASS* pclass = NULL;
    SCCP_DATA* data = NULL;
    ITS_USHORT lDataLen = 0;
    SCCP_LONG_DATA *lData = NULL;
    SCCP_HOP_COUNT* hop = NULL;
    ITS_OCTET dlen = 0;
    SCCP_ADDR *clp = NULL, *cdp = NULL;

    SCCP_DEBUG(("SCLCHandleRoutingFailure:\n"));


    /* Incr Routing Failure counter */
    PEG_IncrPeg(TTC_SCCP_Pegs, PEG_SCCP_ROUTING_FAILURE);

    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_PROTOCOL_CLASS)
        {
            pclass = &ies[i].param_data.protocolClass;
        }
        else if (ies[i].param_id == SCCP_PRM_DATA)
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
        else if (ies[i].param_id == SCCP_PRM_HOP_COUNTER)
        {
            hop = &ies[i].param_data.hopCount;
        }
        else if (ies[i].param_id == SCCP_PRM_LONG_DATA)
        {
            lData = &ies[i].param_data.longData;
            lDataLen = ies[i].param_data.longData.len;
        }
    }

    if (!clp)
    {
         SCCP_WARNING(("SCLCHandleRoutingFailure: Don't know who to inform\n"));

         return (ITS_SUCCESS);
    }

    if ((SCCP_DecodeAddr(clp, &addrInd, NULL, &ssn,
                         NULL, NULL) != ITS_SUCCESS) ||
        !(addrInd & SCCP_CPA_HAS_SSN))
    {
         SCCP_WARNING(("SCLCHandleRoutingFailure: Don't know who to inform\n"));

         return (ITS_SUCCESS);
    }


    switch (mType)
    {
    case SCCP_MSG_UDT:
        SCCP_DEBUG(("SCLCHandleRoutingFailure: Send UDTS\n"));

        if (pclass == NULL || data == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        if (!(pclass->pclass & SCCP_PCLASS_RET_ON_ERR))
        {
            SCCP_DEBUG(("SCLCHandleRoutingFailure: Return option not"
                        "present\n"));

            /* just discard */
            return (ITS_SUCCESS);
        }

        /* build the routing label */
        resp.sio = mtp3->sio;
        tmp = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        MTP3_RL_SET_OPC_VALUE(resp.label, tmp);
        tmp = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        MTP3_RL_SET_DPC_VALUE(resp.label, tmp);
        MTP3_RL_SET_SLS(resp.label, MTP3_RL_GET_SLS(mtp3->label));

        /* return cause */
        lies[0].param_id = SCCP_PRM_RETURN_CAUSE;
        lies[0].param_length = sizeof(SCCP_RET_CAUSE);
        lies[0].param_data.returnCause.cause = reason;

        /* calledParty */
        lies[1].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
        lies[1].param_length = sizeof(SCCP_ADDR);
        memcpy(&lies[1].param_data.calledPartyAddr, clp, sizeof(SCCP_ADDR));

        /* callingParty */
        lies[2].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
        lies[2].param_length = sizeof(SCCP_ADDR);
        memcpy(&lies[2].param_data.callingPartyAddr, cdp, sizeof(SCCP_ADDR));

        /* copy in data */
        lies[3].param_id = SCCP_PRM_DATA;
        lies[3].param_length = dlen;
        memcpy(lies[3].param_data.userData.data, data->data, dlen);

        return SCRCHandleSCLCMsg_TTC(&resp, SCCP_MSG_UDTS, lies, 4);

    case SCCP_MSG_XUDT:
        SCCP_DEBUG(("SCLCHandleRoutingFailure: Send XUDTS\n"));

        if (pclass == NULL || data == NULL || hop == NULL)
        {
            SCCP_ERROR(("SCLCHandleRoutingFailure: XUDT is missing"
                        "required arguments\n"));

            return (ITS_EINVALIDARGS);
        }

        if (!(pclass->pclass & SCCP_PCLASS_RET_ON_ERR))
        {
            SCCP_DEBUG(("SCLCHandleRoutingFailure: Return option not"
                        "present\n"));

            /* just discard */
            return (ITS_SUCCESS);
        }

        /* build the routing label */
        resp.sio = mtp3->sio;
        tmp = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        MTP3_RL_SET_OPC_VALUE(resp.label, tmp);
        tmp = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        MTP3_RL_SET_DPC_VALUE(resp.label, tmp);
        MTP3_RL_SET_SLS(resp.label, MTP3_RL_GET_SLS(mtp3->label));

        /* return cause */
        lies[0].param_id = SCCP_PRM_RETURN_CAUSE;
        lies[0].param_length = sizeof(SCCP_RET_CAUSE);
        lies[0].param_data.returnCause.cause = reason;

        /* hop counter */
        lies[1].param_id = SCCP_PRM_HOP_COUNTER;
        lies[1].param_length = sizeof(SCCP_HOP_COUNT);
        lies[1].param_data.hopCount.count = hop->count;

        /* calledParty */
        lies[2].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
        lies[2].param_length = sizeof(SCCP_ADDR);
        memcpy(&lies[2].param_data.calledPartyAddr, clp, sizeof(SCCP_ADDR));

        /* callingParty */
        lies[3].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
        lies[3].param_length = sizeof(SCCP_ADDR);
        memcpy(&lies[3].param_data.callingPartyAddr, cdp, sizeof(SCCP_ADDR));

        /* copy in data */
        lies[4].param_id = SCCP_PRM_DATA;
        lies[4].param_length = dlen;
        memcpy(lies[4].param_data.userData.data, data->data, dlen);

        return SCRCHandleSCLCMsg_TTC(&resp, SCCP_MSG_XUDTS, lies, 5);

    case SCCP_MSG_LUDT:
        SCCP_DEBUG(("SCLCHandleRoutingFailure: Send LUDTS\n"));

        /* Q752 Implementation */
        /* LUDTS Sent */
        SccpGenOmImage_TTC[omBuf.activeOm].SCCPGenPegs.messageLUDTSSent++;

        if (pclass == NULL || lData == NULL || hop == NULL)
        {
            SCCP_ERROR(("SCLCHandleRoutingFailure: LUDT is missing"
                        "required arguments\n"));


            return (ITS_EINVALIDARGS);
        }

        if (!(pclass->pclass & SCCP_PCLASS_RET_ON_ERR))
        {
            SCCP_DEBUG(("SCLCHandleRoutingFailure: Return option not"
                        "present\n"));

            /* just discard */
            return (ITS_SUCCESS);
        }

        /* build the routing label */
        resp.sio = mtp3->sio;
        tmp = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        MTP3_RL_SET_OPC_VALUE(resp.label, tmp);
        tmp = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        MTP3_RL_SET_DPC_VALUE(resp.label, tmp);
        MTP3_RL_SET_SLS(resp.label, MTP3_RL_GET_SLS(mtp3->label));

        /* return cause */
        lies[0].param_id = SCCP_PRM_RETURN_CAUSE;
        lies[0].param_length = sizeof(SCCP_RET_CAUSE);
        lies[0].param_data.returnCause.cause = reason;

        /* hop counter */
        lies[1].param_id = SCCP_PRM_HOP_COUNTER;
        lies[1].param_length = sizeof(SCCP_HOP_COUNT);
        lies[1].param_data.hopCount.count = hop->count;

        /* calledParty */
        lies[2].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
        lies[2].param_length = sizeof(SCCP_ADDR);
        memcpy(&lies[2].param_data.calledPartyAddr, clp, sizeof(SCCP_ADDR));

        /* callingParty */
        lies[3].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
        lies[3].param_length = sizeof(SCCP_ADDR);
        memcpy(&lies[3].param_data.callingPartyAddr, cdp, sizeof(SCCP_ADDR));

        /* copy in data */
        lies[4].param_id = SCCP_PRM_LONG_DATA;
        lies[4].param_data.longData.len = lDataLen;
        memcpy(lies[4].param_data.longData.data, lData->data, lDataLen);

        return SCRCHandleSCLCMsg_TTC(&resp, SCCP_MSG_LUDTS, lies, 5);

    case SCCP_MSG_UDTS:
    case SCCP_MSG_XUDTS:
    case SCCP_MSG_LUDTS:
        /* just discard */
        return (ITS_SUCCESS);
    }

    if (ret != ITS_SUCCESS)
    {
        SCCP_ERROR(("SCLCHandleRoutingFailure: Failed to handle "
                    "service message\n"));

    }

    return (ret);
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
 *  gharipriya 12-10-2006 Bug Id 4472            Remove the check for SSN  
 *
 *  gharipriya 25-09-2006 Bug Id 4330            UDT/XUDT  Pegs Implementation
 *
 *  csireesh  03-06-2005  Issue ID::1920         Hop Counter Check Added
 *
 *  csireesh  20-05-2005  ID::R0070 to R0130     Segmentation Implementation
 *
 ****************************************************************************/
int
SCLCHandleSCRCMsg_TTC(MTP3_HEADER* mtp3, ITS_OCTET mType,
                        ITS_SCCP_IE* ies, int ieCount,
                        ITS_UINT pc, ITS_OCTET ssn)
{
    int ret, i;
    int dataIndex = -1;
    int cgAddrIndex = -1;
    SCCP_ADDR *callingPartyAddr;
    SCCP_HOP_COUNT* hc = NULL;
    int segIEPres = ITS_FALSE;
    SCCP_PROT_CLASS* pclass = NULL;
    ITS_OCTET dsmKey[SCCP_MAX_ADDR_LEN + MAX_SEG_REF_LEN];
    ITS_OCTET keyLen, lpclass;
    int error;
    ITS_HDR hdr;
    ITS_EVENT event;
    ITS_OCTET ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

    SCCP_DEBUG(("SCLCHandleSCRCMsg: ssn %02x\n", ssn));

    PEG_IncrPeg(TTC_SCCP_Pegs, PEG_SCCP_REMOTE_MSG_RECEIVED);

    /* Q752 Implementation */
        SccpGenOmImage_TTC[omBuf.activeOm].SCCPGenPegs.messageFromRemoteSS++;

    /* IntelliSS7 routing */
    hdr.type = ITS_SCCP;
    hdr.context.ssn = ssn;

    printf("Intellinet Routing SCLCHandleSCRCMsg_TTC %d \n", ssn);

    /* add in the routing label */
    ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
    ies[ieCount].param_length = sizeof(MTP3_HEADER);
    ies[ieCount].param_data.routingLabel = *mtp3;
    ieCount++;

    if (BEHAVIORS_GetBehavior(&TTC_SCCP_Behaviors,
                              SCCP_B_use_SCMG) && ssn == SCCP_SSN_SCCPMGMT)
    {
        return SCMGHandleSCLCMsg_TTC(mtp3, mType, ies, ieCount);
    }

    if (ssn == SCCP_SSN_SCCPMGMT)
    {
        return ITS_SUCCESS;
    }

    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_HOP_COUNTER)
        {
            hc = &ies[i].param_data.hopCount;
            break;
        }
        else if (ies[i].param_id == SCCP_PRM_PROTOCOL_CLASS)
        {
            lpclass = (0x0F &ies[i].param_data.protocolClass.pclass);
        }
    }

    if (hc) 
    {
        if (hc->count < 0 || hc->count > SCCP_MAX_HOP_COUNT) 
        {
            SCCP_ERROR(("SCLCHandleSCRCMsg: Hop count exceeded\n"));
            /* ERROR - Incoming Message - Hop Count Exceeded. */

            PEG_IncrPeg(TTC_SCCP_Pegs, PEG_SCCP_HOP_COUNTER_VIOLATION_ERR);

            /* Q752 Implementation */
                SccpGenOmImage_TTC[omBuf.activeOm].SCCPGenPegs.hopCounterViolationErr++;   
    
            SCLCHandleRoutingFailure_TTC(mtp3, mType, ies, 
                                           ieCount, 
                                           SCCP_RET_HOP_COUNT_EXCEEDED);

            return ITS_SUCCESS;
        }
    }

    switch (mType)
    {
    case SCCP_MSG_UDT:
        PEG_IncrPeg(TTC_SCCP_Pegs, PEG_SCCP_REMOTE_UDT_RCVD);

        /* Q752 Implementation */
            SccpGenOmImage_TTC[omBuf.activeOm].SCCPGenPegs.messageUDTRcvd++;

        //Q752 SSN pegs
            SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].ssn = ssn;
            if (lpclass == SCCP_PCLASS_0)
            {
                SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].userUDTRcvdperClass0SSN++;
            }
            else if (lpclass == SCCP_PCLASS_1)
            {
                SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].userUDTRcvdperClass1SSN++;
       	    }

        if (SCCP_Encode(ies, ieCount, mType, &event, &hdr,
                        &SCCP_UDT_Desc) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCLCHandleSCRCMsg: Encode failure\n"));
            return (ITS_EINVALIDARGS);
        }

        break;

    case SCCP_MSG_XUDT:
       PEG_IncrPeg(TTC_SCCP_Pegs, PEG_SCCP_REMOTE_XUDT_RCVD);
 
       /* Q752 Implementation */
           SccpGenOmImage_TTC[omBuf.activeOm].SCCPGenPegs.messageXUDTRcvd++;


       /* Increment SSN Peg for XUDT Received */
       //Q752 SSN pegs
       SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].ssn = ssn;

       if (lpclass == SCCP_PCLASS_0)
       { 
          SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].userXUDTRcvdperClass0SSN++;
       }
       else if (lpclass == SCCP_PCLASS_1)
       {
          SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].userXUDTRcvdperClass1SSN++;
       }

       for (i = 0; i < ieCount; i++)
       {
            if (ies[i].param_id == SCCP_PRM_DATA)
            {
                dataIndex = i;
            }
            if (ies[i].param_id == SCCP_PRM_CALLING_PARTY_ADDR)
            {
                cgAddrIndex = i;
            }
       }

       if (cgAddrIndex < 0 || dataIndex < 0)
       {
            SCCP_ERROR(("SCLCHandleSCRCMsg: missind data or address\n"));

            return (ITS_EMISSMAND);
       }

       for (i = 0; i < ieCount; i++)
       {
            if (ies[i].param_id == SCCP_PRM_SEGMENTATION)
            {
                ITS_OCTET remainingSegment;
                ITS_OCTET dataLen;
                ITS_OCTET *data;
                ITS_OCTET tmp[SCCP_MAX_DATA];
                ITS_INT maxDataLen;
                SCCP_REASM_CTXT *ctxt;
                ITS_INT segRefNum;
                SCCP_REF_NUM *segRef;
                ITS_UINT pc = 0;

                pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);

                segIEPres = ITS_TRUE;
                segRef = &(ies[i].param_data.segmentation.localRef);

                callingPartyAddr = &(ies[cgAddrIndex].param_data.callingPartyAddr);
                segRefNum = RN_GET_REF_NUM(*segRef);

                keyLen = 0;

                memcpy(dsmKey, &pc, 3);
                memcpy(dsmKey + 3, &segRefNum, MAX_SEG_REF_LEN);

                keyLen += (sizeof(int) + sizeof(ITS_UINT));

                memcpy(&dsmKey[keyLen], callingPartyAddr->data, 
                       callingPartyAddr->len);
                keyLen += callingPartyAddr->len;

                SCCP_DEBUG(("Performing Reassembly Procedure\n"));

                if (ies[i].param_data.segmentation.flags & SCCP_SEG_IS_FIRST)
                {
                    remainingSegment = ies[i].param_data.segmentation.
                                        flags & SCCP_SEG_REMNANT_MASK;

                    if (remainingSegment == 0)
                    {
                        SCCP_DEBUG(("Received First and last segment"));

                        if (SCCP_Encode(ies, ieCount, SCCP_MSG_UDT, 
                                        &event, &hdr,
                                        &SCCP_UDT_Desc) 
                                        != ITS_SUCCESS)
                        {
                            SCCP_ERROR(("SCLCHandleSCRCMsg: Encode failure\n"));

                            return (ITS_EINVALIDARGS);
                        }

                        break;
                        
                    }

                    segRefNum = RN_GET_REF_NUM(*segRef);
                    dataLen = ies[dataIndex].param_length;
                    data = ies[dataIndex].param_data.userData.data;
                    maxDataLen = (remainingSegment + 1) * dataLen;

                    if( SCCP_AddSegmentRef_TTC(dsmKey, keyLen,  maxDataLen, 
                                                 remainingSegment, dataLen, 
                                                 data, segRefNum) 
                                                 != ITS_SUCCESS)
                    {
                         /* Easy way to send XUDTS */
                         SCCP_ERROR(("Failed to add segment refrence"));
                         PEG_IncrPeg(TTC_SCCP_Pegs,
                                               PEG_SCCP_REMOTE_REASSEMBLE_ERR);

                         /* Q752 Implementation */
                             SccpGenOmImage_TTC[omBuf.activeOm].SCCPGenPegs.reassemblyErrNoReassemblySpace++;  /* 7.12 */
  
                             SccpGenOmImage_TTC[omBuf.activeOm].SCCPGenPegs.reassemblyErrReassemblyFailed++;

                         SCLCHandleRoutingFailure_TTC(mtp3, mType, ies, 
                                                        ieCount, 
                                                 SCCP_RET_ERR_IN_LOCAL_PROCESS);

                         return ITS_SUCCESS;
                    }
                    else
                    {
                        SCCP_DEBUG(("first segment successfully added\n"));

                        return ITS_SUCCESS;
                    }
                }
                else /* not first segement */
                {
                    remainingSegment = ies[i].param_data.segmentation.
                                        flags & SCCP_SEG_REMNANT_MASK;
                    segRefNum = RN_GET_REF_NUM(*segRef);

                    ctxt = (SCCP_REASM_CTXT *) DSM_Find(DSM_SccpFtGroupId,
                                                        DSM_TABLE_TTC_SCCP_CTXT,
                                                        (ITS_OCTET *)dsmKey,
                                                         keyLen, 
                                                         &error);

                    if (error != ITS_SUCCESS)
                    {

                        switch (error)
                        {
                            case (ITS_EBADMUTEX):
                            SCCP_CRITICAL(("Couldn't "
                                           "acquire mutex.\n"));

                            break;

                            case (ITS_ENOTFOUND):
                            SCCP_WARNING(("HandleSCRCMsg: Could not find "
                                           " context.\n"));

                            break;

                            case (ITS_EINUSE):
                            SCCP_CRITICAL(("DSM Row Locked.\n"));

                            break;
                        }
                        
                        SCLCHandleRoutingFailure_TTC(mtp3, mType, ies, 
                                            ieCount, SCCP_RET_ERR_IN_TRANSPORT);

                        return (ITS_ENOCONN);
                    }

                    /* Out if sequence segment */
                    if (ctxt->remainingSegment != remainingSegment + 1)
                    {
                        /* send XUDTS */
                        /* perform clean up */

                        SCCP_ERROR(("Remaining segment field not correct:\n"));
                        
                        /* Q752 Implementation */
                            SccpGenOmImage_TTC[omBuf.activeOm].SCCPGenPegs.reassemblyErrSegRxOOS++;

                        /*returning first segment in XUDTS*/
                        SCLC_GetFirstSegmentData(
                                        ies[dataIndex].param_data.userData.data,
                                         (ctxt->startFragKey), ctxt->keyLen);

                        if(ctxt->totalDataLen < SCCP_MAX_SEG_DATA)
                        {
                            ies[dataIndex].param_length = ctxt->totalDataLen;
                        }
                        else
                        {
                            ies[dataIndex].param_length = SCCP_MAX_SEG_DATA;
                        }

                        SCLCHandleRoutingFailure_TTC(mtp3, mType, ies, 
                                            ieCount, SCCP_RET_ERR_IN_TRANSPORT);

                        SCCP_DeleteSegmentRef_TTC(dsmKey, keyLen, ctxt);

                        return ITS_SUCCESS;
                    }

                    dataLen = ies[dataIndex].param_length;
                    data = ies[dataIndex].param_data.userData.data;

                    printf("ctxt->totalDataLen + dataLen = %d ctxt->maxDataLen == %d----\n",(ctxt->totalDataLen + dataLen), ctxt->maxDataLen);
                    if ((ctxt->totalDataLen + dataLen) > ctxt->maxDataLen) 
                    {
                        /* perform clean up */
                         SCCP_ERROR(("Data length exceeds max expected data"));
                         PEG_IncrPeg(TTC_SCCP_Pegs,
                                     PEG_SCCP_REMOTE_REASSEMBLE_ERR);

                         /* Q752 Implementation */
                             SccpGenOmImage_TTC[omBuf.activeOm].SCCPGenPegs.reassemblyErrNoReassemblySpace++; /* 7.12 */

                             SccpGenOmImage_TTC[omBuf.activeOm].SCCPGenPegs.reassemblyErrReassemblyFailed++;


                         SCLC_GetFirstSegmentData(
                                        ies[dataIndex].param_data.userData.data,
                                        (ctxt->startFragKey), ctxt->keyLen);

                         if (ctxt->totalDataLen < SCCP_MAX_SEG_DATA)
                         {
                            ies[dataIndex].param_length =ctxt->totalDataLen;
                         }
                         else
                         {
                            ies[dataIndex].param_length = SCCP_MAX_SEG_DATA;
                         }

                         SCLCHandleRoutingFailure_TTC(mtp3, mType, ies, 
                                            ieCount, SCCP_RET_ERR_IN_TRANSPORT);

                         SCCP_DeleteSegmentRef_TTC(dsmKey, keyLen, ctxt);

                         return ITS_SUCCESS;
                    }

                    if (remainingSegment > 0)
                    {
                        ctxt->remainingSegment = remainingSegment;

                        if (SCLC_PutDataInFragList(NULL, 0,
                                                  ctxt, data, dataLen) 
                                                  != ITS_SUCCESS)
                        {
                             SCCP_ERROR(("Could not add darta to fragment" 
                                         " list"));
                             PEG_IncrPeg(TTC_SCCP_Pegs,
                                         PEG_SCCP_REMOTE_REASSEMBLE_ERR);
 
                             /* Q752 Implementation */
                                 SccpGenOmImage_TTC[omBuf.activeOm].SCCPGenPegs.reassemblyErrNoReassemblySpace++;  /* 7.12 */
                             
				 SccpGenOmImage_TTC[omBuf.activeOm].SCCPGenPegs.reassemblyErrReassemblyFailed++; 

                            SCLC_GetFirstSegmentData(ies[dataIndex].param_data.
                                                     userData.  data, 
                                                     ctxt->startFragKey, 
                                                     ctxt->keyLen);

                             if (ctxt->totalDataLen < SCCP_MAX_SEG_DATA)
                             {
                                ies[dataIndex].param_length =
                                                    ctxt->totalDataLen;
                             }
                             else
                             {
                                ies[dataIndex].param_length = 
                                                          SCCP_MAX_SEG_DATA;
                             }

                             SCLCHandleRoutingFailure_TTC(mtp3, mType, ies, 
                                                ieCount, 
                                                SCCP_RET_ERR_IN_LOCAL_PROCESS);

                             SCCP_DeleteSegmentRef_TTC(dsmKey, keyLen, ctxt);

                             return ITS_SUCCESS;
                        }

                        ctxt->totalDataLen += dataLen;

                        error = DSM_Commit(DSM_SccpFtGroupId,
                                           DSM_TABLE_TTC_SCCP_CTXT, 
                                           (ITS_OCTET *)dsmKey, 
                                            keyLen, ctxt);

                        if (error != ITS_SUCCESS)
                        {
                            SCCP_ERROR((" Couldn't commit  context.\n"));

                            return (error);
                        } 

                        return ITS_SUCCESS;
                    }
                    else /* last segement */
                    {
                        SCCP_DEBUG(("Received last segment "));

                        ies[dataIndex].param_id = SCCP_PRM_LONG_DATA;
                        memcpy(tmp, data, dataLen);
                        ies[dataIndex].param_data.longData.len = 
                                                 ctxt->totalDataLen + dataLen;

                        SCLC_GetDataFromFragList(ies[dataIndex].param_data.longData.data, 
                                            ctxt->startFragKey, 
                                            ctxt->keyLen);

                        ctxt->keyLen = 0;

                        memcpy(ies[dataIndex].param_data.longData.data + 
                               ctxt->totalDataLen, tmp, dataLen);

                        if (SCCP_Encode(ies, ieCount, SCCP_MSG_LUDT, 
                                        &event, &hdr,
                                        &SCCP_LUDT_Desc) != 
                                        ITS_SUCCESS)
                        {
                            SCCP_ERROR(("SCLCHandleSCRCMsg: Encode failure\n"));

                            SCCP_DeleteSegmentRef_TTC(dsmKey, keyLen, ctxt);

                            return (ITS_EINVALIDARGS);
                        }

                        SCCP_DeleteSegmentRef_TTC(dsmKey, keyLen, ctxt);

                        break;
                    }
                        
                }
            }
        }

        /* No segmentation IE not received that is single XUDT */
        if (segIEPres == ITS_FALSE)
        {
            if (SCCP_Encode(ies, ieCount, SCCP_MSG_UDT, &event, &hdr,
                            &SCCP_UDT_Desc) != ITS_SUCCESS)
            {
                SCCP_ERROR(("SCLCHandleSCRCMsg: Encode failure\n"));

                return (ITS_EINVALIDARGS);
            }
        }

        break;

    case SCCP_MSG_UDTS:
        PEG_IncrPeg(TTC_SCCP_Pegs, PEG_SCCP_REMOTE_UDTS_RCVD);

        /* Q752 Implementation */ 
            SccpGenOmImage_TTC[omBuf.activeOm].SCCPGenPegs.messageUDTSRcvd++;

        if (SCCP_Encode(ies, ieCount, mType, &event, &hdr,
                        &SCCP_UDTS_Desc) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCLCHandleSCRCMsg: Encode failure\n"));

            return (ITS_EINVALIDARGS);
        }

        break;

    case SCCP_MSG_XUDTS:
        PEG_IncrPeg(TTC_SCCP_Pegs, PEG_SCCP_REMOTE_XUDTS_RCVD);
 
        /* Q752 Implementation */ 
            SccpGenOmImage_TTC[omBuf.activeOm].SCCPGenPegs.messageXUDTSRcvd++;

        if (SCCP_Encode(ies, ieCount, mType, &event, &hdr,
                        &SCCP_XUDTS_Desc) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCLCHandleSCRCMsg: Encode failure\n"));

            return (ITS_EINVALIDARGS);
        }

        break;

    case SCCP_MSG_LUDT:
        PEG_IncrPeg(TTC_SCCP_Pegs, PEG_SCCP_REMOTE_LUDT_RCVD);

        /* Q752 Implementation */
            SccpGenOmImage_TTC[omBuf.activeOm].SCCPGenPegs.messageLUDTRcvd++;

        // Q752 SSN Peg
            SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].ssn = ssn;
            if (lpclass == SCCP_PCLASS_0)
            {
               SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].userLUDTRcvdperClass0SSN++;
            }
            else if (lpclass == SCCP_PCLASS_1)
            {
               SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].userLUDTRcvdperClass1SSN++;
            }

        if (SCCP_Encode(ies, ieCount, mType, &event, &hdr,
                        &SCCP_LUDT_Desc) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCLCHandleSCRCMsg: Encode failure\n"));

            return (ITS_EINVALIDARGS);
        }

        break;

    case SCCP_MSG_LUDTS:
        PEG_IncrPeg(TTC_SCCP_Pegs, PEG_SCCP_REMOTE_LUDTS_RCVD);

        /* Q752 Implementation */
            SccpGenOmImage_TTC[omBuf.activeOm].SCCPGenPegs.messageLUDTSRcvd++;

        if (SCCP_Encode(ies, ieCount, mType, &event, &hdr,
                        &SCCP_LUDTS_Desc) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCLCHandleSCRCMsg: Encode failure\n"));

            return (ITS_EINVALIDARGS);
        }

        break;

    default:
         SCCP_ERROR(("SCLCHandleSCRCMsg: Bad message type\n"));
         break;
    }

    event.src = ITS_SCCP_SRC;
    ITS_SET_CTXT(&event.data[1], hdr.context.ssn);

    ret = ROUTE_SendToRouteContext(pc, &event,
                                   ROUTE_DPC_SIO_SSN,
                                   FAMILY_JAPAN,
                                   ROUTE_SIO_SCCP | ni,
                                   (ITS_OCTET)hdr.context.ssn,
                                   ITS_SS7_DEFAULT_LINK_SET,
                                   ITS_SS7_DEFAULT_LINK_CODE,
                                   ITS_SS7_DEFAULT_PRI,
                                   ITS_SS7_DEFAULT_SLS);
    if (ret != ITS_SUCCESS)
    {
        SCCP_WARNING(("SendToAPP: no route to dest.\n"));
    }

    ITS_EVENT_TERM(&event);

    return (ret);
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
 ****************************************************************************/
int
SCLCHandleSCMGMsg_TTC(MTP3_HEADER* mtp3, ITS_OCTET mType,
                        ITS_SCCP_IE* ies, int ieCount)
{
    switch (mType)
    {
    case SCCP_MSG_UDT:
        return SCRCHandleSCLCMsg_TTC(mtp3, SCCP_MSG_UDT, ies, ieCount);

    case SCCP_MSG_XUDT:
        return SCRCHandleSCLCMsg_TTC(mtp3, SCCP_MSG_XUDT, ies, ieCount);

    case SCCP_MSG_UDTS:
        return SCRCHandleSCLCMsg_TTC(mtp3, SCCP_MSG_UDTS, ies, ieCount);

    case SCCP_MSG_XUDTS:
        return SCRCHandleSCLCMsg_TTC(mtp3, SCCP_MSG_XUDTS, ies, ieCount);

    case SCCP_MSG_LUDT:
        return SCRCHandleSCLCMsg_TTC(mtp3, SCCP_MSG_LUDT, ies, ieCount);

    case SCCP_MSG_LUDTS:
        return SCRCHandleSCLCMsg_TTC(mtp3, SCCP_MSG_LUDTS, ies, ieCount);

    }

    return (ITS_EINVALIDARGS);
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
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  gharipriya 12-10-2006 Bug Id 4472            Remove the check for SSN and
 *                                               add mtp3 hearder check in the
 *                                               appropriate place.
 *
 *  gharipriya 25-09-2006  Bug ID:4329,4328,4357  UDT/XUDT Pegs Implementation.
 *
 ****************************************************************************/
int
SCLCHandleAPPMsg_TTC(ITS_EVENT* event)
{
    ITS_SCCP_IE ies[32];
    int ieCount;
    int ret, i;
    MTP3_HEADER* mtp3 = NULL;
    ITS_OCTET    data[SCCP_LONG_DATA_MAX];
    int          dataLen = 0;
    int          dataIndex = -1;
    ITS_OCTET    totalSegment;
    ITS_OCTET    segIndex;
    SCCP_REF_NUM *sgLRef = NULL; 
   
    /* Q752 Declaration */ 
    SCCP_ADDR *clp = NULL, *cdp = NULL;
    ITS_OCTET ai;
    ITS_UINT pc; 
    ITS_OCTET ssn, lpclass, ni;
    SCCP_PROT_CLASS* pclass = NULL;
 
    SCCP_DEBUG(("SCLCHandleAPPMsg:\n"));
    PEG_IncrPeg(TTC_SCCP_Pegs, PEG_SCCP_USER_MSG_SENT);

    /* Q752 Implementation */ 
        SccpGenOmImage_TTC[omBuf.activeOm].SCCPGenPegs.messageFromLocalSS++;

    switch (SCCP_MSG_TYPE(event))
    {
    case SCCP_MSG_UDT:
        PEG_IncrPeg(TTC_SCCP_Pegs, PEG_SCCP_USER_UDT_SENT);
        
        /* Q752 Implementation */ 
             SccpGenOmImage_TTC[omBuf.activeOm].SCCPGenPegs.messageUDTSent++;

        if ((ret = SCCP_Decode(ies, &ieCount, event,
                               &SCCP_UDT_Desc)) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCLCHandleAPPMsg: Decode of UDT failed\n"));

            return (ret);
        }

        for (i = 0; i < ieCount; i++)
        {
            if (ies[i].param_id == SCCP_PRM_ROUTING_LABEL)
            {
                mtp3 = &ies[i].param_data.routingLabel;
                break;
            }
        }

        for (i = 0; i < ieCount; i++)
        {
            if (ies[i].param_id == SCCP_PRM_PROTOCOL_CLASS)
            {
                lpclass = (0x0F & ies[i].param_data.protocolClass.pclass);
                if (ies[i].param_data.protocolClass.pclass & SCCP_PCLASS_MASK)
                {
                }
                else
                {
                }

                break;
            }
        }

        for (i = 0; i < ieCount; i++)
        {
            if (ies[i].param_id == SCCP_PRM_CALLED_PARTY_ADDR)
            {
                cdp = &ies[i].param_data.calledPartyAddr;
                break;
            }
        }

        if (mtp3 == NULL)
        {
            /* Discarding  Message - Defective MTP3 header. */
            SCCP_Alarm_TTC(633, __FILE__, __LINE__, "family=%s:mType=%s",
                           "TTC", "UDT");
 
            return (ITS_EMISSMAND);
        }
 
        /* Q752 Implementation */
        SCCP_DecodeAddr(cdp, &ai, &pc, &ssn, NULL, NULL);

        /* Increment SSN Peg for UDT Sent */

           SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].ssn = ssn;
           if (lpclass == SCCP_PCLASS_0)
           {
              SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].userUDTSentperClass0SSN++;
           }
           else if (lpclass == SCCP_PCLASS_1)
           {
              SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].userUDTSentperClass1SSN++;
           }


        return SCRCHandleSCLCMsg_TTC(mtp3, SCCP_MSG_UDT, ies, ieCount);

    case SCCP_MSG_XUDT:
        PEG_IncrPeg(TTC_SCCP_Pegs, PEG_SCCP_USER_XUDT_SENT);

        /* Q752 Implementation */
            SccpGenOmImage_TTC[omBuf.activeOm].SCCPGenPegs.messageXUDTSent++;

        if ((ret = SCCP_Decode(ies, &ieCount, event,
                               &SCCP_XUDT_Desc)) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCLCHandleAPPMsg: Decode of XUDT failed\n"));

            return (ret);
        }
       
        for (i = 0; i < ieCount; i++)
        {
            if (ies[i].param_id == SCCP_PRM_ROUTING_LABEL)
            {
                mtp3 = &ies[i].param_data.routingLabel;

            }
            /* Q752 Implementation */
            else if (ies[i].param_id == SCCP_PRM_LONG_DATA)
            {
                dataLen = ies[i].param_data.longData.len;
            }
            else if (ies[i].param_id == SCCP_PRM_PROTOCOL_CLASS)
            {
               lpclass = (0x0F & ies[i].param_data.protocolClass.pclass);
            }
        }

        for (i = 0; i < ieCount; i++)
        {
            if (ies[i].param_id == SCCP_PRM_CALLED_PARTY_ADDR)
            {
                cdp = &ies[i].param_data.calledPartyAddr;
                break;
            }
        }

        if (mtp3 == NULL)
        {
            /* Incoming Message - Discarding  Message - Defective MTP3 header.*/
            SCCP_Alarm_TTC(633, __FILE__, __LINE__, "family=%s:mType=%s",
                           "TTC", "XUDT");
          
            return (ITS_EMISSMAND);
        }

        /* Q752 Implementation */
        SCCP_DecodeAddr(cdp, &ai, &pc, &ssn, NULL, NULL);

       /* Increment SSN Peg for XUDT Sent */
          SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].ssn = ssn;
       	  if (lpclass == SCCP_PCLASS_0)
          {
              SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].userXUDTSentperClass0SSN++;
          }
          else if (lpclass == SCCP_PCLASS_1)
          {
              SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].userXUDTSentperClass1SSN++;
          }
 
        /* Q752 Implementation */       
        if (dataLen > SCCP_LONG_DATA_MAX)  
        {
           SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].ssn = ssn;
           SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].msgLargeForSeg++;
           return ITS_ESENDFAIL;
        }	
 
        return SCRCHandleSCLCMsg_TTC(mtp3, SCCP_MSG_XUDT, ies, ieCount);

    case SCCP_MSG_UDTS:
        PEG_IncrPeg(TTC_SCCP_Pegs,   PEG_SCCP_USER_UDTS_SENT);

        /* Q752 Implementation */
            SccpGenOmImage_TTC[omBuf.activeOm].SCCPGenPegs.messageUDTSSent++;

        if ((ret = SCCP_Decode(ies, &ieCount, event,
                               &SCCP_UDTS_Desc)) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCLCHandleAPPMsg: Decode of UDTS failed\n"));

            /* SCCP decode failed. */
            return (ret);
        }

        for (i = 0; i < ieCount; i++)
        {
            if (ies[i].param_id == SCCP_PRM_ROUTING_LABEL)
            {
                mtp3 = &ies[i].param_data.routingLabel;

                break;
            }
        }
 
        if (mtp3 == NULL)
        {
            /* Incoming Message - Discarding  Message - Defective MTP3 header.*/
            SCCP_Alarm_TTC(633, __FILE__, __LINE__, "family=%s:mType=%s",
                           "TTC", "UDTS");

            return (ITS_EMISSMAND);
        }

        return SCRCHandleSCLCMsg_TTC(mtp3, SCCP_MSG_UDTS, ies, ieCount);

    case SCCP_MSG_XUDTS:
        PEG_IncrPeg(TTC_SCCP_Pegs,   PEG_SCCP_USER_XUDTS_SENT);

        /* Q752 Implementation */
            SccpGenOmImage_TTC[omBuf.activeOm].SCCPGenPegs.messageXUDTSSent++;

        if ((ret = SCCP_Decode(ies, &ieCount, event,
                               &SCCP_XUDTS_Desc)) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCLCHandleAPPMsg: Decode of XUDTS failed\n"));

            return (ret);
        }

        for (i = 0; i < ieCount; i++)
        {
            if (ies[i].param_id == SCCP_PRM_ROUTING_LABEL)
            {
                mtp3 = &ies[i].param_data.routingLabel;

                break;
            }
        }

        if (mtp3 == NULL)
        {
            /* Incoming Message - Discarding  Message - Defective MTP3 header.*/
            SCCP_Alarm_TTC(633, __FILE__, __LINE__, "family=%s:mType=%s",
                           "TTC", "XUDTS");

            return (ITS_EMISSMAND);
        }

        return SCRCHandleSCLCMsg_TTC(mtp3, SCCP_MSG_XUDTS, ies, ieCount);
    
    case SCCP_MSG_LUDT:
        PEG_IncrPeg(TTC_SCCP_Pegs, PEG_SCCP_USER_LUDT_SENT);

        /* Q752 Implementation */
            SccpGenOmImage_TTC[omBuf.activeOm].SCCPGenPegs.messageLUDTSent++;

        if ((ret = SCCP_Decode(ies, &ieCount, event,
                               &SCCP_LUDT_Desc)) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCLCHandleAPPMsg: Decode of LUDT failed\n"));

            return (ret);
        }
        
   
        for (i = 0; i < ieCount; i++)
        {
            if (ies[i].param_id == SCCP_PRM_PROTOCOL_CLASS)
            {
                lpclass = (0x0F &ies[i].param_data.protocolClass.pclass);
            }

            else if (ies[i].param_id == SCCP_PRM_ROUTING_LABEL)
            {
                mtp3 = &ies[i].param_data.routingLabel;

                break;
            }
        }

        for (i = 0; i < ieCount; i++)
        {
            if (ies[i].param_id == SCCP_PRM_CALLED_PARTY_ADDR)
            {
                cdp = &ies[i].param_data.calledPartyAddr;
                break;
            }
        }
            
        if (mtp3 == NULL)
        {
            /* Incoming Message - Discarding  Message - Defective MTP3 header.*/
            SCCP_Alarm_TTC(633, __FILE__, __LINE__, "family=%s:mType=%s",
                           "TTC", "XUDT");
            
            return (ITS_EMISSMAND);
        }

        /* Q752 Implementation */
        SCCP_DecodeAddr(cdp, &ai, &pc, &ssn, NULL, NULL);

        /* Increment SSN Peg for LUDT Sent */
           SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].ssn = ssn;
           if (lpclass == SCCP_PCLASS_0)
           {
              SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].userLUDTSentperClass0SSN++;
           }
           else if (lpclass == SCCP_PCLASS_1)
           {
              SsnOmImage[omBuf.activeOm].SCCPSSNPegs[ssn].userLUDTSentperClass1SSN++;
           }

        for (i = 0; i < ieCount; i++)
        {
            if (ies[i].param_id == SCCP_PRM_LONG_DATA)
            {
                dataLen = ies[i].param_data.longData.len;
                break;
            }
        }
         
        if(dataLen > SCCP_LUDT_MAX)             
        {
            for (i = 0; i < ieCount; i++)
            {
                if (ies[i].param_id == SCCP_PRM_LONG_DATA)
                {
                    dataLen = ies[i].param_data.longData.len;
                    memcpy(data, ies[i].param_data.longData.data, dataLen);
                    dataIndex = i;
                    ies[i].param_id = SCCP_PRM_DATA;
                }
            }

            segIndex = ieCount;
            for (i = 0; i < ieCount; i++)
            {
                if (ies[i].param_id == SCCP_PRM_SEGMENTATION)
                {
                  segIndex = i;
                  ieCount--;
                }
            }

            /* Add segmentation IE */
            ies[segIndex].param_id = SCCP_PRM_SEGMENTATION;
            ies[segIndex].param_length = sizeof(SCCP_SEGMENTATION);

            __local_seg_ref_number++;
            if(__local_seg_ref_number >= SCCP_MAX_SEG_REF)
            {
                __local_seg_ref_number = 0;
            }
           
            RN_SET_REF_NUM(ies[segIndex].param_data.segmentation.localRef,
                           __local_seg_ref_number);
      
            /* Q752 Implementation */ 
            sgLRef = &ies[i].param_data.segmentation.localRef;  

            if (sgLRef == NULL) /* chandra sgLRef for Testing */
            {
               SccpGenOmImage_TTC[omBuf.activeOm].SCCPGenPegs.segmentationErrSegFailed++; 
               return (ITS_EMISSMAND); 
            }  

            ieCount++;
            totalSegment = dataLen / SCCP_MAX_SEG_DATA;
 
            /* if data not exact mutiple of SCCP_MAX_SEG_DATA add one more segment*/
            if (dataLen % SCCP_MAX_SEG_DATA)
            {
                totalSegment++;
            }

            if (totalSegment > SCCP_MAX_ALLOWED_SEGMENT)
            {
                SCCP_ERROR(("SCLCHandleAPPMsg : data length too long for "
                             "segmentation data len = %d \n", dataLen));

                PEG_IncrPeg(TTC_SCCP_Pegs, PEG_SCCP_USER_SEGMENTATION_ERR);

                return ITS_ESENDFAIL;
            }

            for (i = 0;i < totalSegment; i++)
            {
                if (dataLen < (SCCP_MAX_SEG_DATA + (i * SCCP_MAX_SEG_DATA)))
                {
                    ies[dataIndex].param_length = dataLen - (i * SCCP_MAX_SEG_DATA);
                    memcpy(ies[dataIndex].param_data.userData.data, 
                           &(data[i * SCCP_MAX_SEG_DATA]), 
                           dataLen - (i * SCCP_MAX_SEG_DATA));
                }
                else if(dataLen == i * SCCP_MAX_SEG_DATA)
                {
                    return ITS_SUCCESS;
                }
                else
                {
                    ies[dataIndex].param_length = SCCP_MAX_SEG_DATA;
                    memcpy(ies[dataIndex].param_data.userData.data, 
                           &(data[i * SCCP_MAX_SEG_DATA]),
                           SCCP_MAX_SEG_DATA);
                }
    
                if(i == 0)
                {
                    /* first segment */
                    ies[segIndex].param_data.segmentation.flags = 
                                            SCCP_SEG_IS_FIRST|SCCP_SEG_RETAIN_SEQ;
                }
                else
                {
                    ies[segIndex].param_data.segmentation.flags = 
                                                          SCCP_SEG_RETAIN_SEQ;
                }
     
                ies[segIndex].param_data.segmentation.flags |= (totalSegment - i 
                                                                 - 1);
    
                ret = SCRCHandleSCLCMsg_TTC(mtp3, SCCP_MSG_XUDT, ies, ieCount);

                if (ret != ITS_SUCCESS)
                {

                    return ret;

                }
            }
        }
        else
        {
            ret = SCRCHandleSCLCMsg_TTC(mtp3, SCCP_MSG_LUDT, ies, ieCount);

            if (ret != ITS_SUCCESS)
            {
                return ret;
            }
        }

        return ret;

    case SCCP_MSG_LUDTS:
        PEG_IncrPeg(TTC_SCCP_Pegs,   PEG_SCCP_USER_LUDTS_SENT);

        /* Q752 Implementation */
            SccpGenOmImage_TTC[omBuf.activeOm].SCCPGenPegs.messageLUDTSSent++;

        if ((ret = SCCP_Decode(ies, &ieCount, event,
                               &SCCP_LUDTS_Desc)) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCLCHandleAPPMsg: Decode of LUDTS failed\n"));

            return (ret);
        }

        for (i = 0; i < ieCount; i++)
        {
            if (ies[i].param_id == SCCP_PRM_ROUTING_LABEL)
            {
                mtp3 = &ies[i].param_data.routingLabel;

                break;
            }
        }

        if (mtp3 == NULL)
        {
            /* Incr the discarded Peg counter for this msg also */

            /* Incoming Message - Discarding  Message - Defective MTP3 header. */
            SCCP_Alarm_TTC(633, __FILE__, __LINE__, "family=%s:mType=%s",
                           "TTC", "LUDTS");

            return (ITS_EMISSMAND);
        }

        return SCRCHandleSCLCMsg_TTC(mtp3, SCCP_MSG_LUDTS, ies, ieCount);
    
    default:
        SCCP_ERROR(("SCLCHandleSCRCMsg: Bad message type\n"));
        break;

    }

    return (ITS_EINVALIDARGS);
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
SCLCHandleReasmTimer_TTC(ITS_TimerData* td)
{
    SCCP_REASM_CTXT ctxt;
    SCCP_REASM_CTXT *ct = NULL;
    int cref;
    int error;
    ITS_OCTET dsmKey[SCCP_MAX_ADDR_LEN + MAX_SEG_REF_LEN];

    memcpy(&ctxt, td->context, sizeof(SCCP_REASM_CTXT));
    cref = ctxt.refno;
    
    memcpy(dsmKey, ctxt.startFragKey, ctxt.keyLen);
    memcpy(dsmKey, (ITS_OCTET *)&cref, MAX_SEG_REF_LEN);


    ct = (SCCP_REASM_CTXT *) DSM_Find(DSM_SccpFtGroupId,
                                      DSM_TABLE_TTC_SCCP_CTXT, 
                                      (ITS_OCTET *)dsmKey, 
                                      ctxt.keyLen, &error);
    if (error != ITS_SUCCESS)
    {

        switch (error)
        {
             case (ITS_EBADMUTEX):
                  SCCP_CRITICAL(("Couldn't acquire mutex.\n"));

                  break;

            case (ITS_ENOTFOUND):
                  SCCP_WARNING(("Could not find context.\n"));

                  break;

            case (ITS_EINUSE):
                  SCCP_CRITICAL(("DSM Row Locked.\n"));

                  break;
        }

        return ITS_SUCCESS;
    }

    if (ct->keyLen != 0)
    {
        SCLC_FreeFragList(ct->startFragKey, ct->keyLen);
    }

    error = DSM_Free(DSM_SccpFtGroupId,
                     DSM_TABLE_TTC_SCCP_CTXT, 
                     (ITS_OCTET *)dsmKey,
                     ctxt.keyLen, ct);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("DSM unable to free Reference.\n"));
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
SCLC_GetDataFromFragList(ITS_OCTET *data,
                         ITS_OCTET *startKey, ITS_OCTET keyLen)
{
    SCCP_DATA_FRAG* fptr;
    int error;

    fptr = (SCCP_DATA_FRAG *) DSM_Find(DSM_SccpFtGroupId,
                                       DSM_TABLE_TTC_SCCP_CTXT,
                                       (ITS_OCTET *)startKey, 
                                       keyLen, &error);

    if (error == ITS_ENOTFOUND)
    {
        SCCP_CRITICAL(("GetDataInFragList: Couldn't alloc segment.\n"));

        return (ITS_ENOMEM);
    }

    memcpy(data, fptr->data, fptr->len);

    error = DSM_Free(DSM_SccpFtGroupId,
                     DSM_TABLE_TTC_SCCP_CTXT, 
                     (ITS_OCTET *)startKey,
                     keyLen, fptr);

    *startKey = 0;
    if (error != ITS_SUCCESS)
    {
         SCCP_ERROR(("GetDataFromFragList: DSM unable to free Segment.\n"));
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
SCLC_PutDataInFragList(ITS_OCTET *dsmKey, ITS_OCTET dsmKeyLen, 
                       SCCP_REASM_CTXT *ctxt,
                       ITS_OCTET *data, ITS_OCTET len)
{
    SCCP_DATA_FRAG* fptr;  
    int size = sizeof(SCCP_DATA_FRAG);
    int error;
    ITS_OCTET *key = ctxt->startFragKey;
    ITS_OCTET keyLen = ctxt->keyLen;
    ITS_INT refno;

    if(ctxt->keyLen == 0)
    {
        refno = ctxt->refno | 0x80000000;

        memcpy(key, dsmKey, dsmKeyLen);
        memcpy(key, &refno, MAX_SEG_REF_LEN);
        ctxt->keyLen = dsmKeyLen;

        fptr = (SCCP_DATA_FRAG *) DSM_FindNoLock(DSM_SccpFtGroupId,
                                                 DSM_TABLE_TTC_SCCP_CTXT,
                                                 (ITS_OCTET *)key, 
                                                 dsmKeyLen, &error);

        if (error != ITS_ENOTFOUND)
        {
            SCCP_CRITICAL(("PutDataInFragList: Couldn't alloc segment.\n"));

            return (ITS_ENOMEM);
        }

        if (error == ITS_ENOTFOUND)
        {

            fptr = (SCCP_DATA_FRAG *) DSM_AllocNoLock(DSM_SccpFtGroupId,
                                                      DSM_TABLE_TTC_SCCP_CTXT,
                                                      (ITS_OCTET *)key, 
                                                      dsmKeyLen, size, 
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


                return (error);
            }
        }

        error = DSM_LockRowNoLock(DSM_SccpFtGroupId, fptr);

        if (error != ITS_SUCCESS)
        {
            SCCP_CRITICAL(("GetNextLocalRef: DSM_LockRowNoLock failed\n"));

            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_TTC_SCCP_CTXT);

            return (error);
        }

        memcpy(&(fptr->data[fptr->len]), data, len);
        fptr->len += len;

        error = DSM_CommitNoLock(
                            DSM_SccpFtGroupId,
                            DSM_TABLE_TTC_SCCP_CTXT, 
                            (ITS_OCTET *)key, 
                            dsmKeyLen, fptr);

         if (error != ITS_SUCCESS)
         {
             SCCP_ERROR(("PutDataInFragList: Couldn't add context.\n"));

             return (error);
         }

         error = DSM_UnlockRowNoLock(DSM_SccpFtGroupId, fptr);

         if (error != ITS_SUCCESS)
         {
             SCCP_CRITICAL(("PutDataInFragList: DSM_UnlockRowNoLock failed\n"));

             DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_TTC_SCCP_CTXT);

             return (error);
          }

    }
    else
    {
        fptr = (SCCP_DATA_FRAG *) DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_TTC_SCCP_CTXT,
                                           (ITS_OCTET *)key, 
                                           keyLen, &error);

        if (error == ITS_ENOTFOUND)
        {
            SCCP_CRITICAL(("PutDataInFragList: Couldn't alloc segment.\n"));
    
            return (ITS_ENOMEM);
        }

        memcpy(&(fptr->data[fptr->len]), data, len);
        fptr->len += len;

        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_TTC_SCCP_CTXT, 
                           (ITS_OCTET *)key, 
                           keyLen, fptr);

         if (error != ITS_SUCCESS)
         {
             SCCP_ERROR(("PutDataInFragList: Couldn't add context.\n"));

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
SCLC_GetFirstSegmentData(ITS_OCTET *data, ITS_OCTET *startKey, ITS_OCTET keyLen)
{
    SCCP_DATA_FRAG* fptr;
    int error;

    fptr = (SCCP_DATA_FRAG *) DSM_Find(DSM_SccpFtGroupId,
                                       DSM_TABLE_TTC_SCCP_CTXT,
                                       (ITS_OCTET *)startKey, 
                                       keyLen, &error);

    if (error == ITS_ENOTFOUND)
    {
        SCCP_CRITICAL(("GetDataInFragList: Couldn't alloc segment.\n"));

        return (ITS_ENOMEM);
    }

    if(fptr->len > SCCP_MAX_SEG_DATA)
    {
        memcpy(data, fptr->data, SCCP_MAX_SEG_DATA);
    }
    else
    {
        memcpy(data, fptr->data, fptr->len);
    }

    error = DSM_Free(DSM_SccpFtGroupId,
                     DSM_TABLE_TTC_SCCP_CTXT, 
                     (ITS_OCTET *)startKey,
                     keyLen, fptr);

    *startKey = 0;
    if (error != ITS_SUCCESS)
    {

        SCCP_ERROR(("GetFirstSegment: DSM unable to free Segment.\n"));
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
void
SCLC_FreeFragList(ITS_OCTET *startKey, ITS_OCTET keyLen)
{
    SCCP_DATA_FRAG* fptr;
    int error;

    fptr = (SCCP_DATA_FRAG *) DSM_Find(DSM_SccpFtGroupId,
                                       DSM_TABLE_TTC_SCCP_CTXT,
                                       (ITS_OCTET *)startKey, 
                                       keyLen, &error);

    if (error == ITS_ENOTFOUND)
    {
        SCCP_CRITICAL(("GetDataInFragList: Couldn't alloc segment.\n"));

        return ;
    }

    error = DSM_Free(DSM_SccpFtGroupId,
                     DSM_TABLE_TTC_SCCP_CTXT, 
                     (ITS_OCTET *)startKey,
                     keyLen, fptr);

    *startKey = 0;
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("GetDataFromFragList: DSM unable to free Segment.\n"));

    }
    
    return;

}

