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
 *  ID: $Id: ansi-scmg.c,v 9.8.6.3 2010/07/09 04:47:09 ssingh Exp $
 *
 * LOG: $Log: ansi-scmg.c,v $
 * LOG: Revision 9.8.6.3  2010/07/09 04:47:09  ssingh
 * LOG: more fixes against SST not starting #3056 - Olivier
 * LOG:
 * LOG: Revision 9.8.6.2  2010/06/21 07:10:04  chandrashekharbs
 * LOG: Fix for SMLC hang issue, #2944 - omayor
 * LOG:
 * LOG: Revision 9.8.6.1  2010/04/16 22:31:05  ssingh
 * LOG: fix for issue SMLC-2638
 * LOG:
 * LOG: Revision 9.8  2008/07/18 05:26:58  ssingh
 * LOG: SDS ID:: ID :: D0240 Warning removal for Solaris Compilation
 * LOG:
 * LOG: Revision 9.7  2008/06/04 10:30:24  ssingh
 * LOG: ALU porting, B-0100LX-LUSG-00 (june 04,2008 base)
 * LOG:
 * LOG: Revision 9.6  2008/04/22 10:45:20  kramesh
 * LOG: Propagated TCS issue 1123.Dead lock occurs when processing
 * LOG: multiple PAUSE/RESUME at the same time.
 * LOG:
 * LOG: Revision 9.5  2008/04/15 05:03:17  kramesh
 * LOG: Merged Persistent Branch Changes to current.
 * LOG:
 * LOG: Revision 9.4.2.2  2007/05/18 06:47:41  pspl
 * LOG: (PSPL, abhijeet) moved the Alarm raising statement after the memcpy()
 * LOG: to have value for the PC
 * LOG:
 * LOG: Revision 9.4.2.1  2007/04/24 14:05:33  pspl
 * LOG: Made propogation of MTP3 indication to upper layer configurable
 * LOG: from xml (Rahul).
 * LOG:
 * LOG: Revision 9.4  2007/02/01 13:25:18  yranade
 * LOG: 2nd round of merge
 * LOG:
 * LOG: Revision 9.3  2007/01/11 12:43:35  yranade
 * LOG: Merge changes from 6.5.3 and Lucent branches
 * LOG:
 * LOG: Revision 9.2.30.1  2006/09/29 14:58:42  mshanmugam
 * LOG: Propagation of redundancy modifications from Kineto Branch (kramesh).
 * LOG:
 * LOG: Revision 9.2.8.10  2007/11/22 14:05:13  mshanmugam
 * LOG: added code for BuildCPCData and BuildDupData
 * LOG:
 * LOG: Revision 9.2.8.9  2007/10/05 11:28:27  mshanmugam
 * LOG: ported the fix for issue 6172
 * LOG:
 * LOG: Revision 9.2.8.8  2007/07/22 13:18:42  raghavendrabk
 * LOG: Propagated the fix given for Issue ID:6172
 * LOG:
 * LOG: Revision 9.2.8.7  2007/07/06 14:19:33  ssingh
 * LOG: Fix to stop sending SST when the Node is Standby
 * LOG:
 * LOG: Revision 9.2.8.6  2007/04/30 07:17:32  sbhaskaran
 * LOG: Fix for stopping the Backup Node to send SCMG messages
 * LOG:
 * LOG: Revision 9.2.8.5  2007/04/27 13:57:36  sbhaskaran
 * LOG: Compilation error resolved
 * LOG:
 * LOG: Revision 9.2.8.4  2007/04/27 05:45:52  raghavendrabk
 * LOG: Alarm Format Changes for Family handling in OAM
 * LOG:
 * LOG: Revision 9.2.8.3  2007/02/02 14:05:39  raghavendrabk
 * LOG: Parallel Stack changes for Alarms and Statistics
 * LOG:
 * LOG: Revision 9.2  2005/04/06 11:26:23  mmanikandan
 * LOG: Bug Propagation and Validation bug Fix.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:32  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.6  2005/03/21 13:53:34  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.4.2.2.2.4.6.1  2004/12/29 13:37:09  csireesh
 * LOG: SCCP bug propogation and OAM Changes
 * LOG:
 * LOG: Revision 7.4.2.2.2.4  2004/09/13 07:19:17  csireesh
 * LOG: Bug Fix:1107,1147,1148
 * LOG:
 * LOG: Revision 7.4.2.2.2.3  2004/09/02 11:55:54  csireesh
 * LOG: Validation Bug Fixes for Alarms, Pegs and MML commands.
 * LOG:
 * LOG: Revision 7.4.2.2.2.2  2004/07/06 10:55:15  csireesh
 * LOG: MML Commands Updated
 * LOG:
 * LOG: Revision 7.4.2.2.2.1  2004/06/22 11:47:52  csireesh
 * LOG: ALARMS and PEGS Propogation from TCS branch.
 * LOG:
 * LOG: Revision 7.4.2.2  2003/12/15 19:57:25  hcho
 * LOG: Subsystem is allowed still need to notify the management.
 * LOG:
 * LOG: Revision 7.4.2.1  2003/02/25 10:29:24  asingh
 * LOG: Corrected ctxt2 calculation in the function BCSTSendSSP
 * LOG:
 * LOG: Revision 7.4  2003/02/03 12:08:33  aganguly
 * LOG: Changes for SCCP alarms: clean up of unwanted alarms left for Release 6.4
 * LOG:
 * LOG: Revision 7.3  2002/11/15 18:12:09  ngoel
 * LOG: mask sio
 * LOG:
 * LOG: Revision 7.2  2002/11/14 16:43:45  ngoel
 * LOG: merge scmg corrections from pr6.1
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.15  2002/07/29 18:04:40  ngoel
 * LOG: correct peg type
 * LOG:
 * LOG: Adding support for China variant
 * LOG:
 * LOG: Revision 6.13  2002/06/05 15:48:48  mmiers
 * LOG: More SCMG work
 * LOG:
 * LOG: Revision 6.12  2002/05/06 21:00:37  mmiers
 * LOG: Bug fixing.
 * LOG:
 * LOG: Revision 6.11  2002/05/06 20:11:17  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 6.10  2002/04/17 23:02:25  hdivoux
 * LOG: FT/HA integration.
 * LOG:
 * LOG: Revision 6.9  2002/04/03 23:24:51  mmiers
 * LOG: SCMG timers in DSM
 * LOG:
 * LOG: Revision 6.8  2002/04/01 22:51:17  mmiers
 * LOG: Remove hardcoded NI and PRI
 * LOG:
 * LOG: Revision 6.7  2002/03/27 22:05:46  mmiers
 * LOG: Put SST/SSP/SSA into DSM properly.  TODO: put the serials
 * LOG: in DSM as well.
 * LOG:
 * LOG: Revision 6.6  2002/03/27 17:48:12  mmiers
 * LOG: Convert to using shared timers.
 * LOG:
 * LOG: Revision 6.5  2002/03/14 22:52:31  mmiers
 * LOG: Convert TCAP and SCCP to OAM
 * LOG:
 * LOG: Revision 6.4  2002/03/11 20:59:46  mmiers
 * LOG: It builds.  Now for the hard part.
 * LOG:
 * LOG: Revision 6.3  2002/03/08 21:31:27  mmiers
 * LOG: Formatting complete.  TODO: CPC lists.
 * LOG:
 * LOG: Revision 6.2  2002/03/07 22:21:30  mmiers
 * LOG: Merge ITU SCCP.  Doesn't build (have to work on CPC impl).
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:38  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.13  2002/01/02 21:02:44  mmiers
 * LOG: Back out the routing label change.  It breaks hybrid stack builds.
 * LOG:
 * LOG: Revision 5.12  2002/01/02 19:56:08  mmiers
 * LOG: Convert to using long names (everything but TCAP).
 * LOG:
 * LOG: Revision 5.11  2001/11/12 23:31:04  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 5.10  2001/11/12 23:29:14  mmiers
 * LOG: Fixme removal
 * LOG:
 * LOG: Revision 5.9  2001/09/26 21:28:43  mmiers
 * LOG: SRM is essentially complete, but a few more tricks are needed.
 * LOG: Other stuff is more fixme removal.
 * LOG:
 * LOG: Revision 5.8  2001/09/25 21:35:20  mmiers
 * LOG: Fix up SCCP routing and SCMG.
 * LOG:
 * LOG: Revision 5.7  2001/09/24 22:50:23  mmiers
 * LOG: Remove bogus SSN from MTP3 P/R/S messages.  This adds fixmes to
 * LOG: SCMG.
 * LOG:
 * LOG: Revision 5.6  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.5  2001/09/06 17:25:02  mmiers
 * LOG: Straighten out routing a bit.
 * LOG:
 * LOG: Revision 5.4  2001/08/21 20:21:31  mmiers
 * LOG: Start adding in the missing code.
 * LOG:
 * LOG: Revision 5.3  2001/08/17 22:16:32  mmiers
 * LOG: Note some fixmes
 * LOG:
 * LOG: Revision 5.2  2001/08/17 20:21:15  mmiers
 * LOG: New routing subsystem for MTP3.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:27  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:03  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.10  2001/04/18 23:17:07  omayor
 * LOG: Avoid sending MTP3 management messages to SCCP callbacks.
 * LOG:
 * LOG: Revision 3.9  2000/12/29 17:31:50  mmiers
 * LOG: Go ahead and broadcast UIS/UOS even if allowed/prohibited
 * LOG:
 * LOG: Revision 3.8  2000/12/22 00:36:41  mmiers
 * LOG: Traces
 * LOG:
 * LOG: Revision 3.7  2000/12/21 22:11:22  mmiers
 * LOG: Trace more
 * LOG:
 * LOG: Revision 3.6  2000/11/14 00:18:19  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.6  2000/10/20 22:23:13  omayor
 * LOG: Add SOR, SOG SCMG procedure for duplicate SSN. Also LUDT, LUDTS
 * LOG: procedures for ITU SCCP
 * LOG:
 * LOG: Revision 3.5  2000/10/05 23:04:32  mmiers
 * LOG: Go back to the old way for now.
 * LOG:
 * LOG: Revision 3.4  2000/09/25 18:56:13  mmiers
 * LOG: More ROUTE fixups.
 * LOG:
 * LOG: Revision 3.3  2000/09/25 18:31:47  mmiers
 * LOG: Set up for the new routing table.
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:07:22  mmiers
 * LOG: Zero copy is in.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:27  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.3  2000/01/26 03:05:45  mmiers
 * LOG:
 * LOG:
 * LOG: Commit some more changes to get us on an OO footing.
 * LOG:
 * LOG: Revision 2.2  2000/01/21 22:49:55  mmiers
 * LOG:
 * LOG: Use separate up/allowed functions.
 * LOG:
 * LOG: Revision 2.1  1999/12/06 21:30:09  mmiers
 * LOG:
 * LOG:
 * LOG: Debug with HP's GDI.
 * LOG:
 * LOG: Revision 1.4.2.1  1999/12/06 21:27:27  mmiers
 * LOG:
 * LOG:
 * LOG: Debug with HP's GDI.
 * LOG:
 * LOG: Revision 1.4  1999/08/26 23:44:54  labuser
 * LOG:
 * LOG:
 * LOG: Alter GTT to include original PC (if any) and SSN (if any).
 * LOG:
 * LOG: Revision 1.3  1999/03/24 22:46:34  mmiers
 * LOG:
 * LOG:
 * LOG: Clean up the SST queue when terminating.
 * LOG:
 * LOG: Revision 1.2  1999/03/17 21:37:48  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol framework complete.  Now for implementation.
 * LOG:
 * LOG: Revision 1.1  1999/03/17 18:39:43  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol commit.  Still have to finish TCAP.
 * LOG:
 * LOG: Revision 1.20  1998/11/19 01:31:51  mmiers
 * LOG: Build with warning at max.  5 bugs found.
 * LOG:
 * LOG: Revision 1.19  1998/11/17 22:37:39  mmiers
 * LOG: Propagate SCMG (SSP/SSA)
 * LOG:
 * LOG: Revision 1.18  1998/11/17 03:08:55  mmiers
 * LOG: Finish off SCMG.
 * LOG:
 * LOG: Revision 1.17  1998/11/13 15:11:02  mmiers
 * LOG: Clean up some overnight changes.
 * LOG:
 * LOG: Revision 1.16  1998/11/13 02:49:43  mmiers
 * LOG: Do SST.
 * LOG:
 * LOG: Revision 1.15  1998/11/11 15:43:43  mmiers
 * LOG: clean up some build errors.
 * LOG:
 * LOG: Revision 1.14  1998/11/11 03:47:35  mmiers
 * LOG: Clean up some SCCP stuff.
 * LOG:
 * LOG: Revision 1.13  1998/11/11 03:23:53  mmiers
 * LOG: Finish up SCMG.  Still need SST, but that is lower priority.
 * LOG:
 * LOG: Revision 1.12  1998/11/11 00:45:31  mmiers
 * LOG: Work on CPC/CSSN information.
 * LOG:
 * LOG: Revision 1.11  1998/11/10 16:10:12  mmiers
 * LOG: More work on SCMG.
 * LOG:
 * LOG: Revision 1.10  1998/11/06 23:04:29  mmiers
 * LOG: Work on broadcast.
 * LOG:
 * LOG: Revision 1.9  1998/11/05 21:30:32  mmiers
 * LOG: Working on pause/resume.
 * LOG:
 * LOG: Revision 1.8  1998/10/29 03:11:19  mmiers
 * LOG: Handle UIS/UOS, UDTS/XUDTS correctly.  Need to work on SSA/SSP.
 * LOG:
 * LOG: Revision 1.7  1998/10/28 23:51:48  mmiers
 * LOG: Halfway through SCMG.
 * LOG:
 * LOG: Revision 1.6  1998/10/20 01:40:23  mmiers
 * LOG: include all SCCP timers.  More work on inactivity test.  Thinking
 * LOG: about SCMG.
 * LOG:
 * LOG: Revision 1.5  1998/09/27 00:17:55  mmiers
 * LOG: More work on SCCP
 * LOG:
 * LOG: Revision 1.4  1998/09/24 23:27:31  mmiers
 * LOG: Continue work on improved SCCP.
 * LOG:
 * LOG: Revision 1.3  1998/09/24 19:24:38  mmiers
 * LOG: More work on SCCP.
 * LOG:
 * LOG: Revision 1.2  1998/09/24 17:31:51  mmiers
 * LOG: More working with SCCP.
 * LOG:
 * LOG: Revision 1.1  1998/09/24 16:33:12  mmiers
 * LOG: Rearrange vendor lib a little for smarter SCCP.
 * LOG:
 * LOG:
 *
 ****************************************************************************/

#include <string.h>
#include <assert.h>
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
#include <its_timers.h>
#include <its_route_rwlock.h>
#include <its_redundancy.h>

