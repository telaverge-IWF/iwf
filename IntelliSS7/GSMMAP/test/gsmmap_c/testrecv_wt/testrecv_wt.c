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

/* Decode Operation InsertSubscriberDaraArg */

int
InterpretOperationInsertSubscriberDataArg(const ITS_OCTET* octetArray, size_t size);

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
 * two pools. One is the worker pool, the other is the border pool
 */

static LocalPool*   borderPool = NULL;
static LocalPool*   workerPool = NULL;

static int dispatcherPoolSize = 1;

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
    ITS_HANDLE h;
    ITS_EVENT event;

    /*
     * getting NULL here is a fatal error
     */
    assert((h = ITS_Initialize(work->mask,
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
    ITS_Terminate(h);
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
    ITS_HDR header;
    int result = ITS_SUCCESS;

    /*
     *  o   Create transport.
     *  
     *  o   Receive TCAP end dialogue.
     *
     *  o   Exit loop, return the thread to the pool.
     */

    /* Getting NULL here is a fatal error */
    assert((handle = ITS_Initialize(self->mask,
                                self->instance)) != NULL);
    
    memset((char *)&header, 0, sizeof(ITS_HDR));
    memset((char *)&cpt, 0, sizeof(TCAP_CPT));

    while(1)
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
            TCAP_ReceiveComponent(handle, &event, &header, &cpt);
            printf("\nReceive TCAP component...\n");

            switch (cpt.ptype)
            {
            case TCAP_PT_TC_INVOKE_CCITT:
            {
                printf("\nInvoke component Received.\n");

                /* Selection according to GSM MAP operation. */
                switch (cpt.u.invoke.operation.data[2])
                {
                case GSMMAP_OP_insertSubscriberData:
                {
                    InterpretOperationInsertSubscriberDataArg(
                                    cpt.u.invoke.param.data, 
                                    cpt.u.invoke.param.len);
                    break;
                }

                default:
                /* Should be processed by complete code. */
                    break;
                }

                break;
            }

            case TCAP_PT_TC_RESULT_L_CCITT:
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

            /* Last component? */
            if (cpt.last_component == TCP_LAST_CPT)
            {
                TCAP_DLG endDlg;

                memset((char *)&endDlg, 0, sizeof(TCAP_DLG));
                endDlg.ptype = TCPPT_TC_END;

                result = TCAP_SendDialogue(handle, &header, &endDlg);

                if(result != ITS_SUCCESS)
                {
                    printf("\nError sending end dialog.\n");
                    continue;
                }

                printf("\nEnd dialogue sent.\n");
            }
        }
        else if (TCAP_MSG_TYPE(&event) == ITS_TCAP_DLG)
        {
            TCAP_DLG dlg;

            memset(&dlg, 0, sizeof(TCAP_DLG));

            TCAP_ReceiveDialogue(handle, &event, &header, &dlg);
            printf("\nReceived TCAP dialogue...\n"
                   "ptype = 0x%x, dialogue_id = 0x%x\n",
                    dlg.ptype,header.context.dialogue_id);

            switch (dlg.ptype)
            {
            case TCAP_PT_TC_BEGIN_CCITT:
                printf("\nBegin dialogue Received.\n\n");
                break;

            case TCAP_PT_TC_UNI_CCITT:
            case TCAP_PT_TC_END_CCITT:
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

/*------------------------------------------------------------------------------
 *
 *  Routes the TCAP message to the application based on the dialog id
 *  This functions as the "application selector" as documented by
 *  ITS_RoutingMap
 *
 *------------------------------------------------------------------------------*/

ITS_USHORT
SelectApplication(ITS_HDR *hdr, ITS_EVENT* event)
{
    TPOOL_THREAD* iThread;
    WORKER_Control* work;
    ITS_USHORT qid;
    int did;
    
    /*
     * If this point is reached then the transaction dialogue id is
     * not in the application routing table. Therefore we need to:
     *
     * o Get a worker thread from the worker pool.
     *
     * o Update the application routing table.
     *
     * o Add thread function to the worker thread and resume it.
     */

    did = hdr->context.dialogue_id;

    assert(TPOOL_GetFirstAvailThread(&workerPool->pool,
                                     &iThread) == ITS_SUCCESS);

    work = (WORKER_Control *)iThread;
    qid = work->instance;
        
    assert(ROUTE_AddApplication(qid, hdr) == ITS_SUCCESS);
        
    assert(TPOOL_DispatchOnThread(iThread,
                                  HandleTcapMsg,
                                  NULL) == ITS_SUCCESS); 
        
    return (qid);
}

/*------------------------------------------------------------------------------
 *                              Entry Point 
 *------------------------------------------------------------------------------*/
int
main(int argc, char** argv)
{
    int result;

    printf("\nBegin GSM MAP W/Toolkit receive example...\n");

#if defined(WIN32)
    SetConsoleCtrlHandler(breakHandler, TRUE);
#else
    signal(SIGINT, exitHandler);
#endif /* defined(WIN32) */
       
    /*
     *  Set Application Name
     */
    APPL_SetName("test_receive_wt");

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
     * set the application selector for TCAP messages
     */
    assert(ROUTE_SetApplicationSelector(SelectApplication) != NULL);

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

    /*
     * start the border dispatchers.
     */

    TPOOL_Dispatch(&borderPool->pool, BorderDispatch, NULL);

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

#if defined(USE_INTELLINET_STACK)
    ITS_RemFeature(itsINTELLISS7_Class);
#endif

    printf("\nEnd of GSM MAP W/Toolkit receive example.\n");
    return EXIT_SUCCESS;
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
InterpretOperationInsertSubscriberDataArg(const ITS_OCTET* octetArray, size_t size)
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