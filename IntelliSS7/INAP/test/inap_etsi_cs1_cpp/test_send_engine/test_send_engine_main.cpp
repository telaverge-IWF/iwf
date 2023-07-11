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
//  ID: $Id: test_send_engine_main.cpp,v 9.1 2005/03/23 12:51:47 cvsadmin Exp $
//
///////////////////////////////////////////////////////////////////////////////

//
//  ETSI INAP CS1 send example.
//
//  This example shows how to send the argument of an ETSI INAP Connect 
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

#include <engine++.h>
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
#include <vframe.h>

#include <tcap++.h>

#include <Asn.h>
//#include <AsnException.h>

#include <inap_cpp.h>
//#include <inap_etsi_cs1_connect_arg.h>

//#include <UnitTest.h>

using namespace std;
using namespace its;
using namespace inap;
//using namespace inap_china_cs1;

#if defined(WIN32)
#define EXPORTFUNC   __declspec(dllexport)
#else // !defined(WIN32)
#define EXPORTFUNC
#endif // defined(WIN32)

/* Encode method */
typedef vector<byte> (*EncodeProc)();

typedef struct
{
    ITS_USHORT opCode;
    EncodeProc encProc;
    const char* name;
}
OPERATION_Info;

///////////////////////////////////////////////////////////////////////////////
//
//  External function declarations.
//

extern vector<byte> BuildOperationConnectArg();

extern vector<byte> BuildOperationConnectToResourceArg();

extern vector<byte> BuildOperationEstablishTemporaryConnectionArg();

extern vector<byte> BuildOperationPlayAnnouncementArg();

extern vector<byte> BuildOperationPromptAndCollectUserInformationArg();

extern vector<byte> BuildOperationSendChargingInformationArg();

extern vector<byte> BuildOperationEventReportBCSMArg();

OPERATION_Info opInfo[] =
    {{ OP_connect,
       BuildOperationConnectArg,
       "ConnectArg" },
     { OP_connectToResource,
       BuildOperationConnectToResourceArg,
       "ConnectToResourceArg" },
     { OP_establishTemporaryConnection,
       BuildOperationEstablishTemporaryConnectionArg,
       "EstablishTemporaryConnectionArg" },
     { OP_playAnnouncement,
       BuildOperationPlayAnnouncementArg,
       "PlayAnnouncementArg" },
     { OP_promptAndCollectUserInformation,
       BuildOperationPromptAndCollectUserInformationArg,
       "PromptAndCollectUserInformationArg" },
     { OP_activityTest,
       NULL,
       "ActivityTest" },
     { OP_eventReportBCSM,
       BuildOperationEventReportBCSMArg,
       "EventReportBCSMArg" },
     { OP_sendChargingInformation,
       BuildOperationSendChargingInformationArg,
       "SendChargingInformationArg" }};
 
///////////////////////////////////////////////////////////////////////////////
//
//  Definitions for SCCP addresses.
//

#define SCCP_ADDR_INDICATOR (SCCP_CPA_ROUTE_INT |   \
                             SCCP_CPA_ROUTE_SSN |   \
                             SCCP_CPA_HAS_PC    |   \
                             SCCP_CPA_HAS_SSN)
#if 0
#define LOCAL_PC    2057
#define LOCAL_SSN   254

#define REMOTE_PC   4114
#define REMOTE_SSN  254
#endif

static ITS_UINT localPc, localSsn, remotePc, remoteSsn;

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

extern "C" void
MTP3_Callback(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    ITS_UINT pc;
    MTP3_PAUSE_RESUME mtp3_pause_resume;
    ITS_OCTET mType;
    MTP3_HEADER mtpHdr;
    ITS_USHORT len;

    ITS_EVENT* ev = (ITS_EVENT *)callData;

    cout << "MTP3 Callback called" << endl;

    MTP3_Decode(ev, &mType, &mtpHdr,
                (ITS_OCTET *)&mtp3_pause_resume, &len);

    pc = MTP3_PC_GET_VALUE(mtp3_pause_resume.affected);

    TRANSPORT_Control* base = (TRANSPORT_Control *)object;

    if (ev->data[0] == MTP3_MSG_RESUME)
    {
        cout << "Received MTP3-RESUME on pc = "<< pc << endl;
    }
    else if (ev->data[0] == MTP3_MSG_PAUSE)
    {
        cout << "Received MTP3-PAUSE on pc = "<< pc << endl;
    }
}

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

