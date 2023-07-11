/*
 ****************************************************************************
 * DISCLAIMER:
 *
 * INTELLINET DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
 * ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
 * INTELLINET BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
 * ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 *  
 ****************************************************************************
 *
 *  ID: $Id: tools.cpp,v 9.1 2005/03/23 12:51:34 cvsadmin Exp $
 *
 * LOG: $Log: tools.cpp,v $
 * LOG: Revision 9.1  2005/03/23 12:51:34  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:31  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:08:51  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:21  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:22  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:03  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2000/08/15 23:57:21  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:19:28  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.3  1999/11/01 17:26:36  cbascon
 * LOG:
 * LOG:
 * LOG: Should have log entries on files now.
 * LOG:
 ****************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//
// Tool functions for the testing of GSSMAPPlus
//
////////////////////////////////////////////////////////////////////////////////

#include "tools.h"
#include "SendOrReceive.h"


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


/*
 ****************************************************************************
 * NOTE: The functions below are used to set the member variables of
 *       GSMMAP classes.
 *
 ****************************************************************************/

AbsentSubscriberDiagnosticSM* InitializeAbsentSubscriberDiagnosticSM()
{
    long val = 0;
    AbsentSubscriberDiagnosticSM *asds;
    
    // Ask user to provide data
    cout << "Enter AbsentSubscriberDiagnosticSM, integer (0..255): ";
    val = getSelection(0, 255);
    cout << endl;

    asds = new AbsentSubscriberDiagnosticSM(val);
    return asds;
}


Additional_Number* InitializeAdditional_Number()
{
    Additional_Number *an = new Additional_Number();

    // Ask user to select type of additional number
    cout << "Select Additional Number:" << endl;
    cout << "-------------------------" << endl;
    cout << "[0] MSC-Number" << endl;
    cout << "[1] SGSN-Number" << endl;
    cout << endl;

    if (getSelection(0, 1) == 0)
    {
        an->SetChoiceMsc_Number(InitializeMsc_Number());
    }
    else
    {
        an->SetChoiceSgsn_Number(InitializeISDN_AddressString());
    }
    cout << endl;
    return an;
}


AddressString* InitializeAddressString()
{
    byte arr[] = { 0xAAU, 0xBBU };

    AddressString *as = new AddressString(ArrayToVector(arr, ARRAY_SIZE(arr)));

    return as;
}

AddressString* InitializeForwardedToNumber()
{
    byte array[] = { 0x00, 0x01, 0x02, 0x04, 0x05 };

    AddressString *as =
        new AddressString(ArrayToVector(array, ARRAY_SIZE(array)));

    return as;
}


AgeOfLocationInformation* InitializeAgeOfLocationInformation()
{
    long val = 0;
    AgeOfLocationInformation *aoli;

    // Ask for user entry
    cout << "Enter AgeOfLocationInformation, integer (0..32767): ";
    val = getSelection(0, 32767);
    cout << endl;

    aoli = new AgeOfLocationInformation(val);
    return aoli;
}


AlertingPattern* InitializeAlertingPattern()
{
    byte array[] = { 0x01 };

    AlertingPattern *ap =
        new AlertingPattern(ArrayToVector(array, ARRAY_SIZE(array)));

    return ap;
}


AlertReason* InitializeAlertReason()
{
    long val = 0;
    AlertReason *ar;

    // Ask user to select AlertReason
    cout << "Select AlertReason:" << endl;
    cout << "-------------------" << endl;
    cout << "[0] MS-Present" << endl;
    cout << "[1] MemoryAvailable" << endl;
    val = getSelection(0, 1);
    cout << endl;

    ar = new AlertReason(val);
    return ar;
}


ReadyForSM_Arg::AlertReasonIndicator* InitializeAlertReasonIndicator()
{
    ReadyForSM_Arg::AlertReasonIndicator *ari = 
        new ReadyForSM_Arg::AlertReasonIndicator();

    return ari;
}


GPRSSubscriptionDataWithdraw::AllGPRSData* InitializeAllGprsData()
{
    GPRSSubscriptionDataWithdraw::AllGPRSData *gsdw = 
        new GPRSSubscriptionDataWithdraw::AllGPRSData();

    return gsdw;
}


APN* InitializeApn()
{
    byte arr[] = { 0x01, 0x02, 0x03, 0x04 };

    IA5String *apn = new IA5String(ArrayToVector(arr, ARRAY_SIZE(arr)));

    return apn;
}



AuthenticationSet* InitializeAuthenticationSet()
{
    AuthenticationSet *as = new AuthenticationSet();

    as->SetKc(InitializeKc());
    as->SetRand(InitializeRand());
    as->SetSres(InitializeSres());

    return as;
}


AuthenticationSetList* InitializeAuthenticationSetList()
{
    AuthenticationSetList *asl = new AuthenticationSetList();

    // Add 3 elements to the list
    asl->AddElement(InitializeAuthenticationSet());
    asl->AddElement(InitializeAuthenticationSet());
    asl->AddElement(InitializeAuthenticationSet());

    return asl;
}


RegisterSS_Arg::BasicService* InitializeBasicService()
{
    RegisterSS_Arg::BasicService *basicServ = 
        new RegisterSS_Arg::BasicService();

    basicServ->SetChoiceBearerService(InitializeBearerService());

    return basicServ;
}


BasicServiceCode* InitializeBasicServiceCode()
{
    BasicServiceCode *bc = new BasicServiceCode();

    bc->SetChoiceBearerService(InitializeBearerService());

    return bc;
}


BasicServiceCriteria* InitializeBasicServiceCriteria()
{
    BasicServiceCriteria *bsc = new BasicServiceCriteria();

    bsc->AddElement(InitializeExt_BasicServiceCode());

    return bsc;
}


BasicServiceGroupList* InitializeBasicServiceGroupList()
{
    BasicServiceGroupList *bl = new BasicServiceGroupList();

    bl->AddElement(InitializeBasicServiceCode());
    bl->AddElement(InitializeBasicServiceCode());

    return bl;
}


