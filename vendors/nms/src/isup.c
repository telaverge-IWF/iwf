/****************************************************************************
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
 *  ID: $Id: isup.c,v 9.1 2005/03/23 12:56:15 cvsadmin Exp $
 * LOG: $Log: isup.c,v $
 * LOG: Revision 9.1  2005/03/23 12:56:15  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:55:38  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:11:03  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.3  2002/05/20 16:30:38  sjaddu
 * LOG: Merge from PR6.
 * LOG:
 * LOG: Revision 6.2  2002/05/16 15:51:09  hcho
 * LOG: Modifications for v3_6 build.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:15:00  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.6.2.2  2002/05/09 15:12:58  hcho
 * LOG: Integrate v3_6 with vframe.
 * LOG:
 * LOG: Revision 5.6.2.1  2002/04/18 19:59:23  sjaddu
 * LOG: NMS 3.8 changes in PR6
 * LOG:
 * LOG: Revision 5.6  2001/12/17 21:09:22  mmiers
 * LOG: Finish the vendor framework.  Works with NMS MTP2.
 * LOG:
 * LOG: Revision 5.5  2001/12/15 01:19:50  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.4  2001/11/16 23:37:40  mmiers
 * LOG: Today's round of testing.
 * LOG:
 * LOG: Revision 5.3  2001/10/05 22:59:42  mmiers
 * LOG: NMS MTP2 API is taking shape.
 * LOG:
 * LOG: Revision 5.2  2001/09/05 20:35:48  mmiers
 * LOG: Consolidate the NMS libraries.  Only the root library so far.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:42  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.3  2001/08/16 19:13:07  hcho
 * LOG: Backported from PR4 for not using ISUP.
 * LOG:
 * LOG: Revision 1.23.2.3  2001/08/16 17:46:48  hcho
 * LOG: Some version mess up.
 * LOG:
 * LOG: Revision 1.23.2.2  2001/08/16 16:51:13  hcho
 * LOG: Add stubs for not using ISUP.
 * LOG:
 * LOG: Revision 1.23  2001/05/04 16:18:01  hcho
 * LOG: Put ITS_EVENT_TERM back and modify service array.
 * LOG:
 * LOG: Revision 1.22  2001/05/04 15:46:54  hcho
 * LOG: Modified ISUP binding sequence.
 * LOG:
 * LOG: Revision 1.21  2001/02/28 15:49:54  hxing
 * LOG: Test in progress
 * LOG:
 * LOG: Revision 1.20  2001/02/14 00:53:05  hxing
 * LOG: Problem with ITS_SS7_HANDLE
 * LOG:
 * LOG: Revision 1.19  2001/02/08 23:30:57  hxing
 * LOG: Debug in solaris for isup integration
 * LOG:
 * LOG: Revision 1.18  2001/02/06 21:09:36  hxing
 * LOG: Work around ctaInitialize
 * LOG:
 * LOG: Revision 1.17  2001/02/06 00:14:57  hxing
 * LOG: Remove warnings
 * LOG:
 * LOG: Revision 1.16  2001/01/18 22:30:18  hxing
 * LOG: change ComputeMSize to ISUP_ComputeMSize
 * LOG:
 * LOG: Revision 1.15  2000/12/20 16:38:33  hxing
 * LOG: Add one more entry to the contexg struct
 * LOG:
 * LOG: Revision 1.14  2000/12/12 23:49:21  hxing
 * LOG: Testing isup with mtp3
 * LOG:
 * LOG: Revision 1.13  2000/12/12 16:49:09  hxing
 * LOG: testing
 * LOG:
 * LOG: Revision 1.12  2000/12/11 22:39:41  hxing
 * LOG: Debugging
 * LOG:
 * LOG: Revision 1.11  2000/12/05 21:19:25  hxing
 * LOG: Non-blocking wait for event
 * LOG:
 * LOG: Revision 1.10  2000/12/05 17:38:05  hxing
 * LOG: isup integration change
 * LOG:
 * LOG: Revision 1.9  2000/11/13 23:14:21  mmiers
 * LOG: Try to recover the repository
 * LOG:
 * LOG: Revision 1.9  2000/10/17 14:56:38  labuser
 * LOG:
 * LOG: Debug in solaris
 * LOG:
 * LOG: Revision 1.8  2000/10/03 23:53:14  labuser
 * LOG:
 * LOG: Debugging in Solaris
 * LOG:
 * LOG: Revision 1.7  2000/10/03 20:27:53  hxing
 * LOG: Debugging in Solaris
 * LOG:
 * LOG: Revision 1.6  2000/10/02 22:37:51  hxing
 * LOG: Work in solaris
 * LOG:
 * LOG: Revision 1.5  2000/10/02 14:37:29  hxing
 * LOG: work in solaris
 * LOG:
 * LOG: Revision 1.4  2000/09/21 22:49:28  hxing
 * LOG: work in progress
 * LOG:
 * LOG: Revision 1.3  2000/09/20 22:58:45  hxing
 * LOG: Work in progress
 * LOG:
 * LOG: Revision 1.2  2000/09/18 15:32:53  hxing
 * LOG: Work in progress
 * LOG:
 * LOG: Revision 1.1  2000/09/08 21:57:35  hxing
 * LOG: Add project for nms (version 3.5) vendor
 * LOG:
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

#include <its_intern.h>

#if defined(INCLUDE_ISUP)

#include <its_mlist.h>

#if defined (UNIX)
#include <unistd.h>
#elif defined (WIN32)
#include <windows.h>
#include <winbase.h>
#include <io.h>
#include <fcntl.h>
#endif


/*
 * The maximum number of circuits to be managed by the ISUP layer
 */
#define MAX_ISUP_CIRCUITS     65535

/* number of isup services */
#if defined(INCLUDE_VMI)
#define num_isupServices 2
#else
#define num_isupServices 1
#endif

/*
 * spInstId
 */
#define SP_INST_ID_ZERO     0
#define SP_INST_ID_NULL     0xFFFFFFFFU

/*
 * The array of spInstIds associated with a call.
 * It is indexed by the suInstId
 */
static U32 its_spInstIds[MAX_ISUP_CIRCUITS];

#if defined(INCLUDE_VMI)
extern ITS_BOOLEAN isCtaInitialized;
#else
ITS_BOOLEAN isCtaInitialized;
#endif

extern int nms_debug;
extern int nms_errno;

int 
NMS_ISUP_EncodeMTP3(ITS_ISUP_IE *ies, int ieCount, ITS_OCTET msgType,
                ITS_EVENT *event, ITS_HDR *hdr, ISUP_MSG_DESC* desc);

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Initialize the NMS board interface.
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
 *      If ISUP is successfully initialized, ITS_SUCCESS is returned.
 *      Any other return value indicates an initialization error.
 ****************************************************************************/
int
NMSInitializeISUP(ITS_SS7_HANDLE handl)
{
    DWORD               retval;
    CTA_EVENT           ctaEvent;
    ITS_SS7_CONTEXT     *context = (ITS_SS7_CONTEXT *)handl;
    CTAQUEUEHD          queueHd = 0;
    CTAHD               ctaHd = NULL_CTAHD;
    CTA_INIT_PARMS      isupInitparms = {0};

    memset(its_spInstIds, 0xFFU, sizeof(U32) * MAX_ISUP_CIRCUITS);    
    
    /* bind this application as a user of the ISUP layer */
    isupInitparms.size = sizeof(CTA_INIT_PARMS);
    isupInitparms.traceflags = CTA_TRACE_ON_ERROR;
    //isupInitparms.parmflags = CTA_PARM_MGMT_SHARED_IF_PRESENT;
    isupInitparms.ctacompatlevel = CTA_COMPATLEVEL;

    if (!isCtaInitialized)
    {
        retval = ctaInitialize(NULL,0, &isupInitparms);
    
        if (retval != SUCCESS)
        {
            printf( "Error : (%d) error returned in (%s) call.\n", 
                     (int)retval, "ctaInitialize" );
    
            return (ITS_ENOPROXY);
        }
    }

    /* Create Queue: (2nd parm 0: num of manager services) */
    retval = ctaCreateQueue(NULL, 0, &queueHd );

    if ( retval != SUCCESS )
    {
        printf( "Error : (%d) error returned in (%s) call.\n", 
                 (int)retval, "ctaCreateQueue" );

        return (ITS_ENOPROXY);
    }

    context->isQueueInitialized = ITS_TRUE;

    /* Open ctaHd on queueHd  */
    retval = ctaCreateContext(queueHd, context->isupSapid, NULL, &ctaHd );

    if ( retval != SUCCESS )
    {
        printf( "Error : (%d) error returned in (%s) call.\n", 
                 (int)retval, "ctaCreateContext" );

        return (ITS_ENOPROXY);
    }

    /* save ctaHd and queueHd for later use */
    context->isupCtaHd = ctaHd;

#if NMS_VERSION < 3080

    context->isupCtaQueueHd = queueHd;

#else

    context->mtp3CtaQueueHd = queueHd;

#endif 

    printf("MgmtSrcEnt = %d\n", context->isupMgmtSrcEnt);

    /* open management service */
    if ((retval = isupInitMgmtAPI(context->boardNum,
                  (U8)(context->isupMgmtSrcEnt) )) != SUCCESS )
    {
        printf("Error: (%d) error returned in isupInitMgmtAPI\n", (int)retval);

        return (!ITS_SUCCESS);
    }

    NMSOpenISUP(handl);

    VMI_SetSS7Handle(handl);

    if (nms_debug)
    {
        printf("initialize: ctaHd = 0x%08X, queueHd = 0x%08X\n", 
                (int) ctaHd, (int) queueHd);
    } 

    return (ITS_SUCCESS);
}

