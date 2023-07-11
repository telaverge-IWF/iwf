package diameter.s6a_r10;

import com.intellinet.diameter.*;


/**
 * The VPLMN Dynamic Address Allowed AVP is of type Enumerated. It indicates whether 
 * the UE is allowed to use a dynamic address allocated in the VPLMN. If this AVP is 
 * not present, this means that the UE is not allowed to use these kind of addresses. 
 * The following values are defined:
 *	NOTALLOWED (0)
 *	ALLOWED (1)
 */
public class VPLMNDynamicAddressAllowed extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        NOTALLOWED(0),
        ALLOWED(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a VPLMNDynamicAddressAllowed with the given value.
     *
     * @param value - the value of the AVP
     */
    public VPLMNDynamicAddressAllowed(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    VPLMNDynamicAddressAllowed(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
