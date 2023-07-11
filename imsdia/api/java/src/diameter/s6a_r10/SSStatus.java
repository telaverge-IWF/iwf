package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class SSStatus extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a SSStatus with the given value.
     *
     * @param value - the value of the AVP
     */
    public SSStatus(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    SSStatus(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
