package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Base-Time-Interval AVP (AVP code 1265) is of type Unsigned32. It 
 * contains the length of the base time interval, for controlling the 
 * consumption of time quota, in seconds. 
 */
public class BaseTimeInterval extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a BaseTimeInterval with the given value.
     *
     * @param value - the value of the AVP
     */
    public BaseTimeInterval(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    BaseTimeInterval(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
