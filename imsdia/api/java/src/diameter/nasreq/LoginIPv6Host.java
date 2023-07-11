package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Login-IPv6-Host AVP (AVP Code 98) [RADIUSIPv6] is of type
 * OctetString and contains the IPv6 address of a host with which to
 * connect the user when the Login-Service AVP is included. It MAY be
 * used in an AA-Request command as a hint to the Diameter Server that a
 * specific host is desired, but the Diameter Server is not required to
 * honor the hint in the AA-Answer.
 */
public class LoginIPv6Host extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a LoginIPv6Host with the given value.
     *
     * @param value - the value of the AVP
     */
    public LoginIPv6Host(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    LoginIPv6Host(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
