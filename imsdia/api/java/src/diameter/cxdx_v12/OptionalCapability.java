package diameter.cxdx_v12;

import com.intellinet.diameter.*;


/**
 * The Optional-Capability AVP is of type Unsigned32. The value included in this AVP can be used to represent a single
 * determined optional capability of an S-CSCF. Each optional capability available in an individual operator��s network
 * shall be allocated a unique value. The allocation of these values to individual capabilities is an operator issue.
 */
public class OptionalCapability extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a OptionalCapability with the given value.
     *
     * @param value - the value of the AVP
     */
    public OptionalCapability(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    OptionalCapability(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
