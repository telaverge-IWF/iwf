////////////////////////////////////////////////////////////////////////////////
//
// Tool functions for the testing of GSSMAPPlus
//
////////////////////////////////////////////////////////////////////////////////

#include "tools.h"


// Since the code rely on the standard C++ library,
// the following must be accepted by the compiler.
using namespace std;



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

//////////////////////////////////////////////////////////////////
//
//      Message Encode and Decode general functions
//
///////////////////////////////////////////////////////////////////
void MsgEncode(AsnObject* p, Octets** octets, string& str)
{
    ////////////////////////////////////////////////////////
    // Print ASN.1 value before encoding.
    if (testPrint)
    {
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Printing ASN.1 value before encoding..." << endl;
        cout << endl << *p << endl;
    }

    ostrstream oss;
    oss << *p << '\0';

    str = oss.str();

    ////////////////////////////////////////////////////////
    // Encode using ASN.1 BER.
    Octets* tmpOctets;

    try
    {
        tmpOctets = p->Encode();
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
        cout << endl << *tmpOctets << endl;
    }

    *octets = tmpOctets;
}



void MsgDecode(AsnObject* p, Octets* octets, string& str)
{
    /////////////////////////////
    // Decoded => suffix "Dec".
    /////////////////////////////

    
    // Decoding using ASN.1 BER.
    try
    {
        p->Decode(*octets);
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
    if (testPrint)
    {
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Printing ASN.1 value after decoding..." << endl;
        cout << endl << *p << endl;
    }

    ostrstream oss;
    oss << *p << '\0';

    str = oss.str();
}


void CompareStrings(const string& str1, const string& str2)
{
    if (str1 == str2)
    {
        cout << "Parameters before encoding and after decoding are IDENTICAL." 
             << endl << endl;
    }
    else
    {
        cout << "Parameters before encoding and after decoding are DIFFERENT." 
             << endl << endl;
    }
}

//////////////////////////////////////////////////////////////////
//
//      Initialize Parameters
//
//////////////////////////////////////////////////////////////////
AbsentSubscriberDiagnosticSM* InitializeAbsentSubscriberDiagnosticSM()
{
    AbsentSubscriberDiagnosticSM* ret = 
        new AbsentSubscriberDiagnosticSM((long) 20);

    return ret;
}


Additional_Number* InitializeAdditional_Number()
{
    Additional_Number* ret = new Additional_Number();

    ret->SetChoiceMsc_Number(InitializeMsc_Number());

    return ret;
}


AddressString* InitializeAddressString()
{
    byte arr[] = { 0xAAU, 0xBBU };

    AddressString* as = new AddressString
        (ArrayToVector(arr, ARRAY_SIZE(arr)));

    return as;
}

AddressString* InitializeForwardedToNumber()
{
    byte array[] = { 0x00, 0x01, 0x02, 0x04, 0x05 };

    AddressString* addressString =
        new AddressString(ArrayToVector(array, ARRAY_SIZE(array)));

    return addressString;
}


AgeOfLocationInformation* InitializeAgeOfLocationInformation()
{
    long valparam = 20;
    AgeOfLocationInformation* aoli = new AgeOfLocationInformation(valparam);

    return aoli;
}


AlertingPattern* InitializeAlertingPattern()
{
    byte array[] = { 0x01 };

    AlertingPattern* alertingPattern =
        new AlertingPattern(ArrayToVector(array, ARRAY_SIZE(array)));

    return alertingPattern;
}


AlertReason* InitializeAlertReason()
{
    AlertReason* ret = new AlertReason();

    ret->SetMemoryAvailable();

    return ret;
}


ReadyForSM_Arg::AlertReasonIndicator* InitializeAlertReasonIndicator()
{
    ReadyForSM_Arg::AlertReasonIndicator* ret = 
        new ReadyForSM_Arg::AlertReasonIndicator();

    return ret;
}


GPRSSubscriptionDataWithdraw::AllGPRSData* InitializeAllGprsData()
{
    GPRSSubscriptionDataWithdraw::AllGPRSData* ret = 
        new GPRSSubscriptionDataWithdraw::AllGPRSData();

    return ret;
}


APN* InitializeApn()
{
    byte arr[] = { 0x01, 0x02, 0x03, 0x04 };

    IA5String* apn = new IA5String(ArrayToVector(arr, ARRAY_SIZE(arr)));

    return apn;
}



AuthenticationSet* InitializeAuthenticationSet()
{
    AuthenticationSet* as = new AuthenticationSet();

    as->SetKc(InitializeKc());
    as->SetRand(InitializeRand());
    as->SetSres(InitializeSres());

    return as;
}


AuthenticationSetList* InitializeAuthenticationSetList()
{
    AuthenticationSetList* asl = new AuthenticationSetList();

    // Add 3 elements to the list
    asl->AddElement(InitializeAuthenticationSet());
    asl->AddElement(InitializeAuthenticationSet());
    asl->AddElement(InitializeAuthenticationSet());

    return asl;
}


RegisterSS_Arg::BasicService* InitializeBasicService()
{
    RegisterSS_Arg::BasicService* basicServ = 
        new RegisterSS_Arg::BasicService();
    
    basicServ->SetChoiceBearerService(InitializeBearerService());

    return basicServ;
}


BasicServiceCode* InitializeBasicServiceCode()
{
    BasicServiceCode* bc = new BasicServiceCode();

    bc->SetChoiceBearerService(InitializeBearerService());

    return bc;
}


BasicServiceCriteria* InitializeBasicServiceCriteria()
{
    BasicServiceCriteria* bsc = new BasicServiceCriteria();

    bsc->AddElement(InitializeExt_BasicServiceCode());

    return bsc;
}


BasicServiceGroupList* InitializeBasicServiceGroupList()
{
    BasicServiceGroupList* bl = new BasicServiceGroupList();

    bl->AddElement(InitializeBasicServiceCode());
    bl->AddElement(InitializeBasicServiceCode());

    return bl;
}


BasicServiceList* InitializeBasicServiceList()
{
    BasicServiceList* ret = new BasicServiceList();

    ret->AddElement(InitializeExt_BasicServiceCode());
    ret->AddElement(InitializeExt_BasicServiceCode());
    ret->AddElement(InitializeExt_BasicServiceCode());
    ret->AddElement(InitializeExt_BasicServiceCode());

    return ret;
}


BearerServiceCode* InitializeBearerService()
{
    byte arr[] = { 0xAAU };

    BearerServiceCode* bsc = 
        new BearerServiceCode(ArrayToVector(arr, ARRAY_SIZE(arr)));

    return bsc;
}


BearerServiceList* InitializeBearerServiceList()
{
    BearerServiceList* bl = new BearerServiceList();

    // Insert 2 elements (Type Ext_BearerServiceCode).
    byte arr[] = { 0xBBU };
    Ext_BearerServiceCode* bc1 = 
        new Ext_BearerServiceCode(ArrayToVector(arr, ARRAY_SIZE(arr)));    

    byte array5[] = { 0xBBU };
    Ext_BearerServiceCode* bc2 = 
        new Ext_BearerServiceCode(ArrayToVector(array5, ARRAY_SIZE(array5)));

    bl->AddElement(bc1);
    bl->AddElement(bc2);
	
	return bl;
}


CallDirection* InitializeCallDirection()
{
    byte array[] = { 0x01 };

    CallDirection* cd =
        new CallDirection(ArrayToVector(array, ARRAY_SIZE(array)));

    return cd;
}


CallOutcome* InitializeCallOutcome()
{
    CallOutcome* co = new CallOutcome();

    co->SetBusy();
    
    return co;
}


CallReportData* InitializeCallReportData()
{
    CallReportData* crd = new CallReportData();

    crd->SetMonitoringMode(InitializeMonitoringMode());

    crd->SetCallOutcome(InitializeCallOutcome());

    //extensionContainer

    return crd;
}


VoiceBroadcastData::BroadcastInitEntitlement*
InitializeBroadcastInitEntitlement()
{
    VoiceBroadcastData::BroadcastInitEntitlement* ret = 
        new VoiceBroadcastData::BroadcastInitEntitlement();

    return ret;
}


PrepareHO_Arg::Bss_APDU* InitializeBss_APDU()
{
    return InitializeExternalSignalInfo();
}


CCBS_Feature::B_subscriberNumber* InitializeB_subscriberNumber()
{
    return InitializeAddressString();
}


CCBS_Feature::B_subscriberSubaddress* InitializeB_subscriberSubaddress()
{
    byte arr[] = { 0xAAU, 0xBBU };

    ISDN_SubaddressString* sb = new ISDN_SubaddressString
        (ArrayToVector(arr, ARRAY_SIZE(arr)));

    return sb;
}


CCBS_Data::CallInfo* InitializeCallInfo()
{
    return InitializeExternalSignalInfo();
}


CCBS_Indicators* InitializeCCBS_Indicators()
{
    CCBS_Indicators* ci = new CCBS_Indicators();
    
    ci->SetCcbs_Possible(InitializeCcbs_Possible());

    ci->SetKeepCCBS_CallIndicator(InitializeKeepCCBS_CallIndicator());

    // extensionContainer

    return ci;
}


CCBS_Indicators::Ccbs_Possible* InitializeCcbs_Possible()
{
    CCBS_Indicators::Ccbs_Possible* cp =
        new CCBS_Indicators::Ccbs_Possible();

    return cp;
}


CallReferenceNumber* InitializeCallReferenceNumber()
{
    byte array[] = { 0x01, 0x02, 0x03, 0x04, 0x05 };
    
    CallReferenceNumber* callReferenceNumber =
        new CallReferenceNumber(ArrayToVector(array, ARRAY_SIZE(array)), true);

    return callReferenceNumber;
}


CCBS_SubscriberStatus* InitializeCCBS_SubscriberStatus()
{
    CCBS_SubscriberStatus* ccbs_ss = new CCBS_SubscriberStatus();

    ccbs_ss->SetCcbsNotIdle();

    return ccbs_ss;
}


CallTypeCriteria* InitializeCallTypeCriteria()
{
    CallTypeCriteria* ctc = new CallTypeCriteria();

    ctc->SetForwarded();

    return ctc;
}



SubscriberState::CamelBusy* InitializeCamelBusy()
{
    SubscriberState::CamelBusy* ret = new SubscriberState::CamelBusy();

    return ret;
}



CamelCapabilityHandling* InitializeCamelCapabilityHandling()
{
    long lval = 2;  // must be 1-16

    CamelCapabilityHandling* cch = new CamelCapabilityHandling(lval);

    return cch;
}


CamelInfo* InitializeCamelInfo()
{
    CamelInfo* camelInfo = new CamelInfo();

    bool barray[] = { true, false, true, false, true };
    SupportedCamelPhases* supportedCamelPhases =
        new SupportedCamelPhases(ArrayToVector(barray, ARRAY_SIZE(barray)),
                                               true);
    camelInfo->SetSupportedCamelPhases(supportedCamelPhases);

    CamelInfo::Suppress_T_CSI* suppress_T_CSI =
        new CamelInfo::Suppress_T_CSI();

    return camelInfo;
}


CamelRoutingInfo* InitializeCamelRoutingInfo()
{
    CamelRoutingInfo* cri = new CamelRoutingInfo();

    cri->SetForwardingData(InitializeForwardingData());

    cri->SetGmscCamelSubscriptionInfo(InitializeGmscCamelSubscriptionInfo());

    // extensionContainer

    return cri;
}

DeleteSubscriberDataArg::CamelSubscriptionInfoWithdraw*
InitializeCamelSubscriptionInfoWithdraw()
{
    DeleteSubscriberDataArg::CamelSubscriptionInfoWithdraw*
        ret = new DeleteSubscriberDataArg::CamelSubscriptionInfoWithdraw();

    return ret;
}

CancellationType* InitializeCancellationType()
{
    CancellationType* ct = new CancellationType();

    ct->SetUpdateProcedure();

    return ct;
}

Category *InitializeCategory()
{
    byte array3[] = { 0x66U };

    Category* category = 
        new Category(ArrayToVector(array3, ARRAY_SIZE(array3)));

	return category;
}


SendRoutingInfoArg::Ccbs_Call* InitializeCcbs_Call()
{
    SendRoutingInfoArg::Ccbs_Call* ccbs_Call =
        new SendRoutingInfoArg::Ccbs_Call();

    return ccbs_Call;
}


CCBS_Data* InitializeCcbs_Data()
{
    CCBS_Data* cdata = new CCBS_Data();

    cdata->SetCallInfo(InitializeCallInfo());
    cdata->SetCcbs_Feature(InitializeCcbs_Feature());
    cdata->SetNetworkSignalInfo(InitializeNetworkSignalInfo());
    cdata->SetServiceIndicator(InitializeServiceIndicator());
    cdata->SetTranslatedB_Number(InitializeTranslatedB_Number());

    return cdata;
}


CCBS_Feature* InitializeCcbs_Feature()
{
    CCBS_Feature* cf = new CCBS_Feature();

    cf->SetB_subscriberNumber(InitializeB_subscriberNumber());
    cf->SetB_subscriberSubaddress(InitializeB_subscriberSubaddress());
    cf->SetBasicServiceGroup(InitializeBasicService());
    cf->SetCcbs_Index(InitializeCcbs_Index());

    return cf;
}


CCBS_Index* InitializeCcbs_Index()
{
    CCBS_Index* ci = new CCBS_Index((long) 3);

    return ci;
}


CCBS_Indicators::KeepCCBS_CallIndicator* InitializeKeepCCBS_CallIndicator()
{
    CCBS_Indicators::KeepCCBS_CallIndicator* kcci =
        new CCBS_Indicators::KeepCCBS_CallIndicator();

    return kcci;
}


CellIdFixedLength* InitializeCellIdFixedLength()
{
    // octet string size 7
    byte array[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 };

    CellIdFixedLength* cifl =
        new CellIdFixedLength(ArrayToVector(array, ARRAY_SIZE(array)));

    return cifl;
}


CellIdOrLAI* InitializeCellIdOrLAI()
{
    CellIdOrLAI* cellIdOrLAI = new CellIdOrLAI();

    cellIdOrLAI->SetChoiceCellIdFixedLength(InitializeCellIdFixedLength());

    return cellIdOrLAI;
}


CipheringAlgorithm* InitializeCipheringAlgorithm()
{
    byte array[] = { 0x02 };

    CipheringAlgorithm* ca =
        new CipheringAlgorithm(ArrayToVector(array, ARRAY_SIZE(array)));

    return ca;
}


CODEC_Info* InitializeCODEC_Info()
{
    byte array[] = { 0x01, 0x02, 0x03, 0x04, 0x05,
                     0x06, 0x07, 0x08, 0x09, 0x0a };

    CODEC_Info* codec_info =
        new CODEC_Info(ArrayToVector(array, ARRAY_SIZE(array)));

    return codec_info;
}


GPRSSubscriptionData::CompleteDataListIncluded* 
InitializeCompleteDataListIncluded()
{
    GPRSSubscriptionData::CompleteDataListIncluded* ret = 
        new GPRSSubscriptionData::CompleteDataListIncluded();

    return ret;
}



CUG_CheckInfo* InitializeCUG_CheckInfo()
{
    byte array1[] = { 0x01U, 0x02U, 0x03U, 0x04U };

    CUG_CheckInfo* cug_CheckInfo = new CUG_CheckInfo();

    cug_CheckInfo->SetCug_Interlock(ArrayToVector(array1, ARRAY_SIZE(array1)));

    CUG_CheckInfo::Cug_OutgoingAccess* cugOutgoingAccess = 
        new CUG_CheckInfo::Cug_OutgoingAccess();

    cug_CheckInfo->SetCug_OutgoingAccess(cugOutgoingAccess);

    return cug_CheckInfo;
}


CUG_Interlock* InitializeCUG_Interlock()
{
    // octet string size 4
    byte array[] = { 0x11, 0x22, 0x33, 0x44 };

    CUG_Interlock* cug_interlock =
        new CUG_Interlock(ArrayToVector(array, ARRAY_SIZE(array)));

    return cug_interlock;
}


SendRoutingInfoRes::CugSubscriptionFlag* InitializeCugSubscriptionFlag()
{
    SendRoutingInfoRes::CugSubscriptionFlag* cug_sf =
        new SendRoutingInfoRes::CugSubscriptionFlag();

    return cug_sf;
}


DefaultCallHandling* InitializeDefaultCallHandling()
{
    DefaultCallHandling* dch = new DefaultCallHandling();
    
    dch->SetReleaseCall();

    return dch;
}


ReportSM_DeliveryStatusArg::DeliveryOutcomeIndicator*
InitializeDeliveryOutcomeIndicator()
{
    ReportSM_DeliveryStatusArg::DeliveryOutcomeIndicator* ret = 
        new ReportSM_DeliveryStatusArg::DeliveryOutcomeIndicator();

    return ret;
}


DestinationNumberCriteria* InitializeDestinationNumberCriteria()
{
    DestinationNumberCriteria* dnc = new DestinationNumberCriteria();
    
    dnc->SetMatchType(InitializeMatchType());

    DestinationNumberList* dnlist = new DestinationNumberList();

    dnlist->AddElement(InitializeISDN_AddressString());

    return dnc;
}


SS_Data::DefaultPriority* InitializeDefaultPriority()
{
    return InitializeEmlpp_Priority();
}

EMLPP_Priority* InitializeEmlpp_Priority()
{
    EMLPP_Priority* ep = new EMLPP_Priority((long) 3);

    return ep;
}


EventReportData* InitializeEventReportData()
{
    EventReportData* erd = new EventReportData();

    erd->SetCcbs_SubscriberStatus(InitializeCCBS_SubscriberStatus());

    return erd;
}


Ext_BasicServiceCode* InitializeExt_BasicServiceCode()
{
    Ext_BasicServiceCode* ext_bsc = new Ext_BasicServiceCode();

    ext_bsc->SetChoiceExt_BearerService(InitializeExt_BearerServiceCode());

    return ext_bsc;
}


Ext_BasicServiceCode* InitializeBasicServiceGroup()
{
    byte array1[] = { 0x01, 0x02, 0x03,0x04, 0x05 };
    byte array2[] = { 0x01 };

    Ext_BasicServiceCode* basicServiceGroup =
        new Ext_BasicServiceCode();

    Ext_BearerServiceCode* extBearerServiceCode =
        new Ext_BearerServiceCode(ArrayToVector(array1, ARRAY_SIZE(array1)));

    basicServiceGroup->SetChoiceExt_BearerService(extBearerServiceCode);
    
    Ext_TeleserviceCode* extTeleserviceCode =
        new Ext_TeleserviceCode(ArrayToVector(array2, ARRAY_SIZE(array2)));
    basicServiceGroup->SetChoiceExt_Teleservice(extTeleserviceCode);

    return basicServiceGroup;
}


Ext_BearerServiceCode* InitializeExt_BearerServiceCode()
{
    byte array[] = { 0x44U };

    Ext_BearerServiceCode* ext_BearerServiceCode =
        new Ext_BearerServiceCode(ArrayToVector(array, ARRAY_SIZE(array)));

    return ext_BearerServiceCode;
}


ExtendedRoutingInfo* InitializeExtendedRoutingInfo()
{
    ExtendedRoutingInfo* eri = new ExtendedRoutingInfo();

    eri->SetChoiceCamelRoutingInfo(InitializeCamelRoutingInfo());

    return eri;
}


ExtensionContainer* InitializeExtensionContainer()
{
    ExtensionContainer* extContainer = 
        new ExtensionContainer();

    return extContainer;
}


ExternalSignalInfo* InitializeExternalSignalInfo()
{
    ExternalSignalInfo* esi = new ExternalSignalInfo();

    esi->SetExtensionContainer(InitializeExtensionContainer());
    esi->SetProtocolId(InitializeProtocolId());
    esi->SetSignalInfo(InitializeSignalInfo());

    return esi;
}


ExternalSignalInfo* InitializeGsm_BearerCapability()
{
    return InitializeExternalSignalInfo();
}


SendRoutingInfoArg::NetworkSignalInfo* InitializeNetworkSignalInfo2()
{
    return InitializeExternalSignalInfo();
}


Ext_SS_Data* InitializeExt_SS_Data()
{
    Ext_SS_Data* sS_Data = new Ext_SS_Data();

	sS_Data->SetSs_Code(InitializeSS_Code());
	sS_Data->SetSs_Status(InitializeExt_SS_Status());
    sS_Data->SetSs_SubscriptionOption(InitializeSS_SubscriptionOption());

	return sS_Data;
}



Ext_SS_Info* InitializeExt_SS_Info_Choice_CUG_Info()
{
    Ext_SS_Info* sS_Info2 = new Ext_SS_Info();

    // element choice is cug-Info.

    CUG_Info* cUG_Info = new CUG_Info();

    CUG_SubscriptionList* cUG_SubscriptionList = new CUG_SubscriptionList();

    // Insert 2 elements (type CUG_Subscription).

    CUG_Subscription* cUG_Subscription1 = new CUG_Subscription();

    CUG_Index* cUG_Index1 = new CUG_Index(1999l);

    cUG_Subscription1->SetCug_Index(cUG_Index1);

    byte array12[] = { 0x11U, 0x22U, 0x33U, 0x44U };

    CUG_Interlock* cUG_Interlock1 = 
        new CUG_Interlock(ArrayToVector(array12, ARRAY_SIZE(array12)));

    cUG_Subscription1->SetCug_Interlock(cUG_Interlock1);

    IntraCUG_Options* intraCUG_Options1 = new IntraCUG_Options();

    intraCUG_Options1->SetNoCUG_Restrictions();

    cUG_Subscription1->SetIntraCUG_Options(intraCUG_Options1);

    cUG_SubscriptionList->AddElement(cUG_Subscription1);

    CUG_Subscription* cUG_Subscription2 = new CUG_Subscription();

    CUG_Index* cUG_Index2 = new CUG_Index(2001l);

    cUG_Subscription2->SetCug_Index(cUG_Index2);

    byte array13[] = { 0x44U, 0x33U, 0x22U, 0x11U };

    CUG_Interlock* cUG_Interlock2 = 
        new CUG_Interlock(ArrayToVector(array13, ARRAY_SIZE(array13)));

    cUG_Subscription2->SetCug_Interlock(cUG_Interlock2);

    IntraCUG_Options* intraCUG_Options2 = new IntraCUG_Options();

    intraCUG_Options2->SetNoCUG_Restrictions();

    cUG_Subscription2->SetIntraCUG_Options(intraCUG_Options2);

    cUG_SubscriptionList->AddElement(cUG_Subscription2);

    cUG_Info->SetCug_SubscriptionList(cUG_SubscriptionList);

	
	CUG_FeatureList *cUG_FeatureList = new CUG_FeatureList();

	// Insert one element (type CUG_Feature)

	CUG_Feature *cUG_Feature = new CUG_Feature();

	Ext_BasicServiceCode *basicServiceCodeInCUGFeature = new 
		Ext_BasicServiceCode();

	long iCUGIndex = 255;

	CUG_Index *cUG_Index100 = new CUG_Index(iCUGIndex);

	byte array600[] = { 0x55U };

	InterCUG_Restrictions *interCUG_Restrictions = 
		new InterCUG_Restrictions(ArrayToVector(array600, ARRAY_SIZE(array600)));


    byte array510[] = { 0x44U };

    Ext_BearerServiceCode* bearerServiceCode100 = 
        new Ext_BearerServiceCode(ArrayToVector(array510, ARRAY_SIZE(array510)));

    basicServiceCodeInCUGFeature->SetChoiceExt_BearerService(bearerServiceCode100);


	cUG_Feature->SetBasicService(basicServiceCodeInCUGFeature);

	cUG_Feature->SetPreferentialCUG_Indicator(cUG_Index100);

	cUG_Feature->SetInterCUG_Restrictions(interCUG_Restrictions);
	

	cUG_FeatureList->AddElement(cUG_Feature);

	cUG_Info->SetCug_FeatureList(cUG_FeatureList);

    sS_Info2->SetChoiceCug_Info(cUG_Info);

	return sS_Info2;
}


Ext_SS_Info* InitializeExt_SS_Info_Choice_Ext_ForwInfo()
{
    Ext_SS_Info* sS_Info1 = new Ext_SS_Info();

    //  choice is forwardingInfo.

    Ext_ForwInfo* forwardingInfo = new Ext_ForwInfo();

    byte array9[] = { 0x33U };

    SS_Code* sS_Code = new SS_Code(ArrayToVector(array9, ARRAY_SIZE(array9)));

    forwardingInfo->SetSs_Code(sS_Code);

    Ext_ForwFeatureList* forwardingFeatureList = 
        new Ext_ForwFeatureList();

    // Insert 1 element (type Ext_ForwFeature).

    Ext_ForwFeature* forwardingFeature = new Ext_ForwFeature();

    Ext_BasicServiceCode* basicServiceCode = new Ext_BasicServiceCode();

    byte array10[] = { 0x44U };

    Ext_BearerServiceCode* bearerServiceCode = 
        new Ext_BearerServiceCode(ArrayToVector(array10, ARRAY_SIZE(array10)));

    basicServiceCode->SetChoiceExt_BearerService(bearerServiceCode);

    forwardingFeature->SetBasicService(basicServiceCode);

	byte array100[] = { 0x01U };

	Ext_SS_Status *ss_Status  = 
		new Ext_SS_Status(ArrayToVector(array100, ARRAY_SIZE(array100)));

	forwardingFeature->SetSs_Status(ss_Status);

    byte array101[] = { 0x11U, 0x22U, 0x33U, 0x44U, 0x55U, 0x66U, 0x77U, 0x88U };

    ISDN_AddressString* iSDN_AddressString1 = 
        new ISDN_AddressString(ArrayToVector(array101, ARRAY_SIZE(array101)));

    forwardingFeature->SetForwardedToNumber(iSDN_AddressString1);

    byte array11[] = { 0x01U, 0x02U, 0x03U, 0x04U,
                       0x05U, 0x06U, 0x07U, 0x08U };

    ISDN_SubaddressString* iSDN_SubaddressString2 = 
        new ISDN_SubaddressString(ArrayToVector(array11, ARRAY_SIZE(array11)));

    forwardingFeature->SetForwardedToSubaddress(iSDN_SubaddressString2);

	byte array102[] = { 0x01U };

	Ext_ForwOptions *forwOptions  = 
		new Ext_ForwOptions(ArrayToVector(array102, ARRAY_SIZE(array102)));

	forwardingFeature->SetForwardingOptions(forwOptions);

	long iNoRepCondTime = 5;

	Ext_NoRepCondTime *noRepCondTime = new Ext_NoRepCondTime(iNoRepCondTime);

	forwardingFeature->SetNoReplyConditionTime(noRepCondTime);

    forwardingFeatureList->AddElement(forwardingFeature);

    forwardingInfo->SetForwardingFeatureList(forwardingFeatureList);

    sS_Info1->SetChoiceForwardingInfo(forwardingInfo);
	
	return sS_Info1;
}


Ext_SS_Info* InitializeExt_SS_Info_Choice_Ext_SS_Data()
{
    Ext_SS_Info* sS_Info3 = new Ext_SS_Info();

    // element choice is Ext-ss-Data.
    sS_Info3->SetChoiceSs_Data(InitializeExt_SS_Data());

	return sS_Info3;
}


Ext_SS_Status *InitializeExt_SS_Status()
{
	byte arr[] = { 0x01U };

	Ext_SS_Status *ss  = 
		new Ext_SS_Status(ArrayToVector(arr, ARRAY_SIZE(arr)));
	
	return ss;
}


Ext_SS_InfoList* InitializeExt_SS_InfoList()
{
    Ext_SS_InfoList* sS_InfoList = new Ext_SS_InfoList();

    // Insert 3 elements (type Ext_SS_Info).

    sS_InfoList->AddElement(InitializeExt_SS_Info_Choice_Ext_ForwInfo());
    sS_InfoList->AddElement(InitializeExt_SS_Info_Choice_CUG_Info());
    sS_InfoList->AddElement(InitializeExt_SS_Info_Choice_Ext_SS_Data());
	
	return sS_InfoList;
}


Ext_TeleserviceCode* InitializeExt_TeleserviceCode()
{
    byte array[] = { 0x00 };

    Ext_TeleserviceCode* ext_tc =
        new Ext_TeleserviceCode(ArrayToVector(array, ARRAY_SIZE(array)));

    return ext_tc;
}


ForwardGroupCallSignallingArg::UplinkRejectCommand*
InitializeFGCSAUplinkRejectCommand()
{
    ForwardGroupCallSignallingArg::UplinkRejectCommand* urc =
        new ForwardGroupCallSignallingArg::UplinkRejectCommand();

    return urc;
}


ForwardGroupCallSignallingArg::UplinkReleaseCommand*
InitializeFGCSAUplinkReleaseCommand()
{
    ForwardGroupCallSignallingArg::UplinkReleaseCommand* urc =
        new ForwardGroupCallSignallingArg::UplinkReleaseCommand();

    return urc;
}


ForwardGroupCallSignallingArg::UplinkReleaseIndication*
InitializeFGCSAUplinkReleaseIndication()
{
    ForwardGroupCallSignallingArg::UplinkReleaseIndication* uri =
        new ForwardGroupCallSignallingArg::UplinkReleaseIndication();

    return uri;
}


ForwardGroupCallSignallingArg::UplinkRequestAck*
InitializeFGCSAUplinkRequestAck()
{
    ForwardGroupCallSignallingArg::UplinkRequestAck* ura =
        new ForwardGroupCallSignallingArg::UplinkRequestAck();

    return ura;
}


ForwardGroupCallSignallingArg::UplinkSeizedCommand*
InitializeFGCSAUplinkSeizedCommand()
{
    ForwardGroupCallSignallingArg::UplinkSeizedCommand* usc =
        new ForwardGroupCallSignallingArg::UplinkSeizedCommand();

    return usc;
}


ForwardingData* InitializeForwardingData()
{
    ForwardingData* forwardingData = new ForwardingData();

    forwardingData->SetForwardedToNumber(InitializeForwardedToNumber());

    forwardingData->SetForwardedToSubaddress
        (InitializeForwardedToSubaddress());

    forwardingData->SetForwardingOptions(InitializeForwardingOptions());

    // extensionContainer not used

    return forwardingData;
}


ForwardingOptions* InitializeForwardingOptions()
{
    byte array[] = { 0x01 };

    ForwardingOptions* forwardOptions =
        new ForwardingOptions(ArrayToVector(array, ARRAY_SIZE(array)));

    return forwardOptions;
}


ForwardingReason* InitializeForwardingReason()
{
    ForwardingReason* forwardingReason = new ForwardingReason();
    forwardingReason->SetBusy();

    return forwardingReason;
}


GroupKeyNumber* InitializeGroupKeyNumber()
{
    long num = 11;

    GroupKeyNumber* gkn = new GroupKeyNumber(num);

    return gkn;
}


RegisterSS_Arg::ForwardedToNumber* IntializeForwardedToNumber()
{
    byte arr[] = { 0x01U, 0x02U, 0x03U, 0x04U }; 

    RegisterSS_Arg::ForwardedToNumber* ftn = 
        new RegisterSS_Arg::ForwardedToNumber(ArrayToVector
                                              (arr, ARRAY_SIZE(arr)));

    return ftn;
}


RegisterSS_Arg::ForwardedToSubaddress* IntializeForwardedToSubaddress()
{
    byte arr[] = { 0x01U, 0x02U, 0x03U, 0x04U }; 

    RegisterSS_Arg::ForwardedToSubaddress* fts = 
        new RegisterSS_Arg::ForwardedToSubaddress(ArrayToVector
                                              (arr, ARRAY_SIZE(arr)));

    return fts;
}


PurgeMS_Res::FreezeP_TMSI* InitializeFreezeP_TMSI()
{
    PurgeMS_Res::FreezeP_TMSI* ft = new PurgeMS_Res::FreezeP_TMSI();

    return ft;
}


PurgeMS_Res::FreezeTMSI* InitializeFreezeTMSI()
{
    PurgeMS_Res::FreezeTMSI* ft = new PurgeMS_Res::FreezeTMSI();

    return ft;
}


GeographicalInformation* InitializeGeographicalInformation()
{
    // octet string size 8
    byte array[] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };

    GeographicalInformation* gi =
        new GeographicalInformation(ArrayToVector(array, ARRAY_SIZE(array)));

    return gi;
}


