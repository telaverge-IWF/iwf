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
 *  ID: $Id: itu-mgmt.c,v 9.7.30.2.8.1 2014/09/17 07:01:58 jsarvesh Exp $
 *
 * LOG: $Log: itu-mgmt.c,v $
 * LOG: Revision 9.7.30.2.8.1  2014/09/17 07:01:58  jsarvesh
 * LOG: Changes done for removing warnings
 * LOG:
 * LOG: Revision 9.7.30.2.4.1  2014/09/15 07:23:32  jsarvesh
 * LOG: Changes done for removing Warnings
 * LOG:
 * LOG: Revision 9.7.30.2  2013/12/10 13:42:29  jsarvesh
 * LOG: IwfProductization Changes done to add Error Handling for UAL Configuration
 * LOG:
 * LOG: Revision 9.7.30.1  2013/11/18 11:41:40  jsarvesh
 * LOG: Iwf_Productization Changes done for Dynamic Sigtran Configuration
 * LOG:
 * LOG: Revision 9.7  2008/06/04 10:36:34  ssingh
 * LOG: ALU porting, B-0100LX-LUSG-00 (june 04,2008 base)
 * LOG:
 * LOG: Revision 9.6  2008/05/01 13:42:57  kramesh
 * LOG: Propagated WSC Issue 1030. rt_dump mml display issue.
 * LOG:
 * LOG: Revision 9.5  2007/01/11 12:43:37  yranade
 * LOG: Merge changes from 6.5.3 and Lucent branches
 * LOG:
 * LOG: Revision 9.4.4.20  2008/03/28 11:01:44  ssodhi
 * LOG: Issue 376
 * LOG:
 * LOG: Revision 9.4.4.19  2008/03/24 10:30:47  ssodhi
 * LOG: Improved mi_get_ls_s and rt_dump_s
 * LOG:
 * LOG: Revision 9.4.4.18  2008/03/19 12:22:54  ssodhi
 * LOG: Fix for issue 357 and added/improved MTP3 traces
 * LOG:
 * LOG: Revision 9.4.4.17  2008/03/14 14:41:15  ssodhi
 * LOG: Infra to calculate MTP3Thread's event processing rate
 * LOG:
 * LOG: Revision 9.4.4.16  2008/02/17 15:09:34  ssodhi
 * LOG: Improving the command mi_set_link_attrib
 * LOG:
 * LOG: Revision 9.4.4.15  2008/02/08 06:38:28  ssodhi
 * LOG: A command to aid developers.
 * LOG:
 * LOG: Revision 9.4.4.14  2008/01/14 10:23:03  ssodhi
 * LOG: Code changes for Accelero Performance Enhancement - ALU BSG Project
 * LOG:
 * LOG: Revision 9.4.4.13  2007/05/09 12:26:12  mshanmugam
 * LOG: Fix for 5731 - skatta
 * LOG:
 * LOG: Revision 9.4.4.12  2007/04/26 08:57:55  raghavendrabk
 * LOG: Resolved issue with Linkset Peg collection
 * LOG:
 * LOG: Revision 9.4.4.11  2007/04/11 07:48:20  mshanmugam
 * LOG: Family check is added for link pegs
 * LOG:
 * LOG: Revision 9.4.4.10  2007/03/31 10:38:01  mshanmugam
 * LOG: Fix for MMLs mi_get_all_lpc mi_get_all_rpc
 * LOG:
 * LOG: Revision 9.4.4.9  2007/03/21 12:09:53  sdwivedi
 * LOG: Fix for Parallel Stack Issue #5230
 * LOG:
 * LOG: Revision 9.4.4.8  2007/02/26 10:19:55  raghavendrabk
 * LOG: Family structure filled in OM API
 * LOG:
 * LOG: Revision 9.4.4.7  2007/02/07 11:57:58  gharipriya
 * LOG: Fix for Parallel Stack Issues 5223,5231, 5295,5296 raised on MMLs
 * LOG:
 * LOG: Revision 9.4.4.6  2007/02/07 11:42:41  raghavendrabk
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 9.4.4.5  2006/09/26 06:52:22  mshanmugam
 * LOG: Removing The Q752 Compilation flag
 * LOG:
 * LOG: Revision 9.4.4.4  2006/09/13 15:28:17  mshanmugam
 * LOG: extern c with cpp defined added
 * LOG:
 * LOG: Revision 9.4.4.3  2006/09/13 10:34:51  mshanmugam
 * LOG: The Get and Reset Om Functions made as extern C for Q752.
 * LOG:
 * LOG: Revision 9.4.4.2  2006/08/18 12:26:03  mshanmugam
 * LOG: Added new APIs for Q.752 Implementation.
 * LOG:
 * LOG: Revision 9.4.4.1  2005/11/11 22:50:01  randresol
 * LOG: Fix MTP3 bugs(PBN ISSUE:2921, 2773, 2691 )  for Lucent BSG
 * LOG:
 * LOG: Revision 9.4  2005/05/17 06:04:14  adutta
 * LOG: Fixed issue#1840
 * LOG:
 * LOG: Revision 9.3  2005/05/06 06:14:43  adutta
 * LOG: MTP Route pegs declaration
 * LOG:
 * LOG: Revision 9.2  2005/04/07 09:10:29  snagesh
 * LOG: Modifications for LPO Feature
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:41  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:53:44  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.5.2.7.2.3.4.11  2005/02/28 11:51:04  mmanikandan
 * LOG: Compilation Error fixed.
 * LOG:
 * LOG: Revision 7.5.2.7.2.3.4.10  2005/02/21 05:07:22  snagesh
 * LOG: PEG_MTP3_USERPART_DISABLE removed from the list
 * LOG:
 * LOG: Revision 7.5.2.7.2.3.4.9  2005/02/21 04:37:59  snagesh
 * LOG: Fixes for OAM bugs 1490 and 1547 - individual and "All" option showing diff values
 * LOG: and clearing of link pegs
 * LOG:
 * LOG: Revision 7.5.2.7.2.3.4.8  2005/02/07 11:44:29  sbabu
 * LOG: MTP3 OAM Bug Fix
 * LOG:
 * LOG: Revision 7.5.2.7.2.3.4.7  2005/01/31 11:51:02  snagesh
 * LOG: MTP3 OSS APIs added
 * LOG:
 * LOG: Revision 7.5.2.7.2.3.4.6  2005/01/11 13:06:39  craghavendra
 * LOG: Syslog Enhancements.
 * LOG:
 * LOG: Revision 7.5.2.7.2.3.4.5  2005/01/07 12:14:01  mmanikandan
 * LOG: Compiler limit in windows for braces.
 * LOG:
 * LOG: Revision 7.5.2.7.2.3.4.4  2005/01/04 16:05:02  snagesh
 * LOG: Commented get_pegids MMLs
 * LOG:
 * LOG: Revision 7.5.2.7.2.3.4.3  2005/01/04 13:43:56  mmanikandan
 * LOG: Changes for CTF.
 * LOG:
 * LOG: Revision 7.5.2.7.2.3.4.2  2004/12/31 07:51:38  sbabu
 * LOG: MTP3 OAM Changes
 * LOG:
 * LOG: Revision 7.5.2.7.2.3.4.1  2004/12/17 03:57:44  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.5.2.7.2.3  2004/10/06 13:24:58  mmanikandan
 * LOG: Compiler limit in windows for braces.
 * LOG:
 * LOG: Revision 7.5.2.7.2.2  2004/08/25 10:41:19  kannanp
 * LOG: Get Global pegs T25 to T34 are removed .
 * LOG:
 * LOG: Revision 7.5.2.7.2.1  2004/08/10 12:14:46  kannanp
 * LOG: Changes for MTP3 pegs, alarms & MMLs - propagated from TCS.
 * LOG:
 * LOG: Revision 7.5.2.7  2003/12/08 11:25:26  kannanp
 * LOG: Fix bugs 596,598 wrong display of Timers,Add MMLs for clearing peg counts.
 * LOG:
 * LOG: Revision 7.5.2.6  2003/11/28 07:50:11  kannanp
 * LOG: Peg Fix patch from Current.
 * LOG:
 * LOG: Revision 7.5.2.5  2003/11/13 12:11:00  kannanp
 * LOG: MTP3 MML API.
 * LOG:
 * LOG: Revision 7.5.2.4  2003/03/26 06:32:09  randresol
 * LOG: Change Debug Console commands naming convention
 * LOG:
 * LOG: Revision 7.5.2.3  2003/03/17 11:48:41  akumar
 * LOG: Added ITU MML in PR_6.3 Branch
 * LOG:
 * LOG: Revision 7.5.2.2  2003/02/18 02:11:52  randresol
 * LOG: Enhance mtp3Shutdown command
 * LOG:
 * LOG: Revision 7.5.2.1  2003/02/14 07:29:22  randresol
 * LOG: Enhancement for Pegs and Alarms
 * LOG:
 * LOG: Revision 7.5  2003/02/13 10:35:23  ttipatre
 * LOG: New Interface for Pegs.
 * LOG:
 * LOG: Revision 7.4  2002/12/24 07:46:10  ttipatre
 * LOG: Link Level Pegs.
 * LOG:
 * LOG: Revision 7.3  2002/11/09 21:48:32  randresol
 * LOG: Add ROUTE Reader/Writer Lock for MTP3 Optimization
 * LOG:
 * LOG: Revision 7.2  2002/09/26 23:00:10  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:28  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.6  2002/08/16 22:07:08  mmiers
 * LOG: Include China variant.
 * LOG:
 * LOG: Revision 6.5  2002/07/15 14:44:08  ngoel
 * LOG: move TCAP Console function to itu-tcap
 * LOG:
 * LOG: Revision 6.4  2002/07/08 00:02:22  ngoel
 * LOG: move sccp console function to itu-sccp.c
 * LOG:
 * LOG: Revision 6.3  2002/06/18 20:56:16  mmiers
 * LOG: Add debug console hooks in preparation for MML
 * LOG:
 * LOG: Revision 6.2  2002/05/15 15:06:48  randresol
 * LOG: Integrate shared behaviors and timers with management interface
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:38  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.8  2002/01/31 22:56:17  mmiers
 * LOG: Correct dispatch entity
 * LOG:
 * LOG: Revision 5.7  2002/01/29 19:56:26  mmiers
 * LOG: warning removal
 * LOG:
 * LOG: Revision 5.6  2001/12/15 01:19:50  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.5  2001/12/11 23:49:52  mmiers
 * LOG: Get rid of FIXMEs.
 * LOG:
 * LOG: Revision 5.4  2001/12/06 22:39:05  mmiers
 * LOG: First cut of ITU MTP3.
 * LOG:
 * LOG: Revision 5.3  2001/11/09 20:19:55  mmiers
 * LOG: Don't force the vendor lib to be part of the engine.  Make into
 * LOG: DLL instead.
 * LOG:
 * LOG: Revision 5.2  2001/10/22 21:18:21  rsonak
 * LOG: Get cvs logs in the file
 * LOG:
 ****************************************************************************/

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#undef CCITT
#undef ANSI
#if !defined(PRC) && !defined(TTC)
#define CCITT
#endif

#include <its.h>
#include <engine.h>
#include <its_callback.h>
#include <its_mutex.h>
#include <its_route.h>
#include <its_transports.h>
#include <its_assertion.h>
#include <its_route_rwlock.h>

#include <dbc_serv.h>

#ident "$Id: itu-mgmt.c,v 9.7.30.2.8.1 2014/09/17 07:01:58 jsarvesh Exp $"

#if defined(PRC)
#include <china/snmm.h>
#include <china/sltm.h>
#include <china/mtp3.h>
#elif defined(TTC)
#include <japan/snmm.h>
#include <japan/sltm.h>
#include <japan/mtp3.h>
#else
#include <itu/snmm.h>
#include <itu/sltm.h>
#include <itu/mtp3.h>
#endif

#include "mtp3_intern.h"
#include "IwfErrorResp.h"

extern mtp3OmBuffer omBuf;
struct adj_sp_node *adjSpNodePtr;


/* Funtion Prototypes */
#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */
void MTP3_ResetOm_CCITT();
void MTP3_GetOm_CCITT(mtp3Om *);
#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

void MTP3_ResetOm_MML_CCITT();
void MTP3_GetOm_MML_CCITT(DBC_Server *);
void MTP3LinkOmDataInitialize(mtp3_link_stat_table *);
void MTP3LinksetOmDataInitialize(mtp3_linkset_stat_table *);

void DumpGlobalPegId(DBC_Server *dbc);
void DumpLinkPegId(DBC_Server *dbc);

void static NodeShutDown();

static ITS_INT DumpGlobalPegs(DBC_Server *dbc);
static ITS_INT DumpLinkPegs(SS7_LinkPtr ln, DBC_Server *dbc);
static ITS_INT DumpDPCPegs(SS7_Destination* dest, DBC_Server *dbc);

static int DumpRemotePointCodeData(ITS_POINTER data, void *in, void *out) ;
static int DumpLocalPointCodeData(ITS_POINTER data, void *in, void *out) ;

static int GetRemotePointCodeData(ITS_POINTER data, void *in, void *out);
static int GetLocalPointCodeData(ITS_POINTER data, void *in, void *out);



static ITS_CHAR *mtp3GPegStr[] =
{
     "PEG_MTP3_MSG_PAUSE",
     "PEG_MTP3_MSG_RESUME",
     "PEG_MTP3_MSG_STATUS",
     "PEG_MTP3_INITIALIZE",
     "PEG_MTP3_TERMINATE",
     "PEG_MTP3_MSG_RECEIVED_INERROR",
     "PEG_MTP3_CHANGEOVER",
     "PEG_MTP3_CHANGEBACK",
     "PEG_MTP3_SL_UNAVAILABLE",
     "PEG_MTP3_LINK_INHIBIT",
     "PEG_MTP3_LINK_UNINHIBIT",
     "PEG_MTP3_LINK_FORCE_UNINHIBIT",
     "PEG_MTP3_CONGESTION",
     "PEG_MTP3_SLS_UNAVAILABLE",
     "PEG_MTP3_TFC_RECEIVED",
     "PEG_MTP3_TFA_RECEIVED",
     "PEG_MTP3_ROUTESET_UNAVAILABLE",
     "PEG_MTP3_ADJECENT_SP_UNACCESIBLE",
     "PEG_MTP3_USERPART_ENABLE",
     "PEG_MTP3_USERPART_DISABLE",
     "PEG_MTP3_T1_EXPIRED",
     "PEG_MTP3_T2_EXPIRED",
     "PEG_MTP3_T3_EXPIRED",
     "PEG_MTP3_T4_EXPIRED",
     "PEG_MTP3_T5_EXPIRED",
     "PEG_MTP3_T6_EXPIRED",
     "PEG_MTP3_T7_EXPIRED",
     "PEG_MTP3_T8_EXPIRED",
     "PEG_MTP3_T9_EXPIRED",
     "PEG_MTP3_T10_EXPIRED",
     "PEG_MTP3_T11_EXPIRED",
     "PEG_MTP3_T12_EXPIRED",
     "PEG_MTP3_T13_EXPIRED",
     "PEG_MTP3_T14_EXPIRED",
     "PEG_MTP3_T15_EXPIRED",
     "PEG_MTP3_T16_EXPIRED",
     "PEG_MTP3_T17_EXPIRED",
     "PEG_MTP3_T18_EXPIRED",
     "PEG_MTP3_T19_EXPIRED",
     "PEG_MTP3_T20_EXPIRED",
     "PEG_MTP3_T21_EXPIRED",
     "PEG_MTP3_T22_EXPIRED",
     "PEG_MTP3_T23_EXPIRED",
     "PEG_MTP3_T24_EXPIRED",
     "PEG_MTP3_T25_EXPIRED",
     "PEG_MTP3_T26_EXPIRED",
     "PEG_MTP3_T27_EXPIRED",
     "PEG_MTP3_T28_EXPIRED",
     "PEG_MTP3_T29_EXPIRED",
     "PEG_MTP3_T30_EXPIRED",
     "PEG_MTP3_T31_EXPIRED",
     "PEG_MTP3_T32_EXPIRED",
     "PEG_MTP3_T33_EXPIRED",
     "PEG_MTP3_T34_EXPIRED",
      NULL
};

static ITS_CHAR *mtp3LPegStr[] =
{
      "PEG_MTP3_LINK_MSU_TX",
      "PEG_MTP3_LINK_MSU_RX",
      "PEG_MTP3_LINK_OCTETS_TX",
      "PEG_MTP3_LINK_OCTETS_RX",
      "PEG_MTP3_LINK_COO_TX",
      "PEG_MTP3_LINK_COO_RX",
      "PEG_MTP3_LINK_COA_TX",
      "PEG_MTP3_LINK_COA_RX" ,
      "PEG_MTP3_LINK_ECO_TX",
      "PEG_MTP3_LINK_ECO_RX",
      "PEG_MTP3_LINK_ECA_TX",
      "PEG_MTP3_LINK_ECA_RX",
      "PEG_MTP3_LINK_CBD_TX",
      "PEG_MTP3_LINK_CBD_RX",
      "PEG_MTP3_LINK_CBA_TX",
      "PEG_MTP3_LINK_CBA_RX",
      "PEG_MTP3_LINK_LIN_TX",
      "PEG_MTP3_LINK_LIN_RX",
      "PEG_MTP3_LINK_LIA_TX",
      "PEG_MTP3_LINK_LIA_RX",
      "PEG_MTP3_LINK_LUN_TX",
      "PEG_MTP3_LINK_LUN_RX",
      "PEG_MTP3_LINK_LUA_TX",
      "PEG_MTP3_LINK_LUA_RX",
      "PEG_MTP3_LINK_LID_TX",
      "PEG_MTP3_LINK_LID_RX",
      "PEG_MTP3_LINK_LFU_TX",
      "PEG_MTP3_LINK_LFU_RX",
      "PEG_MTP3_LINK_LLI_TX",
      "PEG_MTP3_LINK_LLI_RX",
      "PEG_MTP3_LINK_LRI_TX",
      "PEG_MTP3_LINK_LRI_RX",
      "PEG_MTP3_LINK_DLC_TX",
      "PEG_MTP3_LINK_DLC_RX",
      "PEG_MTP3_LINK_CSS_TX",
      "PEG_MTP3_LINK_CSS_RX",
      "PEG_MTP3_LINK_CNS_TX",
      "PEG_MTP3_LINK_CNS_RX",
      "PEG_MTP3_LINK_CNP_TX",
      "PEG_MTP3_LINK_CNP_RX",
      "PEG_MTP3_LINK_UPU_TX",
      "PEG_MTP3_LINK_UPU_RX",
      "PEG_MTP3_LINK_SLTM_TX",
      "PEG_MTP3_LINK_SLTM_RX",
      "PEG_MTP3_LINK_SLTA_TX",
      "PEG_MTP3_LINK_SLTA_RX",
       NULL
};

static ITS_CHAR *mtp3DPegStr[] =
{
      "PEG_MTP3_DPC_TFA_TX",
      "PEG_MTP3_DPC_TFA_RX",
      "PEG_MTP3_DPC_TFP_TX",
      "PEG_MTP3_DPC_TFP_RX",
      "PEG_MTP3_DPC_RST_TX",
      "PEG_MTP3_DPC_RST_RX",
      "PEG_MTP3_DPC_TFR_RX",
      "PEG_MTP3_DPC_TFC_TX" ,
      "PEG_MTP3_DPC_TFC_RX",
      "PEG_MTP3_DPC_SIF_TX",
      NULL
};


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
 * -----------------------------------------------------------------------------
 * Name      Date        Reference               Description
 * -----------------------------------------------------------------------------
 * snagesh   04-04-2005  ACC651-SDS-MTPL-1.0.02  Added handling of MGMT triggers
 *                       ID::D0010               for LPO feature
 *
 ****************************************************************************/