#ident "$Id: ansi-scmg.c,v 9.8.6.3 2010/07/09 04:47:09 ssingh Exp $"

#include <ansi/sccp.h>

#include "sccp_intern.h"

/* Externs */
extern ITS_Class ITS_RedundancyClass;

/*
 * SST structure
 */
typedef struct
{
    ROUTE_Info     routeInfo;
    MTP3_HEADER    sourceHdr;
}
SST_Info;

/*
 * SST key
 */
typedef struct
{
    ITS_UINT    dpc;
    ITS_OCTET   sio;
    ITS_OCTET   ssn;
}
SST_Key;

extern TQUEUETRAN_Manager* __SCCP_ANSI_RcvQueue;

extern void BuildCPCData_ANSI();
extern void BuildDupData_ANSI();

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle receipt of message for prohibited subsytem
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
SendSCMG_ANSI(MTP3_HEADER* mtp3, SCCP_SCMG_ANSI* scmg, ITS_UINT toSSN)
{
    ITS_SCCP_IE lies[32];
    ITS_OCTET addrInd, sio;

    if (ITS_RedundancyClass != NULL)
    {
        if (REDUNDANCY_GET_NODE_STATE(ITS_RedundancyClass) == ITS_STATE_BACKUP)
        {
            SCCP_DEBUG(("SendSCMG_ANSI: Backup node should not send SCMG msgs\n"));
            return (ITS_SUCCESS);
        }
    }

    SCCP_DEBUG(("SendSCMG_ANSI: type %02x ssn %02x pc %08x\n",
                scmg->type, scmg->ssn, MTP3_PC_GET_VALUE(scmg->pointCode)));

    /* protocol class */
    lies[0].param_id = SCCP_PRM_PROTOCOL_CLASS;
    lies[0].param_length = sizeof(SCCP_PROT_CLASS);
    lies[0].param_data.protocolClass.pclass = SCCP_PCLASS_0;

    /* build common addrInd. NOTE: Apparently, we do NOT include PC */
    addrInd = SCCP_CPA_HAS_SSN|SCCP_CPA_ROUTE_SSN;
    if ((mtp3->sio & MTP3_NIC_MASK) == MTP3_NIC_NATIONAL)
    {
        addrInd |= SCCP_CPA_ROUTE_NAT;
    }
    else
    {
        addrInd |= SCCP_CPA_ROUTE_INT;
    }

    /* calledParty */
    lies[1].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
    lies[1].param_length = sizeof(SCCP_ADDR);
    SCCP_EncodeAddr(&lies[1].param_data.calledPartyAddr,
                    addrInd, 0, SCCP_SSN_SCCPMGMT, NULL, 0);

    /* callingParty */
    lies[2].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
    lies[2].param_length = sizeof(SCCP_ADDR);
    SCCP_EncodeAddr(&lies[2].param_data.callingPartyAddr,
                    addrInd, 0, (ITS_OCTET)toSSN, NULL, 0);

    /* copy in SCMG */
    lies[3].param_id = SCCP_PRM_DATA;
    lies[3].param_length = sizeof(SCCP_SCMG_ANSI);
    memcpy(lies[3].param_data.userData.data,
           scmg,
           sizeof(SCCP_SCMG_ANSI));

    sio = MTP3_HDR_GET_SIO(*mtp3);
    sio &= ~MTP3_MPC_MASK;

    /* set the priority */
    switch (scmg->type)
    {
    case SCCP_SCMG_SS_ALLOWED:
    case SCCP_SCMG_SS_PROHIBIT:
        sio |= MTP3_MPC_PRI_3;
        break;

    case SCCP_SCMG_SS_OOS_REQ:
    case SCCP_SCMG_SS_OOS_GRANT:
        sio |= MTP3_MPC_PRI_1;
        break;

    case SCCP_SCMG_SS_STATUS_TEST:
    case SCCP_SCMG_SS_BACKUP_ROUTE:
    case SCCP_SCMG_SS_NORMAL_ROUTE:
    case SCCP_SCMG_SS_ROUTE_STATUS:
        break;

    default:
        break;
    }

    MTP3_HDR_SET_SIO(*mtp3, sio);

    return SCLCHandleSCMGMsg_ANSI(mtp3, SCCP_MSG_UDT, lies, 4);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle receipt of message for prohibited subsytem
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
SSTCStartSST_ANSI(MTP3_HEADER* mtp3, ITS_UINT pc, ITS_OCTET ssn)
{
    SST_Info* tmp;
    int error;
    SST_Key key;
    ITS_OCTET ni;
    ITS_INT ctxt;
    ROUTE_Info* linfo = NULL;
    ITS_SERIAL *serial;
    ITS_UINT skey;
    ITS_UINT opc;

    SCCP_DEBUG(("SSTCStartSST:\n"));

     memset(&key, 0, sizeof(key));

    /* see if we even do this */
    if (!BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_SCMG))
    {
        SCCP_DEBUG(("SSTCStartSST: for (%08x:%02x) not started\n",
                    pc, ssn));

        return (ITS_ENOTCONFIG);
    }

    /*
     * lock the table
     */
    if (DSM_LockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCMG) != ITS_SUCCESS)
    {
        SCCP_ERROR(("Failed to lock SCMG table\n"));
        
        return (ITS_EBADMUTEX);
    }

    key.dpc = pc;
    key.ssn = ssn;
    key.sio = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

    /* already running? */
    if ((tmp = DSM_FindNoLock(DSM_SccpFtGroupId,
                              DSM_TABLE_ANSI_SCMG,
                              (ITS_OCTET *)&key, sizeof(key),
                              &error)) == NULL)
    {
        /* get the other locks we need */
        if (DSM_LockTable(
                DSM_SccpFtGroupId, 
                DSM_TABLE_ANSI_SCCP_CPC) != ITS_SUCCESS)
        {
            SCCP_ERROR(("Unable to acquire CPC lock\n"));

            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCMG);

            return (ITS_EBADMUTEX);
        }

        /* see if we have a local subsystem that cares about this remote */
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;
        ctxt = pc | (ni << 24);
        if ((linfo = DSM_FindNoLock(DSM_SccpFtGroupId,
                                    DSM_TABLE_ANSI_SCCP_CPC,
                                    (ITS_OCTET *)&ctxt, sizeof(ITS_UINT),
                                    &error)) == NULL)
        {
            /* Can't find local SSN */
            SCCP_DEBUG(("StartSST: No locally concerned SSNs for %08x %2d\n",
                        pc, ssn));

            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CPC);
            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCMG);

            return (ITS_ENOTFOUND);
        }

        /* we're done looking at this table */
        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CPC);

        /* if we get here, *somebody* local cares.  Add the SST info */
        if ((tmp = (SST_Info *)DSM_AllocNoLock(DSM_SccpFtGroupId,
                                               DSM_TABLE_ANSI_SCMG,
                                               (ITS_OCTET *)&key, sizeof(key),
                                               sizeof(SST_Info), &error)) == NULL)
        {
            SCCP_ERROR(("SSTCStartSST: Out of DSM\n"));

            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCMG);

            return (ITS_ENOMEM);
        }

        /* add info */
        tmp->routeInfo.basic.type = REMOTE_ROUTE;
        tmp->routeInfo.basic.dpc = pc;
        tmp->routeInfo.basic.criteria.ssn = ssn;
        tmp->routeInfo.basic.criteria.sio = ni  | MTP3_SIO_SCCP;
        tmp->sourceHdr = *mtp3;
        opc = MTP3_RL_GET_DPC_VALUE(tmp->sourceHdr.label);
        MTP3_RL_SET_DPC_VALUE(tmp->sourceHdr.label, pc);
        MTP3_RL_SET_OPC_VALUE(tmp->sourceHdr.label, opc);
        MTP3_HDR_SET_SIO(tmp->sourceHdr, ni | MTP3_SIO_SCCP);

        DSM_CommitNoLock(DSM_SccpFtGroupId,
                         DSM_TABLE_ANSI_SCMG,
                         (ITS_OCTET *)&key, sizeof(key),
                         tmp);
    }

    DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCMG);

    /* maybe start the SCMG timer */
    if (DSM_LockTable(
            DSM_SccpFtGroupId, 
            DSM_TABLE_MGMT_DATA) != ITS_SUCCESS)
    {
        SCCP_ERROR(("DSM Table error\n"));

        return (ITS_EBADMUTEX);
    }

    skey = DSM_MGMT_REC_ANSI_SCCP_SST_SERIAL;
    if ((serial = DSM_FindNoLock(DSM_SccpFtGroupId,
                                 DSM_TABLE_MGMT_DATA,
                                 (ITS_OCTET *)&skey,
                                 sizeof(ITS_UINT),
                                 &error)) == NULL)
    {
        SCCP_ERROR(("Can't find SST serial key!\n"));

        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA);

        return  (ITS_ENOTFOUND);
    }

    if (*serial != 0)
    {
        TIMERS_CancelTimer(*serial);
    }

    *serial =
          TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                  TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                       SCCP_T_statInfo),
                                                       NULL, 0);

    DSM_CommitNoLock(DSM_SccpFtGroupId,
                     DSM_TABLE_MGMT_DATA,
                     (ITS_OCTET *)&skey, sizeof(ITS_UINT),
                     serial);

    DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA);
    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle receipt of message for prohibited subsytem
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
SSTCStopSST_ANSI(MTP3_HEADER* mtp3, ITS_UINT pc, ITS_OCTET ssn)
{
    SST_Key key;
    ROUTE_Info* tmp;
    ITS_UINT size, skey;
    ITS_SERIAL *serial;
    int error;

    SCCP_DEBUG(("SSTCStopSST:\n"));

     memset(&key, 0, sizeof(key));

    /* see if we even do this */
    if (!BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_SCMG))
    {
        SCCP_DEBUG(("SSTCStopSST: for (%08x:%02x) not propagated\n",
                    pc, ssn));

        return;
    }

    /* lock the table */
    if (DSM_LockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCMG) != ITS_SUCCESS)
    {
        SCCP_ERROR(("Can't lock SCMG table\n"));

        return;
    }

    key.dpc = pc;
    key.ssn = ssn;
    key.sio = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

    /* is it running? */
    if ((tmp = DSM_FindNoLock(DSM_SccpFtGroupId,
                              DSM_TABLE_ANSI_SCMG,
                              (ITS_OCTET *)&key, sizeof(key),
                              &error)) == NULL)
    {
        /* yep.  Just unlock and return */
        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCMG);

        return;
    }

    /* if we get here it is.  Kill it */
    DSM_FreeNoLock(DSM_SccpFtGroupId,
                   DSM_TABLE_ANSI_SCMG,
                   (ITS_OCTET *)&key, sizeof(key),
                   tmp);

    /* see if the table is empty */
    size = 0;
    DSM_TableGetSize(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCMG, &size);

    /* serial needs to be in DSM */
    if (DSM_LockTable(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA) != ITS_SUCCESS)
    {
        SCCP_ERROR(("DSM Table error\n"));

        return;
    }

    skey = DSM_MGMT_REC_ANSI_SCCP_SST_SERIAL;
    if ((serial = DSM_FindNoLock(DSM_SccpFtGroupId,
                                 DSM_TABLE_MGMT_DATA,
                                 (ITS_OCTET *)&skey,
                                 sizeof(ITS_UINT),
                                 &error)) == NULL)
    {
        SCCP_ERROR(("Can't find SST serial key!\n"));

        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA);

        return;
    }

    if (size == 0 && *serial != 0)
    {
        TIMERS_CancelTimer(*serial);

        *serial = 0;

        DSM_CommitNoLock(DSM_SccpFtGroupId,
                         DSM_TABLE_MGMT_DATA,
                         (ITS_OCTET *)&skey, sizeof(ITS_UINT),
                         serial);
    }

    DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA);

    /* done. */
    DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCMG);
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
ITS_BOOLEAN
SCMGIsSSTPending_ANSI(ROUTE_Info *rinfo)
{
    ITS_INT error;
    SST_Key key;
    ROUTE_Info* tmp;

    if (!rinfo)
    {
        return (ITS_ENULLPTR);
    }

    memset(&key, 0, sizeof(key));

    if (DSM_LockTableLocal(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCMG) != ITS_SUCCESS)
    {
        SCCP_ERROR(("Can't lock SCMG table\n"));

        return (ITS_EBADMUTEX);
    }

    key.dpc = rinfo->basic.dpc;
    key.sio = rinfo->basic.criteria.sio & ROUTE_NI_MASK;
    key.ssn = rinfo->basic.criteria.ssn;

    /* is it running? */
    if ((tmp = DSM_FindNoLockLocal(DSM_SccpFtGroupId,
                              DSM_TABLE_ANSI_SCMG,
                              (ITS_OCTET *)&key, sizeof(key),
                              &error)) == NULL)
    {
        /* yep.  Just unlock and return */
        DSM_UnlockTableLocal(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCMG);

        return (ITS_FALSE);
    }

    DSM_UnlockTableLocal(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCMG);

    return (ITS_TRUE);
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
static void
LBCSSendSPAcc(MTP3_HEADER* mtp3, ITS_UINT pc)
{
    /* Bug Id : 7,11
     Description : To Send the MTP3 indication up to SCCP layer.

     if SCCP_B_propagate_SCMG flag in configuration file is yes then propagate
     the message else don't
    */
    if (BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_SCMG))
    {
        ITS_EVENT ev;
        MTP3_PAUSE_RESUME pr;

        SCCP_DEBUG(("LBCSSendSPAcc: for (%08x)\n", pc));

        MTP3_PC_SET_VALUE(pr.affected, pc);

        ev.src = ITS_MTP3_ANSI_SRC;
        MTP3_Encode(&ev, MTP3_MSG_RESUME, mtp3,
                        (ITS_OCTET *)&pr, sizeof(MTP3_PAUSE_RESUME));

        CALLBACK_CallCallbackList(SCCP_ManagementCallbacks,
                        NULL,
                        (ITS_POINTER)&ev);

        ITS_EVENT_TERM(&ev);
    }
    else
        SCCP_DEBUG(("LBCSSendSPAcc: for (%08x) not propagated\n", pc));
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
static void
LBCSSendSPInAcc(MTP3_HEADER* mtp3, ITS_UINT pc)
{
    /* Bug Id : 7,11
     Description : To Send the MTP3 indication up to SCCP layer.

     if SCCP_B_propagate_SCMG flag in configuration file is yes then propagate
     the message else don't
    */
    if (BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_SCMG))
    {
         ITS_EVENT ev;
         MTP3_PAUSE_RESUME pr;

         MTP3_PC_SET_VALUE(pr.affected, pc);

         ev.src = ITS_MTP3_ANSI_SRC;
         MTP3_Encode(&ev, MTP3_MSG_PAUSE, mtp3,
                     (ITS_OCTET *)&pr, sizeof(MTP3_PAUSE_RESUME));


         CALLBACK_CallCallbackList(SCCP_ManagementCallbacks,
                                   NULL,
                                  (ITS_POINTER)&ev);

         ITS_EVENT_TERM(&ev);
    }
    else
         SCCP_DEBUG(("LBCSSendSPInAcc: for (%08x) not propagated\n", pc));
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
static void
LBCSSendSPCong(MTP3_HEADER* mtp3, ITS_UINT pc, ITS_OCTET congLevel)
{
    /* Bug Id : 7,11
     Description : To Send the MTP3 indication up to SCCP layer.

     if SCCP_B_propagate_SCMG flag in configuration file is yes then propagate
     the message else don't
    */
    if (BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_SCMG))
    {
        ITS_EVENT ev;
        MTP3_STATUS st;

        SCCP_DEBUG(("LBCSSendSPCong: for (%08x)\n", pc));

        MTP3_PC_SET_VALUE(st.affected, pc);
        st.cause = MTP3_STATUS_CONGESTED;
        st.congLevel = congLevel;

        ev.src = ITS_MTP3_ANSI_SRC;
        MTP3_Encode(&ev, MTP3_MSG_STATUS, mtp3,
                        (ITS_OCTET *)&st, sizeof(MTP3_STATUS));


        CALLBACK_CallCallbackList(SCCP_ManagementCallbacks,
                        NULL,
                        (ITS_POINTER)&ev);

        ITS_EVENT_TERM(&ev);
    }
    else
        SCCP_DEBUG(("LBCSSendSPCong: for (%08x) not propagated\n", pc));
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
static void
LBCSSendSSA(ITS_OCTET ni, ITS_UINT pc, ITS_OCTET ssn)
{
    ITS_SCCP_IE lies[32];
    ITS_OCTET addrInd;
    MTP3_HEADER resp;
    SCCP_SCMG_ANSI scmg;
    ITS_EVENT ev;
    ITS_HDR hdr;

    SCCP_DEBUG(("LBCSSendSSA: for (%08x:%02x)\n",
                pc, ssn));

    if (!BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_SCMG))
    {
        SCCP_DEBUG(("LBCSSendSSA: for (%08x:%02x) not propagated\n",
                    pc, ssn));


        return;
    }

    /* build the routing label */
    resp.sio = ni|MTP3_MPC_PRI_3|MTP3_SIO_SCCP;
    MTP3_RL_SET_DPC_VALUE(resp.label, pc);
    MTP3_RL_SET_OPC_VALUE(resp.label, pc);
    MTP3_RL_SET_SLS(resp.label, 0);

    /* protocol class */
    lies[0].param_id = SCCP_PRM_PROTOCOL_CLASS;
    lies[0].param_length = sizeof(SCCP_PROT_CLASS);
    lies[0].param_data.protocolClass.pclass = SCCP_PCLASS_0;

    /* build common addrInd. NOTE: Apparently, we do NOT include PC */
    addrInd = SCCP_CPA_HAS_SSN|SCCP_CPA_ROUTE_SSN|SCCP_CPA_ROUTE_NAT;

    /* calledParty */
    lies[1].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
    lies[1].param_length = sizeof(SCCP_ADDR);
    SCCP_EncodeAddr(&lies[1].param_data.calledPartyAddr,
                    addrInd, 0, ssn, NULL, 0);

    /* callingParty */
    lies[2].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
    lies[2].param_length = sizeof(SCCP_ADDR);
    SCCP_EncodeAddr(&lies[2].param_data.callingPartyAddr,
                    addrInd, 0, SCCP_SSN_SCCPMGMT, NULL, 0);

    /* copy in SCMG */
    scmg.type = SCCP_SCMG_SS_ALLOWED;
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
    hdr.context.ssn = SCCP_SSN_SCCPMGMT;

    ev.src = ITS_SCCP_ANSI_SRC;
    SCCP_Encode(lies, 5, SCCP_MSG_UDT, &ev, &hdr,
                    &SCCP_UDT_Desc);

    CALLBACK_CallCallbackList(SCCP_ManagementCallbacks,
                              NULL, (ITS_POINTER)&ev);


    ITS_EVENT_TERM(&ev);
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
static void
LBCSSendSSP(ITS_OCTET ni, ITS_UINT pc, ITS_OCTET ssn)
{
    ITS_SCCP_IE lies[32];
    ITS_OCTET addrInd;
    MTP3_HEADER resp;
    SCCP_SCMG_ANSI scmg;
    ITS_EVENT ev;
    ITS_HDR hdr;

    SCCP_DEBUG(("LBCSSendSSP: for (%08x:%02x)\n",
                pc, ssn));

    if (!BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_SCMG))
    {
        SCCP_DEBUG(("LBCSSendSSP: for (%08x:%02x) not propagated\n",
                    pc, ssn));

        return;
    }

    /* build the routing label */
    resp.sio = ni|MTP3_MPC_PRI_3|MTP3_SIO_SCCP;
    MTP3_RL_SET_DPC_VALUE(resp.label, pc);
    MTP3_RL_SET_OPC_VALUE(resp.label, pc);
    MTP3_RL_SET_SLS(resp.label, 0);

    /* protocol class */
    lies[0].param_id = SCCP_PRM_PROTOCOL_CLASS;
    lies[0].param_length = sizeof(SCCP_PROT_CLASS);
    lies[0].param_data.protocolClass.pclass = SCCP_PCLASS_0;

    /* build common addrInd. NOTE: Apparently, we do NOT include PC */
    addrInd = SCCP_CPA_HAS_SSN|SCCP_CPA_ROUTE_SSN|SCCP_CPA_ROUTE_NAT;

    /* calledParty */
    lies[1].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
    lies[1].param_length = sizeof(SCCP_ADDR);
    SCCP_EncodeAddr(&lies[1].param_data.calledPartyAddr,
                        addrInd, 0, ssn, NULL, 0);
    
    /* callingParty */
    lies[2].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
    lies[2].param_length = sizeof(SCCP_ADDR);
    SCCP_EncodeAddr(&lies[2].param_data.callingPartyAddr,
                    addrInd, 0, SCCP_SSN_SCCPMGMT, NULL, 0);

    /* copy in SCMG */
    scmg.type = SCCP_SCMG_SS_PROHIBIT;
    scmg.ssn = ssn;
    MTP3_PC_SET_VALUE(scmg.pointCode, pc);
    scmg.multiplicity = SCCP_SCMG_SMI_SOLO;

    lies[3].param_id = SCCP_PRM_DATA;
    lies[3].param_length = sizeof(SCCP_SCMG_ANSI);
    memcpy(lies[3].param_data.userData.data,
           &scmg,
           sizeof(SCCP_SCMG_ANSI));

    hdr.type = ITS_SCCP;
    hdr.context.ssn = SCCP_SSN_SCCPMGMT;

    ev.src = ITS_SCCP_ANSI_SRC;
    SCCP_Encode(lies, 5, SCCP_MSG_UDT, &ev, &hdr,&SCCP_UDT_Desc); 

    CALLBACK_CallCallbackList(SCCP_ManagementCallbacks,
                              NULL,
                              (ITS_POINTER)&ev);

    ITS_EVENT_TERM(&ev);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function sends a SOR to the system duplicate
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
static void
SCMG_SendSORToDuplicate(SCCP_SCMG_ANSI *uos,
                        ITS_OCTET ni, ITS_UINT pc, ITS_OCTET ssn)
{
    SCCP_SCMG_ANSI scmg;
    MTP3_HEADER hdr;
    ITS_SERIAL *serial;
    ITS_UINT skey;
    int error;

    /* build MTP3 Header */
    hdr.sio = ni|MTP3_MPC_PRI_1|MTP3_SIO_SCCP;
    MTP3_RL_SET_DPC_VALUE(hdr.label, pc);
    MTP3_RL_SET_OPC_VALUE(hdr.label, 
                          MTP3_PC_GET_VALUE_ANSI(uos->pointCode));
    MTP3_RL_SET_SLS(hdr.label, 0);

    /* Building the SCMG Information */
    scmg.type = SCCP_SCMG_SS_OOS_REQ;
    /* affected ssn, we get from the UOS message */
    scmg.ssn = uos->ssn;
    /* affected point code, get from the UOS message */
    scmg.pointCode = uos->pointCode;
    /* multiplicity parameter... if we are here we have a duplicate */
    scmg.multiplicity = SCCP_SCMG_SMI_DUP;

    SendSCMG_ANSI(&hdr, &scmg, ssn);

    /* need to start the SOR timer: serial needs to be in DSM */
    if (DSM_LockTable(
            DSM_SccpFtGroupId, 
            DSM_TABLE_MGMT_DATA) != ITS_SUCCESS)
    {
        SCCP_ERROR(("DSM Table error\n"));

        return;
    }

    skey = DSM_MGMT_REC_ANSI_SCCP_SOR_SERIAL;
    if ((serial = DSM_FindNoLock(DSM_SccpFtGroupId,
                                 DSM_TABLE_MGMT_DATA,
                                 (ITS_OCTET *)&skey,
                                 sizeof(ITS_UINT),
                                 &error)) == NULL)
    {
        SCCP_ERROR(("Can't find SOR serial key!\n"));

        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA);

        return;
    }

    *serial =
        TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_coordChg),
                                NULL, 0);

    DSM_CommitNoLock(DSM_SccpFtGroupId,
                     DSM_TABLE_MGMT_DATA,
                     (ITS_OCTET *)&skey, sizeof(ITS_UINT),
                     serial);

    DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      this function is used handle a SOG message from system
 *      duplicate.
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
static void
SCMG_SendSOGToDuplicate(MTP3_HEADER *mtp3, SCCP_SCMG_ANSI *sor)
{
    SCCP_SCMG_ANSI scmg;
    MTP3_HEADER resp;
    ITS_UINT tmp;

    /* build MTP3 Header */
    resp.sio = mtp3->sio;
    tmp = MTP3_RL_GET_DPC_VALUE(mtp3->label);
    MTP3_RL_SET_OPC_VALUE(resp.label, tmp);
    tmp = MTP3_RL_GET_OPC_VALUE(mtp3->label);
    MTP3_RL_SET_DPC_VALUE(resp.label, tmp);
    MTP3_RL_SET_SLS(resp.label, MTP3_RL_GET_SLS(mtp3->label));
    
    /* Building the SCMG Information */
    scmg.type = SCCP_SCMG_SS_OOS_GRANT;
    /* affected ssn, we get from the SOR message */
    scmg.ssn = sor->ssn;
    /* affected point code, get from the SOR message */
    scmg.pointCode = sor->pointCode;
    /* multiplicity parameter... if we are here we have a duplicate */
    scmg.multiplicity = SCCP_SCMG_SMI_DUP;

    SendSCMG_ANSI(&resp, &scmg, sor->ssn);

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
 ****************************************************************************/
static void
LBCSSendUIS(ITS_OCTET ni, ITS_UINT pc, ITS_OCTET ssn)
{
    ITS_SCCP_IE lies[32];
    ITS_OCTET addrInd;
    MTP3_HEADER resp;
    SCCP_SCMG_ANSI scmg;
    ITS_EVENT ev;
    ITS_HDR hdr;

    SCCP_DEBUG(("LBCSSendUIS: for (%08x:%02x)\n",
                pc, ssn));

    if (!BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_SCMG))
    {
        SCCP_DEBUG(("LBCSSendUIS: for (%08x:%02x) not propagated\n",
                    pc, ssn));

        return;
    }

    /* build the routing label */
    resp.sio = ni|MTP3_SIO_SCCP;
    MTP3_RL_SET_DPC_VALUE(resp.label, pc);
    MTP3_RL_SET_OPC_VALUE(resp.label, pc);
    MTP3_RL_SET_SLS(resp.label, 0);

    /* protocol class */
    lies[0].param_id = SCCP_PRM_PROTOCOL_CLASS;
    lies[0].param_length = sizeof(SCCP_PROT_CLASS);
    lies[0].param_data.protocolClass.pclass = SCCP_PCLASS_0;

    /* build common addrInd. NOTE: Apparently, we do NOT include PC */
    addrInd = SCCP_CPA_HAS_SSN|SCCP_CPA_ROUTE_SSN|SCCP_CPA_ROUTE_NAT;

    /* calledParty */
    lies[1].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
    lies[1].param_length = sizeof(SCCP_ADDR);
    SCCP_EncodeAddr(&lies[1].param_data.calledPartyAddr,
                    addrInd, 0, ssn, NULL, 0);

    /* callingParty */
    lies[2].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
    lies[2].param_length = sizeof(SCCP_ADDR);
    SCCP_EncodeAddr(&lies[2].param_data.callingPartyAddr,
                    addrInd, 0, SCCP_SSN_SCCPMGMT, NULL, 0);

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

    hdr.type = ITS_SCCP;
    hdr.context.ssn = SCCP_SSN_SCCPMGMT;

    ev.src = ITS_SCCP_ANSI_SRC;
    SCCP_Encode(lies, 5, SCCP_MSG_UDT, &ev, &hdr, &SCCP_UDT_Desc);

    CALLBACK_CallCallbackList(SCCP_ManagementCallbacks,
                              NULL,
                              (ITS_POINTER)&ev);

    ITS_EVENT_TERM(&ev);
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
static void
LBCSSendUOS(ITS_OCTET ni, ITS_UINT pc, ITS_OCTET ssn)
{
    ITS_SCCP_IE lies[32];
    ITS_OCTET addrInd;
    MTP3_HEADER resp;
    SCCP_SCMG_ANSI scmg;
    ITS_EVENT ev;
    ITS_HDR hdr;

    SCCP_DEBUG(("LBCSSendUOS: for (%08x:%02x)\n",
                pc, ssn));


    if (!BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_SCMG))
    {
        SCCP_DEBUG(("LBCSSendUOS: for (%08x:%02x) not propagated\n",
                    pc, ssn));

        return;
    }

    /* build the routing label */
    resp.sio = ni|MTP3_SIO_SCCP;
    MTP3_RL_SET_DPC_VALUE(resp.label, pc);
    MTP3_RL_SET_OPC_VALUE(resp.label, pc);
    MTP3_RL_SET_SLS(resp.label, 0);

    /* protocol class */
    lies[0].param_id = SCCP_PRM_PROTOCOL_CLASS;
    lies[0].param_length = sizeof(SCCP_PROT_CLASS);
    lies[0].param_data.protocolClass.pclass = SCCP_PCLASS_0;

    /* build common addrInd. NOTE: Apparently, we do NOT include PC */
    addrInd = SCCP_CPA_HAS_SSN|SCCP_CPA_ROUTE_SSN|SCCP_CPA_ROUTE_NAT;

    /* calledParty */
    lies[1].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
    lies[1].param_length = sizeof(SCCP_ADDR);
    SCCP_EncodeAddr(&lies[1].param_data.calledPartyAddr,
                    addrInd, 0, ssn, NULL, 0);

    /* callingParty */
    lies[2].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
    lies[2].param_length = sizeof(SCCP_ADDR);
    SCCP_EncodeAddr(&lies[2].param_data.callingPartyAddr,
                    addrInd, 0, SCCP_SSN_SCCPMGMT, NULL, 0);

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

    hdr.type = ITS_SCCP;
    hdr.context.ssn = SCCP_SSN_SCCPMGMT;

    ev.src = ITS_SCCP_ANSI_SRC;
    SCCP_Encode(lies, 5, SCCP_MSG_UDT, &ev, &hdr, &SCCP_UDT_Desc);

    CALLBACK_CallCallbackList(SCCP_ManagementCallbacks,
                              NULL,
                              (ITS_POINTER)&ev);    

    ITS_EVENT_TERM(&ev);
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static void
LBCSSendSSC(ITS_OCTET ni, ITS_UINT pc, ITS_OCTET ssn)
{
    ITS_SCCP_IE lies[32];
    ITS_OCTET addrInd;
    MTP3_HEADER resp;
    SCCP_SCMG scmg;
    ITS_EVENT ev;
    ITS_HDR hdr;

    SCCP_DEBUG(("LBCSSendSSC: for (%08x:%02x)\n",
                pc, ssn));
    if (!BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors,
                               SCCP_B_propagate_SCMG))
    {
        SCCP_DEBUG(("LBCSSendSSC: for (%08x:%02x) not propagated\n",
                    pc, ssn));
        return;
    }

    /* build the routing label */
    resp.sio = ni|MTP3_SIO_SCCP;
    MTP3_RL_SET_DPC_VALUE(resp.label, pc);
    MTP3_RL_SET_OPC_VALUE(resp.label, pc);
    MTP3_RL_SET_SLS(resp.label, 0);

    /* protocol class */
    lies[0].param_id = SCCP_PRM_PROTOCOL_CLASS;
    lies[0].param_length = sizeof(SCCP_PROT_CLASS);
    lies[0].param_data.protocolClass.pclass = SCCP_PCLASS_0;

    /* build common addrInd. NOTE: Apparently, we do NOT include PC */
    addrInd = SCCP_CPA_HAS_SSN|SCCP_CPA_ROUTE_SSN|SCCP_CPA_ROUTE_NAT;

    /* calledParty */
    lies[1].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
    lies[1].param_length = sizeof(SCCP_ADDR);
    SCCP_EncodeAddr(&lies[1].param_data.calledPartyAddr,
                    addrInd, 0, ssn, NULL, 0);

    /* callingParty */
    lies[2].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
    lies[2].param_length = sizeof(SCCP_ADDR);
    SCCP_EncodeAddr(&lies[2].param_data.callingPartyAddr,
                    addrInd, 0, SCCP_SSN_SCCPMGMT, NULL, 0);

    /* copy in SCMG */
    scmg.type = SCCP_SCMG_SS_CONG;
    scmg.ssn = ssn;
    MTP3_PC_SET_VALUE(scmg.pointCode, pc);
    scmg.multiplicity = SCCP_SCMG_SMI_SOLO;

    lies[3].param_id = SCCP_PRM_DATA;
    lies[3].param_length = sizeof(SCCP_SCMG);
    memcpy(lies[3].param_data.userData.data,
           &scmg,
           sizeof(SCCP_SCMG));

    hdr.type = ITS_SCCP;
    hdr.context.ssn = SCCP_SSN_SCCPMGMT;

    ev.src = ITS_SCCP_SRC;
    SCCP_Encode(lies, 5, SCCP_MSG_UDT, &ev, &hdr, &SCCP_UDT_Desc);

    /* TO DO: incr Local Broadcast Congested   */

    CALLBACK_CallCallbackList(SCCP_ManagementCallbacks,
                              NULL,
                              (ITS_POINTER)&ev);


    ITS_EVENT_TERM(&ev);
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
static void
BCSTSendSSA(MTP3_HEADER* mtp3, SCCP_SCMG_ANSI* oscmg, ITS_BOOLEAN fromCPC)
{
    ITS_UINT apc = MTP3_PC_GET_VALUE(oscmg->pointCode), opc;
    ITS_OCTET ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;
    ITS_INT ctxt = apc | (ni << 24);
    SCCP_SCMG_ANSI scmg;
    ROUTE_Info *rinfo, *linfo, *tinfo1, *tinfo2;
    MTP3_HEADER hdr;
    ITS_INT error;

    SCCP_DEBUG(("BCSTSendSSA: BCST for (%08x:%02x) : Local %d\n",
                apc, oscmg->ssn, !fromCPC));

    if (!BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_SCMG))
    {
        SCCP_DEBUG(("BCSTSendSSA: for (%08x:%02x) not propagated\n",
                    apc, oscmg->ssn));

        return;
    }

    /* is this an SSA from a) outside, and b) NOT from the CPC itself? */
    opc = MTP3_RL_GET_OPC_VALUE(mtp3->label);
    if (fromCPC && (opc != apc))
    {
        return;
    }

    /*
     * Lock the tables we need
     */
    if (DSM_LockTable(
            DSM_SccpFtGroupId, 
            DSM_TABLE_ANSI_SCCP_LPC) != ITS_SUCCESS)
    {
        SCCP_ERROR(("Can't lock table\n"));

        return;
    }
    if (DSM_LockTable(
            DSM_SccpFtGroupId, 
            DSM_TABLE_ANSI_SCCP_CPC) != ITS_SUCCESS)
    {
        SCCP_ERROR(("Can't lock table\n"));

        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);

        return;
    }

    /*
     * if from local SSN, send SSA to all concerned remotes
     */
    if (!fromCPC)
    {
        rinfo = (ROUTE_Info *)DSM_FindNoLock(DSM_SccpFtGroupId, 
                                             DSM_TABLE_ANSI_SCCP_LPC, 
                                             (ITS_OCTET *)&ctxt,
                                             sizeof(ctxt), &error);
        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
            case (ITS_EBADMUTEX):
                SCCP_CRITICAL(("BCSTSendSSA: Couldn't acquire mutex.\n"));

                break;

            case (ITS_EINUSE):
                SCCP_ERROR(("BCSTSendSSA: DSM Row Locked.\n"));

                break;

            case (ITS_ENOTFOUND):
                SCCP_ERROR(("BCSTSendSSA: Can't find local SSN\n"));

                break;

            default:
                SCCP_ERROR(("BCSTSendSSA: Can't find local SSN\n"));

                break;
            }

            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CPC);
            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);

            return;
        }

        /* build SCMG info */
        scmg.type = SCCP_SCMG_SS_ALLOWED;
        scmg.ssn = oscmg->ssn;
        MTP3_PC_SET_VALUE(scmg.pointCode, apc);
        scmg.multiplicity = SCCP_SCMG_SMI_SOLO;

        hdr = *mtp3;
        MTP3_RL_SET_OPC_VALUE(hdr.label, apc);

        /* send to all concerned */
        for (tinfo1 = rinfo; rinfo != NULL; rinfo = rinfo->next)
        {
            MTP3_RL_SET_DPC_VALUE(hdr.label, rinfo->basic.dpc);

            if (rinfo->basic.style == ROUTE_DPC_SIO_SSN ||
                rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN)
            {
                SendSCMG_ANSI(&hdr, &scmg, rinfo->basic.criteria.ssn);
            }
            else if (rinfo->basic.style == ROUTE_DPC_SIO_SSN_RANGE ||
                     rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN_RANGE)
            {
                SendSCMG_ANSI(&hdr, &scmg, rinfo->basic.criteria.range.begin);
            }
        }

        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CPC);
        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);
    }
    else
    {
        /*
         * for all local ssn's concerned about this remote
         */
        linfo = (ROUTE_Info *)DSM_FindNoLock(DSM_SccpFtGroupId,
                                             DSM_TABLE_ANSI_SCCP_CPC, 
                                             (ITS_OCTET *)&ctxt,
                                             sizeof(ctxt), &error);
        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("BCSTSendSSA: Couldn't acquire mutex.\n"));

                break;

            case (ITS_EINUSE):
                SCCP_ERROR(("BCSTSendSSA: DSM Row Locked.\n"));

                break;

            case (ITS_ENOTFOUND):
                SCCP_ERROR(("BCSTSendSSA: Can't find concerned SSN\n"));

                break;

            default:
                SCCP_ERROR(("BCSTSendSSA: Can't find concerned SSN\n"));

                break;
            }

            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CPC);
            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);

            return;
        }
  
        /* copy in SCMG */
        scmg.type = SCCP_SCMG_SS_ALLOWED;
        scmg.ssn = oscmg->ssn;
        MTP3_PC_SET_VALUE(scmg.pointCode, apc);
        scmg.multiplicity = SCCP_SCMG_SMI_SOLO;

        for (tinfo1 = linfo; linfo != NULL; linfo = linfo->next)
        {
            ITS_INT ctxt2 = linfo->basic.dpc | (ni << 24);
            ITS_OCTET localSSN = 0;

            if (tinfo1->basic.style == ROUTE_DPC_SIO_SSN ||
                tinfo1->basic.style == ROUTE_DPC_OPC_SIO_SSN)
            {
                localSSN = tinfo1->basic.criteria.ssn;
            }
            else if (tinfo1->basic.style == ROUTE_DPC_SIO_SSN_RANGE ||
                     tinfo1->basic.style == ROUTE_DPC_OPC_SIO_SSN_RANGE)
            {
                localSSN = (ITS_OCTET)tinfo1->basic.criteria.range.begin;
            }
            else
            {
                SCCP_ERROR(("Bad route style\n"));

                continue;
            }

            rinfo = (ROUTE_Info *)DSM_FindNoLock(DSM_SccpFtGroupId,
                                                 DSM_TABLE_ANSI_SCCP_LPC, 
                                                 (ITS_OCTET *)&ctxt2, 
                                                 sizeof(ctxt2), &error);
            if (error != ITS_SUCCESS)
            {
                switch(error)
                {
                case (ITS_EBADMUTEX):
                    SCCP_ERROR(("BCSTSendSSA: Couldn't acquire mutex.\n"));

                    break;

                case (ITS_EINUSE):
                    SCCP_ERROR(("BCSTSendSSA: DSM Row Locked.\n"));

                    break;

                case (ITS_ENOTFOUND):
                    SCCP_ERROR(("BCSTSendSSA: Can't find local SSN\n"));

                    break;

                default:
                    SCCP_ERROR(("BCSTSendSSA: Can't find local SSN\n"));

                    break;
                }

                continue;
            }

            hdr = *mtp3;
            MTP3_RL_SET_OPC_VALUE(hdr.label, linfo->basic.dpc);

            /* inform everybody we know is concerned about this SSN */
            for (tinfo2 = rinfo; rinfo != NULL; rinfo = rinfo->next)
            {
                /* except don't send to the one who informed us */
                if (rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN &&
                    rinfo->basic.dpc == apc &&
                    ((rinfo->basic.criteria.sio  & MTP3_NIC_MASK) == ni) &&
                    rinfo->basic.criteria.ssn == oscmg->ssn)
                {
                    continue;
                }
                else if (rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN_RANGE &&
                         rinfo->basic.dpc == apc &&
                         ((rinfo->basic.criteria.sio & MTP3_NIC_MASK) == ni) &&
                         oscmg->ssn >= rinfo->basic.criteria.range.begin &&
                         oscmg->ssn <= rinfo->basic.criteria.range.end)
                {
                    continue;
                }

                MTP3_RL_SET_DPC_VALUE(hdr.label, rinfo->basic.dpc);

                SendSCMG_ANSI(&hdr, &scmg, localSSN);
            }
        }

        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CPC);
        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);
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
 ****************************************************************************/
