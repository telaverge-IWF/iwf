package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPConnectGenericNumberNQI extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPConnectGenericNumberNQI with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPConnectGenericNumberNQI(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPConnectGenericNumberNQI(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
