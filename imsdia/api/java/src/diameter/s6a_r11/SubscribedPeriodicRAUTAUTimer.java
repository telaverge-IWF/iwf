package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class SubscribedPeriodicRAUTAUTimer extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a SubscribedPeriodicRAUTAUTimer with the given value.
     *
     * @param value - the value of the AVP
     */
    public SubscribedPeriodicRAUTAUTimer(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    SubscribedPeriodicRAUTAUTimer(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