static void
BCSTSendSSC(MTP3_HEADER* mtp3, SCCP_SCMG* oscmg, ITS_BOOLEAN fromCPC)
{
    ITS_UINT apc = MTP3_PC_GET_VALUE(oscmg->pointCode), opc;
    ITS_OCTET ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;
    ITS_INT ctxt = apc | (ni << 24);
    SCCP_SCMG scmg;
    ROUTE_Info* rinfo, *linfo, *tinfo1, *tinfo2;
    MTP3_HEADER hdr;
    int error;

    SCCP_DEBUG(("BCSTSendSSC: BCST for (%08x:%02x) : Local %d\n",
                apc, oscmg->ssn, !fromCPC));

    if (!BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors,
                               SCCP_B_propagate_SCMG))
    {
        SCCP_DEBUG(("BCSTSendSSC: for (%08x:%02x) not propagated\n",
                    apc, oscmg->ssn));


        return;
    }

    /* is this an SSP from a) outside, and b) NOT from the CPC itself? */
    opc = MTP3_RL_GET_OPC_VALUE(mtp3->label);
    if (fromCPC && (opc != apc))
    {
        /* The protocol says don't respond */
        return;
    }
    /*
     * Lock the tables we need
     */
    if (DSM_LockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC) != ITS_SUCCESS)
    {
        SCCP_ERROR(("Can't lock table\n"));

        return;
    }
    if (DSM_LockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CPC) != ITS_SUCCESS)
    {
        SCCP_ERROR(("Can't lock table\n"));

        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);

        return;
    }

    /*
     * if from local SSN, send SSC to all concerned remotes

     */
    if (!fromCPC)
    {

        rinfo = (ROUTE_Info *)DSM_FindNoLock(DSM_SccpFtGroupId,
                                             DSM_TABLE_ANSI_SCCP_LPC,
                                             (ITS_OCTET *)&ctxt,
                                             sizeof(ctxt), &error);
        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("BCSTSendSSC: Couldn't acquire mutex.\n"));

                break;

            case (ITS_EINUSE):
                SCCP_ERROR(("BCSTSendSSC: DSM Row Locked.\n"));

                break;

            case (ITS_ENOTFOUND):
                SCCP_ERROR(("BCSTSendSSC: Can't find local SSN\n"));

                break;

           default:
                SCCP_ERROR(("BCSTSendSSC: Can't find local SSN\n"));
                break;
            }

            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CPC);
            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);

            return;
        }

        /* build SCMG info */
        scmg.type = SCCP_SCMG_SS_CONGESTED;

        scmg.ssn = oscmg->ssn;
        MTP3_PC_SET_VALUE(scmg.pointCode, apc);
        scmg.multiplicity = SCCP_SCMG_SMI_SOLO;

        hdr = *mtp3;
        MTP3_RL_SET_OPC_VALUE(hdr.label, apc);

        /* send to all concerned */
        for (tinfo1 = rinfo; rinfo != NULL; rinfo = rinfo->next)
        {
           MTP3_RL_SET_DPC_VALUE(hdr.label, rinfo->basic.dpc);

            if (rinfo->basic.style == ROUTE_DPC_SIO_SSN ||
                rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN)
            {
                SendSCMG_ANSI(&hdr, &scmg, rinfo->basic.criteria.ssn);
            }
            else if (rinfo->basic.style == ROUTE_DPC_SIO_SSN_RANGE ||
                     rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN_RANGE)
            {
                SendSCMG_ANSI(&hdr, &scmg, rinfo->basic.criteria.range.begin);
            }
        }

        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CPC);
        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);
    }
    else
    {
        /*
         * for all local ssn's concerned about this remote
         */
        linfo = (ROUTE_Info *)DSM_FindNoLock(DSM_SccpFtGroupId,
                                            DSM_TABLE_ANSI_SCCP_CPC,
                                             (ITS_OCTET *)&ctxt,
                                             sizeof(ctxt), &error);
        if (error != ITS_SUCCESS)
        {
            switch(error)
            {

            case (ITS_EBADMUTEX):
                SCCP_ERROR(("BCSTSendSSC: Couldn't acquire mutex.\n"));

                break;

            case (ITS_EINUSE):
                SCCP_ERROR(("BCSTSendSSC: DSM Row Locked.\n"));

                break;

            case (ITS_ENOTFOUND):
                SCCP_ERROR(("BCSTSendSSC: Can't find concerned SSN\n"));

                break;

            default:

                SCCP_ERROR(("BCSTSendSSC: Can't find concerned SSN\n"));

                break;
            }
            return;
        }

        /* copy in SCMG */
        scmg.type = SCCP_SCMG_SS_CONGESTED;
        scmg.ssn = oscmg->ssn;
        MTP3_PC_SET_VALUE(scmg.pointCode, apc);
        scmg.multiplicity = SCCP_SCMG_SMI_SOLO;

        for (tinfo1 = linfo; linfo != NULL; linfo = linfo->next)
        {
            ITS_INT ctxt2 = linfo->basic.dpc | (ni << 24);
            ITS_OCTET localSSN = 0;

            if (tinfo1->basic.style == ROUTE_DPC_SIO_SSN ||
                tinfo1->basic.style == ROUTE_DPC_OPC_SIO_SSN)
            {
                localSSN = tinfo1->basic.criteria.ssn;
            }
            else if (tinfo1->basic.style == ROUTE_DPC_SIO_SSN_RANGE ||
                     tinfo1->basic.style == ROUTE_DPC_OPC_SIO_SSN_RANGE)
            {
                localSSN = (ITS_OCTET)tinfo1->basic.criteria.range.begin;
            }
            else
            {
                SCCP_ERROR(("Bad route style\n"));

                continue;
            }

            rinfo = (ROUTE_Info *)DSM_FindNoLock(DSM_SccpFtGroupId,
                                                 DSM_TABLE_ANSI_SCCP_LPC,
                                                 (ITS_OCTET *)&ctxt2,
                                                 sizeof(ctxt2), &error);
            if (error != ITS_SUCCESS)
            {
                switch(error)
                {
                case (ITS_EBADMUTEX):
                    SCCP_ERROR(("BCSTSendSSC: Couldn't acquire mutex.\n"));

                    break;

                case (ITS_EINUSE):
                    SCCP_ERROR(("BCSTSendSSC: DSM Row Locked.\n"));

                    break;

                case (ITS_ENOTFOUND):
                    SCCP_ERROR(("BCSTSendSSC: Can't find local SSN\n"));

                    break;

                default:
                    SCCP_ERROR(("BCSTSendSSC: Can't find local SSN\n"));
                    break;
                }

                continue;
            }

            hdr = *mtp3;
            MTP3_RL_SET_OPC_VALUE(hdr.label, linfo->basic.dpc);

           /* inform everybody we know is concerned about this SSN */
            for (tinfo2 = rinfo; rinfo != NULL; rinfo = rinfo->next)
            {
                /* except don't send to the one who informed us */
                if (rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN &&
                    rinfo->basic.dpc == apc &&
                    ((rinfo->basic.criteria.sio  & MTP3_NIC_MASK) == ni) &&
                    rinfo->basic.criteria.ssn == oscmg->ssn)
                {
                    continue;
                }
                else if (rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN_RANGE &&
                         rinfo->basic.dpc == apc &&
                         ((rinfo->basic.criteria.sio & MTP3_NIC_MASK) == ni) &&
                         oscmg->ssn >= rinfo->basic.criteria.range.begin &&
                         oscmg->ssn <= rinfo->basic.criteria.range.end)
                {
                    continue;
                }

                MTP3_RL_SET_DPC_VALUE(hdr.label, rinfo->basic.dpc);

                SendSCMG_ANSI(&hdr, &scmg, localSSN);
            }
        }

        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CPC);
        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);
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
 ****************************************************************************/
