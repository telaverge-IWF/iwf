package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Unit-Quota-Threshold AVP is of type Unsigned32 and contains a threshold value in service
 * specific units.
 */
public class UnitQuotaThreshold extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a UnitQuotaThreshold with the given value.
     *
     * @param value - the value of the AVP
     */
    public UnitQuotaThreshold(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    UnitQuotaThreshold(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
