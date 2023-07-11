package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPReleaseCause extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPReleaseCause with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPReleaseCause(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPReleaseCause(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
