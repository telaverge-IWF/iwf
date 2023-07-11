package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
* The SIP-Request-Timestamp-Fraction AVP (AVP code 2301) is of type Unsigned32 and holds 
* the miliseconds fraction in relation to SIP-Request-Timestamp.
*/
public class SIPRequestTimestampFraction extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a SIPRequestTimestampFraction with the given value.
     *
     * @param value - the value of the AVP
     */
    public SIPRequestTimestampFraction(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    SIPRequestTimestampFraction(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
