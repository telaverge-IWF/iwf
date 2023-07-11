package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class RelayNodeIndicator extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        NOT_RELAY_NODE(0),
        RELAY_NODE(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a RelayNodeIndicator with the given value.
     *
     * @param value - the value of the AVP
     */
    public RelayNodeIndicator(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    RelayNodeIndicator(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
