package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPConnectGenericNumber extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPConnectGenericNumber with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPConnectGenericNumber(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CAPConnectGenericNumber(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
