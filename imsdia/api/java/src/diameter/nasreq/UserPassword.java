package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The User-Password AVP (AVP Code 2) is of type OctetString and
 * contains the password of the user to be authenticated, or the user's
 * input in a multi-round authentication exchange.
 * The User-Password AVP contains a user password or one-time password
 * and therefore represents sensitive information. As required in
 * [BASE], Diameter messages are encrypted by using IPsec or TLS.
 * Unless this AVP is used for one-time passwords, the User-Password AVP
 * SHOULD NOT be used in untrusted proxy environments without encrypting
 * it by using end-to-end security techniques, such as the proposed CMS
 * Security [DiamCMS].
 */
public class UserPassword extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a UserPassword with the given value.
     *
     * @param value - the value of the AVP
     */
    public UserPassword(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    UserPassword(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
