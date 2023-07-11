package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Login-LAT-Service AVP (AVP Code 34) is of type OctetString and contains
 * the system with which the user is to be connected by LAT. It MAY be used in
 * an authorization request as a hint to the server that a specific service is
 * desired, but the server is not required to honor the hint in the
 * corresponding response. This AVP MUST only be present in the response if
 * the Login-Service AVP states that LAT is desired.
 */
public class LoginLATService extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a LoginLATService with the given value.
     *
     * @param value - the value of the AVP
     */
    public LoginLATService(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    LoginLATService(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
