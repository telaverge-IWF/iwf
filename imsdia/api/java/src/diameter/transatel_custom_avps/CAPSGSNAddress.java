package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPSGSNAddress extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPSGSNAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPSGSNAddress(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CAPSGSNAddress(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
