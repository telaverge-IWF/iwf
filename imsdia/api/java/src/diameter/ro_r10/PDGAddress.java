package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * PDG-Address AVP is of type Address and contains the PDG IP address.
 */
public class PDGAddress extends com.intellinet.diameter.DerivedAVP<Address> {
    /**
     * Constructs a PDGAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public PDGAddress(Address value) {
        super(new com.intellinet.diameter.AddressData(value));
    }

    PDGAddress(com.intellinet.diameter.AddressData data) {
        super(data);
    }
}