int
NMSOpenISUP(ITS_SS7_HANDLE handl)
{
    ITS_SS7_CONTEXT     *context = (ITS_SS7_CONTEXT *)handl;
    DWORD               retval;
    CTAQUEUEHD          queueHd = 0;
    CTAHD               ctaHd = NULL_CTAHD;
    CTA_EVENT           ctaEvent;
    static int          initialized = 1;

#if defined(INCLUDE_VMI)
    CTA_SERVICE_DESC isupOpenSvcLst[num_isupServices] = 
    {{{"ISUP", "ISUPMGR"},{0},{0},{0}},{{"HMI","HMIMGR"},{0},{0},{0}}};    

    char *isupCloseSvcLst[num_isupServices] = { "ISUP", "HMI" };
#else
    CTA_SERVICE_DESC isupOpenSvcLst[num_isupServices] =
        {{{"ISUP", "ISUPMGR" }, {0}, {0}, {0}} };
    char *isupCloseSvcLst[num_isupServices] = { "ISUP" };
#endif

    ctaHd = context->isupCtaHd;

#if NMS_VERSION < 3080

    queueHd = context->isupCtaQueueHd;

#else

    queueHd = context->mtp3CtaQueueHd;

#endif

    /* Not to close service at first time */ 
    if (!initialized)
    {
        /* Close service and destroy context. */
        retval = ctaCloseServices(ctaHd, isupCloseSvcLst, num_isupServices);
    
        if (retval != SUCCESS)
        {
            printf("Error : (%d) error returned in (%s) call.\n",
                    (int)retval, "ctaCloseServices");
    
            return (ITS_ENOPROXY);
        }
    
        printf("CtaCloseServices succeed\n");

        /* Wait for service close to complete. */
        retval = ctaWaitEvent(queueHd, &ctaEvent, CTA_WAIT_FOREVER);
    
        if (retval != SUCCESS)
        {
            printf("Error : (%d) error returned in (%s) call.\n",
                    (int)retval, "ctaWaitEvent");
    
            return (ITS_ENOPROXY);
        }
    
        if ((ctaEvent.id != CTAEVN_CLOSE_SERVICES_DONE)  ||
            (ctaEvent.value != CTA_REASON_FINISHED))
        {
            printf("Error : (%d) error returned in (%s) call.\n",
                    (int)retval, "ctaWaitEvent");
    
            return (ITS_ENOPROXY);
        }

        printf("CtaWaitEvent : CtaCloseServices succeed\n");
    }

    isupOpenSvcLst[0].svcargs.args[0] = context->boardNum; /* board number */
    isupOpenSvcLst[0].svcargs.args[1] = context->srcInst;  /* srcInst */
    isupOpenSvcLst[0].svcargs.args[2] = context->isupSrcEnt;   /* dprChan */
    isupOpenSvcLst[0].svcargs.args[3] = 1;     /* AutoBind? (yes=1, no= 0) */
    isupOpenSvcLst[0].svcargs.args[4] = context->isupSapid;    /* spId */
    isupOpenSvcLst[0].svcargs.args[5] = context->servUserId;  /* suId */    

    retval = ctaOpenServices(ctaHd, &isupOpenSvcLst[0], num_isupServices);
    if (retval != SUCCESS)
    {
        printf("Error : (%d) error returned in (%s) call.\n", 
               (int)retval, "ctaOpenServices");

        return (ITS_ENOPROXY);
    }

    printf("CtaOpenServices succeed\n");

    /* Wait for service open to complete. */
    retval = ctaWaitEvent(queueHd, &ctaEvent, CTA_WAIT_FOREVER);
    if (retval != SUCCESS)
    {
        printf("Error : (%d) error returned in (%s) call.\n", 
                (int)retval, "ctaWaitEvent");

        return (ITS_ENOPROXY);
    }

    if ((ctaEvent.id != CTAEVN_OPEN_SERVICES_DONE) ||
        (ctaEvent.value != CTA_REASON_FINISHED))
    {
        printf("Error : (%d) error returned in (%s) call.\n", 
                (int)retval, "ctaWaitEvent");

        return (ITS_ENOPROXY);
    }

    printf("CtaWaitEvent : CtaOpenServices succeed\n");

    initialized = 0;

    return retval;
}

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
 *      If ISUP is successfully terminated, ITS_SUCCESS is returned.
 *      Any other return value indicates an termination error..
 ****************************************************************************/
