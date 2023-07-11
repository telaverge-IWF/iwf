package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPConnectOriginalCalledNumberNPI extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPConnectOriginalCalledNumberNPI with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPConnectOriginalCalledNumberNPI(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPConnectOriginalCalledNumberNPI(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
