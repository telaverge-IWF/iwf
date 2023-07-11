package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Originator-SCCP-Address AVP (AVP code 2008) is of type Address. It is the "SCCP calling address" used by the messaging node when receiving a message. It can contain either an SSN, a Point Code (ISPC) or a Global Title, where Global Title represents an E.164 number.
 */
public class OriginatorSCCPAddress extends com.intellinet.diameter.DerivedAVP<Address> {
    /**
     * Constructs a OriginatorSCCPAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public OriginatorSCCPAddress(Address value) {
        super(new com.intellinet.diameter.AddressData(value));
    }

    OriginatorSCCPAddress(com.intellinet.diameter.AddressData data) {
        super(data);
    }
}
