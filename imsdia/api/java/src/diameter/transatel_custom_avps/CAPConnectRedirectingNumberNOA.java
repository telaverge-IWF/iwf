package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPConnectRedirectingNumberNOA extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPConnectRedirectingNumberNOA with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPConnectRedirectingNumberNOA(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPConnectRedirectingNumberNOA(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
