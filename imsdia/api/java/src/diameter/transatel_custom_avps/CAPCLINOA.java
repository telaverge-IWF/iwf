package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPCLINOA extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPCLINOA with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPCLINOA(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPCLINOA(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
