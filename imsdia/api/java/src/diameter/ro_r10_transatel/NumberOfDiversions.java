package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Number-Of-Diversions AVP (AVP Code 2034) is of type Unsigned32 and 
 * holds the number of diversions related to a CDIV service. When counting the 
 * number of diversions, all types of diversion are included.
 */
public class NumberOfDiversions extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a NumberOfDiversions with the given value.
     *
     * @param value - the value of the AVP
     */
    public NumberOfDiversions(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    NumberOfDiversions(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
