package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class GMLCRestriction extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        GMLC_LIST(0),
        HOME_COUNTRY(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a GMLCRestriction with the given value.
     *
     * @param value - the value of the AVP
     */
    public GMLCRestriction(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    GMLCRestriction(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
