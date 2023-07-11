package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPConnectGenericNumberNOA extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPConnectGenericNumberNOA with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPConnectGenericNumberNOA(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPConnectGenericNumberNOA(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
