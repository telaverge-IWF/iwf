package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Participant-Action-Type AVP (AVP code 2049) is of type Enumerated and 
 * holds the participant's action type during the conference for Billing 
 * Domain's information.
 */
public class ParticipantActionType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        CREATE_CONF(0),
        JOIN_CONF(1),
        INVITE_INTO_CONF(2),
        QUIT_CONF(3);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a ParticipantActionType with the given value.
     *
     * @param value - the value of the AVP
     */
    public ParticipantActionType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    ParticipantActionType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
