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
 *  ID: $Id: ttc-smh.c,v 9.7 2008/07/18 05:47:53 ssingh Exp $
 *
 * LOG: $Log: ttc-smh.c,v $
 * LOG: Revision 9.7  2008/07/18 05:47:53  ssingh
 * LOG: SDS ID:: ID :: D0240 Warning removal for Solaris Compilation
 * LOG:
 * LOG: Revision 9.6  2008/06/17 06:38:02  nvijikumar
 * LOG: Updated for ITU over TTC support (Split Stack)
 * LOG: ACC-CG-SDS-SS7-V1.0.02::D7040,D7080
 * LOG:
 * LOG: Revision 9.5  2008/06/12 12:51:50  nvijikumar
 * LOG: Renaming from COT to CPOT (CCITT prime - 16bit)
 * LOG: ACC-CG-SDS-SS7-V1.0.02::ID:: D6030
 * LOG:
 * LOG: Revision 9.4  2008/06/04 10:38:48  ssingh
 * LOG: ALU porting, B-0100LX-LUSG-00 (june 04,2008 base)
 * LOG:
 * LOG: Revision 9.3  2007/02/01 13:25:20  yranade
 * LOG: 2nd round of merge
 * LOG:
 * LOG: Revision 9.2  2007/01/11 12:43:41  yranade
 * LOG: Merge changes from 6.5.3 and Lucent branches
 * LOG:
 * LOG: Revision 9.1.10.21  2008/03/28 14:13:12  ssodhi
 * LOG: TTC Issue 376
 * LOG:
 * LOG: Revision 9.1.10.20  2008/03/25 08:53:30  ssodhi
 * LOG: Fix for issue 376
 * LOG:
 * LOG: Revision 9.1.10.19  2008/02/29 11:45:30  skatta
 * LOG: Fix for issue #282
 * LOG:
 * LOG: Revision 9.1.10.18  2008/02/15 14:43:26  skatta
 * LOG: Fix for issue 536
 * LOG:
 * LOG: Revision 9.1.10.17  2008/01/30 15:06:52  ssodhi
 * LOG: Fix for issue #376
 * LOG:
 * LOG: Revision 9.1.10.16  2008/01/21 08:19:28  ssodhi
 * LOG: Fix to resolve hang issue
 * LOG:
 * LOG: Revision 9.1.10.15  2008/01/18 10:20:19  ssodhi
 * LOG: Corrected the Call to Function HMDC_Main_TTC
 * LOG:
 * LOG: Revision 9.1.10.14  2008/01/17 10:38:42  ssodhi
 * LOG: Call function Send_MTP2_to_MTP3_Msg_ToPeer only if msg is management msg
 * LOG:
 * LOG: Revision 9.1.10.13  2008/01/14 10:21:16  ssodhi
 * LOG: Code changes for Accelero Performance Enhancement - ALU BSG Project
 * LOG:
 * LOG: Revision 9.1.10.12.2.2  2008/01/04 07:55:42  ssodhi
 * LOG: Revision 9.1.10.12.2.1  2007/12/26 15:30:35  ssodhi
 * LOG: Revision 9.1.10.11  2007/11/18 15:05:48  ssingh
 * LOG: Revision 9.1.10.10 corrected; linking problem
 * LOG:
 * LOG: Revision 9.1.10.10  2007/11/16 12:11:53  mshanmugam
 * LOG: to avoid more CPU utilisation in MTP3, we are not calling MTP3_TRACE_ENTRY when DEBUG is OFF
 * LOG:
 * LOG: Revision 9.1.10.9  2007/10/05 11:18:46  mshanmugam
 * LOG: CPOT Stack support as per design Id D0060
 * LOG:
 * LOG: Revision 9.1.10.8  2007/05/18 11:22:12  raghavendrabk
 * LOG: Changes for Alarm Optimisation
 * LOG:
 * LOG: Revision 9.1.10.7  2007/04/30 09:21:09  raghavendrabk
 * LOG: Resolved internode issue for parallel stack
 * LOG:
 * LOG: Revision 9.1.10.6  2007/04/27 16:32:46  sbhaskaran
 * LOG: Corrected Internode Data message handling
 * LOG:
 * LOG: Revision 9.1.10.5  2007/04/27 13:32:16  raghavendrabk
 * LOG: Alarm Format updated with family
 * LOG:
 * LOG: Revision 9.1.10.4  2007/02/02 14:20:20  raghavendrabk
 * LOG: Parallel Stack changes for Alarms and Statistics
 * LOG:
 * LOG: Revision 9.1.10.3  2007/01/23 13:41:54  gharipriya
 * LOG: Merging the fix for 9bit SLS from the Lucent maintenance branch
 * LOG:
 * LOG: Revision 9.1.10.2  2006/12/23 10:05:37  randresol
 * LOG: Modifications to allow TTC and ITU stacks to run in parallel
 * LOG:
 * LOG: Revision 9.1.10.1  2006/10/12 10:28:25  ssingh
 * LOG: fix for 4402;printf issue
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:48  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.1  2005/03/23 09:41:23  cvsadmin
 * LOG: PR6.4.2 sources propagated to Current.
 * LOG:
 * LOG: Revision 1.1.2.1  2005/02/18 11:26:52  dsatish
 * LOG: Added Initial version file for TTC
 * LOG:
 * LOG: Revision 7.8.10.2.8.5  2005/02/01 07:33:03  dsatish
 * LOG: Ansi Over PRC changes after merging.
 * LOG:
 * LOG: Revision 7.8.10.2.8.4  2005/01/25 11:36:14  snagesh
 * LOG: OAM Bug fixes for bugs 1419,1420
 * LOG:
 * LOG: Revision 7.8.10.2.8.3  2005/01/05 10:41:23  craghavendra
 * LOG: Critical Trace before abort().
 * LOG:
 * LOG: Revision 7.8.10.2.8.2  2004/12/31 07:31:27  sbabu
 * LOG: MTP3 OAM Changes
 * LOG:
 * LOG: Revision 7.8.10.2.8.1  2004/12/17 03:57:46  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.8.10.2  2004/08/10 12:14:46  kannanp
 * LOG: Changes for MTP3 pegs, alarms & MMLs - propagated from TCS.
 * LOG:
 * LOG: Revision 7.8.10.1  2004/01/30 11:16:43  sjaddu
 * LOG: Added changes for active-backup configuration.
 * LOG:
 * LOG: Revision 7.8  2003/02/13 10:39:22  ttipatre
 * LOG: New Alarms Added.
 * LOG:
 * LOG: Revision 7.7  2003/01/15 09:19:32  ttipatre
 * LOG: Send TFP for invalid destination fixed.
 * LOG:
 * LOG: Revision 7.6  2002/12/24 19:22:34  randresol
 * LOG: Move LINK_FindLink to improve performance
 * LOG:
 * LOG: Revision 7.5  2002/12/24 07:49:08  ttipatre
 * LOG: Link Level Pegs.
 * LOG:
 * LOG: Revision 7.4  2002/11/20 05:20:27  ttipatre
 * LOG: Modified to protocol specific alarms.
 * LOG:
 * LOG: Revision 7.3  2002/11/09 22:09:55  randresol
 * LOG: Replace LINK_FindLinkLock LINK_FindLinkNoLock for faster processing
 * LOG:
 * LOG: Revision 7.2  2002/09/16 22:35:56  mmiers
 * LOG: Fix signatures
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:28  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.13  2002/08/16 22:07:09  mmiers
 * LOG: Include China variant.
 * LOG:
 * LOG: Revision 6.12  2002/07/25 14:21:51  randresol
 * LOG: Fix bugs found during functional testing.
 * LOG:
 * LOG: Revision 6.11  2002/06/21 22:49:38  mmiers
 * LOG: Adding support for China variant
 * LOG:
 * LOG: Revision 6.10  2002/06/13 20:35:27  ttipatre
 * LOG: Adding MTP3 Pegs and Alarms
 * LOG:
 * LOG: Revision 6.6  2002/05/15 15:06:48  randresol
 * LOG: Integrate shared behaviors and timers with management interface
 * LOG:
 * LOG: Revision 6.5  2002/04/29 21:23:21  randresol
 * LOG: Add InterNode processing and shared booleans
 * LOG:
 * LOG: Revision 6.4.2.1  2002/04/18 19:07:44  randresol
 * LOG: Add InterNode Border Transport processing
 * LOG:
 * LOG: Revision 6.4  2002/04/08 19:10:35  mmiers
 * LOG: Bug fix for user parts.
 * LOG:
 * LOG: Revision 6.3  2002/03/26 18:28:23  randresol
 * LOG: crBuf, cocbBuf, rtrvBuf and route list are now in DSM
 * LOG:
 * LOG: Revision 6.2  2002/03/12 22:41:55  mmiers
 * LOG: Magic number removal.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:39  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.14  2002/02/28 15:31:09  mmiers
 * LOG: On failure to send certain messages send synthetic events
 * LOG: back.
 * LOG:
 * LOG: Revision 5.13  2002/02/27 23:07:44  mmiers
 * LOG: Post throughput testing.
 * LOG:
 * LOG: Revision 5.12  2002/02/13 22:45:23  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 5.11  2002/01/09 21:24:15  mmiers
 * LOG: Correct the build settings, add XCO/XCA (SAAL changeover).
 * LOG:
 * LOG: Revision 5.10  2001/12/28 19:35:02  mmiers
 * LOG: Remove priority.  ITU doesn't have this.
 * LOG:
 * LOG: Revision 5.9  2001/12/15 01:19:50  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.8  2001/12/11 23:49:53  mmiers
 * LOG: Get rid of FIXMEs.
 * LOG:
 * LOG: Revision 5.7  2001/12/07 23:11:47  mmiers
 * LOG: Fix up ITU MTP3 (start testing it).
 * LOG:
 * LOG: Revision 5.6  2001/12/06 22:39:05  mmiers
 * LOG: First cut of ITU MTP3.
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

