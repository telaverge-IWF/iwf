package diameter.cxdx_v12;

import com.intellinet.diameter.*;


public class SessionPriority extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        PRIORITY0(0),
        PRIORITY1(1),
        PRIORITY2(2),
        PRIORITY3(3),
        PRIORITY4(4);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a SessionPriority with the given value.
     *
     * @param value - the value of the AVP
     */
    public SessionPriority(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    SessionPriority(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