ITSSS7DLLAPI int
MGMT_Main_CCITT(MTP3_SubSystems src, MGMT_Triggers trigger,
                ITS_OCTET *sif, ITS_USHORT len,
                ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    int ret;

    MTP3_TRACE_ENTRY_CCITT(MTP3_MGMT, src, trigger, sif, len,
                          linkSet, linkCode);

    MTP3_DEBUG(("linkSet %d linkCode %d is present physically on this node\n", linkSet, linkCode));
    switch (trigger)
    {
    case MGMT_TRIGGER_NO_ROUTING_DATA:       /* from HMRT */
        break;

    case MGMT_TRIGGER_LINK_TEST_PASSED:      /* from SLTC */
        MTP3_DEBUG(("SLT passed for linkSet %d linkCode %d\n", linkSet, linkCode));
        break;

    case MGMT_TRIGGER_LINK_TEST_FAILED:      /* from SLTC */
        MTP3_DEBUG(("SLT failed for linkSet %d linkCode %d\n", linkSet, linkCode));
        break;

    case MGMT_TRIGGER_LINK_ACTIVATION_FAIL:  /* from LSAC */
    case MGMT_TRIGGER_INHIBIT_REQ_TIMEOUT:   /* from TLAC */
    case MGMT_TRIGGER_UNINHIBIT_REQ_TIMEOUT: /* from TLAC */    
    case MGMT_TRIGGER_INHIBIT_DENIED:        /* from TLAC */
    case MGMT_TRIGGER_LINK_INHIBITED:        /* from TLAC */
    case MGMT_TRIGGER_LINK_REMOTE_UNINHIBIT: /* from TLAC */
    case MGMT_TRIGGER_UNINHIBIT_IMPOSSIBLE:  /* from TLAC */
    case MGMT_TRIGGER_MSG_FOR_INVALID_DEST:          /* from HMRT */
        break;

    case MGMT_TRIGGER_RESTART:               /* from USER */
        if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
        {
            return (ITS_EBADMUTEX);
        }

        ret = TPRC_Main_CCITT(MTP3_USER,
                              STM_TRIGGER_RESTART_INDIC,
                              NULL, 0,
                              ITS_SS7_DEFAULT_LINK_SET,
                              ITS_SS7_DEFAULT_LINK_CODE);

        LINKSET_CommitLinkSet(LINKSET_FindLinkSet(linkSet));

        ROUTE_UnlockWrite(routeRWLock);
 
        return (ret);

    case MGMT_TRIGGER_INHIBIT_LINK:
        if (src != MTP3_STM_TLAC) /* to avoid getting into the recursive loop */
        {
            if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS) 
            {
                return (ITS_EBADMUTEX);
            }

            ret = TLAC_Main_CCITT(MTP3_MGMT,
                                  STM_TRIGGER_INHIBIT_LINK,
                                  NULL, 0,
                                  linkSet,
                                  linkCode);          

            LINKSET_CommitLinkSet(LINKSET_FindLinkSet(linkSet));
            ROUTE_UnlockWrite(routeRWLock);

            return (ret);
        }
        break;

    case MGMT_TRIGGER_UNINHIBIT_LINK:
        if (src != MTP3_STM_TLAC) /* to avoid getting into the recursive loop */
        {
            if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
            {
                return (ITS_EBADMUTEX);
            }

            ret = TLAC_Main_CCITT(MTP3_MGMT,
                                  STM_TRIGGER_UNINHIBIT_LINK,
                                  NULL, 0,
                                  linkSet,
                                  linkCode);

            LINKSET_CommitLinkSet(LINKSET_FindLinkSet(linkSet));
            ROUTE_UnlockWrite(routeRWLock);

            return (ret);
        }
        break;

    case MGMT_TRIGGER_DEACTIVATE_LINK_SET:
        if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS) 
        {
            return (ITS_EBADMUTEX);
        }

        ret = LLSC_Main_CCITT(MTP3_MGMT,
                              SLM_TRIGGER_DEACTIVATE_LINK_SET,
                              NULL, 0,
                              linkSet,
                              linkCode);

        LINKSET_CommitLinkSet(LINKSET_FindLinkSet(linkSet));
        ROUTE_UnlockWrite(routeRWLock);
        
        return (ret);

    case MGMT_TRIGGER_DEACTIVATE_LINK:

	MTP3_DEBUG(("Management trigger: Deactivate linkSet %d linkCode %d \n", linkSet, linkCode));

        if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
        {
            return (ITS_EBADMUTEX);
        }
        ret = LSAC_Main_CCITT(MTP3_MGMT,
                              SLM_TRIGGER_DEACTIVATE_LINK,
                              NULL, 0,
                              linkSet,
                              linkCode);
        
        LINKSET_CommitLinkSet(LINKSET_FindLinkSet(linkSet));
        ROUTE_UnlockWrite(routeRWLock);
        
        return (ret);

    case MGMT_TRIGGER_ACTIVATE_LINK:

	MTP3_DEBUG(("Management trigger: Activate linkSet %d linkCode %d \n", linkSet, linkCode));

        if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
        {
            return (ITS_EBADMUTEX);
        }

        ret = LSAC_Main_CCITT(MTP3_MGMT,
                              SLM_TRIGGER_ACTIVATE_LINK,
                              NULL, 0,
                              linkSet,
                              linkCode);
        
        LINKSET_CommitLinkSet(LINKSET_FindLinkSet(linkSet));
        ROUTE_UnlockWrite(routeRWLock);
        
        return (ret);

    case MGMT_TRIGGER_ACTIVATE_LINK_SET:
        if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
        {
            return (ITS_EBADMUTEX);
        }

        ret = LLSC_Main_CCITT(MTP3_MGMT,
                              SLM_TRIGGER_ACTIVATE_LINK_SET,
                              NULL, 0,
                              linkSet,
                              linkCode);

        LINKSET_CommitLinkSet(LINKSET_FindLinkSet(linkSet));
        ROUTE_UnlockWrite(routeRWLock);
        
        return (ret);

    case MGMT_TRIGGER_LP_OUTAGE:
        if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
        {
            return (ITS_EBADMUTEX);
        }

        ret = LSAC_Main_CCITT(MTP3_MGMT,
                             SLM_TRIGGER_LP_OUTAGE,
                             NULL, 0,
                             linkSet,
                             linkCode);

        LINKSET_CommitLinkSet(LINKSET_FindLinkSet(linkSet));
        ROUTE_UnlockWrite(routeRWLock);

        return (ret);

    case MGMT_TRIGGER_LP_RECOVERD:
        if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
        {
            return (ITS_EBADMUTEX);
        }

        ret = LSAC_Main_CCITT(MTP3_MGMT,
                             SLM_TRIGGER_LP_RECOVERD,
                             NULL, 0,
                             linkSet,
                             linkCode);

        LINKSET_CommitLinkSet(LINKSET_FindLinkSet(linkSet));
        ROUTE_UnlockWrite(routeRWLock);

        return (ret);

    default:
        MTP3_DEBUG(("Unknown mgmt trigger\n"));
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
void static
ShutDownNode(DBC_Server *dbc)
{
    TRANSPORT_Manager *tm;
    TRANSPORT_Control *tr;
    ITS_UINT mask;
    char buf[ITS_PATH_MAX];

    tm = TRANSPORT_GetManager();

    if (RWLOCK_LockShared(&tm->transportGate) != ITS_SUCCESS)
    {
         return;
    }

    for ( tr = tm->listHead;
          tr != NULL; tr = TRANSPORT_HMI_NEXT(tr))
    {
        mask = TRANSPORT_MASK(tr);

        if ((mask & ITS_MTP2_CCITT) == ITS_MTP2_CCITT)
        {
            SS7_LinkPtr lp;

            for (lp = TRANSPORT_SS7_INFO(tr).linkInfo;
                 lp != NULL; lp = lp->next)
            {
               sprintf(buf, "Deactivating ls:%d lc:%d\n",
                       lp->linkSet->linkSet, lp->linkCode);

               DBC_AppendText(dbc, buf);

               MGMT_Main_CCITT(MTP3_USER,
                               MGMT_TRIGGER_DEACTIVATE_LINK,
                               NULL, 0,
                               lp->linkSet->linkSet, lp->linkCode);
            }

        }
    }

    RWLOCK_UnlockShared(&tm->transportGate);
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
 * -----------------------------------------------------------------------------
 * Name      Date        Reference               Description
 * -----------------------------------------------------------------------------
 * snagesh   04-04-2005  ACC651-SDS-MTPL-1.0.02  Added handling of the MMLs
 *                       ID::D0010               mi_lpo & mi_lpr for LPO feature
 *
 * adutta    05-06-2005  Personeta Enhancements  Added handling of the MMLs
 *                                               for route pegs 
 *
 * skatta    11-04-2007                          Family check is removed for
 *                                               mi_shutdown  MML command
 ****************************************************************************/
void
MTP3_Console_CCITT(DBC_Server *dbc, const char *cmdLine)
{    
    char buf[ITS_PATH_MAX];
    int linkSet = 0, linkCode = 0, ret = 0;
    SS7_LinkPtr ln; 
    SS7_LinkSetPtr ls;
    ITS_UINT i;

    ITS_C_ASSERT(dbc != NULL);

    if (DBC_Cmd(dbc, "mi_get_gen_cfg", "MTP3 Get General Config", "", ""))
    {
        MTP3GeneralCfg *cfg = 0;
        cfg =  MTP3_GetGeneralCfg_CCITT();
        sprintf(buf, "\n*********** MTP3 General Config *************\n");
        DBC_AppendText(dbc, buf);

        i = cfg->alarmLevel;

        switch(i)
        {
            case ALARM_LVL_CRIT :
                sprintf(buf, "\n    Alarm Level:  CRITICAL\n");
            break;

            case ALARM_LVL_MAJOR :
                sprintf(buf, "\n    Alarm Level:  MAJOR\n");
            break;

            case ALARM_LVL_MINOR :
                sprintf(buf, "\n    Alarm Level:  MINOR\n");
            break;

            case ALARM_LVL_INFO :
                sprintf(buf, "\n    Alarm Level:  INFO\n");
            break;

            case ALARM_LVL_OFF :
                sprintf(buf, "\n    Alarm Level:  OFF\n");
            break;

            default :
                sprintf(buf, "\n    Alarm Level Not Set\n");
            break;
        }

        DBC_AppendText(dbc, buf);
        strcpy(buf, "\n    MTP3 Trace -\n");
        DBC_AppendText(dbc, buf);

        if ( cfg->traceOn)
        {
           if (TRACE_IsLevelOn(MTP3_CCITT_TraceData,
                                    MTP3_TRACE_DEBUG))
           {
               strcpy(buf, "        Debug     = ");
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_DEBUG,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_DEBUG,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_DEBUG,
                                      2))
               {
                    strcat(buf, " syslog");
               }
           }
           else
           {
               strcpy(buf, "        Debug     = null");
           }
           strcat(buf, "\n");
           DBC_AppendText(dbc, buf);

           if (TRACE_IsLevelOn(MTP3_CCITT_TraceData,
                                    MTP3_TRACE_ABORT))
           {
               strcpy(buf, "        Critical  = ");
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_ABORT,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_ABORT,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_ABORT,
                                      2))
               {
                    strcat(buf, " syslog");
               }
           }
           else
           {
               strcpy(buf, "        Critical  = null");
           }
           strcat(buf, "\n");
           DBC_AppendText(dbc, buf);

           if (TRACE_IsLevelOn(MTP3_CCITT_TraceData,
                                    MTP3_TRACE_WARNING))
           {
               strcpy(buf, "        Warning   = ");
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_WARNING,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_WARNING,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_WARNING,
                                      2))
               {
                    strcat(buf, " syslog");
               } 
           }
           else
           {
               strcpy(buf, "        Warning   = null");
           }

           strcat(buf, "\n");
           DBC_AppendText(dbc, buf);

           if (TRACE_IsLevelOn(MTP3_CCITT_TraceData,
                                    MTP3_TRACE_ERROR))
           {
               strcpy(buf, "        Error     = ");
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_ERROR,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_ERROR,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_ERROR,
                                      2))
               {
                    strcat(buf, " syslog");
               }
           }
           else
           {
               strcpy(buf, "        Error     = null");
           }
           strcat(buf, "\n");
           DBC_AppendText(dbc, buf);

           if (TRACE_IsLevelOn(MTP3_CCITT_TraceData,
                                    MTP3_TRACE_EVENT))
           {
               strcpy(buf, "        Event     = ");
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_EVENT,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_EVENT,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_EVENT,
                                      2))
               {
                    strcat(buf, " syslog");
               } 
           }
           else
           {
               strcpy(buf, "        Event     = null");
           }
           strcat(buf, "\n");
           DBC_AppendText(dbc, buf);
       }
       else
       {
           strcpy(buf, "        Debug     = null\n");
           DBC_AppendText(dbc, buf);
           strcpy(buf, "        Critical  = null\n");
           DBC_AppendText(dbc, buf);
           strcpy(buf, "        Warning   = null\n");
           DBC_AppendText(dbc, buf);
           strcpy(buf, "        Error     = null\n");
           DBC_AppendText(dbc, buf);
           strcpy(buf, "        Event     = null\n");
           DBC_AppendText(dbc, buf);
       }
        sprintf(buf, "\n*********** End of MTP3 General Config ***********\n");
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_set_gen_cfg", "MTP3 Set General Config",
                     "<alarm level> <Trace Type> <traceOutput> <On/Off>",""))
    {
        MTP3GeneralCfg cfg;
        char alarmLevel[ITS_PATH_MAX];
        char traceOn[ITS_PATH_MAX];
        char traceType[ITS_PATH_MAX];
        char traceOutput[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s %s", buf, alarmLevel, traceType,
                     traceOutput, traceOn);

        if (ret != 5)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: mi_set_gen_cfg <alarmlevel> <tracetype>" 
                         " <trOutput> <On/Off>\n"
                          "See help to see possible values\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(alarmLevel, "CRITICAL") != NULL ||
            strstr(alarmLevel, "critical") != NULL)
        {
            cfg.alarmLevel = ALARM_LVL_CRIT;
        }
        else if (strstr(alarmLevel, "MAJOR") ||
                strstr(alarmLevel, "major") )
        {
            cfg.alarmLevel = ALARM_LVL_MAJOR;
        }
        else if (strstr(alarmLevel, "MINOR") ||
                strstr(alarmLevel, "minor"))
        {
            cfg.alarmLevel = ALARM_LVL_MINOR;
        }
        else if (strstr(alarmLevel, "INFO") ||
                 strstr(alarmLevel, "info"))
        {
            cfg.alarmLevel = ALARM_LVL_INFO;
        }
        else if (strstr(alarmLevel, "OFF") ||
                strstr(alarmLevel, "off") )
        {
            cfg.alarmLevel = ALARM_LVL_OFF;
        }
        else
        {
            sprintf(buf, "\nInvalid Alarm Level\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(traceOn, "ON") || strstr(traceOn, "on"))
        {
            cfg.traceOn = ITS_TRUE;
        }
        else if (strstr(traceOn, "OFF") || strstr(traceOn, "off"))
        {
            cfg.traceOn = ITS_FALSE;
        }
        else
        {
            sprintf(buf, "\nInvalid Trace Level\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(traceType, "CRITICAL") || strstr(traceType, "critical"))
        {
            strcpy(cfg.traceType, MTP3_CRITICAL_STRING);
        }
        else if (strstr(traceType, "DEBUG") || strstr(traceType, "debug"))
        {
            strcpy(cfg.traceType, MTP3_DEBUG_STRING);
        }
        else if (strstr(traceType, "WARNING") || strstr(traceType, "warning"))
        {
            strcpy(cfg.traceType, MTP3_WARNING_STRING);
        }
        else if (strstr(traceType, "ERROR") || strstr(traceType, "error"))
        {
            strcpy(cfg.traceType, MTP3_ERROR_STRING);
        }
        else if (strstr(traceType, "EVENT") || strstr(traceType, "event"))
        {
            strcpy(cfg.traceType, MTP3_EVENT_STRING);
        }
        else if (strstr(traceType, "ALL") || strstr(traceType, "all"))
        {
            strcpy(cfg.traceType, "all");
        }
        else
        {
            sprintf(buf, "\nInvalid Trace Type\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(traceOutput, "STDOUT") || strstr(traceOutput, "stdout"))
        {
            strcpy(cfg.traceOutput, MTP3_STDOUT_STRING);
        }
        else if (strstr(traceOutput, "FILE") || strstr(traceOutput, "file"))
        {
            strcpy(cfg.traceOutput, MTP3_FILE_STRING);
        }
        else if (strstr(traceOutput, "SYSLOG") || strstr(traceOutput, "syslog"))
        {
            strcpy(cfg.traceOutput, MTP3_SYSLOG_STRING);
        }
        else
        {
            sprintf(buf, "\nInvalid Trace Output\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret =  MTP3_SetGeneralCfg_CCITT(&cfg);
        if (ret != ITS_SUCCESS)
        {
            return;
        }

       sprintf(buf, "\n*********** MTP3 General Config Set*************\n");
       DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "mi_in_link", "Inhibit Link", "<linkset> <linkcode>",  ""))
    {
        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: mi_in_link <linkset> <linkcode>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
        {
            sprintf(buf, "\n***Link %d on link set %d is not configured***\n",
                           linkSet, linkCode);
            DBC_AppendText(dbc, buf);
            return;
        }

        ls = LINKSET_FindLinkSet((ITS_OCTET) linkSet);
        if (ls->family != FAMILY_ITU)
        {
            sprintf(buf, "\n***Mismatch in the linkSet Family***\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret = MGMT_Main_CCITT(MTP3_USER,
                              MGMT_TRIGGER_INHIBIT_LINK,
                              NULL, 0,
                              (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);

        if (ret != ITS_SUCCESS)
        {
            sprintf(buf,"\n***Link  %d:%d inhibition failed: reason %s\n***\n",
                    linkSet, linkCode, ITS_GetErrorText(ret));
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "\n***Link %d:%d Inhibition initiated*** \n", linkSet, linkCode);
        DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "mi_unin_link", "Uninhibit Link", 
             "<linkset> <linkcode>", ""))
    {
        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n" 
                         "Usage: mi_unin_link <linkset> <linkcode>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
        {
            sprintf(buf, "\n***Link %d on link set %d is not configured***\n",
                           linkSet, linkCode);
            DBC_AppendText(dbc, buf);
            return;
        }

        ls = LINKSET_FindLinkSet((ITS_OCTET) linkSet);
        if (ls->family != FAMILY_ITU)
        {
            sprintf(buf, "\n***Mismatch in the linkSet Family***\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret = MGMT_Main_CCITT(MTP3_USER,
                              MGMT_TRIGGER_UNINHIBIT_LINK,
                              NULL, 0,
                              (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);

        if (ret != ITS_SUCCESS)
        {
            sprintf(buf,"\n***Link  %d:%d uninhibition failed: reason %s\n***\n",
                    linkSet, linkCode, ITS_GetErrorText(ret));
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "\n***Link %d:%d Uninhibition initiated***\n", linkSet, linkCode);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_deact_ls", "Deactivate Link Set", "<linkset>", ""))
    {
        ret = sscanf(cmdLine, "%s %d", buf, &linkSet);
        if (ret != 2)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n" 
                         "Usage: mi_deact_ls <linkset> \n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((ls = LINKSET_FindLinkSet((ITS_OCTET)linkSet)) == NULL)
        {
            sprintf(buf, "\n***Linkset %d not configured***\n", linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }


        ls = LINKSET_FindLinkSet((ITS_OCTET) linkSet);
        if (ls->family != FAMILY_ITU)
        {
            sprintf(buf, "\n***Mismatch in the linkSet Family***\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret = MGMT_Main_CCITT(MTP3_USER,
                              MGMT_TRIGGER_DEACTIVATE_LINK_SET,
                              NULL, 0,
                              (ITS_OCTET)linkSet, ITS_SS7_DEFAULT_LINK_CODE);

        if (ret != ITS_SUCCESS)
        {
            sprintf(buf,"\n***Linkset %d deactivation failed: reason %s***\n",
                    linkSet, ITS_GetErrorText(ret));
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "\n***Linkset %d Deactivation initiated***\n", linkSet);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_act_ls", "Activate Link Set", "<linkset>", ""))
    {
        ret = sscanf(cmdLine, "%s %d", buf, &linkSet);
        if (ret != 2)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n" 
                         "Usage: mi_act_ls <linkset> \n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((ls = LINKSET_FindLinkSet((ITS_OCTET)linkSet)) == NULL)
        {
            sprintf(buf, "\n***Linkset %d not configured***\n", linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }

        ls = LINKSET_FindLinkSet((ITS_OCTET) linkSet);
        if (ls->family != FAMILY_ITU)
        {
            sprintf(buf, "\n***Mismatch in the linkSet Family***\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret= MGMT_Main_CCITT(MTP3_USER,
                             MGMT_TRIGGER_ACTIVATE_LINK_SET,
                             NULL, 0,
                             (ITS_OCTET)linkSet, ITS_SS7_DEFAULT_LINK_CODE);

        if (ret != ITS_SUCCESS)
        {
            sprintf(buf,"\n***Linkset %d activation failed:reason %s***\n",
                    linkSet, ITS_GetErrorText(ret));
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "\n***Linkset %d Activation initiated***\n", linkSet);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_deact_link", "Deactivate Link", 
             "<linkset> <linkcode>", ""))
    {
        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n" 
                         "Usage: mi_deact_link <linkset> <linkcode> \n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
        {
            sprintf(buf, "\n***Link %d on link set %d is not configured***\n",
                           linkCode, linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }

        ls = LINKSET_FindLinkSet((ITS_OCTET) linkSet);
        if (ls->family != FAMILY_ITU)
        {
            sprintf(buf, "\n***Mismatch in the linkSet Family***\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret= MGMT_Main_CCITT(MTP3_USER,
                             MGMT_TRIGGER_DEACTIVATE_LINK,
                             NULL, 0,
                             (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);

        if (ret != ITS_SUCCESS)
        {
            sprintf(buf,"\n***Link %d:%d deactivation failed:reason %s***\n",
                    linkSet, linkCode, ITS_GetErrorText(ret));
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "\n***Link %d:%d Deactivation initiated***\n", linkSet, linkCode);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_act_link", "Activate Link", 
             "<linkset> <linkcode>", ""))
    {
        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n" 
                         "Usage: mi_act_link <linkset> <linkcode> \n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
        {
            sprintf(buf, "\n***Link %d on link set %d is not configured***\n",
                           linkCode, linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }

        ls = LINKSET_FindLinkSet((ITS_OCTET) linkSet);
        if (ls->family != FAMILY_ITU)
        {
            sprintf(buf, "\n***Mismatch in the linkSet Family***\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret= MGMT_Main_CCITT(MTP3_USER,
                             MGMT_TRIGGER_ACTIVATE_LINK,
                             NULL, 0,
                             (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);

        if (ret != ITS_SUCCESS)
        {
            sprintf(buf,"\n***Linkset %d activation failed: reason %s***\n",
                    linkSet, ITS_GetErrorText(ret));
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "\n***Link %d:%d Activation initiated***\n", linkSet, linkCode);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_start", "Start MTP3", "", ""))
    {
        sprintf(buf, "\n*********** Starting MTP3 **************\n");
        DBC_AppendText(dbc, buf);

        MGMT_Main_CCITT(MTP3_USER,
                        MGMT_TRIGGER_RESTART,
                        NULL, 0,
                        ITS_SS7_DEFAULT_LINK_SET,
                        ITS_SS7_DEFAULT_LINK_CODE);

    }
    else if (DBC_Cmd(dbc, "mi_get_ls", "Dump Link Sets", "", ""))
    {
        char *dump = NULL;
        SS7_Family family = FAMILY_ITU;

        ROUTE_LockForWrite(routeRWLock);

        LINKSET_DumpLinkSetHashtable(&dump, family);

        ROUTE_UnlockWrite(routeRWLock);

        if (dump)
        {
            DBC_AppendText(dbc, dump);
        }
    }
    else if (DBC_Cmd(dbc, "mi_get_ls_s", "Dump Link Sets (simple)", "<-c>", ""))
    {
        char *dump = NULL;
        SS7_Family family = FAMILY_ITU;
	ITS_BOOLEAN concise = ITS_FALSE;
	char conciseStr[10] = "err";

        sscanf(cmdLine, "%s %s", buf, conciseStr);

        if (strstr(conciseStr, "-c") != NULL)
	{
	    concise = ITS_TRUE;
	}

        ROUTE_LockForWrite(routeRWLock);

        LINKSET_DumpLinkSetHashtable_simple(&dump, family, concise);

        ROUTE_UnlockWrite(routeRWLock);

        if (dump)
        {
            DBC_AppendText(dbc, dump);
        }
    }
    else if (DBC_Cmd(dbc, "mi_get_sls_map", "Show SLS Mapping", "<pointCode> <sio>", ""))
    {
	unsigned char sls, sls1,new_sls;
	unsigned char link_flag    = 0xF0;
	unsigned char linkset_flag = 0x0F;
	int link, linkset;
	MTP3_HEADER mtp3hdr;
	ROUTE_MatchInfo rinfo;
	ITS_UINT pointCode = 1025;
	ITS_OCTET sio = 131;
	ITS_OCTET ni = 0;

#if 0	
        ret = sscanf(cmdLine, "%s %u %u", buf, &pointCode, &sio);
        if (ret != 3)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n" 
                         "Usage: mi_get_sls_map <pointCode> <sio> \n");
            DBC_AppendText(dbc, buf);
            return;
        }
#endif

	ni = sio & MTP3_NIC_MASK;
	sprintf(buf, "\n Command: %s pointCode: %u, sio: %u, ni: %u\n", buf, pointCode, sio, ni); 
	DBC_AppendText(dbc, buf);

	for (sls  = 0; sls < 127; sls++) 
	{    
	      MTP3_RL_SET_SLS_CCITT(mtp3hdr.label,sls); 
	      sls1 = MTP3_RL_GET_SLS_CCITT(mtp3hdr.label);
	     
	      new_sls = sls1;
	      new_sls = (new_sls << 1) | ((new_sls >> 3) & 1);
	      new_sls += 1;

	      link =   (new_sls & link_flag) >> 4;

	      linkset = ((int)(new_sls & linkset_flag))/2 +1; 

	      if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pointCode,
					      DONT_CARE, ROUTE_DPC_NI,
					      FAMILY_ITU,
					      ni,   
					      ITS_SS7_DEFAULT_LINK_SET,
					      ITS_SS7_DEFAULT_LINK_CODE,
					      ITS_SS7_DEFAULT_PRI,
					      new_sls) != ITS_SUCCESS)
	      {    
		 sprintf(buf, "ROUTE_ParseRouteMatchInfoArgs returned error\n");
	         DBC_AppendText(dbc, buf);
                 return;

	      }    

	      ROUTE_SelectRouteContextInfo(&rinfo);
	      sprintf(buf, " [sls %4u 0x%4x] [%4u 0x%4x][new_sls %4u 0x%4x] [LS %4d LC %4d] [linkset %u link %u] \n",
		      sls,sls,sls1,sls1,new_sls,new_sls,rinfo.linkSet,rinfo.linkCode, linkset, link);
	      DBC_AppendText(dbc, buf);
	}    

    }
 
    else if (DBC_Cmd(dbc, "mi_set_link_attrib", "Set Link Attribute <linkset> <link> <attr_type> <attr value>", "", ""))
    {
	int attrib_type  = 0;
	int attrib_value = 0;
	int old_attrib_value = 0;
	int updated_attrib_value = 0;
        SS7_Link  newlink;

        ret = sscanf(cmdLine, "%s %d %d %d %d", buf, &linkSet, &linkCode, &attrib_type, &attrib_value);
        if (ret != 5)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n" 
                         "Usage: mi_set_link_attrib <linkset> <link> <attr_type> <attr value> \n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "\nAttribute type 1 - dsmNodeId *******\n"); 
            DBC_AppendText(dbc, buf);
            sprintf(buf, "\nAttribute type 2 - id (Transport Instance) *******\n"); 
            DBC_AppendText(dbc, buf);
            return;
        } 

        ls = LINKSET_FindLinkSet((ITS_OCTET) linkSet);
        if (ls == NULL)
        {
            sprintf(buf, "\n***Linkset %d is not configured***\n",
                           linkSet);
            DBC_AppendText(dbc, buf);
            return ;
        }

        if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
        {
            sprintf(buf, "\n***Link %d on link set %d is not configured***\n",
                           linkCode, linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }
        if(attrib_type == 1)
	{

	    old_attrib_value = ln->dsmNodeId;
	    ln->dsmNodeId = attrib_value;
	    LINK_CommitLink(ln);
	    updated_attrib_value = ln->dsmNodeId;
	}
	else if(attrib_type == 2)
	{
#if 0
	    ITS_USHORT instance = attrib_value;

            tc = TRANSPORT_FindTransport(instance);
            if (tc == NULL)
            {
                sprintf(buf, "\nTransport %d not found\n",attrib_value);
                DBC_AppendText(dbc, buf);
                return ;
            }
#endif
	    old_attrib_value = ln->id;
	    if (old_attrib_value == attrib_value) 
	    {
		sprintf(buf, "\nLink %d on link set %d already has the trasnport id equal "
			"to what you have specified\n", linkCode, linkSet);
		DBC_AppendText(dbc, buf);
                return;
	    }

            newlink = *ln;

	    ret = LINK_RemLink(linkSet,ln);
	    if (ret != ITS_SUCCESS)
	    {    
		sprintf(buf, "Failed to delete link %d in LinkSet %d\n", 
				 linkCode, linkSet);
		DBC_AppendText(dbc, buf);
		return; 
	    }    
 

            newlink.id = attrib_value ;  

	    ret = LINK_AddLink(linkSet, &newlink);
	    if (ret != ITS_SUCCESS)
	    {   
		sprintf(buf, "Failed to add link %d in LinkSet %d\n",
			linkCode,linkSet);
		DBC_AppendText(dbc, buf);
		return;
	    }

	    ln = LINK_FindLink((ITS_OCTET) linkSet, (ITS_OCTET) linkCode);
	    if(ln == NULL)
	    {   
		sprintf(buf, "Link not found after addition. "
			"Linkset %d LinkCode %d",linkSet,linkCode);
		return;
	    }

	    updated_attrib_value = ln->id;
            //LINK_AddLinkInfoToTransport(tc, ln);
	    
	}

        sprintf(buf, "\n*** (Linkset)%d:(Link)%d Attribute type (%d )updated. Old value: %d  New value %d ***\n", 
		linkSet, linkCode, attrib_type, old_attrib_value, updated_attrib_value);
        DBC_AppendText(dbc, buf);
 	
    }
 
    else if (DBC_Cmd(dbc, "mi_sync_ls", "Sync Linksets", "", ""))
    {
        char *dump = "Sync Linksets DONE";
        SS7_Family family = FAMILY_ITU;

        ROUTE_LockForWrite(routeRWLock);

        LINKSET_DumpLinkSetHashtable(&dump, family);

        ROUTE_UnlockWrite(routeRWLock);

        if (dump)
        {
            DBC_AppendText(dbc, dump);
        }
    }
#if 0
    else if (DBC_Cmd(dbc, "mi_get_rt", "Dump Routes Info", "<>", "<>"))
    {
        char *dump = NULL;

        ROUTE_LockForWrite(routeRWLock);

        ROUTE_DumpSS7ToIdHashtable(&dump);

        ROUTE_UnlockWrite(routeRWLock);

        if (dump)
        {
            DBC_AppendText(dbc, dump);
        free(dump);
        }

    }
#endif
    else if (DBC_Cmd(dbc, "mi_get_link", "get Link Status", 
             "<linkset> <linkcode>", ""))
    {
        char *dump = NULL;

        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);

        if (ret != 3)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: mi_get_link <linkset> <linkcode>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
        {
            sprintf(buf, "\n***Link %d on link set %d is not configured***\n",
                           linkSet, linkCode);
            DBC_AppendText(dbc, buf);
            return;
        }

        ls = LINKSET_FindLinkSet((ITS_OCTET) linkSet);
        if (ls->family != FAMILY_ITU)
        {
            sprintf(buf, "\n***Mismatch in the linkSet Family***\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ROUTE_LockForWrite(routeRWLock);

        LINK_DumpLinkInfo(&dump, (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);

        ROUTE_UnlockWrite(routeRWLock);

        if (dump)
        {
            DBC_AppendText(dbc, dump);
        }

    }
#ifdef MTP3_EVENT_PROCESSING_RATE_CALCULATION_ENABLE
    else if (DBC_Cmd(dbc, "mi_epr", "Enable/Disable MTP3 Thread's Event Processing Rate Calculation", 
             "enable <event burst>/disable", ""))
    {
	char enableDisable[ITS_PATH_MAX];
	ITS_BOOLEAN enableDisableVal = ITS_FALSE;
        ITS_UINT event_burst = DEFAULT_MTP3_EPR_EVENT_BURST;

        ret = sscanf(cmdLine, "%s %s %d", buf, enableDisable, &event_burst);
        if (ret != 3)
        {
             sprintf(buf,  "\n**** Invalid Command Arguments *******\n"
                           "Usage: mi_epr <enable <event burst>>/disable\n"); 
             DBC_AppendText(dbc, buf);
             return;
        }
        if((strncmp(enableDisable, "enable", 6) == 0)|| (strncmp(enableDisable, "ENABLE", 6) == 0))
	{
	    if ((event_burst < 1) || (event_burst >  MAX_MTP3_EPR_EVENT_BURST)) 
	    {
		 sprintf(buf,  "\n EPR event burst has to be in the range [1, %d]\n",MAX_MTP3_EPR_EVENT_BURST); 
		 DBC_AppendText(dbc, buf);
		 return;
	    }
	    enableDisableVal = ITS_TRUE;
            sprintf(buf,  "\n**** Calculation for MTP3 Thread's event processing rate enabled . Event burst: %u*******\n",
		    event_burst); 
	    DBC_AppendText(dbc, buf);
	} 
	else 
	{
            sprintf(buf,  "\n**** Calculation for MTP3 Thread's event processing rate disabled *******\n"); 
	    DBC_AppendText(dbc, buf);
	}

	SetMTP3EventProcessingRateCalculation(enableDisableVal, event_burst);
    }
#endif
    else if (DBC_Cmd(dbc, "mi_get_gen_peg", "Get MTP3 General Pegs", 
             "<Peg Id>", ""))
    {
        char pgName[ITS_PATH_MAX];
        ITS_UINT value;
        ITS_INT pgNum;

        ret = sscanf(cmdLine, "%s %s", buf, pgName);
        if (ret != 2)
        {
             sprintf(buf,  "\n**** Invalid Command Arguments *******\n"
                           "Usage: mi_get_gen_peg [<Peg Id> or <ALL/all>]\n"); 
             DBC_AppendText(dbc, buf);
             return;
        }

        if((strncmp(pgName, "ALL", 3) == 0)||
           (strncmp(pgName, "all", 3) == 0)||
           (atoi(pgName) == ALL_MTP3_PEGS))
        {
            /* Invoke function MTP3_GetOm_MML_CCITT() */
            MTP3_GetOm_MML_CCITT(dbc);
            DumpGlobalPegs(dbc);
            return;
        }
        else
        {
           if(!isdigit((int)pgName[0]))
           {
              sprintf(buf, "\n**** Unrecognized Peg *****\n");
              DBC_AppendText(dbc, buf);
              return;
           }
        }
         
        pgNum = atoi(pgName); 
         
        if (pgNum >= PEG_MTP3_NUM_PEGS_CCITT)
        {
            sprintf(buf, "\n   **** Invalid Peg Id *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "Getting the Peg for %s Now\n", mtp3GPegStr[pgNum]);
        DBC_AppendText(dbc, buf);

        value = PEG_GetPeg(CCITT_MTP3_Pegs, pgNum);

        sprintf(buf, "\n   value is %d\n", value);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_get_link_peg", "Get Link Level Pegs", 
             "<linkset> <linkcode> <Peg Id>", ""))
    {
        char pgName[ITS_PATH_MAX];
        ITS_UINT value;
        ITS_INT pgNum;

        ret = sscanf(cmdLine, "%s %d %d %s", buf, &linkSet, &linkCode, pgName);
        if (ret != 4)
        {
            sprintf(buf,  "\n**** Invalid Command Arguments *******\n"
                          "Usage: mi_get_link_peg <linkset> <linkcode> [<Peg Id> or <ALL/all>]\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
        {
            sprintf(buf, "\n***Link %d on link set %d is not configured***\n",
                           linkSet, linkCode);
            DBC_AppendText(dbc, buf);
            return;
        }

        if((strncmp(pgName, "ALL", 3) == 0) ||
           (strncmp(pgName, "all", 3) == 0)||
           (atoi(pgName) == ALL_MTP3_PEGS))
        {
           DumpLinkPegs(ln, dbc);
           return;
        }
        else
        {
           if(!isdigit((int)pgName[0]))
           {
              sprintf(buf, "\n**** Unrecognized Peg *****\n");
              DBC_AppendText(dbc, buf);
              return;
           }
        }

        pgNum = atoi(pgName);

        if (pgNum >= PEG_MTP3_NUM_LINK_PEGS)
        {
            sprintf(buf, "\n   **** Invalid Peg Id *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "Getting the Peg for %s Now\n",mtp3LPegStr[pgNum]);
        DBC_AppendText(dbc, buf);

        value = PEG_GetPeg(&ln->MTP3_LINK_PEGS,pgNum);

        sprintf(buf, "\n   value is %d\n", value);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_get_route_peg", "Get Route Level Pegs",
             "<dpc> <ni> <Peg Id>", ""))
    {
        char pgName[ITS_PATH_MAX];
        SS7_Destination* dest;
        ITS_UINT value;
        ITS_INT pgNum;
        ITS_UINT dpc;
        ITS_UINT ni;

        ret = sscanf(cmdLine, "%s %d %d %s", buf, &dpc, &ni, pgName);
        if (ret != 4)
        {
            sprintf(buf,  "\n**** Invalid Command Arguments *******\n" \
                          "Usage: mi_get_dpc_peg <dpc> <ni> \
                                           [<Peg Id> or <ALL/all>]\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((dest = ROUTE_FindDestination(dpc, ni, FAMILY_ITU)) == NULL)
        {
            sprintf(buf, "\n*** DPC %d NI %d not configured ***\n", dpc, ni);
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((*dest->entries)->basic.type == LOCAL_ROUTE)
        {
            sprintf(buf, "\n*** LPC %d Local point code entered  ***\n", dpc);
            DBC_AppendText(dbc, buf);
            return;
        }

        if((strncmp(pgName, "ALL", 3) == 0) ||
           (strncmp(pgName, "all", 3) == 0)||
           (atoi(pgName) == ALL_MTP3_PEGS))
        {
           DumpDPCPegs(dest, dbc);
           return;
        }
        else
        {
           if(!isdigit((int)pgName[0]))
           {
              sprintf(buf, "\n**** Unrecognized Peg *****\n");
              DBC_AppendText(dbc, buf);
              return;
           }
        }

        pgNum = atoi(pgName);

        if (pgNum > PEG_MTP3_NUM_DPC_PEGS)
        {
            sprintf(buf, "\n   **** Invalid Peg Id *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "Getting the Peg for %s Now\n",mtp3DPegStr[pgNum]);
        DBC_AppendText(dbc, buf);

        value = PEG_GetPeg(&dest->MTP3_DPC_PEGS,pgNum);

        sprintf(buf, "\n   value is %d\n", value);
        DBC_AppendText(dbc, buf);
    }

#if 0
    else if (DBC_Cmd(dbc, "mi_get_gen_pegid", "Show all general peg IDs", "", ""))
    {
        DumpGlobalPegId(dbc);
    }
    else if (DBC_Cmd(dbc, "mi_get_link_pegid", "Show all link level peg IDs", "", ""))
    {
        DumpLinkPegId(dbc);
    }
#endif

    else if (DBC_Cmd(dbc, "mi_clr_gen_peg", "MTP3 Reset a particular gen Peg",
                          "[<Pegid> (or) <ALL/all>]",""))
    {
        char pegType[ITS_PATH_MAX];
        ITS_INT pgNum; 

        ret = sscanf(cmdLine, "%s %s", buf, pegType);
        if (ret != 2)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: mi_clr_gen_peg [<Pegid> (or) <ALL/all>]\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if((strncmp(pegType, "ALL", 3) == 0) ||
           (strncmp(pegType, "all", 3) == 0)||
           (atoi(pegType) == ALL_MTP3_PEGS))
        {
            /* Invoke function MTP3_ResetOm_MML_CCITT() */
            MTP3_ResetOm_MML_CCITT();

            for (i = 0; i < PEG_MTP3_NUM_PEGS_CCITT; i++)
            {
                PEG_ClearPeg(CCITT_MTP3_Pegs, i);
            }

            sprintf(buf, "\nClearing All MTP3 General Pegs for Now\n\n");
            DBC_AppendText(dbc, buf);
            return;
        }
        else
        {
            if(!isdigit((int)pegType[0]))
            {
                sprintf(buf, "\n**** Unrecognized Peg *****\n");
                DBC_AppendText(dbc, buf);
                return;
            }
        }

        pgNum = atoi(pegType);        

        if (pgNum > PEG_MTP3_NUM_PEGS_CCITT - 1)
        {
            sprintf(buf, "\n   **** Invalid Peg Id *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        PEG_ClearPeg(CCITT_MTP3_Pegs, pgNum);

        sprintf(buf, "Clearing the Peg for %s Now\n", mtp3GPegStr[pgNum]);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_clr_link_peg", "MTP3 Clear particular Route Peg",
                          "<linkSet> <linkCode> [<Pegid> (or) <ALL/all>]",""))
    {
        char pegType[ITS_PATH_MAX];
        ITS_INT pgNum;
        ret = sscanf(cmdLine, "%s %d %d %s", buf, &linkSet, &linkCode,pegType);
        if (ret != 4)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
            "Usage: mi_clr_link_peg <linkset> <linkcode> [<Pegid> (or) <ALL/all>]\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
        {
            sprintf(buf, "\n***Link %d on link set %d is not configured***\n",
                           linkSet, linkCode);
            DBC_AppendText(dbc, buf);
            return;
        }

        if((strncmp(pegType, "ALL", 3) == 0) ||
           (strncmp(pegType, "all", 3) == 0) || 
           (atoi(pegType) == ALL_MTP3_PEGS))   
        {
            for (i = 0; i < PEG_MTP3_NUM_LINK_PEGS; i++)
            {
                PEG_ClearPeg(&ln->MTP3_LINK_PEGS, i);
            }

            sprintf(buf, "Clearing All MTP3 Link Pegs for linkset %d linkcode %d\n",
                         linkSet, linkCode);
            DBC_AppendText(dbc, buf);
            return;
        }
        else
        {
            if(!isdigit((int)pegType[0]))
            {
               sprintf(buf, "\n**** Unrecognized Peg *****\n");
               DBC_AppendText(dbc, buf);
               return;
            }
        }

        pgNum = atoi(pegType);

        if (pgNum >= PEG_MTP3_NUM_LINK_PEGS)
        {
            sprintf(buf, "\n   **** Invalid Peg Id *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, pgNum);

        sprintf(buf, "Clearing the Peg %s for linkset %d linkcode %d Now\n",
                      mtp3LPegStr[pgNum], linkSet, linkCode);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_clr_route_peg", "Clear route Level Pegs",
             "<dpc> <ni> <Peg Id>", ""))
    {
        char pgName[ITS_PATH_MAX];
        SS7_Destination* dest;
        ITS_INT pgNum;
        ITS_UINT dpc;
        ITS_UINT ni;

        ret = sscanf(cmdLine, "%s %d %d %s", buf, &dpc, &ni, pgName);
        if (ret != 4)
        {
            sprintf(buf,  "\n**** Invalid Command Arguments *******\n" \
                          "Usage: mi_get_dpc_peg <dpc> <ni> \
                                           [<Peg Id> or <ALL/all>]\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((dest = ROUTE_FindDestination(dpc, ni, FAMILY_ITU)) == NULL)
        {
            sprintf(buf, "\n*** DPC %d NI %d not configured ***\n", dpc, ni);
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((*dest->entries)->basic.type == LOCAL_ROUTE)
        {
            sprintf(buf, "\n*** LPC %d Local point code entered  ***\n", dpc);
            DBC_AppendText(dbc, buf);
            return;
        }

        if((strncmp(pgName, "ALL", 3) == 0) ||
           (strncmp(pgName, "all", 3) == 0)||
           (atoi(pgName) == ALL_MTP3_PEGS))
        {
            for (i = 0; i <= PEG_MTP3_NUM_DPC_PEGS; i++)
            {
                PEG_ClearPeg(&dest->MTP3_DPC_PEGS, i);
            }

            sprintf(buf, "Clearing All MTP3 Route Pegs for dpc %d ni %d\n",
                         dpc, ni);
            DBC_AppendText(dbc, buf);
            return;
        }
        else
        {
           if(!isdigit((int)pgName[0]))
           {
              sprintf(buf, "\n**** Unrecognized Peg *****\n");
              DBC_AppendText(dbc, buf);
              return;
           }
        }

        pgNum = atoi(pgName);

        if (pgNum > PEG_MTP3_NUM_DPC_PEGS)
        {
            sprintf(buf, "\n   **** Invalid Peg Id *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "Getting the Peg for %s Now\n",mtp3DPegStr[pgNum]);
        DBC_AppendText(dbc, buf);

        PEG_ClearPeg(&dest->MTP3_DPC_PEGS,pgNum);

        sprintf(buf, "Clearing the Peg %s for dpc %d ni %d Now\n",
                      mtp3DPegStr[pgNum], dpc, ni);

        DBC_AppendText(dbc, buf);
    }

#if 0
    else if (DBC_Cmd(dbc, "mi_debug_trace", "Debug Trace", "<on, off>", "<>"))
    {
        char onOff[10];

        ret = sscanf(cmdLine, "%s %s ",buf, onOff);

        if (strstr(onOff, "on") != NULL)
        {

            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_DEBUG_STRING,
                                       MTP3_STDOUT_STRING, ITS_TRUE);


            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      MTP3_DEBUG_STRING, ITS_TRUE);

        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_DEBUG_STRING,
                                       MTP3_STDOUT_STRING, ITS_FALSE);

            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      MTP3_DEBUG_STRING, ITS_FALSE);
        }
    }      
    else if (DBC_Cmd(dbc, "mi_warning_trace", "Warning Trace", "<on, off>", "<>"
))
    {
        char onOff[10];

        ret = sscanf(cmdLine, "%s %s ",buf, onOff);

        if (strstr(onOff, "on") != NULL)
        {

            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_WARNING_STRING,
                                       MTP3_STDOUT_STRING, ITS_TRUE);


            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      MTP3_WARNING_STRING, ITS_TRUE);

        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_WARNING_STRING,
                                       MTP3_STDOUT_STRING, ITS_FALSE);

            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      MTP3_WARNING_STRING, ITS_FALSE);
        }
    }     
    else if (DBC_Cmd(dbc, "mi_error_trace", "Error Trace", "<on, off>", "<>"))
    {
        char onOff[10];

        ret = sscanf(cmdLine, "%s %s ",buf, onOff);

        if (strstr(onOff, "on") != NULL)
        {

            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_ERROR_STRING,
                                       MTP3_STDOUT_STRING, ITS_TRUE);


            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      MTP3_ERROR_STRING, ITS_TRUE);

        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_ERROR_STRING,
                                       MTP3_STDOUT_STRING, ITS_FALSE);

            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      MTP3_ERROR_STRING, ITS_FALSE);
        }
    }    
#endif
    else if (DBC_Cmd(dbc, "mi_shutdown", "shutdown mtp3", "", ""))
    {
        ShutDownNode(dbc);

        TIMERS_Sleep(5);

        ENGINE_Terminate();
    }
    else if (DBC_Cmd(dbc, "mi_set_rpc", "set a remote point code",
               "<rpc><ssn><ls><f>", "<remote pc><ssn><link set><family>"))
    {
        char direction[20];
        char family[10];
        char buf[ITS_PATH_MAX];
        ITS_UINT rpc ;
        ITS_UINT sio;
        ITS_UINT ssn;
        ITS_UINT linkSet ;
        ITS_UINT linkCode ;
        ITS_UINT ret;

        SS7_LinkSetPtr ls;
        SS7_LinkPtr    lp;
        SS7_LinkSet    set;
        ROUTE_MatchInfo rinfo;

        memset(&rinfo, 0, sizeof(rinfo));

        memset(&set, 0, sizeof(SS7_LinkSet));
        set.isUp = ITS_FALSE;

        /* addRoute direction paremeters */
        ret = sscanf(cmdLine, "%s   %d    %d   %d    %d       %s",
                               buf, &rpc, &sio, &ssn, &linkSet, family);
       if (ret != 6)
       {
           sprintf(buf,"*** Error: Invalid parameters, try help mi_set_rpc \n");
           DBC_AppendText(dbc, buf);
           return;
       }
       /*** process family ***/

       if (strcmp(family, FAMILY_ANSI_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_ANSI;
           set.family = FAMILY_ANSI ;
       }
       else if (strcmp(family, FAMILY_CCITT_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_ITU;
           set.family = FAMILY_ITU ;
       }
       else if (strcmp(family, FAMILY_CHINA_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_CHINA;
       }
       else if (strcmp(family, FAMILY_JAPAN_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_JAPAN;
       }
       else
       {
           sprintf(buf, "Error invalid family...\n");
           DBC_AppendText(dbc, buf);
           return;
       }
       ls = LINKSET_FindLinkSet(linkSet);
       if (ls != NULL)
       {
          /* LinkSet exist ,So check for linkcode configuration */

           for (linkCode = 0 ; linkCode < MAX_LINKS ; linkCode++)
           {
               lp = LINK_FindLink((ITS_OCTET) linkSet, (ITS_OCTET) linkCode);

               if (lp != NULL)
               {
                   /* link exist for this linkset ,So proceed */
                   /* sprintf(buf, "ls:%d lc:%d exist\n",linkSet, linkCode);
                      DBC_AppendText(dbc, buf);
                   */
                   break ;
               }
           }
           if ( linkCode == MAX_LINKS )
           {
               sprintf( buf,  "links not configured for this linkset : %d",
                               linkSet);
               DBC_AppendText(dbc, buf);

               return ;
           }
       }
       else
       {
            sprintf( buf,  "LinkSet %d not configured ", linkSet);
            DBC_AppendText(dbc, buf);
            return ;
       }
       /** Process Direction **/

       strcpy(direction,ROUTE_TYPE_REMOTE_STRING) ;

       rinfo.basic.type = REMOTE_ROUTE;

       sprintf(buf, "*********** Adding Remote pointcode %d*************\n",rpc
)
;
       DBC_AppendText(dbc, buf);
       /*** process route style ****/

       rinfo.basic.style = ROUTE_DPC_SIO_SSN;
       rinfo.basic.dpc = rpc;
       rinfo.basic.criteria.sio = sio ;
       rinfo.basic.criteria.ssn = ssn ;

       rinfo.linkSet = (ITS_OCTET) linkSet;
       rinfo.linkCode = 0;
       rinfo.priority = 0;
       rinfo.sls  = 0;
       rinfo.rkey = 0;
       rinfo.basic.mask = ITS_SS7_DEFAULT_ROUTE_MASK;

       if ( (ret = ROUTE_AddRouteContextInfo(&rinfo)) != ITS_SUCCESS)
       {
           sprintf(buf, "Error %d: Route cannot be added\n", ret);
           DBC_AppendText(dbc,buf);
           return;
       }
    }
    else if (DBC_Cmd(dbc, "mi_rem_rpc","Remove a remote point code",
         "<rpc><ni><LinkSet><family>", "<remote pc><ni><linkset><family>"))
    {
        char family[10];
        ITS_UINT rpc ;
        ITS_UINT ni,famly ;
        ITS_UINT linkSet;

        ROUTE_MatchInfo rinfo;
        SS7_Destination *rc;
        SS7_LinkSetPtr ls;

        ret = sscanf(cmdLine, "%s %d %d %d %s", buf, &rpc, &ni, &linkSet,family
);
        if (ret != 5)
        {
           sprintf(buf, "*** Error: Invalid parameters, try help mi_rem_rpc \n"
);
           DBC_AppendText(dbc, buf);
           return;
        }

        rinfo.basic.type = REMOTE_ROUTE;

       if (strcmp(family, FAMILY_ANSI_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_ANSI;
           famly = FAMILY_ANSI ;
       }
       else if (strcmp(family, FAMILY_CCITT_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_ITU;
           famly = FAMILY_ITU ;
       }
       else if (strcmp(family, FAMILY_CHINA_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_CHINA;
           famly = FAMILY_CHINA ;
       }
       else if (strcmp(family, FAMILY_JAPAN_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_JAPAN;
           famly = FAMILY_JAPAN ;
       }
       else
       {
           sprintf(buf, "Error invalid family...\n");
           DBC_AppendText(dbc, buf);
           return;
       }

       ls = LINKSET_FindLinkSet(linkSet);
       if (ls == NULL)
       {
           sprintf(buf, "Invalid Linkset\n");
           DBC_AppendText(dbc, buf);
           return;
       }
       if ((rc = ROUTE_FindDestination(rpc, ni, famly)) == NULL)
       {
          sprintf(buf,"%s","Error : Cannot delete - RPC Not Found\n");
          DBC_AppendText(dbc, buf);
          return ;
       }

       rinfo.basic.style = ROUTE_DPC_NI;
       rinfo.basic.dpc = rpc;
       rinfo.basic.criteria.sio = (ITS_OCTET)ni & ROUTE_NI_MASK;

       rinfo.linkSet = (ITS_OCTET) linkSet;
       rinfo.linkCode = 0;
       rinfo.priority = 0;
       rinfo.sls  = 0;
       rinfo.rkey = 0;
       rinfo.basic.mask = ITS_SS7_DEFAULT_ROUTE_MASK;
       if (ROUTE_DeleteRouteContextInfo(&rinfo) != ITS_SUCCESS)
       {
           sprintf(buf, "Error %d: Route cannot be deleted\n", ret);
           DBC_AppendText(dbc, buf);
           return;
       }
       sprintf(buf, "*********** Deleting Remote pointcode %d**********\n",rpc)
;
       DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_get_all_rpc", "get all remote PC", "<>", "<>"))
    {
        char *dump = NULL;
        char* strDumpEntries = NULL;

        strDumpEntries = (char *)calloc(PRINT_DATA_MAX_SIZE, sizeof(char));

        DSM_TableIterate(DSM_RoutingFtGroupId,
                           DSM_TABLE_DESTINATIONS,
                           &strDumpEntries,
                           NULL,
                           DumpRemotePointCodeData);

        if (strDumpEntries)
        {
            DBC_AppendText(dbc, strDumpEntries);
            free(dump);
        }
    }
    else if (DBC_Cmd(dbc, "mi_get_all_lpc", "get all local PC", "<>", "<>"))
    {
        char *dump = NULL;
        char* strDumpEntries = NULL;

        strDumpEntries = (char *)calloc(PRINT_DATA_MAX_SIZE, sizeof(char));

        DSM_TableIterate(DSM_RoutingFtGroupId,
                           DSM_TABLE_DESTINATIONS,
                           &strDumpEntries,
                           NULL,
                           DumpLocalPointCodeData);

        if (strDumpEntries)
        {
            DBC_AppendText(dbc, strDumpEntries);
            free(dump);
        }
    }
    else if (DBC_Cmd(dbc, "mi_lpo", "Local Processor Outage", "<ls> <lc>", "<linkset> <linkcode>"))
    {
        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            sprintf(buf, "*** Error: Invalid parameters, try help mi_lpo \n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
        {
            sprintf(buf, "\n***Link %d on linkset %d is not configured***\n",
                           linkCode, linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }

        if (ln->isSAAL)
        {
            sprintf(buf," *** LPO is not supported for SAAL Link *** \n");
            DBC_AppendText(dbc, buf);
            return;
        }
      
        ls = LINKSET_FindLinkSet((ITS_OCTET) linkSet);
        if (ls->family != FAMILY_ITU)
        {
            sprintf(buf, "\n***Mismatch in the linkSet Family***\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "*** sending Local Processor Outage to MTP3 for ls:%d lc:%d ***\n",
                     linkSet, linkCode);
        DBC_AppendText(dbc, buf);

        MGMT_Main_CCITT(MTP3_USER,
                       MGMT_TRIGGER_LP_OUTAGE,
                       NULL, 0,
                       (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);
    }
    else if (DBC_Cmd(dbc, "mi_lpr", "Local Processor Recovery", "<ls> <lc>", "<linkset> <linkcode>"))
    {
        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            sprintf(buf, "*** Error: Invalid parameters, try help mi_lpr \n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
        {
            sprintf(buf, "\n***Link %d on linkset %d is not configured***\n",
                           linkCode, linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }

        if (ln->isSAAL)
        {
            sprintf(buf," *** LPR is not supported for SAAL Link *** \n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ls = LINKSET_FindLinkSet((ITS_OCTET) linkSet);
        if (ls->family != FAMILY_ITU)
        {
            sprintf(buf, "\n***Mismatch in the linkSet Family***\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "*** sending Local Processor Recovery to MTP3 for ls:%d lc:%d ***\n",
                     linkSet, linkCode);
        DBC_AppendText(dbc, buf);

        MGMT_Main_CCITT(MTP3_USER,
                       MGMT_TRIGGER_LP_RECOVERD,
                       NULL, 0,
                       (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);
    }
}

#if 0
void
MTP3_Console_CCITT(DBC_Server *dbc, const char *cmdLine)
{    
    char buf[ITS_PATH_MAX];
    int linkSet = 0, linkCode = 0, ret = 0;
    ITS_UINT pg,value;
    SS7_LinkSetPtr ls;
    SS7_LinkPtr ln; 
    ITS_UINT i;

    ITS_C_ASSERT(dbc != NULL);

    if (DBC_Cmd(dbc, "mi_il", "Inhibit Link", "<ls> <lc>", "<link set> <link code>"))
    {
        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            return;
        }

        if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
        {
            sprintf(buf, "\n***Link %d on link set %d is not configured***\n",
                           linkCode, linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "*********** Going to inhibit link 1 now *************\n");
        DBC_AppendText(dbc, buf);

        MGMT_Main_CCITT(MTP3_USER,
                        MGMT_TRIGGER_INHIBIT_LINK,
                        NULL, 0,
                        (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);

        sprintf(buf, "*********** Returned from the MGMT Inhibit *************\n");
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_ul", "Uninhibit Link", "<ls> <lc>", "<link set> <link code>"))
    {
        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            return;
        }

        if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
        {
            sprintf(buf, "\n***Link %d on link set %d is not configured***\n",
                           linkCode, linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "*********** Going to uninhibit link 1 now *************\n");
        DBC_AppendText(dbc, buf);

        MGMT_Main_CCITT(MTP3_USER,
                        MGMT_TRIGGER_UNINHIBIT_LINK,
                        NULL, 0,
                        (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);

        sprintf(buf, "*********** Returned from the MGMT UnInhibit *************\n");
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_dls", "Deactivate Link Set", "<ls>", "<link set>"))
    {
        ret = sscanf(cmdLine, "%s %d", buf, &linkSet);
        if (ret != 2)
        {
            return;
        }

        if ((ls = LINKSET_FindLinkSet((ITS_OCTET)linkSet)) == NULL)
        {
            sprintf(buf, "\n***Linkset %d not configured***\n", linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "*********** Deactivating link set ************\n");
        DBC_AppendText(dbc, buf);

        MGMT_Main_CCITT(MTP3_USER,
                        MGMT_TRIGGER_DEACTIVATE_LINK_SET,
                        NULL, 0,
                        (ITS_OCTET)linkSet, ITS_SS7_DEFAULT_LINK_CODE);

        sprintf(buf, "*********** Link set deactivated *************\n");
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_als", "Activate Link Set", "<ls>", "<link set>"))
    {
        ret = sscanf(cmdLine, "%s %d", buf, &linkSet);
        if (ret != 2)
        {
            return;
        }

        if ((ls = LINKSET_FindLinkSet((ITS_OCTET)linkSet)) == NULL)
        {
            sprintf(buf, "\n***Linkset %d not configured***\n", linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "*********** Activate Link Set ************\n");
        DBC_AppendText(dbc, buf);

        MGMT_Main_CCITT(MTP3_USER,
                        MGMT_TRIGGER_ACTIVATE_LINK_SET,
                        NULL, 0,
                        (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);

        sprintf(buf, "*********** Link Set Activated *************\n");
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_dln", "Deactivate Link", "<ls> <lc>", "<link set> <link code>"))
    {
        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            return;
        }

        if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
        {
            sprintf(buf, "\n***Link %d on link set %d is not configured***\n",
                           linkCode, linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "****** Going to Deactivate link now ******\n");
        DBC_AppendText(dbc, buf);

        MGMT_Main_CCITT(MTP3_USER,
                        MGMT_TRIGGER_DEACTIVATE_LINK,
                        NULL, 0,
                        (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);

        sprintf(buf, "****** Returned from the MGMT Deactivate Link ******\n");
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_aln", "Activate Link", "<ls> <lc>", "<link set> <link code>"))
    {
        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            return;
        }

        if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
        {
            sprintf(buf, "\n***Link %d on link set %d is not configured***\n",
                           linkCode, linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "****** Going to Activate link now ******\n");
        DBC_AppendText(dbc, buf);

        MGMT_Main_CCITT(MTP3_USER,
                        MGMT_TRIGGER_ACTIVATE_LINK,
                        NULL, 0,
                        (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);

        sprintf(buf, "****** Returned from the MGMT Activate Link ******\n");
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_start", "Start MTP3", "<>", "<>"))
    {
        sprintf(buf, "*********** Starting MTP3 **************\n");
        DBC_AppendText(dbc, buf);

        MGMT_Main_CCITT(MTP3_USER,
                        MGMT_TRIGGER_RESTART,
                        NULL, 0,
                        ITS_SS7_DEFAULT_LINK_SET,
                        ITS_SS7_DEFAULT_LINK_CODE);

        sprintf(buf, "*********** Returned from the MGMT Restart *************\n");
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_dumpls", "Dump Link Sets", "<>", "<>"))
    {
        char *dump = NULL;
        SS7_Family family = FAMILY_ITU;

        ROUTE_LockForWrite(routeRWLock);

        LINKSET_DumpLinkSetHashtable(&dump, family);

        ROUTE_UnlockWrite(routeRWLock);

        if (dump)
        {
            DBC_AppendText(dbc, dump);
        }
    }
    else if (DBC_Cmd(dbc, "mi_dumprt", "Dump Routes Info", "<>", "<>"))
    {
        char *dump = NULL;

        ROUTE_LockForWrite(routeRWLock);

        ROUTE_DumpSS7ToIdHashtable(&dump,cmdLine);

        ROUTE_UnlockWrite(routeRWLock);

        if (dump)
        {
            DBC_AppendText(dbc, dump);
        free(dump);
        }

    }
    else if (DBC_Cmd(dbc, "mi_link_status", "get Link Status", "<ls>", "<lc>"))
    {
        char *dump = NULL;

        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);

        ROUTE_LockForWrite(routeRWLock);

        LINK_DumpLinkInfo(&dump, (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);

        ROUTE_UnlockWrite(routeRWLock);

        if (dump)
        {
            DBC_AppendText(dbc, dump);
        }

    }
    else if (DBC_Cmd(dbc, "mi_get_peg", "Get Pegs", "<pg> ", "<Peg#> <>"))
    {
        ret = sscanf(cmdLine, "%s %d", buf, &pg);
        if (ret != 2)
        {
             return;
        }

        if (pg >= PEG_MTP3_NUM_PEGS_CCITT || pg < 0)
        {
            sprintf(buf, "range for peg is %d - %d", 0,PEG_MTP3_NUM_PEGS_CCITT-1);
            DBC_AppendText(dbc, buf);
            return ;
        }

        sprintf(buf, "Getting the Peg for #%d Now\n", pg);
        DBC_AppendText(dbc, buf);

        value = PEG_GetPeg(CCITT_MTP3_Pegs, pg);

        sprintf(buf, "value is %d\n", value);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_get_link_peg", "Get Link Level Pegs", "<ls> <lc> <p g>", "<link set> <link code><Peg#>"))
    {
        ret = sscanf(cmdLine, "%s %d %d %d", buf, &linkSet, &linkCode, &pg);
        if (ret != 4)
        {
            sprintf(buf, "Please enter the proper format\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (pg >= PEG_MTP3_LINK_NUM_PEGS || pg < 4)
        {
            sprintf(buf, "range for Pegs is %d - %d\n", 4, (PEG_MTP3_LINK_NUM_PEGS - 1));
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "******Getting the Peg for link %d:%d, peg %d ******\n", linkSet, linkCode,pg);

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));
            return;
        }

        value = PEG_GetPeg(&ln->MTP3_LINK_PEGS,pg);

        sprintf(buf, "value is %d\n", value);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_show_peg_ids", "Dump Peg Ids", "<>", "<>"))
    {
        DumpGlobalPegId(dbc);
        DumpLinkPegId(dbc);

    }
    else if (DBC_Cmd(dbc, "mi_clr_gen_pegs", "MTP3 Reset a particular gen Peg",
                          "[<Pegid> (or) <All/all>]",""))
    {
        char pegType[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s", buf, pegType);

        if (ret != 2)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: mi_clr_gen_pegs [<Pegid> (or) <All/all>]\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if(strncmp(pegType, "All", 3) == 0 ||
           strncmp(pegType, "all", 3) == 0)
        {
           for (i = 0; i < PEG_MTP3_NUM_PEGS_CCITT; i++)
           {
               PEG_ClearPeg(CCITT_MTP3_Pegs, i);
           }

           sprintf(buf, "\n** Cleared all MTP3 gen pegs **\n");
           DBC_AppendText(dbc, buf);
           return;
        }
        else
        {
           if(!isdigit((int)pegType[0]))
           {
              sprintf(buf, "\n**** Unrecognized Peg *****\n");
              DBC_AppendText(dbc, buf);
              return;
           }
        }

        if ( atoi(pegType) > PEG_MTP3_NUM_PEGS_CCITT - 1)
        {
             sprintf(buf, "\n** MTP3 general peg %d does not exist **\n",
                                                       atoi(pegType));
             DBC_AppendText(dbc, buf);
             return;
         }
         for (i = 0; i < PEG_MTP3_NUM_PEGS_CCITT; i++)
         {
             if (i == (ITS_UINT)RESFILE_ParseNum(pegType))
             {
                 PEG_ClearPeg(CCITT_MTP3_Pegs, i);
                 sprintf(buf, "\n** Cleared MTP3 general peg id %d **\n", i);

                 DBC_AppendText(dbc, buf);
                 break;
             }
         }
    }
    else if (DBC_Cmd(dbc, "mi_clr_link_pegs", "MTP3 Clear particular Link Peg",
                          "<linkset> <linkcode> [<Pegid> (or) <All/all>]",""))
    {
        char pegType[ITS_PATH_MAX];
        ret = sscanf(cmdLine, "%s %d %d %s", buf, &linkSet, &linkCode,pegType);
        if (ret != 4)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
            "Usage: mi_clr_link_pegs <linkset> <linkcode> [<Pegid> (or) <All/all>]\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (atoi(pegType) > PEG_MTP3_LINK_NUM_PEGS - 1)
        {
            sprintf(buf, "\n** MTP3 Link peg %d does not exist **\n", atoi(pegType)
);
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
        {
            sprintf(buf, "\n***Link %d on link set %d is not configured***\n",
                           linkCode, linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }

        if(strncmp(pegType, "All", 3) == 0 ||
           strncmp(pegType, "all", 3) == 0)
        {
           for (i = 0; i < PEG_MTP3_LINK_NUM_PEGS; i++)
           {
               PEG_ClearPeg(&ln->MTP3_LINK_PEGS, i);
           }

           sprintf(buf, "\n** Cleared all pegs for linkset %d linkcode %d**\n",
                   linkSet,linkCode);

           DBC_AppendText(dbc, buf);
           return;
         }
         else
         {
            if(!isdigit((int)pegType[0]))
            {
               sprintf(buf, "\n**** Unrecognized Peg *****\n");
               DBC_AppendText(dbc, buf);
               return;
            }
         }

        for (i = 0; i < PEG_MTP3_LINK_NUM_PEGS; i++)
        {
            if ((ITS_UINT)RESFILE_ParseNum(pegType) == i)
            {
               PEG_ClearPeg(&ln->MTP3_LINK_PEGS, i);
               sprintf(buf, "\n** Cleared peg id %d for linkset %d linkcode %d **\n",i,linkSet,linkCode);
               return;
            }
         }

        for (i = 0; i < PEG_MTP3_LINK_NUM_PEGS; i++)
        {
            if ((ITS_UINT)RESFILE_ParseNum(pegType) == i)
            {
               PEG_ClearPeg(&ln->MTP3_LINK_PEGS, i);
               sprintf(buf, "\n** Cleared peg id %d for linkset %d linkcode %d **\n",i, linkSet,linkCode);
               DBC_AppendText(dbc, buf);
               break;
            }
        }
    }
    else if (DBC_Cmd(dbc, "mi_debug_trace", "Debug Trace", "<on, off>", "<>"))
    {
        char onOff[10];

        ret = sscanf(cmdLine, "%s %s ",buf, onOff);

        if (strstr(onOff, "on") != NULL)
        {

            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_DEBUG_STRING,
                                       MTP3_STDOUT_STRING, ITS_TRUE);


            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      MTP3_DEBUG_STRING, ITS_TRUE);

        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_DEBUG_STRING,
                                       MTP3_STDOUT_STRING, ITS_FALSE);

            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      MTP3_DEBUG_STRING, ITS_FALSE);
        }
    }      
    else if (DBC_Cmd(dbc, "mi_warning_trace", "Warning Trace", "<on, off>", "<>"
))
    {
        char onOff[10];

        ret = sscanf(cmdLine, "%s %s ",buf, onOff);

        if (strstr(onOff, "on") != NULL)
        {

            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_WARNING_STRING,
                                       MTP3_STDOUT_STRING, ITS_TRUE);


            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      MTP3_WARNING_STRING, ITS_TRUE);

        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_WARNING_STRING,
                                       MTP3_STDOUT_STRING, ITS_FALSE);

            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      MTP3_WARNING_STRING, ITS_FALSE);
        }
    }     
    else if (DBC_Cmd(dbc, "mi_error_trace", "Error Trace", "<on, off>", "<>"))
    {
        char onOff[10];

        ret = sscanf(cmdLine, "%s %s ",buf, onOff);

        if (strstr(onOff, "on") != NULL)
        {

            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_ERROR_STRING,
                                       MTP3_STDOUT_STRING, ITS_TRUE);


            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      MTP3_ERROR_STRING, ITS_TRUE);

        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_ERROR_STRING,
                                       MTP3_STDOUT_STRING, ITS_FALSE);

            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      MTP3_ERROR_STRING, ITS_FALSE);
        }
    }    
    else if (DBC_Cmd(dbc, "mi_shutdown", "shutdown mtp3", "<>", "<>"))
    {
        ShutDownNode(dbc);

        TIMERS_Sleep(5);

        ENGINE_Terminate();
    }

}
#endif

static int
DumpRemotePointCodeData(ITS_POINTER data, void *in, void *out)
{
    char** pStrDump = (char **)in;
    ITS_UINT i,j ;
    char printBuf[PRINT_BUF_MAX_SIZE];
    SS7_Destination* ss7Context = (SS7_Destination*)data;

    if (*pStrDump == NULL)
    {
        return ITS_ENOMEM;
    }

    for (i = 0; i < ss7Context->numEntries; i++)
    {
       if ( ss7Context->entries[i]->basic.type == REMOTE_ROUTE &&
           ss7Context->entries[i]->basic.family == FAMILY_ITU )
       {
           strcat(*pStrDump, "------------------------------\n");

           /* Remote PointCode. */

           strcat(*pStrDump, "Remote PC:         <");
           sprintf(printBuf, "%u", ss7Context->entries[i]->basic.dpc);
           strcat(*pStrDump, printBuf);
           strcat(*pStrDump, ">\n");

           /* Family */

           strcat(*pStrDump, "Family:      <");
           strcat(*pStrDump,
                  FAMILY_TO_TEXT(ss7Context->entries[i]->basic.family));
           strcat(*pStrDump, ">\n");

           /* SIO */

           strcat(*pStrDump, "SIO:         <");
           sprintf(printBuf, "%u",
                   ss7Context->entries[i]->basic.criteria.sio);
           strcat(*pStrDump, printBuf);
           strcat(*pStrDump, ">\n");

           /* status . */

           strcat(*pStrDump, "status:      <");
           sprintf(printBuf, "%s", STATUS_STR(ss7Context->status));
           strcat(*pStrDump, printBuf);
           strcat(*pStrDump, ">\n");
           strcat(*pStrDump, "------------------------------\n");

           for (j = 0; j <= i; j++)
           {
               if (ss7Context->entries[i]->basic.dpc ==
                                            ss7Context->entries[j]->basic.dpc )
               {
                   return ITS_SUCCESS ;
               }
           }

        }
     }
     return ITS_SUCCESS;
}


static int
DumpLocalPointCodeData(ITS_POINTER data, void *in, void *out)
{
    char** pStrDump = (char **)in;
    ITS_UINT i,j;
    char printBuf[PRINT_BUF_MAX_SIZE];
    SS7_Destination* ss7Context = (SS7_Destination*)data;

    if (*pStrDump == NULL)
    {
        return ITS_ENOMEM;
    }

    for (i = 0; i < ss7Context->numEntries; i++)
    {
        if ( ss7Context->entries[i]->basic.type == LOCAL_ROUTE && 
                ss7Context->entries[i]->basic.family == FAMILY_ITU )
        {
           strcat(*pStrDump, "------------------------------\n");

           /*Local PointCode. */
           strcat(*pStrDump, "Local PC:         <");
           sprintf(printBuf, "%u", ss7Context->entries[i]->basic.dpc);
           strcat(*pStrDump, printBuf);
           strcat(*pStrDump, ">\n");

           /* Family */
           strcat(*pStrDump, "Family:      <");
           strcat(*pStrDump,
                  FAMILY_TO_TEXT(ss7Context->entries[i]->basic.family));
           strcat(*pStrDump, ">\n");

           strcat(*pStrDump, "------------------------------\n");

           for (j = 0; j <= i; j++)
           {
               if (ss7Context->entries[i]->basic.dpc ==
                                            ss7Context->entries[j]->basic.dpc )
               {
                   return ITS_SUCCESS ;
               }
           }
        }
     }
     return ITS_SUCCESS;
}


static int
DumpGlobalPegs(DBC_Server *dbc)
{
     char buf[ITS_PATH_MAX];

     sprintf(buf, "\n********** Printing Global Pegs **********\n");
     DBC_AppendText(dbc, buf);

#ifndef WIN32

     /* Print the pegs and their assciated Id's */
     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_MSG_PAUSE),
              PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_PAUSE));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_MSG_RESUME),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_RESUME));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_MSG_STATUS),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_STATUS));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_MSG_RECEIVED_INERROR),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_RECEIVED_INERROR));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_CHANGEOVER),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_CHANGEOVER));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_CHANGEBACK),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_CHANGEBACK));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_SL_UNAVAILABLE),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_SL_UNAVAILABLE));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_LINK_INHIBIT),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_INHIBIT));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_LINK_UNINHIBIT),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_UNINHIBIT));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_LINK_FORCE_UNINHIBIT),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_FORCE_UNINHIBIT));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_CONGESTION),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_CONGESTION));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_SLS_UNAVAILABLE),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_SLS_UNAVAILABLE));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_TFC_RECEIVED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_TFC_RECEIVED));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_TFA_RECEIVED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_TFA_RECEIVED));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_ROUTESET_UNAVAILABLE),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_ROUTESET_UNAVAILABLE));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_ADJECENT_SP_UNACCESIBLE),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_ADJECENT_SP_UNACCESIBLE));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_USERPART_ENABLE),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_USERPART_ENABLE));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T1_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T1_EXPIRED));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T2_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T2_EXPIRED));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T3_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T3_EXPIRED));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T4_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T4_EXPIRED));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T5_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T5_EXPIRED));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T6_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T6_EXPIRED));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T7_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T7_EXPIRED));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T8_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T8_EXPIRED));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T9_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T9_EXPIRED));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T10_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T10_EXPIRED));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T11_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T11_EXPIRED));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T12_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T12_EXPIRED));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T13_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T13_EXPIRED));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T14_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T14_EXPIRED));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T15_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T15_EXPIRED));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T16_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T16_EXPIRED));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T17_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T17_EXPIRED));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T18_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T18_EXPIRED));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T19_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T19_EXPIRED));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T20_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T20_EXPIRED));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T21_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T21_EXPIRED));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T22_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T22_EXPIRED));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T23_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T23_EXPIRED));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-35s  :  %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T24_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T24_EXPIRED));

     DBC_AppendText(dbc, buf);

