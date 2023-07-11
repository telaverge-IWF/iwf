package diameter.nasreq;

import com.intellinet.diameter.*;
import diameter.*;

public class AATest {

    public static void testAARequest() throws Exception {
        AARequest aARequest = new AARequest(false, false);
        aARequest.setSessionId(new diameter.base.SessionId("utf8string719032248"));
        aARequest.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-55332132)));
        aARequest.setOriginHost(new diameter.base.OriginHost("id1216115928.diameter.com"));
        aARequest.setOriginRealm(new diameter.base.OriginRealm("id367294475.diameter.com"));
        aARequest.setDestinationRealm(new diameter.base.DestinationRealm("id-1290075055.diameter.com"));
        aARequest.setAuthRequestType(new diameter.base.AuthRequestType(diameter.base.AuthRequestType.Value.AUTHENTICATE_ONLY));
        aARequest.setDestinationHost(new diameter.base.DestinationHost("id1046762680.diameter.com"));
        aARequest.setNASIdentifier(new NASIdentifier("utf8string117672987"));
        aARequest.setNASIPAddress(new NASIPAddress("octetstring264935670"));
        aARequest.setNASIPv6Address(new NASIPv6Address("octetstring1495527969"));
        aARequest.setNASPort(new NASPort(new Integer(-84440125)));
        aARequest.setNASPortId(new NASPortId("utf8string389483419"));
        aARequest.setNASPortType(new NASPortType(NASPortType.Value.PIAFS));
        aARequest.setOriginAAAProtocol(new OriginAAAProtocol(OriginAAAProtocol.Value.RADIUS));
        aARequest.setOriginStateId(new diameter.base.OriginStateId(new Integer(-409180165)));
        aARequest.setPortLimit(new PortLimit(new Integer(-986394988)));
        aARequest.setUserName(new diameter.base.UserName("utf8string257427205"));
        aARequest.setUserPassword(new UserPassword("octetstring414797640"));
        aARequest.setServiceType(new ServiceType(ServiceType.Value.IAPP_REGISTER));
        aARequest.setState(new State("octetstring383327831"));
        aARequest.setAuthorizationLifetime(new diameter.base.AuthorizationLifetime(new Integer(-258400935)));
        aARequest.setAuthGracePeriod(new diameter.base.AuthGracePeriod(new Integer(765736325)));
        aARequest.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.STATE_MAINTAINED));
        aARequest.setCallbackNumber(new CallbackNumber("utf8string499292610"));
        aARequest.setCalledStationId(new CalledStationId("utf8string-615286730"));
        aARequest.setCallingStationId(new CallingStationId("utf8string1982472807"));
        aARequest.setOriginatingLineInfo(new OriginatingLineInfo("octetstring-928122938"));
        aARequest.setConnectInfo(new ConnectInfo("utf8string1997642176"));
        {
            CHAPAuth cHAPAuth = new CHAPAuth();
            cHAPAuth.setCHAPAlgorithm(new CHAPAlgorithm(CHAPAlgorithm.Value.CHAPMD5));
            cHAPAuth.setCHAPIdent(new CHAPIdent("octetstring-2115348863"));
            cHAPAuth.setCHAPResponse(new CHAPResponse("octetstring614109122"));
            // add more AVP as ANY values to cHAPAuth
            aARequest.setCHAPAuth(cHAPAuth);
        }
        aARequest.setCHAPChallenge(new CHAPChallenge("octetstring1880807957"));
        aARequest.addFramedCompression(new FramedCompression(FramedCompression.Value.VJ_TCP_IP));
        aARequest.setFramedInterfaceId(new FramedInterfaceId(new Long(9112160785867207700L)));
        aARequest.setFramedIPAddress(new FramedIPAddress("octetstring-527078821"));
        aARequest.addFramedIPv6Prefix(new FramedIPv6Prefix("octetstring544188747"));
        aARequest.setFramedIPNetmask(new FramedIPNetmask("octetstring-1324565739"));
        aARequest.setFramedMTU(new FramedMTU(new Integer(1170882480)));
        aARequest.setFramedProtocol(new FramedProtocol(FramedProtocol.Value.X_75));
        aARequest.setARAPPassword(new ARAPPassword("octetstring1382845186"));
        aARequest.setARAPSecurity(new ARAPSecurity(new Integer(1001693006)));
        aARequest.addARAPSecurityData(new ARAPSecurityData("octetstring1507886982"));
        aARequest.addLoginIPHost(new LoginIPHost("octetstring1337678896"));
        aARequest.addLoginIPv6Host(new LoginIPv6Host("octetstring2004258785"));
        aARequest.setLoginLATGroup(new LoginLATGroup("octetstring-1937150399"));
        aARequest.setLoginLATNode(new LoginLATNode("octetstring1816590543"));
        aARequest.setLoginLATPort(new LoginLATPort("octetstring1790377170"));
        aARequest.setLoginLATService(new LoginLATService("octetstring-1524885885"));
        {
            Tunneling tunneling = new Tunneling();
            tunneling.setTunnelType(new TunnelType(TunnelType.Value.L2TP));
            tunneling.setTunnelMediumType(new TunnelMediumType(TunnelMediumType.Value.APPLETALK));
            tunneling.setTunnelClientEndpoint(new TunnelClientEndpoint("utf8string1553925966"));
            tunneling.setTunnelServerEndpoint(new TunnelServerEndpoint("utf8string250201451"));
            tunneling.setTunnelPreference(new TunnelPreference(new Integer(-888254299)));
            tunneling.setTunnelClientAuthId(new TunnelClientAuthId("utf8string-450852633"));
            tunneling.setTunnelServerAuthId(new TunnelServerAuthId("utf8string-1387608459"));
            tunneling.setTunnelAssignmentId(new TunnelAssignmentId("octetstring13327856"));
            tunneling.setTunnelPassword(new TunnelPassword("octetstring297411142"));
            tunneling.setTunnelPrivateGroupId(new TunnelPrivateGroupId("octetstring-1889290719"));
            aARequest.addTunneling(tunneling);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-419115963.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring464669302"));
            // add more AVP as ANY values to proxyInfo
            aARequest.addProxyInfo(proxyInfo);
        }
        aARequest.addRouteRecord(new diameter.base.RouteRecord("id551069961.diameter.com"));
        // add more AVP as ANY values to aARequest

        byte[] buffer = aARequest.encode();
        AARequest aARequest2 = new AARequest(buffer);
        String s1 = aARequest.toString();
        String s2 = aARequest2.toString();
        if (!s1.equals(s2)) {
            System.err.println("aARequest1 = " + s1);
            System.err.println("aARequest2 = " + s2);
            throw new VerificationException("AARequest encoding/decoding failure");
        }
    }

    public static void testAAAnswer() throws Exception {
        AAAnswer aAAnswer = new AAAnswer(false, false);
        aAAnswer.setSessionId(new diameter.base.SessionId("utf8string711562001"));
        aAAnswer.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-281719629)));
        aAAnswer.setAuthRequestType(new diameter.base.AuthRequestType(diameter.base.AuthRequestType.Value.AUTHENTICATE_ONLY));
        aAAnswer.setResultCode(new diameter.base.ResultCode(new Integer(-2090321519)));
        aAAnswer.setOriginHost(new diameter.base.OriginHost("id266282273.diameter.com"));
        aAAnswer.setOriginRealm(new diameter.base.OriginRealm("id-686759766.diameter.com"));
        aAAnswer.setUserName(new diameter.base.UserName("utf8string1419274815"));
        aAAnswer.setServiceType(new ServiceType(ServiceType.Value.MODEM_RELAY));
        aAAnswer.addClass(new diameter.base.Class("octetstring1194681919"));
        aAAnswer.addConfigurationToken(new ConfigurationToken("octetstring-230558381"));
        aAAnswer.setAcctInterimInterval(new diameter.base.AcctInterimInterval(new Integer(1579535573)));
        aAAnswer.setErrorMessage(new diameter.base.ErrorMessage("utf8string-1299799295"));
        aAAnswer.setErrorReportingHost(new diameter.base.ErrorReportingHost("id-784007180.diameter.com"));
        aAAnswer.setIdleTimeout(new IdleTimeout(new Integer(-199005289)));
        aAAnswer.setAuthorizationLifetime(new diameter.base.AuthorizationLifetime(new Integer(1972821305)));
        aAAnswer.setAuthGracePeriod(new diameter.base.AuthGracePeriod(new Integer(-1472583527)));
        aAAnswer.setAuthSessionState(new diameter.base.AuthSessionState(diameter.base.AuthSessionState.Value.NO_STATE_MAINTAINED));
        aAAnswer.setReAuthRequestType(new diameter.base.ReAuthRequestType(diameter.base.ReAuthRequestType.Value.AUTHORIZE_ONLY));
        aAAnswer.setMultiRoundTimeOut(new diameter.base.MultiRoundTimeOut(new Integer(609876434)));
        aAAnswer.setSessionTimeout(new diameter.base.SessionTimeout(new Integer(-1322849820)));
        aAAnswer.setState(new State("octetstring-774564745"));
        aAAnswer.addReplyMessage(new ReplyMessage("utf8string-345263576"));
        aAAnswer.setOriginAAAProtocol(new OriginAAAProtocol(OriginAAAProtocol.Value.RADIUS));
        aAAnswer.setOriginStateId(new diameter.base.OriginStateId(new Integer(-63516537)));
        aAAnswer.addFilterId(new FilterId("utf8string-671009400"));
        aAAnswer.setPasswordRetry(new PasswordRetry(new Integer(665835052)));
        aAAnswer.setPortLimit(new PortLimit(new Integer(-1209773370)));
        aAAnswer.setPrompt(new Prompt(Prompt.Value.ECHO));
        aAAnswer.setARAPChallengeResponse(new ARAPChallengeResponse("octetstring-535973220"));
        aAAnswer.setARAPFeatures(new ARAPFeatures("octetstring-2147200001"));
        aAAnswer.setARAPSecurity(new ARAPSecurity(new Integer(1499283343)));
        aAAnswer.addARAPSecurityData(new ARAPSecurityData("octetstring1414529268"));
        aAAnswer.setARAPZoneAccess(new ARAPZoneAccess(ARAPZoneAccess.Value.EXCLUSIVELY));
        aAAnswer.setCallbackId(new CallbackId("utf8string-1152460602"));
        aAAnswer.setCallbackNumber(new CallbackNumber("utf8string1829624084"));
        aAAnswer.setFramedAppletalkLink(new FramedAppletalkLink(new Integer(-1551787205)));
        aAAnswer.addFramedAppletalkNetwork(new FramedAppletalkNetwork(new Integer(-1372955928)));
        aAAnswer.setFramedAppletalkZone(new FramedAppletalkZone("octetstring-2035640384"));
        aAAnswer.addFramedCompression(new FramedCompression(FramedCompression.Value.NONE));
        aAAnswer.setFramedInterfaceId(new FramedInterfaceId(new Long(-1200729527212088883L)));
        aAAnswer.setFramedIPAddress(new FramedIPAddress("octetstring-949048441"));
        aAAnswer.addFramedIPv6Prefix(new FramedIPv6Prefix("octetstring738744855"));
        aAAnswer.setFramedIPv6Pool(new FramedIPv6Pool("octetstring-1589963838"));
        aAAnswer.addFramedIPv6Route(new FramedIPv6Route("utf8string-1134969611"));
        aAAnswer.setFramedIPNetmask(new FramedIPNetmask("octetstring-1084045418"));
        aAAnswer.addFramedRoute(new FramedRoute("utf8string355404829"));
        aAAnswer.setFramedPool(new FramedPool("octetstring1943881817"));
        aAAnswer.setFramedIPXNetwork(new FramedIPXNetwork("utf8string662062865"));
        aAAnswer.setFramedMTU(new FramedMTU(new Integer(-523305461)));
        aAAnswer.setFramedProtocol(new FramedProtocol(FramedProtocol.Value.X_75));
        aAAnswer.setFramedRouting(new FramedRouting(FramedRouting.Value.NONE));
        aAAnswer.addLoginIPHost(new LoginIPHost("octetstring1531250161"));
        aAAnswer.addLoginIPv6Host(new LoginIPv6Host("octetstring-677667412"));
        aAAnswer.setLoginLATGroup(new LoginLATGroup("octetstring-1090213151"));
        aAAnswer.setLoginLATNode(new LoginLATNode("octetstring-486439630"));
        aAAnswer.setLoginLATPort(new LoginLATPort("octetstring554709851"));
        aAAnswer.setLoginLATService(new LoginLATService("octetstring-58561489"));
        aAAnswer.setLoginService(new LoginService(LoginService.Value.PORTMASTER));
        aAAnswer.setLoginTCPPort(new LoginTCPPort(new Integer(1665514091)));
        aAAnswer.addNASFilterRule(new NASFilterRule(new IPFilterRule()));
        aAAnswer.addQoSFilterRule(new QoSFilterRule(new IPFilterRule()));
        {
            Tunneling tunneling = new Tunneling();
            tunneling.setTunnelType(new TunnelType(TunnelType.Value.L2TP));
            tunneling.setTunnelMediumType(new TunnelMediumType(TunnelMediumType.Value.APPLETALK));
            tunneling.setTunnelClientEndpoint(new TunnelClientEndpoint("utf8string-946482999"));
            tunneling.setTunnelServerEndpoint(new TunnelServerEndpoint("utf8string34285387"));
            tunneling.setTunnelPreference(new TunnelPreference(new Integer(-2112692635)));
            tunneling.setTunnelClientAuthId(new TunnelClientAuthId("utf8string1558069911"));
            tunneling.setTunnelServerAuthId(new TunnelServerAuthId("utf8string1732264599"));
            tunneling.setTunnelAssignmentId(new TunnelAssignmentId("octetstring-1239262088"));
            tunneling.setTunnelPassword(new TunnelPassword("octetstring-238191536"));
            tunneling.setTunnelPrivateGroupId(new TunnelPrivateGroupId("octetstring1182552165"));
            aAAnswer.addTunneling(tunneling);
        }
        aAAnswer.addRedirectHost(new diameter.base.RedirectHost(new URI("domain349845684.com", URI.Scheme.AAAS, (short)17198, URI.Transport.TCP, URI.Protocol.DIAMETER)));
        aAAnswer.setRedirectHostUsage(new diameter.base.RedirectHostUsage(diameter.base.RedirectHostUsage.Value.ALL_APPLICATION));
        aAAnswer.setRedirectMaxCacheTime(new diameter.base.RedirectMaxCacheTime(new Integer(-303148245)));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id810885743.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring2108222490"));
            // add more AVP as ANY values to proxyInfo
            aAAnswer.addProxyInfo(proxyInfo);
        }
        // add more AVP as ANY values to aAAnswer

        byte[] buffer = aAAnswer.encode();
        AAAnswer aAAnswer2 = new AAAnswer(buffer);
        String s1 = aAAnswer.toString();
        String s2 = aAAnswer2.toString();
        if (!s1.equals(s2)) {
            System.err.println("aAAnswer1 = " + s1);
            System.err.println("aAAnswer2 = " + s2);
            throw new VerificationException("AAAnswer encoding/decoding failure");
        }
    }

    public static void main(String[] args) throws Exception {
        testAARequest();
        testAAAnswer();
    }
}
