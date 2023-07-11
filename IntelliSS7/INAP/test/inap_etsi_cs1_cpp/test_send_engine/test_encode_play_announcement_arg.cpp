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
//  ID: $Id: test_encode_play_announcement_arg.cpp,v 9.1 2005/03/23 12:51:47 cvsadmin Exp $
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
#include <inap_etsi_cs1_play_announcement_arg.h>

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
//     // Call BuildPlayAnnouncementArg function.
//     vector<byte> encodedPlayAnnouncementArg =
//        BuildOperationPlayAnnouncementArg();
//
///////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
//  How to Build an INAP Connect operation argument (PlayAnnouncementArg):
//
//  o   Create PlayAnnouncementArg object.
//
//  o   Insert data step by step in the created PlayAnnouncementArg object
//      (i.e. populate various parameters of the PlayAnnouncementArg operation
//      argument).
//  
//  o   Encode the PlayAnnouncementArg object to produce a
//      PlayAnnouncementArg encoded value.
//

vector<byte> 
BuildOperationPlayAnnouncementArg()
{
    //  [1] Create PlayAnnouncementArg object.

    PlayAnnouncementArg*
        playAnnouncementArg = new PlayAnnouncementArg();

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Memory management note: all the following parameter objects that are
    //  used to populate the ConnectArg object must be created in the heap (i.e.
    //  using operator new) and not in the stack. They are automatically deleted
    //  when the connectArg object is deleted. Only the ConnectToResourceArg
    //  object itself can be created in the stack. 

    ////////////////////////////////////////////////////////////////////////////

    //  [2] Populate mandatory parameter "informationToSend".

    //  [2-1] Create InfomationToSend object.

    InformationToSend* informationToSend
        = new InformationToSend();

    //  [2-1-1] Create DisplayInformation object.

    DisplayInformation* displayInformation
        = new DisplayInformation("Test String");

    informationToSend->SetChoiceDisplayInformation(displayInformation);

    playAnnouncementArg->SetInformationToSend(informationToSend);

    //  [3] Populate mandatory parameter "disconnectFromIPForbidden".

    //  [3-1] Create DisconnectFromIPForbidden object.

    PlayAnnouncementArg::DisconnectFromIPForbidden*
        disconnectFromIPForbidden
        = new PlayAnnouncementArg::DisconnectFromIPForbidden(false);

    playAnnouncementArg->SetDisconnectFromIPForbidden(
        disconnectFromIPForbidden);

    //  [4] Populate mandatory parameter "requestAnnouncementComplete".

    //  [4-1] Create RequestAnnouncementComplete object.

    PlayAnnouncementArg::RequestAnnouncementComplete*
        requestAnnouncementComplete 
        = new PlayAnnouncementArg::RequestAnnouncementComplete(false);

    playAnnouncementArg->SetRequestAnnouncementComplete(
        requestAnnouncementComplete);

    //  [5] Populate optional parameter "extensions".
    //  [5-1] Create Extensions object.

    PlayAnnouncementArg::Extensions*
        extensions = new PlayAnnouncementArg::Extensions();

    //  [5-2-1] Populate parameter "extensionField1".

    //  [5-2-2] Create ExtensionField object.

    ExtensionField* extensionField1 = new ExtensionField();

    //  [5-1-1] Add ExtensionField::Type object to ExtensionField object.

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

    //  [5-3-1] Populate parameter "extensionField2".

    //  [5-3-2] Create ExtensionField object.

    ExtensionField* extensionField2 = new ExtensionField();

    //  [5-3-3] Add ExtensionField::Type object to ExtensionField object.

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

    //  [5-4] Set Extensions object in EstablishTemporaryConnectionArg object.

    playAnnouncementArg->SetExtensions(extensions);

    ////////////////////////////////////////////////////////////////////////////

    //  [7] Encode PlayAnnouncementArg object.

    Octets* octets = NULL;

    try
    {
        //  Can throw and AsnEncodeError execption. 

        octets = playAnnouncementArg->Encode();
    }
    catch (AsnEncodeError& encodeError)
    {
        cout << endl << encodeError.GetDescription() << endl;

        //  More specific error processing should be added here.

        //  By default re-throw exception.

        throw encodeError;
    }

    cout << endl;
    cout << "Printing PlayAnnouncementArg ASN.1 encoded value...\n";
    cout << *octets;
    cout << endl;

    ////////////////////////////////////////////////////////////////////////////

    //   [8] Retrieve PlayAnnouncementArg ASN.1 encoded value from
    //   octets object.

    vector<byte> encodedPlayAnnouncementArg = octets->GetArray();

    ////////////////////////////////////////////////////////////////////////////

    //  [9] Free all memory allocated on the heap.

    //  [9-1] Delete PlayAnnouncementArg object (and therefore all the
    //  parameter objects that have been previously set).

    delete playAnnouncementArg;

    //  [9-2] Delete Octets object created by the call to Encode.

    delete octets;

    ////////////////////////////////////////////////////////////////////////////

    //  [10] Return (by value) EstablishTemporaryConnectionArg ASN.1 encoded
    //  value.

    return encodedPlayAnnouncementArg;
}
