package diameter.cxdx_v12;

import com.intellinet.diameter.*;


public class FramedIPv6Prefix extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a FramedIPv6Prefix with the given value.
     *
     * @param value - the value of the AVP
     */
    public FramedIPv6Prefix(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    FramedIPv6Prefix(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
