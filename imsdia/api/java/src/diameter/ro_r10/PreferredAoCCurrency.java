package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
*  The Preferred-AoC-Currency AVP (AVP code 2315) is of type Unsigned32 and indicates the preferred 
*  currency code that the AoC function would like to get the AoC information. It is specified by using 
*  the numeric values defined in the ISO 4217 standard, refer RFC 4006 [402].
*/
public class PreferredAoCCurrency extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a PreferredAoCCurrency with the given value.
     *
     * @param value - the value of the AVP
     */
    public PreferredAoCCurrency(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    PreferredAoCCurrency(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
