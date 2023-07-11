package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPConnectDestinationNumberNPI extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPConnectDestinationNumberNPI with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPConnectDestinationNumberNPI(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPConnectDestinationNumberNPI(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
