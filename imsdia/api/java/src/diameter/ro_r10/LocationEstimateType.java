package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * Location-Estimate-Type AVP is of type UTF8String.
 */
public class LocationEstimateType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        CURRENT_LOCATION(0),
        CURRENT_LAST_KNOWN_LOCATION(1),
        INITIAL_LOCATION(2),
        ACTIVATE_DEFERRED_LOCATION(3),
        CANCEL_DEFERRED_LOCATION(4);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a LocationEstimateType with the given value.
     *
     * @param value - the value of the AVP
     */
    public LocationEstimateType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    LocationEstimateType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
