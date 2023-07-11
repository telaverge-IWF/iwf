package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Quota-Holding-Time AVP is of type Unsigned32 and contains the quots holding time in seconds.
 */
public class QuotaHoldingTime extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a QuotaHoldingTime with the given value.
     *
     * @param value - the value of the AVP
     */
    public QuotaHoldingTime(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    QuotaHoldingTime(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
