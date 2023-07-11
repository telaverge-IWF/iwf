#include <diameter/Exceptions.h>
#include <diameter/cxdx_v12/LocationInfo.h>

void testLocationInfoRequest() {
    diameter::cxdx_v12::LocationInfoRequest request;

    request.setSessionId(diameter::base::SessionId(...));
    request.setVendorSpecificApplicationId(diameter::base::VendorSpecificApplicationId(...));
    request.setAuthSessionState(diameter::base::AuthSessionState(...));
    request.setOriginHost(diameter::base::OriginHost(...));
    request.setOriginRealm(diameter::base::OriginRealm(...));
    request.setDestinationRealm(diameter::base::DestinationRealm(...));
    request.setPublicIdentity(PublicIdentity(...));
    request.setDestinationHost(diameter::base::DestinationHost(...));
    request.setOriginatingRequest(OriginatingRequest(...));
    request.setUserAuthorizationType(UserAuthorizationType(...));
    request.setSessionPriority(SessionPriority(...));
    request.addSupportedFeatures(SupportedFeatures(...));
    request.addProxyInfo(diameter::base::ProxyInfo(...));
    request.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}

void testLocationInfoAnswer() {
    diameter::cxdx_v12::LocationInfoAnswer answer;

    answer.setSessionId(diameter::base::SessionId(...));
    answer.setVendorSpecificApplicationId(diameter::base::VendorSpecificApplicationId(...));
    answer.setAuthSessionState(diameter::base::AuthSessionState(...));
    answer.setOriginHost(diameter::base::OriginHost(...));
    answer.setOriginRealm(diameter::base::OriginRealm(...));
    answer.setResultCode(diameter::base::ResultCode(...));
    answer.setExperimentalResult(diameter::base::ExperimentalResult(...));
    answer.setWildcardedPublicIdentity(WildcardedPublicIdentity(...));
    answer.setLIAFlags(LIAFlags(...));
    answer.addSupportedFeatures(SupportedFeatures(...));
    answer.setServerName(ServerName(...));
    answer.setServerCapabilities(ServerCapabilities(...));
    answer.addFailedAVP(diameter::base::FailedAVP(...));
    answer.addProxyInfo(diameter::base::ProxyInfo(...));
    answer.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}
