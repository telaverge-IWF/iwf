package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The AoC-Format AVP (AVP code 2310) is of type Enumerated and holds the 
 * format on how the AoC information shall be sent to the UE.
 */
public class AoCFormat extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        MONETARY(0),
        NON_MONETARY(1),
        CAI(2);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a AoCFormat with the given value.
     *
     * @param value - the value of the AVP
     */
    public AoCFormat(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    AoCFormat(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
