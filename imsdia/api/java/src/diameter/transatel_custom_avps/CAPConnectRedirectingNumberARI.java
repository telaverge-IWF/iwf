package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPConnectRedirectingNumberARI extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPConnectRedirectingNumberARI with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPConnectRedirectingNumberARI(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPConnectRedirectingNumberARI(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
