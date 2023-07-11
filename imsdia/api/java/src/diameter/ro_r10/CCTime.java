package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The CC-Time AVP is of type Unsigned32 and indicates the length of the requested, 
 * granted, or used time in seconds.
 */
public class CCTime extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CCTime with the given value.
     *
     * @param value - the value of the AVP
     */
    public CCTime(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CCTime(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
