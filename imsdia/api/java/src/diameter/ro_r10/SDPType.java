package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The SDP-Type AVP (AVP code 2036) is of type Enumerated and holds 
 * information if the SDP media component was of type SDP offer or SDP answer.
 */
public class SDPType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        SDP_Offer(0),
        SDP_Answer(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a SDPType with the given value.
     *
     * @param value - the value of the AVP
     */
    public SDPType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    SDPType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
