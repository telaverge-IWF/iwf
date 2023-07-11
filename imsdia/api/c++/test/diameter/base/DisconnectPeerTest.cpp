#include <diameter/Exceptions.h>
#include <diameter/base/DisconnectPeer.h>

void testDisconnectPeerRequest() {
    diameter::base::DisconnectPeerRequest request;

    request.setOriginHost(OriginHost(...));
    request.setOriginRealm(OriginRealm(...));
    request.setDisconnectCause(DisconnectCause(...));
}

void testDisconnectPeerAnswer() {
    diameter::base::DisconnectPeerAnswer answer;

    answer.setResultCode(ResultCode(...));
    answer.setOriginHost(OriginHost(...));
    answer.setOriginRealm(OriginRealm(...));
    answer.setErrorMessage(ErrorMessage(...));
    answer.addFailedAVP(FailedAVP(...));
}
