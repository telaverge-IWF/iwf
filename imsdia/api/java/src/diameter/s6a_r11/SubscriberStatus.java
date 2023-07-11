package diameter.s6a_r11;

import com.intellinet.diameter.*;


/**
 * The 3GPP Subscriber Status AVP is of type Enumerated. It indicates if the service 
 * is barred or granted. The following values are defined:
 *	SERVICEGRANTED (0)
 *	OPERATORDETERMINEDBARRING (1)
 */
public class SubscriberStatus extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        SERVICEGRANTED(0),
        OPERATORDETERMINEDBARRING(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a SubscriberStatus with the given value.
     *
     * @param value - the value of the AVP
     */
    public SubscriberStatus(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    SubscriberStatus(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
