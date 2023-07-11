package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPSMSCAddress extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPSMSCAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPSMSCAddress(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CAPSMSCAddress(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
