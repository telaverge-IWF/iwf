/*----------------------------------------------------------------------------*
 *                                                                            *
 *      Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.     *
 *              Manufactured in the United States of America.                 *
 *        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        *
 *                                                                            *
 *    This product and related documentation is protected by copyright and    *
 *    distributed under licenses restricting its use, copying, distribution   *
 *    and decompilation.  No part of this product or related documentation    *
 *    may be reproduced in any form by any means without prior written        *
 *    authorization of IntelliNet Technologies and its licensors, if any.     *
 *                                                                            *
 *    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       *
 *    government is subject to restrictions as set forth in subparagraph      *
 *    (c)(1)(ii) of the Rights in Technical Data and Computer Software        *
 *    clause at DFARS 252.227-7013 and FAR 52.227-19.                         *
 *                                                                            *
 *----------------------------------------------------------------------------*
 *                                                                            *
 * CONTRACT: INTERNAL                                                         *
 *                                                                            *
 *----------------------------------------------------------------------------*
 *
 *  ID: $Id: test_receive_main.c,v 9.1 2005/03/23 12:51:35 cvsadmin Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  MAP V4 receive example.
 *
 *  This example shows how to receive the argument of a MAP InsertSubscriberData
 *  operation. The part used to interpret (decode and retrieve data) for the
 *  InsertSubscriberData operation argument is identical the test_codec example.
 *
 *
 *
 *  IntelliNet SS7 stack note:
 *
 *  The conditional sections of the code that are included if the preprocessor
 *  symbol "USE_INTELLINET_STACK" is defined are required only if the IntelliNet
 *  SS7 stack is used. The IntelliNet SS7 stack allows to run the example
 *  without any SS7 hardware.
 *
 */

#include <stdio.h>

#if defined(WIN32)
#include <conio.h>
#else /* !defined(WIN32) */
#if !defined(EXIT_FAILURE)
#define EXIT_FAILURE (-1)
#endif
#if !defined(EXIT_SUCCESS)
#define EXIT_SUCCESS (0)
#endif
#endif /* defined(WIN32) */

#include <its.h>
#include <its_app.h>
#include <its_tq_trans.h>
#include <its_thread.h>
#include <its_timers.h>
#include <its_route.h>
#include <its_trace.h>
#include <its_worker.h>
#include <its_semaphore.h>

#if defined(USE_INTELLINET_STACK)
#include <its_ss7_stubs.h>
#include <its_ss7_trans.h>
#endif /* defined(USE_INTELLINET_STACK) */

#include <tcap.h>

#include <asn_common.h>

#include <map_c.h>
#include <map_v4_its_feature_class_c.h>
#include <map_v4_insert_subscriber_data_arg_c.h>

/*------------------------------------------------------------------------------
 *
 *  Temporary work around for missing symbols in IntelliNet Vendor Library.
 *
 *  => Must be removed when problem will be corrected.
 */

int ISUP_SetVariant_CCITT() { return 0; }
int CCITT_CallTable;
int CCITT_ISUP_Variant() { return 0; }
int ISUP_TlvEventToL3Message_CCITT() { return 0; }
int ISUP_L3MessageToTlvEvent_CCITT() { return 0; }
int ComputeMSize() { return 0; }

/*----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
 * 
 *  Local function declarations.
 */

static int InterpretOperationInsertSubscriberDataArg(
                    const ITS_OCTET* octetArray, 
                    size_t size);


/*------------------------------------------------------------------------------
 *
 *  Simple break handler (specific for WIN32 and Unix).
 */

#if defined(WIN32)
static BOOL WINAPI breakHandler(DWORD ctrlType)
{
    ITS_GlobalStop();

    exit(EXIT_SUCCESS);
}
#else /* !defined(WIN32) */
static void exitHandler(int sig)
{
    ITS_GlobalStop();

    exit(EXIT_SUCCESS);
}
#endif /* defined(WIN32) */

#if defined(USE_INTELLINET_STACK)

/*------------------------------------------------------------------------------
 *
 *  Synchronization object (semaphore) used to synchronize primary thread and
 *  border transport thread.
 */

static ITS_SEMAPHORE borderTransportSemaphore;


