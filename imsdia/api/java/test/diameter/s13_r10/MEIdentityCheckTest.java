package diameter.s13_r10;

import com.intellinet.diameter.*;
import diameter.*;

public class MEIdentityCheckTest {

    public static void testMEIdentityCheckRequest() throws Exception {
        MEIdentityCheckRequest mEIdentityCheckRequest = new MEIdentityCheckRequest(false, false);
        mEIdentityCheckRequest.setSessionId(new diameter.base.SessionId("utf8string-123097757"));
        mEIdentityCheckRequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        mEIdentityCheckRequest.setOriginHost(new diameter.base.OriginHost("id-113382748.diameter.com"));
        mEIdentityCheckRequest.setOriginRealm(new diameter.base.OriginRealm("id-1977750584.diameter.com"));
        mEIdentityCheckRequest.setDestinationRealm(new diameter.base.DestinationRealm("id-1756585618.diameter.com"));
        {
            TerminalInformation terminalInformation = new TerminalInformation();
            terminalInformation.setIMEI(new IMEI("utf8string-1098535868"));
            terminalInformation.setS133GPP2MEID(new S133GPP2MEID("octetstring-1448238581"));
            terminalInformation.setSoftwareVersion(new SoftwareVersion("utf8string2095724083"));
            // add more AVP as ANY values to terminalInformation
            mEIdentityCheckRequest.setTerminalInformation(terminalInformation);
        }
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-1488638392)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-1639553913)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-1297958387)));
            mEIdentityCheckRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        mEIdentityCheckRequest.setDestinationHost(new diameter.base.DestinationHost("id-1830736578.diameter.com"));
        mEIdentityCheckRequest.setUserName(new diameter.base.UserName("utf8string-29376265"));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id569809325.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring43620012"));
            // add more AVP as ANY values to proxyInfo
            mEIdentityCheckRequest.addProxyInfo(proxyInfo);
        }
        mEIdentityCheckRequest.addRouteRecord(new diameter.base.RouteRecord("id-637238743.diameter.com"));
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
        mEIdentityCheckAnswer.setSessionId(new diameter.base.SessionId("utf8string-884542526"));
        mEIdentityCheckAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        mEIdentityCheckAnswer.setOriginHost(new diameter.base.OriginHost("id-737421463.diameter.com"));
        mEIdentityCheckAnswer.setOriginRealm(new diameter.base.OriginRealm("id-763451273.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(1626191419)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(362985529)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(264956134)));
            mEIdentityCheckAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        mEIdentityCheckAnswer.setResultCode(new diameter.base.ResultCode(new Integer(691810496)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(61174144)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(88037507)));
            mEIdentityCheckAnswer.setExperimentalResult(experimentalResult);
        }
        mEIdentityCheckAnswer.setEquipmentStatus(new EquipmentStatus(EquipmentStatus.Value.WHITELISTED));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id759135429.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring1822141629"));
            // add more AVP as ANY values to proxyInfo
            mEIdentityCheckAnswer.addProxyInfo(proxyInfo);
        }
        mEIdentityCheckAnswer.addRouteRecord(new diameter.base.RouteRecord("id970789027.diameter.com"));
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
