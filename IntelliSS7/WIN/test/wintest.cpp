////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 1998 IntelliNet Technologies, Inc. All Rights Reserved.     //
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
// CONTRACT: internal                                                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
//  ID: $Id: wintest.cpp,v 9.1 2005/03/23 12:52:46 cvsadmin Exp $
//
////////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32
#pragma warning (disable : 4786)
#endif

#include <string>
#include <iostream>
#include <stdio.h>

// IntelliSS7 headers

#include <its++.h>
#include <its_app.h>
#include <its_thread.h>
//#include <its_gdi_stubs.h>

#include <its_timers.h>
#include <its_route.h>
#include <its_transports.h>
#include <its_worker.h>
#include <its_exception.h>
#include <its_timers.h>
#include <its_tq_trans.h>
//#include <its_stubs.h>
#include <its_ss7_stubs.h>

#include <its_ss7_trans.h>


// ASN CPP headers

#include <asn-cpp/AsnObject.h>
#include <AsnSequence.h>
#include <AsnException.h>
#include <Octets.h>

//
// Protocol headers
//
#if defined(ANSI)
#include <mtp3++.h>
#include <sccp++.h>
#include <tcap++.h>
#include <win_cpp.h>
#include <win_feature_request_il.h>
#include <win_feature_request_rrl.h>
#include <win_service_request_il.h>
#include <win_service_request_rrl.h>
#include <win_analyzed_information_il.h>
#include <win_analyzed_information_rrl.h>
#include <win_trigger_type.h>
#include <win_connection_failure_report_il.h>
#include <win_connect_resource_il.h>
#include <win_facility_selected_and_available_il.h>
#include <win_facility_selected_and_available_rrl.h>
#include <win_seize_resource_il.h>
#include <win_seize_resource_rrl.h>
#include <win_srf_directive_il.h>
#include <win_srf_directive_rrl.h>
#include <win_tbusy_il.h>
#include <win_t_busy_rrl.h>
#include <win_t_no_answer_il.h>
#include <win_t_no_answer_rrl.h>

#endif

#include "wincpptest.h"
#include "win_trace.h"

#if defined(ITS_NAMESPACE)
using namespace std;
using namespace its;
using namespace win;
#endif


/*.implementation:protected
 ****************************************************************************
 *  Purpose:
 *      To display the options to send a WIN message 
 *
 *  Input Parameters:
 *      dlg - pointer to a TCAP_Dialogue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
void
DisplayMenu()
{
    cout << endl;
    cout << "Select Operation to Send" << endl;
    cout << "--------------------------------------" << endl;
    cout << "[0]   Exit " << endl;
    cout << "[1*]  FeatureReq InvokeLast" << endl;
    cout << "[2*]  FeatureReq ReturnResultLast" << endl;
	cout << "[3$]  ServiceReq InvokeLast" << endl;
    cout << "[4$]  ServiceReq ReturnResultLast" << endl;
	cout << "[5*]  AnalyzedInfo InvokeLast" << endl;
    cout << "[6*]  AnalyzedInfo ReturnResultLast" << endl;
	cout << "[7#]  ConnectionFailureRep InvokeLast" << endl;
    cout << "[8&]  ConnectResource InvokeLast" << endl;
    cout << "[9*]  FailitySelected InvokeLast" << endl;
    cout << "[10*] FailitySelected ReturnResultLast" << endl;
    cout << "[11%] SeizeResource InvokeLast" << endl;
    cout << "[12%] SeizeResource ReturnResultLast" << endl;
    cout << "[13$] SRFDirective InvokeLast" << endl;
    cout << "[14$] SRFDirective ReturnResultLast" << endl;
	cout << "[15*] TBusy InvokeLast" << endl;
    cout << "[16*] TBusy ReturnResultLast" << endl;
	cout << "[17$] TNoAnswer InvokeLast" << endl;
    cout << "[18$] TNoAnswer ReturnResultLast" << endl;
    cout << "[19]  Error Component" << endl;
    cout << "[20]  Reject Component" << endl;
    cout << endl;
    cout << "->> ";
}


/*.implementation:protected
 ****************************************************************************
 *  Purpose:
 *      To send a a message to the mtp3 layer.
 *
 *  Input Parameters:
 *      dlg - pointer to a TCAP_Dialogue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/

THREAD_RET_TYPE
RecvMTP3Func(void *arg)
{
    int i = 0, ret = ITS_SUCCESS;
    bool keepGoing = true;
    ITS_Event ev;

    printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
    cout << "Wait for MTP3 event." << endl;
    
    while ( keepGoing ) 
    {
        if (trout->GetNextEvent(ev) != ITS_SUCCESS)
        {
            cout << "Failed to get MTP3 event." << endl;
            continue;
        }
        else
        {
            cout << "Event source: ";
            switch ( ev.GetSource() )
            {
            case ITS_MTP3_SRC:
                printf("MTP3");
                break;
            case ITS_SCCP_SRC:
                printf("SCCP");
                break;
            case ITS_TCAP_SRC:
                printf("TCAP");
                break;
            }
            cout << ", " << ev.GetSource() << endl;
            cout << "Length:  " << ev.GetLength() << endl;

            for (int i = 0; i < ev.GetLength(); i++)
            {
                printf("%02x ", ev.GetData()[i]);
                if (!((i+1) % 25))
                {
                    printf("\n");
                }
            }

            if ((i+1) % 25)
            {
                printf("\n");
            }

            cout << "Sending to SCCP..." << endl;
            ev.SetSource( ITS_MTP3_SRC ); 

            ret = ITS_Transport::PutEvent(ITS_SCCP_SRC, ev);
            if (ret != ITS_SUCCESS)
            {
                printf("[WMM IS41 Test]: %s: line %d\n", __FILE__,
                       __LINE__);
                printf("Fail to put MTP3 event.\n");
                fflush(stdout);
            }
            else
            {
                printf("Put OK...\n");
                fflush(stdout);
            }
        }
    }

    return (0);
}

/*.implementation:protected
 ****************************************************************************
 *  Purpose:
 *      To send a LocationRequest invoke last using the WIN library.
 *
 *  Input Parameters:
 *      dlg - pointer to a TCAP_Dialogue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
THREAD_RET_TYPE
RecvTCAPFunc(void *arg)
{
    int ret = ITS_SUCCESS;
    bool keepGoing = true;
    bool national = false;
    ITS_OCTET family = 0x00, op = 0x00;
    Octets* octets = NULL;
    ITS_Event ev;
    ITS_ByteArray buf;


    while ( keepGoing ) 
    {
        // Get TCAP event
        printf("[WMM IS41 Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Wait for TCAP event." << endl;

        DisplayMenu();

        if (trin->GetNextEvent(ev) != ITS_SUCCESS)
        {
            cout << "TCAP GetNextEvent() failed." << endl;
            continue;
        }
        else
        {
            if (TCAP_MSG_TYPE(&ev.GetEvent()) == ITS_TCAP_CPT)
            {
                ret = TCAP_Component::Receive((ITS_HANDLE)trin->GetTransport(),
                                              ev, dlg, &cpt);

				cout << "DID is" << dlg->GetDialogueID() << endl;

                if (ret == ITS_SUCCESS)
                {
                    traceComponent( cpt );

                    // Determine what kind of component was received
                    switch (cpt->GetComponentType())
                    {
                    case TCPPT_TC_INVOKE:
                    case TCPPT_TC_INVOKE_NL:
                        printf("[WIN Test]: %s: line %d\n",
                               __FILE__, __LINE__);
                        printf("Received invoke component.\n");

                        ((TCAP_Invoke *)cpt)->GetOperation(national,
                                                           family,
                                                           op);
                        ((TCAP_Invoke *)cpt)->GetParameter(buf);

                        printf("Creating octets from parameter.\n");
                        octets = new Octets(buf);
										

                        // Decode parameter of invoke component
                        printf("Decoding WIN message.\n");
                         
						
				    switch (op)
					{
						case OP_FeatureRequest:
						{
						FeatureRequestIL fril;
                        DecodeMsg(&fril, octets);						
                        }
					    break;

						case OP_ServiceRequest:
						{
							ServiceRequestIL sril;
							DecodeMsg(&sril, octets);
						}
						break;
					 
						case OP_AnalyzedInformation:
						{
							AnalyzedInformationIL aiil;
                            DecodeMsg(&aiil, octets);
						}
						break;

						case OP_ConnectionFailureReport:
                        {
							ConnectionFailureReportIL cfril;
                            DecodeMsg(&cfril, octets);
						}
						break;

						case OP_ConnectResource:
                        {
							ConnectResourceIL cril;
                            DecodeMsg(&cril, octets);
						}
						break;

						case OP_FacilitySelectedAndAvailable:
                        {
							FacilitySelectedAndAvailableIL fsaail;
                            DecodeMsg(&fsaail, octets);
						}
						break;

						case OP_SeizeResource:
						{
							SeizeResourceIL sreil;
                            DecodeMsg(&sreil, octets);
						}
						break;

						case OP_SRFDirective:
                        {
							SRFDirectiveIL sdil;
                            DecodeMsg(&sdil, octets);
						}
						break;

						case OP_TBusy:
                        {
							TbusyIL tbil;
                            DecodeMsg(&tbil, octets);
						}
						break;

						case OP_TNoAnswer: 
                        {
							TNoAnswerIL tail;
                            DecodeMsg(&tail, octets);
						}
						break;
					}


                        // Free allocated memory
                        if (octets)
                        {
                            delete octets;
                        }
					
                    break;

                    case TCPPT_TC_RESULT_L:
                    case TCPPT_TC_RESULT_NL:
                        printf("[WMM IS41 Test]: %s: line %d\n",
                               __FILE__, __LINE__);
                        printf("Received result component.\n");

                        ((TCAP_Result *)cpt)->GetParameter(buf);

                        octets = new Octets(buf);

						

                    // Decode parameter of result component
						
					

					   if ( frID == dlg->GetDialogueID())
						{
						FeatureRequestRRL frrrl;
                        DecodeMsg(&frrrl, octets);						
                        }
					    else if (srID == dlg->GetDialogueID())
						{
						ServiceRequestRRL srrrl;
						DecodeMsg(&srrrl, octets);
						}

                        else if (aiID == dlg->GetDialogueID())
						{
						    AnalyzedInformationRRL airrl;
							DecodeMsg(&airrl, octets);
						}
												
						else if (fsaID == dlg->GetDialogueID())
                        {
							FacilitySelectedAndAvailableRRL fsaarrl;
							DecodeMsg(&fsaarrl, octets);
                        }

						else if (sreID == dlg->GetDialogueID())
                        {
							SeizeResourceRRL srerrl;
							DecodeMsg(&srerrl, octets);
                        }

						else if (sdID == dlg->GetDialogueID())
                        {
							SRFDirectiveRRL sdrrl;
							DecodeMsg(&sdrrl, octets);
                        }
						else if (tbID == dlg->GetDialogueID())
                        {
							TBusyRRL tbrrl;
							DecodeMsg(&tbrrl, octets);
                        }

						else 
                        {
							TNoAnswerRRL tarrl;
							DecodeMsg(&tarrl, octets);
                        }


                        // Free allocated memory
                        
                        if (octets)
						{
                            delete octets;
                        }

                    break;


                    case TCPPT_TC_ERROR:
                        printf("[WIN Test]: %s: line %d\n",
                               __FILE__, __LINE__);
                        printf("Received error component.\n");
                        break;

                    case TCPPT_TC_REJECT:
                        printf("[WIN Test]: %s: line %d\n",
                               __FILE__, __LINE__);
                        printf("Received reject component.\n");
                        break;

                    case TCPPT_TC_CANCEL:
                        printf("[WIN Test]: %s: line %d\n",
                               __FILE__, __LINE__);
                        printf("Received cancel component.\n");
                        break;

                    default:
                        printf("[WIN Test]: %s: line %d\n",
                               __FILE__, __LINE__);
                        cout << "Received unknown component. "
                             << dec << cpt->GetComponentType()
                             << endl;
                    }
                }

                else
                {
                    printf("[WIN Test]: %s: line %d\n", __FILE__,
                           __LINE__);
                    printf("Fail to receive component.\n");
                }

            }
            else if (TCAP_MSG_TYPE(&ev.GetEvent()) == ITS_TCAP_DLG)
            {
                ret = TCAP_Dialogue::Receive((ITS_HANDLE)trin->GetTransport(),
                                             ev, &dlg);

                if (ret == ITS_SUCCESS)
                {
                    printf("[WIN Test]: %s: line %d\n", __FILE__,
                           __LINE__);
                    printf("Received dialogue.\n");

                    switch (dlg->GetDialogueType())
                    {
                    case TCPPT_TC_UNI:
                        printf("[WIN Test]: %s: line %d\n",
                               __FILE__, __LINE__);
                        printf("Received Unidirectinal dialogue.\n");
                        break;

                    case TCPPT_TC_QUERY_W_PERM:
                        printf("[WIN Test]: %s: line %d\n",
                               __FILE__, __LINE__);
                        printf("Received QWP dialogue.\n");
                        break;

                    case TCPPT_TC_QUERY_WO_PERM:
                        printf("[WIN Test]: %s: line %d\n",
                               __FILE__, __LINE__);
                        printf("Received QWOP dialogue.\n");
                        break;

                    case TCPPT_TC_RESP:
                        printf("[WIN Test]: %s: line %d\n",
                               __FILE__, __LINE__);
                        printf("Received Response dialogue.\n");
                        break;

                    case TCPPT_TC_CONV_W_PERM:
                        printf("[WIN Test]: %s: line %d\n",
                               __FILE__, __LINE__);
                        printf("Received CWP dialogue.\n");
                        break;

                    case TCPPT_TC_CONV_WO_PERM:
                        printf("[WIN Test]: %s: line %d\n",
                               __FILE__, __LINE__);
                        printf("Received CWOP dialogue.\n");
                        break;

                    case TCPPT_TC_ABORT:
                        printf("[WIN Test]: %s: line %d\n",
                               __FILE__, __LINE__);
                        printf("Received Abort dialogue.\n");
                        break;

                    case TCPPT_TC_NOTICE:
                        printf("[WIN Test]: %s: line %d\n",
                               __FILE__, __LINE__);
                        printf("Received Notice dialogue.\n");
                        break;

                    default:
                        printf("[WIN Test]: %s: line %d\n",
                               __FILE__, __LINE__);
                        printf("Received unknown dialogue. 0x%02x",
                               dlg->GetDialogueType());
                        break;
                    }
                }
                else
                {
                    printf("[WIN Test]: %s: line %d\n", __FILE__,
                           __LINE__);
                    printf("Fail to receive dialogue.\n");
                }

                printf("Got dialogue: DID is %d\n",
                       dlg->GetDialogueID());
            }
        }
    }

    return (0);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will encode a IS41 message.
 *
 *  Input Parameters:
 *      p - pointer to the IS41 message to be encoded
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      octets - used to store the encoded value of the IS41 message
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
EncodeMsg(AsnObject* p, Octets** octets)
{
    // Print ASN.1 value before encoding.
    printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
    cout << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Printing ASN.1 value before encoding..." << endl;
    cout << endl << *p << endl;

    // Encode using ASN.1 BER.
    Octets* tmpOctets;

    try
    {
        tmpOctets = p->Encode();
    }
    catch (AsnEncodeError& exc)
    {
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Exception during encoding phase..." << endl;
        cout << exc.GetDescription() << endl;
        cout << "Exit test..." << endl;
    }

    cout << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Printing ASN.1 encoded value..." << endl;
    cout << endl << *tmpOctets << endl;

    *octets = tmpOctets;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will decode an encoded IS41 message.
 *
 *  Input Parameters:
 *      octets - the encoded value of a IS41 message
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      p - storage for decoded IS41 message
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
DecodeMsg(AsnObject* p, Octets* octets)
{
    // Decoding using ASN.1 BER.
    try
    {
        p->Decode(*octets);
    }
    catch (AsnDecodeError& exc)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Exception during decoding phase..." << endl;
        cout << exc.GetDescription() << endl;
        cout << "Exit test..." << endl;
    }

    // Print ASN.1 value after decoding.
    printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
    cout << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Printing ASN.1 value after decoding..." << endl;
    cout << endl << *p << endl;
}

/*.implementation:protected
 ****************************************************************************
 *  Purpose:
 *      To send a FeatureRequest invoke last using the WIN library.
 *
 *  Input Parameters:
 *      dlg - pointer to a TCAP_Dialogue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
SendFeatureRequestIL(TCAP_Dialogue *dlg)
{
    int result = ITS_SUCCESS;
    ITS_OCTET family = 0x00, code = 0x00;
    Octets *encOctets;
    TCAP_Invoke inv;
	frID = dlg->GetDialogueID();
    FeatureRequestIL *fril = new FeatureRequestIL();

	byte digitsArray[5] = { 0x11, 0x22, 0x33, 0x44, 0x55 };
	byte esnArray[4] = { 0x11, 0x12, 0x13, 0x14 };
	byte mobileIDNumArray[5] = { 0x11, 0x22, 0x33, 0x44, 0x55 };

    byte billingIdArray[7] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 };
    byte callingPartyNum1Array[5] = { 0x04, 0x77, 0x62, 0x44, 0x25 };
    byte callingPartyNum2Array[5] = { 0x04, 0x77, 0x33, 0x14, 0x34 };
    byte callingPartySubaddrArray[5] = { 0x11, 0x22, 0x33, 0x44, 0x55 };
	byte conferenceCallIndArray[2] = { 0x23, 0x24 };
    byte mobileDirectoryNumArray[5] = { 0x22, 0x34, 0x13, 0x24, 0x16};  
	byte oneTimeFeatureIndArray[2]= { 0x34, 0x53 };
    byte mscidArray[3] = { 0x04, 0x05, 0x06 };
    byte mscidNumArray[5] = { 0x12, 0x13, 0x14, 0x15, 0x16 };
    byte pc_ssnArray[5] = { 0x11, 0x22, 0x33, 0x44, 0x55 };	
    byte senderIdNumArray[5] = { 0x91, 0x92, 0x93, 0x94, 0x95 };
    byte transactionCapabilityArray[5] = { 0x30, 0x32, 0x34, 0x36, 0x38 };


    /* Set LocationRequest parameters*/
    

    // BillingID
    
    BillingID* billingId =
        new BillingID(FixedByteArrayToVector(billingIdArray));
    fril->SetBillingID( billingId );

    
    // CallingPartyNumberDigits1
    
    CallingPartyNumberDigits1* callingPartyNum1 =
        new CallingPartyNumberDigits1(FixedByteArrayToVector(callingPartyNum1Array));
    fril->SetCallingPartyNumberDigits1( callingPartyNum1 );

    
    // CallingPartyNumberDigits2
    
    CallingPartyNumberDigits2* callingPartyNum2
        = new CallingPartyNumberDigits2(FixedByteArrayToVector(callingPartyNum2Array));
    fril->SetCallingPartyNumberDigits2( callingPartyNum2 ); 

    
    // CallingPartySubaddress
    
    CallingPartySubaddress* callingPartySubaddr =
        new CallingPartySubaddress(FixedByteArrayToVector(callingPartySubaddrArray));
    fril->SetCallingPartySubaddress( callingPartySubaddr ); 

    
	// ConferenceCallingIndicator

	ConferenceCallingIndicator* cci = 
		new ConferenceCallingIndicator(FixedByteArrayToVector(conferenceCallIndArray));
    fril->SetConferenceCallingIndicator(cci);

    // Digits
    
    Digits* digits = new Digits( FixedByteArrayToVector( digitsArray ) );
    fril->SetDigits( digits ); 

	
	//Electronic Serial no.
	
	ElectronicSerialNumber* esn = 
		new ElectronicSerialNumber( FixedByteArrayToVector( esnArray ) );
	fril->SetElectronicSerialNumber(esn);

	
    // MobileDirectoryNumber
 
	MobileDirectoryNumber* mdn = 
		new MobileDirectoryNumber(FixedByteArrayToVector(mobileDirectoryNumArray));
	fril->SetMobileDirectoryNumber(mdn);

	//MobileIdentificationNumber
	
    MobileIdentificationNumber* min = 
		new MobileIdentificationNumber(FixedByteArrayToVector(mobileIDNumArray));
	fril->SetMobileIdentificationNumber(min);

	
    // MSCID
    
    MSCID* mscid = new MSCID( FixedByteArrayToVector( mscidArray ) );
    fril->SetMSCID( mscid );

    
    // MSCIdentificationNumber
    
    MSCIdentificationNumber* mscIdentificationNum =
        new MSCIdentificationNumber( FixedByteArrayToVector( mscidNumArray) );
    fril->SetMSCIdentificationNumber( mscIdentificationNum );

    
	// OneTimeFeatureIndicator

	OneTimeFeatureIndicator* otfi = 
		new OneTimeFeatureIndicator( FixedByteArrayToVector( oneTimeFeatureIndArray) );
    fril->SetOneTimeFeatureIndicator(otfi);


    // PC_SSN
    
    PC_SSN* pc_ssn = new PC_SSN( FixedByteArrayToVector( pc_ssnArray) );
    fril->SetPC_SSN( pc_ssn );

   
    // SenderIdentificationNumber
    
    SenderIdentificationNumber* senderIdNum =
        new SenderIdentificationNumber(FixedByteArrayToVector(senderIdNumArray));
    fril->SetSenderIdentificationNumber( senderIdNum );

        
    // TransactionCapability
    
    TransactionCapability* transactionCapability =
        new TransactionCapability(FixedByteArrayToVector(transactionCapabilityArray));
    fril->SetTransactionCapability( transactionCapability );


    /* Encode IS41 message*/
    
    EncodeMsg( fril, &encOctets );

    inv.SetTimeOut( 90 );
    inv.SetInvokeID( 1 );
    inv.SetOperation(true, 17, OP_FeatureRequest);
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    traceComponent( &inv );

    /* Send an LocationRequest invoke component*/
    result = TCAP_Component::Send((ITS_HANDLE)trin->GetTransport(), dlg, &inv);

    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "FeatureRequest invoke send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send FeatureRequest invoke." << endl;
        cout << "Error: " << ITS_GetErrorText( result ) << endl;
    }

    /* Send dialog*/
    result = TCAP_Dialogue::Send((ITS_HANDLE)trin->GetTransport(), dlg);
    
    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Dialogue send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send Dialogue." << endl;
        cout << "Error: " << ITS_GetErrorText( result ) << endl;
    }


    /* Free allocated memory*/
    if (fril)
    {
        delete fril;
    }

    if (encOctets)
    {
        delete encOctets;
    }

    fril = NULL;
    encOctets = NULL;

    return result;
}

