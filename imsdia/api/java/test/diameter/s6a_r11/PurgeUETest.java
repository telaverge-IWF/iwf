package diameter.s6a_r11;

import com.intellinet.diameter.*;
import diameter.*;

public class PurgeUETest {

    public static void testPurgeUERequest() throws Exception {
        PurgeUERequest purgeUERequest = new PurgeUERequest(false, false);
        purgeUERequest.setSessionId(new diameter.base.SessionId("utf8string27839574"));
        purgeUERequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        purgeUERequest.setOriginHost(new diameter.base.OriginHost("id914927303.diameter.com"));
        purgeUERequest.setOriginRealm(new diameter.base.OriginRealm("id-1930497701.diameter.com"));
        purgeUERequest.setDestinationRealm(new diameter.base.DestinationRealm("id-1848000922.diameter.com"));
        purgeUERequest.setUserName(new diameter.base.UserName("utf8string-781851185"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(1473925000)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(1376825231)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-73906386)));
            purgeUERequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        purgeUERequest.setDestinationHost(new diameter.base.DestinationHost("id743510287.diameter.com"));
        purgeUERequest.setPURFlags(new PURFlags(new Integer(-1231812907)));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(1005001016)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(1403349640)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-2129385851)));
            // add more AVP as ANY values to supportedFeatures
            purgeUERequest.addSupportedFeatures(supportedFeatures);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id2115009095.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring631402607"));
            // add more AVP as ANY values to proxyInfo
            purgeUERequest.addProxyInfo(proxyInfo);
        }
        purgeUERequest.addRouteRecord(new diameter.base.RouteRecord("id-1651738559.diameter.com"));
        // add more AVP as ANY values to purgeUERequest

        byte[] buffer = purgeUERequest.encode();
        PurgeUERequest purgeUERequest2 = new PurgeUERequest(buffer);
        String s1 = purgeUERequest.toString();
        String s2 = purgeUERequest2.toString();
        if (!s1.equals(s2)) {
            System.err.println("purgeUERequest1 = " + s1);
            System.err.println("purgeUERequest2 = " + s2);
            throw new VerificationException("PurgeUERequest encoding/decoding failure");
        }
    }

    public static void testPurgeUEAnswer() throws Exception {
        PurgeUEAnswer purgeUEAnswer = new PurgeUEAnswer(false, false);
        purgeUEAnswer.setSessionId(new diameter.base.SessionId("utf8string466004081"));
        purgeUEAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        purgeUEAnswer.setOriginHost(new diameter.base.OriginHost("id-129951448.diameter.com"));
        purgeUEAnswer.setOriginRealm(new diameter.base.OriginRealm("id1166078681.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(1129750866)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(812524169)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(1892274631)));
            purgeUEAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        purgeUEAnswer.setPUAFlags(new PUAFlags(new Integer(1450024582)));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(354394265)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(-485980534)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(1788371193)));
            // add more AVP as ANY values to supportedFeatures
            purgeUEAnswer.addSupportedFeatures(supportedFeatures);
        }
        purgeUEAnswer.setResultCode(new diameter.base.ResultCode(new Integer(406256766)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(1017663136)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(1303415961)));
            purgeUEAnswer.setExperimentalResult(experimentalResult);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-1352217407.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring160675446"));
            // add more AVP as ANY values to proxyInfo
            purgeUEAnswer.addProxyInfo(proxyInfo);
        }
        purgeUEAnswer.addRouteRecord(new diameter.base.RouteRecord("id1527827417.diameter.com"));
        // add more AVP as ANY values to purgeUEAnswer

        byte[] buffer = purgeUEAnswer.encode();
        PurgeUEAnswer purgeUEAnswer2 = new PurgeUEAnswer(buffer);
        String s1 = purgeUEAnswer.toString();
        String s2 = purgeUEAnswer2.toString();
        if (!s1.equals(s2)) {
            System.err.println("purgeUEAnswer1 = " + s1);
            System.err.println("purgeUEAnswer2 = " + s2);
            throw new VerificationException("PurgeUEAnswer encoding/decoding failure");
        }
    }

    public static void main(String[] args) throws Exception {
        testPurgeUERequest();
        testPurgeUEAnswer();
    }
}
