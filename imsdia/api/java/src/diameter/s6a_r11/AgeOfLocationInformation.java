package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class AgeOfLocationInformation extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a AgeOfLocationInformation with the given value.
     *
     * @param value - the value of the AVP
     */
    public AgeOfLocationInformation(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    AgeOfLocationInformation(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
