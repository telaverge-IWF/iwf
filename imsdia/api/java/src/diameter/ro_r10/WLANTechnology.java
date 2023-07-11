package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * WLAN-Technology is of type Unsigned32.
 */
public class WLANTechnology extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a WLANTechnology with the given value.
     *
     * @param value - the value of the AVP
     */
    public WLANTechnology(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    WLANTechnology(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
