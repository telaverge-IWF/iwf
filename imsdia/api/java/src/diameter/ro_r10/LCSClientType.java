package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * LCS-Client-Type AVP is of type Enumerated.
 */
public class LCSClientType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        EMERGENCY_SERVICES(0),
        VALUE_ADDED_SERVICES(1),
        PLMN_OPERATOR_SERVICES(2),
        LAWFUL_INTERCEPT_SERVICES(3);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a LCSClientType with the given value.
     *
     * @param value - the value of the AVP
     */
    public LCSClientType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    LCSClientType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