/*------------------------------------------------------------------------------
 *
 *  Boolean to be set to true to stop border transport thread.
 */

static ITS_BOOLEAN borderTransportStopRequested = ITS_FALSE;


/*------------------------------------------------------------------------------
 *
 *  Border transport thread function.
 */

THREAD_RET_TYPE
BorderTransportThreadDispatchFunction(void* arg)
{
    ITS_HANDLE borderTransportHandle = NULL; 
    ITS_EVENT event;

    memset(&event, 0, sizeof(ITS_EVENT));

	borderTransportHandle = 
        ITS_Initialize(
            ITS_TCAP            | 
            ITS_TRANSPORT_FIFO  |
            ITS_TRANSPORT_SINGLE_USER, 
            2);

    if (borderTransportHandle == NULL)
    {
        printf(
            "\nIntelliSS7 Error <%s>.\n", 
            ITS_GetErrorText(ITS_ENOTRANSPORT));

		THREAD_NORMAL_EXIT;
    }

    SEMA_PostSemaphore(&borderTransportSemaphore);

    while (!borderTransportStopRequested)
    {
        int res = ITS_GetNextEvent(borderTransportHandle, &event);

        if (res != ITS_SUCCESS)
        {
            printf(
                "\nIntelliSS7 Error <%s>.\n",
                ITS_GetErrorText(res));
        }
        else
        {
            /* Set event source to MTP3 (for routing purpose). */

            event.src = ITS_MTP3_SRC;

            TRANSPORT_PutEvent(ITS_SCCP_SRC, &event);
        }
    }

    ITS_Terminate(borderTransportHandle);

    THREAD_NORMAL_EXIT;
}

#endif /* defined(USE_INTELLINET_STACK) */


/*------------------------------------------------------------------------------
 *
 *  Entry point.
 */

int
main(int argc, char** argv)
{
    int res             = ITS_SUCCESS;
    ITS_HANDLE handle   = NULL;

    ITS_THREAD  borderTransportThread;

    ITS_HDR hdr;
    TCAP_DLG recvDlg;
    TCAP_CPT recvCpt;

    memset(&borderTransportThread, 0, sizeof(ITS_THREAD));
    memset((char *)&hdr, 0, sizeof(ITS_HDR));
    memset((char *)&recvDlg, 0, sizeof(TCAP_DLG));
    memset((char *)&recvCpt, 0, sizeof(TCAP_CPT));


    printf("\nBegin MAP V4 receive example...\n");

    /*--------------------------------------------------------------------------
     *
     *  Set break handler (specific for WIN32 and Unix).
     */

#if defined(WIN32)
    SetConsoleCtrlHandler(breakHandler, TRUE);
#else
    signal(SIGINT, exitHandler);
#endif /* defined(WIN32) */
       

    /*--------------------------------------------------------------------------
     *
     *  Set Application Name
     */

    APPL_SetName("test_receive");
       

#if defined(USE_INTELLINET_STACK)

    /*--------------------------------------------------------------------------
     *
     *  Using IntelliSS7 stack (add that feature).
     */

    res = ITS_AddFeature(itsINTELLISS7_Class);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        exit(EXIT_FAILURE);
    }

#endif /* defined(USE_INTELLINET_STACK) */


    /*--------------------------------------------------------------------------
     *
     *  Add ASN.1 C runtime feature to IntelliSS7.
     */

    res = ITS_AddFeature(itsASN_C_RUNTIME_Class);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        exit(EXIT_FAILURE);
    }


    /*--------------------------------------------------------------------------
     *
     *  Add MAP V4 feature to IntelliSS7.
     */

    res = ITS_AddFeature(itsMAP_V4_Class);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        exit(EXIT_FAILURE);
    }

    /*--------------------------------------------------------------------------
     *
     *  IntelliSS7 subsystems initialization (including licensing).
     */

    res = ITS_GlobalStart(ITS_TCAP | ITS_SCCP);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));
        
        exit(EXIT_FAILURE);
    }

