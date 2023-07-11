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
//  ID: $Id: test_encode_event_report_bcsm_arg.cpp,v 9.1 2005/03/23 12:51:47 cvsadmin Exp $
//
///////////////////////////////////////////////////////////////////////////////

//
//  INAP ETSI CS1 ASN.1 codec example.
//
//  This example shows how to build (create, insert data and encode)
//  for the INAP EventReportBCSM operation argument.
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
#include <inap_etsi_cs1_event_report_bcsm_arg.h>

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
//     // Call BuildEventReportBCSMArg function.
//     vector<byte> encodedEventReportBCSMArg =
//        BuildOperationEventReportBCSMArg();
//
///////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
//  How to Build an INAP EventReportBCSM operation argument
//  (EventReportBCSMArg):
//
//  o   Create EventReportBCSM object.
//
//  o   Insert data step by step in the created EventReportBCSM object
//      (i.e. populate various parameters of the EventReportBCSM
//      operation argument).
//  
//  o   Encode the EventReportBCSMArg object to produce a
//      EventReportBCSM encoded value.
//

vector<byte> 
BuildOperationEventReportBCSMArg()
{
    //  [1] Create EventReportBCSMArg object.

    EventReportBCSMArg*
        eventReportBCSMArg = new EventReportBCSMArg();

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Memory management note: all the following parameter objects that are
    //  used to populate the EventReportBCSM object must be created in
    //  the heap (i.e. using operator new) and not in the stack. They are
    //  automatically deleted when the connectArg object is deleted. Only the
    //  SCIBillingChargingCharacteristics object itself can be created in the
    //  stack. 

    ////////////////////////////////////////////////////////////////////////////

    //  [2] Populate mandatory parameter "EventTypeBCSM".

    //  [2-1] Create EventTypeBCSM object.

    EventTypeBCSM* eventTypeBCSM
        = new EventTypeBCSM(EventTypeBCSM::EVENT_TYPE_BCSM_COLLECTED_INFO);

    eventReportBCSMArg->SetEventTypeBCSM(eventTypeBCSM);

    //  [3] Populate mandatory parameter "EventSpecificInformation".

    //  [3-1] Create EventSpecificInformation object.

    EventSpecificInformationBCSM* eventSpecificInformationBCSM
        = new EventSpecificInformationBCSM();

    //  [3-2] Populate parameter "CollectedInfoSpecificInfo".

    //  [3-2-1] Create CollectedInfoSpecificInfo object.

    byte fixedArray1[] = { 0x11, 0x12, 0x14, 0x17, 0x18 };

    CalledPartyNumber* calledPartyNumber1
        = new CalledPartyNumber(FixedByteArrayToVector(fixedArray1));

    EventSpecificInformationBCSM::CollectedInfoSpecificInfo*
        collectedInfoSpecificInfo
            = new EventSpecificInformationBCSM::CollectedInfoSpecificInfo();

    collectedInfoSpecificInfo->SetCalledPartyNumber(calledPartyNumber1);

    eventSpecificInformationBCSM->SetChoiceCollectedInfoSpecificInfo(
        collectedInfoSpecificInfo);

    //  [3-3] Populate parameter "AnalyzedInfoSpecificInfo".

    //  [3-3-1] Create AnalyzedInfoSpecificInfo object.

    byte fixedArray2[] = { 0x10, 0x13, 0x11, 0x15, 0x19 };

    CalledPartyNumber* calledPartyNumber2
        = new CalledPartyNumber(FixedByteArrayToVector(fixedArray2));

    EventSpecificInformationBCSM::AnalyzedInfoSpecificInfo*
        analyzedInfoSpecificInfo
            = new EventSpecificInformationBCSM::AnalyzedInfoSpecificInfo();

    analyzedInfoSpecificInfo->SetCalledPartyNumber(calledPartyNumber2);

    eventSpecificInformationBCSM->SetChoiceAnalyzedInfoSpecificInfo(
        analyzedInfoSpecificInfo);

    eventReportBCSMArg->SetEventSpecificInformationBCSM(
        eventSpecificInformationBCSM);

    //  [4] Create optional parameter "LegID".

    LegID* legID = new LegID();

    //  [4-1] Create LegType object.

    byte fixedArray3[] = {0x1};

    LegType legType(FixedByteArrayToVector(fixedArray3));

    //  [4-2] Populate LegID object.

    legID->SetChoiceSendingSideID(legType);

    eventReportBCSMArg->SetLegID(legID);

    //  [5] Populate optional parameter "extensions".
    //  [5-1] Create Extensions object.

    EventReportBCSMArg::Extensions*
        extensions = new EventReportBCSMArg::Extensions();

    //  [5-2-1] Populate parameter "extensionField1".

    //  [5-2-2] Create ExtensionField object.

    ExtensionField* extensionField1 = new ExtensionField();

    //  [5-2-3] Add ExtensionField::Type object to ExtensionField object.

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

    eventReportBCSMArg->SetExtensions(extensions);

    ////////////////////////////////////////////////////////////////////////////

    //  [6] Encode EventReportBCSMArg object.

    Octets* octets = NULL;

    try
    {
        //  Can throw and AsnEncodeError execption. 

        octets = eventReportBCSMArg->Encode();
    }
    catch (AsnEncodeError& encodeError)
    {
        cout << endl << encodeError.GetDescription() << endl;

        //  More specific error processing should be added here.

        //  By default re-throw exception.

        throw encodeError;
    }

    cout << endl;
    cout << "Printing EventReportBCSMArg ASN.1 encoded value...\n";
    cout << *octets;
    cout << endl;

    ////////////////////////////////////////////////////////////////////////////

    //  [7] Retrieve EventReportBCSMArg ASN.1 encoded value from
    //   octets object.

    vector<byte> encodedEventReportBCSMArg = octets->GetArray();

    ////////////////////////////////////////////////////////////////////////////

    //  [8] Free all memory allocated on the heap.

    //  [8-1] Delete EventReportBCSMArg object (and therefore all the
    //  parameter objects that have been previously set).

    delete eventReportBCSMArg;

    //  [8-2] Delete Octets object created by the call to Encode.

    delete octets;

    ////////////////////////////////////////////////////////////////////////////

    //  [9] Return (by value) EstablishTemporaryConnectionArg ASN.1 encoded
    //  value.

    return encodedEventReportBCSMArg;
}
