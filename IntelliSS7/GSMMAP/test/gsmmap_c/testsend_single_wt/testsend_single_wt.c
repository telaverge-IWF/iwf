#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <its.h>
#include <its_app.h>

#include <its_tq_trans.h>
#include <its_thread.h>
#include <its_timers.h>
#include <its_route.h>
#include <its_trace.h>
#include <its_worker.h>

#if defined(USE_INTELLINET_STACK)
    #include <its_ss7_stubs.h>
    #include <its_ss7_trans.h>
#endif

#include <tcap.h>

#include <asn_common.h>

#include <GSMMAP.h>
#include <map_v4_its_feature_class_c.h>
#include <map_v4_insert_subscriber_data_arg_c.h>

/* ISUP linking functions not defined */

int ISUP_SetVariant_CCITT() { return 0; }
int CCITT_CallTable;
int CCITT_ISUP_Variant() { return 0; }
int ISUP_TlvEventToL3Message_CCITT() { return 0; }
int ISUP_L3MessageToTlvEvent_CCITT() { return 0; }
int ComputeMSize() { return 0; }

/* 
 *  Helper functions declaration
 */

int TEST_SendGSMMAPInvoke(int, ITS_USHORT, ITS_HANDLE);
int TEST_DecodeGSMMAPResult( TCAP_CPT*, ITS_HANDLE);
int InterpretOperationInsertSubscriberDataArg(ITS_OCTET* octetArray, size_t size);
int BuildOperationInsertSubscriberDataArg(ITS_OCTET** octetArray, size_t* size);
void HandleTcapMsg(TPOOL_THREAD *s, void *arg);

/*
 *  Define LocalPool structure
 *
 *  Define border and worker threads initial instance number
 */

typedef struct
{
    TPOOL   pool;
    int     count;
}
LocalPool;

#define FIRST_BORDER    2
#define FIRST_WORKER    100

/*
 *  two pools. One is the worker pool, the other is the border pool       
 */
static LocalPool*   borderPool = NULL;
static LocalPool*   workerPool = NULL;

static int dispatcherPoolSize = 1;

/*
 *
 *  Definitions for SCCP addresses.
 *
 */
SCCP_ADDR originatingAddr;
SCCP_ADDR destinationAddr; 

#define SCCP_ADDR_INDICATOR (SCCP_CPA_ROUTE_NAT |   \
                             SCCP_CPA_ROUTE_SSN |   \
                             SCCP_CPA_HAS_PC    |   \
                             SCCP_CPA_HAS_SSN)

#define LOCAL_PC    0
#define LOCAL_SSN   3

#define REMOTE_PC   0
#define REMOTE_SSN  4

/*
 *  GSMMAP and Error Messages
 */
#define TEST_MIN_MSG        0
#define TEST_INSSUBSDATA    TEST_MIN_MSG + 0 /* insertSubscriberData */
#define TEST_NOT_IMPL       TEST_MIN_MSG + 99

/* Synchronization object (semaphore) used to synchronize worker threads */
ITS_SEMAPHORE sema_wait_for_dispatch;

/*------------------------------------------------------------------------------
 *
 *  Simple break handler (specific for WIN32 and Unix).
 *
 *------------------------------------------------------------------------------*/

#if defined(WIN32)
static BOOL WINAPI breakHandler(DWORD ctrlType)
{
    ITS_GlobalStop();
    return 0;
}
#else
static void exitHandler(int sig)
{
    ITS_GlobalStop();
    eiit(ITS_SUCCESS);
}
#endif

/*------------------------------------------------------------------------------
 *
 * Create one thread in the border pool
 *
 *------------------------------------------------------------------------------*/

TPOOL_THREAD *
CreateBorderPoolThread(TPOOL* pool, int stackSize)
{
    LocalPool* p = (LocalPool *)pool;
    WORKER_Control *worker;

    /* The name of the the Border thread has to match with ini section name */
    worker = WORKER_InitWorker(stackSize, "Border0",
                               ITS_SCCP | ITS_TCAP | ITS_TRANSPORT_FIFO|
                               ITS_TRANSPORT_DELAY_CREATE,
                               (ITS_USHORT)p->count);
    p->count++;

    return ((TPOOL_THREAD *)worker);
}

/*------------------------------------------------------------------------------
 *
 * Create one thread in the worker pool
 *
 *------------------------------------------------------------------------------*/

TPOOL_THREAD *
CreateWorkerPoolThread(TPOOL* pool, int stackSize)
{
    LocalPool* p = (LocalPool *)pool;
    WORKER_Control *worker;

    worker = WORKER_InitWorker(stackSize, "A Worker",
                               ITS_TCAP |
                               ITS_SCCP |
                               ITS_TRANSPORT_TQUEUE,
                               (ITS_USHORT)p->count);

    p->count++;

    return ((TPOOL_THREAD *)worker);
}

/*------------------------------------------------------------------------------
 *
 *  Standard border loop
 *
 *------------------------------------------------------------------------------*/

void
BorderDispatch(TPOOL_THREAD* thr, void *arg)
{
    WORKER_Control* work = (WORKER_Control *)thr;
    ITS_HANDLE handle;
    ITS_EVENT event;

    /*
     * getting NULL here is a fatal error
     */
    assert((handle = ITS_Initialize(work->mask,
                               work->instance)) != NULL);
    
    /*
     * dispatcher loop.  Take all incoming messages and send them to SCCP.
     */
    while (WORKER_GetNextEvent(work, &event) == ITS_SUCCESS) //!work->tInfo.exit
    {
        /*
         * border transports implement MTP3.
         */
        event.src = ITS_MTP3_SRC;

        /*
         * this example is only handling SCCP messages.  ISUP would
         * be handled similarly.
         */
        if (TRANSPORT_PutEvent(ITS_SCCP_SRC, &event) != ITS_SUCCESS)
        {
            printf("Couldn't send SCCP message to TCAP\n");
        }
    }
    
    /*
     * this is good practice
     */
    ITS_Terminate(handle);
}


