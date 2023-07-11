package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The AoC-Service-Obligatory-Type AVP (AVP code 2312) is of type Enumerated and holds 
 * the information if the AoC information is binding or not.
 */
public class AoCServiceObligatoryType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        NON_BINDING(0),
        BINDING(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a AoCServiceObligatoryType with the given value.
     *
     * @param value - the value of the AVP
     */
    public AoCServiceObligatoryType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    AoCServiceObligatoryType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
