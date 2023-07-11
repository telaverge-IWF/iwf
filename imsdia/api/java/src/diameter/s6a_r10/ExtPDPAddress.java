package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class ExtPDPAddress extends com.intellinet.diameter.DerivedAVP<Address> {
    /**
     * Constructs a ExtPDPAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public ExtPDPAddress(Address value) {
        super(new com.intellinet.diameter.AddressData(value));
    }

    ExtPDPAddress(com.intellinet.diameter.AddressData data) {
        super(data);
    }
}
