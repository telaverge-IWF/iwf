package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPConnectOriginalCalledNumber extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPConnectOriginalCalledNumber with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPConnectOriginalCalledNumber(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CAPConnectOriginalCalledNumber(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
