////////////////////////////////////C++-//////////////////////////////////////
//                                                                          //
//   Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.      //
//             Manufactured in the United States of America.                //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.      //
//                                                                          //
//   This product and related documentation is protected by copyright and   //
//   distributed under licenses restricting its use, copying, distribution  //
//   and decompilation.  No part of this product or related documentation   //
//   may be reproduced in any form by any means without prior written       //
//   authorization of IntelliNet Technologies and its licensors, if any.    //
//                                                                          //
//   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      //
//   government is subject to restrictions as set forth in subparagraph     //
//   (c)(1)(ii) of the Rights in Technical Data and Computer Software       //
//   clause at DFARS 252.227-7013 and FAR 52.227-19.                        //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  CONTRACT: INTERNAL                                                      //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//
#include <its.h>
#include <its++.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <sys/timeb.h>
#include <string>
#include <map>


#include <engine++.h>
#include <its_thread_pool.h>
#include <its_work_item.h>
#include <its_mutex.h>

#include <tcap++.h>
#include <Asn.h>

#include <cap_cpp.h>
#include <cap_v2_assist_request_instructions_arg.h>
#include <cap_v2_play_announcement_arg.h>
#include <cap_v2_prompt_and_collect_user_information_arg.h>

#if defined(WIN32)
#define EXPORT  __declspec(dllexport)
#define IMPORT  __declspec(dllimport)
#else
#define EXPORT
#define IMPORT
#endif

#if defined(WIN32)
#pragma warning(disable : 4786)
#endif

#define LOCAL_SSN   2
#define REMOTE_SSN  2
#define LOCAL_PC    100
#define REMOTE_PC   1

//
// address indicator
//
#define ADDR_IND    (SCCP_CPA_ROUTE_NAT|SCCP_CPA_ROUTE_SSN|\
                     SCCP_CPA_HAS_PC|SCCP_CPA_HAS_SSN)

////////////////////////////////////////////////////////////////////////////////
//
//  Utilities.
//

//
//  Macro to get the size (count of items) of a fixed array.
//
#define FixedArraySize(array)       (sizeof(array) / sizeof(array[0]))

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

//
using namespace std;
using namespace its;
using namespace engine;
using namespace cap;  
using namespace cap_v2;
  
void InterpretOperationPromptAndCollectUserInformationArg(const vector<byte>& 
    encodedInsertSubscriberDataArg);
void InterpretOperationAssistRequestInstructionsArg(const vector<byte>& 
    encodedAssistRequestInstructionsArg);
void InterpretOperationPlayAnnouncement(const vector<byte>& 
                                        encodedPlayAnnouncementArg);

InformationToSend* InitializeInformationToSend(); 
Integer4* InitializeInteger4();
CollectedDigits::InterruptableAnnInd* InitializeInterruptableAnnInd();
PromptAndCollectUserInformationArg::DisconnectFromIPForbidden*
InitializePromptAndCollectUserInformation_DisconnectFromIPForbidden(); 
PlayAnnouncementArg::DisconnectFromIPForbidden*
InitializePlayAnnouncement_DisconnectFromIPForbidden(); 
Tone* InitializeTone();
CollectedDigits::VoiceInformation* InitializeVoiceInformation();
CollectedDigits::VoiceBack* InitializeVoiceBack();           
CollectedInfo* InitializeCollectedInfo();  
CorrelationID* InitializeCorrelationID();
InformationToSend* InitializeInformationToSend();
IPSSPCapabilities* InitializeIPSSPCapabilities();
PlayAnnouncementArg::RequestAnnouncementComplete* InitializeRequestAnnouncementComplete();

vector<byte> BuildOperationPromptAndCollectUserInformationArg();
vector<byte> BuildOperationAssistRequestInstructionArg();
vector<byte> BuildOperationPlayAnnouncementArg();

