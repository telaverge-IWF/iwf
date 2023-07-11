package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class ICSIndicator extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        FALSE(0),
        TRUE(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a ICSIndicator with the given value.
     *
     * @param value - the value of the AVP
     */
    public ICSIndicator(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    ICSIndicator(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
