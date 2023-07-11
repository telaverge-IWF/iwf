package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Value-Digits AVP is of type Integer64 (AVP Code 447) and contains the significant digits 
 * of the number.  If decimal values are needed to present the units, the scaling MUST be 
 * indicated with the related Exponent AVP.
 */
public class ValueDigits extends com.intellinet.diameter.DerivedAVP<Long> {
    /**
     * Constructs a ValueDigits with the given value.
     *
     * @param value - the value of the AVP
     */
    public ValueDigits(Long value) {
        super(new com.intellinet.diameter.Integer64Data(value));
    }

    ValueDigits(com.intellinet.diameter.Integer64Data data) {
        super(data);
    }
}
