package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPCLINPI extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPCLINPI with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPCLINPI(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPCLINPI(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
