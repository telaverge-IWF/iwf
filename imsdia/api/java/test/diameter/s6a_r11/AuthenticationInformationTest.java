package diameter.s6a_r11;

import com.intellinet.diameter.*;
import diameter.*;

public class AuthenticationInformationTest {

    public static void testAuthenticationInformationRequest() throws Exception {
        AuthenticationInformationRequest authenticationInformationRequest = new AuthenticationInformationRequest(false, false);
        authenticationInformationRequest.setSessionId(new diameter.base.SessionId("utf8string1634839754"));
        authenticationInformationRequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        authenticationInformationRequest.setOriginHost(new diameter.base.OriginHost("id-1702029840.diameter.com"));
        authenticationInformationRequest.setOriginRealm(new diameter.base.OriginRealm("id-1111405759.diameter.com"));
        authenticationInformationRequest.setDestinationRealm(new diameter.base.DestinationRealm("id555422589.diameter.com"));
        authenticationInformationRequest.setUserName(new diameter.base.UserName("utf8string254913981"));
        authenticationInformationRequest.setVisitedPLMNId(new VisitedPLMNId("octetstring-1904033714"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(1220433136)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(1462403466)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-1178471928)));
            authenticationInformationRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        {
            RequestedEUTRANAuthenticationInfo requestedEUTRANAuthenticationInfo = new RequestedEUTRANAuthenticationInfo();
            requestedEUTRANAuthenticationInfo.setNumberOfRequestedVectors(new NumberOfRequestedVectors(new Integer(777284926)));
            requestedEUTRANAuthenticationInfo.setImmediateResponsePreferred(new ImmediateResponsePreferred(new Integer(1362261988)));
            requestedEUTRANAuthenticationInfo.setReSynchronizationInfo(new ReSynchronizationInfo("octetstring-464330292"));
            // add more AVP as ANY values to requestedEUTRANAuthenticationInfo
            authenticationInformationRequest.setRequestedEUTRANAuthenticationInfo(requestedEUTRANAuthenticationInfo);
        }
        {
            RequestedUTRANGERANAuthenticationInfo requestedUTRANGERANAuthenticationInfo = new RequestedUTRANGERANAuthenticationInfo();
            requestedUTRANGERANAuthenticationInfo.setNumberOfRequestedVectors(new NumberOfRequestedVectors(new Integer(-1624629499)));
            requestedUTRANGERANAuthenticationInfo.setImmediateResponsePreferred(new ImmediateResponsePreferred(new Integer(263224520)));
            requestedUTRANGERANAuthenticationInfo.setReSynchronizationInfo(new ReSynchronizationInfo("octetstring1283298085"));
            // add more AVP as ANY values to requestedUTRANGERANAuthenticationInfo
            authenticationInformationRequest.setRequestedUTRANGERANAuthenticationInfo(requestedUTRANGERANAuthenticationInfo);
        }
        authenticationInformationRequest.setDestinationHost(new diameter.base.DestinationHost("id-876252809.diameter.com"));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(1371045335)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(2143588881)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-434596907)));
            // add more AVP as ANY values to supportedFeatures
            authenticationInformationRequest.addSupportedFeatures(supportedFeatures);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-1615002515.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring1298605801"));
            // add more AVP as ANY values to proxyInfo
            authenticationInformationRequest.addProxyInfo(proxyInfo);
        }
        authenticationInformationRequest.addRouteRecord(new diameter.base.RouteRecord("id679993803.diameter.com"));
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
        authenticationInformationAnswer.setSessionId(new diameter.base.SessionId("utf8string228922517"));
        authenticationInformationAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        authenticationInformationAnswer.setOriginHost(new diameter.base.OriginHost("id1845381610.diameter.com"));
        authenticationInformationAnswer.setOriginRealm(new diameter.base.OriginRealm("id95908846.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-1823666393)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(286522327)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-1127976423)));
            authenticationInformationAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        authenticationInformationAnswer.setResultCode(new diameter.base.ResultCode(new Integer(1021856935)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(-784759724)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(-512570907)));
            authenticationInformationAnswer.setExperimentalResult(experimentalResult);
        }
        authenticationInformationAnswer.setErrorDiagnostic(new ErrorDiagnostic(ErrorDiagnostic.Value.NO_GPRS_DATA_SUBSCRIBED));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-1445023599)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(-873382384)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(1624687575)));
            // add more AVP as ANY values to supportedFeatures
            authenticationInformationAnswer.addSupportedFeatures(supportedFeatures);
        }
        {
            AuthenticationInfo authenticationInfo = new AuthenticationInfo();
            {
                EUTRANVector eUTRANVector = new EUTRANVector();
                eUTRANVector.setRAND(new RAND("octetstring369338375"));
                eUTRANVector.setXRES(new XRES("octetstring2006513698"));
                eUTRANVector.setAUTN(new AUTN("octetstring-1663103013"));
                eUTRANVector.setKASME(new KASME("octetstring2143446941"));
                eUTRANVector.setItemNumber(new ItemNumber(new Integer(-737159197)));
                // add more AVP as ANY values to eUTRANVector
                authenticationInfo.addEUTRANVector(eUTRANVector);
            }
            {
                UTRANVector uTRANVector = new UTRANVector();
                uTRANVector.setRAND(new RAND("octetstring-1838176665"));
                uTRANVector.setXRES(new XRES("octetstring-464438935"));
                uTRANVector.setAUTN(new AUTN("octetstring-2104137205"));
                uTRANVector.setCK(new CK("octetstring-1784709268"));
                uTRANVector.setIK(new IK("octetstring-1215056141"));
                uTRANVector.setItemNumber(new ItemNumber(new Integer(1362743172)));
                // add more AVP as ANY values to uTRANVector
                authenticationInfo.addUTRANVector(uTRANVector);
            }
            {
                GERANVector gERANVector = new GERANVector();
                gERANVector.setRAND(new RAND("octetstring384186353"));
                gERANVector.setSRES(new SRES("octetstring-791508905"));
                gERANVector.setKc(new Kc("octetstring760174356"));
                gERANVector.setItemNumber(new ItemNumber(new Integer(252858161)));
                // add more AVP as ANY values to gERANVector
                authenticationInfo.addGERANVector(gERANVector);
            }
            // add more AVP as ANY values to authenticationInfo
            authenticationInformationAnswer.setAuthenticationInfo(authenticationInfo);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id1892283496.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring1681711809"));
            // add more AVP as ANY values to proxyInfo
            authenticationInformationAnswer.addProxyInfo(proxyInfo);
        }
        authenticationInformationAnswer.addRouteRecord(new diameter.base.RouteRecord("id83656264.diameter.com"));
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