BasicServiceList* InitializeBasicServiceList()
{
    BasicServiceList *bsl = new BasicServiceList();

    bsl->AddElement(InitializeExt_BasicServiceCode());
    bsl->AddElement(InitializeExt_BasicServiceCode());
    bsl->AddElement(InitializeExt_BasicServiceCode());
    bsl->AddElement(InitializeExt_BasicServiceCode());

    return bsl;
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
    BearerServiceList *bl = new BearerServiceList();

    // Insert 2 elements (Type Ext_BearerServiceCode).
    byte arr[] = { 0xBBU };
    Ext_BearerServiceCode *bc1 = 
        new Ext_BearerServiceCode(ArrayToVector(arr, ARRAY_SIZE(arr)));    

    byte array5[] = { 0xBBU };
    Ext_BearerServiceCode *bc2 = 
        new Ext_BearerServiceCode(ArrayToVector(array5, ARRAY_SIZE(array5)));

    bl->AddElement(bc1);
    bl->AddElement(bc2);
	
    return bl;
}


CallDirection* InitializeCallDirection()
{
    byte array[] = { 0x01 };

    CallDirection *cd =
        new CallDirection(ArrayToVector(array, ARRAY_SIZE(array)));

    return cd;
}


CallOutcome* InitializeCallOutcome()
{
    long val = 0;
    CallOutcome *co;

    // Ask user to select CallOutcome
    cout << "Select CallOutcome:" << endl;
    cout << "-------------------" << endl;
    cout << "[0] Success" << endl;
    cout << "[1] Failure" << endl;
    cout << "[2] Busy" << endl;
    val = getSelection(0, 2);
    cout << endl;

    co = new CallOutcome(val);
    return co;
}


CallReportData* InitializeCallReportData()
{
    CallReportData *crd = new CallReportData();

    crd->SetMonitoringMode(InitializeMonitoringMode());
    crd->SetCallOutcome(InitializeCallOutcome());

    return crd;
}


VoiceBroadcastData::BroadcastInitEntitlement*
InitializeBroadcastInitEntitlement()
{
    VoiceBroadcastData::BroadcastInitEntitlement *bie = 
        new VoiceBroadcastData::BroadcastInitEntitlement();

    return bie;
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

    ISDN_SubaddressString *bss = new ISDN_SubaddressString
        (ArrayToVector(arr, ARRAY_SIZE(arr)));

    return bss;
}


CCBS_Data::CallInfo* InitializeCallInfo()
{
    return InitializeExternalSignalInfo();
}


CCBS_Indicators* InitializeCCBS_Indicators()
{
    CCBS_Indicators *ci = new CCBS_Indicators();
    
    ci->SetCcbs_Possible(InitializeCcbs_Possible());
    ci->SetKeepCCBS_CallIndicator(InitializeKeepCCBS_CallIndicator());

    return ci;
}


CCBS_Indicators::Ccbs_Possible* InitializeCcbs_Possible()
{
    CCBS_Indicators::Ccbs_Possible *cp =
        new CCBS_Indicators::Ccbs_Possible();

    return cp;
}


CallReferenceNumber* InitializeCallReferenceNumber()
{
    byte array[] = { 0x01, 0x02, 0x03, 0x04, 0x05 };
    
    CallReferenceNumber *crn =
        new CallReferenceNumber(ArrayToVector(array, ARRAY_SIZE(array)), true);

    return crn;
}


CCBS_SubscriberStatus* InitializeCCBS_SubscriberStatus()
{
    long val = 0;
    CCBS_SubscriberStatus *css;

    // Ask user to select CCBS_SubscriberStatus
    cout << "Select CCBS_SubscriberStatus:" << endl;
    cout << "-----------------------------" << endl;
    cout << "[0] NotIdle" << endl;
    cout << "[1] Idle" << endl;
    cout << "[2] NotReachable" << endl;
    val = getSelection(0, 2);
    cout << endl;

    css = new CCBS_SubscriberStatus(val);
    return css;
}


CallTypeCriteria* InitializeCallTypeCriteria()
{
    long val = 0;
    CallTypeCriteria *ctc;

    // Ask user to select CallTypeCriteria
    cout << "Select CallTypeCriteria:" << endl;
    cout << "------------------------" << endl;
    cout << "[0] Forwarded" << endl;
    cout << "[1] NotForwarded" << endl;
    val = getSelection(0, 1);
    cout << endl;

    ctc = new CallTypeCriteria(val);
    return ctc;
}



SubscriberState::CamelBusy* InitializeCamelBusy()
{
    SubscriberState::CamelBusy *cb = new SubscriberState::CamelBusy();

    return cb;
}



CamelCapabilityHandling* InitializeCamelCapabilityHandling()
{
    long val = 0;
    CamelCapabilityHandling *cch;

    // Ask user to enter CamelCapabilityHandling
    cout << "Enter CamelCapabilityHandling, integer (1..16): ";
    val = getSelection(1, 16);
    cout << endl;

    cch = new CamelCapabilityHandling(val);
    return cch;
}


CamelInfo* InitializeCamelInfo()
{
    bool barray[] = { true, false, true, false, true };
    CamelInfo *ci = new CamelInfo();
    
    SupportedCamelPhases* supportedCamelPhases =
        new SupportedCamelPhases(ArrayToVector(barray, ARRAY_SIZE(barray)),
                                               true);
    ci->SetSupportedCamelPhases(supportedCamelPhases);

    CamelInfo::Suppress_T_CSI *suppress_T_CSI =
        new CamelInfo::Suppress_T_CSI();

    return ci;
}


CamelRoutingInfo* InitializeCamelRoutingInfo()
{
    CamelRoutingInfo *cri = new CamelRoutingInfo();

    cout << "Setting CamelRoutingInfo parameters:" << endl;
    cout << "------------------------------------" << endl;

    // Setting CamelRoutingInfo mandatory parameter
    cri->SetGmscCamelSubscriptionInfo(InitializeGmscCamelSubscriptionInfo());

    // Ask user to include ForwardingData optional parameter
    cout << "Include ForwardingData optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        cri->SetForwardingData(InitializeForwardingData());
    }

    return cri;
}

