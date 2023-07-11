package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The PDP-Context-Type AVP (AVP code 1247) is of type Enumerated and indicates the type of a PDP context.
 */
public class PDPContextType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        PRIMARY(0),
        SECONDARY(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a PDPContextType with the given value.
     *
     * @param value - the value of the AVP
     */
    public PDPContextType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    PDPContextType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
