package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPRRBSNoAnswerTimeout extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPRRBSNoAnswerTimeout with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPRRBSNoAnswerTimeout(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPRRBSNoAnswerTimeout(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
