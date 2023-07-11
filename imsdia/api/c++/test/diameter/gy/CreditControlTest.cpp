#include <diameter/Exceptions.h>
#include <diameter/gy/CreditControl.h>

void testCreditControlRequest() {
    diameter::gy::CreditControlRequest request;

    request.setSessionId(diameter::base::SessionId(...));
    request.setOriginHost(diameter::base::OriginHost(...));
    request.setOriginRealm(diameter::base::OriginRealm(...));
    request.setDestinationRealm(diameter::base::DestinationRealm(...));
    request.setAuthApplicationId(diameter::base::AuthApplicationId(...));
    request.setServiceContextId(ServiceContextId(...));
    request.setCCRequestType(CCRequestType(...));
    request.setCCRequestNumber(CCRequestNumber(...));
    request.setDestinationHost(diameter::base::DestinationHost(...));
    request.setUserName(diameter::base::UserName(...));
    request.setOriginStateId(diameter::base::OriginStateId(...));
    request.setEventTimestamp(diameter::base::EventTimestamp(...));
    request.addSubscriptionId(SubscriptionId(...));
    request.setTerminationCause(diameter::base::TerminationCause(...));
    request.setRequestedAction(RequestedAction(...));
    request.setAoCRequestType(AoCRequestType(...));
    request.setMultipleServicesIndicator(MultipleServicesIndicator(...));
    request.addMultipleServicesCreditControl(MultipleServicesCreditControl(...));
    request.setCCCorrelationId(CCCorrelationId(...));
    request.setUserEquipmentInfo(UserEquipmentInfo(...));
    request.addProxyInfo(diameter::base::ProxyInfo(...));
    request.addRouteRecord(diameter::base::RouteRecord(...));
    request.setServiceInformation(ServiceInformation(...));
    // add more AVP as ANY values
}

void testCreditControlAnswer() {
    diameter::gy::CreditControlAnswer answer;

    answer.setSessionId(diameter::base::SessionId(...));
    answer.setResultCode(diameter::base::ResultCode(...));
    answer.setOriginHost(diameter::base::OriginHost(...));
    answer.setOriginRealm(diameter::base::OriginRealm(...));
    answer.setAuthApplicationId(diameter::base::AuthApplicationId(...));
    answer.setCCRequestType(CCRequestType(...));
    answer.setCCRequestNumber(CCRequestNumber(...));
    answer.setCCSessionFailover(CCSessionFailover(...));
    answer.addMultipleServicesCreditControl(MultipleServicesCreditControl(...));
    answer.setCostInformation(CostInformation(...));
    answer.setLowBalanceIndication(LowBalanceIndication(...));
    answer.setRemainingBalance(RemainingBalance(...));
    answer.setCreditControlFailureHandling(CreditControlFailureHandling(...));
    answer.setDirectDebitingFailureHandling(DirectDebitingFailureHandling(...));
    answer.addRedirectHost(diameter::base::RedirectHost(...));
    answer.setRedirectHostUsage(diameter::base::RedirectHostUsage(...));
    answer.setRedirectMaxCacheTime(diameter::base::RedirectMaxCacheTime(...));
    answer.addProxyInfo(diameter::base::ProxyInfo(...));
    answer.addRouteRecord(diameter::base::RouteRecord(...));
    answer.addFailedAVP(diameter::base::FailedAVP(...));
    answer.setServiceInformation(ServiceInformation(...));
    // add more AVP as ANY values
}
