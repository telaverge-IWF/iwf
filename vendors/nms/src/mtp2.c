/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *  ID: $Id: mtp2.c,v 9.10 2008/05/29 11:59:52 kramesh Exp $
 *
 * LOG: $Log: mtp2.c,v $
 * LOG: Revision 9.10  2008/05/29 11:59:52  kramesh
 * LOG: Fix for Whizible Bug ID 929.
 * LOG:
 * LOG: Revision 9.9  2008/04/22 10:58:57  kramesh
 * LOG: Propagated BCGI issue 1533.MML pegs when links are terminated
 * LOG: on another node.
 * LOG:
 * LOG: Revision 9.8  2007/01/11 12:43:44  yranade
 * LOG: Merge changes from 6.5.3 and Lucent branches
 * LOG:
 * LOG: Revision 9.5.6.1  2006/09/26 21:58:11  omayor
 * LOG: Propagated fix for ticket #1217. BCGI: MTP2 hangs when congestion
 * LOG: indication is received from NMS.
 * LOG:
 * LOG: Revision 9.7.2.2  2006/08/23 21:21:55  omayor
 * LOG: Fix for trouble ticket 1217. When congestion indications are received from
 * LOG: NMS MTP2, we must reply with the same congestion level. The congestion
 * LOG: level is manitained in the context on a per link basis.
 * LOG:
 * LOG: Revision 9.7.2.1  2006/06/07 09:05:49  sbabu
 * LOG:  creating branch B-BCGI-LINUX-00
 * LOG:
 * LOG: Revision 9.7  2005/08/02 00:12:34  randresol
 * LOG: Fix memory leak caused the EMLIST.
 * LOG:
 * LOG: Revision 9.6  2005/07/27 23:53:30  randresol
 * LOG: Fix Link Deactivation/Reactivation problem
 * LOG:
 * LOG: Revision 9.5  2005/07/20 22:54:50  randresol
 * LOG: Tentative to fix memory corruption
 * LOG:
 * LOG: Revision 9.4  2005/07/18 22:40:25  randresol
 * LOG: Modification to use cpia*_ asynchronous library for NMS4000 TX board.
 * LOG:
 * LOG: Revision 9.3  2005/05/27 12:24:34  snagesh
 * LOG: Modifications for fixing NMS TX 4000 issue in Linux
 * LOG:
 * LOG: Revision 9.2  2005/05/06 10:08:39  mmanikandan
 * LOG: PR6.5.1 Validation Bug(1793) Fix.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:56:16  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:55:39  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.10.3.12.9  2005/02/21 05:01:18  snagesh
 * LOG: Corrected traces printing junk linkcode/linkport
 * LOG:
 * LOG: Revision 7.2.10.3.12.8  2005/02/09 10:04:57  snagesh
 * LOG: Fix for bug 1551 - m2_get_all_link_pegs printf issue
 * LOG:
 * LOG: Revision 7.2.10.3.12.7  2005/02/07 05:08:41  snagesh
 * LOG: Fix for bug 1499
 * LOG:
 * LOG: Revision 7.2.10.3.12.6  2005/02/03 08:51:45  craghavendra
 * LOG: Fix for GetGeneralCfg.
 * LOG:
 * LOG: Revision 7.2.10.3.12.5  2005/01/31 11:26:53  snagesh
 * LOG: MTP2 OSS APIs added
 * LOG:
 * LOG: Revision 7.2.10.3.12.4  2005/01/05 12:27:02  craghavendra
 * LOG: Syslog Enhancement.
 * LOG:
 * LOG: Revision 7.2.10.3.12.3  2005/01/05 10:30:11  snagesh
 * LOG: removed tabs
 * LOG:
 * LOG: Revision 7.2.10.3.12.2  2005/01/04 16:08:26  snagesh
 * LOG: commented get_gen_pegids MML
 * LOG:
 * LOG: Revision 7.2.10.3.12.1  2005/01/03 16:32:43  snagesh
 * LOG: MTP2 OAM changes
 * LOG:
 * LOG: Revision 7.2.10.3  2004/07/09 07:24:58  dsatish
 * LOG: Merging activity for timeslot changes
 * LOG:
 * LOG: Revision 7.2.10.2  2004/03/18 10:26:32  kannanp
 * LOG: Review comments added.
 * LOG:
 * LOG: Revision 7.2.10.1  2004/03/17 13:16:13  kannanp
 * LOG: For MTP2 Alarms.
 * LOG:
 * LOG: Revision 7.2  2002/12/24 20:45:56  randresol
 * LOG: Fix bugs in BSNT and L3_L2_RETRIEVE_MSGS cases
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:11:03  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/05/17 16:09:10  randresol
 * LOG: Bug fixes for resource generation code
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:15:03  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.17  2002/01/31 22:53:56  mmiers
 * LOG: Make it family independent.
 * LOG:
 * LOG: Revision 5.16  2002/01/09 21:24:15  mmiers
 * LOG: Correct the build settings, add XCO/XCA (SAAL changeover).
 * LOG:
 * LOG: Revision 5.15  2001/12/17 21:09:22  mmiers
 * LOG: Finish the vendor framework.  Works with NMS MTP2.
 * LOG:
 * LOG: Revision 5.14  2001/11/30 23:43:14  mmiers
 * LOG: Start testing config-d (route management).
 * LOG:
 * LOG: Revision 5.13  2001/11/16 23:37:40  mmiers
 * LOG: Today's round of testing.
 * LOG:
 * LOG: Revision 5.12  2001/11/15 23:52:27  mmiers
 * LOG: Today's testing.
 * LOG:
 * LOG: Revision 5.11  2001/11/12 22:54:14  vnitin
 * LOG: Fix L3_L2_STOP and L3_L2_DISCONNECT
 * LOG:
 * LOG: Revision 5.10  2001/10/19 21:37:29  mmiers
 * LOG: Missing BSNT
 * LOG:
 * LOG: Revision 5.9  2001/10/19 20:49:00  mmiers
 * LOG: Get things working with the engine.
 * LOG:
 * LOG: Revision 5.8  2001/10/18 19:01:40  mmiers
 * LOG: Fallout from the routing changes
 * LOG:
 * LOG: Revision 5.7  2001/10/15 21:54:22  mmiers
 * LOG: Get MTP2 API working ok.
 * LOG:
 * LOG: Revision 5.6  2001/10/12 23:14:52  mmiers
 * LOG: Fun with NMS.  The MTP2 API now works.
 * LOG:
 * LOG: Revision 5.5  2001/10/09 23:24:59  mmiers
 * LOG: Bug fixes.
 * LOG:
 * LOG: Revision 5.4  2001/10/06 23:30:33  mmiers
 * LOG: Finish the MTP2 API.
 * LOG:
 * LOG: Revision 5.3  2001/10/05 22:59:42  mmiers
 * LOG: NMS MTP2 API is taking shape.
 * LOG:
 * LOG: Revision 5.2  2001/09/05 23:05:45  mmiers
 * LOG: Working MTP2 into the scene.
 * LOG:
 * LOG: Revision 5.1  2001/09/05 22:00:31  mmiers
 * LOG: Add MTP2 API.
 * LOG:
 *
 ****************************************************************************/

#include <its.h>
#include <its_mlist.h>
#include <its_emlist.h>
#include <its_ss7_trans.h>
#include <its_intern.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(INCLUDE_MTP2)

#include <mtp2app.h>
#include <mtp2_alarm.h>
#include <mtp2_pegs.h>

#include <mtp2_cmn.h>
#include <tx_core.h>

#define MAX_NMS400_RECV_QUEUE_SIZE 15

static ITS_UINT pegs[PEG_NMS_MTP2_NUM_GLOBAL_PEGS];
static PEGS_DECL_SUBSYS(NMS_MTP2, pegs);
static ITS_UINT nmsInitializedFlag = ITS_FALSE;
PEG_Manager *NMS_MTP2_Pegs = &NMS_MTP2_PEGS;

static ITS_CHAR *mtp2GPegStr[] =
{
     "PEG_MTP2_GET_DATA_FAILED",
     "PEG_MTP2_SEND_DATA_FAILED",
     "PEG_MTP2_LOCAL_PROC_DOWN",
     "PEG_MTP2_LOCAL_PROC_UP",
     "PEG_MTP2_REMOTE_PROC_DOWN",
     "PEG_MTP2_REMOTE_PROC_UP",
     "PEG_MTP2_STAT_IND",
     "PEG_MTP2_SUERM_EXPIRY",
     "PEG_MTP2_INCORRECT_FIB_BSN",
     "PEG_MTP2_CONG_DETECTED",
     "PEG_MTP2_CONG_RECOVERED",
     "PEG_MTP2_MSU_TX",
     "PEG_MTP2_MSU_RX",
     "PEG_MTP2_T2_EXPIRED",
     "PEG_MTP2_T6_EXPIRED",
     "PEG_MTP2_T7_EXPIRED"
};

