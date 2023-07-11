package diameter.dcca;

import com.intellinet.diameter.*;
import diameter.*;

public class RATest {

    public static void testRARequest() throws Exception {
        RARequest rARequest = new RARequest(false, false);
        rARequest.setSessionId(new diameter.base.SessionId("utf8string1325196771"));
        rARequest.setOriginHost(new diameter.base.OriginHost("id382142964.diameter.com"));
        rARequest.setOriginRealm(new diameter.base.OriginRealm("id-135066738.diameter.com"));
        rARequest.setDestinationRealm(new diameter.base.DestinationRealm("id1035590733.diameter.com"));
        rARequest.setDestinationHost(new diameter.base.DestinationHost("id651389947.diameter.com"));
        rARequest.setAuthApplicationId(new diameter.base.AuthApplicationId(new Integer(-1993834419)));
        rARequest.setReAuthRequestType(new diameter.base.ReAuthRequestType(diameter.base.ReAuthRequestType.Value.AUTHORIZE_AUTHENTICATE));
        rARequest.setUserName(new diameter.base.UserName("utf8string123074447"));
        rARequest.setOriginStateId(new diameter.base.OriginStateId(new Integer(-742926625)));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id2091802574.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring-1665223419"));
            // add more AVP as ANY values to proxyInfo
            rARequest.addProxyInfo(proxyInfo);
        }
        rARequest.addRouteRecord(new diameter.base.RouteRecord("id-14604656.diameter.com"));
        rARequest.setCCSubSessionId(new CCSubSessionId(new Long(373003712855073890L)));
        rARequest.setGSUPoolIdentifier(new GSUPoolIdentifier(new Integer(-1156095386)));
        rARequest.setServiceIdentifier(new ServiceIdentifier(new Integer(-419390324)));
        rARequest.setRatingGroup(new RatingGroup(new Integer(140055508)));
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
        rAAnswer.setSessionId(new diameter.base.SessionId("utf8string1248586856"));
        rAAnswer.setResultCode(new diameter.base.ResultCode(new Integer(-2114441432)));
        rAAnswer.setOriginHost(new diameter.base.OriginHost("id-349712960.diameter.com"));
        rAAnswer.setOriginRealm(new diameter.base.OriginRealm("id533993476.diameter.com"));
        rAAnswer.setUserName(new diameter.base.UserName("utf8string2100691420"));
        rAAnswer.setOriginStateId(new diameter.base.OriginStateId(new Integer(781305635)));
        rAAnswer.setErrorMessage(new diameter.base.ErrorMessage("utf8string1525061420"));
        rAAnswer.setErrorReportingHost(new diameter.base.ErrorReportingHost("id198882017.diameter.com"));
        rAAnswer.addRedirectHost(new diameter.base.RedirectHost(new URI("domain-1250143820.com", URI.Scheme.AAAS, (short)10740, URI.Transport.TCP, URI.Protocol.DIAMETER)));
        rAAnswer.setRedirectHostUsage(new diameter.base.RedirectHostUsage(diameter.base.RedirectHostUsage.Value.DONT_CACHE));
        rAAnswer.setRedirectMaxCacheTime(new diameter.base.RedirectMaxCacheTime(new Integer(1323549850)));
        {
            diameter.base.ProxyInfo proxyInfo = new diameter.base.ProxyInfo();
            proxyInfo.setProxyHost(new diameter.base.ProxyHost("id-60017268.diameter.com"));
            proxyInfo.setProxyState(new diameter.base.ProxyState("octetstring717037000"));
            // add more AVP as ANY values to proxyInfo
            rAAnswer.addProxyInfo(proxyInfo);
        }
        rAAnswer.setCCSubSessionId(new CCSubSessionId(new Long(6574744037725074710L)));
        rAAnswer.setGSUPoolIdentifier(new GSUPoolIdentifier(new Integer(-1759956092)));
        rAAnswer.setServiceIdentifier(new ServiceIdentifier(new Integer(-1648231557)));
        rAAnswer.setRatingGroup(new RatingGroup(new Integer(1327699038)));
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
