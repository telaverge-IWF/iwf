package diameter.cxdx_v12;

import com.intellinet.diameter.*;


public class DigestQoP extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a DigestQoP with the given value.
     *
     * @param value - the value of the AVP
     */
    public DigestQoP(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    DigestQoP(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
