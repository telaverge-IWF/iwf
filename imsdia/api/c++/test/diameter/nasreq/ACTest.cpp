#include <diameter/Exceptions.h>
#include <diameter/nasreq/AC.h>

void testACRequest() {
    diameter::nasreq::ACRequest request;

    request.setSessionId(diameter::base::SessionId(...));
    request.setOriginHost(diameter::base::OriginHost(...));
    request.setOriginRealm(diameter::base::OriginRealm(...));
    request.setDestinationRealm(diameter::base::DestinationRealm(...));
    request.setAccountingRecordType(diameter::base::AccountingRecordType(...));
    request.setAccountingRecordNumber(diameter::base::AccountingRecordNumber(...));
    request.setAcctApplicationId(diameter::base::AcctApplicationId(...));
    request.setVendorSpecificApplicationId(diameter::base::VendorSpecificApplicationId(...));
    request.setUserName(diameter::base::UserName(...));
    request.setAccountingSubSessionId(diameter::base::AccountingSubSessionId(...));
    request.setAcctSessionId(diameter::base::AcctSessionId(...));
    request.setAcctMultiSessionId(diameter::base::AcctMultiSessionId(...));
    request.setOriginAAAProtocol(OriginAAAProtocol(...));
    request.setOriginStateId(diameter::base::OriginStateId(...));
    request.setDestinationHost(diameter::base::DestinationHost(...));
    request.setEventTimestamp(diameter::base::EventTimestamp(...));
    request.setAcctDelayTime(AcctDelayTime(...));
    request.setNASIdentifier(NASIdentifier(...));
    request.setNASIPAddress(NASIPAddress(...));
    request.setNASIPv6Address(NASIPv6Address(...));
    request.setNASPort(NASPort(...));
    request.setNASPortId(NASPortId(...));
    request.setNASPortType(NASPortType(...));
    request.addClass(diameter::base::Class(...));
    request.setServiceType(ServiceType(...));
    request.setTerminationCause(diameter::base::TerminationCause(...));
    request.setAccountingInputOctets(AccountingInputOctets(...));
    request.setAccountingInputPackets(AccountingInputPackets(...));
    request.setAccountingOutputOctets(AccountingOutputOctets(...));
    request.setAccountingOutputPackets(AccountingOutputPackets(...));
    request.setAcctAuthentic(AcctAuthentic(...));
    request.setAccountingAuthMethod(AccountingAuthMethod(...));
    request.setAcctLinkCount(AcctLinkCount(...));
    request.setAcctSessionTime(AcctSessionTime(...));
    request.setAcctTunnelConnection(AcctTunnelConnection(...));
    request.setAcctTunnelPacketsLost(AcctTunnelPacketsLost(...));
    request.setCallbackId(CallbackId(...));
    request.setCallbackNumber(CallbackNumber(...));
    request.setCalledStationId(CalledStationId(...));
    request.setCallingStationId(CallingStationId(...));
    request.addConnectInfo(ConnectInfo(...));
    request.setOriginatingLineInfo(OriginatingLineInfo(...));
    request.setAuthorizationLifetime(diameter::base::AuthorizationLifetime(...));
    request.setSessionTimeout(diameter::base::SessionTimeout(...));
    request.setIdleTimeout(IdleTimeout(...));
    request.setPortLimit(PortLimit(...));
    request.setAccountingRealtimeRequired(diameter::base::AccountingRealtimeRequired(...));
    request.setAcctInterimInterval(diameter::base::AcctInterimInterval(...));
    request.addFilterId(FilterId(...));
    request.addNASFilterRule(NASFilterRule(...));
    request.addQoSFilterRule(QoSFilterRule(...));
    request.setFramedAppletalkLink(FramedAppletalkLink(...));
    request.setFramedAppletalkNetwork(FramedAppletalkNetwork(...));
    request.setFramedAppletalkZone(FramedAppletalkZone(...));
    request.setFramedCompression(FramedCompression(...));
    request.setFramedInterfaceId(FramedInterfaceId(...));
    request.setFramedIPAddress(FramedIPAddress(...));
    request.setFramedIPNetmask(FramedIPNetmask(...));
    request.addFramedIPv6Prefix(FramedIPv6Prefix(...));
    request.setFramedIPv6Pool(FramedIPv6Pool(...));
    request.addFramedIPv6Route(FramedIPv6Route(...));
    request.setFramedIPXNetwork(FramedIPXNetwork(...));
    request.setFramedMTU(FramedMTU(...));
    request.setFramedPool(FramedPool(...));
    request.setFramedProtocol(FramedProtocol(...));
    request.addFramedRoute(FramedRoute(...));
    request.setFramedRouting(FramedRouting(...));
    request.addLoginIPHost(LoginIPHost(...));
    request.addLoginIPv6Host(LoginIPv6Host(...));
    request.setLoginLATGroup(LoginLATGroup(...));
    request.setLoginLATNode(LoginLATNode(...));
    request.setLoginLATPort(LoginLATPort(...));
    request.setLoginLATService(LoginLATService(...));
    request.setLoginService(LoginService(...));
    request.setLoginTCPPort(LoginTCPPort(...));
    request.addTunneling(Tunneling(...));
    request.addProxyInfo(diameter::base::ProxyInfo(...));
    request.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}

void testACAnswer() {
    diameter::nasreq::ACAnswer answer;

    answer.setSessionId(diameter::base::SessionId(...));
    answer.setResultCode(diameter::base::ResultCode(...));
    answer.setOriginHost(diameter::base::OriginHost(...));
    answer.setOriginRealm(diameter::base::OriginRealm(...));
    answer.setAccountingRecordType(diameter::base::AccountingRecordType(...));
    answer.setAccountingRecordNumber(diameter::base::AccountingRecordNumber(...));
    answer.setAcctApplicationId(diameter::base::AcctApplicationId(...));
    answer.setVendorSpecificApplicationId(diameter::base::VendorSpecificApplicationId(...));
    answer.setUserName(diameter::base::UserName(...));
    answer.setAccountingSubSessionId(diameter::base::AccountingSubSessionId(...));
    answer.setAcctSessionId(diameter::base::AcctSessionId(...));
    answer.setAcctMultiSessionId(diameter::base::AcctMultiSessionId(...));
    answer.setEventTimestamp(diameter::base::EventTimestamp(...));
    answer.setErrorMessage(diameter::base::ErrorMessage(...));
    answer.setErrorReportingHost(diameter::base::ErrorReportingHost(...));
    answer.addFailedAVP(diameter::base::FailedAVP(...));
    answer.setOriginAAAProtocol(OriginAAAProtocol(...));
    answer.setOriginStateId(diameter::base::OriginStateId(...));
    answer.setNASIdentifier(NASIdentifier(...));
    answer.setNASIPAddress(NASIPAddress(...));
    answer.setNASIPv6Address(NASIPv6Address(...));
    answer.setNASPort(NASPort(...));
    answer.setNASPortId(NASPortId(...));
    answer.setNASPortType(NASPortType(...));
    answer.setServiceType(ServiceType(...));
    answer.setTerminationCause(diameter::base::TerminationCause(...));
    answer.setAccountingRealtimeRequired(diameter::base::AccountingRealtimeRequired(...));
    answer.setAcctInterimInterval(diameter::base::AcctInterimInterval(...));
    answer.addClass(diameter::base::Class(...));
    answer.addProxyInfo(diameter::base::ProxyInfo(...));
    answer.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}
