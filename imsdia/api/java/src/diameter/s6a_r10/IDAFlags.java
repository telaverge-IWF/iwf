package diameter.s6a_r10;

import com.intellinet.diameter.*;


/**
 * The IDA-Flags AVP is of type Unsigned32 and it contains a bit mask. The meaning of the 
 * bits is defined : 0- MME area restricted This bit, when set, indicates that the complete
 * MME area is restricted due to regional subscription.How the HSS uses this information 
 * is FFS. Bits not defined in this table shall be cleared by the sending MME and discarded 
 * by the receiving HSS.
 */
public class IDAFlags extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a IDAFlags with the given value.
     *
     * @param value - the value of the AVP
     */
    public IDAFlags(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    IDAFlags(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
