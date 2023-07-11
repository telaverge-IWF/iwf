package diameter.s6a;

import com.intellinet.diameter.*;


public class GMLCNumber extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a GMLCNumber with the given value.
     *
     * @param value - the value of the AVP
     */
    public GMLCNumber(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    GMLCNumber(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