/*.implementation:protected
 ****************************************************************************
 *  Purpose:
 *      To send a FeatureRequest result last using the WIN library.
 *
 *  Input Parameters:
 *      dlg - pointer to a TCAP_Dialogue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
SendFeatureRequestRRL(TCAP_Dialogue *dlg, TCAP_Component *recvCpt)
{
    int result = ITS_SUCCESS;
    ITS_OCTET family = 0x00, code = 0x00;
    Octets *encOctets = NULL;
    TCAP_Result res;
    FeatureRequestRRL *frrrl = new FeatureRequestRRL();

	byte actionCodeArray[2] = { 0x71, 0x82 };
    byte announcementCodeArray1[5] = { 0x01, 0x02, 0x03, 0x04, 0x05 };
    byte announcementCodeArray2[5] = { 0x11, 0x12, 0x13, 0x14, 0x15 };
    byte callingPartyNumStr1Array[5] = { 0x04, 0x77, 0x62, 0x60, 0x08 };
	byte callingPartyNumStr2Array[5] = { 0x12, 0x37, 0x42, 0x65, 0x48 };
	byte callingPartySubaddrArray[5] = { 0x01, 0x32, 0x38, 0x24, 0x35 };
	byte carrierDigitsArray[5] = { 0x77, 0x88, 0x12, 0x67, 0x99 };
	byte conferenceCallIndArray[2] = { 0x32, 0x33 };
	byte digitsArray[5] = { 0x27, 0x58, 0x12, 0x67, 0x65 };
    byte digitsCarrierArray[5] = { 0x11, 0x22, 0x33, 0x44, 0x55 };
    byte digitsDestinationArray[5] = { 0x91, 0x92, 0x93, 0x94, 0x95 };
	byte displayTextArray[2] = {0x32, 0x33};
	byte dMHbillingdigitsArray[6] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 }; 
	byte dMHaccountCodeArray[5] = { 0x02, 0x03, 0x04, 0x05, 0x08 };
	byte dMHaltBillDigitsArray[5] = { 0x31, 0x02, 0x03, 0x04, 0x12 };
    byte groupInfoArray[4] = { 0x13, 0x23, 0x33, 0x34 };
    byte mdnArray[5] = { 0x04, 0x77, 0x28, 0x44, 0x87 };
	byte noAnswerTArray[2] = { 0x34, 0x12 };
    byte oneTimeFeatureIndArray[2]= { 0x40, 0x42 };
	byte pACAIndicatorArray[2] = {0x32, 0x15 };
	byte pilotNumberArray[5] = {0x10, 0x22, 0x30, 0x40, 0x51};
	byte redirectingNumDigitsArray[5] = { 0x10, 0x20, 0x30, 0x40, 0x50 };
	byte redirectingNumStrArray[5] = { 0x10, 0x20, 0x32, 0x40, 0x54 };
    byte redirectingSubaddrArray[6] = { 0x01, 0x21, 0x31, 0x41, 0x51, 0x27 };
	byte routingDigitsArray[5] = {0x11, 0x34, 0x21, 0x54, 0x26};

    byte terminationTriggersArray[2] = { 0x11, 0x12 };
    
    byte destinationDigitsArray[5] = { 0x01, 0x02, 0x16, 0x23, 0x15 };
    byte mscidArray[3] = { 0x04, 0x05, 0x06 };
    
	byte wINTriggListArray[2] = {0x23, 0x11 };
	byte globalTitleArray[2] = {0x11, 0x12};
	byte pcSSNArray[5] = {0x11, 0x12, 0x13, 0x14, 0x15};


    /* Set LocationRequest result parameters*/
   
    
	//FeatureResult
	
	FeatureResult featureResult;
	featureResult.SetUnsuccessful();
	frrrl->SetFeatureResult(featureResult);

	//AccessDeniedReason
	
    AccessDeniedReason accessDeniedReason;
    accessDeniedReason.SetBusy();
    frrrl->SetAccessDeniedReason( accessDeniedReason );

    
	// ActionCode

    ActionCode* actionCode =
		new ActionCode(FixedByteArrayToVector(actionCodeArray));
	frrrl->SetActionCode(actionCode);

    // AnnouncementList
    
    AnnouncementCode* announcementCode1 =
        new AnnouncementCode(FixedByteArrayToVector(announcementCodeArray1));
    
    AnnouncementCode* announcementCode2 =
        new AnnouncementCode(FixedByteArrayToVector(announcementCodeArray2));
    
    AnnouncementList::CHOICE choice1;
    choice1.SetChoiceAnnouncementCode( announcementCode1 );

    AnnouncementList::CHOICE choice2;
    choice2.SetChoiceAnnouncementCode( announcementCode2 );

    AnnouncementList announcementList;
    announcementList.AddElement( choice1);
    announcementList.AddElement( choice2);

    frrrl->SetAnnouncementList( announcementList );
   
    // CallingPartyNumberString1
    
    CallingPartyNumberString1* callingPartyNumStr1 =
        new CallingPartyNumberString1(FixedByteArrayToVector(callingPartyNumStr1Array));
    frrrl->SetCallingPartyNumberString1( callingPartyNumStr1 );

    
	// CallingPartyNumberString2
    
    CallingPartyNumberString2* callingPartyNumStr2 =
        new CallingPartyNumberString2(FixedByteArrayToVector(callingPartyNumStr2Array));
    frrrl->SetCallingPartyNumberString2( callingPartyNumStr2 );


	// CallingPartySubaddress
    
    CallingPartySubaddress* callingPartySubaddr =
        new CallingPartySubaddress(FixedByteArrayToVector(callingPartySubaddrArray));
    frrrl->SetCallingPartySubaddress( callingPartySubaddr ); 

    // CarrierDigits
    
    CarrierDigits* carrierDigits =
        new CarrierDigits(FixedByteArrayToVector(digitsCarrierArray));
    frrrl->SetCarrierDigits( carrierDigits );
    
	// ConferenceCallingIndicator

	ConferenceCallingIndicator* cci = 
		new ConferenceCallingIndicator(FixedByteArrayToVector(conferenceCallIndArray));
    frrrl->SetConferenceCallingIndicator(cci);

	// Digits

	Digits* digits =
        new Digits(FixedByteArrayToVector(digitsArray));
    frrrl->SetDigits( digits );

    // DisplayText
   
    DisplayText* dt =
        new DisplayText(FixedByteArrayToVector(displayTextArray));
    frrrl->SetDisplayText( dt );


	// DMHBillingID
    
    DMH_BillingDigits* dMH_billingDigits =
        new DMH_BillingDigits(FixedByteArrayToVector(dMHbillingdigitsArray));
    frrrl->SetDMH_BillingDigits( dMH_billingDigits );

	// DMHAccountCode

	DMH_AccountCodeDigits* dmha =
		new DMH_AccountCodeDigits(FixedByteArrayToVector(dMHaccountCodeArray));
	frrrl->SetDMH_AccountCodeDigits(dmha);

    // DMHAlternateBillingID
    
    DMH_AlternateBillingDigits* dmhab =
        new DMH_AlternateBillingDigits(FixedByteArrayToVector(dMHaltBillDigitsArray));
    frrrl->SetDMH_AlternateBillingDigits( dmhab );

	// DMHRedirectionIndicator

	DMH_RedirectionIndicator dmhr;
	dmhr.SetCFU();
	frrrl->SetDMH_RedirectionIndicator(dmhr);

	// GroupInformation

	GroupInformation* gi = 
		new GroupInformation(FixedByteArrayToVector(groupInfoArray));
	frrrl->SetGroupInformation(gi);

    // MobileDirectoryNumber
    
    MobileDirectoryNumber* mdn =
        new MobileDirectoryNumber(FixedByteArrayToVector(mdnArray));
    frrrl->SetMobileDirectoryNumber( mdn );

	// NoAnswerTime

	NoAnswerTime* nat = 
		new NoAnswerTime(FixedByteArrayToVector(noAnswerTArray));
	frrrl->SetNoAnswerTime(nat);

	// OneTimeFeatureIndicator

	OneTimeFeatureIndicator* otfi = 
		new OneTimeFeatureIndicator( FixedByteArrayToVector( oneTimeFeatureIndArray) );
    frrrl->SetOneTimeFeatureIndicator(otfi);

	// PACAIndicator

	PACAIndicator* pacai = 
		new PACAIndicator(FixedByteArrayToVector(pACAIndicatorArray));
	frrrl->SetPACAIndicator(pacai);

	// PilotNumber

	PilotNumber* pn =
		new PilotNumber(FixedByteArrayToVector(pilotNumberArray));
	frrrl->SetPilotNumber(pn);

	// RedirectingNumberDigits
    
    RedirectingNumberDigits* redirectingNumDigits =
        new RedirectingNumberDigits(FixedByteArrayToVector(redirectingNumDigitsArray));
	frrrl->SetRedirectingNumberDigits( redirectingNumDigits );

	// RedirectingNumberString
    
    RedirectingNumberString* rns =
        new RedirectingNumberString(FixedByteArrayToVector(redirectingNumStrArray));
	frrrl->SetRedirectingNumberString( rns );

    // RedirectingSubaddress
    
    RedirectingSubaddress* redirectingSubaddr =
        new RedirectingSubaddress(FixedByteArrayToVector(redirectingSubaddrArray));
    frrrl->SetRedirectingSubaddress( redirectingSubaddr );

	// ResumePIC

	ResumePIC rPIC;
	rPIC.SetSelectRoutePIC();
	frrrl->SetResumePIC(rPIC);

    
    // RoutingDigits   
    
    RoutingDigits* rd =
        new RoutingDigits(FixedByteArrayToVector(routingDigitsArray));
    frrrl->SetRoutingDigits( rd );


	//TerminationList   

	DestinationDigits* dd =
        new DestinationDigits(FixedByteArrayToVector(destinationDigitsArray));
    
	MSCID* mscid = new MSCID( FixedByteArrayToVector( mscidArray ));
    
	IntersystemTermination ist;
	ist.SetDestinationDigits(dd);
	ist.SetMSCID(mscid);

	TerminationList::CHOICE ch;  
	ch.SetChoiceIntersystemTermination(ist);

    TerminationList tl;
	tl.AddElement(ch);

	frrrl->SetTerminationList(tl);

	// TerminationTriggers

	TerminationTriggers* tt = 
		new TerminationTriggers(FixedByteArrayToVector(terminationTriggersArray));
	frrrl->SetTerminationTriggers(tt);



    /* Encode WIN message*/
    EncodeMsg( frrrl, &encOctets );

    res.SetInvokeID( 1/*recvCpt->GetInvokeID() */);
    res.SetParameter( const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                      encOctets->GetLength());

    /* Printout result information*/
    traceComponent( &res );

    /* Send an LocationRequest result component*/
    result = TCAP_Component::Send((ITS_HANDLE)trin->GetTransport(), dlg,
                                  &res);

    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "FeatureRequest ReturnResultLast send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send FeatureRequest ReturnResultLast." << endl;
        cout << "Error: " << result << endl;
    }

    /* Send dialog*/
    result = TCAP_Dialogue::Send((ITS_HANDLE)trin->GetTransport(), dlg);
    
    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Dialogue send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send Dialogue." << endl;
        cout << "Error: " << ITS_GetErrorText( result ) << endl;
    }

    /* Free allocated memory*/
    if (frrrl)
    {
        delete frrrl;
    }

    if (encOctets)
    {
        delete encOctets;
    }

    frrrl = NULL;
    encOctets = NULL;

    return result;
}



/*.implementation:protected
 ****************************************************************************
 *  Purpose:
 *      To send ServiceRequest invoke last using the WIN library.
 *
 *  Input Parameters:
 *      dlg - pointer to a TCAP_Dialogue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
SendServiceRequestIL(TCAP_Dialogue *dlg)
{
    int result = ITS_SUCCESS;
    ITS_OCTET family = 0x00, code = 0x00;
    Octets *encOctets;
    TCAP_Invoke inv;
	srID = dlg->GetDialogueID();
    ServiceRequestIL *sril = new ServiceRequestIL();

    byte serviceIdArray [2] = { 0x02, 0x05 };

	byte availTypeArray[2]= {0x22, 0x23};
	byte billingIdArray[7] = { 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09 };
	byte callingPartyNameArray[2] = {0x32, 0x41};
	byte callingPartyNum1Array[5] = { 0x14, 0x27, 0x32, 0x24, 0x27 };
    byte callingPartyNum2Array[5] = { 0x13, 0x75, 0x23, 0x15, 0x24 };
	byte callingPartySubaddrArray[5] = { 0x10, 0x20, 0x30, 0x40, 0x50 };
	byte digitsArray[5] = { 0x01, 0x02, 0x13, 0x34, 0x44 };

	byte dataIDArray[2] = {0x12, 0x13};
	byte dataValueArray[2] = {0x22, 0x23};

	byte groupInfoArray[4] = { 0x13, 0x23, 0x03, 0x53 };
	byte legInfoArray[4] = {0x11, 0x12, 0x23, 0x24};
	byte locationAreaArray[2] = {0x33, 0x34};
	byte mdnArray[5] = { 0x04, 0x75, 0x28, 0x44, 0x87 }; 
	byte mobileIdNumArray[5] = {0x11, 0x22, 0x33, 0x44, 0x55};
    byte mscidArray[3] = { 0x01, 0x02, 0x03 };
	byte mscinArray[5] = { 0x01, 0x02, 0x03, 0x04, 0x05};
	byte pilotBillIDArray[7] = {0x10, 0x22, 0x30, 0x40, 0x51, 0x43, 0x12};
	byte pilotNumberArray[5] = {0x10, 0x22, 0x30, 0x40, 0x51};
	byte pc_ssnArray[5] = {0x11, 0x22, 0x33, 0x44, 0x60};
	byte preferredLangIndArray[2] = { 0x04, 0x11 };
	byte redirectingPartyNameArray[5] = {0x13, 0x14, 0x15, 0x16, 0x17};
    byte redirectingNumDigitsArray[5] = {0x10, 0x20, 0x30, 0x40, 0x50};
    byte redirectingSubaddrArray[6] = {0x11, 0x21, 0x31, 0x41, 0x51, 0x61};	
    byte senderIdNumArray[5] = {0x90, 0x91, 0x92, 0x93, 0x94};
	byte servCellIDArray[2] = {0x22, 0x44};

	int  timeDateOffset = 100;
	byte tatArray[2] = {0x12, 0x23};
    byte transactionCapabilityArray[5] = {0x30, 0x29, 0x31, 0x34, 0x18};
    byte triggerCapabilityArray[1] = { 0x03};

    /* Set LocationRequest parameters*/
    
    
    // ServiceID
    
    ServiceID* serviceId = 
        new ServiceID(FixedByteArrayToVector(serviceIdArray));  
    sril->SetServiceID (serviceId);   

    //AccessDeniedReason
	
    AccessDeniedReason accessDeniedReason;
    accessDeniedReason.SetNoPageResponse();
    sril->SetAccessDeniedReason( accessDeniedReason );


	// AvailabilityType

	AvailabilityType* at =
		new AvailabilityType(FixedByteArrayToVector(availTypeArray));
	sril->SetAvailabilityType(at);

    // BillingID
    
    BillingID* billingId =
        new BillingID(FixedByteArrayToVector(billingIdArray));
    sril->SetBillingID( billingId );

	// CallingPartyName
    
    CallingPartyName* cpn =
        new CallingPartyName(FixedByteArrayToVector(callingPartyNameArray));
    sril->SetCallingPartyName( cpn );

    
    // CallingPartyNumberDigits1
    
    CallingPartyNumberDigits1* callingPartyNum1 =
        new CallingPartyNumberDigits1(FixedByteArrayToVector(callingPartyNum1Array));
    sril->SetCallingPartyNumberDigits1( callingPartyNum1 );

    
    // CallingPartyNumberDigits2
    
    CallingPartyNumberDigits2* callingPartyNum2
        = new CallingPartyNumberDigits2(FixedByteArrayToVector(callingPartyNum2Array));
    sril->SetCallingPartyNumberDigits2( callingPartyNum2 ); 

    
    // CallingPartySubaddress
    
    CallingPartySubaddress* callingPartySubaddr =
        new CallingPartySubaddress(FixedByteArrayToVector(callingPartySubaddrArray));
    sril->SetCallingPartySubaddress( callingPartySubaddr ); 

	// ConditionallyDeniedReason

	ConditionallyDeniedReason cdr;
	cdr.SetNotUsed();
