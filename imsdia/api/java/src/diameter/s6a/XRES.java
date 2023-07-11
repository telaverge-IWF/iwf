package diameter.s6a;

import com.intellinet.diameter.*;


/** 
 * The XRES AVP is of type OctetString. This AVP contains the XRES. See 3GPP TS 33.401[5].
 */
public class XRES extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a XRES with the given value.
     *
     * @param value - the value of the AVP
     */
    public XRES(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    XRES(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
