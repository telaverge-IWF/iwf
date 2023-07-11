package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The CSG-Access-Mode AVP (AVP code 2317) is of type Enumerated and holds the mode 
 * in which the CSG cell User is accessing to, operates.
 */
public class CSGAccessMode extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        Closed_mode(0),
        Hybrid_Mode(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a CSGAccessMode with the given value.
     *
     * @param value - the value of the AVP
     */
    public CSGAccessMode(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    CSGAccessMode(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
