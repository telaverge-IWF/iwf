package diameter.s6a;

import com.intellinet.diameter.*;


/**
 * The Requesting-Node-Type AVP is of type Enumerated and it contains the type of 
 * the node requesting for authentication vectors. The following values are defined:
 *	MME (0)
 *	SGSN (1)
 *	MME/SGSN (2)
 */
public class RequestingNodeType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        MME(0),
        SGSN(1),
        MMESGSN(2);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a RequestingNodeType with the given value.
     *
     * @param value - the value of the AVP
     */
    public RequestingNodeType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    RequestingNodeType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
