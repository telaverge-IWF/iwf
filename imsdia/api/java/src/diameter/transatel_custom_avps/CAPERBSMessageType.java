package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPERBSMessageType extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPERBSMessageType with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPERBSMessageType(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPERBSMessageType(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
