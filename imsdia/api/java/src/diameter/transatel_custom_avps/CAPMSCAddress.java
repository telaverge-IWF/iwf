package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPMSCAddress extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPMSCAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPMSCAddress(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CAPMSCAddress(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
