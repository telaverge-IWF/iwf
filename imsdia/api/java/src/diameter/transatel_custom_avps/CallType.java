package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CallType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        MO_VOICE(1),
        MT_VOICE(2),
        MO_SMS(3),
        MO_MMS(4),
        MT_FW(5),
        MO_FW(6),
        MT_SMS(7);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a CallType with the given value.
     *
     * @param value - the value of the AVP
     */
    public CallType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    CallType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
