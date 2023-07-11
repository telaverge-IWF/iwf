package diameter.cxdx_v12;

import com.intellinet.diameter.*;
import diameter.*;

public class PushProfileTest {

    public static void testPushProfileRequest() throws Exception {
        PushProfileRequest pushProfileRequest = new PushProfileRequest(false, false);
        pushProfileRequest.setSessionId(new diameter.base.SessionId("utf8string-1504537669"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(1291492778)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(1543582577)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-2030702187)));
            pushProfileRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        pushProfileRequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        pushProfileRequest.setOriginHost(new diameter.base.OriginHost("id-1605491577.diameter.com"));
        pushProfileRequest.setOriginRealm(new diameter.base.OriginRealm("id-254295039.diameter.com"));
        pushProfileRequest.setDestinationHost(new diameter.base.DestinationHost("id829264352.diameter.com"));
        pushProfileRequest.setDestinationRealm(new diameter.base.DestinationRealm("id-1923602252.diameter.com"));
        pushProfileRequest.setUserName(new diameter.base.UserName("utf8string1914698174"));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-1519213590)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(-298831363)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-1080660125)));
            // add more AVP as ANY values to supportedFeatures
            pushProfileRequest.addSupportedFeatures(supportedFeatures);
        }
        pushProfileRequest.setUserData(new UserData("octetstring-839121870"));
        {
            ChargingInformation chargingInformation = new ChargingInformation();
            chargingInformation.setPrimaryEventChargingFunctionName(new PrimaryEventChargingFunctionName(new URI("domain-1670355910.com", URI.Scheme.AAAS, (short)25725, URI.Transport.TCP, URI.Protocol.DIAMETER)));
            chargingInformation.setSecondaryEventChargingFunctionName(new SecondaryEventChargingFunctionName(new URI("domain976535926.com", URI.Scheme.AAAS, (short)4949, URI.Transport.TCP, URI.Protocol.DIAMETER)));
            chargingInformation.setPrimaryChargingCollectionFunctionName(new PrimaryChargingCollectionFunctionName(new URI("domain-1381013487.com", URI.Scheme.AAAS, (short)11466, URI.Transport.TCP, URI.Protocol.DIAMETER)));
            chargingInformation.setSecondaryChargingCollectionFunctionName(new SecondaryChargingCollectionFunctionName(new URI("domain389055144.com", URI.Scheme.AAAS, (short)12746, URI.Transport.TCP, URI.Protocol.DIAMETER)));
            // add more AVP as ANY values to chargingInformation
            pushProfileRequest.setChargingInformation(chargingInformation);
        }
        {
            SIPAuthDataItem sIPAuthDataItem = new SIPAuthDataItem();
            sIPAuthDataItem.setSIPItemNumber(new SIPItemNumber(new Integer(1224109172)));
            sIPAuthDataItem.setSIPAuthenticationScheme(new SIPAuthenticationScheme("utf8string1508363371"));
            sIPAuthDataItem.setSIPAuthenticate(new SIPAuthenticate("octetstring-1186010564"));
            sIPAuthDataItem.setSIPAuthorization(new SIPAuthorization("octetstring-99221940"));
            sIPAuthDataItem.setSIPAuthenticationContext(new SIPAuthenticationContext("octetstring-235062944"));
            sIPAuthDataItem.setConfidentialityKey(new ConfidentialityKey("octetstring804855942"));
            sIPAuthDataItem.setIntegrityKey(new IntegrityKey("octetstring2048420912"));
            {
                SIPDigestAuthenticate sIPDigestAuthenticate = new SIPDigestAuthenticate();
                sIPDigestAuthenticate.setDigestRealm(new DigestRealm("utf8string2023042765"));
                sIPDigestAuthenticate.setDigestQoP(new DigestQoP("utf8string1915146274"));
                sIPDigestAuthenticate.setDigestHA1(new DigestHA1("utf8string1396986790"));
                sIPDigestAuthenticate.setDigestAlgorithm(new DigestAlgorithm("utf8string-997916239"));
                // add more AVP as ANY values to sIPDigestAuthenticate
                sIPAuthDataItem.setSIPDigestAuthenticate(sIPDigestAuthenticate);
            }
            sIPAuthDataItem.setFramedIPAddress(new FramedIPAddress("octetstring1277141474"));
            sIPAuthDataItem.setFramedIPv6Prefix(new FramedIPv6Prefix("octetstring1065331429"));
            sIPAuthDataItem.setFramedInterfaceId(new FramedInterfaceId(new Long(7660033345148945617L)));
            sIPAuthDataItem.addLineIdentifier(new LineIdentifier("octetstring135504477"));
            // add more AVP as ANY values to sIPAuthDataItem
            pushProfileRequest.setSIPAuthDataItem(sIPAuthDataItem);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id1722278284.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-1464050578"));
            // add more AVP as ANY values to proxyInfo
            pushProfileRequest.addProxyInfo(proxyInfo);
        }
        pushProfileRequest.addRouteRecord(new diameter.base.RouteRecord("id1419875191.diameter.com"));
        // add more AVP as ANY values to pushProfileRequest

        byte[] buffer = pushProfileRequest.encode();
        PushProfileRequest pushProfileRequest2 = new PushProfileRequest(buffer);
        String s1 = pushProfileRequest.toString();
        String s2 = pushProfileRequest2.toString();
        if (!s1.equals(s2)) {
            System.err.println("pushProfileRequest1 = " + s1);
            System.err.println("pushProfileRequest2 = " + s2);
            throw new VerificationException("PushProfileRequest encoding/decoding failure");
        }
    }

    public static void testPushProfileAnswer() throws Exception {
        PushProfileAnswer pushProfileAnswer = new PushProfileAnswer(false, false);
        pushProfileAnswer.setSessionId(new diameter.base.SessionId("utf8string-1270791877"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-679852094)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-1443498620)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(1575398806)));
            pushProfileAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        pushProfileAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        pushProfileAnswer.setOriginHost(new diameter.base.OriginHost("id-138487730.diameter.com"));
        pushProfileAnswer.setOriginRealm(new diameter.base.OriginRealm("id-50993724.diameter.com"));
        pushProfileAnswer.setResultCode(new diameter.base.ResultCode(new Integer(974160544)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(942838752)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(357040555)));
            pushProfileAnswer.setExperimentalResult(experimentalResult);
        }
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-33365524)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(1986437693)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-913032991)));
            // add more AVP as ANY values to supportedFeatures
            pushProfileAnswer.addSupportedFeatures(supportedFeatures);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-826300457.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring755851250"));
            // add more AVP as ANY values to proxyInfo
            pushProfileAnswer.addProxyInfo(proxyInfo);
        }
        pushProfileAnswer.addRouteRecord(new diameter.base.RouteRecord("id-165739464.diameter.com"));
        // add more AVP as ANY values to pushProfileAnswer

        byte[] buffer = pushProfileAnswer.encode();
        PushProfileAnswer pushProfileAnswer2 = new PushProfileAnswer(buffer);
        String s1 = pushProfileAnswer.toString();
        String s2 = pushProfileAnswer2.toString();
        if (!s1.equals(s2)) {
            System.err.println("pushProfileAnswer1 = " + s1);
            System.err.println("pushProfileAnswer2 = " + s2);
            throw new VerificationException("PushProfileAnswer encoding/decoding failure");
        }
    }

    public static void main(String[] args) throws Exception {
        testPushProfileRequest();
        testPushProfileAnswer();
    }
}
