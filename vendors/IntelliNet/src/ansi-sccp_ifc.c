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
 *  ID: $Id: ansi-sccp_ifc.c,v 9.2 2008/06/04 10:30:24 ssingh Exp $
 *
 * LOG: $Log: ansi-sccp_ifc.c,v $
 * LOG: Revision 9.2  2008/06/04 10:30:24  ssingh
 * LOG: ALU porting, B-0100LX-LUSG-00 (june 04,2008 base)
 * LOG:
 * LOG: Revision 9.1.10.2  2007/04/27 05:43:02  raghavendrabk
 * LOG: Alarm Format Changes for Family handling in OAM
 * LOG:
 * LOG: Revision 9.1.10.1  2007/02/02 14:00:22  rdangi
 * LOG: Parallel Stack changes for Alarms and Statistics
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:32  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:53:34  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.14.1.12.2  2005/02/21 09:00:30  csireesh
 * LOG: OAM Validation Bug Fix
 * LOG:
 * LOG: Revision 7.1.14.1.12.1  2004/12/29 13:32:35  csireesh
 * LOG: SCCP bug propogation and OAM Changes
 * LOG:
 * LOG: Revision 7.1.14.1  2004/06/22 11:47:52  csireesh
 * LOG: ALARMS and PEGS Propogation from TCS branch.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.5  2002/07/12 15:59:05  labuser
 * LOG: build correct SIO before sending UIS
 * LOG:
 * LOG: Revision 6.4  2002/05/29 22:43:47  mmiers
 * LOG: Signature change
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
 * LOG: Revision 5.7  2002/01/02 21:02:44  mmiers
 * LOG: Back out the routing label change.  It breaks hybrid stack builds.
 * LOG:
 * LOG: Revision 5.6  2002/01/02 19:56:08  mmiers
 * LOG: Convert to using long names (everything but TCAP).
 * LOG:
 * LOG: Revision 5.5  2001/12/15 01:19:50  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.4  2001/11/09 20:19:54  mmiers
 * LOG: Don't force the vendor lib to be part of the engine.  Make into
 * LOG: DLL instead.
 * LOG:
 * LOG: Revision 5.3  2001/09/25 21:35:20  mmiers
 * LOG: Fix up SCCP routing and SCMG.
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:27  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:03  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.3  2001/03/14 22:07:09  mmiers
 * LOG: Include ISUP in the engine.
 * LOG:
 * LOG: Revision 3.2  2001/02/06 16:07:34  mmiers
 * LOG: Tweaks.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:27  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.2  1999/12/18 00:21:07  mmiers
 * LOG:
 * LOG:
 * LOG: Convert vendor lib to new format.
 * LOG:
 * LOG: Revision 2.1  1999/12/06 21:30:08  mmiers
 * LOG:
 * LOG:
 * LOG: Debug with HP's GDI.
 * LOG:
 * LOG: Revision 1.2.2.1  1999/12/06 21:27:26  mmiers
 * LOG:
 * LOG:
 * LOG: Debug with HP's GDI.
 * LOG:
 * LOG: Revision 1.2  1999/08/26 23:44:54  labuser
 * LOG:
 * LOG:
 * LOG: Alter GTT to include original PC (if any) and SSN (if any).
 * LOG:
 * LOG: Revision 1.1  1999/03/17 18:39:42  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol commit.  Still have to finish TCAP.
 * LOG:
 * LOG: Revision 1.23  1999/03/16 20:58:28  mmiers
 * LOG:
 * LOG:
 * LOG: Fix interface names, start ITU TCAP.
 * LOG:
 * LOG: Revision 1.22  1998/12/08 19:14:11  rsonak
 * LOG: Add an assertion to track memory overruns.
 * LOG:
 * LOG: Revision 1.21  1998/11/12 01:42:44  mmiers
 * LOG: Continue debugging SSP/SSA.
 * LOG:
 * LOG: Revision 1.20  1998/11/05 22:15:32  mmiers
 * LOG: Add UIS/UOS/CONG user messages.
 * LOG:
 * LOG: Revision 1.19  1998/11/05 21:34:20  mmiers
 * LOG: Add UIS, UOS routines.
 * LOG:
 * LOG: Revision 1.18  1998/11/05 21:30:32  mmiers
 * LOG: Working on pause/resume.
 * LOG:
 * LOG: Revision 1.17  1998/10/15 01:19:14  mmiers
 * LOG: Remove assert().  We shouldn't terminate, we should gracefully work
 * LOG: around errors.
 * LOG:
 * LOG: More work on SCCP COC.  Added connection timer, release timer,
 * LOG: reset timer.  Check for proper handling of missing information.
 * LOG:
 * LOG: Revision 1.16  1998/09/27 00:04:09  mmiers
 * LOG: More work on SCCP.
 * LOG:
 * LOG: Revision 1.15  1998/09/21 18:31:38  mmiers
 * LOG: Get C-trace hooked up and working.
 * LOG:
 * LOG: Revision 1.14  1998/09/10 16:02:47  mmiers
 * LOG: Forgot to release the mutex on the connection request.
 * LOG:
 * LOG: Revision 1.13  1998/08/29 00:49:59  whu
 * LOG: SCCP changes for Wei.
 * LOG:
 * LOG: Revision 1.12  1998/07/21 21:28:29  mmiers
 * LOG: Modify SCCP implementation.
 * LOG:
 * LOG: Revision 1.11  1998/07/13 22:05:23  whu
 * LOG: Optional parameters are NEVER mandatory.
 * LOG:
 * LOG: Revision 1.10  1998/07/07 15:21:21  mmiers
 * LOG: Bug fixes for TCAP.
 * LOG:
 * LOG: Revision 1.9  1998/07/03 19:42:19  mmiers
 * LOG: SCCP as a separate thread.
 * LOG:
 * LOG: Revision 1.8  1998/06/24 16:11:38  mmiers
 * LOG: Debugging SCCP; also straighten out the ITS_Transport issues.
 * LOG:
 * LOG: Revision 1.7  1998/06/23 22:56:58  mmiers
 * LOG: Debugging SCCP.
 * LOG:
 * LOG: Revision 1.6  1998/06/23 00:49:35  mmiers
 * LOG: Bug hunting.
 * LOG:
 * LOG: Revision 1.5  1998/06/23 00:35:37  mmiers
 * LOG: Debugging SCCP.
 * LOG:
 * LOG: Revision 1.4  1998/06/22 22:58:18  gkosasi
 * LOG: Fix bugs in IntelliNet vendor code.  Missing breaks during IE processing.
 * LOG:
 * LOG: Revision 1.3  1998/06/19 22:25:28  mmiers
 * LOG: Nearing the end for TCAP.  Initial implementation of SCCP.
 * LOG:
 * LOG: Revision 1.2  1998/06/17 21:32:29  mmiers
 * LOG: Get Vendor straightened out.
 * LOG:
 * LOG: Revision 1.1  1998/06/17 20:46:32  mmiers
 * LOG: Add vendor IntelliNet.
 * LOG:
 * LOG: Revision 1.8  1998/06/17 19:57:03  mmiers
 * LOG: Retain backwards compatibility.
 * LOG:
 * LOG: Revision 1.7  1998/06/15 16:29:05  mmiers
 * LOG: Testing TCAP.
 * LOG:
 * LOG: Revision 1.6  1998/06/05 20:08:57  mmiers
 * LOG: Tweaking things for the release.  Now to retag.
 * LOG:
 * LOG: Revision 1.5  1998/06/01 22:32:00  mmiers
 * LOG: Raw documentation for SCCP.
 * LOG:
 * LOG: Revision 1.4  1998/05/14 20:41:44  mmiers
 * LOG: Update SCCP (read implement).  The rest are modifications to get
 * LOG: further the implementation of worker threads.
 * LOG:
 * LOG: Revision 1.3  1998/05/05 00:00:03  mmiers
 * LOG: Add new signatures, remove TCSM code from tcap.h.
 * LOG:
 * LOG: Revision 1.2  1998/05/04 22:57:37  mmiers
 * LOG: Much work on naming consistency.  This will force a TCAP change.
 * LOG:
 * LOG: Revision 1.1  1998/05/01 14:04:22  mmiers
 * LOG: Update with interface routines.  Need to fill in checks for mandatory
 * LOG: parms, and call ifc routines.
 * LOG:
 * LOG: Revision 1.2  1998/04/07 15:51:54  mmiers
 * LOG: Update library to reflect vendor changes.
 * LOG:
 * LOG: Revision 1.1  1998/02/25 21:42:28  mmiers
 * LOG: Add in initial implementation of SCCP interface.
 * LOG:
 *
 ****************************************************************************/

