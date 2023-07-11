package diameter.ro_r10;

import com.intellinet.diameter.*;


public class NumberOfMessagesSuccessfullySent extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a NumberOfMessagesSuccessfullySent with the given value.
     *
     * @param value - the value of the AVP
     */
    public NumberOfMessagesSuccessfullySent(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    NumberOfMessagesSuccessfullySent(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
