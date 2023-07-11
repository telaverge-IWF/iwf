package diameter.s6a_r10;

import com.intellinet.diameter.*;


/**
 * The SRES AVP is of type OctetString. This AVP contains the SRES. See 3GPP TS 33.102 [xx].
 */
public class SRES extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a SRES with the given value.
     *
     * @param value - the value of the AVP
     */
    public SRES(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    SRES(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
