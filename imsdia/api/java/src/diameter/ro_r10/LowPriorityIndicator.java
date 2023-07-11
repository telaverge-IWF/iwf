package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The Low-Priority-Indicator AVP (AVP code 2602) is of type Enumerated and indicates if the PDN 
 * connection has a low priority, i.e. for Machine Type Communications.
 r
 */
public class LowPriorityIndicator extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        NO(0),
        YES(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a LowPriorityIndicator with the given value.
     *
     * @param value - the value of the AVP
     */
    public LowPriorityIndicator(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    LowPriorityIndicator(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
