package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Login-IP-Host AVP (AVP Code 14) [RADIUS] is of type OctetString
 * and contains the IPv4 address of a host with which to connect the
 * user when the Login-Service AVP is included. It MAY be used in an
 * AA-Request command as a hint to the Diameter Server that a specific
 * host is desired, but the Diameter Server is not required to honor the
 * hint in the AA-Answer.
 */
public class LoginIPHost extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a LoginIPHost with the given value.
     *
     * @param value - the value of the AVP
     */
    public LoginIPHost(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    LoginIPHost(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
