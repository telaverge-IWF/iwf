package diameter.s6a;

import com.intellinet.diameter.*;
import diameter.*;

public class AuthenticationInformationTest {

    public static void testAuthenticationInformationRequest() throws Exception {
        AuthenticationInformationRequest authenticationInformationRequest = new AuthenticationInformationRequest(false, false);
        authenticationInformationRequest.setSessionId(new diameter.base.SessionId("utf8string305238104"));
        authenticationInformationRequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        authenticationInformationRequest.setOriginHost(new diameter.base.OriginHost("id242807426.diameter.com"));
        authenticationInformationRequest.setOriginRealm(new diameter.base.OriginRealm("id1659084513.diameter.com"));
        authenticationInformationRequest.setDestinationRealm(new diameter.base.DestinationRealm("id261297685.diameter.com"));
        authenticationInformationRequest.setUserName(new diameter.base.UserName("utf8string-524365785"));
        authenticationInformationRequest.setVisitedPLMNId(new VisitedPLMNId("octetstring30251021"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(1163106086)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(1746906615)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-1299846268)));
            authenticationInformationRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        {
            RequestedEUTRANAuthenticationInfo requestedEUTRANAuthenticationInfo = new RequestedEUTRANAuthenticationInfo();
            requestedEUTRANAuthenticationInfo.setNumberOfRequestedVectors(new NumberOfRequestedVectors(new Integer(1214198675)));
            requestedEUTRANAuthenticationInfo.setImmediateResponsePreferred(new ImmediateResponsePreferred(new Integer(1698142186)));
            requestedEUTRANAuthenticationInfo.setReSynchronizationInfo(new ReSynchronizationInfo("octetstring451399900"));
            // add more AVP as ANY values to requestedEUTRANAuthenticationInfo
            authenticationInformationRequest.setRequestedEUTRANAuthenticationInfo(requestedEUTRANAuthenticationInfo);
        }
        {
            RequestedUTRANGERANAuthenticationInfo requestedUTRANGERANAuthenticationInfo = new RequestedUTRANGERANAuthenticationInfo();
            requestedUTRANGERANAuthenticationInfo.setNumberOfRequestedVectors(new NumberOfRequestedVectors(new Integer(-1628735484)));
            requestedUTRANGERANAuthenticationInfo.setImmediateResponsePreferred(new ImmediateResponsePreferred(new Integer(1315018372)));
            requestedUTRANGERANAuthenticationInfo.setReSynchronizationInfo(new ReSynchronizationInfo("octetstring36835700"));
            // add more AVP as ANY values to requestedUTRANGERANAuthenticationInfo
            authenticationInformationRequest.setRequestedUTRANGERANAuthenticationInfo(requestedUTRANGERANAuthenticationInfo);
        }
        authenticationInformationRequest.setDestinationHost(new diameter.base.DestinationHost("id-344965282.diameter.com"));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-1642481160)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(278867808)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(494385742)));
            // add more AVP as ANY values to supportedFeatures
            authenticationInformationRequest.addSupportedFeatures(supportedFeatures);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-1996563183.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-823100263"));
            // add more AVP as ANY values to proxyInfo
            authenticationInformationRequest.addProxyInfo(proxyInfo);
        }
        authenticationInformationRequest.addRouteRecord(new diameter.base.RouteRecord("id1158652065.diameter.com"));
        // add more AVP as ANY values to authenticationInformationRequest

        byte[] buffer = authenticationInformationRequest.encode();
        AuthenticationInformationRequest authenticationInformationRequest2 = new AuthenticationInformationRequest(buffer);
        String s1 = authenticationInformationRequest.toString();
        String s2 = authenticationInformationRequest2.toString();
        if (!s1.equals(s2)) {
            System.err.println("authenticationInformationRequest1 = " + s1);
            System.err.println("authenticationInformationRequest2 = " + s2);
            throw new VerificationException("AuthenticationInformationRequest encoding/decoding failure");
        }
    }

    public static void testAuthenticationInformationAnswer() throws Exception {
        AuthenticationInformationAnswer authenticationInformationAnswer = new AuthenticationInformationAnswer(false, false);
        authenticationInformationAnswer.setSessionId(new diameter.base.SessionId("utf8string-542202277"));
        authenticationInformationAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        authenticationInformationAnswer.setOriginHost(new diameter.base.OriginHost("id-1377021636.diameter.com"));
        authenticationInformationAnswer.setOriginRealm(new diameter.base.OriginRealm("id-637115944.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(1774140207)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(1589861534)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-1813639741)));
            authenticationInformationAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        authenticationInformationAnswer.setResultCode(new diameter.base.ResultCode(new Integer(608685845)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(1204786586)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(-1365875342)));
            authenticationInformationAnswer.setExperimentalResult(experimentalResult);
        }
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-660128170)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(-531281269)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-1609091962)));
            // add more AVP as ANY values to supportedFeatures
            authenticationInformationAnswer.addSupportedFeatures(supportedFeatures);
        }
        {
            AuthenticationInfo authenticationInfo = new AuthenticationInfo();
            {
                EUTRANVector eUTRANVector = new EUTRANVector();
                eUTRANVector.setRAND(new RAND("octetstring946952115"));
                eUTRANVector.setXRES(new XRES("octetstring1810333267"));
                eUTRANVector.setAUTN(new AUTN("octetstring-1926802316"));
                eUTRANVector.setKASME(new KASME("octetstring-1010696958"));
                eUTRANVector.setItemNumber(new ItemNumber(new Integer(1525187485)));
                // add more AVP as ANY values to eUTRANVector
                authenticationInfo.addEUTRANVector(eUTRANVector);
            }
            {
                UTRANVector uTRANVector = new UTRANVector();
                uTRANVector.setRAND(new RAND("octetstring-1206784894"));
                uTRANVector.setXRES(new XRES("octetstring-1734951630"));
                uTRANVector.setAUTN(new AUTN("octetstring200731550"));
                uTRANVector.setCK(new CK("octetstring-158678718"));
                uTRANVector.setIK(new IK("octetstring477179533"));
                uTRANVector.setItemNumber(new ItemNumber(new Integer(-1239132746)));
                // add more AVP as ANY values to uTRANVector
                authenticationInfo.addUTRANVector(uTRANVector);
            }
            {
                GERANVector gERANVector = new GERANVector();
                gERANVector.setRAND(new RAND("octetstring-1987574024"));
                gERANVector.setSRES(new SRES("octetstring1210888589"));
                gERANVector.setKc(new Kc("octetstring-481052754"));
                gERANVector.setItemNumber(new ItemNumber(new Integer(-1981758939)));
                // add more AVP as ANY values to gERANVector
                authenticationInfo.addGERANVector(gERANVector);
            }
            // add more AVP as ANY values to authenticationInfo
            authenticationInformationAnswer.setAuthenticationInfo(authenticationInfo);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id2014734231.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring1572375427"));
            // add more AVP as ANY values to proxyInfo
            authenticationInformationAnswer.addProxyInfo(proxyInfo);
        }
        authenticationInformationAnswer.addRouteRecord(new diameter.base.RouteRecord("id-475969878.diameter.com"));
        // add more AVP as ANY values to authenticationInformationAnswer

        byte[] buffer = authenticationInformationAnswer.encode();
        AuthenticationInformationAnswer authenticationInformationAnswer2 = new AuthenticationInformationAnswer(buffer);
        String s1 = authenticationInformationAnswer.toString();
        String s2 = authenticationInformationAnswer2.toString();
        if (!s1.equals(s2)) {
            System.err.println("authenticationInformationAnswer1 = " + s1);
            System.err.println("authenticationInformationAnswer2 = " + s2);
            throw new VerificationException("AuthenticationInformationAnswer encoding/decoding failure");
        }
    }

    public static void main(String[] args) throws Exception {
        testAuthenticationInformationRequest();
        testAuthenticationInformationAnswer();
    }
}
