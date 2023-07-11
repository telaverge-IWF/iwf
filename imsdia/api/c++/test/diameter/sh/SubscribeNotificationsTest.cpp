#include <diameter/Exceptions.h>
#include <diameter/sh/SubscribeNotifications.h>

void testSubscribeNotificationsRequest() {
    diameter::sh::SubscribeNotificationsRequest request;

    request.setSessionId(diameter::base::SessionId(...));
    request.setVendorSpecificApplicationId(diameter::base::VendorSpecificApplicationId(...));
    request.setAuthSessionState(diameter::base::AuthSessionState(...));
    request.setOriginHost(diameter::base::OriginHost(...));
    request.setOriginRealm(diameter::base::OriginRealm(...));
    request.setDestinationRealm(diameter::base::DestinationRealm(...));
    request.setUserIdentity(UserIdentity(...));
    request.setSubsReqType(SubsReqType(...));
    request.setDataReference(DataReference(...));
    request.setDestinationHost(diameter::base::DestinationHost(...));
    request.addSupportedFeatures(diameter::cxdx::SupportedFeatures(...));
    request.setServiceIndication(ServiceIndication(...));
    request.setServerName(diameter::cxdx::ServerName(...));
    request.addProxyInfo(diameter::base::ProxyInfo(...));
    request.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}

void testSubscribeNotificationsAnswer() {
    diameter::sh::SubscribeNotificationsAnswer answer;

    answer.setSessionId(diameter::base::SessionId(...));
    answer.setVendorSpecificApplicationId(diameter::base::VendorSpecificApplicationId(...));
    answer.setAuthSessionState(diameter::base::AuthSessionState(...));
    answer.setOriginHost(diameter::base::OriginHost(...));
    answer.setOriginRealm(diameter::base::OriginRealm(...));
    answer.setResultCode(diameter::base::ResultCode(...));
    answer.setExperimentalResult(diameter::base::ExperimentalResult(...));
    answer.addSupportedFeatures(diameter::cxdx::SupportedFeatures(...));
    answer.addFailedAVP(diameter::base::FailedAVP(...));
    answer.addProxyInfo(diameter::base::ProxyInfo(...));
    answer.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}