static void
BCSTSendSSP(MTP3_HEADER* mtp3, SCCP_SCMG_ANSI* oscmg, ITS_BOOLEAN fromCPC)
{
    ITS_UINT apc = MTP3_PC_GET_VALUE(oscmg->pointCode), opc;
    ITS_OCTET ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;
    ITS_INT ctxt = apc | (ni << 24);
    SCCP_SCMG_ANSI scmg;
    ROUTE_Info* rinfo, *linfo, *tinfo1, *tinfo2;
    MTP3_HEADER hdr;
    ITS_INT error;

    SCCP_DEBUG(("BCSTSendSSP: BCST for (%08x:%02x) : Local %d\n",
                apc, oscmg->ssn, !fromCPC));

    if (!BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_SCMG))
    {
        SCCP_DEBUG(("BCSTSendSSP: for (%08x:%02x) not propagated\n",
                    apc, oscmg->ssn));

        return;
    }

    /* is this an SSP from a) outside, and b) NOT from the CPC itself? */
    opc = MTP3_RL_GET_OPC_VALUE(mtp3->label);
    if (fromCPC && (opc != apc))
    {
        /* The protocol says don't respond */

        return;
    }

    /*
     * Lock the tables we need
     */
    if (DSM_LockTable(
            DSM_SccpFtGroupId, 
            DSM_TABLE_ANSI_SCCP_LPC) != ITS_SUCCESS)
    {
        SCCP_ERROR(("Can't lock table\n"));

        return;
    }
    if (DSM_LockTable(
            DSM_SccpFtGroupId, 
            DSM_TABLE_ANSI_SCCP_CPC) != ITS_SUCCESS)
    {
        SCCP_ERROR(("Can't lock table\n"));

        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);

        return;
    }

    /*
     * if from local SSN, send SSP to all concerned remotes
     */
    if (!fromCPC)
    {

        rinfo = (ROUTE_Info *)DSM_FindNoLock(DSM_SccpFtGroupId,
                                             DSM_TABLE_ANSI_SCCP_LPC,
                                             (ITS_OCTET *)&ctxt,
                                             sizeof(ctxt), &error);
        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("BCSTSendSSP: Couldn't acquire mutex.\n"));

                break;

            case (ITS_EINUSE):
                SCCP_ERROR(("BCSTSendSSP: DSM Row Locked.\n"));

                break;

            case (ITS_ENOTFOUND):
                SCCP_ERROR(("BCSTSendSSP: Can't find local SSN\n"));

                break;

            default:
                SCCP_ERROR(("BCSTSendSSP: Can't find local SSN\n"));

                break;
            }

            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CPC);
            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);

            return;
        }

        /* build SCMG info */
        scmg.type = SCCP_SCMG_SS_PROHIBIT;
        scmg.ssn = oscmg->ssn;
        MTP3_PC_SET_VALUE(scmg.pointCode, apc);
        scmg.multiplicity = SCCP_SCMG_SMI_SOLO;

        hdr = *mtp3;
        MTP3_RL_SET_OPC_VALUE(hdr.label, apc);

        /* send to all concerned */
        for (tinfo1 = rinfo; rinfo != NULL; rinfo = rinfo->next)
        {
            MTP3_RL_SET_DPC_VALUE(hdr.label, rinfo->basic.dpc);

            if (rinfo->basic.style == ROUTE_DPC_SIO_SSN ||
                rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN)
            {
                SendSCMG_ANSI(&hdr, &scmg, rinfo->basic.criteria.ssn);
            }
            else if (rinfo->basic.style == ROUTE_DPC_SIO_SSN_RANGE ||
                     rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN_RANGE)
            {
                SendSCMG_ANSI(&hdr, &scmg, rinfo->basic.criteria.range.begin);
            }
        }

        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CPC);
        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);
    }
    else
    {
        /*
         * for all local ssn's concerned about this remote
         */
        linfo = (ROUTE_Info *)DSM_FindNoLock(DSM_SccpFtGroupId, 
                                             DSM_TABLE_ANSI_SCCP_CPC,
                                             (ITS_OCTET *)&ctxt,
                                             sizeof(ctxt), &error);
        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
            case (ITS_EBADMUTEX):
                SCCP_ERROR(("BCSTSendSSP: Couldn't acquire mutex.\n"));

                break;

            case (ITS_EINUSE):
                SCCP_ERROR(("BCSTSendSSP: DSM Row Locked.\n"));

                break;

            case (ITS_ENOTFOUND):
                SCCP_ERROR(("BCSTSendSSP: Can't find concerned SSN\n"));

                break;

            default:
                SCCP_ERROR(("BCSTSendSSP: Can't find concerned SSN\n"));

                break;
            }

            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CPC);
            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);

            return;
        }

        /* copy in SCMG */
        scmg.type = SCCP_SCMG_SS_PROHIBIT;
        scmg.ssn = oscmg->ssn;
        MTP3_PC_SET_VALUE(scmg.pointCode, apc);
        scmg.multiplicity = SCCP_SCMG_SMI_SOLO;

        for (tinfo1 = linfo; linfo != NULL; linfo = linfo->next)
        {
            ITS_UINT ctxt2 = (ni << 24) | linfo->basic.dpc;
            ITS_OCTET localSSN = 0;

            if (tinfo1->basic.style == ROUTE_DPC_SIO_SSN ||
                tinfo1->basic.style == ROUTE_DPC_OPC_SIO_SSN)
            {
                localSSN = tinfo1->basic.criteria.ssn;
            }
            else if (tinfo1->basic.style == ROUTE_DPC_SIO_SSN_RANGE ||
                     tinfo1->basic.style == ROUTE_DPC_OPC_SIO_SSN_RANGE)
            {
                localSSN = (ITS_OCTET)tinfo1->basic.criteria.range.begin;
            }
            else
            {
                SCCP_ERROR(("Bad route style\n"));

                continue;
            }

            rinfo = (ROUTE_Info *)DSM_FindNoLock(DSM_SccpFtGroupId,
                                                 DSM_TABLE_ANSI_SCCP_LPC,
                                                 (ITS_OCTET *)&ctxt2,
                                                 sizeof(ctxt2), &error);
            if (error != ITS_SUCCESS)
            {
                switch(error)
                {
                case (ITS_EBADMUTEX):
                    SCCP_ERROR(("BCSTSendSSP: Couldn't acquire mutex.\n"));

                    break;

                case (ITS_EINUSE):
                    SCCP_ERROR(("BCSTSendSSP: DSM Row Locked.\n"));
                    
                    break;

                case (ITS_ENOTFOUND):
                    SCCP_ERROR(("BCSTSendSSP: Can't find local SSN\n"));

                    break;

                default:
                    SCCP_ERROR(("BCSTSendSSP: Can't find local SSN\n"));
                    
                    break;
                }
                continue;
            }

            hdr = *mtp3;
            MTP3_RL_SET_OPC_VALUE(hdr.label, linfo->basic.dpc);

            /* inform everybody we know is concerned about this SSN */
            for (tinfo2 = rinfo; rinfo != NULL; rinfo = rinfo->next)
            {
                /* except don't send to the one who informed us */
                if (rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN &&
                    rinfo->basic.dpc == apc &&
                    ((rinfo->basic.criteria.sio & MTP3_NIC_MASK) == ni) &&
                    rinfo->basic.criteria.ssn == oscmg->ssn)
                {
                    continue;
                }
                else if (rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN_RANGE &&
                         rinfo->basic.dpc == apc &&
                         ((rinfo->basic.criteria.sio & MTP3_NIC_MASK) == ni) &&
                         oscmg->ssn >= rinfo->basic.criteria.range.begin &&
                         oscmg->ssn <= rinfo->basic.criteria.range.end)
                {
                    continue;
                }

                MTP3_RL_SET_DPC_VALUE(hdr.label, rinfo->basic.dpc);

                SendSCMG_ANSI(&hdr, &scmg, localSSN);
            }
        }

        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CPC);
        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle receipt of message for prohibited subsytem
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
 *      There's a comment in SCRCHandleSCLCMsg_ANSI that explains why
 *      we put the local SSN in the message.
 *
 ****************************************************************************/
