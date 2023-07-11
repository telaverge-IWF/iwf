package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Currency-Code AVP is of type Unsigned32 and contains a currency code that specifies 
 * in which currency the values of AVPs containing monetary units were given.It is specified
 * by using the numeric values defined in the ISO 4217 standard [ISO4217].
 */
public class CurrencyCode extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CurrencyCode with the given value.
     *
     * @param value - the value of the AVP
     */
    public CurrencyCode(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CurrencyCode(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
