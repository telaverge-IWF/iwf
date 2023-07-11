package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPSMVPFormat extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPSMVPFormat with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPSMVPFormat(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CAPSMVPFormat(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