extern "C"
{
    void ReceiveTcapDlgComp_CCITT(ITS_HANDLE handle, 
                                  ITS_Worker *worker, ITS_Event *ev);

    void TcapThreadFunction_CCITT(its::ITS_ThreadPoolThread* thr, 
                                  ITS_HANDLE handle);

    void 
    RouteSS7(){}


    ITS_USHORT 
    RouteAPP(ITS_HDR *hdr, ITS_EVENT *event)
    {
        ThreadPoolEntry thr;
        engine::Worker *eng;
        cout << "Inside RouteAPP " << endl;
        workerPool->GetFirstAvailThread(thr);
        eng = reinterpret_cast<engine::Worker *>(thr.GetThread());
        //its::workerPool->DispatchOnThread(thr, DISP_Dispatch_USER_CPP,
        //                          (void *)eng->GetCallbackStruct());
        workerPool->DispatchOnThread(thr, TcapThreadFunction_CCITT,
                            (void *)0);
        ROUTE_AddApplication(eng->GetInstance(), hdr);
        return eng->GetInstance();
    }

    void
    MyPreFunc()
    {
        ThreadPoolEntry thr;
        engine::Worker *eng;
        cout << "Inside MyPreFunc " << endl;
        workerPool->GetFirstAvailThread(thr);
        eng = reinterpret_cast<engine::Worker *>(thr.GetThread());
        workerPool->DispatchOnThread(thr, DISP_Dispatch_USER_CPP,
                                     (void *)eng->GetCallbackStruct());
    }

    void 
    MyPostFunc(){}

    int 
    AppMain(its::ThreadPoolThread *thr, its::Event &event)
    {
        return ITS_SUCCESS;
    }

    int 
    FilterCacheMsgs(its::ThreadPoolThread *thr, its::Event &ev)
    {
        printf("FilterCacheMsgs\n");
        return ITS_SUCCESS;
    }

    int 
    ClientPostInit(its::ThreadPoolThread *thr, ITS_HANDLE h)
    {
        printf("ClientPostInit\n");
        return ITS_SUCCESS;
    }

    int 
    ClientPreInit(its::ThreadPoolThread *thr, ITS_HANDLE h)
    {
        printf("ClientPostInit\n");
        return ITS_SUCCESS;
    }

    void
    TcapThreadFunction_CCITT(its::ITS_ThreadPoolThread* thr, ITS_HANDLE handle)
    {
        SCCP_CallingPartyAddr origAddr;
        SCCP_CalledPartyAddr  destAddr;
        ITS_Worker* worker = static_cast<ITS_Worker*> (thr);
        ITS_USHORT instance = worker->GetInstance();
        handle = ITS_Initialize(worker->GetMask(), worker->GetInstance());
        while (!worker->GetExit())
        {
            ITS_Event event;
            int res = worker->GetNextEvent(event);
            if (res != ITS_SUCCESS)
            {
               ITS_Error itsError(res, __FILE__, __LINE__);
               cout << "******* Received Error from Gateway **********" 
                    << endl << flush;
               cout << endl << itsError.GetDescription() << endl << flush;
            }
            else
            {            
                cout << "Message# 27";
                ReceiveTcapDlgComp_CCITT(handle, worker, &event);
                break;
            }
        }
        cout << "TcapThreadFunction" << endl;
    }

    void
    ReceiveTcapDlgComp_CCITT(ITS_HANDLE handle, ITS_Worker *worker, 
                             ITS_Event *ev)
    {
       ITS_Event event;
       TCAP_Dialogue* dlg  = NULL;
       TCAP_Component* cpt = NULL;
       if (TCAP_MSG_TYPE((&ev->GetEvent())) == ITS_TCAP_DLG)
       {
          cout << "Received TCAP Dialogue" << endl;
          int res = TCAP_Dialogue::Receive(handle, *ev, &dlg);
          if (res != ITS_SUCCESS)
          {
              cout << "Receive Dilog Failed" << endl;
              ITS_THROW_ERROR(res);
          }
          // Must be a begin. 
          if (dlg->GetDialogueType() == TCPPT_TC_BEGIN)
          {
              cout << "TCAP Begin Received" << endl;
              TCAP_Begin* beginDlg = static_cast<TCAP_Begin*>(dlg);
              // Get the component.
              res = worker->GetNextEvent(event);
              if (res != ITS_SUCCESS)
              {
                 cout << "GetNextEvent Failed" << endl;
                 ITS_THROW_ERROR(res);
              }
              // Must be a component.
              if(TCAP_MSG_TYPE((&event.GetEvent())) == ITS_TCAP_CPT)
              {
                  cout << "TCAP Component";
                  res = TCAP_Component::Receive(handle, event, dlg, &cpt);
                  if (res != ITS_SUCCESS)
                  {
                      cout << "Component Receive Failed";
                      ITS_THROW_ERROR(res);
                  }
                  // Must be an invoke. 
                  if (cpt->GetComponentType() == TCPPT_TC_INVOKE)
                  {
                     TCAP_Invoke* invokeCpt = static_cast<TCAP_Invoke*>(cpt);
                     cout << "Received TCAP Invoke";
                     // Retrieve the operation.
                     // bool            isNational;
                     // ITS_OCTET       family;
                     // ITS_OCTET       operation;
                     ITS_ASSERT(invokeCpt != NULL);
                     ITS_ASSERT(beginDlg != NULL);
                     ITS_USHORT dlgId = beginDlg->GetDialogueID();
                     ITS_OCTET invokeId = invokeCpt->GetInvokeID(); 
                     //SendTcapResponse_CCITT(handle, dlgId, invokeId);
                     ITS_LONG operation = 0;
                     invokeCpt->GetOperation(operation);
                     // Selection according to GSM MAP operation.
                     switch (operation)
                     {
	      	         case  OP_assistRequestInstructions:
                         {
                             vector<byte> encodedAssistRequestInstructionsArg;
                             // The parameter field of the TCAP invoke component
                             // contains the CAMEL AssistRequestInstructions 
                             // Data operation argument.
                             invokeCpt->
                                 GetParameter(
                                     encodedAssistRequestInstructionsArg);

                             //
                             //  Function call uses CAMEL ASN.1 C++ API.
                             //
                             InterpretOperationAssistRequestInstructionsArg(
                                 encodedAssistRequestInstructionsArg); 
                            //

                            break;
                         }
		         case OP_playAnnouncement:
                         {
                             vector<byte> encodedPlayAnnouncement;
                             // The parameter field of the TCAP invoke component
                             // contains the CAMEL PlayAnnouncement operation 
                             // argument.
                             invokeCpt->GetParameter(encodedPlayAnnouncement);

                             //
                             //  Function call uses CAMEL ASN.1 C++ API.
                             //
                             InterpretOperationPlayAnnouncement(
                                 encodedPlayAnnouncement); 
                             //

                         break;
                         }
                         default:
                         {
		             cout << "operation code:  " <<  operation;
                             break;
                         }
                     } // Switch.

                     // Dispatch to procedure according to operation.           
                     invokeCpt->SetInvokeID(97);
                     // Prompt to select the proper option
                     cout << "Enter 1 to play announcement" << endl;
                     cout << "Enter 2 to prompt and collect user information" 
                          << endl;
                     vector<byte> encodedSubscriberData;
                     int choice;
                     cin >> choice;
                     if ( choice == 1 )
                     {
                         invokeCpt->SetOperation(OP_playAnnouncement);
                         invokeCpt->SetClass(1);
                         encodedSubscriberData = 
                             BuildOperationPlayAnnouncementArg();
                         invokeCpt->SetParameter(encodedSubscriberData);
                     }
                     else if ( choice == 2 )
                     {
                         invokeCpt->
                             SetOperation(OP_promptAndCollectUserInformation);
                             invokeCpt->SetClass(1);
                             encodedSubscriberData = 
                                 BuildOperationPromptAndCollectUserInformationArg();
                             invokeCpt->SetParameter(encodedSubscriberData);
                     }   
                     else
                     {
                         invokeCpt->SetOperation(OP_playAnnouncement);
                         invokeCpt->SetClass(1);
                         encodedSubscriberData = 
                             BuildOperationPlayAnnouncementArg();
                         invokeCpt->SetParameter(encodedSubscriberData);
                     }
                     cout << endl;
                     cout << "Ready to reply with(execute) CAP operation...";
                     cout << endl;
                     TCAP_End endDlg;
                     endDlg.SetDialogueID(dlgId); 
                     TCAP_Component::Send(handle, &endDlg, invokeCpt);
                     TCAP_Dialogue::Send(handle, &endDlg);
                  }
                  else // Not an Invoke
                  {
                      cout << "Received Componenet Not Invoke" << endl;
                      cout << "Not a valid TCAP Invoke Operation" << endl;
                  }               
               }
               else // Not a Component
               {
                   cout << "Did not Receive A Component";
                   cout << "Response/Reject to a timed out Dialogue ?" << endl;
               }
           }
           else // Not a Query With Permission
           {
              cout << "Received Dialogue Not Begin" << endl;
              cout << "Expected a TCAP_Begin" << endl;
              cout << "Response/Reject to a timed out Dialogue ?" << endl;
           }
       }
    }
}


