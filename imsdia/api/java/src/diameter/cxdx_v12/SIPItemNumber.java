package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The SIP-Item-Number AVP is of type Unsigned32, and is included in a SIP-Auth-Data-Item grouped AVP in
 * circumstances where there are multiple occurrences of SIP-Auth-Data-Item AVPs, and the order in which they should
 * be processed is significant. In this scenario, SIP-Auth-Data-Item AVPs with a low SIP-Item-Number value should be
 * processed before SIP-Auth-Data-Items AVPs with a high SIP-Item-Number value.
 */
public class SIPItemNumber extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a SIPItemNumber with the given value.
     *
     * @param value - the value of the AVP
     */
    public SIPItemNumber(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    SIPItemNumber(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
