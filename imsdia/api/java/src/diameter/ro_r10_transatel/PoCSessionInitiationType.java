package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The PoC-Session-Initiation-Type AVP (AVP code 1277) is of type Enumerated 
 * and specifies the type of the PoC session initiation.
 */
public class PoCSessionInitiationType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        Pre_established(0),
        On_demand(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a PoCSessionInitiationType with the given value.
     *
     * @param value - the value of the AVP
     */
    public PoCSessionInitiationType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    PoCSessionInitiationType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
