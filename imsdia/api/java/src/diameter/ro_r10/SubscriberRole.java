package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Subscriber-Role  AVP (AVP code 2033) is of type Enumerated and 
 * indicates the role of the subscriber(originating party or terminating party)
 * in MMTel supplementary services. 
 */
public class SubscriberRole extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        ORIGINATING(0),
        TERMINATING(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a SubscriberRole with the given value.
     *
     * @param value - the value of the AVP
     */
    public SubscriberRole(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    SubscriberRole(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
