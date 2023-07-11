package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPConnectRedirectingCounter extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPConnectRedirectingCounter with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPConnectRedirectingCounter(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPConnectRedirectingCounter(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
