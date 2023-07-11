package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The Reason-Code AVP is of type Enumerated, and defines the reason for the network initiated de-registration. The
 * following values are defined:
 * <ul>
 * <li> PERMANENT_TERMINATION (0)
 * <li> NEW_SERVER_ASSIGNED (1)
 * <li> SERVER_CHANGE (2)
 * <li> REMOVE_S-CSCF (3)
 * </ul>
 * The detailed behaviour of the S-CSCF is defined in 3GPP TS 29.228.
 */
public class ReasonCode extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        PERMANENT_TERMINATION(0),
        NEW_SERVER_ASSIGNED(1),
        SERVER_CHANGE(2),
        REMOVE_SCSCF(3);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a ReasonCode with the given value.
     *
     * @param value - the value of the AVP
     */
    public ReasonCode(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    ReasonCode(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
