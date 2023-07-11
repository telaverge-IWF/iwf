#include <diameter/Exceptions.h>
#include <diameter/cxdx_v12/ServerAssignment.h>

void testServerAssignmentRequest() {
    diameter::cxdx_v12::ServerAssignmentRequest request;

    request.setSessionId(diameter::base::SessionId(...));
    request.setVendorSpecificApplicationId(diameter::base::VendorSpecificApplicationId(...));
    request.setAuthSessionState(diameter::base::AuthSessionState(...));
    request.setOriginHost(diameter::base::OriginHost(...));
    request.setOriginRealm(diameter::base::OriginRealm(...));
    request.setServerName(ServerName(...));
    request.setServerAssignmentType(ServerAssignmentType(...));
    request.setUserDataAlreadyAvailable(UserDataAlreadyAvailable(...));
    request.setDestinationRealm(diameter::base::DestinationRealm(...));
    request.setDestinationHost(diameter::base::DestinationHost(...));
    request.setUserName(diameter::base::UserName(...));
    request.setWildcardedPublicIdentity(WildcardedPublicIdentity(...));
    request.setSCSCFRestorationInfo(SCSCFRestorationInfo(...));
    request.setMultipleRegistrationIndication(MultipleRegistrationIndication(...));
    request.setSessionPriority(SessionPriority(...));
    request.addSupportedFeatures(SupportedFeatures(...));
    request.addPublicIdentity(PublicIdentity(...));
    request.addProxyInfo(diameter::base::ProxyInfo(...));
    request.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}

void testServerAssignmentAnswer() {
    diameter::cxdx_v12::ServerAssignmentAnswer answer;

    answer.setSessionId(diameter::base::SessionId(...));
    answer.setVendorSpecificApplicationId(diameter::base::VendorSpecificApplicationId(...));
    answer.setAuthSessionState(diameter::base::AuthSessionState(...));
    answer.setOriginHost(diameter::base::OriginHost(...));
    answer.setOriginRealm(diameter::base::OriginRealm(...));
    answer.setResultCode(diameter::base::ResultCode(...));
    answer.setExperimentalResult(diameter::base::ExperimentalResult(...));
    answer.setUserName(diameter::base::UserName(...));
    answer.addSupportedFeatures(SupportedFeatures(...));
    answer.setUserData(UserData(...));
    answer.setChargingInformation(ChargingInformation(...));
    answer.setAssociatedIdentities(AssociatedIdentities(...));
    answer.setLooseRouteIndication(LooseRouteIndication(...));
    answer.addSCSCFRestorationInfo(SCSCFRestorationInfo(...));
    answer.setAssociatedRegisteredIdentities(AssociatedRegisteredIdentities(...));
    answer.setServerName(ServerName(...));
    answer.setWildcardedPublicIdentity(WildcardedPublicIdentity(...));
    answer.setPriviledgedSenderIndication(PriviledgedSenderIndication(...));
    answer.addFailedAVP(diameter::base::FailedAVP(...));
    answer.addProxyInfo(diameter::base::ProxyInfo(...));
    answer.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
}
