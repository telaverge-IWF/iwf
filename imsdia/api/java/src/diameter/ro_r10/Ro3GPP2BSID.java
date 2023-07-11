package diameter.ro_r10;

import com.intellinet.diameter.*;


public class Ro3GPP2BSID extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a Ro3GPP2BSID with the given value.
     *
     * @param value - the value of the AVP
     */
    public Ro3GPP2BSID(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    Ro3GPP2BSID(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