SendRoutingInfoForGprsArg::Ggsn_Address* InitializeGgsn_Address()
{
    return InitializeGSN_Address();
}


FailureReportArg::Ggsn_Number* InitializeGgsn_Number()
{
    return InitializeISDN_AddressString();
}



GlobalCellId* InitializeGlobalCellId()
{
    byte arr[] = { 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U }; 

    GlobalCellId* gid = new GlobalCellId(ArrayToVector(arr, ARRAY_SIZE(arr)));

    return gid;
}


GPRSDataList* InitializeGprsDataList()
{
    GPRSDataList* gl = new GPRSDataList();

    gl->AddElement(InitializePDP_Context());
    gl->AddElement(InitializePDP_Context());
    gl->AddElement(InitializePDP_Context());

    return gl;
}



LocationInfoWithLMSI::GprsNodeIndicator* InitializeGprsNodeIndicator()
{
    LocationInfoWithLMSI::GprsNodeIndicator* ret = 
        new LocationInfoWithLMSI::GprsNodeIndicator();

    return ret;
}



GPRSSubscriptionData* InitializeGprsSubscriptionData()
{
    GPRSSubscriptionData* gdata = new GPRSSubscriptionData();

    gdata->SetExtensionContainer(InitializeExtensionContainer());
    gdata->SetCompleteDataListIncluded(InitializeCompleteDataListIncluded());
    gdata->SetGprsDataList(InitializeGprsDataList());

    return gdata;
}



