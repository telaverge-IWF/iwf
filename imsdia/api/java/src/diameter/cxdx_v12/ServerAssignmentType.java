package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The Server-Assignment-Type AVP is of type Enumerated, and indicates the type of server update being performed in a
 * Server-Assignment-Request operation. The following values are defined:
 * <ul>
 * <li> NO_ASSIGNMENT (0)<br>
 * This value is used to request from HSS the user profile assigned to one or more public identities, without
 * affecting the registration state of those identities.
 * <li> REGISTRATION (1)<br>
 * The request is generated as a consequence of a first registration of an identity.
 * <li> RE_REGISTRATION (2)<br>
 * The request corresponds to the re-registration of an identity.
 * <li> UNREGISTERED_USER (3)<br>
 * The request is generated because the S-CSCF received an INVITE for a public identity that is not registered.
 * <li> TIMEOUT_DEREGISTRATION (4)<br>
 * The SIP registration timer of an identity has expired.
 * <li> USER_DEREGISTRATION (5)<br>
 * The S-CSCF has received a user initiated de-registration request.
 * <li> TIMEOUT_DEREGISTRATION_STORE_SERVER_NAME (6)<br>
 * The SIP registration timer of an identity has expired. The S-CSCF keeps the user data stored in the S-CSCF
 * and requests HSS to store the S-CSCF name.
 * <li> USER_DEREGISTRATION_STORE_SERVER_NAME (7)<br>
 * The S-CSCF has received a user initiated de-registration request. The S-CSCF keeps the user data stored in
 * the S-CSCF and requests HSS to store the S-CSCF name.
 * <li> ADMINISTRATIVE_DEREGISTRATION (8)<br>
 * The S-CSCF, due to administrative reasons, has performed the de-registration of an identity.
 * <li> AUTHENTICATION_FAILURE (9)<br>
 * The authentication of a user has failed.
 * <li> AUTHENTICATION_TIMEOUT (10)<br>
 * The authentication timeout has expired.
 * <li> DEREGISTRATION_TOO_MUCH_DATA (11)<br>
 * The S-CSCF has requested user profile information from the HSS and has received a volume of data higher
 * than it can accept.
 * </ul>
 */
public class ServerAssignmentType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        NO_ASSIGNMENT(0),
        REGISTRATION(1),
        RE_REGISTRATION(2),
        UNREGISTERED_USER(3),
        TIMEOUT_DEREGISTRATION(4),
        USER_DEREGISTRATION(5),
        TIMEOUT_DEREGISTRATION_STORE_SERVER_NAME(6),
        USER_DEREGISTRATION_STORE_SERVER_NAME(7),
        ADMINISTRATIVE_DEREGISTRATION(8),
        AUTHENTICATION_FAILURE(9),
        AUTHENTICATION_TIMEOUT(10),
        DEREGISTRATION_TOO_MUCH_DATA(11),
        AAA_USER_DATA_REQUEST(12),
        PGW_UPDATE(13),
        RESTORATION(14);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a ServerAssignmentType with the given value.
     *
     * @param value - the value of the AVP
     */
    public ServerAssignmentType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    ServerAssignmentType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
