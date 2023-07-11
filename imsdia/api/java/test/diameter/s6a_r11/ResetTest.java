package diameter.s6a_r11;

import com.intellinet.diameter.*;
import diameter.*;

public class ResetTest {

    public static void testResetRequest() throws Exception {
        ResetRequest resetRequest = new ResetRequest(false, false);
        resetRequest.setSessionId(new diameter.base.SessionId("utf8string-1670095640"));
        resetRequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        resetRequest.setOriginHost(new diameter.base.OriginHost("id-1644052891.diameter.com"));
        resetRequest.setOriginRealm(new diameter.base.OriginRealm("id1672171338.diameter.com"));
        resetRequest.setDestinationHost(new diameter.base.DestinationHost("id1082748456.diameter.com"));
        resetRequest.setDestinationRealm(new diameter.base.DestinationRealm("id-763528677.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(1669801613)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-1931757512)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-967489749)));
            resetRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(1765983654)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(291108283)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-51247326)));
            // add more AVP as ANY values to supportedFeatures
            resetRequest.addSupportedFeatures(supportedFeatures);
        }
        resetRequest.addUserId(new UserId("utf8string-804374837"));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-793055067.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-528843828"));
            // add more AVP as ANY values to proxyInfo
            resetRequest.addProxyInfo(proxyInfo);
        }
        resetRequest.addRouteRecord(new diameter.base.RouteRecord("id-1921060367.diameter.com"));
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
        resetAnswer.setSessionId(new diameter.base.SessionId("utf8string-170580471"));
        resetAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        resetAnswer.setOriginHost(new diameter.base.OriginHost("id-1778390413.diameter.com"));
        resetAnswer.setOriginRealm(new diameter.base.OriginRealm("id-874444948.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(379054200)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(1984394181)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-57723334)));
            resetAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        resetAnswer.setResultCode(new diameter.base.ResultCode(new Integer(1723602417)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(1945308)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(-1029281461)));
            resetAnswer.setExperimentalResult(experimentalResult);
        }
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-1687125050)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(351521121)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(647331853)));
            // add more AVP as ANY values to supportedFeatures
            resetAnswer.addSupportedFeatures(supportedFeatures);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-230690314.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring909616478"));
            // add more AVP as ANY values to proxyInfo
            resetAnswer.addProxyInfo(proxyInfo);
        }
        resetAnswer.addRouteRecord(new diameter.base.RouteRecord("id2128458844.diameter.com"));
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