//	cdr.SetWaitable();
	sril->SetConditionallyDeniedReason(cdr);

	// DataAccessElementList

	DataID* did = new DataID(FixedByteArrayToVector(dataIDArray));
	DataValue* dv = new DataValue(FixedByteArrayToVector(dataValueArray));

	Change change1;
	change1.SetNotused();
/*	change2.SetSetDataItemToDefaultValue();
	change3.SetAddDataItem();
	change4.SetDeleteDataItem();
	change5.SetReplaceDataItemWithAssociatedDataValue();*/

	DataAccessElement dae;
	dae.SetDataID(did);
	dae.SetDataValue(dv);
	dae.SetChange(change1);
/*	dae.SetChange(change2);
	dae.SetChange(change3);
	dae.SetChange(change4);
	dae.SetChange(change5);*/

	DataAccessElementList::SEQUENCE seq;
	seq.SetDataAccessElement(dae);
	
	DataAccessElementList dael;
	dael.AddElement(seq);

	sril->SetDataAccessElementList(dael);

   // Digits
    
    Digits* digits = new Digits(FixedByteArrayToVector(digitsArray));
    sril->SetDigitsdialed(digits); 

	//GroupInformation

	GroupInformation* gi = 
		new GroupInformation(FixedByteArrayToVector(groupInfoArray));
	sril->SetGroupInformation(gi);


	//LegInformation

	LegInformation* li = 
		new LegInformation(FixedByteArrayToVector(legInfoArray));
	sril->SetLegInformation(li);

	// LocationAreaID

	LocationAreaID* laID =
		new LocationAreaID(FixedByteArrayToVector(locationAreaArray));
	sril->SetLocationAreaID(laID);

	// MobileDirectoryNumber
    
    MobileDirectoryNumber* mdn =
        new MobileDirectoryNumber(FixedByteArrayToVector(mdnArray));
    sril->SetMobileDirectoryNumber( mdn );

	//MobileIdentificationNumber
	
    MobileIdentificationNumber* min = 
	    new MobileIdentificationNumber(FixedByteArrayToVector(mobileIdNumArray ) );
	sril->SetMobileIdentificationNumber(min);

	
    // MSCID
    
    MSCID* mscid = new MSCID( FixedByteArrayToVector( mscidArray ));
    sril->SetMSCID( mscid );


	// MSCIN
    
   /* MSCIN* mscin = new MSCIN( FixedByteArrayToVector( mscinArray ));
    sril->SetMSCIN( mscin );
    
    // PC_SSN
    
    PC_SSN* pc_ssn = new PC_SSN( FixedByteArrayToVector( pc_ssnArray));
    sril->SetPC_SSN( pc_ssn );


	// PilotBillingID
	
	PilotBillingID* pb =
		new PilotBillingID(FixedByteArrayToVector(pilotBillIDArray));
	sril->SetPilotBillingID(pb);


	// PilotNumber

	PilotNumber* pn =
		new PilotNumber(FixedByteArrayToVector(pilotNumberArray));
	sril->SetPilotNumber(pn);

	// PreferredLanguageIndicator

	PreferredLanguageIndicator* pli =
		new PreferredLanguageIndicator(FixedByteArrayToVector(preferredLangIndArray));
	sril->SetPreferredLanguageIndicator(pli);


	// RedirectingPartyName
    
    RedirectingPartyName* rpn =
        new RedirectingPartyName(FixedByteArrayToVector(redirectingPartyNameArray));
    sril->SetRedirectingPartyName( rpn );

	// RedirectingNumberDigits
    
    RedirectingNumberDigits* redirectingNumDigits =
        new RedirectingNumberDigits(FixedByteArrayToVector(redirectingNumDigitsArray));
	sril->SetRedirectingNumberDigits( redirectingNumDigits );

    
    // RedirectingSubaddress
    
    RedirectingSubaddress* redirectingSubaddr =
        new RedirectingSubaddress(FixedByteArrayToVector(redirectingSubaddrArray));
    sril->SetRedirectingSubaddress( redirectingSubaddr );
    

	//RedirectionReason

	RedirectionReason rr;
	rr.SetCallRefused();
	sril->SetRedirectionReason(rr);

    // SenderIdentificationNumber
    
    SenderIdentificationNumber* senderIdNum =
        new SenderIdentificationNumber(FixedByteArrayToVector(senderIdNumArray));
    sril->SetSenderIdentificationNumber( senderIdNum );

            
	// ServingCellID

	ServingCellID* sid =
		new ServingCellID(FixedByteArrayToVector(servCellIDArray));
	sril->SetServingCellID(sid);*/

	// SystemMyTypeCode

	SystemMyTypeCode smtc;
	smtc.SetInet();
	sril->SetSystemMyTypeCode(smtc);


	// TerminationAccessType

	TerminationAccessType* tat =
		new TerminationAccessType(FixedByteArrayToVector(tatArray));
	sril->SetTerminationAccessType(tat);

	// TimeDateOffSet

	TimeDateOffset* tdos = 
		new TimeDateOffset(timeDateOffset);
	sril->SetTimeDateOffset(tdos);

    // TransactionCapability
    
   TransactionCapability* transactionCapability =
        new TransactionCapability(FixedByteArrayToVector(transactionCapabilityArray));
    sril->SetTransactionCapability( transactionCapability );

	// TriggerType

	TriggerType tt;
	tt.SetFourDigit();
	sril->SetTriggerType(tt);
    
	// wINCapability

    WINCapability* wINCapability = new WINCapability();
	TriggerCapability* triggerCapability = 
		new TriggerCapability(FixedByteArrayToVector(triggerCapabilityArray));
    wINCapability->SetTriggerCapability(triggerCapability);
	sril->SetWINCapability(wINCapability);



    /* Encode IS41 message*/
    
    EncodeMsg( sril, &encOctets );

    inv.SetTimeOut( 90 );
    inv.SetInvokeID( 1 );
    inv.SetOperation(true, 77, OP_ServiceRequest);
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    traceComponent( &inv );

    /* Send an LocationRequest invoke component*/
    result = TCAP_Component::Send((ITS_HANDLE)trin->GetTransport(), dlg, &inv);

    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Service_Request_Invoke send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send Service_Request_Invoke." << endl;
        cout << "Error: " << ITS_GetErrorText( result ) << endl;
    }


    /* Send dialog*/
    result = TCAP_Dialogue::Send((ITS_HANDLE)trin->GetTransport(), dlg);
    
    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Dialogue send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send Dialogue." << endl;
        cout << "Error: " << ITS_GetErrorText( result ) << endl;
    }


    /* Free allocated memory*/
    if (sril)
    {
        delete sril;
    }

    if (encOctets)
    {
        delete encOctets;
    }

    sril = NULL;
    encOctets = NULL;

    return result;
}

    
/*.implementation:protected
 ****************************************************************************
 *  Purpose:
 *      To send a ServiceRequest result last using the WIN library.
 *
 *  Input Parameters:
 *      dlg - pointer to a TCAP_Dialogue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
SendServiceRequestRRL(TCAP_Dialogue *dlg, TCAP_Component *recvCpt)
{
    int result = ITS_SUCCESS;
    ITS_OCTET family = 0x00, code = 0x00;
    Octets *encOctets = NULL;
    TCAP_Result res;
    ServiceRequestRRL *srrrl = new ServiceRequestRRL();

	byte actionCodeArray[2] = { 0x56, 0x85 };
	byte alertCodeArray[2] = { 0x36, 0x65 };
    byte announcementCodeArray1[5] = { 0x01, 0x02, 0x03, 0x04, 0x05 };
    byte announcementCodeArray2[5] = { 0x11, 0x12, 0x13, 0x14, 0x15 };
    byte callPartyNumStr1Array[5] = { 0x04, 0x77, 0x62, 0x60, 0x08 };
	byte callPartyNumStr2Array[5] = { 0x14, 0x37, 0x42, 0x50, 0x28 };
	byte callPartySubaddrArray[5] = { 0x10, 0x22, 0x33, 0x44, 0x59 };
    byte carrierDigitsArray[5] = { 0x04, 0x77, 0x22, 0x99, 0x24 };
    byte digitsArray[5] = { 0x91, 0x92, 0x93, 0x94, 0x95 };
	byte displayTextArray[2] = {0x32, 0x33};
	byte dMHbillingdigitsArray[6] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 }; 
	byte dMHaccountCodeArray[5] = { 0x02, 0x03, 0x04, 0x05, 0x08 };
	byte dMHaltBillDigitsArray[5] = { 0x31, 0x02, 0x03, 0x04, 0x12 };
    byte groupInfoArray[4] = { 0x13, 0x23, 0x33, 0x43 };
    byte mdnArray[5] = { 0x04, 0x77, 0x28, 0x44, 0x96 };  
	byte redirectingNumDigitsArray[5] = { 0x10, 0x20, 0x30, 0x40, 0x50 };
	byte redirectingNumStrArray[5] = { 0x10, 0x20, 0x30, 0x40, 0x50 };
	byte redirectingPartyNameArray[5] = {0x13, 0x14, 0x15, 0x21, 0x20};
    byte redirectingSubaddrArray[6] = {0x11, 0x21, 0x31, 0x41, 0x51, 0x61};
    byte routingDigitsArray[5] = { 0x04, 0x77, 0x23, 0x78, 0x99 };
    
	byte destinationDigitsArray[5] = { 0x01, 0x02, 0x16, 0x23, 0x19 };
    byte mscidArray[3] = { 0x04, 0x05, 0x67};
    
    /* Set LocationRequest result parameters*/

  
	//AccessDeniedReason
	
    AccessDeniedReason accessDeniedReason;
    accessDeniedReason.SetInactive();
    srrrl->SetAccessDeniedReason( accessDeniedReason );

    // ActionCode

    ActionCode* actionCode =
		new ActionCode(FixedByteArrayToVector(actionCodeArray));
	srrrl->SetActionCode(actionCode);

	// AlertCode

    AlertCode* alertCode =
		new AlertCode(FixedByteArrayToVector(alertCodeArray));
	srrrl->SetAlertCode(alertCode);

    // AnnouncementList
    
    AnnouncementCode* announcementCode1 =
        new AnnouncementCode(FixedByteArrayToVector(announcementCodeArray1));
    
    AnnouncementCode* announcementCode2 =
        new AnnouncementCode(FixedByteArrayToVector(announcementCodeArray2));
    
    AnnouncementList::CHOICE choice1;
    choice1.SetChoiceAnnouncementCode( announcementCode1 );

    AnnouncementList::CHOICE choice2;
    choice2.SetChoiceAnnouncementCode( announcementCode2 );

    AnnouncementList announcementList;
    announcementList.AddElement( choice1);
    announcementList.AddElement( choice2);

    srrrl->SetAnnouncementList( announcementList );

    
    // CallingPartyNumberString1
    
    CallingPartyNumberString1* callingPartyNumStr1 =
        new CallingPartyNumberString1(FixedByteArrayToVector(callPartyNumStr1Array));
    srrrl->SetCallingPartyNumberString1( callingPartyNumStr1 );

	// CallingPartyNumberString2
    
    CallingPartyNumberString2* callingPartyNumStr2 =
        new CallingPartyNumberString2(FixedByteArrayToVector(callPartyNumStr2Array));
    srrrl->SetCallingPartyNumberString2( callingPartyNumStr2 );

   
	 // CallingPartySubaddress
    
    CallingPartySubaddress* callingPartySubaddr =
        new CallingPartySubaddress(FixedByteArrayToVector(callPartySubaddrArray));
    srrrl->SetCallingPartySubaddress( callingPartySubaddr ); 


    // DigitsCarrier
    
    CarrierDigits* carrierDigits =
        new CarrierDigits(FixedByteArrayToVector(carrierDigitsArray));

    srrrl->SetCarrierDigits( carrierDigits );

	// DigitsDialed
	
	Digits* digits = new Digits(FixedByteArrayToVector(digitsArray));
    srrrl->SetDigitsdialed( digits );

	
    // DisplayText
   
	byte noAnswerTArray[2] = { 0x34, 0x12 };
    DisplayText* dt =
        new DisplayText(FixedByteArrayToVector(displayTextArray));
    srrrl->SetDisplayText( dt );


	// DMHBillingID
    
    DMH_BillingDigits* dMH_billingDigits =
        new DMH_BillingDigits(FixedByteArrayToVector(dMHbillingdigitsArray));
    srrrl->SetDMH_BillingDigits( dMH_billingDigits );

	// DMHAccountCode

	DMH_AccountCodeDigits* dmha =
		new DMH_AccountCodeDigits(FixedByteArrayToVector(dMHaccountCodeArray));
	srrrl->SetDMH_AccountCodeDigits(dmha);

    // DMHAlternateBillingID
    
    DMH_AlternateBillingDigits* dmhab =
        new DMH_AlternateBillingDigits(FixedByteArrayToVector(dMHaltBillDigitsArray));
    srrrl->SetDMH_AlternateBillingDigits( dmhab );

	// DMHRedirectionIndicator

	DMH_RedirectionIndicator dmhr;
	dmhr.SetCFU();
	srrrl->SetDMH_RedirectionIndicator(dmhr);


	//GroupInformation

	GroupInformation* gi = 
		new GroupInformation(FixedByteArrayToVector(groupInfoArray));
	srrrl->SetGroupInformation(gi);

    // MobileDirectoryNumber
    
    MobileDirectoryNumber* mdn =
        new MobileDirectoryNumber(FixedByteArrayToVector(mdnArray));
    srrrl->SetMobileDirectoryNumber( mdn );

	// NoAnswerTime

	NoAnswerTime* nat = 
		new NoAnswerTime(FixedByteArrayToVector(noAnswerTArray));
	srrrl->SetNoAnswerTime(nat);


    // RedirectingNumberDigits
    
	RedirectingNumberDigits* redirectingNumDigits =
        new RedirectingNumberDigits(FixedByteArrayToVector(redirectingNumDigitsArray));
    srrrl->SetRedirectingNumberDigits( redirectingNumDigits );


	// RedirectingNumberString
    
	RedirectingNumberString* redirectingNumStr =
        new RedirectingNumberString(FixedByteArrayToVector(redirectingNumStrArray));
    srrrl->SetRedirectingNumberString( redirectingNumStr );

	// RedirectingPartyName

    RedirectingPartyName* rpn =
        new RedirectingPartyName(FixedByteArrayToVector(redirectingPartyNameArray));
    srrrl->SetRedirectingPartyName( rpn );

    
    // RedirectingSubaddress
   
	RedirectingSubaddress* redirectingSubaddr =
        new RedirectingSubaddress(FixedByteArrayToVector(redirectingSubaddrArray));

    srrrl->SetRedirectingSubaddress( redirectingSubaddr );
    

	// ResumePIC

	ResumePIC rPIC;
	rPIC.SetSelectRoutePIC();
	srrrl->SetResumePIC(rPIC);

    
    // RoutingDigits
    
    RoutingDigits* routingDigits =
        new RoutingDigits(FixedByteArrayToVector(routingDigitsArray));

    srrrl->SetRoutingDigits( routingDigits );

	//TerminationList   

	DestinationDigits* dd =
        new DestinationDigits(FixedByteArrayToVector(destinationDigitsArray));
    
	MSCID* mscid = new MSCID( FixedByteArrayToVector( mscidArray ));
    
	IntersystemTermination ist;
	ist.SetDestinationDigits(dd);
	ist.SetMSCID(mscid);

	TerminationList::CHOICE ch;  
	ch.SetChoiceIntersystemTermination(ist);

    TerminationList tl;
	tl.AddElement(ch);

	srrrl->SetTerminationList(tl);



    /* Encode WIN message*/
    EncodeMsg( srrrl, &encOctets );

    res.SetInvokeID( recvCpt->GetInvokeID());
    res.SetParameter( const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                      encOctets->GetLength());

    /* Printout result information*/
    traceComponent( &res );

    /* Send an LocationRequest result component*/
    result = TCAP_Component::Send((ITS_HANDLE)trin->GetTransport(), dlg,
                                  &res);

    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "ServiceRequest ReturnResultLast send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send ServiceRequest ReturnResultLast." << endl;
        cout << "Error: " << result << endl;
    }

    /* Send dialog*/
    result = TCAP_Dialogue::Send((ITS_HANDLE)trin->GetTransport(), dlg);
    
    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Dialogue send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send Dialogue." << endl;
        cout << "Error: " << ITS_GetErrorText( result ) << endl;
    }

    /* Free allocated memory*/
    if (srrrl)
    {
        delete srrrl;
    }

    if (encOctets)
    {
        delete encOctets;
    }

    srrrl = NULL;
    encOctets = NULL;

    return result;
}


/* termination handler*/

static void exitHandler(int sig)
{
    delete trin;
    delete trout;

    ITS_GlobalStop();

    exit(0);
}


