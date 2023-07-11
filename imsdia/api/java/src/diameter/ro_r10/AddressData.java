package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Address-Data AVP is of type UTF8String and indicates the address information and formatted
 * according type of address indicated in the Address-Type and according to MMS encapsulation.
 */
public class AddressData extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a AddressData with the given value.
     *
     * @param value - the value of the AVP
     */
    public AddressData(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    AddressData(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
