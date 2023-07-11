package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPIMSI extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPIMSI with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPIMSI(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CAPIMSI(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
