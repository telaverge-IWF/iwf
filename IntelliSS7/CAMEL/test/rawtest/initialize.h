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
 ****************************************************************************/


#ifndef INITIALIZE_H
#define INITIALIZE_H

#include <its++.h>

#if !defined(HPUX)
#include <iostream>
#else
#include <iostream/iostream.h>
#endif


#include <AsnException.h>


// Header files for CAP message classes used in this this program

#include <cap_v3_apply_charging_arg.h>
#include <cap_v3_apply_charging_report_arg.h>
#include <cap_v3_assist_request_instructions_arg.h>
#include <cap_v3_call_gap_arg.h>
#include <cap_v3_call_information_request_arg.h>
#include <cap_v3_call_information_report_arg.h>
#include <cap_v3_initial_dp_arg.h>
#include <cap_v3_connect_to_resource_arg.h>
#include <cap_v3_connect_arg.h>
#include <cap_v3_cancel_arg.h>
#include <cap_v3_continue_with_argument_arg.h>
#include <cap_v3_establish_temporary_connection_arg.h>
#include <cap_v3_event_report_bcsm_arg.h>
#include <cap_v3_furnish_charging_information_arg.h>
#include <cap_v3_release_call_arg.h>
#include <cap_v3_request_report_bcsm_event_arg.h>
#include <cap_v3_reset_timer_arg.h>
#include <cap_v3_send_charging_information_arg.h>
#include <cap_v3_play_announcement_arg.h>
#include <cap_v3_prompt_and_collect_user_information_arg.h>
#include <cap_v3_received_information_arg.h>


#if defined(ITS_NAMESPACE)
using namespace std;
using namespace its;
using namespace cap;
using namespace cap_v3;
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

//
void getCharDigits(byte *byteArray, int len);

AChBillingChargingCharacteristics* InitializeAChBillingChargingCharacteristics();

AdditionalCallingPartyNumber* InitializeAdditionalCallingPartyNumber();

AlertingPattern* InitializeAlertingPattern();
/*
ApplicationTimer* InitializeApplicationTimer();
*/

BCSMEvent* InitializeBCSMEvent();

BearerCapability* InitializeBearerCapability();

BearerCapability::BearerCap* InitializeBearerCapability_BearerCap();

CalledPartyNumber* InitializeCalledPartyNumber();
/*
CallingPartyBusinessGroupID* InitializeCallingPartyBusinessGroupID();
*/
CallingPartysCategory* InitializeCallingPartysCategory();
/*
CallingPartySubaddress* InitializeCallingPartySubaddress();
*/
CallingPartyNumber* InitializeCallingPartyNumber();


CallResult* InitializeCallResult();
Cause* InitializeCause();

CGEncountered* InitializeCGEncountered();

CollectedInfo* InitializeCollectedInfo();
CollectedDigits::MinimumNbOfDigits* InitializeMinimumNbOfDigits();
CollectedDigits::MaximumNbOfDigits* InitializeMaximumNbOfDigits();
/*
ConnectArg::Extensions* InitializeConnectArg_Extensions();
*/

ControlType* InitializeControlType();

CorrelationID* InitializeCorrelationID();
/*
CutAndPaste* InitializeCutAndPaste();
*/

DestinationRoutingAddress* InitializeDestinationRoutingAddress();

Digits* InitializeDigits();

PlayAnnouncementArg::DisconnectFromIPForbidden* InitializeDisconnectFromIPForbidden();

PromptAndCollectUserInformationArg::DisconnectFromIPForbidden* 
		InitializePromptAndCollectUserInformation_DisconnectFromIPForbidden();

DpSpecificCriteria* InitializeDpSpecificCriteria();

Duration* InitializeDuration();

ErrorTreatment* InitializeErrorTreatment();

EventSpecificInformationBCSM* InitializeEventSpecificInformationBCSM();

EventSpecificInformationBCSM::RouteSelectFailureSpecificInfo*
InitializeEventSpecificInformationBCSM_RouteSelectFailureSpecificInfo();

EventTypeBCSM* InitializeEventTypeBCSM();

ForwardServiceInteractionInd*  InitializeForwardServiceInteractionInd();
/*
ExtensionField* InitializeExtensionField();

ExtensionField::Criticality* InitializeExtensionField_Criticality();

ExtensionField::Type* InitializeExtensionField_Type();

ExtensionField::Value* InitializeExtensionField_Value();
*/

FCIBillingChargingCharacteristics* InitializeFCIBillingChargingCharacteristics();

/*
ForwardingCondition* InitializeForwardingCondition();
*/

GapCriteria* InitializeGapCriteria();

GapIndicators* InitializeGapIndicators();

GapOnService* InitializeGapOnService();

GapTreatment* InitializeGapTreatment();

InformationToSend* InitializeInformationToSend();

/*
InitialDPArg::Extensions* InitializeInitialDPArg_Extensions();
*/

Integer4* InitializeInteger4();

CollectedDigits::InterruptableAnnInd* InitializeInterruptableAnnInd();

Interval* InitializeInterval();

LegID* InitializeReceivingLegID();

LegID* InitializeSendingLegID();

LegType* InitializeReceivingLegType();

LegType* InitializeSendingLegType();

LocationNumber* InitializeLocationNumber();

MiscCallInfo* InitializeMiscCallInfo();

MiscCallInfo::DpAssignment* InitializeMiscCallInfo_DpAssignment();

MiscCallInfo::MessageType* InitializeMiscCallInfo_MessageType();

MonitorMode* InitializeMonitorMode();

OriginalCalledPartyID* InitializeOriginalCalledPartyID();

/*
ReportCondition* InitializeReportCondition();
*/
PlayAnnouncementArg::DisconnectFromIPForbidden* InitializeDisconnectFromIPForbidden();
PlayAnnouncementArg::RequestAnnouncementComplete* InitializeRequestAnnouncementComplete();
/*
RequestedInformation* InitializeRequestedInformation();
*/

RequestedInformationList* InitializeRequestedInformationList();

RequestedInformationType* InitializeRequestedInformationType();

RequestedInformationTypeList* InitializeRequestedInformationTypeList();

RequestedInformationValue* InitializeRequestedInformationValue();

RequestReportBCSMEventArg::BcsmEvents*
InitializeRequestReportBCSMEventArg_BcsmEvents();


ConnectToResourceArg::ResourceAddress* InitializeResourceAddress();
/*
ResourceID::TrunkGroupID* InitializeResourceID_TrunkGroupID();

ResourceStatus* InitializeResourceStatus();

RouteList* InitializeRouteList();
*/
ScfID* InitializeScfID();

SCIBillingChargingCharacteristics* InitializeSciBillingChargingCharacteristics();

ServiceKey* InitializeServiceKey();

ServiceInteractionIndicatorsTwo* 
				InitializeServiceInteractionIndicatorsTwo();

TimerID* InitializeTimerID();

Tone* InitializeTone();

CollectedDigits::VoiceInformation* InitializeVoiceInformation();
CollectedDigits::VoiceBack* InitializeVoiceBack();

#endif // INITIALIZE_H