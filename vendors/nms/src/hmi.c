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
 *  ID: $Id: hmi.c,v 9.1 2005/03/23 12:56:15 cvsadmin Exp $
 * LOG: $Log: hmi.c,v $
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
 * LOG: Revision 6.1  2002/02/28 16:14:59  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.6.6.2  2002/05/09 15:12:58  hcho
 * LOG: Integrate v3_6 with vframe.
 * LOG:
 * LOG: Revision 5.6.6.1  2002/04/18 19:58:44  sjaddu
 * LOG: NMS 3.8 changes in PR6
 * LOG:
 * LOG: Revision 5.6  2001/11/09 20:19:55  mmiers
 * LOG: Don't force the vendor lib to be part of the engine.  Make into
 * LOG: DLL instead.
 * LOG:
 * LOG: Revision 5.5  2001/10/19 20:49:00  mmiers
 * LOG: Get things working with the engine.
 * LOG:
 * LOG: Revision 5.4  2001/10/06 23:30:33  mmiers
 * LOG: Finish the MTP2 API.
 * LOG:
 * LOG: Revision 5.3  2001/10/05 22:59:42  mmiers
 * LOG: NMS MTP2 API is taking shape.
 * LOG:
 * LOG: Revision 5.2  2001/09/05 22:00:31  mmiers
 * LOG: Add MTP2 API.
 * LOG:
 * LOG: Revision 5.1  2001/09/05 20:35:48  mmiers
 * LOG: Consolidate the NMS libraries.  Only the root library so far.
 * LOG:
 * LOG: Revision 5.2  2001/09/04 15:48:09  ssharma
 * LOG: Integrate with RM, add debug statements.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:42  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/07/18 19:49:50  rsonak
 * LOG: Added RM notifications and itsNMSRM_Class
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:08  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.10  2001/05/04 16:16:44  hcho
 * LOG: Put ITS_EVENT_TERM back.
 * LOG:
 * LOG: Revision 3.9  2001/05/04 15:46:54  hcho
 * LOG: Modified ISUP binding sequence.
 * LOG:
 * LOG: Revision 3.8  2001/02/28 15:49:54  hxing
 * LOG: Test in progress
 * LOG:
 * LOG: Revision 3.7  2001/02/14 00:53:05  hxing
 * LOG: Problem with ITS_SS7_HANDLE
 * LOG:
 * LOG: Revision 3.6  2001/02/08 23:30:57  hxing
 * LOG: Debug in solaris for isup integration
 * LOG:
 * LOG: Revision 3.5  2001/02/06 21:09:36  hxing
 * LOG: Work around ctaInitialize
 * LOG:
 * LOG: Revision 3.4  2001/02/06 17:14:00  hxing
 * LOG: Check return errors
 * LOG:
 * LOG: Revision 3.3  2001/02/06 00:14:57  hxing
 * LOG: Remove warnings
 * LOG:
 * LOG: Revision 3.2  2001/02/05 23:58:35  hxing
 * LOG: Remove hard tabs
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:11:55  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.2  2000/08/10 00:19:23  labuser
 * LOG: Correct HMI_TIMEOUT Error
 * LOG:
 * LOG: Revision 1.1  2000/07/18 15:27:41  yranade
 * LOG:
 * LOG: Initial version.
 * LOG:
 * LOG: Revision 1.5  2000/06/17 01:15:58  rsonak
 * LOG:
 * LOG:
 * LOG: Enlarge error buffer.
 * LOG:
 * LOG: Revision 1.4  2000/06/14 15:52:47  rsonak
 * LOG:
 * LOG: Sync with change in signature of TPOOL_Init in IntelliSS7.
 * LOG:
 * LOG: Revision 1.3  2000/06/12 15:20:43  randresol
 * LOG: Submit a new version of HMI
 * LOG:
 * LOG: Revision 1.1.2.3  2000/06/09 01:31:39  labuser
 * LOG: Rebind the application to MTP3 after loading the board
 * LOG:
 * LOG: Revision 1.1.2.2  2000/06/02 15:34:52  randresol
 * LOG:
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.1.2.1  2000/05/24 01:31:04  randresol
 * LOG: Link with SS7 Version 3.0 and CtAccess V 2.11
 * LOG:
 * LOG: Revision 1.1  2000/05/11 22:01:55  randresol
 * LOG: Creation of NMS directory for SS7 Version 3.
 * LOG: Creation of VMI Interface on top of NMS HMI library to support redundancy.
 * LOG:
 *
 ****************************************************************************/

