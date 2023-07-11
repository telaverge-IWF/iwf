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
 *  ID: $Id: test_send_main.c,v 9.1 2005/03/23 12:51:46 cvsadmin Exp $
 *
 *----------------------------------------------------------------------------*/

/*
 *  INAP CS1 send example.
 *
 *  This example shows how to send the argument of an INAP Connect operation.
 *  The part used to build (create, insert data and encode) the Connect
 *  operation argument is identical the test_codec example.
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

#include <inap_c.h>
#include <inap_cs1_its_feature_class_c.h>
#include <inap_cs1_connect_arg_c.h>

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
 *  Definitions for SCCP addresses.
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


/*------------------------------------------------------------------------------
 * 
 *  Local function declarations.
 */

static int ExecuteOperationConnect(
                ITS_HANDLE handle);

static int ExecuteReceiveLoop(
                ITS_HANDLE handle);

static int BuildOperationConnectArg(
                ITS_OCTET** octetArray, 
                size_t* size);


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
            ITS_TCAP                    | 
            ITS_TRANSPORT_FIFO          |
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

    memset(&borderTransportThread, 0, sizeof(ITS_THREAD));


    printf("\nBegin INAP CS1 send example...\n");

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

    APPL_SetName("test_send");


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
     *  Add INAP CS1 feature to IntelliSS7.
     */

    res = ITS_AddFeature(itsINAP_CS1_Class);

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
     *  Encode SCCP addresses according to local and remote PC and SSN.
     */

    memset((char *)&destinationAddr, 0, sizeof(SCCP_ADDR));
    memset((char *)&originatingAddr, 0, sizeof(SCCP_ADDR));

    res = SCCP_EncodeAddr(
                    &originatingAddr, 
                    SCCP_ADDR_INDICATOR, 
                    LOCAL_PC, 
                    LOCAL_SSN, 
                    NULL, 
                    0);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        ITS_GlobalStop();

        exit(EXIT_FAILURE);
    }

    res = SCCP_EncodeAddr(
                    &destinationAddr, 
                    SCCP_ADDR_INDICATOR, 
                    REMOTE_PC, 
                    REMOTE_SSN, 
                    NULL, 
                    0);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        ITS_GlobalStop();

        exit(EXIT_FAILURE);
    }


    /*--------------------------------------------------------------------------
     *
     *  Execute INAP operation Connect.  
     */

    res = ExecuteOperationConnect(handle);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        ITS_GlobalStop();

        exit(EXIT_FAILURE);
    }


    /*--------------------------------------------------------------------------
     *
     *  Execute receive loop (wait for answer).
     */

    res = ExecuteReceiveLoop(handle);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        ITS_GlobalStop();

        exit(EXIT_FAILURE);
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

    THREAD_DeleteThread(&borderTransportThread);

    SEMA_DeleteSemaphore(&borderTransportSemaphore);

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

    ITS_RemFeature(itsINAP_CS1_Class);

    printf("\nEnd of INAP CS1 send example.\n");

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
 *
 *  Execute INAP operation Connect:
 *  
 *  o   Allocate new dialogue ID.
 *
 *  o   Build TCAP begin dialogue.
 *
 *  o   Build TCAP invoke component.
 *
 *  o   Call function to build INAP Connect operation argument.
 *
 *  o   Send TCAP invoke component.
 *  
 *  o   Send TCAP begin dialogue.
 *
 */

