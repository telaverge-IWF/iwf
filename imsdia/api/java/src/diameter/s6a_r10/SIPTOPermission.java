package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class SIPTOPermission extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        SIPTO_ALLOWED(0),
        SIPTO_NOTALLOWED(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a SIPTOPermission with the given value.
     *
     * @param value - the value of the AVP
     */
    public SIPTOPermission(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    SIPTOPermission(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
