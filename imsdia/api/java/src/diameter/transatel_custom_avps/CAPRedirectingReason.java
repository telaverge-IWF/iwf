package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPRedirectingReason extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPRedirectingReason with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPRedirectingReason(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPRedirectingReason(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
