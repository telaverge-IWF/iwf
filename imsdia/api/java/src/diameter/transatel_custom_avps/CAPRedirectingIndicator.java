package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPRedirectingIndicator extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPRedirectingIndicator with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPRedirectingIndicator(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPRedirectingIndicator(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
