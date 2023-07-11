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
#include <cap_v2_prompt_and_collect_user_information_arg.h>
#include <cap_v2_assist_request_instructions_arg.h>
#include <cap_v2_play_announcement_arg.h>

#if defined(WIN32)
#pragma warning(disable : 4786)
#endif
//
#define LOCAL_SSN   2
#define REMOTE_SSN  2
#define LOCAL_PC    1
#define REMOTE_PC   100

//
// address indicator
//
#define ADDR_IND    (SCCP_CPA_ROUTE_NAT|SCCP_CPA_ROUTE_SSN|\
                     SCCP_CPA_HAS_PC|SCCP_CPA_HAS_SSN)
#if defined(WIN32)
#define EXPORT  __declspec(dllexport)
#define IMPORT  __declspec(dllimport)
#else
#define EXPORT
#define IMPORT
#endif
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

//
using namespace std;
using namespace its;
using namespace engine;
using namespace cap_v2;
using namespace cap;


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
InformationToSend* InitializeInformationToSend(); 
CorrelationID* InitializeCorrelationID();
IPSSPCapabilities* InitializeIPSSPCapabilities();
PlayAnnouncementArg::RequestAnnouncementComplete* InitializeRequestAnnouncementComplete();

vector<byte> BuildOperationAssistRequestInstructionArg();
vector<byte> BuildOperationPlayAnnouncementArg();

void InterpretOperationPlayAnnouncement(const vector<byte>& 
                                        encodedPlayAnnouncementArg);
void InterpretOperationPromptAndCollectUserInformationArg(const vector<byte>& 
                                                          encodedInsertSubscriberDataArg);

