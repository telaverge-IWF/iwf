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
 *  ID: $Id: ansi-sclc.c,v 9.7.44.1 2014/09/17 07:01:58 jsarvesh Exp $
 *
 * LOG: $Log: ansi-sclc.c,v $
 * LOG: Revision 9.7.44.1  2014/09/17 07:01:58  jsarvesh
 * LOG: Changes done for removing warnings
 * LOG:
 * LOG: Revision 9.7.38.1  2014/09/15 07:23:32  jsarvesh
 * LOG: Changes done for removing Warnings
 * LOG:
 * LOG: Revision 9.7  2008/06/04 10:30:24  ssingh
 * LOG: ALU porting, B-0100LX-LUSG-00 (june 04,2008 base)
 * LOG:
 * LOG: Revision 9.6  2008/04/15 05:03:17  kramesh
 * LOG: Merged Persistent Branch Changes to current.
 * LOG:
 * LOG: Revision 9.5.2.1  2007/04/24 13:59:25  pspl
 * LOG: Fixed an issue with reassembly timer in ansi (Rahul)
 * LOG:
 * LOG: Revision 9.5  2007/01/11 12:43:35  yranade
 * LOG: Merge changes from 6.5.3 and Lucent branches
 * LOG:
 * LOG: Revision 9.4.24.1  2006/09/29 14:58:42  mshanmugam
 * LOG: Propagation of redundancy modifications from Kineto Branch (kramesh).
 * LOG:
 * LOG: Revision 9.4.4.2  2007/04/27 05:44:11  raghavendrabk
 * LOG: Alarm Format Changes for Family handling in OAM
 * LOG:
 * LOG: Revision 9.4.4.1  2007/02/02 14:04:27  raghavendrabk
 * LOG: Parallel Stack changes for Alarms and Statistics
 * LOG:
 * LOG: Revision 9.4  2005/06/02 12:28:48  adutta
 * LOG: Definitaion change
 * LOG:
 * LOG: Revision 9.3  2005/06/02 12:10:29  adutta
 * LOG: Fixed issue# 1920
 * LOG:
 * LOG: Revision 9.2  2005/05/30 11:35:21  adutta
 * LOG: XUDT implementation in ANSI
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:32  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.6  2005/03/21 13:53:34  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.5.2.1.6.2.8.3  2005/02/21 09:00:30  csireesh
 * LOG: OAM Validation Bug Fix
 * LOG:
 * LOG: Revision 7.5.2.1.6.2.8.2  2005/01/25 07:23:00  csireesh
 * LOG: Fixed Bug 1445 and removed Tab spaces
 * LOG:
 * LOG: Revision 7.5.2.1.6.2.8.1  2004/12/29 13:34:31  csireesh
 * LOG: SCCP bug propogation and OAM Changes
 * LOG:
 * LOG: Revision 7.5.2.1.6.2  2004/08/06 10:10:05  sswami
 * LOG: Alarm ID 232 is removed as it is similar to 248
 * LOG:
 * LOG: Revision 7.5.2.1.6.1  2004/06/22 11:47:52  csireesh
 * LOG: ALARMS and PEGS Propogation from TCS branch.
 * LOG:
 * LOG: Revision 7.5.2.1  2003/05/22 08:39:55  aganguly
 * LOG: XUDT with HopCounter violation, XUDTS is sent by the stack.
 * LOG:
 * LOG: Revision 7.5  2003/02/03 11:19:28  aganguly
 * LOG: Alarm rework after code review:
 * LOG:
 * LOG: Revision 7.4  2003/02/03 07:07:40  aganguly
 * LOG: Changes for SCCP alarms: clean up of unwanted alarms left for Release 6.4
 * LOG:
 * LOG: Revision 7.3  2003/01/16 16:23:33  mmiers
 * LOG: Tandem port, large context changes.
 * LOG:
 * LOG: Revision 7.2  2002/11/04 22:18:29  ngoel
 * LOG: swap clp, cdp before sending UDTS/XUDTS
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.7  2002/07/29 18:02:50  ngoel
 * LOG: correct peg type
 * LOG:
 * LOG: Revision 6.6  2002/07/12 15:53:44  labuser
 * LOG: get correct NI from SIO(use AND op)lbana.
 * LOG:
 * LOG: Revision 6.5  2002/06/21 22:49:38  mmiers
 * LOG: Adding support for China variant
 * LOG:
 * LOG: Revision 6.4  2002/05/20 21:11:50  mmiers
 * LOG: Flip PCs.  Add OAM implementation.  Try chaining fix.
 * LOG:
 * LOG: Revision 6.3  2002/03/14 22:52:31  mmiers
 * LOG: Convert TCAP and SCCP to OAM
 * LOG:
 * LOG: Revision 6.2  2002/03/07 17:42:30  mmiers
 * LOG: Most of ANSI SCCP merged.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:38  mmiers
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
 * LOG: Revision 5.1  2001/08/16 20:46:27  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:03  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:07:22  mmiers
 * LOG: Zero copy is in.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:27  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  1999/12/06 21:30:08  mmiers
 * LOG:
 * LOG:
 * LOG: Debug with HP's GDI.
 * LOG:
 * LOG: Revision 1.4.2.1  1999/12/06 21:27:26  mmiers
 * LOG:
 * LOG:
 * LOG: Debug with HP's GDI.
 * LOG:
 * LOG: Revision 1.4  1999/08/26 23:44:54  labuser
 * LOG:
 * LOG:
 * LOG: Alter GTT to include original PC (if any) and SSN (if any).
 * LOG:
 * LOG: Revision 1.3  1999/08/26 19:58:48  rsonak
 * LOG:
 * LOG:
 * LOG: Some protocol fixes.
 * LOG:
 * LOG: Revision 1.2  1999/06/21 23:20:40  mmiers
 * LOG:
 * LOG:
 * LOG: Fix UDTS transmission.
 * LOG:
 * LOG: Revision 1.1  1999/03/17 18:39:42  mmiers
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


