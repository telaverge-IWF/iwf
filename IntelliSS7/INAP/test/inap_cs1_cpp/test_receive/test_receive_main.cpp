////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.     //
//              Manufactured in the United States of America.                 //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
//                                                                            //
//    This product and related documentation is protected by copyright and    //
//    distributed under licenses restricting its use, copying, distribution   //
//    and decompilation.  No part of this product or related documentation    //
//    may be reproduced in any form by any means without prior written        //
//    authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                            //
//    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//    government is subject to restrictions as set forth in subparagraph      //
//    (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//    clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CONTRACT: INTERNAL                                                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
//  ID: $Id: test_receive_main.cpp,v 9.1 2005/03/23 12:51:46 cvsadmin Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//  INAP CS1 receive example.
//
//  This example shows how to receive the argument of an INAP Connect operation.
//  The part used to interpret (decode and retrieve data) for the Connect 
//  operation argument is identical the test_codec example.
//

//
//  IntelliNet SS7 stack note:
//
//  The conditional sections of the code that are included if the preprocessor
//  symbol "USE_INTELLINET_STACK" is defined are required only if the IntelliNet
//  SS7 stack is used. The IntelliNet SS7 stack allows to run the example
//  without any SS7 hardware.
//
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

#if !defined(WIN32)
#include <signal.h>
#endif // defined(WIN32)

#include <iostream>

#include <its_app.h>
#include <its_transports.h>


#if defined(USE_INTELLINET_STACK)
#include <its_thread.h>
#include <its_semaphore.h>
#include <its_object.h>
//#include <its_ss7_stubs.h>
#include <its_object.h>

extern "C" ITS_Class itsINTELLISS7_Class;
#endif // defined(USE_INTELLINET_STACK)

#include <itu/sccp.h>
#include <itu/tcap.h>
#include <tcap++.h>

#include <Asn.h>
#include <AsnException.h>

#include <inap_cpp.h>
#include <inap_cs1_connect_arg.h>
#include <inap_cs1_initial_dp_arg.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace inap;
using namespace inap_cs1;
#endif // defined(ITS_STD_NAMESPACE)


////////////////////////////////////////////////////////////////////////////////
//
//  Temporary work around for missing symbols in IntelliNet Vendor Library.
//
//  => Must be removed when problem will be corrected.
//

extern "C" {

int ISUP_SetVariant_CCITT() { return 0; }
int CCITT_CallTable;
int CCITT_ISUP_Variant() { return 0; }
int ISUP_TlvEventToL3Message_CCITT() { return 0; }
int ISUP_L3MessageToTlvEvent_CCITT() { return 0; }
int ComputeMSize() { return 0; }

}


////////////////////////////////////////////////////////////////////////////////
//
//  Local function declarations.
//

void InterpretOperationConnectArg(const vector<byte>& encodedConnectArg);


////////////////////////////////////////////////////////////////////////////////
//
//  Simple break handler (specific for WIN32 and Unix).
//

#if defined(WIN32)
static BOOL WINAPI breakHandler(DWORD ctrlType)
{
    ITS_GlobalStop();

    exit(EXIT_SUCCESS);
}
#else // !defined(WIN32)
static void exitHandler(int sig)
{
    ITS_GlobalStop();

    exit(EXIT_SUCCESS);
}
#endif // defined(WIN32)



#if defined(USE_INTELLINET_STACK)

////////////////////////////////////////////////////////////////////////////////
//
//  Synchronization object (semaphore) used to synchronize primary thread and
//  border transport thread.
//

static ITS_Semaphore borderTransportSemaphore(0);


////////////////////////////////////////////////////////////////////////////////
//
//  Border transport thread class and thread function.
//

class BorderTransportThread : public ITS_Thread
{
public:

    BorderTransportThread()
    :   ITS_Thread(0, DispatchFunction),
        stopRequested(false)
    {}

    ~BorderTransportThread() {}

    void 
    StopRequested()
    { stopRequested = true; }

    bool 
    IsStopRequested() const
    { return stopRequested; }
  
    static THREAD_RET_TYPE DispatchFunction(void* arg);

protected:

    bool stopRequested;
};


