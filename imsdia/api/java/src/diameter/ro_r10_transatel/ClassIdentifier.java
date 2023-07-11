package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Class-Identifier AVP is of type enumerated.
 */
public class ClassIdentifier extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        Personal(0),
        Advertisement(1),
        Informational(2),
        Auto(3);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a ClassIdentifier with the given value.
     *
     * @param value - the value of the AVP
     */
    public ClassIdentifier(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    ClassIdentifier(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
