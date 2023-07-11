package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPERBSLegId extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPERBSLegId with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPERBSLegId(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPERBSLegId(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