extern "C" EXPORTFUNC void
ApplicationPreFunc()
{
    string value;

    ITS_ResourceManager *rf = new ITS_ResourceManager(APPL_GetConfigFileName());

    if (rf->GetKeyValueOf("", "LOCAL_PC", value) == ITS_SUCCESS)
    {
        localPc = atoi(value.c_str());
    }

    if (rf->GetKeyValueOf("", "REMOTE_PC", value) == ITS_SUCCESS)
    {
        remotePc = atoi(value.c_str());
    }

    if (rf->GetKeyValueOf("", "LOCAL_SSN", value) == ITS_SUCCESS)
    {
        localSsn = atoi(value.c_str());
    }

    if (rf->GetKeyValueOf("", "REMOTE_SSN", value) == ITS_SUCCESS)
    {
        remoteSsn = atoi(value.c_str());
    }
  
    if (CALLBACK_AddCallback(MTP3_CCITT_ManagementCallbacks,
                            MTP3_Callback, NULL) != ITS_SUCCESS)
    {
        cout << "Error adding callback..." << endl;

        ITS_GlobalStop();

        exit(0);
    }

    cout << "Successful return from ApplicationPreFunc" << endl;
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

int MenuOption()
{
    int input;

    ///////////////////////////////////////////////////////////////////////////
    //  Provide multiple messages selection

    cout << endl;
    cout << "==========================================================\n";
    cout << endl;
    cout << "Choose a message to send:" << endl;
    cout << endl;

    for (int i = 0; i < sizeof(opInfo)/sizeof(opInfo[0]); ++i)
    {
        cout << i << ". " << opInfo[i].name << endl;
    }

    scanf("%i", &input);

    return input;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Main test function.
//
void Test::Run()
{
    int choice = MenuOption();

    ///////////////////////////////////////////////////////////////////////////
    //
    //  Execute ETSI INAP operation Connect:
    //  
    //  o   Allocate new dialogue ID.
    //
    //  o   Build TCAP begin dialogue.
    //
    //  o   Build TCAP invoke component.
    //
    //  o   Call function to build ETSI INAP Connect operation argument.
    //
    //  o   Send TCAP invoke component.
    //  
    //  o   Send TCAP begin dialogue.
    //

    ITS_HANDLE handle = GetHandle();


    ITS_USHORT dialogueID = 0;

    TCAP_AllocateDialogueId(ISS7_CCITT_Stack, &dialogueID);


    // Create begin dialogue (dlg) object and populate it.

    TCAP_Begin beginDlg;

    beginDlg.SetDialogueID(dialogueID);

    beginDlg.SetOrigAddr(
                SCCP_ADDR_INDICATOR, 
                localPc, 
                localSsn, 
                NULL, 
                0);

    beginDlg.SetDestAddr(
                SCCP_ADDR_INDICATOR, 
                remotePc, 
                remoteSsn, 
                NULL, 
                0);

    // Create invoke component (cpt) object and populate it.

    TCAP_Invoke invokeCpt;

    invokeCpt.SetInvokeID(1);

    // "OP_connect" is defined in file inap_cpp.h.

    invokeCpt.SetOperation(opInfo[choice].opCode); 

    // Class 2 (only errors appear in the INAP Connect operation macro, see
    // INAP recommendation Q.1218).

    invokeCpt.SetClass(2);

    ///////////////////////////////////////////////////////////////////////////
    //
    //  Function call uses ETSI INAP ASN.1 C++ API.
    //

    if (opInfo[choice].encProc)
    {
        vector<byte> encodedBytes = opInfo[choice].encProc();

    //
    ///////////////////////////////////////////////////////////////////////////

    // The parameter field of the TCAP invoke component contains the ETSI
    // INAP operation argument.

        invokeCpt.SetParameter(encodedBytes);
    }

    cout << endl << "Ready to execute ETSI INAP " << opInfo[choice].name
         << " operation..." << endl;
  
    TCAP_Component::Send(ISS7_CCITT_Stack, &beginDlg, &invokeCpt);

    TCAP_Dialogue::Send(ISS7_CCITT_Stack, &beginDlg);

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

            res = TCAP_Component::Receive(ISS7_CCITT_Stack, event, recvDlg, &recvCpt);

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
            case TCAP_PT_TC_END_CCITT:
            {
                cout << "End dialogue." << endl;

                TCAP_End* recvEndDlg = static_cast<TCAP_End*>(recvDlg);

                stop = true; // Exit receive loop.

                break;
            }

            case TCAP_PT_TC_P_ABORT_CCITT:
                cout << "P_ABORT received" << endl;
                break;

            case TCAP_PT_TC_U_ABORT_CCITT:
                cout << "U_ABORT received" << endl;
                break;

            case TCAP_PT_TC_UNI_CCITT:
            case TCAP_PT_TC_BEGIN_CCITT:
            case TCAP_PT_TC_CONTINUE_CCITT:
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
    cout << endl << "Begin ETSI INAP CS1 send example..." << endl;

    ///////////////////////////////////////////////////////
    // Set Application name (allow to find XML init file).

#if defined(WIN32)
    APPL_SetName("test_send_win32");
#else // !defined(WIN32)
    APPL_SetName("test_send_unix");
#endif // defined(WIN32)

    ENGINE_Initialize(argc, argv, NULL, 0);

    ENGINE_Run(argc, argv);

    cout << endl << "End of ETSI INAP CS1 send example..." << endl;

    return EXIT_SUCCESS;
}