THREAD_RET_TYPE
BorderTransportThread::DispatchFunction(void* arg)
{
    BorderTransportThread* current =
        static_cast<BorderTransportThread*>(arg);

    #if defined(USE_SOCKETS)

        ITS_HANDLE handle = ITS_Initialize(
                                    ITS_TCAP                    |
                                    ITS_TRANSPORT_SSOCKET       |
                                    ITS_TRANSPORT_SINGLE_USER,
                                    2);

#else // !defined(USE_SOCKETS)

    ITS_HANDLE handle = ITS_Initialize(
                                ITS_TCAP                    |
                                ITS_TRANSPORT_FIFO          |
                                ITS_TRANSPORT_SINGLE_USER,
                                2);

#endif // defined(USE_SOCKETS)

    //ITS_HANDLE handle = ITS_Initialize(
      //                          ITS_TCAP                    |
        //                        ITS_TRANSPORT_FIFO          |
          //                      ITS_TRANSPORT_SINGLE_USER,
            //                    2);

    if (handle == NULL)
    {
        ITS_Error itsError(ITS_ENOTRANSPORT, __FILE__, __LINE__);

        cout << endl << itsError.GetDescription() << endl;

        THREAD_NORMAL_EXIT;
    }

    // To signal primary thread that the border transport thread is running and
    // that the associated transport is initialized.

    borderTransportSemaphore.Post();

    ITS_Event event;

    while (!current->stopRequested)
    {

        int res = ITS_GetNextEvent(handle, &event.GetEvent());

        if (res != ITS_SUCCESS)
        {
            ITS_Error itsError(res, __FILE__, __LINE__);

            cout << endl << itsError.GetDescription() << endl;
        }
        else
        {
            // Set event source to MTP3 (for routing purpose).

            event.SetSource(ITS_MTP3_SRC);

            // Send event to IntelliNet stack (SCCP layer).
            
            ITS_Transport::PutEvent(ITS_SCCP_SRC, event);
        }
    }

    ITS_Terminate(handle);

    THREAD_NORMAL_EXIT;
}

#endif // defined(USE_INTELLINET_STACK)


////////////////////////////////////////////////////////////////////////////////
//
//  Entry point.
//

