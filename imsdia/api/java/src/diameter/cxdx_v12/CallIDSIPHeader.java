package diameter.cxdx_v12;

import com.intellinet.diameter.*;


public class CallIDSIPHeader extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CallIDSIPHeader with the given value.
     *
     * @param value - the value of the AVP
     */
    public CallIDSIPHeader(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    CallIDSIPHeader(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
