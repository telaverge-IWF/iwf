////////////////////////////////////////////////////////////////////////////////
//
// Tool functions for the testing of GSSMAPPlus
//
////////////////////////////////////////////////////////////////////////////////

#if !defined(_TOOLS_H_)
#define _TOOLS_H_

#include <AsnException.h>

// MS part
#include <CancelLocationArg.h>
#include <CancelLocationRes.h>
#include <SendIdentificationRes.h>
#include <TMSI.h>     // Arg: SendIdentification
#include <PurgeMS_Arg.h>
#include <PurgeMS_Res.h>
#include <UpdateGprsLocationArg.h>
#include <UpdateGprsLocationRes.h>
#include <PrepareHO_Arg.h>
#include <PrepareHO_Res.h>
// SendEndSignal / ProcessAccessSignaling / ForwardAccessSignaling
// Arg: bss-APDU ExternalSignalInfo    Res: None
#include <PrepareSubsequentHO_Arg.h> // Res: bss-APDU ExternalSignalInfo
#include <SendAuthenticationInfoArg.h>
#include <SendAuthenticationInfoRes.h>
#include <IMEI.h> // Arg: CheckIMEI
#include <EquipmentStatus.h>   // Res: CheckIMEI
#include <InsertSubscriberDataArg.h>
#include <InsertSubscriberDataRes.h>
#include <DeleteSubscriberDataArg.h>
#include <DeleteSubscriberDataRes.h>
#include <ResetArg.h> // Res
// ForwardCheckSSIndication
#include <RestoreDataArg.h>
#include <RestoreDataRes.h>
#include <ProvideSubscriberInfoArg.h>
#include <ProvideSubscriberInfoRes.h>
#include <SendRoutingInfoForGprsArg.h>
#include <SendRoutingInfoForGprsRes.h>
#include <FailureReportArg.h>
#include <FailureReportRes.h>
#include <NoteMsPresentForGprsArg.h>
#include <NoteMsPresentForGprsRes.h>
#include <UpdateLocationArg.h>
#include <UpdateLocationRes.h>
#include <AnyTimeInterrogationArg.h>
#include <AnyTimeInterrogationRes.h>

// OM part
#include <ActivateTraceModeRes.h>
#include <ActivateTraceModeArg.h>
#include <DeactivateTraceModeRes.h>
#include <DeactivateTraceModeArg.h>


// CH part
#include <SendRoutingInfoArg.h>
#include <SendRoutingInfoRes.h>
#include <ProvideRoamingNumberArg.h>
#include <ProvideRoamingNumberRes.h>
#include <SetReportingStateArg.h>
#include <SetReportingStateRes.h>
#include <StatusReportArg.h>
#include <StatusReportRes.h>
#include <RemoteUserFreeArg.h>
#include <RemoteUserFreeRes.h>
#include <SIWFSSignallingModifyArg.h>
#include <SIWFSSignallingModifyRes.h>
#include <ProvideSIWFSNumberArg.h>
#include <ProvideSIWFSNumberRes.h>
#include <ResumeCallHandlingArg.h>
#include <ResumeCallHandlingRes.h>

// SS part
#include <RegisterSS_Arg.h>  // Res : SS_Info
#include <SS_ForBS_Code.h>  // Arg:  EraseSS/ActivateSS/DeactivateSS
#include <SS_Info.h>  // Res:  EraseSS/ActivateSS/DeactivateSS
#include <InterrogateSS_Res.h>  // Arg : SS_ForBS_Code
// RegisterPassword  // Arg: SS_Code   Res: Password
#include <GuidanceInfo.h>
// GetPassword    // Arg: GuidanceInfo   Res: Password
#include <USSD_Arg.h>   // Arg for ProcessUnstructuredSSRequest
                        // UnstructuredSS_Request / UnstructuredSS_Notify
#include <USSD_Res.h>   // Res for ProcessUnstructuredSSRequest 
                        //         UnstructuredSSRequest
#include <RegisterCC_EntryArg.h>
#include <RegisterCC_EntryRes.h>
#include <EraseCC_EntryArg.h>
#include <EraseCC_EntryRes.h>
#include <SS_InvocationNotificationArg.h>
#include <SS_InvocationNotificationRes.h>