static TRACE_OutputInitializer fileCritTrace =
{
    MTP2_FILE_STRING,
    ITS_TRUE,
    MTP2_TRACE_CRITICAL_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileErrTrace =
{
    MTP2_FILE_STRING,
    ITS_TRUE,
    MTP2_TRACE_ERROR_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileWarnTrace =
{
    MTP2_FILE_STRING,
    ITS_TRUE,
    MTP2_TRACE_WARNING_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileDebugTrace =
{
    MTP2_FILE_STRING,
    ITS_TRUE,
    MTP2_TRACE_DEBUG_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer stdoutTrace =
{
    MTP2_STDOUT_STRING,
    ITS_TRUE,
    NULL,
    TRACE_TO_DISPLAY
};

static TRACE_OutputInitializer syslogTrace =
{
    MTP2_SYSLOG_STRING,
    ITS_TRUE,
    NULL,
#if defined(WIN32)
    TRACE_TO_NT_EVENT_LOG
#else
    TRACE_TO_SYSLOG
#endif
};


TRACE_LevelInitializer MTP2_TraceMap[] =
{
    {MTP2_CRITICAL_STRING, ITS_TRUE,  3, { &stdoutTrace, &fileCritTrace, &syslogTrace  } },
    {MTP2_ERROR_STRING,    ITS_TRUE,  3, { &stdoutTrace, &fileErrTrace, &syslogTrace   } },
    {MTP2_WARNING_STRING,  ITS_TRUE,  3, { &stdoutTrace, &fileWarnTrace, &syslogTrace  } },
    {MTP2_DEBUG_STRING,    ITS_FALSE, 3, { &stdoutTrace, &fileDebugTrace, &syslogTrace } }
};

TRACE_Data* MTP2_NMS_TraceData = NULL;

static MTP2GeneralCfg* MTP2_GetGeneralCfg();
static int MTP2_SetGeneralCfg(MTP2GeneralCfg* cfg);
static void DumpGeneralPegs(DBC_Server *dbc);
static void DumpGeneralPegIds(DBC_Server *dbc);
static void DumpLinkPegs(DBC_Server *dbc, ITS_OCTET linkSet,
                         ITS_OCTET linkCode, MTP2LinkStats *linkPegs);

static void NMS_RxNotif( TX_HANDLE txHandle, void *chkey );
static void NMS_TxNotif( TX_HANDLE handle, void *chkey, CPIPKT *msg,
                     void *tx_key, CPI_ERR_TYPE ccode );


static EMLIST_Manager *_NMS400_Token_Pool = NULL;

int
NMSHandleNotification(ITS_SS7_HANDLE handle)
{

    ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *)handle;
    int ret;
           /*  Call the cpia_intr function which will either handle
            *  the event internally or upcall the CpiaRxNotif or 
            *  CpiaTxNotif function.
            */

            ret = cpia_intr(context->txHandle);
            if (ret != CPI_SUCCESS)
            {
                printf("cpia_intr FAILS: error=%d\n", ret);
                return ITS_ENOMSG;
            }


    return ITS_SUCCESS;
   
}
 
static void NMS_RxNotif( TX_HANDLE txHandle, void *chkey )
{
    ITS_SS7_HANDLE handle = (ITS_SS7_HANDLE) chkey;

    if (NMSRetrieveMTP2Message(handle) != ITS_SUCCESS)
    {
        MTP2_CRITICAL(("NMS_RxNotif: Fail to retrieve MTP2 message\n"));

    }

    MTP2_DEBUG(("NMSRetrieveMTP2Message... success\n"));


}

void NMS_TxNotif( TX_HANDLE handle, void *chkey, CPIPKT *msg,
                     void *tx_key, CPI_ERR_TYPE ccode )
{
    ITS_EVENT token; 

    if (tx_key != NULL) 
    {
        token = *(ITS_EVENT *)tx_key;
        /*printf("TxNotif: Returning Token %d to pool\n", token.src); */
        EMQUEUE_PutEvent(_NMS400_Token_Pool, &token, sizeof(ITS_EVENT));
    }
#if 0
    if (msg != NULL)
    {
        free( msg );                /* all done with request message */
    }
#endif
}



/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Initialize the NMS interface.
 *
 *  Input Parameters:
 *      ITS_SS7_HANDLE - The board context.
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
 *  kramesh   28-05-2008  Bug ID:929        MML command m2_get_all_link_pegs, 
 *                                          returns the peg value two times 
 ****************************************************************************/
#if NMS_VERSION >= 4000
int
NMSInitializeMTP2(ITS_SS7_HANDLE handle)
{
    ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *)handle;
    MTP2TXPKT       txBuf;
    CPIPKT *pTxBuf;
    char            sbuf[CPSTRSIZE], *ptr = sbuf; /* dummy for old cpi_init */
    short port, ret = 0;
    ITS_OCTET idx;
    int i;
    ITS_EVENT token;

    memset(&txBuf, 0, sizeof(MTP2TXPKT));

    if ((_NMS400_Token_Pool  = EMQUEUE_Create()) == NULL)
    {
        MTP2_CRITICAL(("Fail to Create Token pool for NMS4000 board\n"));
        return ITS_ENOMEM;
    }
    /* Create a pool of tokens */
    for (i = 0; i < MAX_NMS400_RECV_QUEUE_SIZE; i++)
    { 
        //token = (ITS_EVENT*) malloc (sizeof(ITS_EVENT));
        ITS_EVENT_INIT(&token, i, 0);
        EMQUEUE_PutEvent(_NMS400_Token_Pool, &token, sizeof(ITS_EVENT));
    }


    ret = cpi_init(ret, &ptr);

    if (ret != CPI_SUCCESS)
    {
        MTP2_CRITICAL(("NMS Initialize failed.cpi_init failed\n"));
        return ITS_EINVALIDARGS;
    }

    port = PORT(context->boardNum, context->mtp2SrcEnt);

    context->txHandle = cpia_open((void *) context, context->boardNum,
                             context->mtp2SrcEnt/*CPIM_PORT*/, NMS_RxNotif, NMS_TxNotif);

    if (context->txHandle == CPI_INVALID_HANDLE)
    {
        MTP2_CRITICAL(("NMS Initialize failed. cpi_open failed: %ld\n",
                            cpi_get_last_error()));
        MTP2_Alarm_NMS(12001, __FILE__, __LINE__,NULL);

        return (ITS_EINVALIDARGS);
    }

    context->mtp2Sync = cpi_wait_obj(context->txHandle);
    if (context->mtp2Sync == CPI_INVALID_WAIT_HANDLE)
    {
        MTP2_CRITICAL(("NMS Initialize failed. cpi_wait_obj failed: %ld\n",
                            cpi_get_last_error()));
        MTP2_Alarm_NMS(12001, __FILE__, __LINE__,NULL);

        return (ITS_EINVALIDARGS);
    }

    /* Bind this application as a user of the MTP2 layer */
    txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
    txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
    txBuf.hdr.hdr.length        = HDRSIZE + sizeof(BindReq);
    MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
    MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(BindReq));
    txBuf.msgType               = MTP2_BIND_REQ;
    txBuf.data.bindReq.srcEnt   = context->mtp2SrcEnt;  /* app entity */
    txBuf.data.bindReq.srcInst  = context->srcInst;     /* app instance */

    for (idx = 0; idx < context->numLinkCodes; idx++)
    {
        ITS_USHORT link;

        link = context->dataLink[idx].linkPort;

        /* board link number */
        TXPKT_SET_PROVIDER_ID(txBuf, link);
        /* app's idea of global link number */
        MTP2_BIND_REQ_SET_USER_ID(txBuf.data.bindReq, link);

        MTP2_DEBUG(("MTP2:::: Set userId to %04x\n", link));
        printf("MTP2:::: Set userId to %04x\n", link);

        /*pTxBuf = (CPIPKT *) malloc (sizeof(CPIPKT));
        memcpy(pTxBuf, &txBuf, sizeof(CPIPKT));*/
   
        printf("cpia_send: ptxBuf=%x\n", pTxBuf);

        /*ret = cpia_send(context->txHandle, (CPIPKT *)pTxBuf, NULL);*/
        ret = cpia_send(context->txHandle, (CPIPKT *)&txBuf, NULL);
        if (ret != CPI_SUCCESS)
        {
//#if !defined(LINUX)
            MTP2_CRITICAL(("NMS Initialize failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));
            MTP2_Alarm_NMS(12001, __FILE__, __LINE__,NULL);

            return (ITS_ENOTFOUND);
//#endif
        }
/*
        ret = waitForBindConfirm(context->txHandle);
        if (ret != CPI_SUCCESS)
        {
            printf("First Bind Confirm not received: %d\n", ret);
            exit(1);
        }
*/
    }

    MTP2_DEBUG(("NMS Initialized\n"));
    MTP2_Alarm_NMS(12000, __FILE__, __LINE__,NULL);
    
    if(nmsInitializedFlag == ITS_FALSE)
	{	 
        DBC_AddDoCommand(NMS_MTP2_Console);
    }

    nmsInitializedFlag = ITS_TRUE;	


    return (ITS_SUCCESS);
}
#else
int
NMSInitializeMTP2(ITS_SS7_HANDLE handle)
{
    ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *)handle;
    MTP2TXPKT       txBuf;
    char            sbuf[CPSTRSIZE], *ptr = sbuf; /* dummy for old cpi_init */
    short port, ret = 0;
    ITS_OCTET idx;

    memset(&txBuf, 0, sizeof(txBuf));

    ret = cpi_init(ret, &ptr);

    if (ret != CPI_SUCCESS)
    {
        MTP2_CRITICAL(("NMS Initialize failed.cpi_init failed\n"));
        return ITS_EINVALIDARGS;
    }

    port = PORT(context->boardNum, context->mtp2SrcEnt);
    context->txHandle = cpi_open(port, CPIM_PORT, NULL);
    if (context->txHandle == CPI_INVALID_HANDLE)
    {
        MTP2_CRITICAL(("NMS Initialize failed. cpi_open failed: %ld\n",
                            cpi_get_last_error()));
        MTP2_Alarm_NMS(12001, __FILE__, __LINE__,NULL);

        return (ITS_EINVALIDARGS);
    }

    context->mtp2Sync = cpi_wait_obj(context->txHandle);
    if (context->mtp2Sync == CPI_INVALID_WAIT_HANDLE)
    {
        MTP2_CRITICAL(("NMS Initialize failed. cpi_wait_obj failed: %ld\n",
                            cpi_get_last_error()));
        MTP2_Alarm_NMS(12001, __FILE__, __LINE__,NULL);

        return (ITS_EINVALIDARGS);
    }

    /* Bind this application as a user of the MTP2 layer */
    txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
    txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
    txBuf.hdr.hdr.length        = HDRSIZE + sizeof(BindReq);
    MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
    MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(BindReq));
    txBuf.msgType               = MTP2_BIND_REQ;
    txBuf.data.bindReq.srcEnt   = context->mtp2SrcEnt;  /* app entity */
    txBuf.data.bindReq.srcInst  = context->srcInst;     /* app instance */

    for (idx = 0; idx < context->numLinkCodes; idx++)
    {
        ITS_USHORT link;

        link = context->dataLink[idx].linkPort;

        /* board link number */
        TXPKT_SET_PROVIDER_ID(txBuf, link);
        /* app's idea of global link number */
        MTP2_BIND_REQ_SET_USER_ID(txBuf.data.bindReq, link);

        MTP2_DEBUG(("MTP2:::: Set userId to %04x\n", link));

        ret = cpi_send(context->txHandle, (CPIPKT *)&txBuf);
        if (ret != CPI_SUCCESS)
        {
            MTP2_CRITICAL(("NMS Initialize failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));
            MTP2_Alarm_NMS(12001, __FILE__, __LINE__,NULL);

            return (ITS_ENOTFOUND);
        }
    }

    MTP2_DEBUG(("NMS Initialized\n"));
    MTP2_Alarm_NMS(12000, __FILE__, __LINE__,NULL);

    DBC_AddDoCommand(NMS_MTP2_Console);

    return (ITS_SUCCESS);
}
#endif

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Terminate the NMS interface.
 *
 *  Input Parameters:
 *      ITS_SS7_HANDLE - The board context.
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
#if NMS_VERSION >= 4000
int
NMSTermMTP2(ITS_SS7_HANDLE handle)
{
    ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *)handle;
    MTP2TXPKT txBuf;
    ITS_OCTET idx;
    int ret;

    memset(&txBuf, 0, sizeof(txBuf));

    /* Unbind this application as a user of the MTP2 layer */
    txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
    txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
    txBuf.hdr.hdr.length        = HDRSIZE + sizeof(BindReq);
    MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
    MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(BindReq));
    txBuf.msgType               = MTP2_UNBIND_REQ;
    txBuf.data.bindReq.srcEnt   = context->mtp2SrcEnt;  /* app entity */
    txBuf.data.bindReq.srcInst  = context->srcInst;     /* app instance */

    for (idx = 0; idx < context->numLinkCodes; idx++)
    {
        ITS_USHORT link;

        link = context->dataLink[idx].linkPort;

        /* board link number */
        TXPKT_SET_PROVIDER_ID(txBuf, link);
        /* app's idea of global link number */
        MTP2_BIND_REQ_SET_USER_ID(txBuf.data.bindReq, link);

        MTP2_DEBUG(("MTP2:::: Set userId to %04x\n", link));

        /*pTxBuf = (CPIPKT *) malloc (sizeof(CPIPKT));
        memcpy(pTxBuf, &txBuf, sizeof(CPIPKT));*/

        /*ret = cpia_send(context->txHandle, (CPIPKT *)pTxBuf, NULL);*/
        ret = cpia_send(context->txHandle, (CPIPKT *)&txBuf, NULL);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("NMS Term failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));

            return (ITS_ENOTFOUND);
        }
    }

    cpi_close(context->txHandle);

    TRACE_Destructor(MTP2_NMS_TraceData);

    return (ITS_SUCCESS);
}
#else
int
NMSTermMTP2(ITS_SS7_HANDLE handle)
{
    ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *)handle;
    MTP2TXPKT txBuf;
    ITS_OCTET idx;
    int ret;

    memset(&txBuf, 0, sizeof(txBuf));

    /* Unbind this application as a user of the MTP2 layer */
    txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
    txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
    txBuf.hdr.hdr.length        = HDRSIZE + sizeof(BindReq);
    MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
    MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(BindReq));
    txBuf.msgType               = MTP2_UNBIND_REQ;
    txBuf.data.bindReq.srcEnt   = context->mtp2SrcEnt;  /* app entity */
    txBuf.data.bindReq.srcInst  = context->srcInst;     /* app instance */

    for (idx = 0; idx < context->numLinkCodes; idx++)
    {
        ITS_USHORT link;

        link = context->dataLink[idx].linkPort;

        /* board link number */
        TXPKT_SET_PROVIDER_ID(txBuf, link);
        /* app's idea of global link number */
        MTP2_BIND_REQ_SET_USER_ID(txBuf.data.bindReq, link);

        MTP2_DEBUG(("MTP2:::: Set userId to %04x\n", link));

        ret = cpi_send(context->txHandle, (CPIPKT *)&txBuf);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("NMS Term failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));

            return (ITS_ENOTFOUND);
        }
    }

    cpi_close(context->txHandle);

    TRACE_Destructor(MTP2_NMS_TraceData);

    return (ITS_SUCCESS);
}
#endif

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
static ITS_OCTET
GetLinkCode(ITS_SS7_CONTEXT *context, ITS_OCTET port)
{
    int i;

    for (i = 0; i < context->numLinkCodes; i++)
    {
        if (context->dataLink[i].linkPort == port)
        {
            return context->dataLink[i].linkCode;
        }

    }

    MTP2_ERROR(("Port %d not associated with a linkcode\n", port));

    return 0xFF /*ITS_DEFAULT_LINK_CODE*/;

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
static ITS_OCTET
GetLinkPort(ITS_SS7_CONTEXT *context, ITS_OCTET linkCode)
{
    int i;

    for (i = 0; i < context->numLinkCodes; i++)
    {
        if (context->dataLink[i].linkCode == linkCode)
        {
            return context->dataLink[i].linkPort;
        }

    }

    MTP2_ERROR(("Linkcode %d not associated with a port\n", linkCode));

    return 0xFF /*ITS_DEFAULT_LINK_CODE*/;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Retrieve the congestion level value for a give link. 
 *
 *  Input Parameters:
 *      ITS_SS7_CONTEXT* : pointer to handle that keeps links information
 *                         for this MTP2 transport. 
 *      ITS_OCTET        : concerned linkCode.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_OCTET : NMS congestion level for this link. 
 ****************************************************************************/
static ITS_OCTET
GetFlcLevel(ITS_SS7_CONTEXT *context, ITS_OCTET linkCode)
{
    int i;

    for (i = 0; i < context->numLinkCodes; i++)
    {
        if (context->dataLink[i].linkCode == linkCode)
        {
            return context->dataLink[i].flcLevel;
        }
    }

    MTP2_ERROR(("GetFlcLevel: Cong Level not found for linkCode %d", linkCode));

    return 0x00;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Sets the congestion level for a particular link. 
 *
 *  Input Parameters:
 *      ITS_SS7_CONTEXT* : pointer to handle that keeps links information
 *                         for this MTP2 transport.
 *      ITS_OCTET        : concerned linkCode.
 *      ITS_OCTET        : concerned linkSet
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
SetFlcLevel(ITS_SS7_CONTEXT *context, ITS_OCTET linkCode, ITS_OCTET flcLevel)
{
    int i;

    for (i = 0; i < context->numLinkCodes; i++)
    {
        if (context->dataLink[i].linkCode == linkCode)
        {
            context->dataLink[i].flcLevel =  flcLevel;
   
            MTP2_WARNING(("SetFlcLevel: Cong Level linkCode %d, set to %d",
                           linkCode, flcLevel));
            return;
        }
    }

    MTP2_ERROR(("SetFlcLevel: Failed to set linkCode %d, to cong level %d",
                linkCode, flcLevel));

    return;
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
NMSRetrieveMTP2Message(ITS_SS7_HANDLE handl)
{
    ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *)handl;
    short   status;
    short   len = sizeof(MTP2RXPKT);
    unsigned short start, end;
    unsigned short start_hdr;
    U8      msgType;
    S16     userId;
    S16     linkCode;
    U8      *dataPtr;
    ITS_USHORT dlen, action;
    MTP2RXPKT  rxBuf;                  /* packet buffer */
    ITS_EVENT ev;
    ITS_UINT bsn,linkSet;

    MTP2_DEBUG(("NMSRetrieveMTP2Message....\n"));

    memset(&rxBuf, 0, sizeof(MTP2RXPKT));

#if NMS_VERSION >= 4000
    status = cpia_get_data(context->txHandle, (void *)&rxBuf, &len);
#else
    status = cpi_get_data(context->txHandle, (void *)&rxBuf, &len);
#endif
    if (len == 0)
    {
        MTP2_WARNING(("cpia_get_data return with len = 0, status %d\n", status));
        return ITS_SUCCESS;
    }

    linkSet = context->linkSet;

    start_hdr = MTP2HDR_GET_START(rxBuf.hdr);
    linkCode = (rxBuf.data[start_hdr+1] << 8) | rxBuf.data[start_hdr+2];

    if (status != CPI_SUCCESS)
    {
        MTP2_ERROR(("Retrieve Message failed, status %ld\n", cpi_get_last_error()));
        MTP2_Alarm_NMS(12002, __FILE__, __LINE__,
                       "LinkSet:LinkCode %d:%d",linkSet,linkCode);  
        PEG_IncrPeg(NMS_MTP2_Pegs, PEG_MTP2_GET_DATA_FAILED);

        return (ITS_ENOMSG);
    }

    start = MTP2HDR_GET_START(rxBuf.hdr);
    end = MTP2HDR_GET_END(rxBuf.hdr);
    msgType = rxBuf.data[start];
    userId = (rxBuf.data[start+1] << 8) | rxBuf.data[start+2];
    dataPtr = (U8 *)&rxBuf.data[start+3];
    dlen = end - start - 3 * sizeof(ITS_OCTET);

    MTP2_DEBUG(("MTP2::: userId %04x start %d end %d len %d fd %d\n",
                 userId, start, end, dlen, context->mtp2Sync));

    /* got an incoming message, decode it */
    switch (msgType)
    {
    case MTP2_BIND_CFM:
        MTP2_DEBUG(("MTP2::: Link %d:Bind Confirmation received\n", userId));
        return (ITS_ENOMSG);

    case MTP2_UNBIND_CFM:
        MTP2_DEBUG(("MTP2::: Link %d:Unbind Confirmation received\n", userId));
        return (ITS_ENOMSG);

    case MTP2_DISC_CFM:
        MTP2_DEBUG(("MTP2::: Link %d:Disconnect Confirmation received\n", userId));
        return (ITS_ENOMSG);

    case MTP2_FLOW_CFM:
        MTP2_DEBUG(("MTP2::: Link %d:Flow Control Confirmation received\n", userId));
        return (ITS_ENOMSG);

    case MTP2_CONN_CFM:
        MTP2_DEBUG(("MTP2::: Link %d:Connect Confirmation received\n", userId));

        ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                       3 * sizeof(ITS_OCTET));

        ev.data[0] = L2_L3_IN_SERVICE;
        ev.data[1] = context->linkSet;
        ev.data[2] = GetLinkCode(context, userId & 0xFFU);

        return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

    case MTP2_DATA_CFM:
        switch (((DatCfm*)dataPtr)->status)
        {
        case DATCFMSTA_MORE:
            MTP2_DEBUG(("MTP2::: Link %d:Data Confirmation received with a packet\n",
                          userId));

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           dlen - (sizeof(DatCfm) - MAXMTP2DATA - 1) +
                            3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_RETRIEVED_MSG;
            ev.data[1] = context->linkSet;
            ev.data[2] = GetLinkCode(context, userId & 0xFFU);

            memcpy(&ev.data[3], dataPtr + (sizeof(DatCfm) - MAXMTP2DATA - 1),
                   dlen - (sizeof(DatCfm) - MAXMTP2DATA - 1));

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case DATCFMSTA_LAST:
            MTP2_DEBUG(("MTP2::: Link %d:Data Confirmation received with the last packet\n",
                          userId));

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           dlen - (sizeof(DatCfm) - MAXMTP2DATA - 1) +
                            3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_RETRIEVED_MSG;
            ev.data[1] = context->linkSet;
            ev.data[2] = GetLinkCode(context, userId & 0xFFU);

            memcpy(&ev.data[3], dataPtr + (sizeof(DatCfm) - MAXMTP2DATA - 1),
                   dlen - (sizeof(DatCfm) - MAXMTP2DATA - 1));

            MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_RETRIEVAL_COMPLETE;
            ev.data[1] = context->linkSet;
            ev.data[2] = GetLinkCode(context, userId & 0xFFU);

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case DATCFMSTA_NUM_ACKED:
            MTP2_DEBUG(("MTP2::: Link %d:Data Confirmation received acking %d messages\n",
                          userId, ((DatCfm *)dataPtr)->credit));
            return (ITS_ENOMSG);

        default:
            MTP2_DEBUG(("MTP2::: Link %d:Data Confirmation received with illegal status %d\n",
                          userId, ((DatCfm *)dataPtr)->status));
            return (ITS_ENOMSG);
        }

        /* NOTREACHED */
        return (ITS_ENOMSG);

    case MTP2_DISC_IND:
        ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                       3 * sizeof(ITS_OCTET));

        ev.data[0] = L2_L3_OUT_OF_SERVICE;
        ev.data[1] = context->linkSet;
        ev.data[2] = GetLinkCode(context, userId & 0xFFU);

        switch (MTP2_DIS_IND_GET_REASON(*((DisInd *)dataPtr)))
        {
        case SUERM_OVERFLOW:            
            MTP2_WARNING(("MTP2:::: Link %d:Disconnect Indication received - SUERM overflow\n",
                          userId));
            MTP2_Alarm_NMS(12016, __FILE__, __LINE__,
                         "LinkSet:LinkCode %d:%d",linkSet,linkCode);
            PEG_IncrPeg(NMS_MTP2_Pegs, PEG_MTP2_SUERM_EXPIRY);
            break;

        case T2_EXPIRED:            
            MTP2_WARNING(("MTP2:::: Link %d:Disconnect Indication received - T2 expired\n",
                          userId));
            MTP2_Alarm_NMS(12003, __FILE__, __LINE__,
                         "LinkSet:LinkCode %d:%d",linkSet,linkCode);
            PEG_IncrPeg(NMS_MTP2_Pegs, PEG_MTP2_T2_EXPIRED);
            break;

        case T7_EXPIRED:            
            MTP2_WARNING(("MTP2:::: Link %d:Disconnect Indication received - T7 expired\n",
                          userId));
            MTP2_Alarm_NMS(12004, __FILE__, __LINE__,
                         "LinkSet:LinkCode %d:%d",linkSet,linkCode);
            PEG_IncrPeg(NMS_MTP2_Pegs, PEG_MTP2_T7_EXPIRED);
            break;

        case INVALID_BSN:           
        case INVALID_FIB:           
            MTP2_WARNING(("MTP2:::: Link %d:Disconnect Indication received - Invalid BSN/FIB\n",
                          userId));
            MTP2_Alarm_NMS(12014, __FILE__, __LINE__,
                         "LinkSet:LinkCode %d:%d",linkSet,linkCode);
            PEG_IncrPeg(NMS_MTP2_Pegs, PEG_MTP2_INCORRECT_FIB_BSN);
            break;

        case STATUS_IND_FROM_NETWORK:          
            MTP2_WARNING(("MTP2:::: Link %d:Disconnect Indication received - Status indication\n",
                          userId));
            MTP2_Alarm_NMS(12005, __FILE__, __LINE__,
                         "LinkSet:LinkCode %d:%d",linkSet,linkCode);
            PEG_IncrPeg(NMS_MTP2_Pegs, PEG_MTP2_STAT_IND);
            break;

        case L2_CONG_EXCESS_PERIOD:          
            MTP2_WARNING(("MTP2:::: Link %d:Disconnect Indication received - "
                          "Excessive congestion period\n", userId));
            MTP2_Alarm_NMS(12022, __FILE__, __LINE__,
                         "LinkSet:LinkCode %d:%d",linkSet,linkCode);
            PEG_IncrPeg(NMS_MTP2_Pegs, PEG_MTP2_T6_EXPIRED);
            break;
        }

        return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

    case MTP2_FLOW_IND:
        action = MTP2_FLOW_IND_GET_ACTION(*((FlowInd *)dataPtr));

        SetFlcLevel(context, linkCode, ((FlowInd *)dataPtr)->flcLevel);

        if (action == FLOWIND_STARTED)
        {
            MTP2_WARNING(("MTP2:::: Link %d:Flow Indication received -"
                          "congestion detected\n", userId));
            MTP2_Alarm_NMS(12017, __FILE__, __LINE__,
                         "LinkSet:LinkCode %d:%d",linkSet,linkCode);
            PEG_IncrPeg(NMS_MTP2_Pegs, PEG_MTP2_CONG_DETECTED);

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_CONGESTION_ONSET;
        }
        else if (action == FLOWIND_STOPPED)
        {
            MTP2_DEBUG(("MTP2:::: Link %d:Flow Indication received - "
                        "congestion recovered\n", userId));
            MTP2_Alarm_NMS(12018, __FILE__, __LINE__,
                         "LinkSet:LinkCode %d:%d",linkSet,linkCode);
            PEG_IncrPeg(NMS_MTP2_Pegs, PEG_MTP2_CONG_RECOVERED);

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_CONGESTION_ABATES;
        }
        else
        {
            return (ITS_ENOMSG);
        }

        ev.data[1] = context->linkSet;
        ev.data[2] = GetLinkCode(context, userId & 0xFFU);

        return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

    case MTP2_STAT_CFM:
        switch (MTP2_STA_CFM_GET_ACTION(*((StaCfm *)dataPtr)))
        {
        case STACFM_BSN:
            bsn = MTP2_STA_CFM_GET_STATUS(*((StaCfm *)dataPtr));

            MTP2_DEBUG(("MTP2:::: Link %d:Status Confirmation received with a BSN = %d\n",
                        userId, bsn));

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET) + sizeof(ITS_UINT));

            ev.data[0] = L2_L3_BSNT;
            ev.data[1] = context->linkSet;
            ev.data[2] = GetLinkCode(context, userId & 0xFFU);
            memcpy(&ev.data[3], &bsn, sizeof(ITS_UINT));

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case STACFM_NO_UNACKED:
            MTP2_DEBUG(("MTP2:::: Link %d:Status Confirmation received with no unacknowledged messages\n",
                        userId));

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_RETRIEVAL_COMPLETE;
            ev.data[1] = context->linkSet;
            ev.data[2] = GetLinkCode(context, userId & 0xFFU);

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

        case STACFM_NOACTION:
            switch (MTP2_STA_CFM_GET_STATUS(*((StaCfm *)dataPtr)))
            {
            case STACFM_STS_LCL_DOWN:
                MTP2_WARNING(("MTP2:::: Link %d:Status Confirmation received - Local Processor Down\n",
                            userId));
                MTP2_Alarm_NMS(12006, __FILE__, __LINE__,
                       "LinkSet:LinkCode %d:%d",linkSet,linkCode);
                PEG_IncrPeg(NMS_MTP2_Pegs, PEG_MTP2_LOCAL_PROC_DOWN);
                break;

            case STACFM_STS_LCL_UP:
                MTP2_DEBUG(("MTP2:::: Link %d:Status Confirmation received - Local Processor Up\n",
                            userId));
                MTP2_Alarm_NMS(12008, __FILE__, __LINE__,
                       "LinkSet:LinkCode %d:%d",linkSet,linkCode);
                PEG_IncrPeg(NMS_MTP2_Pegs, PEG_MTP2_LOCAL_PROC_UP);
                break;

            default:
                MTP2_DEBUG(("MTP2:::: Link %d:Status Confirmation received\n", userId));
                break;
            }

            return (ITS_ENOMSG);

        default:
            MTP2_DEBUG(("MTP2:::: Link %d:Status Confirmation received\n", userId));
            return (ITS_ENOMSG);
        }

        /* NOTREACHED */
        return (ITS_ENOMSG);


    case MTP2_DATA_IND:
        MTP2_DEBUG(("MTP2:::: Link %d:Data received\n", userId));
        PEG_IncrPeg(NMS_MTP2_Pegs, PEG_MTP2_MSU_RX);

        ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                       dlen + 3 * sizeof(ITS_OCTET));

        ev.data[0] = L2_L3_DATA;
        ev.data[1] = context->linkSet;
        ev.data[2] = GetLinkCode(context, userId & 0xFFU);

        memcpy(&ev.data[3], dataPtr, dlen);

        return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

    case MTP2_STAT_IND:
        if (((StaInd *)dataPtr)->status == STAIND_REM_DOWN)
        {
            MTP2_WARNING(("MTP2:::: Link %d:Status Indication received - Remote Processor Down\n",
                            userId));
            MTP2_Alarm_NMS(12007, __FILE__, __LINE__,
                         "LinkSet:LinkCode %d:%d",linkSet,linkCode);
            PEG_IncrPeg(NMS_MTP2_Pegs, PEG_MTP2_REMOTE_PROC_DOWN);

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_REMOTE_PROCESSOR_OUT;
            ev.data[1] = context->linkSet;
            ev.data[2] = GetLinkCode(context, userId & 0xFFU);

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));
        }
        else if (((StaInd *)dataPtr)->status == STAIND_REM_UP)
        {
            MTP2_DEBUG(("MTP2:::: Link %d:Status Indication received - Remote Processor Up\n",
                            userId));
            MTP2_Alarm_NMS(12009, __FILE__, __LINE__,
                         "LinkSet:LinkCode %d:%d",linkSet,linkCode);
            PEG_IncrPeg(NMS_MTP2_Pegs, PEG_MTP2_REMOTE_PROC_UP);

            ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                           3 * sizeof(ITS_OCTET));

            ev.data[0] = L2_L3_REMOTE_PROCESSOR_REC;
            ev.data[1] = context->linkSet;
            ev.data[2] = GetLinkCode(context, userId & 0xFFU);

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));
        }
        else
        {
            MTP2_DEBUG(("MTP2:::: Link %d:Status Indication received\n", userId));
        }

        return (ITS_ENOMSG);

    default:
        MTP2_ERROR(("MTP2:::: Link %d:Unknown MTP2 message received, message type: %d\n",
                    userId, msgType));
        break;
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
#if NMS_VERSION >= 4000
int
NMSSendMTP2Event(ITS_SS7_HANDLE handle, ITS_OCTET *data, ITS_USHORT dlen)
{
    ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *)handle;
    MTP2TXPKT    txBuf; 
    ITS_EVENT ev;
    ITS_OCTET linkSet;
    ITS_OCTET linkCode;
    ITS_OCTET linkPort;
    ITS_UINT fsnc=0;
    short ret;
    void *queueData;
    ITS_EVENT token;
    ITS_UINT len;

    ev.data = data;
    ev.len = dlen;

    memset(&txBuf, 0, sizeof(txBuf));

    linkSet = L2_LINK_SET(&ev);
    linkCode = L2_LINK_CODE(&ev);
    linkPort = GetLinkPort(context, linkCode);

    switch (L2_MSG_TYPE(&ev))
    {
    case L3_L2_START:
        MTP2_DEBUG(("MTP2:::: START\n"));

#if 0
        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(DisReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(DisReq));
        txBuf.msgType               = MTP2_DISC_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
        MTP2_DIS_REQ_SET_REASON(txBuf.data.disReq, DISCREQ_LVL_2_ONLY);/* disconnect L1 */
        
        pTxBuf = (MTP2TXPKT *) malloc (sizeof(MTP2TXPKT));
        memcpy(pTxBuf, &txBuf, sizeof(MTP2TXPKT));

        /*ret = cpia_send(context->txHandle, (CPIPKT *)pTxBuf, NULL);*/
        ret = cpia_send(context->txHandle, (CPIPKT *)&txBuf, token);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send DISCONNECT failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));
            return (ITS_EPROTERR);
        }
