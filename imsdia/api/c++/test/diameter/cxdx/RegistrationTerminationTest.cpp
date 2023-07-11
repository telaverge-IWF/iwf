#include <diameter/Exceptions.h>
#include <diameter/cxdx/RegistrationTermination.h>

void testRegistrationTerminationRequest() {
    diameter::cxdx::RegistrationTerminationRequest request;

    request.setSessionId(diameter::base::SessionId(...));
    request.setVendorSpecificApplicationId(diameter::base::VendorSpecificApplicationId(...));
    request.setAuthSessionState(diameter::base::AuthSessionState(...));
    request.setOriginHost(diameter::base::OriginHost(...));
    request.setOriginRealm(diameter::base::OriginRealm(...));
    request.setDestinationHost(diameter::base::DestinationHost(...));
    request.setDestinationRealm(diameter::base::DestinationRealm(...));
    request.setUserName(diameter::base::UserName(...));
    request.setDeregistrationReason(DeregistrationReason(...));
    request.setAssociatedIdentities(AssociatedIdentities(...));
    request.addSupportedFeatures(SupportedFeatures(...));
    request.addPublicIdentity(PublicIdentity(...));
    request.addProxyInfo(diameter::base::ProxyInfo(...));
    request.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}

void testRegistrationTerminationAnswer() {
    diameter::cxdx::RegistrationTerminationAnswer answer;

    answer.setSessionId(diameter::base::SessionId(...));
    answer.setVendorSpecificApplicationId(diameter::base::VendorSpecificApplicationId(...));
    answer.setAuthSessionState(diameter::base::AuthSessionState(...));
    answer.setOriginHost(diameter::base::OriginHost(...));
    answer.setOriginRealm(diameter::base::OriginRealm(...));
    answer.setResultCode(diameter::base::ResultCode(...));
    answer.setExperimentalResult(diameter::base::ExperimentalResult(...));
    answer.setAssociatedIdentities(AssociatedIdentities(...));
    answer.addSupportedFeatures(SupportedFeatures(...));
    answer.addFailedAVP(diameter::base::FailedAVP(...));
    answer.addProxyInfo(diameter::base::ProxyInfo(...));
    answer.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}
