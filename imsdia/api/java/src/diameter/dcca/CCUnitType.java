package diameter.dcca;

import com.intellinet.diameter.*;


/**
 * The CC-Unit-Type AVP (AVP Code 454) is of type Enumerated and specifies the type of units 
 * considered to be pooled into a credit pool.
 */
public class CCUnitType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        TIME(0),
        MONEY(1),
        TOTAL_OCTETS(2),
        INPUT_OCTETS(3),
        OUTPUT_OCTETS(4),
        SERVICE_SPECIFIC_UNITS(5);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a CCUnitType with the given value.
     *
     * @param value - the value of the AVP
     */
    public CCUnitType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    CCUnitType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
