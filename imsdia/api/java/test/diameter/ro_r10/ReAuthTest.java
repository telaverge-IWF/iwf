package diameter.ro_r10;

import com.intellinet.diameter.*;
import diameter.*;

public class ReAuthTest {

    public static void testReAuthRequest() throws Exception {
        ReAuthRequest reAuthRequest = new ReAuthRequest(false, false);
        reAuthRequest.setSessionId(new diameter.base.SessionId("utf8string-290033731"));
        reAuthRequest.setOriginHost(new diameter.base.OriginHost("id116330128.diameter.com"));
        reAuthRequest.setOriginRealm(new diameter.base.OriginRealm("id1849968988.diameter.com"));
        reAuthRequest.setDestinationRealm(new diameter.base.DestinationRealm("id-1263473549.diameter.com"));
        reAuthRequest.setDestinationHost(new diameter.base.DestinationHost("id-117626779.diameter.com"));
        reAuthRequest.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(389515042)));
        reAuthRequest.setReAuthRequestType(new diameter.base.ReAuthRequestType(diameter.base.ReAuthRequestType.Value.AUTHORIZE_AUTHENTICATE));
        reAuthRequest.setUserName(new diameter.base.UserName("utf8string-27183283"));
        reAuthRequest.setOriginStateId(new diameter.base.OriginStateId(new Integer(-1467961822)));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id136653557.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-364353038"));
            // add more AVP as ANY values to proxyInfo
            reAuthRequest.addProxyInfo(proxyInfo);
        }
        reAuthRequest.addRouteRecord(new diameter.base.RouteRecord("id1577635821.diameter.com"));
        reAuthRequest.setGSUPoolIdentifier(new GSUPoolIdentifier(new Integer(-256357010)));
        reAuthRequest.setServiceIdentifier(new ServiceIdentifier(new Integer(-615689014)));
        reAuthRequest.setRatingGroup(new RatingGroup(new Integer(-2055752529)));
        // add more AVP as ANY values to reAuthRequest

        byte[] buffer = reAuthRequest.encode();
        ReAuthRequest reAuthRequest2 = new ReAuthRequest(buffer);
        String s1 = reAuthRequest.toString();
        String s2 = reAuthRequest2.toString();
        if (!s1.equals(s2)) {
            System.err.println("reAuthRequest1 = " + s1);
            System.err.println("reAuthRequest2 = " + s2);
            throw new VerificationException("ReAuthRequest encoding/decoding failure");
        }
    }

    public static void testReAuthAnswer() throws Exception {
        ReAuthAnswer reAuthAnswer = new ReAuthAnswer(false, false);
        reAuthAnswer.setSessionId(new diameter.base.SessionId("utf8string-656467076"));
        reAuthAnswer.setResultCode(new diameter.base.ResultCode(new Integer(463085340)));
        reAuthAnswer.setOriginHost(new diameter.base.OriginHost("id1503760616.diameter.com"));
        reAuthAnswer.setOriginRealm(new diameter.base.OriginRealm("id1151205812.diameter.com"));
        reAuthAnswer.setUserName(new diameter.base.UserName("utf8string-1879912643"));
        reAuthAnswer.setOriginStateId(new diameter.base.OriginStateId(new Integer(-1686901584)));
        reAuthAnswer.setErrorMessage(new diameter.base.ErrorMessage("utf8string-1621340969"));
        reAuthAnswer.setErrorReportingHost(new diameter.base.ErrorReportingHost("id319915093.diameter.com"));
        reAuthAnswer.addRedirectHost(new diameter.base.RedirectHost(new URI("domain479965167.com", URI.Scheme.AAAS, (short)1514, URI.Transport.TCP, URI.Protocol.DIAMETER)));
        reAuthAnswer.setRedirectHostUsage(new diameter.base.RedirectHostUsage(diameter.base.RedirectHostUsage.Value.DONT_CACHE));
        reAuthAnswer.setRedirectMaxCacheTime(new diameter.base.RedirectMaxCacheTime(new Integer(-1478783704)));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id1262379893.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-1396548700"));
            // add more AVP as ANY values to proxyInfo
            reAuthAnswer.addProxyInfo(proxyInfo);
        }
        // add more AVP as ANY values to reAuthAnswer

        byte[] buffer = reAuthAnswer.encode();
        ReAuthAnswer reAuthAnswer2 = new ReAuthAnswer(buffer);
        String s1 = reAuthAnswer.toString();
        String s2 = reAuthAnswer2.toString();
        if (!s1.equals(s2)) {
            System.err.println("reAuthAnswer1 = " + s1);
            System.err.println("reAuthAnswer2 = " + s2);
            throw new VerificationException("ReAuthAnswer encoding/decoding failure");
        }
    }

    public static void main(String[] args) throws Exception {
        testReAuthRequest();
        testReAuthAnswer();
    }
}