/////////////////////////////////////////////////////////////////////////////
//
//  How to interpret an (encoded) CAMEL PlayAnnouncementArg 
//  argument (PlayAnnouncementArg):
//
//  o   Decode a PlayAnnouncementArg encoded value (i.e. create a 
//      PlayAnnouncementArg object from a PlayAnnouncementArg encoded 
//      value).
//
//  o   Retrieve Data from a PlayAnnouncementArg object.
//

void
InterpretOperationPlayAnnouncement(
    const vector<byte>& encodedPlayAnnouncementArg)
{
    //  [1] Create an Octets object from the 
    //  PromptAndCollectUserInformationArg ASN.1 
    //  encoded value.

    Octets* octets = new Octets(encodedPlayAnnouncementArg);

    ////////////////////////////////////////////////////////////////////////////

    //  [2] Create a InsertSubscriberDataArg object (used by the decode phase).

    PlayAnnouncementArg* 
        playAnnouncementArg = new 
            PlayAnnouncementArg();

    ////////////////////////////////////////////////////////////////////////////

    //  [3] Decode the PlayAnnouncementArg ASN.1 encoded value and therefore
    //  populate previously created PlayAnnouncementArg object.


    playAnnouncementArg->Decode(*octets);
    cout << endl;
    cout << "Printing decoded PlayAnnouncementArg object..." << endl;
    cout << *playAnnouncementArg;
    cout << endl;

    ////////////////////////////////////////////////////////////////////////////

    //  [10] Free all memory allocated on the heap.

    //  [10-1] Delete Octets object.

    delete octets;

    //  [10-2] Delete PlayAnnouncementArg object.

    delete playAnnouncementArg;
}

