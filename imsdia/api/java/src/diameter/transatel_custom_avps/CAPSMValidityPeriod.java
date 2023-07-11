package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPSMValidityPeriod extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPSMValidityPeriod with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPSMValidityPeriod(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CAPSMValidityPeriod(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