GroupId* InitializeGroupId()
{
    byte arr[] = { 0x01U, 0x02U, 0x03U }; 

    GroupId* ret = new GroupId(ArrayToVector(arr, ARRAY_SIZE(arr)));

    return ret;
}


GmscCamelSubscriptionInfo* InitializeGmscCamelSubscriptionInfo()
{
    GmscCamelSubscriptionInfo* gcsi = new GmscCamelSubscriptionInfo();

    gcsi->SetT_CSI(InitializeT_CSI());
    gcsi->SetO_CSI(InitializeO_CSI());

    return gcsi;
}


GPRSSubscriptionDataWithdraw* InitializeGprsSubscriptionDataWithdraw()
{
    GPRSSubscriptionDataWithdraw* ret = new GPRSSubscriptionDataWithdraw();

    ret->SetChoiceAllGPRSData(InitializeAllGprsData());

    return ret;
}



RoutingInfoForSM_Arg::GprsSupportIndicator*
InitializeGprsSupportIndicator()
{
    RoutingInfoForSM_Arg::GprsSupportIndicator* ret = 
        new RoutingInfoForSM_Arg::GprsSupportIndicator();

    return ret;
}



SS_CamelData::GsmSCF_Address* InitializeGSMSCF_Address()
{
    return InitializeISDN_AddressString();
}

