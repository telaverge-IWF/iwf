package diameter.ro_r10;

import com.intellinet.diameter.*;


public class NumberOfMessagesSuccessfullyExploded extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a NumberOfMessagesSuccessfullyExploded with the given value.
     *
     * @param value - the value of the AVP
     */
    public NumberOfMessagesSuccessfullyExploded(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    NumberOfMessagesSuccessfullyExploded(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
