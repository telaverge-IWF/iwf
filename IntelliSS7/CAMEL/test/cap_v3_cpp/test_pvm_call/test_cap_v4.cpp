/////////////////////////////////////////////////////////////////////////////////
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
//  ID: $Id: test_cap_v4.cpp,v 9.1 2005/03/23 12:51:14 cvsadmin Exp $
//
////////////////////////////////////////////////////////////////////////////////

#include <its++.h>

#include <string>
#include <iostream>

#include <Asn.h>
#include <AsnException.h>

#include <cap_cpp.h>
#include <cap_v3_apply_charging_arg.h>
#include <cap_v4_apply_charging_report_arg.h>
#include <cap_v4_assist_request_instructions_arg.h>
#include <cap_v4_call_gap_arg.h>
#include <cap_v4_call_information_request_arg.h>
#include <cap_v4_call_information_report_arg.h>
#include <cap_v4_initial_dp_arg.h>
#include <cap_v4_connect_to_resource_arg.h>
#include <cap_v4_connect_arg.h>
#include <cap_v4_cancel_arg.h>
#include <cap_v4_continue_with_argument_arg.h>
#include <cap_v4_establish_temporary_connection_arg.h>
#include <cap_v4_event_report_bcsm_arg.h>
#include <cap_v4_furnish_charging_information_arg.h>
#include <cap_v4_release_call_arg.h>
#include <cap_v4_request_report_bcsm_event_arg.h>
#include <cap_v4_reset_timer_arg.h>
#include <cap_v4_send_charging_information_arg.h>
#include <cap_v4_play_announcement_arg.h>
#include <cap_v4_prompt_and_collect_user_information_arg.h>
#include <cap_v4_received_information_arg.h>


#if defined(ITS_NAMESPACE)
using namespace std;
using namespace its;
using namespace cap_v4;
using namespace cap;
#endif



// Functions for encoding and decoding
//
int EncodeMsg(AsnObject* p, Octets** octets);
int DecodeMsg(AsnObject* p, Octets* octets);
void decodeCAPMsg(ITS_LONG code, Octets *octets);

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


enum {

