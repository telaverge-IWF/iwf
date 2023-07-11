#include <diameter/Exceptions.h>
#include <diameter/gqgqprime/RA.h>

void testRARequest() {
    diameter::gqgqprime::RARequest request;

    request.setSessionId(diameter::base::SessionId(...));
    request.setOriginHost(diameter::base::OriginHost(...));
    request.setOriginRealm(diameter::base::OriginRealm(...));
    request.setDestinationRealm(diameter::base::DestinationRealm(...));
    request.setDestinationHost(diameter::base::DestinationHost(...));
    request.setAuthApplicationId(diameter::base::AuthApplicationId(...));
    request.addSpecificAction(SpecificAction(...));
    request.addAccessNetworkChargingIdentifier(AccessNetworkChargingIdentifier(...));
    request.setAccessNetworkChargingAddress(AccessNetworkChargingAddress(...));
    request.addFlows(Flows(...));
    request.setAbortCause(AbortCause(...));
    request.setOriginStateId(diameter::base::OriginStateId(...));
    request.addProxyInfo(diameter::base::ProxyInfo(...));
    request.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}

void testRAAnswer() {
    diameter::gqgqprime::RAAnswer answer;

    answer.setSessionId(diameter::base::SessionId(...));
    answer.setOriginHost(diameter::base::OriginHost(...));
    answer.setOriginRealm(diameter::base::OriginRealm(...));
    answer.setResultCode(diameter::base::ResultCode(...));
    answer.setExperimentalResult(diameter::base::ExperimentalResult(...));
    answer.addMediaComponentDescription(MediaComponentDescription(...));
    answer.addFlowGrouping(FlowGrouping(...));
    answer.setOriginStateId(diameter::base::OriginStateId(...));
    answer.setErrorMessage(diameter::base::ErrorMessage(...));
    answer.setErrorReportingHost(diameter::base::ErrorReportingHost(...));
    answer.addFailedAVP(diameter::base::FailedAVP(...));
    answer.addProxyInfo(diameter::base::ProxyInfo(...));
    // add more AVP as ANY values
}