DeleteSubscriberDataArg::CamelSubscriptionInfoWithdraw*
InitializeCamelSubscriptionInfoWithdraw()
{
    DeleteSubscriberDataArg::CamelSubscriptionInfoWithdraw *csiw =
        new DeleteSubscriberDataArg::CamelSubscriptionInfoWithdraw();

    return csiw;
}

CancellationType* InitializeCancellationType()
{
    long val = 0;
    CancellationType *ct;

    // Ask user to select CancellationType
    cout << "Select CancellationType:" << endl;
    cout << "------------------------" << endl;
    cout << "[0] UpdateProcedure" << endl;
    cout << "[1] SubscriptionWithdraw" << endl;
    val = getSelection(0, 1);
    cout << endl;

    ct = new CancellationType(val);
    return ct;
}

Category *InitializeCategory()
{
    byte array[] = { 0x66U };

    Category *c = new Category(ArrayToVector(array, ARRAY_SIZE(array)));

    return c;
}


SendRoutingInfoArg::Ccbs_Call* InitializeCcbs_Call()
{
    SendRoutingInfoArg::Ccbs_Call *cc = new SendRoutingInfoArg::Ccbs_Call();

    return cc;
}


CCBS_Data* InitializeCcbs_Data()
{
    CCBS_Data *cd = new CCBS_Data();

    cout << "Setting CCBS_Data parameters:" << endl;
    cout << "-----------------------------" << endl;

    // Set mandatory parameters
    cd->SetCallInfo(InitializeCallInfo());
    cd->SetCcbs_Feature(InitializeCcbs_Feature());
    cd->SetNetworkSignalInfo(InitializeNetworkSignalInfo());
    cd->SetTranslatedB_Number(InitializeTranslatedB_Number());

    // Ask user to include service indicator optional parameter
    cout << "Include ServiceIndicator optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        cd->SetServiceIndicator(InitializeServiceIndicator());
    }
    return cd;
}


CCBS_Feature* InitializeCcbs_Feature()
{
    CCBS_Feature *cf = new CCBS_Feature();

    cout << "Setting CCBS_Feature parameters:" << endl;
    cout << "--------------------------------" << endl;

    // Ask user to include B_subscriberNumber optional parameter
    cout << "Include B_subscriberNumber optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        cf->SetB_subscriberNumber(InitializeB_subscriberNumber());
    }

    // Ask user to include B_subscriberSubaddress optional parameter
    cout << "Include B_subscriberSubaddress optional parameter? ";
    cout << "[y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        cf->SetB_subscriberSubaddress(InitializeB_subscriberSubaddress());
    }

    // Ask user to include BasicServiceGroup optional parameter
    cout << "Include BasicServiceGroup optional parameter? ";
    cout << "[y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        cf->SetBasicServiceGroup(InitializeBasicService());
    }

    // Ask user to include Ccbs_Index optional parameter
    cout << "Include Ccbs_Index optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        cf->SetCcbs_Index(InitializeCcbs_Index());
    }
    cout << endl;
    return cf;
}


CCBS_Index* InitializeCcbs_Index()
{
    long val = 0;
    CCBS_Index *ci;

    // Ask user to provide CCBS_Index
    cout << "Enter CCBS_Index, integer (1..5): ";
    val = getSelection(1, 5);
    cout << endl;

    ci = new CCBS_Index(val);
    return ci;
}


CCBS_Indicators::KeepCCBS_CallIndicator* InitializeKeepCCBS_CallIndicator()
{
    CCBS_Indicators::KeepCCBS_CallIndicator *kcci =
        new CCBS_Indicators::KeepCCBS_CallIndicator();

    return kcci;
}


CellIdFixedLength* InitializeCellIdFixedLength()
{
    // octet string size 7
    byte array[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 };

    CellIdFixedLength *cifl =
        new CellIdFixedLength(ArrayToVector(array, ARRAY_SIZE(array)));

    return cifl;
}


CellIdOrLAI* InitializeCellIdOrLAI()
{
    CellIdOrLAI *ciol = new CellIdOrLAI();

    ciol->SetChoiceCellIdFixedLength(InitializeCellIdFixedLength());

    return ciol;
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

    CODEC_Info *ci =
        new CODEC_Info(ArrayToVector(array, ARRAY_SIZE(array)));

    return ci;
}


GPRSSubscriptionData::CompleteDataListIncluded* 
InitializeCompleteDataListIncluded()
{
    GPRSSubscriptionData::CompleteDataListIncluded *cdli = 
        new GPRSSubscriptionData::CompleteDataListIncluded();

    return cdli;
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
    SendRoutingInfoRes::CugSubscriptionFlag* csf =
        new SendRoutingInfoRes::CugSubscriptionFlag();

    return csf;
}


DefaultCallHandling* InitializeDefaultCallHandling()
{
    long val = 0;
    DefaultCallHandling *dch;
    
    // Ask user to select DefaultCallHandling
    cout << "Select DefaultCallHandling:" << endl;
    cout << "---------------------------" << endl;
    cout << "[0] ContinueCall" << endl;
    cout << "[1] ReleaseCall" << endl;
    val = getSelection(0, 1);
    cout << endl;

    dch = new DefaultCallHandling(val);
    return dch;
}


ReportSM_DeliveryStatusArg::DeliveryOutcomeIndicator*
InitializeDeliveryOutcomeIndicator()
{
    ReportSM_DeliveryStatusArg::DeliveryOutcomeIndicator *doi = 
        new ReportSM_DeliveryStatusArg::DeliveryOutcomeIndicator();

    return doi;
}


