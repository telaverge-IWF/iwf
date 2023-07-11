package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Pre-emption-Capability AVP (AVP code 1047) is of type Enumerated.
 * The AVP defines whether a service data flow can get resources that were already assigned to
 * another service data flow with a lower priority level.
 */
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
