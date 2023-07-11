#include <diameter/Exceptions.h>
#include <diameter/ro_r10_transatel/ReAuth.h>

void testReAuthRequest() {
    diameter::ro_r10_transatel::ReAuthRequest request;

    request.setSessionId(diameter::base::SessionId(...));
    request.setOriginHost(diameter::base::OriginHost(...));
    request.setOriginRealm(diameter::base::OriginRealm(...));
    request.setDestinationRealm(diameter::base::DestinationRealm(...));
    request.setDestinationHost(diameter::base::DestinationHost(...));
    request.setAuthApplicationId(diameter::base::AuthApplicationId(...));
    request.setReAuthRequestType(diameter::base::ReAuthRequestType(...));
    request.setUserName(diameter::base::UserName(...));
    request.setOriginStateId(diameter::base::OriginStateId(...));
    request.addProxyInfo(diameter::base::ProxyInfo(...));
    request.addRouteRecord(diameter::base::RouteRecord(...));
    request.setGSUPoolIdentifier(GSUPoolIdentifier(...));
    request.setServiceIdentifier(ServiceIdentifier(...));
    request.setRatingGroup(RatingGroup(...));
    // add more AVP as ANY values
}

void testReAuthAnswer() {
    diameter::ro_r10_transatel::ReAuthAnswer answer;

    answer.setSessionId(diameter::base::SessionId(...));
    answer.setResultCode(diameter::base::ResultCode(...));
    answer.setOriginHost(diameter::base::OriginHost(...));
    answer.setOriginRealm(diameter::base::OriginRealm(...));
    answer.setUserName(diameter::base::UserName(...));
    answer.setOriginStateId(diameter::base::OriginStateId(...));
    answer.setErrorMessage(diameter::base::ErrorMessage(...));
    answer.setErrorReportingHost(diameter::base::ErrorReportingHost(...));
    answer.addFailedAVP(diameter::base::FailedAVP(...));
    answer.addRedirectHost(diameter::base::RedirectHost(...));
    answer.setRedirectHostUsage(diameter::base::RedirectHostUsage(...));
    answer.setRedirectMaxCacheTime(diameter::base::RedirectMaxCacheTime(...));
    answer.addProxyInfo(diameter::base::ProxyInfo(...));
    // add more AVP as ANY values
}
