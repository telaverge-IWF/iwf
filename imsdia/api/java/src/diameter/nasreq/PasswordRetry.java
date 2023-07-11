package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Password-Retry AVP (AVP Code 75) is of type Unsigned32 and MAY be
 * included in the AA-Answer if the Result-Code indicates an
 * authentication failure. The value of this AVP indicates how many
 * authentication attempts a user is permitted before being
 * disconnected. This AVP is primarily intended for use when the
 * Framed-Protocol AVP (see section 6.10.1) is set to ARAP.
 */
public class PasswordRetry extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a PasswordRetry with the given value.
     *
     * @param value - the value of the AVP
     */
    public PasswordRetry(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    PasswordRetry(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
