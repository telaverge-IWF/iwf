package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Client-Address AVP (AVP code 2018) is of type Address and is the address of the messaging Node which the OCS is connected to.
 */
public class ClientAddress extends com.intellinet.diameter.DerivedAVP<Address> {
    /**
     * Constructs a ClientAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public ClientAddress(Address value) {
        super(new com.intellinet.diameter.AddressData(value));
    }

    ClientAddress(com.intellinet.diameter.AddressData data) {
        super(data);
    }
}
