package diameter.cxdx_v12;

import com.intellinet.diameter.*;
import diameter.*;

public class ServerAssignmentTest {

    public static void testServerAssignmentRequest() throws Exception {
        ServerAssignmentRequest serverAssignmentRequest = new ServerAssignmentRequest(false, false);
        serverAssignmentRequest.setSessionId(new diameter.base.SessionId("utf8string-1037275587"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-111022229)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(1595672207)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-1352000583)));
            serverAssignmentRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        serverAssignmentRequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        serverAssignmentRequest.setOriginHost(new diameter.base.OriginHost("id1731274219.diameter.com"));
        serverAssignmentRequest.setOriginRealm(new diameter.base.OriginRealm("id-896462592.diameter.com"));
        serverAssignmentRequest.setServerName(new ServerName("utf8string760244665"));
        serverAssignmentRequest.setServerAssignmentType(new ServerAssignmentType(ServerAssignmentType.Value.AUTHENTICATION_TIMEOUT));
        serverAssignmentRequest.setUserDataAlreadyAvailable(new UserDataAlreadyAvailable(UserDataAlreadyAvailable.Value.USER_DATA_NOT_AVAILABLE));
        serverAssignmentRequest.setDestinationRealm(new diameter.base.DestinationRealm("id-646206709.diameter.com"));
        serverAssignmentRequest.setDestinationHost(new diameter.base.DestinationHost("id-2135801167.diameter.com"));
        serverAssignmentRequest.setUserName(new diameter.base.UserName("utf8string-1191992779"));
        serverAssignmentRequest.setWildcardedPublicIdentity(new WildcardedPublicIdentity("utf8string-773881566"));
        {
            SCSCFRestorationInfo sCSCFRestorationInfo = new SCSCFRestorationInfo();
            sCSCFRestorationInfo.setUserName(new diameter.base.UserName("utf8string-19625665"));
            {
                RestorationInfo restorationInfo = new RestorationInfo();
                restorationInfo.setPath(new Path("octetstring-762201196"));
                restorationInfo.setContact(new Contact("octetstring-375881917"));
                {
                    SubscriptionInfo subscriptionInfo = new SubscriptionInfo();
                    subscriptionInfo.setCallIDSIPHeader(new CallIDSIPHeader("octetstring1402544633"));
                    subscriptionInfo.setFromSIPHeader(new FromSIPHeader("octetstring599081344"));
                    subscriptionInfo.setToSIPHeader(new ToSIPHeader("octetstring-1344671232"));
                    subscriptionInfo.setRecordRoute(new RecordRoute("octetstring496720370"));
                    subscriptionInfo.setContact(new Contact("octetstring-229177497"));
                    // add more AVP as ANY values to subscriptionInfo
                    restorationInfo.setSubscriptionInfo(subscriptionInfo);
                }
                // add more AVP as ANY values to restorationInfo
                sCSCFRestorationInfo.addRestorationInfo(restorationInfo);
            }
            sCSCFRestorationInfo.setSIPAuthenticationScheme(new SIPAuthenticationScheme("utf8string76425154"));
            // add more AVP as ANY values to sCSCFRestorationInfo
            serverAssignmentRequest.setSCSCFRestorationInfo(sCSCFRestorationInfo);
        }
        serverAssignmentRequest.setMultipleRegistrationIndication(new MultipleRegistrationIndication(MultipleRegistrationIndication.Value.MULTIPLE_REGISTRATION));
        serverAssignmentRequest.setSessionPriority(new SessionPriority(SessionPriority.Value.PRIORITY2));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(52060222)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(1817621268)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(1321093427)));
            // add more AVP as ANY values to supportedFeatures
            serverAssignmentRequest.addSupportedFeatures(supportedFeatures);
        }
        serverAssignmentRequest.addPublicIdentity(new PublicIdentity("utf8string-538081923"));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-578732935.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring1357950688"));
            // add more AVP as ANY values to proxyInfo
            serverAssignmentRequest.addProxyInfo(proxyInfo);
        }
        serverAssignmentRequest.addRouteRecord(new diameter.base.RouteRecord("id1541810146.diameter.com"));
        // add more AVP as ANY values to serverAssignmentRequest

        byte[] buffer = serverAssignmentRequest.encode();
        ServerAssignmentRequest serverAssignmentRequest2 = new ServerAssignmentRequest(buffer);
        String s1 = serverAssignmentRequest.toString();
        String s2 = serverAssignmentRequest2.toString();
        if (!s1.equals(s2)) {
            System.err.println("serverAssignmentRequest1 = " + s1);
            System.err.println("serverAssignmentRequest2 = " + s2);
            throw new VerificationException("ServerAssignmentRequest encoding/decoding failure");
        }
    }

    public static void testServerAssignmentAnswer() throws Exception {
        ServerAssignmentAnswer serverAssignmentAnswer = new ServerAssignmentAnswer(false, false);
        serverAssignmentAnswer.setSessionId(new diameter.base.SessionId("utf8string-2085827459"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(4747849)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-1732854671)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(645336846)));
            serverAssignmentAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        serverAssignmentAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        serverAssignmentAnswer.setOriginHost(new diameter.base.OriginHost("id1566457965.diameter.com"));
        serverAssignmentAnswer.setOriginRealm(new diameter.base.OriginRealm("id-1179457356.diameter.com"));
        serverAssignmentAnswer.setResultCode(new diameter.base.ResultCode(new Integer(-966019975)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(-1204181517)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(1137459654)));
            serverAssignmentAnswer.setExperimentalResult(experimentalResult);
        }
        serverAssignmentAnswer.setUserName(new diameter.base.UserName("utf8string1736596034"));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-2096569337)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(1231655959)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(1662289450)));
            // add more AVP as ANY values to supportedFeatures
            serverAssignmentAnswer.addSupportedFeatures(supportedFeatures);
        }
        serverAssignmentAnswer.setUserData(new UserData("octetstring1639406493"));
        {
            ChargingInformation chargingInformation = new ChargingInformation();
            chargingInformation.setPrimaryEventChargingFunctionName(new PrimaryEventChargingFunctionName(new URI("domain914683573.com", URI.Scheme.AAAS, (short)7262, URI.Transport.TCP, URI.Protocol.DIAMETER)));
            chargingInformation.setSecondaryEventChargingFunctionName(new SecondaryEventChargingFunctionName(new URI("domain1627841655.com", URI.Scheme.AAAS, (short)17849, URI.Transport.TCP, URI.Protocol.DIAMETER)));
            chargingInformation.setPrimaryChargingCollectionFunctionName(new PrimaryChargingCollectionFunctionName(new URI("domain-281328439.com", URI.Scheme.AAAS, (short)15824, URI.Transport.TCP, URI.Protocol.DIAMETER)));
            chargingInformation.setSecondaryChargingCollectionFunctionName(new SecondaryChargingCollectionFunctionName(new URI("domain1573968363.com", URI.Scheme.AAAS, (short)3774, URI.Transport.TCP, URI.Protocol.DIAMETER)));
            // add more AVP as ANY values to chargingInformation
            serverAssignmentAnswer.setChargingInformation(chargingInformation);
        }
        {
            AssociatedIdentities associatedIdentities = new AssociatedIdentities();
            associatedIdentities.addUserName(new diameter.base.UserName("utf8string-2006448309"));
            // add more AVP as ANY values to associatedIdentities
            serverAssignmentAnswer.setAssociatedIdentities(associatedIdentities);
        }
        serverAssignmentAnswer.setLooseRouteIndication(new LooseRouteIndication(LooseRouteIndication.Value.LOOSE_ROUTE_REQUIRED));
        {
            SCSCFRestorationInfo sCSCFRestorationInfo = new SCSCFRestorationInfo();
            sCSCFRestorationInfo.setUserName(new diameter.base.UserName("utf8string190548659"));
            {
                RestorationInfo restorationInfo = new RestorationInfo();
                restorationInfo.setPath(new Path("octetstring-1910931188"));
                restorationInfo.setContact(new Contact("octetstring859593907"));
                {
                    SubscriptionInfo subscriptionInfo = new SubscriptionInfo();
                    subscriptionInfo.setCallIDSIPHeader(new CallIDSIPHeader("octetstring1234344358"));
                    subscriptionInfo.setFromSIPHeader(new FromSIPHeader("octetstring36747201"));
                    subscriptionInfo.setToSIPHeader(new ToSIPHeader("octetstring-217424257"));
                    subscriptionInfo.setRecordRoute(new RecordRoute("octetstring2044814563"));
                    subscriptionInfo.setContact(new Contact("octetstring914862996"));
                    // add more AVP as ANY values to subscriptionInfo
                    restorationInfo.setSubscriptionInfo(subscriptionInfo);
                }
                // add more AVP as ANY values to restorationInfo
                sCSCFRestorationInfo.addRestorationInfo(restorationInfo);
            }
            sCSCFRestorationInfo.setSIPAuthenticationScheme(new SIPAuthenticationScheme("utf8string676904418"));
            // add more AVP as ANY values to sCSCFRestorationInfo
            serverAssignmentAnswer.addSCSCFRestorationInfo(sCSCFRestorationInfo);
        }
        {
            AssociatedRegisteredIdentities associatedRegisteredIdentities = new AssociatedRegisteredIdentities();
            associatedRegisteredIdentities.addUserName(new diameter.base.UserName("utf8string-2021526541"));
            // add more AVP as ANY values to associatedRegisteredIdentities
            serverAssignmentAnswer.setAssociatedRegisteredIdentities(associatedRegisteredIdentities);
        }
        serverAssignmentAnswer.setServerName(new ServerName("utf8string-738416553"));
        serverAssignmentAnswer.setWildcardedPublicIdentity(new WildcardedPublicIdentity("utf8string-957256247"));
        serverAssignmentAnswer.setPriviledgedSenderIndication(new PriviledgedSenderIndication(PriviledgedSenderIndication.Value.NOT_PRIVILEDGED_SENDER));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-2025398006.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-1900593510"));
            // add more AVP as ANY values to proxyInfo
            serverAssignmentAnswer.addProxyInfo(proxyInfo);
        }
        serverAssignmentAnswer.addRouteRecord(new diameter.base.RouteRecord("id-1482880803.diameter.com"));
        // add more AVP as ANY values to serverAssignmentAnswer

        byte[] buffer = serverAssignmentAnswer.encode();
        ServerAssignmentAnswer serverAssignmentAnswer2 = new ServerAssignmentAnswer(buffer);
        String s1 = serverAssignmentAnswer.toString();
        String s2 = serverAssignmentAnswer2.toString();
        if (!s1.equals(s2)) {
            System.err.println("serverAssignmentAnswer1 = " + s1);
            System.err.println("serverAssignmentAnswer2 = " + s2);
            throw new VerificationException("ServerAssignmentAnswer encoding/decoding failure");
        }
    }

    public static void main(String[] args) throws Exception {
        testServerAssignmentRequest();
        testServerAssignmentAnswer();
    }
}
