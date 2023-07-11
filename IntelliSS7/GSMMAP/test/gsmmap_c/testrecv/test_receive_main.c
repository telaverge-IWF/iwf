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

int ISUP_SetVariant_CCITT() { return 0; }
int CCITT_CallTable;
int CCITT_ISUP_Variant() { return 0; }
int ISUP_TlvEventToL3Message_CCITT() { return 0; }
int ISUP_L3MessageToTlvEvent_CCITT() { return 0; }
int ComputeMSize() { return 0; }

/* Decode Operation InsertSubscriberDaraArg */
int
InterpretOperationInsertSubscriberDataArg(const ITS_OCTET* octetArray, size_t size);


#if defined(WIN32)

/*
 *  The following macros set and clear, respectively, given bits of the C 
 *  runtime library debug flag, as specified by a bitmask.
 */

#if defined(_DEBUG)

#define  SET_CRT_DEBUG_FIELD(a) \
            _CrtSetDbgFlag((a) | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#define  CLEAR_CRT_DEBUG_FIELD(a) \
            _CrtSetDbgFlag(~(a) & _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))

#else /* !defined(_DEBUG) */

#define  SET_CRT_DEBUG_FIELD(a)   ((void) 0)
#define  CLEAR_CRT_DEBUG_FIELD(a) ((void) 0)

#endif /* defined(_DEBUG) */

#endif /* defined(WIN32) */

ITS_HANDLE handle = NULL;
ITS_HANDLE dispatch_handle = NULL;

/*
 *   Termination handler
 */
#if defined(WIN32)
static BOOL WINAPI breakHandler(DWORD ctrlType)
#else
static void exitHandler(int sig)
#endif
{
    ITS_Terminate(handle);
    return 0;
}

/*
 *   Dispatch Thread
 */
THREAD_RET_TYPE
Dispatch(void *arg)
{
    ITS_EVENT ev;

	dispatch_handle = ITS_Initialize(ITS_SCCP | ITS_TCAP | ITS_TRANSPORT_FIFO
                                     , 2);

    if (!dispatch_handle)
    {
		THREAD_NORMAL_EXIT;
    }

    while (ITS_GetNextEvent(dispatch_handle, &ev) == ITS_SUCCESS)
    {
        ev.src = ITS_MTP3_SRC;
        TRANSPORT_PutEvent(ITS_SCCP_SRC, &ev);
    }

    THREAD_NORMAL_EXIT;
}

int
main(int argc, char** argv)
{
    ITS_THREAD  tranThread;
    ITS_HDR     header;
    TCAP_CPT    cpt;
    int result;

    printf("\nBegin GSM MAP V4 receive example...\n");

#if defined(WIN32)
    SetConsoleCtrlHandler(breakHandler, TRUE);
#else
    signal(SIGINT, exitHandler);
#endif /* defined(WIN32) */
       
    /*
     *  Set Application Name
     */

    APPL_SetName("test_receive");

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
     *  Tcap transport
     */
    handle = (ITS_HANDLE)ITS_Initialize(ITS_TCAP | 
                                        ITS_SCCP | 
                                        ITS_TRANSPORT_TQUEUE |
                                        ITS_TRANSPORT_SINGLE_USER, 
                                        1);
    if(handle == NULL)
    {
        printf("Null tcap handle \n");
        exit(0);
    }

    /* 
     *  Border Transport Thread
     */
    result = THREAD_CreateThread(&tranThread, 
                                 0, 
                                 Dispatch,
                                 NULL, 
                                 ITS_TRUE);
    if (result != ITS_SUCCESS)
    {
        printf("Couldn't create dispatch thread.\n");
        ITS_Terminate(handle);
        return 0;
    }

    memset((char *)&header, 0, sizeof(ITS_HDR));
    memset((char *)&cpt, 0, sizeof(TCAP_CPT));

    /* Receiving loop */
	while (1)
	{
        ITS_EVENT event;

		result = ITS_GetNextEvent(handle, &event);

        if (result != ITS_SUCCESS)
        {
            printf("\nITS_GetNextEvent() Error");

            continue;
        }

        printf("\nReceived Event...\n");

        if (TCAP_MSG_TYPE(&event) == ITS_TCAP_CPT)
        {
            TCAP_ReceiveComponent(handle, &event, &header, &cpt);
            printf("\nReceive TCAP component...\n");

            switch (cpt.ptype)
            {
            case TCAP_PT_TC_INVOKE_CCITT:
            {
                printf("\nInvoke component.\n");

                /* Selection according to GSM MAP operation. */
                switch (cpt.u.invoke.operation.data[2])
                {
                case GSMMAP_OP_insertSubscriberData:
                    InterpretOperationInsertSubscriberDataArg(
                                    cpt.u.invoke.param.data, 
                                    cpt.u.invoke.param.len);
                    break;

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
                    printf("\nError sending end dialogue.\n\n");
                    continue;
                }

                printf("\nEnd dialogue sent.\n\n");
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
                printf("\nBegin dialogue.\n");
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

    /*
     *  IntelliSS7 termination.
     */

    ITS_Terminate(handle);

    ITS_GlobalStop();

    ITS_RemFeature(itsASN_C_RUNTIME_Class);

    ITS_RemFeature(itsMAP_V4_Class);

#if defined(USE_INTELLINET_STACK)
    ITS_RemFeature(itsINTELLISS7_Class);
#endif

    printf("\nEnd of GSM MAP V4 receive example.\n");
    
    return EXIT_SUCCESS;
}

/*------------------------------------------------------------------------------
 *  Decode Operation InsertSubscriberDaraArg
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