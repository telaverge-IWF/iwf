package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * CG-Address AVP is of type Address and holds the IP-address of the charging gateway.
 */
public class CGAddress extends com.intellinet.diameter.DerivedAVP<Address> {
    /**
     * Constructs a CGAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public CGAddress(Address value) {
        super(new com.intellinet.diameter.AddressData(value));
    }

    CGAddress(com.intellinet.diameter.AddressData data) {
        super(data);
    }
}
