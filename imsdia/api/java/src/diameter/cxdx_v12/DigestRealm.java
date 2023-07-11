package diameter.cxdx_v12;

import com.intellinet.diameter.*;


public class DigestRealm extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a DigestRealm with the given value.
     *
     * @param value - the value of the AVP
     */
    public DigestRealm(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    DigestRealm(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
