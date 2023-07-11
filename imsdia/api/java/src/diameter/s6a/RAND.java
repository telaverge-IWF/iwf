package diameter.s6a;

import com.intellinet.diameter.*;


/**
 * The RAND AVP is of type OctetString. This AVP contains the RAND. See 3GPP TS 33.401[5].
 */
public class RAND extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a RAND with the given value.
     *
     * @param value - the value of the AVP
     */
    public RAND(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    RAND(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
