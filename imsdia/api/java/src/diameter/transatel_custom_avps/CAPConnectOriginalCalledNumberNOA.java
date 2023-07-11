package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPConnectOriginalCalledNumberNOA extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPConnectOriginalCalledNumberNOA with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPConnectOriginalCalledNumberNOA(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPConnectOriginalCalledNumberNOA(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
