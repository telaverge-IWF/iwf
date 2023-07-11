package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPSMRejectDuplicate extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPSMRejectDuplicate with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPSMRejectDuplicate(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CAPSMRejectDuplicate(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
