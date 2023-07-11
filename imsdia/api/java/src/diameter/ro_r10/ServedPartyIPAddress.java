package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Served-Party-IP-Address AVP is of type Address and holds the IP address of either the calling or
 * called party,depending on whether the P-CSCF is in touch with the calling or the called party. 
 * This AVP is only provided by the P-CSCF.
 */
public class ServedPartyIPAddress extends com.intellinet.diameter.DerivedAVP<Address> {
    /**
     * Constructs a ServedPartyIPAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public ServedPartyIPAddress(Address value) {
        super(new com.intellinet.diameter.AddressData(value));
    }

    ServedPartyIPAddress(com.intellinet.diameter.AddressData data) {
        super(data);
    }
}
