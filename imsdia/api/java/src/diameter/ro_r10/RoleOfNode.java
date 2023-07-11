package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Role-Of-Node AVP is of type enumerated and specifies the role of the AS/CSCF.
 */
public class RoleOfNode extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        ORIGINATING_ROLE(0),
        TERMINATING_ROLE(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a RoleOfNode with the given value.
     *
     * @param value - the value of the AVP
     */
    public RoleOfNode(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    RoleOfNode(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
