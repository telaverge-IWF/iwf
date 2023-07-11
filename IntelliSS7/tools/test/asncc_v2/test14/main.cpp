///////////////////////////////////////////////////////////////////////////////
//
// Test14 (test of EXTERNAL and indirectly of ANY).
//
///////////////////////////////////////////////////////////////////////////////

#if defined(WIN32)
#pragma warning(disable:4786) 
#endif // defined(WIN32)

#include <stdio.h>
#include <iostream>

#if defined(WIN32)
#include <conio.h>
#endif // defined(WIN32)

#include <its++.h>
#include <its_statics.cpp>

#include <EXTERNAL.h>
#include <IA5String.h>

using namespace std;
using namespace its;


static void Test();
static void TestXml();

static bool testPrint = true;


int 
main(int argc, char* argv[])
{
    cout << "Begin test..." << endl;

    try
    {
        Test();

        cout << endl << endl;

        TestXml();
    }
    catch (ITS_GenericException& exp)
    {
        cout << endl << exp.GetDescription() << endl;
    }

    cout << "End of test..." << endl;
    
#if defined(WIN32)
    // To stop here in console application.
    cout << "Type any key to quit...";
    char c = getch();
#endif // defined(WIN32)

    return 0;
}


void
Test()
{

    EXTERNAL* external = new EXTERNAL();

    EXTERNAL::Indirect_reference* 
        indirect_Reference = 
            new EXTERNAL::Indirect_reference();

    indirect_Reference->SetValue(1999);

    EXTERNAL::Encoding* encoding = new EXTERNAL::Encoding();

    EXTERNAL::Encoding::Single_ASN1_type* single_ASN1_type =
        new EXTERNAL::Encoding::Single_ASN1_type();

    IA5String* iA5String = new IA5String();

    iA5String->SetString("Space 1999");

    single_ASN1_type->SetAny(iA5String);

    encoding->SetChoice(single_ASN1_type);

    external->SetIndirect_reference(indirect_Reference);

    external->SetEncoding(encoding);

    // Encode to ASN.1.

    Octets* octets = external->Encode();

    if (testPrint)
    {
        cout << endl;
        cout << "Printing ASN.1 encoded value..." << endl;
        cout << *octets;
        cout << endl;
    }

    // Decode from ASN.1 => suffix "After".

    EXTERNAL* externalAfter = new EXTERNAL();

    externalAfter->Decode(*octets);

    if (testPrint)
    {
        cout << endl;
        cout << "Printing decoded external..." << endl;
        cout << *externalAfter;
        cout << endl;
    }

    // Release all the memory.
    delete externalAfter;
    delete external;
    delete octets;
}


void
TestXml()
{
    EXTERNAL* external = new EXTERNAL();

    EXTERNAL::Indirect_reference* 
        indirect_Reference = 
            new EXTERNAL::Indirect_reference();

    indirect_Reference->SetValue(1999);

    EXTERNAL::Encoding* encoding = new EXTERNAL::Encoding();

    EXTERNAL::Encoding::Single_ASN1_type* single_ASN1_type =
        new EXTERNAL::Encoding::Single_ASN1_type();

    IA5String* iA5String = new IA5String();

    iA5String->SetString("Space 1999");

    single_ASN1_type->SetAny(iA5String);

    encoding->SetChoice(single_ASN1_type);

    external->SetIndirect_reference(indirect_Reference);

    external->SetEncoding(encoding);

    // Encode to ASN.1.

    Characters* characters = external->EncodeToXml();

    if (testPrint)
    {
        cout << endl;
        cout << "Printing ASN.1 encoded value..." << endl;
        cout << *characters;
        cout << endl;
    }

    // Decode from ASN.1 => suffix "After".

    EXTERNAL* externalAfter = new EXTERNAL();

    externalAfter->DecodeFromXml(*characters);

    if (testPrint)
    {
        cout << endl;
        cout << "Printing decoded external..." << endl;
        cout << *externalAfter;
        cout << endl;
    }

    // Release all the memory.
    delete externalAfter;
    delete external;
    delete characters;
}






#if 0

//
// Local reference format => no more need for complicated nested scoping
// declaration.
//

