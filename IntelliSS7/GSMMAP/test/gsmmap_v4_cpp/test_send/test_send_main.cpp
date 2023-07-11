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
//  ID: $Id: test_send_main.cpp,v 9.1 2005/03/23 12:51:36 cvsadmin Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//  MAP V4 send example.
//
//  This example shows how to send the argument of an MAP InsertSubscriberData
//  operation. The part used to build (create, insert data and encode) the 
//  InsertSubscriberData operation argument is identical the test_codec example.
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
#include <its_ss7_stubs.h>
#include <its_object.h>

extern "C" ITS_Class itsINTELLISS7_Class;
#endif // defined(USE_INTELLINET_STACK)

#include <itu/sccp.h>
#include <itu/tcap.h>
#include <tcap++.h>

#include <Asn.h>
#include <AsnException.h>

#include <map_cpp.h>
#include <map_v4_insert_subscriber_data_arg.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace map_common;
using namespace map_v4;
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

vector<byte> BuildOperationInsertSubscriberDataArg();


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

    ITS_HANDLE handle = ITS_Initialize(
                                ITS_TCAP                    |
                                ITS_TRANSPORT_FIFO          |
                                ITS_TRANSPORT_SINGLE_USER,
                                2);

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
    cout << endl << "Begin MAP V4 send example..." << endl;


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
        //  Execute MAP operation InsertSubscriberData:
        //  
        //  o   Allocate new dialogue ID.
        //
        //  o   Build TCAP begin dialogue.
        //
        //  o   Build TCAP invoke component.
        //
        //  o   Call function to build MAP InsertSubscriberData operation 
        //      argument.
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

        // "OP_insertSubscriberData" is defined in file inap_cpp.h.

        invokeCpt.SetOperation(OP_insertSubscriberData); 

        // Class 2 (only errors appear in the MAP Insert Subscriber Data 
        // operation macro, see MAP recommendation Q.XXXX).

        invokeCpt.SetClass(2);

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Function call uses MAP ASN.1 C++ API.
    //

        vector<byte> encodedInsertSubscriberDataArg = 
                BuildOperationInsertSubscriberDataArg();

    //
    ////////////////////////////////////////////////////////////////////////////


        // The parameter field of the TCAP invoke component contains the MAP
        // InsertSubscriberData operation argument.

        invokeCpt.SetParameter(encodedInsertSubscriberDataArg);


        cout << endl;
        cout << "Ready to execute MAP InsertSubscriberData operation...";
        cout << endl;
      
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

    cout << endl << "End of MAP V4 send example." << endl;
    
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

//
//  Macro to convert fixed arrays (of booleans) to vectors.
//
#define FixedBooleanArrayToVector(array)   \
    (vector<bool>(array, array + FixedArraySize(array)))


////////////////////////////////////////////////////////////////////////////////
//
//  How to Build a MAP InsertSubscriberData operation argument 
//  (InsertSubscriberDataArg):
//
//  o   Create InsertSubscriberDataArg object.
//
//  o   Insert data step by step in the created InsertSubscriberDataArg object 
//      (i.e. populate various parameters of the InsertSubscriberData 
//      operation argument).
//  
//  o   Encode the InsertSubscriberDataArg object to produce an 
//      InsertSubscriberDataArg encoded value.
//

