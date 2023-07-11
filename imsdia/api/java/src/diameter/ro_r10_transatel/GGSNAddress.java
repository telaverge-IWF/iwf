package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * GGSN-Address AVP is of type Address and holds the IP-Address of the GGSN that generated 
 * the GPRS Charging ID.
 */
public class GGSNAddress extends com.intellinet.diameter.DerivedAVP<Address> {
    /**
     * Constructs a GGSNAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public GGSNAddress(Address value) {
        super(new com.intellinet.diameter.AddressData(value));
    }

    GGSNAddress(com.intellinet.diameter.AddressData data) {
        super(data);
    }
}