/*.implementation:protected
 ****************************************************************************
 *  Purpose:
 *      To send a AnalyzedInformation result last using the WIN library.
 *
 *  Input Parameters:
 *      dlg - pointer to a TCAP_Dialogue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
SendAnalyzedInformationIL(TCAP_Dialogue *dlg)
{
    int result = ITS_SUCCESS;
    ITS_OCTET family = 0x00, code = 0x00;
    Octets *encOctets;
    TCAP_Invoke inv;
	aiID = dlg->GetDialogueID();

    AnalyzedInformationIL *aiil = new AnalyzedInformationIL();

    byte billingIdArray[7] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 };
	byte mscidArray[3] = { 0x04, 0x05, 0x06 };
	byte digitsArray[5] = { 0x12, 0x23, 0x34, 0x45, 0x56 };
    byte transactionCapabilityArray[5] = { 0x30, 0x32, 0x34, 0x36, 0x38 };
	byte triggerCapabilityArray[1] = { 0x03};

    byte callingPartyNum1Array[5] = { 0x04, 0x77, 0x62, 0x44, 0x25 };
    byte callingPartyNum2Array[5] = { 0x04, 0x77, 0x33, 0x14, 0x34 };
    byte callingPartySubaddrArray[5] = { 0x11, 0x22, 0x33, 0x44, 0x55 };
	byte conferenceCallIndArray[2] = { 0x23, 0x34 };
	byte esnArray[4] = { 0x11, 0x12, 0x13, 0x14 };
	byte locationAreaArray[2] = {0x33, 0x54};
	byte mobileDirectoryNumArray[5] = { 0x22, 0x34, 0x16, 0x24, 0x19}; 
    byte mscidNumArray[5] = { 0x12, 0x13, 0x14, 0x15, 0x16 };
	byte mobileidentificaitonnumberarray[5] = { 0x11, 0x22, 0x33, 0x44, 0x55 };
    byte redirectingNumDigitsArray[5] = { 0x10, 0x20, 0x30, 0x40, 0x50 };
	byte redirectingPartyNameArray[5] = {0x13, 0x14, 0x15, 0x21, 0x20};
    byte redirectingSubaddrArray[6] = { 0x11, 0x21, 0x31, 0x41, 0x51, 0x61 };
	byte servCellIDArray[2] = {0x32, 0x44};	
	byte tatArray[1] = {0x15};
    
    /* Set LocationRequest parameters*/
    

    // BillingID
    
    BillingID* billingId =
        new BillingID(FixedByteArrayToVector(billingIdArray));

    aiil->SetBillingID( billingId );

    
    // CallingPartyNumberDigits1
    
    CallingPartyNumberString1* callingPartyNum1 =
        new CallingPartyNumberString1(FixedByteArrayToVector(callingPartyNum1Array));

    aiil->SetCallingPartyNumberString1( callingPartyNum1 );

    
    // CallingPartyNumberDigits2
    
    CallingPartyNumberString2* callingPartyNum2
        = new CallingPartyNumberString2(FixedByteArrayToVector(callingPartyNum2Array));

    aiil->SetCallingPartyNumberString2( callingPartyNum2 ); 

    
    // CallingPartySubaddress
    
    CallingPartySubaddress* callingPartySubaddr =
        new CallingPartySubaddress(FixedByteArrayToVector(callingPartySubaddrArray));

    aiil->SetCallingPartySubaddress( callingPartySubaddr ); 

    // ConferenceCallingIndicator

	ConferenceCallingIndicator* cci = 
		new ConferenceCallingIndicator(FixedByteArrayToVector(conferenceCallIndArray));
    aiil->SetConferenceCallingIndicator(cci);


    // Digits
    
    Digits* digits = new Digits( FixedByteArrayToVector( digitsArray ) );

    aiil->SetDigits( digits ); 

	
	//Electronic Serial no.
	
	ElectronicSerialNumber* esn = new ElectronicSerialNumber( FixedByteArrayToVector( esnArray ) );
	
	aiil->SetElectronicSerialNumber(esn);

	// LocationAreaID

	LocationAreaID* laID =
		new LocationAreaID(FixedByteArrayToVector(locationAreaArray));
	aiil->SetLocationAreaID(laID);

	 // MobileDirectoryNumber
 
	MobileDirectoryNumber* mdn = 
		new MobileDirectoryNumber(FixedByteArrayToVector(mobileDirectoryNumArray));
	aiil->SetMobileDirectoryNumber(mdn);
	

	//MobileIdentificationNumber
	
    MobileIdentificationNumber* min = new MobileIdentificationNumber( FixedByteArrayToVector( mobileidentificaitonnumberarray ) );
	aiil->SetMobileIdentificationNumber(min);

	
	// MSCID
    
    MSCID* mscid = new MSCID( FixedByteArrayToVector( mscidArray ) );

    aiil->SetMSCID( mscid );

    
    // MSCIdentificationNumber
    
    MSCIdentificationNumber* mscIdentificationNum =
        new MSCIdentificationNumber( FixedByteArrayToVector( mscidNumArray) );

    aiil->SetMSCIdentificationNumber( mscIdentificationNum );

    
    // RedirectingNumberDigits
    
	RedirectingNumberDigits* redirectingNumDigits =
        new RedirectingNumberDigits(FixedByteArrayToVector(redirectingNumDigitsArray));

    aiil->SetRedirectingNumberDigits( redirectingNumDigits );

	// RedirectingPartyName

    RedirectingPartyName* rpn =
        new RedirectingPartyName(FixedByteArrayToVector(redirectingPartyNameArray));
    aiil->SetRedirectingPartyName( rpn );

    
    // RedirectingSubaddress
   
	RedirectingSubaddress* redirectingSubaddr =
        new RedirectingSubaddress(FixedByteArrayToVector(redirectingSubaddrArray));

    aiil->SetRedirectingSubaddress( redirectingSubaddr );

	// ServingCellID

	ServingCellID* sid =
		new ServingCellID(FixedByteArrayToVector(servCellIDArray));
	aiil->SetServingCellID(sid);

	// SystemMyTypeCode

	SystemMyTypeCode smtc;
	smtc.SetTelos();
	aiil->SetSystemMyTypeCode(smtc);

	// TerminationAccessType

	TerminationAccessType* tat =
		new TerminationAccessType(FixedByteArrayToVector(tatArray));
	aiil->SetTerminationAccessType(tat);

        
    // TransactionCapability
    
    TransactionCapability* transactionCapability =
        new TransactionCapability(FixedByteArrayToVector(transactionCapabilityArray));

    aiil->SetTransactionCapability( transactionCapability );

	// TriggerType

	TriggerType triggerType;
	triggerType.SetAllCalls();
	aiil->SetTriggerType(triggerType);
    
   
	// wINCapability
    WINCapability* wINCapability = new WINCapability();
	TriggerCapability* triggerCapability = 
		new TriggerCapability(FixedByteArrayToVector(triggerCapabilityArray));
    wINCapability->SetTriggerCapability(triggerCapability);
	aiil->SetWINCapability(wINCapability);

	
    /*Encode IS41 message*/
    
    EncodeMsg( aiil, &encOctets );

    inv.SetTimeOut( 90 );
    inv.SetInvokeID( 1 );
    inv.SetOperation(true, 64, OP_AnalyzedInformation);
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    traceComponent( &inv );

    /* Send an LocationRequest invoke component*/
    result = TCAP_Component::Send((ITS_HANDLE)trin->GetTransport(), dlg, &inv);

    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "AnalyzedInformation invoke send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send AnalyzedInformation invoke." << endl;
        cout << "Error: " << ITS_GetErrorText( result ) << endl;
    }

    /* Send dialog*/
    result = TCAP_Dialogue::Send((ITS_HANDLE)trin->GetTransport(), dlg);
    
    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Dialogue send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send Dialogue." << endl;
        cout << "Error: " << ITS_GetErrorText( result ) << endl;
    }


    /* Free allocated memory*/
    if (aiil)
    {
        delete aiil;
    }

    if (encOctets)
    {
        delete encOctets;
    }

    aiil = NULL;
    encOctets = NULL;

    return result;
}


/*.implementation:protected
 ****************************************************************************
 *  Purpose:
 *      To send a AnalyzedInformation result last using the WIN library.
 *
 *  Input Parameters:
 *      dlg - pointer to a TCAP_Dialogue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/

int
SendAnalyzedInformationRRL(TCAP_Dialogue *dlg, TCAP_Component *recvCpt)
{
    int result = ITS_SUCCESS;
    ITS_OCTET family = 0x00, code = 0x00;
    Octets *encOctets = NULL;
    TCAP_Result res;
	
    AnalyzedInformationRRL *airrl = new AnalyzedInformationRRL();

	byte actionCodeArray[2] = { 0x91, 0x87 };
    byte announcementCodeArray1[5] = { 0x01, 0x02, 0x03, 0x04, 0x05 };
    byte announcementCodeArray2[5] = { 0x11, 0x12, 0x13, 0x14, 0x15 };
	byte carrierDigitsArray[5] = { 0x04, 0x77, 0x22, 0x99, 0x24 };
	byte conferenceCallIndArray[2] = { 0x23, 0x45 };
    byte digitsArray[5] = { 0x11, 0x22, 0x33, 0x44, 0x55 };
    byte displayTextArray[2] = {0x32, 0x33};
	byte dMHbillingdigitsArray[5] = { 0x01, 0x02, 0x03, 0x04, 0x05 }; 
	byte dMHaccountCodeArray[5] = { 0x02, 0x03, 0x04, 0x05, 0x08 };
	byte dMHaltBillDigitsArray[6] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
	byte noAnswerTArray[2] = { 0x34, 0x12 };
    byte oneTimeFeatureIndArray[2]= { 0x45, 0x58 };
    byte routingDigitsArray[5] = { 0x04, 0x77, 0x23, 0x78, 0x99 };
    byte terminationTriggersArray[2] = { 0x01, 0x02 };

	byte destinationDigitsArray[5] = { 0x91, 0x02, 0x16, 0x27, 0x15 };
    byte mscidArray[3] = { 0x07, 0x05, 0x09 };

	byte globalTitleArray[2] = {0x41, 0x32};
	byte pcSSNArray[5] = {0x11, 0x12, 0x13, 0x14, 0x15};
	byte winTriggListArray[2] = {0x23, 0x34};
    
    /* Set LocationRequest result parameters*/
     

	//AccessDeniedReason
	
    AccessDeniedReason accessDeniedReason;
    accessDeniedReason.SetBusy();
    airrl->SetAccessDeniedReason( accessDeniedReason );

    // ActionCode

    ActionCode* actionCode =
		new ActionCode(FixedByteArrayToVector(actionCodeArray));
	airrl->SetActionCode(actionCode);
    
    // AnnouncementList
    
    AnnouncementCode* announcementCode1 =
        new AnnouncementCode(FixedByteArrayToVector(announcementCodeArray1));
    
    AnnouncementCode* announcementCode2 =
        new AnnouncementCode(FixedByteArrayToVector(announcementCodeArray2));
    
    AnnouncementList::CHOICE choice1;
    choice1.SetChoiceAnnouncementCode( announcementCode1 );

    AnnouncementList::CHOICE choice2;
    choice2.SetChoiceAnnouncementCode( announcementCode2 );

    AnnouncementList announcementList;
    announcementList.AddElement( choice1);
    announcementList.AddElement( choice2);

    airrl->SetAnnouncementList( announcementList );
    
    // DigitsCarrier
    
    CarrierDigits* carrierDigits =
        new CarrierDigits(FixedByteArrayToVector(carrierDigitsArray));
    airrl->SetCarrierDigits( carrierDigits );

	// ConferenceCallingIndicator

	ConferenceCallingIndicator* cci = 
		new ConferenceCallingIndicator(FixedByteArrayToVector(conferenceCallIndArray));
    airrl->SetConferenceCallingIndicator(cci);

	// DisplayText
    
    DisplayText* dt =
        new DisplayText(FixedByteArrayToVector(displayTextArray));
    airrl->SetDisplayText( dt );

	 // DMHBillingID
    
    DMH_BillingDigits* dMH_billingDigits =
        new DMH_BillingDigits(FixedByteArrayToVector(dMHbillingdigitsArray));
    airrl->SetDMH_BillingDigits( dMH_billingDigits );

   // DMHAccountCode

	DMH_AccountCodeDigits* dmha =
		new DMH_AccountCodeDigits(FixedByteArrayToVector(dMHaccountCodeArray));
	airrl->SetDMH_AccountCodeDigits(dmha);

    // DMHAlternateBillingID
    
    DMH_AlternateBillingDigits* dmhab =
        new DMH_AlternateBillingDigits(FixedByteArrayToVector(dMHaltBillDigitsArray));
    airrl->SetDMH_AlternateBillingDigits( dmhab );

	// DMHRedirectionIndicator

	DMH_RedirectionIndicator dmhr;
	dmhr.SetCFU();
	airrl->SetDMH_RedirectionIndicator(dmhr);


	// NoAnswerTime

	NoAnswerTime* nat = 
		new NoAnswerTime(FixedByteArrayToVector(noAnswerTArray));
	airrl->SetNoAnswerTime(nat);

	// OneTimeFeatureIndicator
     
	OneTimeFeatureIndicator* otfi = 
		new OneTimeFeatureIndicator( FixedByteArrayToVector( oneTimeFeatureIndArray) );
    airrl->SetOneTimeFeatureIndicator(otfi);

	 // ResumePIC

	ResumePIC rPIC;
	rPIC.SetSelectRoutePIC();
	airrl->SetResumePIC(rPIC);

    // RoutingDigits
    
    RoutingDigits* routingDigits =
        new RoutingDigits(FixedByteArrayToVector(routingDigitsArray));
    airrl->SetRoutingDigits( routingDigits );

	//TerminationList   

	DestinationDigits* dd =
        new DestinationDigits(FixedByteArrayToVector(destinationDigitsArray));
    
	MSCID* mscid = new MSCID( FixedByteArrayToVector( mscidArray ));
    
	IntersystemTermination ist;
	ist.SetDestinationDigits(dd);
	ist.SetMSCID(mscid);

	TerminationList::CHOICE ch;  
	ch.SetChoiceIntersystemTermination(ist);

    TerminationList tl;
	tl.AddElement(ch);

	airrl->SetTerminationList(tl);

	// TerminationTriggers

	TerminationTriggers* tt = 
		new TerminationTriggers(FixedByteArrayToVector(terminationTriggersArray));
	airrl->SetTerminationTriggers(tt);

	// TriggerAddressList

	GlobalTitle* gt = new GlobalTitle(FixedByteArrayToVector(globalTitleArray));
	PC_SSN* pcssn = new PC_SSN(FixedByteArrayToVector(pcSSNArray));
	WINTriggerList* wint =
		new WINTriggerList(FixedByteArrayToVector(winTriggListArray));

	DestinationAddress da;
	da.SetChoiceGlobalTitle(gt);
	da.SetChoicePC_SSN(pcssn);

	TriggerList trl;
	trl.SetDestinationAddress(da);
	trl.SetWINTriggerList(wint);

	TriggerAddressList::SET set;
	set.SetTriggerList(trl);

	TriggerAddressList tal;
	tal.AddElement(set);

	airrl->SetTriggerAddressList(tal);
	

    /* Encode WIN message*/
    EncodeMsg( airrl, &encOctets );

    res.SetInvokeID( 1/*recvCpt->GetInvokeID() */);
    res.SetParameter( const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                      encOctets->GetLength());

    /* Printout result information*/
    traceComponent( &res );

    /* Send an LocationRequest result component*/
    result = TCAP_Component::Send((ITS_HANDLE)trin->GetTransport(), dlg,
                                  &res);

    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "AnalyzedInformation ReturnResultLast send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send AnalyzedInformation ReturnResultLast." << endl;
        cout << "Error: " << result << endl;
    }

    /* Send dialog*/
    result = TCAP_Dialogue::Send((ITS_HANDLE)trin->GetTransport(), dlg);
    
    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Dialogue send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send Dialogue." << endl;
        cout << "Error: " << ITS_GetErrorText( result ) << endl;
    }

    /* Free allocated memory*/
    if (airrl)
    {
        delete airrl;
    }

    if (encOctets)
    {
        delete encOctets;
    }

    airrl = NULL;
    encOctets = NULL;

    return result;
}

/*.implementation:protected
 ****************************************************************************
 *  Purpose:
 *      To send a  ConnectionFailureReport invoke last using the WIN library.
 *
 *  Input Parameters:
 *      dlg - pointer to a TCAP_Dialogue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
SendConnectionFailureReportIL(TCAP_Dialogue *dlg)
{
    int result = ITS_SUCCESS;
    ITS_OCTET family = 0x00, code = 0x00;
    Octets *encOctets;
    TCAP_Invoke inv;
    ConnectionFailureReportIL *cfril = new ConnectionFailureReportIL();

	byte failureCauseArray[2] = { 0x01, 0x02 };

	/*Set LocationRequest result parameters*/

    // FailureType

	FailureType failureType;
	failureType.SetNotUsed();
	cfril->SetFailureType(failureType);

    // FailureCause

    FailureCause* failureCause =
        new FailureCause(FixedByteArrayToVector(failureCauseArray));
    cfril->SetFailureCause( failureCause );

	/*Encode IS41 message*/
    
    EncodeMsg( cfril, &encOctets );

    inv.SetTimeOut( 90 );
    inv.SetInvokeID( 1 );
    inv.SetOperation(true, 65, OP_ConnectionFailureReport);
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    traceComponent( &inv );

    /* Send an LocationRequest invoke component*/
    result = TCAP_Component::Send((ITS_HANDLE)trin->GetTransport(), dlg, &inv);

    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "ConnectionFailureReport invoke send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send ConnectionFailureReport invoke." << endl;
        cout << "Error: " << ITS_GetErrorText( result ) << endl;
    }

    // Send dialog
    result = TCAP_Dialogue::Send((ITS_HANDLE)trin->GetTransport(), dlg);
    
    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Dialogue send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send Dialogue." << endl;
        cout << "Error: " << ITS_GetErrorText( result ) << endl;
    }

	
	
// Free allocated memory
    if (cfril)
    {
        delete cfril;
    }

    if (encOctets)
    {
        delete encOctets;
    }

    cfril = NULL;
    encOctets = NULL;

    return result;
}


/*.implementation:protected
 ****************************************************************************
 *  Purpose:
 *      To send a ConnectResource invoke last using the WIN library.
 *
 *  Input Parameters:
 *      dlg - pointer to a TCAP_Dialogue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
SendConnectResourceIL(TCAP_Dialogue *dlg)
{
    int result = ITS_SUCCESS;
    ITS_OCTET family = 0x00, code = 0x00;
    Octets *encOctets;
    TCAP_Invoke inv;
    ConnectResourceIL *cril = new ConnectResourceIL();

	byte destinationDigitsArray[5] = { 0x01, 0x02, 0x11, 0x23, 0x14 };
    byte digitsCarrierArray[5] = { 0x11, 0x22, 0x33, 0x14, 0x56 };
    byte routingDigitsArray[5] = { 0x04, 0x77, 0x23, 0x78, 0x91 };


	/*Set LocationRequest result parameters*/

    // DestinationDigits

    
    DestinationDigits* destinationDigits =
        new DestinationDigits(FixedByteArrayToVector(destinationDigitsArray));
    cril->SetDestinationDigits( destinationDigits );


    // CarrierDigits

	CarrierDigits* carrierDigits =
        new CarrierDigits(FixedByteArrayToVector(digitsCarrierArray));
    cril->SetCarrierDigits( carrierDigits );

     
    // RoutingDigits
    
    RoutingDigits* routingDigits =
        new RoutingDigits(FixedByteArrayToVector(routingDigitsArray));
    cril->SetRoutingDigits( routingDigits );


	/*Encode IS41 message*/
    
    EncodeMsg( cril, &encOctets );

    inv.SetTimeOut( 90 );
    inv.SetInvokeID( 1 );
    inv.SetOperation(true, 66, OP_ConnectResource);
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    traceComponent( &inv );

    /* Send an LocationRequest invoke component*/
    result = TCAP_Component::Send((ITS_HANDLE)trin->GetTransport(), dlg, &inv);

    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "ConnectResource invoke send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send ConnectResource invoke." << endl;
        cout << "Error: " << ITS_GetErrorText( result ) << endl;
    }

    // Send dialog
    result = TCAP_Dialogue::Send((ITS_HANDLE)trin->GetTransport(), dlg);
    
    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Dialogue send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send Dialogue." << endl;
        cout << "Error: " << ITS_GetErrorText( result ) << endl;
    }

	
	
// Free allocated memory
    if (cril)
    {
        delete cril;
    }

    if (encOctets)
    {
        delete encOctets;
    }

    cril = NULL;
    encOctets = NULL;

    return result;
}


