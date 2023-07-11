#include <diameter/Exceptions.h>
#include <diameter/base/NONPROXYABLEERROR.h>

void testNONPROXYABLEERROR() {
    diameter::base::NONPROXYABLEERROR answer;

    answer.setSessionId(SessionId(...));
    answer.setOriginHost(OriginHost(...));
    answer.setOriginRealm(OriginRealm(...));
    answer.setResultCode(ResultCode(...));
    answer.setOriginStateId(OriginStateId(...));
    answer.setErrorReportingHost(ErrorReportingHost(...));
    answer.setProxyInfo(ProxyInfo(...));
    // add more AVP as ANY values
}
