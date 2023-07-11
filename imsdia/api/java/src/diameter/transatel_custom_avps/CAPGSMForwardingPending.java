package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPGSMForwardingPending extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPGSMForwardingPending with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPGSMForwardingPending(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPGSMForwardingPending(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
