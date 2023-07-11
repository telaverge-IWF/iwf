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
//  ID: $Id: test_decode_connect_arg.cpp,v 9.1 2005/03/23 12:51:47 cvsadmin Exp $
//
///////////////////////////////////////////////////////////////////////////////

//
//  INAP ETSI CS1 ASN.1 decode example.
//
//  This example shows how to interpret (decode and retrieve data) for the INAP
//  ConnectArg operation argument.
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
#include <inap_etsi_cs1_connect_arg.h>

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
//  How to interpret an (encoded) INAP Connect operation argument (ConnectArg):
//
//  o   Decode a ConnectArg encoded value (i.e. create a ConnectArg object from
//      a ConnectArg encoded value).
//
//  o   Retrieve Data from a ConnectArg object.
//

void
InterpretOperationConnectArg(const vector<byte>& encodedConnectArg)
{
    //  [1] Create an Octets object from the ConnectArg ASN.1 encoded value.

    Octets* octets = new Octets(encodedConnectArg);

    ////////////////////////////////////////////////////////////////////////////

    //  [2] Create ConnectArg object (used by the decode phase).

    ConnectArg* connectArg = new ConnectArg();

    ////////////////////////////////////////////////////////////////////////////

    //  [3] Decode the ConnectArg ASN.1 encoded value and therefore populate 
    //  previously created ConnectArg object.

    try
    {
        //  Can throw and AsnDecodeError exception.

        connectArg->Decode(*octets);
    }
    catch (AsnDecodeError& decodeError)
    {
        cout << endl << decodeError.GetDescription() << endl;

        // More specific error processing should be added here.

        // By default re-throw exeception.

        throw decodeError;
    }

    cout << endl;
    cout << "Printing decoded ConnectArg object..." << endl;
    cout << *connectArg;
    cout << endl;

    ////////////////////////////////////////////////////////////////////////////

    //  [4] Retrieve mandatory parameter "destinationRoutingAddress".

    //  [4-1] Retrieve reference to DestinationRoutingAddress object.

    const DestinationRoutingAddress& 
        destinationRoutingAddress =
            connectArg->GetDestinationRoutingAddress();

    //  INAP API Note: a DestinationRoutingAddress object contains a list of 
    //  CalledPartyNumber objects.

    //  [4-2] Retrieve contents of DestinationRoutingAddress object.

    for (int i = 0; i < destinationRoutingAddress.Size(); i++)
    {
        //  [4-2-1] Retrieve reference to CalledPartyNumber object.

        const CalledPartyNumber&
            calledPartyNumber =
                destinationRoutingAddress.ElementAt(i);

        //  [4-2-2] Retrieve contents of CalledPartyNumber object.

        vector<byte> vector1 = calledPartyNumber.GetArray();

        //  Do something with vector of bytes...

        //  [4-2-3] Print CalledPartyNumber object.

        cout << endl;
        cout << "Printing CalledPartyNumber object..." << endl;
        cout << calledPartyNumber;
        cout << endl;
    }

    //  [4-3] Print DestinationRoutingAddress object.

    cout << endl;
    cout << "Printing DestinationRoutingAddress object..." << endl;
    cout << destinationRoutingAddress;
    cout << endl;

    ////////////////////////////////////////////////////////////////////////////

    //  [5] Retrieve optional parameter "alertingPattern".

    if (connectArg->OptionAlertingPattern())
    {
        //  [5-1] Retrieve reference to AlertingPattern object.

        const AlertingPattern&
            alertingPattern =
                connectArg->GetAlertingPattern();

        //  [5-2] Retrieve contents of AlertingPattern object.

        vector<byte> vector2 = alertingPattern.GetArray();

        // Do something with vector of bytes...

        //  [5-3] Print AlertingPattern object.

        cout << endl;
        cout << "Printing AlertingPattern object..." << endl;
        cout << alertingPattern;
        cout << endl;
    }

    ////////////////////////////////////////////////////////////////////////////

    //  [6] Retrieve optional parameter "correlationID".

    if (connectArg->OptionCorrelationID())
    {
        //  [6-1] Retrieve reference to CorrelationID object.

        const CorrelationID&
            correlationID = 
                connectArg->GetCorrelationID();

        //  [6-2] Retrieve contents of CorrelationID object.

        vector<byte> vector3 = correlationID.GetArray();

        // Do something with vector of bytes...

        //  [6-3] Print CorrelationID object.

        cout << endl;
        cout << "Printing CorrelationID object..." << endl;
        cout << correlationID;
        cout << endl;
    }

    ////////////////////////////////////////////////////////////////////////////

    //  [7] Retrieve optional parameter "routeList".

    if (connectArg->OptionRouteList())
    {
        //  [7-1] Retrieve reference to RouteList object.

        const RouteList& 
            routeList =
                connectArg->GetRouteList();

        //  INAP API Note: a RouteList object contains a list of 
        //  RouteList::OCTETSTRING objects.

        //  [7-2] Retrieve contents of RouteList object.

        for (int i = 0; i < routeList.Size(); i++)
        {
            //  [7-2-1] Retrieve reference to RouteList::OCTETSTRING object.

            const RouteList::OCTETSTRING&
                routeListOCTETSTRING =
                    routeList.ElementAt(i);

            //  [7-2-2] Retrieve contents of RouteList::OCTETSTRING object.

            vector<byte> vector4 = routeListOCTETSTRING.GetArray();

            //  Do something with vector of bytes...

            //  [7-2-3] Print RouteList::OCTETSTRING object.

            cout << endl;
            cout << "Printing RouteList::OCTETSTRING object..." << endl;
            cout << routeListOCTETSTRING;
            cout << endl;
        }

        //  [7-3] Print RouteList object.

        cout << endl;
        cout << "Printing RouteList object..." << endl;
        cout << routeList;
        cout << endl;
    }

    ////////////////////////////////////////////////////////////////////////////

    //  [8] Retrieve optional parameter "callingPartyNumber".

    if (connectArg->OptionCallingPartyNumber())
    {
        //  [8-1] Retrieve reference to CallingPartyNumber object.

        const CallingPartyNumber&
            callingPartyNumber = 
                connectArg->GetCallingPartyNumber();

        //  [8-2] Retrieve contents of CallingPartyNumber object.

        vector<byte> vector5 = callingPartyNumber.GetArray();

        // Do something with vector of bytes...

        //  [8-3] Print CallingPartyNumber object.

        cout << endl;
        cout << "Printing CallingPartyNumber object..." << endl;
        cout << callingPartyNumber;
        cout << endl;
    }

    ////////////////////////////////////////////////////////////////////////////

    //  [9] Free all memory allocated on the heap.

    //  [9-1] Delete Octets object.

    delete octets;

    //  [9-2] Delete ConnectArg object.

    delete connectArg;
}