GSN_Address* InitializeGSN_Address()
{
    byte arr[] = { 0x01U, 0x02U, 0x03U, 0x04U }; 

    GSN_Address* ga = new GSN_Address(ArrayToVector(arr, ARRAY_SIZE(arr)));

    return ga;
}


PrepareHO_Res::HandoverNumber* InitializeHandoverNumber()
{
    return InitializeISDN_AddressString();
}


HLR_Id* InitializeHLR_Id()
{
    return InitializeIMSI();
}


HLR_List* InitializeHLR_List()
{
    HLR_List* ret = new HLR_List();

    ret->AddElement(InitializeHLR_Id());
    ret->AddElement(InitializeHLR_Id());
    ret->AddElement(InitializeHLR_Id());

    return ret;
}



UpdateGprsLocationRes::Hlr_Number* InitializeHlr_Number()
{
    return InitializeISDN_AddressString();
}

PrepareHO_Arg::Ho_NumberNotRequired* InitializeHo_NumberNotRequired()
{
    PrepareHO_Arg::Ho_NumberNotRequired* hr = 
        new PrepareHO_Arg::Ho_NumberNotRequired();

    return hr;
}


Identity* InitializeIdentity()
{
    Identity* identity = new Identity();
    
    byte array1[] = { 0x01U, 0x02U, 0x03U, 0x04U }; 
    IMSI* imsi = new IMSI(ArrayToVector(array1, ARRAY_SIZE(array1)));

    identity->SetChoiceImsi(imsi);

    return identity;
}


