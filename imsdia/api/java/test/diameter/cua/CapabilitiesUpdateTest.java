package diameter.cua;

import com.intellinet.diameter.*;
import diameter.*;

public class CapabilitiesUpdateTest {

    public static void testCapabilitiesUpdateRequest() throws Exception {
        CapabilitiesUpdateRequest capabilitiesUpdateRequest = new CapabilitiesUpdateRequest(false, false);
        capabilitiesUpdateRequest.setOriginHost(new diameter.base.OriginHost("id1491169163.diameter.com"));
        capabilitiesUpdateRequest.setOriginRealm(new diameter.base.OriginRealm("id180417990.diameter.com"));
        capabilitiesUpdateRequest.addHostIPAddress(new diameter.base.HostIPAddress(new Address(Address.Family.IPV4, "18.226.155.29")));
        capabilitiesUpdateRequest.setVendorId(new diameter.base.VendorId(new Integer(-1123243698)));
        capabilitiesUpdateRequest.setProductName(new diameter.base.ProductName("utf8string1027413281"));
        capabilitiesUpdateRequest.setOriginStateId(new diameter.base.OriginStateId(new Integer(540257777)));
        capabilitiesUpdateRequest.addSupportedVendorId(new diameter.base.SupportedVendorId(new Integer(183781445)));
        capabilitiesUpdateRequest.addAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-1163175665)));
        capabilitiesUpdateRequest.addAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(1287393333)));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(760833660)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-307259283)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-1508995245)));
            capabilitiesUpdateRequest.addVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        capabilitiesUpdateRequest.setFirmwareRevision(new diameter.base.FirmwareRevision(new Integer(-1447667789)));
        // add more AVP as ANY values to capabilitiesUpdateRequest

        byte[] buffer = capabilitiesUpdateRequest.encode();
        CapabilitiesUpdateRequest capabilitiesUpdateRequest2 = new CapabilitiesUpdateRequest(buffer);
        String s1 = capabilitiesUpdateRequest.toString();
        String s2 = capabilitiesUpdateRequest2.toString();
        if (!s1.equals(s2)) {
            System.err.println("capabilitiesUpdateRequest1 = " + s1);
            System.err.println("capabilitiesUpdateRequest2 = " + s2);
            throw new VerificationException("CapabilitiesUpdateRequest encoding/decoding failure");
        }
    }

    public static void testCapabilitiesUpdateAnswer() throws Exception {
        CapabilitiesUpdateAnswer capabilitiesUpdateAnswer = new CapabilitiesUpdateAnswer(false, false);
        capabilitiesUpdateAnswer.setOriginHost(new diameter.base.OriginHost("id-613431836.diameter.com"));
        capabilitiesUpdateAnswer.setOriginRealm(new diameter.base.OriginRealm("id-1364009290.diameter.com"));
        capabilitiesUpdateAnswer.setResultCode(new diameter.base.ResultCode(new Integer(-328010964)));
        capabilitiesUpdateAnswer.setErrorMessage(new diameter.base.ErrorMessage("utf8string-644606090"));
        // add more AVP as ANY values to capabilitiesUpdateAnswer

        byte[] buffer = capabilitiesUpdateAnswer.encode();
        CapabilitiesUpdateAnswer capabilitiesUpdateAnswer2 = new CapabilitiesUpdateAnswer(buffer);
        String s1 = capabilitiesUpdateAnswer.toString();
        String s2 = capabilitiesUpdateAnswer2.toString();
        if (!s1.equals(s2)) {
            System.err.println("capabilitiesUpdateAnswer1 = " + s1);
            System.err.println("capabilitiesUpdateAnswer2 = " + s2);
            throw new VerificationException("CapabilitiesUpdateAnswer encoding/decoding failure");
        }
    }

    public static void main(String[] args) throws Exception {
        testCapabilitiesUpdateRequest();
        testCapabilitiesUpdateAnswer();
    }
}
