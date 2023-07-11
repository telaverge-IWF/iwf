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
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <time.h>
#include <sys/timeb.h>
#include <strstream>
#include <string>
#include <map>

#include <engine++.h>
#include <its_thread_pool.h>
#include <its_work_item.h>
#include <its_mutex.h>
#include <its_ip_trans.h>
#include <tcap++.h>
#include <Asn.h>
#include <AsnException.h>
#include <cap_cpp.h>
#include <cap_v2_prompt_and_collect_user_information_arg.h>
#include <cap_v2_assist_request_instructions_arg.h>
#include <cap_v2_play_announcement_arg.h>
#include <cap_v2_specialized_resource_report_arg.h>
#include <cap_v2_received_information_arg.h>

#include <its_timers.h>

#include <app_trace.h>

#if defined(WIN32)
#pragma warning(disable : 4786)
#endif

#define LOCAL_SSN   2	//IPD SSN
#define REMOTE_SSN  2   //SCP SSN
#define LOCAL_PC    10  //IPD Point Code
#define TmpSize     1024    //Temporary variables size
#define MaxSize     52100  //Maximum size of an XML message 
#define HeaderSize  46  // Size of the XML Message Header

//
// address indicator
//
#define ADDR_IND        ( SCCP_CPA_ROUTE_NAT | SCCP_CPA_ROUTE_SSN | \
                          SCCP_CPA_HAS_PC | SCCP_CPA_HAS_SSN)
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
#define FixedArraySize( array )        (sizeof( array ) / sizeof( array[0] ))

//
//  Macro to convert fixed arrays (of bytes) to vectors.
//
#define FixedByteArrayToVector(array)   \
    ( vector<byte>( array, array + FixedArraySize(array)) )

//
//  Macro to convert fixed arrays (of booleans) to vectors.
//
#define FixedBooleanArrayToVector(array)   \
    (vector<bool>(array, array + FixedArraySize(array)))

using namespace std;
using namespace its;
using namespace engine;
using namespace cap_v2;
using namespace cap;

/////////////////////////////////////////////////////////////////////////////
//
//  Synchronization string, between each XML message
//
/////////////////////////////////////////////////////////////////////////////

static char* sync_data = "@@@@@@";
extern ITS_USHORT IVRTransportInst; 
/////////////////////////////////////////////////////////////////////////////
//
//  Functions prototypes
//
/////////////////////////////////////////////////////////////////////////////


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

vector<byte> BuildOperationAssistRequestInstructionArg(char XMLmessage[]);

vector<byte> BuildOperationPlayAnnouncementArg();

void InterpretOperationPlayAnnouncement
     (
     const vector<byte>& encodedPlayAnnouncementArg,
     ITS_USHORT dlgID
     );

void InterpretOperationPromptAndCollectUserInformationArg
     (
     const vector<byte>& encodedInsertSubscriberDataArg,
     ITS_USHORT dlgID 
     );

/////////////////////////////////////////////////////////////////////////////
//
//  Global variables
//  TableSize is the size of the correlation table between the TCAP dialogue 
//  Ids and the dialogue Ids set by the IVR.
//
/////////////////////////////////////////////////////////////////////////////

const int TableSize=65536;

/////////////////////////////////////////////////////////////////////////////
//
//  Correlation Table class definition
//
/////////////////////////////////////////////////////////////////////////////


class TcapdidToIvrdidTable
{
    private:
	ITS_USHORT    data[TableSize];
	Mutex         *key;

    public:
	TcapdidToIvrdidTable()
	{
	    key = new Mutex(0);
	    memset (data, 0, TableSize * sizeof(ITS_USHORT));
	}

	int
	InsertEntry ( ITS_USHORT TcapDid, ITS_USHORT IvrDid ) //insert in table
	{
	    if (( key->Acquire()==ITS_SUCCESS ))
	    {
               APP_TRACE_DEBUG(( "Mutex acquired, inserting in table" ));
	       data[TcapDid] = IvrDid;
	    }
	    else
	    {
               APP_TRACE_WARNING(("could not acquire Mutex " ));
	    }
	    if (key->Release()==ITS_SUCCESS)
	    {
                APP_TRACE_DEBUG(("Mutex Released, inserting in table finished " ));
	    }
	    else
	    {
                APP_TRACE_WARNING(("could not release Mutex " ));
	    }
	    return ITS_SUCCESS;
	}

	int
	RemoveEntry ( ITS_USHORT TcapDid ) //delete from table
	{
	    if ( key->Acquire() == ITS_SUCCESS )
	    {
               APP_TRACE_DEBUG(("Mutex acquired, deleting from table " ));
	       data[TcapDid] = 0;
	    }
	    else
	    {
               APP_TRACE_WARNING(( "could not acquire Mutex " ));
	    }
	    if ( key->Release()==ITS_SUCCESS )
	    {
               APP_TRACE_DEBUG(( "Mutex Released, inserting in table finished " ));
	    }
	    else
	    {
               APP_TRACE_WARNING(( "could not release Mutex " ));
	    }
	    return ITS_SUCCESS;
	}

