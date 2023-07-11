package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class EUTRANCellGlobalIdentity extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a EUTRANCellGlobalIdentity with the given value.
     *
     * @param value - the value of the AVP
     */
    public EUTRANCellGlobalIdentity(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    EUTRANCellGlobalIdentity(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
