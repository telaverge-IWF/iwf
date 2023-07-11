package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * This Envelope-End-Time AVP (AVP code 1267) is of type Time. It is set to the time of the end of the time envelope.
 */
public class EnvelopeEndTime extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a EnvelopeEndTime with the given value.
     *
     * @param value - the value of the AVP
     */
    public EnvelopeEndTime(Integer value) {
        super(new com.intellinet.diameter.TimeData(value));
    }

    EnvelopeEndTime(com.intellinet.diameter.TimeData data) {
        super(data);
    }
}
