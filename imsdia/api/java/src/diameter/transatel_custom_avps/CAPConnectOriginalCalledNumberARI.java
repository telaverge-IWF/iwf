package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPConnectOriginalCalledNumberARI extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPConnectOriginalCalledNumberARI with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPConnectOriginalCalledNumberARI(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPConnectOriginalCalledNumberARI(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
