package diameter.s6a;

import com.intellinet.diameter.*;


/**
 * The KASME AVP is of type OctetString. This AVP contains the K_ASME. See 3GPP TS 33.401[5].
 */
public class KASME extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a KASME with the given value.
     *
     * @param value - the value of the AVP
     */
    public KASME(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    KASME(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