#if 0
     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T25_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T25_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T26_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T26_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T27_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T27_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T28_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T28_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T29_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T29_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T30_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T30_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T31_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T31_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T32_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T32_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T33_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T33_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T34_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T34_EXPIRED));
     DBC_AppendText(dbc, buf);
#endif
#endif
    return ITS_SUCCESS;
}


void
DumpGlobalPegId(DBC_Server *dbc)
{

     char buf[32000];
     char buf1[32000];

     memset(buf , 0, 32000);
     memset(buf1, 0, 32000);

     sprintf(buf, "\n*****Printing Global Pegs****************\n");
     strcat(buf1, buf);

#ifndef WIN32

     /* Print the pegs and their assciated Id's */
     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_MSG_PAUSE),
             PEG_MTP3_MSG_PAUSE, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_PAUSE));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_MSG_RESUME),
             PEG_MTP3_MSG_RESUME, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_RESUME));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_MSG_STATUS),
             PEG_MTP3_MSG_STATUS, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_STATUS));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_INITIALIZE),
             PEG_MTP3_INITIALIZE, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_INITIALIZE));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_TERMINATE),
             PEG_MTP3_TERMINATE, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_TERMINATE));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_MSG_RECEIVED_INERROR),
             PEG_MTP3_MSG_RECEIVED_INERROR, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_RECEIVED_INERROR));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_CHANGEOVER),
             PEG_MTP3_CHANGEOVER, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_CHANGEOVER));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_CHANGEBACK),
             PEG_MTP3_CHANGEBACK, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_CHANGEBACK));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_SL_UNAVAILABLE),
             PEG_MTP3_SL_UNAVAILABLE, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_SL_UNAVAILABLE));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_LINK_INHIBIT),
             PEG_MTP3_LINK_INHIBIT, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_INHIBIT));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_LINK_UNINHIBIT),
             PEG_MTP3_LINK_UNINHIBIT, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_UNINHIBIT));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_LINK_FORCE_UNINHIBIT),
             PEG_MTP3_LINK_FORCE_UNINHIBIT, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_FORCE_UNINHIBIT));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_CONGESTION),
             PEG_MTP3_CONGESTION, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_CONGESTION));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_SLS_UNAVAILABLE),
             PEG_MTP3_SLS_UNAVAILABLE, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_SLS_UNAVAILABLE));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_TFC_RECEIVED),
             PEG_MTP3_TFC_RECEIVED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_TFC_RECEIVED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_TFA_RECEIVED),
             PEG_MTP3_TFA_RECEIVED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_TFA_RECEIVED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_ROUTESET_UNAVAILABLE),
             PEG_MTP3_ROUTESET_UNAVAILABLE, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_ROUTESET_UNAVAILABLE));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_ADJECENT_SP_UNACCESIBLE),
             PEG_MTP3_ADJECENT_SP_UNACCESIBLE, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_ADJECENT_SP_UNACCESIBLE));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_USERPART_ENABLE),
             PEG_MTP3_USERPART_ENABLE, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_USERPART_ENABLE));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_USERPART_DISABLE),
             PEG_MTP3_USERPART_DISABLE, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_USERPART_DISABLE));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T1_EXPIRED),
             PEG_MTP3_T1_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T1_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T2_EXPIRED),
             PEG_MTP3_T2_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T2_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T3_EXPIRED),
             PEG_MTP3_T3_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T3_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T4_EXPIRED),
             PEG_MTP3_T4_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T4_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T5_EXPIRED),
             PEG_MTP3_T5_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T5_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T6_EXPIRED),
             PEG_MTP3_T6_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T6_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T7_EXPIRED),
             PEG_MTP3_T7_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T7_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T8_EXPIRED),
             PEG_MTP3_T8_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T8_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T9_EXPIRED),
             PEG_MTP3_T9_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T9_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T10_EXPIRED),
             PEG_MTP3_T10_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T10_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T11_EXPIRED),
             PEG_MTP3_T11_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T11_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T12_EXPIRED),
             PEG_MTP3_T12_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T12_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T13_EXPIRED),
             PEG_MTP3_T13_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T13_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T14_EXPIRED),
             PEG_MTP3_T14_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T14_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T15_EXPIRED),
             PEG_MTP3_T15_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T15_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T16_EXPIRED),
             PEG_MTP3_T16_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T16_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T17_EXPIRED),
             PEG_MTP3_T17_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T17_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T18_EXPIRED),
             PEG_MTP3_T18_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T18_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T19_EXPIRED),
             PEG_MTP3_T19_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T19_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T20_EXPIRED),
             PEG_MTP3_T20_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T20_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T21_EXPIRED),
             PEG_MTP3_T21_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T21_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T22_EXPIRED),
             PEG_MTP3_T22_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T22_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T23_EXPIRED),
             PEG_MTP3_T23_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T23_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T24_EXPIRED),
             PEG_MTP3_T24_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T24_EXPIRED));
     strcat(buf1, buf);

