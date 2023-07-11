package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPConnectRedirectingNumberNPI extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPConnectRedirectingNumberNPI with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPConnectRedirectingNumberNPI(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPConnectRedirectingNumberNPI(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