/*------------------------------------------------------------------------------*/
/*                              Entry Point                                     */
/*------------------------------------------------------------------------------*/

int
main(int argc, char** argv)
{
    int result, i;
    TPOOL_THREAD* iThread;
    WORKER_Control* work;

    printf("\nBegin GSM MAP with toolkit send example...\n");

#if defined(WIN32)
    SetConsoleCtrlHandler(breakHandler, TRUE);
#else
    signal(SIGINT, exitHandler);
#endif /* defined(WIN32) */
       
    /*
     *
     *  Set Application Name
     *
     */

    APPL_SetName("test_send_wt");

#if defined(USE_INTELLINET_STACK)

    /*-----------------------------------------------------------------------
     *
     *  Using IntelliSS7 stack (add that feature).
     *
     *-----------------------------------------------------------------------*/

    result = ITS_AddFeature(itsINTELLISS7_Class);

    if (result != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(result));

        exit(EXIT_FAILURE);
    }

#endif /* defined(USE_INTELLINET_STACK) */

    result = ITS_AddFeature(itsASN_C_RUNTIME_Class);

    if (result != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(result));

        exit(EXIT_FAILURE);
    }

    result = ITS_AddFeature(itsMAP_V4_Class);

    if (result != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(result));

        exit(EXIT_FAILURE);
    }

    /*
     *  IntelliSS7 subsystems initialization (including licensing).
     */

    result = ITS_GlobalStart(ITS_TCAP | ITS_SCCP);
    if (result != ITS_SUCCESS)
    {
        printf("\nITS_GlobalStart() failed!");
        exit(0);
    }

    /*
     *  Create the worker pool BEFORE the border pool.  This
     *  will avoid the race condition of not having workers
     *  available when a border receives a message.
     *
     *  o  Allocate worker thread pool
     *
     *  o  Create worker thread pool
     *
     *  o  Create worker threads in the pool
     */

    workerPool = (LocalPool *)calloc(1, sizeof(LocalPool));
    if (workerPool == NULL)
    {
        printf("Out of memory\n");

        return (EXIT_FAILURE);
    }
    workerPool->count = FIRST_WORKER;

    if (TPOOL_InitPool(&workerPool->pool) != ITS_SUCCESS)
    {
        printf("Couldn't initialize the thread pool\n");

        return (EXIT_FAILURE);
    }

    if (TPOOL_CreatePool(&workerPool->pool, 5, 0,
                         CreateWorkerPoolThread) != ITS_SUCCESS)
    {
        printf("Couldn't create worker pool.\n");

        return (EXIT_FAILURE);
    }

    /*
     *  o   allocate border pool
     *  
     *  o   Create border transport pool.
     *
     *  o   Create border transport threads in the pool.
     * 
     *  o   Start the border dispatcher.
     */

    borderPool = (LocalPool *)calloc(1, sizeof(LocalPool));
    if (borderPool == NULL)
    {
        printf("Out of memory\n");

        return (EXIT_FAILURE);
    }
    borderPool->count = FIRST_BORDER;

    if (TPOOL_InitPool(&borderPool->pool) != ITS_SUCCESS)
    {
        printf("Couldn't initialize the thread pool\n");

        return (EXIT_FAILURE);
    }

    if (TPOOL_CreatePool(&borderPool->pool, dispatcherPoolSize, 0,
                         CreateBorderPoolThread) != ITS_SUCCESS)
    {
        printf("Couldn't create worker pool.\n");

        return (EXIT_FAILURE);
    }

    /* Start the border dispatchers. */
    TPOOL_Dispatch(&borderPool->pool, BorderDispatch, NULL);

    /*
     *  Local & Remote PC & SSN 
     */

    memset((char *)&destinationAddr, 0, sizeof(SCCP_ADDR));
    memset((char *)&originatingAddr, 0, sizeof(SCCP_ADDR));

    result = SCCP_EncodeAddr(&originatingAddr, 
                             SCCP_ADDR_INDICATOR, 
                             LOCAL_PC, 
                             (ITS_OCTET)LOCAL_SSN, 
                             NULL, 
                             0);

    if (result != ITS_SUCCESS)
    {
        printf("\n Failed to set SCCP Origination Address. Error is: %s .",
               ITS_GetErrorText(result));
        printf("\n Quiting...");
        ITS_GlobalStop();
        exit(0);
    }

    result = SCCP_EncodeAddr(&destinationAddr, 
                             SCCP_ADDR_INDICATOR, 
                             REMOTE_PC, 
                             (ITS_OCTET)REMOTE_SSN, 
                             NULL, 
                             0);

    if (result != ITS_SUCCESS)
    {
        printf("\n Failed to set SCCP Destination Address. Error is: %s .",
               ITS_GetErrorText(result));
        printf("\n Quiting...");
        ITS_GlobalStop();
        exit(0);
    }

    /*
     *  o  Get the available worker thread.
     *
     *  o  Invoke the unit of work.
     */

    /* Create semaphore to syncronize worker threads */
    SEMA_CreateSemaphore(&sema_wait_for_dispatch, 0);
    for(i = 0; i < 1; i++)
    {
        SEMA_PostSemaphore(&sema_wait_for_dispatch);

        assert(TPOOL_GetFirstAvailThread(&workerPool->pool,
                                         &iThread) == ITS_SUCCESS);

        work = (WORKER_Control *)iThread;
       
        assert(TPOOL_DispatchOnThread(iThread,
                                      HandleTcapMsg,
                                      NULL) == ITS_SUCCESS); 

        SEMA_WaitSemaphore(&sema_wait_for_dispatch);
    }
    /* We are done using the semaphore */
    SEMA_DeleteSemaphore(&sema_wait_for_dispatch);

    while (1)
    {
        TIMERS_Sleep(1);
    }

    /*
     *  IntelliSS7 termination.
     */

    ITS_GlobalStop();

    ITS_RemFeature(itsASN_C_RUNTIME_Class);

    ITS_RemFeature(itsMAP_V4_Class);

    printf("\nEnd of GSM MAP with toolkit send example.\n");
    
    return EXIT_SUCCESS;
}

