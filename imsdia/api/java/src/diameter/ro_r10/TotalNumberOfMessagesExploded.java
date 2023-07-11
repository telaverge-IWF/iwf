package diameter.ro_r10;

import com.intellinet.diameter.*;


public class TotalNumberOfMessagesExploded extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a TotalNumberOfMessagesExploded with the given value.
     *
     * @param value - the value of the AVP
     */
    public TotalNumberOfMessagesExploded(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    TotalNumberOfMessagesExploded(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
