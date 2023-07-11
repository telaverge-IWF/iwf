package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class CurrentLocationRetrieved extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        ACTIVE_LOCATION_RETRIEVAL(0);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a CurrentLocationRetrieved with the given value.
     *
     * @param value - the value of the AVP
     */
    public CurrentLocationRetrieved(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    CurrentLocationRetrieved(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
