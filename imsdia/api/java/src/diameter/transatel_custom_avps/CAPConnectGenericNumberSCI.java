package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPConnectGenericNumberSCI extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPConnectGenericNumberSCI with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPConnectGenericNumberSCI(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPConnectGenericNumberSCI(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
