package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class CSGMembershipIndication extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        NOT_CSG_MEMBER(0),
        CSG_MEMBER(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a CSGMembershipIndication with the given value.
     *
     * @param value - the value of the AVP
     */
    public CSGMembershipIndication(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    CSGMembershipIndication(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