bool stop=false;
extern "C"
{
    void ReceiveTcapDlgComp_ITU(ITS_HANDLE handle, ITS_Worker *worker, 
                                ITS_Event *ev);
    extern "C" EXPORT void
    TcapThreadFunction_ITU(its::ITS_ThreadPoolThread* thr, ITS_HANDLE handle)
    {
        ITS_USHORT dialogueID;
        SCCP_CallingPartyAddr origAddr;
        SCCP_CalledPartyAddr  destAddr;
        ITS_Worker* worker = static_cast<ITS_Worker*> (thr);
        ITS_USHORT instance = worker->GetInstance();
        handle = ITS_Initialize(worker->GetMask(), worker->GetInstance());
        TCAP_AllocateDialogueId(&dialogueID);
        TCAP_Begin beginDlg;
        beginDlg.SetDialogueID(dialogueID);
        ITS_OCTET slsKey, priority;
        ITS_OCTET gtt[7] = 
            { 0x01, 0x34, 
                 /* First 3 bytes are TT, NP and NAI, then the number */
                      0x96, 0x09, 0x50, 0x23, 0x01 };

        slsKey = 0;
        priority = 0;
        beginDlg.SetQualityOfService(QOSI_RET_OPT, slsKey, priority);

        //Set Orig Addr
        origAddr.SetSSN(LOCAL_SSN);
        origAddr.SetPointCode(LOCAL_PC);
        ITS_OCTET addressIndicator = SCCP_CPA_HAS_SSN | 
        SCCP_CPA_HAS_PC | SCCP_CPA_ROUTE_NAT | SCCP_CPA_GTTI_TRANS_ANSI;
        origAddr.SetGlobalTitle(addressIndicator, gtt, 7);
        origAddr.SetRouteByPCSSN(true);     // GTT in originating address     
        origAddr.SetInternationalRouting(false);
        beginDlg.SetOPC(LOCAL_PC);
        beginDlg.SetOrigAddr(origAddr);         
        //Set Dest Addr
        destAddr.SetSSN(REMOTE_SSN);
        destAddr.SetPointCode(REMOTE_PC);
        addressIndicator = SCCP_CPA_HAS_SSN | SCCP_CPA_HAS_PC| 
        SCCP_CPA_ROUTE_NAT | SCCP_CPA_GTTI_TRANS_ANSI;
        destAddr.SetGlobalTitle(addressIndicator, gtt, 7);
        destAddr.SetRouteByPCSSN(true);     // GTT in originating address     
        destAddr.SetInternationalRouting(false);
        beginDlg.SetDPC(REMOTE_PC);
        beginDlg.SetDestAddr(destAddr);     
        TCAP_Invoke invokeCpt;
        int op;
        invokeCpt.SetInvokeID(96); 
        for(;;)
        {
            cout << endl<< "please choose from the following operations:"<<endl;
            cout <<"1: Assist Request Instruction."<<endl;
            cin >> op;
            if (op==1)
            {
                invokeCpt.SetOperation(OP_assistRequestInstructions);
                invokeCpt.SetClass(1);
                invokeCpt.SetTimeOut(100);
                vector<byte> encodedInsertSubscriberDataArg;
                encodedInsertSubscriberDataArg = 
                    BuildOperationAssistRequestInstructionArg();

                invokeCpt.SetParameter(encodedInsertSubscriberDataArg);
                break;
            }
            else
                cout << "Invalid choice: " << op << endl;
        }
        ITS_HDR    hdr;
        hdr.type = ITS_TCAP;
        hdr.context.dialogue_id = dialogueID;
        int res = ROUTE_AddApplication(instance, &hdr);
        if (res != ITS_SUCCESS)
        {
            cout << "Message# 38";
            cout << "Thread(" 
                 << "Failed to execute ROUTE_AddApplication with error "
                 << res << endl;
            ITS_THROW_ERROR(worker != NULL);
        }
        TCAP_Component::Send(handle, &beginDlg, &invokeCpt);
        TCAP_Dialogue::Send(handle, &beginDlg);
        while (stop==false)
        {
            ITS_Event event;
            int res = worker->GetNextEvent(event);
            if (res != ITS_SUCCESS)
            {
                ITS_Error itsError(res, __FILE__, __LINE__);
                cout << "******* Received Error from Gateway **********" << endl << flush;
                cout << endl << itsError.GetDescription() << endl << flush;
            }
            else
            {            
                ReceiveTcapDlgComp_ITU(handle, worker, &event);
                break;
            }
         }
         cout << "TcapThreadFunction" << endl;
         ROUTE_DeleteApplication(worker->GetInstance(), &hdr);
         //  ITS_Terminate(handle);
         // ITS_GlobalStop();
    }

    void
    ReceiveTcapDlgComp_ITU(ITS_HANDLE handle, ITS_Worker *worker, ITS_Event *ev)
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
                cout << "Receive Dialogue Failed" << endl;
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
                if (TCAP_MSG_TYPE((&event.GetEvent())) == ITS_TCAP_CPT)
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
                        //bool            isNational;
                        //ITS_OCTET       family;
                        // ITS_OCTET       operation;
                        ITS_ASSERT(invokeCpt != NULL);
                        ITS_ASSERT(beginDlg != NULL);
                        ITS_USHORT dlgId = beginDlg->GetDialogueID();
                        ITS_OCTET invokeId = invokeCpt->GetInvokeID(); 
                        //SendTcapResponse_ITU(handle, dlgId, invokeId);
                        // Dispatch to procedure according to operation.                        
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
                      cout << "Response/Reject to a timed out Dialogue ?" 
                           << endl;
                 }
             }
             else if (dlg->GetDialogueType() == TCPPT_TC_END)
             {
                 cout << "TCAP End Received" << endl;
                 TCAP_End* EndDlg = static_cast<TCAP_End*>(dlg);

                 // Get the component.
                 res = worker->GetNextEvent(event);
                 if (res != ITS_SUCCESS)
                 {
                     cout << "GetNextEvent Failed" << endl;
                     ITS_THROW_ERROR(res);
                 }
                 // Must be a component.
                 if (TCAP_MSG_TYPE((&event.GetEvent())) == ITS_TCAP_CPT)
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
                         TCAP_Invoke* invokeCpt =  
                             static_cast<TCAP_Invoke*>(cpt);
                         cout << "Received TCAP Invoke";
                         // Retrieve the operation.
                         //bool            isNational;
                         //ITS_OCTET       family;
                         // ITS_OCTET       operation;
                         ITS_ASSERT(invokeCpt != NULL);
                         ITS_ASSERT(EndDlg != NULL);
                         ITS_USHORT dlgId = EndDlg->GetDialogueID();
                         ITS_OCTET invokeId = invokeCpt->GetInvokeID(); 
                         //SendTcapResponse_ITU(handle, dlgId, invokeId);
                         ITS_LONG operation = 0;
                         invokeCpt->GetOperation(operation);
                         // Selection according to GSM MAP operation.

                         switch (operation)
                         {
                             case OP_playAnnouncement:
                             {
                                 vector<byte> encodedPlayAnnouncement;
                                // The parameter field of the TCAP invoke 
                                // component contains the CAMEL 
                                // PlayAnnouncement operation argument.
                                invokeCpt->
                                    GetParameter(encodedPlayAnnouncement);
                                //
                                //  Function call uses CAMEL ASN.1 C++ API.
                                //
                                InterpretOperationPlayAnnouncement(
                                    encodedPlayAnnouncement);

                                //
                             break;
                             }
                             case OP_promptAndCollectUserInformation:
                             {
                                 vector<byte> 
                                 encodedpromptAndCollectUserInformation;
                                 // Parameter field of the TCAP invoke component
                                 // contains the GSM MAP Insert Subscriber 
                                 // Data operation argument.
                                 invokeCpt->
                                     GetParameter(
                                        encodedpromptAndCollectUserInformation);

                                 //
                                 //  Function call uses GSM MAP ASN.1 C++ API.
                                 //
                                 InterpretOperationPromptAndCollectUserInformationArg(encodedpromptAndCollectUserInformation);

                                 //
                             break;
                             }
                             default:
                             {
                                 cout << "operation code:  " <<  operation;
                             }
                         } // Switch.
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
                     cout << "Response/Reject to a timed out Dialogue ?" 
                          << endl;
                 }
             }
             cout << "End Dialogue  Message Received" << endl;
             stop=true; 
         }
         else // Not a Query With Permission
         {
             cout << "Received Dialogue Not Begin" << endl;
             cout << "Expected a TCAP_Begin" << endl;
             cout << "Response/Reject to a timed out Dialogue ?" << endl;
         }
     }
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
    assistRequestInstructionArg->SetCorrelationID(InitializeCorrelationID()) ;
    assistRequestInstructionArg->SetIPSSPCapabilities(InitializeIPSSPCapabilities());
    // Extensions, not set
    Octets* octets = NULL;
    octets = assistRequestInstructionArg->Encode();
    cout << endl;
    cout << "Printing assistRequestInstructionArg ASN.1 encoded value..." << endl;
    cout << *octets;
    cout << endl;

    //////////////////////////////////////////////////////////////////////////

    // [11] Retrieve AssistRequestInstructionArg ASN.1 encoded value 
    // from octets object.

    vector<byte> encodedAssistRequestInstructionArg = octets->GetArray();

    //////////////////////////////////////////////////////////////////////////

    //  [12] Free all memory allocated on the heap.
    //  [12-1] Delete assistRequestInstructionArg object (and therefore all the 
    //  parameter objects that have been previously set).

    delete assistRequestInstructionArg;

    //  [12-2] Delete Octets object created by the call to Encode.

    delete octets;

    //////////////////////////////////////////////////////////////////////////

    //  [13] Return (by value) encodedAssistRequestInstructionArg 
    //  ASN.1 encoded value.

    return encodedAssistRequestInstructionArg;
}

