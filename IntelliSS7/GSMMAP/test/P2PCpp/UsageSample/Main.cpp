////////////////////////////////////////////////////////////////////////////////
//
//
// GSMMAP usage sample (Insert Subscriber Data).
//
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <conio.h>

#include <its++.h>
#include <its_stubs.h>
#include <its_ss7_stubs.h>

#include <AsnException.h>

#include <InsertSubscriberDataArg.h>


// Since the code rely on the standard C++ library,
// the following must be accepted by the compiler.
using namespace std;

#if defined(ITS_NAMESPACE)
using namespace its;
#endif    // defined(ITS_NAMESPACE)


static void Test();
static void TestSpeedAndMemory();

static bool testPrint = true;



int main(int argc, char* argv[])
{
    cout << "Begin test..." << endl;


    try
    {

        // The following will be required with the licensing mechanism
        // (one call at the beginning of the application). 
        // Temporary commented.

        // int res = ITS_GlobalStart(0);
        // 
        // if (res != ITS_SUCCESS)
        // {
        //     throw ITS_Error(res, __FILE__, __LINE__);
        // }

        Test();

        // TestSpeedAndMemory();

        // ITS_GlobalStop();
    }
    catch (ITS_GenericException& exp)
    {
        cout << endl << exp.GetDescription() << endl;

        // ITS_GlobalStop();
    }

    cout << "End of test..." << endl;
    
    // To stop here in console application.
    cout << "Type any key to quit...";
    char c = getch();

    return 0;
}


//
// Macro to get size (count of items) of a statically dimensioned array.
//

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))


// Function template to convert arrays to vectors.

template <typename T> inline std::vector<T> ArrayToVector(T array[], size_t size)
{ return std::vector<T>(array, array + size); }


// Helper operator<< to print content of vector of bytes.

static std::string ByteToHexString(byte b)
{
    char strBuf[3];

    sprintf(strBuf, "%02X", b);

    return strBuf;
}

std::ostream& operator<< (std::ostream& os, const std::vector<byte>& vect)
{
    os << "{ ";

    for (int i = 0; i < vect.size(); i++)
    {
        os << "0x" << ByteToHexString(vect[i]).c_str();
        
        if (i != vect.size() - 1)
        {
            os << ",";
        }

        os << " ";
    }

    os << "}";

    return os;
}

