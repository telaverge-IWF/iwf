package diameter.s6a_r11;

import com.intellinet.diameter.*;
import diameter.*;

public class CancelLocationTest {

    public static void testCancelLocationRequest() throws Exception {
        CancelLocationRequest cancelLocationRequest = new CancelLocationRequest(false, false);
        cancelLocationRequest.setSessionId(new diameter.base.SessionId("utf8string-1972549824"));
        cancelLocationRequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        cancelLocationRequest.setOriginHost(new diameter.base.OriginHost("id-305897250.diameter.com"));
        cancelLocationRequest.setOriginRealm(new diameter.base.OriginRealm("id-581708802.diameter.com"));
        cancelLocationRequest.setDestinationHost(new diameter.base.DestinationHost("id561214061.diameter.com"));
        cancelLocationRequest.setDestinationRealm(new diameter.base.DestinationRealm("id938371788.diameter.com"));
        cancelLocationRequest.setUserName(new diameter.base.UserName("utf8string-1567523153"));
        cancelLocationRequest.setCancellationType(new CancellationType(CancellationType.Value.MME_UPDATE_PROCEDURE));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(2137855612)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(1302855081)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-1774413949)));
            cancelLocationRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        cancelLocationRequest.setCLRFlags(new CLRFlags(new Integer(826515075)));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(938944168)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(1741129646)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-1432929097)));
            // add more AVP as ANY values to supportedFeatures
            cancelLocationRequest.addSupportedFeatures(supportedFeatures);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-1138023956.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring1069637719"));
            // add more AVP as ANY values to proxyInfo
            cancelLocationRequest.addProxyInfo(proxyInfo);
        }
        cancelLocationRequest.addRouteRecord(new diameter.base.RouteRecord("id360064236.diameter.com"));
        // add more AVP as ANY values to cancelLocationRequest

        byte[] buffer = cancelLocationRequest.encode();
        CancelLocationRequest cancelLocationRequest2 = new CancelLocationRequest(buffer);
        String s1 = cancelLocationRequest.toString();
        String s2 = cancelLocationRequest2.toString();
        if (!s1.equals(s2)) {
            System.err.println("cancelLocationRequest1 = " + s1);
            System.err.println("cancelLocationRequest2 = " + s2);
            throw new VerificationException("CancelLocationRequest encoding/decoding failure");
        }
    }

    public static void testCancelLocationAnswer() throws Exception {
        CancelLocationAnswer cancelLocationAnswer = new CancelLocationAnswer(false, false);
        cancelLocationAnswer.setSessionId(new diameter.base.SessionId("utf8string1000711758"));
        cancelLocationAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        cancelLocationAnswer.setOriginHost(new diameter.base.OriginHost("id136075681.diameter.com"));
        cancelLocationAnswer.setOriginRealm(new diameter.base.OriginRealm("id1392676350.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(989056789)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-1441668419)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-444894189)));
            cancelLocationAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-1274966658)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(668839687)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-490665545)));
            // add more AVP as ANY values to supportedFeatures
            cancelLocationAnswer.addSupportedFeatures(supportedFeatures);
        }
        cancelLocationAnswer.setResultCode(new diameter.base.ResultCode(new Integer(-321079377)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(1459345594)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(-550094862)));
            cancelLocationAnswer.setExperimentalResult(experimentalResult);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-1119760145.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-1297819081"));
            // add more AVP as ANY values to proxyInfo
            cancelLocationAnswer.addProxyInfo(proxyInfo);
        }
        cancelLocationAnswer.addRouteRecord(new diameter.base.RouteRecord("id-2108407897.diameter.com"));
        // add more AVP as ANY values to cancelLocationAnswer

        byte[] buffer = cancelLocationAnswer.encode();
        CancelLocationAnswer cancelLocationAnswer2 = new CancelLocationAnswer(buffer);
        String s1 = cancelLocationAnswer.toString();
        String s2 = cancelLocationAnswer2.toString();
        if (!s1.equals(s2)) {
            System.err.println("cancelLocationAnswer1 = " + s1);
            System.err.println("cancelLocationAnswer2 = " + s2);
            throw new VerificationException("CancelLocationAnswer encoding/decoding failure");
        }
    }

    public static void main(String[] args) throws Exception {
        testCancelLocationRequest();
        testCancelLocationAnswer();
    }
}
