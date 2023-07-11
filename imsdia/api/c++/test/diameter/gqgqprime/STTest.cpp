#include <diameter/Exceptions.h>
#include <diameter/gqgqprime/ST.h>

void testSTRequest() {
    diameter::gqgqprime::STRequest request;

    request.setSessionId(diameter::base::SessionId(...));
    request.setOriginHost(diameter::base::OriginHost(...));
    request.setOriginRealm(diameter::base::OriginRealm(...));
    request.setDestinationRealm(diameter::base::DestinationRealm(...));
    request.setTerminationCause(diameter::base::TerminationCause(...));
    request.setAuthApplicationId(diameter::base::AuthApplicationId(...));
    request.setDestinationHost(diameter::base::DestinationHost(...));
    request.addClass(diameter::base::Class(...));
    request.setOriginStateId(diameter::base::OriginStateId(...));
    request.addProxyInfo(diameter::base::ProxyInfo(...));
    request.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}

void testSTAnswer() {
    diameter::gqgqprime::STAnswer answer;

    answer.setSessionId(diameter::base::SessionId(...));
    answer.setOriginHost(diameter::base::OriginHost(...));
    answer.setOriginRealm(diameter::base::OriginRealm(...));
    answer.setResultCode(diameter::base::ResultCode(...));
    answer.setExperimentalResult(diameter::base::ExperimentalResult(...));
    answer.setErrorMessage(diameter::base::ErrorMessage(...));
    answer.setErrorReportingHost(diameter::base::ErrorReportingHost(...));
    answer.addFailedAVP(diameter::base::FailedAVP(...));
    answer.setOriginStateId(diameter::base::OriginStateId(...));
    answer.addRedirectHost(diameter::base::RedirectHost(...));
    answer.setRedirectHostUsage(diameter::base::RedirectHostUsage(...));
    answer.setRedirectMaxCacheTime(diameter::base::RedirectMaxCacheTime(...));
    answer.addProxyInfo(diameter::base::ProxyInfo(...));
    // add more AVP as ANY values
}