#endif

        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(ConReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(ConReq));
        txBuf.msgType               = MTP2_CONN_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);                    /* board link number */
        if (context->emergency & (1 << linkPort))
        {
            txBuf.data.conReq.status   = CONREQSTA_LVL_1_2_EMRG;  /* emergency align */
        }
        else
        {
            txBuf.data.conReq.status   = CONREQSTA_LVL_1_2_NORM;  /* normal align */
        }
        
        /*pTxBuf = (CPIPKT *) malloc (sizeof(CPIPKT));
        memcpy(pTxBuf, &txBuf, sizeof(MTP2TXPKT));*/

        /*ret = cpia_send(context->txHandle, (CPIPKT *)pTxBuf, NULL);*/
        ret = cpia_send(context->txHandle, (CPIPKT *)&txBuf, NULL);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send START failed. cpia_send failed: %ld\n",
                            cpi_get_last_error()));
            MTP2_Alarm_NMS(12010, __FILE__, __LINE__,
                         "LinkSet:LinkCode %d:%d",linkSet,linkCode);

            return (ITS_EPROTERR);
        }

        MTP2_Alarm_NMS(12012, __FILE__, __LINE__,
                         "LinkSet:LinkCode %d:%d",linkSet,linkCode);
        
        return (ITS_SUCCESS);
        
    case L3_L2_STOP:
        MTP2_DEBUG(("MTP2:::: STOP\n"));

        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(DisReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(DisReq));
        txBuf.msgType               = MTP2_DISC_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
