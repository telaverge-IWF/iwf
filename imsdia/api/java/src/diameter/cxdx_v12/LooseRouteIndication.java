package diameter.cxdx_v12;

import com.intellinet.diameter.*;


public class LooseRouteIndication extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        LOOSE_ROUTE_NOT_REQUIRED(0),
        LOOSE_ROUTE_REQUIRED(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a LooseRouteIndication with the given value.
     *
     * @param value - the value of the AVP
     */
    public LooseRouteIndication(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    LooseRouteIndication(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
