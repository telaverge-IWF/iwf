#include <diameter/Exceptions.h>
#include <diameter/sh/UserData.h>

void testUserDataRequest() {
    diameter::sh::UserDataRequest request;

    request.setSessionId(diameter::base::SessionId(...));
    request.setVendorSpecificApplicationId(diameter::base::VendorSpecificApplicationId(...));
    request.setAuthSessionState(diameter::base::AuthSessionState(...));
    request.setOriginHost(diameter::base::OriginHost(...));
    request.setOriginRealm(diameter::base::OriginRealm(...));
    request.setDestinationRealm(diameter::base::DestinationRealm(...));
    request.setUserIdentity(UserIdentity(...));
    request.setDataReference(DataReference(...));
    request.setDestinationHost(diameter::base::DestinationHost(...));
    request.addSupportedFeatures(diameter::cxdx::SupportedFeatures(...));
    request.setServerName(diameter::cxdx::ServerName(...));
    request.setServiceIndication(ServiceIndication(...));
    request.setIdentitySet(IdentitySet(...));
    request.setRequestedDomain(RequestedDomain(...));
    request.setCurrentLocation(CurrentLocation(...));
    request.addProxyInfo(diameter::base::ProxyInfo(...));
    request.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}

void testUserDataAnswer() {
    diameter::sh::UserDataAnswer answer;

    answer.setSessionId(diameter::base::SessionId(...));
    answer.setVendorSpecificApplicationId(diameter::base::VendorSpecificApplicationId(...));
    answer.setAuthSessionState(diameter::base::AuthSessionState(...));
    answer.setOriginHost(diameter::base::OriginHost(...));
    answer.setOriginRealm(diameter::base::OriginRealm(...));
    answer.setResultCode(diameter::base::ResultCode(...));
    answer.setExperimentalResult(diameter::base::ExperimentalResult(...));
    answer.addSupportedFeatures(diameter::cxdx::SupportedFeatures(...));
    answer.setShUserData(ShUserData(...));
    answer.addFailedAVP(diameter::base::FailedAVP(...));
    answer.addProxyInfo(diameter::base::ProxyInfo(...));
    answer.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}
