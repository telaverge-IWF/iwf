package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPEventTypeSMS extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPEventTypeSMS with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPEventTypeSMS(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPEventTypeSMS(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