// SM part
#include <RoutingInfoForSM_Arg.h>
#include <RoutingInfoForSM_Res.h> // SendRoutingInfoForSM
#include <MO_ForwardSM_Arg.h>
#include <MO_ForwardSM_Res.h>
#include <ReportSM_DeliveryStatusArg.h>
#include <ReportSM_DeliveryStatusRes.h>
#include <ReadyForSM_Arg.h>
#include <ReadyForSM_Res.h>
#include <MT_ForwardSM_Arg.h>
#include <MT_ForwardSM_Res.h>
#include <AlertServiceCentreArg.h>
#include <InformServiceCentreArg.h>

// GC part
#include <PrepareGroupCallArg.h>
#include <PrepareGroupCallRes.h>
#include <SendGroupCallEndSignalArg.h>
#include <SendGroupCallEndSignalRes.h>
#include <ForwardGroupCallSignallingArg.h>
#include <ProcessGroupCallSignallingArg.h>




#if defined(ITS_NAMESPACE)
using namespace its;
#endif    // defined(ITS_NAMESPACE)

static bool testPrint = true;

//
// Macro to get size (count of items) of a statically dimensioned array.
//
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))


// Function template to convert arrays to vectors.
template <typename T> inline std::vector<T> ArrayToVector(T array[], size_t size)
{ return std::vector<T>(array, array + size); }



// Helper operator<< to print content of vector of bytes.

static std::string ByteToHexString(byte b);

std::ostream& operator<< (std::ostream& os, const std::vector<byte>& vect);

//////////////////////////////////////////////////////////////////
//      Message Encode and Decode general functions
//////////////////////////////////////////////////////////////////
void MsgEncode(AsnObject* p, Octets** octets, std::string& str);
void MsgDecode(AsnObject* p, Octets* octets, std::string& str);
void CompareStrings(const std::string& str1, const std::string& str2);

//////////////////////////////////////////////////////////////////
//      Initialize Parameters
///////////////////////////////////////////////////////////////////
AbsentSubscriberDiagnosticSM* InitializeAbsentSubscriberDiagnosticSM();

ActivateTraceModeArg::Omc_Id* InitializeOmc_Id();

Additional_Number* InitializeAdditional_Number();

AddressString* InitializeAddressString();

AddressString* InitializeForwardedToNumber();

AgeOfLocationInformation* InitializeAgeOfLocationInformation();

AlertingPattern* InitializeAlertingPattern();

AlertReason* InitializeAlertReason();

ReadyForSM_Arg::AlertReasonIndicator* InitializeAlertReasonIndicator();

GPRSSubscriptionDataWithdraw::AllGPRSData* InitializeAllGprsData();

AuthenticationSet* InitializeAuthenticationSet();

AuthenticationSetList* InitializeAuthenticationSetList();

ForwardingData* InitializeForwardingData();

BasicServiceCode* InitializeBasicServiceCode();

BasicServiceCriteria* InitializeBasicServiceCriteria();

BasicServiceList* InitializeBasicServiceList();

BearerServiceCode* InitializeBearerService();

BasicServiceGroupList* InitializeBasicServiceGroupList();

BearerServiceList* InitializeBearerServiceList();

CallDirection* InitializeCallDirection();

CallOutcome* InitializeCallOutcome();

CallReferenceNumber* InitializeCallReferenceNumber();

CallReportData* InitializeCallReportData();

CallTypeCriteria* InitializeCallTypeCriteria();

SubscriberState::CamelBusy* InitializeCamelBusy();

CamelCapabilityHandling* InitializeCamelCapabilityHandling();

CamelInfo* InitializeCamelInfo();

CamelRoutingInfo* InitializeCamelRoutingInfo();

CancellationType* InitializeCancellationType();

Category* InitializeCategory();

CCBS_Data* InitializeCcbs_Data();

CCBS_Data::CallInfo* InitializeCallInfo();

CCBS_Data::NetworkSignalInfo* InitializeNetworkSignalInfo();

CCBS_Data::TranslatedB_Number* InitializeTranslatedB_Number();

CCBS_Feature* InitializeCcbs_Feature();

CCBS_Feature::B_subscriberNumber* InitializeB_subscriberNumber();

CCBS_Feature::B_subscriberSubaddress* InitializeB_subscriberSubaddress();

CCBS_Index* InitializeCcbs_Index();

CCBS_Indicators* InitializeCCBS_Indicators();

CCBS_Indicators::Ccbs_Possible* InitializeCcbs_Possible();

CCBS_Indicators::KeepCCBS_CallIndicator* InitializeKeepCCBS_CallIndicator();

CCBS_SubscriberStatus* InitializeCCBS_SubscriberStatus();

