package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Accounting-Output-Octets AVP (AVP Code 364) is of type Unsigned64
 * and contains the number of octets sent to the user.
 * For NAS usage, this AVP indicates how many octets have been sent to
 * the port in the course of this session. It can only be present in
 * ACR messages with an Accounting-Record-Type of INTERIM_RECORD or
 * STOP_RECORD.
 */
public class AccountingOutputOctets extends com.intellinet.diameter.DerivedAVP<Long> {
    /**
     * Constructs a AccountingOutputOctets with the given value.
     *
     * @param value - the value of the AVP
     */
    public AccountingOutputOctets(Long value) {
        super(new com.intellinet.diameter.Unsigned64Data(value));
    }

    AccountingOutputOctets(com.intellinet.diameter.Unsigned64Data data) {
        super(data);
    }
}
