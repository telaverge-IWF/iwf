package diameter.s6a;

import com.intellinet.diameter.*;
import diameter.*;

public class PurgeUETest {

    public static void testPurgeUERequest() throws Exception {
        PurgeUERequest purgeUERequest = new PurgeUERequest(false, false);
        purgeUERequest.setSessionId(new diameter.base.SessionId("utf8string15988642"));
        purgeUERequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        purgeUERequest.setOriginHost(new diameter.base.OriginHost("id419839688.diameter.com"));
        purgeUERequest.setOriginRealm(new diameter.base.OriginRealm("id-1923120498.diameter.com"));
        purgeUERequest.setDestinationRealm(new diameter.base.DestinationRealm("id-348706725.diameter.com"));
        purgeUERequest.setUserName(new diameter.base.UserName("utf8string-119393168"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-876328662)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-377059490)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-1471545408)));
            purgeUERequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        purgeUERequest.setDestinationHost(new diameter.base.DestinationHost("id533322278.diameter.com"));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(1747592101)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(-616562859)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-840000520)));
            // add more AVP as ANY values to supportedFeatures
            purgeUERequest.addSupportedFeatures(supportedFeatures);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-2102307428.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-1696126485"));
            // add more AVP as ANY values to proxyInfo
            purgeUERequest.addProxyInfo(proxyInfo);
        }
        purgeUERequest.addRouteRecord(new diameter.base.RouteRecord("id633504581.diameter.com"));
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
        purgeUEAnswer.setSessionId(new diameter.base.SessionId("utf8string66460376"));
        purgeUEAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        purgeUEAnswer.setOriginHost(new diameter.base.OriginHost("id696676113.diameter.com"));
        purgeUEAnswer.setOriginRealm(new diameter.base.OriginRealm("id733618154.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-554590823)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-1893395720)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-2102506911)));
            purgeUEAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        purgeUEAnswer.setPUAFlags(new PUAFlags(new Integer(508412971)));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(1698911178)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(-1886789316)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-1475650193)));
            // add more AVP as ANY values to supportedFeatures
            purgeUEAnswer.addSupportedFeatures(supportedFeatures);
        }
        purgeUEAnswer.setResultCode(new diameter.base.ResultCode(new Integer(-1340682337)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(-2042576505)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(2000886792)));
            purgeUEAnswer.setExperimentalResult(experimentalResult);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id1167943529.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-1339783854"));
            // add more AVP as ANY values to proxyInfo
            purgeUEAnswer.addProxyInfo(proxyInfo);
        }
        purgeUEAnswer.addRouteRecord(new diameter.base.RouteRecord("id-126438165.diameter.com"));
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
