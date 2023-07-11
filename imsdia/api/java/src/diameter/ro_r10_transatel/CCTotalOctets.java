package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The CC-Total-Octets AVP is of type Unsigned64 and contains the total number of requested,
 * granted, or used octets regardless of the direction (sent or received).
 */
public class CCTotalOctets extends com.intellinet.diameter.DerivedAVP<Long> {
    /**
     * Constructs a CCTotalOctets with the given value.
     *
     * @param value - the value of the AVP
     */
    public CCTotalOctets(Long value) {
        super(new com.intellinet.diameter.Unsigned64Data(value));
    }

    CCTotalOctets(com.intellinet.diameter.Unsigned64Data data) {
        super(data);
    }
}
