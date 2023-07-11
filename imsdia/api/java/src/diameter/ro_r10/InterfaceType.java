package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Interface-Type AVP (AVP code 2006) is of type Enumerated and contains 
 * information about type of interface / nature of the transaction in the 
 * messaging node for which the charging event occurs
 */
public class InterfaceType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        Unknown(0),
        MOBILE_ORIGINATING(1),
        MOBILE_TERMINATING(2),
        APPLICATION_ORIGINATING(3),
        APPLICATION_TERMINATION(4);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a InterfaceType with the given value.
     *
     * @param value - the value of the AVP
     */
    public InterfaceType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    InterfaceType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
