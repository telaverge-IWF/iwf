package diameter.ro_r10;

import com.intellinet.diameter.*;


public class StopTime extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a StopTime with the given value.
     *
     * @param value - the value of the AVP
     */
    public StopTime(Integer value) {
        super(new com.intellinet.diameter.TimeData(value));
    }

    StopTime(com.intellinet.diameter.TimeData data) {
        super(data);
    }
}
