package diameter.cxdx_v12;

import com.intellinet.diameter.*;


public class MultipleRegistrationIndication extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        NOT_MULTIPLE_REGISTRATION(0),
        MULTIPLE_REGISTRATION(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a MultipleRegistrationIndication with the given value.
     *
     * @param value - the value of the AVP
     */
    public MultipleRegistrationIndication(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    MultipleRegistrationIndication(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