static int
SendSST(ITS_POINTER data, void *in, void *out)
{
    SST_Info *tmp = (SST_Info *)data;
    SCCP_SCMG_ANSI scmg;
    ROUTE_Info *linfo;
    int error;
    ITS_OCTET ni;
    ITS_UINT ctxt;

    scmg.type = SCCP_SCMG_SS_STATUS_TEST;
    scmg.ssn = tmp->routeInfo.basic.criteria.ssn;
    MTP3_PC_SET_VALUE(scmg.pointCode, tmp->routeInfo.basic.dpc);
    scmg.multiplicity = SCCP_SCMG_SMI_SOLO;

    ni = MTP3_HDR_GET_SIO(tmp->sourceHdr) & MTP3_NIC_MASK;
    ctxt = tmp->routeInfo.basic.dpc | (ni << 24);

    linfo = (ROUTE_Info *)DSM_FindNoLock(DSM_SccpFtGroupId,
                                         DSM_TABLE_ANSI_SCCP_CPC,
                                         (ITS_OCTET *)&ctxt,
                                         sizeof(ctxt), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_ERROR(("SCMGHandleSSTTimeout: Couldn't acquire mutex.\n"));

            break;

        case (ITS_EINUSE):
            SCCP_ERROR(("SCMGHandleSSTTimeout: DSM Row Locked.\n"));

            break;

        case (ITS_ENOTFOUND):
            SCCP_ERROR(("SCMGHandleSSTTimeout: Can't find concerned SSN\n"));

            break;

        default:

            SCCP_ERROR(("SCMGHandleSSTTimeout: Can't find concerned SSN\n"));
            break;
        }

        return (ITS_SUCCESS);
    }

    /* we know an LPC is concerned, but it doesn't really matter which */
    if (linfo->basic.style == ROUTE_DPC_SIO_SSN ||
        linfo->basic.style == ROUTE_DPC_OPC_SIO_SSN)
    {
        SendSCMG_ANSI(&tmp->sourceHdr, &scmg,
                 linfo->basic.criteria.ssn);
    }
    else if (linfo->basic.style == ROUTE_DPC_SIO_SSN_RANGE ||
             linfo->basic.style == ROUTE_DPC_OPC_SIO_SSN_RANGE)
    {
        SendSCMG_ANSI(&tmp->sourceHdr, &scmg,
                 linfo->basic.criteria.range.begin);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle receipt of message for prohibited subsytem
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
SCMGHandleSSTTimeout_ANSI()
{
    ITS_UINT size, skey;
    ITS_SERIAL *serial;
    int error;

    SCCP_DEBUG(("SCMGHandleSSTTimeout:\n"));

    /* make sure we're supposed to be here */
    if (!BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_SCMG))
    {
        SCCP_ERROR(("SCMGHandleSSTTimeout: this shouldn't happen\n"));
        
        return (ITS_SUCCESS);
    }

    /* lock the tables we need */
    if (DSM_LockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCMG) != ITS_SUCCESS)
    {
        SCCP_ERROR(("Unable to lock table\n"));
        
        return (ITS_SUCCESS);
    }
    if (DSM_LockTable(
            DSM_SccpFtGroupId, 
            DSM_TABLE_ANSI_SCCP_CPC) != ITS_SUCCESS)
    {
        SCCP_ERROR(("Unable to lock table\n"));

        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCMG);

        return (ITS_SUCCESS);
    }

    /* Generate the SSTs. */
    DSM_TableIterate(
        DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCMG, NULL, NULL, SendSST);

    /* unlock */
    DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CPC);
    DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCMG);

    size = 0;
    DSM_TableGetSize(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCMG, &size);

    /* serial needs to be in DSM */
    if (DSM_LockTable(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA) != ITS_SUCCESS)
    {
        SCCP_ERROR(("DSM Table error\n"));
        return (ITS_SUCCESS);
    }

    skey = DSM_MGMT_REC_ANSI_SCCP_SST_SERIAL;
    if ((serial = DSM_FindNoLock(DSM_SccpFtGroupId,
                                 DSM_TABLE_MGMT_DATA,
                                 (ITS_OCTET *)&skey,
                                 sizeof(ITS_UINT),
                                 &error)) == NULL)
    {
        SCCP_ERROR(("Can't find SST serial key!\n"));        

        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA);

        return (ITS_SUCCESS);
    }

    if (size != 0)
    {
        *serial =
            TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                    TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                         SCCP_T_statInfo),
                                    NULL, 0);
    }
    else
    {
        *serial = 0;
    }

    DSM_CommitNoLock(DSM_SccpFtGroupId,
                     DSM_TABLE_MGMT_DATA,
                     (ITS_OCTET *)&skey, sizeof(ITS_UINT),
                     serial);

    DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle receipt of message for prohibited subsytem
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
SCMGSSPCHandleMsgForProhibitedSSN_ANSI(MTP3_HEADER* mtp3, ITS_OCTET mType,
                                       ITS_SCCP_IE* ies, int ieCount,
                                       ITS_UINT pc, ITS_OCTET ssn,
                                       ITS_OCTET reason)
{
    SCCP_SCMG_ANSI scmg;
    SCCP_ADDR* clp = NULL;
    ITS_OCTET addrInd = 0, toSSN = 0;
    ITS_OCTET ni = MTP3_HDR_GET_SIO_ANSI(*mtp3) & MTP3_NIC_MASK;
    int i;

    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_CALLING_PARTY_ADDR)
        {
            clp = &ies[i].param_data.callingPartyAddr;
            break;
        }
    }

    if (clp == NULL ||
        SCCP_DecodeAddr(clp, &addrInd, NULL, &toSSN,
                        NULL, NULL) != ITS_SUCCESS ||
        !(addrInd & SCCP_CPA_HAS_SSN))
    {
        return (ITS_EINVALIDARGS);
    }

    if (SCCP_IsSSNEquipped(ni, pc, ssn))
    {
        MTP3_HEADER resp;
        ITS_UINT tmp;

        /* build the routing label */
        resp.sio = mtp3->sio;
        tmp = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        MTP3_RL_SET_OPC_VALUE(resp.label, tmp);
        tmp = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        MTP3_RL_SET_DPC_VALUE(resp.label, tmp);
        MTP3_RL_SET_SLS(resp.label, MTP3_RL_GET_SLS(mtp3->label));

        scmg.type = SCCP_SCMG_SS_PROHIBIT;
        scmg.ssn = ssn;
        MTP3_PC_SET_VALUE(scmg.pointCode, pc);
        scmg.multiplicity = SCCP_SCMG_SMI_SOLO;

        return SendSCMG_ANSI(&resp, &scmg, toSSN);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle receipt of SCMG message
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
 *  csireesh   04-04-2005  Bug ID:1674          Incrementing SSC peg.
 *  
 ****************************************************************************/
int
SCMGHandleSCLCMsg_ANSI(MTP3_HEADER* mtp3, ITS_OCTET mType,
                       ITS_SCCP_IE* ies, int ieCount)
{
    int i, error;
    SCCP_SCMG_ANSI scmg;
    ITS_UINT pc;
    ITS_UINT pcgen = 0;
    SCCP_ADDR* clp = NULL;
    SCCP_DATA* data = NULL;
    ITS_OCTET dlen = 0;
    ITS_OCTET addrInd, ssn;
    ITS_BOOLEAN isLocal = ITS_FALSE;
    ITS_BOOLEAN isAllowed;
    ITS_OCTET ni;
    ITS_SERIAL *serial;
    ITS_UINT skey;

    /* recall that this handles both USER and REMOTE SCMG messages */
    /* one case where this will happen is if/when TCAP terminates */
    SCCP_DEBUG(("SCMGHandleSCLC:\n"));

    /* get the NI so we can use it in routing */
    ni = MTP3_HDR_GET_SIO_ANSI(*mtp3);
    ni &= MTP3_NIC_MASK;

    pcgen = MTP3_RL_GET_OPC_VALUE(mtp3->label);

    /* get the data and calling party */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_CALLING_PARTY_ADDR)
        {
            clp = &ies[i].param_data.callingPartyAddr;
        }
        else if (ies[i].param_id == SCCP_PRM_DATA)
        {
            data = &ies[i].param_data.userData;
            dlen = ies[i].param_length;
        }
    }

    /* make sure everything we need looks ok */
    if (data == NULL || clp == NULL)
    {
        SCCP_DEBUG(("SCMGHandleSCLC: Missing data or clp\n"));

        /* Message - Discarding Message - Invalid or Corrupted. */
        SCCP_Alarm_ANSI(50, __FILE__, __LINE__, "family=%s:pc=%x","ANSI", pcgen);

        return (ITS_EINVALIDARGS);
    }

    if (dlen != sizeof(SCCP_SCMG_ANSI))
    {
        SCCP_DEBUG(("SCMGHandleSCLC: Invalid data size\n"));

        /* Message - Discarding Message - Invalid or Corrupted. */
        SCCP_Alarm_ANSI(50, __FILE__, __LINE__, "family=%s:pc=%x","ANSI", pcgen);

        return (ITS_EINVALIDARGS);
    }

    if (SCCP_DecodeAddr(clp, &addrInd, &pc, &ssn, NULL, 0) != ITS_SUCCESS)
    {
        SCCP_DEBUG(("SCMGHandleSCLC: Couldn't decode source addr\n"));
        
        /* Message - Discarding Message - Invalid or Corrupted. */
        SCCP_Alarm_ANSI(50, __FILE__, __LINE__, "family=%s:pc=%x","ANSI", pcgen);

        return (ITS_EINVALIDARGS);
    }

    if ((addrInd & (SCCP_CPA_ROUTE_SSN|SCCP_CPA_HAS_SSN)) !=
            (SCCP_CPA_ROUTE_SSN|SCCP_CPA_HAS_SSN))
    {
        SCCP_DEBUG(("SCMGHandleSCLC: Bad address indicator\n"));

        /* Message - Discarding Message - Invalid or Corrupted. */
        SCCP_Alarm_ANSI(50, __FILE__, __LINE__, "family=%s:pc=%x", "ANSI", pcgen);

        return (ITS_EINVALIDARGS);
    }

    pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);

    /* see if the message originator is local or remote */
    if (SCCP_IsSSNEquipped(ni, pc, ssn))
    {
        isLocal = ITS_TRUE;
    }
    else
    {
        isLocal = ITS_FALSE;
    }

    /* get the SCMG */
    memcpy(&scmg, data->data, sizeof(SCCP_SCMG_ANSI));

    /* now handle it */
    switch (scmg.type)
    {
    case SCCP_SCMG_SS_ALLOWED:
        SCCP_DEBUG(("SCMGHandleSCLC: SSA\n"));
        pc = MTP3_PC_GET_VALUE(scmg.pointCode);

        PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_SSA_RCVD);
    
        if (ROUTE_GetRouteContextStatus(pc, &isAllowed,
                                        ROUTE_DPC_SIO_SSN,
                                        FAMILY_ANSI,
                                        ROUTE_SIO_SCCP | ni,
                                        scmg.ssn,
                                        ITS_SS7_DEFAULT_LINK_SET,
                                        ITS_SS7_DEFAULT_LINK_CODE,
                                        ITS_SS7_DEFAULT_PRI,
                                        ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            return (ITS_EINVALIDARGS);
        }

        SSTCStopSST_ANSI(mtp3, pc, scmg.ssn);

        if (isAllowed)
        {
            /* SSN Already in the allowed state */
            SCCP_Alarm_ANSI(46, __FILE__, __LINE__,
                            "family=%s:pc=%x:ssn=%x",
                            "ANSI", MTP3_RL_GET_OPC_VALUE(mtp3->label), scmg.ssn);

            LBCSSendSSA((ITS_OCTET)(MTP3_HDR_GET_SIO_ANSI(*mtp3) &
                        MTP3_NIC_MASK), pc, scmg.ssn);

            return(ITS_SUCCESS);
        }
        else
        {
            SCCP_Alarm_ANSI(43, __FILE__, __LINE__, "family=%s:pc=%x:ssn=%x",
                             "ANSI", MTP3_RL_GET_OPC_VALUE(mtp3->label),
                             scmg.ssn);
        }

        if(ROUTE_SetRouteContextStatus(pc, ITS_TRUE,
                                    ROUTE_DPC_SIO_SSN,
                                    FAMILY_ANSI,
                                    ROUTE_SIO_SCCP | ni,
                                    scmg.ssn,
                                    ITS_SS7_DEFAULT_LINK_SET,
                                    ITS_SS7_DEFAULT_LINK_CODE,
                                    ITS_SS7_DEFAULT_PRI,
                                    ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCMGHandleSCLC:Failed to set the route"
                        " context status"));
        }

        BCSTSendSSA(mtp3, &scmg, ITS_TRUE);

        LBCSSendSSA((ITS_OCTET)(MTP3_HDR_GET_SIO_ANSI(*mtp3) & MTP3_NIC_MASK),
                    pc, scmg.ssn);
        
        /* State change to Allowed State */
        SCCP_Alarm_ANSI(55, __FILE__, __LINE__,"family:pc=%x:ssn=%x",
                            "ANSI", MTP3_RL_GET_OPC_VALUE(mtp3->label), scmg.ssn);
        
        break;

    case SCCP_SCMG_SS_PROHIBIT:
        SCCP_DEBUG(("SCMGHandleSCLC: SSP\n"));
        pc = MTP3_PC_GET_VALUE(scmg.pointCode);

        PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_SSP_RCVD);

        /* is SS already prohibited */
        if (ROUTE_GetRouteContextStatus(pc, &isAllowed,
                                        ROUTE_DPC_SIO_SSN,
                                        FAMILY_ANSI,
                                        ROUTE_SIO_SCCP | ni,
                                        scmg.ssn,
                                        ITS_SS7_DEFAULT_LINK_SET,
                                        ITS_SS7_DEFAULT_LINK_CODE,
                                        ITS_SS7_DEFAULT_PRI,
                                        ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCMGHandleSCLC:Discarding Message"
                        " No Route to Destination"));

            return (ITS_EINVALIDARGS);
        }


        if (!isAllowed)
        {
           /* Already in the prohibted state for SSN=%x.*/
           SCCP_Alarm_ANSI(47, __FILE__, __LINE__,
                            "family=%s:pc=%x:ssn=%x",
                            "ANSI", pc, scmg.ssn);

           return (ITS_SUCCESS);
        }
        else
        {
            SCCP_Alarm_ANSI(44, __FILE__, __LINE__, "family=%s:pc=%x:ssn:%x",
                           "ANSI", MTP3_RL_GET_OPC_VALUE(mtp3->label), scmg.ssn);
        }

        if(ROUTE_SetRouteContextStatus(pc, ITS_FALSE,
                                    ROUTE_DPC_SIO_SSN,
                                    FAMILY_ANSI,
                                    ROUTE_SIO_SCCP | ni,
                                    scmg.ssn,
                                    ITS_SS7_DEFAULT_LINK_SET,
                                    ITS_SS7_DEFAULT_LINK_CODE,
                                    ITS_SS7_DEFAULT_PRI,
                                    ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
             SCCP_ERROR(("SCMGHandleSCLC:Failed to set the route"
                        " context status"));
         }

        SSTCStartSST_ANSI(mtp3, pc, scmg.ssn);

        LBCSSendSSP((ITS_OCTET)(MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK),
                    pc, scmg.ssn);

        BCSTSendSSP(mtp3, &scmg, ITS_TRUE);

        /*State change to Prohibted State SSN=%x*/
        SCCP_Alarm_ANSI(56, __FILE__, __LINE__,
                         "family=%s:pc=%x:ssn:%x",
                         "ANSI", MTP3_RL_GET_OPC_VALUE(mtp3->label), scmg.ssn);

        break;
    case SCCP_SCMG_SS_CONGESTED:
        SCCP_DEBUG(("SCMGHandleSCLC: SSC\n"));

        PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_SSC_RCVD);

        SCCP_Alarm_ANSI(45, __FILE__, __LINE__, "family=%s:pc=%x:ssn=%x",
                         "ANSI", MTP3_RL_GET_OPC_VALUE(mtp3->label),
                         scmg.ssn);

        pc = MTP3_PC_GET_VALUE(scmg.pointCode);
        if (ROUTE_GetRouteContextStatus(pc, &isAllowed,
                                        ROUTE_DPC_SIO_SSN,
                                        FAMILY_ANSI,
                                        ROUTE_SIO_SCCP | ni,
                                        scmg.ssn,
                                        ITS_SS7_DEFAULT_LINK_SET,
                                        ITS_SS7_DEFAULT_LINK_CODE,
                                        ITS_SS7_DEFAULT_PRI,
                                        ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {

            SCCP_ERROR(("SCMGHandleSCLC:Discarding Message - No Route"
                        " to Destination\n"));

            return (ITS_EINVALIDARGS);
        }
        if (!isAllowed)
        {
            SCCP_Alarm_ANSI(48, __FILE__, __LINE__,
                            "family=%s:pc=%x:ssn=%x",
                             "ANSI", pc, scmg.ssn);
            return (ITS_SUCCESS);
        }

        if(ROUTE_SetRouteContextStatus(pc, ITS_FALSE,
                                    ROUTE_DPC_SIO_SSN,
                                    FAMILY_ANSI,
                                    ROUTE_SIO_SCCP | ni,
                                    scmg.ssn,
                                    ITS_SS7_DEFAULT_LINK_SET,
                                    ITS_SS7_DEFAULT_LINK_CODE,
                                    ITS_SS7_DEFAULT_PRI,
                                    ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCMGHandleSCLC:Failed to set the route context\n"));
        }

        LBCSSendSSC((ITS_OCTET)(MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK),
                    pc, scmg.ssn);

        break;

    case SCCP_SCMG_SS_STATUS_TEST:

        SCCP_DEBUG(("SCMGHandleSCLC: SST from %08x:%02x\n",
                    MTP3_RL_GET_OPC_VALUE(mtp3->label), ssn));

        if (DSM_LockTable(
                DSM_SccpFtGroupId, 
                DSM_TABLE_MGMT_DATA) != ITS_SUCCESS)
        {
            SCCP_ERROR(("DSM Table error\n"));

            return (ITS_EBADMUTEX);
        }

        skey = DSM_MGMT_REC_ANSI_SCCP_SST_IGNORE_SERIAL;
        if ((serial = DSM_FindNoLock(DSM_SccpFtGroupId,
                                     DSM_TABLE_MGMT_DATA,
                                     (ITS_OCTET *)&skey,
                                     sizeof(ITS_UINT),
                                     &error)) == NULL)
        {
            SCCP_ERROR(("Can't find SST IGNORE serial key!\n"));

            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA);

            return (ITS_ENOTFOUND);
        }

        if (*serial == 0)
        {
            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA);

            /* SSTC */
            if (ROUTE_GetRouteContextStatus(pc, &isAllowed,
                                            ROUTE_DPC_SIO_SSN,
                                            FAMILY_ANSI,
                                            ROUTE_SIO_SCCP | ni,
                                            scmg.ssn,
                                            ITS_SS7_DEFAULT_LINK_SET,
                                            ITS_SS7_DEFAULT_LINK_CODE,
                                            ITS_SS7_DEFAULT_PRI,
                                            ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
            {
                return (ITS_EINVALIDARGS);
            }

            if (isAllowed)
            {
                MTP3_HEADER resp;
                ITS_UINT tmp;

                /* build the routing label */
                resp.sio = mtp3->sio;
                tmp = MTP3_RL_GET_DPC_VALUE(mtp3->label);
                MTP3_RL_SET_OPC_VALUE(resp.label, tmp);
                tmp = MTP3_RL_GET_OPC_VALUE(mtp3->label);
                MTP3_RL_SET_DPC_VALUE(resp.label, tmp);
                MTP3_RL_SET_SLS(resp.label, MTP3_RL_GET_SLS(mtp3->label));

                scmg.type = SCCP_SCMG_SS_ALLOWED;

                SendSCMG_ANSI(&resp, &scmg, ssn);
            }
        }
        else
        {
            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA);

            SCCP_DEBUG(("SCMGHandleSCLC: SST Received is Ignored\n"));
        }

        break;

    case SCCP_SCMG_SS_UIS:
        SCCP_DEBUG(("SCMGHandleSCLC: UIS\n"));

        if (!isLocal)
        {
            SCCP_Alarm_ANSI(54, __FILE__, __LINE__, "family=%s:pc=%x:ssn:%x",
                         "ANSI", pc,scmg.ssn);
      
            SCCP_DEBUG(("Not local\n"));
        
            /* Message - Discarding Message - Invalid or Corrupted. */

            SCCP_ERROR(("SCMGHandleSCLC:Message is invalid or corrupted\n"));

            /* How the heck did we get this */
            return (ITS_EINVALIDARGS);
        }

        pc = MTP3_PC_GET_VALUE(scmg.pointCode);
        if (ROUTE_GetRouteContextStatus(pc, &isAllowed,
                                        ROUTE_DPC_SIO_SSN,
                                        FAMILY_ANSI,
                                        ROUTE_SIO_SCCP | ni,
                                        scmg.ssn,
                                        ITS_SS7_DEFAULT_LINK_SET,
                                        ITS_SS7_DEFAULT_LINK_CODE,
                                        ITS_SS7_DEFAULT_PRI,
                                        ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            SCCP_DEBUG(("No route: pc %08x ssn %d\n", pc, scmg.ssn));

            return (ITS_EINVALIDARGS);
        }

        if (isAllowed)
        {
            SCCP_DEBUG(("Already allowed\n"));

            LBCSSendUIS(ni, pc, scmg.ssn);

            SCCP_Alarm_ANSI(51, __FILE__, __LINE__,
                            "family=%s:ssn=%x","ANSI", scmg.ssn);


            return (ITS_SUCCESS);
        }

        if( ROUTE_SetRouteContextStatus(pc, ITS_TRUE,
                                    ROUTE_DPC_SIO_SSN,
                                    FAMILY_ANSI,
                                    ROUTE_SIO_SCCP | ni,
                                    scmg.ssn,
                                    ITS_SS7_DEFAULT_LINK_SET,
                                    ITS_SS7_DEFAULT_LINK_CODE,
                                    ITS_SS7_DEFAULT_PRI,
                                    ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SMGHandleSCLC:Failed to set the route context"
                        " status "));
        }

        BCSTSendSSA(mtp3, &scmg, ITS_FALSE);

        LBCSSendUIS(ni, pc, scmg.ssn);

        break;

    case SCCP_SCMG_SS_UOS:
    {
        ITS_INT ctxt = (ssn << 24) | pc;
        ROUTE_Info *rinfo;

        SCCP_DEBUG(("SCMGHandleSCLC: UOS\n"));

        if (!isLocal)
        {
            SCCP_Alarm_ANSI(53, __FILE__, __LINE__, "family=%s:pc=%x:ssn=%x",
                         "ANSI", pc,scmg.ssn);
        
            SCCP_ERROR(("SCMGHandleSCLC:Discarding Message - Invalid or"
                         " Corrupted."));
            /* How the heck did we get this */
            return (ITS_EINVALIDARGS);
        }

        if (ROUTE_GetRouteContextStatus(pc, &isAllowed,
                                        ROUTE_DPC_SIO_SSN,
                                        FAMILY_ANSI,
                                        ROUTE_SIO_SCCP | ni,
                                        scmg.ssn,
                                        ITS_SS7_DEFAULT_LINK_SET,
                                        ITS_SS7_DEFAULT_LINK_CODE,
                                        ITS_SS7_DEFAULT_PRI,
                                        ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCMGHandleSCLCDiscarding Message - No Route"
                        " to Destination"));

            return (ITS_EINVALIDARGS);
        }

        if (!isAllowed)
        {
            LBCSSendUOS(ni, pc, scmg.ssn);

            /*Already in the Prohibted State, so broad casting locally.*/
            SCCP_Alarm_ANSI(52, __FILE__, __LINE__,"family=%s:pc=%x:ssn=%x",
                          "ANSI", MTP3_RL_GET_OPC_VALUE(mtp3->label), scmg.ssn);

            return (ITS_SUCCESS);
        }

        if(ROUTE_SetRouteContextStatus(pc, ITS_FALSE,
                                    ROUTE_DPC_SIO_SSN,
                                    FAMILY_ANSI,
                                    ROUTE_SIO_SCCP | ni,
                                    scmg.ssn,
                                    ITS_SS7_DEFAULT_LINK_SET,
                                    ITS_SS7_DEFAULT_LINK_CODE,
                                    ITS_SS7_DEFAULT_PRI,
                                    ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCMGHandleSCLC:Failed to set the route"
                        " context status"));
        }

        LBCSSendUOS(ni, pc, scmg.ssn);

        BCSTSendSSP(mtp3, &scmg, ITS_FALSE);

        /* get the duplicate */
        if ((rinfo = DSM_Find(DSM_SccpFtGroupId,
                              DSM_TABLE_ANSI_SCCP_DUPS,
                              (ITS_OCTET *)&ctxt,
                              sizeof(ITS_UINT), &error)) == NULL)
        {
            /* don't complain.  The user probably doesn't have a duplicate */
            return (ITS_SUCCESS);
        }

        if (rinfo->basic.type == DUPLICATED_ROUTE)
        {
            SCMG_SendSORToDuplicate(&scmg,
                                    (ITS_OCTET)(rinfo->basic.criteria.sio &
                                                MTP3_NIC_MASK),
                                    rinfo->basic.dpc,
                                    rinfo->basic.criteria.ssn);
        }

        break;
    }
    case SCCP_SCMG_SS_CONG:
        SCCP_DEBUG(("SCMGHandleSCLC: SS CONG\n"));
        PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_SSC_RCVD);

        if (!isLocal)
        {
            SCCP_Alarm_ANSI(45, __FILE__, __LINE__, "family=%s:pc=%x:ssn=%x", "ANSI", pc,
                         ssn);
            SCCP_ERROR(("SCMGHandleSCLC:Discarding Message - Invalid or"
                         " Corrupted.\n"));
            return (ITS_EINVALIDARGS);
        }

        if (ROUTE_GetRouteContextStatus(pc, &isAllowed,
                                        ROUTE_DPC_SIO_SSN,
                                        FAMILY_ANSI,
                                        ROUTE_SIO_SCCP | ni,
                                        scmg.ssn,
                                        ITS_SS7_DEFAULT_LINK_SET,
                                        ITS_SS7_DEFAULT_LINK_CODE,
                                        ITS_SS7_DEFAULT_PRI,
                                        ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCMGHandleSCLCDiscarding Message - No Route"
                        " to Destination\n"));

            return (ITS_EINVALIDARGS);
        }

        if (!isAllowed)
        {
            LBCSSendSSC((ITS_OCTET)(MTP3_HDR_GET_SIO(*mtp3) &
                                    MTP3_NIC_MASK), pc, scmg.ssn);
            SCCP_Alarm_ANSI(48, __FILE__, __LINE__,
                            "family=%s:pc=%x:ssn=%x",
                             "ANSI", pc, scmg.ssn);

            return (ITS_SUCCESS);
        }

        if(ROUTE_SetRouteContextStatus(pc, ITS_FALSE,
                                    ROUTE_DPC_SIO_SSN,
                                    FAMILY_ANSI,
                                    ROUTE_SIO_SCCP | ni,
                                    scmg.ssn,
                                    ITS_SS7_DEFAULT_LINK_SET,
                                    ITS_SS7_DEFAULT_LINK_CODE,
                                    ITS_SS7_DEFAULT_PRI,
                                    ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCMGHandleSCLC: Failed to set the route"
                        " context status\n"));
        }

        LBCSSendSSC((ITS_OCTET)(MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK),
                    pc, scmg.ssn);

        BCSTSendSSC(mtp3, &scmg, ITS_FALSE);

        break;

    /* these all have to do with multiplicity */
    case SCCP_SCMG_SS_OOS_REQ:

        pc = MTP3_PC_GET_VALUE(scmg.pointCode);

        if (!isLocal)
        {
            SCCP_Alarm_ANSI(53, __FILE__, __LINE__, "family=%s:pc=%x:ssn=%x",
                         "ANSI", pc,scmg.ssn);
        }

        if (ROUTE_GetRouteContextStatus(pc, &isAllowed,
                                        ROUTE_DPC_SIO_SSN,
                                        FAMILY_ANSI,
                                        ROUTE_SIO_SCCP | ni,
                                        scmg.ssn,
                                        ITS_SS7_DEFAULT_LINK_SET,
                                        ITS_SS7_DEFAULT_LINK_CODE,
                                        ITS_SS7_DEFAULT_PRI,
                                        ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCMGHandleSCLC: Message - Discarding Message"
                        " No Route to Destination"));
            return (ITS_EINVALIDARGS);
        }
            
        /* this way we let to the user the decision to take the
           additional traffic or not */
        CALLBACK_CallCallbackList(SCCP_ManagementCallbacks,
                                  NULL,
                                  (ITS_POINTER)&scmg);

        if (scmg.type == SCCP_SCMG_SS_OOS_GRANT)
        {
            SCMG_SendSOGToDuplicate(mtp3, &scmg);
        }
        
        break;
        
    case SCCP_SCMG_SS_OOS_GRANT:
        /* check if SOR timer has not expired */
        if (DSM_LockTable(
                DSM_SccpFtGroupId, 
                DSM_TABLE_MGMT_DATA) != ITS_SUCCESS)
        {
            SCCP_ERROR(("DSM Table error\n"));
            return (ITS_EBADMUTEX);
        }

        skey = DSM_MGMT_REC_ANSI_SCCP_SOR_SERIAL;
        if ((serial = DSM_FindNoLock(DSM_SccpFtGroupId,
                                     DSM_TABLE_MGMT_DATA,
                                     (ITS_OCTET *)&skey,
                                     sizeof(ITS_UINT),
                                     &error)) == NULL)
        {
            SCCP_ERROR(("Can't find SOR serial key!\n"));

            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA);

            return (ITS_ENOTFOUND);
        }

        if (*serial != 0)
        {
            TIMERS_CancelTimer(*serial);
            *serial = 0;

            DSM_CommitNoLock(DSM_SccpFtGroupId,
                             DSM_TABLE_MGMT_DATA,
                             (ITS_OCTET *)&skey, sizeof(ITS_UINT),
                             serial);

            /* We need to broadcast Subsystem Prohibited to all 
               concerned users */
            BCSTSendSSP(mtp3, &scmg, ITS_TRUE);

            /* according to specs we also need to start a ignore SST timer
               and ignore all SST for the duration of this timer */
            skey = DSM_MGMT_REC_ANSI_SCCP_SST_IGNORE_SERIAL;
            if ((serial = DSM_FindNoLock(DSM_SccpFtGroupId,
                                         DSM_TABLE_MGMT_DATA,
                                         (ITS_OCTET *)&skey,
                                         sizeof(ITS_UINT),
                                         &error)) == NULL)
            {
                SCCP_ERROR(("Can't find SOR serial key!\n"));

                DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA);

                return (ITS_ENOTFOUND);
            }

            *serial = 
               TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                       TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                            SCCP_T_ignoreSST),
                                       NULL, 0);

            DSM_CommitNoLock(DSM_SccpFtGroupId,
                             DSM_TABLE_MGMT_DATA,
                             (ITS_OCTET *)&skey, sizeof(ITS_UINT),
                             serial);

            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA);

            /* We need to put the system out of service
               this done by setting the route to down */
            /* FIXME: if the route is a range, we should add an xlist
             * entry as a specific match for the down route.
             */
            if (ROUTE_SetRouteContextStatus(MTP3_PC_GET_VALUE(scmg.pointCode),
                                            ITS_FALSE, ROUTE_DPC_SIO_SSN,
                                            FAMILY_ANSI,
                                            ROUTE_SIO_SCCP | ni,
                                            scmg.ssn,
                                            ITS_SS7_DEFAULT_LINK_SET,
                                            ITS_SS7_DEFAULT_LINK_CODE,
                                            ITS_SS7_DEFAULT_PRI,
                                            ITS_SS7_DEFAULT_SLS))
            {
                SCCP_ERROR(("Unable to update Route Status for PC: %d, SSN %02x.\n",
                            scmg.pointCode, scmg.ssn));

            }

        }
        else
        {
            /* just unlock the table */
            DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_MGMT_DATA);
        }
        
        /* timer has expired, we ignore the message */

        break;


    case SCCP_SCMG_SS_BACKUP_ROUTE:
    case SCCP_SCMG_SS_NORMAL_ROUTE:
    case SCCP_SCMG_SS_ROUTE_STATUS:
        SCCP_DEBUG(("SCMGHandleSCLC: Unsupported\n"));

        break;

    default:
        SCCP_DEBUG(("SCMGHandleSCLC: Unknown: %02x,PC %08x\n", scmg.type,pc));

        /* Message - Discarding Message -  SCMG Type Unknown. */
        SCCP_Alarm_ANSI(49, __FILE__, __LINE__,
                                   "family=%s",
                                   "ANSI");

        break;
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Set the Route Status 
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
 *  kramesh   22-04-2008  Bug ID:1123      Propagated TCS Issue.
 *                                         Deadlock occurs when processing 
 *                                         multiple PAUSEs/RESUMEs at the same time 
 *  
 ****************************************************************************/

