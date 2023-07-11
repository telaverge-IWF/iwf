package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Accounting-Input-Octets AVP (AVP Code 363) is of type Unsigned64
 * and contains the number of octets received from the user.
 * For NAS usage, this AVP indicates how many octets have been received
 * from the port in the course of this session. It can only be present
 * in ACR messages with an Accounting-Record-Type of INTERIM_RECORD or
 * STOP_RECORD.
 */
public class AccountingInputOctets extends com.intellinet.diameter.DerivedAVP<Long> {
    /**
     * Constructs a AccountingInputOctets with the given value.
     *
     * @param value - the value of the AVP
     */
    public AccountingInputOctets(Long value) {
        super(new com.intellinet.diameter.Unsigned64Data(value));
    }

    AccountingInputOctets(com.intellinet.diameter.Unsigned64Data data) {
        super(data);
    }
}