#if 0
     /* Commented as per spec */
     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T25_EXPIRED),
             PEG_MTP3_T25_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T25_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T26_EXPIRED),
             PEG_MTP3_T26_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T26_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T27_EXPIRED),
             PEG_MTP3_T27_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T27_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T28_EXPIRED),
             PEG_MTP3_T28_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T28_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T29_EXPIRED),
             PEG_MTP3_T29_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T29_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T30_EXPIRED),
             PEG_MTP3_T30_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T30_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T31_EXPIRED),
             PEG_MTP3_T31_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T31_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T32_EXPIRED),
             PEG_MTP3_T32_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T32_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T33_EXPIRED),
             PEG_MTP3_T33_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T33_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T34_EXPIRED),
             PEG_MTP3_T34_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T34_EXPIRED));
     strcat(buf1, buf);
#endif
#endif

     sprintf(buf, "\n*******************************************\n");
     strcat(buf1, buf);

     DBC_AppendText(dbc, buf1);
}

static int
DumpLinkPegs(SS7_LinkPtr ln, DBC_Server *dbc)
{
     char buf[ITS_PATH_MAX];

     sprintf(buf, "\n********** Printing Link Pegs **********\n");
     DBC_AppendText(dbc, buf);

#ifndef WIN32

 /* Print the pegs and their assciated Id's */
     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_COO_TX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COO_TX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_COO_RX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COO_RX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_COA_TX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COA_TX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_COA_RX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COA_RX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_ECO_TX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECO_TX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_ECO_RX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECO_RX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_ECA_TX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECA_TX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_ECA_RX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECA_RX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_CBD_TX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBD_TX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT (PEG_MTP3_LINK_CBD_RX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBD_RX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_CBA_TX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBA_TX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_CBA_RX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBA_RX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LIN_TX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIN_TX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LIN_RX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIN_RX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LIA_TX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIA_TX));
     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LIA_RX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIA_RX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LUN_TX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_TX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LUN_RX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_RX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LUA_TX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUA_TX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LUA_RX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUA_RX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LID_TX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LID_TX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LID_RX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LID_RX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LFU_TX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LFU_TX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LFU_RX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LFU_RX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LLI_TX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LLI_TX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LLI_RX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LLI_RX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LRI_TX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LRI_TX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LRI_RX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LRI_RX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_DLC_TX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_DLC_TX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_DLC_RX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS,PEG_MTP3_LINK_DLC_RX ));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_CSS_TX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CSS_TX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_CSS_RX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CSS_RX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_CNS_TX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNS_TX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_CNS_RX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNS_RX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_CNP_TX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNP_TX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_CNP_RX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNP_RX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_UPU_TX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_UPU_TX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_UPU_RX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_UPU_RX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_SLTM_TX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTM_TX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_SLTM_RX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTM_RX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_SLTA_TX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTA_TX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_SLTA_RX),
             PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTA_RX));

     DBC_AppendText(dbc, buf);

