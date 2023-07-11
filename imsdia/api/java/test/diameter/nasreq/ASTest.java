package diameter.nasreq;

import com.intellinet.diameter.*;
import diameter.*;

public class ASTest {

    public static void testASRequest() throws Exception {
        ASRequest aSRequest = new ASRequest(false, false);
        aSRequest.setSessionId(new diameter.base.SessionId("utf8string-2130310777"));
        aSRequest.setOriginHost(new diameter.base.OriginHost("id-1264645487.diameter.com"));
        aSRequest.setOriginRealm(new diameter.base.OriginRealm("id-671905710.diameter.com"));
        aSRequest.setDestinationRealm(new diameter.base.DestinationRealm("id2094280831.diameter.com"));
        aSRequest.setDestinationHost(new diameter.base.DestinationHost("id-250066134.diameter.com"));
        aSRequest.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(898189360)));
        aSRequest.setUserName(new diameter.base.UserName("utf8string318346452"));
        aSRequest.setOriginAAAProtocol(new OriginAAAProtocol(OriginAAAProtocol.Value.RADIUS));
        aSRequest.setOriginStateId(new diameter.base.OriginStateId(new Integer(1018934580)));
        aSRequest.setNASIdentifier(new NASIdentifier("utf8string706417149"));
        aSRequest.setNASIPAddress(new NASIPAddress("octetstring1110831502"));
        aSRequest.setNASIPv6Address(new NASIPv6Address("octetstring-1779153449"));
        aSRequest.setNASPort(new NASPort(new Integer(-1659132467)));
        aSRequest.setNASPortId(new NASPortId("utf8string2114060549"));
        aSRequest.setNASPortType(new NASPortType(NASPortType.Value.G_3_Fax));
        aSRequest.setServiceType(new ServiceType(ServiceType.Value.AUTHORIZE_ONLY));
        aSRequest.setFramedIPAddress(new FramedIPAddress("octetstring1286957174"));
        aSRequest.setFramedIPv6Prefix(new FramedIPv6Prefix("octetstring-34004997"));
        aSRequest.setFramedInterfaceId(new FramedInterfaceId(new Long(-2444271694337926086L)));
        aSRequest.setCalledStationId(new CalledStationId("utf8string491351099"));
        aSRequest.setCallingStationId(new CallingStationId("utf8string-165693605"));
        aSRequest.setOriginatingLineInfo(new OriginatingLineInfo("octetstring-2053108725"));
        aSRequest.setAcctSessionId(new diameter.base.AcctSessionId("octetstring273323157"));
        aSRequest.setAcctMultiSessionId(new diameter.base.AcctMultiSessionId("utf8string1827481892"));
        aSRequest.setState(new State("octetstring-1112655918"));
        aSRequest.addClass(new diameter.base.Class("octetstring965804452"));
        aSRequest.addReplyMessage(new ReplyMessage("utf8string-1325867651"));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id1817274608.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-433789220"));
            // add more AVP as ANY values to proxyInfo
            aSRequest.addProxyInfo(proxyInfo);
        }
        aSRequest.addRouteRecord(new diameter.base.RouteRecord("id1677638778.diameter.com"));
        // add more AVP as ANY values to aSRequest

        byte[] buffer = aSRequest.encode();
        ASRequest aSRequest2 = new ASRequest(buffer);
        String s1 = aSRequest.toString();
        String s2 = aSRequest2.toString();
        if (!s1.equals(s2)) {
            System.err.println("aSRequest1 = " + s1);
            System.err.println("aSRequest2 = " + s2);
            throw new VerificationException("ASRequest encoding/decoding failure");
        }
    }

    public static void testASAnswer() throws Exception {
        ASAnswer aSAnswer = new ASAnswer(false, false);
        aSAnswer.setSessionId(new diameter.base.SessionId("utf8string-1656889372"));
        aSAnswer.setResultCode(new diameter.base.ResultCode(new Integer(156755717)));
        aSAnswer.setOriginHost(new diameter.base.OriginHost("id-1750715985.diameter.com"));
        aSAnswer.setOriginRealm(new diameter.base.OriginRealm("id691833469.diameter.com"));
        aSAnswer.setUserName(new diameter.base.UserName("utf8string-1824396038"));
        aSAnswer.setOriginAAAProtocol(new OriginAAAProtocol(OriginAAAProtocol.Value.RADIUS));
        aSAnswer.setOriginStateId(new diameter.base.OriginStateId(new Integer(1927858775)));
        aSAnswer.setState(new State("octetstring927866890"));
        aSAnswer.setErrorMessage(new diameter.base.ErrorMessage("utf8string-679077389"));
        aSAnswer.setErrorReportingHost(new diameter.base.ErrorReportingHost("id1893025366.diameter.com"));
        aSAnswer.addRedirectHost(new diameter.base.RedirectHost(new URI("domain692843297.com", URI.Scheme.AAAS, (short)2432, URI.Transport.TCP, URI.Protocol.DIAMETER)));
        aSAnswer.setRedirectHostUsage(new diameter.base.RedirectHostUsage(diameter.base.RedirectHostUsage.Value.ALL_HOST));
        aSAnswer.setRedirectMaxCacheTime(new diameter.base.RedirectMaxCacheTime(new Integer(903383988)));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-1889887171.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-689823213"));
            // add more AVP as ANY values to proxyInfo
            aSAnswer.addProxyInfo(proxyInfo);
        }
        // add more AVP as ANY values to aSAnswer

        byte[] buffer = aSAnswer.encode();
        ASAnswer aSAnswer2 = new ASAnswer(buffer);
        String s1 = aSAnswer.toString();
        String s2 = aSAnswer2.toString();
        if (!s1.equals(s2)) {
            System.err.println("aSAnswer1 = " + s1);
            System.err.println("aSAnswer2 = " + s2);
            throw new VerificationException("ASAnswer encoding/decoding failure");
        }
    }

    public static void main(String[] args) throws Exception {
        testASRequest();
        testASAnswer();
    }
}
