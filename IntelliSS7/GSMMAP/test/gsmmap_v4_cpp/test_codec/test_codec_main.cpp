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
//  ID: $Id: test_codec_main.cpp,v 9.1 2005/03/23 12:51:35 cvsadmin Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//  MAP V4 ASN.1 codec example.
//
//  This example shows how to build (create, insert data and encode) and how
//  to interpret (decode and retrieve data) for the following MAP operation
//  arguments:
//
//  o   InsertSubscriberDataArg.
//
//  o   ....
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

#include <Asn.h>
#include <AsnException.h>

#include <map_cpp.h>
#include <map_v4_insert_subscriber_data_arg.h>


#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)

#if defined(ITS_NAMESPACE)
using namespace its;
using namespace map_common;
using namespace map_v4;
#endif // defined(ITS_NAMESPACE)


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
//
//  How to Build a MAP InsertSubscriberData operation argument 
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
BuildOperationInsertSubscriberDataArg()
{
    //  [1] Create InsertSubscriberDataArg object.

    InsertSubscriberDataArg* insertSubscriberDataArg = 
		                           new InsertSubscriberDataArg();

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

    IMSI* imsi = new IMSI(FixedByteArrayToVector(fixedArray1));

    //  [2-2] Set IMSI object in InsertSubscriberDataArg object.

    insertSubscriberDataArg->SetImsi(imsi);


    ////////////////////////////////////////////////////////////////////////////

    //  [3] Populate optional parameter "msisdn".

    //  [3-1] Create an ISDN_AddressString object.

    byte fixedArray2[] = { 0x11U, 0x22U, 0x33U, 0x44U, 0x55U };

    ISDN_AddressString* iSDN_AddressString = 
        new ISDN_AddressString(FixedByteArrayToVector(fixedArray2));

    //  [3-2] Set ISDN_AddressString object in InsertSubscriberDataArg object.

    insertSubscriberDataArg->SetMsisdn(iSDN_AddressString);


    ////////////////////////////////////////////////////////////////////////////

    //  [4] Populate optional parameter "category".

    //  [4-1] Create Category object.

    byte fixedArray3[] = { 0x66U };

    Category* category = 
        new Category(FixedByteArrayToVector(fixedArray3));

    //  [4-2] Set Category object in InsertSubscriberDataArg object.

    insertSubscriberDataArg->SetCategory(category);


    ////////////////////////////////////////////////////////////////////////////

    //  [5] Populate optional parameter "subscriberStatus".

    //  [5-1] Create SubscriberStatus object.

    SubscriberStatus* subscriberStatus = new SubscriberStatus();

    subscriberStatus->SetServiceGranted();

    //  [5-2] Set SubscriberStatus object in InsertSubscriberDataArg object.

    insertSubscriberDataArg->SetSubscriberStatus(subscriberStatus);


    ////////////////////////////////////////////////////////////////////////////

    //  [6] Populate optional parameter "bearerServiceList".

    //  [6-1] Create BearerServiceList object.

    BearerServiceList* bearerServiceList = new BearerServiceList();

    //  MAP API Note: a BearerServiceList object contains a list of 
    //  Ext_BearerServiceCode objects.

    //  [6-1-1] Create Ext_BearerServiceCode object.

    byte fixedArray4[] = { 0xAAU };

    Ext_BearerServiceCode* ext_bearerServiceCode1 = 
        new Ext_BearerServiceCode(FixedByteArrayToVector(fixedArray4));

    //  [6-1-2] Create Ext_BearerServiceCode object.

    byte fixedArray5[] = { 0xBBU };

    Ext_BearerServiceCode* ext_bearerServiceCode2 = 
        new Ext_BearerServiceCode(FixedByteArrayToVector(fixedArray5));

    //  [6-1-3] Add Ext_BearerServiceCode object to BearerServiceList object.

    bearerServiceList->AddElement(ext_bearerServiceCode1);
    
	//  [6-1-4] Add Ext_BearerServiceCode object to BearerServiceList object.

    bearerServiceList->AddElement(ext_bearerServiceCode2);

    //  [6-2] Set BearerServiceList object in InsertSubscriberDataArg object.

    insertSubscriberDataArg->SetBearerServiceList(bearerServiceList);


    ////////////////////////////////////////////////////////////////////////////

    //  [7] Populate optional parameter "teleserviceList".

    //  [7-1] Create TeleServiceList object.

    TeleserviceList* teleserviceList = new TeleserviceList();

    //  MAP API Note: a TeleServiceList object contains a list of 
    //  Ext_TeleServiceCode objects.

    //  [7-1-1] Create Ext_TeleServiceCode object.

    byte fixedArray6[] = { 0xCCU };

    Ext_TeleserviceCode* ext_teleserviceCode1 = 
        new Ext_TeleserviceCode(FixedByteArrayToVector(fixedArray6));

    //  [7-1-2] Create Ext_TeleServiceCode object.
    
    byte fixedArray7[] = { 0xDDU };

    Ext_TeleserviceCode* ext_teleserviceCode2 = 
        new Ext_TeleserviceCode(FixedByteArrayToVector(fixedArray7));
	
	//  [7-1-3] Create Ext_TeleServiceCode object.

    byte fixedArray8[] = { 0xEEU };

    Ext_TeleserviceCode* ext_teleserviceCode3 = 
        new Ext_TeleserviceCode(FixedByteArrayToVector(fixedArray8));
	
	//  [7-1-4] Add Ext_TeleServiceCode object to TeleServiceList object.
	
    teleserviceList->AddElement(ext_teleserviceCode1);

	//  [7-1-5] Add Ext_TeleServiceCode object to TeleServiceList object.
	
    teleserviceList->AddElement(ext_teleserviceCode2);

	//  [7-1-6] Add Ext_TeleServiceCode object to TeleServiceList object.

    teleserviceList->AddElement(ext_teleserviceCode3);

    //  [7-2] Set TeleServiceList object in InsertSubscriberDataArg object.

    insertSubscriberDataArg->SetTeleserviceList(teleserviceList);


    ////////////////////////////////////////////////////////////////////////////

    //  [8] Populate optional parameter "provisionedSS".

    //  [8-1] Create Ext_SS_InfoList object.

    Ext_SS_InfoList* ext_SS_InfoList = new Ext_SS_InfoList();

    //  MAP API Note: an Ext_SS_InfoList object contains a list of 
    //  Ext_SS_Info objects.

    //  [8-1-1] Create Ext_SS_Info object.
    
	Ext_SS_Info* ext_SS_Info1 = new Ext_SS_Info();
    
	//  MAP API Note: an Ext-SS-Info object contains a choice of
	//  Ext-ForwInfo, Ext-CallBarInfo, CUG-Info, Ext-SS-Data or EMLPP-Info.

    //  Choice is forwardingInfo (type Ext_ForwInfo).

    //  [8-1-1-1] Create Ext_ForwInfo object.

    Ext_ForwInfo* ext_forwInfo = new Ext_ForwInfo();

    //  [8-1-1-1-1] Create SS_Code object.

    byte fixedArray9[] = { 0x33U };

    SS_Code* sS_Code1 = new SS_Code(FixedByteArrayToVector(fixedArray9));

    //  [8-1-1-1-2] Set SS_Code object in Ext_ForwInfo object.

    ext_forwInfo->SetSs_Code(sS_Code1);

    //  [8-1-1-1-3] Create Ext_ForwFeatureList object.

    Ext_ForwFeatureList* ext_forwFeatureList = 
        new Ext_ForwFeatureList();

	//  MAP API Note: an Ext-SS-Ext_ForwFeatureList object contains a list
	//  of Ext_ForwFeature objects.

    //  [8-1-1-1-3-1] Create Ext_ForwFeature object.

    Ext_ForwFeature* ext_forwFeature = new Ext_ForwFeature();
    
	//  [8-1-1-1-3-1-1] Create Ext_SS_Status object.
    
	byte fixedArray10[] = { 0x22U, 0x22U, 0x22U };

    Ext_SS_Status* ext_SS_Status1 = 
        new Ext_SS_Status(FixedByteArrayToVector(fixedArray10));

    //  [8-1-1-1-3-1-2] Create Ext_BasicServiceCode object.
    
	Ext_BasicServiceCode* ext_basicServiceCode = new Ext_BasicServiceCode();

    byte fixedArray11[] = { 0x44U };

    Ext_BearerServiceCode* ext_bearerServiceCode = 
        new Ext_BearerServiceCode(FixedByteArrayToVector(fixedArray11));

    ext_basicServiceCode->SetChoiceExt_BearerService(ext_bearerServiceCode);

    //  [8-1-1-1-3-1-3] Create ISDN_SubaddressString object.
    
	byte fixedArray12[] = 
        { 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U };

    ISDN_SubaddressString* iSDN_SubaddressString = 
        new ISDN_SubaddressString(FixedByteArrayToVector(fixedArray12));
    
	//  [8-1-1-1-3-1-4] Set Ext_SS_Status object in Ext_ForwFeature 
    //  object.
    
	ext_forwFeature->SetSs_Status(ext_SS_Status1);
    
	//  [8-1-1-1-3-1-5] Set Ext_BearerServiceCode object in 
    //  Ext_ForwFeature object.
    
	ext_forwFeature->SetBasicService(ext_basicServiceCode);
    
	//  [8-1-1-1-3-1-6] Set ISDN_SubaddressString object in 
    //  Ext_ForwFeature object.
    
	ext_forwFeature->SetForwardedToSubaddress(iSDN_SubaddressString);


    //  [8-1-1-1-3-2] Add Ext_ForwFeature object to Ext_ForwFeatureList 
    //  object.

    ext_forwFeatureList->AddElement(ext_forwFeature);

    //  [8-1-1-1-4] Set ForwardingFeatureList object in Ext_ForwInfo 
    //  object.

    ext_forwInfo->SetForwardingFeatureList(ext_forwFeatureList);

    //  [8-1-1-2] Set choice ForwardingInfo of Ext_SS_Info object.

    ext_SS_Info1->SetChoiceForwardingInfo(ext_forwInfo);
    
	//  [8-1-2] Create Ext_SS_Info object.
    
	Ext_SS_Info* ext_SS_Info2 = new Ext_SS_Info();

	//  MAP API Note: an Ext-SS-Info object contains a choice of
	//  Ext-ForwInfo, Ext-CallBarInfo, CUG-Info, Ext-SS-Data or EMLPP-Info.

    //  Choice is cug-Info.

    //  [8-1-2-1] Create CUG_Info object.

    CUG_Info* cUG_Info = new CUG_Info();

    //  [8-1-2-1-1] Create CUG_SubscriptionList object.

    CUG_SubscriptionList* cUG_SubscriptionList = new CUG_SubscriptionList();

	//  MAP API Note: an CUG_SubscriptionList object contains a list of 
    //  CUG_Subscription objects.

    //  [8-1-2-1-1-1] Create CUG_Subscription object.
    
	CUG_Subscription* cUG_Subscription1 = new CUG_Subscription();

    CUG_Index* cUG_Index1 = new CUG_Index(1999l);

    cUG_Subscription1->SetCug_Index(cUG_Index1);

    byte fixedArray13[] = { 0x11U, 0x22U, 0x33U, 0x44U };

    CUG_Interlock* cUG_Interlock1 = 
        new CUG_Interlock(FixedByteArrayToVector(fixedArray13));

    cUG_Subscription1->SetCug_Interlock(cUG_Interlock1);

    IntraCUG_Options* intraCUG_Options1 = new IntraCUG_Options();

    intraCUG_Options1->SetNoCUG_Restrictions();

    cUG_Subscription1->SetIntraCUG_Options(intraCUG_Options1);

    //  [8-1-2-1-1-2] Create CUG_Subscription object.
    
	CUG_Subscription* cUG_Subscription2 = new CUG_Subscription();

    CUG_Index* cUG_Index2 = new CUG_Index(2001l);

    cUG_Subscription2->SetCug_Index(cUG_Index2);

    byte fixedArray14[] = { 0x44U, 0x33U, 0x22U, 0x11U };

    CUG_Interlock* cUG_Interlock2 = 
        new CUG_Interlock(FixedByteArrayToVector(fixedArray14));

    cUG_Subscription2->SetCug_Interlock(cUG_Interlock2);

    IntraCUG_Options* intraCUG_Options2 = new IntraCUG_Options();

    intraCUG_Options2->SetNoCUG_Restrictions();

    cUG_Subscription2->SetIntraCUG_Options(intraCUG_Options2);

    //  [8-1-2-1-1-3] Add CUG_Subscription object to 
    //  CUG_SubscriptionList object.
    
	cUG_SubscriptionList->AddElement(cUG_Subscription1);
    
	//  [8-1-2-1-1-4] Add CUG_Subscription object to 
    //  CUG_SubscriptionList object.

    cUG_SubscriptionList->AddElement(cUG_Subscription2);


    //  [8-1-2-1-2] Set CUG_SubscriptionList object in object CUG_Info.

    cUG_Info->SetCug_SubscriptionList(cUG_SubscriptionList);

    //  [8-1-2-2] Set choice CUG_Info in object Ext_SS_Info.

    ext_SS_Info2->SetChoiceCug_Info(cUG_Info);

    //  [8-1-3] Create Ext_SS_Info object.
    
	Ext_SS_Info* ext_SS_Info3 = new Ext_SS_Info();

	//  MAP API Note: an Ext-SS-Info object contains a choice of
	//  Ext-ForwInfo, Ext-CallBarInfo, CUG-Info, Ext-SS-Data or EMLPP-Info.

    //  Choice is ss-Data.

    //  [8-1-3-1] Create Ext_SS_Data object.

    Ext_SS_Data* ext_SS_Data = new Ext_SS_Data();

    //  [8-1-3-1-1] Create SS_Code object.
    
	byte fixedArray15[] = { 0x11U };

    SS_Code* sS_Code2 = new SS_Code(FixedByteArrayToVector(fixedArray15));
    
	//  [8-1-3-1-2] Create SS_Status object.
    
	byte fixedArray16[] = { 0x22U, 0x22U };

    Ext_SS_Status* ext_SS_Status2 = 
        new Ext_SS_Status(FixedByteArrayToVector(fixedArray16));

    //  [8-1-3-1-3] Create SS_SubscriptionOption object.
    
	SS_SubscriptionOption* sS_SubscriptionOption = new SS_SubscriptionOption();

    CliRestrictionOption* cliRestrictionOption = new CliRestrictionOption();

    cliRestrictionOption->SetTemporaryDefaultRestricted();

    sS_SubscriptionOption->SetChoiceCliRestrictionOption(cliRestrictionOption);

	//  [8-1-3-1-4] Set SS_Code object in Ext_SS_Data object.

    ext_SS_Data->SetSs_Code(sS_Code2);
	
	//  [8-1-3-1-5] Set SS_Status object in Ext_SS_Data object.
    
	ext_SS_Data->SetSs_Status(ext_SS_Status2);
	
	//  [8-1-3-1-6] Set SS_SubscriptionOption object in Ext_SS_Data 
    //  object.
    
	ext_SS_Data->SetSs_SubscriptionOption(sS_SubscriptionOption);

    
	//  [8-1-3-2] Set choice Ext_SS_Data in Ext_SS_Info object.

    ext_SS_Info3->SetChoiceSs_Data(ext_SS_Data);

	//  [8-1-4] Add Ext_SS_Info object to Ext_SS_InfoList object.
    
	ext_SS_InfoList->AddElement(ext_SS_Info1);
	
	//  [8-1-5] Add Ext_SS_Info object to Ext_SS_InfoList object.
    
	ext_SS_InfoList->AddElement(ext_SS_Info2);
	
	//  [8-1-6] Add Ext_SS_Info object to Ext_SS_InfoList object.
    
	ext_SS_InfoList->AddElement(ext_SS_Info3);
    
	//  [8-2] Set Ext_SS_InfoList object in InsertSubscriberDataArg object.
    
	insertSubscriberDataArg->SetProvisionedSS(ext_SS_InfoList);

    ////////////////////////////////////////////////////////////////////////////

    //  [9] Populate optional parameter "odb_data".

    //  [9-1] Create an ODB_Data object.
    
	ODB_Data* oDB_Data = new ODB_Data();
    
	//  [9-1-1] Create an ODB_GeneralData object.
    
	bool fixedArray17[] = { true, false, true, false, true,
                            false, true, false, true, false,
                            true, false, true, false, true,
                            false, true, false, true, false,
                            true, false, true, false, true };

    ODB_GeneralData* oDB_GeneralData = 
        new ODB_GeneralData(FixedBooleanArrayToVector(fixedArray17));

    //  [9-1-2] Create an ODB_HPLMN_Data object.
    
	bool fixedArray18[] = { false, true, false, true };

    ODB_HPLMN_Data* oDB_HPLMN_Data = 
        new ODB_HPLMN_Data(FixedBooleanArrayToVector(fixedArray18));

    //  [9-1-3] Set ODB_GeneralData object in ODB_Data object.
    
	oDB_Data->SetOdb_GeneralData(oDB_GeneralData);
    
	//  [9-1-4] Set ODB_HPLMN_Data object in ODB_Data object.

    oDB_Data->SetOdb_HPLMN_Data(oDB_HPLMN_Data);	

    //  [9-2] Set ODB_Data object in InsertSubscriberDataArg object.

    insertSubscriberDataArg->SetOdb_Data(oDB_Data);


    ////////////////////////////////////////////////////////////////////////////

    //  [10] Encode InsertSubscriberDataArg object.

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

    //  [11] Retrieve InsertSubscriberDataArg ASN.1 encoded value from octets 
    //  object.

    vector<byte> encodedInsertSubscriberDataArg = octets->GetArray();

    ////////////////////////////////////////////////////////////////////////////

    //  [12] Free all memory allocated on the heap.

    //  [12-1] Delete InsertSubscriberDataArg object (and therefore all the 
    //  parameter objects that have been previously set).

    delete insertSubscriberDataArg;

    //  [12-2] Delete Octets object created by the call to Encode.

    delete octets;

    ////////////////////////////////////////////////////////////////////////////

    //  [13] Return (by value) InsertSubscriberDataArg ASN.1 encoded value.

    return encodedInsertSubscriberDataArg;
}