#endif
    return ITS_SUCCESS;
}

static ITS_INT
DumpDPCPegs(SS7_Destination* dest, DBC_Server *dbc)
{
     char buf[ITS_PATH_MAX];

     sprintf(buf, "\n********** Printing Link Pegs **********\n");
     DBC_AppendText(dbc, buf);

#ifndef WIN32

     /* Print the pegs and their assciated Id's */
     sprintf(buf,"%-30s  :  %d\n",DPC_PEGID_TO_TEXT(PEG_MTP3_DPC_TFA_TX),
             PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFA_TX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",DPC_PEGID_TO_TEXT(PEG_MTP3_DPC_TFA_RX),
             PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFA_RX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",DPC_PEGID_TO_TEXT(PEG_MTP3_DPC_TFP_TX),
             PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFP_TX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",DPC_PEGID_TO_TEXT(PEG_MTP3_DPC_TFP_RX),
             PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFP_RX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",DPC_PEGID_TO_TEXT(PEG_MTP3_DPC_RST_TX),
             PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_RST_TX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",DPC_PEGID_TO_TEXT(PEG_MTP3_DPC_RST_RX),
             PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_RST_RX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",DPC_PEGID_TO_TEXT(PEG_MTP3_DPC_TFR_RX),
             PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFR_RX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",DPC_PEGID_TO_TEXT(PEG_MTP3_DPC_TFC_TX),
             PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFC_TX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",DPC_PEGID_TO_TEXT(PEG_MTP3_DPC_TFC_RX),
             PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFC_RX));

     DBC_AppendText(dbc, buf);

     sprintf(buf,"%-30s  :  %d\n",DPC_PEGID_TO_TEXT(PEG_MTP3_DPC_SIF_TX),
             PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_SIF_TX));

     DBC_AppendText(dbc, buf);

#endif
    return ITS_SUCCESS;
}


