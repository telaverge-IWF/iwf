package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Login-TCP-Port AVP (AVP Code 16) is of type Unsigned32 and contains the
 * TCP port with which the user is to be connected when the Login-Service AVP
 * is also present. This AVP SHOULD only be present in authorization responses.
 * The value MUST NOT be greater than 65,535.
 */
public class LoginTCPPort extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a LoginTCPPort with the given value.
     *
     * @param value - the value of the AVP
     */
    public LoginTCPPort(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    LoginTCPPort(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
