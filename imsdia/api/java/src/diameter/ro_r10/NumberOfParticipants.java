package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Number-Of-Participants AVP is of type Unsigned32  and holds the number of invited parties of the PoC session.
 */
public class NumberOfParticipants extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a NumberOfParticipants with the given value.
     *
     * @param value - the value of the AVP
     */
    public NumberOfParticipants(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    NumberOfParticipants(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
