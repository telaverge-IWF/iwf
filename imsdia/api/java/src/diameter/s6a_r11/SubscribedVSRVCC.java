package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class SubscribedVSRVCC extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        VSRVCC_SUBSCRIBED(0);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a SubscribedVSRVCC with the given value.
     *
     * @param value - the value of the AVP
     */
    public SubscribedVSRVCC(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    SubscribedVSRVCC(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