static int
SetRoutesStatus(ITS_UINT pc, ITS_OCTET ni, ITS_BOOLEAN status)
{
    SS7_Destination *dest = NULL;
    int i = 0;

    ROUTE_UnlockRead(routeRWLock, __SCCP_ANSI_RcvQueue);

    if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
    {
        if (ROUTE_LockForRead(routeRWLock) != ITS_SUCCESS)
        {
            SCCP_ERROR(("Failed to get route lock\n"));
        }

        SCCP_ERROR(("SetRoutesStatus: Failed to lock routing table."));
        return (ITS_EBADMUTEX);
    }

    dest = ROUTE_FindDestination(pc, ni, FAMILY_ANSI);
    if (dest == NULL)
    {
        ROUTE_UnlockWrite(routeRWLock);

        if (ROUTE_LockForRead(routeRWLock) != ITS_SUCCESS)
        {
            SCCP_ERROR(("Failed to get route lock\n"));
        }

        SCCP_ERROR(("SetRoutesStatus: Destination PC: %d, ni: %02x, not found.\n"));
        return (ITS_ENOTFOUND);
    }

    for (i = 0; i < dest->numEntries; i++)
    {
        if (dest->entries[i]->basic.style == ROUTE_DPC_SIO_SSN &&
            dest->entries[i]->basic.type == REMOTE_ROUTE)
        {
            int ret = ITS_SUCCESS;

            ret = ROUTE_SetRouteContextStatus(pc, status,
                                    ROUTE_DPC_SIO_SSN,
                                    FAMILY_ANSI,
                                    ROUTE_SIO_SCCP | ni,
                                    dest->entries[i]->basic.criteria.ssn, 
                                    ITS_SS7_DEFAULT_LINK_SET,
                                    ITS_SS7_DEFAULT_LINK_CODE,
                                    ITS_SS7_DEFAULT_PRI,
                                    ITS_SS7_DEFAULT_SLS);
            if (ret != ITS_SUCCESS)
            {
                SCCP_ERROR(("SetRoutesStatus: Failed to set route status.\n"));
            }
        }
    }

    if (status)
    {
        dest->status = DESTINATION_AVAILABLE;
    }
    else
    {
        dest->status = DESTINATION_UNAVAILABLE;
    }

    ROUTE_CommitDestination(dest, pc, ni, FAMILY_ANSI);

    ROUTE_UnlockWrite(routeRWLock);

    if (ROUTE_LockForRead(routeRWLock) != ITS_SUCCESS)
    {
        SCCP_ERROR(("Failed to get route lock\n"));
    }

    return (ITS_SUCCESS);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Perform the SCCP procedure for a paused point code
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
 *  kramesh   22-04-2008  Bug ID:1123        Propagated TCS Issue.
 *                                        Deadlock occurs when processing 
 *                                        multiple PAUSEs/RESUMEs at the same time 
 *  
 ****************************************************************************/
static void 
PausePC(MTP3_HEADER *mtp3, ITS_UINT pc)
{
    ROUTE_Info *linfo, *rinfo, *tinfo1, *tinfo2;
    ITS_OCTET ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;
    ITS_UINT ctxt = (ni << 24) | pc;
    int error, ret;

    ret = SetRoutesStatus(pc, ni, ITS_FALSE);
    if (ret != ITS_SUCCESS)
    { 
        SCCP_ERROR(("PausePC: Failed to set routes prohibited for DPC: %d.\n",
                    pc));
    }
    else
    {
       SCCP_DEBUG(("PausePC: Set route status to prohibited for "
                    "DPC: %d.\n", pc));
    }

    if (DSM_LockTable(
            DSM_SccpFtGroupId, 
            DSM_TABLE_ANSI_SCCP_LPC) != ITS_SUCCESS)
    {

        SCCP_ERROR(("Unable to acquire LPC lock\n"));

        return;
    }
    if (DSM_LockTable(
            DSM_SccpFtGroupId, 
            DSM_TABLE_ANSI_SCCP_CPC) != ITS_SUCCESS)
    {
        SCCP_ERROR(("Unable to acquire CPC lock\n"));

        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);

        return;
    }

    /* Stop SSTs to concerned SSNs for this PC */
    /* Send SSP for concerned SSNs for this PC */
    if ((linfo = DSM_FindNoLock(DSM_SccpFtGroupId, 
                                DSM_TABLE_ANSI_SCCP_CPC,
                                (ITS_OCTET *)&ctxt, sizeof(ITS_UINT),
                                &error)) != NULL)
    {
        for (tinfo1 = linfo; linfo != NULL; linfo = linfo->next)
        {
            ITS_UINT ctxt2 = (ni << 24) | linfo->basic.dpc;

            if ((rinfo = DSM_FindNoLock(DSM_SccpFtGroupId, 
                                        DSM_TABLE_ANSI_SCCP_LPC,
                                        (ITS_OCTET *)&ctxt2,
                                        sizeof(ITS_UINT), &error)) != NULL)
            {
                for (tinfo2 = rinfo; rinfo != NULL; rinfo = rinfo->next)
                {
                    if (rinfo->basic.dpc == pc)
                    {
                        if (rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN)
                        {
                            SSTCStopSST_ANSI(mtp3, pc, rinfo->basic.criteria.ssn);

                            LBCSSendSSP((ITS_OCTET)(MTP3_HDR_GET_SIO(*mtp3) &
                                                    MTP3_NIC_MASK),
                                        pc, rinfo->basic.criteria.ssn);
                        }
                        else if (rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN_RANGE)
                        {
                            ITS_USHORT cnt;

                            for (cnt = rinfo->basic.criteria.range.begin;
                                 cnt <= rinfo->basic.criteria.range.end;
                                 cnt++)
                            {
                                SSTCStopSST_ANSI(mtp3, pc, (ITS_OCTET)cnt);

                                LBCSSendSSP((ITS_OCTET)(MTP3_HDR_GET_SIO(*mtp3) &
                                                        MTP3_NIC_MASK),
                                            pc, (ITS_OCTET)cnt);
                            }
                        }
                    }
                }
            }
        }
    }

    DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CPC);
    DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Perform the SCCP procedure for a paused point code
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
 *  kramesh   22-04-2008  Bug ID:1123         Propagated TCS Issue.
 *                                            Deadlock occurs when processing 
 *                                        multiple PAUSEs/RESUMEs at the same time 
 *  
 ****************************************************************************/