#include <string.h>

#undef CCITT
#undef ANSI
#define ANSI

#include <its.h>
#include <its_hash.h>
#include <its_route.h>
#include <its_transports.h>
#include <its_license.h>
#include <its_assertion.h>

#ident "$Id: ansi-sccp_ifc.c,v 9.2 2008/06/04 10:30:24 ssingh Exp $"

#include <ansi/sccp.h>

#include "sccp_intern.h"

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function builds and sends a generic SCCP message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      hdr - the context for this message
 *      ies - the information elements that make up the message
 *      ieCount - the number of information elements
 *      mandatory - a vector containing the mandatory information element
 *          ids
 *      mandatoryCount - the size of the mandatory vector
 *      variable - a vector containing the variable information element
 *          ids
 *      variableCount - the size of the variable vector
 *      optional - a vector containing the optional information element
 *          ids
 *      optionalCount - the size of the optional vector
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the message is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
INTELLINET_SendSCCPEvent_ANSI(ITS_HANDLE handle, ITS_OCTET type,
                              ITS_HDR *hdr,
                              ITS_SCCP_IE *ies, int ieCount,
                              SCCP_MSG_DESC* desc)
{
    ITS_EVENT ev;
    int ret;

    ITS_C_ASSERT(ies != NULL && hdr != NULL && desc != NULL);

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_ANSI_SCCP))
    {
        /* CIRTICAL - ANSI SCCP License not found */
        SCCP_Alarm_ANSI(27, __FILE__, __LINE__, "family=%s", "ANSI");

        return (ITS_ENOLICENSE);
    }

    if ((ret = SCCP_Encode(ies, ieCount, type,
                           &ev, hdr, desc)) != ITS_SUCCESS)
    {
        /* Minor - Outgoing Message - Discarding Message - Invalid or Corrupted. */
        return (ret);
    }
    
    ev.src = TRANSPORT_INSTANCE(handle);

    return TRANSPORT_PutEvent(ITS_SCCP_ANSI_SRC, &ev);
}

