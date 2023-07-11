package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The ARAP-Security AVP (AVP Code 74) is of type OctetString and MAY be
 * present in the AA-Request or AA-Answer message if the Framed-Protocol
 * AVP is set to the value of ARAP, and the Result-Code AVP is set to
 * DIAMETER_MULTI_ROUND_AUTH. This AVP contains the security module
 * challenge or response associated with the ARAP Security Module
 * specified in ARAP-Security.
 */
public class ARAPSecurityData extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ARAPSecurityData with the given value.
     *
     * @param value - the value of the AVP
     */
    public ARAPSecurityData(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    ARAPSecurityData(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
