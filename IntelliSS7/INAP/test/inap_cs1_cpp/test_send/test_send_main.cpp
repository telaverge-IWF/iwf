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
//  ID: $Id: test_send_main.cpp,v 9.1 2005/03/23 12:51:46 cvsadmin Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//  INAP CS1 send example.
//
//  This example shows how to send the argument of an INAP Connect operation.
//  The part used to build (create, insert data and encode) the Connect 
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

vector<byte> BuildOperationConnectArg();


////////////////////////////////////////////////////////////////////////////////
//
//  Definitions for SCCP addresses.
//

#define SCCP_ADDR_INDICATOR (SCCP_CPA_ROUTE_NAT |   \
                             SCCP_CPA_ROUTE_SSN |   \
                             SCCP_CPA_HAS_PC    |   \
                             SCCP_CPA_HAS_SSN)


#define LOCAL_PC    0
#define LOCAL_SSN   3

#define REMOTE_PC   0
#define REMOTE_SSN  4


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
                                    ITS_TRANSPORT_CSOCKET       |
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
    cout << endl << "Begin INAP CS1 send example..." << endl;


    ////////////////////////////////////////////////////////////////////////////
    //
    //  Set break handler (specific for WIN32 and Unix).
    //

#if defined(WIN32)
    SetConsoleCtrlHandler(breakHandler, TRUE);
#else // !defined(WIN32)
    signal(SIGINT, exitHandler);
#endif // defined(WIN32)

    try
    {
        ////////////////////////////////////////////////////////////////////////
        //
        //  Set application name.
        //

        ITS_Application::SetName("test_send");


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
        //  Execute INAP operation Connect:
        //  
        //  o   Allocate new dialogue ID.
        //
        //  o   Build TCAP begin dialogue.
        //
        //  o   Build TCAP invoke component.
        //
        //  o   Call function to build INAP Connect operation argument.
        //
        //  o   Send TCAP invoke component.
        //  
        //  o   Send TCAP begin dialogue.
        //


        ITS_USHORT dialogueID = 0;

        TCAP_AllocateDialogueId(&dialogueID);


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

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Function call uses INAP ASN.1 C++ API.
    //

        vector<byte> encodedConnectArg = BuildOperationConnectArg();

    //
    ////////////////////////////////////////////////////////////////////////////


        // The parameter field of the TCAP invoke component contains the INAP
        // Connect operation argument.

        invokeCpt.SetParameter(encodedConnectArg);


        cout << endl << "Ready to execute INAP Connect operation..." << endl;
      
        TCAP_Component::Send(handle, &beginDlg, &invokeCpt);

        TCAP_Dialogue::Send(handle, &beginDlg);

        ////////////////////////////////////////////////////////////////////////
        //
        //  Receive loop:
        //  
        //  o   Receive TCAP end dialogue (sent by test_receive example).
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

        ITS_RemFeature(itsINTELLISS7_Class);

#endif // defined(USE_INTELLINET_STACK)


    }
    catch (ITS_GenericException& exp)
    {
        cout << endl << exp.GetDescription() << endl;

        ITS_GlobalStop();

        exit(EXIT_FAILURE);
    }

    cout << endl << "End of INAP CS1 send example." << endl;
    
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



////////////////////////////////////////////////////////////////////////////////
//
//  How to Build an INAP Connect operation argument (ConnectArg):
//
//  o   Create a ConnectArg object.
//
//  o   Insert data step by step in the created ConnectArg object (i.e. populate
//      various parameters of the Connect operation argument).
//  
//  o   Encode the ConnectArg object to produce a ConnectArg encoded value.
//

