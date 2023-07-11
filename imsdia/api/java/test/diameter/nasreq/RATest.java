package diameter.nasreq;

import com.intellinet.diameter.*;
import diameter.*;

public class RATest {

    public static void testRARequest() throws Exception {
        RARequest rARequest = new RARequest(false, false);
        rARequest.setSessionId(new diameter.base.SessionId("utf8string462066231"));
        rARequest.setOriginHost(new diameter.base.OriginHost("id-2015270923.diameter.com"));
        rARequest.setOriginRealm(new diameter.base.OriginRealm("id-1588308234.diameter.com"));
        rARequest.setDestinationRealm(new diameter.base.DestinationRealm("id596713368.diameter.com"));
        rARequest.setDestinationHost(new diameter.base.DestinationHost("id1255815938.diameter.com"));
        rARequest.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(1424732660)));
        rARequest.setReAuthRequestType(new diameter.base.ReAuthRequestType(diameter.base.ReAuthRequestType.Value.AUTHORIZE_ONLY));
        rARequest.setUserName(new diameter.base.UserName("utf8string-401288672"));
        rARequest.setOriginAAAProtocol(new OriginAAAProtocol(OriginAAAProtocol.Value.RADIUS));
        rARequest.setOriginStateId(new diameter.base.OriginStateId(new Integer(2083783860)));
        rARequest.setNASIdentifier(new NASIdentifier("utf8string261939721"));
        rARequest.setNASIPAddress(new NASIPAddress("octetstring1522817005"));
        rARequest.setNASIPv6Address(new NASIPv6Address("octetstring-1204350416"));
        rARequest.setNASPort(new NASPort(new Integer(996422787)));
        rARequest.setNASPortId(new NASPortId("utf8string1643912334"));
        rARequest.setNASPortType(new NASPortType(NASPortType.Value.SDSL));
        rARequest.setServiceType(new ServiceType(ServiceType.Value.LOGIN));
        rARequest.setFramedIPAddress(new FramedIPAddress("octetstring1995169402"));
        rARequest.setFramedIPv6Prefix(new FramedIPv6Prefix("octetstring869033884"));
        rARequest.setFramedInterfaceId(new FramedInterfaceId(new Long(2661845594356124374L)));
        rARequest.setCalledStationId(new CalledStationId("utf8string1826481578"));
        rARequest.setCallingStationId(new CallingStationId("utf8string217758890"));
        rARequest.setOriginatingLineInfo(new OriginatingLineInfo("octetstring-1132143707"));
        rARequest.setAcctSessionId(new diameter.base.AcctSessionId("octetstring949565632"));
        rARequest.setAcctMultiSessionId(new diameter.base.AcctMultiSessionId("utf8string2014056340"));
        rARequest.setState(new State("octetstring-1439075825"));
        rARequest.addClass(new diameter.base.Class("octetstring1604268772"));
        rARequest.setReplyMessage(new ReplyMessage("utf8string1027778464"));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id333149150.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-1933606236"));
            // add more AVP as ANY values to proxyInfo
            rARequest.addProxyInfo(proxyInfo);
        }
        rARequest.addRouteRecord(new diameter.base.RouteRecord("id-906596919.diameter.com"));
        // add more AVP as ANY values to rARequest

        byte[] buffer = rARequest.encode();
        RARequest rARequest2 = new RARequest(buffer);
        String s1 = rARequest.toString();
        String s2 = rARequest2.toString();
        if (!s1.equals(s2)) {
            System.err.println("rARequest1 = " + s1);
            System.err.println("rARequest2 = " + s2);
            throw new VerificationException("RARequest encoding/decoding failure");
        }
    }

    public static void testRAAnswer() throws Exception {
        RAAnswer rAAnswer = new RAAnswer(false, false);
        rAAnswer.setSessionId(new diameter.base.SessionId("utf8string577515706"));
        rAAnswer.setResultCode(new diameter.base.ResultCode(new Integer(-775703740)));
        rAAnswer.setOriginHost(new diameter.base.OriginHost("id230828967.diameter.com"));
        rAAnswer.setOriginRealm(new diameter.base.OriginRealm("id1072582901.diameter.com"));
        rAAnswer.setUserName(new diameter.base.UserName("utf8string1127606209"));
        rAAnswer.setOriginAAAProtocol(new OriginAAAProtocol(OriginAAAProtocol.Value.RADIUS));
        rAAnswer.setOriginStateId(new diameter.base.OriginStateId(new Integer(-363854622)));
        rAAnswer.setErrorMessage(new diameter.base.ErrorMessage("utf8string1807836002"));
        rAAnswer.setErrorReportingHost(new diameter.base.ErrorReportingHost("id-1790482019.diameter.com"));
        rAAnswer.addRedirectHost(new diameter.base.RedirectHost(new URI("domain1909035069.com", URI.Scheme.AAAS, (short)30475, URI.Transport.TCP, URI.Protocol.DIAMETER)));
        rAAnswer.setRedirectHostUsage(new diameter.base.RedirectHostUsage(diameter.base.RedirectHostUsage.Value.ALL_HOST));
        rAAnswer.setRedirectMaxCacheTime(new diameter.base.RedirectMaxCacheTime(new Integer(1005441902)));
        rAAnswer.setServiceType(new ServiceType(ServiceType.Value.CALLBACK_NAS_PROMPT));
        rAAnswer.addConfigurationToken(new ConfigurationToken("octetstring-227494802"));
        rAAnswer.setIdleTimeout(new IdleTimeout(new Integer(-332499328)));
        rAAnswer.setAuthorizationLifetime(new diameter.base.AuthorizationLifetime(new Integer(-1133271601)));
        rAAnswer.setAuthGracePeriod(new diameter.base.AuthGracePeriod(new Integer(1771213609)));
        rAAnswer.setReAuthRequestType(new diameter.base.ReAuthRequestType(diameter.base.ReAuthRequestType.Value.AUTHORIZE_AUTHENTICATE));
        rAAnswer.setState(new State("octetstring1933702254"));
        rAAnswer.addClass(new diameter.base.Class("octetstring-1057154978"));
        rAAnswer.addReplyMessage(new ReplyMessage("utf8string1326973824"));
        rAAnswer.setPrompt(new Prompt(Prompt.Value.ECHO));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-1563461755.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-2099797636"));
            // add more AVP as ANY values to proxyInfo
            rAAnswer.addProxyInfo(proxyInfo);
        }
        // add more AVP as ANY values to rAAnswer

        byte[] buffer = rAAnswer.encode();
        RAAnswer rAAnswer2 = new RAAnswer(buffer);
        String s1 = rAAnswer.toString();
        String s2 = rAAnswer2.toString();
        if (!s1.equals(s2)) {
            System.err.println("rAAnswer1 = " + s1);
            System.err.println("rAAnswer2 = " + s2);
            throw new VerificationException("RAAnswer encoding/decoding failure");
        }
    }

    public static void main(String[] args) throws Exception {
        testRARequest();
        testRAAnswer();
    }
}