////////////////////////////////////////////////////////////////////////////////
//
//  How to interpret an (encoded) MAP Insert Subscriber Data operation 
//  argument (InsertSubscriberDataArg):
//
//  o   Decode an InsertSubscriberDataArg encoded value (i.e. create an 
//      InsertSubscriberDataArg object from an InsertSubscriberDataArg encoded 
//      value).
//
//  o   Retrieve Data from an InsertSubscriberDataArg object.
//

void
InterpretOperationInsertSubscriberDataArg(
                            const vector<byte>& encodedInsertSubscriberDataArg)
{
    //  [1] Create an Octets object from the InsertSubscriberDataArg ASN.1 
    //  encoded value.

    Octets* octets = new Octets(encodedInsertSubscriberDataArg);

    ////////////////////////////////////////////////////////////////////////////

    //  [2] Create InsertSubscriberDataArg object (used by the decode phase).

    InsertSubscriberDataArg* 
        insertSubscriberDataArg = new 
            InsertSubscriberDataArg();

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

        const IMSI& imsi = insertSubscriberDataArg->GetImsi();
        
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

        const ISDN_AddressString& 
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

    //  [6] Retrieve optional parameter "category".

    if (insertSubscriberDataArg->OptionCategory())
    {
        //  [6-1] Retrieve reference to  Category object.

        const Category& category = insertSubscriberDataArg->GetCategory();
        
		//  [6-2] Retrieve contents of Category object.
        
		vector<byte> vector3 = category.GetArray();

        //  Do something with vector of bytes...
        
		//  [6-3] Print Category object.
        
		cout << endl;
        cout << "Printing Category object..." << endl;
        cout << category;
        cout << endl;
    }

    ////////////////////////////////////////////////////////////////////////////

    //  [7] Retrieve optional parameter "subscriberStatus".

    if (insertSubscriberDataArg->OptionSubscriberStatus())
    {
        //  [7-1] Retrieve reference to  SubscriberStatus object.

        const SubscriberStatus& 
            subscriberStatus = 
                insertSubscriberDataArg->GetSubscriberStatus();
        
		//  [7-2] Retrieve contents of SubscriberStatus object.
        
        if (subscriberStatus.IsOperatorDeterminedBarring())
        {
            // Do something...
        }
        else if (subscriberStatus.IsServiceGranted())
        {
            // Do something...
        }
        
		//  [7-3] Print SubscriberStatus object.
        
		cout << endl;
        cout << "Printing SubscriberStatus object..." << endl;
        cout << subscriberStatus;
        cout << endl;
    }

    ////////////////////////////////////////////////////////////////////////////

    //  [8] Retrieve optional parameter "bearerServiceList".

    if (insertSubscriberDataArg->OptionBearerServiceList())
    {
        //  [8-1] Retrieve reference to  BearerServiceList object.

        const BearerServiceList& bearerServiceList =
            insertSubscriberDataArg->GetBearerServiceList();
    
        //  MAP API Note: a BearerServiceList object contains a list of 
        //  Ext_BearerServiceCode objects.

        //  [8-2] Retrieve contents of BearerServiceList object.

        for (int i = 0; i < bearerServiceList.Size(); i++)
        {
            //  [8-2-1] Retrieve reference to Ext_BearerServiceCode object.
            
            const Ext_BearerServiceCode& ext_bearerServiceCode = 
                            bearerServiceList.ElementAt(i);

            //  [8-2-2] Retrieve contents of Ext_BearerServiceCode object.

            vector<byte> vector4 = ext_bearerServiceCode.GetArray();

            //  Do something with vector of bytes...

            //  [8-2-3] Print Ext_BearerServiceCode object.

            cout << endl;
            cout << "Printing Ext_BearerServiceCode object..." << endl;
            cout << ext_bearerServiceCode;
            cout << endl;
        }

        //  [8-3] Print BearerServiceList object.

        cout << endl;
        cout << "Printing BearerServiceList object..." << endl;
        cout << bearerServiceList;
        cout << endl;
    }

    ////////////////////////////////////////////////////////////////////////////

    //  [9] Retrieve optional parameter "provisionedSS".

    if (insertSubscriberDataArg->OptionProvisionedSS())
    {
        //  [9-1] Retrieve reference to  Ext_SS_InfoList object.

        const Ext_SS_InfoList& ext_SS_InfoList = 
            insertSubscriberDataArg->GetProvisionedSS();

        //  MAP API Note: an Ext_SS_InfoList object contains a list of 
        //  Ext_SS_Info objects.

        //  [9-2] Retrieve contents of Ext_SS_InfoList object.

        for (int i = 0; i < ext_SS_InfoList.Size(); i++)
        {
            //  [9-2-1] Retrieve reference to Ext_SS_Info object.
            
            const Ext_SS_Info& ext_SS_Info = 
                            ext_SS_InfoList.ElementAt(i);

	        //  MAP API Note: an Ext-SS-Info object contains a choice of
	        //  Ext-ForwInfo, Ext-CallBarInfo, CUG-Info, Ext-SS-Data or 
            //  EMLPP-Info.

            //  [9-2-2] Retrieve contents of Ext_SS_Info object.
            
            if (ext_SS_Info.ChoiceForwardingInfo())
            {
                //  [9-2-2-1] Retrieve reference to Ext_ForwInfo object.
                
                const Ext_ForwInfo& ext_ForwInfo = 
                            ext_SS_Info.GetChoiceForwardingInfo();                
                
                //  [9-2-2-2] Retrieve contents of Ext_ForwInfo object.
                
                //  [9-2-2-2-1] Retrieve reference to SS_Code object.
                
                const SS_Code& sS_Code = ext_ForwInfo.GetSs_Code();

                //  [9-2-2-2-2] Retrieve contents of SS_Code object.
        
                vector<byte> vector5 = sS_Code.GetArray();

                //  Do something with vector of bytes...
                
                //  [9-2-2-2-3] Print SS_Code object.
                
                cout << endl;
                cout << "Printing SS_Code object..." << endl;
                cout << sS_Code;
                cout << endl;

                //  [9-2-2-2-4] Retrieve reference to Ext_ForwFeatureList 
                //  object.

                const Ext_ForwFeatureList& 
                    ext_ForwFeatureList = 
                        ext_ForwInfo.GetForwardingFeatureList();

                //  [9-2-2-2-5] Retrieve contents of Ext_ForwFeatureList object.
           
	            //  MAP API Note: an Ext_ForwFeatureList object contains a 
                //  list of Ext_ForwFeature objects.

                for (int i = 0; i < ext_ForwFeatureList.Size(); i++)
                {
                    //  [9-2-2-2-5-1] Retrieve reference to Ext_ForwFeature 
                    //  object.
            
                    const Ext_ForwFeature& ext_ForwFeature = 
                                    ext_ForwFeatureList.ElementAt(i);

                    //  [9-2-2-2-5-2] Retrieve contents of Ext_ForwFeature 
                    //  object.
                    
                    //  [9-2-2-2-5-2-1] Retrieve reference to Ext_SS_Status 
                    //  object.
                    
                    const Ext_SS_Status& ext_SS_Status = 
                        ext_ForwFeature.GetSs_Status();

                    //  [9-2-2-2-5-2-2] Retrieve contents of Ext_SS_Status 
                    //  object.

                    vector<byte> vector6 = ext_SS_Status.GetArray();

                    //  Do something with vector of bytes...
                    
                    //  [9-2-2-2-5-2-3] Print Ext_SS_Status object.

                    cout << endl;
                    cout << "Printing Ext_SS_Status object..." << endl;
                    cout << ext_SS_Status;
                    cout << endl;
                    
                    //  [9-2-2-2-5-2-4] Retrieve reference to 
                    //  Ext_BasicServiceCode object.
                    
                    const Ext_BasicServiceCode& ext_BasicServiceCode = 
                                    ext_ForwFeature.GetBasicService();

                    //  [9-2-2-2-5-2-5] Retrieve contents of 
                    //  Ext_BasicServiceCode object.

                    if (ext_BasicServiceCode.ChoiceExt_BearerService())
                    {
                        // Do something...
                    }
                    else if (ext_BasicServiceCode.ChoiceExt_Teleservice())
                    {
                        // Do something...
                    }
                    
                    //  [9-2-2-2-5-2-6] Print Ext_BasicServiceCode object.

                    cout << endl;
                    cout << "Printing Ext_BasicServiceCode object..." << endl;
                    cout << ext_BasicServiceCode;
                    cout << endl;
                    
                    //  [9-2-2-2-5-2-7] Retrieve reference to 
                    //  ISDN_SubaddressString object.
                    
                    const ISDN_SubaddressString& iSDN_SubaddressString =
                                    ext_ForwFeature.GetForwardedToSubaddress();

                    //  [9-2-2-2-5-2-8] Retrieve contents of 
                    //  ISDN_SubaddressString object.

                    vector<byte> vector7 = iSDN_SubaddressString.GetArray();

                    //  Do something with vector of bytes...
                    
                    //  [9-2-2-2-5-2-9] Print ISDN_SubaddressString object.

                    cout << endl;
                    cout << "Printing ISDN_SubaddressString object..." << endl;
                    cout << iSDN_SubaddressString;
                    cout << endl;
                    
                    //  [9-2-2-2-5-3] Print Ext_ForwFeature object.

                    cout << endl;
                    cout << "Printing Ext_ForwFeature object..." << endl;
                    cout << ext_ForwFeature;
                    cout << endl;
                }                
                
                //  [9-2-2-2-6] Print Ext_ForwFeatureList object.

                cout << endl;
                cout << "Printing Ext_ForwFeatureList object..." << endl;
                cout << ext_ForwFeatureList;
                cout << endl;
                
                //  [9-2-2-3] Print Ext_ForwInfo object.

                cout << endl;
                cout << "Printing Ext_ForwInfo object..." << endl;
                cout << ext_ForwInfo;
                cout << endl;
            }
            else if (ext_SS_Info.ChoiceCug_Info())
            {
                cout << endl;
                cout << "Choice Cug Info not printed..." << endl;
                cout << endl;
            }
            else if (ext_SS_Info.ChoiceSs_Data())
            {
                cout << endl;
                cout << "Choice Ss Data not printed..." << endl;
                cout << endl;
            }

            //  [9-2-3] Print Ext_SS_Info object.

            cout << endl;
            cout << "Printing Ext_SS_Info object..." << endl;
            cout << ext_SS_Info;
            cout << endl;
        }

        //  [9-3] Print Ext_SS_InfoList object.

        cout << endl;
        cout << "Printing Ext_SS_InfoList object..." << endl;
        cout << ext_SS_InfoList;
        cout << endl;
    }            

    ////////////////////////////////////////////////////////////////////////////

    //  [10] Free all memory allocated on the heap.

    //  [10-1] Delete Octets object.

    delete octets;

    //  [10-2] Delete InsertSubscriberDataArg object.

    delete insertSubscriberDataArg;
}