int
ExecuteOperationConnect(ITS_HANDLE handle)
{
    int res                 = ITS_SUCCESS;
    ITS_OCTET* octetArray   = NULL;
    size_t size             = 0;

    ITS_HDR hdr;
    TCAP_DLG dlg;
    TCAP_CPT cpt;    

    memset((char *)&hdr, 0, sizeof(ITS_HDR));
    memset((char *)&dlg, 0, sizeof(TCAP_DLG));
    memset((char *)&cpt, 0, sizeof(TCAP_CPT));

    /*
     *  Allocate new dialogue ID.
     */

    hdr.type = ITS_TCAP;
    TCAP_AllocateDialogueId(&hdr.context.dialogue_id);


    /*
     *  Populate begin dialogue (dlg).
     */

    dlg.ptype = TCPPT_TC_BEGIN;

    memcpy(&dlg.u.begin.orig_addr, &originatingAddr, sizeof(SCCP_ADDR));
    memcpy(&dlg.u.begin.dest_addr, &destinationAddr, sizeof(SCCP_ADDR));

    dlg.u.begin.cpt_present = 1;


    /* 
     *  Populate invoke component (cpt).
     */

    cpt.ptype = TCPPT_TC_INVOKE;
    cpt.u.invoke.timeout = 100;
    cpt.u.invoke.opClass = 2;

    cpt.u.invoke.invoke_id.data[0]  = TCPPN_INVOKE_TAG;
    cpt.u.invoke.invoke_id.data[1]  = 1; 
    cpt.u.invoke.invoke_id.data[2]  = 1; 
    cpt.u.invoke.invoke_id.len      = 3;
    cpt.u.invoke.linked_id.len      = 0;
    cpt.last_component              = 1;

    res = BuildOperationConnectArg(&octetArray, &size);

    if (res != ITS_SUCCESS)
    {
        return res;
    }
            
    memcpy(cpt.u.invoke.param.data, octetArray, size);
    cpt.u.invoke.param.len = size;

    if (octetArray != NULL)
    {
        free(octetArray);
    }

	cpt.u.invoke.operation.len = 3;
	cpt.u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
	cpt.u.invoke.operation.data[1] = 1;

    /* INAP_OP_CONNECT is defined in inap_c.h. */

	cpt.u.invoke.operation.data[2] = INAP_OP_CONNECT;

    res = TCAP_SendComponent(handle, &hdr, &cpt);

    if (res != ITS_SUCCESS)
    {
        return res;
    }

    res = TCAP_SendDialogue(handle, &hdr, &dlg);

    if (res != ITS_SUCCESS)
    {
        return res;
    }

    return ITS_SUCCESS;
}


/*------------------------------------------------------------------------------
 *
 *  Receive loop:
 *  
 *  o   Receive TCAP end dialogue (sent by test_receive example).
 *
 *  o   Exit loop and return success.
 *
 */

static int 
ExecuteReceiveLoop(ITS_HANDLE handle)
{
    int res             = ITS_SUCCESS;
    ITS_BOOLEAN stop    = ITS_FALSE;

    ITS_EVENT event;
    ITS_HDR hdr;
    TCAP_DLG recvDlg;
    TCAP_CPT recvCpt;

    memset((char *)&event, 0, sizeof(ITS_EVENT));
    memset((char *)&hdr, 0, sizeof(ITS_HDR));
    memset((char *)&recvDlg, 0, sizeof(TCAP_DLG));
    memset((char *)&recvCpt, 0, sizeof(TCAP_CPT));


    while(!stop)
    {
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
                return res;
            }

            printf("\nReceived TCAP component...\n");
        }
        else if (TCAP_MSG_TYPE(&event) == ITS_TCAP_DLG)
        {
            res = TCAP_ReceiveDialogue(handle, &event, &hdr, &recvDlg);

            if (res != ITS_SUCCESS)
            {
                return res;
            }

            printf("\nReceived TCAP dialogue...\n");

            printf("\nDialogue ID: <%d>.\n", hdr.context.dialogue_id);

            switch (recvDlg.ptype)
            {
            case TCAP_PT_TC_END_CCITT:
            {
                printf("\nEnd dialogue.\n");

                stop = ITS_TRUE; /* Exit receive loop. */

                break;
            }

            case TCAP_PT_TC_UNI_CCITT:
            case TCAP_PT_TC_BEGIN_CCITT:
            case TCAP_PT_TC_CONTINUE_CCITT:
            case TCAP_PT_TC_P_ABORT_CCITT:
            case TCAP_PT_TC_U_ABORT_CCITT:
            case TCAP_PT_TC_NOTICE_CCITT:
            {
                /* Should be processed by complete code. */

                stop = ITS_TRUE; /* Exit receive loop. */

                break;
            }

            default:
            {
                /* Should not be reached. */

                break;
            }
            } /* Switch. */
        }
    } 

    return ITS_SUCCESS;
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
 *  How to Build a Connect operation argument (INAP_CS1_ConnectArg):
 *
 *  o   Create a ConnectArg object.
 *
 *  o   Insert data step by step in the created ConnectArg object (i.e. populate
 *      various parameters of the Connect operation argument).
 *  
 *  o   Encode the ConnectArg object to produce a ConnectArg encoded value.
 *
 */