#if defined(INCLUDE_VMI)

#include <ss7type.h>
#include <ctadef.h>
#include <hmidef.h>
#include <ctadisp.h>
#include <hmiapi.h>

#undef THREAD_RET_TYPE

#include <its_intern.h>
#include <its.h>
#include <its_vmi.h>        
#include <its_transports.h>
#include <its_thread_pool.h>
#include <its_timers.h>
#include <its_ss7_trans.h>

#include <stdlib.h>
 

#if defined(STANDALONE)
#error Invalid configuration.  Thread pools cannot be
#error run from single threaded processes.
#endif

#define VMI_MAXTHREAD 5

typedef struct
{
    CTAHD vmiHandle;
    ITS_USHORT vmiHandleId;
    ITS_BOOLEAN busy; /* to determine if this handle is being
                         used by another thread.
                      */
    CTAQUEUEHD vmiRecvQueue;
}
VMI_CtxHandle;

typedef struct 
{
   ITS_UINT mask;
   ITS_USHORT vmiHandleId;
   ITS_USHORT srcInstance;
   VMI_CtxHandle *ctxHandle;
   
}
VMI_Arg;

typedef struct
{
    TPOOL*  pool;
    int     count;
}
LocalPool;

static ITS_SS7_HANDLE   tektxHandl;
static LocalPool        vmiPool; 
U8 loadFlag = 0;

ITS_BOOLEAN isCtaInitialized;

/*
 * A pool of five vmi handles on the HMI Service. 
 *  we allow up to 5 connection handles to the HMI Service. 
 *  The connections are established as follow:
 *    . One permanent handle to receive asychronous event
 *    . One permanent handle to send primitives and associate responses
 *    . 3 or 4 dynamic handles primitives only when the permanent handle
 *      is busy  
 */
static VMI_CtxHandle vmiHandlePool[VMI_MAXTHREAD]; 

static ITS_Class rmHelper;

static int VMI_InstanceTable[VMI_MAX_INSTANCE] =
{
    -1,
    -1,
    -1,
    -1,
    -1
};
static CTA_SERVICE_NAME InitServices[] =
{
    {
        "HMI",
        "HMIMGR"
    }
} ;

static ITS_OCTET HmiToVmiRtnCode(DWORD hmiRtnCode);
static ITS_OCTET HmiEvtIdToVmiEvtId(DWORD hmiEventId);

static void NotifyOnHmiEvent(DWORD hmiEventId);
static void VMI_SendPrimitive(SS7_VendorState newState);

static TPOOL_THREAD* VMI_ThreadCreator(TPOOL *pool, int stackSize); 
static int  VMI_OpenService(VMI_CtxHandle *ctxHandle, ITS_USHORT vmiHandleId,
                            DWORD serviceType);
