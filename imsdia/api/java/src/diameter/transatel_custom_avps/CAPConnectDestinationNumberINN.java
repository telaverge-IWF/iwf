package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPConnectDestinationNumberINN extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPConnectDestinationNumberINN with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPConnectDestinationNumberINN(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPConnectDestinationNumberINN(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
