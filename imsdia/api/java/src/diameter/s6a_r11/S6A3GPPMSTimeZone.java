package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class S6A3GPPMSTimeZone extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a S6A3GPPMSTimeZone with the given value.
     *
     * @param value - the value of the AVP
     */
    public S6A3GPPMSTimeZone(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    S6A3GPPMSTimeZone(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
