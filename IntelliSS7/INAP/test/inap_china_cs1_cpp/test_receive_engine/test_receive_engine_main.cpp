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
//  ID: $Id: test_receive_engine_main.cpp,v 9.1 2005/03/23 12:51:45 cvsadmin Exp $
//
///////////////////////////////////////////////////////////////////////////////

//
//  INAP CHINA CS1 receive example.
//
//  This example shows how to receive the argument of an INAP CHINA Connect 
//  operation.
//
//  The part used to interpret (decode and retrieve data) for the Connect 
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

void InterpretOperationConnectArg(const vector<byte>& encodedConnectArg);


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
    //  Receive (infinite) loop:
    //
    //  o   Receive TCAP begin dialogue.
    //
    //  o   Receive TCAP invoke component.
    //
    //  o   Call function to interpret INAP CHINA Connect operation argument.
    //
    //  o   Send back TCAP end dialogue if last component.
    //
    //  o   Exit loop.
    //

    ITS_HANDLE handle = GetHandle();

    TCAP_Dialogue* recvDlg       = NULL;
    TCAP_Component* recvCpt      = NULL;
    ITS_USHORT currentDialogueID = 0;

	while (true)
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

            switch (recvCpt->GetComponentType())
            {
            case TCAP_PT_TC_INVOKE_CCITT:
            {
                cout << "Invoke component." << endl;

                TCAP_Invoke* recvInvokeCpt = 
                    static_cast<TCAP_Invoke*> (recvCpt);

                ITS_LONG operation = 0;

                recvInvokeCpt->GetOperation(operation);

                // Selection according to INAP CHINA operation.

                switch (operation)
                {
                case OP_connect:
                {
                    vector<byte> encodedConnectArg;

                    // The parameter field of the TCAP invoke component
                    // contains the INAP CHINA Connect operation argument.

                    recvInvokeCpt->GetParameter(encodedConnectArg);

                    ///////////////////////////////////////////////////////////
                    //
                    //  Function call uses INAP CHINA ASN.1 C++ API.
                    //

                    InterpretOperationConnectArg(encodedConnectArg);

                    //
                    ///////////////////////////////////////////////////////////

                    break;
                }

                default:
                {
                    // Should be processed by complete code (all other INAP
                    // CHINA operation codes).

                    break;
                }
                } // Switch.

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
                // Should be processed by complete code.

                break;
            }

            default:
            {
                // Should not be reached.

                break;
            }
            } // Switch. 

            // Last component?

            if (recvCpt->GetLast())
            {
                TCAP_End endDlg;

                endDlg.SetDialogueID(currentDialogueID);

                TCAP_Dialogue::Send(handle, &endDlg);
            }
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
            case TCAP_PT_TC_BEGIN_CCITT:
            {
                cout << "Begin dialogue." << endl;

                TCAP_Begin* recvBeginDlg = 
                    static_cast<TCAP_Begin*>(recvDlg);

                break;
            }

            case TCAP_PT_TC_UNI_CCITT:
            case TCAP_PT_TC_END_CCITT:
            case TCAP_PT_TC_CONTINUE_CCITT:
            case TCAP_PT_TC_P_ABORT_CCITT:
            case TCAP_PT_TC_U_ABORT_CCITT:
            case TCAP_PT_TC_NOTICE_CCITT:
            {
                // Should be processed by complete code.

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
        delete recvCpt;
        recvCpt = NULL;
    }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Entry point.
//

