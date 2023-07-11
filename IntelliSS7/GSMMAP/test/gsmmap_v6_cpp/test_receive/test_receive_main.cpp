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
////////////////////////////////////////////////////////////////////////////////

//
//  MAP v6 receive example.
//
//  This example shows how to receive the argument of a MAP InsertSubscriberData 
//  operation. The part used to interpret (decode and retrieve data) for the
//  InsertSubscriberData operation argument is identical to the test_codec 
//  example.
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
#include <its_object.h>

extern "C" ITS_Class itsINTELLISS7_Class;
#endif // defined(USE_INTELLINET_STACK)

#include <itu/sccp.h>
#include <itu/tcap.h>
#include <tcap++.h>

#include <Asn.h>
#include <AsnException.h>

#include <map_cpp.h>
#include <map_v6_insert_subscriber_data_arg.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace map_common;
using namespace map_v6;
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

void InterpretOperationInsertSubscriberDataArg(
        const vector<byte>& encodedInsertSubscriberDataArg);


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
    :   ITS_Thread(0, (ITS_THREAD_FUNC)DispatchFunction),
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
    cout << endl << "Begin MAP v6 receive example..." << endl;

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
        //  o   Call function to interpret MAP InsertSubscriberData operation
        //      argument.
        //
        //  o   Send back a TCAP end dialogue if last component.
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

                    // Selection according to MAP operation.

                    switch (operation)
                    {
                    case OP_insertSubscriberData:
                    {
                        vector<byte> encodedInsertSubscriberDataArg;

                        // The parameter field of the TCAP invoke component
                        // contains the MAP InsertSubscriberData operation
                        // argument.

                        recvInvokeCpt->
                            GetParameter(encodedInsertSubscriberDataArg);

                    ////////////////////////////////////////////////////////////
                    //
                    //  Function call uses MAP ASN.1 C++ API.
                    //

                        InterpretOperationInsertSubscriberDataArg(
                            encodedInsertSubscriberDataArg);

                    //
                    ////////////////////////////////////////////////////////////

                        break;
                    }

                    default:
                    {
                        // Should be processed by complete code (all other MAP
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

    cout << endl << "End of MAP v6 receive example." << endl;
    

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
//  How to interpret an (encoded) MAP InsertSubscriberData operation 
//  argument (InsertSubscriberDataArg):
//
//  o   Decode a InsertSubscriberDataArg encoded value (i.e. create a 
//      InsertSubscriberDataArg object from a InsertSubscriberDataArg encoded 
//      value).
//
//  o   Retrieve Data from a InsertSubscriberDataArg object.
//

void
InterpretOperationInsertSubscriberDataArg(
                            const vector<byte>& encodedInsertSubscriberDataArg)
{
    //  [1] Create an Octets object from the InsertSubscriberDataArg ASN.1 
    //  encoded value.

    Octets* octets = new Octets(encodedInsertSubscriberDataArg);

    ////////////////////////////////////////////////////////////////////////////

    //  [2] Create a InsertSubscriberDataArg object (used by the decode phase).

    InsertSubscriberDataArg* 
        insertSubscriberDataArg = new 
            InsertSubscriberDataArg();

    ////////////////////////////////////////////////////////////////////////////

    //  [3] Decode the InsertSubscriberDataArg ASN.1 encoded value and therefore
    //  populate previously created InsertSubscriberDataArg object.

    try
    {
        //  Can throw and AsnDecodeError exception.

        insertSubscriberDataArg->Decode(*octets);
    }
    catch (AsnDecodeError& decodeError)
    {
        cout << endl << decodeError.GetDescription() << endl;

        // More specific error processing should be added here.

        // By default re-throw exeception.

        throw decodeError;
    }

    cout << endl;
    cout << "Printing decoded InsertSubscriberDataArg object..." << endl;
    cout << *insertSubscriberDataArg;
    cout << endl;

    ////////////////////////////////////////////////////////////////////////////

    //  [4] Retrieve optional parameter "imsi".

    if (insertSubscriberDataArg->OptionImsi())
    {
        //  [4-1] Retrieve reference to IMSI object.

        const IMSI& imsi = insertSubscriberDataArg->GetImsi();
        
		//  [4-2] Retrieve contents of IMSI object.
        
		vector<byte> vector1 = imsi.GetArray();

        //  Do something with vector of bytes...
        
		//  [4-3] Print IMSI object.
        
		cout << endl;
        cout << "Printing IMSI object..." << endl;
        cout << imsi;
        cout << endl;
    }

    ////////////////////////////////////////////////////////////////////////////

    //  [5] Retrieve optional parameter "msisdn".

    if (insertSubscriberDataArg->OptionMsisdn())
    {
        //  [5-1] Retrieve reference to  ISDN_AddressString object.

        const ISDN_AddressString& 
            iSDN_AddressString = 
                insertSubscriberDataArg->GetMsisdn();
        
		//  [5-2] Retrieve contents of ISDN_AddressString object.
        
		vector<byte> vector2 = iSDN_AddressString.GetArray();

        //  Do something with vector of bytes...
        
		//  [5-3] Print ISDN_AddressString object.
        
		cout << endl;
        cout << "Printing ISDN_AddressString object..." << endl;
        cout << iSDN_AddressString;
        cout << endl;
    }

    ////////////////////////////////////////////////////////////////////////////

    //  [6] Retrieve optional parameter "category".

    if (insertSubscriberDataArg->OptionCategory())
    {
        //  [6-1] Retrieve reference to  Category object.

        const Category& category = insertSubscriberDataArg->GetCategory();
        
		//  [6-2] Retrieve contents of Category object.
        
		vector<byte> vector3 = category.GetArray();

        //  Do something with vector of bytes...
        
		//  [6-3] Print Category object.
        
		cout << endl;
        cout << "Printing Category object..." << endl;
        cout << category;
        cout << endl;
    }

    ////////////////////////////////////////////////////////////////////////////

    //  [7] Retrieve optional parameter "subscriberStatus".

    if (insertSubscriberDataArg->OptionSubscriberStatus())
    {
        //  [7-1] Retrieve reference to  SubscriberStatus object.

        const SubscriberStatus& 
            subscriberStatus = 
                insertSubscriberDataArg->GetSubscriberStatus();
        
		//  [7-2] Retrieve contents of SubscriberStatus object.
        
        if (subscriberStatus.IsOperatorDeterminedBarring())
        {
            // Do something...
        }
        else if (subscriberStatus.IsServiceGranted())
        {
            // Do something...
        }
        
		//  [7-3] Print SubscriberStatus object.
        
		cout << endl;
        cout << "Printing SubscriberStatus object..." << endl;
        cout << subscriberStatus;
        cout << endl;
    }

    ////////////////////////////////////////////////////////////////////////////

    //  [8] Retrieve optional parameter "bearerServiceList".

    if (insertSubscriberDataArg->OptionBearerServiceList())
    {
        //  [8-1] Retrieve reference to  BearerServiceList object.

        const BearerServiceList& bearerServiceList =
            insertSubscriberDataArg->GetBearerServiceList();
    
        //  MAP API Note: a BearerServiceList object contains a list of 
        //  Ext_BearerServiceCode objects.

        //  [8-2] Retrieve contents of BearerServiceList object.

        for (int i = 0; i < bearerServiceList.Size(); i++)
        {
            //  [8-2-1] Retrieve reference to Ext_BearerServiceCode object.
            
            const Ext_BearerServiceCode& ext_bearerServiceCode = 
                            bearerServiceList.ElementAt(i);

            //  [8-2-2] Retrieve contents of Ext_BearerServiceCode object.

            vector<byte> vector4 = ext_bearerServiceCode.GetArray();

            //  Do something with vector of bytes...

            //  [8-2-3] Print Ext_BearerServiceCode object.

            cout << endl;
            cout << "Printing Ext_BearerServiceCode object..." << endl;
            cout << ext_bearerServiceCode;
            cout << endl;
        }

        //  [8-3] Print BearerServiceList object.

        cout << endl;
        cout << "Printing BearerServiceList object..." << endl;
        cout << bearerServiceList;
        cout << endl;
    }

    ////////////////////////////////////////////////////////////////////////////

    //  [9] Retrieve optional parameter "provisionedSS".

    if (insertSubscriberDataArg->OptionProvisionedSS())
    {
        //  [9-1] Retrieve reference to  Ext_SS_InfoList object.

        const Ext_SS_InfoList& ext_SS_InfoList = 
            insertSubscriberDataArg->GetProvisionedSS();

        //  MAP API Note: a Ext_SS_InfoList object contains a list of 
        //  Ext_SS_Info objects.

        //  [9-2] Retrieve contents of Ext_SS_InfoList object.

        for (int i = 0; i < ext_SS_InfoList.Size(); i++)
        {
            //  [9-2-1] Retrieve reference to Ext_SS_Info object.
            
            const Ext_SS_Info& ext_SS_Info = 
                            ext_SS_InfoList.ElementAt(i);

	        //  MAP API Note: a Ext-SS-Info object contains a choice of
	        //  Ext-ForwInfo, Ext-CallBarInfo, CUG-Info, Ext-SS-Data or 
            //  EMLPP-Info.

            //  [9-2-2] Retrieve contents of Ext_SS_Info object.
            
            if (ext_SS_Info.ChoiceForwardingInfo())
            {
                //  [9-2-2-1] Retrieve reference to Ext_ForwInfo object.
                
                const Ext_ForwInfo& ext_ForwInfo = 
                            ext_SS_Info.GetChoiceForwardingInfo();                
                
                //  [9-2-2-2] Retrieve contents of Ext_ForwInfo object.
                
                //  [9-2-2-2-1] Retrieve reference to SS_Code object.
                
                const SS_Code& sS_Code = ext_ForwInfo.GetSs_Code();

                //  [9-2-2-2-2] Retrieve contents of SS_Code object.
        
                vector<byte> vector5 = sS_Code.GetArray();

                //  Do something with vector of bytes...
                
                //  [9-2-2-2-3] Print SS_Code object.
                
                cout << endl;
                cout << "Printing SS_Code object..." << endl;
                cout << sS_Code;
                cout << endl;

                //  [9-2-2-2-4] Retrieve reference to Ext_ForwFeatureList 
                //  object.

                const Ext_ForwFeatureList& 
                    ext_ForwFeatureList = 
                        ext_ForwInfo.GetForwardingFeatureList();

                //  [9-2-2-2-5] Retrieve contents of Ext_ForwFeatureList object.
           
	            //  MAP API Note: a Ext_ForwFeatureList object contains a 
                //  list of Ext_ForwFeature objects.

                for (int i = 0; i < ext_ForwFeatureList.Size(); i++)
                {
                    //  [9-2-2-2-5-1] Retrieve reference to Ext_ForwFeature 
                    //  object.
            
                    const Ext_ForwFeature& ext_ForwFeature = 
                                    ext_ForwFeatureList.ElementAt(i);

                    //  [9-2-2-2-5-2] Retrieve contents of Ext_ForwFeature 
                    //  object.
                    
                    //  [9-2-2-2-5-2-1] Retrieve reference to Ext_SS_Status 
                    //  object.
                    
                    const Ext_SS_Status& ext_SS_Status = 
                        ext_ForwFeature.GetSs_Status();

                    //  [9-2-2-2-5-2-2] Retrieve contents of Ext_SS_Status 
                    //  object.

                    vector<byte> vector6 = ext_SS_Status.GetArray();

                    //  Do something with vector of bytes...
                    
                    //  [9-2-2-2-5-2-3] Print Ext_SS_Status object.

                    cout << endl;
                    cout << "Printing Ext_SS_Status object..." << endl;
                    cout << ext_SS_Status;
                    cout << endl;
                    
                    //  [9-2-2-2-5-2-4] Retrieve reference to 
                    //  Ext_BasicServiceCode object.
                    
                    const Ext_BasicServiceCode& ext_BasicServiceCode = 
                                    ext_ForwFeature.GetBasicService();

                    //  [9-2-2-2-5-2-5] Retrieve contents of 
                    //  Ext_BasicServiceCode object.

                    if (ext_BasicServiceCode.ChoiceExt_BearerService())
                    {
                        // Do something...
                    }
                    else if (ext_BasicServiceCode.ChoiceExt_Teleservice())
                    {
                        // Do something...
                    }
                    
                    //  [9-2-2-2-5-2-6] Print Ext_BasicServiceCode object.

                    cout << endl;
                    cout << "Printing Ext_BasicServiceCode object..." << endl;
                    cout << ext_BasicServiceCode;
                    cout << endl;
                    
                    //  [9-2-2-2-5-2-7] Retrieve reference to 
                    //  ISDN_SubaddressString object.
                    
                    const ISDN_SubaddressString& iSDN_SubaddressString =
                                    ext_ForwFeature.GetForwardedToSubaddress();

                    //  [9-2-2-2-5-2-8] Retrieve contents of 
                    //  ISDN_SubaddressString object.

                    vector<byte> vector7 = iSDN_SubaddressString.GetArray();

                    //  Do something with vector of bytes...
                    
                    //  [9-2-2-2-5-2-9] Print ISDN_SubaddressString object.

                    cout << endl;
                    cout << "Printing ISDN_SubaddressString object..." << endl;
                    cout << iSDN_SubaddressString;
                    cout << endl;
                    
                    //  [9-2-2-2-5-3] Print Ext_ForwFeature object.

                    cout << endl;
                    cout << "Printing Ext_ForwFeature object..." << endl;
                    cout << ext_ForwFeature;
                    cout << endl;
                }                
                
                //  [9-2-2-2-6] Print Ext_ForwFeatureList object.

                cout << endl;
                cout << "Printing Ext_ForwFeatureList object..." << endl;
                cout << ext_ForwFeatureList;
                cout << endl;
                
                //  [9-2-2-3] Print Ext_ForwInfo object.

                cout << endl;
                cout << "Printing Ext_ForwInfo object..." << endl;
                cout << ext_ForwInfo;
                cout << endl;
            }
            else if (ext_SS_Info.ChoiceCug_Info())
            {
                cout << endl;
                cout << "Choice Cug Info not printed..." << endl;
                cout << endl;
            }
            else if (ext_SS_Info.ChoiceSs_Data())
            {
                cout << endl;
                cout << "Choice Ss Data not printed..." << endl;
                cout << endl;
            }

            //  [9-2-3] Print Ext_SS_Info object.

            cout << endl;
            cout << "Printing Ext_SS_Info object..." << endl;
            cout << ext_SS_Info;
            cout << endl;
        }

        //  [9-3] Print Ext_SS_InfoList object.

        cout << endl;
        cout << "Printing Ext_SS_InfoList object..." << endl;
        cout << ext_SS_InfoList;
        cout << endl;
    }            

    ////////////////////////////////////////////////////////////////////////////

    //  [10] Free all memory allocated on the heap.

    //  [10-1] Delete Octets object.

    delete octets;

    //  [10-2] Delete InsertSubscriberDataArg object.

    delete insertSubscriberDataArg;
}
