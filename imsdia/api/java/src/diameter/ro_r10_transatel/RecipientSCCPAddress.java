package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Recipient-SCCP-Address AVP (AVP code 2010) is of type Address. It is the "SCCP called address" used by the messaging node when delivering the message. It can contain either an SSN, a Point Code (ISPC) or a Global Title, where Global Title represents an E.164 number.
  */
public class RecipientSCCPAddress extends com.intellinet.diameter.DerivedAVP<Address> {
    /**
     * Constructs a RecipientSCCPAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public RecipientSCCPAddress(Address value) {
        super(new com.intellinet.diameter.AddressData(value));
    }

    RecipientSCCPAddress(com.intellinet.diameter.AddressData data) {
        super(data);
    }
}