void
DumpLinkPegId(DBC_Server *dbc)
{
     char buf[32000];
     char buf1[32000];

     memset(buf , 0, 32000);
     memset(buf1, 0, 32000);

     sprintf(buf, "\n*****Printing Link Level Pegs************\n");
     strcat(buf1, buf);

     /* Print the pegs and their assciated Id's */
#if 0
     sprintf(buf, "PEG_MTP3_LINK_MSU_TX                    %3d\n",PEG_MTP3_LINK_MSU_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_MSU_RX                    %3d\n",PEG_MTP3_LINK_MSU_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_OCTETS_TX                 %3d\n",PEG_MTP3_LINK_OCTETS_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_OCTETS_RX                 %3d\n",PEG_MTP3_LINK_OCTETS_RX);
     strcat(buf1, buf);
#endif
     sprintf(buf, "PEG_MTP3_LINK_COO_TX                    %3d\n",PEG_MTP3_LINK_COO_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_COO_RX                    %3d\n",PEG_MTP3_LINK_COO_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_COA_TX                    %3d\n", PEG_MTP3_LINK_COA_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_COA_RX                    %3d\n",PEG_MTP3_LINK_COA_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_ECO_TX                    %3d\n",PEG_MTP3_LINK_ECO_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_ECO_RX                    %3d\n",PEG_MTP3_LINK_ECO_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_ECA_TX                    %3d\n",PEG_MTP3_LINK_ECA_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_ECA_RX                    %3d\n",PEG_MTP3_LINK_ECA_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_CBD_TX                    %3d\n",PEG_MTP3_LINK_CBD_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_CBD_RX                    %3d\n",PEG_MTP3_LINK_CBD_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_CBA_TX                    %3d\n",PEG_MTP3_LINK_CBA_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_CBA_RX                    %3d\n",PEG_MTP3_LINK_CBA_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LIN_TX                    %3d\n",PEG_MTP3_LINK_LIN_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LIN_RX                    %3d\n",PEG_MTP3_LINK_LIN_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LIA_TX                    %3d\n",PEG_MTP3_LINK_LIA_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LIA_RX                    %3d\n",PEG_MTP3_LINK_LIA_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LUN_TX                    %3d\n",PEG_MTP3_LINK_LUN_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LUN_RX                    %3d\n",PEG_MTP3_LINK_LUN_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LUA_TX                    %3d\n",PEG_MTP3_LINK_LUA_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LUA_RX                    %3d\n",PEG_MTP3_LINK_LUA_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LID_TX                    %3d\n",PEG_MTP3_LINK_LID_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LID_RX                    %3d\n",PEG_MTP3_LINK_LID_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LFU_TX                    %3d\n",PEG_MTP3_LINK_LFU_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LFU_RX                    %3d\n",PEG_MTP3_LINK_LFU_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LLI_TX                    %3d\n",PEG_MTP3_LINK_LLI_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LLI_RX                    %3d\n",PEG_MTP3_LINK_LLI_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LRI_TX                    %3d\n",PEG_MTP3_LINK_LRI_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LRI_RX                    %3d\n",PEG_MTP3_LINK_LRI_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_DLC_TX                    %3d\n",PEG_MTP3_LINK_DLC_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_DLC_RX                    %3d\n",PEG_MTP3_LINK_DLC_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_CSS_TX                    %3d\n",PEG_MTP3_LINK_CSS_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_CSS_RX                    %3d\n",PEG_MTP3_LINK_CSS_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_CNS_TX                    %3d\n",PEG_MTP3_LINK_CNS_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_CNS_RX                    %3d\n",PEG_MTP3_LINK_CNS_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_CNP_TX                    %3d\n",PEG_MTP3_LINK_CNP_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_CNP_RX                    %3d\n",PEG_MTP3_LINK_CNP_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_UPU_TX                    %3d\n",PEG_MTP3_LINK_UPU_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_UPU_RX                    %3d\n",PEG_MTP3_LINK_UPU_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_SLTM_TX                   %3d\n",PEG_MTP3_LINK_SLTM_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_SLTM_RX                   %3d\n",PEG_MTP3_LINK_SLTM_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_SLTA_TX                   %3d\n",PEG_MTP3_LINK_SLTA_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_SLTA_RX                   %3d\n",PEG_MTP3_LINK_SLTA_RX);
     strcat(buf1, buf);

     DBC_AppendText(dbc, buf1);
}


/****************************************************************************
 *  Purpose:
 *      To Start the MTP3 Node
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Void
 ****************************************************************************/
ITSSS7DLLAPI void 
MTP3_OSS_Start_CCITT()
{
    ITS_INT ret = ITS_SUCCESS;
    
    ret = MGMT_Main_CCITT(MTP3_USER,
                          MGMT_TRIGGER_RESTART,
                          NULL, 
                          0,
                          ITS_SS7_DEFAULT_LINK_SET,
                          ITS_SS7_DEFAULT_LINK_CODE);
}

/****************************************************************************
 *  Purpose:
 *      To Shutdown the MTP3 Node
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Void
 ****************************************************************************/
ITSSS7DLLAPI void 
MTP3_OSS_Shutdown_CCITT()
{
    NodeShutDown();

    TIMERS_Sleep(5);

    ENGINE_Terminate();
}

/****************************************************************************
 *  Purpose:
 *      Gets the MTP3 General config
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Void
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_GetGeneralCfg_CCITT(MTP3_GeneralCfg* genCfg)
{
    if (genCfg == NULL)
        return ITS_ENOMEM;

    genCfg->alarmLevel = (MGMT_AlarmLevel)MTP3_AlarmLevel_CCITT;

    genCfg->debugTrace = TRACE_IsLevelOn(MTP3_CCITT_TraceData, MTP3_TRACE_DEBUG); 
    if (genCfg->debugTrace)
    {
        genCfg->debugTraceOutput = 0;
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_DEBUG, 0))
        {
            genCfg->debugTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_DEBUG, 1))
        {
            genCfg->debugTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_DEBUG, 2))
        {
            genCfg->debugTraceOutput |= TRACE_TO_SYSLOG;
        }
        if (!genCfg->debugTraceOutput)
        {
            genCfg->debugTraceOutput |= TRACE_TO_NONE;
        }
    }

    genCfg->warningTrace = TRACE_IsLevelOn(MTP3_CCITT_TraceData, MTP3_TRACE_WARNING); 
    if (genCfg->warningTrace)
    {
        genCfg->warningTraceOutput = 0;
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_WARNING, 0))
        {
            genCfg->warningTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_WARNING, 1))
        {
            genCfg->warningTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_WARNING, 2))
        {
            genCfg->warningTraceOutput |= TRACE_TO_SYSLOG;
        }
        if (!genCfg->warningTraceOutput)
        {
            genCfg->warningTraceOutput |= TRACE_TO_NONE;
        }
    }

    genCfg->errorTrace = TRACE_IsLevelOn(MTP3_CCITT_TraceData, MTP3_TRACE_ERROR); 
    if (genCfg->errorTrace)
    {
        genCfg->errorTraceOutput = 0;
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_ERROR, 0))
        {
            genCfg->errorTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_ERROR, 1))
        {
            genCfg->errorTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_ERROR, 2))
        {
            genCfg->errorTraceOutput |= TRACE_TO_SYSLOG;
        }
        if (!genCfg->errorTraceOutput)
        {
            genCfg->errorTraceOutput |= TRACE_TO_NONE;
        }
    }

    genCfg->criticalTrace = TRACE_IsLevelOn(MTP3_CCITT_TraceData, MTP3_TRACE_ABORT); 
    if (genCfg->criticalTrace)
    {
        genCfg->criticalTraceOutput = 0;
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_ABORT, 0))
        {
            genCfg->criticalTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_ABORT, 1))
        {
            genCfg->criticalTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_ABORT, 2))
        {
            genCfg->criticalTraceOutput |= TRACE_TO_SYSLOG;
        }
        if (!genCfg->criticalTraceOutput)
        {
            genCfg->criticalTraceOutput |= TRACE_TO_NONE;
        }
    }

    genCfg->eventTrace = TRACE_IsLevelOn(MTP3_CCITT_TraceData, MTP3_TRACE_EVENT); 
    if (genCfg->eventTrace)
    {
        genCfg->eventTraceOutput = 0;
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_EVENT, 0))
        {
            genCfg->eventTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_EVENT, 1))
        {
            genCfg->eventTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_EVENT, 2))
        {
            genCfg->eventTraceOutput |= TRACE_TO_SYSLOG;
        }
        if (!genCfg->eventTraceOutput)
        {
            genCfg->eventTraceOutput |= TRACE_TO_NONE;
        }
    }

    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Sets the MTP3 General config
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Void
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_SetGeneralCfg_CCITT(MTP3_GeneralCfg* genCfg)
{
    if (genCfg == NULL)
        return ITS_ENOMEM;

    MTP3_AlarmLevel_CCITT = genCfg->alarmLevel;

    if (genCfg->debugTrace)
    {
        TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData, MTP3_DEBUG_STRING,  ITS_TRUE); 

        if (genCfg->debugTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_DEBUG_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_DEBUG_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_FALSE);
        }
        
        if (genCfg->debugTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_DEBUG_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_DEBUG_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_FALSE);
        }
        
        if (genCfg->debugTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_DEBUG_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_DEBUG_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->debugTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_DEBUG_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_DEBUG_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_DEBUG_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData, MTP3_DEBUG_STRING,  ITS_FALSE); 
        }
    }

    if (genCfg->warningTrace)
    {
        TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData, MTP3_WARNING_STRING,  ITS_TRUE); 

        if (genCfg->warningTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_WARNING_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_WARNING_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_FALSE);
        }
        
        if (genCfg->warningTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_WARNING_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_WARNING_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_FALSE);
        }
        
        if (genCfg->warningTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_WARNING_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_WARNING_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_FALSE);
        }
        
        if (genCfg->warningTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_WARNING_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_WARNING_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_WARNING_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData, MTP3_WARNING_STRING,  ITS_FALSE); 
        }
    }

    if (genCfg->errorTrace)
    {
        TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData, MTP3_ERROR_STRING,  ITS_TRUE); 

        if (genCfg->errorTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_ERROR_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_ERROR_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_FALSE);
        }
        
        if (genCfg->errorTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_ERROR_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_ERROR_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_FALSE);
        }
        
        if (genCfg->errorTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_ERROR_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_ERROR_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_FALSE);
        }
        
        if (genCfg->errorTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_ERROR_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_ERROR_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_ERROR_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData, MTP3_ERROR_STRING,  ITS_FALSE); 
        }
    }

    if (genCfg->criticalTrace)
    {
        TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData, MTP3_CRITICAL_STRING,  ITS_TRUE); 

        if (genCfg->criticalTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_CRITICAL_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_CRITICAL_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_FALSE);
        }
        
        if (genCfg->criticalTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_CRITICAL_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_CRITICAL_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_FALSE);
        }
        
        if (genCfg->criticalTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_CRITICAL_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_CRITICAL_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_FALSE);
        }
        
        if (genCfg->criticalTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_CRITICAL_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_CRITICAL_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_CRITICAL_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData, MTP3_CRITICAL_STRING,  ITS_FALSE); 
        }
    }

    if (genCfg->eventTrace)
    {
        TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData, MTP3_EVENT_STRING,  ITS_TRUE); 

        if (genCfg->eventTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_EVENT_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_EVENT_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_FALSE);
        }
        
        if (genCfg->eventTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_EVENT_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_EVENT_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_FALSE);
        }
        
        if (genCfg->eventTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_EVENT_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_EVENT_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_FALSE);
        }
        
        if (genCfg->eventTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_EVENT_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_EVENT_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_EVENT_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData, MTP3_EVENT_STRING,  ITS_FALSE); 
        }
    }

    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Sets the MTP3 Behavior
 *
 *  Input Parameters:
 *      ITS_BOOLEAN        isStp
 *      ITS_BOOLEAN        handleSpareNic
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Void
 ****************************************************************************/
ITSSS7DLLAPI void
MTP3_OSS_SetBehavior_CCITT(ITS_BOOLEAN isStp, ITS_BOOLEAN handleSpareNic)
{
    BEHAVIORS_SetBehavior(&CCITT_MTP3_Behaviors, MTP3_B_stpFunction, isStp);
    MTP3_CCITT_HandleSpareNIC = handleSpareNic;    
}

/****************************************************************************
 *  Purpose:
 *      Gets the MTP3 Behavior
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      ITS_BOOLEAN*    isStp
 *      ITS_BOOLEAN*    handleSpareNic
 *
 *  Return Value:
 *      Void
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_GetBehavior_CCITT(ITS_BOOLEAN* isStp, ITS_BOOLEAN* handleSpareNic)
{
    if (isStp == NULL || handleSpareNic == NULL)
        return ITS_ENOMEM;

    *isStp = BEHAVIORS_GetBehavior(&CCITT_MTP3_Behaviors, MTP3_B_stpFunction);
    *handleSpareNic = MTP3_CCITT_HandleSpareNIC; 

    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Inhibits the link
 *
 *  Input Parameters:
 *      ITS_OCTET   linkSet
 *      ITS_OCTET   linkCode
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_InhibitLink_CCITT(ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkPtr ln;
    ITS_INT     ret = ITS_SUCCESS; 

    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
        MTP3_ERROR(("Link %d not found in Linkset %d\n", linkCode, linkSet));
        return ITS_ELINKNOTFOUND;
    }

    ret = MGMT_Main_CCITT(MTP3_USER,
                          MGMT_TRIGGER_INHIBIT_LINK,
                          NULL, 
                          0,
                          linkSet, 
                          linkCode);
    if (ret != ITS_SUCCESS)
    {
        MTP3_ERROR(("Link %d in linkset %d Inhibition error %d", linkCode, linkSet, ret));
        return ret;
    }

    MTP3_DEBUG(("Link %d in linkset %d Inhibited\n", linkCode, linkSet));
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Uninhibits the link
 *
 *  Input Parameters:
 *      ITS_OCTET   linkSet
 *      ITS_OCTET   linkCode
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_UninhibitLink_CCITT(ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkPtr ln;
    ITS_INT     ret = ITS_SUCCESS; 

    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
        MTP3_ERROR(("Link %d not found in Linkset %d\n", linkCode, linkSet));
        return ITS_ELINKNOTFOUND;
    }

    ret = MGMT_Main_CCITT(MTP3_USER,
                          MGMT_TRIGGER_UNINHIBIT_LINK,
                          NULL, 
                          0,
                          linkSet, 
                          linkCode);
    if (ret != ITS_SUCCESS)
    {
        MTP3_ERROR(("Link %d in linkset %d Uninhibition error %d", linkCode, linkSet, ret));
        return ret;
    }

    MTP3_DEBUG(("Link %d in linkset %d Uninhibited\n", linkCode, linkSet));
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Deactivates the link
 *
 *  Input Parameters:
 *      ITS_OCTET   linkSet
 *      ITS_OCTET   linkCode
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_DeactivateLink_CCITT(ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkPtr ln;
    ITS_INT     ret = ITS_SUCCESS; 

    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
        MTP3_ERROR(("Link %d not found in Linkset %d\n", linkCode, linkSet));
        return ITS_ELINKNOTFOUND;
    }

    ret = MGMT_Main_CCITT(MTP3_USER,
                          MGMT_TRIGGER_DEACTIVATE_LINK,
                          NULL, 
                          0,
                          linkSet, 
                          linkCode);
    if (ret != ITS_SUCCESS)
    {
        MTP3_ERROR(("Link %d in linkset %d Deactivation error %d", linkCode, linkSet, ret));
        return ret;
    }

    MTP3_DEBUG(("Link %d in linkset %d Deactivated\n", linkCode, linkSet));
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Activates the link
 *
 *  Input Parameters:
 *      ITS_OCTET   linkSet
 *      ITS_OCTET   linkCode
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_ActivateLink_CCITT(ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkPtr ln;
    ITS_INT     ret = ITS_SUCCESS; 

    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
        MTP3_ERROR(("Link %d not found in Linkset %d\n", linkCode, linkSet));
        return ITS_ELINKNOTFOUND;
    }

    ret = MGMT_Main_CCITT(MTP3_USER,
                          MGMT_TRIGGER_ACTIVATE_LINK,
                          NULL, 
                          0,
                          linkSet, 
                          linkCode);
    if (ret != ITS_SUCCESS)
    {
        MTP3_ERROR(("Link %d in linkset %d Activation error %d", linkCode, linkSet, ret));
        return ret;
    }

    MTP3_DEBUG(("Link %d in linkset %d Activated\n", linkCode, linkSet));
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Deactivates the linkset
 *
 *  Input Parameters:
 *      ITS_OCTET   linkSet
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_DeactivateLinkset_CCITT (ITS_OCTET linkSet)
{
    SS7_LinkSetPtr  ls;
    ITS_INT         ret = ITS_SUCCESS; 

    if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
    {
        MTP3_ERROR(("Linkset %d not found\n", linkSet));
        return ITS_ELINKSETNOTFOUND;
    }

    ret = MGMT_Main_CCITT(MTP3_USER,
                          MGMT_TRIGGER_DEACTIVATE_LINK_SET,
                          NULL, 
                          0,
                          linkSet, 
                          ITS_SS7_DEFAULT_LINK_CODE);
    if (ret != ITS_SUCCESS)
    {
        MTP3_ERROR(("Linkset %d Deactivation error %d", linkSet, ret));
        return ret;
    }

    MTP3_DEBUG(("Linkset %d Deactivated\n", linkSet));
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Activates the linkset
 *
 *  Input Parameters:
 *      ITS_OCTET       linkSet
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_ActivateLinkset_CCITT (ITS_OCTET linkSet)
{
    SS7_LinkSetPtr  ls;
    ITS_INT         ret = ITS_SUCCESS; 

    if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
    {
        MTP3_ERROR(("Linkset %d not found\n", linkSet));
        return ITS_ELINKSETNOTFOUND;
    }

    ret = MGMT_Main_CCITT(MTP3_USER,
                          MGMT_TRIGGER_ACTIVATE_LINK_SET,
                          NULL, 
                          0,
                          linkSet, 
                          ITS_SS7_DEFAULT_LINK_CODE);
    if (ret != ITS_SUCCESS)
    {
        MTP3_ERROR(("Linkset %d Activation error %d", linkSet, ret));
        return ret;
    }

    MTP3_DEBUG(("Linkset %d Activated\n", linkSet));
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Gets the configured linksets
 *
 *  Input Parameters:
 *      ITS_OCTET   linkSet
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Void
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_GetLinkset_CCITT(ITS_OCTET linkSet, SS7_LinkSetInfo* linkSetInfoPtr, ITS_OCTET* numLinksets)
{
    SS7_LinkSetPtr  ls = NULL;
    ITS_OCTET       index;

    if (linkSetInfoPtr == NULL || numLinksets == NULL)
        return ITS_ENOMEM;

    if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
    {
        if (DSM_LockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("Couldn't acquire lock\n"));
            return ITS_EBADMUTEX;
        }

        (*numLinksets) = 0;
        for (index = 0; index < ITS_SS7_DEFAULT_LINK_SET; index++)
        {
            ls = LINKSET_FindLinkSet(index);
            if (ls)
            {
                linkSetInfoPtr->linkSet    = ls->linkSet;
                linkSetInfoPtr->lpc        = ls->lpc;
                linkSetInfoPtr->adjacent   = ls->adjacent;
                linkSetInfoPtr->ni         = ls->ni;
                linkSetInfoPtr->family     = ls->family;
                linkSetInfoPtr->numLinks   = ls->numLinks;
                linkSetInfoPtr->adjSTP     = ls->adjSTP;
                linkSetInfoPtr->isUp       = ls->isUp;

                linkSetInfoPtr++;
                (*numLinksets)++;
            }
        }

        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);
    }
    else
    {
        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Linkset %d not found", linkSet));
            return ITS_ELINKSETNOTFOUND;
        }

        (*numLinksets) = 1;
        linkSetInfoPtr->linkSet    = ls->linkSet;
        linkSetInfoPtr->lpc        = ls->lpc;
        linkSetInfoPtr->adjacent   = ls->adjacent;
        linkSetInfoPtr->ni         = ls->ni;
        linkSetInfoPtr->family     = ls->family;
        linkSetInfoPtr->numLinks   = ls->numLinks;
        linkSetInfoPtr->adjSTP     = ls->adjSTP;
        linkSetInfoPtr->isUp       = ls->isUp;
    }

    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Gets the link information
 *
 *  Input Parameters:
 *      ITS_OCTET   linkSet
 *      ITS_OCTET   linkCode
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Void
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_GetLink_CCITT(ITS_OCTET linkSet, ITS_OCTET linkCode, SS7_LinkInfo* linkInfoPtr)
{
    SS7_LinkPtr  link = NULL ;

    if (linkInfoPtr == NULL)
        return ITS_ENOMEM;

    memset(linkInfoPtr, 0, sizeof(SS7_LinkInfo));

    link = LINK_FindLink(linkSet, linkCode);
    if (link == NULL)
    {
        MTP3_ERROR(("Link %d not found in Linkset %d\n", linkCode, linkSet));
        return ITS_ELINKNOTFOUND;
    }

    linkInfoPtr->linkSet    = link->linkSet->linkSet;
    linkInfoPtr->linkCode   = link->linkCode;
    linkInfoPtr->family     = link->family;
    linkInfoPtr->id         = link->id;
    linkInfoPtr->initActive = link->initActive;
    linkInfoPtr->localLink  = link->localLink;
    linkInfoPtr->priority   = link->priority ;
    linkInfoPtr->isUp       = link->isUp;
    linkInfoPtr->isAllowed  = link->isAllowed;
    linkInfoPtr->active     = link->active;
    linkInfoPtr->congLevel  = link->congLevel;
    linkInfoPtr->availableState = link->availableState;
    linkInfoPtr->testPassed = link->testPassed;

    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Gets the MTP3 global pegs
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Void
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
MTP3_OSS_GetGeneralPegs_CCITT(MTP3_GenPegs* globalPegs)
{
    if (globalPegs == NULL)
        return ITS_ENOMEM;

    globalPegs->msgPause             = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_PAUSE);
    globalPegs->msgResume            = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_RESUME);
    globalPegs->msgStatus            = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_STATUS);
    globalPegs->initialize           = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_INITIALIZE);
    globalPegs->terminate            = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_TERMINATE);
    globalPegs->msgReceivedInError   = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_RECEIVED_INERROR);
    globalPegs->changeover           = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_CHANGEOVER);
    globalPegs->changeback           = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_CHANGEBACK);
    globalPegs->slUnavailable        = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_SL_UNAVAILABLE);
    globalPegs->linkInhibit          = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_INHIBIT);
    globalPegs->linkUnInhibit        = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_UNINHIBIT);
    globalPegs->linkforceUninhibit   = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_FORCE_UNINHIBIT);
    globalPegs->congestion           = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_CONGESTION);
    globalPegs->slsUnavailable       = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_SLS_UNAVAILABLE);
    globalPegs->tfcReceived          = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_TFC_RECEIVED);
    globalPegs->tfaReceived          = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_TFA_RECEIVED);
    globalPegs->routesetUnavailable  = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_ROUTESET_UNAVAILABLE);
    globalPegs->adjacentSpUnaccesible= PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_ADJECENT_SP_UNACCESIBLE);
    globalPegs->userpartEnable       = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_USERPART_ENABLE);
    globalPegs->userpartDisable      = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_USERPART_DISABLE);

    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Gets the MTP3 link pegs for the specified link
 *
 *  Input Parameters:
 *      ITS_OCTET       linkSet
 *      ITS_OCTET       linkCode
 *
 *  Output Parameters:
 *      MTP3_LinkPegs*  linkPegs
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_GetLinkPegs_CCITT(ITS_OCTET linkSet, ITS_OCTET linkCode, MTP3_LinkPegs* linkPegs)
{
    SS7_LinkPtr ln = NULL;

    if (linkPegs == NULL)
        return ITS_ENOMEM;

    ln = LINK_FindLinkNoLock(linkSet, linkCode);
    if (ln == NULL)
    {
        MTP3_ERROR(("Link %d not found in Linkset %d\n", linkCode, linkSet));
        return ITS_ELINKNOTFOUND;
    }

    linkPegs->cooTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COO_TX);
    linkPegs->cooRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COO_RX);
    linkPegs->coaTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COA_TX);
    linkPegs->coaRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COA_RX);
    linkPegs->ecoTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECO_TX);
    linkPegs->ecoRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECO_RX);
    linkPegs->ecaTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECA_TX);
    linkPegs->ecaRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECA_RX);
    linkPegs->cbdTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBD_TX);
    linkPegs->cbdRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBD_RX);
    linkPegs->cbaTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBA_TX);
    linkPegs->cbaRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBA_RX);
    linkPegs->linTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIN_TX);
    linkPegs->linRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIN_RX);
    linkPegs->liaTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIA_TX);
    linkPegs->liaRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIA_RX);
    linkPegs->lunTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_TX);
    linkPegs->lunRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_RX);
    linkPegs->luaTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUA_TX);
    linkPegs->luaRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUA_RX);
    linkPegs->lidTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LID_TX);
    linkPegs->lidRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LID_RX);
    linkPegs->lfuTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LFU_TX);
    linkPegs->lfuRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LFU_RX);
    linkPegs->lliTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LLI_TX);
    linkPegs->lliRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LLI_RX);
    linkPegs->lriTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LRI_TX);
    linkPegs->lriRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LRI_RX);
    linkPegs->dlcTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_DLC_TX);
    linkPegs->dlcRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_DLC_RX);
    linkPegs->cssTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CSS_TX);
    linkPegs->cssRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CSS_RX);
    linkPegs->cnsTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNS_TX);
    linkPegs->cnsRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNS_RX);
    linkPegs->cnpTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNP_TX);
    linkPegs->cnpRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNP_RX);
    linkPegs->upuTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_UPU_TX);
    linkPegs->upuRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_UPU_RX);
    linkPegs->sltmTx    = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTM_TX);
    linkPegs->sltmRx    = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTM_RX);
    linkPegs->sltaTx    = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTA_TX);
    linkPegs->sltaRx    = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTA_RX);

    return ITS_SUCCESS; 
}

/****************************************************************************
 *  Purpose:
 *      Gets the MTP3 DPC pegs for the specified dpc 
 *
 *  Input Parameters:
 *      ITS_UINT      dpc 
 *      ITS_UINT      ni 
 *
 *  Output Parameters:
 *      MTP3_DpcPegs*  routePegs
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
MTP3_OSS_GetDpcPegs_CCITT(ITS_UINT pc, ITS_UINT ni, MTP3_RoutePegs* routePegs)
{
    SS7_Destination* dest;


    if ((dest = ROUTE_FindDestination(pc, ni, FAMILY_ITU)) == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    if ((*dest->entries)->basic.type == LOCAL_ROUTE)
    {
        return (ITS_ENOTFOUND);
    }

    routePegs->tfaTx = PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFA_TX);
    routePegs->tfaRx = PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFA_RX);
    routePegs->tfpTx = PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFP_TX);
    routePegs->tfpRx = PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFP_RX);
    routePegs->rstTx = PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_RST_TX);
    routePegs->rstRx = PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_RST_RX);
    routePegs->tfrRx = PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFR_RX);
    routePegs->tfcTx = PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFC_TX);
    routePegs->tfcRx = PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFC_RX);
    routePegs->sifTx = PEG_GetPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_SIF_TX);

    return (ITS_SUCCESS);

}

/****************************************************************************
 *  Purpose:
 *      Clears the MTP3 global pegs
 *
 *  Input Parameters:
 *      ITS_UINT    pegId
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Void
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_ClearGeneralPeg_CCITT(ITS_UINT pegId)
{
    if (pegId == MTP3_ALL_PEGS)
    {
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_INITIALIZE);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_TERMINATE);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_RESTART);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_PAUSE); 
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_RESUME);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_STATUS);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_OUT_OF_SERVICE);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_IN_SERVICE);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_CHANGEOVER);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_EMER_CHANGEOVER);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_CHANGEBACK);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_INHIBIT);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_INHIBIT_DNY);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_UNINHIBIT);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_FORCE_UNINHIBIT);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_BLOCK);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_UNBLOCK);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_ACTIVATION);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_DEACTIVATION);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_CONGESTION_DETECT);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSU_TX);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSU_RX);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_SLTM_TX);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_SLTM_RX);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_SLTA_TX);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_SLTA_RX);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_SLT_PASSED);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_SLT_FAILED);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_TFP_TX);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_TFP_RX);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_TFA_TX);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_TFA_RX);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_REMOTE_ROUTE_FAILURE );
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_USERPART_ROUTE_FAILURE );
    }
    else
    {
        if (pegId > PEG_MTP3_NUM_PEGS_CCITT)
        {
            MTP3_ERROR(("Peg Id %d not found\n", pegId));
            return ITS_ENOTFOUND;
        }
        else
        {
            PEG_ClearPeg(CCITT_MTP3_Pegs, pegId);
        }
    }

    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Clears the MTP3 link pegs
 *
 *  Input Parameters:
 *      ITS_OCTET       linkSet
 *      ITS_OCTET       linkCode
 *      ITS_UINT        pegId   
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Void
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_ClearLinkPeg_CCITT(ITS_OCTET linkSet, ITS_OCTET linkCode, ITS_UINT pegId)
{
    SS7_LinkPtr ln = NULL;

    ln = LINK_FindLinkNoLock(linkSet, linkCode);
    if (ln == NULL)
    {
        MTP3_ERROR(("Link %d not found in Linkset %d\n", linkCode, linkSet));
        return ITS_ELINKNOTFOUND;
    }

    if (pegId == MTP3_ALL_PEGS)
    {
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COO_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COO_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COA_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COA_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECO_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECO_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECA_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECA_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBD_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBD_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBA_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBA_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIN_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIN_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIA_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIA_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUA_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUA_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LID_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LID_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LFU_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LFU_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LLI_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LLI_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LRI_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LRI_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_DLC_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_DLC_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CSS_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CSS_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNS_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNS_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNP_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNP_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_UPU_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_UPU_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTM_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTM_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTA_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTA_RX);
    }
    else
    {
        if (pegId > PEG_MTP3_NUM_LINK_PEGS)
        {
            MTP3_ERROR(("Peg Id %d not found\n", pegId));
            return ITS_ENOTFOUND;
        }
        else
        {
            PEG_ClearPeg(&ln->MTP3_LINK_PEGS, pegId);
        }
    }
    
    return ITS_SUCCESS;
}

/****************************************************************************
 *
 *  Purpose:
 *      Clears the MTP3 Route pegs
 *
 *  Input Parameters:
 *      ITS_UINT      pc
 *      ITS_UINT      ni
 *      ITS_UINT      pegId
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Void
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
MTP3_OSS_ClearDpcPeg_CCITT(ITS_UINT pc, ITS_UINT ni, ITS_UINT pegId)
{

    SS7_Destination* dest;

    if ((dest = ROUTE_FindDestination(pc, ni, FAMILY_ITU)) == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    if ((*dest->entries)->basic.type == LOCAL_ROUTE)
    {
        return (ITS_ENOTFOUND);
    }

    if (pegId == MTP3_ALL_PEGS)
    {
        PEG_ClearPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFA_TX);
        PEG_ClearPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFA_RX);
        PEG_ClearPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFP_TX);
        PEG_ClearPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFP_RX);
        PEG_ClearPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_RST_TX);
        PEG_ClearPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_RST_RX);
        PEG_ClearPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFR_RX);
        PEG_ClearPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFC_TX);
        PEG_ClearPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFC_RX);
        PEG_ClearPeg(&dest->MTP3_DPC_PEGS, PEG_MTP3_DPC_SIF_TX);
    }
    else
    {
        if (pegId > PEG_MTP3_NUM_DPC_PEGS)
        {
            MTP3_ERROR(("Peg Id %d not found\n", pegId));
            return ITS_ENOTFOUND;
        }
        else
        {
            PEG_ClearPeg(&dest->MTP3_DPC_PEGS, pegId);
        }
    }

    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Adds a specified linkset
 *
 *  Input Parameters:
 *      ITS_OCTET       linkSet
 *      SS7_Family      family
 *      ITS_UINT        lpc
 *      ITS_UINT        apc
 *      ITS_OCTET       ni
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Void
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
MTP3_OSS_AddLinkset_CCITT(ITS_OCTET linkSet, SS7_Family family, ITS_UINT lpc, ITS_UINT apc, ITS_UINT ni)
{
    ITS_INT         ret;
    SS7_LinkSetPtr  ls;
    SS7_LinkSet      linkset;

    ls = LINKSET_FindLinkSet(linkSet);
    if (ls != NULL)
    {
        MTP3_ERROR(("Linkset %d already exists\n", linkSet));
        return ADD_ASSOCIATIONSET_ERR_ALREADY_PRESENT;
    }

    memset(&linkset, 0, sizeof(SS7_LinkSet));
    linkset.linkSet     = linkSet;
    linkset.adjacent    = apc;
    linkset.lpc         = lpc;
    linkset.ni          = ni & ROUTE_NI_MASK;
    linkset.numLinks    = 0;
    linkset.numToStart  = 0;
    linkset.isUp        = ITS_FALSE;
    linkset.firstLink   = ITS_TRUE; 
    linkset.family      = family;

    ret = LINKSET_AddLinkSet(&linkset);
    if (ret == ITS_EBADMUTEX || ret == ITS_ENOMEM)
    {
        MTP3_ERROR(("Linkset %d Addition Error %d\n", linkSet, ret));
        return ADD_ASSOCIATIONSET_ERR_FAILED_AT_BACKEND;
    }
    else if(ret != ITS_SUCCESS)
    {
        MTP3_ERROR(("Linkset %d Addition Error %d\n", linkSet, ret));
        return ret;
    }

    printf("\nAddLinkSet: firstLink value is %d for linkset %d\n", linkset.firstLink, linkSet);

    MTP3_DEBUG(("Linkset %d Added\n", linkSet));
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Deletes the specified linkset
 *
 *  Input Parameters:
 *      ITS_OCTET       linkSet
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Void
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_RemoveLinkset_CCITT(ITS_OCTET linkSet)
{
    ITS_INT        ret;
    SS7_LinkSetPtr  ls;

    ls = LINKSET_FindLinkSet(linkSet);
    if (ls == NULL)
    {
        MTP3_ERROR(("Linkset %d not found\n", linkSet));
        //return ITS_ELINKSETNOTFOUND;
        return DEL_ASSOCIATIONSET_ERR_NO_PRESENT;
    }

    if (ls->numLinks != 0)
    {
        MTP3_ERROR(("Links exist in linkset %d\n", linkSet));
        //return ITS_ELINKSEXIST;
        return DEL_ASSOCIATIONSET_ERR_IS_ASSOCIATED;
    }

    ret = LINKSET_RemLinkSet(ls);
    if (ret != ITS_SUCCESS)
    {
        MTP3_ERROR(("Linkset %d Deletion Error %d\n", linkSet, ret));
        //return ret;
        return DEL_ASSOCIATIONSET_ERR_FAILED_AT_BACKEND;
    }

    MTP3_DEBUG(("Linkset %d Deleted\n", linkSet));
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Adds the specified linkcode to the linkset
 *
 *  Input Parameters:
 *      ITS_OCTET       linkSet
 *      ITS_OCTET       linkCode
 *      ITS_UINT        transId
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_AddLink_CCITT(ITS_OCTET linkSet, ITS_OCTET linkCode, ITS_UINT transId)
{
    ITS_INT             ret;
    SS7_LinkPtr         lp;
    SS7_LinkSetPtr      ls;
    TRANSPORT_Control   *tc;
    SS7_Link            ln;

    ENGINE_LinkPart engLink;
    ENGINE_ThreadPool wp;
    ENGINE_Transport tp = NULL;
    ITS_Object retn;
    ITS_Object *list = NULL; 
    ITS_BOOLEAN haveSet = ITS_FALSE, haveCode = ITS_FALSE,
                havePri = ITS_FALSE;

    tc = TRANSPORT_FindTransport(transId);
    if (tc == NULL)
    {
        MTP3_ERROR(("Transport %d not found\n", transId));
        //return ITS_ENOTRANSPORT;
        return ADD_ASSOCIATION_ERR_TRANSPORT_INSTANCE_NOT_FOUND;
    }

    ls = LINKSET_FindLinkSet((ITS_OCTET) linkSet);
    if (ls == NULL)
    {
        MTP3_ERROR(("Linkset %d not found\n", linkSet));
        //return ITS_ELINKSETNOTFOUND;
        return ADD_ASSOCIATION_ERR_LINKSET_NOT_FOUND;
    }

    lp = LINK_FindLink((ITS_OCTET) linkSet, (ITS_OCTET) linkCode);
    if (lp != NULL)
    {
        MTP3_ERROR(("Link %d already exists in linkset %d\n", linkCode, linkSet));
        //return ITS_EDUPLENTRY;
        return ADD_ASSOCIATION_ERR_ALREADY_PRESENT;
    }

    memset(&ln, 0, sizeof(SS7_Link));
    ln.initActive   = ITS_TRUE;
    ln.termFixed    = ITS_TRUE;
    ln.linkFixed    = ITS_TRUE;
    ln.isSAAL       = ITS_FALSE;
    ln.next         = NULL;
    ln.prev         = NULL; 
    ln.isUp         = ITS_FALSE;
    ln.isAllowed    = ITS_TRUE;
    ln.linkCode     = (ITS_OCTET) linkCode;
    ln.id           = transId;
    ln.dsmNodeId    = DSM_GetNodeId();
    ln.family       = ls->family;

    ret = LINK_AddLink(linkSet, &ln);
    if (ret != ITS_SUCCESS)
    {
        MTP3_ERROR(("Link %d in linkset %d Addition Error %d\n", linkCode, linkSet, ret));
        //return ret;
        return ADD_ASSOCIATION_ERR_FAILED_AT_BACKEND;
    }

    lp = LINK_FindLink((ITS_OCTET) linkSet, (ITS_OCTET) linkCode);
    if (lp == NULL)
    {
        MTP3_ERROR(("Link %d in linkset %d not found after addition\n", linkCode, linkSet));
        //return ITS_ELINKNOTFOUND;
        return ADD_ASSOCIATION_ERR_ASSOCIATION_NOT_FOUND_IN_ASSOCIATIONSET_AFTER_ADDITION;
    }

    LINK_AddLinkInfoToTransport(tc, lp);

    wp = (ENGINE_ThreadPool)ENGINE_APP_POOLS(application);

    while (wp != NULL)
    {
        if (ENGINE_TP_TYPE(wp) == TP_BORDERS)
        {
            tp = (ENGINE_Transport)ENGINE_TP_TRANSPORTS(wp);
            list = &(tp->transport.links);
        }
        wp = (ENGINE_ThreadPool)ENGINE_TP_NEXT(wp);
    }

    memset(&engLink, 0, sizeof(ENGINE_LinkPart));

    engLink.linkSet = (ITS_OCTET)linkSet;
    haveSet = ITS_TRUE;
    engLink.linkCode = (ITS_OCTET)linkCode; 
    haveCode = ITS_TRUE;
    engLink.linkPri = 0;
    havePri = ITS_TRUE;
    engLink.initActive = ITS_TRUE;
    engLink.termFixed = ITS_TRUE;
    engLink.linkFixed = ITS_TRUE;
    engLink.terminal = 0;
    engLink.circuit = (ITS_USHORT)ln.dataLink;
    engLink.isSAAL = ln.isSAAL;
    engLink.isLocal = ITS_FALSE; 
    engLink.family = ls->family;

    ITS_C_ASSERT(haveSet && haveCode && havePri);

    retn = ITS_ConstructObject(itsENGINE_LinkClass, list,
            engLink.linkSet, engLink.linkCode,
            engLink.linkPri, engLink.initActive, 
            engLink.termFixed, engLink.linkFixed,
            engLink.terminal, engLink.circuit,
            engLink.isSAAL, engLink.isLocal,
            engLink.family);

    MTP3_DEBUG(("Link %d in linkset %d Added\n", linkCode, linkSet));
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Deletes the specified linkcode from the linkset
 *
 *  Input Parameters:
 *      ITS_OCTET       linkSet
 *      ITS_OCTET       linkCode
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_RemoveLink_CCITT(ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    ITS_INT         ret;
    SS7_LinkPtr     lp;
    SS7_LinkSetPtr  ls;

    ls = LINKSET_FindLinkSet(linkSet);
    if (ls == NULL)
    {
        MTP3_ERROR(("Linkset %d not found\n", linkSet));
        return ITS_ELINKSETNOTFOUND;
    }

    lp = LINK_FindLink(linkSet, linkCode);
    if (lp == NULL)
    {
        MTP3_ERROR(("Link %d in linkset %d not found\n", linkCode, linkSet));
        return ITS_ELINKNOTFOUND;
    }

    ret = LINK_RemLink(linkSet, lp);
    if (ret != ITS_SUCCESS)
    {
        MTP3_ERROR(("Link %d in linkset %d Deletion error %d\n", linkCode, linkSet, ret));
        return ret;
    }

    MTP3_DEBUG(("Link %d in linkset %d Deleted\n", linkCode, linkSet));
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Adds the specified remote point code
 *
 *  Input Parameters:
 *      ITS_UINT        rpc
 *      ITS_OCTET       ni
 *      ITS_OCTET       linkSet
 *      ITS_OCTET       family
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_AddRemotePC_CCITT(ITS_UINT rpc, ITS_OCTET sio,ITS_OCTET ssn,  ITS_OCTET linkSet, ITS_OCTET priority, SS7_Family family)
{
    ITS_INT         ret;
    SS7_LinkSetPtr  ls;
    SS7_LinkPtr     lp;
    ROUTE_MatchInfo rinfo;
    ITS_OCTET       linkCode;

    memset(&rinfo, 0, sizeof(rinfo));

    ls = LINKSET_FindLinkSet(linkSet);
    if (ls != NULL)
    {
        for (linkCode = 0 ; linkCode < MAX_LINKS ; linkCode++)
        {
            lp = LINK_FindLink((ITS_OCTET) linkSet, (ITS_OCTET) linkCode);
            if (lp != NULL)
            {
                /* link exist for this linkset ,So proceed */
                break ;
            }
        }
        if ( linkCode == MAX_LINKS )
        {
            MTP3_ERROR(("Link not found Linkset %d\n", linkSet));
            //return ITS_ELINKNOTFOUND;
            return ADD_ROUTE_ERR_ASSOCIATION_NOT_PRESENT;
        }
    }
    else
    {
        MTP3_ERROR(("Linkset %d not found\n", linkSet));
        //return ITS_ELINKSETNOTFOUND;
        return ADD_ROUTE_ERR_ASSOCIATION_SET_NOT_PRESENT;
    }

    rinfo.basic.type    = REMOTE_ROUTE;
    rinfo.basic.family  = family;
    rinfo.basic.style   = ROUTE_DPC_SIO_SSN;
    rinfo.basic.dpc     = rpc;
    rinfo.basic.mask    = ITS_SS7_DEFAULT_ROUTE_MASK;
    rinfo.basic.criteria.sio = sio;
    rinfo.basic.criteria.ssn = ssn;

    rinfo.linkSet   = linkSet;
    rinfo.linkCode  = 0;
    rinfo.priority  = priority;
    rinfo.sls       = 0;
    rinfo.rkey      = 0;
    rinfo.basic.mask = ITS_SS7_DEFAULT_ROUTE_MASK;

    ret = ROUTE_AddRouteContextInfo(&rinfo);
    if (ret != ITS_SUCCESS)
    {
        MTP3_ERROR(("Route Addition error %d\n", ret));
        //return ret;
        return ADD_ROUTE_ERR_GENERIC_ERROR;
    }

    MTP3_DEBUG(("RPC %d Added\n", rpc));
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Removes the specified remote point code
 *
 *  Input Parameters:
 *      ITS_UINT        rpc
 *      ITS_OCTET       ni
 *      ITS_OCTET       linkSet
 *      ITS_OCTET       family
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_RemoveRemotePC_CCITT(ITS_UINT rpc, ITS_OCTET sio, ITS_OCTET ssn, ITS_OCTET linkSet, ITS_OCTET priority, SS7_Family family)
{
    ITS_INT             ret;
    SS7_LinkSetPtr      ls;
    SS7_Destination     *rc;
    ROUTE_MatchInfo     rinfo;

    ls = LINKSET_FindLinkSet(linkSet);
    if (ls == NULL)
    {
        MTP3_ERROR(("Linkset %d not found\n", linkSet));
        //return ITS_ELINKSETNOTFOUND;
        return DEL_ROUTE_ERR_ASSOCIATION_SET_NOT_PRESENT;
    }

    rc = ROUTE_FindDestination(rpc, sio, family);
    if (rc == NULL)
    {
        MTP3_ERROR(("Destination with RPC %d not found\n", rpc));
        //return ITS_ENODESTINATION;
        return DEL_ROUTE_ERR_DESTINATION_NOT_PRESENT;
    }

    rinfo.basic.type    = REMOTE_ROUTE;
    rinfo.basic.family  = family;
    rinfo.basic.style   = ROUTE_DPC_SIO_SSN;
    rinfo.basic.dpc     = rpc;
    rinfo.basic.mask    = ITS_SS7_DEFAULT_ROUTE_MASK;
    //rinfo.basic.criteria.sio = (ITS_OCTET)ni & ROUTE_NI_MASK;
    rinfo.basic.criteria.sio = sio;
    rinfo.basic.criteria.ssn = ssn;
    rinfo.linkSet   = (ITS_OCTET) linkSet;
    rinfo.linkCode  = 0;
    rinfo.priority  = priority;
    rinfo.sls       = 0;
    rinfo.rkey      = 0;

    ret = ROUTE_DeleteRouteContextInfo(&rinfo);
    if (ret != ITS_SUCCESS)
    {
        MTP3_ERROR(("Destination with RPC %d Deletion error %d\n", rpc, ret));
        return ret;
    }

    MTP3_DEBUG(("RPC %d Deleted\n", rpc));
    return ITS_SUCCESS;
}

