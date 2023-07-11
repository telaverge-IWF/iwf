package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


public class TotalNumberOfMessagesSent extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a TotalNumberOfMessagesSent with the given value.
     *
     * @param value - the value of the AVP
     */
    public TotalNumberOfMessagesSent(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    TotalNumberOfMessagesSent(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