#if 0
        /* This doesn't seem to work well, use Disconnect Mgmt Req instead */
        MTP2_DIS_REQ_SET_REASON(txBuf.data.disReq, DISCREQ_LVL_2_ONLY);   /* disconnect L2 */
#endif
        MTP2_DIS_REQ_SET_REASON(txBuf.data.disReq, DISCREQ_MGMT_REQ);   /* disconnect L2 */

        /*pTxBuf = (CPIPKT *) malloc (sizeof(CPIPKT));
        memcpy(pTxBuf, &txBuf, sizeof(MTP2TXPKT));*/

        /*ret = cpia_send(context->txHandle, (CPIPKT *)pTxBuf, NULL);*/
        ret = cpia_send(context->txHandle, (CPIPKT *)&txBuf, NULL);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send STOP failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));
            MTP2_Alarm_NMS(12011, __FILE__, __LINE__,
                       "LinkSet:LinkCode %d:%d",linkSet,linkCode);

            return (ITS_EPROTERR);
        }

        MTP2_Alarm_NMS(12013, __FILE__, __LINE__,
                       "LinkSet:LinkCode %d:%d",linkSet,linkCode);
        
        return (ITS_SUCCESS);
        
    case L3_L2_RESUME:
        MTP2_DEBUG(("MTP2:::: RESUME\n"));

        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(ConReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(ConReq));
        txBuf.msgType               = MTP2_CONN_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
        if (context->emergency & (1 << linkPort))
        {
            txBuf.data.conReq.status   = CONREQSTA_LVL_2_EMRG;   /* emergency align */
        }
        else
        {
            txBuf.data.conReq.status   = CONREQSTA_LVL_2_NORM;   /* normal align */
        }
        
        /*pTxBuf = (CPIPKT *) malloc (sizeof(CPIPKT));
        memcpy(pTxBuf, &txBuf, sizeof(MTP2TXPKT));*/

        /*ret = cpia_send(context->txHandle, (CPIPKT *)pTxBuf, NULL);*/
        ret = cpia_send(context->txHandle, (CPIPKT *)&txBuf, NULL);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send RESUME failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));
            return (ITS_EPROTERR);
        }
        
        return (ITS_SUCCESS);
        
    case L3_L2_CLEAR_BUFFERS:
    case L3_L2_CLEAR_RTB:
        MTP2_DEBUG(("MTP2:::: CLEAR BUFFERS\n"));

        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(StaReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(StaReq));
        txBuf.msgType               = MTP2_STAT_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
        MTP2_STA_REQ_SET_ACTION(txBuf.data.staReq, STAREQ_DROP_UNACKED); /* drop all queued transmit */
        
        /*pTxBuf = (CPIPKT *) malloc (sizeof(CPIPKT));
        memcpy(pTxBuf, &txBuf, sizeof(MTP2TXPKT));*/

        /*ret = cpia_send(context->txHandle, (CPIPKT *)pTxBuf, NULL);*/
        ret = cpia_send(context->txHandle, (CPIPKT *)&txBuf, NULL);
        if (ret != CPI_SUCCESS)
        {
            MTP2_Alarm_NMS(12019, __FILE__, __LINE__,
                           "LinkSet:LinkCode %d:%d",linkSet,linkCode);
            return (ITS_EPROTERR);
        }
        
        return (ITS_SUCCESS);
        
    case L3_L2_EMERGENCY:
        MTP2_DEBUG(("MTP2:::: EMERGENCY\n"));

        /* set emergency bit for this link */
        context->emergency |= 1 << linkPort;
        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(StaReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(StaReq));
        txBuf.msgType               = MTP2_STAT_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
        MTP2_STA_REQ_SET_ACTION(txBuf.data.staReq, STAREQ_CHANGE_STATUS);    /* status alteration */
        MTP2_STA_REQ_SET_STATUS(txBuf.data.staReq, STAREQ_STS_START_EMERG);  /* emergency */
        
        /*pTxBuf = (CPIPKT *) malloc (sizeof(CPIPKT));
        memcpy(pTxBuf, &txBuf, sizeof(MTP2TXPKT));*/

        /*ret = cpia_send(context->txHandle, (CPIPKT *)pTxBuf, NULL);*/
        ret = cpia_send(context->txHandle, (CPIPKT *)&txBuf, NULL);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send EMERGENCY failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));
            MTP2_Alarm_NMS(12020, __FILE__, __LINE__,
                       "LinkSet:LinkCode %d:%d",linkSet,linkCode);

            return (ITS_EPROTERR);
        }
        
        return (ITS_SUCCESS);
        
    case L3_L2_EMERGENCY_CEASE:
        MTP2_DEBUG(("MTP2:::: EMERGENCY CEASE\n"));

        /* clear emergency bit for this link */
        context->emergency &= ~(1 << linkPort);
        
        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(StaReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(StaReq));
        txBuf.msgType               = MTP2_STAT_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
        MTP2_STA_REQ_SET_ACTION(txBuf.data.staReq, STAREQ_CHANGE_STATUS);    /* status alteration */
        MTP2_STA_REQ_SET_STATUS(txBuf.data.staReq, STAREQ_STS_END_EMERG);  /* emergency */
        
        /*pTxBuf = (CPIPKT *) malloc (sizeof(CPIPKT));
        memcpy(pTxBuf, &txBuf, sizeof(MTP2TXPKT));*/

        /*ret = cpia_send(context->txHandle, (CPIPKT *)pTxBuf, NULL);*/
        ret = cpia_send(context->txHandle, (CPIPKT *)&txBuf, NULL);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send EMERGENCY CEASE failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));
            return (ITS_EPROTERR);
        }
        
        return (ITS_SUCCESS);
        
    case L3_L2_DATA:
        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        /* don't forget to strip off "MTP3 message type */
        txBuf.hdr.hdr.length        = HDRSIZE + dlen - 4 * sizeof(ITS_OCTET);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + dlen - 4 * sizeof(ITS_OCTET));
        txBuf.msgType               = MTP2_DATA_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
        memcpy(txBuf.data.datReq.data, L2_LINK_DATA(&ev) + 1,
               dlen - 4 * sizeof(ITS_OCTET));
        
        /*pTxBuf = (CPIPKT *) malloc (sizeof(CPIPKT));*/
        /*memcpy(pTxBuf, &txBuf, sizeof(MTP2TXPKT));*/

        /* cpia_send_data returns an error if more then 16 messages
         * are inqueue simultanously... we use token mechanism
         * to control the flow of data to the NMS4000 board.
         */

        ret = EMQUEUE_GetNextEvent(_NMS400_Token_Pool, &queueData, &len);
        if (ret != ITS_SUCCESS)
        {
            MTP2_ERROR(("Send DATA failed. Cannot Get token\n")); 

            return (ITS_EPROTERR);
 
        }
        memcpy(&token, queueData, sizeof(ITS_EVENT));
        ITS_Free(queueData);

        /*ret = cpia_send(context->txHandle, (CPIPKT *)pTxBuf, token);*/
        ret = cpia_send(context->txHandle, (CPIPKT *)&txBuf, &token);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send DATA failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));
            MTP2_Alarm_NMS(12021, __FILE__, __LINE__,
                           "LinkSet:LinkCode %d:%d",linkSet,linkCode);
            PEG_IncrPeg(NMS_MTP2_Pegs, PEG_MTP2_SEND_DATA_FAILED);

            return (ITS_EPROTERR);
        }
        
        PEG_IncrPeg(NMS_MTP2_Pegs, PEG_MTP2_MSU_TX);
        return (ITS_SUCCESS);
        
    case L3_L2_RETRIEVE_BSNT:
        MTP2_DEBUG(("MTP2:::: RETRIEVE BSNT\n"));

        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(StaReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(StaReq));
        txBuf.msgType               = MTP2_STAT_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
        MTP2_STA_REQ_SET_ACTION(txBuf.data.staReq, STAREQ_GET_BSN);  /* fetch BSNT */
        
        /*pTxBuf = (CPIPKT *) malloc (sizeof(CPIPKT));
        memcpy(pTxBuf, &txBuf, sizeof(MTP2TXPKT));*/

        /*ret = cpia_send(context->txHandle, (CPIPKT *)pTxBuf, NULL);*/
        ret = cpia_send(context->txHandle, (CPIPKT *)&txBuf, NULL);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send RETRIEVE BSNT failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));
            return (ITS_EPROTERR);
        }
        
        return (ITS_SUCCESS);
        
    case L3_L2_RETRIEVE_MSGS:
        MTP2_DEBUG(("MTP2:::: RETRIEVE MSGS\n"));

        memcpy(&fsnc, L2_LINK_DATA(&ev), sizeof(ITS_UINT));

        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(StaReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(StaReq));
        txBuf.msgType               = MTP2_STAT_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
        MTP2_STA_REQ_SET_ACTION(txBuf.data.staReq, STAREQ_GET_UNACKED);  /* fetch messages */
        MTP2_STA_REQ_SET_STATUS(txBuf.data.staReq, fsnc);

        /*pTxBuf = (CPIPKT *) malloc (sizeof(CPIPKT));
        memcpy(pTxBuf, &txBuf, sizeof(MTP2TXPKT));*/

        /*ret = cpia_send(context->txHandle, (CPIPKT *)pTxBuf, NULL);*/
        ret = cpia_send(context->txHandle, (CPIPKT *)&txBuf, NULL);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send RETRIEVE MSGS failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));
            MTP2_Alarm_NMS(12015, __FILE__, __LINE__,
                           "LinkSet:LinkCode %d:%d",linkSet,linkCode);

            return (ITS_EPROTERR);
        }
        
        return (ITS_SUCCESS);
        
    case L3_L2_CONNECT:
        MTP2_DEBUG(("MTP2:::: CONNECT: port %d\n", linkPort));


        /*
         * NMS doesn't let you do an L1 then L2 connect.
         */
        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(ConReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(ConReq));
        txBuf.msgType               = MTP2_CONN_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
        txBuf.data.conReq.status    = CONREQSTA_LVL_1_2_NORM;/*CONREQSTA_LVL_1; */          /* connect L1 */
        
        /*pTxBuf = (CPIPKT *) malloc (sizeof(CPIPKT));
        memcpy(pTxBuf, &txBuf, sizeof(MTP2TXPKT));*/

        /*ret = cpia_send(context->txHandle, (CPIPKT *)pTxBuf, NULL);*/
        ret = cpia_send(context->txHandle, (CPIPKT *)&txBuf, NULL);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send CONNECT failed. cpi_send failed: %ld\n",
                              cpi_get_last_error()));
            return (ITS_EPROTERR);
        }


        return (ITS_SUCCESS);
        
    case L3_L2_DISCONNECT:
        MTP2_DEBUG(("MTP2:::: DISCONNECT\n"));

#if 0
        /* NMS doesn't seem to work quite right with this */
        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(DisReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(DisReq));
        txBuf.msgType               = MTP2_DISC_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
        MTP2_DIS_REQ_SET_REASON(txBuf.data.disReq, DISCREQ_LVL_1_TOO);/* disconnect L1 */
        
        ret = cpi_send(context->txHandle, (CPIPKT *)&txBuf);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send DISCONNECT failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));
            return (ITS_EPROTERR);
        }
