package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class DaylightSavingTime extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        NO_ADJUSTMENT(0),
        PLUS_ONE_HOUR_ADJUSTMENT(1),
        PLUS_TWO_HOURS_ADJUSTMENT(2);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a DaylightSavingTime with the given value.
     *
     * @param value - the value of the AVP
     */
    public DaylightSavingTime(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    DaylightSavingTime(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
