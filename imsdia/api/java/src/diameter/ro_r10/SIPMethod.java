package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * SIP-Method AVP is of type UTF8String and holds the name of the SIP Method (INVITE,UPDATE,etc)
 * causing an accounting request to be sent to the CDF.
 */
public class SIPMethod extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a SIPMethod with the given value.
     *
     * @param value - the value of the AVP
     */
    public SIPMethod(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    SIPMethod(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
