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
//  ID: $Id: test_encode_connect_to_resource_arg.cpp,v 9.1 2005/03/23 12:51:47 cvsadmin Exp $
//
///////////////////////////////////////////////////////////////////////////////

//
//  INAP ETSI CS1 ASN.1 codec example.
//
//  This example shows how to build (create, insert data and encode)
//  for the INAP ConnectToResourceArg operation argument.
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
#include <inap_etsi_cs1_connect_to_resource_arg.h>

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
//     // Call BuildOperationConnectToResourceArg function.
//     vector<byte> encodedConnectToResourceArg =
//        BuildOperationConnectToResourceArg();
//
///////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
//  How to Build an INAP Connect operation argument (ConnectToResourceArg):
//
//  o   Create ConnectToResourceArg object.
//
//  o   Insert data step by step in the created ConnectToResourceArg object
//      (i.e. populate various parameters of the Connect operation argument).
//  
//  o   Encode the ConnectToResourceArg object to produce a
//      ConnectToResourceArg encoded value.
//

vector<byte> 
BuildOperationConnectToResourceArg()
{
    //  [1] Create ConnectToResourceArg object.

    ConnectToResourceArg* connectToResourceArg = new ConnectToResourceArg();

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Memory management note: all the following parameter objects that are
    //  used to populate the ConnectArg object must be created in the heap (i.e.
    //  using operator new) and not in the stack. They are automatically deleted
    //  when the connectArg object is deleted. Only the ConnectToResourceArg
    //  object itself can be created in the stack. 

    ////////////////////////////////////////////////////////////////////////////

    //  [2] Populate mandatory parameter "resourceAddress".

    //  [2-1] Create ResourceAddress object.

    ConnectToResourceArg::ResourceAddress*
        resourceAddress = new ConnectToResourceArg::ResourceAddress();

    //  [2-2] Populate ResourceAddress object.

    byte fixedArray1[] = { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16 };

    IPRoutingAddress ipRoutingAddress(FixedByteArrayToVector(fixedArray1));

    resourceAddress->SetChoiceIpRoutingAddress(ipRoutingAddress);

    //  [2-3] Set ResourceAddress object in ConnectToResourceArg object.

    connectToResourceArg->SetResourceAddress(resourceAddress);

    //  [3] Populate optional parameter "extensions".
    //  [3-1] Create Extensions object.

    ConnectToResourceArg::Extensions*
        extensions = new ConnectToResourceArg::Extensions();

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

    //  [3-4] Set Extensions object in ConnectToResourceArg object.

    connectToResourceArg->SetExtensions(extensions);

    //  [4] Populate optional parameter "serviceInteractionIndicators".
    //  [4-1] Create ServiceInteractionIndicators object.

    byte fixedArray2[] = { 0x01, 0x02, 0x03 };

    ServiceInteractionIndicators* serviceInteractionIndicators
        = new ServiceInteractionIndicators(FixedByteArrayToVector(fixedArray2));

    //  [4-2] Set ServiceInteractionIndicators object in ConnectToResourceArg
    //  object.

    connectToResourceArg->SetServiceInteractionIndicators(
        serviceInteractionIndicators);

    ////////////////////////////////////////////////////////////////////////////

    //  [5] Encode ConnectToResourceArg object.

    Octets* octets = NULL;

    try
    {
        //  Can throw and AsnEncodeError execption. 

        octets = connectToResourceArg->Encode();
    }
    catch (AsnEncodeError& encodeError)
    {
        cout << endl << encodeError.GetDescription() << endl;

        //  More specific error processing should be added here.

        //  By default re-throw exception.

        throw encodeError;
    }

    cout << endl;
    cout << "Printing ConnectToResourceArg ASN.1 encoded value..." << endl;
    cout << *octets;
    cout << endl;

    ////////////////////////////////////////////////////////////////////////////

    //   [6] Retrieve ConnectToResourceArg ASN.1 encoded value from octets
    //   object.

    vector<byte> encodedConnectToResourceArg = octets->GetArray();

    ////////////////////////////////////////////////////////////////////////////

    //  [7] Free all memory allocated on the heap.

    //  [7-1] Delete ConnectToResourceArg object (and therefore all the
    //  parameter objects that have been previously set).

    delete connectToResourceArg;

    //  [7-2] Delete Octets object created by the call to Encode.

    delete octets;

    ////////////////////////////////////////////////////////////////////////////

    //  [8] Return (by value) ConnectToResourceArg ASN.1 encoded value.

    return encodedConnectToResourceArg;
}