/*------------------------------------------------------------------------------
 *
 *  Decode GSM Map Return Result
 *
 *------------------------------------------------------------------------------*/

int 
TEST_DecodeGSMMAPResult( TCAP_CPT *cpt, ITS_HANDLE handle )
{
    int ret = 0;

    if (cpt->ptype != TCPPT_TC_RESULT_L && cpt->ptype != TCPPT_TC_RESULT_NL)
    {
        printf("Received component type 0x02x - not an Result."
               " Will not try to decode. \n", cpt->ptype);
        return ITS_BADTCAPMESSAGE;
    }

    if (cpt->u.result.param.len <= 2)
    {
        printf("Received component type 0x%02x (Opcode %d) does not have"
               " any parameters. Will not process any further.\n",
               cpt->ptype, cpt->u.result.operation.data[2]);
        return ITS_BADTCAPMESSAGE;
    }

    switch(cpt->u.result.operation.data[2])
    {
        case (GSMMAP_OP_insertSubscriberData):
            printf("Going to decode InsertSubscriberData Result.\n");
            InterpretOperationInsertSubscriberDataArg(
                                                cpt->u.result.param.data, 
                                                cpt->u.result.param.len);
        
        case (GSMMAP_OP_sendIdentification):
        case (GSMMAP_OP_restoreData):
        case (GSMMAP_OP_activateTraceMode):
        case (GSMMAP_OP_deactivateTraceMode):
            /* Should be processed by complete code. */
            break;

        default:
            break;

    } /* switch(opFam) */
    return ret;
}

/*------------------------------------------------------------------------------
 *
 *  Send Insert Subscriber Data invoke component
 *
 *------------------------------------------------------------------------------*/

int
TEST_SendGSMMAPInvoke(int cmdInput, ITS_USHORT instance, ITS_HANDLE handle)
{
    int ret = 0, c;
    TCAP_CPT cpt;
    ITS_EVENT event;    
    ITS_HDR hdr;
    TCAP_DLG dlg;

    /*
     *  Execute GSM MAP operation Insert Subscriber Data:
     *  
     *  o   Allocate new dialogue ID.
     *
     *  o   Register for subsequent message.
     *
     *  o   Build TCAP begin dialogue.
     *
     *  o   Build TCAP invoke component.
     *
     *  o   Call BuildOperationInsertSubscriberDataArg to build GSM MAP 
     *      Insert Subscriber Data operation.
     *
     *  o   Send TCAP invoke component.
     *  
     *  o   Send TCAP begin dialogue.
     */

    memset((char *)&cpt, 0, sizeof(TCAP_CPT));
    memset((char *)&hdr, 0, sizeof(ITS_HDR));
    memset((char *)&dlg, 0, sizeof(TCAP_DLG));
    memset((char *)&event, 0, sizeof(ITS_EVENT));

    hdr.type = ITS_TCAP;
    TCAP_AllocateDialogueId(&hdr.context.dialogue_id);
    printf("dialogue_id allocated = %d.\n", hdr.context.dialogue_id);

    /* Register for subsequent message */ 
    assert(ROUTE_AddApplication(instance, &hdr) == ITS_SUCCESS);

    /* Create begin dialogue and populate it */
    dlg.ptype = TCPPT_TC_BEGIN;
    dlg.u.begin.orig_addr.len = 4;
    dlg.u.begin.dest_addr.len = 4;
    printf("Dest addr copied in: ");
    for (c = 0; c < 4; c++)
    {
        dlg.u.begin.dest_addr.data[c] = destinationAddr.data[c];
        printf(" 0x%02x", dlg.u.begin.dest_addr.data[c]);
    }
    printf("\n");

    printf("Orig addr copied in: ");
    for (c = 0; c < 4; c++)
    {
        dlg.u.begin.orig_addr.data[c] = originatingAddr.data[c];
        printf(" 0x%02x", dlg.u.begin.orig_addr.data[c]);
    }
    printf("\n");
    dlg.u.begin.qos.indicator |= QOSI_RET_OPT;
    dlg.u.begin.cpt_present = 1;

    /* Build invoke component and populate it */
    cpt.ptype = TCPPT_TC_INVOKE;
    cpt.u.invoke.timeout = 15;  /* Set timeout of waiting for response */
    cpt.u.invoke.opClass = 1;

    cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG; /* tag */
    cpt.u.invoke.invoke_id.data[1] = 1; 
    cpt.u.invoke.invoke_id.data[2] = 5; 
    cpt.u.invoke.invoke_id.len = 3;
    cpt.u.invoke.linked_id.len = 0;
    cpt.last_component = 1;

    switch(cmdInput)
    {
        case (TEST_INSSUBSDATA):
        {
            ITS_OCTET* octetArray = NULL;
            size_t size = 0;

            BuildOperationInsertSubscriberDataArg(&octetArray, &size);
            
            memcpy(cpt.u.invoke.param.data, octetArray, size);
            cpt.u.invoke.param.len = size;

			cpt.u.invoke.operation.len = 3;
			cpt.u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
			cpt.u.invoke.operation.data[1] = 1;
			cpt.u.invoke.operation.data[2] = GSMMAP_OP_insertSubscriberData;

            TCAP_SendComponent(handle, &hdr, &cpt);
        }
        break;
        
        default:
        {
            printf("\nNot Implemented yet....\n");
            ret =  TEST_NOT_IMPL;
        }
        break;
    }

    printf("Sending dialogue \n");

    if (ret == ITS_SUCCESS)
    {
        ret = TCAP_SendDialogue(handle, &hdr, &dlg);
    }
    if (ret != ITS_SUCCESS && ret != TEST_NOT_IMPL)
    {       
        printf("Cannot send dialogue \n");
    }
    else if (ret == TEST_NOT_IMPL)
    {
        printf("Nothing send out, as message is not implemented.\n");
    }
    else if (ret == ITS_SUCCESS)
    {
        printf("Dialogue sent \n");
    }
    fflush(stdout);

    return ret;
}