#if defined(CPOT_SPLIT_STACK)
#undef CCITT
#define TTC
#endif

#include <its.h>
#include <its_callback.h>
#include <its_mutex.h>
#include <its_route.h>
#include <its_transports.h>
#include <its_assertion.h>
#include <its_thread_pool.h>
#include <its_redundancy.h>

#ident "$Id: ttc-smh.c,v 9.7 2008/07/18 05:47:53 ssingh Exp $"

#if defined(PRC)  || defined (USE_PRC_SCCP)
#undef CCITT
#define PRC
#include <china/snmm.h>
#include <china/sltm.h>
#include <china/mtp3.h>
#elif defined(TTC)  || defined (USE_TTC_SCCP)
#undef CCITT
#if !defined(TTC)
#define TTC
#endif
#include <japan/snmm.h>
#include <japan/sltm.h>
#include <japan/mtp3.h>
#else
#include <itu/snmm.h>
#include <itu/sltm.h>
#include <itu/mtp3.h>
#endif

#include "mtp3_intern.h"

/* local data */
static ITS_BOOLEAN      TRIGGER_FOR_ROUTING = ITS_FALSE;

extern ITS_Class ITS_RedundancyClass;

extern mtp3OmBuffer omBuf; 

/*
 * signalling message handling: message discrimination
 */
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
SMH_Main_TTC(MTP3_SubSystems src, MTP3_SubSystems dest,
               SMH_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_TRACE_ENTRY_TTC(MTP3_SMH, src, trigger, sif, len,
                           linkSet, linkCode);

    switch (trigger)
    {
    /* HMDC */
    /* HMDT */
    case SMH_TRIGGER_L2_L3_MSG:
        /*
         * we have to be a little more creative than the SDLs.  They
         * magically deliver MTP2 indications to the right place without
         * saying how that happens.
         */
        switch (sif[0])
        {
        case L2_L3_IN_SERVICE:
            return LSAC_Main_TTC(MTP3_L2,
                                   SLM_TRIGGER_L2_IN_SERVICE,
                                   sif, len,
                                   linkSet, linkCode);

        case L2_L3_REMOTE_PROCESSOR_OUT:
            return LSAC_Main_TTC(MTP3_L2,
                                   SLM_TRIGGER_L2_RPO,
                                   sif, len,
                                   linkSet, linkCode);

        case L2_L3_OUT_OF_SERVICE:
            return LSAC_Main_TTC(MTP3_L2,
                                   SLM_TRIGGER_L2_OUT_OF_SERVICE,
                                   sif, len,
                                   linkSet, linkCode);

        case L2_L3_REMOTE_PROCESSOR_REC:
            return LSAC_Main_TTC(MTP3_L2,
                                   SLM_TRIGGER_L2_RPR,
                                   sif, len,
                                   linkSet, linkCode);

        case L2_L3_BSNT:
            return TCOC_Main_TTC(MTP3_L2,
                                   STM_TRIGGER_BSNT,
                                   sif, len,
                                   linkSet, linkCode);

        case L2_L3_BSNT_NOT_RETRIEVABLE:
            return TCOC_Main_TTC(MTP3_L2,
                                   STM_TRIGGER_BSNT_NOT_RETRIEVABLE,
                                   sif, len,
                                   linkSet, linkCode);

        case L2_L3_RETRIEVED_MSG:
            return TCOC_Main_TTC(MTP3_L2,
                                   STM_TRIGGER_RETRIEVED_MSGS,
                                   sif, len,
                                   linkSet, linkCode);

        case L2_L3_RETRIEVAL_COMPLETE:
            return TCOC_Main_TTC(MTP3_L2,
                                   STM_TRIGGER_RETRIEVAL_COMPLETE,
                                   sif, len,
                                   linkSet, linkCode);

        case L2_L3_RETRIEVAL_NOT_POSSIBLE:
            return TCOC_Main_TTC(MTP3_L2,
                                   STM_TRIGGER_RETRIEVAL_NOT_POSSIBLE,
                                   sif, len,
                                   linkSet, linkCode);
            
        case L2_L3_DATA:
            return HMDC_Main_TTC(MTP3_L2, trigger,
                                   sif, len,
                                   linkSet, linkCode);

        case L2_L3_RB_CLEARED:
            return LSAC_Main_TTC(MTP3_L2,
                                   SLM_TRIGGER_RB_CLEARED,
                                   sif, len,
                                   linkSet, linkCode);

        case L2_L3_RTB_CLEARED:
            return LSAC_Main_TTC(MTP3_L2,
                                   SLM_TRIGGER_RTB_CLEARED,
                                   sif, len,
                                   linkSet, linkCode);

        case L2_L3_CONGESTION_ONSET:
        case L2_L3_CONGESTION_ABATES:
            return TSRC_Main_TTC(MTP3_L2,
                                   STM_TRIGGER_LINK_CONGESTION_STATUS,
                                   sif, len,
                                   linkSet, linkCode);

        default:
            MTP3_DEBUG(("Unknown msg type: %d\n", sif[0]));
            MTP3_Alarm_TTC(2406, __FILE__, __LINE__, "family=%s", "TTC");
            PEG_IncrPeg(TTC_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
            break;
        }
        break;

    case SMH_TRIGGER_L4_L3_MSG:
        return HMRT_Main_TTC(MTP3_L4, trigger,
                               sif, len,
                               linkSet, linkCode);

    default:
        PEG_IncrPeg(TTC_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
        abort();
    }

    /* NOTREACHED */
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
 ****************************************************************************/
int
HMDC_Main_TTC(MTP3_SubSystems src, SMH_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER *mtp3a;
    MTP3_HEADER *mtp3i;
    ITS_UINT dpc;
    ITS_BOOLEAN isLocal = ITS_FALSE;
    int ret;
    ITS_OCTET up, ni;
    
    MTP3_TRACE_ENTRY_TTC(MTP3_SMH_HMDC, src, trigger, sif, len,
                           linkSet, linkCode);

    /*
     * determine label structure.  Should only handle national networks
     * here.
     *
     * byte 1 of the buffer is the SIO.
     */

    mtp3a = (MTP3_HEADER *)&sif[1];
    mtp3i = (MTP3_HEADER *)&sif[1];
    if ((MTP3_HDR_GET_SIO(*mtp3a) & MTP3_NIC_MASK) ==
        MTP3_NIC_INTERNATIONAL ||
        (MTP3_HDR_GET_SIO(*mtp3a) & MTP3_NIC_MASK) ==
        MTP3_NIC_SPARE)
    {
        dpc = MTP3_RL_GET_DPC_VALUE(mtp3i->label);
    }
    else if ((MTP3_HDR_GET_SIO(*mtp3a) & MTP3_NIC_MASK) ==
             MTP3_NIC_NATIONAL)
    {
        dpc = MTP3_RL_GET_DPC_VALUE(mtp3a->label);
    }
    else if ((MTP3_HDR_GET_SIO(*mtp3a) & MTP3_NIC_MASK) ==
             MTP3_NIC_RESERVED)
    {
        if (MTP3_TTC_HandleSpareNIC)
        {
            dpc = MTP3_RL_GET_DPC_VALUE(mtp3a->label);
        }
        else
        {
            /* discard, what else can we do? */
            MTP3_DEBUG(("MTP3_HMDC: Failed to handle L2 message\n"));

            MTP3_Alarm_TTC(2407, __FILE__, __LINE__, "family=%s", "TTC");

            return (ITS_EINVALIDARGS);
        }
    }
    else
    {
        /* discard, what else can we do? */
        MTP3_DEBUG(("MTP3_HMDC: Failed to handle L2 message\n"));

        MTP3_Alarm_TTC(2407, __FILE__, __LINE__, "family=%s", "TTC");
            
        return (ITS_EINVALIDARGS);
    }
    

    up = MTP3_HDR_GET_SIO(*mtp3a) & MTP3_SIO_UP_MASK;
    ni = MTP3_HDR_GET_SIO(*mtp3a) & MTP3_NIC_MASK;
    if ((ret = ROUTE_GetRouteContextLocal(dpc, &isLocal,
                                          /* ROUTE_DPC_NI, */ ROUTE_DPC_SIO,
                                          FAMILY_JAPAN,
                                          ni | up,
                                          ITS_SS7_DEFAULT_LINK_SET,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_PRI,
                                          ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
    {
        MTP3_DEBUG(("MTP3_HMDC: Route failure %d\n", ret));

        MTP3_Alarm_TTC(2408, __FILE__, __LINE__, "family=%s","TTC");

        isLocal = ITS_FALSE;
    }
    
    /*
     * if local, send to distribution.  Else send to routing.
     */
    if (isLocal)
    {
        return HMDT_Main_TTC(MTP3_SMH_HMDC,
                               SMH_TRIGGER_L2_L3_MSG,
                               sif, len,
                               linkSet, linkCode);
    }
    else
    {
        return HMRT_Main_TTC(MTP3_SMH_HMDC,
                               SMH_TRIGGER_MSG_FOR_ROUTING,
                               sif, len,
                               linkSet, linkCode);
    }
}

/*
 * HMDT
 */
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
HMDT_Main_TTC(MTP3_SubSystems src, SMH_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SNMM_MESSAGE *snmm;
    MTP3_HEADER *mtp3;
    MTP3_HEADER omtp3;
    SNMM_MESSAGE osnmm;
    ITS_UINT pc1, pc2;
    ITS_USHORT dest;
    ITS_EVENT ev;
    ITS_OCTET sio, ni;
    int ret;
    
    MTP3_TRACE_ENTRY_TTC(MTP3_SMH_HMDT, src, trigger, sif, len,
                          linkSet, linkCode);


    mtp3 = (MTP3_HEADER *)&sif[1];

    sio = MTP3_HDR_GET_SIO(*mtp3);

    printf("===== Printing SIF ======\n");
    for(ret = 0; ret < len; ret++)
    {
        printf(" %02x", sif[ret]);
    } 
    printf("\n");

    switch (sio & MTP3_SIO_UP_MASK)
    {
    case MTP3_SIO_SNMM: /* signalling network management */
        snmm = (SNMM_MESSAGE *)&sif[sizeof(MTP3_HEADER) + sizeof(ITS_OCTET)];
        switch (SNMM_HC0_GET(*snmm))
        {
        case SNMM_HC0_CHM: /* changeover */
        case SNMM_HC0_ECM: /* emergency changeover */
        case SNMM_HC0_MIM: /* management inhibit */
        case SNMM_HC0_TRM: /* traffic restart */
        case SNMM_HC0_UFC: /* user flow control */
            return STM_Main_TTC(MTP3_SMH_HMDT, MTP3_STM,
                                  STM_TRIGGER_L2_MSG,
                                  sif, len,
                                  linkSet, linkCode);
            
        case SNMM_HC0_FCM: /* transfer controlled/congestion */
        case SNMM_HC0_TFM: /* transfer prohibit/allow/restrict */
        case SNMM_HC0_RSM: /* route set test */
            return SRM_Main_TTC(MTP3_SMH_HMDT, MTP3_SRM,
                                  SRM_TRIGGER_L2_MSG,
                                  sif, len, linkSet, linkCode);
            
        case SNMM_HC0_DLM: /* data link connection */
            return SLM_Main_TTC(MTP3_SMH_HMDT, MTP3_SLM,
                                  SLM_TRIGGER_L2_MSG,
                                  sif, len,
                                  linkSet, linkCode);
            
        default:
            MTP3_DEBUG(("HMDT_Main_TTC: Invalid HCO\n"));

            return (ITS_EINVALIDARGS);
        }
        break;
        
    case MTP3_SIO_SLTM_REG: /* signalling network testing and maintenance */
    case MTP3_SIO_SLTM_SPEC:
        return SLT_Main_TTC(MTP3_SMH_HMDT, MTP3_SLT,
                              SLT_TRIGGER_L2_MSG,
                              sif, len,
                              linkSet, linkCode);

    default:
        dest = MTP3_UserPartOwner((ITS_OCTET)(sio & MTP3_SIO_UP_MASK));

        if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
        {
            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

#if 0  /* defined(0)*/
            if ((ret = MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                                   mtp3,
                                   sif + (sizeof(MTP3_HEADER) - 1 ) + sizeof(ITS_OCTET),
                                   (ITS_USHORT)
                                    (len - sizeof(MTP3_HEADER) -
                                     sizeof(ITS_OCTET)))) != ITS_SUCCESS)
#else
            if ((ret = MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                                   mtp3,
                                   sif + sizeof(MTP3_HEADER) + sizeof(ITS_OCTET),
                                   (ITS_USHORT)
                                    (len - sizeof(MTP3_HEADER) -
                                     sizeof(ITS_OCTET)))) != ITS_SUCCESS)
#endif
            {
                MTP3_DEBUG(("HMDT_Main_TTC: MTP3 encode failed.\n"));

                MTP3_Alarm_TTC(2501, __FILE__, __LINE__, "family=%s", "TTC");
            
                return (ret);
            }

            if (ITS_RedundancyClass != NULL)
            {
                /* Now we have to check the user part state*/
                if (REDUNDANCY_GET_NODE_STATE(ITS_RedundancyClass)
                                    == ITS_STATE_BACKUP)
                {
                    TRANSPORT_Control *trCtl = NULL;
                    /* Put the event on the inter node
                     * hopefully we find some nicer way to do it
                     * TBD
                     */
                    trCtl = TRANSPORT_FindTransportByName(
                                                MTP3_INTER_NODE_STRING_TTC);
                    if (trCtl == NULL) 
                    {
                        return ret;
                    }

                    ev.src = sio & MTP3_SIO_UP_MASK;

                    ret = TRANSPORT_PutEvent(TRANSPORT_INSTANCE(trCtl), &ev);
                    if (ret != ITS_SUCCESS)
                    {
                        MTP3_DEBUG(("HMDT_Main_TTC: No Inter node connection %d\n"));
                        return ret;
                    }

                    TRANSPORT_UnfindTransport(trCtl);
                    return ret;
                }
            }

            /* We are here becuz active or stub */
        
            PEG_IncrPeg(TTC_MTP3_Pegs, PEG_MTP3_MSU_RX);

            ret =TRANSPORT_PutEvent(dest, &ev);

            return ret;
        }
        else
        {
            SS7_LinkPtr ln;

            /* build UPU, send */
            pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
            pc2 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
            ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, pc2);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, pc1);

            SNMM_HC0_SET(osnmm, SNMM_HC0_UFC);
            SNMM_HC1_SET(osnmm, SNMM_HC1_UPU);
            SNMM_USER_PART_UNAVAIL_SET_DEST(osnmm.data.userPartUnavailable,
                                            pc1);
            SNMM_USER_PART_UNAVAIL_SET_USER(osnmm.data.userPartUnavailable,
                                            MTP3_HDR_GET_SIO(*mtp3) &
                                              MTP3_SIO_UP_MASK);
            SNMM_USER_PART_UNAVAIL_SET_CAUSE(osnmm.data.userPartUnavailable,
                                             SNMM_UPU_CAUSE_UNEQUIPPED);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
            SNMM_Encode(&ev, &omtp3, &osnmm);

            if ( (ln = LINK_FindLinkNoLock(linkSet, linkCode)) != NULL)
            {
                /* Increament Link Peg for UPU Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_UPU_TX);
				LinkOmImage[omBuf.activeOm].MTP3LinkStat[linkSet][linkCode].upuTx++;
            }

            ret = HMRT_Main_TTC(MTP3_SMH_HMDT,
                                  SMH_TRIGGER_MSG_FOR_ROUTING,
                                  ev.data, ev.len,
                                  linkSet, linkCode);
            ITS_EVENT_TERM(&ev);

            return (ret);
        }
        break;
    }
}

/*
 * HMRT
 */
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
MessageForRouting(ITS_OCTET *sif, ITS_USHORT len,
                  ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    int ret;
    ITS_USHORT dest;
    MTP3_HEADER *mtp3 = (MTP3_HEADER *)&sif[1];
    ITS_UINT dpc, opc;
    ITS_BOOLEAN isLocal = ITS_FALSE;
    ITS_OCTET ni, up, sls;
    SS7_Destination *rc;
    MTP3_POINT_CODE pc;
    ROUTE_MatchInfo rinfo;

    dpc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
    ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;
    up = MTP3_HDR_GET_SIO(*mtp3) & MTP3_SIO_UP_MASK;
    sls = MTP3_RL_GET_SLS(mtp3->label);
    rinfo.rkey = 0;

    /*
     * special case here.  ITU only has 4 bits of SLS and can't
     * do combined link sets based only on SLS.
     *
     * ITU is a little weird.  We need to distribute traffic in
     * the case we have a combined link set, but we also need
     * that distribution to be even within a link set.  We know
     * that consecutive values will be evenly distributed, so
     * we use a high bit to select the link set (leaving the
     * lower bits to permute as they will).  This should get an
     * even distribution of traffic between the link sets and
     * and within the link sets (note that the routing subsystem
     * expects 5 bits to work with here).
     */
    sls = (sls << 1) | ((sls >> 3) & 1);
    sls +=1;

    /*
     * Any routing data for that DPC?
     */
    if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, dpc,
                                      DONT_CARE, ROUTE_DPC_NI,
                                      FAMILY_JAPAN,
                                      ni,
                                      ITS_SS7_DEFAULT_LINK_SET,
                                      ITS_SS7_DEFAULT_LINK_CODE,
                                      ITS_SS7_DEFAULT_PRI,
                                      sls) != ITS_SUCCESS)
    {
        /* can't recover, can't continue */
        return (ITS_EPROTERR);
    }


    dest = ROUTE_SelectRouteContextInfo(&rinfo);
    /*
     * NOTE: at this point, rinfo.sls has the rotated SLS bits.
     * Also, rinfo.rkey has the index of the routing entry used.
     */

    if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
    {
        opc = MTP3_RL_GET_OPC_VALUE(mtp3->label);

        if ((ret = ROUTE_GetRouteContextLocal(opc, &isLocal,
                                              ROUTE_DPC_SIO,
                                              FAMILY_JAPAN,
                                              ni | up,
                                              ITS_SS7_DEFAULT_LINK_SET,
                                              ITS_SS7_DEFAULT_LINK_CODE,
                                              ITS_SS7_DEFAULT_PRI,
                                              ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("MessageForRouting: RouteContextLocal\n"));

            /* fix for Bug 162 */
            if ((dest == ITS_INVALID_SRC) && TRIGGER_FOR_ROUTING)
            {
                MTP3_DEBUG(("let RTPC know\n"));
            }
            else
            {
            	return (ITS_EINVALIDARGS);
            }
        }

        /* trigger managment */
        MGMT_Main_TTC(MTP3_SMH_HMRT,
                        MGMT_TRIGGER_MSG_FOR_INVALID_DEST,
                        sif, len,
                        linkSet, linkCode);

        /* let RTPC know */
        if (isLocal)
        {
            return (ITS_EINVALIDARGS);
        }
        else
        {
            if ((rc = ROUTE_FindDestination(dpc, ni, FAMILY_JAPAN)) == NULL)
            {
                MTP3_DEBUG(("FindDestination failed.\n"));

                MTP3_Alarm_TTC(2411, __FILE__, __LINE__, "dpc=%x:ni=%x:family=%s", 
                                 dpc, ni, "TTC");

                MTP3_PC_SET_VALUE(pc, dpc);

                return RTPC_Main_TTC(MTP3_SMH_HMRT,
                                       SRM_TRIGGER_MSG_FOR_INACCESS_SP,
                                       sif, len,
                                       linkSet, linkCode);
            }

            /* if (!cluster inaccessible) */
            if (rc->status == DESTINATION_UNAVAILABLE)
            {
                MTP3_DEBUG(("Destination unavailable: %02x %08x.\n", ni, dpc));

                MTP3_Alarm_TTC(2412, __FILE__, __LINE__,"dpc=%x:ni=%x:family=%s",dpc, ni, "TTC");                                    

                MTP3_PC_SET_VALUE(pc, dpc);

                return RTPC_Main_TTC(MTP3_SMH_HMRT,
                                       SRM_TRIGGER_MSG_FOR_INACCESS_SP,
                                       sif, len,
                                       linkSet, linkCode);
            }
        }

        return (ITS_SUCCESS);
    }
    else
    {
        if ((rc = ROUTE_FindDestination(dpc, ni, FAMILY_JAPAN)) == NULL)
        {
            MTP3_DEBUG(("FindDestination failed, return.\n"));

            MTP3_Alarm_TTC(2411, __FILE__, __LINE__, "dpc=%x:ni=%x:family=%s", dpc, ni, "TTC");

            return (ITS_SS7_DEFAULT_LINK_SET);
        }

        /* if destination restricted */
        if (rc->status == DESTINATION_RESTRICTED)
        {
            MTP3_PC_SET_VALUE(pc, dpc);

            MTP3_Alarm_TTC(2413, __FILE__, __LINE__, "dpc=%x:ni=%x:family=%s",dpc, ni, "TTC");

            RTRC_Main_TTC(MTP3_SMH_HMRT,
                            SRM_TRIGGER_MSG_FOR_RESTRICTED_DEST,
                            sif, len,
                            linkSet, linkCode);
        }

        /*
         * DPC is acccessible.
         *
         * select linkset, link on the basis of the SLS.
         * User messages are handled here, so linkSet, linkCode are
         * unspecified here.  However,  the destination link has already
         * been selected and the SLS bits rotated.
         *
         * NOTE: ITU can't rotate SLS bits.
         */
        /* MTP3_RL_SET_SLS(mtp3->label, rinfo.sls); */

        MTP3_DEBUG(("MessageForRouting: Route message to ls:%d lc:%d\n",
                    rinfo.linkSet, rinfo.linkCode)); 

        PEG_IncrPeg(TTC_MTP3_Pegs, PEG_MTP3_MSU_TX);
        /*PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_MSU_TX);*/

        return HMCG_Main_TTC(MTP3_SMH_HMRT,
                               SMH_TRIGGER_L3_L2_MSG,
                               sif, len,
                               rinfo.linkSet,
                               rinfo.linkCode,
                               rinfo.rkey);
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
static int
LinkManagementMessage(ITS_OCTET *sif, ITS_USHORT len,
                      ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    ITS_USHORT dest;
    MTP3_HEADER *mtp3 = (MTP3_HEADER *)&sif[1];
    ITS_UINT dpc;
    ITS_OCTET ni, sls;
    ROUTE_MatchInfo rinfo;

    dpc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
    ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;
    sls = MTP3_RL_GET_SLS(mtp3->label);
    rinfo.rkey = 0;

    /*
     * special case here.  ITU only has 4 bits of SLS and can't
     * do combined link sets based only on SLS.
     */
    sls <<= 1;

    if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, dpc,
                                      DONT_CARE, ROUTE_DPC_NI,
                                      FAMILY_JAPAN,
                                      ni,
                                      linkSet, linkCode,
                                      ITS_SS7_DEFAULT_PRI,
                                      sls) != ITS_SUCCESS)
    {
        MTP3_Alarm_TTC(2502, __FILE__, __LINE__,
                         "dpc=%d:ls=%d:lc=%d:family=%s",
                         dpc,linkSet,linkCode, "TTC");
        /* can't recover, can't continue */
        return (ITS_EPROTERR);
    }

    /* find route */
    dest = ROUTE_SelectRouteContextInfo(&rinfo);
    /*
     * NOTE: at this point, rinfo.sls has the rotated SLS bits.
     * Also, rinfo.rkey has the index of the routing entry used.
     */

    /* is the destination accessible */
    if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
    {
        MTP3_Alarm_TTC(2414, __FILE__, __LINE__, "dpc=%d:ni=%d:family=%s", dpc,ni, "TTC");
        /* discard if it isn't */
        MTP3_Alarm_TTC(2502, __FILE__, __LINE__,
                         "dpc=%d:ls=%d:lc=%d:family=%s", 
                         dpc,linkSet,linkCode, "TTC");
        return (ITS_SUCCESS);
    }

    /*
     * SDL says "select an available link SLC".  To me, that means
     * "any way you can get there".  We don't really care about SLS
     * in this case.  SelectRouteContextInfo may return a link that
     * is down, but I guess that's ok, because traffic will be at
     * some point be transferred.
     *
     * NOTE: ITU can't rotate SLS bits.
     */
    /* MTP3_RL_SET_SLS(mtp3->label, rinfo.sls); */

    return HMCG_Main_TTC(MTP3_SMH_HMRT,
                           SMH_TRIGGER_L3_L2_MSG,
                           sif, len,
                           rinfo.linkSet,
                           rinfo.linkCode,
                           rinfo.rkey);
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
TrafficManagementMessage(ITS_OCTET *sif, ITS_USHORT len,
                         ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    ITS_USHORT dest;
    MTP3_HEADER *mtp3 = (MTP3_HEADER *)&sif[1];
    ITS_UINT dpc;
    SNMM_MESSAGE *snmm = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER) +
                                          sizeof(ITS_OCTET));
    ITS_OCTET ni, sls;
    ROUTE_MatchInfo rinfo;
    SS7_Destination *d;

    dpc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
    ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;
    sls = MTP3_RL_GET_SLS(mtp3->label);
    rinfo.rkey = 0;

    /*
     * special case here.  ITU only has 4 bits of SLS and can't
     * do combined link sets based only on SLS.
     */
    sls <<= 1;

    if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, dpc,
                                      DONT_CARE, ROUTE_DPC_NI,
                                      FAMILY_JAPAN,
                                      ni,
                                      ITS_SS7_DEFAULT_LINK_SET,
                                      ITS_SS7_DEFAULT_LINK_CODE,
                                      ITS_SS7_DEFAULT_PRI,
                                      sls) != ITS_SUCCESS)
    {
        MTP3_Alarm_TTC(2503, __FILE__, __LINE__,
                        "dpc=%d:ls=%d:lc=%d:family=%s",
                         dpc,linkSet,linkCode, "TTC");

        /* can't recover, can't continue */
        return (ITS_EPROTERR);
    }

    d = ROUTE_FindDestination(dpc, ni, FAMILY_JAPAN);
    dest = ROUTE_SelectRouteContextInfo(&rinfo);

    /*
     * NOTE: at this point, rinfo.sls has the rotated SLS bits.
     * Also, rinfo.rkey has the index of the routing entry used.
     *
     * NOTE: ITU can't rotate SLS bits.
     */

    /* MTP3_RL_SET_SLS(mtp3->label, rinfo.sls); */

    /* management inhibit message? */
    if (SNMM_HC0_GET(*snmm) == SNMM_HC0_MIM)
    {
        /* force uninhibit? */
        if (SNMM_HC1_GET(*snmm) == SNMM_HC1_LFU)
        {
            /* select link coded in SLC */
            return HMCG_Main_TTC(MTP3_SMH_HMRT, SMH_TRIGGER_L3_L2_MSG,
                                   sif, len,
                                   linkSet,
                                   linkCode,
                                   rinfo.rkey);
        }
        /* uninhibit or uninhibit ack? */
        else if (SNMM_HC1_GET(*snmm) == SNMM_HC1_LUN ||
                 SNMM_HC1_GET(*snmm) == SNMM_HC1_LUA)
        {
            /* DPC accessible? */
            /*
             * Houston, we have a problem.  Some tests like the first
             * form, some prefer the second.  It would be nice to know
             * why.  I suspect it's when the first form sees the allowed
             * flag.
             */
            /*if (d->status != DESTINATION_UNAVAILABLE)*/
            if  (dest != ITS_NO_SRC && dest != ITS_INVALID_SRC) 
            {
                /* yes, select an available link */
                return HMCG_Main_TTC(MTP3_SMH_HMRT,
                                       SMH_TRIGGER_L3_L2_MSG,
                                       sif, len,
                                       rinfo.linkSet,
                                       rinfo.linkCode,
                                       rinfo.rkey);
            }

            /* select link coded in SLC */

            return HMCG_Main_TTC(MTP3_SMH_HMRT,
                                   SMH_TRIGGER_L3_L2_MSG,
                                   sif, len,
                                   linkSet,
                                   linkCode,
                                   rinfo.rkey);
        }

        /* select an available link */
        return HMCG_Main_TTC(MTP3_SMH_HMRT,
                               SMH_TRIGGER_L3_L2_MSG,
                               sif, len,
                               rinfo.linkSet,
                               rinfo.linkCode,
                               rinfo.rkey);
    }
    /* destination accessible? */
    if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
    {
        MTP3_Alarm_TTC(2415, __FILE__, __LINE__, "dpc=%d:ni=%d:family=%s",dpc,ni, "TTC");

        MTP3_Alarm_TTC(2503, __FILE__, __LINE__,
                        "dpc=%d:ls=%d:lc=%d:family=%s",
                         dpc,linkSet,linkCode, "TTC");

        return (ITS_EINVALIDARGS);
    }

    /* changeback message? */
    if (SNMM_HC0_GET(*snmm) == SNMM_HC0_CHM)
    {
        /* changeback declaration */
        if (SNMM_HC1_GET(*snmm) == SNMM_HC1_CBD)
        {
            /*
             * Select an alternative link based on the SLC and the
             * changeback code.  Interpretation, anyone?  Yes.  Use
             * what the caller gave you.
             */
            return HMCG_Main_TTC(MTP3_SMH_HMRT,
                                   SMH_TRIGGER_L3_L2_MSG,
                                   sif, len,
                                   linkSet,
                                   linkCode,
                                   rinfo.rkey);
        }
        /* changeback ack */
        else if (SNMM_HC1_GET(*snmm) == SNMM_HC1_CBA)
        {
            /* select linkSet, link based on loadsharing and SLS */
            return HMCG_Main_TTC(MTP3_SMH_HMRT,
                                   SMH_TRIGGER_L3_L2_MSG,
                                   sif, len,
                                   linkSet,
                                   linkCode,
                                   rinfo.rkey);
        }
        /* changeover */
        else if (SNMM_HC1_GET(*snmm) == SNMM_HC1_COO ||
                 SNMM_HC1_GET(*snmm) == SNMM_HC1_XCO)
        {
            /* select linkSet, link based on what TLAC or TCOC tells us */
            return HMCG_Main_TTC(MTP3_SMH_HMRT,
                                   SMH_TRIGGER_L3_L2_MSG,
                                   sif, len,
                                   linkSet,
                                   linkCode,
                                   rinfo.rkey);
        }
        /* changeover ack */
        else if (SNMM_HC1_GET(*snmm) == SNMM_HC1_COA ||
                 SNMM_HC1_GET(*snmm) == SNMM_HC1_XCA)
        {
            /* select linkSet, link based on what TLAC or TCOC tells us */
            return HMCG_Main_TTC(MTP3_SMH_HMRT,
                                   SMH_TRIGGER_L3_L2_MSG,
                                   sif, len,
                                   linkSet,
                                   linkCode,
                                   rinfo.rkey);
        }
    }
    /* changeback message? */
    else if (SNMM_HC0_GET(*snmm) == SNMM_HC0_ECM)
    {
        /* changeover */
        if (SNMM_HC1_GET(*snmm) == SNMM_HC1_ECO)
        {
            MTP3_Alarm_TTC(2515, __FILE__, __LINE__, "ls=%d:lc=%d:family=%s",
                            linkSet,linkCode, "TTC");

            /* select linkSet, link based on what TLAC or TCOC tells us */
            return HMCG_Main_TTC(MTP3_SMH_HMRT,
                                   SMH_TRIGGER_L3_L2_MSG,
                                   sif, len,
                                   linkSet,
                                   linkCode,
                                   rinfo.rkey);
        }
        /* changeover ack */
        else if (SNMM_HC1_GET(*snmm) == SNMM_HC1_ECA)
        {
            /* select linkSet, link based on what TLAC or TCOC tells us */
            return HMCG_Main_TTC(MTP3_SMH_HMRT,
                                   SMH_TRIGGER_L3_L2_MSG,
                                   sif, len,
                                   linkSet,
                                   linkCode,
                                   rinfo.rkey);
        }
    }

    if  (dest != ITS_NO_SRC && dest != ITS_INVALID_SRC) 
    {
        /* select an available link */
        return HMCG_Main_TTC(MTP3_SMH_HMRT,
                               SMH_TRIGGER_L3_L2_MSG,
                               sif, len,
                               rinfo.linkSet,
                               rinfo.linkCode,
                               rinfo.rkey);
    }

    return HMCG_Main_TTC(MTP3_SMH_HMRT,
                               SMH_TRIGGER_L3_L2_MSG,
                               sif, len,
                               linkSet,
                               linkCode,
                               rinfo.rkey);
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
TestControlMessage(ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER *mtp3 = (MTP3_HEADER *)&sif[1];
    ITS_UINT dpc;
    ITS_OCTET ni, sls;
    ROUTE_MatchInfo rinfo;
    ITS_USHORT dest;

    dpc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
    ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;
    sls = MTP3_RL_GET_SLS(mtp3->label);

    /*
     * special case here.  ITU only has 4 bits of SLS and can't
     * do combined link sets based only on SLS.
     */
    sls <<= 1;

    /* use linkSet, linkCode here */
    if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, dpc,
                                      DONT_CARE, ROUTE_DPC_NI,
                                      FAMILY_JAPAN,
                                      ni,
                                      linkSet,
                                      linkCode,
                                      ITS_SS7_DEFAULT_PRI,
                                      sls) != ITS_SUCCESS)
    {
        MTP3_Alarm_TTC(2504, __FILE__, __LINE__,
                        "dpc=%d:ls=%d:lc=%d:family=%s",
                         dpc,linkSet,linkCode, "TTC");
        /* can't recover, can't continue */
        return (ITS_EPROTERR);
    }

    dest = ROUTE_SelectRouteContextInfo(&rinfo);
    /*
     * NOTE: at this point, rinfo.sls has the rotated SLS bits.
     * Also, rinfo.rkey has the index of the routing entry used.
     *
     * NOTE: ITU can't rotate SLS bits.
     */

    /* MTP3_RL_SET_SLS(mtp3->label, rinfo.sls); */

    /* DPC accessible? SDL doesn't have this, but it makes sense. */
    if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
    {
        MTP3_Alarm_TTC(2416, __FILE__, __LINE__, "dpc=%x:ni=%x:family=%s",dpc,ni, "TTC");

        MTP3_Alarm_TTC(2504, __FILE__, __LINE__,
                        "dpc=%d:ls=%d:lc=%d:family=%s",
                        dpc,linkSet,linkCode, "TTC");

        return (ITS_SUCCESS);
    }

    /*
     * select a link == SLC.  As long as the initiator gives the right
     * link code, this is ok.
     */
    return HMCG_Main_TTC(MTP3_SMH_HMRT,
                           SMH_TRIGGER_L3_L2_MSG,
                           sif, len,
                           linkSet, linkCode,
                           rinfo.rkey);
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
ResetLinkMap(ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkSetPtr ls;

    ls = LINKSET_FindLinkSet(linkSet);
    if (ls == NULL)
    {
        MTP3_WARNING(("Can't find linkSet to adjust\n"));

        return;
    }

    /* move SLS codes away */
    LINKSET_RemoveActiveLink(ls, linkCode);
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
SetCurrentRoute(ITS_OCTET *sif, ITS_USHORT len, ITS_OCTET linkSet)
{
    MTP3_HEADER *mtp3 = (MTP3_HEADER *)&sif[1];
    ROUTE_MatchInfo rinfo;
    ITS_UINT pc;
    ITS_OCTET ni;

    pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
    ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

    /* get the match info */
    if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                      REMOTE_ROUTE, ROUTE_DPC_NI,
                                      FAMILY_JAPAN,
                                      ni,
                                      linkSet,
                                      ITS_SS7_DEFAULT_LINK_CODE,
                                      ITS_SS7_DEFAULT_LINK_PRI,
                                      ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
    {
        /* give up. */
        return;
    }

    ROUTE_SetCurrentRoute(&rinfo);
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
HMRT_Main_TTC(MTP3_SubSystems src, SMH_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_TRACE_ENTRY_TTC(MTP3_SMH_HMRT, src, trigger, sif, len,
                          linkSet, linkCode);

    /*
     * set this Bool to false;
     * should be set to true only if Message is for Routing.
     */
     TRIGGER_FOR_ROUTING = ITS_FALSE;

    /* HMRT */
    switch (trigger)
    {
    case SMH_TRIGGER_UPDATE_ROUTING_TABLES:
        ITS_C_ASSERT(src == MTP3_STM_TCOC ||
                     src == MTP3_STM_TCBC ||
                     src == MTP3_STM_TFRC ||
                     src == MTP3_STM_TCRC);
        if (src == MTP3_STM_TCOC)
        {
            /*
             * if src is TCOC, recalculate SLS/SLC map, removing
             * the indicated link.
             */
            ResetLinkMap(linkSet, linkCode);
        }
        else if (src == MTP3_STM_TCBC)
        {
            /*
             * if src is TCBC, recalculate SLS/SLC map, adding
             * the indicated link.
             *
             * This is a NOOP now.  The changeback code has to
             * be smarter than this.
             */
        }
        else if (src == MTP3_STM_TFRC)
        {
            /*
             * if src is TFRC, change the current route to the
             * newly indicated one.
             */
            SetCurrentRoute(sif, len, linkSet);
        }
        else if (src == MTP3_STM_TCRC)
        {
            /*
             * if src is TCRC, change the current route back to
             * the indicated one.
             */
            SetCurrentRoute(sif, len, linkSet);
        }
        break;

    case SMH_TRIGGER_MSG_FOR_ROUTING:
        ITS_C_ASSERT(src == MTP3_SMH_HMDC ||
                     src == MTP3_SMH_HMDT);
        /* fix for bug 162 */
        TRIGGER_FOR_ROUTING = ITS_TRUE;
        return MessageForRouting(sif, len, linkSet, linkCode);

    case SMH_TRIGGER_L4_L3_MSG:
        ITS_C_ASSERT(src == MTP3_L4);

        return  MessageForRouting(sif, len, linkSet, linkCode);


    case SMH_TRIGGER_ROUTE_MGMT_MSG:
        ITS_C_ASSERT(src >= MTP3_SRM_RTPC &&
                     src <= MTP3_SRM_RTRC);
        return MessageForRouting(sif, len, linkSet, linkCode);

    case SMH_TRIGGER_LINK_MGMT_MSG:
        ITS_C_ASSERT(src >= MTP3_SLM_LLSC &&
                     src <= MTP3_SLM_LSDA);
        return LinkManagementMessage(sif, len, linkSet, linkCode);

    case SMH_TRIGGER_TRAFFIC_MGMT_MSG:
        ITS_C_ASSERT(src >= MTP3_STM_TLAC &&
                     src <= MTP3_STM_TPRC);
        return TrafficManagementMessage(sif, len, linkSet, linkCode);

    case SMH_TRIGGER_TEST_CONTROL_MSG:
        return TestControlMessage(sif, len, linkSet, linkCode);

    default:
        MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
        PEG_IncrPeg(TTC_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);

        break;
    }

    /* NOTREACHED */
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
static ITS_BOOLEAN
ShouldDiscard(ITS_OCTET congLevel, ITS_OCTET pri)
{
    /*
     * discard if message is at priority lower that one less than the
     * the current congestion level.  IMPLEMENTATION CHOICE.
     */
    if ((congLevel - pri) > 1)
    {
        return (ITS_TRUE);
    }

    return (ITS_FALSE);
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
static ITS_BOOLEAN
DangerOfCongestion(MTP3_HEADER *mtp3, ITS_OCTET pri)
{
    /*
     * implementation dependent
     */
    return (ITS_FALSE);
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
static ITS_BOOLEAN
TransmitBufferFull()
{
    /*
     * implementation choice.  We never say this.
     */
    return (ITS_FALSE);
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
HMCG_Main_TTC(MTP3_SubSystems src, SMH_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode,
               ITS_UINT whichEntry)
{
    MTP3_HEADER *mtp3 = (MTP3_HEADER *)&sif[1];
    SS7_Destination *rc;
    ITS_UINT dpc;
    ITS_OCTET pri, ni, congestion_level;
    int ret;
	SS7_LinkPtr ln;


    MTP3_TRACE_ENTRY_TTC(MTP3_SMH_HMCG, src, trigger, sif, len,
                          linkSet, linkCode);

    pri = MTP3_HDR_GET_SIO(*mtp3) & MTP3_MPC_MASK;
    dpc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
    ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

    if ((rc = ROUTE_FindDestination(dpc, ni, FAMILY_JAPAN)) == NULL)
    {
        MTP3_DEBUG(("FindDestination failed, return.\n"));

        MTP3_Alarm_TTC(2419, __FILE__, __LINE__, "dpc=%x:ni=%x:family=%s",dpc,ni, "TTC");

        return (ITS_SS7_DEFAULT_LINK_SET);
    }

    /* Increment the Link Congestion Indications OM based on different levels */
    congestion_level = 0; 
    if ( (ln = LINK_FindLinkNoLock(linkSet, linkCode)) != NULL)
    {
        congestion_level = ln->congLevel;

        switch(congestion_level)
        {
            case 1:
            LinkOmImage[omBuf.activeOm].MTP3LinkStat[linkSet][linkCode].l1CongCount++;
            break;
            case 2:
            LinkOmImage[omBuf.activeOm].MTP3LinkStat[linkSet][linkCode].l2CongCount++;
            break;
            case 3:
            LinkOmImage[omBuf.activeOm].MTP3LinkStat[linkSet][linkCode].l3CongCount++;
            break;
            default:
            break;
        }
    }

    /*
     * we found the destination so we can see if we should queue or
     * go ahead and send.
     */
    if (rc->entries[whichEntry]->qPut)
    {
        ITS_EVENT ev;

        /*
         * we have to queue.  SLS rotation has already been performed,
         * so put it in L2 format to help us remember that.
         */
        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, len + 3 * sizeof(ITS_OCTET));

        L2_MSG_TYPE(&ev) = L3_L2_DATA;
        L2_LINK_SET(&ev) = linkSet;
        L2_LINK_CODE(&ev) = linkCode;

        if (len)
        {
            memcpy(L2_LINK_DATA(&ev), sif, len);
        }

        return DSMQUEUE_Enqueue(rc->entries[whichEntry]->crBuf, ev);
    }

    /* is pri < congestion status */
    if (pri < rc->entries[whichEntry]->congLevel)
    {
        RTCC_Main_TTC(MTP3_SMH_HMCG,
                       SRM_TRIGGER_SEND_TRANSFER_CONTROL,
                       sif, len,
                       linkSet, linkCode);

        /* is pri < discard status */
        if (ShouldDiscard(rc->entries[whichEntry]->congLevel, pri))
        {
            return (ITS_ENOMSG);
        }

        /* transmit buffer full */
        if (TransmitBufferFull(linkSet, linkCode))
        {
            return (ITS_ENOMSG);
        }

        ret = MTP2_SendData_TTC(linkSet, linkCode,
                                  L3_L2_DATA, sif, len);

        return (ret);
    }
    else if (DangerOfCongestion(mtp3, pri))
    {
        TSRC_Main_TTC(MTP3_SMH_HMDC,
                        STM_TRIGGER_DANGER_OF_CONGESTION,
                        sif, len,
                        linkSet, linkCode);
    }

    ret = MTP2_SendData_TTC(linkSet, linkCode,
                              L3_L2_DATA, sif, len);

    return (ret);
}

/*
 * debugging.
 */
static char *toL2[] =
{
    "START",
    "STOP",
    "RESUME",
    "CLEAR_BUFFERS",
    "CLEAR_RTB",
    "EMERGENCY",
    "EMERGENCY_CEASE",
    "DATA",
    "RETRIEVE_BSNT",
    "RETRIEVE_MSGS",
    "FLOW_CONTROL_START",
    "FLOW_CONTROL_STOP",
    "LPO",
    "LPR"
};

static char *toL1[] =
{
    "CONNECT",
    "DISCONNECT"
};

#define MUST_PASS(x) \
    (((x)[1] & MTP3_SIO_UP_MASK) <= MTP3_SIO_SLTM_SPEC)

/*
 * These bits indicate the level messages are being directed
 * to.
 */
#define L2_BITS 0x80
#define L1_BITS 0x90

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
MTP2_SendData_TTC(ITS_OCTET linkSet, ITS_OCTET linkCode,
                   ITS_OCTET command,
                   ITS_OCTET *data, ITS_USHORT len)
{
    SS7_LinkPtr ln;
    ITS_EVENT ev;
    ITS_USHORT idx;
    char *cmd;
    int i;

    if (TRACE_IsLevelOn(MTP3_TTC_TraceData,
                        MTP3_TRACE_DEBUG))
    {
        printf("===> MTP2_SendData_TTC: len: %d \n", len);
        printf("====> DATA <====\n");
        for (i= 0; i < len; i++)
        {
            printf("%02x ", data[i]);
        }
        printf("\n");
    }

    if ((command & L1_BITS) == L1_BITS)
    {
        cmd = toL1[command - L1_BITS];
    }
    else if (command & L2_BITS)
    {
        cmd = toL2[command - L2_BITS];
    }
    else
    {
        cmd = "UNKNOWN";
    }

    if (command != L3_L2_DATA)
    {
        MTP3_DEBUG(("MTP2Send: command %s linkSet/Code: %d:%d\n",
                    cmd, linkSet, linkCode));

        if (TRACE_IsLevelOn(MTP3_TTC_TraceData, MTP3_TRACE_DEBUG))
        {
            if (data && len > 0)
            {
                for (idx = 0; idx < len; idx++)
                {
                    TRACE_RAW(MTP3_TTC_TraceData, MTP3_TRACE_DEBUG,
                          ("%02x ", data[idx]));

                    if (!((idx+1) % 25))
                    {
                        TRACE_RAW(MTP3_TTC_TraceData, MTP3_TRACE_DEBUG,
                              ("\n"));
                    }
                }
                if ((idx+1) % 25)
                {
                    TRACE_RAW(MTP3_TTC_TraceData, MTP3_TRACE_DEBUG, ("\n"));
                }
            }
            else
            {
                TRACE_RAW(MTP3_TTC_TraceData, MTP3_TRACE_DEBUG, ("  NO DATA\n"));
            }
        }
    }

    if ((ln = LINK_FindLinkNoLock(linkSet, linkCode)) == NULL)
    {
        MTP3_ERROR(("Can't find link to send to\n"));

        MTP3_Alarm_TTC(2420, __FILE__, __LINE__, "ls=%d:lc=%d:family=%s", 
                         linkSet, linkCode, "TTC");

        return (ITS_EINVALIDARGS);
    }

    /*
     * break into L2 format here
     */
    ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, len + 3 * sizeof(ITS_OCTET));

    L2_MSG_TYPE(&ev) = command;
    L2_LINK_SET(&ev) = linkSet;
    L2_LINK_CODE(&ev) = linkCode;

    if ((command == L3_L2_DATA) && (!MUST_PASS(data) && ln->qPut))
    {
        int ret;
        MTP3_EventRec evRec;

        ITS_OCTET sio;
        MTP3_HEADER hdr; 
    
        memcpy(&hdr, &data[1], sizeof(MTP3_HEADER));
        sio = MTP3_HDR_GET_SIO_TTC(hdr);
    
        printf("===>>> SIO: %02x\n", sio);

        memcpy(L2_LINK_DATA(&ev), data, len);

        evRec.seqNo = ln->linkSet->seqNum++;
        evRec.event = ev;

        ret = DSMQUEUE_Enqueue(ln->cocbBuf,
                       MTP3EventRecToItsEvent_TTC(evRec) );

        ITS_EVENT_TERM(&evRec.event);

        return ret;
    }
    if (len)
    {
        
        SS7_LinkSetPtr ls = NULL;
        ls = LINKSET_FindLinkSet(linkSet);

        if (ls->is9Bit || command != L3_L2_DATA )
        {
            /* For TTC 9-Bit SLS, the routing label for messages
             * is always 48bits. MTP3 stack accepts only 48bits RLs
             * so no change is required here. Send 48-byte RL to Network
             */
            memcpy(L2_LINK_DATA(&ev), data, len);
        }
        else
        {
           /* for 4-Bit and 5-Bit SLS, Management messages and SLT
            * message uses 48bit Routing Label. Data Messages use
            * 48-bit sls. Therefore, for IntelliNet stack to process
            * this message, we should remove the spare octet at the end
            * of 48-bit routing label of the outgoing MTP3 User data
            * message. 
            */

            ITS_OCTET sio;
            MTP3_HEADER hdr; 

            memcpy(&hdr, &data[1], sizeof(MTP3_HEADER));
            sio = MTP3_HDR_GET_SIO_TTC(hdr);

            printf("===> SIO: %02x\n", sio);


            switch (sio & MTP3_SIO_UP_MASK)
            {
                case MTP3_SIO_SNMM: /* signalling network management */
                case MTP3_SIO_SLTM_REG:
                case MTP3_SIO_SLTM_SPEC:

                /* so no change is required here
                 */
                memcpy(L2_LINK_DATA(&ev), data, len);

                break;
            default: 
                printf("Fixing User data len\n");
                memcpy(L2_LINK_DATA(&ev), data, sizeof(MTP3_HEADER) - 1);
                memcpy(&L2_LINK_DATA(&ev)[sizeof(MTP3_HEADER)], 
                       &data[sizeof(MTP3_HEADER) + 1], len - sizeof(MTP3_HEADER));
	        ev.len--;
           
            }

        }
    }

    if (command == L3_L2_DATA)
    {
        return TRANSPORT_PutEvent(ln->id, &ev);
    }
    else
    {
        int ret;

        ret = TRANSPORT_PutEvent(ln->id, &ev);

        if (ret != ITS_SUCCESS)
        {
            ITS_EVENT fail;

            if (command == L3_L2_RETRIEVE_BSNT)
            {
                /* generate artificial event back to MTP3 saying we can't get
                 * it. */
                ITS_EVENT_INIT(&fail, ln->id, 3 * sizeof(ITS_OCTET));

                fail.data[0] = L2_L3_BSNT_NOT_RETRIEVABLE;
                fail.data[1] = linkSet;
                fail.data[2] = linkCode;

                TRANSPORT_PutEvent(ITS_MTP3_SRC, &fail);
            }
            else if (command == L3_L2_RETRIEVE_MSGS)
            {
                /* generate artificial event back to MTP3 */
                ITS_EVENT_INIT(&fail, ln->id, 3 * sizeof(ITS_OCTET));

                fail.data[0] = L2_L3_RETRIEVAL_NOT_POSSIBLE;
                fail.data[1] = linkSet;
                fail.data[2] = linkCode;

                TRANSPORT_PutEvent(ITS_MTP3_SRC, &fail);
            }
        }

        return (ret);
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
 ****************************************************************************/
int
MTP2_ReceiveData_TTC(ITS_EVENT *ev,
                      ITS_OCTET *linkSet, ITS_OCTET *linkCode,
                      ITS_OCTET *data, ITS_USHORT *len)
{
    SS7_LinkSetPtr ls = NULL;
    int i;

    ITS_C_ASSERT(ev->len >= (3 * sizeof(ITS_OCTET)));

    *len = ev->len - (2 * sizeof(ITS_OCTET));

    *linkSet = L2_LINK_SET(ev);
    *linkCode = L2_LINK_CODE(ev);
    *data = L2_MSG_TYPE(ev);

    ls = LINKSET_FindLinkSet(*linkSet);

    if (len)
    {
        if (ls->is9Bit || data[0] != L2_L3_DATA )
        {
            /* For TTC 9-Bit SLS, the routing label for messages
             * is always 48bits. MTP3 stack accepts only 48bits RLs
             * so no change is required here
             */
            memcpy(&data[1], L2_LINK_DATA(ev), *len);
        }
        else
        {
           /* for 4-Bit and 5-Bit SLS, Management messages and SLT
            * message uses 48bit Routing Label. Data Messages use
            * 48-bit sls. Therefore, for IntelliNet stack to process
            * this message, we should add the spare octet at the end
            * of 40-bit routing label of the incoming MTP3 User data
            * message. 
            */

            ITS_OCTET sio;
            MTP3_HEADER hdr; 

            memcpy(&hdr, L2_LINK_DATA(ev), sizeof(MTP3_HEADER));
            sio = MTP3_HDR_GET_SIO_TTC(hdr);

            switch (sio & MTP3_SIO_UP_MASK)
            {
                case MTP3_SIO_SNMM: /* signalling network management */
                case MTP3_SIO_SLTM_REG:
                case MTP3_SIO_SLTM_SPEC:

             /* so no change is required here
             */
                memcpy(&data[1], L2_LINK_DATA(ev), *len);

                break;
            default: 
                memcpy(&data[1], L2_LINK_DATA(ev), sizeof(MTP3_HEADER) - 1);
	        data[sizeof(MTP3_HEADER)]=0; /* spare octet in RL */
                memcpy(&data[sizeof(MTP3_HEADER)+1], &L2_LINK_DATA(ev)[sizeof(MTP3_HEADER) -1 ], *len - sizeof(MTP3_HEADER));
	        (*len)++;
           
            }
        }
        printf("=======> DATA From L2 <=======\n");
        for (i = 0; i < *len; i++)
        {
            printf("%02x ", data[i]);            
        }
	printf("\n");

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
 ****************************************************************************/
ITSSS7DLLAPI int
MTP3_INodeEvent_TTC(TPOOL_THREAD *thr, ITS_EVENT *ev)
{

    switch (L2_MSG_TYPE(ev))
    {
    case L3_L2_START:
    case L3_L2_STOP:
    case L3_L2_RESUME:
    case L3_L2_CLEAR_BUFFERS:
    case L3_L2_CLEAR_RTB:
    case L3_L2_EMERGENCY:
    case L3_L2_EMERGENCY_CEASE:
    case L3_L2_DATA:
    case L3_L2_RETRIEVE_BSNT:
    case L3_L2_RETRIEVE_MSGS:
    case L3_L2_FLOW_CONTROL_START:
    case L3_L2_FLOW_CONTROL_STOP:
    case L3_L2_LOCAL_PROCESSOR_OUT:
    case L3_L2_LOCAL_PROCESSOR_REC:
    {
        char *cmd;
        ITS_OCTET command = L2_MSG_TYPE(ev);

        if ((command & L1_BITS) == L1_BITS)
        {
            cmd = toL1[command - L1_BITS];
        }
        else if (command & L2_BITS)
        {
            cmd = toL2[command - L2_BITS];
        }
        else
        {
            cmd = "UNKNOWN";
        }

        MTP3_DEBUG(("MTP3_INodeEvent: Receive Inter-Node Event for local MTP2:"
                    "\ncommand= %s linkSet= %d linkCode= %d\n", cmd,
                     L2_LINK_SET(ev),  L2_LINK_CODE(ev) ));

        MTP2_SendData_TTC(L2_LINK_SET(ev),
                            L2_LINK_CODE(ev),
                            L2_MSG_TYPE(ev),
                            L2_LINK_DATA(ev),
                            (ITS_USHORT)(ev->len -
                            3 * sizeof(ITS_OCTET)));

        break;
    }
    case MTP3_MSG_USER_DATA:
    {
        /*This event is comming from backup node*/
        ITS_USHORT dest =0;

        dest = MTP3_UserPartOwner((ITS_OCTET)(ev->src & MTP3_SIO_UP_MASK));
        if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
        {
            ev->src = ITS_MTP3_SRC;
            TRANSPORT_PutEvent(dest, ev);
        }
        return !ITS_SUCCESS;
    }        
    case MTP3_MSG_RESUME:
    {
      /* Resume Indication is received from the Standby Node */
        ITS_USHORT dest =0;

        dest = MTP3_UserPartOwner((ITS_OCTET)(ev->src & MTP3_SIO_UP_MASK));
	MTP3_DEBUG(("MTP3_InterNode: Received RESUME Indication from Standby Node: Dest %u\n", dest));
        if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
        {
            ev->src = ITS_MTP3_SRC;
#if defined(CPOT_SPLIT_STACK)
            dest = ITS_SCCP_CCITT_SRC;
#else
            dest = ITS_SCCP_TTC_SRC;
#endif
            CALLBACK_CallCallbackList(MTP3_ManagementCallbacks,
		                      NULL, (ITS_POINTER)ev);

            TRANSPORT_PutEvent(dest, ev);
	    MTP3_DEBUG(("MTP3_InterNode: RESUME Indication sent to Dest %u\n", dest));
        } 
	else
	{
	    MTP3_ERROR(("\nMTP3_InterNode: Could not send RESUME Indicationto MTP3 User Part (Dest %u)\n", dest));

	}

        return !ITS_SUCCESS;
    }

    case MTP3_MSG_PAUSE:
    {
        MTP3_DEBUG(("\nMTP3_InterNode: Received PAUSE Indication from Standby Node\n"));
        ev->src = ITS_MTP3_SRC;

        /* Invoke the Callback for DEST INACCESS processing (i.e. propagating PAUSE) */
        CALLBACK_CallCallbackList(MTP3_ManagementCallbacks,
                                       NULL, (ITS_POINTER)ev);
        return !ITS_SUCCESS;
    }
    default:
        PEG_IncrPeg(TTC_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
        /* unknown command to L2 */
        break;
    }

    return ITS_SUCCESS;
}
