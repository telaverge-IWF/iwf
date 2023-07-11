package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPCallReference extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPCallReference with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPCallReference(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    CAPCallReference(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
