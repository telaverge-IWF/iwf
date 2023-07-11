#include <diameter/Exceptions.h>
#include <diameter/s6a/DeleteSubscriberData.h>

void testDeleteSubscriberDataRequest() {
    diameter::s6a::DeleteSubscriberDataRequest request;

    request.setSessionId(diameter::base::SessionId(...));
    request.setAuthSessionState(diameter::base::AuthSessionState(...));
    request.setOriginHost(diameter::base::OriginHost(...));
    request.setOriginRealm(diameter::base::OriginRealm(...));
    request.setDestinationHost(diameter::base::DestinationHost(...));
    request.setDestinationRealm(diameter::base::DestinationRealm(...));
    request.setUserName(diameter::base::UserName(...));
    request.setDSRFlags(DSRFlags(...));
    request.setVendorSpecificApplicationId(diameter::base::VendorSpecificApplicationId(...));
    request.setTraceReference(TraceReference(...));
    request.addTSCode(TSCode(...));
    request.addSSCode(SSCode(...));
    request.addSupportedFeatures(SupportedFeatures(...));
    request.addContextIdentifier(ContextIdentifier(...));
    request.addProxyInfo(diameter::base::ProxyInfo(...));
    request.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}

void testDeleteSubscriberDataAnswer() {
    diameter::s6a::DeleteSubscriberDataAnswer answer;

    answer.setSessionId(diameter::base::SessionId(...));
    answer.setAuthSessionState(diameter::base::AuthSessionState(...));
    answer.setOriginHost(diameter::base::OriginHost(...));
    answer.setOriginRealm(diameter::base::OriginRealm(...));
    answer.setVendorSpecificApplicationId(diameter::base::VendorSpecificApplicationId(...));
    answer.addSupportedFeatures(SupportedFeatures(...));
    answer.setResultCode(diameter::base::ResultCode(...));
    answer.setExperimentalResult(diameter::base::ExperimentalResult(...));
    answer.setDSAFlags(DSAFlags(...));
    answer.addFailedAVP(diameter::base::FailedAVP(...));
    answer.addProxyInfo(diameter::base::ProxyInfo(...));
    answer.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}
