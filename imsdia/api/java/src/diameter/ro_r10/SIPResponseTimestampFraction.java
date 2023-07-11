package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
* The SIP-Response-Timestamp-Fraction AVP (AVP code 2302) is of type Unsigned32 and holds the
* miliseconds fraction in relation to SIP-Response-Timestamp.
*/
public class SIPResponseTimestampFraction extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a SIPResponseTimestampFraction with the given value.
     *
     * @param value - the value of the AVP
     */
    public SIPResponseTimestampFraction(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    SIPResponseTimestampFraction(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
