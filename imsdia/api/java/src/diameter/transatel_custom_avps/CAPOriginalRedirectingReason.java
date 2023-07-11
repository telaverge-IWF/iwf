package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPOriginalRedirectingReason extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPOriginalRedirectingReason with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPOriginalRedirectingReason(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPOriginalRedirectingReason(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
