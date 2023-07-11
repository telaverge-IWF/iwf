package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
  * The PoC-Change-Condition AVP (AVP code 1261) is of type Enumerated and contains the reason for closing a container and the addition of a new container. 
 */
public class PoCChangeCondition extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        serviceChange(0),
        volumeLimit(1),
        timeLimit(2),
        numberofTalkBurstLimit(3),
        numberofActiveParticipants(4),
        tariffTime(5);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a PoCChangeCondition with the given value.
     *
     * @param value - the value of the AVP
     */
    public PoCChangeCondition(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    PoCChangeCondition(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
