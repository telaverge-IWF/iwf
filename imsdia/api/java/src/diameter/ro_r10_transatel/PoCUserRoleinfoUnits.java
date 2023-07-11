package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The PoC-User-Role-info-Units (AVP code 1254) is of type Enumerated and 
 * specify the role type details of PoC users.
 */
public class PoCUserRoleinfoUnits extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        Moderator(1),
        Dispatcher(2),
        Session_Owner(3),
        Session_Participant(4);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a PoCUserRoleinfoUnits with the given value.
     *
     * @param value - the value of the AVP
     */
    public PoCUserRoleinfoUnits(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    PoCUserRoleinfoUnits(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