#undef CCITT
#undef ANSI
#define ANSI

#include <its.h>
#include <its_dsm.h>
#include <its_mutex.h>
#include <its_thread.h>
#include <its_route.h>
#include <its_tq_trans.h>

#ident "$Id: ansi-sclc.c,v 9.7.44.1 2014/09/17 07:01:58 jsarvesh Exp $"

#include <ansi/sccp.h>

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

extern ITS_UINT         __local_seg_ref_number;

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
SCLCHandleRoutingFailure_ANSI(MTP3_HEADER* mtp3, ITS_OCTET mType,
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
    SCCP_HOP_COUNT* hop = NULL;
    ITS_OCTET dlen = 0;
    SCCP_ADDR *clp = NULL, *cdp = NULL;

    SCCP_DEBUG(("SCLCHandleRoutingFailure:\n"));
    
    /* Incr Routing Failure counter */
    PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_ROUTING_FAILURE);

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
    }

    if (!clp)
    {
        SCCP_WARNING(("SCLCHandleRoutingFailure: Don't know who to inform\n"));

        return (ITS_SUCCESS);
    }

    if ((SCCP_DecodeAddr_ANSI(clp, &addrInd, NULL, &ssn,
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

        return SCRCHandleSCLCMsg_ANSI(&resp, SCCP_MSG_UDTS, lies, 4);

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

        return SCRCHandleSCLCMsg_ANSI(&resp, SCCP_MSG_XUDTS, lies, 5);

    case SCCP_MSG_UDTS:
    case SCCP_MSG_XUDTS:

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
 *  csireesh  03-06-2005  Issue ID::1920          Hop Counter Check Added
 *
 *  csireesh  30-05-2005  ID::R0070 to R0130      Segmentation Implementation
 *
 ****************************************************************************/
ITS_INT
SCLCHandleSCRCMsg_ANSI(MTP3_HEADER* mtp3, ITS_OCTET mType,
                       ITS_SCCP_IE* ies, int ieCount,
                       ITS_UINT pc, ITS_OCTET ssn)
{
    ITS_INT ret, i;
    ITS_INT dataIndex = -1;
    ITS_INT cgAddrIndex = -1;
    SCCP_ADDR *callingPartyAddr;
    SCCP_HOP_COUNT* hc = NULL;
    ITS_INT segIEPres = ITS_FALSE;
    ITS_OCTET dsmKey[SCCP_MAX_ADDR_LEN + MAX_SEG_REF_LEN];
    ITS_OCTET keyLen;
    ITS_INT error;
    ITS_HDR hdr;
    ITS_EVENT event;
    ITS_OCTET ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

    SCCP_DEBUG(("SCLCHandleSCRCMsg: ssn %02x\n", ssn));

    PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_MSG_RECEIVED);

    /* IntelliSS7 routing */
    hdr.type = ITS_SCCP;
    hdr.context.ssn = ssn;

    /* add in the routing label */
    ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
    ies[ieCount].param_length = sizeof(MTP3_HEADER);
    ies[ieCount].param_data.routingLabel = *mtp3;
    ieCount++;

    if (BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors,
                              SCCP_B_use_SCMG) && ssn == SCCP_SSN_SCCPMGMT)
    {
        return SCMGHandleSCLCMsg_ANSI(mtp3, mType, ies, ieCount);
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
    }

    if (hc)
    {
        if (hc->count < 0 || hc->count > SCCP_MAX_HOP_COUNT)
        {
            SCCP_ERROR(("SCLCHandleSCRCMsg: Hop count exceeded\n"));
            /* ERROR - Incoming Message - Hop Count Exceeded. */

            PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_HOP_COUNTER_VIOLATION_ERR);

            SCLCHandleRoutingFailure_ANSI(mtp3, mType, ies,
                                           ieCount,
                                           SCCP_RET_HOP_COUNT_EXCEEDED);

            return ITS_SUCCESS;
        }
    }

    switch (mType)
    {
    case SCCP_MSG_UDT:
        PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_UDT_RCVD);

        if (SCCP_Encode(ies, ieCount, mType, &event, &hdr,
                        &SCCP_UDT_Desc_ANSI) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCLCHandleSCRCMsg: Encode failure\n"));
            return (ITS_EINVALIDARGS);
        }

        break;

    case SCCP_MSG_XUDT:
       PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_XUDT_RCVD);

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

                    if( SCCP_AddSegmentRef_ANSI(dsmKey, keyLen,  maxDataLen,
                                                 remainingSegment, dataLen,
                                                 data, segRefNum)
                                                 != ITS_SUCCESS)
                    {
                         /* Easy way to send XUDTS */
                         SCCP_ERROR(("Failed to add segment refrence"));
                         PEG_IncrPeg(ANSI_SCCP_Pegs,
                                               PEG_SCCP_REMOTE_REASSEMBLE_ERR);
                         SCLCHandleRoutingFailure_ANSI(mtp3, mType, ies,
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
                                                        DSM_TABLE_ANSI_SCCP_CTXT,
                                                        (ITS_OCTET *)dsmKey,
                                                         keyLen,
                                                         &error);

                    if (error != ITS_SUCCESS)
                    {

                        switch (error)
                        {
                            case (ITS_EBADMUTEX):
                            SCCP_CRITICAL(("Couldn't acquire mutex.\n"));

                            break;

                            case (ITS_ENOTFOUND):
                            SCCP_WARNING(("HandleSCRCMsg: Could not find "
                                           " context.\n"));

                            break;

                            case (ITS_EINUSE):
                            SCCP_CRITICAL(("DSM Row Locked.\n"));

                            break;
                        }

                        SCLCHandleRoutingFailure_ANSI(mtp3, mType, ies,
                                            ieCount, SCCP_RET_ERR_IN_TRANSPORT);

                        return (ITS_ENOCONN);
                    }

                    /* Out if sequence segment */
                    if (ctxt->remainingSegment != remainingSegment + 1)
                    {
                        /* send XUDTS */
                        /* perform clean up */

                        SCCP_ERROR(("Remainig segment field not correct:\n"));

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

                        SCLCHandleRoutingFailure_ANSI(mtp3, mType, ies,
                                            ieCount, SCCP_RET_ERR_IN_TRANSPORT);

                        SCCP_DeleteSegmentRef_ANSI(dsmKey, keyLen, ctxt);

                        return ITS_SUCCESS;
                    }

                    dataLen = ies[dataIndex].param_length;
                    data = ies[dataIndex].param_data.userData.data;

                    if ((ctxt->totalDataLen + dataLen) > ctxt->maxDataLen)
                    {
                        /* perform clean up */
                         SCCP_ERROR(("Data length exceeds max expected data"));
                         PEG_IncrPeg(ANSI_SCCP_Pegs,
                                     PEG_SCCP_REMOTE_REASSEMBLE_ERR);

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

                         SCLCHandleRoutingFailure_ANSI(mtp3, mType, ies,
                                            ieCount, SCCP_RET_ERR_IN_TRANSPORT);

                         SCCP_DeleteSegmentRef_ANSI(dsmKey, keyLen, ctxt);

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
                            PEG_IncrPeg(ANSI_SCCP_Pegs,
                                        PEG_SCCP_REMOTE_REASSEMBLE_ERR);
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

                            SCLCHandleRoutingFailure_ANSI(mtp3, mType, ies,
                                               ieCount,
                                               SCCP_RET_ERR_IN_LOCAL_PROCESS);

                            SCCP_DeleteSegmentRef_ANSI(dsmKey, keyLen, ctxt);

                            return ITS_SUCCESS;
                        }

                        ctxt->totalDataLen += dataLen;

                        error = DSM_Commit(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT,
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
                        SCCP_DEBUG(("Received last segment\n"));

                        ies[dataIndex].param_id = SCCP_PRM_LONG_DATA;
                        memcpy(tmp, data, dataLen);
                        ies[dataIndex].param_data.longData.len =
                                                 ctxt->totalDataLen + dataLen;

                        SCLC_GetDataFromFragList(ies[dataIndex].param_data.longData.data, 
                                                 ctxt->startFragKey, ctxt->keyLen);

                        ctxt->keyLen = 0;

                        memcpy(ies[dataIndex].param_data.longData.data +
                               ctxt->totalDataLen, tmp, dataLen);

                        if (SCCP_Encode(ies, ieCount, SCCP_MSG_LUDT,
                                        &event, &hdr,
                                        &SCCP_LUDT_Desc) !=
                                        ITS_SUCCESS)
                        {
                            SCCP_ERROR(("SCLCHandleSCRCMsg: Encode failure\n"));

                            SCCP_DeleteSegmentRef_ANSI(dsmKey, keyLen, ctxt);

                            return (ITS_EINVALIDARGS);
                        }

                        SCCP_DeleteSegmentRef_ANSI(dsmKey, keyLen, ctxt);

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
        PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_UDTS_RCVD);

        if (SCCP_Encode(ies, ieCount, mType, &event, &hdr,
                        &SCCP_UDTS_Desc_ANSI) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCLCHandleSCRCMsg: Encode failure\n"));

            return (ITS_EINVALIDARGS);
        }

        break;

    case SCCP_MSG_XUDTS:
        PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_XUDTS_RCVD);

        if (SCCP_Encode(ies, ieCount, mType, &event, &hdr,
                        &SCCP_XUDTS_Desc_ANSI) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCLCHandleSCRCMsg: Encode failure\n"));

            return (ITS_EINVALIDARGS);
        }

        break;

    default:
        SCCP_ERROR(("SCLCHandleSCRCMsg: Bad message type\n"));
        break;
    }

    event.src = ITS_SCCP_ANSI_SRC;
    ITS_SET_CTXT(&event.data[1], hdr.context.ssn);

    ret = ROUTE_SendToRouteContext(pc, &event,
                                   ROUTE_DPC_SIO_SSN,
                                   FAMILY_ANSI,
                                   ROUTE_SIO_SCCP | ni,
                                   (ITS_OCTET)hdr.context.ssn,
                                   ITS_SS7_DEFAULT_LINK_SET,
                                   ITS_SS7_DEFAULT_LINK_CODE,
                                   ITS_SS7_DEFAULT_PRI,
                                   ITS_SS7_DEFAULT_SLS);

    if (ret != ITS_SUCCESS)
    {
        SCCP_WARNING(("SCLCHandleSCRCMsg: no route to dest.\n"));
        /* Discarding Message - No Route to Destination - PC: %1  SSN %2  */
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
SCLCHandleSCMGMsg_ANSI(MTP3_HEADER* mtp3, ITS_OCTET mType,
                       ITS_SCCP_IE* ies, int ieCount)
{
    switch (mType)
    {
    case SCCP_MSG_UDT:
        return SCRCHandleSCLCMsg_ANSI(mtp3, SCCP_MSG_UDT, ies, ieCount);

    case SCCP_MSG_XUDT:
        return SCRCHandleSCLCMsg_ANSI(mtp3, SCCP_MSG_XUDT, ies, ieCount);

    case SCCP_MSG_UDTS:
        return SCRCHandleSCLCMsg_ANSI(mtp3, SCCP_MSG_UDTS, ies, ieCount);

    case SCCP_MSG_XUDTS:
        return SCRCHandleSCLCMsg_ANSI(mtp3, SCCP_MSG_XUDTS, ies, ieCount);
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
 ****************************************************************************/
int
SCLCHandleAPPMsg_ANSI(ITS_EVENT* event)
{
    ITS_SCCP_IE ies[32];
    ITS_INT ieCount;
    ITS_INT ret, i;
    MTP3_HEADER* mtp3 = NULL;

    SCCP_DEBUG(("SCLCHandleAPPMsg:\n"));
    PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_MSG_SENT);

    switch (SCCP_MSG_TYPE(event))
    {
    case SCCP_MSG_UDT:
        PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_UDT_SENT);

        if ((ret = SCCP_Decode_ANSI(ies, &ieCount, event,
                                    &SCCP_UDT_Desc_ANSI)) != ITS_SUCCESS)
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

        if (mtp3 == NULL)
        {
            /* ERROR - Discarding %1 Message - Defective MTP3 header.  */
            SCCP_Alarm_ANSI(233, __FILE__, __LINE__, "family=%s:mType=%s", "ANSI", "UDT");

            return (ITS_EMISSMAND);
        }

        return SCRCHandleSCLCMsg_ANSI(mtp3, SCCP_MSG_UDT, ies, ieCount);

    case SCCP_MSG_XUDT:
        PEG_IncrPeg(ANSI_SCCP_Pegs,   PEG_SCCP_USER_XUDT_SENT);

        if ((ret = SCCP_Decode_ANSI(ies, &ieCount, event,
                                    &SCCP_XUDT_Desc_ANSI)) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCLCHandleAPPMsg: Decode of XUDT failed\n"));

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
            /* ERROR - Discarding %1 Message - Defective MTP3 header.  */
            SCCP_Alarm_ANSI(233, __FILE__, __LINE__, "family=%s:mType=%s", "ANSI", "XUDT");

            return (ITS_EMISSMAND);
        }

        return SCRCHandleSCLCMsg_ANSI(mtp3, SCCP_MSG_XUDT, ies, ieCount);

    case SCCP_MSG_UDTS:
        PEG_IncrPeg(ANSI_SCCP_Pegs,   PEG_SCCP_USER_UDTS_SENT);

        if ((ret = SCCP_Decode_ANSI(ies, &ieCount, event,
                                    &SCCP_UDTS_Desc_ANSI)) != ITS_SUCCESS)
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
            /* ERROR - Discarding %1 Message - Defective MTP3 header.  */
            SCCP_Alarm_ANSI(233, __FILE__, __LINE__,"family=%s:mType=%s", "ANSI", "UDTS");

            return (ITS_EMISSMAND);
        }

        return SCRCHandleSCLCMsg_ANSI(mtp3, SCCP_MSG_UDTS, ies, ieCount);

    case SCCP_MSG_XUDTS:
        PEG_IncrPeg(ANSI_SCCP_Pegs,   PEG_SCCP_USER_XUDTS_SENT);

        if ((ret = SCCP_Decode_ANSI(ies, &ieCount, event,
                                    &SCCP_XUDTS_Desc_ANSI)) != ITS_SUCCESS)
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
            /* ERROR - Discarding %1 Message - Defective MTP3 header.  */
            SCCP_Alarm_ANSI(233, __FILE__, __LINE__,"family=%s:mType=%s", "ANSI", "XUDTS");

            return (ITS_EMISSMAND);
        }

        return SCRCHandleSCLCMsg_ANSI(mtp3, SCCP_MSG_XUDTS, ies, ieCount);
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
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  csireesh  30-05-2005  ID::R0070 to R0130      Segmentation Implementation
 *
 ****************************************************************************/
ITS_INT
SCLCHandleReasmTimer_ANSI(ITS_TimerData* td)
{
    SCCP_REASM_CTXT ctxt;
    SCCP_REASM_CTXT *ct = NULL;
    ITS_INT error;
    ITS_OCTET dsmKey[SCCP_MAX_ADDR_LEN + MAX_SEG_REF_LEN];

    memcpy(&ctxt, td->context, sizeof(SCCP_REASM_CTXT));

    /*
     Bug Id : 60
     Description : ASP was performing reassembly even after reassembly timer get expire.
    */
    memcpy(dsmKey, ctxt.reasmKey, ctxt.reasmKeyLen);

    ct = (SCCP_REASM_CTXT *) DSM_Find(DSM_SccpFtGroupId,
                                      DSM_TABLE_ANSI_SCCP_CTXT,
                                      (ITS_OCTET *)dsmKey,
                                      ctxt.reasmKeyLen, &error);
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
                     DSM_TABLE_ANSI_SCCP_CTXT,
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
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  csireesh  30-05-2005  ID::R0070 to R0130      Segmentation Implementation
 *
 ****************************************************************************/
ITS_INT
SCLC_GetDataFromFragList(ITS_OCTET *data,
                         ITS_OCTET *startKey, ITS_OCTET keyLen)
{
    SCCP_DATA_FRAG* fptr;
    ITS_INT error;

    fptr = (SCCP_DATA_FRAG *) DSM_Find(DSM_SccpFtGroupId,
                                       DSM_TABLE_ANSI_SCCP_CTXT,
                                       (ITS_OCTET *)startKey,
                                       keyLen, &error);

    if (error == ITS_ENOTFOUND)
    {
        SCCP_CRITICAL(("GetDataInFragList: Couldn't alloc segment.\n"));

        return (ITS_ENOMEM);
    }

    memcpy(data, fptr->data, fptr->len);

    error = DSM_Free(DSM_SccpFtGroupId,
                     DSM_TABLE_ANSI_SCCP_CTXT,
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
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  csireesh  30-05-2005  ID::R0070 to R0130      Segmentation Implementation
 *
 ****************************************************************************/
ITS_INT
SCLC_PutDataInFragList(ITS_OCTET *dsmKey, ITS_OCTET dsmKeyLen,
                       SCCP_REASM_CTXT *ctxt,
                       ITS_OCTET *data, ITS_OCTET len)
{
    SCCP_DATA_FRAG* fptr;
    ITS_INT size = sizeof(SCCP_DATA_FRAG);
    ITS_INT error;
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
                                                 DSM_TABLE_ANSI_SCCP_CTXT,
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
                                                      DSM_TABLE_ANSI_SCCP_CTXT,
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

            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CTXT);

            return (error);
        }

        memcpy(&(fptr->data[fptr->len]), data, len);
        fptr->len += len;

        error = DSM_CommitNoLock(
                            DSM_SccpFtGroupId,
                            DSM_TABLE_ANSI_SCCP_CTXT,
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

             DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CTXT);

             return (error);
          }

    }
    else
    {
        fptr = (SCCP_DATA_FRAG *) DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT,
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
                           DSM_TABLE_ANSI_SCCP_CTXT,
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
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  csireesh  30-05-2005  ID::R0070 to R0130      Segmentation Implementation
 *
 ****************************************************************************/
ITS_INT
SCLC_GetFirstSegmentData(ITS_OCTET *data, ITS_OCTET *startKey, ITS_OCTET keyLen)
{
    SCCP_DATA_FRAG* fptr;
    ITS_INT error;

    fptr = (SCCP_DATA_FRAG *) DSM_Find(DSM_SccpFtGroupId,
                                       DSM_TABLE_ANSI_SCCP_CTXT,
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
                     DSM_TABLE_ANSI_SCCP_CTXT,
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
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  csireesh  30-05-2005  ID::R0070 to R0130      Segmentation Implementation
 *
 ****************************************************************************/
void
SCLC_FreeFragList(ITS_OCTET *startKey, ITS_OCTET keyLen)
{
    SCCP_DATA_FRAG* fptr;
    int error;

    fptr = (SCCP_DATA_FRAG *) DSM_Find(DSM_SccpFtGroupId,
                                       DSM_TABLE_ANSI_SCCP_CTXT,
                                       (ITS_OCTET *)startKey,
                                       keyLen, &error);

    if (error == ITS_ENOTFOUND)
    {
        SCCP_CRITICAL(("GetDataInFragList: Couldn't alloc segment.\n"));

        return ;
    }

    error = DSM_Free(DSM_SccpFtGroupId,
                     DSM_TABLE_ANSI_SCCP_CTXT,
                     (ITS_OCTET *)startKey,
                     keyLen, fptr);

    *startKey = 0;
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("GetDataFromFragList: DSM unable to free Segment.\n"));

    }

    return;
}

