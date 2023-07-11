package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPCLIR extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPCLIR with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPCLIR(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPCLIR(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
