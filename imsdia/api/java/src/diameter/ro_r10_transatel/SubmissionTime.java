package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Submission-Time AVP is of type Time and indicates the time at which the MM was submitted or
 * forwarded as specified in the corresponding MMI message.
 */
public class SubmissionTime extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a SubmissionTime with the given value.
     *
     * @param value - the value of the AVP
     */
    public SubmissionTime(Integer value) {
        super(new com.intellinet.diameter.TimeData(value));
    }

    SubmissionTime(com.intellinet.diameter.TimeData data) {
        super(data);
    }
}
