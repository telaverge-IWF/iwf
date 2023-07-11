package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * PDP-Address AVP is of type Address and holds the IP-Address associated with the PDP session.
 */
public class PDPAddress extends com.intellinet.diameter.DerivedAVP<Address> {
    /**
     * Constructs a PDPAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public PDPAddress(Address value) {
        super(new com.intellinet.diameter.AddressData(value));
    }

    PDPAddress(com.intellinet.diameter.AddressData data) {
        super(data);
    }
}