int
NMSTermISUP(ITS_SS7_HANDLE handl)
{   
    DWORD               retval;
    ITS_SS7_CONTEXT     *context = (ITS_SS7_CONTEXT *)handl;
    CTA_EVENT           ctaEvent;
    CTAQUEUEHD          queueHd = 0;

#if defined(INCLUDE_VMI)   
    char *isupCloseSvcLst[num_isupServices] = { "ISUP" , "HMI" };
#else
    char *isupCloseSvcLst[num_isupServices] = { "ISUP" };
#endif

#if NMS_VERSION < 3080

    queueHd = context->isupCtaQueueHd;

#else

    queueHd = context->mtp3CtaQueueHd;

#endif

    /*char *isupCloseSvcLst[] = { "ISUP" };*/

#if NMS_VERSION < 3080

    queueHd = context->isupCtaQueueHd;

#else

    queueHd = context->mtp3CtaQueueHd;

#endif

    /*
    *   Close service and destroy context.
    */
    retval = ctaCloseServices( context->isupCtaHd,isupCloseSvcLst,num_isupServices );

    if ( retval != SUCCESS )
    {
        printf( "Error : (%d) error returned in (%s) call.\n",(int)retval, "ctaCloseServices" );

        return (ITS_ENOPROXY);
    }

    /* Wait for service close to complete. */
    retval = ctaWaitEvent(queueHd, 
                          &ctaEvent, 
                          CTA_WAIT_FOREVER);

    if ( retval != SUCCESS )
    {
        printf( "Error : (%d) error returned in (%s) call.\n", 
                 (int)retval, "ctaWaitEvent" );

        return (ITS_ENOPROXY);
    }
    if (( ctaEvent.id != CTAEVN_CLOSE_SERVICES_DONE )  || 
        ( ctaEvent.value != CTA_REASON_FINISHED ))
    {
        printf( "Error : (%d) error returned in (%s) call.\n", 
                 (int)retval, "ctaWaitEvent" );

        return (ITS_ENOPROXY);
    }

    retval = ctaDestroyContext( context->isupCtaHd );

    if ( retval != SUCCESS )
    {
        printf( "Error : (%d) error returned in (%s) call.\n", 
                 (int)retval, "ctaDestroyContext" );

        return (ITS_ENOPROXY);
    }

    /* Wait for context close to complete. */
    retval = ctaWaitEvent( queueHd, 
                           &ctaEvent, 
                           CTA_WAIT_FOREVER );

    if ( retval != SUCCESS )
    {
        printf( "Error : (%d) error returned in (%s) call.\n", 
                 (int)retval, "ctaWaitEvent" );

        return (ITS_ENOPROXY);
    }
    if (( ctaEvent.id != CTAEVN_DESTROY_CONTEXT_DONE ) || 
        ( ctaEvent.value != CTA_REASON_FINISHED ))
    {
        printf( "Error : (%d) error returned in (%s) call.\n", 
                 (int)retval, "ctaWaitEvent" );

        return (ITS_ENOPROXY);
    }

    retval = ctaDestroyQueue(queueHd);

    if ( retval != SUCCESS )
    {
        printf( "Error : (%d) error returned in (%s) call.\n", 
                 (int)retval, "ctaDestroyQueue" );

        return (ITS_ENOPROXY);
    }
    
    /* term management service */
    if ((retval = isupTermMgmtAPI(context->boardNum)) != SUCCESS )
    {
        printf("Error: (%d) error returned in isupTermMgmtAPI\n", (int)retval);
    
        return (!ITS_SUCCESS);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function retrieve an ISUP msg from NMS
 *
 *  Input Parameters:
 *      handle: ITS Handle.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If ISUP is successfully retrieved, ITS_SUCCESS is returned.
 *      Any other return value indicates an receiving failure.
 ****************************************************************************/
int
NMSRetrieveISUPMessage(ITS_SS7_HANDLE handle)
{
    SiAllSdus           msg;
    IsupRcvInfoBlk      infoBlk;
    ITS_SS7_CONTEXT     *context = (ITS_SS7_CONTEXT *)handle;    
    ITS_EVENT           itsEvent;
    ITS_ISUP_IE         ies[ITS_MAX_ISUP_IES];
    ITS_HDR             itsHeader;
    int                 ieCount = 0;
    ITS_OCTET           msgType = 0;
    ISUP_MSG_DESC       msgDesc;
    MTP3_PAUSE_RESUME   mtp3PauseResume;
    MTP3_HEADER         mtp3Hdr;
    IsupCircCfg         isupCircCfg;
    IsupGenParms        isupGenParm;
    S16                 status;
    CTA_EVENT           ctaEvent;
    DWORD               retval;
    ITS_UINT            opc, dpc;

    memset(&msg, 0, sizeof(msg));
    memset(ies, 0, sizeof(ITS_ISUP_IE) * ITS_MAX_ISUP_IES);
    memset((char *)&infoBlk, 0, sizeof(IsupRcvInfoBlk));
    memset(&ctaEvent, 0, sizeof(CTA_EVENT));

#if NMS_VERSION < 3080

    /* ctaWaitEvent is called in v3_8 WaitForIndication. For v3_6 and down,
     * user must call ctaWaitEvent here. */

    /* cta wait event */    
    retval = ctaWaitEvent(context->isupCtaQueueHd, &ctaEvent, CTA_WAIT_FOREVER);

    if ( retval != SUCCESS)
    {
        printf( "Error : (%d) error returned in (%s) call.\n",
                 (int)retval, "ctaWaitEvent" );

        return (ITS_ENOPROXY);
    }

    if (nms_debug)
    {
        PrintCtaEvent(&ctaEvent);
    }

    switch ( ctaEvent.id )
    {
    case ISUPEVN_DATA:
        /* an ISUP event has occured, call ISUPRetrieveMessage()
         * to get the event */
        if (ISUPRetrieveMessage(context->isupCtaHd, &msg, &infoBlk, 1)
            != ISUP_SUCCESS)
        {
            return (ITS_ENOMSG);
        }
        break;

    default:
        printf("isupCtaHd = 0x%08X\n", context->isupCtaHd);

        printf("CTAHD(0x%08X) : Unhandled event id (0x%x) during wait.\n",
                (int)ctaEvent.ctahd, (int)ctaEvent.id );

        return !ITS_SUCCESS;
    }

#else

    /* an ISUP event has occured, call ISUPRetrieveMessage()
     * to get the event */
    if (ISUPRetrieveMessage(context->isupCtaHd, &msg, &infoBlk, 1)
        != ISUP_SUCCESS)
    {
        return (ITS_ENOMSG);
    }

#endif

    if (nms_debug)
    {
        printf("\nNMSRetrieveISUPMessage: receive message from NMS stack.\n");    
        printf("indType = %d\n", (int) infoBlk.indType);
        printf("evntType = %d\n", (int) infoBlk.evntType);
        printf("suId = %d\n", (int) infoBlk.suId);
        printf("suInstId = %d\n", (int) infoBlk.suInstId);
        printf("spInstId = %d\n", (int) infoBlk.spInstId);
        printf("circuit = %d\n", (int) infoBlk.circuit);
        printf("globalFlg = %d\n", (int) infoBlk.globalFlg);
        printf("srcBoard = %d\n", (int) infoBlk.srcBoard);
    }
    
    /*
     * check what kind of message received
     * Since the eventType is not enough to determine the msgType, we check the 
     * indType first then the eventType
     */
    switch (infoBlk.indType)
    {
    /* event connect confirm: 
     * two messages possible: Answer(ANM)or Connect(CON)(CCITT only)
     * These two msgs are almost the same. We choose ANM since it is more common
     */
    /* ISUP Connect Event SiConEvnt */
    case EVTSITCONCFM: 
        msgType = ISUP_MSG_ANM;
        msgDesc = ISUP_ANM_Desc;
        ieCount = ReceiveNmsANM(&msg, ies);
        break;

    /* ISUP Connect Event SiConEvnt*/
    case EVTSITCONIND: /*Initial Address (IAM)*/
        msgType = ISUP_MSG_IAM;
        msgDesc = ISUP_IAM_Desc;
        ieCount = ReceiveNmsIAM(&msg, ies);
        break;

    /* Connect Status Event SiCnStEvnt*/    
    case EVTSITCNSTIND:/* event connect status indicator*/
    {
        switch (infoBlk.evntType)
        {
        case ADDRCMPLT: /* Address complete (ACM) */
            msgType = ISUP_MSG_ACM;
            msgDesc = ISUP_ACM_Desc;
            ieCount = ReceiveNmsACM(&msg, ies);
            break;

        case PROGRESS: /* Call progress (CPG) */
            msgType = ISUP_MSG_CPG;
            msgDesc = ISUP_CPG_Desc;
            ieCount = ReceiveNmsCPG(&msg, ies);
            break;

        case INFORMATION: /* Information (INF) */
            msgType = ISUP_MSG_INF;
            msgDesc = ISUP_INF_Desc;
            ieCount = ReceiveNmsINF(&msg, ies);
            break;

        case INFORMATREQ: /* Information Request (INR) */
            msgType = ISUP_MSG_INR;
            msgDesc = ISUP_INR_Desc;
            ieCount = ReceiveNmsINR(&msg, ies);
            break;

        case FRWDTRSFR: /* Forward transfer (FOT) */
            msgType = ISUP_MSG_FOT;
            msgDesc = ISUP_FOT_Desc;
            ieCount = ReceiveNmsFOT(&msg, ies);
            break;

#if defined ( CCITT )
        case SUBSADDR: /* Subsequent address (SAM) (CCITT only) */
            msgType = ISUP_MSG_SAM;
            msgDesc = ISUP_SAM_Desc;
            ieCount = ReceiveNmsSAM(&msg, ies);
            break;

        case IDENTREQ: /* Identification request (IDR) (CCITT only) */
            msgType = ISUP_MSG_IDR;
            msgDesc = ISUP_IDR_Desc;
            ieCount = ReceiveNmsIDR(&msg, ies);
            break;

        case IDENTRSP: /* Identification response (IRS) (CCITT only) */
            msgType = ISUP_MSG_IRS;
            msgDesc = ISUP_IRS_Desc;
            ieCount = ReceiveNmsIRS(&msg, ies);
            break;

        case NETRESMGT: /* Network Resource Mgngmnt (NRM) (CCITT only) */
            msgType = ISUP_MSG_NRM;
            msgDesc = ISUP_NRM_Desc;
            ieCount = ReceiveNmsNRM(&msg, ies);
            break;
#endif /* CCITT */

#if defined (ANSI)
        case EXIT: /* Exit (EXM) (CCITT only) */
            msgType = ISUP_MSG_EXM;
            msgDesc = ISUP_EXM_Desc;
            ieCount = ReceiveNmsEXM(&msg, ies);
            break;

#endif /* ANSI */

        default: /* unknown msgs or msgs we don't handle */
            if (nms_debug)
            {
                printf("\nReceived ConnectStatusEvent, msgType = %d unknown. Exit\n",
                       infoBlk.evntType);
            }
            return (ITS_ENOMSG);
        }
    }
        break;

    /* event data Indication: 
     * two msgs possible: Pass-along(PAM) or 
     * User-to-user information(USR) (CCITT only)
     */
    /* Information Event SiInfoEvnt */
    case EVTSITDATIND:
        if (msg.m.siInfoEvnt.passAlng.eh.pres == PRESENT)
        {   
            ieCount = ReceiveNmsPAM(&msg, ies);
        }
#if defined (CCITT)
        else if (msg.m.siInfoEvnt.usr2UsrInfo.eh.pres == PRESENT)
        {   
            ieCount = ReceiveNmsUSR(&msg, ies);
        }
#endif /* CCITT */
        break;

    /* Release Event SiRelEvnt */
    case EVTSITRELIND: /* Release (REL) */
        msgType = ISUP_MSG_REL;
        msgDesc = ISUP_REL_Desc;
        ieCount = ReceiveNmsREL(&msg, ies);
        break;

    /* Release Event SiRelEvnt */
    case EVTSITRELCFM: /* Release complete(RLC) */
        msgType = ISUP_MSG_RLC;
        msgDesc = ISUP_RLC_Desc;
        ieCount = ReceiveNmsRLC(&msg, ies);
        break;

    /* resume event SiResmEvnt */
    case EVTSITRESMIND: /* Resume(RES) */
        msgType = ISUP_MSG_RES;
        msgDesc = ISUP_RES_Desc;
        ieCount = ReceiveNmsRES(&msg, ies);
        break;

    /* Status Event SiStaEvnt */    
    case EVTSITSTAIND: /* events for status indication primitives */
    {
        switch (infoBlk.evntType)
        {
        case ERRORIND:   /* ERROR indication from ISUP layer */
            if (msg.m.siStaEvnt.causeDgn.eh.pres && 
                msg.m.siStaEvnt.causeDgn.causeVal.pres)
            {
                printf("ERROR Status, circ=%d, suId=%d, spId=%d, cause=%d\n",
                       (int) infoBlk.circuit, 
                       (int) infoBlk.suInstId, 
                       (int) infoBlk.spInstId,
                       (int) msg.m.siStaEvnt.causeDgn.causeVal.val );
            }
            else
            {
                printf("ERROR Status, circ=%d, suId=%d, spId=%d, no cause\n",
                       (int) infoBlk.circuit, 
                       (int) infoBlk.suInstId, 
                       (int) infoBlk.spInstId );
            }
            return (ITS_ENOMSG);

        case CIRBLKREQ: /* Blocking (BLO) */
            msgType = ISUP_MSG_BLO;
            msgDesc = ISUP_BLO_Desc;
            /* no ies inside this message */
            break;

        case CIRBLKRSP: /* Blocking Ack (BLA) */
            msgType = ISUP_MSG_BLA;
            msgDesc = ISUP_BLA_Desc;
            /* no ies inside this message */
            break;

        case CONTCHK: /* Continuity check request (CCR) */
            msgType = ISUP_MSG_CCR;
            msgDesc = ISUP_CCR_Desc;
            /* no ies inside this message */
            break; 

        case CONFUSION: /* Confusion(CFN) */
            msgType = ISUP_MSG_CFN;
            msgDesc = ISUP_CFN_Desc;
            ieCount = ReceiveNmsCFN(&msg, ies);
            break;

        case CIRGRPBLKREQ: /* Circuit Group Blocking(CGB) */
            msgType = ISUP_MSG_CGB;
            msgDesc = ISUP_CGB_Desc;
            ieCount = ReceiveNmsCGB(&msg, ies);
            break;

        case CIRGRPBLKRSP: /* Circuit Group Blocking Ack (CGBA) */
            msgType = ISUP_MSG_CGBA;
            msgDesc = ISUP_CGBA_Desc;
            ieCount = ReceiveNmsCGB(&msg, ies); /* same as CGB */
            break;

        case CONTREP: /* Continuity (COT) */
            msgType = ISUP_MSG_COT;
            msgDesc = ISUP_COT_Desc;
            ieCount = ReceiveNmsCOT(&msg, ies);
            break;
        
        case CIRGRPQRYRSP: /* Circuit group query response(CQR) */
            msgType = ISUP_MSG_CQR;
            msgDesc = ISUP_CQR_Desc;
            ieCount = ReceiveNmsCQR(&msg, ies);
            break;

        case CIRGRPRESACK: /* Circuit group reset Ack (GRA) */
            msgType = ISUP_MSG_GRA;
            msgDesc = ISUP_GRA_Desc;
            ieCount = ReceiveNmsGRA(&msg, ies);
            break;

        case CIRGRPRESREQ: /* Circuit group reset(GRS) */
            msgType = ISUP_MSG_GRS;
            msgDesc = ISUP_GRS_Desc;
            ieCount = ReceiveNmsGRS(&msg, ies);
            break;

        case CIRGRPUNBLKREQ: /* Circuit group unblocking (CGU) */
            msgType = ISUP_MSG_CGU;
            msgDesc = ISUP_CGU_Desc;
            ieCount = ReceiveNmsCGB(&msg, ies);  /* same as CGB */
            break;

        case CIRGRPUNBLKRSP: /* Circuit group unblocking ack (CGUA) */
            msgType = ISUP_MSG_CGUA;
            msgDesc = ISUP_CGUA_Desc;
            ieCount = ReceiveNmsCGB(&msg, ies);  /* same as CGB */
            break;

#if defined (ANSI)
        case CIRRESERVE: /* Circuit reserve (CRM) */
            msgType = ISUP_MSG_CRM;
            msgDesc = ISUP_CRM_Desc;
            ieCount = ReceiveNmsCRM(&msg, ies);
            break;

        case CIRRESERVEACK: /* Circuit reserve ack (CRA) */
            msgType = ISUP_MSG_CRA;
            msgDesc = ISUP_CRA_Desc;
            /* no ies inside this message */
            break;
#endif /* ANSI */

        case LOOPBCKACK: /* Loopback acknowledge (LPA) */
            msgType = ISUP_MSG_LPA;
            msgDesc = ISUP_LPA_Desc;
            /* no ies inside this message */
            break;

        case CIRRESREQ: /* Reset circuit(RSC) */
            msgType = ISUP_MSG_RSC;
            msgDesc = ISUP_RSC_Desc;
            /* no ies inside this message */
            break;    

        case CIRUNBLKREQ: /* Unblocking (UBL) */
            msgType = ISUP_MSG_UBL;
            msgDesc = ISUP_UBL_Desc;
            /* no ies inside this message */
            break;

        case CIRUNBLKRSP: /* Unblocking ack(UBA) */
            msgType = ISUP_MSG_UBA;
            msgDesc = ISUP_UBA_Desc;
            /* no ies inside this message */
            break;

        case CIRRESREQLOC:/* reset initiated locally by the software */
            if (nms_debug)
            {
                printf("\nReceived StatusEvent: reset initiated locally by "
                       "the software\n");
            }
            return (ITS_ENOMSG);

        case MTPPAUSE:   /* pause received from MTP */
        case MTPRESUME:  /* resume received from MTP */
        {
            if (infoBlk.evntType == MTPPAUSE)
            {
                msgType = MTP3_MSG_PAUSE;
                printf("\nReceived StatusEvent: Pause received from MTP\n");

                return ITS_ENOMSG;
            }
            else
            {
                msgType = MTP3_MSG_RESUME;
                printf("\nReceived StatusEvent: Resume received from MTP\n");
            }

            memset(&mtp3Hdr, 0, sizeof(MTP3_HEADER));
            memset(&mtp3PauseResume, 0, sizeof(MTP3_PAUSE_RESUME));

            /* get the affected pc */
            if ((status = isupGetCircCfg(infoBlk.srcBoard, 
                                         &isupCircCfg, 
                                         infoBlk.circuit)) != ISUP_MGMT_SUCCESS)
            {
                printf( "Board %d Circuit %d Get Configuration Request failed:"
                        " status = %d\n",
                        (int)infoBlk.srcBoard, 
                        (int)infoBlk.circuit, 
                        (int)status );

                return ITS_ENOMSG;
            }
            if (nms_debug)
            {
            /*    printf("affectedPointCode: %d.%d.%d\n", 
                        (int) ((isupCircCfg.dstPointCode >> 16) & 0xff), 
                        (int) ((isupCircCfg.dstPointCode >> 8) & 0xff), 
                        (int) (isupCircCfg.dstPointCode & 0xff));
             */
            }

            MTP3_PC_SET_VALUE(mtp3PauseResume.affected, 
                              (ITS_UINT)isupCircCfg.dstPointCode);
            
            if (MTP3_Encode(&itsEvent, msgType, &mtp3Hdr,
                            (ITS_OCTET *)&mtp3PauseResume, 
                            sizeof(MTP3_PAUSE_RESUME)) != ITS_SUCCESS)
            {
                return ITS_ENOMSG;
            }

            itsEvent.src = ITS_MTP3_SRC;

            return MQUEUE_Enqueue(VENDOR_RCV_Q(context),
                                  &itsEvent, sizeof(ITS_EVENT));
            break;
        }

        case RMTUSRUNAVAIL:  /* remote user unavailable */
            if (nms_debug)
            {
                printf("\nReceived StatusEvent: Remote user unavailable.\n");
            }
            return (ITS_ENOMSG);

        case RMTUSRAVAIL:  /* remote user available */
            if (nms_debug)
            {
                printf("\nReceived StatusEvent: Remote user available.\n");
            }
            return (ITS_ENOMSG);

        case MTPCONGEST:  /* congestion received from MTP */
            if (nms_debug)
            {
                printf("\nReceived StatusEvent:Congestion received from MTP.");
            }
            return (ITS_ENOMSG);

        case MTPSTOPCONGEST:  /* stop congestion received from MTP */
            if (nms_debug)
            {
                printf("\nReceived StatusEvent: Stop congestion received "
                       " from MTP.\n");
            }
            return (ITS_ENOMSG);

        case REATTEMPT: /* reattemp indication */
            if (nms_debug)
            {
                printf("\nReceived StatusEvent: Reattempt.\n");
            }
            return (ITS_ENOMSG);

        case STPCONTIN: /* stop continuity indication */
            if (nms_debug)
            {
                printf("\nReceived StatusEvent: StopContinuityIndication.\n");
            }
            return (ITS_ENOMSG);

        case CIRUNEQPD: /* circuit unequipped indication */
            if (nms_debug)
            {
                printf("Received StatusEvent: CircuitUnequippedIndication.\n");
            }
            return (ITS_ENOMSG);

        case CIRGRPSET: /* circuit group set status */
            if (nms_debug)
            {
                printf("\nReceived StatusEvent: CircuitGroupSetStatus.\n");
            }
            return (ITS_ENOMSG);

        case CIRGRPGET: /* circuit group get status */
            if (nms_debug)
            {
                printf("\nReceived StatusEvent: CircuitGroupGetStatus.\n");
            }
            return (ITS_ENOMSG);

        case MTPBACKUP: /* BACKUP received from MTP */
            if (nms_debug)
            {
                printf("\nReceived StatusEvent: MTPBACKUP.\n");
            }
            return (ITS_ENOMSG);

        case MTPPRIMARY: /* PRIMARY received from MTP */
            if (nms_debug)
            {
                printf("\nReceived StatusEvent: MTPPRIMARY.\n");
            }
            return (ITS_ENOMSG);

        case MTPSTANDALONE: /* STANDALONE received from MTP */
            if (nms_debug)
            {
                printf("\nReceived StatusEvent: MTPSTANDALONE.\n");
            }
            return (ITS_ENOMSG);

        default:
            /* unknown message or messages we don't handle */
            if (nms_debug)
            {
                printf("\nReceived StatusEvent, msgType = %d unknown. Exit\n",
                       infoBlk.evntType);
            }
            return (ITS_ENOMSG);
        }
    }
        break;

    /* facility event SiFacEvnt */    
    case EVTSITFACIND: /* events for general facility request */
    {
        switch (infoBlk.evntType)
        {
#if defined (CCITT)
        case FACILITY: /* Facility (FAC) (CCITT only) */
            msgType = ISUP_MSG_FAC;
            msgDesc = ISUP_FAC_Desc;
            ieCount = ReceiveNmsFAC(&msg, ies);
            break;

        case FACILITYACC: /* Facility accepted (FAA) (CCITT only) */
            msgType = ISUP_MSG_FAA;
            msgDesc = ISUP_FAA_Desc;
            ieCount = ReceiveNmsFAA(&msg, ies);
            break;

        case FACILITYREJ: /* Facility reject(FRJ) (CCITT only) */
            msgType = ISUP_MSG_FRJ;
            msgDesc = ISUP_FRJ_Desc;
            ieCount = ReceiveNmsFRJ(&msg, ies);
            break;

        case FACILITYREQ: /* Facility request (FAR) (CCITT only) */
            msgType = ISUP_MSG_FAR;
            msgDesc = ISUP_FAR_Desc;
            ieCount = ReceiveNmsFAA(&msg, ies); /* same as FAA */
            break;
#endif

        default:
            if (nms_debug)
            {
                printf("\nReceived FacilityEvent, msgType = %d unknown. Exit\n",
                       infoBlk.evntType);
            }
            return (ITS_ENOMSG);
            break;
        }
    }
        break;

    /* suspend event SiSuspEvnt */
    case EVTSITSUSPIND: /* Suspend(SUS) */
        msgType = ISUP_MSG_SUS;
        msgDesc = ISUP_SUS_Desc;
        ieCount = ReceiveNmsSUS(&msg, ies);
        break;

    /* raw event SiRawEvnt */
    case EVTSITRAWIND: /* TODO */
        if (nms_debug)
        {
            printf("\nReceived RawEvent. Exit\n");
        }
        return (ITS_ENOMSG);

    default:
        break;
    } /* switch infoBlk.indType */

    /* initialize itsEvent */
    ITS_EVENT_INIT(&itsEvent, ITS_ISUP_SRC, MTP2_MAX_MSG_SIZE);

    /* populate ITS_HDR part */
    itsHeader.context.cic = (ITS_USHORT)infoBlk.circuit;

    /* 
     * use type to store srcBorad, this is only for the
     * NMS_ISUP_EncodeMTP3 use 
     */
    itsHeader.type = (ITS_USHORT)infoBlk.srcBoard;

    /* set mtp3Hdr */
    MTP3_HDR_SET_SIO(mtp3Hdr, MTP3_SIO_ISUP);

    /* get the dpc */    
    if ((status = isupGetCircCfg((U8)infoBlk.srcBoard, 
                                 &isupCircCfg, 
                                 infoBlk.circuit)) != ISUP_MGMT_SUCCESS)
    {
        printf( "Board %d Circuit %d isupGetCircCfg failed: status = %d\n",
                infoBlk.srcBoard, infoBlk.circuit, status );

        return ITS_ENOMSG;
    }

    /* get the opc */    
    if ( (status = isupGetGenCfg((U8)infoBlk.srcBoard, &isupGenParm))
         != ISUP_MGMT_SUCCESS )
    {
        printf( "Board %d isupGetGenCfg failed: status = %d\n",
                infoBlk.srcBoard, status );

        return ITS_ENOMSG;
    }


    /* set the dpc, opc (U32) */
    opc = isupCircCfg.dstPointCode;
    dpc = isupGenParm.orgPointCode;

    MTP3_RL_SET_OPC_VALUE(mtp3Hdr.label, opc);   
    MTP3_RL_SET_DPC_VALUE(mtp3Hdr.label, dpc);

    ies[ieCount].param_id = ISUP_PRM_ROUTING_LABEL;
    ies[ieCount].param_length = sizeof(MTP3_HEADER);
    memcpy(&ies[ieCount].param_data.routingLabel,
           &mtp3Hdr, sizeof(MTP3_HEADER));
    ieCount++;

    if (NMS_ISUP_EncodeMTP3(ies, ieCount, msgType, &itsEvent, &itsHeader, &msgDesc)
         == ITS_SUCCESS)
    {
        MQUEUE_Enqueue(VENDOR_RCV_Q(context), &itsEvent, sizeof(ITS_EVENT));

        if (nms_debug)
        {
            printf("\nNMS_ISUP_EncodeMTP3 success. ieCount = %d\n", ieCount);
        }
    }
    else
    {
        if (nms_debug)
        {
            printf("\nError NMS_ISUP_EncodeMTP3, msgType = %d", msgType);
        }

        return ITS_ENOMSG;
    }

    ITS_EVENT_TERM(&itsEvent);

    /*
     * Set the spInstId associated with the circuit 
     * I think this should only be done if the received msg is valid
     */
    if (its_spInstIds[infoBlk.circuit] == SP_INST_ID_NULL)
    {
        its_spInstIds[infoBlk.circuit] = infoBlk.spInstId;
    }

    /* If received msg is RLC or RSC, reset spInstId to null after the clear
     * of the connection 
     */
    if ( (infoBlk.indType == EVTSITRELCFM) ||
         (infoBlk.indType == EVTSITSTAIND && infoBlk.evntType == CIRRESREQ) )
    {
        its_spInstIds[infoBlk.circuit] = SP_INST_ID_NULL;
    }
   
    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function builds and sends a generic ISUP message.
 *
 *  Input Parameters:
 *      handl:  the transport handle.
 *      type:   the message type of the ISUP message.
 *      hdr:    the context for this message.
 *      ies:    the information elements that make up the ISUP message
 *      ieCount:the number of information elements.
 *      desc:   message decription of the ISUP message..
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the ISUP message is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates a sending failure.
 ****************************************************************************/
int
NMSSendISUPEvent(ITS_SS7_HANDLE handl, ITS_OCTET type, ITS_HDR* hdr,
                 ITS_ISUP_IE* ies, int ieCount, ISUP_MSG_DESC* desc)
{
    ITS_EVENT         itsEvent;
    int               i;
    SiConEvnt         conEvent;
    SiCnStEvnt        conStatusEvent;
    SiInfoEvnt        infoEvent;
    SiRelEvnt         releaseEvent;
    SiResmEvnt        resumeEvent;
    SiStaEvnt         statusEvent;
#if defined (CCITT)
    SiFacEvnt         facilityEvent;
#endif    
    SiSuspEvnt        suspendEvent;    
    DWORD             status = 0;
    ITS_SS7_CONTEXT*  context = (ITS_SS7_CONTEXT *)handl;

    /* TODO: Get the correct values for suInstId, spInstId, circuit
     * For now: let the user pick the cic for the message, use the suInstId = 0 
     *          store the spInstId from NMS stack.
     *          Use cic and spInstId to identify a call 
     */
    CTAHD             ctaHd = context->isupCtaHd;    
    SuId              suId = context->isupSapid;   
    SiInstId          suInstId = 0;
    SiInstId          spInstId;
    CirId             circuit = hdr->context.cic; 
    Bool              cirSelFlg = FALSE; /* must be true if use circuit above*/
    Bool              globalFlg = FALSE; /* True if global request; 
                                          * False if circuit-specific request.*/
                                               
    /* if this is the first message in the connection, spInstId should be 0,
     * otherwise use the stored spInstId 
     */
    if (its_spInstIds[circuit] == SP_INST_ID_NULL)
    {
        spInstId = SP_INST_ID_ZERO;
    }
    else
    {
        spInstId = its_spInstIds[circuit];
    }    

    /*
     * Ensure this ISUP message is valid. (all F & V parms are present)
     */
    if (ISUP_MessageSanityCheck(type, ies, ieCount, desc) != ITS_SUCCESS)
    {
        if (nms_debug)
        {
            printf("NMSSendISUPEvent: ISUP_MessageSanityCheck failed. Exit\n");
        }
        return ITS_BADISUPMESSAGE;
    }

    /* Dump some NMS info and ITS_EVENT for debugging purpose only. */
    if (nms_debug)
    {
       /* first dump the nms params */
        printf("\nNMSSendISUPEvent: send message to NMS stack.\n");    

        printf("msgType = %d\n", (int) type);
        printf("ctaHd = %d\n", (int) ctaHd);
        printf("suId = %d\n", (int) suId);
        printf("suInstId = %d\n", (int) suInstId);
        printf("spInstId = %d\n", (int) spInstId);
        printf("circuit = %d\n", (int) circuit);
        printf("globalFlg = %d\n", (int) globalFlg);
        printf("cirSelFlg = %d\n", (int) cirSelFlg);
        printf("srcBoard = %d\n", (int) context->boardNum);

        if(ISUP_Encode(ies, ieCount, type, &itsEvent, hdr, desc) != ITS_SUCCESS)
        {
            printf("NMSSendISUPEvent: Try ISUP_Encode before sending, Failed. "
                   " Exit\n");
            
            return ITS_BADISUPMESSAGE;
        }

        printf("\nDump ITS_EVENT data part before sending\n");
        printf("ieCount = %d\n", ieCount);
        for (i = 0; i < itsEvent.len; i++)
        {
            printf("%02x ", itsEvent.data[i]);
            if (!((i+1) % 20))
            {
                printf("\n");
            }
        }
        if ((i+1) % 20)
        {
            printf("\n");
        }
    }

    /*
     * Note that we don't use the Initialization API provided by NMS
     * because we will overwrite the msg with the information from
     * the ITS ISUP message
     */
    switch (type)
    {
    /*
    ** Connect Event messages
    */
    case ISUP_MSG_ANM: /* Answer  */ 
#if defined (CCITT)
    case ISUP_MSG_CON: /* Connect */
#endif                
        /* Translate the ies into an NMS connect event */
        GetNMSConnectEvent(ies, ieCount, desc, &conEvent);
        /* send the event */
        status = ISUPConnectResp(ctaHd, suId, suInstId, 
                                 spInstId, circuit, &conEvent);
        break;

    case ISUP_MSG_IAM: /* Initial Address */
        GetNMSConnectEvent(ies, ieCount, desc, &conEvent);
        status = ISUPConnectReq( ctaHd, suId, suInstId, spInstId, cirSelFlg, 
                                 circuit, &conEvent);
        break;

    /*
    ** Connect Status Event messages
    */          
    case ISUP_MSG_ACM: /* Address Complete */
        GetNMSConnectStatusEvent(ies, ieCount, desc, &conStatusEvent);
        status = ISUPConnectStatusReq(ctaHd, suId, suInstId, spInstId,
                                      circuit, &conStatusEvent, ADDRCMPLT);
        break;

    case ISUP_MSG_CPG: /* Call Progress */
        GetNMSConnectStatusEvent(ies, ieCount, desc, &conStatusEvent);
        status = ISUPConnectStatusReq(ctaHd, suId, suInstId, spInstId,
                                      circuit, &conStatusEvent, PROGRESS);
        break;

    case ISUP_MSG_FOT: /* Forward Transfer */
        GetNMSConnectStatusEvent(ies, ieCount, desc, &conStatusEvent);
        status = ISUPConnectStatusReq(ctaHd, suId, suInstId, spInstId,
                                      circuit, &conStatusEvent, FRWDTRSFR);
        break;

    case ISUP_MSG_INF: /* Information */
        GetNMSConnectStatusEvent(ies, ieCount, desc, &conStatusEvent);
        status = ISUPConnectStatusReq(ctaHd, suId, suInstId, spInstId,
                                      circuit, &conStatusEvent, INFORMATION);
        break;

    case ISUP_MSG_INR: /* Information Request */
        GetNMSConnectStatusEvent(ies, ieCount, desc, &conStatusEvent);
        status = ISUPConnectStatusReq(ctaHd, suId, suInstId, spInstId,
                                      circuit, &conStatusEvent, INFORMATREQ);
        break;

#if defined (CCITT)
    case ISUP_MSG_SAM: /* Subsequent Address */
        GetNMSConnectStatusEvent(ies, ieCount, desc, &conStatusEvent);
        status = ISUPConnectStatusReq(ctaHd, suId, suInstId, spInstId,
                                      circuit, &conStatusEvent, SUBSADDR);
        break;

    case ISUP_MSG_IDR: /* Identification Request */
        GetNMSConnectStatusEvent(ies, ieCount, desc, &conStatusEvent);
        status = ISUPConnectStatusReq(ctaHd, suId, suInstId, spInstId,
                                      circuit, &conStatusEvent, IDENTREQ);
        break;

    case ISUP_MSG_IRS: /* Identification Response */
        GetNMSConnectStatusEvent(ies, ieCount, desc, &conStatusEvent);
        status = ISUPConnectStatusReq(ctaHd, suId, suInstId, spInstId,
                                      circuit, &conStatusEvent, IDENTRSP);
        break;

#endif       

    /*
    ** Status Event messages
    */
    case ISUP_MSG_BLO: /* Blocking */
        GetNMSStatusEvent(ies, ieCount, desc, &statusEvent);
        status = ISUPStatusReq(ctaHd, suId, suInstId, spInstId, globalFlg, 
                        circuit, CIRBLKREQ, &statusEvent);
        break;

    case ISUP_MSG_BLA: /* Blocking Acknowledgement */
        GetNMSStatusEvent(ies, ieCount, desc, &statusEvent);
        status = ISUPStatusReq(ctaHd, suId, suInstId, spInstId, globalFlg, 
                        circuit, CIRBLKRSP, &statusEvent);
        break;

    case ISUP_MSG_CGB: /* Circuit Group Blocking */
        GetNMSStatusEvent(ies, ieCount, desc, &statusEvent);
        status = ISUPStatusReq(ctaHd, suId, suInstId, spInstId, globalFlg, 
                        circuit, CIRGRPBLKREQ, &statusEvent);
        break;

    case ISUP_MSG_CGBA: /* Circuit Group Blocking Acknowledgement */
        GetNMSStatusEvent(ies, ieCount, desc, &statusEvent);
        status = ISUPStatusReq(ctaHd, suId, suInstId, spInstId, globalFlg, 
                        circuit, CIRGRPBLKRSP, &statusEvent);
        break;

    case ISUP_MSG_CQM: /* Circuit [Group - ITU] Query */
        GetNMSStatusEvent(ies, ieCount, desc, &statusEvent);
        status = ISUPStatusReq(ctaHd, suId, suInstId, spInstId, globalFlg, 
                        circuit, CIRGRPQRYREQ, &statusEvent);
        break;

    case ISUP_MSG_GRS: /* Circuit Group Reset */
        GetNMSStatusEvent(ies, ieCount, desc, &statusEvent);
        status = ISUPStatusReq(ctaHd, suId, suInstId, spInstId, globalFlg, 
                        circuit, CIRGRPRESREQ, &statusEvent);
        break;

    case ISUP_MSG_CGU: /* Circuit Group Unblocking */
        GetNMSStatusEvent(ies, ieCount, desc, &statusEvent);
        status = ISUPStatusReq(ctaHd, suId, suInstId, spInstId, globalFlg, 
                        circuit, CIRGRPUNBLKREQ, &statusEvent);
        break;

    case ISUP_MSG_CGUA: /* Circuit Group Unblocking Acknowledgement */
        GetNMSStatusEvent(ies, ieCount, desc, &statusEvent);
        status = ISUPStatusReq(ctaHd, suId, suInstId, spInstId, globalFlg, 
                        circuit, CIRGRPUNBLKRSP, &statusEvent);
        break;

    case ISUP_MSG_COT: /* Continuity */
        GetNMSStatusEvent(ies, ieCount, desc, &statusEvent);
        status = ISUPStatusReq(ctaHd, suId, suInstId, spInstId, globalFlg, 
                        circuit, CONTREP, &statusEvent);
        break;

    case ISUP_MSG_CCR: /* Continuity Check Request */
        GetNMSStatusEvent(ies, ieCount, desc, &statusEvent);
        status = ISUPStatusReq(ctaHd, suId, suInstId, spInstId, globalFlg, 
                        circuit, CONTCHK, &statusEvent);
        break;

    case ISUP_MSG_LPA: /* LoopBack Ack */
        GetNMSStatusEvent(ies, ieCount, desc, &statusEvent);
        status = ISUPStatusReq(ctaHd, suId, suInstId, spInstId, globalFlg, 
                        circuit, LOOPBCKACK, &statusEvent);
        break;

    case ISUP_MSG_RSC: /* Reset Circuit Message */
        GetNMSStatusEvent(ies, ieCount, desc, &statusEvent);
        status = ISUPStatusReq(ctaHd, suId, suInstId, spInstId, globalFlg, 
                        circuit, CIRRESREQ, &statusEvent);
        break;

    case ISUP_MSG_UBL: /* Unblocking */
        GetNMSStatusEvent(ies, ieCount, desc, &statusEvent);
        status = ISUPStatusReq(ctaHd, suId, suInstId, spInstId, globalFlg, 
                        circuit, CIRUNBLKREQ, &statusEvent);
        break;

    case ISUP_MSG_UBA: /* Unblocking Acknowledgement */
        GetNMSStatusEvent(ies, ieCount, desc, &statusEvent);
        status = ISUPStatusReq(ctaHd, suId, suInstId, spInstId, globalFlg, 
                        circuit, CIRUNBLKRSP, &statusEvent);
        break;

#if defined (ANSI)
    case ISUP_MSG_CRM: /* Circuit Reservation */
        GetNMSStatusEvent(ies, ieCount, desc, &statusEvent);
        status = ISUPStatusReq(ctaHd, suId, suInstId, spInstId, globalFlg, 
                        circuit, CIRRESERVE, &statusEvent);
        break;

    case ISUP_MSG_CRA: /* Circuit Reservation Acknowledgement */
        GetNMSStatusEvent(ies, ieCount, desc, &statusEvent);
        status = ISUPStatusReq(ctaHd, suId, suInstId, spInstId, globalFlg, 
                        circuit, CIRRESERVEACK, &statusEvent);
        break;
#endif        

    /*
    ** Information Event messages
    */
    case ISUP_MSG_PAM: /* Pass Along */
        GetNMSPAM(ies, ieCount, desc, &infoEvent);
        status = ISUPDataReq(ctaHd, suId, suInstId, spInstId, 
                             circuit, &infoEvent);
        break;

#if defined (CCITT)
    case ISUP_MSG_USR: /* User-to-User Message */
        GetNMSInfoEvent(ies, ieCount, desc, &infoEvent);
        status = ISUPDataReq(ctaHd, suId, suInstId, spInstId, 
                             circuit, &infoEvent);
        break;
#endif

    /*
    ** Release Event messages
    */
    case ISUP_MSG_REL: /* Release */
        GetNMSReleaseEvent(ies, ieCount, desc, &releaseEvent);
        status = ISUPReleaseReq(ctaHd, suId, suInstId, spInstId, 
                                circuit, &releaseEvent);
        break;

    case ISUP_MSG_RLC: /* Release Complete */
        GetNMSReleaseEvent(ies, ieCount, desc, &releaseEvent);
        status = ISUPReleaseResp(ctaHd, suId, suInstId, spInstId, 
                                 circuit, &releaseEvent);
        /* reset spInstId to null after the clear of the connection */
        its_spInstIds[circuit] = SP_INST_ID_NULL;
        break;  

    /*
    ** Resume Event messages
    */
    case ISUP_MSG_RES: /* Resume */
        GetNMSResumeEvent(ies, ieCount, desc, &resumeEvent);
        status = ISUPResumeReq(ctaHd, suId, suInstId, spInstId, 
                               circuit, &resumeEvent);
        break;

    /*
    ** Suspend Event messages
    */
    case ISUP_MSG_SUS: /* Suspend */
        GetNMSSuspendEvent(ies, ieCount, desc, &suspendEvent);
        status = ISUPSuspendReq(ctaHd, suId, suInstId, spInstId, 
                                circuit, &suspendEvent);
        break;

    /*
    ** Management messages
    */
#if defined (ANSI) 
    case ISUP_MSG_CVT: /* Circuit Validation Test */
        /* This msg contains no ie, send in the management API */
        status = isupValidateCircuit(context->boardNum, circuit);        
        break;
#endif

    /*
    ** Facility Event messages
    */
#if defined (CCITT)   
    case ISUP_MSG_FAA: /* Facility Accepted */
        GetNMSFacilityEvent(ies, ieCount, desc, &facilityEvent);
        status = ISUPFacilityReq(ctaHd, suId, suInstId, spInstId,
                      circuit, &facilityEvent, FACILITYACC);
        break;

    case ISUP_MSG_FRJ: /* Facility Reject */
        GetNMSFacilityEvent(ies, ieCount, desc, &facilityEvent);
        status = ISUPFacilityReq(ctaHd, suId, suInstId, spInstId,
                      circuit, &facilityEvent, FACILITYREJ);
        break;

    case ISUP_MSG_FAC: /* Facility */
        GetNMSFacilityEvent(ies, ieCount, desc, &facilityEvent);
        status = ISUPFacilityReq(ctaHd, suId, suInstId, spInstId,
                      circuit, &facilityEvent, FACILITY);
        break;

    case ISUP_MSG_FAR: /* Facility Request */
        GetNMSFacilityEvent(ies, ieCount, desc, &facilityEvent);
        status = ISUPFacilityReq(ctaHd, suId, suInstId, spInstId,
                      circuit, &facilityEvent, FACILITYREQ);
        break;
#endif
   
    /* 
    ** Not supported or generated automatically by ISUP task messages
    */
    case ISUP_MSG_CRG: /* Charge Information */
    case ISUP_MSG_CQR: /* Circuit [Group - ITU] Query Response */
    case ISUP_MSG_GRA: /* Circuit Group Reset Acknowledgement */
    case ISUP_MSG_CFN: /* Confusion */
    case ISUP_MSG_UCIC: /* Unequipped Circuit Identification Code */
#if defined (ANSI)
    case ISUP_MSG_CVR: /* Circuit Validation Response */
    case ISUP_MSG_EXM: /* Exit Message */
#endif
#if defined (CCITT)
    case ISUP_MSG_NRM: /* Network Ressource Management */
    case ISUP_MSG_SGM: /* Segmentation */
    case ISUP_MSG_UPA: /* User Part Available */
    case ISUP_MSG_UPT: /* User Part Test */
    case ISUP_MSG_OLM: /* Overload */
#endif
    default:
        if (nms_debug)
        {
            printf("NMSSendISUPEvent: msgType = %d", type);
            printf(" not supported or generated automatically by NMS.");
        }
        break;

    } /* switch */

    if (status != ISUP_SUCCESS)
    {
        printf("NMSSendISUPEvent failed. status = %d", (int) status);

        return (ITS_ESENDFAIL);
    }

    return (ITS_SUCCESS);
}

/*
 * convert an array of IEs to a ITS_OCTET buf for MTP3.
 */
int 
NMS_ISUP_EncodeMTP3(ITS_ISUP_IE *ies, int ieCount, ITS_OCTET msgType,
                ITS_EVENT *event, ITS_HDR *hdr, ISUP_MSG_DESC* desc)
{
    int i, j, offset, evoffset, lastVarOffset;

    ITS_ISUP_IE* ieRef[ITS_MAX_ISUP_IES];

    ITS_BOOLEAN haveOpts = ITS_FALSE, sawOpts = ITS_FALSE;
    int optPtr = 0;

    int ptrTableSize = 0;

    ITS_OCTET *margs = desc->mArgs;
    int nmargs = desc->nmArgs;

    ITS_OCTET *vargs = desc->vArgs;
    int nvargs = desc->nvArgs;

    ITS_OCTET *oargs = desc->oArgs;
    int noargs = desc->noArgs;

    ITS_BOOLEAN msgIsPAM = ITS_FALSE;
    ITS_OCTET msgTypeInPAM = 0x00;
    int startIndex = 0;
    ITS_USHORT len = 0;
    ITS_OCTET data[MAX_ISUP_DATA_LEN];
    MTP3_HEADER mtp3Hdr;
    IsupCircCfg isupCircCfg;
    IsupGenParms isupGenParm;
    S16 status;
    ITS_USHORT CIC = hdr->context.cic;
    ITS_BOOLEAN hasMTP3Hdr = ITS_FALSE;

    printf("NMS_ISUP_EncodeMTP3: hdr->context.CIC = %d\n", CIC);

    memset(&mtp3Hdr, 0, sizeof(MTP3_HEADER));

    /* sanity */
    if (ieCount > ITS_MAX_ISUP_IES)
    {
        return (ITS_EOVERFLOW);
    }

    /* Check if msg Type is PAM */
    if (msgType == ISUP_MSG_PAM)
    {
        if (ies[0].param_id == ISUP_PRM_MSG_IN_PAM)
        {
            msgTypeInPAM = ies[0].param_data.msgTypeInPAM;
            msgIsPAM = ITS_TRUE;
            startIndex++;
        }
        else
        {
            return (ITS_EMISSMAND);
        }
    }

    /* start at zero */
    offset = 0;

    /* find the fixed mandatory */
    for (i = 0; i < nmargs; i++)
    {
        for (j = startIndex; j < ieCount; j++)
        {
            if (ies[j].param_id == margs[i])
            {
                ieRef[offset] = &ies[j];
                offset++;
                break;
            }
        }

        /* is it missing? */
        if (j == ieCount)
        {
            return (ITS_EMISSMAND);
        }
    }

    /* find the variable mandatory */
    for (i = 0; i < nvargs; i++)
    {
        for (j = startIndex; j < ieCount; j++)
        {
            if (ies[j].param_id == vargs[i])
            {
                ieRef[offset] = &ies[j];
                offset++;
                break;
            }
        }

        /* is it missing? */
        if (j == ieCount)
        {
            return (ITS_EMISSMAND);
        }
    }

    /* find the optionals */
    for (i = 0; i < noargs; i++)
    {
        for (j = startIndex; j < ieCount; j++)
        {
            if (ies[j].param_id == oargs[i])
            {
                ieRef[offset] = &ies[j];
                offset++;
                break;
            }
        }
        /* if missing, that's ok */
    }

    /* skip extras */
    while (offset < ieCount)
    {
        ieRef[offset] = NULL;
        offset++;
    }
        
    /* set the message type */
    data[0] = msgType;
    
    evoffset = sizeof(ITS_OCTET);    

    /*
     * Before putting in the params, if the Msg is the PAM, before the params
     * we must have the msg type in the PAM
     */
    if (msgIsPAM)
    {
        data[evoffset] = msgTypeInPAM;
        evoffset++;
    }

    /* copy in the mandatories */
    for (i = 0; i < nmargs; i++)
    {
        memcpy(&data[evoffset], &ieRef[i]->param_data,
               ieRef[i]->param_length);

        evoffset += ieRef[i]->param_length;
    }

    /* do we have any optionals? */
    if (noargs > 0)
    {
        haveOpts = ITS_TRUE;
    }

    /* compute the size of the ptr table */
    ptrTableSize = nvargs + (haveOpts ? 1 : 0);
    lastVarOffset = 0;

    /* build the ptr table for mandatory variable args */
    for (i = 0; i < nvargs; i++)
    {
        data[evoffset] = ptrTableSize + lastVarOffset - i;
        lastVarOffset += ieRef[nmargs + i]->param_length + 1;
        evoffset++;
    }

    /* if we have *any* optionals, build pointer to that */
    if (haveOpts)
    {
        data[evoffset] = ptrTableSize + lastVarOffset - i;
        optPtr = evoffset;
        evoffset++;
    }

    /* copy in the variable mandatories */
    for (i = 0; i < nvargs; i++)
    {
        data[evoffset] = ieRef[nmargs + i]->param_length;
        evoffset++;

        memcpy(&data[evoffset], &ieRef[nmargs + i]->param_data,
               ieRef[nmargs + i]->param_length);

        evoffset += ieRef[nmargs + i]->param_length;
    }

    /* copy in the optionals */
    for (i = nmargs + nvargs; i < ieCount; i++)
    {
        if (ieRef[i] == NULL)
        {
            continue;
        }

        sawOpts = ITS_TRUE;

        data[evoffset] = ieRef[i]->param_id;
        evoffset++;

        data[evoffset] = ieRef[i]->param_length;
        evoffset++;

        memcpy(&data[evoffset], &ieRef[i]->param_data,
               ieRef[i]->param_length);

        evoffset += ieRef[i]->param_length;
    }

    /* terminate variable list */
    if (noargs != 0)
    {
        data[evoffset] = ISUP_PRM_EOP;
        evoffset++;
    }

    if (haveOpts && !sawOpts)
    {
        data[optPtr] = 0;
    }

    /* set final length */
    len = evoffset;

    /* find the routing label, if present */
    for (i = startIndex; i < ieCount; i++)
    {
        if (ies[i].param_id == ISUP_PRM_ROUTING_LABEL)
        {
            memcpy(&mtp3Hdr, &ies[i].param_data.routingLabel,
                   ies[i].param_length);
            hasMTP3Hdr = ITS_TRUE;
            break;
        }
    }

    if (!hasMTP3Hdr)
    {
        /* get mtp3Hdr */
        mtp3Hdr.sio = MTP3_SIO_ISUP;

        /* the srcBoard is stored in the hdr->type */
        /* get the dpc */    
        if ((status = isupGetCircCfg((U8)hdr->type, 
                                     &isupCircCfg, 
                                     CIC)) != ISUP_MGMT_SUCCESS)
        {
            printf( "Board %d Circuit %d isupGetCircCfg failed: status = %d\n",
                    hdr->type, CIC, status );

            return ITS_ENOMSG;
        }

        /* get the opc */    
        if ( (status = isupGetGenCfg((U8)hdr->type, &isupGenParm))
             != ISUP_MGMT_SUCCESS )
        {
            printf( "Board %d isupGetGenCfg failed: status = %d\n",
                    hdr->type, status );

            return ITS_ENOMSG;
        }

        /* set the dpc, opc (U32) */
        MTP3_RL_SET_DPC_VALUE(mtp3Hdr.label, isupCircCfg.dstPointCode);   
        MTP3_RL_SET_OPC_VALUE(mtp3Hdr.label, isupGenParm.orgPointCode);
    }

    event->data[0] = MTP3_MSG_USER_DATA;
    
    /* copy in the (rest of)CIC */
#if defined(CCITT)
    /* set the sls = the four least significant bits of the CIC */
    MTP3_RL_SET_SLS(mtp3Hdr.label, CIC & 0x000F);

    event->data[1 + sizeof(MTP3_HEADER)] = (CIC >> 4) & 0xFF;
    event->data[1 + sizeof(MTP3_HEADER) + 1] = (CIC >> 12) & 0x0F; 
#elif defined(ANSI)
    MTP3_RL_SET_SLS(mtp3Hdr.label, 0x00);
    event->data[1 + sizeof(MTP3_HEADER)] = CIC & 0xFF;
    event->data[1 + sizeof(MTP3_HEADER) + 1] = (CIC >> 8) & 0xFF; 
#endif 
    
    memcpy(&event->data[1], &mtp3Hdr, sizeof(MTP3_HEADER));

    memcpy(&event->data[1 + sizeof(MTP3_HEADER) + 2], data, len);

    event->len = sizeof(ITS_OCTET) + sizeof(MTP3_HEADER) + 
                 sizeof(ITS_USHORT) + len;
    event->src = ITS_MTP3_SRC;

    /*   -------------------------------------------------
     *   | 1 | MTP3_HEADER | CIC | ISUP message          |
     *   -------------------------------------------------
     *     1   sizeof(^)      2        len
     */

    if (nms_debug)
    {
        printf("NMS_ISUP_EncodeMTP3 success.");
    }

    return (ITS_SUCCESS);
}

#endif /* INCLUDE_ISUP */

