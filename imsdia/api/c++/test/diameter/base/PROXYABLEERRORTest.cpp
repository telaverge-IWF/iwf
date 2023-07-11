#include <diameter/Exceptions.h>
#include <diameter/base/PROXYABLEERROR.h>

void testPROXYABLEERROR() {
    diameter::base::PROXYABLEERROR answer;

    answer.setSessionId(SessionId(...));
    answer.setOriginHost(OriginHost(...));
    answer.setOriginRealm(OriginRealm(...));
    answer.setResultCode(ResultCode(...));
    answer.setOriginStateId(OriginStateId(...));
    answer.setErrorReportingHost(ErrorReportingHost(...));
    answer.addProxyInfo(ProxyInfo(...));
    // add more AVP as ANY values
}
