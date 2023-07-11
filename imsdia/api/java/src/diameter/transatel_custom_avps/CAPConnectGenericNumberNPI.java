package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPConnectGenericNumberNPI extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPConnectGenericNumberNPI with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPConnectGenericNumberNPI(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPConnectGenericNumberNPI(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
