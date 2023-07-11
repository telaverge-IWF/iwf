package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class LIPAPermission extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        LIPA_PROHIBITED(0),
        LIPA_ONLY(1),
        LIPA_CONDITIONAL(2);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a LIPAPermission with the given value.
     *
     * @param value - the value of the AVP
     */
    public LIPAPermission(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    LIPAPermission(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
