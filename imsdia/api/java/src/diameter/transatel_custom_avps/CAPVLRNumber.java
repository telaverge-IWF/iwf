package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPVLRNumber extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPVLRNumber with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPVLRNumber(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CAPVLRNumber(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
