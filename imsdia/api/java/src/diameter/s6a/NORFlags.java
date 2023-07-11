package diameter.s6a;

import com.intellinet.diameter.*;


/**
 * The NOR-Flags AVP is of type Unsigned32 and it contains a bit mask. The meaning of 
 *  the bits is defined below: 
 *  0 -Single-Registration-Indication, This bit, when set, indicates that the HSS shall send 
 * 	   a Cancel Location message to the current SGSN due to ISR
 * 1- MME area restricted, This bit, when set, indicates that the complete MME area is 
 * 	   restricted due to regional subscription
 * Note: Bits not defined in this table shall be cleared by the sending MME and 
 *	discarded by the receiving HSS.
 */
public class NORFlags extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a NORFlags with the given value.
     *
     * @param value - the value of the AVP
     */
    public NORFlags(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    NORFlags(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
