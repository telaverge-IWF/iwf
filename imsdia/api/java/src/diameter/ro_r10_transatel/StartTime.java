package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


public class StartTime extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a StartTime with the given value.
     *
     * @param value - the value of the AVP
     */
    public StartTime(Integer value) {
        super(new com.intellinet.diameter.TimeData(value));
    }

    StartTime(com.intellinet.diameter.TimeData data) {
        super(data);
    }
}
