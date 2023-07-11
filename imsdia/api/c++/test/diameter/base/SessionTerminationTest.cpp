#include <diameter/Exceptions.h>
#include <diameter/base/SessionTermination.h>

void testSessionTerminationRequest() {
    diameter::base::SessionTerminationRequest request;

    request.setSessionId(SessionId(...));
    request.setOriginHost(OriginHost(...));
    request.setOriginRealm(OriginRealm(...));
    request.setDestinationRealm(DestinationRealm(...));
    request.setAuthApplicationId(AuthApplicationId(...));
    request.setTerminationCause(TerminationCause(...));
    request.setUserName(UserName(...));
    request.setDestinationHost(DestinationHost(...));
    request.addClass(Class(...));
    request.setOriginStateId(OriginStateId(...));
    request.addProxyInfo(ProxyInfo(...));
    request.addRouteRecord(RouteRecord(...));
    // add more AVP as ANY values
}

void testSessionTerminationAnswer() {
    diameter::base::SessionTerminationAnswer answer;

    answer.setSessionId(SessionId(...));
    answer.setResultCode(ResultCode(...));
    answer.setOriginHost(OriginHost(...));
    answer.setOriginRealm(OriginRealm(...));
    answer.setUserName(UserName(...));
    answer.addClass(Class(...));
    answer.setErrorMessage(ErrorMessage(...));
    answer.setErrorReportingHost(ErrorReportingHost(...));
    answer.addFailedAVP(FailedAVP(...));
    answer.setOriginStateId(OriginStateId(...));
    answer.addRedirectHost(RedirectHost(...));
    answer.setRedirectHostUsage(RedirectHostUsage(...));
    answer.setRedirectMaxCacheTime(RedirectMaxCacheTime(...));
    answer.addProxyInfo(ProxyInfo(...));
    // add more AVP as ANY values
}
