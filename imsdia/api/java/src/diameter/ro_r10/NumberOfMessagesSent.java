package diameter.ro_r10;

import com.intellinet.diameter.*;


public class NumberOfMessagesSent extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a NumberOfMessagesSent with the given value.
     *
     * @param value - the value of the AVP
     */
    public NumberOfMessagesSent(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    NumberOfMessagesSent(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
