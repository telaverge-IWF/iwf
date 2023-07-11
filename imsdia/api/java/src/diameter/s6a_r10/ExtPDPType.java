package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class ExtPDPType extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a ExtPDPType with the given value.
     *
     * @param value - the value of the AVP
     */
    public ExtPDPType(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    ExtPDPType(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
