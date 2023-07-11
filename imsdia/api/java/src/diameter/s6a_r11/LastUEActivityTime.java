package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class LastUEActivityTime extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a LastUEActivityTime with the given value.
     *
     * @param value - the value of the AVP
     */
    public LastUEActivityTime(Integer value) {
        super(new com.intellinet.diameter.TimeData(value));
    }

    LastUEActivityTime(com.intellinet.diameter.TimeData data) {
        super(data);
    }
}
