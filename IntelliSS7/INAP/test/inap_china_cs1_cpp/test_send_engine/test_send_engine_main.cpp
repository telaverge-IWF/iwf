///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//      Copyright 2002 IntelliNet Technologies, Inc. All Rights Reserved.    //
//              Manufactured in the United States of America.                //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       //
//                                                                           //
//    This product and related documentation is protected by copyright and   //
//    distributed under licenses restricting its use, copying, distribution  //
//    and decompilation.  No part of this product or related documentation   //
//    may be reproduced in any form by any means without prior written       //
//    authorization of IntelliNet Technologies and its licensors, if any.    //
//                                                                           //
//    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      //
//    government is subject to restrictions as set forth in subparagraph     //
//    (c)(1)(ii) of the Rights in Technical Data and Computer Software       //
//    clause at DFARS 252.227-7013 and FAR 52.227-19.                        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// CONTRACT: INTERNAL                                                        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//
//  ID: $Id: test_send_engine_main.cpp,v 9.1 2005/03/23 12:51:45 cvsadmin Exp $
//
///////////////////////////////////////////////////////////////////////////////

//
//  INAP CHINA CS1 send example.
//
//  This example shows how to send the argument of an INAP CHINA Connect 
//  operation.
//
//  The part used to build (create, insert data and encode) the Connect 
//  operation argument is identical the test_codec example.
//

//
//  C++ related note:
//  
//  The code relies on STL (C++ Standard Template Library). A basic knowledge
//  of STL is assumed (mainly classes std::vector and std::list). Likewise, a 
//  basic knowledge of C++ standard classes (e.g. std::string, std::ostream...) 
//  is also assumed. 
// 


#include <its++.h>


#include <iostream>

#include <its_app.h>
#include <its_trace.h>
#include <its_assertion.h>
#include <its_thread_pool.h>
#include <its_transports.h>
#include <its_assertion.h>
#include <its_thread.h>
#include <its_worker.h>
#include <its_assertion.h>
#include <its_gen_disp.h>
#include <its_service.h>
#include <engine.h>

#include <tcap++.h>

#include <Asn.h>
#include <AsnException.h>

#include <inap_cpp.h>
#include <inap_china_cs1_connect_arg.h>


using namespace std;
using namespace its;
using namespace inap;
using namespace inap_china_cs1;

#if defined(WIN32)
#define EXPORTFUNC   __declspec(dllexport)
#else // !defined(WIN32)
#define EXPORTFUNC
#endif // defined(WIN32)


///////////////////////////////////////////////////////////////////////////////
//
//  Local function declarations.
//

vector<byte> BuildOperationConnectArg();


///////////////////////////////////////////////////////////////////////////////
//
//  Definitions for SCCP addresses.
//

#define SCCP_ADDR_INDICATOR (SCCP_CPA_ROUTE_NAT |   \
                             SCCP_CPA_ROUTE_SSN |   \
                             SCCP_CPA_HAS_PC    |   \
                             SCCP_CPA_HAS_SSN)

#define LOCAL_PC    1
#define LOCAL_SSN   2

#define REMOTE_PC   2
#define REMOTE_SSN  2


///////////////////////////////////////////////////////////////////////////////
//
// Test.
//

class Test
{
public:

    Test()
    {
        // Nothing to do.
    }

    ~Test()
    {
        // Nothing to do.
    }

    void 
    SetHandle(ITS_HANDLE handle)
    {
        _handle = handle;
    }

    ITS_HANDLE
    GetHandle() const
    {
        return _handle;
    }

    void Run(); // Main test function (see below).

protected:

    ITS_HANDLE _handle;
};


///////////////////////////////////////////////////////////////////////////////
//
//  ApplicationSelector (always returns MainThread phony Border Transport
//  instance). Phony Border Transport approach is a simple way to have an
//  example with one dedicated main thread of execution within IntelliSS7
//  Engine. 
//

extern "C" EXPORTFUNC ITS_USHORT
ApplicationSelector(ITS_HDR* hdr, ITS_EVENT* event)
{
    static ITS_USHORT mainThreadTransportInstance = 0;

    if (mainThreadTransportInstance == 0)
    {
        TRANSPORT_Control* tc = TRANSPORT_FindTransportByName("MainThread");

        if (tc == NULL)
        {
            printf("\nUnable to find MainThread phony Border Transport\n\n");
        }
        else
        {
            mainThreadTransportInstance = tc->transport.instance;
        }
    }

    if (mainThreadTransportInstance != 0)
    {
        return mainThreadTransportInstance;
    }
    else
    {
        return ITS_DEFAULT_USER_SRC;
    }
}


