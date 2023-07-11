package diameter.s6a;

import com.intellinet.diameter.*;


public class PreemptionCapability extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        PRE_EMPTION_CAPABILITY_ENABLED(0),
        PRE_EMPTION_CAPABILITY_DISABLED(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a PreemptionCapability with the given value.
     *
     * @param value - the value of the AVP
     */
    public PreemptionCapability(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    PreemptionCapability(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
