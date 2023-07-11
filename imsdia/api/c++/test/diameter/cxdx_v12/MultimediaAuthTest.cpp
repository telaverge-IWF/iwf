#include <diameter/Exceptions.h>
#include <diameter/cxdx_v12/MultimediaAuth.h>

void testMultimediaAuthRequest() {
    diameter::cxdx_v12::MultimediaAuthRequest request;

    request.setSessionId(diameter::base::SessionId(...));
    request.setVendorSpecificApplicationId(diameter::base::VendorSpecificApplicationId(...));
    request.setAuthSessionState(diameter::base::AuthSessionState(...));
    request.setOriginHost(diameter::base::OriginHost(...));
    request.setOriginRealm(diameter::base::OriginRealm(...));
    request.setDestinationRealm(diameter::base::DestinationRealm(...));
    request.setUserName(diameter::base::UserName(...));
    request.setPublicIdentity(PublicIdentity(...));
    request.setServerName(ServerName(...));
    request.setSIPAuthDataItem(SIPAuthDataItem(...));
    request.setSIPNumberAuthItems(SIPNumberAuthItems(...));
    request.setDestinationHost(diameter::base::DestinationHost(...));
    request.addSupportedFeatures(SupportedFeatures(...));
    request.addProxyInfo(diameter::base::ProxyInfo(...));
    request.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}

void testMultimediaAuthAnswer() {
    diameter::cxdx_v12::MultimediaAuthAnswer answer;

    answer.setSessionId(diameter::base::SessionId(...));
    answer.setVendorSpecificApplicationId(diameter::base::VendorSpecificApplicationId(...));
    answer.setAuthSessionState(diameter::base::AuthSessionState(...));
    answer.setOriginHost(diameter::base::OriginHost(...));
    answer.setOriginRealm(diameter::base::OriginRealm(...));
    answer.setResultCode(diameter::base::ResultCode(...));
    answer.setExperimentalResult(diameter::base::ExperimentalResult(...));
    answer.setUserName(diameter::base::UserName(...));
    answer.addSupportedFeatures(SupportedFeatures(...));
    answer.setPublicIdentity(PublicIdentity(...));
    answer.setSIPNumberAuthItems(SIPNumberAuthItems(...));
    answer.addSIPAuthDataItem(SIPAuthDataItem(...));
    answer.addFailedAVP(diameter::base::FailedAVP(...));
    answer.addProxyInfo(diameter::base::ProxyInfo(...));
    answer.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}
