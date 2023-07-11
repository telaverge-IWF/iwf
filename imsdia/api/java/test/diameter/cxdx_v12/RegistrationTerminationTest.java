package diameter.cxdx_v12;

import com.intellinet.diameter.*;
import diameter.*;

public class RegistrationTerminationTest {

    public static void testRegistrationTerminationRequest() throws Exception {
        RegistrationTerminationRequest registrationTerminationRequest = new RegistrationTerminationRequest(false, false);
        registrationTerminationRequest.setSessionId(new diameter.base.SessionId("utf8string-1608270152"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-1037000852)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(735886511)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(1973566883)));
            registrationTerminationRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        registrationTerminationRequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        registrationTerminationRequest.setOriginHost(new diameter.base.OriginHost("id1850856893.diameter.com"));
        registrationTerminationRequest.setOriginRealm(new diameter.base.OriginRealm("id1790191123.diameter.com"));
        registrationTerminationRequest.setDestinationHost(new diameter.base.DestinationHost("id-1162475402.diameter.com"));
        registrationTerminationRequest.setDestinationRealm(new diameter.base.DestinationRealm("id-495720454.diameter.com"));
        registrationTerminationRequest.setUserName(new diameter.base.UserName("utf8string151428789"));
        {
            DeregistrationReason deregistrationReason = new DeregistrationReason();
            deregistrationReason.setReasonCode(new ReasonCode(ReasonCode.Value.PERMANENT_TERMINATION));
            deregistrationReason.setReasonInfo(new ReasonInfo("utf8string-753673314"));
            // add more AVP as ANY values to deregistrationReason
            registrationTerminationRequest.setDeregistrationReason(deregistrationReason);
        }
        {
            AssociatedIdentities associatedIdentities = new AssociatedIdentities();
            associatedIdentities.addUserName(new diameter.base.UserName("utf8string2047058430"));
            // add more AVP as ANY values to associatedIdentities
            registrationTerminationRequest.setAssociatedIdentities(associatedIdentities);
        }
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(1162359748)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(81298319)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(1818239563)));
            // add more AVP as ANY values to supportedFeatures
            registrationTerminationRequest.addSupportedFeatures(supportedFeatures);
        }
        registrationTerminationRequest.addPublicIdentity(new PublicIdentity("utf8string1643158655"));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-765459664.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-931309535"));
            // add more AVP as ANY values to proxyInfo
            registrationTerminationRequest.addProxyInfo(proxyInfo);
        }
        registrationTerminationRequest.addRouteRecord(new diameter.base.RouteRecord("id1217221138.diameter.com"));
        // add more AVP as ANY values to registrationTerminationRequest

        byte[] buffer = registrationTerminationRequest.encode();
        RegistrationTerminationRequest registrationTerminationRequest2 = new RegistrationTerminationRequest(buffer);
        String s1 = registrationTerminationRequest.toString();
        String s2 = registrationTerminationRequest2.toString();
        if (!s1.equals(s2)) {
            System.err.println("registrationTerminationRequest1 = " + s1);
            System.err.println("registrationTerminationRequest2 = " + s2);
            throw new VerificationException("RegistrationTerminationRequest encoding/decoding failure");
        }
    }

    public static void testRegistrationTerminationAnswer() throws Exception {
        RegistrationTerminationAnswer registrationTerminationAnswer = new RegistrationTerminationAnswer(false, false);
        registrationTerminationAnswer.setSessionId(new diameter.base.SessionId("utf8string161626488"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(1360625465)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(838251974)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-1092532056)));
            registrationTerminationAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        registrationTerminationAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        registrationTerminationAnswer.setOriginHost(new diameter.base.OriginHost("id1847540605.diameter.com"));
        registrationTerminationAnswer.setOriginRealm(new diameter.base.OriginRealm("id1799484615.diameter.com"));
        registrationTerminationAnswer.setResultCode(new diameter.base.ResultCode(new Integer(-2066988563)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(1193920282)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(-1186857827)));
            registrationTerminationAnswer.setExperimentalResult(experimentalResult);
        }
        {
            AssociatedIdentities associatedIdentities = new AssociatedIdentities();
            associatedIdentities.addUserName(new diameter.base.UserName("utf8string121262304"));
            // add more AVP as ANY values to associatedIdentities
            registrationTerminationAnswer.setAssociatedIdentities(associatedIdentities);
        }
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-299193812)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(-886854028)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(1009688097)));
            // add more AVP as ANY values to supportedFeatures
            registrationTerminationAnswer.addSupportedFeatures(supportedFeatures);
        }
        {
            IdentitywithEmergencyRegistration identitywithEmergencyRegistration = new IdentitywithEmergencyRegistration();
            identitywithEmergencyRegistration.setUserName(new diameter.base.UserName("utf8string1069982555"));
            identitywithEmergencyRegistration.setPublicIdentity(new PublicIdentity("utf8string1583042721"));
            // add more AVP as ANY values to identitywithEmergencyRegistration
            registrationTerminationAnswer.addIdentitywithEmergencyRegistration(identitywithEmergencyRegistration);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id1515183823.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring2080502424"));
            // add more AVP as ANY values to proxyInfo
            registrationTerminationAnswer.addProxyInfo(proxyInfo);
        }
        registrationTerminationAnswer.addRouteRecord(new diameter.base.RouteRecord("id1449142873.diameter.com"));
        // add more AVP as ANY values to registrationTerminationAnswer

        byte[] buffer = registrationTerminationAnswer.encode();
        RegistrationTerminationAnswer registrationTerminationAnswer2 = new RegistrationTerminationAnswer(buffer);
        String s1 = registrationTerminationAnswer.toString();
        String s2 = registrationTerminationAnswer2.toString();
        if (!s1.equals(s2)) {
            System.err.println("registrationTerminationAnswer1 = " + s1);
            System.err.println("registrationTerminationAnswer2 = " + s2);
            throw new VerificationException("RegistrationTerminationAnswer encoding/decoding failure");
        }
    }

    public static void main(String[] args) throws Exception {
        testRegistrationTerminationRequest();
        testRegistrationTerminationAnswer();
    }
}
