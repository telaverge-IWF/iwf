package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;
import diameter.*;

public class ReAuthTest {

    public static void testReAuthRequest() throws Exception {
        ReAuthRequest reAuthRequest = new ReAuthRequest(false, false);
        reAuthRequest.setSessionId(new diameter.base.SessionId("utf8string1247616522"));
        reAuthRequest.setOriginHost(new diameter.base.OriginHost("id1082763916.diameter.com"));
        reAuthRequest.setOriginRealm(new diameter.base.OriginRealm("id475761960.diameter.com"));
        reAuthRequest.setDestinationRealm(new diameter.base.DestinationRealm("id-804449342.diameter.com"));
        reAuthRequest.setDestinationHost(new diameter.base.DestinationHost("id1614094577.diameter.com"));
        reAuthRequest.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-98389491)));
        reAuthRequest.setReAuthRequestType(new diameter.base.ReAuthRequestType(diameter.base.ReAuthRequestType.Value.AUTHORIZE_ONLY));
        reAuthRequest.setUserName(new diameter.base.UserName("utf8string703867084"));
        reAuthRequest.setOriginStateId(new diameter.base.OriginStateId(new Integer(-594578417)));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id269554862.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring1481663232"));
            // add more AVP as ANY values to proxyInfo
            reAuthRequest.addProxyInfo(proxyInfo);
        }
        reAuthRequest.addRouteRecord(new diameter.base.RouteRecord("id1031993076.diameter.com"));
        reAuthRequest.setGSUPoolIdentifier(new GSUPoolIdentifier(new Integer(-1573914129)));
        reAuthRequest.setServiceIdentifier(new ServiceIdentifier(new Integer(1275418736)));
        reAuthRequest.setRatingGroup(new RatingGroup(new Integer(1562012604)));
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
        reAuthAnswer.setSessionId(new diameter.base.SessionId("utf8string1302724964"));
        reAuthAnswer.setResultCode(new diameter.base.ResultCode(new Integer(-54587002)));
        reAuthAnswer.setOriginHost(new diameter.base.OriginHost("id-1622766683.diameter.com"));
        reAuthAnswer.setOriginRealm(new diameter.base.OriginRealm("id711317723.diameter.com"));
        reAuthAnswer.setUserName(new diameter.base.UserName("utf8string1181931189"));
        reAuthAnswer.setOriginStateId(new diameter.base.OriginStateId(new Integer(135490439)));
        reAuthAnswer.setErrorMessage(new diameter.base.ErrorMessage("utf8string-197422669"));
        reAuthAnswer.setErrorReportingHost(new diameter.base.ErrorReportingHost("id-1273521463.diameter.com"));
        reAuthAnswer.addRedirectHost(new diameter.base.RedirectHost(new URI("domain-1527237300.com", URI.Scheme.AAAS, (short)24821, URI.Transport.TCP, URI.Protocol.DIAMETER)));
        reAuthAnswer.setRedirectHostUsage(new diameter.base.RedirectHostUsage(diameter.base.RedirectHostUsage.Value.ALL_SESSION));
        reAuthAnswer.setRedirectMaxCacheTime(new diameter.base.RedirectMaxCacheTime(new Integer(1512822727)));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-691957248.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-1191403783"));
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
