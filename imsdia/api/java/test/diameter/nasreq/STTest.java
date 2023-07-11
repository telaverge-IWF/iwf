package diameter.nasreq;

import com.intellinet.diameter.*;
import diameter.*;

public class STTest {

    public static void testSTRequest() throws Exception {
        STRequest sTRequest = new STRequest(false, false);
        sTRequest.setSessionId(new diameter.base.SessionId("utf8string1377671794"));
        sTRequest.setOriginHost(new diameter.base.OriginHost("id-9469450.diameter.com"));
        sTRequest.setOriginRealm(new diameter.base.OriginRealm("id1885232822.diameter.com"));
        sTRequest.setDestinationRealm(new diameter.base.DestinationRealm("id-787355511.diameter.com"));
        sTRequest.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(351475023)));
        sTRequest.setTerminationCause(new diameter.base.TerminationCause(diameter.base.TerminationCause.Value.DIAMETER_BAD_ANSWER));
        sTRequest.setUserName(new diameter.base.UserName("utf8string628609666"));
        sTRequest.setDestinationHost(new diameter.base.DestinationHost("id553554370.diameter.com"));
        sTRequest.addClass(new diameter.base.Class("octetstring1928809985"));
        sTRequest.setOriginAAAProtocol(new OriginAAAProtocol(OriginAAAProtocol.Value.RADIUS));
        sTRequest.setOriginStateId(new diameter.base.OriginStateId(new Integer(-1772162412)));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id1189274287.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring880941513"));
            // add more AVP as ANY values to proxyInfo
            sTRequest.addProxyInfo(proxyInfo);
        }
        sTRequest.addRouteRecord(new diameter.base.RouteRecord("id-1441894458.diameter.com"));
        // add more AVP as ANY values to sTRequest

        byte[] buffer = sTRequest.encode();
        STRequest sTRequest2 = new STRequest(buffer);
        String s1 = sTRequest.toString();
        String s2 = sTRequest2.toString();
        if (!s1.equals(s2)) {
            System.err.println("sTRequest1 = " + s1);
            System.err.println("sTRequest2 = " + s2);
            throw new VerificationException("STRequest encoding/decoding failure");
        }
    }

    public static void testSTAnswer() throws Exception {
        STAnswer sTAnswer = new STAnswer(false, false);
        sTAnswer.setSessionId(new diameter.base.SessionId("utf8string-1234291615"));
        sTAnswer.setResultCode(new diameter.base.ResultCode(new Integer(2082457538)));
        sTAnswer.setOriginHost(new diameter.base.OriginHost("id772784527.diameter.com"));
        sTAnswer.setOriginRealm(new diameter.base.OriginRealm("id-870439375.diameter.com"));
        sTAnswer.setUserName(new diameter.base.UserName("utf8string1089477194"));
        sTAnswer.addClass(new diameter.base.Class("octetstring-247068395"));
        sTAnswer.setErrorMessage(new diameter.base.ErrorMessage("utf8string-682947782"));
        sTAnswer.setErrorReportingHost(new diameter.base.ErrorReportingHost("id1706693231.diameter.com"));
        sTAnswer.setOriginAAAProtocol(new OriginAAAProtocol(OriginAAAProtocol.Value.RADIUS));
        sTAnswer.setOriginStateId(new diameter.base.OriginStateId(new Integer(-1466223917)));
        sTAnswer.addRedirectHost(new diameter.base.RedirectHost(new URI("domain-1298267071.com", URI.Scheme.AAAS, (short)20322, URI.Transport.TCP, URI.Protocol.DIAMETER)));
        sTAnswer.setRedirectHostUsage(new diameter.base.RedirectHostUsage(diameter.base.RedirectHostUsage.Value.ALL_USER));
        sTAnswer.setRedirectMaxCacheTime(new diameter.base.RedirectMaxCacheTime(new Integer(-1202053162)));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-2039717502.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-613075576"));
            // add more AVP as ANY values to proxyInfo
            sTAnswer.addProxyInfo(proxyInfo);
        }
        // add more AVP as ANY values to sTAnswer

        byte[] buffer = sTAnswer.encode();
        STAnswer sTAnswer2 = new STAnswer(buffer);
        String s1 = sTAnswer.toString();
        String s2 = sTAnswer2.toString();
        if (!s1.equals(s2)) {
            System.err.println("sTAnswer1 = " + s1);
            System.err.println("sTAnswer2 = " + s2);
            throw new VerificationException("STAnswer encoding/decoding failure");
        }
    }

    public static void main(String[] args) throws Exception {
        testSTRequest();
        testSTAnswer();
    }
}
