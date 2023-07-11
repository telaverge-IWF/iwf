package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * SGSN-Address AVP is of type Address and holds the IP-Address fo the SGSN that was
 * used during a report.
 */
public class SGSNAddress extends com.intellinet.diameter.DerivedAVP<Address> {
    /**
     * Constructs a SGSNAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public SGSNAddress(Address value) {
        super(new com.intellinet.diameter.AddressData(value));
    }

    SGSNAddress(com.intellinet.diameter.AddressData data) {
        super(data);
    }
}
