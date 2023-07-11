package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class PURFlags extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a PURFlags with the given value.
     *
     * @param value - the value of the AVP
     */
    public PURFlags(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    PURFlags(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
