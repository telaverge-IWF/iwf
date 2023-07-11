package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The CC-Output-Octets AVP is of type Unsigned64 and contains the number of requested,
 * granted, or used octets that can be/have been sent to the end user.
 */
public class CCOutputOctets extends com.intellinet.diameter.DerivedAVP<Long> {
    /**
     * Constructs a CCOutputOctets with the given value.
     *
     * @param value - the value of the AVP
     */
    public CCOutputOctets(Long value) {
        super(new com.intellinet.diameter.Unsigned64Data(value));
    }

    CCOutputOctets(com.intellinet.diameter.Unsigned64Data data) {
        super(data);
    }
}
