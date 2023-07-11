package diameter.s6a_r11;

import com.intellinet.diameter.*;
import diameter.*;

public class NotifyTest {

    public static void testNotifyRequest() throws Exception {
        NotifyRequest notifyRequest = new NotifyRequest(false, false);
        notifyRequest.setSessionId(new diameter.base.SessionId("utf8string89061466"));
        notifyRequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        notifyRequest.setOriginHost(new diameter.base.OriginHost("id2040395434.diameter.com"));
        notifyRequest.setOriginRealm(new diameter.base.OriginRealm("id625764373.diameter.com"));
        notifyRequest.setDestinationRealm(new diameter.base.DestinationRealm("id-518223716.diameter.com"));
        notifyRequest.setUserName(new diameter.base.UserName("utf8string1928985479"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-1096042226)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-2084730845)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-330160554)));
            notifyRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        notifyRequest.setDestinationHost(new diameter.base.DestinationHost("id1288433858.diameter.com"));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-38796688)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(578671606)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-720297466)));
            // add more AVP as ANY values to supportedFeatures
            notifyRequest.addSupportedFeatures(supportedFeatures);
        }
        {
            TerminalInformation terminalInformation = new TerminalInformation();
            terminalInformation.setIMEI(new IMEI("utf8string-2037075365"));
            terminalInformation.setS6a3GPP2MEID(new S6a3GPP2MEID("octetstring-1438168791"));
            terminalInformation.setSoftwareVersion(new SoftwareVersion("utf8string-1530752347"));
            // add more AVP as ANY values to terminalInformation
            notifyRequest.setTerminalInformation(terminalInformation);
        }
        notifyRequest.setNORFlags(new NORFlags(new Integer(-932248848)));
        {
            MIP6AgentInfo mIP6AgentInfo = new MIP6AgentInfo();
            mIP6AgentInfo.addMIPHomeAgentAddress(new MIPHomeAgentAddress(new Address(Address.Family.IPV4, "126.98.119.69")));
            {
                MIPHomeAgentHost mIPHomeAgentHost = new MIPHomeAgentHost();
                mIPHomeAgentHost.setDestinationRealm(new diameter.base.DestinationRealm("id-1395176297.diameter.com"));
                mIPHomeAgentHost.setDestinationHost(new diameter.base.DestinationHost("id180771289.diameter.com"));
                // add more AVP as ANY values to mIPHomeAgentHost
                mIP6AgentInfo.setMIPHomeAgentHost(mIPHomeAgentHost);
            }
            mIP6AgentInfo.setMIP6HomeLinkPrefix(new MIP6HomeLinkPrefix("octetstring479712336"));
            // add more AVP as ANY values to mIP6AgentInfo
            notifyRequest.setMIP6AgentInfo(mIP6AgentInfo);
        }
        notifyRequest.setVisitedNetworkIdentifier(new VisitedNetworkIdentifier("octetstring482203265"));
        notifyRequest.setContextIdentifier(new ContextIdentifier(new Integer(-765917728)));
        notifyRequest.setServiceSelection(new ServiceSelection("utf8string-1694517020"));
        notifyRequest.setAlertReason(new AlertReason(AlertReason.Value.UE_MEMORY_AVAILABLE));
        notifyRequest.setUESRVCCCapability(new UESRVCCCapability(UESRVCCCapability.Value.UE_SRVCC_SUPPORTED));
        notifyRequest.setHomogeneousSupportofIMSVoiceOverPSSessions(new HomogeneousSupportofIMSVoiceOverPSSessions(HomogeneousSupportofIMSVoiceOverPSSessions.Value.NOT_SUPPORTED));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-1443240522.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring1265452604"));
            // add more AVP as ANY values to proxyInfo
            notifyRequest.addProxyInfo(proxyInfo);
        }
        notifyRequest.addRouteRecord(new diameter.base.RouteRecord("id350965828.diameter.com"));
        // add more AVP as ANY values to notifyRequest

        byte[] buffer = notifyRequest.encode();
        NotifyRequest notifyRequest2 = new NotifyRequest(buffer);
        String s1 = notifyRequest.toString();
        String s2 = notifyRequest2.toString();
        if (!s1.equals(s2)) {
            System.err.println("notifyRequest1 = " + s1);
            System.err.println("notifyRequest2 = " + s2);
            throw new VerificationException("NotifyRequest encoding/decoding failure");
        }
    }

    public static void testNotifyAnswer() throws Exception {
        NotifyAnswer notifyAnswer = new NotifyAnswer(false, false);
        notifyAnswer.setSessionId(new diameter.base.SessionId("utf8string590895937"));
        notifyAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        notifyAnswer.setOriginHost(new diameter.base.OriginHost("id-1288848951.diameter.com"));
        notifyAnswer.setOriginRealm(new diameter.base.OriginRealm("id-684777135.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(1856603034)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(1814935323)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-1357418505)));
            notifyAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        notifyAnswer.setResultCode(new diameter.base.ResultCode(new Integer(1050738393)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(546440334)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(993983812)));
            notifyAnswer.setExperimentalResult(experimentalResult);
        }
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-917108653)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(-285593218)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-597340708)));
            // add more AVP as ANY values to supportedFeatures
            notifyAnswer.addSupportedFeatures(supportedFeatures);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-1444864857.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring1860125185"));
            // add more AVP as ANY values to proxyInfo
            notifyAnswer.addProxyInfo(proxyInfo);
        }
        notifyAnswer.addRouteRecord(new diameter.base.RouteRecord("id1028937925.diameter.com"));
        // add more AVP as ANY values to notifyAnswer

        byte[] buffer = notifyAnswer.encode();
        NotifyAnswer notifyAnswer2 = new NotifyAnswer(buffer);
        String s1 = notifyAnswer.toString();
        String s2 = notifyAnswer2.toString();
        if (!s1.equals(s2)) {
            System.err.println("notifyAnswer1 = " + s1);
            System.err.println("notifyAnswer2 = " + s2);
            throw new VerificationException("NotifyAnswer encoding/decoding failure");
        }
    }

    public static void main(String[] args) throws Exception {
        testNotifyRequest();
        testNotifyAnswer();
    }
}
