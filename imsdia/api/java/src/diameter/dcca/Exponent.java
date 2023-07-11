package diameter.dcca;

import com.intellinet.diameter.*;


/**
 * Exponent AVP is of type Integer32 (AVP Code 429) and contains the exponent value to 
 * be applied for the Value-Digit AVP within the Unit-Value AVP.
 */
public class Exponent extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a Exponent with the given value.
     *
     * @param value - the value of the AVP
     */
    public Exponent(Integer value) {
        super(new com.intellinet.diameter.Integer32Data(value));
    }

    Exponent(com.intellinet.diameter.Integer32Data data) {
        super(data);
    }
}
