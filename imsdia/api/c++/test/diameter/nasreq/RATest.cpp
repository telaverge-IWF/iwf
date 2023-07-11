#include <diameter/Exceptions.h>
#include <diameter/nasreq/RA.h>

void testRARequest() {
    diameter::nasreq::RARequest request;

    request.setSessionId(diameter::base::SessionId(...));
    request.setOriginHost(diameter::base::OriginHost(...));
    request.setOriginRealm(diameter::base::OriginRealm(...));
    request.setDestinationRealm(diameter::base::DestinationRealm(...));
    request.setDestinationHost(diameter::base::DestinationHost(...));
    request.setAuthApplicationId(diameter::base::AuthApplicationId(...));
    request.setReAuthRequestType(diameter::base::ReAuthRequestType(...));
    request.setUserName(diameter::base::UserName(...));
    request.setOriginAAAProtocol(OriginAAAProtocol(...));
    request.setOriginStateId(diameter::base::OriginStateId(...));
    request.setNASIdentifier(NASIdentifier(...));
    request.setNASIPAddress(NASIPAddress(...));
    request.setNASIPv6Address(NASIPv6Address(...));
    request.setNASPort(NASPort(...));
    request.setNASPortId(NASPortId(...));
    request.setNASPortType(NASPortType(...));
    request.setServiceType(ServiceType(...));
    request.setFramedIPAddress(FramedIPAddress(...));
    request.setFramedIPv6Prefix(FramedIPv6Prefix(...));
    request.setFramedInterfaceId(FramedInterfaceId(...));
    request.setCalledStationId(CalledStationId(...));
    request.setCallingStationId(CallingStationId(...));
    request.setOriginatingLineInfo(OriginatingLineInfo(...));
    request.setAcctSessionId(diameter::base::AcctSessionId(...));
    request.setAcctMultiSessionId(diameter::base::AcctMultiSessionId(...));
    request.setState(State(...));
    request.addClass(diameter::base::Class(...));
    request.setReplyMessage(ReplyMessage(...));
    request.addProxyInfo(diameter::base::ProxyInfo(...));
    request.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}

void testRAAnswer() {
    diameter::nasreq::RAAnswer answer;

    answer.setSessionId(diameter::base::SessionId(...));
    answer.setResultCode(diameter::base::ResultCode(...));
    answer.setOriginHost(diameter::base::OriginHost(...));
    answer.setOriginRealm(diameter::base::OriginRealm(...));
    answer.setUserName(diameter::base::UserName(...));
    answer.setOriginAAAProtocol(OriginAAAProtocol(...));
    answer.setOriginStateId(diameter::base::OriginStateId(...));
    answer.setErrorMessage(diameter::base::ErrorMessage(...));
    answer.setErrorReportingHost(diameter::base::ErrorReportingHost(...));
    answer.addFailedAVP(diameter::base::FailedAVP(...));
    answer.addRedirectHost(diameter::base::RedirectHost(...));
    answer.setRedirectHostUsage(diameter::base::RedirectHostUsage(...));
    answer.setRedirectMaxCacheTime(diameter::base::RedirectMaxCacheTime(...));
    answer.setServiceType(ServiceType(...));
    answer.addConfigurationToken(ConfigurationToken(...));
    answer.setIdleTimeout(IdleTimeout(...));
    answer.setAuthorizationLifetime(diameter::base::AuthorizationLifetime(...));
    answer.setAuthGracePeriod(diameter::base::AuthGracePeriod(...));
    answer.setReAuthRequestType(diameter::base::ReAuthRequestType(...));
    answer.setState(State(...));
    answer.addClass(diameter::base::Class(...));
    answer.addReplyMessage(ReplyMessage(...));
    answer.setPrompt(Prompt(...));
    answer.addProxyInfo(diameter::base::ProxyInfo(...));
    // add more AVP as ANY values
}