#if defined(USE_INTELLINET_STACK)

    /*--------------------------------------------------------------------------
     *        
     *  o   Create border transport semaphore.
     *
     *  o   Create border transport thread object.
     *  
     *  o   Start border transport thread.
     *
     *  o   Wait for border transport thread (synchronization point).
     */

    res = SEMA_CreateSemaphore(&borderTransportSemaphore, 0);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        ITS_GlobalStop();

        exit(EXIT_FAILURE);
    }

    res = THREAD_CreateThread(
            &borderTransportThread,
            0,
            BorderTransportThreadDispatchFunction,
            NULL,
            ITS_TRUE);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        ITS_GlobalStop();

        exit(EXIT_FAILURE);
    }

    res = SEMA_WaitSemaphore(&borderTransportSemaphore);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        ITS_GlobalStop();

        exit(EXIT_FAILURE);
    }

#endif /* defined(USE_INTELLINET_STACK) */


    /*--------------------------------------------------------------------------
     *
     *  Create transport.
     */

    handle = (ITS_HANDLE)ITS_Initialize(ITS_TCAP | 
                                        ITS_TRANSPORT_TQUEUE |
                                        ITS_TRANSPORT_SINGLE_USER, 
                                        1);
    if(handle == NULL)
    {
        printf(
            "\nIntelliSS7 Error <%s>.\n", 
            ITS_GetErrorText(ITS_ENOTRANSPORT));

        ITS_GlobalStop();

        exit(EXIT_FAILURE);
    }


    /*--------------------------------------------------------------------------
     *
     *  Receive (infinite) loop:
     *
     *  o   Receive TCAP begin dialogue.
     *
     *  o   Receive TCAP invoke component.
     *
     *  o   Call function to interpret MAP InsertSubscriberData operation
     *      argument.
     *
     *  o   Send back a TCAP end dialogue if last component.
     *
     *  o   Exit loop.
     *
     */

	while (ITS_TRUE)
	{
        ITS_EVENT event;

        memset(&event, 0, sizeof(ITS_EVENT));

		res = ITS_GetNextEvent(handle, &event);

        if (res != ITS_SUCCESS)
        {
            printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

            continue;
        }

        printf("\nReceived Event...\n");

        printf("\nSource: <%d>.\n", event.src);

        if (TCAP_MSG_TYPE(&event) == ITS_TCAP_CPT)
        {
            res = TCAP_ReceiveComponent(handle, &event, &hdr, &recvCpt);

            if (res != ITS_SUCCESS)
            {
                printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

                ITS_GlobalStop();

                exit(EXIT_FAILURE);
            }

            printf("\nReceive TCAP component...\n");

            switch (recvCpt.ptype)
            {
            case TCAP_PT_TC_INVOKE_CCITT:
            {
                printf("\nInvoke component.\n");

                /* Selection according to MAP operation. */

                switch (recvCpt.u.invoke.operation.data[2])
                {
                case MAP_OP_INSERT_SUBSCRIBER_DATA:
                {
                    /*
                     *  The parameter field of the TCAP invoke component
                     *  contains the MAP InsertSubscriberData operation
                     *  argument.
                     */


                    /*----------------------------------------------------------
                     *
                     *  Function call uses MAP ASN.1 C API.
                     */

                    InterpretOperationInsertSubscriberDataArg(
                        recvCpt.u.invoke.param.data, 
                        recvCpt.u.invoke.param.len);

                    /*
                     *--------------------------------------------------------*/

                    break;
                }

                default:
                {
                    /* 
                     *  Should be processed by complete code (all other MAP
                     *  operation codes. 
                     */

                    break;
                }
                } /* Switch. */

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
            {
                /* Should be processed by complete code. */

                break;
            }

            default:
            {
                /* Should not be reached. */

                break;
            }
            } /* Switch. */

            /* Last component? */

            if (recvCpt.last_component == TCP_LAST_CPT)
            {
                TCAP_DLG endDlg;

                memset((char *)&endDlg, 0, sizeof(TCAP_DLG));

                endDlg.ptype = TCPPT_TC_END;

                res = TCAP_SendDialogue(handle, &hdr, &endDlg);

                if(res != ITS_SUCCESS)
                {
                    printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));
                }
            }
        }
        else if (TCAP_MSG_TYPE(&event) == ITS_TCAP_DLG)
        {
            res = TCAP_ReceiveDialogue(handle, &event, &hdr, &recvDlg);

            printf("\nReceived TCAP dialogue...\n");

            printf("Dialogue ID: <%d>.\n", hdr.context.dialogue_id); 

            switch (recvDlg.ptype)
            {
            case TCAP_PT_TC_BEGIN_CCITT:
            {
                printf("\nBegin dialogue.\n");

                break;
            }

            case TCAP_PT_TC_UNI_CCITT:
            case TCAP_PT_TC_END_CCITT:
            case TCAP_PT_TC_CONTINUE_CCITT:
            case TCAP_PT_TC_P_ABORT_CCITT:
            case TCAP_PT_TC_U_ABORT_CCITT:
            case TCAP_PT_TC_NOTICE_CCITT:
            {
                /* Should be processed by complete code. */

                break;
            }

            default:
            {
                /* Should not be reached. */

                break;
            }
            }   /* Switch. */
        }
	}

    /*--------------------------------------------------------------------------
     *
     *  o   Stop border transport thread.
     *
     *  o   Delete border transport thread (can be done even if still running).
     *
     *  o   Delete border transport semaphore.
     */

