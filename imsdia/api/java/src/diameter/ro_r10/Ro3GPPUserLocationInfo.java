package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * 3GPP-User-Location-Info AVP is of type Octetstring. It indicates details of where the
 *  UE is currenly located (e.g SAI or CGI).
 */
public class Ro3GPPUserLocationInfo extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a Ro3GPPUserLocationInfo with the given value.
     *
     * @param value - the value of the AVP
     */
    public Ro3GPPUserLocationInfo(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    Ro3GPPUserLocationInfo(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
