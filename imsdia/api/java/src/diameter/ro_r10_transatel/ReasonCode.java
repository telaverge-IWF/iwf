package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
* The Reason-Code AVP (AVP code 2316) is of type Enumerated and identifies if the
* Rate-Element corresponds to a specific charge type.
*/
public class ReasonCode extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        UNKNOWN(0),
        USAGE(1),
        COMMUNICATION_ATTEMPT_CHARGE(2),
        SETUP_CHARGE(3),
        ADD_ON_CHARGE(4);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a ReasonCode with the given value.
     *
     * @param value - the value of the AVP
     */
    public ReasonCode(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    ReasonCode(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
