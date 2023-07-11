#include <diameter/Exceptions.h>
#include <diameter/base/ReAuth.h>

void testReAuthRequest() {
    diameter::base::ReAuthRequest request;

    request.setSessionId(SessionId(...));
    request.setOriginHost(OriginHost(...));
    request.setOriginRealm(OriginRealm(...));
    request.setDestinationRealm(DestinationRealm(...));
    request.setDestinationHost(DestinationHost(...));
    request.setAuthApplicationId(AuthApplicationId(...));
    request.setReAuthRequestType(ReAuthRequestType(...));
    request.setUserName(UserName(...));
    request.setOriginStateId(OriginStateId(...));
    request.addProxyInfo(ProxyInfo(...));
    request.addRouteRecord(RouteRecord(...));
    // add more AVP as ANY values
}

void testReAuthAnswer() {
    diameter::base::ReAuthAnswer answer;

    answer.setSessionId(SessionId(...));
    answer.setResultCode(ResultCode(...));
    answer.setOriginHost(OriginHost(...));
    answer.setOriginRealm(OriginRealm(...));
    answer.setUserName(UserName(...));
    answer.setOriginStateId(OriginStateId(...));
    answer.setErrorMessage(ErrorMessage(...));
    answer.setErrorReportingHost(ErrorReportingHost(...));
    answer.addFailedAVP(FailedAVP(...));
    answer.addRedirectHost(RedirectHost(...));
    answer.setRedirectHostUsage(RedirectHostUsage(...));
    answer.setRedirectMaxCacheTime(RedirectMaxCacheTime(...));
    answer.addProxyInfo(ProxyInfo(...));
    // add more AVP as ANY values
}