IMSI *InitializeIMSI()
{
    byte array1[] = { 0x01U, 0x02U, 0x03U, 0x04U }; 

    IMSI* imsi = new IMSI(ArrayToVector(array1, ARRAY_SIZE(array1)));

	
	return imsi;
}


InterrogationType* InitializeInterrogationType()
{
    InterrogationType* interrogationType = new InterrogationType();
    interrogationType->SetBasicCall();

    return interrogationType;
}


ISDN_AddressString* InitializeGsmSCF_Address()
{
    return InitializeISDN_AddressString();
}

ISDN_AddressString* InitializeISDN_AddressString()
{
    return InitializeAddressString();
}


ISDN_AddressString* InitializeMsc_Number()
{
    return InitializeISDN_AddressString();
}


ISDN_AddressString* InitializeRoamingNumber()
{
    return InitializeISDN_AddressString();
}


ISDN_SubaddressString* InitializeForwardedToSubaddress()
{
    byte array[] = { 0x11, 0x22, 0x33, 0x44, 0x55 };

    ISDN_SubaddressString* isdnSubaddressString = 
        new ISDN_SubaddressString(ArrayToVector(array, ARRAY_SIZE(array)));

    return isdnSubaddressString;
}


ISDN_AddressString* InitializeVmsc_Address()
{
    return InitializeISDN_AddressString();
}


Kc* InitializeKc()
{
    byte arr[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };

    Kc* k = new Kc(ArrayToVector(arr, ARRAY_SIZE(arr)));

    return k;
}

LMSI* InitializeLMSI()
{
    byte arr[] = { 0x11, 0x22, 0x33, 0x44 };

    LMSI* ret = new LMSI(ArrayToVector(arr, ARRAY_SIZE(arr)));

    return ret;
}


RequestedInfo::LocationInformation* InitializeLocationInfo()
{
    RequestedInfo::LocationInformation* ret = 
        new RequestedInfo::LocationInformation();

    return ret;
}


LocationInformation* InitializeLocationInformation()
{
    LocationInformation* li = new LocationInformation();

    li->SetAgeOfLocationInformation(InitializeAgeOfLocationInformation());

    li->SetGeographicalInformation(InitializeGeographicalInformation());

    li->SetVlr_number(InitializeISDN_AddressString());

    li->SetLocationNumber(InitializeLocationNumber());

    li->SetCellIdOrLAI(InitializeCellIdOrLAI());

    // extensionContainer

    return li;
}


LocationInfoWithLMSI* InitializeLocationInfoWithLMSI()
{
    LocationInfoWithLMSI* ret = new LocationInfoWithLMSI();

    ret->SetAdditional_Number(InitializeAdditional_Number());
    ret->SetExtensionContainer(InitializeExtensionContainer());
    ret->SetGprsNodeIndicator(InitializeGprsNodeIndicator());
    ret->SetLmsi(InitializeLMSI());
    ret->SetNetworkNode_Number(InitializeNetworkNode_Number());

    return ret;
}


LocationNumber* InitializeLocationNumber()
{
    byte array[] = { 0x10, 0x20, 0x30, 0x40 };

    LocationNumber* ln =
        new LocationNumber(ArrayToVector(array, ARRAY_SIZE(array)));

    return ln;
}


MatchType* InitializeMatchType()
{
    MatchType* mt = new MatchType();

    mt->SetEnabling();

    return mt;
}


MonitoringMode* InitializeMonitoringMode()
{
    MonitoringMode* mm = new MonitoringMode();

    mm->SetA_side();

    return mm;
}


MT_ForwardSM_Arg::MoreMessagesToSend* InitializeMoreMessagesToSend()
{
    MT_ForwardSM_Arg::MoreMessagesToSend* ret = 
        new MT_ForwardSM_Arg::MoreMessagesToSend();

    return ret;
}

MW_Status* InitializeMW_Status()
{
    bool arr[] = { false, false, false, false, false, false  };

    MW_Status* ret = new MW_Status(ArrayToVector(arr, ARRAY_SIZE(arr)));

    ret->SetMcef_Set();
    //ret->SetMnrf_Set();

    return ret;
}


LocationInfoWithLMSI::NetworkNode_Number* InitializeNetworkNode_Number()
{
    return InitializeISDN_AddressString();
}


ProvideRoamingNumberArg::Ccbs_Call* InitializePRNACcbs_Call()
{
    ProvideRoamingNumberArg::Ccbs_Call* ccbs_call =
        new ProvideRoamingNumberArg::Ccbs_Call();

    return ccbs_call;
}


ProvideRoamingNumberArg::Or_Interrogation* InitializePRNAOr_Interrogation()
{
    ProvideRoamingNumberArg::Or_Interrogation* orInterrogation =
        new ProvideRoamingNumberArg::Or_Interrogation();

    return orInterrogation;
}


SendRoutingInfoForGprsRes::MobileNotReachableReason*
InitializeMobileNotReachableReason()
{
    return InitializeAbsentSubscriberDiagnosticSM();
}


InsertSubscriberDataArg::Msisdn* InitializeMsisdn()
{
    return InitializeISDN_AddressString();
}


ReportingState* InitializeReportingState()
{
    ReportingState* rs = new ReportingState();

    rs->SetStartMonitoring();

    return rs;
}


RestoreDataRes::MsNotReachable* InitializeMsNotReachable()
{
    RestoreDataRes::MsNotReachable* ret = 
        new RestoreDataRes::MsNotReachable();

    return ret;
}



CCBS_Data::NetworkSignalInfo* InitializeNetworkSignalInfo()
{
    return InitializeExternalSignalInfo();    
}

NAEA_CIC* InitializeNaea_PreferredCIC()
{
    byte arr[] = { 0x11U, 0x22U, 0x33U };

    NAEA_CIC* ncic = new NAEA_CIC(ArrayToVector(arr, ARRAY_SIZE(arr)));

    return ncic;
}


NAEA_PreferredCI* InitializeNaea_PreferredCI()
{
    NAEA_PreferredCI* ret = new NAEA_PreferredCI();

    ret->SetExtensionContainer(InitializeExtensionContainer());
    ret->SetNaea_PreferredCIC(InitializeNaea_PreferredCIC());

    return ret;
}


