package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPSCCPErrorCause extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPSCCPErrorCause with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPSCCPErrorCause(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPSCCPErrorCause(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
