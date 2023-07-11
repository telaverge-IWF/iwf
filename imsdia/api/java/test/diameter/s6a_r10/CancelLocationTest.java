package diameter.s6a_r10;

import com.intellinet.diameter.*;
import diameter.*;

public class CancelLocationTest {

    public static void testCancelLocationRequest() throws Exception {
        CancelLocationRequest cancelLocationRequest = new CancelLocationRequest(false, false);
        cancelLocationRequest.setSessionId(new diameter.base.SessionId("utf8string1030575940"));
        cancelLocationRequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        cancelLocationRequest.setOriginHost(new diameter.base.OriginHost("id2010725536.diameter.com"));
        cancelLocationRequest.setOriginRealm(new diameter.base.OriginRealm("id1804166639.diameter.com"));
        cancelLocationRequest.setDestinationHost(new diameter.base.DestinationHost("id-385639476.diameter.com"));
        cancelLocationRequest.setDestinationRealm(new diameter.base.DestinationRealm("id1498409031.diameter.com"));
        cancelLocationRequest.setUserName(new diameter.base.UserName("utf8string1728849892"));
        cancelLocationRequest.setCancellationType(new CancellationType(CancellationType.Value.UPDATE_PROCEDURE_IWF));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(1502260499)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(1848314387)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(185026349)));
            cancelLocationRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        cancelLocationRequest.setCLRFlags(new CLRFlags(new Integer(-1929094466)));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-380190282)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(-812092842)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(2064288503)));
            // add more AVP as ANY values to supportedFeatures
            cancelLocationRequest.addSupportedFeatures(supportedFeatures);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-1385371461.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring1619382981"));
            // add more AVP as ANY values to proxyInfo
            cancelLocationRequest.addProxyInfo(proxyInfo);
        }
        cancelLocationRequest.addRouteRecord(new diameter.base.RouteRecord("id-1840890131.diameter.com"));
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
        cancelLocationAnswer.setSessionId(new diameter.base.SessionId("utf8string2103922471"));
        cancelLocationAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        cancelLocationAnswer.setOriginHost(new diameter.base.OriginHost("id1275397119.diameter.com"));
        cancelLocationAnswer.setOriginRealm(new diameter.base.OriginRealm("id-825453536.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(306847840)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-1462072531)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-611853506)));
            cancelLocationAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-156077821)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(-2117401964)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-1269187098)));
            // add more AVP as ANY values to supportedFeatures
            cancelLocationAnswer.addSupportedFeatures(supportedFeatures);
        }
        cancelLocationAnswer.setResultCode(new diameter.base.ResultCode(new Integer(-797508812)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(1103160863)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(1117981918)));
            cancelLocationAnswer.setExperimentalResult(experimentalResult);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-1707643677.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-1241295529"));
            // add more AVP as ANY values to proxyInfo
            cancelLocationAnswer.addProxyInfo(proxyInfo);
        }
        cancelLocationAnswer.addRouteRecord(new diameter.base.RouteRecord("id1912640082.diameter.com"));
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