DestinationNumberCriteria* InitializeDestinationNumberCriteria()
{
    DestinationNumberCriteria *dnc = new DestinationNumberCriteria();
    
    dnc->SetMatchType(InitializeMatchType());

    DestinationNumberList *dnlist = new DestinationNumberList();
    dnlist->AddElement(InitializeISDN_AddressString());

    return dnc;
}


SS_Data::DefaultPriority* InitializeDefaultPriority()
{
    return InitializeEmlpp_Priority();
}

EMLPP_Priority* InitializeEmlpp_Priority()
{
    long val = 0;
    EMLPP_Priority *ep;

    // Ask user to enter EMLPP_Priority
    cout << "Enter EMLPP_Priority, integer (0..15): ";
    val = getSelection(0, 15);
    cout << endl;

    ep = new EMLPP_Priority(val);
    return ep;
}


EventReportData* InitializeEventReportData()
{
    EventReportData *erd = new EventReportData();

    erd->SetCcbs_SubscriberStatus(InitializeCCBS_SubscriberStatus());

    return erd;
}


Ext_BasicServiceCode* InitializeExt_BasicServiceCode()
{
    Ext_BasicServiceCode *ebsc = new Ext_BasicServiceCode();

    ebsc->SetChoiceExt_BearerService(InitializeExt_BearerServiceCode());

    return ebsc;
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
    ExtendedRoutingInfo *eri = new ExtendedRoutingInfo();

    // Ask user to select ExtendedRoutingInfo
    cout << "Select ExtendedRoutingInfo:" << endl;
    cout << "---------------------------" << endl;
    cout << "[1] RoutingInfo" << endl;
    cout << "[2] CamelRoutingInfo" << endl;
    if (getSelection(1, 2) == 1)
    {
        eri->SetChoiceRoutingInfo(InitializeRoutingInfo());
    }
    else
    {
        eri->SetChoiceCamelRoutingInfo(InitializeCamelRoutingInfo());
    }
    return eri;
}


ExtensionContainer* InitializeExtensionContainer()
{
    ExtensionContainer *ec = new ExtensionContainer();

    return ec;
}


ExternalSignalInfo* InitializeExternalSignalInfo()
{
    ExternalSignalInfo *esi = new ExternalSignalInfo();

    // Setting mandatory parameters
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
    Ext_SS_Data *esd = new Ext_SS_Data();

    // Setting mandatory parameters
    esd->SetSs_Code(InitializeSS_Code());
    esd->SetSs_Status(InitializeExt_SS_Status());

    // Ask user to include Ss_SubscriptionOption optional parameter
    cout << "Include Ss_SubscriptionOption optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        esd->SetSs_SubscriptionOption(InitializeSS_SubscriptionOption());
    }
    return esd;
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
    Ext_SS_Info *sS_Info3 = new Ext_SS_Info();

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
    ForwardingData *fd = new ForwardingData();

    cout << "Setting ForwardingData parameters:" << endl;
    cout << "----------------------------------" << endl;

    // Ask user to include ForwardedToNumber optional parameter
    cout << "Include ForwardedToNumber optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        fd->SetForwardedToNumber(InitializeForwardedToNumber());
    }

    // Ask user to include ForwardedToSubaddress optional parameter
    cout << "Include ForwardedToSubaddress optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        fd->SetForwardedToSubaddress(InitializeForwardedToSubaddress());
    }

    // Ask user to include ForwardingOptions optional parameter
    cout << "Include ForwardingOptions optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        fd->SetForwardingOptions(InitializeForwardingOptions());
    }

    cout << endl;
    return fd;
}


ForwardingOptions* InitializeForwardingOptions()
{
    byte array[] = { 0x01 };

    ForwardingOptions *fo =
        new ForwardingOptions(ArrayToVector(array, ARRAY_SIZE(array)));

    return fo;
}


ForwardingReason* InitializeForwardingReason()
{
    long val = 0;
    ForwardingReason *fr;

    // Ask user to select forwarding reason
    cout << "Select ForwardingReason:" << endl;
    cout << "------------------------" << endl;
    cout << "[0] NotReachable" << endl;
    cout << "[1] Busy" << endl;
    cout << "[2] NoReply" << endl;
    cout << endl;
    val = getSelection(0, 2);
    cout << endl;

    fr = new ForwardingReason(val);
    return fr;
}


GroupKeyNumber* InitializeGroupKeyNumber()
{
    long val = 0;

    GroupKeyNumber *gkn;

    // Ask user to provide GroupKeyNumber integer
    cout << "Enter GroupKeyNumber, integer (0..15): ";
    val = getSelection(0, 15);
    cout << endl;

    gkn = new GroupKeyNumber(val);
    return gkn;
}


RegisterSS_Arg::ForwardedToNumber* IntializeForwardedToNumber()
{
    byte arr[] = { 0x01U, 0x02U, 0x03U, 0x04U }; 

    RegisterSS_Arg::ForwardedToNumber *ftn = 
        new RegisterSS_Arg::ForwardedToNumber(ArrayToVector
                                              (arr, ARRAY_SIZE(arr)));

    return ftn;
}


RegisterSS_Arg::ForwardedToSubaddress* IntializeForwardedToSubaddress()
{
    byte arr[] = { 0x01U, 0x02U, 0x03U, 0x04U }; 

    RegisterSS_Arg::ForwardedToSubaddress *fts = 
        new RegisterSS_Arg::ForwardedToSubaddress(ArrayToVector
                                              (arr, ARRAY_SIZE(arr)));

    return fts;
}


PurgeMS_Res::FreezeP_TMSI* InitializeFreezeP_TMSI()
{
    PurgeMS_Res::FreezeP_TMSI *fpt = new PurgeMS_Res::FreezeP_TMSI();

    return fpt;
}


PurgeMS_Res::FreezeTMSI* InitializeFreezeTMSI()
{
    PurgeMS_Res::FreezeTMSI *ft = new PurgeMS_Res::FreezeTMSI();

    return ft;
}


