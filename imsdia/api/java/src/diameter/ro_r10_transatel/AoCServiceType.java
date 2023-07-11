package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The AoC-Service-Type AVP (AVP code 2313) is of type Enumerated and defines the type 
 * of AoC information to be provided to the subscriber.
 */
public class AoCServiceType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        NONE(0),
        AOC_S(1),
        AOC_D(2),
        AOC_E(3);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a AoCServiceType with the given value.
     *
     * @param value - the value of the AVP
     */
    public AoCServiceType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    AoCServiceType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
