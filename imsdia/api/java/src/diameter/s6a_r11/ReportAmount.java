package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class ReportAmount extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        NUM_REPORTS_1(0),
        NUM_REPORTS_2(1),
        NUM_REPORTS_4(2),
        NUM_REPORTS_8(3),
        NUM_REPORTS_16(4),
        NUM_REPORTS_32(5),
        NUM_REPORTS_64(6),
        NUM_REPORTS_INFINITE(7);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a ReportAmount with the given value.
     *
     * @param value - the value of the AVP
     */
    public ReportAmount(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    ReportAmount(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
