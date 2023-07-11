package diameter.cxdx_v12;

import com.intellinet.diameter.*;


public class FromSIPHeader extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a FromSIPHeader with the given value.
     *
     * @param value - the value of the AVP
     */
    public FromSIPHeader(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    FromSIPHeader(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