/*------------------------------------------------------------------------------
 *
 *  transport thread : unit of work
 *
 *------------------------------------------------------------------------------*/

void
HandleTcapMsg(TPOOL_THREAD *s, void *arg)
{
    WORKER_Control* self = (WORKER_Control*)s;
    ITS_HANDLE handle;
    ITS_EVENT event;
    TCAP_CPT cpt;
    TCAP_DLG dlg;
    ITS_HDR header;
    int result = ITS_SUCCESS, cmdInput, keepGoing = 1;

    /*
     *  o   Create transport.
     *  
     *  o   Call TEST_SendGSMMAPInvoke function on the operation to send
     */

    /* Getting NULL here is a fatal error */
    assert((handle = ITS_Initialize(self->mask,
                                    self->instance)) != NULL);
    
    /*  Send InsertSubscriberData */
    cmdInput = TEST_INSSUBSDATA; /* InsertSubscriberData */
    result = TEST_SendGSMMAPInvoke(cmdInput, self->instance, handle);
    if (result != ITS_SUCCESS)
    {
        printf("\nProblem sending TCAP dialog, exiting!!!\n");
        return;
    }

    memset((char *)&header, 0, sizeof(ITS_HDR));
    memset((char *)&cpt, 0, sizeof(TCAP_CPT));
    memset((char *)&dlg, 0, sizeof(TCAP_DLG));
    memset((char *)&event, 0, sizeof(ITS_EVENT));

    /*
     *  Receive loop:
     *  
     *  o   Receive TCAP end dialogue.
     *
     *  o   Exit loop, return the thread to the pool.
     */

    while(keepGoing)
    {
        /* Get the Dialog portion of the TCAP message  */
        result = WORKER_GetNextEvent(self, &event);
        if (result != ITS_SUCCESS)
        {
            printf("\nWORKER_GetNextEvent() Error");

            continue;
        }

        if (TCAP_MSG_TYPE(&event) == ITS_TCAP_CPT)
        {
            printf("Received Component\n");

            TCAP_ReceiveComponent(handle, &event, &header, &cpt);
            printf("ptype = 0x%x\n", cpt.ptype);            
            switch(cpt.ptype)
            {
            case TCPPT_TC_RESULT_L:
            {
                /* Decode the parameter set in the component. */
                printf("Received Return Result component.\n");

                TEST_DecodeGSMMAPResult( &cpt, handle );
                break;
            }

            case TCAP_PT_TC_INVOKE_CCITT:
            case TCAP_PT_TC_U_ERROR_CCITT:
            case TCAP_PT_TC_R_REJECT_CCITT:
            case TCAP_PT_TC_RESULT_NL_CCITT:
            case TCAP_PT_TC_L_CANCEL_CCITT:
            case TCAP_PT_TC_U_CANCEL_CCITT:
            case TCAP_PT_TC_L_REJECT_CCITT:
            case TCAP_PT_TC_U_REJECT_CCITT:
                /* Should be processed by complete code. */
                break;
            default:
                /* Should not be reached. */
                break;
            }
        }
        else if (TCAP_MSG_TYPE(&event) == ITS_TCAP_DLG)
        {
            printf("Received Dialogue\n");

            TCAP_ReceiveDialogue(handle, &event, &header, &dlg);
            printf("ptype = 0x%x, dialogue_id = 0x%x\n",
                    dlg.ptype,header.context.dialogue_id);

            switch (dlg.ptype)
            {
            case TCAP_PT_TC_END_CCITT:
                printf("\nEnd dialogue received.\n\n");
                keepGoing = 0;
                /* Should be processed by complete code. */
                break;

            case TCAP_PT_TC_BEGIN_CCITT:
            case TCAP_PT_TC_UNI_CCITT:
            case TCAP_PT_TC_CONTINUE_CCITT:
            case TCAP_PT_TC_P_ABORT_CCITT:
            case TCAP_PT_TC_U_ABORT_CCITT:
            case TCAP_PT_TC_NOTICE_CCITT:
                /* Should be processed by complete code. */
                break;
            default:
                /* Should not be reached. */
                break;
            }
        }
    }
    TPOOL_ReturnToAvailThreads(&workerPool->pool, s);
}

