package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Login-Service AVP (AVP Code 15) is of type Enumerated and contains the
 * service that should be used to connect the user to the login host. This AVP
 * SHOULD only be present in authorization responses.
 */
public class LoginService extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        TELNET(0),
        RLOGIN(1),
        TCPCLEAR(2),
        PORTMASTER(3),
        LAT(4),
        X25_PAD(5),
        X25_T3POS(6),
        TCPCLEARQUIET(8);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a LoginService with the given value.
     *
     * @param value - the value of the AVP
     */
    public LoginService(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    LoginService(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
