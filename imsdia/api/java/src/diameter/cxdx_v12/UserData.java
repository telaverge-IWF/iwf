package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The User-Data AVP is of type OctetString. This AVP contains the user data required to give service to a user. The exact
 * content and format of this AVP is described in 3GPP TS 29.228.
 */
public class UserData extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a UserData with the given value.
     *
     * @param value - the value of the AVP
     */
    public UserData(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    UserData(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
