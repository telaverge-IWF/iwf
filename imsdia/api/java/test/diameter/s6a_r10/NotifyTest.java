package diameter.s6a_r10;

import com.intellinet.diameter.*;
import diameter.*;

public class NotifyTest {

    public static void testNotifyRequest() throws Exception {
        NotifyRequest notifyRequest = new NotifyRequest(false, false);
        notifyRequest.setSessionId(new diameter.base.SessionId("utf8string92237455"));
        notifyRequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        notifyRequest.setOriginHost(new diameter.base.OriginHost("id-1142552806.diameter.com"));
        notifyRequest.setOriginRealm(new diameter.base.OriginRealm("id1545046515.diameter.com"));
        notifyRequest.setDestinationRealm(new diameter.base.DestinationRealm("id1876373894.diameter.com"));
        notifyRequest.setUserName(new diameter.base.UserName("utf8string-836795146"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-1591454115)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(1148980281)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(1235897797)));
            notifyRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        notifyRequest.setDestinationHost(new diameter.base.DestinationHost("id287229138.diameter.com"));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(1437761829)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(-1974293796)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-1729764801)));
            // add more AVP as ANY values to supportedFeatures
            notifyRequest.addSupportedFeatures(supportedFeatures);
        }
        {
            TerminalInformation terminalInformation = new TerminalInformation();
            terminalInformation.setIMEI(new IMEI("utf8string-1829558586"));
            terminalInformation.setS6a3GPP2MEID(new S6a3GPP2MEID("octetstring-2142808945"));
            terminalInformation.setSoftwareVersion(new SoftwareVersion("utf8string2098513916"));
            // add more AVP as ANY values to terminalInformation
            notifyRequest.setTerminalInformation(terminalInformation);
        }
        notifyRequest.setNORFlags(new NORFlags(new Integer(-191715594)));
        {
            MIP6AgentInfo mIP6AgentInfo = new MIP6AgentInfo();
            mIP6AgentInfo.addMIPHomeAgentAddress(new MIPHomeAgentAddress(new Address(Address.Family.IPV4, "101.1.66.69")));
            {
                MIPHomeAgentHost mIPHomeAgentHost = new MIPHomeAgentHost();
                mIPHomeAgentHost.setDestinationRealm(new diameter.base.DestinationRealm("id-125516170.diameter.com"));
                mIPHomeAgentHost.setDestinationHost(new diameter.base.DestinationHost("id1249956259.diameter.com"));
                // add more AVP as ANY values to mIPHomeAgentHost
                mIP6AgentInfo.setMIPHomeAgentHost(mIPHomeAgentHost);
            }
            mIP6AgentInfo.setMIP6HomeLinkPrefix(new MIP6HomeLinkPrefix("octetstring290572101"));
            // add more AVP as ANY values to mIP6AgentInfo
            notifyRequest.setMIP6AgentInfo(mIP6AgentInfo);
        }
        notifyRequest.setVisitedNetworkIdentifier(new VisitedNetworkIdentifier("octetstring-823215238"));
        notifyRequest.setContextIdentifier(new ContextIdentifier(new Integer(79214587)));
        notifyRequest.setServiceSelection(new ServiceSelection("utf8string-1378753267"));
        notifyRequest.setAlertReason(new AlertReason(AlertReason.Value.UE_MEMORY_AVAILABLE));
        notifyRequest.setUESRVCCCapability(new UESRVCCCapability(UESRVCCCapability.Value.UE_SRVCC_NOT_SUPPORTED));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id1493880174.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-2071997119"));
            // add more AVP as ANY values to proxyInfo
            notifyRequest.addProxyInfo(proxyInfo);
        }
        notifyRequest.addRouteRecord(new diameter.base.RouteRecord("id718163102.diameter.com"));
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
        notifyAnswer.setSessionId(new diameter.base.SessionId("utf8string-1970190919"));
        notifyAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        notifyAnswer.setOriginHost(new diameter.base.OriginHost("id-387872549.diameter.com"));
        notifyAnswer.setOriginRealm(new diameter.base.OriginRealm("id1994229710.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(1098577609)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(1774681817)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-715835513)));
            notifyAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        notifyAnswer.setResultCode(new diameter.base.ResultCode(new Integer(990090231)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(-2129655886)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(1262743577)));
            notifyAnswer.setExperimentalResult(experimentalResult);
        }
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-1591139406)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(-1251467275)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(1729465059)));
            // add more AVP as ANY values to supportedFeatures
            notifyAnswer.addSupportedFeatures(supportedFeatures);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id773385253.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring1072282499"));
            // add more AVP as ANY values to proxyInfo
            notifyAnswer.addProxyInfo(proxyInfo);
        }
        notifyAnswer.addRouteRecord(new diameter.base.RouteRecord("id-60744922.diameter.com"));
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
