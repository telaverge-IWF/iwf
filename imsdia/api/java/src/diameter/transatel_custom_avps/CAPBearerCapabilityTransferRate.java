package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPBearerCapabilityTransferRate extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPBearerCapabilityTransferRate with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPBearerCapabilityTransferRate(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CAPBearerCapabilityTransferRate(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
