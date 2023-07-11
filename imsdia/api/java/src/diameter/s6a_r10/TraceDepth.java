package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class TraceDepth extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        Minimum(0),
        Medium(1),
        Maximum(2),
        MinimumWithoutVendorSpecificExtension(3),
        MediumWithoutVendorSpecificExtension(4),
        MaximumWithoutVendorSpecificExtension(5);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a TraceDepth with the given value.
     *
     * @param value - the value of the AVP
     */
    public TraceDepth(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    TraceDepth(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
