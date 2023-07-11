package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPConnectOriginalRedirectingReason extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPConnectOriginalRedirectingReason with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPConnectOriginalRedirectingReason(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPConnectOriginalRedirectingReason(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