GeographicalInformation* InitializeGeographicalInformation()
{
    // octet string size 8
    byte array[] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };

    GeographicalInformation *gi =
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

    GlobalCellId *gid = new GlobalCellId(ArrayToVector(arr, ARRAY_SIZE(arr)));

    return gid;
}


GPRSDataList* InitializeGprsDataList()
{
    GPRSDataList *gl = new GPRSDataList();

    gl->AddElement(InitializePDP_Context());
    gl->AddElement(InitializePDP_Context());
    gl->AddElement(InitializePDP_Context());

    return gl;
}



LocationInfoWithLMSI::GprsNodeIndicator* InitializeGprsNodeIndicator()
{
    LocationInfoWithLMSI::GprsNodeIndicator *gni = 
        new LocationInfoWithLMSI::GprsNodeIndicator();

    return gni;
}



GPRSSubscriptionData* InitializeGprsSubscriptionData()
{
    GPRSSubscriptionData *gsd = new GPRSSubscriptionData();

    cout << "Setting GPRSSubscriptionData parameters:" << endl;
    cout << "----------------------------------------" << endl;
    // Set mandatory parameter
    gsd->SetGprsDataList(InitializeGprsDataList());

    // Ask user to include CompleteDataListIncluded optional parameter
    cout << "Include CompleteDataListIncluded optional parameter? ";
    cout << "[y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        gsd->SetCompleteDataListIncluded(InitializeCompleteDataListIncluded());
    }
    
    // Ask user to include extension container optional parameter
    cout << "Include ExtensionContainer optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        gsd->SetExtensionContainer(InitializeExtensionContainer());
    }

    cout << endl;
    return gsd;
}



GroupId* InitializeGroupId()
{
    byte array[] = { 0x01U, 0x02U, 0x03U }; 

    GroupId *gi = new GroupId(ArrayToVector(array, ARRAY_SIZE(array)));

    return gi;
}


GmscCamelSubscriptionInfo* InitializeGmscCamelSubscriptionInfo()
{
    GmscCamelSubscriptionInfo *gcsi = new GmscCamelSubscriptionInfo();

    cout << "Setting GmscCamelSubscriptionInfo parameters:" << endl;
    cout << "---------------------------------------------" << endl;

    // Ask user to include T_CSI optional parameter
    cout << "Include T_CSI optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        gcsi->SetT_CSI(InitializeT_CSI());
    }

    // Ask user to include O_CSI optional parameter
    cout << "Include O_CSI optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        gcsi->SetO_CSI(InitializeO_CSI());
    }

    cout << endl;
    return gcsi;
}


GPRSSubscriptionDataWithdraw* InitializeGprsSubscriptionDataWithdraw()
{
    GPRSSubscriptionDataWithdraw *gsdw = new GPRSSubscriptionDataWithdraw();

    gsdw->SetChoiceAllGPRSData(InitializeAllGprsData());

    return gsdw;
}



RoutingInfoForSM_Arg::GprsSupportIndicator*
InitializeGprsSupportIndicator()
{
    RoutingInfoForSM_Arg::GprsSupportIndicator *gsi = 
        new RoutingInfoForSM_Arg::GprsSupportIndicator();

    return gsi;
}



SS_CamelData::GsmSCF_Address* InitializeGSMSCF_Address()
{
    return InitializeISDN_AddressString();
}

GSN_Address* InitializeGSN_Address()
{
    byte arr[] = { 0x01U, 0x02U, 0x03U, 0x04U }; 

    GSN_Address *ga = new GSN_Address(ArrayToVector(arr, ARRAY_SIZE(arr)));

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
    HLR_List *hl = new HLR_List();

    hl->AddElement(InitializeHLR_Id());
    hl->AddElement(InitializeHLR_Id());
    hl->AddElement(InitializeHLR_Id());

    return hl;
}



UpdateGprsLocationRes::Hlr_Number* InitializeHlr_Number()
{
    return InitializeISDN_AddressString();
}

PrepareHO_Arg::Ho_NumberNotRequired* InitializeHo_NumberNotRequired()
{
    PrepareHO_Arg::Ho_NumberNotRequired *hr = 
        new PrepareHO_Arg::Ho_NumberNotRequired();

    return hr;
}


Identity* InitializeIdentity()
{
    Identity* identity = new Identity();
    
    byte array1[] = { 0x01U, 0x02U, 0x03U, 0x04U }; 
    IMSI *imsi = new IMSI(ArrayToVector(array1, ARRAY_SIZE(array1)));

    identity->SetChoiceImsi(imsi);

    return identity;
}


IMSI* InitializeIMSI()
{
    byte array1[] = { 0x01U, 0x02U, 0x03U, 0x04U }; 

    IMSI *imsi = new IMSI(ArrayToVector(array1, ARRAY_SIZE(array1)));

    return imsi;
}


InterrogationType* InitializeInterrogationType()
{
    long val = 0;
    InterrogationType *it;
    
    // Ask user to select InterrogationType
    cout << "Select InterrogationType:" << endl;
    cout << "-------------------------" << endl;
    cout << "[0] BasicCall" << endl;
    cout << "[1] Forwarding" << endl;
    cout << endl;
    val = getSelection(0, 1);
    cout << endl;

    it = new InterrogationType(val);
    return it;
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

    ISDN_SubaddressString *iss = 
        new ISDN_SubaddressString(ArrayToVector(array, ARRAY_SIZE(array)));

    return iss;
}


ISDN_AddressString* InitializeVmsc_Address()
{
    return InitializeISDN_AddressString();
}


Kc* InitializeKc()
{
    byte array[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };

    Kc *k = new Kc(ArrayToVector(array, ARRAY_SIZE(array)));

    return k;
}


LMSI* InitializeLMSI()
{
    byte arr[] = { 0x11, 0x22, 0x33, 0x44 };

    LMSI *lmsi = new LMSI(ArrayToVector(arr, ARRAY_SIZE(arr)));

    return lmsi;
}


