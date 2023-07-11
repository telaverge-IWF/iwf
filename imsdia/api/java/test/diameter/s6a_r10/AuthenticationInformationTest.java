package diameter.s6a_r10;

import com.intellinet.diameter.*;
import diameter.*;

public class AuthenticationInformationTest {

    public static void testAuthenticationInformationRequest() throws Exception {
        AuthenticationInformationRequest authenticationInformationRequest = new AuthenticationInformationRequest(false, false);
        authenticationInformationRequest.setSessionId(new diameter.base.SessionId("utf8string-767710859"));
        authenticationInformationRequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        authenticationInformationRequest.setOriginHost(new diameter.base.OriginHost("id-1984146164.diameter.com"));
        authenticationInformationRequest.setOriginRealm(new diameter.base.OriginRealm("id-367292520.diameter.com"));
        authenticationInformationRequest.setDestinationRealm(new diameter.base.DestinationRealm("id-1103569793.diameter.com"));
        authenticationInformationRequest.setUserName(new diameter.base.UserName("utf8string199424389"));
        authenticationInformationRequest.setVisitedPLMNId(new VisitedPLMNId("octetstring976026044"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-1510639006)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-1416566871)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(1954047527)));
            authenticationInformationRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        {
            RequestedEUTRANAuthenticationInfo requestedEUTRANAuthenticationInfo = new RequestedEUTRANAuthenticationInfo();
            requestedEUTRANAuthenticationInfo.setNumberOfRequestedVectors(new NumberOfRequestedVectors(new Integer(508097816)));
            requestedEUTRANAuthenticationInfo.setImmediateResponsePreferred(new ImmediateResponsePreferred(new Integer(-940423598)));
            requestedEUTRANAuthenticationInfo.setReSynchronizationInfo(new ReSynchronizationInfo("octetstring-1516214017"));
            // add more AVP as ANY values to requestedEUTRANAuthenticationInfo
            authenticationInformationRequest.setRequestedEUTRANAuthenticationInfo(requestedEUTRANAuthenticationInfo);
        }
        {
            RequestedUTRANGERANAuthenticationInfo requestedUTRANGERANAuthenticationInfo = new RequestedUTRANGERANAuthenticationInfo();
            requestedUTRANGERANAuthenticationInfo.setNumberOfRequestedVectors(new NumberOfRequestedVectors(new Integer(1820684914)));
            requestedUTRANGERANAuthenticationInfo.setImmediateResponsePreferred(new ImmediateResponsePreferred(new Integer(843520682)));
            requestedUTRANGERANAuthenticationInfo.setReSynchronizationInfo(new ReSynchronizationInfo("octetstring1026149576"));
            // add more AVP as ANY values to requestedUTRANGERANAuthenticationInfo
            authenticationInformationRequest.setRequestedUTRANGERANAuthenticationInfo(requestedUTRANGERANAuthenticationInfo);
        }
        authenticationInformationRequest.setDestinationHost(new diameter.base.DestinationHost("id-892136953.diameter.com"));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-95053194)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(2107242297)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-945028895)));
            // add more AVP as ANY values to supportedFeatures
            authenticationInformationRequest.addSupportedFeatures(supportedFeatures);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id1233640980.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-909103578"));
            // add more AVP as ANY values to proxyInfo
            authenticationInformationRequest.addProxyInfo(proxyInfo);
        }
        authenticationInformationRequest.addRouteRecord(new diameter.base.RouteRecord("id290939193.diameter.com"));
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
        authenticationInformationAnswer.setSessionId(new diameter.base.SessionId("utf8string525445335"));
        authenticationInformationAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        authenticationInformationAnswer.setOriginHost(new diameter.base.OriginHost("id-1630387364.diameter.com"));
        authenticationInformationAnswer.setOriginRealm(new diameter.base.OriginRealm("id463740037.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-309016154)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(433672264)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-1029225441)));
            authenticationInformationAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        authenticationInformationAnswer.setResultCode(new diameter.base.ResultCode(new Integer(-225868469)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(-1827559181)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(-1996459893)));
            authenticationInformationAnswer.setExperimentalResult(experimentalResult);
        }
        authenticationInformationAnswer.setErrorDiagnostic(new ErrorDiagnostic(ErrorDiagnostic.Value.ODB_HPLMN_APN));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-460949946)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(1945864489)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(444318070)));
            // add more AVP as ANY values to supportedFeatures
            authenticationInformationAnswer.addSupportedFeatures(supportedFeatures);
        }
        {
            AuthenticationInfo authenticationInfo = new AuthenticationInfo();
            {
                EUTRANVector eUTRANVector = new EUTRANVector();
                eUTRANVector.setRAND(new RAND("octetstring-683061086"));
                eUTRANVector.setXRES(new XRES("octetstring-1802772941"));
                eUTRANVector.setAUTN(new AUTN("octetstring1876853733"));
                eUTRANVector.setKASME(new KASME("octetstring736884233"));
                eUTRANVector.setItemNumber(new ItemNumber(new Integer(-1912704719)));
                // add more AVP as ANY values to eUTRANVector
                authenticationInfo.addEUTRANVector(eUTRANVector);
            }
            {
                UTRANVector uTRANVector = new UTRANVector();
                uTRANVector.setRAND(new RAND("octetstring1831385213"));
                uTRANVector.setXRES(new XRES("octetstring-893770093"));
                uTRANVector.setAUTN(new AUTN("octetstring-209979572"));
                uTRANVector.setCK(new CK("octetstring-1184249546"));
                uTRANVector.setIK(new IK("octetstring45112634"));
                uTRANVector.setItemNumber(new ItemNumber(new Integer(-1340689063)));
                // add more AVP as ANY values to uTRANVector
                authenticationInfo.addUTRANVector(uTRANVector);
            }
            {
                GERANVector gERANVector = new GERANVector();
                gERANVector.setRAND(new RAND("octetstring-868796577"));
                gERANVector.setSRES(new SRES("octetstring-790744496"));
                gERANVector.setKc(new Kc("octetstring-111059878"));
                gERANVector.setItemNumber(new ItemNumber(new Integer(1181825075)));
                // add more AVP as ANY values to gERANVector
                authenticationInfo.addGERANVector(gERANVector);
            }
            // add more AVP as ANY values to authenticationInfo
            authenticationInformationAnswer.setAuthenticationInfo(authenticationInfo);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-469130800.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-1332649691"));
            // add more AVP as ANY values to proxyInfo
            authenticationInformationAnswer.addProxyInfo(proxyInfo);
        }
        authenticationInformationAnswer.addRouteRecord(new diameter.base.RouteRecord("id-1841145827.diameter.com"));
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
