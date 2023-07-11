package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class SSCode extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a SSCode with the given value.
     *
     * @param value - the value of the AVP
     */
    public SSCode(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    SSCode(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
