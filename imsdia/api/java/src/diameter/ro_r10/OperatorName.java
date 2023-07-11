package diameter.ro_r10;

import com.intellinet.diameter.*;


public class OperatorName extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a OperatorName with the given value.
     *
     * @param value - the value of the AVP
     */
    public OperatorName(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    OperatorName(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