int
BuildOperationInsertSubscriberDataArg(ITS_OCTET** octetArray, size_t* size)
{
    MAP_V4_InsertSubscriberDataArg insertSubscriberDataArg  = NULL;

    ITS_OCTET array1[] = { 0x01U, 0x02U, 0x03U, 0x04U };
    size_t array1Size = 4;

    ITS_OCTET array2[] = { 0x11U, 0x22U, 0x33U, 0x44U, 0x55U };
    size_t array2Size = 5;

    ITS_OCTET array3[] = { 0x66U };
    size_t array3Size = 1;

    ITS_OCTET array4[] = { 0xAAU };
    size_t array4Size = 1;

    ITS_OCTET array5[] = { 0xBBU };
    size_t array5Size = 1;

    ITS_OCTET array6[] = { 0xCCU };
    size_t array6Size = 1;

    ITS_OCTET array7[] = { 0xDDU };
    size_t array7Size = 1;

    ITS_OCTET array8[] = { 0xEEU };
    size_t array8Size = 1;

    ITS_OCTET array9[] = { 0x33U };
    size_t array9Size = 1;

    ITS_OCTET array10[] = { 0x44U };
    size_t array10Size = 1;

    ITS_OCTET array11[] = { 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U };
    size_t array11Size = 8;

    ITS_OCTET array12[] = { 0x11U, 0x22U, 0x33U, 0x44U };
    size_t array12Size = 4;

    ITS_OCTET array13[] = { 0x44U, 0x33U, 0x22U, 0x11U };
    size_t array13Size = 4;

    ITS_BOOLEAN array14[] = { ITS_TRUE, ITS_FALSE, ITS_TRUE, ITS_FALSE, ITS_TRUE, 
                              ITS_FALSE, ITS_TRUE, ITS_FALSE, ITS_TRUE, ITS_FALSE,
                              ITS_FALSE, ITS_TRUE, ITS_FALSE, ITS_TRUE, ITS_FALSE };
    size_t array14Size = 15;

    ITS_BOOLEAN array15[] = { ITS_FALSE, ITS_TRUE, ITS_FALSE, ITS_TRUE };
    size_t array15Size = 4;

    /* Local variables used for encoding and decoding. */

    ASN_Octets octets                   = NULL;
    ASN_EncodeError encodeError         = NULL;
    ASN_DecodeError decodeError         = NULL;

    int res                             = ITS_SUCCESS;

    int encodeErrorCode                 = ITS_SUCCESS;
    const char* encodeErrorText         = NULL;
    const char* encodeExtendedErrorText = NULL;

    /*------------------------------------------------------------------------*/
    /* Populate ASN.1 object to encode.                                       */
    /*------------------------------------------------------------------------*/

    insertSubscriberDataArg = MAP_V4_InsertSubscriberDataArg_ConstructDefault();

    if (insertSubscriberDataArg == NULL)
    {
        return ITS_ENOMEM;
    }

    /* Set imsi. */
    {
        MAP_V4_IMSI imsi = NULL;

        imsi = MAP_V4_TBCD_STRING_ConstructWithArraySize(array1, array1Size);

        if (imsi == NULL)
        {
            return ITS_ENOMEM;
        }

        MAP_V4_InsertSubscriberDataArg_SetImsi(insertSubscriberDataArg, imsi);
    }

    /* Set category. */
    {
        MAP_V4_Category category = NULL;

        category = MAP_V4_Category_ConstructWithArraySize(
                                                        array3,
                                                        array3Size);

        if (category == NULL)
        {
            return ITS_ENOMEM;
        }

        MAP_V4_InsertSubscriberDataArg_SetCategory(
                                        insertSubscriberDataArg, 
                                        category);
    } 

    /* Set subscriberStatus. */
    {
        MAP_V4_SubscriberStatus subscriberStatus = NULL;

        subscriberStatus = MAP_V4_SubscriberStatus_ConstructDefault();

        if (subscriberStatus == NULL)
        {
            return ITS_ENOMEM;
        }

        MAP_V4_SubscriberStatus_SetServiceGranted(subscriberStatus);

        MAP_V4_InsertSubscriberDataArg_SetSubscriberStatus(
                                            insertSubscriberDataArg,
                                            subscriberStatus);
    }

    /* Set bearerServiceList. */
    {
        MAP_V4_BearerServiceList bearerServiceList = NULL;

        bearerServiceList = MAP_V4_BearerServiceList_ConstructDefault();

        if (bearerServiceList == NULL)
        {
            return ITS_ENOMEM;
        }

        /* Insert first elements (type BearerServiceCode). */
        {
            MAP_V4_Ext_BearerServiceCode bearerServiceCode1 = NULL;

            bearerServiceCode1 = 
                MAP_V4_Ext_BearerServiceCode_ConstructWithArraySize(
                                                                array4,
                                                                array4Size);

            if (bearerServiceCode1 == NULL)
            {
                return ITS_ENOMEM;
            }

            res = MAP_V4_BearerServiceList_AddElement(
                                                bearerServiceList, 
                                                bearerServiceCode1);

            if (res != ITS_SUCCESS)
            {
                return res;
            }
        }

        /* Insert second elements (type BearerServiceCode). */
        {
            MAP_V4_Ext_BearerServiceCode bearerServiceCode2 = NULL;

            bearerServiceCode2 = 
                MAP_V4_Ext_BearerServiceCode_ConstructWithArraySize(
                                                                array5,
                                                                array5Size);

            if (bearerServiceCode2 == NULL)
            {
                return ITS_ENOMEM;
            }

            res = MAP_V4_BearerServiceList_AddElement(
                                                bearerServiceList,
                                                bearerServiceCode2);

            if (res != ITS_SUCCESS)
            {
                return res;
            }
        }

        MAP_V4_InsertSubscriberDataArg_SetBearerServiceList(
                                                insertSubscriberDataArg,
                                                bearerServiceList);
    }

    /* Set teleserviceList. */
    {
        MAP_V4_TeleserviceList teleserviceList = NULL;

        teleserviceList = MAP_V4_TeleserviceList_ConstructDefault();

        if (teleserviceList == NULL)
        {
            return ITS_ENOMEM;
        }

        /* Set teleserviceCode1 */
        {
            MAP_V4_Ext_TeleserviceCode teleserviceCode1 = NULL;

            teleserviceCode1 = 
                MAP_V4_Ext_TeleserviceCode_ConstructWithArraySize(
                                                                array6,
                                                                array6Size);

            if (teleserviceCode1 == NULL)
            {
                return ITS_ENOMEM;
            }

            res = MAP_V4_TeleserviceList_AddElement(
                                                teleserviceList, 
                                                teleserviceCode1);

            if (res != ITS_SUCCESS)
            {
                return res;
            }
        }

        /* Set teleserviceCode2 */
        {
            MAP_V4_Ext_TeleserviceCode teleserviceCode2 = NULL;

            teleserviceCode2 = 
                MAP_V4_Ext_TeleserviceCode_ConstructWithArraySize(
                                                            array7,
                                                            array7Size);

            if (teleserviceCode2 == NULL)
            {
                return ITS_ENOMEM;
            }

            res = MAP_V4_TeleserviceList_AddElement(teleserviceList, teleserviceCode2);

            if (res != ITS_SUCCESS)
            {
                return res;
            }

        }

        /* Set teleserviceCode3 */
        {
            MAP_V4_Ext_TeleserviceCode teleserviceCode3 = NULL;

            teleserviceCode3 = MAP_V4_Ext_TeleserviceCode_ConstructWithArraySize(
                                                            array8,
                                                            array8Size);

            if (teleserviceCode3 == NULL)
            {
                return ITS_ENOMEM;
            }

            res = MAP_V4_TeleserviceList_AddElement(teleserviceList, teleserviceCode3);

            if (res != ITS_SUCCESS)
            {
                return res;
            }
        }

        MAP_V4_InsertSubscriberDataArg_SetTeleserviceList(
                                                    insertSubscriberDataArg,
                                                    teleserviceList);
    }

    /* Set provisionedSS (type SS_InfoList). */
    {
        MAP_V4_Ext_SS_InfoList ext_SS_InfoList = NULL;

        ext_SS_InfoList = MAP_V4_Ext_SS_InfoList_ConstructDefault();

        if (ext_SS_InfoList == NULL)
        {
            return ITS_ENOMEM;
        }

        /* Insert 2 elements (type SS_Info). */
        /* First ext_SS_Info1. */
        {
            MAP_V4_Ext_SS_Info ext_SS_Info1 = NULL;

            ext_SS_Info1 = MAP_V4_Ext_SS_Info_ConstructDefault();

            if (ext_SS_Info1 == NULL)
            {
                return ITS_ENOMEM;
            }

            /* First element choice is forwardingInfo. */
            {
                MAP_V4_Ext_ForwInfo forwardingInfo = NULL;

                forwardingInfo = MAP_V4_Ext_ForwInfo_ConstructDefault();

                if (forwardingInfo == NULL)
                {
                    return ITS_ENOMEM;
                }

                /* Set sS_Code */
                {
                    MAP_V4_SS_Code sS_Code = NULL;
                    sS_Code = MAP_V4_SS_Code_ConstructWithArraySize(
                                                                array9,
                                                                array9Size);

                    if (sS_Code == NULL)
                    {
                        return ITS_ENOMEM;
                    }

                    MAP_V4_Ext_ForwInfo_SetSs_Code(forwardingInfo, sS_Code);
                }

                /* Set forwardingFeatureList */
                {
                    MAP_V4_Ext_ForwFeatureList forwardingFeatureList = NULL;

                    forwardingFeatureList = 
                        MAP_V4_Ext_ForwFeatureList_ConstructDefault();

                    if (forwardingFeatureList == NULL)
                    {
                        return ITS_ENOMEM;
                    }
                
                    /* Insert 1 element (type ForwardingFeature). */
                    {
                        MAP_V4_Ext_ForwFeature forwardingFeature = NULL;

                        forwardingFeature = 
                            MAP_V4_Ext_ForwFeature_ConstructDefault();

                        /* Set basicServiceCode. */
                        {
                            MAP_V4_Ext_BasicServiceCode basicServiceCode 
                                                                    = NULL;
                            basicServiceCode = 
                                MAP_V4_Ext_BasicServiceCode_ConstructDefault();

                            if (basicServiceCode == NULL)
                            {
                                return ITS_ENOMEM;
                            }

                            /* Set bearerServiceCode. */
                            {
                                MAP_V4_Ext_BearerServiceCode bearerServiceCode
                                                                    = NULL;

                                bearerServiceCode = MAP_V4_Ext_BearerServiceCode_ConstructWithArraySize(
                                                array10,
                                                array10Size);

                                if (bearerServiceCode == NULL)
                                {
                                    return ITS_ENOMEM;
                                }

                                MAP_V4_Ext_BasicServiceCode_SetChoiceExt_BearerService(
                                                        basicServiceCode, 
                                                        bearerServiceCode);
                            }

                            MAP_V4_Ext_ForwFeature_SetBasicService(
                                                        forwardingFeature,
                                                        basicServiceCode);
                        }

                        /* Set ext_SS_Status */
                        {
                            MAP_V4_Ext_SS_Status ext_SS_Status = NULL;

                            ext_SS_Status = 
                                MAP_V4_Ext_SS_Status_ConstructWithArraySize(
                                                                        array10,
                                                                        array10Size);

                            if(ext_SS_Status == NULL)
                            {
                                return ITS_ENOMEM;
                            }

                            MAP_V4_Ext_ForwFeature_SetSs_Status(
                                                        forwardingFeature, 
                                                        ext_SS_Status);
                        }
                        /* Set iSDN_SubaddressString. */
                        {
                            MAP_V4_ISDN_SubaddressString iSDN_SubaddressString
                                                                    = NULL;

                            iSDN_SubaddressString = 
                                MAP_V4_ISDN_SubaddressString_ConstructWithArraySize(
                                                            array11,
                                                            array11Size);

                            if (iSDN_SubaddressString == NULL)
                            {
                                return ITS_ENOMEM;
                            }

                            MAP_V4_Ext_ForwFeature_SetForwardedToSubaddress(
                                                        forwardingFeature, 
                                                        iSDN_SubaddressString);
                        }

                        res = MAP_V4_Ext_ForwFeatureList_AddElement(
                                                                forwardingFeatureList,
                                                                forwardingFeature);

                        if (res != ITS_SUCCESS)
                        {
                            return res;
                        }
                    }

                    MAP_V4_Ext_ForwInfo_SetForwardingFeatureList(
                                                        forwardingInfo,
                                                        forwardingFeatureList);
                }

                MAP_V4_Ext_SS_Info_SetChoiceForwardingInfo(
                                                        ext_SS_Info1,
                                                        forwardingInfo);
            }

            res = MAP_V4_Ext_SS_InfoList_AddElement(
                                                ext_SS_InfoList,
                                                ext_SS_Info1);

            if (res != ITS_SUCCESS)
            {
                return res;
            }
        }
        
        /* Second element. */
        {
            MAP_V4_Ext_SS_Info ext_SS_Info2 = NULL;

            ext_SS_Info2 = MAP_V4_Ext_SS_Info_ConstructDefault();

            if (ext_SS_Info2 == NULL)
            {
                return ITS_ENOMEM;
            }

            /* Second element choice is cug-Info. */
            {
                MAP_V4_CUG_Info cUG_Info = NULL;

                cUG_Info = MAP_V4_CUG_Info_ConstructDefault();

                if (cUG_Info == NULL)
                {
                    return ITS_ENOMEM;
                }

                /* Set CUG-SubscriptionList. */
                {
                    MAP_V4_CUG_SubscriptionList cUG_SubscriptionList = NULL;

                    cUG_SubscriptionList = MAP_V4_CUG_SubscriptionList_ConstructDefault();

                    if (cUG_SubscriptionList == NULL)
                    {
                        return ITS_ENOMEM;
                    }

                    MAP_V4_CUG_Info_SetCug_SubscriptionList(
                                                        cUG_Info,
                                                        cUG_SubscriptionList);
                }

                MAP_V4_Ext_SS_Info_SetChoiceCug_Info(
                                                ext_SS_Info2,
                                                cUG_Info);
            }

            res = MAP_V4_Ext_SS_InfoList_AddElement(
                                                ext_SS_InfoList,
                                                ext_SS_Info2);

            if (res != ITS_SUCCESS)
            {
                return res;
            }
        }

        MAP_V4_InsertSubscriberDataArg_SetProvisionedSS(
                                                insertSubscriberDataArg, 
                                                ext_SS_InfoList);
    }

    /* Set odb-Data. */
    {
        MAP_V4_ODB_Data oDB_Data = NULL;

        oDB_Data = MAP_V4_ODB_Data_ConstructDefault();

        if (oDB_Data == NULL)
        {
            return ITS_ENOMEM;
        }

        /* Set oDB_GeneralData, oDB_HPLMN_Data. */
        {
            MAP_V4_ODB_GeneralData oDB_GeneralData  = NULL;
            MAP_V4_ODB_HPLMN_Data oDB_HPLMN_Data = NULL;

            oDB_GeneralData = MAP_V4_ODB_GeneralData_ConstructWithArraySize(
                                                                    array14, 
                                                                    array14Size);

            if (oDB_GeneralData == NULL)
            {
                return ITS_ENOMEM;
            }


            MAP_V4_ODB_Data_SetOdb_GeneralData(oDB_Data, oDB_GeneralData);

            oDB_HPLMN_Data = MAP_V4_ODB_HPLMN_Data_ConstructWithArraySize(
                                                            array15,
                                                            array15Size);

            if (oDB_HPLMN_Data == NULL)
            {
                return ITS_ENOMEM;
            }
        
            MAP_V4_ODB_Data_SetOdb_HPLMN_Data(oDB_Data, oDB_HPLMN_Data);

        }

        MAP_V4_InsertSubscriberDataArg_SetOdb_Data(
                                    insertSubscriberDataArg, 
                                    oDB_Data);
        }

    /*------------------------------------------------------------------------*/
    /* Encode ASN.1 object.                                                   */
    /*------------------------------------------------------------------------*/

    res = MAP_V4_InsertSubscriberDataArg_Encode(
                                insertSubscriberDataArg, 
                                &octets, 
                                &encodeError);

    if (res == ITS_E_ASN_ENCODE_ERROR)
    {
        /*  
         *  Status:                                              
         *                                                       
         *  octets == NULL.                                      
         *  encodeError != NULL. Must be destructed by end-user. 
         */


        /* Retrieve and print encode error code. */

        encodeErrorCode = 
            ASN_EncodeError_GetError(encodeError);

        printf(
            "\nEncode error code is <%d>.\n\n", 
            encodeErrorCode);


        /* 
         *  Retrieve and print encode error text (freed automatically when the
         *  encodeError object is destructed).                               
         */

        encodeErrorText = 
            ASN_EncodeError_GetErrorText(encodeError);

        if (encodeErrorText == NULL)
        {
            /* Error: out of memory. */
        }

        printf(
            "\nEncode error text is <%s>.\n\n", 
            encodeErrorText);


        /* 
         *  Retrieve and print extended encode error text (freed automatically
         *  when the encodeError object is destructed).
         */

        encodeExtendedErrorText = 
            ASN_EncodeError_GetExtentedErrorText(encodeError);

        printf(
            "\nEncode error extended text is <%s>.\n\n", 
            encodeExtendedErrorText);


        /* Object encodeError must be destructed by end-user. */

        ASN_EncodeError_Destruct(encodeError);


        MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);

        return res;
    }
    else if (res != ITS_SUCCESS)
    {
        MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);

        return res;
    }

    /*------------------------------------------------------------------------*/
    /* Print contents of ASN.1 encoded value.                                 */
    /*------------------------------------------------------------------------*/

    printf("\nPrinting ASN.1 encoded value...\n\n");

    ASN_Octets_Print(octets);

    printf("\n");

    *size = ASN_Octets_GetSize(octets);

    /* return address has to be dynamically allocated */
    *octetArray = (ITS_OCTET*)calloc(ASN_Octets_GetSize(octets), sizeof(ITS_OCTET));

    if (*octetArray == NULL)
    {
        MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);
        ASN_Octets_Destruct(octets);

        return ITS_ENOMEM;
    }

    memcpy(*octetArray, ASN_Octets_GetArray(octets), ASN_Octets_GetSize(octets));

    MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);
    ASN_Octets_Destruct(octets);

    return ITS_SUCCESS;
}