/////////////////////////////////////////////////////////////////////////////
//
//  How to interpret an (encoded) CAMEL AssistRequestInstructionsArg 
//  argument (AssistRequestInstructionsArg):
//
//  o   Decode a AssistRequestInstructionsArg encoded value (i.e. create a 
//      AssistRequestInstructionsArg object from a AssistRequestInstructionsArg encoded 
//      value).
//
//  o   Retrieve Data from a AssistRequestInstructionsArg object.
//

void
InterpretOperationAssistRequestInstructionsArg(
    const vector<byte>& encodedAssistRequestInstructionsArg)
{
    //  [1] Create an Octets object from the AssistRequestInstructionsArg ASN.1 
    //  encoded value.

    Octets* octets = new Octets(encodedAssistRequestInstructionsArg);

    /////////////////////////////////////////////////////////////////////////

    //  [2] Create a AssistRequestInstructionsArg object (used by the decode 
    //  phase).

    AssistRequestInstructionsArg* 
        assistRequestInstructionsArg = new AssistRequestInstructionsArg();

    /////////////////////////////////////////////////////////////////////////

    //  [3] Decode the AssistRequestInstructionsArg ASN.1 encoded value and 
    //  therefore
    //  populate previously created AssistRequestInstructionsArg object.


    assistRequestInstructionsArg->Decode(*octets);
    cout << endl;
    cout << "Printing decoded AssistRequestInstructionsArg object..." << endl;
    cout << *assistRequestInstructionsArg;
    cout << endl;

    //////////////////////////////////////////////////////////////////////////

    //  [4] Free all memory allocated on the heap.

    //  [4-1] Delete Octets object.

    delete octets;

    //  [4-2] Delete AssistRequestInstructionsArg object.

    delete assistRequestInstructionsArg;
}

