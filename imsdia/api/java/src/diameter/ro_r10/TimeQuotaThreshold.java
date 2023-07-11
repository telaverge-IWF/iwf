package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Time-Quota-Threshold AVP is of type Unsigned32 and contains a threshold value in seconds.
 */
public class TimeQuotaThreshold extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a TimeQuotaThreshold with the given value.
     *
     * @param value - the value of the AVP
     */
    public TimeQuotaThreshold(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    TimeQuotaThreshold(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
