package diameter.s6a_r11;

import com.intellinet.diameter.*;


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