CellIdFixedLength* InitializeCellIdFixedLength();

CellIdOrLAI* InitializeCellIdOrLAI();

CipheringAlgorithm* InitializeCipheringAlgorithm();

CODEC_Info* InitializeCODEC_Info();

ContextId* InitializePdp_ContextId();

CUG_CheckInfo* InitializeCUG_CheckInfo();

CUG_Interlock* InitializeCUG_Interlock();

DefaultCallHandling* InitializeDefaultCallHandling();

DeleteSubscriberDataArg::CamelSubscriptionInfoWithdraw*
InitializeCamelSubscriptionInfoWithdraw();

DeleteSubscriberDataArg::RoamingRestrictedInSgsnDueToUnsuppportedFeature*
InitializeRoamingRestrictedInSgsnDueToUnsuppportedFeature();

ReportSM_DeliveryStatusArg::DeliveryOutcomeIndicator*
InitializeDeliveryOutcomeIndicator();

DestinationNumberCriteria* InitializeDestinationNumberCriteria();

EMLPP_Priority* InitializeEmlpp_Priority();

EventReportData* InitializeEventReportData();

Ext_BasicServiceCode* InitializeBasicServiceGroup();

Ext_BasicServiceCode* InitializeExt_BasicServiceCode();

Ext_BearerServiceCode* InitializeExt_BearerServiceCode();

Ext_SS_Data* InitializeExt_SS_Data();

Ext_SS_Info* InitializeExt_SS_Info_Choice_CUG_Info();

Ext_SS_Info* InitializeExt_SS_Info_Choice_Ext_ForwInfo();

Ext_SS_Info* InitializeExt_SS_Info_Choice_Ext_SS_Data();

Ext_SS_Status* InitializeExt_SS_Status();

Ext_SS_InfoList* InitializeExt_SS_InfoList();

Ext_TeleserviceCode* InitializeExt_TeleserviceCode();

ExtendedRoutingInfo* InitializeExtendedRoutingInfo();

ExtensionContainer* InitializeExtensionContainer();

ExternalSignalInfo* InitializeExternalSignalInfo();

ExternalSignalInfo* InitializeGsm_BearerCapability();

ForwardGroupCallSignallingArg::UplinkRejectCommand*
InitializeFGCSAUplinkRejectCommand();

ForwardGroupCallSignallingArg::UplinkReleaseCommand*
InitializeFGCSAUplinkReleaseCommand();

ForwardGroupCallSignallingArg::UplinkReleaseIndication*
InitializeFGCSAUplinkReleaseIndication();

ForwardGroupCallSignallingArg::UplinkRequestAck*
InitializeFGCSAUplinkRequestAck();

ForwardGroupCallSignallingArg::UplinkSeizedCommand*
InitializeFGCSAUplinkSeizedCommand();

ForwardingOptions* InitializeForwardingOptions();

ForwardingReason* InitializeForwardingReason();

GeographicalInformation* InitializeGeographicalInformation();

SendRoutingInfoForGprsArg::Ggsn_Address* InitializeGgsn_Address();

FailureReportArg::Ggsn_Number* InitializeGgsn_Number();

GlobalCellId* InitializeGlobalCellId();

GmscCamelSubscriptionInfo* InitializeGmscCamelSubscriptionInfo();

GPRSDataList* InitializeGprsDataList();

LocationInfoWithLMSI::GprsNodeIndicator* InitializeGprsNodeIndicator();

GPRSSubscriptionData* InitializeGprsSubscriptionData();

GPRSSubscriptionDataWithdraw* InitializeGprsSubscriptionDataWithdraw();

RoutingInfoForSM_Arg::GprsSupportIndicator*
InitializeGprsSupportIndicator();

GroupId* InitializeGroupId();

GroupKeyNumber* InitializeGroupKeyNumber();

GSN_Address* InitializeGSN_Address();

HLR_Id* InitializeHLR_Id();

HLR_List* InitializeHLR_List();

Identity* InitializeIdentity();

IMSI* InitializeIMSI();

InsertSubscriberDataArg::Msisdn* InitializeMsisdn();

InsertSubscriberDataArg::ProvisionedSS* InitializeProvisionedSS();

InsertSubscriberDataArg::RegionalSubscriptionData* 
    InitializeRegionalSubscriptionData();

InsertSubscriberDataArg::RoamingRestrictedInSgsnDueToUnsupportedFeature*
    InitializeRoamingRestrictedInSgsnDueToUnsupportedFeature();

