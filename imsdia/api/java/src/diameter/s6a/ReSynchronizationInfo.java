package diameter.s6a;

import com.intellinet.diameter.*;


/**
 * The Re-Synchronization-Info AVP is of type OctetString. 
 * It contains the concatenation of RAND and AUTS
*/
public class ReSynchronizationInfo extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ReSynchronizationInfo with the given value.
     *
     * @param value - the value of the AVP
     */
    public ReSynchronizationInfo(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    ReSynchronizationInfo(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
