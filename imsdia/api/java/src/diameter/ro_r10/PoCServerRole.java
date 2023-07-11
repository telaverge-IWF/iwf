package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * PoC-Server-Role AVP is of type Enumerated and specifies the role of the PoC server.
 */
public class PoCServerRole extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        Participating_PoC_Server(0),
        Controlling_PoC_Server(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a PoCServerRole with the given value.
     *
     * @param value - the value of the AVP
     */
    public PoCServerRole(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    PoCServerRole(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
