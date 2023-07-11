#include <diameter/Exceptions.h>
#include <diameter/s6a/Notify.h>

void testNotifyRequest() {
    diameter::s6a::NotifyRequest request;

    request.setSessionId(diameter::base::SessionId(...));
    request.setAuthSessionState(diameter::base::AuthSessionState(...));
    request.setOriginHost(diameter::base::OriginHost(...));
    request.setOriginRealm(diameter::base::OriginRealm(...));
    request.setDestinationRealm(diameter::base::DestinationRealm(...));
    request.setUserName(diameter::base::UserName(...));
    request.setVendorSpecificApplicationId(diameter::base::VendorSpecificApplicationId(...));
    request.setDestinationHost(diameter::base::DestinationHost(...));
    request.addSupportedFeatures(SupportedFeatures(...));
    request.setTerminalInformation(TerminalInformation(...));
    request.setNORFlags(NORFlags(...));
    request.setMIP6AgentInfo(MIP6AgentInfo(...));
    request.setContextIdentifier(ContextIdentifier(...));
    request.setServiceSelection(ServiceSelection(...));
    request.setAlertReason(AlertReason(...));
    request.addProxyInfo(diameter::base::ProxyInfo(...));
    request.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}

void testNotifyAnswer() {
    diameter::s6a::NotifyAnswer answer;

    answer.setSessionId(diameter::base::SessionId(...));
    answer.setAuthSessionState(diameter::base::AuthSessionState(...));
    answer.setOriginHost(diameter::base::OriginHost(...));
    answer.setOriginRealm(diameter::base::OriginRealm(...));
    answer.setVendorSpecificApplicationId(diameter::base::VendorSpecificApplicationId(...));
    answer.setResultCode(diameter::base::ResultCode(...));
    answer.setExperimentalResult(diameter::base::ExperimentalResult(...));
    answer.addSupportedFeatures(SupportedFeatures(...));
    answer.addFailedAVP(diameter::base::FailedAVP(...));
    answer.addProxyInfo(diameter::base::ProxyInfo(...));
    answer.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}
