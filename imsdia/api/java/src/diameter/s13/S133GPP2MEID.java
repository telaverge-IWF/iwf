package diameter.s13;

import com.intellinet.diameter.*;


/**
 * The 3GPP2-MEID AVP is of type OctetString. This AVP contains the Mobile Equipment
 * Identity of the user's terminal. See 3GPP2 A.S0022 Annex A.
 */
public class S133GPP2MEID extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a S133GPP2MEID with the given value.
     *
     * @param value - the value of the AVP
     */
    public S133GPP2MEID(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    S133GPP2MEID(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
