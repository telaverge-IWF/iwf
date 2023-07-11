package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The CSG-Membership-Indication AVP (AVP code 2318) is of type Enumerated, and indicates the UE 
 * is a member of the accessing CSG cell, if the access mode is Hybrid, as described in TS 29.060 [225], 
 * and in TS 29.274 [226]. If this indication is not present, this means the UE is a Not member of the 
 * CSG cell for hybrid access mode
 */
public class CSGMembershipIndication extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        Not_CSG_member(0),
        CSG_Member(1);

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
