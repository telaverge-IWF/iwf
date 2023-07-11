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
//  ID: $Id: test_decode_event_report_bcsm_arg.cpp,v 9.1 2005/03/23 12:51:47 cvsadmin Exp $
//
///////////////////////////////////////////////////////////////////////////////

//
//  INAP ETSI CS1 ASN.1 decode example.
//
//  This example shows how to interpret (decode and retrieve data) for the INAP
//  EventReportBCSM operation argument.
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

////////////////////////////////////////////////////////////////////////////////
//
//  How to interpret an (encoded) INAP Connect To Resource
//  (EventReportBCSMArg):
//
//  o   Decode a EventReportBCSMArg encoded value (i.e. create a
//      EventReportBCSMArg object from a EventReportBCSMArg encoded value).
//
//  o   Retrieve Data from a EventReportBCSMArg object.
//

void
InterpretOperationEventReportBCSMArg(const vector<byte>& encodedEventReportBCSMArg)
{
    //  [1] Create an Octets object from the EventReportBCSMArg ASN.1 encoded
    //  value.

    Octets* octets = new Octets(encodedEventReportBCSMArg);

    ////////////////////////////////////////////////////////////////////////////

    //  [2] Create EventReportBCSMArg object (used by the decode
    //  phase).

    EventReportBCSMArg*
        eventReportBCSMArg = new EventReportBCSMArg();

    ////////////////////////////////////////////////////////////////////////////

    //  [3] Decode the EventReportBCSMArg ASN.1 encoded value and
    //  therefore  populate previously created EventReportBCSMArg
    //  object.

    try
    {
        //  Can throw and AsnDecodeError exception.

        eventReportBCSMArg->Decode(*octets);
    }
    catch (AsnDecodeError& decodeError)
    {
        cout << endl << decodeError.GetDescription() << endl;

        // More specific error processing should be added here.

        // By default re-throw exeception.

        throw decodeError;
    }

    cout << endl;
    cout << "Printing decoded EventReportBCSMArg object...\n";
    cout << *eventReportBCSMArg;
    cout << endl;

#if 0
    ////////////////////////////////////////////////////////////////////////////

    //  [4] Retrieve mandatory parameter "resourceAddress".

    //  [4-1] Retrieve reference to ResourceAddress object.

    const ConnectToResourceArg::ResourceAddress& 
        resourceAddress = connectToResourceArg->GetResourceAddress();

    //  INAP API Note: a ResourceAddress object contains choice of 
    //  IPRoutingAddress or no object.

    if (resourceAddress.ChoiceIpRoutingAddress())
    {
        //  [4-2] Retrieve reference to ResourceAddress object.

        const IPRoutingAddress& ipRoutingAddress =
            resourceAddress.GetChoiceIpRoutingAddress();

        //  [4-3] Retrieve contents of CalledPartyNumber object.

        vector<byte> vector1 = ipRoutingAddress.GetArray();

        //  Do something with vector of bytes...

        //  [4-4] Print IPRoutingAddress object.

        cout << endl;
        cout << "Printing IPRoutingAddress object..." << endl;
        cout << ipRoutingAddress;
        cout << endl;
    }
    else if (resourceAddress.ChoiceNone())
    {
        //  [4-2] Retrieve reference to ResourceAddress object.

        const ConnectToResourceArg::ResourceAddress::None&
            none = resourceAddress.GetChoiceNone();

        //  [4-3] Print None object.

        cout << endl;
        cout << "Printing None object..." << endl;
        cout << none;
        cout << endl;
    }

    if (connectToResourceArg->OptionExtensions())
    {
        //  [5-1] Retrieve reference to Extensions object.

        const ConnectToResourceArg::Extensions& extensions =
            connectToResourceArg->GetExtensions();

        //  INAP API Note: a Extensions object contains a list of 
        //  ExtensionField objects.
    
        //  [5-2] Retrieve contents of Extensions object.
    
        for (int i = 0; i < extensions.Size(); i++)
        {
            //  [5-2-1] Retrieve reference to ExtensionField object.
    
            const ExtensionField& extensionField = extensions.ElementAt(i);
    
            //  [5-2-2] Retrieve contents of ExtensionField object.
    
            const ExtensionField::Type& type = extensionField.GetType();
    
            int value1 = type.GetValue();

            //  Do something with value1 ...

            //  [5-2-3] Print Type object.

            cout << endl;
            cout << "Printing Type object..." << endl;
            cout << type;
            cout << endl;

            const ExtensionField::Criticality&
                criticality = extensionField.GetCriticality();

            long value2 = criticality.GetValue();

            //  Do something with value2 ...

            //  [5-2-4] Print Criticality object.

            cout << endl;
            cout << "Printing Criticality object..." << endl;
            cout << criticality;
            cout << endl;

            //  Do something with vector of bytes...
    
            const ExtensionField::Value& value = extensionField.GetValue();
    
            //  [5-2-5] Print Value object.

            cout << endl;
            cout << "Printing Value object..." << endl;
            cout << value;
            cout << endl;
        }
    }

    ////////////////////////////////////////////////////////////////////////////

    //  [5] Retrieve optional parameter "serviceInteractionIndicators".

    if (connectToResourceArg->OptionServiceInteractionIndicators())
    {
        //  [6-1] Retrieve reference to ServiceInteractionIndicators object.

        const ServiceInteractionIndicators& serviceInteractionIndicators =
            connectToResourceArg->GetServiceInteractionIndicators();

        //  [6-2] Retrieve contents of ServiceInteractionIndicators object.

        vector<byte> vector1 = serviceInteractionIndicators.GetArray();

        // Do something with vector of bytes...

        //  [6-3] Print AlertingPattern object.

        cout << endl;
        cout << "Printing ServiceInteractionIndicators object..." << endl;
        cout << serviceInteractionIndicators;
        cout << endl;
    }

    ////////////////////////////////////////////////////////////////////////////
#endif
    //  [7] Free all memory allocated on the heap.

    //  [7-1] Delete Octets object.

    delete octets;

    //  [7-2] Delete EventReportBCSMArg object.

    delete eventReportBCSMArg;
}

