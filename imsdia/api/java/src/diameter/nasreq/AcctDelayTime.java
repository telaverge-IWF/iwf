package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Acct-Delay-Time AVP (AVP Code 41) is of type Unsigned32 and
 * indicates the number of seconds the Diameter client has been trying
 * to send the Accounting-Request (ACR). The accounting server may
 * subtract this value from the time when the ACR arrives at the server
 * to calculate the approximate time of the event that caused the ACR to
 * be generated.
 */
public class AcctDelayTime extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a AcctDelayTime with the given value.
     *
     * @param value - the value of the AVP
     */
    public AcctDelayTime(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    AcctDelayTime(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