/*.implementation:protected
 ****************************************************************************
 *  Purpose:
 *      To send a FacilitySelectedAndAvail invoke last using the WIN library.
 *
 *  Input Parameters:
 *      dlg - pointer to a TCAP_Dialogue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
SendFacilitySelectedAndAvailableIL(TCAP_Dialogue *dlg)
{
    int result = ITS_SUCCESS;
    ITS_OCTET family = 0x00, code = 0x00;
    Octets *encOctets;
    TCAP_Invoke inv;
	fsaID = dlg->GetDialogueID();

    FacilitySelectedAndAvailableIL *fsaail = new FacilitySelectedAndAvailableIL();
	
    byte billingIdArray[7] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 };
	byte mscidArray[3] = { 0x04, 0x05, 0x06 };
	byte digitsArray[5] = { 0x12, 0x23, 0x34, 0x45, 0x56 };
    byte transactionCapabilityArray[5] = { 0x30, 0x32, 0x34, 0x36, 0x38 };
	byte triggerCapabilityArray[1] = { 0x03};

    byte callingPartyNum1Array[5] = { 0x04, 0x77, 0x62, 0x44, 0x25 };
    byte callingPartyNum2Array[5] = { 0x04, 0x77, 0x33, 0x14, 0x34 };
    byte callingPartySubaddrArray[5] = { 0x11, 0x22, 0x33, 0x44, 0x55 };
	byte esnArray[4] = { 0x11, 0x12, 0x13, 0x14 };
	byte groupInfoArray[4] = { 0x13, 0x23, 0x33, 0x34 };
	byte legInfoArray[4] = {0x11, 0x12, 0x23, 0x24};
	byte locationAreaArray[2] = {0x33, 0x34};
	byte mdnArray[5] = { 0x04, 0x77, 0x28, 0x44, 0x87 };
	byte mobileidentificaitonnumberarray[5] = { 0x11, 0x22, 0x33, 0x44, 0x55 };
    byte mscidNumArray[5] = { 0x12, 0x13, 0x14, 0x15, 0x16 };

	byte mscinArray[5] = { 0x01, 0x02, 0x03, 0x04, 0x05};
	byte oneTimeFeatureIndArray[2]= { 0x40, 0x42 };
	byte pilotBillIDArray[7] = {0x10, 0x22, 0x30, 0x40, 0x51, 0x43, 0x12};
	byte pilotNumberArray[5] = {0x10, 0x22, 0x30, 0x40, 0x51};	
	byte preferredLangIndArray[2] = { 0x04, 0x11 };
	byte redirectingNumDigitsArray[5] = { 0x10, 0x20, 0x30, 0x40, 0x50 };
	byte redirectingPartyNameArray[5] = {0x13, 0x14, 0x15, 0x16, 0x17};	
    byte redirectingSubaddrArray[6] = { 0x01, 0x21, 0x31, 0x41, 0x51, 0x27 };
	byte servCellIDArray[2] = {0x22, 0x44};
	
	byte tatArray[1] = {0x12};
	
    
    /* Set LocationRequest parameters*/
    

    // BillingID
    
    BillingID* billingId =
        new BillingID(FixedByteArrayToVector(billingIdArray));

    fsaail->SetBillingID( billingId );

    
    // CallingPartyNumberDigits1
    
    CallingPartyNumberDigits1* callingPartyNum1 =
        new CallingPartyNumberDigits1(FixedByteArrayToVector(callingPartyNum1Array));

    fsaail->SetCallingPartyNumberDigits1( callingPartyNum1 );

    
    // CallingPartyNumberDigits2
    
    CallingPartyNumberDigits2* callingPartyNum2
        = new CallingPartyNumberDigits2(FixedByteArrayToVector(callingPartyNum2Array));

    fsaail->SetCallingPartyNumberDigits2( callingPartyNum2 ); 

    
    // CallingPartySubaddress
    
    CallingPartySubaddress* callingPartySubaddr =
        new CallingPartySubaddress(FixedByteArrayToVector(callingPartySubaddrArray));

    fsaail->SetCallingPartySubaddress( callingPartySubaddr ); 

	
	//Electronic Serial no.
	
	ElectronicSerialNumber* esn = new ElectronicSerialNumber( FixedByteArrayToVector( esnArray ) );
	
	fsaail->SetElectronicSerialNumber(esn);

	//GroupInformation

	GroupInformation* gi = 
		new GroupInformation(FixedByteArrayToVector(groupInfoArray));
	fsaail->SetGroupInformation(gi);

	//LegInformation

	LegInformation* li = 
		new LegInformation(FixedByteArrayToVector(legInfoArray));
	fsaail->SetLegInformation(li);

	// LocationAreaID

	LocationAreaID* laID =
		new LocationAreaID(FixedByteArrayToVector(locationAreaArray));
	fsaail->SetLocationAreaID(laID);
    
    // MobileDirectoryNumber
    
    MobileDirectoryNumber* mdn =
        new MobileDirectoryNumber(FixedByteArrayToVector(mdnArray));
    fsaail->SetMobileDirectoryNumber( mdn );

	
	//MobileIdentificationNumber
	
    MobileIdentificationNumber* min = new MobileIdentificationNumber( FixedByteArrayToVector( mobileidentificaitonnumberarray ) );
	fsaail->SetMobileIdentificationNumber(min);

	
	// MSCID
    
    MSCID* mscid = new MSCID( FixedByteArrayToVector( mscidArray ) );

    fsaail->SetMSCID( mscid );

    
    // MSCIdentificationNumber
    
    MSCIdentificationNumber* mscIdentificationNum =
        new MSCIdentificationNumber( FixedByteArrayToVector( mscidNumArray) );

    fsaail->SetMSCIdentificationNumber( mscIdentificationNum );

    
	// OneTimeFeatureIndicator

	OneTimeFeatureIndicator* otfi = 
		new OneTimeFeatureIndicator( FixedByteArrayToVector( oneTimeFeatureIndArray) );
    fsaail->SetOneTimeFeatureIndicator(otfi);

	// PilotBillingID

	PilotBillingID* pb =
		new PilotBillingID(FixedByteArrayToVector(pilotBillIDArray));
	fsaail->SetPilotBillingID(pb);

	// PilotNumber

	PilotNumber* pn =
		new PilotNumber(FixedByteArrayToVector(pilotNumberArray));
	fsaail->SetPilotNumber(pn);

	// PreferredLanguageIndicator

	PreferredLanguageIndicator* pli =
		new PreferredLanguageIndicator(FixedByteArrayToVector(preferredLangIndArray));
	fsaail->SetPreferredLanguageIndicator(pli);

	// RedirectingPartyName
    
    RedirectingPartyName* rpn =
        new RedirectingPartyName(FixedByteArrayToVector(redirectingPartyNameArray));
    fsaail->SetRedirectingPartyName( rpn );

    
    // RedirectingNumberDigits
    
	RedirectingNumberDigits* redirectingNumDigits =
        new RedirectingNumberDigits(FixedByteArrayToVector(redirectingNumDigitsArray));

    fsaail->SetRedirectingNumberDigits( redirectingNumDigits );

    
    // RedirectingSubaddress
   
	RedirectingSubaddress* redirectingSubaddr =
        new RedirectingSubaddress(FixedByteArrayToVector(redirectingSubaddrArray));

    fsaail->SetRedirectingSubaddress( redirectingSubaddr );

	// ServingCellID

	ServingCellID* sid =
		new ServingCellID(FixedByteArrayToVector(servCellIDArray));
	fsaail->SetServingCellID(sid);

	// SystemMyTypeCode

	SystemMyTypeCode smtc;
	smtc.SetTelos();
	fsaail->SetSystemMyTypeCode(smtc);


    // TerminationAccessType

	TerminationAccessType* tat =
		new TerminationAccessType(FixedByteArrayToVector(tatArray));
	fsaail->SetTerminationAccessType(tat);

    // TransactionCapability
    
    TransactionCapability* transactionCapability =
        new TransactionCapability(FixedByteArrayToVector(transactionCapabilityArray));

    fsaail->SetTransactionCapability( transactionCapability );


	// TriggerType

	TriggerType triggerType;
	triggerType.SetAllCalls();
	fsaail->SetTriggerType(triggerType);
    
   
	// wINCapability
    WINCapability* wINCapability = new WINCapability();
	TriggerCapability* triggerCapability = 
		new TriggerCapability(FixedByteArrayToVector(triggerCapabilityArray));
    wINCapability->SetTriggerCapability(triggerCapability);
	fsaail->SetWINCapability(wINCapability);



	/*Encode IS41 message*/
    
    EncodeMsg( fsaail , &encOctets );

    inv.SetTimeOut( 90 );
    inv.SetInvokeID( 1 );
    inv.SetOperation(true, 68, OP_FacilitySelectedAndAvailable);
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    traceComponent( &inv );

    /* Send an LocationRequest invoke component*/
    result = TCAP_Component::Send((ITS_HANDLE)trin->GetTransport(), dlg, &inv);

    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "FacilitySelectedAndAvailable invoke send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send FacilitySelectedAndAvailable invoke." << endl;
        cout << "Error: " << ITS_GetErrorText( result ) << endl;
    }

    // Send dialog
    result = TCAP_Dialogue::Send((ITS_HANDLE)trin->GetTransport(), dlg);
    
    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Dialogue send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send Dialogue." << endl;
        cout << "Error: " << ITS_GetErrorText( result ) << endl;
    }

		
// Free allocated memory
    
	if (fsaail)
    {
        delete fsaail;
    }

    if (encOctets)
    {
        delete encOctets;
    }

    fsaail = NULL;
    encOctets = NULL;

    return result;
}


/*.implementation:protected
 ****************************************************************************
 *  Purpose:
 *      To send a FacilitySelectedAndAvailable result last using the WIN library.
 *
 *  Input Parameters:
 *      dlg - pointer to a TCAP_Dialogue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/

int
SendFacilitySelectedAndAvailableRRL(TCAP_Dialogue *dlg, TCAP_Component *recvCpt)
{
    int result = ITS_SUCCESS;
    ITS_OCTET family = 0x00, code = 0x00;
    Octets *encOctets = NULL;
    TCAP_Result res;

    FacilitySelectedAndAvailableRRL *fsaarrl = 
		new FacilitySelectedAndAvailableRRL();
    
	byte actionCodeArray[2] = { 0x90, 0x80 };
	byte alertCodeArray[2] = { 0x36, 0x65 };
    byte announcementCodeArray1[5] = { 0x01, 0x02, 0x03, 0x04, 0x05 };
    byte announcementCodeArray2[5] = { 0x11, 0x12, 0x13, 0x14, 0x15 };   
	byte displayTextArray[2] = {0x32, 0x33};
	byte dMHaccountCodeArray[5] = { 0x02, 0x03, 0x04, 0x05, 0x08 };
	byte dMHaltBillDigitsArray[5] = { 0x31, 0x02, 0x03, 0x04, 0x12 };
	byte dMHbillingdigitsArray[7] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07}; 
	byte noAnswerTArray[2] = { 0x34, 0x12 };
    byte oneTimeFeatureIndArray[2]= { 0x24, 0x50 };
    byte terminationTriggersArray[2] = { 0x01, 0x02 };

    byte globalTitleArray[2] = {0x41, 0x32};
	byte pcSSNArray[5] = {0x11, 0x12, 0x13, 0x14, 0x15};
	byte winTriggListArray[2] = {0x23, 0x34};


    /* Set LocationRequest result parameters*/
     

	//AccessDeniedReason
	
    AccessDeniedReason accessDeniedReason;
    accessDeniedReason.SetNoPageResponse();
    fsaarrl->SetAccessDeniedReason( accessDeniedReason );

    // ActionCode

    ActionCode* actionCode =
		new ActionCode(FixedByteArrayToVector(actionCodeArray));
	fsaarrl->SetActionCode(actionCode);

	// AlertCode

    AlertCode* alertCode =
		new AlertCode(FixedByteArrayToVector(alertCodeArray));
	fsaarrl->SetAlertCode(alertCode);
    
    // AnnouncementList
    
    AnnouncementCode* announcementCode1 =
        new AnnouncementCode(FixedByteArrayToVector(announcementCodeArray1));
    
    AnnouncementCode* announcementCode2 =
        new AnnouncementCode(FixedByteArrayToVector(announcementCodeArray2));
    
    AnnouncementList::CHOICE choice1;
    choice1.SetChoiceAnnouncementCode( announcementCode1 );

    AnnouncementList::CHOICE choice2;
    choice2.SetChoiceAnnouncementCode( announcementCode2 );

    AnnouncementList announcementList;
    announcementList.AddElement( choice1);
    announcementList.AddElement( choice2);

    fsaarrl->SetAnnouncementList( announcementList );
    
    // DisplayText
    
    DisplayText* dt =
        new DisplayText(FixedByteArrayToVector(displayTextArray));
    fsaarrl->SetDisplayText( dt );

	 // DMHBillingID
    
    DMH_BillingDigits* dMH_billingDigits =
        new DMH_BillingDigits(FixedByteArrayToVector(dMHbillingdigitsArray));
    fsaarrl->SetDMH_BillingDigits( dMH_billingDigits );
    
	// DMHAccountCode

	DMH_AccountCodeDigits* dmha =
		new DMH_AccountCodeDigits(FixedByteArrayToVector(dMHaccountCodeArray));
	fsaarrl->SetDMH_AccountCodeDigits(dmha);

    // DMHAlternateBillingID
    
    DMH_AlternateBillingDigits* dmhab =
        new DMH_AlternateBillingDigits(FixedByteArrayToVector(dMHaltBillDigitsArray));
    fsaarrl->SetDMH_AlternateBillingDigits( dmhab );

	// DMHRedirectionIndicator

	DMH_RedirectionIndicator dmhr;
	dmhr.SetCFU();
	fsaarrl->SetDMH_RedirectionIndicator(dmhr);

	// NoAnswerTime

	NoAnswerTime* nat = 
		new NoAnswerTime(FixedByteArrayToVector(noAnswerTArray));
	fsaarrl->SetNoAnswerTime(nat);


	// OneTimeFeatureIndicator
     
	OneTimeFeatureIndicator* otfi = 
		new OneTimeFeatureIndicator( FixedByteArrayToVector( oneTimeFeatureIndArray) );
    fsaarrl->SetOneTimeFeatureIndicator(otfi);

	// ResumePIC

	ResumePIC rPIC;
	rPIC.SetSelectRoutePIC();
	fsaarrl->SetResumePIC(rPIC);

	// TerminationTriggers

	TerminationTriggers* tt = 
		new TerminationTriggers(FixedByteArrayToVector(terminationTriggersArray));
	fsaarrl->SetTerminationTriggers(tt);

	// TriggerAddressList

	GlobalTitle* gt = new GlobalTitle(FixedByteArrayToVector(globalTitleArray));
	PC_SSN* pcssn = new PC_SSN(FixedByteArrayToVector(pcSSNArray));
	WINTriggerList* wint =
		new WINTriggerList(FixedByteArrayToVector(winTriggListArray));

	DestinationAddress da;
	da.SetChoiceGlobalTitle(gt);
	da.SetChoicePC_SSN(pcssn);

	TriggerList trl;
	trl.SetDestinationAddress(da);
	trl.SetWINTriggerList(wint);

	TriggerAddressList::SET set;
	set.SetTriggerList(trl);

	TriggerAddressList tal;
	tal.AddElement(set);

	fsaarrl->SetTriggerAddressList(tal);
	

    /* Encode WIN message*/

    EncodeMsg( fsaarrl, &encOctets );

    res.SetInvokeID( 1/*recvCpt->GetInvokeID() */);
    res.SetParameter( const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                      encOctets->GetLength());

    /* Printout result information*/
    traceComponent( &res );

    /* Send an LocationRequest result component*/
    result = TCAP_Component::Send((ITS_HANDLE)trin->GetTransport(), dlg,
                                  &res);

    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Facility ReturnResultLast send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send Facility ReturnResultLast." << endl;
        cout << "Error: " << result << endl;
    }

    /* Send dialog*/
    result = TCAP_Dialogue::Send((ITS_HANDLE)trin->GetTransport(), dlg);
    
    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Dialogue send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send Dialogue." << endl;
        cout << "Error: " << ITS_GetErrorText( result ) << endl;
    }

    /* Free allocated memory*/
    if (fsaarrl)
    {
        delete fsaarrl;
    }

    if (encOctets)
    {
        delete encOctets;
    }

    fsaarrl = NULL;
    encOctets = NULL;

    return result;
}


/*.implementation:protected
 ****************************************************************************
 *  Purpose:
 *      To send a SeizeResource invoke last using the WIN library.
 *
 *  Input Parameters:
 *      dlg - pointer to a TCAP_Dialogue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
SendSeizeResourceIL(TCAP_Dialogue *dlg)
{
    int result = ITS_SUCCESS;
    ITS_OCTET family = 0x00, code = 0x00;
    Octets *encOctets;
    TCAP_Invoke inv;
	sreID = dlg->GetDialogueID();

    SeizeResourceIL *sreil = new SeizeResourceIL();

	byte privateSpecResArray[2] = { 0x01, 0x02 };
	byte preferredLangIndArray[2] = { 0x03, 0x12 };
	byte specializedResourceArray[2] = { 0x11, 0x22 };

	/*Set LocationRequest result parameters*/

    // PrivateSpecializedResource

	PrivateSpecializedResource* privateSpec =
		new PrivateSpecializedResource(FixedByteArrayToVector(privateSpecResArray));
	sreil->SetPrivateSpecializedResource(privateSpec);
    

	// PreferredLanguageIndicator

	PreferredLanguageIndicator* pli =
		new PreferredLanguageIndicator(FixedByteArrayToVector(preferredLangIndArray));
	sreil->SetPreferredLanguageIndicator(pli);


	/*Encode IS41 message*/
    
    EncodeMsg( sreil, &encOctets );

    inv.SetTimeOut( 90 );
    inv.SetInvokeID( 1 );
    inv.SetOperation(true, 73, OP_SeizeResource);
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    traceComponent( &inv );

    /* Send an LocationRequest invoke component*/
    result = TCAP_Component::Send((ITS_HANDLE)trin->GetTransport(), dlg, &inv);

    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "SeizeResource invoke send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send SeizeResource invoke." << endl;
        cout << "Error: " << ITS_GetErrorText( result ) << endl;
    }

    // Send dialog
    result = TCAP_Dialogue::Send((ITS_HANDLE)trin->GetTransport(), dlg);
    
    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Dialogue send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send Dialogue." << endl;
        cout << "Error: " << ITS_GetErrorText( result ) << endl;
    }

	
	
// Free allocated memory
    if (sreil)
    {
        delete sreil;
    }

    if (encOctets)
    {
        delete encOctets;
    }

    sreil = NULL;
    encOctets = NULL;

    return result;
}

/*.implementation:protected
 ****************************************************************************
 *  Purpose:
 *      To send a SeizeResource result last using the WIN library.
 *
 *  Input Parameters:
 *      dlg - pointer to a TCAP_Dialogue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
SendSeizeResourceRRL(TCAP_Dialogue *dlg, TCAP_Component *recvCpt)
{
    int result = ITS_SUCCESS;
    ITS_OCTET family = 0x00, code = 0x00;
    Octets *encOctets = NULL;
    TCAP_Result res;

    SeizeResourceRRL *srerrl = new SeizeResourceRRL();
    
    byte destinationDigitsArray[5] = { 0x91, 0x92, 0x93, 0x94, 0x95 };


    /* Set LocationRequest result parameters*/
     
    // DestinationDigits
	
	DestinationDigits* destinationDigits =
        new DestinationDigits(FixedByteArrayToVector(destinationDigitsArray));
    srerrl->SetDestinationDigits( destinationDigits );

    /* Encode WIN message*/
    EncodeMsg( srerrl, &encOctets );

    res.SetInvokeID( 1/*recvCpt->GetInvokeID() */);
    res.SetParameter( const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                      encOctets->GetLength());

    /* Printout result information*/
    traceComponent( &res );

    /* Send an LocationRequest result component*/
    result = TCAP_Component::Send((ITS_HANDLE)trin->GetTransport(), dlg,
                                  &res);

    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "SeizeResource ReturnResultLast send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send SeizeResource ReturnResultLast." << endl;
        cout << "Error: " << result << endl;
    }

    /* Send dialog*/
    result = TCAP_Dialogue::Send((ITS_HANDLE)trin->GetTransport(), dlg);
    
    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Dialogue send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send Dialogue." << endl;
        cout << "Error: " << ITS_GetErrorText( result ) << endl;
    }

    /* Free allocated memory*/
    if (srerrl)
    {
        delete srerrl;
    }

    if (encOctets)
    {
        delete encOctets;
    }

    srerrl = NULL;
    encOctets = NULL;

    return result;
}


