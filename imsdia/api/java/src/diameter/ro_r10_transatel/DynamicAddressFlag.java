package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Dynamic-Address-Flag AVP(AVP code 2051)  is of type Enumerated, and  
 * indicates whether the PDP context/PDN address is statically or dynamically 
 * allocated.
 */
public class DynamicAddressFlag extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        Static(0),
        Dynamic(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a DynamicAddressFlag with the given value.
     *
     * @param value - the value of the AVP
     */
    public DynamicAddressFlag(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    DynamicAddressFlag(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
