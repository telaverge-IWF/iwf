package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The CC-Sub-Session-Id AVP (AVP Code 419) is of type Unsigned64 and contains
 * the credit-control sub-session identifier. The combination of the Session-Id
 * and this AVP MUST be unique per sub-session, and the value of this AVP MUST
 * be monotonically increased by one for all new sub-sessions. The absence of
 * this AVP implies that no subsessions are in use.
 */
public class CCSubSessionId extends com.intellinet.diameter.DerivedAVP<Long> {
    /**
     * Constructs a CCSubSessionId with the given value.
     *
     * @param value - the value of the AVP
     */
    public CCSubSessionId(Long value) {
        super(new com.intellinet.diameter.Unsigned64Data(value));
    }

    CCSubSessionId(com.intellinet.diameter.Unsigned64Data data) {
        super(data);
    }
}
