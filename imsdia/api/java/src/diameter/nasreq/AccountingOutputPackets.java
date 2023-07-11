package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Accounting-Output-Packets (AVP Code 366) is of type Unsigned64
 * and contains the number of IP packets sent to the user.
 * For NAS usage, this AVP indicates how many packets have been sent to
 * the port over the course of a session being provided to a Framed
 * User. It can only be present in ACR messages with an Accounting-
 * Record-Type of INTERIM_RECORD or STOP_RECORD.
 */
public class AccountingOutputPackets extends com.intellinet.diameter.DerivedAVP<Long> {
    /**
     * Constructs a AccountingOutputPackets with the given value.
     *
     * @param value - the value of the AVP
     */
    public AccountingOutputPackets(Long value) {
        super(new com.intellinet.diameter.Unsigned64Data(value));
    }

    AccountingOutputPackets(com.intellinet.diameter.Unsigned64Data data) {
        super(data);
    }
}
