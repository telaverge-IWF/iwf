package diameter.cxdx_v12;

import com.intellinet.diameter.*;
import diameter.*;

public class MultimediaAuthTest {

    public static void testMultimediaAuthRequest() throws Exception {
        MultimediaAuthRequest multimediaAuthRequest = new MultimediaAuthRequest(false, false);
        multimediaAuthRequest.setSessionId(new diameter.base.SessionId("utf8string1297805058"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-1232857044)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(1684826107)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(970034186)));
            multimediaAuthRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        multimediaAuthRequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        multimediaAuthRequest.setOriginHost(new diameter.base.OriginHost("id854678223.diameter.com"));
        multimediaAuthRequest.setOriginRealm(new diameter.base.OriginRealm("id1899728512.diameter.com"));
        multimediaAuthRequest.setDestinationRealm(new diameter.base.DestinationRealm("id1531274515.diameter.com"));
        multimediaAuthRequest.setUserName(new diameter.base.UserName("utf8string8541477"));
        multimediaAuthRequest.setPublicIdentity(new PublicIdentity("utf8string1431352824"));
        multimediaAuthRequest.setServerName(new ServerName("utf8string889512475"));
        {
            SIPAuthDataItem sIPAuthDataItem = new SIPAuthDataItem();
            sIPAuthDataItem.setSIPItemNumber(new SIPItemNumber(new Integer(1257480800)));
            sIPAuthDataItem.setSIPAuthenticationScheme(new SIPAuthenticationScheme("utf8string-299332540"));
            sIPAuthDataItem.setSIPAuthenticate(new SIPAuthenticate("octetstring-22494464"));
            sIPAuthDataItem.setSIPAuthorization(new SIPAuthorization("octetstring2014774299"));
            sIPAuthDataItem.setSIPAuthenticationContext(new SIPAuthenticationContext("octetstring-1240978579"));
            sIPAuthDataItem.setConfidentialityKey(new ConfidentialityKey("octetstring1981160433"));
            sIPAuthDataItem.setIntegrityKey(new IntegrityKey("octetstring-1797541733"));
            {
                SIPDigestAuthenticate sIPDigestAuthenticate = new SIPDigestAuthenticate();
                sIPDigestAuthenticate.setDigestRealm(new DigestRealm("utf8string1363637733"));
                sIPDigestAuthenticate.setDigestQoP(new DigestQoP("utf8string1772919653"));
                sIPDigestAuthenticate.setDigestHA1(new DigestHA1("utf8string1826519831"));
                sIPDigestAuthenticate.setDigestAlgorithm(new DigestAlgorithm("utf8string1035425814"));
                // add more AVP as ANY values to sIPDigestAuthenticate
                sIPAuthDataItem.setSIPDigestAuthenticate(sIPDigestAuthenticate);
            }
            sIPAuthDataItem.setFramedIPAddress(new FramedIPAddress("octetstring1368833763"));
            sIPAuthDataItem.setFramedIPv6Prefix(new FramedIPv6Prefix("octetstring-151674359"));
            sIPAuthDataItem.setFramedInterfaceId(new FramedInterfaceId(new Long(-3697769625436888353L)));
            sIPAuthDataItem.addLineIdentifier(new LineIdentifier("octetstring1176272315"));
            // add more AVP as ANY values to sIPAuthDataItem
            multimediaAuthRequest.setSIPAuthDataItem(sIPAuthDataItem);
        }
        multimediaAuthRequest.setSIPNumberAuthItems(new SIPNumberAuthItems(new Integer(1338707671)));
        multimediaAuthRequest.setDestinationHost(new diameter.base.DestinationHost("id2068668729.diameter.com"));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-846019510)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(-737748796)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-190649753)));
            // add more AVP as ANY values to supportedFeatures
            multimediaAuthRequest.addSupportedFeatures(supportedFeatures);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-71137284.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring664013713"));
            // add more AVP as ANY values to proxyInfo
            multimediaAuthRequest.addProxyInfo(proxyInfo);
        }
        multimediaAuthRequest.addRouteRecord(new diameter.base.RouteRecord("id-549715531.diameter.com"));
        // add more AVP as ANY values to multimediaAuthRequest

        byte[] buffer = multimediaAuthRequest.encode();
        MultimediaAuthRequest multimediaAuthRequest2 = new MultimediaAuthRequest(buffer);
        String s1 = multimediaAuthRequest.toString();
        String s2 = multimediaAuthRequest2.toString();
        if (!s1.equals(s2)) {
            System.err.println("multimediaAuthRequest1 = " + s1);
            System.err.println("multimediaAuthRequest2 = " + s2);
            throw new VerificationException("MultimediaAuthRequest encoding/decoding failure");
        }
    }

    public static void testMultimediaAuthAnswer() throws Exception {
        MultimediaAuthAnswer multimediaAuthAnswer = new MultimediaAuthAnswer(false, false);
        multimediaAuthAnswer.setSessionId(new diameter.base.SessionId("utf8string1166688791"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-918719952)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-1567862243)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-1713127265)));
            multimediaAuthAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        multimediaAuthAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        multimediaAuthAnswer.setOriginHost(new diameter.base.OriginHost("id-1049932310.diameter.com"));
        multimediaAuthAnswer.setOriginRealm(new diameter.base.OriginRealm("id-1584674301.diameter.com"));
        multimediaAuthAnswer.setResultCode(new diameter.base.ResultCode(new Integer(-452314596)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(1672788141)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(108572378)));
            multimediaAuthAnswer.setExperimentalResult(experimentalResult);
        }
        multimediaAuthAnswer.setUserName(new diameter.base.UserName("utf8string1906520272"));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(1609327816)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(1672577627)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-578534688)));
            // add more AVP as ANY values to supportedFeatures
            multimediaAuthAnswer.addSupportedFeatures(supportedFeatures);
        }
        multimediaAuthAnswer.setPublicIdentity(new PublicIdentity("utf8string-546854263"));
        multimediaAuthAnswer.setSIPNumberAuthItems(new SIPNumberAuthItems(new Integer(-409869840)));
        {
            SIPAuthDataItem sIPAuthDataItem = new SIPAuthDataItem();
            sIPAuthDataItem.setSIPItemNumber(new SIPItemNumber(new Integer(-195537726)));
            sIPAuthDataItem.setSIPAuthenticationScheme(new SIPAuthenticationScheme("utf8string-626017308"));
            sIPAuthDataItem.setSIPAuthenticate(new SIPAuthenticate("octetstring-1817523987"));
            sIPAuthDataItem.setSIPAuthorization(new SIPAuthorization("octetstring308227465"));
            sIPAuthDataItem.setSIPAuthenticationContext(new SIPAuthenticationContext("octetstring-617022875"));
            sIPAuthDataItem.setConfidentialityKey(new ConfidentialityKey("octetstring-780860698"));
            sIPAuthDataItem.setIntegrityKey(new IntegrityKey("octetstring1645560572"));
            {
                SIPDigestAuthenticate sIPDigestAuthenticate = new SIPDigestAuthenticate();
                sIPDigestAuthenticate.setDigestRealm(new DigestRealm("utf8string1317427555"));
                sIPDigestAuthenticate.setDigestQoP(new DigestQoP("utf8string-55703644"));
                sIPDigestAuthenticate.setDigestHA1(new DigestHA1("utf8string2075330643"));
                sIPDigestAuthenticate.setDigestAlgorithm(new DigestAlgorithm("utf8string-768139076"));
                // add more AVP as ANY values to sIPDigestAuthenticate
                sIPAuthDataItem.setSIPDigestAuthenticate(sIPDigestAuthenticate);
            }
            sIPAuthDataItem.setFramedIPAddress(new FramedIPAddress("octetstring367773598"));
            sIPAuthDataItem.setFramedIPv6Prefix(new FramedIPv6Prefix("octetstring1857320474"));
            sIPAuthDataItem.setFramedInterfaceId(new FramedInterfaceId(new Long(3262512248975286074L)));
            sIPAuthDataItem.addLineIdentifier(new LineIdentifier("octetstring964139100"));
            // add more AVP as ANY values to sIPAuthDataItem
            multimediaAuthAnswer.addSIPAuthDataItem(sIPAuthDataItem);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-317255098.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-1707457537"));
            // add more AVP as ANY values to proxyInfo
            multimediaAuthAnswer.addProxyInfo(proxyInfo);
        }
        multimediaAuthAnswer.addRouteRecord(new diameter.base.RouteRecord("id-1425977138.diameter.com"));
        // add more AVP as ANY values to multimediaAuthAnswer

        byte[] buffer = multimediaAuthAnswer.encode();
        MultimediaAuthAnswer multimediaAuthAnswer2 = new MultimediaAuthAnswer(buffer);
        String s1 = multimediaAuthAnswer.toString();
        String s2 = multimediaAuthAnswer2.toString();
        if (!s1.equals(s2)) {
            System.err.println("multimediaAuthAnswer1 = " + s1);
            System.err.println("multimediaAuthAnswer2 = " + s2);
            throw new VerificationException("MultimediaAuthAnswer encoding/decoding failure");
        }
    }

    public static void main(String[] args) throws Exception {
        testMultimediaAuthRequest();
        testMultimediaAuthAnswer();
    }
}
