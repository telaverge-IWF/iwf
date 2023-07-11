package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class EventThresholdRSRQ extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a EventThresholdRSRQ with the given value.
     *
     * @param value - the value of the AVP
     */
    public EventThresholdRSRQ(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    EventThresholdRSRQ(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
