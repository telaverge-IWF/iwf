package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPSMMessageTypeIndicator extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPSMMessageTypeIndicator with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPSMMessageTypeIndicator(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CAPSMMessageTypeIndicator(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
