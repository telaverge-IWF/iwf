package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPLocationNumber extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPLocationNumber with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPLocationNumber(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CAPLocationNumber(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
