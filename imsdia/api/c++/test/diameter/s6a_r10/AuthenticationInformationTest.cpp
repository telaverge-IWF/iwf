#include <diameter/Exceptions.h>
#include <diameter/s6a_r10/AuthenticationInformation.h>

void testAuthenticationInformationRequest() {
    diameter::s6a_r10::AuthenticationInformationRequest request;

    request.setSessionId(diameter::base::SessionId(...));
    request.setAuthSessionState(diameter::base::AuthSessionState(...));
    request.setOriginHost(diameter::base::OriginHost(...));
    request.setOriginRealm(diameter::base::OriginRealm(...));
    request.setDestinationRealm(diameter::base::DestinationRealm(...));
    request.setUserName(diameter::base::UserName(...));
    request.setVisitedPLMNId(VisitedPLMNId(...));
    request.setVendorSpecificApplicationId(diameter::base::VendorSpecificApplicationId(...));
    request.setRequestedEUTRANAuthenticationInfo(RequestedEUTRANAuthenticationInfo(...));
    request.setRequestedUTRANGERANAuthenticationInfo(RequestedUTRANGERANAuthenticationInfo(...));
    request.setDestinationHost(diameter::base::DestinationHost(...));
    request.addSupportedFeatures(SupportedFeatures(...));
    request.addProxyInfo(diameter::base::ProxyInfo(...));
    request.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}

void testAuthenticationInformationAnswer() {
    diameter::s6a_r10::AuthenticationInformationAnswer answer;

    answer.setSessionId(diameter::base::SessionId(...));
    answer.setAuthSessionState(diameter::base::AuthSessionState(...));
    answer.setOriginHost(diameter::base::OriginHost(...));
    answer.setOriginRealm(diameter::base::OriginRealm(...));
    answer.setVendorSpecificApplicationId(diameter::base::VendorSpecificApplicationId(...));
    answer.setResultCode(diameter::base::ResultCode(...));
    answer.setExperimentalResult(diameter::base::ExperimentalResult(...));
    answer.setErrorDiagnostic(ErrorDiagnostic(...));
    answer.addSupportedFeatures(SupportedFeatures(...));
    answer.setAuthenticationInfo(AuthenticationInfo(...));
    answer.addFailedAVP(diameter::base::FailedAVP(...));
    answer.addProxyInfo(diameter::base::ProxyInfo(...));
    answer.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}
