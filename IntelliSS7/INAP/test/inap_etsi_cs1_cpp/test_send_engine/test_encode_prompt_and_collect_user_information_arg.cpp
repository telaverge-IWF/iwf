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
//  ID: $Id: test_encode_prompt_and_collect_user_information_arg.cpp,v 9.1 2005/03/23 12:51:47 cvsadmin Exp $
//
///////////////////////////////////////////////////////////////////////////////

//
//  INAP ETSI CS1 ASN.1 codec example.
//
//  This example shows how to build (create, insert data and encode)
//  for the INAP PromptAndCollectUserInformation operation argument.
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
#include <inap_etsi_cs1_prompt_and_collect_user_information_arg.h>

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
//     // Call PromptAndCollectUserInformationArg function.
//     vector<byte> encodedPromptAndCollectUserInformationArg =
//        BuildOperationPromptAndCollectUserInformationArg();
//
///////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
//  How to Build an INAP Connect operation argument (PromptAndCollectUserInformationArg):
//
//  o   Create PromptAndCollectUserInformationArg object.
//
//  o   Insert data step by step in the created
//      PromptAndCollectUserInformationArg object
//      (i.e. populate various parameters of the
//      PromptAndCollectUserInformationArg operation argument).
//  
//  o   Encode the PromptAndCollectUserInformationArg object to produce a
//      PromptAndCollectUserInformationArg encoded value.
//

vector<byte> 
BuildOperationPromptAndCollectUserInformationArg()
{
    //  [1] Create PromptAndCollectUserInformationArg object.

    PromptAndCollectUserInformationArg* promptAndCollectUserInformationArg
        = new PromptAndCollectUserInformationArg();

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Memory management note: all the following parameter objects that are
    //  used to populate the ConnectArg object must be created in the heap (i.e.
    //  using operator new) and not in the stack. They are automatically deleted
    //  when the connectArg object is deleted. Only the ConnectToResourceArg
    //  object itself can be created in the stack. 

    ////////////////////////////////////////////////////////////////////////////

    //  [2] Populate mandatory parameter "collectedInfo".

    //  [2-1] Create CollectedInfo object.

    CollectedInfo* collectedInfo = new CollectedInfo();

    //  [2-1-1] Create CollectedDigits object.

    CollectedDigits* collectedDigits = new CollectedDigits();

    //  [2-1-1-1] Create MinimumNbOfDigits object.

    CollectedDigits::MinimumNbOfDigits minimumNbOfDigits(2); 

    //  [2-1-1-1-1] Populate MinimumNbOfDigits object.

    collectedDigits->SetMinimumNbOfDigits(minimumNbOfDigits);

    //  [2-1-1-2] Create MaximumNbOfDigits object.

    CollectedDigits::MaximumNbOfDigits maximumNbOfDigits(20); 

    //  [2-1-1-2-1] Populate MaximumNbOfDigits object.

    collectedDigits->SetMaximumNbOfDigits(maximumNbOfDigits);

    //  [2-1-1-3] Create ErrorTreatment object.

    CollectedDigits::ErrorTreatment
        errorTreatment(
            CollectedDigits::ErrorTreatment::ERROR_TREATMENT_REPEAT_PROMPT); 

    //  [2-1-1-3-1] Populate ErrorTreatment object.

    collectedDigits->SetErrorTreatment(errorTreatment);

    //  [2-1-1-4] Create InterruptableAnnId object.

    CollectedDigits::InterruptableAnnInd interruptableAnnInd(false);

    //  [2-1-1-4-1] Populate InterruptableAnnId object.

    collectedDigits->SetInterruptableAnnInd(interruptableAnnInd);

    //  [2-1-1-5] Create VoiceInformation object.

    CollectedDigits::VoiceInformation voiceInformation(true);

    //  [2-1-1-5-2] Populate VoiceInformation object.

    collectedDigits->SetVoiceInformation(voiceInformation);

    //  [2-1-1-6] Create VoiceBack object.

    CollectedDigits::VoiceBack voiceBack(true);

    //  [2-1-1-6-1] Populate VoiceBack object.

    collectedDigits->SetVoiceBack(voiceBack);

    collectedInfo->SetChoiceCollectedDigits(collectedDigits);

    promptAndCollectUserInformationArg->SetCollectedInfo(collectedInfo);

    //  [3] Populate mandatory parameter "disconnectFromIPForbidden".

    //  [3-1] Create DisconnectFromIPForbidden object.

    PromptAndCollectUserInformationArg::DisconnectFromIPForbidden*
        disconnectFromIPForbidden = new
           PromptAndCollectUserInformationArg::DisconnectFromIPForbidden(false);

    promptAndCollectUserInformationArg->SetDisconnectFromIPForbidden(
        disconnectFromIPForbidden);

    //  [4] Create InformationToSend object.

    InformationToSend* informationToSend = new InformationToSend();

    //  [4-1] Populate InformationToSend object.

    DisplayInformation* displayInformation =
        new DisplayInformation("Test String");

    informationToSend->SetChoiceDisplayInformation(displayInformation);

    promptAndCollectUserInformationArg->SetInformationToSend(informationToSend);

    //  [4] Create Extensions object.

    PromptAndCollectUserInformationArg::Extensions*
        extensions = new PromptAndCollectUserInformationArg::Extensions();

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

    promptAndCollectUserInformationArg->SetExtensions(extensions);

    ////////////////////////////////////////////////////////////////////////////

    //  [7] Encode PromptAndCollectUserInformationArg object.

    Octets* octets = NULL;

    try
    {
        //  Can throw and AsnEncodeError execption. 

        octets = promptAndCollectUserInformationArg->Encode();
    }
    catch (AsnEncodeError& encodeError)
    {
        cout << endl << encodeError.GetDescription() << endl;

        //  More specific error processing should be added here.

        //  By default re-throw exception.

        throw encodeError;
    }

    cout << endl;
    cout << "Printing PromptAndCollectUserInformationArg ASN.1 encoded" 
         << " value...\n";
    cout << *octets;
    cout << endl;

    ////////////////////////////////////////////////////////////////////////////

    //   [8] Retrieve PromptAndCollectUserInformationArg ASN.1 encoded value
    //   from octets object.

    vector<byte> encodedPromptAndCollectUserInformationArg = octets->GetArray();

    ////////////////////////////////////////////////////////////////////////////

    //  [9] Free all memory allocated on the heap.

    //  [9-1] Delete PromptAndCollectUserInformationArg object (and therefore
    //  all the parameter objects that have been previously set).

    delete promptAndCollectUserInformationArg;

    //  [9-2] Delete Octets object created by the call to Encode.

    delete octets;

    ////////////////////////////////////////////////////////////////////////////

    //  [10] Return (by value) EstablishTemporaryConnectionArg ASN.1 encoded
    //  value.

    return encodedPromptAndCollectUserInformationArg;
}
