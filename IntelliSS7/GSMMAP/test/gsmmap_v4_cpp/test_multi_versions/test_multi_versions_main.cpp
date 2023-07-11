////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.     //
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
// CONTRACT: INTERNAL                                                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
//  ID: $Id: test_multi_versions_main.cpp,v 9.1 2005/03/23 12:51:35 cvsadmin Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//  MAP Multi-Version ASN.1 codec example.
//
//  This example shows how to use in a same source file (and therefore 
//  executable) two different versions of MAP codecs (MAP V4 and MAP V1). It is 
//  partially based on the test_codec example. 
// 

//
//  C++ related note:
//  
//  The code relies on STL (C++ Standard Template Library). A basic knowledge
//  of STL is assumed (mainly classes std::vector and std::list). Likewise, a 
//  basic knowledge of C++ standard classes (e.g. std::string, std::ostream...) 
//  is also assumed. 
// 


#include <iostream>

#include <its++.h>
#include <its_ss7_stubs.h>

#include <Asn.h>
#include <AsnException.h>

#include <map_cpp.h>
#include <map_v4_insert_subscriber_data_arg.h>
#include <map_v1_insert_subscriber_data_arg.h>


#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined (ITS_STD_NAMESPACE)

#if defined(ITS_NAMESPACE)
using namespace its;
using namespace map_common;         //
using namespace map_v4;             // C++ compiler tells which symbols are
using namespace map_v1;             // ambiguous and must be prefixed.
#endif // defined(ITS_NAMESPACE)    //


////////////////////////////////////////////////////////////////////////////////
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

//
//  Macro to convert fixed arrays (of booleans) to vectors.
//
#define FixedBooleanArrayToVector(array)   \
    (vector<bool>(array, array + FixedArraySize(array)))


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              MAP V4                                        //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
//  How to Build a MAP V4 InsertSubscriberData operation argument 
//  (InsertSubscriberDataArg):
//
//  o   Create InsertSubscriberDataArg object.
//
//  o   Insert data step by step in the created InsertSubscriberDataArg object 
//      (i.e. populate various parameters of the InsertSubscriberData 
//      operation argument).
//  
//  o   Encode the InsertSubscriberDataArg object to produce an 
//      InsertSubscriberDataArg encoded value.
//

vector<byte> 
MAP_V4_BuildOperationInsertSubscriberDataArg()
{
    //  [1] Create InsertSubscriberDataArg object.

    map_v4::InsertSubscriberDataArg* insertSubscriberDataArg = 
        new map_v4::InsertSubscriberDataArg();

    ////////////////////////////////////////////////////////////////////////////

    //  Memory management note: all the following parameter objects that are
    //  used to populate the InsertSubscriberDataArg object must be created in 
	//  the heap (i.e. using operator new) and not in the stack. They are 
	//  automatically deleted when the insertSubscriberDataArg object is 
    //  deleted. Only the InsertSubscriberDataArg object itself can be created 
    //  in the stack. 

    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////

    //  [2] Populate optional parameter "imsi".

    //  [2-1] Create IMSI object.

    byte fixedArray1[] = { 0x01U, 0x02U, 0x03U, 0x04U }; 

    map_v4::IMSI* imsi = new map_v4::IMSI(FixedByteArrayToVector(fixedArray1));

    //  [2-2] Set IMSI object in InsertSubscriberDataArg object.

    insertSubscriberDataArg->SetImsi(imsi);


    ////////////////////////////////////////////////////////////////////////////

    //  [3] Populate optional parameter "msisdn".

    //  [3-1] Create an ISDN_AddressString object.

    byte fixedArray2[] = { 0x11U, 0x22U, 0x33U, 0x44U, 0x55U };

    map_v4::ISDN_AddressString* iSDN_AddressString = 
        new map_v4::ISDN_AddressString(FixedByteArrayToVector(fixedArray2));

    //  [3-2] Set ISDN_AddressString object in InsertSubscriberDataArg object.

    insertSubscriberDataArg->SetMsisdn(iSDN_AddressString);


    ////////////////////////////////////////////////////////////////////////////

    //  [4] Encode InsertSubscriberDataArg object.

    Octets* octets = NULL;

    try
    {
        //  Can throw and AsnEncodeError execption. 

        octets = insertSubscriberDataArg->Encode();
    }
    catch (AsnEncodeError& encodeError)
    {
        cout << endl << encodeError.GetDescription() << endl;

        //  More specific error processing should be added here.

        //  By default re-throw exception.

        throw encodeError;
    }

    cout << endl;
    cout << "Printing InsertSubscriberDataArg ASN.1 encoded value..." << endl;
    cout << *octets;
    cout << endl;

    ////////////////////////////////////////////////////////////////////////////

    //  [5] Retrieve InsertSubscriberDataArg ASN.1 encoded value from octets 
    //  object.

    vector<byte> encodedInsertSubscriberDataArg = octets->GetArray();

    ////////////////////////////////////////////////////////////////////////////

    //  [6] Free all memory allocated on the heap.

    //  [6-1] Delete InsertSubscriberDataArg object (and therefore all the 
    //  parameter objects that have been previously set).

    delete insertSubscriberDataArg;

    //  [6-2] Delete Octets object created by the call to Encode.

    delete octets;

    ////////////////////////////////////////////////////////////////////////////

    //  [7] Return (by value) InsertSubscriberDataArg ASN.1 encoded value.

    return encodedInsertSubscriberDataArg;
}


