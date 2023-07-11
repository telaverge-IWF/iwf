#include <diameter/Exceptions.h>
#include <diameter/cua/CapabilitiesUpdate.h>

void testCapabilitiesUpdateRequest() {
    diameter::cua::CapabilitiesUpdateRequest request;

    request.setOriginHost(diameter::base::OriginHost(...));
    request.setOriginRealm(diameter::base::OriginRealm(...));
    request.addHostIPAddress(diameter::base::HostIPAddress(...));
    request.setVendorId(diameter::base::VendorId(...));
    request.setProductName(diameter::base::ProductName(...));
    request.setOriginStateId(diameter::base::OriginStateId(...));
    request.addSupportedVendorId(diameter::base::SupportedVendorId(...));
    request.addAuthApplicationId(diameter::base::AuthApplicationId(...));
    request.addAcctApplicationId(diameter::base::AcctApplicationId(...));
    request.addVendorSpecificApplicationId(diameter::base::VendorSpecificApplicationId(...));
    request.setFirmwareRevision(diameter::base::FirmwareRevision(...));
    // add more AVP as ANY values
}

void testCapabilitiesUpdateAnswer() {
    diameter::cua::CapabilitiesUpdateAnswer answer;

    answer.setOriginHost(diameter::base::OriginHost(...));
    answer.setOriginRealm(diameter::base::OriginRealm(...));
    answer.setResultCode(diameter::base::ResultCode(...));
    answer.setErrorMessage(diameter::base::ErrorMessage(...));
    // add more AVP as ANY values
}
