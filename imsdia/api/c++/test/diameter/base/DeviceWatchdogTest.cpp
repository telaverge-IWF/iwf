#include <diameter/Exceptions.h>
#include <diameter/base/DeviceWatchdog.h>

void testDeviceWatchdogRequest() {
    diameter::base::DeviceWatchdogRequest request;

    request.setOriginHost(OriginHost(...));
    request.setOriginRealm(OriginRealm(...));
    request.setOriginStateId(OriginStateId(...));
    request.setIDCIDSHeartbeat(IDCIDSHeartbeat(...));
}

void testDeviceWatchdogAnswer() {
    diameter::base::DeviceWatchdogAnswer answer;

    answer.setResultCode(ResultCode(...));
    answer.setOriginHost(OriginHost(...));
    answer.setOriginRealm(OriginRealm(...));
    answer.setErrorMessage(ErrorMessage(...));
    answer.addFailedAVP(FailedAVP(...));
    answer.setOriginStateId(OriginStateId(...));
    answer.setIDCIDSHeartbeat(IDCIDSHeartbeat(...));
}
