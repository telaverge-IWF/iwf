package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Session-Priority AVP is of type Enumerated and indicates to the HSS the session's priority.
 */
public class SessionPriority extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        PRIORITY_0(0),
        PRIORITY_1(1),
        PRIORITY_2(2),
        PRIORITY_3(3),
        PRIORITY_4(4);

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
