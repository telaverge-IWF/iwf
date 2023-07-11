package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPSMDCS extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CAPSMDCS with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPSMDCS(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    CAPSMDCS(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
