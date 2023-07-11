package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPSMUserDataHeaderIndicator extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPSMUserDataHeaderIndicator with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPSMUserDataHeaderIndicator(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CAPSMUserDataHeaderIndicator(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
