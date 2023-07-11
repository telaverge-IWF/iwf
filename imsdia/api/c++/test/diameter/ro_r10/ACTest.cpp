#include <diameter/Exceptions.h>
#include <diameter/ro_r10/AC.h>

void testACRequest() {
    diameter::ro_r10::ACRequest request;

    request.setSessionId(diameter::base::SessionId(...));
    request.setOriginHost(diameter::base::OriginHost(...));
    request.setOriginRealm(diameter::base::OriginRealm(...));
    request.setDestinationRealm(diameter::base::DestinationRealm(...));
    request.setAccountingRecordType(diameter::base::AccountingRecordType(...));
    request.setAccountingRecordNumber(diameter::base::AccountingRecordNumber(...));
    request.setAcctApplicationId(diameter::base::AcctApplicationId(...));
    request.setUserName(diameter::base::UserName(...));
    request.setAcctInterimInterval(diameter::base::AcctInterimInterval(...));
    request.setOriginStateId(diameter::base::OriginStateId(...));
    request.setEventTimestamp(diameter::base::EventTimestamp(...));
    request.addProxyInfo(diameter::base::ProxyInfo(...));
    request.addRouteRecord(diameter::base::RouteRecord(...));
    request.setServiceContextId(ServiceContextId(...));
    request.setServiceInformation(ServiceInformation(...));
    // add more AVP as ANY values
}

void testACAnswer() {
    diameter::ro_r10::ACAnswer answer;

    answer.setSessionId(diameter::base::SessionId(...));
    answer.setResultCode(diameter::base::ResultCode(...));
    answer.setOriginHost(diameter::base::OriginHost(...));
    answer.setOriginRealm(diameter::base::OriginRealm(...));
    answer.setAccountingRecordType(diameter::base::AccountingRecordType(...));
    answer.setAccountingRecordNumber(diameter::base::AccountingRecordNumber(...));
    answer.setAcctApplicationId(diameter::base::AcctApplicationId(...));
    answer.setUserName(diameter::base::UserName(...));
    answer.setErrorReportingHost(diameter::base::ErrorReportingHost(...));
    answer.setAcctInterimInterval(diameter::base::AcctInterimInterval(...));
    answer.setOriginStateId(diameter::base::OriginStateId(...));
    answer.setEventTimestamp(diameter::base::EventTimestamp(...));
    answer.addProxyInfo(diameter::base::ProxyInfo(...));
    // add more AVP as ANY values
}
