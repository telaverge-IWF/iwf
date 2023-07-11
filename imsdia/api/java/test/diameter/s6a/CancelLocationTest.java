package diameter.s6a;

import com.intellinet.diameter.*;
import diameter.*;

public class CancelLocationTest {

    public static void testCancelLocationRequest() throws Exception {
        CancelLocationRequest cancelLocationRequest = new CancelLocationRequest(false, false);
        cancelLocationRequest.setSessionId(new diameter.base.SessionId("utf8string1067293343"));
        cancelLocationRequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        cancelLocationRequest.setOriginHost(new diameter.base.OriginHost("id-1088162968.diameter.com"));
        cancelLocationRequest.setOriginRealm(new diameter.base.OriginRealm("id-2028150358.diameter.com"));
        cancelLocationRequest.setDestinationHost(new diameter.base.DestinationHost("id-234988032.diameter.com"));
        cancelLocationRequest.setDestinationRealm(new diameter.base.DestinationRealm("id-1882818637.diameter.com"));
        cancelLocationRequest.setUserName(new diameter.base.UserName("utf8string2044292350"));
        cancelLocationRequest.setCancellationType(new CancellationType(CancellationType.Value.MME_UPDATE_PROCEDURE));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(1786006591)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(541729315)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(1206344418)));
            cancelLocationRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-639547713)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(-1832322847)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(177118476)));
            // add more AVP as ANY values to supportedFeatures
            cancelLocationRequest.addSupportedFeatures(supportedFeatures);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-1806043815.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-1879873515"));
            // add more AVP as ANY values to proxyInfo
            cancelLocationRequest.addProxyInfo(proxyInfo);
        }
        cancelLocationRequest.addRouteRecord(new diameter.base.RouteRecord("id-1627806258.diameter.com"));
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
        cancelLocationAnswer.setSessionId(new diameter.base.SessionId("utf8string222165565"));
        cancelLocationAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        cancelLocationAnswer.setOriginHost(new diameter.base.OriginHost("id622261422.diameter.com"));
        cancelLocationAnswer.setOriginRealm(new diameter.base.OriginRealm("id-1174929849.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-1448703705)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-1919136974)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-991264878)));
            cancelLocationAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-1849225961)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(-516791543)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-499769161)));
            // add more AVP as ANY values to supportedFeatures
            cancelLocationAnswer.addSupportedFeatures(supportedFeatures);
        }
        cancelLocationAnswer.setResultCode(new diameter.base.ResultCode(new Integer(489440827)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(-508239352)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(-108456628)));
            cancelLocationAnswer.setExperimentalResult(experimentalResult);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id258162430.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring1437662110"));
            // add more AVP as ANY values to proxyInfo
            cancelLocationAnswer.addProxyInfo(proxyInfo);
        }
        cancelLocationAnswer.addRouteRecord(new diameter.base.RouteRecord("id1619303064.diameter.com"));
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
