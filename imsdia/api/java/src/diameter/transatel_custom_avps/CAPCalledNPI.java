package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPCalledNPI extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPCalledNPI with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPCalledNPI(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPCalledNPI(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
