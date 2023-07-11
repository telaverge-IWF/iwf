package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPIMEI extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPIMEI with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPIMEI(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CAPIMEI(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
