package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * 3GPP-CAMEL-Charging-Info AVP is of type OctetString. It is used to copy any CAMEL
 * information present in S-CDR(s).
 */
public class Ro3GPPCAMELChargingInfo extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a Ro3GPPCAMELChargingInfo with the given value.
     *
     * @param value - the value of the AVP
     */
    public Ro3GPPCAMELChargingInfo(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    Ro3GPPCAMELChargingInfo(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
