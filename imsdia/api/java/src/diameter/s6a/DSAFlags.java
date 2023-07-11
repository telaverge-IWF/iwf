package diameter.s6a;

import com.intellinet.diameter.*;


/**
 * The DSA-Flags AVP is of type Unsigned32 and it contains a bit mask. 
 * The meaning of the bits is defined below:
 *	0- MME area restricted	This bit, when set, indicates that the complete MME area is 
 *	restricted due to regional subscription.
 * Note: Bits not defined in this table shall be cleared by the sending MME and 
 *		discarded by the receiving HSS.
 */
public class DSAFlags extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a DSAFlags with the given value.
     *
     * @param value - the value of the AVP
     */
    public DSAFlags(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    DSAFlags(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
