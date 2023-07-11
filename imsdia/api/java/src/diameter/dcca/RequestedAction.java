package diameter.dcca;

import com.intellinet.diameter.*;


/**
 * Requested-Action AVP is of type Enumerated and contains the requested action being sent by 
 * Credit-Control-Request command where the CC-Request-Type is set to EVENT_REQUEST.
 */
public class RequestedAction extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        DIRECT_DEBITING(0),
        REFUND_ACCOUNT(1),
        CHECK_BALANCE(2),
        PRICE_ENQUIRY(3);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a RequestedAction with the given value.
     *
     * @param value - the value of the AVP
     */
    public RequestedAction(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    RequestedAction(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
