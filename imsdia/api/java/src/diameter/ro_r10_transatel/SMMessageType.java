package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The SM-Message-Type AVP (AVP code 2007) is of type Enumerated and indicates the type of the message which caused the charging interaction
 */
public class SMMessageType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        SUBMISSION(0),
        DELIVERY_REPORT(1),
        SM_Service_Request(2);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a SMMessageType with the given value.
     *
     * @param value - the value of the AVP
     */
    public SMMessageType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    SMMessageType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