////////////////////////////////////////////////////////////////////////////////
//
//  How to Build a CAMEL AssistRequestInstruction operation argument 
//  (AssistRequestInstructionArg):
//
//  o   Create AssistRequestInstructionArg object.
//
//  o   Insert data step by step in the created AssistRequestInstructionArg object 
//      (i.e. populate various parameters of the AssistRequestInstruction 
//      operation argument).
//  
//  o   Encode the AssistRequestInstructionArg object to produce an 
//      AssistRequestInstructionArg encoded value.
//
    
vector<byte>
BuildOperationAssistRequestInstructionArg()
{
    AssistRequestInstructionsArg *assistRequestInstructionArg =
        new AssistRequestInstructionsArg();
        // Set Parameters
        cout << endl;
        cout << "Setting AssistRequestInstruction Parameters:" << endl;
        cout << "---------------------------" << endl;
        cout << endl;

        assistRequestInstructionArg->
            SetCorrelationID(InitializeCorrelationID()) ;
            assistRequestInstructionArg->
                SetIPSSPCapabilities(InitializeIPSSPCapabilities());

        // Extensions, not set
        Octets* octets = NULL;
        octets = assistRequestInstructionArg->Encode();
        cout << endl;
        cout << "Printing assistRequestInstructionArg ASN.1 encoded value..." 
             << endl;
        cout << *octets;
        cout << endl;

        //////////////////////////////////////////////////////////////////////

        //  [11] Retrieve assistRequestInstructionArg ASN.1 encoded value from 
        //  octets object.
        vector<byte> encodedAssistRequestInstructionArg = octets->GetArray();

        //////////////////////////////////////////////////////////////////////

        //  [12] Free all memory allocated on the heap.
        //  [12-1] Delete assistRequestInstructionArg object (and therefore 
        //  all the parameter objects that have been previously set).

    	delete assistRequestInstructionArg;

        //  [12-2] Delete Octets object created by the call to Encode.

    	delete octets;

        //////////////////////////////////////////////////////////////////////

        //  [13] Return (by value) InsertSubscriberDataArg ASN.1 encoded value.

    	return encodedAssistRequestInstructionArg;
}

//////////////////////////////////////////////////////////////////////////////
//
//  Initialization of the different messages parameters 
//  for AssistRequestInstructionArg.
//
//////////////////////////////////////////////////////////////////////////////


CorrelationID* 
InitializeCorrelationID()
{
    byte array[] = { 0x02, 0x03, 0x04, 0x05, 0x06 };
    CorrelationID* cid = new CorrelationID(FixedByteArrayToVector(array));
    return cid;
}             

IPSSPCapabilities* 
InitializeIPSSPCapabilities()
{
    byte array[] = { 0x01, 0x02 };
    IPSSPCapabilities* cid =
    new IPSSPCapabilities(FixedByteArrayToVector(array));
    return cid;
}    

////////////////////////////////////////////////////////////////////////////////
//
//  END OF
//  Initialization of the different messages parameters 
//  for AssistRequestInstructionArg.
//
////////////////////////////////////////////////////////////////////////////////                   

////////////////////////////////////////////////////////////////////////////////
//
//  How to Build a CAMEL PlayAnnouncement operation argument 
//  (PlayAnnouncementArg):
//
//  o   Create PlayAnnouncementArg object.
//
//  o   Insert data step by step in the created PlayAnnouncementArg object 
//      (i.e. populate various parameters of the PlayAnnouncement
//      operation argument).
//  
//  o   Encode the PlayAnnouncementArg object to produce an 
//      PlayAnnouncementArg encoded value.
//

