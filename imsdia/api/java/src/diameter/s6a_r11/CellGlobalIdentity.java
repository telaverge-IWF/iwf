package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class CellGlobalIdentity extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a CellGlobalIdentity with the given value.
     *
     * @param value - the value of the AVP
     */
    public CellGlobalIdentity(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    CellGlobalIdentity(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