/*.implementation:protected
 ****************************************************************************
 *  Purpose:
 *      To send a SRFDirective invoke last using the WIN library.
 *
 *  Input Parameters:
 *      dlg - pointer to a TCAP_Dialogue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
SendSRFDirectiveIL(TCAP_Dialogue *dlg)
{
    int result = ITS_SUCCESS;
    ITS_OCTET family = 0x00, code = 0x00;
    Octets *encOctets;
    TCAP_Invoke inv;
	sdID = dlg->GetDialogueID();

    SRFDirectiveIL *sdil = new SRFDirectiveIL();

	byte announcementCodeArray[5] = { 0x01, 0x02, 0x03, 0x04, 0x05 };
	byte digitCollCtrlArray[12] = { 0x01, 0x02, 0x12, 0x34, 0x45, 0x13, 0x22, 
		                            0x26, 0x76, 0x46, 0x54, 0x79 };
    byte scriptNameArray[2] = {0x22, 0x23};

	/*Set LocationRequest result parameters*/


    // AnnouncementList
    
    AnnouncementCode* announcementCode =
        new AnnouncementCode(FixedByteArrayToVector(announcementCodeArray));
    
    AnnouncementList::CHOICE choice;
    choice.SetChoiceAnnouncementCode( announcementCode );

    AnnouncementList announcementList;
    announcementList.AddElement( choice);

    sdil->SetAnnouncementList( announcementList );


    // DigitCollectionControl

	DigitCollectionControl* dcc =
		new DigitCollectionControl(FixedByteArrayToVector(digitCollCtrlArray));
	sdil->SetDigitCollectionControl(dcc);
    

	// ExecuteScript

	ExecuteScript* es = new ExecuteScript();
	ScriptName* sn = new ScriptName(FixedByteArrayToVector(scriptNameArray));	
    es->SetScriptName(sn);
	sdil->SetExecuteScript(es);

	
	/*Encode IS41 message*/
    
    EncodeMsg( sdil, &encOctets );

    inv.SetTimeOut( 90 );
    inv.SetInvokeID( 1 );
    inv.SetOperation(true, 74, OP_SRFDirective);
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    traceComponent( &inv );

    /* Send an LocationRequest invoke component*/
    result = TCAP_Component::Send((ITS_HANDLE)trin->GetTransport(), dlg, &inv);

    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "SRFDirective invoke send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send SRFDirective invoke." << endl;
        cout << "Error: " << ITS_GetErrorText( result ) << endl;
    }

    // Send dialog
    result = TCAP_Dialogue::Send((ITS_HANDLE)trin->GetTransport(), dlg);
    
    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Dialogue send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send Dialogue." << endl;
        cout << "Error: " << ITS_GetErrorText( result ) << endl;
    }

	
	
// Free allocated memory
    if (sdil)
    {
        delete sdil;
    }

    if (encOctets)
    {
        delete encOctets;
    }

    sdil = NULL;
    encOctets = NULL;

    return result;
}

/*.implementation:protected
 ****************************************************************************
 *  Purpose:
 *      To send a SRFDirective result last using the WIN library.
 *
 *  Input Parameters:
 *      dlg - pointer to a TCAP_Dialogue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
SendSRFDirectiveRRL(TCAP_Dialogue *dlg, TCAP_Component *recvCpt)
{
    int result = ITS_SUCCESS;
    ITS_OCTET family = 0x00, code = 0x00;
    Octets *encOctets = NULL;
    TCAP_Result res;

    SRFDirectiveRRL *sdrrl = new SRFDirectiveRRL();
    
    byte digitsArray[5] = { 0x91, 0x92, 0x93, 0x94, 0x95 };
    byte scriptResultArray[2] = {0x11, 0x22 };

    /* Set LocationRequest result parameters*/
     
    // DigitsDialed
	
	Digits* digits = new Digits(FixedByteArrayToVector(digitsArray));
    sdrrl->SetDigitsdialed( digits );

	// ScriptResult

	ScriptResult* sr = new ScriptResult(FixedByteArrayToVector(scriptResultArray));
    sdrrl->SetScriptResult(sr);


    /* Encode WIN message*/
    EncodeMsg( sdrrl, &encOctets );

    res.SetInvokeID( 1/*recvCpt->GetInvokeID() */);
    res.SetParameter( const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                      encOctets->GetLength());

    /* Printout result information*/
    traceComponent( &res );

    /* Send an LocationRequest result component*/
    result = TCAP_Component::Send((ITS_HANDLE)trin->GetTransport(), dlg,
                                  &res);

    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "SRFdirective ReturnResultLast send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send SRFdirective ReturnResultLast." << endl;
        cout << "Error: " << result << endl;
    }

    /* Send dialog*/
    result = TCAP_Dialogue::Send((ITS_HANDLE)trin->GetTransport(), dlg);
    
    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Dialogue send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send Dialogue." << endl;
        cout << "Error: " << ITS_GetErrorText( result ) << endl;
    }

    /* Free allocated memory*/
    if (sdrrl)
    {
        delete sdrrl;
    }

    if (encOctets)
    {
        delete encOctets;
    }

    sdrrl = NULL;
    encOctets = NULL;

    return result;
}


/*.implementation:protected
 ****************************************************************************
 *  Purpose:
 *      To send a TBusy invoke last using the WIN library.
 *
 *  Input Parameters:
 *      dlg - pointer to a TCAP_Dialogue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/

int
SendTBusyIL(TCAP_Dialogue *dlg)
{
    int result = ITS_SUCCESS;
    ITS_OCTET family = 0x00, code = 0x00;
    Octets *encOctets;
    TCAP_Invoke inv;
	tbID = dlg->GetDialogueID();

    TbusyIL *tbil = new TbusyIL();

    byte billingIdArray[7] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 };
	byte mscidArray[3] = { 0x04, 0x05, 0x06 };
    byte transactionCapabilityArray[5] = { 0x30, 0x32, 0x34, 0x36, 0x38 };
	byte triggerCapabilityArray[1] = { 0x03};

    byte callingPartyNum1Array[5] = { 0x04, 0x77, 0x62, 0x44, 0x25 };
    byte callingPartyNum2Array[5] = { 0x04, 0x77, 0x33, 0x14, 0x34 };
    byte callingPartySubaddrArray[5] = { 0x11, 0x22, 0x33, 0x44, 0x55 };
	byte esnArray[4] = { 0x11, 0x12, 0x13, 0x14 };
	byte groupInfoArray[4] = { 0x13, 0x26, 0x33, 0x49 };
	byte legInfoArray[4] = {0x11, 0x12, 0x93, 0x24};
	byte locationAreaArray[2] = {0x33, 0x54};
	byte mobileDirectoryNumArray[5] = { 0x22, 0x34, 0x13, 0x24, 0x16};
    byte mscidNumArray[5] = { 0x12, 0x13, 0x14, 0x15, 0x16 };
	byte mobileidentificaitonnumberarray[5] = { 0x11, 0x22, 0x33, 0x44, 0x55 };
	byte oneTimeFeatureIndArray[2]= { 0x34, 0x53 };
	byte pilotBillIDArray[7] = {0x10, 0x22, 0x30, 0x40, 0x51, 0x43, 0x12};
	byte pilotNumberArray[5] = {0x10, 0x22, 0x30, 0x40, 0x51};
	byte preferredLangIndArray[2] = { 0x04, 0x31 };
    byte redirectingNumDigitsArray[5] = { 0x10, 0x20, 0x30, 0x40, 0x50 };
    byte redirectingSubaddrArray[6] = { 0x11, 0x21, 0x31, 0x41, 0x51, 0x61 };
	byte servCellIDArray[2] = {0x22, 0x44};
	byte tatArray[1] = {0x12};

	
    
    /* Set LocationRequest parameters*/
    

    // BillingID
    
    BillingID* billingId =
        new BillingID(FixedByteArrayToVector(billingIdArray));

    tbil->SetBillingID( billingId );

    
    // CallingPartyNumberDigits1
    
    CallingPartyNumberDigits1* callingPartyNum1 =
        new CallingPartyNumberDigits1(FixedByteArrayToVector(callingPartyNum1Array));

    tbil->SetCallingPartyNumberDigits1( callingPartyNum1 );

    
    // CallingPartyNumberDigits2
    
    CallingPartyNumberDigits2* callingPartyNum2
        = new CallingPartyNumberDigits2(FixedByteArrayToVector(callingPartyNum2Array));

    tbil->SetCallingPartyNumberDigits2( callingPartyNum2 ); 

    
    // CallingPartySubaddress
    
    CallingPartySubaddress* callingPartySubaddr =
        new CallingPartySubaddress(FixedByteArrayToVector(callingPartySubaddrArray));

    tbil->SetCallingPartySubaddress( callingPartySubaddr ); 

	
	//Electronic Serial no.
	
	ElectronicSerialNumber* esn = new ElectronicSerialNumber( FixedByteArrayToVector( esnArray ) );
	
	tbil->SetElectronicSerialNumber(esn);

	//GroupInformation

	GroupInformation* gi = 
		new GroupInformation(FixedByteArrayToVector(groupInfoArray));
	tbil->SetGroupInformation(gi);

	//LegInformation

	LegInformation* li = 
		new LegInformation(FixedByteArrayToVector(legInfoArray));
	tbil->SetLegInformation(li);

	// LocationAreaID

	LocationAreaID* laID =
		new LocationAreaID(FixedByteArrayToVector(locationAreaArray));
	tbil->SetLocationAreaID(laID);
	
	// MobileDirectoryNumber
   
	MobileDirectoryNumber* mdn = 
		new MobileDirectoryNumber(FixedByteArrayToVector(mobileDirectoryNumArray));
	tbil->SetMobileDirectoryNumber(mdn);

	//MobileIdentificationNumber
	
    MobileIdentificationNumber* min = new MobileIdentificationNumber( FixedByteArrayToVector( mobileidentificaitonnumberarray ) );
	tbil->SetMobileIdentificationNumber(min);

	
	// MSCID
    
    MSCID* mscid = new MSCID( FixedByteArrayToVector( mscidArray ) );

    tbil->SetMSCID( mscid );

    
    // MSCIdentificationNumber
    
    MSCIdentificationNumber* mscIdentificationNum =
        new MSCIdentificationNumber( FixedByteArrayToVector( mscidNumArray) );

    tbil->SetMSCIdentificationNumber( mscIdentificationNum );

    // OneTimeFeatureIndicator

	OneTimeFeatureIndicator* otfi = 
		new OneTimeFeatureIndicator( FixedByteArrayToVector( oneTimeFeatureIndArray) );
    tbil->SetOneTimeFeatureIndicator(otfi);

    // PilotBillingID

	PilotBillingID* pb =
		new PilotBillingID(FixedByteArrayToVector(pilotBillIDArray));
	tbil->SetPilotBillingID(pb);


	// PilotNumber

	PilotNumber* pn =
		new PilotNumber(FixedByteArrayToVector(pilotNumberArray));
	tbil->SetPilotNumber(pn);


	// PreferredLanguageIndicator

	PreferredLanguageIndicator* pli =
		new PreferredLanguageIndicator(FixedByteArrayToVector(preferredLangIndArray));
	tbil->SetPreferredLanguageIndicator(pli);


    // RedirectingNumberDigits
    
	RedirectingNumberDigits* redirectingNumDigits =
        new RedirectingNumberDigits(FixedByteArrayToVector(redirectingNumDigitsArray));

    tbil->SetRedirectingNumberDigits( redirectingNumDigits );

    
    // RedirectingSubaddress
   
	RedirectingSubaddress* redirectingSubaddr =
        new RedirectingSubaddress(FixedByteArrayToVector(redirectingSubaddrArray));

    tbil->SetRedirectingSubaddress( redirectingSubaddr );

	//RedirectionReason

	RedirectionReason rr;
	rr.SetCallRefused();
	tbil->SetRedirectionReason(rr);

	// ServingCellID

	ServingCellID* sid =
		new ServingCellID(FixedByteArrayToVector(servCellIDArray));
	tbil->SetServingCellID(sid);

	// SystemMyTypeCode

	SystemMyTypeCode smtc;
	smtc.SetTelos();
	tbil->SetSystemMyTypeCode(smtc);

	// TerminationAccessType

	TerminationAccessType* tat =
		new TerminationAccessType(FixedByteArrayToVector(tatArray));
	tbil->SetTerminationAccessType(tat);

        
    // TransactionCapability
    
    TransactionCapability* transactionCapability =
        new TransactionCapability(FixedByteArrayToVector(transactionCapabilityArray));

    tbil->SetTransactionCapability( transactionCapability );


	// TriggerType

	TriggerType triggerType;
	triggerType.SetAllCalls();
	tbil->SetTriggerType(triggerType);
    
   
	// wINCapability
    WINCapability* wINCapability = new WINCapability();
	TriggerCapability* triggerCapability = 
		new TriggerCapability(FixedByteArrayToVector(triggerCapabilityArray));
    wINCapability->SetTriggerCapability(triggerCapability);
	tbil->SetWINCapability(wINCapability);

	
    /*Encode IS41 message*/
    
    EncodeMsg( tbil, &encOctets );

    inv.SetTimeOut( 90 );
    inv.SetInvokeID( 1 );
    inv.SetOperation(true, 75, OP_TBusy);
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    traceComponent( &inv );

    /* Send an LocationRequest invoke component*/
    result = TCAP_Component::Send((ITS_HANDLE)trin->GetTransport(), dlg, &inv);

    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "TBusy invoke send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send TBusy invoke." << endl;
        cout << "Error: " << ITS_GetErrorText( result ) << endl;
    }

    /* Send dialog*/
    result = TCAP_Dialogue::Send((ITS_HANDLE)trin->GetTransport(), dlg);
    
    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Dialogue send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send Dialogue." << endl;
        cout << "Error: " << ITS_GetErrorText( result ) << endl;
    }


    /* Free allocated memory*/
    if (tbil)
    {
        delete tbil;
    }

    if (encOctets)
    {
        delete encOctets;
    }

    tbil = NULL;
    encOctets = NULL;

    return result;
}


/*.implementation:protected
 ****************************************************************************
 *  Purpose:
 *      To send a TBusy result last using the WIN library.
 *
 *  Input Parameters:
 *      dlg - pointer to a TCAP_Dialogue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
SendTBusyRRL(TCAP_Dialogue *dlg, TCAP_Component *recvCpt)
{
    int result = ITS_SUCCESS;
    ITS_OCTET family = 0x00, code = 0x00;
    Octets *encOctets = NULL;
    TCAP_Result res;

    TBusyRRL *tbrrl = new TBusyRRL();


	byte actionCodeArray[2] = { 0x51, 0x85 };
    byte announcementCodeArray[5] = { 0x11, 0x12, 0x13, 0x14, 0x15 };
    byte callPartyNumStr1Array[5] = { 0x04, 0x34, 0x52, 0x65, 0x18 };
    byte callPartyNumStr2Array[5] = { 0x04, 0x77, 0x62, 0x60, 0x08 };
	byte carrierDigitsArray[5] = { 0x04, 0x77, 0x22, 0x99, 0x24 };
	byte displayTextArray[2] = {0x22, 0x23}; 
	byte dMHbillingdigitsArray[6] = { 0x11, 0x02, 0x03, 0x04, 0x05, 0x06 }; 
	byte dMHaccountCodeArray[5] = { 0x02, 0x03, 0x04, 0x05, 0x32 };
	byte dMHaltBillDigitsArray[5] = { 0x21, 0x02, 0x03, 0x04, 0x42 };
    byte groupInfoArray[4] = { 0x13, 0x23, 0x33, 0x43 };
    byte oneTimeFeatureIndArray[2]= { 0x12, 0x67 };
	byte pilotNumberArray[5] = {0x19, 0x22, 0x30, 0x40, 0x21};
	byte redirectingNumDigitsArray[5] = { 0x11, 0x21, 0x31, 0x41, 0x51 };
    byte routingDigitsArray[5] = { 0x04, 0x77, 0x23, 0x78, 0x99 };
 
	byte destinationDigitsArray[5] = { 0x01, 0x02, 0x16, 0x23, 0x15 };
    byte mscidArray[3] = { 0x04, 0x05, 0x06 };
	
	byte terminationTriggersArray[2] = { 0x41, 0x42 };
    
    byte globalTitleArray[2] = {0x41, 0x72};
	byte pcSSNArray[5] = {0x11, 0x12, 0x13, 0x54, 0x35};
	byte winTriggListArray[2] = {0x63, 0x94};


    /* Set LocationRequest result parameters*/

  
	//AccessDeniedReason
	
    AccessDeniedReason accessDeniedReason;
    accessDeniedReason.SetTerminationDenied();
    tbrrl->SetAccessDeniedReason( accessDeniedReason );

      
	// ActionCode

    ActionCode* actionCode =
		new ActionCode(FixedByteArrayToVector(actionCodeArray));
	tbrrl->SetActionCode(actionCode);


    // AnnouncementList
    
    AnnouncementCode* announcementCode =
        new AnnouncementCode(FixedByteArrayToVector(announcementCodeArray));
    
    AnnouncementList::CHOICE choice;
    choice.SetChoiceAnnouncementCode( announcementCode );

    AnnouncementList announcementList;
    announcementList.AddElement( choice );

    tbrrl->SetAnnouncementList( announcementList );

    
    // CallingPartyNumberString1
    
    CallingPartyNumberString1* callingPartyNumStr1 =
        new CallingPartyNumberString1(FixedByteArrayToVector(callPartyNumStr1Array));
    tbrrl->SetCallingPartyNumberString1( callingPartyNumStr1 );

    
	// CallingPartyNumberString2
    
    CallingPartyNumberString2* callingPartyNumStr2 =
        new CallingPartyNumberString2(FixedByteArrayToVector(callPartyNumStr2Array));
    tbrrl->SetCallingPartyNumberString2( callingPartyNumStr2 );

    // DigitsCarrier
    
    CarrierDigits* carrierDigits =
        new CarrierDigits(FixedByteArrayToVector(carrierDigitsArray));
    tbrrl->SetCarrierDigits( carrierDigits );

    // DisplayText
  
    DisplayText* dt =
        new DisplayText(FixedByteArrayToVector(displayTextArray));
    tbrrl->SetDisplayText( dt );

	
	// DMHBillingID
    
    DMH_BillingDigits* dMH_billingDigits =
        new DMH_BillingDigits(FixedByteArrayToVector(dMHbillingdigitsArray));
    tbrrl->SetDMH_BillingDigits( dMH_billingDigits );

	// DMHAccountCode

	DMH_AccountCodeDigits* dmha =
		new DMH_AccountCodeDigits(FixedByteArrayToVector(dMHaccountCodeArray));
	tbrrl->SetDMH_AccountCodeDigits(dmha);

    // DMHAlternateBillingID
    
    DMH_AlternateBillingDigits* dmhab =
        new DMH_AlternateBillingDigits(FixedByteArrayToVector(dMHaltBillDigitsArray));
    tbrrl->SetDMH_AlternateBillingDigits( dmhab );

	// DMHRedirectionIndicator

	DMH_RedirectionIndicator dmhr;
	dmhr.SetCFB();
	tbrrl->SetDMH_RedirectionIndicator(dmhr);

	// GroupInformation

	GroupInformation* gi = 
		new GroupInformation(FixedByteArrayToVector(groupInfoArray));
	tbrrl->SetGroupInformation(gi);

	// OneTimeFeatureIndicator
     
	OneTimeFeatureIndicator* otfi = 
		new OneTimeFeatureIndicator( FixedByteArrayToVector( oneTimeFeatureIndArray) );
    tbrrl->SetOneTimeFeatureIndicator(otfi);

	// PilotNumber

	PilotNumber* pn =
		new PilotNumber(FixedByteArrayToVector(pilotNumberArray));
	tbrrl->SetPilotNumber(pn);

	// RedirectingNumberDigits
    
    RedirectingNumberDigits* redirectingNumDigits =
        new RedirectingNumberDigits(FixedByteArrayToVector(redirectingNumDigitsArray));
	tbrrl->SetRedirectingNumberDigits( redirectingNumDigits );

	// ResumePIC

	ResumePIC rPIC;
	rPIC.SetCollectInformationPIC();
	tbrrl->SetResumePIC(rPIC);

    // RoutingDigits
    
    RoutingDigits* routingDigits =
        new RoutingDigits(FixedByteArrayToVector(routingDigitsArray));
    tbrrl->SetRoutingDigits( routingDigits );

	//TerminationList   

	DestinationDigits* dd =
        new DestinationDigits(FixedByteArrayToVector(destinationDigitsArray));
    
	MSCID* mscid = new MSCID( FixedByteArrayToVector( mscidArray ));
    
	IntersystemTermination ist;
	ist.SetDestinationDigits(dd);
	ist.SetMSCID(mscid);

	TerminationList::CHOICE ch;  
	ch.SetChoiceIntersystemTermination(ist);

    TerminationList tl;
	tl.AddElement(ch);

	tbrrl->SetTerminationList(tl);

	// TerminationTriggers

	TerminationTriggers* tt = 
		new TerminationTriggers(FixedByteArrayToVector(terminationTriggersArray));
	tbrrl->SetTerminationTriggers(tt);

	// TriggerAddressList

	GlobalTitle* gt = new GlobalTitle(FixedByteArrayToVector(globalTitleArray));
	PC_SSN* pcssn = new PC_SSN(FixedByteArrayToVector(pcSSNArray));
	WINTriggerList* wint =
		new WINTriggerList(FixedByteArrayToVector(winTriggListArray));

	DestinationAddress da;
	da.SetChoiceGlobalTitle(gt);
	da.SetChoicePC_SSN(pcssn);

	TriggerList trl;
	trl.SetDestinationAddress(da);
	trl.SetWINTriggerList(wint);

	TriggerAddressList::SET set;
	set.SetTriggerList(trl);

	TriggerAddressList tal;
	tal.AddElement(set);

	tbrrl->SetTriggerAddressList(tal);
	


    /* Encode WIN message*/
    EncodeMsg( tbrrl, &encOctets );

    res.SetInvokeID( recvCpt->GetInvokeID());
    res.SetParameter( const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                      encOctets->GetLength());

    /* Printout result information*/
    traceComponent( &res );

    /* Send an LocationRequest result component*/
    result = TCAP_Component::Send((ITS_HANDLE)trin->GetTransport(), dlg,
                                  &res);

    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "TBusy ReturnResultLast send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send TBusy ReturnResultLast." << endl;
        cout << "Error: " << result << endl;
    }

    /* Send dialog*/
    result = TCAP_Dialogue::Send((ITS_HANDLE)trin->GetTransport(), dlg);
    
    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Dialogue send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send Dialogue." << endl;
        cout << "Error: " << ITS_GetErrorText( result ) << endl;
    }

    /* Free allocated memory*/
    if (tbrrl)
    {
        delete tbrrl;
    }

    if (encOctets)
    {
        delete encOctets;
    }

    tbrrl = NULL;
    encOctets = NULL;

    return result;
}


