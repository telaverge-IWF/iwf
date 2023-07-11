package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The Authentication-Scheme AVP is of type UTF8String and indicates the authentication scheme used in the
 * authentication of SIP messages.
 */
public class SIPAuthenticationScheme extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a SIPAuthenticationScheme with the given value.
     *
     * @param value - the value of the AVP
     */
    public SIPAuthenticationScheme(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    SIPAuthenticationScheme(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
