package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Adaptations AVP is of type Enumerated and indicates whether teh originator allows adaptation of the
 * content (default Yes)
 */
public class Adaptations extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        Yes(0),
        No(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a Adaptations with the given value.
     *
     * @param value - the value of the AVP
     */
    public Adaptations(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    Adaptations(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
