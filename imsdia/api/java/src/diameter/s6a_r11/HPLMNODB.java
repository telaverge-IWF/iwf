package diameter.s6a_r11;

import com.intellinet.diameter.*;


/**
 * The HPLMN-ODB AVP is of type Unsigned32 and it contains a bit mask indicating the HPLMN 
 * specific services of a subscriber that are barred by the operator. The meaning of the 
 * bits is HPLMN specific:
 *  	0	HPLMN specific barring type 1
 *	1	HPLMN specific barring type 2
 *	2	HPLMN specific barring type 3
 *	3	HPLMN specific barring type 4
 */
public class HPLMNODB extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a HPLMNODB with the given value.
     *
     * @param value - the value of the AVP
     */
    public HPLMNODB(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    HPLMNODB(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
