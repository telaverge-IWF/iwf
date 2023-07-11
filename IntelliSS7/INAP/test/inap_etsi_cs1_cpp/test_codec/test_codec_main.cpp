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
//  ID: $Id: test_codec_main.cpp,v 9.1 2005/03/23 12:51:47 cvsadmin Exp $
//
///////////////////////////////////////////////////////////////////////////////

//
//  INAP ETSI CS1 ASN.1 codec example.
//
//  This example shows how to build (create, insert data and encode) and how
//  to interpret (decode and retrieve data) for the INAP ConnectArg operation
//  argument.
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
//  How to Build an INAP Connect operation argument (ConnectArg):
//
//  o   Create ConnectArg object.
//
//  o   Insert data step by step in the created ConnectArg object (i.e. populate
//      various parameters of the Connect operation argument).
//  
//  o   Encode the ConnectArg object to produce a ConnectArg encoded value.
//

vector<byte> 
BuildOperationConnectArg()
{
    //  [1] Create ConnectArg object.

    ConnectArg* connectArg = new ConnectArg();

    ////////////////////////////////////////////////////////////////////////////

    //  Memory management note: all the following parameter objects that are
    //  used to populate the ConnectArg object must be created in the heap (i.e.
    //  using operator new) and not in the stack. They are automatically deleted
    //  when the connectArg object is deleted. Only the ConnectArg object itself
    //  can be created in the stack. 

    ////////////////////////////////////////////////////////////////////////////

    //  [2] Populate mandatory parameter "destinationRoutingAddress".

    //  [2-1] Create DestinationRoutingAddress object.

    DestinationRoutingAddress* 
        destinationRoutingAddress =
            new DestinationRoutingAddress();
    
    //  INAP API Note: a DestinationRoutingAddress object contains a list of 
    //  CalledPartyNumber objects.

    //  [2-1-1] Create CalledPartyNumber object.

    byte fixedArray1[] = { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16 };

    CalledPartyNumber*
        calledPartyNumber =
            new CalledPartyNumber(FixedByteArrayToVector(fixedArray1));

    //  [2-1-2] Add CalledPartyNumber object to DestinationRoutingAddress 
    //  object. 

    destinationRoutingAddress->AddElement(calledPartyNumber);

    //  [2-2] Set DestinationRoutingAddress object in ConnectArg object.

    connectArg->SetDestinationRoutingAddress(destinationRoutingAddress);

    ////////////////////////////////////////////////////////////////////////////

    //  [3] Populate optional parameter "alertingPattern".

    //  [3-1] Create an AlertingPattern object.

    byte fixedArray2[] = { 0x20, 0x21, 0x22 };

    AlertingPattern* 
        alertingPattern =
            new AlertingPattern(FixedByteArrayToVector(fixedArray2));

    //  [3-2] Set AlertingPattern object in ConnectArg object.

    connectArg->SetAlertingPattern(alertingPattern);

    ////////////////////////////////////////////////////////////////////////////

    //  [4] Populate optional parameter "correlationID".

    //  [4-1] Create CorrelationID object.

    byte fixedArray3[] = { 0x30, 0x31, 0x32, 0x33, 0x34 };

    CorrelationID*
        correlationID =
            new CorrelationID(FixedByteArrayToVector(fixedArray3));

    //  [4-2] Set CorrelationID object in ConnectArg object.

    connectArg->SetCorrelationID(correlationID);

    ////////////////////////////////////////////////////////////////////////////

    //  [5] Populate optional parameter "routeList".

    //  [5-1] Create RouteList object.

    RouteList* routeList = new RouteList();

    //  INAP API Note: a RouteList object contains a list of 
    //  RouteList::OCTETSTRING objects.

    //  [5-1-1] Create RouteList::OCTETSTRING object.

    byte fixedArray4[] = { 0x01, 0x02, 0x03 };

    RouteList::OCTETSTRING*
        routeListOCTETSTRING1 =
            new RouteList::OCTETSTRING(
                FixedByteArrayToVector(fixedArray4));

    //  [5-1-2] Create RouteList::OCTETSTRING object.

    byte fixedArray5[] = { 0x11, 0x22, 0x33, 0x44 };

    RouteList::OCTETSTRING*
        routeListOCTETSTRING2 =
            new RouteList::OCTETSTRING(
                FixedByteArrayToVector(fixedArray5));

    //  [5-1-3] Create RouteList::OCTETSTRING object.

    byte fixedArray6[] = { 0x10, 0x20, 0x30, 0x40, 0x50 };

    RouteList::OCTETSTRING*
        routeListOCTETSTRING3 =
            new RouteList::OCTETSTRING(
                FixedByteArrayToVector(fixedArray6));

    //  [5-1-4] Add RouteList::OCTETSTRING object to RouteList object.

    routeList->AddElement(routeListOCTETSTRING1);

    //  [5-1-5] Add RouteList::OCTETSTRING object to RouteList object.

    routeList->AddElement(routeListOCTETSTRING2);

    //  [5-1-6] Add RouteList::OCTETSTRING object to RouteList object.

    routeList->AddElement(routeListOCTETSTRING3);

    //  [5-2] Set RouteList object in ConnectArg object.

    connectArg->SetRouteList(routeList);

    ////////////////////////////////////////////////////////////////////////////

    //  [6] Populate optional parameter "callingPartyNumber".

    //  [6-1] Create CallingPartyNumber object.

    byte fixedArray7[] = { 0x07, 0x07, 0x08, 0x09, 0x09, 0x08, 0x04 };

    CallingPartyNumber*
        callingPartyNumber =
            new CallingPartyNumber(FixedByteArrayToVector(fixedArray7));

    //  [6-2] Set CallingPartyNumber object in ConnectArg object.

    connectArg->SetCallingPartyNumber(callingPartyNumber);

    ////////////////////////////////////////////////////////////////////////////

    //  [7] Encode ConnectArg object.

    Octets* octets = NULL;

    try
    {
        //  Can throw and AsnEncodeError execption. 

        octets = connectArg->Encode();
    }
    catch (AsnEncodeError& encodeError)
    {
        cout << endl << encodeError.GetDescription() << endl;

        //  More specific error processing should be added here.

        //  By default re-throw exception.

        throw encodeError;
    }

    cout << endl;
    cout << "Printing ConnectArg ASN.1 encoded value..." << endl;
    cout << *octets;
    cout << endl;

    ////////////////////////////////////////////////////////////////////////////

    //  [8] Retrieve ConnectArg ASN.1 encoded value from octets object.

    vector<byte> encodedConnectArg = octets->GetArray();

    ////////////////////////////////////////////////////////////////////////////

    //  [9] Free all memory allocated on the heap.

    //  [9-1] Delete ConnectArg object (and therefore all the parameter
    //  objects that have been previously set).

    delete connectArg;

    //  [9-2] Delete Octets object created by the call to Encode.

    delete octets;

    ////////////////////////////////////////////////////////////////////////////

    //  [10] Return (by value) ConnectArg ASN.1 encoded value.

    return encodedConnectArg;
}


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


///////////////////////////////////////////////////////////////////////////////
//
//  Entry point:
//
//  o   Initialize IntelliSS7.
//
//  o   Call BuildOperationConnectArg function.
//  
//  o   Call InterpretOperationConnectArg function.
//
//  o   Terminate IntelliSS7.
// 

int 
main(int argc, char* argv[])
{
    cout << endl << "Begin INAP ETSI CS1 ASN.1 codec example..." << endl;

    try
    {
        ///////////////////////////////////////////////////////////////////////

        //  [1] Call BuildOperationConnectArg function.

        vector<byte> encodedConnectArg =
            BuildOperationConnectArg();

        //  [2] Call InterpretOperationConnectArg function.

        InterpretOperationConnectArg(encodedConnectArg);

        ///////////////////////////////////////////////////////////////////////
    }
    catch (ITS_GenericException& exp)
    {
        cout << endl << exp.GetDescription() << endl;
    }

    cout << endl << "End of INAP ETSI CS1 ASN.1 codec example." << endl;
    

    // To stop here in console application.

    cout << endl << "Press Enter to quit...";

    char c = '\0';
    cin.get(c);

    return EXIT_SUCCESS;
}

