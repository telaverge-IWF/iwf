package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPRedirectionCounter extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPRedirectionCounter with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPRedirectionCounter(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPRedirectionCounter(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