RequestedInfo::LocationInformation* InitializeLocationInfo()
{
    RequestedInfo::LocationInformation *li = 
        new RequestedInfo::LocationInformation();

    return li;
}


LocationInformation* InitializeLocationInformation()
{
    LocationInformation *li = new LocationInformation();

    cout << "Setting LocationInformation parameters:" << endl;
    cout << "---------------------------------------" << endl;

    // Ask user to include AgeOfLocationInformation optional parameter
    cout << "Include AgeOfLocationInformation optional parameter? ";
    cout << "[y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        li->SetAgeOfLocationInformation(InitializeAgeOfLocationInformation());
    }

    // Ask user to include GeographicalInformation optional parameter
    cout << "Include GeographicalInformation optional parameter? ";
    cout << "[y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        li->SetGeographicalInformation(InitializeGeographicalInformation());
    }

    // Ask user to include VLR number
    cout << "Include Vlr_number? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        li->SetVlr_number(InitializeISDN_AddressString());
    }

    // Ask user to include LocationNumber
    cout << "Include LocationNumber? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        li->SetLocationNumber(InitializeLocationNumber());
    }

    // Ask user to include CellIdOrLAI
    cout << "Include CellIdOrLAI? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        li->SetCellIdOrLAI(InitializeCellIdOrLAI());
    }

    cout << endl;
    return li;
}


LocationInfoWithLMSI* InitializeLocationInfoWithLMSI()
{
    LocationInfoWithLMSI* liwl = new LocationInfoWithLMSI();

    cout << "Setting LocationInfoWithLMSI parameters:" << endl;
    cout << "----------------------------------------" << endl;

    // Set mandatory parameter
    liwl->SetNetworkNode_Number(InitializeNetworkNode_Number());

    // Ask user to include Additional_Number
    cout << "Include Additional_Number? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        liwl->SetAdditional_Number(InitializeAdditional_Number());
    }

    // Ask user to include GprsNodeIndicator
    cout << "Include GprsNodeIndicator? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        liwl->SetGprsNodeIndicator(InitializeGprsNodeIndicator());
    }

    // Ask user to include Lmsi
    cout << "Include Lmsi? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        liwl->SetLmsi(InitializeLMSI());
    }
    
    // Ask user to include ExtensionContainer
    cout << "Include ExtensionContainer? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        liwl->SetExtensionContainer(InitializeExtensionContainer());
    }

    cout << endl;
    return liwl;
}


LocationNumber* InitializeLocationNumber()
{
    byte array[] = { 0x10, 0x20, 0x30, 0x40 };

    LocationNumber *ln =
        new LocationNumber(ArrayToVector(array, ARRAY_SIZE(array)));

    return ln;
}


MatchType* InitializeMatchType()
{
    long val = 0;
    MatchType *mt;

    // Ask user to select matchtype
    cout << "Select MatchType:" << endl;
    cout << "-----------------" << endl;
    cout << "[0] Inhibiting" << endl;
    cout << "[1] Enabling" << endl;
    cout << endl;
    val = getSelection(0, 1);
    cout << endl;

    mt = new MatchType(val);
    return mt;
}


MonitoringMode* InitializeMonitoringMode()
{
    long val = 0;
    MonitoringMode *mm;

    // Ask user to select monitoring mode
    cout << "Select MonitoringMode:" << endl;
    cout << "----------------------" << endl;
    cout << "[0] A-side" << endl;
    cout << "[1] B-side" << endl;
    cout << endl;
    val = getSelection(0, 1);
    cout << endl;

    mm = new MonitoringMode(val);
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
    ProvideRoamingNumberArg::Ccbs_Call *cc =
        new ProvideRoamingNumberArg::Ccbs_Call();

    return cc;
}


ProvideRoamingNumberArg::Or_Interrogation* InitializePRNAOr_Interrogation()
{
    ProvideRoamingNumberArg::Or_Interrogation *oi =
        new ProvideRoamingNumberArg::Or_Interrogation();

    return oi;
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
    long val = 0;
    ReportingState *rs;

    // Ask user to select reporting state
    cout << "Select ReportingState:" << endl;
    cout << "----------------------" << endl;
    cout << "[0] StopMonitoring" << endl;
    cout << "[1] StartMonitoring" << endl;
    cout << endl;
    val = getSelection(0, 1);
    cout << endl;

    rs = new ReportingState(val);
    return rs;
}


RestoreDataRes::MsNotReachable* InitializeMsNotReachable()
{
    RestoreDataRes::MsNotReachable *mnr = 
        new RestoreDataRes::MsNotReachable();

    return mnr;
}



CCBS_Data::NetworkSignalInfo* InitializeNetworkSignalInfo()
{
    return InitializeExternalSignalInfo();    
}

NAEA_CIC* InitializeNaea_PreferredCIC()
{
    byte arr[] = { 0x11U, 0x22U, 0x33U };

    NAEA_CIC *nc = new NAEA_CIC(ArrayToVector(arr, ARRAY_SIZE(arr)));

    return nc;
}


NAEA_PreferredCI* InitializeNaea_PreferredCI()
{
    NAEA_PreferredCI *npc = new NAEA_PreferredCI();

    npc->SetNaea_PreferredCIC(InitializeNaea_PreferredCIC());
    npc->SetExtensionContainer(InitializeExtensionContainer());

    return npc;
}


NetworkAccessMode* InitializeNetworkAccessMode()
{
    long val = 0;
    NetworkAccessMode *nam;

    // Ask user to select NetworkAccessMode
    cout << "Select NetworkAccessMode:" << endl;
    cout << "-------------------------" << endl;
    cout << "[0] BothMSCAndSGSN" << endl;
    cout << "[1] OnlyMSC" << endl;
    cout << "[2] OnlySGSN" << endl;
    cout << endl;
    val = getSelection(0, 2);
    cout << endl;

    nam = new NetworkAccessMode(val);
    return nam;
}


