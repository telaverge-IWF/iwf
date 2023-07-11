package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class S6a3GPP2MEID extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a S6a3GPP2MEID with the given value.
     *
     * @param value - the value of the AVP
     */
    public S6a3GPP2MEID(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    S6a3GPP2MEID(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
