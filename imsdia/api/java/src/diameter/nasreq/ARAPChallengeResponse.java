package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The ARAP-Challenge-Response AVP (AVP Code 84) is of type OctetString
 * and is only present when the Framed-Protocol AVP (see section 6.10.1)
 * is included in the message and is set to ARAP. This AVP contains an
 * 8 octet response to the dial-in client's challenge. The RADIUS
 * server calculates this value by taking the dial-in client's challenge
 * from the high-order 8 octets of the ARAP-Password AVP and performing
 * DES encryption on this value with the authenticating user's password
 * as the key. If the user's password is fewer than 8 octets in length,
 * the password is padded at the end with NULL octets to a length of 8
 * before it is used as a key.
 */
public class ARAPChallengeResponse extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ARAPChallengeResponse with the given value.
     *
     * @param value - the value of the AVP
     */
    public ARAPChallengeResponse(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    ARAPChallengeResponse(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