static void VMI_PrimitiveDispatcher(TPOOL_THREAD *pThread, void *arg);
static void VMI_ReceiverDispatcher(TPOOL_THREAD *pThread, void *arg);
static int  VMI_SendToRegisteredInstance(ITS_EVENT *itsEvent);
static void VMI_ShowError( char *preface, DWORD errcode );
static int  VMI_WaitForEventWithReason( CTAQUEUEHD vmiRecvQueue, 
                                       DWORD eventId,
                                       DWORD eventVal);

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize health management.
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
VMI_Initialize(ITS_Class newClass)
{
    int ret = ITS_SUCCESS;
    DWORD vmiRet;
    CTA_INIT_PARMS initparms = { 0 };

    vmiPool.count = 1;
    vmiPool.pool = TPOOL_InitPool(&vmiPool);    
    if (!vmiPool.pool)
    {
        return !ITS_SUCCESS;
    }

    ret = TPOOL_CreatePool(vmiPool.pool, VMI_MAXTHREAD, 0, VMI_ThreadCreator);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }


    /*******************************************
     ********** Initialize Service    **********
     *******************************************/

    /* Initialize size of init parms structure */
    initparms.size = sizeof(CTA_INIT_PARMS);
    /* Use process global default parameters */
    initparms.parmflags = CTA_PARM_MGMT_SHARED_IF_PRESENT;
    /* If daemon running then initialize tracing */
    initparms.traceflags = CTA_TRACE_ENABLE;
    /* Notify when CT Access changes its internal list of wait objects*/
    /*initparms.ctaflags = CTA_NOTIFY_UPDATE_WAITOBJS;*/
    /* Verify CT Access compatibility */
    initparms.ctacompatlevel = CTA_COMPATLEVEL;

    /************************************************************
     *Initialize CT Access
     *vmiRet = ctaInitialize(InitServices,
     *              sizeof(InitServices)/sizeof(InitServices[0]),
     *              &initparms);
     *************************************************************/

    /*Pass NULL for InitServices so it will read from file cta.cfg*/
    vmiRet = ctaInitialize(NULL,0,&initparms);
    if (vmiRet != SUCCESS)
    {
        printf( "Error : (%d) error returned in (%s) call.\n", 
                 (int)vmiRet, "ctaInitialize" );
        return (ITS_ENOPROXY);
    }

    VMI_ShowError( "ctaInitialize", vmiRet );

    isCtaInitialized = ITS_TRUE;

    printf("VMI_Initialize: ctaInitialize already called\n");
    
    /* Create a Que for events to be stored in*/
    vmiRet = ctaCreateQueue(NULL, 0, &vmiHandlePool[0].vmiRecvQueue);

    if (vmiRet != SUCCESS)
    {
        printf( "Error : (%d) error returned in (%s) call.\n", 
                 (int)vmiRet, "ctaCreateQueue" );

        return (ITS_ENOPROXY);
    }
    
    VMI_ShowError( "ctaCreateQueue", vmiRet );
 
    printf("queueHd: vmiHandlePool[0].vmiRecvQueue = 0x%08X\n",
           (unsigned)vmiHandlePool[0].vmiRecvQueue);

    vmiHandlePool[0].busy = ITS_FALSE;
    vmiHandlePool[1].vmiHandleId = 1;

    /*
     * Create a permanent CTA context to handle application request and
     * associated responses
     */
    vmiRet = ctaCreateQueue(NULL, 0, &vmiHandlePool[1].vmiRecvQueue);

    if (vmiRet != SUCCESS)
    {
        printf( "Error : (%d) error returned in (%s) call.\n", 
                 (int)vmiRet, "ctaCreateQueue" );

        return (ITS_ENOPROXY);
    }

    printf("queueHd: vmiHandlePool[1].vmiRecvQueue = 0x%08X\n",
            (unsigned)vmiHandlePool[1].vmiRecvQueue);

    vmiHandlePool[1].busy = ITS_FALSE;
    vmiHandlePool[1].vmiHandleId = 1;

    if ( VMI_OpenService(&vmiHandlePool[1], vmiHandlePool[1].vmiHandleId,
                         HMI_DO_COMMANDS) != ITS_SUCCESS)
    {
        printf("VMI_OpenService failed\n");

        return !ITS_SUCCESS;
    }

    /* find our RM helper */
    rmHelper = ITS_FindFeature(SS7RM_CLASS_NAME);
    if (rmHelper == NULL)
    {
        return (!ITS_SUCCESS);
    }

    /* Dispatch the thread that read incomming event from the vmi Queue */
    ret = TPOOL_Dispatch(vmiPool.pool, 
                         VMI_ReceiverDispatcher ,
                         (void *) &vmiHandlePool[0]);

    if (ret != ITS_SUCCESS)
    {
        printf("Error: VMI_Initialize::TPOOL_Dispatch failed\n");
    
        return ret;
    }

    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Terminate health management.
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
VMI_Terminate(ITS_Class newClass)
{
    DWORD vmiRet;
    
    TPOOL_DestroyPool(vmiPool.pool);
    TPOOL_WaitForDestroyComplete();

    /*
    **   This function destroys the event queue and all CTA contexts
    **   associated with the event queue. This is an asynchonous function
    **   so the application remains blocked until all cleanup and close
    **   activity has completed.
    */
    vmiRet = ctaDestroyQueue(vmiHandlePool[0].vmiRecvQueue);
    vmiRet = ctaDestroyQueue(vmiHandlePool[1].vmiRecvQueue);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Register an instance with VMI
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
VMI_RegisterInstance(ITS_USHORT instance)
{
    int i;

    for (i = 0; i < VMI_MAX_INSTANCE; i++)
    {
        if (VMI_InstanceTable[i] == -1)
        {
            VMI_InstanceTable[i] = instance;
            return ITS_SUCCESS;
        }    
    }
   
    return ITS_ENOMEM;

}
    
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Deregister an instance with VMI
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
VMI_DeregisterInstance(ITS_USHORT instance)
{
    int i;

    for(i = 0; i < VMI_MAX_INSTANCE; i++)
    {
        if (VMI_InstanceTable[i] == instance)
        {
            VMI_InstanceTable[i] = -1 ;
            return ITS_SUCCESS;
        }
    }
    return ITS_ENOMEM;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Set SS7 handle to local for service open.
 *
 *  Input Parameters:
 *      ss7Handle.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS or !ITS_SUCCESS.
 ****************************************************************************/
int
VMI_SetSS7Handle(ITS_SS7_HANDLE ss7Handl)
{
    if (ss7Handl != NULL)
    {
        tektxHandl = ss7Handl;

        return ITS_SUCCESS;
    }

    return !ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a pool thread.
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
static TPOOL_THREAD *
VMI_ThreadCreator(TPOOL *pool, int stackSize)
{
    static int nbrOfThrds = 1;
    TPOOL_THREAD *aThread;

    if (nbrOfThrds > VMI_MAXTHREAD)
    {
        /* This thread pool should not contain more then VMI_MAXTHREAD */
        /* Returning NULL will cause TPOOL_CreatePool to fail          */
        return NULL;
    }
    
    if ( (aThread = (TPOOL_THREAD *) calloc(1, sizeof(TPOOL_THREAD))) == NULL)
    {
        /* cannot allocate the memory to create the thread */
        return NULL;
    }

    nbrOfThrds++;

    return aThread;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Send a primitive
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
VMI_SendPrimitive(SS7_VendorState newState) 
{
    VMI_Arg *vmiArg;
    int ret = ITS_SUCCESS;
    DWORD vmiRet;
    ITS_USHORT i = 1;

    vmiArg = (VMI_Arg*) malloc(sizeof(VMI_Arg));

    switch (newState)
    {
        case SS7_PRIMARY_STATE :
            vmiArg->mask = VMI_PRIMARY;
            printf("\nVMI_SendPrimitive : Primary\n");
            break;

        case SS7_SECONDARY_STATE :
            vmiArg->mask = VMI_BACKUP;
            printf("\nVMI_SendPrimitive : Backup\n");
            break;

        default:
            vmiArg->mask = VMI_PRIMARY;
            printf("\nVMI_SendPrimitive : Default\n");
            break;
    }

    vmiArg->vmiHandleId = 1; /* Assign to the permanent context handle */
    vmiArg->ctxHandle = &vmiHandlePool[1];
  
    /* Check for available Context Handle in the Pool */
    /* Reminder: vmiHandleId 0 is reserved to receive asynchronous events  
                 vmiHandleId 1 is a permanent handle to send requests     
                 vmiHandleId 2-4 are dynamic handle to send requests      
    */
    
    /* check if the permanent handle is busy */
    /* if the permanent handle is not busy then use that handle */ 
    /* to excecute the request */
   
    if (vmiHandlePool[1].busy == ITS_TRUE) 
    {
        /* the permanent context handle is busy. We shoud allocate  
           a new context handle to process this request.
           First we should find a available one in the pool.
        */
        for (i = 1; i < VMI_MAXTHREAD ; i++)
        {
            if (vmiHandlePool[i].busy == ITS_FALSE)
            {
                /* Create a dynamic queue to handle request */
                vmiRet = ctaCreateQueue(NULL, 0, 
                         &vmiHandlePool[i].vmiRecvQueue);

                if (vmiRet != SUCCESS)
                {
                    printf("\nctaCreateQueue failed...\n");
                    return; 
                }
    
                vmiHandlePool[i].busy = ITS_TRUE; 
                break;
            } 

        }
        if (i == VMI_MAXTHREAD)
        {
            printf("\nNo resource available for processing this request\n");
            return ;
        } 
    }

    vmiHandlePool[i].busy = ITS_TRUE;
    vmiArg->vmiHandleId = i ; /* Assign to context handle */
    vmiArg->ctxHandle = &vmiHandlePool[i];

    ret = TPOOL_Dispatch(vmiPool.pool, 
                         VMI_PrimitiveDispatcher, 
                         (void *) vmiArg); 

    if (ret != ITS_SUCCESS)
    {
        printf("\nVMI_SendPrimitive : TPOOL_Dispatch failed!\n");
        /* TODO: Deallocate Context */

        vmiHandlePool[i].busy = ITS_FALSE;
        free(vmiArg);
    }

    return;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Open the service.
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
VMI_OpenService(VMI_CtxHandle *ctxHandle, ITS_USHORT vmiHandleId, 
                DWORD serviceType)
{
    int ret = ITS_SUCCESS;
    DWORD vmiRet;
    CTA_SERVICE_DESC vmiSvcList[1] = {
        {{"HMI", "HMIMGR"}, {{0}, 0, 0}, {{0}, {0}}, {0, 0, 0, 0, 0}}
    };
    
    vmiRet = ctaCreateContext(ctxHandle->vmiRecvQueue, 0, NULL, 
                              &(ctxHandle->vmiHandle));

    if (vmiRet != SUCCESS)
    {
        printf( "Error : (%d) error returned in (%s) call.\n", 
                 (int)vmiRet, "ctaCreateContext" );

        return (ITS_ENOPROXY);
    }

    VMI_ShowError( "ctaCreateContext", vmiRet );

    printf("ctaHd: ctxHandle->vmiHandle = 0x%08X\n",
           (unsigned)ctxHandle->vmiHandle);
    
    /* Set the parameters for the HMI Service List */
    vmiSvcList[0].svcargs.args[0] = (DWORD) vmiHandleId; /* unique index */
    vmiSvcList[0].svcargs.args[1] = 1; /* board 1 */
    vmiSvcList[0].svcargs.args[2] = serviceType; 
    if (serviceType == HMI_RCV_EVENTS)
    {
       vmiSvcList[0].svcargs.args[1] = HMI_EVENTS_ALL_BOARDS;
    }

   /* Create the dynamic service to receive HMI events */

    vmiRet = ctaOpenServices(ctxHandle->vmiHandle, 
                             &vmiSvcList[0], 1);
    if (vmiRet != SUCCESS)
    {
       printf("\nctaOpenServices failed...\n");
       return ITS_ENOMEM;
    }
    
   /* Wait for service open to complete */
   ret = VMI_WaitForEventWithReason(ctxHandle->vmiRecvQueue, 
                   CTAEVN_OPEN_SERVICES_DONE, CTA_REASON_FINISHED);

   if (ret != ITS_SUCCESS)
   {
       printf("\nWait for Open services has failed\n");

       return ITS_ENOMEM;
   }

   VMI_ShowError( "ctaOpenServices", vmiRet);

   return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Dispatch a primitive.
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
VMI_PrimitiveDispatcher(TPOOL_THREAD *pThread, void *arg)
{
    VMI_Arg *vmiArg = (VMI_Arg *) arg;
    ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *)tektxHandl;
    DWORD hmiRet = 0;
    ITS_EVENT itsEvent;

    ITS_EVENT_INIT(&itsEvent, VMI_SYNCHRONOUS_SRC, MTP2_MAX_MSG_SIZE);

    if (vmiArg->vmiHandleId != 1)
    {
        VMI_OpenService(vmiArg->ctxHandle, 
                        vmiArg->vmiHandleId, HMI_DO_COMMANDS);

        TIMERS_Sleep(1);
    }

    switch(vmiArg->mask)
    {
        case VMI_BACKUP:
            hmiRet = hmiBackup(vmiArg->ctxHandle->vmiHandle);

            /* Bind to ISUP */
            if (tektxHandl != NULL)
            {
                if ((TRANSPORT_MASK(VENDOR_OWNING_TRANSPORT(context))
                    & ITS_ISUP) == ITS_ISUP)
                {
                    if (NMSOpenISUP(tektxHandl) != ITS_SUCCESS)
                    {
                        printf("ISUP BindError: Unable to bind the ISUP\n");
                    }
                    loadFlag = 0;
                }
            }
#if defined(ENABLE_ISUP_INDICS)
            /* Bind to ISUP */
            if (loadFlag)
            {
                if ((TRANSPORT_MASK(VENDOR_OWNING_TRANSPORT(context))
                    & ITS_ISUP) == ITS_ISUP)
                {
                    if (NMSOpenISUP(tektxHandl) != ITS_SUCCESS)
                    {
                        printf("ISUP BindError: Unable to bind the ISUP\n");
                    }
                    loadFlag = 0;
                }
            }
#endif 
            break;
         case VMI_PRIMARY:
            hmiRet = hmiPrimary(vmiArg->ctxHandle->vmiHandle);

            /* Bind to ISUP */
            if (tektxHandl != NULL)
            {
                if ((TRANSPORT_MASK(VENDOR_OWNING_TRANSPORT(context))
                    & ITS_ISUP) == ITS_ISUP)
                {
                    if (NMSOpenISUP(tektxHandl) != ITS_SUCCESS)
                    {
                        printf("ISUP BindError: Unable to bind the ISUP\n");
                    }
                    loadFlag = 0;
                }
            }
#if defined(ENABLE_ISUP_INDICS)
            /* Bind to ISUP */
            if (loadFlag)
            {
                if ((context->mask & ITS_ISUP) == ITS_ISUP)
                {
                    if (NMSOpenISUP(tektxHandl) != ITS_SUCCESS)
                    {
                        printf("ISUP BindError: Unable to bind the ISUP\n");
                    }
                    loadFlag = 0;
                }
            }
#endif

            break;
           
        case VMI_HALT_BOARD:
            
            hmiRet = hmiHaltBoard(vmiArg->ctxHandle->vmiHandle);
            loadFlag = 0;

            break;

        case VMI_LOAD_BOARD:
            
            hmiRet = hmiLoadBoard(vmiArg->ctxHandle->vmiHandle);
            loadFlag = 1;

            break;
 
        case VMI_RESET:
            hmiRet = hmiReset(vmiArg->ctxHandle->vmiHandle);

            break;

        case VMI_SHUTDOWN:
            hmiRet = hmiShutdown(vmiArg->ctxHandle->vmiHandle);

            break;

        case VMI_STANDALONE:
            hmiRet = hmiStandalone(vmiArg->ctxHandle->vmiHandle);

            /* Bind to ISUP */
            if (tektxHandl != NULL)
            {
                if ((TRANSPORT_MASK(VENDOR_OWNING_TRANSPORT(context))
                    & ITS_ISUP) == ITS_ISUP)
                {
                    if (NMSOpenISUP(tektxHandl) != ITS_SUCCESS)
                    {
                        printf("ISUP BindError: Unable to bind the ISUP\n");
                    }
                    loadFlag = 0;
                }
            }
#if defined(ENABLE_ISUP_INDICS)
            /* Bind to ISUP */
            if (tektxHandl != NULL)
            {
                if ((TRANSPORT_MASK(VENDOR_OWNING_TRANSPORT(context))
                    & ITS_ISUP) == ITS_ISUP)
                {
                    if (NMSOpenISUP(tektxHandl) != ITS_SUCCESS)
                    {
                        printf("ISUP BindError: Unable to bind the ISUP\n");
                    }
                    loadFlag = 0;
                }
            }
#endif
            break;

        case VMI_STATUS_REQUEST:
            /* TODO */
            break;

        default:
           break;
     }
     
     if (hmiRet != SUCCESS)
     {
          SS7RM_CLASS_TERM_EVENT_NOTIFY(rmHelper)(SS7RM_PARTIAL_FAILURE);
     }

     /* Destroy the CTA Context. All currently opened services are
     ** closed.
     */

     if (vmiArg->vmiHandleId != 1)
     {
         hmiRet = ctaDestroyQueue(vmiArg->ctxHandle->vmiRecvQueue);
         VMI_ShowError( "ctaDestroyQueue (SYN Queue)", hmiRet );
     }
     vmiArg->ctxHandle->busy = ITS_FALSE; 
     
     free(vmiArg);

     ITS_EVENT_TERM(&itsEvent);

     return;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Don't know.
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
VMI_ReceiverDispatcher(TPOOL_THREAD *pThread, void *arg)
{
    ITS_BOOLEAN finish = ITS_FALSE;
    CTA_EVENT hmiEvent;
    DWORD vmiRet;
    int ret;

    VMI_CtxHandle *ctxHandle = (VMI_CtxHandle *) arg;

    ctxHandle->busy = ITS_TRUE;
    
    ret = VMI_OpenService(ctxHandle, ctxHandle->vmiHandleId, HMI_RCV_EVENTS);

    if (ret != ITS_SUCCESS)
    {
        printf("VMI_OpenService has Failed\n");
        /* exit the thread */
        return;
    }

    while (!TPOOL_THREAD_EXIT(pThread) & !finish)
    {
        /* Check for the thread exit status every 10 seconds */
        vmiRet = ctaWaitEvent(ctxHandle->vmiRecvQueue, 
                              &hmiEvent, CTA_WAIT_FOREVER /*10000*/);
        VMI_ShowError( "VMI_ReceiverDispatcher: ctaWaitEvent on ASYN Queue", 
                       vmiRet );

        if (vmiRet != SUCCESS)
        {
            /*printf("\nctaWaitEvent on event ASYN Receiver Queue has failed\n");*/
            TIMERS_Sleep(2);
            return;
        }

        if (hmiEvent.id == CTAEVN_WAIT_TIMEOUT)
            continue;

        if (hmiEvent.id == HMI_EVN_STARTING)
        {
            /* Rebind the application to MTP3 */
            if (NMSInitializeMTP3(tektxHandl) != ITS_SUCCESS)
            {
                printf("MTP3BindError: Unable to bind the application\n");
            }
        }

        printf("VMI_ReceiverDispatcher: hmiEvent.id = 0x%08X\n",
               (unsigned)hmiEvent.id);

        NotifyOnHmiEvent(hmiEvent.id);

        if (hmiEvent.id == HMI_EVN_HALTED)
        {
            /* The application must call VMI_Terminate() */
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Send to a registered instance.
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
VMI_SendToRegisteredInstance(ITS_EVENT *itsEvent)
{
    int ret = 0;
    int i;
    ITS_USHORT dest;

    for(i = 0; i < VMI_MAX_INSTANCE; i++)
    {
        if (VMI_InstanceTable[i] != -1)
        {
            dest = (ITS_USHORT) VMI_InstanceTable[i];
            ret = TRANSPORT_PutEvent(dest, itsEvent);
        }        
    }

    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Wait for an event.
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
VMI_WaitForEventWithReason(CTAQUEUEHD vmiRecvQueue, 
                           DWORD eventId,
                           DWORD eventVal)
{
    CTA_EVENT event = { 0 };

    /* Wait for the service manager and services to be opened asynchronously */
    do
    {
        ctaWaitEvent( vmiRecvQueue, &event, CTA_WAIT_FOREVER ); 
    }
    while (event.id != eventId);
      
    if (event.value != eventVal)
    {
        printf ("Opening services failed: val=0x%x\n", (int) event.value );   
        return ITS_ENOMEM;
    }

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Convert an HMI return code.
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
HmiToVmiRtnCode(DWORD hmiRtnCode)
{
    switch (hmiRtnCode)
    {
    case SUCCESS:
        return (ITS_OCTET) VMI_SUCCESS; 

    case HMI_ERR_CLOSED:
        return (ITS_OCTET) VMI_ERR_CLOSED; 

    case HMI_ERR_BADCMD:
        return (ITS_OCTET) VMI_ERR_BADCMD; 

    case  HMI_ERR_TIMEOUT:
        return (ITS_OCTET) VMI_ERR_TIMEOUT; 

    case HMI_ERR_INTERROR:
        return (ITS_OCTET) VMI_ERR_INTERROR; 

    case   HMI_ERR_INVHANDLE:
        return (ITS_OCTET) VMI_ERR_INVHANDLE; 

    case HMI_ERR_REFUSED:
        return (ITS_OCTET) VMI_ERR_REFUSED; 

    case HMI_ERR_NOMEM:
        return (ITS_OCTET) VMI_ERR_NOMEM; 

    default:
       return 0;
    }
} 

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Convert an HMI event code
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
HmiEvtIdToVmiEvtId(DWORD hmiEventId)
{
    switch (hmiEventId)
    {
    case  HMI_EVN_ISOLATED:
        return (ITS_OCTET)  VMI_EVN_ISOLATED; 

    case HMI_EVN_CONNECTED:
        return (ITS_OCTET) VMI_EVN_CONNECTED; 

    case HMI_EVN_NOWPRIMARY:
        return (ITS_OCTET) VMI_EVN_NOWPRIMARY; 

    case HMI_EVN_BRDDEAD:
        return (ITS_OCTET)  VMI_EVN_BRDDEAD; 

    case  HMI_EVN_TASKDEAD:
        return (ITS_OCTET)  VMI_EVN_TASKDEAD; 

    case  HMI_EVN_HALTED:
        return (ITS_OCTET)  VMI_EVN_HALTED; 

    case  HMI_EVN_LOADING:
        return (ITS_OCTET)  VMI_EVN_LOADING; 

    case  HMI_EVN_NOWBACKUP:
        return (ITS_OCTET)  VMI_EVN_NOWBACKUP; 

    case  HMI_EVN_NOWSTANDALONE:
        return (ITS_OCTET)  VMI_EVN_NOWSTANDALONE; 

    case HMI_EVN_STARTING:
        return (ITS_OCTET) VMI_EVN_STARTING; 

    case  HMI_EVN_CONFLICT:
        return (ITS_OCTET)  VMI_EVN_CONFLICT; 

    case  HMI_EVN_SERVICE_DOWN:
        return (ITS_OCTET)  VMI_EVN_SERVICE_DOWN; 

    default:
        printf("Unknown hmiEvent.id\n");
        return 0;
    }
} 

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Notification to RM
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
NotifyOnHmiEvent(DWORD hmiEventId)
{
    switch (hmiEventId)
    {
    case HMI_EVN_ISOLATED:
         printf("\n HMI EVN ISOLATED \n");
         fflush(stdout);
         break;

    case HMI_EVN_CONNECTED:
         printf("\n HMI EVN CONNECTED \n");
         fflush(stdout);
         break;

    case HMI_EVN_NOWPRIMARY:
         printf("\n HMI EVN NOW PRIMARY \n");
         fflush(stdout);
         SS7RM_CLASS_STACK_TO_ENGINE_NOTIFY(rmHelper)(SS7_PRIMARY_STATE); 
         break;

    case HMI_EVN_BRDDEAD:
         printf("\n HMI EVN BOARD DEAD \n");
         fflush(stdout);
         SS7RM_CLASS_TERM_EVENT_NOTIFY(rmHelper)(SS7RM_TOTAL_FAILURE);
         break;

    case HMI_EVN_TASKDEAD:
         printf("\n HMI EVN TASK DEAD \n");
         fflush(stdout);
         SS7RM_CLASS_TERM_EVENT_NOTIFY(rmHelper)(SS7RM_TOTAL_FAILURE);
         break;

    case HMI_EVN_HALTED:
         printf("\n HMI EVN HALTED \n");
         fflush(stdout);
         SS7RM_CLASS_TERM_EVENT_NOTIFY(rmHelper)(SS7RM_PARTIAL_FAILURE);
         break;

    case HMI_EVN_LOADING:
         printf("\n HMI EVN LOADING \n");
         fflush(stdout);
         break;

    case HMI_EVN_NOWBACKUP:
         printf("\n HMI EVN NOW BACKUP \n");
         fflush(stdout);
         SS7RM_CLASS_STACK_TO_ENGINE_NOTIFY(rmHelper)(SS7_SECONDARY_STATE); 
         break;

    case HMI_EVN_NOWSTANDALONE:
         printf("\n HMI EVN NOW STANDALONE \n");
         fflush(stdout);
         break;

    case HMI_EVN_STARTING:
         printf("\n HMI EVN STARTING \n");
         fflush(stdout);
         break;

    case HMI_EVN_CONFLICT:
         printf("\n HMI EVN CONFLICT \n");
         fflush(stdout);
         break;

    case HMI_EVN_SERVICE_DOWN:
         printf("\n HMI EVN SERVICE DOWN \n");
         fflush(stdout);
         SS7RM_CLASS_TERM_EVENT_NOTIFY(rmHelper)(SS7RM_TOTAL_FAILURE);
         break;

    default:
         printf("\n HMI EVN UNKNOWN \n");
         fflush(stdout);
         break;
    }
} 

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Display error text.
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
VMI_ShowError( char *preface, DWORD errcode )
{    
    char text[ITS_PATH_MAX];    

    ctaGetText( NULL_CTAHD, errcode, text, sizeof(text) );    
    printf( "\t%s: %s\n", preface, text );
}

/*
 * RM class record.
 */
SS7RM_ClassRec itsNMS_RMClassRec =
{
    /* core */
    {
        NULL,                       /* superclass */
        0,                          /* instance size */
        ITS_FALSE,                  /* not initted */
        0,                          /* initial ref count */
        SS7RM_CLASS_NAME,           /* class name: replace with your vendor */
        VMI_Initialize,             /* no class init */
        VMI_Terminate,              /* no class dest */
        ITS_CLASS_PART_NO_INIT,     /* class part init */
        ITS_CLASS_PART_NO_DEST,     /* class part destroy */
        ITS_INST_NO_CONST,          /* no instantiate */
        ITS_INST_NO_DEST,           /* no destroy */
        NULL                        /* extension */
    },
    /* RM */
    {
        NULL,                       
        VMI_SendPrimitive,              
        NULL
    }
};

SS7DLLAPI ITS_Class itsNMSRM_Class = (ITS_Class)&itsNMS_RMClassRec;

#endif /* INCLUDE_VMI */
