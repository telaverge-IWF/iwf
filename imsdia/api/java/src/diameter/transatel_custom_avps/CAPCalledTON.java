package diameter.transatel_custom_avps;

import com.intellinet.diameter.*;


public class CAPCalledTON extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a CAPCalledTON with the given value.
     *
     * @param value - the value of the AVP
     */
    public CAPCalledTON(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    CAPCalledTON(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