////////////////////////////////////////////////////////////////////////////////
//
//  How to interpret an (encoded) MAP V4 Insert Subscriber Data operation 
//  argument (InsertSubscriberDataArg):
//
//  o   Decode an InsertSubscriberDataArg encoded value (i.e. create an 
//      InsertSubscriberDataArg object from an InsertSubscriberDataArg encoded 
//      value).
//
//  o   Retrieve Data from an InsertSubscriberDataArg object.
//

void
MAP_V4_InterpretOperationInsertSubscriberDataArg(
                            const vector<byte>& encodedInsertSubscriberDataArg)
{
    //  [1] Create an Octets object from the InsertSubscriberDataArg ASN.1 
    //  encoded value.

    Octets* octets = new Octets(encodedInsertSubscriberDataArg);

    ////////////////////////////////////////////////////////////////////////////

    //  [2] Create InsertSubscriberDataArg object (used by the decode phase).

    map_v4::InsertSubscriberDataArg* 
        insertSubscriberDataArg = new 
            map_v4::InsertSubscriberDataArg();

    ////////////////////////////////////////////////////////////////////////////

    //  [3] Decode the InsertSubscriberDataArg ASN.1 encoded value and therefore
    //  populate previously created InsertSubscriberDataArg object.

    try
    {
        //  Can throw and AsnDecodeError exception.

        insertSubscriberDataArg->Decode(*octets);
    }
    catch (AsnDecodeError& decodeError)
    {
        cout << endl << decodeError.GetDescription() << endl;

        // More specific error processing should be added here.

        // By default re-throw exeception.

        throw decodeError;
    }

    cout << endl;
    cout << "Printing decoded InsertSubscriberDataArg object..." << endl;
    cout << *insertSubscriberDataArg;
    cout << endl;

    ////////////////////////////////////////////////////////////////////////////

    //  [4] Retrieve optional parameter "imsi".

    if (insertSubscriberDataArg->OptionImsi())
    {
        //  [4-1] Retrieve reference to IMSI object.

        const map_v4::IMSI& imsi = insertSubscriberDataArg->GetImsi();
        
		//  [4-2] Retrieve contents of IMSI object.
        
		vector<byte> vector1 = imsi.GetArray();

        //  Do something with vector of bytes...
        
		//  [4-3] Print IMSI object.
        
		cout << endl;
        cout << "Printing IMSI object..." << endl;
        cout << imsi;
        cout << endl;
    }

    ////////////////////////////////////////////////////////////////////////////

    //  [5] Retrieve optional parameter "msisdn".

    if (insertSubscriberDataArg->OptionMsisdn())
    {
        //  [5-1] Retrieve reference to  ISDN_AddressString object.

        const map_v4::ISDN_AddressString& 
            iSDN_AddressString = 
                insertSubscriberDataArg->GetMsisdn();
        
		//  [5-2] Retrieve contents of ISDN_AddressString object.
        
		vector<byte> vector2 = iSDN_AddressString.GetArray();

        //  Do something with vector of bytes...
        
		//  [5-3] Print ISDN_AddressString object.
        
		cout << endl;
        cout << "Printing ISDN_AddressString object..." << endl;
        cout << iSDN_AddressString;
        cout << endl;
    }


    ////////////////////////////////////////////////////////////////////////////

    //  [6] Free all memory allocated on the heap.

    //  [6-1] Delete Octets object.

    delete octets;

    //  [6-2] Delete InsertSubscriberDataArg object.

    delete insertSubscriberDataArg;
}




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              MAP V1                                        //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
//  How to Build a MAP V1 InsertSubscriberData operation argument 
//  (InsertSubscriberDataArg):
//
//  o   Create InsertSubscriberDataArg object.
//
//  o   Insert data step by step in the created InsertSubscriberDataArg object 
//      (i.e. populate various parameters of the InsertSubscriberData 
//      operation argument).
//  
//  o   Encode the InsertSubscriberDataArg object to produce an 
//      InsertSubscriberDataArg encoded value.
//

