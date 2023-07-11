package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The PoC-Change-Time AVP (AVP code 1262) is of type Time and is a time 
 * stamp that defines the moment when a container is closed or the CDR is closed
 */
public class PoCChangeTime extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a PoCChangeTime with the given value.
     *
     * @param value - the value of the AVP
     */
    public PoCChangeTime(Integer value) {
        super(new com.intellinet.diameter.TimeData(value));
    }

    PoCChangeTime(com.intellinet.diameter.TimeData data) {
        super(data);
    }
}
