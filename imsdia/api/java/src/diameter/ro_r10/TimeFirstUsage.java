package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Time-First-Usage  AVP (AVP code 2043) is of type Time and holds the 
 * time in UTC format for the first IP packet to be transmitted and mapped to 
 * the current service data container.
 */
public class TimeFirstUsage extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a TimeFirstUsage with the given value.
     *
     * @param value - the value of the AVP
     */
    public TimeFirstUsage(Integer value) {
        super(new com.intellinet.diameter.TimeData(value));
    }

    TimeFirstUsage(com.intellinet.diameter.TimeData data) {
        super(data);
    }
}
