package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPBearerCapability extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPBearerCapability with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPBearerCapability(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    CAPBearerCapability(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
