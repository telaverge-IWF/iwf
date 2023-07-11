package diameter.s6a_r11;

import com.intellinet.diameter.*;


/**
 * The Number-Of-Requested-Vectors AVP is of type Unsigned32. 
 * This AVP contains the number of AVs the MME is prepared to receive
*/
public class NumberOfRequestedVectors extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a NumberOfRequestedVectors with the given value.
     *
     * @param value - the value of the AVP
     */
    public NumberOfRequestedVectors(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    NumberOfRequestedVectors(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