///////////////////////////////////////////////////////////////////////////////
//
//  MainThreadFunction (to be called by Engine through MainThread phony Border
//  Transport).
//

extern "C" EXPORTFUNC void
MainThreadFunction(ThreadPoolThread* thread, void* arg)
{
    Worker* worker = static_cast<Worker*>(thread);
    DISP_FuncsCPP* cbs = static_cast<DISP_FuncsCPP*>(arg);
    ITS_HANDLE handle = NULL;

    ITS_C_REQUIRE(worker != NULL);
    ITS_C_REQUIRE(cbs != NULL);

    if (cbs->PreInitialize)
    {
        if ((cbs->PreInitialize)(thread) != ITS_SUCCESS)
        {
            free(cbs);

            return;
        }
    }

    handle = ITS_Initialize(worker->GetMask(), worker->GetInstance());

    if (cbs->PostInitialize)
    {
        if ((cbs->PostInitialize)(thread, handle) != ITS_SUCCESS)
        {
            if (handle)
            {
                ITS_Terminate(handle);
            }

            free(cbs);

            return;
        }
    }
    else if (handle == NULL)
    {
        if (cbs->PostTerminate)
        {
            (cbs->PostTerminate)(thread);
        }

        return;
    }

    // Dispatcher loop => Changed to run test.
    while (!worker->GetExit())
    {
        Test test;

        test.SetHandle(handle);

        test.Run();

        // Stop application.
        SERVICE_DefaultStopHandler();
        SERVICE_SetStopped();

        // Stop loop.
        break;
    }
    
    if (cbs->PreTerminate)
    {
        (cbs->PreTerminate)(thread);
    }

    ITS_Terminate(handle);

    if (cbs->PostTerminate)
    {
        (cbs->PostTerminate)(thread);
    }

    free(cbs);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Main test function.
//

void Test::Run()
{
    ///////////////////////////////////////////////////////////////////////////
    //
    //  Execute INAP CHINA operation Connect:
    //  
    //  o   Allocate new dialogue ID.
    //
    //  o   Build TCAP begin dialogue.
    //
    //  o   Build TCAP invoke component.
    //
    //  o   Call function to build INAP CHINA Connect operation argument.
    //
    //  o   Send TCAP invoke component.
    //  
    //  o   Send TCAP begin dialogue.
    //

    ITS_HANDLE handle = GetHandle();


    ITS_USHORT dialogueID = 0;

    TCAP_AllocateDialogueId(handle, &dialogueID);


    // Create begin dialogue (dlg) object and populate it.

    TCAP_Begin beginDlg;

    beginDlg.SetDialogueID(dialogueID);

    beginDlg.SetOrigAddr(
                SCCP_ADDR_INDICATOR, 
                LOCAL_PC, 
                LOCAL_SSN, 
                NULL, 
                0);

    beginDlg.SetDestAddr(
                SCCP_ADDR_INDICATOR, 
                REMOTE_PC, 
                REMOTE_SSN, 
                NULL, 
                0);

    // Create invoke component (cpt) object and populate it.

    TCAP_Invoke invokeCpt;

    invokeCpt.SetInvokeID(1);

    // "OP_connect" is defined in file inap_cpp.h.

    invokeCpt.SetOperation(OP_connect); 

    // Class 2 (only errors appear in the INAP Connect operation macro, see
    // INAP recommendation Q.1218).

    invokeCpt.SetClass(2);

    ///////////////////////////////////////////////////////////////////////////
    //
    //  Function call uses INAP CHINA ASN.1 C++ API.
    //

    vector<byte> encodedConnectArg = BuildOperationConnectArg();

    //
    ///////////////////////////////////////////////////////////////////////////


    // The parameter field of the TCAP invoke component contains the INAP
    // CHINA Connect operation argument.

    invokeCpt.SetParameter(encodedConnectArg);


    cout << endl << "Ready to execute INAP CHINA Connect operation..." << endl;
  
    TCAP_Component::Send(handle, &beginDlg, &invokeCpt);

    TCAP_Dialogue::Send(handle, &beginDlg);

    ///////////////////////////////////////////////////////////////////////////
    //
    //  Receive loop:
    //  
    //  o   Receive TCAP end dialogue (sent by test_receive_engine example).
    //
    //  o   Exit loop.
    //

    TCAP_Dialogue* recvDlg       = NULL;
    TCAP_Component* recvCpt      = NULL;
    ITS_USHORT currentDialogueID = 0;

    bool stop = false;

	while (!stop)
	{
        ITS_Event event;

		int res = ITS_GetNextEvent(handle, &event.GetEvent());

        if (res != ITS_SUCCESS)
        {
            ITS_Error itsError(res, __FILE__, __LINE__);

            cout << endl << itsError.GetDescription() << endl;

            continue;
        }

        cout << endl << "Received Event..." << endl;

        cout << "Source: <" << event.GetSource() << ">." << endl;

        if (TCAP_MSG_TYPE(&event.GetEvent()) == ITS_TCAP_CPT)
        {
            if (recvCpt != NULL)
            {
                delete recvCpt;
                recvCpt = NULL;
            }

            res = TCAP_Component::Receive(handle, event, recvDlg, &recvCpt);

            if (res != ITS_SUCCESS)
            {
                throw ITS_Error(res, __FILE__, __LINE__); // Fatal error.
            }

            cout << endl << "Receive TCAP component..." << endl;
        }
        else if (TCAP_MSG_TYPE(&event.GetEvent()) == ITS_TCAP_DLG)
        {
            if (recvDlg != NULL)
            {
                delete recvDlg;
                recvDlg = NULL;
            }

            res = TCAP_Dialogue::Receive(handle, event, &recvDlg);

            if (res != ITS_SUCCESS)
            {
                throw ITS_Error(res, __FILE__, __LINE__); // Fatal error.
            }

            cout << endl << "Received TCAP dialogue..." << endl;

            currentDialogueID = recvDlg->GetDialogueID();

            cout << "Dialogue ID: <" << currentDialogueID << ">." << endl;

            switch (recvDlg->GetDialogueType())
            {
            case TCAP_PT_TC_END_CCITT:
            {
                cout << "End dialogue." << endl;

                TCAP_End* recvEndDlg = static_cast<TCAP_End*>(recvDlg);

                stop = true; // Exit receive loop.

                break;
            }

            case TCAP_PT_TC_UNI_CCITT:
            case TCAP_PT_TC_BEGIN_CCITT:
            case TCAP_PT_TC_CONTINUE_CCITT:
            case TCAP_PT_TC_P_ABORT_CCITT:
            case TCAP_PT_TC_U_ABORT_CCITT:
            case TCAP_PT_TC_NOTICE_CCITT:
            {
                // Should be processed by complete code.

                stop = true; // Exit receive loop.

                break;
            }

            default:
            {
                // Should not be reached.

                break;
            }
            } // Switch.
        }
	}

    if (recvDlg != NULL)
    {
        delete recvDlg;
        recvDlg = NULL;
    }

    if (recvCpt != NULL)
    {
        delete recvDlg;
        recvDlg = NULL;
    }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Entry point.
//

int main(int argc, const char** argv)
{
    cout << endl << "Begin INAP CHINA CS1 send example..." << endl;

    ///////////////////////////////////////////////////////
    // Set Application name (allow to find XML init file).

#if defined(WIN32)
    APPL_SetName("test_send_win32");
#else // !defined(WIN32)
    APPL_SetName("test_send_unix");
#endif // defined(WIN32)

    ENGINE_Initialize(argc, argv, NULL, 0);

    ENGINE_Run(argc, argv);

    cout << endl << "End of INAP CHINA CS1 send example..." << endl;

    return EXIT_SUCCESS;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
//  Following code is identical to test_codec example.
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
//  Utilities.
//

//
//  Macro to get the size (count of items) of a fixed array.
//
#define FixedArraySize(array)       \
    (sizeof(array) / sizeof(array[0]))

//
//  Macro to convert fixed arrays (of bytes) to vectors.
//
#define FixedByteArrayToVector(array)   \
    (vector<byte>(array, array + FixedArraySize(array)))



///////////////////////////////////////////////////////////////////////////////
//
//  How to Build an INAP CHINA Connect operation argument (ConnectArg):
//
//  o   Create ConnectArg object.
//
//  o   Insert data step by step in the created ConnectArg object (i.e. 
//      populate various parameters of the Connect operation argument).
//  
//  o   Encode the ConnectArg object to produce a ConnectArg encoded value.
//

vector<byte> 
BuildOperationConnectArg()
{
    //  [1] Create ConnectArg object.

    ConnectArg* connectArg = new ConnectArg();

    ///////////////////////////////////////////////////////////////////////////

    //  Memory management note: all the following parameter objects that are
    //  used to populate the ConnectArg object must be created in the heap 
    //  (i.e. using operator new) and not in the stack. They are automatically
    //  deleted when the connectArg object is deleted. Only the ConnectArg 
    //  object itself can be created in the stack. 

    ///////////////////////////////////////////////////////////////////////////

    //  [2] Populate mandatory parameter "destinationRoutingAddress".

    //  [2-1] Create DestinationRoutingAddress object.

    DestinationRoutingAddress* 
        destinationRoutingAddress =
            new DestinationRoutingAddress();
    
    //  INAP API Note: a DestinationRoutingAddress object contains a list of 
    //  CalledPartyNumber objects.

    //  [2-1-1] Create CalledPartyNumber object.

    byte fixedArray1[] = { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16 };

    CalledPartyNumber*
        calledPartyNumber =
            new CalledPartyNumber(FixedByteArrayToVector(fixedArray1));

    //  [2-1-2] Add CalledPartyNumber object to DestinationRoutingAddress 
    //  object. 

    destinationRoutingAddress->AddElement(calledPartyNumber);

    //  [2-2] Set DestinationRoutingAddress object in ConnectArg object.

    connectArg->SetDestinationRoutingAddress(destinationRoutingAddress);

    ///////////////////////////////////////////////////////////////////////////

    //  [3] Populate optional parameter "alertingPattern".

    //  [3-1] Create an AlertingPattern object.

    byte fixedArray2[] = { 0x20, 0x21, 0x22 };

    AlertingPattern* 
        alertingPattern =
            new AlertingPattern(FixedByteArrayToVector(fixedArray2));

    //  [3-2] Set AlertingPattern object in ConnectArg object.

    connectArg->SetAlertingPattern(alertingPattern);

    ///////////////////////////////////////////////////////////////////////////

    //  [4] Populate optional parameter "correlationID".

    //  [4-1] Create CorrelationID object.

    byte fixedArray3[] = { 0x30, 0x31, 0x32, 0x33, 0x34 };

    CorrelationID*
        correlationID =
            new CorrelationID(FixedByteArrayToVector(fixedArray3));

    //  [4-2] Set CorrelationID object in ConnectArg object.

    connectArg->SetCorrelationID(correlationID);

    ///////////////////////////////////////////////////////////////////////////

    //  [5] Populate optional parameter "callingPartyNumber".

    //  [5-1] Create CallingPartyNumber object.

    byte fixedArray7[] = { 0x07, 0x07, 0x08, 0x09, 0x09, 0x08, 0x04 };

    CallingPartyNumber*
        callingPartyNumber =
            new CallingPartyNumber(FixedByteArrayToVector(fixedArray7));

    //  [5-2] Set CallingPartyNumber object in ConnectArg object.

    connectArg->SetCallingPartyNumber(callingPartyNumber);

    ///////////////////////////////////////////////////////////////////////////

    //  [6] Encode ConnectArg object.

    Octets* octets = NULL;

    try
    {
        //  Can throw and AsnEncodeError execption. 

        octets = connectArg->Encode();
    }
    catch (AsnEncodeError& encodeError)
    {
        cout << endl << encodeError.GetDescription() << endl;

        //  More specific error processing should be added here.

        //  By default re-throw exception.

        throw encodeError;
    }

    cout << endl;
    cout << "Printing ConnectArg ASN.1 encoded value..." << endl;
    cout << *octets;
    cout << endl;

    ///////////////////////////////////////////////////////////////////////////

    //  [7] Retrieve ConnectArg ASN.1 encoded value from octets object.

    vector<byte> encodedConnectArg = octets->GetArray();

    ///////////////////////////////////////////////////////////////////////////

    //  [8] Free all memory allocated on the heap.

    //  [8-1] Delete ConnectArg object (and therefore all the parameter
    //  objects that have been previously set).

    delete connectArg;

    //  [8-2] Delete Octets object created by the call to Encode.

    delete octets;

    ///////////////////////////////////////////////////////////////////////////

    //  [9] Return (by value) ConnectArg ASN.1 encoded value.

    return encodedConnectArg;
}

