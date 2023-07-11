package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Node-Functionality AVP is of type Enumerated and includes the functionality identifier of the node.
 */
public class NodeFunctionality extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        S_CSCF(0),
        P_CSCF(1),
        I_CSCF(2),
        MRFC(3),
        MGCF(4),
        BGCF(5),
        AS(6),
        IBCF(7),
        S_GW(8),
        P_GW(9),
        HSGW(10);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a NodeFunctionality with the given value.
     *
     * @param value - the value of the AVP
     */
    public NodeFunctionality(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    NodeFunctionality(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