void Test()
{
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////
    // InsertSubscriberDataArg Encode part.
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////

    InsertSubscriberDataArg* 
        insertSubscriberDataArg =
            new InsertSubscriberDataArg();

    ////////////////////////////////////////////////////////
    // Set imsi.

    byte array1[] = { 0x01U, 0x02U, 0x03U, 0x04U }; 

    IMSI* imsi = new IMSI(ArrayToVector(array1, ARRAY_SIZE(array1)));

    insertSubscriberDataArg->SetImsi(imsi);


    ////////////////////////////////////////////////////////
    // Set msisdn.

    byte array2[] = { 0x11U, 0x22U, 0x33U, 0x44U, 0x55U };

    ISDN_AddressString* iSDN_AddressString = 
        new ISDN_AddressString(ArrayToVector(array2, ARRAY_SIZE(array2)));

    insertSubscriberDataArg->SetMsisdn(iSDN_AddressString);


    ////////////////////////////////////////////////////////
    // Set category.

    byte array3[] = { 0x66U };

    Category* category = 
        new Category(ArrayToVector(array3, ARRAY_SIZE(array3)));

    insertSubscriberDataArg->SetCategory(category);


    ////////////////////////////////////////////////////////
    // Set subscriberStatus.

    SubscriberStatus* subscriberStatus = new SubscriberStatus();

    subscriberStatus->SetServiceGranted();

    insertSubscriberDataArg->SetSubscriberStatus(subscriberStatus);


    ////////////////////////////////////////////////////////
    // Set bearerServiceList.

    BearerServiceList* bearerServiceList = new BearerServiceList();

    // Insert 2 elements (Type Ext_BearerServiceCode).

    byte array4[] = { 0xAAU };

    Ext_BearerServiceCode* ext_bearerServiceCode1 = 
        new Ext_BearerServiceCode(ArrayToVector(array4, ARRAY_SIZE(array4)));

    bearerServiceList->AddElement(ext_bearerServiceCode1);

    byte array5[] = { 0xBBU };

    Ext_BearerServiceCode* ext_bearerServiceCode2 = 
        new Ext_BearerServiceCode(ArrayToVector(array5, ARRAY_SIZE(array5)));

    bearerServiceList->AddElement(ext_bearerServiceCode2);

    insertSubscriberDataArg->SetBearerServiceList(bearerServiceList);

    ////////////////////////////////////////////////////////
    // Set teleserviceList.

    TeleserviceList* teleserviceList = new TeleserviceList();

    // Insert 3 elements (type Ext_TeleserviceCode).

    byte array6[] = { 0xCCU };

    Ext_TeleserviceCode* ext_teleserviceCode1 = 
        new Ext_TeleserviceCode(ArrayToVector(array6, ARRAY_SIZE(array6)));

    teleserviceList->AddElement(ext_teleserviceCode1);

    byte array7[] = { 0xDDU };

    Ext_TeleserviceCode* ext_teleserviceCode2 = 
        new Ext_TeleserviceCode(ArrayToVector(array7, ARRAY_SIZE(array7)));

    teleserviceList->AddElement(ext_teleserviceCode2);

    byte array8[] = { 0xEEU };

    Ext_TeleserviceCode* ext_teleserviceCode3 = 
        new Ext_TeleserviceCode(ArrayToVector(array8, ARRAY_SIZE(array8)));

    teleserviceList->AddElement(ext_teleserviceCode3);

    insertSubscriberDataArg->SetTeleserviceList(teleserviceList);

    ////////////////////////////////////////////////////////
    // Set provisionedSS (type Ext_SS_InfoList).

    Ext_SS_InfoList* ext_SS_InfoList = new Ext_SS_InfoList();

    // Insert 3 elements (type Ext_SS_Info).

    // First element.

    Ext_SS_Info* ext_SS_Info1 = new Ext_SS_Info();

    // First element choice is forwardingInfo (type Ext_ForwInfo).

    Ext_ForwInfo* ext_forwInfo = new Ext_ForwInfo();

    byte array9[] = { 0x33U };

    SS_Code* sS_Code1 = new SS_Code(ArrayToVector(array9, ARRAY_SIZE(array9)));

    ext_forwInfo->SetSs_Code(sS_Code1);

    Ext_ForwFeatureList* ext_forwFeatureList = 
        new Ext_ForwFeatureList();

    // Insert 1 element (type Ext_ForwFeature).

    Ext_ForwFeature* ext_forwFeature = new Ext_ForwFeature();

    byte array10[] = { 0x22U, 0x22U, 0x22U };

    Ext_SS_Status* ext_SS_Status1 = 
        new Ext_SS_Status(ArrayToVector(array10, ARRAY_SIZE(array10)));

    ext_forwFeature->SetSs_Status(ext_SS_Status1);

    Ext_BasicServiceCode* ext_basicServiceCode = new Ext_BasicServiceCode();

    byte array11[] = { 0x44U };

    Ext_BearerServiceCode* ext_bearerServiceCode = 
        new Ext_BearerServiceCode(ArrayToVector(array11, ARRAY_SIZE(array11)));

    ext_basicServiceCode->SetChoiceExt_BearerService(ext_bearerServiceCode);

    ext_forwFeature->SetBasicService(ext_basicServiceCode);

    byte array12[] = { 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U };

    ISDN_SubaddressString* iSDN_SubaddressString = 
        new ISDN_SubaddressString(ArrayToVector(array12, ARRAY_SIZE(array12)));

    ext_forwFeature->SetForwardedToSubaddress(iSDN_SubaddressString);

    ext_forwFeatureList->AddElement(ext_forwFeature);

    ext_forwInfo->SetForwardingFeatureList(ext_forwFeatureList);

    ext_SS_Info1->SetChoiceForwardingInfo(ext_forwInfo);

    ext_SS_InfoList->AddElement(ext_SS_Info1);

    // Second element.

    Ext_SS_Info* ext_SS_Info2 = new Ext_SS_Info();

    // Second element choice is cug-Info.

    CUG_Info* cUG_Info = new CUG_Info();

    CUG_SubscriptionList* cUG_SubscriptionList = new CUG_SubscriptionList();

    // Insert 2 elements (type CUG_Subscription).

    CUG_Subscription* cUG_Subscription1 = new CUG_Subscription();

    CUG_Index* cUG_Index1 = new CUG_Index(1999l);

    cUG_Subscription1->SetCug_Index(cUG_Index1);

    byte array13[] = { 0x11U, 0x22U, 0x33U, 0x44U };

    CUG_Interlock* cUG_Interlock1 = 
        new CUG_Interlock(ArrayToVector(array13, ARRAY_SIZE(array13)));

    cUG_Subscription1->SetCug_Interlock(cUG_Interlock1);

    IntraCUG_Options* intraCUG_Options1 = new IntraCUG_Options();

    intraCUG_Options1->SetNoCUG_Restrictions();

    cUG_Subscription1->SetIntraCUG_Options(intraCUG_Options1);

    cUG_SubscriptionList->AddElement(cUG_Subscription1);

    CUG_Subscription* cUG_Subscription2 = new CUG_Subscription();

    CUG_Index* cUG_Index2 = new CUG_Index(2001l);

    cUG_Subscription2->SetCug_Index(cUG_Index2);

    byte array14[] = { 0x44U, 0x33U, 0x22U, 0x11U };

    CUG_Interlock* cUG_Interlock2 = 
        new CUG_Interlock(ArrayToVector(array14, ARRAY_SIZE(array14)));

    cUG_Subscription2->SetCug_Interlock(cUG_Interlock2);

    IntraCUG_Options* intraCUG_Options2 = new IntraCUG_Options();

    intraCUG_Options2->SetNoCUG_Restrictions();

    cUG_Subscription2->SetIntraCUG_Options(intraCUG_Options2);

    cUG_SubscriptionList->AddElement(cUG_Subscription2);

    cUG_Info->SetCug_SubscriptionList(cUG_SubscriptionList);

    ext_SS_Info2->SetChoiceCug_Info(cUG_Info);

    ext_SS_InfoList->AddElement(ext_SS_Info2);

    // Third element.

    Ext_SS_Info* ext_SS_Info3 = new Ext_SS_Info();

    // Third element choice is ss-Data.

    Ext_SS_Data* ext_SS_Data = new Ext_SS_Data();

    byte array15[] = { 0x11U };

    SS_Code* sS_Code2 = new SS_Code(ArrayToVector(array15, ARRAY_SIZE(array15)));

    ext_SS_Data->SetSs_Code(sS_Code2);

    byte array16[] = { 0x22U, 0x22U };

    Ext_SS_Status* ext_SS_Status2 = 
        new Ext_SS_Status(ArrayToVector(array16, ARRAY_SIZE(array16)));

    ext_SS_Data->SetSs_Status(ext_SS_Status2);

    SS_SubscriptionOption* sS_SubscriptionOption = new SS_SubscriptionOption();

    CliRestrictionOption* cliRestrictionOption = new CliRestrictionOption();

    cliRestrictionOption->SetTemporaryDefaultRestricted();

    sS_SubscriptionOption->SetChoiceCliRestrictionOption(cliRestrictionOption);

    ext_SS_Data->SetSs_SubscriptionOption(sS_SubscriptionOption);

    ext_SS_Info3->SetChoiceSs_Data(ext_SS_Data);

    ext_SS_InfoList->AddElement(ext_SS_Info3);

    insertSubscriberDataArg->SetProvisionedSS(ext_SS_InfoList);

    ////////////////////////////////////////////////////////
    // Set odb-Data.

    ODB_Data* oDB_Data = new ODB_Data();

    bool array17[] = { true, false, true, false, true,
                       false, true, false, true, false,
                       true, false, true, false, true,
                       false, true, false, true, false,
                       true, false, true, false, true };

    ODB_GeneralData* oDB_GeneralData = 
        new ODB_GeneralData(ArrayToVector(array17, ARRAY_SIZE(array17)));

    oDB_Data->SetOdb_GeneralData(oDB_GeneralData);

    bool array18[] = { false, true, false, true };

    ODB_HPLMN_Data* oDB_HPLMN_Data = 
        new ODB_HPLMN_Data(ArrayToVector(array18, ARRAY_SIZE(array18)));

    oDB_Data->SetOdb_HPLMN_Data(oDB_HPLMN_Data);

    insertSubscriberDataArg->SetOdb_Data(oDB_Data);


    ////////////////////////////////////////////////////////
    // Print ASN.1 value before encoding.
    ////////////////////////////////////////////////////////

    if (testPrint)
    {
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Printing ASN.1 value before encoding..." << endl;
        cout << endl;
        cout << *insertSubscriberDataArg;
        cout << endl;
    }

    ////////////////////////////////////////////////////////
    // Encode using ASN.1 BER.
    ////////////////////////////////////////////////////////

    Octets* octets = NULL;

    try
    {
        octets = insertSubscriberDataArg->Encode();
    }
    catch (AsnEncodeError& exc)
    {
        if (testPrint)
        {
            cout << endl;
            cout << "--------------------------------------------------" << endl;
            cout << "Exception during encoding phase..." << endl;
            cout << exc.GetDescription() << endl;
            cout << "Exit test..." << endl;

            exit(EXIT_FAILURE);
        }
    }

    if (testPrint)
    {
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Printing ASN.1 encoded value..." << endl;
        cout << endl;
        cout << *octets;
        cout << endl;
    }

    // Release all allocated memory till current point.

    delete insertSubscriberDataArg;

    insertSubscriberDataArg = NULL;


    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////
    // InsertSubscriberDataArg Decode part.
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////

    /////////////////////////////
    // Decoded => suffix "Dec".
    /////////////////////////////

    // For all optionals we should check that they are present with the
    // OptionXXXXXX() member functions.

    InsertSubscriberDataArg*
        insertSubscriberDataArgDec = 
            new InsertSubscriberDataArg();

    ////////////////////////////////////////////////////////
    // Decoding using ASN.1 BER.
    ////////////////////////////////////////////////////////

    try
    {
        insertSubscriberDataArgDec->Decode(*octets);
    }
    catch (AsnDecodeError& exc)
    {
        if (testPrint)
        {
            cout << endl;
            cout << "--------------------------------------------------" << endl;
            cout << "Exception during decoding phase..." << endl;
            cout << exc.GetDescription() << endl;
            cout << "Exit test..." << endl;

            exit(EXIT_FAILURE);
        }
    }

    ////////////////////////////////////////////////////////
    // Print ASN.1 value after decoding.
    ////////////////////////////////////////////////////////

    if (testPrint)
    {
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Printing ASN.1 value after decoding..." << endl;
        cout << endl;
        cout << *insertSubscriberDataArgDec;
        cout << endl;
    }


    if (testPrint)
    {
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Access ASN.1 value content after decoding..." << endl;
        cout << endl;
    }

    if (insertSubscriberDataArgDec->OptionImsi())
    {
        const IMSI& imsiDec = insertSubscriberDataArgDec->GetImsi();

        if (testPrint)
        {
            cout << endl;
            cout << imsiDec;
            cout << endl;
        }

        const vector<byte>& arrayDec = imsiDec.GetArray();

        if (testPrint)
        {
            cout << endl;
            cout << "IMSI raw content: " << arrayDec;
            cout << endl;
        }
    }

    if (insertSubscriberDataArgDec->OptionBearerServiceList())
    {
        const BearerServiceList& bearerServiceListDec =
            insertSubscriberDataArgDec->GetBearerServiceList();

        if (testPrint)
        {
            cout << endl;
            cout << "BearerServiceList has <";
            cout << bearerServiceListDec.Size();
            cout << "> element(s).";
            cout << endl;
        }

        // Get first element (size of SEQUENCE OF is >= 1).

        const Ext_BearerServiceCode& ext_bearerServiceCodeDec = 
            bearerServiceListDec.ElementAt(0);

        if (testPrint)
        {
            cout << endl;
            cout << ext_bearerServiceCodeDec;
            cout << endl;
        }

        const vector<byte>& arrayDec = ext_bearerServiceCodeDec.GetArray();

        if (testPrint)
        {
            cout << endl;
            cout << "Ext_BearerServiceCode raw content: " << arrayDec;
            cout << endl;
        }
    }

    if (insertSubscriberDataArgDec->OptionProvisionedSS())
    {
        const Ext_SS_InfoList& ext_SS_InfoListDec = 
            insertSubscriberDataArgDec->GetProvisionedSS();

        if (testPrint)
        {
            cout << endl;
            cout << "Ext_SS_InfoList has <";
            cout << ext_SS_InfoListDec.Size();
            cout << "> element(s).";
            cout << endl;
        }

        // Get first element (size of SEQUENCE OF is >= 1).

        const Ext_SS_Info& ext_SS_InfoDec =
            ext_SS_InfoListDec.ElementAt(0);

        if (ext_SS_InfoDec.ChoiceForwardingInfo())
        {
            const Ext_ForwInfo& ext_ForwInfoDec = 
                ext_SS_InfoDec.GetChoiceForwardingInfo();

            const Ext_ForwFeatureList& ext_ForwFeatureListDec =
                ext_ForwInfoDec.GetForwardingFeatureList();

            if (testPrint)
            {
                cout << endl;
                cout << "Ext_ForwFeatureList has <";
                cout << ext_ForwFeatureListDec.Size();
                cout << "> element(s).";
                cout << endl;
            }

            // Get first element (size of SEQUENCE OF is >= 1).

            const Ext_ForwFeature& ext_ForwFeatureDec =
                ext_ForwFeatureListDec.ElementAt(0);

            if (testPrint)
            {
                cout << endl;
                cout << ext_ForwFeatureDec;
                cout << endl;
            }

            if (ext_ForwFeatureDec.OptionForwardedToSubaddress())
            {
                const ISDN_SubaddressString& iSDN_SubaddressStringDec =
                    ext_ForwFeatureDec.GetForwardedToSubaddress();

                if (testPrint)
                {
                    cout << endl;
                    cout << iSDN_SubaddressStringDec;
                    cout << endl;
                }

                const vector<byte>& arrayDec = 
                        iSDN_SubaddressStringDec.GetArray();

                if (testPrint)
                {
                    cout << endl;
                    cout << "ForwardedToSubaddress raw content: " << endl;
                    cout << arrayDec;
                    cout << endl;
                }
            }
        }
    }

    // To be continued...

    // Release all allocated memory.

    delete insertSubscriberDataArgDec;
    delete octets;
}

void TestSpeedAndMemory()
{
    testPrint = false;

    for (long i = 0; i < 10000l; i++)
    {
       Test();
    }

    testPrint = true;
}

