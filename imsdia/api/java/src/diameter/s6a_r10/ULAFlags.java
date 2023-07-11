package diameter.s6a_r10;

import com.intellinet.diameter.*;


/**
 * The ULA-Flags AVP is of type Unsigned32 and it contains a bit mask. 
 * The meaning of the bits is defined below
 * Bit= 0 ===> Separation Indication.This bit, when set, indicates that the HSS stores 
 * SGSN number and MME number in separate memory. A Rel-8 HSS shall set the bit.
 * A IWF interworking with a pre Rel-8 HSS/HLR shall clear the bit. Bits not defined in 
 * this shall be cleared by the sending HSS and discarded by the receiving MME.
 */
public class ULAFlags extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a ULAFlags with the given value.
     *
     * @param value - the value of the AVP
     */
    public ULAFlags(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    ULAFlags(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
