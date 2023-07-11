#include <diameter/Exceptions.h>
#include <diameter/cxdx/UserAuthorization.h>

void testUserAuthorizationRequest() {
    diameter::cxdx::UserAuthorizationRequest request;

    request.setSessionId(diameter::base::SessionId(...));
    request.setVendorSpecificApplicationId(diameter::base::VendorSpecificApplicationId(...));
    request.setAuthSessionState(diameter::base::AuthSessionState(...));
    request.setOriginHost(diameter::base::OriginHost(...));
    request.setOriginRealm(diameter::base::OriginRealm(...));
    request.setDestinationRealm(diameter::base::DestinationRealm(...));
    request.setUserName(diameter::base::UserName(...));
    request.setPublicIdentity(PublicIdentity(...));
    request.setVisitedNetworkIdentifier(VisitedNetworkIdentifier(...));
    request.setDestinationHost(diameter::base::DestinationHost(...));
    request.addSupportedFeatures(SupportedFeatures(...));
    request.setUserAuthorizationType(UserAuthorizationType(...));
    request.addProxyInfo(diameter::base::ProxyInfo(...));
    request.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}

void testUserAuthorizationAnswer() {
    diameter::cxdx::UserAuthorizationAnswer answer;

    answer.setSessionId(diameter::base::SessionId(...));
    answer.setVendorSpecificApplicationId(diameter::base::VendorSpecificApplicationId(...));
    answer.setAuthSessionState(diameter::base::AuthSessionState(...));
    answer.setOriginHost(diameter::base::OriginHost(...));
    answer.setOriginRealm(diameter::base::OriginRealm(...));
    answer.setResultCode(diameter::base::ResultCode(...));
    answer.setExperimentalResult(diameter::base::ExperimentalResult(...));
    answer.addSupportedFeatures(SupportedFeatures(...));
    answer.setServerName(ServerName(...));
    answer.setServerCapabilities(ServerCapabilities(...));
    answer.addFailedAVP(diameter::base::FailedAVP(...));
    answer.addProxyInfo(diameter::base::ProxyInfo(...));
    answer.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}
