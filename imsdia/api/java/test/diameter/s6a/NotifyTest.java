package diameter.s6a;

import com.intellinet.diameter.*;
import diameter.*;

public class NotifyTest {

    public static void testNotifyRequest() throws Exception {
        NotifyRequest notifyRequest = new NotifyRequest(false, false);
        notifyRequest.setSessionId(new diameter.base.SessionId("utf8string-969470417"));
        notifyRequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        notifyRequest.setOriginHost(new diameter.base.OriginHost("id-573718676.diameter.com"));
        notifyRequest.setOriginRealm(new diameter.base.OriginRealm("id1432601068.diameter.com"));
        notifyRequest.setDestinationRealm(new diameter.base.DestinationRealm("id-1773359194.diameter.com"));
        notifyRequest.setUserName(new diameter.base.UserName("utf8string715447879"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(2127807892)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(1958820869)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(1059138687)));
            notifyRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        notifyRequest.setDestinationHost(new diameter.base.DestinationHost("id910780694.diameter.com"));
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-1608486387)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(-456445903)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-511470649)));
            // add more AVP as ANY values to supportedFeatures
            notifyRequest.addSupportedFeatures(supportedFeatures);
        }
        {
            TerminalInformation terminalInformation = new TerminalInformation();
            terminalInformation.setIMEI(new IMEI("utf8string1355121194"));
            terminalInformation.setS6a3GPP2MEID(new S6a3GPP2MEID("octetstring-1473450799"));
            terminalInformation.setSoftwareVersion(new SoftwareVersion("utf8string2075961027"));
            // add more AVP as ANY values to terminalInformation
            notifyRequest.setTerminalInformation(terminalInformation);
        }
        notifyRequest.setNORFlags(new NORFlags(new Integer(-1503220117)));
        {
            MIP6AgentInfo mIP6AgentInfo = new MIP6AgentInfo();
            mIP6AgentInfo.addMIPHomeAgentAddress(new MIPHomeAgentAddress(new Address(Address.Family.IPV4, "118.44.6.33")));
            {
                MIPHomeAgentHost mIPHomeAgentHost = new MIPHomeAgentHost();
                mIPHomeAgentHost.setDestinationRealm(new diameter.base.DestinationRealm("id-1162465832.diameter.com"));
                mIPHomeAgentHost.setDestinationHost(new diameter.base.DestinationHost("id-1279728842.diameter.com"));
                // add more AVP as ANY values to mIPHomeAgentHost
                mIP6AgentInfo.setMIPHomeAgentHost(mIPHomeAgentHost);
            }
            mIP6AgentInfo.setMIP6HomeLinkPrefix(new MIP6HomeLinkPrefix("octetstring1368201838"));
            // add more AVP as ANY values to mIP6AgentInfo
            notifyRequest.setMIP6AgentInfo(mIP6AgentInfo);
        }
        notifyRequest.setContextIdentifier(new ContextIdentifier(new Integer(-2014243704)));
        notifyRequest.setServiceSelection(new ServiceSelection("utf8string-203163541"));
        notifyRequest.setAlertReason(new AlertReason(AlertReason.Value.UE_MEMORY_AVAILABLE));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-1686456816.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring1255697806"));
            // add more AVP as ANY values to proxyInfo
            notifyRequest.addProxyInfo(proxyInfo);
        }
        notifyRequest.addRouteRecord(new diameter.base.RouteRecord("id-1190118120.diameter.com"));
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
        notifyAnswer.setSessionId(new diameter.base.SessionId("utf8string-702101081"));
        notifyAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        notifyAnswer.setOriginHost(new diameter.base.OriginHost("id-951463919.diameter.com"));
        notifyAnswer.setOriginRealm(new diameter.base.OriginRealm("id-1813555853.diameter.com"));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-1954619018)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-1047677209)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(-1797277240)));
            notifyAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        notifyAnswer.setResultCode(new diameter.base.ResultCode(new Integer(-242720060)));
        {
            diameter.base.ExperimentalResult experimentalResult = new diameter.base.ExperimentalResult();
            experimentalResult.setVendorId(new diameter.base.VendorId(new Integer(-1351234418)));
            experimentalResult.setExperimentalResultCode(new diameter.base.ExperimentalResultCode(new Integer(-953414410)));
            notifyAnswer.setExperimentalResult(experimentalResult);
        }
        {
            SupportedFeatures supportedFeatures = new SupportedFeatures();
            supportedFeatures.setVendorId(new diameter.base.VendorId(new Integer(-1916652700)));
            supportedFeatures.setFeatureListID(new FeatureListID(new Integer(577144930)));
            supportedFeatures.setFeatureList(new FeatureList(new Integer(-399803244)));
            // add more AVP as ANY values to supportedFeatures
            notifyAnswer.addSupportedFeatures(supportedFeatures);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id412114330.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring1960140274"));
            // add more AVP as ANY values to proxyInfo
            notifyAnswer.addProxyInfo(proxyInfo);
        }
        notifyAnswer.addRouteRecord(new diameter.base.RouteRecord("id-11339961.diameter.com"));
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
