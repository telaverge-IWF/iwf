package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPVersion extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPVersion with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPVersion(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPVersion(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
