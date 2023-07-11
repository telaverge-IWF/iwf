package diameter.s6a_r10;

import com.intellinet.diameter.*;
import diameter.*;

public class ResetTest {

    public static void testResetRequest() throws Exception {
        ResetRequest resetRequest = new ResetRequest(false, false);
        resetRequest.setSessionId(new diameter.base.SessionId("utf8string-1079681355"));
        resetRequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        resetRequest.setOriginHost(new diameter.base.OriginHost("id729932847.diameter.com"));
        resetRequest.setOriginRealm(new diameter.base.OriginRealm("id881430659.diameter.com"));
        resetRequest.setDestinationHost(new diameter.base.DestinationHost("id-1031887056.diameter.com"));
        resetRequest.setDestinationRealm(new diameter.base.DestinationRealm("id2059642426.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(372719741)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(2026061106)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(1614760582)));
            resetRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(321050918)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(-2030622166)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-1373913533)));
            // add more AVP as ANY values to supportedFeatures
            resetRequest.addSupportedFeatures(supportedFeatures);
        }
        resetRequest.addUserId(new UserId("octetstring1293294286"));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-503181050.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring504244825"));
            // add more AVP as ANY values to proxyInfo
            resetRequest.addProxyInfo(proxyInfo);
        }
        resetRequest.addRouteRecord(new diameter.base.RouteRecord("id-1949784776.diameter.com"));
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
        resetAnswer.setSessionId(new diameter.base.SessionId("utf8string168966349"));
        resetAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        resetAnswer.setOriginHost(new diameter.base.OriginHost("id26470544.diameter.com"));
        resetAnswer.setOriginRealm(new diameter.base.OriginRealm("id-722611587.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-1388705876)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(959522957)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-942004344)));
            resetAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        resetAnswer.setResultCode(new diameter.base.ResultCode(new Integer(-864709720)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(1047603178)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(-1499922956)));
            resetAnswer.setExperimentalResult(experimentalResult);
        }
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(957233987)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(-380247550)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-925979245)));
            // add more AVP as ANY values to supportedFeatures
            resetAnswer.addSupportedFeatures(supportedFeatures);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id425435605.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-1389147036"));
            // add more AVP as ANY values to proxyInfo
            resetAnswer.addProxyInfo(proxyInfo);
        }
        resetAnswer.addRouteRecord(new diameter.base.RouteRecord("id-1676901051.diameter.com"));
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
