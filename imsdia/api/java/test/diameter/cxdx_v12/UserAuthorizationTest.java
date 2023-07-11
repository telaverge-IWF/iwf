package diameter.cxdx_v12;

import com.intellinet.diameter.*;
import diameter.*;

public class UserAuthorizationTest {

    public static void testUserAuthorizationRequest() throws Exception {
        UserAuthorizationRequest userAuthorizationRequest = new UserAuthorizationRequest(false, false);
        userAuthorizationRequest.setSessionId(new diameter.base.SessionId("utf8string-731908582"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-777277754)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-1539708369)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(709861387)));
            userAuthorizationRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        userAuthorizationRequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        userAuthorizationRequest.setOriginHost(new diameter.base.OriginHost("id145615014.diameter.com"));
        userAuthorizationRequest.setOriginRealm(new diameter.base.OriginRealm("id-1009957543.diameter.com"));
        userAuthorizationRequest.setDestinationRealm(new diameter.base.DestinationRealm("id1424340912.diameter.com"));
        userAuthorizationRequest.setUserName(new diameter.base.UserName("utf8string-1959199368"));
        userAuthorizationRequest.setPublicIdentity(new PublicIdentity("utf8string473597395"));
        userAuthorizationRequest.setVisitedNetworkIdentifier(new VisitedNetworkIdentifier("octetstring1580504830"));
        userAuthorizationRequest.setDestinationHost(new diameter.base.DestinationHost("id-1435158235.diameter.com"));
        userAuthorizationRequest.setUARFlags(new UARFlags(new Integer(470947763)));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(143534796)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(743770222)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(1391337224)));
            // add more AVP as ANY values to supportedFeatures
            userAuthorizationRequest.addSupportedFeatures(supportedFeatures);
        }
        userAuthorizationRequest.setUserAuthorizationType(new UserAuthorizationType(UserAuthorizationType.Value.REGISTRATION_AND_CAPABILITIES));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-1460648096.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-136018124"));
            // add more AVP as ANY values to proxyInfo
            userAuthorizationRequest.addProxyInfo(proxyInfo);
        }
        userAuthorizationRequest.addRouteRecord(new diameter.base.RouteRecord("id1414979577.diameter.com"));
        // add more AVP as ANY values to userAuthorizationRequest

        byte[] buffer = userAuthorizationRequest.encode();
        UserAuthorizationRequest userAuthorizationRequest2 = new UserAuthorizationRequest(buffer);
        String s1 = userAuthorizationRequest.toString();
        String s2 = userAuthorizationRequest2.toString();
        if (!s1.equals(s2)) {
            System.err.println("userAuthorizationRequest1 = " + s1);
            System.err.println("userAuthorizationRequest2 = " + s2);
            throw new VerificationException("UserAuthorizationRequest encoding/decoding failure");
        }
    }

    public static void testUserAuthorizationAnswer() throws Exception {
        UserAuthorizationAnswer userAuthorizationAnswer = new UserAuthorizationAnswer(false, false);
        userAuthorizationAnswer.setSessionId(new diameter.base.SessionId("utf8string2070545804"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(842085475)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-1950604610)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(1898947945)));
            userAuthorizationAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        userAuthorizationAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        userAuthorizationAnswer.setOriginHost(new diameter.base.OriginHost("id-385877858.diameter.com"));
        userAuthorizationAnswer.setOriginRealm(new diameter.base.OriginRealm("id-1908400061.diameter.com"));
        userAuthorizationAnswer.setResultCode(new diameter.base.ResultCode(new Integer(-1227777096)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(-237364946)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(1470294279)));
            userAuthorizationAnswer.setExperimentalResult(experimentalResult);
        }
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(148564193)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(1609215871)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-1675893009)));
            // add more AVP as ANY values to supportedFeatures
            userAuthorizationAnswer.addSupportedFeatures(supportedFeatures);
        }
        userAuthorizationAnswer.setServerName(new ServerName("utf8string396204081"));
        {
            ServerCapabilities serverCapabilities = new ServerCapabilities();
            serverCapabilities.addMandatoryCapability(new MandatoryCapability(new Integer(-1347013116)));
            serverCapabilities.addOptionalCapability(new OptionalCapability(new Integer(1617382441)));
            serverCapabilities.addServerName(new ServerName("utf8string-1498830980"));
            // add more AVP as ANY values to serverCapabilities
            userAuthorizationAnswer.setServerCapabilities(serverCapabilities);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-578696955.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring2041585678"));
            // add more AVP as ANY values to proxyInfo
            userAuthorizationAnswer.addProxyInfo(proxyInfo);
        }
        userAuthorizationAnswer.addRouteRecord(new diameter.base.RouteRecord("id-81727544.diameter.com"));
        // add more AVP as ANY values to userAuthorizationAnswer

        byte[] buffer = userAuthorizationAnswer.encode();
        UserAuthorizationAnswer userAuthorizationAnswer2 = new UserAuthorizationAnswer(buffer);
        String s1 = userAuthorizationAnswer.toString();
        String s2 = userAuthorizationAnswer2.toString();
        if (!s1.equals(s2)) {
            System.err.println("userAuthorizationAnswer1 = " + s1);
            System.err.println("userAuthorizationAnswer2 = " + s2);
            throw new VerificationException("UserAuthorizationAnswer encoding/decoding failure");
        }
    }

    public static void main(String[] args) throws Exception {
        testUserAuthorizationRequest();
        testUserAuthorizationAnswer();
    }
}
