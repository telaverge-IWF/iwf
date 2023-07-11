package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The SM-User-Data-Header AVP (AVP code 2015) is of type OctetString and 
 * contains any user data header extracted from the user data part of the SM.
 *  Encoding is as described in 3GPP TS 23.040 [216]. 
 * Any padding bits are not considered part of the header and are omitted.
 */
public class SMUserDataHeader extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a SMUserDataHeader with the given value.
     *
     * @param value - the value of the AVP
     */
    public SMUserDataHeader(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    SMUserDataHeader(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
