package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * WAG-Address AVP is of type Address and contains the WAG IP address.
 */
public class WAGAddress extends com.intellinet.diameter.DerivedAVP<Address> {
    /**
     * Constructs a WAGAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public WAGAddress(Address value) {
        super(new com.intellinet.diameter.AddressData(value));
    }

    WAGAddress(com.intellinet.diameter.AddressData data) {
        super(data);
    }
}