#if defined(USE_INTELLINET_STACK)

    borderTransportStopRequested = ITS_TRUE;

    THREAD_DeleteThread(borderTransportThread);

    SEMA_DeleteSemaphore(borderTransportSemaphore);

#endif /* defined(USE_INTELLINET_STACK) */


    /*--------------------------------------------------------------------------
     *
     *  IntelliSS7 termination.
     */

    ITS_Terminate(handle);

    ITS_GlobalStop();


    /*--------------------------------------------------------------------------
     *
     *  Using IntelliSS7 stack (remove feature).
     */

#if defined (USE_INTELLINET_STACK)

    ITS_RemFeature(itsINTELLISS7_Class);

#endif /* defined(USE_INTELLINET_STACK) */

    ITS_RemFeature(itsASN_C_RUNTIME_Class);

    ITS_RemFeature(itsMAP_V4_Class);

    printf("\nEnd of MAP V4 receive example.\n");

#if defined(WIN32)

    /* To stop here in console application. */

    printf("Type any key to quit...\n");

    {
        char c = getch();
    }
    
#endif /* defined(WIN32) */
    
    return EXIT_SUCCESS;
}


/*------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 *
 *  Following code is identical to test_codec example.
 *
 *------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
 *
 *  How to interpret an (encoded) MAP InsertSubscriberData operation argument 
 *  (InsertSubscriberDataArg):
 *
 *  o   Decode InsertSubscriberDataArg encoded value (i.e. create 
 *      InsertSubscriberDataArg object from InsertSubscriberDataArg encoded 
 *      value).
 *
 *  o   Retrieve Data from InsertSubscriberDataArg object.
 *
 */

