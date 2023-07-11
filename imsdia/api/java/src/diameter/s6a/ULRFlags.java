package diameter.s6a;

import com.intellinet.diameter.*;


/**
 * The ULR-Flags AVP is of type Unsigned32 and it contains a bit mask. 
 * The meaning of the bits is defined below
 * Bit= 0 ==> Single-Registration-Indication. This bit, when set, indicates that the 
 * HSS shall send Cancel Location to the SGSN.
 * Bit= 1 ==> S6a/S6d-Indicator, This bit when set, indicates that the ULR message 
 * is sent on the S6a interface,i.e. the source node is an MME (or a combined MME/SGSN 
 * to which the UE is attached via E-UTRAN).This bit, when cleared, indicates that 
 * the ULR message is sent on the S6d interface, i.e. the source node is an 
 * SGSN (or a combined MME/SGSN to which the UE is attached via UTRAN or GERAN).
 * Bits not defined in this table shall be cleared by the sending MME and discarded by 
 * the receiving HSS.
 */
public class ULRFlags extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a ULRFlags with the given value.
     *
     * @param value - the value of the AVP
     */
    public ULRFlags(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    ULRFlags(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
