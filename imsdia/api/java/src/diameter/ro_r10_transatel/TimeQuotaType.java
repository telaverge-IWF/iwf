package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Time-Quota-Type AVP (AVP code 1271) is of type Enumerated. It is 
 * used to indicate which time quota consumption mechanism shall be used 
 * for the associated Rating Group.
 */
public class TimeQuotaType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        DISCRETE_TIME_PERIOD(0),
        CONTINUOUS_TIME_PERIOD(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a TimeQuotaType with the given value.
     *
     * @param value - the value of the AVP
     */
    public TimeQuotaType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    TimeQuotaType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