/*.implementation:external
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
INTELLINET_SendUOS_ANSI(ITS_HANDLE handle, ITS_OCTET ni,
                        ITS_UINT pc, ITS_OCTET ssn)
{
    ITS_SCCP_IE lies[32];
    ITS_OCTET addrInd;
    MTP3_HEADER resp;
    ITS_HDR hdr;
    ITS_EVENT event;
    SCCP_SCMG_ANSI scmg;

    PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_LOCAL_SS_PROHIBITED);

    if (!BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors,
                              SCCP_B_use_SCMG))
    {
        return (ITS_SUCCESS);
    }

    /* build the routing label */
    resp.sio = MTP3_SIO_SCCP | ni;
    MTP3_RL_SET_DPC_VALUE(resp.label, pc);
    MTP3_RL_SET_OPC_VALUE(resp.label, pc);
    MTP3_RL_SET_SLS(resp.label, 0);

    /* protocol class */
    lies[0].param_id = SCCP_PRM_PROTOCOL_CLASS;
    lies[0].param_length = sizeof(SCCP_PROT_CLASS);
    lies[0].param_data.protocolClass.pclass = SCCP_PCLASS_0;

    /* build common addrInd. NOTE: Apparently, we do NOT include PC */
    addrInd = SCCP_CPA_HAS_SSN|SCCP_CPA_ROUTE_SSN;

    /* calledParty */
    lies[1].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
    lies[1].param_length = sizeof(SCCP_ADDR);
    SCCP_EncodeAddr(&lies[1].param_data.calledPartyAddr,
                    addrInd, 0, SCCP_SSN_SCCPMGMT, NULL, 0);

    /* callingParty */
    lies[2].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
    lies[2].param_length = sizeof(SCCP_ADDR);
    SCCP_EncodeAddr(&lies[2].param_data.callingPartyAddr,
                    addrInd, 0, ssn, NULL, 0);

    /* copy in SCMG */
    scmg.type = SCCP_SCMG_SS_UOS;
    scmg.ssn = ssn;
    MTP3_PC_SET_VALUE(scmg.pointCode, pc);
    scmg.multiplicity = SCCP_SCMG_SMI_SOLO;

    lies[3].param_id = SCCP_PRM_DATA;
    lies[3].param_length = sizeof(SCCP_SCMG_ANSI);
    memcpy(lies[3].param_data.userData.data,
           &scmg,
           sizeof(SCCP_SCMG_ANSI));

    lies[4].param_id = SCCP_PRM_ROUTING_LABEL;
    lies[4].param_length = sizeof(MTP3_HEADER);
    lies[4].param_data.routingLabel = resp;

    hdr.type = ITS_SCCP;
    hdr.context.ssn = ssn;
    SCCP_Encode(lies, 5, SCCP_MSG_UDT, &event, &hdr, &SCCP_UDT_Desc);
    event.src = TRANSPORT_INSTANCE(handle);

    /* User Out of Service - PC: %1  SSN %2  */
    SCCP_Alarm_ANSI(28, __FILE__, __LINE__,
                    "family=%s:pc=%x:ssn=%x", "ANSI", pc, ssn);

    return TRANSPORT_PutEvent(ITS_SCCP_ANSI_SRC, &event);
}

