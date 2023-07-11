package diameter.cxdx_v12;

import com.intellinet.diameter.*;


public class DigestHA1 extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a DigestHA1 with the given value.
     *
     * @param value - the value of the AVP
     */
    public DigestHA1(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    DigestHA1(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
