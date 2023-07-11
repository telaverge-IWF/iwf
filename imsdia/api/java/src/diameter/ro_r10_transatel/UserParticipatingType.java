package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The User-Participating-Type AVP(AVP code 1279) is of type Enumerated. 
 * It is a subfield of Participants-Group AVP to indicate the user 
 * participating type when participating in the PoC session.
 */
public class UserParticipatingType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        Normal(0),
        NW_PoC_Box(1),
        UE_PoC_Box(2);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a UserParticipatingType with the given value.
     *
     * @param value - the value of the AVP
     */
    public UserParticipatingType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    UserParticipatingType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
