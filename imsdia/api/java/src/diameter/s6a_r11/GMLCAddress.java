package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class GMLCAddress extends com.intellinet.diameter.DerivedAVP<Address> {
    /**
     * Constructs a GMLCAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public GMLCAddress(Address value) {
        super(new com.intellinet.diameter.AddressData(value));
    }

    GMLCAddress(com.intellinet.diameter.AddressData data) {
        super(data);
    }
}
