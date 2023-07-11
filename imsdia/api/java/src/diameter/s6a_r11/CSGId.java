package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class CSGId extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CSGId with the given value.
     *
     * @param value - the value of the AVP
     */
    public CSGId(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CSGId(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