/*.implementation:protected
 ****************************************************************************
 *  Purpose:
 *      To send a TNoAnswer invoke last using the WIN library.
 *
 *  Input Parameters:
 *      dlg - pointer to a TCAP_Dialogue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/

int
SendTNoAnswerIL(TCAP_Dialogue *dlg)
{
    int result = ITS_SUCCESS;
    ITS_OCTET family = 0x00, code = 0x00;
    Octets *encOctets;
    TCAP_Invoke inv;
    TNoAnswerIL *tail = new TNoAnswerIL();

    byte billingIdArray[7] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 };
	byte mscidArray[3] = { 0x04, 0x05, 0x06 };
    byte transactionCapabilityArray[5] = { 0x13, 0x32, 0x34, 0x36, 0x38 };
	byte triggerCapabilityArray[1] = { 0x07};

    byte callingPartyNum1Array[5] = { 0x05, 0x17, 0x62, 0x44, 0x25 };
    byte callingPartyNum2Array[5] = { 0x04, 0x77, 0x33, 0x14, 0x34 };
    byte callingPartySubaddrArray[5] = { 0x11, 0x22, 0x33, 0x44, 0x55 };
	byte esnArray[4] = { 0x11, 0x12, 0x13, 0x14 };
	byte groupInfoArray[4] = { 0x13, 0x23, 0x23, 0x53 };
	byte legInfoArray[4] = {0x11, 0x18, 0x23, 0x24};
	byte locationAreaArray[2] = {0x43, 0x44};
	byte mobileDirectoryNumArray[5] = { 0x22, 0x14, 0x23, 0x34, 0x16}; 
    byte mscidNumArray[5] = { 0x12, 0x13, 0x14, 0x15, 0x16 };
	byte mobileIDNumArray[5] = { 0x11, 0x22, 0x33, 0x44, 0x55 };
	byte oneTimeFeatureIndArray[2]= { 0x15, 0x59 }; 
	byte pilotBillIDArray[7] = {0x10, 0x22, 0x30, 0x41, 0x51, 0x43, 0x12};
	byte pilotNumberArray[5] = {0x10, 0x22, 0x30, 0x40, 0x41};
	byte preferredLangIndArray[2] = { 0x14, 0x35 };
    byte redirectingNumDigitsArray[5] = { 0x10, 0x20, 0x30, 0x40, 0x50 };
    byte redirectingSubaddrArray[6] = { 0x11, 0x23, 0x31, 0x41, 0x51, 0x61 };
	byte servCellIDArray[2] = {0x12, 0x34};
    byte tatArray[1] = {0x42};
    
    /* Set LocationRequest parameters*/
    

    // BillingID
    
    BillingID* billingId =
        new BillingID(FixedByteArrayToVector(billingIdArray));

    tail->SetBillingID( billingId );

    
    // CallingPartyNumberDigits1
    
    CallingPartyNumberDigits1* callingPartyNum1 =
        new CallingPartyNumberDigits1(FixedByteArrayToVector(callingPartyNum1Array));

    tail->SetCallingPartyNumberDigits1( callingPartyNum1 );

    
    // CallingPartyNumberDigits2
    
    CallingPartyNumberDigits2* callingPartyNum2
        = new CallingPartyNumberDigits2(FixedByteArrayToVector(callingPartyNum2Array));

    tail->SetCallingPartyNumberDigits2( callingPartyNum2 ); 

    
    // CallingPartySubaddress
    
    CallingPartySubaddress* callingPartySubaddr =
        new CallingPartySubaddress(FixedByteArrayToVector(callingPartySubaddrArray));

    tail->SetCallingPartySubaddress( callingPartySubaddr ); 
	
	//Electronic Serial no.
	
	ElectronicSerialNumber* esn = new ElectronicSerialNumber( FixedByteArrayToVector( esnArray ) );
	
	tail->SetElectronicSerialNumber(esn);

	// GroupInformation

	GroupInformation* gi = 
		new GroupInformation(FixedByteArrayToVector(groupInfoArray));
	tail->SetGroupInformation(gi);

	//LegInformation

	LegInformation* li = 
		new LegInformation(FixedByteArrayToVector(legInfoArray));
	tail->SetLegInformation(li);

	// LocationAreaID

	LocationAreaID* laID =
		new LocationAreaID(FixedByteArrayToVector(locationAreaArray));
	tail->SetLocationAreaID(laID);

	// MobileDirectoryNumber
  
	MobileDirectoryNumber* mdn = 
		new MobileDirectoryNumber(FixedByteArrayToVector(mobileDirectoryNumArray));
	tail->SetMobileDirectoryNumber(mdn);

	//MobileIdentificationNumber
	
    MobileIdentificationNumber* min = new MobileIdentificationNumber(FixedByteArrayToVector(mobileIDNumArray));
	tail->SetMobileIdentificationNumber(min);
   
	// MSCID
    
    MSCID* mscid = new MSCID( FixedByteArrayToVector( mscidArray ));
    tail->SetMSCID( mscid );

    // MSCIdentificationNumber
    
    MSCIdentificationNumber* mscIdentificationNum =
        new MSCIdentificationNumber( FixedByteArrayToVector( mscidNumArray) );

    tail->SetMSCIdentificationNumber( mscIdentificationNum );

	// OneTimeFeatureIndicator
    
	OneTimeFeatureIndicator* otfi = 
		new OneTimeFeatureIndicator( FixedByteArrayToVector( oneTimeFeatureIndArray) );
    tail->SetOneTimeFeatureIndicator(otfi);

	// PilotBillingID

	PilotBillingID* pb =
		new PilotBillingID(FixedByteArrayToVector(pilotBillIDArray));
	tail->SetPilotBillingID(pb);


	// PilotNumber

	PilotNumber* pn =
		new PilotNumber(FixedByteArrayToVector(pilotNumberArray));
	tail->SetPilotNumber(pn);


	// PreferredLanguageIndicator

	PreferredLanguageIndicator* pli =
		new PreferredLanguageIndicator(FixedByteArrayToVector(preferredLangIndArray));
	tail->SetPreferredLanguageIndicator(pli);

    // RedirectingNumberDigits
    
	RedirectingNumberDigits* redirectingNumDigits =
        new RedirectingNumberDigits(FixedByteArrayToVector(redirectingNumDigitsArray));

    tail->SetRedirectingNumberDigits( redirectingNumDigits );

    
    // RedirectingSubaddress
   
	RedirectingSubaddress* redirectingSubaddr =
        new RedirectingSubaddress(FixedByteArrayToVector(redirectingSubaddrArray));
    tail->SetRedirectingSubaddress( redirectingSubaddr );

    //RedirectionReason

	RedirectionReason rr;
	rr.SetCallAccepted();
	tail->SetRedirectionReason(rr);   
		        
	// ServingCellID

	ServingCellID* sid =
		new ServingCellID(FixedByteArrayToVector(servCellIDArray));
	tail->SetServingCellID(sid);

	// SystemMyTypeCode

	SystemMyTypeCode smtc;
	smtc.SetTelos();
	tail->SetSystemMyTypeCode(smtc);

	// TerminationAccessType

	TerminationAccessType* tat =
		new TerminationAccessType(FixedByteArrayToVector(tatArray));
	tail->SetTerminationAccessType(tat);


    // TransactionCapability
    
    TransactionCapability* transactionCapability =
        new TransactionCapability(FixedByteArrayToVector(transactionCapabilityArray));

    tail->SetTransactionCapability( transactionCapability );


	// TriggerType

	TriggerType triggerType;
	triggerType.SetAllCalls();
	tail->SetTriggerType(triggerType);
    
   
	// wINCapability
    WINCapability* wINCapability = new WINCapability();
	TriggerCapability* triggerCapability = 
		new TriggerCapability(FixedByteArrayToVector(triggerCapabilityArray));
    wINCapability->SetTriggerCapability(triggerCapability);
	tail->SetWINCapability(wINCapability);

	
    /*Encode IS41 message*/
    
    EncodeMsg( tail, &encOctets );

    inv.SetTimeOut( 90 );
    inv.SetInvokeID( 1 );
    inv.SetOperation(true, 76, OP_TNoAnswer);
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    traceComponent( &inv );

    /* Send an LocationRequest invoke component*/
    result = TCAP_Component::Send((ITS_HANDLE)trin->GetTransport(), dlg, &inv);

    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "TNoAnswer invoke send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send TNoAnswer invoke." << endl;
        cout << "Error: " << ITS_GetErrorText( result ) << endl;
    }

    /* Send dialog*/
    result = TCAP_Dialogue::Send((ITS_HANDLE)trin->GetTransport(), dlg);
    
    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Dialogue send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send Dialogue." << endl;
        cout << "Error: " << ITS_GetErrorText( result ) << endl;
    }


    /* Free allocated memory*/
    if (tail)
    {
        delete tail;
    }

    if (encOctets)
    {
        delete encOctets;
    }

    tail = NULL;
    encOctets = NULL;

    return result;
}


/*.implementation:protected
 ****************************************************************************
 *  Purpose:
 *      To send a TNoAnswer result last using the WIN library.
 *
 *  Input Parameters:
 *      dlg - pointer to a TCAP_Dialogue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
SendTNoAnswerRRL(TCAP_Dialogue *dlg, TCAP_Component *recvCpt)
{
    int result = ITS_SUCCESS;
    ITS_OCTET family = 0x00, code = 0x00;
    Octets *encOctets = NULL;
    TCAP_Result res;

    TNoAnswerRRL *tarrl = new TNoAnswerRRL();

    byte actionCodeArray[2] = { 0x52, 0x75 };
    byte announcementCodeArray[5] = { 0x31, 0x12, 0x13, 0x14, 0x45 };
    byte callPartyNumStr1Array[5] = { 0x04, 0x34, 0x42, 0x65, 0x38 };
    byte callPartyNumStr2Array[5] = { 0x04, 0x67, 0x62, 0x60, 0x08 };
	byte carrierDigitsArray[5] = { 0x04, 0x77, 0x22, 0x89, 0x24 };
	byte displayTextArray[2] = {0x22, 0x23}; 
	byte dMHbillingdigitsArray[6] = { 0x11, 0x02, 0x03, 0x44, 0x05, 0x06 }; 
	byte dMHaccountCodeArray[5] = { 0x02, 0x03, 0x04, 0x05, 0x32 };
	byte dMHaltBillDigitsArray[5] = { 0x21, 0x02, 0x03, 0x34, 0x42 };
    byte groupInfoArray[4] = { 0x13, 0x23, 0x33, 0x43 };
    byte oneTimeFeatureIndArray[2]= { 0x12, 0x67 };
	byte pilotNumberArray[5] = {0x19, 0x22, 0x30, 0x40, 0x21};
	byte redirectingNumDigitsArray[5] = { 0x11, 0x21, 0x31, 0x41, 0x51 };
    byte routingDigitsArray[5] = { 0x04, 0x77, 0x23, 0x78, 0x89 };
 
	byte destinationDigitsArray[5] = { 0x01, 0x02, 0x16, 0x23, 0x15 };
    byte mscidArray[3] = { 0x04, 0x05, 0x06 };
	
	byte terminationTriggersArray[2] = { 0x41, 0x42 };
    
    byte globalTitleArray[2] = {0x41, 0x72};
	byte pcSSNArray[5] = {0x11, 0x12, 0x13, 0x54, 0x35};
	byte winTriggListArray[2] = {0x63, 0x94};


    /* Set LocationRequest result parameters*/

  
	//AccessDeniedReason
	
    AccessDeniedReason accessDeniedReason;
    accessDeniedReason.SetTerminationDenied();
    tarrl->SetAccessDeniedReason( accessDeniedReason );

      
	// ActionCode

    ActionCode* actionCode =
		new ActionCode(FixedByteArrayToVector(actionCodeArray));
	tarrl->SetActionCode(actionCode);


    // AnnouncementList
    
    AnnouncementCode* announcementCode =
        new AnnouncementCode(FixedByteArrayToVector(announcementCodeArray));
    
    AnnouncementList::CHOICE choice;
    choice.SetChoiceAnnouncementCode( announcementCode );

    AnnouncementList announcementList;
    announcementList.AddElement( choice );

    tarrl->SetAnnouncementList( announcementList );

    
    // CallingPartyNumberString1
    
    CallingPartyNumberString1* callingPartyNumStr1 =
        new CallingPartyNumberString1(FixedByteArrayToVector(callPartyNumStr1Array));
    tarrl->SetCallingPartyNumberString1( callingPartyNumStr1 );

    
	// CallingPartyNumberString2
    
    CallingPartyNumberString2* callingPartyNumStr2 =
        new CallingPartyNumberString2(FixedByteArrayToVector(callPartyNumStr2Array));
    tarrl->SetCallingPartyNumberString2( callingPartyNumStr2 );

    // DigitsCarrier
    
    CarrierDigits* carrierDigits =
        new CarrierDigits(FixedByteArrayToVector(carrierDigitsArray));
    tarrl->SetCarrierDigits( carrierDigits );

    // DisplayText
  
    DisplayText* dt =
        new DisplayText(FixedByteArrayToVector(displayTextArray));
    tarrl->SetDisplayText( dt );

	
	// DMHBillingID
    
    DMH_BillingDigits* dMH_billingDigits =
        new DMH_BillingDigits(FixedByteArrayToVector(dMHbillingdigitsArray));
    tarrl->SetDMH_BillingDigits( dMH_billingDigits );

	// DMHAccountCode

	DMH_AccountCodeDigits* dmha =
		new DMH_AccountCodeDigits(FixedByteArrayToVector(dMHaccountCodeArray));
	tarrl->SetDMH_AccountCodeDigits(dmha);

    // DMHAlternateBillingID
    
    DMH_AlternateBillingDigits* dmhab =
        new DMH_AlternateBillingDigits(FixedByteArrayToVector(dMHaltBillDigitsArray));
    tarrl->SetDMH_AlternateBillingDigits( dmhab );

	// DMHRedirectionIndicator

	DMH_RedirectionIndicator dmhr;
	dmhr.SetCFB();
	tarrl->SetDMH_RedirectionIndicator(dmhr);

	// GroupInformation

	GroupInformation* gi = 
		new GroupInformation(FixedByteArrayToVector(groupInfoArray));
	tarrl->SetGroupInformation(gi);

	// OneTimeFeatureIndicator
     
	OneTimeFeatureIndicator* otfi = 
		new OneTimeFeatureIndicator( FixedByteArrayToVector( oneTimeFeatureIndArray) );
    tarrl->SetOneTimeFeatureIndicator(otfi);

	// PilotNumber

	PilotNumber* pn =
		new PilotNumber(FixedByteArrayToVector(pilotNumberArray));
	tarrl->SetPilotNumber(pn);

	// RedirectingNumberDigits
    
    RedirectingNumberDigits* redirectingNumDigits =
        new RedirectingNumberDigits(FixedByteArrayToVector(redirectingNumDigitsArray));
	tarrl->SetRedirectingNumberDigits( redirectingNumDigits );

	// ResumePIC

	ResumePIC rPIC;
	rPIC.SetCollectInformationPIC();
	tarrl->SetResumePIC(rPIC);

    // RoutingDigits
    
    RoutingDigits* routingDigits =
        new RoutingDigits(FixedByteArrayToVector(routingDigitsArray));
    tarrl->SetRoutingDigits( routingDigits );

	//TerminationList   

	DestinationDigits* dd =
        new DestinationDigits(FixedByteArrayToVector(destinationDigitsArray));
    
	MSCID* mscid = new MSCID( FixedByteArrayToVector( mscidArray ));
    
	IntersystemTermination ist;
	ist.SetDestinationDigits(dd);
	ist.SetMSCID(mscid);

	TerminationList::CHOICE ch;  
	ch.SetChoiceIntersystemTermination(ist);

    TerminationList tl;
	tl.AddElement(ch);

	tarrl->SetTerminationList(tl);

	// TerminationTriggers

	TerminationTriggers* tt = 
		new TerminationTriggers(FixedByteArrayToVector(terminationTriggersArray));
	tarrl->SetTerminationTriggers(tt);

	// TriggerAddressList

	GlobalTitle* gt = new GlobalTitle(FixedByteArrayToVector(globalTitleArray));
	PC_SSN* pcssn = new PC_SSN(FixedByteArrayToVector(pcSSNArray));
	WINTriggerList* wint =
		new WINTriggerList(FixedByteArrayToVector(winTriggListArray));

	DestinationAddress da;
	da.SetChoiceGlobalTitle(gt);
	da.SetChoicePC_SSN(pcssn);

	TriggerList trl;
	trl.SetDestinationAddress(da);
	trl.SetWINTriggerList(wint);

	TriggerAddressList::SET set;
	set.SetTriggerList(trl);

	TriggerAddressList tal;
	tal.AddElement(set);

	tarrl->SetTriggerAddressList(tal);


    /* Encode WIN message*/
    EncodeMsg( tarrl, &encOctets );

    res.SetInvokeID( recvCpt->GetInvokeID());
    res.SetParameter( const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                      encOctets->GetLength());

    /* Printout result information*/
    traceComponent( &res );

    /* Send an LocationRequest result component*/
    result = TCAP_Component::Send((ITS_HANDLE)trin->GetTransport(), dlg,
                                  &res);

    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "TNoAnswer ReturnResultLast send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send TNoAnswer ReturnResultLast." << endl;
        cout << "Error: " << result << endl;
    }

    /* Send dialog*/
    result = TCAP_Dialogue::Send((ITS_HANDLE)trin->GetTransport(), dlg);
    
    if (result == ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Dialogue send success." << endl;
    }
    else
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        cout << "Failed to send Dialogue." << endl;
        cout << "Error: " << ITS_GetErrorText( result ) << endl;
    }

    /* Free allocated memory*/
    if (tarrl)
    {
        delete tarrl;
    }

    if (encOctets)
    {
        delete encOctets;
    }

    tarrl = NULL;
    encOctets = NULL;

    return result;
}



