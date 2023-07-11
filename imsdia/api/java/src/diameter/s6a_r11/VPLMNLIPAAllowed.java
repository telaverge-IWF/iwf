package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class VPLMNLIPAAllowed extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        LIPA_NOTALLOWED(0),
        LIPA_ALLOWED(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a VPLMNLIPAAllowed with the given value.
     *
     * @param value - the value of the AVP
     */
    public VPLMNLIPAAllowed(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    VPLMNLIPAAllowed(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
