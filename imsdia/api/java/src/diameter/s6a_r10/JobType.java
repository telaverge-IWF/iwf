package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class JobType extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        IMMEDIATE_MDT_ONLY(0),
        LOGGED_MDT_ONLY(1),
        TRACE_ONLY(2),
        IMMEDIATE_MDT_AND_TRACE(3);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a JobType with the given value.
     *
     * @param value - the value of the AVP
     */
    public JobType(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    JobType(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
