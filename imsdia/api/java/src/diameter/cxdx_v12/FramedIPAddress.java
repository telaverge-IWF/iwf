package diameter.cxdx_v12;

import com.intellinet.diameter.*;


public class FramedIPAddress extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a FramedIPAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public FramedIPAddress(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    FramedIPAddress(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
