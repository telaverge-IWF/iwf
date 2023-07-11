package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class CLRFlags extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CLRFlags with the given value.
     *
     * @param value - the value of the AVP
     */
    public CLRFlags(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CLRFlags(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
