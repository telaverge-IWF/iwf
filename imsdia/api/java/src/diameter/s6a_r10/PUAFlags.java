package diameter.s6a_r10;

import com.intellinet.diameter.*;


/**
   * The PUA-Flags AVP is of type Unsigned32 and it contains a bit mask. 
   * The meaning of the bits is defined below:
   *  0-Freeze M-TMSI	This bit, when set, indicates to the MME that the M-TMSI needs 
   * to be frozen, i.e. shall not be immediately re-used.
   * Note: Bits not defined in this table shall be cleared by the sending HSS and 
   *	discarded by the receiving MME.
   */
public class PUAFlags extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a PUAFlags with the given value.
     *
     * @param value - the value of the AVP
     */
    public PUAFlags(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    PUAFlags(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
