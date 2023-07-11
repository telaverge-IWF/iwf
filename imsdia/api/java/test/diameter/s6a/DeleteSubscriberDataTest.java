package diameter.s6a;

import com.intellinet.diameter.*;
import diameter.*;

public class DeleteSubscriberDataTest {

    public static void testDeleteSubscriberDataRequest() throws Exception {
        DeleteSubscriberDataRequest deleteSubscriberDataRequest = new DeleteSubscriberDataRequest(false, false);
        deleteSubscriberDataRequest.setSessionId(new diameter.base.SessionId("utf8string918496467"));
        deleteSubscriberDataRequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        deleteSubscriberDataRequest.setOriginHost(new diameter.base.OriginHost("id-1059695352.diameter.com"));
        deleteSubscriberDataRequest.setOriginRealm(new diameter.base.OriginRealm("id-366075483.diameter.com"));
        deleteSubscriberDataRequest.setDestinationHost(new diameter.base.DestinationHost("id-391687390.diameter.com"));
        deleteSubscriberDataRequest.setDestinationRealm(new diameter.base.DestinationRealm("id-201907864.diameter.com"));
        deleteSubscriberDataRequest.setUserName(new diameter.base.UserName("utf8string822918207"));
        deleteSubscriberDataRequest.setDSRFlags(new DSRFlags(new Integer(1522134602)));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-1036871659)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(1123372505)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-409918830)));
            deleteSubscriberDataRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        deleteSubscriberDataRequest.setTraceReference(new TraceReference("octetstring-1562047621"));
        deleteSubscriberDataRequest.addTSCode(new TSCode("octetstring-1415204820"));
        deleteSubscriberDataRequest.addSSCode(new SSCode("octetstring1401042963"));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-1978700086)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(1833290956)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-2069914774)));
            // add more AVP as ANY values to supportedFeatures
            deleteSubscriberDataRequest.addSupportedFeatures(supportedFeatures);
        }
        deleteSubscriberDataRequest.addContextIdentifier(new ContextIdentifier(new Integer(-2124060137)));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-852220680.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring991913748"));
            // add more AVP as ANY values to proxyInfo
            deleteSubscriberDataRequest.addProxyInfo(proxyInfo);
        }
        deleteSubscriberDataRequest.addRouteRecord(new diameter.base.RouteRecord("id574402287.diameter.com"));
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
        deleteSubscriberDataAnswer.setSessionId(new diameter.base.SessionId("utf8string-1202490625"));
        deleteSubscriberDataAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        deleteSubscriberDataAnswer.setOriginHost(new diameter.base.OriginHost("id-1323894432.diameter.com"));
        deleteSubscriberDataAnswer.setOriginRealm(new diameter.base.OriginRealm("id1999019238.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-402121974)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(1382370234)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-746868438)));
            deleteSubscriberDataAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-2034067807)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(-1295563528)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-1718427010)));
            // add more AVP as ANY values to supportedFeatures
            deleteSubscriberDataAnswer.addSupportedFeatures(supportedFeatures);
        }
        deleteSubscriberDataAnswer.setResultCode(new diameter.base.ResultCode(new Integer(829455819)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(1142746369)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(-1644556136)));
            deleteSubscriberDataAnswer.setExperimentalResult(experimentalResult);
        }
        deleteSubscriberDataAnswer.setDSAFlags(new DSAFlags(new Integer(1288915294)));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id3737389.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-582757605"));
            // add more AVP as ANY values to proxyInfo
            deleteSubscriberDataAnswer.addProxyInfo(proxyInfo);
        }
        deleteSubscriberDataAnswer.addRouteRecord(new diameter.base.RouteRecord("id1508053662.diameter.com"));
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
