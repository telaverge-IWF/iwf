package diameter.s6a;

import com.intellinet.diameter.*;


public class PDPType extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a PDPType with the given value.
     *
     * @param value - the value of the AVP
     */
    public PDPType(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    PDPType(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
