package diameter.s6a_r11;

import com.intellinet.diameter.*;


/**
 * The Visited-PLMN-Id AVP is of type OctetString. It shall contain the concatenation 
 * of MCC and MNC. See 3GPP TS 23.003 [3].
 */
public class VisitedPLMNId extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a VisitedPLMNId with the given value.
     *
     * @param value - the value of the AVP
     */
    public VisitedPLMNId(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    VisitedPLMNId(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