NoReplyConditionTime* InitializeNoReplyConditionTime()
{
    long val = 0;
    NoReplyConditionTime *nrct;

    // Ask user to provide NoReplyConditionTime
    cout << "Enter NoReplyConditionTime, integer (5..30): ";
    val = getSelection(5, 30);
    cout << endl;

    nrct = new NoReplyConditionTime(val);
    return nrct;
}


NumberOfForwarding* InitializeNumberOfForwarding()
{
    long val = 0;
    NumberOfForwarding *nof;

    // Ask user to provide NumberOfForwarding
    cout << "Enter NumberOfForwarding, integer (1..5): ";
    val = getSelection(1, 5);
    cout << endl;

    nof = new NumberOfForwarding(val);
    return nof;
}


O_BcsmCamelTDP_Criteria* InitializeO_BcsmCamelTDP_Criteria()
{
    O_BcsmCamelTDP_Criteria *obctc = new O_BcsmCamelTDP_Criteria();
    
    cout << "Setting O_BcsmCamelTDP_Criteria parameters:" << endl;
    cout << "-------------------------------------------" << endl;

    // Ask user to include DestinationNumberCriteria optional parameter
    cout << "Include DestinationNumberCriteria optional parameter? ";
    cout << "[y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        obctc->SetDestinationNumberCriteria
            (InitializeDestinationNumberCriteria());
    }

    // Ask user to include BasicServiceCriteria optional parameter
    cout << "Include BasicServiceCriteria optional parameter? ";
    cout << "[y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        obctc->SetBasicServiceCriteria(InitializeBasicServiceCriteria());
    }

    // Ask user to include CallTypeCriteria optional parameter
    cout << "Include CallTypeCriteria optional parameter? ";
    cout << "[y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        obctc->SetCallTypeCriteria(InitializeCallTypeCriteria());
    }

    cout << endl;
    return obctc;
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
    cameldata1->SetO_BcsmCamelTDP_Criteria
        (InitializeO_BcsmCamelTDP_Criteria());

    camellist->AddElement(cameldata1);

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
    O_CSI *o_csi = new O_CSI();

    cout << "Setting O_CSI parameters:" << endl;
    cout << "-------------------------" << endl;

    // Setting mandatory parameter
    o_csi->SetO_BcsmCamelTDPDataList(InitializeO_BcsmCamelTDPDataList());

    // Ask user to include CamelCapabilityHandling
    cout << "Include CamelCapabilityHandling optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        o_csi->SetCamelCapabilityHandling(InitializeCamelCapabilityHandling());
    }

    cout << endl;
    return o_csi;
}


ODB_Data* InitializeODB_Data()
{
    ODB_Data *od = new ODB_Data();

    cout << "Setting ODB_Data parameters:" << endl;
    cout << "----------------------------" << endl;

    // Setting mandatory parameter
    od->SetOdb_GeneralData(InitializeODB_GeneralData());

    // Ask user to include Odb_HPLMN_Data
    cout << "Include Odb_HPLMN_Data optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        od->SetOdb_HPLMN_Data(InitializeODB_HPLMN_Data());
    }

    // Ask user to include ExtensionContainer
    cout << "Include ExtensionContainer optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        od->SetExtensionContainer(InitializeExtensionContainer());
    }

    cout << endl;
    return od;
}


ODB_GeneralData *InitializeODB_GeneralData()
{
    bool array[] = { true, false, true, false, true,
                     false, true, false, true, false,
                     true, false, true, false, true,
                     false, true, false, true, false,
                     true, false, true, false, true };

    ODB_GeneralData *ogd = 
        new ODB_GeneralData(ArrayToVector(array, ARRAY_SIZE(array)));

    return ogd;
}


ODB_HPLMN_Data* InitializeODB_HPLMN_Data()
{
    bool arr[] = { false, true, false, true };

    ODB_HPLMN_Data *ohd = 
        new ODB_HPLMN_Data(ArrayToVector(arr, ARRAY_SIZE(arr)));

    return ohd;
}


ActivateTraceModeArg::Omc_Id* InitializeOmc_Id()
{
    byte array1[] = { 0x01U, 0x02U, 0x03U, 0x04U }; 

    ActivateTraceModeArg::Omc_Id *oi = 
        new ActivateTraceModeArg::Omc_Id
        (ArrayToVector(array1, ARRAY_SIZE(array1)));

    return oi;
}


OR_Phase* InitializeOrCapability()
{
    long val = 0;
    OR_Phase *op;

    // Ask user to enter OR_Phase value
    cout << "Enter OR_Phase, integer (1..127): ";
    val = getSelection(1, 127);
    cout << endl;

    op = new OR_Phase(val);
    return op;
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

    cout << "Setting PDP_Context parameters:" << endl;
    cout << "-------------------------------" << endl;

    // Setting mandatory parameters
    pc->SetPdp_ContextId(InitializePdp_ContextId());
    pc->SetPdp_Type(InitializePdp_Type());
    pc->SetQos_Subscribed(InitializeQos_Subscribed());
    pc->SetApn(InitializeApn());

    //Ask user to include Pdp_Address
    cout <<"Include Pdp_Address optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        pc->SetPdp_Address(InitializePdp_Address());
    }
    
    //Ask user to include VplmnAddressAllowed
    cout <<"Include VplmnAddressAllowed optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        pc->SetVplmnAddressAllowed(InitializeVplmnAddressAllowed());
    }

    //Ask user to include ExtensionContainer
    cout <<"Include ExtensionContainer optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        pc->SetExtensionContainer(InitializeExtensionContainer());
    }

    cout << endl;
    return pc;
}


ContextId* InitializePdp_ContextId()
{
    long val = 0;
    ContextId *cid;

    // Ask user to provide ContextId value
    cout << "Enter ContextId, integer (1..50): ";
    val = getSelection(1, 50);
    cout << endl;

    cid = new ContextId(val);
    return cid;
}