ITSSS7DLLAPI ITS_INT
MTP3_OSS_GetRemoteRoute_CCITT(ITS_UINT pointCode, ITS_OCTET sio, SS7_Family family, SS7_Destination** ss7Dest)
{
    *ss7Dest = ROUTE_FindDestination(pointCode, sio, family);
    if(*ss7Dest == NULL)
    {
        return !ITS_SUCCESS;
    }
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Gets all the remote point codes configured
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      SS7_DestInfo*   remPc
 *      ITS_OCTET*      numDests
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_GetRemotePC_CCITT(SS7_DestInfo *remPc, ITS_OCTET* numDests)
{
    ITS_INT     ret;

    if (remPc == NULL || numDests == NULL)
        return ITS_ENOMEM;

    *numDests = 0;
    ret = DSM_TableIterate(DSM_RoutingFtGroupId, 
                           DSM_TABLE_DESTINATIONS, 
                           remPc, 
                           numDests, 
                           GetRemotePointCodeData);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Adds the specified local point code
 *
 *  Input Parameters:
 *      ITS_UINT        rpc
 *      ITS_OCTET       ni
 *      ITS_OCTET       linkSet
 *      ITS_OCTET       family
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_AddRoutingKeyroutePC_CCITT(ITS_UINT lpc, ITS_OCTET sio, ITS_OCTET ssn, ITS_UINT rkey, SS7_Family family)
{
    ITS_INT         ret;
    ROUTE_MatchInfo rinfo;

    memset(&rinfo, 0, sizeof(rinfo));

    rinfo.basic.type    = ROUTING_KEY_ROUTE;
    rinfo.basic.family  = family;
    rinfo.basic.style   = ROUTE_DPC_SIO_SSN;
    rinfo.basic.dpc     = lpc;
    rinfo.basic.mask    = ITS_SS7_DEFAULT_ROUTE_MASK;
    rinfo.basic.criteria.sio = sio;
    rinfo.basic.criteria.ssn = ssn;

    rinfo.linkSet   = 0;
    rinfo.linkCode  = 0;
    rinfo.priority  = 0;
    rinfo.sls       = 0;
    rinfo.rkey      = rkey;
    rinfo.basic.mask = ITS_SS7_DEFAULT_ROUTE_MASK;

    ret = ROUTE_AddRoutingKeyInfo(rkey, &rinfo);
    if (ret != ITS_SUCCESS)
    {
        MTP3_ERROR(("Route Addition error %d\n", ret));
        return ADD_ROUTINGKEYROUTE_ERR_FAILED_AT_BACKEND;
    }

    MTP3_DEBUG(("LPC RoutingKeyRoute %d Added\n", lpc));
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Removes the specified remote point code
 *
 *  Input Parameters:
 *      ITS_UINT        rpc
 *      ITS_OCTET       ni
 *      ITS_OCTET       linkSet
 *      ITS_OCTET       family
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_RemoveRoutingKeyRoute_CCITT(ITS_UINT rkey)
{
    int ret = ITS_SUCCESS;
    ret = ROUTE_DeleteRoutingKey(rkey);
    if (ret != ITS_SUCCESS)
    {
        MTP3_ERROR(("Route with RoutingKey %d Deletion error %d\n", rkey, ret));
        return ret;
    }

    MTP3_DEBUG(("RoutingKeyRoute %d Deleted\n", rkey));
    return ITS_SUCCESS;
}

ITSSS7DLLAPI ITS_INT
SetBorderPoolTransport_CCITT(char *name, char *type, char *family,char *modifier, 
        ENGINE_TransportSpecificsPart bSpecs)
{
    int retVal = ITS_SUCCESS;
    ENGINE_TransportCallbacksPart bCBS;
    memset(&bCBS, 0, sizeof(ENGINE_TransportCallbacksPart));
    retVal = ENGINE_AddTransport(name, type, family, modifier, bSpecs, &bCBS);
    if(retVal == ITS_ENOMEM)
    {
        MTP3_ERROR(("Transport Creation Failed ..!!"));
        return retVal;
    }
    return retVal;
}

ITSSS7DLLAPI ITS_INT
DeleteBorderPoolTransport_CCITT(ITS_UINT transportId)
{
    int retVal = ITS_SUCCESS;
    retVal = ENGINE_DeleteTransport(transportId);
    if (retVal != ITS_SUCCESS)
    {
        MTP3_ERROR(("Transport Deletion Failed"));
        return retVal;
    }
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Gets all the remote point codes configured
 *
 *  Input Parameters:
 *      ITS_POINTER        data
 *
 *  Output Parameters:
 *      void*       in
 *      void*       out
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
static int 
GetRemotePointCodeData(ITS_POINTER data, void *in, void *out)
{
    SS7_DestInfo*       destInfo = (SS7_DestInfo*)in;
    ITS_OCTET*          numDests = (ITS_OCTET*)out;
    SS7_Destination*    ss7Context = (SS7_Destination*)data;
    ITS_OCTET           i, j;
    ITS_OCTET           index;

    for (i = 0; i < ss7Context->numEntries; i++)
    {
        if (ss7Context->entries[i]->basic.type == REMOTE_ROUTE)
        {
            for (j = 0 ; j < i ;j++)
            {
                if (ss7Context->entries[i]->basic.dpc ==
                                  ss7Context->entries[j]->basic.dpc )
                {
                    return ITS_SUCCESS;
                }
            }

            index = *numDests;
            (destInfo + index)->dpc = ss7Context->entries[i]->basic.dpc;    
            (destInfo + index)->family = ss7Context->entries[i]->basic.family;
            (destInfo + index)->sio = ss7Context->entries[i]->basic.criteria.sio;
            (destInfo + index)->status = ss7Context->status;

            (*numDests)++;
        }
    }
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Gets all the local point codes configured
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      SS7_DestInfo*   localPc
 *      ITS_OCTET*      numDests
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_GetLocalPC_CCITT(SS7_DestInfo *localPc, ITS_OCTET* numDests)
{
    ITS_INT     ret;

    if (localPc == NULL || numDests == NULL)
        return ITS_ENOMEM;

    *numDests = 0;
    ret = DSM_TableIterate(DSM_RoutingFtGroupId, 
                           DSM_TABLE_DESTINATIONS, 
                           localPc, 
                           numDests, 
                           GetLocalPointCodeData);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Gets all the local point codes configured
 *
 *  Input Parameters:
 *      ITS_POINTER        data
 *
 *  Output Parameters:
 *      void*   in
 *      void*   out
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
static int 
GetLocalPointCodeData(ITS_POINTER data, void *in, void *out)
{
    SS7_DestInfo*       destInfo = (SS7_DestInfo*)in;
    ITS_OCTET*          numDests = (ITS_OCTET*)out;
    SS7_Destination*    ss7Context = (SS7_Destination*)data;
    ITS_OCTET           i, j;
    ITS_OCTET           index;

    for (i = 0; i < ss7Context->numEntries; i++)
    {
        if (ss7Context->entries[i]->basic.type == LOCAL_ROUTE)
        {
            for (j = 0 ; j < i ;j++)
            {
                if (ss7Context->entries[i]->basic.dpc ==
                                            ss7Context->entries[j]->basic.dpc )
                {
                    return ITS_SUCCESS;
                }
            }

            index = *numDests;
            (destInfo + index)->dpc = ss7Context->entries[i]->basic.dpc;    
            (destInfo + index)->family = ss7Context->entries[i]->basic.family;

            (*numDests)++;
        }
    }
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      To ShutDown MTP3 Node.
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Void
 ****************************************************************************/
void static
NodeShutDown()
{
    TRANSPORT_Manager *tm;
    TRANSPORT_Control *tr;
    ITS_UINT mask;

    tm = TRANSPORT_GetManager();

    if (RWLOCK_LockShared(&tm->transportGate) != ITS_SUCCESS)
    {
         return ;
    }

    for ( tr = tm->listHead;
          tr != NULL; tr = TRANSPORT_HMI_NEXT(tr))
    {
        mask = TRANSPORT_MASK(tr);

        if ((mask & ITS_MTP2_CCITT) == ITS_MTP2_CCITT)
        {
            SS7_LinkPtr lp;

            for (lp = TRANSPORT_SS7_INFO(tr).linkInfo;
                 lp != NULL; lp = lp->next)
            {
               printf("Deactivating ls:%d lc:%d\n",
                       lp->linkSet->linkSet, lp->linkCode);

               MGMT_Main_CCITT(MTP3_USER,
                               MGMT_TRIGGER_DEACTIVATE_LINK,
                               NULL, 0,
                               lp->linkSet->linkSet, lp->linkCode);
            }

        }
    }

    RWLOCK_UnlockShared(&tm->transportGate);
}

/****************************************************************************
 *  Purpose:
 *      This API is invoked by the MTP3 SubDAP present in DAP.  This will
 *      clear the ACTIVE MTP3 OM Buffer. 
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      void
 *
 *  Revision History:
 * ------------------------------------------------------------------------
 * Name        Date          Reference               Description
 * ------------------------------------------------------------------------
 * mshanmugam  14-08-2006    ACC-PR66-SDS-GEN    Q.752 SS7 Monitoring and
 *                           v1.0.02             Measurement
 *                           ID:: D0020, 
 *                           D0110 - D0210, 
 *                           D0310 - D0350,
 *                           D0380 - D0460 
 *
 ****************************************************************************/
void MTP3_ResetOm_CCITT()
{
  struct adj_sp_node *temp;

  /* Clear Active MTP3 Link, Linkset and Adjacent SP OM Buffer */ 
  MTP3LinkOmDataInitialize (&LinkOmImage[omBuf.activeOm]);
  MTP3LinksetOmDataInitialize (&LinkSetOmImage[omBuf.activeOm]);   

  temp = adjSpNodePtr;
  while(temp != NULL)
  {
    temp->SpImage[omBuf.activeOm].adjSPInaccess = 0;
    temp->SpImage[omBuf.activeOm].adjSPInaccDuration = 0;
    /* Since the timestamp will be used in the later point, we are not clearing it */
    temp = temp->next;
  }
}

/****************************************************************************
 *  Purpose:
 *      This API is invoked by the MTP3 SubDAP present in DAP.  This will
 *      clear the INACTIVE MTP3 OM Buffer, toggle the ACTIVE/INACTIVE 
 *      MTP3 OM Buffers and copy the collected OM buffer ( present in
 *      INACTIVE Buffer) into the OAM structure.
 *
 *  Input Parameters:
 *      mtp3Om Structure Pointer 
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      void
 *
 *  Revision History:
 * ------------------------------------------------------------------------
 * Name        Date          Reference               Description
 * ------------------------------------------------------------------------
 * mshanmugam  14-08-2006    ACC-PR66-SDS-GEN    Q.752 SS7 Monitoring and
 *                           v1.0.02             Measurement
 *                           ID:: D0020,
 *                           D0110 - D0210,
 *                           D0310 - D0350,
 *                           D0380 - D0460
 *
 ****************************************************************************/
void MTP3_GetOm_CCITT(mtp3Om *OmMtp3Data)
{
  ITS_OCTET i, j, linkset, linkcode;
  ITS_UINT retVal;
  SS7_LinkSetPtr ls;
  SS7_LinkPtr ln;
  struct adj_sp_node *temp, *temp1, *temp2;
  struct timeval current_time;
  SS7_Family famDesc;

  /* Clear the OAM structure before filling it to avoid holding invalid data */
  memset(OmMtp3Data, 0, sizeof(mtp3Om));

  /*Adding Family to outer structure to collect PM data OM*/
  famDesc = FAMILY_ITU;
  memcpy(&OmMtp3Data->family,
       &famDesc,
       sizeof(ITS_UINT));

  /* Clear Inactive MTP3 Link, Linkset and Adjancent SP OM Buffer */ 
  MTP3LinkOmDataInitialize (&LinkOmImage[omBuf.inactiveOm]);
  MTP3LinksetOmDataInitialize (&LinkSetOmImage[omBuf.inactiveOm]);

  temp = adjSpNodePtr;
  for(;;)
  {
    if(temp != NULL)
    {
      memset(&temp->SpImage[omBuf.inactiveOm], 0, sizeof(struct ADJ_SP));
      temp = temp->next;
    }
    else
    {
      break;
    }
  }

  /* Toggle ACTIVE/INACTIVE MTP3 Link & LinkSet and Adjacent SP Buffers */
  omBuf.activeOm ^= 0x01;
  omBuf.inactiveOm ^= 0x01;
  
  /* Collect the Adjacent SP, Linkset and Link Peg information present
     in the INACTIVE OM Buffer */
  temp = adjSpNodePtr;

  if(adjSpNodePtr == NULL)
  {
    /* Dont do anything... No SPs are in inaccessible state */
  }
  else
  {
    while(temp != NULL)
    {
      if(temp->SpImage[omBuf.inactiveOm].timeStamp == 0)
      {
        /* Dont do anything... This means the adjacent SP was not inaccessible or
           the duration is already calculated */
      }
      else
      {
        /* Get the current time and update the SP inaccessible duration 
           properly */
        retVal = gettimeofday(&current_time, NULL);
  
        if(temp->SpImage[omBuf.inactiveOm].adjSPInaccDuration == 0)
        {
          temp->SpImage[omBuf.inactiveOm].adjSPInaccDuration = current_time.tv_sec - 
                       temp->SpImage[omBuf.inactiveOm].timeStamp;
        }
        else
        {
          temp->SpImage[omBuf.inactiveOm].adjSPInaccDuration = 
                       temp->SpImage[omBuf.inactiveOm].adjSPInaccDuration + current_time.tv_sec -
                       temp->SpImage[omBuf.inactiveOm].timeStamp;
        } 
      }

      /* Collect the SP related pegs from Inactive Buffer and update the OAM Buffer */
      OmMtp3Data->spStats.adjSpStats[OmMtp3Data->spStats.count].adjSp =
                        temp->adj_sig_point;
      OmMtp3Data->spStats.adjSpStats[OmMtp3Data->spStats.count].adjSPInaccess = 
                        temp->SpImage[omBuf.inactiveOm].adjSPInaccess;
      OmMtp3Data->spStats.adjSpStats[OmMtp3Data->spStats.count].adjSPInaccDuration = 
                        temp->SpImage[omBuf.inactiveOm].adjSPInaccDuration;
 
      OmMtp3Data->spStats.count++;

      if(temp->adjSpInaccFlag == ITS_FALSE)
      {
        if(temp->prev == NULL && temp->next == NULL) /* Only one element */
        {
          free(temp);
          temp = NULL;
          adjSpNodePtr = NULL;
        }
        else
        {
          if(temp->prev == NULL) /* Starting */
          {
            temp1 = temp->next;
            free(temp);
            temp1->prev = NULL;
            /* Update the adjSpNodePtr with the proper start address */
            adjSpNodePtr = temp1;
            temp = temp1;
          }
          else if(temp->next == NULL) /* End */
          {
            temp1 = temp->prev;
            free(temp);
            temp = NULL; 
            temp1->next = NULL;
          }
          else /* Middle */
          {
            temp1 = temp->prev;
            temp2 = temp->next;
            free(temp);
            temp1->next = temp2;
            temp2->prev = temp1;
            temp = temp2;
          } 
        }
      }
      else
      {
        /* Store the current time in the active buffer, so that we 
           can use it during the next duration calculation */
        temp->SpImage[omBuf.activeOm].timeStamp = current_time.tv_sec;

        temp = temp->next;
      }
    }
  }

  for(i = 1; i < ITS_SS7_DEFAULT_LINK_SET; i++)
  {
    if ((ls = LINKSET_FindLinkSet(i)) == NULL)
    {
      continue;
    }

    if(ls->family != FAMILY_ITU)
    {
      continue;
    }
    linkset = ls->linkSet;
    
    LinkSetOmImage[omBuf.inactiveOm].MTP3LinkSetStat[linkset].linkset = linkset;

    /* Since the Duration OMs are pegged for every 10 second, we need to 
       multiply the pegged duration with DURATION_OM_TICK, so that the peg is
       displayed in number of seconds */ 

    LinkSetOmImage[omBuf.inactiveOm].MTP3LinkSetStat[linkset].linksetUnavailDuration *= DURATION_OM_TICK;

    /* Copy the content of the Inactive Linkset Buffer into the OAM Buffer */
    memcpy(&OmMtp3Data->lkStats.linksetStats[OmMtp3Data->lkStats.count], 
           &LinkSetOmImage[omBuf.inactiveOm].MTP3LinkSetStat[linkset],
           sizeof(mtp3LinksetPegs));

    OmMtp3Data->lkStats.count++;

    /* Loop through all the configured links */ 
    for (j = 0; j < ls->numLinks; j++)
    {
      ln = ls->links[j];

      linkcode = ln->linkCode;

      LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].linkset = linkset;
      LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].linkcode = linkcode;
      LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].slInsDuration *= DURATION_OM_TICK;
      LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].slUnavailDuration *= DURATION_OM_TICK;
      LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].slRPODuration *= DURATION_OM_TICK;
      LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].slLocalInhibitDuration *= DURATION_OM_TICK;
      LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].slRemoteInhibitDuration *= DURATION_OM_TICK;
      LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].slCumulativeCongDuration *= DURATION_OM_TICK;

      /* Copy the content of Link Inactive OM Buffer content
         into the OAM Buffer */
      memcpy(&OmMtp3Data->lnStats.linkStats[OmMtp3Data->lnStats.count],
             &LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode],
             sizeof(mtp3LinkPegs));
 
      OmMtp3Data->lnStats.count++;
    } 
  }
}

