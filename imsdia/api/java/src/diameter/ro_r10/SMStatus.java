package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The SM-Status AVP (AVP code 2014) is of type OctetString. The OctetString 
 * is of length 1 octet and contains status information about the delivery of an SM.
 */
public class SMStatus extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a SMStatus with the given value.
     *
     * @param value - the value of the AVP
     */
    public SMStatus(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    SMStatus(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
