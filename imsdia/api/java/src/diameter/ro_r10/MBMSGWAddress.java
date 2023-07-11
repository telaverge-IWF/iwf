package diameter.ro_r10;

import com.intellinet.diameter.*;


/** 
 * The MBMS GW-Address AVP (AVP code 2307) is of type Address and holds the IP-address . 
 * This AVP of the MBMS GW that generated the MBMS Charging ID when MBMS GW is stand-alone.
 */
public class MBMSGWAddress extends com.intellinet.diameter.DerivedAVP<Address> {
    /**
     * Constructs a MBMSGWAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public MBMSGWAddress(Address value) {
        super(new com.intellinet.diameter.AddressData(value));
    }

    MBMSGWAddress(com.intellinet.diameter.AddressData data) {
        super(data);
    }
}