/*.implementation:external
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
INTELLINET_SendUIS_ANSI(ITS_HANDLE handle, ITS_OCTET ni,
                        ITS_UINT pc, ITS_OCTET ssn)
{
    ITS_SCCP_IE lies[32];
    ITS_OCTET addrInd;
    MTP3_HEADER resp;
    ITS_HDR hdr;
    ITS_EVENT event;
    SCCP_SCMG_ANSI scmg;

    PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_LOCAL_SS_ALLOWED);

    if (!BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors,
                              SCCP_B_use_SCMG))
    {
        return (ITS_SUCCESS);
    }

    /* build the routing label */

    resp.sio = MTP3_SIO_SCCP | ni;
    MTP3_RL_SET_DPC_VALUE(resp.label, pc);
    MTP3_RL_SET_OPC_VALUE(resp.label, pc);
    MTP3_RL_SET_SLS(resp.label, 0);

    /* protocol class */
    lies[0].param_id = SCCP_PRM_PROTOCOL_CLASS;
    lies[0].param_length = sizeof(SCCP_PROT_CLASS);
    lies[0].param_data.protocolClass.pclass = SCCP_PCLASS_0;

    /* build common addrInd. NOTE: Apparently, we do NOT include PC */
    addrInd = SCCP_CPA_HAS_SSN|SCCP_CPA_ROUTE_SSN;

    /* calledParty */
    lies[1].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
    lies[1].param_length = sizeof(SCCP_ADDR);
    SCCP_EncodeAddr(&lies[1].param_data.calledPartyAddr,
                    addrInd, 0, SCCP_SSN_SCCPMGMT, NULL, 0);

    /* callingParty */
    lies[2].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
    lies[2].param_length = sizeof(SCCP_ADDR);
    SCCP_EncodeAddr(&lies[2].param_data.callingPartyAddr,
                    addrInd, 0, ssn, NULL, 0);

    /* copy in SCMG */
    scmg.type = SCCP_SCMG_SS_UIS;
    scmg.ssn = ssn;
    MTP3_PC_SET_VALUE(scmg.pointCode, pc);
    scmg.multiplicity = SCCP_SCMG_SMI_SOLO;

    lies[3].param_id = SCCP_PRM_DATA;
    lies[3].param_length = sizeof(SCCP_SCMG_ANSI);
    memcpy(lies[3].param_data.userData.data,
           &scmg,
           sizeof(SCCP_SCMG_ANSI));

    lies[4].param_id = SCCP_PRM_ROUTING_LABEL;
    lies[4].param_length = sizeof(MTP3_HEADER);
    lies[4].param_data.routingLabel = resp;

    hdr.type = ITS_SCCP;
    hdr.context.ssn = ssn;
    SCCP_Encode(lies, 5, SCCP_MSG_UDT, &event, &hdr, &SCCP_UDT_Desc);
    event.src = TRANSPORT_INSTANCE(handle);

    /* User In Service - PC: %1  SSN %2  */
    SCCP_Alarm_ANSI(29, __FILE__, __LINE__,
                    "family=%s:pc=%x:ssn=%x", "ANSI", pc, ssn);

    return TRANSPORT_PutEvent(ITS_SCCP_ANSI_SRC, &event);
}

