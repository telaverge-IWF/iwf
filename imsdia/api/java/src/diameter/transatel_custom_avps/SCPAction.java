package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class SCPAction extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        REJECT(11),
        CONTINUE(12),
        CONNECT(13),
        TRANSPARENT_FOLLOW_ON(14),
        FOLLOW_ON_CONTINUE(15),
        FOLLOW_ON_CONNECT(16);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a SCPAction with the given value.
     *
     * @param value - the value of the AVP
     */
    public SCPAction(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    SCPAction(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
