package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * MBMS-Service-Area AVP is of type OctetString and indicates the area over which the MBMS bearer service
 * has to be distributed.
 */
public class MBMSServiceArea extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a MBMSServiceArea with the given value.
     *
     * @param value - the value of the AVP
     */
    public MBMSServiceArea(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    MBMSServiceArea(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
