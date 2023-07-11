package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The SIP-Authenticate AVP is of type OctetString and contains specific parts of the data portion of the WWWAuthenticate
 * or Proxy-Authenticate SIP headers that are to be present in a SIP response. The identification and
 * encoding of the specific parts are defined in 3GPP TS 29.228.
 */
public class SIPAuthenticate extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a SIPAuthenticate with the given value.
     *
     * @param value - the value of the AVP
     */
    public SIPAuthenticate(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    SIPAuthenticate(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
