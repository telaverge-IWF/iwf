package diameter.cxdx_v12;

import com.intellinet.diameter.*;


public class DigestAlgorithm extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a DigestAlgorithm with the given value.
     *
     * @param value - the value of the AVP
     */
    public DigestAlgorithm(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    DigestAlgorithm(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
