#include <diameter/Exceptions.h>
#include <diameter/base/Accounting.h>

void testAccountingRequest() {
    diameter::base::AccountingRequest request;

    request.setSessionId(SessionId(...));
    request.setOriginHost(OriginHost(...));
    request.setOriginRealm(OriginRealm(...));
    request.setDestinationRealm(DestinationRealm(...));
    request.setAccountingRecordType(AccountingRecordType(...));
    request.setAccountingRecordNumber(AccountingRecordNumber(...));
    request.setAcctApplicationId(AcctApplicationId(...));
    request.setVendorSpecificApplicationId(VendorSpecificApplicationId(...));
    request.setUserName(UserName(...));
    request.setAccountingSubSessionId(AccountingSubSessionId(...));
    request.setAcctSessionId(AcctSessionId(...));
    request.setAcctMultiSessionId(AcctMultiSessionId(...));
    request.setAcctInterimInterval(AcctInterimInterval(...));
    request.setAccountingRealtimeRequired(AccountingRealtimeRequired(...));
    request.setOriginStateId(OriginStateId(...));
    request.setEventTimestamp(EventTimestamp(...));
    request.addProxyInfo(ProxyInfo(...));
    request.addRouteRecord(RouteRecord(...));
    // add more AVP as ANY values
}

void testAccountingAnswer() {
    diameter::base::AccountingAnswer answer;

    answer.setSessionId(SessionId(...));
    answer.setResultCode(ResultCode(...));
    answer.setOriginHost(OriginHost(...));
    answer.setOriginRealm(OriginRealm(...));
    answer.setAccountingRecordType(AccountingRecordType(...));
    answer.setAccountingRecordNumber(AccountingRecordNumber(...));
    answer.setAcctApplicationId(AcctApplicationId(...));
    answer.setVendorSpecificApplicationId(VendorSpecificApplicationId(...));
    answer.setUserName(UserName(...));
    answer.setAccountingSubSessionId(AccountingSubSessionId(...));
    answer.setAcctSessionId(AcctSessionId(...));
    answer.setAcctMultiSessionId(AcctMultiSessionId(...));
    answer.setErrorReportingHost(ErrorReportingHost(...));
    answer.setAcctInterimInterval(AcctInterimInterval(...));
    answer.setAccountingRealtimeRequired(AccountingRealtimeRequired(...));
    answer.setOriginStateId(OriginStateId(...));
    answer.setEventTimestamp(EventTimestamp(...));
    answer.addProxyInfo(ProxyInfo(...));
    // add more AVP as ANY values
}
