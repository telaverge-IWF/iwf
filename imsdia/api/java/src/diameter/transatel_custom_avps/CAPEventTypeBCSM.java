package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPEventTypeBCSM extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPEventTypeBCSM with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPEventTypeBCSM(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPEventTypeBCSM(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
