package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class CSGAccessMode extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        CLOSED_MODE(0),
        HYBRID_MODE(1);

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
