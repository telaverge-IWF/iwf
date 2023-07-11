package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class LoggingInterval extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        LOG_PERIODICITY_1_28(0),
        LOG_PERIODICITY_2_56(1),
        LOG_PERIODICITY_5_12(2),
        LOG_PERIODICITY_10_24(3),
        LOG_PERIODICITY_20_48(4),
        LOG_PERIODICITY_30_72(5),
        LOG_PERIODICITY_40_96(6),
        LOG_PERIODICITY_61_44(7);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a LoggingInterval with the given value.
     *
     * @param value - the value of the AVP
     */
    public LoggingInterval(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    LoggingInterval(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
