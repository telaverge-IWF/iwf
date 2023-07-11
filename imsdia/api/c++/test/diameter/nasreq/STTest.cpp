#include <diameter/Exceptions.h>
#include <diameter/nasreq/ST.h>

void testSTRequest() {
    diameter::nasreq::STRequest request;

    request.setSessionId(diameter::base::SessionId(...));
    request.setOriginHost(diameter::base::OriginHost(...));
    request.setOriginRealm(diameter::base::OriginRealm(...));
    request.setDestinationRealm(diameter::base::DestinationRealm(...));
    request.setAuthApplicationId(diameter::base::AuthApplicationId(...));
    request.setTerminationCause(diameter::base::TerminationCause(...));
    request.setUserName(diameter::base::UserName(...));
    request.setDestinationHost(diameter::base::DestinationHost(...));
    request.addClass(diameter::base::Class(...));
    request.setOriginAAAProtocol(OriginAAAProtocol(...));
    request.setOriginStateId(diameter::base::OriginStateId(...));
    request.addProxyInfo(diameter::base::ProxyInfo(...));
    request.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}

void testSTAnswer() {
    diameter::nasreq::STAnswer answer;

    answer.setSessionId(diameter::base::SessionId(...));
    answer.setResultCode(diameter::base::ResultCode(...));
    answer.setOriginHost(diameter::base::OriginHost(...));
    answer.setOriginRealm(diameter::base::OriginRealm(...));
    answer.setUserName(diameter::base::UserName(...));
    answer.addClass(diameter::base::Class(...));
    answer.setErrorMessage(diameter::base::ErrorMessage(...));
    answer.setErrorReportingHost(diameter::base::ErrorReportingHost(...));
    answer.addFailedAVP(diameter::base::FailedAVP(...));
    answer.setOriginAAAProtocol(OriginAAAProtocol(...));
    answer.setOriginStateId(diameter::base::OriginStateId(...));
    answer.addRedirectHost(diameter::base::RedirectHost(...));
    answer.setRedirectHostUsage(diameter::base::RedirectHostUsage(...));
    answer.setRedirectMaxCacheTime(diameter::base::RedirectMaxCacheTime(...));
    answer.addProxyInfo(diameter::base::ProxyInfo(...));
    // add more AVP as ANY values
}
