package diameter.cxdx_v12;

import com.intellinet.diameter.*;


public class ToSIPHeader extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ToSIPHeader with the given value.
     *
     * @param value - the value of the AVP
     */
    public ToSIPHeader(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    ToSIPHeader(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
