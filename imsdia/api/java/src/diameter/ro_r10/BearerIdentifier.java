package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Bearer-Identifier AVP (AVP code 1020) is of type OctetString, and
 * it indicates the bearer to which specific information refers.
 */
public class BearerIdentifier extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a BearerIdentifier with the given value.
     *
     * @param value - the value of the AVP
     */
    public BearerIdentifier(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    BearerIdentifier(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
