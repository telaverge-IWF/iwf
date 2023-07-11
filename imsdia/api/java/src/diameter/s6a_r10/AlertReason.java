package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class AlertReason extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        UE_PRESENT(0),
        UE_MEMORY_AVAILABLE(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a AlertReason with the given value.
     *
     * @param value - the value of the AVP
     */
    public AlertReason(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    AlertReason(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
