package diameter.dcca;

import com.intellinet.diameter.*;


/**
 * CC-Request-Type AVP is of type enumerated and contains the reason for sending the Credit-
 * Control request message.
 */
public class CCRequestType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        INITIAL_REQUEST(1),
        UPDATE_REQUEST(2),
        TERMINATION_REQUEST(3),
        EVENT_REQUEST(4);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a CCRequestType with the given value.
     *
     * @param value - the value of the AVP
     */
    public CCRequestType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    CCRequestType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
