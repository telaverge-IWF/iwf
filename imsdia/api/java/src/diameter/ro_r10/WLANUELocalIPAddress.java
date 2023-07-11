package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * WLAN-UE-Local-IPAddress AVP is of type Unsigned32.
 */
public class WLANUELocalIPAddress extends com.intellinet.diameter.DerivedAVP<Address> {
    /**
     * Constructs a WLANUELocalIPAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public WLANUELocalIPAddress(Address value) {
        super(new com.intellinet.diameter.AddressData(value));
    }

    WLANUELocalIPAddress(com.intellinet.diameter.AddressData data) {
        super(data);
    }
}
