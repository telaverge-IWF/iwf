package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
* The SGW-Address AVP (AVP code 2067) is of type Address and holds the IP-address of the SGW Node.
*/
public class SGWAddress extends com.intellinet.diameter.DerivedAVP<Address> {
    /**
     * Constructs a SGWAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public SGWAddress(Address value) {
        super(new com.intellinet.diameter.AddressData(value));
    }

    SGWAddress(com.intellinet.diameter.AddressData data) {
        super(data);
    }
}
