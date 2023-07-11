package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Login-LAT-Port AVP (AVP Code 63) is of type OctetString and
 * contains the Port with which the user is to be connected by LAT. It
 * MAY be used in an authorization request as a hint to the server that
 * a specific port is desired, but the server is not required to honor
 * the hint in the corresponding response. This AVP MUST only be
 * present in a response if the Login-Service-Type AVP is set to LAT.
 */
public class LoginLATPort extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a LoginLATPort with the given value.
     *
     * @param value - the value of the AVP
     */
    public LoginLATPort(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    LoginLATPort(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
