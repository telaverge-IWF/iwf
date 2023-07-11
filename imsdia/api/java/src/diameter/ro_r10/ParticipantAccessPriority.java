package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Participant-Access-Priority AVP (AVP code 1259) is of type Enumerated. 
 * It is a subfield of Participants-Group AVP to indicate the priority level 
 * for users when initiating a new PoC session or participating in a PoC 
 * session.
 */
public class ParticipantAccessPriority extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        Pre_emptive_priority(1),
        High_priority(2),
        Normal_priority(3),
        Low_priority(4);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a ParticipantAccessPriority with the given value.
     *
     * @param value - the value of the AVP
     */
    public ParticipantAccessPriority(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    ParticipantAccessPriority(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
