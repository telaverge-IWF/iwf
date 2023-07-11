package diameter.s6a_r11;

import com.intellinet.diameter.*;


/**
 * The CK is of type OctetString, and contains the Confidentiality Key (CK).
 */
public class CK extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CK with the given value.
     *
     * @param value - the value of the AVP
     */
    public CK(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    CK(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