vector<byte> 
MAP_V1_BuildOperationInsertSubscriberDataArg()
{
    //  [1] Create InsertSubscriberDataArg object.

    map_v1::InsertSubscriberDataArg* insertSubscriberDataArg = 
        new map_v1::InsertSubscriberDataArg();

    ////////////////////////////////////////////////////////////////////////////

    //  Memory management note: all the following parameter objects that are
    //  used to populate the InsertSubscriberDataArg object must be created in 
	//  the heap (i.e. using operator new) and not in the stack. They are 
	//  automatically deleted when the insertSubscriberDataArg object is 
    //  deleted. Only the InsertSubscriberDataArg object itself can be created 
    //  in the stack. 

    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////

    //  [2] Populate optional parameter "imsi".

    //  [2-1] Create IMSI object.

    byte fixedArray1[] = { 0x01U, 0x02U, 0x03U, 0x04U }; 

    map_v1::IMSI* imsi = new map_v1::IMSI(FixedByteArrayToVector(fixedArray1));

    //  [2-2] Set IMSI object in InsertSubscriberDataArg object.

    insertSubscriberDataArg->SetImsi(imsi);


    ////////////////////////////////////////////////////////////////////////////

    //  [3] Populate optional parameter "msisdn".

    //  [3-1] Create an ISDN_AddressString object.

    byte fixedArray2[] = { 0x11U, 0x22U, 0x33U, 0x44U, 0x55U };

    map_v1::IsdnAddressString* isdnAddressString = 
        new map_v1::IsdnAddressString(FixedByteArrayToVector(fixedArray2));

    //  [3-2] Set ISDN_AddressString object in InsertSubscriberDataArg object.

    insertSubscriberDataArg->SetMsIsdn(isdnAddressString);


    ////////////////////////////////////////////////////////////////////////////

    //  [4] Encode InsertSubscriberDataArg object.

    Octets* octets = NULL;

    try
    {
        //  Can throw and AsnEncodeError execption. 

        octets = insertSubscriberDataArg->Encode();
    }
    catch (AsnEncodeError& encodeError)
    {
        cout << endl << encodeError.GetDescription() << endl;

        //  More specific error processing should be added here.

        //  By default re-throw exception.

        throw encodeError;
    }

    cout << endl;
    cout << "Printing InsertSubscriberDataArg ASN.1 encoded value..." << endl;
    cout << *octets;
    cout << endl;

    ////////////////////////////////////////////////////////////////////////////

    //  [5] Retrieve InsertSubscriberDataArg ASN.1 encoded value from octets 
    //  object.

    vector<byte> encodedInsertSubscriberDataArg = octets->GetArray();

    ////////////////////////////////////////////////////////////////////////////

    //  [6] Free all memory allocated on the heap.

    //  [6-1] Delete InsertSubscriberDataArg object (and therefore all the 
    //  parameter objects that have been previously set).

    delete insertSubscriberDataArg;

    //  [6-2] Delete Octets object created by the call to Encode.

    delete octets;

    ////////////////////////////////////////////////////////////////////////////

    //  [7] Return (by value) InsertSubscriberDataArg ASN.1 encoded value.

    return encodedInsertSubscriberDataArg;
}


////////////////////////////////////////////////////////////////////////////////
//
//  How to interpret an (encoded) MAP V1 Insert Subscriber Data operation 
//  argument (InsertSubscriberDataArg):
//
//  o   Decode an InsertSubscriberDataArg encoded value (i.e. create an 
//      InsertSubscriberDataArg object from an InsertSubscriberDataArg encoded 
//      value).
//
//  o   Retrieve Data from an InsertSubscriberDataArg object.
//

