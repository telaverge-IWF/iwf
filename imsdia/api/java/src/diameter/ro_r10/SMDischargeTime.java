package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The SM-Discharge-Time AVP (AVP code 2012) is of type Time. It indicates the time associated with the event being reported in the SM-Status AVP. It is only used in scenarios in which the delivery of the Delivery-Report (more properly the Status-Report) is being charged.
 */
public class SMDischargeTime extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a SMDischargeTime with the given value.
     *
     * @param value - the value of the AVP
     */
    public SMDischargeTime(Integer value) {
        super(new com.intellinet.diameter.TimeData(value));
    }

    SMDischargeTime(com.intellinet.diameter.TimeData data) {
        super(data);
    }
}
