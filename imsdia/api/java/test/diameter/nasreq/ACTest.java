package diameter.nasreq;

import com.intellinet.diameter.*;
import diameter.*;

public class ACTest {

    public static void testACRequest() throws Exception {
        ACRequest aCRequest = new ACRequest(false, false);
        aCRequest.setSessionId(new diameter.base.SessionId("utf8string-455692079"));
        aCRequest.setOriginHost(new diameter.base.OriginHost("id425605703.diameter.com"));
        aCRequest.setOriginRealm(new diameter.base.OriginRealm("id-743426146.diameter.com"));
        aCRequest.setDestinationRealm(new diameter.base.DestinationRealm("id748266463.diameter.com"));
        aCRequest.setAccountingRecordType(new diameter.base.AccountingRecordType(diameter.base.AccountingRecordType.Value.START_RECORD));
        aCRequest.setAccountingRecordNumber(new diameter.base.AccountingRecordNumber(new Integer(-1301132605)));
        aCRequest.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(1979475749)));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-1816025792)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(1606146384)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(813461374)));
            aCRequest.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        aCRequest.setUserName(new diameter.base.UserName("utf8string-1240405763"));
        aCRequest.setAccountingSubSessionId(new diameter.base.AccountingSubSessionId(new Long(5482313823980832640L)));
        aCRequest.setAcctSessionId(new diameter.base.AcctSessionId("octetstring-1728264419"));
        aCRequest.setAcctMultiSessionId(new diameter.base.AcctMultiSessionId("utf8string1001875016"));
        aCRequest.setOriginAAAProtocol(new OriginAAAProtocol(OriginAAAProtocol.Value.RADIUS));
        aCRequest.setOriginStateId(new diameter.base.OriginStateId(new Integer(209396616)));
        aCRequest.setDestinationHost(new diameter.base.DestinationHost("id1247053458.diameter.com"));
        aCRequest.setEventTimestamp(new diameter.base.EventTimestamp(new Integer(1405290491)));
        aCRequest.setAcctDelayTime(new AcctDelayTime(new Integer(334608604)));
        aCRequest.setNASIdentifier(new NASIdentifier("utf8string-81636051"));
        aCRequest.setNASIPAddress(new NASIPAddress("octetstring-1004876219"));
        aCRequest.setNASIPv6Address(new NASIPv6Address("octetstring397145605"));
        aCRequest.setNASPort(new NASPort(new Integer(-1824889511)));
        aCRequest.setNASPortId(new NASPortId("utf8string-1664999595"));
        aCRequest.setNASPortType(new NASPortType(NASPortType.Value.Token_Ring));
        aCRequest.addClass(new diameter.base.Class("octetstring1497441462"));
        aCRequest.setServiceType(new ServiceType(ServiceType.Value.AUTHENTICATE_ONLY));
        aCRequest.setTerminationCause(new diameter.base.TerminationCause(diameter.base.TerminationCause.Value.DIAMETER_BAD_ANSWER));
        aCRequest.setAccountingInputOctets(new AccountingInputOctets(new Long(6173906709596017758L)));
        aCRequest.setAccountingInputPackets(new AccountingInputPackets(new Long(-7194334654825688876L)));
        aCRequest.setAccountingOutputOctets(new AccountingOutputOctets(new Long(4295501082762700596L)));
        aCRequest.setAccountingOutputPackets(new AccountingOutputPackets(new Long(3255807377344146707L)));
        aCRequest.setAcctAuthentic(new AcctAuthentic(AcctAuthentic.Value.LOCAL));
        aCRequest.setAccountingAuthMethod(new AccountingAuthMethod(AccountingAuthMethod.Value.CHAP));
        aCRequest.setAcctLinkCount(new AcctLinkCount(new Integer(-1970367)));
        aCRequest.setAcctSessionTime(new AcctSessionTime(new Integer(1093645546)));
        aCRequest.setAcctTunnelConnection(new AcctTunnelConnection("octetstring1766339780"));
        aCRequest.setAcctTunnelPacketsLost(new AcctTunnelPacketsLost(new Integer(1642997725)));
        aCRequest.setCallbackId(new CallbackId("utf8string-328434595"));
        aCRequest.setCallbackNumber(new CallbackNumber("utf8string-2114396623"));
        aCRequest.setCalledStationId(new CalledStationId("utf8string-685099980"));
        aCRequest.setCallingStationId(new CallingStationId("utf8string1895567393"));
        aCRequest.addConnectInfo(new ConnectInfo("utf8string-529942611"));
        aCRequest.setOriginatingLineInfo(new OriginatingLineInfo("octetstring600446397"));
        aCRequest.setAuthorizationLifetime(new diameter.base.AuthorizationLifetime(new Integer(677160918)));
        aCRequest.setSessionTimeout(new diameter.base.SessionTimeout(new Integer(1899501565)));
        aCRequest.setIdleTimeout(new IdleTimeout(new Integer(171851606)));
        aCRequest.setPortLimit(new PortLimit(new Integer(-1003910430)));
        aCRequest.setAccountingRealtimeRequired(new diameter.base.AccountingRealtimeRequired(diameter.base.AccountingRealtimeRequired.Value.GRANT_AND_STORE));
        aCRequest.setAcctInterimInterval(new diameter.base.AcctInterimInterval(new Integer(-385452477)));
        aCRequest.addFilterId(new FilterId("utf8string617047847"));
        aCRequest.addNASFilterRule(new NASFilterRule(new IPFilterRule()));
        aCRequest.addQoSFilterRule(new QoSFilterRule(new IPFilterRule()));
        aCRequest.setFramedAppletalkLink(new FramedAppletalkLink(new Integer(1014198072)));
        aCRequest.setFramedAppletalkNetwork(new FramedAppletalkNetwork(new Integer(1064127116)));
        aCRequest.setFramedAppletalkZone(new FramedAppletalkZone("octetstring474020420"));
        aCRequest.setFramedCompression(new FramedCompression(FramedCompression.Value.IPX));
        aCRequest.setFramedInterfaceId(new FramedInterfaceId(new Long(-6373597730646159316L)));
        aCRequest.setFramedIPAddress(new FramedIPAddress("octetstring748318065"));
        aCRequest.setFramedIPNetmask(new FramedIPNetmask("octetstring-1871275609"));
        aCRequest.addFramedIPv6Prefix(new FramedIPv6Prefix("octetstring2046108556"));
        aCRequest.setFramedIPv6Pool(new FramedIPv6Pool("octetstring1235272121"));
        aCRequest.addFramedIPv6Route(new FramedIPv6Route("utf8string631499589"));
        aCRequest.setFramedIPXNetwork(new FramedIPXNetwork("utf8string406984909"));
        aCRequest.setFramedMTU(new FramedMTU(new Integer(-353760397)));
        aCRequest.setFramedPool(new FramedPool("octetstring590398012"));
        aCRequest.setFramedProtocol(new FramedProtocol(FramedProtocol.Value.GANDALF));
        aCRequest.addFramedRoute(new FramedRoute("utf8string1936676471"));
        aCRequest.setFramedRouting(new FramedRouting(FramedRouting.Value.NONE));
        aCRequest.addLoginIPHost(new LoginIPHost("octetstring-1395196001"));
        aCRequest.addLoginIPv6Host(new LoginIPv6Host("octetstring459815418"));
        aCRequest.setLoginLATGroup(new LoginLATGroup("octetstring1325857668"));
        aCRequest.setLoginLATNode(new LoginLATNode("octetstring736327258"));
        aCRequest.setLoginLATPort(new LoginLATPort("octetstring1033959773"));
        aCRequest.setLoginLATService(new LoginLATService("octetstring1701247600"));
        aCRequest.setLoginService(new LoginService(LoginService.Value.RLOGIN));
        aCRequest.setLoginTCPPort(new LoginTCPPort(new Integer(-173797431)));
        {
            Tunneling tunneling = new Tunneling();
            tunneling.setTunnelType(new TunnelType(TunnelType.Value.N_ESP));
            tunneling.setTunnelMediumType(new TunnelMediumType(TunnelMediumType.Value.E_164_NSAP));
            tunneling.setTunnelClientEndpoint(new TunnelClientEndpoint("utf8string-1457955373"));
            tunneling.setTunnelServerEndpoint(new TunnelServerEndpoint("utf8string15217631"));
            tunneling.setTunnelPreference(new TunnelPreference(new Integer(1101158064)));
            tunneling.setTunnelClientAuthId(new TunnelClientAuthId("utf8string-171566568"));
            tunneling.setTunnelServerAuthId(new TunnelServerAuthId("utf8string-319325218"));
            tunneling.setTunnelAssignmentId(new TunnelAssignmentId("octetstring370820070"));
            tunneling.setTunnelPassword(new TunnelPassword("octetstring1963674353"));
            tunneling.setTunnelPrivateGroupId(new TunnelPrivateGroupId("octetstring455748434"));
            aCRequest.addTunneling(tunneling);
        }
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-2140229433.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring1683694737"));
            // add more AVP as ANY values to proxyInfo
            aCRequest.addProxyInfo(proxyInfo);
        }
        aCRequest.addRouteRecord(new diameter.base.RouteRecord("id-1528381172.diameter.com"));
        // add more AVP as ANY values to aCRequest

        byte[] buffer = aCRequest.encode();
        ACRequest aCRequest2 = new ACRequest(buffer);
        String s1 = aCRequest.toString();
        String s2 = aCRequest2.toString();
        if (!s1.equals(s2)) {
            System.err.println("aCRequest1 = " + s1);
            System.err.println("aCRequest2 = " + s2);
            throw new VerificationException("ACRequest encoding/decoding failure");
        }
    }

    public static void testACAnswer() throws Exception {
        ACAnswer aCAnswer = new ACAnswer(false, false);
        aCAnswer.setSessionId(new diameter.base.SessionId("utf8string-1949151362"));
        aCAnswer.setResultCode(new diameter.base.ResultCode(new Integer(1573643824)));
        aCAnswer.setOriginHost(new diameter.base.OriginHost("id1935221823.diameter.com"));
        aCAnswer.setOriginRealm(new diameter.base.OriginRealm("id1637899946.diameter.com"));
        aCAnswer.setAccountingRecordType(new diameter.base.AccountingRecordType(diameter.base.AccountingRecordType.Value.INTERIM_RECORD));
        aCAnswer.setAccountingRecordNumber(new diameter.base.AccountingRecordNumber(new Integer(-1405477501)));
        aCAnswer.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(565739904)));
        {
            diameter.base.VendorSpecificApplicationId vendorSpecificApplicationId = new diameter.base.VendorSpecificApplicationId();
            vendorSpecificApplicationId.addVendorId(new diameter.base.VendorId(new Integer(-1138661508)));
            vendorSpecificApplicationId.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-391795226)));
            vendorSpecificApplicationId.setAcctApplicationId(new diameter.base.AcctApplicationId(new Integer(1540266825)));
            aCAnswer.setVendorSpecificApplicationId(vendorSpecificApplicationId);
        }
        aCAnswer.setUserName(new diameter.base.UserName("utf8string-828418601"));
        aCAnswer.setAccountingSubSessionId(new diameter.base.AccountingSubSessionId(new Long(1152862915516877019L)));
        aCAnswer.setAcctSessionId(new diameter.base.AcctSessionId("octetstring-2065960004"));
        aCAnswer.setAcctMultiSessionId(new diameter.base.AcctMultiSessionId("utf8string2110712001"));
        aCAnswer.setEventTimestamp(new diameter.base.EventTimestamp(new Integer(579605439)));
        aCAnswer.setErrorMessage(new diameter.base.ErrorMessage("utf8string2039996220"));
        aCAnswer.setErrorReportingHost(new diameter.base.ErrorReportingHost("id-2087662438.diameter.com"));
        aCAnswer.setOriginAAAProtocol(new OriginAAAProtocol(OriginAAAProtocol.Value.RADIUS));
        aCAnswer.setOriginStateId(new diameter.base.OriginStateId(new Integer(1778463266)));
        aCAnswer.setNASIdentifier(new NASIdentifier("utf8string1995866950"));
        aCAnswer.setNASIPAddress(new NASIPAddress("octetstring-1814009797"));
        aCAnswer.setNASIPv6Address(new NASIPv6Address("octetstring-1554155026"));
        aCAnswer.setNASPort(new NASPort(new Integer(1288981703)));
        aCAnswer.setNASPortId(new NASPortId("utf8string-1036725107"));
        aCAnswer.setNASPortType(new NASPortType(NASPortType.Value.Async));
        aCAnswer.setServiceType(new ServiceType(ServiceType.Value.LOGIN));
        aCAnswer.setTerminationCause(new diameter.base.TerminationCause(diameter.base.TerminationCause.Value.DIAMETER_ADMINISTRATIVE));
        aCAnswer.setAccountingRealtimeRequired(new diameter.base.AccountingRealtimeRequired(diameter.base.AccountingRealtimeRequired.Value.GRANT_AND_LOSE));
        aCAnswer.setAcctInterimInterval(new diameter.base.AcctInterimInterval(new Integer(-2069388449)));
        aCAnswer.addClass(new diameter.base.Class("octetstring1974010531"));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id1050298682.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring1059653260"));
            // add more AVP as ANY values to proxyInfo
            aCAnswer.addProxyInfo(proxyInfo);
        }
        aCAnswer.addRouteRecord(new diameter.base.RouteRecord("id938609604.diameter.com"));
        // add more AVP as ANY values to aCAnswer

        byte[] buffer = aCAnswer.encode();
        ACAnswer aCAnswer2 = new ACAnswer(buffer);
        String s1 = aCAnswer.toString();
        String s2 = aCAnswer2.toString();
        if (!s1.equals(s2)) {
            System.err.println("aCAnswer1 = " + s1);
            System.err.println("aCAnswer2 = " + s2);
            throw new VerificationException("ACAnswer encoding/decoding failure");
        }
    }

    public static void main(String[] args) throws Exception {
        testACRequest();
        testACAnswer();
    }
}
