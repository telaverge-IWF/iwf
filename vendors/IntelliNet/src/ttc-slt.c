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
 *  ID: $Id: ttc-slt.c,v 9.5 2008/06/17 06:38:02 nvijikumar Exp $  
 *
 * LOG: $Log: ttc-slt.c,v $
 * LOG: Revision 9.5  2008/06/17 06:38:02  nvijikumar
 * LOG: Updated for ITU over TTC support (Split Stack)
 * LOG: ACC-CG-SDS-SS7-V1.0.02::D7040,D7080
 * LOG:
 * LOG: Revision 9.4  2008/06/12 12:51:50  nvijikumar
 * LOG: Renaming from COT to CPOT (CCITT prime - 16bit)
 * LOG: ACC-CG-SDS-SS7-V1.0.02::ID:: D6030
 * LOG:
 * LOG: Revision 9.3  2008/06/04 10:38:48  ssingh
 * LOG: ALU porting, B-0100LX-LUSG-00 (june 04,2008 base)
 * LOG:
 * LOG: Revision 9.2  2007/01/11 12:43:41  yranade
 * LOG: Merge changes from 6.5.3 and Lucent branches
 * LOG:
 * LOG: Revision 9.1.10.5  2007/10/05 11:18:00  mshanmugam
 * LOG: CPOT Stack support as per design Id D0060
 * LOG:
 * LOG: Revision 9.1.10.4  2007/05/18 11:21:39  raghavendrabk
 * LOG: Changes for Alarm Optimisation
 * LOG:
 * LOG: Revision 9.1.10.3  2007/02/02 14:20:05  raghavendrabk
 * LOG: Parallel Stack changes for Alarms and Statistics
 * LOG:
 * LOG: Revision 9.1.10.2  2006/12/23 10:05:37  randresol
 * LOG: Modifications to allow TTC and ITU stacks to run in parallel
 * LOG:
 * LOG: Revision 9.1.10.1  2006/11/08 15:56:09  mshanmugam
 * LOG: Fix for Bug id:4401  SRT,SRA message pegs implementation (skatta)
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
 * LOG: Revision 7.5.2.2.8.1.8.3  2005/01/25 11:36:14  snagesh
 * LOG: OAM Bug fixes for bugs 1419,1420
 * LOG:
 * LOG: Revision 7.5.2.2.8.1.8.2  2004/12/31 07:29:24  sbabu
 * LOG: MTP3 OAM Changes
 * LOG:
 * LOG: Revision 7.5.2.2.8.1.8.1  2004/12/17 03:57:46  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.5.2.2.8.1  2004/08/10 12:14:46  kannanp
 * LOG: Changes for MTP3 pegs, alarms & MMLs - propagated from TCS.
 * LOG:
 * LOG: Revision 7.5.2.2  2003/04/21 12:14:10  ttipatre
 * LOG: Bug 156 fixed for ITU.
 * LOG:
 * LOG: Revision 7.5.2.1  2003/02/21 01:42:34  randresol
 * LOG: Add more alarms
 * LOG:
 * LOG: Revision 7.5  2003/02/13 10:38:41  ttipatre
 * LOG: New Alarms Added.
 * LOG:
 * LOG: Revision 7.4  2002/12/24 19:30:13  randresol
 * LOG: Mark slt2 timer expired
 * LOG:
 * LOG: Revision 7.3  2002/12/24 07:48:27  ttipatre
 * LOG: Link Level Pegs.
 * LOG:
 * LOG: Revision 7.2  2002/11/10 19:48:27  randresol
 * LOG: Remove Shared Timers for SLT's
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:28  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.4  2002/08/16 22:07:09  mmiers
 * LOG: Include China variant.
 * LOG:
 * LOG: Revision 6.3  2002/06/13 20:35:07  ttipatre
 * LOG: Adding MTP3 Pegs and Alarms
 * LOG:
 * LOG: Revision 6.2  2002/05/15 15:06:48  randresol
 * LOG: Integrate shared behaviors and timers with management interface
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:39  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.5  2002/01/29 19:56:26  mmiers
 * LOG: warning removal
 * LOG:
 * LOG: Revision 5.4  2001/12/29 00:12:36  mmiers
 * LOG: ITU uses SLS key for SLC
 * LOG:
 * LOG: Revision 5.3  2001/12/28 20:31:05  mmiers
 * LOG: SLC is SLS in ITU
 * LOG:
 * LOG: Revision 5.2  2001/12/28 19:31:46  mmiers
 * LOG: Fix for ITU
 * LOG:
 * LOG: Revision 5.1  2001/12/06 22:39:05  mmiers
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
#include <its_timers.h>

