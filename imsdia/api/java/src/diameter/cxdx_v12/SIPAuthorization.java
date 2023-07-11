package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The SIP-Authorization AVP is of type OctetString and contains specific parts of the data portion of the Authorization or
 * Proxy-Authorization SIP headers suitable for inclusion in a SIP request. The identification and encoding of the specific
 * parts are defined in 3GPP TS 29.228.
 */
public class SIPAuthorization extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a SIPAuthorization with the given value.
     *
     * @param value - the value of the AVP
     */
    public SIPAuthorization(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    SIPAuthorization(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
