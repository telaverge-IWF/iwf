package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPConnectGenericNumberNII extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPConnectGenericNumberNII with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPConnectGenericNumberNII(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPConnectGenericNumberNII(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
