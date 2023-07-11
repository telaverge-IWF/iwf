package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Envelope-Start-Time AVP (AVP code 1269) is of type Time. It is set 
 * to the time of the packet of user data which caused the time envelope 
 * to start.
 */
public class EnvelopeStartTime extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a EnvelopeStartTime with the given value.
     *
     * @param value - the value of the AVP
     */
    public EnvelopeStartTime(Integer value) {
        super(new com.intellinet.diameter.TimeData(value));
    }

    EnvelopeStartTime(com.intellinet.diameter.TimeData data) {
        super(data);
    }
}
