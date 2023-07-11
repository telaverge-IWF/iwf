package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPConnectRedirectingIndicator extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPConnectRedirectingIndicator with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPConnectRedirectingIndicator(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPConnectRedirectingIndicator(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
