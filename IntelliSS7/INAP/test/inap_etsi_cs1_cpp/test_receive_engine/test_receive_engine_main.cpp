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
//  ID: $Id: test_receive_engine_main.cpp,v 9.1 2005/03/23 12:51:47 cvsadmin Exp $
//
///////////////////////////////////////////////////////////////////////////////

//
//  ETSI INAP CS1 receive example.
//
//  This example shows how to receive the argument of an ETSI INAP Connect 
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


using namespace std;
using namespace its;
using namespace inap;

#if defined(WIN32)
#define EXPORTFUNC   __declspec(dllexport)
#else // !defined(WIN32)
#define EXPORTFUNC
#endif // defined(WIN32)


///////////////////////////////////////////////////////////////////////////////
//
//  External function declarations.
//

extern void InterpretOperationConnectArg(
    const vector<byte>& encodedConnectArg);

extern void InterpretOperationConnectToResourceArg(
    const vector<byte>& encodedConnectToResourceArg);

extern void InterpretOperationEstablishTemporaryConnectionArg(
    const vector<byte>& encodedEstablishTemporaryConnectionArg);

extern void InterpretOperationPlayAnnouncementArg(
    const vector<byte>& encodedPlayAnnouncementArg);

extern void InterpretOperationPromptAndCollectUserInformationArg(
    const vector<byte>& encodedPromptAndCollectUserInformationArg);

extern void InterpretOperationSendChargingInformationArg(
    const vector<byte>& encodedSendChargingInformationArg);

extern void InterpretOperationEventReportBCSMArg(
    const vector<byte>& encodedEventReportBCSMArg);

typedef void (*DecodeProc)(const vector<byte>& encodedMsg);

typedef struct
{
    int opcode;
    DecodeProc decProc;
    const char* name;
}
OPERATION_Info;

OPERATION_Info opInfo[] =
    { { OP_connect,
        InterpretOperationConnectArg,
        "ConnectArg" },
      { OP_connectToResource,
        InterpretOperationConnectToResourceArg,
        "ConnectToResourceArg" },
      { OP_establishTemporaryConnection,
        InterpretOperationEstablishTemporaryConnectionArg,
        "EstablishTemporaryConnectionArg" },
      { OP_playAnnouncement,
        InterpretOperationPlayAnnouncementArg,
        "PlayAnnouncementArg" },
      { OP_promptAndCollectUserInformation,
        InterpretOperationPromptAndCollectUserInformationArg,
        "PromptAndCollectUserInformationArg" },
      { OP_activityTest,
        NULL,
        "activityTest" },
      { OP_sendChargingInformation,
        InterpretOperationSendChargingInformationArg,
        "SendChargingInformationArg" },
      { OP_eventReportBCSM,
        InterpretOperationEventReportBCSMArg,
        "EventReportBCSMArg" }
    };

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
    //  o   Call function to interpret ETSI INAP Connect operation argument.
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

            res = TCAP_Component::Receive(ISS7_CCITT_Stack, event, recvDlg, &recvCpt);

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

                // Selection according to ETSI INAP operation.

                for (int i = 0; i < sizeof(opInfo)/sizeof(opInfo[0]); ++i)
                {
                    if (operation == opInfo[i].opcode)
                    {
                        cout << "ETSI INAP " << opInfo[i].name
                             << " operation...\n" << endl; 

                        if (opInfo[i].decProc)
                        {
                            vector<byte> encodeBytes; 

                            recvInvokeCpt->GetParameter(encodeBytes);

                            opInfo[i].decProc(encodeBytes);
                        }
                    }
                }
#if 0
                switch (operation)
                {
                case OP_connect:
                {
                    vector<byte> encodedConnectArg;

                    // The parameter field of the TCAP invoke component
                    // contains the ETSI INAP Connect operation argument.

                    recvInvokeCpt->GetParameter(encodedConnectArg);

                    ///////////////////////////////////////////////////////////
                    //
                    //  Function call uses ETSI INAP ASN.1 C++ API.
                    //

                    InterpretOperationConnectArg(encodedConnectArg);

                    //
                    ///////////////////////////////////////////////////////////

                    break;
                }

                case OP_connectToResource:
                {
                    vector<byte> encodedConnectToResource;

                    // The parameter field of the TCAP invoke component
                    // contains the ETSI INAP ConnectToResource operation
                    // argument.

                    recvInvokeCpt->GetParameter(encodedConnectToResource);

                    ///////////////////////////////////////////////////////////
                    //
                    //  Function call uses ETSI INAP ASN.1 C++ API.
                    //

                    InterpretOperationConnectToResourceArg(
                        encodedConnectToResource);

                    //
                    ///////////////////////////////////////////////////////////

                    break;
                }

                case OP_establishTemporaryConnection:
                {
                    vector<byte> encodedEstablishTemporaryConnectionArg;

                    // The parameter field of the TCAP invoke component
                    // contains the ETSI INAP EstablishTemporaryConnectionArg
                    // operation argument.

                    recvInvokeCpt->GetParameter(
                        encodedEstablishTemporaryConnectionArg);

                    ///////////////////////////////////////////////////////////
                    //
                    //  Function call uses ETSI INAP ASN.1 C++ API.
                    //

                    InterpretOperationEstablishTemporaryConnectionArg(
                        encodedEstablishTemporaryConnectionArg);

                    //
                    ///////////////////////////////////////////////////////////

                    break;
                }

                case OP_playAnnouncement:
                {
                    vector<byte> encodedPlayAnnouncementArg;

                    // The parameter field of the TCAP invoke component
                    // contains the ETSI INAP Connect operation argument.

                    recvInvokeCpt->GetParameter(encodedPlayAnnouncementArg);

                    ///////////////////////////////////////////////////////////
                    //
                    //  Function call uses ETSI INAP ASN.1 C++ API.
                    //

                    InterpretOperationPlayAnnouncementArg(
                        encodedPlayAnnouncementArg);

                    //
                    ///////////////////////////////////////////////////////////

                    break;
                }
                default:
                {
                    // Should be processed by complete code (all other ETSI
                    // INAP operation codes).

                    break;
                }
                } // Switch.
#endif

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

                TCAP_Dialogue::Send(ISS7_CCITT_Stack, &endDlg);
            }
        }
        else if (TCAP_MSG_TYPE(&event.GetEvent()) == ITS_TCAP_DLG)
        {
            if (recvDlg != NULL)
            {
                delete recvDlg;
                recvDlg = NULL;
            }

            res = TCAP_Dialogue::Receive(ISS7_CCITT_Stack, event, &recvDlg);

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
    cout << endl << "Begin ETSI INAP CS1 receive example..." << endl;

    ///////////////////////////////////////////////////////
    // Set Application name (allow to find XML init file).

#if defined(WIN32)
    APPL_SetName("test_receive_win32");
#else // !defined(WIN32)
    APPL_SetName("test_receive_unix");
#endif // defined(WIN32)

    ENGINE_Initialize(argc, argv, NULL, 0);

    ENGINE_Run(argc, argv);

    cout << endl << "End of ETSI INAP CS1 receive example..." << endl;

    return EXIT_SUCCESS;
}
