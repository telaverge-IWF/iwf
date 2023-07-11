package diameter.s6a;

import com.intellinet.diameter.*;


/**
 * The Immediate-Response-Preferred AVP is of type Unsigned32. When EUTRAN-AVs and UMTS-AVs 
 * or GERAN AVs are requested, this parameter indicates which type of AV is requested for 
 * immediate use in the MME/SGSN. It may be used by the HSS to determine the number of 
 * vectors to be obtained from the AuC.
*/
public class ImmediateResponsePreferred extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a ImmediateResponsePreferred with the given value.
     *
     * @param value - the value of the AVP
     */
    public ImmediateResponsePreferred(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    ImmediateResponsePreferred(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
