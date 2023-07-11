package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The User-Authorization-Type AVP is of type Enumerated, and indicates the type of user authorization being performed
 * in a User Authorization operation, i.e. UAR command. The following values are defined:
 * <ul>
 * <li> REGISTRATION (0)<br>
 * This value is used in case of the initial registration or re-registration. I-CSCF determines this from the
 * Expires field or expires parameter in Contact field in the SIP REGISTER method if it is not equal to zero.
 * This is the default value.
 * <li> DE_REGISTRATION (1)<br>
 * This value is used in case of the de-registration. I-CSCF determines this from the Expires field or expires
 * parameter in Contact field in the SIP REGISTER method if it is equal to zero.
 * <li> REGISTRATION_AND_CAPABILITIES (2)<br>
 * This value is used in case of initial registration or re-registration and when the I-CSCF explicitly requests SCSCF
 * capability information from the HSS. The I-CSCF shall use this value when the user's current S-CSCF,
 * which is stored in the HSS, cannot be contacted and a new S-CSCF needs to be selected
 * </ul>
 */
public class UserAuthorizationType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        REGISTRATION(0),
        DE_REGISTRATION(1),
        REGISTRATION_AND_CAPABILITIES(2);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a UserAuthorizationType with the given value.
     *
     * @param value - the value of the AVP
     */
    public UserAuthorizationType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    UserAuthorizationType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
