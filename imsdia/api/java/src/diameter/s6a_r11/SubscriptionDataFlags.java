package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class SubscriptionDataFlags extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a SubscriptionDataFlags with the given value.
     *
     * @param value - the value of the AVP
     */
    public SubscriptionDataFlags(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    SubscriptionDataFlags(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
