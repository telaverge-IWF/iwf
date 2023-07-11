package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class OMCId extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a OMCId with the given value.
     *
     * @param value - the value of the AVP
     */
    public OMCId(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    OMCId(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
