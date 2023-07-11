package diameter.s6a_r10;

import com.intellinet.diameter.*;
import diameter.*;

public class DeleteSubscriberDataTest {

    public static void testDeleteSubscriberDataRequest() throws Exception {
        DeleteSubscriberDataRequest deleteSubscriberDataRequest = new DeleteSubscriberDataRequest(false, false);
        deleteSubscriberDataRequest.setSessionId(new diameter.base.SessionId("utf8string-303854308"));
        deleteSubscriberDataRequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        deleteSubscriberDataRequest.setOriginHost(new diameter.base.OriginHost("id-1819664011.diameter.com"));
        deleteSubscriberDataRequest.setOriginRealm(new diameter.base.OriginRealm("id1150505238.diameter.com"));
        deleteSubscriberDataRequest.setDestinationHost(new diameter.base.DestinationHost("id-1528200139.diameter.com"));
        deleteSubscriberDataRequest.setDestinationRealm(new diameter.base.DestinationRealm("id463727402.diameter.com"));
        deleteSubscriberDataRequest.setUserName(new diameter.base.UserName("utf8string-95373349"));
        deleteSubscriberDataRequest.setDSRFlags(new DSRFlags(new Integer(693448456)));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(720427402)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(1946298136)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(1463157306)));
            deleteSubscriberDataRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        deleteSubscriberDataRequest.setTraceReference(new TraceReference("octetstring-826530778"));
        deleteSubscriberDataRequest.addTSCode(new TSCode("octetstring-101499953"));
        deleteSubscriberDataRequest.addSSCode(new SSCode("octetstring515943411"));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-2067187783)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(-1207560190)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(370492369)));
            // add more AVP as ANY values to supportedFeatures
            deleteSubscriberDataRequest.addSupportedFeatures(supportedFeatures);
        }
        deleteSubscriberDataRequest.addContextIdentifier(new ContextIdentifier(new Integer(1046001097)));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-670008441.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring1126875553"));
            // add more AVP as ANY values to proxyInfo
            deleteSubscriberDataRequest.addProxyInfo(proxyInfo);
        }
        deleteSubscriberDataRequest.addRouteRecord(new diameter.base.RouteRecord("id1743959718.diameter.com"));
        // add more AVP as ANY values to deleteSubscriberDataRequest

        byte[] buffer = deleteSubscriberDataRequest.encode();
        DeleteSubscriberDataRequest deleteSubscriberDataRequest2 = new DeleteSubscriberDataRequest(buffer);
        String s1 = deleteSubscriberDataRequest.toString();
        String s2 = deleteSubscriberDataRequest2.toString();
        if (!s1.equals(s2)) {
            System.err.println("deleteSubscriberDataRequest1 = " + s1);
            System.err.println("deleteSubscriberDataRequest2 = " + s2);
            throw new VerificationException("DeleteSubscriberDataRequest encoding/decoding failure");
        }
    }

    public static void testDeleteSubscriberDataAnswer() throws Exception {
        DeleteSubscriberDataAnswer deleteSubscriberDataAnswer = new DeleteSubscriberDataAnswer(false, false);
        deleteSubscriberDataAnswer.setSessionId(new diameter.base.SessionId("utf8string-1532233677"));
        deleteSubscriberDataAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        deleteSubscriberDataAnswer.setOriginHost(new diameter.base.OriginHost("id-578927047.diameter.com"));
        deleteSubscriberDataAnswer.setOriginRealm(new diameter.base.OriginRealm("id-1792002267.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(493577402)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(1294505010)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(1092124730)));
            deleteSubscriberDataAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-554558824)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(398029686)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-1723371568)));
            // add more AVP as ANY values to supportedFeatures
            deleteSubscriberDataAnswer.addSupportedFeatures(supportedFeatures);
        }
        deleteSubscriberDataAnswer.setResultCode(new diameter.base.ResultCode(new Integer(-323276142)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(1000297648)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(-619326984)));
            deleteSubscriberDataAnswer.setExperimentalResult(experimentalResult);
        }
        deleteSubscriberDataAnswer.setDSAFlags(new DSAFlags(new Integer(-806552539)));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-221139923.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring1548922553"));
            // add more AVP as ANY values to proxyInfo
            deleteSubscriberDataAnswer.addProxyInfo(proxyInfo);
        }
        deleteSubscriberDataAnswer.addRouteRecord(new diameter.base.RouteRecord("id-1944413079.diameter.com"));
        // add more AVP as ANY values to deleteSubscriberDataAnswer

        byte[] buffer = deleteSubscriberDataAnswer.encode();
        DeleteSubscriberDataAnswer deleteSubscriberDataAnswer2 = new DeleteSubscriberDataAnswer(buffer);
        String s1 = deleteSubscriberDataAnswer.toString();
        String s2 = deleteSubscriberDataAnswer2.toString();
        if (!s1.equals(s2)) {
            System.err.println("deleteSubscriberDataAnswer1 = " + s1);
            System.err.println("deleteSubscriberDataAnswer2 = " + s2);
            throw new VerificationException("DeleteSubscriberDataAnswer encoding/decoding failure");
        }
    }

    public static void main(String[] args) throws Exception {
        testDeleteSubscriberDataRequest();
        testDeleteSubscriberDataAnswer();
    }
}
