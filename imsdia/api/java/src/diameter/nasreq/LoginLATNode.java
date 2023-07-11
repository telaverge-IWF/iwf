package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Login-LAT-Node AVP (AVP Code 35) is of type OctetString and contains the
 * Node with which the user is to be automatically connected by LAT. It MAY be
 * used in an authorization request as a hint to the server that a specific
 * LAT node is desired, but the server is not required to honor the hint in 
 * the corresponding response. This AVP MUST only be present in a response if
 * the Login-Service-Type AVP is set to LAT.
 */
public class LoginLATNode extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a LoginLATNode with the given value.
     *
     * @param value - the value of the AVP
     */
    public LoginLATNode(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    LoginLATNode(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