#ident "$Id: ttc-slt.c,v 9.5 2008/06/17 06:38:02 nvijikumar Exp $"

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

extern mtp3OmBuffer omBuf;

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
SLT_Main_TTC(MTP3_SubSystems src, MTP3_SubSystems dest,
               SLT_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_TRACE_ENTRY_TTC(MTP3_SLT, src, trigger, sif, len,
                           linkSet, linkCode);

    switch (trigger)
    {
    case SLT_TRIGGER_L2_MSG:                 /* from HMDT */
    case SLT_TRIGGER_START_TEST:             /* from MGMT */
    case SLT_TRIGGER_T1:                     /* from timer control */
        return SLTC_Main_TTC(src, trigger, sif, len, linkSet, linkCode);
    }

    MTP3_DEBUG(("Invalid trigger for function %d\n",
                trigger));
    PEG_IncrPeg(TTC_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);

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
 *
 * Revision history:
 *  --------------------------------------------------------------------------
 *  Name          Date        Reference                   Description
 *  --------------------------------------------------------------------------
 *  skatta     08-11-2006     Bug ID: 4401        Fix for SRT,SRA message pegs
 *
 ****************************************************************************/
int
SLTC_Main_TTC(MTP3_SubSystems src,
               SLT_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER *mtp3 = (MTP3_HEADER *)&sif[1];
    SLTM_MESSAGE *sltm = (SLTM_MESSAGE *)&sif[sizeof(MTP3_HEADER) + 
                                              sizeof(ITS_OCTET)];
    MTP3_HEADER omtp3;
    SLTM_MESSAGE osltm;
    ITS_UINT pc1, pc2;
    ITS_EVENT ev;
    ITS_OCTET dlen;
    int ret;
    SS7_LinkPtr ln;
    SS7_LinkSetPtr ls;
    MTP3_TimerContext tc;
    ITS_OCTET slc;

    printf("===== Start SLT \n\n");

    MTP3_TRACE_ENTRY_TTC(MTP3_SLT_SLTC, src, trigger, sif, len,
                           linkSet, linkCode);

    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
        MTP3_ERROR(("Invalid link %d:%d\n", linkSet, linkCode));

        return (ITS_EINVALIDARGS);
    }

    ls = ln->linkSet;
    ITS_C_ASSERT(ls != NULL);

    switch (trigger)
    {
    case SLT_TRIGGER_L2_MSG:                 /* from HMDT */
        switch (SLTM_HC0_GET(*sltm))
        {
        case SLTM_HC0_TST:
#if defined(TTC)
        case SLTM_HC0_SRA_TTC:
#endif
            switch (SLTM_HC1_GET(*sltm))
            {
            case SLTM_HC1_SLTM:
                /* Increament Link Peg for SLTM Received */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SRT_RX);

                PEG_IncrPeg(TTC_MTP3_Pegs, PEG_MTP3_SRT_RX);
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_SRT_RX);
                
                /* Increment the Link Peg for SRT Transmitted in OmBuf*/
                LinkOmImage[omBuf.activeOm].MTP3LinkStat[linkSet][linkCode].srtRx++;

                /* build SLTA, send */
                pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
                pc2 = MTP3_RL_GET_OPC_VALUE(mtp3->label);

                /*
                 * For some reason, the INET sends us our own
                 * SLTM back.  This check avoids us stopping
                 * because of that.  Used to be:
                 * ITS_C_ASSERT(pc1 == ls->lpc);
                 * ITS_C_ASSERT(pc2 == ls->adjacent);
                 */
                printf("SLTM recv: OPC: 0x%04x DPC: 0x%04x\n", pc1, pc2);
                if (pc1 != ls->lpc || pc2 != ls->adjacent)
                {
                    printf("SLT FAIL::: PC Missmatch: LocalPC: 0x%04x, AdjPC: 0x%04x\n",
                          ls->lpc, ls->adjacent   );
                    return (ITS_EINVALIDARGS);
                }

                /*Fix the problem for Bug 156 for TTC*/
                /*Don't send SLTA if Invalid SLC in SLTM */
                slc = MTP3_RL_GET_SLS(mtp3->label);

                printf("=====> SLTM: SLC %d\n", slc);

                if ((ln = LINK_FindLink(linkSet, slc)) == NULL)
                {
                    MTP3_ERROR(("Invalid slc %d\n", slc));

                    return (ITS_EINVALIDARGS);
                }

                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SLTM_REG | ls->ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, pc2);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, pc1);
                MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);
                
                dlen = SLTM_LINK_TEST_GET_LENGTH(sltm->data.linkTest);

