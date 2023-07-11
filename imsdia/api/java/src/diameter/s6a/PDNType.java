package diameter.s6a;

import com.intellinet.diameter.*;


/**
 * The PDN-Type AVP is of type Enumerated and indicates the address type of PDN. 
 * The following values are defined:
 *   IPv4 (0)
 *   IPv6 (1)
 *   IPv4v62)
 */
public class PDNType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        IPv4(0),
        IPv6(1),
        IPv4v6(2);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a PDNType with the given value.
     *
     * @param value - the value of the AVP
     */
    public PDNType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    PDNType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