//////////////////////////////////////////////////////////////////////////
//
//  Initialization of the different messages parameters 
//  for AssistRequestInstructionArg.
//
//////////////////////////////////////////////////////////////////////////


CorrelationID* InitializeCorrelationID()
{
    byte array[] = { 0x02, 0x03, 0x04, 0x05, 0x06 };
    CorrelationID* cid = new CorrelationID(FixedByteArrayToVector(array));
    return cid;
}             

IPSSPCapabilities* InitializeIPSSPCapabilities()
{
    byte array[] = { 0x01, 0x02 };
    IPSSPCapabilities* cid =
    new IPSSPCapabilities(FixedByteArrayToVector(array));
    return cid;
}    
//////////////////////////////////////////////////////////////////////////
//
//  END OF
//  Initialization of the different messages parameters 
//  for AssistRequestInstructionArg.
//
////////////////////////////////////////////////////////////////////////////////                   

////////////////////////////////////////////////////////////////////////////////
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
    // [1] Create an Octets object from the PromptAndCollectUserInformationArg 
    // ASN.1  encoded value.

    Octets* octets = new Octets(encodedPlayAnnouncementArg);

////////////////////////////////////////////////////////////////////////////

//  [2] Create a InsertSubscriberDataArg object (used by the decode phase).

    PlayAnnouncementArg* playAnnouncementArg = new PlayAnnouncementArg();

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
void
InterpretOperationPromptAndCollectUserInformationArg(
    const vector<byte>& encodedPromptAndCollectUserInformationArg)
{
    // [1] Create an Octets object from the PromptAndCollectUserInformationArg 
    // ASN.1 encoded value.

    Octets* octets = new Octets(encodedPromptAndCollectUserInformationArg);

////////////////////////////////////////////////////////////////////////////

//  [2] Create a InsertSubscriberDataArg object (used by the decode phase).

    PromptAndCollectUserInformationArg* promptAndCollectUserInformationArg = 
        new PromptAndCollectUserInformationArg();

////////////////////////////////////////////////////////////////////////////

//  [3] Decode the PromptAndCollectUserInformationArg ASN.1 encoded value and 
//  therefore populate previously created PromptAndCollectUserInformationArg 
//  object.

    promptAndCollectUserInformationArg->Decode(*octets);
    cout << endl;
    cout << "Printing decoded PromptAndCollectUserInformationArg object..." 
         << endl;
    cout << *promptAndCollectUserInformationArg;
    cout << endl;

////////////////////////////////////////////////////////////////////////////

//  [10] Free all memory allocated on the heap.

//  [10-1] Delete Octets object.

    delete octets;

//  [10-2] Delete PromptAndCollectUserInformationArg object.

    delete promptAndCollectUserInformationArg;
}