/*.implementation:external
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
INTELLINET_SetCongestion_ANSI(ITS_HANDLE handle, ITS_OCTET ni,
                              ITS_UINT pc, ITS_OCTET ssn, ITS_OCTET cong)
{
    ITS_SCCP_IE lies[32];
    ITS_OCTET addrInd;
    MTP3_HEADER resp;
    ITS_HDR hdr;
    ITS_EVENT event;
    SCCP_SCMG_ANSI scmg;

    PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_LOCAL_SS_CONGESTED);

    if (!BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors,
                              SCCP_B_use_SCMG))
    {
        return (ITS_SUCCESS);
    }

    /* build the routing label */
    resp.sio = MTP3_SIO_SCCP;
    MTP3_RL_SET_DPC_VALUE(resp.label, pc);
    MTP3_RL_SET_OPC_VALUE(resp.label, pc);
    MTP3_RL_SET_SLS(resp.label, 0);

    /* protocol class */
    lies[0].param_id = SCCP_PRM_PROTOCOL_CLASS;
    lies[0].param_length = sizeof(SCCP_PROT_CLASS);
    lies[0].param_data.protocolClass.pclass = SCCP_PCLASS_0;

    /* build common addrInd. NOTE: Apparently, we do NOT include PC */
    addrInd = SCCP_CPA_HAS_SSN|SCCP_CPA_ROUTE_SSN;

    /* calledParty */
    lies[1].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
    lies[1].param_length = sizeof(SCCP_ADDR);
    SCCP_EncodeAddr(&lies[1].param_data.calledPartyAddr,
                    addrInd, 0, SCCP_SSN_SCCPMGMT, NULL, 0);

    /* callingParty */
    lies[2].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
    lies[2].param_length = sizeof(SCCP_ADDR);
    SCCP_EncodeAddr(&lies[2].param_data.callingPartyAddr,
                    addrInd, 0, ssn, NULL, 0);

    /* copy in SCMG */
    scmg.type = SCCP_SCMG_SS_CONG;
    scmg.ssn = ssn;
    MTP3_PC_SET_VALUE(scmg.pointCode, pc);
    scmg.multiplicity = SCCP_SCMG_SMI_SOLO;

    lies[3].param_id = SCCP_PRM_DATA;
    lies[3].param_length = sizeof(SCCP_SCMG_ANSI);
    memcpy(lies[3].param_data.userData.data,
           &scmg,
           sizeof(SCCP_SCMG_ANSI));

    lies[4].param_id = SCCP_PRM_ROUTING_LABEL;
    lies[4].param_length = sizeof(MTP3_HEADER);
    lies[4].param_data.routingLabel = resp;

    hdr.type = ITS_SCCP;
    hdr.context.ssn = ssn;
    SCCP_Encode(lies, 5, SCCP_MSG_UDT, &event, &hdr, &SCCP_UDT_Desc);
    event.src = TRANSPORT_INSTANCE(handle);

    /* User In Congested - PC: %1  SSN %2  */
    SCCP_Alarm_ANSI(30, __FILE__, __LINE__,
                    "family=%s:pc=%x:ssn=%x", "ANSI", pc, ssn);

    return TRANSPORT_PutEvent(ITS_SCCP_ANSI_SRC, &event);
}
