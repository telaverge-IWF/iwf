package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The CHAP-Challenge AVP (AVP Code 60) is of type OctetString and contains the  * CHAP Challenge sent by the NAS to the CHAP peer [PPPCHAP].
 */
public class CHAPChallenge extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CHAPChallenge with the given value.
     *
     * @param value - the value of the AVP
     */
    public CHAPChallenge(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    CHAPChallenge(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