int main(int argc, char* argv[])
{
    cout << endl << "Begin INAP CS1 receive example..." << endl;

#if defined(WIN32)
    SetConsoleCtrlHandler(breakHandler, TRUE);
#else
    signal(SIGINT, exitHandler);
#endif // defined(WIN32)

    try
    {
        ////////////////////////////////////////////////////////////////////////
        //
        //  Set application name.
        //

        ITS_Application::SetName("test_receive");


#if defined(USE_INTELLINET_STACK)

        ////////////////////////////////////////////////////////////////////////
        //
        //  Using IntelliSS7 stack (add that feature).
        //

        int res = ITS_AddFeature(itsINTELLISS7_Class);

        if (res != ITS_SUCCESS)
        {
            throw ITS_Error(res, __FILE__, __LINE__); // Fatal error.
        }

#endif // defined(USE_INTELLINET_STACK)


        ////////////////////////////////////////////////////////////////////////
        //        
        //  IntelliSS7 subsystems initialization (including licensing).
        //

        res = ITS_GlobalStart(ITS_TCAP | ITS_SCCP);

        if (res != ITS_SUCCESS)
        {
            throw ITS_Error(res, __FILE__, __LINE__); // Fatal error.
        }

#if defined(USE_INTELLINET_STACK)

        ////////////////////////////////////////////////////////////////////////
        //        
        //  o   Create border transport thread object.
        //  
        //  o   Start border transport thread.
        //
        //  o   Wait for border transport thread (synchronization point).
        //

        BorderTransportThread* borderTransportThread = new BorderTransportThread();

        borderTransportThread->Enter((void *)borderTransportThread);

        borderTransportSemaphore.Wait();  

#endif // defined(USE_INTELLINET_STACK)

        ////////////////////////////////////////////////////////////////////////
        //
        //  Create transport.
        //

        ITS_HANDLE handle = ITS_Initialize(
                                    ITS_TCAP |
                                    ITS_TRANSPORT_SINGLE_USER |
                                    ITS_TRANSPORT_TQUEUE,
                                    1);

        if (handle == NULL)
        {
            // Fatal error.

            throw ITS_Error(ITS_ENOTRANSPORT, __FILE__, __LINE__);
        }


        ////////////////////////////////////////////////////////////////////////
        //
        //  Receive (infinite) loop:
        //
        //  o   Receive TCAP begin dialogue.
        //
        //  o   Receive TCAP invoke component.
        //
        //  o   Call function to interpret INAP Connect operation argument.
        //
        //  o   Send back TCAP end dialogue if last component.
        //
        //  o   Exit loop.
        //

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

                    // Selection according to INAP operation.

                    switch (operation)
                    {
                    case OP_connect:
                    {
                        vector<byte> encodedConnectArg;

                        // The parameter field of the TCAP invoke component
                        // contains the INAP Connect operation argument.

                        recvInvokeCpt->GetParameter(encodedConnectArg);

                    ////////////////////////////////////////////////////////////
                    //
                    //  Function call uses INAP ASN.1 C++ API.
                    //

                        InterpretOperationConnectArg(encodedConnectArg);

                    //
                    ////////////////////////////////////////////////////////////

                        break;
                    }

                    default:
                    {
                        // Should be processed by complete code (all other INAP
                        // operation codes).

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

#if defined(USE_INTELLINET_STACK)

        ////////////////////////////////////////////////////////////////////////
        //        
        //  o   Stop border transport thread.
        //
        //  o   Delete border transport thread object.
        //

        borderTransportThread->StopRequested();

        delete borderTransportThread;

#endif // defined(USE_INTELLINET_STACK)
   
        ////////////////////////////////////////////////////////////////////////
        //
        //  IntelliSS7 termination.
        //

        ITS_Terminate(handle);

        ITS_GlobalStop();


#if defined(USE_INTELLINET_STACK)

        ////////////////////////////////////////////////////////////////////////
        //
        //  Using IntelliSS7 stack (remove feature).
        //

#endif // defined(USE_INTELLINET_STACK)


    }
    catch (ITS_GenericException& exp)
    {
        cout << endl << exp.GetDescription() << endl;

        ITS_GlobalStop();

        exit(EXIT_FAILURE);
    }

    cout << endl << "End of INAP CS1 receive example." << endl;
    

    // To stop here in console application.

    cout << endl << "Press Enter to quit...";

    char c = '\0';
    cin.get(c);

    return EXIT_SUCCESS;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
//  Following code is identical to test_codec example.
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
//  How to interpret an (encoded) INAP Connect operation argument (ConnectArg):
//
//  o   Decode ConnectArg encoded value (i.e. create ConnectArg object from
//      ConnectArg encoded value).
//
//  o   Retrieve Data from ConnectArg object.
//

void
InterpretOperationConnectArg(const vector<byte>& encodedConnectArg)
{
    //  [1] Create an Octets object from the ConnectArg ASN.1 encoded value.

    Octets* octets = new Octets(encodedConnectArg);

    ////////////////////////////////////////////////////////////////////////////

    //  [2] Create ConnectArg object (used by the decode phase).

    ConnectArg* connectArg = new ConnectArg();

    ////////////////////////////////////////////////////////////////////////////

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

    ////////////////////////////////////////////////////////////////////////////

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

    ////////////////////////////////////////////////////////////////////////////

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

    ////////////////////////////////////////////////////////////////////////////

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

    ////////////////////////////////////////////////////////////////////////////

    //  [7] Retrieve optional parameter "forwardingCondition".

    if (connectArg->OptionForwardingCondition())
    {
        //  [7-1] Retrieve reference to ForwardingCondition object.

        const ForwardingCondition& 
            forwardingCondition =
                connectArg->GetForwardingCondition();

        //  [7-2] Retrieve contents of ForwardingCondition object.

        if (forwardingCondition.IsBusy())
        {
            // Do something...
        }
        else if (forwardingCondition.IsNoanswer())
        {
            // Do something...
        }
        else if (forwardingCondition.IsAny())
        {
            // Do something...
        }
        else
        {
            // Not reached (an AsnDecodeError has been thrown previously).
        }

        //  [7-3] Print ForwardingCondition object.

        cout << endl;
        cout << "Printing ForwardingCondition object..." << endl;
        cout << forwardingCondition;
        cout << endl;
    }

    ////////////////////////////////////////////////////////////////////////////

    //  [8] Retrieve optional parameter "routeList".

    if (connectArg->OptionRouteList())
    {
        //  [8-1] Retrieve reference to RouteList object.

        const RouteList& 
            routeList =
                connectArg->GetRouteList();

        //  INAP API Note: a RouteList object contains a list of 
        //  RouteList::OCTETSTRING objects.

        //  [8-2] Retrieve contents of RouteList object.

        for (int i = 0; i < routeList.Size(); i++)
        {
            //  [8-2-1] Retrieve reference to RouteList::OCTETSTRING object.

            const RouteList::OCTETSTRING&
                routeListOCTETSTRING =
                    routeList.ElementAt(i);

            //  [8-2-2] Retrieve contents of RouteList::OCTETSTRING object.

            vector<byte> vector4 = routeListOCTETSTRING.GetArray();

            //  Do something with vector of bytes...

            //  [8-2-3] Print RouteList::OCTETSTRING object.

            cout << endl;
            cout << "Printing RouteList::OCTETSTRING object..." << endl;
            cout << routeListOCTETSTRING;
            cout << endl;
        }

        //  [8-3] Print RouteList object.

        cout << endl;
        cout << "Printing RouteList object..." << endl;
        cout << routeList;
        cout << endl;
    }

    ////////////////////////////////////////////////////////////////////////////

    //  [9] Retrieve optional parameter "callingPartyNumber".

    if (connectArg->OptionCallingPartyNumber())
    {
        //  [9-1] Retrieve reference to CallingPartyNumber object.

        const CallingPartyNumber&
            callingPartyNumber = 
                connectArg->GetCallingPartyNumber();

        //  [9-2] Retrieve contents of CallingPartyNumber object.

        vector<byte> vector5 = callingPartyNumber.GetArray();

        // Do something with vector of bytes...

        //  [9-3] Print CallingPartyNumber object.

        cout << endl;
        cout << "Printing CallingPartyNumber object..." << endl;
        cout << callingPartyNumber;
        cout << endl;
    }

    ////////////////////////////////////////////////////////////////////////////

    //  [10] Free all memory allocated on the heap.

    //  [10-1] Delete Octets object.

    delete octets;

    //  [10-2] Delete ConnectArg object.

    delete connectArg;
}