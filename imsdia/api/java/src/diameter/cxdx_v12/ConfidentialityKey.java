package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The Confidentiality-Key is of type OctetString, and contains the Confidentiality Key (CK).
 */
public class ConfidentialityKey extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ConfidentialityKey with the given value.
     *
     * @param value - the value of the AVP
     */
    public ConfidentialityKey(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    ConfidentialityKey(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
