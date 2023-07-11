package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPSMProtocolID extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPSMProtocolID with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPSMProtocolID(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CAPSMProtocolID(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
