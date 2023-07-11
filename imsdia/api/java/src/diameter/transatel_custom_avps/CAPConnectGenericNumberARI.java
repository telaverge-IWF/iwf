package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPConnectGenericNumberARI extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPConnectGenericNumberARI with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPConnectGenericNumberARI(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPConnectGenericNumberARI(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
