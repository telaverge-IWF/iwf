package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Low-Balance-Indication AVP (AVP code 2020) is of type Enumerated and 
 * indicates if the subscriber balance went below a designated threshold by 
 * its account
 */
public class LowBalanceIndication extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        NOT_APPLICABLE(0),
        YES(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a LowBalanceIndication with the given value.
     *
     * @param value - the value of the AVP
     */
    public LowBalanceIndication(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    LowBalanceIndication(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
