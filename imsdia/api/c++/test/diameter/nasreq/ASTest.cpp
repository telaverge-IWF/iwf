#include <diameter/Exceptions.h>
#include <diameter/nasreq/AS.h>

void testASRequest() {
    diameter::nasreq::ASRequest request;

    request.setSessionId(diameter::base::SessionId(...));
    request.setOriginHost(diameter::base::OriginHost(...));
    request.setOriginRealm(diameter::base::OriginRealm(...));
    request.setDestinationRealm(diameter::base::DestinationRealm(...));
    request.setDestinationHost(diameter::base::DestinationHost(...));
    request.setAuthApplicationId(diameter::base::AuthApplicationId(...));
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
    request.addReplyMessage(ReplyMessage(...));
    request.addProxyInfo(diameter::base::ProxyInfo(...));
    request.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}

void testASAnswer() {
    diameter::nasreq::ASAnswer answer;

    answer.setSessionId(diameter::base::SessionId(...));
    answer.setResultCode(diameter::base::ResultCode(...));
    answer.setOriginHost(diameter::base::OriginHost(...));
    answer.setOriginRealm(diameter::base::OriginRealm(...));
    answer.setUserName(diameter::base::UserName(...));
    answer.setOriginAAAProtocol(OriginAAAProtocol(...));
    answer.setOriginStateId(diameter::base::OriginStateId(...));
    answer.setState(State(...));
    answer.setErrorMessage(diameter::base::ErrorMessage(...));
    answer.setErrorReportingHost(diameter::base::ErrorReportingHost(...));
    answer.addFailedAVP(diameter::base::FailedAVP(...));
    answer.addRedirectHost(diameter::base::RedirectHost(...));
    answer.setRedirectHostUsage(diameter::base::RedirectHostUsage(...));
    answer.setRedirectMaxCacheTime(diameter::base::RedirectMaxCacheTime(...));
    answer.addProxyInfo(diameter::base::ProxyInfo(...));
    // add more AVP as ANY values
}