#endif
        return (ITS_SUCCESS);
        
    case L3_L2_FLOW_CONTROL_START:
        MTP2_DEBUG(("MTP2:::: FLOW CONTROL START\n"));

        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(FlowReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(FlowReq));
        txBuf.msgType               = MTP2_FLOW_RSP;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */

        MTP2_FLOW_REQ_SET_ACTION(txBuf.data.flowReq, FLOWREQ_SETLEVEL);
        txBuf.data.flowReq.flcLevel = GetFlcLevel(context, linkCode);

        MTP2_DEBUG(("Responding with level: %d for linkPort %d.\n",
                    GetFlcLevel(context, linkCode), linkPort));

        ret = cpia_send(context->txHandle, (CPIPKT *)&txBuf, NULL);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send FLOW CONTROL START failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));
            return (ITS_EPROTERR);
        }

        return (ITS_SUCCESS);

    case L3_L2_FLOW_CONTROL_STOP:
        MTP2_DEBUG(("MTP2:::: FLOW CONTROL STOP\n"));

        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(FlowReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(FlowReq));
        txBuf.msgType               = MTP2_FLOW_RSP;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
        MTP2_FLOW_REQ_SET_ACTION(txBuf.data.flowReq, FLOWREQ_SETLEVEL);

        txBuf.data.flowReq.flcLevel = GetFlcLevel(context, linkCode);

        MTP2_DEBUG(("Responding with level: %d for linkPort %d.\n",
                     GetFlcLevel(context, linkCode), linkPort));

        ret = cpia_send(context->txHandle, (CPIPKT *)&txBuf, NULL);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send FLOW CONTROL STOP failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));
            return (ITS_EPROTERR);
        }

        return (ITS_SUCCESS);

    case L3_L2_LOCAL_PROCESSOR_OUT:
        MTP2_DEBUG(("MTP2:::: LOCAL PROCESSOR OUT\n"));

        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(StaReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(StaReq));
        txBuf.msgType               = MTP2_STAT_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
        MTP2_STA_REQ_SET_ACTION(txBuf.data.staReq, STAREQ_CHANGE_STATUS);  /* fetch messages */
        MTP2_STA_REQ_SET_STATUS(txBuf.data.staReq, STAREQ_STS_LCL_DOWN);

        /*pTxBuf = (CPIPKT *) malloc (sizeof(CPIPKT));
        memcpy(pTxBuf, &txBuf, sizeof(MTP2TXPKT));*/

        /*ret = cpia_send(context->txHandle, (CPIPKT *)pTxBuf, NULL);*/
        ret = cpia_send(context->txHandle, (CPIPKT *)&txBuf, NULL);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send LOCAL PROC DOWN failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));
            return (ITS_EPROTERR);
        }
        
        return (ITS_SUCCESS);

    case L3_L2_LOCAL_PROCESSOR_REC:
        MTP2_DEBUG(("MTP2:::: LOCAL PROCESSOR UP\n"));

        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(StaReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(StaReq));
        txBuf.msgType               = MTP2_STAT_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
        MTP2_STA_REQ_SET_ACTION(txBuf.data.staReq, STAREQ_CHANGE_STATUS);  /* fetch messages */
        MTP2_STA_REQ_SET_STATUS(txBuf.data.staReq, STAREQ_STS_LCL_UP);

        /*pTxBuf = (CPIPKT *) malloc (sizeof(CPIPKT));
        memcpy(pTxBuf, &txBuf, sizeof(MTP2TXPKT));*/

        /*ret = cpia_send(context->txHandle, (CPIPKT *)pTxBuf, NULL);*/
        ret = cpia_send(context->txHandle, (CPIPKT *)&txBuf, NULL);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send LOCAL PROC UP failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));
            return (ITS_EPROTERR);
        }
        
        return (ITS_SUCCESS);

    default:
        break;
    }

    return (ITS_SUCCESS);
}
#else
int
NMSSendMTP2Event(ITS_SS7_HANDLE handle, ITS_OCTET *data, ITS_USHORT dlen)
{
    ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *)handle;
    MTP2TXPKT       txBuf;
    ITS_EVENT ev;
    ITS_OCTET linkSet;
    ITS_OCTET linkCode;
    ITS_OCTET linkPort;
    ITS_UINT fsnc=0;
    short ret;

    ev.data = data;
    ev.len = dlen;

    memset(&txBuf, 0, sizeof(txBuf));

    linkSet = L2_LINK_SET(&ev);
    linkCode = L2_LINK_CODE(&ev);
    linkPort = GetLinkPort(context, linkCode);

    switch (L2_MSG_TYPE(&ev))
    {
    case L3_L2_START:
        MTP2_DEBUG(("MTP2:::: START\n"));

#if 0
        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(DisReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(DisReq));
        txBuf.msgType               = MTP2_DISC_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
        MTP2_DIS_REQ_SET_REASON(txBuf.data.disReq, DISCREQ_LVL_2_ONLY);/* disconnect L1 */
        

        ret = cpi_send(context->txHandle, (CPIPKT *)&txBuf);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send DISCONNECT failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));
            return (ITS_EPROTERR);
        }
#endif

        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(ConReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(ConReq));
        txBuf.msgType               = MTP2_CONN_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);                    /* board link number */
        if (context->emergency & (1 << linkPort))
        {
            txBuf.data.conReq.status   = CONREQSTA_LVL_1_2_EMRG;  /* emergency align */
        }
        else
        {
            txBuf.data.conReq.status   = CONREQSTA_LVL_1_2_NORM;  /* normal align */
        }
        
        ret = cpi_send(context->txHandle, (CPIPKT *)&txBuf);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send START failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));
            MTP2_Alarm_NMS(12010, __FILE__, __LINE__,
                         "LinkSet:LinkCode %d:%d",linkSet,linkCode);

            return (ITS_EPROTERR);
        }

        MTP2_Alarm_NMS(12012, __FILE__, __LINE__,
                         "LinkSet:LinkCode %d:%d",linkSet,linkCode);
        
        return (ITS_SUCCESS);
        
    case L3_L2_STOP:
        MTP2_DEBUG(("MTP2:::: STOP\n"));

        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(DisReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(DisReq));
        txBuf.msgType               = MTP2_DISC_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
#if 0
        /* This doesn't seem to work well, use Disconnect Mgmt Req instead */
        MTP2_DIS_REQ_SET_REASON(txBuf.data.disReq, DISCREQ_LVL_2_ONLY);   /* disconnect L2 */
#endif
        MTP2_DIS_REQ_SET_REASON(txBuf.data.disReq, DISCREQ_MGMT_REQ);   /* disconnect L2 */
        ret = cpi_send(context->txHandle, (CPIPKT *)&txBuf);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send STOP failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));
            MTP2_Alarm_NMS(12011, __FILE__, __LINE__,
                       "LinkSet:LinkCode %d:%d",linkSet,linkCode);

            return (ITS_EPROTERR);
        }

        MTP2_Alarm_NMS(12013, __FILE__, __LINE__,
                       "LinkSet:LinkCode %d:%d",linkSet,linkCode);
        
        return (ITS_SUCCESS);
        
    case L3_L2_RESUME:
        MTP2_DEBUG(("MTP2:::: RESUME\n"));

        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(ConReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(ConReq));
        txBuf.msgType               = MTP2_CONN_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
        if (context->emergency & (1 << linkPort))
        {
            txBuf.data.conReq.status   = CONREQSTA_LVL_2_EMRG;   /* emergency align */
        }
        else
        {
            txBuf.data.conReq.status   = CONREQSTA_LVL_2_NORM;   /* normal align */
        }
        
        ret = cpi_send(context->txHandle, (CPIPKT *)&txBuf);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send RESUME failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));
            return (ITS_EPROTERR);
        }
        
        return (ITS_SUCCESS);
        
    case L3_L2_CLEAR_BUFFERS:
    case L3_L2_CLEAR_RTB:
        MTP2_DEBUG(("MTP2:::: CLEAR BUFFERS\n"));

        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(StaReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(StaReq));
        txBuf.msgType               = MTP2_STAT_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
        MTP2_STA_REQ_SET_ACTION(txBuf.data.staReq, STAREQ_DROP_UNACKED); /* drop all queued transmit */
        
        ret = cpi_send(context->txHandle, (CPIPKT *)&txBuf);
        if (ret != CPI_SUCCESS)
        {
            MTP2_Alarm_NMS(12019, __FILE__, __LINE__,
                           "LinkSet:LinkCode %d:%d",linkSet,linkCode);
            return (ITS_EPROTERR);
        }
        
        return (ITS_SUCCESS);
        
    case L3_L2_EMERGENCY:
        MTP2_DEBUG(("MTP2:::: EMERGENCY\n"));

        /* set emergency bit for this link */
        context->emergency |= 1 << linkPort;
        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(StaReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(StaReq));
        txBuf.msgType               = MTP2_STAT_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
        MTP2_STA_REQ_SET_ACTION(txBuf.data.staReq, STAREQ_CHANGE_STATUS);    /* status alteration */
        MTP2_STA_REQ_SET_STATUS(txBuf.data.staReq, STAREQ_STS_START_EMERG);  /* emergency */
        
        ret = cpi_send(context->txHandle, (CPIPKT *)&txBuf);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send EMERGENCY failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));
            MTP2_Alarm_NMS(12020, __FILE__, __LINE__,
                       "LinkSet:LinkCode %d:%d",linkSet,linkCode);

            return (ITS_EPROTERR);
        }
        
        return (ITS_SUCCESS);
        
    case L3_L2_EMERGENCY_CEASE:
        MTP2_DEBUG(("MTP2:::: EMERGENCY CEASE\n"));

        /* clear emergency bit for this link */
        context->emergency &= ~(1 << linkPort);
        
        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(StaReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(StaReq));
        txBuf.msgType               = MTP2_STAT_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
        MTP2_STA_REQ_SET_ACTION(txBuf.data.staReq, STAREQ_CHANGE_STATUS);    /* status alteration */
        MTP2_STA_REQ_SET_STATUS(txBuf.data.staReq, STAREQ_STS_END_EMERG);  /* emergency */
        
        ret = cpi_send(context->txHandle, (CPIPKT *)&txBuf);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send EMERGENCY CEASE failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));
            return (ITS_EPROTERR);
        }
        
        return (ITS_SUCCESS);
        
    case L3_L2_DATA:
        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        /* don't forget to strip off "MTP3 message type */
        txBuf.hdr.hdr.length        = HDRSIZE + dlen - 4 * sizeof(ITS_OCTET);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + dlen - 4 * sizeof(ITS_OCTET));
        txBuf.msgType               = MTP2_DATA_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
        memcpy(txBuf.data.datReq.data, L2_LINK_DATA(&ev) + 1,
               dlen - 4 * sizeof(ITS_OCTET));
        
        ret = cpi_send(context->txHandle, (CPIPKT *)&txBuf);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send DATA failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));
            MTP2_Alarm_NMS(12021, __FILE__, __LINE__,
                           "LinkSet:LinkCode %d:%d",linkSet,linkCode);
            PEG_IncrPeg(NMS_MTP2_Pegs, PEG_MTP2_SEND_DATA_FAILED);

            return (ITS_EPROTERR);
        }
        
        PEG_IncrPeg(NMS_MTP2_Pegs, PEG_MTP2_MSU_TX);
        return (ITS_SUCCESS);
        
    case L3_L2_RETRIEVE_BSNT:
        MTP2_DEBUG(("MTP2:::: RETRIEVE BSNT\n"));

        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(StaReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(StaReq));
        txBuf.msgType               = MTP2_STAT_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
        MTP2_STA_REQ_SET_ACTION(txBuf.data.staReq, STAREQ_GET_BSN);  /* fetch BSNT */
        
        ret = cpi_send(context->txHandle, (CPIPKT *)&txBuf);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send RETRIEVE BSNT failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));
            return (ITS_EPROTERR);
        }
        
        return (ITS_SUCCESS);
        
    case L3_L2_RETRIEVE_MSGS:
        MTP2_DEBUG(("MTP2:::: RETRIEVE MSGS\n"));

        memcpy(&fsnc, L2_LINK_DATA(&ev), sizeof(ITS_UINT));

        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(StaReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(StaReq));
        txBuf.msgType               = MTP2_STAT_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
        MTP2_STA_REQ_SET_ACTION(txBuf.data.staReq, STAREQ_GET_UNACKED);  /* fetch messages */
        MTP2_STA_REQ_SET_STATUS(txBuf.data.staReq, fsnc);

        ret = cpi_send(context->txHandle, (CPIPKT *)&txBuf);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send RETRIEVE MSGS failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));
            MTP2_Alarm_NMS(12015, __FILE__, __LINE__,
                           "LinkSet:LinkCode %d:%d",linkSet,linkCode);

            return (ITS_EPROTERR);
        }
        
        return (ITS_SUCCESS);
        
    case L3_L2_CONNECT:
        MTP2_DEBUG(("MTP2:::: CONNECT\n"));

#if 0
        /*
         * NMS doesn't let you do an L1 then L2 connect.
         */
        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(ConReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(ConReq));
        txBuf.msgType               = MTP2_CONN_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
        txBuf.data.conReq.status    = CONREQSTA_LVL_1;           /* connect L1 */
        
        ret = cpi_send(context->txHandle, (CPIPKT *)&txBuf);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send CONNECT failed. cpi_send failed: %ld\n",
                              cpi_get_last_error()));
            return (ITS_EPROTERR);
        }
#endif

        return (ITS_SUCCESS);
        
    case L3_L2_DISCONNECT:
        MTP2_DEBUG(("MTP2:::: DISCONNECT\n"));

#if 0
        /* NMS doesn't seem to work quite right with this */
        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(DisReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(DisReq));
        txBuf.msgType               = MTP2_DISC_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
        MTP2_DIS_REQ_SET_REASON(txBuf.data.disReq, DISCREQ_LVL_1_TOO);/* disconnect L1 */
        
        ret = cpi_send(context->txHandle, (CPIPKT *)&txBuf);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send DISCONNECT failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));
            return (ITS_EPROTERR);
        }
#endif
        return (ITS_SUCCESS);
        
    case L3_L2_FLOW_CONTROL_START:
        MTP2_DEBUG(("MTP2:::: FLOW CONTROL START\n"));
    
        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
#if 1
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(FlowReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(FlowReq));
        txBuf.msgType               = MTP2_FLOW_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
        MTP2_FLOW_REQ_SET_ACTION(txBuf.data.flowReq, FLOWREQ_SETLEVEL);
        txBuf.data.flowReq.flcLevel = FLOWIND_STOPPED;
#else
        txBuf.hdr.hdr.length        = HDRSIZE;
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE);
        txBuf.msgType               = MTP2_FLOW_RSP;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
