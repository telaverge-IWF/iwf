#include <diameter/Exceptions.h>
#include <diameter/base/CapabilitiesExchange.h>

void testCapabilitiesExchangeRequest() {
    diameter::base::CapabilitiesExchangeRequest request;

    request.setOriginHost(OriginHost(...));
    request.setOriginRealm(OriginRealm(...));
    request.addHostIPAddress(HostIPAddress(...));
    request.setVendorId(VendorId(...));
    request.setProductName(ProductName(...));
    request.setOriginStateId(OriginStateId(...));
    request.addSupportedVendorId(SupportedVendorId(...));
    request.addAuthApplicationId(AuthApplicationId(...));
    request.addInbandSecurityId(InbandSecurityId(...));
    request.addAcctApplicationId(AcctApplicationId(...));
    request.addVendorSpecificApplicationId(VendorSpecificApplicationId(...));
    request.setFirmwareRevision(FirmwareRevision(...));
    // add more AVP as ANY values
}

void testCapabilitiesExchangeAnswer() {
    diameter::base::CapabilitiesExchangeAnswer answer;

    answer.setResultCode(ResultCode(...));
    answer.setOriginHost(OriginHost(...));
    answer.setOriginRealm(OriginRealm(...));
    answer.addHostIPAddress(HostIPAddress(...));
    answer.setVendorId(VendorId(...));
    answer.setProductName(ProductName(...));
    answer.setOriginStateId(OriginStateId(...));
    answer.setErrorMessage(ErrorMessage(...));
    answer.addFailedAVP(FailedAVP(...));
    answer.addSupportedVendorId(SupportedVendorId(...));
    answer.addAuthApplicationId(AuthApplicationId(...));
    answer.addInbandSecurityId(InbandSecurityId(...));
    answer.addAcctApplicationId(AcctApplicationId(...));
    answer.addVendorSpecificApplicationId(VendorSpecificApplicationId(...));
    answer.setFirmwareRevision(FirmwareRevision(...));
    // add more AVP as ANY values
}
