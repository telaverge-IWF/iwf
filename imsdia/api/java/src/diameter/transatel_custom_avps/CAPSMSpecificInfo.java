package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPSMSpecificInfo extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPSMSpecificInfo with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPSMSpecificInfo(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    CAPSMSpecificInfo(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