InsertSubscriberDataArg::RoamingRestrictionDueToUnsupportedFeature*
    InitializeRoamingRestrictionDueToUnsupportedFeature();

InsertSubscriberDataArg::VbsSubscriptionData* 
    InitializeVbsSubscriptionData();

InsertSubscriberDataArg::VgcsSubscriptionData* 
    InitializeVgcsSubscriptionData();

InterrogationType* InitializeInterrogationType();

ISDN_AddressString* InitializeISDN_AddressString();

ISDN_AddressString* InitializeGsmSCF_Address();

ISDN_AddressString* InitializeMsc_Number();

ISDN_AddressString* InitializeRoamingNumber();

ISDN_AddressString* InitializeVmsc_Address();

ISDN_SubaddressString* InitializeForwardedToSubaddress();

Kc* InitializeKc();

LMSI* InitializeLMSI();

RequestedInfo::LocationInformation* InitializeLocationInfo();

LocationInformation* InitializeLocationInformation();

LocationInfoWithLMSI* InitializeLocationInfoWithLMSI();

LocationNumber* InitializeLocationNumber();

MatchType* InitializeMatchType();

MonitoringMode* InitializeMonitoringMode();

MT_ForwardSM_Arg::MoreMessagesToSend* InitializeMoreMessagesToSend();

SendRoutingInfoForGprsRes::MobileNotReachableReason*
InitializeMobileNotReachableReason();

RestoreDataRes::MsNotReachable* InitializeMsNotReachable();

MW_Status* InitializeMW_Status();

NAEA_CIC* InitializeNaea_PreferredCIC();

NAEA_PreferredCI* InitializeNaea_PreferredCI();

NetworkAccessMode* InitializeNetworkAccessMode();

LocationInfoWithLMSI::NetworkNode_Number* InitializeNetworkNode_Number();

NoReplyConditionTime* InitializeNoReplyConditionTime();

NumberOfForwarding* InitializeNumberOfForwarding();

O_BcsmCamelTDP_Criteria* InitializeO_BcsmCamelTDP_Criteria();

O_BcsmCamelTDPDataList* InitializeO_BcsmCamelTDPDataList();

O_BcsmTriggerDetectionPoint* InitializeO_BcsmTriggerDetectionPoint();

O_CSI* InitializeO_CSI();

ODB_Data* InitializeODB_Data();

ODB_GeneralData* InitializeODB_GeneralData();

ODB_HPLMN_Data* InitializeODB_HPLMN_Data();

OR_Phase* InitializeOrCapability();

PDP_Context* InitializePDP_Context();

PDP_Context::VplmnAddressAllowed* InitializeVplmnAddressAllowed();

PDP_Type* InitializePdp_Type();

PrepareGroupCallArg::UplinkFree* InitializeUplinkFree();

PrepareHO_Arg::Bss_APDU* InitializeBss_APDU();

PrepareHO_Arg::Ho_NumberNotRequired* InitializeHo_NumberNotRequired();

PrepareHO_Arg::TargetCellId* InitializeTargetCellId();

ProcessGroupCallSignallingArg::ReleaseGroupCall*
InitializePGCSAReleaseGroupCall();

ProcessGroupCallSignallingArg::UplinkReleaseIndication*
InitializePGCSAUplinkReleaseIndication();

ProcessGroupCallSignallingArg::UplinkRequest*
InitializePGCSAUplinkRequest();

ProtocolId* InitializeProtocolId();

ProvideRoamingNumberArg::Ccbs_Call* InitializePRNACcbs_Call();

ProvideRoamingNumberArg::Or_Interrogation* InitializePRNAOr_Interrogation();

PurgeMS_Arg::Sgsn_Number* InitializeSgsn_Number();

PurgeMS_Arg::Vlr_Number* InitializeVlr_Number();

PurgeMS_Res::FreezeP_TMSI* InitializeFreezeP_TMSI();

PurgeMS_Res::FreezeTMSI* InitializeFreezeTMSI();

PrepareHO_Res::HandoverNumber* InitializeHandoverNumber();

PrepareSubsequentHO_Arg::TargetMSC_Number* InitializeTargetMSC_Number();

QoS_Subscribed* InitializeQos_Subscribed();

RAND* InitializeRand();

DeleteSubscriberDataArg::RegionalSubscriptionIdentifier*
InitializeRegionalSubscriptionIdentifier();

RequestedInfo* InitializeRequestedInfo();

