package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * SIP-Request-Timestamp AVP is of type Time and holds the time in UTC format of the SIP request
 * (e.g. Invite, Update)
 */
public class SIPRequestTimestamp extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a SIPRequestTimestamp with the given value.
     *
     * @param value - the value of the AVP
     */
    public SIPRequestTimestamp(Integer value) {
        super(new com.intellinet.diameter.TimeData(value));
    }

    SIPRequestTimestamp(com.intellinet.diameter.TimeData data) {
        super(data);
    }
}
