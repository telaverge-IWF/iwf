#include <diameter/Exceptions.h>
#include <diameter/s6a/InsertSubscriberData.h>

void testInsertSubscriberDataRequest() {
    diameter::s6a::InsertSubscriberDataRequest request;

    request.setSessionId(diameter::base::SessionId(...));
    request.setAuthSessionState(diameter::base::AuthSessionState(...));
    request.setOriginHost(diameter::base::OriginHost(...));
    request.setOriginRealm(diameter::base::OriginRealm(...));
    request.setDestinationHost(diameter::base::DestinationHost(...));
    request.setDestinationRealm(diameter::base::DestinationRealm(...));
    request.setUserName(diameter::base::UserName(...));
    request.setSubscriptionData(SubscriptionData(...));
    request.setVendorSpecificApplicationId(diameter::base::VendorSpecificApplicationId(...));
    request.setIDRFlags(IDRFlags(...));
    request.addSupportedFeatures(SupportedFeatures(...));
    request.addProxyInfo(diameter::base::ProxyInfo(...));
    request.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}

void testInsertSubscriberDataAnswer() {
    diameter::s6a::InsertSubscriberDataAnswer answer;

    answer.setSessionId(diameter::base::SessionId(...));
    answer.setAuthSessionState(diameter::base::AuthSessionState(...));
    answer.setOriginHost(diameter::base::OriginHost(...));
    answer.setOriginRealm(diameter::base::OriginRealm(...));
    answer.setVendorSpecificApplicationId(diameter::base::VendorSpecificApplicationId(...));
    answer.addSupportedFeatures(SupportedFeatures(...));
    answer.setResultCode(diameter::base::ResultCode(...));
    answer.setExperimentalResult(diameter::base::ExperimentalResult(...));
    answer.setIDAFlags(IDAFlags(...));
    answer.addFailedAVP(diameter::base::FailedAVP(...));
    answer.addProxyInfo(diameter::base::ProxyInfo(...));
    answer.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}
