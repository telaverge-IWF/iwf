package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class MPSPriority extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a MPSPriority with the given value.
     *
     * @param value - the value of the AVP
     */
    public MPSPriority(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    MPSPriority(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
