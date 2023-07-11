package diameter.s6a_r10;

import com.intellinet.diameter.*;


/**
 * The Operator-Determined-Barring AVP is of type Unsigned32 and it contains a bit mask 
 * indicating the services of a subscriber that are barred by the operator. The meaning 
 * of the bits is the following:
 * 0 - All Packet Oriented Services Barred
 * 1 - Roamer Access HPLMN-AP Barred
 * 2 - Roamer Access to VPLMN-AP Barred
 */
public class OperatorDeterminedBarring extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a OperatorDeterminedBarring with the given value.
     *
     * @param value - the value of the AVP
     */
    public OperatorDeterminedBarring(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    OperatorDeterminedBarring(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
