package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Quota-consumption-Time is of type Unsigned32 and contains an idle traffic threshold time in
 * seconds.
 */
public class QuotaConsumptionTime extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a QuotaConsumptionTime with the given value.
     *
     * @param value - the value of the AVP
     */
    public QuotaConsumptionTime(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    QuotaConsumptionTime(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