////////////////////////////////////////////////////////////////////////////////
//
//  Entry point:
//
//  o   Initialize IntelliSS7.
//
//  o   Call BuildOperationInsertSubscriberDataArg function.
//  
//  o   Call InterpretOperationInsertSubscriberDataArg function.
//  
//  o   Terminate IntelliSS7.
// 

int main(int argc, char* argv[])
{
    cout << endl << "Begin MAP V4 ASN.1 codec example..." << endl;

    try
    {
        // IntelliSS7 initialization (including licensing).

        int res = ITS_GlobalStart(0);

        if (res != ITS_SUCCESS)
        {
            throw ITS_Error(res, __FILE__, __LINE__);
        }

        ////////////////////////////////////////////////////////////////////////

        //  [1] Call BuildOperationInsertSubscriberDataArg function.

        vector<byte> encodedInsertSubscriberDataArg =
            BuildOperationInsertSubscriberDataArg();

        //  [2] Call InterpretOperationInsertSubscriberDataArg function.

        InterpretOperationInsertSubscriberDataArg(
            encodedInsertSubscriberDataArg);


        ////////////////////////////////////////////////////////////////////////

        // IntelliSS7 termination.

        ITS_GlobalStop();
    }
    catch (ITS_GenericException& exp)
    {
        cout << endl << exp.GetDescription() << endl;

        ITS_GlobalStop();
    }

    cout << endl << "End of MAP V4 ASN.1 codec example." << endl;
    

    // To stop here in console application.

    cout << endl << "Press Enter to quit...";

    char c = '\0';
    cin.get(c);

    return EXIT_SUCCESS;
}

