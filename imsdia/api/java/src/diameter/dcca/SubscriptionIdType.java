package diameter.dcca;

import com.intellinet.diameter.*;


/**
 * Subscription-Id-Type AVP is of type Enumerated and it is used to determine which type of
 * identifier is carried by the Subscription-Id AVP.
 */
public class SubscriptionIdType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        END_USER_E164(0),
        END_USER_IMSI(1),
        END_USER_SIP_URI(2),
        END_USER_NAI(3),
        END_USER_PRIVATE(4);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a SubscriptionIdType with the given value.
     *
     * @param value - the value of the AVP
     */
    public SubscriptionIdType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    SubscriptionIdType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
