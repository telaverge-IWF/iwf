package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class MDTUserConsent extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        CONSENT_NOT_GIVEN(0),
        CONSENT_GIVEN(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a MDTUserConsent with the given value.
     *
     * @param value - the value of the AVP
     */
    public MDTUserConsent(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    MDTUserConsent(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