vector<byte> 
BuildOperationConnectArg()
{
    //  [1] Create ConnectArg object.

    ConnectArg* connectArg = new ConnectArg();

    ////////////////////////////////////////////////////////////////////////////

    //  Memory management note: all the following parameter objects that are
    //  used to populate the ConnectArg object must be created in the heap (i.e.
    //  using operator new) and not in the stack. They are automatically deleted
    //  when the connectArg object is deleted. Only the ConnectArg object itself
    //  can be created in the stack. 

    ////////////////////////////////////////////////////////////////////////////

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

    ////////////////////////////////////////////////////////////////////////////

    //  [3] Populate optional parameter "alertingPattern".

    //  [3-1] Create an AlertingPattern object.

    byte fixedArray2[] = { 0x20, 0x21, 0x22 };

    AlertingPattern* 
        alertingPattern =
            new AlertingPattern(FixedByteArrayToVector(fixedArray2));

    //  [3-2] Set AlertingPattern object in ConnectArg object.

    connectArg->SetAlertingPattern(alertingPattern);

    ////////////////////////////////////////////////////////////////////////////

    //  [4] Populate optional parameter "correlationID".

    //  [4-1] Create CorrelationID object.

    byte fixedArray3[] = { 0x30, 0x31, 0x32, 0x33, 0x34 };

    CorrelationID*
        correlationID =
            new CorrelationID(FixedByteArrayToVector(fixedArray3));

    //  [4-2] Set CorrelationID object in ConnectArg object.

    connectArg->SetCorrelationID(correlationID);

    ////////////////////////////////////////////////////////////////////////////

    //  [5] Populate optional parameter "forwardingCondition".

    //  [5-1] Create ForwardingCondition object.

    ForwardingCondition*
        forwardingCondition =
            new ForwardingCondition();

    forwardingCondition->SetAny();

    //  [5-2] Set ForwardingCondition object in ConnectArg object.

    connectArg->SetForwardingCondition(forwardingCondition);

    ////////////////////////////////////////////////////////////////////////////

    //  [6] Populate optional parameter "routeList".

    //  [6-1] Create RouteList object.

    RouteList* routeList = new RouteList();

    //  INAP API Note: a RouteList object contains a list of 
    //  RouteList::OCTETSTRING objects.

    //  [6-1-1] Create RouteList::OCTETSTRING object.

    byte fixedArray4[] = { 0x01, 0x02, 0x03 };

    RouteList::OCTETSTRING*
        routeListOCTETSTRING1 =
            new RouteList::OCTETSTRING(
                FixedByteArrayToVector(fixedArray4));

    //  [6-1-2] Create RouteList::OCTETSTRING object.

    byte fixedArray5[] = { 0x11, 0x22, 0x33, 0x44 };

    RouteList::OCTETSTRING*
        routeListOCTETSTRING2 =
            new RouteList::OCTETSTRING(
                FixedByteArrayToVector(fixedArray5));

    //  [6-1-3] Create RouteList::OCTETSTRING object.

    byte fixedArray6[] = { 0x10, 0x20, 0x30, 0x40, 0x50 };

    RouteList::OCTETSTRING*
        routeListOCTETSTRING3 =
            new RouteList::OCTETSTRING(
                FixedByteArrayToVector(fixedArray6));

    //  [6-1-4] Add RouteList::OCTETSTRING object to RouteList object.

    routeList->AddElement(routeListOCTETSTRING1);

    //  [6-1-5] Add RouteList::OCTETSTRING object to RouteList object.

    routeList->AddElement(routeListOCTETSTRING2);

    //  [6-1-6] Add RouteList::OCTETSTRING object to RouteList object.

    routeList->AddElement(routeListOCTETSTRING3);

    //  [6-2] Set RouteList object in ConnectArg object.

    connectArg->SetRouteList(routeList);

    ////////////////////////////////////////////////////////////////////////////

    //  [7] Populate optional parameter "callingPartyNumber".

    //  [7-1] Create CallingPartyNumber object.

    byte fixedArray7[] = { 0x07, 0x07, 0x08, 0x09, 0x09, 0x08, 0x04 };

    CallingPartyNumber*
        callingPartyNumber =
            new CallingPartyNumber(FixedByteArrayToVector(fixedArray7));

    //  [7-2] Set CallingPartyNumber object in ConnectArg object.

    connectArg->SetCallingPartyNumber(callingPartyNumber);

    ////////////////////////////////////////////////////////////////////////////

    //  [8] Encode ConnectArg object.

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

    ////////////////////////////////////////////////////////////////////////////

    //  [9] Retrieve ConnectArg ASN.1 encoded value from octets object.

    vector<byte> encodedConnectArg = octets->GetArray();

    ////////////////////////////////////////////////////////////////////////////

    //  [10] Free all memory allocated on the heap.

    //  [10-1] Delete ConnectArg object (and therefore all the parameter
    //  objects that have been previously set).

    delete connectArg;

    //  [10-2] Delete Octets object created by the call to Encode.

    delete octets;

    ////////////////////////////////////////////////////////////////////////////

    //  [11] Return (by value) ConnectArg ASN.1 encoded value.

    return encodedConnectArg;
}

