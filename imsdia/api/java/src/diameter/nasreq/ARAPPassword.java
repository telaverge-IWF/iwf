package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The ARAP-Password AVP (AVP Code 70) is of type OctetString and is
 * only present when the Framed-Protocol AVP (see section 6.10.1) is
 * included in the message and is set to ARAP. This AVP MUST NOT be
 * present if either the User-Password or the CHAP-Auth AVP is present.
 * See [RADIUSExt] for more information on the contents of this AVP.
 */
public class ARAPPassword extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ARAPPassword with the given value.
     *
     * @param value - the value of the AVP
     */
    public ARAPPassword(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    ARAPPassword(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
