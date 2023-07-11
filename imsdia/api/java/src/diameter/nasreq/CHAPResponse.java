package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The CHAP-Response AVP (AVP Code 405) is of type OctetString and
 * contains the 16 octet authentication data provided by the user in
 * response to the CHAP challenge [PPPCHAP].
 */
public class CHAPResponse extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CHAPResponse with the given value.
     *
     * @param value - the value of the AVP
     */
    public CHAPResponse(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    CHAPResponse(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
