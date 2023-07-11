package diameter.s6a;

import com.intellinet.diameter.*;
import diameter.*;

public class ResetTest {

    public static void testResetRequest() throws Exception {
        ResetRequest resetRequest = new ResetRequest(false, false);
        resetRequest.setSessionId(new diameter.base.SessionId("utf8string-1234487080"));
        resetRequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        resetRequest.setOriginHost(new diameter.base.OriginHost("id1920820936.diameter.com"));
        resetRequest.setOriginRealm(new diameter.base.OriginRealm("id1345494722.diameter.com"));
        resetRequest.setDestinationHost(new diameter.base.DestinationHost("id-384958728.diameter.com"));
        resetRequest.setDestinationRealm(new diameter.base.DestinationRealm("id2098880947.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(1110227777)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(1635533443)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-1350718867)));
            resetRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-1390322712)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(-720713922)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(333836668)));
            // add more AVP as ANY values to supportedFeatures
            resetRequest.addSupportedFeatures(supportedFeatures);
        }
        resetRequest.addUserId(new UserId("octetstring-1625499371"));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-1013554111.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring793933891"));
            // add more AVP as ANY values to proxyInfo
            resetRequest.addProxyInfo(proxyInfo);
        }
        resetRequest.addRouteRecord(new diameter.base.RouteRecord("id306758991.diameter.com"));
        // add more AVP as ANY values to resetRequest

        byte[] buffer = resetRequest.encode();
        ResetRequest resetRequest2 = new ResetRequest(buffer);
        String s1 = resetRequest.toString();
        String s2 = resetRequest2.toString();
        if (!s1.equals(s2)) {
            System.err.println("resetRequest1 = " + s1);
            System.err.println("resetRequest2 = " + s2);
            throw new VerificationException("ResetRequest encoding/decoding failure");
        }
    }

    public static void testResetAnswer() throws Exception {
        ResetAnswer resetAnswer = new ResetAnswer(false, false);
        resetAnswer.setSessionId(new diameter.base.SessionId("utf8string-1393056243"));
        resetAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        resetAnswer.setOriginHost(new diameter.base.OriginHost("id-318797601.diameter.com"));
        resetAnswer.setOriginRealm(new diameter.base.OriginRealm("id1206226332.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(1145608018)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-1018864916)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(488399081)));
            resetAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        resetAnswer.setResultCode(new diameter.base.ResultCode(new Integer(-289774337)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(766263722)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(-447563089)));
            resetAnswer.setExperimentalResult(experimentalResult);
        }
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-539544053)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(1265115453)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(982566596)));
            // add more AVP as ANY values to supportedFeatures
            resetAnswer.addSupportedFeatures(supportedFeatures);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-1361200929.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-1347800956"));
            // add more AVP as ANY values to proxyInfo
            resetAnswer.addProxyInfo(proxyInfo);
        }
        resetAnswer.addRouteRecord(new diameter.base.RouteRecord("id-1056828743.diameter.com"));
        // add more AVP as ANY values to resetAnswer

        byte[] buffer = resetAnswer.encode();
        ResetAnswer resetAnswer2 = new ResetAnswer(buffer);
        String s1 = resetAnswer.toString();
        String s2 = resetAnswer2.toString();
        if (!s1.equals(s2)) {
            System.err.println("resetAnswer1 = " + s1);
            System.err.println("resetAnswer2 = " + s2);
            throw new VerificationException("ResetAnswer encoding/decoding failure");
        }
    }

    public static void main(String[] args) throws Exception {
        testResetRequest();
        testResetAnswer();
    }
}
