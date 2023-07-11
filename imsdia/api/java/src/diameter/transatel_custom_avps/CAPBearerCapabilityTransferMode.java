package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPBearerCapabilityTransferMode extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPBearerCapabilityTransferMode with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPBearerCapabilityTransferMode(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CAPBearerCapabilityTransferMode(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