void 
TestLRF()
{
    FeatureRequestRRL*
        featureRequestRRL = 
            new FeatureRequestRRL();

    FeatureResult* featureResult = new FeatureResult();

    featureResult->SetSuccessful();

    featureRequestRRL->SetFeatureResult(featureResult);
        
    byte array1[] = { 0xAAU, 0xBBU, 0xCCU, 0xDDU };

    vector<byte> v1(array1, array1 + 4);

    GroupInformation* groupInformation = new GroupInformation(v1);

    featureRequestRRL->SetGroupInformation(groupInformation);

    TerminationList* terminationList = new TerminationList();

    //
    // Local scope typedef still needed because CHOICE is not a Local Reference.
    // (And CHOICE is an anonymous type of SEQUENCE OF.)
    //

    typedef FeatureRequestRRL::
                TerminationList::
                    CHOICE
                        CHOICE;
                
    CHOICE* choice1 = new CHOICE();

    LocalTermination* localTermination = new LocalTermination();

    byte array2[] = { 0x01U, 0x02U, 0x03U, 0x04U };

    vector<byte> v2(array2, array2 + 4);

    ElectronicSerialNumber* electronicSerialNumber = 
        new ElectronicSerialNumber(v2);

    localTermination->
        SetElectronicSerialNumber(
            electronicSerialNumber);

    byte array3[] = { 0xF1U, 0xF2U };

    vector<byte> v3(array3, array3 + 2);

    AlertCode* alertCode = new AlertCode(v3);

    localTermination->
        SetAlertCode(
            alertCode);

    choice1->SetChoiceLocalTermination(localTermination);

    terminationList->AddElement(choice1);

    CHOICE* choice2 = new CHOICE();

    PSTNTermination* pSTNTermination = new PSTNTermination();

    byte array4[] = { 0x10U, 0x20U, 0x30U, 0x40U, 0x50U };

    vector<byte> v4(array4, array4 + 5);

    DestinationDigits* destinationDigits = new DestinationDigits(v4);
    
    pSTNTermination->SetDestinationDigits(destinationDigits);

    byte array5[] = { 0x11U, 0x22U, 0x33U, 0x44U, 0x55U, 0x66U, 0x77U };

    vector<byte> v5(array5, array5 + 7);

    CarrierDigits* carrierDigits = new CarrierDigits(v5);
    
    pSTNTermination->SetCarrierDigits(carrierDigits);

    choice2->SetChoicePSTNTermination(pSTNTermination);

    terminationList->AddElement(choice2);

    featureRequestRRL->SetTerminationList(terminationList);

    // Encode to ASN.1.

    Octets* octets = featureRequestRRL->Encode();

    if (testPrint)
    {
        cout << endl;
        cout << "Printing ASN.1 encoded value..." << endl;
        cout << *octets;
        cout << endl;
    }

    // Decode from ASN.1 => suffix "After".
    // For all optionals we should check that they are present
    // with the OptionXXXXXXXX() member functions.

    FeatureRequestRRL*
        featureRequestRRLAfter = 
            new FeatureRequestRRL();

    featureRequestRRLAfter->Decode(*octets);

    const FeatureResult& featureResultAfter 
        = featureRequestRRLAfter->GetFeatureResult();

    const GroupInformation& groupInformationAfter
        = featureRequestRRLAfter->GetGroupInformation();

    const TerminationList& terminationListAfter
        = featureRequestRRLAfter->GetTerminationList();

    const CHOICE& choice1After = terminationListAfter.ElementAt(0);

    const CHOICE& choice2After = terminationListAfter.ElementAt(1);

    if (choice1After.ChoiceLocalTermination())
    {
        const LocalTermination& localTerminationAfter = 
            choice1After.GetChoiceLocalTermination();

        const ElectronicSerialNumber& electronicSerialNumberAfter =
            localTerminationAfter.GetElectronicSerialNumber();

        const AlertCode& alertCodeAfter = 
            localTerminationAfter.GetAlertCode();

    }

    if (choice2After.ChoicePSTNTermination())
    {
        const PSTNTermination& pSTNTerminationAfter = 
            choice2After.GetChoicePSTNTermination();

        const DestinationDigits& destinationDigitsAfter =
            pSTNTerminationAfter.GetDestinationDigits();

        const CarrierDigits& carrierDigitsAfter = 
            pSTNTerminationAfter.GetCarrierDigits();

    }

    if (testPrint)
    {
        cout << endl;
        cout << "Printing decoded featureRequestRRL..." << endl;
        cout << *featureRequestRRLAfter;
        cout << endl;
    }

    // Release all the memory.

    delete featureRequestRRLAfter;
    delete featureRequestRRL;
    delete octets;
}