#endif

        ret = cpi_send(context->txHandle, (CPIPKT *)&txBuf);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send FLOW CONTROL START failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));
            return (ITS_EPROTERR);
        }

        return (ITS_SUCCESS);

    case L3_L2_FLOW_CONTROL_STOP:
        MTP2_DEBUG(("MTP2:::: FLOW CONTROL STOP\n"));

        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(FlowReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(FlowReq));
        txBuf.msgType               = MTP2_FLOW_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
        MTP2_FLOW_REQ_SET_ACTION(txBuf.data.flowReq, FLOWREQ_SETLEVEL);
        txBuf.data.flowReq.flcLevel = FLOWIND_STOPPED;

        ret = cpi_send(context->txHandle, (CPIPKT *)&txBuf);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send FLOW CONTROL STOP failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));
            return (ITS_EPROTERR);
        }

        return (ITS_SUCCESS);

    case L3_L2_LOCAL_PROCESSOR_OUT:
        MTP2_DEBUG(("MTP2:::: LOCAL PROCESSOR OUT\n"));

        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(StaReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(StaReq));
        txBuf.msgType               = MTP2_STAT_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
        MTP2_STA_REQ_SET_ACTION(txBuf.data.staReq, STAREQ_CHANGE_STATUS);  /* fetch messages */
        MTP2_STA_REQ_SET_STATUS(txBuf.data.staReq, STAREQ_STS_LCL_DOWN);

        ret = cpi_send(context->txHandle, (CPIPKT *)&txBuf);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send LOCAL PROC DOWN failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));
            return (ITS_EPROTERR);
        }
        
        return (ITS_SUCCESS);

    case L3_L2_LOCAL_PROCESSOR_REC:
        MTP2_DEBUG(("MTP2:::: LOCAL PROCESSOR UP\n"));

        txBuf.hdr.hdr.src           = PORT(0, context->mtp2SrcEnt);
        txBuf.hdr.hdr.dst           = PORT(context->boardNum, MTP2_ENT);
        txBuf.hdr.hdr.length        = HDRSIZE + sizeof(StaReq);
        MTP2HDR_SET_START(txBuf.hdr, FILLER_COUNT);
        MTP2HDR_SET_END(txBuf.hdr, ENDSIZE + sizeof(StaReq));
        txBuf.msgType               = MTP2_STAT_REQ;
        TXPKT_SET_PROVIDER_ID(txBuf, linkPort);    /* board link number */
        MTP2_STA_REQ_SET_ACTION(txBuf.data.staReq, STAREQ_CHANGE_STATUS);  /* fetch messages */
        MTP2_STA_REQ_SET_STATUS(txBuf.data.staReq, STAREQ_STS_LCL_UP);

        ret = cpi_send(context->txHandle, (CPIPKT *)&txBuf);
        if (ret != CPI_SUCCESS)
        {
            MTP2_ERROR(("Send LOCAL PROC UP failed. cpi_send failed: %ld\n",
                            cpi_get_last_error()));
            return (ITS_EPROTERR);
        }
        
        return (ITS_SUCCESS);

    default:
        break;
    }

    return (ITS_SUCCESS);
}

#endif

/*
 ****************************************************************************
 *  Purpose:
 *      Processes the MML command received by the DBC Server
 *
 *  Input Parameters:
 *      DBC_Server*    dbc
 *      const char*    cmdLine
 *
 *  Input/Output Parameters:
 *      None
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      None
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  kramesh   22-04-2008  Bug ID:1533         Propagated BCGI Issue.
 *                                           MML pegs when links are terminated
 *                                           on another node.
 *  
 ****************************************************************************/
void
NMS_MTP2_Console(DBC_Server *dbc, const char *cmdLine)
{
    int ret;
    char buf[ITS_PATH_MAX];

    if (DBC_Cmd(dbc, "m2_get_gen_cfg", "MTP2 Get General Config", "<>", "<>"))
    {
        MTP2GeneralCfg *cfg = 0;
        ITS_UINT almLevel;

        cfg =  MTP2_GetGeneralCfg();
        sprintf(buf, "\n********** MTP2 General Config **********\n");
        DBC_AppendText(dbc, buf);

        almLevel = cfg->alarmLevel;

        switch(almLevel)
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
        strcpy(buf, "\n    MTP2 Trace -\n");
        DBC_AppendText(dbc, buf);

        if ( cfg->traceOn)
        {
           if (TRACE_IsLevelOn(MTP2_NMS_TraceData, MTP2_TRACE_CRITICAL))
           {
               strcpy(buf, "        Critical  = ");
               if (TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_CRITICAL, 0))
               {
                    strcat(buf, " stdout");
               }
               if (TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_CRITICAL, 1))
               {
                    strcat(buf, " file");
               }
               if (TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_CRITICAL, 2))
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

           if (TRACE_IsLevelOn(MTP2_NMS_TraceData, MTP2_TRACE_ERROR))
           {
               strcpy(buf, "        Error     = ");
               if (TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_ERROR, 0))
               {
                    strcat(buf, " stdout");
               }
               if (TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_ERROR, 1))
               {
                    strcat(buf, " file");
               }
               if (TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_ERROR, 2))
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

           if (TRACE_IsLevelOn(MTP2_NMS_TraceData, MTP2_TRACE_WARNING))
           {
               strcpy(buf, "        Warning   = ");
               if (TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_WARNING, 0))
               {
                    strcat(buf, " stdout");
               }
               if (TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_WARNING, 1))
               {
                    strcat(buf, " file");
               }
               if (TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_WARNING, 2))
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

           if (TRACE_IsLevelOn(MTP2_NMS_TraceData, MTP2_TRACE_DEBUG))
           {
               strcpy(buf, "        Debug     = ");
               if (TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_DEBUG, 0))
               {
                    strcat(buf, " stdout");
               }
               if (TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_DEBUG, 1))
               {
                    strcat(buf, " file");
               }
               if (TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_DEBUG, 2))
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

       }
        sprintf(buf, "\n********** End of MTP2 General Config **********\n");
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "m2_set_gen_cfg", "MTP2 Set General Config",
                     "<alarm level> <Trace Type> <traceOutput> <On/Off>",""))
    {
        MTP2GeneralCfg cfg;
        char alarmLevel[ITS_PATH_MAX];
        char traceOn[ITS_PATH_MAX];
        char traceType[ITS_PATH_MAX];
        char traceOutput[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s %s", buf, alarmLevel, traceType,
                     traceOutput, traceOn);

        if (ret != 5)
        {
            sprintf(buf, "\n********** Invalid Command Arguments **********\n"
                         "Usage: m2_set_gen_cfg <alarmlevel> <tracetype>"
                         " <trOutput> <On/Off>\n");
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
            strcpy(cfg.traceType, MTP2_CRITICAL_STRING);
        }
        else if (strstr(traceType, "ERROR") || strstr(traceType, "error"))
        {
            strcpy(cfg.traceType, MTP2_ERROR_STRING);
        }
        else if (strstr(traceType, "WARNING") || strstr(traceType, "warning"))
        {
            strcpy(cfg.traceType, MTP2_WARNING_STRING);
        }
        else if (strstr(traceType, "DEBUG") || strstr(traceType, "debug"))
        {
            strcpy(cfg.traceType, MTP2_DEBUG_STRING);
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
            strcpy(cfg.traceOutput, MTP2_STDOUT_STRING);
        }
        else if (strstr(traceOutput, "FILE") || strstr(traceOutput, "file"))
        {
            strcpy(cfg.traceOutput, MTP2_FILE_STRING);
        }
        else if (strstr(traceOutput, "SYSLOG") || strstr(traceOutput, "syslog"))
        {
            strcpy(cfg.traceOutput, MTP2_SYSLOG_STRING);
        }
        else
        {
            sprintf(buf, "\nInvalid Trace Output\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret = MTP2_SetGeneralCfg(&cfg);
        if (ret != ITS_SUCCESS)
        {
            return;
        }

       sprintf(buf, "\n********** MTP2 General Config Set **********\n");
       DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "m2_get_gen_peg", "Get MTP2 General Pegs", "<Peg Id>", "<>"))
    {
        char pgName[ITS_PATH_MAX];
        ITS_OCTET pegId;
        ITS_UINT value;

        ret = sscanf(cmdLine, "%s %s", buf, pgName);
        if (ret != 2)
        {
             sprintf(buf,  "\n********** Invalid Command Arguments **********\n"
                           "Usage: m2_get_gen_peg [<Peg Id> or <All/all>]\n");
             DBC_AppendText(dbc, buf);
             return;
        }

        if(strncmp(pgName, "All", 3) == 0 ||
           strncmp(pgName, "all", 3) == 0 ||
           atoi(pgName) == ALL_MTP2_PEGS)
        {
           DumpGeneralPegs(dbc);
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

        pegId = atoi(pgName);

        if (pegId >= PEG_NMS_MTP2_NUM_GLOBAL_PEGS)
        {
            sprintf(buf, "\n********** Invalid Peg Type **********\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "\n   %s \n", mtp2GPegStr[pegId]);
        DBC_AppendText(dbc, buf);

           value = PEG_GetPeg(NMS_MTP2_Pegs, pegId);

        sprintf(buf, "\n   value is %d\n", value);
        DBC_AppendText(dbc, buf);
    }

#if 0
    else if (DBC_Cmd(dbc, "m2_get_gen_pegids", "Get all MTP2 General Peg Ids", "<>", "<>"))
    {
        DumpGeneralPegIds(dbc);
    }
#endif

    else if (DBC_Cmd(dbc, "m2_clr_gen_peg", "Clear MTP2 General Pegs", "<Peg Id>", "<>"))
    {
        char pegType[ITS_PATH_MAX];
        ITS_OCTET pegId;

        ret = sscanf(cmdLine, "%s %s", buf, pegType);

        if (ret != 2)
        {
            sprintf(buf, "\n********** Invalid Command Arguments **********\n"
                         "Usage: m2_clr_gen_peg [<Peg Id> or <All/all>]\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if(strncmp(pegType, "All", 3) == 0 ||
           strncmp(pegType, "all", 3) == 0 ||
           atoi(pegType) == ALL_MTP2_PEGS)
        {
           for (pegId = 0; pegId < PEG_NMS_MTP2_NUM_GLOBAL_PEGS; pegId++)
           {
               PEG_ClearPeg(NMS_MTP2_Pegs, pegId);
           }

           sprintf(buf, "\n** Cleared all MTP2 general pegs **\n");
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

        if (atoi(pegType) >= PEG_NMS_MTP2_NUM_GLOBAL_PEGS)
        {
             sprintf(buf, "\n** MTP2 general peg %d does not exist **\n",
                                                       atoi(pegType));
             DBC_AppendText(dbc, buf);
             return;
        }

        PEG_ClearPeg(NMS_MTP2_Pegs, atoi(pegType));

        sprintf(buf, "\n** Cleared MTP2 general peg id %d **\n", atoi(pegType));
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "m2_get_all_link_pegs", "Get MTP2 Link Pegs",
                          "<linkset> <linkcode>", "<>"))
    {
        ITS_INT linkSet, linkCode;
        ITS_OCTET i;
        SS7_LinkPtr ln;
        MTP2_STATUS ret;
        MTP2LinkStats linkStats;
        ITS_SHORT linkNum;
        TRANSPORT_Control *tc;
        SS7TRAN_Manager *ss7;
        ITS_SS7_CONTEXT *context;
        VENDOR_Instance *inst;

        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            sprintf(buf, "\n********** Invalid Command Arguments **********\n"
                         "Usage: m2_get_all_link_pegs <linkset> <linkcode>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
        {
            sprintf(buf, "\n*** Link %d on linkset %d is not configured ***\n",
                           linkCode, linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }

        tc = TRANSPORT_FindTransport(ln->id);

        if ((tc != NULL) && 
            (TRANSPORT_MASK(tc) & ITS_TRANSPORT_SS7) &&
            ((TRANSPORT_MASK(tc) & ITS_MTP2_ANSI) || 
             (TRANSPORT_MASK(tc) & ITS_MTP2_CCITT)))
        {
            ss7 = (SS7TRAN_Manager *)tc;
            inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);
            context = (ITS_SS7_CONTEXT *)inst;

            ret = Mtp2MgmtInit(context->boardNum, context->srcEnt, 
                               context->srcInst);

            if (ret == MTP2_SUCCESS)
            {
                linkNum = 0;
                for (i = 0; i < context->numLinkCodes; i++)
                {
                    if (context->dataLink[i].linkCode == (ITS_OCTET)linkCode)
                    {
                        linkNum = context->dataLink[i].linkPort;
                        break;
                    }
                }

                ret = Mtp2LinkStats(context->boardNum, linkNum, &linkStats, 
                                    ITS_FALSE);

                if (ret == MTP2_SUCCESS)
                {
                    DumpLinkPegs(dbc, linkSet, linkCode, &linkStats);
                }
                else
                {
                    sprintf(buf, "\n** Error while getting link pegs **\n");
                    DBC_AppendText(dbc, buf);
                    return;
                }
            }
            else
            {
                sprintf(buf, "\n** Error while getting link pegs **\n");
                DBC_AppendText(dbc, buf);
                return;
            }
        }
        else if (tc != NULL)
        {
            sprintf(buf, "\n*** Link %d on linkset %d may not terminate on"
                         " this node ***\n", linkCode, linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }
    }
    else if (DBC_Cmd(dbc, "m2_clr_all_link_pegs", "Clear MTP2 Link Pegs",
                          "<linkset> <linkcode>", "<>"))
    {
        ITS_INT linkSet, linkCode;
        ITS_OCTET i;
        SS7_LinkPtr ln;
        MTP2_STATUS ret;
        MTP2LinkStats linkStats;
        ITS_SHORT linkNum;
        TRANSPORT_Control *tc;
        SS7TRAN_Manager *ss7;
        ITS_SS7_CONTEXT *context;
        VENDOR_Instance *inst;

        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            sprintf(buf, "\n********** Invalid Command Arguments **********\n"
                         "Usage: m2_clr_all_link_pegs <linkset> <linkcode>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
        {
            sprintf(buf, "\n*** Link %d on linkset %d is not configured ***\n",
                           linkSet, linkCode);
            DBC_AppendText(dbc, buf);
            return;
        }

        tc = TRANSPORT_FindTransport(ln->id);

        if ((tc != NULL) && 
            (TRANSPORT_MASK(tc) & ITS_TRANSPORT_SS7) &&
            ((TRANSPORT_MASK(tc) & ITS_MTP2_ANSI) || 
             (TRANSPORT_MASK(tc) & ITS_MTP2_CCITT)))
        {

            ss7 = (SS7TRAN_Manager *)tc;
            inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);
            context = (ITS_SS7_CONTEXT *)inst;

            ret =  Mtp2MgmtInit(context->boardNum, context->srcEnt,
                                context->srcInst);

            if (ret == MTP2_SUCCESS)
            {
                linkNum = 0;
                for (i = 0; i < context->numLinkCodes; i++)
                {
                    if (context->dataLink[i].linkCode == (ITS_OCTET)linkCode)
                    {
                        linkNum = context->dataLink[i].linkPort;
                        break;
                    }
                }

                ret = Mtp2LinkStats(context->boardNum, linkNum, &linkStats, 1);
                if (ret == MTP2_SUCCESS)
                {
                    sprintf(buf, "\n***** Cleared MTP2 link pegs for  *****\n");
                    DBC_AppendText(dbc, buf);
                    sprintf(buf, "\n    Linkset:%d  Linkcode:%d \n", linkSet,
                                                                     linkCode);
                    DBC_AppendText(dbc, buf);
                }
                else
                {
                    sprintf(buf, "\n** Error while clearing link pegs **\n");
                    DBC_AppendText(dbc, buf);
                    return;
                }
            }
            else
            {
                sprintf(buf, "\n** Error while clearing link pegs **\n");
                DBC_AppendText(dbc, buf);
                return;
            }
        }
        else if (tc != NULL)
        {
            sprintf(buf, "\n*** Link %d on linkset %d may not terminate on"
                         " this node ***\n", linkCode, linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }
    }
}

/*
 ****************************************************************************
 *  Purpose:
 *      Gets the MTP2 Alarms and Trace levels
 *
 *  Input Parameters:
 *      None
 *
 *  Input/Output Parameters:
 *      None
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      MTP2GeneralCfg*     cfg
 ****************************************************************************/
MTP2GeneralCfg*
MTP2_GetGeneralCfg()
{
    MTP2GeneralCfg *cfg;

    cfg = calloc(1, sizeof(MTP2GeneralCfg));
    if (cfg == NULL)
    {
        return (NULL);
    }
    cfg->traceOn = (TRACE_IsLevelOn(MTP2_NMS_TraceData, MTP2_TRACE_CRITICAL) &&
                    (TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_CRITICAL, 0) ||
                     TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_CRITICAL, 1) ||
                     TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_CRITICAL, 2))) ||
                   (TRACE_IsLevelOn(MTP2_NMS_TraceData, MTP2_TRACE_ERROR) &&
                    (TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_ERROR, 0) ||
                     TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_ERROR, 1) ||
                     TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_ERROR, 2))) ||
                   (TRACE_IsLevelOn(MTP2_NMS_TraceData, MTP2_TRACE_WARNING) &&
                    (TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_WARNING, 0) ||
                     TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_WARNING, 1) ||
                     TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_WARNING, 2))) ||
                   (TRACE_IsLevelOn(MTP2_NMS_TraceData, MTP2_TRACE_DEBUG) &&
                    (TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_DEBUG, 0) ||
                     TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_DEBUG, 1) ||
                     TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_DEBUG, 2)));

    cfg->alarmLevel = MTP2_AlarmLevel;

    return (cfg);
}

