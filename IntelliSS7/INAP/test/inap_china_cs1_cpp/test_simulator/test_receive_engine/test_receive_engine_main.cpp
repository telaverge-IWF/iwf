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
//  ID: $Id: 
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
#include <inap_china_cs1_call_gap_arg.h>
#include <inap_china_cs1_assist_request_instructions_arg.h>
#include <inap_china_cs1_cancel_arg.h>
#include <inap_china_cs1_initial_dp_arg.h>

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
void InterpretCallGapArg(const vector<byte>& encodedCallGapArg);
void InterpretAssistRequestInstArg(const vector<byte>& encodedAssistRequestInstructionsArg);
void InterpretCancelArg(const vector<byte>& encodedCancelArg);
void InterpretInitialDPArg(const vector<byte>& encodedInitialDPArg);

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

    TRANSPORT_Control* tc = NULL;

    if (mainThreadTransportInstance == 0)
    {
        // Start at 20000 because MainThread transport belongs to border pool.
        for (unsigned short i = 20000; i < 20064; i++)
        {
            tc = TRANSPORT_FindTransport(i);

            if (tc != NULL && strcmp(tc->transport.name, "MainThread") == 0)
            {
                break;
            }
        }

        if (tc == NULL)
        {
            printf("\nUnable to find MainThread phony Border Transport...\n\n");
        }
        else
        {
            printf("\nFound MainThread phony Border Transport...\n\n");

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

            res = TCAP_Component::Receive(ISS7_PRC_Stack, event, recvDlg, &recvCpt);

            if (res != ITS_SUCCESS)
            {
                throw ITS_Error(res, __FILE__, __LINE__); // Fatal error.
            }

            cout << endl << "Receive TCAP component..." << endl;

            switch (recvCpt->GetComponentType())
            {
            case TCAP_PT_TC_INVOKE_PRC:
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
                case OP_callGap:
                {
                    vector<byte> encodedCallGapArg;

                    recvInvokeCpt->GetParameter(encodedCallGapArg);

                    InterpretCallGapArg(encodedCallGapArg);

                    break;
                }
                case OP_assistRequestInstructions:
                {
                    vector<byte> encodedAssistRequestInstructionsArg;

                    recvInvokeCpt->GetParameter(encodedAssistRequestInstructionsArg);

                    InterpretAssistRequestInstArg(encodedAssistRequestInstructionsArg);

                    break;
                }
                case OP_cancel:
                {
                    vector<byte> encodedCancelArg;

                    recvInvokeCpt->GetParameter(encodedCancelArg);

                    InterpretCancelArg(encodedCancelArg);

                    break;
                }
                case OP_initialDP:
                {
                    vector<byte> encodedInitialDPArg;

                    recvInvokeCpt->GetParameter(encodedInitialDPArg);

                    InterpretInitialDPArg(encodedInitialDPArg);

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

            case TCAP_PT_TC_RESULT_L_PRC:
            case TCAP_PT_TC_U_ERROR_PRC:  
            case TCAP_PT_TC_R_REJECT_PRC: 
            case TCAP_PT_TC_RESULT_NL_PRC:
            case TCAP_PT_TC_L_CANCEL_PRC:
            case TCAP_PT_TC_U_CANCEL_PRC: 
            case TCAP_PT_TC_L_REJECT_PRC: 
            case TCAP_PT_TC_U_REJECT_PRC:
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

                TCAP_Dialogue::Send(ISS7_PRC_Stack, &endDlg);
            }
        }
        else if (TCAP_MSG_TYPE(&event.GetEvent()) == ITS_TCAP_DLG)
        {
            if (recvDlg != NULL)
            {
                delete recvDlg;
                recvDlg = NULL;
            }

            res = TCAP_Dialogue::Receive(ISS7_PRC_Stack, event, &recvDlg);

            if (res != ITS_SUCCESS)
            {
                throw ITS_Error(res, __FILE__, __LINE__); // Fatal error.
            }

            cout << endl << "Received TCAP dialogue..." << endl;

            currentDialogueID = recvDlg->GetDialogueID();

            cout << "Dialogue ID: <" << currentDialogueID << ">." << endl;

            switch (recvDlg->GetDialogueType())
            {
            case TCAP_PT_TC_BEGIN_PRC:
            {
                cout << "Begin dialogue." << endl;

                TCAP_Begin* recvBeginDlg = 
                    static_cast<TCAP_Begin*>(recvDlg);

                break;
            }

            case TCAP_PT_TC_UNI_PRC:
            case TCAP_PT_TC_END_PRC:
            case TCAP_PT_TC_CONTINUE_PRC:
            case TCAP_PT_TC_P_ABORT_PRC:
            case TCAP_PT_TC_U_ABORT_PRC:
            case TCAP_PT_TC_NOTICE_PRC:
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
InterpretAssistRequestInstArg(const vector<byte>& encodedAssistRequestInstructionsArg)
{
    //  [1] Create an Octets object from the AssistRequestInstructionsArg
    //      ASN.1 encoded value.

    Octets* octets = new Octets(encodedAssistRequestInstructionsArg);

    ///////////////////////////////////////////////////////////////////////////

    //  [2] Create AssistRequestInstructionsArg object (used by the decode phase).

    AssistRequestInstructionsArg* assistRequestInstArg = 
                                              new AssistRequestInstructionsArg();

    ///////////////////////////////////////////////////////////////////////////

    //  [3] Decode the assistRequestInstructionsArg ASN.1 encoded value and 
    //      therefore populate previously created AssistRequestInstructionsArg
    //      object.

    try
    {
        //  Can throw and AsnDecodeError exception.

        assistRequestInstArg->Decode(*octets);
    }
    catch (AsnDecodeError& decodeError)
    {
        cout << endl << decodeError.GetDescription() << endl;

        // More specific error processing should be added here.

        // By default re-throw exeception.

        throw decodeError;
    }

    cout << endl;
    cout << "Printing decoded assistRequestInstArg object..." << endl;
    cout << *assistRequestInstArg;
    cout << endl;

    //  [4] Free all memory allocated on the heap.

    //  [4-1] Delete Octets object.

    delete octets;

    //  [4-2] Delete assistRequestInstArg object.

    delete assistRequestInstArg;

    return;
}


void
InterpretCancelArg(const vector<byte>& encodedCancelArg)
{
    //  [1] Create an Octets object from the cancelArg ASN.1 encoded value.

    Octets* octets = new Octets(encodedCancelArg);

    ///////////////////////////////////////////////////////////////////////////

    //  [2] Create cancelArg object (used by the decode phase).

    CancelArg* cancelArg = new CancelArg();

    ///////////////////////////////////////////////////////////////////////////

    //  [3] Decode the cancelArg ASN.1 encoded value and therefore populate
    //  previously created CancelDPArg object.

    try
    {
        //  Can throw and AsnDecodeError exception.

        cancelArg->Decode(*octets);
    }
    catch (AsnDecodeError& decodeError)
    {
        cout << endl << decodeError.GetDescription() << endl;

        // More specific error processing should be added here.

        // By default re-throw exeception.

        throw decodeError;
    }

    cout << endl;
    cout << "Printing decoded CancelArg object..." << endl;
    cout << *cancelArg;
    cout << endl;

    //  [4] Free all memory allocated on the heap.

    //  [4-1] Delete Octets object.

    delete octets;

    //  [4-2] Delete cancelArg object.

    delete cancelArg;

    return;

}

void
InterpretInitialDPArg(const vector<byte>& encodedInitialDPArg)
{
    //  [1] Create an Octets object from the initialDPArg ASN.1 encoded value.

    Octets* octets = new Octets(encodedInitialDPArg);

    ///////////////////////////////////////////////////////////////////////////

    //  [2] Create InitialDPArg object (used by the decode phase).

    InitialDPArg* initialDPArg = new InitialDPArg();

    ///////////////////////////////////////////////////////////////////////////

    //  [3] Decode the initialDPArg ASN.1 encoded value and therefore populate
    //  previously created InitialDPArg object.

    try
    {
        //  Can throw and AsnDecodeError exception.

        initialDPArg->Decode(*octets);
    }
    catch (AsnDecodeError& decodeError)
    {
        cout << endl << decodeError.GetDescription() << endl;

        // More specific error processing should be added here.

        // By default re-throw exeception.

        throw decodeError;
    }

    cout << endl;
    cout << "Printing decoded InitialDPArg object..." << endl;
    cout << *initialDPArg;
    cout << endl;

    //  [4] Free all memory allocated on the heap.

    //  [4-1] Delete Octets object.

    delete octets;

    //  [4-2] Delete initialDPArg object.

    delete initialDPArg;

    return;

}


void
InterpretCallGapArg(const vector<byte>& encodedCallGapArg)
{

    //  [1] Create an Octets object from the callGapArg ASN.1 encoded value.

    Octets* octets = new Octets(encodedCallGapArg);

    ///////////////////////////////////////////////////////////////////////////

    //  [2] Create CallGapArg object (used by the decode phase).

    CallGapArg* callGapArg = new CallGapArg();

    ///////////////////////////////////////////////////////////////////////////

    //  [3] Decode the callGapArg ASN.1 encoded value and therefore populate 
    //  previously created CallGapArg object.

    try
    {
        //  Can throw and AsnDecodeError exception.

        callGapArg->Decode(*octets);
    }
    catch (AsnDecodeError& decodeError)
    {
        cout << endl << decodeError.GetDescription() << endl;

        // More specific error processing should be added here.

        // By default re-throw exeception.

        throw decodeError;
    }

    cout << endl;
    cout << "Printing decoded CallGapArg object..." << endl;
    cout << *callGapArg;
    cout << endl;


    //  [4] Free all memory allocated on the heap.

    //  [4-1] Delete Octets object.

    delete octets;

    //  [4-2] Delete callGapArg object.

    delete callGapArg;

    return;

}

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


    //  [4] Free all memory allocated on the heap.

    //  [4-1] Delete Octets object.

    delete octets;

    //  [4-2] Delete ConnectArg object.

    delete connectArg;
}
