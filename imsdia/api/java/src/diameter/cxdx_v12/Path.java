package diameter.cxdx_v12;

import com.intellinet.diameter.*;


public class Path extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a Path with the given value.
     *
     * @param value - the value of the AVP
     */
    public Path(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    Path(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
