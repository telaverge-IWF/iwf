package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class ReportingTrigger extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a ReportingTrigger with the given value.
     *
     * @param value - the value of the AVP
     */
    public ReportingTrigger(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    ReportingTrigger(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
