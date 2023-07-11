package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPConnectRedirectingReason extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPConnectRedirectingReason with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPConnectRedirectingReason(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPConnectRedirectingReason(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
