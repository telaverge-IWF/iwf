package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Change-Time AVP (AVP code 2038) is of type Time.  In EPC Charging, 
 * it holds the time in UTC format when the volume counts associated to the 
 * IP-CAN bearer, or the service data container, is closed and reported due to 
 * Charging condition change. 
 */
public class ChangeTime extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a ChangeTime with the given value.
     *
     * @param value - the value of the AVP
     */
    public ChangeTime(Integer value) {
        super(new com.intellinet.diameter.TimeData(value));
    }

    ChangeTime(com.intellinet.diameter.TimeData data) {
        super(data);
    }
}
