#include <diameter/Exceptions.h>
#include <diameter/s6a_r10/UpdateLocation.h>

void testUpdateLocationRequest() {
    diameter::s6a_r10::UpdateLocationRequest request;

    request.setSessionId(diameter::base::SessionId(...));
    request.setAuthSessionState(diameter::base::AuthSessionState(...));
    request.setOriginHost(diameter::base::OriginHost(...));
    request.setOriginRealm(diameter::base::OriginRealm(...));
    request.setDestinationRealm(diameter::base::DestinationRealm(...));
    request.setUserName(diameter::base::UserName(...));
    request.setULRFlags(ULRFlags(...));
    request.setVisitedPLMNId(VisitedPLMNId(...));
    request.setRATType(RATType(...));
    request.setVendorSpecificApplicationId(diameter::base::VendorSpecificApplicationId(...));
    request.setSGSNNumber(SGSNNumber(...));
    request.setDestinationHost(diameter::base::DestinationHost(...));
    request.addSupportedFeatures(SupportedFeatures(...));
    request.setTerminalInformation(TerminalInformation(...));
    request.setUESRVCCCapability(UESRVCCCapability(...));
    request.setHomogeneousSupportofIMSVoiceOverPSSessions(HomogeneousSupportofIMSVoiceOverPSSessions(...));
    request.setGMLCAddress(GMLCAddress(...));
    request.addActiveAPN(ActiveAPN(...));
    request.addProxyInfo(diameter::base::ProxyInfo(...));
    request.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}

void testUpdateLocationAnswer() {
    diameter::s6a_r10::UpdateLocationAnswer answer;

    answer.setSessionId(diameter::base::SessionId(...));
    answer.setAuthSessionState(diameter::base::AuthSessionState(...));
    answer.setOriginHost(diameter::base::OriginHost(...));
    answer.setOriginRealm(diameter::base::OriginRealm(...));
    answer.setVendorSpecificApplicationId(diameter::base::VendorSpecificApplicationId(...));
    answer.setULAFlags(ULAFlags(...));
    answer.setResultCode(diameter::base::ResultCode(...));
    answer.setExperimentalResult(diameter::base::ExperimentalResult(...));
    answer.setErrorDiagnostic(ErrorDiagnostic(...));
    answer.addSupportedFeatures(SupportedFeatures(...));
    answer.setSubscriptionData(SubscriptionData(...));
    answer.addFailedAVP(diameter::base::FailedAVP(...));
    answer.addProxyInfo(diameter::base::ProxyInfo(...));
    answer.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}
