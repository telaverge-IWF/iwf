package diameter.ro_r10;

import com.intellinet.diameter.*;


public class Ro3GPPIMSI extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a Ro3GPPIMSI with the given value.
     *
     * @param value - the value of the AVP
     */
    public Ro3GPPIMSI(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    Ro3GPPIMSI(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
