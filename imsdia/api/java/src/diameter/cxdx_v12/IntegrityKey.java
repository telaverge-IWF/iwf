package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The Integrity-Key is of type OctetString, and contains the Integrity Key (IK).
 */
public class IntegrityKey extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a IntegrityKey with the given value.
     *
     * @param value - the value of the AVP
     */
    public IntegrityKey(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    IntegrityKey(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
