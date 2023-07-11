package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Acct-Session-Time AVP (AVP Code 46) is of type Unsigned32 and
 * indicates the length of the current session in seconds. It can only
 * be present in ACR messages with an Accounting-Record-Type of
 * INTERIM_RECORD or STOP_RECORD.
 */
public class AcctSessionTime extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a AcctSessionTime with the given value.
     *
     * @param value - the value of the AVP
     */
    public AcctSessionTime(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    AcctSessionTime(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
