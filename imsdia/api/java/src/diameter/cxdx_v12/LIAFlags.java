package diameter.cxdx_v12;

import com.intellinet.diameter.*;


public class LIAFlags extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a LIAFlags with the given value.
     *
     * @param value - the value of the AVP
     */
    public LIAFlags(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    LIAFlags(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
