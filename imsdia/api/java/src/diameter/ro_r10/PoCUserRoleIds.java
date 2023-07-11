package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The PoC-User-Role-Ids AVP (AVP code 1253) is of type UTF8String and 
 * identifies the PoC user role.
 */
public class PoCUserRoleIds extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a PoCUserRoleIds with the given value.
     *
     * @param value - the value of the AVP
     */
    public PoCUserRoleIds(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    PoCUserRoleIds(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
