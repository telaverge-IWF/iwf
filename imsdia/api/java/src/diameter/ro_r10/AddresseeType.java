package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Addressee-Type AVP is of type Enumerated and identifies how the recipient is addressed in the 
 * header of an MM.
 */
public class AddresseeType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        TO(0),
        CC(1),
        BCC(2);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a AddresseeType with the given value.
     *
     * @param value - the value of the AVP
     */
    public AddresseeType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    AddresseeType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
