package diameter.cxdx_v12;

import com.intellinet.diameter.*;


public class OriginatingRequest extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        ORIGINATING(0);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a OriginatingRequest with the given value.
     *
     * @param value - the value of the AVP
     */
    public OriginatingRequest(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    OriginatingRequest(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
