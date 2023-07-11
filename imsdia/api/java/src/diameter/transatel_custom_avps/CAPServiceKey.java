package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPServiceKey extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPServiceKey with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPServiceKey(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPServiceKey(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