//
// Backward compatibility with complicated nested scoping declarations.
//

void 
TestBackwardCompatibility()
{
    FeatureRequestRRL*
        featureRequestRRL = 
            new FeatureRequestRRL();

    // Local scope typedef.
    typedef FeatureRequestRRL::
                FeatureResult 
                    FeatureResult;

    FeatureResult* featureResult = new FeatureResult();

    featureResult->SetSuccessful();

    featureRequestRRL->SetFeatureResult(featureResult);

    // Local scope typedef.
    typedef FeatureRequestRRL::
                GroupInformation
                    GroupInformation;
        
    byte array1[] = { 0xAAU, 0xBBU, 0xCCU, 0xDDU };

    vector<byte> v1(array1, array1 + 4);

    GroupInformation* groupInformation = new GroupInformation(v1);

    featureRequestRRL->SetGroupInformation(groupInformation);

    // Local scope typedef.
    typedef FeatureRequestRRL::
                TerminationList
                    TerminationList;

    TerminationList* terminationList = new TerminationList();

    // Local scope typedef.
    typedef FeatureRequestRRL::
                TerminationList::
                    CHOICE
                        CHOICE;
                
    CHOICE* choice1 = new CHOICE();

    // Local scope typedef.
    typedef FeatureRequestRRL::
                TerminationList::
                    CHOICE::
                        LocalTermination
                            LocalTermination;

    LocalTermination* localTermination = new LocalTermination();

    // Local scope typedef.
    typedef FeatureRequestRRL::
                TerminationList::
                    CHOICE::
                        LocalTermination::
                            ElectronicSerialNumber
                                ElectronicSerialNumber;

    byte array2[] = { 0x01U, 0x02U, 0x03U, 0x04U };

    vector<byte> v2(array2, array2 + 4);

    ElectronicSerialNumber* electronicSerialNumber = 
        new ElectronicSerialNumber(v2);

    localTermination->
        SetElectronicSerialNumber(
            electronicSerialNumber);

    // Local scope typedef.
    typedef FeatureRequestRRL::
                TerminationList::
                    CHOICE::
                        LocalTermination::
                            AlertCode
                                AlertCode;

    byte array3[] = { 0xF1U, 0xF2U };

    vector<byte> v3(array3, array3 + 2);

    AlertCode* alertCode = new AlertCode(v3);

    localTermination->
        SetAlertCode(
            alertCode);

    choice1->SetChoiceLocalTermination(localTermination);

    terminationList->AddElement(choice1);

    CHOICE* choice2 = new CHOICE();

    // Local scope typedef.
    typedef FeatureRequestRRL::
                TerminationList::
                    CHOICE::
                        PSTNTermination
                            PSTNTermination;

    PSTNTermination* pSTNTermination = new PSTNTermination();

    // Local scope typedef.
    typedef FeatureRequestRRL::
                TerminationList::
                    CHOICE::
                        PSTNTermination::
                            DestinationDigits
                                DestinationDigits;

    byte array4[] = { 0x10U, 0x20U, 0x30U, 0x40U, 0x50U };

    vector<byte> v4(array4, array4 + 5);

    DestinationDigits* destinationDigits = new DestinationDigits(v4);
    
    pSTNTermination->SetDestinationDigits(destinationDigits);

    // Local scope typdef.
    typedef FeatureRequestRRL::
                TerminationList::
                    CHOICE::
                        PSTNTermination::
                            CarrierDigits
                                CarrierDigits;

    byte array5[] = { 0x11U, 0x22U, 0x33U, 0x44U, 0x55U, 0x66U, 0x77U };

    vector<byte> v5(array5, array5 + 7);

    CarrierDigits* carrierDigits = new CarrierDigits(v5);
    
    pSTNTermination->SetCarrierDigits(carrierDigits);

    choice2->SetChoicePSTNTermination(pSTNTermination);

    terminationList->AddElement(choice2);

    featureRequestRRL->SetTerminationList(terminationList);

    // Encode to ASN.1.

    Octets* octets = featureRequestRRL->Encode();

    if (testPrint)
    {
        cout << endl;
        cout << "Printing ASN.1 encoded value..." << endl;
        cout << *octets;
        cout << endl;
    }

    // Decode from ASN.1 => suffix "After".
    // For all optionals we should check that they are present
    // with the OptionXXXXXXXX() member functions.

    FeatureRequestRRL*
        featureRequestRRLAfter = 
            new FeatureRequestRRL();

    featureRequestRRLAfter->Decode(*octets);

    const FeatureResult& featureResultAfter 
        = featureRequestRRLAfter->GetFeatureResult();

    const GroupInformation& groupInformationAfter
        = featureRequestRRLAfter->GetGroupInformation();

    const TerminationList& terminationListAfter
        = featureRequestRRLAfter->GetTerminationList();

    const CHOICE& choice1After = terminationListAfter.ElementAt(0);

    const CHOICE& choice2After = terminationListAfter.ElementAt(1);

    if (choice1After.ChoiceLocalTermination())
    {
        const LocalTermination& localTerminationAfter = 
            choice1After.GetChoiceLocalTermination();

        const ElectronicSerialNumber& electronicSerialNumberAfter =
            localTerminationAfter.GetElectronicSerialNumber();

        const AlertCode& alertCodeAfter = 
            localTerminationAfter.GetAlertCode();

    }

    if (choice2After.ChoicePSTNTermination())
    {
        const PSTNTermination& pSTNTerminationAfter = 
            choice2After.GetChoicePSTNTermination();

        const DestinationDigits& destinationDigitsAfter =
            pSTNTerminationAfter.GetDestinationDigits();

        const CarrierDigits& carrierDigitsAfter = 
            pSTNTerminationAfter.GetCarrierDigits();

    }

    if (testPrint)
    {
        cout << endl;
        cout << "Printing decoded featureRequestRRL..." << endl;
        cout << *featureRequestRRLAfter;
        cout << endl;
    }

    // Release all the memory.

    delete featureRequestRRLAfter;
    delete featureRequestRRL;
    delete octets;
}