NetworkAccessMode* InitializeNetworkAccessMode()
{
    NetworkAccessMode* ret = new NetworkAccessMode();

    ret->SetOnlyMSC();

    return ret;
}


NoReplyConditionTime* InitializeNoReplyConditionTime()
{
    byte arr[] = { 0x11U, 0x22U, 0x33U, 0x44U, 0x55U };

    NoReplyConditionTime* nrct = new NoReplyConditionTime();

    return nrct;
}


NumberOfForwarding* InitializeNumberOfForwarding()
{
    byte num = { 0x01 };

    NumberOfForwarding* numOfForwarding = new NumberOfForwarding(num, true);

    return numOfForwarding;
}


O_BcsmCamelTDP_Criteria* InitializeO_BcsmCamelTDP_Criteria()
{
    O_BcsmCamelTDP_Criteria* tdpc = new O_BcsmCamelTDP_Criteria();
    
    tdpc->SetDestinationNumberCriteria(InitializeDestinationNumberCriteria());

    tdpc->SetBasicServiceCriteria(InitializeBasicServiceCriteria());

    tdpc->SetCallTypeCriteria(InitializeCallTypeCriteria());

    return tdpc;
}


O_BcsmCamelTDPDataList* InitializeO_BcsmCamelTDPDataList()
{
    O_BcsmCamelTDPDataList* camellist = new O_BcsmCamelTDPDataList();
    
    // create list element 1 for addition
    O_BcsmCamelTDPData* cameldata1 = new O_BcsmCamelTDPData();

    cameldata1->SetO_BcsmTriggerDetectionPoint
        (InitializeO_BcsmTriggerDetectionPoint());

    cameldata1->SetServiceKey(InitializeServiceKey());

    cameldata1->SetGsmSCF_Address(InitializeGsmSCF_Address());

    cameldata1->SetDefaultCallHandling(InitializeDefaultCallHandling());

    cameldata1->SetO_BcsmCamelTDP_Criteria(InitializeO_BcsmCamelTDP_Criteria());

    camellist->AddElement(cameldata1);

    // extensionContainer not included

    return camellist;
}


O_BcsmTriggerDetectionPoint* InitializeO_BcsmTriggerDetectionPoint()
{
    O_BcsmTriggerDetectionPoint* tdp = new O_BcsmTriggerDetectionPoint();
    
    tdp->SetCollectedInfo();

    return tdp;
}


O_CSI* InitializeO_CSI()
{
    O_CSI* o_csi = new O_CSI();

    o_csi->SetO_BcsmCamelTDPDataList(InitializeO_BcsmCamelTDPDataList());

    o_csi->SetCamelCapabilityHandling(InitializeCamelCapabilityHandling());

    // extensionContainer not used

    return o_csi;
}


ODB_Data* InitializeODB_Data()
{
    ODB_Data* ret = new ODB_Data();

    ret->SetExtensionContainer(InitializeExtensionContainer());
    ret->SetOdb_GeneralData(InitializeODB_GeneralData());
    ret->SetOdb_HPLMN_Data(InitializeODB_HPLMN_Data());

    return ret;
}


ODB_GeneralData *InitializeODB_GeneralData()
{
    bool arr[] = { true, false, true, false, true,
                   false, true, false, true, false,
                   true, false, true, false, true,
                   false, true, false, true, false,
                   true, false, true, false, true };

    ODB_GeneralData* ret = 
        new ODB_GeneralData(ArrayToVector(arr, ARRAY_SIZE(arr)));

	return ret;
}

ODB_HPLMN_Data* InitializeODB_HPLMN_Data()
{
    bool arr[] = { false, true, false, true };

    ODB_HPLMN_Data* ret = 
        new ODB_HPLMN_Data(ArrayToVector(arr, ARRAY_SIZE(arr)));

    return ret;
}


ActivateTraceModeArg::Omc_Id* InitializeOmc_Id()
{
    byte array1[] = { 0x01U, 0x02U, 0x03U, 0x04U }; 

    ActivateTraceModeArg::Omc_Id* omcId = 
        new ActivateTraceModeArg::Omc_Id
        (ArrayToVector(array1, ARRAY_SIZE(array1)));

    return omcId;
}


OR_Phase* InitializeOrCapability()
{
    long integer = 11;

    OR_Phase* orPhase = new OR_Phase(integer, true);
    
    return orPhase;
}



SendRoutingInfoArg::Or_Interrogation* InitializeOr_Interrogation()
{
    SendRoutingInfoArg::Or_Interrogation* orInterrogation =
        new SendRoutingInfoArg::Or_Interrogation();

    return orInterrogation;
}


PDP_Address* InitializePdp_Address()
{
    byte arr[] = { 0x01, 0x02, 0x03, 0x04 };

    PDP_Address* pa = new PDP_Address(ArrayToVector(arr, ARRAY_SIZE(arr)));

    return pa;
}



PDP_Context* InitializePDP_Context()
{
    PDP_Context* pc = new PDP_Context();

    pc->SetApn(InitializeApn());
    pc->SetExtensionContainer(InitializeExtensionContainer());
    pc->SetPdp_Address(InitializePdp_Address());
    pc->SetPdp_ContextId(InitializePdp_ContextId());
    pc->SetPdp_Type(InitializePdp_Type());
    pc->SetQos_Subscribed(InitializeQos_Subscribed());
    pc->SetVplmnAddressAllowed(InitializeVplmnAddressAllowed());

    return pc;
}


ContextId* InitializePdp_ContextId()
{
    ContextId* cid = new ContextId((long) 12);

    return cid;
}



PDP_Type* InitializePdp_Type()
{
    byte arr[] = { 0x01, 0x02 };

    PDP_Type* pt = new PDP_Type(ArrayToVector(arr, ARRAY_SIZE(arr)));

    return pt;
}


PrepareGroupCallArg::UplinkFree* InitializeUplinkFree()
{
    PrepareGroupCallArg::UplinkFree* uf =
        new PrepareGroupCallArg::UplinkFree();

    return uf;
}


ProcessGroupCallSignallingArg::ReleaseGroupCall*
InitializePGCSAReleaseGroupCall()
{
    ProcessGroupCallSignallingArg::ReleaseGroupCall* rgc =
        new ProcessGroupCallSignallingArg::ReleaseGroupCall();

    return rgc;
}


ProcessGroupCallSignallingArg::UplinkReleaseIndication*
InitializePGCSAUplinkReleaseIndication()
{
    ProcessGroupCallSignallingArg::UplinkReleaseIndication* uri =
        new ProcessGroupCallSignallingArg::UplinkReleaseIndication();

    return uri;
}


ProcessGroupCallSignallingArg::UplinkRequest*
InitializePGCSAUplinkRequest()
{
    ProcessGroupCallSignallingArg::UplinkRequest* ur =
        new ProcessGroupCallSignallingArg::UplinkRequest();

    return ur;
}


ProtocolId* InitializeProtocolId()
{
    ProtocolId* pid = new ProtocolId();

    pid->SetGsm_0806();

    return pid;
}



InsertSubscriberDataArg::ProvisionedSS* InitializeProvisionedSS()
{
    return InitializeExt_SS_InfoList();
}


QoS_Subscribed* InitializeQos_Subscribed()
{
    byte arr[] = { 0x01, 0x02, 0x03 };

    QoS_Subscribed* qs = 
        new QoS_Subscribed(ArrayToVector(arr, ARRAY_SIZE(arr)));

    return qs;
}


RAND* InitializeRand()
{
    byte arr[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 
                   0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10 };

    RAND* r = new RAND(ArrayToVector(arr, ARRAY_SIZE(arr)));

    return r;
}


InsertSubscriberDataArg::RoamingRestrictedInSgsnDueToUnsupportedFeature*
InitializeRoamingRestrictedInSgsnDueToUnsupportedFeature()
{
    InsertSubscriberDataArg::RoamingRestrictedInSgsnDueToUnsupportedFeature*
        ret = new InsertSubscriberDataArg::
        RoamingRestrictedInSgsnDueToUnsupportedFeature();

    return ret;
}


DeleteSubscriberDataArg::RoamingRestrictedInSgsnDueToUnsuppportedFeature*
InitializeRoamingRestrictedInSgsnDueToUnsuppportedFeature()
{
    DeleteSubscriberDataArg::RoamingRestrictedInSgsnDueToUnsuppportedFeature*
        ret = new DeleteSubscriberDataArg::
        RoamingRestrictedInSgsnDueToUnsuppportedFeature();

    return ret;
}




InsertSubscriberDataArg::RoamingRestrictionDueToUnsupportedFeature*
InitializeRoamingRestrictionDueToUnsupportedFeature()
{
    InsertSubscriberDataArg::RoamingRestrictionDueToUnsupportedFeature* 
        ret = new InsertSubscriberDataArg::
        RoamingRestrictionDueToUnsupportedFeature();

    return ret;
}