int  
BuildOperationConnectArg(ITS_OCTET** octetArray, size_t* size)
{
    INAP_CS1_ConnectArg connectArg  = NULL;
    ASN_Octets octets               = NULL;
    int res                         = ITS_SUCCESS;

    ASN_C_REQUIRE(octetArray != NULL);
    ASN_C_REQUIRE(size != NULL);
    ASN_C_REQUIRE(*octetArray == NULL);

    /*  
     *  [1] Create ConnectArg object. 
     */

    connectArg = INAP_CS1_ConnectArg_ConstructDefault();

    if (connectArg == NULL)
    {
        return ITS_ENOMEM;
    }

    /*------------------------------------------------------------------------*/

    /*
     *  Memory management note: all the following parameter objects that are
     *  used to populate the connectArg object are created in the heap using 
     *  the appropriate construct function. They are automatically deleted 
     *  (i.e. all associated memory released) when the connectArg object is
     *  deleted. 
     */

    /*------------------------------------------------------------------------*/

    /*  
     *  [2] Populate mandatory parameter "destinationRoutingAddress". 
     */

    {
        /*  
         *  [2-1] Create DestinationRoutingAddress object. 
         */

        INAP_CS1_DestinationRoutingAddress 
            destinationRoutingAddress = 
                INAP_CS1_DestinationRoutingAddress_ConstructDefault();

        if (destinationRoutingAddress == NULL)
        {
            INAP_CS1_ConnectArg_Destruct(connectArg);

            return ITS_ENOMEM;
        }
    
        /*
         *  INAP API Note: a DestinationRoutingAddress object contains a list of
         *  CalledPartyNumber objects.
         */

        {
            /*  
             *  [2-1-1] Create CalledPartyNumber object. 
             */

            ITS_OCTET fixedArray1[] = 
                { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16 };

            size_t fixedArray1Size = 7;

            INAP_CS1_CalledPartyNumber 
                calledPartyNumber =
                    INAP_CS1_CalledPartyNumber_ConstructWithArraySize(
                        fixedArray1,
                        fixedArray1Size);

            if (calledPartyNumber == NULL)
            {
                INAP_CS1_ConnectArg_Destruct(connectArg);
                INAP_CS1_DestinationRoutingAddress_Destruct(
                    destinationRoutingAddress);

                return ITS_ENOMEM;
            }

            /*
             *  [2-1-2] Add CalledPartyNumber object to 
             *  DestinationRoutingAddress object. 
             */

            res = 
                INAP_CS1_DestinationRoutingAddress_AddElement(
                    destinationRoutingAddress,
                    calledPartyNumber);

            if (res != ITS_SUCCESS)
            {
                INAP_CS1_ConnectArg_Destruct(connectArg);
                INAP_CS1_DestinationRoutingAddress_Destruct(
                    destinationRoutingAddress);

                return ITS_ENOMEM;
            }
        }

        /*
         *  [2-2] Set DestinationRoutingAddress object in ConnectArg object.
         */

        INAP_CS1_ConnectArg_SetDestinationRoutingAddress(
            connectArg,
            destinationRoutingAddress);
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [3] Populate optional parameter "alertingPattern".
     */

    {
        /*
         *  [3-1] Create AlertingPattern object.
         */

        ITS_OCTET fixedArray2[] = { 0x20, 0x21, 0x22 };

        size_t fixedArray2Size = 3;

        INAP_CS1_AlertingPattern
            alertingPattern =
                INAP_CS1_AlertingPattern_ConstructWithArraySize(
                    fixedArray2,
                    fixedArray2Size);

        if (alertingPattern == NULL)
        {
            INAP_CS1_ConnectArg_Destruct(connectArg);

            return ITS_ENOMEM;
        }

        /*
         *  [3-2] Set AlertingPattern object in ConnectArg object.
         */

        INAP_CS1_ConnectArg_SetAlertingPattern(
            connectArg,
            alertingPattern);
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [4] Populate optional parameter "correlationID".
     */

    {
        /*
         *  [4-1] Create CorrelationID object.
         */

        ITS_OCTET fixedArray3[] = { 0x30, 0x31, 0x32, 0x33, 0x34 };

        size_t fixedArray3Size = 5;

        INAP_CS1_CorrelationID
            correlationID =
                INAP_CS1_CorrelationID_ConstructWithArraySize(
                    fixedArray3,
                    fixedArray3Size);

        if (correlationID == NULL)
        {
            INAP_CS1_ConnectArg_Destruct(connectArg);

            return ITS_ENOMEM;
        }

        /*
         *  [4-2] Set CorrelationID object in ConnectArg object.
         */

        INAP_CS1_ConnectArg_SetCorrelationID(
            connectArg,
            correlationID);
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [5] Populate optional parameter "forwardingCondition".
     */

    {
        /*
         *  [5-1] Create ForwardingCondition object.
         */

        INAP_CS1_ForwardingCondition
            forwardingCondition =
                INAP_CS1_ForwardingCondition_ConstructDefault();

        if (forwardingCondition == NULL)
        {
            INAP_CS1_ConnectArg_Destruct(connectArg);

            return ITS_ENOMEM;
        }

        INAP_CS1_ForwardingCondition_SetAny(forwardingCondition);

        /*
         *  [5-2] Set ForwardingCondition object in ConnectArg object.
         */

        INAP_CS1_ConnectArg_SetForwardingCondition(
            connectArg,
            forwardingCondition);
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [6] Populate optional parameter "routeList".
     */

    {
        /*
         *  [6-1] Create RouteList object.
         */

        INAP_CS1_RouteList 
            routeList = 
                INAP_CS1_RouteList_ConstructDefault();

        if (routeList == NULL)
        {
            INAP_CS1_ConnectArg_Destruct(connectArg);

            return ITS_ENOMEM;
        }

        /*
         *  INAP API Note: a RouteList object contains a list of 
         *  RouteList_OCTETSTRING objects.
         */

        {
            /*
             *  [6-1-1] Create RouteList_OCTETSTRING object.
             */

            ITS_OCTET fixedArray4[] = { 0x01, 0x02, 0x03 };

            size_t fixedArray4Size = 3;

            INAP_CS1_RouteList_OCTETSTRING
                routeListOCTETSTRING1 =
                    INAP_CS1_RouteList_OCTETSTRING_ConstructWithArraySize(
                        fixedArray4,
                        fixedArray4Size);

            if (routeListOCTETSTRING1 == NULL)
            {
                INAP_CS1_ConnectArg_Destruct(connectArg);
                INAP_CS1_RouteList_Destruct(routeList);

                return ITS_ENOMEM;
            }

            /*
             *  [6-1-2] Add RouteList_OCTETSTRING object to RouteList object.
             */

            res =
                INAP_CS1_RouteList_AddElement(
                    routeList,
                    routeListOCTETSTRING1);

            if (res != ITS_SUCCESS)
            {
                INAP_CS1_ConnectArg_Destruct(connectArg);
                INAP_CS1_RouteList_Destruct(routeList);
                INAP_CS1_RouteList_OCTETSTRING_Destruct(routeListOCTETSTRING1);

                return ITS_ENOMEM;
            }
        }

        {
            /*
             *  [6-1-3] Create RouteList_OCTETSTRING object.
             */

            ITS_OCTET fixedArray5[] = { 0x11, 0x22, 0x33, 0x44 };

            size_t fixedArray5Size = 4;

            INAP_CS1_RouteList_OCTETSTRING
                routeListOCTETSTRING2 =
                    INAP_CS1_RouteList_OCTETSTRING_ConstructWithArraySize(
                        fixedArray5,
                        fixedArray5Size);

            if (routeListOCTETSTRING2 == NULL)
            {
                INAP_CS1_ConnectArg_Destruct(connectArg);
                INAP_CS1_RouteList_Destruct(routeList);

                return ITS_ENOMEM;
            }

            /*
             *  [6-1-4] Add RouteList_OCTETSTRING object to RouteList object.
             */

            res =
                INAP_CS1_RouteList_AddElement(
                    routeList,
                    routeListOCTETSTRING2);

            if (res != ITS_SUCCESS)
            {
                INAP_CS1_ConnectArg_Destruct(connectArg);
                INAP_CS1_RouteList_Destruct(routeList);
                INAP_CS1_RouteList_OCTETSTRING_Destruct(routeListOCTETSTRING2);

                return ITS_ENOMEM;
            }
        }

        {
            /*
             *  [6-1-5] Create RouteList_OCTETSTRING object.
             */

            ITS_OCTET fixedArray6[] = { 0x10, 0x20, 0x30, 0x40, 0x50 };

            size_t fixedArray6Size = 5;

            INAP_CS1_RouteList_OCTETSTRING
                routeListOCTETSTRING3 =
                    INAP_CS1_RouteList_OCTETSTRING_ConstructWithArraySize(
                        fixedArray6,
                        fixedArray6Size);

            if (routeListOCTETSTRING3 == NULL)
            {
                INAP_CS1_ConnectArg_Destruct(connectArg);
                INAP_CS1_RouteList_Destruct(routeList);

                return ITS_ENOMEM;
            }

            /*  
             *  [6-1-6] Add RouteList_OCTETSTRING object to RouteList object.
             */

            res =
                INAP_CS1_RouteList_AddElement(
                    routeList,
                    routeListOCTETSTRING3);

            if (res != ITS_SUCCESS)
            {
                INAP_CS1_ConnectArg_Destruct(connectArg);
                INAP_CS1_RouteList_Destruct(routeList);
                INAP_CS1_RouteList_OCTETSTRING_Destruct(routeListOCTETSTRING3);

                return ITS_ENOMEM;
            }
        }

        /*
         *  [6-2] Set RouteList object in ConnectArg object.
         */

        INAP_CS1_ConnectArg_SetRouteList(connectArg, routeList);
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [7] Populate optional parameter "callingPartyNumber".
     */

    {
        /*
         *  [7-1] Create CallingPartyNumber object.
         */

        ITS_OCTET fixedArray7[] = { 0x07, 0x07, 0x08, 0x09, 0x09, 0x08, 0x04 };

        size_t fixedArray7Size = 7;

        INAP_CS1_CallingPartyNumber
            callingPartyNumber =
                INAP_CS1_CallingPartyNumber_ConstructWithArraySize(
                    fixedArray7,
                    fixedArray7Size);

        if (callingPartyNumber == NULL)
        {
            INAP_CS1_ConnectArg_Destruct(connectArg);

            return ITS_ENOMEM;
        }

        /*
         *  [7-2] Set CallingPartyNumber object in ConnectArg object.
         */

        INAP_CS1_ConnectArg_SetCallingPartyNumber(
            connectArg, 
            callingPartyNumber);
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [8] Encode ConnectArg object.
     */

    {
        ASN_EncodeError encodeError         = NULL;
        int encodeErrorCode                 = ITS_SUCCESS;
        const char* encodeErrorText         = NULL;
        const char* encodeExtendedErrorText = NULL;


        res = INAP_CS1_ConnectArg_Encode(
                connectArg, 
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


            /* 
             * Retrieve and print encode error code. 
             */

            encodeErrorCode = 
                ASN_EncodeError_GetError(
                    encodeError);

            printf(
                "\nEncode error code is <%d>.\n\n", 
                encodeErrorCode);

            /* 
             *  Retrieve and print encode error text (freed automatically when
             *  encodeError object is destructed).                               
             */

            encodeErrorText = 
                ASN_EncodeError_GetErrorText(encodeError);

            if (encodeErrorText == NULL)
            {
                INAP_CS1_ConnectArg_Destruct(connectArg);
                ASN_EncodeError_Destruct(encodeError);

                return ITS_ENOMEM;
            }

            printf(
                "\nEncode error text is <%s>.\n\n", 
                encodeErrorText);

            /* 
             *  Retrieve and print extended encode error text (freed 
             *  automatically when encodeError object is destructed).
             */

            encodeExtendedErrorText = 
                ASN_EncodeError_GetExtendedErrorText(
                    encodeError);

            if (encodeExtendedErrorText == NULL)
            {
                INAP_CS1_ConnectArg_Destruct(connectArg);
                ASN_EncodeError_Destruct(encodeError);

                return ITS_ENOMEM;
            }

            printf(
                "\nEncode error extended text is <%s>.\n\n", 
                encodeExtendedErrorText);

            INAP_CS1_ConnectArg_Destruct(connectArg);

            /* 
             *  Object encodeError must be destructed by end-user. 
             */

            ASN_EncodeError_Destruct(encodeError);

            return res;
        }
        else if (res != ITS_SUCCESS)
        {
            INAP_CS1_ConnectArg_Destruct(connectArg);

            return res;
        }
        else
        {
            /* 
             *  res == ITS_SUCCESS. Nothing to do. Continue processing. 
             */
        }

        /*
         *  Print contents of ASN.1 encoded value.
         */

        printf("\nPrinting ConnectArg ASN.1 encoded value...\n\n");

        ASN_Octets_Print(octets);

        printf("\n");
    }

    /*------------------------------------------------------------------------*/

    /*
     *  [9] Retrieve ConnectArg ASN.1 encoded value from octets object and
     *  return ConnectArg ASN.1 encoded value through the function parameters
     *  octetArray and size.
     */

    *octetArray = 
        (ITS_OCTET*)calloc(
            ASN_Octets_GetSize(octets), 
            sizeof(ITS_OCTET));

    if (*octetArray == NULL)
    {
        INAP_CS1_ConnectArg_Destruct(connectArg);
        ASN_Octets_Destruct(octets);

        return ITS_ENOMEM;
    }

    memcpy(
        *octetArray, 
        ASN_Octets_GetArray(octets), 
        ASN_Octets_GetSize(octets));

    *size = ASN_Octets_GetSize(octets);

    /*------------------------------------------------------------------------*/

    /*
     *  [10] Free all memory allocated on the heap.
     */

    /*
     *  [10-1] Delete ConnectArg object (and therefore all the parameter 
     *  objects that have been previously set).
     */

    INAP_CS1_ConnectArg_Destruct(connectArg);

    /*
     *  [10-2] Delete Octets object created by the call to 
     *  INAP_CS1_ConnectArg_Encode.
     */

    ASN_Octets_Destruct(octets);

    /*------------------------------------------------------------------------*/

    /*
     *  Return success.
     */

    return ITS_SUCCESS;
}

