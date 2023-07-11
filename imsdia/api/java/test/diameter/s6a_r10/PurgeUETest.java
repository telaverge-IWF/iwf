package diameter.s6a_r10;

import com.intellinet.diameter.*;
import diameter.*;

public class PurgeUETest {

    public static void testPurgeUERequest() throws Exception {
        PurgeUERequest purgeUERequest = new PurgeUERequest(false, false);
        purgeUERequest.setSessionId(new diameter.base.SessionId("utf8string-1341054610"));
        purgeUERequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        purgeUERequest.setOriginHost(new diameter.base.OriginHost("id-2001331883.diameter.com"));
        purgeUERequest.setOriginRealm(new diameter.base.OriginRealm("id-2044550925.diameter.com"));
        purgeUERequest.setDestinationRealm(new diameter.base.DestinationRealm("id-389810922.diameter.com"));
        purgeUERequest.setUserName(new diameter.base.UserName("utf8string-827640449"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(1628929014)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(1415133770)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(1765920019)));
            purgeUERequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        purgeUERequest.setDestinationHost(new diameter.base.DestinationHost("id-765147570.diameter.com"));
        purgeUERequest.setPURFlags(new PURFlags(new Integer(-823003769)));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(1291026152)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(229447714)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(719829682)));
            // add more AVP as ANY values to supportedFeatures
            purgeUERequest.addSupportedFeatures(supportedFeatures);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-1185953294.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring2133754135"));
            // add more AVP as ANY values to proxyInfo
            purgeUERequest.addProxyInfo(proxyInfo);
        }
        purgeUERequest.addRouteRecord(new diameter.base.RouteRecord("id218524715.diameter.com"));
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
        purgeUEAnswer.setSessionId(new diameter.base.SessionId("utf8string-132843397"));
        purgeUEAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        purgeUEAnswer.setOriginHost(new diameter.base.OriginHost("id1063004961.diameter.com"));
        purgeUEAnswer.setOriginRealm(new diameter.base.OriginRealm("id-1675639845.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(1143073602)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(1686096650)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(1137383663)));
            purgeUEAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        purgeUEAnswer.setPUAFlags(new PUAFlags(new Integer(1695383920)));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-625921875)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(980827116)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(1042278387)));
            // add more AVP as ANY values to supportedFeatures
            purgeUEAnswer.addSupportedFeatures(supportedFeatures);
        }
        purgeUEAnswer.setResultCode(new diameter.base.ResultCode(new Integer(1847872211)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(-250395407)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(2120682810)));
            purgeUEAnswer.setExperimentalResult(experimentalResult);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-434560697.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-990899477"));
            // add more AVP as ANY values to proxyInfo
            purgeUEAnswer.addProxyInfo(proxyInfo);
        }
        purgeUEAnswer.addRouteRecord(new diameter.base.RouteRecord("id1430713240.diameter.com"));
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
