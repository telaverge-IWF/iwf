package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Accounting-Input-Packets (AVP Code 365) is of type Unsigned64 and
 * contains the number of packets received from the user.
 * For NAS usage, this AVP indicates how many packets have been received
 * from the port over the course of a session being provided to a Framed
 * User. It can only be present in ACR messages with an Accounting-
 * Record-Type of INTERIM_RECORD or STOP_RECORD.
 */
public class AccountingInputPackets extends com.intellinet.diameter.DerivedAVP<Long> {
    /**
     * Constructs a AccountingInputPackets with the given value.
     *
     * @param value - the value of the AVP
     */
    public AccountingInputPackets(Long value) {
        super(new com.intellinet.diameter.Unsigned64Data(value));
    }

    AccountingInputPackets(com.intellinet.diameter.Unsigned64Data data) {
        super(data);
    }
}