int 
InterpretOperationInsertSubscriberDataArg(
    const ITS_OCTET* octetArray, 
    size_t size)
{
    MAP_V4_InsertSubscriberDataArg insertSubscriberDataArg  = NULL;
    ASN_Octets octets                                       = NULL;
    int res                                                 = ITS_SUCCESS;

    ASN_C_REQUIRE(octetArray != NULL);
    ASN_C_REQUIRE(size != 0);

    /*
     *  [1] Create Octets object from InsertSubscriberDataArg ASN.1 
     *  encoded value.
     */

    octets = ASN_Octets_ConstructWithArray(octetArray, size);

    if (octets == NULL)
    {
        return ITS_ENOMEM;
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [2] Create InsertSubscriberDataArg object (used by decode phase).
     */

    insertSubscriberDataArg = MAP_V4_InsertSubscriberDataArg_ConstructDefault();

    if (insertSubscriberDataArg == NULL)
    {
        ASN_Octets_Destruct(octets);

        return ITS_ENOMEM;
    }

    /*------------------------------------------------------------------------*/

    /*  
     *  [3] Decode InsertSubscriberDataArg ASN.1 encoded value and therefore
     *  populate previously created InsertSubscriberDataArg object.
     */

    {
        ASN_DecodeError decodeError         = NULL;
        int decodeErrorCode                 = ITS_SUCCESS;
        const char* decodeErrorText         = NULL;
        const char* decodeExtendedErrorText = NULL;

        res = MAP_V4_InsertSubscriberDataArg_Decode(
                                insertSubscriberDataArg, 
                                octets, 
                                &decodeError);

        if (res == ITS_E_ASN_DECODE_ERROR)
        {
            /* 
             *  Status:                                                   
             *                                                            
             *  decodeError != NULL. Must be destructed by end-user.       
             */


            /* 
             *  Retrieve and print decode error code. 
             */

            decodeErrorCode = 
                ASN_DecodeError_GetError(decodeError);

            fprintf(
                stderr, 
                "\nDecode error code is <%d>.\n\n", 
                decodeErrorCode);

            /* 
             *  Retrieve and print decode error text (freed automatically when
             *  decodeError object is destructed).                             
             */

            decodeErrorText = 
                ASN_DecodeError_GetErrorText(decodeError);

            if (decodeErrorText == NULL)
            {
                ASN_Octets_Destruct(octets);
                MAP_V4_InsertSubscriberDataArg_Destruct(
                    insertSubscriberDataArg);
                ASN_DecodeError_Destruct(decodeError);

                return ITS_ENOMEM;
            }

            fprintf(
                stderr, 
                "\nDecode error text is <%s>.\n\n", 
                decodeErrorText);

            /* 
             *  Retrieve and print extended decode error text (freed 
             *  automatically when decodeError object is destructed).
             */

            decodeExtendedErrorText = 
                ASN_DecodeError_GetExtendedErrorText(decodeError);

            if (decodeExtendedErrorText == NULL)
            {
                ASN_Octets_Destruct(octets);
                MAP_V4_InsertSubscriberDataArg_Destruct(
                    insertSubscriberDataArg);
                ASN_DecodeError_Destruct(decodeError);

                return ITS_ENOMEM;
            }

            fprintf(
                stderr, 
                "\nDecode error extended text is <%s>.\n\n", 
                decodeExtendedErrorText);

            ASN_Octets_Destruct(octets);
            MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);

            /* 
             *  Object decodeError must be destructed by end-user. 
             */

            ASN_DecodeError_Destruct(decodeError);

            return res;
        }
        else if (res != ITS_SUCCESS)
        {
            ASN_Octets_Destruct(octets);
            MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);
            ASN_DecodeError_Destruct(decodeError);

            return res;
        }
        else
        {
            /* 
             *  res == ITS_SUCCESS. Nothing to do. Continue processing. 
             */
        }

        /*
         *  Print decoded InsertSubscriberDataArg object.
         */

        printf("\nPrinting decoded InsertSubscriberDataArg object...\n");

        MAP_V4_InsertSubscriberDataArg_Print(insertSubscriberDataArg);

        printf("\n");
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [4] Retrieve optional parameter "imsi".
     */

    if (MAP_V4_InsertSubscriberDataArg_OptionImsi(insertSubscriberDataArg))
    {
        const ITS_OCTET* array  = NULL;
        size_t arraySize        = 0;

        /*
         *  [4-1] Retrieve const pointer to IMSI object.
         */

        const MAP_V4_IMSI
            imsi =
                MAP_V4_InsertSubscriberDataArg_GetImsi(
                    insertSubscriberDataArg);

        /*
         *  [4-2] Retrieve contents of IMSI object.
         */

        array = 
            MAP_V4_IMSI_GetArray(
                imsi);

        arraySize =
            MAP_V4_IMSI_GetSize(
                imsi);

        /*
         *  Do something with array of octets...
         */

        /*
         *  [4-3] Print IMSI object.
         */

        printf("\nPrinting IMSI object...\n");

        MAP_V4_IMSI_Print(imsi);

        printf("\n");
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [5] Retrieve other optional parameters: to be done.
     */

    /*------------------------------------------------------------------------*/

    /*
     *  [6] Free all memory allocated on the heap.
     */

    /*
     *  [6-1] Delete octets object.
     */

    ASN_Octets_Destruct(octets);

    /*
     *  [6-2] Delete InsertSubscriberDataArg object.
     */

    MAP_V4_InsertSubscriberDataArg_Destruct(insertSubscriberDataArg);

    /*------------------------------------------------------------------------*/

    /*
     *  Return success.
     */

    return ITS_SUCCESS;
}