void
MAP_V1_InterpretOperationInsertSubscriberDataArg(
                            const vector<byte>& encodedInsertSubscriberDataArg)
{
    //  [1] Create an Octets object from the InsertSubscriberDataArg ASN.1 
    //  encoded value.

    Octets* octets = new Octets(encodedInsertSubscriberDataArg);

    ////////////////////////////////////////////////////////////////////////////

    //  [2] Create InsertSubscriberDataArg object (used by the decode phase).

    map_v1::InsertSubscriberDataArg* 
        insertSubscriberDataArg = new 
            map_v1::InsertSubscriberDataArg();

    ////////////////////////////////////////////////////////////////////////////

    //  [3] Decode the InsertSubscriberDataArg ASN.1 encoded value and therefore
    //  populate previously created InsertSubscriberDataArg object.

    try
    {
        //  Can throw and AsnDecodeError exception.

        insertSubscriberDataArg->Decode(*octets);
    }
    catch (AsnDecodeError& decodeError)
    {
        cout << endl << decodeError.GetDescription() << endl;

        // More specific error processing should be added here.

        // By default re-throw exeception.

        throw decodeError;
    }

    cout << endl;
    cout << "Printing decoded InsertSubscriberDataArg object..." << endl;
    cout << *insertSubscriberDataArg;
    cout << endl;

    ////////////////////////////////////////////////////////////////////////////

    //  [4] Retrieve optional parameter "imsi".

    if (insertSubscriberDataArg->OptionImsi())
    {
        //  [4-1] Retrieve reference to IMSI object.

        const map_v1::IMSI& imsi = insertSubscriberDataArg->GetImsi();
        
		//  [4-2] Retrieve contents of IMSI object.
        
		vector<byte> vector1 = imsi.GetArray();

        //  Do something with vector of bytes...
        
		//  [4-3] Print IMSI object.
        
		cout << endl;
        cout << "Printing IMSI object..." << endl;
        cout << imsi;
        cout << endl;
    }

    ////////////////////////////////////////////////////////////////////////////

    //  [5] Retrieve optional parameter "msisdn".

    if (insertSubscriberDataArg->OptionMsIsdn())
    {
        //  [5-1] Retrieve reference to  ISDN_AddressString object.

        const map_v1::IsdnAddressString& 
            isdnAddressString = 
                insertSubscriberDataArg->GetMsIsdn();
        
		//  [5-2] Retrieve contents of ISDN_AddressString object.
        
		vector<byte> vector2 = isdnAddressString.GetArray();

        //  Do something with vector of bytes...
        
		//  [5-3] Print ISDN_AddressString object.
        
		cout << endl;
        cout << "Printing IsdnAddressString object..." << endl;
        cout << isdnAddressString;
        cout << endl;
    }


    ////////////////////////////////////////////////////////////////////////////

    //  [6] Free all memory allocated on the heap.

    //  [6-1] Delete Octets object.

    delete octets;

    //  [6-2] Delete InsertSubscriberDataArg object.

    delete insertSubscriberDataArg;
}





////////////////////////////////////////////////////////////////////////////////
//
//  Entry point:
//
//  o   Initialize IntelliSS7.
//
//  o   Call MAP_V4_BuildOperationInsertSubscriberDataArg function.
//  
//  o   Call MAP_V4_InterpretOperationInsertSubscriberDataArg function.
//
//  o   Call MAP_V1_BuildOperationInsertSubscriberDataArg function.
//  
//  o   Call MAP_V1_InterpretOperationInsertSubscriberDataArg function.
//  
//  o   Terminate IntelliSS7.
// 

int main(int argc, char* argv[])
{
    cout << endl << "Begin MAP Multi-Versions ASN.1 codec example..." << endl;

    try
    {
        // IntelliSS7 initialization (including licensing).

        int res = ITS_GlobalStart(0);

        if (res != ITS_SUCCESS)
        {
            throw ITS_Error(res, __FILE__, __LINE__);
        }

        ////////////////////////////////////////////////////////////////////////

        //  [1] Call MAP_V4_BuildOperationInsertSubscriberDataArg function.

        vector<byte> mapV4_encodedInsertSubscriberDataArg =
            MAP_V4_BuildOperationInsertSubscriberDataArg();

        //  [2] Call MAP_V4_InterpretOperationInsertSubscriberDataArg function.

        MAP_V4_InterpretOperationInsertSubscriberDataArg(
            mapV4_encodedInsertSubscriberDataArg);

        ////////////////////////////////////////////////////////////////////////

        //  [1] Call MAP_V1_BuildOperationInsertSubscriberDataArg function.

        vector<byte> mapV1_encodedInsertSubscriberDataArg =
            MAP_V1_BuildOperationInsertSubscriberDataArg();

        //  [2] Call MAP_V1_InterpretOperationInsertSubscriberDataArg function.

        MAP_V1_InterpretOperationInsertSubscriberDataArg(
            mapV1_encodedInsertSubscriberDataArg);

        ////////////////////////////////////////////////////////////////////////


        // IntelliSS7 termination.

        ITS_GlobalStop();
    }
    catch (ITS_GenericException& exp)
    {
        cout << endl << exp.GetDescription() << endl;

        ITS_GlobalStop();
    }

    cout << endl << "End of MAP Multi-Versions ASN.1 codec example." << endl;
    

    // To stop here in console application.

    cout << endl << "Press Enter to quit...";

    char c = '\0';
    cin.get(c);

    return EXIT_SUCCESS;
}

