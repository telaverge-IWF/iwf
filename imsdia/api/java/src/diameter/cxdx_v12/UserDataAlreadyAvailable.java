package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The User-Data-Already-Available AVP is of type Enumerated, and indicates to the HSS whether or not the S-CSCF
 * already has the part of the user profile that it needs to serve the user. The following values are defined:
 * <ul>
 * <li> USER_DATA_NOT_AVAILABLE (0)<br>
 * The S-CSCF does not have the data that it needs to serve the user.
 * <li> USER_DATA_ALREADY_AVAILABLE (1)<br>
 * The S-CSCF already has the data that it needs to serve the user.
 * </ul>
 */
public class UserDataAlreadyAvailable extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        USER_DATA_NOT_AVAILABLE(0),
        USER_DATA_ALREADY_AVAILABLE(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a UserDataAlreadyAvailable with the given value.
     *
     * @param value - the value of the AVP
     */
    public UserDataAlreadyAvailable(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    UserDataAlreadyAvailable(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
