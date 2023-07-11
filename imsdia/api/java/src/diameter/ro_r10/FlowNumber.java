package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Flow-Number AVP (AVP code 509) is of type Unsigned32,and it contains the
 * ordinal number of the IP flow(s), assigned according to the rules in annex A
 * of 3GPP2 X.S0013-013-0.
 */
public class FlowNumber extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a FlowNumber with the given value.
     *
     * @param value - the value of the AVP
     */
    public FlowNumber(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    FlowNumber(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
