#include <diameter/Exceptions.h>
#include <diameter/gqgqprime/AA.h>

void testAARequest() {
    diameter::gqgqprime::AARequest request;

    request.setSessionId(diameter::base::SessionId(...));
    request.setAuthApplicationId(diameter::base::AuthApplicationId(...));
    request.setOriginHost(diameter::base::OriginHost(...));
    request.setOriginRealm(diameter::base::OriginRealm(...));
    request.setDestinationRealm(diameter::base::DestinationRealm(...));
    request.addMediaComponentDescription(MediaComponentDescription(...));
    request.addFlowGrouping(FlowGrouping(...));
    request.setAFChargingIdentifier(AFChargingIdentifier(...));
    request.setSIPForkingIndication(SIPForkingIndication(...));
    request.addSpecificAction(SpecificAction(...));
    request.setUserName(diameter::base::UserName(...));
    request.setBindingInformation(BindingInformation(...));
    request.setLatchingIndication(LatchingIndication(...));
    request.setReservationPriority(ReservationPriority(...));
    request.setGloballyUniqueAddress(GloballyUniqueAddress(...));
    request.setAuthorizationLifetime(diameter::base::AuthorizationLifetime(...));
    request.addProxyInfo(diameter::base::ProxyInfo(...));
    request.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}

void testAAAnswer() {
    diameter::gqgqprime::AAAnswer answer;

    answer.setSessionId(diameter::base::SessionId(...));
    answer.setAuthApplicationId(diameter::base::AuthApplicationId(...));
    answer.setOriginHost(diameter::base::OriginHost(...));
    answer.setOriginRealm(diameter::base::OriginRealm(...));
    answer.setResultCode(diameter::base::ResultCode(...));
    answer.setExperimentalResult(diameter::base::ExperimentalResult(...));
    answer.setBindingInformation(BindingInformation(...));
    answer.setReservationPriority(ReservationPriority(...));
    answer.setAuthorizationToken(AuthorizationToken(...));
    answer.addAccessNetworkChargingIdentifier(AccessNetworkChargingIdentifier(...));
    answer.setAccessNetworkChargingAddress(AccessNetworkChargingAddress(...));
    answer.setErrorMessage(diameter::base::ErrorMessage(...));
    answer.setErrorReportingHost(diameter::base::ErrorReportingHost(...));
    answer.setAuthorizationLifetime(diameter::base::AuthorizationLifetime(...));
    answer.setAuthGracePeriod(diameter::base::AuthGracePeriod(...));
    answer.addFailedAVP(diameter::base::FailedAVP(...));
    answer.addProxyInfo(diameter::base::ProxyInfo(...));
    // add more AVP as ANY values
}
