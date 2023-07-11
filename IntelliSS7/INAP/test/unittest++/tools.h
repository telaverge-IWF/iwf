#ifndef INAP_TOOLS_H
#define INAP_TOOLS_H


#include <AsnException.h>


/****************************************************************
 *               INAP Message Class Definitions
 ****************************************************************/

#include <InitialDPArg.h>
#include <ConnectArg.h>
#include <RequestReportBCSMEventArg.h>
#include <EventReportBCSMArg.h>
#include <RequestEveryStatusChangeReportArg.h>
#include <StatusReportArg.h>
#include <CancelStatusReportRequestArg.h>
#include <RequestFirstStatusMatchReportArg.h>
#include <RequestCurrentStatusReportResultArg.h>
#include <CallGapArg.h>
#include <CallInformationRequestArg.h>
#include <CallInformationReportArg.h>


/****************************************************************
 *                      Helper functions
 ****************************************************************/

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



/****************************************************************
 *                   Initialize Functions
 ****************************************************************/

AdditionalCallingPartyNumber* InitializeAdditionalCallingPartyNumber();

AlertingPattern* InitializeAlertingPattern();

ApplicationTimer* InitializeApplicationTimer();

BCSMEvent* InitializeBCSMEvent();

BearerCapability* InitializeBearerCapability();

BearerCapability::BearerCap* InitializeBearerCapability_BearerCap();

CalledPartyNumber* InitializeCalledPartyNumber();

CallingPartyBusinessGroupID* InitializeCallingPartyBusinessGroupID();

CallingPartysCategory* InitializeCallingPartysCategory();

CallingPartySubaddress* InitializeCallingPartySubaddress();

CallingPartyNumber* InitializeCallingPartyNumber();

Cause* InitializeCause();

CGEncountered* InitializeCGEncountered();

ConnectArg::Extensions* InitializeConnectArg_Extensions();

ControlType* InitializeControlType();

CorrelationID* InitializeCorrelationID();

CutAndPaste* InitializeCutAndPaste();

DestinationRoutingAddress* InitializeDestinationRoutingAddress();

Digits* InitializeDigits();

DpSpecificCriteria* InitializeDpSpecificCriteria();

Duration* InitializeDuration();

EventSpecificInformationBCSM* InitializeEventSpecificInformationBCSM();

EventSpecificInformationBCSM::CollectedInfoSpecificInfo*
InitializeEventSpecificInformationBCSM_CollectedInfoSpecificInfo();

EventTypeBCSM* InitializeEventTypeBCSM();

ExtensionField* InitializeExtensionField();

ExtensionField::Criticality* InitializeExtensionField_Criticality();

ExtensionField::Type* InitializeExtensionField_Type();

ExtensionField::Value* InitializeExtensionField_Value();

ForwardingCondition* InitializeForwardingCondition();

GapCriteria* InitializeGapCriteria();

GapIndicators* InitializeGapIndicators();

GapOnService* InitializeGapOnService();

GapTreatment* InitializeGapTreatment();

GapTreatment::Both* InitializeGapTreatment_Both();

InformationToSend* InitializeInformationToSend();

InitialDPArg::Extensions* InitializeInitialDPArg_Extensions();

Integer4* InitializeInteger4();

Integer4* InitializeServiceKey();

Interval* InitializeInterval();

LegID* InitializeLegID();

LegType* InitializeLegType();

LocationNumber* InitializeLocationNumber();

MiscCallInfo* InitializeMiscCallInfo();

MiscCallInfo::DpAssignment* InitializeMiscCallInfo_DpAssignment();

MiscCallInfo::MessageType* InitializeMiscCallInfo_MessageType();

MonitorMode* InitializeMonitorMode();

ReportCondition* InitializeReportCondition();

RequestedInformation* InitializeRequestedInformation();

RequestedInformationList* InitializeRequestedInformationList();

RequestedInformationType* InitializeRequestedInformationType();

RequestedInformationTypeList* InitializeRequestedInformationTypeList();

RequestedInformationValue* InitializeRequestedInformationValue();

RequestReportBCSMEventArg::BcsmEvents*
InitializeRequestReportBCSMEventArg_BcsmEvents();

ResourceID* InitializeResourceID();

ResourceID::TrunkGroupID* InitializeResourceID_TrunkGroupID();

ResourceStatus* InitializeResourceStatus();

RouteList* InitializeRouteList();

ScfID* InitializeScfID();

Tone* InitializeTone();


#endif // INAP_TOOLS_H