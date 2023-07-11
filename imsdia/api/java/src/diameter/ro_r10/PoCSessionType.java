package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * PoC-Session-Type AVP is of type Enumerated and specifies the type of PoC session.
 */
public class PoCSessionType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        One_to_one_PoC_session(0),
        chat_PoC_group_session(1),
        pre_arranged_PoC_group_session(2),
        ad_hoc_PoC_group_session(3);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a PoCSessionType with the given value.
     *
     * @param value - the value of the AVP
     */
    public PoCSessionType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    PoCSessionType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