int main(int argc, const char** argv)
{
    cout << endl << "Begin INAP CHINA CS1 receive example..." << endl;

    ///////////////////////////////////////////////////////
    // Set Application name (allow to find XML init file).

#if defined(WIN32)
    APPL_SetName("test_receive_win32");
#else // !defined(WIN32)
    APPL_SetName("test_receive_unix");
#endif // defined(WIN32)

    ENGINE_Initialize(argc, argv, NULL, 0);

    ENGINE_Run(argc, argv);

    cout << endl << "End of INAP CHINA CS1 receive example..." << endl;

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
//  How to interpret an (encoded) INAP Connect operation argument (ConnectArg):
//
//  o   Decode a ConnectArg encoded value (i.e. create a ConnectArg object from
//      a ConnectArg encoded value).
//
//  o   Retrieve Data from a ConnectArg object.
//

void
InterpretOperationConnectArg(const vector<byte>& encodedConnectArg)
{
    //  [1] Create an Octets object from the ConnectArg ASN.1 encoded value.

    Octets* octets = new Octets(encodedConnectArg);

    ///////////////////////////////////////////////////////////////////////////

    //  [2] Create ConnectArg object (used by the decode phase).

    ConnectArg* connectArg = new ConnectArg();

    ///////////////////////////////////////////////////////////////////////////

    //  [3] Decode the ConnectArg ASN.1 encoded value and therefore populate 
    //  previously created ConnectArg object.

    try
    {
        //  Can throw and AsnDecodeError exception.

        connectArg->Decode(*octets);
    }
    catch (AsnDecodeError& decodeError)
    {
        cout << endl << decodeError.GetDescription() << endl;

        // More specific error processing should be added here.

        // By default re-throw exeception.

        throw decodeError;
    }

    cout << endl;
    cout << "Printing decoded ConnectArg object..." << endl;
    cout << *connectArg;
    cout << endl;

    ///////////////////////////////////////////////////////////////////////////

    //  [4] Retrieve mandatory parameter "destinationRoutingAddress".

    //  [4-1] Retrieve reference to DestinationRoutingAddress object.

    const DestinationRoutingAddress& 
        destinationRoutingAddress =
            connectArg->GetDestinationRoutingAddress();

    //  INAP API Note: a DestinationRoutingAddress object contains a list of 
    //  CalledPartyNumber objects.

    //  [4-2] Retrieve contents of DestinationRoutingAddress object.

    for (int i = 0; i < destinationRoutingAddress.Size(); i++)
    {
        //  [4-2-1] Retrieve reference to CalledPartyNumber object.

        const CalledPartyNumber&
            calledPartyNumber =
                destinationRoutingAddress.ElementAt(i);

        //  [4-2-2] Retrieve contents of CalledPartyNumber object.

        vector<byte> vector1 = calledPartyNumber.GetArray();

        //  Do something with vector of bytes...

        //  [4-2-3] Print CalledPartyNumber object.

        cout << endl;
        cout << "Printing CalledPartyNumber object..." << endl;
        cout << calledPartyNumber;
        cout << endl;
    }

    //  [4-3] Print DestinationRoutingAddress object.

    cout << endl;
    cout << "Printing DestinationRoutingAddress object..." << endl;
    cout << destinationRoutingAddress;
    cout << endl;

    ///////////////////////////////////////////////////////////////////////////

    //  [5] Retrieve optional parameter "alertingPattern".

    if (connectArg->OptionAlertingPattern())
    {
        //  [5-1] Retrieve reference to AlertingPattern object.

        const AlertingPattern&
            alertingPattern =
                connectArg->GetAlertingPattern();

        //  [5-2] Retrieve contents of AlertingPattern object.

        vector<byte> vector2 = alertingPattern.GetArray();

        // Do something with vector of bytes...

        //  [5-3] Print AlertingPattern object.

        cout << endl;
        cout << "Printing AlertingPattern object..." << endl;
        cout << alertingPattern;
        cout << endl;
    }

    ///////////////////////////////////////////////////////////////////////////

    //  [6] Retrieve optional parameter "correlationID".

    if (connectArg->OptionCorrelationID())
    {
        //  [6-1] Retrieve reference to CorrelationID object.

        const CorrelationID&
            correlationID = 
                connectArg->GetCorrelationID();

        //  [6-2] Retrieve contents of CorrelationID object.

        vector<byte> vector3 = correlationID.GetArray();

        // Do something with vector of bytes...

        //  [6-3] Print CorrelationID object.

        cout << endl;
        cout << "Printing CorrelationID object..." << endl;
        cout << correlationID;
        cout << endl;
    }

    ///////////////////////////////////////////////////////////////////////////

    //  [7] Retrieve optional parameter "callingPartyNumber".

    if (connectArg->OptionCallingPartyNumber())
    {
        //  [7-1] Retrieve reference to CallingPartyNumber object.

        const CallingPartyNumber&
            callingPartyNumber = 
                connectArg->GetCallingPartyNumber();

        //  [7-2] Retrieve contents of CallingPartyNumber object.

        vector<byte> vector5 = callingPartyNumber.GetArray();

        // Do something with vector of bytes...

        //  [7-3] Print CallingPartyNumber object.

        cout << endl;
        cout << "Printing CallingPartyNumber object..." << endl;
        cout << callingPartyNumber;
        cout << endl;
    }

    ///////////////////////////////////////////////////////////////////////////

    //  [8] Free all memory allocated on the heap.

    //  [8-1] Delete Octets object.

    delete octets;

    //  [8-2] Delete ConnectArg object.

    delete connectArg;
}
