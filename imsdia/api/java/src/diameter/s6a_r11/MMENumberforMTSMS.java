package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class MMENumberforMTSMS extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a MMENumberforMTSMS with the given value.
     *
     * @param value - the value of the AVP
     */
    public MMENumberforMTSMS(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    MMENumberforMTSMS(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
