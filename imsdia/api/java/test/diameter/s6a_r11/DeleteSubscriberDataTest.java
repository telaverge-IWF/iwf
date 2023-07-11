package diameter.s6a_r11;

import com.intellinet.diameter.*;
import diameter.*;

public class DeleteSubscriberDataTest {

    public static void testDeleteSubscriberDataRequest() throws Exception {
        DeleteSubscriberDataRequest deleteSubscriberDataRequest = new DeleteSubscriberDataRequest(false, false);
        deleteSubscriberDataRequest.setSessionId(new diameter.base.SessionId("utf8string-1510995876"));
        deleteSubscriberDataRequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        deleteSubscriberDataRequest.setOriginHost(new diameter.base.OriginHost("id-1495269925.diameter.com"));
        deleteSubscriberDataRequest.setOriginRealm(new diameter.base.OriginRealm("id1123926498.diameter.com"));
        deleteSubscriberDataRequest.setDestinationHost(new diameter.base.DestinationHost("id-1321536026.diameter.com"));
        deleteSubscriberDataRequest.setDestinationRealm(new diameter.base.DestinationRealm("id-14405009.diameter.com"));
        deleteSubscriberDataRequest.setUserName(new diameter.base.UserName("utf8string-981696631"));
        deleteSubscriberDataRequest.setDSRFlags(new DSRFlags(new Integer(918804411)));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-747258430)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(1523456752)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-1350935565)));
            deleteSubscriberDataRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        deleteSubscriberDataRequest.setTraceReference(new TraceReference("octetstring-1798797660"));
        deleteSubscriberDataRequest.addTSCode(new TSCode("octetstring-1007064479"));
        deleteSubscriberDataRequest.addSSCode(new SSCode("octetstring-294130563"));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-1714896794)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(81231163)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-12444105)));
            // add more AVP as ANY values to supportedFeatures
            deleteSubscriberDataRequest.addSupportedFeatures(supportedFeatures);
        }
        deleteSubscriberDataRequest.addContextIdentifier(new ContextIdentifier(new Integer(462285541)));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-230433168.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-2108021216"));
            // add more AVP as ANY values to proxyInfo
            deleteSubscriberDataRequest.addProxyInfo(proxyInfo);
        }
        deleteSubscriberDataRequest.addRouteRecord(new diameter.base.RouteRecord("id-108714045.diameter.com"));
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
        deleteSubscriberDataAnswer.setSessionId(new diameter.base.SessionId("utf8string436110076"));
        deleteSubscriberDataAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        deleteSubscriberDataAnswer.setOriginHost(new diameter.base.OriginHost("id-1007755579.diameter.com"));
        deleteSubscriberDataAnswer.setOriginRealm(new diameter.base.OriginRealm("id2026230220.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-52162677)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(321784519)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(842811271)));
            deleteSubscriberDataAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-1322224660)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(1204910472)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-1356230807)));
            // add more AVP as ANY values to supportedFeatures
            deleteSubscriberDataAnswer.addSupportedFeatures(supportedFeatures);
        }
        deleteSubscriberDataAnswer.setResultCode(new diameter.base.ResultCode(new Integer(-970915582)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(620201810)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(-45340794)));
            deleteSubscriberDataAnswer.setExperimentalResult(experimentalResult);
        }
        deleteSubscriberDataAnswer.setDSAFlags(new DSAFlags(new Integer(-1612262191)));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id395405984.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring979813314"));
            // add more AVP as ANY values to proxyInfo
            deleteSubscriberDataAnswer.addProxyInfo(proxyInfo);
        }
        deleteSubscriberDataAnswer.addRouteRecord(new diameter.base.RouteRecord("id-391057298.diameter.com"));
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
