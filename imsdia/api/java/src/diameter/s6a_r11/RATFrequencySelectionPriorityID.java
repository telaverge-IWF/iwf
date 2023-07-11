package diameter.s6a_r11;

import com.intellinet.diameter.*;


/**
 *  
 */
public class RATFrequencySelectionPriorityID extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a RATFrequencySelectionPriorityID with the given value.
     *
     * @param value - the value of the AVP
     */
    public RATFrequencySelectionPriorityID(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    RATFrequencySelectionPriorityID(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
