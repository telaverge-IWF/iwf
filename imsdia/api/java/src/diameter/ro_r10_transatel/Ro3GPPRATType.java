package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * 3GPP-RAT-Type AVP is of type OctetString. It indicates which Radio Access Technology is 
 * currently serving the UE.
 */
public class Ro3GPPRATType extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a Ro3GPPRATType with the given value.
     *
     * @param value - the value of the AVP
     */
    public Ro3GPPRATType(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    Ro3GPPRATType(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
