package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Address-Type AVP is of type Enumerated and indicates the type of address carried within the 
 * Address-Information AVP.
 */
public class IMSAddressType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        e_mail_address(0),
        MSISDN(1),
        IPv4_Address(2),
        IPv6_Address(3),
        Numeric_Shortcode(4),
        Alphanumeric_Shortcode(5),
        Other(6),
        IMSI(7);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a IMSAddressType with the given value.
     *
     * @param value - the value of the AVP
     */
    public IMSAddressType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    IMSAddressType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
