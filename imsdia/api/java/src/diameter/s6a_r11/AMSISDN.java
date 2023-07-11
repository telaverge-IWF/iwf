package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class AMSISDN extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a AMSISDN with the given value.
     *
     * @param value - the value of the AVP
     */
    public AMSISDN(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    AMSISDN(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
