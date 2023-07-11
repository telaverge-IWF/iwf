package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The SMSC-Address AVP (AVP code 2017) is of type Address and carries the address of the SMSC, as contained in the SM.
 */
public class SMSCAddress extends com.intellinet.diameter.DerivedAVP<Address> {
    /**
     * Constructs a SMSCAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public SMSCAddress(Address value) {
        super(new com.intellinet.diameter.AddressData(value));
    }

    SMSCAddress(com.intellinet.diameter.AddressData data) {
        super(data);
    }
}