vector <byte>
BuildOperationPlayAnnouncementArg()
{
    PlayAnnouncementArg* playAnnouncementArg =
    new PlayAnnouncementArg();    // Set Parameters for CAP message to send
    cout << endl;
    cout << "Setting playAnnouncement Parameters:" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << endl;
    playAnnouncementArg->SetInformationToSend(InitializeInformationToSend());
    playAnnouncementArg->
        SetDisconnectFromIPForbidden(
            InitializePlayAnnouncement_DisconnectFromIPForbidden());
        playAnnouncementArg->SetRequestAnnouncementComplete(
            InitializeRequestAnnouncementComplete());
        Octets* octets = NULL;
        octets = playAnnouncementArg->Encode();
        cout << endl;
        cout << "Printing playAnnouncementArg ASN.1 encoded value..." << endl;
        cout << *octets;
        cout << endl;

    /////////////////////////////////////////////////////////////////////////

    //  [11] Retrieve playAnnouncementArg ASN.1 encoded value from octets 
    //  object.
    vector<byte> encodedPlayAnnouncementArg = octets->GetArray();
    //
    ////////////////////////////////////////////////////////////////////////////

    //  [12] Free all memory allocated on the heap.
    //  [12-1] Delete playAnnouncementArg object (and therefore all the 
    //  parameter objects that have been previously set).
    delete playAnnouncementArg;
    //  [12-2] Delete Octets object created by the call to Encode.

    delete octets;

    ////////////////////////////////////////////////////////////////////////////

    //  [13] Return (by value) InsertSubscriberDataArg ASN.1 encoded value.

    return encodedPlayAnnouncementArg;
}

////////////////////////////////////////////////////////////////////////////////
//
//  How to Build a CAMEL PromptAndCollectUserInformation operation argument
//  (PromptAndCollectUserInformationArg):
//
//  o   Create PromptAndCollectUserInformationArg object.
//
//  o   Insert data step by step in the created PromptAndCollectUserInformationArg object
//      (i.e. populate various parameters of the PromptAndCollectUserInformation

//      operation argument).
//
//  o   Encode the PromptAndCollectUserInformationArg object to produce an
//      PromptAndCollectUserInformationArg encoded value.
//

