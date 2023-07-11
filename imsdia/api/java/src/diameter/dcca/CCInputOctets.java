package diameter.dcca;

import com.intellinet.diameter.*;


/**
 * The CC-Input-Octets AVP is of type Unsigned64 and contains the number of requested, 
 * granted, or used octets that can be/have been received from the end user.
 */
public class CCInputOctets extends com.intellinet.diameter.DerivedAVP<Long> {
    /**
     * Constructs a CCInputOctets with the given value.
     *
     * @param value - the value of the AVP
     */
    public CCInputOctets(Long value) {
        super(new com.intellinet.diameter.Unsigned64Data(value));
    }

    CCInputOctets(com.intellinet.diameter.Unsigned64Data data) {
        super(data);
    }
}
