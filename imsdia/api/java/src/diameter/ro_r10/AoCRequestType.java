package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * The AoC-Request-Type AVP (AVP code 2055 is of type enumerated and 
 * tags if the client is looking for AoCI in conjunction to the 
 *Request-Type and Request-Action AVPs.
 */
public class AoCRequestType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        AoC_NOT_REQUESTED(0),
        AoC_FULL(1),
        AoC_COST_ONLY(2),
        AoC_TARIFF_ONLY(3);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a AoCRequestType with the given value.
     *
     * @param value - the value of the AVP
     */
    public AoCRequestType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    AoCRequestType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