static void
ResumePC(MTP3_HEADER *mtp3, ITS_UINT pc)
{
    ITS_OCTET ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;
    ITS_UINT ctxt = (ni << 24) | pc;
    ROUTE_Info *linfo, *rinfo, *tinfo1, *tinfo2;
    int error, ret;

    ret = SetRoutesStatus(pc, ni, ITS_TRUE);
    if (ret != ITS_SUCCESS)
    {
        SCCP_ERROR(("ResumePC: Failed to set routes Allowed for DPC: %d.\n",
                    pc));
    }
    else
    {
        SCCP_DEBUG(("ResumePC: Set routes Allowed for DPC: %d.\n", 
                     pc));
    }

    if (DSM_LockTable(
            DSM_SccpFtGroupId, 
            DSM_TABLE_ANSI_SCCP_LPC) != ITS_SUCCESS)
    {
        SCCP_ERROR(("Unable to acquire LPC lock\n"));

        return;
    }
    if (DSM_LockTable(
            DSM_SccpFtGroupId, 
            DSM_TABLE_ANSI_SCCP_CPC) != ITS_SUCCESS)
    {
        SCCP_ERROR(("Unable to acquire CPC lock\n"));

        DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);

        return;
    }

    /* Start SST for SSNs on this PC */
    if ((linfo = DSM_FindNoLock(DSM_SccpFtGroupId, 
                                DSM_TABLE_ANSI_SCCP_CPC,
                                (ITS_OCTET *)&ctxt,
                                sizeof(ITS_UINT), &error)) != NULL)
    {
        for (tinfo1 = linfo; linfo != NULL; linfo = linfo->next)
        {
            ITS_UINT ctxt2 = (ni << 24) | linfo->basic.dpc;

            if ((rinfo = DSM_FindNoLock(DSM_SccpFtGroupId,
                                        DSM_TABLE_ANSI_SCCP_LPC,
                                        (ITS_OCTET *)&ctxt2,
                                        sizeof(ITS_UINT), &error)) != NULL)
            {
                for (tinfo2 = rinfo; rinfo != NULL; rinfo = rinfo->next)
                {
                    if (rinfo->basic.dpc == pc)
                    {
                        if (rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN)
                        {
                            SSTCStartSST_ANSI(mtp3, pc, rinfo->basic.criteria.ssn);
                        }
                        else if (rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN_RANGE)
                        {
                            ITS_USHORT cnt;

                            for (cnt = rinfo->basic.criteria.range.begin;
                                 cnt <= rinfo->basic.criteria.range.end;
                                 cnt++)
                            {
                                SSTCStartSST_ANSI(mtp3, pc, (ITS_OCTET)cnt);
                            }
                        }
                    }
                }
            }
        }
    }

    DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_CPC);
    DSM_UnlockTable(DSM_SccpFtGroupId, DSM_TABLE_ANSI_SCCP_LPC);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle receipt of MTP3 management indications
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
SCMGHandleMTP3Msg_ANSI(MTP3_HEADER* mtp3, ITS_OCTET mType,
                       ITS_OCTET* data, ITS_USHORT len)
{
    MTP3_PAUSE_RESUME pr;
    MTP3_STATUS st;
    ITS_UINT pc = 0;

    if (!BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors,
                              SCCP_B_use_SCMG))
    {
        return (ITS_SUCCESS);
    }

    switch (mType)
    {
    case MTP3_MSG_PAUSE:
        /* SPPC */
        SCCP_DEBUG(("SCMGHandleMTP3: MTP-PAUSE\n"));

        if (len != sizeof(MTP3_PAUSE_RESUME))
        {
           /* Unexpected message length.*/
            SCCP_Alarm_ANSI(39, __FILE__, __LINE__, "family=%s", "ANSI");

            break;
        }

        /* Incr Pause Indication Counter for SCCP */
        PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_MTP3_MSG_PAUSE);

        memcpy(&pr, data, len);
        pc = MTP3_PC_GET_VALUE(pr.affected);
        SCCP_Alarm_ANSI(37, __FILE__, __LINE__, "family=%s:pc=%x",
                      "ANSI", MTP3_RL_GET_OPC_VALUE(mtp3->label));

        PausePC(mtp3, pc);

        LBCSSendSPInAcc(mtp3, pc);

        break;

    case MTP3_MSG_RESUME:
        /* SPAC */
        SCCP_DEBUG(("SCMGHandleMTP3: MTP-RESUME\n"));
        SCCP_Alarm_ANSI(36, __FILE__, __LINE__, "family=%s:pc=%x",
                      "ANSI", MTP3_RL_GET_OPC_VALUE(mtp3->label));

        if (len != sizeof(MTP3_PAUSE_RESUME))
        {
           /* Unexpected message length.*/
            SCCP_Alarm_ANSI(39, __FILE__, __LINE__, "family=%s", "ANSI");

            break;
        }

        /* Incr Resume Indication Counter for SCCP */
        PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_MTP3_MSG_RESUME);
 
        memcpy(&pr, data, len);
        pc = MTP3_PC_GET_VALUE(pr.affected);


        /* This code is added to take care of the following scenario:
            -- When the Link to the standby node is aligned first, then
               RESUME Indication will be received by Standby SCCP.  During
               the Node swithover (only the node state got changed, i.e
               the Standby Node changed its state to Active), then SST
               should be started only by the Active Node.  Before starting
               the SST Timer, the CPC/LPC Table is checked to see whether
               any concerned SSN are configured.
 
               BuildCPCData and BuildDupData peforms the building of the
               concerned ssn list and also the duplicate entry list
        */
 
        ROUTE_UnlockReadDSM(routeRWLock);

        BuildCPCData_ANSI();
        BuildDupData_ANSI();

        if (ROUTE_LockForRead(routeRWLock) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCMGHandleMTP3Msg_ANSI: Failed to get route lock\n"));
        }


        /* Removing the PRIMARY check placed.. let SST/SSA start after RESUME
         * Anyways, SST woun't go out after SSTTimer Expiry if node is
         * is BACKUP (with check in scrc
         */
        ResumePC(mtp3, pc);

        LBCSSendSPAcc(mtp3, pc);

        break;

    case MTP3_MSG_STATUS:
        /* SPCC */
        SCCP_DEBUG(("SCMGHandleMTP3: MTP-STATUS\n"));

        SCCP_Alarm_ANSI(38, __FILE__, __LINE__, "family=%s:pc=%x",
                      "ANSI", MTP3_RL_GET_OPC_VALUE(mtp3->label));

        if (len != sizeof(MTP3_STATUS))
        {
            /* Unexpected message length.*/
            SCCP_Alarm_ANSI(39, __FILE__, __LINE__, "family=%s", "ANSI");
            break;
        }

        /* Incr Status Indication Counter for SCCP */
        PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_MTP3_MSG_STATUS);
 
        memcpy(&st, data, len);
        pc = MTP3_PC_GET_VALUE(st.affected);

        LBCSSendSPCong(mtp3, pc, st.congLevel);
        break;

    default:
        break;
    }



    return (ITS_SUCCESS);
}