/*.implementation:protected
 ****************************************************************************
 *  Purpose:
 *      To send a LocationRequest invoke last using the WAN41 library.
 *
 *  Input Parameters:
 *      dlg - pointer to a TCAP_Dialogue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
main(int argc, char **argv)
{
    bool keepGoing = true;
    int ret = ITS_SUCCESS;
    int choice = 0, i = 0;
    int instance = 0;
    ITS_USHORT idid = 0x00, did = 0x00;
    bool national = false;
    ITS_OCTET op = 0, family = 0;
    int local_pc, local_ssn, remote_pc, remote_ssn;
    TCAP_Begin beg;
    TCAP_End end;
    TCAP_Cancel cancel_cpt;
    int error_code = 0x00;
    TCAP_Error error_cpt;
    TCAP_Reject reject_cpt;
    ITS_Event ev;
    ITS_ByteArray buf;
    std::vector<byte> data, vmscid;

    cout << "*****************************************************" << endl;
    cout << "*****                                           *****" << endl;
    cout << "*****    WIN LocationRequest Unit Test			 *****" << endl;
    cout << "*****                                           *****" << endl;
    cout << "*****************************************************" << endl;
    cout << "\n\n";
    cout << "Select instance" << endl;
    cout << "---------------------------" << endl;
    cout << "[1] Server" << endl;
    cout << "[2] Client" << endl;
    cout << endl;
    cout << "->> ";
    cin >> instance;

    // Default instance is 1
    if (instance < 1 || instance > 2)
    {
        instance = 1;
    }
    
    if (instance == 1)
    {
        ITS_Application::SetName( "WINTest1" );
    }
    else
    {
        ITS_Application::SetName( "WINTest2" );
    }
    
    ITS_AddFeature(itsINTELLISS7_Class);
	
	ITS_GlobalStart(ITS_TCAP | ITS_SCCP);

    try
    {
        trin = new ITS_Worker(0, "User", ITS_DEFAULT_USER_SRC,
                              ITS_TRANSPORT_TQUEUE);

        if (trin == NULL)
        {
            printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
            printf("Fail to create Tqueue transport\n");
        }

        if (instance == 1)
        {
            trout = new ITS_Worker(0, "User 2", ITS_DEFAULT_USER_SRC + instance,
                                   ITS_SCCP | ITS_TCAP |
                                   ITS_TRANSPORT_SSOCKET );

            local_pc = 2;
            local_ssn = 20;
            remote_pc = 3;
            remote_ssn = 30;
        }
        else if (instance == 2)
        {
            trout = new ITS_Worker(0, "User 3", ITS_DEFAULT_USER_SRC + instance,
                                   ITS_SCCP | ITS_TCAP |
                                   ITS_TRANSPORT_CSOCKET );

            local_pc = 3;
            local_ssn = 30;
            remote_pc = 2;
            remote_ssn = 20;
        }

        if (trout == NULL)
        {
            printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
            printf("Fail to create socket transport\n");
        }
    }
    catch (...)
    {
        cout << "Couldn't create transport." << endl;

        return (0);
    }


    
    /* Creating MTP3 border transport thread*/
    
    recvMTP3Thread = new ITS_Thread(0, RecvMTP3Func);

    if (recvMTP3Thread->Enter((void *)recvMTP3Thread) != ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        printf("Fail to start MTP3 receive thread\n");
    }

    
    /* Creating TCAP receive thread*/
   
    recvTCAPThread = new ITS_Thread(0, RecvTCAPFunc);
    
    if (recvTCAPThread->Enter((void *)recvTCAPThread) != ITS_SUCCESS)
    {
        printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
        printf("Fail to start TCAP receive thread\n");
    }

    while (keepGoing)
    {
        DisplayMenu();

        cin >> choice;

        switch (choice)
        {
        case 0:
            keepGoing = false;
            continue;
            break;

        case 1:
            beg.SetOrigAddr(ADDR_IND, local_pc, local_ssn, NULL, 0);
            beg.SetDestAddr(ADDR_IND, remote_pc, remote_ssn, NULL, 0);

            if (TCAP_AllocateDialogueId( &did ) != ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Fail to allocate dialog id!" << endl;
                break;
            }

            beg.SetDialogueID( did );
            beg.SetQualityOfService( QOSI_RET_OPT );

            if (SendFeatureRequestIL( &beg ) == ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "InvokeLast sent." << endl;
            }
             

            else
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Fail to send InvokeLast component!" << endl;
            }
			 
            break;

        case 2:
            end.SetDialogueID( dlg->GetDialogueID() );
	
            // Set termination type to Basic End
            end.SetPreArrangedEnd( false );

            if (SendFeatureRequestRRL( &end, cpt) == ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "ReturnResultLast sent." << endl;
            }
			
			else
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Fail to send ReturnResultLast!" << endl;
            }

            // Free allocated memory for received component and dialogue
            if (cpt)
            {
                delete cpt;
            }

            if (dlg)
            {
                delete dlg;
            }
            break;


		case 3:
            beg.SetOrigAddr(ADDR_IND, local_pc, local_ssn, NULL, 0);
            beg.SetDestAddr(ADDR_IND, remote_pc, remote_ssn, NULL, 0);

            if (TCAP_AllocateDialogueId( &did ) != ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Fail to allocate dialog id!" << endl;
                break;
            }

            beg.SetDialogueID( did );

             
			if (SendServiceRequestIL( &beg ) == ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "InvokeLast sent." << endl;
            }

            else
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Fail to send InvokeLast component!" << endl;
            }
            break;

        case 4:
            end.SetDialogueID( dlg->GetDialogueID() );

            // Set termination type to Basic End
            end.SetPreArrangedEnd( false );

            if (SendServiceRequestRRL( &end, cpt) == ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "ReturnResultLast sent." << endl;
            }
			
			else
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Fail to send ReturnResultLast!" << endl;
            }

            // Free allocated memory for received component and dialogue
            if (cpt)
            {
                delete cpt;
            }

            if (dlg)
            {
                delete dlg;
            }
            break;

        case 5:
            beg.SetOrigAddr(ADDR_IND, local_pc, local_ssn, NULL, 0);
            beg.SetDestAddr(ADDR_IND, remote_pc, remote_ssn, NULL, 0);

            if (TCAP_AllocateDialogueId( &did ) != ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Fail to allocate dialog id!" << endl;
                break;
            }

            beg.SetDialogueID( did );
            //beg.SetQualityOfService( QOSI_RET_OPT );

             
			if (SendAnalyzedInformationIL( &beg ) == ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "InvokeLast sent." << endl;
            }

            else
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Fail to send InvokeLast component!" << endl;
            }
            break;

        case 6:
            end.SetDialogueID( dlg->GetDialogueID() );

            // Set termination type to Basic End
            end.SetPreArrangedEnd( false );

            if (SendAnalyzedInformationRRL( &end, cpt) == ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "ReturnResultLast sent." << endl;
            }
			
			else
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Fail to send ReturnResultLast!" << endl;
            }

            // Free allocated memory for received component and dialogue
            if (cpt)
            {
                delete cpt;
            }

            if (dlg)
            {
                delete dlg;
            }
            break;

			case 7:
		    
            beg.SetOrigAddr(ADDR_IND, local_pc, local_ssn, NULL, 0);
            beg.SetDestAddr(ADDR_IND, remote_pc, remote_ssn, NULL, 0);

            if (TCAP_AllocateDialogueId( &did ) != ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Fail to allocate dialog id!" << endl;
                break;
            }

            beg.SetDialogueID( did );

             
			if (SendConnectionFailureReportIL( &beg ) == ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "ConnectionFailureRep InvokeLast sent." << endl;
            }

            else
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Fail to send ConnectionFailureRep InvokeLast component!" << endl;
            }
            break;


			case 8:
		    
            beg.SetOrigAddr(ADDR_IND, local_pc, local_ssn, NULL, 0);
            beg.SetDestAddr(ADDR_IND, remote_pc, remote_ssn, NULL, 0);

            if (TCAP_AllocateDialogueId( &did ) != ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Fail to allocate dialog id!" << endl;
                break;
            }

            beg.SetDialogueID( did );

             
			if (SendConnectResourceIL( &beg ) == ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "ConnectResource InvokeLast sent." << endl;
            }

            else
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Fail to send ConnectResource InvokeLast component!" << endl;
            }
            break;


			case 9:
		    
            beg.SetOrigAddr(ADDR_IND, local_pc, local_ssn, NULL, 0);
            beg.SetDestAddr(ADDR_IND, remote_pc, remote_ssn, NULL, 0);

            if (TCAP_AllocateDialogueId( &did ) != ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Fail to allocate dialog id!" << endl;
                break;
            }

            beg.SetDialogueID( did );

             
			if (SendFacilitySelectedAndAvailableIL( &beg ) == ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "FacilitySelectedAndAvailable InvokeLast sent." << endl;
            }

            else
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Fail to send FacilitySelectedAndAvailable InvokeLast component!" << endl;
            }
            break;


		case 10:
            end.SetDialogueID( dlg->GetDialogueID() );

            // Set termination type to Basic End
            end.SetPreArrangedEnd( false );

            if (SendFacilitySelectedAndAvailableRRL( &end, cpt) == ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "FacilitySelectedAndAvailable ReturnResultLast sent." << endl;
            }
			
			else
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Fail to send ReturnResultLast!" << endl;
            }

            // Free allocated memory for received component and dialogue
            if (cpt)
            {
                delete cpt;
            }

            if (dlg)
            {
                delete dlg;
            }
            break;

		case 11:
            beg.SetOrigAddr(ADDR_IND, local_pc, local_ssn, NULL, 0);
            beg.SetDestAddr(ADDR_IND, remote_pc, remote_ssn, NULL, 0);

            if (TCAP_AllocateDialogueId( &did ) != ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Fail to allocate dialog id!" << endl;
                break;
            }

            beg.SetDialogueID( did );
            beg.SetQualityOfService( QOSI_RET_OPT );

            if (SendSeizeResourceIL( &beg ) == ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "SeizeResource InvokeLast sent." << endl;
            }
             

            else
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Fail to send InvokeLast component!" << endl;
            }
            break;

        case 12:
            end.SetDialogueID( dlg->GetDialogueID() );

            // Set termination type to Basic End
            end.SetPreArrangedEnd( false );

            if (SendSeizeResourceRRL( &end, cpt) == ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "SeizeResource ReturnResultLast sent." << endl;
            }
			
			else
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Fail to send ReturnResultLast!" << endl;
            }

            // Free allocated memory for received component and dialogue
            if (cpt)
            {
                delete cpt;
            }

            if (dlg)
            {
                delete dlg;
            }
            break;
		

		case 13:
            beg.SetOrigAddr(ADDR_IND, local_pc, local_ssn, NULL, 0);
            beg.SetDestAddr(ADDR_IND, remote_pc, remote_ssn, NULL, 0);

            if (TCAP_AllocateDialogueId( &did ) != ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Fail to allocate dialog id!" << endl;
                break;
            }

            beg.SetDialogueID( did );
            beg.SetQualityOfService( QOSI_RET_OPT );

            if (SendSRFDirectiveIL( &beg ) == ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "SRFDirective InvokeLast sent." << endl;
            }
          
            else
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Fail to send SRFDirective InvokeLast component!" << endl;
            }
            break;

        case 14:
            end.SetDialogueID( dlg->GetDialogueID() );

            // Set termination type to Basic End
            end.SetPreArrangedEnd( false );

            if (SendSRFDirectiveRRL( &end, cpt) == ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "SRFDirective ReturnResultLast sent." << endl;
            }			
			else
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Fail to send SRFDirective ReturnResultLast!" << endl;
            }

            // Free allocated memory for received component and dialogue
            if (cpt)
            {
                delete cpt;
            }

            if (dlg)
            {
                delete dlg;
            }
            break;


		case 15:
            beg.SetOrigAddr(ADDR_IND, local_pc, local_ssn, NULL, 0);
            beg.SetDestAddr(ADDR_IND, remote_pc, remote_ssn, NULL, 0);

            if (TCAP_AllocateDialogueId( &did ) != ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Fail to allocate dialog id!" << endl;
                break;
            }

            beg.SetDialogueID( did );
            beg.SetQualityOfService( QOSI_RET_OPT );

            if (SendTBusyIL( &beg ) == ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "InvokeLast sent." << endl;
            }
             
            else
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Fail to send InvokeLast component!" << endl;
            }
            break;

        case 16:
            end.SetDialogueID( dlg->GetDialogueID() );

            // Set termination type to Basic End
            end.SetPreArrangedEnd( false );

            if (SendTBusyRRL( &end, cpt) == ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "ReturnResultLast sent." << endl;
            }
			
			else
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Fail to send ReturnResultLast!" << endl;
            }

            // Free allocated memory for received component and dialogue
            if (cpt)
            {
                delete cpt;
            }

            if (dlg)
            {
                delete dlg;
            }
            break;

		case 17:
            beg.SetOrigAddr(ADDR_IND, local_pc, local_ssn, NULL, 0);
            beg.SetDestAddr(ADDR_IND, remote_pc, remote_ssn, NULL, 0);

            if (TCAP_AllocateDialogueId( &did ) != ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Fail to allocate dialog id!" << endl;
                break;
            }

            beg.SetDialogueID( did );
            beg.SetQualityOfService( QOSI_RET_OPT );

            if (SendTNoAnswerIL( &beg ) == ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "InvokeLast sent." << endl;
            }
             
            else
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Fail to send InvokeLast component!" << endl;
            }
            break;

        case 18:
            end.SetDialogueID( dlg->GetDialogueID() );

            // Set termination type to Basic End
            end.SetPreArrangedEnd( false );

            if (SendTNoAnswerRRL( &end, cpt) == ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "ReturnResultLast sent." << endl;
            }
			
			else
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Fail to send ReturnResultLast!" << endl;
            }

            // Free allocated memory for received component and dialogue
            if (cpt)
            {
                delete cpt;
            }

            if (dlg)
            {
                delete dlg;
            }
            break;

        case 19:
            // Send error component
            end.SetDialogueID( dlg->GetDialogueID() );
            end.SetPreArrangedEnd( false );

            printf("\n");
            printf("Select error code:\n");
            printf("-------------------------------\n");
            printf("[%3d] UnrecognizedMIN\n", ERR_UnrecognizedMIN);
            printf("[%3d] UnrecognizedESN\n", ERR_UnrecognizedESN);
            printf("[%3d] MIN_HLRMismatch\n", ERR_MIN_HLRMismatch);
            printf("[%3d] OperationSequenceProblem\n",
                   ERR_OperationSequenceProblem);
            printf("[%3d] ResourceShortage\n", ERR_ResourceShortage);
            printf("[%3d] OperationNotSupported\n", ERR_OperationNotSupported);
            printf("[%3d] TrunkUnavailable\n", ERR_TrunkUnavailable);
            printf("[%3d] ParameterError\n", ERR_ParameterError);
            printf("[%3d] SystemFailure\n", ERR_SystemFailure);
            printf("[%3d] UnrecognizedParameterValue\n",
                   ERR_UnrecognizedParameterValue);
            printf("[%3d] FeatureInactive\n", ERR_FeatureInactive);
            printf("[%3d] MissingParameter\n", ERR_MissingParameter);
            printf("\n");
            printf("->> ");

            cin >> error_code;

            error_cpt.SetInvokeID( cpt->GetInvokeID() );
            error_cpt.SetError( true, (ITS_OCTET)error_code );

            traceComponent( &error_cpt );

            // Send error component
            ret = TCAP_Component::Send((ITS_HANDLE)trin->GetTransport(), &end,
                                          &error_cpt);
            if (ret == ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Error component send success." << endl;
            }
            else
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Failed to send Error component." << endl;
                cout << "Error: " << ret << endl;
            }

            // Send end dialog
            ret = TCAP_Dialogue::Send((ITS_HANDLE)trin->GetTransport(), &end);
    
            if (ret == ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "End dialogue send success." << endl;
            }
            else
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Failed to send end dialogue." << endl;
                cout << "Error: " << ITS_GetErrorText( ret ) << endl;
            }

            // Free allocated memory for received component and dialogue
            if (cpt)
            {
                delete cpt;
            }

            if (dlg)
            {
                delete dlg;
            }
            break;

        case 20:
            // Send reject component
            end.SetDialogueID( dlg->GetDialogueID() );
            end.SetPreArrangedEnd( false );

            reject_cpt.SetInvokeID( cpt->GetInvokeID() );
            reject_cpt.SetProblem(TCAP_PROB_INVOKE_ANSI,
                                  TCAP_PROB_SPEC_INV_INCORRECT_PARAM_ANSI);

            traceComponent( &reject_cpt );

            // Send reject component
            ret = TCAP_Component::Send((ITS_HANDLE)trin->GetTransport(), &end,
                                          &reject_cpt);
            if (ret == ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Reject component send success." << endl;
            }
            else
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Failed to send reject component." << endl;
                cout << "Error: " << ret << endl;
            }

            // Send end dialog
            ret = TCAP_Dialogue::Send((ITS_HANDLE)trin->GetTransport(), &end);
    
            if (ret == ITS_SUCCESS)
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "End dialogue send success." << endl;
            }
            else
            {
                printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
                cout << "Failed to send end dialogue." << endl;
                cout << "Error: " << ITS_GetErrorText( ret ) << endl;
            }

            // Free allocated memory for received component and dialogue
            if (cpt)
            {
                delete cpt;
            }

            if (dlg)
            {
                delete dlg;
            }
            break;

        }
	}

    /* Clean up before exit*/
    printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
    cout << "Doing clean up before exit." << endl;
#if 0
    printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
    cout << "Delete application." << endl;
    ROUTE_DeleteApplication(ITS_DEFAULT_USER_SRC, &hdr);
#endif

    printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
    cout << "Deleting transports." << endl;

    
    printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
    printf("Exit threads...\n");
    
    if (trin)
    {
        delete trin;
    }

    if (trout)
    {
        delete trout;
    }

    ITS_Thread::Exit(0);


    printf("[WIN Test]: %s: line %d\n", __FILE__, __LINE__);
    cout << "GlobalStop." << endl;
    ITS_GlobalStop();
	ITS_RemFeature(itsINTELLISS7_Class);

    return ret;
}

    
