package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Login-LAT-Group AVP (AVP Code 36) is of type OctetString and
 * contains a string identifying the LAT group codes this user is
 * authorized to use. It MAY be used in an authorization request as a
 * hint to the server that a specific group is desired, but the server
 * is not required to honor the hint in the corresponding response.
 * This AVP MUST only be present in a response if the Login-Service-Type
 * AVP is set to LAT.
 */
public class LoginLATGroup extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a LoginLATGroup with the given value.
     *
     * @param value - the value of the AVP
     */
    public LoginLATGroup(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    LoginLATGroup(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
