package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPBearerCapabilityTransfer extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPBearerCapabilityTransfer with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPBearerCapabilityTransfer(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CAPBearerCapabilityTransfer(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
