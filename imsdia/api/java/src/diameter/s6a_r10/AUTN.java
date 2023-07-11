package diameter.s6a_r10;

import com.intellinet.diameter.*;


/**
 * The AUTN AVP is of type OctetString. This AVP contains the AUTN. See 3GPP TS 33.401[5].
 */
public class AUTN extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a AUTN with the given value.
     *
     * @param value - the value of the AVP
     */
    public AUTN(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    AUTN(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
