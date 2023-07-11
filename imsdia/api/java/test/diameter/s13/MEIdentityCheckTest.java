package diameter.s13;

import com.intellinet.diameter.*;
import diameter.*;

public class MEIdentityCheckTest {

    public static void testMEIdentityCheckRequest() throws Exception {
        MEIdentityCheckRequest mEIdentityCheckRequest = new MEIdentityCheckRequest(false, false);
        mEIdentityCheckRequest.setSessionId(new diameter.base.SessionId("utf8string1467776502"));
        mEIdentityCheckRequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        mEIdentityCheckRequest.setOriginHost(new diameter.base.OriginHost("id898292979.diameter.com"));
        mEIdentityCheckRequest.setOriginRealm(new diameter.base.OriginRealm("id-1170275831.diameter.com"));
        mEIdentityCheckRequest.setDestinationRealm(new diameter.base.DestinationRealm("id1337909410.diameter.com"));
        {
            TerminalInformation terminalInformation = new TerminalInformation();
            terminalInformation.setIMEI(new IMEI("utf8string351951590"));
            terminalInformation.setS133GPP2MEID(new S133GPP2MEID("octetstring2144079263"));
            terminalInformation.setSoftwareVersion(new SoftwareVersion("utf8string1029314566"));
            // add more AVP as ANY values to terminalInformation
            mEIdentityCheckRequest.setTerminalInformation(terminalInformation);
        }
        mEIdentityCheckRequest.setDestinationHost(new diameter.base.DestinationHost("id1639750686.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(886149018)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-1125788651)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(860587254)));
            mEIdentityCheckRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        mEIdentityCheckRequest.setUserName(new diameter.base.UserName("utf8string-515413271"));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id732907886.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring733873666"));
            // add more AVP as ANY values to proxyInfo
            mEIdentityCheckRequest.addProxyInfo(proxyInfo);
        }
        mEIdentityCheckRequest.addRouteRecord(new diameter.base.RouteRecord("id901769700.diameter.com"));
        // add more AVP as ANY values to mEIdentityCheckRequest

        byte[] buffer = mEIdentityCheckRequest.encode();
        MEIdentityCheckRequest mEIdentityCheckRequest2 = new MEIdentityCheckRequest(buffer);
        String s1 = mEIdentityCheckRequest.toString();
        String s2 = mEIdentityCheckRequest2.toString();
        if (!s1.equals(s2)) {
            System.err.println("mEIdentityCheckRequest1 = " + s1);
            System.err.println("mEIdentityCheckRequest2 = " + s2);
            throw new VerificationException("MEIdentityCheckRequest encoding/decoding failure");
        }
    }

    public static void testMEIdentityCheckAnswer() throws Exception {
        MEIdentityCheckAnswer mEIdentityCheckAnswer = new MEIdentityCheckAnswer(false, false);
        mEIdentityCheckAnswer.setSessionId(new diameter.base.SessionId("utf8string1243622058"));
        mEIdentityCheckAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        mEIdentityCheckAnswer.setOriginHost(new diameter.base.OriginHost("id-978867423.diameter.com"));
        mEIdentityCheckAnswer.setOriginRealm(new diameter.base.OriginRealm("id-110433319.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(1367202254)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(1807132804)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-601307407)));
            mEIdentityCheckAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        mEIdentityCheckAnswer.setResultCode(new diameter.base.ResultCode(new Integer(946195838)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(-1987159470)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(-323267453)));
            mEIdentityCheckAnswer.setExperimentalResult(experimentalResult);
        }
        mEIdentityCheckAnswer.setEquipmentStatus(new EquipmentStatus(EquipmentStatus.Value.BLACKLISTED));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id28016388.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring230690273"));
            // add more AVP as ANY values to proxyInfo
            mEIdentityCheckAnswer.addProxyInfo(proxyInfo);
        }
        mEIdentityCheckAnswer.addRouteRecord(new diameter.base.RouteRecord("id751528936.diameter.com"));
        // add more AVP as ANY values to mEIdentityCheckAnswer

        byte[] buffer = mEIdentityCheckAnswer.encode();
        MEIdentityCheckAnswer mEIdentityCheckAnswer2 = new MEIdentityCheckAnswer(buffer);
        String s1 = mEIdentityCheckAnswer.toString();
        String s2 = mEIdentityCheckAnswer2.toString();
        if (!s1.equals(s2)) {
            System.err.println("mEIdentityCheckAnswer1 = " + s1);
            System.err.println("mEIdentityCheckAnswer2 = " + s2);
            throw new VerificationException("MEIdentityCheckAnswer encoding/decoding failure");
        }
    }

    public static void main(String[] args) throws Exception {
        testMEIdentityCheckRequest();
        testMEIdentityCheckAnswer();
    }
}
