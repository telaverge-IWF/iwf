package diameter.cxdx_v12;

import com.intellinet.diameter.*;


public class LineIdentifier extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a LineIdentifier with the given value.
     *
     * @param value - the value of the AVP
     */
    public LineIdentifier(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    LineIdentifier(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
