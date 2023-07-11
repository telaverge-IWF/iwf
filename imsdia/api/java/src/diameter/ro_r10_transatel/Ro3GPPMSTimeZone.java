package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * 3GPP-MS-TimeZone AVP is of type OctetString. It indicates the offset between universal 
 * time and local time in steps of 15 minutes of where the MS currently resides.
 */
public class Ro3GPPMSTimeZone extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a Ro3GPPMSTimeZone with the given value.
     *
     * @param value - the value of the AVP
     */
    public Ro3GPPMSTimeZone(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    Ro3GPPMSTimeZone(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