InsertSubscriberDataArg::RegionalSubscriptionData* 
InitializeRegionalSubscriptionData()
{
    return InitializeZoneCodeList();
}


DeleteSubscriberDataArg::RegionalSubscriptionIdentifier*
InitializeRegionalSubscriptionIdentifier()
{
    return InitializeZoneCode();
}


RegionalSubscriptionResponse* InitializeRegionalSubscriptionResponse()
{
	RegionalSubscriptionResponse* ret = new RegionalSubscriptionResponse();

	ret->SetTooManyZoneCodes();

	return ret;
}


RemoteUserFreeArg::ReplaceB_Number* InitializeReplaceB_Number()
{
    RemoteUserFreeArg::ReplaceB_Number* rbn =
        new RemoteUserFreeArg::ReplaceB_Number();

    return rbn;
}


RequestedInfo* InitializeRequestedInfo()
{
    RequestedInfo* ret = new RequestedInfo();

    ret->SetExtensionContainer(InitializeExtensionContainer());
    ret->SetLocationInformation(InitializeLocationInfo());
    ret->SetSubscriberState(InitializeSubscriber_State());

    return ret;
}


ResumeCallHandlingArg::Ccbs_Possible* InitializeRCHACcbs_Possible()
{
    ResumeCallHandlingArg::Ccbs_Possible* ccbs_possible =
        new ResumeCallHandlingArg::Ccbs_Possible();

    return ccbs_possible;
}


RoutingInfo* InitializeRoutingInfo()
{
    RoutingInfo* routingInfo = new RoutingInfo();

    routingInfo->SetChoiceRoamingNumber(InitializeRoamingNumber());

    routingInfo->SetChoiceForwardingData(InitializeForwardingData());

    return routingInfo;
}


RUF_Outcome* InitializeRUF_Outcome()
{
    RUF_Outcome* ruf_outcome = new RUF_Outcome();

    ruf_outcome->SetRejected();

    return ruf_outcome;
}


ServiceIndicator* InitializeServiceIndicator()
{
    bool arr[] = { false, false };

    ServiceIndicator* si =
        new ServiceIndicator(ArrayToVector(arr, ARRAY_SIZE(arr)));

    si->SetCamel_invoked();
    si->SetClir_invoked();

    return si;
}


ServiceKey* InitializeServiceKey()
{
    long lkey = 22;

    ServiceKey* serviceKey = new ServiceKey(lkey);

    return serviceKey;
}


SignalInfo* InitializeSignalInfo()
{
    byte arr[] = { 0x01U, 0x02U, 0x03U, 0x04U, 0x05U };

    SignalInfo* si = new SignalInfo(ArrayToVector(arr, ARRAY_SIZE(arr)));

    return si;
}



PurgeMS_Arg::Sgsn_Number* InitializeSgsn_Number()
{
    return InitializeISDN_AddressString();
}

UpdateGprsLocationArg::Sgsn_Address* InitializeSgsn_Address()
{
    return InitializeGSN_Address();
}


SendRoutingInfoRes::ForwardingInterrogationRequired*
    InitializeForwardingInterrogationRequired()
{
    SendRoutingInfoRes::ForwardingInterrogationRequired* fir =
        new SendRoutingInfoRes::ForwardingInterrogationRequired();

    return fir;
}


RoutingInfoForSM_Arg::ServiceCentreAddress*
InitializeServiceCentreAddress()
{
    return InitializeAddressString();
}


SM_DeliveryOutcome* InitializeSM_DeliveryOutcome()
{
    SM_DeliveryOutcome* ret = new SM_DeliveryOutcome();

    ret->SetAbsentSubscriber();

    return ret;
}


SM_RP_DA* InitializeSm_RP_DA()
{
    SM_RP_DA* ret = new SM_RP_DA();
   
    ret->SetChoiceImsi(InitializeIMSI());

    return ret;
}


SM_RP_OA* InitializeSm_RP_OA()
{
    SM_RP_OA* ret = new SM_RP_OA();
   
    ret->SetChoiceMsisdn(InitializeMsisdn());

    return ret;
}


SM_RP_MTI* InitializeSm_RP_MTI()
{
    SM_RP_MTI* ret = new SM_RP_MTI((long) 8);

    return ret;
}


SM_RP_SMEA* InitializeSm_RP_SMEA()
{
    byte arr[] = { 0x99, 0x88, 0x77 };

    SM_RP_SMEA* ret = new SM_RP_SMEA(ArrayToVector(arr, ARRAY_SIZE(arr)));

    return ret;
}


MO_ForwardSM_Arg::Sm_RP_UI* InitializeSm_RP_UI()
{
    return InitializeSignalInfo();
}


RoutingInfoForSM_Arg::Sm_RP_PRI* InitializeSm_RP_PRI()
{
    RoutingInfoForSM_Arg::Sm_RP_PRI* ret = 
        new RoutingInfoForSM_Arg::Sm_RP_PRI();

    return ret;
}


SRES* InitializeSres()
{
    byte arr[] = { 0x01, 0x02, 0x03, 0x04 };

    SRES* s = new SRES(ArrayToVector(arr, ARRAY_SIZE(arr)));

    return s;
}

SS_CamelData* InitializeSS_CamelData()
{
    SS_CamelData* ret = new SS_CamelData();

    ret->SetExtensionContainer(InitializeExtensionContainer());
    ret->SetGsmSCF_Address(InitializeGSMSCF_Address());
    ret->SetSs_EventList(InitializeSS_EventList());

    return ret;
}


SS_Code* InitializeSS_Code()
{
    byte arr[] = { 0x33U };

    SS_Code* sc = new SS_Code(ArrayToVector(arr, ARRAY_SIZE(arr)));

	return sc;
}


SS_CSI* InitializeSS_CSI()
{
    SS_CSI* ret = new SS_CSI();

    ret->SetExtensionContainer(InitializeExtensionContainer());
    ret->SetSs_CamelData(InitializeSS_CamelData());

    return ret;
}


SS_Data* InitializeSS_Data()
{
    SS_Data* sd = new SS_Data();

    sd->SetBasicServiceGroupList(InitializeBasicServiceGroupList());
    sd->SetDefaultPriority(InitializeDefaultPriority());
    sd->SetSs_Code(InitializeSS_Code());
    sd->SetSs_Status(InitializeSS_Status());
    sd->SetSs_SubscriptionOption(InitializeSS_SubscriptionOption());

	return sd;
}


SS_EventList* InitializeSS_EventList()
{
    SS_EventList* ret = new SS_EventList();

    ret->AddElement(InitializeSS_Code());
    ret->AddElement(InitializeSS_Code());
    ret->AddElement(InitializeSS_Code());

    return ret;
}

SS_EventSpecification* InitializeSS_EventSpecification()
{
    SS_EventSpecification* ret = new SS_EventSpecification();

    ret->AddElement(InitializeAddressString());
    ret->AddElement(InitializeAddressString());

    return ret;
}


SS_List *InitializeSS_List()
{
	SS_List* sl = new SS_List();

	sl->AddElement(InitializeSS_Code());
    sl->AddElement(InitializeSS_Code());
    sl->AddElement(InitializeSS_Code());
    sl->AddElement(InitializeSS_Code());

	return sl;
}


SS_Status *InitializeSS_Status()
{
	byte array299[] = { 0x01U };

	SS_Status *ss_Status2  = 
		new SS_Status(ArrayToVector(array299, ARRAY_SIZE(array299)));
	
	return ss_Status2;
}


SubscriberInfo* InitializeSubscriberInfo()
{
    SubscriberInfo* ret = new SubscriberInfo();

    ret->SetExtensionContainer(InitializeExtensionContainer());
    ret->SetLocationInformation(InitializeLocationInformation());
    ret->SetSubscriberState(InitializeSubscriberState());

    return ret;
}


SubscriberState* InitializeSubscriberState()
{
    SubscriberState* ss = new SubscriberState();

    ss->SetChoiceAssumedIdle(InitializeAssumedIdle());

    return ss;
}


RequestedInfo::SubscriberState* InitializeSubscriber_State()
{
    RequestedInfo::SubscriberState* ret = 
        new RequestedInfo::SubscriberState();

    return ret;
}


SubscriberState::AssumedIdle* InitializeAssumedIdle()
{
    SubscriberState::AssumedIdle* ai = new SubscriberState::AssumedIdle();

    return ai;
}


SubscriberStatus* InitializeSubscriberStatus()
{
    SubscriberStatus* subscriberStatus = new SubscriberStatus();

    subscriberStatus->SetServiceGranted();

	return subscriberStatus;
}


