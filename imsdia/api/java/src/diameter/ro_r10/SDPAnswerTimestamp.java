package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The SDP-Answer-Timestamp AVP (AVP code 1275) is of type Time and holds the 
 * time in UTC format of the response to the SDP offer.
 */
public class SDPAnswerTimestamp extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a SDPAnswerTimestamp with the given value.
     *
     * @param value - the value of the AVP
     */
    public SDPAnswerTimestamp(Integer value) {
        super(new com.intellinet.diameter.TimeData(value));
    }

    SDPAnswerTimestamp(com.intellinet.diameter.TimeData data) {
        super(data);
    }
}