RegionalSubscriptionResponse* InitializeRegionalSubscriptionResponse();

RegisterSS_Arg::BasicService* InitializeBasicService();

RegisterSS_Arg::ForwardedToNumber* IntializeForwardedToNumber();

RegisterSS_Arg::ForwardedToSubaddress* IntializeForwardedToSubaddress();

RemoteUserFreeArg::ReplaceB_Number* InitializeReplaceB_Number();

ReportingState* InitializeReportingState();

ResumeCallHandlingArg::Ccbs_Possible* InitializeRCHACcbs_Possible();

RoutingInfo* InitializeRoutingInfo();

RUF_Outcome* InitializeRUF_Outcome();

SendRoutingInfoArg::Ccbs_Call* InitializeCcbs_Call();

SendRoutingInfoArg::Or_Interrogation* InitializeOr_Interrogation();

SendRoutingInfoArg::NetworkSignalInfo* InitializeNetworkSignalInfo2();

SendRoutingInfoRes::CugSubscriptionFlag* InitializeCugSubscriptionFlag();

SendRoutingInfoRes::ForwardingInterrogationRequired*
    InitializeForwardingInterrogationRequired();

RoutingInfoForSM_Arg::ServiceCentreAddress*
InitializeServiceCentreAddress();

ServiceIndicator* InitializeServiceIndicator();

ServiceKey* InitializeServiceKey();

SignalInfo* InitializeSignalInfo();

SM_DeliveryOutcome* InitializeSM_DeliveryOutcome();

SM_RP_DA* InitializeSm_RP_DA();

SM_RP_MTI* InitializeSm_RP_MTI();

SM_RP_OA* InitializeSm_RP_OA();

MO_ForwardSM_Arg::Sm_RP_UI* InitializeSm_RP_UI();

RoutingInfoForSM_Arg::Sm_RP_PRI* InitializeSm_RP_PRI();

SM_RP_SMEA* InitializeSm_RP_SMEA();

SRES* InitializeSres();

SS_CamelData::GsmSCF_Address* InitializeGSMSCF_Address();

SS_Code* InitializeSS_Code();

SS_CSI* InitializeSS_CSI();

SS_Data* InitializeSS_Data();

SS_Data::DefaultPriority* InitializeDefaultPriority();

SS_EventList* InitializeSS_EventList();

SS_EventSpecification* InitializeSS_EventSpecification();

SS_List* InitializeSS_List();

SS_Status* InitializeSS_Status();

SS_SubscriptionOption* InitializeSS_SubscriptionOption();

SubscriberInfo* InitializeSubscriberInfo();

SubscriberIdentity* InitializeSubscriberIdentity();

SubscriberState* InitializeSubscriberState();

RequestedInfo::SubscriberState* InitializeSubscriber_State();

SubscriberState::AssumedIdle* InitializeAssumedIdle();

SubscriberStatus* InitializeSubscriberStatus();

SupportedCamelPhases* InitializeSupportedCamelPhases();

SupportedCCBS_Phase* InitializeSupportedCCBS_Phase();

SuppressionOfAnnouncement* InitializeSuppressionOfAnnouncement();

T_CSI* InitializeT_CSI();

TBCD_STRING* InitializeAsciCallReference();

TeleserviceList* InitializeTeleserviceList();

TraceReference* InitializeTraceReference();

TraceType* InitializeTraceType();

UpdateGprsLocationArg::Sgsn_Address* InitializeSgsn_Address();

UpdateGprsLocationRes::Hlr_Number* InitializeHlr_Number();

USSD_DataCodingScheme* InitializeUssd_DataCodingScheme();

USSD_String* InitializeUssd_String();

VBSDataList* InitializeVbsDataList();

DeleteSubscriberDataArg::VbsGroupIndication*
InitializeVbsGroupIndication();

VGCSDataList* InitializeVgcsDataList();

DeleteSubscriberDataArg::VgcsGroupIndication*
InitializeVgcsGroupIndication();

VlrCamelSubscriptionInfo* InitializeVlrCamelSubscriptionInfo();

VLR_Capability* InitializeVLR_Capability();

VoiceBroadcastData* InitializeVoiceBroadcastData();

VoiceBroadcastData::BroadcastInitEntitlement* 
    InitializeBroadcastInitEntitlement();

VoiceGroupCallData* InitializeVoiceGroupCallData();

ZoneCode* InitializeZoneCode();

ZoneCodeList* InitializeZoneCodeList();


#endif //!defined(_TOOLS_H_)