package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class PriorityLevel extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a PriorityLevel with the given value.
     *
     * @param value - the value of the AVP
     */
    public PriorityLevel(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    PriorityLevel(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
