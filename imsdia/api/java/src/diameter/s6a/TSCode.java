package diameter.s6a;

import com.intellinet.diameter.*;


public class TSCode extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a TSCode with the given value.
     *
     * @param value - the value of the AVP
     */
    public TSCode(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    TSCode(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