/*------------------------------------------------------------------------------
 *
 *  o   Allocate a pointer insertSubscriberDataArg to 
 *      MAP_V4_InsertSubscriberDataArg_ObjRec.
 *
 *  o   Construct an ASN_Octets object from the array.
 *
 *  o   Decode the ASN_Octets object into parameter list 
 *      -> insertSubscriberDataArgAfter
 *
 *  o   Printf the decoded object
 *
 *------------------------------------------------------------------------------*/
int
InterpretOperationInsertSubscriberDataArg(ITS_OCTET* octetArray, size_t size)
{
    ASN_EncodeError encodeError         = NULL;
    ASN_DecodeError decodeError         = NULL;
    const char* encodeErrorText         = NULL;
    const char* encodeExtendedErrorText = NULL;
    const char* decodeErrorText         = NULL;
    const char* decodeExtendedErrorText = NULL;
    ASN_Octets octets                   = NULL;
    int res                             = ITS_SUCCESS;
    int encodeErrorCode                 = ITS_SUCCESS;
    int decodeErrorCode                 = ITS_SUCCESS;

    MAP_V4_InsertSubscriberDataArg insertSubscriberDataArgAfter = NULL;

    octets = ASN_Octets_ConstructWithArray(octetArray, size);

    insertSubscriberDataArgAfter = MAP_V4_InsertSubscriberDataArg_ConstructDefault();

    if (insertSubscriberDataArgAfter == NULL)
    {
        return ITS_ENOMEM;
    }

    res = MAP_V4_InsertSubscriberDataArg_Decode(
                                insertSubscriberDataArgAfter, 
                                octets, 
                                &decodeError);

    if (res == ITS_E_ASN_DECODE_ERROR)
    {
        /* 
         *  Status:                                                   
         *                                                            
         *  encodeError != NULL. Must be destructed by end-user.       
         */


        /* Retrieve and print decode error code. */

        decodeErrorCode = 
            ASN_DecodeError_GetError(decodeError);

        fprintf(
            stderr, 
            "\nDecode error code is <%d>.\n\n", 
            decodeErrorCode);


        /* 
         *  Retrieve and print decode error text (freed automatically when the
         *  decodeError object is destructed).                             
         */

        decodeErrorText = 
            ASN_DecodeError_GetErrorText(decodeError);

        if (decodeErrorText == NULL)
        {
            /* Error: out of memory. */
        }

        fprintf(
            stderr, 
            "\nDecode error text is <%s>.\n\n", 
            decodeErrorText);


        /* 
         *  Retrieve and print extended decode error text (freed automatically
         *  when the decodeError object is destructed).                       
         */

        decodeExtendedErrorText = 
            ASN_DecodeError_GetExtentedErrorText(decodeError);

        fprintf(
            stderr, 
            "\nDecode error extended text is <%s>.\n\n", 
            decodeExtendedErrorText);


        /* Object decodeError must be destructed by end-user. */

        ASN_DecodeError_Destruct(decodeError);


        MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArgAfter);

        ASN_Octets_Destruct(octets);

        return res;
    }
    else if (res != ITS_SUCCESS)
    {
        MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArgAfter);

        ASN_Octets_Destruct(octets);

        return res;
    }
    else
    {
        /* res == ITS_SUCCESS. Nothing to do. Continue processing. */
    }


    /*------------------------------------------------------------------------*/
    /* Show how to retrieve data from ASN.1 decoded object.                   */
    /*------------------------------------------------------------------------*/

    /* To be done. */


    /*------------------------------------------------------------------------*/
    /* Print contents of ASN.1 decoded object.                                */
    /*------------------------------------------------------------------------*/

    printf("\nPrinting decoded InsertSubscriberDataArg...\n\n");

    MAP_V4_InsertSubscriberDataArg_Print(insertSubscriberDataArgAfter);

    printf("\n");


    /*------------------------------------------------------------------------*/
    /* Release all the memory.                                                */
    /*------------------------------------------------------------------------*/

    MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArgAfter);

    ASN_Octets_Destruct(octets);

    return ITS_SUCCESS;
}