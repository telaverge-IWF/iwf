///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//      Copyright 2002 IntelliNet Technologies, Inc. All Rights Reserved.    //
//              Manufactured in the United States of America.                //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       //
//                                                                           //
//    This product and related documentation is protected by copyright and   //
//    distributed under licenses restricting its use, copying, distribution  //
//    and decompilation.  No part of this product or related documentation   //
//    may be reproduced in any form by any means without prior written       //
//    authorization of IntelliNet Technologies and its licensors, if any.    //
//                                                                           //
//    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      //
//    government is subject to restrictions as set forth in subparagraph     //
//    (c)(1)(ii) of the Rights in Technical Data and Computer Software       //
//    clause at DFARS 252.227-7013 and FAR 52.227-19.                        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// CONTRACT: INTERNAL                                                        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//
//  ID: $Id: test_encode_send_charging_information_arg.cpp,v 9.1 2005/03/23 12:51:47 cvsadmin Exp $
//
///////////////////////////////////////////////////////////////////////////////

//
//  INAP ETSI CS1 ASN.1 codec example.
//
//  This example shows how to build (create, insert data and encode)
//  for the INAP SendChargingInformation operation argument.
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

#include <iostream>

#include <AsnException.h>

#include <inap_cpp.h>
#include <inap_etsi_cs1_send_charging_information_arg.h>

using namespace std;
using namespace its;
using namespace inap;
using namespace inap_etsi_cs1;



///////////////////////////////////////////////////////////////////////////////
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


///////////////////////////////////////////////////////////////////////
//
// Useage:
//
//   Encode:
//     // Call BuildSendChargingInformationArg function.
//     vector<byte> encodedSendChargingInformationArg =
//        BuildOperationSendChargingInformationArg();
//
///////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
//  How to Build an INAP SendChargingInformation operation argument
//  (SendChargingInformationArg):
//
//  o   Create SendChargingInformation object.
//
//  o   Insert data step by step in the created SendChargingInformation object
//      (i.e. populate various parameters of the SendChargingInformation
//      operation argument).
//  
//  o   Encode the SendChargingInformationArg object to produce a
//      SendChargingInformation encoded value.
//

vector<byte> 
BuildOperationSendChargingInformationArg()
{
    //  [1] Create SendChargingInformationArg object.

    SendChargingInformationArg*
        sendChargingInformationArg = new SendChargingInformationArg();

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Memory management note: all the following parameter objects that are
    //  used to populate the SendChargingInformation object must be created in
    //  the heap (i.e. using operator new) and not in the stack. They are
    //  automatically deleted when the connectArg object is deleted. Only the
    //  SCIBillingChargingCharacteristics object itself can be created in the
    //  stack. 

    ////////////////////////////////////////////////////////////////////////////

    //  [2] Populate mandatory parameter "SCIBillingChargingCharacteristics".

    //  [2-1] Create SCIBillingChargingCharacteristics object.

    byte fixedArray1[] = { 0x11, 0x12, 0x14 };

    SCIBillingChargingCharacteristics*
        sciBillingChargingCharacteristics = new
            SCIBillingChargingCharacteristics(
                  FixedByteArrayToVector(fixedArray1));

    sendChargingInformationArg->SetSCIBillingChargingCharacteristics(
        sciBillingChargingCharacteristics);

    //  [3] Create mandatory parameter "LegID".

    LegID* legID = new LegID();

    //  [3-1] Create LegType object.

    byte fixedArray2[] = {0x1};

    LegType legType(FixedByteArrayToVector(fixedArray2));

    //  [3-2] Populate LegID object.

    legID->SetChoiceSendingSideID(legType);

    sendChargingInformationArg->SetLegID(legID);

    //  [3] Populate optional parameter "extensions".
    //  [3-1] Create Extensions object.

    SendChargingInformationArg::Extensions*
        extensions = new SendChargingInformationArg::Extensions();

    //  [3-2-1] Populate parameter "extensionField1".

    //  [3-2-2] Create ExtensionField object.

    ExtensionField* extensionField1 = new ExtensionField();

    //  [3-1-1] Add ExtensionField::Type object to ExtensionField object.

    ExtensionField::Type* type1 = new ExtensionField::Type();

    type1->SetValue(2);

    ExtensionField::Criticality*
        criticality1 = new ExtensionField::Criticality();

    criticality1->SetValue(0);

    ExtensionField::Value* value1 = new ExtensionField::Value();

    value1->SetAny(new AsnOctetString(0x11));

    extensionField1->SetType(type1);
    extensionField1->SetCriticality(criticality1);
    extensionField1->SetValue(value1);

    extensions->AddElement(extensionField1);

    //  [3-3-1] Populate parameter "extensionField2".

    //  [3-3-2] Create ExtensionField object.

    ExtensionField* extensionField2 = new ExtensionField();

    //  [3-3-3] Add ExtensionField::Type object to ExtensionField object.

    ExtensionField::Type* type2 = new ExtensionField::Type();

    type2->SetValue(1);

    ExtensionField::Criticality*
        criticality2 = new ExtensionField::Criticality();

    criticality2->SetValue(0);

    ExtensionField::Value* value2 = new ExtensionField::Value();

    long var1 = 1;

    value2->SetAny(new AsnInteger(var1));

    extensionField2->SetType(type2);
    extensionField2->SetCriticality(criticality2);
    extensionField2->SetValue(value2);

    extensions->AddElement(extensionField2);

    //  [3-4] Set Extensions object in EstablishTemporaryConnectionArg object.

    sendChargingInformationArg->SetExtensions(extensions);

    ////////////////////////////////////////////////////////////////////////////

    //  [4] Encode SendChargingInformationArg object.

    Octets* octets = NULL;

    try
    {
        //  Can throw and AsnEncodeError execption. 

        octets = sendChargingInformationArg->Encode();
    }
    catch (AsnEncodeError& encodeError)
    {
        cout << endl << encodeError.GetDescription() << endl;

        //  More specific error processing should be added here.

        //  By default re-throw exception.

        throw encodeError;
    }

    cout << endl;
    cout << "Printing SendChargingInformationArg ASN.1 encoded value...\n";
    cout << *octets;
    cout << endl;

    ////////////////////////////////////////////////////////////////////////////

    //  [5] Retrieve SendChargingInformationArg ASN.1 encoded value from
    //   octets object.

    vector<byte> encodedSendChargingInformationArg = octets->GetArray();

    ////////////////////////////////////////////////////////////////////////////

    //  [6] Free all memory allocated on the heap.

    //  [6-1] Delete SendChargingInformationArg object (and therefore all the
    //  parameter objects that have been previously set).

    delete sendChargingInformationArg;

    //  [6-2] Delete Octets object created by the call to Encode.

    delete octets;

    ////////////////////////////////////////////////////////////////////////////

    //  [7] Return (by value) EstablishTemporaryConnectionArg ASN.1 encoded
    //  value.

    return encodedSendChargingInformationArg;
}
