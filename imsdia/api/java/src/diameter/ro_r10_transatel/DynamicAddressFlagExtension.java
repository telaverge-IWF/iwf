package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Dynamic-Address-Flag-Extension AVP (AVP code 2068) is of type Enumerated, and  indicates that 
 * the IPv4 PDN address has been dynamically allocated for that particular IP CAN bearer (PDN connection) 
 * of PDN type IPv4v6, and the dynamic IPv6 address is indicated in Dynamic Address Flag. This field is missing 
 * if IPv4 address is static. 
 */
public class DynamicAddressFlagExtension extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        Static(0),
        Dynamic(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a DynamicAddressFlagExtension with the given value.
     *
     * @param value - the value of the AVP
     */
    public DynamicAddressFlagExtension(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    DynamicAddressFlagExtension(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
