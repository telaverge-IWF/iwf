package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class ExpirationDate extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a ExpirationDate with the given value.
     *
     * @param value - the value of the AVP
     */
    public ExpirationDate(Integer value) {
        super(new com.intellinet.diameter.TimeData(value));
    }

    ExpirationDate(com.intellinet.diameter.TimeData data) {
        super(data);
    }
}