/****************************************************************************
 *  Purpose:
 *      This API is invoked by the mi_clr_gen_peg() MML command. This will
 *      clear the ACTIVE MTP3 OM Buffer.
 *
 *               !!! WARNING WARNING WARNING !!!
 *   This function should not be invoked, when the OAM
 *   duration timer is running.  If this function is called
 *   when the OAM duration timer is running, there will be
 *   inconsistent MTP3 OM values.
 * 
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      void
 *
 *  Revision History:
 * ------------------------------------------------------------------------
 * Name        Date          Reference               Description
 * ------------------------------------------------------------------------
 * mshanmugam  14-08-2006    ACC-PR66-SDS-GEN    Q.752 SS7 Monitoring and
 *                           v1.0.02             Measurement
 *                           ID:: D0020,
 *                           D0110 - D0210,
 *                           D0310 - D0350,
 *                           D0380 - D0460
 *
 ****************************************************************************/

void MTP3_ResetOm_MML_CCITT()
{
  struct adj_sp_node *temp;

  /* Clear Active MTP3 Link and Linkset OM Buffer */
  MTP3LinkOmDataInitialize (&LinkOmImage[omBuf.activeOm]);
  MTP3LinksetOmDataInitialize (&LinkSetOmImage[omBuf.activeOm]);

  temp = adjSpNodePtr;
  while(temp != NULL)
  {
    temp->SpImage[omBuf.activeOm].adjSPInaccess = 0;
    temp->SpImage[omBuf.activeOm].adjSPInaccDuration = 0;
    /* Since the timestamp will be used in the later point, we are not clearing it */
    temp = temp->next;
  }
}

/****************************************************************************
 *  Purpose:
 *      This API is invoked by the mi_get_gen_peg() MML command.  This will
 *      clear the INACTIVE MTP3 OM Buffer, toggle the ACTIVE/INACTIVE
 *      MTP3 OM Buffers and display the collected OM buffer (from the
 *      INACTIVE Buffer) in the DEBUG console.
 *
 *               !!! WARNING WARNING WARNING !!!
 *   This function should not be invoked, when the OAM
 *   duration timer is running.  If this function is called
 *   when the OAM duration timer is running, there will be
 *   inconsistent MTP3 OM values.
 * 
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      void
 *
 *  Revision History:
 * ------------------------------------------------------------------------
 * Name        Date          Reference               Description
 * ------------------------------------------------------------------------
 * mshanmugam  14-08-2006    ACC-PR66-SDS-GEN    Q.752 SS7 Monitoring and
 *                           v1.0.02             Measurement
 *                           ID:: D0020,
 *                           D0110 - D0210,
 *                           D0310 - D0350,
 *                           D0380 - D0460
 *
 * mshanmugam  11-04-2007                        To display only ITU link pegs,
 *                                               family check is added.  
 *                                               To allow linkset no upto 255
 *                                               in  the for loop. 
 ****************************************************************************/

void MTP3_GetOm_MML_CCITT(DBC_Server *dbc)
{
  char buf[32000];
  char buf1[32000];

  ITS_OCTET i, j, linkset, linkcode;
  SS7_LinkSetPtr ls;
  SS7_LinkPtr ln;
  struct adj_sp_node *temp, *temp1, *temp2;
  struct timeval current_time;
  ITS_UINT retVal;

  /* Clear the Temporary Buffers */
  memset(buf , 0, 32000);
  memset(buf1, 0, 32000);

  /* Clear Inactive MTP3 Link, Linkset and Adjacent SP OM Buffer */
  MTP3LinkOmDataInitialize (&LinkOmImage[omBuf.inactiveOm]);
  MTP3LinksetOmDataInitialize (&LinkSetOmImage[omBuf.inactiveOm]);

  temp = adjSpNodePtr;
  for(;;)
  {
    if(temp != NULL)
    {
      memset(&temp->SpImage[omBuf.inactiveOm], 0, sizeof(struct ADJ_SP));
      temp = temp->next;
    }
    else
    {
      break;
    }
  }

  /* Toggle ACTIVE/INACTIVE MTP3 Link & LinkSet and Adjacent SP Buffers */
  omBuf.activeOm ^= 0x01;
  omBuf.inactiveOm ^= 0x01;

  /* Print the contents properly in the Debug Console */

  sprintf(buf, "\n          ****** Q752 MTP3 Measurements ******\n");
  strcat(buf1, buf);
  sprintf(buf, "    ------------------------------------------------\n");
  strcat(buf1, buf);

  DBC_AppendText(dbc, buf1);

  /* Collect the Adjacent SP, Linkset and Link Peg information present
     in the INACTIVE OM Buffer and put it in a linear buffer */

  temp = adjSpNodePtr;

  /* Clear the Temporary Buffers */
  memset(buf , 0, 32000);
  memset(buf1, 0, 32000);

  if(adjSpNodePtr == NULL)
  {
    /* Dont do anything... No SPs are in inaccessible state */
  }
  else
  {
    sprintf(buf, "\n              ****** Signaling Point ******\n");
    strcat(buf1, buf);

    while(temp != NULL)
    {
      if(temp->SpImage[omBuf.inactiveOm].timeStamp == 0)
      {
        /* Dont do anything... This means the adjacent SP was not inaccessible or
           the duration is already calculated */
      }
      else
      {
        /* Get the current time and update the SP inaccessible duration
           properly */
        retVal = gettimeofday(&current_time, NULL);

        if(temp->SpImage[omBuf.inactiveOm].adjSPInaccDuration == 0)
        {
          temp->SpImage[omBuf.inactiveOm].adjSPInaccDuration = current_time.tv_sec -
                       temp->SpImage[omBuf.inactiveOm].timeStamp;
        }
        else
        {
          temp->SpImage[omBuf.inactiveOm].adjSPInaccDuration =
                       temp->SpImage[omBuf.inactiveOm].adjSPInaccDuration + current_time.tv_sec -
                       temp->SpImage[omBuf.inactiveOm].timeStamp;
        }
      }

      /* Print the Contents properly in the Debug Console - Testing purpose */

      sprintf(buf, "\n Signaling Point              : %d", temp->adj_sig_point);
      strcat(buf1, buf);

      sprintf(buf, "\n Inaccessible Count           : %d", temp->SpImage[omBuf.inactiveOm].adjSPInaccess);
      strcat(buf1, buf);

      sprintf(buf, "\n Inaccessible Duration        : %d\n", temp->SpImage[omBuf.inactiveOm].adjSPInaccDuration);
      strcat(buf1, buf);

      if(temp->adjSpInaccFlag == ITS_FALSE)
      {
        if(temp->prev == NULL && temp->next == NULL) /* Only one element */
        {
          free(temp);
          temp = NULL;
          adjSpNodePtr = NULL;
        }
        else
        {
          if(temp->prev == NULL) /* Starting */
          {
            temp1 = temp->next;
            free(temp);
            temp1->prev = NULL;
            /* Update the adjSpNodePtr with the proper start address */
            adjSpNodePtr = temp1;
            temp = temp1;
          }
          else if(temp->next == NULL) /* End */
          {
            temp1 = temp->prev;
            free(temp);
            temp = NULL;
            temp1->next = NULL;
          }
          else /* Middle */
          {
            temp1 = temp->prev;
            temp2 = temp->next;
            free(temp);
            temp1->next = temp2;
            temp2->prev = temp1;
            temp = temp2;
          }
        }
      }
      else
      {
        /* Store the current time in the active buffer, so that we
           can use it during the next duration calculation */
        temp->SpImage[omBuf.activeOm].timeStamp = current_time.tv_sec;

        temp = temp->next;
      }
    }
    DBC_AppendText(dbc, buf1);
  }

  for(i = 1; i < ITS_SS7_DEFAULT_LINK_SET; i++)
  {
    /* Clear the Temporary Buffers */
    memset(buf , 0, 32000);
    memset(buf1, 0, 32000);

    if ((ls = LINKSET_FindLinkSet(i)) == NULL)
    {
      continue;
    }

    if(ls->family == FAMILY_ITU)
    {
    linkset = ls->linkSet;
    LinkSetOmImage[omBuf.inactiveOm].MTP3LinkSetStat[linkset].linkset = linkset;

    /* Since the Duration OMs are pegged for every 10 second, we need to
       multiply the pegged duration with DURATION_OM_TICK, so that the peg is
       displayed in number of seconds */

    LinkSetOmImage[omBuf.inactiveOm].MTP3LinkSetStat[linkset].linksetUnavailDuration *= DURATION_OM_TICK;

    sprintf(buf, "\n              ****** Link Set ******\n");
    strcat(buf1, buf);

    sprintf(buf, "\n Link Set                     : %d", LinkSetOmImage[omBuf.inactiveOm].MTP3LinkSetStat[linkset].linkset);
    strcat(buf1, buf);

    sprintf(buf, "\n Unavailable Duration         : %d", LinkSetOmImage[omBuf.inactiveOm].MTP3LinkSetStat[linkset].linksetUnavailDuration);
    strcat(buf1, buf);

    sprintf(buf, "\n TFA Transmitted              : %d", LinkSetOmImage[omBuf.inactiveOm].MTP3LinkSetStat[linkset].tfaTx);
    strcat(buf1, buf);

    sprintf(buf, "\n TFP Transmitted              : %d\n", LinkSetOmImage[omBuf.inactiveOm].MTP3LinkSetStat[linkset].tfpTx);
    strcat(buf1, buf);

    /* Loop through all the configured links */
    for (j = 0; j < ls->numLinks; j++)
    {
      sprintf(buf, "\n              ****** Link  ******\n");
      strcat(buf1, buf);

      ln = ls->links[j];

      linkcode = ln->linkCode;

      LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].linkset = linkset;
      LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].linkcode = linkcode;
      LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].slInsDuration *= DURATION_OM_TICK;
      LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].slUnavailDuration *= DURATION_OM_TICK;
      LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].slRPODuration *= DURATION_OM_TICK;
      LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].slLocalInhibitDuration *= DURATION_OM_TICK;
      LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].slRemoteInhibitDuration *= DURATION_OM_TICK;
      LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].slCumulativeCongDuration *= DURATION_OM_TICK;

      sprintf(buf, "\n Link Set                     : %d", LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].linkset);
      strcat(buf1, buf);

      sprintf(buf, "\n Link Code                    : %d", LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].linkcode);
      strcat(buf1, buf);

      sprintf(buf, "\n In-Service Duration          : %d", LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].slInsDuration);
      strcat(buf1, buf);

      sprintf(buf, "\n Unavailable Duration         : %d", LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].slUnavailDuration);
      strcat(buf1, buf);

      sprintf(buf, "\n RPO Duration                 : %d", LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].slRPODuration);
      strcat(buf1, buf);

      sprintf(buf, "\n Local Inhibit Duration       : %d", LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].slLocalInhibitDuration);
      strcat(buf1, buf);

      sprintf(buf, "\n Remote Inhibit Duration      : %d", LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].slRemoteInhibitDuration);
      strcat(buf1, buf);

      sprintf(buf, "\n Congestion Duration          : %d", LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].slCumulativeCongDuration);
      strcat(buf1, buf);

      sprintf(buf, "\n Restoration Count            : %d", LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].slRestoration);
      strcat(buf1, buf);

      sprintf(buf, "\n Level 1 Congestion Count     : %d", LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].l1CongCount);
      strcat(buf1, buf);

      sprintf(buf, "\n Level 2 Congestion Count     : %d", LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].l2CongCount);
      strcat(buf1, buf);

      sprintf(buf, "\n Level 3 Congestion Count     : %d", LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].l3CongCount);
      strcat(buf1, buf);

      sprintf(buf, "\n MSU Discard - Routing Error  : %d", LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].msuDiscardRoutingError);
      strcat(buf1, buf);

      sprintf(buf, "\n MSU Discard - Congestion     : %d", LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].msuDiscardCongestion);
      strcat(buf1, buf);

      sprintf(buf, "\n Automatic Changeover         : %d", LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].changeover);
      strcat(buf1, buf);

      sprintf(buf, "\n Automatic Changeback         : %d", LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].changeback);
      strcat(buf1, buf);

      sprintf(buf, "\n Local Inhibit                : %d", LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].localLinkInhibit);
      strcat(buf1, buf);

      sprintf(buf, "\n Local Uninhibit              : %d", LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].localLinkUninhibit);
      strcat(buf1, buf);

      sprintf(buf, "\n TFC Received                 : %d", LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].tfcReceived);
      strcat(buf1, buf);

      sprintf(buf, "\n UPU Transmitted              : %d", LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].upuTx);
      strcat(buf1, buf);

      sprintf(buf, "\n UPU Received                 : %d", LinkOmImage[omBuf.inactiveOm].MTP3LinkStat[linkset][linkcode].upuRx);
      strcat(buf1, buf);

      sprintf(buf, "\n");
      strcat(buf1, buf);
    }
    DBC_AppendText(dbc, buf1);
   }  
 } 
}

/****************************************************************************
 *  Purpose:
 *      This function clears the MTP3 Link OM Buffers. 
 *
 *  Input Parameters:
 *      MTP Link Statistics Structure Pointer 
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      void
 *
 *  Revision History:
 * ------------------------------------------------------------------------
 * Name        Date          Reference               Description
 * ------------------------------------------------------------------------
 * mshanmugam  14-08-2006    ACC-PR66-SDS-GEN    Q.752 SS7 Monitoring and
 *                           v1.0.02             Measurement
 *                           ID:: D0020,
 *                           D0110 - D0210,
 *                           D0310 - D0350,
 *                           D0380 - D0460
 *
 ****************************************************************************/

void MTP3LinkOmDataInitialize(mtp3_link_stat_table *mtp3_om_data_ptr)
{
  memset (mtp3_om_data_ptr, 0, sizeof (mtp3_link_stat_table)); 
}
 
/****************************************************************************
 *  Purpose:
 *      This function clears the MTP3 Linkset OM Buffers.
 *
 *  Input Parameters:
 *      MTP Linkset Statistics Structure Pointer 
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      void
 *
 *  Revision History:
 * ------------------------------------------------------------------------
 * Name        Date          Reference               Description
 * ------------------------------------------------------------------------
 * mshanmugam  14-08-2006    ACC-PR66-SDS-GEN    Q.752 SS7 Monitoring and
 *                           v1.0.02             Measurement
 *                           ID:: D0020,
 *                           D0110 - D0210,
 *                           D0310 - D0350,
 *                           D0380 - D0460
 *
 ****************************************************************************/

void MTP3LinksetOmDataInitialize(mtp3_linkset_stat_table *mtp3_om_data_ptr)
{
  memset (mtp3_om_data_ptr, 0, sizeof (mtp3_linkset_stat_table)); 
}
