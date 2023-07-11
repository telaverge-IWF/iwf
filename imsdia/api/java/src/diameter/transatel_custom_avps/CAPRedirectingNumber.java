package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPRedirectingNumber extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPRedirectingNumber with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPRedirectingNumber(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CAPRedirectingNumber(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
