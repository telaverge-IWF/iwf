package diameter.cxdx_v12;

import com.intellinet.diameter.*;
import diameter.*;

public class LocationInfoTest {

    public static void testLocationInfoRequest() throws Exception {
        LocationInfoRequest locationInfoRequest = new LocationInfoRequest(false, false);
        locationInfoRequest.setSessionId(new diameter.base.SessionId("utf8string-490957194"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(785406130)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(1749021492)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(1874962469)));
            locationInfoRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        locationInfoRequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        locationInfoRequest.setOriginHost(new diameter.base.OriginHost("id-1901440031.diameter.com"));
        locationInfoRequest.setOriginRealm(new diameter.base.OriginRealm("id1272508070.diameter.com"));
        locationInfoRequest.setDestinationRealm(new diameter.base.DestinationRealm("id-1111896807.diameter.com"));
        locationInfoRequest.setPublicIdentity(new PublicIdentity("utf8string-1395268895"));
        locationInfoRequest.setDestinationHost(new diameter.base.DestinationHost("id-43930835.diameter.com"));
        locationInfoRequest.setOriginatingRequest(new OriginatingRequest(OriginatingRequest.Value.ORIGINATING));
        locationInfoRequest.setUserAuthorizationType(new UserAuthorizationType(UserAuthorizationType.Value.REGISTRATION_AND_CAPABILITIES));
        locationInfoRequest.setSessionPriority(new SessionPriority(SessionPriority.Value.PRIORITY2));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(335297234)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(1021729962)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-2057496296)));
            // add more AVP as ANY values to supportedFeatures
            locationInfoRequest.addSupportedFeatures(supportedFeatures);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-461362609.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring1991448995"));
            // add more AVP as ANY values to proxyInfo
            locationInfoRequest.addProxyInfo(proxyInfo);
        }
        locationInfoRequest.addRouteRecord(new diameter.base.RouteRecord("id-1181473725.diameter.com"));
        // add more AVP as ANY values to locationInfoRequest

        byte[] buffer = locationInfoRequest.encode();
        LocationInfoRequest locationInfoRequest2 = new LocationInfoRequest(buffer);
        String s1 = locationInfoRequest.toString();
        String s2 = locationInfoRequest2.toString();
        if (!s1.equals(s2)) {
            System.err.println("locationInfoRequest1 = " + s1);
            System.err.println("locationInfoRequest2 = " + s2);
            throw new VerificationException("LocationInfoRequest encoding/decoding failure");
        }
    }

    public static void testLocationInfoAnswer() throws Exception {
        LocationInfoAnswer locationInfoAnswer = new LocationInfoAnswer(false, false);
        locationInfoAnswer.setSessionId(new diameter.base.SessionId("utf8string1874303113"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(90196771)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-1415355583)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(1253205056)));
            locationInfoAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        locationInfoAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        locationInfoAnswer.setOriginHost(new diameter.base.OriginHost("id-927693917.diameter.com"));
        locationInfoAnswer.setOriginRealm(new diameter.base.OriginRealm("id-461049463.diameter.com"));
        locationInfoAnswer.setResultCode(new diameter.base.ResultCode(new Integer(1324461199)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(43458697)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(-1231243545)));
            locationInfoAnswer.setExperimentalResult(experimentalResult);
        }
        locationInfoAnswer.setWildcardedPublicIdentity(new WildcardedPublicIdentity("utf8string-24200882"));
        locationInfoAnswer.setLIAFlags(new LIAFlags(new Integer(1712755250)));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(2102448359)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(-1938189564)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-638075320)));
            // add more AVP as ANY values to supportedFeatures
            locationInfoAnswer.addSupportedFeatures(supportedFeatures);
        }
        locationInfoAnswer.setServerName(new ServerName("utf8string184469025"));
        {
            ServerCapabilities serverCapabilities = new ServerCapabilities();
            serverCapabilities.addMandatoryCapability(new MandatoryCapability(new Integer(122447937)));
            serverCapabilities.addOptionalCapability(new OptionalCapability(new Integer(-2123899761)));
            serverCapabilities.addServerName(new ServerName("utf8string1576981067"));
            // add more AVP as ANY values to serverCapabilities
            locationInfoAnswer.setServerCapabilities(serverCapabilities);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-1666828690.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring1369686185"));
            // add more AVP as ANY values to proxyInfo
            locationInfoAnswer.addProxyInfo(proxyInfo);
        }
        locationInfoAnswer.addRouteRecord(new diameter.base.RouteRecord("id-366580129.diameter.com"));
        // add more AVP as ANY values to locationInfoAnswer

        byte[] buffer = locationInfoAnswer.encode();
        LocationInfoAnswer locationInfoAnswer2 = new LocationInfoAnswer(buffer);
        String s1 = locationInfoAnswer.toString();
        String s2 = locationInfoAnswer2.toString();
        if (!s1.equals(s2)) {
            System.err.println("locationInfoAnswer1 = " + s1);
            System.err.println("locationInfoAnswer2 = " + s2);
            throw new VerificationException("LocationInfoAnswer encoding/decoding failure");
        }
    }

    public static void main(String[] args) throws Exception {
        testLocationInfoRequest();
        testLocationInfoAnswer();
    }
}
