package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPDialedDigits extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPDialedDigits with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPDialedDigits(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CAPDialedDigits(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