void 
TestSpeedAndMemory()
{
    cout << "Begin performance test (code/decode)..." << endl;

    printf("\n\nEnter number of iterations...\n\n");

    size_t numberOfIterations = 0;

    scanf("%lu", &numberOfIterations);

    time_t tm;
    time(&tm);
    printf("\n\nStart time is %s\n\n", ctime(&tm)); 

    testPrint = false;

    printf("\n\nNumber of iterations is %d\n\n", numberOfIterations);

    for (size_t i = 0; i < numberOfIterations; i++)
    {
       TestLRF();
    }

    testPrint = true;

    time(&tm);
    printf("\n\nEnd time is %s\n\n", ctime(&tm));

    cout << "End performance test (code/decode)..." << endl;
}

//
// Local reference format => no more need for complicated nested scoping
// declaration.
//

void 
TestXmlLRF()
{
    FeatureRequestRRL*
        featureRequestRRL = 
            new FeatureRequestRRL();

    FeatureResult* featureResult = new FeatureResult();

    featureResult->SetSuccessful();

    featureRequestRRL->SetFeatureResult(featureResult);
        
    byte array1[] = { 0xAAU, 0xBBU, 0xCCU, 0xDDU };

    vector<byte> v1(array1, array1 + 4);

    GroupInformation* groupInformation = new GroupInformation(v1);

    featureRequestRRL->SetGroupInformation(groupInformation);

    TerminationList* terminationList = new TerminationList();

    //
    // Local scope typedef still needed because CHOICE is not a Local Reference.
    // (And CHOICE is an anonymous type of SEQUENCE OF.)
    //

    typedef FeatureRequestRRL::
                TerminationList::
                    CHOICE
                        CHOICE;
                
    CHOICE* choice1 = new CHOICE();

    LocalTermination* localTermination = new LocalTermination();

    byte array2[] = { 0x01U, 0x02U, 0x03U, 0x04U };

    vector<byte> v2(array2, array2 + 4);

    ElectronicSerialNumber* electronicSerialNumber = 
        new ElectronicSerialNumber(v2);

    localTermination->
        SetElectronicSerialNumber(
            electronicSerialNumber);

    byte array3[] = { 0xF1U, 0xF2U };

    vector<byte> v3(array3, array3 + 2);

    AlertCode* alertCode = new AlertCode(v3);

    localTermination->
        SetAlertCode(
            alertCode);

    choice1->SetChoiceLocalTermination(localTermination);

    terminationList->AddElement(choice1);

    CHOICE* choice2 = new CHOICE();

    PSTNTermination* pSTNTermination = new PSTNTermination();

    byte array4[] = { 0x10U, 0x20U, 0x30U, 0x40U, 0x50U };

    vector<byte> v4(array4, array4 + 5);

    DestinationDigits* destinationDigits = new DestinationDigits(v4);
    
    pSTNTermination->SetDestinationDigits(destinationDigits);

    byte array5[] = { 0x11U, 0x22U, 0x33U, 0x44U, 0x55U, 0x66U, 0x77U };

    vector<byte> v5(array5, array5 + 7);

    CarrierDigits* carrierDigits = new CarrierDigits(v5);
    
    pSTNTermination->SetCarrierDigits(carrierDigits);

    choice2->SetChoicePSTNTermination(pSTNTermination);

    terminationList->AddElement(choice2);

    featureRequestRRL->SetTerminationList(terminationList);

    // Encode to ASN.1 using XER.

    AsnOptions asnOptions;
    // asnOptions.SetEncodeXmlWithoutSeparators();

    Characters* characters = featureRequestRRL->EncodeToXml(asnOptions);

    if (testPrint)
    {
        cout << endl;
        cout << "Printing ASN.1 encoded value with XER..." << endl;
        cout << *characters;
        cout << endl;
    }

    // Decode from ASN.1 using XER => suffix "After".
    // For all optionals we should check that they are present
    // with the OptionXXXXXXXX() member functions.

    FeatureRequestRRL*
        featureRequestRRLAfter = 
            new FeatureRequestRRL();

    featureRequestRRLAfter->DecodeFromXml(*characters);

    const FeatureResult& featureResultAfter 
        = featureRequestRRLAfter->GetFeatureResult();

    const GroupInformation& groupInformationAfter
        = featureRequestRRLAfter->GetGroupInformation();

    const TerminationList& terminationListAfter
        = featureRequestRRLAfter->GetTerminationList();

    const CHOICE& choice1After = terminationListAfter.ElementAt(0);

    const CHOICE& choice2After = terminationListAfter.ElementAt(1);

    if (choice1After.ChoiceLocalTermination())
    {
        const LocalTermination& localTerminationAfter = 
            choice1After.GetChoiceLocalTermination();

        const ElectronicSerialNumber& electronicSerialNumberAfter =
            localTerminationAfter.GetElectronicSerialNumber();

        const AlertCode& alertCodeAfter = 
            localTerminationAfter.GetAlertCode();

    }

    if (choice2After.ChoicePSTNTermination())
    {
        const PSTNTermination& pSTNTerminationAfter = 
            choice2After.GetChoicePSTNTermination();

        const DestinationDigits& destinationDigitsAfter =
            pSTNTerminationAfter.GetDestinationDigits();

        const CarrierDigits& carrierDigitsAfter = 
            pSTNTerminationAfter.GetCarrierDigits();

    }

    if (testPrint)
    {
        cout << endl;
        cout << "Printing decoded featureRequestRRL..." << endl;
        cout << *featureRequestRRLAfter;
        cout << endl;
    }

    // Release all the memory.

    delete featureRequestRRLAfter;
    delete featureRequestRRL;
    delete characters;
}

void 
TestXmlSpeedAndMemory()
{
    cout << "Begin performance test (XML code/decode)..." << endl;

    printf("\n\nEnter number of iterations...\n\n");

    size_t numberOfIterations = 0;

    scanf("%lu", &numberOfIterations);

    time_t tm;
    time(&tm);
    printf("\n\nStart time is %s\n\n", ctime(&tm)); 

    testPrint = false;

    printf("\n\nNumber of iterations is %d\n\n", numberOfIterations);

    for (size_t i = 0; i < numberOfIterations; i++)
    {
       TestXmlLRF();
    }

    testPrint = true;

    time(&tm);
    printf("\n\nEnd time is %s\n\n", ctime(&tm));

    cout << "End performance test (XML code/decode)..." << endl;
}

#endif // 0