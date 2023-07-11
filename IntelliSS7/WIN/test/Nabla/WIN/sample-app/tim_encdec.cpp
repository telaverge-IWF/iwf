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
// CONTRACT:  TCAP Interface Module                                                     //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
//  ID: $Id: tim_encdec.cpp,v 9.1 2005/03/23 12:52:46 cvsadmin Exp $
//
// LOG: $Log: tim_encdec.cpp,v $
// LOG: Revision 9.1  2005/03/23 12:52:46  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 1.2  2003/03/28 21:12:49  rsonak
// LOG: Copied from PR6.1
// LOG:
// LOG: Revision 1.1.2.1  2002/09/26 17:54:10  pmandal
// LOG: simulators for WIN messages
// LOG:
// LOG: Revision 1.1.2.1  2002/09/23 15:51:47  pmandal
// LOG: Commit send/receive code
// LOG:
// LOG: Revision 1.1.2.2  2002/09/19 17:53:40  ngoel
// LOG: add response encode/decode
// LOG:
// LOG: Revision 1.1.2.1  2002/09/19 17:36:36  ngoel
// LOG: TCAP Interface Module
// LOG:
// LOG:
// LOG:
//
////////////////////////////////////////////////////////////////////////////////
//
#include <engine++.h>
#include <Asn.h>
#include <AsnException.h>
#include <vector>
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
#if !defined(WIN_TEST_H)
#define WIN_TEST_H
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

#if defined(ITS_NAMESPACE)
using namespace std;
using namespace its;
using namespace win;
#endif



	
// Communication

ITS_Worker*     trin;
ITS_Worker*     trout;

ITS_Thread* recvMTP3Thread = NULL;
ITS_Thread* recvTCAPThread = NULL;


// TCAP containers

int frID = 0;
int srID = 0;
int aiID = 0;
int fsaID = 0;
int sreID = 0;
int sdID = 0;
int tbID = 0;

#endif // !defined(WIN_TEST_H)

#endif


ITS_OCTET LocationArg[] = { 0x30,0x1c,0x04,0x08,0x62,0x08,0x61,0x09,
                                     0x00,0x00,0x20,0xf8,0x81,0x07,0x91,0x53,
                                     0x91,0x11,0x53,0x29,0x00,0x04,0x07,0x91,
                                      0x53,0x91,0x11,0x53,0x29,0x00 };
#define LOC_ARG_LEN 30
vector <byte> vParam(LocationArg, LocationArg + 30);
// Functions for encoding and decoding

void EncodeMsg(AsnObject* p, Octets** octets);
void DecodeMsg(AsnObject* p, Octets* octets);

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

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function encodes a dummy TCAP parameters.
 *
 *  Input Parameters:
 *      None 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
vector <byte>
TIM_Encode()
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
    
    cout << *fril << endl;
    EncodeMsg( fril, &encOctets );
    vector<byte> encodedArg = encOctets->GetArray();
//    DecodeMsg( fril, encOctets );

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
    return encodedArg;
   
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function decodes TCAP parameters.
 *
 *  Input Parameters:
 *      None 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS is always returned.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
TIM_Decode(vector <byte> &data)
{
    ITS_UINT i;
    Octets *encOctets;
    FeatureRequestIL *fril = new FeatureRequestIL();
    encOctets = new Octets(data);
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
    return ITS_SUCCESS;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function encodes a TCAP result parameter.
 *
 *  Input Parameters:
 *      None 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
vector <byte>
TIM_EncodeResponse()
{
    ITS_UINT i;

    cout << "Result Parameters Encoded " << endl;
    for( i = 0; i < vParam.size(); i++)
    {
	if(!(i % 8))
        {
            printf("\n");
            printf("\t");
        }
        printf("%x ", vParam[i]);
    }
    printf("\n");

    return vParam;

}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function decodes TCAP parameters.
 *
 *  Input Parameters:
 *      None 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS is always returned.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
TIM_DecodeResponse(vector <byte> &data)
{
    ITS_UINT i;

    cout << "Result Response Parameters " << endl;
    for( i = 0; i < data.size(); i++)
    {
	if(!(i % 8))
        {
            printf("\n");
            printf("\t");
        }
        printf("%x ", data[i]);
    }
    printf("\n");

    return ITS_SUCCESS;
}

