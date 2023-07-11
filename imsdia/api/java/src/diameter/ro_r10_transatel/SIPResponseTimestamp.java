package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * SIP-Response-Timestamp AVP is of type Time and holds the time in UTC format of the response 
 * to the SIP request (e.g. 200 OK).
 */
public class SIPResponseTimestamp extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a SIPResponseTimestamp with the given value.
     *
     * @param value - the value of the AVP
     */
    public SIPResponseTimestamp(Integer value) {
        super(new com.intellinet.diameter.TimeData(value));
    }

    SIPResponseTimestamp(com.intellinet.diameter.TimeData data) {
        super(data);
    }
}
