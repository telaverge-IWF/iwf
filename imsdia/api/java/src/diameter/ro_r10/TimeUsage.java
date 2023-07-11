package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Time-Usage  AVP (AVP code 2045) is of type Time and holds the effective 
 * used time within the service data container reporting interval.
 */
public class TimeUsage extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a TimeUsage with the given value.
     *
     * @param value - the value of the AVP
     */
    public TimeUsage(Integer value) {
        super(new com.intellinet.diameter.TimeData(value));
    }

    TimeUsage(com.intellinet.diameter.TimeData data) {
        super(data);
    }
}