    ERR_UnrecognizedMIN                     =   0x81U,
    ERR_UnrecognizedESN                     =   0x82U,
    ERR_MIN_HLRMismatch                     =   0x83U,
    ERR_OperationSequenceProblem            =   0x84U,
    ERR_ResourceShortage                    =   0x85U,
    ERR_OperationNotSupported               =   0x86U,
    ERR_TrunkUnavailable                    =   0x87U,
    ERR_ParameterError                      =   0x88U,
    ERR_SystemFailure                       =   0x89U,
    ERR_UnrecognizedParameterValue          =   0x8AU,
    ERR_FeatureInactive                     =   0x8BU,
    ERR_MissingParameter                    =   0x8CU

};

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will encode a CAPV3 message.
 *
 *  Input Parameters:
 *      p - pointer to the CAPV3 message to be encoded
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      octets - used to store the encoded value of the CAPV3 message
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
EncodeMsg(AsnObject* p, Octets** octets)
{
    // Print ASN.1 value before encoding.
    printf("[CAPV3 TEST]: %s: line %d\n", __FILE__, __LINE__);
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

        return !ITS_SUCCESS;
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
 *      This function will decode an encoded CAPV3 message.
 *
 *  Input Parameters:
 *      octets - the encoded value of a CAPV3 message
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      p - storage for decoded CAPV3 message
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
DecodeMsg(AsnObject* p, Octets* octets)
{
    // Decoding using ASN.1 BER.
    try
    {
        p->Decode(*octets);
    }
    catch (AsnDecodeError& exc)
    {
        printf("[CAPV3 TEST]: %s: line %d\n", __FILE__, __LINE__);
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Exception during decoding phase..." << endl;
        cout << exc.GetDescription() << endl;
        cout << "Exit test..." << endl;
    }

    // Print ASN.1 value after decoding.
    printf("[CAPV3 TEST]: %s: line %d\n", __FILE__, __LINE__);
    cout << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Printing ASN.1 value after decoding..." << endl;
    cout << endl << *p << endl;
}

ForwardServiceInteractionInd*  InitializeForwardServiceInteractionInd1()
{
    ForwardServiceInteractionInd* fsi
				= new ForwardServiceInteractionInd;

	byte cnfTreatmentIndicatorarray[] = { 0x01 };
	byte divTreatmentIndicatorarray[] = { 0x01 };

	ForwardServiceInteractionInd:: ConferenceTreatmentIndicator* cti=
        new ForwardServiceInteractionInd:: ConferenceTreatmentIndicator(FixedByteArrayToVector(cnfTreatmentIndicatorarray));
						
	ForwardServiceInteractionInd:: CallDiversionTreatmentIndicator* cdti=
        new ForwardServiceInteractionInd:: CallDiversionTreatmentIndicator(FixedByteArrayToVector(divTreatmentIndicatorarray)); 
																  
    // Add the 2 objects to fsi ptr.
    fsi->SetConferenceTreatmentIndicator(cti);
    fsi->SetCallDiversionTreatmentIndicator(cdti);

	// populate other optional parameters later
	return fsi;
}

void  InitializeForwardServiceInteractionInd2(const ForwardServiceInteractionInd& fsi2)

{
       printf("\n test print2");
	byte cmpTreatmentIndicatorarray[] = { 0x01 };
        byte cprTreatmentIndicatorarray[] = { 0x01 };

    ForwardServiceInteractionInd:: CallingPartyRestrictionIndicator* cpri =
        new ForwardServiceInteractionInd:: CallingPartyRestrictionIndicator(FixedByteArrayToVector(cprTreatmentIndicatorarray));

       printf("\n test print4");
   const_cast<ForwardServiceInteractionInd&>(fsi2).SetCallingPartyRestrictionIndicator(cpri);
       printf("\n test print5");

	// populate other optional parameters later
}


ServiceInteractionIndicatorsTwo* InitializeServiceInteractionIndicatorsTwo()
{
	ServiceInteractionIndicatorsTwo* si2 
				= new ServiceInteractionIndicatorsTwo;

	byte holdTreatmentIndicatorarray[] = { 0x01 };
	byte cwTreatmentIndicatorarray[] = { 0x01 };
	byte ectTreatmentIndicatorarray[] = { 0x01 };
    	long valparm = 1;

	ServiceInteractionIndicatorsTwo:: HoldTreatmentIndicator* hti=
        new ServiceInteractionIndicatorsTwo::HoldTreatmentIndicator(FixedByteArrayToVector(holdTreatmentIndicatorarray));
																	
	ServiceInteractionIndicatorsTwo:: CwTreatmentIndicator* cwti=
        new ServiceInteractionIndicatorsTwo::CwTreatmentIndicator(FixedByteArrayToVector(cwTreatmentIndicatorarray)); 
																  
	ServiceInteractionIndicatorsTwo:: EctTreatmentIndicator* ecti =
        new ServiceInteractionIndicatorsTwo::EctTreatmentIndicator(FixedByteArrayToVector(ectTreatmentIndicatorarray)); 
																   
    ConnectedNumberTreatmentInd* cnti =
        new ConnectedNumberTreatmentInd(valparm);
	
    
    // Add the objects to si2 ptr.
    si2->SetHoldTreatmentIndicator(hti);
    si2->SetCwTreatmentIndicator(cwti);
    si2->SetEctTreatmentIndicator(ecti);
    si2->SetConnectedNumberTreatmentInd(cnti);
    
    si2->SetForwardServiceInteractionInd(InitializeForwardServiceInteractionInd1());
    printf("\n test print starts");
    const ForwardServiceInteractionInd& fsi2=si2->GetForwardServiceInteractionInd();
    
    printf("\n test print1");
    
    InitializeForwardServiceInteractionInd2(fsi2);
    
   // si2->SetForwardServiceInteractionInd(const_cast<ForwardServiceInteractionInd*>(&fsi2));
	// populate other optional parameters later
	return si2;

}

CalledPartyNumber* InitializeCalledPartyNumber()
{
    byte array[] = { 0x09, 0x08, 0x02, 0x07, 0x07, 0x02, 0x03 };
    CalledPartyNumber *cpn;

    // Create a CalledPartyNumber object
    cpn = new CalledPartyNumber(FixedByteArrayToVector(array));
    return cpn;
}

ConnectToResourceArg::ResourceAddress* InitializeResourceAddress()
{
    long val = 0;
    ConnectToResourceArg::ResourceAddress *ra;

    ra = new ConnectToResourceArg::ResourceAddress();
    ra->SetChoiceIpRoutingAddress(InitializeCalledPartyNumber());
    return ra;
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
    int ret = ITS_SUCCESS;
    int choice = 0, i = 0;
    int instance = 0;
    
    ITS_Event ev;
    ITS_ByteArray buf;
    std::vector<byte> data;

 
/**************************************************************************************
The following piece of code has been cut and pasted for temporarily executing a testcase to track down
a nesting parameter related problem: in such a case certain parameters cannot be populated 
***************************************************************************************/

    {
        int result = 0;
        int timeout = 0;
        
        
        Octets *encOctets;
        string str;
        ConnectToResourceArg* connectToResourceArg = new ConnectToResourceArg();

        // Set Parameters for CAP message to send
        cout << endl;
        cout << "Setting ConnectToResource Parameters:" << endl;
        cout << "----------------------------------------" << endl;
        cout << endl;


        // Ask the user to send a badly encoded message or a valid message

        {
 
            // User wanted to send a valid CAP message
 
            connectToResourceArg->SetResourceAddress(InitializeResourceAddress());
        }


        // Ask user to include optional parameters


        // ServiceInteractionIndicatorsTwo

        {
            connectToResourceArg->SetServiceInteractionIndicatorsTwo(InitializeServiceInteractionIndicatorsTwo());
        }


        // Encode message
        if (EncodeMsg(connectToResourceArg, &encOctets) != ITS_SUCCESS)
        {
            cout << "Bye bye " << endl;

            cout << "deleting allocated memory ....." << endl;
        
            // Free allocated memory
            delete connectToResourceArg;
            connectToResourceArg = NULL;

            return;
        }
        else
        {
        	   DecodeMsg(connectToResourceArg, encOctets);
        }
        

        cout << "deleting allocated memory ....." << endl;
        
        // Free allocated memory
        delete connectToResourceArg;
        connectToResourceArg = NULL;
        delete encOctets;
        encOctets = NULL;
    }

    return EXIT_SUCCESS;

}

