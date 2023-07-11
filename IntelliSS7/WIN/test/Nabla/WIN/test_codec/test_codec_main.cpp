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
//  ID: $Id: test_codec_main.cpp,v 9.1 2005/03/23 12:52:46 cvsadmin Exp $
//
////////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32
#pragma warning (disable : 4786)
#endif

// IntelliSS7 headers

#include <its++.h>

#include <string>
#include <iostream>
#include <stdio.h>

// ASN CPP headers

#include <Asn.h>
#include <AsnException.h>
#include <Octets.h>

//
// Protocol headers
//
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

#if defined(ITS_NAMESPACE)
using namespace std;
using namespace its;
using namespace win;
#endif

// Functions for encoding and decoding

void EncodeMsg(AsnObject* p, Octets** octets);
void DecodeMsg(AsnObject* p, Octets* octets);

////////////////////////////////////////////////////////////////////////////////
//
//  Utilities.
//

//
//  Macro to get the size (count of items) of a fixed array.
//
#define FixedArraySize(array)       \
    (sizeof(array) / sizeof(array[0]))


//  Macro to convert fixed arrays (of bytes) to vectors.

#define FixedByteArrayToVector(array)   \
    (vector<byte>(array, array + FixedArraySize(array)))


//  Macro to convert fixed arrays (of booleans) to vectors.

#define FixedBooleanArrayToVector(array)   \
    (vector<bool>(array, array + FixedArraySize(array)))


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will encode a WIN message.
 *
 *  Input Parameters:
 *      p - pointer to the WIN message to be encoded
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
 *
 ****************************************************************************/
int
BuildOperationFeatureRequestIL()
{
    int result = ITS_SUCCESS;
    ITS_OCTET family = 0x00, code = 0x00;
    Octets *encOctets;
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
    DecodeMsg( fril, encOctets );

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

//.implementation:protected
//
//  Purpose:
//       To send a FeatureRequest result last using the WIN library.
// 
//   Input Parameters:
// 
//   Input Parameters:
// 
// 
int
main(int argc, char **argv)
{
   cout << endl << "Begin WIN ASN.1 codec example..." << endl;

   try
   {
       // IntelliSS7 initialization (including licensing).

        
       //int res = ITS_AddFeature(itsDSM_StubImplClass);

       //res = ITS_GlobalStart(0);

       //if (res != ITS_SUCCESS)
       //{
       //    throw ITS_Error(res, __FILE__, __LINE__);
       //}


       ////////////////////////////////////////////////////////////////////////

       //  [1] Call BuildOperationAuthenticationDirectiveIL function.
       // BuildOperationAuthenticationDirectiveIL();
        
       //  [2] Call BuildOperationFeatureRequestRRL function.
         
       BuildOperationFeatureRequestIL();

       
       ///////////////////////////////////////////////////////////////////////
        
       // IntelliSS7 termination.
        
       //ITS_GlobalStop();
   }
    
   catch (ITS_GenericException& exp)
   {    
       cout << endl << exp.GetDescription() << endl;
       char c = '\0';
       cin.get(c);
       return EXIT_SUCCESS;
   }
   //ITS_GlobalStop();
}

    