vector<byte>
BuildOperationPromptAndCollectUserInformationArg()
{
    PromptAndCollectUserInformationArg* promptAndCollectUserInformationArg=
        new PromptAndCollectUserInformationArg();
    printf("\n going to  set the parameters");
    promptAndCollectUserInformationArg->
        SetCollectedInfo(InitializeCollectedInfo());
    promptAndCollectUserInformationArg->
        SetDisconnectFromIPForbidden(
           InitializePromptAndCollectUserInformation_DisconnectFromIPForbidden());
    promptAndCollectUserInformationArg->
        SetInformationToSend(InitializeInformationToSend());

    Octets* octets = NULL;
    octets = promptAndCollectUserInformationArg->Encode();
    cout << endl;
    cout << "Printing PromptAndCollectUserInformationArg ASN.1 encoded value..."
         << endl;
    cout << *octets;
    cout << endl;

////////////////////////////////////////////////////////////////////////////

//  [11] Retrieve PromptAndCollectUserInformationArg ASN.1 encoded value from octets
//  object.

vector<byte> encodedPromptAndCollectUserInformationArg = octets->GetArray();

////////////////////////////////////////////////////////////////////////////

//  [12] Free all memory allocated on the heap.

//  [12-1] Delete PromptAndCollectUserInformationArg object (and therefore all the
//  parameter objects that have been previously set).

    delete promptAndCollectUserInformationArg;

//  [12-2] Delete Octets object created by the call to Encode.

    delete octets;

/////////////////////////////////////////////////////////////////////////////////

//  [13] Return (by value) PromptAndCollectUserInformationArg ASN.1 encoded value.

    return encodedPromptAndCollectUserInformationArg;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Initialization of the different messages parameters 
//  for PlayAnnouncementArg and PromptAndCollectUserInformationArg.
//
////////////////////////////////////////////////////////////////////////////////    

PlayAnnouncementArg::RequestAnnouncementComplete* 
    InitializeRequestAnnouncementComplete()
{
    PlayAnnouncementArg::RequestAnnouncementComplete* rac =
        new PlayAnnouncementArg::RequestAnnouncementComplete(false);
    return rac;
}  

PlayAnnouncementArg::DisconnectFromIPForbidden*
InitializePlayAnnouncement_DisconnectFromIPForbidden()
{
    PlayAnnouncementArg::DisconnectFromIPForbidden* dip =
        new PlayAnnouncementArg::DisconnectFromIPForbidden(true);
    return dip;
}                
          
Integer4* 
InitializeInteger4()
{
    long valparam = 11;
    Integer4* integer4 = new Integer4(valparam);
    return integer4;
}          

Tone* 
InitializeTone()
{
    Tone *t = new Tone;
    // Ask user to enter tone-id
    t->SetToneID(InitializeInteger4());
    // Ask user to enter an optional  duration value
    t->SetDuration(InitializeInteger4());
    cout << endl;
    return t;
}         

InformationToSend* 
InitializeInformationToSend()
{
    InformationToSend* its = new InformationToSend();
    its->SetChoiceTone(InitializeTone());
    return its;
}        
PromptAndCollectUserInformationArg::DisconnectFromIPForbidden*
InitializePromptAndCollectUserInformation_DisconnectFromIPForbidden()
{
    PromptAndCollectUserInformationArg::DisconnectFromIPForbidden* dip= 
        new PromptAndCollectUserInformationArg::DisconnectFromIPForbidden(true);
    return dip;
}

CollectedDigits::MinimumNbOfDigits* 
InitializeMinimumNbOfDigits()
{
    long valparam;
    CollectedDigits::MinimumNbOfDigits* mnd;
    // Ask user to enter an integer between 1-30
    cout << "Enter minimum number of digits, integer [1..30]: ";
    cin >> valparam;
    cout << endl;
    mnd = new CollectedDigits::MinimumNbOfDigits(valparam);
    return mnd;
}
CollectedDigits::MaximumNbOfDigits* 
InitializeMaximumNbOfDigits()
{
    long valparam;
    CollectedDigits::MaximumNbOfDigits* mxd;
    // Ask user to enter an integer between 1-30
    cout << "Enter maximum number of digits, integer [1..30]: ";
    cin >> valparam;
    cout << endl;
    mxd = new CollectedDigits::MaximumNbOfDigits(valparam);
    return mxd;
}
ErrorTreatment* 
InitializeErrorTreatment()
{
    ErrorTreatment* et = new ErrorTreatment();
    et->SetHelp();
    return et;
}
CollectedDigits::InterruptableAnnInd* 
InitializeInterruptableAnnInd()
{
    CollectedDigits::InterruptableAnnInd* iai =
       new CollectedDigits::InterruptableAnnInd(true);
    return iai;
}
CollectedDigits::VoiceInformation* 
InitializeVoiceInformation()
{
    CollectedDigits::VoiceInformation* vi = 
        new CollectedDigits::VoiceInformation(true);
    return vi;
}
CollectedDigits::VoiceBack* 
InitializeVoiceBack()
{
    CollectedDigits::VoiceBack* vb =
        new CollectedDigits::VoiceBack(false);
    return vb;
}
CollectedDigits* 
InitializeCollectedDigits()
{
    CollectedDigits* cd = new CollectedDigits();
    cd->SetMinimumNbOfDigits(InitializeMinimumNbOfDigits());
    cd->SetMaximumNbOfDigits(InitializeMaximumNbOfDigits());
    cd->SetErrorTreatment(InitializeErrorTreatment());
    cd->SetInterruptableAnnInd(InitializeInterruptableAnnInd());
    cd->SetVoiceInformation(InitializeVoiceInformation());
    cd->SetVoiceBack(InitializeVoiceBack());
    return cd;
}

CollectedInfo* 
InitializeCollectedInfo()
{
    CollectedInfo* ci = new CollectedInfo();
    ci->SetChoiceCollectedDigits(InitializeCollectedDigits());
    return ci;
}
////////////////////////////////////////////////////////////////////////////////
//
//  END OF
//  Initialization of the different messages parameters 
//  for PlayAnnouncementArg.
//
////////////////////////////////////////////////////////////////////////////////    
