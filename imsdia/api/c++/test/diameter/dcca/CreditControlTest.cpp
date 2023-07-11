#include <diameter/Exceptions.h>
#include <diameter/dcca/CreditControl.h>

void testCreditControlRequest() {
    diameter::dcca::CreditControlRequest request;

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
    request.setCCSubSessionId(CCSubSessionId(...));
    request.setAcctMultiSessionId(diameter::base::AcctMultiSessionId(...));
    request.setOriginStateId(diameter::base::OriginStateId(...));
    request.setEventTimestamp(diameter::base::EventTimestamp(...));
    request.addSubscriptionId(SubscriptionId(...));
    request.setServiceIdentifier(ServiceIdentifier(...));
    request.setTerminationCause(diameter::base::TerminationCause(...));
    request.setRequestedServiceUnit(RequestedServiceUnit(...));
    request.setRequestedAction(RequestedAction(...));
    request.addUsedServiceUnit(UsedServiceUnit(...));
    request.setMultipleServicesIndicator(MultipleServicesIndicator(...));
    request.addMultipleServicesCreditControl(MultipleServicesCreditControl(...));
    request.addServiceParameterInfo(ServiceParameterInfo(...));
    request.setCCCorrelationId(CCCorrelationId(...));
    request.setUserEquipmentInfo(UserEquipmentInfo(...));
    request.addProxyInfo(diameter::base::ProxyInfo(...));
    request.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}

void testCreditControlAnswer() {
    diameter::dcca::CreditControlAnswer answer;

    answer.setSessionId(diameter::base::SessionId(...));
    answer.setResultCode(diameter::base::ResultCode(...));
    answer.setOriginHost(diameter::base::OriginHost(...));
    answer.setOriginRealm(diameter::base::OriginRealm(...));
    answer.setAuthApplicationId(diameter::base::AuthApplicationId(...));
    answer.setCCRequestType(CCRequestType(...));
    answer.setCCRequestNumber(CCRequestNumber(...));
    answer.setUserName(diameter::base::UserName(...));
    answer.setCCSessionFailover(CCSessionFailover(...));
    answer.setCCSubSessionId(CCSubSessionId(...));
    answer.setAcctMultiSessionId(diameter::base::AcctMultiSessionId(...));
    answer.setOriginStateId(diameter::base::OriginStateId(...));
    answer.setEventTimestamp(diameter::base::EventTimestamp(...));
    answer.setGrantedServiceUnit(GrantedServiceUnit(...));
    answer.addMultipleServicesCreditControl(MultipleServicesCreditControl(...));
    answer.setCostInformation(CostInformation(...));
    answer.setFinalUnitIndication(FinalUnitIndication(...));
    answer.setCheckBalanceResult(CheckBalanceResult(...));
    answer.setCreditControlFailureHandling(CreditControlFailureHandling(...));
    answer.setDirectDebitingFailureHandling(DirectDebitingFailureHandling(...));
    answer.setValidityTime(ValidityTime(...));
    answer.addRedirectHost(diameter::base::RedirectHost(...));
    answer.setRedirectHostUsage(diameter::base::RedirectHostUsage(...));
    answer.setRedirectMaxCacheTime(diameter::base::RedirectMaxCacheTime(...));
    answer.addProxyInfo(diameter::base::ProxyInfo(...));
    answer.addRouteRecord(diameter::base::RouteRecord(...));
    answer.addFailedAVP(diameter::base::FailedAVP(...));
    // add more AVP as ANY values
}
