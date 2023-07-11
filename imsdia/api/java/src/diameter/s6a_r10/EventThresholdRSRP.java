package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class EventThresholdRSRP extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a EventThresholdRSRP with the given value.
     *
     * @param value - the value of the AVP
     */
    public EventThresholdRSRP(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    EventThresholdRSRP(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
