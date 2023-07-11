package diameter.cxdx_v12;

import com.intellinet.diameter.*;


public class UARFlags extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a UARFlags with the given value.
     *
     * @param value - the value of the AVP
     */
    public UARFlags(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    UARFlags(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
