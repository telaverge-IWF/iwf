package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPCLI extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPCLI with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPCLI(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CAPCLI(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