vector<byte> 
BuildOperationInsertSubscriberDataArg()
{
    //  [1] Create InsertSubscriberDataArg object.

    InsertSubscriberDataArg* insertSubscriberDataArg = 
		                           new InsertSubscriberDataArg();

    ////////////////////////////////////////////////////////////////////////////

    //  Memory management note: all the following parameter objects that are
    //  used to populate the InsertSubscriberDataArg object must be created in 
	//  the heap (i.e. using operator new) and not in the stack. They are 
	//  automatically deleted when the insertSubscriberDataArg object is 
    //  deleted. Only the InsertSubscriberDataArg object itself can be created 
    //  in the stack. 

    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////

    //  [2] Populate optional parameter "imsi".

    //  [2-1] Create IMSI object.

    byte fixedArray1[] = { 0x01U, 0x02U, 0x03U, 0x04U }; 

    IMSI* imsi = new IMSI(FixedByteArrayToVector(fixedArray1));

    //  [2-2] Set IMSI object in InsertSubscriberDataArg object.

    insertSubscriberDataArg->SetImsi(imsi);


    ////////////////////////////////////////////////////////////////////////////

    //  [3] Populate optional parameter "msisdn".

    //  [3-1] Create an ISDN_AddressString object.

    byte fixedArray2[] = { 0x11U, 0x22U, 0x33U, 0x44U, 0x55U };

    ISDN_AddressString* iSDN_AddressString = 
        new ISDN_AddressString(FixedByteArrayToVector(fixedArray2));

    //  [3-2] Set ISDN_AddressString object in InsertSubscriberDataArg object.

    insertSubscriberDataArg->SetMsisdn(iSDN_AddressString);


    ////////////////////////////////////////////////////////////////////////////

    //  [4] Populate optional parameter "category".

    //  [4-1] Create Category object.

    byte fixedArray3[] = { 0x66U };

    Category* category = 
        new Category(FixedByteArrayToVector(fixedArray3));

    //  [4-2] Set Category object in InsertSubscriberDataArg object.

    insertSubscriberDataArg->SetCategory(category);


    ////////////////////////////////////////////////////////////////////////////

    //  [5] Populate optional parameter "subscriberStatus".

    //  [5-1] Create SubscriberStatus object.

    SubscriberStatus* subscriberStatus = new SubscriberStatus();

    subscriberStatus->SetServiceGranted();

    //  [5-2] Set SubscriberStatus object in InsertSubscriberDataArg object.

    insertSubscriberDataArg->SetSubscriberStatus(subscriberStatus);


    ////////////////////////////////////////////////////////////////////////////

    //  [6] Populate optional parameter "bearerServiceList".

    //  [6-1] Create BearerServiceList object.

    BearerServiceList* bearerServiceList = new BearerServiceList();

    //  MAP API Note: a BearerServiceList object contains a list of 
    //  Ext_BearerServiceCode objects.

    //  [6-1-1] Create Ext_BearerServiceCode object.

    byte fixedArray4[] = { 0xAAU };

    Ext_BearerServiceCode* ext_bearerServiceCode1 = 
        new Ext_BearerServiceCode(FixedByteArrayToVector(fixedArray4));

    //  [6-1-2] Create Ext_BearerServiceCode object.

    byte fixedArray5[] = { 0xBBU };

    Ext_BearerServiceCode* ext_bearerServiceCode2 = 
        new Ext_BearerServiceCode(FixedByteArrayToVector(fixedArray5));

    //  [6-1-3] Add Ext_BearerServiceCode object to BearerServiceList object.

    bearerServiceList->AddElement(ext_bearerServiceCode1);
    
	//  [6-1-4] Add Ext_BearerServiceCode object to BearerServiceList object.

    bearerServiceList->AddElement(ext_bearerServiceCode2);

    //  [6-2] Set BearerServiceList object in InsertSubscriberDataArg object.

    insertSubscriberDataArg->SetBearerServiceList(bearerServiceList);


    ////////////////////////////////////////////////////////////////////////////

    //  [7] Populate optional parameter "teleserviceList".

    //  [7-1] Create TeleServiceList object.

    TeleserviceList* teleserviceList = new TeleserviceList();

    //  MAP API Note: a TeleServiceList object contains a list of 
    //  Ext_TeleServiceCode objects.

    //  [7-1-1] Create Ext_TeleServiceCode object.

    byte fixedArray6[] = { 0xCCU };

    Ext_TeleserviceCode* ext_teleserviceCode1 = 
        new Ext_TeleserviceCode(FixedByteArrayToVector(fixedArray6));

    //  [7-1-2] Create Ext_TeleServiceCode object.
    
    byte fixedArray7[] = { 0xDDU };

    Ext_TeleserviceCode* ext_teleserviceCode2 = 
        new Ext_TeleserviceCode(FixedByteArrayToVector(fixedArray7));
	
	//  [7-1-3] Create Ext_TeleServiceCode object.

    byte fixedArray8[] = { 0xEEU };

    Ext_TeleserviceCode* ext_teleserviceCode3 = 
        new Ext_TeleserviceCode(FixedByteArrayToVector(fixedArray8));
	
	//  [7-1-4] Add Ext_TeleServiceCode object to TeleServiceList object.
	
    teleserviceList->AddElement(ext_teleserviceCode1);

	//  [7-1-5] Add Ext_TeleServiceCode object to TeleServiceList object.
	
    teleserviceList->AddElement(ext_teleserviceCode2);

	//  [7-1-6] Add Ext_TeleServiceCode object to TeleServiceList object.

    teleserviceList->AddElement(ext_teleserviceCode3);

    //  [7-2] Set TeleServiceList object in InsertSubscriberDataArg object.

    insertSubscriberDataArg->SetTeleserviceList(teleserviceList);


    ////////////////////////////////////////////////////////////////////////////

    //  [8] Populate optional parameter "provisionedSS".

    //  [8-1] Create Ext_SS_InfoList object.

    Ext_SS_InfoList* ext_SS_InfoList = new Ext_SS_InfoList();

    //  MAP API Note: an Ext_SS_InfoList object contains a list of 
    //  Ext_SS_Info objects.

    //  [8-1-1] Create Ext_SS_Info object.
    
	Ext_SS_Info* ext_SS_Info1 = new Ext_SS_Info();
    
	//  MAP API Note: an Ext-SS-Info object contains a choice of
	//  Ext-ForwInfo, Ext-CallBarInfo, CUG-Info, Ext-SS-Data or EMLPP-Info.

    //  Choice is forwardingInfo (type Ext_ForwInfo).

    //  [8-1-1-1] Create Ext_ForwInfo object.

    Ext_ForwInfo* ext_forwInfo = new Ext_ForwInfo();

    //  [8-1-1-1-1] Create SS_Code object.

    byte fixedArray9[] = { 0x33U };

    SS_Code* sS_Code1 = new SS_Code(FixedByteArrayToVector(fixedArray9));

    //  [8-1-1-1-2] Set SS_Code object in Ext_ForwInfo object.

    ext_forwInfo->SetSs_Code(sS_Code1);

    //  [8-1-1-1-3] Create Ext_ForwFeatureList object.

    Ext_ForwFeatureList* ext_forwFeatureList = 
        new Ext_ForwFeatureList();

	//  MAP API Note: an Ext-SS-Ext_ForwFeatureList object contains a list
	//  of Ext_ForwFeature objects.

    //  [8-1-1-1-3-1] Create Ext_ForwFeature object.

    Ext_ForwFeature* ext_forwFeature = new Ext_ForwFeature();
    
	//  [8-1-1-1-3-1-1] Create Ext_SS_Status object.
    
	byte fixedArray10[] = { 0x22U, 0x22U, 0x22U };

    Ext_SS_Status* ext_SS_Status1 = 
        new Ext_SS_Status(FixedByteArrayToVector(fixedArray10));

    //  [8-1-1-1-3-1-2] Create Ext_BasicServiceCode object.
    
	Ext_BasicServiceCode* ext_basicServiceCode = new Ext_BasicServiceCode();

    byte fixedArray11[] = { 0x44U };

    Ext_BearerServiceCode* ext_bearerServiceCode = 
        new Ext_BearerServiceCode(FixedByteArrayToVector(fixedArray11));

    ext_basicServiceCode->SetChoiceExt_BearerService(ext_bearerServiceCode);

    //  [8-1-1-1-3-1-3] Create ISDN_SubaddressString object.
    
	byte fixedArray12[] = 
        { 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U };

    ISDN_SubaddressString* iSDN_SubaddressString = 
        new ISDN_SubaddressString(FixedByteArrayToVector(fixedArray12));
    
	//  [8-1-1-1-3-1-4] Set Ext_SS_Status object in Ext_ForwFeature 
    //  object.
    
	ext_forwFeature->SetSs_Status(ext_SS_Status1);
    
	//  [8-1-1-1-3-1-5] Set Ext_BearerServiceCode object in 
    //  Ext_ForwFeature object.
    
	ext_forwFeature->SetBasicService(ext_basicServiceCode);
    
	//  [8-1-1-1-3-1-6] Set ISDN_SubaddressString object in 
    //  Ext_ForwFeature object.
    
	ext_forwFeature->SetForwardedToSubaddress(iSDN_SubaddressString);


    //  [8-1-1-1-3-2] Add Ext_ForwFeature object to Ext_ForwFeatureList 
    //  object.

    ext_forwFeatureList->AddElement(ext_forwFeature);

    //  [8-1-1-1-4] Set ForwardingFeatureList object in Ext_ForwInfo 
    //  object.

    ext_forwInfo->SetForwardingFeatureList(ext_forwFeatureList);

    //  [8-1-1-2] Set choice ForwardingInfo of Ext_SS_Info object.

    ext_SS_Info1->SetChoiceForwardingInfo(ext_forwInfo);
    
	//  [8-1-2] Create Ext_SS_Info object.
    
	Ext_SS_Info* ext_SS_Info2 = new Ext_SS_Info();

	//  MAP API Note: an Ext-SS-Info object contains a choice of
	//  Ext-ForwInfo, Ext-CallBarInfo, CUG-Info, Ext-SS-Data or EMLPP-Info.

    //  Choice is cug-Info.

    //  [8-1-2-1] Create CUG_Info object.

    CUG_Info* cUG_Info = new CUG_Info();

    //  [8-1-2-1-1] Create CUG_SubscriptionList object.

    CUG_SubscriptionList* cUG_SubscriptionList = new CUG_SubscriptionList();

	//  MAP API Note: an CUG_SubscriptionList object contains a list of 
    //  CUG_Subscription objects.

    //  [8-1-2-1-1-1] Create CUG_Subscription object.
    
	CUG_Subscription* cUG_Subscription1 = new CUG_Subscription();

    CUG_Index* cUG_Index1 = new CUG_Index(1999l);

    cUG_Subscription1->SetCug_Index(cUG_Index1);

    byte fixedArray13[] = { 0x11U, 0x22U, 0x33U, 0x44U };

    CUG_Interlock* cUG_Interlock1 = 
        new CUG_Interlock(FixedByteArrayToVector(fixedArray13));

    cUG_Subscription1->SetCug_Interlock(cUG_Interlock1);

    IntraCUG_Options* intraCUG_Options1 = new IntraCUG_Options();

    intraCUG_Options1->SetNoCUG_Restrictions();

    cUG_Subscription1->SetIntraCUG_Options(intraCUG_Options1);

    //  [8-1-2-1-1-2] Create CUG_Subscription object.
    
	CUG_Subscription* cUG_Subscription2 = new CUG_Subscription();

    CUG_Index* cUG_Index2 = new CUG_Index(2001l);

    cUG_Subscription2->SetCug_Index(cUG_Index2);

    byte fixedArray14[] = { 0x44U, 0x33U, 0x22U, 0x11U };

    CUG_Interlock* cUG_Interlock2 = 
        new CUG_Interlock(FixedByteArrayToVector(fixedArray14));

    cUG_Subscription2->SetCug_Interlock(cUG_Interlock2);

    IntraCUG_Options* intraCUG_Options2 = new IntraCUG_Options();

    intraCUG_Options2->SetNoCUG_Restrictions();

    cUG_Subscription2->SetIntraCUG_Options(intraCUG_Options2);

    //  [8-1-2-1-1-3] Add CUG_Subscription object to 
    //  CUG_SubscriptionList object.
    
	cUG_SubscriptionList->AddElement(cUG_Subscription1);
    
	//  [8-1-2-1-1-4] Add CUG_Subscription object to 
    //  CUG_SubscriptionList object.

    cUG_SubscriptionList->AddElement(cUG_Subscription2);


    //  [8-1-2-1-2] Set CUG_SubscriptionList object in object CUG_Info.

    cUG_Info->SetCug_SubscriptionList(cUG_SubscriptionList);

    //  [8-1-2-2] Set choice CUG_Info in object Ext_SS_Info.

    ext_SS_Info2->SetChoiceCug_Info(cUG_Info);

    //  [8-1-3] Create Ext_SS_Info object.
    
	Ext_SS_Info* ext_SS_Info3 = new Ext_SS_Info();

	//  MAP API Note: an Ext-SS-Info object contains a choice of
	//  Ext-ForwInfo, Ext-CallBarInfo, CUG-Info, Ext-SS-Data or EMLPP-Info.

    //  Choice is ss-Data.

    //  [8-1-3-1] Create Ext_SS_Data object.

    Ext_SS_Data* ext_SS_Data = new Ext_SS_Data();

    //  [8-1-3-1-1] Create SS_Code object.
    
	byte fixedArray15[] = { 0x11U };

    SS_Code* sS_Code2 = new SS_Code(FixedByteArrayToVector(fixedArray15));
    
	//  [8-1-3-1-2] Create SS_Status object.
    
	byte fixedArray16[] = { 0x22U, 0x22U };

    Ext_SS_Status* ext_SS_Status2 = 
        new Ext_SS_Status(FixedByteArrayToVector(fixedArray16));

    //  [8-1-3-1-3] Create SS_SubscriptionOption object.
    
	SS_SubscriptionOption* sS_SubscriptionOption = new SS_SubscriptionOption();

    CliRestrictionOption* cliRestrictionOption = new CliRestrictionOption();

    cliRestrictionOption->SetTemporaryDefaultRestricted();

    sS_SubscriptionOption->SetChoiceCliRestrictionOption(cliRestrictionOption);

	//  [8-1-3-1-4] Set SS_Code object in Ext_SS_Data object.

    ext_SS_Data->SetSs_Code(sS_Code2);
	
	//  [8-1-3-1-5] Set SS_Status object in Ext_SS_Data object.
    
	ext_SS_Data->SetSs_Status(ext_SS_Status2);
	
	//  [8-1-3-1-6] Set SS_SubscriptionOption object in Ext_SS_Data 
    //  object.
    
	ext_SS_Data->SetSs_SubscriptionOption(sS_SubscriptionOption);

    
	//  [8-1-3-2] Set choice Ext_SS_Data in Ext_SS_Info object.

    ext_SS_Info3->SetChoiceSs_Data(ext_SS_Data);

	//  [8-1-4] Add Ext_SS_Info object to Ext_SS_InfoList object.
    
	ext_SS_InfoList->AddElement(ext_SS_Info1);
	
	//  [8-1-5] Add Ext_SS_Info object to Ext_SS_InfoList object.
    
	ext_SS_InfoList->AddElement(ext_SS_Info2);
	
	//  [8-1-6] Add Ext_SS_Info object to Ext_SS_InfoList object.
    
	ext_SS_InfoList->AddElement(ext_SS_Info3);
    
	//  [8-2] Set Ext_SS_InfoList object in InsertSubscriberDataArg object.
    
	insertSubscriberDataArg->SetProvisionedSS(ext_SS_InfoList);

    ////////////////////////////////////////////////////////////////////////////

    //  [9] Populate optional parameter "odb_data".

    //  [9-1] Create an ODB_Data object.
    
	ODB_Data* oDB_Data = new ODB_Data();
    
	//  [9-1-1] Create an ODB_GeneralData object.
    
	bool fixedArray17[] = { true, false, true, false, true,
                            false, true, false, true, false,
                            true, false, true, false, true,
                            false, true, false, true, false,
                            true, false, true, false, true };

    ODB_GeneralData* oDB_GeneralData = 
        new ODB_GeneralData(FixedBooleanArrayToVector(fixedArray17));

    //  [9-1-2] Create an ODB_HPLMN_Data object.
    
	bool fixedArray18[] = { false, true, false, true };

    ODB_HPLMN_Data* oDB_HPLMN_Data = 
        new ODB_HPLMN_Data(FixedBooleanArrayToVector(fixedArray18));

    //  [9-1-3] Set ODB_GeneralData object in ODB_Data object.
    
	oDB_Data->SetOdb_GeneralData(oDB_GeneralData);
    
	//  [9-1-4] Set ODB_HPLMN_Data object in ODB_Data object.

    oDB_Data->SetOdb_HPLMN_Data(oDB_HPLMN_Data);	

    //  [9-2] Set ODB_Data object in InsertSubscriberDataArg object.

    insertSubscriberDataArg->SetOdb_Data(oDB_Data);


    ////////////////////////////////////////////////////////////////////////////

    //  [10] Encode InsertSubscriberDataArg object.

    Octets* octets = NULL;

    try
    {
        //  Can throw and AsnEncodeError execption. 

        octets = insertSubscriberDataArg->Encode();
    }
    catch (AsnEncodeError& encodeError)
    {
        cout << endl << encodeError.GetDescription() << endl;

        //  More specific error processing should be added here.

        //  By default re-throw exception.

        throw encodeError;
    }

    cout << endl;
    cout << "Printing InsertSubscriberDataArg ASN.1 encoded value..." << endl;
    cout << *octets;
    cout << endl;

    ////////////////////////////////////////////////////////////////////////////

    //  [11] Retrieve InsertSubscriberDataArg ASN.1 encoded value from octets 
    //  object.

    vector<byte> encodedInsertSubscriberDataArg = octets->GetArray();

    ////////////////////////////////////////////////////////////////////////////

    //  [12] Free all memory allocated on the heap.

    //  [12-1] Delete InsertSubscriberDataArg object (and therefore all the 
    //  parameter objects that have been previously set).

    delete insertSubscriberDataArg;

    //  [12-2] Delete Octets object created by the call to Encode.

    delete octets;

    ////////////////////////////////////////////////////////////////////////////

    //  [13] Return (by value) InsertSubscriberDataArg ASN.1 encoded value.

    return encodedInsertSubscriberDataArg;
}


