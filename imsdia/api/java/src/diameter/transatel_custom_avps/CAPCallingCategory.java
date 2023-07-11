package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPCallingCategory extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPCallingCategory with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPCallingCategory(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPCallingCategory(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
