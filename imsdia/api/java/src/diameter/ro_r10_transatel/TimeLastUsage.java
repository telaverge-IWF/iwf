package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Time-Last-Usage  AVP (AVP code 2044) is of type Time and holds the time 
 * in UTC format for the last  IP packet to be transmitted and mapped to the 
 * current service data container.
 */
public class TimeLastUsage extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a TimeLastUsage with the given value.
     *
     * @param value - the value of the AVP
     */
    public TimeLastUsage(Integer value) {
        super(new com.intellinet.diameter.TimeData(value));
    }

    TimeLastUsage(com.intellinet.diameter.TimeData data) {
        super(data);
    }
}
