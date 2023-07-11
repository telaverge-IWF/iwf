package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Reporting-Reason AVP is of type Enumerated and specifies the reason for usage reporting for
 * one or more types of quota for a particular category.
 */
public class ReportingReason extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        THRESHOLD(0),
        QHT(1),
        FINAL(2),
        QUOTA_EXHAUSTED(3),
        VALIDITY_TIME(4),
        OTHER_QUOTA_TYPE(5),
        RATING_CONDITION_CHANGE(6),
        FORCED_REAUTHORISATION(7),
        POOL_EXHAUSTED(8);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a ReportingReason with the given value.
     *
     * @param value - the value of the AVP
     */
    public ReportingReason(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    ReportingReason(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