#if defined(TTC)
                SLTM_HC0_SET(osltm, SLTM_HC0_SRA_TTC);
                /* FIXME: for TTC the 'test data' seam to be fixed length */
                dlen = 2;
#else
                SLTM_HC0_SET(osltm, SLTM_HC0_TST);
                dlen = SLTM_LINK_TEST_GET_LENGTH(sltm->data.linkTest);
#endif
                SLTM_HC1_SET(osltm, SLTM_HC1_SLTA);
                SLTM_LINK_TEST_SET_SPARE(osltm.data.linkTest, 0);
                SLTM_LINK_TEST_SET_LENGTH(osltm.data.linkTest, dlen);
                memcpy(osltm.data.linkTest.pattern, sltm->data.linkTest.pattern,
                       dlen);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
                SLTM_Encode(&ev, &omtp3, &osltm);

                /* Increament Link Peg for SLTA Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SRA_TX);

                PEG_IncrPeg(TTC_MTP3_Pegs, PEG_MTP3_SRA_TX);
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_SRA_TX);

                 /* Increment the Link Peg in OmBuf*/
                LinkOmImage[omBuf.activeOm].MTP3LinkStat[linkSet][linkCode].sraTx++;
           
                printf("====== Sending SLTA ========");

                ret = HMRT_Main_TTC(MTP3_SLT_SLTC, SMH_TRIGGER_TEST_CONTROL_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);

                return (ret);

            case SLTM_HC1_SLTA:
                ev.data = sif;
                ev.len = len;
                SLTM_Decode(&ev, &omtp3, &osltm);
                /* Increament Link Peg for SLTA Received */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SRA_RX);
 
                PEG_IncrPeg(TTC_MTP3_Pegs, PEG_MTP3_SRA_RX);
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_SRA_RX);

                /* Increment the Link Peg for SRA Recieved in OmBuf*/
                LinkOmImage[omBuf.activeOm].MTP3LinkStat[linkSet][linkCode].sraRx++;
           

                if (memcmp(ln->testPattern, osltm.data.linkTest.pattern,
                           SLTM_LINK_TEST_GET_LENGTH(osltm.data.linkTest)) == 0)
                {
                    /* if (first attempt || second attempt) */
                    if (ln->sltFlags & LINK_TEST_FIRST_ATTEMPT ||
                        ln->sltFlags & LINK_TEST_SECOND_ATTEMPT)
                    {
                        /* stop T1 */
                        if (ln->slt1 != TIMER_BAD_SERIAL)
                        {
                            TIMERS_CancelTimer(ln->slt1);
                            ln->slt1 = TIMER_BAD_SERIAL;
                        }

                        ln->sltFlags &= ~(LINK_TEST_FIRST_ATTEMPT|
                                          LINK_TEST_SECOND_ATTEMPT);

                        /*
                         * This was in SLM, but I believe belongs here
                         */
                        if (!ln->testPassed)
                        {
                            ln->testPassed = ITS_TRUE;

                            TLAC_Main_TTC(MTP3_SLM_LSAC,
                                           STM_TRIGGER_LINK_IN_SERVICE,
                                           NULL, 0,
                                           linkSet, linkCode);

                            LLSC_Main_TTC(MTP3_SLM_LSAC,
                                           SLM_TRIGGER_LINK_ACTIVE,
                                           NULL, 0,
                                           linkSet, linkCode);
                        }

                        PEG_IncrPeg(TTC_MTP3_Pegs, PEG_MTP3_SLT_PASSED);
                        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_SLT_PASSED);

                        return MGMT_Main_TTC(MTP3_SLT_SLTC,
                                              MGMT_TRIGGER_LINK_TEST_PASSED,
                                              sif, len,
                                              linkSet, linkCode);
                    }
                }
                else
                {
                    /* if (first attempt) */
                    if (ln->sltFlags & LINK_TEST_FIRST_ATTEMPT)
                    {
                        /* stop T1 */
                        if (ln->slt1 != TIMER_BAD_SERIAL)
                        {
                            TIMERS_CancelTimer(ln->slt1);
                            ln->slt1 = TIMER_BAD_SERIAL;
                        }

                        MTP3_Alarm_TTC(2507, __FILE__, __LINE__, 
                                         "ls=%x:link=%x:family=%s",
                                         linkSet, linkCode, "TTC");

                        /* build SLTM, send */
                        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
                        pc2 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
                        MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SLTM_REG | ls->ni);
                        MTP3_RL_SET_DPC_VALUE(omtp3.label, pc2);
                        MTP3_RL_SET_OPC_VALUE(omtp3.label, pc1);
                        MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

                        dlen = strlen((char *)ln->testPattern);

                        SLTM_HC0_SET(osltm, SLTM_HC0_TST);
                        SLTM_HC1_SET(osltm, SLTM_HC1_SLTM);
                        SLTM_LINK_TEST_SET_SPARE(osltm.data.linkTest, 0);
                        SLTM_LINK_TEST_SET_LENGTH(osltm.data.linkTest, dlen);
                        memcpy(osltm.data.linkTest.pattern, ln->testPattern,
                               dlen);

                        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
                        SLTM_Encode(&ev, &omtp3, &osltm);

                        /* Increament Link Peg for SLTM Transmitted */
                        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SRT_TX);

                        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_SRT_TX);
                        PEG_IncrPeg(TTC_MTP3_Pegs, PEG_MTP3_SRT_TX);

                        /*Increment Link Peg for SRT Transimtted in OM Buf*/
                        LinkOmImage[omBuf.activeOm].MTP3LinkStat[linkSet][linkCode].srtTx++;
			
                        ret = HMRT_Main_TTC(MTP3_SLT_SLTC, SMH_TRIGGER_TEST_CONTROL_MSG,
                                             ev.data, ev.len,
                                             linkSet, linkCode);
                        ITS_EVENT_TERM(&ev);

                        /* start T1 */
                        tc.timerId = MTP3_SLT_T1;
                        tc.data.linkInfo.linkSet = linkSet;
                        tc.data.linkInfo.linkCode = linkCode;

                        ln->slt1 =
                            TIMERS_StartUTimer(ITS_MTP3_SRC,
                                               __ccitt_slt_t1 * USEC_PER_MILLISEC,
                                               &tc, sizeof(MTP3_TimerContext));
                        return (ret);
                    }
                    else if (ln->sltFlags & LINK_TEST_SECOND_ATTEMPT)
                    {
                        /* stop T1 */
                        if (ln->slt1 != TIMER_BAD_SERIAL)
                        {
                            TIMERS_CancelTimer(ln->slt1);
                            ln->slt1 = TIMER_BAD_SERIAL;
                        }

                        MTP3_Alarm_TTC(2508, __FILE__, __LINE__,
                                        "ls=%x:link=%x:family=%s",
                                         linkSet,linkCode, "TTC");

                        ln->sltFlags &= ~(LINK_TEST_FIRST_ATTEMPT|
                                          LINK_TEST_SECOND_ATTEMPT);

                        ln->testPassed = ITS_FALSE;

                        /* This should also cause a link failure as well */
                        MTP2_SendData_TTC(linkSet, linkCode, L3_L2_STOP, NULL, 0);

                        PEG_IncrPeg(TTC_MTP3_Pegs, PEG_MTP3_SLT_FAILED);
                        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_SLT_FAILED);

                        LSAC_Main_TTC(MTP3_SLT_SLTC,
                                       SLM_TRIGGER_L2_OUT_OF_SERVICE,
                                       NULL, 0,
                                       linkSet, linkCode);

                        MGMT_Main_TTC(MTP3_SLT_SLTC,
                                       MGMT_TRIGGER_LINK_TEST_FAILED,
                                       sif, len,
                                       linkSet, linkCode);
                    }
                }
                break;

            default:
                MTP3_DEBUG(("SLTC_Main_TTC: Bad HC1 code %0x\n",
                            SLTM_HC1_GET(*sltm)));
                break;
            }
            break;

        default:
            MTP3_DEBUG(("SLTC_Main_TTC: Bad HC0 code %0x\n",
                        SLTM_HC0_GET(*sltm)));
            break;
        }
        break;

    case SLT_TRIGGER_START_TEST:             /* from MGMT */
        
        if (!(ln->sltFlags & LINK_TEST_FIRST_ATTEMPT) &&
            !(ln->sltFlags & LINK_TEST_SECOND_ATTEMPT))
        {
            /* set TP = 'x' */

            /* start T1 */
            tc.timerId = MTP3_SLT_T1;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->slt1 =
                TIMERS_StartUTimer(ITS_MTP3_SRC,
                                   __ccitt_slt_t1 * USEC_PER_MILLISEC,
                                   &tc, sizeof(MTP3_TimerContext));

            /* start the repeat test timer */
            if (ln->slt2 != TIMER_BAD_SERIAL)
            {
                TIMERS_CancelTimer(ln->slt2);
            }

            tc.timerId = MTP3_SLT_T2;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->slt2 =
                TIMERS_StartUTimer(ITS_MTP3_SRC,
                                   __ccitt_slt_t2 * USEC_PER_MILLISEC,
                                   &tc, sizeof(MTP3_TimerContext));

            /* set first attempt */
            ln->sltFlags |= LINK_TEST_FIRST_ATTEMPT;

            /* build SLTM, send */
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SLTM_REG | ls->ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
            MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

            dlen = strlen((char *)ln->testPattern);

            SLTM_HC0_SET(osltm, SLTM_HC0_TST);
            SLTM_HC1_SET(osltm, SLTM_HC1_SLTM);
            SLTM_LINK_TEST_SET_SPARE(osltm.data.linkTest, 0);
            SLTM_LINK_TEST_SET_LENGTH(osltm.data.linkTest, dlen);
            memcpy(osltm.data.linkTest.pattern, ln->testPattern,
                   dlen);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

            SLTM_Encode(&ev, &omtp3, &osltm);

            /* Increament Link Peg for SLTM Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SRT_TX);

            PEG_IncrPeg(TTC_MTP3_Pegs, PEG_MTP3_SRT_TX); 
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_SRT_TX);

            /*Increment Link Peg for SRT Transimtted in OM Buf*/
            LinkOmImage[omBuf.activeOm].MTP3LinkStat[linkSet][linkCode].srtTx++;

            printf("Send SLTM: OPC:0x%04x DPC:0x%04x SLC:%d\n", ls->lpc, ls->adjacent,
                    ln->linkCode);

            ret = HMRT_Main_TTC(MTP3_SLT_SLTC, SMH_TRIGGER_TEST_CONTROL_MSG,
                                 ev.data, ev.len,
                                 linkSet, linkCode);
            ITS_EVENT_TERM(&ev);

            return (ret);
        }

    case SLT_TRIGGER_T1:                     /* from timer control */
        if (ln->sltFlags & LINK_TEST_FIRST_ATTEMPT)
        {

            MTP3_Alarm_TTC(2507, __FILE__, __LINE__,
                             "ls=%x:link=%x:family=%s",
                             linkSet,linkCode, "TTC");

            /* start T1 */
            tc.timerId = MTP3_SLT_T1;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->slt1 =
                TIMERS_StartUTimer(ITS_MTP3_SRC,
                                   __ccitt_slt_t1 * USEC_PER_MILLISEC,
                                   &tc, sizeof(MTP3_TimerContext));

            ln->sltFlags &= ~LINK_TEST_FIRST_ATTEMPT;
            ln->sltFlags |= LINK_TEST_SECOND_ATTEMPT;

            /* build SLTM, send */
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SLTM_REG | ln->linkSet->ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ln->linkSet->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ln->linkSet->lpc);
            MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

            dlen = strlen((char *)ln->testPattern);

            SLTM_HC0_SET(osltm, SLTM_HC0_TST);
            SLTM_HC1_SET(osltm, SLTM_HC1_SLTM);
            SLTM_LINK_TEST_SET_SPARE(osltm.data.linkTest, 0);
            SLTM_LINK_TEST_SET_LENGTH(osltm.data.linkTest, dlen);
            memcpy(osltm.data.linkTest.pattern, ln->testPattern,
                   dlen);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

            SLTM_Encode(&ev, &omtp3, &osltm);

            /* Increament Link Peg for SLTM Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SRT_TX);

            PEG_IncrPeg(TTC_MTP3_Pegs, PEG_MTP3_SRT_TX);
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_SRT_TX);

            /*Increment Link Peg for SRT Transimtted in OM Buf*/
            LinkOmImage[omBuf.activeOm].MTP3LinkStat[linkSet][linkCode].srtTx++;

            printf("SLT TIMER: Send SLTM: OPC:0x%04x DPC:0x%04x SLC:%d\n", 
                    ln->linkSet->lpc, ln->linkSet->adjacent, ln->linkCode);

            ret = HMRT_Main_TTC(MTP3_SLT_SLTC,
                                 SMH_TRIGGER_TEST_CONTROL_MSG,
                                 ev.data, ev.len,
                                 linkSet, linkCode);
            ITS_EVENT_TERM(&ev);

            return (ret);
        }
        else if (ln->sltFlags & LINK_TEST_SECOND_ATTEMPT)
        {

            MTP3_Alarm_TTC(2508, __FILE__, __LINE__,
                             "ls=%x:link=%x:family=%s",
                             linkSet,linkCode, "TTC");

            /* set test stopped */
            ln->sltFlags &= ~(LINK_TEST_FIRST_ATTEMPT|
                              LINK_TEST_SECOND_ATTEMPT);

            if (ln->slt2 != TIMER_BAD_SERIAL)
            {
                TIMERS_CancelTimer(ln->slt2);
                ln->slt2 = TIMER_BAD_SERIAL;
            }

            MTP2_SendData_TTC(linkSet, linkCode, L3_L2_STOP, NULL, 0);

            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_SLT_FAILED);
            PEG_IncrPeg(TTC_MTP3_Pegs, PEG_MTP3_SLT_FAILED);

            LSAC_Main_TTC(MTP3_SLT_SLTC,
                           SLM_TRIGGER_L2_OUT_OF_SERVICE,
                           NULL, 0,
                           linkSet, linkCode);

            return MGMT_Main_TTC(MTP3_SLT_SLTC,
                                  MGMT_TRIGGER_LINK_TEST_FAILED,
                                  sif, len,
                                  linkSet, linkCode);
        }
        break;

    default:
        MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
        PEG_IncrPeg(TTC_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
        break;
    }

    return (ITS_SUCCESS);
}
