package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Redirect-Address-Type AVP (AVP Code 433) is of type Enumerated and defines the address
 * type of the address given in the Redirect-Server-Address AVP.
 */
public class RedirectAddressType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        IPv4_Address(0),
        IPv6_Address(1),
        URLocation(2),
        SIP_URI(3);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a RedirectAddressType with the given value.
     *
     * @param value - the value of the AVP
     */
    public RedirectAddressType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    RedirectAddressType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
