package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Tariff-Time-Change AVP (AVP Code 451) is of type Time. It is sent from the server to the 
 * client and includes the time in seconds since January 1, 1900, 00:00 UTC, when the tariff 
 * of the service will be changed.
 */
public class TariffTimeChange extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a TariffTimeChange with the given value.
     *
     * @param value - the value of the AVP
     */
    public TariffTimeChange(Integer value) {
        super(new com.intellinet.diameter.TimeData(value));
    }

    TariffTimeChange(com.intellinet.diameter.TimeData data) {
        super(data);
    }
}