PDP_Type* InitializePdp_Type()
{
    byte arr[] = { 0x01, 0x02 };

    PDP_Type *pt = new PDP_Type(ArrayToVector(arr, ARRAY_SIZE(arr)));

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
    ProcessGroupCallSignallingArg::ReleaseGroupCall *rgc =
        new ProcessGroupCallSignallingArg::ReleaseGroupCall();

    return rgc;
}


ProcessGroupCallSignallingArg::UplinkReleaseIndication*
InitializePGCSAUplinkReleaseIndication()
{
    ProcessGroupCallSignallingArg::UplinkReleaseIndication *uri =
        new ProcessGroupCallSignallingArg::UplinkReleaseIndication();

    return uri;
}


ProcessGroupCallSignallingArg::UplinkRequest*
InitializePGCSAUplinkRequest()
{
    ProcessGroupCallSignallingArg::UplinkRequest *ur =
        new ProcessGroupCallSignallingArg::UplinkRequest();

    return ur;
}


ProtocolId* InitializeProtocolId()
{
    long val = 0;
    ProtocolId *pid;

    // Ask user select a ProtocolId
    cout << "Select ProtocolId:" << endl;
    cout << "------------------" << endl;
    cout << "[1] gsm-0408" << endl;
    cout << "[2] gsm-0806" << endl;
    cout << "[3] gsm-BSSMAP (reserved, normally not to be used)" << endl;
    cout << "[4] ets-300102-1" << endl;
    cout << endl;
    val = getSelection(1, 4);
    cout << endl;

    pid = new ProtocolId(val);
    return pid;
}



InsertSubscriberDataArg::ProvisionedSS* InitializeProvisionedSS()
{
    return InitializeExt_SS_InfoList();
}


QoS_Subscribed* InitializeQos_Subscribed()
{
    byte arr[] = { 0x01, 0x02, 0x03 };

    QoS_Subscribed *qs = 
        new QoS_Subscribed(ArrayToVector(arr, ARRAY_SIZE(arr)));

    return qs;
}


RAND* InitializeRand()
{
    byte arr[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 
                   0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10 };

    RAND *r = new RAND(ArrayToVector(arr, ARRAY_SIZE(arr)));

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
    long val = 0;
    RegionalSubscriptionResponse *rsr;

    // Ask user to select RegionalSubscriptionResponse
    cout << "Select RegionalSubscriptionResponse:" << endl;
    cout << "------------------------------------" << endl;
    cout << "[0] networkNode-AreaRestricted" << endl;
    cout << "[1] tooManyZoneCodes" << endl;
    cout << "[2] zoneCodesConflict" << endl;
    cout << "[3] regionalSubscNotSupported" << endl;
    cout << endl;
    val = getSelection(0, 3);
    cout << endl;

    rsr = new RegionalSubscriptionResponse(val);
    return rsr;
}


RemoteUserFreeArg::ReplaceB_Number* InitializeReplaceB_Number()
{
    RemoteUserFreeArg::ReplaceB_Number *rbn =
        new RemoteUserFreeArg::ReplaceB_Number();

    return rbn;
}


RequestedInfo* InitializeRequestedInfo()
{
    RequestedInfo *ri = new RequestedInfo();

    cout << "Setting RequestedInfo parameters:" << endl;
    cout << "---------------------------------" << endl;
    
    // Ask user to include LocationInformation optional parameter
    cout << "Include LocationInformation optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        ri->SetLocationInformation(InitializeLocationInfo());
    }

    // Ask user to include SubscriberState optional parameter
    cout << "Include SubscriberState optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        ri->SetSubscriberState(InitializeSubscriber_State());
    }

    // Ask user to include ExtensionContainer optional parameter
    cout << "Include ExtensionContainer optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        ri->SetExtensionContainer(InitializeExtensionContainer());
    }

    cout << endl;
    return ri;
}


ResumeCallHandlingArg::Ccbs_Possible* InitializeRCHACcbs_Possible()
{
    ResumeCallHandlingArg::Ccbs_Possible* cp =
        new ResumeCallHandlingArg::Ccbs_Possible();

    return cp;
}

RoutingInfo* InitializeRoutingInfo()
{
    RoutingInfo *ri = new RoutingInfo();

    // Ask user to select RoutingInfo
    cout << "Select RoutingInfo:" << endl;
    cout << "-------------------" << endl;
    cout << "[1] RoamingNumber" << endl;
    cout << "[2] Forwarding Data" << endl;
    cout << endl;
    
    // Determine what the user selected
    if (getSelection(1, 2) == 1)
    {
        ri->SetChoiceRoamingNumber(InitializeRoamingNumber());
    }
    else
    {
        ri->SetChoiceForwardingData(InitializeForwardingData());
    }

    cout << endl;
    return ri;
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
    long val = 1;

    SupportedCCBS_Phase* supportedCCBS_Phase =
        new SupportedCCBS_Phase(val);

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

    TBCD_STRING *tbcd_str =
        new TBCD_STRING(ArrayToVector(array, ARRAY_SIZE(array)));

    return tbcd_str;
}


T_CSI* InitializeT_CSI()
{
    T_BcsmCamelTDPData* cameldata1 = new T_BcsmCamelTDPData();
    T_BcsmCamelTDPData* cameldata2 = new T_BcsmCamelTDPData();

    T_CSI *t_csi = new T_CSI();

    // Set cameldata1
    T_BcsmTriggerDetectionPoint* tbtdp = new T_BcsmTriggerDetectionPoint();
    tbtdp->SetTermAttemptAuthorized();

    cameldata1->SetT_BcsmTriggerDetectionPoint(tbtdp);
    cameldata1->SetServiceKey(InitializeServiceKey());
    cameldata1->SetGsmSCF_Address(InitializeGsmSCF_Address());
    cameldata1->SetDefaultCallHandling(InitializeDefaultCallHandling());


    T_BcsmCamelTDPDataList* camellist = new T_BcsmCamelTDPDataList();

    camellist->AddElement(cameldata1);

    t_csi->SetT_BcsmCamelTDPDataList(camellist);
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