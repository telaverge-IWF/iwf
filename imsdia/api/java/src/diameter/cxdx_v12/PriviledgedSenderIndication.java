package diameter.cxdx_v12;

import com.intellinet.diameter.*;


public class PriviledgedSenderIndication extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        NOT_PRIVILEDGED_SENDER(0),
        PRIVILEDGED_SENDER(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a PriviledgedSenderIndication with the given value.
     *
     * @param value - the value of the AVP
     */
    public PriviledgedSenderIndication(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    PriviledgedSenderIndication(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
