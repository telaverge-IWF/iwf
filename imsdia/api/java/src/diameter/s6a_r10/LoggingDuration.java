package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class LoggingDuration extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        SEC_600(0),
        SEC_1200(1),
        SEC_2400(2),
        SEC_3600(3),
        SEC_5400(4),
        SEC_7200(5);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a LoggingDuration with the given value.
     *
     * @param value - the value of the AVP
     */
    public LoggingDuration(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    LoggingDuration(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