	ITS_USHORT RetrieveEntry ( ITS_USHORT TcapDid ) //retrieve from table
	{
	    return ( data[TcapDid] );
	}
};

/////////////////////////////////////////////////////////////////////////////
//
//  End of Correlation Table class definition
//
/////////////////////////////////////////////////////////////////////////////

bool stop=false; //When to stop the IPD

TcapdidToIvrdidTable table; //Correlation Table Object

extern "C"
{
////////////////////////////////////////////////////////////////
//
//Gateway Post initialize function
//
////////////////////////////////////////////////////////////////

extern "C" EXPORT int GTW_PostInit
                      (
                      its::ITS_ThreadPoolThread* thr, 
                      ITS_HANDLE handle
                      )
{
    //Find IVR Transport

    static bool IVRTransportInstFound = false; 
    if (!IVRTransportInstFound)
    {
        IVRTransportInstFound =true;
        for (unsigned short l=0;l<32;l++)
        {
            TRANSPORT_Control *tc= TRANSPORT_FindTransport(l);
            if (tc != NULL && strcmp(tc->transport.name,"IVR")==0)
            {
                APP_TRACE_DEBUG(( "FOUND IVR TRANSPORT " ));
                //IVRTransportInst=l;
            }
        }
    }
    return ( ITS_SUCCESS );
}

////////////////////////////////////////////////////////////////
//
//  Gateway User Message Handler function
//  This function will receive the events from the gateway and 
//  forward them to the IVR.
//
////////////////////////////////////////////////////////////////


extern "C" EXPORT int GTW_UserMsgHandler
                      (
                      its::ITS_ThreadPoolThread* thr, 
                      Event& ev
                      )
{
    ITS_HANDLE handle = NULL;
    ITS_Event event;
    TCAP_Dialogue* dlg  = NULL;
    TCAP_Component* cpt = NULL;

    ITS_Worker* worker = static_cast<ITS_Worker*> (thr);
    APP_TRACE_DEBUG(( "Inside GTW userMsgHandler : %d %d %s", 
                       ev.GetSource(), ev.GetLength(), ev.GetData() )); 
    if ( TCAP_MSG_TYPE ( &ev.GetEvent() ) == ITS_TCAP_DLG )
    {
       APP_TRACE_DEBUG(( "Received TCAP Dialogue" ));
       int res = TCAP_Dialogue::Receive ( handle, ev, &dlg );
       if ( res != ITS_SUCCESS )
       {
          APP_TRACE_DEBUG(( "Received Dialogue Failed" ));
          ITS_THROW_ERROR(res);
       }
       // Must be a begin. 
       if (dlg->GetDialogueType() == TCPPT_TC_BEGIN)
       {
          APP_TRACE_DEBUG(( "TCAP Begin Received" ));
          TCAP_Begin* beginDlg = static_cast<TCAP_Begin*>( dlg );
          
       }
       else if ( dlg->GetDialogueType() == TCPPT_TC_CONTINUE )
       {
          APP_TRACE_DEBUG(( "TCAP Continue Received" ));
          TCAP_Continue* ContinueDlg = static_cast<TCAP_Continue*>( dlg );

          // Get the component.
          res = worker->GetNextEvent( event );
          if ( res != ITS_SUCCESS )
          {
             APP_TRACE_DEBUG(( "TCAP Continue Received" ));
             ITS_THROW_ERROR(res);
          }

         // Must be a component.
         if ( TCAP_MSG_TYPE((&event.GetEvent())) == ITS_TCAP_CPT )
         {
            APP_TRACE_DEBUG(("TCAP Component " ));
            res = TCAP_Component::Receive(handle, event, dlg, &cpt);
            if ( res != ITS_SUCCESS )
            {
                  APP_TRACE_ERROR (( "Component Receive Failed " ));
                  ITS_THROW_ERROR ( res );
            }
            // Must be an invoke. 
            if (cpt->GetComponentType() == TCPPT_TC_INVOKE)
            {
               TCAP_Invoke* invokeCpt = static_cast<TCAP_Invoke*>(cpt);
               APP_TRACE_DEBUG(("Received TCAP Invoke " ));
               // Retrieve the operation.
               ITS_ASSERT(invokeCpt != NULL);
               ITS_ASSERT(ContinueDlg != NULL);
               ITS_USHORT dlgId = ContinueDlg->GetDialogueID();
               ITS_OCTET invokeId = invokeCpt->GetInvokeID(); 
               ITS_LONG operation = 0;
               invokeCpt->GetOperation(operation);
               // Selection according to CAMEL operation.

               switch ( operation )
               {
                   case OP_playAnnouncement:
                   {
                        vector<byte> encodedPlayAnnouncement;
                        // The parameter field of the TCAP invoke component
                        // contains the CAMEL PlayAnnouncement operation argument.
                       invokeCpt->GetParameter(encodedPlayAnnouncement);
                       //  Function call uses CAMEL ASN.1 C++ API.
                       //
                       InterpretOperationPlayAnnouncement 
                          ( 
                          encodedPlayAnnouncement, dlgId 
                          );
                        SpecializedResourceReportArg *specializedResourceReportArg = 
                            new SpecializedResourceReportArg();
                       
                         Octets* octets = NULL;
                         octets = specializedResourceReportArg->Encode();


                        vector<byte> encodedSpecializedResourceReportArg = 
                            octets->GetArray();  
                       

                       	TCAP_Invoke invokeCpt;
			invokeCpt.SetInvokeID(invokeId);
			invokeCpt.SetOperation(OP_specializedResourceReport); 
			invokeCpt.SetClass(2);
			invokeCpt.SetParameter(encodedSpecializedResourceReportArg);
                        TCAP_End endDlg; 
                        endDlg.SetDialogueID(dlgId);
                       	TCAP_Component::Send(handle, &endDlg, &invokeCpt);
			TCAP_Dialogue::Send(handle, &endDlg); 
                        break;
                   }
                   case OP_promptAndCollectUserInformation:
                   {
                       vector<byte> encodedpromptAndCollectUserInformation;
                       // The parameter field of the TCAP invoke component
                       // contains the CAMEL P&CUI operation
                       // argument.
                       invokeCpt->GetParameter
                          (
                          encodedpromptAndCollectUserInformation
                          );

                       //
                       //  Function call uses CAMEL ASN.1 C++ API.
                       //
                       InterpretOperationPromptAndCollectUserInformationArg 
                           ( 
                           encodedpromptAndCollectUserInformation, dlgId
                           );

                         ReceivedInformationArg *receivedInformationArg = 
                                           new ReceivedInformationArg(); 

                         byte fixedArray12[] = {0x01U, 0x02U}; 

                       Digits* digitsResponse = 
                           new Digits(FixedByteArrayToVector(fixedArray12));
                         

                       receivedInformationArg->SetChoiceDigitsResponse(digitsResponse);
                       Octets* octets = NULL;

                       try
                       {
                          //  Can throw and AsnEncodeError execption. 

                          octets = receivedInformationArg->Encode();
                       }
                       catch (AsnEncodeError& encodeError)
                       {
                          APP_TRACE_DEBUG(("%s", 
                              encodeError.GetDescription().c_str() ));

                          //More specific error processing should be added here.

                          //By default re-throw exception.

                          throw encodeError;
                       }


                       vector<byte> encodedReceivedInformationArg = 
                           octets->GetArray(); 

                       TCAP_Invoke invokeCpt;
                       invokeCpt.SetInvokeID(invokeId);
                       invokeCpt.SetOperation(OP_receivedInformation);
                       invokeCpt.SetClass(2);
                       invokeCpt.SetParameter(encodedReceivedInformationArg);
                                   
                       TCAP_End endDlg;
                       endDlg.SetDialogueID(dlgId);
                       TCAP_Component::Send(handle, &endDlg, &invokeCpt);
                       TCAP_Dialogue::Send(handle, &endDlg);   
                       break;
                  }
                  default:
                  {
                       APP_TRACE_DEBUG(("operation code: %d", operation ));
                  }
               } // Switch.
            }
            else // Not an Invoke
            {
                 APP_TRACE_WARNING(("Received Componenet Not Invoke" ));
                 APP_TRACE_WARNING(("Not a valid TCAP Invoke Operation" ));
            }               
          }
          else // Not a Component
          {
             APP_TRACE_WARNING(("Did not Receive A Component" ));
             APP_TRACE_WARNING(("Response/Reject to a timed out Dialogue ?" ));
           }
       }
       APP_TRACE_DEBUG(("Continue Dialogue  Message Received" ));
       //stop=true; 
    }
    return (ITS_SUCCESS);
			
}
          
/////////////////////////////////////////////////////////////////////
//
// XMLRead Function
//
// Parse XML Message and Send The TCAP Begin
//
/////////////////////////////////////////////////////////////////////

void
XMLread ( char *buf, int mlenght )
{
    char DPC[TmpSize]="  ";
    char TranID[TmpSize]="         ";
    char OC[TmpSize]="          "; 
    char temp[TmpSize]="  ";
    char XMLmessage[MaxSize];

    sscanf ( buf, "%[^'<TranI']",temp );

    APP_TRACE_DEBUG(( "Message lenght: %d", mlenght ));
    bool TranIDdone = false;
    bool DPCdone = false;
    bool OCdone = false;
    int i = 8;
    int j = 0;

    // Read the Transaction ID from the XML Message

    if ( !TranIDdone )
	while ( buf[i]!='<' )
	{
	    TranID[j]=buf[i];
	    j++;
	    i++;
	    TranIDdone = true;
	}
	// Read the Destination Point Code from the XML Message
	if (!DPCdone)
	{
	    while ( buf[i]!='C' ) i++;
	        i++;
	        i++;
	        j=0;
	    while ( buf[i]!='<' )
	    {
	        DPC[j]=buf[i];
	        j++;
	        i++;
		DPCdone = true;
	    }
	    j=0;
	}
	i++;

        // read the Operation Code (they are all included in cap_v2_cpp.h)
        if (!OCdone)
        {
            while ( buf[i]!='C') i++;
                  i++;
            while ( buf[i]!='C') i++;
                  i++;
                  i++;
                  j=0;
            while ( buf[i]!='<' )
            {
                OC[j]=buf[i];
                j++;
                i++;
                OCdone = true;
            }
            j=0;
         }
         i++; 

	// Read the CAMEL Message
	while ( buf[i]!='<' ) i++;
	    while ( i<= mlenght +51 )
	    {
		XMLmessage[j]=buf[i];
		i++;
		j++;
	    }

            XMLmessage[j]='\0';
            ITS_USHORT IVRdid=atoi(TranID);

            APP_TRACE_DEBUG(( "Transaction ID: %d", atoi( TranID ) ));
            APP_TRACE_DEBUG(( "DPC: %d", atoi( DPC ) ));
            APP_TRACE_DEBUG(( "Operation Code: %d", atoi(OC) ));
            APP_TRACE_DEBUG(( "XML Message: %s", XMLmessage ));

        //Send TCAP Dialogue

        TCAP_Begin beginDlg;
        ITS_USHORT dialogueID;
        SCCP_CallingPartyAddr origAddr;
        SCCP_CalledPartyAddr  destAddr;

        //Allocate the Dialogue ID from the stack 
        TCAP_AllocateDialogueId ( &dialogueID );

        //Insert entry in correlation table
        table.InsertEntry ( dialogueID, IVRdid );

        // set ID in the TCAP dialogue
        beginDlg.SetDialogueID ( dialogueID );

        //Set Orig Addr
        origAddr.SetSSN ( LOCAL_SSN );
        origAddr.SetPointCode ( LOCAL_PC );
        ITS_OCTET addressIndicator = SCCP_CPA_HAS_SSN | 
        SCCP_CPA_HAS_PC | SCCP_CPA_ROUTE_NAT;
        origAddr.SetRouteByPCSSN ( true );       
        beginDlg.SetOPC ( LOCAL_PC );
        beginDlg.SetOrigAddr ( origAddr );   
	
        //Set Dest Addr
        destAddr.SetSSN ( REMOTE_SSN );
        destAddr.SetPointCode ( atoi ( DPC ) );
        addressIndicator = SCCP_CPA_HAS_SSN | SCCP_CPA_HAS_PC | 
        SCCP_CPA_ROUTE_NAT;
        destAddr.SetRouteByPCSSN ( true );         
        beginDlg.SetDPC ( atoi ( DPC ) );
        beginDlg.SetDestAddr(destAddr); 
    
        TCAP_Invoke invokeCpt;
        int op = 1;
        invokeCpt.SetInvokeID ( 1 ); 
    
        invokeCpt.SetOperation(atoi(OC));
        invokeCpt.SetClass(2);
        invokeCpt.SetTimeOut(100);
        vector<byte> encodedInsertSubscriberDataArg;
        encodedInsertSubscriberDataArg = 
        BuildOperationAssistRequestInstructionArg ( XMLmessage );
        invokeCpt.SetParameter(encodedInsertSubscriberDataArg);

        TIMERS_Sleep(3);
        TCAP_Component::Send(NULL, &beginDlg, &invokeCpt);
        TCAP_Dialogue::Send(NULL, &beginDlg);

        APP_TRACE_DEBUG(( "TCAP BEGIN SENT " ));
        //END Send TCAP Dialogue

        APP_TRACE_DEBUG(( "TcapThreadFunction " ));
}

///////////////////////////////////////////////////////////////////////
// This function defines the socket writing.
// this writing will be used for communications with the IVR
// following the XML format (XER).
///////////////////////////////////////////////////////////////////////

static int
IVR_Write ( ITS_HANDLE handle, ITS_EVENT *ev )
{
    SOCKTRAN_Manager *ft = ( SOCKTRAN_Manager *)handle;
    ITS_C_REQUIRE(handle != NULL);
    ITS_C_REQUIRE(ev != NULL);
    int ret;
    /* synchronize the stream */

    ret = SOCK_Write ( SOCKTRAN_SOURCE ( ft ), sync_data, 
                       strlen ( sync_data ) );

    if ( ret !=  ( int)strlen ( sync_data ) )
    {
        APP_TRACE_DEBUG(( "cannot write to socket " ));
        return ( ITS_ESENDFAIL );
    }

    int sw;
    APP_TRACE_DEBUG(( "Writing to IVR " ));
 
    /* Write the data */
    if ( ev->len )
    {
        sw = SOCK_Write ( SOCKTRAN_SOURCE ( ft ), 
                          (char *)ev->data, ev->len );

        if ( sw != (int)ev->len )
        {
            return ( ITS_ESENDFAIL );
        }
    }
          
    APP_TRACE_DEBUG(( "bytes written %d", sw ));
    if ( sw <= 0 )
    {
       APP_TRACE_ERROR(( "can't write to socket" ));
     
    }
    return (ITS_SUCCESS);
}

///////////////////////////////////////////////////////////////////////
// This function defines the socket reading.
// this reading will be used for communications with the IVR
// following the XML format (XER).
///////////////////////////////////////////////////////////////////////

static int
IVR_Read ( ITS_HANDLE handle, ITS_EVENT *ev )
{
    int i;
    SOCKTRAN_Manager *ft;
    int recvBufLen, sr,ret;
    char *recvBuf;
    char *c;
    recvBuf = new char[MaxSize];
    c = new char[TmpSize];
    char b;
    ft =  (SOCKTRAN_Manager *)handle;
    strcpy(c, "\0");
    strcpy(recvBuf, "\0");
    unsigned  dosCount;

    /* synchronize the stream */
    for ( i = 0, dosCount = 0; i < strlen ( sync_data ) 
              && dosCount < ITS_MAX_EVENT_SIZE;
              i++, dosCount++ )
    {
        ret = SOCK_Read ( SOCKTRAN_SOURCE ( ft ), &b, sizeof(char) );

        if ( ret != sizeof(char) )
        {
            return ( ITS_ERCVFAIL );
        }

        if ( b != sync_data[i] )
        {
            i = ~0U;
            continue;
        }
    }

    //read sync data
    sr = SOCK_Read ( SOCKTRAN_SOURCE ( ft ), c, 6 );
			
    //read lenght	
    sr = SOCK_Read ( SOCKTRAN_SOURCE ( ft ), c, 6 );
       if ( sr <= 0 )
       {
          APP_TRACE_ERROR(( "can't read socket" ));
       }
       else
       {
          APP_TRACE_DEBUG(( "bytes read %d", sr ));
       }
       recvBufLen = atoi(c);
       ev->len=recvBufLen;

       ev->data = ( ITS_OCTET * )ITS_Malloc ( ev->len+1 );

			
       //read data
       sr = SOCK_Read(SOCKTRAN_SOURCE(ft), (char *)ev->data, ev->len+1);


       if ( sr <= 0 )
       {
          APP_TRACE_ERROR(( "ERROR: can't read socket" ));
       }
       else
       {
           APP_TRACE_DEBUG(( "bytes read %d ", sr ));
       } 
       delete recvBuf;
       delete c;
       return (ITS_SUCCESS);

}

////////////////////////////////////////////////////////////////
//
//IVR Post initialize function
//Redefine the pointers to read and write functions for sockets.
////////////////////////////////////////////////////////////////

extern "C" EXPORT int
IVR_PostInit ( its::ITS_ThreadPoolThread* thr, ITS_HANDLE handle )
{
    SOCKTRAN_READ_EVENT(handle) = IVR_Read;
    SOCKTRAN_WRITE_EVENT(handle) = IVR_Write;
    APP_TRACE_DEBUG(( "Inside IVR Post Init  please wait initializing...." ));
    //Find IVR Transport
    ITS_Worker* worker = static_cast<ITS_Worker*> (thr);
    IVRTransportInst = worker->GetInstance();

/*
 static bool IVRTransportInstFound = false;
  if (!IVRTransportInstFound)
  {
       IVRTransportInstFound =true;
       for (unsigned short l=0;l<32000;l++)
           {
           TRANSPORT_Control *tc= TRANSPORT_FindTransport(l);
           if (tc != NULL && strcmp(tc->transport.name,"IVR")==0)
           {
              APP_TRACE_DEBUG(( "FOUND IVR TRANSPORT : %d", l ));
              IVRTransportInst=l;
              break;
           }
           }
        }*/
    return (ITS_SUCCESS);
}


//////////////////////////////////////////////////////////////////
//
//IVR User Message Handler
//
//////////////////////////////////////////////////////////////////

extern "C" EXPORT int
IVR_UserMsgHandler ( its::ITS_ThreadPoolThread* thr, Event& ev )
{
    APP_TRACE_DEBUG(( "Inside IVR_UserMsgHandler :" ));
    fflush ( stdout );
    ITS_EVENT event = ev.GetEvent();
    event.data[event.len]='\0';
    XMLread ((char * )event.data,event.len );//parse XML message
    return ITS_SUCCESS; 
}

//////////////////////////////////////////////////////////////////
//
//  Receive TCAP dialogue function.
//
//  This function is not used
//  but kept in the code for testing purposes
//  will be removed at the end
//
//////////////////////////////////////////////////////////////////
void ReceiveTcapDlgComp_ITU ( ITS_HANDLE handle, 
                              ITS_Worker *worker, ITS_Event *ev )
{
    ITS_Event event;
    TCAP_Dialogue* dlg  = NULL;
    TCAP_Component* cpt = NULL;
    if (TCAP_MSG_TYPE((&ev->GetEvent())) == ITS_TCAP_DLG)
    {
        APP_TRACE_DEBUG(( "Received TCAP Dialogue " ));
        int res = TCAP_Dialogue::Receive(handle, *ev, &dlg);
        if (res != ITS_SUCCESS)
        {
            APP_TRACE_ERROR(( "Receive Dialogue Failed " ));
            ITS_THROW_ERROR(res);
        }
        // Must be a begin. 
        if (dlg->GetDialogueType() == TCPPT_TC_BEGIN)
        {
            APP_TRACE_DEBUG(( "TCAP Begin Received " ));
            TCAP_Begin* beginDlg = static_cast<TCAP_Begin*>(dlg);
            // Get the component.
            res = worker->GetNextEvent(event);
            if ( res != ITS_SUCCESS )
            {
                APP_TRACE_ERROR(( "GetNextEvent Failed " ));
                ITS_THROW_ERROR ( res );
            }
            // Must be a component.
            if ( TCAP_MSG_TYPE ( ( &event.GetEvent() ) ) == ITS_TCAP_CPT )
            {
                APP_TRACE_DEBUG(( "TCAP Component " ));
                res = TCAP_Component::Receive(handle, event, dlg, &cpt);
                if ( res != ITS_SUCCESS )
                {
                   APP_TRACE_ERROR(( "Component Receive Failed " ));
                   ITS_THROW_ERROR(res);
                }
                // Must be an invoke. 
                if ( cpt->GetComponentType() == TCPPT_TC_INVOKE )
                {
                   TCAP_Invoke* invokeCpt = static_cast<TCAP_Invoke*>(cpt);
                   APP_TRACE_DEBUG(( "Received TCAP Invoke " ));
                   // Retrieve the operation.
                   ITS_ASSERT(invokeCpt != NULL);
                   ITS_ASSERT(beginDlg != NULL);
                   ITS_USHORT dlgId = beginDlg->GetDialogueID();
                   ITS_OCTET invokeId = invokeCpt->GetInvokeID(); 
                   
                   // Dispatch to procedure according to operation.                        
              }
              else // Not an Invoke
              {
                  APP_TRACE_ERROR(( "Received Componenet Not Invoke " ));
                  APP_TRACE_ERROR(( "Not a valid TCAP Invoke Operation " ));
              }               
           }
           else // Not a Component
           {
               APP_TRACE_ERROR(( "Did not Receive A Component " ));
               APP_TRACE_ERROR(( "Response/Reject to a timed out Dialogue ? " ));
           }
        }
        else if (dlg->GetDialogueType() == TCPPT_TC_END)
        {
           APP_TRACE_DEBUG(( "TCAP End Received " ));
           TCAP_End* EndDlg = static_cast<TCAP_End*>(dlg);

           // Get the component.
           res = worker->GetNextEvent(event);
           if (res != ITS_SUCCESS)
           {
              APP_TRACE_ERROR(( "GetNextEvent Failed " ));
              ITS_THROW_ERROR(res);
           }
           // Must be a component.
           if ( TCAP_MSG_TYPE (( &event.GetEvent() ) ) == ITS_TCAP_CPT )
           {
               APP_TRACE_DEBUG(( "TCAP Component " ));
               res = TCAP_Component::Receive ( handle, event, dlg, &cpt );
               if ( res != ITS_SUCCESS )
               {
                  APP_TRACE_ERROR (( "Component Receive Failed " ));
                  ITS_THROW_ERROR ( res );
               }
               // Must be an invoke. 
               if ( cpt->GetComponentType() == TCPPT_TC_INVOKE )
               {
                  TCAP_Invoke* invokeCpt = static_cast<TCAP_Invoke*>(cpt);
                  APP_TRACE_DEBUG(( "Received TCAP Invoke " ));
                  // Retrieve the operation.
                  ITS_ASSERT(invokeCpt != NULL);
                  ITS_ASSERT(EndDlg != NULL);
                  ITS_USHORT dlgId = EndDlg->GetDialogueID();
                  ITS_OCTET invokeId = invokeCpt->GetInvokeID(); 
                  ITS_LONG operation = 0;
                  invokeCpt->GetOperation(operation);
                  // Selection according to GSM MAP operation.

                  switch ( operation )
                  {
                      case OP_playAnnouncement:
                      {
                          vector<byte> encodedPlayAnnouncement;
                          // The parameter field of the TCAP invoke component
                          // contains the CAMEL PlayAnnouncement operation 
                          // argument.
                          invokeCpt->GetParameter(encodedPlayAnnouncement);
                          //  Function call uses CAMEL ASN.1 C++ API.
                          InterpretOperationPlayAnnouncement
                              ( encodedPlayAnnouncement,dlgId );

                          break;
                      }
                      case OP_promptAndCollectUserInformation:
                      {
                      vector<byte> encodedpromptAndCollectUserInformation;
                      // The parameter field of the TCAP invoke component
                      // contains the GSM MAP Insert Subscriber Data 
                      // operation argument.
                      invokeCpt->GetParameter 
                          ( encodedpromptAndCollectUserInformation );

                      //  Function call uses GSM MAP ASN.1 C++ API.
                      //
                      InterpretOperationPromptAndCollectUserInformationArg
                          ( encodedpromptAndCollectUserInformation,dlgId );
                      break;
                      }
                      default:
                      {
                          APP_TRACE_DEBUG(( "operation code: %d", operation  ));
                      }
                } // Switch.
             }
             else // Not an Invoke
             {
                 APP_TRACE_ERROR(( "Received Componenet Not Invoke " ));
                 APP_TRACE_ERROR(( "Not a valid TCAP Invoke Operation " ));
             }               
            }
         else // Not a Component
         {
             APP_TRACE_ERROR(( "Did not Receive A Component" ));
             APP_TRACE_ERROR(( "Response/Reject to a timed out Dialogue ?" ));
         }
      }
      APP_TRACE_DEBUG(( "End Dialogue  Message Received" ));
      //stop=true; 
  }
  else // Not a Query With Permission
  {
      APP_TRACE_ERROR(( "Received Dialogue Not Begin\nExpected a TCAP_Begin" ));
      APP_TRACE_ERROR(( "Response/Reject to a timed out Dialogue ?" ));
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
//  o   Insert data step by step in the created 
//      AssistRequestInstructionArg object 
//      (i.e. populate various parameters of the AssistRequestInstruction 
//      operation argument).
//  
//  o   Encode the AssistRequestInstructionArg object to produce an 
//      AssistRequestInstructionArg encoded value.
//
    
vector<byte>
BuildOperationAssistRequestInstructionArg ( char *XMLmessage )
{
    Characters* characters = new Characters ( XMLmessage );

    AssistRequestInstructionsArg *assistRequestInstructionArg =
       new AssistRequestInstructionsArg();
    // Set Parameters
    APP_TRACE_DEBUG(( "Setting AssistRequestInstruction Parameters:" ));
 
    try
    {
        assistRequestInstructionArg->DecodeFromXml(*characters);
    }
    catch(AsnCharactersDecodeError& charactersDecodeError)
    {
        APP_TRACE_ERROR(( "%s", charactersDecodeError.GetDescription().c_str() ));
    }

    // Extensions, not set
    Octets* octets = NULL;
    octets = assistRequestInstructionArg->Encode();
    ostrstream oss;
    octets->Print(oss);
    oss << '\0';
    APP_TRACE_DEBUG(( "Printing assistRequestInstructionArg ASN.1 encoded value" ));
    APP_TRACE_DEBUG(( "%s", oss.str() ));
    oss.freeze( false );

////////////////////////////////////////////////////////////////////////////

//  [11] Retrieve AssistRequestInstructionArg ASN.1 encoded value from octets 
//  object.

    vector<byte> encodedAssistRequestInstructionArg = octets->GetArray();

////////////////////////////////////////////////////////////////////////////

//  [12] Free all memory allocated on the heap.
//  [12-1] Delete assistRequestInstructionArg object (and therefore all the 
//  parameter objects that have been previously set).

    delete assistRequestInstructionArg;

//  [12-2] Delete Octets object created by the call to Encode.

    delete octets;

////////////////////////////////////////////////////////////////////////////

//  [13] Return (by value) encodedAssistRequestInstructionArg ASN.1 encoded value.

    return encodedAssistRequestInstructionArg;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//  Initialization of the different messages parameters 
//  for AssistRequestInstructionArg.
//
////////////////////////////////////////////////////////////////////////////////


CorrelationID* InitializeCorrelationID()
{
    byte array[] = { 0x02, 0x03, 0x04, 0x05, 0x06 };
    CorrelationID* cid = new CorrelationID ( FixedByteArrayToVector ( array ) );
    return cid;
}             

IPSSPCapabilities* InitializeIPSSPCapabilities()
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
//  How to interpret an (encoded) CAMEL PlayAnnouncementArg
//  argument (PlayAnnouncementArg):
//
//  o   Decode a PlayAnnouncementArg encoded value (i.e. create a
//      PlayAnnouncementArg object from a PlayAnnouncementArg encoded
//      value).
//
//  o   Retrieve Data from a PlayAnnouncementArg object.
//

void InterpretOperationPlayAnnouncement
     ( 
     const vector<byte>& encodedPlayAnnouncementArg, 
     ITS_USHORT dlgID
     )
{
//  [1] Create an Octets object from the PromptAndCollectUserInformationArg 
//  ASN.1  encoded value.

    Octets* octets = new Octets ( encodedPlayAnnouncementArg );

////////////////////////////////////////////////////////////////////////////

//  [2] Create a InsertSubscriberDataArg object ( used by the decode phase ).

    PlayAnnouncementArg* playAnnouncementArg = new PlayAnnouncementArg();

////////////////////////////////////////////////////////////////////////////

//  [3] Decode the PlayAnnouncementArg ASN.1 encoded value and therefore
//  populate previously created PlayAnnouncementArg object.

    playAnnouncementArg->Decode(*octets);
    APP_TRACE_DEBUG(( "Printing decoded PlayAnnouncementArg object..." ));
    ostrstream oss;
    playAnnouncementArg->Print(oss);
    oss << '\0';
    APP_TRACE_DEBUG(( "%s", oss.str() ));
    oss.freeze(false);
    Characters* characters = NULL;
    AsnOptions asnOptions;
    asnOptions.SetEncodeXmlWithoutSeparators();
    try
    {
        characters = playAnnouncementArg->EncodeToXml(asnOptions);
    }
    catch ( AsnEncodeError& encodeError )
    {
        APP_TRACE_DEBUG(( "%s", encodeError.GetDescription().c_str() ));
    }
    char tmp[TableSize];
    ITS_USHORT TranID;
    int sz;
    sz = HeaderSize + characters->GetSize(); 
    TranID=table.RetrieveEntry ( ( ITS_USHORT )dlgID );
    sprintf ( tmp,"@@@@@@%.6d<TranID>%d</TranID><DPC>9999</DPC><OC>47</OC>%s", sz,
    TranID, characters->GetString().c_str() );
    APP_TRACE_DEBUG(( "Result Returned to IVR: %s", tmp  ));
    ITS_Event event(1,sz+13,(ITS_OCTET*)tmp);
    its::Transport::PutEvent(IVRTransportInst,event);


////////////////////////////////////////////////////////////////////////////

//  [10] Free all memory allocated on the heap.

//  [10-1] Delete Octets object.

    delete octets;

//  [10-2] Delete PlayAnnouncementArg object.

    delete playAnnouncementArg;
}

void InterpretOperationPromptAndCollectUserInformationArg
     ( 
     const vector<byte>& encodedPromptAndCollectUserInformationArg,
    ITS_USHORT dlgID 
     )
{
//  [1] Create an Octets object from the PromptAndCollectUserInformationArg 
//  ASN.1  encoded value.

    Octets* octets = new Octets(encodedPromptAndCollectUserInformationArg);

////////////////////////////////////////////////////////////////////////////

//  [2] Create a InsertSubscriberDataArg object (used by the decode phase).

    PromptAndCollectUserInformationArg* promptAndCollectUserInformationArg = 
        new PromptAndCollectUserInformationArg ();

////////////////////////////////////////////////////////////////////////////

//  [3] Decode the PromptAndCollectUserInformationArg ASN.1 encoded value 
//  and therefore populate previously created 
//  PromptAndCollectUserInformationArg object.


    promptAndCollectUserInformationArg->Decode ( *octets );
    ostrstream oss;
    promptAndCollectUserInformationArg->Print(oss);
    oss << '\0';
    APP_TRACE_DEBUG(( "Printing decoded PromptAndCollectUserInformationArg object..." ));
    APP_TRACE_DEBUG(( "%s", oss.str() ));
    oss.freeze(false);

////////////////////////////////////////////////////////////////////////////
 Characters* characters = NULL;
    AsnOptions asnOptions;
    asnOptions.SetEncodeXmlWithoutSeparators();
    try
    {
        characters = promptAndCollectUserInformationArg->EncodeToXml(asnOptions);
    }
    catch ( AsnEncodeError& encodeError )
    {
        APP_TRACE_ERROR(( "%s", encodeError.GetDescription().c_str() ));
    }
    char tmp[TableSize];
    ITS_USHORT TranID;
    int sz;
    sz = HeaderSize + characters->GetSize();
    TranID=table.RetrieveEntry ( ( ITS_USHORT )dlgID );
    sprintf ( tmp,"@@@@@@%.6d<TranID>%d</TranID><DPC>9999</DPC><OC>48</OC>%s", 
              sz,TranID, characters->GetString().c_str() ); 
    APP_TRACE_DEBUG(( "Result Returned to IVR: %s", tmp ));
    ITS_Event event(1,sz+13,(ITS_OCTET*)tmp);
    its::Transport::PutEvent(IVRTransportInst,event);          

//  [10] Free all memory allocated on the heap.

//  [10-1] Delete Octets object.

    delete octets;

//  [10-2] Delete PromptAndCollectUserInformationArg object.

    delete promptAndCollectUserInformationArg;
}