/*
 ****************************************************************************
 *  Purpose:
 *      Sets the MTP2 Alarms and Trace levels
 *
 *  Input Parameters:
 *      MTP2GeneralCfg*     cfg
 *
 *  Input/Output Parameters:
 *      None
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      None
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  kramesh   22-04-2008  Bug ID:1533        Propagated BCGI Issue.
 *                                           MML pegs when links are terminated
 *                                           on another node.
 *  
 ****************************************************************************/
int
MTP2_SetGeneralCfg(MTP2GeneralCfg* cfg)
{
    MTP2_AlarmLevel = cfg->alarmLevel;

    if (strstr(cfg->traceType, "all") != NULL)
    {
        if (cfg->traceOn == ITS_TRUE)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       cfg->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(MTP2_NMS_TraceData,
                                      MTP2_CRITICAL_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_ERROR_STRING,
                                       cfg->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(MTP2_NMS_TraceData,
                                      MTP2_ERROR_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_WARNING_STRING,
                                       cfg->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(MTP2_NMS_TraceData,
                                      MTP2_WARNING_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_DEBUG_STRING,
                                       cfg->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(MTP2_NMS_TraceData,
                                      MTP2_DEBUG_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       cfg->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_ERROR_STRING,
                                       cfg->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_WARNING_STRING,
                                       cfg->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_DEBUG_STRING,
                                       cfg->traceOutput, ITS_FALSE);
        }
    }
    else
    {
        if (cfg->traceOn == ITS_TRUE)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       cfg->traceType,
                                       cfg->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(MTP2_NMS_TraceData,
                                      cfg->traceType, ITS_TRUE);

        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       cfg->traceType,
                                       cfg->traceOutput, ITS_FALSE);
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Dumps MTP2 General Pegs
 *
 *  Input Parameters:
 *      DBC_Server*        dbc
 *
 *  Input/Output Parameters:
 *      None
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      None
 ****************************************************************************/
static void
DumpGeneralPegs(DBC_Server *dbc)
{
    char buf[ITS_PATH_MAX];

    sprintf(buf, "\n********** Printing Global Pegs **********\n");
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s:              value %d\n", 
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_GET_DATA_FAILED),
                      PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_GET_DATA_FAILED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s:              value %d\n", 
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_SEND_DATA_FAILED),
                      PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_SEND_DATA_FAILED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s:              value %d\n", 
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_LOCAL_PROC_DOWN),
                      PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_LOCAL_PROC_DOWN));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s:              value %d\n", 
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_LOCAL_PROC_UP),
                      PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_LOCAL_PROC_UP));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s:              value %d\n", 
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_REMOTE_PROC_DOWN),
                      PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_REMOTE_PROC_DOWN));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s:              value %d\n", 
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_REMOTE_PROC_UP),
                      PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_REMOTE_PROC_UP));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s:              value %d\n", 
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_STAT_IND),
                      PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_STAT_IND));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s:              value %d\n", 
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_SUERM_EXPIRY),
                      PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_SUERM_EXPIRY));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s:              value %d\n", 
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_INCORRECT_FIB_BSN),
                      PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_INCORRECT_FIB_BSN));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s:              value %d\n", 
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_CONG_DETECTED),
                      PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_CONG_DETECTED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s:              value %d\n", 
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_CONG_RECOVERED),
                      PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_CONG_RECOVERED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s:              value %d\n", 
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_MSU_TX),
                      PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_MSU_TX));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s:              value %d\n", 
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_MSU_RX),
                      PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_MSU_RX));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s:              value %d\n", 
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_T2_EXPIRED),
                      PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_T2_EXPIRED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s:              value %d\n", 
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_T6_EXPIRED),
                      PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_T6_EXPIRED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s:              value %d\n", 
                    GLOBAL_PEGID_TO_TEXT(PEG_MTP2_T7_EXPIRED),
                      PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_T7_EXPIRED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n*******************************************\n");
    DBC_AppendText(dbc, buf);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Dumps MTP2 General Peg Ids
 *
 *  Input Parameters:
 *      DBC_Server*     dbc
 *
 *  Input/Output Parameters:
 *      None
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      None
 ****************************************************************************/
static void
DumpGeneralPegIds(DBC_Server *dbc)
{
    char buf[32000];

    memset(buf , 0, 32000);

    sprintf(buf, "\n********** Printing Global Peg Ids **********\n");
    DBC_AppendText(dbc, buf);

    /* Print the pegs and their assciated Id's */
    sprintf(buf, "\n%26s %5d: value %d\n", 
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_GET_DATA_FAILED),
                 PEG_MTP2_GET_DATA_FAILED, 
                PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_GET_DATA_FAILED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n", 
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_SEND_DATA_FAILED),
                 PEG_MTP2_SEND_DATA_FAILED, 
                PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_SEND_DATA_FAILED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n", 
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_LOCAL_PROC_DOWN),
                 PEG_MTP2_LOCAL_PROC_DOWN, 
                PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_LOCAL_PROC_DOWN));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n", 
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_LOCAL_PROC_UP),
                 PEG_MTP2_LOCAL_PROC_UP, 
                PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_LOCAL_PROC_UP));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n", 
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_REMOTE_PROC_DOWN),
                 PEG_MTP2_REMOTE_PROC_DOWN, 
                PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_REMOTE_PROC_DOWN));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n", 
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_REMOTE_PROC_UP),
                 PEG_MTP2_REMOTE_PROC_UP, 
                PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_REMOTE_PROC_UP));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n", 
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_STAT_IND),
                 PEG_MTP2_STAT_IND, 
                PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_STAT_IND));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n", 
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_SUERM_EXPIRY),
                 PEG_MTP2_SUERM_EXPIRY, 
                PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_SUERM_EXPIRY));

    DBC_AppendText(dbc, buf);
    sprintf(buf, "\n%26s %5d: value %d\n", 
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_INCORRECT_FIB_BSN),
                 PEG_MTP2_INCORRECT_FIB_BSN, 
                PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_INCORRECT_FIB_BSN));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n", 
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_CONG_DETECTED),
                 PEG_MTP2_CONG_DETECTED, 
                PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_CONG_DETECTED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n", 
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_CONG_RECOVERED),
                 PEG_MTP2_CONG_RECOVERED, 
                PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_CONG_RECOVERED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n", 
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_MSU_TX),
                 PEG_MTP2_MSU_TX, 
                PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_MSU_TX));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n", 
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_MSU_RX),
                 PEG_MTP2_MSU_RX, 
                PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_MSU_RX));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n", 
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_T2_EXPIRED),
                 PEG_MTP2_T2_EXPIRED, 
                PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_T2_EXPIRED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n", 
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_T6_EXPIRED),
                 PEG_MTP2_T6_EXPIRED, 
                PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_T6_EXPIRED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%26s %5d: value %d\n", 
                GLOBAL_PEGID_TO_TEXT(PEG_MTP2_T7_EXPIRED),
                 PEG_MTP2_T7_EXPIRED, 
                PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_T7_EXPIRED));
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n*******************************************\n");
    DBC_AppendText(dbc, buf);
}

/*
 ****************************************************************************
 *  Purpose:
 *      Dumps MTP2 Link Pegs
 *
 *  Input Parameters:
 *      DBC_Server*     dbc
 *
 *  Input/Output Parameters:
 *      None
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      void
 ****************************************************************************/
static void
DumpLinkPegs(DBC_Server *dbc, ITS_OCTET linkSet,
             ITS_OCTET linkCode, MTP2LinkStats *linkPegs)
{
    char buf[ITS_PATH_MAX];

    sprintf(buf, "\n********** Printing Link Pegs for **********\n");
    DBC_AppendText(dbc, buf);
    sprintf(buf, "\n    Linkset:%d  Linkcode:%d \n", linkSet, linkCode);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %lu\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_FAIL_ALL_REASON),
                    linkPegs->slFailAll);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %lu\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_SUERM_EXPIRY),
                    linkPegs->slFailErr);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %lu\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_INCORRECT_FIB_BSN),
                    linkPegs->slFailAb);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %lu\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_T6_EXPIRED),
                    linkPegs->slFailCong);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %lu\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_T7_EXPIRED),
                    linkPegs->slFailAck);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %lu\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_PROV_ALIGN_FAILED),
                    linkPegs->slFailAlign);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %lu\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_ERR_SU),
                    linkPegs->slNSUErr);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %lu\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_NEG_ACK),
                    linkPegs->slNegAck);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %lu\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_MSU_TX),
                    linkPegs->mTx);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %lu\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_MSU_RX),
                    linkPegs->mRx);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %lu\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_SIF_SIO_OCTET_TX),
                    linkPegs->nSifSioTx);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %lu\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_SIF_SIO_OCTET_RX),
                    linkPegs->nSifSioRx);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n%32s:              value %lu\n",
                    LINK_PEGID_TO_TEXT(PEG_MTP2_LINK_OCTET_RTX),
                    linkPegs->nRetrans);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n*******************************************\n");
    DBC_AppendText(dbc, buf);
}