SS_SubscriptionOption* InitializeSS_SubscriptionOption()
{
    SS_SubscriptionOption* so = new SS_SubscriptionOption();

    CliRestrictionOption* co = new CliRestrictionOption();
    co->SetTemporaryDefaultRestricted();

    so->SetChoiceCliRestrictionOption(co);

    return so;
}


SubscriberIdentity* InitializeSubscriberIdentity()
{
    SubscriberIdentity* ret = new SubscriberIdentity();

    ret->SetChoiceImsi(InitializeIMSI());

    return ret;
}



SupportedCamelPhases* InitializeSupportedCamelPhases()
{
    bool arr[] = { false, false };

	SupportedCamelPhases* ret = 
        new SupportedCamelPhases(ArrayToVector(arr, ARRAY_SIZE(arr)));

	ret->SetPhase1();
    ret->SetPhase2();

	return ret;
}


SupportedCCBS_Phase* InitializeSupportedCCBS_Phase()
{
    long valueParam = 1;

    SupportedCCBS_Phase* supportedCCBS_Phase =
        new SupportedCCBS_Phase(valueParam, true);

    return supportedCCBS_Phase;
}


SuppressionOfAnnouncement* InitializeSuppressionOfAnnouncement()
{
    SuppressionOfAnnouncement* suppressionOfAnnouncement =
        new SuppressionOfAnnouncement();

    return suppressionOfAnnouncement;
}


PrepareHO_Arg::TargetCellId* InitializeTargetCellId()
{
    return InitializeGlobalCellId();
}


PrepareSubsequentHO_Arg::TargetMSC_Number* InitializeTargetMSC_Number()
{
    return InitializeISDN_AddressString();
}


TBCD_STRING* InitializeAsciCallReference()
{
    byte array[] = { 0x01, 0x02, 0x03, 0x04, 0x05 };

    TBCD_STRING* tbcd_str =
        new TBCD_STRING(ArrayToVector(array, ARRAY_SIZE(array)));

    return tbcd_str;
}


T_CSI* InitializeT_CSI()
{
    T_BcsmCamelTDPData* cameldata1 = new T_BcsmCamelTDPData();
    T_BcsmCamelTDPData* cameldata2 = new T_BcsmCamelTDPData();

    T_CSI* t_csi = new T_CSI();

    // Set cameldata1
    T_BcsmTriggerDetectionPoint* tbtdp = new T_BcsmTriggerDetectionPoint();
    tbtdp->SetTermAttemptAuthorized();
    cameldata1->SetT_BcsmTriggerDetectionPoint(tbtdp);

    cameldata1->SetServiceKey(InitializeServiceKey());
    
    cameldata1->SetGsmSCF_Address(InitializeGsmSCF_Address());
    
    cameldata1->SetDefaultCallHandling(InitializeDefaultCallHandling());

    // extensionContainer not included


    T_BcsmCamelTDPDataList* camellist = new T_BcsmCamelTDPDataList();

    camellist->AddElement(cameldata1);

    t_csi->SetT_BcsmCamelTDPDataList(camellist);

    // extensionContainer not used

    t_csi->SetCamelCapabilityHandling(InitializeCamelCapabilityHandling());

    return t_csi;
}



TeleserviceList *InitializeTeleserviceList()
{
    TeleserviceList* tl = new TeleserviceList();

    // Insert 3 elements (type Ext_TeleserviceCode).
    byte arr1[] = { 0xCCU };
    Ext_TeleserviceCode* tc1 = 
        new Ext_TeleserviceCode(ArrayToVector(arr1, ARRAY_SIZE(arr1)));
    tl->AddElement(tc1);

    byte arr2[] = { 0xDDU };
    Ext_TeleserviceCode* tc2 = 
        new Ext_TeleserviceCode(ArrayToVector(arr2, ARRAY_SIZE(arr2)));
    tl->AddElement(tc2);

    byte arr3[] = { 0xEEU };
    Ext_TeleserviceCode* tc3 = 
        new Ext_TeleserviceCode(ArrayToVector(arr3, ARRAY_SIZE(arr3)));
    tl->AddElement(tc3);

	return tl;
}




TraceReference* InitializeTraceReference()
{
   byte array3[] = { 0x66U };

    TraceReference* traceRef = 
        new TraceReference(ArrayToVector(array3, ARRAY_SIZE(array3)));

    return traceRef;
}


TraceType* InitializeTraceType()
{
    TraceType* traceType = new TraceType((long)10);

    return traceType;
}


CCBS_Data::TranslatedB_Number* InitializeTranslatedB_Number()
{
    return InitializeISDN_AddressString();    
}


USSD_DataCodingScheme* InitializeUssd_DataCodingScheme()
{
    byte array3[] = { 0x66U };

    USSD_DataCodingScheme* us = 
        new USSD_DataCodingScheme(ArrayToVector(array3, ARRAY_SIZE(array3)));

    return us;
}

USSD_String* InitializeUssd_String()
{
    byte arr[] = { 0x01U, 0x02U };

    USSD_String* us = 
        new USSD_String(ArrayToVector(arr, ARRAY_SIZE(arr)));

    return us;
}


VBSDataList* InitializeVbsDataList()
{
    VBSDataList* ret = new VBSDataList();

    ret->AddElement(InitializeVoiceBroadcastData());
    ret->AddElement(InitializeVoiceBroadcastData());

    return ret;
}

VGCSDataList* InitializeVgcsDataList()
{
    VGCSDataList* ret = new VGCSDataList();

    ret->AddElement(InitializeVoiceGroupCallData());
    ret->AddElement(InitializeVoiceGroupCallData());

    return ret;
}


DeleteSubscriberDataArg::VbsGroupIndication*
InitializeVbsGroupIndication()
{
    DeleteSubscriberDataArg::VbsGroupIndication*
        ret = new DeleteSubscriberDataArg::VbsGroupIndication();

    return ret;
}


InsertSubscriberDataArg::VbsSubscriptionData* 
InitializeVbsSubscriptionData()
{
    return InitializeVbsDataList();
}



DeleteSubscriberDataArg::VgcsGroupIndication*
InitializeVgcsGroupIndication()
{
    DeleteSubscriberDataArg::VgcsGroupIndication*
        ret = new DeleteSubscriberDataArg::VgcsGroupIndication();

    return ret;
}

InsertSubscriberDataArg::VgcsSubscriptionData* 
InitializeVgcsSubscriptionData()
{
    return InitializeVgcsDataList();
}


VlrCamelSubscriptionInfo* InitializeVlrCamelSubscriptionInfo()
{
    VlrCamelSubscriptionInfo* ret = new VlrCamelSubscriptionInfo();

    ret->SetExtensionContainer(InitializeExtensionContainer());
    //ret->SetO_CSI(InitializeO_CSI());
    ret->SetSs_CSI(InitializeSS_CSI());

    return ret;
}



VLR_Capability* InitializeVLR_Capability()
{
    VLR_Capability* ret = new VLR_Capability();

    ret->SetExtensionContainer(InitializeExtensionContainer());
    ret->SetSupportedCamelPhases(InitializeSupportedCamelPhases());

    return ret;
}


PurgeMS_Arg::Vlr_Number* InitializeVlr_Number()
{
    return InitializeISDN_AddressString();
}


VoiceBroadcastData* InitializeVoiceBroadcastData()
{
    VoiceBroadcastData* ret = new VoiceBroadcastData();

    ret->SetExtensionContainer(InitializeExtensionContainer());
    ret->SetGroupid(InitializeGroupId());
    ret->SetBroadcastInitEntitlement(InitializeBroadcastInitEntitlement());

    return ret;
}


VoiceGroupCallData* InitializeVoiceGroupCallData()
{
    VoiceGroupCallData* ret = new VoiceGroupCallData();

    ret->SetExtensionContainer(InitializeExtensionContainer());
    ret->SetGroupId(InitializeGroupId());

    return ret;
}


PDP_Context::VplmnAddressAllowed* InitializeVplmnAddressAllowed()
{
    PDP_Context::VplmnAddressAllowed* vaa = 
        new PDP_Context::VplmnAddressAllowed();

    return vaa;
}


ZoneCode* InitializeZoneCode()
{
    byte arr[] = { 0x01U, 0x02U };

    ZoneCode* ret = new ZoneCode(ArrayToVector(arr, ARRAY_SIZE(arr)));

    return ret;
}

ZoneCodeList* InitializeZoneCodeList()
{
    ZoneCodeList* ret = new ZoneCodeList();

    ret->AddElement(InitializeZoneCode());
    ret->AddElement(InitializeZoneCode());
    ret->AddElement(InitializeZoneCode());

    return ret;
}