/****************************************************************************
 *  Purpose:
 *      Gets the MTP2 General config
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      MTP2_GeneralCfg*    genCfg
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITS_INT 
MTP2_OSS_GetGeneralCfg(MTP2_GeneralCfg* genCfg)
{
    if (genCfg == NULL)
        return ITS_ENOMEM;

    genCfg->alarmLevel = (MGMT_AlarmLevel)MTP2_AlarmLevel;

    genCfg->debugTrace = TRACE_IsLevelOn(MTP2_NMS_TraceData, MTP2_TRACE_DEBUG);
    if (genCfg->debugTrace)
    {
        genCfg->debugTraceOutput = 0;
        if (TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_DEBUG, 0))
        {
            genCfg->debugTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_DEBUG, 1))
        {
            genCfg->debugTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_DEBUG, 2))
        {
            genCfg->debugTraceOutput |= TRACE_TO_SYSLOG;
        }
        if (!genCfg->debugTraceOutput)
        {
            genCfg->debugTraceOutput |= TRACE_TO_NONE;
        }
    }

    genCfg->warningTrace = TRACE_IsLevelOn(MTP2_NMS_TraceData, MTP2_TRACE_WARNING);
    if (genCfg->warningTrace)
    {
        genCfg->warningTraceOutput = 0;
        if (TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_WARNING, 0))
        {
            genCfg->warningTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_WARNING, 1))
        {
            genCfg->warningTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_WARNING, 2))
        {
            genCfg->warningTraceOutput |= TRACE_TO_SYSLOG;
        }
        if (!genCfg->warningTraceOutput)
        {
            genCfg->warningTraceOutput |= TRACE_TO_NONE;
        }
    }

    genCfg->errorTrace = TRACE_IsLevelOn(MTP2_NMS_TraceData, MTP2_TRACE_ERROR);
    if (genCfg->errorTrace)
    {
        genCfg->errorTraceOutput = 0;
        if (TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_ERROR, 0))
        {
            genCfg->errorTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_ERROR, 1))
        {
            genCfg->errorTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_ERROR, 2))
        {
            genCfg->errorTraceOutput |= TRACE_TO_SYSLOG;
        }
        if (!genCfg->errorTraceOutput)
        {
            genCfg->errorTraceOutput |= TRACE_TO_NONE;
        }
    }

    genCfg->criticalTrace = TRACE_IsLevelOn(MTP2_NMS_TraceData, MTP2_TRACE_CRITICAL);
    if (genCfg->criticalTrace)
    {
       genCfg->criticalTraceOutput = 0;
        if (TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_CRITICAL, 0))
        {
            genCfg->criticalTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_CRITICAL, 1))
        {
            genCfg->criticalTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(MTP2_NMS_TraceData, MTP2_TRACE_CRITICAL, 2))
        {
            genCfg->criticalTraceOutput |= TRACE_TO_SYSLOG;
        }
        if (!genCfg->criticalTraceOutput)
        {
            genCfg->criticalTraceOutput |= TRACE_TO_NONE;
        }
    }

    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Sets the MTP2 General config
 *
 *  Input Parameters:
 *      MTP2_GeneralCfg*    genCfg
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITS_INT 
MTP2_OSS_SetGeneralCfg(MTP2_GeneralCfg* genCfg)
{
    if (genCfg == NULL)
        return ITS_ENOMEM;

    MTP2_AlarmLevel = genCfg->alarmLevel;

    if (genCfg->debugTrace)
    {
        TRACE_SetLevelOnOffByName(MTP2_NMS_TraceData, MTP2_DEBUG_STRING,  ITS_TRUE);

        if (genCfg->debugTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_STDOUT_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->debugTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_FILE_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->debugTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_SYSLOG_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->debugTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_DEBUG_STRING,
                                       MTP2_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(MTP2_NMS_TraceData, MTP2_DEBUG_STRING,  ITS_FALSE);
        }
    }

    if (genCfg->warningTrace)
    {
        TRACE_SetLevelOnOffByName(MTP2_NMS_TraceData, MTP2_WARNING_STRING,  ITS_TRUE);

        if (genCfg->warningTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_STDOUT_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->warningTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_FILE_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->warningTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_SYSLOG_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->warningTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_WARNING_STRING,
                                       MTP2_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(MTP2_NMS_TraceData, MTP2_WARNING_STRING,  ITS_FALSE);
        }
    }

    if (genCfg->errorTrace)
    {
        TRACE_SetLevelOnOffByName(MTP2_NMS_TraceData, MTP2_ERROR_STRING,  ITS_TRUE);

        if (genCfg->errorTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_STDOUT_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->errorTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_FILE_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->errorTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_SYSLOG_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->errorTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_ERROR_STRING,
                                       MTP2_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(MTP2_NMS_TraceData, MTP2_ERROR_STRING,  ITS_FALSE);
        }
    }

    if (genCfg->criticalTrace)
    {
        TRACE_SetLevelOnOffByName(MTP2_NMS_TraceData, MTP2_CRITICAL_STRING,  ITS_TRUE);

        if (genCfg->criticalTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_STDOUT_STRING,
                                       ITS_TRUE);
        }

        else
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_STDOUT_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->criticalTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_FILE_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->criticalTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_SYSLOG_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->criticalTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP2_NMS_TraceData,
                                       MTP2_CRITICAL_STRING,
                                       MTP2_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(MTP2_NMS_TraceData, MTP2_CRITICAL_STRING,  ITS_FALSE);
        }
    }

    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Gets all the MTP2 General pegs
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      MTP2_GeneralPegs*   genPegs
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITS_INT 
MTP2_OSS_GetGeneralPegs(MTP2_GeneralPegs* genPegs)
{
    if (genPegs == NULL)
        return ITS_ENOMEM;

    genPegs->getDataFailed      = PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_GET_DATA_FAILED);
    genPegs->sendDataFailed     = PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_SEND_DATA_FAILED);
    genPegs->localProcDown      = PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_LOCAL_PROC_DOWN);
    genPegs->localProcUp        = PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_LOCAL_PROC_UP);
    genPegs->remoteProcDown     = PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_REMOTE_PROC_DOWN);
    genPegs->remoteProcUp       = PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_REMOTE_PROC_UP);
    genPegs->statInd            = PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_STAT_IND);
    genPegs->suermExpiry        = PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_SUERM_EXPIRY);
    genPegs->incorrectFibBsn    = PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_INCORRECT_FIB_BSN);
    genPegs->congDetected       = PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_CONG_DETECTED);
    genPegs->congRecovered      = PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_CONG_RECOVERED);
    genPegs->msuTx              = PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_MSU_TX);
    genPegs->msuRx              = PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_MSU_RX);
    genPegs->t2Expired          = PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_T2_EXPIRED);
    genPegs->t6Expired          = PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_T6_EXPIRED);
    genPegs->t7Expired          = PEG_GetPeg(NMS_MTP2_Pegs, PEG_MTP2_T7_EXPIRED);

    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Clears the specified or all MTP2 General pegs
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      MTP2_GeneralPegs*   genPegs
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITS_INT 
MTP2_OSS_ClearGeneralPeg(ITS_UINT pegId)
{
    if (pegId == MTP2_ALL_PEGS)
    {
        PEG_ClearBlock(NMS_MTP2_Pegs);
    }
    else
    {
        if (pegId >= PEG_NMS_MTP2_NUM_GLOBAL_PEGS)
        {
            MTP2_ERROR(("Peg Id %d not found\n", pegId));
            return ITS_ENOTFOUND;
        }
        else
        {
            PEG_ClearPeg(NMS_MTP2_Pegs, pegId);
        }
    }

    MTP2_DEBUG(("Peg(s) cleared\n"));
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Gets all the MTP2 Link pegs for the specified link
 *
 *  Input Parameters:
 *      ITS_OCTET       linkSet
 *      ITS_OCTET       linkCode
 *
 *  Output Parameters:
 *      MTP2_LinkPegs*  linkPegs
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITS_INT 
MTP2_OSS_GetLinkPegs(ITS_OCTET linkSet, ITS_OCTET linkCode, MTP2_LinkPegs* linkPegs)
{
    ITS_OCTET i;
    SS7_LinkPtr ln;
    MTP2_STATUS ret;
    MTP2LinkStats linkStats;
    ITS_SHORT linkNum;
    TRANSPORT_Control *tc;
    SS7TRAN_Manager *ss7;
    ITS_SS7_CONTEXT *context;
    VENDOR_Instance *inst;

    if (linkPegs == NULL)
        return ITS_ENOMEM;

    if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
    {
        MTP2_ERROR(("Link %d not found in Linkset %d\n", linkCode, linkSet));
        return ITS_ELINKNOTFOUND;
    }

    tc = TRANSPORT_FindTransport(ln->id);
    if (tc == NULL)
    {
        MTP2_ERROR(("Transport %d not found\n", ln->id));
        return ITS_ENOTFOUND;
    }

    ss7 = (SS7TRAN_Manager *)tc;
    inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);
    context = (ITS_SS7_CONTEXT *)inst;

    ret = Mtp2MgmtInit(context->boardNum, context->srcEnt, context->srcInst);

    if (ret == MTP2_SUCCESS)
    {
        linkNum = 0;
        for (i = 0; i < context->numLinkCodes; i++)
        {
            if (context->dataLink[i].linkCode == (ITS_OCTET)linkCode)
            {
                linkNum = context->dataLink[i].linkPort;
                break;
            }
        }

        ret = Mtp2LinkStats(context->boardNum, linkNum, &linkStats, ITS_FALSE);

        if (ret == MTP2_SUCCESS)
        {
            linkPegs->linkFailure       = linkStats.slFailAll;
            linkPegs->suermExpiry       = linkStats.slFailErr;
            linkPegs->incorrectFibBsn   = linkStats.slFailAb;
            linkPegs->t6Expired         = linkStats.slFailCong;
            linkPegs->t7Expired         = linkStats.slFailAck;
            linkPegs->provingFailed     = linkStats.slFailAlign;
            linkPegs->errSU             = linkStats.slNSUErr;
            linkPegs->negAck            = linkStats.slNegAck;
            linkPegs->msuTx             = linkStats.mTx;
            linkPegs->msuRx             = linkStats.mRx;
            linkPegs->sifSioOctetRx     = linkStats.nSifSioTx;
            linkPegs->sifSioOctetTx     = linkStats.nSifSioRx;
            linkPegs->octetRtx          = linkStats.nRetrans;

            return ITS_SUCCESS;
        }
        else
        {
            MTP2_ERROR(("NMS command failed\n", ln->id));
            return ITS_ESENDFAIL;
        }
    }
    else
    {
        MTP2_ERROR(("NMS command failed\n", ln->id));
        return ITS_ESENDFAIL;
    }
}

/****************************************************************************
 *  Purpose:
 *      Clears all the MTP2 Link pegs for the specified link
 *
 *  Input Parameters:
 *      ITS_OCTET       linkSet
 *      ITS_OCTET       linkCode
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITS_INT 
MTP2_OSS_ClearLinkPegs(ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    ITS_OCTET i;
    SS7_LinkPtr ln;
    MTP2_STATUS ret;
    MTP2LinkStats linkStats;
    ITS_SHORT linkNum;
    TRANSPORT_Control *tc;
    SS7TRAN_Manager *ss7;
    ITS_SS7_CONTEXT *context;
    VENDOR_Instance *inst;

    if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
    {
        MTP2_ERROR(("Link %d not found in Linkset %d\n", linkCode, linkSet));
        return ITS_ELINKNOTFOUND;
    }

    tc = TRANSPORT_FindTransport(ln->id);
    if (tc == NULL)
    {
        MTP2_ERROR(("Transport %d not found\n", ln->id));
        return ITS_ENOTFOUND;
    }

    ss7 = (SS7TRAN_Manager *)tc;
    inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);
    context = (ITS_SS7_CONTEXT *)inst;

    ret =  Mtp2MgmtInit(context->boardNum, context->srcEnt, context->srcInst);
    if (ret == MTP2_SUCCESS)
    {
        linkNum = 0;
        for (i = 0; i < context->numLinkCodes; i++)
        {
            if (context->dataLink[i].linkCode == (ITS_OCTET)linkCode)
            {
                linkNum = context->dataLink[i].linkPort;
                break;
            }
        }

        ret = Mtp2LinkStats(context->boardNum, linkNum, &linkStats, 1);
        if (ret == MTP2_SUCCESS)
        {
            MTP2_DEBUG(("Pegs cleared for linkset %d linkcode %d\n", linkSet, linkCode));
            return ITS_SUCCESS;
        }
        else
        {
            MTP2_ERROR(("NMS command failed\n", ln->id));
            return ITS_ESENDFAIL;
        }
    }
    else
    {
        MTP2_ERROR(("NMS command failed\n", ln->id));
        return ITS_ESENDFAIL;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Commiting the configuration in the XML file.
 *
 *  Input Parameters:
 *      FILE* fp - File Pointer to commit.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name        Date        Reference      Description
 * -----------------------------------------------------------------------------
 * Mani        05-05-2005  BugId:1793
 *
 *  See Also:
 ****************************************************************************/

int 
NMSCommit(FILE* fp)
{
    fprintf(fp, "\t\t<NMS-MTP2>\n");
    
    if (MTP2_NMS_TraceData != NULL)
    {
        fprintf(fp, "\t\t\t<VendorTrace>\n");
        if (TRACE_IsLevelOn(MTP2_NMS_TraceData,
            MTP2_TRACE_CRITICAL))
        {
            if (TRACE_IsOutputOn(MTP2_NMS_TraceData,
                MTP2_TRACE_CRITICAL, 0))
            {
                fprintf(fp, "\t\t\t\t<Critical output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(MTP2_NMS_TraceData,
                MTP2_TRACE_CRITICAL, 1))
            {
                fprintf(fp, "\t\t\t\t<Critical output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(MTP2_NMS_TraceData,
                MTP2_TRACE_CRITICAL, 2))
            {
                fprintf(fp, "\t\t\t\t<Critical output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(MTP2_NMS_TraceData,
            MTP2_TRACE_ERROR))
        {
            if (TRACE_IsOutputOn(MTP2_NMS_TraceData,
                MTP2_TRACE_ERROR, 0))
            {
                fprintf(fp, "\t\t\t\t<Error output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(MTP2_NMS_TraceData,
                MTP2_TRACE_ERROR, 1))
            {
                fprintf(fp, "\t\t\t\t<Error output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(MTP2_NMS_TraceData,
                MTP2_TRACE_ERROR, 2))
            {
                fprintf(fp, "\t\t\t\t<Error output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(MTP2_NMS_TraceData,
            MTP2_TRACE_WARNING))
        {
            if (TRACE_IsOutputOn(MTP2_NMS_TraceData,
                MTP2_TRACE_WARNING, 0))
            {
                fprintf(fp, "\t\t\t\t<Warning output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(MTP2_NMS_TraceData,
                MTP2_TRACE_WARNING, 1))
            {
                fprintf(fp, "\t\t\t\t<Warning output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(MTP2_NMS_TraceData,
                MTP2_TRACE_WARNING, 2))
            {
                fprintf(fp, "\t\t\t\t<Warning output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(MTP2_NMS_TraceData,
            MTP2_TRACE_DEBUG))
        {
            if (TRACE_IsOutputOn(MTP2_NMS_TraceData,
                MTP2_TRACE_DEBUG, 0))
            {
                fprintf(fp, "\t\t\t\t<Debug output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(MTP2_NMS_TraceData,
                MTP2_TRACE_DEBUG, 1))
            {
                fprintf(fp, "\t\t\t\t<Debug output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(MTP2_NMS_TraceData,
                MTP2_TRACE_DEBUG, 2))
            {
                fprintf(fp, "\t\t\t\t<Debug output = \"syslog\" />\n");
            }
        }
        fprintf(fp, "\t\t\t</VendorTrace>\n");
    }
    
    fprintf(fp, "\t\t</NMS-MTP2>\n\n");

    return ITS_SUCCESS;
}

#endif /* defined(INCLUDE_MTP2) */
